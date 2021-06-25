<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* Copyright (c) 2019-2020 Marvell International Ltd. */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/bug.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "qed.h"
#समावेश "qed_hw.h"
#समावेश "qed_mcp.h"
#समावेश "qed_reg_addr.h"

#घोषणा TLV_TYPE(p)     (p[0])
#घोषणा TLV_LENGTH(p)   (p[1])
#घोषणा TLV_FLAGS(p)    (p[3])

#घोषणा QED_TLV_DATA_MAX (14)
काष्ठा qed_tlv_parsed_buf अणु
	/* To be filled with the address to set in Value field */
	व्योम *p_val;

	/* To be used पूर्णांकernally in हाल the value has to be modअगरied */
	u8 data[QED_TLV_DATA_MAX];
पूर्ण;

अटल पूर्णांक qed_mfw_get_tlv_group(u8 tlv_type, u8 *tlv_group)
अणु
	चयन (tlv_type) अणु
	हाल DRV_TLV_FEATURE_FLAGS:
	हाल DRV_TLV_LOCAL_ADMIN_ADDR:
	हाल DRV_TLV_ADDITIONAL_MAC_ADDR_1:
	हाल DRV_TLV_ADDITIONAL_MAC_ADDR_2:
	हाल DRV_TLV_OS_DRIVER_STATES:
	हाल DRV_TLV_PXE_BOOT_PROGRESS:
	हाल DRV_TLV_RX_FRAMES_RECEIVED:
	हाल DRV_TLV_RX_BYTES_RECEIVED:
	हाल DRV_TLV_TX_FRAMES_SENT:
	हाल DRV_TLV_TX_BYTES_SENT:
	हाल DRV_TLV_NPIV_ENABLED:
	हाल DRV_TLV_PCIE_BUS_RX_UTILIZATION:
	हाल DRV_TLV_PCIE_BUS_TX_UTILIZATION:
	हाल DRV_TLV_DEVICE_CPU_CORES_UTILIZATION:
	हाल DRV_TLV_LAST_VALID_DCC_TLV_RECEIVED:
	हाल DRV_TLV_NCSI_RX_BYTES_RECEIVED:
	हाल DRV_TLV_NCSI_TX_BYTES_SENT:
		*tlv_group |= QED_MFW_TLV_GENERIC;
		अवरोध;
	हाल DRV_TLV_LSO_MAX_OFFLOAD_SIZE:
	हाल DRV_TLV_LSO_MIN_SEGMENT_COUNT:
	हाल DRV_TLV_PROMISCUOUS_MODE:
	हाल DRV_TLV_TX_DESCRIPTORS_QUEUE_SIZE:
	हाल DRV_TLV_RX_DESCRIPTORS_QUEUE_SIZE:
	हाल DRV_TLV_NUM_OF_NET_QUEUE_VMQ_CFG:
	हाल DRV_TLV_NUM_OFFLOADED_CONNECTIONS_TCP_IPV4:
	हाल DRV_TLV_NUM_OFFLOADED_CONNECTIONS_TCP_IPV6:
	हाल DRV_TLV_TX_DESCRIPTOR_QUEUE_AVG_DEPTH:
	हाल DRV_TLV_RX_DESCRIPTORS_QUEUE_AVG_DEPTH:
	हाल DRV_TLV_IOV_OFFLOAD:
	हाल DRV_TLV_TX_QUEUES_EMPTY:
	हाल DRV_TLV_RX_QUEUES_EMPTY:
	हाल DRV_TLV_TX_QUEUES_FULL:
	हाल DRV_TLV_RX_QUEUES_FULL:
		*tlv_group |= QED_MFW_TLV_ETH;
		अवरोध;
	हाल DRV_TLV_SCSI_TO:
	हाल DRV_TLV_R_T_TOV:
	हाल DRV_TLV_R_A_TOV:
	हाल DRV_TLV_E_D_TOV:
	हाल DRV_TLV_CR_TOV:
	हाल DRV_TLV_BOOT_TYPE:
	हाल DRV_TLV_NPIV_STATE:
	हाल DRV_TLV_NUM_OF_NPIV_IDS:
	हाल DRV_TLV_SWITCH_NAME:
	हाल DRV_TLV_SWITCH_PORT_NUM:
	हाल DRV_TLV_SWITCH_PORT_ID:
	हाल DRV_TLV_VENDOR_NAME:
	हाल DRV_TLV_SWITCH_MODEL:
	हाल DRV_TLV_SWITCH_FW_VER:
	हाल DRV_TLV_QOS_PRIORITY_PER_802_1P:
	हाल DRV_TLV_PORT_ALIAS:
	हाल DRV_TLV_PORT_STATE:
	हाल DRV_TLV_FIP_TX_DESCRIPTORS_QUEUE_SIZE:
	हाल DRV_TLV_FCOE_RX_DESCRIPTORS_QUEUE_SIZE:
	हाल DRV_TLV_LINK_FAILURE_COUNT:
	हाल DRV_TLV_FCOE_BOOT_PROGRESS:
	हाल DRV_TLV_RX_BROADCAST_PACKETS:
	हाल DRV_TLV_TX_BROADCAST_PACKETS:
	हाल DRV_TLV_FCOE_TX_DESCRIPTOR_QUEUE_AVG_DEPTH:
	हाल DRV_TLV_FCOE_RX_DESCRIPTORS_QUEUE_AVG_DEPTH:
	हाल DRV_TLV_FCOE_RX_FRAMES_RECEIVED:
	हाल DRV_TLV_FCOE_RX_BYTES_RECEIVED:
	हाल DRV_TLV_FCOE_TX_FRAMES_SENT:
	हाल DRV_TLV_FCOE_TX_BYTES_SENT:
	हाल DRV_TLV_CRC_ERROR_COUNT:
	हाल DRV_TLV_CRC_ERROR_1_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_CRC_ERROR_1_TIMESTAMP:
	हाल DRV_TLV_CRC_ERROR_2_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_CRC_ERROR_2_TIMESTAMP:
	हाल DRV_TLV_CRC_ERROR_3_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_CRC_ERROR_3_TIMESTAMP:
	हाल DRV_TLV_CRC_ERROR_4_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_CRC_ERROR_4_TIMESTAMP:
	हाल DRV_TLV_CRC_ERROR_5_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_CRC_ERROR_5_TIMESTAMP:
	हाल DRV_TLV_LOSS_OF_SYNC_ERROR_COUNT:
	हाल DRV_TLV_LOSS_OF_SIGNAL_ERRORS:
	हाल DRV_TLV_PRIMITIVE_SEQUENCE_PROTOCOL_ERROR_COUNT:
	हाल DRV_TLV_DISPARITY_ERROR_COUNT:
	हाल DRV_TLV_CODE_VIOLATION_ERROR_COUNT:
	हाल DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_1:
	हाल DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_2:
	हाल DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_3:
	हाल DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_4:
	हाल DRV_TLV_LAST_FLOGI_TIMESTAMP:
	हाल DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_1:
	हाल DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_2:
	हाल DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_3:
	हाल DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_4:
	हाल DRV_TLV_LAST_FLOGI_ACC_TIMESTAMP:
	हाल DRV_TLV_LAST_FLOGI_RJT:
	हाल DRV_TLV_LAST_FLOGI_RJT_TIMESTAMP:
	हाल DRV_TLV_FDISCS_SENT_COUNT:
	हाल DRV_TLV_FDISC_ACCS_RECEIVED:
	हाल DRV_TLV_FDISC_RJTS_RECEIVED:
	हाल DRV_TLV_PLOGI_SENT_COUNT:
	हाल DRV_TLV_PLOGI_ACCS_RECEIVED:
	हाल DRV_TLV_PLOGI_RJTS_RECEIVED:
	हाल DRV_TLV_PLOGI_1_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_PLOGI_1_TIMESTAMP:
	हाल DRV_TLV_PLOGI_2_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_PLOGI_2_TIMESTAMP:
	हाल DRV_TLV_PLOGI_3_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_PLOGI_3_TIMESTAMP:
	हाल DRV_TLV_PLOGI_4_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_PLOGI_4_TIMESTAMP:
	हाल DRV_TLV_PLOGI_5_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_PLOGI_5_TIMESTAMP:
	हाल DRV_TLV_PLOGI_1_ACC_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_PLOGI_1_ACC_TIMESTAMP:
	हाल DRV_TLV_PLOGI_2_ACC_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_PLOGI_2_ACC_TIMESTAMP:
	हाल DRV_TLV_PLOGI_3_ACC_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_PLOGI_3_ACC_TIMESTAMP:
	हाल DRV_TLV_PLOGI_4_ACC_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_PLOGI_4_ACC_TIMESTAMP:
	हाल DRV_TLV_PLOGI_5_ACC_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_PLOGI_5_ACC_TIMESTAMP:
	हाल DRV_TLV_LOGOS_ISSUED:
	हाल DRV_TLV_LOGO_ACCS_RECEIVED:
	हाल DRV_TLV_LOGO_RJTS_RECEIVED:
	हाल DRV_TLV_LOGO_1_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_LOGO_1_TIMESTAMP:
	हाल DRV_TLV_LOGO_2_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_LOGO_2_TIMESTAMP:
	हाल DRV_TLV_LOGO_3_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_LOGO_3_TIMESTAMP:
	हाल DRV_TLV_LOGO_4_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_LOGO_4_TIMESTAMP:
	हाल DRV_TLV_LOGO_5_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_LOGO_5_TIMESTAMP:
	हाल DRV_TLV_LOGOS_RECEIVED:
	हाल DRV_TLV_ACCS_ISSUED:
	हाल DRV_TLV_PRLIS_ISSUED:
	हाल DRV_TLV_ACCS_RECEIVED:
	हाल DRV_TLV_ABTS_SENT_COUNT:
	हाल DRV_TLV_ABTS_ACCS_RECEIVED:
	हाल DRV_TLV_ABTS_RJTS_RECEIVED:
	हाल DRV_TLV_ABTS_1_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_ABTS_1_TIMESTAMP:
	हाल DRV_TLV_ABTS_2_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_ABTS_2_TIMESTAMP:
	हाल DRV_TLV_ABTS_3_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_ABTS_3_TIMESTAMP:
	हाल DRV_TLV_ABTS_4_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_ABTS_4_TIMESTAMP:
	हाल DRV_TLV_ABTS_5_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_ABTS_5_TIMESTAMP:
	हाल DRV_TLV_RSCNS_RECEIVED:
	हाल DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_1:
	हाल DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_2:
	हाल DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_3:
	हाल DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_4:
	हाल DRV_TLV_LUN_RESETS_ISSUED:
	हाल DRV_TLV_ABORT_TASK_SETS_ISSUED:
	हाल DRV_TLV_TPRLOS_SENT:
	हाल DRV_TLV_NOS_SENT_COUNT:
	हाल DRV_TLV_NOS_RECEIVED_COUNT:
	हाल DRV_TLV_OLS_COUNT:
	हाल DRV_TLV_LR_COUNT:
	हाल DRV_TLV_LRR_COUNT:
	हाल DRV_TLV_LIP_SENT_COUNT:
	हाल DRV_TLV_LIP_RECEIVED_COUNT:
	हाल DRV_TLV_खातापूर्णA_COUNT:
	हाल DRV_TLV_खातापूर्णNI_COUNT:
	हाल DRV_TLV_SCSI_STATUS_CHECK_CONDITION_COUNT:
	हाल DRV_TLV_SCSI_STATUS_CONDITION_MET_COUNT:
	हाल DRV_TLV_SCSI_STATUS_BUSY_COUNT:
	हाल DRV_TLV_SCSI_STATUS_INTERMEDIATE_COUNT:
	हाल DRV_TLV_SCSI_STATUS_INTERMEDIATE_CONDITION_MET_COUNT:
	हाल DRV_TLV_SCSI_STATUS_RESERVATION_CONFLICT_COUNT:
	हाल DRV_TLV_SCSI_STATUS_TASK_SET_FULL_COUNT:
	हाल DRV_TLV_SCSI_STATUS_ACA_ACTIVE_COUNT:
	हाल DRV_TLV_SCSI_STATUS_TASK_ABORTED_COUNT:
	हाल DRV_TLV_SCSI_CHECK_CONDITION_1_RECEIVED_SK_ASC_ASCQ:
	हाल DRV_TLV_SCSI_CHECK_1_TIMESTAMP:
	हाल DRV_TLV_SCSI_CHECK_CONDITION_2_RECEIVED_SK_ASC_ASCQ:
	हाल DRV_TLV_SCSI_CHECK_2_TIMESTAMP:
	हाल DRV_TLV_SCSI_CHECK_CONDITION_3_RECEIVED_SK_ASC_ASCQ:
	हाल DRV_TLV_SCSI_CHECK_3_TIMESTAMP:
	हाल DRV_TLV_SCSI_CHECK_CONDITION_4_RECEIVED_SK_ASC_ASCQ:
	हाल DRV_TLV_SCSI_CHECK_4_TIMESTAMP:
	हाल DRV_TLV_SCSI_CHECK_CONDITION_5_RECEIVED_SK_ASC_ASCQ:
	हाल DRV_TLV_SCSI_CHECK_5_TIMESTAMP:
		*tlv_group = QED_MFW_TLV_FCOE;
		अवरोध;
	हाल DRV_TLV_TARGET_LLMNR_ENABLED:
	हाल DRV_TLV_HEADER_DIGEST_FLAG_ENABLED:
	हाल DRV_TLV_DATA_DIGEST_FLAG_ENABLED:
	हाल DRV_TLV_AUTHENTICATION_METHOD:
	हाल DRV_TLV_ISCSI_BOOT_TARGET_PORTAL:
	हाल DRV_TLV_MAX_FRAME_SIZE:
	हाल DRV_TLV_PDU_TX_DESCRIPTORS_QUEUE_SIZE:
	हाल DRV_TLV_PDU_RX_DESCRIPTORS_QUEUE_SIZE:
	हाल DRV_TLV_ISCSI_BOOT_PROGRESS:
	हाल DRV_TLV_PDU_TX_DESCRIPTOR_QUEUE_AVG_DEPTH:
	हाल DRV_TLV_PDU_RX_DESCRIPTORS_QUEUE_AVG_DEPTH:
	हाल DRV_TLV_ISCSI_PDU_RX_FRAMES_RECEIVED:
	हाल DRV_TLV_ISCSI_PDU_RX_BYTES_RECEIVED:
	हाल DRV_TLV_ISCSI_PDU_TX_FRAMES_SENT:
	हाल DRV_TLV_ISCSI_PDU_TX_BYTES_SENT:
		*tlv_group |= QED_MFW_TLV_ISCSI;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Returns size of the data buffer or, -1 in हाल TLV data is not available. */
