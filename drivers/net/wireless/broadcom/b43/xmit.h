<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_XMIT_H_
#घोषणा B43_XMIT_H_

#समावेश "main.h"
#समावेश <net/mac80211.h>


#घोषणा _b43_declare_plcp_hdr(size) \
	काष्ठा b43_plcp_hdr##size अणु		\
		जोड़ अणु				\
			__le32 data;		\
			__u8 raw[size];		\
		पूर्ण __packed;	\
	पूर्ण __packed

/* काष्ठा b43_plcp_hdr4 */
_b43_declare_plcp_hdr(4);
/* काष्ठा b43_plcp_hdr6 */
_b43_declare_plcp_hdr(6);

#अघोषित _b43_declare_plcp_hdr

/* TX header क्रम v4 firmware */
काष्ठा b43_txhdr अणु
	__le32 mac_ctl;			/* MAC TX control */
	__le16 mac_frame_ctl;		/* Copy of the FrameControl field */
	__le16 tx_fes_समय_norm;	/* TX FES Time Normal */
	__le16 phy_ctl;			/* PHY TX control */
	__le16 phy_ctl1;		/* PHY TX control word 1 */
	__le16 phy_ctl1_fb;		/* PHY TX control word 1 क्रम fallback rates */
	__le16 phy_ctl1_rts;		/* PHY TX control word 1 RTS */
	__le16 phy_ctl1_rts_fb;		/* PHY TX control word 1 RTS क्रम fallback rates */
	__u8 phy_rate;			/* PHY rate */
	__u8 phy_rate_rts;		/* PHY rate क्रम RTS/CTS */
	__u8 extra_ft;			/* Extra Frame Types */
	__u8 chan_radio_code;		/* Channel Radio Code */
	__u8 iv[16];			/* Encryption IV */
	__u8 tx_receiver[6];		/* TX Frame Receiver address */
	__le16 tx_fes_समय_fb;		/* TX FES Time Fallback */
	काष्ठा b43_plcp_hdr6 rts_plcp_fb; /* RTS fallback PLCP header */
	__le16 rts_dur_fb;		/* RTS fallback duration */
	काष्ठा b43_plcp_hdr6 plcp_fb;	/* Fallback PLCP header */
	__le16 dur_fb;			/* Fallback duration */
	__le16 mimo_modelen;		/* MIMO mode length */
	__le16 mimo_ratelen_fb;		/* MIMO fallback rate length */
	__le32 समयout;			/* Timeout */

	जोड़ अणु
		/* Tested with 598.314, 644.1001 and 666.2 */
		काष्ठा अणु
			__le16 mimo_antenna;            /* MIMO antenna select */
			__le16 preload_size;            /* Preload size */
			PAD_BYTES(2);
			__le16 cookie;                  /* TX frame cookie */
			__le16 tx_status;               /* TX status */
			__le16 max_n_mpdus;
			__le16 max_a_bytes_mrt;
			__le16 max_a_bytes_fbr;
			__le16 min_m_bytes;
			काष्ठा b43_plcp_hdr6 rts_plcp;  /* RTS PLCP header */
			__u8 rts_frame[16];             /* The RTS frame (अगर used) */
			PAD_BYTES(2);
			काष्ठा b43_plcp_hdr6 plcp;      /* Main PLCP header */
		पूर्ण क्रमmat_598 __packed;

		/* Tested with 410.2160, 478.104 and 508.* */
		काष्ठा अणु
			__le16 mimo_antenna;		/* MIMO antenna select */
			__le16 preload_size;		/* Preload size */
			PAD_BYTES(2);
			__le16 cookie;			/* TX frame cookie */
			__le16 tx_status;		/* TX status */
			काष्ठा b43_plcp_hdr6 rts_plcp;	/* RTS PLCP header */
			__u8 rts_frame[16];		/* The RTS frame (अगर used) */
			PAD_BYTES(2);
			काष्ठा b43_plcp_hdr6 plcp;	/* Main PLCP header */
		पूर्ण क्रमmat_410 __packed;

		/* Tested with 351.126 */
		काष्ठा अणु
			PAD_BYTES(2);
			__le16 cookie;			/* TX frame cookie */
			__le16 tx_status;		/* TX status */
			काष्ठा b43_plcp_hdr6 rts_plcp;	/* RTS PLCP header */
			__u8 rts_frame[16];		/* The RTS frame (अगर used) */
			PAD_BYTES(2);
			काष्ठा b43_plcp_hdr6 plcp;	/* Main PLCP header */
		पूर्ण क्रमmat_351 __packed;

	पूर्ण __packed;
