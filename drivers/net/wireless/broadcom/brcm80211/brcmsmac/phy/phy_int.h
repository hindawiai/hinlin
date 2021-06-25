<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#अगर_अघोषित _BRCM_PHY_INT_H_
#घोषणा _BRCM_PHY_INT_H_

#समावेश <types.h>
#समावेश <brcmu_utils.h>
#समावेश <brcmu_wअगरi.h>

#घोषणा	PHY_VERSION			अणु 1, 82, 8, 0 पूर्ण

#घोषणा LCNXN_BASEREV		16

काष्ठा phy_shim_info;

काष्ठा brcms_phy_srom_fem अणु
	/* TSSI positive slope, 1: positive, 0: negative */
	u8 tssipos;
	/* Ext PA gain-type: full-gain: 0, pa-lite: 1, no_pa: 2 */
	u8 extpagain;
	/* support 32 combinations of dअगरferent Pdet dynamic ranges */
	u8 pdetrange;
	/* TR चयन isolation */
	u8 triso;
	/* antswctrl lookup table configuration: 32 possible choices */
	u8 antswctrllut;
पूर्ण;

#घोषणा ISNPHY(pi)	PHYTYPE_IS((pi)->pubpi.phy_type, PHY_TYPE_N)
#घोषणा ISLCNPHY(pi)	PHYTYPE_IS((pi)->pubpi.phy_type, PHY_TYPE_LCN)

#घोषणा PHY_GET_RFATTN(rfgain)	((rfgain) & 0x0f)
#घोषणा PHY_GET_PADMIX(rfgain)	(((rfgain) & 0x10) >> 4)
#घोषणा PHY_GET_RFGAINID(rfattn, padmix, width)	((rfattn) + ((padmix)*(width)))
#घोषणा PHY_SAT(x, n)		((x) > ((1<<((n)-1))-1) ? ((1<<((n)-1))-1) : \
				((x) < -(1<<((n)-1)) ? -(1<<((n)-1)) : (x)))
#घोषणा PHY_SHIFT_ROUND(x, n)	((x) >= 0 ? ((x)+(1<<((n)-1)))>>(n) : (x)>>(n))
#घोषणा PHY_HW_ROUND(x, s)		((x >> s) + ((x >> (s-1)) & (s != 0)))

#घोषणा CH_5G_GROUP	3
#घोषणा A_LOW_CHANS	0
#घोषणा A_MID_CHANS	1
#घोषणा A_HIGH_CHANS	2
#घोषणा CH_2G_GROUP	1
#घोषणा G_ALL_CHANS	0

#घोषणा FIRST_REF5_CHANNUM	149
#घोषणा LAST_REF5_CHANNUM	165
#घोषणा	FIRST_5G_CHAN		14
#घोषणा	LAST_5G_CHAN		50
#घोषणा	FIRST_MID_5G_CHAN	14
#घोषणा	LAST_MID_5G_CHAN	35
#घोषणा	FIRST_HIGH_5G_CHAN	36
#घोषणा	LAST_HIGH_5G_CHAN	41
#घोषणा	FIRST_LOW_5G_CHAN	42
#घोषणा	LAST_LOW_5G_CHAN	50

#घोषणा BASE_LOW_5G_CHAN	4900
#घोषणा BASE_MID_5G_CHAN	5100
#घोषणा BASE_HIGH_5G_CHAN	5500

#घोषणा CHAN5G_FREQ(chan)  (5000 + chan*5)
#घोषणा CHAN2G_FREQ(chan)  (2407 + chan*5)

#घोषणा TXP_FIRST_CCK		0
#घोषणा TXP_LAST_CCK		3
#घोषणा TXP_FIRST_OFDM		4
#घोषणा TXP_LAST_OFDM		11
#घोषणा TXP_FIRST_OFDM_20_CDD	12
#घोषणा TXP_LAST_OFDM_20_CDD	19
#घोषणा TXP_FIRST_MCS_20_SISO	20
#घोषणा TXP_LAST_MCS_20_SISO	27
#घोषणा TXP_FIRST_MCS_20_CDD	28
#घोषणा TXP_LAST_MCS_20_CDD	35
#घोषणा TXP_FIRST_MCS_20_STBC	36
#घोषणा TXP_LAST_MCS_20_STBC	43
#घोषणा TXP_FIRST_MCS_20_SDM	44
#घोषणा TXP_LAST_MCS_20_SDM	51
#घोषणा TXP_FIRST_OFDM_40_SISO	52
#घोषणा TXP_LAST_OFDM_40_SISO	59
#घोषणा TXP_FIRST_OFDM_40_CDD	60
#घोषणा TXP_LAST_OFDM_40_CDD	67
#घोषणा TXP_FIRST_MCS_40_SISO	68
#घोषणा TXP_LAST_MCS_40_SISO	75
#घोषणा TXP_FIRST_MCS_40_CDD	76
#घोषणा TXP_LAST_MCS_40_CDD	83
#घोषणा TXP_FIRST_MCS_40_STBC	84
#घोषणा TXP_LAST_MCS_40_STBC	91
#घोषणा TXP_FIRST_MCS_40_SDM	92
#घोषणा TXP_LAST_MCS_40_SDM	99
#घोषणा TXP_MCS_32	        100
#घोषणा TXP_NUM_RATES		101
#घोषणा ADJ_PWR_TBL_LEN		84

#घोषणा TXP_FIRST_SISO_MCS_20	20
#घोषणा TXP_LAST_SISO_MCS_20	27

#घोषणा PHY_CORE_NUM_1	1
#घोषणा PHY_CORE_NUM_2	2
#घोषणा PHY_CORE_NUM_3	3
#घोषणा PHY_CORE_NUM_4	4
#घोषणा PHY_CORE_MAX	PHY_CORE_NUM_4
#घोषणा PHY_CORE_0	0
#घोषणा PHY_CORE_1	1
#घोषणा PHY_CORE_2	2
#घोषणा PHY_CORE_3	3

#घोषणा MA_WINDOW_SZ		8

#घोषणा PHY_NOISE_SAMPLE_MON		1
#घोषणा PHY_NOISE_SAMPLE_EXTERNAL	2
#घोषणा PHY_NOISE_WINDOW_SZ	16
#घोषणा PHY_NOISE_GLITCH_INIT_MA 10
#घोषणा PHY_NOISE_GLITCH_INIT_MA_BADPlCP 10
#घोषणा PHY_NOISE_STATE_MON		0x1
#घोषणा PHY_NOISE_STATE_EXTERNAL	0x2
#घोषणा PHY_NOISE_SAMPLE_LOG_NUM_NPHY	10
#घोषणा PHY_NOISE_SAMPLE_LOG_NUM_UCODE	9

