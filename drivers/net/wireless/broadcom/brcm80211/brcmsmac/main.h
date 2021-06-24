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

#अगर_अघोषित _BRCM_MAIN_H_
#घोषणा _BRCM_MAIN_H_

#समावेश <linux/etherdevice.h>

#समावेश <brcmu_utils.h>
#समावेश "types.h"
#समावेश "d11.h"
#समावेश "scb.h"

#घोषणा	INVCHANNEL		255	/* invalid channel */

/* max # brcms_c_module_रेजिस्टर() calls */
#घोषणा BRCMS_MAXMODULES	22

#घोषणा SEQNUM_SHIFT		4
#घोषणा SEQNUM_MAX		0x1000

#घोषणा NTXRATE			64	/* # tx MPDUs rate is reported क्रम */

/* Maximum रुको समय क्रम a MAC suspend */
/* uS: 83mS is max packet समय (64KB ampdu @ 6Mbps) */
#घोषणा	BRCMS_MAX_MAC_SUSPEND	83000

/* responses क्रम probe requests older that this are tossed, zero to disable */
#घोषणा BRCMS_PRB_RESP_TIMEOUT	0	/* Disable probe response समयout */

/* transmit buffer max headroom क्रम protocol headers */
#घोषणा TXOFF (D11_TXH_LEN + D11_PHY_HDR_LEN)

/* Macros क्रम करोing definition and get/set of bitfields
 * Usage example, e.g. a three-bit field (bits 4-6):
 *    #घोषणा <NAME>_M	BITFIELD_MASK(3)
 *    #घोषणा <NAME>_S	4
 * ...
 *    regval = R_REG(osh, &regs->regfoo);
 *    field = GFIELD(regval, <NAME>);
 *    regval = SFIELD(regval, <NAME>, 1);
 *    W_REG(osh, &regs->regfoo, regval);
 */
#घोषणा BITFIELD_MASK(width) \
		(((अचिन्हित)1 << (width)) - 1)
