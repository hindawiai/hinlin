<शैली गुरु>
/* 57xx_iscsi_hsi.h: QLogic NetXtreme II iSCSI HSI.
 *
 * Copyright (c) 2006 - 2013 Broadcom Corporation
 * Copyright (c) 2014, QLogic Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Anil Veerabhadrappa (anilgv@broadcom.com)
 * Previously Maपूर्णांकained by: Eddie Wai (eddie.wai@broadcom.com)
 * Maपूर्णांकained by: QLogic-Storage-Upstream@qlogic.com
 */
#अगर_अघोषित __57XX_ISCSI_HSI_LINUX_LE__
#घोषणा __57XX_ISCSI_HSI_LINUX_LE__

/*
 * iSCSI Async CQE
 */
काष्ठा bnx2i_async_msg अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 reserved1;
	u16 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved0;
	u8 reserved1;
	u8 op_code;
#पूर्ण_अगर
	u32 reserved2;
	u32 exp_cmd_sn;
	u32 max_cmd_sn;
	u32 reserved3[2];
#अगर defined(__BIG_ENDIAN)
	u16 reserved5;
	u8 err_code;
	u8 reserved4;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 reserved4;
	u8 err_code;
	u16 reserved5;
#पूर्ण_अगर
	u32 reserved6;
	u32 lun[2];
#अगर defined(__BIG_ENDIAN)
	u8 async_event;
	u8 async_vcode;
	u16 param1;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 param1;
	u8 async_vcode;
	u8 async_event;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u16 param2;
	u16 param3;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 param3;
	u16 param2;
#पूर्ण_अगर
	u32 reserved7[3];
	u32 cq_req_sn;
पूर्ण;


/*
 * iSCSI Buffer Descriptor (BD)
 */
काष्ठा iscsi_bd अणु
	u32 buffer_addr_hi;
	u32 buffer_addr_lo;
#अगर defined(__BIG_ENDIAN)
	u16 reserved0;
	u16 buffer_length;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 buffer_length;
	u16 reserved0;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u16 reserved3;
	u16 flags;
#घोषणा ISCSI_BD_RESERVED1 (0x3F<<0)
#घोषणा ISCSI_BD_RESERVED1_SHIFT 0
#घोषणा ISCSI_BD_LAST_IN_BD_CHAIN (0x1<<6)
#घोषणा ISCSI_BD_LAST_IN_BD_CHAIN_SHIFT 6
#घोषणा ISCSI_BD_FIRST_IN_BD_CHAIN (0x1<<7)
#घोषणा ISCSI_BD_FIRST_IN_BD_CHAIN_SHIFT 7
#घोषणा ISCSI_BD_RESERVED2 (0xFF<<8)
#घोषणा ISCSI_BD_RESERVED2_SHIFT 8
#या_अगर defined(__LITTLE_ENDIAN)
	u16 flags;
#घोषणा ISCSI_BD_RESERVED1 (0x3F<<0)
#घोषणा ISCSI_BD_RESERVED1_SHIFT 0
#घोषणा ISCSI_BD_LAST_IN_BD_CHAIN (0x1<<6)
#घोषणा ISCSI_BD_LAST_IN_BD_CHAIN_SHIFT 6
#घोषणा ISCSI_BD_FIRST_IN_BD_CHAIN (0x1<<7)
#घोषणा ISCSI_BD_FIRST_IN_BD_CHAIN_SHIFT 7
#घोषणा ISCSI_BD_RESERVED2 (0xFF<<8)
#घोषणा ISCSI_BD_RESERVED2_SHIFT 8
	u16 reserved3;
#पूर्ण_अगर
पूर्ण;


/*
 * iSCSI Cleanup SQ WQE
 */
काष्ठा bnx2i_cleanup_request अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 reserved1;
	u16 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved0;
	u8 reserved1;
	u8 op_code;
#पूर्ण_अगर
	u32 reserved2[3];
#अगर defined(__BIG_ENDIAN)
	u16 reserved3;
	u16 itt;
#घोषणा ISCSI_CLEANUP_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_CLEANUP_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_CLEANUP_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_CLEANUP_REQUEST_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_CLEANUP_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_CLEANUP_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_CLEANUP_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_CLEANUP_REQUEST_TYPE_SHIFT 14
	u16 reserved3;
#पूर्ण_अगर
	u32 reserved4[10];
#अगर defined(__BIG_ENDIAN)
	u8 cq_index;
	u8 reserved6;
	u16 reserved5;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved5;
	u8 reserved6;
	u8 cq_index;
#पूर्ण_अगर
पूर्ण;


/*
 * iSCSI Cleanup CQE
 */
काष्ठा bnx2i_cleanup_response अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 status;
	u16 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved0;
	u8 status;
	u8 op_code;
#पूर्ण_अगर
	u32 reserved1[3];
	u32 reserved2[2];
#अगर defined(__BIG_ENDIAN)
	u16 reserved4;
	u8 err_code;
	u8 reserved3;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 reserved3;
	u8 err_code;
	u16 reserved4;
#पूर्ण_अगर
	u32 reserved5[7];
#अगर defined(__BIG_ENDIAN)
	u16 reserved6;
	u16 itt;
#घोषणा ISCSI_CLEANUP_RESPONSE_INDEX (0x3FFF<<0)
#घोषणा ISCSI_CLEANUP_RESPONSE_INDEX_SHIFT 0
#घोषणा ISCSI_CLEANUP_RESPONSE_TYPE (0x3<<14)
#घोषणा ISCSI_CLEANUP_RESPONSE_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_CLEANUP_RESPONSE_INDEX (0x3FFF<<0)
#घोषणा ISCSI_CLEANUP_RESPONSE_INDEX_SHIFT 0
#घोषणा ISCSI_CLEANUP_RESPONSE_TYPE (0x3<<14)
#घोषणा ISCSI_CLEANUP_RESPONSE_TYPE_SHIFT 14
	u16 reserved6;
#पूर्ण_अगर
	u32 cq_req_sn;
पूर्ण;


/*
 * SCSI पढ़ो/ग_लिखो SQ WQE
 */
काष्ठा bnx2i_cmd_request अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 op_attr;
#घोषणा ISCSI_CMD_REQUEST_TASK_ATTR (0x7<<0)
#घोषणा ISCSI_CMD_REQUEST_TASK_ATTR_SHIFT 0
#घोषणा ISCSI_CMD_REQUEST_RESERVED1 (0x3<<3)
#घोषणा ISCSI_CMD_REQUEST_RESERVED1_SHIFT 3
#घोषणा ISCSI_CMD_REQUEST_WRITE (0x1<<5)
#घोषणा ISCSI_CMD_REQUEST_WRITE_SHIFT 5
#घोषणा ISCSI_CMD_REQUEST_READ (0x1<<6)
#घोषणा ISCSI_CMD_REQUEST_READ_SHIFT 6
#घोषणा ISCSI_CMD_REQUEST_FINAL (0x1<<7)
#घोषणा ISCSI_CMD_REQUEST_FINAL_SHIFT 7
	u16 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved0;
	u8 op_attr;
#घोषणा ISCSI_CMD_REQUEST_TASK_ATTR (0x7<<0)
#घोषणा ISCSI_CMD_REQUEST_TASK_ATTR_SHIFT 0
#घोषणा ISCSI_CMD_REQUEST_RESERVED1 (0x3<<3)
#घोषणा ISCSI_CMD_REQUEST_RESERVED1_SHIFT 3
#घोषणा ISCSI_CMD_REQUEST_WRITE (0x1<<5)
#घोषणा ISCSI_CMD_REQUEST_WRITE_SHIFT 5
#घोषणा ISCSI_CMD_REQUEST_READ (0x1<<6)
#घोषणा ISCSI_CMD_REQUEST_READ_SHIFT 6
#घोषणा ISCSI_CMD_REQUEST_FINAL (0x1<<7)
#घोषणा ISCSI_CMD_REQUEST_FINAL_SHIFT 7
	u8 op_code;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u16 ud_buffer_offset;
	u16 sd_buffer_offset;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 sd_buffer_offset;
	u16 ud_buffer_offset;