#घोषणा PHY_NOISE_OFFSETFACT_4322  (-103)
#घोषणा PHY_NOISE_MA_WINDOW_SZ	2

#घोषणा	PHY_RSSI_TABLE_SIZE	64
#घोषणा RSSI_ANT_MERGE_MAX	0
#घोषणा RSSI_ANT_MERGE_MIN	1
#घोषणा RSSI_ANT_MERGE_AVG	2

#घोषणा	PHY_TSSI_TABLE_SIZE	64
#घोषणा	APHY_TSSI_TABLE_SIZE	256
#घोषणा	TX_GAIN_TABLE_LENGTH	64
#घोषणा	DEFAULT_11A_TXP_IDX	24
#घोषणा NUM_TSSI_FRAMES        4
#घोषणा	शून्य_TSSI		0x7f
#घोषणा	शून्य_TSSI_W		0x7f7f

#घोषणा PHY_PAPD_EPS_TBL_SIZE_LCNPHY 64

#घोषणा LCNPHY_PERICAL_TEMPBASED_TXPWRCTRL 9

#घोषणा PHY_TXPWR_MIN		10
#घोषणा PHY_TXPWR_MIN_NPHY	8
#घोषणा RADIOPWR_OVERRIDE_DEF	(-1)

#घोषणा PWRTBL_NUM_COEFF	3

#घोषणा SPURAVOID_DISABLE	0
#घोषणा SPURAVOID_AUTO		1
#घोषणा SPURAVOID_FORCEON	2
#घोषणा SPURAVOID_FORCEON2	3

#घोषणा PHY_SW_TIMER_FAST		15
#घोषणा PHY_SW_TIMER_SLOW		60
#घोषणा PHY_SW_TIMER_GLACIAL	120

#घोषणा PHY_PERICAL_AUTO	0
#घोषणा PHY_PERICAL_FULL	1
#घोषणा PHY_PERICAL_PARTIAL	2

#घोषणा PHY_PERICAL_NODELAY	0
#घोषणा PHY_PERICAL_INIT_DELAY	5
#घोषणा PHY_PERICAL_ASSOC_DELAY	5
#घोषणा PHY_PERICAL_WDOG_DELAY	5

#घोषणा MPHASE_TXCAL_NUMCMDS	2

#घोषणा PHY_PERICAL_MPHASE_PENDING(pi) \
	(pi->mphase_cal_phase_id > MPHASE_CAL_STATE_IDLE)

क्रमागत अणु
	MPHASE_CAL_STATE_IDLE = 0,
	MPHASE_CAL_STATE_INIT = 1,
	MPHASE_CAL_STATE_TXPHASE0,
	MPHASE_CAL_STATE_TXPHASE1,
	MPHASE_CAL_STATE_TXPHASE2,
	MPHASE_CAL_STATE_TXPHASE3,
	MPHASE_CAL_STATE_TXPHASE4,
	MPHASE_CAL_STATE_TXPHASE5,
	MPHASE_CAL_STATE_PAPDCAL,
	MPHASE_CAL_STATE_RXCAL,
	MPHASE_CAL_STATE_RSSICAL,
	MPHASE_CAL_STATE_IDLETSSI
पूर्ण;

क्रमागत phy_cal_mode अणु
	CAL_FULL,
	CAL_RECAL,
	CAL_CURRECAL,
	CAL_DIGCAL,
	CAL_GCTRL,
	CAL_SOFT,
	CAL_DIGLO
पूर्ण;

#घोषणा RDR_NTIERS  1
#घोषणा RDR_TIER_SIZE 64
#घोषणा RDR_LIST_SIZE (512/3)
#घोषणा RDR_EPOCH_SIZE 40
#घोषणा RDR_न_अंकTENNAS 2
#घोषणा RDR_NTIER_SIZE  RDR_LIST_SIZE
#घोषणा RDR_LP_BUFFER_SIZE 64
#घोषणा LP_LEN_HIS_SIZE 10

#घोषणा STATIC_NUM_RF 32
#घोषणा STATIC_NUM_BB 9

#घोषणा BB_MULT_MASK		0x0000ffff
#घोषणा BB_MULT_VALID_MASK	0x80000000

#घोषणा PHY_CHAIN_TX_DISABLE_TEMP	115
#घोषणा PHY_HYSTERESIS_DELTATEMP	5

#घोषणा SCAN_INPROG_PHY(pi) \
	(mboolisset(pi->measure_hold, PHY_HOLD_FOR_SCAN))

#घोषणा PLT_INPROG_PHY(pi)      (mboolisset(pi->measure_hold, PHY_HOLD_FOR_PLT))

#घोषणा ASSOC_INPROG_PHY(pi) \
	(mboolisset(pi->measure_hold, PHY_HOLD_FOR_ASSOC))

#घोषणा SCAN_RM_IN_PROGRESS(pi) \
	(mboolisset(pi->measure_hold, PHY_HOLD_FOR_SCAN | PHY_HOLD_FOR_RM))

#घोषणा PHY_MUTED(pi) \
	(mboolisset(pi->measure_hold, PHY_HOLD_FOR_MUTE))

#घोषणा PUB_NOT_ASSOC(pi) \
	(mboolisset(pi->measure_hold, PHY_HOLD_FOR_NOT_ASSOC))

काष्ठा phy_table_info अणु
	uपूर्णांक table;
	पूर्णांक q;
	uपूर्णांक max;
पूर्ण;

काष्ठा phytbl_info अणु
	स्थिर व्योम *tbl_ptr;
	u32 tbl_len;
	u32 tbl_id;
	u32 tbl_offset;
	u32 tbl_width;
पूर्ण;

