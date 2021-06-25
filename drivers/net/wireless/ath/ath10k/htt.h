<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _HTT_H_
#घोषणा _HTT_H_

#समावेश <linux/bug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/kfअगरo.h>
#समावेश <net/mac80211.h>

#समावेश "htc.h"
#समावेश "hw.h"
#समावेश "rx_desc.h"

क्रमागत htt_dbg_stats_type अणु
	HTT_DBG_STATS_WAL_PDEV_TXRX = 1 << 0,
	HTT_DBG_STATS_RX_REORDER    = 1 << 1,
	HTT_DBG_STATS_RX_RATE_INFO  = 1 << 2,
	HTT_DBG_STATS_TX_PPDU_LOG   = 1 << 3,
	HTT_DBG_STATS_TX_RATE_INFO  = 1 << 4,
	/* bits 5-23 currently reserved */

	HTT_DBG_NUM_STATS /* keep this last */
पूर्ण;

क्रमागत htt_h2t_msg_type अणु /* host-to-target */
	HTT_H2T_MSG_TYPE_VERSION_REQ        = 0,
	HTT_H2T_MSG_TYPE_TX_FRM             = 1,
	HTT_H2T_MSG_TYPE_RX_RING_CFG        = 2,
	HTT_H2T_MSG_TYPE_STATS_REQ          = 3,
	HTT_H2T_MSG_TYPE_SYNC               = 4,
	HTT_H2T_MSG_TYPE_AGGR_CFG           = 5,
	HTT_H2T_MSG_TYPE_FRAG_DESC_BANK_CFG = 6,

	/* This command is used क्रम sending management frames in HTT < 3.0.
	 * HTT >= 3.0 uses TX_FRM क्रम everything.
	 */
	HTT_H2T_MSG_TYPE_MGMT_TX            = 7,
	HTT_H2T_MSG_TYPE_TX_FETCH_RESP      = 11,

	HTT_H2T_NUM_MSGS /* keep this last */
पूर्ण;

काष्ठा htt_cmd_hdr अणु
	u8 msg_type;
पूर्ण __packed;

काष्ठा htt_ver_req अणु
	u8 pad[माप(u32) - माप(काष्ठा htt_cmd_hdr)];
पूर्ण __packed;

/*
 * HTT tx MSDU descriptor
 *
 * The HTT tx MSDU descriptor is created by the host HTT SW क्रम each
 * tx MSDU.  The HTT tx MSDU descriptor contains the inक्रमmation that
 * the target firmware needs क्रम the FW's tx processing, particularly
 * क्रम creating the HW msdu descriptor.
 * The same HTT tx descriptor is used क्रम HL and LL प्रणालीs, though
 * a few fields within the tx descriptor are used only by LL or
 * only by HL.
 * The HTT tx descriptor is defined in two manners: by a काष्ठा with
 * bitfields, and by a series of [dword offset, bit mask, bit shअगरt]
 * definitions.
 * The target should use the काष्ठा def, क्रम simplicitly and clarity,
 * but the host shall use the bit-mast + bit-shअगरt defs, to be endian-
 * neutral.  Specअगरically, the host shall use the get/set macros built
 * around the mask + shअगरt defs.
 */
काष्ठा htt_data_tx_desc_frag अणु
	जोड़ अणु
		काष्ठा द्विगुन_word_addr अणु
			__le32 paddr;
			__le32 len;
		पूर्ण __packed dword_addr;
		काष्ठा triple_word_addr अणु
			__le32 paddr_lo;
			__le16 paddr_hi;
			__le16 len_16;
		पूर्ण __packed tword_addr;
	पूर्ण __packed;
पूर्ण __packed;

काष्ठा htt_msdu_ext_desc अणु
	__le32 tso_flag[3];
	__le16 ip_identअगरication;
	u8 flags;
	u8 reserved;
	काष्ठा htt_data_tx_desc_frag frags[6];
पूर्ण;

काष्ठा htt_msdu_ext_desc_64 अणु
	__le32 tso_flag[5];
	__le16 ip_identअगरication;
	u8 flags;
	u8 reserved;
	काष्ठा htt_data_tx_desc_frag frags[6];
पूर्ण;

#घोषणा	HTT_MSDU_EXT_DESC_FLAG_IPV4_CSUM_ENABLE		BIT(0)
#घोषणा	HTT_MSDU_EXT_DESC_FLAG_UDP_IPV4_CSUM_ENABLE	BIT(1)
#घोषणा	HTT_MSDU_EXT_DESC_FLAG_UDP_IPV6_CSUM_ENABLE	BIT(2)
#घोषणा	HTT_MSDU_EXT_DESC_FLAG_TCP_IPV4_CSUM_ENABLE	BIT(3)
#घोषणा	HTT_MSDU_EXT_DESC_FLAG_TCP_IPV6_CSUM_ENABLE	BIT(4)

#घोषणा HTT_MSDU_CHECKSUM_ENABLE (HTT_MSDU_EXT_DESC_FLAG_IPV4_CSUM_ENABLE \
				 | HTT_MSDU_EXT_DESC_FLAG_UDP_IPV4_CSUM_ENABLE \
				 | HTT_MSDU_EXT_DESC_FLAG_UDP_IPV6_CSUM_ENABLE \
				 | HTT_MSDU_EXT_DESC_FLAG_TCP_IPV4_CSUM_ENABLE \
				 | HTT_MSDU_EXT_DESC_FLAG_TCP_IPV6_CSUM_ENABLE)

#घोषणा HTT_MSDU_EXT_DESC_FLAG_IPV4_CSUM_ENABLE_64		BIT(16)
#घोषणा HTT_MSDU_EXT_DESC_FLAG_UDP_IPV4_CSUM_ENABLE_64		BIT(17)
#घोषणा HTT_MSDU_EXT_DESC_FLAG_UDP_IPV6_CSUM_ENABLE_64		BIT(18)
#घोषणा HTT_MSDU_EXT_DESC_FLAG_TCP_IPV4_CSUM_ENABLE_64		BIT(19)
#घोषणा HTT_MSDU_EXT_DESC_FLAG_TCP_IPV6_CSUM_ENABLE_64		BIT(20)
#घोषणा HTT_MSDU_EXT_DESC_FLAG_PARTIAL_CSUM_ENABLE_64		BIT(21)

#घोषणा HTT_MSDU_CHECKSUM_ENABLE_64  (HTT_MSDU_EXT_DESC_FLAG_IPV4_CSUM_ENABLE_64 \
				     | HTT_MSDU_EXT_DESC_FLAG_UDP_IPV4_CSUM_ENABLE_64 \
				     | HTT_MSDU_EXT_DESC_FLAG_UDP_IPV6_CSUM_ENABLE_64 \
				     | HTT_MSDU_EXT_DESC_FLAG_TCP_IPV4_CSUM_ENABLE_64 \
				     | HTT_MSDU_EXT_DESC_FLAG_TCP_IPV6_CSUM_ENABLE_64)

क्रमागत htt_data_tx_desc_flags0 अणु
	HTT_DATA_TX_DESC_FLAGS0_MAC_HDR_PRESENT = 1 << 0,
	HTT_DATA_TX_DESC_FLAGS0_NO_AGGR         = 1 << 1,
	HTT_DATA_TX_DESC_FLAGS0_NO_ENCRYPT      = 1 << 2,
	HTT_DATA_TX_DESC_FLAGS0_NO_CLASSIFY     = 1 << 3,
	HTT_DATA_TX_DESC_FLAGS0_RSVD0           = 1 << 4
#घोषणा HTT_DATA_TX_DESC_FLAGS0_PKT_TYPE_MASK 0xE0
#घोषणा HTT_DATA_TX_DESC_FLAGS0_PKT_TYPE_LSB 5
पूर्ण;

क्रमागत htt_data_tx_desc_flags1 अणु
#घोषणा HTT_DATA_TX_DESC_FLAGS1_VDEV_ID_BITS 6
#घोषणा HTT_DATA_TX_DESC_FLAGS1_VDEV_ID_MASK 0x003F
#घोषणा HTT_DATA_TX_DESC_FLAGS1_VDEV_ID_LSB  0
#घोषणा HTT_DATA_TX_DESC_FLAGS1_EXT_TID_BITS 5
#घोषणा HTT_DATA_TX_DESC_FLAGS1_EXT_TID_MASK 0x07C0
#घोषणा HTT_DATA_TX_DESC_FLAGS1_EXT_TID_LSB  6
	HTT_DATA_TX_DESC_FLAGS1_POSTPONED        = 1 << 11,
	HTT_DATA_TX_DESC_FLAGS1_MORE_IN_BATCH    = 1 << 12,
	HTT_DATA_TX_DESC_FLAGS1_CKSUM_L3_OFFLOAD = 1 << 13,
	HTT_DATA_TX_DESC_FLAGS1_CKSUM_L4_OFFLOAD = 1 << 14,
	HTT_DATA_TX_DESC_FLAGS1_TX_COMPLETE      = 1 << 15
पूर्ण;

#घोषणा HTT_TX_CREDIT_DELTA_ABS_M      0xffff0000
#घोषणा HTT_TX_CREDIT_DELTA_ABS_S      16
#घोषणा HTT_TX_CREDIT_DELTA_ABS_GET(word) \
	    (((word) & HTT_TX_CREDIT_DELTA_ABS_M) >> HTT_TX_CREDIT_DELTA_ABS_S)

#घोषणा HTT_TX_CREDIT_SIGN_BIT_M       0x00000100
#घोषणा HTT_TX_CREDIT_SIGN_BIT_S       8
#घोषणा HTT_TX_CREDIT_SIGN_BIT_GET(word) \
	    (((word) & HTT_TX_CREDIT_SIGN_BIT_M) >> HTT_TX_CREDIT_SIGN_BIT_S)

क्रमागत htt_data_tx_ext_tid अणु
	HTT_DATA_TX_EXT_TID_NON_QOS_MCAST_BCAST = 16,
	HTT_DATA_TX_EXT_TID_MGMT                = 17,
	HTT_DATA_TX_EXT_TID_INVALID             = 31
पूर्ण;

#घोषणा HTT_INVALID_PEERID 0xFFFF

/*
 * htt_data_tx_desc - used क्रम data tx path
 *
 * Note: vdev_id irrelevant क्रम pkt_type == raw and no_classअगरy == 1.
 *       ext_tid: क्रम qos-data frames (0-15), see %HTT_DATA_TX_EXT_TID_
 *                क्रम special kinds of tids
 *       postponed: only क्रम HL hosts. indicates अगर this is a resend
 *                  (HL hosts manage queues on the host )
 *       more_in_batch: only क्रम HL hosts. indicates अगर more packets are
 *                      pending. this allows target to रुको and aggregate
 *       freq: 0 means home channel of given vdev. पूर्णांकended क्रम offchannel
 */
काष्ठा htt_data_tx_desc अणु
	u8 flags0; /* %HTT_DATA_TX_DESC_FLAGS0_ */
	__le16 flags1; /* %HTT_DATA_TX_DESC_FLAGS1_ */
	__le16 len;
	__le16 id;
	__le32 frags_paddr;
	जोड़ अणु
		__le32 peerid;
		काष्ठा अणु
			__le16 peerid;
			__le16 freq;
		पूर्ण __packed offchan_tx;
	पूर्ण __packed;
	u8 prefetch[0]; /* start of frame, क्रम FW classअगरication engine */
पूर्ण __packed;

काष्ठा htt_data_tx_desc_64 अणु
	u8 flags0; /* %HTT_DATA_TX_DESC_FLAGS0_ */
	__le16 flags1; /* %HTT_DATA_TX_DESC_FLAGS1_ */
	__le16 len;
	__le16 id;
	__le64 frags_paddr;
	जोड़ अणु
		__le32 peerid;
		काष्ठा अणु
			__le16 peerid;
			__le16 freq;
		पूर्ण __packed offchan_tx;
	पूर्ण __packed;
	u8 prefetch[0]; /* start of frame, क्रम FW classअगरication engine */
पूर्ण __packed;

क्रमागत htt_rx_ring_flags अणु
	HTT_RX_RING_FLAGS_MAC80211_HDR = 1 << 0,
	HTT_RX_RING_FLAGS_MSDU_PAYLOAD = 1 << 1,
	HTT_RX_RING_FLAGS_PPDU_START   = 1 << 2,
	HTT_RX_RING_FLAGS_PPDU_END     = 1 << 3,
	HTT_RX_RING_FLAGS_MPDU_START   = 1 << 4,
	HTT_RX_RING_FLAGS_MPDU_END     = 1 << 5,
	HTT_RX_RING_FLAGS_MSDU_START   = 1 << 6,
	HTT_RX_RING_FLAGS_MSDU_END     = 1 << 7,
	HTT_RX_RING_FLAGS_RX_ATTENTION = 1 << 8,
	HTT_RX_RING_FLAGS_FRAG_INFO    = 1 << 9,
	HTT_RX_RING_FLAGS_UNICAST_RX   = 1 << 10,
	HTT_RX_RING_FLAGS_MULTICAST_RX = 1 << 11,
	HTT_RX_RING_FLAGS_CTRL_RX      = 1 << 12,
	HTT_RX_RING_FLAGS_MGMT_RX      = 1 << 13,
	HTT_RX_RING_FLAGS_शून्य_RX      = 1 << 14,
	HTT_RX_RING_FLAGS_PHY_DATA_RX  = 1 << 15
पूर्ण;

#घोषणा HTT_RX_RING_SIZE_MIN 128
#घोषणा HTT_RX_RING_SIZE_MAX 2048
#घोषणा HTT_RX_RING_SIZE HTT_RX_RING_SIZE_MAX
#घोषणा HTT_RX_RING_FILL_LEVEL (((HTT_RX_RING_SIZE) / 2) - 1)
#घोषणा HTT_RX_RING_FILL_LEVEL_DUAL_MAC (HTT_RX_RING_SIZE - 1)