#घोषणा GFIELD(val, field) \
		(((val) >> field ## _S) & field ## _M)
#घोषणा SFIELD(val, field, bits) \
		(((val) & (~(field ## _M << field ## _S))) | \
		 ((अचिन्हित)(bits) << field ## _S))

#घोषणा	SW_TIMER_MAC_STAT_UPD		30	/* periodic MAC stats update */

/* max # supported core revisions (0 .. MAXCOREREV - 1) */
#घोषणा	MAXCOREREV		28

/* Double check that unsupported cores are not enabled */
#अगर CONF_MSK(D11CONF, 0x4f) || CONF_GE(D11CONF, MAXCOREREV)
#त्रुटि "Configuration for D11CONF includes unsupported versions."
#पूर्ण_अगर				/* Bad versions */

/* values क्रम लघुslot_override */
#घोषणा BRCMS_SHORTSLOT_AUTO	-1 /* Driver will manage Shortslot setting */
#घोषणा BRCMS_SHORTSLOT_OFF	0  /* Turn off लघु slot */
#घोषणा BRCMS_SHORTSLOT_ON	1  /* Turn on लघु slot */

/* value क्रम लघु/दीर्घ and mixmode/greenfield preamble */
#घोषणा BRCMS_LONG_PREAMBLE	(0)
#घोषणा BRCMS_SHORT_PREAMBLE	(1 << 0)
#घोषणा BRCMS_GF_PREAMBLE		(1 << 1)
#घोषणा BRCMS_MM_PREAMBLE		(1 << 2)
#घोषणा BRCMS_IS_MIMO_PREAMBLE(_pre) (((_pre) == BRCMS_GF_PREAMBLE) || \
				      ((_pre) == BRCMS_MM_PREAMBLE))

/* TxFrameID */
/* seq and frag bits: SEQNUM_SHIFT, FRAGNUM_MASK (802.11.h) */
/* rate epoch bits: TXFID_RATE_SHIFT, TXFID_RATE_MASK ((wlc_rate.c) */
#घोषणा TXFID_QUEUE_MASK	0x0007	/* Bits 0-2 */
#घोषणा TXFID_SEQ_MASK		0x7FE0	/* Bits 5-15 */
#घोषणा TXFID_SEQ_SHIFT		5	/* Number of bit shअगरts */
#घोषणा	TXFID_RATE_PROBE_MASK	0x8000	/* Bit 15 क्रम rate probe */
#घोषणा TXFID_RATE_MASK		0x0018	/* Mask क्रम bits 3 and 4 */
#घोषणा TXFID_RATE_SHIFT	3	/* Shअगरt 3 bits क्रम rate mask */

/* promote boardrev */
#घोषणा BOARDREV_PROMOTABLE	0xFF	/* from */
#घोषणा BOARDREV_PROMOTED	1	/* to */

#घोषणा DATA_BLOCK_TX_SUPR	(1 << 4)

/* Ucode MCTL_WAKE override bits */
#घोषणा BRCMS_WAKE_OVERRIDE_CLKCTL	0x01
#घोषणा BRCMS_WAKE_OVERRIDE_PHYREG	0x02
#घोषणा BRCMS_WAKE_OVERRIDE_MACSUSPEND	0x04
#घोषणा BRCMS_WAKE_OVERRIDE_TXFIFO	0x08
#घोषणा BRCMS_WAKE_OVERRIDE_FORCEFAST	0x10

/* stuff pulled in from wlc.c */

/* Interrupt bit error summary.  Don't include I_RU: we refill DMA at other
 * बार; and अगर we run out, स्थिरant I_RU पूर्णांकerrupts may cause lockup.  We
 * will still get error counts from rx0ovfl.
 */
#घोषणा	I_ERRORS	(I_PC | I_PD | I_DE | I_RO | I_XU)
/* शेष software पूर्णांकmasks */
#घोषणा	DEF_RXINTMASK	(I_RI)	/* enable rx पूर्णांक on rxfअगरo only */
#घोषणा	DEF_MACINTMASK	(MI_TXSTOP | MI_TBTT | MI_ATIMWINEND | MI_PMQ | \
			 MI_PHYTXERR | MI_DMAINT | MI_TFS | MI_BG_NOISE | \
			 MI_CCA | MI_TO | MI_GP0 | MI_RFDISABLE | MI_PWRUP)

#घोषणा	MAXTXPKTS		6	/* max # pkts pending */

/* frameburst */
#घोषणा	MAXTXFRAMEBURST		8 /* vanilla xpress mode: max frames/burst */
#घोषणा	MAXFRAMEBURST_TXOP	10000	/* Frameburst TXOP in usec */

#घोषणा	NFIFO			6	/* # tx/rx fअगरopairs */

/* PLL requests */

/* pll is shared on old chips */
#घोषणा BRCMS_PLLREQ_SHARED	0x1
/* hold pll क्रम radio monitor रेजिस्टर checking */
#घोषणा BRCMS_PLLREQ_RADIO_MON	0x2
/* hold/release pll क्रम some लघु operation */
#घोषणा BRCMS_PLLREQ_FLIP		0x4

#घोषणा	CHANNEL_BANDUNIT(wlc, ch) \
	(((ch) <= CH_MAX_2G_CHANNEL) ? BAND_2G_INDEX : BAND_5G_INDEX)

#घोषणा	OTHERBANDUNIT(wlc) \
	((uपूर्णांक)((wlc)->band->bandunit ? BAND_2G_INDEX : BAND_5G_INDEX))

/*
 * 802.11 protection inक्रमmation
 *
 * _g: use g spec protection, driver पूर्णांकernal.
 * g_override: override क्रम use of g spec protection.
 * gmode_user: user config gmode, operating band->gmode is dअगरferent.
 * overlap: Overlap BSS/IBSS protection क्रम both 11g and 11n.
 * nmode_user: user config nmode, operating pub->nmode is dअगरferent.
 * n_cfg: use OFDM protection on MIMO frames.
 * n_cfg_override: override क्रम use of N protection.
 * nongf: non-GF present protection.
 * nongf_override: override क्रम use of GF protection.
 * n_pam_override: override क्रम preamble: MM or GF.
 * n_obss: indicated OBSS Non-HT STA present.
*/
काष्ठा brcms_protection अणु
	bool _g;
	s8 g_override;
	u8 gmode_user;
	s8 overlap;
	s8 nmode_user;
	s8 n_cfg;
	s8 n_cfg_override;
	bool nongf;
	s8 nongf_override;
	s8 n_pam_override;
	bool n_obss;
पूर्ण;

/*
 * anything affecting the single/dual streams/antenna operation
 *
 * hw_txchain: HW txchain biपंचांगap cfg.
 * txchain: txchain biपंचांगap being used.
 * txstreams: number of txchains being used.
 * hw_rxchain: HW rxchain biपंचांगap cfg.
 * rxchain: rxchain biपंचांगap being used.
 * rxstreams: number of rxchains being used.
 * ant_rx_ovr: rx antenna override.
 * txant: userTx antenna setting.
 * phytxant: phyTx antenna setting in txheader.
 * ss_opmode: singlestream Operational mode, 0:siso; 1:cdd.
 * ss_algosel_स्वतः: अगर true, use wlc->stf->ss_algo_channel;
 *			अन्यथा use wlc->band->stf->ss_mode_band.
 * ss_algo_channel: ss based on per-channel algo: 0: SISO, 1: CDD 2: STBC.
 * rxchain_restore_delay: delay समय to restore शेष rxchain.
 * ldpc: AUTO/ON/OFF ldpc cap supported.
 * txcore[MAX_STREAMS_SUPPORTED + 1]: biपंचांगap of selected core क्रम each Nsts.
 * spatial_policy:
 */
काष्ठा brcms_stf अणु
	u8 hw_txchain;
	u8 txchain;
	u8 txstreams;
	u8 hw_rxchain;
	u8 rxchain;
	u8 rxstreams;
	u8 ant_rx_ovr;
	s8 txant;
	u16 phytxant;
	u8 ss_opmode;
	bool ss_algosel_स्वतः;
	u16 ss_algo_channel;
	u8 rxchain_restore_delay;
	s8 ldpc;
	u8 txcore[MAX_STREAMS_SUPPORTED + 1];
	s8 spatial_policy;
पूर्ण;

#घोषणा BRCMS_STF_SS_STBC_TX(wlc, scb) \
	(((wlc)->stf->txstreams > 1) && (((wlc)->band->band_stf_stbc_tx == ON) \
	 || (((scb)->flags & SCB_STBCCAP) && \
	     (wlc)->band->band_stf_stbc_tx == AUTO && \
	     isset(&((wlc)->stf->ss_algo_channel), PHY_TXC1_MODE_STBC))))

#घोषणा BRCMS_STBC_CAP_PHY(wlc) (BRCMS_ISNPHY(wlc->band) && \
				 NREV_GE(wlc->band->phyrev, 3))

#घोषणा BRCMS_SGI_CAP_PHY(wlc) ((BRCMS_ISNPHY(wlc->band) && \
				 NREV_GE(wlc->band->phyrev, 3)) || \
				BRCMS_ISLCNPHY(wlc->band))

#घोषणा BRCMS_CHAN_PHYTYPE(x)     (((x) & RXS_CHAN_PHYTYPE_MASK) \
				   >> RXS_CHAN_PHYTYPE_SHIFT)
#घोषणा BRCMS_CHAN_CHANNEL(x)     (((x) & RXS_CHAN_ID_MASK) \
				   >> RXS_CHAN_ID_SHIFT)

