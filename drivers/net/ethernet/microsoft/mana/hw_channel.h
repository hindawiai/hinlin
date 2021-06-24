<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright (c) 2021, Microsoft Corporation. */

#अगर_अघोषित _HW_CHANNEL_H
#घोषणा _HW_CHANNEL_H

#घोषणा DEFAULT_LOG2_THROTTLING_FOR_ERROR_EQ  4

#घोषणा HW_CHANNEL_MAX_REQUEST_SIZE  0x1000
#घोषणा HW_CHANNEL_MAX_RESPONSE_SIZE 0x1000

#घोषणा HW_CHANNEL_VF_BOOTSTRAP_QUEUE_DEPTH 1

#घोषणा HWC_INIT_DATA_CQID		1
#घोषणा HWC_INIT_DATA_RQID		2
#घोषणा HWC_INIT_DATA_SQID		3
#घोषणा HWC_INIT_DATA_QUEUE_DEPTH	4
#घोषणा HWC_INIT_DATA_MAX_REQUEST	5
#घोषणा HWC_INIT_DATA_MAX_RESPONSE	6
#घोषणा HWC_INIT_DATA_MAX_NUM_CQS	7
#घोषणा HWC_INIT_DATA_PDID		8
#घोषणा HWC_INIT_DATA_GPA_MKEY		9

/* Structures labeled with "HW DATA" are exchanged with the hardware. All of
 * them are naturally aligned and hence करोn't need __packed.
 */

जोड़ hwc_init_eq_id_db अणु
	u32 as_uपूर्णांक32;

	काष्ठा अणु
		u32 eq_id	: 16;
		u32 करोorbell	: 16;
	पूर्ण;
पूर्ण; /* HW DATA */

जोड़ hwc_init_type_data अणु
	u32 as_uपूर्णांक32;

	काष्ठा अणु
		u32 value	: 24;
		u32 type	:  8;
	पूर्ण;
पूर्ण; /* HW DATA */

काष्ठा hwc_rx_oob अणु
	u32 type	: 6;
	u32 eom		: 1;
	u32 som		: 1;
	u32 venकरोr_err	: 8;
	u32 reserved1	: 16;

	u32 src_virt_wq	: 24;
	u32 src_vfid	: 8;

	u32 reserved2;

	जोड़ अणु
		u32 wqe_addr_low;
		u32 wqe_offset;
	पूर्ण;

	u32 wqe_addr_high;

	u32 client_data_unit	: 14;
	u32 reserved3		: 18;

	u32 tx_oob_data_size;

	u32 chunk_offset	: 21;
	u32 reserved4		: 11;
पूर्ण; /* HW DATA */

काष्ठा hwc_tx_oob अणु
	u32 reserved1;

	u32 reserved2;

	u32 vrq_id	: 24;
	u32 dest_vfid	: 8;

	u32 vrcq_id	: 24;
	u32 reserved3	: 8;

	u32 vscq_id	: 24;
	u32 loopback	: 1;
	u32 lso_override: 1;
	u32 dest_pf	: 1;
	u32 reserved4	: 5;

	u32 vsq_id	: 24;
	u32 reserved5	: 8;
पूर्ण; /* HW DATA */

काष्ठा hwc_work_request अणु
	व्योम *buf_va;
	व्योम *buf_sge_addr;
	u32 buf_len;
	u32 msg_size;

	काष्ठा gdma_wqe_request wqe_req;
	काष्ठा hwc_tx_oob tx_oob;

	काष्ठा gdma_sge sge;
पूर्ण;

/* hwc_dma_buf represents the array of in-flight WQEs.
 * mem_info as know as the GDMA mapped memory is partitioned and used by
 * in-flight WQEs.
 * The number of WQEs is determined by the number of in-flight messages.
 */
काष्ठा hwc_dma_buf अणु
	काष्ठा gdma_mem_info mem_info;

	u32 gpa_mkey;

	u32 num_reqs;
	काष्ठा hwc_work_request reqs[];
पूर्ण;

प्रकार व्योम hwc_rx_event_handler_t(व्योम *ctx, u32 gdma_rxq_id,
				    स्थिर काष्ठा hwc_rx_oob *rx_oob);

प्रकार व्योम hwc_tx_event_handler_t(व्योम *ctx, u32 gdma_txq_id,
				    स्थिर काष्ठा hwc_rx_oob *rx_oob);

काष्ठा hwc_cq अणु
	काष्ठा hw_channel_context *hwc;

	काष्ठा gdma_queue *gdma_cq;
	काष्ठा gdma_queue *gdma_eq;
	काष्ठा gdma_comp *comp_buf;
	u16 queue_depth;

	hwc_rx_event_handler_t *rx_event_handler;
	व्योम *rx_event_ctx;

	hwc_tx_event_handler_t *tx_event_handler;
	व्योम *tx_event_ctx;
पूर्ण;

काष्ठा hwc_wq अणु
	काष्ठा hw_channel_context *hwc;

	काष्ठा gdma_queue *gdma_wq;
	काष्ठा hwc_dma_buf *msg_buf;
	u16 queue_depth;

	काष्ठा hwc_cq *hwc_cq;
पूर्ण;

काष्ठा hwc_caller_ctx अणु
	काष्ठा completion comp_event;
	व्योम *output_buf;
	u32 output_buflen;

	u32 error; /* Linux error code */
	u32 status_code;
पूर्ण;

काष्ठा hw_channel_context अणु
	काष्ठा gdma_dev *gdma_dev;
	काष्ठा device *dev;

	u16 num_inflight_msg;
	u32 max_req_msg_size;

	u16 hwc_init_q_depth_max;
	u32 hwc_init_max_req_msg_size;
	u32 hwc_init_max_resp_msg_size;

	काष्ठा completion hwc_init_eqe_comp;

	काष्ठा hwc_wq *rxq;
	काष्ठा hwc_wq *txq;
	काष्ठा hwc_cq *cq;

	काष्ठा semaphore sema;
	काष्ठा gdma_resource inflight_msg_res;

	काष्ठा hwc_caller_ctx *caller_ctx;
पूर्ण;

पूर्णांक mana_hwc_create_channel(काष्ठा gdma_context *gc);
व्योम mana_hwc_destroy_channel(काष्ठा gdma_context *gc);

पूर्णांक mana_hwc_send_request(काष्ठा hw_channel_context *hwc, u32 req_len,
			  स्थिर व्योम *req, u32 resp_len, व्योम *resp);

#पूर्ण_अगर /* _HW_CHANNEL_H */