काष्ठा htt_rx_ring_setup_ring32 अणु
	__le32 fw_idx_shaकरोw_reg_paddr;
	__le32 rx_ring_base_paddr;
	__le16 rx_ring_len; /* in 4-byte words */
	__le16 rx_ring_bufsize; /* rx skb size - in bytes */
	__le16 flags; /* %HTT_RX_RING_FLAGS_ */
	__le16 fw_idx_init_val;

	/* the following offsets are in 4-byte units */
	__le16 mac80211_hdr_offset;
	__le16 msdu_payload_offset;
	__le16 ppdu_start_offset;
	__le16 ppdu_end_offset;
	__le16 mpdu_start_offset;
	__le16 mpdu_end_offset;
	__le16 msdu_start_offset;
	__le16 msdu_end_offset;
	__le16 rx_attention_offset;
	__le16 frag_info_offset;
पूर्ण __packed;

काष्ठा htt_rx_ring_setup_ring64 अणु
	__le64 fw_idx_shaकरोw_reg_paddr;
	__le64 rx_ring_base_paddr;
	__le16 rx_ring_len; /* in 4-byte words */
	__le16 rx_ring_bufsize; /* rx skb size - in bytes */
	__le16 flags; /* %HTT_RX_RING_FLAGS_ */
	__le16 fw_idx_init_val;

	/* the following offsets are in 4-byte units */
	__le16 mac80211_hdr_offset;
	__le16 msdu_payload_offset;
	__le16 ppdu_start_offset;
	__le16 ppdu_end_offset;
	__le16 mpdu_start_offset;
	__le16 mpdu_end_offset;
	__le16 msdu_start_offset;
	__le16 msdu_end_offset;
	__le16 rx_attention_offset;
	__le16 frag_info_offset;
पूर्ण __packed;

काष्ठा htt_rx_ring_setup_hdr अणु
	u8 num_rings; /* supported values: 1, 2 */
	__le16 rsvd0;
पूर्ण __packed;

काष्ठा htt_rx_ring_setup_32 अणु
	काष्ठा htt_rx_ring_setup_hdr hdr;
	काष्ठा htt_rx_ring_setup_ring32 rings[];
पूर्ण __packed;

काष्ठा htt_rx_ring_setup_64 अणु
	काष्ठा htt_rx_ring_setup_hdr hdr;
	काष्ठा htt_rx_ring_setup_ring64 rings[];
पूर्ण __packed;

/*
 * htt_stats_req - request target to send specअगरied statistics
 *
 * @msg_type: hardcoded %HTT_H2T_MSG_TYPE_STATS_REQ
 * @upload_types: see %htt_dbg_stats_type. this is 24bit field actually
 *	so make sure its little-endian.
 * @reset_types: see %htt_dbg_stats_type. this is 24bit field actually
 *	so make sure its little-endian.
 * @cfg_val: stat_type specअगरic configuration
 * @stat_type: see %htt_dbg_stats_type
 * @cookie_lsb: used क्रम confirmation message from target->host
 * @cookie_msb: ditto as %cookie
 */
काष्ठा htt_stats_req अणु
	u8 upload_types[3];
	u8 rsvd0;
	u8 reset_types[3];
	काष्ठा अणु
		u8 mpdu_bytes;
		u8 mpdu_num_msdus;
		u8 msdu_bytes;
	पूर्ण __packed;
	u8 stat_type;
	__le32 cookie_lsb;
	__le32 cookie_msb;
पूर्ण __packed;

#घोषणा HTT_STATS_REQ_CFG_STAT_TYPE_INVALID 0xff
#घोषणा HTT_STATS_BIT_MASK GENMASK(16, 0)

/*
 * htt_oob_sync_req - request out-of-band sync
 *
 * The HTT SYNC tells the target to suspend processing of subsequent
 * HTT host-to-target messages until some other target agent locally
 * inक्रमms the target HTT FW that the current sync counter is equal to
 * or greater than (in a modulo sense) the sync counter specअगरied in
 * the SYNC message.
 *
 * This allows other host-target components to synchronize their operation
 * with HTT, e.g. to ensure that tx frames करोn't get transmitted until a
 * security key has been करोwnloaded to and activated by the target.
 * In the असलence of any explicit synchronization counter value
 * specअगरication, the target HTT FW will use zero as the शेष current
 * sync value.
 *
 * The HTT target FW will suspend its host->target message processing as दीर्घ
 * as 0 < (in-band sync counter - out-of-band sync counter) & 0xff < 128.
 */
काष्ठा htt_oob_sync_req अणु
	u8 sync_count;
	__le16 rsvd0;
पूर्ण __packed;

काष्ठा htt_aggr_conf अणु
	u8 max_num_ampdu_subframes;
	/* amsdu_subframes is limited by 0x1F mask */
	u8 max_num_amsdu_subframes;
पूर्ण __packed;

काष्ठा htt_aggr_conf_v2 अणु
	u8 max_num_ampdu_subframes;
	/* amsdu_subframes is limited by 0x1F mask */
	u8 max_num_amsdu_subframes;
	u8 reserved;
पूर्ण __packed;

#घोषणा HTT_MGMT_FRM_HDR_DOWNLOAD_LEN 32
काष्ठा htt_mgmt_tx_desc_qca99x0 अणु
	__le32 rate;
पूर्ण __packed;

काष्ठा htt_mgmt_tx_desc अणु
	u8 pad[माप(u32) - माप(काष्ठा htt_cmd_hdr)];
	__le32 msdu_paddr;
	__le32 desc_id;
	__le32 len;
	__le32 vdev_id;
	u8 hdr[HTT_MGMT_FRM_HDR_DOWNLOAD_LEN];
	जोड़ अणु
		काष्ठा htt_mgmt_tx_desc_qca99x0 qca99x0;
	पूर्ण __packed;
पूर्ण __packed;

क्रमागत htt_mgmt_tx_status अणु
	HTT_MGMT_TX_STATUS_OK    = 0,
	HTT_MGMT_TX_STATUS_RETRY = 1,
	HTT_MGMT_TX_STATUS_DROP  = 2
पूर्ण;

/*=== target -> host messages ===============================================*/

क्रमागत htt_मुख्य_t2h_msg_type अणु
	HTT_MAIN_T2H_MSG_TYPE_VERSION_CONF             = 0x0,
	HTT_MAIN_T2H_MSG_TYPE_RX_IND                   = 0x1,
	HTT_MAIN_T2H_MSG_TYPE_RX_FLUSH                 = 0x2,
	HTT_MAIN_T2H_MSG_TYPE_PEER_MAP                 = 0x3,
	HTT_MAIN_T2H_MSG_TYPE_PEER_UNMAP               = 0x4,
	HTT_MAIN_T2H_MSG_TYPE_RX_ADDBA                 = 0x5,
	HTT_MAIN_T2H_MSG_TYPE_RX_DELBA                 = 0x6,
	HTT_MAIN_T2H_MSG_TYPE_TX_COMPL_IND             = 0x7,
	HTT_MAIN_T2H_MSG_TYPE_PKTLOG                   = 0x8,
	HTT_MAIN_T2H_MSG_TYPE_STATS_CONF               = 0x9,
	HTT_MAIN_T2H_MSG_TYPE_RX_FRAG_IND              = 0xa,
	HTT_MAIN_T2H_MSG_TYPE_SEC_IND                  = 0xb,
	HTT_MAIN_T2H_MSG_TYPE_TX_INSPECT_IND           = 0xd,
	HTT_MAIN_T2H_MSG_TYPE_MGMT_TX_COMPL_IND        = 0xe,
	HTT_MAIN_T2H_MSG_TYPE_TX_CREDIT_UPDATE_IND     = 0xf,
	HTT_MAIN_T2H_MSG_TYPE_RX_PN_IND                = 0x10,
	HTT_MAIN_T2H_MSG_TYPE_RX_OFFLOAD_DELIVER_IND   = 0x11,
	HTT_MAIN_T2H_MSG_TYPE_TEST,
	/* keep this last */
	HTT_MAIN_T2H_NUM_MSGS
पूर्ण;

क्रमागत htt_10x_t2h_msg_type अणु
	HTT_10X_T2H_MSG_TYPE_VERSION_CONF              = 0x0,
	HTT_10X_T2H_MSG_TYPE_RX_IND                    = 0x1,
	HTT_10X_T2H_MSG_TYPE_RX_FLUSH                  = 0x2,
	HTT_10X_T2H_MSG_TYPE_PEER_MAP                  = 0x3,
	HTT_10X_T2H_MSG_TYPE_PEER_UNMAP                = 0x4,
	HTT_10X_T2H_MSG_TYPE_RX_ADDBA                  = 0x5,
	HTT_10X_T2H_MSG_TYPE_RX_DELBA                  = 0x6,
	HTT_10X_T2H_MSG_TYPE_TX_COMPL_IND              = 0x7,
	HTT_10X_T2H_MSG_TYPE_PKTLOG                    = 0x8,
	HTT_10X_T2H_MSG_TYPE_STATS_CONF                = 0x9,
	HTT_10X_T2H_MSG_TYPE_RX_FRAG_IND               = 0xa,
	HTT_10X_T2H_MSG_TYPE_SEC_IND                   = 0xb,
	HTT_10X_T2H_MSG_TYPE_RC_UPDATE_IND             = 0xc,
	HTT_10X_T2H_MSG_TYPE_TX_INSPECT_IND            = 0xd,
	HTT_10X_T2H_MSG_TYPE_TEST                      = 0xe,
	HTT_10X_T2H_MSG_TYPE_CHAN_CHANGE               = 0xf,
	HTT_10X_T2H_MSG_TYPE_AGGR_CONF                 = 0x11,
	HTT_10X_T2H_MSG_TYPE_STATS_NOUPLOAD            = 0x12,
	HTT_10X_T2H_MSG_TYPE_MGMT_TX_COMPL_IND         = 0x13,
	/* keep this last */
	HTT_10X_T2H_NUM_MSGS
पूर्ण;

क्रमागत htt_tlv_t2h_msg_type अणु
	HTT_TLV_T2H_MSG_TYPE_VERSION_CONF              = 0x0,
	HTT_TLV_T2H_MSG_TYPE_RX_IND                    = 0x1,
	HTT_TLV_T2H_MSG_TYPE_RX_FLUSH                  = 0x2,
	HTT_TLV_T2H_MSG_TYPE_PEER_MAP                  = 0x3,
	HTT_TLV_T2H_MSG_TYPE_PEER_UNMAP                = 0x4,
	HTT_TLV_T2H_MSG_TYPE_RX_ADDBA                  = 0x5,
	HTT_TLV_T2H_MSG_TYPE_RX_DELBA                  = 0x6,
	HTT_TLV_T2H_MSG_TYPE_TX_COMPL_IND              = 0x7,
	HTT_TLV_T2H_MSG_TYPE_PKTLOG                    = 0x8,
	HTT_TLV_T2H_MSG_TYPE_STATS_CONF                = 0x9,
	HTT_TLV_T2H_MSG_TYPE_RX_FRAG_IND               = 0xa,
	HTT_TLV_T2H_MSG_TYPE_SEC_IND                   = 0xb,
	HTT_TLV_T2H_MSG_TYPE_RC_UPDATE_IND             = 0xc, /* deprecated */
	HTT_TLV_T2H_MSG_TYPE_TX_INSPECT_IND            = 0xd,
	HTT_TLV_T2H_MSG_TYPE_MGMT_TX_COMPL_IND         = 0xe,
	HTT_TLV_T2H_MSG_TYPE_TX_CREDIT_UPDATE_IND      = 0xf,
	HTT_TLV_T2H_MSG_TYPE_RX_PN_IND                 = 0x10,
	HTT_TLV_T2H_MSG_TYPE_RX_OFFLOAD_DELIVER_IND    = 0x11,
	HTT_TLV_T2H_MSG_TYPE_RX_IN_ORD_PADDR_IND       = 0x12,
	/* 0x13 reservd */
	HTT_TLV_T2H_MSG_TYPE_WDI_IPA_OP_RESPONSE       = 0x14,
	HTT_TLV_T2H_MSG_TYPE_CHAN_CHANGE               = 0x15,
	HTT_TLV_T2H_MSG_TYPE_RX_OFLD_PKT_ERR           = 0x16,
	HTT_TLV_T2H_MSG_TYPE_TEST,
	/* keep this last */
	HTT_TLV_T2H_NUM_MSGS
पूर्ण;

