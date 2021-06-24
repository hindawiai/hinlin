<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>

#समावेश "hinic_hw_dev.h"
#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_eqs.h"
#समावेश "hinic_hw_wqe.h"
#समावेश "hinic_hw_wq.h"
#समावेश "hinic_hw_cmdq.h"
#समावेश "hinic_hw_qp_ctxt.h"
#समावेश "hinic_hw_qp.h"
#समावेश "hinic_hw_io.h"

#घोषणा CI_Q_ADDR_SIZE                  माप(u32)

#घोषणा CI_ADDR(base_addr, q_id)        ((base_addr) + \
					 (q_id) * CI_Q_ADDR_SIZE)

#घोषणा CI_TABLE_SIZE(num_qps)          ((num_qps) * CI_Q_ADDR_SIZE)

#घोषणा DB_IDX(db, db_base)             \
	(((अचिन्हित दीर्घ)(db) - (अचिन्हित दीर्घ)(db_base)) / HINIC_DB_PAGE_SIZE)

#घोषणा HINIC_PAGE_SIZE_HW(pg_size)	((u8)ilog2((u32)((pg_size) >> 12)))

क्रमागत io_cmd अणु
	IO_CMD_MODIFY_QUEUE_CTXT = 0,
	IO_CMD_CLEAN_QUEUE_CTXT,
पूर्ण;

अटल व्योम init_db_area_idx(काष्ठा hinic_मुक्त_db_area *मुक्त_db_area)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HINIC_DB_MAX_AREAS; i++)
		मुक्त_db_area->db_idx[i] = i;

	मुक्त_db_area->alloc_pos = 0;
	मुक्त_db_area->वापस_pos = HINIC_DB_MAX_AREAS;

	मुक्त_db_area->num_मुक्त = HINIC_DB_MAX_AREAS;

	sema_init(&मुक्त_db_area->idx_lock, 1);
पूर्ण

अटल व्योम __iomem *get_db_area(काष्ठा hinic_func_to_io *func_to_io)
अणु
	काष्ठा hinic_मुक्त_db_area *मुक्त_db_area = &func_to_io->मुक्त_db_area;
	पूर्णांक pos, idx;

	करोwn(&मुक्त_db_area->idx_lock);

	मुक्त_db_area->num_मुक्त--;

	अगर (मुक्त_db_area->num_मुक्त < 0) अणु
		मुक्त_db_area->num_मुक्त++;
		up(&मुक्त_db_area->idx_lock);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	pos = मुक्त_db_area->alloc_pos++;
	pos &= HINIC_DB_MAX_AREAS - 1;

	idx = मुक्त_db_area->db_idx[pos];

	मुक्त_db_area->db_idx[pos] = -1;

	up(&मुक्त_db_area->idx_lock);

	वापस func_to_io->db_base + idx * HINIC_DB_PAGE_SIZE;
पूर्ण

अटल व्योम वापस_db_area(काष्ठा hinic_func_to_io *func_to_io,
			   व्योम __iomem *db_base)
अणु
	काष्ठा hinic_मुक्त_db_area *मुक्त_db_area = &func_to_io->मुक्त_db_area;
	पूर्णांक pos, idx = DB_IDX(db_base, func_to_io->db_base);

	करोwn(&मुक्त_db_area->idx_lock);

	pos = मुक्त_db_area->वापस_pos++;
	pos &= HINIC_DB_MAX_AREAS - 1;

	मुक्त_db_area->db_idx[pos] = idx;

	मुक्त_db_area->num_मुक्त++;

	up(&मुक्त_db_area->idx_lock);
पूर्ण

अटल पूर्णांक ग_लिखो_sq_ctxts(काष्ठा hinic_func_to_io *func_to_io, u16 base_qpn,
			  u16 num_sqs)