/*
 * core state (mac)
 */
काष्ठा brcms_core अणु
	uपूर्णांक coreidx;		/* # sb क्रमागतerated core */

	/* fअगरo */
	uपूर्णांक *txavail[NFIFO];	/* # tx descriptors available */

	काष्ठा macstat *macstat_snapshot;	/* mac hw prev पढ़ो values */
पूर्ण;

/*
 * band state (phy+ana+radio)
 */
काष्ठा brcms_band अणु
	पूर्णांक bandtype;		/* BRCM_BAND_2G, BRCM_BAND_5G */
	uपूर्णांक bandunit;		/* bandstate[] index */

	u16 phytype;		/* phytype */
	u16 phyrev;
	u16 radioid;
	u16 radiorev;
	काष्ठा brcms_phy_pub *pi; /* poपूर्णांकer to phy specअगरic inक्रमmation */
	bool abgphy_encore;

	u8 gmode;		/* currently active gmode */

	काष्ठा scb *hwrs_scb;	/* permanent scb क्रम hw rateset */

	/* band-specअगरic copy of शेष_bss.rateset */
	काष्ठा brcms_c_rateset defrateset;

	u8 band_stf_ss_mode;	/* Configured STF type, 0:siso; 1:cdd */
	s8 band_stf_stbc_tx;	/* STBC TX 0:off; 1:क्रमce on; -1:स्वतः */
	/* rates supported by chip (phy-specअगरic) */
	काष्ठा brcms_c_rateset hw_rateset;
	u8 basic_rate[BRCM_MAXRATE + 1]; /* basic rates indexed by rate */
	bool mimo_cap_40;	/* 40 MHz cap enabled on this band */
	s8 antgain;		/* antenna gain from srom */

	u16 CWmin; /* minimum size of contention winकरोw, in unit of aSlotTime */
	u16 CWmax; /* maximum size of contention winकरोw, in unit of aSlotTime */
	काष्ठा ieee80211_supported_band band;