काष्ठा पूर्णांकerference_info अणु
	u8 curr_home_channel;
	u16 crsminpwrthld_40_stored;
	u16 crsminpwrthld_20L_stored;
	u16 crsminpwrthld_20U_stored;
	u16 init_gain_code_core1_stored;
	u16 init_gain_code_core2_stored;
	u16 init_gain_codeb_core1_stored;
	u16 init_gain_codeb_core2_stored;
	u16 init_gain_table_stored[4];

	u16 clip1_hi_gain_code_core1_stored;
	u16 clip1_hi_gain_code_core2_stored;
	u16 clip1_hi_gain_codeb_core1_stored;
	u16 clip1_hi_gain_codeb_core2_stored;
	u16 nb_clip_thresh_core1_stored;
	u16 nb_clip_thresh_core2_stored;
	u16 init_ofdmlna2gainchange_stored[4];
	u16 init_ccklna2gainchange_stored[4];
	u16 clip1_lo_gain_code_core1_stored;
	u16 clip1_lo_gain_code_core2_stored;
	u16 clip1_lo_gain_codeb_core1_stored;
	u16 clip1_lo_gain_codeb_core2_stored;
	u16 w1_clip_thresh_core1_stored;
	u16 w1_clip_thresh_core2_stored;
	u16 radio_2056_core1_rssi_gain_stored;
	u16 radio_2056_core2_rssi_gain_stored;
	u16 energy_drop_समयout_len_stored;

	u16 ed_crs40_निश्चितthld0_stored;
	u16 ed_crs40_निश्चितthld1_stored;
	u16 ed_crs40_deनिश्चितthld0_stored;
	u16 ed_crs40_deनिश्चितthld1_stored;
	u16 ed_crs20L_निश्चितthld0_stored;
	u16 ed_crs20L_निश्चितthld1_stored;
	u16 ed_crs20L_deनिश्चितthld0_stored;
	u16 ed_crs20L_deनिश्चितthld1_stored;
	u16 ed_crs20U_निश्चितthld0_stored;
	u16 ed_crs20U_निश्चितthld1_stored;
	u16 ed_crs20U_deनिश्चितthld0_stored;
	u16 ed_crs20U_deनिश्चितthld1_stored;

	u16 badplcp_ma;
	u16 badplcp_ma_previous;
	u16 badplcp_ma_total;
	u16 badplcp_ma_list[MA_WINDOW_SZ];
	पूर्णांक badplcp_ma_index;
	s16 pre_badplcp_cnt;
	s16 bphy_pre_badplcp_cnt;

	u16 init_gain_core1;
	u16 init_gain_core2;
	u16 init_gainb_core1;
	u16 init_gainb_core2;
	u16 init_gain_rfseq[4];

	u16 crsminpwr0;
	u16 crsminpwrl0;
	u16 crsminpwru0;

	s16 crsminpwr_index;

	u16 radio_2057_core1_rssi_wb1a_gc_stored;
	u16 radio_2057_core2_rssi_wb1a_gc_stored;
	u16 radio_2057_core1_rssi_wb1g_gc_stored;
	u16 radio_2057_core2_rssi_wb1g_gc_stored;
	u16 radio_2057_core1_rssi_wb2_gc_stored;
	u16 radio_2057_core2_rssi_wb2_gc_stored;
	u16 radio_2057_core1_rssi_nb_gc_stored;
	u16 radio_2057_core2_rssi_nb_gc_stored;
पूर्ण;

काष्ठा aci_save_gphy अणु
	u16 rc_cal_ovr;
	u16 phycrsth1;
	u16 phycrsth2;
	u16 init_n1p1_gain;
	u16 p1_p2_gain;
	u16 n1_n2_gain;
	u16 n1_p1_gain;
	u16 भाग_search_gain;
	u16 भाग_p1_p2_gain;
	u16 भाग_search_gn_change;
	u16 table_7_2;
	u16 table_7_3;
	u16 cckshbits_gnref;
	u16 clip_thresh;
	u16 clip2_thresh;
	u16 clip3_thresh;
	u16 clip_p2_thresh;
	u16 clip_pwdn_thresh;
	u16 clip_n1p1_thresh;
	u16 clip_n1_pwdn_thresh;
	u16 bbconfig;
	u16 cthr_sthr_shdin;
	u16 energy;
	u16 clip_p1_p2_thresh;
	u16 threshold;
	u16 reg15;
	u16 reg16;
	u16 reg17;
	u16 भाग_srch_idx;
	u16 भाग_srch_p1_p2;
	u16 भाग_srch_gn_back;
	u16 ant_dwell;
	u16 ant_wr_settle;
पूर्ण;

काष्ठा lo_complex_abgphy_info अणु
	s8 i;
	s8 q;
पूर्ण;

काष्ठा nphy_iq_comp अणु
	s16 a0;
	s16 b0;
	s16 a1;
	s16 b1;
पूर्ण;

काष्ठा nphy_txpwrindex अणु
	s8 index;
	s8 index_पूर्णांकernal;
	s8 index_पूर्णांकernal_save;
	u16 AfectrlOverride;
	u16 AfeCtrlDacGain;
	u16 rad_gain;
	u8 bbmult;
	u16 iqcomp_a;
	u16 iqcomp_b;
	u16 locomp;
पूर्ण;

काष्ठा txiqcal_cache अणु

	u16 txcal_coeffs_2G[8];
	u16 txcal_radio_regs_2G[8];
	काष्ठा nphy_iq_comp rxcal_coeffs_2G;

	u16 txcal_coeffs_5G[8];
	u16 txcal_radio_regs_5G[8];
	काष्ठा nphy_iq_comp rxcal_coeffs_5G;
पूर्ण;

काष्ठा nphy_pwrctrl अणु
	s8 max_pwr_2g;
	s8 idle_targ_2g;
	s16 pwrdet_2g_a1;
	s16 pwrdet_2g_b0;
	s16 pwrdet_2g_b1;
	s8 max_pwr_5gm;
	s8 idle_targ_5gm;
	s8 max_pwr_5gh;
	s8 max_pwr_5gl;
	s16 pwrdet_5gm_a1;
	s16 pwrdet_5gm_b0;
	s16 pwrdet_5gm_b1;
	s16 pwrdet_5gl_a1;
	s16 pwrdet_5gl_b0;
	s16 pwrdet_5gl_b1;
	s16 pwrdet_5gh_a1;
	s16 pwrdet_5gh_b0;
	s16 pwrdet_5gh_b1;
	s8 idle_targ_5gl;
	s8 idle_targ_5gh;
	s8 idle_tssi_2g;
	s8 idle_tssi_5g;
	s8 idle_tssi;
	s16 a1;
	s16 b0;
	s16 b1;
पूर्ण;

काष्ठा nphy_txgains अणु
	u16 txlpf[2];
	u16 txgm[2];
	u16 pga[2];
	u16 pad[2];
	u16 ipa[2];
पूर्ण;

#घोषणा PHY_NOISEVAR_बफ_मानE 10

काष्ठा nphy_noisevar_buf अणु
	पूर्णांक bufcount;
	पूर्णांक tone_id[PHY_NOISEVAR_बफ_मानE];
	u32 noise_vars[PHY_NOISEVAR_बफ_मानE];
	u32 min_noise_vars[PHY_NOISEVAR_बफ_मानE];
पूर्ण;

काष्ठा rssical_cache अणु
	u16 rssical_radio_regs_2G[2];
	u16 rssical_phyregs_2G[12];

	u16 rssical_radio_regs_5G[2];
	u16 rssical_phyregs_5G[12];
पूर्ण;