#पूर्ण_अगर
	u32 lun[2];
#अगर defined(__BIG_ENDIAN)
	u16 reserved2;
	u16 itt;
#घोषणा ISCSI_CMD_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_CMD_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_CMD_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_CMD_REQUEST_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_CMD_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_CMD_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_CMD_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_CMD_REQUEST_TYPE_SHIFT 14
	u16 reserved2;
#पूर्ण_अगर
	u32 total_data_transfer_length;
	u32 cmd_sn;
	u32 reserved3;
	u32 cdb[4];
	u32 zero_fill;
	u32 bd_list_addr_lo;
	u32 bd_list_addr_hi;
#अगर defined(__BIG_ENDIAN)
	u8 cq_index;
	u8 sd_start_bd_index;
	u8 ud_start_bd_index;
	u8 num_bds;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 num_bds;
	u8 ud_start_bd_index;
	u8 sd_start_bd_index;
	u8 cq_index;
#पूर्ण_अगर
पूर्ण;


/*
 * task statistics क्रम ग_लिखो response
 */
काष्ठा bnx2i_ग_लिखो_resp_task_stat अणु
#अगर defined(__BIG_ENDIAN)
	u16 num_r2ts;
	u16 num_data_outs;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 num_data_outs;
	u16 num_r2ts;
#पूर्ण_अगर
पूर्ण;

/*
 * task statistics क्रम पढ़ो response
 */
काष्ठा bnx2i_पढ़ो_resp_task_stat अणु
#अगर defined(__BIG_ENDIAN)
	u16 reserved;
	u16 num_data_ins;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 num_data_ins;
	u16 reserved;
#पूर्ण_अगर
पूर्ण;

/*
 * task statistics क्रम iSCSI cmd response
 */
जोड़ bnx2i_cmd_resp_task_stat अणु
	काष्ठा bnx2i_ग_लिखो_resp_task_stat ग_लिखो_stat;
	काष्ठा bnx2i_पढ़ो_resp_task_stat पढ़ो_stat;
पूर्ण;

/*
 * SCSI Command CQE
 */
काष्ठा bnx2i_cmd_response अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 response_flags;
#घोषणा ISCSI_CMD_RESPONSE_RESERVED0 (0x1<<0)
#घोषणा ISCSI_CMD_RESPONSE_RESERVED0_SHIFT 0
#घोषणा ISCSI_CMD_RESPONSE_RESIDUAL_UNDERFLOW (0x1<<1)
#घोषणा ISCSI_CMD_RESPONSE_RESIDUAL_UNDERFLOW_SHIFT 1
#घोषणा ISCSI_CMD_RESPONSE_RESIDUAL_OVERFLOW (0x1<<2)
#घोषणा ISCSI_CMD_RESPONSE_RESIDUAL_OVERFLOW_SHIFT 2
#घोषणा ISCSI_CMD_RESPONSE_BR_RESIDUAL_UNDERFLOW (0x1<<3)
#घोषणा ISCSI_CMD_RESPONSE_BR_RESIDUAL_UNDERFLOW_SHIFT 3
#घोषणा ISCSI_CMD_RESPONSE_BR_RESIDUAL_OVERFLOW (0x1<<4)
#घोषणा ISCSI_CMD_RESPONSE_BR_RESIDUAL_OVERFLOW_SHIFT 4
#घोषणा ISCSI_CMD_RESPONSE_RESERVED1 (0x7<<5)
#घोषणा ISCSI_CMD_RESPONSE_RESERVED1_SHIFT 5
	u8 response;
	u8 status;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 status;
	u8 response;
	u8 response_flags;
#घोषणा ISCSI_CMD_RESPONSE_RESERVED0 (0x1<<0)
#घोषणा ISCSI_CMD_RESPONSE_RESERVED0_SHIFT 0
#घोषणा ISCSI_CMD_RESPONSE_RESIDUAL_UNDERFLOW (0x1<<1)
#घोषणा ISCSI_CMD_RESPONSE_RESIDUAL_UNDERFLOW_SHIFT 1
#घोषणा ISCSI_CMD_RESPONSE_RESIDUAL_OVERFLOW (0x1<<2)
#घोषणा ISCSI_CMD_RESPONSE_RESIDUAL_OVERFLOW_SHIFT 2
#घोषणा ISCSI_CMD_RESPONSE_BR_RESIDUAL_UNDERFLOW (0x1<<3)
#घोषणा ISCSI_CMD_RESPONSE_BR_RESIDUAL_UNDERFLOW_SHIFT 3
#घोषणा ISCSI_CMD_RESPONSE_BR_RESIDUAL_OVERFLOW (0x1<<4)
#घोषणा ISCSI_CMD_RESPONSE_BR_RESIDUAL_OVERFLOW_SHIFT 4
#घोषणा ISCSI_CMD_RESPONSE_RESERVED1 (0x7<<5)
#घोषणा ISCSI_CMD_RESPONSE_RESERVED1_SHIFT 5
	u8 op_code;
#पूर्ण_अगर
	u32 data_length;
	u32 exp_cmd_sn;
	u32 max_cmd_sn;
	u32 reserved2;
	u32 residual_count;
#अगर defined(__BIG_ENDIAN)
	u16 reserved4;
	u8 err_code;
	u8 reserved3;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 reserved3;
	u8 err_code;
	u16 reserved4;
#पूर्ण_अगर
	u32 reserved5[5];
	जोड़ bnx2i_cmd_resp_task_stat task_stat;
	u32 reserved6;
#अगर defined(__BIG_ENDIAN)
	u16 reserved7;
	u16 itt;
#घोषणा ISCSI_CMD_RESPONSE_INDEX (0x3FFF<<0)
#घोषणा ISCSI_CMD_RESPONSE_INDEX_SHIFT 0
#घोषणा ISCSI_CMD_RESPONSE_TYPE (0x3<<14)
#घोषणा ISCSI_CMD_RESPONSE_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_CMD_RESPONSE_INDEX (0x3FFF<<0)
#घोषणा ISCSI_CMD_RESPONSE_INDEX_SHIFT 0
#घोषणा ISCSI_CMD_RESPONSE_TYPE (0x3<<14)
#घोषणा ISCSI_CMD_RESPONSE_TYPE_SHIFT 14
	u16 reserved7;
#पूर्ण_अगर
	u32 cq_req_sn;
पूर्ण;



/*
 * firmware middle-path request SQ WQE
 */
काष्ठा bnx2i_fw_mp_request अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 op_attr;
	u16 hdr_opaque1;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 hdr_opaque1;
	u8 op_attr;
	u8 op_code;
#पूर्ण_अगर
	u32 data_length;
	u32 hdr_opaque2[2];
#अगर defined(__BIG_ENDIAN)
	u16 reserved0;
	u16 itt;
#घोषणा ISCSI_FW_MP_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_FW_MP_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_FW_MP_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_FW_MP_REQUEST_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_FW_MP_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_FW_MP_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_FW_MP_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_FW_MP_REQUEST_TYPE_SHIFT 14
	u16 reserved0;
#पूर्ण_अगर
	u32 hdr_opaque3[4];
	u32 resp_bd_list_addr_lo;
	u32 resp_bd_list_addr_hi;
	u32 resp_buffer;
#घोषणा ISCSI_FW_MP_REQUEST_RESP_BUFFER_LENGTH (0xFFFFFF<<0)
#घोषणा ISCSI_FW_MP_REQUEST_RESP_BUFFER_LENGTH_SHIFT 0
#घोषणा ISCSI_FW_MP_REQUEST_NUM_RESP_BDS (0xFF<<24)
#घोषणा ISCSI_FW_MP_REQUEST_NUM_RESP_BDS_SHIFT 24
#अगर defined(__BIG_ENDIAN)
	u16 reserved4;
	u8 reserved3;
	u8 flags;