क्रमागत htt_10_4_t2h_msg_type अणु
	HTT_10_4_T2H_MSG_TYPE_VERSION_CONF           = 0x0,
	HTT_10_4_T2H_MSG_TYPE_RX_IND                 = 0x1,
	HTT_10_4_T2H_MSG_TYPE_RX_FLUSH               = 0x2,
	HTT_10_4_T2H_MSG_TYPE_PEER_MAP               = 0x3,
	HTT_10_4_T2H_MSG_TYPE_PEER_UNMAP             = 0x4,
	HTT_10_4_T2H_MSG_TYPE_RX_ADDBA               = 0x5,
	HTT_10_4_T2H_MSG_TYPE_RX_DELBA               = 0x6,
	HTT_10_4_T2H_MSG_TYPE_TX_COMPL_IND           = 0x7,
	HTT_10_4_T2H_MSG_TYPE_PKTLOG                 = 0x8,
	HTT_10_4_T2H_MSG_TYPE_STATS_CONF             = 0x9,
	HTT_10_4_T2H_MSG_TYPE_RX_FRAG_IND            = 0xa,
	HTT_10_4_T2H_MSG_TYPE_SEC_IND                = 0xb,
	HTT_10_4_T2H_MSG_TYPE_RC_UPDATE_IND          = 0xc,
	HTT_10_4_T2H_MSG_TYPE_TX_INSPECT_IND         = 0xd,
	HTT_10_4_T2H_MSG_TYPE_MGMT_TX_COMPL_IND      = 0xe,
	HTT_10_4_T2H_MSG_TYPE_CHAN_CHANGE            = 0xf,
	HTT_10_4_T2H_MSG_TYPE_TX_CREDIT_UPDATE_IND   = 0x10,
	HTT_10_4_T2H_MSG_TYPE_RX_PN_IND              = 0x11,
	HTT_10_4_T2H_MSG_TYPE_RX_OFFLOAD_DELIVER_IND = 0x12,
	HTT_10_4_T2H_MSG_TYPE_TEST                   = 0x13,
	HTT_10_4_T2H_MSG_TYPE_EN_STATS               = 0x14,
	HTT_10_4_T2H_MSG_TYPE_AGGR_CONF              = 0x15,
	HTT_10_4_T2H_MSG_TYPE_TX_FETCH_IND           = 0x16,
	HTT_10_4_T2H_MSG_TYPE_TX_FETCH_CONFIRM       = 0x17,
	HTT_10_4_T2H_MSG_TYPE_STATS_NOUPLOAD         = 0x18,
	/* 0x19 to 0x2f are reserved */
	HTT_10_4_T2H_MSG_TYPE_TX_MODE_SWITCH_IND     = 0x30,
	HTT_10_4_T2H_MSG_TYPE_PEER_STATS	     = 0x31,
	/* keep this last */
	HTT_10_4_T2H_NUM_MSGS
पूर्ण;

क्रमागत htt_t2h_msg_type अणु
	HTT_T2H_MSG_TYPE_VERSION_CONF,
	HTT_T2H_MSG_TYPE_RX_IND,
	HTT_T2H_MSG_TYPE_RX_FLUSH,
	HTT_T2H_MSG_TYPE_PEER_MAP,
	HTT_T2H_MSG_TYPE_PEER_UNMAP,
	HTT_T2H_MSG_TYPE_RX_ADDBA,
	HTT_T2H_MSG_TYPE_RX_DELBA,
	HTT_T2H_MSG_TYPE_TX_COMPL_IND,
	HTT_T2H_MSG_TYPE_PKTLOG,
	HTT_T2H_MSG_TYPE_STATS_CONF,
	HTT_T2H_MSG_TYPE_RX_FRAG_IND,
	HTT_T2H_MSG_TYPE_SEC_IND,
	HTT_T2H_MSG_TYPE_RC_UPDATE_IND,
	HTT_T2H_MSG_TYPE_TX_INSPECT_IND,
	HTT_T2H_MSG_TYPE_MGMT_TX_COMPLETION,
	HTT_T2H_MSG_TYPE_TX_CREDIT_UPDATE_IND,
	HTT_T2H_MSG_TYPE_RX_PN_IND,
	HTT_T2H_MSG_TYPE_RX_OFFLOAD_DELIVER_IND,
	HTT_T2H_MSG_TYPE_RX_IN_ORD_PADDR_IND,
	HTT_T2H_MSG_TYPE_WDI_IPA_OP_RESPONSE,
	HTT_T2H_MSG_TYPE_CHAN_CHANGE,
	HTT_T2H_MSG_TYPE_RX_OFLD_PKT_ERR,
	HTT_T2H_MSG_TYPE_AGGR_CONF,
	HTT_T2H_MSG_TYPE_STATS_NOUPLOAD,
	HTT_T2H_MSG_TYPE_TEST,
	HTT_T2H_MSG_TYPE_EN_STATS,
	HTT_T2H_MSG_TYPE_TX_FETCH_IND,
	HTT_T2H_MSG_TYPE_TX_FETCH_CONFIRM,
	HTT_T2H_MSG_TYPE_TX_MODE_SWITCH_IND,
	HTT_T2H_MSG_TYPE_PEER_STATS,
	/* keep this last */
	HTT_T2H_NUM_MSGS
पूर्ण;

/*
 * htt_resp_hdr - header क्रम target-to-host messages
 *
 * msg_type: see htt_t2h_msg_type
 */
काष्ठा htt_resp_hdr अणु
	u8 msg_type;
पूर्ण __packed;

#घोषणा HTT_RESP_HDR_MSG_TYPE_OFFSET 0
#घोषणा HTT_RESP_HDR_MSG_TYPE_MASK   0xff
#घोषणा HTT_RESP_HDR_MSG_TYPE_LSB    0

/* htt_ver_resp - response sent क्रम htt_ver_req */
काष्ठा htt_ver_resp अणु
	u8 minor;
	u8 major;
	u8 rsvd0;
पूर्ण __packed;

#घोषणा HTT_MGMT_TX_CMPL_FLAG_ACK_RSSI BIT(0)

#घोषणा HTT_MGMT_TX_CMPL_INFO_ACK_RSSI_MASK	GENMASK(7, 0)

काष्ठा htt_mgmt_tx_completion अणु
	u8 rsvd0;
	u8 rsvd1;
	u8 flags;
	__le32 desc_id;
	__le32 status;
	__le32 ppdu_id;
	__le32 info;
पूर्ण __packed;

#घोषणा HTT_RX_INDICATION_INFO0_EXT_TID_MASK  (0x1F)
#घोषणा HTT_RX_INDICATION_INFO0_EXT_TID_LSB   (0)
#घोषणा HTT_RX_INDICATION_INFO0_FLUSH_VALID   (1 << 5)
#घोषणा HTT_RX_INDICATION_INFO0_RELEASE_VALID (1 << 6)
#घोषणा HTT_RX_INDICATION_INFO0_PPDU_DURATION BIT(7)

#घोषणा HTT_RX_INDICATION_INFO1_FLUSH_START_SEQNO_MASK   0x0000003F
#घोषणा HTT_RX_INDICATION_INFO1_FLUSH_START_SEQNO_LSB    0
#घोषणा HTT_RX_INDICATION_INFO1_FLUSH_END_SEQNO_MASK     0x00000FC0
#घोषणा HTT_RX_INDICATION_INFO1_FLUSH_END_SEQNO_LSB      6
#घोषणा HTT_RX_INDICATION_INFO1_RELEASE_START_SEQNO_MASK 0x0003F000
#घोषणा HTT_RX_INDICATION_INFO1_RELEASE_START_SEQNO_LSB  12
#घोषणा HTT_RX_INDICATION_INFO1_RELEASE_END_SEQNO_MASK   0x00FC0000
#घोषणा HTT_RX_INDICATION_INFO1_RELEASE_END_SEQNO_LSB    18
#घोषणा HTT_RX_INDICATION_INFO1_NUM_MPDU_RANGES_MASK     0xFF000000
#घोषणा HTT_RX_INDICATION_INFO1_NUM_MPDU_RANGES_LSB      24

#घोषणा HTT_TX_CMPL_FLAG_DATA_RSSI		BIT(0)
#घोषणा HTT_TX_CMPL_FLAG_PPID_PRESENT		BIT(1)
#घोषणा HTT_TX_CMPL_FLAG_PA_PRESENT		BIT(2)
#घोषणा HTT_TX_CMPL_FLAG_PPDU_DURATION_PRESENT	BIT(3)

#घोषणा HTT_TX_DATA_RSSI_ENABLE_WCN3990 BIT(3)
#घोषणा HTT_TX_DATA_APPEND_RETRIES BIT(0)
#घोषणा HTT_TX_DATA_APPEND_TIMESTAMP BIT(1)

काष्ठा htt_rx_indication_hdr अणु
	u8 info0; /* %HTT_RX_INDICATION_INFO0_ */
	__le16 peer_id;
	__le32 info1; /* %HTT_RX_INDICATION_INFO1_ */
पूर्ण __packed;

#घोषणा HTT_RX_INDICATION_INFO0_PHY_ERR_VALID    (1 << 0)
#घोषणा HTT_RX_INDICATION_INFO0_LEGACY_RATE_MASK (0x1E)
#घोषणा HTT_RX_INDICATION_INFO0_LEGACY_RATE_LSB  (1)
#घोषणा HTT_RX_INDICATION_INFO0_LEGACY_RATE_CCK  (1 << 5)
#घोषणा HTT_RX_INDICATION_INFO0_END_VALID        (1 << 6)
#घोषणा HTT_RX_INDICATION_INFO0_START_VALID      (1 << 7)

#घोषणा HTT_RX_INDICATION_INFO1_VHT_SIG_A1_MASK    0x00FFFFFF
#घोषणा HTT_RX_INDICATION_INFO1_VHT_SIG_A1_LSB     0
#घोषणा HTT_RX_INDICATION_INFO1_PREAMBLE_TYPE_MASK 0xFF000000
#घोषणा HTT_RX_INDICATION_INFO1_PREAMBLE_TYPE_LSB  24

#घोषणा HTT_RX_INDICATION_INFO2_VHT_SIG_A1_MASK 0x00FFFFFF
#घोषणा HTT_RX_INDICATION_INFO2_VHT_SIG_A1_LSB  0
#घोषणा HTT_RX_INDICATION_INFO2_SERVICE_MASK    0xFF000000
#घोषणा HTT_RX_INDICATION_INFO2_SERVICE_LSB     24

क्रमागत htt_rx_legacy_rate अणु
	HTT_RX_OFDM_48 = 0,
	HTT_RX_OFDM_24 = 1,
	HTT_RX_OFDM_12,
	HTT_RX_OFDM_6,
	HTT_RX_OFDM_54,
	HTT_RX_OFDM_36,
	HTT_RX_OFDM_18,
	HTT_RX_OFDM_9,

	/* दीर्घ preamble */
	HTT_RX_CCK_11_LP = 0,
	HTT_RX_CCK_5_5_LP = 1,
	HTT_RX_CCK_2_LP,
	HTT_RX_CCK_1_LP,
	/* लघु preamble */
	HTT_RX_CCK_11_SP,
	HTT_RX_CCK_5_5_SP,
	HTT_RX_CCK_2_SP
पूर्ण;

क्रमागत htt_rx_legacy_rate_type अणु
	HTT_RX_LEGACY_RATE_OFDM = 0,
	HTT_RX_LEGACY_RATE_CCK
पूर्ण;

क्रमागत htt_rx_preamble_type अणु
	HTT_RX_LEGACY        = 0x4,
	HTT_RX_HT            = 0x8,
	HTT_RX_HT_WITH_TXBF  = 0x9,
	HTT_RX_VHT           = 0xC,
	HTT_RX_VHT_WITH_TXBF = 0xD,
पूर्ण;

/*
 * Fields: phy_err_valid, phy_err_code, tsf,
 * usec_बारtamp, sub_usec_बारtamp
 * ..are valid only अगर end_valid == 1.
 *
 * Fields: rssi_chains, legacy_rate_type,
 * legacy_rate_cck, preamble_type, service,
 * vht_sig_*
 * ..are valid only अगर start_valid == 1;
 */
काष्ठा htt_rx_indication_ppdu अणु
	u8 combined_rssi;
	u8 sub_usec_बारtamp;
	u8 phy_err_code;
	u8 info0; /* HTT_RX_INDICATION_INFO0_ */
	काष्ठा अणु
		u8 pri20_db;
		u8 ext20_db;
		u8 ext40_db;
		u8 ext80_db;
	पूर्ण __packed rssi_chains[4];
	__le32 tsf;
	__le32 usec_बारtamp;
	__le32 info1; /* HTT_RX_INDICATION_INFO1_ */
	__le32 info2; /* HTT_RX_INDICATION_INFO2_ */
पूर्ण __packed;

क्रमागत htt_rx_mpdu_status अणु
	HTT_RX_IND_MPDU_STATUS_UNKNOWN = 0x0,
	HTT_RX_IND_MPDU_STATUS_OK,
	HTT_RX_IND_MPDU_STATUS_ERR_FCS,
	HTT_RX_IND_MPDU_STATUS_ERR_DUP,
	HTT_RX_IND_MPDU_STATUS_ERR_REPLAY,
	HTT_RX_IND_MPDU_STATUS_ERR_INV_PEER,
	/* only accept EAPOL frames */
	HTT_RX_IND_MPDU_STATUS_UNAUTH_PEER,
	HTT_RX_IND_MPDU_STATUS_OUT_OF_SYNC,
	/* Non-data in promiscuous mode */
	HTT_RX_IND_MPDU_STATUS_MGMT_CTRL,
	HTT_RX_IND_MPDU_STATUS_TKIP_MIC_ERR,
	HTT_RX_IND_MPDU_STATUS_DECRYPT_ERR,
	HTT_RX_IND_MPDU_STATUS_MPDU_LENGTH_ERR,
	HTT_RX_IND_MPDU_STATUS_ENCRYPT_REQUIRED_ERR,
	HTT_RX_IND_MPDU_STATUS_PRIVACY_ERR,

	/*
	 * MISC: discard क्रम unspecअगरied reasons.
	 * Leave this क्रमागत value last.
	 */
	HTT_RX_IND_MPDU_STATUS_ERR_MISC = 0xFF
पूर्ण;

काष्ठा htt_rx_indication_mpdu_range अणु
	u8 mpdu_count;
	u8 mpdu_range_status; /* %htt_rx_mpdu_status */
	u8 pad0;
	u8 pad1;
पूर्ण __packed;

काष्ठा htt_rx_indication_prefix अणु
	__le16 fw_rx_desc_bytes;
	u8 pad0;
	u8 pad1;
पूर्ण;

