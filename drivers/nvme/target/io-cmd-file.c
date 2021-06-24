<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVMe Over Fabrics Target File I/O commands implementation.
 * Copyright (c) 2017-2018 Western Digital Corporation or its
 * affiliates.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/uपन.स>
#समावेश <linux/fभाग.स>
#समावेश <linux/file.h>
#समावेश "nvmet.h"

#घोषणा NVMET_MAX_MPOOL_BVEC		16
#घोषणा NVMET_MIN_MPOOL_OBJ		16

पूर्णांक nvmet_file_ns_revalidate(काष्ठा nvmet_ns *ns)
अणु
	काष्ठा kstat stat;
	पूर्णांक ret;

	ret = vfs_getattr(&ns->file->f_path, &stat, STATX_SIZE,
			  AT_STATX_FORCE_SYNC);
	अगर (!ret)
		ns->size = stat.size;
	वापस ret;
पूर्ण

व्योम nvmet_file_ns_disable(काष्ठा nvmet_ns *ns)
अणु
	अगर (ns->file) अणु
		अगर (ns->buffered_io)
			flush_workqueue(buffered_io_wq);
		mempool_destroy(ns->bvec_pool);
		ns->bvec_pool = शून्य;
		kmem_cache_destroy(ns->bvec_cache);
		ns->bvec_cache = शून्य;
		fput(ns->file);
		ns->file = शून्य;
	पूर्ण
पूर्ण

पूर्णांक nvmet_file_ns_enable(काष्ठा nvmet_ns *ns)
अणु
	पूर्णांक flags = O_RDWR | O_LARGEखाता;
	पूर्णांक ret;

	अगर (!ns->buffered_io)
		flags |= O_सूचीECT;

	ns->file = filp_खोलो(ns->device_path, flags, 0);
	अगर (IS_ERR(ns->file)) अणु
		ret = PTR_ERR(ns->file);
		pr_err("failed to open file %s: (%d)\n",
			ns->device_path, ret);
		ns->file = शून्य;
		वापस ret;
	पूर्ण

	ret = nvmet_file_ns_revalidate(ns);
	अगर (ret)
		जाओ err;

	/*
	 * i_blkbits can be greater than the universally accepted upper bound,
	 * so make sure we export a sane namespace lba_shअगरt.
	 */
	ns->blksize_shअगरt = min_t(u8,
			file_inode(ns->file)->i_blkbits, 12);

	ns->bvec_cache = kmem_cache_create("nvmet-bvec",
			NVMET_MAX_MPOOL_BVEC * माप(काष्ठा bio_vec),
			0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!ns->bvec_cache) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ns->bvec_pool = mempool_create(NVMET_MIN_MPOOL_OBJ, mempool_alloc_slab,
			mempool_मुक्त_slab, ns->bvec_cache);

	अगर (!ns->bvec_pool) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	वापस ret;
err:
	ns->size = 0;
	ns->blksize_shअगरt = 0;
	nvmet_file_ns_disable(ns);
	वापस ret;
पूर्ण

अटल व्योम nvmet_file_init_bvec(काष्ठा bio_vec *bv, काष्ठा scatterlist *sg)
अणु
	bv->bv_page = sg_page(sg);
	bv->bv_offset = sg->offset;
	bv->bv_len = sg->length;
पूर्ण

अटल sमाप_प्रकार nvmet_file_submit_bvec(काष्ठा nvmet_req *req, loff_t pos,
		अचिन्हित दीर्घ nr_segs, माप_प्रकार count, पूर्णांक ki_flags)
