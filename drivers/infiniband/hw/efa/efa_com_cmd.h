<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-2-Clause */
/*
 * Copyright 2018-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#अगर_अघोषित _EFA_COM_CMD_H_
#घोषणा _EFA_COM_CMD_H_

#समावेश "efa_com.h"

#घोषणा EFA_GID_SIZE 16

काष्ठा efa_com_create_qp_params अणु
	u64 rq_base_addr;
	u32 send_cq_idx;
	u32 recv_cq_idx;
	/*
	 * Send descriptor ring size in bytes,
	 * sufficient क्रम user-provided number of WQEs and SGL size
	 */
	u32 sq_ring_size_in_bytes;
	/* Max number of WQEs that will be posted on send queue */
	u32 sq_depth;
	/* Recv descriptor ring size in bytes */
	u32 rq_ring_size_in_bytes;
	u32 rq_depth;
	u16 pd;
	u16 uarn;
	u8 qp_type;
पूर्ण;

काष्ठा efa_com_create_qp_result अणु
	u32 qp_handle;
	u32 qp_num;
	u32 sq_db_offset;
	u32 rq_db_offset;
	u32 llq_descriptors_offset;
	u16 send_sub_cq_idx;
	u16 recv_sub_cq_idx;
पूर्ण;

काष्ठा efa_com_modअगरy_qp_params अणु
	u32 modअगरy_mask;
	u32 qp_handle;
	u32 qp_state;
	u32 cur_qp_state;
	u32 qkey;
	u32 sq_psn;
	u8 sq_drained_async_notअगरy;
	u8 rnr_retry;
पूर्ण;

काष्ठा efa_com_query_qp_params अणु
	u32 qp_handle;
पूर्ण;

काष्ठा efa_com_query_qp_result अणु
	u32 qp_state;
	u32 qkey;
	u32 sq_draining;
	u32 sq_psn;
	u8 rnr_retry;
पूर्ण;

काष्ठा efa_com_destroy_qp_params अणु
	u32 qp_handle;
पूर्ण;

काष्ठा efa_com_create_cq_params अणु
	/* cq physical base address in OS memory */
	dma_addr_t dma_addr;
	/* completion queue depth in # of entries */
	u16 cq_depth;
	u16 num_sub_cqs;
	u16 uarn;
	u8 entry_size_in_bytes;
पूर्ण;

काष्ठा efa_com_create_cq_result अणु
	/* cq identअगरier */
	u16 cq_idx;
	/* actual cq depth in # of entries */
	u16 actual_depth;
पूर्ण;

काष्ठा efa_com_destroy_cq_params अणु
	u16 cq_idx;
पूर्ण;

काष्ठा efa_com_create_ah_params अणु
	u16 pdn;
	/* Destination address in network byte order */
	u8 dest_addr[EFA_GID_SIZE];
पूर्ण;

काष्ठा efa_com_create_ah_result अणु
	u16 ah;
पूर्ण;

काष्ठा efa_com_destroy_ah_params अणु
	u16 ah;
	u16 pdn;
पूर्ण;

काष्ठा efa_com_get_device_attr_result अणु
	u8 addr[EFA_GID_SIZE];
	u64 page_size_cap;
	u64 max_mr_pages;
	u32 mtu;
	u32 fw_version;
	u32 admin_api_version;
	u32 device_version;
	u32 supported_features;
	u32 phys_addr_width;
	u32 virt_addr_width;
	u32 max_qp;
	u32 max_sq_depth; /* wqes */
	u32 max_rq_depth; /* wqes */
	u32 max_cq;
	u32 max_cq_depth; /* cqes */
	u32 अंतरभूत_buf_size;
	u32 max_mr;
	u32 max_pd;
	u32 max_ah;
	u32 max_llq_size;
	u32 max_rdma_size;
	u32 device_caps;
	u16 sub_cqs_per_cq;
	u16 max_sq_sge;
	u16 max_rq_sge;
	u16 max_wr_rdma_sge;
	u16 max_tx_batch;
	u16 min_sq_depth;
	u8 db_bar;