काष्ठा htt_rx_indication अणु
	काष्ठा htt_rx_indication_hdr hdr;
	काष्ठा htt_rx_indication_ppdu ppdu;
	काष्ठा htt_rx_indication_prefix prefix;

	/*
	 * the following fields are both dynamically sized, so
	 * take care addressing them
	 */

	/* the size of this is %fw_rx_desc_bytes */
	काष्ठा fw_rx_desc_base fw_desc;

	/*
	 * %mpdu_ranges starts after &%prefix + roundup(%fw_rx_desc_bytes, 4)
	 * and has %num_mpdu_ranges elements.
	 */
	काष्ठा htt_rx_indication_mpdu_range mpdu_ranges[];
पूर्ण __packed;

/* High latency version of the RX indication */
काष्ठा htt_rx_indication_hl अणु
	काष्ठा htt_rx_indication_hdr hdr;
	काष्ठा htt_rx_indication_ppdu ppdu;
	काष्ठा htt_rx_indication_prefix prefix;
	काष्ठा fw_rx_desc_hl fw_desc;
	काष्ठा htt_rx_indication_mpdu_range mpdu_ranges[];
पूर्ण __packed;

काष्ठा htt_hl_rx_desc अणु
	__le32 info;
	__le32 pn_31_0;
	जोड़ अणु
		काष्ठा अणु
			__le16 pn_47_32;
			__le16 pn_63_48;
		पूर्ण pn16;
		__le32 pn_63_32;
	पूर्ण u0;
	__le32 pn_95_64;
	__le32 pn_127_96;
पूर्ण __packed;

अटल अंतरभूत काष्ठा htt_rx_indication_mpdu_range *
		htt_rx_ind_get_mpdu_ranges(काष्ठा htt_rx_indication *rx_ind)
अणु
	व्योम *ptr = rx_ind;

	ptr += माप(rx_ind->hdr)
	     + माप(rx_ind->ppdu)
	     + माप(rx_ind->prefix)
	     + roundup(__le16_to_cpu(rx_ind->prefix.fw_rx_desc_bytes), 4);
	वापस ptr;
पूर्ण

अटल अंतरभूत काष्ठा htt_rx_indication_mpdu_range *
	htt_rx_ind_get_mpdu_ranges_hl(काष्ठा htt_rx_indication_hl *rx_ind)
अणु
	व्योम *ptr = rx_ind;

	ptr += माप(rx_ind->hdr)
	     + माप(rx_ind->ppdu)
	     + माप(rx_ind->prefix)
	     + माप(rx_ind->fw_desc);
	वापस ptr;
पूर्ण

क्रमागत htt_rx_flush_mpdu_status अणु
	HTT_RX_FLUSH_MPDU_DISCARD = 0,
	HTT_RX_FLUSH_MPDU_REORDER = 1,
पूर्ण;

/*
 * htt_rx_flush - discard or reorder given range of mpdus
 *
 * Note: host must check अगर all sequence numbers between
 *	[seq_num_start, seq_num_end-1] are valid.
 */
काष्ठा htt_rx_flush अणु
	__le16 peer_id;
	u8 tid;
	u8 rsvd0;
	u8 mpdu_status; /* %htt_rx_flush_mpdu_status */
	u8 seq_num_start; /* it is 6 LSBs of 802.11 seq no */
	u8 seq_num_end; /* it is 6 LSBs of 802.11 seq no */
पूर्ण;

काष्ठा htt_rx_peer_map अणु
	u8 vdev_id;
	__le16 peer_id;
	u8 addr[6];
	u8 rsvd0;
	u8 rsvd1;
पूर्ण __packed;

काष्ठा htt_rx_peer_unmap अणु
	u8 rsvd0;
	__le16 peer_id;
पूर्ण __packed;

क्रमागत htt_txrx_sec_cast_type अणु
	HTT_TXRX_SEC_MCAST = 0,
	HTT_TXRX_SEC_UCAST
पूर्ण;

क्रमागत htt_rx_pn_check_type अणु
	HTT_RX_NON_PN_CHECK = 0,
	HTT_RX_PN_CHECK
पूर्ण;

क्रमागत htt_rx_tkip_demic_type अणु
	HTT_RX_NON_TKIP_MIC = 0,
	HTT_RX_TKIP_MIC
पूर्ण;

क्रमागत htt_security_types अणु
	HTT_SECURITY_NONE,
	HTT_SECURITY_WEP128,
	HTT_SECURITY_WEP104,
	HTT_SECURITY_WEP40,
	HTT_SECURITY_TKIP,
	HTT_SECURITY_TKIP_NOMIC,
	HTT_SECURITY_AES_CCMP,
	HTT_SECURITY_WAPI,

	HTT_NUM_SECURITY_TYPES /* keep this last! */
पूर्ण;

#घोषणा ATH10K_HTT_TXRX_PEER_SECURITY_MAX 2
#घोषणा ATH10K_TXRX_NUM_EXT_TIDS 19
#घोषणा ATH10K_TXRX_NON_QOS_TID 16

क्रमागत htt_security_flags अणु
#घोषणा HTT_SECURITY_TYPE_MASK 0x7F
#घोषणा HTT_SECURITY_TYPE_LSB  0
	HTT_SECURITY_IS_UNICAST = 1 << 7
पूर्ण;

काष्ठा htt_security_indication अणु
	जोड़ अणु
		/* करोnt use bitfields; undefined behaviour */
		u8 flags; /* %htt_security_flags */
		काष्ठा अणु
			u8 security_type:7, /* %htt_security_types */
			   is_unicast:1;
		पूर्ण __packed;
	पूर्ण __packed;
	__le16 peer_id;
	u8 michael_key[8];
	u8 wapi_rsc[16];
पूर्ण __packed;

#घोषणा HTT_RX_BA_INFO0_TID_MASK     0x000F
#घोषणा HTT_RX_BA_INFO0_TID_LSB      0
#घोषणा HTT_RX_BA_INFO0_PEER_ID_MASK 0xFFF0
#घोषणा HTT_RX_BA_INFO0_PEER_ID_LSB  4

काष्ठा htt_rx_addba अणु
	u8 winकरोw_size;
	__le16 info0; /* %HTT_RX_BA_INFO0_ */
पूर्ण __packed;

काष्ठा htt_rx_delba अणु
	u8 rsvd0;
	__le16 info0; /* %HTT_RX_BA_INFO0_ */
पूर्ण __packed;

क्रमागत htt_data_tx_status अणु
	HTT_DATA_TX_STATUS_OK            = 0,
	HTT_DATA_TX_STATUS_DISCARD       = 1,
	HTT_DATA_TX_STATUS_NO_ACK        = 2,
	HTT_DATA_TX_STATUS_POSTPONE      = 3, /* HL only */
	HTT_DATA_TX_STATUS_DOWNLOAD_FAIL = 128
पूर्ण;

क्रमागत htt_data_tx_flags अणु
#घोषणा HTT_DATA_TX_STATUS_MASK 0x07
#घोषणा HTT_DATA_TX_STATUS_LSB  0
#घोषणा HTT_DATA_TX_TID_MASK    0x78
#घोषणा HTT_DATA_TX_TID_LSB     3
	HTT_DATA_TX_TID_INVALID = 1 << 7
पूर्ण;

#घोषणा HTT_TX_COMPL_INV_MSDU_ID 0xFFFF

काष्ठा htt_append_retries अणु
	__le16 msdu_id;
	u8 tx_retries;
	u8 flag;
पूर्ण __packed;

काष्ठा htt_data_tx_completion_ext अणु
	काष्ठा htt_append_retries a_retries;
	__le32 t_stamp;
	__le16 msdus_rssi[];
पूर्ण __packed;

/**
 * @brief target -> host TX completion indication message definition
 *
 * @details
 * The following diagram shows the क्रमmat of the TX completion indication sent
 * from the target to the host
 *
 *          |31 28|27|26|25|24|23        16| 15 |14 11|10   8|7          0|
 *          |-------------------------------------------------------------|
 * header:  |rsvd |A2|TP|A1|A0|     num    | t_i| tid |status|  msg_type  |
 *          |-------------------------------------------------------------|
 * payload: |            MSDU1 ID          |         MSDU0 ID             |
 *          |-------------------------------------------------------------|
 *          :            MSDU3 ID          :         MSDU2 ID             :
 *          |-------------------------------------------------------------|
 *          |          काष्ठा htt_tx_compl_ind_append_retries             |
 *          |- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -|
 *          |          काष्ठा htt_tx_compl_ind_append_tx_tstamp           |
 *          |- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -|
 *          |           MSDU1 ACK RSSI     |        MSDU0 ACK RSSI        |
 *          |-------------------------------------------------------------|
 *          :           MSDU3 ACK RSSI     :        MSDU2 ACK RSSI        :
 *          |- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -|
 *    -msg_type
 *     Bits 7:0
 *     Purpose: identअगरies this as HTT TX completion indication
 *    -status
 *     Bits 10:8
 *     Purpose: the TX completion status of payload fragmentations descriptors
 *     Value: could be HTT_TX_COMPL_IND_STAT_OK or HTT_TX_COMPL_IND_STAT_DISCARD
 *    -tid
 *     Bits 14:11
 *     Purpose: the tid associated with those fragmentation descriptors. It is
 *     valid or not, depending on the tid_invalid bit.
 *     Value: 0 to 15
 *    -tid_invalid
 *     Bits 15:15
 *     Purpose: this bit indicates whether the tid field is valid or not
 *     Value: 0 indicates valid, 1 indicates invalid
 *    -num
 *     Bits 23:16
 *     Purpose: the number of payload in this indication
 *     Value: 1 to 255
 *    -A0 = append
 *     Bits 24:24
 *     Purpose: append the काष्ठा htt_tx_compl_ind_append_retries which contains
 *            the number of tx retries क्रम one MSDU at the end of this message
 *     Value: 0 indicates no appending, 1 indicates appending
 *    -A1 = append1
 *     Bits 25:25
 *     Purpose: Append the काष्ठा htt_tx_compl_ind_append_tx_tstamp which
 *            contains the बारtamp info क्रम each TX msdu id in payload.
 *     Value: 0 indicates no appending, 1 indicates appending
 *    -TP = MSDU tx घातer presence
 *     Bits 26:26
 *     Purpose: Indicate whether the TX_COMPL_IND includes a tx घातer report
 *            क्रम each MSDU referenced by the TX_COMPL_IND message.
 *            The order of the per-MSDU tx घातer reports matches the order
 *            of the MSDU IDs.
 *     Value: 0 indicates not appending, 1 indicates appending
 *    -A2 = append2
 *     Bits 27:27
 *     Purpose: Indicate whether data ACK RSSI is appended क्रम each MSDU in
 *            TX_COMP_IND message.  The order of the per-MSDU ACK RSSI report
 *            matches the order of the MSDU IDs.
 *            The ACK RSSI values are valid when status is COMPLETE_OK (and
 *            this append2 bit is set).
 *     Value: 0 indicates not appending, 1 indicates appending
 */

काष्ठा htt_data_tx_completion अणु
	जोड़ अणु
		u8 flags;
		काष्ठा अणु
			u8 status:3,
			   tid:4,
			   tid_invalid:1;
		पूर्ण __packed;
	पूर्ण __packed;
	u8 num_msdus;
	u8 flags2; /* HTT_TX_CMPL_FLAG_DATA_RSSI */
	__le16 msdus[]; /* variable length based on %num_msdus */
पूर्ण __packed;

#घोषणा HTT_TX_PPDU_DUR_INFO0_PEER_ID_MASK	GENMASK(15, 0)
#घोषणा HTT_TX_PPDU_DUR_INFO0_TID_MASK		GENMASK(20, 16)

काष्ठा htt_data_tx_ppdu_dur अणु
	__le32 info0; /* HTT_TX_PPDU_DUR_INFO0_ */
	__le32 tx_duration; /* in usecs */
पूर्ण __packed;

#घोषणा HTT_TX_COMPL_PPDU_DUR_INFO0_NUM_ENTRIES_MASK	GENMASK(7, 0)

काष्ठा htt_data_tx_compl_ppdu_dur अणु
	__le32 info0; /* HTT_TX_COMPL_PPDU_DUR_INFO0_ */
	काष्ठा htt_data_tx_ppdu_dur ppdu_dur[];
पूर्ण __packed;

काष्ठा htt_tx_compl_ind_base अणु
	u32 hdr;
	u16 payload[1/*or more*/];
पूर्ण __packed;

काष्ठा htt_rc_tx_करोne_params अणु
	u32 rate_code;
	u32 rate_code_flags;
	u32 flags;
	u32 num_enqued; /* 1 क्रम non-AMPDU */
	u32 num_retries;
	u32 num_failed; /* क्रम AMPDU */
	u32 ack_rssi;
	u32 समय_stamp;
	u32 is_probe;
पूर्ण;

काष्ठा htt_rc_update अणु
	u8 vdev_id;
	__le16 peer_id;
	u8 addr[6];
	u8 num_elems;
	u8 rsvd0;
	काष्ठा htt_rc_tx_करोne_params params[]; /* variable length %num_elems */
पूर्ण __packed;

/* see htt_rx_indication क्रम similar fields and descriptions */
काष्ठा htt_rx_fragment_indication अणु
	जोड़ अणु
		u8 info0; /* %HTT_RX_FRAG_IND_INFO0_ */
		काष्ठा अणु
			u8 ext_tid:5,
			   flush_valid:1;
		पूर्ण __packed;
	पूर्ण __packed;
	__le16 peer_id;
	__le32 info1; /* %HTT_RX_FRAG_IND_INFO1_ */
	__le16 fw_rx_desc_bytes;
	__le16 rsvd0;

	u8 fw_msdu_rx_desc[];
पूर्ण __packed;

#घोषणा ATH10K_IEEE80211_EXTIV               BIT(5)
#घोषणा ATH10K_IEEE80211_TKIP_MICLEN         8   /* trailing MIC */