अटल पूर्णांक
qed_mfw_get_gen_tlv_value(काष्ठा qed_drv_tlv_hdr *p_tlv,
			  काष्ठा qed_mfw_tlv_generic *p_drv_buf,
			  काष्ठा qed_tlv_parsed_buf *p_buf)
अणु
	चयन (p_tlv->tlv_type) अणु
	हाल DRV_TLV_FEATURE_FLAGS:
		अगर (p_drv_buf->flags.b_set) अणु
			स_रखो(p_buf->data, 0, माप(u8) * QED_TLV_DATA_MAX);
			p_buf->data[0] = p_drv_buf->flags.ipv4_csum_offload ?
			    1 : 0;
			p_buf->data[0] |= (p_drv_buf->flags.lso_supported ?
					   1 : 0) << 1;
			p_buf->p_val = p_buf->data;
			वापस QED_MFW_TLV_FLAGS_SIZE;
		पूर्ण
		अवरोध;

	हाल DRV_TLV_LOCAL_ADMIN_ADDR:
	हाल DRV_TLV_ADDITIONAL_MAC_ADDR_1:
	हाल DRV_TLV_ADDITIONAL_MAC_ADDR_2:
		अणु
			पूर्णांक idx = p_tlv->tlv_type - DRV_TLV_LOCAL_ADMIN_ADDR;

			अगर (p_drv_buf->mac_set[idx]) अणु
				p_buf->p_val = p_drv_buf->mac[idx];
				वापस ETH_ALEN;
			पूर्ण
			अवरोध;
		पूर्ण

	हाल DRV_TLV_RX_FRAMES_RECEIVED:
		अगर (p_drv_buf->rx_frames_set) अणु
			p_buf->p_val = &p_drv_buf->rx_frames;
			वापस माप(p_drv_buf->rx_frames);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_RX_BYTES_RECEIVED:
		अगर (p_drv_buf->rx_bytes_set) अणु
			p_buf->p_val = &p_drv_buf->rx_bytes;
			वापस माप(p_drv_buf->rx_bytes);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_TX_FRAMES_SENT:
		अगर (p_drv_buf->tx_frames_set) अणु
			p_buf->p_val = &p_drv_buf->tx_frames;
			वापस माप(p_drv_buf->tx_frames);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_TX_BYTES_SENT:
		अगर (p_drv_buf->tx_bytes_set) अणु
			p_buf->p_val = &p_drv_buf->tx_bytes;
			वापस माप(p_drv_buf->tx_bytes);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक
