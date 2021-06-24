<शैली गुरु>
/*
 * Copyright (c) 2005 Cisco Systems.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित IB_SRP_H
#घोषणा IB_SRP_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/scatterlist.h>

#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_sa.h>
#समावेश <rdma/ib_cm.h>
#समावेश <rdma/rdma_cm.h>

क्रमागत अणु
	SRP_PATH_REC_TIMEOUT_MS	= 1000,
	SRP_ABORT_TIMEOUT_MS	= 5000,

	SRP_PORT_REसूचीECT	= 1,
	SRP_DLID_REसूचीECT	= 2,
	SRP_STALE_CONN		= 3,

	SRP_DEF_SG_TABLESIZE	= 12,

	SRP_DEFAULT_QUEUE_SIZE	= 1 << 6,
	SRP_RSP_SQ_SIZE		= 1,
	SRP_TSK_MGMT_SQ_SIZE	= 1,
	SRP_DEFAULT_CMD_SQ_SIZE = SRP_DEFAULT_QUEUE_SIZE - SRP_RSP_SQ_SIZE -
				  SRP_TSK_MGMT_SQ_SIZE,

	SRP_TAG_NO_REQ		= ~0U,
	SRP_TAG_TSK_MGMT	= 1U << 31,

	SRP_MAX_PAGES_PER_MR	= 512,

	SRP_MAX_ADD_CDB_LEN	= 16,

	SRP_MAX_IMM_SGE		= 2,
	SRP_MAX_SGE		= SRP_MAX_IMM_SGE + 1,
	/*
	 * Choose the immediate data offset such that a 32 byte CDB still fits.
	 */
	SRP_IMM_DATA_OFFSET	= माप(काष्ठा srp_cmd) +
				  SRP_MAX_ADD_CDB_LEN +
				  माप(काष्ठा srp_imm_buf),
पूर्ण;

क्रमागत srp_target_state अणु
	SRP_TARGET_SCANNING,
	SRP_TARGET_LIVE,
	SRP_TARGET_REMOVED,
पूर्ण;

क्रमागत srp_iu_type अणु
	SRP_IU_CMD,
	SRP_IU_TSK_MGMT,
	SRP_IU_RSP,
पूर्ण;

/*
 * @mr_page_mask: HCA memory registration page mask.
 * @mr_page_size: HCA memory registration page size.
 * @mr_max_size: Maximum size in bytes of a single FR registration request.
 */
काष्ठा srp_device अणु
	काष्ठा list_head	dev_list;
	काष्ठा ib_device       *dev;
	काष्ठा ib_pd	       *pd;
	u32			global_rkey;
	u64			mr_page_mask;
	पूर्णांक			mr_page_size;
	पूर्णांक			mr_max_size;
	पूर्णांक			max_pages_per_mr;
	bool			has_fr;
	bool			use_fast_reg;
पूर्ण;

काष्ठा srp_host अणु
	काष्ठा srp_device      *srp_dev;
	u8			port;
	काष्ठा device		dev;
	काष्ठा list_head	target_list;
	spinlock_t		target_lock;
	काष्ठा completion	released;
	काष्ठा list_head	list;
	काष्ठा mutex		add_target_mutex;
पूर्ण;

काष्ठा srp_request अणु
	काष्ठा scsi_cmnd       *scmnd;
	काष्ठा srp_iu	       *cmd;
	काष्ठा srp_fr_desc     **fr_list;
	काष्ठा srp_direct_buf  *indirect_desc;
	dma_addr_t		indirect_dma_addr;
	लघु			nmdesc;
	काष्ठा ib_cqe		reg_cqe;
पूर्ण;

/**
 * काष्ठा srp_rdma_ch
 * @comp_vector: Completion vector used by this RDMA channel.
 * @max_it_iu_len: Maximum initiator-to-target inक्रमmation unit length.
 * @max_ti_iu_len: Maximum target-to-initiator inक्रमmation unit length.
 */
काष्ठा srp_rdma_ch अणु
	/* These are RW in the hot path, and commonly used together */
	काष्ठा list_head	मुक्त_tx;
	spinlock_t		lock;
	s32			req_lim;

	/* These are पढ़ो-only in the hot path */
	काष्ठा srp_target_port *target ____cacheline_aligned_in_smp;
	काष्ठा ib_cq	       *send_cq;
	काष्ठा ib_cq	       *recv_cq;
	काष्ठा ib_qp	       *qp;
	काष्ठा srp_fr_pool     *fr_pool;
	uपूर्णांक32_t		max_it_iu_len;
	uपूर्णांक32_t		max_ti_iu_len;
	u8			max_imm_sge;
	bool			use_imm_data;

	/* Everything above this poपूर्णांक is used in the hot path of
	 * command processing. Try to keep them packed पूर्णांकo cachelines.
	 */

	काष्ठा completion	करोne;
	पूर्णांक			status;

	जोड़ अणु
		काष्ठा ib_cm अणु
			काष्ठा sa_path_rec	path;
			काष्ठा ib_sa_query	*path_query;
			पूर्णांक			path_query_id;
			काष्ठा ib_cm_id		*cm_id;
		पूर्ण ib_cm;
		काष्ठा rdma_cm अणु
			काष्ठा rdma_cm_id	*cm_id;
		पूर्ण rdma_cm;
	पूर्ण;

	काष्ठा srp_iu	      **tx_ring;
	काष्ठा srp_iu	      **rx_ring;
	काष्ठा srp_request     *req_ring;
	पूर्णांक			comp_vector;

	u64			tsk_mgmt_tag;
	काष्ठा completion	tsk_mgmt_करोne;
	u8			tsk_mgmt_status;
	bool			connected;
पूर्ण;

