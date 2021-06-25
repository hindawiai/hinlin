<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2014-2016 Broadcom Corporation
 * Copyright (c) 2016-2018 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित BNXT_H
#घोषणा BNXT_H

#घोषणा DRV_MODULE_NAME		"bnxt_en"

/* DO NOT CHANGE DRV_VER_* defines
 * FIXME: Delete them
 */
#घोषणा DRV_VER_MAJ	1
#घोषणा DRV_VER_MIN	10
#घोषणा DRV_VER_UPD	2

#समावेश <linux/ethtool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/crash_dump.h>
#समावेश <net/devlink.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/xdp.h>
#समावेश <linux/dim.h>
#अगर_घोषित CONFIG_TEE_BNXT_FW
#समावेश <linux/firmware/broadcom/tee_bnxt_fw.h>
#पूर्ण_अगर

बाह्य काष्ठा list_head bnxt_block_cb_list;

काष्ठा page_pool;

काष्ठा tx_bd अणु
	__le32 tx_bd_len_flags_type;
	#घोषणा TX_BD_TYPE					(0x3f << 0)
	 #घोषणा TX_BD_TYPE_SHORT_TX_BD				 (0x00 << 0)
	 #घोषणा TX_BD_TYPE_LONG_TX_BD				 (0x10 << 0)
	#घोषणा TX_BD_FLAGS_PACKET_END				(1 << 6)
	#घोषणा TX_BD_FLAGS_NO_CMPL				(1 << 7)
	#घोषणा TX_BD_FLAGS_BD_CNT				(0x1f << 8)
	 #घोषणा TX_BD_FLAGS_BD_CNT_SHIFT			 8
	#घोषणा TX_BD_FLAGS_LHINT				(3 << 13)
	 #घोषणा TX_BD_FLAGS_LHINT_SHIFT			 13
	 #घोषणा TX_BD_FLAGS_LHINT_512_AND_SMALLER		 (0 << 13)
	 #घोषणा TX_BD_FLAGS_LHINT_512_TO_1023			 (1 << 13)
	 #घोषणा TX_BD_FLAGS_LHINT_1024_TO_2047			 (2 << 13)
	 #घोषणा TX_BD_FLAGS_LHINT_2048_AND_LARGER		 (3 << 13)
	#घोषणा TX_BD_FLAGS_COAL_NOW				(1 << 15)
	#घोषणा TX_BD_LEN					(0xffff << 16)
	 #घोषणा TX_BD_LEN_SHIFT				 16

	u32 tx_bd_opaque;
	__le64 tx_bd_haddr;
पूर्ण __packed;

काष्ठा tx_bd_ext अणु
	__le32 tx_bd_hsize_lflags;
	#घोषणा TX_BD_FLAGS_TCP_UDP_CHKSUM			(1 << 0)
	#घोषणा TX_BD_FLAGS_IP_CKSUM				(1 << 1)
	#घोषणा TX_BD_FLAGS_NO_CRC				(1 << 2)
	#घोषणा TX_BD_FLAGS_STAMP				(1 << 3)
	#घोषणा TX_BD_FLAGS_T_IP_CHKSUM				(1 << 4)
	#घोषणा TX_BD_FLAGS_LSO					(1 << 5)
	#घोषणा TX_BD_FLAGS_IPID_FMT				(1 << 6)
	#घोषणा TX_BD_FLAGS_T_IPID				(1 << 7)
	#घोषणा TX_BD_HSIZE					(0xff << 16)
	 #घोषणा TX_BD_HSIZE_SHIFT				 16

	__le32 tx_bd_mss;
	__le32 tx_bd_cfa_action;
	#घोषणा TX_BD_CFA_ACTION				(0xffff << 16)
	 #घोषणा TX_BD_CFA_ACTION_SHIFT				 16

	__le32 tx_bd_cfa_meta;
	#घोषणा TX_BD_CFA_META_MASK                             0xfffffff
	#घोषणा TX_BD_CFA_META_VID_MASK                         0xfff
	#घोषणा TX_BD_CFA_META_PRI_MASK                         (0xf << 12)
	 #घोषणा TX_BD_CFA_META_PRI_SHIFT                        12
	#घोषणा TX_BD_CFA_META_TPID_MASK                        (3 << 16)
	 #घोषणा TX_BD_CFA_META_TPID_SHIFT                       16
	#घोषणा TX_BD_CFA_META_KEY                              (0xf << 28)
	 #घोषणा TX_BD_CFA_META_KEY_SHIFT			 28
	#घोषणा TX_BD_CFA_META_KEY_VLAN                         (1 << 28)
पूर्ण;

काष्ठा rx_bd अणु
	__le32 rx_bd_len_flags_type;
	#घोषणा RX_BD_TYPE					(0x3f << 0)
	 #घोषणा RX_BD_TYPE_RX_PACKET_BD			 0x4
	 #घोषणा RX_BD_TYPE_RX_BUFFER_BD			 0x5
	 #घोषणा RX_BD_TYPE_RX_AGG_BD				 0x6
	 #घोषणा RX_BD_TYPE_16B_BD_SIZE				 (0 << 4)
	 #घोषणा RX_BD_TYPE_32B_BD_SIZE				 (1 << 4)
	 #घोषणा RX_BD_TYPE_48B_BD_SIZE				 (2 << 4)
	 #घोषणा RX_BD_TYPE_64B_BD_SIZE				 (3 << 4)
	#घोषणा RX_BD_FLAGS_SOP					(1 << 6)
	#घोषणा RX_BD_FLAGS_EOP					(1 << 7)
	#घोषणा RX_BD_FLAGS_BUFFERS				(3 << 8)
	 #घोषणा RX_BD_FLAGS_1_BUFFER_PACKET			 (0 << 8)
	 #घोषणा RX_BD_FLAGS_2_BUFFER_PACKET			 (1 << 8)
	 #घोषणा RX_BD_FLAGS_3_BUFFER_PACKET			 (2 << 8)
	 #घोषणा RX_BD_FLAGS_4_BUFFER_PACKET			 (3 << 8)
	#घोषणा RX_BD_LEN					(0xffff << 16)
	 #घोषणा RX_BD_LEN_SHIFT				 16

	u32 rx_bd_opaque;
	__le64 rx_bd_haddr;
पूर्ण;

काष्ठा tx_cmp अणु
	__le32 tx_cmp_flags_type;
	#घोषणा CMP_TYPE					(0x3f << 0)
	 #घोषणा CMP_TYPE_TX_L2_CMP				 0
	 #घोषणा CMP_TYPE_RX_L2_CMP				 17
	 #घोषणा CMP_TYPE_RX_AGG_CMP				 18
	 #घोषणा CMP_TYPE_RX_L2_TPA_START_CMP			 19
	 #घोषणा CMP_TYPE_RX_L2_TPA_END_CMP			 21
	 #घोषणा CMP_TYPE_RX_TPA_AGG_CMP			 22
	 #घोषणा CMP_TYPE_STATUS_CMP				 32
	 #घोषणा CMP_TYPE_REMOTE_DRIVER_REQ			 34
	 #घोषणा CMP_TYPE_REMOTE_DRIVER_RESP			 36
	 #घोषणा CMP_TYPE_ERROR_STATUS				 48
	 #घोषणा CMPL_BASE_TYPE_STAT_EJECT			 0x1aUL
	 #घोषणा CMPL_BASE_TYPE_HWRM_DONE			 0x20UL
	 #घोषणा CMPL_BASE_TYPE_HWRM_FWD_REQ			 0x22UL
	 #घोषणा CMPL_BASE_TYPE_HWRM_FWD_RESP			 0x24UL
	 #घोषणा CMPL_BASE_TYPE_HWRM_ASYNC_EVENT		 0x2eUL

	#घोषणा TX_CMP_FLAGS_ERROR				(1 << 6)
	#घोषणा TX_CMP_FLAGS_PUSH				(1 << 7)

	u32 tx_cmp_opaque;
	__le32 tx_cmp_errors_v;
	#घोषणा TX_CMP_V					(1 << 0)
	#घोषणा TX_CMP_ERRORS_BUFFER_ERROR			(7 << 1)
	 #घोषणा TX_CMP_ERRORS_BUFFER_ERROR_NO_ERROR		 0
	 #घोषणा TX_CMP_ERRORS_BUFFER_ERROR_BAD_FORMAT		 2
	 #घोषणा TX_CMP_ERRORS_BUFFER_ERROR_INVALID_STAG	 4
	 #घोषणा TX_CMP_ERRORS_BUFFER_ERROR_STAG_BOUNDS		 5
	 #घोषणा TX_CMP_ERRORS_ZERO_LENGTH_PKT			 (1 << 4)
	 #घोषणा TX_CMP_ERRORS_EXCESSIVE_BD_LEN			 (1 << 5)
	 #घोषणा TX_CMP_ERRORS_DMA_ERROR			 (1 << 6)
	 #घोषणा TX_CMP_ERRORS_HINT_TOO_SHORT			 (1 << 7)

	__le32 tx_cmp_unsed_3;
पूर्ण;

काष्ठा rx_cmp अणु
	__le32 rx_cmp_len_flags_type;
	#घोषणा RX_CMP_CMP_TYPE					(0x3f << 0)
	#घोषणा RX_CMP_FLAGS_ERROR				(1 << 6)
	#घोषणा RX_CMP_FLAGS_PLACEMENT				(7 << 7)
	#घोषणा RX_CMP_FLAGS_RSS_VALID				(1 << 10)
	#घोषणा RX_CMP_FLAGS_UNUSED				(1 << 11)
	 #घोषणा RX_CMP_FLAGS_ITYPES_SHIFT			 12
	 #घोषणा RX_CMP_FLAGS_ITYPE_UNKNOWN			 (0 << 12)
	 #घोषणा RX_CMP_FLAGS_ITYPE_IP				 (1 << 12)
	 #घोषणा RX_CMP_FLAGS_ITYPE_TCP				 (2 << 12)
	 #घोषणा RX_CMP_FLAGS_ITYPE_UDP				 (3 << 12)
	 #घोषणा RX_CMP_FLAGS_ITYPE_FCOE			 (4 << 12)
	 #घोषणा RX_CMP_FLAGS_ITYPE_ROCE			 (5 << 12)
	 #घोषणा RX_CMP_FLAGS_ITYPE_PTP_WO_TS			 (8 << 12)
	 #घोषणा RX_CMP_FLAGS_ITYPE_PTP_W_TS			 (9 << 12)
	#घोषणा RX_CMP_LEN					(0xffff << 16)
	 #घोषणा RX_CMP_LEN_SHIFT				 16

	u32 rx_cmp_opaque;
	__le32 rx_cmp_misc_v1;
	#घोषणा RX_CMP_V1					(1 << 0)
	#घोषणा RX_CMP_AGG_BUFS					(0x1f << 1)
	 #घोषणा RX_CMP_AGG_BUFS_SHIFT				 1
	#घोषणा RX_CMP_RSS_HASH_TYPE				(0x7f << 9)
	 #घोषणा RX_CMP_RSS_HASH_TYPE_SHIFT			 9
	#घोषणा RX_CMP_PAYLOAD_OFFSET				(0xff << 16)
	 #घोषणा RX_CMP_PAYLOAD_OFFSET_SHIFT			 16

	__le32 rx_cmp_rss_hash;
पूर्ण;

#घोषणा RX_CMP_HASH_VALID(rxcmp)				\
	((rxcmp)->rx_cmp_len_flags_type & cpu_to_le32(RX_CMP_FLAGS_RSS_VALID))

#घोषणा RSS_PROखाता_ID_MASK	0x1f

#घोषणा RX_CMP_HASH_TYPE(rxcmp)					\
	(((le32_to_cpu((rxcmp)->rx_cmp_misc_v1) & RX_CMP_RSS_HASH_TYPE) >>\
	  RX_CMP_RSS_HASH_TYPE_SHIFT) & RSS_PROखाता_ID_MASK)

काष्ठा rx_cmp_ext अणु
	__le32 rx_cmp_flags2;
	#घोषणा RX_CMP_FLAGS2_IP_CS_CALC			0x1
	#घोषणा RX_CMP_FLAGS2_L4_CS_CALC			(0x1 << 1)
	#घोषणा RX_CMP_FLAGS2_T_IP_CS_CALC			(0x1 << 2)
	#घोषणा RX_CMP_FLAGS2_T_L4_CS_CALC			(0x1 << 3)
	#घोषणा RX_CMP_FLAGS2_META_FORMAT_VLAN			(0x1 << 4)
	__le32 rx_cmp_meta_data;
	#घोषणा RX_CMP_FLAGS2_METADATA_TCI_MASK			0xffff
	#घोषणा RX_CMP_FLAGS2_METADATA_VID_MASK			0xfff
	#घोषणा RX_CMP_FLAGS2_METADATA_TPID_MASK		0xffff0000
	 #घोषणा RX_CMP_FLAGS2_METADATA_TPID_SFT		 16
	__le32 rx_cmp_cfa_code_errors_v2;
	#घोषणा RX_CMP_V					(1 << 0)
	#घोषणा RX_CMPL_ERRORS_MASK				(0x7fff << 1)
	 #घोषणा RX_CMPL_ERRORS_SFT				 1
	#घोषणा RX_CMPL_ERRORS_BUFFER_ERROR_MASK		(0x7 << 1)
	 #घोषणा RX_CMPL_ERRORS_BUFFER_ERROR_NO_BUFFER		 (0x0 << 1)
	 #घोषणा RX_CMPL_ERRORS_BUFFER_ERROR_DID_NOT_FIT	 (0x1 << 1)
	 #घोषणा RX_CMPL_ERRORS_BUFFER_ERROR_NOT_ON_CHIP	 (0x2 << 1)
	 #घोषणा RX_CMPL_ERRORS_BUFFER_ERROR_BAD_FORMAT		 (0x3 << 1)
	#घोषणा RX_CMPL_ERRORS_IP_CS_ERROR			(0x1 << 4)
	#घोषणा RX_CMPL_ERRORS_L4_CS_ERROR			(0x1 << 5)
	#घोषणा RX_CMPL_ERRORS_T_IP_CS_ERROR			(0x1 << 6)
	#घोषणा RX_CMPL_ERRORS_T_L4_CS_ERROR			(0x1 << 7)
	#घोषणा RX_CMPL_ERRORS_CRC_ERROR			(0x1 << 8)
	#घोषणा RX_CMPL_ERRORS_T_PKT_ERROR_MASK			(0x7 << 9)
	 #घोषणा RX_CMPL_ERRORS_T_PKT_ERROR_NO_ERROR		 (0x0 << 9)
	 #घोषणा RX_CMPL_ERRORS_T_PKT_ERROR_T_L3_BAD_VERSION	 (0x1 << 9)
	 #घोषणा RX_CMPL_ERRORS_T_PKT_ERROR_T_L3_BAD_HDR_LEN	 (0x2 << 9)
	 #घोषणा RX_CMPL_ERRORS_T_PKT_ERROR_TUNNEL_TOTAL_ERROR	 (0x3 << 9)
	 #घोषणा RX_CMPL_ERRORS_T_PKT_ERROR_T_IP_TOTAL_ERROR	 (0x4 << 9)
	 #घोषणा RX_CMPL_ERRORS_T_PKT_ERROR_T_UDP_TOTAL_ERROR	 (0x5 << 9)
	 #घोषणा RX_CMPL_ERRORS_T_PKT_ERROR_T_L3_BAD_TTL	 (0x6 << 9)
	#घोषणा RX_CMPL_ERRORS_PKT_ERROR_MASK			(0xf << 12)
	 #घोषणा RX_CMPL_ERRORS_PKT_ERROR_NO_ERROR		 (0x0 << 12)
	 #घोषणा RX_CMPL_ERRORS_PKT_ERROR_L3_BAD_VERSION	 (0x1 << 12)
	 #घोषणा RX_CMPL_ERRORS_PKT_ERROR_L3_BAD_HDR_LEN	 (0x2 << 12)
	 #घोषणा RX_CMPL_ERRORS_PKT_ERROR_L3_BAD_TTL		 (0x3 << 12)
	 #घोषणा RX_CMPL_ERRORS_PKT_ERROR_IP_TOTAL_ERROR	 (0x4 << 12)
	 #घोषणा RX_CMPL_ERRORS_PKT_ERROR_UDP_TOTAL_ERROR	 (0x5 << 12)
	 #घोषणा RX_CMPL_ERRORS_PKT_ERROR_L4_BAD_HDR_LEN	 (0x6 << 12)
	 #घोषणा RX_CMPL_ERRORS_PKT_ERROR_L4_BAD_HDR_LEN_TOO_SMALL (0x7 << 12)
	 #घोषणा RX_CMPL_ERRORS_PKT_ERROR_L4_BAD_OPT_LEN	 (0x8 << 12)

	#घोषणा RX_CMPL_CFA_CODE_MASK				(0xffff << 16)
	 #घोषणा RX_CMPL_CFA_CODE_SFT				 16

	__le32 rx_cmp_unused3;