qed_mfw_get_eth_tlv_value(काष्ठा qed_drv_tlv_hdr *p_tlv,
			  काष्ठा qed_mfw_tlv_eth *p_drv_buf,
			  काष्ठा qed_tlv_parsed_buf *p_buf)
अणु
	चयन (p_tlv->tlv_type) अणु
	हाल DRV_TLV_LSO_MAX_OFFLOAD_SIZE:
		अगर (p_drv_buf->lso_maxoff_size_set) अणु
			p_buf->p_val = &p_drv_buf->lso_maxoff_size;
			वापस माप(p_drv_buf->lso_maxoff_size);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LSO_MIN_SEGMENT_COUNT:
		अगर (p_drv_buf->lso_minseg_size_set) अणु
			p_buf->p_val = &p_drv_buf->lso_minseg_size;
			वापस माप(p_drv_buf->lso_minseg_size);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PROMISCUOUS_MODE:
		अगर (p_drv_buf->prom_mode_set) अणु
			p_buf->p_val = &p_drv_buf->prom_mode;
			वापस माप(p_drv_buf->prom_mode);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_TX_DESCRIPTORS_QUEUE_SIZE:
		अगर (p_drv_buf->tx_descr_size_set) अणु
			p_buf->p_val = &p_drv_buf->tx_descr_size;
			वापस माप(p_drv_buf->tx_descr_size);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_RX_DESCRIPTORS_QUEUE_SIZE:
		अगर (p_drv_buf->rx_descr_size_set) अणु
			p_buf->p_val = &p_drv_buf->rx_descr_size;
			वापस माप(p_drv_buf->rx_descr_size);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_NUM_OF_NET_QUEUE_VMQ_CFG:
		अगर (p_drv_buf->netq_count_set) अणु
			p_buf->p_val = &p_drv_buf->netq_count;
			वापस माप(p_drv_buf->netq_count);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_NUM_OFFLOADED_CONNECTIONS_TCP_IPV4:
		अगर (p_drv_buf->tcp4_offloads_set) अणु
			p_buf->p_val = &p_drv_buf->tcp4_offloads;
			वापस माप(p_drv_buf->tcp4_offloads);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_NUM_OFFLOADED_CONNECTIONS_TCP_IPV6:
		अगर (p_drv_buf->tcp6_offloads_set) अणु
			p_buf->p_val = &p_drv_buf->tcp6_offloads;
			वापस माप(p_drv_buf->tcp6_offloads);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_TX_DESCRIPTOR_QUEUE_AVG_DEPTH:
		अगर (p_drv_buf->tx_descr_qdepth_set) अणु
			p_buf->p_val = &p_drv_buf->tx_descr_qdepth;
			वापस माप(p_drv_buf->tx_descr_qdepth);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_RX_DESCRIPTORS_QUEUE_AVG_DEPTH:
		अगर (p_drv_buf->rx_descr_qdepth_set) अणु
			p_buf->p_val = &p_drv_buf->rx_descr_qdepth;
			वापस माप(p_drv_buf->rx_descr_qdepth);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_IOV_OFFLOAD:
		अगर (p_drv_buf->iov_offload_set) अणु
			p_buf->p_val = &p_drv_buf->iov_offload;
			वापस माप(p_drv_buf->iov_offload);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_TX_QUEUES_EMPTY:
		अगर (p_drv_buf->txqs_empty_set) अणु
			p_buf->p_val = &p_drv_buf->txqs_empty;
			वापस माप(p_drv_buf->txqs_empty);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_RX_QUEUES_EMPTY:
		अगर (p_drv_buf->rxqs_empty_set) अणु
			p_buf->p_val = &p_drv_buf->rxqs_empty;
			वापस माप(p_drv_buf->rxqs_empty);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_TX_QUEUES_FULL:
		अगर (p_drv_buf->num_txqs_full_set) अणु
			p_buf->p_val = &p_drv_buf->num_txqs_full;
			वापस माप(p_drv_buf->num_txqs_full);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_RX_QUEUES_FULL:
		अगर (p_drv_buf->num_rxqs_full_set) अणु
			p_buf->p_val = &p_drv_buf->num_rxqs_full;
			वापस माप(p_drv_buf->num_rxqs_full);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक
qed_mfw_get_tlv_समय_value(काष्ठा qed_mfw_tlv_समय *p_समय,
			   काष्ठा qed_tlv_parsed_buf *p_buf)
अणु
	अगर (!p_समय->b_set)
		वापस -1;

	/* Validate numbers */
	अगर (p_समय->month > 12)
		p_समय->month = 0;
	अगर (p_समय->day > 31)
		p_समय->day = 0;
	अगर (p_समय->hour > 23)
		p_समय->hour = 0;
	अगर (p_समय->min > 59)
		p_समय->hour = 0;
	अगर (p_समय->msec > 999)
		p_समय->msec = 0;
	अगर (p_समय->usec > 999)
		p_समय->usec = 0;

	स_रखो(p_buf->data, 0, माप(u8) * QED_TLV_DATA_MAX);
	snम_लिखो(p_buf->data, 14, "%d%d%d%d%d%d",
		 p_समय->month, p_समय->day,
		 p_समय->hour, p_समय->min, p_समय->msec, p_समय->usec);

	p_buf->p_val = p_buf->data;

	वापस QED_MFW_TLV_TIME_SIZE;
पूर्ण

अटल पूर्णांक
qed_mfw_get_fcoe_tlv_value(काष्ठा qed_drv_tlv_hdr *p_tlv,
			   काष्ठा qed_mfw_tlv_fcoe *p_drv_buf,
			   काष्ठा qed_tlv_parsed_buf *p_buf)