अणु
	काष्ठा kiocb *iocb = &req->f.iocb;
	sमाप_प्रकार (*call_iter)(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter);
	काष्ठा iov_iter iter;
	पूर्णांक rw;

	अगर (req->cmd->rw.opcode == nvme_cmd_ग_लिखो) अणु
		अगर (req->cmd->rw.control & cpu_to_le16(NVME_RW_FUA))
			ki_flags |= IOCB_DSYNC;
		call_iter = req->ns->file->f_op->ग_लिखो_iter;
		rw = WRITE;
	पूर्ण अन्यथा अणु
		call_iter = req->ns->file->f_op->पढ़ो_iter;
		rw = READ;
	पूर्ण

	iov_iter_bvec(&iter, rw, req->f.bvec, nr_segs, count);

	iocb->ki_pos = pos;
	iocb->ki_filp = req->ns->file;
	iocb->ki_flags = ki_flags | iocb_flags(req->ns->file);

	वापस call_iter(iocb, &iter);
पूर्ण

अटल व्योम nvmet_file_io_करोne(काष्ठा kiocb *iocb, दीर्घ ret, दीर्घ ret2)
अणु
	काष्ठा nvmet_req *req = container_of(iocb, काष्ठा nvmet_req, f.iocb);
	u16 status = NVME_SC_SUCCESS;

	अगर (req->f.bvec != req->अंतरभूत_bvec) अणु
		अगर (likely(req->f.mpool_alloc == false))
			kमुक्त(req->f.bvec);
		अन्यथा
			mempool_मुक्त(req->f.bvec, req->ns->bvec_pool);
	पूर्ण

	अगर (unlikely(ret != req->transfer_len))
		status = त्रुटि_सं_to_nvme_status(req, ret);
	nvmet_req_complete(req, status);
पूर्ण

अटल bool nvmet_file_execute_io(काष्ठा nvmet_req *req, पूर्णांक ki_flags)
अणु
	sमाप_प्रकार nr_bvec = req->sg_cnt;
	अचिन्हित दीर्घ bv_cnt = 0;
	bool is_sync = false;
	माप_प्रकार len = 0, total_len = 0;
	sमाप_प्रकार ret = 0;
	loff_t pos;
	पूर्णांक i;
	काष्ठा scatterlist *sg;

	अगर (req->f.mpool_alloc && nr_bvec > NVMET_MAX_MPOOL_BVEC)
		is_sync = true;

	pos = le64_to_cpu(req->cmd->rw.slba) << req->ns->blksize_shअगरt;
	अगर (unlikely(pos + req->transfer_len > req->ns->size)) अणु
		nvmet_req_complete(req, त्रुटि_सं_to_nvme_status(req, -ENOSPC));
		वापस true;
	पूर्ण

	स_रखो(&req->f.iocb, 0, माप(काष्ठा kiocb));
	क्रम_each_sg(req->sg, sg, req->sg_cnt, i) अणु
		nvmet_file_init_bvec(&req->f.bvec[bv_cnt], sg);
		len += req->f.bvec[bv_cnt].bv_len;
		total_len += req->f.bvec[bv_cnt].bv_len;
		bv_cnt++;

		WARN_ON_ONCE((nr_bvec - 1) < 0);

		अगर (unlikely(is_sync) &&
		    (nr_bvec - 1 == 0 || bv_cnt == NVMET_MAX_MPOOL_BVEC)) अणु
			ret = nvmet_file_submit_bvec(req, pos, bv_cnt, len, 0);
			अगर (ret < 0)
				जाओ complete;

			pos += len;
			bv_cnt = 0;
			len = 0;
		पूर्ण
		nr_bvec--;
	पूर्ण

	अगर (WARN_ON_ONCE(total_len != req->transfer_len)) अणु
		ret = -EIO;
		जाओ complete;
	पूर्ण

	अगर (unlikely(is_sync)) अणु
		ret = total_len;
		जाओ complete;
	पूर्ण

	/*
	 * A शून्य ki_complete ask क्रम synchronous execution, which we want
	 * क्रम the IOCB_NOWAIT हाल.
	 */
	अगर (!(ki_flags & IOCB_NOWAIT))
		req->f.iocb.ki_complete = nvmet_file_io_करोne;

	ret = nvmet_file_submit_bvec(req, pos, bv_cnt, total_len, ki_flags);

	चयन (ret) अणु
	हाल -EIOCBQUEUED:
		वापस true;
	हाल -EAGAIN:
		अगर (WARN_ON_ONCE(!(ki_flags & IOCB_NOWAIT)))
			जाओ complete;
		वापस false;
	हाल -EOPNOTSUPP:
		/*
		 * For file प्रणालीs वापसing error -EOPNOTSUPP, handle
		 * IOCB_NOWAIT error हाल separately and retry without
		 * IOCB_NOWAIT.
		 */
		अगर ((ki_flags & IOCB_NOWAIT))
			वापस false;
		अवरोध;
	पूर्ण