पूर्ण;

#घोषणा RX_CMP_L2_ERRORS						\
	cpu_to_le32(RX_CMPL_ERRORS_BUFFER_ERROR_MASK | RX_CMPL_ERRORS_CRC_ERROR)

#घोषणा RX_CMP_L4_CS_BITS						\
	(cpu_to_le32(RX_CMP_FLAGS2_L4_CS_CALC | RX_CMP_FLAGS2_T_L4_CS_CALC))

#घोषणा RX_CMP_L4_CS_ERR_BITS						\
	(cpu_to_le32(RX_CMPL_ERRORS_L4_CS_ERROR | RX_CMPL_ERRORS_T_L4_CS_ERROR))

#घोषणा RX_CMP_L4_CS_OK(rxcmp1)						\
	    (((rxcmp1)->rx_cmp_flags2 &	RX_CMP_L4_CS_BITS) &&		\
	     !((rxcmp1)->rx_cmp_cfa_code_errors_v2 & RX_CMP_L4_CS_ERR_BITS))

#घोषणा RX_CMP_ENCAP(rxcmp1)						\
	    ((le32_to_cpu((rxcmp1)->rx_cmp_flags2) &			\
	     RX_CMP_FLAGS2_T_L4_CS_CALC) >> 3)

#घोषणा RX_CMP_CFA_CODE(rxcmpl1)					\
	((le32_to_cpu((rxcmpl1)->rx_cmp_cfa_code_errors_v2) &		\
	  RX_CMPL_CFA_CODE_MASK) >> RX_CMPL_CFA_CODE_SFT)

काष्ठा rx_agg_cmp अणु
	__le32 rx_agg_cmp_len_flags_type;
	#घोषणा RX_AGG_CMP_TYPE					(0x3f << 0)
	#घोषणा RX_AGG_CMP_LEN					(0xffff << 16)
	 #घोषणा RX_AGG_CMP_LEN_SHIFT				 16
	u32 rx_agg_cmp_opaque;
	__le32 rx_agg_cmp_v;
	#घोषणा RX_AGG_CMP_V					(1 << 0)
	#घोषणा RX_AGG_CMP_AGG_ID				(0xffff << 16)
	 #घोषणा RX_AGG_CMP_AGG_ID_SHIFT			 16
	__le32 rx_agg_cmp_unused;
पूर्ण;

#घोषणा TPA_AGG_AGG_ID(rx_agg)				\
	((le32_to_cpu((rx_agg)->rx_agg_cmp_v) &		\
	 RX_AGG_CMP_AGG_ID) >> RX_AGG_CMP_AGG_ID_SHIFT)

काष्ठा rx_tpa_start_cmp अणु
	__le32 rx_tpa_start_cmp_len_flags_type;
	#घोषणा RX_TPA_START_CMP_TYPE				(0x3f << 0)
	#घोषणा RX_TPA_START_CMP_FLAGS				(0x3ff << 6)
	 #घोषणा RX_TPA_START_CMP_FLAGS_SHIFT			 6
	#घोषणा RX_TPA_START_CMP_FLAGS_ERROR			(0x1 << 6)
	#घोषणा RX_TPA_START_CMP_FLAGS_PLACEMENT		(0x7 << 7)
	 #घोषणा RX_TPA_START_CMP_FLAGS_PLACEMENT_SHIFT		 7
	 #घोषणा RX_TPA_START_CMP_FLAGS_PLACEMENT_JUMBO		 (0x1 << 7)
	 #घोषणा RX_TPA_START_CMP_FLAGS_PLACEMENT_HDS		 (0x2 << 7)
	 #घोषणा RX_TPA_START_CMP_FLAGS_PLACEMENT_GRO_JUMBO	 (0x5 << 7)
	 #घोषणा RX_TPA_START_CMP_FLAGS_PLACEMENT_GRO_HDS	 (0x6 << 7)
	#घोषणा RX_TPA_START_CMP_FLAGS_RSS_VALID		(0x1 << 10)
	#घोषणा RX_TPA_START_CMP_FLAGS_TIMESTAMP		(0x1 << 11)
	#घोषणा RX_TPA_START_CMP_FLAGS_ITYPES			(0xf << 12)
	 #घोषणा RX_TPA_START_CMP_FLAGS_ITYPES_SHIFT		 12
	 #घोषणा RX_TPA_START_CMP_FLAGS_ITYPE_TCP		 (0x2 << 12)
	#घोषणा RX_TPA_START_CMP_LEN				(0xffff << 16)
	 #घोषणा RX_TPA_START_CMP_LEN_SHIFT			 16

	u32 rx_tpa_start_cmp_opaque;
	__le32 rx_tpa_start_cmp_misc_v1;
	#घोषणा RX_TPA_START_CMP_V1				(0x1 << 0)
	#घोषणा RX_TPA_START_CMP_RSS_HASH_TYPE			(0x7f << 9)
	 #घोषणा RX_TPA_START_CMP_RSS_HASH_TYPE_SHIFT		 9
	#घोषणा RX_TPA_START_CMP_AGG_ID				(0x7f << 25)
	 #घोषणा RX_TPA_START_CMP_AGG_ID_SHIFT			 25
	#घोषणा RX_TPA_START_CMP_AGG_ID_P5			(0xffff << 16)
	 #घोषणा RX_TPA_START_CMP_AGG_ID_SHIFT_P5		 16

	__le32 rx_tpa_start_cmp_rss_hash;
पूर्ण;

#घोषणा TPA_START_HASH_VALID(rx_tpa_start)				\
	((rx_tpa_start)->rx_tpa_start_cmp_len_flags_type &		\
	 cpu_to_le32(RX_TPA_START_CMP_FLAGS_RSS_VALID))

#घोषणा TPA_START_HASH_TYPE(rx_tpa_start)				\
	(((le32_to_cpu((rx_tpa_start)->rx_tpa_start_cmp_misc_v1) &	\
	   RX_TPA_START_CMP_RSS_HASH_TYPE) >>				\
	  RX_TPA_START_CMP_RSS_HASH_TYPE_SHIFT) & RSS_PROखाता_ID_MASK)

#घोषणा TPA_START_AGG_ID(rx_tpa_start)					\
	((le32_to_cpu((rx_tpa_start)->rx_tpa_start_cmp_misc_v1) &	\
	 RX_TPA_START_CMP_AGG_ID) >> RX_TPA_START_CMP_AGG_ID_SHIFT)

#घोषणा TPA_START_AGG_ID_P5(rx_tpa_start)				\
	((le32_to_cpu((rx_tpa_start)->rx_tpa_start_cmp_misc_v1) &	\
	 RX_TPA_START_CMP_AGG_ID_P5) >> RX_TPA_START_CMP_AGG_ID_SHIFT_P5)

#घोषणा TPA_START_ERROR(rx_tpa_start)					\
	((rx_tpa_start)->rx_tpa_start_cmp_len_flags_type &		\
	 cpu_to_le32(RX_TPA_START_CMP_FLAGS_ERROR))

काष्ठा rx_tpa_start_cmp_ext अणु
	__le32 rx_tpa_start_cmp_flags2;
	#घोषणा RX_TPA_START_CMP_FLAGS2_IP_CS_CALC		(0x1 << 0)
	#घोषणा RX_TPA_START_CMP_FLAGS2_L4_CS_CALC		(0x1 << 1)
	#घोषणा RX_TPA_START_CMP_FLAGS2_T_IP_CS_CALC		(0x1 << 2)
	#घोषणा RX_TPA_START_CMP_FLAGS2_T_L4_CS_CALC		(0x1 << 3)
	#घोषणा RX_TPA_START_CMP_FLAGS2_IP_TYPE			(0x1 << 8)
	#घोषणा RX_TPA_START_CMP_FLAGS2_CSUM_CMPL_VALID		(0x1 << 9)
	#घोषणा RX_TPA_START_CMP_FLAGS2_EXT_META_FORMAT		(0x3 << 10)
	 #घोषणा RX_TPA_START_CMP_FLAGS2_EXT_META_FORMAT_SHIFT	 10
	#घोषणा RX_TPA_START_CMP_FLAGS2_CSUM_CMPL		(0xffff << 16)
	 #घोषणा RX_TPA_START_CMP_FLAGS2_CSUM_CMPL_SHIFT	 16

	__le32 rx_tpa_start_cmp_metadata;
	__le32 rx_tpa_start_cmp_cfa_code_v2;
	#घोषणा RX_TPA_START_CMP_V2				(0x1 << 0)
	#घोषणा RX_TPA_START_CMP_ERRORS_BUFFER_ERROR_MASK	(0x7 << 1)
	 #घोषणा RX_TPA_START_CMP_ERRORS_BUFFER_ERROR_SHIFT	 1
	 #घोषणा RX_TPA_START_CMP_ERRORS_BUFFER_ERROR_NO_BUFFER	 (0x0 << 1)
	 #घोषणा RX_TPA_START_CMP_ERRORS_BUFFER_ERROR_BAD_FORMAT (0x3 << 1)
	 #घोषणा RX_TPA_START_CMP_ERRORS_BUFFER_ERROR_FLUSH	 (0x5 << 1)
	#घोषणा RX_TPA_START_CMP_CFA_CODE			(0xffff << 16)
	 #घोषणा RX_TPA_START_CMPL_CFA_CODE_SHIFT		 16
	__le32 rx_tpa_start_cmp_hdr_info;
पूर्ण;

#घोषणा TPA_START_CFA_CODE(rx_tpa_start)				\
	((le32_to_cpu((rx_tpa_start)->rx_tpa_start_cmp_cfa_code_v2) &	\
	 RX_TPA_START_CMP_CFA_CODE) >> RX_TPA_START_CMPL_CFA_CODE_SHIFT)

#घोषणा TPA_START_IS_IPV6(rx_tpa_start)				\
	(!!((rx_tpa_start)->rx_tpa_start_cmp_flags2 &		\
	    cpu_to_le32(RX_TPA_START_CMP_FLAGS2_IP_TYPE)))

#घोषणा TPA_START_ERROR_CODE(rx_tpa_start)				\
	((le32_to_cpu((rx_tpa_start)->rx_tpa_start_cmp_cfa_code_v2) &	\
	  RX_TPA_START_CMP_ERRORS_BUFFER_ERROR_MASK) >>			\
	 RX_TPA_START_CMP_ERRORS_BUFFER_ERROR_SHIFT)

काष्ठा rx_tpa_end_cmp अणु
	__le32 rx_tpa_end_cmp_len_flags_type;
	#घोषणा RX_TPA_END_CMP_TYPE				(0x3f << 0)
	#घोषणा RX_TPA_END_CMP_FLAGS				(0x3ff << 6)
	 #घोषणा RX_TPA_END_CMP_FLAGS_SHIFT			 6
	#घोषणा RX_TPA_END_CMP_FLAGS_PLACEMENT			(0x7 << 7)
	 #घोषणा RX_TPA_END_CMP_FLAGS_PLACEMENT_SHIFT		 7
	 #घोषणा RX_TPA_END_CMP_FLAGS_PLACEMENT_JUMBO		 (0x1 << 7)
	 #घोषणा RX_TPA_END_CMP_FLAGS_PLACEMENT_HDS		 (0x2 << 7)
	 #घोषणा RX_TPA_END_CMP_FLAGS_PLACEMENT_GRO_JUMBO	 (0x5 << 7)
	 #घोषणा RX_TPA_END_CMP_FLAGS_PLACEMENT_GRO_HDS		 (0x6 << 7)
	#घोषणा RX_TPA_END_CMP_FLAGS_RSS_VALID			(0x1 << 10)
	#घोषणा RX_TPA_END_CMP_FLAGS_ITYPES			(0xf << 12)
	 #घोषणा RX_TPA_END_CMP_FLAGS_ITYPES_SHIFT		 12
	 #घोषणा RX_TPA_END_CMP_FLAGS_ITYPE_TCP			 (0x2 << 12)
	#घोषणा RX_TPA_END_CMP_LEN				(0xffff << 16)
	 #घोषणा RX_TPA_END_CMP_LEN_SHIFT			 16

	u32 rx_tpa_end_cmp_opaque;
	__le32 rx_tpa_end_cmp_misc_v1;
	#घोषणा RX_TPA_END_CMP_V1				(0x1 << 0)
	#घोषणा RX_TPA_END_CMP_AGG_BUFS				(0x3f << 1)
	 #घोषणा RX_TPA_END_CMP_AGG_BUFS_SHIFT			 1
	#घोषणा RX_TPA_END_CMP_TPA_SEGS				(0xff << 8)
	 #घोषणा RX_TPA_END_CMP_TPA_SEGS_SHIFT			 8
	#घोषणा RX_TPA_END_CMP_PAYLOAD_OFFSET			(0xff << 16)
	 #घोषणा RX_TPA_END_CMP_PAYLOAD_OFFSET_SHIFT		 16
	#घोषणा RX_TPA_END_CMP_AGG_ID				(0x7f << 25)
	 #घोषणा RX_TPA_END_CMP_AGG_ID_SHIFT			 25
	#घोषणा RX_TPA_END_CMP_AGG_ID_P5			(0xffff << 16)
	 #घोषणा RX_TPA_END_CMP_AGG_ID_SHIFT_P5			 16

	__le32 rx_tpa_end_cmp_tsdelta;
	#घोषणा RX_TPA_END_GRO_TS				(0x1 << 31)
पूर्ण;

#घोषणा TPA_END_AGG_ID(rx_tpa_end)					\
	((le32_to_cpu((rx_tpa_end)->rx_tpa_end_cmp_misc_v1) &		\
	 RX_TPA_END_CMP_AGG_ID) >> RX_TPA_END_CMP_AGG_ID_SHIFT)

#घोषणा TPA_END_AGG_ID_P5(rx_tpa_end)					\
	((le32_to_cpu((rx_tpa_end)->rx_tpa_end_cmp_misc_v1) &		\
	 RX_TPA_END_CMP_AGG_ID_P5) >> RX_TPA_END_CMP_AGG_ID_SHIFT_P5)

#घोषणा TPA_END_PAYLOAD_OFF(rx_tpa_end)					\
	((le32_to_cpu((rx_tpa_end)->rx_tpa_end_cmp_misc_v1) &		\
	 RX_TPA_END_CMP_PAYLOAD_OFFSET) >> RX_TPA_END_CMP_PAYLOAD_OFFSET_SHIFT)

#घोषणा TPA_END_AGG_BUFS(rx_tpa_end)					\
	((le32_to_cpu((rx_tpa_end)->rx_tpa_end_cmp_misc_v1) &		\
	 RX_TPA_END_CMP_AGG_BUFS) >> RX_TPA_END_CMP_AGG_BUFS_SHIFT)

#घोषणा TPA_END_TPA_SEGS(rx_tpa_end)					\
	((le32_to_cpu((rx_tpa_end)->rx_tpa_end_cmp_misc_v1) &		\
	 RX_TPA_END_CMP_TPA_SEGS) >> RX_TPA_END_CMP_TPA_SEGS_SHIFT)

#घोषणा RX_TPA_END_CMP_FLAGS_PLACEMENT_ANY_GRO				\
	cpu_to_le32(RX_TPA_END_CMP_FLAGS_PLACEMENT_GRO_JUMBO &		\
		    RX_TPA_END_CMP_FLAGS_PLACEMENT_GRO_HDS)

#घोषणा TPA_END_GRO(rx_tpa_end)						\
	((rx_tpa_end)->rx_tpa_end_cmp_len_flags_type &			\
	 RX_TPA_END_CMP_FLAGS_PLACEMENT_ANY_GRO)

#घोषणा TPA_END_GRO_TS(rx_tpa_end)					\
	(!!((rx_tpa_end)->rx_tpa_end_cmp_tsdelta &			\
	    cpu_to_le32(RX_TPA_END_GRO_TS)))