अणु
	काष्ठा hinic_hwअगर *hwअगर = func_to_io->hwअगर;
	काष्ठा hinic_sq_ctxt_block *sq_ctxt_block;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_cmdq_buf cmdq_buf;
	काष्ठा hinic_sq_ctxt *sq_ctxt;
	काष्ठा hinic_qp *qp;
	u64 out_param;
	पूर्णांक err, i;

	err = hinic_alloc_cmdq_buf(&func_to_io->cmdqs, &cmdq_buf);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate cmdq buf\n");
		वापस err;
	पूर्ण

	sq_ctxt_block = cmdq_buf.buf;
	sq_ctxt = sq_ctxt_block->sq_ctxt;

	hinic_qp_prepare_header(&sq_ctxt_block->hdr, HINIC_QP_CTXT_TYPE_SQ,
				num_sqs, func_to_io->max_qps);
	क्रम (i = 0; i < num_sqs; i++) अणु
		qp = &func_to_io->qps[i];

		hinic_sq_prepare_ctxt(&sq_ctxt[i], &qp->sq,
				      base_qpn + qp->q_id);
	पूर्ण

	cmdq_buf.size = HINIC_SQ_CTXT_SIZE(num_sqs);

	err = hinic_cmdq_direct_resp(&func_to_io->cmdqs, HINIC_MOD_L2NIC,
				     IO_CMD_MODIFY_QUEUE_CTXT, &cmdq_buf,
				     &out_param);
	अगर ((err) || (out_param != 0)) अणु
		dev_err(&pdev->dev, "Failed to set SQ ctxts\n");
		err = -EFAULT;
	पूर्ण

	hinic_मुक्त_cmdq_buf(&func_to_io->cmdqs, &cmdq_buf);
	वापस err;
पूर्ण

अटल पूर्णांक ग_लिखो_rq_ctxts(काष्ठा hinic_func_to_io *func_to_io, u16 base_qpn,
			  u16 num_rqs)
अणु
	काष्ठा hinic_hwअगर *hwअगर = func_to_io->hwअगर;
	काष्ठा hinic_rq_ctxt_block *rq_ctxt_block;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_cmdq_buf cmdq_buf;
	काष्ठा hinic_rq_ctxt *rq_ctxt;
	काष्ठा hinic_qp *qp;
	u64 out_param;
	पूर्णांक err, i;

	err = hinic_alloc_cmdq_buf(&func_to_io->cmdqs, &cmdq_buf);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate cmdq buf\n");
		वापस err;
	पूर्ण

	rq_ctxt_block = cmdq_buf.buf;
	rq_ctxt = rq_ctxt_block->rq_ctxt;

	hinic_qp_prepare_header(&rq_ctxt_block->hdr, HINIC_QP_CTXT_TYPE_RQ,
				num_rqs, func_to_io->max_qps);
	क्रम (i = 0; i < num_rqs; i++) अणु
		qp = &func_to_io->qps[i];

		hinic_rq_prepare_ctxt(&rq_ctxt[i], &qp->rq,
				      base_qpn + qp->q_id);
	पूर्ण

	cmdq_buf.size = HINIC_RQ_CTXT_SIZE(num_rqs);

	err = hinic_cmdq_direct_resp(&func_to_io->cmdqs, HINIC_MOD_L2NIC,
				     IO_CMD_MODIFY_QUEUE_CTXT, &cmdq_buf,
				     &out_param);
	अगर ((err) || (out_param != 0)) अणु
		dev_err(&pdev->dev, "Failed to set RQ ctxts\n");
		err = -EFAULT;
	पूर्ण

	hinic_मुक्त_cmdq_buf(&func_to_io->cmdqs, &cmdq_buf);
	वापस err;
पूर्ण