#घोषणा ISCSI_FW_MP_REQUEST_RESERVED1 (0x1<<0)
#घोषणा ISCSI_FW_MP_REQUEST_RESERVED1_SHIFT 0
#घोषणा ISCSI_FW_MP_REQUEST_LOCAL_COMPLETION (0x1<<1)
#घोषणा ISCSI_FW_MP_REQUEST_LOCAL_COMPLETION_SHIFT 1
#घोषणा ISCSI_FW_MP_REQUEST_UPDATE_EXP_STAT_SN (0x1<<2)
#घोषणा ISCSI_FW_MP_REQUEST_UPDATE_EXP_STAT_SN_SHIFT 2
#घोषणा ISCSI_FW_MP_REQUEST_RESERVED2 (0x1F<<3)
#घोषणा ISCSI_FW_MP_REQUEST_RESERVED2_SHIFT 3
#या_अगर defined(__LITTLE_ENDIAN)
	u8 flags;
#घोषणा ISCSI_FW_MP_REQUEST_RESERVED1 (0x1<<0)
#घोषणा ISCSI_FW_MP_REQUEST_RESERVED1_SHIFT 0
#घोषणा ISCSI_FW_MP_REQUEST_LOCAL_COMPLETION (0x1<<1)
#घोषणा ISCSI_FW_MP_REQUEST_LOCAL_COMPLETION_SHIFT 1
#घोषणा ISCSI_FW_MP_REQUEST_UPDATE_EXP_STAT_SN (0x1<<2)
#घोषणा ISCSI_FW_MP_REQUEST_UPDATE_EXP_STAT_SN_SHIFT 2
#घोषणा ISCSI_FW_MP_REQUEST_RESERVED2 (0x1F<<3)
#घोषणा ISCSI_FW_MP_REQUEST_RESERVED2_SHIFT 3
	u8 reserved3;
	u16 reserved4;
#पूर्ण_अगर
	u32 bd_list_addr_lo;
	u32 bd_list_addr_hi;
#अगर defined(__BIG_ENDIAN)
	u8 cq_index;
	u8 reserved6;
	u8 reserved5;
	u8 num_bds;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 num_bds;
	u8 reserved5;
	u8 reserved6;
	u8 cq_index;
#पूर्ण_अगर
पूर्ण;


/*
 * firmware response - CQE: used only by firmware
 */
काष्ठा bnx2i_fw_response अणु
	u32 hdr_dword1[2];
	u32 hdr_exp_cmd_sn;
	u32 hdr_max_cmd_sn;
	u32 hdr_ttt;
	u32 hdr_res_cnt;
	u32 cqe_flags;
#घोषणा ISCSI_FW_RESPONSE_RESERVED2 (0xFF<<0)
#घोषणा ISCSI_FW_RESPONSE_RESERVED2_SHIFT 0
#घोषणा ISCSI_FW_RESPONSE_ERR_CODE (0xFF<<8)
#घोषणा ISCSI_FW_RESPONSE_ERR_CODE_SHIFT 8
#घोषणा ISCSI_FW_RESPONSE_RESERVED3 (0xFFFF<<16)
#घोषणा ISCSI_FW_RESPONSE_RESERVED3_SHIFT 16
	u32 stat_sn;
	u32 hdr_dword2[2];
	u32 hdr_dword3[2];
	u32 task_stat;
	u32 reserved0;
	u32 hdr_itt;
	u32 cq_req_sn;
पूर्ण;


/*
 * iSCSI KCQ CQE parameters
 */
जोड़ iscsi_kcqe_params अणु
	u32 reserved0[4];
पूर्ण;

/*
 * iSCSI KCQ CQE
 */
काष्ठा iscsi_kcqe अणु
	u32 iscsi_conn_id;
	u32 completion_status;
	u32 iscsi_conn_context_id;
	जोड़ iscsi_kcqe_params params;
#अगर defined(__BIG_ENDIAN)
	u8 flags;
#घोषणा ISCSI_KCQE_RESERVED0 (0xF<<0)
#घोषणा ISCSI_KCQE_RESERVED0_SHIFT 0
#घोषणा ISCSI_KCQE_LAYER_CODE (0x7<<4)
#घोषणा ISCSI_KCQE_LAYER_CODE_SHIFT 4
#घोषणा ISCSI_KCQE_RESERVED1 (0x1<<7)
#घोषणा ISCSI_KCQE_RESERVED1_SHIFT 7
	u8 op_code;
	u16 qe_self_seq;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 qe_self_seq;
	u8 op_code;
	u8 flags;
#घोषणा ISCSI_KCQE_RESERVED0 (0xF<<0)
#घोषणा ISCSI_KCQE_RESERVED0_SHIFT 0
#घोषणा ISCSI_KCQE_LAYER_CODE (0x7<<4)
#घोषणा ISCSI_KCQE_LAYER_CODE_SHIFT 4
#घोषणा ISCSI_KCQE_RESERVED1 (0x1<<7)
#घोषणा ISCSI_KCQE_RESERVED1_SHIFT 7
#पूर्ण_अगर
पूर्ण;



/*
 * iSCSI KWQE header
 */
काष्ठा iscsi_kwqe_header अणु
#अगर defined(__BIG_ENDIAN)
	u8 flags;
#घोषणा ISCSI_KWQE_HEADER_RESERVED0 (0xF<<0)
#घोषणा ISCSI_KWQE_HEADER_RESERVED0_SHIFT 0
#घोषणा ISCSI_KWQE_HEADER_LAYER_CODE (0x7<<4)
#घोषणा ISCSI_KWQE_HEADER_LAYER_CODE_SHIFT 4
#घोषणा ISCSI_KWQE_HEADER_RESERVED1 (0x1<<7)
#घोषणा ISCSI_KWQE_HEADER_RESERVED1_SHIFT 7
	u8 op_code;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 op_code;
	u8 flags;
#घोषणा ISCSI_KWQE_HEADER_RESERVED0 (0xF<<0)
#घोषणा ISCSI_KWQE_HEADER_RESERVED0_SHIFT 0
#घोषणा ISCSI_KWQE_HEADER_LAYER_CODE (0x7<<4)
#घोषणा ISCSI_KWQE_HEADER_LAYER_CODE_SHIFT 4
#घोषणा ISCSI_KWQE_HEADER_RESERVED1 (0x1<<7)
#घोषणा ISCSI_KWQE_HEADER_RESERVED1_SHIFT 7
#पूर्ण_अगर
पूर्ण;

/*
 * iSCSI firmware init request 1
 */
काष्ठा iscsi_kwqe_init1 अणु
#अगर defined(__BIG_ENDIAN)
	काष्ठा iscsi_kwqe_header hdr;
	u8 reserved0;
	u8 num_cqs;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 num_cqs;
	u8 reserved0;
	काष्ठा iscsi_kwqe_header hdr;
#पूर्ण_अगर
	u32 dummy_buffer_addr_lo;
	u32 dummy_buffer_addr_hi;
#अगर defined(__BIG_ENDIAN)
	u16 num_ccells_per_conn;
	u16 num_tasks_per_conn;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 num_tasks_per_conn;
	u16 num_ccells_per_conn;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u16 sq_wqes_per_page;
	u16 sq_num_wqes;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 sq_num_wqes;
	u16 sq_wqes_per_page;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u8 cq_log_wqes_per_page;
	u8 flags;
