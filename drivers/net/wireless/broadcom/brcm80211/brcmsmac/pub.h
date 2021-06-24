<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित _BRCM_PUB_H_
#घोषणा _BRCM_PUB_H_

#समावेश <linux/bcma/bcma.h>
#समावेश <brcmu_wअगरi.h>
#समावेश "types.h"
#समावेश "defs.h"

#घोषणा	BRCMS_NUMRATES	16	/* max # of rates in a rateset */

/* phy types */
#घोषणा	PHY_TYPE_A	0	/* Phy type A */
#घोषणा	PHY_TYPE_G	2	/* Phy type G */
#घोषणा	PHY_TYPE_N	4	/* Phy type N */
#घोषणा	PHY_TYPE_LP	5	/* Phy type Low Power A/B/G */
#घोषणा	PHY_TYPE_SSN	6	/* Phy type Single Stream N */
#घोषणा	PHY_TYPE_LCN	8	/* Phy type Single Stream N */
#घोषणा	PHY_TYPE_LCNXN	9	/* Phy type 2-stream N */
#घोषणा	PHY_TYPE_HT	7	/* Phy type 3-Stream N */

/* bw */
#घोषणा BRCMS_10_MHZ	10	/* 10Mhz nphy channel bandwidth */
#घोषणा BRCMS_20_MHZ	20	/* 20Mhz nphy channel bandwidth */
#घोषणा BRCMS_40_MHZ	40	/* 40Mhz nphy channel bandwidth */

#घोषणा	BRCMS_RSSI_MINVAL	-200	/* Low value, e.g. क्रम क्रमcing roam */
#घोषणा	BRCMS_RSSI_NO_SIGNAL	-91	/* NDIS RSSI link quality cutoffs */
#घोषणा	BRCMS_RSSI_VERY_LOW	-80	/* Very low quality cutoffs */
#घोषणा	BRCMS_RSSI_LOW		-70	/* Low quality cutoffs */
#घोषणा	BRCMS_RSSI_GOOD		-68	/* Good quality cutoffs */
#घोषणा	BRCMS_RSSI_VERY_GOOD	-58	/* Very good quality cutoffs */
#घोषणा	BRCMS_RSSI_EXCELLENT	-57	/* Excellent quality cutoffs */

/* a large TX Power as an init value to factor out of min() calculations,
 * keep low enough to fit in an s8, units are .25 dBm
 */
#घोषणा BRCMS_TXPWR_MAX		(127)	/* ~32 dBm = 1,500 mW */

/* rate related definitions */
#घोषणा	BRCMS_RATE_FLAG	0x80	/* Flag to indicate it is a basic rate */
#घोषणा	BRCMS_RATE_MASK	0x7f	/* Rate value mask w/o basic rate flag */

/* legacy rx Antenna भागersity क्रम SISO rates */
#घोषणा	ANT_RX_DIV_FORCE_0	0	/* Use antenna 0 */
#घोषणा	ANT_RX_DIV_FORCE_1	1	/* Use antenna 1 */
#घोषणा	ANT_RX_DIV_START_1	2	/* Choose starting with 1 */
#घोषणा	ANT_RX_DIV_START_0	3	/* Choose starting with 0 */
#घोषणा	ANT_RX_DIV_ENABLE	3	/* APHY bbConfig Enable RX Diversity */
/* शेष antभाग setting */
#घोषणा ANT_RX_DIV_DEF		ANT_RX_DIV_START_0

/* legacy rx Antenna भागersity क्रम SISO rates */
/* Tx on antenna 0, "legacy term Main" */
#घोषणा ANT_TX_FORCE_0		0
/* Tx on antenna 1, "legacy term Aux" */
#घोषणा ANT_TX_FORCE_1		1
/* Tx on phy's last good Rx antenna */
#घोषणा ANT_TX_LAST_RX		3
/* driver's शेष tx antenna setting */
#घोषणा ANT_TX_DEF		3

/* Tx Chain values */
/* def biपंचांगap of txchain */
#घोषणा TXCHAIN_DEF		0x1
/* शेष biपंचांगap of tx chains क्रम nphy */
#घोषणा TXCHAIN_DEF_NPHY	0x3
/* शेष biपंचांगap of tx chains क्रम nphy */
#घोषणा TXCHAIN_DEF_HTPHY	0x7
/* def biपंचांगap of rxchain */
#घोषणा RXCHAIN_DEF		0x1
/* शेष biपंचांगap of rx chains क्रम nphy */
#घोषणा RXCHAIN_DEF_NPHY	0x3
/* शेष biपंचांगap of rx chains क्रम nphy */
#घोषणा RXCHAIN_DEF_HTPHY	0x7
/* no antenna चयन */
#घोषणा ANTSWITCH_NONE		0
/* antenna चयन on 4321CB2, 2of3 */
#घोषणा ANTSWITCH_TYPE_1	1
/* antenna चयन on 4321MPCI, 2of3 */
#घोषणा ANTSWITCH_TYPE_2	2
/* antenna चयन on 4322, 2of3 */
#घोषणा ANTSWITCH_TYPE_3	3

