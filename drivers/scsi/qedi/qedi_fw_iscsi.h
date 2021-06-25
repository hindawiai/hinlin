<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI Offload Driver
 * Copyright (c) 2016 Cavium Inc.
 */

#अगर_अघोषित _QEDI_FW_ISCSI_H_
#घोषणा _QEDI_FW_ISCSI_H_

#समावेश "qedi_fw_scsi.h"

काष्ठा iscsi_task_params अणु
	काष्ठा e4_iscsi_task_context *context;
	काष्ठा iscsi_wqe	  *sqe;
	u32			  tx_io_size;
	u32			  rx_io_size;
	u16			  conn_icid;
	u16			  itid;
	u8			  cq_rss_number;
पूर्ण;

काष्ठा iscsi_conn_params अणु
	u32	first_burst_length;
	u32	max_send_pdu_length;
	u32	max_burst_length;
	bool	initial_r2t;
	bool	immediate_data;
पूर्ण;

/* @brief init_initiator_पढ़ो_iscsi_task - initializes iSCSI Initiator Read
 * task context.
 *
 * @param task_params	  - Poपूर्णांकer to task parameters काष्ठा
 * @param conn_params	  - Connection Parameters
 * @param cmd_params	  - command specअगरic parameters
 * @param cmd_pdu_header  - PDU Header Parameters
 * @param sgl_task_params - Poपूर्णांकer to SGL task params
 * @param dअगर_task_params - Poपूर्णांकer to DIF parameters काष्ठा
 */
पूर्णांक init_initiator_rw_iscsi_task(काष्ठा iscsi_task_params *task_params,
				 काष्ठा iscsi_conn_params *conn_params,
				 काष्ठा scsi_initiator_cmd_params *cmd_params,
				 काष्ठा iscsi_cmd_hdr *cmd_pdu_header,
				 काष्ठा scsi_sgl_task_params *tx_sgl_params,
				 काष्ठा scsi_sgl_task_params *rx_sgl_params,
				 काष्ठा scsi_dअगर_task_params *dअगर_task_params);

/* @brief init_initiator_login_request_task - initializes iSCSI Initiator Login
 * Request task context.
 *
 * @param task_params		  - Poपूर्णांकer to task parameters काष्ठा
 * @param login_req_pdu_header    - PDU Header Parameters
 * @param tx_sgl_task_params	  - Poपूर्णांकer to SGL task params
 * @param rx_sgl_task_params	  - Poपूर्णांकer to SGL task params
 */
पूर्णांक init_initiator_login_request_task(काष्ठा iscsi_task_params *task_params,
				      काष्ठा iscsi_login_req_hdr *login_header,
				      काष्ठा scsi_sgl_task_params *tx_params,
				      काष्ठा scsi_sgl_task_params *rx_params);

/* @brief init_initiator_nop_out_task - initializes iSCSI Initiator NOP Out
 * task context.
 *
 * @param task_params		- Poपूर्णांकer to task parameters काष्ठा
 * @param nop_out_pdu_header    - PDU Header Parameters
 * @param tx_sgl_task_params	- Poपूर्णांकer to SGL task params
 * @param rx_sgl_task_params	- Poपूर्णांकer to SGL task params
 */
पूर्णांक init_initiator_nop_out_task(काष्ठा iscsi_task_params *task_params,
				काष्ठा iscsi_nop_out_hdr *nop_out_pdu_header,
				काष्ठा scsi_sgl_task_params *tx_sgl_params,
				काष्ठा scsi_sgl_task_params *rx_sgl_params);

/* @brief init_initiator_logout_request_task - initializes iSCSI Initiator
 * Logout Request task context.
 *
 * @param task_params		- Poपूर्णांकer to task parameters काष्ठा
 * @param logout_pdu_header  - PDU Header Parameters
 * @param tx_sgl_task_params	- Poपूर्णांकer to SGL task params
 * @param rx_sgl_task_params	- Poपूर्णांकer to SGL task params
 */
पूर्णांक init_initiator_logout_request_task(काष्ठा iscsi_task_params *task_params,
				       काष्ठा iscsi_logout_req_hdr *logout_hdr,
				       काष्ठा scsi_sgl_task_params *tx_params,
				       काष्ठा scsi_sgl_task_params *rx_params);

/* @brief init_initiator_पंचांगf_request_task - initializes iSCSI Initiator TMF
 * task context.
 *
 * @param task_params	- Poपूर्णांकer to task parameters काष्ठा
 * @param पंचांगf_pdu_header - PDU Header Parameters
 */
पूर्णांक init_initiator_पंचांगf_request_task(काष्ठा iscsi_task_params *task_params,
				    काष्ठा iscsi_पंचांगf_request_hdr *पंचांगf_header);

/* @brief init_initiator_text_request_task - initializes iSCSI Initiator Text
 * Request task context.
 *
 * @param task_params		     - Poपूर्णांकer to task parameters काष्ठा
 * @param text_request_pdu_header    - PDU Header Parameters
 * @param tx_sgl_task_params	     - Poपूर्णांकer to Tx SGL task params
 * @param rx_sgl_task_params	     - Poपूर्णांकer to Rx SGL task params
 */
पूर्णांक init_initiator_text_request_task(काष्ठा iscsi_task_params *task_params,
				     काष्ठा iscsi_text_request_hdr *text_header,
				     काष्ठा scsi_sgl_task_params *tx_params,
				     काष्ठा scsi_sgl_task_params *rx_params);

/* @brief init_cleanup_task - initializes Clean task (SQE)
 *
 * @param task_params - Poपूर्णांकer to task parameters काष्ठा
 */
पूर्णांक init_cleanup_task(काष्ठा iscsi_task_params *task_params);
#पूर्ण_अगर