#घोषणा ISCSI_KWQE_INIT1_PAGE_SIZE (0xF<<0)
#घोषणा ISCSI_KWQE_INIT1_PAGE_SIZE_SHIFT 0
#घोषणा ISCSI_KWQE_INIT1_DELAYED_ACK_ENABLE (0x1<<4)
#घोषणा ISCSI_KWQE_INIT1_DELAYED_ACK_ENABLE_SHIFT 4
#घोषणा ISCSI_KWQE_INIT1_KEEP_ALIVE_ENABLE (0x1<<5)
#घोषणा ISCSI_KWQE_INIT1_KEEP_ALIVE_ENABLE_SHIFT 5
#घोषणा ISCSI_KWQE_INIT1_TIME_STAMPS_ENABLE (0x1<<6)
#घोषणा ISCSI_KWQE_INIT1_TIME_STAMPS_ENABLE_SHIFT 6
#घोषणा ISCSI_KWQE_INIT1_RESERVED1 (0x1<<7)
#घोषणा ISCSI_KWQE_INIT1_RESERVED1_SHIFT 7
	u16 cq_num_wqes;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 cq_num_wqes;
	u8 flags;
#घोषणा ISCSI_KWQE_INIT1_PAGE_SIZE (0xF<<0)
#घोषणा ISCSI_KWQE_INIT1_PAGE_SIZE_SHIFT 0
#घोषणा ISCSI_KWQE_INIT1_DELAYED_ACK_ENABLE (0x1<<4)
#घोषणा ISCSI_KWQE_INIT1_DELAYED_ACK_ENABLE_SHIFT 4
#घोषणा ISCSI_KWQE_INIT1_KEEP_ALIVE_ENABLE (0x1<<5)
#घोषणा ISCSI_KWQE_INIT1_KEEP_ALIVE_ENABLE_SHIFT 5
#घोषणा ISCSI_KWQE_INIT1_TIME_STAMPS_ENABLE (0x1<<6)
#घोषणा ISCSI_KWQE_INIT1_TIME_STAMPS_ENABLE_SHIFT 6
#घोषणा ISCSI_KWQE_INIT1_RESERVED1 (0x1<<7)
#घोषणा ISCSI_KWQE_INIT1_RESERVED1_SHIFT 7
	u8 cq_log_wqes_per_page;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u16 cq_num_pages;
	u16 sq_num_pages;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 sq_num_pages;
	u16 cq_num_pages;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u16 rq_buffer_size;
	u16 rq_num_wqes;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 rq_num_wqes;
	u16 rq_buffer_size;
#पूर्ण_अगर
पूर्ण;

/*
 * iSCSI firmware init request 2
 */
काष्ठा iscsi_kwqe_init2 अणु
#अगर defined(__BIG_ENDIAN)
	काष्ठा iscsi_kwqe_header hdr;
	u16 max_cq_sqn;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 max_cq_sqn;
	काष्ठा iscsi_kwqe_header hdr;
#पूर्ण_अगर
	u32 error_bit_map[2];
	u32 reserved1[5];
पूर्ण;

/*
 * Initial iSCSI connection offload request 1
 */
काष्ठा iscsi_kwqe_conn_offload1 अणु
#अगर defined(__BIG_ENDIAN)
	काष्ठा iscsi_kwqe_header hdr;
	u16 iscsi_conn_id;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 iscsi_conn_id;
	काष्ठा iscsi_kwqe_header hdr;
#पूर्ण_अगर
	u32 sq_page_table_addr_lo;
	u32 sq_page_table_addr_hi;
	u32 cq_page_table_addr_lo;
	u32 cq_page_table_addr_hi;
	u32 reserved0[3];
पूर्ण;

/*
 * iSCSI Page Table Entry (PTE)
 */
काष्ठा iscsi_pte अणु
	u32 hi;
	u32 lo;
पूर्ण;

/*
 * Initial iSCSI connection offload request 2
 */
काष्ठा iscsi_kwqe_conn_offload2 अणु
#अगर defined(__BIG_ENDIAN)
	काष्ठा iscsi_kwqe_header hdr;
	u16 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved0;
	काष्ठा iscsi_kwqe_header hdr;
#पूर्ण_अगर
	u32 rq_page_table_addr_lo;
	u32 rq_page_table_addr_hi;
	काष्ठा iscsi_pte sq_first_pte;
	काष्ठा iscsi_pte cq_first_pte;
	u32 num_additional_wqes;
पूर्ण;


/*
 * Initial iSCSI connection offload request 3
 */
काष्ठा iscsi_kwqe_conn_offload3 अणु
#अगर defined(__BIG_ENDIAN)
	काष्ठा iscsi_kwqe_header hdr;
	u16 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved0;
	काष्ठा iscsi_kwqe_header hdr;
#पूर्ण_अगर
	u32 reserved1;
	काष्ठा iscsi_pte qp_first_pte[3];
पूर्ण;


/*
 * iSCSI connection update request
 */
काष्ठा iscsi_kwqe_conn_update अणु
#अगर defined(__BIG_ENDIAN)
	काष्ठा iscsi_kwqe_header hdr;
	u16 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved0;
	काष्ठा iscsi_kwqe_header hdr;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u8 session_error_recovery_level;
	u8 max_outstanding_r2ts;
	u8 reserved2;
	u8 conn_flags;
#घोषणा ISCSI_KWQE_CONN_UPDATE_HEADER_DIGEST (0x1<<0)
#घोषणा ISCSI_KWQE_CONN_UPDATE_HEADER_DIGEST_SHIFT 0
#घोषणा ISCSI_KWQE_CONN_UPDATE_DATA_DIGEST (0x1<<1)
#घोषणा ISCSI_KWQE_CONN_UPDATE_DATA_DIGEST_SHIFT 1
#घोषणा ISCSI_KWQE_CONN_UPDATE_INITIAL_R2T (0x1<<2)
#घोषणा ISCSI_KWQE_CONN_UPDATE_INITIAL_R2T_SHIFT 2
#घोषणा ISCSI_KWQE_CONN_UPDATE_IMMEDIATE_DATA (0x1<<3)
#घोषणा ISCSI_KWQE_CONN_UPDATE_IMMEDIATE_DATA_SHIFT 3
#घोषणा ISCSI_KWQE_CONN_UPDATE_OOO_SUPPORT_MODE (0x3<<4)
#घोषणा ISCSI_KWQE_CONN_UPDATE_OOO_SUPPORT_MODE_SHIFT 4
#घोषणा ISCSI_KWQE_CONN_UPDATE_RESERVED1 (0x3<<6)
#घोषणा ISCSI_KWQE_CONN_UPDATE_RESERVED1_SHIFT 6
#या_अगर defined(__LITTLE_ENDIAN)
	u8 conn_flags;
#घोषणा ISCSI_KWQE_CONN_UPDATE_HEADER_DIGEST (0x1<<0)
#घोषणा ISCSI_KWQE_CONN_UPDATE_HEADER_DIGEST_SHIFT 0
#घोषणा ISCSI_KWQE_CONN_UPDATE_DATA_DIGEST (0x1<<1)
#घोषणा ISCSI_KWQE_CONN_UPDATE_DATA_DIGEST_SHIFT 1
#घोषणा ISCSI_KWQE_CONN_UPDATE_INITIAL_R2T (0x1<<2)
#घोषणा ISCSI_KWQE_CONN_UPDATE_INITIAL_R2T_SHIFT 2
#घोषणा ISCSI_KWQE_CONN_UPDATE_IMMEDIATE_DATA (0x1<<3)
#घोषणा ISCSI_KWQE_CONN_UPDATE_IMMEDIATE_DATA_SHIFT 3
#घोषणा ISCSI_KWQE_CONN_UPDATE_OOO_SUPPORT_MODE (0x3<<4)
#घोषणा ISCSI_KWQE_CONN_UPDATE_OOO_SUPPORT_MODE_SHIFT 4
#घोषणा ISCSI_KWQE_CONN_UPDATE_RESERVED1 (0x3<<6)
#घोषणा ISCSI_KWQE_CONN_UPDATE_RESERVED1_SHIFT 6
	u8 reserved2;
	u8 max_outstanding_r2ts;
	u8 session_error_recovery_level;