#घोषणा HTT_RX_FRAG_IND_INFO0_HEADER_LEN     16

#घोषणा HTT_RX_FRAG_IND_INFO0_EXT_TID_MASK     0x1F
#घोषणा HTT_RX_FRAG_IND_INFO0_EXT_TID_LSB      0
#घोषणा HTT_RX_FRAG_IND_INFO0_FLUSH_VALID_MASK 0x20
#घोषणा HTT_RX_FRAG_IND_INFO0_FLUSH_VALID_LSB  5

#घोषणा HTT_RX_FRAG_IND_INFO1_FLUSH_SEQ_NUM_START_MASK 0x0000003F
#घोषणा HTT_RX_FRAG_IND_INFO1_FLUSH_SEQ_NUM_START_LSB  0
#घोषणा HTT_RX_FRAG_IND_INFO1_FLUSH_SEQ_NUM_END_MASK   0x00000FC0
#घोषणा HTT_RX_FRAG_IND_INFO1_FLUSH_SEQ_NUM_END_LSB    6

काष्ठा htt_rx_pn_ind अणु
	__le16 peer_id;
	u8 tid;
	u8 seqno_start;
	u8 seqno_end;
	u8 pn_ie_count;
	u8 reserved;
	u8 pn_ies[];
पूर्ण __packed;

काष्ठा htt_rx_offload_msdu अणु
	__le16 msdu_len;
	__le16 peer_id;
	u8 vdev_id;
	u8 tid;
	u8 fw_desc;
	u8 payload[];
पूर्ण __packed;

काष्ठा htt_rx_offload_ind अणु
	u8 reserved;
	__le16 msdu_count;
पूर्ण __packed;

काष्ठा htt_rx_in_ord_msdu_desc अणु
	__le32 msdu_paddr;
	__le16 msdu_len;
	u8 fw_desc;
	u8 reserved;
पूर्ण __packed;

काष्ठा htt_rx_in_ord_msdu_desc_ext अणु
	__le64 msdu_paddr;
	__le16 msdu_len;
	u8 fw_desc;
	u8 reserved;
पूर्ण __packed;

काष्ठा htt_rx_in_ord_ind अणु
	u8 info;
	__le16 peer_id;
	u8 vdev_id;
	u8 reserved;
	__le16 msdu_count;
	जोड़ अणु
		काष्ठा htt_rx_in_ord_msdu_desc msdu_descs32[0];
		काष्ठा htt_rx_in_ord_msdu_desc_ext msdu_descs64[0];
	पूर्ण __packed;
पूर्ण __packed;

#घोषणा HTT_RX_IN_ORD_IND_INFO_TID_MASK		0x0000001f
#घोषणा HTT_RX_IN_ORD_IND_INFO_TID_LSB		0
#घोषणा HTT_RX_IN_ORD_IND_INFO_OFFLOAD_MASK	0x00000020
#घोषणा HTT_RX_IN_ORD_IND_INFO_OFFLOAD_LSB	5
#घोषणा HTT_RX_IN_ORD_IND_INFO_FRAG_MASK	0x00000040
#घोषणा HTT_RX_IN_ORD_IND_INFO_FRAG_LSB		6

/*
 * target -> host test message definition
 *
 * The following field definitions describe the क्रमmat of the test
 * message sent from the target to the host.
 * The message consists of a 4-octet header, followed by a variable
 * number of 32-bit पूर्णांकeger values, followed by a variable number
 * of 8-bit अक्षरacter values.
 *
 * |31                         16|15           8|7            0|
 * |-----------------------------------------------------------|
 * |          num अक्षरs          |   num पूर्णांकs   |   msg type   |
 * |-----------------------------------------------------------|
 * |                           पूर्णांक 0                           |
 * |-----------------------------------------------------------|
 * |                           पूर्णांक 1                           |
 * |-----------------------------------------------------------|
 * |                            ...                            |
 * |-----------------------------------------------------------|
 * |    अक्षर 3    |    अक्षर 2    |    अक्षर 1    |    अक्षर 0    |
 * |-----------------------------------------------------------|
 * |              |              |      ...     |    अक्षर 4    |
 * |-----------------------------------------------------------|
 *   - MSG_TYPE
 *     Bits 7:0
 *     Purpose: identअगरies this as a test message
 *     Value: HTT_MSG_TYPE_TEST
 *   - NUM_INTS
 *     Bits 15:8
 *     Purpose: indicate how many 32-bit पूर्णांकegers follow the message header
 *   - NUM_CHARS
 *     Bits 31:16
 *     Purpose: indicate how many 8-bit अक्षरacters follow the series of पूर्णांकegers
 */
काष्ठा htt_rx_test अणु
	u8 num_पूर्णांकs;
	__le16 num_अक्षरs;

	/* payload consists of 2 lists:
	 *  a) num_पूर्णांकs * माप(__le32)
	 *  b) num_अक्षरs * माप(u8) aligned to 4bytes
	 */
	u8 payload[];
पूर्ण __packed;

अटल अंतरभूत __le32 *htt_rx_test_get_पूर्णांकs(काष्ठा htt_rx_test *rx_test)
अणु
	वापस (__le32 *)rx_test->payload;
पूर्ण

अटल अंतरभूत u8 *htt_rx_test_get_अक्षरs(काष्ठा htt_rx_test *rx_test)
अणु
	वापस rx_test->payload + (rx_test->num_पूर्णांकs * माप(__le32));
पूर्ण

/*
 * target -> host packet log message
 *
 * The following field definitions describe the क्रमmat of the packet log
 * message sent from the target to the host.
 * The message consists of a 4-octet header,followed by a variable number
 * of 32-bit अक्षरacter values.
 *
 * |31          24|23          16|15           8|7            0|
 * |-----------------------------------------------------------|
 * |              |              |              |   msg type   |
 * |-----------------------------------------------------------|
 * |                        payload                            |
 * |-----------------------------------------------------------|
 *   - MSG_TYPE
 *     Bits 7:0
 *     Purpose: identअगरies this as a test message
 *     Value: HTT_MSG_TYPE_PACKETLOG
 */
काष्ठा htt_pktlog_msg अणु
	u8 pad[3];
	u8 payload[];
पूर्ण __packed;

काष्ठा htt_dbg_stats_rx_reorder_stats अणु
	/* Non QoS MPDUs received */
	__le32 deliver_non_qos;

	/* MPDUs received in-order */
	__le32 deliver_in_order;

	/* Flush due to reorder समयr expired */
	__le32 deliver_flush_समयout;

	/* Flush due to move out of winकरोw */
	__le32 deliver_flush_oow;

	/* Flush due to DELBA */
	__le32 deliver_flush_delba;

	/* MPDUs dropped due to FCS error */
	__le32 fcs_error;

	/* MPDUs dropped due to monitor mode non-data packet */
	__le32 mgmt_ctrl;

	/* MPDUs dropped due to invalid peer */
	__le32 invalid_peer;

	/* MPDUs dropped due to duplication (non aggregation) */
	__le32 dup_non_aggr;

	/* MPDUs dropped due to processed beक्रमe */
	__le32 dup_past;

	/* MPDUs dropped due to duplicate in reorder queue */
	__le32 dup_in_reorder;

	/* Reorder समयout happened */
	__le32 reorder_समयout;

	/* invalid bar ssn */
	__le32 invalid_bar_ssn;

	/* reorder reset due to bar ssn */
	__le32 ssn_reset;
पूर्ण;

काष्ठा htt_dbg_stats_wal_tx_stats अणु
	/* Num HTT cookies queued to dispatch list */
	__le32 comp_queued;

	/* Num HTT cookies dispatched */
	__le32 comp_delivered;

	/* Num MSDU queued to WAL */
	__le32 msdu_enqued;

	/* Num MPDU queue to WAL */
	__le32 mpdu_enqued;

	/* Num MSDUs dropped by WMM limit */
	__le32 wmm_drop;

	/* Num Local frames queued */
	__le32 local_enqued;

	/* Num Local frames करोne */
	__le32 local_मुक्तd;

	/* Num queued to HW */
	__le32 hw_queued;

	/* Num PPDU reaped from HW */
	__le32 hw_reaped;

	/* Num underruns */
	__le32 underrun;

	/* Num PPDUs cleaned up in TX पात */
	__le32 tx_पात;

	/* Num MPDUs requed by SW */
	__le32 mpdus_requed;

	/* excessive retries */
	__le32 tx_ko;

	/* data hw rate code */
	__le32 data_rc;

	/* Scheduler self triggers */
	__le32 self_triggers;

	/* frames dropped due to excessive sw retries */
	__le32 sw_retry_failure;

	/* illegal rate phy errors  */
	__le32 illgl_rate_phy_err;

	/* wal pdev continuous xretry */
	__le32 pdev_cont_xretry;

	/* wal pdev continuous xretry */
	__le32 pdev_tx_समयout;

	/* wal pdev resets  */
	__le32 pdev_resets;

	__le32 phy_underrun;

	/* MPDU is more than txop limit */
	__le32 txop_ovf;
पूर्ण __packed;

काष्ठा htt_dbg_stats_wal_rx_stats अणु
	/* Cnts any change in ring routing mid-ppdu */
	__le32 mid_ppdu_route_change;

	/* Total number of statuses processed */
	__le32 status_rcvd;

	/* Extra frags on rings 0-3 */
	__le32 r0_frags;
	__le32 r1_frags;
	__le32 r2_frags;
	__le32 r3_frags;

	/* MSDUs / MPDUs delivered to HTT */
	__le32 htt_msdus;
	__le32 htt_mpdus;

	/* MSDUs / MPDUs delivered to local stack */
	__le32 loc_msdus;
	__le32 loc_mpdus;

	/* AMSDUs that have more MSDUs than the status ring size */
	__le32 oversize_amsdu;

	/* Number of PHY errors */
	__le32 phy_errs;

	/* Number of PHY errors drops */
	__le32 phy_err_drop;

	/* Number of mpdu errors - FCS, MIC, ENC etc. */
	__le32 mpdu_errs;
पूर्ण __packed;

काष्ठा htt_dbg_stats_wal_peer_stats अणु
	__le32 dummy; /* REMOVE THIS ONCE REAL PEER STAT COUNTERS ARE ADDED */
पूर्ण __packed;

काष्ठा htt_dbg_stats_wal_pdev_txrx अणु
	काष्ठा htt_dbg_stats_wal_tx_stats tx_stats;
	काष्ठा htt_dbg_stats_wal_rx_stats rx_stats;
	काष्ठा htt_dbg_stats_wal_peer_stats peer_stats;
पूर्ण __packed;

काष्ठा htt_dbg_stats_rx_rate_info अणु
	__le32 mcs[10];
	__le32 sgi[10];
	__le32 nss[4];
	__le32 stbc[10];
	__le32 bw[3];
	__le32 pream[6];
	__le32 ldpc;
	__le32 txbf;
पूर्ण;

/*
 * htt_dbg_stats_status -
 * present -     The requested stats have been delivered in full.
 *               This indicates that either the stats inक्रमmation was contained
 *               in its entirety within this message, or अन्यथा this message
 *               completes the delivery of the requested stats info that was
 *               partially delivered through earlier STATS_CONF messages.
 * partial -     The requested stats have been delivered in part.
 *               One or more subsequent STATS_CONF messages with the same
 *               cookie value will be sent to deliver the reमुख्यder of the
 *               inक्रमmation.
 * error -       The requested stats could not be delivered, क्रम example due
 *               to a लघुage of memory to स्थिरruct a message holding the
 *               requested stats.
 * invalid -     The requested stat type is either not recognized, or the
 *               target is configured to not gather the stats type in question.
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * series_करोne - This special value indicates that no further stats info
 *               elements are present within a series of stats info elems
 *               (within a stats upload confirmation message).
 */
क्रमागत htt_dbg_stats_status अणु
	HTT_DBG_STATS_STATUS_PRESENT     = 0,
	HTT_DBG_STATS_STATUS_PARTIAL     = 1,
	HTT_DBG_STATS_STATUS_ERROR       = 2,
	HTT_DBG_STATS_STATUS_INVALID     = 3,
	HTT_DBG_STATS_STATUS_SERIES_DONE = 7
पूर्ण;

