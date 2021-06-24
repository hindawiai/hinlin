<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43legacy_XMIT_H_
#घोषणा B43legacy_XMIT_H_

#समावेश "main.h"


#घोषणा _b43legacy_declare_plcp_hdr(size)	\
	काष्ठा b43legacy_plcp_hdr##size अणु	\
		जोड़ अणु				\
			__le32 data;		\
			__u8 raw[size];		\
		पूर्ण __packed;	\
	पूर्ण __packed

/* काष्ठा b43legacy_plcp_hdr4 */
_b43legacy_declare_plcp_hdr(4);
/* काष्ठा b43legacy_plcp_hdr6 */
_b43legacy_declare_plcp_hdr(6);

#अघोषित _b43legacy_declare_plcp_hdr


/* TX header क्रम v3 firmware */
काष्ठा b43legacy_txhdr_fw3 अणु
	__le32 mac_ctl;				/* MAC TX control */
	__le16 mac_frame_ctl;			/* Copy of the FrameControl */
	__le16 tx_fes_समय_norm;		/* TX FES Time Normal */
	__le16 phy_ctl;				/* PHY TX control */
	__u8 iv[16];				/* Encryption IV */
	__u8 tx_receiver[6];			/* TX Frame Receiver address */
	__le16 tx_fes_समय_fb;			/* TX FES Time Fallback */
	काष्ठा b43legacy_plcp_hdr4 rts_plcp_fb;	/* RTS fallback PLCP */
	__le16 rts_dur_fb;			/* RTS fallback duration */
	काष्ठा b43legacy_plcp_hdr4 plcp_fb;	/* Fallback PLCP */
	__le16 dur_fb;				/* Fallback duration */
	PAD_BYTES(2);
	__le16 cookie;
	__le16 unknown_scb_stuff;
	काष्ठा b43legacy_plcp_hdr6 rts_plcp;	/* RTS PLCP */
	__u8 rts_frame[18];			/* The RTS frame (अगर used) */
	काष्ठा b43legacy_plcp_hdr6 plcp;
पूर्ण __packed;

/* MAC TX control */
#घोषणा B43legacy_TX4_MAC_KEYIDX	0x0FF00000 /* Security key index */
#घोषणा B43legacy_TX4_MAC_KEYIDX_SHIFT	20
#घोषणा B43legacy_TX4_MAC_KEYALG	0x00070000 /* Security key algorithm */
#घोषणा B43legacy_TX4_MAC_KEYALG_SHIFT	16
#घोषणा B43legacy_TX4_MAC_LIFETIME	0x00001000
#घोषणा B43legacy_TX4_MAC_FRAMEBURST	0x00000800
#घोषणा B43legacy_TX4_MAC_SENDCTS	0x00000400
#घोषणा B43legacy_TX4_MAC_AMPDU		0x00000300
#घोषणा B43legacy_TX4_MAC_AMPDU_SHIFT	8
#घोषणा B43legacy_TX4_MAC_CTSFALLBACKOFDM	0x00000200
#घोषणा B43legacy_TX4_MAC_FALLBACKOFDM	0x00000100
#घोषणा B43legacy_TX4_MAC_5GHZ		0x00000080
#घोषणा B43legacy_TX4_MAC_IGNPMQ	0x00000020
#घोषणा B43legacy_TX4_MAC_HWSEQ		0x00000010 /* Use Hardware Seq No */
#घोषणा B43legacy_TX4_MAC_STMSDU	0x00000008 /* Start MSDU */
#घोषणा B43legacy_TX4_MAC_SENDRTS	0x00000004
#घोषणा B43legacy_TX4_MAC_LONGFRAME	0x00000002
#घोषणा B43legacy_TX4_MAC_ACK		0x00000001

/* Extra Frame Types */
#घोषणा B43legacy_TX4_EFT_FBOFDM	0x0001 /* Data frame fb rate type */
#घोषणा B43legacy_TX4_EFT_RTSOFDM	0x0004 /* RTS/CTS rate type */
#घोषणा B43legacy_TX4_EFT_RTSFBOFDM	0x0010 /* RTS/CTS fallback rate type */

/* PHY TX control word */
#घोषणा B43legacy_TX4_PHY_ENC		0x0003 /* Data frame encoding */
#घोषणा B43legacy_TX4_PHY_ENC_CCK	0x0000 /* CCK */
#घोषणा B43legacy_TX4_PHY_ENC_OFDM	0x0001 /* Data frame rate type */
#घोषणा B43legacy_TX4_PHY_SHORTPRMBL	0x0010 /* Use लघु preamble */
#घोषणा B43legacy_TX4_PHY_ANT		0x03C0 /* Antenna selection */
#घोषणा  B43legacy_TX4_PHY_ANT0		0x0000 /* Use antenna 0 */
#घोषणा  B43legacy_TX4_PHY_ANT1		0x0100 /* Use antenna 1 */
#घोषणा  B43legacy_TX4_PHY_ANTLAST	0x0300 /* Use last used antenna */