#पूर्ण_अगर
	u32 context_id;
	u32 max_send_pdu_length;
	u32 max_recv_pdu_length;
	u32 first_burst_length;
	u32 max_burst_length;
	u32 exp_stat_sn;
पूर्ण;

/*
 * iSCSI destroy connection request
 */
काष्ठा iscsi_kwqe_conn_destroy अणु
#अगर defined(__BIG_ENDIAN)
	काष्ठा iscsi_kwqe_header hdr;
	u16 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved0;
	काष्ठा iscsi_kwqe_header hdr;
#पूर्ण_अगर
	u32 context_id;
	u32 reserved1[6];
पूर्ण;

/*
 * iSCSI KWQ WQE
 */
जोड़ iscsi_kwqe अणु
	काष्ठा iscsi_kwqe_init1 init1;
	काष्ठा iscsi_kwqe_init2 init2;
	काष्ठा iscsi_kwqe_conn_offload1 conn_offload1;
	काष्ठा iscsi_kwqe_conn_offload2 conn_offload2;
	काष्ठा iscsi_kwqe_conn_update conn_update;
	काष्ठा iscsi_kwqe_conn_destroy conn_destroy;
पूर्ण;

/*
 * iSCSI Login SQ WQE
 */
काष्ठा bnx2i_login_request अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 op_attr;
#घोषणा ISCSI_LOGIN_REQUEST_NEXT_STAGE (0x3<<0)
#घोषणा ISCSI_LOGIN_REQUEST_NEXT_STAGE_SHIFT 0
#घोषणा ISCSI_LOGIN_REQUEST_CURRENT_STAGE (0x3<<2)
#घोषणा ISCSI_LOGIN_REQUEST_CURRENT_STAGE_SHIFT 2
#घोषणा ISCSI_LOGIN_REQUEST_RESERVED0 (0x3<<4)
#घोषणा ISCSI_LOGIN_REQUEST_RESERVED0_SHIFT 4
#घोषणा ISCSI_LOGIN_REQUEST_CONT (0x1<<6)
#घोषणा ISCSI_LOGIN_REQUEST_CONT_SHIFT 6
#घोषणा ISCSI_LOGIN_REQUEST_TRANSIT (0x1<<7)
#घोषणा ISCSI_LOGIN_REQUEST_TRANSIT_SHIFT 7
	u8 version_max;
	u8 version_min;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 version_min;
	u8 version_max;
	u8 op_attr;
#घोषणा ISCSI_LOGIN_REQUEST_NEXT_STAGE (0x3<<0)
#घोषणा ISCSI_LOGIN_REQUEST_NEXT_STAGE_SHIFT 0
#घोषणा ISCSI_LOGIN_REQUEST_CURRENT_STAGE (0x3<<2)
#घोषणा ISCSI_LOGIN_REQUEST_CURRENT_STAGE_SHIFT 2
#घोषणा ISCSI_LOGIN_REQUEST_RESERVED0 (0x3<<4)
#घोषणा ISCSI_LOGIN_REQUEST_RESERVED0_SHIFT 4
#घोषणा ISCSI_LOGIN_REQUEST_CONT (0x1<<6)
#घोषणा ISCSI_LOGIN_REQUEST_CONT_SHIFT 6
#घोषणा ISCSI_LOGIN_REQUEST_TRANSIT (0x1<<7)
#घोषणा ISCSI_LOGIN_REQUEST_TRANSIT_SHIFT 7
	u8 op_code;
#पूर्ण_अगर
	u32 data_length;
	u32 isid_lo;
#अगर defined(__BIG_ENDIAN)
	u16 isid_hi;
	u16 tsih;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 tsih;
	u16 isid_hi;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u16 reserved2;
	u16 itt;
#घोषणा ISCSI_LOGIN_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_LOGIN_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_LOGIN_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_LOGIN_REQUEST_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_LOGIN_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_LOGIN_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_LOGIN_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_LOGIN_REQUEST_TYPE_SHIFT 14
	u16 reserved2;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u16 cid;
	u16 reserved3;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved3;
	u16 cid;
#पूर्ण_अगर
	u32 cmd_sn;
	u32 exp_stat_sn;
	u32 reserved4;
	u32 resp_bd_list_addr_lo;
	u32 resp_bd_list_addr_hi;
	u32 resp_buffer;
#घोषणा ISCSI_LOGIN_REQUEST_RESP_BUFFER_LENGTH (0xFFFFFF<<0)
#घोषणा ISCSI_LOGIN_REQUEST_RESP_BUFFER_LENGTH_SHIFT 0
#घोषणा ISCSI_LOGIN_REQUEST_NUM_RESP_BDS (0xFF<<24)
#घोषणा ISCSI_LOGIN_REQUEST_NUM_RESP_BDS_SHIFT 24
#अगर defined(__BIG_ENDIAN)
	u16 reserved8;
	u8 reserved7;
	u8 flags;
#घोषणा ISCSI_LOGIN_REQUEST_RESERVED5 (0x3<<0)
#घोषणा ISCSI_LOGIN_REQUEST_RESERVED5_SHIFT 0
#घोषणा ISCSI_LOGIN_REQUEST_UPDATE_EXP_STAT_SN (0x1<<2)
#घोषणा ISCSI_LOGIN_REQUEST_UPDATE_EXP_STAT_SN_SHIFT 2
#घोषणा ISCSI_LOGIN_REQUEST_RESERVED6 (0x1F<<3)
#घोषणा ISCSI_LOGIN_REQUEST_RESERVED6_SHIFT 3
#या_अगर defined(__LITTLE_ENDIAN)
	u8 flags;
#घोषणा ISCSI_LOGIN_REQUEST_RESERVED5 (0x3<<0)
#घोषणा ISCSI_LOGIN_REQUEST_RESERVED5_SHIFT 0
#घोषणा ISCSI_LOGIN_REQUEST_UPDATE_EXP_STAT_SN (0x1<<2)
#घोषणा ISCSI_LOGIN_REQUEST_UPDATE_EXP_STAT_SN_SHIFT 2
#घोषणा ISCSI_LOGIN_REQUEST_RESERVED6 (0x1F<<3)
#घोषणा ISCSI_LOGIN_REQUEST_RESERVED6_SHIFT 3
	u8 reserved7;
	u16 reserved8;
#पूर्ण_अगर
	u32 bd_list_addr_lo;
	u32 bd_list_addr_hi;
#अगर defined(__BIG_ENDIAN)
	u8 cq_index;
	u8 reserved10;
	u8 reserved9;
	u8 num_bds;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 num_bds;
	u8 reserved9;
	u8 reserved10;
	u8 cq_index;
#पूर्ण_अगर
पूर्ण;


/*
 * iSCSI Login CQE
 */
काष्ठा bnx2i_login_response अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 response_flags;
#घोषणा ISCSI_LOGIN_RESPONSE_NEXT_STAGE (0x3<<0)
#घोषणा ISCSI_LOGIN_RESPONSE_NEXT_STAGE_SHIFT 0
#घोषणा ISCSI_LOGIN_RESPONSE_CURRENT_STAGE (0x3<<2)
#घोषणा ISCSI_LOGIN_RESPONSE_CURRENT_STAGE_SHIFT 2
#घोषणा ISCSI_LOGIN_RESPONSE_RESERVED0 (0x3<<4)
#घोषणा ISCSI_LOGIN_RESPONSE_RESERVED0_SHIFT 4
#घोषणा ISCSI_LOGIN_RESPONSE_CONT (0x1<<6)
#घोषणा ISCSI_LOGIN_RESPONSE_CONT_SHIFT 6
#घोषणा ISCSI_LOGIN_RESPONSE_TRANSIT (0x1<<7)
#घोषणा ISCSI_LOGIN_RESPONSE_TRANSIT_SHIFT 7
	u8 version_max;
	u8 version_active;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 version_active;
	u8 version_max;
	u8 response_flags;