काष्ठा rx_tpa_end_cmp_ext अणु
	__le32 rx_tpa_end_cmp_dup_acks;
	#घोषणा RX_TPA_END_CMP_TPA_DUP_ACKS			(0xf << 0)
	#घोषणा RX_TPA_END_CMP_PAYLOAD_OFFSET_P5		(0xff << 16)
	 #घोषणा RX_TPA_END_CMP_PAYLOAD_OFFSET_SHIFT_P5		 16
	#घोषणा RX_TPA_END_CMP_AGG_BUFS_P5			(0xff << 24)
	 #घोषणा RX_TPA_END_CMP_AGG_BUFS_SHIFT_P5		 24

	__le32 rx_tpa_end_cmp_seg_len;
	#घोषणा RX_TPA_END_CMP_TPA_SEG_LEN			(0xffff << 0)

	__le32 rx_tpa_end_cmp_errors_v2;
	#घोषणा RX_TPA_END_CMP_V2				(0x1 << 0)
	#घोषणा RX_TPA_END_CMP_ERRORS				(0x3 << 1)
	#घोषणा RX_TPA_END_CMP_ERRORS_P5			(0x7 << 1)
	#घोषणा RX_TPA_END_CMPL_ERRORS_SHIFT			 1
	 #घोषणा RX_TPA_END_CMP_ERRORS_BUFFER_ERROR_NO_BUFFER	 (0x0 << 1)
	 #घोषणा RX_TPA_END_CMP_ERRORS_BUFFER_ERROR_NOT_ON_CHIP	 (0x2 << 1)
	 #घोषणा RX_TPA_END_CMP_ERRORS_BUFFER_ERROR_BAD_FORMAT	 (0x3 << 1)
	 #घोषणा RX_TPA_END_CMP_ERRORS_BUFFER_ERROR_RSV_ERROR	 (0x4 << 1)
	 #घोषणा RX_TPA_END_CMP_ERRORS_BUFFER_ERROR_FLUSH	 (0x5 << 1)

	u32 rx_tpa_end_cmp_start_opaque;
पूर्ण;

#घोषणा TPA_END_ERRORS(rx_tpa_end_ext)					\
	((rx_tpa_end_ext)->rx_tpa_end_cmp_errors_v2 &			\
	 cpu_to_le32(RX_TPA_END_CMP_ERRORS))

#घोषणा TPA_END_PAYLOAD_OFF_P5(rx_tpa_end_ext)				\
	((le32_to_cpu((rx_tpa_end_ext)->rx_tpa_end_cmp_dup_acks) &	\
	 RX_TPA_END_CMP_PAYLOAD_OFFSET_P5) >>				\
	RX_TPA_END_CMP_PAYLOAD_OFFSET_SHIFT_P5)

#घोषणा TPA_END_AGG_BUFS_P5(rx_tpa_end_ext)				\
	((le32_to_cpu((rx_tpa_end_ext)->rx_tpa_end_cmp_dup_acks) &	\
	 RX_TPA_END_CMP_AGG_BUFS_P5) >> RX_TPA_END_CMP_AGG_BUFS_SHIFT_P5)

#घोषणा EVENT_DATA1_RESET_NOTIFY_FATAL(data1)				\
	(((data1) &							\
	  ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_REASON_CODE_MASK) ==\
	 ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_REASON_CODE_FW_EXCEPTION_FATAL)

#घोषणा EVENT_DATA1_RECOVERY_MASTER_FUNC(data1)				\
	!!((data1) &							\
	   ASYNC_EVENT_CMPL_ERROR_RECOVERY_EVENT_DATA1_FLAGS_MASTER_FUNC)

#घोषणा EVENT_DATA1_RECOVERY_ENABLED(data1)				\
	!!((data1) &							\
	   ASYNC_EVENT_CMPL_ERROR_RECOVERY_EVENT_DATA1_FLAGS_RECOVERY_ENABLED)

काष्ठा nqe_cn अणु
	__le16	type;
	#घोषणा NQ_CN_TYPE_MASK           0x3fUL
	#घोषणा NQ_CN_TYPE_SFT            0
	#घोषणा NQ_CN_TYPE_CQ_NOTIFICATION  0x30UL
	#घोषणा NQ_CN_TYPE_LAST            NQ_CN_TYPE_CQ_NOTIFICATION
	__le16	reserved16;
	__le32	cq_handle_low;
	__le32	v;
	#घोषणा NQ_CN_V     0x1UL
	__le32	cq_handle_high;
पूर्ण;

#घोषणा DB_IDX_MASK						0xffffff
#घोषणा DB_IDX_VALID						(0x1 << 26)
#घोषणा DB_IRQ_DIS						(0x1 << 27)
#घोषणा DB_KEY_TX						(0x0 << 28)
#घोषणा DB_KEY_RX						(0x1 << 28)
#घोषणा DB_KEY_CP						(0x2 << 28)
#घोषणा DB_KEY_ST						(0x3 << 28)
#घोषणा DB_KEY_TX_PUSH						(0x4 << 28)
#घोषणा DB_LONG_TX_PUSH						(0x2 << 24)

#घोषणा BNXT_MIN_ROCE_CP_RINGS	2
#घोषणा BNXT_MIN_ROCE_STAT_CTXS	1

/* 64-bit करोorbell */
#घोषणा DBR_INDEX_MASK					0x0000000000ffffffULL
#घोषणा DBR_XID_MASK					0x000fffff00000000ULL
#घोषणा DBR_XID_SFT					32
#घोषणा DBR_PATH_L2					(0x1ULL << 56)
#घोषणा DBR_TYPE_SQ					(0x0ULL << 60)
#घोषणा DBR_TYPE_RQ					(0x1ULL << 60)
#घोषणा DBR_TYPE_SRQ					(0x2ULL << 60)
#घोषणा DBR_TYPE_SRQ_ARM				(0x3ULL << 60)
#घोषणा DBR_TYPE_CQ					(0x4ULL << 60)
#घोषणा DBR_TYPE_CQ_ARMSE				(0x5ULL << 60)
#घोषणा DBR_TYPE_CQ_ARMALL				(0x6ULL << 60)
#घोषणा DBR_TYPE_CQ_ARMENA				(0x7ULL << 60)
#घोषणा DBR_TYPE_SRQ_ARMENA				(0x8ULL << 60)
#घोषणा DBR_TYPE_CQ_CUTOFF_ACK				(0x9ULL << 60)
#घोषणा DBR_TYPE_NQ					(0xaULL << 60)
#घोषणा DBR_TYPE_NQ_ARM					(0xbULL << 60)
#घोषणा DBR_TYPE_शून्य					(0xfULL << 60)

#घोषणा DB_PF_OFFSET_P5					0x10000
#घोषणा DB_VF_OFFSET_P5					0x4000

#घोषणा INVALID_HW_RING_ID	((u16)-1)

/* The hardware supports certain page sizes.  Use the supported page sizes
 * to allocate the rings.
 */
#अगर (PAGE_SHIFT < 12)
#घोषणा BNXT_PAGE_SHIFT	12
#या_अगर (PAGE_SHIFT <= 13)
#घोषणा BNXT_PAGE_SHIFT	PAGE_SHIFT
#या_अगर (PAGE_SHIFT < 16)
#घोषणा BNXT_PAGE_SHIFT	13
#अन्यथा
#घोषणा BNXT_PAGE_SHIFT	16
#पूर्ण_अगर

#घोषणा BNXT_PAGE_SIZE	(1 << BNXT_PAGE_SHIFT)

/* The RXBD length is 16-bit so we can only support page sizes < 64K */
#अगर (PAGE_SHIFT > 15)
#घोषणा BNXT_RX_PAGE_SHIFT 15
#अन्यथा
#घोषणा BNXT_RX_PAGE_SHIFT PAGE_SHIFT
#पूर्ण_अगर

#घोषणा BNXT_RX_PAGE_SIZE (1 << BNXT_RX_PAGE_SHIFT)

#घोषणा BNXT_MAX_MTU		9500
#घोषणा BNXT_MAX_PAGE_MODE_MTU	\
	((अचिन्हित पूर्णांक)PAGE_SIZE - VLAN_ETH_HLEN - NET_IP_ALIGN -	\
	 XDP_PACKET_HEADROOM)

#घोषणा BNXT_MIN_PKT_SIZE	52

#घोषणा BNXT_DEFAULT_RX_RING_SIZE	511
#घोषणा BNXT_DEFAULT_TX_RING_SIZE	511

#घोषणा MAX_TPA		64
#घोषणा MAX_TPA_P5	256
#घोषणा MAX_TPA_P5_MASK	(MAX_TPA_P5 - 1)
#घोषणा MAX_TPA_SEGS_P5	0x3f

#अगर (BNXT_PAGE_SHIFT == 16)
#घोषणा MAX_RX_PAGES	1
#घोषणा MAX_RX_AGG_PAGES	4
#घोषणा MAX_TX_PAGES	1
#घोषणा MAX_CP_PAGES	8
#अन्यथा
#घोषणा MAX_RX_PAGES	8
#घोषणा MAX_RX_AGG_PAGES	32
#घोषणा MAX_TX_PAGES	8
#घोषणा MAX_CP_PAGES	64
#पूर्ण_अगर

#घोषणा RX_DESC_CNT (BNXT_PAGE_SIZE / माप(काष्ठा rx_bd))
#घोषणा TX_DESC_CNT (BNXT_PAGE_SIZE / माप(काष्ठा tx_bd))
#घोषणा CP_DESC_CNT (BNXT_PAGE_SIZE / माप(काष्ठा tx_cmp))

#घोषणा SW_RXBD_RING_SIZE (माप(काष्ठा bnxt_sw_rx_bd) * RX_DESC_CNT)
#घोषणा HW_RXBD_RING_SIZE (माप(काष्ठा rx_bd) * RX_DESC_CNT)

#घोषणा SW_RXBD_AGG_RING_SIZE (माप(काष्ठा bnxt_sw_rx_agg_bd) * RX_DESC_CNT)

#घोषणा SW_TXBD_RING_SIZE (माप(काष्ठा bnxt_sw_tx_bd) * TX_DESC_CNT)
#घोषणा HW_TXBD_RING_SIZE (माप(काष्ठा tx_bd) * TX_DESC_CNT)

#घोषणा HW_CMPD_RING_SIZE (माप(काष्ठा tx_cmp) * CP_DESC_CNT)

#घोषणा BNXT_MAX_RX_DESC_CNT		(RX_DESC_CNT * MAX_RX_PAGES - 1)
#घोषणा BNXT_MAX_RX_JUM_DESC_CNT	(RX_DESC_CNT * MAX_RX_AGG_PAGES - 1)
#घोषणा BNXT_MAX_TX_DESC_CNT		(TX_DESC_CNT * MAX_TX_PAGES - 1)

#घोषणा RX_RING(x)	(((x) & ~(RX_DESC_CNT - 1)) >> (BNXT_PAGE_SHIFT - 4))
#घोषणा RX_IDX(x)	((x) & (RX_DESC_CNT - 1))

#घोषणा TX_RING(x)	(((x) & ~(TX_DESC_CNT - 1)) >> (BNXT_PAGE_SHIFT - 4))
#घोषणा TX_IDX(x)	((x) & (TX_DESC_CNT - 1))

#घोषणा CP_RING(x)	(((x) & ~(CP_DESC_CNT - 1)) >> (BNXT_PAGE_SHIFT - 4))
#घोषणा CP_IDX(x)	((x) & (CP_DESC_CNT - 1))

#घोषणा TX_CMP_VALID(txcmp, raw_cons)					\
	(!!((txcmp)->tx_cmp_errors_v & cpu_to_le32(TX_CMP_V)) ==	\
	 !((raw_cons) & bp->cp_bit))

#घोषणा RX_CMP_VALID(rxcmp1, raw_cons)					\
	(!!((rxcmp1)->rx_cmp_cfa_code_errors_v2 & cpu_to_le32(RX_CMP_V)) ==\
	 !((raw_cons) & bp->cp_bit))

#घोषणा RX_AGG_CMP_VALID(agg, raw_cons)				\
	(!!((agg)->rx_agg_cmp_v & cpu_to_le32(RX_AGG_CMP_V)) ==	\
	 !((raw_cons) & bp->cp_bit))

#घोषणा NQ_CMP_VALID(nqcmp, raw_cons)				\
	(!!((nqcmp)->v & cpu_to_le32(NQ_CN_V)) == !((raw_cons) & bp->cp_bit))

#घोषणा TX_CMP_TYPE(txcmp)					\
	(le32_to_cpu((txcmp)->tx_cmp_flags_type) & CMP_TYPE)

#घोषणा RX_CMP_TYPE(rxcmp)					\
	(le32_to_cpu((rxcmp)->rx_cmp_len_flags_type) & RX_CMP_CMP_TYPE)

#घोषणा NEXT_RX(idx)		(((idx) + 1) & bp->rx_ring_mask)

#घोषणा NEXT_RX_AGG(idx)	(((idx) + 1) & bp->rx_agg_ring_mask)

#घोषणा NEXT_TX(idx)		(((idx) + 1) & bp->tx_ring_mask)

#घोषणा ADV_RAW_CMP(idx, n)	((idx) + (n))
#घोषणा NEXT_RAW_CMP(idx)	ADV_RAW_CMP(idx, 1)
#घोषणा RING_CMP(idx)		((idx) & bp->cp_ring_mask)
#घोषणा NEXT_CMP(idx)		RING_CMP(ADV_RAW_CMP(idx, 1))

#घोषणा BNXT_HWRM_MAX_REQ_LEN		(bp->hwrm_max_req_len)
#घोषणा BNXT_HWRM_SHORT_REQ_LEN		माप(काष्ठा hwrm_लघु_input)
#घोषणा DFLT_HWRM_CMD_TIMEOUT		500
#घोषणा HWRM_CMD_MAX_TIMEOUT		40000
#घोषणा SHORT_HWRM_CMD_TIMEOUT		20
#घोषणा HWRM_CMD_TIMEOUT		(bp->hwrm_cmd_समयout)
#घोषणा HWRM_RESET_TIMEOUT		((HWRM_CMD_TIMEOUT) * 4)
#घोषणा HWRM_COREDUMP_TIMEOUT		((HWRM_CMD_TIMEOUT) * 12)
#घोषणा BNXT_HWRM_REQ_MAX_SIZE		128
#घोषणा BNXT_HWRM_REQS_PER_PAGE		(BNXT_PAGE_SIZE /	\
					 BNXT_HWRM_REQ_MAX_SIZE)
#घोषणा HWRM_SHORT_MIN_TIMEOUT		3
#घोषणा HWRM_SHORT_MAX_TIMEOUT		10
#घोषणा HWRM_SHORT_TIMEOUT_COUNTER	5

#घोषणा HWRM_MIN_TIMEOUT		25
#घोषणा HWRM_MAX_TIMEOUT		40

#घोषणा HWRM_WAIT_MUST_ABORT(bp, req)					\
	(le16_to_cpu((req)->req_type) != HWRM_VER_GET &&		\
	 !bnxt_is_fw_healthy(bp))

#घोषणा HWRM_TOTAL_TIMEOUT(n)	(((n) <= HWRM_SHORT_TIMEOUT_COUNTER) ?	\
	((n) * HWRM_SHORT_MIN_TIMEOUT) :				\
	(HWRM_SHORT_TIMEOUT_COUNTER * HWRM_SHORT_MIN_TIMEOUT +		\
	 ((n) - HWRM_SHORT_TIMEOUT_COUNTER) * HWRM_MIN_TIMEOUT))

#घोषणा HWRM_VALID_BIT_DELAY_USEC	150

#घोषणा BNXT_HWRM_CHNL_CHIMP	0
#घोषणा BNXT_HWRM_CHNL_KONG	1

#घोषणा BNXT_RX_EVENT		1
#घोषणा BNXT_AGG_EVENT		2
#घोषणा BNXT_TX_EVENT		4
#घोषणा BNXT_REसूचीECT_EVENT	8

काष्ठा bnxt_sw_tx_bd अणु
	जोड़ अणु
		काष्ठा sk_buff		*skb;
		काष्ठा xdp_frame	*xdpf;
	पूर्ण;
	DEFINE_DMA_UNMAP_ADDR(mapping);
	DEFINE_DMA_UNMAP_LEN(len);
	u8			is_gso;
	u8			is_push;
	u8			action;
	जोड़ अणु
		अचिन्हित लघु		nr_frags;
		u16			rx_prod;
	पूर्ण;
पूर्ण;

काष्ठा bnxt_sw_rx_bd अणु
	व्योम			*data;
	u8			*data_ptr;
	dma_addr_t		mapping;