अणु
	काष्ठा qed_mfw_tlv_समय *p_समय;
	u8 idx;

	चयन (p_tlv->tlv_type) अणु
	हाल DRV_TLV_SCSI_TO:
		अगर (p_drv_buf->scsi_समयout_set) अणु
			p_buf->p_val = &p_drv_buf->scsi_समयout;
			वापस माप(p_drv_buf->scsi_समयout);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_R_T_TOV:
		अगर (p_drv_buf->rt_tov_set) अणु
			p_buf->p_val = &p_drv_buf->rt_tov;
			वापस माप(p_drv_buf->rt_tov);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_R_A_TOV:
		अगर (p_drv_buf->ra_tov_set) अणु
			p_buf->p_val = &p_drv_buf->ra_tov;
			वापस माप(p_drv_buf->ra_tov);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_E_D_TOV:
		अगर (p_drv_buf->ed_tov_set) अणु
			p_buf->p_val = &p_drv_buf->ed_tov;
			वापस माप(p_drv_buf->ed_tov);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_CR_TOV:
		अगर (p_drv_buf->cr_tov_set) अणु
			p_buf->p_val = &p_drv_buf->cr_tov;
			वापस माप(p_drv_buf->cr_tov);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_BOOT_TYPE:
		अगर (p_drv_buf->boot_type_set) अणु
			p_buf->p_val = &p_drv_buf->boot_type;
			वापस माप(p_drv_buf->boot_type);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_NPIV_STATE:
		अगर (p_drv_buf->npiv_state_set) अणु
			p_buf->p_val = &p_drv_buf->npiv_state;
			वापस माप(p_drv_buf->npiv_state);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_NUM_OF_NPIV_IDS:
		अगर (p_drv_buf->num_npiv_ids_set) अणु
			p_buf->p_val = &p_drv_buf->num_npiv_ids;
			वापस माप(p_drv_buf->num_npiv_ids);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SWITCH_NAME:
		अगर (p_drv_buf->चयन_name_set) अणु
			p_buf->p_val = &p_drv_buf->चयन_name;
			वापस माप(p_drv_buf->चयन_name);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SWITCH_PORT_NUM:
		अगर (p_drv_buf->चयन_portnum_set) अणु
			p_buf->p_val = &p_drv_buf->चयन_portnum;
			वापस माप(p_drv_buf->चयन_portnum);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SWITCH_PORT_ID:
		अगर (p_drv_buf->चयन_portid_set) अणु
			p_buf->p_val = &p_drv_buf->चयन_portid;
			वापस माप(p_drv_buf->चयन_portid);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_VENDOR_NAME:
		अगर (p_drv_buf->venकरोr_name_set) अणु
			p_buf->p_val = &p_drv_buf->venकरोr_name;
			वापस माप(p_drv_buf->venकरोr_name);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SWITCH_MODEL:
		अगर (p_drv_buf->चयन_model_set) अणु
			p_buf->p_val = &p_drv_buf->चयन_model;
			वापस माप(p_drv_buf->चयन_model);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SWITCH_FW_VER:
		अगर (p_drv_buf->चयन_fw_version_set) अणु
			p_buf->p_val = &p_drv_buf->चयन_fw_version;
			वापस माप(p_drv_buf->चयन_fw_version);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_QOS_PRIORITY_PER_802_1P:
		अगर (p_drv_buf->qos_pri_set) अणु
			p_buf->p_val = &p_drv_buf->qos_pri;
			वापस माप(p_drv_buf->qos_pri);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PORT_ALIAS:
		अगर (p_drv_buf->port_alias_set) अणु
			p_buf->p_val = &p_drv_buf->port_alias;
			वापस माप(p_drv_buf->port_alias);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PORT_STATE:
		अगर (p_drv_buf->port_state_set) अणु
			p_buf->p_val = &p_drv_buf->port_state;
			वापस माप(p_drv_buf->port_state);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_FIP_TX_DESCRIPTORS_QUEUE_SIZE:
		अगर (p_drv_buf->fip_tx_descr_size_set) अणु
			p_buf->p_val = &p_drv_buf->fip_tx_descr_size;
			वापस माप(p_drv_buf->fip_tx_descr_size);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_FCOE_RX_DESCRIPTORS_QUEUE_SIZE:
		अगर (p_drv_buf->fip_rx_descr_size_set) अणु
			p_buf->p_val = &p_drv_buf->fip_rx_descr_size;
			वापस माप(p_drv_buf->fip_rx_descr_size);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LINK_FAILURE_COUNT:
		अगर (p_drv_buf->link_failures_set) अणु
			p_buf->p_val = &p_drv_buf->link_failures;
			वापस माप(p_drv_buf->link_failures);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_FCOE_BOOT_PROGRESS:
		अगर (p_drv_buf->fcoe_boot_progress_set) अणु
			p_buf->p_val = &p_drv_buf->fcoe_boot_progress;
			वापस माप(p_drv_buf->fcoe_boot_progress);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_RX_BROADCAST_PACKETS:
		अगर (p_drv_buf->rx_bcast_set) अणु
			p_buf->p_val = &p_drv_buf->rx_bcast;
			वापस माप(p_drv_buf->rx_bcast);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_TX_BROADCAST_PACKETS:
		अगर (p_drv_buf->tx_bcast_set) अणु
			p_buf->p_val = &p_drv_buf->tx_bcast;
			वापस माप(p_drv_buf->tx_bcast);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_FCOE_TX_DESCRIPTOR_QUEUE_AVG_DEPTH:
		अगर (p_drv_buf->fcoe_txq_depth_set) अणु
			p_buf->p_val = &p_drv_buf->fcoe_txq_depth;
			वापस माप(p_drv_buf->fcoe_txq_depth);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_FCOE_RX_DESCRIPTORS_QUEUE_AVG_DEPTH:
		अगर (p_drv_buf->fcoe_rxq_depth_set) अणु
			p_buf->p_val = &p_drv_buf->fcoe_rxq_depth;
			वापस माप(p_drv_buf->fcoe_rxq_depth);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_FCOE_RX_FRAMES_RECEIVED:
		अगर (p_drv_buf->fcoe_rx_frames_set) अणु
			p_buf->p_val = &p_drv_buf->fcoe_rx_frames;
			वापस माप(p_drv_buf->fcoe_rx_frames);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_FCOE_RX_BYTES_RECEIVED:
		अगर (p_drv_buf->fcoe_rx_bytes_set) अणु
			p_buf->p_val = &p_drv_buf->fcoe_rx_bytes;
			वापस माप(p_drv_buf->fcoe_rx_bytes);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_FCOE_TX_FRAMES_SENT:
		अगर (p_drv_buf->fcoe_tx_frames_set) अणु
			p_buf->p_val = &p_drv_buf->fcoe_tx_frames;
			वापस माप(p_drv_buf->fcoe_tx_frames);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_FCOE_TX_BYTES_SENT:
		अगर (p_drv_buf->fcoe_tx_bytes_set) अणु
			p_buf->p_val = &p_drv_buf->fcoe_tx_bytes;
			वापस माप(p_drv_buf->fcoe_tx_bytes);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_CRC_ERROR_COUNT:
		अगर (p_drv_buf->crc_count_set) अणु
			p_buf->p_val = &p_drv_buf->crc_count;
			वापस माप(p_drv_buf->crc_count);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_CRC_ERROR_1_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_CRC_ERROR_2_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_CRC_ERROR_3_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_CRC_ERROR_4_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_CRC_ERROR_5_RECEIVED_SOURCE_FC_ID:
		idx = (p_tlv->tlv_type -
		       DRV_TLV_CRC_ERROR_1_RECEIVED_SOURCE_FC_ID) / 2;

		अगर (p_drv_buf->crc_err_src_fcid_set[idx]) अणु
			p_buf->p_val = &p_drv_buf->crc_err_src_fcid[idx];
			वापस माप(p_drv_buf->crc_err_src_fcid[idx]);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_CRC_ERROR_1_TIMESTAMP:
	हाल DRV_TLV_CRC_ERROR_2_TIMESTAMP:
	हाल DRV_TLV_CRC_ERROR_3_TIMESTAMP:
	हाल DRV_TLV_CRC_ERROR_4_TIMESTAMP:
	हाल DRV_TLV_CRC_ERROR_5_TIMESTAMP:
		idx = (p_tlv->tlv_type - DRV_TLV_CRC_ERROR_1_TIMESTAMP) / 2;

		वापस qed_mfw_get_tlv_समय_value(&p_drv_buf->crc_err[idx],
						  p_buf);
	हाल DRV_TLV_LOSS_OF_SYNC_ERROR_COUNT:
		अगर (p_drv_buf->losync_err_set) अणु
			p_buf->p_val = &p_drv_buf->losync_err;
			वापस माप(p_drv_buf->losync_err);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LOSS_OF_SIGNAL_ERRORS:
		अगर (p_drv_buf->losig_err_set) अणु
			p_buf->p_val = &p_drv_buf->losig_err;
			वापस माप(p_drv_buf->losig_err);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PRIMITIVE_SEQUENCE_PROTOCOL_ERROR_COUNT:
		अगर (p_drv_buf->primtive_err_set) अणु
			p_buf->p_val = &p_drv_buf->primtive_err;
			वापस माप(p_drv_buf->primtive_err);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_DISPARITY_ERROR_COUNT:
		अगर (p_drv_buf->disparity_err_set) अणु
			p_buf->p_val = &p_drv_buf->disparity_err;
			वापस माप(p_drv_buf->disparity_err);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_CODE_VIOLATION_ERROR_COUNT:
		अगर (p_drv_buf->code_violation_err_set) अणु
			p_buf->p_val = &p_drv_buf->code_violation_err;
			वापस माप(p_drv_buf->code_violation_err);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_1:
	हाल DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_2:
	हाल DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_3:
	हाल DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_4:
		idx = p_tlv->tlv_type -
			DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_1;
		अगर (p_drv_buf->flogi_param_set[idx]) अणु
			p_buf->p_val = &p_drv_buf->flogi_param[idx];
			वापस माप(p_drv_buf->flogi_param[idx]);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LAST_FLOGI_TIMESTAMP:
		वापस qed_mfw_get_tlv_समय_value(&p_drv_buf->flogi_tstamp,
						  p_buf);
	हाल DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_1:
	हाल DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_2:
	हाल DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_3:
	हाल DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_4:
		idx = p_tlv->tlv_type -
			DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_1;

		अगर (p_drv_buf->flogi_acc_param_set[idx]) अणु
			p_buf->p_val = &p_drv_buf->flogi_acc_param[idx];
			वापस माप(p_drv_buf->flogi_acc_param[idx]);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LAST_FLOGI_ACC_TIMESTAMP:
		वापस qed_mfw_get_tlv_समय_value(&p_drv_buf->flogi_acc_tstamp,
						  p_buf);
	हाल DRV_TLV_LAST_FLOGI_RJT:
		अगर (p_drv_buf->flogi_rjt_set) अणु
			p_buf->p_val = &p_drv_buf->flogi_rjt;
			वापस माप(p_drv_buf->flogi_rjt);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LAST_FLOGI_RJT_TIMESTAMP:
		वापस qed_mfw_get_tlv_समय_value(&p_drv_buf->flogi_rjt_tstamp,
						  p_buf);
	हाल DRV_TLV_FDISCS_SENT_COUNT:
		अगर (p_drv_buf->fdiscs_set) अणु
			p_buf->p_val = &p_drv_buf->fdiscs;
			वापस माप(p_drv_buf->fdiscs);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_FDISC_ACCS_RECEIVED:
		अगर (p_drv_buf->fdisc_acc_set) अणु
			p_buf->p_val = &p_drv_buf->fdisc_acc;
			वापस माप(p_drv_buf->fdisc_acc);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_FDISC_RJTS_RECEIVED:
		अगर (p_drv_buf->fdisc_rjt_set) अणु
			p_buf->p_val = &p_drv_buf->fdisc_rjt;
			वापस माप(p_drv_buf->fdisc_rjt);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PLOGI_SENT_COUNT:
		अगर (p_drv_buf->plogi_set) अणु
			p_buf->p_val = &p_drv_buf->plogi;
			वापस माप(p_drv_buf->plogi);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PLOGI_ACCS_RECEIVED:
		अगर (p_drv_buf->plogi_acc_set) अणु
			p_buf->p_val = &p_drv_buf->plogi_acc;
			वापस माप(p_drv_buf->plogi_acc);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PLOGI_RJTS_RECEIVED:
		अगर (p_drv_buf->plogi_rjt_set) अणु
			p_buf->p_val = &p_drv_buf->plogi_rjt;
			वापस माप(p_drv_buf->plogi_rjt);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PLOGI_1_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_PLOGI_2_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_PLOGI_3_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_PLOGI_4_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_PLOGI_5_SENT_DESTINATION_FC_ID:
		idx = (p_tlv->tlv_type -
		       DRV_TLV_PLOGI_1_SENT_DESTINATION_FC_ID) / 2;

		अगर (p_drv_buf->plogi_dst_fcid_set[idx]) अणु
			p_buf->p_val = &p_drv_buf->plogi_dst_fcid[idx];
			वापस माप(p_drv_buf->plogi_dst_fcid[idx]);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PLOGI_1_TIMESTAMP:
	हाल DRV_TLV_PLOGI_2_TIMESTAMP:
	हाल DRV_TLV_PLOGI_3_TIMESTAMP:
	हाल DRV_TLV_PLOGI_4_TIMESTAMP:
	हाल DRV_TLV_PLOGI_5_TIMESTAMP:
		idx = (p_tlv->tlv_type - DRV_TLV_PLOGI_1_TIMESTAMP) / 2;

		वापस qed_mfw_get_tlv_समय_value(&p_drv_buf->plogi_tstamp[idx],
						  p_buf);
	हाल DRV_TLV_PLOGI_1_ACC_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_PLOGI_2_ACC_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_PLOGI_3_ACC_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_PLOGI_4_ACC_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_PLOGI_5_ACC_RECEIVED_SOURCE_FC_ID:
		idx = (p_tlv->tlv_type -
		       DRV_TLV_PLOGI_1_ACC_RECEIVED_SOURCE_FC_ID) / 2;

		अगर (p_drv_buf->plogi_acc_src_fcid_set[idx]) अणु
			p_buf->p_val = &p_drv_buf->plogi_acc_src_fcid[idx];
			वापस माप(p_drv_buf->plogi_acc_src_fcid[idx]);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PLOGI_1_ACC_TIMESTAMP:
	हाल DRV_TLV_PLOGI_2_ACC_TIMESTAMP:
	हाल DRV_TLV_PLOGI_3_ACC_TIMESTAMP:
	हाल DRV_TLV_PLOGI_4_ACC_TIMESTAMP:
	हाल DRV_TLV_PLOGI_5_ACC_TIMESTAMP:
		idx = (p_tlv->tlv_type - DRV_TLV_PLOGI_1_ACC_TIMESTAMP) / 2;
		p_समय = &p_drv_buf->plogi_acc_tstamp[idx];

		वापस qed_mfw_get_tlv_समय_value(p_समय, p_buf);
	हाल DRV_TLV_LOGOS_ISSUED:
		अगर (p_drv_buf->tx_plogos_set) अणु
			p_buf->p_val = &p_drv_buf->tx_plogos;
			वापस माप(p_drv_buf->tx_plogos);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LOGO_ACCS_RECEIVED:
		अगर (p_drv_buf->plogo_acc_set) अणु
			p_buf->p_val = &p_drv_buf->plogo_acc;
			वापस माप(p_drv_buf->plogo_acc);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LOGO_RJTS_RECEIVED:
		अगर (p_drv_buf->plogo_rjt_set) अणु
			p_buf->p_val = &p_drv_buf->plogo_rjt;
			वापस माप(p_drv_buf->plogo_rjt);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LOGO_1_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_LOGO_2_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_LOGO_3_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_LOGO_4_RECEIVED_SOURCE_FC_ID:
	हाल DRV_TLV_LOGO_5_RECEIVED_SOURCE_FC_ID:
		idx = (p_tlv->tlv_type - DRV_TLV_LOGO_1_RECEIVED_SOURCE_FC_ID) /
			2;

		अगर (p_drv_buf->plogo_src_fcid_set[idx]) अणु
			p_buf->p_val = &p_drv_buf->plogo_src_fcid[idx];
			वापस माप(p_drv_buf->plogo_src_fcid[idx]);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LOGO_1_TIMESTAMP:
	हाल DRV_TLV_LOGO_2_TIMESTAMP:
	हाल DRV_TLV_LOGO_3_TIMESTAMP:
	हाल DRV_TLV_LOGO_4_TIMESTAMP:
	हाल DRV_TLV_LOGO_5_TIMESTAMP:
		idx = (p_tlv->tlv_type - DRV_TLV_LOGO_1_TIMESTAMP) / 2;

		वापस qed_mfw_get_tlv_समय_value(&p_drv_buf->plogo_tstamp[idx],
						  p_buf);
	हाल DRV_TLV_LOGOS_RECEIVED:
		अगर (p_drv_buf->rx_logos_set) अणु
			p_buf->p_val = &p_drv_buf->rx_logos;
			वापस माप(p_drv_buf->rx_logos);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_ACCS_ISSUED:
		अगर (p_drv_buf->tx_accs_set) अणु
			p_buf->p_val = &p_drv_buf->tx_accs;
			वापस माप(p_drv_buf->tx_accs);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PRLIS_ISSUED:
		अगर (p_drv_buf->tx_prlis_set) अणु
			p_buf->p_val = &p_drv_buf->tx_prlis;
			वापस माप(p_drv_buf->tx_prlis);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_ACCS_RECEIVED:
		अगर (p_drv_buf->rx_accs_set) अणु
			p_buf->p_val = &p_drv_buf->rx_accs;
			वापस माप(p_drv_buf->rx_accs);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_ABTS_SENT_COUNT:
		अगर (p_drv_buf->tx_abts_set) अणु
			p_buf->p_val = &p_drv_buf->tx_abts;
			वापस माप(p_drv_buf->tx_abts);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_ABTS_ACCS_RECEIVED:
		अगर (p_drv_buf->rx_abts_acc_set) अणु
			p_buf->p_val = &p_drv_buf->rx_abts_acc;
			वापस माप(p_drv_buf->rx_abts_acc);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_ABTS_RJTS_RECEIVED:
		अगर (p_drv_buf->rx_abts_rjt_set) अणु
			p_buf->p_val = &p_drv_buf->rx_abts_rjt;
			वापस माप(p_drv_buf->rx_abts_rjt);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_ABTS_1_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_ABTS_2_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_ABTS_3_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_ABTS_4_SENT_DESTINATION_FC_ID:
	हाल DRV_TLV_ABTS_5_SENT_DESTINATION_FC_ID:
		idx = (p_tlv->tlv_type -
		       DRV_TLV_ABTS_1_SENT_DESTINATION_FC_ID) / 2;

		अगर (p_drv_buf->abts_dst_fcid_set[idx]) अणु
			p_buf->p_val = &p_drv_buf->abts_dst_fcid[idx];
			वापस माप(p_drv_buf->abts_dst_fcid[idx]);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_ABTS_1_TIMESTAMP:
	हाल DRV_TLV_ABTS_2_TIMESTAMP:
	हाल DRV_TLV_ABTS_3_TIMESTAMP:
	हाल DRV_TLV_ABTS_4_TIMESTAMP:
	हाल DRV_TLV_ABTS_5_TIMESTAMP:
		idx = (p_tlv->tlv_type - DRV_TLV_ABTS_1_TIMESTAMP) / 2;

		वापस qed_mfw_get_tlv_समय_value(&p_drv_buf->abts_tstamp[idx],
						  p_buf);
	हाल DRV_TLV_RSCNS_RECEIVED:
		अगर (p_drv_buf->rx_rscn_set) अणु
			p_buf->p_val = &p_drv_buf->rx_rscn;
			वापस माप(p_drv_buf->rx_rscn);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_1:
	हाल DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_2:
	हाल DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_3:
	हाल DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_4:
		idx = p_tlv->tlv_type - DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_1;

		अगर (p_drv_buf->rx_rscn_nport_set[idx]) अणु
			p_buf->p_val = &p_drv_buf->rx_rscn_nport[idx];
			वापस माप(p_drv_buf->rx_rscn_nport[idx]);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LUN_RESETS_ISSUED:
		अगर (p_drv_buf->tx_lun_rst_set) अणु
			p_buf->p_val = &p_drv_buf->tx_lun_rst;
			वापस माप(p_drv_buf->tx_lun_rst);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_ABORT_TASK_SETS_ISSUED:
		अगर (p_drv_buf->पात_task_sets_set) अणु
			p_buf->p_val = &p_drv_buf->पात_task_sets;
			वापस माप(p_drv_buf->पात_task_sets);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_TPRLOS_SENT:
		अगर (p_drv_buf->tx_tprlos_set) अणु
			p_buf->p_val = &p_drv_buf->tx_tprlos;
			वापस माप(p_drv_buf->tx_tprlos);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_NOS_SENT_COUNT:
		अगर (p_drv_buf->tx_nos_set) अणु
			p_buf->p_val = &p_drv_buf->tx_nos;
			वापस माप(p_drv_buf->tx_nos);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_NOS_RECEIVED_COUNT:
		अगर (p_drv_buf->rx_nos_set) अणु
			p_buf->p_val = &p_drv_buf->rx_nos;
			वापस माप(p_drv_buf->rx_nos);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_OLS_COUNT:
		अगर (p_drv_buf->ols_set) अणु
			p_buf->p_val = &p_drv_buf->ols;
			वापस माप(p_drv_buf->ols);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LR_COUNT:
		अगर (p_drv_buf->lr_set) अणु
			p_buf->p_val = &p_drv_buf->lr;
			वापस माप(p_drv_buf->lr);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LRR_COUNT:
		अगर (p_drv_buf->lrr_set) अणु
			p_buf->p_val = &p_drv_buf->lrr;
			वापस माप(p_drv_buf->lrr);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LIP_SENT_COUNT:
		अगर (p_drv_buf->tx_lip_set) अणु
			p_buf->p_val = &p_drv_buf->tx_lip;
			वापस माप(p_drv_buf->tx_lip);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_LIP_RECEIVED_COUNT:
		अगर (p_drv_buf->rx_lip_set) अणु
			p_buf->p_val = &p_drv_buf->rx_lip;
			वापस माप(p_drv_buf->rx_lip);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_खातापूर्णA_COUNT:
		अगर (p_drv_buf->eofa_set) अणु
			p_buf->p_val = &p_drv_buf->eofa;
			वापस माप(p_drv_buf->eofa);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_खातापूर्णNI_COUNT:
		अगर (p_drv_buf->eofni_set) अणु
			p_buf->p_val = &p_drv_buf->eofni;
			वापस माप(p_drv_buf->eofni);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SCSI_STATUS_CHECK_CONDITION_COUNT:
		अगर (p_drv_buf->scsi_chks_set) अणु
			p_buf->p_val = &p_drv_buf->scsi_chks;
			वापस माप(p_drv_buf->scsi_chks);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SCSI_STATUS_CONDITION_MET_COUNT:
		अगर (p_drv_buf->scsi_cond_met_set) अणु
			p_buf->p_val = &p_drv_buf->scsi_cond_met;
			वापस माप(p_drv_buf->scsi_cond_met);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SCSI_STATUS_BUSY_COUNT:
		अगर (p_drv_buf->scsi_busy_set) अणु
			p_buf->p_val = &p_drv_buf->scsi_busy;
			वापस माप(p_drv_buf->scsi_busy);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SCSI_STATUS_INTERMEDIATE_COUNT:
		अगर (p_drv_buf->scsi_पूर्णांकer_set) अणु
			p_buf->p_val = &p_drv_buf->scsi_पूर्णांकer;
			वापस माप(p_drv_buf->scsi_पूर्णांकer);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SCSI_STATUS_INTERMEDIATE_CONDITION_MET_COUNT:
		अगर (p_drv_buf->scsi_पूर्णांकer_cond_met_set) अणु
			p_buf->p_val = &p_drv_buf->scsi_पूर्णांकer_cond_met;
			वापस माप(p_drv_buf->scsi_पूर्णांकer_cond_met);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SCSI_STATUS_RESERVATION_CONFLICT_COUNT:
		अगर (p_drv_buf->scsi_rsv_conflicts_set) अणु
			p_buf->p_val = &p_drv_buf->scsi_rsv_conflicts;
			वापस माप(p_drv_buf->scsi_rsv_conflicts);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SCSI_STATUS_TASK_SET_FULL_COUNT:
		अगर (p_drv_buf->scsi_tsk_full_set) अणु
			p_buf->p_val = &p_drv_buf->scsi_tsk_full;
			वापस माप(p_drv_buf->scsi_tsk_full);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SCSI_STATUS_ACA_ACTIVE_COUNT:
		अगर (p_drv_buf->scsi_aca_active_set) अणु
			p_buf->p_val = &p_drv_buf->scsi_aca_active;
			वापस माप(p_drv_buf->scsi_aca_active);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SCSI_STATUS_TASK_ABORTED_COUNT:
		अगर (p_drv_buf->scsi_tsk_पात_set) अणु
			p_buf->p_val = &p_drv_buf->scsi_tsk_पात;
			वापस माप(p_drv_buf->scsi_tsk_पात);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SCSI_CHECK_CONDITION_1_RECEIVED_SK_ASC_ASCQ:
	हाल DRV_TLV_SCSI_CHECK_CONDITION_2_RECEIVED_SK_ASC_ASCQ:
	हाल DRV_TLV_SCSI_CHECK_CONDITION_3_RECEIVED_SK_ASC_ASCQ:
	हाल DRV_TLV_SCSI_CHECK_CONDITION_4_RECEIVED_SK_ASC_ASCQ:
	हाल DRV_TLV_SCSI_CHECK_CONDITION_5_RECEIVED_SK_ASC_ASCQ:
		idx = (p_tlv->tlv_type -
		       DRV_TLV_SCSI_CHECK_CONDITION_1_RECEIVED_SK_ASC_ASCQ) / 2;

		अगर (p_drv_buf->scsi_rx_chk_set[idx]) अणु
			p_buf->p_val = &p_drv_buf->scsi_rx_chk[idx];
			वापस माप(p_drv_buf->scsi_rx_chk[idx]);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_SCSI_CHECK_1_TIMESTAMP:
	हाल DRV_TLV_SCSI_CHECK_2_TIMESTAMP:
	हाल DRV_TLV_SCSI_CHECK_3_TIMESTAMP:
	हाल DRV_TLV_SCSI_CHECK_4_TIMESTAMP:
	हाल DRV_TLV_SCSI_CHECK_5_TIMESTAMP:
		idx = (p_tlv->tlv_type - DRV_TLV_SCSI_CHECK_1_TIMESTAMP) / 2;
		p_समय = &p_drv_buf->scsi_chk_tstamp[idx];

		वापस qed_mfw_get_tlv_समय_value(p_समय, p_buf);
	शेष:
		अवरोध;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक
qed_mfw_get_iscsi_tlv_value(काष्ठा qed_drv_tlv_hdr *p_tlv,
			    काष्ठा qed_mfw_tlv_iscsi *p_drv_buf,
			    काष्ठा qed_tlv_parsed_buf *p_buf)
अणु
	चयन (p_tlv->tlv_type) अणु
	हाल DRV_TLV_TARGET_LLMNR_ENABLED:
		अगर (p_drv_buf->target_llmnr_set) अणु
			p_buf->p_val = &p_drv_buf->target_llmnr;
			वापस माप(p_drv_buf->target_llmnr);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_HEADER_DIGEST_FLAG_ENABLED:
		अगर (p_drv_buf->header_digest_set) अणु
			p_buf->p_val = &p_drv_buf->header_digest;
			वापस माप(p_drv_buf->header_digest);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_DATA_DIGEST_FLAG_ENABLED:
		अगर (p_drv_buf->data_digest_set) अणु
			p_buf->p_val = &p_drv_buf->data_digest;
			वापस माप(p_drv_buf->data_digest);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_AUTHENTICATION_METHOD:
		अगर (p_drv_buf->auth_method_set) अणु
			p_buf->p_val = &p_drv_buf->auth_method;
			वापस माप(p_drv_buf->auth_method);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_ISCSI_BOOT_TARGET_PORTAL:
		अगर (p_drv_buf->boot_taget_portal_set) अणु
			p_buf->p_val = &p_drv_buf->boot_taget_portal;
			वापस माप(p_drv_buf->boot_taget_portal);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_MAX_FRAME_SIZE:
		अगर (p_drv_buf->frame_size_set) अणु
			p_buf->p_val = &p_drv_buf->frame_size;
			वापस माप(p_drv_buf->frame_size);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PDU_TX_DESCRIPTORS_QUEUE_SIZE:
		अगर (p_drv_buf->tx_desc_size_set) अणु
			p_buf->p_val = &p_drv_buf->tx_desc_size;
			वापस माप(p_drv_buf->tx_desc_size);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PDU_RX_DESCRIPTORS_QUEUE_SIZE:
		अगर (p_drv_buf->rx_desc_size_set) अणु
			p_buf->p_val = &p_drv_buf->rx_desc_size;
			वापस माप(p_drv_buf->rx_desc_size);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_ISCSI_BOOT_PROGRESS:
		अगर (p_drv_buf->boot_progress_set) अणु
			p_buf->p_val = &p_drv_buf->boot_progress;
			वापस माप(p_drv_buf->boot_progress);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PDU_TX_DESCRIPTOR_QUEUE_AVG_DEPTH:
		अगर (p_drv_buf->tx_desc_qdepth_set) अणु
			p_buf->p_val = &p_drv_buf->tx_desc_qdepth;
			वापस माप(p_drv_buf->tx_desc_qdepth);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_PDU_RX_DESCRIPTORS_QUEUE_AVG_DEPTH:
		अगर (p_drv_buf->rx_desc_qdepth_set) अणु
			p_buf->p_val = &p_drv_buf->rx_desc_qdepth;
			वापस माप(p_drv_buf->rx_desc_qdepth);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_ISCSI_PDU_RX_FRAMES_RECEIVED:
		अगर (p_drv_buf->rx_frames_set) अणु
			p_buf->p_val = &p_drv_buf->rx_frames;
			वापस माप(p_drv_buf->rx_frames);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_ISCSI_PDU_RX_BYTES_RECEIVED:
		अगर (p_drv_buf->rx_bytes_set) अणु
			p_buf->p_val = &p_drv_buf->rx_bytes;
			वापस माप(p_drv_buf->rx_bytes);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_ISCSI_PDU_TX_FRAMES_SENT:
		अगर (p_drv_buf->tx_frames_set) अणु
			p_buf->p_val = &p_drv_buf->tx_frames;
			वापस माप(p_drv_buf->tx_frames);
		पूर्ण
		अवरोध;
	हाल DRV_TLV_ISCSI_PDU_TX_BYTES_SENT:
		अगर (p_drv_buf->tx_bytes_set) अणु
			p_buf->p_val = &p_drv_buf->tx_bytes;
			वापस माप(p_drv_buf->tx_bytes);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक qed_mfw_update_tlvs(काष्ठा qed_hwfn *p_hwfn,
			       u8 tlv_group, u8 *p_mfw_buf, u32 size)