/*
 * target -> host statistics upload
 *
 * The following field definitions describe the क्रमmat of the HTT target
 * to host stats upload confirmation message.
 * The message contains a cookie echoed from the HTT host->target stats
 * upload request, which identअगरies which request the confirmation is
 * क्रम, and a series of tag-length-value stats inक्रमmation elements.
 * The tag-length header क्रम each stats info element also includes a
 * status field, to indicate whether the request क्रम the stat type in
 * question was fully met, partially met, unable to be met, or invalid
 * (अगर the stat type in question is disabled in the target).
 * A special value of all 1's in this status field is used to indicate
 * the end of the series of stats info elements.
 *
 *
 * |31                         16|15           8|7   5|4       0|
 * |------------------------------------------------------------|
 * |                  reserved                  |    msg type   |
 * |------------------------------------------------------------|
 * |                        cookie LSBs                         |
 * |------------------------------------------------------------|
 * |                        cookie MSBs                         |
 * |------------------------------------------------------------|
 * |      stats entry length     |   reserved   |  S  |stat type|
 * |------------------------------------------------------------|
 * |                                                            |
 * |                  type-specअगरic stats info                  |
 * |                                                            |
 * |------------------------------------------------------------|
 * |      stats entry length     |   reserved   |  S  |stat type|
 * |------------------------------------------------------------|
 * |                                                            |
 * |                  type-specअगरic stats info                  |
 * |                                                            |
 * |------------------------------------------------------------|
 * |              n/a            |   reserved   | 111 |   n/a   |
 * |------------------------------------------------------------|
 * Header fields:
 *  - MSG_TYPE
 *    Bits 7:0
 *    Purpose: identअगरies this is a statistics upload confirmation message
 *    Value: 0x9
 *  - COOKIE_LSBS
 *    Bits 31:0
 *    Purpose: Provide a mechanism to match a target->host stats confirmation
 *        message with its preceding host->target stats request message.
 *    Value: LSBs of the opaque cookie specअगरied by the host-side requestor
 *  - COOKIE_MSBS
 *    Bits 31:0
 *    Purpose: Provide a mechanism to match a target->host stats confirmation
 *        message with its preceding host->target stats request message.
 *    Value: MSBs of the opaque cookie specअगरied by the host-side requestor
 *
 * Stats Inक्रमmation Element tag-length header fields:
 *  - STAT_TYPE
 *    Bits 4:0
 *    Purpose: identअगरies the type of statistics info held in the
 *        following inक्रमmation element
 *    Value: htt_dbg_stats_type
 *  - STATUS
 *    Bits 7:5
 *    Purpose: indicate whether the requested stats are present
 *    Value: htt_dbg_stats_status, including a special value (0x7) to mark
 *        the completion of the stats entry series
 *  - LENGTH
 *    Bits 31:16
 *    Purpose: indicate the stats inक्रमmation size
 *    Value: This field specअगरies the number of bytes of stats inक्रमmation
 *       that follows the element tag-length header.
 *       It is expected but not required that this length is a multiple of
 *       4 bytes.  Even अगर the length is not an पूर्णांकeger multiple of 4, the
 *       subsequent stats entry header will begin on a 4-byte aligned
 *       boundary.
 */

#घोषणा HTT_STATS_CONF_ITEM_INFO_STAT_TYPE_MASK 0x1F
#घोषणा HTT_STATS_CONF_ITEM_INFO_STAT_TYPE_LSB  0
#घोषणा HTT_STATS_CONF_ITEM_INFO_STATUS_MASK    0xE0
#घोषणा HTT_STATS_CONF_ITEM_INFO_STATUS_LSB     5

काष्ठा htt_stats_conf_item अणु
	जोड़ अणु
		u8 info;
		काष्ठा अणु
			u8 stat_type:5; /* %HTT_DBG_STATS_ */
			u8 status:3; /* %HTT_DBG_STATS_STATUS_ */
		पूर्ण __packed;
	पूर्ण __packed;
	u8 pad;
	__le16 length;
	u8 payload[]; /* roundup(length, 4) दीर्घ */
पूर्ण __packed;

काष्ठा htt_stats_conf अणु
	u8 pad[3];
	__le32 cookie_lsb;
	__le32 cookie_msb;

	/* each item has variable length! */
	काष्ठा htt_stats_conf_item items[];
पूर्ण __packed;

अटल अंतरभूत काष्ठा htt_stats_conf_item *htt_stats_conf_next_item(
					स्थिर काष्ठा htt_stats_conf_item *item)
अणु
	वापस (व्योम *)item + माप(*item) + roundup(item->length, 4);
पूर्ण

/*
 * host -> target FRAG DESCRIPTOR/MSDU_EXT DESC bank
 *
 * The following field definitions describe the क्रमmat of the HTT host
 * to target frag_desc/msdu_ext bank configuration message.
 * The message contains the based address and the min and max id of the
 * MSDU_EXT/FRAG_DESC that will be used by the HTT to map MSDU DESC and
 * MSDU_EXT/FRAG_DESC.
 * HTT will use id in HTT descriptor instead sending the frag_desc_ptr.
 * For QCA988X HW the firmware will use fragment_desc_ptr but in WIFI2.0
 * the hardware करोes the mapping/translation.
 *
 * Total banks that can be configured is configured to 16.
 *
 * This should be called beक्रमe any TX has be initiated by the HTT
 *
 * |31                         16|15           8|7   5|4       0|
 * |------------------------------------------------------------|
 * | DESC_SIZE    |  NUM_BANKS   | RES |SWP|pdev|    msg type   |
 * |------------------------------------------------------------|
 * |                     BANK0_BASE_ADDRESS                     |
 * |------------------------------------------------------------|
 * |                            ...                             |
 * |------------------------------------------------------------|
 * |                    BANK15_BASE_ADDRESS                     |
 * |------------------------------------------------------------|
 * |       BANK0_MAX_ID          |       BANK0_MIN_ID           |
 * |------------------------------------------------------------|
 * |                            ...                             |
 * |------------------------------------------------------------|
 * |       BANK15_MAX_ID         |       BANK15_MIN_ID          |
 * |------------------------------------------------------------|
 * Header fields:
 *  - MSG_TYPE
 *    Bits 7:0
 *    Value: 0x6
 *  - BANKx_BASE_ADDRESS
 *    Bits 31:0
 *    Purpose: Provide a mechanism to specअगरy the base address of the MSDU_EXT
 *         bank physical/bus address.
 *  - BANKx_MIN_ID
 *    Bits 15:0
 *    Purpose: Provide a mechanism to specअगरy the min index that needs to
 *          mapped.
 *  - BANKx_MAX_ID
 *    Bits 31:16
 *    Purpose: Provide a mechanism to specअगरy the max index that needs to
 *
 */
काष्ठा htt_frag_desc_bank_id अणु
	__le16 bank_min_id;
	__le16 bank_max_id;
पूर्ण __packed;

/* real is 16 but it wouldn't fit in the max htt message size
 * so we use a conservatively safe value क्रम now
 */
#घोषणा HTT_FRAG_DESC_BANK_MAX 4

#घोषणा HTT_FRAG_DESC_BANK_CFG_INFO_PDEV_ID_MASK		0x03
#घोषणा HTT_FRAG_DESC_BANK_CFG_INFO_PDEV_ID_LSB			0
#घोषणा HTT_FRAG_DESC_BANK_CFG_INFO_SWAP			BIT(2)
#घोषणा HTT_FRAG_DESC_BANK_CFG_INFO_Q_STATE_VALID		BIT(3)
#घोषणा HTT_FRAG_DESC_BANK_CFG_INFO_Q_STATE_DEPTH_TYPE_MASK	BIT(4)
#घोषणा HTT_FRAG_DESC_BANK_CFG_INFO_Q_STATE_DEPTH_TYPE_LSB	4

क्रमागत htt_q_depth_type अणु
	HTT_Q_DEPTH_TYPE_BYTES = 0,
	HTT_Q_DEPTH_TYPE_MSDUS = 1,
पूर्ण;

#घोषणा HTT_TX_Q_STATE_NUM_PEERS		(TARGET_10_4_NUM_QCACHE_PEERS_MAX + \
						 TARGET_10_4_NUM_VDEVS)
#घोषणा HTT_TX_Q_STATE_NUM_TIDS			8
#घोषणा HTT_TX_Q_STATE_ENTRY_SIZE		1
#घोषणा HTT_TX_Q_STATE_ENTRY_MULTIPLIER		0

/**
 * htt_q_state_conf - part of htt_frag_desc_bank_cfg क्रम host q state config
 *
 * Defines host q state क्रमmat and behavior. See htt_q_state.
 *
 * @record_size: Defines the size of each host q entry in bytes. In practice
 *	however firmware (at least 10.4.3-00191) ignores this host
 *	configuration value and uses hardcoded value of 1.
 * @record_multiplier: This is valid only when q depth type is MSDUs. It
 *	defines the exponent क्रम the घातer of 2 multiplication.
 */
काष्ठा htt_q_state_conf अणु
	__le32 paddr;
	__le16 num_peers;
	__le16 num_tids;
	u8 record_size;
	u8 record_multiplier;
	u8 pad[2];
पूर्ण __packed;

काष्ठा htt_frag_desc_bank_cfg32 अणु
	u8 info; /* HTT_FRAG_DESC_BANK_CFG_INFO_ */
	u8 num_banks;
	u8 desc_size;
	__le32 bank_base_addrs[HTT_FRAG_DESC_BANK_MAX];
	काष्ठा htt_frag_desc_bank_id bank_id[HTT_FRAG_DESC_BANK_MAX];
	काष्ठा htt_q_state_conf q_state;
पूर्ण __packed;

काष्ठा htt_frag_desc_bank_cfg64 अणु
	u8 info; /* HTT_FRAG_DESC_BANK_CFG_INFO_ */
	u8 num_banks;
	u8 desc_size;
	__le64 bank_base_addrs[HTT_FRAG_DESC_BANK_MAX];
	काष्ठा htt_frag_desc_bank_id bank_id[HTT_FRAG_DESC_BANK_MAX];
	काष्ठा htt_q_state_conf q_state;
पूर्ण __packed;

#घोषणा HTT_TX_Q_STATE_ENTRY_COEFFICIENT	128
#घोषणा HTT_TX_Q_STATE_ENTRY_FACTOR_MASK	0x3f
#घोषणा HTT_TX_Q_STATE_ENTRY_FACTOR_LSB		0
#घोषणा HTT_TX_Q_STATE_ENTRY_EXP_MASK		0xc0
#घोषणा HTT_TX_Q_STATE_ENTRY_EXP_LSB		6

/**
 * htt_q_state - shared between host and firmware via DMA
 *
 * This काष्ठाure is used क्रम the host to expose it's software queue state to
 * firmware so that its rate control can schedule fetch requests क्रम optimized
 * perक्रमmance. This is most notably used क्रम MU-MIMO aggregation when multiple
 * MU clients are connected.
 *
 * @count: Each element defines the host queue depth. When q depth type was
 *	configured as HTT_Q_DEPTH_TYPE_BYTES then each entry is defined as:
 *	FACTOR * 128 * 8^EXP (see HTT_TX_Q_STATE_ENTRY_FACTOR_MASK and
 *	HTT_TX_Q_STATE_ENTRY_EXP_MASK). When q depth type was configured as
 *	HTT_Q_DEPTH_TYPE_MSDUS the number of packets is scaled by 2 **
 *	record_multiplier (see htt_q_state_conf).
 * @map: Used by firmware to quickly check which host queues are not empty. It
 *	is a biपंचांगap simply saying.
 * @seq: Used by firmware to quickly check अगर the host queues were updated
 *	since it last checked.
 *
 * FIXME: Is the q_state map[] size calculation really correct?
 */
काष्ठा htt_q_state अणु
	u8 count[HTT_TX_Q_STATE_NUM_TIDS][HTT_TX_Q_STATE_NUM_PEERS];
	u32 map[HTT_TX_Q_STATE_NUM_TIDS][(HTT_TX_Q_STATE_NUM_PEERS + 31) / 32];
	__le32 seq;
पूर्ण __packed;

#घोषणा HTT_TX_FETCH_RECORD_INFO_PEER_ID_MASK	0x0fff
#घोषणा HTT_TX_FETCH_RECORD_INFO_PEER_ID_LSB	0
#घोषणा HTT_TX_FETCH_RECORD_INFO_TID_MASK	0xf000
#घोषणा HTT_TX_FETCH_RECORD_INFO_TID_LSB	12

काष्ठा htt_tx_fetch_record अणु
	__le16 info; /* HTT_TX_FETCH_IND_RECORD_INFO_ */
	__le16 num_msdus;
	__le32 num_bytes;
पूर्ण __packed;

काष्ठा htt_tx_fetch_ind अणु
	u8 pad0;
	__le16 fetch_seq_num;
	__le32 token;
	__le16 num_resp_ids;
	__le16 num_records;
	__le32 resp_ids[0]; /* ath10k_htt_get_tx_fetch_ind_resp_ids() */
	काष्ठा htt_tx_fetch_record records[];
पूर्ण __packed;

अटल अंतरभूत व्योम *
ath10k_htt_get_tx_fetch_ind_resp_ids(काष्ठा htt_tx_fetch_ind *ind)
अणु
	वापस (व्योम *)&ind->records[le16_to_cpu(ind->num_records)];
पूर्ण

काष्ठा htt_tx_fetch_resp अणु
	u8 pad0;
	__le16 resp_id;
	__le16 fetch_seq_num;
	__le16 num_records;
	__le32 token;
	काष्ठा htt_tx_fetch_record records[];
पूर्ण __packed;

काष्ठा htt_tx_fetch_confirm अणु
	u8 pad0;
	__le16 num_resp_ids;
	__le32 resp_ids[];
पूर्ण __packed;

क्रमागत htt_tx_mode_चयन_mode अणु
	HTT_TX_MODE_SWITCH_PUSH = 0,
	HTT_TX_MODE_SWITCH_PUSH_PULL = 1,
पूर्ण;

#घोषणा HTT_TX_MODE_SWITCH_IND_INFO0_ENABLE		BIT(0)
#घोषणा HTT_TX_MODE_SWITCH_IND_INFO0_NUM_RECORDS_MASK	0xfffe
#घोषणा HTT_TX_MODE_SWITCH_IND_INFO0_NUM_RECORDS_LSB	1

#घोषणा HTT_TX_MODE_SWITCH_IND_INFO1_MODE_MASK		0x0003
#घोषणा HTT_TX_MODE_SWITCH_IND_INFO1_MODE_LSB		0
#घोषणा HTT_TX_MODE_SWITCH_IND_INFO1_THRESHOLD_MASK	0xfffc
#घोषणा HTT_TX_MODE_SWITCH_IND_INFO1_THRESHOLD_LSB	2

#घोषणा HTT_TX_MODE_SWITCH_RECORD_INFO0_PEER_ID_MASK	0x0fff
#घोषणा HTT_TX_MODE_SWITCH_RECORD_INFO0_PEER_ID_LSB	0
#घोषणा HTT_TX_MODE_SWITCH_RECORD_INFO0_TID_MASK	0xf000
#घोषणा HTT_TX_MODE_SWITCH_RECORD_INFO0_TID_LSB		12