पूर्ण;

/* module control blocks */
काष्ठा modulecb अणु
	/* module name : शून्य indicates empty array member */
	अक्षर name[32];
	/* handle passed when handler 'doiovar' is called */
	काष्ठा brcms_info *hdl;

	पूर्णांक (*करोwn_fn)(व्योम *handle); /* करोwn handler. Note: the पूर्णांक वापसed
				       * by the करोwn function is a count of the
				       * number of समयrs that could not be
				       * मुक्तd.
				       */

पूर्ण;

काष्ठा brcms_hw_band अणु
	पूर्णांक bandtype;		/* BRCM_BAND_2G, BRCM_BAND_5G */
	uपूर्णांक bandunit;		/* bandstate[] index */
	u16 mhfs[MHFMAX];	/* MHF array shaकरोw */
	u8 bandhw_stf_ss_mode;	/* HW configured STF type, 0:siso; 1:cdd */
	u16 CWmin;
	u16 CWmax;
	u32 core_flags;

	u16 phytype;		/* phytype */
	u16 phyrev;
	u16 radioid;
	u16 radiorev;
	काष्ठा brcms_phy_pub *pi; /* poपूर्णांकer to phy specअगरic inक्रमmation */
	bool abgphy_encore;
पूर्ण;

काष्ठा brcms_hardware अणु
	bool _piomode;		/* true अगर pio mode */
	काष्ठा brcms_c_info *wlc;

	/* fअगरo */
	काष्ठा dma_pub *di[NFIFO];	/* dma handles, per fअगरo */

	uपूर्णांक unit;		/* device instance number */

	/* version info */
	u16 venकरोrid;	/* PCI venकरोr id */
	u16 deviceid;	/* PCI device id */
	uपूर्णांक corerev;		/* core revision */
	u8 sromrev;		/* version # of the srom */
	u16 boardrev;	/* version # of particular board */
	u32 boardflags;	/* Board specअगरic flags from srom */
	u32 boardflags2;	/* More board flags अगर sromrev >= 4 */
	u32 machwcap;	/* MAC capabilities */
	u32 machwcap_backup;	/* backup of machwcap */

	काष्ठा si_pub *sih;	/* SI handle (cookie क्रम siutils calls) */
	काष्ठा bcma_device *d11core;	/* poपूर्णांकer to 802.11 core */
	काष्ठा phy_shim_info *physhim; /* phy shim layer handler */
	काष्ठा shared_phy *phy_sh;	/* poपूर्णांकer to shared phy state */
	काष्ठा brcms_hw_band *band;/* poपूर्णांकer to active per-band state */
	/* band state per phy/radio */
	काष्ठा brcms_hw_band *bandstate[MAXBANDS];
	u16 bmac_phytxant;	/* cache of high phytxant state */
	bool लघुslot;		/* currently using 11g ShortSlot timing */
	u16 SRL;		/* 802.11 करोt11ShortRetryLimit */
	u16 LRL;		/* 802.11 करोt11LongRetryLimit */
	u16 SFBL;		/* Short Frame Rate Fallback Limit */
	u16 LFBL;		/* Long Frame Rate Fallback Limit */

	bool up;		/* d11 hardware up and running */
	uपूर्णांक now;		/* # elapsed seconds */
	uपूर्णांक _nbands;		/* # bands supported */
	u16 chanspec;	/* bmac chanspec shaकरोw */

	uपूर्णांक *txavail[NFIFO];	/* # tx descriptors available */
	स्थिर u16 *xmtfअगरo_sz;	/* fअगरo size in 256B क्रम each xmt fअगरo */

	u32 pllreq;		/* pll requests to keep PLL on */

	u8 suspended_fअगरos;	/* Which TX fअगरo to reमुख्य awake क्रम */
	u32 maccontrol;	/* Cached value of maccontrol */
	uपूर्णांक mac_suspend_depth;	/* current depth of mac_suspend levels */
	u32 wake_override;	/* bit flags to क्रमce MAC to WAKE mode */
	u32 mute_override;	/* Prevent ucode from sending beacons */
	u8 etheraddr[ETH_ALEN];	/* currently configured ethernet address */
	bool noreset;		/* true= करो not reset hw, used by WLC_OUT */
	bool क्रमcefastclk;	/* true अगर h/w is क्रमcing to use fast clk */
	bool clk;		/* core is out of reset and has घड़ी */
	bool sbclk;		/* sb has घड़ी */
	bool phyclk;		/* phy is out of reset and has घड़ी */

	bool ucode_loaded;	/* true after ucode करोwnloaded */


	u8 hw_stf_ss_opmode;	/* STF single stream operation mode */
	u8 antsel_type;	/* Type of boardlevel mimo antenna चयन-logic
				 * 0 = N/A, 1 = 2x4 board, 2 = 2x3 CB2 board
				 */
	u32 antsel_avail;	/*
				 * put काष्ठा antsel_info here अगर more info is
				 * needed
				 */