अणु
	जोड़ qed_mfw_tlv_data *p_tlv_data;
	काष्ठा qed_tlv_parsed_buf buffer;
	काष्ठा qed_drv_tlv_hdr tlv;
	पूर्णांक len = 0;
	u32 offset;
	u8 *p_tlv;

	p_tlv_data = vzalloc(माप(*p_tlv_data));
	अगर (!p_tlv_data)
		वापस -ENOMEM;

	अगर (qed_mfw_fill_tlv_data(p_hwfn, tlv_group, p_tlv_data)) अणु
		vमुक्त(p_tlv_data);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&tlv, 0, माप(tlv));
	क्रम (offset = 0; offset < size;
	     offset += माप(tlv) + माप(u32) * tlv.tlv_length) अणु
		p_tlv = &p_mfw_buf[offset];
		tlv.tlv_type = TLV_TYPE(p_tlv);
		tlv.tlv_length = TLV_LENGTH(p_tlv);
		tlv.tlv_flags = TLV_FLAGS(p_tlv);

		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "Type %d length = %d flags = 0x%x\n", tlv.tlv_type,
			   tlv.tlv_length, tlv.tlv_flags);

		अगर (tlv_group == QED_MFW_TLV_GENERIC)
			len = qed_mfw_get_gen_tlv_value(&tlv,
							&p_tlv_data->generic,
							&buffer);
		अन्यथा अगर (tlv_group == QED_MFW_TLV_ETH)
			len = qed_mfw_get_eth_tlv_value(&tlv,
							&p_tlv_data->eth,
							&buffer);
		अन्यथा अगर (tlv_group == QED_MFW_TLV_FCOE)
			len = qed_mfw_get_fcoe_tlv_value(&tlv,
							 &p_tlv_data->fcoe,
							 &buffer);
		अन्यथा
			len = qed_mfw_get_iscsi_tlv_value(&tlv,
							  &p_tlv_data->iscsi,
							  &buffer);

		अगर (len > 0) अणु
			WARN(len > 4 * tlv.tlv_length,
			     "Incorrect MFW TLV length %d, it shouldn't be greater than %d\n",
			     len, 4 * tlv.tlv_length);
			len = min_t(पूर्णांक, len, 4 * tlv.tlv_length);
			tlv.tlv_flags |= QED_DRV_TLV_FLAGS_CHANGED;
			TLV_FLAGS(p_tlv) = tlv.tlv_flags;
			स_नकल(p_mfw_buf + offset + माप(tlv),
			       buffer.p_val, len);
		पूर्ण
	पूर्ण

	vमुक्त(p_tlv_data);

	वापस 0;