complete:
	nvmet_file_io_करोne(&req->f.iocb, ret, 0);
	वापस true;
पूर्ण

अटल व्योम nvmet_file_buffered_io_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा nvmet_req *req = container_of(w, काष्ठा nvmet_req, f.work);

	nvmet_file_execute_io(req, 0);
पूर्ण

अटल व्योम nvmet_file_submit_buffered_io(काष्ठा nvmet_req *req)
अणु
	INIT_WORK(&req->f.work, nvmet_file_buffered_io_work);
	queue_work(buffered_io_wq, &req->f.work);
पूर्ण

अटल व्योम nvmet_file_execute_rw(काष्ठा nvmet_req *req)
अणु
	sमाप_प्रकार nr_bvec = req->sg_cnt;

	अगर (!nvmet_check_transfer_len(req, nvmet_rw_data_len(req)))
		वापस;

	अगर (!req->sg_cnt || !nr_bvec) अणु
		nvmet_req_complete(req, 0);
		वापस;
	पूर्ण

	अगर (nr_bvec > NVMET_MAX_INLINE_BIOVEC)
		req->f.bvec = kदो_स्मृति_array(nr_bvec, माप(काष्ठा bio_vec),
				GFP_KERNEL);
	अन्यथा
		req->f.bvec = req->अंतरभूत_bvec;

	अगर (unlikely(!req->f.bvec)) अणु
		/* fallback under memory pressure */
		req->f.bvec = mempool_alloc(req->ns->bvec_pool, GFP_KERNEL);
		req->f.mpool_alloc = true;
	पूर्ण अन्यथा
		req->f.mpool_alloc = false;

	अगर (req->ns->buffered_io) अणु
		अगर (likely(!req->f.mpool_alloc) &&
				nvmet_file_execute_io(req, IOCB_NOWAIT))
			वापस;
		nvmet_file_submit_buffered_io(req);
	पूर्ण अन्यथा
		nvmet_file_execute_io(req, 0);
पूर्ण

u16 nvmet_file_flush(काष्ठा nvmet_req *req)
अणु
	वापस त्रुटि_सं_to_nvme_status(req, vfs_fsync(req->ns->file, 1));
पूर्ण

अटल व्योम nvmet_file_flush_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा nvmet_req *req = container_of(w, काष्ठा nvmet_req, f.work);

	nvmet_req_complete(req, nvmet_file_flush(req));
पूर्ण

अटल व्योम nvmet_file_execute_flush(काष्ठा nvmet_req *req)
अणु
	अगर (!nvmet_check_transfer_len(req, 0))
		वापस;
	INIT_WORK(&req->f.work, nvmet_file_flush_work);
	schedule_work(&req->f.work);
पूर्ण