पूर्ण;

काष्ठा bnxt_sw_rx_agg_bd अणु
	काष्ठा page		*page;
	अचिन्हित पूर्णांक		offset;
	dma_addr_t		mapping;
पूर्ण;

काष्ठा bnxt_mem_init अणु
	u8	init_val;
	u16	offset;
#घोषणा	BNXT_MEM_INVALID_OFFSET	0xffff
	u16	size;
पूर्ण;

काष्ठा bnxt_ring_mem_info अणु
	पूर्णांक			nr_pages;
	पूर्णांक			page_size;
	u16			flags;
#घोषणा BNXT_RMEM_VALID_PTE_FLAG	1
#घोषणा BNXT_RMEM_RING_PTE_FLAG		2
#घोषणा BNXT_RMEM_USE_FULL_PAGE_FLAG	4

	u16			depth;
	काष्ठा bnxt_mem_init	*mem_init;

	व्योम			**pg_arr;
	dma_addr_t		*dma_arr;

	__le64			*pg_tbl;
	dma_addr_t		pg_tbl_map;

	पूर्णांक			vmem_size;
	व्योम			**vmem;
पूर्ण;

काष्ठा bnxt_ring_काष्ठा अणु
	काष्ठा bnxt_ring_mem_info	ring_mem;

	u16			fw_ring_id; /* Ring id filled by Chimp FW */
	जोड़ अणु
		u16		grp_idx;
		u16		map_idx; /* Used by cmpl rings */
	पूर्ण;
	u32			handle;
	u8			queue_id;
पूर्ण;

काष्ठा tx_push_bd अणु
	__le32			करोorbell;
	__le32			tx_bd_len_flags_type;
	u32			tx_bd_opaque;
	काष्ठा tx_bd_ext	txbd2;
पूर्ण;

काष्ठा tx_push_buffer अणु
	काष्ठा tx_push_bd	push_bd;
	u32			data[25];
पूर्ण;

काष्ठा bnxt_db_info अणु
	व्योम __iomem		*करोorbell;
	जोड़ अणु
		u64		db_key64;
		u32		db_key32;
	पूर्ण;
पूर्ण;

काष्ठा bnxt_tx_ring_info अणु
	काष्ठा bnxt_napi	*bnapi;
	u16			tx_prod;
	u16			tx_cons;
	u16			txq_index;
	काष्ठा bnxt_db_info	tx_db;

	काष्ठा tx_bd		*tx_desc_ring[MAX_TX_PAGES];
	काष्ठा bnxt_sw_tx_bd	*tx_buf_ring;

	dma_addr_t		tx_desc_mapping[MAX_TX_PAGES];

	काष्ठा tx_push_buffer	*tx_push;
	dma_addr_t		tx_push_mapping;
	__le64			data_mapping;

#घोषणा BNXT_DEV_STATE_CLOSING	0x1
	u32			dev_state;

	काष्ठा bnxt_ring_काष्ठा	tx_ring_काष्ठा;
पूर्ण;

#घोषणा BNXT_LEGACY_COAL_CMPL_PARAMS					\
	(RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_INT_LAT_TMR_MIN |		\
	 RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_INT_LAT_TMR_MAX |		\
	 RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_TIMER_RESET |		\
	 RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_RING_IDLE |			\
	 RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_NUM_CMPL_DMA_AGGR |		\
	 RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_NUM_CMPL_DMA_AGGR_DURING_INT | \
	 RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_CMPL_AGGR_DMA_TMR |		\
	 RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_CMPL_AGGR_DMA_TMR_DURING_INT | \
	 RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_NUM_CMPL_AGGR_INT)

#घोषणा BNXT_COAL_CMPL_ENABLES						\
	(RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_ENABLES_NUM_CMPL_DMA_AGGR | \
	 RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_ENABLES_CMPL_AGGR_DMA_TMR | \
	 RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_ENABLES_INT_LAT_TMR_MAX | \
	 RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_ENABLES_NUM_CMPL_AGGR_INT)

#घोषणा BNXT_COAL_CMPL_MIN_TMR_ENABLE					\
	RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_ENABLES_INT_LAT_TMR_MIN

#घोषणा BNXT_COAL_CMPL_AGGR_TMR_DURING_INT_ENABLE			\
	RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_ENABLES_NUM_CMPL_DMA_AGGR_DURING_INT

काष्ठा bnxt_coal_cap अणु
	u32			cmpl_params;
	u32			nq_params;
	u16			num_cmpl_dma_aggr_max;
	u16			num_cmpl_dma_aggr_during_पूर्णांक_max;
	u16			cmpl_aggr_dma_पंचांगr_max;
	u16			cmpl_aggr_dma_पंचांगr_during_पूर्णांक_max;
	u16			पूर्णांक_lat_पंचांगr_min_max;
	u16			पूर्णांक_lat_पंचांगr_max_max;
	u16			num_cmpl_aggr_पूर्णांक_max;
	u16			समयr_units;
पूर्ण;

काष्ठा bnxt_coal अणु
	u16			coal_ticks;
	u16			coal_ticks_irq;
	u16			coal_bufs;
	u16			coal_bufs_irq;
			/* RING_IDLE enabled when coal ticks < idle_thresh  */
	u16			idle_thresh;
	u8			bufs_per_record;
	u8			budget;
पूर्ण;

काष्ठा bnxt_tpa_info अणु
	व्योम			*data;
	u8			*data_ptr;
	dma_addr_t		mapping;
	u16			len;
	अचिन्हित लघु		gso_type;
	u32			flags2;
	u32			metadata;
	क्रमागत pkt_hash_types	hash_type;
	u32			rss_hash;
	u32			hdr_info;

#घोषणा BNXT_TPA_L4_SIZE(hdr_info)	\
	(((hdr_info) & 0xf8000000) ? ((hdr_info) >> 27) : 32)

#घोषणा BNXT_TPA_INNER_L3_OFF(hdr_info)	\
	(((hdr_info) >> 18) & 0x1ff)

#घोषणा BNXT_TPA_INNER_L2_OFF(hdr_info)	\
	(((hdr_info) >> 9) & 0x1ff)

#घोषणा BNXT_TPA_OUTER_L3_OFF(hdr_info)	\
	((hdr_info) & 0x1ff)

	u16			cfa_code; /* cfa_code in TPA start compl */
	u8			agg_count;
	काष्ठा rx_agg_cmp	*agg_arr;
पूर्ण;

#घोषणा BNXT_AGG_IDX_BMAP_SIZE	(MAX_TPA_P5 / BITS_PER_LONG)

काष्ठा bnxt_tpa_idx_map अणु
	u16		agg_id_tbl[1024];
	अचिन्हित दीर्घ	agg_idx_bmap[BNXT_AGG_IDX_BMAP_SIZE];
पूर्ण;

काष्ठा bnxt_rx_ring_info अणु
	काष्ठा bnxt_napi	*bnapi;
	u16			rx_prod;
	u16			rx_agg_prod;
	u16			rx_sw_agg_prod;
	u16			rx_next_cons;
	काष्ठा bnxt_db_info	rx_db;
	काष्ठा bnxt_db_info	rx_agg_db;

	काष्ठा bpf_prog		*xdp_prog;

	काष्ठा rx_bd		*rx_desc_ring[MAX_RX_PAGES];
	काष्ठा bnxt_sw_rx_bd	*rx_buf_ring;

	काष्ठा rx_bd		*rx_agg_desc_ring[MAX_RX_AGG_PAGES];
	काष्ठा bnxt_sw_rx_agg_bd	*rx_agg_ring;

	अचिन्हित दीर्घ		*rx_agg_bmap;
	u16			rx_agg_bmap_size;

	काष्ठा page		*rx_page;
	अचिन्हित पूर्णांक		rx_page_offset;

	dma_addr_t		rx_desc_mapping[MAX_RX_PAGES];
	dma_addr_t		rx_agg_desc_mapping[MAX_RX_AGG_PAGES];

	काष्ठा bnxt_tpa_info	*rx_tpa;
	काष्ठा bnxt_tpa_idx_map *rx_tpa_idx_map;

	काष्ठा bnxt_ring_काष्ठा	rx_ring_काष्ठा;
	काष्ठा bnxt_ring_काष्ठा	rx_agg_ring_काष्ठा;
	काष्ठा xdp_rxq_info	xdp_rxq;
	काष्ठा page_pool	*page_pool;
पूर्ण;

काष्ठा bnxt_rx_sw_stats अणु
	u64			rx_l4_csum_errors;
	u64			rx_resets;
	u64			rx_buf_errors;
पूर्ण;

काष्ठा bnxt_cmn_sw_stats अणु
	u64			missed_irqs;
पूर्ण;

काष्ठा bnxt_sw_stats अणु
	काष्ठा bnxt_rx_sw_stats rx;
	काष्ठा bnxt_cmn_sw_stats cmn;
पूर्ण;

काष्ठा bnxt_stats_mem अणु
	u64		*sw_stats;
	u64		*hw_masks;
	व्योम		*hw_stats;
	dma_addr_t	hw_stats_map;
	पूर्णांक		len;
पूर्ण;

काष्ठा bnxt_cp_ring_info अणु
	काष्ठा bnxt_napi	*bnapi;
	u32			cp_raw_cons;
	काष्ठा bnxt_db_info	cp_db;

	u8			had_work_करोne:1;
	u8			has_more_work:1;

	u32			last_cp_raw_cons;

	काष्ठा bnxt_coal	rx_ring_coal;
	u64			rx_packets;
	u64			rx_bytes;
	u64			event_ctr;

	काष्ठा dim		dim;

	जोड़ अणु
		काष्ठा tx_cmp	*cp_desc_ring[MAX_CP_PAGES];
		काष्ठा nqe_cn	*nq_desc_ring[MAX_CP_PAGES];
	पूर्ण;

	dma_addr_t		cp_desc_mapping[MAX_CP_PAGES];

	काष्ठा bnxt_stats_mem	stats;
	u32			hw_stats_ctx_id;

	काष्ठा bnxt_sw_stats	sw_stats;

	काष्ठा bnxt_ring_काष्ठा	cp_ring_काष्ठा;

	काष्ठा bnxt_cp_ring_info *cp_ring_arr[2];
#घोषणा BNXT_RX_HDL	0
#घोषणा BNXT_TX_HDL	1
पूर्ण;

काष्ठा bnxt_napi अणु
	काष्ठा napi_काष्ठा	napi;
	काष्ठा bnxt		*bp;

	पूर्णांक			index;
	काष्ठा bnxt_cp_ring_info	cp_ring;
	काष्ठा bnxt_rx_ring_info	*rx_ring;
	काष्ठा bnxt_tx_ring_info	*tx_ring;

	व्योम			(*tx_पूर्णांक)(काष्ठा bnxt *, काष्ठा bnxt_napi *,
					  पूर्णांक);
	पूर्णांक			tx_pkts;
	u8			events;

	u32			flags;
#घोषणा BNXT_NAPI_FLAG_XDP	0x1

	bool			in_reset;
पूर्ण;

काष्ठा bnxt_irq अणु
	irq_handler_t	handler;
	अचिन्हित पूर्णांक	vector;
	u8		requested:1;
	u8		have_cpumask:1;
	अक्षर		name[IFNAMSIZ + 2];
	cpumask_var_t	cpu_mask;
पूर्ण;

#घोषणा HWRM_RING_ALLOC_TX	0x1
#घोषणा HWRM_RING_ALLOC_RX	0x2
#घोषणा HWRM_RING_ALLOC_AGG	0x4
#घोषणा HWRM_RING_ALLOC_CMPL	0x8
#घोषणा HWRM_RING_ALLOC_NQ	0x10

#घोषणा INVALID_STATS_CTX_ID	-1

काष्ठा bnxt_ring_grp_info अणु
	u16	fw_stats_ctx;
	u16	fw_grp_id;
	u16	rx_fw_ring_id;
	u16	agg_fw_ring_id;
	u16	cp_fw_ring_id;
पूर्ण;

काष्ठा bnxt_vnic_info अणु
	u16		fw_vnic_id; /* वापसed by Chimp during alloc */
#घोषणा BNXT_MAX_CTX_PER_VNIC	8
	u16		fw_rss_cos_lb_ctx[BNXT_MAX_CTX_PER_VNIC];
	u16		fw_l2_ctx_id;
#घोषणा BNXT_MAX_UC_ADDRS	4
	__le64		fw_l2_filter_id[BNXT_MAX_UC_ADDRS];
				/* index 0 always dev_addr */
	u16		uc_filter_count;
	u8		*uc_list;

	u16		*fw_grp_ids;
	dma_addr_t	rss_table_dma_addr;
	__le16		*rss_table;
	dma_addr_t	rss_hash_key_dma_addr;
	u64		*rss_hash_key;
	पूर्णांक		rss_table_size;
#घोषणा BNXT_RSS_TABLE_ENTRIES_P5	64
#घोषणा BNXT_RSS_TABLE_SIZE_P5		(BNXT_RSS_TABLE_ENTRIES_P5 * 4)
#घोषणा BNXT_RSS_TABLE_MAX_TBL_P5	8
#घोषणा BNXT_MAX_RSS_TABLE_SIZE_P5				\
	(BNXT_RSS_TABLE_SIZE_P5 * BNXT_RSS_TABLE_MAX_TBL_P5)
#घोषणा BNXT_MAX_RSS_TABLE_ENTRIES_P5				\
	(BNXT_RSS_TABLE_ENTRIES_P5 * BNXT_RSS_TABLE_MAX_TBL_P5)

	u32		rx_mask;

	u8		*mc_list;
	पूर्णांक		mc_list_size;
	पूर्णांक		mc_list_count;
	dma_addr_t	mc_list_mapping;
#घोषणा BNXT_MAX_MC_ADDRS	16

	u32		flags;
#घोषणा BNXT_VNIC_RSS_FLAG	1
#घोषणा BNXT_VNIC_RFS_FLAG	2
#घोषणा BNXT_VNIC_MCAST_FLAG	4
#घोषणा BNXT_VNIC_UCAST_FLAG	8
#घोषणा BNXT_VNIC_RFS_NEW_RSS_FLAG	0x10
पूर्ण;

काष्ठा bnxt_hw_resc अणु
	u16	min_rsscos_ctxs;
	u16	max_rsscos_ctxs;
	u16	min_cp_rings;
	u16	max_cp_rings;
	u16	resv_cp_rings;
	u16	min_tx_rings;
	u16	max_tx_rings;
	u16	resv_tx_rings;
	u16	max_tx_sch_inमाला_दो;
	u16	min_rx_rings;
	u16	max_rx_rings;
	u16	resv_rx_rings;
	u16	min_hw_ring_grps;
	u16	max_hw_ring_grps;
	u16	resv_hw_ring_grps;
	u16	min_l2_ctxs;
	u16	max_l2_ctxs;
	u16	min_vnics;
	u16	max_vnics;
	u16	resv_vnics;
	u16	min_stat_ctxs;
	u16	max_stat_ctxs;
	u16	resv_stat_ctxs;
	u16	max_nqs;
	u16	max_irqs;
	u16	resv_irqs;
पूर्ण;

#अगर defined(CONFIG_BNXT_SRIOV)
काष्ठा bnxt_vf_info अणु
	u16	fw_fid;
	u8	mac_addr[ETH_ALEN];	/* PF asचिन्हित MAC Address */
	u8	vf_mac_addr[ETH_ALEN];	/* VF asचिन्हित MAC address, only
					 * stored by PF.
					 */
	u16	vlan;
	u16	func_qcfg_flags;
	u32	flags;
#घोषणा BNXT_VF_QOS		0x1
#घोषणा BNXT_VF_SPOOFCHK	0x2
#घोषणा BNXT_VF_LINK_FORCED	0x4
#घोषणा BNXT_VF_LINK_UP		0x8
#घोषणा BNXT_VF_TRUST		0x10
	u32	min_tx_rate;
	u32	max_tx_rate;
	व्योम	*hwrm_cmd_req_addr;
	dma_addr_t	hwrm_cmd_req_dma_addr;
पूर्ण;
#पूर्ण_अगर

काष्ठा bnxt_pf_info अणु
#घोषणा BNXT_FIRST_PF_FID	1
#घोषणा BNXT_FIRST_VF_FID	128
	u16	fw_fid;
	u16	port_id;
	u8	mac_addr[ETH_ALEN];
	u32	first_vf_id;
	u16	active_vfs;
	u16	रेजिस्टरed_vfs;
	u16	max_vfs;
	u32	max_encap_records;
	u32	max_decap_records;
	u32	max_tx_em_flows;
	u32	max_tx_wm_flows;
	u32	max_rx_em_flows;
	u32	max_rx_wm_flows;
	अचिन्हित दीर्घ	*vf_event_bmap;
	u16	hwrm_cmd_req_pages;
	u8	vf_resv_strategy;