पूर्ण;

काष्ठा efa_com_get_hw_hपूर्णांकs_result अणु
	u16 mmio_पढ़ो_समयout;
	u16 driver_watchकरोg_समयout;
	u16 admin_completion_समयout;
	u16 poll_पूर्णांकerval;
	u32 reserved[4];
पूर्ण;

काष्ठा efa_com_mem_addr अणु
	u32 mem_addr_low;
	u32 mem_addr_high;
पूर्ण;

/* Used at indirect mode page list chunks क्रम chaining */
काष्ठा efa_com_ctrl_buff_info अणु
	/* indicates length of the buffer poपूर्णांकed by control_buffer_address. */
	u32 length;
	/* poपूर्णांकs to control buffer (direct or indirect) */
	काष्ठा efa_com_mem_addr address;
पूर्ण;

काष्ठा efa_com_reg_mr_params अणु
	/* Memory region length, in bytes. */
	u64 mr_length_in_bytes;
	/* IO Virtual Address associated with this MR. */
	u64 iova;
	/* words 8:15: Physical Buffer List, each element is page-aligned. */
	जोड़ अणु
		/*
		 * Inline array of physical addresses of app pages
		 * (optimization क्रम लघु region reservations)
		 */
		u64 अंतरभूत_pbl_array[4];
		/*
		 * Describes the next physically contiguous chunk of indirect
		 * page list. A page list contains physical addresses of command
		 * data pages. Data pages are 4KB; page list chunks are
		 * variable-sized.
		 */
		काष्ठा efa_com_ctrl_buff_info pbl;
	पूर्ण pbl;
	/* number of pages in PBL (redundant, could be calculated) */
	u32 page_num;
	/* Protection Doमुख्य */
	u16 pd;
	/*
	 * phys_page_size_shअगरt - page size is (1 << phys_page_size_shअगरt)
	 * Page size is used क्रम building the Virtual to Physical
	 * address mapping
	 */
	u8 page_shअगरt;
	/* see permissions field of काष्ठा efa_admin_reg_mr_cmd */
	u8 permissions;
	u8 अंतरभूत_pbl;
	u8 indirect;
पूर्ण;

काष्ठा efa_com_reg_mr_result अणु
	/*
	 * To be used in conjunction with local buffers references in SQ and
	 * RQ WQE
	 */
	u32 l_key;
	/*
	 * To be used in incoming RDMA semantics messages to refer to remotely
	 * accessed memory region
	 */
	u32 r_key;
पूर्ण;

काष्ठा efa_com_dereg_mr_params अणु
	u32 l_key;
पूर्ण;

काष्ठा efa_com_alloc_pd_result अणु
	u16 pdn;
पूर्ण;

काष्ठा efa_com_dealloc_pd_params अणु
	u16 pdn;
पूर्ण;

काष्ठा efa_com_alloc_uar_result अणु
	u16 uarn;
पूर्ण;

काष्ठा efa_com_dealloc_uar_params अणु
	u16 uarn;
पूर्ण;

काष्ठा efa_com_get_stats_params अणु
	/* see क्रमागत efa_admin_get_stats_type */
	u8 type;
	/* see क्रमागत efa_admin_get_stats_scope */
	u8 scope;
	u16 scope_modअगरier;
पूर्ण;

काष्ठा efa_com_basic_stats अणु
	u64 tx_bytes;
	u64 tx_pkts;
	u64 rx_bytes;
	u64 rx_pkts;
	u64 rx_drops;
पूर्ण;

काष्ठा efa_com_messages_stats अणु
	u64 send_bytes;
	u64 send_wrs;
	u64 recv_bytes;
	u64 recv_wrs;
पूर्ण;

काष्ठा efa_com_rdma_पढ़ो_stats अणु
	u64 पढ़ो_wrs;
	u64 पढ़ो_bytes;
	u64 पढ़ो_wr_err;
	u64 पढ़ो_resp_bytes;
पूर्ण;