/**
 * ग_लिखो_qp_ctxts - ग_लिखो the qp ctxt to HW
 * @func_to_io: func to io channel that holds the IO components
 * @base_qpn: first qp number
 * @num_qps: number of qps to ग_लिखो
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक ग_लिखो_qp_ctxts(काष्ठा hinic_func_to_io *func_to_io, u16 base_qpn,
			  u16 num_qps)
अणु
	वापस (ग_लिखो_sq_ctxts(func_to_io, base_qpn, num_qps) ||
		ग_लिखो_rq_ctxts(func_to_io, base_qpn, num_qps));
पूर्ण

अटल पूर्णांक hinic_clean_queue_offload_ctxt(काष्ठा hinic_func_to_io *func_to_io,
					  क्रमागत hinic_qp_ctxt_type ctxt_type)
अणु
	काष्ठा hinic_hwअगर *hwअगर = func_to_io->hwअगर;
	काष्ठा hinic_clean_queue_ctxt *ctxt_block;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_cmdq_buf cmdq_buf;
	u64 out_param = 0;
	पूर्णांक err;

	err = hinic_alloc_cmdq_buf(&func_to_io->cmdqs, &cmdq_buf);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate cmdq buf\n");
		वापस err;
	पूर्ण

	ctxt_block = cmdq_buf.buf;
	ctxt_block->cmdq_hdr.num_queues = func_to_io->max_qps;
	ctxt_block->cmdq_hdr.queue_type = ctxt_type;
	ctxt_block->cmdq_hdr.addr_offset = 0;

	/* TSO/LRO ctxt size: 0x0:0B; 0x1:160B; 0x2:200B; 0x3:240B */
	ctxt_block->ctxt_size = 0x3;

	hinic_cpu_to_be32(ctxt_block, माप(*ctxt_block));

	cmdq_buf.size = माप(*ctxt_block);

	err = hinic_cmdq_direct_resp(&func_to_io->cmdqs, HINIC_MOD_L2NIC,
				     IO_CMD_CLEAN_QUEUE_CTXT,
				     &cmdq_buf, &out_param);

	अगर (err || out_param) अणु
		dev_err(&pdev->dev, "Failed to clean offload ctxts, err: %d, out_param: 0x%llx\n",
			err, out_param);

		err = -EFAULT;
	पूर्ण

	hinic_मुक्त_cmdq_buf(&func_to_io->cmdqs, &cmdq_buf);

	वापस err;
पूर्ण

अटल पूर्णांक hinic_clean_qp_offload_ctxt(काष्ठा hinic_func_to_io *func_to_io)
अणु
	/* clean LRO/TSO context space */
	वापस (hinic_clean_queue_offload_ctxt(func_to_io,
					       HINIC_QP_CTXT_TYPE_SQ) ||
		hinic_clean_queue_offload_ctxt(func_to_io,
					       HINIC_QP_CTXT_TYPE_RQ));
पूर्ण

/**
 * init_qp - Initialize a Queue Pair
 * @func_to_io: func to io channel that holds the IO components
 * @qp: poपूर्णांकer to the qp to initialize
 * @q_id: the id of the qp
 * @sq_msix_entry: msix entry क्रम sq
 * @rq_msix_entry: msix entry क्रम rq
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक init_qp(काष्ठा hinic_func_to_io *func_to_io,
		   काष्ठा hinic_qp *qp, पूर्णांक q_id,
		   काष्ठा msix_entry *sq_msix_entry,
		   काष्ठा msix_entry *rq_msix_entry)
अणु
	काष्ठा hinic_hwअगर *hwअगर = func_to_io->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	व्योम __iomem *db_base;
	पूर्णांक err;

	qp->q_id = q_id;

	err = hinic_wq_allocate(&func_to_io->wqs, &func_to_io->sq_wq[q_id],
				HINIC_SQ_WQEBB_SIZE, HINIC_SQ_PAGE_SIZE,
				func_to_io->sq_depth, HINIC_SQ_WQE_MAX_SIZE);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate WQ for SQ\n");
		वापस err;
	पूर्ण

	err = hinic_wq_allocate(&func_to_io->wqs, &func_to_io->rq_wq[q_id],
				HINIC_RQ_WQEBB_SIZE, HINIC_RQ_PAGE_SIZE,
				func_to_io->rq_depth, HINIC_RQ_WQE_SIZE);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate WQ for RQ\n");
		जाओ err_rq_alloc;
	पूर्ण

	db_base = get_db_area(func_to_io);
	अगर (IS_ERR(db_base)) अणु
		dev_err(&pdev->dev, "Failed to get DB area for SQ\n");
		err = PTR_ERR(db_base);
		जाओ err_get_db;
	पूर्ण

	func_to_io->sq_db[q_id] = db_base;

	qp->sq.qid = q_id;
	err = hinic_init_sq(&qp->sq, hwअगर, &func_to_io->sq_wq[q_id],
			    sq_msix_entry,
			    CI_ADDR(func_to_io->ci_addr_base, q_id),
			    CI_ADDR(func_to_io->ci_dma_base, q_id), db_base);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to init SQ\n");
		जाओ err_sq_init;
	पूर्ण

	qp->rq.qid = q_id;
	err = hinic_init_rq(&qp->rq, hwअगर, &func_to_io->rq_wq[q_id],
			    rq_msix_entry);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to init RQ\n");
		जाओ err_rq_init;
	पूर्ण

	वापस 0;

err_rq_init:
	hinic_clean_sq(&qp->sq);

err_sq_init:
	वापस_db_area(func_to_io, db_base);

err_get_db:
	hinic_wq_मुक्त(&func_to_io->wqs, &func_to_io->rq_wq[q_id]);

err_rq_alloc:
	hinic_wq_मुक्त(&func_to_io->wqs, &func_to_io->sq_wq[q_id]);
	वापस err;
पूर्ण

/**
 * destroy_qp - Clean the resources of a Queue Pair
 * @func_to_io: func to io channel that holds the IO components
 * @qp: poपूर्णांकer to the qp to clean
 **/