#घोषणा BNXT_VF_RESV_STRATEGY_MAXIMAL	0
#घोषणा BNXT_VF_RESV_STRATEGY_MINIMAL	1
#घोषणा BNXT_VF_RESV_STRATEGY_MINIMAL_STATIC	2
	व्योम			*hwrm_cmd_req_addr[4];
	dma_addr_t		hwrm_cmd_req_dma_addr[4];
	काष्ठा bnxt_vf_info	*vf;
पूर्ण;

काष्ठा bnxt_ntuple_filter अणु
	काष्ठा hlist_node	hash;
	u8			dst_mac_addr[ETH_ALEN];
	u8			src_mac_addr[ETH_ALEN];
	काष्ठा flow_keys	fkeys;
	__le64			filter_id;
	u16			sw_id;
	u8			l2_fltr_idx;
	u16			rxq;
	u32			flow_id;
	अचिन्हित दीर्घ		state;
#घोषणा BNXT_FLTR_VALID		0
#घोषणा BNXT_FLTR_UPDATE	1
पूर्ण;

काष्ठा bnxt_link_info अणु
	u8			phy_type;
	u8			media_type;
	u8			transceiver;
	u8			phy_addr;
	u8			phy_link_status;
#घोषणा BNXT_LINK_NO_LINK	PORT_PHY_QCFG_RESP_LINK_NO_LINK
#घोषणा BNXT_LINK_SIGNAL	PORT_PHY_QCFG_RESP_LINK_SIGNAL
#घोषणा BNXT_LINK_LINK		PORT_PHY_QCFG_RESP_LINK_LINK
	u8			wire_speed;
	u8			phy_state;
#घोषणा BNXT_PHY_STATE_ENABLED		0
#घोषणा BNXT_PHY_STATE_DISABLED		1

	u8			link_up;
	u8			duplex;
#घोषणा BNXT_LINK_DUPLEX_HALF	PORT_PHY_QCFG_RESP_DUPLEX_STATE_HALF
#घोषणा BNXT_LINK_DUPLEX_FULL	PORT_PHY_QCFG_RESP_DUPLEX_STATE_FULL
	u8			छोड़ो;
#घोषणा BNXT_LINK_PAUSE_TX	PORT_PHY_QCFG_RESP_PAUSE_TX
#घोषणा BNXT_LINK_PAUSE_RX	PORT_PHY_QCFG_RESP_PAUSE_RX
#घोषणा BNXT_LINK_PAUSE_BOTH	(PORT_PHY_QCFG_RESP_PAUSE_RX | \
				 PORT_PHY_QCFG_RESP_PAUSE_TX)
	u8			lp_छोड़ो;
	u8			स्वतः_छोड़ो_setting;
	u8			क्रमce_छोड़ो_setting;
	u8			duplex_setting;
	u8			स्वतः_mode;
#घोषणा BNXT_AUTO_MODE(mode)	((mode) > BNXT_LINK_AUTO_NONE && \
				 (mode) <= BNXT_LINK_AUTO_MSK)
#घोषणा BNXT_LINK_AUTO_NONE     PORT_PHY_QCFG_RESP_AUTO_MODE_NONE
#घोषणा BNXT_LINK_AUTO_ALLSPDS	PORT_PHY_QCFG_RESP_AUTO_MODE_ALL_SPEEDS
#घोषणा BNXT_LINK_AUTO_ONESPD	PORT_PHY_QCFG_RESP_AUTO_MODE_ONE_SPEED
#घोषणा BNXT_LINK_AUTO_ONEORBELOW PORT_PHY_QCFG_RESP_AUTO_MODE_ONE_OR_BELOW
#घोषणा BNXT_LINK_AUTO_MSK	PORT_PHY_QCFG_RESP_AUTO_MODE_SPEED_MASK
#घोषणा PHY_VER_LEN		3
	u8			phy_ver[PHY_VER_LEN];
	u16			link_speed;
#घोषणा BNXT_LINK_SPEED_100MB	PORT_PHY_QCFG_RESP_LINK_SPEED_100MB
#घोषणा BNXT_LINK_SPEED_1GB	PORT_PHY_QCFG_RESP_LINK_SPEED_1GB
#घोषणा BNXT_LINK_SPEED_2GB	PORT_PHY_QCFG_RESP_LINK_SPEED_2GB
#घोषणा BNXT_LINK_SPEED_2_5GB	PORT_PHY_QCFG_RESP_LINK_SPEED_2_5GB
#घोषणा BNXT_LINK_SPEED_10GB	PORT_PHY_QCFG_RESP_LINK_SPEED_10GB
#घोषणा BNXT_LINK_SPEED_20GB	PORT_PHY_QCFG_RESP_LINK_SPEED_20GB
#घोषणा BNXT_LINK_SPEED_25GB	PORT_PHY_QCFG_RESP_LINK_SPEED_25GB
#घोषणा BNXT_LINK_SPEED_40GB	PORT_PHY_QCFG_RESP_LINK_SPEED_40GB
#घोषणा BNXT_LINK_SPEED_50GB	PORT_PHY_QCFG_RESP_LINK_SPEED_50GB
#घोषणा BNXT_LINK_SPEED_100GB	PORT_PHY_QCFG_RESP_LINK_SPEED_100GB
	u16			support_speeds;
	u16			support_pam4_speeds;
	u16			स्वतः_link_speeds;	/* fw adv setting */
#घोषणा BNXT_LINK_SPEED_MSK_100MB PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_100MB
#घोषणा BNXT_LINK_SPEED_MSK_1GB PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_1GB
#घोषणा BNXT_LINK_SPEED_MSK_2GB PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_2GB
#घोषणा BNXT_LINK_SPEED_MSK_10GB PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_10GB
#घोषणा BNXT_LINK_SPEED_MSK_2_5GB PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_2_5GB
#घोषणा BNXT_LINK_SPEED_MSK_20GB PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_20GB
#घोषणा BNXT_LINK_SPEED_MSK_25GB PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_25GB
#घोषणा BNXT_LINK_SPEED_MSK_40GB PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_40GB
#घोषणा BNXT_LINK_SPEED_MSK_50GB PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_50GB
#घोषणा BNXT_LINK_SPEED_MSK_100GB PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_100GB
	u16			स्वतः_pam4_link_speeds;
#घोषणा BNXT_LINK_PAM4_SPEED_MSK_50GB PORT_PHY_QCFG_RESP_SUPPORT_PAM4_SPEEDS_50G
#घोषणा BNXT_LINK_PAM4_SPEED_MSK_100GB PORT_PHY_QCFG_RESP_SUPPORT_PAM4_SPEEDS_100G
#घोषणा BNXT_LINK_PAM4_SPEED_MSK_200GB PORT_PHY_QCFG_RESP_SUPPORT_PAM4_SPEEDS_200G
	u16			support_स्वतः_speeds;
	u16			support_pam4_स्वतः_speeds;
	u16			lp_स्वतः_link_speeds;
	u16			lp_स्वतः_pam4_link_speeds;
	u16			क्रमce_link_speed;
	u16			क्रमce_pam4_link_speed;
	u32			preemphasis;
	u8			module_status;
	u8			active_fec_sig_mode;
	u16			fec_cfg;
#घोषणा BNXT_FEC_NONE		PORT_PHY_QCFG_RESP_FEC_CFG_FEC_NONE_SUPPORTED
#घोषणा BNXT_FEC_AUTONEG_CAP	PORT_PHY_QCFG_RESP_FEC_CFG_FEC_AUTONEG_SUPPORTED
#घोषणा BNXT_FEC_AUTONEG	PORT_PHY_QCFG_RESP_FEC_CFG_FEC_AUTONEG_ENABLED
#घोषणा BNXT_FEC_ENC_BASE_R_CAP	\
	PORT_PHY_QCFG_RESP_FEC_CFG_FEC_CLAUSE74_SUPPORTED
#घोषणा BNXT_FEC_ENC_BASE_R	PORT_PHY_QCFG_RESP_FEC_CFG_FEC_CLAUSE74_ENABLED
#घोषणा BNXT_FEC_ENC_RS_CAP	\
	PORT_PHY_QCFG_RESP_FEC_CFG_FEC_CLAUSE91_SUPPORTED
#घोषणा BNXT_FEC_ENC_LLRS_CAP	\
	(PORT_PHY_QCFG_RESP_FEC_CFG_FEC_RS272_1XN_SUPPORTED |	\
	 PORT_PHY_QCFG_RESP_FEC_CFG_FEC_RS272_IEEE_SUPPORTED)
#घोषणा BNXT_FEC_ENC_RS		\
	(PORT_PHY_QCFG_RESP_FEC_CFG_FEC_CLAUSE91_ENABLED |	\
	 PORT_PHY_QCFG_RESP_FEC_CFG_FEC_RS544_1XN_ENABLED |	\
	 PORT_PHY_QCFG_RESP_FEC_CFG_FEC_RS544_IEEE_ENABLED)
#घोषणा BNXT_FEC_ENC_LLRS	\
	(PORT_PHY_QCFG_RESP_FEC_CFG_FEC_RS272_1XN_ENABLED |	\
	 PORT_PHY_QCFG_RESP_FEC_CFG_FEC_RS272_IEEE_ENABLED)

	/* copy of requested setting from ethtool cmd */
	u8			स्वतःneg;
#घोषणा BNXT_AUTONEG_SPEED		1
#घोषणा BNXT_AUTONEG_FLOW_CTRL		2
	u8			req_संकेत_mode;
#घोषणा BNXT_SIG_MODE_NRZ	PORT_PHY_QCFG_RESP_SIGNAL_MODE_NRZ
#घोषणा BNXT_SIG_MODE_PAM4	PORT_PHY_QCFG_RESP_SIGNAL_MODE_PAM4
	u8			req_duplex;
	u8			req_flow_ctrl;
	u16			req_link_speed;
	u16			advertising;	/* user adv setting */
	u16			advertising_pam4;
	bool			क्रमce_link_chng;

	bool			phy_retry;
	अचिन्हित दीर्घ		phy_retry_expires;

	/* a copy of phy_qcfg output used to report link
	 * info to VF
	 */
	काष्ठा hwrm_port_phy_qcfg_output phy_qcfg_resp;
पूर्ण;

#घोषणा BNXT_FEC_RS544_ON					\
	 (PORT_PHY_CFG_REQ_FLAGS_FEC_RS544_1XN_ENABLE |		\
	  PORT_PHY_CFG_REQ_FLAGS_FEC_RS544_IEEE_ENABLE)

#घोषणा BNXT_FEC_RS544_OFF					\
	 (PORT_PHY_CFG_REQ_FLAGS_FEC_RS544_1XN_DISABLE |	\
	  PORT_PHY_CFG_REQ_FLAGS_FEC_RS544_IEEE_DISABLE)

#घोषणा BNXT_FEC_RS272_ON					\
	 (PORT_PHY_CFG_REQ_FLAGS_FEC_RS272_1XN_ENABLE |		\
	  PORT_PHY_CFG_REQ_FLAGS_FEC_RS272_IEEE_ENABLE)

#घोषणा BNXT_FEC_RS272_OFF					\
	 (PORT_PHY_CFG_REQ_FLAGS_FEC_RS272_1XN_DISABLE |	\
	  PORT_PHY_CFG_REQ_FLAGS_FEC_RS272_IEEE_DISABLE)

#घोषणा BNXT_PAM4_SUPPORTED(link_info)				\
	((link_info)->support_pam4_speeds)

#घोषणा BNXT_FEC_RS_ON(link_info)				\
	(PORT_PHY_CFG_REQ_FLAGS_FEC_CLAUSE91_ENABLE |		\
	 PORT_PHY_CFG_REQ_FLAGS_FEC_CLAUSE74_DISABLE |		\
	 (BNXT_PAM4_SUPPORTED(link_info) ?			\
	  (BNXT_FEC_RS544_ON | BNXT_FEC_RS272_OFF) : 0))

#घोषणा BNXT_FEC_LLRS_ON					\
	(PORT_PHY_CFG_REQ_FLAGS_FEC_CLAUSE91_ENABLE |		\
	 PORT_PHY_CFG_REQ_FLAGS_FEC_CLAUSE74_DISABLE |		\
	 BNXT_FEC_RS272_ON | BNXT_FEC_RS544_OFF)

#घोषणा BNXT_FEC_RS_OFF(link_info)				\
	(PORT_PHY_CFG_REQ_FLAGS_FEC_CLAUSE91_DISABLE |		\
	 (BNXT_PAM4_SUPPORTED(link_info) ?			\
	  (BNXT_FEC_RS544_OFF | BNXT_FEC_RS272_OFF) : 0))

#घोषणा BNXT_FEC_BASE_R_ON(link_info)				\
	(PORT_PHY_CFG_REQ_FLAGS_FEC_CLAUSE74_ENABLE |		\
	 BNXT_FEC_RS_OFF(link_info))

#घोषणा BNXT_FEC_ALL_OFF(link_info)				\
	(PORT_PHY_CFG_REQ_FLAGS_FEC_CLAUSE74_DISABLE |		\
	 BNXT_FEC_RS_OFF(link_info))

#घोषणा BNXT_MAX_QUEUE	8

काष्ठा bnxt_queue_info अणु
	u8	queue_id;
	u8	queue_profile;
पूर्ण;

#घोषणा BNXT_MAX_LED			4

काष्ठा bnxt_led_info अणु
	u8	led_id;
	u8	led_type;
	u8	led_group_id;
	u8	unused;
	__le16	led_state_caps;
#घोषणा BNXT_LED_ALT_BLINK_CAP(x)	((x) &	\
	cpu_to_le16(PORT_LED_QCAPS_RESP_LED0_STATE_CAPS_BLINK_ALT_SUPPORTED))

	__le16	led_color_caps;
पूर्ण;

#घोषणा BNXT_MAX_TEST	8

काष्ठा bnxt_test_info अणु
	u8 offline_mask;
	u16 समयout;
	अक्षर string[BNXT_MAX_TEST][ETH_GSTRING_LEN];
पूर्ण;

#घोषणा CHIMP_REG_VIEW_ADDR				\
	((bp->flags & BNXT_FLAG_CHIP_P5) ? 0x80000000 : 0xb1000000)

#घोषणा BNXT_GRCPF_REG_CHIMP_COMM		0x0
#घोषणा BNXT_GRCPF_REG_CHIMP_COMM_TRIGGER	0x100
#घोषणा BNXT_GRCPF_REG_WINDOW_BASE_OUT		0x400
#घोषणा BNXT_CAG_REG_LEGACY_INT_STATUS		0x4014
#घोषणा BNXT_CAG_REG_BASE			0x300000

#घोषणा BNXT_GRC_REG_STATUS_P5			0x520

#घोषणा BNXT_GRCPF_REG_KONG_COMM		0xA00
#घोषणा BNXT_GRCPF_REG_KONG_COMM_TRIGGER	0xB00

#घोषणा BNXT_GRC_REG_CHIP_NUM			0x48
#घोषणा BNXT_GRC_REG_BASE			0x260000

#घोषणा BNXT_GRC_BASE_MASK			0xfffff000
#घोषणा BNXT_GRC_OFFSET_MASK			0x00000ffc

काष्ठा bnxt_tc_flow_stats अणु
	u64		packets;
	u64		bytes;
पूर्ण;

#अगर_घोषित CONFIG_BNXT_FLOWER_OFFLOAD
काष्ठा bnxt_flower_indr_block_cb_priv अणु
	काष्ठा net_device *tunnel_netdev;
	काष्ठा bnxt *bp;
	काष्ठा list_head list;
पूर्ण;
#पूर्ण_अगर

काष्ठा bnxt_tc_info अणु
	bool				enabled;

	/* hash table to store TC offloaded flows */
	काष्ठा rhashtable		flow_table;
	काष्ठा rhashtable_params	flow_ht_params;

	/* hash table to store L2 keys of TC flows */
	काष्ठा rhashtable		l2_table;
	काष्ठा rhashtable_params	l2_ht_params;
	/* hash table to store L2 keys क्रम TC tunnel decap */
	काष्ठा rhashtable		decap_l2_table;
	काष्ठा rhashtable_params	decap_l2_ht_params;
	/* hash table to store tunnel decap entries */
	काष्ठा rhashtable		decap_table;
	काष्ठा rhashtable_params	decap_ht_params;
	/* hash table to store tunnel encap entries */
	काष्ठा rhashtable		encap_table;
	काष्ठा rhashtable_params	encap_ht_params;

	/* lock to atomically add/del an l2 node when a flow is
	 * added or deleted.
	 */
	काष्ठा mutex			lock;

	/* Fields used क्रम batching stats query */
	काष्ठा rhashtable_iter		iter;