पूर्ण __packed;

काष्ठा b43_tx_legacy_rate_phy_ctl_entry अणु
	u8 bitrate;
	u16 coding_rate;
	u16 modulation;
पूर्ण;

/* MAC TX control */
#घोषणा B43_TXH_MAC_RTS_FB_SHORTPRMBL	0x80000000 /* RTS fallback preamble */
#घोषणा B43_TXH_MAC_RTS_SHORTPRMBL	0x40000000 /* RTS मुख्य rate preamble */
#घोषणा B43_TXH_MAC_FB_SHORTPRMBL	0x20000000 /* Main fallback preamble */
#घोषणा B43_TXH_MAC_USEFBR		0x10000000 /* Use fallback rate क्रम this AMPDU */
#घोषणा B43_TXH_MAC_KEYIDX		0x0FF00000 /* Security key index */
#घोषणा B43_TXH_MAC_KEYIDX_SHIFT	20
#घोषणा B43_TXH_MAC_ALT_TXPWR		0x00080000 /* Use alternate txpwr defined at loc. M_ALT_TXPWR_IDX */
#घोषणा B43_TXH_MAC_KEYALG		0x00070000 /* Security key algorithm */
#घोषणा B43_TXH_MAC_KEYALG_SHIFT	16
#घोषणा B43_TXH_MAC_AMIC		0x00008000 /* AMIC */
#घोषणा B43_TXH_MAC_RIFS		0x00004000 /* Use RIFS */
#घोषणा B43_TXH_MAC_LIFETIME		0x00002000 /* Lअगरeसमय */
#घोषणा B43_TXH_MAC_FRAMEBURST		0x00001000 /* Frameburst */
#घोषणा B43_TXH_MAC_SENDCTS		0x00000800 /* Send CTS-to-self */
#घोषणा B43_TXH_MAC_AMPDU		0x00000600 /* AMPDU status */
#घोषणा  B43_TXH_MAC_AMPDU_MPDU		0x00000000 /* Regular MPDU, not an AMPDU */
#घोषणा  B43_TXH_MAC_AMPDU_FIRST	0x00000200 /* First MPDU or AMPDU */
#घोषणा  B43_TXH_MAC_AMPDU_INTER	0x00000400 /* Intermediate MPDU or AMPDU */
#घोषणा  B43_TXH_MAC_AMPDU_LAST		0x00000600 /* Last (or only) MPDU of AMPDU */
#घोषणा B43_TXH_MAC_40MHZ		0x00000100 /* Use 40 MHz bandwidth */
#घोषणा B43_TXH_MAC_5GHZ		0x00000080 /* 5GHz band */
#घोषणा B43_TXH_MAC_DFCS		0x00000040 /* DFCS */
#घोषणा B43_TXH_MAC_IGNPMQ		0x00000020 /* Ignore PMQ */
#घोषणा B43_TXH_MAC_HWSEQ		0x00000010 /* Use Hardware Sequence Number */
#घोषणा B43_TXH_MAC_STMSDU		0x00000008 /* Start MSDU */
#घोषणा B43_TXH_MAC_SENDRTS		0x00000004 /* Send RTS */
#घोषणा B43_TXH_MAC_LONGFRAME		0x00000002 /* Long frame */
#घोषणा B43_TXH_MAC_ACK			0x00000001 /* Immediate ACK */