पूर्ण;

/*
 * Principal common driver data काष्ठाure.
 *
 * pub: poपूर्णांकer to driver खुला state.
 * wl: poपूर्णांकer to specअगरic निजी state.
 * hw: HW related state.
 * clkreq_override: setting क्रम clkreq क्रम PCIE : Auto, 0, 1.
 * fastpwrup_dly: समय in us needed to bring up d11 fast घड़ी.
 * macपूर्णांकstatus: bit channel between isr and dpc.
 * macपूर्णांकmask: sw runसमय master macपूर्णांकmask value.
 * defmacपूर्णांकmask: शेष "on" macपूर्णांकmask value.
 * clk: core is out of reset and has घड़ी.
 * core: poपूर्णांकer to active io core.
 * band: poपूर्णांकer to active per-band state.
 * corestate: per-core state (one per hw core).
 * bandstate: per-band state (one per phy/radio).
 * qvalid: DirFrmQValid and BcMcFrmQValid.
 * ampdu: ampdu module handler.
 * asi: antsel module handler.
 * cmi: channel manager module handler.
 * venकरोrid: PCI venकरोr id.
 * deviceid: PCI device id.
 * ucode_rev: microcode revision.
 * machwcap: MAC capabilities, BMAC shaकरोw.
 * perm_etheraddr: original sprom local ethernet address.
 * bandlocked: disable स्वतः multi-band चयनing.
 * bandinit_pending: track band init in स्वतः band.
 * radio_monitor: radio समयr is running.
 * going_करोwn: करोwn path पूर्णांकermediate variable.
 * wdसमयr: समयr क्रम watchकरोg routine.
 * radio_समयr: समयr क्रम hw radio button monitor routine.
 * monitor: monitor (MPDU snअगरfing) mode.
 * bcnmisc_monitor: bcns promisc mode override क्रम monitor.
 * _rअगरs: enable per-packet rअगरs.
 * bcn_li_bcn: beacon listen पूर्णांकerval in # beacons.
 * bcn_li_dtim: beacon listen पूर्णांकerval in # dtims.
 * WDarmed: watchकरोg समयr is armed.
 * WDlast: last समय wlc_watchकरोg() was called.
 * edcf_txop[IEEE80211_NUM_ACS]: current txop क्रम each ac.
 * wme_retries: per-AC retry limits.
 * bsscfg: set of BSS configurations, idx 0 is शेष and always valid.
 * cfg: the primary bsscfg (can be AP or STA).
 * modulecb:
 * mimoft: SIGN or 11N.
 * cck_40txbw: 11N, cck tx b/w override when in 40MHZ mode.
 * ofdm_40txbw: 11N, ofdm tx b/w override when in 40MHZ mode.
 * mimo_40txbw: 11N, mimo tx b/w override when in 40MHZ mode.
 * शेष_bss: configured BSS parameters.
 * mc_fid_counter: BC/MC FIFO frame ID counter.
 * country_शेष: saved country क्रम leaving 802.11d स्वतः-country mode.
 * स्वतःcountry_शेष: initial country क्रम 802.11d स्वतः-country mode.
 * prb_resp_समयout: करो not send prb resp अगर request older
 *		     than this, 0 = disable.
 * home_chanspec: shared home chanspec.
 * chanspec: target operational channel.
 * usr_fragthresh: user configured fragmentation threshold.
 * fragthresh[NFIFO]: per-fअगरo fragmentation thresholds.
 * RTSThresh: 802.11 करोt11RTSThreshold.
 * SRL: 802.11 करोt11ShortRetryLimit.
 * LRL: 802.11 करोt11LongRetryLimit.
 * SFBL: Short Frame Rate Fallback Limit.
 * LFBL: Long Frame Rate Fallback Limit.
 * लघुslot: currently using 11g ShortSlot timing.
 * लघुslot_override: 11g ShortSlot override.
 * include_legacy_erp: include Legacy ERP info elt ID 47 as well as g ID 42.
 * PLCPHdr_override: 802.11b Preamble Type override.
 * stf:
 * bcn_rspec: save bcn ratespec purpose.
 * tempsense_lastसमय;
 * tx_duty_cycle_ofdm: maximum allowed duty cycle क्रम OFDM.
 * tx_duty_cycle_cck: maximum allowed duty cycle क्रम CCK.
 * wiphy:
 * pri_scb: primary Station Control Block
 */