#घोषणा BNXT_FLOW_STATS_BATCH_MAX	10
	काष्ठा bnxt_tc_stats_batch अणु
		व्योम			  *flow_node;
		काष्ठा bnxt_tc_flow_stats hw_stats;
	पूर्ण stats_batch[BNXT_FLOW_STATS_BATCH_MAX];

	/* Stat counter mask (width) */
	u64				bytes_mask;
	u64				packets_mask;
पूर्ण;

काष्ठा bnxt_vf_rep_stats अणु
	u64			packets;
	u64			bytes;
	u64			dropped;
पूर्ण;

काष्ठा bnxt_vf_rep अणु
	काष्ठा bnxt			*bp;
	काष्ठा net_device		*dev;
	काष्ठा metadata_dst		*dst;
	u16				vf_idx;
	u16				tx_cfa_action;
	u16				rx_cfa_code;

	काष्ठा bnxt_vf_rep_stats	rx_stats;
	काष्ठा bnxt_vf_rep_stats	tx_stats;
पूर्ण;

#घोषणा PTU_PTE_VALID             0x1UL
#घोषणा PTU_PTE_LAST              0x2UL
#घोषणा PTU_PTE_NEXT_TO_LAST      0x4UL

#घोषणा MAX_CTX_PAGES	(BNXT_PAGE_SIZE / 8)
#घोषणा MAX_CTX_TOTAL_PAGES	(MAX_CTX_PAGES * MAX_CTX_PAGES)

काष्ठा bnxt_ctx_pg_info अणु
	u32		entries;
	u32		nr_pages;
	व्योम		*ctx_pg_arr[MAX_CTX_PAGES];
	dma_addr_t	ctx_dma_arr[MAX_CTX_PAGES];
	काष्ठा bnxt_ring_mem_info ring_mem;
	काष्ठा bnxt_ctx_pg_info **ctx_pg_tbl;
पूर्ण;

#घोषणा BNXT_MAX_TQM_SP_RINGS		1
#घोषणा BNXT_MAX_TQM_FP_RINGS		8
#घोषणा BNXT_MAX_TQM_RINGS		\
	(BNXT_MAX_TQM_SP_RINGS + BNXT_MAX_TQM_FP_RINGS)

#घोषणा BNXT_BACKING_STORE_CFG_LEGACY_LEN	256

#घोषणा BNXT_SET_CTX_PAGE_ATTR(attr)					\
करो अणु									\
	अगर (BNXT_PAGE_SIZE == 0x2000)					\
		attr = FUNC_BACKING_STORE_CFG_REQ_SRQ_PG_SIZE_PG_8K;	\
	अन्यथा अगर (BNXT_PAGE_SIZE == 0x10000)				\
		attr = FUNC_BACKING_STORE_CFG_REQ_QPC_PG_SIZE_PG_64K;	\
	अन्यथा								\
		attr = FUNC_BACKING_STORE_CFG_REQ_QPC_PG_SIZE_PG_4K;	\
पूर्ण जबतक (0)

काष्ठा bnxt_ctx_mem_info अणु
	u32	qp_max_entries;
	u16	qp_min_qp1_entries;
	u16	qp_max_l2_entries;
	u16	qp_entry_size;
	u16	srq_max_l2_entries;
	u32	srq_max_entries;
	u16	srq_entry_size;
	u16	cq_max_l2_entries;
	u32	cq_max_entries;
	u16	cq_entry_size;
	u16	vnic_max_vnic_entries;
	u16	vnic_max_ring_table_entries;
	u16	vnic_entry_size;
	u32	stat_max_entries;
	u16	stat_entry_size;
	u16	tqm_entry_size;
	u32	tqm_min_entries_per_ring;
	u32	tqm_max_entries_per_ring;
	u32	mrav_max_entries;
	u16	mrav_entry_size;
	u16	tim_entry_size;
	u32	tim_max_entries;
	u16	mrav_num_entries_units;
	u8	tqm_entries_multiple;
	u8	tqm_fp_rings_count;

	u32	flags;
	#घोषणा BNXT_CTX_FLAG_INITED	0x01

	काष्ठा bnxt_ctx_pg_info qp_mem;
	काष्ठा bnxt_ctx_pg_info srq_mem;
	काष्ठा bnxt_ctx_pg_info cq_mem;
	काष्ठा bnxt_ctx_pg_info vnic_mem;
	काष्ठा bnxt_ctx_pg_info stat_mem;
	काष्ठा bnxt_ctx_pg_info mrav_mem;
	काष्ठा bnxt_ctx_pg_info tim_mem;
	काष्ठा bnxt_ctx_pg_info *tqm_mem[BNXT_MAX_TQM_RINGS];

#घोषणा BNXT_CTX_MEM_INIT_QP	0
#घोषणा BNXT_CTX_MEM_INIT_SRQ	1
#घोषणा BNXT_CTX_MEM_INIT_CQ	2
#घोषणा BNXT_CTX_MEM_INIT_VNIC	3
#घोषणा BNXT_CTX_MEM_INIT_STAT	4
#घोषणा BNXT_CTX_MEM_INIT_MRAV	5
#घोषणा BNXT_CTX_MEM_INIT_MAX	6
	काष्ठा bnxt_mem_init	mem_init[BNXT_CTX_MEM_INIT_MAX];
पूर्ण;

काष्ठा bnxt_fw_health अणु
	u32 flags;
	u32 polling_dsecs;
	u32 master_func_रुको_dsecs;
	u32 normal_func_रुको_dsecs;
	u32 post_reset_रुको_dsecs;
	u32 post_reset_max_रुको_dsecs;
	u32 regs[4];
	u32 mapped_regs[4];
#घोषणा BNXT_FW_HEALTH_REG		0
#घोषणा BNXT_FW_HEARTBEAT_REG		1
#घोषणा BNXT_FW_RESET_CNT_REG		2
#घोषणा BNXT_FW_RESET_INPROG_REG	3
	u32 fw_reset_inprog_reg_mask;
	u32 last_fw_heartbeat;
	u32 last_fw_reset_cnt;
	u8 enabled:1;
	u8 master:1;
	u8 fatal:1;
	u8 status_reliable:1;
	u8 पंचांगr_multiplier;
	u8 पंचांगr_counter;
	u8 fw_reset_seq_cnt;
	u32 fw_reset_seq_regs[16];
	u32 fw_reset_seq_vals[16];
	u32 fw_reset_seq_delay_msec[16];
	u32 echo_req_data1;
	u32 echo_req_data2;
	काष्ठा devlink_health_reporter	*fw_reporter;
	काष्ठा devlink_health_reporter *fw_reset_reporter;
	काष्ठा devlink_health_reporter *fw_fatal_reporter;
पूर्ण;

काष्ठा bnxt_fw_reporter_ctx अणु
	अचिन्हित दीर्घ sp_event;
पूर्ण;

#घोषणा BNXT_FW_HEALTH_REG_TYPE_MASK	3
#घोषणा BNXT_FW_HEALTH_REG_TYPE_CFG	0
#घोषणा BNXT_FW_HEALTH_REG_TYPE_GRC	1
#घोषणा BNXT_FW_HEALTH_REG_TYPE_BAR0	2
#घोषणा BNXT_FW_HEALTH_REG_TYPE_BAR1	3

#घोषणा BNXT_FW_HEALTH_REG_TYPE(reg)	((reg) & BNXT_FW_HEALTH_REG_TYPE_MASK)
#घोषणा BNXT_FW_HEALTH_REG_OFF(reg)	((reg) & ~BNXT_FW_HEALTH_REG_TYPE_MASK)

#घोषणा BNXT_FW_HEALTH_WIN_BASE		0x3000
#घोषणा BNXT_FW_HEALTH_WIN_MAP_OFF	8

#घोषणा BNXT_FW_HEALTH_WIN_OFF(reg)	(BNXT_FW_HEALTH_WIN_BASE +	\
					 ((reg) & BNXT_GRC_OFFSET_MASK))

#घोषणा BNXT_FW_STATUS_HEALTH_MSK	0xffff
#घोषणा BNXT_FW_STATUS_HEALTHY		0x8000
#घोषणा BNXT_FW_STATUS_SHUTDOWN		0x100000
#घोषणा BNXT_FW_STATUS_RECOVERING	0x400000

#घोषणा BNXT_FW_IS_HEALTHY(sts)		(((sts) & BNXT_FW_STATUS_HEALTH_MSK) ==\
					 BNXT_FW_STATUS_HEALTHY)

#घोषणा BNXT_FW_IS_BOOTING(sts)		(((sts) & BNXT_FW_STATUS_HEALTH_MSK) < \
					 BNXT_FW_STATUS_HEALTHY)

#घोषणा BNXT_FW_IS_ERR(sts)		(((sts) & BNXT_FW_STATUS_HEALTH_MSK) > \
					 BNXT_FW_STATUS_HEALTHY)

#घोषणा BNXT_FW_IS_RECOVERING(sts)	(BNXT_FW_IS_ERR(sts) &&		       \
					 ((sts) & BNXT_FW_STATUS_RECOVERING))

#घोषणा BNXT_FW_RETRY			5
#घोषणा BNXT_FW_IF_RETRY		10

काष्ठा bnxt अणु
	व्योम __iomem		*bar0;
	व्योम __iomem		*bar1;
	व्योम __iomem		*bar2;

	u32			reg_base;
	u16			chip_num;
#घोषणा CHIP_NUM_57301		0x16c8
#घोषणा CHIP_NUM_57302		0x16c9
#घोषणा CHIP_NUM_57304		0x16ca
#घोषणा CHIP_NUM_58700		0x16cd
#घोषणा CHIP_NUM_57402		0x16d0
#घोषणा CHIP_NUM_57404		0x16d1
#घोषणा CHIP_NUM_57406		0x16d2
#घोषणा CHIP_NUM_57407		0x16d5

#घोषणा CHIP_NUM_57311		0x16ce
#घोषणा CHIP_NUM_57312		0x16cf
#घोषणा CHIP_NUM_57314		0x16df
#घोषणा CHIP_NUM_57317		0x16e0
#घोषणा CHIP_NUM_57412		0x16d6
#घोषणा CHIP_NUM_57414		0x16d7
#घोषणा CHIP_NUM_57416		0x16d8
#घोषणा CHIP_NUM_57417		0x16d9
#घोषणा CHIP_NUM_57412L		0x16da
#घोषणा CHIP_NUM_57414L		0x16db

#घोषणा CHIP_NUM_5745X		0xd730
#घोषणा CHIP_NUM_57452		0xc452
#घोषणा CHIP_NUM_57454		0xc454

#घोषणा CHIP_NUM_57508		0x1750
#घोषणा CHIP_NUM_57504		0x1751
#घोषणा CHIP_NUM_57502		0x1752

#घोषणा CHIP_NUM_58802		0xd802
#घोषणा CHIP_NUM_58804		0xd804
#घोषणा CHIP_NUM_58808		0xd808

	u8			chip_rev;

#घोषणा CHIP_NUM_58818		0xd818

#घोषणा BNXT_CHIP_NUM_5730X(chip_num)		\
	((chip_num) >= CHIP_NUM_57301 &&	\
	 (chip_num) <= CHIP_NUM_57304)

#घोषणा BNXT_CHIP_NUM_5740X(chip_num)		\
	(((chip_num) >= CHIP_NUM_57402 &&	\
	  (chip_num) <= CHIP_NUM_57406) ||	\
	 (chip_num) == CHIP_NUM_57407)

#घोषणा BNXT_CHIP_NUM_5731X(chip_num)		\
	((chip_num) == CHIP_NUM_57311 ||	\
	 (chip_num) == CHIP_NUM_57312 ||	\
	 (chip_num) == CHIP_NUM_57314 ||	\
	 (chip_num) == CHIP_NUM_57317)

#घोषणा BNXT_CHIP_NUM_5741X(chip_num)		\
	((chip_num) >= CHIP_NUM_57412 &&	\
	 (chip_num) <= CHIP_NUM_57414L)

#घोषणा BNXT_CHIP_NUM_58700(chip_num)		\
	 ((chip_num) == CHIP_NUM_58700)

#घोषणा BNXT_CHIP_NUM_5745X(chip_num)		\
	((chip_num) == CHIP_NUM_5745X ||	\
	 (chip_num) == CHIP_NUM_57452 ||	\
	 (chip_num) == CHIP_NUM_57454)


#घोषणा BNXT_CHIP_NUM_57X0X(chip_num)		\
	(BNXT_CHIP_NUM_5730X(chip_num) || BNXT_CHIP_NUM_5740X(chip_num))

#घोषणा BNXT_CHIP_NUM_57X1X(chip_num)		\
	(BNXT_CHIP_NUM_5731X(chip_num) || BNXT_CHIP_NUM_5741X(chip_num))

#घोषणा BNXT_CHIP_NUM_588XX(chip_num)		\
	((chip_num) == CHIP_NUM_58802 ||	\
	 (chip_num) == CHIP_NUM_58804 ||        \
	 (chip_num) == CHIP_NUM_58808)

#घोषणा BNXT_VPD_FLD_LEN	32
	अक्षर			board_partno[BNXT_VPD_FLD_LEN];
	अक्षर			board_serialno[BNXT_VPD_FLD_LEN];

	काष्ठा net_device	*dev;
	काष्ठा pci_dev		*pdev;

	atomic_t		पूर्णांकr_sem;

	u32			flags;
	#घोषणा BNXT_FLAG_CHIP_P5	0x1
	#घोषणा BNXT_FLAG_VF		0x2
	#घोषणा BNXT_FLAG_LRO		0x4
#अगर_घोषित CONFIG_INET
	#घोषणा BNXT_FLAG_GRO		0x8
#अन्यथा
	/* Cannot support hardware GRO अगर CONFIG_INET is not set */
	#घोषणा BNXT_FLAG_GRO		0x0
#पूर्ण_अगर
	#घोषणा BNXT_FLAG_TPA		(BNXT_FLAG_LRO | BNXT_FLAG_GRO)
	#घोषणा BNXT_FLAG_JUMBO		0x10
	#घोषणा BNXT_FLAG_STRIP_VLAN	0x20
	#घोषणा BNXT_FLAG_AGG_RINGS	(BNXT_FLAG_JUMBO | BNXT_FLAG_GRO | \
					 BNXT_FLAG_LRO)
	#घोषणा BNXT_FLAG_USING_MSIX	0x40
	#घोषणा BNXT_FLAG_MSIX_CAP	0x80
	#घोषणा BNXT_FLAG_RFS		0x100
	#घोषणा BNXT_FLAG_SHARED_RINGS	0x200
	#घोषणा BNXT_FLAG_PORT_STATS	0x400
	#घोषणा BNXT_FLAG_UDP_RSS_CAP	0x800
	#घोषणा BNXT_FLAG_NEW_RSS_CAP	0x2000
	#घोषणा BNXT_FLAG_WOL_CAP	0x4000
	#घोषणा BNXT_FLAG_ROCEV1_CAP	0x8000
	#घोषणा BNXT_FLAG_ROCEV2_CAP	0x10000
	#घोषणा BNXT_FLAG_ROCE_CAP	(BNXT_FLAG_ROCEV1_CAP |	\
					 BNXT_FLAG_ROCEV2_CAP)
	#घोषणा BNXT_FLAG_NO_AGG_RINGS	0x20000
	#घोषणा BNXT_FLAG_RX_PAGE_MODE	0x40000
	#घोषणा BNXT_FLAG_CHIP_SR2	0x80000
	#घोषणा BNXT_FLAG_MULTI_HOST	0x100000
	#घोषणा BNXT_FLAG_DSN_VALID	0x200000
	#घोषणा BNXT_FLAG_DOUBLE_DB	0x400000
	#घोषणा BNXT_FLAG_CHIP_NITRO_A0	0x1000000
	#घोषणा BNXT_FLAG_DIM		0x2000000
	#घोषणा BNXT_FLAG_ROCE_MIRROR_CAP	0x4000000
	#घोषणा BNXT_FLAG_PORT_STATS_EXT	0x10000000

	#घोषणा BNXT_FLAG_ALL_CONFIG_FEATS (BNXT_FLAG_TPA |		\
					    BNXT_FLAG_RFS |		\
					    BNXT_FLAG_STRIP_VLAN)

