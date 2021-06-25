<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2014-2016 Broadcom Corporation
 * Copyright (c) 2014-2018 Broadcom Limited
 * Copyright (c) 2018-2021 Broadcom Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * DO NOT MODIFY!!! This file is स्वतःmatically generated.
 */

#अगर_अघोषित _BNXT_HSI_H_
#घोषणा _BNXT_HSI_H_

/* hwrm_cmd_hdr (size:128b/16B) */
काष्ठा hwrm_cmd_hdr अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
पूर्ण;

/* hwrm_resp_hdr (size:64b/8B) */
काष्ठा hwrm_resp_hdr अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
पूर्ण;

#घोषणा CMD_DISCR_TLV_ENCAP 0x8000UL
#घोषणा CMD_DISCR_LAST     CMD_DISCR_TLV_ENCAP


#घोषणा TLV_TYPE_HWRM_REQUEST                    0x1UL
#घोषणा TLV_TYPE_HWRM_RESPONSE                   0x2UL
#घोषणा TLV_TYPE_ROCE_SP_COMMAND                 0x3UL
#घोषणा TLV_TYPE_QUERY_ROCE_CC_GEN1              0x4UL
#घोषणा TLV_TYPE_MODIFY_ROCE_CC_GEN1             0x5UL
#घोषणा TLV_TYPE_ENGINE_CKV_ALIAS_ECC_PUBLIC_KEY 0x8001UL
#घोषणा TLV_TYPE_ENGINE_CKV_IV                   0x8003UL
#घोषणा TLV_TYPE_ENGINE_CKV_AUTH_TAG             0x8004UL
#घोषणा TLV_TYPE_ENGINE_CKV_CIPHERTEXT           0x8005UL
#घोषणा TLV_TYPE_ENGINE_CKV_HOST_ALGORITHMS      0x8006UL
#घोषणा TLV_TYPE_ENGINE_CKV_HOST_ECC_PUBLIC_KEY  0x8007UL
#घोषणा TLV_TYPE_ENGINE_CKV_ECDSA_SIGNATURE      0x8008UL
#घोषणा TLV_TYPE_ENGINE_CKV_FW_ECC_PUBLIC_KEY    0x8009UL
#घोषणा TLV_TYPE_ENGINE_CKV_FW_ALGORITHMS        0x800aUL
#घोषणा TLV_TYPE_LAST                           TLV_TYPE_ENGINE_CKV_FW_ALGORITHMS


/* tlv (size:64b/8B) */
काष्ठा tlv अणु
	__le16	cmd_discr;
	u8	reserved_8b;
	u8	flags;
	#घोषणा TLV_FLAGS_MORE         0x1UL
	#घोषणा TLV_FLAGS_MORE_LAST      0x0UL
	#घोषणा TLV_FLAGS_MORE_NOT_LAST  0x1UL
	#घोषणा TLV_FLAGS_REQUIRED     0x2UL
	#घोषणा TLV_FLAGS_REQUIRED_NO    (0x0UL << 1)
	#घोषणा TLV_FLAGS_REQUIRED_YES   (0x1UL << 1)
	#घोषणा TLV_FLAGS_REQUIRED_LAST TLV_FLAGS_REQUIRED_YES
	__le16	tlv_type;
	__le16	length;
पूर्ण;

/* input (size:128b/16B) */
काष्ठा input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
पूर्ण;

/* output (size:64b/8B) */
काष्ठा output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
पूर्ण;

/* hwrm_लघु_input (size:128b/16B) */
काष्ठा hwrm_लघु_input अणु
	__le16	req_type;
	__le16	signature;
	#घोषणा SHORT_REQ_SIGNATURE_SHORT_CMD 0x4321UL
	#घोषणा SHORT_REQ_SIGNATURE_LAST     SHORT_REQ_SIGNATURE_SHORT_CMD
	__le16	target_id;
	#घोषणा SHORT_REQ_TARGET_ID_DEFAULT 0x0UL
	#घोषणा SHORT_REQ_TARGET_ID_TOOLS   0xfffdUL
	#घोषणा SHORT_REQ_TARGET_ID_LAST   SHORT_REQ_TARGET_ID_TOOLS
	__le16	size;
	__le64	req_addr;
पूर्ण;

/* cmd_nums (size:64b/8B) */
काष्ठा cmd_nums अणु
	__le16	req_type;
	#घोषणा HWRM_VER_GET                              0x0UL
	#घोषणा HWRM_FUNC_ECHO_RESPONSE                   0xbUL
	#घोषणा HWRM_ERROR_RECOVERY_QCFG                  0xcUL
	#घोषणा HWRM_FUNC_DRV_IF_CHANGE                   0xdUL
	#घोषणा HWRM_FUNC_BUF_UNRGTR                      0xeUL
	#घोषणा HWRM_FUNC_VF_CFG                          0xfUL
	#घोषणा HWRM_RESERVED1                            0x10UL
	#घोषणा HWRM_FUNC_RESET                           0x11UL
	#घोषणा HWRM_FUNC_GETFID                          0x12UL
	#घोषणा HWRM_FUNC_VF_ALLOC                        0x13UL
	#घोषणा HWRM_FUNC_VF_FREE                         0x14UL
	#घोषणा HWRM_FUNC_QCAPS                           0x15UL
	#घोषणा HWRM_FUNC_QCFG                            0x16UL
	#घोषणा HWRM_FUNC_CFG                             0x17UL
	#घोषणा HWRM_FUNC_QSTATS                          0x18UL
	#घोषणा HWRM_FUNC_CLR_STATS                       0x19UL
	#घोषणा HWRM_FUNC_DRV_UNRGTR                      0x1aUL
	#घोषणा HWRM_FUNC_VF_RESC_FREE                    0x1bUL
	#घोषणा HWRM_FUNC_VF_VNIC_IDS_QUERY               0x1cUL
	#घोषणा HWRM_FUNC_DRV_RGTR                        0x1dUL
	#घोषणा HWRM_FUNC_DRV_QVER                        0x1eUL
	#घोषणा HWRM_FUNC_BUF_RGTR                        0x1fUL
	#घोषणा HWRM_PORT_PHY_CFG                         0x20UL
	#घोषणा HWRM_PORT_MAC_CFG                         0x21UL
	#घोषणा HWRM_PORT_TS_QUERY                        0x22UL
	#घोषणा HWRM_PORT_QSTATS                          0x23UL
	#घोषणा HWRM_PORT_LPBK_QSTATS                     0x24UL
	#घोषणा HWRM_PORT_CLR_STATS                       0x25UL
	#घोषणा HWRM_PORT_LPBK_CLR_STATS                  0x26UL
	#घोषणा HWRM_PORT_PHY_QCFG                        0x27UL
	#घोषणा HWRM_PORT_MAC_QCFG                        0x28UL
	#घोषणा HWRM_PORT_MAC_PTP_QCFG                    0x29UL
	#घोषणा HWRM_PORT_PHY_QCAPS                       0x2aUL
	#घोषणा HWRM_PORT_PHY_I2C_WRITE                   0x2bUL
	#घोषणा HWRM_PORT_PHY_I2C_READ                    0x2cUL
	#घोषणा HWRM_PORT_LED_CFG                         0x2dUL
	#घोषणा HWRM_PORT_LED_QCFG                        0x2eUL
	#घोषणा HWRM_PORT_LED_QCAPS                       0x2fUL
	#घोषणा HWRM_QUEUE_QPORTCFG                       0x30UL
	#घोषणा HWRM_QUEUE_QCFG                           0x31UL
	#घोषणा HWRM_QUEUE_CFG                            0x32UL
	#घोषणा HWRM_FUNC_VLAN_CFG                        0x33UL
	#घोषणा HWRM_FUNC_VLAN_QCFG                       0x34UL
	#घोषणा HWRM_QUEUE_PFCENABLE_QCFG                 0x35UL
	#घोषणा HWRM_QUEUE_PFCENABLE_CFG                  0x36UL
	#घोषणा HWRM_QUEUE_PRI2COS_QCFG                   0x37UL
	#घोषणा HWRM_QUEUE_PRI2COS_CFG                    0x38UL
	#घोषणा HWRM_QUEUE_COS2BW_QCFG                    0x39UL
	#घोषणा HWRM_QUEUE_COS2BW_CFG                     0x3aUL
	#घोषणा HWRM_QUEUE_DSCP_QCAPS                     0x3bUL
	#घोषणा HWRM_QUEUE_DSCP2PRI_QCFG                  0x3cUL
	#घोषणा HWRM_QUEUE_DSCP2PRI_CFG                   0x3dUL
	#घोषणा HWRM_VNIC_ALLOC                           0x40UL
	#घोषणा HWRM_VNIC_FREE                            0x41UL
	#घोषणा HWRM_VNIC_CFG                             0x42UL
	#घोषणा HWRM_VNIC_QCFG                            0x43UL
	#घोषणा HWRM_VNIC_TPA_CFG                         0x44UL
	#घोषणा HWRM_VNIC_TPA_QCFG                        0x45UL
	#घोषणा HWRM_VNIC_RSS_CFG                         0x46UL
	#घोषणा HWRM_VNIC_RSS_QCFG                        0x47UL
	#घोषणा HWRM_VNIC_PLCMODES_CFG                    0x48UL
	#घोषणा HWRM_VNIC_PLCMODES_QCFG                   0x49UL
	#घोषणा HWRM_VNIC_QCAPS                           0x4aUL
	#घोषणा HWRM_VNIC_UPDATE                          0x4bUL
	#घोषणा HWRM_RING_ALLOC                           0x50UL
	#घोषणा HWRM_RING_FREE                            0x51UL
	#घोषणा HWRM_RING_CMPL_RING_QAGGINT_PARAMS        0x52UL
	#घोषणा HWRM_RING_CMPL_RING_CFG_AGGINT_PARAMS     0x53UL
	#घोषणा HWRM_RING_AGGINT_QCAPS                    0x54UL
	#घोषणा HWRM_RING_SCHQ_ALLOC                      0x55UL
	#घोषणा HWRM_RING_SCHQ_CFG                        0x56UL
	#घोषणा HWRM_RING_SCHQ_FREE                       0x57UL
	#घोषणा HWRM_RING_RESET                           0x5eUL
	#घोषणा HWRM_RING_GRP_ALLOC                       0x60UL
	#घोषणा HWRM_RING_GRP_FREE                        0x61UL
	#घोषणा HWRM_RING_CFG                             0x62UL
	#घोषणा HWRM_RING_QCFG                            0x63UL
	#घोषणा HWRM_RESERVED5                            0x64UL
	#घोषणा HWRM_RESERVED6                            0x65UL
	#घोषणा HWRM_VNIC_RSS_COS_LB_CTX_ALLOC            0x70UL
	#घोषणा HWRM_VNIC_RSS_COS_LB_CTX_FREE             0x71UL
	#घोषणा HWRM_QUEUE_MPLS_QCAPS                     0x80UL
	#घोषणा HWRM_QUEUE_MPLSTC2PRI_QCFG                0x81UL
	#घोषणा HWRM_QUEUE_MPLSTC2PRI_CFG                 0x82UL
	#घोषणा HWRM_QUEUE_VLANPRI_QCAPS                  0x83UL
	#घोषणा HWRM_QUEUE_VLANPRI2PRI_QCFG               0x84UL
	#घोषणा HWRM_QUEUE_VLANPRI2PRI_CFG                0x85UL
	#घोषणा HWRM_CFA_L2_FILTER_ALLOC                  0x90UL
	#घोषणा HWRM_CFA_L2_FILTER_FREE                   0x91UL
	#घोषणा HWRM_CFA_L2_FILTER_CFG                    0x92UL
	#घोषणा HWRM_CFA_L2_SET_RX_MASK                   0x93UL
	#घोषणा HWRM_CFA_VLAN_ANTISPOOF_CFG               0x94UL
	#घोषणा HWRM_CFA_TUNNEL_FILTER_ALLOC              0x95UL
	#घोषणा HWRM_CFA_TUNNEL_FILTER_FREE               0x96UL
	#घोषणा HWRM_CFA_ENCAP_RECORD_ALLOC               0x97UL
	#घोषणा HWRM_CFA_ENCAP_RECORD_FREE                0x98UL
	#घोषणा HWRM_CFA_NTUPLE_FILTER_ALLOC              0x99UL
	#घोषणा HWRM_CFA_NTUPLE_FILTER_FREE               0x9aUL
	#घोषणा HWRM_CFA_NTUPLE_FILTER_CFG                0x9bUL
	#घोषणा HWRM_CFA_EM_FLOW_ALLOC                    0x9cUL
	#घोषणा HWRM_CFA_EM_FLOW_FREE                     0x9dUL
	#घोषणा HWRM_CFA_EM_FLOW_CFG                      0x9eUL
	#घोषणा HWRM_TUNNEL_DST_PORT_QUERY                0xa0UL
	#घोषणा HWRM_TUNNEL_DST_PORT_ALLOC                0xa1UL
	#घोषणा HWRM_TUNNEL_DST_PORT_FREE                 0xa2UL
	#घोषणा HWRM_STAT_CTX_ENG_QUERY                   0xafUL
	#घोषणा HWRM_STAT_CTX_ALLOC                       0xb0UL
	#घोषणा HWRM_STAT_CTX_FREE                        0xb1UL
	#घोषणा HWRM_STAT_CTX_QUERY                       0xb2UL
	#घोषणा HWRM_STAT_CTX_CLR_STATS                   0xb3UL
	#घोषणा HWRM_PORT_QSTATS_EXT                      0xb4UL
	#घोषणा HWRM_PORT_PHY_MDIO_WRITE                  0xb5UL
	#घोषणा HWRM_PORT_PHY_MDIO_READ                   0xb6UL
	#घोषणा HWRM_PORT_PHY_MDIO_BUS_ACQUIRE            0xb7UL
	#घोषणा HWRM_PORT_PHY_MDIO_BUS_RELEASE            0xb8UL
	#घोषणा HWRM_PORT_QSTATS_EXT_PFC_WD               0xb9UL
	#घोषणा HWRM_RESERVED7                            0xbaUL
	#घोषणा HWRM_PORT_TX_FIR_CFG                      0xbbUL
	#घोषणा HWRM_PORT_TX_FIR_QCFG                     0xbcUL
	#घोषणा HWRM_PORT_ECN_QSTATS                      0xbdUL
	#घोषणा HWRM_FW_LIVEPATCH_QUERY                   0xbeUL
	#घोषणा HWRM_FW_LIVEPATCH                         0xbfUL
	#घोषणा HWRM_FW_RESET                             0xc0UL
	#घोषणा HWRM_FW_QSTATUS                           0xc1UL
	#घोषणा HWRM_FW_HEALTH_CHECK                      0xc2UL
	#घोषणा HWRM_FW_SYNC                              0xc3UL
	#घोषणा HWRM_FW_STATE_QCAPS                       0xc4UL
	#घोषणा HWRM_FW_STATE_QUIESCE                     0xc5UL
	#घोषणा HWRM_FW_STATE_BACKUP                      0xc6UL
	#घोषणा HWRM_FW_STATE_RESTORE                     0xc7UL
	#घोषणा HWRM_FW_SET_TIME                          0xc8UL
	#घोषणा HWRM_FW_GET_TIME                          0xc9UL
	#घोषणा HWRM_FW_SET_STRUCTURED_DATA               0xcaUL
	#घोषणा HWRM_FW_GET_STRUCTURED_DATA               0xcbUL
	#घोषणा HWRM_FW_IPC_MAILBOX                       0xccUL
	#घोषणा HWRM_FW_ECN_CFG                           0xcdUL
	#घोषणा HWRM_FW_ECN_QCFG                          0xceUL
	#घोषणा HWRM_FW_SECURE_CFG                        0xcfUL
	#घोषणा HWRM_EXEC_FWD_RESP                        0xd0UL
	#घोषणा HWRM_REJECT_FWD_RESP                      0xd1UL
	#घोषणा HWRM_FWD_RESP                             0xd2UL
	#घोषणा HWRM_FWD_ASYNC_EVENT_CMPL                 0xd3UL
	#घोषणा HWRM_OEM_CMD                              0xd4UL
	#घोषणा HWRM_PORT_PRBS_TEST                       0xd5UL
	#घोषणा HWRM_PORT_SFP_SIDEBAND_CFG                0xd6UL
	#घोषणा HWRM_PORT_SFP_SIDEBAND_QCFG               0xd7UL
	#घोषणा HWRM_FW_STATE_UNQUIESCE                   0xd8UL
	#घोषणा HWRM_PORT_DSC_DUMP                        0xd9UL
	#घोषणा HWRM_TEMP_MONITOR_QUERY                   0xe0UL
	#घोषणा HWRM_REG_POWER_QUERY                      0xe1UL
	#घोषणा HWRM_CORE_FREQUENCY_QUERY                 0xe2UL
	#घोषणा HWRM_REG_POWER_HISTOGRAM                  0xe3UL
	#घोषणा HWRM_WOL_FILTER_ALLOC                     0xf0UL
	#घोषणा HWRM_WOL_FILTER_FREE                      0xf1UL
	#घोषणा HWRM_WOL_FILTER_QCFG                      0xf2UL
	#घोषणा HWRM_WOL_REASON_QCFG                      0xf3UL
	#घोषणा HWRM_CFA_METER_QCAPS                      0xf4UL
	#घोषणा HWRM_CFA_METER_PROखाता_ALLOC              0xf5UL
	#घोषणा HWRM_CFA_METER_PROखाता_FREE               0xf6UL
	#घोषणा HWRM_CFA_METER_PROखाता_CFG                0xf7UL
	#घोषणा HWRM_CFA_METER_INSTANCE_ALLOC             0xf8UL
	#घोषणा HWRM_CFA_METER_INSTANCE_FREE              0xf9UL
	#घोषणा HWRM_CFA_METER_INSTANCE_CFG               0xfaUL
	#घोषणा HWRM_CFA_VFR_ALLOC                        0xfdUL
	#घोषणा HWRM_CFA_VFR_FREE                         0xfeUL
	#घोषणा HWRM_CFA_VF_PAIR_ALLOC                    0x100UL
	#घोषणा HWRM_CFA_VF_PAIR_FREE                     0x101UL
	#घोषणा HWRM_CFA_VF_PAIR_INFO                     0x102UL
	#घोषणा HWRM_CFA_FLOW_ALLOC                       0x103UL
	#घोषणा HWRM_CFA_FLOW_FREE                        0x104UL
	#घोषणा HWRM_CFA_FLOW_FLUSH                       0x105UL
	#घोषणा HWRM_CFA_FLOW_STATS                       0x106UL
	#घोषणा HWRM_CFA_FLOW_INFO                        0x107UL
	#घोषणा HWRM_CFA_DECAP_FILTER_ALLOC               0x108UL
	#घोषणा HWRM_CFA_DECAP_FILTER_FREE                0x109UL
	#घोषणा HWRM_CFA_VLAN_ANTISPOOF_QCFG              0x10aUL
	#घोषणा HWRM_CFA_REसूचीECT_TUNNEL_TYPE_ALLOC       0x10bUL
	#घोषणा HWRM_CFA_REसूचीECT_TUNNEL_TYPE_FREE        0x10cUL
	#घोषणा HWRM_CFA_PAIR_ALLOC                       0x10dUL
	#घोषणा HWRM_CFA_PAIR_FREE                        0x10eUL
	#घोषणा HWRM_CFA_PAIR_INFO                        0x10fUL
	#घोषणा HWRM_FW_IPC_MSG                           0x110UL
	#घोषणा HWRM_CFA_REसूचीECT_TUNNEL_TYPE_INFO        0x111UL
	#घोषणा HWRM_CFA_REसूचीECT_QUERY_TUNNEL_TYPE       0x112UL
	#घोषणा HWRM_CFA_FLOW_AGING_TIMER_RESET           0x113UL
	#घोषणा HWRM_CFA_FLOW_AGING_CFG                   0x114UL
	#घोषणा HWRM_CFA_FLOW_AGING_QCFG                  0x115UL
	#घोषणा HWRM_CFA_FLOW_AGING_QCAPS                 0x116UL
	#घोषणा HWRM_CFA_CTX_MEM_RGTR                     0x117UL
	#घोषणा HWRM_CFA_CTX_MEM_UNRGTR                   0x118UL
	#घोषणा HWRM_CFA_CTX_MEM_QCTX                     0x119UL
	#घोषणा HWRM_CFA_CTX_MEM_QCAPS                    0x11aUL
	#घोषणा HWRM_CFA_COUNTER_QCAPS                    0x11bUL
	#घोषणा HWRM_CFA_COUNTER_CFG                      0x11cUL
	#घोषणा HWRM_CFA_COUNTER_QCFG                     0x11dUL
	#घोषणा HWRM_CFA_COUNTER_QSTATS                   0x11eUL
	#घोषणा HWRM_CFA_TCP_FLAG_PROCESS_QCFG            0x11fUL
	#घोषणा HWRM_CFA_EEM_QCAPS                        0x120UL
	#घोषणा HWRM_CFA_EEM_CFG                          0x121UL
	#घोषणा HWRM_CFA_EEM_QCFG                         0x122UL
	#घोषणा HWRM_CFA_EEM_OP                           0x123UL
	#घोषणा HWRM_CFA_ADV_FLOW_MGNT_QCAPS              0x124UL
	#घोषणा HWRM_CFA_TFLIB                            0x125UL
	#घोषणा HWRM_ENGINE_CKV_STATUS                    0x12eUL
	#घोषणा HWRM_ENGINE_CKV_CKEK_ADD                  0x12fUL
	#घोषणा HWRM_ENGINE_CKV_CKEK_DELETE               0x130UL
	#घोषणा HWRM_ENGINE_CKV_KEY_ADD                   0x131UL
	#घोषणा HWRM_ENGINE_CKV_KEY_DELETE                0x132UL
	#घोषणा HWRM_ENGINE_CKV_FLUSH                     0x133UL
	#घोषणा HWRM_ENGINE_CKV_RNG_GET                   0x134UL
	#घोषणा HWRM_ENGINE_CKV_KEY_GEN                   0x135UL
	#घोषणा HWRM_ENGINE_CKV_KEY_LABEL_CFG             0x136UL
	#घोषणा HWRM_ENGINE_CKV_KEY_LABEL_QCFG            0x137UL
	#घोषणा HWRM_ENGINE_QG_CONFIG_QUERY               0x13cUL
	#घोषणा HWRM_ENGINE_QG_QUERY                      0x13dUL
	#घोषणा HWRM_ENGINE_QG_METER_PROखाता_CONFIG_QUERY 0x13eUL
	#घोषणा HWRM_ENGINE_QG_METER_PROखाता_QUERY        0x13fUL
	#घोषणा HWRM_ENGINE_QG_METER_PROखाता_ALLOC        0x140UL
	#घोषणा HWRM_ENGINE_QG_METER_PROखाता_FREE         0x141UL
	#घोषणा HWRM_ENGINE_QG_METER_QUERY                0x142UL
	#घोषणा HWRM_ENGINE_QG_METER_BIND                 0x143UL
	#घोषणा HWRM_ENGINE_QG_METER_UNBIND               0x144UL
	#घोषणा HWRM_ENGINE_QG_FUNC_BIND                  0x145UL
	#घोषणा HWRM_ENGINE_SG_CONFIG_QUERY               0x146UL
	#घोषणा HWRM_ENGINE_SG_QUERY                      0x147UL
	#घोषणा HWRM_ENGINE_SG_METER_QUERY                0x148UL
	#घोषणा HWRM_ENGINE_SG_METER_CONFIG               0x149UL
	#घोषणा HWRM_ENGINE_SG_QG_BIND                    0x14aUL
	#घोषणा HWRM_ENGINE_QG_SG_UNBIND                  0x14bUL
	#घोषणा HWRM_ENGINE_CONFIG_QUERY                  0x154UL
	#घोषणा HWRM_ENGINE_STATS_CONFIG                  0x155UL
	#घोषणा HWRM_ENGINE_STATS_CLEAR                   0x156UL
	#घोषणा HWRM_ENGINE_STATS_QUERY                   0x157UL
	#घोषणा HWRM_ENGINE_STATS_QUERY_CONTINUOUS_ERROR  0x158UL
	#घोषणा HWRM_ENGINE_RQ_ALLOC                      0x15eUL
	#घोषणा HWRM_ENGINE_RQ_FREE                       0x15fUL
	#घोषणा HWRM_ENGINE_CQ_ALLOC                      0x160UL
	#घोषणा HWRM_ENGINE_CQ_FREE                       0x161UL
	#घोषणा HWRM_ENGINE_NQ_ALLOC                      0x162UL
	#घोषणा HWRM_ENGINE_NQ_FREE                       0x163UL
	#घोषणा HWRM_ENGINE_ON_DIE_RQE_CREDITS            0x164UL
	#घोषणा HWRM_ENGINE_FUNC_QCFG                     0x165UL
	#घोषणा HWRM_FUNC_RESOURCE_QCAPS                  0x190UL
	#घोषणा HWRM_FUNC_VF_RESOURCE_CFG                 0x191UL
	#घोषणा HWRM_FUNC_BACKING_STORE_QCAPS             0x192UL
	#घोषणा HWRM_FUNC_BACKING_STORE_CFG               0x193UL
	#घोषणा HWRM_FUNC_BACKING_STORE_QCFG              0x194UL
	#घोषणा HWRM_FUNC_VF_BW_CFG                       0x195UL
	#घोषणा HWRM_FUNC_VF_BW_QCFG                      0x196UL
	#घोषणा HWRM_FUNC_HOST_PF_IDS_QUERY               0x197UL
	#घोषणा HWRM_FUNC_QSTATS_EXT                      0x198UL
	#घोषणा HWRM_STAT_EXT_CTX_QUERY                   0x199UL
	#घोषणा HWRM_FUNC_SPD_CFG                         0x19aUL
	#घोषणा HWRM_FUNC_SPD_QCFG                        0x19bUL
	#घोषणा HWRM_SELFTEST_QLIST                       0x200UL
	#घोषणा HWRM_SELFTEST_EXEC                        0x201UL
	#घोषणा HWRM_SELFTEST_IRQ                         0x202UL
	#घोषणा HWRM_SELFTEST_RETRIEVE_SERDES_DATA        0x203UL
	#घोषणा HWRM_PCIE_QSTATS                          0x204UL
	#घोषणा HWRM_MFG_FRU_WRITE_CONTROL                0x205UL
	#घोषणा HWRM_MFG_TIMERS_QUERY                     0x206UL
	#घोषणा HWRM_MFG_OTP_CFG                          0x207UL
	#घोषणा HWRM_MFG_OTP_QCFG                         0x208UL
	#घोषणा HWRM_MFG_HDMA_TEST                        0x209UL
	#घोषणा HWRM_MFG_FRU_EEPROM_WRITE                 0x20aUL
	#घोषणा HWRM_MFG_FRU_EEPROM_READ                  0x20bUL
	#घोषणा HWRM_MFG_SOC_IMAGE                        0x20cUL
	#घोषणा HWRM_MFG_SOC_QSTATUS                      0x20dUL
	#घोषणा HWRM_MFG_PARAM_SEEPROM_SYNC               0x20eUL
	#घोषणा HWRM_MFG_PARAM_SEEPROM_READ               0x20fUL
	#घोषणा HWRM_MFG_PARAM_SEEPROM_HEALTH             0x210UL
	#घोषणा HWRM_TF                                   0x2bcUL
	#घोषणा HWRM_TF_VERSION_GET                       0x2bdUL
	#घोषणा HWRM_TF_SESSION_OPEN                      0x2c6UL
	#घोषणा HWRM_TF_SESSION_ATTACH                    0x2c7UL
	#घोषणा HWRM_TF_SESSION_REGISTER                  0x2c8UL
	#घोषणा HWRM_TF_SESSION_UNREGISTER                0x2c9UL
	#घोषणा HWRM_TF_SESSION_CLOSE                     0x2caUL
	#घोषणा HWRM_TF_SESSION_QCFG                      0x2cbUL
	#घोषणा HWRM_TF_SESSION_RESC_QCAPS                0x2ccUL
	#घोषणा HWRM_TF_SESSION_RESC_ALLOC                0x2cdUL
	#घोषणा HWRM_TF_SESSION_RESC_FREE                 0x2ceUL
	#घोषणा HWRM_TF_SESSION_RESC_FLUSH                0x2cfUL
	#घोषणा HWRM_TF_TBL_TYPE_GET                      0x2daUL
	#घोषणा HWRM_TF_TBL_TYPE_SET                      0x2dbUL
	#घोषणा HWRM_TF_TBL_TYPE_BULK_GET                 0x2dcUL
	#घोषणा HWRM_TF_CTXT_MEM_ALLOC                    0x2e2UL
	#घोषणा HWRM_TF_CTXT_MEM_FREE                     0x2e3UL
	#घोषणा HWRM_TF_CTXT_MEM_RGTR                     0x2e4UL
	#घोषणा HWRM_TF_CTXT_MEM_UNRGTR                   0x2e5UL
	#घोषणा HWRM_TF_EXT_EM_QCAPS                      0x2e6UL
	#घोषणा HWRM_TF_EXT_EM_OP                         0x2e7UL
	#घोषणा HWRM_TF_EXT_EM_CFG                        0x2e8UL
	#घोषणा HWRM_TF_EXT_EM_QCFG                       0x2e9UL
	#घोषणा HWRM_TF_EM_INSERT                         0x2eaUL
	#घोषणा HWRM_TF_EM_DELETE                         0x2ebUL
	#घोषणा HWRM_TF_EM_HASH_INSERT                    0x2ecUL
	#घोषणा HWRM_TF_TCAM_SET                          0x2f8UL
	#घोषणा HWRM_TF_TCAM_GET                          0x2f9UL
	#घोषणा HWRM_TF_TCAM_MOVE                         0x2faUL
	#घोषणा HWRM_TF_TCAM_FREE                         0x2fbUL
	#घोषणा HWRM_TF_GLOBAL_CFG_SET                    0x2fcUL
	#घोषणा HWRM_TF_GLOBAL_CFG_GET                    0x2fdUL
	#घोषणा HWRM_TF_IF_TBL_SET                        0x2feUL
	#घोषणा HWRM_TF_IF_TBL_GET                        0x2ffUL
	#घोषणा HWRM_SV                                   0x400UL
	#घोषणा HWRM_DBG_READ_सूचीECT                      0xff10UL
	#घोषणा HWRM_DBG_READ_INसूचीECT                    0xff11UL
	#घोषणा HWRM_DBG_WRITE_सूचीECT                     0xff12UL
	#घोषणा HWRM_DBG_WRITE_INसूचीECT                   0xff13UL
	#घोषणा HWRM_DBG_DUMP                             0xff14UL
	#घोषणा HWRM_DBG_ERASE_NVM                        0xff15UL
	#घोषणा HWRM_DBG_CFG                              0xff16UL
	#घोषणा HWRM_DBG_COREDUMP_LIST                    0xff17UL
	#घोषणा HWRM_DBG_COREDUMP_INITIATE                0xff18UL
	#घोषणा HWRM_DBG_COREDUMP_RETRIEVE                0xff19UL
	#घोषणा HWRM_DBG_FW_CLI                           0xff1aUL
	#घोषणा HWRM_DBG_I2C_CMD                          0xff1bUL
	#घोषणा HWRM_DBG_RING_INFO_GET                    0xff1cUL
	#घोषणा HWRM_DBG_CRASHDUMP_HEADER                 0xff1dUL
	#घोषणा HWRM_DBG_CRASHDUMP_ERASE                  0xff1eUL
	#घोषणा HWRM_DBG_DRV_TRACE                        0xff1fUL
	#घोषणा HWRM_DBG_QCAPS                            0xff20UL
	#घोषणा HWRM_DBG_QCFG                             0xff21UL
	#घोषणा HWRM_DBG_CRASHDUMP_MEDIUM_CFG             0xff22UL
	#घोषणा HWRM_NVM_REQ_ARBITRATION                  0xffedUL
	#घोषणा HWRM_NVM_FACTORY_DEFAULTS                 0xffeeUL
	#घोषणा HWRM_NVM_VALIDATE_OPTION                  0xffefUL
	#घोषणा HWRM_NVM_FLUSH                            0xfff0UL
	#घोषणा HWRM_NVM_GET_VARIABLE                     0xfff1UL
	#घोषणा HWRM_NVM_SET_VARIABLE                     0xfff2UL
	#घोषणा HWRM_NVM_INSTALL_UPDATE                   0xfff3UL
	#घोषणा HWRM_NVM_MODIFY                           0xfff4UL
	#घोषणा HWRM_NVM_VERIFY_UPDATE                    0xfff5UL
	#घोषणा HWRM_NVM_GET_DEV_INFO                     0xfff6UL
	#घोषणा HWRM_NVM_ERASE_सूची_ENTRY                  0xfff7UL
	#घोषणा HWRM_NVM_MOD_सूची_ENTRY                    0xfff8UL
	#घोषणा HWRM_NVM_FIND_सूची_ENTRY                   0xfff9UL
	#घोषणा HWRM_NVM_GET_सूची_ENTRIES                  0xfffaUL
	#घोषणा HWRM_NVM_GET_सूची_INFO                     0xfffbUL
	#घोषणा HWRM_NVM_RAW_DUMP                         0xfffcUL
	#घोषणा HWRM_NVM_READ                             0xfffdUL
	#घोषणा HWRM_NVM_WRITE                            0xfffeUL
	#घोषणा HWRM_NVM_RAW_WRITE_BLK                    0xffffUL
	#घोषणा HWRM_LAST                                HWRM_NVM_RAW_WRITE_BLK
	__le16	unused_0[3];
पूर्ण;

/* ret_codes (size:64b/8B) */
काष्ठा ret_codes अणु
	__le16	error_code;
	#घोषणा HWRM_ERR_CODE_SUCCESS                      0x0UL
	#घोषणा HWRM_ERR_CODE_FAIL                         0x1UL
	#घोषणा HWRM_ERR_CODE_INVALID_PARAMS               0x2UL
	#घोषणा HWRM_ERR_CODE_RESOURCE_ACCESS_DENIED       0x3UL
	#घोषणा HWRM_ERR_CODE_RESOURCE_ALLOC_ERROR         0x4UL
	#घोषणा HWRM_ERR_CODE_INVALID_FLAGS                0x5UL
	#घोषणा HWRM_ERR_CODE_INVALID_ENABLES              0x6UL
	#घोषणा HWRM_ERR_CODE_UNSUPPORTED_TLV              0x7UL
	#घोषणा HWRM_ERR_CODE_NO_BUFFER                    0x8UL
	#घोषणा HWRM_ERR_CODE_UNSUPPORTED_OPTION_ERR       0x9UL
	#घोषणा HWRM_ERR_CODE_HOT_RESET_PROGRESS           0xaUL
	#घोषणा HWRM_ERR_CODE_HOT_RESET_FAIL               0xbUL
	#घोषणा HWRM_ERR_CODE_NO_FLOW_COUNTER_DURING_ALLOC 0xcUL
	#घोषणा HWRM_ERR_CODE_KEY_HASH_COLLISION           0xdUL
	#घोषणा HWRM_ERR_CODE_KEY_ALREADY_EXISTS           0xeUL
	#घोषणा HWRM_ERR_CODE_HWRM_ERROR                   0xfUL
	#घोषणा HWRM_ERR_CODE_BUSY                         0x10UL
	#घोषणा HWRM_ERR_CODE_RESOURCE_LOCKED              0x11UL
	#घोषणा HWRM_ERR_CODE_TLV_ENCAPSULATED_RESPONSE    0x8000UL
	#घोषणा HWRM_ERR_CODE_UNKNOWN_ERR                  0xfffeUL
	#घोषणा HWRM_ERR_CODE_CMD_NOT_SUPPORTED            0xffffUL
	#घोषणा HWRM_ERR_CODE_LAST                        HWRM_ERR_CODE_CMD_NOT_SUPPORTED
	__le16	unused_0[3];
पूर्ण;

/* hwrm_err_output (size:128b/16B) */
काष्ठा hwrm_err_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	opaque_0;
	__le16	opaque_1;
	u8	cmd_err;
	u8	valid;
पूर्ण;
#घोषणा HWRM_NA_SIGNATURE ((__le32)(-1))
#घोषणा HWRM_MAX_REQ_LEN 128
#घोषणा HWRM_MAX_RESP_LEN 704
#घोषणा HW_HASH_INDEX_SIZE 0x80
#घोषणा HW_HASH_KEY_SIZE 40
#घोषणा HWRM_RESP_VALID_KEY 1
#घोषणा HWRM_TARGET_ID_BONO 0xFFF8
#घोषणा HWRM_TARGET_ID_KONG 0xFFF9
#घोषणा HWRM_TARGET_ID_APE 0xFFFA
#घोषणा HWRM_TARGET_ID_TOOLS 0xFFFD
#घोषणा HWRM_VERSION_MAJOR 1
#घोषणा HWRM_VERSION_MINOR 10
#घोषणा HWRM_VERSION_UPDATE 2
#घोषणा HWRM_VERSION_RSVD 16
#घोषणा HWRM_VERSION_STR "1.10.2.16"

/* hwrm_ver_get_input (size:192b/24B) */
काष्ठा hwrm_ver_get_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	u8	hwrm_पूर्णांकf_maj;
	u8	hwrm_पूर्णांकf_min;
	u8	hwrm_पूर्णांकf_upd;
	u8	unused_0[5];
पूर्ण;

/* hwrm_ver_get_output (size:1408b/176B) */
काष्ठा hwrm_ver_get_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	hwrm_पूर्णांकf_maj_8b;
	u8	hwrm_पूर्णांकf_min_8b;
	u8	hwrm_पूर्णांकf_upd_8b;
	u8	hwrm_पूर्णांकf_rsvd_8b;
	u8	hwrm_fw_maj_8b;
	u8	hwrm_fw_min_8b;
	u8	hwrm_fw_bld_8b;
	u8	hwrm_fw_rsvd_8b;
	u8	mgmt_fw_maj_8b;
	u8	mgmt_fw_min_8b;
	u8	mgmt_fw_bld_8b;
	u8	mgmt_fw_rsvd_8b;
	u8	netctrl_fw_maj_8b;
	u8	netctrl_fw_min_8b;
	u8	netctrl_fw_bld_8b;
	u8	netctrl_fw_rsvd_8b;
	__le32	dev_caps_cfg;
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_SECURE_FW_UPD_SUPPORTED                  0x1UL
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_FW_DCBX_AGENT_SUPPORTED                  0x2UL
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_SHORT_CMD_SUPPORTED                      0x4UL
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_SHORT_CMD_REQUIRED                       0x8UL
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_KONG_MB_CHNL_SUPPORTED                   0x10UL
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_FLOW_HANDLE_64BIT_SUPPORTED              0x20UL
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_L2_FILTER_TYPES_ROCE_OR_L2_SUPPORTED     0x40UL
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_VIRTIO_VSWITCH_OFFLOAD_SUPPORTED         0x80UL
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_TRUSTED_VF_SUPPORTED                     0x100UL
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_FLOW_AGING_SUPPORTED                     0x200UL
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_ADV_FLOW_COUNTERS_SUPPORTED              0x400UL
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_CFA_EEM_SUPPORTED                        0x800UL
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_CFA_ADV_FLOW_MGNT_SUPPORTED              0x1000UL
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_CFA_TFLIB_SUPPORTED                      0x2000UL
	#घोषणा VER_GET_RESP_DEV_CAPS_CFG_CFA_TRUFLOW_SUPPORTED                    0x4000UL
	u8	roce_fw_maj_8b;
	u8	roce_fw_min_8b;
	u8	roce_fw_bld_8b;
	u8	roce_fw_rsvd_8b;
	अक्षर	hwrm_fw_name[16];
	अक्षर	mgmt_fw_name[16];
	अक्षर	netctrl_fw_name[16];
	अक्षर	active_pkg_name[16];
	अक्षर	roce_fw_name[16];
	__le16	chip_num;
	u8	chip_rev;
	u8	chip_metal;
	u8	chip_bond_id;
	u8	chip_platक्रमm_type;
	#घोषणा VER_GET_RESP_CHIP_PLATFORM_TYPE_ASIC      0x0UL
	#घोषणा VER_GET_RESP_CHIP_PLATFORM_TYPE_FPGA      0x1UL
	#घोषणा VER_GET_RESP_CHIP_PLATFORM_TYPE_PALLADIUM 0x2UL
	#घोषणा VER_GET_RESP_CHIP_PLATFORM_TYPE_LAST     VER_GET_RESP_CHIP_PLATFORM_TYPE_PALLADIUM
	__le16	max_req_win_len;
	__le16	max_resp_len;
	__le16	def_req_समयout;
	u8	flags;
	#घोषणा VER_GET_RESP_FLAGS_DEV_NOT_RDY                   0x1UL
	#घोषणा VER_GET_RESP_FLAGS_EXT_VER_AVAIL                 0x2UL
	#घोषणा VER_GET_RESP_FLAGS_DEV_NOT_RDY_BACKING_STORE     0x4UL
	u8	unused_0[2];
	u8	always_1;
	__le16	hwrm_पूर्णांकf_major;
	__le16	hwrm_पूर्णांकf_minor;
	__le16	hwrm_पूर्णांकf_build;
	__le16	hwrm_पूर्णांकf_patch;
	__le16	hwrm_fw_major;
	__le16	hwrm_fw_minor;
	__le16	hwrm_fw_build;
	__le16	hwrm_fw_patch;
	__le16	mgmt_fw_major;
	__le16	mgmt_fw_minor;
	__le16	mgmt_fw_build;
	__le16	mgmt_fw_patch;
	__le16	netctrl_fw_major;
	__le16	netctrl_fw_minor;
	__le16	netctrl_fw_build;
	__le16	netctrl_fw_patch;
	__le16	roce_fw_major;
	__le16	roce_fw_minor;
	__le16	roce_fw_build;
	__le16	roce_fw_patch;
	__le16	max_ext_req_len;
	u8	unused_1[5];
	u8	valid;
पूर्ण;

/* eject_cmpl (size:128b/16B) */
काष्ठा eject_cmpl अणु
	__le16	type;
	#घोषणा EJECT_CMPL_TYPE_MASK       0x3fUL
	#घोषणा EJECT_CMPL_TYPE_SFT        0
	#घोषणा EJECT_CMPL_TYPE_STAT_EJECT   0x1aUL
	#घोषणा EJECT_CMPL_TYPE_LAST        EJECT_CMPL_TYPE_STAT_EJECT
	#घोषणा EJECT_CMPL_FLAGS_MASK      0xffc0UL
	#घोषणा EJECT_CMPL_FLAGS_SFT       6
	#घोषणा EJECT_CMPL_FLAGS_ERROR      0x40UL
	__le16	len;
	__le32	opaque;
	__le16	v;
	#घोषणा EJECT_CMPL_V                              0x1UL
	#घोषणा EJECT_CMPL_ERRORS_MASK                    0xfffeUL
	#घोषणा EJECT_CMPL_ERRORS_SFT                     1
	#घोषणा EJECT_CMPL_ERRORS_BUFFER_ERROR_MASK        0xeUL
	#घोषणा EJECT_CMPL_ERRORS_BUFFER_ERROR_SFT         1
	#घोषणा EJECT_CMPL_ERRORS_BUFFER_ERROR_NO_BUFFER     (0x0UL << 1)
	#घोषणा EJECT_CMPL_ERRORS_BUFFER_ERROR_DID_NOT_FIT   (0x1UL << 1)
	#घोषणा EJECT_CMPL_ERRORS_BUFFER_ERROR_BAD_FORMAT    (0x3UL << 1)
	#घोषणा EJECT_CMPL_ERRORS_BUFFER_ERROR_FLUSH         (0x5UL << 1)
	#घोषणा EJECT_CMPL_ERRORS_BUFFER_ERROR_LAST         EJECT_CMPL_ERRORS_BUFFER_ERROR_FLUSH
	__le16	reserved16;
	__le32	unused_2;
पूर्ण;

/* hwrm_cmpl (size:128b/16B) */
काष्ठा hwrm_cmpl अणु
	__le16	type;
	#घोषणा CMPL_TYPE_MASK     0x3fUL
	#घोषणा CMPL_TYPE_SFT      0
	#घोषणा CMPL_TYPE_HWRM_DONE  0x20UL
	#घोषणा CMPL_TYPE_LAST      CMPL_TYPE_HWRM_DONE
	__le16	sequence_id;
	__le32	unused_1;
	__le32	v;
	#घोषणा CMPL_V     0x1UL
	__le32	unused_3;
पूर्ण;

/* hwrm_fwd_req_cmpl (size:128b/16B) */
काष्ठा hwrm_fwd_req_cmpl अणु
	__le16	req_len_type;
	#घोषणा FWD_REQ_CMPL_TYPE_MASK        0x3fUL
	#घोषणा FWD_REQ_CMPL_TYPE_SFT         0
	#घोषणा FWD_REQ_CMPL_TYPE_HWRM_FWD_REQ  0x22UL
	#घोषणा FWD_REQ_CMPL_TYPE_LAST         FWD_REQ_CMPL_TYPE_HWRM_FWD_REQ
	#घोषणा FWD_REQ_CMPL_REQ_LEN_MASK     0xffc0UL
	#घोषणा FWD_REQ_CMPL_REQ_LEN_SFT      6
	__le16	source_id;
	__le32	unused0;
	__le32	req_buf_addr_v[2];
	#घोषणा FWD_REQ_CMPL_V                0x1UL
	#घोषणा FWD_REQ_CMPL_REQ_BUF_ADDR_MASK 0xfffffffeUL
	#घोषणा FWD_REQ_CMPL_REQ_BUF_ADDR_SFT 1
पूर्ण;

/* hwrm_fwd_resp_cmpl (size:128b/16B) */
काष्ठा hwrm_fwd_resp_cmpl अणु
	__le16	type;
	#घोषणा FWD_RESP_CMPL_TYPE_MASK         0x3fUL
	#घोषणा FWD_RESP_CMPL_TYPE_SFT          0
	#घोषणा FWD_RESP_CMPL_TYPE_HWRM_FWD_RESP  0x24UL
	#घोषणा FWD_RESP_CMPL_TYPE_LAST          FWD_RESP_CMPL_TYPE_HWRM_FWD_RESP
	__le16	source_id;
	__le16	resp_len;
	__le16	unused_1;
	__le32	resp_buf_addr_v[2];
	#घोषणा FWD_RESP_CMPL_V                 0x1UL
	#घोषणा FWD_RESP_CMPL_RESP_BUF_ADDR_MASK 0xfffffffeUL
	#घोषणा FWD_RESP_CMPL_RESP_BUF_ADDR_SFT 1
पूर्ण;

/* hwrm_async_event_cmpl (size:128b/16B) */
काष्ठा hwrm_async_event_cmpl अणु
	__le16	type;
	#घोषणा ASYNC_EVENT_CMPL_TYPE_MASK            0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_TYPE_SFT             0
	#घोषणा ASYNC_EVENT_CMPL_TYPE_HWRM_ASYNC_EVENT  0x2eUL
	#घोषणा ASYNC_EVENT_CMPL_TYPE_LAST             ASYNC_EVENT_CMPL_TYPE_HWRM_ASYNC_EVENT
	__le16	event_id;
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_LINK_STATUS_CHANGE         0x0UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_LINK_MTU_CHANGE            0x1UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CHANGE          0x2UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_DCB_CONFIG_CHANGE          0x3UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_PORT_CONN_NOT_ALLOWED      0x4UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CFG_NOT_ALLOWED 0x5UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CFG_CHANGE      0x6UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_PORT_PHY_CFG_CHANGE        0x7UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_RESET_NOTIFY               0x8UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_ERROR_RECOVERY             0x9UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_RING_MONITOR_MSG           0xaUL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_FUNC_DRVR_UNLOAD           0x10UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_FUNC_DRVR_LOAD             0x11UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_FUNC_FLR_PROC_CMPLT        0x12UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_PF_DRVR_UNLOAD             0x20UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_PF_DRVR_LOAD               0x21UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_VF_FLR                     0x30UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_VF_MAC_ADDR_CHANGE         0x31UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_PF_VF_COMM_STATUS_CHANGE   0x32UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_VF_CFG_CHANGE              0x33UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_LLFC_PFC_CHANGE            0x34UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_DEFAULT_VNIC_CHANGE        0x35UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_HW_FLOW_AGED               0x36UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_DEBUG_NOTIFICATION         0x37UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_EEM_CACHE_FLUSH_REQ        0x38UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_EEM_CACHE_FLUSH_DONE       0x39UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_TCP_FLAG_ACTION_CHANGE     0x3aUL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_EEM_FLOW_ACTIVE            0x3bUL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_EEM_CFG_CHANGE             0x3cUL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_TFLIB_DEFAULT_VNIC_CHANGE  0x3dUL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_TFLIB_LINK_STATUS_CHANGE   0x3eUL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_QUIESCE_DONE               0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_DEFERRED_RESPONSE          0x40UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_PFC_WATCHDOG_CFG_CHANGE    0x41UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_ECHO_REQUEST               0x42UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_MAX_RGTR_EVENT_ID          0x43UL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_FW_TRACE_MSG               0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_HWRM_ERROR                 0xffUL
	#घोषणा ASYNC_EVENT_CMPL_EVENT_ID_LAST                      ASYNC_EVENT_CMPL_EVENT_ID_HWRM_ERROR
	__le32	event_data2;
	u8	opaque_v;
	#घोषणा ASYNC_EVENT_CMPL_V          0x1UL
	#घोषणा ASYNC_EVENT_CMPL_OPAQUE_MASK 0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_OPAQUE_SFT 1
	u8	बारtamp_lo;
	__le16	बारtamp_hi;
	__le32	event_data1;
पूर्ण;

/* hwrm_async_event_cmpl_link_status_change (size:128b/16B) */
काष्ठा hwrm_async_event_cmpl_link_status_change अणु
	__le16	type;
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_TYPE_MASK            0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_TYPE_SFT             0
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_TYPE_HWRM_ASYNC_EVENT  0x2eUL
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_TYPE_LAST             ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_TYPE_HWRM_ASYNC_EVENT
	__le16	event_id;
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_EVENT_ID_LINK_STATUS_CHANGE 0x0UL
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_EVENT_ID_LAST              ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_EVENT_ID_LINK_STATUS_CHANGE
	__le32	event_data2;
	u8	opaque_v;
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_V          0x1UL
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_OPAQUE_MASK 0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_OPAQUE_SFT 1
	u8	बारtamp_lo;
	__le16	बारtamp_hi;
	__le32	event_data1;
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_EVENT_DATA1_LINK_CHANGE     0x1UL
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_EVENT_DATA1_LINK_CHANGE_DOWN  0x0UL
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_EVENT_DATA1_LINK_CHANGE_UP    0x1UL
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_EVENT_DATA1_LINK_CHANGE_LAST ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_EVENT_DATA1_LINK_CHANGE_UP
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_EVENT_DATA1_PORT_MASK       0xeUL
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_EVENT_DATA1_PORT_SFT        1
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_EVENT_DATA1_PORT_ID_MASK    0xffff0UL
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_EVENT_DATA1_PORT_ID_SFT     4
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_EVENT_DATA1_PF_ID_MASK      0xff00000UL
	#घोषणा ASYNC_EVENT_CMPL_LINK_STATUS_CHANGE_EVENT_DATA1_PF_ID_SFT       20
पूर्ण;

/* hwrm_async_event_cmpl_port_conn_not_allowed (size:128b/16B) */
काष्ठा hwrm_async_event_cmpl_port_conn_not_allowed अणु
	__le16	type;
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_TYPE_MASK            0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_TYPE_SFT             0
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_TYPE_HWRM_ASYNC_EVENT  0x2eUL
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_TYPE_LAST             ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_TYPE_HWRM_ASYNC_EVENT
	__le16	event_id;
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_EVENT_ID_PORT_CONN_NOT_ALLOWED 0x4UL
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_EVENT_ID_LAST                 ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_EVENT_ID_PORT_CONN_NOT_ALLOWED
	__le32	event_data2;
	u8	opaque_v;
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_V          0x1UL
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_OPAQUE_MASK 0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_OPAQUE_SFT 1
	u8	बारtamp_lo;
	__le16	बारtamp_hi;
	__le32	event_data1;
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_EVENT_DATA1_PORT_ID_MASK                 0xffffUL
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_EVENT_DATA1_PORT_ID_SFT                  0
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_EVENT_DATA1_ENFORCEMENT_POLICY_MASK      0xff0000UL
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_EVENT_DATA1_ENFORCEMENT_POLICY_SFT       16
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_EVENT_DATA1_ENFORCEMENT_POLICY_NONE        (0x0UL << 16)
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_EVENT_DATA1_ENFORCEMENT_POLICY_DISABLETX   (0x1UL << 16)
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_EVENT_DATA1_ENFORCEMENT_POLICY_WARNINGMSG  (0x2UL << 16)
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_EVENT_DATA1_ENFORCEMENT_POLICY_PWRDOWN     (0x3UL << 16)
	#घोषणा ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_EVENT_DATA1_ENFORCEMENT_POLICY_LAST       ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_EVENT_DATA1_ENFORCEMENT_POLICY_PWRDOWN
पूर्ण;

/* hwrm_async_event_cmpl_link_speed_cfg_change (size:128b/16B) */
काष्ठा hwrm_async_event_cmpl_link_speed_cfg_change अणु
	__le16	type;
	#घोषणा ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_TYPE_MASK            0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_TYPE_SFT             0
	#घोषणा ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_TYPE_HWRM_ASYNC_EVENT  0x2eUL
	#घोषणा ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_TYPE_LAST             ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_TYPE_HWRM_ASYNC_EVENT
	__le16	event_id;
	#घोषणा ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_EVENT_ID_LINK_SPEED_CFG_CHANGE 0x6UL
	#घोषणा ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_EVENT_ID_LAST                 ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_EVENT_ID_LINK_SPEED_CFG_CHANGE
	__le32	event_data2;
	u8	opaque_v;
	#घोषणा ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_V          0x1UL
	#घोषणा ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_OPAQUE_MASK 0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_OPAQUE_SFT 1
	u8	बारtamp_lo;
	__le16	बारtamp_hi;
	__le32	event_data1;
	#घोषणा ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_EVENT_DATA1_PORT_ID_MASK                     0xffffUL
	#घोषणा ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_EVENT_DATA1_PORT_ID_SFT                      0
	#घोषणा ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_EVENT_DATA1_SUPPORTED_LINK_SPEEDS_CHANGE     0x10000UL
	#घोषणा ASYNC_EVENT_CMPL_LINK_SPEED_CFG_CHANGE_EVENT_DATA1_ILLEGAL_LINK_SPEED_CFG           0x20000UL
पूर्ण;

/* hwrm_async_event_cmpl_reset_notअगरy (size:128b/16B) */
काष्ठा hwrm_async_event_cmpl_reset_notअगरy अणु
	__le16	type;
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_TYPE_MASK            0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_TYPE_SFT             0
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_TYPE_HWRM_ASYNC_EVENT  0x2eUL
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_TYPE_LAST             ASYNC_EVENT_CMPL_RESET_NOTIFY_TYPE_HWRM_ASYNC_EVENT
	__le16	event_id;
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_ID_RESET_NOTIFY 0x8UL
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_ID_LAST        ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_ID_RESET_NOTIFY
	__le32	event_data2;
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA2_FW_STATUS_CODE_MASK 0xffffUL
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA2_FW_STATUS_CODE_SFT 0
	u8	opaque_v;
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_V          0x1UL
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_OPAQUE_MASK 0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_OPAQUE_SFT 1
	u8	बारtamp_lo;
	__le16	बारtamp_hi;
	__le32	event_data1;
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_DRIVER_ACTION_MASK                  0xffUL
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_DRIVER_ACTION_SFT                   0
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_DRIVER_ACTION_DRIVER_STOP_TX_QUEUE    0x1UL
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_DRIVER_ACTION_DRIVER_IFDOWN           0x2UL
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_DRIVER_ACTION_LAST                   ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_DRIVER_ACTION_DRIVER_IFDOWN
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_REASON_CODE_MASK                    0xff00UL
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_REASON_CODE_SFT                     8
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_REASON_CODE_MANAGEMENT_RESET_REQUEST  (0x1UL << 8)
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_REASON_CODE_FW_EXCEPTION_FATAL        (0x2UL << 8)
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_REASON_CODE_FW_EXCEPTION_NON_FATAL    (0x3UL << 8)
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_REASON_CODE_FAST_RESET                (0x4UL << 8)
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_REASON_CODE_LAST                     ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_REASON_CODE_FAST_RESET
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_DELAY_IN_100MS_TICKS_MASK           0xffff0000UL
	#घोषणा ASYNC_EVENT_CMPL_RESET_NOTIFY_EVENT_DATA1_DELAY_IN_100MS_TICKS_SFT            16
पूर्ण;

/* hwrm_async_event_cmpl_error_recovery (size:128b/16B) */
काष्ठा hwrm_async_event_cmpl_error_recovery अणु
	__le16	type;
	#घोषणा ASYNC_EVENT_CMPL_ERROR_RECOVERY_TYPE_MASK            0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_ERROR_RECOVERY_TYPE_SFT             0
	#घोषणा ASYNC_EVENT_CMPL_ERROR_RECOVERY_TYPE_HWRM_ASYNC_EVENT  0x2eUL
	#घोषणा ASYNC_EVENT_CMPL_ERROR_RECOVERY_TYPE_LAST             ASYNC_EVENT_CMPL_ERROR_RECOVERY_TYPE_HWRM_ASYNC_EVENT
	__le16	event_id;
	#घोषणा ASYNC_EVENT_CMPL_ERROR_RECOVERY_EVENT_ID_ERROR_RECOVERY 0x9UL
	#घोषणा ASYNC_EVENT_CMPL_ERROR_RECOVERY_EVENT_ID_LAST          ASYNC_EVENT_CMPL_ERROR_RECOVERY_EVENT_ID_ERROR_RECOVERY
	__le32	event_data2;
	u8	opaque_v;
	#घोषणा ASYNC_EVENT_CMPL_ERROR_RECOVERY_V          0x1UL
	#घोषणा ASYNC_EVENT_CMPL_ERROR_RECOVERY_OPAQUE_MASK 0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_ERROR_RECOVERY_OPAQUE_SFT 1
	u8	बारtamp_lo;
	__le16	बारtamp_hi;
	__le32	event_data1;
	#घोषणा ASYNC_EVENT_CMPL_ERROR_RECOVERY_EVENT_DATA1_FLAGS_MASK                 0xffUL
	#घोषणा ASYNC_EVENT_CMPL_ERROR_RECOVERY_EVENT_DATA1_FLAGS_SFT                  0
	#घोषणा ASYNC_EVENT_CMPL_ERROR_RECOVERY_EVENT_DATA1_FLAGS_MASTER_FUNC           0x1UL
	#घोषणा ASYNC_EVENT_CMPL_ERROR_RECOVERY_EVENT_DATA1_FLAGS_RECOVERY_ENABLED      0x2UL
पूर्ण;

/* hwrm_async_event_cmpl_ring_monitor_msg (size:128b/16B) */
काष्ठा hwrm_async_event_cmpl_ring_monitor_msg अणु
	__le16	type;
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_TYPE_MASK            0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_TYPE_SFT             0
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_TYPE_HWRM_ASYNC_EVENT  0x2eUL
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_TYPE_LAST             ASYNC_EVENT_CMPL_RING_MONITOR_MSG_TYPE_HWRM_ASYNC_EVENT
	__le16	event_id;
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_EVENT_ID_RING_MONITOR_MSG 0xaUL
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_EVENT_ID_LAST            ASYNC_EVENT_CMPL_RING_MONITOR_MSG_EVENT_ID_RING_MONITOR_MSG
	__le32	event_data2;
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_EVENT_DATA2_DISABLE_RING_TYPE_MASK 0xffUL
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_EVENT_DATA2_DISABLE_RING_TYPE_SFT 0
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_EVENT_DATA2_DISABLE_RING_TYPE_TX    0x0UL
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_EVENT_DATA2_DISABLE_RING_TYPE_RX    0x1UL
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_EVENT_DATA2_DISABLE_RING_TYPE_CMPL  0x2UL
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_EVENT_DATA2_DISABLE_RING_TYPE_LAST ASYNC_EVENT_CMPL_RING_MONITOR_MSG_EVENT_DATA2_DISABLE_RING_TYPE_CMPL
	u8	opaque_v;
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_V          0x1UL
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_OPAQUE_MASK 0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_RING_MONITOR_MSG_OPAQUE_SFT 1
	u8	बारtamp_lo;
	__le16	बारtamp_hi;
	__le32	event_data1;
पूर्ण;

/* hwrm_async_event_cmpl_vf_cfg_change (size:128b/16B) */
काष्ठा hwrm_async_event_cmpl_vf_cfg_change अणु
	__le16	type;
	#घोषणा ASYNC_EVENT_CMPL_VF_CFG_CHANGE_TYPE_MASK            0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_VF_CFG_CHANGE_TYPE_SFT             0
	#घोषणा ASYNC_EVENT_CMPL_VF_CFG_CHANGE_TYPE_HWRM_ASYNC_EVENT  0x2eUL
	#घोषणा ASYNC_EVENT_CMPL_VF_CFG_CHANGE_TYPE_LAST             ASYNC_EVENT_CMPL_VF_CFG_CHANGE_TYPE_HWRM_ASYNC_EVENT
	__le16	event_id;
	#घोषणा ASYNC_EVENT_CMPL_VF_CFG_CHANGE_EVENT_ID_VF_CFG_CHANGE 0x33UL
	#घोषणा ASYNC_EVENT_CMPL_VF_CFG_CHANGE_EVENT_ID_LAST         ASYNC_EVENT_CMPL_VF_CFG_CHANGE_EVENT_ID_VF_CFG_CHANGE
	__le32	event_data2;
	u8	opaque_v;
	#घोषणा ASYNC_EVENT_CMPL_VF_CFG_CHANGE_V          0x1UL
	#घोषणा ASYNC_EVENT_CMPL_VF_CFG_CHANGE_OPAQUE_MASK 0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_VF_CFG_CHANGE_OPAQUE_SFT 1
	u8	बारtamp_lo;
	__le16	बारtamp_hi;
	__le32	event_data1;
	#घोषणा ASYNC_EVENT_CMPL_VF_CFG_CHANGE_EVENT_DATA1_MTU_CHANGE                0x1UL
	#घोषणा ASYNC_EVENT_CMPL_VF_CFG_CHANGE_EVENT_DATA1_MRU_CHANGE                0x2UL
	#घोषणा ASYNC_EVENT_CMPL_VF_CFG_CHANGE_EVENT_DATA1_DFLT_MAC_ADDR_CHANGE      0x4UL
	#घोषणा ASYNC_EVENT_CMPL_VF_CFG_CHANGE_EVENT_DATA1_DFLT_VLAN_CHANGE          0x8UL
	#घोषणा ASYNC_EVENT_CMPL_VF_CFG_CHANGE_EVENT_DATA1_TRUSTED_VF_CFG_CHANGE     0x10UL
पूर्ण;

/* hwrm_async_event_cmpl_शेष_vnic_change (size:128b/16B) */
काष्ठा hwrm_async_event_cmpl_शेष_vnic_change अणु
	__le16	type;
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_TYPE_MASK            0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_TYPE_SFT             0
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_TYPE_HWRM_ASYNC_EVENT  0x2eUL
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_TYPE_LAST             ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_TYPE_HWRM_ASYNC_EVENT
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_UNUSED1_MASK         0xffc0UL
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_UNUSED1_SFT          6
	__le16	event_id;
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_EVENT_ID_ALLOC_FREE_NOTIFICATION 0x35UL
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_EVENT_ID_LAST                   ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_EVENT_ID_ALLOC_FREE_NOTIFICATION
	__le32	event_data2;
	u8	opaque_v;
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_V          0x1UL
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_OPAQUE_MASK 0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_OPAQUE_SFT 1
	u8	बारtamp_lo;
	__le16	बारtamp_hi;
	__le32	event_data1;
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_EVENT_DATA1_DEF_VNIC_STATE_MASK          0x3UL
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_EVENT_DATA1_DEF_VNIC_STATE_SFT           0
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_EVENT_DATA1_DEF_VNIC_STATE_DEF_VNIC_ALLOC  0x1UL
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_EVENT_DATA1_DEF_VNIC_STATE_DEF_VNIC_FREE   0x2UL
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_EVENT_DATA1_DEF_VNIC_STATE_LAST           ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_EVENT_DATA1_DEF_VNIC_STATE_DEF_VNIC_FREE
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_EVENT_DATA1_PF_ID_MASK                   0x3fcUL
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_EVENT_DATA1_PF_ID_SFT                    2
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_EVENT_DATA1_VF_ID_MASK                   0x3fffc00UL
	#घोषणा ASYNC_EVENT_CMPL_DEFAULT_VNIC_CHANGE_EVENT_DATA1_VF_ID_SFT                    10
पूर्ण;

/* hwrm_async_event_cmpl_hw_flow_aged (size:128b/16B) */
काष्ठा hwrm_async_event_cmpl_hw_flow_aged अणु
	__le16	type;
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_TYPE_MASK            0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_TYPE_SFT             0
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_TYPE_HWRM_ASYNC_EVENT  0x2eUL
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_TYPE_LAST             ASYNC_EVENT_CMPL_HW_FLOW_AGED_TYPE_HWRM_ASYNC_EVENT
	__le16	event_id;
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_EVENT_ID_HW_FLOW_AGED 0x36UL
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_EVENT_ID_LAST        ASYNC_EVENT_CMPL_HW_FLOW_AGED_EVENT_ID_HW_FLOW_AGED
	__le32	event_data2;
	u8	opaque_v;
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_V          0x1UL
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_OPAQUE_MASK 0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_OPAQUE_SFT 1
	u8	बारtamp_lo;
	__le16	बारtamp_hi;
	__le32	event_data1;
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_EVENT_DATA1_FLOW_ID_MASK       0x7fffffffUL
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_EVENT_DATA1_FLOW_ID_SFT        0
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_EVENT_DATA1_FLOW_सूचीECTION     0x80000000UL
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_EVENT_DATA1_FLOW_सूचीECTION_RX    (0x0UL << 31)
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_EVENT_DATA1_FLOW_सूचीECTION_TX    (0x1UL << 31)
	#घोषणा ASYNC_EVENT_CMPL_HW_FLOW_AGED_EVENT_DATA1_FLOW_सूचीECTION_LAST ASYNC_EVENT_CMPL_HW_FLOW_AGED_EVENT_DATA1_FLOW_सूचीECTION_TX
पूर्ण;

/* hwrm_async_event_cmpl_eem_cache_flush_req (size:128b/16B) */
काष्ठा hwrm_async_event_cmpl_eem_cache_flush_req अणु
	__le16	type;
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_REQ_TYPE_MASK            0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_REQ_TYPE_SFT             0
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_REQ_TYPE_HWRM_ASYNC_EVENT  0x2eUL
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_REQ_TYPE_LAST             ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_REQ_TYPE_HWRM_ASYNC_EVENT
	__le16	event_id;
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_REQ_EVENT_ID_EEM_CACHE_FLUSH_REQ 0x38UL
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_REQ_EVENT_ID_LAST               ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_REQ_EVENT_ID_EEM_CACHE_FLUSH_REQ
	__le32	event_data2;
	u8	opaque_v;
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_REQ_V          0x1UL
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_REQ_OPAQUE_MASK 0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_REQ_OPAQUE_SFT 1
	u8	बारtamp_lo;
	__le16	बारtamp_hi;
	__le32	event_data1;
पूर्ण;

/* hwrm_async_event_cmpl_eem_cache_flush_करोne (size:128b/16B) */
काष्ठा hwrm_async_event_cmpl_eem_cache_flush_करोne अणु
	__le16	type;
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_DONE_TYPE_MASK            0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_DONE_TYPE_SFT             0
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_DONE_TYPE_HWRM_ASYNC_EVENT  0x2eUL
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_DONE_TYPE_LAST             ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_DONE_TYPE_HWRM_ASYNC_EVENT
	__le16	event_id;
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_DONE_EVENT_ID_EEM_CACHE_FLUSH_DONE 0x39UL
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_DONE_EVENT_ID_LAST                ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_DONE_EVENT_ID_EEM_CACHE_FLUSH_DONE
	__le32	event_data2;
	u8	opaque_v;
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_DONE_V          0x1UL
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_DONE_OPAQUE_MASK 0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_DONE_OPAQUE_SFT 1
	u8	बारtamp_lo;
	__le16	बारtamp_hi;
	__le32	event_data1;
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_DONE_EVENT_DATA1_FID_MASK 0xffffUL
	#घोषणा ASYNC_EVENT_CMPL_EEM_CACHE_FLUSH_DONE_EVENT_DATA1_FID_SFT 0
पूर्ण;

/* hwrm_async_event_cmpl_deferred_response (size:128b/16B) */
काष्ठा hwrm_async_event_cmpl_deferred_response अणु
	__le16	type;
	#घोषणा ASYNC_EVENT_CMPL_DEFERRED_RESPONSE_TYPE_MASK            0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_DEFERRED_RESPONSE_TYPE_SFT             0
	#घोषणा ASYNC_EVENT_CMPL_DEFERRED_RESPONSE_TYPE_HWRM_ASYNC_EVENT  0x2eUL
	#घोषणा ASYNC_EVENT_CMPL_DEFERRED_RESPONSE_TYPE_LAST             ASYNC_EVENT_CMPL_DEFERRED_RESPONSE_TYPE_HWRM_ASYNC_EVENT
	__le16	event_id;
	#घोषणा ASYNC_EVENT_CMPL_DEFERRED_RESPONSE_EVENT_ID_DEFERRED_RESPONSE 0x40UL
	#घोषणा ASYNC_EVENT_CMPL_DEFERRED_RESPONSE_EVENT_ID_LAST             ASYNC_EVENT_CMPL_DEFERRED_RESPONSE_EVENT_ID_DEFERRED_RESPONSE
	__le32	event_data2;
	#घोषणा ASYNC_EVENT_CMPL_DEFERRED_RESPONSE_EVENT_DATA2_SEQ_ID_MASK 0xffffUL
	#घोषणा ASYNC_EVENT_CMPL_DEFERRED_RESPONSE_EVENT_DATA2_SEQ_ID_SFT 0
	u8	opaque_v;
	#घोषणा ASYNC_EVENT_CMPL_DEFERRED_RESPONSE_V          0x1UL
	#घोषणा ASYNC_EVENT_CMPL_DEFERRED_RESPONSE_OPAQUE_MASK 0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_DEFERRED_RESPONSE_OPAQUE_SFT 1
	u8	बारtamp_lo;
	__le16	बारtamp_hi;
	__le32	event_data1;
पूर्ण;

/* hwrm_async_event_cmpl_echo_request (size:128b/16B) */
काष्ठा hwrm_async_event_cmpl_echo_request अणु
	__le16	type;
	#घोषणा ASYNC_EVENT_CMPL_ECHO_REQUEST_TYPE_MASK            0x3fUL
	#घोषणा ASYNC_EVENT_CMPL_ECHO_REQUEST_TYPE_SFT             0
	#घोषणा ASYNC_EVENT_CMPL_ECHO_REQUEST_TYPE_HWRM_ASYNC_EVENT  0x2eUL
	#घोषणा ASYNC_EVENT_CMPL_ECHO_REQUEST_TYPE_LAST             ASYNC_EVENT_CMPL_ECHO_REQUEST_TYPE_HWRM_ASYNC_EVENT
	__le16	event_id;
	#घोषणा ASYNC_EVENT_CMPL_ECHO_REQUEST_EVENT_ID_ECHO_REQUEST 0x42UL
	#घोषणा ASYNC_EVENT_CMPL_ECHO_REQUEST_EVENT_ID_LAST        ASYNC_EVENT_CMPL_ECHO_REQUEST_EVENT_ID_ECHO_REQUEST
	__le32	event_data2;
	u8	opaque_v;
	#घोषणा ASYNC_EVENT_CMPL_ECHO_REQUEST_V          0x1UL
	#घोषणा ASYNC_EVENT_CMPL_ECHO_REQUEST_OPAQUE_MASK 0xfeUL
	#घोषणा ASYNC_EVENT_CMPL_ECHO_REQUEST_OPAQUE_SFT 1
	u8	बारtamp_lo;
	__le16	बारtamp_hi;
	__le32	event_data1;
पूर्ण;

/* hwrm_func_reset_input (size:192b/24B) */
काष्ठा hwrm_func_reset_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	enables;
	#घोषणा FUNC_RESET_REQ_ENABLES_VF_ID_VALID     0x1UL
	__le16	vf_id;
	u8	func_reset_level;
	#घोषणा FUNC_RESET_REQ_FUNC_RESET_LEVEL_RESETALL      0x0UL
	#घोषणा FUNC_RESET_REQ_FUNC_RESET_LEVEL_RESETME       0x1UL
	#घोषणा FUNC_RESET_REQ_FUNC_RESET_LEVEL_RESETCHILDREN 0x2UL
	#घोषणा FUNC_RESET_REQ_FUNC_RESET_LEVEL_RESETVF       0x3UL
	#घोषणा FUNC_RESET_REQ_FUNC_RESET_LEVEL_LAST         FUNC_RESET_REQ_FUNC_RESET_LEVEL_RESETVF
	u8	unused_0;
पूर्ण;

/* hwrm_func_reset_output (size:128b/16B) */
काष्ठा hwrm_func_reset_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_func_getfid_input (size:192b/24B) */
काष्ठा hwrm_func_getfid_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	enables;
	#घोषणा FUNC_GETFID_REQ_ENABLES_PCI_ID     0x1UL
	__le16	pci_id;
	u8	unused_0[2];
पूर्ण;

/* hwrm_func_getfid_output (size:128b/16B) */
काष्ठा hwrm_func_getfid_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	fid;
	u8	unused_0[5];
	u8	valid;
पूर्ण;

/* hwrm_func_vf_alloc_input (size:192b/24B) */
काष्ठा hwrm_func_vf_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	enables;
	#घोषणा FUNC_VF_ALLOC_REQ_ENABLES_FIRST_VF_ID     0x1UL
	__le16	first_vf_id;
	__le16	num_vfs;
पूर्ण;

/* hwrm_func_vf_alloc_output (size:128b/16B) */
काष्ठा hwrm_func_vf_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	first_vf_id;
	u8	unused_0[5];
	u8	valid;
पूर्ण;

/* hwrm_func_vf_मुक्त_input (size:192b/24B) */
काष्ठा hwrm_func_vf_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	enables;
	#घोषणा FUNC_VF_FREE_REQ_ENABLES_FIRST_VF_ID     0x1UL
	__le16	first_vf_id;
	__le16	num_vfs;
पूर्ण;

/* hwrm_func_vf_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_func_vf_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_func_vf_cfg_input (size:448b/56B) */
काष्ठा hwrm_func_vf_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	enables;
	#घोषणा FUNC_VF_CFG_REQ_ENABLES_MTU                  0x1UL
	#घोषणा FUNC_VF_CFG_REQ_ENABLES_GUEST_VLAN           0x2UL
	#घोषणा FUNC_VF_CFG_REQ_ENABLES_ASYNC_EVENT_CR       0x4UL
	#घोषणा FUNC_VF_CFG_REQ_ENABLES_DFLT_MAC_ADDR        0x8UL
	#घोषणा FUNC_VF_CFG_REQ_ENABLES_NUM_RSSCOS_CTXS      0x10UL
	#घोषणा FUNC_VF_CFG_REQ_ENABLES_NUM_CMPL_RINGS       0x20UL
	#घोषणा FUNC_VF_CFG_REQ_ENABLES_NUM_TX_RINGS         0x40UL
	#घोषणा FUNC_VF_CFG_REQ_ENABLES_NUM_RX_RINGS         0x80UL
	#घोषणा FUNC_VF_CFG_REQ_ENABLES_NUM_L2_CTXS          0x100UL
	#घोषणा FUNC_VF_CFG_REQ_ENABLES_NUM_VNICS            0x200UL
	#घोषणा FUNC_VF_CFG_REQ_ENABLES_NUM_STAT_CTXS        0x400UL
	#घोषणा FUNC_VF_CFG_REQ_ENABLES_NUM_HW_RING_GRPS     0x800UL
	__le16	mtu;
	__le16	guest_vlan;
	__le16	async_event_cr;
	u8	dflt_mac_addr[6];
	__le32	flags;
	#घोषणा FUNC_VF_CFG_REQ_FLAGS_TX_ASSETS_TEST             0x1UL
	#घोषणा FUNC_VF_CFG_REQ_FLAGS_RX_ASSETS_TEST             0x2UL
	#घोषणा FUNC_VF_CFG_REQ_FLAGS_CMPL_ASSETS_TEST           0x4UL
	#घोषणा FUNC_VF_CFG_REQ_FLAGS_RSSCOS_CTX_ASSETS_TEST     0x8UL
	#घोषणा FUNC_VF_CFG_REQ_FLAGS_RING_GRP_ASSETS_TEST       0x10UL
	#घोषणा FUNC_VF_CFG_REQ_FLAGS_STAT_CTX_ASSETS_TEST       0x20UL
	#घोषणा FUNC_VF_CFG_REQ_FLAGS_VNIC_ASSETS_TEST           0x40UL
	#घोषणा FUNC_VF_CFG_REQ_FLAGS_L2_CTX_ASSETS_TEST         0x80UL
	#घोषणा FUNC_VF_CFG_REQ_FLAGS_PPP_PUSH_MODE_ENABLE       0x100UL
	#घोषणा FUNC_VF_CFG_REQ_FLAGS_PPP_PUSH_MODE_DISABLE      0x200UL
	__le16	num_rsscos_ctxs;
	__le16	num_cmpl_rings;
	__le16	num_tx_rings;
	__le16	num_rx_rings;
	__le16	num_l2_ctxs;
	__le16	num_vnics;
	__le16	num_stat_ctxs;
	__le16	num_hw_ring_grps;
	u8	unused_0[4];
पूर्ण;

/* hwrm_func_vf_cfg_output (size:128b/16B) */
काष्ठा hwrm_func_vf_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_func_qcaps_input (size:192b/24B) */
काष्ठा hwrm_func_qcaps_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	fid;
	u8	unused_0[6];
पूर्ण;

/* hwrm_func_qcaps_output (size:704b/88B) */
काष्ठा hwrm_func_qcaps_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	fid;
	__le16	port_id;
	__le32	flags;
	#घोषणा FUNC_QCAPS_RESP_FLAGS_PUSH_MODE_SUPPORTED                   0x1UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_GLOBAL_MSIX_AUTOMASKING               0x2UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_PTP_SUPPORTED                         0x4UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_ROCE_V1_SUPPORTED                     0x8UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_ROCE_V2_SUPPORTED                     0x10UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_WOL_MAGICPKT_SUPPORTED                0x20UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_WOL_BMP_SUPPORTED                     0x40UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_TX_RING_RL_SUPPORTED                  0x80UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_TX_BW_CFG_SUPPORTED                   0x100UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_VF_TX_RING_RL_SUPPORTED               0x200UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_VF_BW_CFG_SUPPORTED                   0x400UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_STD_TX_RING_MODE_SUPPORTED            0x800UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_GENEVE_TUN_FLAGS_SUPPORTED            0x1000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_NVGRE_TUN_FLAGS_SUPPORTED             0x2000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_GRE_TUN_FLAGS_SUPPORTED               0x4000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_MPLS_TUN_FLAGS_SUPPORTED              0x8000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_PCIE_STATS_SUPPORTED                  0x10000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_ADOPTED_PF_SUPPORTED                  0x20000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_ADMIN_PF_SUPPORTED                    0x40000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_LINK_ADMIN_STATUS_SUPPORTED           0x80000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_WCB_PUSH_MODE                         0x100000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_DYNAMIC_TX_RING_ALLOC                 0x200000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_HOT_RESET_CAPABLE                     0x400000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_ERROR_RECOVERY_CAPABLE                0x800000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_STATS_SUPPORTED                   0x1000000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_ERR_RECOVER_RELOAD                    0x2000000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_NOTIFY_VF_DEF_VNIC_CHNG_SUPPORTED     0x4000000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_VLAN_ACCELERATION_TX_DISABLED         0x8000000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_COREDUMP_CMD_SUPPORTED                0x10000000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_CRASHDUMP_CMD_SUPPORTED               0x20000000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_PFC_WD_STATS_SUPPORTED                0x40000000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_DBG_QCAPS_CMD_SUPPORTED               0x80000000UL
	u8	mac_address[6];
	__le16	max_rsscos_ctx;
	__le16	max_cmpl_rings;
	__le16	max_tx_rings;
	__le16	max_rx_rings;
	__le16	max_l2_ctxs;
	__le16	max_vnics;
	__le16	first_vf_id;
	__le16	max_vfs;
	__le16	max_stat_ctx;
	__le32	max_encap_records;
	__le32	max_decap_records;
	__le32	max_tx_em_flows;
	__le32	max_tx_wm_flows;
	__le32	max_rx_em_flows;
	__le32	max_rx_wm_flows;
	__le32	max_mcast_filters;
	__le32	max_flow_id;
	__le32	max_hw_ring_grps;
	__le16	max_sp_tx_rings;
	u8	unused_0[2];
	__le32	flags_ext;
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_ECN_MARK_SUPPORTED                     0x1UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_ECN_STATS_SUPPORTED                    0x2UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_EXT_HW_STATS_SUPPORTED                 0x4UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_HOT_RESET_IF_SUPPORT                   0x8UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_PROXY_MODE_SUPPORT                     0x10UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_TX_PROXY_SRC_INTF_OVERRIDE_SUPPORT     0x20UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_SCHQ_SUPPORTED                         0x40UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_PPP_PUSH_MODE_SUPPORTED                0x80UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_EVB_MODE_CFG_NOT_SUPPORTED             0x100UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_SOC_SPD_SUPPORTED                      0x200UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_FW_LIVEPATCH_SUPPORTED                 0x400UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_FAST_RESET_CAPABLE                     0x800UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_TX_METADATA_CFG_CAPABLE                0x1000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_NVM_OPTION_ACTION_SUPPORTED            0x2000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_BD_METADATA_SUPPORTED                  0x4000UL
	#घोषणा FUNC_QCAPS_RESP_FLAGS_EXT_ECHO_REQUEST_SUPPORTED                 0x8000UL
	u8	max_schqs;
	u8	mpc_chnls_cap;
	#घोषणा FUNC_QCAPS_RESP_MPC_CHNLS_CAP_TCE         0x1UL
	#घोषणा FUNC_QCAPS_RESP_MPC_CHNLS_CAP_RCE         0x2UL
	#घोषणा FUNC_QCAPS_RESP_MPC_CHNLS_CAP_TE_CFA      0x4UL
	#घोषणा FUNC_QCAPS_RESP_MPC_CHNLS_CAP_RE_CFA      0x8UL
	#घोषणा FUNC_QCAPS_RESP_MPC_CHNLS_CAP_PRIMATE     0x10UL
	u8	unused_1;
	u8	valid;
पूर्ण;

/* hwrm_func_qcfg_input (size:192b/24B) */
काष्ठा hwrm_func_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	fid;
	u8	unused_0[6];
पूर्ण;

/* hwrm_func_qcfg_output (size:768b/96B) */
काष्ठा hwrm_func_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	fid;
	__le16	port_id;
	__le16	vlan;
	__le16	flags;
	#घोषणा FUNC_QCFG_RESP_FLAGS_OOB_WOL_MAGICPKT_ENABLED     0x1UL
	#घोषणा FUNC_QCFG_RESP_FLAGS_OOB_WOL_BMP_ENABLED          0x2UL
	#घोषणा FUNC_QCFG_RESP_FLAGS_FW_DCBX_AGENT_ENABLED        0x4UL
	#घोषणा FUNC_QCFG_RESP_FLAGS_STD_TX_RING_MODE_ENABLED     0x8UL
	#घोषणा FUNC_QCFG_RESP_FLAGS_FW_LLDP_AGENT_ENABLED        0x10UL
	#घोषणा FUNC_QCFG_RESP_FLAGS_MULTI_HOST                   0x20UL
	#घोषणा FUNC_QCFG_RESP_FLAGS_TRUSTED_VF                   0x40UL
	#घोषणा FUNC_QCFG_RESP_FLAGS_SECURE_MODE_ENABLED          0x80UL
	#घोषणा FUNC_QCFG_RESP_FLAGS_PREBOOT_LEGACY_L2_RINGS      0x100UL
	#घोषणा FUNC_QCFG_RESP_FLAGS_HOT_RESET_ALLOWED            0x200UL
	#घोषणा FUNC_QCFG_RESP_FLAGS_PPP_PUSH_MODE_ENABLED        0x400UL
	#घोषणा FUNC_QCFG_RESP_FLAGS_RING_MONITOR_ENABLED         0x800UL
	#घोषणा FUNC_QCFG_RESP_FLAGS_FAST_RESET_ALLOWED           0x1000UL
	#घोषणा FUNC_QCFG_RESP_FLAGS_MULTI_ROOT                   0x2000UL
	u8	mac_address[6];
	__le16	pci_id;
	__le16	alloc_rsscos_ctx;
	__le16	alloc_cmpl_rings;
	__le16	alloc_tx_rings;
	__le16	alloc_rx_rings;
	__le16	alloc_l2_ctx;
	__le16	alloc_vnics;
	__le16	mtu;
	__le16	mru;
	__le16	stat_ctx_id;
	u8	port_partition_type;
	#घोषणा FUNC_QCFG_RESP_PORT_PARTITION_TYPE_SPF     0x0UL
	#घोषणा FUNC_QCFG_RESP_PORT_PARTITION_TYPE_MPFS    0x1UL
	#घोषणा FUNC_QCFG_RESP_PORT_PARTITION_TYPE_NPAR1_0 0x2UL
	#घोषणा FUNC_QCFG_RESP_PORT_PARTITION_TYPE_NPAR1_5 0x3UL
	#घोषणा FUNC_QCFG_RESP_PORT_PARTITION_TYPE_NPAR2_0 0x4UL
	#घोषणा FUNC_QCFG_RESP_PORT_PARTITION_TYPE_UNKNOWN 0xffUL
	#घोषणा FUNC_QCFG_RESP_PORT_PARTITION_TYPE_LAST   FUNC_QCFG_RESP_PORT_PARTITION_TYPE_UNKNOWN
	u8	port_pf_cnt;
	#घोषणा FUNC_QCFG_RESP_PORT_PF_CNT_UNAVAIL 0x0UL
	#घोषणा FUNC_QCFG_RESP_PORT_PF_CNT_LAST   FUNC_QCFG_RESP_PORT_PF_CNT_UNAVAIL
	__le16	dflt_vnic_id;
	__le16	max_mtu_configured;
	__le32	min_bw;
	#घोषणा FUNC_QCFG_RESP_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा FUNC_QCFG_RESP_MIN_BW_BW_VALUE_SFT              0
	#घोषणा FUNC_QCFG_RESP_MIN_BW_SCALE                     0x10000000UL
	#घोषणा FUNC_QCFG_RESP_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा FUNC_QCFG_RESP_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा FUNC_QCFG_RESP_MIN_BW_SCALE_LAST                 FUNC_QCFG_RESP_MIN_BW_SCALE_BYTES
	#घोषणा FUNC_QCFG_RESP_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा FUNC_QCFG_RESP_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा FUNC_QCFG_RESP_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा FUNC_QCFG_RESP_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा FUNC_QCFG_RESP_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा FUNC_QCFG_RESP_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा FUNC_QCFG_RESP_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा FUNC_QCFG_RESP_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा FUNC_QCFG_RESP_MIN_BW_BW_VALUE_UNIT_LAST         FUNC_QCFG_RESP_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	max_bw;
	#घोषणा FUNC_QCFG_RESP_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा FUNC_QCFG_RESP_MAX_BW_BW_VALUE_SFT              0
	#घोषणा FUNC_QCFG_RESP_MAX_BW_SCALE                     0x10000000UL
	#घोषणा FUNC_QCFG_RESP_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा FUNC_QCFG_RESP_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा FUNC_QCFG_RESP_MAX_BW_SCALE_LAST                 FUNC_QCFG_RESP_MAX_BW_SCALE_BYTES
	#घोषणा FUNC_QCFG_RESP_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा FUNC_QCFG_RESP_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा FUNC_QCFG_RESP_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा FUNC_QCFG_RESP_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा FUNC_QCFG_RESP_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा FUNC_QCFG_RESP_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा FUNC_QCFG_RESP_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा FUNC_QCFG_RESP_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा FUNC_QCFG_RESP_MAX_BW_BW_VALUE_UNIT_LAST         FUNC_QCFG_RESP_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	evb_mode;
	#घोषणा FUNC_QCFG_RESP_EVB_MODE_NO_EVB 0x0UL
	#घोषणा FUNC_QCFG_RESP_EVB_MODE_VEB    0x1UL
	#घोषणा FUNC_QCFG_RESP_EVB_MODE_VEPA   0x2UL
	#घोषणा FUNC_QCFG_RESP_EVB_MODE_LAST  FUNC_QCFG_RESP_EVB_MODE_VEPA
	u8	options;
	#घोषणा FUNC_QCFG_RESP_OPTIONS_CACHE_LINESIZE_MASK         0x3UL
	#घोषणा FUNC_QCFG_RESP_OPTIONS_CACHE_LINESIZE_SFT          0
	#घोषणा FUNC_QCFG_RESP_OPTIONS_CACHE_LINESIZE_SIZE_64        0x0UL
	#घोषणा FUNC_QCFG_RESP_OPTIONS_CACHE_LINESIZE_SIZE_128       0x1UL
	#घोषणा FUNC_QCFG_RESP_OPTIONS_CACHE_LINESIZE_LAST          FUNC_QCFG_RESP_OPTIONS_CACHE_LINESIZE_SIZE_128
	#घोषणा FUNC_QCFG_RESP_OPTIONS_LINK_ADMIN_STATE_MASK       0xcUL
	#घोषणा FUNC_QCFG_RESP_OPTIONS_LINK_ADMIN_STATE_SFT        2
	#घोषणा FUNC_QCFG_RESP_OPTIONS_LINK_ADMIN_STATE_FORCED_DOWN  (0x0UL << 2)
	#घोषणा FUNC_QCFG_RESP_OPTIONS_LINK_ADMIN_STATE_FORCED_UP    (0x1UL << 2)
	#घोषणा FUNC_QCFG_RESP_OPTIONS_LINK_ADMIN_STATE_AUTO         (0x2UL << 2)
	#घोषणा FUNC_QCFG_RESP_OPTIONS_LINK_ADMIN_STATE_LAST        FUNC_QCFG_RESP_OPTIONS_LINK_ADMIN_STATE_AUTO
	#घोषणा FUNC_QCFG_RESP_OPTIONS_RSVD_MASK                   0xf0UL
	#घोषणा FUNC_QCFG_RESP_OPTIONS_RSVD_SFT                    4
	__le16	alloc_vfs;
	__le32	alloc_mcast_filters;
	__le32	alloc_hw_ring_grps;
	__le16	alloc_sp_tx_rings;
	__le16	alloc_stat_ctx;
	__le16	alloc_msix;
	__le16	रेजिस्टरed_vfs;
	__le16	l2_करोorbell_bar_size_kb;
	u8	unused_1;
	u8	always_1;
	__le32	reset_addr_poll;
	__le16	legacy_l2_db_size_kb;
	__le16	svअगर_info;
	#घोषणा FUNC_QCFG_RESP_SVIF_INFO_SVIF_MASK      0x7fffUL
	#घोषणा FUNC_QCFG_RESP_SVIF_INFO_SVIF_SFT       0
	#घोषणा FUNC_QCFG_RESP_SVIF_INFO_SVIF_VALID     0x8000UL
	u8	mpc_chnls;
	#घोषणा FUNC_QCFG_RESP_MPC_CHNLS_TCE_ENABLED         0x1UL
	#घोषणा FUNC_QCFG_RESP_MPC_CHNLS_RCE_ENABLED         0x2UL
	#घोषणा FUNC_QCFG_RESP_MPC_CHNLS_TE_CFA_ENABLED      0x4UL
	#घोषणा FUNC_QCFG_RESP_MPC_CHNLS_RE_CFA_ENABLED      0x8UL
	#घोषणा FUNC_QCFG_RESP_MPC_CHNLS_PRIMATE_ENABLED     0x10UL
	u8	unused_2[6];
	u8	valid;
पूर्ण;

/* hwrm_func_cfg_input (size:768b/96B) */
काष्ठा hwrm_func_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	fid;
	__le16	num_msix;
	__le32	flags;
	#घोषणा FUNC_CFG_REQ_FLAGS_SRC_MAC_ADDR_CHECK_DISABLE     0x1UL
	#घोषणा FUNC_CFG_REQ_FLAGS_SRC_MAC_ADDR_CHECK_ENABLE      0x2UL
	#घोषणा FUNC_CFG_REQ_FLAGS_RSVD_MASK                      0x1fcUL
	#घोषणा FUNC_CFG_REQ_FLAGS_RSVD_SFT                       2
	#घोषणा FUNC_CFG_REQ_FLAGS_STD_TX_RING_MODE_ENABLE        0x200UL
	#घोषणा FUNC_CFG_REQ_FLAGS_STD_TX_RING_MODE_DISABLE       0x400UL
	#घोषणा FUNC_CFG_REQ_FLAGS_VIRT_MAC_PERSIST               0x800UL
	#घोषणा FUNC_CFG_REQ_FLAGS_NO_AUTOCLEAR_STATISTIC         0x1000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_TX_ASSETS_TEST                 0x2000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_RX_ASSETS_TEST                 0x4000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_CMPL_ASSETS_TEST               0x8000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_RSSCOS_CTX_ASSETS_TEST         0x10000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_RING_GRP_ASSETS_TEST           0x20000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_STAT_CTX_ASSETS_TEST           0x40000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_VNIC_ASSETS_TEST               0x80000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_L2_CTX_ASSETS_TEST             0x100000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_TRUSTED_VF_ENABLE              0x200000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_DYNAMIC_TX_RING_ALLOC          0x400000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_NQ_ASSETS_TEST                 0x800000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_TRUSTED_VF_DISABLE             0x1000000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_PREBOOT_LEGACY_L2_RINGS        0x2000000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_HOT_RESET_IF_EN_DIS            0x4000000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_PPP_PUSH_MODE_ENABLE           0x8000000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_PPP_PUSH_MODE_DISABLE          0x10000000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_BD_METADATA_ENABLE             0x20000000UL
	#घोषणा FUNC_CFG_REQ_FLAGS_BD_METADATA_DISABLE            0x40000000UL
	__le32	enables;
	#घोषणा FUNC_CFG_REQ_ENABLES_MTU                      0x1UL
	#घोषणा FUNC_CFG_REQ_ENABLES_MRU                      0x2UL
	#घोषणा FUNC_CFG_REQ_ENABLES_NUM_RSSCOS_CTXS          0x4UL
	#घोषणा FUNC_CFG_REQ_ENABLES_NUM_CMPL_RINGS           0x8UL
	#घोषणा FUNC_CFG_REQ_ENABLES_NUM_TX_RINGS             0x10UL
	#घोषणा FUNC_CFG_REQ_ENABLES_NUM_RX_RINGS             0x20UL
	#घोषणा FUNC_CFG_REQ_ENABLES_NUM_L2_CTXS              0x40UL
	#घोषणा FUNC_CFG_REQ_ENABLES_NUM_VNICS                0x80UL
	#घोषणा FUNC_CFG_REQ_ENABLES_NUM_STAT_CTXS            0x100UL
	#घोषणा FUNC_CFG_REQ_ENABLES_DFLT_MAC_ADDR            0x200UL
	#घोषणा FUNC_CFG_REQ_ENABLES_DFLT_VLAN                0x400UL
	#घोषणा FUNC_CFG_REQ_ENABLES_DFLT_IP_ADDR             0x800UL
	#घोषणा FUNC_CFG_REQ_ENABLES_MIN_BW                   0x1000UL
	#घोषणा FUNC_CFG_REQ_ENABLES_MAX_BW                   0x2000UL
	#घोषणा FUNC_CFG_REQ_ENABLES_ASYNC_EVENT_CR           0x4000UL
	#घोषणा FUNC_CFG_REQ_ENABLES_VLAN_ANTISPOOF_MODE      0x8000UL
	#घोषणा FUNC_CFG_REQ_ENABLES_ALLOWED_VLAN_PRIS        0x10000UL
	#घोषणा FUNC_CFG_REQ_ENABLES_EVB_MODE                 0x20000UL
	#घोषणा FUNC_CFG_REQ_ENABLES_NUM_MCAST_FILTERS        0x40000UL
	#घोषणा FUNC_CFG_REQ_ENABLES_NUM_HW_RING_GRPS         0x80000UL
	#घोषणा FUNC_CFG_REQ_ENABLES_CACHE_LINESIZE           0x100000UL
	#घोषणा FUNC_CFG_REQ_ENABLES_NUM_MSIX                 0x200000UL
	#घोषणा FUNC_CFG_REQ_ENABLES_ADMIN_LINK_STATE         0x400000UL
	#घोषणा FUNC_CFG_REQ_ENABLES_HOT_RESET_IF_SUPPORT     0x800000UL
	#घोषणा FUNC_CFG_REQ_ENABLES_SCHQ_ID                  0x1000000UL
	#घोषणा FUNC_CFG_REQ_ENABLES_MPC_CHNLS                0x2000000UL
	__le16	mtu;
	__le16	mru;
	__le16	num_rsscos_ctxs;
	__le16	num_cmpl_rings;
	__le16	num_tx_rings;
	__le16	num_rx_rings;
	__le16	num_l2_ctxs;
	__le16	num_vnics;
	__le16	num_stat_ctxs;
	__le16	num_hw_ring_grps;
	u8	dflt_mac_addr[6];
	__le16	dflt_vlan;
	__be32	dflt_ip_addr[4];
	__le32	min_bw;
	#घोषणा FUNC_CFG_REQ_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा FUNC_CFG_REQ_MIN_BW_BW_VALUE_SFT              0
	#घोषणा FUNC_CFG_REQ_MIN_BW_SCALE                     0x10000000UL
	#घोषणा FUNC_CFG_REQ_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा FUNC_CFG_REQ_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा FUNC_CFG_REQ_MIN_BW_SCALE_LAST                 FUNC_CFG_REQ_MIN_BW_SCALE_BYTES
	#घोषणा FUNC_CFG_REQ_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा FUNC_CFG_REQ_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा FUNC_CFG_REQ_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा FUNC_CFG_REQ_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा FUNC_CFG_REQ_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा FUNC_CFG_REQ_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा FUNC_CFG_REQ_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा FUNC_CFG_REQ_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा FUNC_CFG_REQ_MIN_BW_BW_VALUE_UNIT_LAST         FUNC_CFG_REQ_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	max_bw;
	#घोषणा FUNC_CFG_REQ_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा FUNC_CFG_REQ_MAX_BW_BW_VALUE_SFT              0
	#घोषणा FUNC_CFG_REQ_MAX_BW_SCALE                     0x10000000UL
	#घोषणा FUNC_CFG_REQ_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा FUNC_CFG_REQ_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा FUNC_CFG_REQ_MAX_BW_SCALE_LAST                 FUNC_CFG_REQ_MAX_BW_SCALE_BYTES
	#घोषणा FUNC_CFG_REQ_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा FUNC_CFG_REQ_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा FUNC_CFG_REQ_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा FUNC_CFG_REQ_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा FUNC_CFG_REQ_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा FUNC_CFG_REQ_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा FUNC_CFG_REQ_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा FUNC_CFG_REQ_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा FUNC_CFG_REQ_MAX_BW_BW_VALUE_UNIT_LAST         FUNC_CFG_REQ_MAX_BW_BW_VALUE_UNIT_INVALID
	__le16	async_event_cr;
	u8	vlan_antispoof_mode;
	#घोषणा FUNC_CFG_REQ_VLAN_ANTISPOOF_MODE_NOCHECK                 0x0UL
	#घोषणा FUNC_CFG_REQ_VLAN_ANTISPOOF_MODE_VALIDATE_VLAN           0x1UL
	#घोषणा FUNC_CFG_REQ_VLAN_ANTISPOOF_MODE_INSERT_IF_VLANDNE       0x2UL
	#घोषणा FUNC_CFG_REQ_VLAN_ANTISPOOF_MODE_INSERT_OR_OVERRIDE_VLAN 0x3UL
	#घोषणा FUNC_CFG_REQ_VLAN_ANTISPOOF_MODE_LAST                   FUNC_CFG_REQ_VLAN_ANTISPOOF_MODE_INSERT_OR_OVERRIDE_VLAN
	u8	allowed_vlan_pris;
	u8	evb_mode;
	#घोषणा FUNC_CFG_REQ_EVB_MODE_NO_EVB 0x0UL
	#घोषणा FUNC_CFG_REQ_EVB_MODE_VEB    0x1UL
	#घोषणा FUNC_CFG_REQ_EVB_MODE_VEPA   0x2UL
	#घोषणा FUNC_CFG_REQ_EVB_MODE_LAST  FUNC_CFG_REQ_EVB_MODE_VEPA
	u8	options;
	#घोषणा FUNC_CFG_REQ_OPTIONS_CACHE_LINESIZE_MASK         0x3UL
	#घोषणा FUNC_CFG_REQ_OPTIONS_CACHE_LINESIZE_SFT          0
	#घोषणा FUNC_CFG_REQ_OPTIONS_CACHE_LINESIZE_SIZE_64        0x0UL
	#घोषणा FUNC_CFG_REQ_OPTIONS_CACHE_LINESIZE_SIZE_128       0x1UL
	#घोषणा FUNC_CFG_REQ_OPTIONS_CACHE_LINESIZE_LAST          FUNC_CFG_REQ_OPTIONS_CACHE_LINESIZE_SIZE_128
	#घोषणा FUNC_CFG_REQ_OPTIONS_LINK_ADMIN_STATE_MASK       0xcUL
	#घोषणा FUNC_CFG_REQ_OPTIONS_LINK_ADMIN_STATE_SFT        2
	#घोषणा FUNC_CFG_REQ_OPTIONS_LINK_ADMIN_STATE_FORCED_DOWN  (0x0UL << 2)
	#घोषणा FUNC_CFG_REQ_OPTIONS_LINK_ADMIN_STATE_FORCED_UP    (0x1UL << 2)
	#घोषणा FUNC_CFG_REQ_OPTIONS_LINK_ADMIN_STATE_AUTO         (0x2UL << 2)
	#घोषणा FUNC_CFG_REQ_OPTIONS_LINK_ADMIN_STATE_LAST        FUNC_CFG_REQ_OPTIONS_LINK_ADMIN_STATE_AUTO
	#घोषणा FUNC_CFG_REQ_OPTIONS_RSVD_MASK                   0xf0UL
	#घोषणा FUNC_CFG_REQ_OPTIONS_RSVD_SFT                    4
	__le16	num_mcast_filters;
	__le16	schq_id;
	__le16	mpc_chnls;
	#घोषणा FUNC_CFG_REQ_MPC_CHNLS_TCE_ENABLE          0x1UL
	#घोषणा FUNC_CFG_REQ_MPC_CHNLS_TCE_DISABLE         0x2UL
	#घोषणा FUNC_CFG_REQ_MPC_CHNLS_RCE_ENABLE          0x4UL
	#घोषणा FUNC_CFG_REQ_MPC_CHNLS_RCE_DISABLE         0x8UL
	#घोषणा FUNC_CFG_REQ_MPC_CHNLS_TE_CFA_ENABLE       0x10UL
	#घोषणा FUNC_CFG_REQ_MPC_CHNLS_TE_CFA_DISABLE      0x20UL
	#घोषणा FUNC_CFG_REQ_MPC_CHNLS_RE_CFA_ENABLE       0x40UL
	#घोषणा FUNC_CFG_REQ_MPC_CHNLS_RE_CFA_DISABLE      0x80UL
	#घोषणा FUNC_CFG_REQ_MPC_CHNLS_PRIMATE_ENABLE      0x100UL
	#घोषणा FUNC_CFG_REQ_MPC_CHNLS_PRIMATE_DISABLE     0x200UL
	u8	unused_0[4];
पूर्ण;

/* hwrm_func_cfg_output (size:128b/16B) */
काष्ठा hwrm_func_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_func_qstats_input (size:192b/24B) */
काष्ठा hwrm_func_qstats_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	fid;
	u8	flags;
	#घोषणा FUNC_QSTATS_REQ_FLAGS_UNUSED       0x0UL
	#घोषणा FUNC_QSTATS_REQ_FLAGS_ROCE_ONLY    0x1UL
	#घोषणा FUNC_QSTATS_REQ_FLAGS_COUNTER_MASK 0x2UL
	#घोषणा FUNC_QSTATS_REQ_FLAGS_LAST        FUNC_QSTATS_REQ_FLAGS_COUNTER_MASK
	u8	unused_0[5];
पूर्ण;

/* hwrm_func_qstats_output (size:1408b/176B) */
काष्ठा hwrm_func_qstats_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le64	tx_ucast_pkts;
	__le64	tx_mcast_pkts;
	__le64	tx_bcast_pkts;
	__le64	tx_discard_pkts;
	__le64	tx_drop_pkts;
	__le64	tx_ucast_bytes;
	__le64	tx_mcast_bytes;
	__le64	tx_bcast_bytes;
	__le64	rx_ucast_pkts;
	__le64	rx_mcast_pkts;
	__le64	rx_bcast_pkts;
	__le64	rx_discard_pkts;
	__le64	rx_drop_pkts;
	__le64	rx_ucast_bytes;
	__le64	rx_mcast_bytes;
	__le64	rx_bcast_bytes;
	__le64	rx_agg_pkts;
	__le64	rx_agg_bytes;
	__le64	rx_agg_events;
	__le64	rx_agg_पातs;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_func_qstats_ext_input (size:256b/32B) */
काष्ठा hwrm_func_qstats_ext_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	fid;
	u8	flags;
	#घोषणा FUNC_QSTATS_EXT_REQ_FLAGS_UNUSED       0x0UL
	#घोषणा FUNC_QSTATS_EXT_REQ_FLAGS_ROCE_ONLY    0x1UL
	#घोषणा FUNC_QSTATS_EXT_REQ_FLAGS_COUNTER_MASK 0x2UL
	#घोषणा FUNC_QSTATS_EXT_REQ_FLAGS_LAST        FUNC_QSTATS_EXT_REQ_FLAGS_COUNTER_MASK
	u8	unused_0[1];
	__le32	enables;
	#घोषणा FUNC_QSTATS_EXT_REQ_ENABLES_SCHQ_ID     0x1UL
	__le16	schq_id;
	__le16	traffic_class;
	u8	unused_1[4];
पूर्ण;

/* hwrm_func_qstats_ext_output (size:1536b/192B) */
काष्ठा hwrm_func_qstats_ext_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le64	rx_ucast_pkts;
	__le64	rx_mcast_pkts;
	__le64	rx_bcast_pkts;
	__le64	rx_discard_pkts;
	__le64	rx_error_pkts;
	__le64	rx_ucast_bytes;
	__le64	rx_mcast_bytes;
	__le64	rx_bcast_bytes;
	__le64	tx_ucast_pkts;
	__le64	tx_mcast_pkts;
	__le64	tx_bcast_pkts;
	__le64	tx_error_pkts;
	__le64	tx_discard_pkts;
	__le64	tx_ucast_bytes;
	__le64	tx_mcast_bytes;
	__le64	tx_bcast_bytes;
	__le64	rx_tpa_eligible_pkt;
	__le64	rx_tpa_eligible_bytes;
	__le64	rx_tpa_pkt;
	__le64	rx_tpa_bytes;
	__le64	rx_tpa_errors;
	__le64	rx_tpa_events;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_func_clr_stats_input (size:192b/24B) */
काष्ठा hwrm_func_clr_stats_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	fid;
	u8	unused_0[6];
पूर्ण;

/* hwrm_func_clr_stats_output (size:128b/16B) */
काष्ठा hwrm_func_clr_stats_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_func_vf_resc_मुक्त_input (size:192b/24B) */
काष्ठा hwrm_func_vf_resc_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	vf_id;
	u8	unused_0[6];
पूर्ण;

/* hwrm_func_vf_resc_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_func_vf_resc_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_func_drv_rgtr_input (size:896b/112B) */
काष्ठा hwrm_func_drv_rgtr_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा FUNC_DRV_RGTR_REQ_FLAGS_FWD_ALL_MODE               0x1UL
	#घोषणा FUNC_DRV_RGTR_REQ_FLAGS_FWD_NONE_MODE              0x2UL
	#घोषणा FUNC_DRV_RGTR_REQ_FLAGS_16BIT_VER_MODE             0x4UL
	#घोषणा FUNC_DRV_RGTR_REQ_FLAGS_FLOW_HANDLE_64BIT_MODE     0x8UL
	#घोषणा FUNC_DRV_RGTR_REQ_FLAGS_HOT_RESET_SUPPORT          0x10UL
	#घोषणा FUNC_DRV_RGTR_REQ_FLAGS_ERROR_RECOVERY_SUPPORT     0x20UL
	#घोषणा FUNC_DRV_RGTR_REQ_FLAGS_MASTER_SUPPORT             0x40UL
	#घोषणा FUNC_DRV_RGTR_REQ_FLAGS_FAST_RESET_SUPPORT         0x80UL
	__le32	enables;
	#घोषणा FUNC_DRV_RGTR_REQ_ENABLES_OS_TYPE             0x1UL
	#घोषणा FUNC_DRV_RGTR_REQ_ENABLES_VER                 0x2UL
	#घोषणा FUNC_DRV_RGTR_REQ_ENABLES_TIMESTAMP           0x4UL
	#घोषणा FUNC_DRV_RGTR_REQ_ENABLES_VF_REQ_FWD          0x8UL
	#घोषणा FUNC_DRV_RGTR_REQ_ENABLES_ASYNC_EVENT_FWD     0x10UL
	__le16	os_type;
	#घोषणा FUNC_DRV_RGTR_REQ_OS_TYPE_UNKNOWN   0x0UL
	#घोषणा FUNC_DRV_RGTR_REQ_OS_TYPE_OTHER     0x1UL
	#घोषणा FUNC_DRV_RGTR_REQ_OS_TYPE_MSDOS     0xeUL
	#घोषणा FUNC_DRV_RGTR_REQ_OS_TYPE_WINDOWS   0x12UL
	#घोषणा FUNC_DRV_RGTR_REQ_OS_TYPE_SOLARIS   0x1dUL
	#घोषणा FUNC_DRV_RGTR_REQ_OS_TYPE_LINUX     0x24UL
	#घोषणा FUNC_DRV_RGTR_REQ_OS_TYPE_FREEBSD   0x2aUL
	#घोषणा FUNC_DRV_RGTR_REQ_OS_TYPE_ESXI      0x68UL
	#घोषणा FUNC_DRV_RGTR_REQ_OS_TYPE_WIN864    0x73UL
	#घोषणा FUNC_DRV_RGTR_REQ_OS_TYPE_WIN2012R2 0x74UL
	#घोषणा FUNC_DRV_RGTR_REQ_OS_TYPE_UEFI      0x8000UL
	#घोषणा FUNC_DRV_RGTR_REQ_OS_TYPE_LAST     FUNC_DRV_RGTR_REQ_OS_TYPE_UEFI
	u8	ver_maj_8b;
	u8	ver_min_8b;
	u8	ver_upd_8b;
	u8	unused_0[3];
	__le32	बारtamp;
	u8	unused_1[4];
	__le32	vf_req_fwd[8];
	__le32	async_event_fwd[8];
	__le16	ver_maj;
	__le16	ver_min;
	__le16	ver_upd;
	__le16	ver_patch;
पूर्ण;

/* hwrm_func_drv_rgtr_output (size:128b/16B) */
काष्ठा hwrm_func_drv_rgtr_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	flags;
	#घोषणा FUNC_DRV_RGTR_RESP_FLAGS_IF_CHANGE_SUPPORTED     0x1UL
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_func_drv_unrgtr_input (size:192b/24B) */
काष्ठा hwrm_func_drv_unrgtr_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा FUNC_DRV_UNRGTR_REQ_FLAGS_PREPARE_FOR_SHUTDOWN     0x1UL
	u8	unused_0[4];
पूर्ण;

/* hwrm_func_drv_unrgtr_output (size:128b/16B) */
काष्ठा hwrm_func_drv_unrgtr_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_func_buf_rgtr_input (size:1024b/128B) */
काष्ठा hwrm_func_buf_rgtr_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	enables;
	#घोषणा FUNC_BUF_RGTR_REQ_ENABLES_VF_ID            0x1UL
	#घोषणा FUNC_BUF_RGTR_REQ_ENABLES_ERR_BUF_ADDR     0x2UL
	__le16	vf_id;
	__le16	req_buf_num_pages;
	__le16	req_buf_page_size;
	#घोषणा FUNC_BUF_RGTR_REQ_REQ_BUF_PAGE_SIZE_16B 0x4UL
	#घोषणा FUNC_BUF_RGTR_REQ_REQ_BUF_PAGE_SIZE_4K  0xcUL
	#घोषणा FUNC_BUF_RGTR_REQ_REQ_BUF_PAGE_SIZE_8K  0xdUL
	#घोषणा FUNC_BUF_RGTR_REQ_REQ_BUF_PAGE_SIZE_64K 0x10UL
	#घोषणा FUNC_BUF_RGTR_REQ_REQ_BUF_PAGE_SIZE_2M  0x15UL
	#घोषणा FUNC_BUF_RGTR_REQ_REQ_BUF_PAGE_SIZE_4M  0x16UL
	#घोषणा FUNC_BUF_RGTR_REQ_REQ_BUF_PAGE_SIZE_1G  0x1eUL
	#घोषणा FUNC_BUF_RGTR_REQ_REQ_BUF_PAGE_SIZE_LAST FUNC_BUF_RGTR_REQ_REQ_BUF_PAGE_SIZE_1G
	__le16	req_buf_len;
	__le16	resp_buf_len;
	u8	unused_0[2];
	__le64	req_buf_page_addr0;
	__le64	req_buf_page_addr1;
	__le64	req_buf_page_addr2;
	__le64	req_buf_page_addr3;
	__le64	req_buf_page_addr4;
	__le64	req_buf_page_addr5;
	__le64	req_buf_page_addr6;
	__le64	req_buf_page_addr7;
	__le64	req_buf_page_addr8;
	__le64	req_buf_page_addr9;
	__le64	error_buf_addr;
	__le64	resp_buf_addr;
पूर्ण;

/* hwrm_func_buf_rgtr_output (size:128b/16B) */
काष्ठा hwrm_func_buf_rgtr_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_func_drv_qver_input (size:192b/24B) */
काष्ठा hwrm_func_drv_qver_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	reserved;
	__le16	fid;
	u8	unused_0[2];
पूर्ण;

/* hwrm_func_drv_qver_output (size:256b/32B) */
काष्ठा hwrm_func_drv_qver_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	os_type;
	#घोषणा FUNC_DRV_QVER_RESP_OS_TYPE_UNKNOWN   0x0UL
	#घोषणा FUNC_DRV_QVER_RESP_OS_TYPE_OTHER     0x1UL
	#घोषणा FUNC_DRV_QVER_RESP_OS_TYPE_MSDOS     0xeUL
	#घोषणा FUNC_DRV_QVER_RESP_OS_TYPE_WINDOWS   0x12UL
	#घोषणा FUNC_DRV_QVER_RESP_OS_TYPE_SOLARIS   0x1dUL
	#घोषणा FUNC_DRV_QVER_RESP_OS_TYPE_LINUX     0x24UL
	#घोषणा FUNC_DRV_QVER_RESP_OS_TYPE_FREEBSD   0x2aUL
	#घोषणा FUNC_DRV_QVER_RESP_OS_TYPE_ESXI      0x68UL
	#घोषणा FUNC_DRV_QVER_RESP_OS_TYPE_WIN864    0x73UL
	#घोषणा FUNC_DRV_QVER_RESP_OS_TYPE_WIN2012R2 0x74UL
	#घोषणा FUNC_DRV_QVER_RESP_OS_TYPE_UEFI      0x8000UL
	#घोषणा FUNC_DRV_QVER_RESP_OS_TYPE_LAST     FUNC_DRV_QVER_RESP_OS_TYPE_UEFI
	u8	ver_maj_8b;
	u8	ver_min_8b;
	u8	ver_upd_8b;
	u8	unused_0[3];
	__le16	ver_maj;
	__le16	ver_min;
	__le16	ver_upd;
	__le16	ver_patch;
	u8	unused_1[7];
	u8	valid;
पूर्ण;

/* hwrm_func_resource_qcaps_input (size:192b/24B) */
काष्ठा hwrm_func_resource_qcaps_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	fid;
	u8	unused_0[6];
पूर्ण;

/* hwrm_func_resource_qcaps_output (size:448b/56B) */
काष्ठा hwrm_func_resource_qcaps_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	max_vfs;
	__le16	max_msix;
	__le16	vf_reservation_strategy;
	#घोषणा FUNC_RESOURCE_QCAPS_RESP_VF_RESERVATION_STRATEGY_MAXIMAL        0x0UL
	#घोषणा FUNC_RESOURCE_QCAPS_RESP_VF_RESERVATION_STRATEGY_MINIMAL        0x1UL
	#घोषणा FUNC_RESOURCE_QCAPS_RESP_VF_RESERVATION_STRATEGY_MINIMAL_STATIC 0x2UL
	#घोषणा FUNC_RESOURCE_QCAPS_RESP_VF_RESERVATION_STRATEGY_LAST          FUNC_RESOURCE_QCAPS_RESP_VF_RESERVATION_STRATEGY_MINIMAL_STATIC
	__le16	min_rsscos_ctx;
	__le16	max_rsscos_ctx;
	__le16	min_cmpl_rings;
	__le16	max_cmpl_rings;
	__le16	min_tx_rings;
	__le16	max_tx_rings;
	__le16	min_rx_rings;
	__le16	max_rx_rings;
	__le16	min_l2_ctxs;
	__le16	max_l2_ctxs;
	__le16	min_vnics;
	__le16	max_vnics;
	__le16	min_stat_ctx;
	__le16	max_stat_ctx;
	__le16	min_hw_ring_grps;
	__le16	max_hw_ring_grps;
	__le16	max_tx_scheduler_inमाला_दो;
	__le16	flags;
	#घोषणा FUNC_RESOURCE_QCAPS_RESP_FLAGS_MIN_GUARANTEED     0x1UL
	u8	unused_0[5];
	u8	valid;
पूर्ण;

/* hwrm_func_vf_resource_cfg_input (size:448b/56B) */
काष्ठा hwrm_func_vf_resource_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	vf_id;
	__le16	max_msix;
	__le16	min_rsscos_ctx;
	__le16	max_rsscos_ctx;
	__le16	min_cmpl_rings;
	__le16	max_cmpl_rings;
	__le16	min_tx_rings;
	__le16	max_tx_rings;
	__le16	min_rx_rings;
	__le16	max_rx_rings;
	__le16	min_l2_ctxs;
	__le16	max_l2_ctxs;
	__le16	min_vnics;
	__le16	max_vnics;
	__le16	min_stat_ctx;
	__le16	max_stat_ctx;
	__le16	min_hw_ring_grps;
	__le16	max_hw_ring_grps;
	__le16	flags;
	#घोषणा FUNC_VF_RESOURCE_CFG_REQ_FLAGS_MIN_GUARANTEED     0x1UL
	u8	unused_0[2];
पूर्ण;

/* hwrm_func_vf_resource_cfg_output (size:256b/32B) */
काष्ठा hwrm_func_vf_resource_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	reserved_rsscos_ctx;
	__le16	reserved_cmpl_rings;
	__le16	reserved_tx_rings;
	__le16	reserved_rx_rings;
	__le16	reserved_l2_ctxs;
	__le16	reserved_vnics;
	__le16	reserved_stat_ctx;
	__le16	reserved_hw_ring_grps;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_func_backing_store_qcaps_input (size:128b/16B) */
काष्ठा hwrm_func_backing_store_qcaps_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
पूर्ण;

/* hwrm_func_backing_store_qcaps_output (size:704b/88B) */
काष्ठा hwrm_func_backing_store_qcaps_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	qp_max_entries;
	__le16	qp_min_qp1_entries;
	__le16	qp_max_l2_entries;
	__le16	qp_entry_size;
	__le16	srq_max_l2_entries;
	__le32	srq_max_entries;
	__le16	srq_entry_size;
	__le16	cq_max_l2_entries;
	__le32	cq_max_entries;
	__le16	cq_entry_size;
	__le16	vnic_max_vnic_entries;
	__le16	vnic_max_ring_table_entries;
	__le16	vnic_entry_size;
	__le32	stat_max_entries;
	__le16	stat_entry_size;
	__le16	tqm_entry_size;
	__le32	tqm_min_entries_per_ring;
	__le32	tqm_max_entries_per_ring;
	__le32	mrav_max_entries;
	__le16	mrav_entry_size;
	__le16	tim_entry_size;
	__le32	tim_max_entries;
	__le16	mrav_num_entries_units;
	u8	tqm_entries_multiple;
	u8	ctx_kind_initializer;
	__le16	ctx_init_mask;
	#घोषणा FUNC_BACKING_STORE_QCAPS_RESP_CTX_INIT_MASK_QP       0x1UL
	#घोषणा FUNC_BACKING_STORE_QCAPS_RESP_CTX_INIT_MASK_SRQ      0x2UL
	#घोषणा FUNC_BACKING_STORE_QCAPS_RESP_CTX_INIT_MASK_CQ       0x4UL
	#घोषणा FUNC_BACKING_STORE_QCAPS_RESP_CTX_INIT_MASK_VNIC     0x8UL
	#घोषणा FUNC_BACKING_STORE_QCAPS_RESP_CTX_INIT_MASK_STAT     0x10UL
	#घोषणा FUNC_BACKING_STORE_QCAPS_RESP_CTX_INIT_MASK_MRAV     0x20UL
	u8	qp_init_offset;
	u8	srq_init_offset;
	u8	cq_init_offset;
	u8	vnic_init_offset;
	u8	tqm_fp_rings_count;
	u8	stat_init_offset;
	u8	mrav_init_offset;
	u8	tqm_fp_rings_count_ext;
	u8	rsvd[5];
	u8	valid;
पूर्ण;

/* tqm_fp_ring_cfg (size:128b/16B) */
काष्ठा tqm_fp_ring_cfg अणु
	u8	tqm_ring_pg_माप_प्रकारqm_ring_lvl;
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_LVL_MASK      0xfUL
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_LVL_SFT       0
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_LVL_LVL_0       0x0UL
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_LVL_LVL_1       0x1UL
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_LVL_LVL_2       0x2UL
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_LVL_LAST       TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_LVL_LVL_2
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_PG_SIZE_MASK  0xf0UL
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_PG_SIZE_SFT   4
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_PG_SIZE_LAST   TQM_FP_RING_CFG_TQM_RING_CFG_TQM_RING_PG_SIZE_PG_1G
	u8	unused[3];
	__le32	tqm_ring_num_entries;
	__le64	tqm_ring_page_dir;
पूर्ण;

/* hwrm_func_backing_store_cfg_input (size:2432b/304B) */
काष्ठा hwrm_func_backing_store_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_FLAGS_PREBOOT_MODE               0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_FLAGS_MRAV_RESERVATION_SPLIT     0x2UL
	__le32	enables;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_QP             0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_SRQ            0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_CQ             0x4UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_VNIC           0x8UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_STAT           0x10UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_SP         0x20UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_RING0      0x40UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_RING1      0x80UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_RING2      0x100UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_RING3      0x200UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_RING4      0x400UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_RING5      0x800UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_RING6      0x1000UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_RING7      0x2000UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_MRAV           0x4000UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_TIM            0x8000UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_RING8      0x10000UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_RING9      0x20000UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_RING10     0x40000UL
	u8	qpc_pg_size_qpc_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_QPC_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_QPC_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_QPC_PG_SIZE_PG_1G
	u8	srq_pg_size_srq_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_SRQ_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_SRQ_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_SRQ_PG_SIZE_PG_1G
	u8	cq_pg_size_cq_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_CQ_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_CQ_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_CQ_PG_SIZE_PG_1G
	u8	vnic_pg_size_vnic_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_VNIC_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_VNIC_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_VNIC_PG_SIZE_PG_1G
	u8	stat_pg_size_stat_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_STAT_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_STAT_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_STAT_PG_SIZE_PG_1G
	u8	tqm_sp_pg_माप_प्रकारqm_sp_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_TQM_SP_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_SP_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_TQM_SP_PG_SIZE_PG_1G
	u8	tqm_ring0_pg_माप_प्रकारqm_ring0_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_TQM_RING0_PG_SIZE_PG_1G
	u8	tqm_ring1_pg_माप_प्रकारqm_ring1_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_TQM_RING1_PG_SIZE_PG_1G
	u8	tqm_ring2_pg_माप_प्रकारqm_ring2_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_TQM_RING2_PG_SIZE_PG_1G
	u8	tqm_ring3_pg_माप_प्रकारqm_ring3_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_TQM_RING3_PG_SIZE_PG_1G
	u8	tqm_ring4_pg_माप_प्रकारqm_ring4_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_TQM_RING4_PG_SIZE_PG_1G
	u8	tqm_ring5_pg_माप_प्रकारqm_ring5_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_TQM_RING5_PG_SIZE_PG_1G
	u8	tqm_ring6_pg_माप_प्रकारqm_ring6_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_TQM_RING6_PG_SIZE_PG_1G
	u8	tqm_ring7_pg_माप_प्रकारqm_ring7_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_TQM_RING7_PG_SIZE_PG_1G
	u8	mrav_pg_size_mrav_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_MRAV_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_MRAV_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_MRAV_PG_SIZE_PG_1G
	u8	tim_pg_माप_प्रकारim_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_TIM_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_TIM_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_TIM_PG_SIZE_PG_1G
	__le64	qpc_page_dir;
	__le64	srq_page_dir;
	__le64	cq_page_dir;
	__le64	vnic_page_dir;
	__le64	stat_page_dir;
	__le64	tqm_sp_page_dir;
	__le64	tqm_ring0_page_dir;
	__le64	tqm_ring1_page_dir;
	__le64	tqm_ring2_page_dir;
	__le64	tqm_ring3_page_dir;
	__le64	tqm_ring4_page_dir;
	__le64	tqm_ring5_page_dir;
	__le64	tqm_ring6_page_dir;
	__le64	tqm_ring7_page_dir;
	__le64	mrav_page_dir;
	__le64	tim_page_dir;
	__le32	qp_num_entries;
	__le32	srq_num_entries;
	__le32	cq_num_entries;
	__le32	stat_num_entries;
	__le32	tqm_sp_num_entries;
	__le32	tqm_ring0_num_entries;
	__le32	tqm_ring1_num_entries;
	__le32	tqm_ring2_num_entries;
	__le32	tqm_ring3_num_entries;
	__le32	tqm_ring4_num_entries;
	__le32	tqm_ring5_num_entries;
	__le32	tqm_ring6_num_entries;
	__le32	tqm_ring7_num_entries;
	__le32	mrav_num_entries;
	__le32	tim_num_entries;
	__le16	qp_num_qp1_entries;
	__le16	qp_num_l2_entries;
	__le16	qp_entry_size;
	__le16	srq_num_l2_entries;
	__le16	srq_entry_size;
	__le16	cq_num_l2_entries;
	__le16	cq_entry_size;
	__le16	vnic_num_vnic_entries;
	__le16	vnic_num_ring_table_entries;
	__le16	vnic_entry_size;
	__le16	stat_entry_size;
	__le16	tqm_entry_size;
	__le16	mrav_entry_size;
	__le16	tim_entry_size;
	u8	tqm_ring8_pg_माप_प्रकारqm_ring_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_RING8_TQM_RING_PG_SIZE_PG_1G
	u8	ring8_unused[3];
	__le32	tqm_ring8_num_entries;
	__le64	tqm_ring8_page_dir;
	u8	tqm_ring9_pg_माप_प्रकारqm_ring_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_RING9_TQM_RING_PG_SIZE_PG_1G
	u8	ring9_unused[3];
	__le32	tqm_ring9_num_entries;
	__le64	tqm_ring9_page_dir;
	u8	tqm_ring10_pg_माप_प्रकारqm_ring_lvl;
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_LVL_MASK      0xfUL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_LVL_SFT       0
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_LVL_LVL_0       0x0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_LVL_LVL_1       0x1UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_LVL_LVL_2       0x2UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_LVL_LAST       FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_LVL_LVL_2
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_PG_SIZE_MASK  0xf0UL
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_PG_SIZE_SFT   4
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_PG_SIZE_PG_4K   (0x0UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_PG_SIZE_PG_8K   (0x1UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_PG_SIZE_PG_64K  (0x2UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_PG_SIZE_PG_2M   (0x3UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_PG_SIZE_PG_8M   (0x4UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_PG_SIZE_PG_1G   (0x5UL << 4)
	#घोषणा FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_PG_SIZE_LAST   FUNC_BACKING_STORE_CFG_REQ_RING10_TQM_RING_PG_SIZE_PG_1G
	u8	ring10_unused[3];
	__le32	tqm_ring10_num_entries;
	__le64	tqm_ring10_page_dir;
पूर्ण;

/* hwrm_func_backing_store_cfg_output (size:128b/16B) */
काष्ठा hwrm_func_backing_store_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_error_recovery_qcfg_input (size:192b/24B) */
काष्ठा hwrm_error_recovery_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	u8	unused_0[8];
पूर्ण;

/* hwrm_error_recovery_qcfg_output (size:1664b/208B) */
काष्ठा hwrm_error_recovery_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	flags;
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FLAGS_HOST       0x1UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FLAGS_CO_CPU     0x2UL
	__le32	driver_polling_freq;
	__le32	master_func_रुको_period;
	__le32	normal_func_रुको_period;
	__le32	master_func_रुको_period_after_reset;
	__le32	max_bailout_समय_after_reset;
	__le32	fw_health_status_reg;
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEALTH_STATUS_REG_ADDR_SPACE_MASK    0x3UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEALTH_STATUS_REG_ADDR_SPACE_SFT     0
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEALTH_STATUS_REG_ADDR_SPACE_PCIE_CFG  0x0UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEALTH_STATUS_REG_ADDR_SPACE_GRC       0x1UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEALTH_STATUS_REG_ADDR_SPACE_BAR0      0x2UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEALTH_STATUS_REG_ADDR_SPACE_BAR1      0x3UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEALTH_STATUS_REG_ADDR_SPACE_LAST     ERROR_RECOVERY_QCFG_RESP_FW_HEALTH_STATUS_REG_ADDR_SPACE_BAR1
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEALTH_STATUS_REG_ADDR_MASK          0xfffffffcUL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEALTH_STATUS_REG_ADDR_SFT           2
	__le32	fw_heartbeat_reg;
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEARTBEAT_REG_ADDR_SPACE_MASK    0x3UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEARTBEAT_REG_ADDR_SPACE_SFT     0
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEARTBEAT_REG_ADDR_SPACE_PCIE_CFG  0x0UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEARTBEAT_REG_ADDR_SPACE_GRC       0x1UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEARTBEAT_REG_ADDR_SPACE_BAR0      0x2UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEARTBEAT_REG_ADDR_SPACE_BAR1      0x3UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEARTBEAT_REG_ADDR_SPACE_LAST     ERROR_RECOVERY_QCFG_RESP_FW_HEARTBEAT_REG_ADDR_SPACE_BAR1
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEARTBEAT_REG_ADDR_MASK          0xfffffffcUL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_HEARTBEAT_REG_ADDR_SFT           2
	__le32	fw_reset_cnt_reg;
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_RESET_CNT_REG_ADDR_SPACE_MASK    0x3UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_RESET_CNT_REG_ADDR_SPACE_SFT     0
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_RESET_CNT_REG_ADDR_SPACE_PCIE_CFG  0x0UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_RESET_CNT_REG_ADDR_SPACE_GRC       0x1UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_RESET_CNT_REG_ADDR_SPACE_BAR0      0x2UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_RESET_CNT_REG_ADDR_SPACE_BAR1      0x3UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_RESET_CNT_REG_ADDR_SPACE_LAST     ERROR_RECOVERY_QCFG_RESP_FW_RESET_CNT_REG_ADDR_SPACE_BAR1
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_RESET_CNT_REG_ADDR_MASK          0xfffffffcUL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_FW_RESET_CNT_REG_ADDR_SFT           2
	__le32	reset_inprogress_reg;
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_INPROGRESS_REG_ADDR_SPACE_MASK    0x3UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_INPROGRESS_REG_ADDR_SPACE_SFT     0
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_INPROGRESS_REG_ADDR_SPACE_PCIE_CFG  0x0UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_INPROGRESS_REG_ADDR_SPACE_GRC       0x1UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_INPROGRESS_REG_ADDR_SPACE_BAR0      0x2UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_INPROGRESS_REG_ADDR_SPACE_BAR1      0x3UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_INPROGRESS_REG_ADDR_SPACE_LAST     ERROR_RECOVERY_QCFG_RESP_RESET_INPROGRESS_REG_ADDR_SPACE_BAR1
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_INPROGRESS_REG_ADDR_MASK          0xfffffffcUL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_INPROGRESS_REG_ADDR_SFT           2
	__le32	reset_inprogress_reg_mask;
	u8	unused_0[3];
	u8	reg_array_cnt;
	__le32	reset_reg[16];
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_REG_ADDR_SPACE_MASK    0x3UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_REG_ADDR_SPACE_SFT     0
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_REG_ADDR_SPACE_PCIE_CFG  0x0UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_REG_ADDR_SPACE_GRC       0x1UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_REG_ADDR_SPACE_BAR0      0x2UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_REG_ADDR_SPACE_BAR1      0x3UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_REG_ADDR_SPACE_LAST     ERROR_RECOVERY_QCFG_RESP_RESET_REG_ADDR_SPACE_BAR1
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_REG_ADDR_MASK          0xfffffffcUL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_RESET_REG_ADDR_SFT           2
	__le32	reset_reg_val[16];
	u8	delay_after_reset[16];
	__le32	err_recovery_cnt_reg;
	#घोषणा ERROR_RECOVERY_QCFG_RESP_ERR_RECOVERY_CNT_REG_ADDR_SPACE_MASK    0x3UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_ERR_RECOVERY_CNT_REG_ADDR_SPACE_SFT     0
	#घोषणा ERROR_RECOVERY_QCFG_RESP_ERR_RECOVERY_CNT_REG_ADDR_SPACE_PCIE_CFG  0x0UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_ERR_RECOVERY_CNT_REG_ADDR_SPACE_GRC       0x1UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_ERR_RECOVERY_CNT_REG_ADDR_SPACE_BAR0      0x2UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_ERR_RECOVERY_CNT_REG_ADDR_SPACE_BAR1      0x3UL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_ERR_RECOVERY_CNT_REG_ADDR_SPACE_LAST     ERROR_RECOVERY_QCFG_RESP_ERR_RECOVERY_CNT_REG_ADDR_SPACE_BAR1
	#घोषणा ERROR_RECOVERY_QCFG_RESP_ERR_RECOVERY_CNT_REG_ADDR_MASK          0xfffffffcUL
	#घोषणा ERROR_RECOVERY_QCFG_RESP_ERR_RECOVERY_CNT_REG_ADDR_SFT           2
	u8	unused_1[3];
	u8	valid;
पूर्ण;

/* hwrm_func_echo_response_input (size:192b/24B) */
काष्ठा hwrm_func_echo_response_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	event_data1;
	__le32	event_data2;
पूर्ण;

/* hwrm_func_echo_response_output (size:128b/16B) */
काष्ठा hwrm_func_echo_response_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_func_drv_अगर_change_input (size:192b/24B) */
काष्ठा hwrm_func_drv_अगर_change_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा FUNC_DRV_IF_CHANGE_REQ_FLAGS_UP     0x1UL
	__le32	unused;
पूर्ण;

/* hwrm_func_drv_अगर_change_output (size:128b/16B) */
काष्ठा hwrm_func_drv_अगर_change_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	flags;
	#घोषणा FUNC_DRV_IF_CHANGE_RESP_FLAGS_RESC_CHANGE           0x1UL
	#घोषणा FUNC_DRV_IF_CHANGE_RESP_FLAGS_HOT_FW_RESET_DONE     0x2UL
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_port_phy_cfg_input (size:448b/56B) */
काष्ठा hwrm_port_phy_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_RESET_PHY                  0x1UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_DEPRECATED                 0x2UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FORCE                      0x4UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_RESTART_AUTONEG            0x8UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_EEE_ENABLE                 0x10UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_EEE_DISABLE                0x20UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_EEE_TX_LPI_ENABLE          0x40UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_EEE_TX_LPI_DISABLE         0x80UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FEC_AUTONEG_ENABLE         0x100UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FEC_AUTONEG_DISABLE        0x200UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FEC_CLAUSE74_ENABLE        0x400UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FEC_CLAUSE74_DISABLE       0x800UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FEC_CLAUSE91_ENABLE        0x1000UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FEC_CLAUSE91_DISABLE       0x2000UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FORCE_LINK_DWN             0x4000UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FEC_RS544_1XN_ENABLE       0x8000UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FEC_RS544_1XN_DISABLE      0x10000UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FEC_RS544_IEEE_ENABLE      0x20000UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FEC_RS544_IEEE_DISABLE     0x40000UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FEC_RS272_1XN_ENABLE       0x80000UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FEC_RS272_1XN_DISABLE      0x100000UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FEC_RS272_IEEE_ENABLE      0x200000UL
	#घोषणा PORT_PHY_CFG_REQ_FLAGS_FEC_RS272_IEEE_DISABLE     0x400000UL
	__le32	enables;
	#घोषणा PORT_PHY_CFG_REQ_ENABLES_AUTO_MODE                     0x1UL
	#घोषणा PORT_PHY_CFG_REQ_ENABLES_AUTO_DUPLEX                   0x2UL
	#घोषणा PORT_PHY_CFG_REQ_ENABLES_AUTO_PAUSE                    0x4UL
	#घोषणा PORT_PHY_CFG_REQ_ENABLES_AUTO_LINK_SPEED               0x8UL
	#घोषणा PORT_PHY_CFG_REQ_ENABLES_AUTO_LINK_SPEED_MASK          0x10UL
	#घोषणा PORT_PHY_CFG_REQ_ENABLES_WIRESPEED                     0x20UL
	#घोषणा PORT_PHY_CFG_REQ_ENABLES_LPBK                          0x40UL
	#घोषणा PORT_PHY_CFG_REQ_ENABLES_PREEMPHASIS                   0x80UL
	#घोषणा PORT_PHY_CFG_REQ_ENABLES_FORCE_PAUSE                   0x100UL
	#घोषणा PORT_PHY_CFG_REQ_ENABLES_EEE_LINK_SPEED_MASK           0x200UL
	#घोषणा PORT_PHY_CFG_REQ_ENABLES_TX_LPI_TIMER                  0x400UL
	#घोषणा PORT_PHY_CFG_REQ_ENABLES_FORCE_PAM4_LINK_SPEED         0x800UL
	#घोषणा PORT_PHY_CFG_REQ_ENABLES_AUTO_PAM4_LINK_SPEED_MASK     0x1000UL
	__le16	port_id;
	__le16	क्रमce_link_speed;
	#घोषणा PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_100MB 0x1UL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_1GB   0xaUL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_2GB   0x14UL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_2_5GB 0x19UL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_10GB  0x64UL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_20GB  0xc8UL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_25GB  0xfaUL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_40GB  0x190UL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_50GB  0x1f4UL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_100GB 0x3e8UL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_10MB  0xffffUL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_LAST PORT_PHY_CFG_REQ_FORCE_LINK_SPEED_10MB
	u8	स्वतः_mode;
	#घोषणा PORT_PHY_CFG_REQ_AUTO_MODE_NONE         0x0UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_MODE_ALL_SPEEDS   0x1UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_MODE_ONE_SPEED    0x2UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_MODE_ONE_OR_BELOW 0x3UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_MODE_SPEED_MASK   0x4UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_MODE_LAST        PORT_PHY_CFG_REQ_AUTO_MODE_SPEED_MASK
	u8	स्वतः_duplex;
	#घोषणा PORT_PHY_CFG_REQ_AUTO_DUPLEX_HALF 0x0UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_DUPLEX_FULL 0x1UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_DUPLEX_BOTH 0x2UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_DUPLEX_LAST PORT_PHY_CFG_REQ_AUTO_DUPLEX_BOTH
	u8	स्वतः_छोड़ो;
	#घोषणा PORT_PHY_CFG_REQ_AUTO_PAUSE_TX                0x1UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_PAUSE_RX                0x2UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_PAUSE_AUTONEG_PAUSE     0x4UL
	u8	unused_0;
	__le16	स्वतः_link_speed;
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_100MB 0x1UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_1GB   0xaUL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_2GB   0x14UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_2_5GB 0x19UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_10GB  0x64UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_20GB  0xc8UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_25GB  0xfaUL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_40GB  0x190UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_50GB  0x1f4UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_100GB 0x3e8UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_10MB  0xffffUL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_LAST PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_10MB
	__le16	स्वतः_link_speed_mask;
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_MASK_100MBHD     0x1UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_MASK_100MB       0x2UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_MASK_1GBHD       0x4UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_MASK_1GB         0x8UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_MASK_2GB         0x10UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_MASK_2_5GB       0x20UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_MASK_10GB        0x40UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_MASK_20GB        0x80UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_MASK_25GB        0x100UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_MASK_40GB        0x200UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_MASK_50GB        0x400UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_MASK_100GB       0x800UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_MASK_10MBHD      0x1000UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_SPEED_MASK_10MB        0x2000UL
	u8	wirespeed;
	#घोषणा PORT_PHY_CFG_REQ_WIRESPEED_OFF 0x0UL
	#घोषणा PORT_PHY_CFG_REQ_WIRESPEED_ON  0x1UL
	#घोषणा PORT_PHY_CFG_REQ_WIRESPEED_LAST PORT_PHY_CFG_REQ_WIRESPEED_ON
	u8	lpbk;
	#घोषणा PORT_PHY_CFG_REQ_LPBK_NONE     0x0UL
	#घोषणा PORT_PHY_CFG_REQ_LPBK_LOCAL    0x1UL
	#घोषणा PORT_PHY_CFG_REQ_LPBK_REMOTE   0x2UL
	#घोषणा PORT_PHY_CFG_REQ_LPBK_EXTERNAL 0x3UL
	#घोषणा PORT_PHY_CFG_REQ_LPBK_LAST    PORT_PHY_CFG_REQ_LPBK_EXTERNAL
	u8	क्रमce_छोड़ो;
	#घोषणा PORT_PHY_CFG_REQ_FORCE_PAUSE_TX     0x1UL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_PAUSE_RX     0x2UL
	u8	unused_1;
	__le32	preemphasis;
	__le16	eee_link_speed_mask;
	#घोषणा PORT_PHY_CFG_REQ_EEE_LINK_SPEED_MASK_RSVD1     0x1UL
	#घोषणा PORT_PHY_CFG_REQ_EEE_LINK_SPEED_MASK_100MB     0x2UL
	#घोषणा PORT_PHY_CFG_REQ_EEE_LINK_SPEED_MASK_RSVD2     0x4UL
	#घोषणा PORT_PHY_CFG_REQ_EEE_LINK_SPEED_MASK_1GB       0x8UL
	#घोषणा PORT_PHY_CFG_REQ_EEE_LINK_SPEED_MASK_RSVD3     0x10UL
	#घोषणा PORT_PHY_CFG_REQ_EEE_LINK_SPEED_MASK_RSVD4     0x20UL
	#घोषणा PORT_PHY_CFG_REQ_EEE_LINK_SPEED_MASK_10GB      0x40UL
	__le16	क्रमce_pam4_link_speed;
	#घोषणा PORT_PHY_CFG_REQ_FORCE_PAM4_LINK_SPEED_50GB  0x1f4UL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_PAM4_LINK_SPEED_100GB 0x3e8UL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_PAM4_LINK_SPEED_200GB 0x7d0UL
	#घोषणा PORT_PHY_CFG_REQ_FORCE_PAM4_LINK_SPEED_LAST PORT_PHY_CFG_REQ_FORCE_PAM4_LINK_SPEED_200GB
	__le32	tx_lpi_समयr;
	#घोषणा PORT_PHY_CFG_REQ_TX_LPI_TIMER_MASK 0xffffffUL
	#घोषणा PORT_PHY_CFG_REQ_TX_LPI_TIMER_SFT 0
	__le16	स्वतः_link_pam4_speed_mask;
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_PAM4_SPEED_MASK_50G      0x1UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_PAM4_SPEED_MASK_100G     0x2UL
	#घोषणा PORT_PHY_CFG_REQ_AUTO_LINK_PAM4_SPEED_MASK_200G     0x4UL
	u8	unused_2[2];
पूर्ण;

/* hwrm_port_phy_cfg_output (size:128b/16B) */
काष्ठा hwrm_port_phy_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_port_phy_cfg_cmd_err (size:64b/8B) */
काष्ठा hwrm_port_phy_cfg_cmd_err अणु
	u8	code;
	#घोषणा PORT_PHY_CFG_CMD_ERR_CODE_UNKNOWN       0x0UL
	#घोषणा PORT_PHY_CFG_CMD_ERR_CODE_ILLEGAL_SPEED 0x1UL
	#घोषणा PORT_PHY_CFG_CMD_ERR_CODE_RETRY         0x2UL
	#घोषणा PORT_PHY_CFG_CMD_ERR_CODE_LAST         PORT_PHY_CFG_CMD_ERR_CODE_RETRY
	u8	unused_0[7];
पूर्ण;

/* hwrm_port_phy_qcfg_input (size:192b/24B) */
काष्ठा hwrm_port_phy_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	port_id;
	u8	unused_0[6];
पूर्ण;

/* hwrm_port_phy_qcfg_output (size:768b/96B) */
काष्ठा hwrm_port_phy_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	link;
	#घोषणा PORT_PHY_QCFG_RESP_LINK_NO_LINK 0x0UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_SIGNAL  0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_LINK    0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_LAST   PORT_PHY_QCFG_RESP_LINK_LINK
	u8	active_fec_संकेत_mode;
	#घोषणा PORT_PHY_QCFG_RESP_SIGNAL_MODE_MASK                0xfUL
	#घोषणा PORT_PHY_QCFG_RESP_SIGNAL_MODE_SFT                 0
	#घोषणा PORT_PHY_QCFG_RESP_SIGNAL_MODE_NRZ                   0x0UL
	#घोषणा PORT_PHY_QCFG_RESP_SIGNAL_MODE_PAM4                  0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_SIGNAL_MODE_LAST                 PORT_PHY_QCFG_RESP_SIGNAL_MODE_PAM4
	#घोषणा PORT_PHY_QCFG_RESP_ACTIVE_FEC_MASK                 0xf0UL
	#घोषणा PORT_PHY_QCFG_RESP_ACTIVE_FEC_SFT                  4
	#घोषणा PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_NONE_ACTIVE        (0x0UL << 4)
	#घोषणा PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_CLAUSE74_ACTIVE    (0x1UL << 4)
	#घोषणा PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_CLAUSE91_ACTIVE    (0x2UL << 4)
	#घोषणा PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_RS544_1XN_ACTIVE   (0x3UL << 4)
	#घोषणा PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_RS544_IEEE_ACTIVE  (0x4UL << 4)
	#घोषणा PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_RS272_1XN_ACTIVE   (0x5UL << 4)
	#घोषणा PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_RS272_IEEE_ACTIVE  (0x6UL << 4)
	#घोषणा PORT_PHY_QCFG_RESP_ACTIVE_FEC_LAST                  PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_RS272_IEEE_ACTIVE
	__le16	link_speed;
	#घोषणा PORT_PHY_QCFG_RESP_LINK_SPEED_100MB 0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_SPEED_1GB   0xaUL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_SPEED_2GB   0x14UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_SPEED_2_5GB 0x19UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_SPEED_10GB  0x64UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_SPEED_20GB  0xc8UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_SPEED_25GB  0xfaUL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_SPEED_40GB  0x190UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_SPEED_50GB  0x1f4UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_SPEED_100GB 0x3e8UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_SPEED_200GB 0x7d0UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_SPEED_10MB  0xffffUL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_SPEED_LAST PORT_PHY_QCFG_RESP_LINK_SPEED_10MB
	u8	duplex_cfg;
	#घोषणा PORT_PHY_QCFG_RESP_DUPLEX_CFG_HALF 0x0UL
	#घोषणा PORT_PHY_QCFG_RESP_DUPLEX_CFG_FULL 0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_DUPLEX_CFG_LAST PORT_PHY_QCFG_RESP_DUPLEX_CFG_FULL
	u8	छोड़ो;
	#घोषणा PORT_PHY_QCFG_RESP_PAUSE_TX     0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_PAUSE_RX     0x2UL
	__le16	support_speeds;
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_100MBHD     0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_100MB       0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_1GBHD       0x4UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_1GB         0x8UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_2GB         0x10UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_2_5GB       0x20UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_10GB        0x40UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_20GB        0x80UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_25GB        0x100UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_40GB        0x200UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_50GB        0x400UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_100GB       0x800UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_10MBHD      0x1000UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_SPEEDS_10MB        0x2000UL
	__le16	क्रमce_link_speed;
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_LINK_SPEED_100MB 0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_LINK_SPEED_1GB   0xaUL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_LINK_SPEED_2GB   0x14UL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_LINK_SPEED_2_5GB 0x19UL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_LINK_SPEED_10GB  0x64UL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_LINK_SPEED_20GB  0xc8UL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_LINK_SPEED_25GB  0xfaUL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_LINK_SPEED_40GB  0x190UL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_LINK_SPEED_50GB  0x1f4UL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_LINK_SPEED_100GB 0x3e8UL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_LINK_SPEED_10MB  0xffffUL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_LINK_SPEED_LAST PORT_PHY_QCFG_RESP_FORCE_LINK_SPEED_10MB
	u8	स्वतः_mode;
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_MODE_NONE         0x0UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_MODE_ALL_SPEEDS   0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_MODE_ONE_SPEED    0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_MODE_ONE_OR_BELOW 0x3UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_MODE_SPEED_MASK   0x4UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_MODE_LAST        PORT_PHY_QCFG_RESP_AUTO_MODE_SPEED_MASK
	u8	स्वतः_छोड़ो;
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_PAUSE_TX                0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_PAUSE_RX                0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_PAUSE_AUTONEG_PAUSE     0x4UL
	__le16	स्वतः_link_speed;
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_100MB 0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_1GB   0xaUL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_2GB   0x14UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_2_5GB 0x19UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_10GB  0x64UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_20GB  0xc8UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_25GB  0xfaUL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_40GB  0x190UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_50GB  0x1f4UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_100GB 0x3e8UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_10MB  0xffffUL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_LAST PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_10MB
	__le16	स्वतः_link_speed_mask;
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_MASK_100MBHD     0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_MASK_100MB       0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_MASK_1GBHD       0x4UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_MASK_1GB         0x8UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_MASK_2GB         0x10UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_MASK_2_5GB       0x20UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_MASK_10GB        0x40UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_MASK_20GB        0x80UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_MASK_25GB        0x100UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_MASK_40GB        0x200UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_MASK_50GB        0x400UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_MASK_100GB       0x800UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_MASK_10MBHD      0x1000UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_LINK_SPEED_MASK_10MB        0x2000UL
	u8	wirespeed;
	#घोषणा PORT_PHY_QCFG_RESP_WIRESPEED_OFF 0x0UL
	#घोषणा PORT_PHY_QCFG_RESP_WIRESPEED_ON  0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_WIRESPEED_LAST PORT_PHY_QCFG_RESP_WIRESPEED_ON
	u8	lpbk;
	#घोषणा PORT_PHY_QCFG_RESP_LPBK_NONE     0x0UL
	#घोषणा PORT_PHY_QCFG_RESP_LPBK_LOCAL    0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_LPBK_REMOTE   0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_LPBK_EXTERNAL 0x3UL
	#घोषणा PORT_PHY_QCFG_RESP_LPBK_LAST    PORT_PHY_QCFG_RESP_LPBK_EXTERNAL
	u8	क्रमce_छोड़ो;
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_PAUSE_TX     0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_PAUSE_RX     0x2UL
	u8	module_status;
	#घोषणा PORT_PHY_QCFG_RESP_MODULE_STATUS_NONE          0x0UL
	#घोषणा PORT_PHY_QCFG_RESP_MODULE_STATUS_DISABLETX     0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_MODULE_STATUS_WARNINGMSG    0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_MODULE_STATUS_PWRDOWN       0x3UL
	#घोषणा PORT_PHY_QCFG_RESP_MODULE_STATUS_NOTINSERTED   0x4UL
	#घोषणा PORT_PHY_QCFG_RESP_MODULE_STATUS_CURRENTFAULT  0x5UL
	#घोषणा PORT_PHY_QCFG_RESP_MODULE_STATUS_NOTAPPLICABLE 0xffUL
	#घोषणा PORT_PHY_QCFG_RESP_MODULE_STATUS_LAST         PORT_PHY_QCFG_RESP_MODULE_STATUS_NOTAPPLICABLE
	__le32	preemphasis;
	u8	phy_maj;
	u8	phy_min;
	u8	phy_bld;
	u8	phy_type;
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_UNKNOWN          0x0UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_BASECR           0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_BASEKR4          0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_BASELR           0x3UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_BASESR           0x4UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_BASEKR2          0x5UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_BASEKX           0x6UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_BASEKR           0x7UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_BASET            0x8UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_BASETE           0x9UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_SGMIIEXTPHY      0xaUL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_25G_BASECR_CA_L  0xbUL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_25G_BASECR_CA_S  0xcUL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_25G_BASECR_CA_N  0xdUL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_25G_BASESR       0xeUL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_100G_BASECR4     0xfUL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_100G_BASESR4     0x10UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_100G_BASELR4     0x11UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_100G_BASEER4     0x12UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_100G_BASESR10    0x13UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_40G_BASECR4      0x14UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_40G_BASESR4      0x15UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_40G_BASELR4      0x16UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_40G_BASEER4      0x17UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_40G_ACTIVE_CABLE 0x18UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_1G_BASET         0x19UL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_1G_BASESX        0x1aUL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_1G_BASECX        0x1bUL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_200G_BASECR4     0x1cUL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_200G_BASESR4     0x1dUL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_200G_BASELR4     0x1eUL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_200G_BASEER4     0x1fUL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_TYPE_LAST            PORT_PHY_QCFG_RESP_PHY_TYPE_200G_BASEER4
	u8	media_type;
	#घोषणा PORT_PHY_QCFG_RESP_MEDIA_TYPE_UNKNOWN 0x0UL
	#घोषणा PORT_PHY_QCFG_RESP_MEDIA_TYPE_TP      0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_MEDIA_TYPE_DAC     0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_MEDIA_TYPE_FIBRE   0x3UL
	#घोषणा PORT_PHY_QCFG_RESP_MEDIA_TYPE_LAST   PORT_PHY_QCFG_RESP_MEDIA_TYPE_FIBRE
	u8	xcvr_pkg_type;
	#घोषणा PORT_PHY_QCFG_RESP_XCVR_PKG_TYPE_XCVR_INTERNAL 0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_XCVR_PKG_TYPE_XCVR_EXTERNAL 0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_XCVR_PKG_TYPE_LAST         PORT_PHY_QCFG_RESP_XCVR_PKG_TYPE_XCVR_EXTERNAL
	u8	eee_config_phy_addr;
	#घोषणा PORT_PHY_QCFG_RESP_PHY_ADDR_MASK              0x1fUL
	#घोषणा PORT_PHY_QCFG_RESP_PHY_ADDR_SFT               0
	#घोषणा PORT_PHY_QCFG_RESP_EEE_CONFIG_MASK            0xe0UL
	#घोषणा PORT_PHY_QCFG_RESP_EEE_CONFIG_SFT             5
	#घोषणा PORT_PHY_QCFG_RESP_EEE_CONFIG_EEE_ENABLED      0x20UL
	#घोषणा PORT_PHY_QCFG_RESP_EEE_CONFIG_EEE_ACTIVE       0x40UL
	#घोषणा PORT_PHY_QCFG_RESP_EEE_CONFIG_EEE_TX_LPI       0x80UL
	u8	parallel_detect;
	#घोषणा PORT_PHY_QCFG_RESP_PARALLEL_DETECT     0x1UL
	__le16	link_partner_adv_speeds;
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_SPEEDS_100MBHD     0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_SPEEDS_100MB       0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_SPEEDS_1GBHD       0x4UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_SPEEDS_1GB         0x8UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_SPEEDS_2GB         0x10UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_SPEEDS_2_5GB       0x20UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_SPEEDS_10GB        0x40UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_SPEEDS_20GB        0x80UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_SPEEDS_25GB        0x100UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_SPEEDS_40GB        0x200UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_SPEEDS_50GB        0x400UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_SPEEDS_100GB       0x800UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_SPEEDS_10MBHD      0x1000UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_SPEEDS_10MB        0x2000UL
	u8	link_partner_adv_स्वतः_mode;
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_AUTO_MODE_NONE         0x0UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_AUTO_MODE_ALL_SPEEDS   0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_AUTO_MODE_ONE_SPEED    0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_AUTO_MODE_ONE_OR_BELOW 0x3UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_AUTO_MODE_SPEED_MASK   0x4UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_AUTO_MODE_LAST        PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_AUTO_MODE_SPEED_MASK
	u8	link_partner_adv_छोड़ो;
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_PAUSE_TX     0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_PAUSE_RX     0x2UL
	__le16	adv_eee_link_speed_mask;
	#घोषणा PORT_PHY_QCFG_RESP_ADV_EEE_LINK_SPEED_MASK_RSVD1     0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_ADV_EEE_LINK_SPEED_MASK_100MB     0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_ADV_EEE_LINK_SPEED_MASK_RSVD2     0x4UL
	#घोषणा PORT_PHY_QCFG_RESP_ADV_EEE_LINK_SPEED_MASK_1GB       0x8UL
	#घोषणा PORT_PHY_QCFG_RESP_ADV_EEE_LINK_SPEED_MASK_RSVD3     0x10UL
	#घोषणा PORT_PHY_QCFG_RESP_ADV_EEE_LINK_SPEED_MASK_RSVD4     0x20UL
	#घोषणा PORT_PHY_QCFG_RESP_ADV_EEE_LINK_SPEED_MASK_10GB      0x40UL
	__le16	link_partner_adv_eee_link_speed_mask;
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_EEE_LINK_SPEED_MASK_RSVD1     0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_EEE_LINK_SPEED_MASK_100MB     0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_EEE_LINK_SPEED_MASK_RSVD2     0x4UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_EEE_LINK_SPEED_MASK_1GB       0x8UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_EEE_LINK_SPEED_MASK_RSVD3     0x10UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_EEE_LINK_SPEED_MASK_RSVD4     0x20UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_ADV_EEE_LINK_SPEED_MASK_10GB      0x40UL
	__le32	xcvr_identअगरier_type_tx_lpi_समयr;
	#घोषणा PORT_PHY_QCFG_RESP_TX_LPI_TIMER_MASK            0xffffffUL
	#घोषणा PORT_PHY_QCFG_RESP_TX_LPI_TIMER_SFT             0
	#घोषणा PORT_PHY_QCFG_RESP_XCVR_IDENTIFIER_TYPE_MASK    0xff000000UL
	#घोषणा PORT_PHY_QCFG_RESP_XCVR_IDENTIFIER_TYPE_SFT     24
	#घोषणा PORT_PHY_QCFG_RESP_XCVR_IDENTIFIER_TYPE_UNKNOWN   (0x0UL << 24)
	#घोषणा PORT_PHY_QCFG_RESP_XCVR_IDENTIFIER_TYPE_SFP       (0x3UL << 24)
	#घोषणा PORT_PHY_QCFG_RESP_XCVR_IDENTIFIER_TYPE_QSFP      (0xcUL << 24)
	#घोषणा PORT_PHY_QCFG_RESP_XCVR_IDENTIFIER_TYPE_QSFPPLUS  (0xdUL << 24)
	#घोषणा PORT_PHY_QCFG_RESP_XCVR_IDENTIFIER_TYPE_QSFP28    (0x11UL << 24)
	#घोषणा PORT_PHY_QCFG_RESP_XCVR_IDENTIFIER_TYPE_LAST     PORT_PHY_QCFG_RESP_XCVR_IDENTIFIER_TYPE_QSFP28
	__le16	fec_cfg;
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_NONE_SUPPORTED           0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_AUTONEG_SUPPORTED        0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_AUTONEG_ENABLED          0x4UL
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_CLAUSE74_SUPPORTED       0x8UL
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_CLAUSE74_ENABLED         0x10UL
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_CLAUSE91_SUPPORTED       0x20UL
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_CLAUSE91_ENABLED         0x40UL
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_RS544_1XN_SUPPORTED      0x80UL
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_RS544_1XN_ENABLED        0x100UL
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_RS544_IEEE_SUPPORTED     0x200UL
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_RS544_IEEE_ENABLED       0x400UL
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_RS272_1XN_SUPPORTED      0x800UL
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_RS272_1XN_ENABLED        0x1000UL
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_RS272_IEEE_SUPPORTED     0x2000UL
	#घोषणा PORT_PHY_QCFG_RESP_FEC_CFG_FEC_RS272_IEEE_ENABLED       0x4000UL
	u8	duplex_state;
	#घोषणा PORT_PHY_QCFG_RESP_DUPLEX_STATE_HALF 0x0UL
	#घोषणा PORT_PHY_QCFG_RESP_DUPLEX_STATE_FULL 0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_DUPLEX_STATE_LAST PORT_PHY_QCFG_RESP_DUPLEX_STATE_FULL
	u8	option_flags;
	#घोषणा PORT_PHY_QCFG_RESP_OPTION_FLAGS_MEDIA_AUTO_DETECT     0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_OPTION_FLAGS_SIGNAL_MODE_KNOWN     0x2UL
	अक्षर	phy_venकरोr_name[16];
	अक्षर	phy_venकरोr_partnumber[16];
	__le16	support_pam4_speeds;
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_PAM4_SPEEDS_50G      0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_PAM4_SPEEDS_100G     0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_SUPPORT_PAM4_SPEEDS_200G     0x4UL
	__le16	क्रमce_pam4_link_speed;
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_PAM4_LINK_SPEED_50GB  0x1f4UL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_PAM4_LINK_SPEED_100GB 0x3e8UL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_PAM4_LINK_SPEED_200GB 0x7d0UL
	#घोषणा PORT_PHY_QCFG_RESP_FORCE_PAM4_LINK_SPEED_LAST PORT_PHY_QCFG_RESP_FORCE_PAM4_LINK_SPEED_200GB
	__le16	स्वतः_pam4_link_speed_mask;
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_PAM4_LINK_SPEED_MASK_50G      0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_PAM4_LINK_SPEED_MASK_100G     0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_AUTO_PAM4_LINK_SPEED_MASK_200G     0x4UL
	u8	link_partner_pam4_adv_speeds;
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_PAM4_ADV_SPEEDS_50GB      0x1UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_PAM4_ADV_SPEEDS_100GB     0x2UL
	#घोषणा PORT_PHY_QCFG_RESP_LINK_PARTNER_PAM4_ADV_SPEEDS_200GB     0x4UL
	u8	valid;
पूर्ण;

/* hwrm_port_mac_cfg_input (size:384b/48B) */
काष्ठा hwrm_port_mac_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा PORT_MAC_CFG_REQ_FLAGS_MATCH_LINK                    0x1UL
	#घोषणा PORT_MAC_CFG_REQ_FLAGS_VLAN_PRI2COS_ENABLE           0x2UL
	#घोषणा PORT_MAC_CFG_REQ_FLAGS_TUNNEL_PRI2COS_ENABLE         0x4UL
	#घोषणा PORT_MAC_CFG_REQ_FLAGS_IP_DSCP2COS_ENABLE            0x8UL
	#घोषणा PORT_MAC_CFG_REQ_FLAGS_PTP_RX_TS_CAPTURE_ENABLE      0x10UL
	#घोषणा PORT_MAC_CFG_REQ_FLAGS_PTP_RX_TS_CAPTURE_DISABLE     0x20UL
	#घोषणा PORT_MAC_CFG_REQ_FLAGS_PTP_TX_TS_CAPTURE_ENABLE      0x40UL
	#घोषणा PORT_MAC_CFG_REQ_FLAGS_PTP_TX_TS_CAPTURE_DISABLE     0x80UL
	#घोषणा PORT_MAC_CFG_REQ_FLAGS_OOB_WOL_ENABLE                0x100UL
	#घोषणा PORT_MAC_CFG_REQ_FLAGS_OOB_WOL_DISABLE               0x200UL
	#घोषणा PORT_MAC_CFG_REQ_FLAGS_VLAN_PRI2COS_DISABLE          0x400UL
	#घोषणा PORT_MAC_CFG_REQ_FLAGS_TUNNEL_PRI2COS_DISABLE        0x800UL
	#घोषणा PORT_MAC_CFG_REQ_FLAGS_IP_DSCP2COS_DISABLE           0x1000UL
	#घोषणा PORT_MAC_CFG_REQ_FLAGS_PTP_ONE_STEP_TX_TS            0x2000UL
	__le32	enables;
	#घोषणा PORT_MAC_CFG_REQ_ENABLES_IPG                            0x1UL
	#घोषणा PORT_MAC_CFG_REQ_ENABLES_LPBK                           0x2UL
	#घोषणा PORT_MAC_CFG_REQ_ENABLES_VLAN_PRI2COS_MAP_PRI           0x4UL
	#घोषणा PORT_MAC_CFG_REQ_ENABLES_TUNNEL_PRI2COS_MAP_PRI         0x10UL
	#घोषणा PORT_MAC_CFG_REQ_ENABLES_DSCP2COS_MAP_PRI               0x20UL
	#घोषणा PORT_MAC_CFG_REQ_ENABLES_RX_TS_CAPTURE_PTP_MSG_TYPE     0x40UL
	#घोषणा PORT_MAC_CFG_REQ_ENABLES_TX_TS_CAPTURE_PTP_MSG_TYPE     0x80UL
	#घोषणा PORT_MAC_CFG_REQ_ENABLES_COS_FIELD_CFG                  0x100UL
	#घोषणा PORT_MAC_CFG_REQ_ENABLES_PTP_FREQ_ADJ_PPB               0x200UL
	__le16	port_id;
	u8	ipg;
	u8	lpbk;
	#घोषणा PORT_MAC_CFG_REQ_LPBK_NONE   0x0UL
	#घोषणा PORT_MAC_CFG_REQ_LPBK_LOCAL  0x1UL
	#घोषणा PORT_MAC_CFG_REQ_LPBK_REMOTE 0x2UL
	#घोषणा PORT_MAC_CFG_REQ_LPBK_LAST  PORT_MAC_CFG_REQ_LPBK_REMOTE
	u8	vlan_pri2cos_map_pri;
	u8	reserved1;
	u8	tunnel_pri2cos_map_pri;
	u8	dscp2pri_map_pri;
	__le16	rx_ts_capture_ptp_msg_type;
	__le16	tx_ts_capture_ptp_msg_type;
	u8	cos_field_cfg;
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_RSVD1                     0x1UL
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_VLAN_PRI_SEL_MASK         0x6UL
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_VLAN_PRI_SEL_SFT          1
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_VLAN_PRI_SEL_INNERMOST      (0x0UL << 1)
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_VLAN_PRI_SEL_OUTER          (0x1UL << 1)
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_VLAN_PRI_SEL_OUTERMOST      (0x2UL << 1)
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_VLAN_PRI_SEL_UNSPECIFIED    (0x3UL << 1)
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_VLAN_PRI_SEL_LAST          PORT_MAC_CFG_REQ_COS_FIELD_CFG_VLAN_PRI_SEL_UNSPECIFIED
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_T_VLAN_PRI_SEL_MASK       0x18UL
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_T_VLAN_PRI_SEL_SFT        3
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_T_VLAN_PRI_SEL_INNERMOST    (0x0UL << 3)
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_T_VLAN_PRI_SEL_OUTER        (0x1UL << 3)
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_T_VLAN_PRI_SEL_OUTERMOST    (0x2UL << 3)
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_T_VLAN_PRI_SEL_UNSPECIFIED  (0x3UL << 3)
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_T_VLAN_PRI_SEL_LAST        PORT_MAC_CFG_REQ_COS_FIELD_CFG_T_VLAN_PRI_SEL_UNSPECIFIED
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_DEFAULT_COS_MASK          0xe0UL
	#घोषणा PORT_MAC_CFG_REQ_COS_FIELD_CFG_DEFAULT_COS_SFT           5
	u8	unused_0[3];
	__s32	ptp_freq_adj_ppb;
	u8	unused_1[4];
पूर्ण;

/* hwrm_port_mac_cfg_output (size:128b/16B) */
काष्ठा hwrm_port_mac_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	mru;
	__le16	mtu;
	u8	ipg;
	u8	lpbk;
	#घोषणा PORT_MAC_CFG_RESP_LPBK_NONE   0x0UL
	#घोषणा PORT_MAC_CFG_RESP_LPBK_LOCAL  0x1UL
	#घोषणा PORT_MAC_CFG_RESP_LPBK_REMOTE 0x2UL
	#घोषणा PORT_MAC_CFG_RESP_LPBK_LAST  PORT_MAC_CFG_RESP_LPBK_REMOTE
	u8	unused_0;
	u8	valid;
पूर्ण;

/* hwrm_port_mac_ptp_qcfg_input (size:192b/24B) */
काष्ठा hwrm_port_mac_ptp_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	port_id;
	u8	unused_0[6];
पूर्ण;

/* hwrm_port_mac_ptp_qcfg_output (size:640b/80B) */
काष्ठा hwrm_port_mac_ptp_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	flags;
	#घोषणा PORT_MAC_PTP_QCFG_RESP_FLAGS_सूचीECT_ACCESS      0x1UL
	#घोषणा PORT_MAC_PTP_QCFG_RESP_FLAGS_ONE_STEP_TX_TS     0x4UL
	#घोषणा PORT_MAC_PTP_QCFG_RESP_FLAGS_HWRM_ACCESS        0x8UL
	u8	unused_0[3];
	__le32	rx_ts_reg_off_lower;
	__le32	rx_ts_reg_off_upper;
	__le32	rx_ts_reg_off_seq_id;
	__le32	rx_ts_reg_off_src_id_0;
	__le32	rx_ts_reg_off_src_id_1;
	__le32	rx_ts_reg_off_src_id_2;
	__le32	rx_ts_reg_off_करोमुख्य_id;
	__le32	rx_ts_reg_off_fअगरo;
	__le32	rx_ts_reg_off_fअगरo_adv;
	__le32	rx_ts_reg_off_granularity;
	__le32	tx_ts_reg_off_lower;
	__le32	tx_ts_reg_off_upper;
	__le32	tx_ts_reg_off_seq_id;
	__le32	tx_ts_reg_off_fअगरo;
	__le32	tx_ts_reg_off_granularity;
	u8	unused_1[7];
	u8	valid;
पूर्ण;

/* tx_port_stats (size:3264b/408B) */
काष्ठा tx_port_stats अणु
	__le64	tx_64b_frames;
	__le64	tx_65b_127b_frames;
	__le64	tx_128b_255b_frames;
	__le64	tx_256b_511b_frames;
	__le64	tx_512b_1023b_frames;
	__le64	tx_1024b_1518b_frames;
	__le64	tx_good_vlan_frames;
	__le64	tx_1519b_2047b_frames;
	__le64	tx_2048b_4095b_frames;
	__le64	tx_4096b_9216b_frames;
	__le64	tx_9217b_16383b_frames;
	__le64	tx_good_frames;
	__le64	tx_total_frames;
	__le64	tx_ucast_frames;
	__le64	tx_mcast_frames;
	__le64	tx_bcast_frames;
	__le64	tx_छोड़ो_frames;
	__le64	tx_pfc_frames;
	__le64	tx_jabber_frames;
	__le64	tx_fcs_err_frames;
	__le64	tx_control_frames;
	__le64	tx_oversz_frames;
	__le64	tx_single_dfrl_frames;
	__le64	tx_multi_dfrl_frames;
	__le64	tx_single_coll_frames;
	__le64	tx_multi_coll_frames;
	__le64	tx_late_coll_frames;
	__le64	tx_excessive_coll_frames;
	__le64	tx_frag_frames;
	__le64	tx_err;
	__le64	tx_tagged_frames;
	__le64	tx_dbl_tagged_frames;
	__le64	tx_runt_frames;
	__le64	tx_fअगरo_underruns;
	__le64	tx_pfc_ena_frames_pri0;
	__le64	tx_pfc_ena_frames_pri1;
	__le64	tx_pfc_ena_frames_pri2;
	__le64	tx_pfc_ena_frames_pri3;
	__le64	tx_pfc_ena_frames_pri4;
	__le64	tx_pfc_ena_frames_pri5;
	__le64	tx_pfc_ena_frames_pri6;
	__le64	tx_pfc_ena_frames_pri7;
	__le64	tx_eee_lpi_events;
	__le64	tx_eee_lpi_duration;
	__le64	tx_llfc_logical_msgs;
	__le64	tx_hcfc_msgs;
	__le64	tx_total_collisions;
	__le64	tx_bytes;
	__le64	tx_xthol_frames;
	__le64	tx_stat_discard;
	__le64	tx_stat_error;
पूर्ण;

/* rx_port_stats (size:4224b/528B) */
काष्ठा rx_port_stats अणु
	__le64	rx_64b_frames;
	__le64	rx_65b_127b_frames;
	__le64	rx_128b_255b_frames;
	__le64	rx_256b_511b_frames;
	__le64	rx_512b_1023b_frames;
	__le64	rx_1024b_1518b_frames;
	__le64	rx_good_vlan_frames;
	__le64	rx_1519b_2047b_frames;
	__le64	rx_2048b_4095b_frames;
	__le64	rx_4096b_9216b_frames;
	__le64	rx_9217b_16383b_frames;
	__le64	rx_total_frames;
	__le64	rx_ucast_frames;
	__le64	rx_mcast_frames;
	__le64	rx_bcast_frames;
	__le64	rx_fcs_err_frames;
	__le64	rx_ctrl_frames;
	__le64	rx_छोड़ो_frames;
	__le64	rx_pfc_frames;
	__le64	rx_unsupported_opcode_frames;
	__le64	rx_unsupported_da_छोड़ोpfc_frames;
	__le64	rx_wrong_sa_frames;
	__le64	rx_align_err_frames;
	__le64	rx_oor_len_frames;
	__le64	rx_code_err_frames;
	__le64	rx_false_carrier_frames;
	__le64	rx_ovrsz_frames;
	__le64	rx_jbr_frames;
	__le64	rx_mtu_err_frames;
	__le64	rx_match_crc_frames;
	__le64	rx_promiscuous_frames;
	__le64	rx_tagged_frames;
	__le64	rx_द्विगुन_tagged_frames;
	__le64	rx_trunc_frames;
	__le64	rx_good_frames;
	__le64	rx_pfc_xon2xoff_frames_pri0;
	__le64	rx_pfc_xon2xoff_frames_pri1;
	__le64	rx_pfc_xon2xoff_frames_pri2;
	__le64	rx_pfc_xon2xoff_frames_pri3;
	__le64	rx_pfc_xon2xoff_frames_pri4;
	__le64	rx_pfc_xon2xoff_frames_pri5;
	__le64	rx_pfc_xon2xoff_frames_pri6;
	__le64	rx_pfc_xon2xoff_frames_pri7;
	__le64	rx_pfc_ena_frames_pri0;
	__le64	rx_pfc_ena_frames_pri1;
	__le64	rx_pfc_ena_frames_pri2;
	__le64	rx_pfc_ena_frames_pri3;
	__le64	rx_pfc_ena_frames_pri4;
	__le64	rx_pfc_ena_frames_pri5;
	__le64	rx_pfc_ena_frames_pri6;
	__le64	rx_pfc_ena_frames_pri7;
	__le64	rx_sch_crc_err_frames;
	__le64	rx_undrsz_frames;
	__le64	rx_frag_frames;
	__le64	rx_eee_lpi_events;
	__le64	rx_eee_lpi_duration;
	__le64	rx_llfc_physical_msgs;
	__le64	rx_llfc_logical_msgs;
	__le64	rx_llfc_msgs_with_crc_err;
	__le64	rx_hcfc_msgs;
	__le64	rx_hcfc_msgs_with_crc_err;
	__le64	rx_bytes;
	__le64	rx_runt_bytes;
	__le64	rx_runt_frames;
	__le64	rx_stat_discard;
	__le64	rx_stat_err;
पूर्ण;

/* hwrm_port_qstats_input (size:320b/40B) */
काष्ठा hwrm_port_qstats_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	port_id;
	u8	flags;
	#घोषणा PORT_QSTATS_REQ_FLAGS_UNUSED       0x0UL
	#घोषणा PORT_QSTATS_REQ_FLAGS_COUNTER_MASK 0x1UL
	#घोषणा PORT_QSTATS_REQ_FLAGS_LAST        PORT_QSTATS_REQ_FLAGS_COUNTER_MASK
	u8	unused_0[5];
	__le64	tx_stat_host_addr;
	__le64	rx_stat_host_addr;
पूर्ण;

/* hwrm_port_qstats_output (size:128b/16B) */
काष्ठा hwrm_port_qstats_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	tx_stat_size;
	__le16	rx_stat_size;
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* tx_port_stats_ext (size:2048b/256B) */
काष्ठा tx_port_stats_ext अणु
	__le64	tx_bytes_cos0;
	__le64	tx_bytes_cos1;
	__le64	tx_bytes_cos2;
	__le64	tx_bytes_cos3;
	__le64	tx_bytes_cos4;
	__le64	tx_bytes_cos5;
	__le64	tx_bytes_cos6;
	__le64	tx_bytes_cos7;
	__le64	tx_packets_cos0;
	__le64	tx_packets_cos1;
	__le64	tx_packets_cos2;
	__le64	tx_packets_cos3;
	__le64	tx_packets_cos4;
	__le64	tx_packets_cos5;
	__le64	tx_packets_cos6;
	__le64	tx_packets_cos7;
	__le64	pfc_pri0_tx_duration_us;
	__le64	pfc_pri0_tx_transitions;
	__le64	pfc_pri1_tx_duration_us;
	__le64	pfc_pri1_tx_transitions;
	__le64	pfc_pri2_tx_duration_us;
	__le64	pfc_pri2_tx_transitions;
	__le64	pfc_pri3_tx_duration_us;
	__le64	pfc_pri3_tx_transitions;
	__le64	pfc_pri4_tx_duration_us;
	__le64	pfc_pri4_tx_transitions;
	__le64	pfc_pri5_tx_duration_us;
	__le64	pfc_pri5_tx_transitions;
	__le64	pfc_pri6_tx_duration_us;
	__le64	pfc_pri6_tx_transitions;
	__le64	pfc_pri7_tx_duration_us;
	__le64	pfc_pri7_tx_transitions;
पूर्ण;

/* rx_port_stats_ext (size:3648b/456B) */
काष्ठा rx_port_stats_ext अणु
	__le64	link_करोwn_events;
	__le64	continuous_छोड़ो_events;
	__le64	resume_छोड़ो_events;
	__le64	continuous_roce_छोड़ो_events;
	__le64	resume_roce_छोड़ो_events;
	__le64	rx_bytes_cos0;
	__le64	rx_bytes_cos1;
	__le64	rx_bytes_cos2;
	__le64	rx_bytes_cos3;
	__le64	rx_bytes_cos4;
	__le64	rx_bytes_cos5;
	__le64	rx_bytes_cos6;
	__le64	rx_bytes_cos7;
	__le64	rx_packets_cos0;
	__le64	rx_packets_cos1;
	__le64	rx_packets_cos2;
	__le64	rx_packets_cos3;
	__le64	rx_packets_cos4;
	__le64	rx_packets_cos5;
	__le64	rx_packets_cos6;
	__le64	rx_packets_cos7;
	__le64	pfc_pri0_rx_duration_us;
	__le64	pfc_pri0_rx_transitions;
	__le64	pfc_pri1_rx_duration_us;
	__le64	pfc_pri1_rx_transitions;
	__le64	pfc_pri2_rx_duration_us;
	__le64	pfc_pri2_rx_transitions;
	__le64	pfc_pri3_rx_duration_us;
	__le64	pfc_pri3_rx_transitions;
	__le64	pfc_pri4_rx_duration_us;
	__le64	pfc_pri4_rx_transitions;
	__le64	pfc_pri5_rx_duration_us;
	__le64	pfc_pri5_rx_transitions;
	__le64	pfc_pri6_rx_duration_us;
	__le64	pfc_pri6_rx_transitions;
	__le64	pfc_pri7_rx_duration_us;
	__le64	pfc_pri7_rx_transitions;
	__le64	rx_bits;
	__le64	rx_buffer_passed_threshold;
	__le64	rx_pcs_symbol_err;
	__le64	rx_corrected_bits;
	__le64	rx_discard_bytes_cos0;
	__le64	rx_discard_bytes_cos1;
	__le64	rx_discard_bytes_cos2;
	__le64	rx_discard_bytes_cos3;
	__le64	rx_discard_bytes_cos4;
	__le64	rx_discard_bytes_cos5;
	__le64	rx_discard_bytes_cos6;
	__le64	rx_discard_bytes_cos7;
	__le64	rx_discard_packets_cos0;
	__le64	rx_discard_packets_cos1;
	__le64	rx_discard_packets_cos2;
	__le64	rx_discard_packets_cos3;
	__le64	rx_discard_packets_cos4;
	__le64	rx_discard_packets_cos5;
	__le64	rx_discard_packets_cos6;
	__le64	rx_discard_packets_cos7;
पूर्ण;

/* hwrm_port_qstats_ext_input (size:320b/40B) */
काष्ठा hwrm_port_qstats_ext_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	port_id;
	__le16	tx_stat_size;
	__le16	rx_stat_size;
	u8	flags;
	#घोषणा PORT_QSTATS_EXT_REQ_FLAGS_UNUSED       0x0UL
	#घोषणा PORT_QSTATS_EXT_REQ_FLAGS_COUNTER_MASK 0x1UL
	#घोषणा PORT_QSTATS_EXT_REQ_FLAGS_LAST        PORT_QSTATS_EXT_REQ_FLAGS_COUNTER_MASK
	u8	unused_0;
	__le64	tx_stat_host_addr;
	__le64	rx_stat_host_addr;
पूर्ण;

/* hwrm_port_qstats_ext_output (size:128b/16B) */
काष्ठा hwrm_port_qstats_ext_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	tx_stat_size;
	__le16	rx_stat_size;
	__le16	total_active_cos_queues;
	u8	flags;
	#घोषणा PORT_QSTATS_EXT_RESP_FLAGS_CLEAR_ROCE_COUNTERS_SUPPORTED     0x1UL
	u8	valid;
पूर्ण;

/* hwrm_port_lpbk_qstats_input (size:128b/16B) */
काष्ठा hwrm_port_lpbk_qstats_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
पूर्ण;

/* hwrm_port_lpbk_qstats_output (size:768b/96B) */
काष्ठा hwrm_port_lpbk_qstats_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le64	lpbk_ucast_frames;
	__le64	lpbk_mcast_frames;
	__le64	lpbk_bcast_frames;
	__le64	lpbk_ucast_bytes;
	__le64	lpbk_mcast_bytes;
	__le64	lpbk_bcast_bytes;
	__le64	tx_stat_discard;
	__le64	tx_stat_error;
	__le64	rx_stat_discard;
	__le64	rx_stat_error;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_port_ecn_qstats_input (size:256b/32B) */
काष्ठा hwrm_port_ecn_qstats_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	port_id;
	__le16	ecn_stat_buf_size;
	u8	flags;
	#घोषणा PORT_ECN_QSTATS_REQ_FLAGS_UNUSED       0x0UL
	#घोषणा PORT_ECN_QSTATS_REQ_FLAGS_COUNTER_MASK 0x1UL
	#घोषणा PORT_ECN_QSTATS_REQ_FLAGS_LAST        PORT_ECN_QSTATS_REQ_FLAGS_COUNTER_MASK
	u8	unused_0[3];
	__le64	ecn_stat_host_addr;
पूर्ण;

/* hwrm_port_ecn_qstats_output (size:128b/16B) */
काष्ठा hwrm_port_ecn_qstats_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	ecn_stat_buf_size;
	u8	mark_en;
	u8	unused_0[4];
	u8	valid;
पूर्ण;

/* port_stats_ecn (size:512b/64B) */
काष्ठा port_stats_ecn अणु
	__le64	mark_cnt_cos0;
	__le64	mark_cnt_cos1;
	__le64	mark_cnt_cos2;
	__le64	mark_cnt_cos3;
	__le64	mark_cnt_cos4;
	__le64	mark_cnt_cos5;
	__le64	mark_cnt_cos6;
	__le64	mark_cnt_cos7;
पूर्ण;

/* hwrm_port_clr_stats_input (size:192b/24B) */
काष्ठा hwrm_port_clr_stats_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	port_id;
	u8	flags;
	#घोषणा PORT_CLR_STATS_REQ_FLAGS_ROCE_COUNTERS     0x1UL
	u8	unused_0[5];
पूर्ण;

/* hwrm_port_clr_stats_output (size:128b/16B) */
काष्ठा hwrm_port_clr_stats_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_port_lpbk_clr_stats_input (size:128b/16B) */
काष्ठा hwrm_port_lpbk_clr_stats_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
पूर्ण;

/* hwrm_port_lpbk_clr_stats_output (size:128b/16B) */
काष्ठा hwrm_port_lpbk_clr_stats_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_port_ts_query_input (size:192b/24B) */
काष्ठा hwrm_port_ts_query_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा PORT_TS_QUERY_REQ_FLAGS_PATH             0x1UL
	#घोषणा PORT_TS_QUERY_REQ_FLAGS_PATH_TX            0x0UL
	#घोषणा PORT_TS_QUERY_REQ_FLAGS_PATH_RX            0x1UL
	#घोषणा PORT_TS_QUERY_REQ_FLAGS_PATH_LAST         PORT_TS_QUERY_REQ_FLAGS_PATH_RX
	#घोषणा PORT_TS_QUERY_REQ_FLAGS_CURRENT_TIME     0x2UL
	__le16	port_id;
	u8	unused_0[2];
पूर्ण;

/* hwrm_port_ts_query_output (size:192b/24B) */
काष्ठा hwrm_port_ts_query_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le64	ptp_msg_ts;
	__le16	ptp_msg_seqid;
	u8	unused_0[5];
	u8	valid;
पूर्ण;

/* hwrm_port_phy_qcaps_input (size:192b/24B) */
काष्ठा hwrm_port_phy_qcaps_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	port_id;
	u8	unused_0[6];
पूर्ण;

/* hwrm_port_phy_qcaps_output (size:256b/32B) */
काष्ठा hwrm_port_phy_qcaps_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	flags;
	#घोषणा PORT_PHY_QCAPS_RESP_FLAGS_EEE_SUPPORTED                    0x1UL
	#घोषणा PORT_PHY_QCAPS_RESP_FLAGS_EXTERNAL_LPBK_SUPPORTED          0x2UL
	#घोषणा PORT_PHY_QCAPS_RESP_FLAGS_AUTONEG_LPBK_SUPPORTED           0x4UL
	#घोषणा PORT_PHY_QCAPS_RESP_FLAGS_SHARED_PHY_CFG_SUPPORTED         0x8UL
	#घोषणा PORT_PHY_QCAPS_RESP_FLAGS_CUMULATIVE_COUNTERS_ON_RESET     0x10UL
	#घोषणा PORT_PHY_QCAPS_RESP_FLAGS_LOCAL_LPBK_NOT_SUPPORTED         0x20UL
	#घोषणा PORT_PHY_QCAPS_RESP_FLAGS_FW_MANAGED_LINK_DOWN             0x40UL
	#घोषणा PORT_PHY_QCAPS_RESP_FLAGS_NO_FCS                           0x80UL
	u8	port_cnt;
	#घोषणा PORT_PHY_QCAPS_RESP_PORT_CNT_UNKNOWN 0x0UL
	#घोषणा PORT_PHY_QCAPS_RESP_PORT_CNT_1       0x1UL
	#घोषणा PORT_PHY_QCAPS_RESP_PORT_CNT_2       0x2UL
	#घोषणा PORT_PHY_QCAPS_RESP_PORT_CNT_3       0x3UL
	#घोषणा PORT_PHY_QCAPS_RESP_PORT_CNT_4       0x4UL
	#घोषणा PORT_PHY_QCAPS_RESP_PORT_CNT_LAST   PORT_PHY_QCAPS_RESP_PORT_CNT_4
	__le16	supported_speeds_क्रमce_mode;
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_FORCE_MODE_100MBHD     0x1UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_FORCE_MODE_100MB       0x2UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_FORCE_MODE_1GBHD       0x4UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_FORCE_MODE_1GB         0x8UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_FORCE_MODE_2GB         0x10UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_FORCE_MODE_2_5GB       0x20UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_FORCE_MODE_10GB        0x40UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_FORCE_MODE_20GB        0x80UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_FORCE_MODE_25GB        0x100UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_FORCE_MODE_40GB        0x200UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_FORCE_MODE_50GB        0x400UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_FORCE_MODE_100GB       0x800UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_FORCE_MODE_10MBHD      0x1000UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_FORCE_MODE_10MB        0x2000UL
	__le16	supported_speeds_स्वतः_mode;
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_AUTO_MODE_100MBHD     0x1UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_AUTO_MODE_100MB       0x2UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_AUTO_MODE_1GBHD       0x4UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_AUTO_MODE_1GB         0x8UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_AUTO_MODE_2GB         0x10UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_AUTO_MODE_2_5GB       0x20UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_AUTO_MODE_10GB        0x40UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_AUTO_MODE_20GB        0x80UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_AUTO_MODE_25GB        0x100UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_AUTO_MODE_40GB        0x200UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_AUTO_MODE_50GB        0x400UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_AUTO_MODE_100GB       0x800UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_AUTO_MODE_10MBHD      0x1000UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_AUTO_MODE_10MB        0x2000UL
	__le16	supported_speeds_eee_mode;
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_EEE_MODE_RSVD1     0x1UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_EEE_MODE_100MB     0x2UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_EEE_MODE_RSVD2     0x4UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_EEE_MODE_1GB       0x8UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_EEE_MODE_RSVD3     0x10UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_EEE_MODE_RSVD4     0x20UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_SPEEDS_EEE_MODE_10GB      0x40UL
	__le32	tx_lpi_समयr_low;
	#घोषणा PORT_PHY_QCAPS_RESP_TX_LPI_TIMER_LOW_MASK 0xffffffUL
	#घोषणा PORT_PHY_QCAPS_RESP_TX_LPI_TIMER_LOW_SFT 0
	#घोषणा PORT_PHY_QCAPS_RESP_RSVD2_MASK           0xff000000UL
	#घोषणा PORT_PHY_QCAPS_RESP_RSVD2_SFT            24
	__le32	valid_tx_lpi_समयr_high;
	#घोषणा PORT_PHY_QCAPS_RESP_TX_LPI_TIMER_HIGH_MASK 0xffffffUL
	#घोषणा PORT_PHY_QCAPS_RESP_TX_LPI_TIMER_HIGH_SFT 0
	#घोषणा PORT_PHY_QCAPS_RESP_RSVD_MASK             0xff000000UL
	#घोषणा PORT_PHY_QCAPS_RESP_RSVD_SFT              24
	__le16	supported_pam4_speeds_स्वतः_mode;
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_PAM4_SPEEDS_AUTO_MODE_50G      0x1UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_PAM4_SPEEDS_AUTO_MODE_100G     0x2UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_PAM4_SPEEDS_AUTO_MODE_200G     0x4UL
	__le16	supported_pam4_speeds_क्रमce_mode;
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_PAM4_SPEEDS_FORCE_MODE_50G      0x1UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_PAM4_SPEEDS_FORCE_MODE_100G     0x2UL
	#घोषणा PORT_PHY_QCAPS_RESP_SUPPORTED_PAM4_SPEEDS_FORCE_MODE_200G     0x4UL
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_port_phy_i2c_पढ़ो_input (size:320b/40B) */
काष्ठा hwrm_port_phy_i2c_पढ़ो_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	__le32	enables;
	#घोषणा PORT_PHY_I2C_READ_REQ_ENABLES_PAGE_OFFSET     0x1UL
	__le16	port_id;
	u8	i2c_slave_addr;
	u8	unused_0;
	__le16	page_number;
	__le16	page_offset;
	u8	data_length;
	u8	unused_1[7];
पूर्ण;

/* hwrm_port_phy_i2c_पढ़ो_output (size:640b/80B) */
काष्ठा hwrm_port_phy_i2c_पढ़ो_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	data[16];
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_port_phy_mdio_ग_लिखो_input (size:320b/40B) */
काष्ठा hwrm_port_phy_mdio_ग_लिखो_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	unused_0[2];
	__le16	port_id;
	u8	phy_addr;
	u8	dev_addr;
	__le16	reg_addr;
	__le16	reg_data;
	u8	cl45_mdio;
	u8	unused_1[7];
पूर्ण;

/* hwrm_port_phy_mdio_ग_लिखो_output (size:128b/16B) */
काष्ठा hwrm_port_phy_mdio_ग_लिखो_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_port_phy_mdio_पढ़ो_input (size:256b/32B) */
काष्ठा hwrm_port_phy_mdio_पढ़ो_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	unused_0[2];
	__le16	port_id;
	u8	phy_addr;
	u8	dev_addr;
	__le16	reg_addr;
	u8	cl45_mdio;
	u8	unused_1;
पूर्ण;

/* hwrm_port_phy_mdio_पढ़ो_output (size:128b/16B) */
काष्ठा hwrm_port_phy_mdio_पढ़ो_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	reg_data;
	u8	unused_0[5];
	u8	valid;
पूर्ण;

/* hwrm_port_led_cfg_input (size:512b/64B) */
काष्ठा hwrm_port_led_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	enables;
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED0_ID            0x1UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED0_STATE         0x2UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED0_COLOR         0x4UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED0_BLINK_ON      0x8UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED0_BLINK_OFF     0x10UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED0_GROUP_ID      0x20UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED1_ID            0x40UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED1_STATE         0x80UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED1_COLOR         0x100UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED1_BLINK_ON      0x200UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED1_BLINK_OFF     0x400UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED1_GROUP_ID      0x800UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED2_ID            0x1000UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED2_STATE         0x2000UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED2_COLOR         0x4000UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED2_BLINK_ON      0x8000UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED2_BLINK_OFF     0x10000UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED2_GROUP_ID      0x20000UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED3_ID            0x40000UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED3_STATE         0x80000UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED3_COLOR         0x100000UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED3_BLINK_ON      0x200000UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED3_BLINK_OFF     0x400000UL
	#घोषणा PORT_LED_CFG_REQ_ENABLES_LED3_GROUP_ID      0x800000UL
	__le16	port_id;
	u8	num_leds;
	u8	rsvd;
	u8	led0_id;
	u8	led0_state;
	#घोषणा PORT_LED_CFG_REQ_LED0_STATE_DEFAULT  0x0UL
	#घोषणा PORT_LED_CFG_REQ_LED0_STATE_OFF      0x1UL
	#घोषणा PORT_LED_CFG_REQ_LED0_STATE_ON       0x2UL
	#घोषणा PORT_LED_CFG_REQ_LED0_STATE_BLINK    0x3UL
	#घोषणा PORT_LED_CFG_REQ_LED0_STATE_BLINKALT 0x4UL
	#घोषणा PORT_LED_CFG_REQ_LED0_STATE_LAST    PORT_LED_CFG_REQ_LED0_STATE_BLINKALT
	u8	led0_color;
	#घोषणा PORT_LED_CFG_REQ_LED0_COLOR_DEFAULT    0x0UL
	#घोषणा PORT_LED_CFG_REQ_LED0_COLOR_AMBER      0x1UL
	#घोषणा PORT_LED_CFG_REQ_LED0_COLOR_GREEN      0x2UL
	#घोषणा PORT_LED_CFG_REQ_LED0_COLOR_GREENAMBER 0x3UL
	#घोषणा PORT_LED_CFG_REQ_LED0_COLOR_LAST      PORT_LED_CFG_REQ_LED0_COLOR_GREENAMBER
	u8	unused_0;
	__le16	led0_blink_on;
	__le16	led0_blink_off;
	u8	led0_group_id;
	u8	rsvd0;
	u8	led1_id;
	u8	led1_state;
	#घोषणा PORT_LED_CFG_REQ_LED1_STATE_DEFAULT  0x0UL
	#घोषणा PORT_LED_CFG_REQ_LED1_STATE_OFF      0x1UL
	#घोषणा PORT_LED_CFG_REQ_LED1_STATE_ON       0x2UL
	#घोषणा PORT_LED_CFG_REQ_LED1_STATE_BLINK    0x3UL
	#घोषणा PORT_LED_CFG_REQ_LED1_STATE_BLINKALT 0x4UL
	#घोषणा PORT_LED_CFG_REQ_LED1_STATE_LAST    PORT_LED_CFG_REQ_LED1_STATE_BLINKALT
	u8	led1_color;
	#घोषणा PORT_LED_CFG_REQ_LED1_COLOR_DEFAULT    0x0UL
	#घोषणा PORT_LED_CFG_REQ_LED1_COLOR_AMBER      0x1UL
	#घोषणा PORT_LED_CFG_REQ_LED1_COLOR_GREEN      0x2UL
	#घोषणा PORT_LED_CFG_REQ_LED1_COLOR_GREENAMBER 0x3UL
	#घोषणा PORT_LED_CFG_REQ_LED1_COLOR_LAST      PORT_LED_CFG_REQ_LED1_COLOR_GREENAMBER
	u8	unused_1;
	__le16	led1_blink_on;
	__le16	led1_blink_off;
	u8	led1_group_id;
	u8	rsvd1;
	u8	led2_id;
	u8	led2_state;
	#घोषणा PORT_LED_CFG_REQ_LED2_STATE_DEFAULT  0x0UL
	#घोषणा PORT_LED_CFG_REQ_LED2_STATE_OFF      0x1UL
	#घोषणा PORT_LED_CFG_REQ_LED2_STATE_ON       0x2UL
	#घोषणा PORT_LED_CFG_REQ_LED2_STATE_BLINK    0x3UL
	#घोषणा PORT_LED_CFG_REQ_LED2_STATE_BLINKALT 0x4UL
	#घोषणा PORT_LED_CFG_REQ_LED2_STATE_LAST    PORT_LED_CFG_REQ_LED2_STATE_BLINKALT
	u8	led2_color;
	#घोषणा PORT_LED_CFG_REQ_LED2_COLOR_DEFAULT    0x0UL
	#घोषणा PORT_LED_CFG_REQ_LED2_COLOR_AMBER      0x1UL
	#घोषणा PORT_LED_CFG_REQ_LED2_COLOR_GREEN      0x2UL
	#घोषणा PORT_LED_CFG_REQ_LED2_COLOR_GREENAMBER 0x3UL
	#घोषणा PORT_LED_CFG_REQ_LED2_COLOR_LAST      PORT_LED_CFG_REQ_LED2_COLOR_GREENAMBER
	u8	unused_2;
	__le16	led2_blink_on;
	__le16	led2_blink_off;
	u8	led2_group_id;
	u8	rsvd2;
	u8	led3_id;
	u8	led3_state;
	#घोषणा PORT_LED_CFG_REQ_LED3_STATE_DEFAULT  0x0UL
	#घोषणा PORT_LED_CFG_REQ_LED3_STATE_OFF      0x1UL
	#घोषणा PORT_LED_CFG_REQ_LED3_STATE_ON       0x2UL
	#घोषणा PORT_LED_CFG_REQ_LED3_STATE_BLINK    0x3UL
	#घोषणा PORT_LED_CFG_REQ_LED3_STATE_BLINKALT 0x4UL
	#घोषणा PORT_LED_CFG_REQ_LED3_STATE_LAST    PORT_LED_CFG_REQ_LED3_STATE_BLINKALT
	u8	led3_color;
	#घोषणा PORT_LED_CFG_REQ_LED3_COLOR_DEFAULT    0x0UL
	#घोषणा PORT_LED_CFG_REQ_LED3_COLOR_AMBER      0x1UL
	#घोषणा PORT_LED_CFG_REQ_LED3_COLOR_GREEN      0x2UL
	#घोषणा PORT_LED_CFG_REQ_LED3_COLOR_GREENAMBER 0x3UL
	#घोषणा PORT_LED_CFG_REQ_LED3_COLOR_LAST      PORT_LED_CFG_REQ_LED3_COLOR_GREENAMBER
	u8	unused_3;
	__le16	led3_blink_on;
	__le16	led3_blink_off;
	u8	led3_group_id;
	u8	rsvd3;
पूर्ण;

/* hwrm_port_led_cfg_output (size:128b/16B) */
काष्ठा hwrm_port_led_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_port_led_qcfg_input (size:192b/24B) */
काष्ठा hwrm_port_led_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	port_id;
	u8	unused_0[6];
पूर्ण;

/* hwrm_port_led_qcfg_output (size:448b/56B) */
काष्ठा hwrm_port_led_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	num_leds;
	u8	led0_id;
	u8	led0_type;
	#घोषणा PORT_LED_QCFG_RESP_LED0_TYPE_SPEED    0x0UL
	#घोषणा PORT_LED_QCFG_RESP_LED0_TYPE_ACTIVITY 0x1UL
	#घोषणा PORT_LED_QCFG_RESP_LED0_TYPE_INVALID  0xffUL
	#घोषणा PORT_LED_QCFG_RESP_LED0_TYPE_LAST    PORT_LED_QCFG_RESP_LED0_TYPE_INVALID
	u8	led0_state;
	#घोषणा PORT_LED_QCFG_RESP_LED0_STATE_DEFAULT  0x0UL
	#घोषणा PORT_LED_QCFG_RESP_LED0_STATE_OFF      0x1UL
	#घोषणा PORT_LED_QCFG_RESP_LED0_STATE_ON       0x2UL
	#घोषणा PORT_LED_QCFG_RESP_LED0_STATE_BLINK    0x3UL
	#घोषणा PORT_LED_QCFG_RESP_LED0_STATE_BLINKALT 0x4UL
	#घोषणा PORT_LED_QCFG_RESP_LED0_STATE_LAST    PORT_LED_QCFG_RESP_LED0_STATE_BLINKALT
	u8	led0_color;
	#घोषणा PORT_LED_QCFG_RESP_LED0_COLOR_DEFAULT    0x0UL
	#घोषणा PORT_LED_QCFG_RESP_LED0_COLOR_AMBER      0x1UL
	#घोषणा PORT_LED_QCFG_RESP_LED0_COLOR_GREEN      0x2UL
	#घोषणा PORT_LED_QCFG_RESP_LED0_COLOR_GREENAMBER 0x3UL
	#घोषणा PORT_LED_QCFG_RESP_LED0_COLOR_LAST      PORT_LED_QCFG_RESP_LED0_COLOR_GREENAMBER
	u8	unused_0;
	__le16	led0_blink_on;
	__le16	led0_blink_off;
	u8	led0_group_id;
	u8	led1_id;
	u8	led1_type;
	#घोषणा PORT_LED_QCFG_RESP_LED1_TYPE_SPEED    0x0UL
	#घोषणा PORT_LED_QCFG_RESP_LED1_TYPE_ACTIVITY 0x1UL
	#घोषणा PORT_LED_QCFG_RESP_LED1_TYPE_INVALID  0xffUL
	#घोषणा PORT_LED_QCFG_RESP_LED1_TYPE_LAST    PORT_LED_QCFG_RESP_LED1_TYPE_INVALID
	u8	led1_state;
	#घोषणा PORT_LED_QCFG_RESP_LED1_STATE_DEFAULT  0x0UL
	#घोषणा PORT_LED_QCFG_RESP_LED1_STATE_OFF      0x1UL
	#घोषणा PORT_LED_QCFG_RESP_LED1_STATE_ON       0x2UL
	#घोषणा PORT_LED_QCFG_RESP_LED1_STATE_BLINK    0x3UL
	#घोषणा PORT_LED_QCFG_RESP_LED1_STATE_BLINKALT 0x4UL
	#घोषणा PORT_LED_QCFG_RESP_LED1_STATE_LAST    PORT_LED_QCFG_RESP_LED1_STATE_BLINKALT
	u8	led1_color;
	#घोषणा PORT_LED_QCFG_RESP_LED1_COLOR_DEFAULT    0x0UL
	#घोषणा PORT_LED_QCFG_RESP_LED1_COLOR_AMBER      0x1UL
	#घोषणा PORT_LED_QCFG_RESP_LED1_COLOR_GREEN      0x2UL
	#घोषणा PORT_LED_QCFG_RESP_LED1_COLOR_GREENAMBER 0x3UL
	#घोषणा PORT_LED_QCFG_RESP_LED1_COLOR_LAST      PORT_LED_QCFG_RESP_LED1_COLOR_GREENAMBER
	u8	unused_1;
	__le16	led1_blink_on;
	__le16	led1_blink_off;
	u8	led1_group_id;
	u8	led2_id;
	u8	led2_type;
	#घोषणा PORT_LED_QCFG_RESP_LED2_TYPE_SPEED    0x0UL
	#घोषणा PORT_LED_QCFG_RESP_LED2_TYPE_ACTIVITY 0x1UL
	#घोषणा PORT_LED_QCFG_RESP_LED2_TYPE_INVALID  0xffUL
	#घोषणा PORT_LED_QCFG_RESP_LED2_TYPE_LAST    PORT_LED_QCFG_RESP_LED2_TYPE_INVALID
	u8	led2_state;
	#घोषणा PORT_LED_QCFG_RESP_LED2_STATE_DEFAULT  0x0UL
	#घोषणा PORT_LED_QCFG_RESP_LED2_STATE_OFF      0x1UL
	#घोषणा PORT_LED_QCFG_RESP_LED2_STATE_ON       0x2UL
	#घोषणा PORT_LED_QCFG_RESP_LED2_STATE_BLINK    0x3UL
	#घोषणा PORT_LED_QCFG_RESP_LED2_STATE_BLINKALT 0x4UL
	#घोषणा PORT_LED_QCFG_RESP_LED2_STATE_LAST    PORT_LED_QCFG_RESP_LED2_STATE_BLINKALT
	u8	led2_color;
	#घोषणा PORT_LED_QCFG_RESP_LED2_COLOR_DEFAULT    0x0UL
	#घोषणा PORT_LED_QCFG_RESP_LED2_COLOR_AMBER      0x1UL
	#घोषणा PORT_LED_QCFG_RESP_LED2_COLOR_GREEN      0x2UL
	#घोषणा PORT_LED_QCFG_RESP_LED2_COLOR_GREENAMBER 0x3UL
	#घोषणा PORT_LED_QCFG_RESP_LED2_COLOR_LAST      PORT_LED_QCFG_RESP_LED2_COLOR_GREENAMBER
	u8	unused_2;
	__le16	led2_blink_on;
	__le16	led2_blink_off;
	u8	led2_group_id;
	u8	led3_id;
	u8	led3_type;
	#घोषणा PORT_LED_QCFG_RESP_LED3_TYPE_SPEED    0x0UL
	#घोषणा PORT_LED_QCFG_RESP_LED3_TYPE_ACTIVITY 0x1UL
	#घोषणा PORT_LED_QCFG_RESP_LED3_TYPE_INVALID  0xffUL
	#घोषणा PORT_LED_QCFG_RESP_LED3_TYPE_LAST    PORT_LED_QCFG_RESP_LED3_TYPE_INVALID
	u8	led3_state;
	#घोषणा PORT_LED_QCFG_RESP_LED3_STATE_DEFAULT  0x0UL
	#घोषणा PORT_LED_QCFG_RESP_LED3_STATE_OFF      0x1UL
	#घोषणा PORT_LED_QCFG_RESP_LED3_STATE_ON       0x2UL
	#घोषणा PORT_LED_QCFG_RESP_LED3_STATE_BLINK    0x3UL
	#घोषणा PORT_LED_QCFG_RESP_LED3_STATE_BLINKALT 0x4UL
	#घोषणा PORT_LED_QCFG_RESP_LED3_STATE_LAST    PORT_LED_QCFG_RESP_LED3_STATE_BLINKALT
	u8	led3_color;
	#घोषणा PORT_LED_QCFG_RESP_LED3_COLOR_DEFAULT    0x0UL
	#घोषणा PORT_LED_QCFG_RESP_LED3_COLOR_AMBER      0x1UL
	#घोषणा PORT_LED_QCFG_RESP_LED3_COLOR_GREEN      0x2UL
	#घोषणा PORT_LED_QCFG_RESP_LED3_COLOR_GREENAMBER 0x3UL
	#घोषणा PORT_LED_QCFG_RESP_LED3_COLOR_LAST      PORT_LED_QCFG_RESP_LED3_COLOR_GREENAMBER
	u8	unused_3;
	__le16	led3_blink_on;
	__le16	led3_blink_off;
	u8	led3_group_id;
	u8	unused_4[6];
	u8	valid;
पूर्ण;

/* hwrm_port_led_qcaps_input (size:192b/24B) */
काष्ठा hwrm_port_led_qcaps_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	port_id;
	u8	unused_0[6];
पूर्ण;

/* hwrm_port_led_qcaps_output (size:384b/48B) */
काष्ठा hwrm_port_led_qcaps_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	num_leds;
	u8	unused[3];
	u8	led0_id;
	u8	led0_type;
	#घोषणा PORT_LED_QCAPS_RESP_LED0_TYPE_SPEED    0x0UL
	#घोषणा PORT_LED_QCAPS_RESP_LED0_TYPE_ACTIVITY 0x1UL
	#घोषणा PORT_LED_QCAPS_RESP_LED0_TYPE_INVALID  0xffUL
	#घोषणा PORT_LED_QCAPS_RESP_LED0_TYPE_LAST    PORT_LED_QCAPS_RESP_LED0_TYPE_INVALID
	u8	led0_group_id;
	u8	unused_0;
	__le16	led0_state_caps;
	#घोषणा PORT_LED_QCAPS_RESP_LED0_STATE_CAPS_ENABLED                 0x1UL
	#घोषणा PORT_LED_QCAPS_RESP_LED0_STATE_CAPS_OFF_SUPPORTED           0x2UL
	#घोषणा PORT_LED_QCAPS_RESP_LED0_STATE_CAPS_ON_SUPPORTED            0x4UL
	#घोषणा PORT_LED_QCAPS_RESP_LED0_STATE_CAPS_BLINK_SUPPORTED         0x8UL
	#घोषणा PORT_LED_QCAPS_RESP_LED0_STATE_CAPS_BLINK_ALT_SUPPORTED     0x10UL
	__le16	led0_color_caps;
	#घोषणा PORT_LED_QCAPS_RESP_LED0_COLOR_CAPS_RSVD                0x1UL
	#घोषणा PORT_LED_QCAPS_RESP_LED0_COLOR_CAPS_AMBER_SUPPORTED     0x2UL
	#घोषणा PORT_LED_QCAPS_RESP_LED0_COLOR_CAPS_GREEN_SUPPORTED     0x4UL
	u8	led1_id;
	u8	led1_type;
	#घोषणा PORT_LED_QCAPS_RESP_LED1_TYPE_SPEED    0x0UL
	#घोषणा PORT_LED_QCAPS_RESP_LED1_TYPE_ACTIVITY 0x1UL
	#घोषणा PORT_LED_QCAPS_RESP_LED1_TYPE_INVALID  0xffUL
	#घोषणा PORT_LED_QCAPS_RESP_LED1_TYPE_LAST    PORT_LED_QCAPS_RESP_LED1_TYPE_INVALID
	u8	led1_group_id;
	u8	unused_1;
	__le16	led1_state_caps;
	#घोषणा PORT_LED_QCAPS_RESP_LED1_STATE_CAPS_ENABLED                 0x1UL
	#घोषणा PORT_LED_QCAPS_RESP_LED1_STATE_CAPS_OFF_SUPPORTED           0x2UL
	#घोषणा PORT_LED_QCAPS_RESP_LED1_STATE_CAPS_ON_SUPPORTED            0x4UL
	#घोषणा PORT_LED_QCAPS_RESP_LED1_STATE_CAPS_BLINK_SUPPORTED         0x8UL
	#घोषणा PORT_LED_QCAPS_RESP_LED1_STATE_CAPS_BLINK_ALT_SUPPORTED     0x10UL
	__le16	led1_color_caps;
	#घोषणा PORT_LED_QCAPS_RESP_LED1_COLOR_CAPS_RSVD                0x1UL
	#घोषणा PORT_LED_QCAPS_RESP_LED1_COLOR_CAPS_AMBER_SUPPORTED     0x2UL
	#घोषणा PORT_LED_QCAPS_RESP_LED1_COLOR_CAPS_GREEN_SUPPORTED     0x4UL
	u8	led2_id;
	u8	led2_type;
	#घोषणा PORT_LED_QCAPS_RESP_LED2_TYPE_SPEED    0x0UL
	#घोषणा PORT_LED_QCAPS_RESP_LED2_TYPE_ACTIVITY 0x1UL
	#घोषणा PORT_LED_QCAPS_RESP_LED2_TYPE_INVALID  0xffUL
	#घोषणा PORT_LED_QCAPS_RESP_LED2_TYPE_LAST    PORT_LED_QCAPS_RESP_LED2_TYPE_INVALID
	u8	led2_group_id;
	u8	unused_2;
	__le16	led2_state_caps;
	#घोषणा PORT_LED_QCAPS_RESP_LED2_STATE_CAPS_ENABLED                 0x1UL
	#घोषणा PORT_LED_QCAPS_RESP_LED2_STATE_CAPS_OFF_SUPPORTED           0x2UL
	#घोषणा PORT_LED_QCAPS_RESP_LED2_STATE_CAPS_ON_SUPPORTED            0x4UL
	#घोषणा PORT_LED_QCAPS_RESP_LED2_STATE_CAPS_BLINK_SUPPORTED         0x8UL
	#घोषणा PORT_LED_QCAPS_RESP_LED2_STATE_CAPS_BLINK_ALT_SUPPORTED     0x10UL
	__le16	led2_color_caps;
	#घोषणा PORT_LED_QCAPS_RESP_LED2_COLOR_CAPS_RSVD                0x1UL
	#घोषणा PORT_LED_QCAPS_RESP_LED2_COLOR_CAPS_AMBER_SUPPORTED     0x2UL
	#घोषणा PORT_LED_QCAPS_RESP_LED2_COLOR_CAPS_GREEN_SUPPORTED     0x4UL
	u8	led3_id;
	u8	led3_type;
	#घोषणा PORT_LED_QCAPS_RESP_LED3_TYPE_SPEED    0x0UL
	#घोषणा PORT_LED_QCAPS_RESP_LED3_TYPE_ACTIVITY 0x1UL
	#घोषणा PORT_LED_QCAPS_RESP_LED3_TYPE_INVALID  0xffUL
	#घोषणा PORT_LED_QCAPS_RESP_LED3_TYPE_LAST    PORT_LED_QCAPS_RESP_LED3_TYPE_INVALID
	u8	led3_group_id;
	u8	unused_3;
	__le16	led3_state_caps;
	#घोषणा PORT_LED_QCAPS_RESP_LED3_STATE_CAPS_ENABLED                 0x1UL
	#घोषणा PORT_LED_QCAPS_RESP_LED3_STATE_CAPS_OFF_SUPPORTED           0x2UL
	#घोषणा PORT_LED_QCAPS_RESP_LED3_STATE_CAPS_ON_SUPPORTED            0x4UL
	#घोषणा PORT_LED_QCAPS_RESP_LED3_STATE_CAPS_BLINK_SUPPORTED         0x8UL
	#घोषणा PORT_LED_QCAPS_RESP_LED3_STATE_CAPS_BLINK_ALT_SUPPORTED     0x10UL
	__le16	led3_color_caps;
	#घोषणा PORT_LED_QCAPS_RESP_LED3_COLOR_CAPS_RSVD                0x1UL
	#घोषणा PORT_LED_QCAPS_RESP_LED3_COLOR_CAPS_AMBER_SUPPORTED     0x2UL
	#घोषणा PORT_LED_QCAPS_RESP_LED3_COLOR_CAPS_GREEN_SUPPORTED     0x4UL
	u8	unused_4[3];
	u8	valid;
पूर्ण;

/* hwrm_queue_qportcfg_input (size:192b/24B) */
काष्ठा hwrm_queue_qportcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा QUEUE_QPORTCFG_REQ_FLAGS_PATH     0x1UL
	#घोषणा QUEUE_QPORTCFG_REQ_FLAGS_PATH_TX    0x0UL
	#घोषणा QUEUE_QPORTCFG_REQ_FLAGS_PATH_RX    0x1UL
	#घोषणा QUEUE_QPORTCFG_REQ_FLAGS_PATH_LAST QUEUE_QPORTCFG_REQ_FLAGS_PATH_RX
	__le16	port_id;
	u8	drv_qmap_cap;
	#घोषणा QUEUE_QPORTCFG_REQ_DRV_QMAP_CAP_DISABLED 0x0UL
	#घोषणा QUEUE_QPORTCFG_REQ_DRV_QMAP_CAP_ENABLED  0x1UL
	#घोषणा QUEUE_QPORTCFG_REQ_DRV_QMAP_CAP_LAST    QUEUE_QPORTCFG_REQ_DRV_QMAP_CAP_ENABLED
	u8	unused_0;
पूर्ण;

/* hwrm_queue_qportcfg_output (size:1344b/168B) */
काष्ठा hwrm_queue_qportcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	max_configurable_queues;
	u8	max_configurable_lossless_queues;
	u8	queue_cfg_allowed;
	u8	queue_cfg_info;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_CFG_INFO_ASYM_CFG     0x1UL
	u8	queue_pfcenable_cfg_allowed;
	u8	queue_pri2cos_cfg_allowed;
	u8	queue_cos2bw_cfg_allowed;
	u8	queue_id0;
	u8	queue_id0_service_profile;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID0_SERVICE_PROखाता_LOSSY          0x0UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID0_SERVICE_PROखाता_LOSSLESS       0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID0_SERVICE_PROखाता_LOSSLESS_ROCE  0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID0_SERVICE_PROखाता_LOSSY_ROCE_CNP 0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID0_SERVICE_PROखाता_LOSSLESS_NIC   0x3UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID0_SERVICE_PROखाता_UNKNOWN        0xffUL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID0_SERVICE_PROखाता_LAST          QUEUE_QPORTCFG_RESP_QUEUE_ID0_SERVICE_PROखाता_UNKNOWN
	u8	queue_id1;
	u8	queue_id1_service_profile;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID1_SERVICE_PROखाता_LOSSY          0x0UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID1_SERVICE_PROखाता_LOSSLESS       0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID1_SERVICE_PROखाता_LOSSLESS_ROCE  0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID1_SERVICE_PROखाता_LOSSY_ROCE_CNP 0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID1_SERVICE_PROखाता_LOSSLESS_NIC   0x3UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID1_SERVICE_PROखाता_UNKNOWN        0xffUL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID1_SERVICE_PROखाता_LAST          QUEUE_QPORTCFG_RESP_QUEUE_ID1_SERVICE_PROखाता_UNKNOWN
	u8	queue_id2;
	u8	queue_id2_service_profile;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID2_SERVICE_PROखाता_LOSSY          0x0UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID2_SERVICE_PROखाता_LOSSLESS       0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID2_SERVICE_PROखाता_LOSSLESS_ROCE  0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID2_SERVICE_PROखाता_LOSSY_ROCE_CNP 0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID2_SERVICE_PROखाता_LOSSLESS_NIC   0x3UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID2_SERVICE_PROखाता_UNKNOWN        0xffUL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID2_SERVICE_PROखाता_LAST          QUEUE_QPORTCFG_RESP_QUEUE_ID2_SERVICE_PROखाता_UNKNOWN
	u8	queue_id3;
	u8	queue_id3_service_profile;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID3_SERVICE_PROखाता_LOSSY          0x0UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID3_SERVICE_PROखाता_LOSSLESS       0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID3_SERVICE_PROखाता_LOSSLESS_ROCE  0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID3_SERVICE_PROखाता_LOSSY_ROCE_CNP 0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID3_SERVICE_PROखाता_LOSSLESS_NIC   0x3UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID3_SERVICE_PROखाता_UNKNOWN        0xffUL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID3_SERVICE_PROखाता_LAST          QUEUE_QPORTCFG_RESP_QUEUE_ID3_SERVICE_PROखाता_UNKNOWN
	u8	queue_id4;
	u8	queue_id4_service_profile;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID4_SERVICE_PROखाता_LOSSY          0x0UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID4_SERVICE_PROखाता_LOSSLESS       0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID4_SERVICE_PROखाता_LOSSLESS_ROCE  0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID4_SERVICE_PROखाता_LOSSY_ROCE_CNP 0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID4_SERVICE_PROखाता_LOSSLESS_NIC   0x3UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID4_SERVICE_PROखाता_UNKNOWN        0xffUL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID4_SERVICE_PROखाता_LAST          QUEUE_QPORTCFG_RESP_QUEUE_ID4_SERVICE_PROखाता_UNKNOWN
	u8	queue_id5;
	u8	queue_id5_service_profile;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID5_SERVICE_PROखाता_LOSSY          0x0UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID5_SERVICE_PROखाता_LOSSLESS       0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID5_SERVICE_PROखाता_LOSSLESS_ROCE  0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID5_SERVICE_PROखाता_LOSSY_ROCE_CNP 0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID5_SERVICE_PROखाता_LOSSLESS_NIC   0x3UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID5_SERVICE_PROखाता_UNKNOWN        0xffUL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID5_SERVICE_PROखाता_LAST          QUEUE_QPORTCFG_RESP_QUEUE_ID5_SERVICE_PROखाता_UNKNOWN
	u8	queue_id6;
	u8	queue_id6_service_profile;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID6_SERVICE_PROखाता_LOSSY          0x0UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID6_SERVICE_PROखाता_LOSSLESS       0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID6_SERVICE_PROखाता_LOSSLESS_ROCE  0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID6_SERVICE_PROखाता_LOSSY_ROCE_CNP 0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID6_SERVICE_PROखाता_LOSSLESS_NIC   0x3UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID6_SERVICE_PROखाता_UNKNOWN        0xffUL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID6_SERVICE_PROखाता_LAST          QUEUE_QPORTCFG_RESP_QUEUE_ID6_SERVICE_PROखाता_UNKNOWN
	u8	queue_id7;
	u8	queue_id7_service_profile;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID7_SERVICE_PROखाता_LOSSY          0x0UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID7_SERVICE_PROखाता_LOSSLESS       0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID7_SERVICE_PROखाता_LOSSLESS_ROCE  0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID7_SERVICE_PROखाता_LOSSY_ROCE_CNP 0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID7_SERVICE_PROखाता_LOSSLESS_NIC   0x3UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID7_SERVICE_PROखाता_UNKNOWN        0xffUL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID7_SERVICE_PROखाता_LAST          QUEUE_QPORTCFG_RESP_QUEUE_ID7_SERVICE_PROखाता_UNKNOWN
	u8	queue_id0_service_profile_type;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID0_SERVICE_PROखाता_TYPE_ROCE     0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID0_SERVICE_PROखाता_TYPE_NIC      0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID0_SERVICE_PROखाता_TYPE_CNP      0x4UL
	अक्षर	qid0_name[16];
	अक्षर	qid1_name[16];
	अक्षर	qid2_name[16];
	अक्षर	qid3_name[16];
	अक्षर	qid4_name[16];
	अक्षर	qid5_name[16];
	अक्षर	qid6_name[16];
	अक्षर	qid7_name[16];
	u8	queue_id1_service_profile_type;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID1_SERVICE_PROखाता_TYPE_ROCE     0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID1_SERVICE_PROखाता_TYPE_NIC      0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID1_SERVICE_PROखाता_TYPE_CNP      0x4UL
	u8	queue_id2_service_profile_type;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID2_SERVICE_PROखाता_TYPE_ROCE     0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID2_SERVICE_PROखाता_TYPE_NIC      0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID2_SERVICE_PROखाता_TYPE_CNP      0x4UL
	u8	queue_id3_service_profile_type;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID3_SERVICE_PROखाता_TYPE_ROCE     0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID3_SERVICE_PROखाता_TYPE_NIC      0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID3_SERVICE_PROखाता_TYPE_CNP      0x4UL
	u8	queue_id4_service_profile_type;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID4_SERVICE_PROखाता_TYPE_ROCE     0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID4_SERVICE_PROखाता_TYPE_NIC      0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID4_SERVICE_PROखाता_TYPE_CNP      0x4UL
	u8	queue_id5_service_profile_type;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID5_SERVICE_PROखाता_TYPE_ROCE     0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID5_SERVICE_PROखाता_TYPE_NIC      0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID5_SERVICE_PROखाता_TYPE_CNP      0x4UL
	u8	queue_id6_service_profile_type;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID6_SERVICE_PROखाता_TYPE_ROCE     0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID6_SERVICE_PROखाता_TYPE_NIC      0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID6_SERVICE_PROखाता_TYPE_CNP      0x4UL
	u8	queue_id7_service_profile_type;
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID7_SERVICE_PROखाता_TYPE_ROCE     0x1UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID7_SERVICE_PROखाता_TYPE_NIC      0x2UL
	#घोषणा QUEUE_QPORTCFG_RESP_QUEUE_ID7_SERVICE_PROखाता_TYPE_CNP      0x4UL
	u8	valid;
पूर्ण;

/* hwrm_queue_qcfg_input (size:192b/24B) */
काष्ठा hwrm_queue_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा QUEUE_QCFG_REQ_FLAGS_PATH     0x1UL
	#घोषणा QUEUE_QCFG_REQ_FLAGS_PATH_TX    0x0UL
	#घोषणा QUEUE_QCFG_REQ_FLAGS_PATH_RX    0x1UL
	#घोषणा QUEUE_QCFG_REQ_FLAGS_PATH_LAST QUEUE_QCFG_REQ_FLAGS_PATH_RX
	__le32	queue_id;
पूर्ण;

/* hwrm_queue_qcfg_output (size:128b/16B) */
काष्ठा hwrm_queue_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	queue_len;
	u8	service_profile;
	#घोषणा QUEUE_QCFG_RESP_SERVICE_PROखाता_LOSSY    0x0UL
	#घोषणा QUEUE_QCFG_RESP_SERVICE_PROखाता_LOSSLESS 0x1UL
	#घोषणा QUEUE_QCFG_RESP_SERVICE_PROखाता_UNKNOWN  0xffUL
	#घोषणा QUEUE_QCFG_RESP_SERVICE_PROखाता_LAST    QUEUE_QCFG_RESP_SERVICE_PROखाता_UNKNOWN
	u8	queue_cfg_info;
	#घोषणा QUEUE_QCFG_RESP_QUEUE_CFG_INFO_ASYM_CFG     0x1UL
	u8	unused_0;
	u8	valid;
पूर्ण;

/* hwrm_queue_cfg_input (size:320b/40B) */
काष्ठा hwrm_queue_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा QUEUE_CFG_REQ_FLAGS_PATH_MASK 0x3UL
	#घोषणा QUEUE_CFG_REQ_FLAGS_PATH_SFT  0
	#घोषणा QUEUE_CFG_REQ_FLAGS_PATH_TX     0x0UL
	#घोषणा QUEUE_CFG_REQ_FLAGS_PATH_RX     0x1UL
	#घोषणा QUEUE_CFG_REQ_FLAGS_PATH_BIसूची  0x2UL
	#घोषणा QUEUE_CFG_REQ_FLAGS_PATH_LAST  QUEUE_CFG_REQ_FLAGS_PATH_BIसूची
	__le32	enables;
	#घोषणा QUEUE_CFG_REQ_ENABLES_DFLT_LEN            0x1UL
	#घोषणा QUEUE_CFG_REQ_ENABLES_SERVICE_PROखाता     0x2UL
	__le32	queue_id;
	__le32	dflt_len;
	u8	service_profile;
	#घोषणा QUEUE_CFG_REQ_SERVICE_PROखाता_LOSSY    0x0UL
	#घोषणा QUEUE_CFG_REQ_SERVICE_PROखाता_LOSSLESS 0x1UL
	#घोषणा QUEUE_CFG_REQ_SERVICE_PROखाता_UNKNOWN  0xffUL
	#घोषणा QUEUE_CFG_REQ_SERVICE_PROखाता_LAST    QUEUE_CFG_REQ_SERVICE_PROखाता_UNKNOWN
	u8	unused_0[7];
पूर्ण;

/* hwrm_queue_cfg_output (size:128b/16B) */
काष्ठा hwrm_queue_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_queue_pfcenable_qcfg_input (size:192b/24B) */
काष्ठा hwrm_queue_pfcenable_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	port_id;
	u8	unused_0[6];
पूर्ण;

/* hwrm_queue_pfcenable_qcfg_output (size:128b/16B) */
काष्ठा hwrm_queue_pfcenable_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	flags;
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI0_PFC_ENABLED              0x1UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI1_PFC_ENABLED              0x2UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI2_PFC_ENABLED              0x4UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI3_PFC_ENABLED              0x8UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI4_PFC_ENABLED              0x10UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI5_PFC_ENABLED              0x20UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI6_PFC_ENABLED              0x40UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI7_PFC_ENABLED              0x80UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI0_PFC_WATCHDOG_ENABLED     0x100UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI1_PFC_WATCHDOG_ENABLED     0x200UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI2_PFC_WATCHDOG_ENABLED     0x400UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI3_PFC_WATCHDOG_ENABLED     0x800UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI4_PFC_WATCHDOG_ENABLED     0x1000UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI5_PFC_WATCHDOG_ENABLED     0x2000UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI6_PFC_WATCHDOG_ENABLED     0x4000UL
	#घोषणा QUEUE_PFCENABLE_QCFG_RESP_FLAGS_PRI7_PFC_WATCHDOG_ENABLED     0x8000UL
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_queue_pfcenable_cfg_input (size:192b/24B) */
काष्ठा hwrm_queue_pfcenable_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI0_PFC_ENABLED              0x1UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI1_PFC_ENABLED              0x2UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI2_PFC_ENABLED              0x4UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI3_PFC_ENABLED              0x8UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI4_PFC_ENABLED              0x10UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI5_PFC_ENABLED              0x20UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI6_PFC_ENABLED              0x40UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI7_PFC_ENABLED              0x80UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI0_PFC_WATCHDOG_ENABLED     0x100UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI1_PFC_WATCHDOG_ENABLED     0x200UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI2_PFC_WATCHDOG_ENABLED     0x400UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI3_PFC_WATCHDOG_ENABLED     0x800UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI4_PFC_WATCHDOG_ENABLED     0x1000UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI5_PFC_WATCHDOG_ENABLED     0x2000UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI6_PFC_WATCHDOG_ENABLED     0x4000UL
	#घोषणा QUEUE_PFCENABLE_CFG_REQ_FLAGS_PRI7_PFC_WATCHDOG_ENABLED     0x8000UL
	__le16	port_id;
	u8	unused_0[2];
पूर्ण;

/* hwrm_queue_pfcenable_cfg_output (size:128b/16B) */
काष्ठा hwrm_queue_pfcenable_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_queue_pri2cos_qcfg_input (size:192b/24B) */
काष्ठा hwrm_queue_pri2cos_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा QUEUE_PRI2COS_QCFG_REQ_FLAGS_PATH      0x1UL
	#घोषणा QUEUE_PRI2COS_QCFG_REQ_FLAGS_PATH_TX     0x0UL
	#घोषणा QUEUE_PRI2COS_QCFG_REQ_FLAGS_PATH_RX     0x1UL
	#घोषणा QUEUE_PRI2COS_QCFG_REQ_FLAGS_PATH_LAST  QUEUE_PRI2COS_QCFG_REQ_FLAGS_PATH_RX
	#घोषणा QUEUE_PRI2COS_QCFG_REQ_FLAGS_IVLAN     0x2UL
	u8	port_id;
	u8	unused_0[3];
पूर्ण;

/* hwrm_queue_pri2cos_qcfg_output (size:192b/24B) */
काष्ठा hwrm_queue_pri2cos_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	pri0_cos_queue_id;
	u8	pri1_cos_queue_id;
	u8	pri2_cos_queue_id;
	u8	pri3_cos_queue_id;
	u8	pri4_cos_queue_id;
	u8	pri5_cos_queue_id;
	u8	pri6_cos_queue_id;
	u8	pri7_cos_queue_id;
	u8	queue_cfg_info;
	#घोषणा QUEUE_PRI2COS_QCFG_RESP_QUEUE_CFG_INFO_ASYM_CFG     0x1UL
	u8	unused_0[6];
	u8	valid;
पूर्ण;

/* hwrm_queue_pri2cos_cfg_input (size:320b/40B) */
काष्ठा hwrm_queue_pri2cos_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा QUEUE_PRI2COS_CFG_REQ_FLAGS_PATH_MASK 0x3UL
	#घोषणा QUEUE_PRI2COS_CFG_REQ_FLAGS_PATH_SFT  0
	#घोषणा QUEUE_PRI2COS_CFG_REQ_FLAGS_PATH_TX     0x0UL
	#घोषणा QUEUE_PRI2COS_CFG_REQ_FLAGS_PATH_RX     0x1UL
	#घोषणा QUEUE_PRI2COS_CFG_REQ_FLAGS_PATH_BIसूची  0x2UL
	#घोषणा QUEUE_PRI2COS_CFG_REQ_FLAGS_PATH_LAST  QUEUE_PRI2COS_CFG_REQ_FLAGS_PATH_BIसूची
	#घोषणा QUEUE_PRI2COS_CFG_REQ_FLAGS_IVLAN     0x4UL
	__le32	enables;
	#घोषणा QUEUE_PRI2COS_CFG_REQ_ENABLES_PRI0_COS_QUEUE_ID     0x1UL
	#घोषणा QUEUE_PRI2COS_CFG_REQ_ENABLES_PRI1_COS_QUEUE_ID     0x2UL
	#घोषणा QUEUE_PRI2COS_CFG_REQ_ENABLES_PRI2_COS_QUEUE_ID     0x4UL
	#घोषणा QUEUE_PRI2COS_CFG_REQ_ENABLES_PRI3_COS_QUEUE_ID     0x8UL
	#घोषणा QUEUE_PRI2COS_CFG_REQ_ENABLES_PRI4_COS_QUEUE_ID     0x10UL
	#घोषणा QUEUE_PRI2COS_CFG_REQ_ENABLES_PRI5_COS_QUEUE_ID     0x20UL
	#घोषणा QUEUE_PRI2COS_CFG_REQ_ENABLES_PRI6_COS_QUEUE_ID     0x40UL
	#घोषणा QUEUE_PRI2COS_CFG_REQ_ENABLES_PRI7_COS_QUEUE_ID     0x80UL
	u8	port_id;
	u8	pri0_cos_queue_id;
	u8	pri1_cos_queue_id;
	u8	pri2_cos_queue_id;
	u8	pri3_cos_queue_id;
	u8	pri4_cos_queue_id;
	u8	pri5_cos_queue_id;
	u8	pri6_cos_queue_id;
	u8	pri7_cos_queue_id;
	u8	unused_0[7];
पूर्ण;

/* hwrm_queue_pri2cos_cfg_output (size:128b/16B) */
काष्ठा hwrm_queue_pri2cos_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_queue_cos2bw_qcfg_input (size:192b/24B) */
काष्ठा hwrm_queue_cos2bw_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	port_id;
	u8	unused_0[6];
पूर्ण;

/* hwrm_queue_cos2bw_qcfg_output (size:896b/112B) */
काष्ठा hwrm_queue_cos2bw_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	queue_id0;
	u8	unused_0;
	__le16	unused_1;
	__le32	queue_id0_min_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id0_max_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id0_tsa_assign;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID0_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id0_pri_lvl;
	u8	queue_id0_bw_weight;
	u8	queue_id1;
	__le32	queue_id1_min_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id1_max_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id1_tsa_assign;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID1_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id1_pri_lvl;
	u8	queue_id1_bw_weight;
	u8	queue_id2;
	__le32	queue_id2_min_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id2_max_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id2_tsa_assign;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID2_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id2_pri_lvl;
	u8	queue_id2_bw_weight;
	u8	queue_id3;
	__le32	queue_id3_min_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id3_max_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id3_tsa_assign;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID3_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id3_pri_lvl;
	u8	queue_id3_bw_weight;
	u8	queue_id4;
	__le32	queue_id4_min_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id4_max_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id4_tsa_assign;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID4_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id4_pri_lvl;
	u8	queue_id4_bw_weight;
	u8	queue_id5;
	__le32	queue_id5_min_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id5_max_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id5_tsa_assign;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID5_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id5_pri_lvl;
	u8	queue_id5_bw_weight;
	u8	queue_id6;
	__le32	queue_id6_min_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id6_max_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id6_tsa_assign;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID6_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id6_pri_lvl;
	u8	queue_id6_bw_weight;
	u8	queue_id7;
	__le32	queue_id7_min_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id7_max_bw;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id7_tsa_assign;
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_QCFG_RESP_QUEUE_ID7_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id7_pri_lvl;
	u8	queue_id7_bw_weight;
	u8	unused_2[4];
	u8	valid;
पूर्ण;

/* hwrm_queue_cos2bw_cfg_input (size:1024b/128B) */
काष्ठा hwrm_queue_cos2bw_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	__le32	enables;
	#घोषणा QUEUE_COS2BW_CFG_REQ_ENABLES_COS_QUEUE_ID0_VALID     0x1UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_ENABLES_COS_QUEUE_ID1_VALID     0x2UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_ENABLES_COS_QUEUE_ID2_VALID     0x4UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_ENABLES_COS_QUEUE_ID3_VALID     0x8UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_ENABLES_COS_QUEUE_ID4_VALID     0x10UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_ENABLES_COS_QUEUE_ID5_VALID     0x20UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_ENABLES_COS_QUEUE_ID6_VALID     0x40UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_ENABLES_COS_QUEUE_ID7_VALID     0x80UL
	__le16	port_id;
	u8	queue_id0;
	u8	unused_0;
	__le32	queue_id0_min_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id0_max_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id0_tsa_assign;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID0_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id0_pri_lvl;
	u8	queue_id0_bw_weight;
	u8	queue_id1;
	__le32	queue_id1_min_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id1_max_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id1_tsa_assign;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID1_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id1_pri_lvl;
	u8	queue_id1_bw_weight;
	u8	queue_id2;
	__le32	queue_id2_min_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id2_max_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id2_tsa_assign;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID2_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id2_pri_lvl;
	u8	queue_id2_bw_weight;
	u8	queue_id3;
	__le32	queue_id3_min_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id3_max_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id3_tsa_assign;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID3_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id3_pri_lvl;
	u8	queue_id3_bw_weight;
	u8	queue_id4;
	__le32	queue_id4_min_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id4_max_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id4_tsa_assign;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID4_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id4_pri_lvl;
	u8	queue_id4_bw_weight;
	u8	queue_id5;
	__le32	queue_id5_min_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id5_max_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id5_tsa_assign;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID5_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id5_pri_lvl;
	u8	queue_id5_bw_weight;
	u8	queue_id6;
	__le32	queue_id6_min_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id6_max_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id6_tsa_assign;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID6_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id6_pri_lvl;
	u8	queue_id6_bw_weight;
	u8	queue_id7;
	__le32	queue_id7_min_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MIN_BW_BW_VALUE_UNIT_INVALID
	__le32	queue_id7_max_bw;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_BW_VALUE_SFT              0
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_SCALE                     0x10000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_SCALE_LAST                 QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_SCALE_BYTES
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_LAST         QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	queue_id7_tsa_assign;
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_TSA_ASSIGN_SP             0x0UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_TSA_ASSIGN_ETS            0x1UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_TSA_ASSIGN_RESERVED_FIRST 0x2UL
	#घोषणा QUEUE_COS2BW_CFG_REQ_QUEUE_ID7_TSA_ASSIGN_RESERVED_LAST  0xffUL
	u8	queue_id7_pri_lvl;
	u8	queue_id7_bw_weight;
	u8	unused_1[5];
पूर्ण;

/* hwrm_queue_cos2bw_cfg_output (size:128b/16B) */
काष्ठा hwrm_queue_cos2bw_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_queue_dscp_qcaps_input (size:192b/24B) */
काष्ठा hwrm_queue_dscp_qcaps_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	u8	port_id;
	u8	unused_0[7];
पूर्ण;

/* hwrm_queue_dscp_qcaps_output (size:128b/16B) */
काष्ठा hwrm_queue_dscp_qcaps_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	num_dscp_bits;
	u8	unused_0;
	__le16	max_entries;
	u8	unused_1[3];
	u8	valid;
पूर्ण;

/* hwrm_queue_dscp2pri_qcfg_input (size:256b/32B) */
काष्ठा hwrm_queue_dscp2pri_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	dest_data_addr;
	u8	port_id;
	u8	unused_0;
	__le16	dest_data_buffer_size;
	u8	unused_1[4];
पूर्ण;

/* hwrm_queue_dscp2pri_qcfg_output (size:128b/16B) */
काष्ठा hwrm_queue_dscp2pri_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	entry_cnt;
	u8	शेष_pri;
	u8	unused_0[4];
	u8	valid;
पूर्ण;

/* hwrm_queue_dscp2pri_cfg_input (size:320b/40B) */
काष्ठा hwrm_queue_dscp2pri_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	src_data_addr;
	__le32	flags;
	#घोषणा QUEUE_DSCP2PRI_CFG_REQ_FLAGS_USE_HW_DEFAULT_PRI     0x1UL
	__le32	enables;
	#घोषणा QUEUE_DSCP2PRI_CFG_REQ_ENABLES_DEFAULT_PRI     0x1UL
	u8	port_id;
	u8	शेष_pri;
	__le16	entry_cnt;
	u8	unused_0[4];
पूर्ण;

/* hwrm_queue_dscp2pri_cfg_output (size:128b/16B) */
काष्ठा hwrm_queue_dscp2pri_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_vnic_alloc_input (size:192b/24B) */
काष्ठा hwrm_vnic_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा VNIC_ALLOC_REQ_FLAGS_DEFAULT                  0x1UL
	#घोषणा VNIC_ALLOC_REQ_FLAGS_VIRTIO_NET_FID_VALID     0x2UL
	__le16	virtio_net_fid;
	u8	unused_0[2];
पूर्ण;

/* hwrm_vnic_alloc_output (size:128b/16B) */
काष्ठा hwrm_vnic_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	vnic_id;
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_vnic_मुक्त_input (size:192b/24B) */
काष्ठा hwrm_vnic_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	vnic_id;
	u8	unused_0[4];
पूर्ण;

/* hwrm_vnic_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_vnic_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_vnic_cfg_input (size:384b/48B) */
काष्ठा hwrm_vnic_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा VNIC_CFG_REQ_FLAGS_DEFAULT                              0x1UL
	#घोषणा VNIC_CFG_REQ_FLAGS_VLAN_STRIP_MODE                      0x2UL
	#घोषणा VNIC_CFG_REQ_FLAGS_BD_STALL_MODE                        0x4UL
	#घोषणा VNIC_CFG_REQ_FLAGS_ROCE_DUAL_VNIC_MODE                  0x8UL
	#घोषणा VNIC_CFG_REQ_FLAGS_ROCE_ONLY_VNIC_MODE                  0x10UL
	#घोषणा VNIC_CFG_REQ_FLAGS_RSS_DFLT_CR_MODE                     0x20UL
	#घोषणा VNIC_CFG_REQ_FLAGS_ROCE_MIRRORING_CAPABLE_VNIC_MODE     0x40UL
	__le32	enables;
	#घोषणा VNIC_CFG_REQ_ENABLES_DFLT_RING_GRP            0x1UL
	#घोषणा VNIC_CFG_REQ_ENABLES_RSS_RULE                 0x2UL
	#घोषणा VNIC_CFG_REQ_ENABLES_COS_RULE                 0x4UL
	#घोषणा VNIC_CFG_REQ_ENABLES_LB_RULE                  0x8UL
	#घोषणा VNIC_CFG_REQ_ENABLES_MRU                      0x10UL
	#घोषणा VNIC_CFG_REQ_ENABLES_DEFAULT_RX_RING_ID       0x20UL
	#घोषणा VNIC_CFG_REQ_ENABLES_DEFAULT_CMPL_RING_ID     0x40UL
	#घोषणा VNIC_CFG_REQ_ENABLES_QUEUE_ID                 0x80UL
	#घोषणा VNIC_CFG_REQ_ENABLES_RX_CSUM_V2_MODE          0x100UL
	__le16	vnic_id;
	__le16	dflt_ring_grp;
	__le16	rss_rule;
	__le16	cos_rule;
	__le16	lb_rule;
	__le16	mru;
	__le16	शेष_rx_ring_id;
	__le16	शेष_cmpl_ring_id;
	__le16	queue_id;
	u8	rx_csum_v2_mode;
	#घोषणा VNIC_CFG_REQ_RX_CSUM_V2_MODE_DEFAULT 0x0UL
	#घोषणा VNIC_CFG_REQ_RX_CSUM_V2_MODE_ALL_OK  0x1UL
	#घोषणा VNIC_CFG_REQ_RX_CSUM_V2_MODE_MAX     0x2UL
	#घोषणा VNIC_CFG_REQ_RX_CSUM_V2_MODE_LAST   VNIC_CFG_REQ_RX_CSUM_V2_MODE_MAX
	u8	unused0[5];
पूर्ण;

/* hwrm_vnic_cfg_output (size:128b/16B) */
काष्ठा hwrm_vnic_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_vnic_qcaps_input (size:192b/24B) */
काष्ठा hwrm_vnic_qcaps_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	enables;
	u8	unused_0[4];
पूर्ण;

/* hwrm_vnic_qcaps_output (size:192b/24B) */
काष्ठा hwrm_vnic_qcaps_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	mru;
	u8	unused_0[2];
	__le32	flags;
	#घोषणा VNIC_QCAPS_RESP_FLAGS_UNUSED                              0x1UL
	#घोषणा VNIC_QCAPS_RESP_FLAGS_VLAN_STRIP_CAP                      0x2UL
	#घोषणा VNIC_QCAPS_RESP_FLAGS_BD_STALL_CAP                        0x4UL
	#घोषणा VNIC_QCAPS_RESP_FLAGS_ROCE_DUAL_VNIC_CAP                  0x8UL
	#घोषणा VNIC_QCAPS_RESP_FLAGS_ROCE_ONLY_VNIC_CAP                  0x10UL
	#घोषणा VNIC_QCAPS_RESP_FLAGS_RSS_DFLT_CR_CAP                     0x20UL
	#घोषणा VNIC_QCAPS_RESP_FLAGS_ROCE_MIRRORING_CAPABLE_VNIC_CAP     0x40UL
	#घोषणा VNIC_QCAPS_RESP_FLAGS_OUTERMOST_RSS_CAP                   0x80UL
	#घोषणा VNIC_QCAPS_RESP_FLAGS_COS_ASSIGNMENT_CAP                  0x100UL
	#घोषणा VNIC_QCAPS_RESP_FLAGS_RX_CMPL_V2_CAP                      0x200UL
	#घोषणा VNIC_QCAPS_RESP_FLAGS_VNIC_STATE_CAP                      0x400UL
	#घोषणा VNIC_QCAPS_RESP_FLAGS_VIRTIO_NET_VNIC_ALLOC_CAP           0x800UL
	#घोषणा VNIC_QCAPS_RESP_FLAGS_METADATA_FORMAT_CAP                 0x1000UL
	__le16	max_aggs_supported;
	u8	unused_1[5];
	u8	valid;
पूर्ण;

/* hwrm_vnic_tpa_cfg_input (size:320b/40B) */
काष्ठा hwrm_vnic_tpa_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा VNIC_TPA_CFG_REQ_FLAGS_TPA                       0x1UL
	#घोषणा VNIC_TPA_CFG_REQ_FLAGS_ENCAP_TPA                 0x2UL
	#घोषणा VNIC_TPA_CFG_REQ_FLAGS_RSC_WND_UPDATE            0x4UL
	#घोषणा VNIC_TPA_CFG_REQ_FLAGS_GRO                       0x8UL
	#घोषणा VNIC_TPA_CFG_REQ_FLAGS_AGG_WITH_ECN              0x10UL
	#घोषणा VNIC_TPA_CFG_REQ_FLAGS_AGG_WITH_SAME_GRE_SEQ     0x20UL
	#घोषणा VNIC_TPA_CFG_REQ_FLAGS_GRO_IPID_CHECK            0x40UL
	#घोषणा VNIC_TPA_CFG_REQ_FLAGS_GRO_TTL_CHECK             0x80UL
	#घोषणा VNIC_TPA_CFG_REQ_FLAGS_AGG_PACK_AS_GRO           0x100UL
	__le32	enables;
	#घोषणा VNIC_TPA_CFG_REQ_ENABLES_MAX_AGG_SEGS      0x1UL
	#घोषणा VNIC_TPA_CFG_REQ_ENABLES_MAX_AGGS          0x2UL
	#घोषणा VNIC_TPA_CFG_REQ_ENABLES_MAX_AGG_TIMER     0x4UL
	#घोषणा VNIC_TPA_CFG_REQ_ENABLES_MIN_AGG_LEN       0x8UL
	__le16	vnic_id;
	__le16	max_agg_segs;
	#घोषणा VNIC_TPA_CFG_REQ_MAX_AGG_SEGS_1   0x0UL
	#घोषणा VNIC_TPA_CFG_REQ_MAX_AGG_SEGS_2   0x1UL
	#घोषणा VNIC_TPA_CFG_REQ_MAX_AGG_SEGS_4   0x2UL
	#घोषणा VNIC_TPA_CFG_REQ_MAX_AGG_SEGS_8   0x3UL
	#घोषणा VNIC_TPA_CFG_REQ_MAX_AGG_SEGS_MAX 0x1fUL
	#घोषणा VNIC_TPA_CFG_REQ_MAX_AGG_SEGS_LAST VNIC_TPA_CFG_REQ_MAX_AGG_SEGS_MAX
	__le16	max_aggs;
	#घोषणा VNIC_TPA_CFG_REQ_MAX_AGGS_1   0x0UL
	#घोषणा VNIC_TPA_CFG_REQ_MAX_AGGS_2   0x1UL
	#घोषणा VNIC_TPA_CFG_REQ_MAX_AGGS_4   0x2UL
	#घोषणा VNIC_TPA_CFG_REQ_MAX_AGGS_8   0x3UL
	#घोषणा VNIC_TPA_CFG_REQ_MAX_AGGS_16  0x4UL
	#घोषणा VNIC_TPA_CFG_REQ_MAX_AGGS_MAX 0x7UL
	#घोषणा VNIC_TPA_CFG_REQ_MAX_AGGS_LAST VNIC_TPA_CFG_REQ_MAX_AGGS_MAX
	u8	unused_0[2];
	__le32	max_agg_समयr;
	__le32	min_agg_len;
पूर्ण;

/* hwrm_vnic_tpa_cfg_output (size:128b/16B) */
काष्ठा hwrm_vnic_tpa_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_vnic_tpa_qcfg_input (size:192b/24B) */
काष्ठा hwrm_vnic_tpa_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	vnic_id;
	u8	unused_0[6];
पूर्ण;

/* hwrm_vnic_tpa_qcfg_output (size:256b/32B) */
काष्ठा hwrm_vnic_tpa_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	flags;
	#घोषणा VNIC_TPA_QCFG_RESP_FLAGS_TPA                       0x1UL
	#घोषणा VNIC_TPA_QCFG_RESP_FLAGS_ENCAP_TPA                 0x2UL
	#घोषणा VNIC_TPA_QCFG_RESP_FLAGS_RSC_WND_UPDATE            0x4UL
	#घोषणा VNIC_TPA_QCFG_RESP_FLAGS_GRO                       0x8UL
	#घोषणा VNIC_TPA_QCFG_RESP_FLAGS_AGG_WITH_ECN              0x10UL
	#घोषणा VNIC_TPA_QCFG_RESP_FLAGS_AGG_WITH_SAME_GRE_SEQ     0x20UL
	#घोषणा VNIC_TPA_QCFG_RESP_FLAGS_GRO_IPID_CHECK            0x40UL
	#घोषणा VNIC_TPA_QCFG_RESP_FLAGS_GRO_TTL_CHECK             0x80UL
	__le16	max_agg_segs;
	#घोषणा VNIC_TPA_QCFG_RESP_MAX_AGG_SEGS_1   0x0UL
	#घोषणा VNIC_TPA_QCFG_RESP_MAX_AGG_SEGS_2   0x1UL
	#घोषणा VNIC_TPA_QCFG_RESP_MAX_AGG_SEGS_4   0x2UL
	#घोषणा VNIC_TPA_QCFG_RESP_MAX_AGG_SEGS_8   0x3UL
	#घोषणा VNIC_TPA_QCFG_RESP_MAX_AGG_SEGS_MAX 0x1fUL
	#घोषणा VNIC_TPA_QCFG_RESP_MAX_AGG_SEGS_LAST VNIC_TPA_QCFG_RESP_MAX_AGG_SEGS_MAX
	__le16	max_aggs;
	#घोषणा VNIC_TPA_QCFG_RESP_MAX_AGGS_1   0x0UL
	#घोषणा VNIC_TPA_QCFG_RESP_MAX_AGGS_2   0x1UL
	#घोषणा VNIC_TPA_QCFG_RESP_MAX_AGGS_4   0x2UL
	#घोषणा VNIC_TPA_QCFG_RESP_MAX_AGGS_8   0x3UL
	#घोषणा VNIC_TPA_QCFG_RESP_MAX_AGGS_16  0x4UL
	#घोषणा VNIC_TPA_QCFG_RESP_MAX_AGGS_MAX 0x7UL
	#घोषणा VNIC_TPA_QCFG_RESP_MAX_AGGS_LAST VNIC_TPA_QCFG_RESP_MAX_AGGS_MAX
	__le32	max_agg_समयr;
	__le32	min_agg_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_vnic_rss_cfg_input (size:384b/48B) */
काष्ठा hwrm_vnic_rss_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	hash_type;
	#घोषणा VNIC_RSS_CFG_REQ_HASH_TYPE_IPV4         0x1UL
	#घोषणा VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV4     0x2UL
	#घोषणा VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV4     0x4UL
	#घोषणा VNIC_RSS_CFG_REQ_HASH_TYPE_IPV6         0x8UL
	#घोषणा VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV6     0x10UL
	#घोषणा VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV6     0x20UL
	__le16	vnic_id;
	u8	ring_table_pair_index;
	u8	hash_mode_flags;
	#घोषणा VNIC_RSS_CFG_REQ_HASH_MODE_FLAGS_DEFAULT         0x1UL
	#घोषणा VNIC_RSS_CFG_REQ_HASH_MODE_FLAGS_INNERMOST_4     0x2UL
	#घोषणा VNIC_RSS_CFG_REQ_HASH_MODE_FLAGS_INNERMOST_2     0x4UL
	#घोषणा VNIC_RSS_CFG_REQ_HASH_MODE_FLAGS_OUTERMOST_4     0x8UL
	#घोषणा VNIC_RSS_CFG_REQ_HASH_MODE_FLAGS_OUTERMOST_2     0x10UL
	__le64	ring_grp_tbl_addr;
	__le64	hash_key_tbl_addr;
	__le16	rss_ctx_idx;
	u8	unused_1[6];
पूर्ण;

/* hwrm_vnic_rss_cfg_output (size:128b/16B) */
काष्ठा hwrm_vnic_rss_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_vnic_rss_cfg_cmd_err (size:64b/8B) */
काष्ठा hwrm_vnic_rss_cfg_cmd_err अणु
	u8	code;
	#घोषणा VNIC_RSS_CFG_CMD_ERR_CODE_UNKNOWN             0x0UL
	#घोषणा VNIC_RSS_CFG_CMD_ERR_CODE_INTERFACE_NOT_READY 0x1UL
	#घोषणा VNIC_RSS_CFG_CMD_ERR_CODE_LAST               VNIC_RSS_CFG_CMD_ERR_CODE_INTERFACE_NOT_READY
	u8	unused_0[7];
पूर्ण;

/* hwrm_vnic_plcmodes_cfg_input (size:320b/40B) */
काष्ठा hwrm_vnic_plcmodes_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा VNIC_PLCMODES_CFG_REQ_FLAGS_REGULAR_PLACEMENT     0x1UL
	#घोषणा VNIC_PLCMODES_CFG_REQ_FLAGS_JUMBO_PLACEMENT       0x2UL
	#घोषणा VNIC_PLCMODES_CFG_REQ_FLAGS_HDS_IPV4              0x4UL
	#घोषणा VNIC_PLCMODES_CFG_REQ_FLAGS_HDS_IPV6              0x8UL
	#घोषणा VNIC_PLCMODES_CFG_REQ_FLAGS_HDS_FCOE              0x10UL
	#घोषणा VNIC_PLCMODES_CFG_REQ_FLAGS_HDS_ROCE              0x20UL
	#घोषणा VNIC_PLCMODES_CFG_REQ_FLAGS_VIRTIO_PLACEMENT      0x40UL
	__le32	enables;
	#घोषणा VNIC_PLCMODES_CFG_REQ_ENABLES_JUMBO_THRESH_VALID      0x1UL
	#घोषणा VNIC_PLCMODES_CFG_REQ_ENABLES_HDS_OFFSET_VALID        0x2UL
	#घोषणा VNIC_PLCMODES_CFG_REQ_ENABLES_HDS_THRESHOLD_VALID     0x4UL
	#घोषणा VNIC_PLCMODES_CFG_REQ_ENABLES_MAX_BDS_VALID           0x8UL
	__le32	vnic_id;
	__le16	jumbo_thresh;
	__le16	hds_offset;
	__le16	hds_threshold;
	__le16	max_bds;
	u8	unused_0[4];
पूर्ण;

/* hwrm_vnic_plcmodes_cfg_output (size:128b/16B) */
काष्ठा hwrm_vnic_plcmodes_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_vnic_rss_cos_lb_ctx_alloc_input (size:128b/16B) */
काष्ठा hwrm_vnic_rss_cos_lb_ctx_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
पूर्ण;

/* hwrm_vnic_rss_cos_lb_ctx_alloc_output (size:128b/16B) */
काष्ठा hwrm_vnic_rss_cos_lb_ctx_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	rss_cos_lb_ctx_id;
	u8	unused_0[5];
	u8	valid;
पूर्ण;

/* hwrm_vnic_rss_cos_lb_ctx_मुक्त_input (size:192b/24B) */
काष्ठा hwrm_vnic_rss_cos_lb_ctx_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	rss_cos_lb_ctx_id;
	u8	unused_0[6];
पूर्ण;

/* hwrm_vnic_rss_cos_lb_ctx_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_vnic_rss_cos_lb_ctx_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_ring_alloc_input (size:704b/88B) */
काष्ठा hwrm_ring_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	enables;
	#घोषणा RING_ALLOC_REQ_ENABLES_RING_ARB_CFG          0x2UL
	#घोषणा RING_ALLOC_REQ_ENABLES_STAT_CTX_ID_VALID     0x8UL
	#घोषणा RING_ALLOC_REQ_ENABLES_MAX_BW_VALID          0x20UL
	#घोषणा RING_ALLOC_REQ_ENABLES_RX_RING_ID_VALID      0x40UL
	#घोषणा RING_ALLOC_REQ_ENABLES_NQ_RING_ID_VALID      0x80UL
	#घोषणा RING_ALLOC_REQ_ENABLES_RX_BUF_SIZE_VALID     0x100UL
	#घोषणा RING_ALLOC_REQ_ENABLES_SCHQ_ID               0x200UL
	#घोषणा RING_ALLOC_REQ_ENABLES_MPC_CHNLS_TYPE        0x400UL
	u8	ring_type;
	#घोषणा RING_ALLOC_REQ_RING_TYPE_L2_CMPL   0x0UL
	#घोषणा RING_ALLOC_REQ_RING_TYPE_TX        0x1UL
	#घोषणा RING_ALLOC_REQ_RING_TYPE_RX        0x2UL
	#घोषणा RING_ALLOC_REQ_RING_TYPE_ROCE_CMPL 0x3UL
	#घोषणा RING_ALLOC_REQ_RING_TYPE_RX_AGG    0x4UL
	#घोषणा RING_ALLOC_REQ_RING_TYPE_NQ        0x5UL
	#घोषणा RING_ALLOC_REQ_RING_TYPE_LAST     RING_ALLOC_REQ_RING_TYPE_NQ
	u8	unused_0;
	__le16	flags;
	#घोषणा RING_ALLOC_REQ_FLAGS_RX_SOP_PAD     0x1UL
	__le64	page_tbl_addr;
	__le32	fbo;
	u8	page_size;
	u8	page_tbl_depth;
	__le16	schq_id;
	__le32	length;
	__le16	logical_id;
	__le16	cmpl_ring_id;
	__le16	queue_id;
	__le16	rx_buf_size;
	__le16	rx_ring_id;
	__le16	nq_ring_id;
	__le16	ring_arb_cfg;
	#घोषणा RING_ALLOC_REQ_RING_ARB_CFG_ARB_POLICY_MASK      0xfUL
	#घोषणा RING_ALLOC_REQ_RING_ARB_CFG_ARB_POLICY_SFT       0
	#घोषणा RING_ALLOC_REQ_RING_ARB_CFG_ARB_POLICY_SP          0x1UL
	#घोषणा RING_ALLOC_REQ_RING_ARB_CFG_ARB_POLICY_WFQ         0x2UL
	#घोषणा RING_ALLOC_REQ_RING_ARB_CFG_ARB_POLICY_LAST       RING_ALLOC_REQ_RING_ARB_CFG_ARB_POLICY_WFQ
	#घोषणा RING_ALLOC_REQ_RING_ARB_CFG_RSVD_MASK            0xf0UL
	#घोषणा RING_ALLOC_REQ_RING_ARB_CFG_RSVD_SFT             4
	#घोषणा RING_ALLOC_REQ_RING_ARB_CFG_ARB_POLICY_PARAM_MASK 0xff00UL
	#घोषणा RING_ALLOC_REQ_RING_ARB_CFG_ARB_POLICY_PARAM_SFT 8
	__le16	unused_3;
	__le32	reserved3;
	__le32	stat_ctx_id;
	__le32	reserved4;
	__le32	max_bw;
	#घोषणा RING_ALLOC_REQ_MAX_BW_BW_VALUE_MASK             0xfffffffUL
	#घोषणा RING_ALLOC_REQ_MAX_BW_BW_VALUE_SFT              0
	#घोषणा RING_ALLOC_REQ_MAX_BW_SCALE                     0x10000000UL
	#घोषणा RING_ALLOC_REQ_MAX_BW_SCALE_BITS                  (0x0UL << 28)
	#घोषणा RING_ALLOC_REQ_MAX_BW_SCALE_BYTES                 (0x1UL << 28)
	#घोषणा RING_ALLOC_REQ_MAX_BW_SCALE_LAST                 RING_ALLOC_REQ_MAX_BW_SCALE_BYTES
	#घोषणा RING_ALLOC_REQ_MAX_BW_BW_VALUE_UNIT_MASK        0xe0000000UL
	#घोषणा RING_ALLOC_REQ_MAX_BW_BW_VALUE_UNIT_SFT         29
	#घोषणा RING_ALLOC_REQ_MAX_BW_BW_VALUE_UNIT_MEGA          (0x0UL << 29)
	#घोषणा RING_ALLOC_REQ_MAX_BW_BW_VALUE_UNIT_KILO          (0x2UL << 29)
	#घोषणा RING_ALLOC_REQ_MAX_BW_BW_VALUE_UNIT_BASE          (0x4UL << 29)
	#घोषणा RING_ALLOC_REQ_MAX_BW_BW_VALUE_UNIT_GIGA          (0x6UL << 29)
	#घोषणा RING_ALLOC_REQ_MAX_BW_BW_VALUE_UNIT_PERCENT1_100  (0x1UL << 29)
	#घोषणा RING_ALLOC_REQ_MAX_BW_BW_VALUE_UNIT_INVALID       (0x7UL << 29)
	#घोषणा RING_ALLOC_REQ_MAX_BW_BW_VALUE_UNIT_LAST         RING_ALLOC_REQ_MAX_BW_BW_VALUE_UNIT_INVALID
	u8	पूर्णांक_mode;
	#घोषणा RING_ALLOC_REQ_INT_MODE_LEGACY 0x0UL
	#घोषणा RING_ALLOC_REQ_INT_MODE_RSVD   0x1UL
	#घोषणा RING_ALLOC_REQ_INT_MODE_MSIX   0x2UL
	#घोषणा RING_ALLOC_REQ_INT_MODE_POLL   0x3UL
	#घोषणा RING_ALLOC_REQ_INT_MODE_LAST  RING_ALLOC_REQ_INT_MODE_POLL
	u8	mpc_chnls_type;
	#घोषणा RING_ALLOC_REQ_MPC_CHNLS_TYPE_TCE     0x0UL
	#घोषणा RING_ALLOC_REQ_MPC_CHNLS_TYPE_RCE     0x1UL
	#घोषणा RING_ALLOC_REQ_MPC_CHNLS_TYPE_TE_CFA  0x2UL
	#घोषणा RING_ALLOC_REQ_MPC_CHNLS_TYPE_RE_CFA  0x3UL
	#घोषणा RING_ALLOC_REQ_MPC_CHNLS_TYPE_PRIMATE 0x4UL
	#घोषणा RING_ALLOC_REQ_MPC_CHNLS_TYPE_LAST   RING_ALLOC_REQ_MPC_CHNLS_TYPE_PRIMATE
	u8	unused_4[2];
	__le64	cq_handle;
पूर्ण;

/* hwrm_ring_alloc_output (size:128b/16B) */
काष्ठा hwrm_ring_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	ring_id;
	__le16	logical_ring_id;
	u8	push_buffer_index;
	#घोषणा RING_ALLOC_RESP_PUSH_BUFFER_INDEX_PING_BUFFER 0x0UL
	#घोषणा RING_ALLOC_RESP_PUSH_BUFFER_INDEX_PONG_BUFFER 0x1UL
	#घोषणा RING_ALLOC_RESP_PUSH_BUFFER_INDEX_LAST       RING_ALLOC_RESP_PUSH_BUFFER_INDEX_PONG_BUFFER
	u8	unused_0[2];
	u8	valid;
पूर्ण;

/* hwrm_ring_मुक्त_input (size:256b/32B) */
काष्ठा hwrm_ring_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	u8	ring_type;
	#घोषणा RING_FREE_REQ_RING_TYPE_L2_CMPL   0x0UL
	#घोषणा RING_FREE_REQ_RING_TYPE_TX        0x1UL
	#घोषणा RING_FREE_REQ_RING_TYPE_RX        0x2UL
	#घोषणा RING_FREE_REQ_RING_TYPE_ROCE_CMPL 0x3UL
	#घोषणा RING_FREE_REQ_RING_TYPE_RX_AGG    0x4UL
	#घोषणा RING_FREE_REQ_RING_TYPE_NQ        0x5UL
	#घोषणा RING_FREE_REQ_RING_TYPE_LAST     RING_FREE_REQ_RING_TYPE_NQ
	u8	flags;
	#घोषणा RING_FREE_REQ_FLAGS_VIRTIO_RING_VALID 0x1UL
	#घोषणा RING_FREE_REQ_FLAGS_LAST             RING_FREE_REQ_FLAGS_VIRTIO_RING_VALID
	__le16	ring_id;
	__le32	prod_idx;
	__le32	opaque;
	__le32	unused_1;
पूर्ण;

/* hwrm_ring_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_ring_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_ring_reset_input (size:192b/24B) */
काष्ठा hwrm_ring_reset_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	u8	ring_type;
	#घोषणा RING_RESET_REQ_RING_TYPE_L2_CMPL     0x0UL
	#घोषणा RING_RESET_REQ_RING_TYPE_TX          0x1UL
	#घोषणा RING_RESET_REQ_RING_TYPE_RX          0x2UL
	#घोषणा RING_RESET_REQ_RING_TYPE_ROCE_CMPL   0x3UL
	#घोषणा RING_RESET_REQ_RING_TYPE_RX_RING_GRP 0x6UL
	#घोषणा RING_RESET_REQ_RING_TYPE_LAST       RING_RESET_REQ_RING_TYPE_RX_RING_GRP
	u8	unused_0;
	__le16	ring_id;
	u8	unused_1[4];
पूर्ण;

/* hwrm_ring_reset_output (size:128b/16B) */
काष्ठा hwrm_ring_reset_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	push_buffer_index;
	#घोषणा RING_RESET_RESP_PUSH_BUFFER_INDEX_PING_BUFFER 0x0UL
	#घोषणा RING_RESET_RESP_PUSH_BUFFER_INDEX_PONG_BUFFER 0x1UL
	#घोषणा RING_RESET_RESP_PUSH_BUFFER_INDEX_LAST       RING_RESET_RESP_PUSH_BUFFER_INDEX_PONG_BUFFER
	u8	unused_0[3];
	u8	consumer_idx[3];
	u8	valid;
पूर्ण;

/* hwrm_ring_aggपूर्णांक_qcaps_input (size:128b/16B) */
काष्ठा hwrm_ring_aggपूर्णांक_qcaps_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
पूर्ण;

/* hwrm_ring_aggपूर्णांक_qcaps_output (size:384b/48B) */
काष्ठा hwrm_ring_aggपूर्णांक_qcaps_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	cmpl_params;
	#घोषणा RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_INT_LAT_TMR_MIN                  0x1UL
	#घोषणा RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_INT_LAT_TMR_MAX                  0x2UL
	#घोषणा RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_TIMER_RESET                      0x4UL
	#घोषणा RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_RING_IDLE                        0x8UL
	#घोषणा RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_NUM_CMPL_DMA_AGGR                0x10UL
	#घोषणा RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_NUM_CMPL_DMA_AGGR_DURING_INT     0x20UL
	#घोषणा RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_CMPL_AGGR_DMA_TMR                0x40UL
	#घोषणा RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_CMPL_AGGR_DMA_TMR_DURING_INT     0x80UL
	#घोषणा RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_NUM_CMPL_AGGR_INT                0x100UL
	__le32	nq_params;
	#घोषणा RING_AGGINT_QCAPS_RESP_NQ_PARAMS_INT_LAT_TMR_MIN     0x1UL
	__le16	num_cmpl_dma_aggr_min;
	__le16	num_cmpl_dma_aggr_max;
	__le16	num_cmpl_dma_aggr_during_पूर्णांक_min;
	__le16	num_cmpl_dma_aggr_during_पूर्णांक_max;
	__le16	cmpl_aggr_dma_पंचांगr_min;
	__le16	cmpl_aggr_dma_पंचांगr_max;
	__le16	cmpl_aggr_dma_पंचांगr_during_पूर्णांक_min;
	__le16	cmpl_aggr_dma_पंचांगr_during_पूर्णांक_max;
	__le16	पूर्णांक_lat_पंचांगr_min_min;
	__le16	पूर्णांक_lat_पंचांगr_min_max;
	__le16	पूर्णांक_lat_पंचांगr_max_min;
	__le16	पूर्णांक_lat_पंचांगr_max_max;
	__le16	num_cmpl_aggr_पूर्णांक_min;
	__le16	num_cmpl_aggr_पूर्णांक_max;
	__le16	समयr_units;
	u8	unused_0[1];
	u8	valid;
पूर्ण;

/* hwrm_ring_cmpl_ring_qaggपूर्णांक_params_input (size:192b/24B) */
काष्ठा hwrm_ring_cmpl_ring_qaggपूर्णांक_params_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	ring_id;
	__le16	flags;
	#घोषणा RING_CMPL_RING_QAGGINT_PARAMS_REQ_FLAGS_UNUSED_0_MASK 0x3UL
	#घोषणा RING_CMPL_RING_QAGGINT_PARAMS_REQ_FLAGS_UNUSED_0_SFT 0
	#घोषणा RING_CMPL_RING_QAGGINT_PARAMS_REQ_FLAGS_IS_NQ        0x4UL
	u8	unused_0[4];
पूर्ण;

/* hwrm_ring_cmpl_ring_qaggपूर्णांक_params_output (size:256b/32B) */
काष्ठा hwrm_ring_cmpl_ring_qaggपूर्णांक_params_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	flags;
	#घोषणा RING_CMPL_RING_QAGGINT_PARAMS_RESP_FLAGS_TIMER_RESET     0x1UL
	#घोषणा RING_CMPL_RING_QAGGINT_PARAMS_RESP_FLAGS_RING_IDLE       0x2UL
	__le16	num_cmpl_dma_aggr;
	__le16	num_cmpl_dma_aggr_during_पूर्णांक;
	__le16	cmpl_aggr_dma_पंचांगr;
	__le16	cmpl_aggr_dma_पंचांगr_during_पूर्णांक;
	__le16	पूर्णांक_lat_पंचांगr_min;
	__le16	पूर्णांक_lat_पंचांगr_max;
	__le16	num_cmpl_aggr_पूर्णांक;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_ring_cmpl_ring_cfg_aggपूर्णांक_params_input (size:320b/40B) */
काष्ठा hwrm_ring_cmpl_ring_cfg_aggपूर्णांक_params_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	ring_id;
	__le16	flags;
	#घोषणा RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_FLAGS_TIMER_RESET     0x1UL
	#घोषणा RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_FLAGS_RING_IDLE       0x2UL
	#घोषणा RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_FLAGS_IS_NQ           0x4UL
	__le16	num_cmpl_dma_aggr;
	__le16	num_cmpl_dma_aggr_during_पूर्णांक;
	__le16	cmpl_aggr_dma_पंचांगr;
	__le16	cmpl_aggr_dma_पंचांगr_during_पूर्णांक;
	__le16	पूर्णांक_lat_पंचांगr_min;
	__le16	पूर्णांक_lat_पंचांगr_max;
	__le16	num_cmpl_aggr_पूर्णांक;
	__le16	enables;
	#घोषणा RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_ENABLES_NUM_CMPL_DMA_AGGR                0x1UL
	#घोषणा RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_ENABLES_NUM_CMPL_DMA_AGGR_DURING_INT     0x2UL
	#घोषणा RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_ENABLES_CMPL_AGGR_DMA_TMR                0x4UL
	#घोषणा RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_ENABLES_INT_LAT_TMR_MIN                  0x8UL
	#घोषणा RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_ENABLES_INT_LAT_TMR_MAX                  0x10UL
	#घोषणा RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_ENABLES_NUM_CMPL_AGGR_INT                0x20UL
	u8	unused_0[4];
पूर्ण;

/* hwrm_ring_cmpl_ring_cfg_aggपूर्णांक_params_output (size:128b/16B) */
काष्ठा hwrm_ring_cmpl_ring_cfg_aggपूर्णांक_params_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_ring_grp_alloc_input (size:192b/24B) */
काष्ठा hwrm_ring_grp_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	cr;
	__le16	rr;
	__le16	ar;
	__le16	sc;
पूर्ण;

/* hwrm_ring_grp_alloc_output (size:128b/16B) */
काष्ठा hwrm_ring_grp_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	ring_group_id;
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_ring_grp_मुक्त_input (size:192b/24B) */
काष्ठा hwrm_ring_grp_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	ring_group_id;
	u8	unused_0[4];
पूर्ण;

/* hwrm_ring_grp_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_ring_grp_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

#घोषणा DEFAULT_FLOW_ID 0xFFFFFFFFUL
#घोषणा ROCEV1_FLOW_ID 0xFFFFFFFEUL
#घोषणा ROCEV2_FLOW_ID 0xFFFFFFFDUL
#घोषणा ROCEV2_CNP_FLOW_ID 0xFFFFFFFCUL

/* hwrm_cfa_l2_filter_alloc_input (size:768b/96B) */
काष्ठा hwrm_cfa_l2_filter_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_PATH              0x1UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_PATH_TX             0x0UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_PATH_RX             0x1UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_PATH_LAST          CFA_L2_FILTER_ALLOC_REQ_FLAGS_PATH_RX
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_LOOPBACK          0x2UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_DROP              0x4UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_OUTERMOST         0x8UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_TRAFFIC_MASK      0x30UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_TRAFFIC_SFT       4
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_TRAFFIC_NO_ROCE_L2  (0x0UL << 4)
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_TRAFFIC_L2          (0x1UL << 4)
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_TRAFFIC_ROCE        (0x2UL << 4)
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_TRAFFIC_LAST       CFA_L2_FILTER_ALLOC_REQ_FLAGS_TRAFFIC_ROCE
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_XDP_DISABLE       0x40UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_FLAGS_SOURCE_VALID      0x80UL
	__le32	enables;
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_L2_ADDR             0x1UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_L2_ADDR_MASK        0x2UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_L2_OVLAN            0x4UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_L2_OVLAN_MASK       0x8UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_L2_IVLAN            0x10UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_L2_IVLAN_MASK       0x20UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_T_L2_ADDR           0x40UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_T_L2_ADDR_MASK      0x80UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_T_L2_OVLAN          0x100UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_T_L2_OVLAN_MASK     0x200UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_T_L2_IVLAN          0x400UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_T_L2_IVLAN_MASK     0x800UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_SRC_TYPE            0x1000UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_SRC_ID              0x2000UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_TUNNEL_TYPE         0x4000UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_DST_ID              0x8000UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_MIRROR_VNIC_ID      0x10000UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_NUM_VLANS           0x20000UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_ENABLES_T_NUM_VLANS         0x40000UL
	u8	l2_addr[6];
	u8	num_vlans;
	u8	t_num_vlans;
	u8	l2_addr_mask[6];
	__le16	l2_ovlan;
	__le16	l2_ovlan_mask;
	__le16	l2_ivlan;
	__le16	l2_ivlan_mask;
	u8	unused_1[2];
	u8	t_l2_addr[6];
	u8	unused_2[2];
	u8	t_l2_addr_mask[6];
	__le16	t_l2_ovlan;
	__le16	t_l2_ovlan_mask;
	__le16	t_l2_ivlan;
	__le16	t_l2_ivlan_mask;
	u8	src_type;
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_SRC_TYPE_NPORT 0x0UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_SRC_TYPE_PF    0x1UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_SRC_TYPE_VF    0x2UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_SRC_TYPE_VNIC  0x3UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_SRC_TYPE_KONG  0x4UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_SRC_TYPE_APE   0x5UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_SRC_TYPE_BONO  0x6UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_SRC_TYPE_TANG  0x7UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_SRC_TYPE_LAST CFA_L2_FILTER_ALLOC_REQ_SRC_TYPE_TANG
	u8	unused_3;
	__le32	src_id;
	u8	tunnel_type;
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_NONTUNNEL    0x0UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_VXLAN        0x1UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_NVGRE        0x2UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_L2GRE        0x3UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_IPIP         0x4UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_GENEVE       0x5UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_MPLS         0x6UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_STT          0x7UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_IPGRE        0x8UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_VXLAN_V4     0x9UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_IPGRE_V1     0xaUL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_L2_ETYPE     0xbUL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_VXLAN_GPE_V6 0xcUL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_ANYTUNNEL    0xffUL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_LAST        CFA_L2_FILTER_ALLOC_REQ_TUNNEL_TYPE_ANYTUNNEL
	u8	unused_4;
	__le16	dst_id;
	__le16	mirror_vnic_id;
	u8	pri_hपूर्णांक;
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_PRI_HINT_NO_PREFER    0x0UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_PRI_HINT_ABOVE_FILTER 0x1UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_PRI_HINT_BELOW_FILTER 0x2UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_PRI_Hपूर्णांक_उच्च          0x3UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_PRI_Hपूर्णांक_न्यून          0x4UL
	#घोषणा CFA_L2_FILTER_ALLOC_REQ_PRI_HINT_LAST        CFA_L2_FILTER_ALLOC_REQ_PRI_Hपूर्णांक_न्यून
	u8	unused_5;
	__le32	unused_6;
	__le64	l2_filter_id_hपूर्णांक;
पूर्ण;

/* hwrm_cfa_l2_filter_alloc_output (size:192b/24B) */
काष्ठा hwrm_cfa_l2_filter_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le64	l2_filter_id;
	__le32	flow_id;
	#घोषणा CFA_L2_FILTER_ALLOC_RESP_FLOW_ID_VALUE_MASK 0x3fffffffUL
	#घोषणा CFA_L2_FILTER_ALLOC_RESP_FLOW_ID_VALUE_SFT 0
	#घोषणा CFA_L2_FILTER_ALLOC_RESP_FLOW_ID_TYPE      0x40000000UL
	#घोषणा CFA_L2_FILTER_ALLOC_RESP_FLOW_ID_TYPE_INT    (0x0UL << 30)
	#घोषणा CFA_L2_FILTER_ALLOC_RESP_FLOW_ID_TYPE_EXT    (0x1UL << 30)
	#घोषणा CFA_L2_FILTER_ALLOC_RESP_FLOW_ID_TYPE_LAST  CFA_L2_FILTER_ALLOC_RESP_FLOW_ID_TYPE_EXT
	#घोषणा CFA_L2_FILTER_ALLOC_RESP_FLOW_ID_सूची       0x80000000UL
	#घोषणा CFA_L2_FILTER_ALLOC_RESP_FLOW_ID_सूची_RX      (0x0UL << 31)
	#घोषणा CFA_L2_FILTER_ALLOC_RESP_FLOW_ID_सूची_TX      (0x1UL << 31)
	#घोषणा CFA_L2_FILTER_ALLOC_RESP_FLOW_ID_सूची_LAST   CFA_L2_FILTER_ALLOC_RESP_FLOW_ID_सूची_TX
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_cfa_l2_filter_मुक्त_input (size:192b/24B) */
काष्ठा hwrm_cfa_l2_filter_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	l2_filter_id;
पूर्ण;

/* hwrm_cfa_l2_filter_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_cfa_l2_filter_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_cfa_l2_filter_cfg_input (size:320b/40B) */
काष्ठा hwrm_cfa_l2_filter_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा CFA_L2_FILTER_CFG_REQ_FLAGS_PATH              0x1UL
	#घोषणा CFA_L2_FILTER_CFG_REQ_FLAGS_PATH_TX             0x0UL
	#घोषणा CFA_L2_FILTER_CFG_REQ_FLAGS_PATH_RX             0x1UL
	#घोषणा CFA_L2_FILTER_CFG_REQ_FLAGS_PATH_LAST          CFA_L2_FILTER_CFG_REQ_FLAGS_PATH_RX
	#घोषणा CFA_L2_FILTER_CFG_REQ_FLAGS_DROP              0x2UL
	#घोषणा CFA_L2_FILTER_CFG_REQ_FLAGS_TRAFFIC_MASK      0xcUL
	#घोषणा CFA_L2_FILTER_CFG_REQ_FLAGS_TRAFFIC_SFT       2
	#घोषणा CFA_L2_FILTER_CFG_REQ_FLAGS_TRAFFIC_NO_ROCE_L2  (0x0UL << 2)
	#घोषणा CFA_L2_FILTER_CFG_REQ_FLAGS_TRAFFIC_L2          (0x1UL << 2)
	#घोषणा CFA_L2_FILTER_CFG_REQ_FLAGS_TRAFFIC_ROCE        (0x2UL << 2)
	#घोषणा CFA_L2_FILTER_CFG_REQ_FLAGS_TRAFFIC_LAST       CFA_L2_FILTER_CFG_REQ_FLAGS_TRAFFIC_ROCE
	__le32	enables;
	#घोषणा CFA_L2_FILTER_CFG_REQ_ENABLES_DST_ID                 0x1UL
	#घोषणा CFA_L2_FILTER_CFG_REQ_ENABLES_NEW_MIRROR_VNIC_ID     0x2UL
	__le64	l2_filter_id;
	__le32	dst_id;
	__le32	new_mirror_vnic_id;
पूर्ण;

/* hwrm_cfa_l2_filter_cfg_output (size:128b/16B) */
काष्ठा hwrm_cfa_l2_filter_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_cfa_l2_set_rx_mask_input (size:448b/56B) */
काष्ठा hwrm_cfa_l2_set_rx_mask_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	vnic_id;
	__le32	mask;
	#घोषणा CFA_L2_SET_RX_MASK_REQ_MASK_MCAST               0x2UL
	#घोषणा CFA_L2_SET_RX_MASK_REQ_MASK_ALL_MCAST           0x4UL
	#घोषणा CFA_L2_SET_RX_MASK_REQ_MASK_BCAST               0x8UL
	#घोषणा CFA_L2_SET_RX_MASK_REQ_MASK_PROMISCUOUS         0x10UL
	#घोषणा CFA_L2_SET_RX_MASK_REQ_MASK_OUTERMOST           0x20UL
	#घोषणा CFA_L2_SET_RX_MASK_REQ_MASK_VLANONLY            0x40UL
	#घोषणा CFA_L2_SET_RX_MASK_REQ_MASK_VLAN_NONVLAN        0x80UL
	#घोषणा CFA_L2_SET_RX_MASK_REQ_MASK_ANYVLAN_NONVLAN     0x100UL
	__le64	mc_tbl_addr;
	__le32	num_mc_entries;
	u8	unused_0[4];
	__le64	vlan_tag_tbl_addr;
	__le32	num_vlan_tags;
	u8	unused_1[4];
पूर्ण;

/* hwrm_cfa_l2_set_rx_mask_output (size:128b/16B) */
काष्ठा hwrm_cfa_l2_set_rx_mask_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_cfa_l2_set_rx_mask_cmd_err (size:64b/8B) */
काष्ठा hwrm_cfa_l2_set_rx_mask_cmd_err अणु
	u8	code;
	#घोषणा CFA_L2_SET_RX_MASK_CMD_ERR_CODE_UNKNOWN                    0x0UL
	#घोषणा CFA_L2_SET_RX_MASK_CMD_ERR_CODE_NTUPLE_FILTER_CONFLICT_ERR 0x1UL
	#घोषणा CFA_L2_SET_RX_MASK_CMD_ERR_CODE_LAST                      CFA_L2_SET_RX_MASK_CMD_ERR_CODE_NTUPLE_FILTER_CONFLICT_ERR
	u8	unused_0[7];
पूर्ण;

/* hwrm_cfa_tunnel_filter_alloc_input (size:704b/88B) */
काष्ठा hwrm_cfa_tunnel_filter_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_FLAGS_LOOPBACK     0x1UL
	__le32	enables;
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_ENABLES_L2_FILTER_ID       0x1UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_ENABLES_L2_ADDR            0x2UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_ENABLES_L2_IVLAN           0x4UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_ENABLES_L3_ADDR            0x8UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_ENABLES_L3_ADDR_TYPE       0x10UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_ENABLES_T_L3_ADDR_TYPE     0x20UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_ENABLES_T_L3_ADDR          0x40UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_ENABLES_TUNNEL_TYPE        0x80UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_ENABLES_VNI                0x100UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_ENABLES_DST_VNIC_ID        0x200UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_ENABLES_MIRROR_VNIC_ID     0x400UL
	__le64	l2_filter_id;
	u8	l2_addr[6];
	__le16	l2_ivlan;
	__le32	l3_addr[4];
	__le32	t_l3_addr[4];
	u8	l3_addr_type;
	u8	t_l3_addr_type;
	u8	tunnel_type;
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_NONTUNNEL    0x0UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_VXLAN        0x1UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_NVGRE        0x2UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_L2GRE        0x3UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_IPIP         0x4UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_GENEVE       0x5UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_MPLS         0x6UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_STT          0x7UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_IPGRE        0x8UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_VXLAN_V4     0x9UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_IPGRE_V1     0xaUL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_L2_ETYPE     0xbUL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_VXLAN_GPE_V6 0xcUL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_ANYTUNNEL    0xffUL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_LAST        CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_TYPE_ANYTUNNEL
	u8	tunnel_flags;
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_FLAGS_TUN_FLAGS_OAM_CHECKSUM_EXPLHDR     0x1UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_FLAGS_TUN_FLAGS_CRITICAL_OPT_S1          0x2UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_REQ_TUNNEL_FLAGS_TUN_FLAGS_EXTHDR_SEQNUM_S0         0x4UL
	__le32	vni;
	__le32	dst_vnic_id;
	__le32	mirror_vnic_id;
पूर्ण;

/* hwrm_cfa_tunnel_filter_alloc_output (size:192b/24B) */
काष्ठा hwrm_cfa_tunnel_filter_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le64	tunnel_filter_id;
	__le32	flow_id;
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_RESP_FLOW_ID_VALUE_MASK 0x3fffffffUL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_RESP_FLOW_ID_VALUE_SFT 0
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_RESP_FLOW_ID_TYPE      0x40000000UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_RESP_FLOW_ID_TYPE_INT    (0x0UL << 30)
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_RESP_FLOW_ID_TYPE_EXT    (0x1UL << 30)
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_RESP_FLOW_ID_TYPE_LAST  CFA_TUNNEL_FILTER_ALLOC_RESP_FLOW_ID_TYPE_EXT
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_RESP_FLOW_ID_सूची       0x80000000UL
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_RESP_FLOW_ID_सूची_RX      (0x0UL << 31)
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_RESP_FLOW_ID_सूची_TX      (0x1UL << 31)
	#घोषणा CFA_TUNNEL_FILTER_ALLOC_RESP_FLOW_ID_सूची_LAST   CFA_TUNNEL_FILTER_ALLOC_RESP_FLOW_ID_सूची_TX
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_cfa_tunnel_filter_मुक्त_input (size:192b/24B) */
काष्ठा hwrm_cfa_tunnel_filter_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	tunnel_filter_id;
पूर्ण;

/* hwrm_cfa_tunnel_filter_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_cfa_tunnel_filter_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_vxlan_ipv4_hdr (size:128b/16B) */
काष्ठा hwrm_vxlan_ipv4_hdr अणु
	u8	ver_hlen;
	#घोषणा VXLAN_IPV4_HDR_VER_HLEN_HEADER_LENGTH_MASK 0xfUL
	#घोषणा VXLAN_IPV4_HDR_VER_HLEN_HEADER_LENGTH_SFT 0
	#घोषणा VXLAN_IPV4_HDR_VER_HLEN_VERSION_MASK      0xf0UL
	#घोषणा VXLAN_IPV4_HDR_VER_HLEN_VERSION_SFT       4
	u8	tos;
	__be16	ip_id;
	__be16	flags_frag_offset;
	u8	ttl;
	u8	protocol;
	__be32	src_ip_addr;
	__be32	dest_ip_addr;
पूर्ण;

/* hwrm_vxlan_ipv6_hdr (size:320b/40B) */
काष्ठा hwrm_vxlan_ipv6_hdr अणु
	__be32	ver_tc_flow_label;
	#घोषणा VXLAN_IPV6_HDR_VER_TC_FLOW_LABEL_VER_SFT         0x1cUL
	#घोषणा VXLAN_IPV6_HDR_VER_TC_FLOW_LABEL_VER_MASK        0xf0000000UL
	#घोषणा VXLAN_IPV6_HDR_VER_TC_FLOW_LABEL_TC_SFT          0x14UL
	#घोषणा VXLAN_IPV6_HDR_VER_TC_FLOW_LABEL_TC_MASK         0xff00000UL
	#घोषणा VXLAN_IPV6_HDR_VER_TC_FLOW_LABEL_FLOW_LABEL_SFT  0x0UL
	#घोषणा VXLAN_IPV6_HDR_VER_TC_FLOW_LABEL_FLOW_LABEL_MASK 0xfffffUL
	#घोषणा VXLAN_IPV6_HDR_VER_TC_FLOW_LABEL_LAST           VXLAN_IPV6_HDR_VER_TC_FLOW_LABEL_FLOW_LABEL_MASK
	__be16	payload_len;
	u8	next_hdr;
	u8	ttl;
	__be32	src_ip_addr[4];
	__be32	dest_ip_addr[4];
पूर्ण;

/* hwrm_cfa_encap_data_vxlan (size:640b/80B) */
काष्ठा hwrm_cfa_encap_data_vxlan अणु
	u8	src_mac_addr[6];
	__le16	unused_0;
	u8	dst_mac_addr[6];
	u8	num_vlan_tags;
	u8	unused_1;
	__be16	ovlan_tpid;
	__be16	ovlan_tci;
	__be16	ivlan_tpid;
	__be16	ivlan_tci;
	__le32	l3[10];
	#घोषणा CFA_ENCAP_DATA_VXLAN_L3_VER_MASK 0xfUL
	#घोषणा CFA_ENCAP_DATA_VXLAN_L3_VER_IPV4 0x4UL
	#घोषणा CFA_ENCAP_DATA_VXLAN_L3_VER_IPV6 0x6UL
	#घोषणा CFA_ENCAP_DATA_VXLAN_L3_LAST    CFA_ENCAP_DATA_VXLAN_L3_VER_IPV6
	__be16	src_port;
	__be16	dst_port;
	__be32	vni;
	u8	hdr_rsvd0[3];
	u8	hdr_rsvd1;
	u8	hdr_flags;
	u8	unused[3];
पूर्ण;

/* hwrm_cfa_encap_record_alloc_input (size:832b/104B) */
काष्ठा hwrm_cfa_encap_record_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_FLAGS_LOOPBACK     0x1UL
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_FLAGS_EXTERNAL     0x2UL
	u8	encap_type;
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_VXLAN        0x1UL
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_NVGRE        0x2UL
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_L2GRE        0x3UL
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_IPIP         0x4UL
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_GENEVE       0x5UL
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_MPLS         0x6UL
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_VLAN         0x7UL
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_IPGRE        0x8UL
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_VXLAN_V4     0x9UL
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_IPGRE_V1     0xaUL
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_L2_ETYPE     0xbUL
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_VXLAN_GPE_V6 0xcUL
	#घोषणा CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_LAST        CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_VXLAN_GPE_V6
	u8	unused_0[3];
	__le32	encap_data[20];
पूर्ण;

/* hwrm_cfa_encap_record_alloc_output (size:128b/16B) */
काष्ठा hwrm_cfa_encap_record_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	encap_record_id;
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_cfa_encap_record_मुक्त_input (size:192b/24B) */
काष्ठा hwrm_cfa_encap_record_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	encap_record_id;
	u8	unused_0[4];
पूर्ण;

/* hwrm_cfa_encap_record_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_cfa_encap_record_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_cfa_ntuple_filter_alloc_input (size:1024b/128B) */
काष्ठा hwrm_cfa_ntuple_filter_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_FLAGS_LOOPBACK              0x1UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_FLAGS_DROP                  0x2UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_FLAGS_METER                 0x4UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_FLAGS_DEST_FID              0x8UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_FLAGS_ARP_REPLY             0x10UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_FLAGS_DEST_RFS_RING_IDX     0x20UL
	__le32	enables;
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_L2_FILTER_ID         0x1UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_ETHERTYPE            0x2UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_TUNNEL_TYPE          0x4UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_SRC_MACADDR          0x8UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_IPADDR_TYPE          0x10UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_SRC_IPADDR           0x20UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_SRC_IPADDR_MASK      0x40UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_DST_IPADDR           0x80UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_DST_IPADDR_MASK      0x100UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_IP_PROTOCOL          0x200UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_SRC_PORT             0x400UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_SRC_PORT_MASK        0x800UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_DST_PORT             0x1000UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_DST_PORT_MASK        0x2000UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_PRI_HINT             0x4000UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_NTUPLE_FILTER_ID     0x8000UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_DST_ID               0x10000UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_MIRROR_VNIC_ID       0x20000UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_DST_MACADDR          0x40000UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_RFS_RING_TBL_IDX     0x80000UL
	__le64	l2_filter_id;
	u8	src_macaddr[6];
	__be16	ethertype;
	u8	ip_addr_type;
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_IP_ADDR_TYPE_UNKNOWN 0x0UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_IP_ADDR_TYPE_IPV4    0x4UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_IP_ADDR_TYPE_IPV6    0x6UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_IP_ADDR_TYPE_LAST   CFA_NTUPLE_FILTER_ALLOC_REQ_IP_ADDR_TYPE_IPV6
	u8	ip_protocol;
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_IP_PROTOCOL_UNKNOWN 0x0UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_IP_PROTOCOL_TCP     0x6UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_IP_PROTOCOL_UDP     0x11UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_IP_PROTOCOL_LAST   CFA_NTUPLE_FILTER_ALLOC_REQ_IP_PROTOCOL_UDP
	__le16	dst_id;
	__le16	mirror_vnic_id;
	u8	tunnel_type;
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_NONTUNNEL    0x0UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_VXLAN        0x1UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_NVGRE        0x2UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_L2GRE        0x3UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_IPIP         0x4UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_GENEVE       0x5UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_MPLS         0x6UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_STT          0x7UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_IPGRE        0x8UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_VXLAN_V4     0x9UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_IPGRE_V1     0xaUL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_L2_ETYPE     0xbUL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_VXLAN_GPE_V6 0xcUL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_ANYTUNNEL    0xffUL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_LAST        CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_ANYTUNNEL
	u8	pri_hपूर्णांक;
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_PRI_HINT_NO_PREFER 0x0UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_PRI_HINT_ABOVE     0x1UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_PRI_HINT_BELOW     0x2UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_PRI_HINT_HIGHEST   0x3UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_PRI_HINT_LOWEST    0x4UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_REQ_PRI_HINT_LAST     CFA_NTUPLE_FILTER_ALLOC_REQ_PRI_HINT_LOWEST
	__be32	src_ipaddr[4];
	__be32	src_ipaddr_mask[4];
	__be32	dst_ipaddr[4];
	__be32	dst_ipaddr_mask[4];
	__be16	src_port;
	__be16	src_port_mask;
	__be16	dst_port;
	__be16	dst_port_mask;
	__le64	ntuple_filter_id_hपूर्णांक;
पूर्ण;

/* hwrm_cfa_ntuple_filter_alloc_output (size:192b/24B) */
काष्ठा hwrm_cfa_ntuple_filter_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le64	ntuple_filter_id;
	__le32	flow_id;
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_RESP_FLOW_ID_VALUE_MASK 0x3fffffffUL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_RESP_FLOW_ID_VALUE_SFT 0
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_RESP_FLOW_ID_TYPE      0x40000000UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_RESP_FLOW_ID_TYPE_INT    (0x0UL << 30)
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_RESP_FLOW_ID_TYPE_EXT    (0x1UL << 30)
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_RESP_FLOW_ID_TYPE_LAST  CFA_NTUPLE_FILTER_ALLOC_RESP_FLOW_ID_TYPE_EXT
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_RESP_FLOW_ID_सूची       0x80000000UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_RESP_FLOW_ID_सूची_RX      (0x0UL << 31)
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_RESP_FLOW_ID_सूची_TX      (0x1UL << 31)
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_RESP_FLOW_ID_सूची_LAST   CFA_NTUPLE_FILTER_ALLOC_RESP_FLOW_ID_सूची_TX
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_cfa_ntuple_filter_alloc_cmd_err (size:64b/8B) */
काष्ठा hwrm_cfa_ntuple_filter_alloc_cmd_err अणु
	u8	code;
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_CMD_ERR_CODE_UNKNOWN                   0x0UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_CMD_ERR_CODE_RX_MASK_VLAN_CONFLICT_ERR 0x1UL
	#घोषणा CFA_NTUPLE_FILTER_ALLOC_CMD_ERR_CODE_LAST                     CFA_NTUPLE_FILTER_ALLOC_CMD_ERR_CODE_RX_MASK_VLAN_CONFLICT_ERR
	u8	unused_0[7];
पूर्ण;

/* hwrm_cfa_ntuple_filter_मुक्त_input (size:192b/24B) */
काष्ठा hwrm_cfa_ntuple_filter_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	ntuple_filter_id;
पूर्ण;

/* hwrm_cfa_ntuple_filter_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_cfa_ntuple_filter_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_cfa_ntuple_filter_cfg_input (size:384b/48B) */
काष्ठा hwrm_cfa_ntuple_filter_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	enables;
	#घोषणा CFA_NTUPLE_FILTER_CFG_REQ_ENABLES_NEW_DST_ID                0x1UL
	#घोषणा CFA_NTUPLE_FILTER_CFG_REQ_ENABLES_NEW_MIRROR_VNIC_ID        0x2UL
	#घोषणा CFA_NTUPLE_FILTER_CFG_REQ_ENABLES_NEW_METER_INSTANCE_ID     0x4UL
	__le32	flags;
	#घोषणा CFA_NTUPLE_FILTER_CFG_REQ_FLAGS_DEST_FID              0x1UL
	#घोषणा CFA_NTUPLE_FILTER_CFG_REQ_FLAGS_DEST_RFS_RING_IDX     0x2UL
	__le64	ntuple_filter_id;
	__le32	new_dst_id;
	__le32	new_mirror_vnic_id;
	__le16	new_meter_instance_id;
	#घोषणा CFA_NTUPLE_FILTER_CFG_REQ_NEW_METER_INSTANCE_ID_INVALID 0xffffUL
	#घोषणा CFA_NTUPLE_FILTER_CFG_REQ_NEW_METER_INSTANCE_ID_LAST   CFA_NTUPLE_FILTER_CFG_REQ_NEW_METER_INSTANCE_ID_INVALID
	u8	unused_1[6];
पूर्ण;

/* hwrm_cfa_ntuple_filter_cfg_output (size:128b/16B) */
काष्ठा hwrm_cfa_ntuple_filter_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_cfa_decap_filter_alloc_input (size:832b/104B) */
काष्ठा hwrm_cfa_decap_filter_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_FLAGS_OVS_TUNNEL     0x1UL
	__le32	enables;
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_TUNNEL_TYPE        0x1UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_TUNNEL_ID          0x2UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_SRC_MACADDR        0x4UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_DST_MACADDR        0x8UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_OVLAN_VID          0x10UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_IVLAN_VID          0x20UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_T_OVLAN_VID        0x40UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_T_IVLAN_VID        0x80UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_ETHERTYPE          0x100UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_SRC_IPADDR         0x200UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_DST_IPADDR         0x400UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_IPADDR_TYPE        0x800UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_IP_PROTOCOL        0x1000UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_SRC_PORT           0x2000UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_DST_PORT           0x4000UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_DST_ID             0x8000UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_MIRROR_VNIC_ID     0x10000UL
	__be32	tunnel_id;
	u8	tunnel_type;
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_NONTUNNEL    0x0UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_VXLAN        0x1UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_NVGRE        0x2UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_L2GRE        0x3UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_IPIP         0x4UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_GENEVE       0x5UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_MPLS         0x6UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_STT          0x7UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_IPGRE        0x8UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_VXLAN_V4     0x9UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_IPGRE_V1     0xaUL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_L2_ETYPE     0xbUL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_VXLAN_GPE_V6 0xcUL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_ANYTUNNEL    0xffUL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_LAST        CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_ANYTUNNEL
	u8	unused_0;
	__le16	unused_1;
	u8	src_macaddr[6];
	u8	unused_2[2];
	u8	dst_macaddr[6];
	__be16	ovlan_vid;
	__be16	ivlan_vid;
	__be16	t_ovlan_vid;
	__be16	t_ivlan_vid;
	__be16	ethertype;
	u8	ip_addr_type;
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_IP_ADDR_TYPE_UNKNOWN 0x0UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_IP_ADDR_TYPE_IPV4    0x4UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_IP_ADDR_TYPE_IPV6    0x6UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_IP_ADDR_TYPE_LAST   CFA_DECAP_FILTER_ALLOC_REQ_IP_ADDR_TYPE_IPV6
	u8	ip_protocol;
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_IP_PROTOCOL_UNKNOWN 0x0UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_IP_PROTOCOL_TCP     0x6UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_IP_PROTOCOL_UDP     0x11UL
	#घोषणा CFA_DECAP_FILTER_ALLOC_REQ_IP_PROTOCOL_LAST   CFA_DECAP_FILTER_ALLOC_REQ_IP_PROTOCOL_UDP
	__le16	unused_3;
	__le32	unused_4;
	__be32	src_ipaddr[4];
	__be32	dst_ipaddr[4];
	__be16	src_port;
	__be16	dst_port;
	__le16	dst_id;
	__le16	l2_ctxt_ref_id;
पूर्ण;

/* hwrm_cfa_decap_filter_alloc_output (size:128b/16B) */
काष्ठा hwrm_cfa_decap_filter_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	decap_filter_id;
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_cfa_decap_filter_मुक्त_input (size:192b/24B) */
काष्ठा hwrm_cfa_decap_filter_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	decap_filter_id;
	u8	unused_0[4];
पूर्ण;

/* hwrm_cfa_decap_filter_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_cfa_decap_filter_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_cfa_flow_alloc_input (size:1024b/128B) */
काष्ठा hwrm_cfa_flow_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	flags;
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_TUNNEL                 0x1UL
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_NUM_VLAN_MASK          0x6UL
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_NUM_VLAN_SFT           1
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_NUM_VLAN_NONE            (0x0UL << 1)
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_NUM_VLAN_ONE             (0x1UL << 1)
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_NUM_VLAN_TWO             (0x2UL << 1)
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_NUM_VLAN_LAST           CFA_FLOW_ALLOC_REQ_FLAGS_NUM_VLAN_TWO
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_FLOWTYPE_MASK          0x38UL
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_FLOWTYPE_SFT           3
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_FLOWTYPE_L2              (0x0UL << 3)
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_FLOWTYPE_IPV4            (0x1UL << 3)
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_FLOWTYPE_IPV6            (0x2UL << 3)
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_FLOWTYPE_LAST           CFA_FLOW_ALLOC_REQ_FLAGS_FLOWTYPE_IPV6
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_PATH_TX                0x40UL
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_PATH_RX                0x80UL
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_MATCH_VXLAN_IP_VNI     0x100UL
	#घोषणा CFA_FLOW_ALLOC_REQ_FLAGS_VHOST_ID_USE_VLAN      0x200UL
	__le16	src_fid;
	__le32	tunnel_handle;
	__le16	action_flags;
	#घोषणा CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_FWD                       0x1UL
	#घोषणा CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_RECYCLE                   0x2UL
	#घोषणा CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_DROP                      0x4UL
	#घोषणा CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_METER                     0x8UL
	#घोषणा CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_TUNNEL                    0x10UL
	#घोषणा CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_NAT_SRC                   0x20UL
	#घोषणा CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_NAT_DEST                  0x40UL
	#घोषणा CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_NAT_IPV4_ADDRESS          0x80UL
	#घोषणा CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_L2_HEADER_REWRITE         0x100UL
	#घोषणा CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_TTL_DECREMENT             0x200UL
	#घोषणा CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_TUNNEL_IP                 0x400UL
	#घोषणा CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_FLOW_AGING_ENABLED        0x800UL
	#घोषणा CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_PRI_HINT                  0x1000UL
	#घोषणा CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_NO_FLOW_COUNTER_ALLOC     0x2000UL
	__le16	dst_fid;
	__be16	l2_reग_लिखो_vlan_tpid;
	__be16	l2_reग_लिखो_vlan_tci;
	__le16	act_meter_id;
	__le16	ref_flow_handle;
	__be16	ethertype;
	__be16	outer_vlan_tci;
	__be16	dmac[3];
	__be16	inner_vlan_tci;
	__be16	smac[3];
	u8	ip_dst_mask_len;
	u8	ip_src_mask_len;
	__be32	ip_dst[4];
	__be32	ip_src[4];
	__be16	l4_src_port;
	__be16	l4_src_port_mask;
	__be16	l4_dst_port;
	__be16	l4_dst_port_mask;
	__be32	nat_ip_address[4];
	__be16	l2_reग_लिखो_dmac[3];
	__be16	nat_port;
	__be16	l2_reग_लिखो_smac[3];
	u8	ip_proto;
	u8	tunnel_type;
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_NONTUNNEL    0x0UL
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_VXLAN        0x1UL
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_NVGRE        0x2UL
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_L2GRE        0x3UL
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_IPIP         0x4UL
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_GENEVE       0x5UL
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_MPLS         0x6UL
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_STT          0x7UL
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_IPGRE        0x8UL
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_VXLAN_V4     0x9UL
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_IPGRE_V1     0xaUL
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_L2_ETYPE     0xbUL
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_VXLAN_GPE_V6 0xcUL
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_ANYTUNNEL    0xffUL
	#घोषणा CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_LAST        CFA_FLOW_ALLOC_REQ_TUNNEL_TYPE_ANYTUNNEL
पूर्ण;

/* hwrm_cfa_flow_alloc_output (size:256b/32B) */
काष्ठा hwrm_cfa_flow_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	flow_handle;
	u8	unused_0[2];
	__le32	flow_id;
	#घोषणा CFA_FLOW_ALLOC_RESP_FLOW_ID_VALUE_MASK 0x3fffffffUL
	#घोषणा CFA_FLOW_ALLOC_RESP_FLOW_ID_VALUE_SFT 0
	#घोषणा CFA_FLOW_ALLOC_RESP_FLOW_ID_TYPE      0x40000000UL
	#घोषणा CFA_FLOW_ALLOC_RESP_FLOW_ID_TYPE_INT    (0x0UL << 30)
	#घोषणा CFA_FLOW_ALLOC_RESP_FLOW_ID_TYPE_EXT    (0x1UL << 30)
	#घोषणा CFA_FLOW_ALLOC_RESP_FLOW_ID_TYPE_LAST  CFA_FLOW_ALLOC_RESP_FLOW_ID_TYPE_EXT
	#घोषणा CFA_FLOW_ALLOC_RESP_FLOW_ID_सूची       0x80000000UL
	#घोषणा CFA_FLOW_ALLOC_RESP_FLOW_ID_सूची_RX      (0x0UL << 31)
	#घोषणा CFA_FLOW_ALLOC_RESP_FLOW_ID_सूची_TX      (0x1UL << 31)
	#घोषणा CFA_FLOW_ALLOC_RESP_FLOW_ID_सूची_LAST   CFA_FLOW_ALLOC_RESP_FLOW_ID_सूची_TX
	__le64	ext_flow_handle;
	__le32	flow_counter_id;
	u8	unused_1[3];
	u8	valid;
पूर्ण;

/* hwrm_cfa_flow_alloc_cmd_err (size:64b/8B) */
काष्ठा hwrm_cfa_flow_alloc_cmd_err अणु
	u8	code;
	#घोषणा CFA_FLOW_ALLOC_CMD_ERR_CODE_UNKNOWN         0x0UL
	#घोषणा CFA_FLOW_ALLOC_CMD_ERR_CODE_L2_CONTEXT_TCAM 0x1UL
	#घोषणा CFA_FLOW_ALLOC_CMD_ERR_CODE_ACTION_RECORD   0x2UL
	#घोषणा CFA_FLOW_ALLOC_CMD_ERR_CODE_FLOW_COUNTER    0x3UL
	#घोषणा CFA_FLOW_ALLOC_CMD_ERR_CODE_WILD_CARD_TCAM  0x4UL
	#घोषणा CFA_FLOW_ALLOC_CMD_ERR_CODE_HASH_COLLISION  0x5UL
	#घोषणा CFA_FLOW_ALLOC_CMD_ERR_CODE_KEY_EXISTS      0x6UL
	#घोषणा CFA_FLOW_ALLOC_CMD_ERR_CODE_FLOW_CTXT_DB    0x7UL
	#घोषणा CFA_FLOW_ALLOC_CMD_ERR_CODE_LAST           CFA_FLOW_ALLOC_CMD_ERR_CODE_FLOW_CTXT_DB
	u8	unused_0[7];
पूर्ण;

/* hwrm_cfa_flow_मुक्त_input (size:256b/32B) */
काष्ठा hwrm_cfa_flow_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	flow_handle;
	__le16	unused_0;
	__le32	flow_counter_id;
	__le64	ext_flow_handle;
पूर्ण;

/* hwrm_cfa_flow_मुक्त_output (size:256b/32B) */
काष्ठा hwrm_cfa_flow_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le64	packet;
	__le64	byte;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_cfa_flow_info_input (size:256b/32B) */
काष्ठा hwrm_cfa_flow_info_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	flow_handle;
	#घोषणा CFA_FLOW_INFO_REQ_FLOW_HANDLE_MAX_MASK       0xfffUL
	#घोषणा CFA_FLOW_INFO_REQ_FLOW_HANDLE_MAX_SFT        0
	#घोषणा CFA_FLOW_INFO_REQ_FLOW_HANDLE_CNP_CNT        0x1000UL
	#घोषणा CFA_FLOW_INFO_REQ_FLOW_HANDLE_ROCEV1_CNT     0x2000UL
	#घोषणा CFA_FLOW_INFO_REQ_FLOW_HANDLE_ROCEV2_CNT     0x4000UL
	#घोषणा CFA_FLOW_INFO_REQ_FLOW_HANDLE_सूची_RX         0x8000UL
	u8	unused_0[6];
	__le64	ext_flow_handle;
पूर्ण;

/* hwrm_cfa_flow_info_output (size:5632b/704B) */
काष्ठा hwrm_cfa_flow_info_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	flags;
	#घोषणा CFA_FLOW_INFO_RESP_FLAGS_PATH_TX     0x1UL
	#घोषणा CFA_FLOW_INFO_RESP_FLAGS_PATH_RX     0x2UL
	u8	profile;
	__le16	src_fid;
	__le16	dst_fid;
	__le16	l2_ctxt_id;
	__le64	em_info;
	__le64	tcam_info;
	__le64	vfp_tcam_info;
	__le16	ar_id;
	__le16	flow_handle;
	__le32	tunnel_handle;
	__le16	flow_समयr;
	u8	unused_0[6];
	__le32	flow_key_data[130];
	__le32	flow_action_info[30];
	u8	unused_1[7];
	u8	valid;
पूर्ण;

/* hwrm_cfa_flow_stats_input (size:640b/80B) */
काष्ठा hwrm_cfa_flow_stats_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	num_flows;
	__le16	flow_handle_0;
	__le16	flow_handle_1;
	__le16	flow_handle_2;
	__le16	flow_handle_3;
	__le16	flow_handle_4;
	__le16	flow_handle_5;
	__le16	flow_handle_6;
	__le16	flow_handle_7;
	__le16	flow_handle_8;
	__le16	flow_handle_9;
	u8	unused_0[2];
	__le32	flow_id_0;
	__le32	flow_id_1;
	__le32	flow_id_2;
	__le32	flow_id_3;
	__le32	flow_id_4;
	__le32	flow_id_5;
	__le32	flow_id_6;
	__le32	flow_id_7;
	__le32	flow_id_8;
	__le32	flow_id_9;
पूर्ण;

/* hwrm_cfa_flow_stats_output (size:1408b/176B) */
काष्ठा hwrm_cfa_flow_stats_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le64	packet_0;
	__le64	packet_1;
	__le64	packet_2;
	__le64	packet_3;
	__le64	packet_4;
	__le64	packet_5;
	__le64	packet_6;
	__le64	packet_7;
	__le64	packet_8;
	__le64	packet_9;
	__le64	byte_0;
	__le64	byte_1;
	__le64	byte_2;
	__le64	byte_3;
	__le64	byte_4;
	__le64	byte_5;
	__le64	byte_6;
	__le64	byte_7;
	__le64	byte_8;
	__le64	byte_9;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_cfa_vfr_alloc_input (size:448b/56B) */
काष्ठा hwrm_cfa_vfr_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	vf_id;
	__le16	reserved;
	u8	unused_0[4];
	अक्षर	vfr_name[32];
पूर्ण;

/* hwrm_cfa_vfr_alloc_output (size:128b/16B) */
काष्ठा hwrm_cfa_vfr_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	rx_cfa_code;
	__le16	tx_cfa_action;
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_cfa_vfr_मुक्त_input (size:448b/56B) */
काष्ठा hwrm_cfa_vfr_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	अक्षर	vfr_name[32];
	__le16	vf_id;
	__le16	reserved;
	u8	unused_0[4];
पूर्ण;

/* hwrm_cfa_vfr_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_cfa_vfr_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_cfa_eem_qcaps_input (size:192b/24B) */
काष्ठा hwrm_cfa_eem_qcaps_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा CFA_EEM_QCAPS_REQ_FLAGS_PATH_TX               0x1UL
	#घोषणा CFA_EEM_QCAPS_REQ_FLAGS_PATH_RX               0x2UL
	#घोषणा CFA_EEM_QCAPS_REQ_FLAGS_PREFERRED_OFFLOAD     0x4UL
	__le32	unused_0;
पूर्ण;

/* hwrm_cfa_eem_qcaps_output (size:320b/40B) */
काष्ठा hwrm_cfa_eem_qcaps_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	flags;
	#घोषणा CFA_EEM_QCAPS_RESP_FLAGS_PATH_TX                                         0x1UL
	#घोषणा CFA_EEM_QCAPS_RESP_FLAGS_PATH_RX                                         0x2UL
	#घोषणा CFA_EEM_QCAPS_RESP_FLAGS_CENTRALIZED_MEMORY_MODEL_SUPPORTED              0x4UL
	#घोषणा CFA_EEM_QCAPS_RESP_FLAGS_DETACHED_CENTRALIZED_MEMORY_MODEL_SUPPORTED     0x8UL
	__le32	unused_0;
	__le32	supported;
	#घोषणा CFA_EEM_QCAPS_RESP_SUPPORTED_KEY0_TABLE                       0x1UL
	#घोषणा CFA_EEM_QCAPS_RESP_SUPPORTED_KEY1_TABLE                       0x2UL
	#घोषणा CFA_EEM_QCAPS_RESP_SUPPORTED_EXTERNAL_RECORD_TABLE            0x4UL
	#घोषणा CFA_EEM_QCAPS_RESP_SUPPORTED_EXTERNAL_FLOW_COUNTERS_TABLE     0x8UL
	#घोषणा CFA_EEM_QCAPS_RESP_SUPPORTED_FID_TABLE                        0x10UL
	__le32	max_entries_supported;
	__le16	key_entry_size;
	__le16	record_entry_size;
	__le16	efc_entry_size;
	__le16	fid_entry_size;
	u8	unused_1[7];
	u8	valid;
पूर्ण;

/* hwrm_cfa_eem_cfg_input (size:384b/48B) */
काष्ठा hwrm_cfa_eem_cfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा CFA_EEM_CFG_REQ_FLAGS_PATH_TX               0x1UL
	#घोषणा CFA_EEM_CFG_REQ_FLAGS_PATH_RX               0x2UL
	#घोषणा CFA_EEM_CFG_REQ_FLAGS_PREFERRED_OFFLOAD     0x4UL
	#घोषणा CFA_EEM_CFG_REQ_FLAGS_SECONDARY_PF          0x8UL
	__le16	group_id;
	__le16	unused_0;
	__le32	num_entries;
	__le32	unused_1;
	__le16	key0_ctx_id;
	__le16	key1_ctx_id;
	__le16	record_ctx_id;
	__le16	efc_ctx_id;
	__le16	fid_ctx_id;
	__le16	unused_2;
	__le32	unused_3;
पूर्ण;

/* hwrm_cfa_eem_cfg_output (size:128b/16B) */
काष्ठा hwrm_cfa_eem_cfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_cfa_eem_qcfg_input (size:192b/24B) */
काष्ठा hwrm_cfa_eem_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा CFA_EEM_QCFG_REQ_FLAGS_PATH_TX     0x1UL
	#घोषणा CFA_EEM_QCFG_REQ_FLAGS_PATH_RX     0x2UL
	__le32	unused_0;
पूर्ण;

/* hwrm_cfa_eem_qcfg_output (size:256b/32B) */
काष्ठा hwrm_cfa_eem_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	flags;
	#घोषणा CFA_EEM_QCFG_RESP_FLAGS_PATH_TX               0x1UL
	#घोषणा CFA_EEM_QCFG_RESP_FLAGS_PATH_RX               0x2UL
	#घोषणा CFA_EEM_QCFG_RESP_FLAGS_PREFERRED_OFFLOAD     0x4UL
	__le32	num_entries;
	__le16	key0_ctx_id;
	__le16	key1_ctx_id;
	__le16	record_ctx_id;
	__le16	efc_ctx_id;
	__le16	fid_ctx_id;
	u8	unused_2[5];
	u8	valid;
पूर्ण;

/* hwrm_cfa_eem_op_input (size:192b/24B) */
काष्ठा hwrm_cfa_eem_op_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा CFA_EEM_OP_REQ_FLAGS_PATH_TX     0x1UL
	#घोषणा CFA_EEM_OP_REQ_FLAGS_PATH_RX     0x2UL
	__le16	unused_0;
	__le16	op;
	#घोषणा CFA_EEM_OP_REQ_OP_RESERVED    0x0UL
	#घोषणा CFA_EEM_OP_REQ_OP_EEM_DISABLE 0x1UL
	#घोषणा CFA_EEM_OP_REQ_OP_EEM_ENABLE  0x2UL
	#घोषणा CFA_EEM_OP_REQ_OP_EEM_CLEANUP 0x3UL
	#घोषणा CFA_EEM_OP_REQ_OP_LAST       CFA_EEM_OP_REQ_OP_EEM_CLEANUP
पूर्ण;

/* hwrm_cfa_eem_op_output (size:128b/16B) */
काष्ठा hwrm_cfa_eem_op_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_cfa_adv_flow_mgnt_qcaps_input (size:256b/32B) */
काष्ठा hwrm_cfa_adv_flow_mgnt_qcaps_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	unused_0[4];
पूर्ण;

/* hwrm_cfa_adv_flow_mgnt_qcaps_output (size:128b/16B) */
काष्ठा hwrm_cfa_adv_flow_mgnt_qcaps_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	flags;
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_FLOW_HND_16BIT_SUPPORTED                     0x1UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_FLOW_HND_64BIT_SUPPORTED                     0x2UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_FLOW_BATCH_DELETE_SUPPORTED                  0x4UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_FLOW_RESET_ALL_SUPPORTED                     0x8UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_NTUPLE_FLOW_DEST_FUNC_SUPPORTED              0x10UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_TX_EEM_FLOW_SUPPORTED                        0x20UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_RX_EEM_FLOW_SUPPORTED                        0x40UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_FLOW_COUNTER_ALLOC_SUPPORTED                 0x80UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_RFS_RING_TBL_IDX_SUPPORTED                   0x100UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_UNTAGGED_VLAN_SUPPORTED                      0x200UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_XDP_SUPPORTED                                0x400UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_L2_HEADER_SOURCE_FIELDS_SUPPORTED            0x800UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_NTUPLE_FLOW_RX_ARP_SUPPORTED                 0x1000UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_RFS_RING_TBL_IDX_V2_SUPPORTED                0x2000UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_NTUPLE_FLOW_RX_ETHERTYPE_IP_SUPPORTED        0x4000UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_TRUFLOW_CAPABLE                              0x8000UL
	#घोषणा CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_L2_FILTER_TRAFFIC_TYPE_L2_ROCE_SUPPORTED     0x10000UL
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_tunnel_dst_port_query_input (size:192b/24B) */
काष्ठा hwrm_tunnel_dst_port_query_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	u8	tunnel_type;
	#घोषणा TUNNEL_DST_PORT_QUERY_REQ_TUNNEL_TYPE_VXLAN        0x1UL
	#घोषणा TUNNEL_DST_PORT_QUERY_REQ_TUNNEL_TYPE_GENEVE       0x5UL
	#घोषणा TUNNEL_DST_PORT_QUERY_REQ_TUNNEL_TYPE_VXLAN_V4     0x9UL
	#घोषणा TUNNEL_DST_PORT_QUERY_REQ_TUNNEL_TYPE_IPGRE_V1     0xaUL
	#घोषणा TUNNEL_DST_PORT_QUERY_REQ_TUNNEL_TYPE_L2_ETYPE     0xbUL
	#घोषणा TUNNEL_DST_PORT_QUERY_REQ_TUNNEL_TYPE_VXLAN_GPE_V6 0xcUL
	#घोषणा TUNNEL_DST_PORT_QUERY_REQ_TUNNEL_TYPE_LAST        TUNNEL_DST_PORT_QUERY_REQ_TUNNEL_TYPE_VXLAN_GPE_V6
	u8	unused_0[7];
पूर्ण;

/* hwrm_tunnel_dst_port_query_output (size:128b/16B) */
काष्ठा hwrm_tunnel_dst_port_query_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	tunnel_dst_port_id;
	__be16	tunnel_dst_port_val;
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_tunnel_dst_port_alloc_input (size:192b/24B) */
काष्ठा hwrm_tunnel_dst_port_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	u8	tunnel_type;
	#घोषणा TUNNEL_DST_PORT_ALLOC_REQ_TUNNEL_TYPE_VXLAN        0x1UL
	#घोषणा TUNNEL_DST_PORT_ALLOC_REQ_TUNNEL_TYPE_GENEVE       0x5UL
	#घोषणा TUNNEL_DST_PORT_ALLOC_REQ_TUNNEL_TYPE_VXLAN_V4     0x9UL
	#घोषणा TUNNEL_DST_PORT_ALLOC_REQ_TUNNEL_TYPE_IPGRE_V1     0xaUL
	#घोषणा TUNNEL_DST_PORT_ALLOC_REQ_TUNNEL_TYPE_L2_ETYPE     0xbUL
	#घोषणा TUNNEL_DST_PORT_ALLOC_REQ_TUNNEL_TYPE_VXLAN_GPE_V6 0xcUL
	#घोषणा TUNNEL_DST_PORT_ALLOC_REQ_TUNNEL_TYPE_LAST        TUNNEL_DST_PORT_ALLOC_REQ_TUNNEL_TYPE_VXLAN_GPE_V6
	u8	unused_0;
	__be16	tunnel_dst_port_val;
	u8	unused_1[4];
पूर्ण;

/* hwrm_tunnel_dst_port_alloc_output (size:128b/16B) */
काष्ठा hwrm_tunnel_dst_port_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	tunnel_dst_port_id;
	u8	unused_0[5];
	u8	valid;
पूर्ण;

/* hwrm_tunnel_dst_port_मुक्त_input (size:192b/24B) */
काष्ठा hwrm_tunnel_dst_port_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	u8	tunnel_type;
	#घोषणा TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_VXLAN        0x1UL
	#घोषणा TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_GENEVE       0x5UL
	#घोषणा TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_VXLAN_V4     0x9UL
	#घोषणा TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_IPGRE_V1     0xaUL
	#घोषणा TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_L2_ETYPE     0xbUL
	#घोषणा TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_VXLAN_GPE_V6 0xcUL
	#घोषणा TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_LAST        TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_VXLAN_GPE_V6
	u8	unused_0;
	__le16	tunnel_dst_port_id;
	u8	unused_1[4];
पूर्ण;

/* hwrm_tunnel_dst_port_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_tunnel_dst_port_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_1[7];
	u8	valid;
पूर्ण;

/* ctx_hw_stats (size:1280b/160B) */
काष्ठा ctx_hw_stats अणु
	__le64	rx_ucast_pkts;
	__le64	rx_mcast_pkts;
	__le64	rx_bcast_pkts;
	__le64	rx_discard_pkts;
	__le64	rx_error_pkts;
	__le64	rx_ucast_bytes;
	__le64	rx_mcast_bytes;
	__le64	rx_bcast_bytes;
	__le64	tx_ucast_pkts;
	__le64	tx_mcast_pkts;
	__le64	tx_bcast_pkts;
	__le64	tx_error_pkts;
	__le64	tx_discard_pkts;
	__le64	tx_ucast_bytes;
	__le64	tx_mcast_bytes;
	__le64	tx_bcast_bytes;
	__le64	tpa_pkts;
	__le64	tpa_bytes;
	__le64	tpa_events;
	__le64	tpa_पातs;
पूर्ण;

/* ctx_hw_stats_ext (size:1408b/176B) */
काष्ठा ctx_hw_stats_ext अणु
	__le64	rx_ucast_pkts;
	__le64	rx_mcast_pkts;
	__le64	rx_bcast_pkts;
	__le64	rx_discard_pkts;
	__le64	rx_error_pkts;
	__le64	rx_ucast_bytes;
	__le64	rx_mcast_bytes;
	__le64	rx_bcast_bytes;
	__le64	tx_ucast_pkts;
	__le64	tx_mcast_pkts;
	__le64	tx_bcast_pkts;
	__le64	tx_error_pkts;
	__le64	tx_discard_pkts;
	__le64	tx_ucast_bytes;
	__le64	tx_mcast_bytes;
	__le64	tx_bcast_bytes;
	__le64	rx_tpa_eligible_pkt;
	__le64	rx_tpa_eligible_bytes;
	__le64	rx_tpa_pkt;
	__le64	rx_tpa_bytes;
	__le64	rx_tpa_errors;
	__le64	rx_tpa_events;
पूर्ण;

/* hwrm_stat_ctx_alloc_input (size:256b/32B) */
काष्ठा hwrm_stat_ctx_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	stats_dma_addr;
	__le32	update_period_ms;
	u8	stat_ctx_flags;
	#घोषणा STAT_CTX_ALLOC_REQ_STAT_CTX_FLAGS_ROCE     0x1UL
	u8	unused_0;
	__le16	stats_dma_length;
पूर्ण;

/* hwrm_stat_ctx_alloc_output (size:128b/16B) */
काष्ठा hwrm_stat_ctx_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	stat_ctx_id;
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_stat_ctx_मुक्त_input (size:192b/24B) */
काष्ठा hwrm_stat_ctx_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	stat_ctx_id;
	u8	unused_0[4];
पूर्ण;

/* hwrm_stat_ctx_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_stat_ctx_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	stat_ctx_id;
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_stat_ctx_query_input (size:192b/24B) */
काष्ठा hwrm_stat_ctx_query_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	stat_ctx_id;
	u8	flags;
	#घोषणा STAT_CTX_QUERY_REQ_FLAGS_COUNTER_MASK     0x1UL
	u8	unused_0[3];
पूर्ण;

/* hwrm_stat_ctx_query_output (size:1408b/176B) */
काष्ठा hwrm_stat_ctx_query_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le64	tx_ucast_pkts;
	__le64	tx_mcast_pkts;
	__le64	tx_bcast_pkts;
	__le64	tx_discard_pkts;
	__le64	tx_error_pkts;
	__le64	tx_ucast_bytes;
	__le64	tx_mcast_bytes;
	__le64	tx_bcast_bytes;
	__le64	rx_ucast_pkts;
	__le64	rx_mcast_pkts;
	__le64	rx_bcast_pkts;
	__le64	rx_discard_pkts;
	__le64	rx_error_pkts;
	__le64	rx_ucast_bytes;
	__le64	rx_mcast_bytes;
	__le64	rx_bcast_bytes;
	__le64	rx_agg_pkts;
	__le64	rx_agg_bytes;
	__le64	rx_agg_events;
	__le64	rx_agg_पातs;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_stat_ext_ctx_query_input (size:192b/24B) */
काष्ठा hwrm_stat_ext_ctx_query_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	stat_ctx_id;
	u8	flags;
	#घोषणा STAT_EXT_CTX_QUERY_REQ_FLAGS_COUNTER_MASK     0x1UL
	u8	unused_0[3];
पूर्ण;

/* hwrm_stat_ext_ctx_query_output (size:1536b/192B) */
काष्ठा hwrm_stat_ext_ctx_query_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le64	rx_ucast_pkts;
	__le64	rx_mcast_pkts;
	__le64	rx_bcast_pkts;
	__le64	rx_discard_pkts;
	__le64	rx_error_pkts;
	__le64	rx_ucast_bytes;
	__le64	rx_mcast_bytes;
	__le64	rx_bcast_bytes;
	__le64	tx_ucast_pkts;
	__le64	tx_mcast_pkts;
	__le64	tx_bcast_pkts;
	__le64	tx_error_pkts;
	__le64	tx_discard_pkts;
	__le64	tx_ucast_bytes;
	__le64	tx_mcast_bytes;
	__le64	tx_bcast_bytes;
	__le64	rx_tpa_eligible_pkt;
	__le64	rx_tpa_eligible_bytes;
	__le64	rx_tpa_pkt;
	__le64	rx_tpa_bytes;
	__le64	rx_tpa_errors;
	__le64	rx_tpa_events;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_stat_ctx_clr_stats_input (size:192b/24B) */
काष्ठा hwrm_stat_ctx_clr_stats_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	stat_ctx_id;
	u8	unused_0[4];
पूर्ण;

/* hwrm_stat_ctx_clr_stats_output (size:128b/16B) */
काष्ठा hwrm_stat_ctx_clr_stats_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_pcie_qstats_input (size:256b/32B) */
काष्ठा hwrm_pcie_qstats_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	pcie_stat_size;
	u8	unused_0[6];
	__le64	pcie_stat_host_addr;
पूर्ण;

/* hwrm_pcie_qstats_output (size:128b/16B) */
काष्ठा hwrm_pcie_qstats_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	pcie_stat_size;
	u8	unused_0[5];
	u8	valid;
पूर्ण;

/* pcie_ctx_hw_stats (size:768b/96B) */
काष्ठा pcie_ctx_hw_stats अणु
	__le64	pcie_pl_संकेत_पूर्णांकegrity;
	__le64	pcie_dl_संकेत_पूर्णांकegrity;
	__le64	pcie_tl_संकेत_पूर्णांकegrity;
	__le64	pcie_link_पूर्णांकegrity;
	__le64	pcie_tx_traffic_rate;
	__le64	pcie_rx_traffic_rate;
	__le64	pcie_tx_dllp_statistics;
	__le64	pcie_rx_dllp_statistics;
	__le64	pcie_equalization_समय;
	__le32	pcie_ltssm_histogram[4];
	__le64	pcie_recovery_histogram;
पूर्ण;

/* hwrm_fw_reset_input (size:192b/24B) */
काष्ठा hwrm_fw_reset_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	u8	embedded_proc_type;
	#घोषणा FW_RESET_REQ_EMBEDDED_PROC_TYPE_BOOT                  0x0UL
	#घोषणा FW_RESET_REQ_EMBEDDED_PROC_TYPE_MGMT                  0x1UL
	#घोषणा FW_RESET_REQ_EMBEDDED_PROC_TYPE_NETCTRL               0x2UL
	#घोषणा FW_RESET_REQ_EMBEDDED_PROC_TYPE_ROCE                  0x3UL
	#घोषणा FW_RESET_REQ_EMBEDDED_PROC_TYPE_HOST                  0x4UL
	#घोषणा FW_RESET_REQ_EMBEDDED_PROC_TYPE_AP                    0x5UL
	#घोषणा FW_RESET_REQ_EMBEDDED_PROC_TYPE_CHIP                  0x6UL
	#घोषणा FW_RESET_REQ_EMBEDDED_PROC_TYPE_HOST_RESOURCE_REINIT  0x7UL
	#घोषणा FW_RESET_REQ_EMBEDDED_PROC_TYPE_IMPACTLESS_ACTIVATION 0x8UL
	#घोषणा FW_RESET_REQ_EMBEDDED_PROC_TYPE_LAST                 FW_RESET_REQ_EMBEDDED_PROC_TYPE_IMPACTLESS_ACTIVATION
	u8	selfrst_status;
	#घोषणा FW_RESET_REQ_SELFRST_STATUS_SELFRSTNONE      0x0UL
	#घोषणा FW_RESET_REQ_SELFRST_STATUS_SELFRSTASAP      0x1UL
	#घोषणा FW_RESET_REQ_SELFRST_STATUS_SELFRSTPCIERST   0x2UL
	#घोषणा FW_RESET_REQ_SELFRST_STATUS_SELFRSTIMMEDIATE 0x3UL
	#घोषणा FW_RESET_REQ_SELFRST_STATUS_LAST            FW_RESET_REQ_SELFRST_STATUS_SELFRSTIMMEDIATE
	u8	host_idx;
	u8	flags;
	#घोषणा FW_RESET_REQ_FLAGS_RESET_GRACEFUL     0x1UL
	u8	unused_0[4];
पूर्ण;

/* hwrm_fw_reset_output (size:128b/16B) */
काष्ठा hwrm_fw_reset_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	selfrst_status;
	#घोषणा FW_RESET_RESP_SELFRST_STATUS_SELFRSTNONE      0x0UL
	#घोषणा FW_RESET_RESP_SELFRST_STATUS_SELFRSTASAP      0x1UL
	#घोषणा FW_RESET_RESP_SELFRST_STATUS_SELFRSTPCIERST   0x2UL
	#घोषणा FW_RESET_RESP_SELFRST_STATUS_SELFRSTIMMEDIATE 0x3UL
	#घोषणा FW_RESET_RESP_SELFRST_STATUS_LAST            FW_RESET_RESP_SELFRST_STATUS_SELFRSTIMMEDIATE
	u8	unused_0[6];
	u8	valid;
पूर्ण;

/* hwrm_fw_qstatus_input (size:192b/24B) */
काष्ठा hwrm_fw_qstatus_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	u8	embedded_proc_type;
	#घोषणा FW_QSTATUS_REQ_EMBEDDED_PROC_TYPE_BOOT    0x0UL
	#घोषणा FW_QSTATUS_REQ_EMBEDDED_PROC_TYPE_MGMT    0x1UL
	#घोषणा FW_QSTATUS_REQ_EMBEDDED_PROC_TYPE_NETCTRL 0x2UL
	#घोषणा FW_QSTATUS_REQ_EMBEDDED_PROC_TYPE_ROCE    0x3UL
	#घोषणा FW_QSTATUS_REQ_EMBEDDED_PROC_TYPE_HOST    0x4UL
	#घोषणा FW_QSTATUS_REQ_EMBEDDED_PROC_TYPE_AP      0x5UL
	#घोषणा FW_QSTATUS_REQ_EMBEDDED_PROC_TYPE_CHIP    0x6UL
	#घोषणा FW_QSTATUS_REQ_EMBEDDED_PROC_TYPE_LAST   FW_QSTATUS_REQ_EMBEDDED_PROC_TYPE_CHIP
	u8	unused_0[7];
पूर्ण;

/* hwrm_fw_qstatus_output (size:128b/16B) */
काष्ठा hwrm_fw_qstatus_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	selfrst_status;
	#घोषणा FW_QSTATUS_RESP_SELFRST_STATUS_SELFRSTNONE    0x0UL
	#घोषणा FW_QSTATUS_RESP_SELFRST_STATUS_SELFRSTASAP    0x1UL
	#घोषणा FW_QSTATUS_RESP_SELFRST_STATUS_SELFRSTPCIERST 0x2UL
	#घोषणा FW_QSTATUS_RESP_SELFRST_STATUS_SELFRSTPOWER   0x3UL
	#घोषणा FW_QSTATUS_RESP_SELFRST_STATUS_LAST          FW_QSTATUS_RESP_SELFRST_STATUS_SELFRSTPOWER
	u8	nvm_option_action_status;
	#घोषणा FW_QSTATUS_RESP_NVM_OPTION_ACTION_STATUS_NVMOPT_ACTION_NONE     0x0UL
	#घोषणा FW_QSTATUS_RESP_NVM_OPTION_ACTION_STATUS_NVMOPT_ACTION_HOTRESET 0x1UL
	#घोषणा FW_QSTATUS_RESP_NVM_OPTION_ACTION_STATUS_NVMOPT_ACTION_WARMBOOT 0x2UL
	#घोषणा FW_QSTATUS_RESP_NVM_OPTION_ACTION_STATUS_NVMOPT_ACTION_COLDBOOT 0x3UL
	#घोषणा FW_QSTATUS_RESP_NVM_OPTION_ACTION_STATUS_LAST                  FW_QSTATUS_RESP_NVM_OPTION_ACTION_STATUS_NVMOPT_ACTION_COLDBOOT
	u8	unused_0[5];
	u8	valid;
पूर्ण;

/* hwrm_fw_set_समय_input (size:256b/32B) */
काष्ठा hwrm_fw_set_समय_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	year;
	#घोषणा FW_SET_TIME_REQ_YEAR_UNKNOWN 0x0UL
	#घोषणा FW_SET_TIME_REQ_YEAR_LAST   FW_SET_TIME_REQ_YEAR_UNKNOWN
	u8	month;
	u8	day;
	u8	hour;
	u8	minute;
	u8	second;
	u8	unused_0;
	__le16	millisecond;
	__le16	zone;
	#घोषणा FW_SET_TIME_REQ_ZONE_UTC     0
	#घोषणा FW_SET_TIME_REQ_ZONE_UNKNOWN 65535
	#घोषणा FW_SET_TIME_REQ_ZONE_LAST   FW_SET_TIME_REQ_ZONE_UNKNOWN
	u8	unused_1[4];
पूर्ण;

/* hwrm_fw_set_समय_output (size:128b/16B) */
काष्ठा hwrm_fw_set_समय_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_काष्ठा_hdr (size:128b/16B) */
काष्ठा hwrm_काष्ठा_hdr अणु
	__le16	काष्ठा_id;
	#घोषणा STRUCT_HDR_STRUCT_ID_LLDP_CFG           0x41bUL
	#घोषणा STRUCT_HDR_STRUCT_ID_DCBX_ETS           0x41dUL
	#घोषणा STRUCT_HDR_STRUCT_ID_DCBX_PFC           0x41fUL
	#घोषणा STRUCT_HDR_STRUCT_ID_DCBX_APP           0x421UL
	#घोषणा STRUCT_HDR_STRUCT_ID_DCBX_FEATURE_STATE 0x422UL
	#घोषणा STRUCT_HDR_STRUCT_ID_LLDP_GENERIC       0x424UL
	#घोषणा STRUCT_HDR_STRUCT_ID_LLDP_DEVICE        0x426UL
	#घोषणा STRUCT_HDR_STRUCT_ID_POWER_BKUP         0x427UL
	#घोषणा STRUCT_HDR_STRUCT_ID_AFM_OPAQUE         0x1UL
	#घोषणा STRUCT_HDR_STRUCT_ID_PORT_DESCRIPTION   0xaUL
	#घोषणा STRUCT_HDR_STRUCT_ID_RSS_V2             0x64UL
	#घोषणा STRUCT_HDR_STRUCT_ID_MSIX_PER_VF        0xc8UL
	#घोषणा STRUCT_HDR_STRUCT_ID_LAST              STRUCT_HDR_STRUCT_ID_MSIX_PER_VF
	__le16	len;
	u8	version;
	u8	count;
	__le16	subtype;
	__le16	next_offset;
	#घोषणा STRUCT_HDR_NEXT_OFFSET_LAST 0x0UL
	u8	unused_0[6];
पूर्ण;

/* hwrm_काष्ठा_data_dcbx_app (size:64b/8B) */
काष्ठा hwrm_काष्ठा_data_dcbx_app अणु
	__be16	protocol_id;
	u8	protocol_selector;
	#घोषणा STRUCT_DATA_DCBX_APP_PROTOCOL_SELECTOR_ETHER_TYPE   0x1UL
	#घोषणा STRUCT_DATA_DCBX_APP_PROTOCOL_SELECTOR_TCP_PORT     0x2UL
	#घोषणा STRUCT_DATA_DCBX_APP_PROTOCOL_SELECTOR_UDP_PORT     0x3UL
	#घोषणा STRUCT_DATA_DCBX_APP_PROTOCOL_SELECTOR_TCP_UDP_PORT 0x4UL
	#घोषणा STRUCT_DATA_DCBX_APP_PROTOCOL_SELECTOR_LAST        STRUCT_DATA_DCBX_APP_PROTOCOL_SELECTOR_TCP_UDP_PORT
	u8	priority;
	u8	valid;
	u8	unused_0[3];
पूर्ण;

/* hwrm_fw_set_काष्ठाured_data_input (size:256b/32B) */
काष्ठा hwrm_fw_set_काष्ठाured_data_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	src_data_addr;
	__le16	data_len;
	u8	hdr_cnt;
	u8	unused_0[5];
पूर्ण;

/* hwrm_fw_set_काष्ठाured_data_output (size:128b/16B) */
काष्ठा hwrm_fw_set_काष्ठाured_data_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_fw_set_काष्ठाured_data_cmd_err (size:64b/8B) */
काष्ठा hwrm_fw_set_काष्ठाured_data_cmd_err अणु
	u8	code;
	#घोषणा FW_SET_STRUCTURED_DATA_CMD_ERR_CODE_UNKNOWN     0x0UL
	#घोषणा FW_SET_STRUCTURED_DATA_CMD_ERR_CODE_BAD_HDR_CNT 0x1UL
	#घोषणा FW_SET_STRUCTURED_DATA_CMD_ERR_CODE_BAD_FMT     0x2UL
	#घोषणा FW_SET_STRUCTURED_DATA_CMD_ERR_CODE_BAD_ID      0x3UL
	#घोषणा FW_SET_STRUCTURED_DATA_CMD_ERR_CODE_LAST       FW_SET_STRUCTURED_DATA_CMD_ERR_CODE_BAD_ID
	u8	unused_0[7];
पूर्ण;

/* hwrm_fw_get_काष्ठाured_data_input (size:256b/32B) */
काष्ठा hwrm_fw_get_काष्ठाured_data_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	dest_data_addr;
	__le16	data_len;
	__le16	काष्ठाure_id;
	__le16	subtype;
	#घोषणा FW_GET_STRUCTURED_DATA_REQ_SUBTYPE_UNUSED                  0x0UL
	#घोषणा FW_GET_STRUCTURED_DATA_REQ_SUBTYPE_ALL                     0xffffUL
	#घोषणा FW_GET_STRUCTURED_DATA_REQ_SUBTYPE_NEAR_BRIDGE_ADMIN       0x100UL
	#घोषणा FW_GET_STRUCTURED_DATA_REQ_SUBTYPE_NEAR_BRIDGE_PEER        0x101UL
	#घोषणा FW_GET_STRUCTURED_DATA_REQ_SUBTYPE_NEAR_BRIDGE_OPERATIONAL 0x102UL
	#घोषणा FW_GET_STRUCTURED_DATA_REQ_SUBTYPE_NON_TPMR_ADMIN          0x200UL
	#घोषणा FW_GET_STRUCTURED_DATA_REQ_SUBTYPE_NON_TPMR_PEER           0x201UL
	#घोषणा FW_GET_STRUCTURED_DATA_REQ_SUBTYPE_NON_TPMR_OPERATIONAL    0x202UL
	#घोषणा FW_GET_STRUCTURED_DATA_REQ_SUBTYPE_HOST_OPERATIONAL        0x300UL
	#घोषणा FW_GET_STRUCTURED_DATA_REQ_SUBTYPE_LAST                   FW_GET_STRUCTURED_DATA_REQ_SUBTYPE_HOST_OPERATIONAL
	u8	count;
	u8	unused_0;
पूर्ण;

/* hwrm_fw_get_काष्ठाured_data_output (size:128b/16B) */
काष्ठा hwrm_fw_get_काष्ठाured_data_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	hdr_cnt;
	u8	unused_0[6];
	u8	valid;
पूर्ण;

/* hwrm_fw_get_काष्ठाured_data_cmd_err (size:64b/8B) */
काष्ठा hwrm_fw_get_काष्ठाured_data_cmd_err अणु
	u8	code;
	#घोषणा FW_GET_STRUCTURED_DATA_CMD_ERR_CODE_UNKNOWN 0x0UL
	#घोषणा FW_GET_STRUCTURED_DATA_CMD_ERR_CODE_BAD_ID  0x3UL
	#घोषणा FW_GET_STRUCTURED_DATA_CMD_ERR_CODE_LAST   FW_GET_STRUCTURED_DATA_CMD_ERR_CODE_BAD_ID
	u8	unused_0[7];
पूर्ण;

/* hwrm_exec_fwd_resp_input (size:1024b/128B) */
काष्ठा hwrm_exec_fwd_resp_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	encap_request[26];
	__le16	encap_resp_target_id;
	u8	unused_0[6];
पूर्ण;

/* hwrm_exec_fwd_resp_output (size:128b/16B) */
काष्ठा hwrm_exec_fwd_resp_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_reject_fwd_resp_input (size:1024b/128B) */
काष्ठा hwrm_reject_fwd_resp_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	encap_request[26];
	__le16	encap_resp_target_id;
	u8	unused_0[6];
पूर्ण;

/* hwrm_reject_fwd_resp_output (size:128b/16B) */
काष्ठा hwrm_reject_fwd_resp_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_fwd_resp_input (size:1024b/128B) */
काष्ठा hwrm_fwd_resp_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	encap_resp_target_id;
	__le16	encap_resp_cmpl_ring;
	__le16	encap_resp_len;
	u8	unused_0;
	u8	unused_1;
	__le64	encap_resp_addr;
	__le32	encap_resp[24];
पूर्ण;

/* hwrm_fwd_resp_output (size:128b/16B) */
काष्ठा hwrm_fwd_resp_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_fwd_async_event_cmpl_input (size:320b/40B) */
काष्ठा hwrm_fwd_async_event_cmpl_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	encap_async_event_target_id;
	u8	unused_0[6];
	__le32	encap_async_event_cmpl[4];
पूर्ण;

/* hwrm_fwd_async_event_cmpl_output (size:128b/16B) */
काष्ठा hwrm_fwd_async_event_cmpl_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_temp_monitor_query_input (size:128b/16B) */
काष्ठा hwrm_temp_monitor_query_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
पूर्ण;

/* hwrm_temp_monitor_query_output (size:128b/16B) */
काष्ठा hwrm_temp_monitor_query_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	temp;
	u8	phy_temp;
	u8	om_temp;
	u8	flags;
	#घोषणा TEMP_MONITOR_QUERY_RESP_FLAGS_TEMP_NOT_AVAILABLE         0x1UL
	#घोषणा TEMP_MONITOR_QUERY_RESP_FLAGS_PHY_TEMP_NOT_AVAILABLE     0x2UL
	#घोषणा TEMP_MONITOR_QUERY_RESP_FLAGS_OM_NOT_PRESENT             0x4UL
	#घोषणा TEMP_MONITOR_QUERY_RESP_FLAGS_OM_TEMP_NOT_AVAILABLE      0x8UL
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_wol_filter_alloc_input (size:512b/64B) */
काष्ठा hwrm_wol_filter_alloc_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	__le32	enables;
	#घोषणा WOL_FILTER_ALLOC_REQ_ENABLES_MAC_ADDRESS           0x1UL
	#घोषणा WOL_FILTER_ALLOC_REQ_ENABLES_PATTERN_OFFSET        0x2UL
	#घोषणा WOL_FILTER_ALLOC_REQ_ENABLES_PATTERN_BUF_SIZE      0x4UL
	#घोषणा WOL_FILTER_ALLOC_REQ_ENABLES_PATTERN_BUF_ADDR      0x8UL
	#घोषणा WOL_FILTER_ALLOC_REQ_ENABLES_PATTERN_MASK_ADDR     0x10UL
	#घोषणा WOL_FILTER_ALLOC_REQ_ENABLES_PATTERN_MASK_SIZE     0x20UL
	__le16	port_id;
	u8	wol_type;
	#घोषणा WOL_FILTER_ALLOC_REQ_WOL_TYPE_MAGICPKT 0x0UL
	#घोषणा WOL_FILTER_ALLOC_REQ_WOL_TYPE_BMP      0x1UL
	#घोषणा WOL_FILTER_ALLOC_REQ_WOL_TYPE_INVALID  0xffUL
	#घोषणा WOL_FILTER_ALLOC_REQ_WOL_TYPE_LAST    WOL_FILTER_ALLOC_REQ_WOL_TYPE_INVALID
	u8	unused_0[5];
	u8	mac_address[6];
	__le16	pattern_offset;
	__le16	pattern_buf_size;
	__le16	pattern_mask_size;
	u8	unused_1[4];
	__le64	pattern_buf_addr;
	__le64	pattern_mask_addr;
पूर्ण;

/* hwrm_wol_filter_alloc_output (size:128b/16B) */
काष्ठा hwrm_wol_filter_alloc_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	wol_filter_id;
	u8	unused_0[6];
	u8	valid;
पूर्ण;

/* hwrm_wol_filter_मुक्त_input (size:256b/32B) */
काष्ठा hwrm_wol_filter_मुक्त_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	flags;
	#घोषणा WOL_FILTER_FREE_REQ_FLAGS_FREE_ALL_WOL_FILTERS     0x1UL
	__le32	enables;
	#घोषणा WOL_FILTER_FREE_REQ_ENABLES_WOL_FILTER_ID     0x1UL
	__le16	port_id;
	u8	wol_filter_id;
	u8	unused_0[5];
पूर्ण;

/* hwrm_wol_filter_मुक्त_output (size:128b/16B) */
काष्ठा hwrm_wol_filter_मुक्त_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_wol_filter_qcfg_input (size:448b/56B) */
काष्ठा hwrm_wol_filter_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	port_id;
	__le16	handle;
	u8	unused_0[4];
	__le64	pattern_buf_addr;
	__le16	pattern_buf_size;
	u8	unused_1[6];
	__le64	pattern_mask_addr;
	__le16	pattern_mask_size;
	u8	unused_2[6];
पूर्ण;

/* hwrm_wol_filter_qcfg_output (size:256b/32B) */
काष्ठा hwrm_wol_filter_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	next_handle;
	u8	wol_filter_id;
	u8	wol_type;
	#घोषणा WOL_FILTER_QCFG_RESP_WOL_TYPE_MAGICPKT 0x0UL
	#घोषणा WOL_FILTER_QCFG_RESP_WOL_TYPE_BMP      0x1UL
	#घोषणा WOL_FILTER_QCFG_RESP_WOL_TYPE_INVALID  0xffUL
	#घोषणा WOL_FILTER_QCFG_RESP_WOL_TYPE_LAST    WOL_FILTER_QCFG_RESP_WOL_TYPE_INVALID
	__le32	unused_0;
	u8	mac_address[6];
	__le16	pattern_offset;
	__le16	pattern_size;
	__le16	pattern_mask_size;
	u8	unused_1[3];
	u8	valid;
पूर्ण;

/* hwrm_wol_reason_qcfg_input (size:320b/40B) */
काष्ठा hwrm_wol_reason_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	port_id;
	u8	unused_0[6];
	__le64	wol_pkt_buf_addr;
	__le16	wol_pkt_buf_size;
	u8	unused_1[6];
पूर्ण;

/* hwrm_wol_reason_qcfg_output (size:128b/16B) */
काष्ठा hwrm_wol_reason_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	wol_filter_id;
	u8	wol_reason;
	#घोषणा WOL_REASON_QCFG_RESP_WOL_REASON_MAGICPKT 0x0UL
	#घोषणा WOL_REASON_QCFG_RESP_WOL_REASON_BMP      0x1UL
	#घोषणा WOL_REASON_QCFG_RESP_WOL_REASON_INVALID  0xffUL
	#घोषणा WOL_REASON_QCFG_RESP_WOL_REASON_LAST    WOL_REASON_QCFG_RESP_WOL_REASON_INVALID
	u8	wol_pkt_len;
	u8	unused_0[4];
	u8	valid;
पूर्ण;

/* hwrm_dbg_पढ़ो_direct_input (size:256b/32B) */
काष्ठा hwrm_dbg_पढ़ो_direct_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	host_dest_addr;
	__le32	पढ़ो_addr;
	__le32	पढ़ो_len32;
पूर्ण;

/* hwrm_dbg_पढ़ो_direct_output (size:128b/16B) */
काष्ठा hwrm_dbg_पढ़ो_direct_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	crc32;
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_dbg_qcaps_input (size:192b/24B) */
काष्ठा hwrm_dbg_qcaps_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	fid;
	u8	unused_0[6];
पूर्ण;

/* hwrm_dbg_qcaps_output (size:192b/24B) */
काष्ठा hwrm_dbg_qcaps_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	fid;
	u8	unused_0[2];
	__le32	coredump_component_disable_caps;
	#घोषणा DBG_QCAPS_RESP_COREDUMP_COMPONENT_DISABLE_CAPS_NVRAM     0x1UL
	__le32	flags;
	#घोषणा DBG_QCAPS_RESP_FLAGS_CRASHDUMP_NVM          0x1UL
	#घोषणा DBG_QCAPS_RESP_FLAGS_CRASHDUMP_HOST_DDR     0x2UL
	#घोषणा DBG_QCAPS_RESP_FLAGS_CRASHDUMP_SOC_DDR      0x4UL
	u8	unused_1[3];
	u8	valid;
पूर्ण;

/* hwrm_dbg_qcfg_input (size:192b/24B) */
काष्ठा hwrm_dbg_qcfg_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	fid;
	__le16	flags;
	#घोषणा DBG_QCFG_REQ_FLAGS_CRASHDUMP_SIZE_FOR_DEST_MASK         0x3UL
	#घोषणा DBG_QCFG_REQ_FLAGS_CRASHDUMP_SIZE_FOR_DEST_SFT          0
	#घोषणा DBG_QCFG_REQ_FLAGS_CRASHDUMP_SIZE_FOR_DEST_DEST_NVM       0x0UL
	#घोषणा DBG_QCFG_REQ_FLAGS_CRASHDUMP_SIZE_FOR_DEST_DEST_HOST_DDR  0x1UL
	#घोषणा DBG_QCFG_REQ_FLAGS_CRASHDUMP_SIZE_FOR_DEST_DEST_SOC_DDR   0x2UL
	#घोषणा DBG_QCFG_REQ_FLAGS_CRASHDUMP_SIZE_FOR_DEST_LAST          DBG_QCFG_REQ_FLAGS_CRASHDUMP_SIZE_FOR_DEST_DEST_SOC_DDR
	__le32	coredump_component_disable_flags;
	#घोषणा DBG_QCFG_REQ_COREDUMP_COMPONENT_DISABLE_FLAGS_NVRAM     0x1UL
पूर्ण;

/* hwrm_dbg_qcfg_output (size:256b/32B) */
काष्ठा hwrm_dbg_qcfg_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	fid;
	u8	unused_0[2];
	__le32	coredump_size;
	__le32	flags;
	#घोषणा DBG_QCFG_RESP_FLAGS_UART_LOG               0x1UL
	#घोषणा DBG_QCFG_RESP_FLAGS_UART_LOG_SECONDARY     0x2UL
	#घोषणा DBG_QCFG_RESP_FLAGS_FW_TRACE               0x4UL
	#घोषणा DBG_QCFG_RESP_FLAGS_FW_TRACE_SECONDARY     0x8UL
	#घोषणा DBG_QCFG_RESP_FLAGS_DEBUG_NOTIFY           0x10UL
	#घोषणा DBG_QCFG_RESP_FLAGS_JTAG_DEBUG             0x20UL
	__le16	async_cmpl_ring;
	u8	unused_2[2];
	__le32	crashdump_size;
	u8	unused_3[3];
	u8	valid;
पूर्ण;

/* coredump_segment_record (size:128b/16B) */
काष्ठा coredump_segment_record अणु
	__le16	component_id;
	__le16	segment_id;
	__le16	max_instances;
	u8	version_hi;
	u8	version_low;
	u8	seg_flags;
	u8	compress_flags;
	#घोषणा SFLAG_COMPRESSED_ZLIB     0x1UL
	u8	unused_0[2];
	__le32	segment_len;
पूर्ण;

/* hwrm_dbg_coredump_list_input (size:256b/32B) */
काष्ठा hwrm_dbg_coredump_list_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	host_dest_addr;
	__le32	host_buf_len;
	__le16	seq_no;
	u8	flags;
	#घोषणा DBG_COREDUMP_LIST_REQ_FLAGS_CRASHDUMP     0x1UL
	u8	unused_0[1];
पूर्ण;

/* hwrm_dbg_coredump_list_output (size:128b/16B) */
काष्ठा hwrm_dbg_coredump_list_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	flags;
	#घोषणा DBG_COREDUMP_LIST_RESP_FLAGS_MORE     0x1UL
	u8	unused_0;
	__le16	total_segments;
	__le16	data_len;
	u8	unused_1;
	u8	valid;
पूर्ण;

/* hwrm_dbg_coredump_initiate_input (size:256b/32B) */
काष्ठा hwrm_dbg_coredump_initiate_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	component_id;
	__le16	segment_id;
	__le16	instance;
	__le16	unused_0;
	u8	seg_flags;
	u8	unused_1[7];
पूर्ण;

/* hwrm_dbg_coredump_initiate_output (size:128b/16B) */
काष्ठा hwrm_dbg_coredump_initiate_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* coredump_data_hdr (size:128b/16B) */
काष्ठा coredump_data_hdr अणु
	__le32	address;
	__le32	flags_length;
	#घोषणा COREDUMP_DATA_HDR_FLAGS_LENGTH_ACTUAL_LEN_MASK     0xffffffUL
	#घोषणा COREDUMP_DATA_HDR_FLAGS_LENGTH_ACTUAL_LEN_SFT      0
	#घोषणा COREDUMP_DATA_HDR_FLAGS_LENGTH_INसूचीECT_ACCESS     0x1000000UL
	__le32	instance;
	__le32	next_offset;
पूर्ण;

/* hwrm_dbg_coredump_retrieve_input (size:448b/56B) */
काष्ठा hwrm_dbg_coredump_retrieve_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	host_dest_addr;
	__le32	host_buf_len;
	__le32	unused_0;
	__le16	component_id;
	__le16	segment_id;
	__le16	instance;
	__le16	unused_1;
	u8	seg_flags;
	u8	unused_2;
	__le16	unused_3;
	__le32	unused_4;
	__le32	seq_no;
	__le32	unused_5;
पूर्ण;

/* hwrm_dbg_coredump_retrieve_output (size:128b/16B) */
काष्ठा hwrm_dbg_coredump_retrieve_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	flags;
	#घोषणा DBG_COREDUMP_RETRIEVE_RESP_FLAGS_MORE     0x1UL
	u8	unused_0;
	__le16	data_len;
	u8	unused_1[3];
	u8	valid;
पूर्ण;

/* hwrm_dbg_ring_info_get_input (size:192b/24B) */
काष्ठा hwrm_dbg_ring_info_get_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	u8	ring_type;
	#घोषणा DBG_RING_INFO_GET_REQ_RING_TYPE_L2_CMPL 0x0UL
	#घोषणा DBG_RING_INFO_GET_REQ_RING_TYPE_TX      0x1UL
	#घोषणा DBG_RING_INFO_GET_REQ_RING_TYPE_RX      0x2UL
	#घोषणा DBG_RING_INFO_GET_REQ_RING_TYPE_NQ      0x3UL
	#घोषणा DBG_RING_INFO_GET_REQ_RING_TYPE_LAST   DBG_RING_INFO_GET_REQ_RING_TYPE_NQ
	u8	unused_0[3];
	__le32	fw_ring_id;
पूर्ण;

/* hwrm_dbg_ring_info_get_output (size:192b/24B) */
काष्ठा hwrm_dbg_ring_info_get_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	producer_index;
	__le32	consumer_index;
	__le32	cag_vector_ctrl;
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_nvm_पढ़ो_input (size:320b/40B) */
काष्ठा hwrm_nvm_पढ़ो_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	host_dest_addr;
	__le16	dir_idx;
	u8	unused_0[2];
	__le32	offset;
	__le32	len;
	u8	unused_1[4];
पूर्ण;

/* hwrm_nvm_पढ़ो_output (size:128b/16B) */
काष्ठा hwrm_nvm_पढ़ो_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_nvm_get_dir_entries_input (size:192b/24B) */
काष्ठा hwrm_nvm_get_dir_entries_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	host_dest_addr;
पूर्ण;

/* hwrm_nvm_get_dir_entries_output (size:128b/16B) */
काष्ठा hwrm_nvm_get_dir_entries_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_nvm_get_dir_info_input (size:128b/16B) */
काष्ठा hwrm_nvm_get_dir_info_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
पूर्ण;

/* hwrm_nvm_get_dir_info_output (size:192b/24B) */
काष्ठा hwrm_nvm_get_dir_info_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	entries;
	__le32	entry_length;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_nvm_ग_लिखो_input (size:384b/48B) */
काष्ठा hwrm_nvm_ग_लिखो_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	host_src_addr;
	__le16	dir_type;
	__le16	dir_ordinal;
	__le16	dir_ext;
	__le16	dir_attr;
	__le32	dir_data_length;
	__le16	option;
	__le16	flags;
	#घोषणा NVM_WRITE_REQ_FLAGS_KEEP_ORIG_ACTIVE_IMG     0x1UL
	__le32	dir_item_length;
	__le32	unused_0;
पूर्ण;

/* hwrm_nvm_ग_लिखो_output (size:128b/16B) */
काष्ठा hwrm_nvm_ग_लिखो_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	dir_item_length;
	__le16	dir_idx;
	u8	unused_0;
	u8	valid;
पूर्ण;

/* hwrm_nvm_ग_लिखो_cmd_err (size:64b/8B) */
काष्ठा hwrm_nvm_ग_लिखो_cmd_err अणु
	u8	code;
	#घोषणा NVM_WRITE_CMD_ERR_CODE_UNKNOWN  0x0UL
	#घोषणा NVM_WRITE_CMD_ERR_CODE_FRAG_ERR 0x1UL
	#घोषणा NVM_WRITE_CMD_ERR_CODE_NO_SPACE 0x2UL
	#घोषणा NVM_WRITE_CMD_ERR_CODE_LAST    NVM_WRITE_CMD_ERR_CODE_NO_SPACE
	u8	unused_0[7];
पूर्ण;

/* hwrm_nvm_modअगरy_input (size:320b/40B) */
काष्ठा hwrm_nvm_modअगरy_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	host_src_addr;
	__le16	dir_idx;
	__le16	flags;
	#घोषणा NVM_MODIFY_REQ_FLAGS_BATCH_MODE     0x1UL
	#घोषणा NVM_MODIFY_REQ_FLAGS_BATCH_LAST     0x2UL
	__le32	offset;
	__le32	len;
	u8	unused_1[4];
पूर्ण;

/* hwrm_nvm_modअगरy_output (size:128b/16B) */
काष्ठा hwrm_nvm_modअगरy_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_nvm_find_dir_entry_input (size:256b/32B) */
काष्ठा hwrm_nvm_find_dir_entry_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	enables;
	#घोषणा NVM_FIND_सूची_ENTRY_REQ_ENABLES_सूची_IDX_VALID     0x1UL
	__le16	dir_idx;
	__le16	dir_type;
	__le16	dir_ordinal;
	__le16	dir_ext;
	u8	opt_ordinal;
	#घोषणा NVM_FIND_सूची_ENTRY_REQ_OPT_ORDINAL_MASK 0x3UL
	#घोषणा NVM_FIND_सूची_ENTRY_REQ_OPT_ORDINAL_SFT 0
	#घोषणा NVM_FIND_सूची_ENTRY_REQ_OPT_ORDINAL_EQ    0x0UL
	#घोषणा NVM_FIND_सूची_ENTRY_REQ_OPT_ORDINAL_GE    0x1UL
	#घोषणा NVM_FIND_सूची_ENTRY_REQ_OPT_ORDINAL_GT    0x2UL
	#घोषणा NVM_FIND_सूची_ENTRY_REQ_OPT_ORDINAL_LAST NVM_FIND_सूची_ENTRY_REQ_OPT_ORDINAL_GT
	u8	unused_0[3];
पूर्ण;

/* hwrm_nvm_find_dir_entry_output (size:256b/32B) */
काष्ठा hwrm_nvm_find_dir_entry_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le32	dir_item_length;
	__le32	dir_data_length;
	__le32	fw_ver;
	__le16	dir_ordinal;
	__le16	dir_idx;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_nvm_erase_dir_entry_input (size:192b/24B) */
काष्ठा hwrm_nvm_erase_dir_entry_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	dir_idx;
	u8	unused_0[6];
पूर्ण;

/* hwrm_nvm_erase_dir_entry_output (size:128b/16B) */
काष्ठा hwrm_nvm_erase_dir_entry_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_nvm_get_dev_info_input (size:128b/16B) */
काष्ठा hwrm_nvm_get_dev_info_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
पूर्ण;

/* hwrm_nvm_get_dev_info_output (size:640b/80B) */
काष्ठा hwrm_nvm_get_dev_info_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	manufacturer_id;
	__le16	device_id;
	__le32	sector_size;
	__le32	nvram_size;
	__le32	reserved_size;
	__le32	available_size;
	u8	nvm_cfg_ver_maj;
	u8	nvm_cfg_ver_min;
	u8	nvm_cfg_ver_upd;
	u8	flags;
	#घोषणा NVM_GET_DEV_INFO_RESP_FLAGS_FW_VER_VALID     0x1UL
	अक्षर	pkg_name[16];
	__le16	hwrm_fw_major;
	__le16	hwrm_fw_minor;
	__le16	hwrm_fw_build;
	__le16	hwrm_fw_patch;
	__le16	mgmt_fw_major;
	__le16	mgmt_fw_minor;
	__le16	mgmt_fw_build;
	__le16	mgmt_fw_patch;
	__le16	roce_fw_major;
	__le16	roce_fw_minor;
	__le16	roce_fw_build;
	__le16	roce_fw_patch;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_nvm_mod_dir_entry_input (size:256b/32B) */
काष्ठा hwrm_nvm_mod_dir_entry_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	enables;
	#घोषणा NVM_MOD_सूची_ENTRY_REQ_ENABLES_CHECKSUM     0x1UL
	__le16	dir_idx;
	__le16	dir_ordinal;
	__le16	dir_ext;
	__le16	dir_attr;
	__le32	checksum;
पूर्ण;

/* hwrm_nvm_mod_dir_entry_output (size:128b/16B) */
काष्ठा hwrm_nvm_mod_dir_entry_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_nvm_verअगरy_update_input (size:192b/24B) */
काष्ठा hwrm_nvm_verअगरy_update_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le16	dir_type;
	__le16	dir_ordinal;
	__le16	dir_ext;
	u8	unused_0[2];
पूर्ण;

/* hwrm_nvm_verअगरy_update_output (size:128b/16B) */
काष्ठा hwrm_nvm_verअगरy_update_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_nvm_install_update_input (size:192b/24B) */
काष्ठा hwrm_nvm_install_update_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le32	install_type;
	#घोषणा NVM_INSTALL_UPDATE_REQ_INSTALL_TYPE_NORMAL 0x0UL
	#घोषणा NVM_INSTALL_UPDATE_REQ_INSTALL_TYPE_ALL    0xffffffffUL
	#घोषणा NVM_INSTALL_UPDATE_REQ_INSTALL_TYPE_LAST  NVM_INSTALL_UPDATE_REQ_INSTALL_TYPE_ALL
	__le16	flags;
	#घोषणा NVM_INSTALL_UPDATE_REQ_FLAGS_ERASE_UNUSED_SPACE     0x1UL
	#घोषणा NVM_INSTALL_UPDATE_REQ_FLAGS_REMOVE_UNUSED_PKG      0x2UL
	#घोषणा NVM_INSTALL_UPDATE_REQ_FLAGS_ALLOWED_TO_DEFRAG      0x4UL
	#घोषणा NVM_INSTALL_UPDATE_REQ_FLAGS_VERIFY_ONLY            0x8UL
	u8	unused_0[2];
पूर्ण;

/* hwrm_nvm_install_update_output (size:192b/24B) */
काष्ठा hwrm_nvm_install_update_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le64	installed_items;
	u8	result;
	#घोषणा NVM_INSTALL_UPDATE_RESP_RESULT_SUCCESS 0x0UL
	#घोषणा NVM_INSTALL_UPDATE_RESP_RESULT_LAST   NVM_INSTALL_UPDATE_RESP_RESULT_SUCCESS
	u8	problem_item;
	#घोषणा NVM_INSTALL_UPDATE_RESP_PROBLEM_ITEM_NONE    0x0UL
	#घोषणा NVM_INSTALL_UPDATE_RESP_PROBLEM_ITEM_PACKAGE 0xffUL
	#घोषणा NVM_INSTALL_UPDATE_RESP_PROBLEM_ITEM_LAST   NVM_INSTALL_UPDATE_RESP_PROBLEM_ITEM_PACKAGE
	u8	reset_required;
	#घोषणा NVM_INSTALL_UPDATE_RESP_RESET_REQUIRED_NONE  0x0UL
	#घोषणा NVM_INSTALL_UPDATE_RESP_RESET_REQUIRED_PCI   0x1UL
	#घोषणा NVM_INSTALL_UPDATE_RESP_RESET_REQUIRED_POWER 0x2UL
	#घोषणा NVM_INSTALL_UPDATE_RESP_RESET_REQUIRED_LAST NVM_INSTALL_UPDATE_RESP_RESET_REQUIRED_POWER
	u8	unused_0[4];
	u8	valid;
पूर्ण;

/* hwrm_nvm_install_update_cmd_err (size:64b/8B) */
काष्ठा hwrm_nvm_install_update_cmd_err अणु
	u8	code;
	#घोषणा NVM_INSTALL_UPDATE_CMD_ERR_CODE_UNKNOWN  0x0UL
	#घोषणा NVM_INSTALL_UPDATE_CMD_ERR_CODE_FRAG_ERR 0x1UL
	#घोषणा NVM_INSTALL_UPDATE_CMD_ERR_CODE_NO_SPACE 0x2UL
	#घोषणा NVM_INSTALL_UPDATE_CMD_ERR_CODE_LAST    NVM_INSTALL_UPDATE_CMD_ERR_CODE_NO_SPACE
	u8	unused_0[7];
पूर्ण;

/* hwrm_nvm_get_variable_input (size:320b/40B) */
काष्ठा hwrm_nvm_get_variable_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	dest_data_addr;
	__le16	data_len;
	__le16	option_num;
	#घोषणा NVM_GET_VARIABLE_REQ_OPTION_NUM_RSVD_0    0x0UL
	#घोषणा NVM_GET_VARIABLE_REQ_OPTION_NUM_RSVD_FFFF 0xffffUL
	#घोषणा NVM_GET_VARIABLE_REQ_OPTION_NUM_LAST     NVM_GET_VARIABLE_REQ_OPTION_NUM_RSVD_FFFF
	__le16	dimensions;
	__le16	index_0;
	__le16	index_1;
	__le16	index_2;
	__le16	index_3;
	u8	flags;
	#घोषणा NVM_GET_VARIABLE_REQ_FLAGS_FACTORY_DFLT     0x1UL
	u8	unused_0;
पूर्ण;

/* hwrm_nvm_get_variable_output (size:128b/16B) */
काष्ठा hwrm_nvm_get_variable_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	__le16	data_len;
	__le16	option_num;
	#घोषणा NVM_GET_VARIABLE_RESP_OPTION_NUM_RSVD_0    0x0UL
	#घोषणा NVM_GET_VARIABLE_RESP_OPTION_NUM_RSVD_FFFF 0xffffUL
	#घोषणा NVM_GET_VARIABLE_RESP_OPTION_NUM_LAST     NVM_GET_VARIABLE_RESP_OPTION_NUM_RSVD_FFFF
	u8	unused_0[3];
	u8	valid;
पूर्ण;

/* hwrm_nvm_get_variable_cmd_err (size:64b/8B) */
काष्ठा hwrm_nvm_get_variable_cmd_err अणु
	u8	code;
	#घोषणा NVM_GET_VARIABLE_CMD_ERR_CODE_UNKNOWN       0x0UL
	#घोषणा NVM_GET_VARIABLE_CMD_ERR_CODE_VAR_NOT_EXIST 0x1UL
	#घोषणा NVM_GET_VARIABLE_CMD_ERR_CODE_CORRUPT_VAR   0x2UL
	#घोषणा NVM_GET_VARIABLE_CMD_ERR_CODE_LEN_TOO_SHORT 0x3UL
	#घोषणा NVM_GET_VARIABLE_CMD_ERR_CODE_LAST         NVM_GET_VARIABLE_CMD_ERR_CODE_LEN_TOO_SHORT
	u8	unused_0[7];
पूर्ण;

/* hwrm_nvm_set_variable_input (size:320b/40B) */
काष्ठा hwrm_nvm_set_variable_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	__le64	src_data_addr;
	__le16	data_len;
	__le16	option_num;
	#घोषणा NVM_SET_VARIABLE_REQ_OPTION_NUM_RSVD_0    0x0UL
	#घोषणा NVM_SET_VARIABLE_REQ_OPTION_NUM_RSVD_FFFF 0xffffUL
	#घोषणा NVM_SET_VARIABLE_REQ_OPTION_NUM_LAST     NVM_SET_VARIABLE_REQ_OPTION_NUM_RSVD_FFFF
	__le16	dimensions;
	__le16	index_0;
	__le16	index_1;
	__le16	index_2;
	__le16	index_3;
	u8	flags;
	#घोषणा NVM_SET_VARIABLE_REQ_FLAGS_FORCE_FLUSH                0x1UL
	#घोषणा NVM_SET_VARIABLE_REQ_FLAGS_ENCRYPT_MODE_MASK          0xeUL
	#घोषणा NVM_SET_VARIABLE_REQ_FLAGS_ENCRYPT_MODE_SFT           1
	#घोषणा NVM_SET_VARIABLE_REQ_FLAGS_ENCRYPT_MODE_NONE            (0x0UL << 1)
	#घोषणा NVM_SET_VARIABLE_REQ_FLAGS_ENCRYPT_MODE_HMAC_SHA1       (0x1UL << 1)
	#घोषणा NVM_SET_VARIABLE_REQ_FLAGS_ENCRYPT_MODE_AES256          (0x2UL << 1)
	#घोषणा NVM_SET_VARIABLE_REQ_FLAGS_ENCRYPT_MODE_HMAC_SHA1_AUTH  (0x3UL << 1)
	#घोषणा NVM_SET_VARIABLE_REQ_FLAGS_ENCRYPT_MODE_LAST           NVM_SET_VARIABLE_REQ_FLAGS_ENCRYPT_MODE_HMAC_SHA1_AUTH
	#घोषणा NVM_SET_VARIABLE_REQ_FLAGS_FLAGS_UNUSED_0_MASK        0x70UL
	#घोषणा NVM_SET_VARIABLE_REQ_FLAGS_FLAGS_UNUSED_0_SFT         4
	#घोषणा NVM_SET_VARIABLE_REQ_FLAGS_FACTORY_DEFAULT            0x80UL
	u8	unused_0;
पूर्ण;

/* hwrm_nvm_set_variable_output (size:128b/16B) */
काष्ठा hwrm_nvm_set_variable_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* hwrm_nvm_set_variable_cmd_err (size:64b/8B) */
काष्ठा hwrm_nvm_set_variable_cmd_err अणु
	u8	code;
	#घोषणा NVM_SET_VARIABLE_CMD_ERR_CODE_UNKNOWN       0x0UL
	#घोषणा NVM_SET_VARIABLE_CMD_ERR_CODE_VAR_NOT_EXIST 0x1UL
	#घोषणा NVM_SET_VARIABLE_CMD_ERR_CODE_CORRUPT_VAR   0x2UL
	#घोषणा NVM_SET_VARIABLE_CMD_ERR_CODE_LAST         NVM_SET_VARIABLE_CMD_ERR_CODE_CORRUPT_VAR
	u8	unused_0[7];
पूर्ण;

/* hwrm_selftest_qlist_input (size:128b/16B) */
काष्ठा hwrm_selftest_qlist_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
पूर्ण;

/* hwrm_selftest_qlist_output (size:2240b/280B) */
काष्ठा hwrm_selftest_qlist_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	num_tests;
	u8	available_tests;
	#घोषणा SELFTEST_QLIST_RESP_AVAILABLE_TESTS_NVM_TEST                 0x1UL
	#घोषणा SELFTEST_QLIST_RESP_AVAILABLE_TESTS_LINK_TEST                0x2UL
	#घोषणा SELFTEST_QLIST_RESP_AVAILABLE_TESTS_REGISTER_TEST            0x4UL
	#घोषणा SELFTEST_QLIST_RESP_AVAILABLE_TESTS_MEMORY_TEST              0x8UL
	#घोषणा SELFTEST_QLIST_RESP_AVAILABLE_TESTS_PCIE_SERDES_TEST         0x10UL
	#घोषणा SELFTEST_QLIST_RESP_AVAILABLE_TESTS_ETHERNET_SERDES_TEST     0x20UL
	u8	offline_tests;
	#घोषणा SELFTEST_QLIST_RESP_OFFLINE_TESTS_NVM_TEST                 0x1UL
	#घोषणा SELFTEST_QLIST_RESP_OFFLINE_TESTS_LINK_TEST                0x2UL
	#घोषणा SELFTEST_QLIST_RESP_OFFLINE_TESTS_REGISTER_TEST            0x4UL
	#घोषणा SELFTEST_QLIST_RESP_OFFLINE_TESTS_MEMORY_TEST              0x8UL
	#घोषणा SELFTEST_QLIST_RESP_OFFLINE_TESTS_PCIE_SERDES_TEST         0x10UL
	#घोषणा SELFTEST_QLIST_RESP_OFFLINE_TESTS_ETHERNET_SERDES_TEST     0x20UL
	u8	unused_0;
	__le16	test_समयout;
	u8	unused_1[2];
	अक्षर	test0_name[32];
	अक्षर	test1_name[32];
	अक्षर	test2_name[32];
	अक्षर	test3_name[32];
	अक्षर	test4_name[32];
	अक्षर	test5_name[32];
	अक्षर	test6_name[32];
	अक्षर	test7_name[32];
	u8	eyescope_target_BER_support;
	#घोषणा SELFTEST_QLIST_RESP_EYESCOPE_TARGET_BER_SUPPORT_BER_1E8_SUPPORTED  0x0UL
	#घोषणा SELFTEST_QLIST_RESP_EYESCOPE_TARGET_BER_SUPPORT_BER_1E9_SUPPORTED  0x1UL
	#घोषणा SELFTEST_QLIST_RESP_EYESCOPE_TARGET_BER_SUPPORT_BER_1E10_SUPPORTED 0x2UL
	#घोषणा SELFTEST_QLIST_RESP_EYESCOPE_TARGET_BER_SUPPORT_BER_1E11_SUPPORTED 0x3UL
	#घोषणा SELFTEST_QLIST_RESP_EYESCOPE_TARGET_BER_SUPPORT_BER_1E12_SUPPORTED 0x4UL
	#घोषणा SELFTEST_QLIST_RESP_EYESCOPE_TARGET_BER_SUPPORT_LAST              SELFTEST_QLIST_RESP_EYESCOPE_TARGET_BER_SUPPORT_BER_1E12_SUPPORTED
	u8	unused_2[6];
	u8	valid;
पूर्ण;

/* hwrm_selftest_exec_input (size:192b/24B) */
काष्ठा hwrm_selftest_exec_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
	u8	flags;
	#घोषणा SELFTEST_EXEC_REQ_FLAGS_NVM_TEST                 0x1UL
	#घोषणा SELFTEST_EXEC_REQ_FLAGS_LINK_TEST                0x2UL
	#घोषणा SELFTEST_EXEC_REQ_FLAGS_REGISTER_TEST            0x4UL
	#घोषणा SELFTEST_EXEC_REQ_FLAGS_MEMORY_TEST              0x8UL
	#घोषणा SELFTEST_EXEC_REQ_FLAGS_PCIE_SERDES_TEST         0x10UL
	#घोषणा SELFTEST_EXEC_REQ_FLAGS_ETHERNET_SERDES_TEST     0x20UL
	u8	unused_0[7];
पूर्ण;

/* hwrm_selftest_exec_output (size:128b/16B) */
काष्ठा hwrm_selftest_exec_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	requested_tests;
	#घोषणा SELFTEST_EXEC_RESP_REQUESTED_TESTS_NVM_TEST                 0x1UL
	#घोषणा SELFTEST_EXEC_RESP_REQUESTED_TESTS_LINK_TEST                0x2UL
	#घोषणा SELFTEST_EXEC_RESP_REQUESTED_TESTS_REGISTER_TEST            0x4UL
	#घोषणा SELFTEST_EXEC_RESP_REQUESTED_TESTS_MEMORY_TEST              0x8UL
	#घोषणा SELFTEST_EXEC_RESP_REQUESTED_TESTS_PCIE_SERDES_TEST         0x10UL
	#घोषणा SELFTEST_EXEC_RESP_REQUESTED_TESTS_ETHERNET_SERDES_TEST     0x20UL
	u8	test_success;
	#घोषणा SELFTEST_EXEC_RESP_TEST_SUCCESS_NVM_TEST                 0x1UL
	#घोषणा SELFTEST_EXEC_RESP_TEST_SUCCESS_LINK_TEST                0x2UL
	#घोषणा SELFTEST_EXEC_RESP_TEST_SUCCESS_REGISTER_TEST            0x4UL
	#घोषणा SELFTEST_EXEC_RESP_TEST_SUCCESS_MEMORY_TEST              0x8UL
	#घोषणा SELFTEST_EXEC_RESP_TEST_SUCCESS_PCIE_SERDES_TEST         0x10UL
	#घोषणा SELFTEST_EXEC_RESP_TEST_SUCCESS_ETHERNET_SERDES_TEST     0x20UL
	u8	unused_0[5];
	u8	valid;
पूर्ण;

/* hwrm_selftest_irq_input (size:128b/16B) */
काष्ठा hwrm_selftest_irq_input अणु
	__le16	req_type;
	__le16	cmpl_ring;
	__le16	seq_id;
	__le16	target_id;
	__le64	resp_addr;
पूर्ण;

/* hwrm_selftest_irq_output (size:128b/16B) */
काष्ठा hwrm_selftest_irq_output अणु
	__le16	error_code;
	__le16	req_type;
	__le16	seq_id;
	__le16	resp_len;
	u8	unused_0[7];
	u8	valid;
पूर्ण;

/* db_push_info (size:64b/8B) */
काष्ठा db_push_info अणु
	u32	push_size_push_index;
	#घोषणा DB_PUSH_INFO_PUSH_INDEX_MASK 0xffffffUL
	#घोषणा DB_PUSH_INFO_PUSH_INDEX_SFT 0
	#घोषणा DB_PUSH_INFO_PUSH_SIZE_MASK 0x1f000000UL
	#घोषणा DB_PUSH_INFO_PUSH_SIZE_SFT  24
	u32	reserved32;
पूर्ण;

/* fw_status_reg (size:32b/4B) */
काष्ठा fw_status_reg अणु
	u32	fw_status;
	#घोषणा FW_STATUS_REG_CODE_MASK              0xffffUL
	#घोषणा FW_STATUS_REG_CODE_SFT               0
	#घोषणा FW_STATUS_REG_CODE_READY               0x8000UL
	#घोषणा FW_STATUS_REG_CODE_LAST               FW_STATUS_REG_CODE_READY
	#घोषणा FW_STATUS_REG_IMAGE_DEGRADED         0x10000UL
	#घोषणा FW_STATUS_REG_RECOVERABLE            0x20000UL
	#घोषणा FW_STATUS_REG_CRASHDUMP_ONGOING      0x40000UL
	#घोषणा FW_STATUS_REG_CRASHDUMP_COMPLETE     0x80000UL
	#घोषणा FW_STATUS_REG_SHUTDOWN               0x100000UL
	#घोषणा FW_STATUS_REG_CRASHED_NO_MASTER      0x200000UL
पूर्ण;

/* hcomm_status (size:64b/8B) */
काष्ठा hcomm_status अणु
	u32	sig_ver;
	#घोषणा HCOMM_STATUS_VER_MASK      0xffUL
	#घोषणा HCOMM_STATUS_VER_SFT       0
	#घोषणा HCOMM_STATUS_VER_LATEST      0x1UL
	#घोषणा HCOMM_STATUS_VER_LAST       HCOMM_STATUS_VER_LATEST
	#घोषणा HCOMM_STATUS_SIGNATURE_MASK 0xffffff00UL
	#घोषणा HCOMM_STATUS_SIGNATURE_SFT 8
	#घोषणा HCOMM_STATUS_SIGNATURE_VAL   (0x484353UL << 8)
	#घोषणा HCOMM_STATUS_SIGNATURE_LAST HCOMM_STATUS_SIGNATURE_VAL
	u32	fw_status_loc;
	#घोषणा HCOMM_STATUS_TRUE_ADDR_SPACE_MASK    0x3UL
	#घोषणा HCOMM_STATUS_TRUE_ADDR_SPACE_SFT     0
	#घोषणा HCOMM_STATUS_FW_STATUS_LOC_ADDR_SPACE_PCIE_CFG  0x0UL
	#घोषणा HCOMM_STATUS_FW_STATUS_LOC_ADDR_SPACE_GRC       0x1UL
	#घोषणा HCOMM_STATUS_FW_STATUS_LOC_ADDR_SPACE_BAR0      0x2UL
	#घोषणा HCOMM_STATUS_FW_STATUS_LOC_ADDR_SPACE_BAR1      0x3UL
	#घोषणा HCOMM_STATUS_FW_STATUS_LOC_ADDR_SPACE_LAST     HCOMM_STATUS_FW_STATUS_LOC_ADDR_SPACE_BAR1
	#घोषणा HCOMM_STATUS_TRUE_OFFSET_MASK        0xfffffffcUL
	#घोषणा HCOMM_STATUS_TRUE_OFFSET_SFT         2
पूर्ण;
#घोषणा HCOMM_STATUS_STRUCT_LOC 0x31001F0UL

#पूर्ण_अगर /* _BNXT_HSI_H_ */