पूर्ण

पूर्णांक qed_mfw_process_tlv_req(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 addr, size, offset, resp, param, val, global_offsize, global_addr;
	u8 tlv_group = 0, id, *p_mfw_buf = शून्य, *p_temp;
	काष्ठा qed_drv_tlv_hdr tlv;
	पूर्णांक rc;

	addr = SECTION_OFFSIZE_ADDR(p_hwfn->mcp_info->खुला_base,
				    PUBLIC_GLOBAL);
	global_offsize = qed_rd(p_hwfn, p_ptt, addr);
	global_addr = SECTION_ADDR(global_offsize, 0);
	addr = global_addr + दुरत्व(काष्ठा खुला_global, data_ptr);
	addr = qed_rd(p_hwfn, p_ptt, addr);
	size = qed_rd(p_hwfn, p_ptt, global_addr +
		      दुरत्व(काष्ठा खुला_global, data_size));

	अगर (!size) अणु
		DP_NOTICE(p_hwfn, "Invalid TLV req size = %d\n", size);
		जाओ drv_करोne;
	पूर्ण

	p_mfw_buf = vzalloc(size);
	अगर (!p_mfw_buf) अणु
		DP_NOTICE(p_hwfn, "Failed allocate memory for p_mfw_buf\n");
		जाओ drv_करोne;
	पूर्ण

	/* Read the TLV request to local buffer. MFW represents the TLV in
	 * little endian क्रमmat and mcp वापसs it bigendian क्रमmat. Hence
	 * driver need to convert data to little endian first and then करो the
	 * स_नकल (casting) to preserve the MFW TLV क्रमmat in the driver buffer.
	 *
	 */
	क्रम (offset = 0; offset < size; offset += माप(u32)) अणु
		val = qed_rd(p_hwfn, p_ptt, addr + offset);
		val = be32_to_cpu((__क्रमce __be32)val);
		स_नकल(&p_mfw_buf[offset], &val, माप(u32));
	पूर्ण

	/* Parse the headers to क्रमागतerate the requested TLV groups */
	क्रम (offset = 0; offset < size;
	     offset += माप(tlv) + माप(u32) * tlv.tlv_length) अणु
		p_temp = &p_mfw_buf[offset];
		tlv.tlv_type = TLV_TYPE(p_temp);
		tlv.tlv_length = TLV_LENGTH(p_temp);
		अगर (qed_mfw_get_tlv_group(tlv.tlv_type, &tlv_group))
			DP_VERBOSE(p_hwfn, NETIF_MSG_DRV,
				   "Un recognized TLV %d\n", tlv.tlv_type);
	पूर्ण

	/* Sanitize the TLV groups according to personality */
	अगर ((tlv_group & QED_MFW_TLV_ETH) && !QED_IS_L2_PERSONALITY(p_hwfn)) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "Skipping L2 TLVs for non-L2 function\n");
		tlv_group &= ~QED_MFW_TLV_ETH;
	पूर्ण

	अगर ((tlv_group & QED_MFW_TLV_FCOE) &&
	    p_hwfn->hw_info.personality != QED_PCI_FCOE) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "Skipping FCoE TLVs for non-FCoE function\n");
		tlv_group &= ~QED_MFW_TLV_FCOE;
	पूर्ण

	अगर ((tlv_group & QED_MFW_TLV_ISCSI) &&
	    p_hwfn->hw_info.personality != QED_PCI_ISCSI) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "Skipping iSCSI TLVs for non-iSCSI function\n");
		tlv_group &= ~QED_MFW_TLV_ISCSI;
	पूर्ण

	/* Update the TLV values in the local buffer */
	क्रम (id = QED_MFW_TLV_GENERIC; id < QED_MFW_TLV_MAX; id <<= 1) अणु
		अगर (tlv_group & id)
			अगर (qed_mfw_update_tlvs(p_hwfn, id, p_mfw_buf, size))
				जाओ drv_करोne;
	पूर्ण

	/* Write the TLV data to shared memory. The stream of 4 bytes first need
	 * to be mem-copied to u32 element to make it as LSB क्रमmat. And then
	 * converted to big endian as required by mcp-ग_लिखो.
	 */
	क्रम (offset = 0; offset < size; offset += माप(u32)) अणु
		स_नकल(&val, &p_mfw_buf[offset], माप(u32));
		val = (__क्रमce u32)cpu_to_be32(val);
		qed_wr(p_hwfn, p_ptt, addr + offset, val);
	पूर्ण

drv_करोne:
	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_GET_TLV_DONE, 0, &resp,
			 &param);

	vमुक्त(p_mfw_buf);

	वापस rc;
पूर्ण