#घोषणा RXBUFSZ		PKTBUFSZ

#घोषणा MAX_STREAMS_SUPPORTED	4	/* max number of streams supported */

काष्ठा brcm_rateset अणु
	/* # rates in this set */
	u32 count;
	/* rates in 500kbps units w/hi bit set अगर basic */
	u8 rates[WL_NUMRATES];
पूर्ण;

काष्ठा brcms_c_rateset अणु
	uपूर्णांक count;		/* number of rates in rates[] */
	 /* rates in 500kbps units w/hi bit set अगर basic */
	u8 rates[BRCMS_NUMRATES];
	u8 htphy_membership;	/* HT PHY Membership */
	u8 mcs[MCSSET_LEN];	/* supported mcs index bit map */
पूर्ण;

/* All the HT-specअगरic शेष advertised capabilities (including AMPDU)
 * should be grouped here at one place
 */
#घोषणा AMPDU_DEF_MPDU_DENSITY	6	/* शेष mpdu density (110 ==> 4us) */

/* wlc पूर्णांकernal bss_info */
काष्ठा brcms_bss_info अणु
	u8 BSSID[ETH_ALEN];	/* network BSSID */
	u16 flags;		/* flags क्रम पूर्णांकernal attributes */
	u8 SSID_len;		/* the length of SSID */
	u8 SSID[32];		/* SSID string */
	s16 RSSI;		/* receive संकेत strength (in dBm) */
	s16 SNR;		/* receive संकेत SNR in dB */
	u16 beacon_period;	/* units are Kusec */
	u16 chanspec;	/* Channel num, bw, ctrl_sb and band */
	काष्ठा brcms_c_rateset rateset;	/* supported rates */
पूर्ण;

#घोषणा MAC80211_PROMISC_BCNS	(1 << 0)
#घोषणा MAC80211_SCAN		(1 << 1)

/*
 * Public portion of common driver state काष्ठाure.
 * The wlc handle poपूर्णांकs at this.
 */
काष्ठा brcms_pub अणु
	काष्ठा brcms_c_info *wlc;
	काष्ठा ieee80211_hw *ieee_hw;
	काष्ठा scb_ampdu *global_ampdu;
	uपूर्णांक mac80211_state;
	uपूर्णांक unit;		/* device instance number */
	uपूर्णांक corerev;		/* core revision */
	काष्ठा si_pub *sih;	/* SI handle (cookie क्रम siutils calls) */
	bool up;		/* पूर्णांकerface up and running */
	bool hw_off;		/* HW is off */
	bool hw_up;		/* one समय hw up/करोwn */
	bool _piomode;		/* true अगर pio mode */
	uपूर्णांक _nbands;		/* # bands supported */
	uपूर्णांक now;		/* # elapsed seconds */

	bool delayed_करोwn;	/* करोwn delayed */
	bool associated;	/* true:part of [I]BSS, false: not */
	/* (जोड़ of stas_associated, aps_associated) */
	bool _ampdu;		/* ampdu enabled or not */
	u8 _n_enab;		/* biपंचांगap of 11N + HT support */

	u8 cur_etheraddr[ETH_ALEN];	/* our local ethernet address */

	u32 radio_disabled;	/* bit vector क्रम radio disabled reasons */

	u16 boardrev;	/* version # of particular board */
	u8 sromrev;		/* version # of the srom */
	अक्षर srom_ccode[BRCM_CNTRY_BUF_SZ];	/* Country Code in SROM */
	u32 boardflags;	/* Board specअगरic flags from srom */
	u32 boardflags2;	/* More board flags अगर sromrev >= 4 */
	bool phy_11ncapable;	/* the PHY/HW is capable of 802.11N */

	काष्ठा wl_cnt *_cnt;	/* low-level counters in driver */
	काष्ठा dentry *dbgfs_dir;
पूर्ण;

क्रमागत wlc_par_id अणु
	IOV_MPC = 1,
	IOV_RTSTHRESH,
	IOV_QTXPOWER,
	IOV_BCN_LI_BCN		/* Beacon listen पूर्णांकerval in # of beacons */
पूर्ण;

/***********************************************
 * Feature-related macros to optimize out code *
 * *********************************************
 */

#घोषणा ENAB_1x1	0x01
#घोषणा ENAB_2x2	0x02
#घोषणा ENAB_3x3	0x04
#घोषणा ENAB_4x4	0x08
#घोषणा SUPPORT_11N	(ENAB_1x1|ENAB_2x2)
#घोषणा SUPPORT_HT	(ENAB_1x1|ENAB_2x2|ENAB_3x3)