काष्ठा lcnphy_cal_results अणु

	u16 txiqlocal_a;
	u16 txiqlocal_b;
	u16 txiqlocal_didq;
	u8 txiqlocal_ei0;
	u8 txiqlocal_eq0;
	u8 txiqlocal_fi0;
	u8 txiqlocal_fq0;

	u16 txiqlocal_bestcoeffs[11];
	u16 txiqlocal_bestcoeffs_valid;

	u32 papd_eps_tbl[PHY_PAPD_EPS_TBL_SIZE_LCNPHY];
	u16 analog_gain_ref;
	u16 lut_begin;
	u16 lut_end;
	u16 lut_step;
	u16 rxcompdbm;
	u16 papdctrl;
	u16 sslpnCalibClkEnCtrl;

	u16 rxiqcal_coeff_a0;
	u16 rxiqcal_coeff_b0;
पूर्ण;

काष्ठा shared_phy अणु
	काष्ठा brcms_phy *phy_head;
	uपूर्णांक unit;
	काष्ठा phy_shim_info *physhim;
	uपूर्णांक corerev;
	u32 machwcap;
	bool up;
	bool clk;
	uपूर्णांक now;
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
	uपूर्णांक fast_समयr;
	uपूर्णांक slow_समयr;
	uपूर्णांक glacial_समयr;
	u8 rx_antभाग;
	s8 phy_noise_winकरोw[MA_WINDOW_SZ];
	uपूर्णांक phy_noise_index;
	u8 hw_phytxchain;
	u8 hw_phyrxchain;
	u8 phytxchain;
	u8 phyrxchain;
	u8 rssi_mode;
	bool _rअगरs_phy;
पूर्ण;

काष्ठा brcms_phy_pub अणु
	uपूर्णांक phy_type;
	uपूर्णांक phy_rev;
	u8 phy_corक्रमागत;
	u16 radioid;
	u8 radiorev;
	u8 radiover;

	uपूर्णांक coreflags;
	uपूर्णांक ana_rev;
	bool abgphy_encore;
पूर्ण;

काष्ठा phy_func_ptr अणु
	व्योम (*init)(काष्ठा brcms_phy *);
	व्योम (*calinit)(काष्ठा brcms_phy *);
	व्योम (*chanset)(काष्ठा brcms_phy *, u16 chanspec);
	व्योम (*txpwrrecalc)(काष्ठा brcms_phy *);
	पूर्णांक (*दीर्घtrn)(काष्ठा brcms_phy *, पूर्णांक);
	व्योम (*txiqccget)(काष्ठा brcms_phy *, u16 *, u16 *);
	व्योम (*txiqccset)(काष्ठा brcms_phy *, u16, u16);
	u16 (*txloccget)(काष्ठा brcms_phy *);
	व्योम (*radioloftget)(काष्ठा brcms_phy *, u8 *, u8 *, u8 *, u8 *);
	व्योम (*carrsuppr)(काष्ठा brcms_phy *);
	s32 (*rxsigpwr)(काष्ठा brcms_phy *, s32);
	व्योम (*detach)(काष्ठा brcms_phy *);
पूर्ण;