/* Extra Frame Types */
#घोषणा B43_TXH_EFT_FB			0x03 /* Data frame fallback encoding */
#घोषणा  B43_TXH_EFT_FB_CCK		0x00 /* CCK */
#घोषणा  B43_TXH_EFT_FB_OFDM		0x01 /* OFDM */
#घोषणा  B43_TXH_EFT_FB_HT		0x02 /* HT */
#घोषणा  B43_TXH_EFT_FB_VHT		0x03 /* VHT */
#घोषणा B43_TXH_EFT_RTS			0x0C /* RTS/CTS encoding */
#घोषणा  B43_TXH_EFT_RTS_CCK		0x00 /* CCK */
#घोषणा  B43_TXH_EFT_RTS_OFDM		0x04 /* OFDM */
#घोषणा  B43_TXH_EFT_RTS_HT		0x08 /* HT */
#घोषणा  B43_TXH_EFT_RTS_VHT		0x0C /* VHT */
#घोषणा B43_TXH_EFT_RTSFB		0x30 /* RTS/CTS fallback encoding */
#घोषणा  B43_TXH_EFT_RTSFB_CCK		0x00 /* CCK */
#घोषणा  B43_TXH_EFT_RTSFB_OFDM		0x10 /* OFDM */
#घोषणा  B43_TXH_EFT_RTSFB_HT		0x20 /* HT */
#घोषणा  B43_TXH_EFT_RTSFB_VHT		0x30 /* VHT */

/* PHY TX control word */
#घोषणा B43_TXH_PHY_ENC			0x0003 /* Data frame encoding */
#घोषणा  B43_TXH_PHY_ENC_CCK		0x0000 /* CCK */
#घोषणा  B43_TXH_PHY_ENC_OFDM		0x0001 /* OFDM */
#घोषणा  B43_TXH_PHY_ENC_HT		0x0002 /* HT */
#घोषणा  B43_TXH_PHY_ENC_VHT		0x0003 /* VHT */
#घोषणा B43_TXH_PHY_SHORTPRMBL		0x0010 /* Use लघु preamble */
#घोषणा B43_TXH_PHY_ANT			0x03C0 /* Antenna selection */
#घोषणा  B43_TXH_PHY_ANT0		0x0000 /* Use antenna 0 */
#घोषणा  B43_TXH_PHY_ANT1		0x0040 /* Use antenna 1 */
#घोषणा  B43_TXH_PHY_ANT01AUTO		0x00C0 /* Use antenna 0/1 स्वतः */
#घोषणा  B43_TXH_PHY_ANT2		0x0100 /* Use antenna 2 */
#घोषणा  B43_TXH_PHY_ANT3		0x0200 /* Use antenna 3 */
#घोषणा B43_TXH_PHY_TXPWR		0xFC00 /* TX घातer */
#घोषणा B43_TXH_PHY_TXPWR_SHIFT		10

/* PHY TX control word 1 */
#घोषणा B43_TXH_PHY1_BW			0x0007 /* Bandwidth */
#घोषणा  B43_TXH_PHY1_BW_10		0x0000 /* 10 MHz */
#घोषणा  B43_TXH_PHY1_BW_10U		0x0001 /* 10 MHz upper */
#घोषणा  B43_TXH_PHY1_BW_20		0x0002 /* 20 MHz */
#घोषणा  B43_TXH_PHY1_BW_20U		0x0003 /* 20 MHz upper */
#घोषणा  B43_TXH_PHY1_BW_40		0x0004 /* 40 MHz */
#घोषणा  B43_TXH_PHY1_BW_40DUP		0x0005 /* 40 MHz duplicate */
#घोषणा B43_TXH_PHY1_MODE		0x0038 /* Mode */
#घोषणा  B43_TXH_PHY1_MODE_SISO		0x0000 /* SISO */
#घोषणा  B43_TXH_PHY1_MODE_CDD		0x0008 /* CDD */
#घोषणा  B43_TXH_PHY1_MODE_STBC		0x0010 /* STBC */
#घोषणा  B43_TXH_PHY1_MODE_SDM		0x0018 /* SDM */
#घोषणा B43_TXH_PHY1_CRATE		0x0700 /* Coding rate */
#घोषणा  B43_TXH_PHY1_CRATE_1_2		0x0000 /* 1/2 */
#घोषणा  B43_TXH_PHY1_CRATE_2_3		0x0100 /* 2/3 */
#घोषणा  B43_TXH_PHY1_CRATE_3_4		0x0200 /* 3/4 */
#घोषणा  B43_TXH_PHY1_CRATE_4_5		0x0300 /* 4/5 */
#घोषणा  B43_TXH_PHY1_CRATE_5_6		0x0400 /* 5/6 */
#घोषणा  B43_TXH_PHY1_CRATE_7_8		0x0600 /* 7/8 */
#घोषणा B43_TXH_PHY1_MODUL		0x3800 /* Modulation scheme */
#घोषणा  B43_TXH_PHY1_MODUL_BPSK	0x0000 /* BPSK */
#घोषणा  B43_TXH_PHY1_MODUL_QPSK	0x0800 /* QPSK */
#घोषणा  B43_TXH_PHY1_MODUL_QAM16	0x1000 /* QAM16 */
#घोषणा  B43_TXH_PHY1_MODUL_QAM64	0x1800 /* QAM64 */
#घोषणा  B43_TXH_PHY1_MODUL_QAM256	0x2000 /* QAM256 */