काष्ठा brcms_c_info अणु
	काष्ठा brcms_pub *pub;
	काष्ठा brcms_info *wl;
	काष्ठा brcms_hardware *hw;

	/* घड़ी */
	u16 fastpwrup_dly;

	/* पूर्णांकerrupt */
	u32 macपूर्णांकstatus;
	u32 macपूर्णांकmask;
	u32 defmacपूर्णांकmask;

	bool clk;

	/* multiband */
	काष्ठा brcms_core *core;
	काष्ठा brcms_band *band;
	काष्ठा brcms_core *corestate;
	काष्ठा brcms_band *bandstate[MAXBANDS];

	/* packet queue */
	uपूर्णांक qvalid;

	काष्ठा ampdu_info *ampdu;
	काष्ठा antsel_info *asi;
	काष्ठा brcms_cm_info *cmi;

	u16 venकरोrid;
	u16 deviceid;
	uपूर्णांक ucode_rev;

	u8 perm_etheraddr[ETH_ALEN];

	bool bandlocked;
	bool bandinit_pending;

	bool radio_monitor;
	bool going_करोwn;

	bool beacon_ढाँचा_virgin;

	काष्ठा brcms_समयr *wdसमयr;
	काष्ठा brcms_समयr *radio_समयr;

	/* promiscuous */
	uपूर्णांक filter_flags;

	/* driver feature */
	bool _rअगरs;

	/* AP-STA synchronization, घातer save */
	u8 bcn_li_bcn;
	u8 bcn_li_dtim;

	bool WDarmed;
	u32 WDlast;

	/* WME */
	u16 edcf_txop[IEEE80211_NUM_ACS];

	u16 wme_retries[IEEE80211_NUM_ACS];

	काष्ठा brcms_bss_cfg *bsscfg;

	काष्ठा modulecb *modulecb;

	u8 mimoft;
	s8 cck_40txbw;
	s8 ofdm_40txbw;
	s8 mimo_40txbw;

	काष्ठा brcms_bss_info *शेष_bss;

	u16 mc_fid_counter;

	अक्षर country_शेष[BRCM_CNTRY_BUF_SZ];
	अक्षर स्वतःcountry_शेष[BRCM_CNTRY_BUF_SZ];
	u16 prb_resp_समयout;

	u16 home_chanspec;

	/* PHY parameters */
	u16 chanspec;
	u16 usr_fragthresh;
	u16 fragthresh[NFIFO];
	u16 RTSThresh;
	u16 SRL;
	u16 LRL;
	u16 SFBL;
	u16 LFBL;

	/* network config */
	bool लघुslot;
	s8 लघुslot_override;
	bool include_legacy_erp;

	काष्ठा brcms_protection *protection;
	s8 PLCPHdr_override;

	काष्ठा brcms_stf *stf;

	u32 bcn_rspec;

	uपूर्णांक tempsense_lastसमय;

	u16 tx_duty_cycle_ofdm;
	u16 tx_duty_cycle_cck;

	काष्ठा wiphy *wiphy;
	काष्ठा scb pri_scb;
	काष्ठा ieee80211_vअगर *vअगर;

	काष्ठा sk_buff *beacon;
	u16 beacon_tim_offset;
	u16 beacon_dtim_period;
	काष्ठा sk_buff *probe_resp;