काष्ठा brcms_phy अणु
	काष्ठा brcms_phy_pub pubpi_ro;
	काष्ठा shared_phy *sh;
	काष्ठा phy_func_ptr pi_fptr;

	जोड़ अणु
		काष्ठा brcms_phy_lcnphy *pi_lcnphy;
	पूर्ण u;
	bool user_txpwr_at_rfport;

	काष्ठा bcma_device *d11core;
	काष्ठा brcms_phy *next;
	काष्ठा brcms_phy_pub pubpi;

	bool करो_initcal;
	bool phytest_on;
	bool ofdm_rateset_war;
	bool bf_preempt_4306;
	u16 radio_chanspec;
	u8 antsel_type;
	u16 bw;
	u8 txpwr_percent;
	bool phy_init_por;

	bool init_in_progress;
	bool initialized;
	bool sbपंचांगl_gm;
	uपूर्णांक refcnt;
	bool watchकरोg_override;
	u8 phynoise_state;
	uपूर्णांक phynoise_now;
	पूर्णांक phynoise_chan_watchकरोg;
	bool phynoise_polling;
	bool disable_percal;
	u32 measure_hold;

	s16 txpa_2g[PWRTBL_NUM_COEFF];
	s16 txpa_2g_low_temp[PWRTBL_NUM_COEFF];
	s16 txpa_2g_high_temp[PWRTBL_NUM_COEFF];
	s16 txpa_5g_low[PWRTBL_NUM_COEFF];
	s16 txpa_5g_mid[PWRTBL_NUM_COEFF];
	s16 txpa_5g_hi[PWRTBL_NUM_COEFF];

	u8 tx_srom_max_2g;
	u8 tx_srom_max_5g_low;
	u8 tx_srom_max_5g_mid;
	u8 tx_srom_max_5g_hi;
	u8 tx_srom_max_rate_2g[TXP_NUM_RATES];
	u8 tx_srom_max_rate_5g_low[TXP_NUM_RATES];
	u8 tx_srom_max_rate_5g_mid[TXP_NUM_RATES];
	u8 tx_srom_max_rate_5g_hi[TXP_NUM_RATES];
	u8 tx_user_target[TXP_NUM_RATES];
	s8 tx_घातer_offset[TXP_NUM_RATES];
	u8 tx_घातer_target[TXP_NUM_RATES];

	काष्ठा brcms_phy_srom_fem srom_fem2g;
	काष्ठा brcms_phy_srom_fem srom_fem5g;

	u8 tx_घातer_max;
	u8 tx_घातer_max_rate_ind;
	bool hwpwrctrl;
	u8 nphy_txpwrctrl;
	s8 nphy_txrx_chain;
	bool phy_5g_pwrgain;

	u16 phy_wreg;
	u16 phy_wreg_limit;

	s8 n_preamble_override;
	u8 antचयन;
	u8 aa2g, aa5g;

	s8 idle_tssi[CH_5G_GROUP];
	s8 target_idle_tssi;
	s8 txpwr_est_Pout;
	u8 tx_घातer_min;
	u8 txpwr_limit[TXP_NUM_RATES];
	u8 txpwr_env_limit[TXP_NUM_RATES];
	u8 adj_pwr_tbl_nphy[ADJ_PWR_TBL_LEN];

	bool channel_14_wide_filter;

	bool txpwroverride;
	bool txpwridx_override_aphy;
	s16 radiopwr_override;
	u16 hwpwr_txcur;
	u8 saved_txpwr_idx;

	bool edcrs_threshold_lock;

	u32 tr_R_gain_val;
	u32 tr_T_gain_val;

	s16 ofdm_analog_filt_bw_override;
	s16 cck_analog_filt_bw_override;
	s16 ofdm_rccal_override;
	s16 cck_rccal_override;
	u16 extlna_type;

	uपूर्णांक पूर्णांकerference_mode_crs_समय;
	u16 crsglitch_prev;
	bool पूर्णांकerference_mode_crs;

	u32 phy_tx_tone_freq;
	uपूर्णांक phy_lastcal;
	bool phy_क्रमcecal;
	bool phy_fixed_noise;
	u32 xtalfreq;
	u8 pभाग;
	s8 carrier_suppr_disable;

	bool phy_bphy_evm;
	bool phy_bphy_rfcs;
	s8 phy_scraminit;
	u8 phy_gpiosel;

	s16 phy_txcore_disable_temp;
	s16 phy_txcore_enable_temp;
	s8 phy_tempsense_offset;
	bool phy_txcore_heatedup;

	u16 radiopwr;
	u16 bb_atten;
	u16 txctl1;

	u16 mपूर्णांकxbias;
	u16 mपूर्णांकxmag;
	काष्ठा lo_complex_abgphy_info gphy_locomp_iq
			[STATIC_NUM_RF][STATIC_NUM_BB];
	s8 stats_11b_txघातer[STATIC_NUM_RF][STATIC_NUM_BB];
	u16 gain_table[TX_GAIN_TABLE_LENGTH];
	bool loopback_gain;
	s16 max_lpback_gain_hdB;
	s16 trsw_rx_gain_hdB;
	u8 घातer_vec[8];

	u16 rc_cal;
	पूर्णांक nrssi_table_delta;
	पूर्णांक nrssi_slope_scale;
	पूर्णांक nrssi_slope_offset;
	पूर्णांक min_rssi;
	पूर्णांक max_rssi;

	s8 txpwridx;
	u8 min_txघातer;

	u8 a_band_high_disable;

	u16 tx_vos;
	u16 global_tx_bb_dc_bias_loft;

	पूर्णांक rf_max;
	पूर्णांक bb_max;
	पूर्णांक rf_list_size;
	पूर्णांक bb_list_size;
	u16 *rf_attn_list;
	u16 *bb_attn_list;
	u16 padmix_mask;
	u16 padmix_reg;
	u16 *txmag_list;
	uपूर्णांक txmag_len;
	bool txmag_enable;

	s8 *a_tssi_to_dbm;
	s8 *m_tssi_to_dbm;
	s8 *l_tssi_to_dbm;
	s8 *h_tssi_to_dbm;
	u8 *hwtxpwr;

	u16 freqtrack_saved_regs[2];
	पूर्णांक cur_पूर्णांकerference_mode;
	bool hwpwrctrl_capable;
	bool temppwrctrl_capable;

	uपूर्णांक phycal_nslope;
	uपूर्णांक phycal_noffset;
	uपूर्णांक phycal_mlo;
	uपूर्णांक phycal_txघातer;

	u8 phy_aa2g;

	bool nphy_tableloaded;
	s8 nphy_rssisel;
	u32 nphy_bb_mult_save;
	u16 nphy_txiqlocal_bestc[11];
	bool nphy_txiqlocal_coeffsvalid;
	काष्ठा nphy_txpwrindex nphy_txpwrindex[PHY_CORE_NUM_2];
	काष्ठा nphy_pwrctrl nphy_pwrctrl_info[PHY_CORE_NUM_2];
	u16 cck2gpo;
	u32 ofdm2gpo;
	u32 ofdm5gpo;
	u32 ofdm5glpo;
	u32 ofdm5ghpo;
	u8 bw402gpo;
	u8 bw405gpo;
	u8 bw405glpo;
	u8 bw405ghpo;
	u8 cdd2gpo;
	u8 cdd5gpo;
	u8 cdd5glpo;
	u8 cdd5ghpo;
	u8 stbc2gpo;
	u8 stbc5gpo;
	u8 stbc5glpo;
	u8 stbc5ghpo;
	u8 bwdup2gpo;
	u8 bwdup5gpo;
	u8 bwdup5glpo;
	u8 bwdup5ghpo;
	u16 mcs2gpo[8];
	u16 mcs5gpo[8];
	u16 mcs5glpo[8];
	u16 mcs5ghpo[8];
	u32 nphy_rxcalparams;

	u8 phy_spuraव्योम;
	bool phy_isspuraव्योम;

	u8 phy_pabias;
	u8 nphy_papd_skip;
	u8 nphy_tssi_slope;

	s16 nphy_noise_win[PHY_CORE_MAX][PHY_NOISE_WINDOW_SZ];
	u8 nphy_noise_index;

	bool nphy_gain_boost;
	bool nphy_elna_gain_config;
	u16 old_bphy_test;
	u16 old_bphy_testcontrol;

	bool phyhang_aव्योम;

	bool rssical_nphy;
	u8 nphy_perical;
	uपूर्णांक nphy_perical_last;
	u8 cal_type_override;
	u8 mphase_cal_phase_id;
	u8 mphase_txcal_cmdidx;
	u8 mphase_txcal_numcmds;
	u16 mphase_txcal_bestcoeffs[11];
	u16 nphy_txiqlocal_chanspec;
	u16 nphy_iqcal_chanspec_2G;
	u16 nphy_iqcal_chanspec_5G;
	u16 nphy_rssical_chanspec_2G;
	u16 nphy_rssical_chanspec_5G;
	काष्ठा wlapi_समयr *phycal_समयr;
	bool use_पूर्णांक_tx_iqlo_cal_nphy;
	bool पूर्णांकernal_tx_iqlo_cal_tapoff_पूर्णांकpa_nphy;
	s16 nphy_lastcal_temp;

	काष्ठा txiqcal_cache calibration_cache;
	काष्ठा rssical_cache rssical_cache;

	u8 nphy_txpwr_idx[2];
	u8 nphy_papd_cal_type;
	uपूर्णांक nphy_papd_last_cal;
	u16 nphy_papd_tx_gain_at_last_cal[2];
	u8 nphy_papd_cal_gain_index[2];
	s16 nphy_papd_epsilon_offset[2];
	bool nphy_papd_recal_enable;
	u32 nphy_papd_recal_counter;
	bool nphy_क्रमce_papd_cal;
	bool nphy_papdcomp;
	bool ipa2g_on;
	bool ipa5g_on;

	u16 classअगरier_state;
	u16 clip_state[2];
	uपूर्णांक nphy_deaf_count;
	u8 rxiq_samps;
	u8 rxiq_antsel;

	u16 rfctrlIntc1_save;
	u16 rfctrlIntc2_save;
	bool first_cal_after_assoc;
	u16 tx_rx_cal_radio_saveregs[22];
	u16 tx_rx_cal_phy_saveregs[15];

	u8 nphy_cal_orig_pwr_idx[2];
	u8 nphy_txcal_pwr_idx[2];
	u8 nphy_rxcal_pwr_idx[2];
	u16 nphy_cal_orig_tx_gain[2];
	काष्ठा nphy_txgains nphy_cal_target_gain;
	u16 nphy_txcal_bbmult;
	u16 nphy_gmval;

	u16 nphy_saved_bbconf;

	bool nphy_gband_spurwar_en;
	bool nphy_gband_spurwar2_en;
	bool nphy_aband_spurwar_en;
	u16 nphy_rccal_value;
	u16 nphy_crsminpwr[3];
	काष्ठा nphy_noisevar_buf nphy_saved_noisevars;
	bool nphy_anarxlpf_adjusted;
	bool nphy_crsminpwr_adjusted;
	bool nphy_noisevars_adjusted;

	bool nphy_rxcal_active;
	u16 radar_percal_mask;
	bool dfs_lp_buffer_nphy;

	u16 nphy_fineघड़ीgatecontrol;

	s8 rx2tx_biasentry;

	u16 crsminpwr0;
	u16 crsminpwrl0;
	u16 crsminpwru0;
	s16 noise_crsminpwr_index;
	u16 init_gain_core1;
	u16 init_gain_core2;
	u16 init_gainb_core1;
	u16 init_gainb_core2;
	u8 aci_noise_curr_channel;
	u16 init_gain_rfseq[4];

	bool radio_is_on;

	bool nphy_sample_play_lpf_bw_ctl_ovr;

	u16 tbl_data_hi;
	u16 tbl_data_lo;
	u16 tbl_addr;

	uपूर्णांक tbl_save_id;
	uपूर्णांक tbl_save_offset;

	u8 txpwrctrl;
	s8 txpwrindex[PHY_CORE_MAX];

	u8 phycal_tempdelta;
	u32 mcs20_po;
	u32 mcs40_po;
	काष्ठा wiphy *wiphy;