अटल अंतरभूत
माप_प्रकार b43_txhdr_size(काष्ठा b43_wldev *dev)
अणु
	चयन (dev->fw.hdr_क्रमmat) अणु
	हाल B43_FW_HDR_598:
		वापस 112 + माप(काष्ठा b43_plcp_hdr6);
	हाल B43_FW_HDR_410:
		वापस 104 + माप(काष्ठा b43_plcp_hdr6);
	हाल B43_FW_HDR_351:
		वापस 100 + माप(काष्ठा b43_plcp_hdr6);
	पूर्ण
	वापस 0;
पूर्ण


पूर्णांक b43_generate_txhdr(काष्ठा b43_wldev *dev,
		       u8 * txhdr,
		       काष्ठा sk_buff *skb_frag,
		       काष्ठा ieee80211_tx_info *txctl, u16 cookie);

/* Transmit Status */
काष्ठा b43_txstatus अणु
	u16 cookie;		/* The cookie from the txhdr */
	u16 seq;		/* Sequence number */
	u8 phy_stat;		/* PHY TX status */
	u8 frame_count;		/* Frame transmit count */
	u8 rts_count;		/* RTS transmit count */
	u8 supp_reason;		/* Suppression reason */
	/* flags */
	u8 pm_indicated;	/* PM mode indicated to AP */
	u8 पूर्णांकermediate;	/* Intermediate status notअगरication (not final) */
	u8 क्रम_ampdu;		/* Status is क्रम an AMPDU (afterburner) */
	u8 acked;		/* Wireless ACK received */
पूर्ण;

/* txstatus supp_reason values */
क्रमागत अणु
	B43_TXST_SUPP_NONE,	/* Not suppressed */
	B43_TXST_SUPP_PMQ,	/* Suppressed due to PMQ entry */
	B43_TXST_SUPP_FLUSH,	/* Suppressed due to flush request */
	B43_TXST_SUPP_PREV,	/* Previous fragment failed */
	B43_TXST_SUPP_CHAN,	/* Channel mismatch */
	B43_TXST_SUPP_LIFE,	/* Lअगरeसमय expired */
	B43_TXST_SUPP_UNDER,	/* Buffer underflow */
	B43_TXST_SUPP_ABNACK,	/* Afterburner NACK */
पूर्ण;

/* Receive header क्रम v4 firmware. */
काष्ठा b43_rxhdr_fw4 अणु
	__le16 frame_len;	/* Frame length */
	 PAD_BYTES(2);
	__le16 phy_status0;	/* PHY RX Status 0 */
	जोड़ अणु
		/* RSSI क्रम A/B/G-PHYs */
		काष्ठा अणु
			__u8 jssi;	/* PHY RX Status 1: JSSI */
			__u8 sig_qual;	/* PHY RX Status 1: Signal Quality */
		पूर्ण __packed;

		/* RSSI क्रम N-PHYs */
		काष्ठा अणु
			__s8 घातer0;	/* PHY RX Status 1: Power 0 */
			__s8 घातer1;	/* PHY RX Status 1: Power 1 */
		पूर्ण __packed;
	पूर्ण __packed;
	जोड़ अणु
		/* HT-PHY */
		काष्ठा अणु
			PAD_BYTES(1);
			__s8 phy_ht_घातer0;
		पूर्ण __packed;

		/* RSSI क्रम N-PHYs */
		काष्ठा अणु
			__s8 घातer2;
			PAD_BYTES(1);
		पूर्ण __packed;

		__le16 phy_status2;	/* PHY RX Status 2 */
	पूर्ण __packed;
	जोड़ अणु
		/* HT-PHY */
		काष्ठा अणु
			__s8 phy_ht_घातer1;
			__s8 phy_ht_घातer2;
		पूर्ण __packed;

		__le16 phy_status3;	/* PHY RX Status 3 */
	पूर्ण __packed;
	जोड़ अणु
		/* Tested with 598.314, 644.1001 and 666.2 */
		काष्ठा अणु
			__le16 phy_status4;	/* PHY RX Status 4 */
			__le16 phy_status5;	/* PHY RX Status 5 */
			__le32 mac_status;	/* MAC RX status */
			__le16 mac_समय;
			__le16 channel;
		पूर्ण क्रमmat_598 __packed;

		/* Tested with 351.126, 410.2160, 478.104 and 508.* */
		काष्ठा अणु
			__le32 mac_status;	/* MAC RX status */
			__le16 mac_समय;
			__le16 channel;
		पूर्ण क्रमmat_351 __packed;
	पूर्ण __packed;