काष्ठा htt_tx_mode_चयन_record अणु
	__le16 info0; /* HTT_TX_MODE_SWITCH_RECORD_INFO0_ */
	__le16 num_max_msdus;
पूर्ण __packed;

काष्ठा htt_tx_mode_चयन_ind अणु
	u8 pad0;
	__le16 info0; /* HTT_TX_MODE_SWITCH_IND_INFO0_ */
	__le16 info1; /* HTT_TX_MODE_SWITCH_IND_INFO1_ */
	u8 pad1[2];
	काष्ठा htt_tx_mode_चयन_record records[];
पूर्ण __packed;

काष्ठा htt_channel_change अणु
	u8 pad[3];
	__le32 freq;
	__le32 center_freq1;
	__le32 center_freq2;
	__le32 phymode;
पूर्ण __packed;

काष्ठा htt_per_peer_tx_stats_ind अणु
	__le32	succ_bytes;
	__le32  retry_bytes;
	__le32  failed_bytes;
	u8	ratecode;
	u8	flags;
	__le16	peer_id;
	__le16  succ_pkts;
	__le16	retry_pkts;
	__le16	failed_pkts;
	__le16	tx_duration;
	__le32	reserved1;
	__le32	reserved2;
पूर्ण __packed;

काष्ठा htt_peer_tx_stats अणु
	u8 num_ppdu;
	u8 ppdu_len;
	u8 version;
	u8 payload[];
पूर्ण __packed;

#घोषणा ATH10K_10_2_TX_STATS_OFFSET	136
#घोषणा PEER_STATS_FOR_NO_OF_PPDUS	4

काष्ठा ath10k_10_2_peer_tx_stats अणु
	u8 ratecode[PEER_STATS_FOR_NO_OF_PPDUS];
	u8 success_pkts[PEER_STATS_FOR_NO_OF_PPDUS];
	__le16 success_bytes[PEER_STATS_FOR_NO_OF_PPDUS];
	u8 retry_pkts[PEER_STATS_FOR_NO_OF_PPDUS];
	__le16 retry_bytes[PEER_STATS_FOR_NO_OF_PPDUS];
	u8 failed_pkts[PEER_STATS_FOR_NO_OF_PPDUS];
	__le16 failed_bytes[PEER_STATS_FOR_NO_OF_PPDUS];
	u8 flags[PEER_STATS_FOR_NO_OF_PPDUS];
	__le32 tx_duration;
	u8 tx_ppdu_cnt;
	u8 peer_id;
पूर्ण __packed;

जोड़ htt_rx_pn_t अणु
	/* WEP: 24-bit PN */
	u32 pn24;

	/* TKIP or CCMP: 48-bit PN */
	u64 pn48;

	/* WAPI: 128-bit PN */
	u64 pn128[2];
पूर्ण;

काष्ठा htt_cmd अणु
	काष्ठा htt_cmd_hdr hdr;
	जोड़ अणु
		काष्ठा htt_ver_req ver_req;
		काष्ठा htt_mgmt_tx_desc mgmt_tx;
		काष्ठा htt_data_tx_desc data_tx;
		काष्ठा htt_rx_ring_setup_32 rx_setup_32;
		काष्ठा htt_rx_ring_setup_64 rx_setup_64;
		काष्ठा htt_stats_req stats_req;
		काष्ठा htt_oob_sync_req oob_sync_req;
		काष्ठा htt_aggr_conf aggr_conf;
		काष्ठा htt_aggr_conf_v2 aggr_conf_v2;
		काष्ठा htt_frag_desc_bank_cfg32 frag_desc_bank_cfg32;
		काष्ठा htt_frag_desc_bank_cfg64 frag_desc_bank_cfg64;
		काष्ठा htt_tx_fetch_resp tx_fetch_resp;
	पूर्ण;
पूर्ण __packed;

काष्ठा htt_resp अणु
	काष्ठा htt_resp_hdr hdr;
	जोड़ अणु
		काष्ठा htt_ver_resp ver_resp;
		काष्ठा htt_mgmt_tx_completion mgmt_tx_completion;
		काष्ठा htt_data_tx_completion data_tx_completion;
		काष्ठा htt_rx_indication rx_ind;
		काष्ठा htt_rx_indication_hl rx_ind_hl;
		काष्ठा htt_rx_fragment_indication rx_frag_ind;
		काष्ठा htt_rx_peer_map peer_map;
		काष्ठा htt_rx_peer_unmap peer_unmap;
		काष्ठा htt_rx_flush rx_flush;
		काष्ठा htt_rx_addba rx_addba;
		काष्ठा htt_rx_delba rx_delba;
		काष्ठा htt_security_indication security_indication;
		काष्ठा htt_rc_update rc_update;
		काष्ठा htt_rx_test rx_test;
		काष्ठा htt_pktlog_msg pktlog_msg;
		काष्ठा htt_stats_conf stats_conf;
		काष्ठा htt_rx_pn_ind rx_pn_ind;
		काष्ठा htt_rx_offload_ind rx_offload_ind;
		काष्ठा htt_rx_in_ord_ind rx_in_ord_ind;
		काष्ठा htt_tx_fetch_ind tx_fetch_ind;
		काष्ठा htt_tx_fetch_confirm tx_fetch_confirm;
		काष्ठा htt_tx_mode_चयन_ind tx_mode_चयन_ind;
		काष्ठा htt_channel_change chan_change;
		काष्ठा htt_peer_tx_stats peer_tx_stats;
	पूर्ण;
पूर्ण __packed;

/*** host side काष्ठाures follow ***/

काष्ठा htt_tx_करोne अणु
	u16 msdu_id;
	u16 status;
	u8 ack_rssi;
पूर्ण;

क्रमागत htt_tx_compl_state अणु
	HTT_TX_COMPL_STATE_NONE,
	HTT_TX_COMPL_STATE_ACK,
	HTT_TX_COMPL_STATE_NOACK,
	HTT_TX_COMPL_STATE_DISCARD,
पूर्ण;

काष्ठा htt_peer_map_event अणु
	u8 vdev_id;
	u16 peer_id;
	u8 addr[ETH_ALEN];
पूर्ण;

काष्ठा htt_peer_unmap_event अणु
	u16 peer_id;
पूर्ण;

काष्ठा ath10k_htt_txbuf_32 अणु
	काष्ठा htt_data_tx_desc_frag frags[2];
	काष्ठा ath10k_htc_hdr htc_hdr;
	काष्ठा htt_cmd_hdr cmd_hdr;
	काष्ठा htt_data_tx_desc cmd_tx;
पूर्ण __packed __aligned(4);

काष्ठा ath10k_htt_txbuf_64 अणु
	काष्ठा htt_data_tx_desc_frag frags[2];
	काष्ठा ath10k_htc_hdr htc_hdr;
	काष्ठा htt_cmd_hdr cmd_hdr;
	काष्ठा htt_data_tx_desc_64 cmd_tx;
पूर्ण __packed __aligned(4);

काष्ठा ath10k_htt अणु
	काष्ठा ath10k *ar;
	क्रमागत ath10k_htc_ep_id eid;

	काष्ठा sk_buff_head rx_indication_head;

	u8 target_version_major;
	u8 target_version_minor;
	काष्ठा completion target_version_received;
	u8 max_num_amsdu;
	u8 max_num_ampdu;

	स्थिर क्रमागत htt_t2h_msg_type *t2h_msg_types;
	u32 t2h_msg_types_max;

	काष्ठा अणु
		/*
		 * Ring of network buffer objects - This ring is
		 * used exclusively by the host SW. This ring
		 * mirrors the dev_addrs_ring that is shared
		 * between the host SW and the MAC HW. The host SW
		 * uses this netbufs ring to locate the network
		 * buffer objects whose data buffers the HW has
		 * filled.
		 */
		काष्ठा sk_buff **netbufs_ring;

		/* This is used only with firmware supporting IN_ORD_IND.
		 *
		 * With Full Rx Reorder the HTT Rx Ring is more of a temporary
		 * buffer ring from which buffer addresses are copied by the
		 * firmware to MAC Rx ring. Firmware then delivers IN_ORD_IND
		 * poपूर्णांकing to specअगरic (re-ordered) buffers.
		 *
		 * FIXME: With kernel generic hashing functions there's a lot
		 * of hash collisions क्रम sk_buffs.
		 */
		bool in_ord_rx;
		DECLARE_HASHTABLE(skb_table, 4);

		/*
		 * Ring of buffer addresses -
		 * This ring holds the "physical" device address of the
		 * rx buffers the host SW provides क्रम the MAC HW to
		 * fill.
		 */
		जोड़ अणु
			__le64 *paddrs_ring_64;
			__le32 *paddrs_ring_32;
		पूर्ण;

		/*
		 * Base address of ring, as a "physical" device address
		 * rather than a CPU address.
		 */
		dma_addr_t base_paddr;

		/* how many elems in the ring (घातer of 2) */
		पूर्णांक size;

		/* size - 1 */
		अचिन्हित पूर्णांक size_mask;

		/* how many rx buffers to keep in the ring */
		पूर्णांक fill_level;

		/* how many rx buffers (full+empty) are in the ring */
		पूर्णांक fill_cnt;

		/*
		 * alloc_idx - where HTT SW has deposited empty buffers
		 * This is allocated in consistent mem, so that the FW can
		 * पढ़ो this variable, and program the HW's FW_IDX reg with
		 * the value of this shaकरोw रेजिस्टर.
		 */
		काष्ठा अणु
			__le32 *vaddr;
			dma_addr_t paddr;
		पूर्ण alloc_idx;

		/* where HTT SW has processed bufs filled by rx MAC DMA */
		काष्ठा अणु
			अचिन्हित पूर्णांक msdu_payld;
		पूर्ण sw_rd_idx;

		/*
		 * refill_retry_समयr - समयr triggered when the ring is
		 * not refilled to the level expected
		 */
		काष्ठा समयr_list refill_retry_समयr;

		/* Protects access to all rx ring buffer state variables */
		spinlock_t lock;
	पूर्ण rx_ring;

	अचिन्हित पूर्णांक prefetch_len;

	/* Protects access to pending_tx, num_pending_tx */
	spinlock_t tx_lock;
	पूर्णांक max_num_pending_tx;
	पूर्णांक num_pending_tx;
	पूर्णांक num_pending_mgmt_tx;
	काष्ठा idr pending_tx;
	रुको_queue_head_t empty_tx_wq;

	/* FIFO क्रम storing tx करोne status अणुack, no-ack, discardपूर्ण and msdu id */
	DECLARE_KFIFO_PTR(txकरोne_fअगरo, काष्ठा htt_tx_करोne);

	/* set अगर host-fw communication goes haywire
	 * used to aव्योम further failures
	 */
	bool rx_confused;
	atomic_t num_mpdus_पढ़ोy;

	/* This is used to group tx/rx completions separately and process them
	 * in batches to reduce cache stalls
	 */
	काष्ठा sk_buff_head rx_msdus_q;
	काष्ठा sk_buff_head rx_in_ord_compl_q;
	काष्ठा sk_buff_head tx_fetch_ind_q;

	/* rx_status ढाँचा */
	काष्ठा ieee80211_rx_status rx_status;

	काष्ठा अणु
		dma_addr_t paddr;
		जोड़ अणु
			काष्ठा htt_msdu_ext_desc *vaddr_desc_32;
			काष्ठा htt_msdu_ext_desc_64 *vaddr_desc_64;
		पूर्ण;
		माप_प्रकार size;
	पूर्ण frag_desc;

	काष्ठा अणु
		dma_addr_t paddr;
		जोड़ अणु
			काष्ठा ath10k_htt_txbuf_32 *vaddr_txbuff_32;
			काष्ठा ath10k_htt_txbuf_64 *vaddr_txbuff_64;
		पूर्ण;
		माप_प्रकार size;
	पूर्ण txbuf;

	काष्ठा अणु
		bool enabled;
		काष्ठा htt_q_state *vaddr;
		dma_addr_t paddr;
		u16 num_push_allowed;
		u16 num_peers;
		u16 num_tids;
		क्रमागत htt_tx_mode_चयन_mode mode;
		क्रमागत htt_q_depth_type type;
	पूर्ण tx_q_state;

	bool tx_mem_allocated;
	स्थिर काष्ठा ath10k_htt_tx_ops *tx_ops;
	स्थिर काष्ठा ath10k_htt_rx_ops *rx_ops;
	bool disable_tx_comp;
	bool bundle_tx;
	काष्ठा sk_buff_head tx_req_head;
	काष्ठा sk_buff_head tx_complete_head;
पूर्ण;

काष्ठा ath10k_htt_tx_ops अणु
	पूर्णांक (*htt_send_rx_ring_cfg)(काष्ठा ath10k_htt *htt);
	पूर्णांक (*htt_send_frag_desc_bank_cfg)(काष्ठा ath10k_htt *htt);
	पूर्णांक (*htt_alloc_frag_desc)(काष्ठा ath10k_htt *htt);
	व्योम (*htt_मुक्त_frag_desc)(काष्ठा ath10k_htt *htt);
	पूर्णांक (*htt_tx)(काष्ठा ath10k_htt *htt, क्रमागत ath10k_hw_txrx_mode txmode,
		      काष्ठा sk_buff *msdu);
	पूर्णांक (*htt_alloc_txbuff)(काष्ठा ath10k_htt *htt);
	व्योम (*htt_मुक्त_txbuff)(काष्ठा ath10k_htt *htt);
	पूर्णांक (*htt_h2t_aggr_cfg_msg)(काष्ठा ath10k_htt *htt,
				    u8 max_subfrms_ampdu,
				    u8 max_subfrms_amsdu);
	व्योम (*htt_flush_tx)(काष्ठा ath10k_htt *htt);
पूर्ण;