पूर्ण;

काष्ठा cs32 अणु
	s32 q;
	s32 i;
पूर्ण;

काष्ठा radio_regs अणु
	u16 address;
	u32 init_a;
	u32 init_g;
	u8 करो_init_a;
	u8 करो_init_g;
पूर्ण;

काष्ठा radio_20xx_regs अणु
	u16 address;
	u8 init;
	u8 करो_init;
पूर्ण;

काष्ठा lcnphy_radio_regs अणु
	u16 address;
	u8 init_a;
	u8 init_g;
	u8 करो_init_a;
	u8 करो_init_g;
पूर्ण;

u16 पढ़ो_phy_reg(काष्ठा brcms_phy *pi, u16 addr);
व्योम ग_लिखो_phy_reg(काष्ठा brcms_phy *pi, u16 addr, u16 val);
व्योम and_phy_reg(काष्ठा brcms_phy *pi, u16 addr, u16 val);
व्योम or_phy_reg(काष्ठा brcms_phy *pi, u16 addr, u16 val);
व्योम mod_phy_reg(काष्ठा brcms_phy *pi, u16 addr, u16 mask, u16 val);

u16 पढ़ो_radio_reg(काष्ठा brcms_phy *pi, u16 addr);
व्योम or_radio_reg(काष्ठा brcms_phy *pi, u16 addr, u16 val);
व्योम and_radio_reg(काष्ठा brcms_phy *pi, u16 addr, u16 val);
व्योम mod_radio_reg(काष्ठा brcms_phy *pi, u16 addr, u16 mask, u16 val);
व्योम xor_radio_reg(काष्ठा brcms_phy *pi, u16 addr, u16 mask);

व्योम ग_लिखो_radio_reg(काष्ठा brcms_phy *pi, u16 addr, u16 val);

व्योम wlc_phyreg_enter(काष्ठा brcms_phy_pub *pih);
व्योम wlc_phyreg_निकास(काष्ठा brcms_phy_pub *pih);
व्योम wlc_radioreg_enter(काष्ठा brcms_phy_pub *pih);
व्योम wlc_radioreg_निकास(काष्ठा brcms_phy_pub *pih);

व्योम wlc_phy_पढ़ो_table(काष्ठा brcms_phy *pi,
			स्थिर काष्ठा phytbl_info *ptbl_info,
			u16 tblAddr, u16 tblDataHi, u16 tblDatalo);
व्योम wlc_phy_ग_लिखो_table(काष्ठा brcms_phy *pi,
			 स्थिर काष्ठा phytbl_info *ptbl_info,
			 u16 tblAddr, u16 tblDataHi, u16 tblDatalo);
व्योम wlc_phy_table_addr(काष्ठा brcms_phy *pi, uपूर्णांक tbl_id, uपूर्णांक tbl_offset,
			u16 tblAddr, u16 tblDataHi, u16 tblDataLo);
व्योम wlc_phy_table_data_ग_लिखो(काष्ठा brcms_phy *pi, uपूर्णांक width, u32 val);

व्योम ग_लिखो_phy_channel_reg(काष्ठा brcms_phy *pi, uपूर्णांक val);
व्योम wlc_phy_txघातer_update_shm(काष्ठा brcms_phy *pi);

u8 wlc_phy_nbits(s32 value);
व्योम wlc_phy_compute_dB(u32 *cmplx_pwr, s8 *p_dB, u8 core);

uपूर्णांक wlc_phy_init_radio_regs_allbands(काष्ठा brcms_phy *pi,
				      काष्ठा radio_20xx_regs *radioregs);
uपूर्णांक wlc_phy_init_radio_regs(काष्ठा brcms_phy *pi,
			     स्थिर काष्ठा radio_regs *radioregs,
			     u16 core_offset);

व्योम wlc_phy_txघातer_ipa_upd(काष्ठा brcms_phy *pi);

व्योम wlc_phy_करो_dummy_tx(काष्ठा brcms_phy *pi, bool ofdm, bool pa_on);
व्योम wlc_phy_papd_decode_epsilon(u32 epsilon, s32 *eps_real, s32 *eps_imag);

व्योम wlc_phy_cal_perical_mphase_reset(काष्ठा brcms_phy *pi);
व्योम wlc_phy_cal_perical_mphase_restart(काष्ठा brcms_phy *pi);

bool wlc_phy_attach_nphy(काष्ठा brcms_phy *pi);
bool wlc_phy_attach_lcnphy(काष्ठा brcms_phy *pi);

व्योम wlc_phy_detach_lcnphy(काष्ठा brcms_phy *pi);

व्योम wlc_phy_init_nphy(काष्ठा brcms_phy *pi);
व्योम wlc_phy_init_lcnphy(काष्ठा brcms_phy *pi);