#घोषणा ISCSI_LOGIN_RESPONSE_NEXT_STAGE (0x3<<0)
#घोषणा ISCSI_LOGIN_RESPONSE_NEXT_STAGE_SHIFT 0
#घोषणा ISCSI_LOGIN_RESPONSE_CURRENT_STAGE (0x3<<2)
#घोषणा ISCSI_LOGIN_RESPONSE_CURRENT_STAGE_SHIFT 2
#घोषणा ISCSI_LOGIN_RESPONSE_RESERVED0 (0x3<<4)
#घोषणा ISCSI_LOGIN_RESPONSE_RESERVED0_SHIFT 4
#घोषणा ISCSI_LOGIN_RESPONSE_CONT (0x1<<6)
#घोषणा ISCSI_LOGIN_RESPONSE_CONT_SHIFT 6
#घोषणा ISCSI_LOGIN_RESPONSE_TRANSIT (0x1<<7)
#घोषणा ISCSI_LOGIN_RESPONSE_TRANSIT_SHIFT 7
	u8 op_code;
#पूर्ण_अगर
	u32 data_length;
	u32 exp_cmd_sn;
	u32 max_cmd_sn;
	u32 reserved1[2];
#अगर defined(__BIG_ENDIAN)
	u16 reserved3;
	u8 err_code;
	u8 reserved2;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 reserved2;
	u8 err_code;
	u16 reserved3;
#पूर्ण_अगर
	u32 stat_sn;
	u32 isid_lo;
#अगर defined(__BIG_ENDIAN)
	u16 isid_hi;
	u16 tsih;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 tsih;
	u16 isid_hi;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u8 status_class;
	u8 status_detail;
	u16 reserved4;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved4;
	u8 status_detail;
	u8 status_class;
#पूर्ण_अगर
	u32 reserved5[3];
#अगर defined(__BIG_ENDIAN)
	u16 reserved6;
	u16 itt;
#घोषणा ISCSI_LOGIN_RESPONSE_INDEX (0x3FFF<<0)
#घोषणा ISCSI_LOGIN_RESPONSE_INDEX_SHIFT 0
#घोषणा ISCSI_LOGIN_RESPONSE_TYPE (0x3<<14)
#घोषणा ISCSI_LOGIN_RESPONSE_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_LOGIN_RESPONSE_INDEX (0x3FFF<<0)
#घोषणा ISCSI_LOGIN_RESPONSE_INDEX_SHIFT 0
#घोषणा ISCSI_LOGIN_RESPONSE_TYPE (0x3<<14)
#घोषणा ISCSI_LOGIN_RESPONSE_TYPE_SHIFT 14
	u16 reserved6;
#पूर्ण_अगर
	u32 cq_req_sn;
पूर्ण;


/*
 * iSCSI Logout SQ WQE
 */
काष्ठा bnx2i_logout_request अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 op_attr;
#घोषणा ISCSI_LOGOUT_REQUEST_REASON (0x7F<<0)
#घोषणा ISCSI_LOGOUT_REQUEST_REASON_SHIFT 0
#घोषणा ISCSI_LOGOUT_REQUEST_ALWAYS_ONE (0x1<<7)
#घोषणा ISCSI_LOGOUT_REQUEST_ALWAYS_ONE_SHIFT 7
	u16 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved0;
	u8 op_attr;
#घोषणा ISCSI_LOGOUT_REQUEST_REASON (0x7F<<0)
#घोषणा ISCSI_LOGOUT_REQUEST_REASON_SHIFT 0
#घोषणा ISCSI_LOGOUT_REQUEST_ALWAYS_ONE (0x1<<7)
#घोषणा ISCSI_LOGOUT_REQUEST_ALWAYS_ONE_SHIFT 7
	u8 op_code;
#पूर्ण_अगर
	u32 data_length;
	u32 reserved1[2];
#अगर defined(__BIG_ENDIAN)
	u16 reserved2;
	u16 itt;
#घोषणा ISCSI_LOGOUT_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_LOGOUT_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_LOGOUT_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_LOGOUT_REQUEST_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_LOGOUT_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_LOGOUT_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_LOGOUT_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_LOGOUT_REQUEST_TYPE_SHIFT 14
	u16 reserved2;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u16 cid;
	u16 reserved3;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved3;
	u16 cid;
#पूर्ण_अगर
	u32 cmd_sn;
	u32 reserved4[5];
	u32 zero_fill;
	u32 bd_list_addr_lo;
	u32 bd_list_addr_hi;
#अगर defined(__BIG_ENDIAN)
	u8 cq_index;
	u8 reserved6;
	u8 reserved5;
	u8 num_bds;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 num_bds;
	u8 reserved5;
	u8 reserved6;
	u8 cq_index;
#पूर्ण_अगर
पूर्ण;


/*
 * iSCSI Logout CQE
 */
काष्ठा bnx2i_logout_response अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 reserved1;
	u8 response;
	u8 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 reserved0;
	u8 response;
	u8 reserved1;
	u8 op_code;
#पूर्ण_अगर
	u32 reserved2;
	u32 exp_cmd_sn;
	u32 max_cmd_sn;
	u32 reserved3[2];
#अगर defined(__BIG_ENDIAN)
	u16 reserved5;
	u8 err_code;
	u8 reserved4;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 reserved4;
	u8 err_code;
	u16 reserved5;
#पूर्ण_अगर
	u32 reserved6[3];
#अगर defined(__BIG_ENDIAN)
	u16 समय_प्रकारo_रुको;
	u16 समय_प्रकारo_retain;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 समय_प्रकारo_retain;
	u16 समय_प्रकारo_रुको;
#पूर्ण_अगर
	u32 reserved7[3];
#अगर defined(__BIG_ENDIAN)
	u16 reserved8;
	u16 itt;
#घोषणा ISCSI_LOGOUT_RESPONSE_INDEX (0x3FFF<<0)
#घोषणा ISCSI_LOGOUT_RESPONSE_INDEX_SHIFT 0
#घोषणा ISCSI_LOGOUT_RESPONSE_TYPE (0x3<<14)
#घोषणा ISCSI_LOGOUT_RESPONSE_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_LOGOUT_RESPONSE_INDEX (0x3FFF<<0)
#घोषणा ISCSI_LOGOUT_RESPONSE_INDEX_SHIFT 0
#घोषणा ISCSI_LOGOUT_RESPONSE_TYPE (0x3<<14)
#घोषणा ISCSI_LOGOUT_RESPONSE_TYPE_SHIFT 14
	u16 reserved8;
#पूर्ण_अगर
	u32 cq_req_sn;
पूर्ण;


/*
 * iSCSI Nop-In CQE
 */
काष्ठा bnx2i_nop_in_msg अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 reserved1;
	u16 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved0;
	u8 reserved1;
	u8 op_code;
#पूर्ण_अगर
	u32 data_length;
	u32 exp_cmd_sn;
	u32 max_cmd_sn;
	u32 ttt;
	u32 reserved2;
#अगर defined(__BIG_ENDIAN)
	u16 reserved4;
	u8 err_code;
	u8 reserved3;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 reserved3;
	u8 err_code;
	u16 reserved4;
#पूर्ण_अगर
	u32 reserved5;
	u32 lun[2];
	u32 reserved6[4];
#अगर defined(__BIG_ENDIAN)
	u16 reserved7;
	u16 itt;
#घोषणा ISCSI_NOP_IN_MSG_INDEX (0x3FFF<<0)
#घोषणा ISCSI_NOP_IN_MSG_INDEX_SHIFT 0
#घोषणा ISCSI_NOP_IN_MSG_TYPE (0x3<<14)
#घोषणा ISCSI_NOP_IN_MSG_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_NOP_IN_MSG_INDEX (0x3FFF<<0)
#घोषणा ISCSI_NOP_IN_MSG_INDEX_SHIFT 0
#घोषणा ISCSI_NOP_IN_MSG_TYPE (0x3<<14)
#घोषणा ISCSI_NOP_IN_MSG_TYPE_SHIFT 14
	u16 reserved7;