पूर्णांक b43legacy_generate_txhdr(काष्ठा b43legacy_wldev *dev,
			      u8 *txhdr,
			      स्थिर अचिन्हित अक्षर *fragment_data,
			      अचिन्हित पूर्णांक fragment_len,
			      काष्ठा ieee80211_tx_info *info,
			      u16 cookie);


/* Transmit Status */
काष्ठा b43legacy_txstatus अणु
	u16 cookie;	/* The cookie from the txhdr */
	u16 seq;	/* Sequence number */
	u8 phy_stat;	/* PHY TX status */
	u8 frame_count;	/* Frame transmit count */
	u8 rts_count;	/* RTS transmit count */
	u8 supp_reason;	/* Suppression reason */
	/* flags */
	u8 pm_indicated;/* PM mode indicated to AP */
	u8 पूर्णांकermediate;/* Intermediate status notअगरication */
	u8 क्रम_ampdu;	/* Status is क्रम an AMPDU (afterburner) */
	u8 acked;	/* Wireless ACK received */
पूर्ण;

/* txstatus supp_reason values */
क्रमागत अणु
	B43legacy_TXST_SUPP_NONE,	/* Not suppressed */
	B43legacy_TXST_SUPP_PMQ,	/* Suppressed due to PMQ entry */
	B43legacy_TXST_SUPP_FLUSH,	/* Suppressed due to flush request */
	B43legacy_TXST_SUPP_PREV,	/* Previous fragment failed */
	B43legacy_TXST_SUPP_CHAN,	/* Channel mismatch */
	B43legacy_TXST_SUPP_LIFE,	/* Lअगरeसमय expired */
	B43legacy_TXST_SUPP_UNDER,	/* Buffer underflow */
	B43legacy_TXST_SUPP_ABNACK,	/* Afterburner NACK */
पूर्ण;

/* Transmit Status as received through DMA/PIO on old chips */
काष्ठा b43legacy_hwtxstatus अणु
	PAD_BYTES(4);
	__le16 cookie;
	u8 flags;
	u8 count;
	PAD_BYTES(2);
	__le16 seq;
	u8 phy_stat;
	PAD_BYTES(1);
पूर्ण __packed;


/* Receive header क्रम v3 firmware. */
काष्ठा b43legacy_rxhdr_fw3 अणु
	__le16 frame_len;	/* Frame length */
	PAD_BYTES(2);
	__le16 phy_status0;	/* PHY RX Status 0 */
	__u8 jssi;		/* PHY RX Status 1: JSSI */
	__u8 sig_qual;		/* PHY RX Status 1: Signal Quality */
	PAD_BYTES(2);		/* PHY RX Status 2 */
	__le16 phy_status3;	/* PHY RX Status 3 */
	__le16 mac_status;	/* MAC RX status */
	__le16 mac_समय;
	__le16 channel;
पूर्ण __packed;


/* PHY RX Status 0 */
#घोषणा B43legacy_RX_PHYST0_GAINCTL	0x4000 /* Gain Control */
#घोषणा B43legacy_RX_PHYST0_PLCPHCF	0x0200
#घोषणा B43legacy_RX_PHYST0_PLCPFV	0x0100
#घोषणा B43legacy_RX_PHYST0_SHORTPRMBL	0x0080 /* Recvd with Short Preamble */
#घोषणा B43legacy_RX_PHYST0_LCRS	0x0040
#घोषणा B43legacy_RX_PHYST0_ANT		0x0020 /* Antenna */
#घोषणा B43legacy_RX_PHYST0_UNSRATE	0x0010
#घोषणा B43legacy_RX_PHYST0_CLIP	0x000C
#घोषणा B43legacy_RX_PHYST0_CLIP_SHIFT	2
#घोषणा B43legacy_RX_PHYST0_FTYPE	0x0003 /* Frame type */
#घोषणा  B43legacy_RX_PHYST0_CCK	0x0000 /* Frame type: CCK */
#घोषणा  B43legacy_RX_PHYST0_OFDM	0x0001 /* Frame type: OFDM */
#घोषणा  B43legacy_RX_PHYST0_PRE_N	0x0002 /* Pre-standard N-PHY frame */
#घोषणा  B43legacy_RX_PHYST0_STD_N	0x0003 /* Standard N-PHY frame */

/* PHY RX Status 2 */
#घोषणा B43legacy_RX_PHYST2_LNAG	0xC000 /* LNA Gain */
#घोषणा B43legacy_RX_PHYST2_LNAG_SHIFT	14
#घोषणा B43legacy_RX_PHYST2_PNAG	0x3C00 /* PNA Gain */
#घोषणा B43legacy_RX_PHYST2_PNAG_SHIFT	10
#घोषणा B43legacy_RX_PHYST2_FOFF	0x03FF /* F offset */