/**
 * काष्ठा srp_target_port
 * @comp_vector: Completion vector used by the first RDMA channel created क्रम
 *   this target port.
 */
काष्ठा srp_target_port अणु
	/* पढ़ो and written in the hot path */
	spinlock_t		lock;

	/* पढ़ो only in the hot path */
	u32			global_rkey;
	काष्ठा srp_rdma_ch	*ch;
	काष्ठा net		*net;
	u32			ch_count;
	u32			lkey;
	क्रमागत srp_target_state	state;
	uपूर्णांक32_t		max_it_iu_size;
	अचिन्हित पूर्णांक		cmd_sg_cnt;
	अचिन्हित पूर्णांक		indirect_size;
	bool			allow_ext_sg;

	/* other member variables */
	जोड़ ib_gid		sgid;
	__be64			id_ext;
	__be64			ioc_guid;
	__be64			initiator_ext;
	u16			io_class;
	काष्ठा srp_host	       *srp_host;
	काष्ठा Scsi_Host       *scsi_host;
	काष्ठा srp_rport       *rport;
	अक्षर			target_name[32];
	अचिन्हित पूर्णांक		scsi_id;
	अचिन्हित पूर्णांक		sg_tablesize;
	अचिन्हित पूर्णांक		target_can_queue;
	पूर्णांक			mr_pool_size;
	पूर्णांक			mr_per_cmd;
	पूर्णांक			queue_size;
	पूर्णांक			req_ring_size;
	पूर्णांक			comp_vector;
	पूर्णांक			tl_retry_count;

	bool			using_rdma_cm;

	जोड़ अणु
		काष्ठा अणु
			__be64			service_id;
			जोड़ ib_gid		orig_dgid;
			__be16			pkey;
		पूर्ण ib_cm;
		काष्ठा अणु
			जोड़ अणु
				काष्ठा sockaddr_in	ip4;
				काष्ठा sockaddr_in6	ip6;
				काष्ठा sockaddr		sa;
				काष्ठा sockaddr_storage ss;
			पूर्ण src;
			जोड़ अणु
				काष्ठा sockaddr_in	ip4;
				काष्ठा sockaddr_in6	ip6;
				काष्ठा sockaddr		sa;
				काष्ठा sockaddr_storage ss;
			पूर्ण dst;
			bool src_specअगरied;
		पूर्ण rdma_cm;
	पूर्ण;

	u32			rq_पंचांगo_jअगरfies;

	पूर्णांक			zero_req_lim;

	काष्ठा work_काष्ठा	tl_err_work;
	काष्ठा work_काष्ठा	हटाओ_work;

	काष्ठा list_head	list;
	bool			qp_in_error;
पूर्ण;

काष्ठा srp_iu अणु
	काष्ठा list_head	list;
	u64			dma;
	व्योम		       *buf;
	माप_प्रकार			size;
	क्रमागत dma_data_direction	direction;
	u32			num_sge;
	काष्ठा ib_sge		sge[SRP_MAX_SGE];
	काष्ठा ib_cqe		cqe;
पूर्ण;

/**
 * काष्ठा srp_fr_desc - fast registration work request arguments
 * @entry: Entry in srp_fr_pool.मुक्त_list.
 * @mr:    Memory region.
 * @frpl:  Fast registration page list.
 */
काष्ठा srp_fr_desc अणु
	काष्ठा list_head		entry;
	काष्ठा ib_mr			*mr;
पूर्ण;

/**
 * काष्ठा srp_fr_pool - pool of fast registration descriptors
 *
 * An entry is available क्रम allocation अगर and only अगर it occurs in @मुक्त_list.
 *
 * @size:      Number of descriptors in this pool.
 * @max_page_list_len: Maximum fast registration work request page list length.
 * @lock:      Protects मुक्त_list.
 * @मुक्त_list: List of मुक्त descriptors.
 * @desc:      Fast registration descriptor pool.
 */
काष्ठा srp_fr_pool अणु
	पूर्णांक			size;
	पूर्णांक			max_page_list_len;
	spinlock_t		lock;
	काष्ठा list_head	मुक्त_list;
	काष्ठा srp_fr_desc	desc[];
पूर्ण;

/**
 * काष्ठा srp_map_state - per-request DMA memory mapping state
 * @desc:	    Poपूर्णांकer to the element of the SRP buffer descriptor array
 *		    that is being filled in.
 * @pages:	    Array with DMA addresses of pages being considered क्रम
 *		    memory registration.
 * @base_dma_addr:  DMA address of the first page that has not yet been mapped.
 * @dma_len:	    Number of bytes that will be रेजिस्टरed with the next FR
 *                  memory registration call.
 * @total_len:	    Total number of bytes in the sg-list being mapped.
 * @npages:	    Number of page addresses in the pages[] array.
 * @nmdesc:	    Number of FR memory descriptors used क्रम mapping.
 * @ndesc:	    Number of SRP buffer descriptors that have been filled in.
 */
काष्ठा srp_map_state अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा srp_fr_desc **next;
			काष्ठा srp_fr_desc **end;
		पूर्ण fr;
		काष्ठा अणु
			व्योम		   **next;
			व्योम		   **end;
		पूर्ण gen;
	पूर्ण;
	काष्ठा srp_direct_buf  *desc;
	जोड़ अणु
		u64			*pages;
		काष्ठा scatterlist	*sg;
	पूर्ण;
	dma_addr_t		base_dma_addr;
	u32			dma_len;
	u32			total_len;
	अचिन्हित पूर्णांक		npages;
	अचिन्हित पूर्णांक		nmdesc;
	अचिन्हित पूर्णांक		ndesc;
पूर्ण;

#पूर्ण_अगर /* IB_SRP_H */
