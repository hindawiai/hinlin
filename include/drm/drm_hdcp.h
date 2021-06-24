<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright (C) 2017 Google, Inc.
 *
 * Authors:
 * Sean Paul <seanpaul@chromium.org>
 */

#अगर_अघोषित _DRM_HDCP_H_INCLUDED_
#घोषणा _DRM_HDCP_H_INCLUDED_

#समावेश <linux/types.h>

/* Period of hdcp checks (to ensure we're still authenticated) */
#घोषणा DRM_HDCP_CHECK_PERIOD_MS		(128 * 16)
#घोषणा DRM_HDCP2_CHECK_PERIOD_MS		500

/* Shared lengths/masks between HDMI/DVI/DisplayPort */
#घोषणा DRM_HDCP_AN_LEN				8
#घोषणा DRM_HDCP_BSTATUS_LEN			2
#घोषणा DRM_HDCP_KSV_LEN			5
#घोषणा DRM_HDCP_RI_LEN				2
#घोषणा DRM_HDCP_V_PRIME_PART_LEN		4
#घोषणा DRM_HDCP_V_PRIME_NUM_PARTS		5
#घोषणा DRM_HDCP_NUM_DOWNSTREAM(x)		(x & 0x7f)
#घोषणा DRM_HDCP_MAX_CASCADE_EXCEEDED(x)	(x & BIT(3))
#घोषणा DRM_HDCP_MAX_DEVICE_EXCEEDED(x)		(x & BIT(7))

/* Slave address क्रम the HDCP रेजिस्टरs in the receiver */
#घोषणा DRM_HDCP_DDC_ADDR			0x3A

/* Value to use at the end of the SHA-1 bytestream used क्रम repeaters */
#घोषणा DRM_HDCP_SHA1_TERMINATOR		0x80

/* HDCP रेजिस्टर offsets क्रम HDMI/DVI devices */
#घोषणा DRM_HDCP_DDC_BKSV			0x00
#घोषणा DRM_HDCP_DDC_RI_PRIME			0x08
#घोषणा DRM_HDCP_DDC_AKSV			0x10
#घोषणा DRM_HDCP_DDC_AN				0x18
#घोषणा DRM_HDCP_DDC_V_PRIME(h)			(0x20 + h * 4)
#घोषणा DRM_HDCP_DDC_BCAPS			0x40
#घोषणा  DRM_HDCP_DDC_BCAPS_REPEATER_PRESENT	BIT(6)
#घोषणा  DRM_HDCP_DDC_BCAPS_KSV_FIFO_READY	BIT(5)
#घोषणा DRM_HDCP_DDC_BSTATUS			0x41
#घोषणा DRM_HDCP_DDC_KSV_FIFO			0x43

#घोषणा DRM_HDCP_1_4_SRM_ID			0x8
#घोषणा DRM_HDCP_1_4_VRL_LENGTH_SIZE		3
#घोषणा DRM_HDCP_1_4_DCP_SIG_SIZE		40

/* Protocol message definition क्रम HDCP2.2 specअगरication */
/*
 * Protected content streams are classअगरied पूर्णांकo 2 types:
 * - Type0: Can be transmitted with HDCP 1.4+
 * - Type1: Can be transmitted with HDCP 2.2+
 */
#घोषणा HDCP_STREAM_TYPE0			0x00
#घोषणा HDCP_STREAM_TYPE1			0x01

/* HDCP2.2 Msg IDs */
#घोषणा HDCP_2_2_शून्य_MSG			1
#घोषणा HDCP_2_2_AKE_INIT			2
#घोषणा HDCP_2_2_AKE_SEND_CERT			3
#घोषणा HDCP_2_2_AKE_NO_STORED_KM		4
#घोषणा HDCP_2_2_AKE_STORED_KM			5
#घोषणा HDCP_2_2_AKE_SEND_HPRIME		7
#घोषणा HDCP_2_2_AKE_SEND_PAIRING_INFO		8
#घोषणा HDCP_2_2_LC_INIT			9
#घोषणा HDCP_2_2_LC_SEND_LPRIME			10
#घोषणा HDCP_2_2_SKE_SEND_EKS			11
#घोषणा HDCP_2_2_REP_SEND_RECVID_LIST		12
#घोषणा HDCP_2_2_REP_SEND_ACK			15
#घोषणा HDCP_2_2_REP_STREAM_MANAGE		16
#घोषणा HDCP_2_2_REP_STREAM_READY		17