अटल व्योम destroy_qp(काष्ठा hinic_func_to_io *func_to_io,
		       काष्ठा hinic_qp *qp)
अणु
	पूर्णांक q_id = qp->q_id;

	hinic_clean_rq(&qp->rq);
	hinic_clean_sq(&qp->sq);

	वापस_db_area(func_to_io, func_to_io->sq_db[q_id]);

	hinic_wq_मुक्त(&func_to_io->wqs, &func_to_io->rq_wq[q_id]);
	hinic_wq_मुक्त(&func_to_io->wqs, &func_to_io->sq_wq[q_id]);
पूर्ण

/**
 * hinic_io_create_qps - Create Queue Pairs
 * @func_to_io: func to io channel that holds the IO components
 * @base_qpn: base qp number
 * @num_qps: number queue pairs to create
 * @sq_msix_entries: msix entries क्रम sq
 * @rq_msix_entries: msix entries क्रम rq
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_io_create_qps(काष्ठा hinic_func_to_io *func_to_io,
			u16 base_qpn, पूर्णांक num_qps,
			काष्ठा msix_entry *sq_msix_entries,
			काष्ठा msix_entry *rq_msix_entries)
अणु
	काष्ठा hinic_hwअगर *hwअगर = func_to_io->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	माप_प्रकार qps_size, wq_size, db_size;
	व्योम *ci_addr_base;
	पूर्णांक i, j, err;

	qps_size = num_qps * माप(*func_to_io->qps);
	func_to_io->qps = devm_kzalloc(&pdev->dev, qps_size, GFP_KERNEL);
	अगर (!func_to_io->qps)
		वापस -ENOMEM;

	wq_size = num_qps * माप(*func_to_io->sq_wq);
	func_to_io->sq_wq = devm_kzalloc(&pdev->dev, wq_size, GFP_KERNEL);
	अगर (!func_to_io->sq_wq) अणु
		err = -ENOMEM;
		जाओ err_sq_wq;
	पूर्ण

	wq_size = num_qps * माप(*func_to_io->rq_wq);
	func_to_io->rq_wq = devm_kzalloc(&pdev->dev, wq_size, GFP_KERNEL);
	अगर (!func_to_io->rq_wq) अणु
		err = -ENOMEM;
		जाओ err_rq_wq;
	पूर्ण

	db_size = num_qps * माप(*func_to_io->sq_db);
	func_to_io->sq_db = devm_kzalloc(&pdev->dev, db_size, GFP_KERNEL);
	अगर (!func_to_io->sq_db) अणु
		err = -ENOMEM;
		जाओ err_sq_db;
	पूर्ण

	ci_addr_base = dma_alloc_coherent(&pdev->dev, CI_TABLE_SIZE(num_qps),
					  &func_to_io->ci_dma_base,
					  GFP_KERNEL);
	अगर (!ci_addr_base) अणु
		dev_err(&pdev->dev, "Failed to allocate CI area\n");
		err = -ENOMEM;
		जाओ err_ci_base;
	पूर्ण

	func_to_io->ci_addr_base = ci_addr_base;

	क्रम (i = 0; i < num_qps; i++) अणु
		err = init_qp(func_to_io, &func_to_io->qps[i], i,
			      &sq_msix_entries[i], &rq_msix_entries[i]);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to create QP %d\n", i);
			जाओ err_init_qp;
		पूर्ण
	पूर्ण

	err = ग_लिखो_qp_ctxts(func_to_io, base_qpn, num_qps);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to init QP ctxts\n");
		जाओ err_ग_लिखो_qp_ctxts;
	पूर्ण

	err = hinic_clean_qp_offload_ctxt(func_to_io);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to clean QP contexts space\n");
		जाओ err_ग_लिखो_qp_ctxts;
	पूर्ण

	वापस 0;

err_ग_लिखो_qp_ctxts:
err_init_qp:
	क्रम (j = 0; j < i; j++)
		destroy_qp(func_to_io, &func_to_io->qps[j]);

	dma_मुक्त_coherent(&pdev->dev, CI_TABLE_SIZE(num_qps),
			  func_to_io->ci_addr_base, func_to_io->ci_dma_base);

err_ci_base:
	devm_kमुक्त(&pdev->dev, func_to_io->sq_db);

err_sq_db:
	devm_kमुक्त(&pdev->dev, func_to_io->rq_wq);

err_rq_wq:
	devm_kमुक्त(&pdev->dev, func_to_io->sq_wq);

err_sq_wq:
	devm_kमुक्त(&pdev->dev, func_to_io->qps);
	वापस err;
पूर्ण

/**
 * hinic_io_destroy_qps - Destroy the IO Queue Pairs
 * @func_to_io: func to io channel that holds the IO components
 * @num_qps: number queue pairs to destroy
 **/
