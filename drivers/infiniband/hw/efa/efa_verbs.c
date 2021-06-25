<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright 2018-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/log2.h>

#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश "efa.h"

क्रमागत अणु
	EFA_MMAP_DMA_PAGE = 0,
	EFA_MMAP_IO_WC,
	EFA_MMAP_IO_NC,
पूर्ण;

#घोषणा EFA_AENQ_ENABLED_GROUPS \
	(BIT(EFA_ADMIN_FATAL_ERROR) | BIT(EFA_ADMIN_WARNING) | \
	 BIT(EFA_ADMIN_NOTIFICATION) | BIT(EFA_ADMIN_KEEP_ALIVE))

काष्ठा efa_user_mmap_entry अणु
	काष्ठा rdma_user_mmap_entry rdma_entry;
	u64 address;
	u8 mmap_flag;
पूर्ण;

#घोषणा EFA_DEFINE_STATS(op) \
	op(EFA_TX_BYTES, "tx_bytes") \
	op(EFA_TX_PKTS, "tx_pkts") \
	op(EFA_RX_BYTES, "rx_bytes") \
	op(EFA_RX_PKTS, "rx_pkts") \
	op(EFA_RX_DROPS, "rx_drops") \
	op(EFA_SEND_BYTES, "send_bytes") \
	op(EFA_SEND_WRS, "send_wrs") \
	op(EFA_RECV_BYTES, "recv_bytes") \
	op(EFA_RECV_WRS, "recv_wrs") \
	op(EFA_RDMA_READ_WRS, "rdma_read_wrs") \
	op(EFA_RDMA_READ_BYTES, "rdma_read_bytes") \
	op(EFA_RDMA_READ_WR_ERR, "rdma_read_wr_err") \
	op(EFA_RDMA_READ_RESP_BYTES, "rdma_read_resp_bytes") \
	op(EFA_SUBMITTED_CMDS, "submitted_cmds") \
	op(EFA_COMPLETED_CMDS, "completed_cmds") \
	op(EFA_CMDS_ERR, "cmds_err") \
	op(EFA_NO_COMPLETION_CMDS, "no_completion_cmds") \
	op(EFA_KEEP_ALIVE_RCVD, "keep_alive_rcvd") \
	op(EFA_ALLOC_PD_ERR, "alloc_pd_err") \
	op(EFA_CREATE_QP_ERR, "create_qp_err") \
	op(EFA_CREATE_CQ_ERR, "create_cq_err") \
	op(EFA_REG_MR_ERR, "reg_mr_err") \
	op(EFA_ALLOC_UCONTEXT_ERR, "alloc_ucontext_err") \
	op(EFA_CREATE_AH_ERR, "create_ah_err") \
	op(EFA_MMAP_ERR, "mmap_err")

#घोषणा EFA_STATS_ENUM(ename, name) ename,
#घोषणा EFA_STATS_STR(ename, name) [ename] = name,

क्रमागत efa_hw_stats अणु
	EFA_DEFINE_STATS(EFA_STATS_ENUM)
पूर्ण;

अटल स्थिर अक्षर *स्थिर efa_stats_names[] = अणु
	EFA_DEFINE_STATS(EFA_STATS_STR)
पूर्ण;

#घोषणा EFA_CHUNK_PAYLOAD_SHIFT       12
#घोषणा EFA_CHUNK_PAYLOAD_SIZE        BIT(EFA_CHUNK_PAYLOAD_SHIFT)
#घोषणा EFA_CHUNK_PAYLOAD_PTR_SIZE    8

#घोषणा EFA_CHUNK_SHIFT               12
#घोषणा EFA_CHUNK_SIZE                BIT(EFA_CHUNK_SHIFT)
#घोषणा EFA_CHUNK_PTR_SIZE            माप(काष्ठा efa_com_ctrl_buff_info)

#घोषणा EFA_PTRS_PER_CHUNK \
	((EFA_CHUNK_SIZE - EFA_CHUNK_PTR_SIZE) / EFA_CHUNK_PAYLOAD_PTR_SIZE)

#घोषणा EFA_CHUNK_USED_SIZE \
	((EFA_PTRS_PER_CHUNK * EFA_CHUNK_PAYLOAD_PTR_SIZE) + EFA_CHUNK_PTR_SIZE)

काष्ठा pbl_chunk अणु
	dma_addr_t dma_addr;
	u64 *buf;
	u32 length;
पूर्ण;

काष्ठा pbl_chunk_list अणु
	काष्ठा pbl_chunk *chunks;
	अचिन्हित पूर्णांक size;
पूर्ण;

काष्ठा pbl_context अणु
	जोड़ अणु
		काष्ठा अणु
			dma_addr_t dma_addr;
		पूर्ण continuous;
		काष्ठा अणु
			u32 pbl_buf_size_in_pages;
			काष्ठा scatterlist *sgl;
			पूर्णांक sg_dma_cnt;
			काष्ठा pbl_chunk_list chunk_list;
		पूर्ण indirect;
	पूर्ण phys;
	u64 *pbl_buf;
	u32 pbl_buf_size_in_bytes;
	u8 physically_continuous;
पूर्ण;

अटल अंतरभूत काष्ठा efa_dev *to_edev(काष्ठा ib_device *ibdev)
अणु
	वापस container_of(ibdev, काष्ठा efa_dev, ibdev);
पूर्ण

अटल अंतरभूत काष्ठा efa_ucontext *to_eucontext(काष्ठा ib_ucontext *ibucontext)
अणु
	वापस container_of(ibucontext, काष्ठा efa_ucontext, ibucontext);
पूर्ण

अटल अंतरभूत काष्ठा efa_pd *to_epd(काष्ठा ib_pd *ibpd)
अणु
	वापस container_of(ibpd, काष्ठा efa_pd, ibpd);
पूर्ण

अटल अंतरभूत काष्ठा efa_mr *to_emr(काष्ठा ib_mr *ibmr)
अणु
	वापस container_of(ibmr, काष्ठा efa_mr, ibmr);
पूर्ण

अटल अंतरभूत काष्ठा efa_qp *to_eqp(काष्ठा ib_qp *ibqp)
अणु
	वापस container_of(ibqp, काष्ठा efa_qp, ibqp);
पूर्ण

अटल अंतरभूत काष्ठा efa_cq *to_ecq(काष्ठा ib_cq *ibcq)
अणु
	वापस container_of(ibcq, काष्ठा efa_cq, ibcq);
पूर्ण

अटल अंतरभूत काष्ठा efa_ah *to_eah(काष्ठा ib_ah *ibah)
अणु
	वापस container_of(ibah, काष्ठा efa_ah, ibah);
पूर्ण

अटल अंतरभूत काष्ठा efa_user_mmap_entry *
to_emmap(काष्ठा rdma_user_mmap_entry *rdma_entry)
अणु
	वापस container_of(rdma_entry, काष्ठा efa_user_mmap_entry, rdma_entry);
पूर्ण