पूर्ण __packed;

/* PHY RX Status 0 */
#घोषणा B43_RX_PHYST0_GAINCTL		0x4000 /* Gain Control */
#घोषणा B43_RX_PHYST0_PLCPHCF		0x0200
#घोषणा B43_RX_PHYST0_PLCPFV		0x0100
#घोषणा B43_RX_PHYST0_SHORTPRMBL	0x0080 /* Received with Short Preamble */
#घोषणा B43_RX_PHYST0_LCRS		0x0040
#घोषणा B43_RX_PHYST0_ANT		0x0020 /* Antenna */
#घोषणा B43_RX_PHYST0_UNSRATE		0x0010
#घोषणा B43_RX_PHYST0_CLIP		0x000C
#घोषणा B43_RX_PHYST0_CLIP_SHIFT	2
#घोषणा B43_RX_PHYST0_FTYPE		0x0003 /* Frame type */
#घोषणा  B43_RX_PHYST0_CCK		0x0000 /* Frame type: CCK */
#घोषणा  B43_RX_PHYST0_OFDM		0x0001 /* Frame type: OFDM */
#घोषणा  B43_RX_PHYST0_PRE_N		0x0002 /* Pre-standard N-PHY frame */
#घोषणा  B43_RX_PHYST0_STD_N		0x0003 /* Standard N-PHY frame */

/* PHY RX Status 2 */
#घोषणा B43_RX_PHYST2_LNAG		0xC000 /* LNA Gain */
#घोषणा B43_RX_PHYST2_LNAG_SHIFT	14
#घोषणा B43_RX_PHYST2_PNAG		0x3C00 /* PNA Gain */
#घोषणा B43_RX_PHYST2_PNAG_SHIFT	10
#घोषणा B43_RX_PHYST2_FOFF		0x03FF /* F offset */

/* PHY RX Status 3 */
#घोषणा B43_RX_PHYST3_DIGG		0x1800 /* DIG Gain */
#घोषणा B43_RX_PHYST3_DIGG_SHIFT	11
#घोषणा B43_RX_PHYST3_TRSTATE		0x0400 /* TR state */

/* MAC RX Status */
#घोषणा B43_RX_MAC_RXST_VALID		0x01000000 /* PHY RXST valid */
#घोषणा B43_RX_MAC_TKIP_MICERR		0x00100000 /* TKIP MIC error */
#घोषणा B43_RX_MAC_TKIP_MICATT		0x00080000 /* TKIP MIC attempted */
#घोषणा B43_RX_MAC_AGGTYPE		0x00060000 /* Aggregation type */
#घोषणा B43_RX_MAC_AGGTYPE_SHIFT	17
#घोषणा B43_RX_MAC_AMSDU		0x00010000 /* A-MSDU mask */
#घोषणा B43_RX_MAC_BEACONSENT		0x00008000 /* Beacon sent flag */
#घोषणा B43_RX_MAC_KEYIDX		0x000007E0 /* Key index */
#घोषणा B43_RX_MAC_KEYIDX_SHIFT		5
#घोषणा B43_RX_MAC_DECERR		0x00000010 /* Decrypt error */
#घोषणा B43_RX_MAC_DEC			0x00000008 /* Decryption attempted */
#घोषणा B43_RX_MAC_PADDING		0x00000004 /* Pad bytes present */
#घोषणा B43_RX_MAC_RESP			0x00000002 /* Response frame transmitted */
#घोषणा B43_RX_MAC_FCSERR		0x00000001 /* FCS error */