व्योम hinic_io_destroy_qps(काष्ठा hinic_func_to_io *func_to_io, पूर्णांक num_qps)
अणु
	काष्ठा hinic_hwअगर *hwअगर = func_to_io->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	माप_प्रकार ci_table_size;
	पूर्णांक i;

	ci_table_size = CI_TABLE_SIZE(num_qps);

	क्रम (i = 0; i < num_qps; i++)
		destroy_qp(func_to_io, &func_to_io->qps[i]);

	dma_मुक्त_coherent(&pdev->dev, ci_table_size, func_to_io->ci_addr_base,
			  func_to_io->ci_dma_base);

	devm_kमुक्त(&pdev->dev, func_to_io->sq_db);

	devm_kमुक्त(&pdev->dev, func_to_io->rq_wq);
	devm_kमुक्त(&pdev->dev, func_to_io->sq_wq);

	devm_kमुक्त(&pdev->dev, func_to_io->qps);
पूर्ण

पूर्णांक hinic_set_wq_page_size(काष्ठा hinic_hwdev *hwdev, u16 func_idx,
			   u32 page_size)
अणु
	काष्ठा hinic_wq_page_size page_size_info = अणु0पूर्ण;
	u16 out_size = माप(page_size_info);
	काष्ठा hinic_pfhwdev *pfhwdev;
	पूर्णांक err;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	page_size_info.func_idx = func_idx;
	page_size_info.ppf_idx = HINIC_HWIF_PPF_IDX(hwdev->hwअगर);
	page_size_info.page_size = HINIC_PAGE_SIZE_HW(page_size);

	err = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				HINIC_COMM_CMD_PAGESIZE_SET, &page_size_info,
				माप(page_size_info), &page_size_info,
				&out_size, HINIC_MGMT_MSG_SYNC);
	अगर (err || !out_size || page_size_info.status) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to set wq page size, err: %d, status: 0x%x, out_size: 0x%0x\n",
			err, page_size_info.status, out_size);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hinic_io_init - Initialize the IO components
 * @func_to_io: func to io channel that holds the IO components
 * @hwअगर: HW पूर्णांकerface क्रम accessing IO
 * @max_qps: maximum QPs in HW
 * @num_ceqs: number completion event queues
 * @ceq_msix_entries: msix entries क्रम ceqs
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_io_init(काष्ठा hinic_func_to_io *func_to_io,
		  काष्ठा hinic_hwअगर *hwअगर, u16 max_qps, पूर्णांक num_ceqs,
		  काष्ठा msix_entry *ceq_msix_entries)