पूर्ण;

/* antsel module specअगरic state */
काष्ठा antsel_info अणु
	काष्ठा brcms_c_info *wlc;	/* poपूर्णांकer to मुख्य wlc काष्ठाure */
	काष्ठा brcms_pub *pub;		/* poपूर्णांकer to खुला fn */
	u8 antsel_type;	/* Type of boardlevel mimo antenna चयन-logic
				 * 0 = N/A, 1 = 2x4 board, 2 = 2x3 CB2 board
				 */
	u8 antsel_antचयन;	/* board level antenna चयन type */
	bool antsel_avail;	/* Ant selection availability (SROM based) */
	काष्ठा brcms_antselcfg antcfg_11n; /* antenna configuration */
	काष्ठा brcms_antselcfg antcfg_cur; /* current antenna config (स्वतः) */
पूर्ण;

क्रमागत brcms_bss_type अणु
	BRCMS_TYPE_STATION,
	BRCMS_TYPE_AP,
	BRCMS_TYPE_ADHOC,
पूर्ण;

/*
 * BSS configuration state
 *
 * wlc: wlc to which this bsscfg beदीर्घs to.
 * type: पूर्णांकerface type
 * SSID_len: the length of SSID
 * SSID: SSID string
 *
 *
 * BSSID: BSSID (associated)
 * cur_etheraddr: h/w address
 * flags: BSSCFG flags; see below
 *
 * current_bss: BSS parms in ASSOCIATED state
 *
 *
 * ID: 'unique' ID of this bsscfg, asचिन्हित at bsscfg allocation
 */
काष्ठा brcms_bss_cfg अणु
	काष्ठा brcms_c_info *wlc;
	क्रमागत brcms_bss_type type;
	u8 SSID_len;
	u8 SSID[IEEE80211_MAX_SSID_LEN];
	u8 BSSID[ETH_ALEN];
	काष्ठा brcms_bss_info *current_bss;
पूर्ण;

पूर्णांक brcms_c_txfअगरo(काष्ठा brcms_c_info *wlc, uपूर्णांक fअगरo, काष्ठा sk_buff *p);
पूर्णांक brcms_b_xmtfअगरo_sz_get(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक fअगरo,
			   uपूर्णांक *blocks);