/* RX channel */
#घोषणा B43_RX_CHAN_40MHZ		0x1000 /* 40 Mhz channel width */
#घोषणा B43_RX_CHAN_5GHZ		0x0800 /* 5 Ghz band */
#घोषणा B43_RX_CHAN_ID			0x07F8 /* Channel ID */
#घोषणा B43_RX_CHAN_ID_SHIFT		3
#घोषणा B43_RX_CHAN_PHYTYPE		0x0007 /* PHY type */


u8 b43_plcp_get_ratecode_cck(स्थिर u8 bitrate);
u8 b43_plcp_get_ratecode_ofdm(स्थिर u8 bitrate);

व्योम b43_generate_plcp_hdr(काष्ठा b43_plcp_hdr4 *plcp,
			   स्थिर u16 octets, स्थिर u8 bitrate);

व्योम b43_rx(काष्ठा b43_wldev *dev, काष्ठा sk_buff *skb, स्थिर व्योम *_rxhdr);

व्योम b43_handle_txstatus(काष्ठा b43_wldev *dev,
			 स्थिर काष्ठा b43_txstatus *status);
bool b43_fill_txstatus_report(काष्ठा b43_wldev *dev,
			      काष्ठा ieee80211_tx_info *report,
			      स्थिर काष्ठा b43_txstatus *status);

व्योम b43_tx_suspend(काष्ठा b43_wldev *dev);
व्योम b43_tx_resume(काष्ठा b43_wldev *dev);


/* Helper functions क्रम converting the key-table index from "firmware-format"
 * to "raw-format" and back. The firmware API changed क्रम this at some revision.
 * We need to account क्रम that here. */
अटल अंतरभूत पूर्णांक b43_new_kidx_api(काष्ठा b43_wldev *dev)
अणु
	/* FIXME: Not sure the change was at rev 351 */
	वापस (dev->fw.rev >= 351);
पूर्ण
अटल अंतरभूत u8 b43_kidx_to_fw(काष्ठा b43_wldev *dev, u8 raw_kidx)
अणु
	u8 firmware_kidx;
	अगर (b43_new_kidx_api(dev)) अणु
		firmware_kidx = raw_kidx;
	पूर्ण अन्यथा अणु
		अगर (raw_kidx >= 4)	/* Is per STA key? */
			firmware_kidx = raw_kidx - 4;
		अन्यथा
			firmware_kidx = raw_kidx;	/* TX शेष key */
	पूर्ण
	वापस firmware_kidx;
पूर्ण
अटल अंतरभूत u8 b43_kidx_to_raw(काष्ठा b43_wldev *dev, u8 firmware_kidx)
अणु
	u8 raw_kidx;
	अगर (b43_new_kidx_api(dev))
		raw_kidx = firmware_kidx;
	अन्यथा
		raw_kidx = firmware_kidx + 4;	/* RX शेष keys or per STA keys */
	वापस raw_kidx;
पूर्ण

/* काष्ठा b43_निजी_tx_info - TX info निजी to b43.
 * The काष्ठाure is placed in (काष्ठा ieee80211_tx_info *)->rate_driver_data
 *
 * @bouncebuffer: DMA Bouncebuffer (अगर used)
 */
काष्ठा b43_निजी_tx_info अणु
	व्योम *bouncebuffer;
पूर्ण;

अटल अंतरभूत काष्ठा b43_निजी_tx_info *
b43_get_priv_tx_info(काष्ठा ieee80211_tx_info *info)
अणु
	BUILD_BUG_ON(माप(काष्ठा b43_निजी_tx_info) >
		     माप(info->rate_driver_data));
	वापस (काष्ठा b43_निजी_tx_info *)info->rate_driver_data;
पूर्ण

#पूर्ण_अगर /* B43_XMIT_H_ */