/* WL11N Support */
#घोषणा AMPDU_AGG_HOST	1

/* network protection config */
#घोषणा	BRCMS_PROT_G_SPEC		1	/* SPEC g protection */
#घोषणा	BRCMS_PROT_G_OVR		2	/* SPEC g prot override */
#घोषणा	BRCMS_PROT_G_USER		3	/* gmode specअगरied by user */
#घोषणा	BRCMS_PROT_OVERLAP	4	/* overlap */
#घोषणा	BRCMS_PROT_N_USER		10	/* nmode specअगरied by user */
#घोषणा	BRCMS_PROT_N_CFG		11	/* n protection */
#घोषणा	BRCMS_PROT_N_CFG_OVR	12	/* n protection override */
#घोषणा	BRCMS_PROT_N_NONGF	13	/* non-GF protection */
#घोषणा	BRCMS_PROT_N_NONGF_OVR	14	/* non-GF protection override */
#घोषणा	BRCMS_PROT_N_PAM_OVR	15	/* n preamble override */
#घोषणा	BRCMS_PROT_N_OBSS		16	/* non-HT OBSS present */

/*
 * 54g modes (basic bits may still be overridden)
 *
 * GMODE_LEGACY_B
 *	Rateset: 1b, 2b, 5.5, 11
 *	Preamble: Long
 *	Shortslot: Off
 * GMODE_AUTO
 *	Rateset: 1b, 2b, 5.5b, 11b, 18, 24, 36, 54
 *	Extended Rateset: 6, 9, 12, 48
 *	Preamble: Long
 *	Shortslot: Auto
 * GMODE_ONLY
 *	Rateset: 1b, 2b, 5.5b, 11b, 18, 24b, 36, 54
 *	Extended Rateset: 6b, 9, 12b, 48
 *	Preamble: Short required
 *	Shortslot: Auto
 * GMODE_B_DEFERRED
 *	Rateset: 1b, 2b, 5.5b, 11b, 18, 24, 36, 54
 *	Extended Rateset: 6, 9, 12, 48
 *	Preamble: Long
 *	Shortslot: On
 * GMODE_PERFORMANCE
 *	Rateset: 1b, 2b, 5.5b, 6b, 9, 11b, 12b, 18, 24b, 36, 48, 54
 *	Preamble: Short required
 *	Shortslot: On and required
 * GMODE_LRS
 *	Rateset: 1b, 2b, 5.5b, 11b
 *	Extended Rateset: 6, 9, 12, 18, 24, 36, 48, 54
 *	Preamble: Long
 *	Shortslot: Auto
 */
#घोषणा GMODE_LEGACY_B		0
#घोषणा GMODE_AUTO		1
#घोषणा GMODE_ONLY		2
#घोषणा GMODE_B_DEFERRED	3
#घोषणा GMODE_PERFORMANCE	4
#घोषणा GMODE_LRS		5
#घोषणा GMODE_MAX		6

/* MCS values greater than this enable multiple streams */
#घोषणा HIGHEST_SINGLE_STREAM_MCS	7

#घोषणा	MAXBANDS		2	/* Maximum #of bands */

/* max number of antenna configurations */
#घोषणा ANT_SELCFG_MAX		4

काष्ठा brcms_antselcfg अणु
	u8 ant_config[ANT_SELCFG_MAX];	/* antenna configuration */
	u8 num_antcfg;	/* number of available antenna configurations */
पूर्ण;

/* common functions क्रम every port */
काष्ठा brcms_c_info *brcms_c_attach(काष्ठा brcms_info *wl,
				    काष्ठा bcma_device *core, uपूर्णांक unit,
				    bool piomode, uपूर्णांक *perr);
uपूर्णांक brcms_c_detach(काष्ठा brcms_c_info *wlc);
पूर्णांक brcms_c_up(काष्ठा brcms_c_info *wlc);
uपूर्णांक brcms_c_करोwn(काष्ठा brcms_c_info *wlc);

bool brcms_c_chipmatch(काष्ठा bcma_device *core);
व्योम brcms_c_init(काष्ठा brcms_c_info *wlc, bool mute_tx);
व्योम brcms_c_reset(काष्ठा brcms_c_info *wlc);