#घोषणा HDCP_2_2_RTX_LEN			8
#घोषणा HDCP_2_2_RRX_LEN			8

#घोषणा HDCP_2_2_K_PUB_RX_MOD_N_LEN		128
#घोषणा HDCP_2_2_K_PUB_RX_EXP_E_LEN		3
#घोषणा HDCP_2_2_K_PUB_RX_LEN			(HDCP_2_2_K_PUB_RX_MOD_N_LEN + \
						 HDCP_2_2_K_PUB_RX_EXP_E_LEN)

#घोषणा HDCP_2_2_DCP_LLC_SIG_LEN		384

#घोषणा HDCP_2_2_E_KPUB_KM_LEN			128
#घोषणा HDCP_2_2_E_KH_KM_M_LEN			(16 + 16)
#घोषणा HDCP_2_2_H_PRIME_LEN			32
#घोषणा HDCP_2_2_E_KH_KM_LEN			16
#घोषणा HDCP_2_2_RN_LEN				8
#घोषणा HDCP_2_2_L_PRIME_LEN			32
#घोषणा HDCP_2_2_E_DKEY_KS_LEN			16
#घोषणा HDCP_2_2_RIV_LEN			8
#घोषणा HDCP_2_2_SEQ_NUM_LEN			3
#घोषणा HDCP_2_2_V_PRIME_HALF_LEN		(HDCP_2_2_L_PRIME_LEN / 2)
#घोषणा HDCP_2_2_RECEIVER_ID_LEN		DRM_HDCP_KSV_LEN
#घोषणा HDCP_2_2_MAX_DEVICE_COUNT		31
#घोषणा HDCP_2_2_RECEIVER_IDS_MAX_LEN		(HDCP_2_2_RECEIVER_ID_LEN * \
						 HDCP_2_2_MAX_DEVICE_COUNT)
#घोषणा HDCP_2_2_MPRIME_LEN			32

/* Following Macros take a byte at a समय क्रम bit(s) masking */
/*
 * TODO: HDCP_2_2_MAX_CONTENT_STREAMS_CNT is based upon actual
 * H/W MST streams capacity.
 * This required to be moved out to platक्रमm specअगरic header.
 */
#घोषणा HDCP_2_2_MAX_CONTENT_STREAMS_CNT	4
#घोषणा HDCP_2_2_TXCAP_MASK_LEN			2
#घोषणा HDCP_2_2_RXCAPS_LEN			3
#घोषणा HDCP_2_2_RX_REPEATER(x)			((x) & BIT(0))
#घोषणा HDCP_2_2_DP_HDCP_CAPABLE(x)		((x) & BIT(1))
#घोषणा HDCP_2_2_RXINFO_LEN			2

/* HDCP1.x compliant device in करोwnstream */
#घोषणा HDCP_2_2_HDCP1_DEVICE_CONNECTED(x)	((x) & BIT(0))

/* HDCP2.0 Compliant repeater in करोwnstream */
#घोषणा HDCP_2_2_HDCP_2_0_REP_CONNECTED(x)	((x) & BIT(1))
#घोषणा HDCP_2_2_MAX_CASCADE_EXCEEDED(x)	((x) & BIT(2))
#घोषणा HDCP_2_2_MAX_DEVS_EXCEEDED(x)		((x) & BIT(3))
#घोषणा HDCP_2_2_DEV_COUNT_LO(x)		(((x) & (0xF << 4)) >> 4)
#घोषणा HDCP_2_2_DEV_COUNT_HI(x)		((x) & BIT(0))
#घोषणा HDCP_2_2_DEPTH(x)			(((x) & (0x7 << 1)) >> 1)

काष्ठा hdcp2_cert_rx अणु
	u8	receiver_id[HDCP_2_2_RECEIVER_ID_LEN];
	u8	kpub_rx[HDCP_2_2_K_PUB_RX_LEN];
	u8	reserved[2];
	u8	dcp_signature[HDCP_2_2_DCP_LLC_SIG_LEN];
पूर्ण __packed;

काष्ठा hdcp2_streamid_type अणु
	u8	stream_id;
	u8	stream_type;
पूर्ण __packed;

/*
 * The TxCaps field specअगरied in the HDCP HDMI, DP specs
 * This field is big endian as specअगरied in the errata.
 */