#घोषणा BNXT_PF(bp)		(!((bp)->flags & BNXT_FLAG_VF))
#घोषणा BNXT_VF(bp)		((bp)->flags & BNXT_FLAG_VF)
#घोषणा BNXT_NPAR(bp)		((bp)->port_partition_type)
#घोषणा BNXT_MH(bp)		((bp)->flags & BNXT_FLAG_MULTI_HOST)
#घोषणा BNXT_SINGLE_PF(bp)	(BNXT_PF(bp) && !BNXT_NPAR(bp) && !BNXT_MH(bp))
#घोषणा BNXT_SH_PORT_CFG_OK(bp)	(BNXT_PF(bp) &&				\
				 ((bp)->phy_flags & BNXT_PHY_FL_SHARED_PORT_CFG))
#घोषणा BNXT_PHY_CFG_ABLE(bp)	((BNXT_SINGLE_PF(bp) ||			\
				  BNXT_SH_PORT_CFG_OK(bp)) &&		\
				 (bp)->link_info.phy_state == BNXT_PHY_STATE_ENABLED)
#घोषणा BNXT_CHIP_TYPE_NITRO_A0(bp) ((bp)->flags & BNXT_FLAG_CHIP_NITRO_A0)
#घोषणा BNXT_RX_PAGE_MODE(bp)	((bp)->flags & BNXT_FLAG_RX_PAGE_MODE)
#घोषणा BNXT_SUPPORTS_TPA(bp)	(!BNXT_CHIP_TYPE_NITRO_A0(bp) &&	\
				 (!((bp)->flags & BNXT_FLAG_CHIP_P5) ||	\
				  (bp)->max_tpa_v2) && !is_kdump_kernel())

#घोषणा BNXT_CHIP_SR2(bp)			\
	((bp)->chip_num == CHIP_NUM_58818)

#घोषणा BNXT_CHIP_P5_THOR(bp)			\
	((bp)->chip_num == CHIP_NUM_57508 ||	\
	 (bp)->chip_num == CHIP_NUM_57504 ||	\
	 (bp)->chip_num == CHIP_NUM_57502)

/* Chip class phase 5 */
#घोषणा BNXT_CHIP_P5(bp)			\
	(BNXT_CHIP_P5_THOR(bp) || BNXT_CHIP_SR2(bp))

/* Chip class phase 4.x */
#घोषणा BNXT_CHIP_P4(bp)			\
	(BNXT_CHIP_NUM_57X1X((bp)->chip_num) ||	\
	 BNXT_CHIP_NUM_5745X((bp)->chip_num) ||	\
	 BNXT_CHIP_NUM_588XX((bp)->chip_num) ||	\
	 (BNXT_CHIP_NUM_58700((bp)->chip_num) &&	\
	  !BNXT_CHIP_TYPE_NITRO_A0(bp)))

#घोषणा BNXT_CHIP_P4_PLUS(bp)			\
	(BNXT_CHIP_P4(bp) || BNXT_CHIP_P5(bp))

	काष्ठा bnxt_en_dev	*edev;

	काष्ठा bnxt_napi	**bnapi;

	काष्ठा bnxt_rx_ring_info	*rx_ring;
	काष्ठा bnxt_tx_ring_info	*tx_ring;
	u16			*tx_ring_map;

	काष्ठा sk_buff *	(*gro_func)(काष्ठा bnxt_tpa_info *, पूर्णांक, पूर्णांक,
					    काष्ठा sk_buff *);

	काष्ठा sk_buff *	(*rx_skb_func)(काष्ठा bnxt *,
					       काष्ठा bnxt_rx_ring_info *,
					       u16, व्योम *, u8 *, dma_addr_t,
					       अचिन्हित पूर्णांक);

	u16			max_tpa_v2;
	u16			max_tpa;
	u32			rx_buf_size;
	u32			rx_buf_use_size;	/* useable size */
	u16			rx_offset;
	u16			rx_dma_offset;
	क्रमागत dma_data_direction	rx_dir;
	u32			rx_ring_size;
	u32			rx_agg_ring_size;
	u32			rx_copy_thresh;
	u32			rx_ring_mask;
	u32			rx_agg_ring_mask;
	पूर्णांक			rx_nr_pages;
	पूर्णांक			rx_agg_nr_pages;
	पूर्णांक			rx_nr_rings;
	पूर्णांक			rsscos_nr_ctxs;

	u32			tx_ring_size;
	u32			tx_ring_mask;
	पूर्णांक			tx_nr_pages;
	पूर्णांक			tx_nr_rings;
	पूर्णांक			tx_nr_rings_per_tc;
	पूर्णांक			tx_nr_rings_xdp;

	पूर्णांक			tx_wake_thresh;
	पूर्णांक			tx_push_thresh;
	पूर्णांक			tx_push_size;

	u32			cp_ring_size;
	u32			cp_ring_mask;
	u32			cp_bit;
	पूर्णांक			cp_nr_pages;
	पूर्णांक			cp_nr_rings;

	/* grp_info indexed by completion ring index */
	काष्ठा bnxt_ring_grp_info	*grp_info;
	काष्ठा bnxt_vnic_info	*vnic_info;
	पूर्णांक			nr_vnics;
	u16			*rss_indir_tbl;
	u16			rss_indir_tbl_entries;
	u32			rss_hash_cfg;

	u16			max_mtu;
	u8			max_tc;
	u8			max_lltc;	/* lossless TCs */
	काष्ठा bnxt_queue_info	q_info[BNXT_MAX_QUEUE];
	u8			tc_to_qidx[BNXT_MAX_QUEUE];
	u8			q_ids[BNXT_MAX_QUEUE];
	u8			max_q;

	अचिन्हित पूर्णांक		current_पूर्णांकerval;
#घोषणा BNXT_TIMER_INTERVAL	HZ

	काष्ठा समयr_list	समयr;

	अचिन्हित दीर्घ		state;
#घोषणा BNXT_STATE_OPEN		0
#घोषणा BNXT_STATE_IN_SP_TASK	1
#घोषणा BNXT_STATE_READ_STATS	2
#घोषणा BNXT_STATE_FW_RESET_DET 3
#घोषणा BNXT_STATE_IN_FW_RESET	4
#घोषणा BNXT_STATE_ABORT_ERR	5
#घोषणा BNXT_STATE_FW_FATAL_COND	6
#घोषणा BNXT_STATE_DRV_REGISTERED	7
#घोषणा BNXT_STATE_PCI_CHANNEL_IO_FROZEN	8
#घोषणा BNXT_STATE_NAPI_DISABLED	9

#घोषणा BNXT_NO_FW_ACCESS(bp)					\
	(test_bit(BNXT_STATE_FW_FATAL_COND, &(bp)->state) ||	\
	 pci_channel_offline((bp)->pdev))

	काष्ठा bnxt_irq	*irq_tbl;
	पूर्णांक			total_irqs;
	u8			mac_addr[ETH_ALEN];

#अगर_घोषित CONFIG_BNXT_DCB
	काष्ठा ieee_pfc		*ieee_pfc;
	काष्ठा ieee_ets		*ieee_ets;
	u8			dcbx_cap;
	u8			शेष_pri;
	u8			max_dscp_value;
#पूर्ण_अगर /* CONFIG_BNXT_DCB */

	u32			msg_enable;

	u32			fw_cap;
	#घोषणा BNXT_FW_CAP_SHORT_CMD			0x00000001
	#घोषणा BNXT_FW_CAP_LLDP_AGENT			0x00000002
	#घोषणा BNXT_FW_CAP_DCBX_AGENT			0x00000004
	#घोषणा BNXT_FW_CAP_NEW_RM			0x00000008
	#घोषणा BNXT_FW_CAP_IF_CHANGE			0x00000010
	#घोषणा BNXT_FW_CAP_KONG_MB_CHNL		0x00000080
	#घोषणा BNXT_FW_CAP_OVS_64BIT_HANDLE		0x00000400
	#घोषणा BNXT_FW_CAP_TRUSTED_VF			0x00000800
	#घोषणा BNXT_FW_CAP_ERROR_RECOVERY		0x00002000
	#घोषणा BNXT_FW_CAP_PKG_VER			0x00004000
	#घोषणा BNXT_FW_CAP_CFA_ADV_FLOW		0x00008000
	#घोषणा BNXT_FW_CAP_CFA_RFS_RING_TBL_IDX_V2	0x00010000
	#घोषणा BNXT_FW_CAP_PCIE_STATS_SUPPORTED	0x00020000
	#घोषणा BNXT_FW_CAP_EXT_STATS_SUPPORTED		0x00040000
	#घोषणा BNXT_FW_CAP_ERR_RECOVER_RELOAD		0x00100000
	#घोषणा BNXT_FW_CAP_HOT_RESET			0x00200000
	#घोषणा BNXT_FW_CAP_VLAN_RX_STRIP		0x01000000
	#घोषणा BNXT_FW_CAP_VLAN_TX_INSERT		0x02000000
	#घोषणा BNXT_FW_CAP_EXT_HW_STATS_SUPPORTED	0x04000000
	#घोषणा BNXT_FW_CAP_RING_MONITOR		0x40000000

#घोषणा BNXT_NEW_RM(bp)		((bp)->fw_cap & BNXT_FW_CAP_NEW_RM)
	u32			hwrm_spec_code;
	u16			hwrm_cmd_seq;
	u16                     hwrm_cmd_kong_seq;
	u16			hwrm_पूर्णांकr_seq_id;
	व्योम			*hwrm_लघु_cmd_req_addr;
	dma_addr_t		hwrm_लघु_cmd_req_dma_addr;
	व्योम			*hwrm_cmd_resp_addr;
	dma_addr_t		hwrm_cmd_resp_dma_addr;
	व्योम			*hwrm_cmd_kong_resp_addr;
	dma_addr_t		hwrm_cmd_kong_resp_dma_addr;

	काष्ठा rtnl_link_stats64	net_stats_prev;
	काष्ठा bnxt_stats_mem	port_stats;
	काष्ठा bnxt_stats_mem	rx_port_stats_ext;
	काष्ठा bnxt_stats_mem	tx_port_stats_ext;
	u16			fw_rx_stats_ext_size;
	u16			fw_tx_stats_ext_size;
	u16			hw_ring_stats_size;
	u8			pri2cos_idx[8];
	u8			pri2cos_valid;

	u16			hwrm_max_req_len;
	u16			hwrm_max_ext_req_len;
	पूर्णांक			hwrm_cmd_समयout;
	काष्ठा mutex		hwrm_cmd_lock;	/* serialize hwrm messages */
	काष्ठा hwrm_ver_get_output	ver_resp;
#घोषणा FW_VER_STR_LEN		32
#घोषणा BC_HWRM_STR_LEN		21
#घोषणा PHY_VER_STR_LEN         (FW_VER_STR_LEN - BC_HWRM_STR_LEN)
	अक्षर			fw_ver_str[FW_VER_STR_LEN];
	अक्षर			hwrm_ver_supp[FW_VER_STR_LEN];
	अक्षर			nvm_cfg_ver[FW_VER_STR_LEN];
	u64			fw_ver_code;
#घोषणा BNXT_FW_VER_CODE(maj, min, bld, rsv)			\
	((u64)(maj) << 48 | (u64)(min) << 32 | (u64)(bld) << 16 | (rsv))
#घोषणा BNXT_FW_MAJ(bp)		((bp)->fw_ver_code >> 48)

	u16			vxlan_fw_dst_port_id;
	u16			nge_fw_dst_port_id;
	__be16			vxlan_port;
	__be16			nge_port;
	u8			port_partition_type;
	u8			port_count;
	u16			br_mode;

	काष्ठा bnxt_coal_cap	coal_cap;
	काष्ठा bnxt_coal	rx_coal;
	काष्ठा bnxt_coal	tx_coal;

	u32			stats_coal_ticks;
#घोषणा BNXT_DEF_STATS_COAL_TICKS	 1000000
#घोषणा BNXT_MIN_STATS_COAL_TICKS	  250000
#घोषणा BNXT_MAX_STATS_COAL_TICKS	 1000000

	काष्ठा work_काष्ठा	sp_task;
	अचिन्हित दीर्घ		sp_event;
#घोषणा BNXT_RX_MASK_SP_EVENT		0
#घोषणा BNXT_RX_NTP_FLTR_SP_EVENT	1
#घोषणा BNXT_LINK_CHNG_SP_EVENT		2
#घोषणा BNXT_HWRM_EXEC_FWD_REQ_SP_EVENT	3
#घोषणा BNXT_RESET_TASK_SP_EVENT	6
#घोषणा BNXT_RST_RING_SP_EVENT		7
#घोषणा BNXT_HWRM_PF_UNLOAD_SP_EVENT	8
#घोषणा BNXT_PERIODIC_STATS_SP_EVENT	9
#घोषणा BNXT_HWRM_PORT_MODULE_SP_EVENT	10
#घोषणा BNXT_RESET_TASK_SILENT_SP_EVENT	11
#घोषणा BNXT_LINK_SPEED_CHNG_SP_EVENT	14
#घोषणा BNXT_FLOW_STATS_SP_EVENT	15
#घोषणा BNXT_UPDATE_PHY_SP_EVENT	16
#घोषणा BNXT_RING_COAL_NOW_SP_EVENT	17
#घोषणा BNXT_FW_RESET_NOTIFY_SP_EVENT	18
#घोषणा BNXT_FW_EXCEPTION_SP_EVENT	19
#घोषणा BNXT_LINK_CFG_CHANGE_SP_EVENT	21
#घोषणा BNXT_FW_ECHO_REQUEST_SP_EVENT	23

	काष्ठा delayed_work	fw_reset_task;
	पूर्णांक			fw_reset_state;
#घोषणा BNXT_FW_RESET_STATE_POLL_VF	1
#घोषणा BNXT_FW_RESET_STATE_RESET_FW	2
#घोषणा BNXT_FW_RESET_STATE_ENABLE_DEV	3
#घोषणा BNXT_FW_RESET_STATE_POLL_FW	4
#घोषणा BNXT_FW_RESET_STATE_OPENING	5
#घोषणा BNXT_FW_RESET_STATE_POLL_FW_DOWN	6

	u16			fw_reset_min_dsecs;
#घोषणा BNXT_DFLT_FW_RST_MIN_DSECS	20
	u16			fw_reset_max_dsecs;
#घोषणा BNXT_DFLT_FW_RST_MAX_DSECS	60
	अचिन्हित दीर्घ		fw_reset_बारtamp;

	काष्ठा bnxt_fw_health	*fw_health;

	काष्ठा bnxt_hw_resc	hw_resc;
	काष्ठा bnxt_pf_info	pf;
	काष्ठा bnxt_ctx_mem_info	*ctx;
#अगर_घोषित CONFIG_BNXT_SRIOV
	पूर्णांक			nr_vfs;
	काष्ठा bnxt_vf_info	vf;
	रुको_queue_head_t	sriov_cfg_रुको;
	bool			sriov_cfg;
#घोषणा BNXT_SRIOV_CFG_WAIT_TMO	msecs_to_jअगरfies(10000)

	/* lock to protect VF-rep creation/cleanup via
	 * multiple paths such as ->sriov_configure() and
	 * devlink ->eचयन_mode_set()
	 */
	काष्ठा mutex		sriov_lock;
#पूर्ण_अगर

#अगर BITS_PER_LONG == 32
	/* ensure atomic 64-bit करोorbell ग_लिखोs on 32-bit प्रणालीs. */
	spinlock_t		db_lock;
#पूर्ण_अगर
	पूर्णांक			db_size;

#घोषणा BNXT_NTP_FLTR_MAX_FLTR	4096
#घोषणा BNXT_NTP_FLTR_HASH_SIZE	512
#घोषणा BNXT_NTP_FLTR_HASH_MASK	(BNXT_NTP_FLTR_HASH_SIZE - 1)
	काष्ठा hlist_head	ntp_fltr_hash_tbl[BNXT_NTP_FLTR_HASH_SIZE];
	spinlock_t		ntp_fltr_lock;	/* क्रम hash table add, del */

	अचिन्हित दीर्घ		*ntp_fltr_bmap;
	पूर्णांक			ntp_fltr_count;

	/* To protect link related settings during link changes and
	 * ethtool settings changes.
	 */
	काष्ठा mutex		link_lock;
	काष्ठा bnxt_link_info	link_info;
	काष्ठा ethtool_eee	eee;
	u32			lpi_पंचांगr_lo;
	u32			lpi_पंचांगr_hi;

	/* copied from flags in hwrm_port_phy_qcaps_output */
	u8			phy_flags;