व्योम wlc_phy_cal_init_nphy(काष्ठा brcms_phy *pi);
व्योम wlc_phy_cal_init_lcnphy(काष्ठा brcms_phy *pi);

व्योम wlc_phy_chanspec_set_nphy(काष्ठा brcms_phy *pi, u16 chanspec);
व्योम wlc_phy_chanspec_set_lcnphy(काष्ठा brcms_phy *pi, u16 chanspec);
व्योम wlc_phy_chanspec_set_fixup_lcnphy(काष्ठा brcms_phy *pi, u16 chanspec);
पूर्णांक wlc_phy_channel2freq(uपूर्णांक channel);
पूर्णांक wlc_phy_chanspec_freq2bandrange_lpssn(uपूर्णांक);
पूर्णांक wlc_phy_chanspec_bandrange_get(काष्ठा brcms_phy *, u16 chanspec);

व्योम wlc_lcnphy_set_tx_pwr_ctrl(काष्ठा brcms_phy *pi, u16 mode);
s8 wlc_lcnphy_get_current_tx_pwr_idx(काष्ठा brcms_phy *pi);

व्योम wlc_phy_txघातer_recalc_target_nphy(काष्ठा brcms_phy *pi);
व्योम wlc_lcnphy_txघातer_recalc_target(काष्ठा brcms_phy *pi);
व्योम wlc_phy_txघातer_recalc_target_lcnphy(काष्ठा brcms_phy *pi);

व्योम wlc_lcnphy_set_tx_pwr_by_index(काष्ठा brcms_phy *pi, पूर्णांक index);
व्योम wlc_lcnphy_tx_pu(काष्ठा brcms_phy *pi, bool bEnable);
व्योम wlc_lcnphy_stop_tx_tone(काष्ठा brcms_phy *pi);
व्योम wlc_lcnphy_start_tx_tone(काष्ठा brcms_phy *pi, s32 f_kHz, u16 max_val,
			      bool iqcalmode);

व्योम wlc_phy_txघातer_sromlimit_get_nphy(काष्ठा brcms_phy *pi, uपूर्णांक chan,
					u8 *max_pwr, u8 rate_id);
व्योम wlc_phy_ofdm_to_mcs_घातers_nphy(u8 *घातer, u8 rate_mcs_start,
				     u8 rate_mcs_end, u8 rate_ofdm_start);
व्योम wlc_phy_mcs_to_ofdm_घातers_nphy(u8 *घातer, u8 rate_ofdm_start,
				     u8 rate_ofdm_end, u8 rate_mcs_start);

u16 wlc_lcnphy_tempsense(काष्ठा brcms_phy *pi, bool mode);
s16 wlc_lcnphy_tempsense_new(काष्ठा brcms_phy *pi, bool mode);
s8 wlc_lcnphy_tempsense_degree(काष्ठा brcms_phy *pi, bool mode);
s8 wlc_lcnphy_vbatsense(काष्ठा brcms_phy *pi, bool mode);
व्योम wlc_phy_carrier_suppress_lcnphy(काष्ठा brcms_phy *pi);
व्योम wlc_lcnphy_crsuprs(काष्ठा brcms_phy *pi, पूर्णांक channel);
व्योम wlc_lcnphy_epa_चयन(काष्ठा brcms_phy *pi, bool mode);
व्योम wlc_2064_vco_cal(काष्ठा brcms_phy *pi);

व्योम wlc_phy_txघातer_recalc_target(काष्ठा brcms_phy *pi);

#घोषणा LCNPHY_TBL_ID_PAPDCOMPDELTATBL	0x18
#घोषणा LCNPHY_TX_POWER_TABLE_SIZE	128
#घोषणा LCNPHY_MAX_TX_POWER_INDEX	(LCNPHY_TX_POWER_TABLE_SIZE - 1)
#घोषणा LCNPHY_TBL_ID_TXPWRCTL	0x07
#घोषणा LCNPHY_TX_PWR_CTRL_OFF	0
#घोषणा LCNPHY_TX_PWR_CTRL_SW		(0x1 << 15)
#घोषणा LCNPHY_TX_PWR_CTRL_HW         ((0x1 << 15) | \
					(0x1 << 14) | \
					(0x1 << 13))

#घोषणा LCNPHY_TX_PWR_CTRL_TEMPBASED	0xE001

व्योम wlc_lcnphy_ग_लिखो_table(काष्ठा brcms_phy *pi,
			    स्थिर काष्ठा phytbl_info *pti);
व्योम wlc_lcnphy_पढ़ो_table(काष्ठा brcms_phy *pi, काष्ठा phytbl_info *pti);
व्योम wlc_lcnphy_set_tx_iqcc(काष्ठा brcms_phy *pi, u16 a, u16 b);
व्योम wlc_lcnphy_set_tx_locc(काष्ठा brcms_phy *pi, u16 didq);
व्योम wlc_lcnphy_get_tx_iqcc(काष्ठा brcms_phy *pi, u16 *a, u16 *b);
u16 wlc_lcnphy_get_tx_locc(काष्ठा brcms_phy *pi);
व्योम wlc_lcnphy_get_radio_loft(काष्ठा brcms_phy *pi, u8 *ei0, u8 *eq0, u8 *fi0,
			       u8 *fq0);
व्योम wlc_lcnphy_calib_modes(काष्ठा brcms_phy *pi, uपूर्णांक mode);
व्योम wlc_lcnphy_deaf_mode(काष्ठा brcms_phy *pi, bool mode);
bool wlc_phy_tpc_isenabled_lcnphy(काष्ठा brcms_phy *pi);
व्योम wlc_lcnphy_tx_pwr_update_npt(काष्ठा brcms_phy *pi);
s32 wlc_lcnphy_tssi2dbm(s32 tssi, s32 a1, s32 b0, s32 b1);
व्योम wlc_lcnphy_get_tssi(काष्ठा brcms_phy *pi, s8 *ofdm_pwr, s8 *cck_pwr);
व्योम wlc_lcnphy_tx_घातer_adjusपंचांगent(काष्ठा brcms_phy_pub *ppi);

s32 wlc_lcnphy_rx_संकेत_घातer(काष्ठा brcms_phy *pi, s32 gain_index);

#घोषणा NPHY_MAX_HPVGA1_INDEX		10
#घोषणा NPHY_DEF_HPVGA1_INDEXLIMIT	7

काष्ठा phy_iq_est अणु
	s32 iq_prod;
	u32 i_pwr;
	u32 q_pwr;
पूर्ण;

व्योम wlc_phy_stay_in_carriersearch_nphy(काष्ठा brcms_phy *pi, bool enable);
व्योम wlc_nphy_deaf_mode(काष्ठा brcms_phy *pi, bool mode);