अटल व्योम nvmet_file_execute_discard(काष्ठा nvmet_req *req)
अणु
	पूर्णांक mode = FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE;
	काष्ठा nvme_dsm_range range;
	loff_t offset, len;
	u16 status = 0;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i <= le32_to_cpu(req->cmd->dsm.nr); i++) अणु
		status = nvmet_copy_from_sgl(req, i * माप(range), &range,
					माप(range));
		अगर (status)
			अवरोध;

		offset = le64_to_cpu(range.slba) << req->ns->blksize_shअगरt;
		len = le32_to_cpu(range.nlb);
		len <<= req->ns->blksize_shअगरt;
		अगर (offset + len > req->ns->size) अणु
			req->error_slba = le64_to_cpu(range.slba);
			status = त्रुटि_सं_to_nvme_status(req, -ENOSPC);
			अवरोध;
		पूर्ण

		ret = vfs_fallocate(req->ns->file, mode, offset, len);
		अगर (ret && ret != -EOPNOTSUPP) अणु
			req->error_slba = le64_to_cpu(range.slba);
			status = त्रुटि_सं_to_nvme_status(req, ret);
			अवरोध;
		पूर्ण
	पूर्ण

	nvmet_req_complete(req, status);
पूर्ण

अटल व्योम nvmet_file_dsm_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा nvmet_req *req = container_of(w, काष्ठा nvmet_req, f.work);

	चयन (le32_to_cpu(req->cmd->dsm.attributes)) अणु
	हाल NVME_DSMGMT_AD:
		nvmet_file_execute_discard(req);
		वापस;
	हाल NVME_DSMGMT_IDR:
	हाल NVME_DSMGMT_IDW:
	शेष:
		/* Not supported yet */
		nvmet_req_complete(req, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम nvmet_file_execute_dsm(काष्ठा nvmet_req *req)
अणु
	अगर (!nvmet_check_data_len_lte(req, nvmet_dsm_len(req)))
		वापस;
	INIT_WORK(&req->f.work, nvmet_file_dsm_work);
	schedule_work(&req->f.work);
पूर्ण

अटल व्योम nvmet_file_ग_लिखो_zeroes_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा nvmet_req *req = container_of(w, काष्ठा nvmet_req, f.work);
	काष्ठा nvme_ग_लिखो_zeroes_cmd *ग_लिखो_zeroes = &req->cmd->ग_लिखो_zeroes;
	पूर्णांक mode = FALLOC_FL_ZERO_RANGE | FALLOC_FL_KEEP_SIZE;
	loff_t offset;
	loff_t len;
	पूर्णांक ret;

	offset = le64_to_cpu(ग_लिखो_zeroes->slba) << req->ns->blksize_shअगरt;
	len = (((sector_t)le16_to_cpu(ग_लिखो_zeroes->length) + 1) <<
			req->ns->blksize_shअगरt);

	अगर (unlikely(offset + len > req->ns->size)) अणु
		nvmet_req_complete(req, त्रुटि_सं_to_nvme_status(req, -ENOSPC));
		वापस;
	पूर्ण

	ret = vfs_fallocate(req->ns->file, mode, offset, len);
	nvmet_req_complete(req, ret < 0 ? त्रुटि_सं_to_nvme_status(req, ret) : 0);
पूर्ण

अटल व्योम nvmet_file_execute_ग_लिखो_zeroes(काष्ठा nvmet_req *req)
अणु
	अगर (!nvmet_check_transfer_len(req, 0))
		वापस;
	INIT_WORK(&req->f.work, nvmet_file_ग_लिखो_zeroes_work);
	schedule_work(&req->f.work);
पूर्ण

u16 nvmet_file_parse_io_cmd(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvme_command *cmd = req->cmd;

	चयन (cmd->common.opcode) अणु
	हाल nvme_cmd_पढ़ो:
	हाल nvme_cmd_ग_लिखो:
		req->execute = nvmet_file_execute_rw;
		वापस 0;
	हाल nvme_cmd_flush:
		req->execute = nvmet_file_execute_flush;
		वापस 0;
	हाल nvme_cmd_dsm:
		req->execute = nvmet_file_execute_dsm;
		वापस 0;
	हाल nvme_cmd_ग_लिखो_zeroes:
		req->execute = nvmet_file_execute_ग_लिखो_zeroes;
		वापस 0;
	शेष:
		वापस nvmet_report_invalid_opcode(req);
	पूर्ण
पूर्ण