काष्ठा hdcp2_tx_caps अणु
	/* Transmitter must set this to 0x2 */
	u8	version;

	/* Reserved क्रम HDCP and DP Spec. Read as Zero */
	u8	tx_cap_mask[HDCP_2_2_TXCAP_MASK_LEN];
पूर्ण __packed;

/* Main काष्ठाures क्रम HDCP2.2 protocol communication */
काष्ठा hdcp2_ake_init अणु
	u8			msg_id;
	u8			r_tx[HDCP_2_2_RTX_LEN];
	काष्ठा hdcp2_tx_caps	tx_caps;
पूर्ण __packed;

काष्ठा hdcp2_ake_send_cert अणु
	u8			msg_id;
	काष्ठा hdcp2_cert_rx	cert_rx;
	u8			r_rx[HDCP_2_2_RRX_LEN];
	u8			rx_caps[HDCP_2_2_RXCAPS_LEN];
पूर्ण __packed;

काष्ठा hdcp2_ake_no_stored_km अणु
	u8	msg_id;
	u8	e_kpub_km[HDCP_2_2_E_KPUB_KM_LEN];
पूर्ण __packed;

काष्ठा hdcp2_ake_stored_km अणु
	u8	msg_id;
	u8	e_kh_km_m[HDCP_2_2_E_KH_KM_M_LEN];
पूर्ण __packed;

काष्ठा hdcp2_ake_send_hprime अणु
	u8	msg_id;
	u8	h_prime[HDCP_2_2_H_PRIME_LEN];
पूर्ण __packed;

काष्ठा hdcp2_ake_send_pairing_info अणु
	u8	msg_id;
	u8	e_kh_km[HDCP_2_2_E_KH_KM_LEN];
पूर्ण __packed;

काष्ठा hdcp2_lc_init अणु
	u8	msg_id;
	u8	r_n[HDCP_2_2_RN_LEN];
पूर्ण __packed;

काष्ठा hdcp2_lc_send_lprime अणु
	u8	msg_id;
	u8	l_prime[HDCP_2_2_L_PRIME_LEN];
पूर्ण __packed;

काष्ठा hdcp2_ske_send_eks अणु
	u8	msg_id;
	u8	e_dkey_ks[HDCP_2_2_E_DKEY_KS_LEN];
	u8	riv[HDCP_2_2_RIV_LEN];
पूर्ण __packed;

काष्ठा hdcp2_rep_send_receiverid_list अणु
	u8	msg_id;
	u8	rx_info[HDCP_2_2_RXINFO_LEN];
	u8	seq_num_v[HDCP_2_2_SEQ_NUM_LEN];
	u8	v_prime[HDCP_2_2_V_PRIME_HALF_LEN];
	u8	receiver_ids[HDCP_2_2_RECEIVER_IDS_MAX_LEN];
पूर्ण __packed;

काष्ठा hdcp2_rep_send_ack अणु
	u8	msg_id;
	u8	v[HDCP_2_2_V_PRIME_HALF_LEN];
पूर्ण __packed;

काष्ठा hdcp2_rep_stream_manage अणु
	u8			msg_id;
	u8			seq_num_m[HDCP_2_2_SEQ_NUM_LEN];
	__be16			k;
	काष्ठा hdcp2_streamid_type streams[HDCP_2_2_MAX_CONTENT_STREAMS_CNT];
पूर्ण __packed;

काष्ठा hdcp2_rep_stream_पढ़ोy अणु
	u8	msg_id;
	u8	m_prime[HDCP_2_2_MPRIME_LEN];
पूर्ण __packed;

/* HDCP2.2 TIMEOUTs in mSec */
#घोषणा HDCP_2_2_CERT_TIMEOUT_MS		100
#घोषणा HDCP_2_2_DP_CERT_READ_TIMEOUT_MS	110
#घोषणा HDCP_2_2_HPRIME_NO_PAIRED_TIMEOUT_MS	1000
#घोषणा HDCP_2_2_HPRIME_PAIRED_TIMEOUT_MS	200
#घोषणा HDCP_2_2_DP_HPRIME_READ_TIMEOUT_MS	7
#घोषणा HDCP_2_2_PAIRING_TIMEOUT_MS		200
#घोषणा HDCP_2_2_DP_PAIRING_READ_TIMEOUT_MS	5
#घोषणा	HDCP_2_2_HDMI_LPRIME_TIMEOUT_MS		20
#घोषणा HDCP_2_2_DP_LPRIME_TIMEOUT_MS		16
#घोषणा HDCP_2_2_RECVID_LIST_TIMEOUT_MS		3000
#घोषणा HDCP_2_2_STREAM_READY_TIMEOUT_MS	100