#घोषणा wlc_phy_ग_लिखो_table_nphy(pi, pti) \
	wlc_phy_ग_लिखो_table(pi, pti, 0x72, 0x74, 0x73)

#घोषणा wlc_phy_पढ़ो_table_nphy(pi, pti) \
	wlc_phy_पढ़ो_table(pi, pti, 0x72, 0x74, 0x73)

#घोषणा wlc_nphy_table_addr(pi, id, off) \
	wlc_phy_table_addr((pi), (id), (off), 0x72, 0x74, 0x73)

#घोषणा wlc_nphy_table_data_ग_लिखो(pi, w, v) \
	wlc_phy_table_data_ग_लिखो((pi), (w), (v))

व्योम wlc_phy_table_पढ़ो_nphy(काष्ठा brcms_phy *pi, u32, u32 l, u32 o, u32 w,
			     व्योम *d);
व्योम wlc_phy_table_ग_लिखो_nphy(काष्ठा brcms_phy *pi, u32, u32, u32, u32,
			      स्थिर व्योम *);

#घोषणा	PHY_IPA(pi) \
	((pi->ipa2g_on && CHSPEC_IS2G(pi->radio_chanspec)) || \
	 (pi->ipa5g_on && CHSPEC_IS5G(pi->radio_chanspec)))

#घोषणा BRCMS_PHY_WAR_PR51571(pi) \
	अगर (NREV_LT((pi)->pubpi.phy_rev, 3)) \
		(व्योम)bcma_पढ़ो32(pi->d11core, D11REGOFFS(maccontrol))

व्योम wlc_phy_cal_perical_nphy_run(काष्ठा brcms_phy *pi, u8 caltype);
व्योम wlc_phy_aci_reset_nphy(काष्ठा brcms_phy *pi);
व्योम wlc_phy_pa_override_nphy(काष्ठा brcms_phy *pi, bool en);

u8 wlc_phy_get_chan_freq_range_nphy(काष्ठा brcms_phy *pi, uपूर्णांक chan);
व्योम wlc_phy_चयन_radio_nphy(काष्ठा brcms_phy *pi, bool on);

व्योम wlc_phy_stf_chain_upd_nphy(काष्ठा brcms_phy *pi);

व्योम wlc_phy_क्रमce_rfseq_nphy(काष्ठा brcms_phy *pi, u8 cmd);
s16 wlc_phy_tempsense_nphy(काष्ठा brcms_phy *pi);

u16 wlc_phy_classअगरier_nphy(काष्ठा brcms_phy *pi, u16 mask, u16 val);

व्योम wlc_phy_rx_iq_est_nphy(काष्ठा brcms_phy *pi, काष्ठा phy_iq_est *est,
			    u16 num_samps, u8 रुको_समय, u8 रुको_क्रम_crs);

व्योम wlc_phy_rx_iq_coeffs_nphy(काष्ठा brcms_phy *pi, u8 ग_लिखो,
			       काष्ठा nphy_iq_comp *comp);
व्योम wlc_phy_aci_and_noise_reduction_nphy(काष्ठा brcms_phy *pi);

व्योम wlc_phy_rxcore_setstate_nphy(काष्ठा brcms_phy_pub *pih, u8 rxcore_biपंचांगask);
u8 wlc_phy_rxcore_माला_लोtate_nphy(काष्ठा brcms_phy_pub *pih);

व्योम wlc_phy_txpwrctrl_enable_nphy(काष्ठा brcms_phy *pi, u8 ctrl_type);
व्योम wlc_phy_txpwr_fixघातer_nphy(काष्ठा brcms_phy *pi);
व्योम wlc_phy_txpwr_apply_nphy(काष्ठा brcms_phy *pi);
व्योम wlc_phy_txpwr_papd_cal_nphy(काष्ठा brcms_phy *pi);
u16 wlc_phy_txpwr_idx_get_nphy(काष्ठा brcms_phy *pi);

काष्ठा nphy_txgains wlc_phy_get_tx_gain_nphy(काष्ठा brcms_phy *pi);
पूर्णांक wlc_phy_cal_txiqlo_nphy(काष्ठा brcms_phy *pi,
			    काष्ठा nphy_txgains target_gain, bool full, bool m);
पूर्णांक wlc_phy_cal_rxiq_nphy(काष्ठा brcms_phy *pi, काष्ठा nphy_txgains target_gain,
			  u8 type, bool d);
व्योम wlc_phy_txpwr_index_nphy(काष्ठा brcms_phy *pi, u8 core_mask,
			      s8 txpwrindex, bool res);
व्योम wlc_phy_rssisel_nphy(काष्ठा brcms_phy *pi, u8 core, u8 rssi_type);
पूर्णांक wlc_phy_poll_rssi_nphy(काष्ठा brcms_phy *pi, u8 rssi_type,
			   s32 *rssi_buf, u8 nsamps);
व्योम wlc_phy_rssi_cal_nphy(काष्ठा brcms_phy *pi);
पूर्णांक wlc_phy_aci_scan_nphy(काष्ठा brcms_phy *pi);
व्योम wlc_phy_cal_txgainctrl_nphy(काष्ठा brcms_phy *pi, s32 dBm_targetघातer,
				 bool debug);
पूर्णांक wlc_phy_tx_tone_nphy(काष्ठा brcms_phy *pi, u32 f_kHz, u16 max_val, u8 mode,
			 u8, bool);
व्योम wlc_phy_stopplayback_nphy(काष्ठा brcms_phy *pi);
व्योम wlc_phy_est_tonepwr_nphy(काष्ठा brcms_phy *pi, s32 *qdBm_pwrbuf,
			      u8 num_samps);
व्योम wlc_phy_radio205x_vcocal_nphy(काष्ठा brcms_phy *pi);

पूर्णांक wlc_phy_rssi_compute_nphy(काष्ठा brcms_phy *pi, काष्ठा d11rxhdr *rxh);

#घोषणा NPHY_TESTPATTERN_BPHY_EVM   0
#घोषणा NPHY_TESTPATTERN_BPHY_RFCS  1

व्योम wlc_phy_nphy_tkip_rअगरs_war(काष्ठा brcms_phy *pi, u8 rअगरs);

व्योम wlc_phy_get_pwrdet_offsets(काष्ठा brcms_phy *pi, s8 *cckoffset,
				s8 *ofdmoffset);
s8 wlc_phy_upd_rssi_offset(काष्ठा brcms_phy *pi, s8 rssi, u16 chanspec);

bool wlc_phy_n_txघातer_ipa_ison(काष्ठा brcms_phy *pih);
#पूर्ण_अगर				/* _BRCM_PHY_INT_H_ */
