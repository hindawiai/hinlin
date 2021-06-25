<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 * Copyright (c) 2013 Hauke Mehrtens <hauke@hauke-m.de>
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

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/pci_ids.h>
#समावेश <linux/अगर_ether.h>
#समावेश <net/cfg80211.h>
#समावेश <net/mac80211.h>
#समावेश <brcm_hw_ids.h>
#समावेश <aiutils.h>
#समावेश <chipcommon.h>
#समावेश "rate.h"
#समावेश "scb.h"
#समावेश "phy/phy_hal.h"
#समावेश "channel.h"
#समावेश "antsel.h"
#समावेश "stf.h"
#समावेश "ampdu.h"
#समावेश "mac80211_if.h"
#समावेश "ucode_loader.h"
#समावेश "main.h"
#समावेश "soc.h"
#समावेश "dma.h"
#समावेश "debug.h"
#समावेश "brcms_trace_events.h"

/* watchकरोg समयr, in unit of ms */
#घोषणा TIMER_INTERVAL_WATCHDOG		1000
/* radio monitor समयr, in unit of ms */
#घोषणा TIMER_INTERVAL_RADIOCHK		800

/* beacon पूर्णांकerval, in unit of 1024TU */
#घोषणा BEACON_INTERVAL_DEFAULT		100

/* n-mode support capability */
/* 2x2 includes both 1x1 & 2x2 devices
 * reserved #घोषणा 2 क्रम future when we want to separate 1x1 & 2x2 and
 * control it independently
 */
#घोषणा WL_11N_2x2			1
#घोषणा WL_11N_3x3			3
#घोषणा WL_11N_4x4			4

#घोषणा EDCF_ACI_MASK			0x60
#घोषणा EDCF_ACI_SHIFT			5
#घोषणा EDCF_ECWMIN_MASK		0x0f
#घोषणा EDCF_ECWMAX_SHIFT		4
#घोषणा EDCF_AIFSN_MASK			0x0f
#घोषणा EDCF_AIFSN_MAX			15
#घोषणा EDCF_ECWMAX_MASK		0xf0

#घोषणा EDCF_AC_BE_TXOP_STA		0x0000
#घोषणा EDCF_AC_BK_TXOP_STA		0x0000
#घोषणा EDCF_AC_VO_ACI_STA		0x62
#घोषणा EDCF_AC_VO_ECW_STA		0x32
#घोषणा EDCF_AC_VI_ACI_STA		0x42
#घोषणा EDCF_AC_VI_ECW_STA		0x43
#घोषणा EDCF_AC_BK_ECW_STA		0xA4
#घोषणा EDCF_AC_VI_TXOP_STA		0x005e
#घोषणा EDCF_AC_VO_TXOP_STA		0x002f
#घोषणा EDCF_AC_BE_ACI_STA		0x03
#घोषणा EDCF_AC_BE_ECW_STA		0xA4
#घोषणा EDCF_AC_BK_ACI_STA		0x27
#घोषणा EDCF_AC_VO_TXOP_AP		0x002f

#घोषणा EDCF_TXOP2USEC(txop)		((txop) << 5)
#घोषणा EDCF_ECW2CW(exp)		((1 << (exp)) - 1)

#घोषणा APHY_SYMBOL_TIME		4
#घोषणा APHY_PREAMBLE_TIME		16
#घोषणा APHY_SIGNAL_TIME		4
#घोषणा APHY_SIFS_TIME			16
#घोषणा APHY_SERVICE_NBITS		16
#घोषणा APHY_TAIL_NBITS			6
#घोषणा BPHY_SIFS_TIME			10
#घोषणा BPHY_PLCP_SHORT_TIME		96

#घोषणा PREN_PREAMBLE			24
#घोषणा PREN_MM_EXT			12
#घोषणा PREN_PREAMBLE_EXT		4

#घोषणा DOT11_MAC_HDR_LEN		24
#घोषणा DOT11_ACK_LEN			10
#घोषणा DOT11_BA_LEN			4
#घोषणा DOT11_OFDM_SIGNAL_EXTENSION	6
#घोषणा DOT11_MIN_FRAG_LEN		256
#घोषणा DOT11_RTS_LEN			16
#घोषणा DOT11_CTS_LEN			10
#घोषणा DOT11_BA_BITMAP_LEN		128
#घोषणा DOT11_MAXNUMFRAGS		16
#घोषणा DOT11_MAX_FRAG_LEN		2346

#घोषणा BPHY_PLCP_TIME			192
#घोषणा RIFS_11N_TIME			2

/* length of the BCN ढाँचा area */
#घोषणा BCN_TMPL_LEN			512

/* brcms_bss_info flag bit values */
#घोषणा BRCMS_BSS_HT			0x0020	/* BSS is HT (MIMO) capable */

/* chip rx buffer offset */
#घोषणा BRCMS_HWRXOFF			38

/* rfdisable delay समयr 500 ms, runs of ALP घड़ी */
#घोषणा RFDISABLE_DEFAULT		10000000

#घोषणा BRCMS_TEMPSENSE_PERIOD		10	/* 10 second समयout */

/* synthpu_dly बार in us */
#घोषणा SYNTHPU_DLY_APHY_US		3700
#घोषणा SYNTHPU_DLY_BPHY_US		1050
#घोषणा SYNTHPU_DLY_NPHY_US		2048
#घोषणा SYNTHPU_DLY_LPPHY_US		300

#घोषणा ANTCNT				10	/* vanilla M_MAX_ANTCNT val */

/* Per-AC retry limit रेजिस्टर definitions; uses defs.h bitfield macros */
#घोषणा EDCF_SHORT_S			0
#घोषणा EDCF_SFB_S			4
#घोषणा EDCF_LONG_S			8
#घोषणा EDCF_LFB_S			12
#घोषणा EDCF_SHORT_M			BITFIELD_MASK(4)
#घोषणा EDCF_SFB_M			BITFIELD_MASK(4)
#घोषणा EDCF_LONG_M			BITFIELD_MASK(4)
#घोषणा EDCF_LFB_M			BITFIELD_MASK(4)

#घोषणा RETRY_SHORT_DEF			7	/* Default Short retry Limit */
#घोषणा RETRY_SHORT_MAX			255	/* Maximum Short retry Limit */
#घोषणा RETRY_LONG_DEF			4	/* Default Long retry count */
#घोषणा RETRY_SHORT_FB			3	/* Short count क्रम fb rate */
#घोषणा RETRY_LONG_FB			2	/* Long count क्रम fb rate */

#घोषणा APHY_CWMIN			15
#घोषणा PHY_CWMAX			1023

#घोषणा EDCF_AIFSN_MIN			1

#घोषणा FRAGNUM_MASK			0xF

#घोषणा APHY_SLOT_TIME			9
#घोषणा BPHY_SLOT_TIME			20

#घोषणा WL_SPURAVOID_OFF		0
#घोषणा WL_SPURAVOID_ON1		1
#घोषणा WL_SPURAVOID_ON2		2

/* invalid core flags, use the saved coreflags */
#घोषणा BRCMS_USE_COREFLAGS		0xffffffff

/* values क्रम PLCPHdr_override */
#घोषणा BRCMS_PLCP_AUTO			-1
#घोषणा BRCMS_PLCP_SHORT		0
#घोषणा BRCMS_PLCP_LONG			1

/* values क्रम g_protection_override and n_protection_override */
#घोषणा BRCMS_PROTECTION_AUTO		-1
#घोषणा BRCMS_PROTECTION_OFF		0
#घोषणा BRCMS_PROTECTION_ON		1
#घोषणा BRCMS_PROTECTION_MMHDR_ONLY	2
#घोषणा BRCMS_PROTECTION_CTS_ONLY	3

/* values क्रम g_protection_control and n_protection_control */
#घोषणा BRCMS_PROTECTION_CTL_OFF	0
#घोषणा BRCMS_PROTECTION_CTL_LOCAL	1
#घोषणा BRCMS_PROTECTION_CTL_OVERLAP	2

/* values क्रम n_protection */
#घोषणा BRCMS_N_PROTECTION_OFF		0
#घोषणा BRCMS_N_PROTECTION_OPTIONAL	1
#घोषणा BRCMS_N_PROTECTION_20IN40	2
#घोषणा BRCMS_N_PROTECTION_MIXEDMODE	3

/* values क्रम band specअगरic 40MHz capabilities */
#घोषणा BRCMS_N_BW_20ALL		0
#घोषणा BRCMS_N_BW_40ALL		1
#घोषणा BRCMS_N_BW_20IN2G_40IN5G	2

/* bitflags क्रम SGI support (sgi_rx iovar) */
#घोषणा BRCMS_N_SGI_20			0x01
#घोषणा BRCMS_N_SGI_40			0x02

/* defines used by the nrate iovar */
/* MSC in use,indicates b0-6 holds an mcs */
#घोषणा NRATE_MCS_INUSE			0x00000080
/* rate/mcs value */
#घोषणा NRATE_RATE_MASK			0x0000007f
/* stf mode mask: siso, cdd, stbc, sdm */
#घोषणा NRATE_STF_MASK			0x0000ff00
/* stf mode shअगरt */
#घोषणा NRATE_STF_SHIFT			8
/* bit indicate to override mcs only */
#घोषणा NRATE_OVERRIDE_MCS_ONLY		0x40000000
#घोषणा NRATE_SGI_MASK			0x00800000	/* sgi mode */
#घोषणा NRATE_SGI_SHIFT			23		/* sgi mode */
#घोषणा NRATE_LDPC_CODING		0x00400000	/* adv coding in use */
#घोषणा NRATE_LDPC_SHIFT		22		/* ldpc shअगरt */

#घोषणा NRATE_STF_SISO			0		/* stf mode SISO */
#घोषणा NRATE_STF_CDD			1		/* stf mode CDD */
#घोषणा NRATE_STF_STBC			2		/* stf mode STBC */
#घोषणा NRATE_STF_SDM			3		/* stf mode SDM */

#घोषणा MAX_DMA_SEGS			4

/* # of entries in Tx FIFO */
#घोषणा NTXD				64
/* Max # of entries in Rx FIFO based on 4kb page size */
#घोषणा NRXD				256

/* Amount of headroom to leave in Tx FIFO */
#घोषणा TX_HEADROOM			4

/* try to keep this # rbufs posted to the chip */
#घोषणा NRXBUFPOST			32

/* max # frames to process in brcms_c_recv() */
#घोषणा RXBND				8
/* max # tx status to process in wlc_txstatus() */
#घोषणा TXSBND				8

/* brcmu_क्रमmat_flags() bit description काष्ठाure */
काष्ठा brcms_c_bit_desc अणु
	u32 bit;
	स्थिर अक्षर *name;
पूर्ण;

/*
 * The following table lists the buffer memory allocated to xmt fअगरos in HW.
 * the size is in units of 256bytes(one block), total size is HW dependent
 * ucode has शेष fअगरo partition, sw can overग_लिखो अगर necessary
 *
 * This is करोcumented in twiki under the topic UcodeTxFअगरo. Please ensure
 * the twiki is updated beक्रमe making changes.
 */

/* Starting corerev क्रम the fअगरo size table */
#घोषणा XMTFIFOTBL_STARTREV	17

काष्ठा d11init अणु
	__le16 addr;
	__le16 size;
	__le32 value;
पूर्ण;

काष्ठा edcf_acparam अणु
	u8 ACI;
	u8 ECW;
	u16 TXOP;
पूर्ण __packed;

/* debug/trace */
uपूर्णांक brcm_msg_level;

/* TX FIFO number to WME/802.1E Access Category */
अटल स्थिर u8 wme_fअगरo2ac[] = अणु
	IEEE80211_AC_BK,
	IEEE80211_AC_BE,
	IEEE80211_AC_VI,
	IEEE80211_AC_VO,
	IEEE80211_AC_BE,
	IEEE80211_AC_BE
पूर्ण;

/* ieee80211 Access Category to TX FIFO number */
अटल स्थिर u8 wme_ac2fअगरo[] = अणु
	TX_AC_VO_FIFO,
	TX_AC_VI_FIFO,
	TX_AC_BE_FIFO,
	TX_AC_BK_FIFO
पूर्ण;

अटल स्थिर u16 xmtfअगरo_sz[][NFIFO] = अणु
	/* corerev 17: 5120, 49152, 49152, 5376, 4352, 1280 */
	अणु20, 192, 192, 21, 17, 5पूर्ण,
	/* corerev 18: */
	अणु0, 0, 0, 0, 0, 0पूर्ण,
	/* corerev 19: */
	अणु0, 0, 0, 0, 0, 0पूर्ण,
	/* corerev 20: 5120, 49152, 49152, 5376, 4352, 1280 */
	अणु20, 192, 192, 21, 17, 5पूर्ण,
	/* corerev 21: 2304, 14848, 5632, 3584, 3584, 1280 */
	अणु9, 58, 22, 14, 14, 5पूर्ण,
	/* corerev 22: 5120, 49152, 49152, 5376, 4352, 1280 */
	अणु20, 192, 192, 21, 17, 5पूर्ण,
	/* corerev 23: 5120, 49152, 49152, 5376, 4352, 1280 */
	अणु20, 192, 192, 21, 17, 5पूर्ण,
	/* corerev 24: 2304, 14848, 5632, 3584, 3584, 1280 */
	अणु9, 58, 22, 14, 14, 5पूर्ण,
	/* corerev 25: */
	अणु0, 0, 0, 0, 0, 0पूर्ण,
	/* corerev 26: */
	अणु0, 0, 0, 0, 0, 0पूर्ण,
	/* corerev 27: */
	अणु0, 0, 0, 0, 0, 0पूर्ण,
	/* corerev 28: 2304, 14848, 5632, 3584, 3584, 1280 */
	अणु9, 58, 22, 14, 14, 5पूर्ण,
पूर्ण;

#अगर_घोषित DEBUG
अटल स्थिर अक्षर * स्थिर fअगरo_names[] = अणु
	"AC_BK", "AC_BE", "AC_VI", "AC_VO", "BCMC", "ATIM" पूर्ण;
#अन्यथा
अटल स्थिर अक्षर fअगरo_names[6][1];
#पूर्ण_अगर

#अगर_घोषित DEBUG
/* poपूर्णांकer to most recently allocated wl/wlc */
अटल काष्ठा brcms_c_info *wlc_info_dbg = (काष्ठा brcms_c_info *) (शून्य);
#पूर्ण_अगर

/* Mapping of ieee80211 AC numbers to tx fअगरos */
अटल स्थिर u8 ac_to_fअगरo_mapping[IEEE80211_NUM_ACS] = अणु
	[IEEE80211_AC_VO]	= TX_AC_VO_FIFO,
	[IEEE80211_AC_VI]	= TX_AC_VI_FIFO,
	[IEEE80211_AC_BE]	= TX_AC_BE_FIFO,
	[IEEE80211_AC_BK]	= TX_AC_BK_FIFO,
पूर्ण;

/* Mapping of tx fअगरos to ieee80211 AC numbers */
अटल स्थिर u8 fअगरo_to_ac_mapping[IEEE80211_NUM_ACS] = अणु
	[TX_AC_BK_FIFO]	= IEEE80211_AC_BK,
	[TX_AC_BE_FIFO]	= IEEE80211_AC_BE,
	[TX_AC_VI_FIFO]	= IEEE80211_AC_VI,
	[TX_AC_VO_FIFO]	= IEEE80211_AC_VO,
पूर्ण;

अटल u8 brcms_ac_to_fअगरo(u8 ac)
अणु
	अगर (ac >= ARRAY_SIZE(ac_to_fअगरo_mapping))
		वापस TX_AC_BE_FIFO;
	वापस ac_to_fअगरo_mapping[ac];
पूर्ण

अटल u8 brcms_fअगरo_to_ac(u8 fअगरo)
अणु
	अगर (fअगरo >= ARRAY_SIZE(fअगरo_to_ac_mapping))
		वापस IEEE80211_AC_BE;
	वापस fअगरo_to_ac_mapping[fअगरo];
पूर्ण

/* Find basic rate क्रम a given rate */
अटल u8 brcms_basic_rate(काष्ठा brcms_c_info *wlc, u32 rspec)
अणु
	अगर (is_mcs_rate(rspec))
		वापस wlc->band->basic_rate[mcs_table[rspec & RSPEC_RATE_MASK]
		       .leg_ofdm];
	वापस wlc->band->basic_rate[rspec & RSPEC_RATE_MASK];
पूर्ण

अटल u16 frametype(u32 rspec, u8 mimoframe)
अणु
	अगर (is_mcs_rate(rspec))
		वापस mimoframe;
	वापस is_cck_rate(rspec) ? FT_CCK : FT_OFDM;
पूर्ण

/* currently the best mechanism क्रम determining SIFS is the band in use */
अटल u16 get_sअगरs(काष्ठा brcms_band *band)
अणु
	वापस band->bandtype == BRCM_BAND_5G ? APHY_SIFS_TIME :
				 BPHY_SIFS_TIME;
पूर्ण

/*
 * Detect Card हटाओd.
 * Even checking an sbconfig रेजिस्टर पढ़ो will not false trigger when the core
 * is in reset it अवरोधs CF address mechanism. Accessing gphy phyversion will
 * cause SB error अगर aphy is in reset on 4306B0-DB. Need a simple accessible
 * reg with fixed 0/1 pattern (some platक्रमms वापस all 0).
 * If घड़ीs are present, call the sb routine which will figure out अगर the
 * device is हटाओd.
 */
अटल bool brcms_deviceहटाओd(काष्ठा brcms_c_info *wlc)
अणु
	u32 macctrl;

	अगर (!wlc->hw->clk)
		वापस ai_deviceहटाओd(wlc->hw->sih);
	macctrl = bcma_पढ़ो32(wlc->hw->d11core,
			      D11REGOFFS(maccontrol));
	वापस (macctrl & (MCTL_PSM_JMP_0 | MCTL_IHR_EN)) != MCTL_IHR_EN;
पूर्ण

/* sum the inभागidual fअगरo tx pending packet counts */
अटल पूर्णांक brcms_txpktpendtot(काष्ठा brcms_c_info *wlc)
अणु
	पूर्णांक i;
	पूर्णांक pending = 0;

	क्रम (i = 0; i < ARRAY_SIZE(wlc->hw->di); i++)
		अगर (wlc->hw->di[i])
			pending += dma_txpending(wlc->hw->di[i]);
	वापस pending;
पूर्ण

अटल bool brcms_is_mband_unlocked(काष्ठा brcms_c_info *wlc)
अणु
	वापस wlc->pub->_nbands > 1 && !wlc->bandlocked;
पूर्ण

अटल पूर्णांक brcms_chspec_bw(u16 chanspec)
अणु
	अगर (CHSPEC_IS40(chanspec))
		वापस BRCMS_40_MHZ;
	अगर (CHSPEC_IS20(chanspec))
		वापस BRCMS_20_MHZ;

	वापस BRCMS_10_MHZ;
पूर्ण

अटल व्योम brcms_c_bsscfg_mमुक्त(काष्ठा brcms_bss_cfg *cfg)
अणु
	अगर (cfg == शून्य)
		वापस;

	kमुक्त(cfg->current_bss);
	kमुक्त(cfg);
पूर्ण

अटल व्योम brcms_c_detach_mमुक्त(काष्ठा brcms_c_info *wlc)
अणु
	अगर (wlc == शून्य)
		वापस;

	brcms_c_bsscfg_mमुक्त(wlc->bsscfg);
	kमुक्त(wlc->pub);
	kमुक्त(wlc->modulecb);
	kमुक्त(wlc->शेष_bss);
	kमुक्त(wlc->protection);
	kमुक्त(wlc->stf);
	kमुक्त(wlc->bandstate[0]);
	अगर (wlc->corestate)
		kमुक्त(wlc->corestate->macstat_snapshot);
	kमुक्त(wlc->corestate);
	अगर (wlc->hw)
		kमुक्त(wlc->hw->bandstate[0]);
	kमुक्त(wlc->hw);
	अगर (wlc->beacon)
		dev_kमुक्त_skb_any(wlc->beacon);
	अगर (wlc->probe_resp)
		dev_kमुक्त_skb_any(wlc->probe_resp);

	kमुक्त(wlc);
पूर्ण

अटल काष्ठा brcms_bss_cfg *brcms_c_bsscfg_दो_स्मृति(uपूर्णांक unit)
अणु
	काष्ठा brcms_bss_cfg *cfg;

	cfg = kzalloc(माप(काष्ठा brcms_bss_cfg), GFP_ATOMIC);
	अगर (cfg == शून्य)
		जाओ fail;

	cfg->current_bss = kzalloc(माप(काष्ठा brcms_bss_info), GFP_ATOMIC);
	अगर (cfg->current_bss == शून्य)
		जाओ fail;

	वापस cfg;

 fail:
	brcms_c_bsscfg_mमुक्त(cfg);
	वापस शून्य;
पूर्ण

अटल काष्ठा brcms_c_info *
brcms_c_attach_दो_स्मृति(uपूर्णांक unit, uपूर्णांक *err, uपूर्णांक devid)
अणु
	काष्ठा brcms_c_info *wlc;

	wlc = kzalloc(माप(काष्ठा brcms_c_info), GFP_ATOMIC);
	अगर (wlc == शून्य) अणु
		*err = 1002;
		जाओ fail;
	पूर्ण

	/* allocate काष्ठा brcms_c_pub state काष्ठाure */
	wlc->pub = kzalloc(माप(काष्ठा brcms_pub), GFP_ATOMIC);
	अगर (wlc->pub == शून्य) अणु
		*err = 1003;
		जाओ fail;
	पूर्ण
	wlc->pub->wlc = wlc;

	/* allocate काष्ठा brcms_hardware state काष्ठाure */

	wlc->hw = kzalloc(माप(काष्ठा brcms_hardware), GFP_ATOMIC);
	अगर (wlc->hw == शून्य) अणु
		*err = 1005;
		जाओ fail;
	पूर्ण
	wlc->hw->wlc = wlc;

	wlc->hw->bandstate[0] =
		kसुस्मृति(MAXBANDS, माप(काष्ठा brcms_hw_band), GFP_ATOMIC);
	अगर (wlc->hw->bandstate[0] == शून्य) अणु
		*err = 1006;
		जाओ fail;
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		क्रम (i = 1; i < MAXBANDS; i++)
			wlc->hw->bandstate[i] = (काष्ठा brcms_hw_band *)
			    ((अचिन्हित दीर्घ)wlc->hw->bandstate[0] +
			     (माप(काष्ठा brcms_hw_band) * i));
	पूर्ण

	wlc->modulecb =
		kसुस्मृति(BRCMS_MAXMODULES, माप(काष्ठा modulecb),
			GFP_ATOMIC);
	अगर (wlc->modulecb == शून्य) अणु
		*err = 1009;
		जाओ fail;
	पूर्ण

	wlc->शेष_bss = kzalloc(माप(काष्ठा brcms_bss_info), GFP_ATOMIC);
	अगर (wlc->शेष_bss == शून्य) अणु
		*err = 1010;
		जाओ fail;
	पूर्ण

	wlc->bsscfg = brcms_c_bsscfg_दो_स्मृति(unit);
	अगर (wlc->bsscfg == शून्य) अणु
		*err = 1011;
		जाओ fail;
	पूर्ण

	wlc->protection = kzalloc(माप(काष्ठा brcms_protection),
				  GFP_ATOMIC);
	अगर (wlc->protection == शून्य) अणु
		*err = 1016;
		जाओ fail;
	पूर्ण

	wlc->stf = kzalloc(माप(काष्ठा brcms_stf), GFP_ATOMIC);
	अगर (wlc->stf == शून्य) अणु
		*err = 1017;
		जाओ fail;
	पूर्ण

	wlc->bandstate[0] =
		kसुस्मृति(MAXBANDS, माप(काष्ठा brcms_band), GFP_ATOMIC);
	अगर (wlc->bandstate[0] == शून्य) अणु
		*err = 1025;
		जाओ fail;
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		क्रम (i = 1; i < MAXBANDS; i++)
			wlc->bandstate[i] = (काष्ठा brcms_band *)
				((अचिन्हित दीर्घ)wlc->bandstate[0]
				+ (माप(काष्ठा brcms_band)*i));
	पूर्ण

	wlc->corestate = kzalloc(माप(काष्ठा brcms_core), GFP_ATOMIC);
	अगर (wlc->corestate == शून्य) अणु
		*err = 1026;
		जाओ fail;
	पूर्ण

	wlc->corestate->macstat_snapshot =
		kzalloc(माप(काष्ठा macstat), GFP_ATOMIC);
	अगर (wlc->corestate->macstat_snapshot == शून्य) अणु
		*err = 1027;
		जाओ fail;
	पूर्ण

	वापस wlc;

 fail:
	brcms_c_detach_mमुक्त(wlc);
	वापस शून्य;
पूर्ण

/*
 * Update the slot timing क्रम standard 11b/g (20us slots)
 * or लघुslot 11g (9us slots)
 * The PSM needs to be suspended क्रम this call.
 */
अटल व्योम brcms_b_update_slot_timing(काष्ठा brcms_hardware *wlc_hw,
					bool लघुslot)
अणु
	काष्ठा bcma_device *core = wlc_hw->d11core;

	अगर (लघुslot) अणु
		/* 11g लघु slot: 11a timing */
		bcma_ग_लिखो16(core, D11REGOFFS(अगरs_slot), 0x0207);
		brcms_b_ग_लिखो_shm(wlc_hw, M_DOT11_SLOT, APHY_SLOT_TIME);
	पूर्ण अन्यथा अणु
		/* 11g दीर्घ slot: 11b timing */
		bcma_ग_लिखो16(core, D11REGOFFS(अगरs_slot), 0x0212);
		brcms_b_ग_लिखो_shm(wlc_hw, M_DOT11_SLOT, BPHY_SLOT_TIME);
	पूर्ण
पूर्ण

/*
 * calculate frame duration of a given rate and length, वापस
 * समय in usec unit
 */
अटल uपूर्णांक brcms_c_calc_frame_समय(काष्ठा brcms_c_info *wlc, u32 ratespec,
				    u8 preamble_type, uपूर्णांक mac_len)
अणु
	uपूर्णांक nsyms, dur = 0, Ndps, kNdps;
	uपूर्णांक rate = rspec2rate(ratespec);

	अगर (rate == 0) अणु
		brcms_err(wlc->hw->d11core, "wl%d: WAR: using rate of 1 mbps\n",
			  wlc->pub->unit);
		rate = BRCM_RATE_1M;
	पूर्ण

	अगर (is_mcs_rate(ratespec)) अणु
		uपूर्णांक mcs = ratespec & RSPEC_RATE_MASK;
		पूर्णांक tot_streams = mcs_2_txstreams(mcs) + rspec_stc(ratespec);

		dur = PREN_PREAMBLE + (tot_streams * PREN_PREAMBLE_EXT);
		अगर (preamble_type == BRCMS_MM_PREAMBLE)
			dur += PREN_MM_EXT;
		/* 1000Ndbps = kbps * 4 */
		kNdps = mcs_2_rate(mcs, rspec_is40mhz(ratespec),
				   rspec_issgi(ratespec)) * 4;

		अगर (rspec_stc(ratespec) == 0)
			nsyms =
			    CEIL((APHY_SERVICE_NBITS + 8 * mac_len +
				  APHY_TAIL_NBITS) * 1000, kNdps);
		अन्यथा
			/* STBC needs to have even number of symbols */
			nsyms =
			    2 *
			    CEIL((APHY_SERVICE_NBITS + 8 * mac_len +
				  APHY_TAIL_NBITS) * 1000, 2 * kNdps);

		dur += APHY_SYMBOL_TIME * nsyms;
		अगर (wlc->band->bandtype == BRCM_BAND_2G)
			dur += DOT11_OFDM_SIGNAL_EXTENSION;
	पूर्ण अन्यथा अगर (is_ofdm_rate(rate)) अणु
		dur = APHY_PREAMBLE_TIME;
		dur += APHY_SIGNAL_TIME;
		/* Ndbps = Mbps * 4 = rate(500Kbps) * 2 */
		Ndps = rate * 2;
		/* NSyms = CEILING((SERVICE + 8*NBytes + TAIL) / Ndbps) */
		nsyms =
		    CEIL((APHY_SERVICE_NBITS + 8 * mac_len + APHY_TAIL_NBITS),
			 Ndps);
		dur += APHY_SYMBOL_TIME * nsyms;
		अगर (wlc->band->bandtype == BRCM_BAND_2G)
			dur += DOT11_OFDM_SIGNAL_EXTENSION;
	पूर्ण अन्यथा अणु
		/*
		 * calc # bits * 2 so factor of 2 in rate (1/2 mbps)
		 * will भागide out
		 */
		mac_len = mac_len * 8 * 2;
		/* calc उच्चमानing of bits/rate = microseconds of air समय */
		dur = (mac_len + rate - 1) / rate;
		अगर (preamble_type & BRCMS_SHORT_PREAMBLE)
			dur += BPHY_PLCP_SHORT_TIME;
		अन्यथा
			dur += BPHY_PLCP_TIME;
	पूर्ण
	वापस dur;
पूर्ण

अटल व्योम brcms_c_ग_लिखो_inits(काष्ठा brcms_hardware *wlc_hw,
				स्थिर काष्ठा d11init *inits)
अणु
	काष्ठा bcma_device *core = wlc_hw->d11core;
	पूर्णांक i;
	uपूर्णांक offset;
	u16 size;
	u32 value;

	brcms_dbg_info(wlc_hw->d11core, "wl%d\n", wlc_hw->unit);

	क्रम (i = 0; inits[i].addr != cpu_to_le16(0xffff); i++) अणु
		size = le16_to_cpu(inits[i].size);
		offset = le16_to_cpu(inits[i].addr);
		value = le32_to_cpu(inits[i].value);
		अगर (size == 2)
			bcma_ग_लिखो16(core, offset, value);
		अन्यथा अगर (size == 4)
			bcma_ग_लिखो32(core, offset, value);
		अन्यथा
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम brcms_c_ग_लिखो_mhf(काष्ठा brcms_hardware *wlc_hw, u16 *mhfs)
अणु
	u8 idx;
	u16 addr[] = अणु
		M_HOST_FLAGS1, M_HOST_FLAGS2, M_HOST_FLAGS3, M_HOST_FLAGS4,
		M_HOST_FLAGS5
	पूर्ण;

	क्रम (idx = 0; idx < MHFMAX; idx++)
		brcms_b_ग_लिखो_shm(wlc_hw, addr[idx], mhfs[idx]);
पूर्ण

अटल व्योम brcms_c_ucode_bsinit(काष्ठा brcms_hardware *wlc_hw)
अणु
	काष्ठा brcms_ucode *ucode = &wlc_hw->wlc->wl->ucode;

	/* init microcode host flags */
	brcms_c_ग_लिखो_mhf(wlc_hw, wlc_hw->band->mhfs);

	/* करो band-specअगरic ucode IHR, SHM, and SCR inits */
	अगर (D11REV_IS(wlc_hw->corerev, 17) || D11REV_IS(wlc_hw->corerev, 23)) अणु
		अगर (BRCMS_ISNPHY(wlc_hw->band))
			brcms_c_ग_लिखो_inits(wlc_hw, ucode->d11n0bsinitvals16);
		अन्यथा
			brcms_err(wlc_hw->d11core,
				  "%s: wl%d: unsupported phy in corerev %d\n",
				  __func__, wlc_hw->unit,
				  wlc_hw->corerev);
	पूर्ण अन्यथा अणु
		अगर (D11REV_IS(wlc_hw->corerev, 24)) अणु
			अगर (BRCMS_ISLCNPHY(wlc_hw->band))
				brcms_c_ग_लिखो_inits(wlc_hw,
						    ucode->d11lcn0bsinitvals24);
			अन्यथा
				brcms_err(wlc_hw->d11core,
					  "%s: wl%d: unsupported phy in core rev %d\n",
					  __func__, wlc_hw->unit,
					  wlc_hw->corerev);
		पूर्ण अन्यथा अणु
			brcms_err(wlc_hw->d11core,
				  "%s: wl%d: unsupported corerev %d\n",
				  __func__, wlc_hw->unit, wlc_hw->corerev);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम brcms_b_core_ioctl(काष्ठा brcms_hardware *wlc_hw, u32 m, u32 v)
अणु
	काष्ठा bcma_device *core = wlc_hw->d11core;
	u32 ioctl = bcma_aपढ़ो32(core, BCMA_IOCTL) & ~m;

	bcma_aग_लिखो32(core, BCMA_IOCTL, ioctl | v);
पूर्ण

अटल व्योम brcms_b_core_phy_clk(काष्ठा brcms_hardware *wlc_hw, bool clk)
अणु
	brcms_dbg_info(wlc_hw->d11core, "wl%d: clk %d\n", wlc_hw->unit, clk);

	wlc_hw->phyclk = clk;

	अगर (OFF == clk) अणु	/* clear gmode bit, put phy पूर्णांकo reset */

		brcms_b_core_ioctl(wlc_hw, (SICF_PRST | SICF_FGC | SICF_GMODE),
				   (SICF_PRST | SICF_FGC));
		udelay(1);
		brcms_b_core_ioctl(wlc_hw, (SICF_PRST | SICF_FGC), SICF_PRST);
		udelay(1);

	पूर्ण अन्यथा अणु		/* take phy out of reset */

		brcms_b_core_ioctl(wlc_hw, (SICF_PRST | SICF_FGC), SICF_FGC);
		udelay(1);
		brcms_b_core_ioctl(wlc_hw, SICF_FGC, 0);
		udelay(1);

	पूर्ण
पूर्ण

/* low-level band चयन utility routine */
अटल व्योम brcms_c_setxband(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक bandunit)
अणु
	brcms_dbg_mac80211(wlc_hw->d11core, "wl%d: bandunit %d\n", wlc_hw->unit,
			   bandunit);

	wlc_hw->band = wlc_hw->bandstate[bandunit];

	/*
	 * BMAC_NOTE:
	 *   until we eliminate need क्रम wlc->band refs in low level code
	 */
	wlc_hw->wlc->band = wlc_hw->wlc->bandstate[bandunit];

	/* set gmode core flag */
	अगर (wlc_hw->sbclk && !wlc_hw->noreset) अणु
		u32 gmode = 0;

		अगर (bandunit == 0)
			gmode = SICF_GMODE;

		brcms_b_core_ioctl(wlc_hw, SICF_GMODE, gmode);
	पूर्ण
पूर्ण

/* चयन to new band but leave it inactive */
अटल u32 brcms_c_setband_inact(काष्ठा brcms_c_info *wlc, uपूर्णांक bandunit)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	u32 macपूर्णांकmask;
	u32 macctrl;

	brcms_dbg_mac80211(wlc_hw->d11core, "wl%d\n", wlc_hw->unit);
	macctrl = bcma_पढ़ो32(wlc_hw->d11core,
			      D11REGOFFS(maccontrol));
	WARN_ON((macctrl & MCTL_EN_MAC) != 0);

	/* disable पूर्णांकerrupts */
	macपूर्णांकmask = brcms_पूर्णांकrsoff(wlc->wl);

	/* radio off */
	wlc_phy_चयन_radio(wlc_hw->band->pi, OFF);

	brcms_b_core_phy_clk(wlc_hw, OFF);

	brcms_c_setxband(wlc_hw, bandunit);

	वापस macपूर्णांकmask;
पूर्ण

/* process an inभागidual काष्ठा tx_status */
अटल bool
brcms_c_करोtxstatus(काष्ठा brcms_c_info *wlc, काष्ठा tx_status *txs)
अणु
	काष्ठा sk_buff *p = शून्य;
	uपूर्णांक queue = NFIFO;
	काष्ठा dma_pub *dma = शून्य;
	काष्ठा d11txh *txh = शून्य;
	काष्ठा scb *scb = शून्य;
	पूर्णांक tx_frame_count;
	uपूर्णांक supr_status;
	bool lastframe;
	काष्ठा ieee80211_hdr *h;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा ieee80211_tx_rate *txrate;
	पूर्णांक i;
	bool fatal = true;

	trace_brcms_txstatus(&wlc->hw->d11core->dev, txs->framelen,
			     txs->frameid, txs->status, txs->lasttxसमय,
			     txs->sequence, txs->phyerr, txs->ackphyrxsh);

	/* discard पूर्णांकermediate indications क्रम ucode with one legitimate हाल:
	 *   e.g. अगर "useRTS" is set. ucode did a successful rts/cts exchange,
	 *   but the subsequent tx of DATA failed. so it will start rts/cts
	 *   from the beginning (resetting the rts transmission count)
	 */
	अगर (!(txs->status & TX_STATUS_AMPDU)
	    && (txs->status & TX_STATUS_INTERMEDIATE)) अणु
		brcms_dbg_tx(wlc->hw->d11core, "INTERMEDIATE but not AMPDU\n");
		fatal = false;
		जाओ out;
	पूर्ण

	queue = txs->frameid & TXFID_QUEUE_MASK;
	अगर (queue >= NFIFO) अणु
		brcms_err(wlc->hw->d11core, "queue %u >= NFIFO\n", queue);
		जाओ out;
	पूर्ण

	dma = wlc->hw->di[queue];

	p = dma_getnexttxp(wlc->hw->di[queue], DMA_RANGE_TRANSMITTED);
	अगर (p == शून्य) अणु
		brcms_err(wlc->hw->d11core, "dma_getnexttxp returned null!\n");
		जाओ out;
	पूर्ण

	txh = (काष्ठा d11txh *) (p->data);

	अगर (txs->phyerr)
		brcms_dbg_tx(wlc->hw->d11core, "phyerr 0x%x, rate 0x%x\n",
			     txs->phyerr, txh->MainRates);

	अगर (txs->frameid != le16_to_cpu(txh->TxFrameID)) अणु
		brcms_err(wlc->hw->d11core, "frameid != txh->TxFrameID\n");
		जाओ out;
	पूर्ण
	tx_info = IEEE80211_SKB_CB(p);
	h = (काष्ठा ieee80211_hdr *)((u8 *) (txh + 1) + D11_PHY_HDR_LEN);

	अगर (tx_info->rate_driver_data[0])
		scb = &wlc->pri_scb;

	अगर (tx_info->flags & IEEE80211_TX_CTL_AMPDU) अणु
		brcms_c_ampdu_करोtxstatus(wlc->ampdu, scb, p, txs);
		fatal = false;
		जाओ out;
	पूर्ण

	/*
	 * brcms_c_ampdu_करोtxstatus() will trace tx descriptors क्रम AMPDU
	 * frames; this traces them क्रम the rest.
	 */
	trace_brcms_txdesc(&wlc->hw->d11core->dev, txh, माप(*txh));

	supr_status = txs->status & TX_STATUS_SUPR_MASK;
	अगर (supr_status == TX_STATUS_SUPR_BADCH) अणु
		अचिन्हित xfts = le16_to_cpu(txh->XtraFrameTypes);
		brcms_dbg_tx(wlc->hw->d11core,
			     "Pkt tx suppressed, dest chan %u, current %d\n",
			     (xfts >> XFTS_CHANNEL_SHIFT) & 0xff,
			     CHSPEC_CHANNEL(wlc->शेष_bss->chanspec));
	पूर्ण

	tx_frame_count =
	    (txs->status & TX_STATUS_FRM_RTX_MASK) >> TX_STATUS_FRM_RTX_SHIFT;

	lastframe = !ieee80211_has_morefrags(h->frame_control);

	अगर (!lastframe) अणु
		brcms_err(wlc->hw->d11core, "Not last frame!\n");
	पूर्ण अन्यथा अणु
		/*
		 * Set inक्रमmation to be consumed by Minstrel ht.
		 *
		 * The "fallback limit" is the number of tx attempts a given
		 * MPDU is sent at the "primary" rate. Tx attempts beyond that
		 * limit are sent at the "secondary" rate.
		 * A 'short frame' करोes not exceed RTS treshold.
		 */
		u16 sfbl,	/* Short Frame Rate Fallback Limit */
		    lfbl,	/* Long Frame Rate Fallback Limit */
		    fbl;

		अगर (queue < IEEE80211_NUM_ACS) अणु
			sfbl = GFIELD(wlc->wme_retries[wme_fअगरo2ac[queue]],
				      EDCF_SFB);
			lfbl = GFIELD(wlc->wme_retries[wme_fअगरo2ac[queue]],
				      EDCF_LFB);
		पूर्ण अन्यथा अणु
			sfbl = wlc->SFBL;
			lfbl = wlc->LFBL;
		पूर्ण

		txrate = tx_info->status.rates;
		अगर (txrate[0].flags & IEEE80211_TX_RC_USE_RTS_CTS)
			fbl = lfbl;
		अन्यथा
			fbl = sfbl;

		ieee80211_tx_info_clear_status(tx_info);

		अगर ((tx_frame_count > fbl) && (txrate[1].idx >= 0)) अणु
			/*
			 * rate selection requested a fallback rate
			 * and we used it
			 */
			txrate[0].count = fbl;
			txrate[1].count = tx_frame_count - fbl;
		पूर्ण अन्यथा अणु
			/*
			 * rate selection did not request fallback rate, or
			 * we didn't need it
			 */
			txrate[0].count = tx_frame_count;
			/*
			 * rc80211_minstrel.c:minstrel_tx_status() expects
			 * unused rates to be marked with idx = -1
			 */
			txrate[1].idx = -1;
			txrate[1].count = 0;
		पूर्ण

		/* clear the rest of the rates */
		क्रम (i = 2; i < IEEE80211_TX_MAX_RATES; i++) अणु
			txrate[i].idx = -1;
			txrate[i].count = 0;
		पूर्ण

		अगर (txs->status & TX_STATUS_ACK_RCV)
			tx_info->flags |= IEEE80211_TX_STAT_ACK;
	पूर्ण

	अगर (lastframe) अणु
		/* हटाओ PLCP & Broadcom tx descriptor header */
		skb_pull(p, D11_PHY_HDR_LEN);
		skb_pull(p, D11_TXH_LEN);
		ieee80211_tx_status_irqsafe(wlc->pub->ieee_hw, p);
	पूर्ण अन्यथा अणु
		brcms_err(wlc->hw->d11core,
			  "%s: Not last frame => not calling tx_status\n",
			  __func__);
	पूर्ण

	fatal = false;

 out:
	अगर (fatal) अणु
		अगर (txh)
			trace_brcms_txdesc(&wlc->hw->d11core->dev, txh,
					   माप(*txh));
		brcmu_pkt_buf_मुक्त_skb(p);
	पूर्ण

	अगर (dma && queue < NFIFO) अणु
		u16 ac_queue = brcms_fअगरo_to_ac(queue);
		अगर (dma->txavail > TX_HEADROOM && queue < TX_BCMC_FIFO &&
		    ieee80211_queue_stopped(wlc->pub->ieee_hw, ac_queue))
			ieee80211_wake_queue(wlc->pub->ieee_hw, ac_queue);
		dma_kick_tx(dma);
	पूर्ण

	वापस fatal;
पूर्ण

/* process tx completion events in BMAC
 * Return true अगर more tx status need to be processed. false otherwise.
 */
अटल bool
brcms_b_txstatus(काष्ठा brcms_hardware *wlc_hw, bool bound, bool *fatal)
अणु
	काष्ठा bcma_device *core;
	काष्ठा tx_status txstatus, *txs;
	u32 s1, s2;
	uपूर्णांक n = 0;
	/*
	 * Param 'max_tx_num' indicates max. # tx status to process beक्रमe
	 * अवरोध out.
	 */
	uपूर्णांक max_tx_num = bound ? TXSBND : -1;

	txs = &txstatus;
	core = wlc_hw->d11core;
	*fatal = false;

	जबतक (n < max_tx_num) अणु
		s1 = bcma_पढ़ो32(core, D11REGOFFS(frmtxstatus));
		अगर (s1 == 0xffffffff) अणु
			brcms_err(core, "wl%d: %s: dead chip\n", wlc_hw->unit,
				  __func__);
			*fatal = true;
			वापस false;
		पूर्ण
		/* only process when valid */
		अगर (!(s1 & TXS_V))
			अवरोध;

		s2 = bcma_पढ़ो32(core, D11REGOFFS(frmtxstatus2));
		txs->status = s1 & TXS_STATUS_MASK;
		txs->frameid = (s1 & TXS_FID_MASK) >> TXS_FID_SHIFT;
		txs->sequence = s2 & TXS_SEQ_MASK;
		txs->phyerr = (s2 & TXS_PTX_MASK) >> TXS_PTX_SHIFT;
		txs->lasttxसमय = 0;

		*fatal = brcms_c_करोtxstatus(wlc_hw->wlc, txs);
		अगर (*fatal)
			वापस false;
		n++;
	पूर्ण

	वापस n >= max_tx_num;
पूर्ण

अटल व्योम brcms_c_tbtt(काष्ठा brcms_c_info *wlc)
अणु
	अगर (wlc->bsscfg->type == BRCMS_TYPE_ADHOC)
		/*
		 * DirFrmQ is now valid...defer setting until end
		 * of ATIM winकरोw
		 */
		wlc->qvalid |= MCMD_सूचीFRMQVAL;
पूर्ण

/* set initial host flags value */
अटल व्योम
brcms_c_mhfdef(काष्ठा brcms_c_info *wlc, u16 *mhfs, u16 mhf2_init)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;

	स_रखो(mhfs, 0, MHFMAX * माप(u16));

	mhfs[MHF2] |= mhf2_init;

	/* prohibit use of slowघड़ी on multअगरunction boards */
	अगर (wlc_hw->boardflags & BFL_NOPLLDOWN)
		mhfs[MHF1] |= MHF1_FORCEFASTCLK;

	अगर (BRCMS_ISNPHY(wlc_hw->band) && NREV_LT(wlc_hw->band->phyrev, 2)) अणु
		mhfs[MHF2] |= MHF2_NPHY40MHZ_WAR;
		mhfs[MHF1] |= MHF1_IQSWAP_WAR;
	पूर्ण
पूर्ण

अटल uपूर्णांक
dmareg(uपूर्णांक direction, uपूर्णांक fअगरonum)
अणु
	अगर (direction == DMA_TX)
		वापस दुरत्व(काष्ठा d11regs, fअगरo64regs[fअगरonum].dmaxmt);
	वापस दुरत्व(काष्ठा d11regs, fअगरo64regs[fअगरonum].dmarcv);
पूर्ण

अटल bool brcms_b_attach_dmapio(काष्ठा brcms_c_info *wlc, uपूर्णांक j, bool wme)
अणु
	uपूर्णांक i;
	अक्षर name[8];
	/*
	 * ucode host flag 2 needed क्रम pio mode, independent of band and fअगरo
	 */
	u16 pio_mhf2 = 0;
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	uपूर्णांक unit = wlc_hw->unit;

	/* name and offsets क्रम dma_attach */
	snम_लिखो(name, माप(name), "wl%d", unit);

	अगर (wlc_hw->di[0] == शून्य) अणु	/* Init FIFOs */
		पूर्णांक dma_attach_err = 0;

		/*
		 * FIFO 0
		 * TX: TX_AC_BK_FIFO (TX AC Background data packets)
		 * RX: RX_FIFO (RX data packets)
		 */
		wlc_hw->di[0] = dma_attach(name, wlc,
					   (wme ? dmareg(DMA_TX, 0) : 0),
					   dmareg(DMA_RX, 0),
					   (wme ? NTXD : 0), NRXD,
					   RXBUFSZ, -1, NRXBUFPOST,
					   BRCMS_HWRXOFF);
		dma_attach_err |= (शून्य == wlc_hw->di[0]);

		/*
		 * FIFO 1
		 * TX: TX_AC_BE_FIFO (TX AC Best-Efक्रमt data packets)
		 *   (legacy) TX_DATA_FIFO (TX data packets)
		 * RX: UNUSED
		 */
		wlc_hw->di[1] = dma_attach(name, wlc,
					   dmareg(DMA_TX, 1), 0,
					   NTXD, 0, 0, -1, 0, 0);
		dma_attach_err |= (शून्य == wlc_hw->di[1]);

		/*
		 * FIFO 2
		 * TX: TX_AC_VI_FIFO (TX AC Video data packets)
		 * RX: UNUSED
		 */
		wlc_hw->di[2] = dma_attach(name, wlc,
					   dmareg(DMA_TX, 2), 0,
					   NTXD, 0, 0, -1, 0, 0);
		dma_attach_err |= (शून्य == wlc_hw->di[2]);
		/*
		 * FIFO 3
		 * TX: TX_AC_VO_FIFO (TX AC Voice data packets)
		 *   (legacy) TX_CTL_FIFO (TX control & mgmt packets)
		 */
		wlc_hw->di[3] = dma_attach(name, wlc,
					   dmareg(DMA_TX, 3),
					   0, NTXD, 0, 0, -1,
					   0, 0);
		dma_attach_err |= (शून्य == wlc_hw->di[3]);
/* Cleaner to leave this as अगर with AP defined */

		अगर (dma_attach_err) अणु
			brcms_err(wlc_hw->d11core,
				  "wl%d: wlc_attach: dma_attach failed\n",
				  unit);
			वापस false;
		पूर्ण

		/* get poपूर्णांकer to dma engine tx flow control variable */
		क्रम (i = 0; i < NFIFO; i++)
			अगर (wlc_hw->di[i])
				wlc_hw->txavail[i] =
				    (uपूर्णांक *) dma_getvar(wlc_hw->di[i],
							"&txavail");
	पूर्ण

	/* initial ucode host flags */
	brcms_c_mhfdef(wlc, wlc_hw->band->mhfs, pio_mhf2);

	वापस true;
पूर्ण

अटल व्योम brcms_b_detach_dmapio(काष्ठा brcms_hardware *wlc_hw)
अणु
	uपूर्णांक j;

	क्रम (j = 0; j < NFIFO; j++) अणु
		अगर (wlc_hw->di[j]) अणु
			dma_detach(wlc_hw->di[j]);
			wlc_hw->di[j] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Initialize brcms_c_info शेष values ...
 * may get overrides later in this function
 *  BMAC_NOTES, move low out and resolve the dangling ones
 */
अटल व्योम brcms_b_info_init(काष्ठा brcms_hardware *wlc_hw)
अणु
	काष्ठा brcms_c_info *wlc = wlc_hw->wlc;

	/* set शेष sw macपूर्णांकmask value */
	wlc->defmacपूर्णांकmask = DEF_MACINTMASK;

	/* various 802.11g modes */
	wlc_hw->लघुslot = false;

	wlc_hw->SFBL = RETRY_SHORT_FB;
	wlc_hw->LFBL = RETRY_LONG_FB;

	/* शेष mac retry limits */
	wlc_hw->SRL = RETRY_SHORT_DEF;
	wlc_hw->LRL = RETRY_LONG_DEF;
	wlc_hw->chanspec = ch20mhz_chspec(1);
पूर्ण

अटल व्योम brcms_b_रुको_क्रम_wake(काष्ठा brcms_hardware *wlc_hw)
अणु
	/* delay beक्रमe first पढ़ो of ucode state */
	udelay(40);

	/* रुको until ucode is no दीर्घer asleep */
	SPINWAIT((brcms_b_पढ़ो_shm(wlc_hw, M_UCODE_DBGST) ==
		  DBGST_ASLEEP), wlc_hw->wlc->fastpwrup_dly);
पूर्ण

/* control chip घड़ी to save घातer, enable dynamic घड़ी or क्रमce fast घड़ी */
अटल व्योम brcms_b_clkctl_clk(काष्ठा brcms_hardware *wlc_hw, क्रमागत bcma_clkmode mode)
अणु
	अगर (ai_get_cccaps(wlc_hw->sih) & CC_CAP_PMU) अणु
		/* new chips with PMU, CCS_FORCEHT will distribute the HT घड़ी
		 * on backplane, but mac core will still run on ALP(not HT) when
		 * it enters घातersave mode, which means the FCA bit may not be
		 * set. Should wakeup mac अगर driver wants it to run on HT.
		 */

		अगर (wlc_hw->clk) अणु
			अगर (mode == BCMA_CLKMODE_FAST) अणु
				bcma_set32(wlc_hw->d11core,
					   D11REGOFFS(clk_ctl_st),
					   CCS_FORCEHT);

				udelay(64);

				SPINWAIT(
				    ((bcma_पढ़ो32(wlc_hw->d11core,
				      D11REGOFFS(clk_ctl_st)) &
				      CCS_HTAVAIL) == 0),
				      PMU_MAX_TRANSITION_DLY);
				WARN_ON(!(bcma_पढ़ो32(wlc_hw->d11core,
					D11REGOFFS(clk_ctl_st)) &
					CCS_HTAVAIL));
			पूर्ण अन्यथा अणु
				अगर ((ai_get_pmurev(wlc_hw->sih) == 0) &&
				    (bcma_पढ़ो32(wlc_hw->d11core,
					D11REGOFFS(clk_ctl_st)) &
					(CCS_FORCEHT | CCS_HTAREQ)))
					SPINWAIT(
					    ((bcma_पढ़ो32(wlc_hw->d11core,
					      दुरत्व(काष्ठा d11regs,
						       clk_ctl_st)) &
					      CCS_HTAVAIL) == 0),
					      PMU_MAX_TRANSITION_DLY);
				bcma_mask32(wlc_hw->d11core,
					D11REGOFFS(clk_ctl_st),
					~CCS_FORCEHT);
			पूर्ण
		पूर्ण
		wlc_hw->क्रमcefastclk = (mode == BCMA_CLKMODE_FAST);
	पूर्ण अन्यथा अणु

		/* old chips w/o PMU, क्रमce HT through cc,
		 * then use FCA to verअगरy mac is running fast घड़ी
		 */

		wlc_hw->क्रमcefastclk = ai_clkctl_cc(wlc_hw->sih, mode);

		/* check fast घड़ी is available (अगर core is not in reset) */
		अगर (wlc_hw->क्रमcefastclk && wlc_hw->clk)
			WARN_ON(!(bcma_aपढ़ो32(wlc_hw->d11core, BCMA_IOST) &
				  SISF_FCLKA));

		/*
		 * keep the ucode wake bit on अगर क्रमcefastclk is on since we
		 * करो not want ucode to put us back to slow घड़ी when it करोzes
		 * क्रम PM mode. Code below matches the wake override bit with
		 * current क्रमcefastclk state. Only setting bit in wake_override
		 * instead of waking ucode immediately since old code had this
		 * behavior. Older code set wlc->क्रमcefastclk but only had the
		 * wake happen अगर the wakup_ucode work (रक्षित by an up
		 * check) was executed just below.
		 */
		अगर (wlc_hw->क्रमcefastclk)
			mboolset(wlc_hw->wake_override,
				 BRCMS_WAKE_OVERRIDE_FORCEFAST);
		अन्यथा
			mboolclr(wlc_hw->wake_override,
				 BRCMS_WAKE_OVERRIDE_FORCEFAST);
	पूर्ण
पूर्ण

/* set or clear ucode host flag bits
 * it has an optimization क्रम no-change ग_लिखो
 * it only ग_लिखोs through shared memory when the core has घड़ी;
 * pre-CLK changes should use wlc_ग_लिखो_mhf to get around the optimization
 *
 *
 * bands values are: BRCM_BAND_AUTO <--- Current band only
 *                   BRCM_BAND_5G   <--- 5G band only
 *                   BRCM_BAND_2G   <--- 2G band only
 *                   BRCM_BAND_ALL  <--- All bands
 */
व्योम
brcms_b_mhf(काष्ठा brcms_hardware *wlc_hw, u8 idx, u16 mask, u16 val,
	     पूर्णांक bands)
अणु
	u16 save;
	u16 addr[MHFMAX] = अणु
		M_HOST_FLAGS1, M_HOST_FLAGS2, M_HOST_FLAGS3, M_HOST_FLAGS4,
		M_HOST_FLAGS5
	पूर्ण;
	काष्ठा brcms_hw_band *band;

	अगर ((val & ~mask) || idx >= MHFMAX)
		वापस; /* error condition */

	चयन (bands) अणु
		/* Current band only or all bands,
		 * then set the band to current band
		 */
	हाल BRCM_BAND_AUTO:
	हाल BRCM_BAND_ALL:
		band = wlc_hw->band;
		अवरोध;
	हाल BRCM_BAND_5G:
		band = wlc_hw->bandstate[BAND_5G_INDEX];
		अवरोध;
	हाल BRCM_BAND_2G:
		band = wlc_hw->bandstate[BAND_2G_INDEX];
		अवरोध;
	शेष:
		band = शून्य;	/* error condition */
	पूर्ण

	अगर (band) अणु
		save = band->mhfs[idx];
		band->mhfs[idx] = (band->mhfs[idx] & ~mask) | val;

		/* optimization: only ग_लिखो through अगर changed, and
		 * changed band is the current band
		 */
		अगर (wlc_hw->clk && (band->mhfs[idx] != save)
		    && (band == wlc_hw->band))
			brcms_b_ग_लिखो_shm(wlc_hw, addr[idx],
					   (u16) band->mhfs[idx]);
	पूर्ण

	अगर (bands == BRCM_BAND_ALL) अणु
		wlc_hw->bandstate[0]->mhfs[idx] =
		    (wlc_hw->bandstate[0]->mhfs[idx] & ~mask) | val;
		wlc_hw->bandstate[1]->mhfs[idx] =
		    (wlc_hw->bandstate[1]->mhfs[idx] & ~mask) | val;
	पूर्ण
पूर्ण

/* set the maccontrol रेजिस्टर to desired reset state and
 * initialize the sw cache of the रेजिस्टर
 */
अटल व्योम brcms_c_mctrl_reset(काष्ठा brcms_hardware *wlc_hw)
अणु
	/* IHR accesses are always enabled, PSM disabled, HPS off and WAKE on */
	wlc_hw->maccontrol = 0;
	wlc_hw->suspended_fअगरos = 0;
	wlc_hw->wake_override = 0;
	wlc_hw->mute_override = 0;
	brcms_b_mctrl(wlc_hw, ~0, MCTL_IHR_EN | MCTL_WAKE);
पूर्ण

/*
 * ग_लिखो the software state of maccontrol and
 * overrides to the maccontrol रेजिस्टर
 */
अटल व्योम brcms_c_mctrl_ग_लिखो(काष्ठा brcms_hardware *wlc_hw)
अणु
	u32 maccontrol = wlc_hw->maccontrol;

	/* OR in the wake bit अगर overridden */
	अगर (wlc_hw->wake_override)
		maccontrol |= MCTL_WAKE;

	/* set AP and INFRA bits क्रम mute अगर needed */
	अगर (wlc_hw->mute_override) अणु
		maccontrol &= ~(MCTL_AP);
		maccontrol |= MCTL_INFRA;
	पूर्ण

	bcma_ग_लिखो32(wlc_hw->d11core, D11REGOFFS(maccontrol),
		     maccontrol);
पूर्ण

/* set or clear maccontrol bits */
व्योम brcms_b_mctrl(काष्ठा brcms_hardware *wlc_hw, u32 mask, u32 val)
अणु
	u32 maccontrol;
	u32 new_maccontrol;

	अगर (val & ~mask)
		वापस; /* error condition */
	maccontrol = wlc_hw->maccontrol;
	new_maccontrol = (maccontrol & ~mask) | val;

	/* अगर the new maccontrol value is the same as the old, nothing to करो */
	अगर (new_maccontrol == maccontrol)
		वापस;

	/* something changed, cache the new value */
	wlc_hw->maccontrol = new_maccontrol;

	/* ग_लिखो the new values with overrides applied */
	brcms_c_mctrl_ग_लिखो(wlc_hw);
पूर्ण

व्योम brcms_c_ucode_wake_override_set(काष्ठा brcms_hardware *wlc_hw,
				 u32 override_bit)
अणु
	अगर (wlc_hw->wake_override || (wlc_hw->maccontrol & MCTL_WAKE)) अणु
		mboolset(wlc_hw->wake_override, override_bit);
		वापस;
	पूर्ण

	mboolset(wlc_hw->wake_override, override_bit);

	brcms_c_mctrl_ग_लिखो(wlc_hw);
	brcms_b_रुको_क्रम_wake(wlc_hw);
पूर्ण

व्योम brcms_c_ucode_wake_override_clear(काष्ठा brcms_hardware *wlc_hw,
				   u32 override_bit)
अणु
	mboolclr(wlc_hw->wake_override, override_bit);

	अगर (wlc_hw->wake_override || (wlc_hw->maccontrol & MCTL_WAKE))
		वापस;

	brcms_c_mctrl_ग_लिखो(wlc_hw);
पूर्ण

/* When driver needs ucode to stop beaconing, it has to make sure that
 * MCTL_AP is clear and MCTL_INFRA is set
 * Mode           MCTL_AP        MCTL_INFRA
 * AP                1              1
 * STA               0              1 <--- This will ensure no beacons
 * IBSS              0              0
 */
अटल व्योम brcms_c_ucode_mute_override_set(काष्ठा brcms_hardware *wlc_hw)
अणु
	wlc_hw->mute_override = 1;

	/* अगर maccontrol alपढ़ोy has AP == 0 and INFRA == 1 without this
	 * override, then there is no change to ग_लिखो
	 */
	अगर ((wlc_hw->maccontrol & (MCTL_AP | MCTL_INFRA)) == MCTL_INFRA)
		वापस;

	brcms_c_mctrl_ग_लिखो(wlc_hw);
पूर्ण

/* Clear the override on AP and INFRA bits */
अटल व्योम brcms_c_ucode_mute_override_clear(काष्ठा brcms_hardware *wlc_hw)
अणु
	अगर (wlc_hw->mute_override == 0)
		वापस;

	wlc_hw->mute_override = 0;

	/* अगर maccontrol alपढ़ोy has AP == 0 and INFRA == 1 without this
	 * override, then there is no change to ग_लिखो
	 */
	अगर ((wlc_hw->maccontrol & (MCTL_AP | MCTL_INFRA)) == MCTL_INFRA)
		वापस;

	brcms_c_mctrl_ग_लिखो(wlc_hw);
पूर्ण

/*
 * Write a MAC address to the given match reg offset in the RXE match engine.
 */
अटल व्योम
brcms_b_set_addrmatch(काष्ठा brcms_hardware *wlc_hw, पूर्णांक match_reg_offset,
		       स्थिर u8 *addr)
अणु
	काष्ठा bcma_device *core = wlc_hw->d11core;
	u16 mac_l;
	u16 mac_m;
	u16 mac_h;

	brcms_dbg_rx(core, "wl%d: brcms_b_set_addrmatch\n", wlc_hw->unit);

	mac_l = addr[0] | (addr[1] << 8);
	mac_m = addr[2] | (addr[3] << 8);
	mac_h = addr[4] | (addr[5] << 8);

	/* enter the MAC addr पूर्णांकo the RXE match रेजिस्टरs */
	bcma_ग_लिखो16(core, D11REGOFFS(rcm_ctl),
		     RCM_INC_DATA | match_reg_offset);
	bcma_ग_लिखो16(core, D11REGOFFS(rcm_mat_data), mac_l);
	bcma_ग_लिखो16(core, D11REGOFFS(rcm_mat_data), mac_m);
	bcma_ग_लिखो16(core, D11REGOFFS(rcm_mat_data), mac_h);
पूर्ण

व्योम
brcms_b_ग_लिखो_ढाँचा_ram(काष्ठा brcms_hardware *wlc_hw, पूर्णांक offset, पूर्णांक len,
			    व्योम *buf)
अणु
	काष्ठा bcma_device *core = wlc_hw->d11core;
	u32 word;
	__le32 word_le;
	__be32 word_be;
	bool be_bit;
	brcms_dbg_info(core, "wl%d\n", wlc_hw->unit);

	bcma_ग_लिखो32(core, D11REGOFFS(tplatewrptr), offset);

	/* अगर MCTL_BIGEND bit set in mac control रेजिस्टर,
	 * the chip swaps data in fअगरo, as well as data in
	 * ढाँचा ram
	 */
	be_bit = (bcma_पढ़ो32(core, D11REGOFFS(maccontrol)) & MCTL_BIGEND) != 0;

	जबतक (len > 0) अणु
		स_नकल(&word, buf, माप(u32));

		अगर (be_bit) अणु
			word_be = cpu_to_be32(word);
			word = *(u32 *)&word_be;
		पूर्ण अन्यथा अणु
			word_le = cpu_to_le32(word);
			word = *(u32 *)&word_le;
		पूर्ण

		bcma_ग_लिखो32(core, D11REGOFFS(tplatewrdata), word);

		buf = (u8 *) buf + माप(u32);
		len -= माप(u32);
	पूर्ण
पूर्ण

अटल व्योम brcms_b_set_cwmin(काष्ठा brcms_hardware *wlc_hw, u16 newmin)
अणु
	wlc_hw->band->CWmin = newmin;

	bcma_ग_लिखो32(wlc_hw->d11core, D11REGOFFS(objaddr),
		     OBJADDR_SCR_SEL | S_DOT11_CWMIN);
	(व्योम)bcma_पढ़ो32(wlc_hw->d11core, D11REGOFFS(objaddr));
	bcma_ग_लिखो32(wlc_hw->d11core, D11REGOFFS(objdata), newmin);
पूर्ण

अटल व्योम brcms_b_set_cwmax(काष्ठा brcms_hardware *wlc_hw, u16 newmax)
अणु
	wlc_hw->band->CWmax = newmax;

	bcma_ग_लिखो32(wlc_hw->d11core, D11REGOFFS(objaddr),
		     OBJADDR_SCR_SEL | S_DOT11_CWMAX);
	(व्योम)bcma_पढ़ो32(wlc_hw->d11core, D11REGOFFS(objaddr));
	bcma_ग_लिखो32(wlc_hw->d11core, D11REGOFFS(objdata), newmax);
पूर्ण

व्योम brcms_b_bw_set(काष्ठा brcms_hardware *wlc_hw, u16 bw)
अणु
	bool fastclk;

	/* request FAST घड़ी अगर not on */
	fastclk = wlc_hw->क्रमcefastclk;
	अगर (!fastclk)
		brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_FAST);

	wlc_phy_bw_state_set(wlc_hw->band->pi, bw);

	brcms_b_phy_reset(wlc_hw);
	wlc_phy_init(wlc_hw->band->pi, wlc_phy_chanspec_get(wlc_hw->band->pi));

	/* restore the clk */
	अगर (!fastclk)
		brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_DYNAMIC);
पूर्ण

अटल व्योम brcms_b_upd_synthpu(काष्ठा brcms_hardware *wlc_hw)
अणु
	u16 v;
	काष्ठा brcms_c_info *wlc = wlc_hw->wlc;
	/* update SYNTHPU_DLY */

	अगर (BRCMS_ISLCNPHY(wlc->band))
		v = SYNTHPU_DLY_LPPHY_US;
	अन्यथा अगर (BRCMS_ISNPHY(wlc->band) && (NREV_GE(wlc->band->phyrev, 3)))
		v = SYNTHPU_DLY_NPHY_US;
	अन्यथा
		v = SYNTHPU_DLY_BPHY_US;

	brcms_b_ग_लिखो_shm(wlc_hw, M_SYNTHPU_DLY, v);
पूर्ण

अटल व्योम brcms_c_ucode_txant_set(काष्ठा brcms_hardware *wlc_hw)
अणु
	u16 phyctl;
	u16 phytxant = wlc_hw->bmac_phytxant;
	u16 mask = PHY_TXC_ANT_MASK;

	/* set the Probe Response frame phy control word */
	phyctl = brcms_b_पढ़ो_shm(wlc_hw, M_CTXPRS_BLK + C_CTX_PCTLWD_POS);
	phyctl = (phyctl & ~mask) | phytxant;
	brcms_b_ग_लिखो_shm(wlc_hw, M_CTXPRS_BLK + C_CTX_PCTLWD_POS, phyctl);

	/* set the Response (ACK/CTS) frame phy control word */
	phyctl = brcms_b_पढ़ो_shm(wlc_hw, M_RSP_PCTLWD);
	phyctl = (phyctl & ~mask) | phytxant;
	brcms_b_ग_लिखो_shm(wlc_hw, M_RSP_PCTLWD, phyctl);
पूर्ण

अटल u16 brcms_b_ofdm_ratetable_offset(काष्ठा brcms_hardware *wlc_hw,
					 u8 rate)
अणु
	uपूर्णांक i;
	u8 plcp_rate = 0;
	काष्ठा plcp_संकेत_rate_lookup अणु
		u8 rate;
		u8 संकेत_rate;
	पूर्ण;
	/* OFDM RATE sub-field of PLCP SIGNAL field, per 802.11 sec 17.3.4.1 */
	स्थिर काष्ठा plcp_संकेत_rate_lookup rate_lookup[] = अणु
		अणुBRCM_RATE_6M, 0xBपूर्ण,
		अणुBRCM_RATE_9M, 0xFपूर्ण,
		अणुBRCM_RATE_12M, 0xAपूर्ण,
		अणुBRCM_RATE_18M, 0xEपूर्ण,
		अणुBRCM_RATE_24M, 0x9पूर्ण,
		अणुBRCM_RATE_36M, 0xDपूर्ण,
		अणुBRCM_RATE_48M, 0x8पूर्ण,
		अणुBRCM_RATE_54M, 0xCपूर्ण
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(rate_lookup); i++) अणु
		अगर (rate == rate_lookup[i].rate) अणु
			plcp_rate = rate_lookup[i].संकेत_rate;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Find the SHM poपूर्णांकer to the rate table entry by looking in the
	 * Direct-map Table
	 */
	वापस 2 * brcms_b_पढ़ो_shm(wlc_hw, M_RT_सूचीMAP_A + (plcp_rate * 2));
पूर्ण

अटल व्योम brcms_upd_ofdm_pctl1_table(काष्ठा brcms_hardware *wlc_hw)
अणु
	u8 rate;
	u8 rates[8] = अणु
		BRCM_RATE_6M, BRCM_RATE_9M, BRCM_RATE_12M, BRCM_RATE_18M,
		BRCM_RATE_24M, BRCM_RATE_36M, BRCM_RATE_48M, BRCM_RATE_54M
	पूर्ण;
	u16 entry_ptr;
	u16 pctl1;
	uपूर्णांक i;

	अगर (!BRCMS_PHY_11N_CAP(wlc_hw->band))
		वापस;

	/* walk the phy rate table and update the entries */
	क्रम (i = 0; i < ARRAY_SIZE(rates); i++) अणु
		rate = rates[i];

		entry_ptr = brcms_b_ofdm_ratetable_offset(wlc_hw, rate);

		/* पढ़ो the SHM Rate Table entry OFDM PCTL1 values */
		pctl1 =
		    brcms_b_पढ़ो_shm(wlc_hw, entry_ptr + M_RT_OFDM_PCTL1_POS);

		/* modअगरy the value */
		pctl1 &= ~PHY_TXC1_MODE_MASK;
		pctl1 |= (wlc_hw->hw_stf_ss_opmode << PHY_TXC1_MODE_SHIFT);

		/* Update the SHM Rate Table entry OFDM PCTL1 values */
		brcms_b_ग_लिखो_shm(wlc_hw, entry_ptr + M_RT_OFDM_PCTL1_POS,
				   pctl1);
	पूर्ण
पूर्ण

/* band-specअगरic init */
अटल व्योम brcms_b_bsinit(काष्ठा brcms_c_info *wlc, u16 chanspec)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;

	brcms_dbg_mac80211(wlc_hw->d11core, "wl%d: bandunit %d\n", wlc_hw->unit,
			   wlc_hw->band->bandunit);

	brcms_c_ucode_bsinit(wlc_hw);

	wlc_phy_init(wlc_hw->band->pi, chanspec);

	brcms_c_ucode_txant_set(wlc_hw);

	/*
	 * cwmin is band-specअगरic, update hardware
	 * with value क्रम current band
	 */
	brcms_b_set_cwmin(wlc_hw, wlc_hw->band->CWmin);
	brcms_b_set_cwmax(wlc_hw, wlc_hw->band->CWmax);

	brcms_b_update_slot_timing(wlc_hw,
				   wlc_hw->band->bandtype == BRCM_BAND_5G ?
				   true : wlc_hw->लघुslot);

	/* ग_लिखो phytype and phyvers */
	brcms_b_ग_लिखो_shm(wlc_hw, M_PHYTYPE, (u16) wlc_hw->band->phytype);
	brcms_b_ग_लिखो_shm(wlc_hw, M_PHYVER, (u16) wlc_hw->band->phyrev);

	/*
	 * initialize the txphyctl1 rate table since
	 * shmem is shared between bands
	 */
	brcms_upd_ofdm_pctl1_table(wlc_hw);

	brcms_b_upd_synthpu(wlc_hw);
पूर्ण

/* Perक्रमm a soft reset of the PHY PLL */
व्योम brcms_b_core_phypll_reset(काष्ठा brcms_hardware *wlc_hw)
अणु
	ai_cc_reg(wlc_hw->sih, दुरत्व(काष्ठा chipcregs, chipcontrol_addr),
		  ~0, 0);
	udelay(1);
	ai_cc_reg(wlc_hw->sih, दुरत्व(काष्ठा chipcregs, chipcontrol_data),
		  0x4, 0);
	udelay(1);
	ai_cc_reg(wlc_hw->sih, दुरत्व(काष्ठा chipcregs, chipcontrol_data),
		  0x4, 4);
	udelay(1);
	ai_cc_reg(wlc_hw->sih, दुरत्व(काष्ठा chipcregs, chipcontrol_data),
		  0x4, 0);
	udelay(1);
पूर्ण

/* light way to turn on phy घड़ी without reset क्रम NPHY only
 *  refer to brcms_b_core_phy_clk क्रम full version
 */
व्योम brcms_b_phyclk_fgc(काष्ठा brcms_hardware *wlc_hw, bool clk)
अणु
	/* support(necessary क्रम NPHY and HYPHY) only */
	अगर (!BRCMS_ISNPHY(wlc_hw->band))
		वापस;

	अगर (ON == clk)
		brcms_b_core_ioctl(wlc_hw, SICF_FGC, SICF_FGC);
	अन्यथा
		brcms_b_core_ioctl(wlc_hw, SICF_FGC, 0);

पूर्ण

व्योम brcms_b_macphyclk_set(काष्ठा brcms_hardware *wlc_hw, bool clk)
अणु
	अगर (ON == clk)
		brcms_b_core_ioctl(wlc_hw, SICF_MPCLKE, SICF_MPCLKE);
	अन्यथा
		brcms_b_core_ioctl(wlc_hw, SICF_MPCLKE, 0);
पूर्ण

व्योम brcms_b_phy_reset(काष्ठा brcms_hardware *wlc_hw)
अणु
	काष्ठा brcms_phy_pub *pih = wlc_hw->band->pi;
	u32 phy_bw_clkbits;

	brcms_dbg_info(wlc_hw->d11core, "wl%d: reset phy\n", wlc_hw->unit);

	अगर (pih == शून्य)
		वापस;

	phy_bw_clkbits = wlc_phy_clk_bwbits(wlc_hw->band->pi);

	/* Specअगरic reset sequence required क्रम NPHY rev 3 and 4 */
	अगर (BRCMS_ISNPHY(wlc_hw->band) && NREV_GE(wlc_hw->band->phyrev, 3) &&
	    NREV_LE(wlc_hw->band->phyrev, 4)) अणु
		/* Set the PHY bandwidth */
		brcms_b_core_ioctl(wlc_hw, SICF_BWMASK, phy_bw_clkbits);

		udelay(1);

		/* Perक्रमm a soft reset of the PHY PLL */
		brcms_b_core_phypll_reset(wlc_hw);

		/* reset the PHY */
		brcms_b_core_ioctl(wlc_hw, (SICF_PRST | SICF_PCLKE),
				   (SICF_PRST | SICF_PCLKE));
	पूर्ण अन्यथा अणु
		brcms_b_core_ioctl(wlc_hw,
				   (SICF_PRST | SICF_PCLKE | SICF_BWMASK),
				   (SICF_PRST | SICF_PCLKE | phy_bw_clkbits));
	पूर्ण

	udelay(2);
	brcms_b_core_phy_clk(wlc_hw, ON);

	wlc_phy_anacore(pih, ON);
पूर्ण

/* चयन to and initialize new band */
अटल व्योम brcms_b_setband(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक bandunit,
			    u16 chanspec) अणु
	काष्ठा brcms_c_info *wlc = wlc_hw->wlc;
	u32 macपूर्णांकmask;

	/* Enable the d11 core beक्रमe accessing it */
	अगर (!bcma_core_is_enabled(wlc_hw->d11core)) अणु
		bcma_core_enable(wlc_hw->d11core, 0);
		brcms_c_mctrl_reset(wlc_hw);
	पूर्ण

	macपूर्णांकmask = brcms_c_setband_inact(wlc, bandunit);

	अगर (!wlc_hw->up)
		वापस;

	brcms_b_core_phy_clk(wlc_hw, ON);

	/* band-specअगरic initializations */
	brcms_b_bsinit(wlc, chanspec);

	/*
	 * If there are any pending software पूर्णांकerrupt bits,
	 * then replace these with a harmless nonzero value
	 * so brcms_c_dpc() will re-enable पूर्णांकerrupts when करोne.
	 */
	अगर (wlc->macपूर्णांकstatus)
		wlc->macपूर्णांकstatus = MI_DMAINT;

	/* restore macपूर्णांकmask */
	brcms_पूर्णांकrsrestore(wlc->wl, macपूर्णांकmask);

	/* ucode should still be suspended.. */
	WARN_ON((bcma_पढ़ो32(wlc_hw->d11core, D11REGOFFS(maccontrol)) &
		 MCTL_EN_MAC) != 0);
पूर्ण

अटल bool brcms_c_isgoodchip(काष्ठा brcms_hardware *wlc_hw)
अणु

	/* reject unsupported corerev */
	अगर (!CONF_HAS(D11CONF, wlc_hw->corerev)) अणु
		wiphy_err(wlc_hw->wlc->wiphy, "unsupported core rev %d\n",
			  wlc_hw->corerev);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Validate some board info parameters */
अटल bool brcms_c_validboardtype(काष्ठा brcms_hardware *wlc_hw)
अणु
	uपूर्णांक boardrev = wlc_hw->boardrev;

	/* 4 bits each क्रम board type, major, minor, and tiny version */
	uपूर्णांक brt = (boardrev & 0xf000) >> 12;
	uपूर्णांक b0 = (boardrev & 0xf00) >> 8;
	uपूर्णांक b1 = (boardrev & 0xf0) >> 4;
	uपूर्णांक b2 = boardrev & 0xf;

	/* voards from other venकरोrs are always considered valid */
	अगर (ai_get_boardvenकरोr(wlc_hw->sih) != PCI_VENDOR_ID_BROADCOM)
		वापस true;

	/* करो some boardrev sanity checks when boardvenकरोr is Broadcom */
	अगर (boardrev == 0)
		वापस false;

	अगर (boardrev <= 0xff)
		वापस true;

	अगर ((brt > 2) || (brt == 0) || (b0 > 9) || (b0 == 0) || (b1 > 9)
		|| (b2 > 9))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम brcms_c_get_macaddr(काष्ठा brcms_hardware *wlc_hw, u8 etheraddr[ETH_ALEN])
अणु
	काष्ठा ssb_sprom *sprom = &wlc_hw->d11core->bus->sprom;

	/* If macaddr exists, use it (Sromrev4, CIS, ...). */
	अगर (!is_zero_ether_addr(sprom->il0mac)) अणु
		स_नकल(etheraddr, sprom->il0mac, ETH_ALEN);
		वापस;
	पूर्ण

	अगर (wlc_hw->_nbands > 1)
		स_नकल(etheraddr, sprom->et1mac, ETH_ALEN);
	अन्यथा
		स_नकल(etheraddr, sprom->il0mac, ETH_ALEN);
पूर्ण

/* घातer both the pll and बाह्यal oscillator on/off */
अटल व्योम brcms_b_xtal(काष्ठा brcms_hardware *wlc_hw, bool want)
अणु
	brcms_dbg_info(wlc_hw->d11core, "wl%d: want %d\n", wlc_hw->unit, want);

	/*
	 * करोnt घातer करोwn अगर pllकरोwn is false or
	 * we must poll hw radio disable
	 */
	अगर (!want && wlc_hw->pllreq)
		वापस;

	wlc_hw->sbclk = want;
	अगर (!wlc_hw->sbclk) अणु
		wlc_hw->clk = false;
		अगर (wlc_hw->band && wlc_hw->band->pi)
			wlc_phy_hw_clk_state_upd(wlc_hw->band->pi, false);
	पूर्ण
पूर्ण

/*
 * Return true अगर radio is disabled, otherwise false.
 * hw radio disable संकेत is an बाह्यal pin, users activate it asynchronously
 * this function could be called when driver is करोwn and w/o घड़ी
 * it operates on dअगरferent रेजिस्टरs depending on corerev and boardflag.
 */
अटल bool brcms_b_radio_पढ़ो_hwdisabled(काष्ठा brcms_hardware *wlc_hw)
अणु
	bool v, clk, xtal;
	u32 flags = 0;

	xtal = wlc_hw->sbclk;
	अगर (!xtal)
		brcms_b_xtal(wlc_hw, ON);

	/* may need to take core out of reset first */
	clk = wlc_hw->clk;
	अगर (!clk) अणु
		/*
		 * mac no दीर्घer enables phyclk स्वतःmatically when driver
		 * accesses phyreg throughput mac. This can be skipped since
		 * only mac reg is accessed below
		 */
		अगर (D11REV_GE(wlc_hw->corerev, 18))
			flags |= SICF_PCLKE;

		/*
		 * TODO: test suspend/resume
		 *
		 * AI chip करोesn't restore bar0win2 on
		 * hibernation/resume, need sw fixup
		 */

		bcma_core_enable(wlc_hw->d11core, flags);
		brcms_c_mctrl_reset(wlc_hw);
	पूर्ण

	v = ((bcma_पढ़ो32(wlc_hw->d11core,
			  D11REGOFFS(phydebug)) & PDBG_RFD) != 0);

	/* put core back पूर्णांकo reset */
	अगर (!clk)
		bcma_core_disable(wlc_hw->d11core, 0);

	अगर (!xtal)
		brcms_b_xtal(wlc_hw, OFF);

	वापस v;
पूर्ण

अटल bool wlc_dma_rxreset(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक fअगरo)
अणु
	काष्ठा dma_pub *di = wlc_hw->di[fअगरo];
	वापस dma_rxreset(di);
पूर्ण

/* d11 core reset
 *   ensure fask घड़ी during reset
 *   reset dma
 *   reset d11(out of reset)
 *   reset phy(out of reset)
 *   clear software macपूर्णांकstatus क्रम fresh new start
 * one testing hack wlc_hw->noreset will bypass the d11/phy reset
 */
व्योम brcms_b_corereset(काष्ठा brcms_hardware *wlc_hw, u32 flags)
अणु
	uपूर्णांक i;
	bool fastclk;

	अगर (flags == BRCMS_USE_COREFLAGS)
		flags = (wlc_hw->band->pi ? wlc_hw->band->core_flags : 0);

	brcms_dbg_info(wlc_hw->d11core, "wl%d: core reset\n", wlc_hw->unit);

	/* request FAST घड़ी अगर not on  */
	fastclk = wlc_hw->क्रमcefastclk;
	अगर (!fastclk)
		brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_FAST);

	/* reset the dma engines except first समय thru */
	अगर (bcma_core_is_enabled(wlc_hw->d11core)) अणु
		क्रम (i = 0; i < NFIFO; i++)
			अगर ((wlc_hw->di[i]) && (!dma_txreset(wlc_hw->di[i])))
				brcms_err(wlc_hw->d11core, "wl%d: %s: "
					  "dma_txreset[%d]: cannot stop dma\n",
					   wlc_hw->unit, __func__, i);

		अगर ((wlc_hw->di[RX_FIFO])
		    && (!wlc_dma_rxreset(wlc_hw, RX_FIFO)))
			brcms_err(wlc_hw->d11core, "wl%d: %s: dma_rxreset"
				  "[%d]: cannot stop dma\n",
				  wlc_hw->unit, __func__, RX_FIFO);
	पूर्ण
	/* अगर noreset, just stop the psm and वापस */
	अगर (wlc_hw->noreset) अणु
		wlc_hw->wlc->macपूर्णांकstatus = 0;	/* skip wl_dpc after करोwn */
		brcms_b_mctrl(wlc_hw, MCTL_PSM_RUN | MCTL_EN_MAC, 0);
		वापस;
	पूर्ण

	/*
	 * mac no दीर्घer enables phyclk स्वतःmatically when driver accesses
	 * phyreg throughput mac, AND phy_reset is skipped at early stage when
	 * band->pi is invalid. need to enable PHY CLK
	 */
	अगर (D11REV_GE(wlc_hw->corerev, 18))
		flags |= SICF_PCLKE;

	/*
	 * reset the core
	 * In chips with PMU, the fastclk request goes through d11 core
	 * reg 0x1e0, which is cleared by the core_reset. have to re-request it.
	 *
	 * This adds some delay and we can optimize it by also requesting
	 * fastclk through chipcommon during this period अगर necessary. But
	 * that has to work coordinate with other driver like mips/arm since
	 * they may touch chipcommon as well.
	 */
	wlc_hw->clk = false;
	bcma_core_enable(wlc_hw->d11core, flags);
	wlc_hw->clk = true;
	अगर (wlc_hw->band && wlc_hw->band->pi)
		wlc_phy_hw_clk_state_upd(wlc_hw->band->pi, true);

	brcms_c_mctrl_reset(wlc_hw);

	अगर (ai_get_cccaps(wlc_hw->sih) & CC_CAP_PMU)
		brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_FAST);

	brcms_b_phy_reset(wlc_hw);

	/* turn on PHY_PLL */
	brcms_b_core_phypll_ctl(wlc_hw, true);

	/* clear sw पूर्णांकstatus */
	wlc_hw->wlc->macपूर्णांकstatus = 0;

	/* restore the clk setting */
	अगर (!fastclk)
		brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_DYNAMIC);
पूर्ण

/* txfअगरo sizes needs to be modअगरied(increased) since the newer cores
 * have more memory.
 */
अटल व्योम brcms_b_corerev_fअगरofixup(काष्ठा brcms_hardware *wlc_hw)
अणु
	काष्ठा bcma_device *core = wlc_hw->d11core;
	u16 fअगरo_nu;
	u16 txfअगरo_startblk = TXFIFO_START_BLK, txfअगरo_endblk;
	u16 txfअगरo_def, txfअगरo_def1;
	u16 txfअगरo_cmd;

	/* tx fअगरos start at TXFIFO_START_BLK from the Base address */
	txfअगरo_startblk = TXFIFO_START_BLK;

	/* sequence of operations:  reset fअगरo, set fअगरo size, reset fअगरo */
	क्रम (fअगरo_nu = 0; fअगरo_nu < NFIFO; fअगरo_nu++) अणु

		txfअगरo_endblk = txfअगरo_startblk + wlc_hw->xmtfअगरo_sz[fअगरo_nu];
		txfअगरo_def = (txfअगरo_startblk & 0xff) |
		    (((txfअगरo_endblk - 1) & 0xff) << TXFIFO_FIFOTOP_SHIFT);
		txfअगरo_def1 = ((txfअगरo_startblk >> 8) & 0x1) |
		    ((((txfअगरo_endblk -
			1) >> 8) & 0x1) << TXFIFO_FIFOTOP_SHIFT);
		txfअगरo_cmd =
		    TXFIFOCMD_RESET_MASK | (fअगरo_nu << TXFIFOCMD_FIFOSEL_SHIFT);

		bcma_ग_लिखो16(core, D11REGOFFS(xmtfअगरocmd), txfअगरo_cmd);
		bcma_ग_लिखो16(core, D11REGOFFS(xmtfअगरodef), txfअगरo_def);
		bcma_ग_लिखो16(core, D11REGOFFS(xmtfअगरodef1), txfअगरo_def1);

		bcma_ग_लिखो16(core, D11REGOFFS(xmtfअगरocmd), txfअगरo_cmd);

		txfअगरo_startblk += wlc_hw->xmtfअगरo_sz[fअगरo_nu];
	पूर्ण
	/*
	 * need to propagate to shm location to be in sync since ucode/hw won't
	 * करो this
	 */
	brcms_b_ग_लिखो_shm(wlc_hw, M_FIFOSIZE0,
			   wlc_hw->xmtfअगरo_sz[TX_AC_BE_FIFO]);
	brcms_b_ग_लिखो_shm(wlc_hw, M_FIFOSIZE1,
			   wlc_hw->xmtfअगरo_sz[TX_AC_VI_FIFO]);
	brcms_b_ग_लिखो_shm(wlc_hw, M_FIFOSIZE2,
			   ((wlc_hw->xmtfअगरo_sz[TX_AC_VO_FIFO] << 8) | wlc_hw->
			    xmtfअगरo_sz[TX_AC_BK_FIFO]));
	brcms_b_ग_लिखो_shm(wlc_hw, M_FIFOSIZE3,
			   ((wlc_hw->xmtfअगरo_sz[TX_ATIM_FIFO] << 8) | wlc_hw->
			    xmtfअगरo_sz[TX_BCMC_FIFO]));
पूर्ण

/* This function is used क्रम changing the tsf frac रेजिस्टर
 * If spur aव्योमance mode is off, the mac freq will be 80/120/160Mhz
 * If spur aव्योमance mode is on1, the mac freq will be 82/123/164Mhz
 * If spur aव्योमance mode is on2, the mac freq will be 84/126/168Mhz
 * HTPHY Formula is 2^26/freq(MHz) e.g.
 * For spuron2 - 126MHz -> 2^26/126 = 532610.0
 *  - 532610 = 0x82082 => tsf_clk_frac_h = 0x8, tsf_clk_frac_l = 0x2082
 * For spuron: 123MHz -> 2^26/123    = 545600.5
 *  - 545601 = 0x85341 => tsf_clk_frac_h = 0x8, tsf_clk_frac_l = 0x5341
 * For spur off: 120MHz -> 2^26/120    = 559240.5
 *  - 559241 = 0x88889 => tsf_clk_frac_h = 0x8, tsf_clk_frac_l = 0x8889
 */

व्योम brcms_b_चयन_macfreq(काष्ठा brcms_hardware *wlc_hw, u8 spurmode)
अणु
	काष्ठा bcma_device *core = wlc_hw->d11core;

	अगर ((ai_get_chip_id(wlc_hw->sih) == BCMA_CHIP_ID_BCM43224) ||
	    (ai_get_chip_id(wlc_hw->sih) == BCMA_CHIP_ID_BCM43225)) अणु
		अगर (spurmode == WL_SPURAVOID_ON2) अणु	/* 126Mhz */
			bcma_ग_लिखो16(core, D11REGOFFS(tsf_clk_frac_l), 0x2082);
			bcma_ग_लिखो16(core, D11REGOFFS(tsf_clk_frac_h), 0x8);
		पूर्ण अन्यथा अगर (spurmode == WL_SPURAVOID_ON1) अणु	/* 123Mhz */
			bcma_ग_लिखो16(core, D11REGOFFS(tsf_clk_frac_l), 0x5341);
			bcma_ग_लिखो16(core, D11REGOFFS(tsf_clk_frac_h), 0x8);
		पूर्ण अन्यथा अणु	/* 120Mhz */
			bcma_ग_लिखो16(core, D11REGOFFS(tsf_clk_frac_l), 0x8889);
			bcma_ग_लिखो16(core, D11REGOFFS(tsf_clk_frac_h), 0x8);
		पूर्ण
	पूर्ण अन्यथा अगर (BRCMS_ISLCNPHY(wlc_hw->band)) अणु
		अगर (spurmode == WL_SPURAVOID_ON1) अणु	/* 82Mhz */
			bcma_ग_लिखो16(core, D11REGOFFS(tsf_clk_frac_l), 0x7CE0);
			bcma_ग_लिखो16(core, D11REGOFFS(tsf_clk_frac_h), 0xC);
		पूर्ण अन्यथा अणु	/* 80Mhz */
			bcma_ग_लिखो16(core, D11REGOFFS(tsf_clk_frac_l), 0xCCCD);
			bcma_ग_लिखो16(core, D11REGOFFS(tsf_clk_frac_h), 0xC);
		पूर्ण
	पूर्ण
पूर्ण

व्योम brcms_c_start_station(काष्ठा brcms_c_info *wlc, u8 *addr)
अणु
	स_नकल(wlc->pub->cur_etheraddr, addr, माप(wlc->pub->cur_etheraddr));
	wlc->bsscfg->type = BRCMS_TYPE_STATION;
पूर्ण

व्योम brcms_c_start_ap(काष्ठा brcms_c_info *wlc, u8 *addr, स्थिर u8 *bssid,
		      u8 *ssid, माप_प्रकार ssid_len)
अणु
	brcms_c_set_ssid(wlc, ssid, ssid_len);

	स_नकल(wlc->pub->cur_etheraddr, addr, माप(wlc->pub->cur_etheraddr));
	स_नकल(wlc->bsscfg->BSSID, bssid, माप(wlc->bsscfg->BSSID));
	wlc->bsscfg->type = BRCMS_TYPE_AP;

	brcms_b_mctrl(wlc->hw, MCTL_AP | MCTL_INFRA, MCTL_AP | MCTL_INFRA);
पूर्ण

व्योम brcms_c_start_adhoc(काष्ठा brcms_c_info *wlc, u8 *addr)
अणु
	स_नकल(wlc->pub->cur_etheraddr, addr, माप(wlc->pub->cur_etheraddr));
	wlc->bsscfg->type = BRCMS_TYPE_ADHOC;

	brcms_b_mctrl(wlc->hw, MCTL_AP | MCTL_INFRA, 0);
पूर्ण

/* Initialize GPIOs that are controlled by D11 core */
अटल व्योम brcms_c_gpio_init(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	u32 gc, gm;

	/* use GPIO select 0 to get all gpio संकेतs from the gpio out reg */
	brcms_b_mctrl(wlc_hw, MCTL_GPOUT_SEL_MASK, 0);

	/*
	 * Common GPIO setup:
	 *      G0 = LED 0 = WLAN Activity
	 *      G1 = LED 1 = WLAN 2.4 GHz Radio State
	 *      G2 = LED 2 = WLAN 5 GHz Radio State
	 *      G4 = radio disable input (HI enabled, LO disabled)
	 */

	gc = gm = 0;

	/* Allocate GPIOs क्रम mimo antenna भागersity feature */
	अगर (wlc_hw->antsel_type == ANTSEL_2x3) अणु
		/* Enable antenna भागersity, use 2x3 mode */
		brcms_b_mhf(wlc_hw, MHF3, MHF3_ANTSEL_EN,
			     MHF3_ANTSEL_EN, BRCM_BAND_ALL);
		brcms_b_mhf(wlc_hw, MHF3, MHF3_ANTSEL_MODE,
			     MHF3_ANTSEL_MODE, BRCM_BAND_ALL);

		/* init superचयन control */
		wlc_phy_antsel_init(wlc_hw->band->pi, false);

	पूर्ण अन्यथा अगर (wlc_hw->antsel_type == ANTSEL_2x4) अणु
		gm |= gc |= (BOARD_GPIO_12 | BOARD_GPIO_13);
		/*
		 * The board itself is घातered by these GPIOs
		 * (when not sending pattern) so set them high
		 */
		bcma_set16(wlc_hw->d11core, D11REGOFFS(psm_gpio_oe),
			   (BOARD_GPIO_12 | BOARD_GPIO_13));
		bcma_set16(wlc_hw->d11core, D11REGOFFS(psm_gpio_out),
			   (BOARD_GPIO_12 | BOARD_GPIO_13));

		/* Enable antenna भागersity, use 2x4 mode */
		brcms_b_mhf(wlc_hw, MHF3, MHF3_ANTSEL_EN,
			     MHF3_ANTSEL_EN, BRCM_BAND_ALL);
		brcms_b_mhf(wlc_hw, MHF3, MHF3_ANTSEL_MODE, 0,
			     BRCM_BAND_ALL);

		/* Configure the desired घड़ी to be 4Mhz */
		brcms_b_ग_लिखो_shm(wlc_hw, M_ANTSEL_CLKDIV,
				   ANTSEL_CLKDIV_4MHZ);
	पूर्ण

	/*
	 * gpio 9 controls the PA. ucode is responsible
	 * क्रम wiggling out and oe
	 */
	अगर (wlc_hw->boardflags & BFL_PACTRL)
		gm |= gc |= BOARD_GPIO_PACTRL;

	/* apply to gpiocontrol रेजिस्टर */
	bcma_chipco_gpio_control(&wlc_hw->d11core->bus->drv_cc, gm, gc);
पूर्ण

अटल व्योम brcms_ucode_ग_लिखो(काष्ठा brcms_hardware *wlc_hw,
			      स्थिर __le32 ucode[], स्थिर माप_प्रकार nbytes)
अणु
	काष्ठा bcma_device *core = wlc_hw->d11core;
	uपूर्णांक i;
	uपूर्णांक count;

	brcms_dbg_info(wlc_hw->d11core, "wl%d\n", wlc_hw->unit);

	count = (nbytes / माप(u32));

	bcma_ग_लिखो32(core, D11REGOFFS(objaddr),
		     OBJADDR_AUTO_INC | OBJADDR_UCM_SEL);
	(व्योम)bcma_पढ़ो32(core, D11REGOFFS(objaddr));
	क्रम (i = 0; i < count; i++)
		bcma_ग_लिखो32(core, D11REGOFFS(objdata), le32_to_cpu(ucode[i]));

पूर्ण

अटल व्योम brcms_ucode_करोwnload(काष्ठा brcms_hardware *wlc_hw)
अणु
	काष्ठा brcms_ucode *ucode = &wlc_hw->wlc->wl->ucode;

	अगर (wlc_hw->ucode_loaded)
		वापस;

	अगर (D11REV_IS(wlc_hw->corerev, 17) || D11REV_IS(wlc_hw->corerev, 23)) अणु
		अगर (BRCMS_ISNPHY(wlc_hw->band)) अणु
			brcms_ucode_ग_लिखो(wlc_hw, ucode->bcm43xx_16_mimo,
					  ucode->bcm43xx_16_mimosz);
			wlc_hw->ucode_loaded = true;
		पूर्ण अन्यथा
			brcms_err(wlc_hw->d11core,
				  "%s: wl%d: unsupported phy in corerev %d\n",
				  __func__, wlc_hw->unit, wlc_hw->corerev);
	पूर्ण अन्यथा अगर (D11REV_IS(wlc_hw->corerev, 24)) अणु
		अगर (BRCMS_ISLCNPHY(wlc_hw->band)) अणु
			brcms_ucode_ग_लिखो(wlc_hw, ucode->bcm43xx_24_lcn,
					  ucode->bcm43xx_24_lcnsz);
			wlc_hw->ucode_loaded = true;
		पूर्ण अन्यथा अणु
			brcms_err(wlc_hw->d11core,
				  "%s: wl%d: unsupported phy in corerev %d\n",
				  __func__, wlc_hw->unit, wlc_hw->corerev);
		पूर्ण
	पूर्ण
पूर्ण

व्योम brcms_b_txant_set(काष्ठा brcms_hardware *wlc_hw, u16 phytxant)
अणु
	/* update sw state */
	wlc_hw->bmac_phytxant = phytxant;

	/* push to ucode अगर up */
	अगर (!wlc_hw->up)
		वापस;
	brcms_c_ucode_txant_set(wlc_hw);

पूर्ण

u16 brcms_b_get_txant(काष्ठा brcms_hardware *wlc_hw)
अणु
	वापस (u16) wlc_hw->wlc->stf->txant;
पूर्ण

व्योम brcms_b_antsel_type_set(काष्ठा brcms_hardware *wlc_hw, u8 antsel_type)
अणु
	wlc_hw->antsel_type = antsel_type;

	/* Update the antsel type क्रम phy module to use */
	wlc_phy_antsel_type_set(wlc_hw->band->pi, antsel_type);
पूर्ण

अटल व्योम brcms_b_fअगरoerrors(काष्ठा brcms_hardware *wlc_hw)
अणु
	bool fatal = false;
	uपूर्णांक unit;
	uपूर्णांक पूर्णांकstatus, idx;
	काष्ठा bcma_device *core = wlc_hw->d11core;

	unit = wlc_hw->unit;

	क्रम (idx = 0; idx < NFIFO; idx++) अणु
		/* पढ़ो पूर्णांकstatus रेजिस्टर and ignore any non-error bits */
		पूर्णांकstatus =
			bcma_पढ़ो32(core,
				    D11REGOFFS(पूर्णांकctrlregs[idx].पूर्णांकstatus)) &
			I_ERRORS;
		अगर (!पूर्णांकstatus)
			जारी;

		brcms_dbg_पूर्णांक(core, "wl%d: intstatus%d 0x%x\n",
			      unit, idx, पूर्णांकstatus);

		अगर (पूर्णांकstatus & I_RO) अणु
			brcms_err(core, "wl%d: fifo %d: receive fifo "
				  "overflow\n", unit, idx);
			fatal = true;
		पूर्ण

		अगर (पूर्णांकstatus & I_PC) अणु
			brcms_err(core, "wl%d: fifo %d: descriptor error\n",
				  unit, idx);
			fatal = true;
		पूर्ण

		अगर (पूर्णांकstatus & I_PD) अणु
			brcms_err(core, "wl%d: fifo %d: data error\n", unit,
				  idx);
			fatal = true;
		पूर्ण

		अगर (पूर्णांकstatus & I_DE) अणु
			brcms_err(core, "wl%d: fifo %d: descriptor protocol "
				  "error\n", unit, idx);
			fatal = true;
		पूर्ण

		अगर (पूर्णांकstatus & I_RU)
			brcms_err(core, "wl%d: fifo %d: receive descriptor "
				  "underflow\n", idx, unit);

		अगर (पूर्णांकstatus & I_XU) अणु
			brcms_err(core, "wl%d: fifo %d: transmit fifo "
				  "underflow\n", idx, unit);
			fatal = true;
		पूर्ण

		अगर (fatal) अणु
			brcms_fatal_error(wlc_hw->wlc->wl); /* big hammer */
			अवरोध;
		पूर्ण अन्यथा
			bcma_ग_लिखो32(core,
				     D11REGOFFS(पूर्णांकctrlregs[idx].पूर्णांकstatus),
				     पूर्णांकstatus);
	पूर्ण
पूर्ण

व्योम brcms_c_पूर्णांकrson(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	wlc->macपूर्णांकmask = wlc->defmacपूर्णांकmask;
	bcma_ग_लिखो32(wlc_hw->d11core, D11REGOFFS(macपूर्णांकmask), wlc->macपूर्णांकmask);
पूर्ण

u32 brcms_c_पूर्णांकrsoff(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	u32 macपूर्णांकmask;

	अगर (!wlc_hw->clk)
		वापस 0;

	macपूर्णांकmask = wlc->macपूर्णांकmask;	/* isr can still happen */

	bcma_ग_लिखो32(wlc_hw->d11core, D11REGOFFS(macपूर्णांकmask), 0);
	(व्योम)bcma_पढ़ो32(wlc_hw->d11core, D11REGOFFS(macपूर्णांकmask));
	udelay(1);		/* ensure पूर्णांक line is no दीर्घer driven */
	wlc->macपूर्णांकmask = 0;

	/* वापस previous macपूर्णांकmask; resolve race between us and our isr */
	वापस wlc->macपूर्णांकstatus ? 0 : macपूर्णांकmask;
पूर्ण

व्योम brcms_c_पूर्णांकrsrestore(काष्ठा brcms_c_info *wlc, u32 macपूर्णांकmask)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	अगर (!wlc_hw->clk)
		वापस;

	wlc->macपूर्णांकmask = macपूर्णांकmask;
	bcma_ग_लिखो32(wlc_hw->d11core, D11REGOFFS(macपूर्णांकmask), wlc->macपूर्णांकmask);
पूर्ण

/* assumes that the d11 MAC is enabled */
अटल व्योम brcms_b_tx_fअगरo_suspend(काष्ठा brcms_hardware *wlc_hw,
				    uपूर्णांक tx_fअगरo)
अणु
	u8 fअगरo = 1 << tx_fअगरo;

	/* Two clients of this code, 11h Quiet period and scanning. */

	/* only suspend अगर not alपढ़ोy suspended */
	अगर ((wlc_hw->suspended_fअगरos & fअगरo) == fअगरo)
		वापस;

	/* क्रमce the core awake only अगर not alपढ़ोy */
	अगर (wlc_hw->suspended_fअगरos == 0)
		brcms_c_ucode_wake_override_set(wlc_hw,
						BRCMS_WAKE_OVERRIDE_TXFIFO);

	wlc_hw->suspended_fअगरos |= fअगरo;

	अगर (wlc_hw->di[tx_fअगरo]) अणु
		/*
		 * Suspending AMPDU transmissions in the middle can cause
		 * underflow which may result in mismatch between ucode and
		 * driver so suspend the mac beक्रमe suspending the FIFO
		 */
		अगर (BRCMS_PHY_11N_CAP(wlc_hw->band))
			brcms_c_suspend_mac_and_रुको(wlc_hw->wlc);

		dma_txsuspend(wlc_hw->di[tx_fअगरo]);

		अगर (BRCMS_PHY_11N_CAP(wlc_hw->band))
			brcms_c_enable_mac(wlc_hw->wlc);
	पूर्ण
पूर्ण

अटल व्योम brcms_b_tx_fअगरo_resume(काष्ठा brcms_hardware *wlc_hw,
				   uपूर्णांक tx_fअगरo)
अणु
	/* BMAC_NOTE: BRCMS_TX_FIFO_ENAB is करोne in brcms_c_dpc() क्रम DMA हाल
	 * but need to be करोne here क्रम PIO otherwise the watchकरोg will catch
	 * the inconsistency and fire
	 */
	/* Two clients of this code, 11h Quiet period and scanning. */
	अगर (wlc_hw->di[tx_fअगरo])
		dma_txresume(wlc_hw->di[tx_fअगरo]);

	/* allow core to sleep again */
	अगर (wlc_hw->suspended_fअगरos == 0)
		वापस;
	अन्यथा अणु
		wlc_hw->suspended_fअगरos &= ~(1 << tx_fअगरo);
		अगर (wlc_hw->suspended_fअगरos == 0)
			brcms_c_ucode_wake_override_clear(wlc_hw,
						BRCMS_WAKE_OVERRIDE_TXFIFO);
	पूर्ण
पूर्ण

/* precondition: requires the mac core to be enabled */
अटल व्योम brcms_b_mute(काष्ठा brcms_hardware *wlc_hw, bool mute_tx)
अणु
	अटल स्थिर u8 null_ether_addr[ETH_ALEN] = अणु0, 0, 0, 0, 0, 0पूर्ण;
	u8 *ethaddr = wlc_hw->wlc->pub->cur_etheraddr;

	अगर (mute_tx) अणु
		/* suspend tx fअगरos */
		brcms_b_tx_fअगरo_suspend(wlc_hw, TX_DATA_FIFO);
		brcms_b_tx_fअगरo_suspend(wlc_hw, TX_CTL_FIFO);
		brcms_b_tx_fअगरo_suspend(wlc_hw, TX_AC_BK_FIFO);
		brcms_b_tx_fअगरo_suspend(wlc_hw, TX_AC_VI_FIFO);

		/* zero the address match रेजिस्टर so we करो not send ACKs */
		brcms_b_set_addrmatch(wlc_hw, RCM_MAC_OFFSET, null_ether_addr);
	पूर्ण अन्यथा अणु
		/* resume tx fअगरos */
		brcms_b_tx_fअगरo_resume(wlc_hw, TX_DATA_FIFO);
		brcms_b_tx_fअगरo_resume(wlc_hw, TX_CTL_FIFO);
		brcms_b_tx_fअगरo_resume(wlc_hw, TX_AC_BK_FIFO);
		brcms_b_tx_fअगरo_resume(wlc_hw, TX_AC_VI_FIFO);

		/* Restore address */
		brcms_b_set_addrmatch(wlc_hw, RCM_MAC_OFFSET, ethaddr);
	पूर्ण

	wlc_phy_mute_upd(wlc_hw->band->pi, mute_tx, 0);

	अगर (mute_tx)
		brcms_c_ucode_mute_override_set(wlc_hw);
	अन्यथा
		brcms_c_ucode_mute_override_clear(wlc_hw);
पूर्ण

व्योम
brcms_c_mute(काष्ठा brcms_c_info *wlc, bool mute_tx)
अणु
	brcms_b_mute(wlc->hw, mute_tx);
पूर्ण

/*
 * Read and clear macपूर्णांकmask and macपूर्णांकstatus and पूर्णांकstatus रेजिस्टरs.
 * This routine should be called with पूर्णांकerrupts off
 * Return:
 *   -1 अगर brcms_deviceहटाओd(wlc) evaluates to true;
 *   0 अगर the पूर्णांकerrupt is not क्रम us, or we are in some special हालs;
 *   device पूर्णांकerrupt status bits otherwise.
 */
अटल अंतरभूत u32 wlc_पूर्णांकstatus(काष्ठा brcms_c_info *wlc, bool in_isr)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	काष्ठा bcma_device *core = wlc_hw->d11core;
	u32 macपूर्णांकstatus, mask;

	/* macपूर्णांकstatus includes a DMA पूर्णांकerrupt summary bit */
	macपूर्णांकstatus = bcma_पढ़ो32(core, D11REGOFFS(macपूर्णांकstatus));
	mask = in_isr ? wlc->macपूर्णांकmask : wlc->defmacपूर्णांकmask;

	trace_brcms_macपूर्णांकstatus(&core->dev, in_isr, macपूर्णांकstatus, mask);

	/* detect cardbus हटाओd, in घातer करोwn(suspend) and in reset */
	अगर (brcms_deviceहटाओd(wlc))
		वापस -1;

	/* brcms_deviceहटाओd() succeeds even when the core is still resetting,
	 * handle that हाल here.
	 */
	अगर (macपूर्णांकstatus == 0xffffffff)
		वापस 0;

	/* defer unsolicited पूर्णांकerrupts */
	macपूर्णांकstatus &= mask;

	/* अगर not क्रम us */
	अगर (macपूर्णांकstatus == 0)
		वापस 0;

	/* turn off the पूर्णांकerrupts */
	bcma_ग_लिखो32(core, D11REGOFFS(macपूर्णांकmask), 0);
	(व्योम)bcma_पढ़ो32(core, D11REGOFFS(macपूर्णांकmask));
	wlc->macपूर्णांकmask = 0;

	/* clear device पूर्णांकerrupts */
	bcma_ग_लिखो32(core, D11REGOFFS(macपूर्णांकstatus), macपूर्णांकstatus);

	/* MI_DMAINT is indication of non-zero पूर्णांकstatus */
	अगर (macपूर्णांकstatus & MI_DMAINT)
		/*
		 * only fअगरo पूर्णांकerrupt enabled is I_RI in
		 * RX_FIFO. If MI_DMAINT is set, assume it
		 * is set and clear the पूर्णांकerrupt.
		 */
		bcma_ग_लिखो32(core, D11REGOFFS(पूर्णांकctrlregs[RX_FIFO].पूर्णांकstatus),
			     DEF_RXINTMASK);

	वापस macपूर्णांकstatus;
पूर्ण

/* Update wlc->macपूर्णांकstatus and wlc->पूर्णांकstatus[]. */
/* Return true अगर they are updated successfully. false otherwise */
bool brcms_c_पूर्णांकrsupd(काष्ठा brcms_c_info *wlc)
अणु
	u32 macपूर्णांकstatus;

	/* पढ़ो and clear macपूर्णांकstatus and पूर्णांकstatus रेजिस्टरs */
	macपूर्णांकstatus = wlc_पूर्णांकstatus(wlc, false);

	/* device is हटाओd */
	अगर (macपूर्णांकstatus == 0xffffffff)
		वापस false;

	/* update पूर्णांकerrupt status in software */
	wlc->macपूर्णांकstatus |= macपूर्णांकstatus;

	वापस true;
पूर्ण

/*
 * First-level पूर्णांकerrupt processing.
 * Return true अगर this was our पूर्णांकerrupt
 * and अगर further brcms_c_dpc() processing is required,
 * false otherwise.
 */
bool brcms_c_isr(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	u32 macपूर्णांकstatus;

	अगर (!wlc_hw->up || !wlc->macपूर्णांकmask)
		वापस false;

	/* पढ़ो and clear macपूर्णांकstatus and पूर्णांकstatus रेजिस्टरs */
	macपूर्णांकstatus = wlc_पूर्णांकstatus(wlc, true);

	अगर (macपूर्णांकstatus == 0xffffffff) अणु
		brcms_err(wlc_hw->d11core,
			  "DEVICEREMOVED detected in the ISR code path\n");
		वापस false;
	पूर्ण

	/* it is not क्रम us */
	अगर (macपूर्णांकstatus == 0)
		वापस false;

	/* save पूर्णांकerrupt status bits */
	wlc->macपूर्णांकstatus = macपूर्णांकstatus;

	वापस true;

पूर्ण

व्योम brcms_c_suspend_mac_and_रुको(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	काष्ठा bcma_device *core = wlc_hw->d11core;
	u32 mc, mi;

	brcms_dbg_mac80211(core, "wl%d: bandunit %d\n", wlc_hw->unit,
			   wlc_hw->band->bandunit);

	/*
	 * Track overlapping suspend requests
	 */
	wlc_hw->mac_suspend_depth++;
	अगर (wlc_hw->mac_suspend_depth > 1)
		वापस;

	/* क्रमce the core awake */
	brcms_c_ucode_wake_override_set(wlc_hw, BRCMS_WAKE_OVERRIDE_MACSUSPEND);

	mc = bcma_पढ़ो32(core, D11REGOFFS(maccontrol));

	अगर (mc == 0xffffffff) अणु
		brcms_err(core, "wl%d: %s: dead chip\n", wlc_hw->unit,
			  __func__);
		brcms_करोwn(wlc->wl);
		वापस;
	पूर्ण
	WARN_ON(mc & MCTL_PSM_JMP_0);
	WARN_ON(!(mc & MCTL_PSM_RUN));
	WARN_ON(!(mc & MCTL_EN_MAC));

	mi = bcma_पढ़ो32(core, D11REGOFFS(macपूर्णांकstatus));
	अगर (mi == 0xffffffff) अणु
		brcms_err(core, "wl%d: %s: dead chip\n", wlc_hw->unit,
			  __func__);
		brcms_करोwn(wlc->wl);
		वापस;
	पूर्ण
	WARN_ON(mi & MI_MACSSPNDD);

	brcms_b_mctrl(wlc_hw, MCTL_EN_MAC, 0);

	SPINWAIT(!(bcma_पढ़ो32(core, D11REGOFFS(macपूर्णांकstatus)) & MI_MACSSPNDD),
		 BRCMS_MAX_MAC_SUSPEND);

	अगर (!(bcma_पढ़ो32(core, D11REGOFFS(macपूर्णांकstatus)) & MI_MACSSPNDD)) अणु
		brcms_err(core, "wl%d: wlc_suspend_mac_and_wait: waited %d uS"
			  " and MI_MACSSPNDD is still not on.\n",
			  wlc_hw->unit, BRCMS_MAX_MAC_SUSPEND);
		brcms_err(core, "wl%d: psmdebug 0x%08x, phydebug 0x%08x, "
			  "psm_brc 0x%04x\n", wlc_hw->unit,
			  bcma_पढ़ो32(core, D11REGOFFS(psmdebug)),
			  bcma_पढ़ो32(core, D11REGOFFS(phydebug)),
			  bcma_पढ़ो16(core, D11REGOFFS(psm_brc)));
	पूर्ण

	mc = bcma_पढ़ो32(core, D11REGOFFS(maccontrol));
	अगर (mc == 0xffffffff) अणु
		brcms_err(core, "wl%d: %s: dead chip\n", wlc_hw->unit,
			  __func__);
		brcms_करोwn(wlc->wl);
		वापस;
	पूर्ण
	WARN_ON(mc & MCTL_PSM_JMP_0);
	WARN_ON(!(mc & MCTL_PSM_RUN));
	WARN_ON(mc & MCTL_EN_MAC);
पूर्ण

व्योम brcms_c_enable_mac(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	काष्ठा bcma_device *core = wlc_hw->d11core;
	u32 mc, mi;

	brcms_dbg_mac80211(core, "wl%d: bandunit %d\n", wlc_hw->unit,
			   wlc->band->bandunit);

	/*
	 * Track overlapping suspend requests
	 */
	wlc_hw->mac_suspend_depth--;
	अगर (wlc_hw->mac_suspend_depth > 0)
		वापस;

	mc = bcma_पढ़ो32(core, D11REGOFFS(maccontrol));
	WARN_ON(mc & MCTL_PSM_JMP_0);
	WARN_ON(mc & MCTL_EN_MAC);
	WARN_ON(!(mc & MCTL_PSM_RUN));

	brcms_b_mctrl(wlc_hw, MCTL_EN_MAC, MCTL_EN_MAC);
	bcma_ग_लिखो32(core, D11REGOFFS(macपूर्णांकstatus), MI_MACSSPNDD);

	mc = bcma_पढ़ो32(core, D11REGOFFS(maccontrol));
	WARN_ON(mc & MCTL_PSM_JMP_0);
	WARN_ON(!(mc & MCTL_EN_MAC));
	WARN_ON(!(mc & MCTL_PSM_RUN));

	mi = bcma_पढ़ो32(core, D11REGOFFS(macपूर्णांकstatus));
	WARN_ON(mi & MI_MACSSPNDD);

	brcms_c_ucode_wake_override_clear(wlc_hw,
					  BRCMS_WAKE_OVERRIDE_MACSUSPEND);
पूर्ण

व्योम brcms_b_band_stf_ss_set(काष्ठा brcms_hardware *wlc_hw, u8 stf_mode)
अणु
	wlc_hw->hw_stf_ss_opmode = stf_mode;

	अगर (wlc_hw->clk)
		brcms_upd_ofdm_pctl1_table(wlc_hw);
पूर्ण

अटल bool brcms_b_validate_chip_access(काष्ठा brcms_hardware *wlc_hw)
अणु
	काष्ठा bcma_device *core = wlc_hw->d11core;
	u32 w, val;
	काष्ठा wiphy *wiphy = wlc_hw->wlc->wiphy;

	/* Validate dchip रेजिस्टर access */

	bcma_ग_लिखो32(core, D11REGOFFS(objaddr), OBJADDR_SHM_SEL | 0);
	(व्योम)bcma_पढ़ो32(core, D11REGOFFS(objaddr));
	w = bcma_पढ़ो32(core, D11REGOFFS(objdata));

	/* Can we ग_लिखो and पढ़ो back a 32bit रेजिस्टर? */
	bcma_ग_लिखो32(core, D11REGOFFS(objaddr), OBJADDR_SHM_SEL | 0);
	(व्योम)bcma_पढ़ो32(core, D11REGOFFS(objaddr));
	bcma_ग_लिखो32(core, D11REGOFFS(objdata), (u32) 0xaa5555aa);

	bcma_ग_लिखो32(core, D11REGOFFS(objaddr), OBJADDR_SHM_SEL | 0);
	(व्योम)bcma_पढ़ो32(core, D11REGOFFS(objaddr));
	val = bcma_पढ़ो32(core, D11REGOFFS(objdata));
	अगर (val != (u32) 0xaa5555aa) अणु
		wiphy_err(wiphy, "wl%d: validate_chip_access: SHM = 0x%x, "
			  "expected 0xaa5555aa\n", wlc_hw->unit, val);
		वापस false;
	पूर्ण

	bcma_ग_लिखो32(core, D11REGOFFS(objaddr), OBJADDR_SHM_SEL | 0);
	(व्योम)bcma_पढ़ो32(core, D11REGOFFS(objaddr));
	bcma_ग_लिखो32(core, D11REGOFFS(objdata), (u32) 0x55aaaa55);

	bcma_ग_लिखो32(core, D11REGOFFS(objaddr), OBJADDR_SHM_SEL | 0);
	(व्योम)bcma_पढ़ो32(core, D11REGOFFS(objaddr));
	val = bcma_पढ़ो32(core, D11REGOFFS(objdata));
	अगर (val != (u32) 0x55aaaa55) अणु
		wiphy_err(wiphy, "wl%d: validate_chip_access: SHM = 0x%x, "
			  "expected 0x55aaaa55\n", wlc_hw->unit, val);
		वापस false;
	पूर्ण

	bcma_ग_लिखो32(core, D11REGOFFS(objaddr), OBJADDR_SHM_SEL | 0);
	(व्योम)bcma_पढ़ो32(core, D11REGOFFS(objaddr));
	bcma_ग_लिखो32(core, D11REGOFFS(objdata), w);

	/* clear CFPStart */
	bcma_ग_लिखो32(core, D11REGOFFS(tsf_cfpstart), 0);

	w = bcma_पढ़ो32(core, D11REGOFFS(maccontrol));
	अगर ((w != (MCTL_IHR_EN | MCTL_WAKE)) &&
	    (w != (MCTL_IHR_EN | MCTL_GMODE | MCTL_WAKE))) अणु
		wiphy_err(wiphy, "wl%d: validate_chip_access: maccontrol = "
			  "0x%x, expected 0x%x or 0x%x\n", wlc_hw->unit, w,
			  (MCTL_IHR_EN | MCTL_WAKE),
			  (MCTL_IHR_EN | MCTL_GMODE | MCTL_WAKE));
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

#घोषणा PHYPLL_WAIT_US	100000

व्योम brcms_b_core_phypll_ctl(काष्ठा brcms_hardware *wlc_hw, bool on)
अणु
	काष्ठा bcma_device *core = wlc_hw->d11core;
	u32 पंचांगp;

	brcms_dbg_info(core, "wl%d\n", wlc_hw->unit);

	पंचांगp = 0;

	अगर (on) अणु
		अगर ((ai_get_chip_id(wlc_hw->sih) == BCMA_CHIP_ID_BCM4313)) अणु
			bcma_set32(core, D11REGOFFS(clk_ctl_st),
				   CCS_ERSRC_REQ_HT |
				   CCS_ERSRC_REQ_D11PLL |
				   CCS_ERSRC_REQ_PHYPLL);
			SPINWAIT((bcma_पढ़ो32(core, D11REGOFFS(clk_ctl_st)) &
				  CCS_ERSRC_AVAIL_HT) != CCS_ERSRC_AVAIL_HT,
				 PHYPLL_WAIT_US);

			पंचांगp = bcma_पढ़ो32(core, D11REGOFFS(clk_ctl_st));
			अगर ((पंचांगp & CCS_ERSRC_AVAIL_HT) != CCS_ERSRC_AVAIL_HT)
				brcms_err(core, "%s: turn on PHY PLL failed\n",
					  __func__);
		पूर्ण अन्यथा अणु
			bcma_set32(core, D11REGOFFS(clk_ctl_st),
				   पंचांगp | CCS_ERSRC_REQ_D11PLL |
				   CCS_ERSRC_REQ_PHYPLL);
			SPINWAIT((bcma_पढ़ो32(core, D11REGOFFS(clk_ctl_st)) &
				  (CCS_ERSRC_AVAIL_D11PLL |
				   CCS_ERSRC_AVAIL_PHYPLL)) !=
				 (CCS_ERSRC_AVAIL_D11PLL |
				  CCS_ERSRC_AVAIL_PHYPLL), PHYPLL_WAIT_US);

			पंचांगp = bcma_पढ़ो32(core, D11REGOFFS(clk_ctl_st));
			अगर ((पंचांगp &
			     (CCS_ERSRC_AVAIL_D11PLL | CCS_ERSRC_AVAIL_PHYPLL))
			    !=
			    (CCS_ERSRC_AVAIL_D11PLL | CCS_ERSRC_AVAIL_PHYPLL))
				brcms_err(core, "%s: turn on PHY PLL failed\n",
					  __func__);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Since the PLL may be shared, other cores can still
		 * be requesting it; so we'll deनिश्चित the request but
		 * not रुको क्रम status to comply.
		 */
		bcma_mask32(core, D11REGOFFS(clk_ctl_st),
			    ~CCS_ERSRC_REQ_PHYPLL);
		(व्योम)bcma_पढ़ो32(core, D11REGOFFS(clk_ctl_st));
	पूर्ण
पूर्ण

अटल व्योम brcms_c_coredisable(काष्ठा brcms_hardware *wlc_hw)
अणु
	bool dev_gone;

	brcms_dbg_info(wlc_hw->d11core, "wl%d: disable core\n", wlc_hw->unit);

	dev_gone = brcms_deviceहटाओd(wlc_hw->wlc);

	अगर (dev_gone)
		वापस;

	अगर (wlc_hw->noreset)
		वापस;

	/* radio off */
	wlc_phy_चयन_radio(wlc_hw->band->pi, OFF);

	/* turn off analog core */
	wlc_phy_anacore(wlc_hw->band->pi, OFF);

	/* turn off PHYPLL to save घातer */
	brcms_b_core_phypll_ctl(wlc_hw, false);

	wlc_hw->clk = false;
	bcma_core_disable(wlc_hw->d11core, 0);
	wlc_phy_hw_clk_state_upd(wlc_hw->band->pi, false);
पूर्ण

अटल व्योम brcms_c_flushqueues(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	uपूर्णांक i;

	/* मुक्त any posted tx packets */
	क्रम (i = 0; i < NFIFO; i++) अणु
		अगर (wlc_hw->di[i]) अणु
			dma_txreclaim(wlc_hw->di[i], DMA_RANGE_ALL);
			अगर (i < TX_BCMC_FIFO)
				ieee80211_wake_queue(wlc->pub->ieee_hw,
						     brcms_fअगरo_to_ac(i));
		पूर्ण
	पूर्ण

	/* मुक्त any posted rx packets */
	dma_rxreclaim(wlc_hw->di[RX_FIFO]);
पूर्ण

अटल u16
brcms_b_पढ़ो_objmem(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक offset, u32 sel)
अणु
	काष्ठा bcma_device *core = wlc_hw->d11core;
	u16 objoff = D11REGOFFS(objdata);

	bcma_ग_लिखो32(core, D11REGOFFS(objaddr), sel | (offset >> 2));
	(व्योम)bcma_पढ़ो32(core, D11REGOFFS(objaddr));
	अगर (offset & 2)
		objoff += 2;

	वापस bcma_पढ़ो16(core, objoff);
पूर्ण

अटल व्योम
brcms_b_ग_लिखो_objmem(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक offset, u16 v,
		     u32 sel)
अणु
	काष्ठा bcma_device *core = wlc_hw->d11core;
	u16 objoff = D11REGOFFS(objdata);

	bcma_ग_लिखो32(core, D11REGOFFS(objaddr), sel | (offset >> 2));
	(व्योम)bcma_पढ़ो32(core, D11REGOFFS(objaddr));
	अगर (offset & 2)
		objoff += 2;

	bcma_wflush16(core, objoff, v);
पूर्ण

/*
 * Read a single u16 from shared memory.
 * SHM 'offset' needs to be an even address
 */
u16 brcms_b_पढ़ो_shm(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक offset)
अणु
	वापस brcms_b_पढ़ो_objmem(wlc_hw, offset, OBJADDR_SHM_SEL);
पूर्ण

/*
 * Write a single u16 to shared memory.
 * SHM 'offset' needs to be an even address
 */
व्योम brcms_b_ग_लिखो_shm(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक offset, u16 v)
अणु
	brcms_b_ग_लिखो_objmem(wlc_hw, offset, v, OBJADDR_SHM_SEL);
पूर्ण

/*
 * Copy a buffer to shared memory of specअगरied type .
 * SHM 'offset' needs to be an even address and
 * Buffer length 'len' must be an even number of bytes
 * 'sel' selects the type of memory
 */
व्योम
brcms_b_copyto_objmem(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक offset,
		      स्थिर व्योम *buf, पूर्णांक len, u32 sel)
अणु
	u16 v;
	स्थिर u8 *p = (स्थिर u8 *)buf;
	पूर्णांक i;

	अगर (len <= 0 || (offset & 1) || (len & 1))
		वापस;

	क्रम (i = 0; i < len; i += 2) अणु
		v = p[i] | (p[i + 1] << 8);
		brcms_b_ग_लिखो_objmem(wlc_hw, offset + i, v, sel);
	पूर्ण
पूर्ण

/*
 * Copy a piece of shared memory of specअगरied type to a buffer .
 * SHM 'offset' needs to be an even address and
 * Buffer length 'len' must be an even number of bytes
 * 'sel' selects the type of memory
 */
व्योम
brcms_b_copyfrom_objmem(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक offset, व्योम *buf,
			 पूर्णांक len, u32 sel)
अणु
	u16 v;
	u8 *p = (u8 *) buf;
	पूर्णांक i;

	अगर (len <= 0 || (offset & 1) || (len & 1))
		वापस;

	क्रम (i = 0; i < len; i += 2) अणु
		v = brcms_b_पढ़ो_objmem(wlc_hw, offset + i, sel);
		p[i] = v & 0xFF;
		p[i + 1] = (v >> 8) & 0xFF;
	पूर्ण
पूर्ण

/* Copy a buffer to shared memory.
 * SHM 'offset' needs to be an even address and
 * Buffer length 'len' must be an even number of bytes
 */
अटल व्योम brcms_c_copyto_shm(काष्ठा brcms_c_info *wlc, uपूर्णांक offset,
			स्थिर व्योम *buf, पूर्णांक len)
अणु
	brcms_b_copyto_objmem(wlc->hw, offset, buf, len, OBJADDR_SHM_SEL);
पूर्ण

अटल व्योम brcms_b_retrylimit_upd(काष्ठा brcms_hardware *wlc_hw,
				   u16 SRL, u16 LRL)
अणु
	wlc_hw->SRL = SRL;
	wlc_hw->LRL = LRL;

	/* ग_लिखो retry limit to SCR, shouldn't need to suspend */
	अगर (wlc_hw->up) अणु
		bcma_ग_लिखो32(wlc_hw->d11core, D11REGOFFS(objaddr),
			     OBJADDR_SCR_SEL | S_DOT11_SRC_LMT);
		(व्योम)bcma_पढ़ो32(wlc_hw->d11core, D11REGOFFS(objaddr));
		bcma_ग_लिखो32(wlc_hw->d11core, D11REGOFFS(objdata), wlc_hw->SRL);
		bcma_ग_लिखो32(wlc_hw->d11core, D11REGOFFS(objaddr),
			     OBJADDR_SCR_SEL | S_DOT11_LRC_LMT);
		(व्योम)bcma_पढ़ो32(wlc_hw->d11core, D11REGOFFS(objaddr));
		bcma_ग_लिखो32(wlc_hw->d11core, D11REGOFFS(objdata), wlc_hw->LRL);
	पूर्ण
पूर्ण

अटल व्योम brcms_b_pllreq(काष्ठा brcms_hardware *wlc_hw, bool set, u32 req_bit)
अणु
	अगर (set) अणु
		अगर (mboolisset(wlc_hw->pllreq, req_bit))
			वापस;

		mboolset(wlc_hw->pllreq, req_bit);

		अगर (mboolisset(wlc_hw->pllreq, BRCMS_PLLREQ_FLIP)) अणु
			अगर (!wlc_hw->sbclk)
				brcms_b_xtal(wlc_hw, ON);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!mboolisset(wlc_hw->pllreq, req_bit))
			वापस;

		mboolclr(wlc_hw->pllreq, req_bit);

		अगर (mboolisset(wlc_hw->pllreq, BRCMS_PLLREQ_FLIP)) अणु
			अगर (wlc_hw->sbclk)
				brcms_b_xtal(wlc_hw, OFF);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम brcms_b_antsel_set(काष्ठा brcms_hardware *wlc_hw, u32 antsel_avail)
अणु
	wlc_hw->antsel_avail = antsel_avail;
पूर्ण

/*
 * conditions under which the PM bit should be set in outgoing frames
 * and STAY_AWAKE is meaningful
 */
अटल bool brcms_c_ps_allowed(काष्ठा brcms_c_info *wlc)
अणु
	/* not supporting PS so always वापस false क्रम now */
	वापस false;
पूर्ण

अटल व्योम brcms_c_statsupd(काष्ठा brcms_c_info *wlc)
अणु
	पूर्णांक i;
	काष्ठा macstat *macstats;
#अगर_घोषित DEBUG
	u16 delta;
	u16 rxf0ovfl;
	u16 txfunfl[NFIFO];
#पूर्ण_अगर				/* DEBUG */

	/* अगर driver करोwn, make no sense to update stats */
	अगर (!wlc->pub->up)
		वापस;

	macstats = wlc->core->macstat_snapshot;

#अगर_घोषित DEBUG
	/* save last rx fअगरo 0 overflow count */
	rxf0ovfl = macstats->rxf0ovfl;

	/* save last tx fअगरo  underflow count */
	क्रम (i = 0; i < NFIFO; i++)
		txfunfl[i] = macstats->txfunfl[i];
#पूर्ण_अगर				/* DEBUG */

	/* Read mac stats from contiguous shared memory */
	brcms_b_copyfrom_objmem(wlc->hw, M_UCODE_MACSTAT, macstats,
				माप(*macstats), OBJADDR_SHM_SEL);

#अगर_घोषित DEBUG
	/* check क्रम rx fअगरo 0 overflow */
	delta = (u16)(macstats->rxf0ovfl - rxf0ovfl);
	अगर (delta)
		brcms_err(wlc->hw->d11core, "wl%d: %u rx fifo 0 overflows!\n",
			  wlc->pub->unit, delta);

	/* check क्रम tx fअगरo underflows */
	क्रम (i = 0; i < NFIFO; i++) अणु
		delta = macstats->txfunfl[i] - txfunfl[i];
		अगर (delta)
			brcms_err(wlc->hw->d11core,
				  "wl%d: %u tx fifo %d underflows!\n",
				  wlc->pub->unit, delta, i);
	पूर्ण
#पूर्ण_अगर				/* DEBUG */

	/* merge counters from dma module */
	क्रम (i = 0; i < NFIFO; i++) अणु
		अगर (wlc->hw->di[i])
			dma_counterreset(wlc->hw->di[i]);
	पूर्ण
पूर्ण

अटल व्योम brcms_b_reset(काष्ठा brcms_hardware *wlc_hw)
अणु
	/* reset the core */
	अगर (!brcms_deviceहटाओd(wlc_hw->wlc))
		brcms_b_corereset(wlc_hw, BRCMS_USE_COREFLAGS);

	/* purge the dma rings */
	brcms_c_flushqueues(wlc_hw->wlc);
पूर्ण

व्योम brcms_c_reset(काष्ठा brcms_c_info *wlc)
अणु
	brcms_dbg_info(wlc->hw->d11core, "wl%d\n", wlc->pub->unit);

	/* slurp up hw mac counters beक्रमe core reset */
	brcms_c_statsupd(wlc);

	/* reset our snapshot of macstat counters */
	स_रखो(wlc->core->macstat_snapshot, 0, माप(काष्ठा macstat));

	brcms_b_reset(wlc->hw);
पूर्ण

व्योम brcms_c_init_scb(काष्ठा scb *scb)
अणु
	पूर्णांक i;

	स_रखो(scb, 0, माप(काष्ठा scb));
	scb->flags = SCB_WMECAP | SCB_HTCAP;
	क्रम (i = 0; i < NUMPRIO; i++) अणु
		scb->seqnum[i] = 0;
		scb->seqctl[i] = 0xFFFF;
	पूर्ण

	scb->seqctl_nonqos = 0xFFFF;
	scb->magic = SCB_MAGIC;
पूर्ण

/* d11 core init
 *   reset PSM
 *   करोwnload ucode/PCM
 *   let ucode run to suspended
 *   करोwnload ucode inits
 *   config other core रेजिस्टरs
 *   init dma
 */
अटल व्योम brcms_b_coreinit(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	काष्ठा bcma_device *core = wlc_hw->d11core;
	u32 bcnपूर्णांक_us;
	uपूर्णांक i = 0;
	bool fअगरosz_fixup = false;
	पूर्णांक err = 0;
	u16 buf[NFIFO];
	काष्ठा brcms_ucode *ucode = &wlc_hw->wlc->wl->ucode;

	brcms_dbg_info(core, "wl%d: core init\n", wlc_hw->unit);

	/* reset PSM */
	brcms_b_mctrl(wlc_hw, ~0, (MCTL_IHR_EN | MCTL_PSM_JMP_0 | MCTL_WAKE));

	brcms_ucode_करोwnload(wlc_hw);
	/*
	 * FIFOSZ fixup. driver wants to controls the fअगरo allocation.
	 */
	fअगरosz_fixup = true;

	/* let the PSM run to the suspended state, set mode to BSS STA */
	bcma_ग_लिखो32(core, D11REGOFFS(macपूर्णांकstatus), -1);
	brcms_b_mctrl(wlc_hw, ~0,
		       (MCTL_IHR_EN | MCTL_INFRA | MCTL_PSM_RUN | MCTL_WAKE));

	/* रुको क्रम ucode to self-suspend after स्वतः-init */
	SPINWAIT(((bcma_पढ़ो32(core, D11REGOFFS(macपूर्णांकstatus)) &
		   MI_MACSSPNDD) == 0), 1000 * 1000);
	अगर ((bcma_पढ़ो32(core, D11REGOFFS(macपूर्णांकstatus)) & MI_MACSSPNDD) == 0)
		brcms_err(core, "wl%d: wlc_coreinit: ucode did not self-"
			  "suspend!\n", wlc_hw->unit);

	brcms_c_gpio_init(wlc);

	bcma_aपढ़ो32(core, BCMA_IOST);

	अगर (D11REV_IS(wlc_hw->corerev, 17) || D11REV_IS(wlc_hw->corerev, 23)) अणु
		अगर (BRCMS_ISNPHY(wlc_hw->band))
			brcms_c_ग_लिखो_inits(wlc_hw, ucode->d11n0initvals16);
		अन्यथा
			brcms_err(core, "%s: wl%d: unsupported phy in corerev"
				  " %d\n", __func__, wlc_hw->unit,
				  wlc_hw->corerev);
	पूर्ण अन्यथा अगर (D11REV_IS(wlc_hw->corerev, 24)) अणु
		अगर (BRCMS_ISLCNPHY(wlc_hw->band))
			brcms_c_ग_लिखो_inits(wlc_hw, ucode->d11lcn0initvals24);
		अन्यथा
			brcms_err(core, "%s: wl%d: unsupported phy in corerev"
				  " %d\n", __func__, wlc_hw->unit,
				  wlc_hw->corerev);
	पूर्ण अन्यथा अणु
		brcms_err(core, "%s: wl%d: unsupported corerev %d\n",
			  __func__, wlc_hw->unit, wlc_hw->corerev);
	पूर्ण

	/* For old ucode, txfअगरo sizes needs to be modअगरied(increased) */
	अगर (fअगरosz_fixup)
		brcms_b_corerev_fअगरofixup(wlc_hw);

	/* check txfअगरo allocations match between ucode and driver */
	buf[TX_AC_BE_FIFO] = brcms_b_पढ़ो_shm(wlc_hw, M_FIFOSIZE0);
	अगर (buf[TX_AC_BE_FIFO] != wlc_hw->xmtfअगरo_sz[TX_AC_BE_FIFO]) अणु
		i = TX_AC_BE_FIFO;
		err = -1;
	पूर्ण
	buf[TX_AC_VI_FIFO] = brcms_b_पढ़ो_shm(wlc_hw, M_FIFOSIZE1);
	अगर (buf[TX_AC_VI_FIFO] != wlc_hw->xmtfअगरo_sz[TX_AC_VI_FIFO]) अणु
		i = TX_AC_VI_FIFO;
		err = -1;
	पूर्ण
	buf[TX_AC_BK_FIFO] = brcms_b_पढ़ो_shm(wlc_hw, M_FIFOSIZE2);
	buf[TX_AC_VO_FIFO] = (buf[TX_AC_BK_FIFO] >> 8) & 0xff;
	buf[TX_AC_BK_FIFO] &= 0xff;
	अगर (buf[TX_AC_BK_FIFO] != wlc_hw->xmtfअगरo_sz[TX_AC_BK_FIFO]) अणु
		i = TX_AC_BK_FIFO;
		err = -1;
	पूर्ण
	अगर (buf[TX_AC_VO_FIFO] != wlc_hw->xmtfअगरo_sz[TX_AC_VO_FIFO]) अणु
		i = TX_AC_VO_FIFO;
		err = -1;
	पूर्ण
	buf[TX_BCMC_FIFO] = brcms_b_पढ़ो_shm(wlc_hw, M_FIFOSIZE3);
	buf[TX_ATIM_FIFO] = (buf[TX_BCMC_FIFO] >> 8) & 0xff;
	buf[TX_BCMC_FIFO] &= 0xff;
	अगर (buf[TX_BCMC_FIFO] != wlc_hw->xmtfअगरo_sz[TX_BCMC_FIFO]) अणु
		i = TX_BCMC_FIFO;
		err = -1;
	पूर्ण
	अगर (buf[TX_ATIM_FIFO] != wlc_hw->xmtfअगरo_sz[TX_ATIM_FIFO]) अणु
		i = TX_ATIM_FIFO;
		err = -1;
	पूर्ण
	अगर (err != 0)
		brcms_err(core, "wlc_coreinit: txfifo mismatch: ucode size %d"
			  " driver size %d index %d\n", buf[i],
			  wlc_hw->xmtfअगरo_sz[i], i);

	/* make sure we can still talk to the mac */
	WARN_ON(bcma_पढ़ो32(core, D11REGOFFS(maccontrol)) == 0xffffffff);

	/* band-specअगरic inits करोne by wlc_bsinit() */

	/* Set up frame burst size and antenna swap threshold init values */
	brcms_b_ग_लिखो_shm(wlc_hw, M_MBURST_SIZE, MAXTXFRAMEBURST);
	brcms_b_ग_लिखो_shm(wlc_hw, M_MAX_ANTCNT, ANTCNT);

	/* enable one rx पूर्णांकerrupt per received frame */
	bcma_ग_लिखो32(core, D11REGOFFS(पूर्णांकrcvlazy[0]), (1 << IRL_FC_SHIFT));

	/* set the station mode (BSS STA) */
	brcms_b_mctrl(wlc_hw,
		       (MCTL_INFRA | MCTL_DISCARD_PMQ | MCTL_AP),
		       (MCTL_INFRA | MCTL_DISCARD_PMQ));

	/* set up Beacon पूर्णांकerval */
	bcnपूर्णांक_us = 0x8000 << 10;
	bcma_ग_लिखो32(core, D11REGOFFS(tsf_cfprep),
		     (bcnपूर्णांक_us << CFPREP_CBI_SHIFT));
	bcma_ग_लिखो32(core, D11REGOFFS(tsf_cfpstart), bcnपूर्णांक_us);
	bcma_ग_लिखो32(core, D11REGOFFS(macपूर्णांकstatus), MI_GP1);

	/* ग_लिखो पूर्णांकerrupt mask */
	bcma_ग_लिखो32(core, D11REGOFFS(पूर्णांकctrlregs[RX_FIFO].पूर्णांकmask),
		     DEF_RXINTMASK);

	/* allow the MAC to control the PHY घड़ी (dynamic on/off) */
	brcms_b_macphyclk_set(wlc_hw, ON);

	/* program dynamic घड़ी control fast घातerup delay रेजिस्टर */
	wlc->fastpwrup_dly = ai_clkctl_fast_pwrup_delay(wlc_hw->sih);
	bcma_ग_लिखो16(core, D11REGOFFS(scc_fastpwrup_dly), wlc->fastpwrup_dly);

	/* tell the ucode the corerev */
	brcms_b_ग_लिखो_shm(wlc_hw, M_MACHW_VER, (u16) wlc_hw->corerev);

	/* tell the ucode MAC capabilities */
	brcms_b_ग_लिखो_shm(wlc_hw, M_MACHW_CAP_L,
			   (u16) (wlc_hw->machwcap & 0xffff));
	brcms_b_ग_लिखो_shm(wlc_hw, M_MACHW_CAP_H,
			   (u16) ((wlc_hw->
				      machwcap >> 16) & 0xffff));

	/* ग_लिखो retry limits to SCR, this करोne after PSM init */
	bcma_ग_लिखो32(core, D11REGOFFS(objaddr),
		     OBJADDR_SCR_SEL | S_DOT11_SRC_LMT);
	(व्योम)bcma_पढ़ो32(core, D11REGOFFS(objaddr));
	bcma_ग_लिखो32(core, D11REGOFFS(objdata), wlc_hw->SRL);
	bcma_ग_लिखो32(core, D11REGOFFS(objaddr),
		     OBJADDR_SCR_SEL | S_DOT11_LRC_LMT);
	(व्योम)bcma_पढ़ो32(core, D11REGOFFS(objaddr));
	bcma_ग_लिखो32(core, D11REGOFFS(objdata), wlc_hw->LRL);

	/* ग_लिखो rate fallback retry limits */
	brcms_b_ग_लिखो_shm(wlc_hw, M_SFRMTXCNTFBRTHSD, wlc_hw->SFBL);
	brcms_b_ग_लिखो_shm(wlc_hw, M_LFRMTXCNTFBRTHSD, wlc_hw->LFBL);

	bcma_mask16(core, D11REGOFFS(अगरs_ctl), 0x0FFF);
	bcma_ग_लिखो16(core, D11REGOFFS(अगरs_aअगरsn), EDCF_AIFSN_MIN);

	/* init the tx dma engines */
	क्रम (i = 0; i < NFIFO; i++) अणु
		अगर (wlc_hw->di[i])
			dma_txinit(wlc_hw->di[i]);
	पूर्ण

	/* init the rx dma engine(s) and post receive buffers */
	dma_rxinit(wlc_hw->di[RX_FIFO]);
	dma_rxfill(wlc_hw->di[RX_FIFO]);
पूर्ण

अटल व्योम brcms_b_init(काष्ठा brcms_hardware *wlc_hw, u16 chanspec)
अणु
	u32 macपूर्णांकmask;
	bool fastclk;
	काष्ठा brcms_c_info *wlc = wlc_hw->wlc;

	/* request FAST घड़ी अगर not on */
	fastclk = wlc_hw->क्रमcefastclk;
	अगर (!fastclk)
		brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_FAST);

	/* disable पूर्णांकerrupts */
	macपूर्णांकmask = brcms_पूर्णांकrsoff(wlc->wl);

	/* set up the specअगरied band and chanspec */
	brcms_c_setxband(wlc_hw, chspec_bandunit(chanspec));
	wlc_phy_chanspec_radio_set(wlc_hw->band->pi, chanspec);

	/* करो one-समय phy inits and calibration */
	wlc_phy_cal_init(wlc_hw->band->pi);

	/* core-specअगरic initialization */
	brcms_b_coreinit(wlc);

	/* band-specअगरic inits */
	brcms_b_bsinit(wlc, chanspec);

	/* restore macपूर्णांकmask */
	brcms_पूर्णांकrsrestore(wlc->wl, macपूर्णांकmask);

	/* seed wake_override with BRCMS_WAKE_OVERRIDE_MACSUSPEND since the mac
	 * is suspended and brcms_c_enable_mac() will clear this override bit.
	 */
	mboolset(wlc_hw->wake_override, BRCMS_WAKE_OVERRIDE_MACSUSPEND);

	/*
	 * initialize mac_suspend_depth to 1 to match ucode
	 * initial suspended state
	 */
	wlc_hw->mac_suspend_depth = 1;

	/* restore the clk */
	अगर (!fastclk)
		brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_DYNAMIC);
पूर्ण

अटल व्योम brcms_c_set_phy_chanspec(काष्ठा brcms_c_info *wlc,
				     u16 chanspec)
अणु
	/* Save our copy of the chanspec */
	wlc->chanspec = chanspec;

	/* Set the chanspec and घातer limits क्रम this locale */
	brcms_c_channel_set_chanspec(wlc->cmi, chanspec, BRCMS_TXPWR_MAX);

	अगर (wlc->stf->ss_algosel_स्वतः)
		brcms_c_stf_ss_algo_channel_get(wlc, &wlc->stf->ss_algo_channel,
					    chanspec);

	brcms_c_stf_ss_update(wlc, wlc->band);
पूर्ण

अटल व्योम
brcms_शेष_rateset(काष्ठा brcms_c_info *wlc, काष्ठा brcms_c_rateset *rs)
अणु
	brcms_c_rateset_शेष(rs, शून्य, wlc->band->phytype,
		wlc->band->bandtype, false, BRCMS_RATE_MASK_FULL,
		(bool) (wlc->pub->_n_enab & SUPPORT_11N),
		brcms_chspec_bw(wlc->शेष_bss->chanspec),
		wlc->stf->txstreams);
पूर्ण

/* derive wlc->band->basic_rate[] table from 'rateset' */
अटल व्योम brcms_c_rate_lookup_init(काष्ठा brcms_c_info *wlc,
			      काष्ठा brcms_c_rateset *rateset)
अणु
	u8 rate;
	u8 mandatory;
	u8 cck_basic = 0;
	u8 ofdm_basic = 0;
	u8 *br = wlc->band->basic_rate;
	uपूर्णांक i;

	/* incoming rates are in 500kbps units as in 802.11 Supported Rates */
	स_रखो(br, 0, BRCM_MAXRATE + 1);

	/* For each basic rate in the rates list, make an entry in the
	 * best basic lookup.
	 */
	क्रम (i = 0; i < rateset->count; i++) अणु
		/* only make an entry क्रम a basic rate */
		अगर (!(rateset->rates[i] & BRCMS_RATE_FLAG))
			जारी;

		/* mask off basic bit */
		rate = (rateset->rates[i] & BRCMS_RATE_MASK);

		अगर (rate > BRCM_MAXRATE) अणु
			brcms_err(wlc->hw->d11core, "brcms_c_rate_lookup_init: "
				  "invalid rate 0x%X in rate set\n",
				  rateset->rates[i]);
			जारी;
		पूर्ण

		br[rate] = rate;
	पूर्ण

	/* The rate lookup table now has non-zero entries क्रम each
	 * basic rate, equal to the basic rate: br[basicN] = basicN
	 *
	 * To look up the best basic rate corresponding to any
	 * particular rate, code can use the basic_rate table
	 * like this
	 *
	 * basic_rate = wlc->band->basic_rate[tx_rate]
	 *
	 * Make sure there is a best basic rate entry क्रम
	 * every rate by walking up the table from low rates
	 * to high, filling in holes in the lookup table
	 */

	क्रम (i = 0; i < wlc->band->hw_rateset.count; i++) अणु
		rate = wlc->band->hw_rateset.rates[i];

		अगर (br[rate] != 0) अणु
			/* This rate is a basic rate.
			 * Keep track of the best basic rate so far by
			 * modulation type.
			 */
			अगर (is_ofdm_rate(rate))
				ofdm_basic = rate;
			अन्यथा
				cck_basic = rate;

			जारी;
		पूर्ण

		/* This rate is not a basic rate so figure out the
		 * best basic rate less than this rate and fill in
		 * the hole in the table
		 */

		br[rate] = is_ofdm_rate(rate) ? ofdm_basic : cck_basic;

		अगर (br[rate] != 0)
			जारी;

		अगर (is_ofdm_rate(rate)) अणु
			/*
			 * In 11g and 11a, the OFDM mandatory rates
			 * are 6, 12, and 24 Mbps
			 */
			अगर (rate >= BRCM_RATE_24M)
				mandatory = BRCM_RATE_24M;
			अन्यथा अगर (rate >= BRCM_RATE_12M)
				mandatory = BRCM_RATE_12M;
			अन्यथा
				mandatory = BRCM_RATE_6M;
		पूर्ण अन्यथा अणु
			/* In 11b, all CCK rates are mandatory 1 - 11 Mbps */
			mandatory = rate;
		पूर्ण

		br[rate] = mandatory;
	पूर्ण
पूर्ण

अटल व्योम brcms_c_bandinit_ordered(काष्ठा brcms_c_info *wlc,
				     u16 chanspec)
अणु
	काष्ठा brcms_c_rateset शेष_rateset;
	uपूर्णांक parkband;
	uपूर्णांक i, band_order[2];

	/*
	 * We might have been bandlocked during करोwn and the chip
	 * घातer-cycled (hibernate). Figure out the right band to park on
	 */
	अगर (wlc->bandlocked || wlc->pub->_nbands == 1) अणु
		/* updated in brcms_c_bandlock() */
		parkband = wlc->band->bandunit;
		band_order[0] = band_order[1] = parkband;
	पूर्ण अन्यथा अणु
		/* park on the band of the specअगरied chanspec */
		parkband = chspec_bandunit(chanspec);

		/* order so that parkband initialize last */
		band_order[0] = parkband ^ 1;
		band_order[1] = parkband;
	पूर्ण

	/* make each band operational, software state init */
	क्रम (i = 0; i < wlc->pub->_nbands; i++) अणु
		uपूर्णांक j = band_order[i];

		wlc->band = wlc->bandstate[j];

		brcms_शेष_rateset(wlc, &शेष_rateset);

		/* fill in hw_rate */
		brcms_c_rateset_filter(&शेष_rateset, &wlc->band->hw_rateset,
				   false, BRCMS_RATES_CCK_OFDM, BRCMS_RATE_MASK,
				   (bool) (wlc->pub->_n_enab & SUPPORT_11N));

		/* init basic rate lookup */
		brcms_c_rate_lookup_init(wlc, &शेष_rateset);
	पूर्ण

	/* sync up phy/radio chanspec */
	brcms_c_set_phy_chanspec(wlc, chanspec);
पूर्ण

/*
 * Set or clear filtering related maccontrol bits based on
 * specअगरied filter flags
 */
व्योम brcms_c_mac_promisc(काष्ठा brcms_c_info *wlc, uपूर्णांक filter_flags)
अणु
	u32 promisc_bits = 0;

	wlc->filter_flags = filter_flags;

	अगर (filter_flags & FIF_OTHER_BSS)
		promisc_bits |= MCTL_PROMISC;

	अगर (filter_flags & FIF_BCN_PRBRESP_PROMISC)
		promisc_bits |= MCTL_BCNS_PROMISC;

	अगर (filter_flags & FIF_FCSFAIL)
		promisc_bits |= MCTL_KEEPBADFCS;

	अगर (filter_flags & (FIF_CONTROL | FIF_PSPOLL))
		promisc_bits |= MCTL_KEEPCONTROL;

	brcms_b_mctrl(wlc->hw,
		MCTL_PROMISC | MCTL_BCNS_PROMISC |
		MCTL_KEEPCONTROL | MCTL_KEEPBADFCS,
		promisc_bits);
पूर्ण

/*
 * ucode, hwmac update
 *    Channel dependent updates क्रम ucode and hw
 */
अटल व्योम brcms_c_ucode_mac_upd(काष्ठा brcms_c_info *wlc)
अणु
	/* enable or disable any active IBSSs depending on whether or not
	 * we are on the home channel
	 */
	अगर (wlc->home_chanspec == wlc_phy_chanspec_get(wlc->band->pi)) अणु
		अगर (wlc->pub->associated) अणु
			/*
			 * BMAC_NOTE: This is something that should be fixed
			 * in ucode inits. I think that the ucode inits set
			 * up the bcn ढाँचाs and shm values with a bogus
			 * beacon. This should not be करोne in the inits. If
			 * ucode needs to set up a beacon क्रम testing, the
			 * test routines should ग_लिखो it करोwn, not expect the
			 * inits to populate a bogus beacon.
			 */
			अगर (BRCMS_PHY_11N_CAP(wlc->band))
				brcms_b_ग_लिखो_shm(wlc->hw,
						M_BCN_TXTSF_OFFSET, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* disable an active IBSS अगर we are not on the home channel */
	पूर्ण
पूर्ण

अटल व्योम brcms_c_ग_लिखो_rate_shm(काष्ठा brcms_c_info *wlc, u8 rate,
				   u8 basic_rate)
अणु
	u8 phy_rate, index;
	u8 basic_phy_rate, basic_index;
	u16 dir_table, basic_table;
	u16 basic_ptr;

	/* Shared memory address क्रम the table we are पढ़ोing */
	dir_table = is_ofdm_rate(basic_rate) ? M_RT_सूचीMAP_A : M_RT_सूचीMAP_B;

	/* Shared memory address क्रम the table we are writing */
	basic_table = is_ofdm_rate(rate) ? M_RT_BBRSMAP_A : M_RT_BBRSMAP_B;

	/*
	 * क्रम a given rate, the LS-nibble of the PLCP SIGNAL field is
	 * the index पूर्णांकo the rate table.
	 */
	phy_rate = rate_info[rate] & BRCMS_RATE_MASK;
	basic_phy_rate = rate_info[basic_rate] & BRCMS_RATE_MASK;
	index = phy_rate & 0xf;
	basic_index = basic_phy_rate & 0xf;

	/* Find the SHM poपूर्णांकer to the ACK rate entry by looking in the
	 * Direct-map Table
	 */
	basic_ptr = brcms_b_पढ़ो_shm(wlc->hw, (dir_table + basic_index * 2));

	/* Update the SHM BSS-basic-rate-set mapping table with the poपूर्णांकer
	 * to the correct basic rate क्रम the given incoming rate
	 */
	brcms_b_ग_लिखो_shm(wlc->hw, (basic_table + index * 2), basic_ptr);
पूर्ण

अटल स्थिर काष्ठा brcms_c_rateset *
brcms_c_rateset_get_hwrs(काष्ठा brcms_c_info *wlc)
अणु
	स्थिर काष्ठा brcms_c_rateset *rs_dflt;

	अगर (BRCMS_PHY_11N_CAP(wlc->band)) अणु
		अगर (wlc->band->bandtype == BRCM_BAND_5G)
			rs_dflt = &ofdm_mimo_rates;
		अन्यथा
			rs_dflt = &cck_ofdm_mimo_rates;
	पूर्ण अन्यथा अगर (wlc->band->gmode)
		rs_dflt = &cck_ofdm_rates;
	अन्यथा
		rs_dflt = &cck_rates;

	वापस rs_dflt;
पूर्ण

अटल व्योम brcms_c_set_ratetable(काष्ठा brcms_c_info *wlc)
अणु
	स्थिर काष्ठा brcms_c_rateset *rs_dflt;
	काष्ठा brcms_c_rateset rs;
	u8 rate, basic_rate;
	uपूर्णांक i;

	rs_dflt = brcms_c_rateset_get_hwrs(wlc);

	brcms_c_rateset_copy(rs_dflt, &rs);
	brcms_c_rateset_mcs_upd(&rs, wlc->stf->txstreams);

	/* walk the phy rate table and update SHM basic rate lookup table */
	क्रम (i = 0; i < rs.count; i++) अणु
		rate = rs.rates[i] & BRCMS_RATE_MASK;

		/* क्रम a given rate brcms_basic_rate वापसs the rate at
		 * which a response ACK/CTS should be sent.
		 */
		basic_rate = brcms_basic_rate(wlc, rate);
		अगर (basic_rate == 0)
			/* This should only happen अगर we are using a
			 * restricted rateset.
			 */
			basic_rate = rs.rates[0] & BRCMS_RATE_MASK;

		brcms_c_ग_लिखो_rate_shm(wlc, rate, basic_rate);
	पूर्ण
पूर्ण

/* band-specअगरic init */
अटल व्योम brcms_c_bsinit(काष्ठा brcms_c_info *wlc)
अणु
	brcms_dbg_info(wlc->hw->d11core, "wl%d: bandunit %d\n",
		       wlc->pub->unit, wlc->band->bandunit);

	/* ग_लिखो ucode ACK/CTS rate table */
	brcms_c_set_ratetable(wlc);

	/* update some band specअगरic mac configuration */
	brcms_c_ucode_mac_upd(wlc);

	/* init antenna selection */
	brcms_c_antsel_init(wlc->asi);

पूर्ण

/* क्रमmula:  IDLE_BUSY_RATIO_X_16 = (100-duty_cycle)/duty_cycle*16 */
अटल पूर्णांक
brcms_c_duty_cycle_set(काष्ठा brcms_c_info *wlc, पूर्णांक duty_cycle, bool isOFDM,
		   bool ग_लिखोToShm)
अणु
	पूर्णांक idle_busy_ratio_x_16 = 0;
	uपूर्णांक offset =
	    isOFDM ? M_TX_IDLE_BUSY_RATIO_X_16_OFDM :
	    M_TX_IDLE_BUSY_RATIO_X_16_CCK;
	अगर (duty_cycle > 100 || duty_cycle < 0) अणु
		brcms_err(wlc->hw->d11core,
			  "wl%d:  duty cycle value off limit\n",
			  wlc->pub->unit);
		वापस -EINVAL;
	पूर्ण
	अगर (duty_cycle)
		idle_busy_ratio_x_16 = (100 - duty_cycle) * 16 / duty_cycle;
	/* Only ग_लिखो to shared memory  when wl is up */
	अगर (ग_लिखोToShm)
		brcms_b_ग_लिखो_shm(wlc->hw, offset, (u16) idle_busy_ratio_x_16);

	अगर (isOFDM)
		wlc->tx_duty_cycle_ofdm = (u16) duty_cycle;
	अन्यथा
		wlc->tx_duty_cycle_cck = (u16) duty_cycle;

	वापस 0;
पूर्ण

/* push sw hps and wake state through hardware */
अटल व्योम brcms_c_set_ps_ctrl(काष्ठा brcms_c_info *wlc)
अणु
	u32 v1, v2;
	bool hps;
	bool awake_beक्रमe;

	hps = brcms_c_ps_allowed(wlc);

	brcms_dbg_mac80211(wlc->hw->d11core, "wl%d: hps %d\n", wlc->pub->unit,
			   hps);

	v1 = bcma_पढ़ो32(wlc->hw->d11core, D11REGOFFS(maccontrol));
	v2 = MCTL_WAKE;
	अगर (hps)
		v2 |= MCTL_HPS;

	brcms_b_mctrl(wlc->hw, MCTL_WAKE | MCTL_HPS, v2);

	awake_beक्रमe = ((v1 & MCTL_WAKE) || ((v1 & MCTL_HPS) == 0));

	अगर (!awake_beक्रमe)
		brcms_b_रुको_क्रम_wake(wlc->hw);
पूर्ण

/*
 * Write this BSS config's MAC address to core.
 * Updates RXE match engine.
 */
अटल व्योम brcms_c_set_mac(काष्ठा brcms_bss_cfg *bsscfg)
अणु
	काष्ठा brcms_c_info *wlc = bsscfg->wlc;

	/* enter the MAC addr पूर्णांकo the RXE match रेजिस्टरs */
	brcms_c_set_addrmatch(wlc, RCM_MAC_OFFSET, wlc->pub->cur_etheraddr);

	brcms_c_ampdu_macaddr_upd(wlc);
पूर्ण

/* Write the BSS config's BSSID address to core (set_bssid in d11procs.tcl).
 * Updates RXE match engine.
 */
अटल व्योम brcms_c_set_bssid(काष्ठा brcms_bss_cfg *bsscfg)
अणु
	/* we need to update BSSID in RXE match रेजिस्टरs */
	brcms_c_set_addrmatch(bsscfg->wlc, RCM_BSSID_OFFSET, bsscfg->BSSID);
पूर्ण

व्योम brcms_c_set_ssid(काष्ठा brcms_c_info *wlc, u8 *ssid, माप_प्रकार ssid_len)
अणु
	u8 len = min_t(u8, माप(wlc->bsscfg->SSID), ssid_len);
	स_रखो(wlc->bsscfg->SSID, 0, माप(wlc->bsscfg->SSID));

	स_नकल(wlc->bsscfg->SSID, ssid, len);
	wlc->bsscfg->SSID_len = len;
पूर्ण

अटल व्योम brcms_b_set_लघुslot(काष्ठा brcms_hardware *wlc_hw, bool लघुslot)
अणु
	wlc_hw->लघुslot = लघुslot;

	अगर (wlc_hw->band->bandtype == BRCM_BAND_2G && wlc_hw->up) अणु
		brcms_c_suspend_mac_and_रुको(wlc_hw->wlc);
		brcms_b_update_slot_timing(wlc_hw, लघुslot);
		brcms_c_enable_mac(wlc_hw->wlc);
	पूर्ण
पूर्ण

/*
 * Suspend the the MAC and update the slot timing
 * क्रम standard 11b/g (20us slots) or लघुslot 11g (9us slots).
 */
अटल व्योम brcms_c_चयन_लघुslot(काष्ठा brcms_c_info *wlc, bool लघुslot)
अणु
	/* use the override अगर it is set */
	अगर (wlc->लघुslot_override != BRCMS_SHORTSLOT_AUTO)
		लघुslot = (wlc->लघुslot_override == BRCMS_SHORTSLOT_ON);

	अगर (wlc->लघुslot == लघुslot)
		वापस;

	wlc->लघुslot = लघुslot;

	brcms_b_set_लघुslot(wlc->hw, लघुslot);
पूर्ण

अटल व्योम brcms_c_set_home_chanspec(काष्ठा brcms_c_info *wlc, u16 chanspec)
अणु
	अगर (wlc->home_chanspec != chanspec) अणु
		wlc->home_chanspec = chanspec;

		अगर (wlc->pub->associated)
			wlc->bsscfg->current_bss->chanspec = chanspec;
	पूर्ण
पूर्ण

व्योम
brcms_b_set_chanspec(काष्ठा brcms_hardware *wlc_hw, u16 chanspec,
		      bool mute_tx, काष्ठा txpwr_limits *txpwr)
अणु
	uपूर्णांक bandunit;

	brcms_dbg_mac80211(wlc_hw->d11core, "wl%d: 0x%x\n", wlc_hw->unit,
			   chanspec);

	wlc_hw->chanspec = chanspec;

	/* Switch bands अगर necessary */
	अगर (wlc_hw->_nbands > 1) अणु
		bandunit = chspec_bandunit(chanspec);
		अगर (wlc_hw->band->bandunit != bandunit) अणु
			/* brcms_b_setband disables other bandunit,
			 *  use light band चयन अगर not up yet
			 */
			अगर (wlc_hw->up) अणु
				wlc_phy_chanspec_radio_set(wlc_hw->
							   bandstate[bandunit]->
							   pi, chanspec);
				brcms_b_setband(wlc_hw, bandunit, chanspec);
			पूर्ण अन्यथा अणु
				brcms_c_setxband(wlc_hw, bandunit);
			पूर्ण
		पूर्ण
	पूर्ण

	wlc_phy_initcal_enable(wlc_hw->band->pi, !mute_tx);

	अगर (!wlc_hw->up) अणु
		अगर (wlc_hw->clk)
			wlc_phy_txघातer_limit_set(wlc_hw->band->pi, txpwr,
						  chanspec);
		wlc_phy_chanspec_radio_set(wlc_hw->band->pi, chanspec);
	पूर्ण अन्यथा अणु
		wlc_phy_chanspec_set(wlc_hw->band->pi, chanspec);
		wlc_phy_txघातer_limit_set(wlc_hw->band->pi, txpwr, chanspec);

		/* Update muting of the channel */
		brcms_b_mute(wlc_hw, mute_tx);
	पूर्ण
पूर्ण

/* चयन to and initialize new band */
अटल व्योम brcms_c_setband(काष्ठा brcms_c_info *wlc,
					   uपूर्णांक bandunit)
अणु
	wlc->band = wlc->bandstate[bandunit];

	अगर (!wlc->pub->up)
		वापस;

	/* रुको क्रम at least one beacon beक्रमe entering sleeping state */
	brcms_c_set_ps_ctrl(wlc);

	/* band-specअगरic initializations */
	brcms_c_bsinit(wlc);
पूर्ण

अटल व्योम brcms_c_set_chanspec(काष्ठा brcms_c_info *wlc, u16 chanspec)
अणु
	uपूर्णांक bandunit;
	u16 old_chanspec = wlc->chanspec;

	अगर (!brcms_c_valid_chanspec_db(wlc->cmi, chanspec)) अणु
		brcms_err(wlc->hw->d11core, "wl%d: %s: Bad channel %d\n",
			  wlc->pub->unit, __func__, CHSPEC_CHANNEL(chanspec));
		वापस;
	पूर्ण

	/* Switch bands अगर necessary */
	अगर (wlc->pub->_nbands > 1) अणु
		bandunit = chspec_bandunit(chanspec);
		अगर (wlc->band->bandunit != bandunit || wlc->bandinit_pending) अणु
			अगर (wlc->bandlocked) अणु
				brcms_err(wlc->hw->d11core,
					  "wl%d: %s: chspec %d band is locked!\n",
					  wlc->pub->unit, __func__,
					  CHSPEC_CHANNEL(chanspec));
				वापस;
			पूर्ण
			/*
			 * should the setband call come after the
			 * brcms_b_chanspec() ? अगर the setband updates
			 * (brcms_c_bsinit) use low level calls to inspect and
			 * set state, the state inspected may be from the wrong
			 * band, or the following brcms_b_set_chanspec() may
			 * unकरो the work.
			 */
			brcms_c_setband(wlc, bandunit);
		पूर्ण
	पूर्ण

	/* sync up phy/radio chanspec */
	brcms_c_set_phy_chanspec(wlc, chanspec);

	/* init antenna selection */
	अगर (brcms_chspec_bw(old_chanspec) != brcms_chspec_bw(chanspec)) अणु
		brcms_c_antsel_init(wlc->asi);

		/* Fix the hardware rateset based on bw.
		 * Mainly add MCS32 क्रम 40Mhz, हटाओ MCS 32 क्रम 20Mhz
		 */
		brcms_c_rateset_bw_mcs_filter(&wlc->band->hw_rateset,
			wlc->band->mimo_cap_40 ? brcms_chspec_bw(chanspec) : 0);
	पूर्ण

	/* update some mac configuration since chanspec changed */
	brcms_c_ucode_mac_upd(wlc);
पूर्ण

/*
 * This function changes the phytxctl क्रम beacon based on current
 * beacon ratespec AND txant setting as per this table:
 *  ratespec     CCK		ant = wlc->stf->txant
 *		OFDM		ant = 3
 */
व्योम brcms_c_beacon_phytxctl_txant_upd(काष्ठा brcms_c_info *wlc,
				       u32 bcn_rspec)
अणु
	u16 phyctl;
	u16 phytxant = wlc->stf->phytxant;
	u16 mask = PHY_TXC_ANT_MASK;

	/* क्रम non-siso rates or शेष setting, use the available chains */
	अगर (BRCMS_PHY_11N_CAP(wlc->band))
		phytxant = brcms_c_stf_phytxchain_sel(wlc, bcn_rspec);

	phyctl = brcms_b_पढ़ो_shm(wlc->hw, M_BCN_PCTLWD);
	phyctl = (phyctl & ~mask) | phytxant;
	brcms_b_ग_लिखो_shm(wlc->hw, M_BCN_PCTLWD, phyctl);
पूर्ण

/*
 * centralized protection config change function to simplअगरy debugging, no
 * consistency checking this should be called only on changes to aव्योम overhead
 * in periodic function
 */
व्योम brcms_c_protection_upd(काष्ठा brcms_c_info *wlc, uपूर्णांक idx, पूर्णांक val)
अणु
	/*
	 * Cannot use brcms_dbg_* here because this function is called
	 * beक्रमe wlc is sufficiently initialized.
	 */
	BCMMSG(wlc->wiphy, "idx %d, val %d\n", idx, val);

	चयन (idx) अणु
	हाल BRCMS_PROT_G_SPEC:
		wlc->protection->_g = (bool) val;
		अवरोध;
	हाल BRCMS_PROT_G_OVR:
		wlc->protection->g_override = (s8) val;
		अवरोध;
	हाल BRCMS_PROT_G_USER:
		wlc->protection->gmode_user = (u8) val;
		अवरोध;
	हाल BRCMS_PROT_OVERLAP:
		wlc->protection->overlap = (s8) val;
		अवरोध;
	हाल BRCMS_PROT_N_USER:
		wlc->protection->nmode_user = (s8) val;
		अवरोध;
	हाल BRCMS_PROT_N_CFG:
		wlc->protection->n_cfg = (s8) val;
		अवरोध;
	हाल BRCMS_PROT_N_CFG_OVR:
		wlc->protection->n_cfg_override = (s8) val;
		अवरोध;
	हाल BRCMS_PROT_N_NONGF:
		wlc->protection->nongf = (bool) val;
		अवरोध;
	हाल BRCMS_PROT_N_NONGF_OVR:
		wlc->protection->nongf_override = (s8) val;
		अवरोध;
	हाल BRCMS_PROT_N_PAM_OVR:
		wlc->protection->n_pam_override = (s8) val;
		अवरोध;
	हाल BRCMS_PROT_N_OBSS:
		wlc->protection->n_obss = (bool) val;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

पूर्ण

अटल व्योम brcms_c_ht_update_sgi_rx(काष्ठा brcms_c_info *wlc, पूर्णांक val)
अणु
	अगर (wlc->pub->up) अणु
		brcms_c_update_beacon(wlc);
		brcms_c_update_probe_resp(wlc, true);
	पूर्ण
पूर्ण

अटल व्योम brcms_c_ht_update_ldpc(काष्ठा brcms_c_info *wlc, s8 val)
अणु
	wlc->stf->ldpc = val;

	अगर (wlc->pub->up) अणु
		brcms_c_update_beacon(wlc);
		brcms_c_update_probe_resp(wlc, true);
		wlc_phy_ldpc_override_set(wlc->band->pi, (val ? true : false));
	पूर्ण
पूर्ण

व्योम brcms_c_wme_setparams(काष्ठा brcms_c_info *wlc, u16 aci,
		       स्थिर काष्ठा ieee80211_tx_queue_params *params,
		       bool suspend)
अणु
	पूर्णांक i;
	काष्ठा shm_acparams acp_shm;
	u16 *shm_entry;

	/* Only apply params अगर the core is out of reset and has घड़ीs */
	अगर (!wlc->clk) अणु
		brcms_err(wlc->hw->d11core, "wl%d: %s : no-clock\n",
			  wlc->pub->unit, __func__);
		वापस;
	पूर्ण

	स_रखो(&acp_shm, 0, माप(काष्ठा shm_acparams));
	/* fill in shm ac params काष्ठा */
	acp_shm.txop = params->txop;
	/* convert from units of 32us to us क्रम ucode */
	wlc->edcf_txop[aci & 0x3] = acp_shm.txop =
	    EDCF_TXOP2USEC(acp_shm.txop);
	acp_shm.aअगरs = (params->aअगरs & EDCF_AIFSN_MASK);

	अगर (aci == IEEE80211_AC_VI && acp_shm.txop == 0
	    && acp_shm.aअगरs < EDCF_AIFSN_MAX)
		acp_shm.aअगरs++;

	अगर (acp_shm.aअगरs < EDCF_AIFSN_MIN
	    || acp_shm.aअगरs > EDCF_AIFSN_MAX) अणु
		brcms_err(wlc->hw->d11core, "wl%d: edcf_setparams: bad "
			  "aifs %d\n", wlc->pub->unit, acp_shm.aअगरs);
	पूर्ण अन्यथा अणु
		acp_shm.cwmin = params->cw_min;
		acp_shm.cwmax = params->cw_max;
		acp_shm.cwcur = acp_shm.cwmin;
		acp_shm.bslots =
			bcma_पढ़ो16(wlc->hw->d11core, D11REGOFFS(tsf_अक्रमom)) &
			acp_shm.cwcur;
		acp_shm.reggap = acp_shm.bslots + acp_shm.aअगरs;
		/* Indicate the new params to the ucode */
		acp_shm.status = brcms_b_पढ़ो_shm(wlc->hw, (M_EDCF_QINFO +
						  wme_ac2fअगरo[aci] *
						  M_EDCF_QLEN +
						  M_EDCF_STATUS_OFF));
		acp_shm.status |= WME_STATUS_NEWAC;

		/* Fill in shm acparam table */
		shm_entry = (u16 *) &acp_shm;
		क्रम (i = 0; i < (पूर्णांक)माप(काष्ठा shm_acparams); i += 2)
			brcms_b_ग_लिखो_shm(wlc->hw,
					  M_EDCF_QINFO +
					  wme_ac2fअगरo[aci] * M_EDCF_QLEN + i,
					  *shm_entry++);
	पूर्ण

	अगर (suspend)
		brcms_c_suspend_mac_and_रुको(wlc);

	brcms_c_update_beacon(wlc);
	brcms_c_update_probe_resp(wlc, false);

	अगर (suspend)
		brcms_c_enable_mac(wlc);
पूर्ण

अटल व्योम brcms_c_edcf_setparams(काष्ठा brcms_c_info *wlc, bool suspend)
अणु
	u16 aci;
	पूर्णांक i_ac;
	काष्ठा ieee80211_tx_queue_params txq_pars;
	अटल स्थिर काष्ठा edcf_acparam शेष_edcf_acparams[] = अणु
		 अणुEDCF_AC_BE_ACI_STA, EDCF_AC_BE_ECW_STA, EDCF_AC_BE_TXOP_STAपूर्ण,
		 अणुEDCF_AC_BK_ACI_STA, EDCF_AC_BK_ECW_STA, EDCF_AC_BK_TXOP_STAपूर्ण,
		 अणुEDCF_AC_VI_ACI_STA, EDCF_AC_VI_ECW_STA, EDCF_AC_VI_TXOP_STAपूर्ण,
		 अणुEDCF_AC_VO_ACI_STA, EDCF_AC_VO_ECW_STA, EDCF_AC_VO_TXOP_STAपूर्ण
	पूर्ण; /* ucode needs these parameters during its initialization */
	स्थिर काष्ठा edcf_acparam *edcf_acp = &शेष_edcf_acparams[0];

	क्रम (i_ac = 0; i_ac < IEEE80211_NUM_ACS; i_ac++, edcf_acp++) अणु
		/* find out which ac this set of params applies to */
		aci = (edcf_acp->ACI & EDCF_ACI_MASK) >> EDCF_ACI_SHIFT;

		/* fill in shm ac params काष्ठा */
		txq_pars.txop = edcf_acp->TXOP;
		txq_pars.aअगरs = edcf_acp->ACI;

		/* CWmin = 2^(ECWmin) - 1 */
		txq_pars.cw_min = EDCF_ECW2CW(edcf_acp->ECW & EDCF_ECWMIN_MASK);
		/* CWmax = 2^(ECWmax) - 1 */
		txq_pars.cw_max = EDCF_ECW2CW((edcf_acp->ECW & EDCF_ECWMAX_MASK)
					    >> EDCF_ECWMAX_SHIFT);
		brcms_c_wme_setparams(wlc, aci, &txq_pars, suspend);
	पूर्ण

	अगर (suspend) अणु
		brcms_c_suspend_mac_and_रुको(wlc);
		brcms_c_enable_mac(wlc);
	पूर्ण
पूर्ण

अटल व्योम brcms_c_radio_monitor_start(काष्ठा brcms_c_info *wlc)
अणु
	/* Don't start the समयr अगर HWRADIO feature is disabled */
	अगर (wlc->radio_monitor)
		वापस;

	wlc->radio_monitor = true;
	brcms_b_pllreq(wlc->hw, true, BRCMS_PLLREQ_RADIO_MON);
	brcms_add_समयr(wlc->radio_समयr, TIMER_INTERVAL_RADIOCHK, true);
पूर्ण

अटल bool brcms_c_radio_monitor_stop(काष्ठा brcms_c_info *wlc)
अणु
	अगर (!wlc->radio_monitor)
		वापस true;

	wlc->radio_monitor = false;
	brcms_b_pllreq(wlc->hw, false, BRCMS_PLLREQ_RADIO_MON);
	वापस brcms_del_समयr(wlc->radio_समयr);
पूर्ण

/* पढ़ो hwdisable state and propagate to wlc flag */
अटल व्योम brcms_c_radio_hwdisable_upd(काष्ठा brcms_c_info *wlc)
अणु
	अगर (wlc->pub->hw_off)
		वापस;

	अगर (brcms_b_radio_पढ़ो_hwdisabled(wlc->hw))
		mboolset(wlc->pub->radio_disabled, WL_RADIO_HW_DISABLE);
	अन्यथा
		mboolclr(wlc->pub->radio_disabled, WL_RADIO_HW_DISABLE);
पूर्ण

/* update hwradio status and वापस it */
bool brcms_c_check_radio_disabled(काष्ठा brcms_c_info *wlc)
अणु
	brcms_c_radio_hwdisable_upd(wlc);

	वापस mboolisset(wlc->pub->radio_disabled, WL_RADIO_HW_DISABLE) ?
			true : false;
पूर्ण

/* periodical query hw radio button जबतक driver is "down" */
अटल व्योम brcms_c_radio_समयr(व्योम *arg)
अणु
	काष्ठा brcms_c_info *wlc = (काष्ठा brcms_c_info *) arg;

	अगर (brcms_deviceहटाओd(wlc)) अणु
		brcms_err(wlc->hw->d11core, "wl%d: %s: dead chip\n",
			  wlc->pub->unit, __func__);
		brcms_करोwn(wlc->wl);
		वापस;
	पूर्ण

	brcms_c_radio_hwdisable_upd(wlc);
पूर्ण

/* common low-level watchकरोg code */
अटल व्योम brcms_b_watchकरोg(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;

	अगर (!wlc_hw->up)
		वापस;

	/* increment second count */
	wlc_hw->now++;

	/* Check क्रम FIFO error पूर्णांकerrupts */
	brcms_b_fअगरoerrors(wlc_hw);

	/* make sure RX dma has buffers */
	dma_rxfill(wlc->hw->di[RX_FIFO]);

	wlc_phy_watchकरोg(wlc_hw->band->pi);
पूर्ण

/* common watchकरोg code */
अटल व्योम brcms_c_watchकरोg(काष्ठा brcms_c_info *wlc)
अणु
	brcms_dbg_info(wlc->hw->d11core, "wl%d\n", wlc->pub->unit);

	अगर (!wlc->pub->up)
		वापस;

	अगर (brcms_deviceहटाओd(wlc)) अणु
		brcms_err(wlc->hw->d11core, "wl%d: %s: dead chip\n",
			  wlc->pub->unit, __func__);
		brcms_करोwn(wlc->wl);
		वापस;
	पूर्ण

	/* increment second count */
	wlc->pub->now++;

	brcms_c_radio_hwdisable_upd(wlc);
	/* अगर radio is disable, driver may be करोwn, quit here */
	अगर (wlc->pub->radio_disabled)
		वापस;

	brcms_b_watchकरोg(wlc);

	/*
	 * occasionally sample mac stat counters to
	 * detect 16-bit counter wrap
	 */
	अगर ((wlc->pub->now % SW_TIMER_MAC_STAT_UPD) == 0)
		brcms_c_statsupd(wlc);

	अगर (BRCMS_ISNPHY(wlc->band) &&
	    ((wlc->pub->now - wlc->tempsense_lastसमय) >=
	     BRCMS_TEMPSENSE_PERIOD)) अणु
		wlc->tempsense_lastसमय = wlc->pub->now;
		brcms_c_tempsense_upd(wlc);
	पूर्ण
पूर्ण

अटल व्योम brcms_c_watchकरोg_by_समयr(व्योम *arg)
अणु
	काष्ठा brcms_c_info *wlc = (काष्ठा brcms_c_info *) arg;

	brcms_c_watchकरोg(wlc);
पूर्ण

अटल bool brcms_c_समयrs_init(काष्ठा brcms_c_info *wlc, पूर्णांक unit)
अणु
	wlc->wdसमयr = brcms_init_समयr(wlc->wl, brcms_c_watchकरोg_by_समयr,
		wlc, "watchdog");
	अगर (!wlc->wdसमयr) अणु
		wiphy_err(wlc->wiphy, "wl%d:  wl_init_timer for wdtimer "
			  "failed\n", unit);
		जाओ fail;
	पूर्ण

	wlc->radio_समयr = brcms_init_समयr(wlc->wl, brcms_c_radio_समयr,
		wlc, "radio");
	अगर (!wlc->radio_समयr) अणु
		wiphy_err(wlc->wiphy, "wl%d:  wl_init_timer for radio_timer "
			  "failed\n", unit);
		जाओ fail;
	पूर्ण

	वापस true;

 fail:
	वापस false;
पूर्ण

/*
 * Initialize brcms_c_info शेष values ...
 * may get overrides later in this function
 */
अटल व्योम brcms_c_info_init(काष्ठा brcms_c_info *wlc, पूर्णांक unit)
अणु
	पूर्णांक i;

	/* Save our copy of the chanspec */
	wlc->chanspec = ch20mhz_chspec(1);

	/* various 802.11g modes */
	wlc->लघुslot = false;
	wlc->लघुslot_override = BRCMS_SHORTSLOT_AUTO;

	brcms_c_protection_upd(wlc, BRCMS_PROT_G_OVR, BRCMS_PROTECTION_AUTO);
	brcms_c_protection_upd(wlc, BRCMS_PROT_G_SPEC, false);

	brcms_c_protection_upd(wlc, BRCMS_PROT_N_CFG_OVR,
			       BRCMS_PROTECTION_AUTO);
	brcms_c_protection_upd(wlc, BRCMS_PROT_N_CFG, BRCMS_N_PROTECTION_OFF);
	brcms_c_protection_upd(wlc, BRCMS_PROT_N_NONGF_OVR,
			       BRCMS_PROTECTION_AUTO);
	brcms_c_protection_upd(wlc, BRCMS_PROT_N_NONGF, false);
	brcms_c_protection_upd(wlc, BRCMS_PROT_N_PAM_OVR, AUTO);

	brcms_c_protection_upd(wlc, BRCMS_PROT_OVERLAP,
			       BRCMS_PROTECTION_CTL_OVERLAP);

	/* 802.11g draft 4.0 NonERP elt advertisement */
	wlc->include_legacy_erp = true;

	wlc->stf->ant_rx_ovr = ANT_RX_DIV_DEF;
	wlc->stf->txant = ANT_TX_DEF;

	wlc->prb_resp_समयout = BRCMS_PRB_RESP_TIMEOUT;

	wlc->usr_fragthresh = DOT11_DEFAULT_FRAG_LEN;
	क्रम (i = 0; i < NFIFO; i++)
		wlc->fragthresh[i] = DOT11_DEFAULT_FRAG_LEN;
	wlc->RTSThresh = DOT11_DEFAULT_RTS_LEN;

	/* शेष rate fallback retry limits */
	wlc->SFBL = RETRY_SHORT_FB;
	wlc->LFBL = RETRY_LONG_FB;

	/* शेष mac retry limits */
	wlc->SRL = RETRY_SHORT_DEF;
	wlc->LRL = RETRY_LONG_DEF;

	/* WME QoS mode is Auto by शेष */
	wlc->pub->_ampdu = AMPDU_AGG_HOST;
पूर्ण

अटल uपूर्णांक brcms_c_attach_module(काष्ठा brcms_c_info *wlc)
अणु
	uपूर्णांक err = 0;
	uपूर्णांक unit;
	unit = wlc->pub->unit;

	wlc->asi = brcms_c_antsel_attach(wlc);
	अगर (wlc->asi == शून्य) अणु
		wiphy_err(wlc->wiphy, "wl%d: attach: antsel_attach "
			  "failed\n", unit);
		err = 44;
		जाओ fail;
	पूर्ण

	wlc->ampdu = brcms_c_ampdu_attach(wlc);
	अगर (wlc->ampdu == शून्य) अणु
		wiphy_err(wlc->wiphy, "wl%d: attach: ampdu_attach "
			  "failed\n", unit);
		err = 50;
		जाओ fail;
	पूर्ण

	अगर ((brcms_c_stf_attach(wlc) != 0)) अणु
		wiphy_err(wlc->wiphy, "wl%d: attach: stf_attach "
			  "failed\n", unit);
		err = 68;
		जाओ fail;
	पूर्ण
 fail:
	वापस err;
पूर्ण

काष्ठा brcms_pub *brcms_c_pub(काष्ठा brcms_c_info *wlc)
अणु
	वापस wlc->pub;
पूर्ण

/* low level attach
 *    run backplane attach, init nvram
 *    run phy attach
 *    initialize software state क्रम each core and band
 *    put the whole chip in reset(driver करोwn state), no घड़ी
 */
अटल पूर्णांक brcms_b_attach(काष्ठा brcms_c_info *wlc, काष्ठा bcma_device *core,
			  uपूर्णांक unit, bool piomode)
अणु
	काष्ठा brcms_hardware *wlc_hw;
	uपूर्णांक err = 0;
	uपूर्णांक j;
	bool wme = false;
	काष्ठा shared_phy_params sha_params;
	काष्ठा wiphy *wiphy = wlc->wiphy;
	काष्ठा pci_dev *pcidev = core->bus->host_pci;
	काष्ठा ssb_sprom *sprom = &core->bus->sprom;

	अगर (core->bus->hosttype == BCMA_HOSTTYPE_PCI)
		brcms_dbg_info(core, "wl%d: vendor 0x%x device 0x%x\n", unit,
			       pcidev->venकरोr,
			       pcidev->device);
	अन्यथा
		brcms_dbg_info(core, "wl%d: vendor 0x%x device 0x%x\n", unit,
			       core->bus->boardinfo.venकरोr,
			       core->bus->boardinfo.type);

	wme = true;

	wlc_hw = wlc->hw;
	wlc_hw->wlc = wlc;
	wlc_hw->unit = unit;
	wlc_hw->band = wlc_hw->bandstate[0];
	wlc_hw->_piomode = piomode;

	/* populate काष्ठा brcms_hardware with शेष values  */
	brcms_b_info_init(wlc_hw);

	/*
	 * Do the hardware portion of the attach. Also initialize software
	 * state that depends on the particular hardware we are running.
	 */
	wlc_hw->sih = ai_attach(core->bus);
	अगर (wlc_hw->sih == शून्य) अणु
		wiphy_err(wiphy, "wl%d: brcms_b_attach: si_attach failed\n",
			  unit);
		err = 11;
		जाओ fail;
	पूर्ण

	/* verअगरy again the device is supported */
	अगर (!brcms_c_chipmatch(core)) अणु
		wiphy_err(wiphy, "wl%d: brcms_b_attach: Unsupported device\n",
			 unit);
		err = 12;
		जाओ fail;
	पूर्ण

	अगर (core->bus->hosttype == BCMA_HOSTTYPE_PCI) अणु
		wlc_hw->venकरोrid = pcidev->venकरोr;
		wlc_hw->deviceid = pcidev->device;
	पूर्ण अन्यथा अणु
		wlc_hw->venकरोrid = core->bus->boardinfo.venकरोr;
		wlc_hw->deviceid = core->bus->boardinfo.type;
	पूर्ण

	wlc_hw->d11core = core;
	wlc_hw->corerev = core->id.rev;

	/* validate chip, chiprev and corerev */
	अगर (!brcms_c_isgoodchip(wlc_hw)) अणु
		err = 13;
		जाओ fail;
	पूर्ण

	/* initialize घातer control रेजिस्टरs */
	ai_clkctl_init(wlc_hw->sih);

	/* request fastघड़ी and क्रमce fastघड़ी क्रम the rest of attach
	 * bring the d11 core out of reset.
	 *   For PMU chips, the first wlc_clkctl_clk is no-op since core-clk
	 *   is still false; But it will be called again inside wlc_corereset,
	 *   after d11 is out of reset.
	 */
	brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_FAST);
	brcms_b_corereset(wlc_hw, BRCMS_USE_COREFLAGS);

	अगर (!brcms_b_validate_chip_access(wlc_hw)) अणु
		wiphy_err(wiphy, "wl%d: brcms_b_attach: validate_chip_access "
			"failed\n", unit);
		err = 14;
		जाओ fail;
	पूर्ण

	/* get the board rev, used just below */
	j = sprom->board_rev;
	/* promote srom boardrev of 0xFF to 1 */
	अगर (j == BOARDREV_PROMOTABLE)
		j = BOARDREV_PROMOTED;
	wlc_hw->boardrev = (u16) j;
	अगर (!brcms_c_validboardtype(wlc_hw)) अणु
		wiphy_err(wiphy, "wl%d: brcms_b_attach: Unsupported Broadcom "
			  "board type (0x%x)" " or revision level (0x%x)\n",
			  unit, ai_get_boardtype(wlc_hw->sih),
			  wlc_hw->boardrev);
		err = 15;
		जाओ fail;
	पूर्ण
	wlc_hw->sromrev = sprom->revision;
	wlc_hw->boardflags = sprom->boardflags_lo + (sprom->boardflags_hi << 16);
	wlc_hw->boardflags2 = sprom->boardflags2_lo + (sprom->boardflags2_hi << 16);

	अगर (wlc_hw->boardflags & BFL_NOPLLDOWN)
		brcms_b_pllreq(wlc_hw, true, BRCMS_PLLREQ_SHARED);

	/* check device id(srom, nvram etc.) to set bands */
	अगर (wlc_hw->deviceid == BCM43224_D11N_ID ||
	    wlc_hw->deviceid == BCM43224_D11N_ID_VEN1 ||
	    wlc_hw->deviceid == BCM43224_CHIP_ID)
		/* Dualband boards */
		wlc_hw->_nbands = 2;
	अन्यथा
		wlc_hw->_nbands = 1;

	अगर ((ai_get_chip_id(wlc_hw->sih) == BCMA_CHIP_ID_BCM43225))
		wlc_hw->_nbands = 1;

	/* BMAC_NOTE: हटाओ init of pub values when brcms_c_attach()
	 * unconditionally करोes the init of these values
	 */
	wlc->venकरोrid = wlc_hw->venकरोrid;
	wlc->deviceid = wlc_hw->deviceid;
	wlc->pub->sih = wlc_hw->sih;
	wlc->pub->corerev = wlc_hw->corerev;
	wlc->pub->sromrev = wlc_hw->sromrev;
	wlc->pub->boardrev = wlc_hw->boardrev;
	wlc->pub->boardflags = wlc_hw->boardflags;
	wlc->pub->boardflags2 = wlc_hw->boardflags2;
	wlc->pub->_nbands = wlc_hw->_nbands;

	wlc_hw->physhim = wlc_phy_shim_attach(wlc_hw, wlc->wl, wlc);

	अगर (wlc_hw->physhim == शून्य) अणु
		wiphy_err(wiphy, "wl%d: brcms_b_attach: wlc_phy_shim_attach "
			"failed\n", unit);
		err = 25;
		जाओ fail;
	पूर्ण

	/* pass all the parameters to wlc_phy_shared_attach in one काष्ठा */
	sha_params.sih = wlc_hw->sih;
	sha_params.physhim = wlc_hw->physhim;
	sha_params.unit = unit;
	sha_params.corerev = wlc_hw->corerev;
	sha_params.vid = wlc_hw->venकरोrid;
	sha_params.did = wlc_hw->deviceid;
	sha_params.chip = ai_get_chip_id(wlc_hw->sih);
	sha_params.chiprev = ai_get_chiprev(wlc_hw->sih);
	sha_params.chippkg = ai_get_chippkg(wlc_hw->sih);
	sha_params.sromrev = wlc_hw->sromrev;
	sha_params.boardtype = ai_get_boardtype(wlc_hw->sih);
	sha_params.boardrev = wlc_hw->boardrev;
	sha_params.boardflags = wlc_hw->boardflags;
	sha_params.boardflags2 = wlc_hw->boardflags2;

	/* alloc and save poपूर्णांकer to shared phy state area */
	wlc_hw->phy_sh = wlc_phy_shared_attach(&sha_params);
	अगर (!wlc_hw->phy_sh) अणु
		err = 16;
		जाओ fail;
	पूर्ण

	/* initialize software state क्रम each core and band */
	क्रम (j = 0; j < wlc_hw->_nbands; j++) अणु
		/*
		 * band0 is always 2.4Ghz
		 * band1, अगर present, is 5Ghz
		 */

		brcms_c_setxband(wlc_hw, j);

		wlc_hw->band->bandunit = j;
		wlc_hw->band->bandtype = j ? BRCM_BAND_5G : BRCM_BAND_2G;
		wlc->band->bandunit = j;
		wlc->band->bandtype = j ? BRCM_BAND_5G : BRCM_BAND_2G;
		wlc->core->coreidx = core->core_index;

		wlc_hw->machwcap = bcma_पढ़ो32(core, D11REGOFFS(machwcap));
		wlc_hw->machwcap_backup = wlc_hw->machwcap;

		/* init tx fअगरo size */
		WARN_ON(wlc_hw->corerev < XMTFIFOTBL_STARTREV ||
			(wlc_hw->corerev - XMTFIFOTBL_STARTREV) >
				ARRAY_SIZE(xmtfअगरo_sz));
		wlc_hw->xmtfअगरo_sz =
		    xmtfअगरo_sz[(wlc_hw->corerev - XMTFIFOTBL_STARTREV)];
		WARN_ON(!wlc_hw->xmtfअगरo_sz[0]);

		/* Get a phy क्रम this band */
		wlc_hw->band->pi =
			wlc_phy_attach(wlc_hw->phy_sh, core,
				       wlc_hw->band->bandtype,
				       wlc->wiphy);
		अगर (wlc_hw->band->pi == शून्य) अणु
			wiphy_err(wiphy, "wl%d: brcms_b_attach: wlc_phy_"
				  "attach failed\n", unit);
			err = 17;
			जाओ fail;
		पूर्ण

		wlc_phy_machwcap_set(wlc_hw->band->pi, wlc_hw->machwcap);

		wlc_phy_get_phyversion(wlc_hw->band->pi, &wlc_hw->band->phytype,
				       &wlc_hw->band->phyrev,
				       &wlc_hw->band->radioid,
				       &wlc_hw->band->radiorev);
		wlc_hw->band->abgphy_encore =
		    wlc_phy_get_encore(wlc_hw->band->pi);
		wlc->band->abgphy_encore = wlc_phy_get_encore(wlc_hw->band->pi);
		wlc_hw->band->core_flags =
		    wlc_phy_get_coreflags(wlc_hw->band->pi);

		/* verअगरy good phy_type & supported phy revision */
		अगर (BRCMS_ISNPHY(wlc_hw->band)) अणु
			अगर (NCONF_HAS(wlc_hw->band->phyrev))
				जाओ good_phy;
			अन्यथा
				जाओ bad_phy;
		पूर्ण अन्यथा अगर (BRCMS_ISLCNPHY(wlc_hw->band)) अणु
			अगर (LCNCONF_HAS(wlc_hw->band->phyrev))
				जाओ good_phy;
			अन्यथा
				जाओ bad_phy;
		पूर्ण अन्यथा अणु
 bad_phy:
			wiphy_err(wiphy, "wl%d: brcms_b_attach: unsupported "
				  "phy type/rev (%d/%d)\n", unit,
				  wlc_hw->band->phytype, wlc_hw->band->phyrev);
			err = 18;
			जाओ fail;
		पूर्ण

 good_phy:
		/*
		 * BMAC_NOTE: wlc->band->pi should not be set below and should
		 * be करोne in the high level attach. However we can not make
		 * that change until all low level access is changed to
		 * wlc_hw->band->pi. Instead करो the wlc->band->pi init below,
		 * keeping wlc_hw->band->pi as well क्रम incremental update of
		 * low level fns, and cut over low only init when all fns
		 * updated.
		 */
		wlc->band->pi = wlc_hw->band->pi;
		wlc->band->phytype = wlc_hw->band->phytype;
		wlc->band->phyrev = wlc_hw->band->phyrev;
		wlc->band->radioid = wlc_hw->band->radioid;
		wlc->band->radiorev = wlc_hw->band->radiorev;
		brcms_dbg_info(core, "wl%d: phy %u/%u radio %x/%u\n", unit,
			       wlc->band->phytype, wlc->band->phyrev,
			       wlc->band->radioid, wlc->band->radiorev);
		/* शेष contention winकरोws size limits */
		wlc_hw->band->CWmin = APHY_CWMIN;
		wlc_hw->band->CWmax = PHY_CWMAX;

		अगर (!brcms_b_attach_dmapio(wlc, j, wme)) अणु
			err = 19;
			जाओ fail;
		पूर्ण
	पूर्ण

	/* disable core to match driver "down" state */
	brcms_c_coredisable(wlc_hw);

	/* Match driver "down" state */
	bcma_host_pci_करोwn(wlc_hw->d11core->bus);

	/* turn off pll and xtal to match driver "down" state */
	brcms_b_xtal(wlc_hw, OFF);

	/* *******************************************************************
	 * The hardware is in the DOWN state at this poपूर्णांक. D11 core
	 * or cores are in reset with घड़ीs off, and the board PLLs
	 * are off अगर possible.
	 *
	 * Beyond this poपूर्णांक, wlc->sbclk == false and chip रेजिस्टरs
	 * should not be touched.
	 *********************************************************************
	 */

	/* init etheraddr state variables */
	brcms_c_get_macaddr(wlc_hw, wlc_hw->etheraddr);

	अगर (is_broadcast_ether_addr(wlc_hw->etheraddr) ||
	    is_zero_ether_addr(wlc_hw->etheraddr)) अणु
		wiphy_err(wiphy, "wl%d: brcms_b_attach: bad macaddr\n",
			  unit);
		err = 22;
		जाओ fail;
	पूर्ण

	brcms_dbg_info(wlc_hw->d11core, "deviceid 0x%x nbands %d board 0x%x\n",
		       wlc_hw->deviceid, wlc_hw->_nbands,
		       ai_get_boardtype(wlc_hw->sih));

	वापस err;

 fail:
	wiphy_err(wiphy, "wl%d: brcms_b_attach: failed with err %d\n", unit,
		  err);
	वापस err;
पूर्ण

अटल bool brcms_c_attach_stf_ant_init(काष्ठा brcms_c_info *wlc)
अणु
	पूर्णांक aa;
	uपूर्णांक unit;
	पूर्णांक bandtype;
	काष्ठा ssb_sprom *sprom = &wlc->hw->d11core->bus->sprom;

	unit = wlc->pub->unit;
	bandtype = wlc->band->bandtype;

	/* get antennas available */
	अगर (bandtype == BRCM_BAND_5G)
		aa = sprom->ant_available_a;
	अन्यथा
		aa = sprom->ant_available_bg;

	अगर ((aa < 1) || (aa > 15)) अणु
		wiphy_err(wlc->wiphy, "wl%d: %s: Invalid antennas available in"
			  " srom (0x%x), using 3\n", unit, __func__, aa);
		aa = 3;
	पूर्ण

	/* reset the शेषs अगर we have a single antenna */
	अगर (aa == 1) अणु
		wlc->stf->ant_rx_ovr = ANT_RX_DIV_FORCE_0;
		wlc->stf->txant = ANT_TX_FORCE_0;
	पूर्ण अन्यथा अगर (aa == 2) अणु
		wlc->stf->ant_rx_ovr = ANT_RX_DIV_FORCE_1;
		wlc->stf->txant = ANT_TX_FORCE_1;
	पूर्ण अन्यथा अणु
	पूर्ण

	/* Compute Antenna Gain */
	अगर (bandtype == BRCM_BAND_5G)
		wlc->band->antgain = sprom->antenna_gain.a1;
	अन्यथा
		wlc->band->antgain = sprom->antenna_gain.a0;

	वापस true;
पूर्ण

अटल व्योम brcms_c_bss_शेष_init(काष्ठा brcms_c_info *wlc)
अणु
	u16 chanspec;
	काष्ठा brcms_band *band;
	काष्ठा brcms_bss_info *bi = wlc->शेष_bss;

	/* init शेष and target BSS with some sane initial values */
	स_रखो(bi, 0, माप(*bi));
	bi->beacon_period = BEACON_INTERVAL_DEFAULT;

	/* fill the शेष channel as the first valid channel
	 * starting from the 2G channels
	 */
	chanspec = ch20mhz_chspec(1);
	wlc->home_chanspec = bi->chanspec = chanspec;

	/* find the band of our शेष channel */
	band = wlc->band;
	अगर (wlc->pub->_nbands > 1 &&
	    band->bandunit != chspec_bandunit(chanspec))
		band = wlc->bandstate[OTHERBANDUNIT(wlc)];

	/* init bss rates to the band specअगरic शेष rate set */
	brcms_c_rateset_शेष(&bi->rateset, शून्य, band->phytype,
		band->bandtype, false, BRCMS_RATE_MASK_FULL,
		(bool) (wlc->pub->_n_enab & SUPPORT_11N),
		brcms_chspec_bw(chanspec), wlc->stf->txstreams);

	अगर (wlc->pub->_n_enab & SUPPORT_11N)
		bi->flags |= BRCMS_BSS_HT;
पूर्ण

अटल व्योम brcms_c_update_mimo_band_bwcap(काष्ठा brcms_c_info *wlc, u8 bwcap)
अणु
	uपूर्णांक i;
	काष्ठा brcms_band *band;

	क्रम (i = 0; i < wlc->pub->_nbands; i++) अणु
		band = wlc->bandstate[i];
		अगर (band->bandtype == BRCM_BAND_5G) अणु
			अगर ((bwcap == BRCMS_N_BW_40ALL)
			    || (bwcap == BRCMS_N_BW_20IN2G_40IN5G))
				band->mimo_cap_40 = true;
			अन्यथा
				band->mimo_cap_40 = false;
		पूर्ण अन्यथा अणु
			अगर (bwcap == BRCMS_N_BW_40ALL)
				band->mimo_cap_40 = true;
			अन्यथा
				band->mimo_cap_40 = false;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम brcms_c_समयrs_deinit(काष्ठा brcms_c_info *wlc)
अणु
	/* मुक्त समयr state */
	अगर (wlc->wdसमयr) अणु
		brcms_मुक्त_समयr(wlc->wdसमयr);
		wlc->wdसमयr = शून्य;
	पूर्ण
	अगर (wlc->radio_समयr) अणु
		brcms_मुक्त_समयr(wlc->radio_समयr);
		wlc->radio_समयr = शून्य;
	पूर्ण
पूर्ण

अटल व्योम brcms_c_detach_module(काष्ठा brcms_c_info *wlc)
अणु
	अगर (wlc->asi) अणु
		brcms_c_antsel_detach(wlc->asi);
		wlc->asi = शून्य;
	पूर्ण

	अगर (wlc->ampdu) अणु
		brcms_c_ampdu_detach(wlc->ampdu);
		wlc->ampdu = शून्य;
	पूर्ण

	brcms_c_stf_detach(wlc);
पूर्ण

/*
 * low level detach
 */
अटल व्योम brcms_b_detach(काष्ठा brcms_c_info *wlc)
अणु
	uपूर्णांक i;
	काष्ठा brcms_hw_band *band;
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;

	brcms_b_detach_dmapio(wlc_hw);

	band = wlc_hw->band;
	क्रम (i = 0; i < wlc_hw->_nbands; i++) अणु
		अगर (band->pi) अणु
			/* Detach this band's phy */
			wlc_phy_detach(band->pi);
			band->pi = शून्य;
		पूर्ण
		band = wlc_hw->bandstate[OTHERBANDUNIT(wlc)];
	पूर्ण

	/* Free shared phy state */
	kमुक्त(wlc_hw->phy_sh);

	wlc_phy_shim_detach(wlc_hw->physhim);

	अगर (wlc_hw->sih) अणु
		ai_detach(wlc_hw->sih);
		wlc_hw->sih = शून्य;
	पूर्ण
पूर्ण

/*
 * Return a count of the number of driver callbacks still pending.
 *
 * General policy is that brcms_c_detach can only dealloc/मुक्त software states.
 * It can NOT touch hardware रेजिस्टरs since the d11core may be in reset and
 * घड़ी may not be available.
 * One exception is sb रेजिस्टर access, which is possible अगर crystal is turned
 * on after "down" state, driver should aव्योम software समयr with the exception
 * of radio_monitor.
 */
uपूर्णांक brcms_c_detach(काष्ठा brcms_c_info *wlc)
अणु
	uपूर्णांक callbacks;

	अगर (wlc == शून्य)
		वापस 0;

	brcms_b_detach(wlc);

	/* delete software समयrs */
	callbacks = 0;
	अगर (!brcms_c_radio_monitor_stop(wlc))
		callbacks++;

	brcms_c_channel_mgr_detach(wlc->cmi);

	brcms_c_समयrs_deinit(wlc);

	brcms_c_detach_module(wlc);

	brcms_c_detach_mमुक्त(wlc);
	वापस callbacks;
पूर्ण

/* update state that depends on the current value of "ap" */
अटल व्योम brcms_c_ap_upd(काष्ठा brcms_c_info *wlc)
अणु
	/* STA-BSS; लघु capable */
	wlc->PLCPHdr_override = BRCMS_PLCP_SHORT;
पूर्ण

/* Initialize just the hardware when coming out of POR or S3/S5 प्रणाली states */
अटल व्योम brcms_b_hw_up(काष्ठा brcms_hardware *wlc_hw)
अणु
	अगर (wlc_hw->wlc->pub->hw_up)
		वापस;

	brcms_dbg_info(wlc_hw->d11core, "wl%d\n", wlc_hw->unit);

	/*
	 * Enable pll and xtal, initialize the घातer control रेजिस्टरs,
	 * and क्रमce fastघड़ी क्रम the reमुख्यder of brcms_c_up().
	 */
	brcms_b_xtal(wlc_hw, ON);
	ai_clkctl_init(wlc_hw->sih);
	brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_FAST);

	/*
	 * TODO: test suspend/resume
	 *
	 * AI chip करोesn't restore bar0win2 on
	 * hibernation/resume, need sw fixup
	 */

	/*
	 * Inक्रमm phy that a POR reset has occurred so
	 * it करोes a complete phy init
	 */
	wlc_phy_por_inक्रमm(wlc_hw->band->pi);

	wlc_hw->ucode_loaded = false;
	wlc_hw->wlc->pub->hw_up = true;

	अगर ((wlc_hw->boardflags & BFL_FEM)
	    && (ai_get_chip_id(wlc_hw->sih) == BCMA_CHIP_ID_BCM4313)) अणु
		अगर (!
		    (wlc_hw->boardrev >= 0x1250
		     && (wlc_hw->boardflags & BFL_FEM_BT)))
			ai_epa_4313war(wlc_hw->sih);
	पूर्ण
पूर्ण

अटल पूर्णांक brcms_b_up_prep(काष्ठा brcms_hardware *wlc_hw)
अणु
	brcms_dbg_info(wlc_hw->d11core, "wl%d\n", wlc_hw->unit);

	/*
	 * Enable pll and xtal, initialize the घातer control रेजिस्टरs,
	 * and क्रमce fastघड़ी क्रम the reमुख्यder of brcms_c_up().
	 */
	brcms_b_xtal(wlc_hw, ON);
	ai_clkctl_init(wlc_hw->sih);
	brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_FAST);

	/*
	 * Configure pci/pcmcia here instead of in brcms_c_attach()
	 * to allow mfg hotswap:  करोwn, hotswap (chip घातer cycle), up.
	 */
	bcma_host_pci_irq_ctl(wlc_hw->d11core->bus, wlc_hw->d11core,
			      true);

	/*
	 * Need to पढ़ो the hwradio status here to cover the हाल where the
	 * प्रणाली is loaded with the hw radio disabled. We करो not want to
	 * bring the driver up in this हाल.
	 */
	अगर (brcms_b_radio_पढ़ो_hwdisabled(wlc_hw)) अणु
		/* put SB PCI in करोwn state again */
		bcma_host_pci_करोwn(wlc_hw->d11core->bus);
		brcms_b_xtal(wlc_hw, OFF);
		वापस -ENOMEDIUM;
	पूर्ण

	bcma_host_pci_up(wlc_hw->d11core->bus);

	/* reset the d11 core */
	brcms_b_corereset(wlc_hw, BRCMS_USE_COREFLAGS);

	वापस 0;
पूर्ण

अटल पूर्णांक brcms_b_up_finish(काष्ठा brcms_hardware *wlc_hw)
अणु
	wlc_hw->up = true;
	wlc_phy_hw_state_upd(wlc_hw->band->pi, true);

	/* FULLY enable dynamic घातer control and d11 core पूर्णांकerrupt */
	brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_DYNAMIC);
	brcms_पूर्णांकrson(wlc_hw->wlc->wl);
	वापस 0;
पूर्ण

/*
 * Write WME tunable parameters क्रम retransmit/max rate
 * from wlc काष्ठा to ucode
 */
अटल व्योम brcms_c_wme_retries_ग_लिखो(काष्ठा brcms_c_info *wlc)
अणु
	पूर्णांक ac;

	/* Need घड़ी to करो this */
	अगर (!wlc->clk)
		वापस;

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		brcms_b_ग_लिखो_shm(wlc->hw, M_AC_TXLMT_ADDR(ac),
				  wlc->wme_retries[ac]);
पूर्ण

/* make पूर्णांकerface operational */
पूर्णांक brcms_c_up(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा ieee80211_channel *ch;

	brcms_dbg_info(wlc->hw->d11core, "wl%d\n", wlc->pub->unit);

	/* HW is turned off so करोn't try to access it */
	अगर (wlc->pub->hw_off || brcms_deviceहटाओd(wlc))
		वापस -ENOMEDIUM;

	अगर (!wlc->pub->hw_up) अणु
		brcms_b_hw_up(wlc->hw);
		wlc->pub->hw_up = true;
	पूर्ण

	अगर ((wlc->pub->boardflags & BFL_FEM)
	    && (ai_get_chip_id(wlc->hw->sih) == BCMA_CHIP_ID_BCM4313)) अणु
		अगर (wlc->pub->boardrev >= 0x1250
		    && (wlc->pub->boardflags & BFL_FEM_BT))
			brcms_b_mhf(wlc->hw, MHF5, MHF5_4313_GPIOCTRL,
				MHF5_4313_GPIOCTRL, BRCM_BAND_ALL);
		अन्यथा
			brcms_b_mhf(wlc->hw, MHF4, MHF4_EXTPA_ENABLE,
				    MHF4_EXTPA_ENABLE, BRCM_BAND_ALL);
	पूर्ण

	/*
	 * Need to पढ़ो the hwradio status here to cover the हाल where the
	 * प्रणाली is loaded with the hw radio disabled. We करो not want to bring
	 * the driver up in this हाल. If radio is disabled, पात up, lower
	 * घातer, start radio समयr and वापस 0(क्रम NDIS) करोn't call
	 * radio_update to aव्योम looping brcms_c_up.
	 *
	 * brcms_b_up_prep() वापसs either 0 or -BCME_RADIOOFF only
	 */
	अगर (!wlc->pub->radio_disabled) अणु
		पूर्णांक status = brcms_b_up_prep(wlc->hw);
		अगर (status == -ENOMEDIUM) अणु
			अगर (!mboolisset
			    (wlc->pub->radio_disabled, WL_RADIO_HW_DISABLE)) अणु
				काष्ठा brcms_bss_cfg *bsscfg = wlc->bsscfg;
				mboolset(wlc->pub->radio_disabled,
					 WL_RADIO_HW_DISABLE);
				अगर (bsscfg->type == BRCMS_TYPE_STATION ||
				    bsscfg->type == BRCMS_TYPE_ADHOC)
					brcms_err(wlc->hw->d11core,
						  "wl%d: up: rfdisable -> "
						  "bsscfg_disable()\n",
						   wlc->pub->unit);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (wlc->pub->radio_disabled) अणु
		brcms_c_radio_monitor_start(wlc);
		वापस 0;
	पूर्ण

	/* brcms_b_up_prep has करोne brcms_c_corereset(). so clk is on, set it */
	wlc->clk = true;

	brcms_c_radio_monitor_stop(wlc);

	/* Set EDCF hostflags */
	brcms_b_mhf(wlc->hw, MHF1, MHF1_EDCF, MHF1_EDCF, BRCM_BAND_ALL);

	brcms_init(wlc->wl);
	wlc->pub->up = true;

	अगर (wlc->bandinit_pending) अणु
		ch = wlc->pub->ieee_hw->conf.chandef.chan;
		brcms_c_suspend_mac_and_रुको(wlc);
		brcms_c_set_chanspec(wlc, ch20mhz_chspec(ch->hw_value));
		wlc->bandinit_pending = false;
		brcms_c_enable_mac(wlc);
	पूर्ण

	brcms_b_up_finish(wlc->hw);

	/* Program the TX wme params with the current settings */
	brcms_c_wme_retries_ग_लिखो(wlc);

	/* start one second watchकरोg समयr */
	brcms_add_समयr(wlc->wdसमयr, TIMER_INTERVAL_WATCHDOG, true);
	wlc->WDarmed = true;

	/* ensure antenna config is up to date */
	brcms_c_stf_phy_txant_upd(wlc);
	/* ensure LDPC config is in sync */
	brcms_c_ht_update_ldpc(wlc, wlc->stf->ldpc);

	वापस 0;
पूर्ण

अटल पूर्णांक brcms_b_bmac_करोwn_prep(काष्ठा brcms_hardware *wlc_hw)
अणु
	bool dev_gone;
	uपूर्णांक callbacks = 0;

	अगर (!wlc_hw->up)
		वापस callbacks;

	dev_gone = brcms_deviceहटाओd(wlc_hw->wlc);

	/* disable पूर्णांकerrupts */
	अगर (dev_gone)
		wlc_hw->wlc->macपूर्णांकmask = 0;
	अन्यथा अणु
		/* now disable पूर्णांकerrupts */
		brcms_पूर्णांकrsoff(wlc_hw->wlc->wl);

		/* ensure we're running on the pll घड़ी again */
		brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_FAST);
	पूर्ण
	/* करोwn phy at the last of this stage */
	callbacks += wlc_phy_करोwn(wlc_hw->band->pi);

	वापस callbacks;
पूर्ण

अटल पूर्णांक brcms_b_करोwn_finish(काष्ठा brcms_hardware *wlc_hw)
अणु
	uपूर्णांक callbacks = 0;
	bool dev_gone;

	अगर (!wlc_hw->up)
		वापस callbacks;

	wlc_hw->up = false;
	wlc_phy_hw_state_upd(wlc_hw->band->pi, false);

	dev_gone = brcms_deviceहटाओd(wlc_hw->wlc);

	अगर (dev_gone) अणु
		wlc_hw->sbclk = false;
		wlc_hw->clk = false;
		wlc_phy_hw_clk_state_upd(wlc_hw->band->pi, false);

		/* reclaim any posted packets */
		brcms_c_flushqueues(wlc_hw->wlc);
	पूर्ण अन्यथा अणु

		/* Reset and disable the core */
		अगर (bcma_core_is_enabled(wlc_hw->d11core)) अणु
			अगर (bcma_पढ़ो32(wlc_hw->d11core,
					D11REGOFFS(maccontrol)) & MCTL_EN_MAC)
				brcms_c_suspend_mac_and_रुको(wlc_hw->wlc);
			callbacks += brcms_reset(wlc_hw->wlc->wl);
			brcms_c_coredisable(wlc_hw);
		पूर्ण

		/* turn off primary xtal and pll */
		अगर (!wlc_hw->noreset) अणु
			bcma_host_pci_करोwn(wlc_hw->d11core->bus);
			brcms_b_xtal(wlc_hw, OFF);
		पूर्ण
	पूर्ण

	वापस callbacks;
पूर्ण

/*
 * Mark the पूर्णांकerface nonoperational, stop the software mechanisms,
 * disable the hardware, मुक्त any transient buffer state.
 * Return a count of the number of driver callbacks still pending.
 */
uपूर्णांक brcms_c_करोwn(काष्ठा brcms_c_info *wlc)
अणु

	uपूर्णांक callbacks = 0;
	पूर्णांक i;

	brcms_dbg_info(wlc->hw->d11core, "wl%d\n", wlc->pub->unit);

	/* check अगर we are alपढ़ोy in the going करोwn path */
	अगर (wlc->going_करोwn) अणु
		brcms_err(wlc->hw->d11core,
			  "wl%d: %s: Driver going down so return\n",
			  wlc->pub->unit, __func__);
		वापस 0;
	पूर्ण
	अगर (!wlc->pub->up)
		वापस callbacks;

	wlc->going_करोwn = true;

	callbacks += brcms_b_bmac_करोwn_prep(wlc->hw);

	brcms_deviceहटाओd(wlc);

	/* Call any रेजिस्टरed करोwn handlers */
	क्रम (i = 0; i < BRCMS_MAXMODULES; i++) अणु
		अगर (wlc->modulecb[i].करोwn_fn)
			callbacks +=
			    wlc->modulecb[i].करोwn_fn(wlc->modulecb[i].hdl);
	पूर्ण

	/* cancel the watchकरोg समयr */
	अगर (wlc->WDarmed) अणु
		अगर (!brcms_del_समयr(wlc->wdसमयr))
			callbacks++;
		wlc->WDarmed = false;
	पूर्ण

	wlc->pub->up = false;

	wlc_phy_mute_upd(wlc->band->pi, false, PHY_MUTE_ALL);

	callbacks += brcms_b_करोwn_finish(wlc->hw);

	/* brcms_b_करोwn_finish has करोne brcms_c_coredisable(). so clk is off */
	wlc->clk = false;

	wlc->going_करोwn = false;
	वापस callbacks;
पूर्ण

/* Set the current gmode configuration */
पूर्णांक brcms_c_set_gmode(काष्ठा brcms_c_info *wlc, u8 gmode, bool config)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक i;
	काष्ठा brcms_c_rateset rs;
	/* Default to 54g Auto */
	/* Advertise and use लघुslot (-1/0/1 Auto/Off/On) */
	s8 लघुslot = BRCMS_SHORTSLOT_AUTO;
	bool ofdm_basic = false;	/* Make 6, 12, and 24 basic rates */
	काष्ठा brcms_band *band;

	/* अगर N-support is enabled, allow Gmode set as दीर्घ as requested
	 * Gmode is not GMODE_LEGACY_B
	 */
	अगर ((wlc->pub->_n_enab & SUPPORT_11N) && gmode == GMODE_LEGACY_B)
		वापस -ENOTSUPP;

	/* verअगरy that we are dealing with 2G band and grab the band poपूर्णांकer */
	अगर (wlc->band->bandtype == BRCM_BAND_2G)
		band = wlc->band;
	अन्यथा अगर ((wlc->pub->_nbands > 1) &&
		 (wlc->bandstate[OTHERBANDUNIT(wlc)]->bandtype == BRCM_BAND_2G))
		band = wlc->bandstate[OTHERBANDUNIT(wlc)];
	अन्यथा
		वापस -EINVAL;

	/* update configuration value */
	अगर (config)
		brcms_c_protection_upd(wlc, BRCMS_PROT_G_USER, gmode);

	/* Clear rateset override */
	स_रखो(&rs, 0, माप(rs));

	चयन (gmode) अणु
	हाल GMODE_LEGACY_B:
		लघुslot = BRCMS_SHORTSLOT_OFF;
		brcms_c_rateset_copy(&gphy_legacy_rates, &rs);

		अवरोध;

	हाल GMODE_LRS:
		अवरोध;

	हाल GMODE_AUTO:
		/* Accept शेषs */
		अवरोध;

	हाल GMODE_ONLY:
		ofdm_basic = true;
		अवरोध;

	हाल GMODE_PERFORMANCE:
		लघुslot = BRCMS_SHORTSLOT_ON;
		ofdm_basic = true;
		अवरोध;

	शेष:
		/* Error */
		brcms_err(wlc->hw->d11core, "wl%d: %s: invalid gmode %d\n",
			  wlc->pub->unit, __func__, gmode);
		वापस -ENOTSUPP;
	पूर्ण

	band->gmode = gmode;

	wlc->लघुslot_override = लघुslot;

	/* Use the शेष 11g rateset */
	अगर (!rs.count)
		brcms_c_rateset_copy(&cck_ofdm_rates, &rs);

	अगर (ofdm_basic) अणु
		क्रम (i = 0; i < rs.count; i++) अणु
			अगर (rs.rates[i] == BRCM_RATE_6M
			    || rs.rates[i] == BRCM_RATE_12M
			    || rs.rates[i] == BRCM_RATE_24M)
				rs.rates[i] |= BRCMS_RATE_FLAG;
		पूर्ण
	पूर्ण

	/* Set शेष bss rateset */
	wlc->शेष_bss->rateset.count = rs.count;
	स_नकल(wlc->शेष_bss->rateset.rates, rs.rates,
	       माप(wlc->शेष_bss->rateset.rates));

	वापस ret;
पूर्ण

पूर्णांक brcms_c_set_nmode(काष्ठा brcms_c_info *wlc)
अणु
	uपूर्णांक i;
	s32 nmode = AUTO;

	अगर (wlc->stf->txstreams == WL_11N_3x3)
		nmode = WL_11N_3x3;
	अन्यथा
		nmode = WL_11N_2x2;

	/* क्रमce GMODE_AUTO अगर NMODE is ON */
	brcms_c_set_gmode(wlc, GMODE_AUTO, true);
	अगर (nmode == WL_11N_3x3)
		wlc->pub->_n_enab = SUPPORT_HT;
	अन्यथा
		wlc->pub->_n_enab = SUPPORT_11N;
	wlc->शेष_bss->flags |= BRCMS_BSS_HT;
	/* add the mcs rates to the शेष and hw ratesets */
	brcms_c_rateset_mcs_build(&wlc->शेष_bss->rateset,
			      wlc->stf->txstreams);
	क्रम (i = 0; i < wlc->pub->_nbands; i++)
		स_नकल(wlc->bandstate[i]->hw_rateset.mcs,
		       wlc->शेष_bss->rateset.mcs, MCSSET_LEN);

	वापस 0;
पूर्ण

अटल पूर्णांक
brcms_c_set_पूर्णांकernal_rateset(काष्ठा brcms_c_info *wlc,
			     काष्ठा brcms_c_rateset *rs_arg)
अणु
	काष्ठा brcms_c_rateset rs, new;
	uपूर्णांक bandunit;

	स_नकल(&rs, rs_arg, माप(काष्ठा brcms_c_rateset));

	/* check क्रम bad count value */
	अगर ((rs.count == 0) || (rs.count > BRCMS_NUMRATES))
		वापस -EINVAL;

	/* try the current band */
	bandunit = wlc->band->bandunit;
	स_नकल(&new, &rs, माप(काष्ठा brcms_c_rateset));
	अगर (brcms_c_rate_hwrs_filter_sort_validate
	    (&new, &wlc->bandstate[bandunit]->hw_rateset, true,
	     wlc->stf->txstreams))
		जाओ good;

	/* try the other band */
	अगर (brcms_is_mband_unlocked(wlc)) अणु
		bandunit = OTHERBANDUNIT(wlc);
		स_नकल(&new, &rs, माप(काष्ठा brcms_c_rateset));
		अगर (brcms_c_rate_hwrs_filter_sort_validate(&new,
						       &wlc->
						       bandstate[bandunit]->
						       hw_rateset, true,
						       wlc->stf->txstreams))
			जाओ good;
	पूर्ण

	वापस -EBADE;

 good:
	/* apply new rateset */
	स_नकल(&wlc->शेष_bss->rateset, &new,
	       माप(काष्ठा brcms_c_rateset));
	स_नकल(&wlc->bandstate[bandunit]->defrateset, &new,
	       माप(काष्ठा brcms_c_rateset));
	वापस 0;
पूर्ण

अटल व्योम brcms_c_ofdm_rateset_war(काष्ठा brcms_c_info *wlc)
अणु
	wlc_phy_ofdm_rateset_war(wlc->band->pi, false);
पूर्ण

पूर्णांक brcms_c_set_channel(काष्ठा brcms_c_info *wlc, u16 channel)
अणु
	u16 chspec = ch20mhz_chspec(channel);

	अगर (channel > MAXCHANNEL)
		वापस -EINVAL;

	अगर (!brcms_c_valid_chanspec_db(wlc->cmi, chspec))
		वापस -EINVAL;


	अगर (!wlc->pub->up && brcms_is_mband_unlocked(wlc)) अणु
		अगर (wlc->band->bandunit != chspec_bandunit(chspec))
			wlc->bandinit_pending = true;
		अन्यथा
			wlc->bandinit_pending = false;
	पूर्ण

	wlc->शेष_bss->chanspec = chspec;
	/* brcms_c_BSSinit() will sanitize the rateset beक्रमe
	 * using it.. */
	अगर (wlc->pub->up && (wlc_phy_chanspec_get(wlc->band->pi) != chspec)) अणु
		brcms_c_set_home_chanspec(wlc, chspec);
		brcms_c_suspend_mac_and_रुको(wlc);
		brcms_c_set_chanspec(wlc, chspec);
		brcms_c_enable_mac(wlc);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक brcms_c_set_rate_limit(काष्ठा brcms_c_info *wlc, u16 srl, u16 lrl)
अणु
	पूर्णांक ac;

	अगर (srl < 1 || srl > RETRY_SHORT_MAX ||
	    lrl < 1 || lrl > RETRY_SHORT_MAX)
		वापस -EINVAL;

	wlc->SRL = srl;
	wlc->LRL = lrl;

	brcms_b_retrylimit_upd(wlc->hw, wlc->SRL, wlc->LRL);

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		wlc->wme_retries[ac] =	SFIELD(wlc->wme_retries[ac],
					       EDCF_SHORT,  wlc->SRL);
		wlc->wme_retries[ac] =	SFIELD(wlc->wme_retries[ac],
					       EDCF_LONG, wlc->LRL);
	पूर्ण
	brcms_c_wme_retries_ग_लिखो(wlc);

	वापस 0;
पूर्ण

व्योम brcms_c_get_current_rateset(काष्ठा brcms_c_info *wlc,
				 काष्ठा brcm_rateset *currs)
अणु
	काष्ठा brcms_c_rateset *rs;

	अगर (wlc->pub->associated)
		rs = &wlc->bsscfg->current_bss->rateset;
	अन्यथा
		rs = &wlc->शेष_bss->rateset;

	/* Copy only legacy rateset section */
	currs->count = rs->count;
	स_नकल(&currs->rates, &rs->rates, rs->count);
पूर्ण

पूर्णांक brcms_c_set_rateset(काष्ठा brcms_c_info *wlc, काष्ठा brcm_rateset *rs)
अणु
	काष्ठा brcms_c_rateset पूर्णांकernal_rs;
	पूर्णांक bcmerror;

	अगर (rs->count > BRCMS_NUMRATES)
		वापस -ENOBUFS;

	स_रखो(&पूर्णांकernal_rs, 0, माप(पूर्णांकernal_rs));

	/* Copy only legacy rateset section */
	पूर्णांकernal_rs.count = rs->count;
	स_नकल(&पूर्णांकernal_rs.rates, &rs->rates, पूर्णांकernal_rs.count);

	/* merge rateset coming in with the current mcsset */
	अगर (wlc->pub->_n_enab & SUPPORT_11N) अणु
		काष्ठा brcms_bss_info *mcsset_bss;
		अगर (wlc->pub->associated)
			mcsset_bss = wlc->bsscfg->current_bss;
		अन्यथा
			mcsset_bss = wlc->शेष_bss;
		स_नकल(पूर्णांकernal_rs.mcs, &mcsset_bss->rateset.mcs[0],
		       MCSSET_LEN);
	पूर्ण

	bcmerror = brcms_c_set_पूर्णांकernal_rateset(wlc, &पूर्णांकernal_rs);
	अगर (!bcmerror)
		brcms_c_ofdm_rateset_war(wlc);

	वापस bcmerror;
पूर्ण

अटल व्योम brcms_c_समय_lock(काष्ठा brcms_c_info *wlc)
अणु
	bcma_set32(wlc->hw->d11core, D11REGOFFS(maccontrol), MCTL_TBTTHOLD);
	/* Commit the ग_लिखो */
	bcma_पढ़ो32(wlc->hw->d11core, D11REGOFFS(maccontrol));
पूर्ण

अटल व्योम brcms_c_समय_unlock(काष्ठा brcms_c_info *wlc)
अणु
	bcma_mask32(wlc->hw->d11core, D11REGOFFS(maccontrol), ~MCTL_TBTTHOLD);
	/* Commit the ग_लिखो */
	bcma_पढ़ो32(wlc->hw->d11core, D11REGOFFS(maccontrol));
पूर्ण

पूर्णांक brcms_c_set_beacon_period(काष्ठा brcms_c_info *wlc, u16 period)
अणु
	u32 bcnपूर्णांक_us;

	अगर (period == 0)
		वापस -EINVAL;

	wlc->शेष_bss->beacon_period = period;

	bcnपूर्णांक_us = period << 10;
	brcms_c_समय_lock(wlc);
	bcma_ग_लिखो32(wlc->hw->d11core, D11REGOFFS(tsf_cfprep),
		     (bcnपूर्णांक_us << CFPREP_CBI_SHIFT));
	bcma_ग_लिखो32(wlc->hw->d11core, D11REGOFFS(tsf_cfpstart), bcnपूर्णांक_us);
	brcms_c_समय_unlock(wlc);

	वापस 0;
पूर्ण

u16 brcms_c_get_phy_type(काष्ठा brcms_c_info *wlc, पूर्णांक phyidx)
अणु
	वापस wlc->band->phytype;
पूर्ण

व्योम brcms_c_set_लघुslot_override(काष्ठा brcms_c_info *wlc, s8 sslot_override)
अणु
	wlc->लघुslot_override = sslot_override;

	/*
	 * लघुslot is an 11g feature, so no more work अगर we are
	 * currently on the 5G band
	 */
	अगर (wlc->band->bandtype == BRCM_BAND_5G)
		वापस;

	अगर (wlc->pub->up && wlc->pub->associated) अणु
		/* let watchकरोg or beacon processing update लघुslot */
	पूर्ण अन्यथा अगर (wlc->pub->up) अणु
		/* unassociated लघुslot is off */
		brcms_c_चयन_लघुslot(wlc, false);
	पूर्ण अन्यथा अणु
		/* driver is करोwn, so just update the brcms_c_info
		 * value */
		अगर (wlc->लघुslot_override == BRCMS_SHORTSLOT_AUTO)
			wlc->लघुslot = false;
		अन्यथा
			wlc->लघुslot =
			    (wlc->लघुslot_override ==
			     BRCMS_SHORTSLOT_ON);
	पूर्ण
पूर्ण

/*
 * रेजिस्टर watchकरोg and करोwn handlers.
 */
पूर्णांक brcms_c_module_रेजिस्टर(काष्ठा brcms_pub *pub,
			    स्थिर अक्षर *name, काष्ठा brcms_info *hdl,
			    पूर्णांक (*d_fn)(व्योम *handle))
अणु
	काष्ठा brcms_c_info *wlc = (काष्ठा brcms_c_info *) pub->wlc;
	पूर्णांक i;

	/* find an empty entry and just add, no duplication check! */
	क्रम (i = 0; i < BRCMS_MAXMODULES; i++) अणु
		अगर (wlc->modulecb[i].name[0] == '\0') अणु
			म_नकलन(wlc->modulecb[i].name, name,
				माप(wlc->modulecb[i].name) - 1);
			wlc->modulecb[i].hdl = hdl;
			wlc->modulecb[i].करोwn_fn = d_fn;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOSR;
पूर्ण

/* unरेजिस्टर module callbacks */
पूर्णांक brcms_c_module_unरेजिस्टर(काष्ठा brcms_pub *pub, स्थिर अक्षर *name,
			      काष्ठा brcms_info *hdl)
अणु
	काष्ठा brcms_c_info *wlc = (काष्ठा brcms_c_info *) pub->wlc;
	पूर्णांक i;

	अगर (wlc == शून्य)
		वापस -ENODATA;

	क्रम (i = 0; i < BRCMS_MAXMODULES; i++) अणु
		अगर (!म_भेद(wlc->modulecb[i].name, name) &&
		    (wlc->modulecb[i].hdl == hdl)) अणु
			स_रखो(&wlc->modulecb[i], 0, माप(wlc->modulecb[i]));
			वापस 0;
		पूर्ण
	पूर्ण

	/* table not found! */
	वापस -ENODATA;
पूर्ण

अटल bool brcms_c_chipmatch_pci(काष्ठा bcma_device *core)
अणु
	काष्ठा pci_dev *pcidev = core->bus->host_pci;
	u16 venकरोr = pcidev->venकरोr;
	u16 device = pcidev->device;

	अगर (venकरोr != PCI_VENDOR_ID_BROADCOM) अणु
		pr_err("unknown vendor id %04x\n", venकरोr);
		वापस false;
	पूर्ण

	अगर (device == BCM43224_D11N_ID_VEN1 || device == BCM43224_CHIP_ID)
		वापस true;
	अगर ((device == BCM43224_D11N_ID) || (device == BCM43225_D11N2G_ID))
		वापस true;
	अगर (device == BCM4313_D11N2G_ID || device == BCM4313_CHIP_ID)
		वापस true;
	अगर ((device == BCM43236_D11N_ID) || (device == BCM43236_D11N2G_ID))
		वापस true;

	pr_err("unknown device id %04x\n", device);
	वापस false;
पूर्ण

अटल bool brcms_c_chipmatch_soc(काष्ठा bcma_device *core)
अणु
	काष्ठा bcma_chipinfo *chipinfo = &core->bus->chipinfo;

	अगर (chipinfo->id == BCMA_CHIP_ID_BCM4716)
		वापस true;

	pr_err("unknown chip id %04x\n", chipinfo->id);
	वापस false;
पूर्ण

bool brcms_c_chipmatch(काष्ठा bcma_device *core)
अणु
	चयन (core->bus->hosttype) अणु
	हाल BCMA_HOSTTYPE_PCI:
		वापस brcms_c_chipmatch_pci(core);
	हाल BCMA_HOSTTYPE_SOC:
		वापस brcms_c_chipmatch_soc(core);
	शेष:
		pr_err("unknown host type: %i\n", core->bus->hosttype);
		वापस false;
	पूर्ण
पूर्ण

u16 brcms_b_rate_shm_offset(काष्ठा brcms_hardware *wlc_hw, u8 rate)
अणु
	u16 table_ptr;
	u8 phy_rate, index;

	/* get the phy specअगरic rate encoding क्रम the PLCP SIGNAL field */
	अगर (is_ofdm_rate(rate))
		table_ptr = M_RT_सूचीMAP_A;
	अन्यथा
		table_ptr = M_RT_सूचीMAP_B;

	/* क्रम a given rate, the LS-nibble of the PLCP SIGNAL field is
	 * the index पूर्णांकo the rate table.
	 */
	phy_rate = rate_info[rate] & BRCMS_RATE_MASK;
	index = phy_rate & 0xf;

	/* Find the SHM poपूर्णांकer to the rate table entry by looking in the
	 * Direct-map Table
	 */
	वापस 2 * brcms_b_पढ़ो_shm(wlc_hw, table_ptr + (index * 2));
पूर्ण

/*
 * bcmc_fid_generate:
 * Generate frame ID क्रम a BCMC packet.  The frag field is not used
 * क्रम MC frames so is used as part of the sequence number.
 */
अटल अंतरभूत u16
bcmc_fid_generate(काष्ठा brcms_c_info *wlc, काष्ठा brcms_bss_cfg *bsscfg,
		  काष्ठा d11txh *txh)
अणु
	u16 frameid;

	frameid = le16_to_cpu(txh->TxFrameID) & ~(TXFID_SEQ_MASK |
						  TXFID_QUEUE_MASK);
	frameid |=
	    (((wlc->
	       mc_fid_counter++) << TXFID_SEQ_SHIFT) & TXFID_SEQ_MASK) |
	    TX_BCMC_FIFO;

	वापस frameid;
पूर्ण

अटल uपूर्णांक
brcms_c_calc_ack_समय(काष्ठा brcms_c_info *wlc, u32 rspec,
		      u8 preamble_type)
अणु
	uपूर्णांक dur = 0;

	/*
	 * Spec 9.6: ack rate is the highest rate in BSSBasicRateSet that
	 * is less than or equal to the rate of the immediately previous
	 * frame in the FES
	 */
	rspec = brcms_basic_rate(wlc, rspec);
	/* ACK frame len == 14 == 2(fc) + 2(dur) + 6(ra) + 4(fcs) */
	dur =
	    brcms_c_calc_frame_समय(wlc, rspec, preamble_type,
				(DOT11_ACK_LEN + FCS_LEN));
	वापस dur;
पूर्ण

अटल uपूर्णांक
brcms_c_calc_cts_समय(काष्ठा brcms_c_info *wlc, u32 rspec,
		      u8 preamble_type)
अणु
	वापस brcms_c_calc_ack_समय(wlc, rspec, preamble_type);
पूर्ण

अटल uपूर्णांक
brcms_c_calc_ba_समय(काष्ठा brcms_c_info *wlc, u32 rspec,
		     u8 preamble_type)
अणु
	/*
	 * Spec 9.6: ack rate is the highest rate in BSSBasicRateSet that
	 * is less than or equal to the rate of the immediately previous
	 * frame in the FES
	 */
	rspec = brcms_basic_rate(wlc, rspec);
	/* BA len == 32 == 16(ctl hdr) + 4(ba len) + 8(biपंचांगap) + 4(fcs) */
	वापस brcms_c_calc_frame_समय(wlc, rspec, preamble_type,
				   (DOT11_BA_LEN + DOT11_BA_BITMAP_LEN +
				    FCS_LEN));
पूर्ण

/* brcms_c_compute_frame_dur()
 *
 * Calculate the 802.11 MAC header DUR field क्रम MPDU
 * DUR क्रम a single frame = 1 SIFS + 1 ACK
 * DUR क्रम a frame with following frags = 3 SIFS + 2 ACK + next frag समय
 *
 * rate			MPDU rate in unit of 500kbps
 * next_frag_len	next MPDU length in bytes
 * preamble_type	use लघु/GF or दीर्घ/MM PLCP header
 */
अटल u16
brcms_c_compute_frame_dur(काष्ठा brcms_c_info *wlc, u32 rate,
		      u8 preamble_type, uपूर्णांक next_frag_len)
अणु
	u16 dur, sअगरs;

	sअगरs = get_sअगरs(wlc->band);

	dur = sअगरs;
	dur += (u16) brcms_c_calc_ack_समय(wlc, rate, preamble_type);

	अगर (next_frag_len) अणु
		/* Double the current DUR to get 2 SIFS + 2 ACKs */
		dur *= 2;
		/* add another SIFS and the frag समय */
		dur += sअगरs;
		dur +=
		    (u16) brcms_c_calc_frame_समय(wlc, rate, preamble_type,
						 next_frag_len);
	पूर्ण
	वापस dur;
पूर्ण

/* The opposite of brcms_c_calc_frame_समय */
अटल uपूर्णांक
brcms_c_calc_frame_len(काष्ठा brcms_c_info *wlc, u32 ratespec,
		   u8 preamble_type, uपूर्णांक dur)
अणु
	uपूर्णांक nsyms, mac_len, Ndps, kNdps;
	uपूर्णांक rate = rspec2rate(ratespec);

	अगर (is_mcs_rate(ratespec)) अणु
		uपूर्णांक mcs = ratespec & RSPEC_RATE_MASK;
		पूर्णांक tot_streams = mcs_2_txstreams(mcs) + rspec_stc(ratespec);
		dur -= PREN_PREAMBLE + (tot_streams * PREN_PREAMBLE_EXT);
		/* payload calculation matches that of regular ofdm */
		अगर (wlc->band->bandtype == BRCM_BAND_2G)
			dur -= DOT11_OFDM_SIGNAL_EXTENSION;
		/* kNdbps = kbps * 4 */
		kNdps =	mcs_2_rate(mcs, rspec_is40mhz(ratespec),
				   rspec_issgi(ratespec)) * 4;
		nsyms = dur / APHY_SYMBOL_TIME;
		mac_len =
		    ((nsyms * kNdps) -
		     ((APHY_SERVICE_NBITS + APHY_TAIL_NBITS) * 1000)) / 8000;
	पूर्ण अन्यथा अगर (is_ofdm_rate(ratespec)) अणु
		dur -= APHY_PREAMBLE_TIME;
		dur -= APHY_SIGNAL_TIME;
		/* Ndbps = Mbps * 4 = rate(500Kbps) * 2 */
		Ndps = rate * 2;
		nsyms = dur / APHY_SYMBOL_TIME;
		mac_len =
		    ((nsyms * Ndps) -
		     (APHY_SERVICE_NBITS + APHY_TAIL_NBITS)) / 8;
	पूर्ण अन्यथा अणु
		अगर (preamble_type & BRCMS_SHORT_PREAMBLE)
			dur -= BPHY_PLCP_SHORT_TIME;
		अन्यथा
			dur -= BPHY_PLCP_TIME;
		mac_len = dur * rate;
		/* भागide out factor of 2 in rate (1/2 mbps) */
		mac_len = mac_len / 8 / 2;
	पूर्ण
	वापस mac_len;
पूर्ण

/*
 * Return true अगर the specअगरied rate is supported by the specअगरied band.
 * BRCM_BAND_AUTO indicates the current band.
 */
अटल bool brcms_c_valid_rate(काष्ठा brcms_c_info *wlc, u32 rspec, पूर्णांक band,
		    bool verbose)
अणु
	काष्ठा brcms_c_rateset *hw_rateset;
	uपूर्णांक i;

	अगर ((band == BRCM_BAND_AUTO) || (band == wlc->band->bandtype))
		hw_rateset = &wlc->band->hw_rateset;
	अन्यथा अगर (wlc->pub->_nbands > 1)
		hw_rateset = &wlc->bandstate[OTHERBANDUNIT(wlc)]->hw_rateset;
	अन्यथा
		/* other band specअगरied and we are a single band device */
		वापस false;

	/* check अगर this is a mimo rate */
	अगर (is_mcs_rate(rspec)) अणु
		अगर ((rspec & RSPEC_RATE_MASK) >= MCS_TABLE_SIZE)
			जाओ error;

		वापस isset(hw_rateset->mcs, (rspec & RSPEC_RATE_MASK));
	पूर्ण

	क्रम (i = 0; i < hw_rateset->count; i++)
		अगर (hw_rateset->rates[i] == rspec2rate(rspec))
			वापस true;
 error:
	अगर (verbose)
		brcms_err(wlc->hw->d11core, "wl%d: valid_rate: rate spec 0x%x "
			  "not in hw_rateset\n", wlc->pub->unit, rspec);

	वापस false;
पूर्ण

अटल u32
mac80211_wlc_set_nrate(काष्ठा brcms_c_info *wlc, काष्ठा brcms_band *cur_band,
		       u32 पूर्णांक_val)
अणु
	काष्ठा bcma_device *core = wlc->hw->d11core;
	u8 stf = (पूर्णांक_val & NRATE_STF_MASK) >> NRATE_STF_SHIFT;
	u8 rate = पूर्णांक_val & NRATE_RATE_MASK;
	u32 rspec;
	bool ismcs = ((पूर्णांक_val & NRATE_MCS_INUSE) == NRATE_MCS_INUSE);
	bool issgi = ((पूर्णांक_val & NRATE_SGI_MASK) >> NRATE_SGI_SHIFT);
	bool override_mcs_only = ((पूर्णांक_val & NRATE_OVERRIDE_MCS_ONLY)
				  == NRATE_OVERRIDE_MCS_ONLY);

	अगर (!ismcs)
		वापस (u32) rate;

	/* validate the combination of rate/mcs/stf is allowed */
	अगर ((wlc->pub->_n_enab & SUPPORT_11N) && ismcs) अणु
		/* mcs only allowed when nmode */
		अगर (stf > PHY_TXC1_MODE_SDM) अणु
			brcms_err(core, "wl%d: %s: Invalid stf\n",
				  wlc->pub->unit, __func__);
			जाओ करोne;
		पूर्ण

		/* mcs 32 is a special हाल, DUP mode 40 only */
		अगर (rate == 32) अणु
			अगर (!CHSPEC_IS40(wlc->home_chanspec) ||
			    ((stf != PHY_TXC1_MODE_SISO)
			     && (stf != PHY_TXC1_MODE_CDD))) अणु
				brcms_err(core, "wl%d: %s: Invalid mcs 32\n",
					  wlc->pub->unit, __func__);
				जाओ करोne;
			पूर्ण
			/* mcs > 7 must use stf SDM */
		पूर्ण अन्यथा अगर (rate > HIGHEST_SINGLE_STREAM_MCS) अणु
			/* mcs > 7 must use stf SDM */
			अगर (stf != PHY_TXC1_MODE_SDM) अणु
				brcms_dbg_mac80211(core, "wl%d: enabling "
						   "SDM mode for mcs %d\n",
						   wlc->pub->unit, rate);
				stf = PHY_TXC1_MODE_SDM;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * MCS 0-7 may use SISO, CDD, and क्रम
			 * phy_rev >= 3 STBC
			 */
			अगर ((stf > PHY_TXC1_MODE_STBC) ||
			    (!BRCMS_STBC_CAP_PHY(wlc)
			     && (stf == PHY_TXC1_MODE_STBC))) अणु
				brcms_err(core, "wl%d: %s: Invalid STBC\n",
					  wlc->pub->unit, __func__);
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (is_ofdm_rate(rate)) अणु
		अगर ((stf != PHY_TXC1_MODE_CDD) && (stf != PHY_TXC1_MODE_SISO)) अणु
			brcms_err(core, "wl%d: %s: Invalid OFDM\n",
				  wlc->pub->unit, __func__);
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अगर (is_cck_rate(rate)) अणु
		अगर ((cur_band->bandtype != BRCM_BAND_2G)
		    || (stf != PHY_TXC1_MODE_SISO)) अणु
			brcms_err(core, "wl%d: %s: Invalid CCK\n",
				  wlc->pub->unit, __func__);
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		brcms_err(core, "wl%d: %s: Unknown rate type\n",
			  wlc->pub->unit, __func__);
		जाओ करोne;
	पूर्ण
	/* make sure multiple antennae are available क्रम non-siso rates */
	अगर ((stf != PHY_TXC1_MODE_SISO) && (wlc->stf->txstreams == 1)) अणु
		brcms_err(core, "wl%d: %s: SISO antenna but !SISO "
			  "request\n", wlc->pub->unit, __func__);
		जाओ करोne;
	पूर्ण

	rspec = rate;
	अगर (ismcs) अणु
		rspec |= RSPEC_MIMORATE;
		/* For STBC populate the STC field of the ratespec */
		अगर (stf == PHY_TXC1_MODE_STBC) अणु
			u8 stc;
			stc = 1;	/* Nss क्रम single stream is always 1 */
			rspec |= (stc << RSPEC_STC_SHIFT);
		पूर्ण
	पूर्ण

	rspec |= (stf << RSPEC_STF_SHIFT);

	अगर (override_mcs_only)
		rspec |= RSPEC_OVERRIDE_MCS_ONLY;

	अगर (issgi)
		rspec |= RSPEC_SHORT_GI;

	अगर ((rate != 0)
	    && !brcms_c_valid_rate(wlc, rspec, cur_band->bandtype, true))
		वापस rate;

	वापस rspec;
करोne:
	वापस rate;
पूर्ण

/*
 * Compute PLCP, but only requires actual rate and length of pkt.
 * Rate is given in the driver standard multiple of 500 kbps.
 * le is set क्रम 11 Mbps rate अगर necessary.
 * Broken out क्रम PRQ.
 */

अटल व्योम brcms_c_cck_plcp_set(काष्ठा brcms_c_info *wlc, पूर्णांक rate_500,
			     uपूर्णांक length, u8 *plcp)
अणु
	u16 usec = 0;
	u8 le = 0;

	चयन (rate_500) अणु
	हाल BRCM_RATE_1M:
		usec = length << 3;
		अवरोध;
	हाल BRCM_RATE_2M:
		usec = length << 2;
		अवरोध;
	हाल BRCM_RATE_5M5:
		usec = (length << 4) / 11;
		अगर ((length << 4) - (usec * 11) > 0)
			usec++;
		अवरोध;
	हाल BRCM_RATE_11M:
		usec = (length << 3) / 11;
		अगर ((length << 3) - (usec * 11) > 0) अणु
			usec++;
			अगर ((usec * 11) - (length << 3) >= 8)
				le = D11B_PLCP_SIGNAL_LE;
		पूर्ण
		अवरोध;

	शेष:
		brcms_err(wlc->hw->d11core,
			  "brcms_c_cck_plcp_set: unsupported rate %d\n",
			  rate_500);
		rate_500 = BRCM_RATE_1M;
		usec = length << 3;
		अवरोध;
	पूर्ण
	/* PLCP संकेत byte */
	plcp[0] = rate_500 * 5;	/* r (500kbps) * 5 == r (100kbps) */
	/* PLCP service byte */
	plcp[1] = (u8) (le | D11B_PLCP_SIGNAL_LOCKED);
	/* PLCP length u16, little endian */
	plcp[2] = usec & 0xff;
	plcp[3] = (usec >> 8) & 0xff;
	/* PLCP CRC16 */
	plcp[4] = 0;
	plcp[5] = 0;
पूर्ण

/* Rate: 802.11 rate code, length: PSDU length in octets */
अटल व्योम brcms_c_compute_mimo_plcp(u32 rspec, uपूर्णांक length, u8 *plcp)
अणु
	u8 mcs = (u8) (rspec & RSPEC_RATE_MASK);
	plcp[0] = mcs;
	अगर (rspec_is40mhz(rspec) || (mcs == 32))
		plcp[0] |= MIMO_PLCP_40MHZ;
	BRCMS_SET_MIMO_PLCP_LEN(plcp, length);
	plcp[3] = rspec_mimoplcp3(rspec); /* rspec alपढ़ोy holds this byte */
	plcp[3] |= 0x7; /* set smoothing, not sounding ppdu & reserved */
	plcp[4] = 0; /* number of extension spatial streams bit 0 & 1 */
	plcp[5] = 0;
पूर्ण

/* Rate: 802.11 rate code, length: PSDU length in octets */
अटल व्योम
brcms_c_compute_ofdm_plcp(u32 rspec, u32 length, u8 *plcp)
अणु
	u8 rate_संकेत;
	u32 पंचांगp = 0;
	पूर्णांक rate = rspec2rate(rspec);

	/*
	 * encode rate per 802.11a-1999 sec 17.3.4.1, with lsb
	 * transmitted first
	 */
	rate_संकेत = rate_info[rate] & BRCMS_RATE_MASK;
	स_रखो(plcp, 0, D11_PHY_HDR_LEN);
	D11A_PHY_HDR_SRATE((काष्ठा ofdm_phy_hdr *) plcp, rate_संकेत);

	पंचांगp = (length & 0xfff) << 5;
	plcp[2] |= (पंचांगp >> 16) & 0xff;
	plcp[1] |= (पंचांगp >> 8) & 0xff;
	plcp[0] |= पंचांगp & 0xff;
पूर्ण

/* Rate: 802.11 rate code, length: PSDU length in octets */
अटल व्योम brcms_c_compute_cck_plcp(काष्ठा brcms_c_info *wlc, u32 rspec,
				 uपूर्णांक length, u8 *plcp)
अणु
	पूर्णांक rate = rspec2rate(rspec);

	brcms_c_cck_plcp_set(wlc, rate, length, plcp);
पूर्ण

अटल व्योम
brcms_c_compute_plcp(काष्ठा brcms_c_info *wlc, u32 rspec,
		     uपूर्णांक length, u8 *plcp)
अणु
	अगर (is_mcs_rate(rspec))
		brcms_c_compute_mimo_plcp(rspec, length, plcp);
	अन्यथा अगर (is_ofdm_rate(rspec))
		brcms_c_compute_ofdm_plcp(rspec, length, plcp);
	अन्यथा
		brcms_c_compute_cck_plcp(wlc, rspec, length, plcp);
पूर्ण

/* brcms_c_compute_rtscts_dur()
 *
 * Calculate the 802.11 MAC header DUR field क्रम an RTS or CTS frame
 * DUR क्रम normal RTS/CTS w/ frame = 3 SIFS + 1 CTS + next frame समय + 1 ACK
 * DUR क्रम CTS-TO-SELF w/ frame    = 2 SIFS         + next frame समय + 1 ACK
 *
 * cts			cts-to-self or rts/cts
 * rts_rate		rts or cts rate in unit of 500kbps
 * rate			next MPDU rate in unit of 500kbps
 * frame_len		next MPDU frame length in bytes
 */
u16
brcms_c_compute_rtscts_dur(काष्ठा brcms_c_info *wlc, bool cts_only,
			   u32 rts_rate,
			   u32 frame_rate, u8 rts_preamble_type,
			   u8 frame_preamble_type, uपूर्णांक frame_len, bool ba)
अणु
	u16 dur, sअगरs;

	sअगरs = get_sअगरs(wlc->band);

	अगर (!cts_only) अणु
		/* RTS/CTS */
		dur = 3 * sअगरs;
		dur +=
		    (u16) brcms_c_calc_cts_समय(wlc, rts_rate,
					       rts_preamble_type);
	पूर्ण अन्यथा अणु
		/* CTS-TO-SELF */
		dur = 2 * sअगरs;
	पूर्ण

	dur +=
	    (u16) brcms_c_calc_frame_समय(wlc, frame_rate, frame_preamble_type,
					 frame_len);
	अगर (ba)
		dur +=
		    (u16) brcms_c_calc_ba_समय(wlc, frame_rate,
					      BRCMS_SHORT_PREAMBLE);
	अन्यथा
		dur +=
		    (u16) brcms_c_calc_ack_समय(wlc, frame_rate,
					       frame_preamble_type);
	वापस dur;
पूर्ण

अटल u16 brcms_c_phytxctl1_calc(काष्ठा brcms_c_info *wlc, u32 rspec)
अणु
	u16 phyctl1 = 0;
	u16 bw;

	अगर (BRCMS_ISLCNPHY(wlc->band)) अणु
		bw = PHY_TXC1_BW_20MHZ;
	पूर्ण अन्यथा अणु
		bw = rspec_get_bw(rspec);
		/* 10Mhz is not supported yet */
		अगर (bw < PHY_TXC1_BW_20MHZ) अणु
			brcms_err(wlc->hw->d11core, "phytxctl1_calc: bw %d is "
				  "not supported yet, set to 20L\n", bw);
			bw = PHY_TXC1_BW_20MHZ;
		पूर्ण
	पूर्ण

	अगर (is_mcs_rate(rspec)) अणु
		uपूर्णांक mcs = rspec & RSPEC_RATE_MASK;

		/* bw, stf, coding-type is part of rspec_phytxbyte2 वापसs */
		phyctl1 = rspec_phytxbyte2(rspec);
		/* set the upper byte of phyctl1 */
		phyctl1 |= (mcs_table[mcs].tx_phy_ctl3 << 8);
	पूर्ण अन्यथा अगर (is_cck_rate(rspec) && !BRCMS_ISLCNPHY(wlc->band)
		   && !BRCMS_ISSSLPNPHY(wlc->band)) अणु
		/*
		 * In CCK mode LPPHY overloads OFDM Modulation bits with CCK
		 * Data Rate. Eventually MIMOPHY would also be converted to
		 * this क्रमmat
		 */
		/* 0 = 1Mbps; 1 = 2Mbps; 2 = 5.5Mbps; 3 = 11Mbps */
		phyctl1 = (bw | (rspec_stf(rspec) << PHY_TXC1_MODE_SHIFT));
	पूर्ण अन्यथा अणु		/* legacy OFDM/CCK */
		s16 phycfg;
		/* get the phyctl byte from rate phycfg table */
		phycfg = brcms_c_rate_legacy_phyctl(rspec2rate(rspec));
		अगर (phycfg == -1) अणु
			brcms_err(wlc->hw->d11core, "phytxctl1_calc: wrong "
				  "legacy OFDM/CCK rate\n");
			phycfg = 0;
		पूर्ण
		/* set the upper byte of phyctl1 */
		phyctl1 =
		    (bw | (phycfg << 8) |
		     (rspec_stf(rspec) << PHY_TXC1_MODE_SHIFT));
	पूर्ण
	वापस phyctl1;
पूर्ण

/*
 * Add काष्ठा d11txh, काष्ठा cck_phy_hdr.
 *
 * 'p' data must start with 802.11 MAC header
 * 'p' must allow enough bytes of local headers to be "pushed" onto the packet
 *
 * headroom == D11_PHY_HDR_LEN + D11_TXH_LEN (D11_TXH_LEN is now 104 bytes)
 *
 */
अटल u16
brcms_c_d11hdrs_mac80211(काष्ठा brcms_c_info *wlc, काष्ठा ieee80211_hw *hw,
		     काष्ठा sk_buff *p, काष्ठा scb *scb, uपूर्णांक frag,
		     uपूर्णांक nfrags, uपूर्णांक queue, uपूर्णांक next_frag_len)
अणु
	काष्ठा ieee80211_hdr *h;
	काष्ठा d11txh *txh;
	u8 *plcp, plcp_fallback[D11_PHY_HDR_LEN];
	पूर्णांक len, phylen, rts_phylen;
	u16 mch, phyctl, xfts, मुख्यrates;
	u16 seq = 0, mcl = 0, status = 0, frameid = 0;
	u32 rspec[2] = अणु BRCM_RATE_1M, BRCM_RATE_1M पूर्ण;
	u32 rts_rspec[2] = अणु BRCM_RATE_1M, BRCM_RATE_1M पूर्ण;
	bool use_rts = false;
	bool use_cts = false;
	bool use_rअगरs = false;
	u8 preamble_type[2] = अणु BRCMS_LONG_PREAMBLE, BRCMS_LONG_PREAMBLE पूर्ण;
	u8 rts_preamble_type[2] = अणु BRCMS_LONG_PREAMBLE, BRCMS_LONG_PREAMBLE पूर्ण;
	u8 *rts_plcp, rts_plcp_fallback[D11_PHY_HDR_LEN];
	काष्ठा ieee80211_rts *rts = शून्य;
	bool qos;
	uपूर्णांक ac;
	bool hwtkmic = false;
	u16 mimo_ctlchbw = PHY_TXC1_BW_20MHZ;
#घोषणा ANTCFG_NONE 0xFF
	u8 antcfg = ANTCFG_NONE;
	u8 fbantcfg = ANTCFG_NONE;
	uपूर्णांक phyctl1_stf = 0;
	u16 durid = 0;
	काष्ठा ieee80211_tx_rate *txrate[2];
	पूर्णांक k;
	काष्ठा ieee80211_tx_info *tx_info;
	bool is_mcs;
	u16 mimo_txbw;
	u8 mimo_preamble_type;

	/* locate 802.11 MAC header */
	h = (काष्ठा ieee80211_hdr *)(p->data);
	qos = ieee80211_is_data_qos(h->frame_control);

	/* compute length of frame in bytes क्रम use in PLCP computations */
	len = p->len;
	phylen = len + FCS_LEN;

	/* Get tx_info */
	tx_info = IEEE80211_SKB_CB(p);

	/* add PLCP */
	plcp = skb_push(p, D11_PHY_HDR_LEN);

	/* add Broadcom tx descriptor header */
	txh = (काष्ठा d11txh *) skb_push(p, D11_TXH_LEN);
	स_रखो(txh, 0, D11_TXH_LEN);

	/* setup frameid */
	अगर (tx_info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ) अणु
		/* non-AP STA should never use BCMC queue */
		अगर (queue == TX_BCMC_FIFO) अणु
			brcms_err(wlc->hw->d11core,
				  "wl%d: %s: ASSERT queue == TX_BCMC!\n",
				  wlc->pub->unit, __func__);
			frameid = bcmc_fid_generate(wlc, शून्य, txh);
		पूर्ण अन्यथा अणु
			/* Increment the counter क्रम first fragment */
			अगर (tx_info->flags & IEEE80211_TX_CTL_FIRST_FRAGMENT)
				scb->seqnum[p->priority]++;

			/* extract fragment number from frame first */
			seq = le16_to_cpu(h->seq_ctrl) & FRAGNUM_MASK;
			seq |= (scb->seqnum[p->priority] << SEQNUM_SHIFT);
			h->seq_ctrl = cpu_to_le16(seq);

			frameid = ((seq << TXFID_SEQ_SHIFT) & TXFID_SEQ_MASK) |
			    (queue & TXFID_QUEUE_MASK);
		पूर्ण
	पूर्ण
	frameid |= queue & TXFID_QUEUE_MASK;

	/* set the ignpmq bit क्रम all pkts tx'd in PS mode and क्रम beacons */
	अगर (ieee80211_is_beacon(h->frame_control))
		mcl |= TXC_IGNOREPMQ;

	txrate[0] = tx_info->control.rates;
	txrate[1] = txrate[0] + 1;

	/*
	 * अगर rate control algorithm didn't give us a fallback
	 * rate, use the primary rate
	 */
	अगर (txrate[1]->idx < 0)
		txrate[1] = txrate[0];

	क्रम (k = 0; k < hw->max_rates; k++) अणु
		is_mcs = txrate[k]->flags & IEEE80211_TX_RC_MCS ? true : false;
		अगर (!is_mcs) अणु
			अगर ((txrate[k]->idx >= 0)
			    && (txrate[k]->idx <
				hw->wiphy->bands[tx_info->band]->n_bitrates)) अणु
				rspec[k] =
				    hw->wiphy->bands[tx_info->band]->
				    bitrates[txrate[k]->idx].hw_value;
			पूर्ण अन्यथा अणु
				rspec[k] = BRCM_RATE_1M;
			पूर्ण
		पूर्ण अन्यथा अणु
			rspec[k] = mac80211_wlc_set_nrate(wlc, wlc->band,
					NRATE_MCS_INUSE | txrate[k]->idx);
		पूर्ण

		/*
		 * Currently only support same setting क्रम primay and
		 * fallback rates. Unअगरy flags क्रम each rate पूर्णांकo a
		 * single value क्रम the frame
		 */
		use_rts |=
		    txrate[k]->
		    flags & IEEE80211_TX_RC_USE_RTS_CTS ? true : false;
		use_cts |=
		    txrate[k]->
		    flags & IEEE80211_TX_RC_USE_CTS_PROTECT ? true : false;


		/*
		 * (1) RATE:
		 *   determine and validate primary rate
		 *   and fallback rates
		 */
		अगर (!rspec_active(rspec[k])) अणु
			rspec[k] = BRCM_RATE_1M;
		पूर्ण अन्यथा अणु
			अगर (!is_multicast_ether_addr(h->addr1)) अणु
				/* set tx antenna config */
				brcms_c_antsel_antcfg_get(wlc->asi, false,
					false, 0, 0, &antcfg, &fbantcfg);
			पूर्ण
		पूर्ण
	पूर्ण

	phyctl1_stf = wlc->stf->ss_opmode;

	अगर (wlc->pub->_n_enab & SUPPORT_11N) अणु
		क्रम (k = 0; k < hw->max_rates; k++) अणु
			/*
			 * apply siso/cdd to single stream mcs's or ofdm
			 * अगर rspec is स्वतः selected
			 */
			अगर (((is_mcs_rate(rspec[k]) &&
			      is_single_stream(rspec[k] & RSPEC_RATE_MASK)) ||
			     is_ofdm_rate(rspec[k]))
			    && ((rspec[k] & RSPEC_OVERRIDE_MCS_ONLY)
				|| !(rspec[k] & RSPEC_OVERRIDE))) अणु
				rspec[k] &= ~(RSPEC_STF_MASK | RSPEC_STC_MASK);

				/* For SISO MCS use STBC अगर possible */
				अगर (is_mcs_rate(rspec[k])
				    && BRCMS_STF_SS_STBC_TX(wlc, scb)) अणु
					u8 stc;

					/* Nss क्रम single stream is always 1 */
					stc = 1;
					rspec[k] |= (PHY_TXC1_MODE_STBC <<
							RSPEC_STF_SHIFT) |
						    (stc << RSPEC_STC_SHIFT);
				पूर्ण अन्यथा
					rspec[k] |=
					    (phyctl1_stf << RSPEC_STF_SHIFT);
			पूर्ण

			/*
			 * Is the phy configured to use 40MHZ frames? If
			 * so then pick the desired txbw
			 */
			अगर (brcms_chspec_bw(wlc->chanspec) == BRCMS_40_MHZ) अणु
				/* शेष txbw is 20in40 SB */
				mimo_ctlchbw = mimo_txbw =
				   CHSPEC_SB_UPPER(wlc_phy_chanspec_get(
								 wlc->band->pi))
				   ? PHY_TXC1_BW_20MHZ_UP : PHY_TXC1_BW_20MHZ;

				अगर (is_mcs_rate(rspec[k])) अणु
					/* mcs 32 must be 40b/w DUP */
					अगर ((rspec[k] & RSPEC_RATE_MASK)
					    == 32) अणु
						mimo_txbw =
						    PHY_TXC1_BW_40MHZ_DUP;
						/* use override */
					पूर्ण अन्यथा अगर (wlc->mimo_40txbw != AUTO)
						mimo_txbw = wlc->mimo_40txbw;
					/* अन्यथा check अगर dst is using 40 Mhz */
					अन्यथा अगर (scb->flags & SCB_IS40)
						mimo_txbw = PHY_TXC1_BW_40MHZ;
				पूर्ण अन्यथा अगर (is_ofdm_rate(rspec[k])) अणु
					अगर (wlc->ofdm_40txbw != AUTO)
						mimo_txbw = wlc->ofdm_40txbw;
				पूर्ण अन्यथा अगर (wlc->cck_40txbw != AUTO) अणु
					mimo_txbw = wlc->cck_40txbw;
				पूर्ण
			पूर्ण अन्यथा अणु
				/*
				 * mcs32 is 40 b/w only.
				 * This is possible क्रम probe packets on
				 * a STA during SCAN
				 */
				अगर ((rspec[k] & RSPEC_RATE_MASK) == 32)
					/* mcs 0 */
					rspec[k] = RSPEC_MIMORATE;

				mimo_txbw = PHY_TXC1_BW_20MHZ;
			पूर्ण

			/* Set channel width */
			rspec[k] &= ~RSPEC_BW_MASK;
			अगर ((k == 0) || ((k > 0) && is_mcs_rate(rspec[k])))
				rspec[k] |= (mimo_txbw << RSPEC_BW_SHIFT);
			अन्यथा
				rspec[k] |= (mimo_ctlchbw << RSPEC_BW_SHIFT);

			/* Disable लघु GI, not supported yet */
			rspec[k] &= ~RSPEC_SHORT_GI;

			mimo_preamble_type = BRCMS_MM_PREAMBLE;
			अगर (txrate[k]->flags & IEEE80211_TX_RC_GREEN_FIELD)
				mimo_preamble_type = BRCMS_GF_PREAMBLE;

			अगर ((txrate[k]->flags & IEEE80211_TX_RC_MCS)
			    && (!is_mcs_rate(rspec[k]))) अणु
				brcms_warn(wlc->hw->d11core,
					   "wl%d: %s: IEEE80211_TX_RC_MCS != is_mcs_rate(rspec)\n",
					   wlc->pub->unit, __func__);
			पूर्ण

			अगर (is_mcs_rate(rspec[k])) अणु
				preamble_type[k] = mimo_preamble_type;

				/*
				 * अगर SGI is selected, then क्रमced mm
				 * क्रम single stream
				 */
				अगर ((rspec[k] & RSPEC_SHORT_GI)
				    && is_single_stream(rspec[k] &
							RSPEC_RATE_MASK))
					preamble_type[k] = BRCMS_MM_PREAMBLE;
			पूर्ण

			/* should be better conditionalized */
			अगर (!is_mcs_rate(rspec[0])
			    && (tx_info->control.rates[0].
				flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE))
				preamble_type[k] = BRCMS_SHORT_PREAMBLE;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (k = 0; k < hw->max_rates; k++) अणु
			/* Set ctrlchbw as 20Mhz */
			rspec[k] &= ~RSPEC_BW_MASK;
			rspec[k] |= (PHY_TXC1_BW_20MHZ << RSPEC_BW_SHIFT);

			/* क्रम nphy, stf of ofdm frames must follow policies */
			अगर (BRCMS_ISNPHY(wlc->band) && is_ofdm_rate(rspec[k])) अणु
				rspec[k] &= ~RSPEC_STF_MASK;
				rspec[k] |= phyctl1_stf << RSPEC_STF_SHIFT;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Reset these क्रम use with AMPDU's */
	txrate[0]->count = 0;
	txrate[1]->count = 0;

	/* (2) PROTECTION, may change rspec */
	अगर ((ieee80211_is_data(h->frame_control) ||
	    ieee80211_is_mgmt(h->frame_control)) &&
	    (phylen > wlc->RTSThresh) && !is_multicast_ether_addr(h->addr1))
		use_rts = true;

	/* (3) PLCP: determine PLCP header and MAC duration,
	 * fill काष्ठा d11txh */
	brcms_c_compute_plcp(wlc, rspec[0], phylen, plcp);
	brcms_c_compute_plcp(wlc, rspec[1], phylen, plcp_fallback);
	स_नकल(&txh->FragPLCPFallback,
	       plcp_fallback, माप(txh->FragPLCPFallback));

	/* Length field now put in CCK FBR CRC field */
	अगर (is_cck_rate(rspec[1])) अणु
		txh->FragPLCPFallback[4] = phylen & 0xff;
		txh->FragPLCPFallback[5] = (phylen & 0xff00) >> 8;
	पूर्ण

	/* MIMO-RATE: need validation ?? */
	मुख्यrates = is_ofdm_rate(rspec[0]) ?
			D11A_PHY_HDR_GRATE((काष्ठा ofdm_phy_hdr *) plcp) :
			plcp[0];

	/* DUR field क्रम मुख्य rate */
	अगर (!ieee80211_is_pspoll(h->frame_control) &&
	    !is_multicast_ether_addr(h->addr1) && !use_rअगरs) अणु
		durid =
		    brcms_c_compute_frame_dur(wlc, rspec[0], preamble_type[0],
					  next_frag_len);
		h->duration_id = cpu_to_le16(durid);
	पूर्ण अन्यथा अगर (use_rअगरs) अणु
		/* NAV protect to end of next max packet size */
		durid =
		    (u16) brcms_c_calc_frame_समय(wlc, rspec[0],
						 preamble_type[0],
						 DOT11_MAX_FRAG_LEN);
		durid += RIFS_11N_TIME;
		h->duration_id = cpu_to_le16(durid);
	पूर्ण

	/* DUR field क्रम fallback rate */
	अगर (ieee80211_is_pspoll(h->frame_control))
		txh->FragDurFallback = h->duration_id;
	अन्यथा अगर (is_multicast_ether_addr(h->addr1) || use_rअगरs)
		txh->FragDurFallback = 0;
	अन्यथा अणु
		durid = brcms_c_compute_frame_dur(wlc, rspec[1],
					      preamble_type[1], next_frag_len);
		txh->FragDurFallback = cpu_to_le16(durid);
	पूर्ण

	/* (4) MAC-HDR: MacTxControlLow */
	अगर (frag == 0)
		mcl |= TXC_STARTMSDU;

	अगर (!is_multicast_ether_addr(h->addr1))
		mcl |= TXC_IMMEDACK;

	अगर (wlc->band->bandtype == BRCM_BAND_5G)
		mcl |= TXC_FREQBAND_5G;

	अगर (CHSPEC_IS40(wlc_phy_chanspec_get(wlc->band->pi)))
		mcl |= TXC_BW_40;

	/* set AMIC bit अगर using hardware TKIP MIC */
	अगर (hwtkmic)
		mcl |= TXC_AMIC;

	txh->MacTxControlLow = cpu_to_le16(mcl);

	/* MacTxControlHigh */
	mch = 0;

	/* Set fallback rate preamble type */
	अगर ((preamble_type[1] == BRCMS_SHORT_PREAMBLE) ||
	    (preamble_type[1] == BRCMS_GF_PREAMBLE)) अणु
		अगर (rspec2rate(rspec[1]) != BRCM_RATE_1M)
			mch |= TXC_PREAMBLE_DATA_FB_SHORT;
	पूर्ण

	/* MacFrameControl */
	स_नकल(&txh->MacFrameControl, &h->frame_control, माप(u16));
	txh->TxFesTimeNormal = cpu_to_le16(0);

	txh->TxFesTimeFallback = cpu_to_le16(0);

	/* TxFrameRA */
	स_नकल(&txh->TxFrameRA, &h->addr1, ETH_ALEN);

	/* TxFrameID */
	txh->TxFrameID = cpu_to_le16(frameid);

	/*
	 * TxStatus, Note the हाल of recreating the first frag of a suppressed
	 * frame then we may need to reset the retry cnt's via the status reg
	 */
	txh->TxStatus = cpu_to_le16(status);

	/*
	 * extra fields क्रम ucode AMPDU aggregation, the new fields are added to
	 * the END of previous काष्ठाure so that it's compatible in driver.
	 */
	txh->MaxNMpdus = cpu_to_le16(0);
	txh->MaxABytes_MRT = cpu_to_le16(0);
	txh->MaxABytes_FBR = cpu_to_le16(0);
	txh->MinMBytes = cpu_to_le16(0);

	/* (5) RTS/CTS: determine RTS/CTS PLCP header and MAC duration,
	 * furnish काष्ठा d11txh */
	/* RTS PLCP header and RTS frame */
	अगर (use_rts || use_cts) अणु
		अगर (use_rts && use_cts)
			use_cts = false;

		क्रम (k = 0; k < 2; k++) अणु
			rts_rspec[k] = brcms_c_rspec_to_rts_rspec(wlc, rspec[k],
							      false,
							      mimo_ctlchbw);
		पूर्ण

		अगर (!is_ofdm_rate(rts_rspec[0]) &&
		    !((rspec2rate(rts_rspec[0]) == BRCM_RATE_1M) ||
		      (wlc->PLCPHdr_override == BRCMS_PLCP_LONG))) अणु
			rts_preamble_type[0] = BRCMS_SHORT_PREAMBLE;
			mch |= TXC_PREAMBLE_RTS_MAIN_SHORT;
		पूर्ण

		अगर (!is_ofdm_rate(rts_rspec[1]) &&
		    !((rspec2rate(rts_rspec[1]) == BRCM_RATE_1M) ||
		      (wlc->PLCPHdr_override == BRCMS_PLCP_LONG))) अणु
			rts_preamble_type[1] = BRCMS_SHORT_PREAMBLE;
			mch |= TXC_PREAMBLE_RTS_FB_SHORT;
		पूर्ण

		/* RTS/CTS additions to MacTxControlLow */
		अगर (use_cts) अणु
			txh->MacTxControlLow |= cpu_to_le16(TXC_SENDCTS);
		पूर्ण अन्यथा अणु
			txh->MacTxControlLow |= cpu_to_le16(TXC_SENDRTS);
			txh->MacTxControlLow |= cpu_to_le16(TXC_LONGFRAME);
		पूर्ण

		/* RTS PLCP header */
		rts_plcp = txh->RTSPhyHeader;
		अगर (use_cts)
			rts_phylen = DOT11_CTS_LEN + FCS_LEN;
		अन्यथा
			rts_phylen = DOT11_RTS_LEN + FCS_LEN;

		brcms_c_compute_plcp(wlc, rts_rspec[0], rts_phylen, rts_plcp);

		/* fallback rate version of RTS PLCP header */
		brcms_c_compute_plcp(wlc, rts_rspec[1], rts_phylen,
				 rts_plcp_fallback);
		स_नकल(&txh->RTSPLCPFallback, rts_plcp_fallback,
		       माप(txh->RTSPLCPFallback));

		/* RTS frame fields... */
		rts = (काष्ठा ieee80211_rts *)&txh->rts_frame;

		durid = brcms_c_compute_rtscts_dur(wlc, use_cts, rts_rspec[0],
					       rspec[0], rts_preamble_type[0],
					       preamble_type[0], phylen, false);
		rts->duration = cpu_to_le16(durid);
		/* fallback rate version of RTS DUR field */
		durid = brcms_c_compute_rtscts_dur(wlc, use_cts,
					       rts_rspec[1], rspec[1],
					       rts_preamble_type[1],
					       preamble_type[1], phylen, false);
		txh->RTSDurFallback = cpu_to_le16(durid);

		अगर (use_cts) अणु
			rts->frame_control = cpu_to_le16(IEEE80211_FTYPE_CTL |
							 IEEE80211_STYPE_CTS);

			स_नकल(&rts->ra, &h->addr2, ETH_ALEN);
		पूर्ण अन्यथा अणु
			rts->frame_control = cpu_to_le16(IEEE80211_FTYPE_CTL |
							 IEEE80211_STYPE_RTS);

			स_नकल(&rts->ra, &h->addr1, 2 * ETH_ALEN);
		पूर्ण

		/* मुख्यrate
		 *    low 8 bits: मुख्य frag rate/mcs,
		 *    high 8 bits: rts/cts rate/mcs
		 */
		मुख्यrates |= (is_ofdm_rate(rts_rspec[0]) ?
				D11A_PHY_HDR_GRATE(
					(काष्ठा ofdm_phy_hdr *) rts_plcp) :
				rts_plcp[0]) << 8;
	पूर्ण अन्यथा अणु
		स_रखो(txh->RTSPhyHeader, 0, D11_PHY_HDR_LEN);
		स_रखो(&txh->rts_frame, 0, माप(काष्ठा ieee80211_rts));
		स_रखो(txh->RTSPLCPFallback, 0, माप(txh->RTSPLCPFallback));
		txh->RTSDurFallback = 0;
	पूर्ण

#अगर_घोषित SUPPORT_40MHZ
	/* add null delimiter count */
	अगर ((tx_info->flags & IEEE80211_TX_CTL_AMPDU) && is_mcs_rate(rspec))
		txh->RTSPLCPFallback[AMPDU_FBR_शून्य_DELIM] =
		   brcm_c_ampdu_null_delim_cnt(wlc->ampdu, scb, rspec, phylen);

#पूर्ण_अगर

	/*
	 * Now that RTS/RTS FB preamble types are updated, ग_लिखो
	 * the final value
	 */
	txh->MacTxControlHigh = cpu_to_le16(mch);

	/*
	 * MainRates (both the rts and frag plcp rates have
	 * been calculated now)
	 */
	txh->MainRates = cpu_to_le16(मुख्यrates);

	/* XtraFrameTypes */
	xfts = frametype(rspec[1], wlc->mimoft);
	xfts |= (frametype(rts_rspec[0], wlc->mimoft) << XFTS_RTS_FT_SHIFT);
	xfts |= (frametype(rts_rspec[1], wlc->mimoft) << XFTS_FBRRTS_FT_SHIFT);
	xfts |= CHSPEC_CHANNEL(wlc_phy_chanspec_get(wlc->band->pi)) <<
							     XFTS_CHANNEL_SHIFT;
	txh->XtraFrameTypes = cpu_to_le16(xfts);

	/* PhyTxControlWord */
	phyctl = frametype(rspec[0], wlc->mimoft);
	अगर ((preamble_type[0] == BRCMS_SHORT_PREAMBLE) ||
	    (preamble_type[0] == BRCMS_GF_PREAMBLE)) अणु
		अगर (rspec2rate(rspec[0]) != BRCM_RATE_1M)
			phyctl |= PHY_TXC_SHORT_HDR;
	पूर्ण

	/* phytxant is properly bit shअगरted */
	phyctl |= brcms_c_stf_d11hdrs_phyctl_txant(wlc, rspec[0]);
	txh->PhyTxControlWord = cpu_to_le16(phyctl);

	/* PhyTxControlWord_1 */
	अगर (BRCMS_PHY_11N_CAP(wlc->band)) अणु
		u16 phyctl1 = 0;

		phyctl1 = brcms_c_phytxctl1_calc(wlc, rspec[0]);
		txh->PhyTxControlWord_1 = cpu_to_le16(phyctl1);
		phyctl1 = brcms_c_phytxctl1_calc(wlc, rspec[1]);
		txh->PhyTxControlWord_1_Fbr = cpu_to_le16(phyctl1);

		अगर (use_rts || use_cts) अणु
			phyctl1 = brcms_c_phytxctl1_calc(wlc, rts_rspec[0]);
			txh->PhyTxControlWord_1_Rts = cpu_to_le16(phyctl1);
			phyctl1 = brcms_c_phytxctl1_calc(wlc, rts_rspec[1]);
			txh->PhyTxControlWord_1_FbrRts = cpu_to_le16(phyctl1);
		पूर्ण

		/*
		 * For mcs frames, अगर mixedmode(overloaded with दीर्घ preamble)
		 * is going to be set, fill in non-zero MModeLen and/or
		 * MModeFbrLen it will be unnecessary अगर they are separated
		 */
		अगर (is_mcs_rate(rspec[0]) &&
		    (preamble_type[0] == BRCMS_MM_PREAMBLE)) अणु
			u16 mmodelen =
			    brcms_c_calc_lsig_len(wlc, rspec[0], phylen);
			txh->MModeLen = cpu_to_le16(mmodelen);
		पूर्ण

		अगर (is_mcs_rate(rspec[1]) &&
		    (preamble_type[1] == BRCMS_MM_PREAMBLE)) अणु
			u16 mmodefbrlen =
			    brcms_c_calc_lsig_len(wlc, rspec[1], phylen);
			txh->MModeFbrLen = cpu_to_le16(mmodefbrlen);
		पूर्ण
	पूर्ण

	ac = skb_get_queue_mapping(p);
	अगर ((scb->flags & SCB_WMECAP) && qos && wlc->edcf_txop[ac]) अणु
		uपूर्णांक frag_dur, dur, dur_fallback;

		/* WME: Update TXOP threshold */
		अगर (!(tx_info->flags & IEEE80211_TX_CTL_AMPDU) && frag == 0) अणु
			frag_dur =
			    brcms_c_calc_frame_समय(wlc, rspec[0],
					preamble_type[0], phylen);

			अगर (rts) अणु
				/* 1 RTS or CTS-to-self frame */
				dur =
				    brcms_c_calc_cts_समय(wlc, rts_rspec[0],
						      rts_preamble_type[0]);
				dur_fallback =
				    brcms_c_calc_cts_समय(wlc, rts_rspec[1],
						      rts_preamble_type[1]);
				/* (SIFS + CTS) + SIFS + frame + SIFS + ACK */
				dur += le16_to_cpu(rts->duration);
				dur_fallback +=
					le16_to_cpu(txh->RTSDurFallback);
			पूर्ण अन्यथा अगर (use_rअगरs) अणु
				dur = frag_dur;
				dur_fallback = 0;
			पूर्ण अन्यथा अणु
				/* frame + SIFS + ACK */
				dur = frag_dur;
				dur +=
				    brcms_c_compute_frame_dur(wlc, rspec[0],
							  preamble_type[0], 0);

				dur_fallback =
				    brcms_c_calc_frame_समय(wlc, rspec[1],
							preamble_type[1],
							phylen);
				dur_fallback +=
				    brcms_c_compute_frame_dur(wlc, rspec[1],
							  preamble_type[1], 0);
			पूर्ण
			/* NEED to set TxFesTimeNormal (hard) */
			txh->TxFesTimeNormal = cpu_to_le16((u16) dur);
			/*
			 * NEED to set fallback rate version of
			 * TxFesTimeNormal (hard)
			 */
			txh->TxFesTimeFallback =
				cpu_to_le16((u16) dur_fallback);

			/*
			 * update txop byte threshold (txop minus पूर्णांकraframe
			 * overhead)
			 */
			अगर (wlc->edcf_txop[ac] >= (dur - frag_dur)) अणु
				uपूर्णांक newfragthresh;

				newfragthresh =
				    brcms_c_calc_frame_len(wlc,
					rspec[0], preamble_type[0],
					(wlc->edcf_txop[ac] -
						(dur - frag_dur)));
				/* range bound the fragthreshold */
				अगर (newfragthresh < DOT11_MIN_FRAG_LEN)
					newfragthresh =
					    DOT11_MIN_FRAG_LEN;
				अन्यथा अगर (newfragthresh >
					 wlc->usr_fragthresh)
					newfragthresh =
					    wlc->usr_fragthresh;
				/* update the fragthresh and करो txc update */
				अगर (wlc->fragthresh[queue] !=
				    (u16) newfragthresh)
					wlc->fragthresh[queue] =
					    (u16) newfragthresh;
			पूर्ण अन्यथा अणु
				brcms_warn(wlc->hw->d11core,
					   "wl%d: %s txop invalid for rate %d\n",
					   wlc->pub->unit, fअगरo_names[queue],
					   rspec2rate(rspec[0]));
			पूर्ण

			अगर (dur > wlc->edcf_txop[ac])
				brcms_warn(wlc->hw->d11core,
					   "wl%d: %s: %s txop exceeded phylen %d/%d dur %d/%d\n",
					   wlc->pub->unit, __func__,
					   fअगरo_names[queue],
					   phylen, wlc->fragthresh[queue],
					   dur, wlc->edcf_txop[ac]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक brcms_c_tx(काष्ठा brcms_c_info *wlc, काष्ठा sk_buff *skb)
अणु
	काष्ठा dma_pub *dma;
	पूर्णांक fअगरo, ret = -ENOSPC;
	काष्ठा d11txh *txh;
	u16 frameid = INVALIDFID;

	fअगरo = brcms_ac_to_fअगरo(skb_get_queue_mapping(skb));
	dma = wlc->hw->di[fअगरo];
	txh = (काष्ठा d11txh *)(skb->data);

	अगर (dma->txavail == 0) अणु
		/*
		 * We someबार get a frame from mac80211 after stopping
		 * the queues. This only ever seems to be a single frame
		 * and is seems likely to be a race. TX_HEADROOM should
		 * ensure that we have enough space to handle these stray
		 * packets, so warn अगर there isn't. If we're out of space
		 * in the tx ring and the tx queue isn't stopped then
		 * we've really got a bug; warn loudly अगर that happens.
		 */
		brcms_warn(wlc->hw->d11core,
			   "Received frame for tx with no space in DMA ring\n");
		WARN_ON(!ieee80211_queue_stopped(wlc->pub->ieee_hw,
						 skb_get_queue_mapping(skb)));
		वापस -ENOSPC;
	पूर्ण

	/* When a BC/MC frame is being committed to the BCMC fअगरo
	 * via DMA (NOT PIO), update ucode or BSS info as appropriate.
	 */
	अगर (fअगरo == TX_BCMC_FIFO)
		frameid = le16_to_cpu(txh->TxFrameID);

	/* Commit BCMC sequence number in the SHM frame ID location */
	अगर (frameid != INVALIDFID) अणु
		/*
		 * To inक्रमm the ucode of the last mcast frame posted
		 * so that it can clear moredata bit
		 */
		brcms_b_ग_लिखो_shm(wlc->hw, M_BCMC_FID, frameid);
	पूर्ण

	ret = brcms_c_txfअगरo(wlc, fअगरo, skb);
	/*
	 * The only reason क्रम brcms_c_txfअगरo to fail is because
	 * there weren't any DMA descriptors, but we've alपढ़ोy
	 * checked क्रम that. So अगर it करोes fail yell loudly.
	 */
	WARN_ON_ONCE(ret);

	वापस ret;
पूर्ण

bool brcms_c_sendpkt_mac80211(काष्ठा brcms_c_info *wlc, काष्ठा sk_buff *sdu,
			      काष्ठा ieee80211_hw *hw)
अणु
	uपूर्णांक fअगरo;
	काष्ठा scb *scb = &wlc->pri_scb;

	fअगरo = brcms_ac_to_fअगरo(skb_get_queue_mapping(sdu));
	brcms_c_d11hdrs_mac80211(wlc, hw, sdu, scb, 0, 1, fअगरo, 0);
	अगर (!brcms_c_tx(wlc, sdu))
		वापस true;

	/* packet discarded */
	dev_kमुक्त_skb_any(sdu);
	वापस false;
पूर्ण

पूर्णांक
brcms_c_txfअगरo(काष्ठा brcms_c_info *wlc, uपूर्णांक fअगरo, काष्ठा sk_buff *p)
अणु
	काष्ठा dma_pub *dma = wlc->hw->di[fअगरo];
	पूर्णांक ret;
	u16 queue;

	ret = dma_txfast(wlc, dma, p);
	अगर (ret	< 0)
		wiphy_err(wlc->wiphy, "txfifo: fatal, toss frames !!!\n");

	/*
	 * Stop queue अगर DMA ring is full. Reserve some मुक्त descriptors,
	 * as we someबार receive a frame from mac80211 after the queues
	 * are stopped.
	 */
	queue = skb_get_queue_mapping(p);
	अगर (dma->txavail <= TX_HEADROOM && fअगरo < TX_BCMC_FIFO &&
	    !ieee80211_queue_stopped(wlc->pub->ieee_hw, queue))
		ieee80211_stop_queue(wlc->pub->ieee_hw, queue);

	वापस ret;
पूर्ण

u32
brcms_c_rspec_to_rts_rspec(काष्ठा brcms_c_info *wlc, u32 rspec,
			   bool use_rspec, u16 mimo_ctlchbw)
अणु
	u32 rts_rspec = 0;

	अगर (use_rspec)
		/* use frame rate as rts rate */
		rts_rspec = rspec;
	अन्यथा अगर (wlc->band->gmode && wlc->protection->_g && !is_cck_rate(rspec))
		/* Use 11Mbps as the g protection RTS target rate and fallback.
		 * Use the brcms_basic_rate() lookup to find the best basic rate
		 * under the target in हाल 11 Mbps is not Basic.
		 * 6 and 9 Mbps are not usually selected by rate selection, but
		 * even अगर the OFDM rate we are protecting is 6 or 9 Mbps, 11
		 * is more robust.
		 */
		rts_rspec = brcms_basic_rate(wlc, BRCM_RATE_11M);
	अन्यथा
		/* calculate RTS rate and fallback rate based on the frame rate
		 * RTS must be sent at a basic rate since it is a
		 * control frame, sec 9.6 of 802.11 spec
		 */
		rts_rspec = brcms_basic_rate(wlc, rspec);

	अगर (BRCMS_PHY_11N_CAP(wlc->band)) अणु
		/* set rts txbw to correct side band */
		rts_rspec &= ~RSPEC_BW_MASK;

		/*
		 * अगर rspec/rspec_fallback is 40MHz, then send RTS on both
		 * 20MHz channel (DUP), otherwise send RTS on control channel
		 */
		अगर (rspec_is40mhz(rspec) && !is_cck_rate(rts_rspec))
			rts_rspec |= (PHY_TXC1_BW_40MHZ_DUP << RSPEC_BW_SHIFT);
		अन्यथा
			rts_rspec |= (mimo_ctlchbw << RSPEC_BW_SHIFT);

		/* pick siso/cdd as शेष क्रम ofdm */
		अगर (is_ofdm_rate(rts_rspec)) अणु
			rts_rspec &= ~RSPEC_STF_MASK;
			rts_rspec |= (wlc->stf->ss_opmode << RSPEC_STF_SHIFT);
		पूर्ण
	पूर्ण
	वापस rts_rspec;
पूर्ण

/* Update beacon listen पूर्णांकerval in shared memory */
अटल व्योम brcms_c_bcn_li_upd(काष्ठा brcms_c_info *wlc)
अणु
	/* wake up every DTIM is the शेष */
	अगर (wlc->bcn_li_dtim == 1)
		brcms_b_ग_लिखो_shm(wlc->hw, M_BCN_LI, 0);
	अन्यथा
		brcms_b_ग_लिखो_shm(wlc->hw, M_BCN_LI,
			      (wlc->bcn_li_dtim << 8) | wlc->bcn_li_bcn);
पूर्ण

अटल व्योम
brcms_b_पढ़ो_tsf(काष्ठा brcms_hardware *wlc_hw, u32 *tsf_l_ptr,
		  u32 *tsf_h_ptr)
अणु
	काष्ठा bcma_device *core = wlc_hw->d11core;

	/* पढ़ो the tsf समयr low, then high to get an atomic पढ़ो */
	*tsf_l_ptr = bcma_पढ़ो32(core, D11REGOFFS(tsf_समयrlow));
	*tsf_h_ptr = bcma_पढ़ो32(core, D11REGOFFS(tsf_समयrhigh));
पूर्ण

/*
 * recover 64bit TSF value from the 16bit TSF value in the rx header
 * given the assumption that the TSF passed in header is within 65ms
 * of the current tsf.
 *
 * 6       5       4       4       3       2       1
 * 3.......6.......8.......0.......2.......4.......6.......8......0
 * |<---------- tsf_h ----------->||<--- tsf_l -->||<-RxTSFTime ->|
 *
 * The RxTSFTime are the lowest 16 bits and provided by the ucode. The
 * tsf_l is filled in by brcms_b_recv, which is करोne earlier in the
 * receive call sequence after rx पूर्णांकerrupt. Only the higher 16 bits
 * are used. Finally, the tsf_h is पढ़ो from the tsf रेजिस्टर.
 */
अटल u64 brcms_c_recover_tsf64(काष्ठा brcms_c_info *wlc,
				 काष्ठा d11rxhdr *rxh)
अणु
	u32 tsf_h, tsf_l;
	u16 rx_tsf_0_15, rx_tsf_16_31;

	brcms_b_पढ़ो_tsf(wlc->hw, &tsf_l, &tsf_h);

	rx_tsf_16_31 = (u16)(tsf_l >> 16);
	rx_tsf_0_15 = rxh->RxTSFTime;

	/*
	 * a greater tsf समय indicates the low 16 bits of
	 * tsf_l wrapped, so decrement the high 16 bits.
	 */
	अगर ((u16)tsf_l < rx_tsf_0_15) अणु
		rx_tsf_16_31 -= 1;
		अगर (rx_tsf_16_31 == 0xffff)
			tsf_h -= 1;
	पूर्ण

	वापस ((u64)tsf_h << 32) | (((u32)rx_tsf_16_31 << 16) + rx_tsf_0_15);
पूर्ण

अटल व्योम
prep_mac80211_status(काष्ठा brcms_c_info *wlc, काष्ठा d11rxhdr *rxh,
		     काष्ठा sk_buff *p,
		     काष्ठा ieee80211_rx_status *rx_status)
अणु
	पूर्णांक channel;
	u32 rspec;
	अचिन्हित अक्षर *plcp;

	/* fill in TSF and flag its presence */
	rx_status->maस_समय = brcms_c_recover_tsf64(wlc, rxh);
	rx_status->flag |= RX_FLAG_MACTIME_START;

	channel = BRCMS_CHAN_CHANNEL(rxh->RxChan);

	rx_status->band =
		channel > 14 ? NL80211_BAND_5GHZ : NL80211_BAND_2GHZ;
	rx_status->freq =
		ieee80211_channel_to_frequency(channel, rx_status->band);

	rx_status->संकेत = wlc_phy_rssi_compute(wlc->hw->band->pi, rxh);

	/* noise */
	/* qual */
	rx_status->antenna =
		(rxh->PhyRxStatus_0 & PRXS0_RXANT_UPSUBBAND) ? 1 : 0;

	plcp = p->data;

	rspec = brcms_c_compute_rspec(rxh, plcp);
	अगर (is_mcs_rate(rspec)) अणु
		rx_status->rate_idx = rspec & RSPEC_RATE_MASK;
		rx_status->encoding = RX_ENC_HT;
		अगर (rspec_is40mhz(rspec))
			rx_status->bw = RATE_INFO_BW_40;
	पूर्ण अन्यथा अणु
		चयन (rspec2rate(rspec)) अणु
		हाल BRCM_RATE_1M:
			rx_status->rate_idx = 0;
			अवरोध;
		हाल BRCM_RATE_2M:
			rx_status->rate_idx = 1;
			अवरोध;
		हाल BRCM_RATE_5M5:
			rx_status->rate_idx = 2;
			अवरोध;
		हाल BRCM_RATE_11M:
			rx_status->rate_idx = 3;
			अवरोध;
		हाल BRCM_RATE_6M:
			rx_status->rate_idx = 4;
			अवरोध;
		हाल BRCM_RATE_9M:
			rx_status->rate_idx = 5;
			अवरोध;
		हाल BRCM_RATE_12M:
			rx_status->rate_idx = 6;
			अवरोध;
		हाल BRCM_RATE_18M:
			rx_status->rate_idx = 7;
			अवरोध;
		हाल BRCM_RATE_24M:
			rx_status->rate_idx = 8;
			अवरोध;
		हाल BRCM_RATE_36M:
			rx_status->rate_idx = 9;
			अवरोध;
		हाल BRCM_RATE_48M:
			rx_status->rate_idx = 10;
			अवरोध;
		हाल BRCM_RATE_54M:
			rx_status->rate_idx = 11;
			अवरोध;
		शेष:
			brcms_err(wlc->hw->d11core,
				  "%s: Unknown rate\n", __func__);
		पूर्ण

		/*
		 * For 5GHz, we should decrease the index as it is
		 * a subset of the 2.4G rates. See bitrates field
		 * of brcms_band_5GHz_nphy (in mac80211_अगर.c).
		 */
		अगर (rx_status->band == NL80211_BAND_5GHZ)
			rx_status->rate_idx -= BRCMS_LEGACY_5G_RATE_OFFSET;

		/* Determine लघु preamble and rate_idx */
		अगर (is_cck_rate(rspec)) अणु
			अगर (rxh->PhyRxStatus_0 & PRXS0_SHORTH)
				rx_status->enc_flags |= RX_ENC_FLAG_SHORTPRE;
		पूर्ण अन्यथा अगर (is_ofdm_rate(rspec)) अणु
			rx_status->enc_flags |= RX_ENC_FLAG_SHORTPRE;
		पूर्ण अन्यथा अणु
			brcms_err(wlc->hw->d11core, "%s: Unknown modulation\n",
				  __func__);
		पूर्ण
	पूर्ण

	अगर (plcp3_issgi(plcp[3]))
		rx_status->enc_flags |= RX_ENC_FLAG_SHORT_GI;

	अगर (rxh->RxStatus1 & RXS_DECERR) अणु
		rx_status->flag |= RX_FLAG_FAILED_PLCP_CRC;
		brcms_err(wlc->hw->d11core, "%s:  RX_FLAG_FAILED_PLCP_CRC\n",
			  __func__);
	पूर्ण
	अगर (rxh->RxStatus1 & RXS_FCSERR) अणु
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
		brcms_err(wlc->hw->d11core, "%s:  RX_FLAG_FAILED_FCS_CRC\n",
			  __func__);
	पूर्ण
पूर्ण

अटल व्योम
brcms_c_recvctl(काष्ठा brcms_c_info *wlc, काष्ठा d11rxhdr *rxh,
		काष्ठा sk_buff *p)
अणु
	पूर्णांक len_mpdu;
	काष्ठा ieee80211_rx_status rx_status;
	काष्ठा ieee80211_hdr *hdr;

	स_रखो(&rx_status, 0, माप(rx_status));
	prep_mac80211_status(wlc, rxh, p, &rx_status);

	/* mac header+body length, exclude CRC and plcp header */
	len_mpdu = p->len - D11_PHY_HDR_LEN - FCS_LEN;
	skb_pull(p, D11_PHY_HDR_LEN);
	__skb_trim(p, len_mpdu);

	/* unmute transmit */
	अगर (wlc->hw->suspended_fअगरos) अणु
		hdr = (काष्ठा ieee80211_hdr *)p->data;
		अगर (ieee80211_is_beacon(hdr->frame_control))
			brcms_b_mute(wlc->hw, false);
	पूर्ण

	स_नकल(IEEE80211_SKB_RXCB(p), &rx_status, माप(rx_status));
	ieee80211_rx_irqsafe(wlc->pub->ieee_hw, p);
पूर्ण

/* calculate frame duration क्रम Mixed-mode L-SIG spoofing, वापस
 * number of bytes goes in the length field
 *
 * Formula given by HT PHY Spec v 1.13
 *   len = 3(nsyms + nstream + 3) - 3
 */
u16
brcms_c_calc_lsig_len(काष्ठा brcms_c_info *wlc, u32 ratespec,
		      uपूर्णांक mac_len)
अणु
	uपूर्णांक nsyms, len = 0, kNdps;

	अगर (is_mcs_rate(ratespec)) अणु
		uपूर्णांक mcs = ratespec & RSPEC_RATE_MASK;
		पूर्णांक tot_streams = (mcs_2_txstreams(mcs) + 1) +
				  rspec_stc(ratespec);

		/*
		 * the payload duration calculation matches that
		 * of regular ofdm
		 */
		/* 1000Ndbps = kbps * 4 */
		kNdps = mcs_2_rate(mcs, rspec_is40mhz(ratespec),
				   rspec_issgi(ratespec)) * 4;

		अगर (rspec_stc(ratespec) == 0)
			nsyms =
			    CEIL((APHY_SERVICE_NBITS + 8 * mac_len +
				  APHY_TAIL_NBITS) * 1000, kNdps);
		अन्यथा
			/* STBC needs to have even number of symbols */
			nsyms =
			    2 *
			    CEIL((APHY_SERVICE_NBITS + 8 * mac_len +
				  APHY_TAIL_NBITS) * 1000, 2 * kNdps);

		/* (+3) account क्रम HT-SIG(2) and HT-STF(1) */
		nsyms += (tot_streams + 3);
		/*
		 * 3 bytes/symbol @ legacy 6Mbps rate
		 * (-3) excluding service bits and tail bits
		 */
		len = (3 * nsyms) - 3;
	पूर्ण

	वापस (u16) len;
पूर्ण

अटल व्योम
brcms_c_mod_prb_rsp_rate_table(काष्ठा brcms_c_info *wlc, uपूर्णांक frame_len)
अणु
	स्थिर काष्ठा brcms_c_rateset *rs_dflt;
	काष्ठा brcms_c_rateset rs;
	u8 rate;
	u16 entry_ptr;
	u8 plcp[D11_PHY_HDR_LEN];
	u16 dur, sअगरs;
	uपूर्णांक i;

	sअगरs = get_sअगरs(wlc->band);

	rs_dflt = brcms_c_rateset_get_hwrs(wlc);

	brcms_c_rateset_copy(rs_dflt, &rs);
	brcms_c_rateset_mcs_upd(&rs, wlc->stf->txstreams);

	/*
	 * walk the phy rate table and update MAC core SHM
	 * basic rate table entries
	 */
	क्रम (i = 0; i < rs.count; i++) अणु
		rate = rs.rates[i] & BRCMS_RATE_MASK;

		entry_ptr = brcms_b_rate_shm_offset(wlc->hw, rate);

		/* Calculate the Probe Response PLCP क्रम the given rate */
		brcms_c_compute_plcp(wlc, rate, frame_len, plcp);

		/*
		 * Calculate the duration of the Probe Response
		 * frame plus SIFS क्रम the MAC
		 */
		dur = (u16) brcms_c_calc_frame_समय(wlc, rate,
						BRCMS_LONG_PREAMBLE, frame_len);
		dur += sअगरs;

		/* Update the SHM Rate Table entry Probe Response values */
		brcms_b_ग_लिखो_shm(wlc->hw, entry_ptr + M_RT_PRS_PLCP_POS,
			      (u16) (plcp[0] + (plcp[1] << 8)));
		brcms_b_ग_लिखो_shm(wlc->hw, entry_ptr + M_RT_PRS_PLCP_POS + 2,
			      (u16) (plcp[2] + (plcp[3] << 8)));
		brcms_b_ग_लिखो_shm(wlc->hw, entry_ptr + M_RT_PRS_DUR_POS, dur);
	पूर्ण
पूर्ण

पूर्णांक brcms_c_get_header_len(व्योम)
अणु
	वापस TXOFF;
पूर्ण

अटल व्योम brcms_c_beacon_ग_लिखो(काष्ठा brcms_c_info *wlc,
				 काष्ठा sk_buff *beacon, u16 tim_offset,
				 u16 dtim_period, bool bcn0, bool bcn1)
अणु
	माप_प्रकार len;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	काष्ठा ieee80211_hw *ieee_hw = brcms_c_pub(wlc)->ieee_hw;

	/* Get tx_info */
	tx_info = IEEE80211_SKB_CB(beacon);

	len = min_t(माप_प्रकार, beacon->len, BCN_TMPL_LEN);
	wlc->bcn_rspec = ieee80211_get_tx_rate(ieee_hw, tx_info)->hw_value;

	brcms_c_compute_plcp(wlc, wlc->bcn_rspec,
			     len + FCS_LEN - D11_PHY_HDR_LEN, beacon->data);

	/* "Regular" and 16 MBSS but not क्रम 4 MBSS */
	/* Update the phytxctl क्रम the beacon based on the rspec */
	brcms_c_beacon_phytxctl_txant_upd(wlc, wlc->bcn_rspec);

	अगर (bcn0) अणु
		/* ग_लिखो the probe response पूर्णांकo the ढाँचा region */
		brcms_b_ग_लिखो_ढाँचा_ram(wlc_hw, T_BCN0_TPL_BASE,
					    (len + 3) & ~3, beacon->data);

		/* ग_लिखो beacon length to SCR */
		brcms_b_ग_लिखो_shm(wlc_hw, M_BCN0_FRM_BYTESZ, (u16) len);
	पूर्ण
	अगर (bcn1) अणु
		/* ग_लिखो the probe response पूर्णांकo the ढाँचा region */
		brcms_b_ग_लिखो_ढाँचा_ram(wlc_hw, T_BCN1_TPL_BASE,
					    (len + 3) & ~3, beacon->data);

		/* ग_लिखो beacon length to SCR */
		brcms_b_ग_लिखो_shm(wlc_hw, M_BCN1_FRM_BYTESZ, (u16) len);
	पूर्ण

	अगर (tim_offset != 0) अणु
		brcms_b_ग_लिखो_shm(wlc_hw, M_TIMBPOS_INBEACON,
				  tim_offset + D11B_PHY_HDR_LEN);
		brcms_b_ग_लिखो_shm(wlc_hw, M_DOT11_DTIMPERIOD, dtim_period);
	पूर्ण अन्यथा अणु
		brcms_b_ग_लिखो_shm(wlc_hw, M_TIMBPOS_INBEACON,
				  len + D11B_PHY_HDR_LEN);
		brcms_b_ग_लिखो_shm(wlc_hw, M_DOT11_DTIMPERIOD, 0);
	पूर्ण
पूर्ण

अटल व्योम brcms_c_update_beacon_hw(काष्ठा brcms_c_info *wlc,
				     काष्ठा sk_buff *beacon, u16 tim_offset,
				     u16 dtim_period)
अणु
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	काष्ठा bcma_device *core = wlc_hw->d11core;

	/* Hardware beaconing क्रम this config */
	u32 both_valid = MCMD_BCN0VLD | MCMD_BCN1VLD;

	/* Check अगर both ढाँचाs are in use, अगर so sched. an पूर्णांकerrupt
	 *      that will call back पूर्णांकo this routine
	 */
	अगर ((bcma_पढ़ो32(core, D11REGOFFS(maccommand)) & both_valid) == both_valid)
		/* clear any previous status */
		bcma_ग_लिखो32(core, D11REGOFFS(macपूर्णांकstatus), MI_BCNTPL);

	अगर (wlc->beacon_ढाँचा_virgin) अणु
		wlc->beacon_ढाँचा_virgin = false;
		brcms_c_beacon_ग_लिखो(wlc, beacon, tim_offset, dtim_period, true,
				     true);
		/* mark beacon0 valid */
		bcma_set32(core, D11REGOFFS(maccommand), MCMD_BCN0VLD);
		वापस;
	पूर्ण

	/* Check that after scheduling the पूर्णांकerrupt both of the
	 *      ढाँचाs are still busy. अगर not clear the पूर्णांक. & remask
	 */
	अगर ((bcma_पढ़ो32(core, D11REGOFFS(maccommand)) & both_valid) == both_valid) अणु
		wlc->defmacपूर्णांकmask |= MI_BCNTPL;
		वापस;
	पूर्ण

	अगर (!(bcma_पढ़ो32(core, D11REGOFFS(maccommand)) & MCMD_BCN0VLD)) अणु
		brcms_c_beacon_ग_लिखो(wlc, beacon, tim_offset, dtim_period, true,
				     false);
		/* mark beacon0 valid */
		bcma_set32(core, D11REGOFFS(maccommand), MCMD_BCN0VLD);
		वापस;
	पूर्ण
	अगर (!(bcma_पढ़ो32(core, D11REGOFFS(maccommand)) & MCMD_BCN1VLD)) अणु
		brcms_c_beacon_ग_लिखो(wlc, beacon, tim_offset, dtim_period,
				     false, true);
		/* mark beacon0 valid */
		bcma_set32(core, D11REGOFFS(maccommand), MCMD_BCN1VLD);
	पूर्ण
पूर्ण

/*
 * Update all beacons क्रम the प्रणाली.
 */
व्योम brcms_c_update_beacon(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा brcms_bss_cfg *bsscfg = wlc->bsscfg;

	अगर (wlc->pub->up && (bsscfg->type == BRCMS_TYPE_AP ||
			     bsscfg->type == BRCMS_TYPE_ADHOC)) अणु
		/* Clear the soft पूर्णांकmask */
		wlc->defmacपूर्णांकmask &= ~MI_BCNTPL;
		अगर (!wlc->beacon)
			वापस;
		brcms_c_update_beacon_hw(wlc, wlc->beacon,
					 wlc->beacon_tim_offset,
					 wlc->beacon_dtim_period);
	पूर्ण
पूर्ण

व्योम brcms_c_set_new_beacon(काष्ठा brcms_c_info *wlc, काष्ठा sk_buff *beacon,
			    u16 tim_offset, u16 dtim_period)
अणु
	अगर (!beacon)
		वापस;
	अगर (wlc->beacon)
		dev_kमुक्त_skb_any(wlc->beacon);
	wlc->beacon = beacon;

	/* add PLCP */
	skb_push(wlc->beacon, D11_PHY_HDR_LEN);
	wlc->beacon_tim_offset = tim_offset;
	wlc->beacon_dtim_period = dtim_period;
	brcms_c_update_beacon(wlc);
पूर्ण

व्योम brcms_c_set_new_probe_resp(काष्ठा brcms_c_info *wlc,
				काष्ठा sk_buff *probe_resp)
अणु
	अगर (!probe_resp)
		वापस;
	अगर (wlc->probe_resp)
		dev_kमुक्त_skb_any(wlc->probe_resp);
	wlc->probe_resp = probe_resp;

	/* add PLCP */
	skb_push(wlc->probe_resp, D11_PHY_HDR_LEN);
	brcms_c_update_probe_resp(wlc, false);
पूर्ण

व्योम brcms_c_enable_probe_resp(काष्ठा brcms_c_info *wlc, bool enable)
अणु
	/*
	 * prevent ucode from sending probe responses by setting the समयout
	 * to 1, it can not send it in that समय frame.
	 */
	wlc->prb_resp_समयout = enable ? BRCMS_PRB_RESP_TIMEOUT : 1;
	brcms_b_ग_लिखो_shm(wlc->hw, M_PRS_MAXTIME, wlc->prb_resp_समयout);
	/* TODO: अगर (enable) => also deactivate receiving of probe request */
पूर्ण

/* Write ssid पूर्णांकo shared memory */
अटल व्योम
brcms_c_shm_ssid_upd(काष्ठा brcms_c_info *wlc, काष्ठा brcms_bss_cfg *cfg)
अणु
	u8 *ssidptr = cfg->SSID;
	u16 base = M_SSID;
	u8 ssidbuf[IEEE80211_MAX_SSID_LEN];

	/* padding the ssid with zero and copy it पूर्णांकo shm */
	स_रखो(ssidbuf, 0, IEEE80211_MAX_SSID_LEN);
	स_नकल(ssidbuf, ssidptr, cfg->SSID_len);

	brcms_c_copyto_shm(wlc, base, ssidbuf, IEEE80211_MAX_SSID_LEN);
	brcms_b_ग_लिखो_shm(wlc->hw, M_SSIDLEN, (u16) cfg->SSID_len);
पूर्ण

अटल व्योम
brcms_c_bss_update_probe_resp(काष्ठा brcms_c_info *wlc,
			      काष्ठा brcms_bss_cfg *cfg,
			      काष्ठा sk_buff *probe_resp,
			      bool suspend)
अणु
	पूर्णांक len;

	len = min_t(माप_प्रकार, probe_resp->len, BCN_TMPL_LEN);

	अगर (suspend)
		brcms_c_suspend_mac_and_रुको(wlc);

	/* ग_लिखो the probe response पूर्णांकo the ढाँचा region */
	brcms_b_ग_लिखो_ढाँचा_ram(wlc->hw, T_PRS_TPL_BASE,
				    (len + 3) & ~3, probe_resp->data);

	/* ग_लिखो the length of the probe response frame (+PLCP/-FCS) */
	brcms_b_ग_लिखो_shm(wlc->hw, M_PRB_RESP_FRM_LEN, (u16) len);

	/* ग_लिखो the SSID and SSID length */
	brcms_c_shm_ssid_upd(wlc, cfg);

	/*
	 * Write PLCP headers and durations क्रम probe response frames
	 * at all rates. Use the actual frame length covered by the
	 * PLCP header क्रम the call to brcms_c_mod_prb_rsp_rate_table()
	 * by subtracting the PLCP len and adding the FCS.
	 */
	brcms_c_mod_prb_rsp_rate_table(wlc,
				      (u16)len + FCS_LEN - D11_PHY_HDR_LEN);

	अगर (suspend)
		brcms_c_enable_mac(wlc);
पूर्ण

व्योम brcms_c_update_probe_resp(काष्ठा brcms_c_info *wlc, bool suspend)
अणु
	काष्ठा brcms_bss_cfg *bsscfg = wlc->bsscfg;

	/* update AP or IBSS probe responses */
	अगर (wlc->pub->up && (bsscfg->type == BRCMS_TYPE_AP ||
			     bsscfg->type == BRCMS_TYPE_ADHOC)) अणु
		अगर (!wlc->probe_resp)
			वापस;
		brcms_c_bss_update_probe_resp(wlc, bsscfg, wlc->probe_resp,
					      suspend);
	पूर्ण
पूर्ण

पूर्णांक brcms_b_xmtfअगरo_sz_get(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक fअगरo,
			   uपूर्णांक *blocks)
अणु
	अगर (fअगरo >= NFIFO)
		वापस -EINVAL;

	*blocks = wlc_hw->xmtfअगरo_sz[fअगरo];

	वापस 0;
पूर्ण

व्योम
brcms_c_set_addrmatch(काष्ठा brcms_c_info *wlc, पूर्णांक match_reg_offset,
		  स्थिर u8 *addr)
अणु
	brcms_b_set_addrmatch(wlc->hw, match_reg_offset, addr);
	अगर (match_reg_offset == RCM_BSSID_OFFSET)
		स_नकल(wlc->bsscfg->BSSID, addr, ETH_ALEN);
पूर्ण

/*
 * Flag 'scan in progress' to withhold dynamic phy calibration
 */
व्योम brcms_c_scan_start(काष्ठा brcms_c_info *wlc)
अणु
	wlc_phy_hold_upd(wlc->band->pi, PHY_HOLD_FOR_SCAN, true);
पूर्ण

व्योम brcms_c_scan_stop(काष्ठा brcms_c_info *wlc)
अणु
	wlc_phy_hold_upd(wlc->band->pi, PHY_HOLD_FOR_SCAN, false);
पूर्ण

व्योम brcms_c_associate_upd(काष्ठा brcms_c_info *wlc, bool state)
अणु
	wlc->pub->associated = state;
पूर्ण

/*
 * When a remote STA/AP is हटाओd by Mac80211, or when it can no दीर्घer accept
 * AMPDU traffic, packets pending in hardware have to be invalidated so that
 * when later on hardware releases them, they can be handled appropriately.
 */
व्योम brcms_c_inval_dma_pkts(काष्ठा brcms_hardware *hw,
			       काष्ठा ieee80211_sta *sta,
			       व्योम (*dma_callback_fn))
अणु
	काष्ठा dma_pub *dmah;
	पूर्णांक i;
	क्रम (i = 0; i < NFIFO; i++) अणु
		dmah = hw->di[i];
		अगर (dmah != शून्य)
			dma_walk_packets(dmah, dma_callback_fn, sta);
	पूर्ण
पूर्ण

पूर्णांक brcms_c_get_curband(काष्ठा brcms_c_info *wlc)
अणु
	वापस wlc->band->bandunit;
पूर्ण

bool brcms_c_tx_flush_completed(काष्ठा brcms_c_info *wlc)
अणु
	पूर्णांक i;

	/* Kick DMA to send any pending AMPDU */
	क्रम (i = 0; i < ARRAY_SIZE(wlc->hw->di); i++)
		अगर (wlc->hw->di[i])
			dma_kick_tx(wlc->hw->di[i]);

	वापस !brcms_txpktpendtot(wlc);
पूर्ण

व्योम brcms_c_set_beacon_listen_पूर्णांकerval(काष्ठा brcms_c_info *wlc, u8 पूर्णांकerval)
अणु
	wlc->bcn_li_bcn = पूर्णांकerval;
	अगर (wlc->pub->up)
		brcms_c_bcn_li_upd(wlc);
पूर्ण

u64 brcms_c_tsf_get(काष्ठा brcms_c_info *wlc)
अणु
	u32 tsf_h, tsf_l;
	u64 tsf;

	brcms_b_पढ़ो_tsf(wlc->hw, &tsf_l, &tsf_h);

	tsf = tsf_h;
	tsf <<= 32;
	tsf |= tsf_l;

	वापस tsf;
पूर्ण

व्योम brcms_c_tsf_set(काष्ठा brcms_c_info *wlc, u64 tsf)
अणु
	u32 tsf_h, tsf_l;

	brcms_c_समय_lock(wlc);

	tsf_l = tsf;
	tsf_h = (tsf >> 32);

	/* पढ़ो the tsf समयr low, then high to get an atomic पढ़ो */
	bcma_ग_लिखो32(wlc->hw->d11core, D11REGOFFS(tsf_समयrlow), tsf_l);
	bcma_ग_लिखो32(wlc->hw->d11core, D11REGOFFS(tsf_समयrhigh), tsf_h);

	brcms_c_समय_unlock(wlc);
पूर्ण

पूर्णांक brcms_c_set_tx_घातer(काष्ठा brcms_c_info *wlc, पूर्णांक txpwr)
अणु
	uपूर्णांक qdbm;

	/* Remove override bit and clip to max qdbm value */
	qdbm = min_t(uपूर्णांक, txpwr * BRCMS_TXPWR_DB_FACTOR, 0xff);
	वापस wlc_phy_txघातer_set(wlc->band->pi, qdbm, false);
पूर्ण

पूर्णांक brcms_c_get_tx_घातer(काष्ठा brcms_c_info *wlc)
अणु
	uपूर्णांक qdbm;
	bool override;

	wlc_phy_txघातer_get(wlc->band->pi, &qdbm, &override);

	/* Return qdbm units */
	वापस (पूर्णांक)(qdbm / BRCMS_TXPWR_DB_FACTOR);
पूर्ण

/* Process received frames */
/*
 * Return true अगर more frames need to be processed. false otherwise.
 * Param 'bound' indicates max. # frames to process beक्रमe अवरोध out.
 */
अटल व्योम brcms_c_recv(काष्ठा brcms_c_info *wlc, काष्ठा sk_buff *p)
अणु
	काष्ठा d11rxhdr *rxh;
	काष्ठा ieee80211_hdr *h;
	uपूर्णांक len;
	bool is_amsdu;

	/* frame starts with rxhdr */
	rxh = (काष्ठा d11rxhdr *) (p->data);

	/* strip off rxhdr */
	skb_pull(p, BRCMS_HWRXOFF);

	/* MAC inserts 2 pad bytes क्रम a4 headers or QoS or A-MSDU subframes */
	अगर (rxh->RxStatus1 & RXS_PBPRES) अणु
		अगर (p->len < 2) अणु
			brcms_err(wlc->hw->d11core,
				  "wl%d: recv: rcvd runt of len %d\n",
				  wlc->pub->unit, p->len);
			जाओ toss;
		पूर्ण
		skb_pull(p, 2);
	पूर्ण

	h = (काष्ठा ieee80211_hdr *)(p->data + D11_PHY_HDR_LEN);
	len = p->len;

	अगर (rxh->RxStatus1 & RXS_FCSERR) अणु
		अगर (!(wlc->filter_flags & FIF_FCSFAIL))
			जाओ toss;
	पूर्ण

	/* check received pkt has at least frame control field */
	अगर (len < D11_PHY_HDR_LEN + माप(h->frame_control))
		जाओ toss;

	/* not supporting A-MSDU */
	is_amsdu = rxh->RxStatus2 & RXS_AMSDU_MASK;
	अगर (is_amsdu)
		जाओ toss;

	brcms_c_recvctl(wlc, rxh, p);
	वापस;

 toss:
	brcmu_pkt_buf_मुक्त_skb(p);
पूर्ण

/* Process received frames */
/*
 * Return true अगर more frames need to be processed. false otherwise.
 * Param 'bound' indicates max. # frames to process beक्रमe अवरोध out.
 */
अटल bool
brcms_b_recv(काष्ठा brcms_hardware *wlc_hw, uपूर्णांक fअगरo, bool bound)
अणु
	काष्ठा sk_buff *p;
	काष्ठा sk_buff *next = शून्य;
	काष्ठा sk_buff_head recv_frames;

	uपूर्णांक n = 0;
	uपूर्णांक bound_limit = bound ? RXBND : -1;
	bool morepending = false;

	skb_queue_head_init(&recv_frames);

	/* gather received frames */
	करो अणु
		/* !give others some समय to run! */
		अगर (n >= bound_limit)
			अवरोध;

		morepending = dma_rx(wlc_hw->di[fअगरo], &recv_frames);
		n++;
	पूर्ण जबतक (morepending);

	/* post more rbufs */
	dma_rxfill(wlc_hw->di[fअगरo]);

	/* process each frame */
	skb_queue_walk_safe(&recv_frames, p, next) अणु
		काष्ठा d11rxhdr_le *rxh_le;
		काष्ठा d11rxhdr *rxh;

		skb_unlink(p, &recv_frames);
		rxh_le = (काष्ठा d11rxhdr_le *)p->data;
		rxh = (काष्ठा d11rxhdr *)p->data;

		/* fixup rx header endianness */
		rxh->RxFrameSize = le16_to_cpu(rxh_le->RxFrameSize);
		rxh->PhyRxStatus_0 = le16_to_cpu(rxh_le->PhyRxStatus_0);
		rxh->PhyRxStatus_1 = le16_to_cpu(rxh_le->PhyRxStatus_1);
		rxh->PhyRxStatus_2 = le16_to_cpu(rxh_le->PhyRxStatus_2);
		rxh->PhyRxStatus_3 = le16_to_cpu(rxh_le->PhyRxStatus_3);
		rxh->PhyRxStatus_4 = le16_to_cpu(rxh_le->PhyRxStatus_4);
		rxh->PhyRxStatus_5 = le16_to_cpu(rxh_le->PhyRxStatus_5);
		rxh->RxStatus1 = le16_to_cpu(rxh_le->RxStatus1);
		rxh->RxStatus2 = le16_to_cpu(rxh_le->RxStatus2);
		rxh->RxTSFTime = le16_to_cpu(rxh_le->RxTSFTime);
		rxh->RxChan = le16_to_cpu(rxh_le->RxChan);

		brcms_c_recv(wlc_hw->wlc, p);
	पूर्ण

	वापस morepending;
पूर्ण

/* second-level पूर्णांकerrupt processing
 *   Return true अगर another dpc needs to be re-scheduled. false otherwise.
 *   Param 'bounded' indicates अगर applicable loops should be bounded.
 */
bool brcms_c_dpc(काष्ठा brcms_c_info *wlc, bool bounded)
अणु
	u32 macपूर्णांकstatus;
	काष्ठा brcms_hardware *wlc_hw = wlc->hw;
	काष्ठा bcma_device *core = wlc_hw->d11core;

	अगर (brcms_deviceहटाओd(wlc)) अणु
		brcms_err(core, "wl%d: %s: dead chip\n", wlc_hw->unit,
			  __func__);
		brcms_करोwn(wlc->wl);
		वापस false;
	पूर्ण

	/* grab and clear the saved software पूर्णांकstatus bits */
	macपूर्णांकstatus = wlc->macपूर्णांकstatus;
	wlc->macपूर्णांकstatus = 0;

	brcms_dbg_पूर्णांक(core, "wl%d: macintstatus 0x%x\n",
		      wlc_hw->unit, macपूर्णांकstatus);

	WARN_ON(macपूर्णांकstatus & MI_PRQ); /* PRQ Interrupt in non-MBSS */

	/* tx status */
	अगर (macपूर्णांकstatus & MI_TFS) अणु
		bool fatal;
		अगर (brcms_b_txstatus(wlc->hw, bounded, &fatal))
			wlc->macपूर्णांकstatus |= MI_TFS;
		अगर (fatal) अणु
			brcms_err(core, "MI_TFS: fatal\n");
			जाओ fatal;
		पूर्ण
	पूर्ण

	अगर (macपूर्णांकstatus & (MI_TBTT | MI_DTIM_TBTT))
		brcms_c_tbtt(wlc);

	/* ATIM winकरोw end */
	अगर (macपूर्णांकstatus & MI_ATIMWINEND) अणु
		brcms_dbg_info(core, "end of ATIM window\n");
		bcma_set32(core, D11REGOFFS(maccommand), wlc->qvalid);
		wlc->qvalid = 0;
	पूर्ण

	/*
	 * received data or control frame, MI_DMAINT is
	 * indication of RX_FIFO पूर्णांकerrupt
	 */
	अगर (macपूर्णांकstatus & MI_DMAINT)
		अगर (brcms_b_recv(wlc_hw, RX_FIFO, bounded))
			wlc->macपूर्णांकstatus |= MI_DMAINT;

	/* noise sample collected */
	अगर (macपूर्णांकstatus & MI_BG_NOISE)
		wlc_phy_noise_sample_पूर्णांकr(wlc_hw->band->pi);

	अगर (macपूर्णांकstatus & MI_GP0) अणु
		brcms_err(core, "wl%d: PSM microcode watchdog fired at %d "
			  "(seconds). Resetting.\n", wlc_hw->unit, wlc_hw->now);

		prपूर्णांकk_once("%s : PSM Watchdog, chipid 0x%x, chiprev 0x%x\n",
			    __func__, ai_get_chip_id(wlc_hw->sih),
			    ai_get_chiprev(wlc_hw->sih));
		brcms_fatal_error(wlc_hw->wlc->wl);
	पूर्ण

	/* gpसमयr समयout */
	अगर (macपूर्णांकstatus & MI_TO)
		bcma_ग_लिखो32(core, D11REGOFFS(gpसमयr), 0);

	अगर (macपूर्णांकstatus & MI_RFDISABLE) अणु
		brcms_dbg_info(core, "wl%d: BMAC Detected a change on the"
			       " RF Disable Input\n", wlc_hw->unit);
		brcms_rfसमाप्त_set_hw_state(wlc->wl);
	पूर्ण

	/* BCN ढाँचा is available */
	अगर (macपूर्णांकstatus & MI_BCNTPL)
		brcms_c_update_beacon(wlc);

	/* it isn't करोne and needs to be resched अगर macपूर्णांकstatus is non-zero */
	वापस wlc->macपूर्णांकstatus != 0;

 fatal:
	brcms_fatal_error(wlc_hw->wlc->wl);
	वापस wlc->macपूर्णांकstatus != 0;
पूर्ण

व्योम brcms_c_init(काष्ठा brcms_c_info *wlc, bool mute_tx)
अणु
	काष्ठा bcma_device *core = wlc->hw->d11core;
	काष्ठा ieee80211_channel *ch = wlc->pub->ieee_hw->conf.chandef.chan;
	u16 chanspec;

	brcms_dbg_info(core, "wl%d\n", wlc->pub->unit);

	chanspec = ch20mhz_chspec(ch->hw_value);

	brcms_b_init(wlc->hw, chanspec);

	/* update beacon listen पूर्णांकerval */
	brcms_c_bcn_li_upd(wlc);

	/* ग_लिखो ethernet address to core */
	brcms_c_set_mac(wlc->bsscfg);
	brcms_c_set_bssid(wlc->bsscfg);

	/* Update tsf_cfprep अगर associated and up */
	अगर (wlc->pub->associated && wlc->pub->up) अणु
		u32 bi;

		/* get beacon period and convert to uS */
		bi = wlc->bsscfg->current_bss->beacon_period << 10;
		/*
		 * update since init path would reset
		 * to शेष value
		 */
		bcma_ग_लिखो32(core, D11REGOFFS(tsf_cfprep),
			     bi << CFPREP_CBI_SHIFT);

		/* Update maccontrol PM related bits */
		brcms_c_set_ps_ctrl(wlc);
	पूर्ण

	brcms_c_bandinit_ordered(wlc, chanspec);

	/* init probe response समयout */
	brcms_b_ग_लिखो_shm(wlc->hw, M_PRS_MAXTIME, wlc->prb_resp_समयout);

	/* init max burst txop (framebursting) */
	brcms_b_ग_लिखो_shm(wlc->hw, M_MBURST_TXOP,
		      (wlc->
		       _rअगरs ? (EDCF_AC_VO_TXOP_AP << 5) : MAXFRAMEBURST_TXOP));

	/* initialize maximum allowed duty cycle */
	brcms_c_duty_cycle_set(wlc, wlc->tx_duty_cycle_ofdm, true, true);
	brcms_c_duty_cycle_set(wlc, wlc->tx_duty_cycle_cck, false, true);

	/*
	 * Update some shared memory locations related to
	 * max AMPDU size allowed to received
	 */
	brcms_c_ampdu_shm_upd(wlc->ampdu);

	/* band-specअगरic inits */
	brcms_c_bsinit(wlc);

	/* Enable EDCF mode (जबतक the MAC is suspended) */
	bcma_set16(core, D11REGOFFS(अगरs_ctl), IFS_USEEDCF);
	brcms_c_edcf_setparams(wlc, false);

	/* पढ़ो the ucode version अगर we have not yet करोne so */
	अगर (wlc->ucode_rev == 0) अणु
		u16 rev;
		u16 patch;

		rev = brcms_b_पढ़ो_shm(wlc->hw, M_BOM_REV_MAJOR);
		patch = brcms_b_पढ़ो_shm(wlc->hw, M_BOM_REV_MINOR);
		wlc->ucode_rev = (rev << NBITS(u16)) | patch;
		snम_लिखो(wlc->wiphy->fw_version,
			 माप(wlc->wiphy->fw_version), "%u.%u", rev, patch);
	पूर्ण

	/* ..now really unleash hell (allow the MAC out of suspend) */
	brcms_c_enable_mac(wlc);

	/* suspend the tx fअगरos and mute the phy क्रम preism cac समय */
	अगर (mute_tx)
		brcms_b_mute(wlc->hw, true);

	/* enable the RF Disable Delay समयr */
	bcma_ग_लिखो32(core, D11REGOFFS(rfdisabledly), RFDISABLE_DEFAULT);

	/*
	 * Initialize WME parameters; अगर they haven't been set by some other
	 * mechanism (IOVar, etc) then पढ़ो them from the hardware.
	 */
	अगर (GFIELD(wlc->wme_retries[0], EDCF_SHORT) == 0) अणु
		/* Uninitialized; पढ़ो from HW */
		पूर्णांक ac;

		क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			wlc->wme_retries[ac] =
			    brcms_b_पढ़ो_shm(wlc->hw, M_AC_TXLMT_ADDR(ac));
	पूर्ण
पूर्ण

/*
 * The common driver entry routine. Error codes should be unique
 */
काष्ठा brcms_c_info *
brcms_c_attach(काष्ठा brcms_info *wl, काष्ठा bcma_device *core, uपूर्णांक unit,
	       bool piomode, uपूर्णांक *perr)
अणु
	काष्ठा brcms_c_info *wlc;
	uपूर्णांक err = 0;
	uपूर्णांक i, j;
	काष्ठा brcms_pub *pub;

	/* allocate काष्ठा brcms_c_info state and its subकाष्ठाures */
	wlc = brcms_c_attach_दो_स्मृति(unit, &err, 0);
	अगर (wlc == शून्य)
		जाओ fail;
	wlc->wiphy = wl->wiphy;
	pub = wlc->pub;

#अगर defined(DEBUG)
	wlc_info_dbg = wlc;
#पूर्ण_अगर

	wlc->band = wlc->bandstate[0];
	wlc->core = wlc->corestate;
	wlc->wl = wl;
	pub->unit = unit;
	pub->_piomode = piomode;
	wlc->bandinit_pending = false;
	wlc->beacon_ढाँचा_virgin = true;

	/* populate काष्ठा brcms_c_info with शेष values  */
	brcms_c_info_init(wlc, unit);

	/* update sta/ap related parameters */
	brcms_c_ap_upd(wlc);

	/*
	 * low level attach steps(all hw accesses go
	 * inside, no more in rest of the attach)
	 */
	err = brcms_b_attach(wlc, core, unit, piomode);
	अगर (err)
		जाओ fail;

	brcms_c_protection_upd(wlc, BRCMS_PROT_N_PAM_OVR, OFF);

	pub->phy_11ncapable = BRCMS_PHY_11N_CAP(wlc->band);

	/* disable allowed duty cycle */
	wlc->tx_duty_cycle_ofdm = 0;
	wlc->tx_duty_cycle_cck = 0;

	brcms_c_stf_phy_chain_calc(wlc);

	/* txchain 1: txant 0, txchain 2: txant 1 */
	अगर (BRCMS_ISNPHY(wlc->band) && (wlc->stf->txstreams == 1))
		wlc->stf->txant = wlc->stf->hw_txchain - 1;

	/* push to BMAC driver */
	wlc_phy_stf_chain_init(wlc->band->pi, wlc->stf->hw_txchain,
			       wlc->stf->hw_rxchain);

	/* pull up some info resulting from the low attach */
	क्रम (i = 0; i < NFIFO; i++)
		wlc->core->txavail[i] = wlc->hw->txavail[i];

	स_नकल(&wlc->perm_etheraddr, &wlc->hw->etheraddr, ETH_ALEN);
	स_नकल(&pub->cur_etheraddr, &wlc->hw->etheraddr, ETH_ALEN);

	क्रम (j = 0; j < wlc->pub->_nbands; j++) अणु
		wlc->band = wlc->bandstate[j];

		अगर (!brcms_c_attach_stf_ant_init(wlc)) अणु
			err = 24;
			जाओ fail;
		पूर्ण

		/* शेष contention winकरोws size limits */
		wlc->band->CWmin = APHY_CWMIN;
		wlc->band->CWmax = PHY_CWMAX;

		/* init gmode value */
		अगर (wlc->band->bandtype == BRCM_BAND_2G) अणु
			wlc->band->gmode = GMODE_AUTO;
			brcms_c_protection_upd(wlc, BRCMS_PROT_G_USER,
					   wlc->band->gmode);
		पूर्ण

		/* init _n_enab supported mode */
		अगर (BRCMS_PHY_11N_CAP(wlc->band)) अणु
			pub->_n_enab = SUPPORT_11N;
			brcms_c_protection_upd(wlc, BRCMS_PROT_N_USER,
						   ((pub->_n_enab ==
						     SUPPORT_11N) ? WL_11N_2x2 :
						    WL_11N_3x3));
		पूर्ण

		/* init per-band शेष rateset, depend on band->gmode */
		brcms_शेष_rateset(wlc, &wlc->band->defrateset);

		/* fill in hw_rateset */
		brcms_c_rateset_filter(&wlc->band->defrateset,
				   &wlc->band->hw_rateset, false,
				   BRCMS_RATES_CCK_OFDM, BRCMS_RATE_MASK,
				   (bool) (wlc->pub->_n_enab & SUPPORT_11N));
	पूर्ण

	/*
	 * update antenna config due to
	 * wlc->stf->txant/txchain/ant_rx_ovr change
	 */
	brcms_c_stf_phy_txant_upd(wlc);

	/* attach each modules */
	err = brcms_c_attach_module(wlc);
	अगर (err != 0)
		जाओ fail;

	अगर (!brcms_c_समयrs_init(wlc, unit)) अणु
		wiphy_err(wl->wiphy, "wl%d: %s: init_timer failed\n", unit,
			  __func__);
		err = 32;
		जाओ fail;
	पूर्ण

	/* depend on rateset, gmode */
	wlc->cmi = brcms_c_channel_mgr_attach(wlc);
	अगर (!wlc->cmi) अणु
		wiphy_err(wl->wiphy, "wl%d: %s: channel_mgr_attach failed"
			  "\n", unit, __func__);
		err = 33;
		जाओ fail;
	पूर्ण

	/* init शेष when all parameters are पढ़ोy, i.e. ->rateset */
	brcms_c_bss_शेष_init(wlc);

	/*
	 * Complete the wlc शेष state initializations..
	 */

	wlc->bsscfg->wlc = wlc;

	wlc->mimoft = FT_HT;
	wlc->mimo_40txbw = AUTO;
	wlc->ofdm_40txbw = AUTO;
	wlc->cck_40txbw = AUTO;
	brcms_c_update_mimo_band_bwcap(wlc, BRCMS_N_BW_20IN2G_40IN5G);

	/* Set शेष values of SGI */
	अगर (BRCMS_SGI_CAP_PHY(wlc)) अणु
		brcms_c_ht_update_sgi_rx(wlc, (BRCMS_N_SGI_20 |
					       BRCMS_N_SGI_40));
	पूर्ण अन्यथा अगर (BRCMS_ISSSLPNPHY(wlc->band)) अणु
		brcms_c_ht_update_sgi_rx(wlc, (BRCMS_N_SGI_20 |
					       BRCMS_N_SGI_40));
	पूर्ण अन्यथा अणु
		brcms_c_ht_update_sgi_rx(wlc, 0);
	पूर्ण

	brcms_b_antsel_set(wlc->hw, wlc->asi->antsel_avail);

	अगर (perr)
		*perr = 0;

	वापस wlc;

 fail:
	wiphy_err(wl->wiphy, "wl%d: %s: failed with err %d\n",
		  unit, __func__, err);
	अगर (wlc)
		brcms_c_detach(wlc);

	अगर (perr)
		*perr = err;
	वापस शून्य;
पूर्ण