/* HDMI HDCP2.2 Register Offsets */
#घोषणा HDCP_2_2_HDMI_REG_VER_OFFSET		0x50
#घोषणा HDCP_2_2_HDMI_REG_WR_MSG_OFFSET		0x60
#घोषणा HDCP_2_2_HDMI_REG_RXSTATUS_OFFSET	0x70
#घोषणा HDCP_2_2_HDMI_REG_RD_MSG_OFFSET		0x80
#घोषणा HDCP_2_2_HDMI_REG_DBG_OFFSET		0xC0

#घोषणा HDCP_2_2_HDMI_SUPPORT_MASK		BIT(2)
#घोषणा HDCP_2_2_RX_CAPS_VERSION_VAL		0x02
#घोषणा HDCP_2_2_SEQ_NUM_MAX			0xFFFFFF
#घोषणा	HDCP_2_2_DELAY_BEFORE_ENCRYPTION_EN	200

/* Below macros take a byte at a समय and mask the bit(s) */
#घोषणा HDCP_2_2_HDMI_RXSTATUS_LEN		2
#घोषणा HDCP_2_2_HDMI_RXSTATUS_MSG_SZ_HI(x)	((x) & 0x3)
#घोषणा HDCP_2_2_HDMI_RXSTATUS_READY(x)		((x) & BIT(2))
#घोषणा HDCP_2_2_HDMI_RXSTATUS_REAUTH_REQ(x)	((x) & BIT(3))

/*
 * Helper functions to convert 24bit big endian hdcp sequence number to
 * host क्रमmat and back
 */
अटल अंतरभूत
u32 drm_hdcp_be24_to_cpu(स्थिर u8 seq_num[HDCP_2_2_SEQ_NUM_LEN])
अणु
	वापस (u32)(seq_num[2] | seq_num[1] << 8 | seq_num[0] << 16);
पूर्ण

अटल अंतरभूत
व्योम drm_hdcp_cpu_to_be24(u8 seq_num[HDCP_2_2_SEQ_NUM_LEN], u32 val)
अणु
	seq_num[0] = val >> 16;
	seq_num[1] = val >> 8;
	seq_num[2] = val;
पूर्ण

#घोषणा DRM_HDCP_SRM_GEN1_MAX_BYTES		(5 * 1024)
#घोषणा DRM_HDCP_1_4_SRM_ID			0x8
#घोषणा DRM_HDCP_SRM_ID_MASK			(0xF << 4)
#घोषणा DRM_HDCP_1_4_VRL_LENGTH_SIZE		3
#घोषणा DRM_HDCP_1_4_DCP_SIG_SIZE		40
#घोषणा DRM_HDCP_2_SRM_ID			0x9
#घोषणा DRM_HDCP_2_INDICATOR			0x1
#घोषणा DRM_HDCP_2_INDICATOR_MASK		0xF
#घोषणा DRM_HDCP_2_VRL_LENGTH_SIZE		3
#घोषणा DRM_HDCP_2_DCP_SIG_SIZE			384
#घोषणा DRM_HDCP_2_NO_OF_DEV_PLUS_RESERVED_SZ	4
#घोषणा DRM_HDCP_2_KSV_COUNT_2_LSBITS(byte)	(((byte) & 0xC0) >> 6)

काष्ठा hdcp_srm_header अणु
	u8 srm_id;
	u8 reserved;
	__be16 srm_version;
	u8 srm_gen_no;
पूर्ण __packed;

काष्ठा drm_device;
काष्ठा drm_connector;

पूर्णांक drm_hdcp_check_ksvs_revoked(काष्ठा drm_device *dev,
				u8 *ksvs, u32 ksv_count);
पूर्णांक drm_connector_attach_content_protection_property(
		काष्ठा drm_connector *connector, bool hdcp_content_type);
व्योम drm_hdcp_update_content_protection(काष्ठा drm_connector *connector,
					u64 val);

/* Content Type classअगरication क्रम HDCP2.2 vs others */
#घोषणा DRM_MODE_HDCP_CONTENT_TYPE0		0
#घोषणा DRM_MODE_HDCP_CONTENT_TYPE1		1

#पूर्ण_अगर