अणु
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	क्रमागत hinic_cmdq_type cmdq, type;
	व्योम __iomem *db_area;
	पूर्णांक err;

	func_to_io->hwअगर = hwअगर;
	func_to_io->qps = शून्य;
	func_to_io->max_qps = max_qps;
	func_to_io->ceqs.hwdev = func_to_io->hwdev;

	err = hinic_ceqs_init(&func_to_io->ceqs, hwअगर, num_ceqs,
			      HINIC_DEFAULT_CEQ_LEN, HINIC_EQ_PAGE_SIZE,
			      ceq_msix_entries);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to init CEQs\n");
		वापस err;
	पूर्ण

	err = hinic_wqs_alloc(&func_to_io->wqs, 2 * max_qps, hwअगर);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate WQS for IO\n");
		जाओ err_wqs_alloc;
	पूर्ण

	func_to_io->db_base = pci_ioremap_bar(pdev, HINIC_PCI_DB_BAR);
	अगर (!func_to_io->db_base) अणु
		dev_err(&pdev->dev, "Failed to remap IO DB area\n");
		err = -ENOMEM;
		जाओ err_db_ioremap;
	पूर्ण

	init_db_area_idx(&func_to_io->मुक्त_db_area);

	क्रम (cmdq = HINIC_CMDQ_SYNC; cmdq < HINIC_MAX_CMDQ_TYPES; cmdq++) अणु
		db_area = get_db_area(func_to_io);
		अगर (IS_ERR(db_area)) अणु
			dev_err(&pdev->dev, "Failed to get cmdq db area\n");
			err = PTR_ERR(db_area);
			जाओ err_db_area;
		पूर्ण

		func_to_io->cmdq_db_area[cmdq] = db_area;
	पूर्ण

	err = hinic_set_wq_page_size(func_to_io->hwdev,
				     HINIC_HWIF_FUNC_IDX(hwअगर),
				     HINIC_DEFAULT_WQ_PAGE_SIZE);
	अगर (err) अणु
		dev_err(&func_to_io->hwअगर->pdev->dev, "Failed to set wq page size\n");
		जाओ init_wq_pg_size_err;
	पूर्ण

	err = hinic_init_cmdqs(&func_to_io->cmdqs, hwअगर,
			       func_to_io->cmdq_db_area);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to initialize cmdqs\n");
		जाओ err_init_cmdqs;
	पूर्ण

	वापस 0;

err_init_cmdqs:
	अगर (!HINIC_IS_VF(func_to_io->hwअगर))
		hinic_set_wq_page_size(func_to_io->hwdev,
				       HINIC_HWIF_FUNC_IDX(hwअगर),
				       HINIC_HW_WQ_PAGE_SIZE);
init_wq_pg_size_err:
err_db_area:
	क्रम (type = HINIC_CMDQ_SYNC; type < cmdq; type++)
		वापस_db_area(func_to_io, func_to_io->cmdq_db_area[type]);

	iounmap(func_to_io->db_base);

err_db_ioremap:
	hinic_wqs_मुक्त(&func_to_io->wqs);

err_wqs_alloc:
	hinic_ceqs_मुक्त(&func_to_io->ceqs);
	वापस err;
पूर्ण

/**
 * hinic_io_मुक्त - Free the IO components
 * @func_to_io: func to io channel that holds the IO components
 **/
व्योम hinic_io_मुक्त(काष्ठा hinic_func_to_io *func_to_io)
अणु
	क्रमागत hinic_cmdq_type cmdq;

	hinic_मुक्त_cmdqs(&func_to_io->cmdqs);

	अगर (!HINIC_IS_VF(func_to_io->hwअगर))
		hinic_set_wq_page_size(func_to_io->hwdev,
				       HINIC_HWIF_FUNC_IDX(func_to_io->hwअगर),
				       HINIC_HW_WQ_PAGE_SIZE);

	क्रम (cmdq = HINIC_CMDQ_SYNC; cmdq < HINIC_MAX_CMDQ_TYPES; cmdq++)
		वापस_db_area(func_to_io, func_to_io->cmdq_db_area[cmdq]);

	iounmap(func_to_io->db_base);
	hinic_wqs_मुक्त(&func_to_io->wqs);
	hinic_ceqs_मुक्त(&func_to_io->ceqs);
पूर्ण
