<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* QLogic FCoE Offload Driver
 * Copyright (c) 2016-2018 Cavium Inc.
 */
#अगर_अघोषित _FCOE_FW_FUNCS_H
#घोषणा _FCOE_FW_FUNCS_H
#समावेश "drv_scsi_fw_funcs.h"
#समावेश "qedf_hsi.h"
#समावेश <linux/qed/qed_अगर.h>

काष्ठा fcoe_task_params अणु
	/* Output parameter [set/filled by the HSI function] */
	काष्ठा e4_fcoe_task_context *context;

	/* Output parameter [set/filled by the HSI function] */
	काष्ठा fcoe_wqe *sqe;
	क्रमागत fcoe_task_type task_type;
	u32 tx_io_size; /* in bytes */
	u32 rx_io_size; /* in bytes */
	u32 conn_cid;
	u16 itid;
	u8 cq_rss_number;

	 /* Whether it's Tape device or not (0=Disk, 1=Tape) */
	u8 is_tape_device;
पूर्ण;

/**
 * @brief init_initiator_rw_fcoe_task - Initializes FCoE task context क्रम
 * पढ़ो/ग_लिखो task types and init fcoe_sqe
 *
 * @param task_params - Poपूर्णांकer to task parameters काष्ठा
 * @param sgl_task_params - Poपूर्णांकer to SGL task params
 * @param sense_data_buffer_phys_addr - Poपूर्णांकer to sense data buffer
 * @param task_retry_id - retry identअगरication - Used only क्रम Tape device
 * @param fcp_cmnd_payload - FCP CMD Payload
 */
पूर्णांक init_initiator_rw_fcoe_task(काष्ठा fcoe_task_params *task_params,
	काष्ठा scsi_sgl_task_params *sgl_task_params,
	काष्ठा regpair sense_data_buffer_phys_addr,
	u32 task_retry_id,
	u8 fcp_cmd_payload[32]);

/**
 * @brief init_initiator_midpath_fcoe_task - Initializes FCoE task context क्रम
 * midpath/unsolicited task types and init fcoe_sqe
 *
 * @param task_params - Poपूर्णांकer to task parameters काष्ठा
 * @param mid_path_fc_header - FC header
 * @param tx_sgl_task_params - Poपूर्णांकer to Tx SGL task params
 * @param rx_sgl_task_params - Poपूर्णांकer to Rx SGL task params
 * @param fw_to_place_fc_header	- Indication अगर the FW will place the FC header
 * in addition to the data arrives.
 */
पूर्णांक init_initiator_midpath_unsolicited_fcoe_task(
	काष्ठा fcoe_task_params *task_params,
	काष्ठा fcoe_tx_mid_path_params *mid_path_fc_header,
	काष्ठा scsi_sgl_task_params *tx_sgl_task_params,
	काष्ठा scsi_sgl_task_params *rx_sgl_task_params,
	u8 fw_to_place_fc_header);

/**
 * @brief init_initiator_पात_fcoe_task - Initializes FCoE task context क्रम
 * पात task types and init fcoe_sqe
 *
 * @param task_params - Poपूर्णांकer to task parameters काष्ठा
 */
पूर्णांक init_initiator_पात_fcoe_task(काष्ठा fcoe_task_params *task_params);

/**
 * @brief init_initiator_cleanup_fcoe_task - Initializes FCoE task context क्रम
 * cleanup task types and init fcoe_sqe
 *
 *
 * @param task_params - Poपूर्णांकer to task parameters काष्ठा
 */
पूर्णांक init_initiator_cleanup_fcoe_task(काष्ठा fcoe_task_params *task_params);

/**
 * @brief init_initiator_cleanup_fcoe_task - Initializes FCoE task context क्रम
 * sequence recovery task types and init fcoe_sqe
 *
 *
 * @param task_params - Poपूर्णांकer to task parameters काष्ठा
 * @param desired_offset - The desired offest the task will be re-sent from
 */
पूर्णांक init_initiator_sequence_recovery_fcoe_task(
	काष्ठा fcoe_task_params *task_params,
	u32 desired_offset);
#पूर्ण_अगर