अटल अंतरभूत पूर्णांक ath10k_htt_send_rx_ring_cfg(काष्ठा ath10k_htt *htt)
अणु
	अगर (!htt->tx_ops->htt_send_rx_ring_cfg)
		वापस -EOPNOTSUPP;

	वापस htt->tx_ops->htt_send_rx_ring_cfg(htt);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_htt_send_frag_desc_bank_cfg(काष्ठा ath10k_htt *htt)
अणु
	अगर (!htt->tx_ops->htt_send_frag_desc_bank_cfg)
		वापस -EOPNOTSUPP;

	वापस htt->tx_ops->htt_send_frag_desc_bank_cfg(htt);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_htt_alloc_frag_desc(काष्ठा ath10k_htt *htt)
अणु
	अगर (!htt->tx_ops->htt_alloc_frag_desc)
		वापस -EOPNOTSUPP;

	वापस htt->tx_ops->htt_alloc_frag_desc(htt);
पूर्ण

अटल अंतरभूत व्योम ath10k_htt_मुक्त_frag_desc(काष्ठा ath10k_htt *htt)
अणु
	अगर (htt->tx_ops->htt_मुक्त_frag_desc)
		htt->tx_ops->htt_मुक्त_frag_desc(htt);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_htt_tx(काष्ठा ath10k_htt *htt,
				क्रमागत ath10k_hw_txrx_mode txmode,
				काष्ठा sk_buff *msdu)
अणु
	वापस htt->tx_ops->htt_tx(htt, txmode, msdu);
पूर्ण

अटल अंतरभूत व्योम ath10k_htt_flush_tx(काष्ठा ath10k_htt *htt)
अणु
	अगर (htt->tx_ops->htt_flush_tx)
		htt->tx_ops->htt_flush_tx(htt);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_htt_alloc_txbuff(काष्ठा ath10k_htt *htt)
अणु
	अगर (!htt->tx_ops->htt_alloc_txbuff)
		वापस -EOPNOTSUPP;

	वापस htt->tx_ops->htt_alloc_txbuff(htt);
पूर्ण

अटल अंतरभूत व्योम ath10k_htt_मुक्त_txbuff(काष्ठा ath10k_htt *htt)
अणु
	अगर (htt->tx_ops->htt_मुक्त_txbuff)
		htt->tx_ops->htt_मुक्त_txbuff(htt);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_htt_h2t_aggr_cfg_msg(काष्ठा ath10k_htt *htt,
					      u8 max_subfrms_ampdu,
					      u8 max_subfrms_amsdu)

अणु
	अगर (!htt->tx_ops->htt_h2t_aggr_cfg_msg)
		वापस -EOPNOTSUPP;

	वापस htt->tx_ops->htt_h2t_aggr_cfg_msg(htt,
						 max_subfrms_ampdu,
						 max_subfrms_amsdu);
पूर्ण

काष्ठा ath10k_htt_rx_ops अणु
	माप_प्रकार (*htt_get_rx_ring_size)(काष्ठा ath10k_htt *htt);
	व्योम (*htt_config_paddrs_ring)(काष्ठा ath10k_htt *htt, व्योम *vaddr);
	व्योम (*htt_set_paddrs_ring)(काष्ठा ath10k_htt *htt, dma_addr_t paddr,
				    पूर्णांक idx);
	व्योम* (*htt_get_vaddr_ring)(काष्ठा ath10k_htt *htt);
	व्योम (*htt_reset_paddrs_ring)(काष्ठा ath10k_htt *htt, पूर्णांक idx);
	bool (*htt_rx_proc_rx_frag_ind)(काष्ठा ath10k_htt *htt,
					काष्ठा htt_rx_fragment_indication *rx,
					काष्ठा sk_buff *skb);
पूर्ण;

अटल अंतरभूत माप_प्रकार ath10k_htt_get_rx_ring_size(काष्ठा ath10k_htt *htt)
अणु
	अगर (!htt->rx_ops->htt_get_rx_ring_size)
		वापस 0;

	वापस htt->rx_ops->htt_get_rx_ring_size(htt);
पूर्ण

अटल अंतरभूत व्योम ath10k_htt_config_paddrs_ring(काष्ठा ath10k_htt *htt,
						 व्योम *vaddr)
अणु
	अगर (htt->rx_ops->htt_config_paddrs_ring)
		htt->rx_ops->htt_config_paddrs_ring(htt, vaddr);
पूर्ण

अटल अंतरभूत व्योम ath10k_htt_set_paddrs_ring(काष्ठा ath10k_htt *htt,
					      dma_addr_t paddr,
					      पूर्णांक idx)
अणु
	अगर (htt->rx_ops->htt_set_paddrs_ring)
		htt->rx_ops->htt_set_paddrs_ring(htt, paddr, idx);
पूर्ण

अटल अंतरभूत व्योम *ath10k_htt_get_vaddr_ring(काष्ठा ath10k_htt *htt)
अणु
	अगर (!htt->rx_ops->htt_get_vaddr_ring)
		वापस शून्य;

	वापस htt->rx_ops->htt_get_vaddr_ring(htt);
पूर्ण

अटल अंतरभूत व्योम ath10k_htt_reset_paddrs_ring(काष्ठा ath10k_htt *htt, पूर्णांक idx)
अणु
	अगर (htt->rx_ops->htt_reset_paddrs_ring)
		htt->rx_ops->htt_reset_paddrs_ring(htt, idx);
पूर्ण

अटल अंतरभूत bool ath10k_htt_rx_proc_rx_frag_ind(काष्ठा ath10k_htt *htt,
						  काष्ठा htt_rx_fragment_indication *rx,
						  काष्ठा sk_buff *skb)
अणु
	अगर (!htt->rx_ops->htt_rx_proc_rx_frag_ind)
		वापस true;

	वापस htt->rx_ops->htt_rx_proc_rx_frag_ind(htt, rx, skb);
पूर्ण

#घोषणा RX_HTT_HDR_STATUS_LEN 64

/* This काष्ठाure layout is programmed via rx ring setup
 * so that FW knows how to transfer the rx descriptor to the host.
 * Buffers like this are placed on the rx ring.
 */
काष्ठा htt_rx_desc अणु
	जोड़ अणु
		/* This field is filled on the host using the msdu buffer
		 * from htt_rx_indication
		 */
		काष्ठा fw_rx_desc_base fw_desc;
		u32 pad;
	पूर्ण __packed;
	काष्ठा अणु
		काष्ठा rx_attention attention;
		काष्ठा rx_frag_info frag_info;
		काष्ठा rx_mpdu_start mpdu_start;
		काष्ठा rx_msdu_start msdu_start;
		काष्ठा rx_msdu_end msdu_end;
		काष्ठा rx_mpdu_end mpdu_end;
		काष्ठा rx_ppdu_start ppdu_start;
		काष्ठा rx_ppdu_end ppdu_end;
	पूर्ण __packed;
	u8 rx_hdr_status[RX_HTT_HDR_STATUS_LEN];
	u8 msdu_payload[];
पूर्ण;

#घोषणा HTT_RX_DESC_HL_INFO_SEQ_NUM_MASK           0x00000fff
#घोषणा HTT_RX_DESC_HL_INFO_SEQ_NUM_LSB            0
#घोषणा HTT_RX_DESC_HL_INFO_ENCRYPTED_MASK         0x00001000
#घोषणा HTT_RX_DESC_HL_INFO_ENCRYPTED_LSB          12
#घोषणा HTT_RX_DESC_HL_INFO_CHAN_INFO_PRESENT_MASK 0x00002000
#घोषणा HTT_RX_DESC_HL_INFO_CHAN_INFO_PRESENT_LSB  13
#घोषणा HTT_RX_DESC_HL_INFO_MCAST_BCAST_MASK       0x00010000
#घोषणा HTT_RX_DESC_HL_INFO_MCAST_BCAST_LSB        16
#घोषणा HTT_RX_DESC_HL_INFO_KEY_ID_OCT_MASK        0x01fe0000
#घोषणा HTT_RX_DESC_HL_INFO_KEY_ID_OCT_LSB         17

काष्ठा htt_rx_desc_base_hl अणु
	__le32 info; /* HTT_RX_DESC_HL_INFO_ */
पूर्ण;

काष्ठा htt_rx_chan_info अणु
	__le16 primary_chan_center_freq_mhz;
	__le16 contig_chan1_center_freq_mhz;
	__le16 contig_chan2_center_freq_mhz;
	u8 phy_mode;
	u8 reserved;
पूर्ण __packed;

#घोषणा HTT_RX_DESC_ALIGN 8

#घोषणा HTT_MAC_ADDR_LEN 6

/*
 * FIX THIS
 * Should be: माप(काष्ठा htt_host_rx_desc) + max rx MSDU size,
 * rounded up to a cache line size.
 */
#घोषणा HTT_RX_BUF_SIZE 2048
#घोषणा HTT_RX_MSDU_SIZE (HTT_RX_BUF_SIZE - (पूर्णांक)माप(काष्ठा htt_rx_desc))

/* Refill a bunch of RX buffers क्रम each refill round so that FW/HW can handle
 * aggregated traffic more nicely.
 */
#घोषणा ATH10K_HTT_MAX_NUM_REFILL 100

/*
 * DMA_MAP expects the buffer to be an पूर्णांकegral number of cache lines.
 * Rather than checking the actual cache line size, this code makes a
 * conservative estimate of what the cache line size could be.
 */
#घोषणा HTT_LOG2_MAX_CACHE_LINE_SIZE 7	/* 2^7 = 128 */
#घोषणा HTT_MAX_CACHE_LINE_SIZE_MASK ((1 << HTT_LOG2_MAX_CACHE_LINE_SIZE) - 1)

/* These values are शेष in most firmware revisions and apparently are a
 * sweet spot perक्रमmance wise.
 */
#घोषणा ATH10K_HTT_MAX_NUM_AMSDU_DEFAULT 3
#घोषणा ATH10K_HTT_MAX_NUM_AMPDU_DEFAULT 64

पूर्णांक ath10k_htt_connect(काष्ठा ath10k_htt *htt);
पूर्णांक ath10k_htt_init(काष्ठा ath10k *ar);
पूर्णांक ath10k_htt_setup(काष्ठा ath10k_htt *htt);

पूर्णांक ath10k_htt_tx_start(काष्ठा ath10k_htt *htt);
व्योम ath10k_htt_tx_stop(काष्ठा ath10k_htt *htt);
व्योम ath10k_htt_tx_destroy(काष्ठा ath10k_htt *htt);
व्योम ath10k_htt_tx_मुक्त(काष्ठा ath10k_htt *htt);

पूर्णांक ath10k_htt_rx_alloc(काष्ठा ath10k_htt *htt);
पूर्णांक ath10k_htt_rx_ring_refill(काष्ठा ath10k *ar);
व्योम ath10k_htt_rx_मुक्त(काष्ठा ath10k_htt *htt);

व्योम ath10k_htt_htc_tx_complete(काष्ठा ath10k *ar, काष्ठा sk_buff *skb);
व्योम ath10k_htt_htc_t2h_msg_handler(काष्ठा ath10k *ar, काष्ठा sk_buff *skb);
bool ath10k_htt_t2h_msg_handler(काष्ठा ath10k *ar, काष्ठा sk_buff *skb);
पूर्णांक ath10k_htt_h2t_ver_req_msg(काष्ठा ath10k_htt *htt);
पूर्णांक ath10k_htt_h2t_stats_req(काष्ठा ath10k_htt *htt, u32 mask, u32 reset_mask,
			     u64 cookie);
व्योम ath10k_htt_hअगर_tx_complete(काष्ठा ath10k *ar, काष्ठा sk_buff *skb);
पूर्णांक ath10k_htt_tx_fetch_resp(काष्ठा ath10k *ar,
			     __le32 token,
			     __le16 fetch_seq_num,
			     काष्ठा htt_tx_fetch_record *records,
			     माप_प्रकार num_records);
व्योम ath10k_htt_op_ep_tx_credits(काष्ठा ath10k *ar);

व्योम ath10k_htt_tx_txq_update(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_txq *txq);
व्योम ath10k_htt_tx_txq_recalc(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_txq *txq);
व्योम ath10k_htt_tx_txq_sync(काष्ठा ath10k *ar);
व्योम ath10k_htt_tx_dec_pending(काष्ठा ath10k_htt *htt);
पूर्णांक ath10k_htt_tx_inc_pending(काष्ठा ath10k_htt *htt);
व्योम ath10k_htt_tx_mgmt_dec_pending(काष्ठा ath10k_htt *htt);
पूर्णांक ath10k_htt_tx_mgmt_inc_pending(काष्ठा ath10k_htt *htt, bool is_mgmt,
				   bool is_presp);

पूर्णांक ath10k_htt_tx_alloc_msdu_id(काष्ठा ath10k_htt *htt, काष्ठा sk_buff *skb);
व्योम ath10k_htt_tx_मुक्त_msdu_id(काष्ठा ath10k_htt *htt, u16 msdu_id);
पूर्णांक ath10k_htt_mgmt_tx(काष्ठा ath10k_htt *htt, काष्ठा sk_buff *msdu);
व्योम ath10k_htt_rx_pktlog_completion_handler(काष्ठा ath10k *ar,
					     काष्ठा sk_buff *skb);
पूर्णांक ath10k_htt_txrx_compl_task(काष्ठा ath10k *ar, पूर्णांक budget);
पूर्णांक ath10k_htt_rx_hl_indication(काष्ठा ath10k *ar, पूर्णांक budget);
व्योम ath10k_htt_set_tx_ops(काष्ठा ath10k_htt *htt);
व्योम ath10k_htt_set_rx_ops(काष्ठा ath10k_htt *htt);
#पूर्ण_अगर