जोड़ efa_com_get_stats_result अणु
	काष्ठा efa_com_basic_stats basic_stats;
	काष्ठा efa_com_messages_stats messages_stats;
	काष्ठा efa_com_rdma_पढ़ो_stats rdma_पढ़ो_stats;
पूर्ण;

व्योम efa_com_set_dma_addr(dma_addr_t addr, u32 *addr_high, u32 *addr_low);
पूर्णांक efa_com_create_qp(काष्ठा efa_com_dev *edev,
		      काष्ठा efa_com_create_qp_params *params,
		      काष्ठा efa_com_create_qp_result *res);
पूर्णांक efa_com_modअगरy_qp(काष्ठा efa_com_dev *edev,
		      काष्ठा efa_com_modअगरy_qp_params *params);
पूर्णांक efa_com_query_qp(काष्ठा efa_com_dev *edev,
		     काष्ठा efa_com_query_qp_params *params,
		     काष्ठा efa_com_query_qp_result *result);
पूर्णांक efa_com_destroy_qp(काष्ठा efa_com_dev *edev,
		       काष्ठा efa_com_destroy_qp_params *params);
पूर्णांक efa_com_create_cq(काष्ठा efa_com_dev *edev,
		      काष्ठा efa_com_create_cq_params *params,
		      काष्ठा efa_com_create_cq_result *result);
पूर्णांक efa_com_destroy_cq(काष्ठा efa_com_dev *edev,
		       काष्ठा efa_com_destroy_cq_params *params);
पूर्णांक efa_com_रेजिस्टर_mr(काष्ठा efa_com_dev *edev,
			काष्ठा efa_com_reg_mr_params *params,
			काष्ठा efa_com_reg_mr_result *result);
पूर्णांक efa_com_dereg_mr(काष्ठा efa_com_dev *edev,
		     काष्ठा efa_com_dereg_mr_params *params);
पूर्णांक efa_com_create_ah(काष्ठा efa_com_dev *edev,
		      काष्ठा efa_com_create_ah_params *params,
		      काष्ठा efa_com_create_ah_result *result);
पूर्णांक efa_com_destroy_ah(काष्ठा efa_com_dev *edev,
		       काष्ठा efa_com_destroy_ah_params *params);
पूर्णांक efa_com_get_device_attr(काष्ठा efa_com_dev *edev,
			    काष्ठा efa_com_get_device_attr_result *result);
पूर्णांक efa_com_get_hw_hपूर्णांकs(काष्ठा efa_com_dev *edev,
			 काष्ठा efa_com_get_hw_hपूर्णांकs_result *result);
bool
efa_com_check_supported_feature_id(काष्ठा efa_com_dev *edev,
				   क्रमागत efa_admin_aq_feature_id feature_id);
पूर्णांक efa_com_set_feature_ex(काष्ठा efa_com_dev *edev,
			   काष्ठा efa_admin_set_feature_resp *set_resp,
			   काष्ठा efa_admin_set_feature_cmd *set_cmd,
			   क्रमागत efa_admin_aq_feature_id feature_id,
			   dma_addr_t control_buf_dma_addr,
			   u32 control_buff_size);
पूर्णांक efa_com_set_aenq_config(काष्ठा efa_com_dev *edev, u32 groups);
पूर्णांक efa_com_alloc_pd(काष्ठा efa_com_dev *edev,
		     काष्ठा efa_com_alloc_pd_result *result);
पूर्णांक efa_com_dealloc_pd(काष्ठा efa_com_dev *edev,
		       काष्ठा efa_com_dealloc_pd_params *params);
पूर्णांक efa_com_alloc_uar(काष्ठा efa_com_dev *edev,
		      काष्ठा efa_com_alloc_uar_result *result);
पूर्णांक efa_com_dealloc_uar(काष्ठा efa_com_dev *edev,
			काष्ठा efa_com_dealloc_uar_params *params);
पूर्णांक efa_com_get_stats(काष्ठा efa_com_dev *edev,
		      काष्ठा efa_com_get_stats_params *params,
		      जोड़ efa_com_get_stats_result *result);

#पूर्ण_अगर /* _EFA_COM_CMD_H_ */
