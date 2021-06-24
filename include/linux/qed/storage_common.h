<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित __STORAGE_COMMON__
#घोषणा __STORAGE_COMMON__

/*********************/
/* SCSI CONSTANTS */
/*********************/

#घोषणा SCSI_MAX_NUM_OF_CMDQS		(NUM_OF_GLOBAL_QUEUES / 2)
#घोषणा BDQ_NUM_RESOURCES		(4)

#घोषणा BDQ_ID_RQ			(0)
#घोषणा BDQ_ID_IMM_DATA			(1)
#घोषणा BDQ_ID_TQ			(2)
#घोषणा BDQ_NUM_IDS			(3)

#घोषणा SCSI_NUM_SGES_SLOW_SGL_THR	8

#घोषणा BDQ_MAX_EXTERNAL_RING_SIZE	BIT(15)

/* SCSI op codes */
#घोषणा SCSI_OPCODE_COMPARE_AND_WRITE	(0x89)
#घोषणा SCSI_OPCODE_READ_10		(0x28)
#घोषणा SCSI_OPCODE_WRITE_6		(0x0A)
#घोषणा SCSI_OPCODE_WRITE_10		(0x2A)
#घोषणा SCSI_OPCODE_WRITE_12		(0xAA)
#घोषणा SCSI_OPCODE_WRITE_16		(0x8A)
#घोषणा SCSI_OPCODE_WRITE_AND_VERIFY_10	(0x2E)
#घोषणा SCSI_OPCODE_WRITE_AND_VERIFY_12	(0xAE)
#घोषणा SCSI_OPCODE_WRITE_AND_VERIFY_16	(0x8E)

/* iSCSI Drv opaque */
काष्ठा iscsi_drv_opaque अणु
	__le16 reserved_zero[3];
	__le16 opaque;
पूर्ण;

/* Scsi 2B/8B opaque जोड़ */
जोड़ scsi_opaque अणु
	काष्ठा regpair fcoe_opaque;
	काष्ठा iscsi_drv_opaque iscsi_opaque;
पूर्ण;

/* SCSI buffer descriptor */
काष्ठा scsi_bd अणु
	काष्ठा regpair address;
	जोड़ scsi_opaque opaque;
पूर्ण;

/* Scsi Drv BDQ काष्ठा */
काष्ठा scsi_bdq_ram_drv_data अणु
	__le16 बाह्यal_producer;
	__le16 reserved0[3];
पूर्ण;

/* SCSI SGE entry */
काष्ठा scsi_sge अणु
	काष्ठा regpair sge_addr;
	__le32 sge_len;
	__le32 reserved;
पूर्ण;

/* Cached SGEs section */
काष्ठा scsi_cached_sges अणु
	काष्ठा scsi_sge sge[4];
पूर्ण;

/* Scsi Drv CMDQ काष्ठा */
काष्ठा scsi_drv_cmdq अणु
	__le16 cmdq_cons;
	__le16 reserved0;
	__le32 reserved1;
पूर्ण;

/* Common SCSI init params passed by driver to FW in function init ramrod */
काष्ठा scsi_init_func_params अणु
	__le16 num_tasks;
	u8 log_page_size;
	u8 log_page_size_conn;
	u8 debug_mode;
	u8 reserved2[11];
पूर्ण;

/* SCSI RQ/CQ/CMDQ firmware function init parameters */
काष्ठा scsi_init_func_queues अणु
	काष्ठा regpair glbl_q_params_addr;
	__le16 rq_buffer_size;
	__le16 cq_num_entries;
	__le16 cmdq_num_entries;
	u8 bdq_resource_id;
	u8 q_validity;
#घोषणा SCSI_INIT_FUNC_QUEUES_RQ_VALID_MASK			0x1
#घोषणा SCSI_INIT_FUNC_QUEUES_RQ_VALID_SHIFT			0
#घोषणा SCSI_INIT_FUNC_QUEUES_IMM_DATA_VALID_MASK		0x1
#घोषणा SCSI_INIT_FUNC_QUEUES_IMM_DATA_VALID_SHIFT		1
#घोषणा SCSI_INIT_FUNC_QUEUES_CMD_VALID_MASK			0x1
#घोषणा SCSI_INIT_FUNC_QUEUES_CMD_VALID_SHIFT			2
#घोषणा SCSI_INIT_FUNC_QUEUES_TQ_VALID_MASK			0x1
#घोषणा SCSI_INIT_FUNC_QUEUES_TQ_VALID_SHIFT			3
#घोषणा SCSI_INIT_FUNC_QUEUES_SOC_EN_MASK			0x1
#घोषणा SCSI_INIT_FUNC_QUEUES_SOC_EN_SHIFT			4
#घोषणा SCSI_INIT_FUNC_QUEUES_SOC_NUM_OF_BLOCKS_LOG_MASK	0x7
#घोषणा SCSI_INIT_FUNC_QUEUES_SOC_NUM_OF_BLOCKS_LOG_SHIFT	5
	__le16 cq_cmdq_sb_num_arr[SCSI_MAX_NUM_OF_CMDQS];
	u8 num_queues;
	u8 queue_relative_offset;
	u8 cq_sb_pi;
	u8 cmdq_sb_pi;
	u8 bdq_pbl_num_entries[BDQ_NUM_IDS];
	u8 reserved1;
	काष्ठा regpair bdq_pbl_base_address[BDQ_NUM_IDS];
	__le16 bdq_xoff_threshold[BDQ_NUM_IDS];
	__le16 cmdq_xoff_threshold;
	__le16 bdq_xon_threshold[BDQ_NUM_IDS];
	__le16 cmdq_xon_threshold;
पूर्ण;

/* Scsi Drv BDQ Data काष्ठा (2 BDQ IDs: 0 - RQ, 1 - Immediate Data) */
काष्ठा scsi_ram_per_bdq_resource_drv_data अणु
	काष्ठा scsi_bdq_ram_drv_data drv_data_per_bdq_id[BDQ_NUM_IDS];
पूर्ण;

/* SCSI SGL types */
क्रमागत scsi_sgl_mode अणु
	SCSI_TX_SLOW_SGL,
	SCSI_FAST_SGL,
	MAX_SCSI_SGL_MODE
पूर्ण;

/* SCSI SGL parameters */
काष्ठा scsi_sgl_params अणु
	काष्ठा regpair sgl_addr;
	__le32 sgl_total_length;
	__le32 sge_offset;
	__le16 sgl_num_sges;
	u8 sgl_index;
	u8 reserved;
पूर्ण;

/* SCSI terminate connection params */
काष्ठा scsi_terminate_extra_params अणु
	__le16 unsolicited_cq_count;
	__le16 cmdq_count;
	u8 reserved[4];
पूर्ण;

/* SCSI Task Queue Element */
काष्ठा scsi_tqe अणु
	__le16 itid;
पूर्ण;

#पूर्ण_अगर /* __STORAGE_COMMON__ */