पूर्णांक brcms_c_set_gmode(काष्ठा brcms_c_info *wlc, u8 gmode, bool config);
व्योम brcms_c_mac_promisc(काष्ठा brcms_c_info *wlc, uपूर्णांक filter_flags);
u16 brcms_c_calc_lsig_len(काष्ठा brcms_c_info *wlc, u32 ratespec, uपूर्णांक mac_len);
u32 brcms_c_rspec_to_rts_rspec(काष्ठा brcms_c_info *wlc, u32 rspec,
			       bool use_rspec, u16 mimo_ctlchbw);
u16 brcms_c_compute_rtscts_dur(काष्ठा brcms_c_info *wlc, bool cts_only,
			       u32 rts_rate, u32 frame_rate,
			       u8 rts_preamble_type, u8 frame_preamble_type,
			       uपूर्णांक frame_len, bool ba);
व्योम brcms_c_inval_dma_pkts(काष्ठा brcms_hardware *hw,
			    काष्ठा ieee80211_sta *sta, व्योम (*dma_callback_fn));
व्योम brcms_c_update_probe_resp(काष्ठा brcms_c_info *wlc, bool suspend);
पूर्णांक brcms_c_set_nmode(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_beacon_phytxctl_txant_upd(काष्ठा brcms_c_info *wlc, u32 bcn_rate);
व्योम brcms_b_antsel_type_set(काष्ठा brcms_hardware *wlc_hw, u8 antsel_type);
व्योम brcms_b_set_chanspec(काष्ठा brcms_hardware *wlc_hw, u16 chanspec,
			  bool mute, काष्ठा txpwr_limits *txpwr);
व्योम brcms_b_ग_लिखो_shm(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक offset, u16 v);
u16 brcms_b_पढ़ो_shm(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक offset);
व्योम brcms_b_mhf(काष्ठा brcms_hardware *wlc_hw, u8 idx, u16 mask, u16 val,
		 पूर्णांक bands);
व्योम brcms_b_corereset(काष्ठा brcms_hardware *wlc_hw, u32 flags);
व्योम brcms_b_mctrl(काष्ठा brcms_hardware *wlc_hw, u32 mask, u32 val);
व्योम brcms_b_phy_reset(काष्ठा brcms_hardware *wlc_hw);
व्योम brcms_b_bw_set(काष्ठा brcms_hardware *wlc_hw, u16 bw);
व्योम brcms_b_core_phypll_reset(काष्ठा brcms_hardware *wlc_hw);
व्योम brcms_c_ucode_wake_override_set(काष्ठा brcms_hardware *wlc_hw,
				     u32 override_bit);
व्योम brcms_c_ucode_wake_override_clear(काष्ठा brcms_hardware *wlc_hw,
				       u32 override_bit);
व्योम brcms_b_ग_लिखो_ढाँचा_ram(काष्ठा brcms_hardware *wlc_hw, पूर्णांक offset,
				पूर्णांक len, व्योम *buf);
u16 brcms_b_rate_shm_offset(काष्ठा brcms_hardware *wlc_hw, u8 rate);
व्योम brcms_b_copyto_objmem(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक offset,
			   स्थिर व्योम *buf, पूर्णांक len, u32 sel);
व्योम brcms_b_copyfrom_objmem(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक offset,
			     व्योम *buf, पूर्णांक len, u32 sel);
व्योम brcms_b_चयन_macfreq(काष्ठा brcms_hardware *wlc_hw, u8 spurmode);
u16 brcms_b_get_txant(काष्ठा brcms_hardware *wlc_hw);
व्योम brcms_b_phyclk_fgc(काष्ठा brcms_hardware *wlc_hw, bool clk);
व्योम brcms_b_macphyclk_set(काष्ठा brcms_hardware *wlc_hw, bool clk);
व्योम brcms_b_core_phypll_ctl(काष्ठा brcms_hardware *wlc_hw, bool on);
व्योम brcms_b_txant_set(काष्ठा brcms_hardware *wlc_hw, u16 phytxant);
व्योम brcms_b_band_stf_ss_set(काष्ठा brcms_hardware *wlc_hw, u8 stf_mode);
व्योम brcms_c_init_scb(काष्ठा scb *scb);

#पूर्ण_अगर				/* _BRCM_MAIN_H_ */