#घोषणा EFA_DEV_CAP(dev, cap) \
	((dev)->dev_attr.device_caps & \
	 EFA_ADMIN_FEATURE_DEVICE_ATTR_DESC_##cap##_MASK)

#घोषणा is_reserved_cleared(reserved) \
	!स_प्रथम_inv(reserved, 0, माप(reserved))

अटल व्योम *efa_zalloc_mapped(काष्ठा efa_dev *dev, dma_addr_t *dma_addr,
			       माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	व्योम *addr;

	addr = alloc_pages_exact(size, GFP_KERNEL | __GFP_ZERO);
	अगर (!addr)
		वापस शून्य;

	*dma_addr = dma_map_single(&dev->pdev->dev, addr, size, dir);
	अगर (dma_mapping_error(&dev->pdev->dev, *dma_addr)) अणु
		ibdev_err(&dev->ibdev, "Failed to map DMA address\n");
		मुक्त_pages_exact(addr, size);
		वापस शून्य;
	पूर्ण

	वापस addr;
पूर्ण

अटल व्योम efa_मुक्त_mapped(काष्ठा efa_dev *dev, व्योम *cpu_addr,
			    dma_addr_t dma_addr,
			    माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	dma_unmap_single(&dev->pdev->dev, dma_addr, size, dir);
	मुक्त_pages_exact(cpu_addr, size);
पूर्ण

पूर्णांक efa_query_device(काष्ठा ib_device *ibdev,
		     काष्ठा ib_device_attr *props,
		     काष्ठा ib_udata *udata)
अणु
	काष्ठा efa_com_get_device_attr_result *dev_attr;
	काष्ठा efa_ibv_ex_query_device_resp resp = अणुपूर्ण;
	काष्ठा efa_dev *dev = to_edev(ibdev);
	पूर्णांक err;

	अगर (udata && udata->inlen &&
	    !ib_is_udata_cleared(udata, 0, udata->inlen)) अणु
		ibdev_dbg(ibdev,
			  "Incompatible ABI params, udata not cleared\n");
		वापस -EINVAL;
	पूर्ण

	dev_attr = &dev->dev_attr;

	स_रखो(props, 0, माप(*props));
	props->max_mr_size = dev_attr->max_mr_pages * PAGE_SIZE;
	props->page_size_cap = dev_attr->page_size_cap;
	props->venकरोr_id = dev->pdev->venकरोr;
	props->venकरोr_part_id = dev->pdev->device;
	props->hw_ver = dev->pdev->subप्रणाली_device;
	props->max_qp = dev_attr->max_qp;
	props->max_cq = dev_attr->max_cq;
	props->max_pd = dev_attr->max_pd;
	props->max_mr = dev_attr->max_mr;
	props->max_ah = dev_attr->max_ah;
	props->max_cqe = dev_attr->max_cq_depth;
	props->max_qp_wr = min_t(u32, dev_attr->max_sq_depth,
				 dev_attr->max_rq_depth);
	props->max_send_sge = dev_attr->max_sq_sge;
	props->max_recv_sge = dev_attr->max_rq_sge;
	props->max_sge_rd = dev_attr->max_wr_rdma_sge;
	props->max_pkeys = 1;

	अगर (udata && udata->outlen) अणु
		resp.max_sq_sge = dev_attr->max_sq_sge;
		resp.max_rq_sge = dev_attr->max_rq_sge;
		resp.max_sq_wr = dev_attr->max_sq_depth;
		resp.max_rq_wr = dev_attr->max_rq_depth;
		resp.max_rdma_size = dev_attr->max_rdma_size;

		अगर (EFA_DEV_CAP(dev, RDMA_READ))
			resp.device_caps |= EFA_QUERY_DEVICE_CAPS_RDMA_READ;

		अगर (EFA_DEV_CAP(dev, RNR_RETRY))
			resp.device_caps |= EFA_QUERY_DEVICE_CAPS_RNR_RETRY;

		err = ib_copy_to_udata(udata, &resp,
				       min(माप(resp), udata->outlen));
		अगर (err) अणु
			ibdev_dbg(ibdev,
				  "Failed to copy udata for query_device\n");
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक efa_query_port(काष्ठा ib_device *ibdev, u32 port,
		   काष्ठा ib_port_attr *props)
अणु
	काष्ठा efa_dev *dev = to_edev(ibdev);

	props->lmc = 1;

	props->state = IB_PORT_ACTIVE;
	props->phys_state = IB_PORT_PHYS_STATE_LINK_UP;
	props->gid_tbl_len = 1;
	props->pkey_tbl_len = 1;
	props->active_speed = IB_SPEED_EDR;
	props->active_width = IB_WIDTH_4X;
	props->max_mtu = ib_mtu_पूर्णांक_to_क्रमागत(dev->dev_attr.mtu);
	props->active_mtu = ib_mtu_पूर्णांक_to_क्रमागत(dev->dev_attr.mtu);
	props->max_msg_sz = dev->dev_attr.mtu;
	props->max_vl_num = 1;

	वापस 0;
पूर्ण

पूर्णांक efa_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr,
		 पूर्णांक qp_attr_mask,
		 काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा efa_dev *dev = to_edev(ibqp->device);
	काष्ठा efa_com_query_qp_params params = अणुपूर्ण;
	काष्ठा efa_com_query_qp_result result;
	काष्ठा efa_qp *qp = to_eqp(ibqp);
	पूर्णांक err;

#घोषणा EFA_QUERY_QP_SUPP_MASK \
	(IB_QP_STATE | IB_QP_PKEY_INDEX | IB_QP_PORT | \
	 IB_QP_QKEY | IB_QP_SQ_PSN | IB_QP_CAP | IB_QP_RNR_RETRY)

	अगर (qp_attr_mask & ~EFA_QUERY_QP_SUPP_MASK) अणु
		ibdev_dbg(&dev->ibdev,
			  "Unsupported qp_attr_mask[%#x] supported[%#x]\n",
			  qp_attr_mask, EFA_QUERY_QP_SUPP_MASK);
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(qp_attr, 0, माप(*qp_attr));
	स_रखो(qp_init_attr, 0, माप(*qp_init_attr));

	params.qp_handle = qp->qp_handle;
	err = efa_com_query_qp(&dev->edev, &params, &result);
	अगर (err)
		वापस err;

	qp_attr->qp_state = result.qp_state;
	qp_attr->qkey = result.qkey;
	qp_attr->sq_psn = result.sq_psn;
	qp_attr->sq_draining = result.sq_draining;
	qp_attr->port_num = 1;
	qp_attr->rnr_retry = result.rnr_retry;

	qp_attr->cap.max_send_wr = qp->max_send_wr;
	qp_attr->cap.max_recv_wr = qp->max_recv_wr;
	qp_attr->cap.max_send_sge = qp->max_send_sge;
	qp_attr->cap.max_recv_sge = qp->max_recv_sge;
	qp_attr->cap.max_अंतरभूत_data = qp->max_अंतरभूत_data;

	qp_init_attr->qp_type = ibqp->qp_type;
	qp_init_attr->recv_cq = ibqp->recv_cq;
	qp_init_attr->send_cq = ibqp->send_cq;
	qp_init_attr->qp_context = ibqp->qp_context;
	qp_init_attr->cap = qp_attr->cap;

	वापस 0;
पूर्ण

पूर्णांक efa_query_gid(काष्ठा ib_device *ibdev, u32 port, पूर्णांक index,
		  जोड़ ib_gid *gid)
अणु
	काष्ठा efa_dev *dev = to_edev(ibdev);

	स_नकल(gid->raw, dev->dev_attr.addr, माप(dev->dev_attr.addr));

	वापस 0;
पूर्ण

पूर्णांक efa_query_pkey(काष्ठा ib_device *ibdev, u32 port, u16 index,
		   u16 *pkey)
अणु
	अगर (index > 0)
		वापस -EINVAL;

	*pkey = 0xffff;
	वापस 0;
पूर्ण

अटल पूर्णांक efa_pd_dealloc(काष्ठा efa_dev *dev, u16 pdn)
अणु
	काष्ठा efa_com_dealloc_pd_params params = अणु
		.pdn = pdn,
	पूर्ण;

	वापस efa_com_dealloc_pd(&dev->edev, &params);
पूर्ण

पूर्णांक efa_alloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा efa_dev *dev = to_edev(ibpd->device);
	काष्ठा efa_ibv_alloc_pd_resp resp = अणुपूर्ण;
	काष्ठा efa_com_alloc_pd_result result;
	काष्ठा efa_pd *pd = to_epd(ibpd);
	पूर्णांक err;

	अगर (udata->inlen &&
	    !ib_is_udata_cleared(udata, 0, udata->inlen)) अणु
		ibdev_dbg(&dev->ibdev,
			  "Incompatible ABI params, udata not cleared\n");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	err = efa_com_alloc_pd(&dev->edev, &result);
	अगर (err)
		जाओ err_out;

	pd->pdn = result.pdn;
	resp.pdn = result.pdn;

	अगर (udata->outlen) अणु
		err = ib_copy_to_udata(udata, &resp,
				       min(माप(resp), udata->outlen));
		अगर (err) अणु
			ibdev_dbg(&dev->ibdev,
				  "Failed to copy udata for alloc_pd\n");
			जाओ err_dealloc_pd;
		पूर्ण
	पूर्ण

	ibdev_dbg(&dev->ibdev, "Allocated pd[%d]\n", pd->pdn);

	वापस 0;

err_dealloc_pd:
	efa_pd_dealloc(dev, result.pdn);
err_out:
	atomic64_inc(&dev->stats.alloc_pd_err);
	वापस err;
पूर्ण

पूर्णांक efa_dealloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा efa_dev *dev = to_edev(ibpd->device);
	काष्ठा efa_pd *pd = to_epd(ibpd);

	ibdev_dbg(&dev->ibdev, "Dealloc pd[%d]\n", pd->pdn);
	efa_pd_dealloc(dev, pd->pdn);
	वापस 0;
पूर्ण

अटल पूर्णांक efa_destroy_qp_handle(काष्ठा efa_dev *dev, u32 qp_handle)
अणु
	काष्ठा efa_com_destroy_qp_params params = अणु .qp_handle = qp_handle पूर्ण;

	वापस efa_com_destroy_qp(&dev->edev, &params);
पूर्ण

अटल व्योम efa_qp_user_mmap_entries_हटाओ(काष्ठा efa_qp *qp)
अणु
	rdma_user_mmap_entry_हटाओ(qp->rq_mmap_entry);
	rdma_user_mmap_entry_हटाओ(qp->rq_db_mmap_entry);
	rdma_user_mmap_entry_हटाओ(qp->llq_desc_mmap_entry);
	rdma_user_mmap_entry_हटाओ(qp->sq_db_mmap_entry);
पूर्ण

पूर्णांक efa_destroy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_udata *udata)
अणु
	काष्ठा efa_dev *dev = to_edev(ibqp->pd->device);
	काष्ठा efa_qp *qp = to_eqp(ibqp);
	पूर्णांक err;

	ibdev_dbg(&dev->ibdev, "Destroy qp[%u]\n", ibqp->qp_num);

	efa_qp_user_mmap_entries_हटाओ(qp);

	err = efa_destroy_qp_handle(dev, qp->qp_handle);
	अगर (err)
		वापस err;

	अगर (qp->rq_cpu_addr) अणु
		ibdev_dbg(&dev->ibdev,
			  "qp->cpu_addr[0x%p] freed: size[%lu], dma[%pad]\n",
			  qp->rq_cpu_addr, qp->rq_size,
			  &qp->rq_dma_addr);
		efa_मुक्त_mapped(dev, qp->rq_cpu_addr, qp->rq_dma_addr,
				qp->rq_size, DMA_TO_DEVICE);
	पूर्ण

	kमुक्त(qp);
	वापस 0;
पूर्ण

अटल काष्ठा rdma_user_mmap_entry*
efa_user_mmap_entry_insert(काष्ठा ib_ucontext *ucontext,
			   u64 address, माप_प्रकार length,
			   u8 mmap_flag, u64 *offset)
अणु
	काष्ठा efa_user_mmap_entry *entry = kzalloc(माप(*entry), GFP_KERNEL);
	पूर्णांक err;

	अगर (!entry)
		वापस शून्य;

	entry->address = address;
	entry->mmap_flag = mmap_flag;

	err = rdma_user_mmap_entry_insert(ucontext, &entry->rdma_entry,
					  length);
	अगर (err) अणु
		kमुक्त(entry);
		वापस शून्य;
	पूर्ण
	*offset = rdma_user_mmap_get_offset(&entry->rdma_entry);

	वापस &entry->rdma_entry;
पूर्ण

अटल पूर्णांक qp_mmap_entries_setup(काष्ठा efa_qp *qp,
				 काष्ठा efa_dev *dev,
				 काष्ठा efa_ucontext *ucontext,
				 काष्ठा efa_com_create_qp_params *params,
				 काष्ठा efa_ibv_create_qp_resp *resp)
अणु
	माप_प्रकार length;
	u64 address;

	address = dev->db_bar_addr + resp->sq_db_offset;
	qp->sq_db_mmap_entry =
		efa_user_mmap_entry_insert(&ucontext->ibucontext,
					   address,
					   PAGE_SIZE, EFA_MMAP_IO_NC,
					   &resp->sq_db_mmap_key);
	अगर (!qp->sq_db_mmap_entry)
		वापस -ENOMEM;

	resp->sq_db_offset &= ~PAGE_MASK;

	address = dev->mem_bar_addr + resp->llq_desc_offset;
	length = PAGE_ALIGN(params->sq_ring_size_in_bytes +
			    (resp->llq_desc_offset & ~PAGE_MASK));

	qp->llq_desc_mmap_entry =
		efa_user_mmap_entry_insert(&ucontext->ibucontext,
					   address, length,
					   EFA_MMAP_IO_WC,
					   &resp->llq_desc_mmap_key);
	अगर (!qp->llq_desc_mmap_entry)
		जाओ err_हटाओ_mmap;

	resp->llq_desc_offset &= ~PAGE_MASK;

	अगर (qp->rq_size) अणु
		address = dev->db_bar_addr + resp->rq_db_offset;

		qp->rq_db_mmap_entry =
			efa_user_mmap_entry_insert(&ucontext->ibucontext,
						   address, PAGE_SIZE,
						   EFA_MMAP_IO_NC,
						   &resp->rq_db_mmap_key);
		अगर (!qp->rq_db_mmap_entry)
			जाओ err_हटाओ_mmap;

		resp->rq_db_offset &= ~PAGE_MASK;

		address = virt_to_phys(qp->rq_cpu_addr);
		qp->rq_mmap_entry =
			efa_user_mmap_entry_insert(&ucontext->ibucontext,
						   address, qp->rq_size,
						   EFA_MMAP_DMA_PAGE,
						   &resp->rq_mmap_key);
		अगर (!qp->rq_mmap_entry)
			जाओ err_हटाओ_mmap;

		resp->rq_mmap_size = qp->rq_size;
	पूर्ण

	वापस 0;

err_हटाओ_mmap:
	efa_qp_user_mmap_entries_हटाओ(qp);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक efa_qp_validate_cap(काष्ठा efa_dev *dev,
			       काष्ठा ib_qp_init_attr *init_attr)
अणु
	अगर (init_attr->cap.max_send_wr > dev->dev_attr.max_sq_depth) अणु
		ibdev_dbg(&dev->ibdev,
			  "qp: requested send wr[%u] exceeds the max[%u]\n",
			  init_attr->cap.max_send_wr,
			  dev->dev_attr.max_sq_depth);
		वापस -EINVAL;
	पूर्ण
	अगर (init_attr->cap.max_recv_wr > dev->dev_attr.max_rq_depth) अणु
		ibdev_dbg(&dev->ibdev,
			  "qp: requested receive wr[%u] exceeds the max[%u]\n",
			  init_attr->cap.max_recv_wr,
			  dev->dev_attr.max_rq_depth);
		वापस -EINVAL;
	पूर्ण
	अगर (init_attr->cap.max_send_sge > dev->dev_attr.max_sq_sge) अणु
		ibdev_dbg(&dev->ibdev,
			  "qp: requested sge send[%u] exceeds the max[%u]\n",
			  init_attr->cap.max_send_sge, dev->dev_attr.max_sq_sge);
		वापस -EINVAL;
	पूर्ण
	अगर (init_attr->cap.max_recv_sge > dev->dev_attr.max_rq_sge) अणु
		ibdev_dbg(&dev->ibdev,
			  "qp: requested sge recv[%u] exceeds the max[%u]\n",
			  init_attr->cap.max_recv_sge, dev->dev_attr.max_rq_sge);
		वापस -EINVAL;
	पूर्ण
	अगर (init_attr->cap.max_अंतरभूत_data > dev->dev_attr.अंतरभूत_buf_size) अणु
		ibdev_dbg(&dev->ibdev,
			  "qp: requested inline data[%u] exceeds the max[%u]\n",
			  init_attr->cap.max_अंतरभूत_data,
			  dev->dev_attr.अंतरभूत_buf_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक efa_qp_validate_attr(काष्ठा efa_dev *dev,
				काष्ठा ib_qp_init_attr *init_attr)
अणु
	अगर (init_attr->qp_type != IB_QPT_DRIVER &&
	    init_attr->qp_type != IB_QPT_UD) अणु
		ibdev_dbg(&dev->ibdev,
			  "Unsupported qp type %d\n", init_attr->qp_type);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (init_attr->srq) अणु
		ibdev_dbg(&dev->ibdev, "SRQ is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (init_attr->create_flags) अणु
		ibdev_dbg(&dev->ibdev, "Unsupported create flags\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा ib_qp *efa_create_qp(काष्ठा ib_pd *ibpd,
			    काष्ठा ib_qp_init_attr *init_attr,
			    काष्ठा ib_udata *udata)
अणु
	काष्ठा efa_com_create_qp_params create_qp_params = अणुपूर्ण;
	काष्ठा efa_com_create_qp_result create_qp_resp;
	काष्ठा efa_dev *dev = to_edev(ibpd->device);
	काष्ठा efa_ibv_create_qp_resp resp = अणुपूर्ण;
	काष्ठा efa_ibv_create_qp cmd = अणुपूर्ण;
	काष्ठा efa_ucontext *ucontext;
	काष्ठा efa_qp *qp;
	पूर्णांक err;

	ucontext = rdma_udata_to_drv_context(udata, काष्ठा efa_ucontext,
					     ibucontext);

	err = efa_qp_validate_cap(dev, init_attr);
	अगर (err)
		जाओ err_out;

	err = efa_qp_validate_attr(dev, init_attr);
	अगर (err)
		जाओ err_out;

	अगर (दुरत्वend(typeof(cmd), driver_qp_type) > udata->inlen) अणु
		ibdev_dbg(&dev->ibdev,
			  "Incompatible ABI params, no input udata\n");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	अगर (udata->inlen > माप(cmd) &&
	    !ib_is_udata_cleared(udata, माप(cmd),
				 udata->inlen - माप(cmd))) अणु
		ibdev_dbg(&dev->ibdev,
			  "Incompatible ABI params, unknown fields in udata\n");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	err = ib_copy_from_udata(&cmd, udata,
				 min(माप(cmd), udata->inlen));
	अगर (err) अणु
		ibdev_dbg(&dev->ibdev,
			  "Cannot copy udata for create_qp\n");
		जाओ err_out;
	पूर्ण

	अगर (cmd.comp_mask) अणु
		ibdev_dbg(&dev->ibdev,
			  "Incompatible ABI params, unknown fields in udata\n");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	qp = kzalloc(माप(*qp), GFP_KERNEL);
	अगर (!qp) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	create_qp_params.uarn = ucontext->uarn;
	create_qp_params.pd = to_epd(ibpd)->pdn;

	अगर (init_attr->qp_type == IB_QPT_UD) अणु
		create_qp_params.qp_type = EFA_ADMIN_QP_TYPE_UD;
	पूर्ण अन्यथा अगर (cmd.driver_qp_type == EFA_QP_DRIVER_TYPE_SRD) अणु
		create_qp_params.qp_type = EFA_ADMIN_QP_TYPE_SRD;
	पूर्ण अन्यथा अणु
		ibdev_dbg(&dev->ibdev,
			  "Unsupported qp type %d driver qp type %d\n",
			  init_attr->qp_type, cmd.driver_qp_type);
		err = -EOPNOTSUPP;
		जाओ err_मुक्त_qp;
	पूर्ण

	ibdev_dbg(&dev->ibdev, "Create QP: qp type %d driver qp type %#x\n",
		  init_attr->qp_type, cmd.driver_qp_type);
	create_qp_params.send_cq_idx = to_ecq(init_attr->send_cq)->cq_idx;
	create_qp_params.recv_cq_idx = to_ecq(init_attr->recv_cq)->cq_idx;
	create_qp_params.sq_depth = init_attr->cap.max_send_wr;
	create_qp_params.sq_ring_size_in_bytes = cmd.sq_ring_size;

	create_qp_params.rq_depth = init_attr->cap.max_recv_wr;
	create_qp_params.rq_ring_size_in_bytes = cmd.rq_ring_size;
	qp->rq_size = PAGE_ALIGN(create_qp_params.rq_ring_size_in_bytes);
	अगर (qp->rq_size) अणु
		qp->rq_cpu_addr = efa_zalloc_mapped(dev, &qp->rq_dma_addr,
						    qp->rq_size, DMA_TO_DEVICE);
		अगर (!qp->rq_cpu_addr) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_qp;
		पूर्ण

		ibdev_dbg(&dev->ibdev,
			  "qp->cpu_addr[0x%p] allocated: size[%lu], dma[%pad]\n",
			  qp->rq_cpu_addr, qp->rq_size, &qp->rq_dma_addr);
		create_qp_params.rq_base_addr = qp->rq_dma_addr;
	पूर्ण

	err = efa_com_create_qp(&dev->edev, &create_qp_params,
				&create_qp_resp);
	अगर (err)
		जाओ err_मुक्त_mapped;

	resp.sq_db_offset = create_qp_resp.sq_db_offset;
	resp.rq_db_offset = create_qp_resp.rq_db_offset;
	resp.llq_desc_offset = create_qp_resp.llq_descriptors_offset;
	resp.send_sub_cq_idx = create_qp_resp.send_sub_cq_idx;
	resp.recv_sub_cq_idx = create_qp_resp.recv_sub_cq_idx;

	err = qp_mmap_entries_setup(qp, dev, ucontext, &create_qp_params,
				    &resp);
	अगर (err)
		जाओ err_destroy_qp;

	qp->qp_handle = create_qp_resp.qp_handle;
	qp->ibqp.qp_num = create_qp_resp.qp_num;
	qp->ibqp.qp_type = init_attr->qp_type;
	qp->max_send_wr = init_attr->cap.max_send_wr;
	qp->max_recv_wr = init_attr->cap.max_recv_wr;
	qp->max_send_sge = init_attr->cap.max_send_sge;
	qp->max_recv_sge = init_attr->cap.max_recv_sge;
	qp->max_अंतरभूत_data = init_attr->cap.max_अंतरभूत_data;

	अगर (udata->outlen) अणु
		err = ib_copy_to_udata(udata, &resp,
				       min(माप(resp), udata->outlen));
		अगर (err) अणु
			ibdev_dbg(&dev->ibdev,
				  "Failed to copy udata for qp[%u]\n",
				  create_qp_resp.qp_num);
			जाओ err_हटाओ_mmap_entries;
		पूर्ण
	पूर्ण

	ibdev_dbg(&dev->ibdev, "Created qp[%d]\n", qp->ibqp.qp_num);

	वापस &qp->ibqp;

err_हटाओ_mmap_entries:
	efa_qp_user_mmap_entries_हटाओ(qp);
err_destroy_qp:
	efa_destroy_qp_handle(dev, create_qp_resp.qp_handle);
err_मुक्त_mapped:
	अगर (qp->rq_size)
		efa_मुक्त_mapped(dev, qp->rq_cpu_addr, qp->rq_dma_addr,
				qp->rq_size, DMA_TO_DEVICE);
err_मुक्त_qp:
	kमुक्त(qp);
err_out:
	atomic64_inc(&dev->stats.create_qp_err);
	वापस ERR_PTR(err);
पूर्ण

अटल स्थिर काष्ठा अणु
	पूर्णांक			valid;
	क्रमागत ib_qp_attr_mask	req_param;
	क्रमागत ib_qp_attr_mask	opt_param;
पूर्ण srd_qp_state_table[IB_QPS_ERR + 1][IB_QPS_ERR + 1] = अणु
	[IB_QPS_RESET] = अणु
		[IB_QPS_RESET] = अणु .valid = 1 पूर्ण,
		[IB_QPS_INIT]  = अणु
			.valid = 1,
			.req_param = IB_QP_PKEY_INDEX |
				     IB_QP_PORT |
				     IB_QP_QKEY,
		पूर्ण,
	पूर्ण,
	[IB_QPS_INIT] = अणु
		[IB_QPS_RESET] = अणु .valid = 1 पूर्ण,
		[IB_QPS_ERR]   = अणु .valid = 1 पूर्ण,
		[IB_QPS_INIT]  = अणु
			.valid = 1,
			.opt_param = IB_QP_PKEY_INDEX |
				     IB_QP_PORT |
				     IB_QP_QKEY,
		पूर्ण,
		[IB_QPS_RTR]   = अणु
			.valid = 1,
			.opt_param = IB_QP_PKEY_INDEX |
				     IB_QP_QKEY,
		पूर्ण,
	पूर्ण,
	[IB_QPS_RTR] = अणु
		[IB_QPS_RESET] = अणु .valid = 1 पूर्ण,
		[IB_QPS_ERR]   = अणु .valid = 1 पूर्ण,
		[IB_QPS_RTS]   = अणु
			.valid = 1,
			.req_param = IB_QP_SQ_PSN,
			.opt_param = IB_QP_CUR_STATE |
				     IB_QP_QKEY |
				     IB_QP_RNR_RETRY,

		पूर्ण
	पूर्ण,
	[IB_QPS_RTS] = अणु
		[IB_QPS_RESET] = अणु .valid = 1 पूर्ण,
		[IB_QPS_ERR]   = अणु .valid = 1 पूर्ण,
		[IB_QPS_RTS]   = अणु
			.valid = 1,
			.opt_param = IB_QP_CUR_STATE |
				     IB_QP_QKEY,
		पूर्ण,
		[IB_QPS_SQD] = अणु
			.valid = 1,
			.opt_param = IB_QP_EN_SQD_ASYNC_NOTIFY,
		पूर्ण,
	पूर्ण,
	[IB_QPS_SQD] = अणु
		[IB_QPS_RESET] = अणु .valid = 1 पूर्ण,
		[IB_QPS_ERR]   = अणु .valid = 1 पूर्ण,
		[IB_QPS_RTS]   = अणु
			.valid = 1,
			.opt_param = IB_QP_CUR_STATE |
				     IB_QP_QKEY,
		पूर्ण,
		[IB_QPS_SQD] = अणु
			.valid = 1,
			.opt_param = IB_QP_PKEY_INDEX |
				     IB_QP_QKEY,
		पूर्ण
	पूर्ण,
	[IB_QPS_SQE] = अणु
		[IB_QPS_RESET] = अणु .valid = 1 पूर्ण,
		[IB_QPS_ERR]   = अणु .valid = 1 पूर्ण,
		[IB_QPS_RTS]   = अणु
			.valid = 1,
			.opt_param = IB_QP_CUR_STATE |
				     IB_QP_QKEY,
		पूर्ण
	पूर्ण,
	[IB_QPS_ERR] = अणु
		[IB_QPS_RESET] = अणु .valid = 1 पूर्ण,
		[IB_QPS_ERR]   = अणु .valid = 1 पूर्ण,
	पूर्ण
पूर्ण;

अटल bool efa_modअगरy_srd_qp_is_ok(क्रमागत ib_qp_state cur_state,
				    क्रमागत ib_qp_state next_state,
				    क्रमागत ib_qp_attr_mask mask)
अणु
	क्रमागत ib_qp_attr_mask req_param, opt_param;

	अगर (mask & IB_QP_CUR_STATE  &&
	    cur_state != IB_QPS_RTR && cur_state != IB_QPS_RTS &&
	    cur_state != IB_QPS_SQD && cur_state != IB_QPS_SQE)
		वापस false;

	अगर (!srd_qp_state_table[cur_state][next_state].valid)
		वापस false;

	req_param = srd_qp_state_table[cur_state][next_state].req_param;
	opt_param = srd_qp_state_table[cur_state][next_state].opt_param;

	अगर ((mask & req_param) != req_param)
		वापस false;

	अगर (mask & ~(req_param | opt_param | IB_QP_STATE))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक efa_modअगरy_qp_validate(काष्ठा efa_dev *dev, काष्ठा efa_qp *qp,
				  काष्ठा ib_qp_attr *qp_attr, पूर्णांक qp_attr_mask,
				  क्रमागत ib_qp_state cur_state,
				  क्रमागत ib_qp_state new_state)
अणु
	पूर्णांक err;

#घोषणा EFA_MODIFY_QP_SUPP_MASK \
	(IB_QP_STATE | IB_QP_CUR_STATE | IB_QP_EN_SQD_ASYNC_NOTIFY | \
	 IB_QP_PKEY_INDEX | IB_QP_PORT | IB_QP_QKEY | IB_QP_SQ_PSN | \
	 IB_QP_RNR_RETRY)

	अगर (qp_attr_mask & ~EFA_MODIFY_QP_SUPP_MASK) अणु
		ibdev_dbg(&dev->ibdev,
			  "Unsupported qp_attr_mask[%#x] supported[%#x]\n",
			  qp_attr_mask, EFA_MODIFY_QP_SUPP_MASK);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (qp->ibqp.qp_type == IB_QPT_DRIVER)
		err = !efa_modअगरy_srd_qp_is_ok(cur_state, new_state,
					       qp_attr_mask);
	अन्यथा
		err = !ib_modअगरy_qp_is_ok(cur_state, new_state, IB_QPT_UD,
					  qp_attr_mask);

	अगर (err) अणु
		ibdev_dbg(&dev->ibdev, "Invalid modify QP parameters\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((qp_attr_mask & IB_QP_PORT) && qp_attr->port_num != 1) अणु
		ibdev_dbg(&dev->ibdev, "Can't change port num\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर ((qp_attr_mask & IB_QP_PKEY_INDEX) && qp_attr->pkey_index) अणु
		ibdev_dbg(&dev->ibdev, "Can't change pkey index\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक efa_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr,
		  पूर्णांक qp_attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा efa_dev *dev = to_edev(ibqp->device);
	काष्ठा efa_com_modअगरy_qp_params params = अणुपूर्ण;
	काष्ठा efa_qp *qp = to_eqp(ibqp);
	क्रमागत ib_qp_state cur_state;
	क्रमागत ib_qp_state new_state;
	पूर्णांक err;

	अगर (qp_attr_mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	अगर (udata->inlen &&
	    !ib_is_udata_cleared(udata, 0, udata->inlen)) अणु
		ibdev_dbg(&dev->ibdev,
			  "Incompatible ABI params, udata not cleared\n");
		वापस -EINVAL;
	पूर्ण

	cur_state = qp_attr_mask & IB_QP_CUR_STATE ? qp_attr->cur_qp_state :
						     qp->state;
	new_state = qp_attr_mask & IB_QP_STATE ? qp_attr->qp_state : cur_state;

	err = efa_modअगरy_qp_validate(dev, qp, qp_attr, qp_attr_mask, cur_state,
				     new_state);
	अगर (err)
		वापस err;

	params.qp_handle = qp->qp_handle;

	अगर (qp_attr_mask & IB_QP_STATE) अणु
		EFA_SET(&params.modअगरy_mask, EFA_ADMIN_MODIFY_QP_CMD_QP_STATE,
			1);
		EFA_SET(&params.modअगरy_mask,
			EFA_ADMIN_MODIFY_QP_CMD_CUR_QP_STATE, 1);
		params.cur_qp_state = cur_state;
		params.qp_state = new_state;
	पूर्ण

	अगर (qp_attr_mask & IB_QP_EN_SQD_ASYNC_NOTIFY) अणु
		EFA_SET(&params.modअगरy_mask,
			EFA_ADMIN_MODIFY_QP_CMD_SQ_DRAINED_ASYNC_NOTIFY, 1);
		params.sq_drained_async_notअगरy = qp_attr->en_sqd_async_notअगरy;
	पूर्ण

	अगर (qp_attr_mask & IB_QP_QKEY) अणु
		EFA_SET(&params.modअगरy_mask, EFA_ADMIN_MODIFY_QP_CMD_QKEY, 1);
		params.qkey = qp_attr->qkey;
	पूर्ण

	अगर (qp_attr_mask & IB_QP_SQ_PSN) अणु
		EFA_SET(&params.modअगरy_mask, EFA_ADMIN_MODIFY_QP_CMD_SQ_PSN, 1);
		params.sq_psn = qp_attr->sq_psn;
	पूर्ण

	अगर (qp_attr_mask & IB_QP_RNR_RETRY) अणु
		EFA_SET(&params.modअगरy_mask, EFA_ADMIN_MODIFY_QP_CMD_RNR_RETRY,
			1);
		params.rnr_retry = qp_attr->rnr_retry;
	पूर्ण

	err = efa_com_modअगरy_qp(&dev->edev, &params);
	अगर (err)
		वापस err;

	qp->state = new_state;

	वापस 0;
पूर्ण

अटल पूर्णांक efa_destroy_cq_idx(काष्ठा efa_dev *dev, पूर्णांक cq_idx)
अणु
	काष्ठा efa_com_destroy_cq_params params = अणु .cq_idx = cq_idx पूर्ण;

	वापस efa_com_destroy_cq(&dev->edev, &params);
पूर्ण

पूर्णांक efa_destroy_cq(काष्ठा ib_cq *ibcq, काष्ठा ib_udata *udata)
अणु
	काष्ठा efa_dev *dev = to_edev(ibcq->device);
	काष्ठा efa_cq *cq = to_ecq(ibcq);

	ibdev_dbg(&dev->ibdev,
		  "Destroy cq[%d] virt[0x%p] freed: size[%lu], dma[%pad]\n",
		  cq->cq_idx, cq->cpu_addr, cq->size, &cq->dma_addr);

	rdma_user_mmap_entry_हटाओ(cq->mmap_entry);
	efa_destroy_cq_idx(dev, cq->cq_idx);
	efa_मुक्त_mapped(dev, cq->cpu_addr, cq->dma_addr, cq->size,
			DMA_FROM_DEVICE);
	वापस 0;
पूर्ण

अटल पूर्णांक cq_mmap_entries_setup(काष्ठा efa_dev *dev, काष्ठा efa_cq *cq,
				 काष्ठा efa_ibv_create_cq_resp *resp)
अणु
	resp->q_mmap_size = cq->size;
	cq->mmap_entry = efa_user_mmap_entry_insert(&cq->ucontext->ibucontext,
						    virt_to_phys(cq->cpu_addr),
						    cq->size, EFA_MMAP_DMA_PAGE,
						    &resp->q_mmap_key);
	अगर (!cq->mmap_entry)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक efa_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		  काष्ठा ib_udata *udata)
अणु
	काष्ठा efa_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा efa_ucontext, ibucontext);
	काष्ठा efa_ibv_create_cq_resp resp = अणुपूर्ण;
	काष्ठा efa_com_create_cq_params params;
	काष्ठा efa_com_create_cq_result result;
	काष्ठा ib_device *ibdev = ibcq->device;
	काष्ठा efa_dev *dev = to_edev(ibdev);
	काष्ठा efa_ibv_create_cq cmd = अणुपूर्ण;
	काष्ठा efa_cq *cq = to_ecq(ibcq);
	पूर्णांक entries = attr->cqe;
	पूर्णांक err;

	ibdev_dbg(ibdev, "create_cq entries %d\n", entries);

	अगर (attr->flags)
		वापस -EOPNOTSUPP;

	अगर (entries < 1 || entries > dev->dev_attr.max_cq_depth) अणु
		ibdev_dbg(ibdev,
			  "cq: requested entries[%u] non-positive or greater than max[%u]\n",
			  entries, dev->dev_attr.max_cq_depth);
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	अगर (दुरत्वend(typeof(cmd), num_sub_cqs) > udata->inlen) अणु
		ibdev_dbg(ibdev,
			  "Incompatible ABI params, no input udata\n");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	अगर (udata->inlen > माप(cmd) &&
	    !ib_is_udata_cleared(udata, माप(cmd),
				 udata->inlen - माप(cmd))) अणु
		ibdev_dbg(ibdev,
			  "Incompatible ABI params, unknown fields in udata\n");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	err = ib_copy_from_udata(&cmd, udata,
				 min(माप(cmd), udata->inlen));
	अगर (err) अणु
		ibdev_dbg(ibdev, "Cannot copy udata for create_cq\n");
		जाओ err_out;
	पूर्ण

	अगर (cmd.comp_mask || !is_reserved_cleared(cmd.reserved_50)) अणु
		ibdev_dbg(ibdev,
			  "Incompatible ABI params, unknown fields in udata\n");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	अगर (!cmd.cq_entry_size) अणु
		ibdev_dbg(ibdev,
			  "Invalid entry size [%u]\n", cmd.cq_entry_size);
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	अगर (cmd.num_sub_cqs != dev->dev_attr.sub_cqs_per_cq) अणु
		ibdev_dbg(ibdev,
			  "Invalid number of sub cqs[%u] expected[%u]\n",
			  cmd.num_sub_cqs, dev->dev_attr.sub_cqs_per_cq);
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	cq->ucontext = ucontext;
	cq->size = PAGE_ALIGN(cmd.cq_entry_size * entries * cmd.num_sub_cqs);
	cq->cpu_addr = efa_zalloc_mapped(dev, &cq->dma_addr, cq->size,
					 DMA_FROM_DEVICE);
	अगर (!cq->cpu_addr) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	params.uarn = cq->ucontext->uarn;
	params.cq_depth = entries;
	params.dma_addr = cq->dma_addr;
	params.entry_size_in_bytes = cmd.cq_entry_size;
	params.num_sub_cqs = cmd.num_sub_cqs;
	err = efa_com_create_cq(&dev->edev, &params, &result);
	अगर (err)
		जाओ err_मुक्त_mapped;

	resp.cq_idx = result.cq_idx;
	cq->cq_idx = result.cq_idx;
	cq->ibcq.cqe = result.actual_depth;
	WARN_ON_ONCE(entries != result.actual_depth);

	err = cq_mmap_entries_setup(dev, cq, &resp);
	अगर (err) अणु
		ibdev_dbg(ibdev, "Could not setup cq[%u] mmap entries\n",
			  cq->cq_idx);
		जाओ err_destroy_cq;
	पूर्ण

	अगर (udata->outlen) अणु
		err = ib_copy_to_udata(udata, &resp,
				       min(माप(resp), udata->outlen));
		अगर (err) अणु
			ibdev_dbg(ibdev,
				  "Failed to copy udata for create_cq\n");
			जाओ err_हटाओ_mmap;
		पूर्ण
	पूर्ण

	ibdev_dbg(ibdev, "Created cq[%d], cq depth[%u]. dma[%pad] virt[0x%p]\n",
		  cq->cq_idx, result.actual_depth, &cq->dma_addr, cq->cpu_addr);

	वापस 0;

err_हटाओ_mmap:
	rdma_user_mmap_entry_हटाओ(cq->mmap_entry);
err_destroy_cq:
	efa_destroy_cq_idx(dev, cq->cq_idx);
err_मुक्त_mapped:
	efa_मुक्त_mapped(dev, cq->cpu_addr, cq->dma_addr, cq->size,
			DMA_FROM_DEVICE);

err_out:
	atomic64_inc(&dev->stats.create_cq_err);
	वापस err;
पूर्ण

अटल पूर्णांक umem_to_page_list(काष्ठा efa_dev *dev,
			     काष्ठा ib_umem *umem,
			     u64 *page_list,
			     u32 hp_cnt,
			     u8 hp_shअगरt)
अणु
	u32 pages_in_hp = BIT(hp_shअगरt - PAGE_SHIFT);
	काष्ठा ib_block_iter biter;
	अचिन्हित पूर्णांक hp_idx = 0;

	ibdev_dbg(&dev->ibdev, "hp_cnt[%u], pages_in_hp[%u]\n",
		  hp_cnt, pages_in_hp);

	rdma_umem_क्रम_each_dma_block(umem, &biter, BIT(hp_shअगरt))
		page_list[hp_idx++] = rdma_block_iter_dma_address(&biter);

	वापस 0;
पूर्ण

अटल काष्ठा scatterlist *efa_vदो_स्मृति_buf_to_sg(u64 *buf, पूर्णांक page_cnt)
अणु
	काष्ठा scatterlist *sglist;
	काष्ठा page *pg;
	पूर्णांक i;

	sglist = kदो_स्मृति_array(page_cnt, माप(*sglist), GFP_KERNEL);
	अगर (!sglist)
		वापस शून्य;
	sg_init_table(sglist, page_cnt);
	क्रम (i = 0; i < page_cnt; i++) अणु
		pg = vदो_स्मृति_to_page(buf);
		अगर (!pg)
			जाओ err;
		sg_set_page(&sglist[i], pg, PAGE_SIZE, 0);
		buf += PAGE_SIZE / माप(*buf);
	पूर्ण
	वापस sglist;

err:
	kमुक्त(sglist);
	वापस शून्य;
पूर्ण

/*
 * create a chunk list of physical pages dma addresses from the supplied
 * scatter gather list
 */
अटल पूर्णांक pbl_chunk_list_create(काष्ठा efa_dev *dev, काष्ठा pbl_context *pbl)
अणु
	काष्ठा pbl_chunk_list *chunk_list = &pbl->phys.indirect.chunk_list;
	पूर्णांक page_cnt = pbl->phys.indirect.pbl_buf_size_in_pages;
	काष्ठा scatterlist *pages_sgl = pbl->phys.indirect.sgl;
	अचिन्हित पूर्णांक chunk_list_size, chunk_idx, payload_idx;
	पूर्णांक sg_dma_cnt = pbl->phys.indirect.sg_dma_cnt;
	काष्ठा efa_com_ctrl_buff_info *ctrl_buf;
	u64 *cur_chunk_buf, *prev_chunk_buf;
	काष्ठा ib_block_iter biter;
	dma_addr_t dma_addr;
	पूर्णांक i;

	/* allocate a chunk list that consists of 4KB chunks */
	chunk_list_size = DIV_ROUND_UP(page_cnt, EFA_PTRS_PER_CHUNK);

	chunk_list->size = chunk_list_size;
	chunk_list->chunks = kसुस्मृति(chunk_list_size,
				     माप(*chunk_list->chunks),
				     GFP_KERNEL);
	अगर (!chunk_list->chunks)
		वापस -ENOMEM;

	ibdev_dbg(&dev->ibdev,
		  "chunk_list_size[%u] - pages[%u]\n", chunk_list_size,
		  page_cnt);

	/* allocate chunk buffers: */
	क्रम (i = 0; i < chunk_list_size; i++) अणु
		chunk_list->chunks[i].buf = kzalloc(EFA_CHUNK_SIZE, GFP_KERNEL);
		अगर (!chunk_list->chunks[i].buf)
			जाओ chunk_list_dealloc;

		chunk_list->chunks[i].length = EFA_CHUNK_USED_SIZE;
	पूर्ण
	chunk_list->chunks[chunk_list_size - 1].length =
		((page_cnt % EFA_PTRS_PER_CHUNK) * EFA_CHUNK_PAYLOAD_PTR_SIZE) +
			EFA_CHUNK_PTR_SIZE;

	/* fill the dma addresses of sg list pages to chunks: */
	chunk_idx = 0;
	payload_idx = 0;
	cur_chunk_buf = chunk_list->chunks[0].buf;
	rdma_क्रम_each_block(pages_sgl, &biter, sg_dma_cnt,
			    EFA_CHUNK_PAYLOAD_SIZE) अणु
		cur_chunk_buf[payload_idx++] =
			rdma_block_iter_dma_address(&biter);

		अगर (payload_idx == EFA_PTRS_PER_CHUNK) अणु
			chunk_idx++;
			cur_chunk_buf = chunk_list->chunks[chunk_idx].buf;
			payload_idx = 0;
		पूर्ण
	पूर्ण

	/* map chunks to dma and fill chunks next ptrs */
	क्रम (i = chunk_list_size - 1; i >= 0; i--) अणु
		dma_addr = dma_map_single(&dev->pdev->dev,
					  chunk_list->chunks[i].buf,
					  chunk_list->chunks[i].length,
					  DMA_TO_DEVICE);
		अगर (dma_mapping_error(&dev->pdev->dev, dma_addr)) अणु
			ibdev_err(&dev->ibdev,
				  "chunk[%u] dma_map_failed\n", i);
			जाओ chunk_list_unmap;
		पूर्ण

		chunk_list->chunks[i].dma_addr = dma_addr;
		ibdev_dbg(&dev->ibdev,
			  "chunk[%u] mapped at [%pad]\n", i, &dma_addr);

		अगर (!i)
			अवरोध;

		prev_chunk_buf = chunk_list->chunks[i - 1].buf;

		ctrl_buf = (काष्ठा efa_com_ctrl_buff_info *)
				&prev_chunk_buf[EFA_PTRS_PER_CHUNK];
		ctrl_buf->length = chunk_list->chunks[i].length;

		efa_com_set_dma_addr(dma_addr,
				     &ctrl_buf->address.mem_addr_high,
				     &ctrl_buf->address.mem_addr_low);
	पूर्ण

	वापस 0;

chunk_list_unmap:
	क्रम (; i < chunk_list_size; i++) अणु
		dma_unmap_single(&dev->pdev->dev, chunk_list->chunks[i].dma_addr,
				 chunk_list->chunks[i].length, DMA_TO_DEVICE);
	पूर्ण
chunk_list_dealloc:
	क्रम (i = 0; i < chunk_list_size; i++)
		kमुक्त(chunk_list->chunks[i].buf);

	kमुक्त(chunk_list->chunks);
	वापस -ENOMEM;
पूर्ण

अटल व्योम pbl_chunk_list_destroy(काष्ठा efa_dev *dev, काष्ठा pbl_context *pbl)
अणु
	काष्ठा pbl_chunk_list *chunk_list = &pbl->phys.indirect.chunk_list;
	पूर्णांक i;

	क्रम (i = 0; i < chunk_list->size; i++) अणु
		dma_unmap_single(&dev->pdev->dev, chunk_list->chunks[i].dma_addr,
				 chunk_list->chunks[i].length, DMA_TO_DEVICE);
		kमुक्त(chunk_list->chunks[i].buf);
	पूर्ण

	kमुक्त(chunk_list->chunks);
पूर्ण

/* initialize pbl continuous mode: map pbl buffer to a dma address. */
अटल पूर्णांक pbl_continuous_initialize(काष्ठा efa_dev *dev,
				     काष्ठा pbl_context *pbl)
अणु
	dma_addr_t dma_addr;

	dma_addr = dma_map_single(&dev->pdev->dev, pbl->pbl_buf,
				  pbl->pbl_buf_size_in_bytes, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&dev->pdev->dev, dma_addr)) अणु
		ibdev_err(&dev->ibdev, "Unable to map pbl to DMA address\n");
		वापस -ENOMEM;
	पूर्ण

	pbl->phys.continuous.dma_addr = dma_addr;
	ibdev_dbg(&dev->ibdev,
		  "pbl continuous - dma_addr = %pad, size[%u]\n",
		  &dma_addr, pbl->pbl_buf_size_in_bytes);

	वापस 0;
पूर्ण

/*
 * initialize pbl indirect mode:
 * create a chunk list out of the dma addresses of the physical pages of
 * pbl buffer.
 */
अटल पूर्णांक pbl_indirect_initialize(काष्ठा efa_dev *dev, काष्ठा pbl_context *pbl)
अणु
	u32 size_in_pages = DIV_ROUND_UP(pbl->pbl_buf_size_in_bytes, PAGE_SIZE);
	काष्ठा scatterlist *sgl;
	पूर्णांक sg_dma_cnt, err;

	BUILD_BUG_ON(EFA_CHUNK_PAYLOAD_SIZE > PAGE_SIZE);
	sgl = efa_vदो_स्मृति_buf_to_sg(pbl->pbl_buf, size_in_pages);
	अगर (!sgl)
		वापस -ENOMEM;

	sg_dma_cnt = dma_map_sg(&dev->pdev->dev, sgl, size_in_pages, DMA_TO_DEVICE);
	अगर (!sg_dma_cnt) अणु
		err = -EINVAL;
		जाओ err_map;
	पूर्ण

	pbl->phys.indirect.pbl_buf_size_in_pages = size_in_pages;
	pbl->phys.indirect.sgl = sgl;
	pbl->phys.indirect.sg_dma_cnt = sg_dma_cnt;
	err = pbl_chunk_list_create(dev, pbl);
	अगर (err) अणु
		ibdev_dbg(&dev->ibdev,
			  "chunk_list creation failed[%d]\n", err);
		जाओ err_chunk;
	पूर्ण

	ibdev_dbg(&dev->ibdev,
		  "pbl indirect - size[%u], chunks[%u]\n",
		  pbl->pbl_buf_size_in_bytes,
		  pbl->phys.indirect.chunk_list.size);

	वापस 0;

err_chunk:
	dma_unmap_sg(&dev->pdev->dev, sgl, size_in_pages, DMA_TO_DEVICE);
err_map:
	kमुक्त(sgl);
	वापस err;
पूर्ण

अटल व्योम pbl_indirect_terminate(काष्ठा efa_dev *dev, काष्ठा pbl_context *pbl)
अणु
	pbl_chunk_list_destroy(dev, pbl);
	dma_unmap_sg(&dev->pdev->dev, pbl->phys.indirect.sgl,
		     pbl->phys.indirect.pbl_buf_size_in_pages, DMA_TO_DEVICE);
	kमुक्त(pbl->phys.indirect.sgl);
पूर्ण

/* create a page buffer list from a mapped user memory region */
अटल पूर्णांक pbl_create(काष्ठा efa_dev *dev,
		      काष्ठा pbl_context *pbl,
		      काष्ठा ib_umem *umem,
		      पूर्णांक hp_cnt,
		      u8 hp_shअगरt)
अणु
	पूर्णांक err;

	pbl->pbl_buf_size_in_bytes = hp_cnt * EFA_CHUNK_PAYLOAD_PTR_SIZE;
	pbl->pbl_buf = kvzalloc(pbl->pbl_buf_size_in_bytes, GFP_KERNEL);
	अगर (!pbl->pbl_buf)
		वापस -ENOMEM;

	अगर (is_vदो_स्मृति_addr(pbl->pbl_buf)) अणु
		pbl->physically_continuous = 0;
		err = umem_to_page_list(dev, umem, pbl->pbl_buf, hp_cnt,
					hp_shअगरt);
		अगर (err)
			जाओ err_मुक्त;

		err = pbl_indirect_initialize(dev, pbl);
		अगर (err)
			जाओ err_मुक्त;
	पूर्ण अन्यथा अणु
		pbl->physically_continuous = 1;
		err = umem_to_page_list(dev, umem, pbl->pbl_buf, hp_cnt,
					hp_shअगरt);
		अगर (err)
			जाओ err_मुक्त;

		err = pbl_continuous_initialize(dev, pbl);
		अगर (err)
			जाओ err_मुक्त;
	पूर्ण

	ibdev_dbg(&dev->ibdev,
		  "user_pbl_created: user_pages[%u], continuous[%u]\n",
		  hp_cnt, pbl->physically_continuous);

	वापस 0;

err_मुक्त:
	kvमुक्त(pbl->pbl_buf);
	वापस err;
पूर्ण

अटल व्योम pbl_destroy(काष्ठा efa_dev *dev, काष्ठा pbl_context *pbl)
अणु
	अगर (pbl->physically_continuous)
		dma_unmap_single(&dev->pdev->dev, pbl->phys.continuous.dma_addr,
				 pbl->pbl_buf_size_in_bytes, DMA_TO_DEVICE);
	अन्यथा
		pbl_indirect_terminate(dev, pbl);

	kvमुक्त(pbl->pbl_buf);
पूर्ण

अटल पूर्णांक efa_create_अंतरभूत_pbl(काष्ठा efa_dev *dev, काष्ठा efa_mr *mr,
				 काष्ठा efa_com_reg_mr_params *params)
अणु
	पूर्णांक err;

	params->अंतरभूत_pbl = 1;
	err = umem_to_page_list(dev, mr->umem, params->pbl.अंतरभूत_pbl_array,
				params->page_num, params->page_shअगरt);
	अगर (err)
		वापस err;

	ibdev_dbg(&dev->ibdev,
		  "inline_pbl_array - pages[%u]\n", params->page_num);

	वापस 0;
पूर्ण

अटल पूर्णांक efa_create_pbl(काष्ठा efa_dev *dev,
			  काष्ठा pbl_context *pbl,
			  काष्ठा efa_mr *mr,
			  काष्ठा efa_com_reg_mr_params *params)
अणु
	पूर्णांक err;

	err = pbl_create(dev, pbl, mr->umem, params->page_num,
			 params->page_shअगरt);
	अगर (err) अणु
		ibdev_dbg(&dev->ibdev, "Failed to create pbl[%d]\n", err);
		वापस err;
	पूर्ण

	params->अंतरभूत_pbl = 0;
	params->indirect = !pbl->physically_continuous;
	अगर (pbl->physically_continuous) अणु
		params->pbl.pbl.length = pbl->pbl_buf_size_in_bytes;

		efa_com_set_dma_addr(pbl->phys.continuous.dma_addr,
				     &params->pbl.pbl.address.mem_addr_high,
				     &params->pbl.pbl.address.mem_addr_low);
	पूर्ण अन्यथा अणु
		params->pbl.pbl.length =
			pbl->phys.indirect.chunk_list.chunks[0].length;

		efa_com_set_dma_addr(pbl->phys.indirect.chunk_list.chunks[0].dma_addr,
				     &params->pbl.pbl.address.mem_addr_high,
				     &params->pbl.pbl.address.mem_addr_low);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा ib_mr *efa_reg_mr(काष्ठा ib_pd *ibpd, u64 start, u64 length,
			 u64 virt_addr, पूर्णांक access_flags,
			 काष्ठा ib_udata *udata)
अणु
	काष्ठा efa_dev *dev = to_edev(ibpd->device);
	काष्ठा efa_com_reg_mr_params params = अणुपूर्ण;
	काष्ठा efa_com_reg_mr_result result = अणुपूर्ण;
	काष्ठा pbl_context pbl;
	पूर्णांक supp_access_flags;
	अचिन्हित पूर्णांक pg_sz;
	काष्ठा efa_mr *mr;
	पूर्णांक अंतरभूत_size;
	पूर्णांक err;

	अगर (udata && udata->inlen &&
	    !ib_is_udata_cleared(udata, 0, माप(udata->inlen))) अणु
		ibdev_dbg(&dev->ibdev,
			  "Incompatible ABI params, udata not cleared\n");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	supp_access_flags =
		IB_ACCESS_LOCAL_WRITE |
		(EFA_DEV_CAP(dev, RDMA_READ) ? IB_ACCESS_REMOTE_READ : 0);

	access_flags &= ~IB_ACCESS_OPTIONAL;
	अगर (access_flags & ~supp_access_flags) अणु
		ibdev_dbg(&dev->ibdev,
			  "Unsupported access flags[%#x], supported[%#x]\n",
			  access_flags, supp_access_flags);
		err = -EOPNOTSUPP;
		जाओ err_out;
	पूर्ण

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	mr->umem = ib_umem_get(ibpd->device, start, length, access_flags);
	अगर (IS_ERR(mr->umem)) अणु
		err = PTR_ERR(mr->umem);
		ibdev_dbg(&dev->ibdev,
			  "Failed to pin and map user space memory[%d]\n", err);
		जाओ err_मुक्त;
	पूर्ण

	params.pd = to_epd(ibpd)->pdn;
	params.iova = virt_addr;
	params.mr_length_in_bytes = length;
	params.permissions = access_flags;

	pg_sz = ib_umem_find_best_pgsz(mr->umem,
				       dev->dev_attr.page_size_cap,
				       virt_addr);
	अगर (!pg_sz) अणु
		err = -EOPNOTSUPP;
		ibdev_dbg(&dev->ibdev, "Failed to find a suitable page size in page_size_cap %#llx\n",
			  dev->dev_attr.page_size_cap);
		जाओ err_unmap;
	पूर्ण

	params.page_shअगरt = order_base_2(pg_sz);
	params.page_num = ib_umem_num_dma_blocks(mr->umem, pg_sz);

	ibdev_dbg(&dev->ibdev,
		  "start %#llx length %#llx params.page_shift %u params.page_num %u\n",
		  start, length, params.page_shअगरt, params.page_num);

	अंतरभूत_size = ARRAY_SIZE(params.pbl.अंतरभूत_pbl_array);
	अगर (params.page_num <= अंतरभूत_size) अणु
		err = efa_create_अंतरभूत_pbl(dev, mr, &params);
		अगर (err)
			जाओ err_unmap;

		err = efa_com_रेजिस्टर_mr(&dev->edev, &params, &result);
		अगर (err)
			जाओ err_unmap;
	पूर्ण अन्यथा अणु
		err = efa_create_pbl(dev, &pbl, mr, &params);
		अगर (err)
			जाओ err_unmap;

		err = efa_com_रेजिस्टर_mr(&dev->edev, &params, &result);
		pbl_destroy(dev, &pbl);

		अगर (err)
			जाओ err_unmap;
	पूर्ण

	mr->ibmr.lkey = result.l_key;
	mr->ibmr.rkey = result.r_key;
	mr->ibmr.length = length;
	ibdev_dbg(&dev->ibdev, "Registered mr[%d]\n", mr->ibmr.lkey);

	वापस &mr->ibmr;

err_unmap:
	ib_umem_release(mr->umem);
err_मुक्त:
	kमुक्त(mr);
err_out:
	atomic64_inc(&dev->stats.reg_mr_err);
	वापस ERR_PTR(err);
पूर्ण

पूर्णांक efa_dereg_mr(काष्ठा ib_mr *ibmr, काष्ठा ib_udata *udata)
अणु
	काष्ठा efa_dev *dev = to_edev(ibmr->device);
	काष्ठा efa_com_dereg_mr_params params;
	काष्ठा efa_mr *mr = to_emr(ibmr);
	पूर्णांक err;

	ibdev_dbg(&dev->ibdev, "Deregister mr[%d]\n", ibmr->lkey);

	params.l_key = mr->ibmr.lkey;
	err = efa_com_dereg_mr(&dev->edev, &params);
	अगर (err)
		वापस err;

	ib_umem_release(mr->umem);
	kमुक्त(mr);

	वापस 0;
पूर्ण

पूर्णांक efa_get_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
			   काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा ib_port_attr attr;
	पूर्णांक err;

	err = ib_query_port(ibdev, port_num, &attr);
	अगर (err) अणु
		ibdev_dbg(ibdev, "Couldn't query port err[%d]\n", err);
		वापस err;
	पूर्ण

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;

	वापस 0;
पूर्ण

अटल पूर्णांक efa_dealloc_uar(काष्ठा efa_dev *dev, u16 uarn)
अणु
	काष्ठा efa_com_dealloc_uar_params params = अणु
		.uarn = uarn,
	पूर्ण;

	वापस efa_com_dealloc_uar(&dev->edev, &params);
पूर्ण

#घोषणा EFA_CHECK_USER_COMP(_dev, _comp_mask, _attr, _mask, _attr_str) \
	(_attr_str = (!(_dev)->dev_attr._attr || ((_comp_mask) & (_mask))) ? \
		     शून्य : #_attr)

अटल पूर्णांक efa_user_comp_handshake(स्थिर काष्ठा ib_ucontext *ibucontext,
				   स्थिर काष्ठा efa_ibv_alloc_ucontext_cmd *cmd)
अणु
	काष्ठा efa_dev *dev = to_edev(ibucontext->device);
	अक्षर *attr_str;

	अगर (EFA_CHECK_USER_COMP(dev, cmd->comp_mask, max_tx_batch,
				EFA_ALLOC_UCONTEXT_CMD_COMP_TX_BATCH, attr_str))
		जाओ err;

	अगर (EFA_CHECK_USER_COMP(dev, cmd->comp_mask, min_sq_depth,
				EFA_ALLOC_UCONTEXT_CMD_COMP_MIN_SQ_WR,
				attr_str))
		जाओ err;

	वापस 0;

err:
	ibdev_dbg(&dev->ibdev, "Userspace handshake failed for %s attribute\n",
		  attr_str);
	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक efa_alloc_ucontext(काष्ठा ib_ucontext *ibucontext, काष्ठा ib_udata *udata)
अणु
	काष्ठा efa_ucontext *ucontext = to_eucontext(ibucontext);
	काष्ठा efa_dev *dev = to_edev(ibucontext->device);
	काष्ठा efa_ibv_alloc_ucontext_resp resp = अणुपूर्ण;
	काष्ठा efa_ibv_alloc_ucontext_cmd cmd = अणुपूर्ण;
	काष्ठा efa_com_alloc_uar_result result;
	पूर्णांक err;

	/*
	 * it's fine अगर the driver करोes not know all request fields,
	 * we will ack input fields in our response.
	 */

	err = ib_copy_from_udata(&cmd, udata,
				 min(माप(cmd), udata->inlen));
	अगर (err) अणु
		ibdev_dbg(&dev->ibdev,
			  "Cannot copy udata for alloc_ucontext\n");
		जाओ err_out;
	पूर्ण

	err = efa_user_comp_handshake(ibucontext, &cmd);
	अगर (err)
		जाओ err_out;

	err = efa_com_alloc_uar(&dev->edev, &result);
	अगर (err)
		जाओ err_out;

	ucontext->uarn = result.uarn;

	resp.cmds_supp_udata_mask |= EFA_USER_CMDS_SUPP_UDATA_QUERY_DEVICE;
	resp.cmds_supp_udata_mask |= EFA_USER_CMDS_SUPP_UDATA_CREATE_AH;
	resp.sub_cqs_per_cq = dev->dev_attr.sub_cqs_per_cq;
	resp.अंतरभूत_buf_size = dev->dev_attr.अंतरभूत_buf_size;
	resp.max_llq_size = dev->dev_attr.max_llq_size;
	resp.max_tx_batch = dev->dev_attr.max_tx_batch;
	resp.min_sq_wr = dev->dev_attr.min_sq_depth;

	err = ib_copy_to_udata(udata, &resp,
			       min(माप(resp), udata->outlen));
	अगर (err)
		जाओ err_dealloc_uar;

	वापस 0;

err_dealloc_uar:
	efa_dealloc_uar(dev, result.uarn);
err_out:
	atomic64_inc(&dev->stats.alloc_ucontext_err);
	वापस err;
पूर्ण

व्योम efa_dealloc_ucontext(काष्ठा ib_ucontext *ibucontext)
अणु
	काष्ठा efa_ucontext *ucontext = to_eucontext(ibucontext);
	काष्ठा efa_dev *dev = to_edev(ibucontext->device);

	efa_dealloc_uar(dev, ucontext->uarn);
पूर्ण

व्योम efa_mmap_मुक्त(काष्ठा rdma_user_mmap_entry *rdma_entry)
अणु
	काष्ठा efa_user_mmap_entry *entry = to_emmap(rdma_entry);

	kमुक्त(entry);
पूर्ण

अटल पूर्णांक __efa_mmap(काष्ठा efa_dev *dev, काष्ठा efa_ucontext *ucontext,
		      काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा rdma_user_mmap_entry *rdma_entry;
	काष्ठा efa_user_mmap_entry *entry;
	अचिन्हित दीर्घ va;
	पूर्णांक err = 0;
	u64 pfn;

	rdma_entry = rdma_user_mmap_entry_get(&ucontext->ibucontext, vma);
	अगर (!rdma_entry) अणु
		ibdev_dbg(&dev->ibdev,
			  "pgoff[%#lx] does not have valid entry\n",
			  vma->vm_pgoff);
		atomic64_inc(&dev->stats.mmap_err);
		वापस -EINVAL;
	पूर्ण
	entry = to_emmap(rdma_entry);

	ibdev_dbg(&dev->ibdev,
		  "Mapping address[%#llx], length[%#zx], mmap_flag[%d]\n",
		  entry->address, rdma_entry->npages * PAGE_SIZE,
		  entry->mmap_flag);

	pfn = entry->address >> PAGE_SHIFT;
	चयन (entry->mmap_flag) अणु
	हाल EFA_MMAP_IO_NC:
		err = rdma_user_mmap_io(&ucontext->ibucontext, vma, pfn,
					entry->rdma_entry.npages * PAGE_SIZE,
					pgprot_noncached(vma->vm_page_prot),
					rdma_entry);
		अवरोध;
	हाल EFA_MMAP_IO_WC:
		err = rdma_user_mmap_io(&ucontext->ibucontext, vma, pfn,
					entry->rdma_entry.npages * PAGE_SIZE,
					pgprot_ग_लिखोcombine(vma->vm_page_prot),
					rdma_entry);
		अवरोध;
	हाल EFA_MMAP_DMA_PAGE:
		क्रम (va = vma->vm_start; va < vma->vm_end;
		     va += PAGE_SIZE, pfn++) अणु
			err = vm_insert_page(vma, va, pfn_to_page(pfn));
			अगर (err)
				अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण

	अगर (err) अणु
		ibdev_dbg(
			&dev->ibdev,
			"Couldn't mmap address[%#llx] length[%#zx] mmap_flag[%d] err[%d]\n",
			entry->address, rdma_entry->npages * PAGE_SIZE,
			entry->mmap_flag, err);
		atomic64_inc(&dev->stats.mmap_err);
	पूर्ण

	rdma_user_mmap_entry_put(rdma_entry);
	वापस err;
पूर्ण

पूर्णांक efa_mmap(काष्ठा ib_ucontext *ibucontext,
	     काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा efa_ucontext *ucontext = to_eucontext(ibucontext);
	काष्ठा efa_dev *dev = to_edev(ibucontext->device);
	माप_प्रकार length = vma->vm_end - vma->vm_start;

	ibdev_dbg(&dev->ibdev,
		  "start %#lx, end %#lx, length = %#zx, pgoff = %#lx\n",
		  vma->vm_start, vma->vm_end, length, vma->vm_pgoff);

	वापस __efa_mmap(dev, ucontext, vma);
पूर्ण

अटल पूर्णांक efa_ah_destroy(काष्ठा efa_dev *dev, काष्ठा efa_ah *ah)
अणु
	काष्ठा efa_com_destroy_ah_params params = अणु
		.ah = ah->ah,
		.pdn = to_epd(ah->ibah.pd)->pdn,
	पूर्ण;

	वापस efa_com_destroy_ah(&dev->edev, &params);
पूर्ण

पूर्णांक efa_create_ah(काष्ठा ib_ah *ibah,
		  काष्ठा rdma_ah_init_attr *init_attr,
		  काष्ठा ib_udata *udata)
अणु
	काष्ठा rdma_ah_attr *ah_attr = init_attr->ah_attr;
	काष्ठा efa_dev *dev = to_edev(ibah->device);
	काष्ठा efa_com_create_ah_params params = अणुपूर्ण;
	काष्ठा efa_ibv_create_ah_resp resp = अणुपूर्ण;
	काष्ठा efa_com_create_ah_result result;
	काष्ठा efa_ah *ah = to_eah(ibah);
	पूर्णांक err;

	अगर (!(init_attr->flags & RDMA_CREATE_AH_SLEEPABLE)) अणु
		ibdev_dbg(&dev->ibdev,
			  "Create address handle is not supported in atomic context\n");
		err = -EOPNOTSUPP;
		जाओ err_out;
	पूर्ण

	अगर (udata->inlen &&
	    !ib_is_udata_cleared(udata, 0, udata->inlen)) अणु
		ibdev_dbg(&dev->ibdev, "Incompatible ABI params\n");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	स_नकल(params.dest_addr, ah_attr->grh.dgid.raw,
	       माप(params.dest_addr));
	params.pdn = to_epd(ibah->pd)->pdn;
	err = efa_com_create_ah(&dev->edev, &params, &result);
	अगर (err)
		जाओ err_out;

	स_नकल(ah->id, ah_attr->grh.dgid.raw, माप(ah->id));
	ah->ah = result.ah;

	resp.efa_address_handle = result.ah;

	अगर (udata->outlen) अणु
		err = ib_copy_to_udata(udata, &resp,
				       min(माप(resp), udata->outlen));
		अगर (err) अणु
			ibdev_dbg(&dev->ibdev,
				  "Failed to copy udata for create_ah response\n");
			जाओ err_destroy_ah;
		पूर्ण
	पूर्ण
	ibdev_dbg(&dev->ibdev, "Created ah[%d]\n", ah->ah);

	वापस 0;

err_destroy_ah:
	efa_ah_destroy(dev, ah);
err_out:
	atomic64_inc(&dev->stats.create_ah_err);
	वापस err;
पूर्ण

पूर्णांक efa_destroy_ah(काष्ठा ib_ah *ibah, u32 flags)
अणु
	काष्ठा efa_dev *dev = to_edev(ibah->pd->device);
	काष्ठा efa_ah *ah = to_eah(ibah);

	ibdev_dbg(&dev->ibdev, "Destroy ah[%d]\n", ah->ah);

	अगर (!(flags & RDMA_DESTROY_AH_SLEEPABLE)) अणु
		ibdev_dbg(&dev->ibdev,
			  "Destroy address handle is not supported in atomic context\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	efa_ah_destroy(dev, ah);
	वापस 0;
पूर्ण

काष्ठा rdma_hw_stats *efa_alloc_hw_stats(काष्ठा ib_device *ibdev, u32 port_num)
अणु
	वापस rdma_alloc_hw_stats_काष्ठा(efa_stats_names,
					  ARRAY_SIZE(efa_stats_names),
					  RDMA_HW_STATS_DEFAULT_LIFESPAN);
पूर्ण

पूर्णांक efa_get_hw_stats(काष्ठा ib_device *ibdev, काष्ठा rdma_hw_stats *stats,
		     u32 port_num, पूर्णांक index)
अणु
	काष्ठा efa_com_get_stats_params params = अणुपूर्ण;
	जोड़ efa_com_get_stats_result result;
	काष्ठा efa_dev *dev = to_edev(ibdev);
	काष्ठा efa_com_rdma_पढ़ो_stats *rrs;
	काष्ठा efa_com_messages_stats *ms;
	काष्ठा efa_com_basic_stats *bs;
	काष्ठा efa_com_stats_admin *as;
	काष्ठा efa_stats *s;
	पूर्णांक err;

	params.scope = EFA_ADMIN_GET_STATS_SCOPE_ALL;
	params.type = EFA_ADMIN_GET_STATS_TYPE_BASIC;

	err = efa_com_get_stats(&dev->edev, &params, &result);
	अगर (err)
		वापस err;

	bs = &result.basic_stats;
	stats->value[EFA_TX_BYTES] = bs->tx_bytes;
	stats->value[EFA_TX_PKTS] = bs->tx_pkts;
	stats->value[EFA_RX_BYTES] = bs->rx_bytes;
	stats->value[EFA_RX_PKTS] = bs->rx_pkts;
	stats->value[EFA_RX_DROPS] = bs->rx_drops;

	params.type = EFA_ADMIN_GET_STATS_TYPE_MESSAGES;
	err = efa_com_get_stats(&dev->edev, &params, &result);
	अगर (err)
		वापस err;

	ms = &result.messages_stats;
	stats->value[EFA_SEND_BYTES] = ms->send_bytes;
	stats->value[EFA_SEND_WRS] = ms->send_wrs;
	stats->value[EFA_RECV_BYTES] = ms->recv_bytes;
	stats->value[EFA_RECV_WRS] = ms->recv_wrs;

	params.type = EFA_ADMIN_GET_STATS_TYPE_RDMA_READ;
	err = efa_com_get_stats(&dev->edev, &params, &result);
	अगर (err)
		वापस err;

	rrs = &result.rdma_पढ़ो_stats;
	stats->value[EFA_RDMA_READ_WRS] = rrs->पढ़ो_wrs;
	stats->value[EFA_RDMA_READ_BYTES] = rrs->पढ़ो_bytes;
	stats->value[EFA_RDMA_READ_WR_ERR] = rrs->पढ़ो_wr_err;
	stats->value[EFA_RDMA_READ_RESP_BYTES] = rrs->पढ़ो_resp_bytes;

	as = &dev->edev.aq.stats;
	stats->value[EFA_SUBMITTED_CMDS] = atomic64_पढ़ो(&as->submitted_cmd);
	stats->value[EFA_COMPLETED_CMDS] = atomic64_पढ़ो(&as->completed_cmd);
	stats->value[EFA_CMDS_ERR] = atomic64_पढ़ो(&as->cmd_err);
	stats->value[EFA_NO_COMPLETION_CMDS] = atomic64_पढ़ो(&as->no_completion);

	s = &dev->stats;
	stats->value[EFA_KEEP_ALIVE_RCVD] = atomic64_पढ़ो(&s->keep_alive_rcvd);
	stats->value[EFA_ALLOC_PD_ERR] = atomic64_पढ़ो(&s->alloc_pd_err);
	stats->value[EFA_CREATE_QP_ERR] = atomic64_पढ़ो(&s->create_qp_err);
	stats->value[EFA_CREATE_CQ_ERR] = atomic64_पढ़ो(&s->create_cq_err);
	stats->value[EFA_REG_MR_ERR] = atomic64_पढ़ो(&s->reg_mr_err);
	stats->value[EFA_ALLOC_UCONTEXT_ERR] =
		atomic64_पढ़ो(&s->alloc_ucontext_err);
	stats->value[EFA_CREATE_AH_ERR] = atomic64_पढ़ो(&s->create_ah_err);
	stats->value[EFA_MMAP_ERR] = atomic64_पढ़ो(&s->mmap_err);

	वापस ARRAY_SIZE(efa_stats_names);
पूर्ण

क्रमागत rdma_link_layer efa_port_link_layer(काष्ठा ib_device *ibdev,
					 u32 port_num)
अणु
	वापस IB_LINK_LAYER_UNSPECIFIED;
पूर्ण