#पूर्ण_अगर
	u32 cq_req_sn;
पूर्ण;


/*
 * iSCSI NOP-OUT SQ WQE
 */
काष्ठा bnx2i_nop_out_request अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 op_attr;
#घोषणा ISCSI_NOP_OUT_REQUEST_RESERVED1 (0x7F<<0)
#घोषणा ISCSI_NOP_OUT_REQUEST_RESERVED1_SHIFT 0
#घोषणा ISCSI_NOP_OUT_REQUEST_ALWAYS_ONE (0x1<<7)
#घोषणा ISCSI_NOP_OUT_REQUEST_ALWAYS_ONE_SHIFT 7
	u16 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved0;
	u8 op_attr;
#घोषणा ISCSI_NOP_OUT_REQUEST_RESERVED1 (0x7F<<0)
#घोषणा ISCSI_NOP_OUT_REQUEST_RESERVED1_SHIFT 0
#घोषणा ISCSI_NOP_OUT_REQUEST_ALWAYS_ONE (0x1<<7)
#घोषणा ISCSI_NOP_OUT_REQUEST_ALWAYS_ONE_SHIFT 7
	u8 op_code;
#पूर्ण_अगर
	u32 data_length;
	u32 lun[2];
#अगर defined(__BIG_ENDIAN)
	u16 reserved2;
	u16 itt;
#घोषणा ISCSI_NOP_OUT_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_NOP_OUT_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_NOP_OUT_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_NOP_OUT_REQUEST_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_NOP_OUT_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_NOP_OUT_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_NOP_OUT_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_NOP_OUT_REQUEST_TYPE_SHIFT 14
	u16 reserved2;
#पूर्ण_अगर
	u32 ttt;
	u32 cmd_sn;
	u32 reserved3[2];
	u32 resp_bd_list_addr_lo;
	u32 resp_bd_list_addr_hi;
	u32 resp_buffer;
#घोषणा ISCSI_NOP_OUT_REQUEST_RESP_BUFFER_LENGTH (0xFFFFFF<<0)
#घोषणा ISCSI_NOP_OUT_REQUEST_RESP_BUFFER_LENGTH_SHIFT 0
#घोषणा ISCSI_NOP_OUT_REQUEST_NUM_RESP_BDS (0xFF<<24)
#घोषणा ISCSI_NOP_OUT_REQUEST_NUM_RESP_BDS_SHIFT 24
#अगर defined(__BIG_ENDIAN)
	u16 reserved7;
	u8 reserved6;
	u8 flags;
#घोषणा ISCSI_NOP_OUT_REQUEST_RESERVED4 (0x1<<0)
#घोषणा ISCSI_NOP_OUT_REQUEST_RESERVED4_SHIFT 0
#घोषणा ISCSI_NOP_OUT_REQUEST_LOCAL_COMPLETION (0x1<<1)
#घोषणा ISCSI_NOP_OUT_REQUEST_LOCAL_COMPLETION_SHIFT 1
#घोषणा ISCSI_NOP_OUT_REQUEST_ZERO_FILL (0x3F<<2)
#घोषणा ISCSI_NOP_OUT_REQUEST_ZERO_FILL_SHIFT 2
#या_अगर defined(__LITTLE_ENDIAN)
	u8 flags;
#घोषणा ISCSI_NOP_OUT_REQUEST_RESERVED4 (0x1<<0)
#घोषणा ISCSI_NOP_OUT_REQUEST_RESERVED4_SHIFT 0
#घोषणा ISCSI_NOP_OUT_REQUEST_LOCAL_COMPLETION (0x1<<1)
#घोषणा ISCSI_NOP_OUT_REQUEST_LOCAL_COMPLETION_SHIFT 1
#घोषणा ISCSI_NOP_OUT_REQUEST_ZERO_FILL (0x3F<<2)
#घोषणा ISCSI_NOP_OUT_REQUEST_ZERO_FILL_SHIFT 2
	u8 reserved6;
	u16 reserved7;
#पूर्ण_अगर
	u32 bd_list_addr_lo;
	u32 bd_list_addr_hi;
#अगर defined(__BIG_ENDIAN)
	u8 cq_index;
	u8 reserved9;
	u8 reserved8;
	u8 num_bds;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 num_bds;
	u8 reserved8;
	u8 reserved9;
	u8 cq_index;
#पूर्ण_अगर
पूर्ण;

/*
 * iSCSI Reject CQE
 */
काष्ठा bnx2i_reject_msg अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 reserved1;
	u8 reason;
	u8 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 reserved0;
	u8 reason;
	u8 reserved1;
	u8 op_code;
#पूर्ण_अगर
	u32 data_length;
	u32 exp_cmd_sn;
	u32 max_cmd_sn;
	u32 reserved2[2];
#अगर defined(__BIG_ENDIAN)
	u16 reserved4;
	u8 err_code;
	u8 reserved3;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 reserved3;
	u8 err_code;
	u16 reserved4;
#पूर्ण_अगर
	u32 reserved5[8];
	u32 cq_req_sn;
पूर्ण;

/*
 * bnx2i iSCSI TMF SQ WQE
 */
काष्ठा bnx2i_पंचांगf_request अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 op_attr;
#घोषणा ISCSI_TMF_REQUEST_FUNCTION (0x7F<<0)
#घोषणा ISCSI_TMF_REQUEST_FUNCTION_SHIFT 0
#घोषणा ISCSI_TMF_REQUEST_ALWAYS_ONE (0x1<<7)
#घोषणा ISCSI_TMF_REQUEST_ALWAYS_ONE_SHIFT 7
	u16 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved0;
	u8 op_attr;
#घोषणा ISCSI_TMF_REQUEST_FUNCTION (0x7F<<0)
#घोषणा ISCSI_TMF_REQUEST_FUNCTION_SHIFT 0
#घोषणा ISCSI_TMF_REQUEST_ALWAYS_ONE (0x1<<7)
#घोषणा ISCSI_TMF_REQUEST_ALWAYS_ONE_SHIFT 7
	u8 op_code;
#पूर्ण_अगर
	u32 data_length;
	u32 lun[2];
#अगर defined(__BIG_ENDIAN)
	u16 reserved1;
	u16 itt;
#घोषणा ISCSI_TMF_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_TMF_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_TMF_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_TMF_REQUEST_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_TMF_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_TMF_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_TMF_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_TMF_REQUEST_TYPE_SHIFT 14
	u16 reserved1;
#पूर्ण_अगर
	u32 ref_itt;
	u32 cmd_sn;
	u32 reserved2;
	u32 ref_cmd_sn;
	u32 reserved3[3];
	u32 zero_fill;
	u32 bd_list_addr_lo;
	u32 bd_list_addr_hi;
#अगर defined(__BIG_ENDIAN)
	u8 cq_index;
	u8 reserved5;
	u8 reserved4;
	u8 num_bds;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 num_bds;
	u8 reserved4;
	u8 reserved5;
	u8 cq_index;
#पूर्ण_अगर
पूर्ण;

/*
 * iSCSI Text SQ WQE
 */
काष्ठा bnx2i_text_request अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 op_attr;
#घोषणा ISCSI_TEXT_REQUEST_RESERVED1 (0x3F<<0)
#घोषणा ISCSI_TEXT_REQUEST_RESERVED1_SHIFT 0
#घोषणा ISCSI_TEXT_REQUEST_CONT (0x1<<6)
#घोषणा ISCSI_TEXT_REQUEST_CONT_SHIFT 6
#घोषणा ISCSI_TEXT_REQUEST_FINAL (0x1<<7)
#घोषणा ISCSI_TEXT_REQUEST_FINAL_SHIFT 7
	u16 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved0;
	u8 op_attr;