/* PHY RX Status 3 */
#घोषणा B43legacy_RX_PHYST3_DIGG	0x1800 /* DIG Gain */
#घोषणा B43legacy_RX_PHYST3_DIGG_SHIFT	11
#घोषणा B43legacy_RX_PHYST3_TRSTATE	0x0400 /* TR state */

/* MAC RX Status */
#घोषणा B43legacy_RX_MAC_BEACONSENT	0x00008000 /* Beacon send flag */
#घोषणा B43legacy_RX_MAC_KEYIDX		0x000007E0 /* Key index */
#घोषणा B43legacy_RX_MAC_KEYIDX_SHIFT	5
#घोषणा B43legacy_RX_MAC_DECERR		0x00000010 /* Decrypt error */
#घोषणा B43legacy_RX_MAC_DEC		0x00000008 /* Decryption attempted */
#घोषणा B43legacy_RX_MAC_PADDING	0x00000004 /* Pad bytes present */
#घोषणा B43legacy_RX_MAC_RESP		0x00000002 /* Response frame xmitted */
#घोषणा B43legacy_RX_MAC_FCSERR		0x00000001 /* FCS error */

/* RX channel */
#घोषणा B43legacy_RX_CHAN_GAIN		0xFC00 /* Gain */
#घोषणा B43legacy_RX_CHAN_GAIN_SHIFT	10
#घोषणा B43legacy_RX_CHAN_ID		0x03FC /* Channel ID */
#घोषणा B43legacy_RX_CHAN_ID_SHIFT	2
#घोषणा B43legacy_RX_CHAN_PHYTYPE	0x0003 /* PHY type */



u8 b43legacy_plcp_get_ratecode_cck(स्थिर u8 bitrate);
u8 b43legacy_plcp_get_ratecode_ofdm(स्थिर u8 bitrate);

व्योम b43legacy_generate_plcp_hdr(काष्ठा b43legacy_plcp_hdr4 *plcp,
			       स्थिर u16 octets, स्थिर u8 bitrate);

व्योम b43legacy_rx(काष्ठा b43legacy_wldev *dev,
		काष्ठा sk_buff *skb,
		स्थिर व्योम *_rxhdr);

व्योम b43legacy_handle_txstatus(काष्ठा b43legacy_wldev *dev,
			       स्थिर काष्ठा b43legacy_txstatus *status);

व्योम b43legacy_handle_hwtxstatus(काष्ठा b43legacy_wldev *dev,
				 स्थिर काष्ठा b43legacy_hwtxstatus *hw);

व्योम b43legacy_tx_suspend(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_tx_resume(काष्ठा b43legacy_wldev *dev);


#घोषणा B43legacy_NR_QOSPARMS	22
क्रमागत अणु
	B43legacy_QOSPARM_TXOP = 0,
	B43legacy_QOSPARM_CWMIN,
	B43legacy_QOSPARM_CWMAX,
	B43legacy_QOSPARM_CWCUR,
	B43legacy_QOSPARM_AIFS,
	B43legacy_QOSPARM_BSLOTS,
	B43legacy_QOSPARM_REGGAP,
	B43legacy_QOSPARM_STATUS,
पूर्ण;

व्योम b43legacy_qos_init(काष्ठा b43legacy_wldev *dev);


/* Helper functions क्रम converting the key-table index from "firmware-format"
 * to "raw-format" and back. The firmware API changed क्रम this at some revision.
 * We need to account क्रम that here. */
अटल अंतरभूत
पूर्णांक b43legacy_new_kidx_api(काष्ठा b43legacy_wldev *dev)
अणु
	/* FIXME: Not sure the change was at rev 351 */
	वापस (dev->fw.rev >= 351);
पूर्ण
अटल अंतरभूत
u8 b43legacy_kidx_to_fw(काष्ठा b43legacy_wldev *dev, u8 raw_kidx)
अणु
	u8 firmware_kidx;
	अगर (b43legacy_new_kidx_api(dev))
		firmware_kidx = raw_kidx;
	अन्यथा अणु
		अगर (raw_kidx >= 4) /* Is per STA key? */
			firmware_kidx = raw_kidx - 4;
		अन्यथा
			firmware_kidx = raw_kidx; /* TX शेष key */
	पूर्ण
	वापस firmware_kidx;
पूर्ण
अटल अंतरभूत
u8 b43legacy_kidx_to_raw(काष्ठा b43legacy_wldev *dev, u8 firmware_kidx)
अणु
	u8 raw_kidx;
	अगर (b43legacy_new_kidx_api(dev))
		raw_kidx = firmware_kidx;
	अन्यथा
		/* RX शेष keys or per STA keys */
		raw_kidx = firmware_kidx + 4;
	वापस raw_kidx;
पूर्ण

#पूर्ण_अगर /* B43legacy_XMIT_H_ */