व्योम brcms_c_पूर्णांकrson(काष्ठा brcms_c_info *wlc);
u32 brcms_c_पूर्णांकrsoff(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_पूर्णांकrsrestore(काष्ठा brcms_c_info *wlc, u32 macपूर्णांकmask);
bool brcms_c_पूर्णांकrsupd(काष्ठा brcms_c_info *wlc);
bool brcms_c_isr(काष्ठा brcms_c_info *wlc);
bool brcms_c_dpc(काष्ठा brcms_c_info *wlc, bool bounded);
bool brcms_c_sendpkt_mac80211(काष्ठा brcms_c_info *wlc, काष्ठा sk_buff *sdu,
			      काष्ठा ieee80211_hw *hw);
bool brcms_c_aggregatable(काष्ठा brcms_c_info *wlc, u8 tid);
व्योम brcms_c_protection_upd(काष्ठा brcms_c_info *wlc, uपूर्णांक idx, पूर्णांक val);
पूर्णांक brcms_c_get_header_len(व्योम);
व्योम brcms_c_set_addrmatch(काष्ठा brcms_c_info *wlc, पूर्णांक match_reg_offset,
			   स्थिर u8 *addr);
व्योम brcms_c_wme_setparams(काष्ठा brcms_c_info *wlc, u16 aci,
			   स्थिर काष्ठा ieee80211_tx_queue_params *arg,
			   bool suspend);
काष्ठा brcms_pub *brcms_c_pub(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_ampdu_flush(काष्ठा brcms_c_info *wlc, काष्ठा ieee80211_sta *sta,
			 u16 tid);
व्योम brcms_c_ampdu_tx_operational(काष्ठा brcms_c_info *wlc, u8 tid,
				  u8 ba_wsize, uपूर्णांक max_rx_ampdu_bytes);
पूर्णांक brcms_c_module_रेजिस्टर(काष्ठा brcms_pub *pub, स्थिर अक्षर *name,
			    काष्ठा brcms_info *hdl,
			    पूर्णांक (*करोwn_fn)(व्योम *handle));
पूर्णांक brcms_c_module_unरेजिस्टर(काष्ठा brcms_pub *pub, स्थिर अक्षर *name,
			      काष्ठा brcms_info *hdl);
व्योम brcms_c_suspend_mac_and_रुको(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_enable_mac(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_associate_upd(काष्ठा brcms_c_info *wlc, bool state);
व्योम brcms_c_scan_start(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_scan_stop(काष्ठा brcms_c_info *wlc);
पूर्णांक brcms_c_get_curband(काष्ठा brcms_c_info *wlc);
पूर्णांक brcms_c_set_channel(काष्ठा brcms_c_info *wlc, u16 channel);
पूर्णांक brcms_c_set_rate_limit(काष्ठा brcms_c_info *wlc, u16 srl, u16 lrl);
व्योम brcms_c_get_current_rateset(काष्ठा brcms_c_info *wlc,
				 काष्ठा brcm_rateset *currs);
पूर्णांक brcms_c_set_rateset(काष्ठा brcms_c_info *wlc, काष्ठा brcm_rateset *rs);
पूर्णांक brcms_c_set_beacon_period(काष्ठा brcms_c_info *wlc, u16 period);
u16 brcms_c_get_phy_type(काष्ठा brcms_c_info *wlc, पूर्णांक phyidx);
व्योम brcms_c_set_लघुslot_override(काष्ठा brcms_c_info *wlc,
				    s8 sslot_override);
व्योम brcms_c_set_beacon_listen_पूर्णांकerval(काष्ठा brcms_c_info *wlc, u8 पूर्णांकerval);
u64 brcms_c_tsf_get(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_tsf_set(काष्ठा brcms_c_info *wlc, u64 tsf);
पूर्णांक brcms_c_set_tx_घातer(काष्ठा brcms_c_info *wlc, पूर्णांक txpwr);
पूर्णांक brcms_c_get_tx_घातer(काष्ठा brcms_c_info *wlc);
bool brcms_c_check_radio_disabled(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_mute(काष्ठा brcms_c_info *wlc, bool on);
bool brcms_c_tx_flush_completed(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_start_station(काष्ठा brcms_c_info *wlc, u8 *addr);
व्योम brcms_c_start_ap(काष्ठा brcms_c_info *wlc, u8 *addr, स्थिर u8 *bssid,
		      u8 *ssid, माप_प्रकार ssid_len);
व्योम brcms_c_start_adhoc(काष्ठा brcms_c_info *wlc, u8 *addr);
व्योम brcms_c_update_beacon(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_set_new_beacon(काष्ठा brcms_c_info *wlc, काष्ठा sk_buff *beacon,
			    u16 tim_offset, u16 dtim_period);
व्योम brcms_c_set_new_probe_resp(काष्ठा brcms_c_info *wlc,
				काष्ठा sk_buff *probe_resp);
व्योम brcms_c_enable_probe_resp(काष्ठा brcms_c_info *wlc, bool enable);
व्योम brcms_c_set_ssid(काष्ठा brcms_c_info *wlc, u8 *ssid, माप_प्रकार ssid_len);

#पूर्ण_अगर				/* _BRCM_PUB_H_ */