#घोषणा ISCSI_TEXT_REQUEST_RESERVED1 (0x3F<<0)
#घोषणा ISCSI_TEXT_REQUEST_RESERVED1_SHIFT 0
#घोषणा ISCSI_TEXT_REQUEST_CONT (0x1<<6)
#घोषणा ISCSI_TEXT_REQUEST_CONT_SHIFT 6
#घोषणा ISCSI_TEXT_REQUEST_FINAL (0x1<<7)
#घोषणा ISCSI_TEXT_REQUEST_FINAL_SHIFT 7
	u8 op_code;
#पूर्ण_अगर
	u32 data_length;
	u32 lun[2];
#अगर defined(__BIG_ENDIAN)
	u16 reserved3;
	u16 itt;
#घोषणा ISCSI_TEXT_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_TEXT_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_TEXT_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_TEXT_REQUEST_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_TEXT_REQUEST_INDEX (0x3FFF<<0)
#घोषणा ISCSI_TEXT_REQUEST_INDEX_SHIFT 0
#घोषणा ISCSI_TEXT_REQUEST_TYPE (0x3<<14)
#घोषणा ISCSI_TEXT_REQUEST_TYPE_SHIFT 14
	u16 reserved3;
#पूर्ण_अगर
	u32 ttt;
	u32 cmd_sn;
	u32 reserved4[2];
	u32 resp_bd_list_addr_lo;
	u32 resp_bd_list_addr_hi;
	u32 resp_buffer;
#घोषणा ISCSI_TEXT_REQUEST_RESP_BUFFER_LENGTH (0xFFFFFF<<0)
#घोषणा ISCSI_TEXT_REQUEST_RESP_BUFFER_LENGTH_SHIFT 0
#घोषणा ISCSI_TEXT_REQUEST_NUM_RESP_BDS (0xFF<<24)
#घोषणा ISCSI_TEXT_REQUEST_NUM_RESP_BDS_SHIFT 24
	u32 zero_fill;
	u32 bd_list_addr_lo;
	u32 bd_list_addr_hi;
#अगर defined(__BIG_ENDIAN)
	u8 cq_index;
	u8 reserved7;
	u8 reserved6;
	u8 num_bds;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 num_bds;
	u8 reserved6;
	u8 reserved7;
	u8 cq_index;
#पूर्ण_अगर
पूर्ण;

/*
 * iSCSI SQ WQE
 */
जोड़ iscsi_request अणु
	काष्ठा bnx2i_cmd_request cmd;
	काष्ठा bnx2i_पंचांगf_request पंचांगf;
	काष्ठा bnx2i_nop_out_request nop_out;
	काष्ठा bnx2i_login_request login_req;
	काष्ठा bnx2i_text_request text;
	काष्ठा bnx2i_logout_request logout_req;
	काष्ठा bnx2i_cleanup_request cleanup;
पूर्ण;


/*
 * iSCSI TMF CQE
 */
काष्ठा bnx2i_पंचांगf_response अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 reserved1;
	u8 response;
	u8 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 reserved0;
	u8 response;
	u8 reserved1;
	u8 op_code;
#पूर्ण_अगर
	u32 reserved2;
	u32 exp_cmd_sn;
	u32 max_cmd_sn;
	u32 reserved3[2];
#अगर defined(__BIG_ENDIAN)
	u16 reserved5;
	u8 err_code;
	u8 reserved4;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 reserved4;
	u8 err_code;
	u16 reserved5;
#पूर्ण_अगर
	u32 reserved6[7];
#अगर defined(__BIG_ENDIAN)
	u16 reserved7;
	u16 itt;
#घोषणा ISCSI_TMF_RESPONSE_INDEX (0x3FFF<<0)
#घोषणा ISCSI_TMF_RESPONSE_INDEX_SHIFT 0
#घोषणा ISCSI_TMF_RESPONSE_TYPE (0x3<<14)
#घोषणा ISCSI_TMF_RESPONSE_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_TMF_RESPONSE_INDEX (0x3FFF<<0)
#घोषणा ISCSI_TMF_RESPONSE_INDEX_SHIFT 0
#घोषणा ISCSI_TMF_RESPONSE_TYPE (0x3<<14)
#घोषणा ISCSI_TMF_RESPONSE_TYPE_SHIFT 14
	u16 reserved7;
#पूर्ण_अगर
	u32 cq_req_sn;
पूर्ण;

/*
 * iSCSI Text CQE
 */
काष्ठा bnx2i_text_response अणु
#अगर defined(__BIG_ENDIAN)
	u8 op_code;
	u8 response_flags;
#घोषणा ISCSI_TEXT_RESPONSE_RESERVED1 (0x3F<<0)
#घोषणा ISCSI_TEXT_RESPONSE_RESERVED1_SHIFT 0
#घोषणा ISCSI_TEXT_RESPONSE_CONT (0x1<<6)
#घोषणा ISCSI_TEXT_RESPONSE_CONT_SHIFT 6
#घोषणा ISCSI_TEXT_RESPONSE_FINAL (0x1<<7)
#घोषणा ISCSI_TEXT_RESPONSE_FINAL_SHIFT 7
	u16 reserved0;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved0;
	u8 response_flags;
#घोषणा ISCSI_TEXT_RESPONSE_RESERVED1 (0x3F<<0)
#घोषणा ISCSI_TEXT_RESPONSE_RESERVED1_SHIFT 0
#घोषणा ISCSI_TEXT_RESPONSE_CONT (0x1<<6)
#घोषणा ISCSI_TEXT_RESPONSE_CONT_SHIFT 6
#घोषणा ISCSI_TEXT_RESPONSE_FINAL (0x1<<7)
#घोषणा ISCSI_TEXT_RESPONSE_FINAL_SHIFT 7
	u8 op_code;
#पूर्ण_अगर
	u32 data_length;
	u32 exp_cmd_sn;
	u32 max_cmd_sn;
	u32 ttt;
	u32 reserved2;
#अगर defined(__BIG_ENDIAN)
	u16 reserved4;
	u8 err_code;
	u8 reserved3;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 reserved3;
	u8 err_code;
	u16 reserved4;
#पूर्ण_अगर
	u32 reserved5;
	u32 lun[2];
	u32 reserved6[4];
#अगर defined(__BIG_ENDIAN)
	u16 reserved7;
	u16 itt;
#घोषणा ISCSI_TEXT_RESPONSE_INDEX (0x3FFF<<0)
#घोषणा ISCSI_TEXT_RESPONSE_INDEX_SHIFT 0
#घोषणा ISCSI_TEXT_RESPONSE_TYPE (0x3<<14)
#घोषणा ISCSI_TEXT_RESPONSE_TYPE_SHIFT 14
#या_अगर defined(__LITTLE_ENDIAN)
	u16 itt;
#घोषणा ISCSI_TEXT_RESPONSE_INDEX (0x3FFF<<0)
#घोषणा ISCSI_TEXT_RESPONSE_INDEX_SHIFT 0
#घोषणा ISCSI_TEXT_RESPONSE_TYPE (0x3<<14)
#घोषणा ISCSI_TEXT_RESPONSE_TYPE_SHIFT 14
	u16 reserved7;
#पूर्ण_अगर
	u32 cq_req_sn;
पूर्ण;

/*
 * iSCSI CQE
 */
जोड़ iscsi_response अणु
	काष्ठा bnx2i_cmd_response cmd;
	काष्ठा bnx2i_पंचांगf_response पंचांगf;
	काष्ठा bnx2i_login_response login_resp;
	काष्ठा bnx2i_text_response text;
	काष्ठा bnx2i_logout_response logout_resp;
	काष्ठा bnx2i_cleanup_response cleanup;
	काष्ठा bnx2i_reject_msg reject;
	काष्ठा bnx2i_async_msg async;
	काष्ठा bnx2i_nop_in_msg nop_in;
पूर्ण;

#पूर्ण_अगर /* __57XX_ISCSI_HSI_LINUX_LE__ */