#घोषणा BNXT_PHY_FL_EEE_CAP		PORT_PHY_QCAPS_RESP_FLAGS_EEE_SUPPORTED
#घोषणा BNXT_PHY_FL_EXT_LPBK		PORT_PHY_QCAPS_RESP_FLAGS_EXTERNAL_LPBK_SUPPORTED
#घोषणा BNXT_PHY_FL_AN_PHY_LPBK		PORT_PHY_QCAPS_RESP_FLAGS_AUTONEG_LPBK_SUPPORTED
#घोषणा BNXT_PHY_FL_SHARED_PORT_CFG	PORT_PHY_QCAPS_RESP_FLAGS_SHARED_PHY_CFG_SUPPORTED
#घोषणा BNXT_PHY_FL_PORT_STATS_NO_RESET	PORT_PHY_QCAPS_RESP_FLAGS_CUMULATIVE_COUNTERS_ON_RESET
#घोषणा BNXT_PHY_FL_NO_PHY_LPBK		PORT_PHY_QCAPS_RESP_FLAGS_LOCAL_LPBK_NOT_SUPPORTED
#घोषणा BNXT_PHY_FL_FW_MANAGED_LKDN	PORT_PHY_QCAPS_RESP_FLAGS_FW_MANAGED_LINK_DOWN
#घोषणा BNXT_PHY_FL_NO_FCS		PORT_PHY_QCAPS_RESP_FLAGS_NO_FCS

	u8			num_tests;
	काष्ठा bnxt_test_info	*test_info;

	u8			wol_filter_id;
	u8			wol;

	u8			num_leds;
	काष्ठा bnxt_led_info	leds[BNXT_MAX_LED];
	u16			dump_flag;
#घोषणा BNXT_DUMP_LIVE		0
#घोषणा BNXT_DUMP_CRASH		1

	काष्ठा bpf_prog		*xdp_prog;

	/* devlink पूर्णांकerface and vf-rep काष्ठाs */
	काष्ठा devlink		*dl;
	काष्ठा devlink_port	dl_port;
	क्रमागत devlink_eचयन_mode eचयन_mode;
	काष्ठा bnxt_vf_rep	**vf_reps; /* array of vf-rep ptrs */
	u16			*cfa_code_map; /* cfa_code -> vf_idx map */
	u8			dsn[8];
	काष्ठा bnxt_tc_info	*tc_info;
	काष्ठा list_head	tc_indr_block_list;
	काष्ठा dentry		*debugfs_pdev;
	काष्ठा device		*hwmon_dev;
पूर्ण;

#घोषणा BNXT_NUM_RX_RING_STATS			8
#घोषणा BNXT_NUM_TX_RING_STATS			8
#घोषणा BNXT_NUM_TPA_RING_STATS			4
#घोषणा BNXT_NUM_TPA_RING_STATS_P5		5
#घोषणा BNXT_NUM_TPA_RING_STATS_P5_SR2		6

#घोषणा BNXT_RING_STATS_SIZE_P5					\
	((BNXT_NUM_RX_RING_STATS + BNXT_NUM_TX_RING_STATS +	\
	  BNXT_NUM_TPA_RING_STATS_P5) * 8)

#घोषणा BNXT_RING_STATS_SIZE_P5_SR2				\
	((BNXT_NUM_RX_RING_STATS + BNXT_NUM_TX_RING_STATS +	\
	  BNXT_NUM_TPA_RING_STATS_P5_SR2) * 8)

#घोषणा BNXT_GET_RING_STATS64(sw, counter)		\
	(*((sw) + दुरत्व(काष्ठा ctx_hw_stats, counter) / 8))

#घोषणा BNXT_GET_RX_PORT_STATS64(sw, counter)		\
	(*((sw) + दुरत्व(काष्ठा rx_port_stats, counter) / 8))

#घोषणा BNXT_GET_TX_PORT_STATS64(sw, counter)		\
	(*((sw) + दुरत्व(काष्ठा tx_port_stats, counter) / 8))

#घोषणा BNXT_PORT_STATS_SIZE				\
	(माप(काष्ठा rx_port_stats) + माप(काष्ठा tx_port_stats) + 1024)

#घोषणा BNXT_TX_PORT_STATS_BYTE_OFFSET			\
	(माप(काष्ठा rx_port_stats) + 512)

#घोषणा BNXT_RX_STATS_OFFSET(counter)			\
	(दुरत्व(काष्ठा rx_port_stats, counter) / 8)

#घोषणा BNXT_TX_STATS_OFFSET(counter)			\
	((दुरत्व(काष्ठा tx_port_stats, counter) +	\
	  BNXT_TX_PORT_STATS_BYTE_OFFSET) / 8)

#घोषणा BNXT_RX_STATS_EXT_OFFSET(counter)		\
	(दुरत्व(काष्ठा rx_port_stats_ext, counter) / 8)

#घोषणा BNXT_TX_STATS_EXT_OFFSET(counter)		\
	(दुरत्व(काष्ठा tx_port_stats_ext, counter) / 8)

#घोषणा BNXT_HW_FEATURE_VLAN_ALL_RX				\
	(NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_HW_VLAN_STAG_RX)
#घोषणा BNXT_HW_FEATURE_VLAN_ALL_TX				\
	(NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_STAG_TX)

#घोषणा I2C_DEV_ADDR_A0				0xa0
#घोषणा I2C_DEV_ADDR_A2				0xa2
#घोषणा SFF_DIAG_SUPPORT_OFFSET			0x5c
#घोषणा SFF_MODULE_ID_SFP			0x3
#घोषणा SFF_MODULE_ID_QSFP			0xc
#घोषणा SFF_MODULE_ID_QSFP_PLUS			0xd
#घोषणा SFF_MODULE_ID_QSFP28			0x11
#घोषणा BNXT_MAX_PHY_I2C_RESP_SIZE		64

अटल अंतरभूत u32 bnxt_tx_avail(काष्ठा bnxt *bp, काष्ठा bnxt_tx_ring_info *txr)
अणु
	/* Tell compiler to fetch tx indices from memory. */
	barrier();

	वापस bp->tx_ring_size -
		((txr->tx_prod - txr->tx_cons) & bp->tx_ring_mask);
पूर्ण

#अगर BITS_PER_LONG == 32
#घोषणा ग_लिखोq(val64, db)			\
करो अणु						\
	spin_lock(&bp->db_lock);		\
	ग_लिखोl((val64) & 0xffffffff, db);	\
	ग_लिखोl((val64) >> 32, (db) + 4);	\
	spin_unlock(&bp->db_lock);		\
पूर्ण जबतक (0)

#घोषणा ग_लिखोq_relaxed ग_लिखोq
#पूर्ण_अगर

/* For TX and RX ring करोorbells with no ordering guarantee*/
अटल अंतरभूत व्योम bnxt_db_ग_लिखो_relaxed(काष्ठा bnxt *bp,
					 काष्ठा bnxt_db_info *db, u32 idx)
अणु
	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		ग_लिखोq_relaxed(db->db_key64 | idx, db->करोorbell);
	पूर्ण अन्यथा अणु
		u32 db_val = db->db_key32 | idx;

		ग_लिखोl_relaxed(db_val, db->करोorbell);
		अगर (bp->flags & BNXT_FLAG_DOUBLE_DB)
			ग_लिखोl_relaxed(db_val, db->करोorbell);
	पूर्ण
पूर्ण

/* For TX and RX ring करोorbells */
अटल अंतरभूत व्योम bnxt_db_ग_लिखो(काष्ठा bnxt *bp, काष्ठा bnxt_db_info *db,
				 u32 idx)
अणु
	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		ग_लिखोq(db->db_key64 | idx, db->करोorbell);
	पूर्ण अन्यथा अणु
		u32 db_val = db->db_key32 | idx;

		ग_लिखोl(db_val, db->करोorbell);
		अगर (bp->flags & BNXT_FLAG_DOUBLE_DB)
			ग_लिखोl(db_val, db->करोorbell);
	पूर्ण
पूर्ण

अटल अंतरभूत bool bnxt_cfa_hwrm_message(u16 req_type)
अणु
	चयन (req_type) अणु
	हाल HWRM_CFA_ENCAP_RECORD_ALLOC:
	हाल HWRM_CFA_ENCAP_RECORD_FREE:
	हाल HWRM_CFA_DECAP_FILTER_ALLOC:
	हाल HWRM_CFA_DECAP_FILTER_FREE:
	हाल HWRM_CFA_EM_FLOW_ALLOC:
	हाल HWRM_CFA_EM_FLOW_FREE:
	हाल HWRM_CFA_EM_FLOW_CFG:
	हाल HWRM_CFA_FLOW_ALLOC:
	हाल HWRM_CFA_FLOW_FREE:
	हाल HWRM_CFA_FLOW_INFO:
	हाल HWRM_CFA_FLOW_FLUSH:
	हाल HWRM_CFA_FLOW_STATS:
	हाल HWRM_CFA_METER_PROखाता_ALLOC:
	हाल HWRM_CFA_METER_PROखाता_FREE:
	हाल HWRM_CFA_METER_PROखाता_CFG:
	हाल HWRM_CFA_METER_INSTANCE_ALLOC:
	हाल HWRM_CFA_METER_INSTANCE_FREE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत bool bnxt_kong_hwrm_message(काष्ठा bnxt *bp, काष्ठा input *req)
अणु
	वापस (bp->fw_cap & BNXT_FW_CAP_KONG_MB_CHNL &&
		bnxt_cfa_hwrm_message(le16_to_cpu(req->req_type)));
पूर्ण

अटल अंतरभूत bool bnxt_hwrm_kong_chnl(काष्ठा bnxt *bp, काष्ठा input *req)
अणु
	वापस (bp->fw_cap & BNXT_FW_CAP_KONG_MB_CHNL &&
		req->resp_addr == cpu_to_le64(bp->hwrm_cmd_kong_resp_dma_addr));
पूर्ण

अटल अंतरभूत व्योम *bnxt_get_hwrm_resp_addr(काष्ठा bnxt *bp, व्योम *req)
अणु
	अगर (bnxt_hwrm_kong_chnl(bp, (काष्ठा input *)req))
		वापस bp->hwrm_cmd_kong_resp_addr;
	अन्यथा
		वापस bp->hwrm_cmd_resp_addr;
पूर्ण

अटल अंतरभूत u16 bnxt_get_hwrm_seq_id(काष्ठा bnxt *bp, u16 dst)
अणु
	u16 seq_id;

	अगर (dst == BNXT_HWRM_CHNL_CHIMP)
		seq_id = bp->hwrm_cmd_seq++;
	अन्यथा
		seq_id = bp->hwrm_cmd_kong_seq++;
	वापस seq_id;
पूर्ण

बाह्य स्थिर u16 bnxt_lhपूर्णांक_arr[];

पूर्णांक bnxt_alloc_rx_data(काष्ठा bnxt *bp, काष्ठा bnxt_rx_ring_info *rxr,
		       u16 prod, gfp_t gfp);
व्योम bnxt_reuse_rx_data(काष्ठा bnxt_rx_ring_info *rxr, u16 cons, व्योम *data);
u32 bnxt_fw_health_पढ़ोl(काष्ठा bnxt *bp, पूर्णांक reg_idx);
व्योम bnxt_set_tpa_flags(काष्ठा bnxt *bp);
व्योम bnxt_set_ring_params(काष्ठा bnxt *);
पूर्णांक bnxt_set_rx_skb_mode(काष्ठा bnxt *bp, bool page_mode);
व्योम bnxt_hwrm_cmd_hdr_init(काष्ठा bnxt *, व्योम *, u16, u16, u16);
पूर्णांक _hwrm_send_message(काष्ठा bnxt *, व्योम *, u32, पूर्णांक);
पूर्णांक _hwrm_send_message_silent(काष्ठा bnxt *bp, व्योम *msg, u32 len, पूर्णांक समयout);
पूर्णांक hwrm_send_message(काष्ठा bnxt *, व्योम *, u32, पूर्णांक);
पूर्णांक hwrm_send_message_silent(काष्ठा bnxt *, व्योम *, u32, पूर्णांक);
पूर्णांक bnxt_hwrm_func_drv_rgtr(काष्ठा bnxt *bp, अचिन्हित दीर्घ *bmap,
			    पूर्णांक bmap_size, bool async_only);
पूर्णांक bnxt_get_nr_rss_ctxs(काष्ठा bnxt *bp, पूर्णांक rx_rings);
पूर्णांक bnxt_hwrm_vnic_cfg(काष्ठा bnxt *bp, u16 vnic_id);
पूर्णांक __bnxt_hwrm_get_tx_rings(काष्ठा bnxt *bp, u16 fid, पूर्णांक *tx_rings);
पूर्णांक bnxt_nq_rings_in_use(काष्ठा bnxt *bp);
पूर्णांक bnxt_hwrm_set_coal(काष्ठा bnxt *);
अचिन्हित पूर्णांक bnxt_get_max_func_stat_ctxs(काष्ठा bnxt *bp);
अचिन्हित पूर्णांक bnxt_get_avail_stat_ctxs_क्रम_en(काष्ठा bnxt *bp);
अचिन्हित पूर्णांक bnxt_get_max_func_cp_rings(काष्ठा bnxt *bp);
अचिन्हित पूर्णांक bnxt_get_avail_cp_rings_क्रम_en(काष्ठा bnxt *bp);
पूर्णांक bnxt_get_avail_msix(काष्ठा bnxt *bp, पूर्णांक num);
पूर्णांक bnxt_reserve_rings(काष्ठा bnxt *bp, bool irq_re_init);
व्योम bnxt_tx_disable(काष्ठा bnxt *bp);
व्योम bnxt_tx_enable(काष्ठा bnxt *bp);
पूर्णांक bnxt_update_link(काष्ठा bnxt *bp, bool chng_link_state);
पूर्णांक bnxt_hwrm_set_छोड़ो(काष्ठा bnxt *);
पूर्णांक bnxt_hwrm_set_link_setting(काष्ठा bnxt *, bool, bool);
पूर्णांक bnxt_hwrm_alloc_wol_fltr(काष्ठा bnxt *bp);
पूर्णांक bnxt_hwrm_मुक्त_wol_fltr(काष्ठा bnxt *bp);
पूर्णांक bnxt_hwrm_func_resc_qcaps(काष्ठा bnxt *bp, bool all);
bool bnxt_is_fw_healthy(काष्ठा bnxt *bp);
पूर्णांक bnxt_hwrm_fw_set_समय(काष्ठा bnxt *);
पूर्णांक bnxt_खोलो_nic(काष्ठा bnxt *, bool, bool);
पूर्णांक bnxt_half_खोलो_nic(काष्ठा bnxt *bp);
व्योम bnxt_half_बंद_nic(काष्ठा bnxt *bp);
पूर्णांक bnxt_बंद_nic(काष्ठा bnxt *, bool, bool);
पूर्णांक bnxt_dbg_hwrm_rd_reg(काष्ठा bnxt *bp, u32 reg_off, u16 num_words,
			 u32 *reg_buf);
व्योम bnxt_fw_exception(काष्ठा bnxt *bp);
व्योम bnxt_fw_reset(काष्ठा bnxt *bp);
पूर्णांक bnxt_check_rings(काष्ठा bnxt *bp, पूर्णांक tx, पूर्णांक rx, bool sh, पूर्णांक tcs,
		     पूर्णांक tx_xdp);
पूर्णांक bnxt_setup_mq_tc(काष्ठा net_device *dev, u8 tc);
पूर्णांक bnxt_get_max_rings(काष्ठा bnxt *, पूर्णांक *, पूर्णांक *, bool);
पूर्णांक bnxt_restore_pf_fw_resources(काष्ठा bnxt *bp);
पूर्णांक bnxt_get_port_parent_id(काष्ठा net_device *dev,
			    काष्ठा netdev_phys_item_id *ppid);
व्योम bnxt_dim_work(काष्ठा work_काष्ठा *work);
पूर्णांक bnxt_hwrm_set_ring_coal(काष्ठा bnxt *bp, काष्ठा bnxt_napi *bnapi);

#पूर्ण_अगर
