<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVM Express device driver
 * Copyright (c) 2011-2014, Intel Corporation.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/aer.h>
#समावेश <linux/async.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/blk-mq-pci.h>
#समावेश <linux/dmi.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/once.h>
#समावेश <linux/pci.h>
#समावेश <linux/suspend.h>
#समावेश <linux/t10-pi.h>
#समावेश <linux/types.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/io-64-nonatomic-hi-lo.h>
#समावेश <linux/sed-opal.h>
#समावेश <linux/pci-p2pdma.h>

#समावेश "trace.h"
#समावेश "nvme.h"

#घोषणा SQ_SIZE(q)	((q)->q_depth << (q)->sqes)
#घोषणा CQ_SIZE(q)	((q)->q_depth * माप(काष्ठा nvme_completion))

#घोषणा SGES_PER_PAGE	(PAGE_SIZE / माप(काष्ठा nvme_sgl_desc))

/*
 * These can be higher, but we need to ensure that any command करोesn't
 * require an sg allocation that needs more than a page of data.
 */
#घोषणा NVME_MAX_KB_SZ	4096
#घोषणा NVME_MAX_SEGS	127

अटल पूर्णांक use_thपढ़ोed_पूर्णांकerrupts;
module_param(use_thपढ़ोed_पूर्णांकerrupts, पूर्णांक, 0);

अटल bool use_cmb_sqes = true;
module_param(use_cmb_sqes, bool, 0444);
MODULE_PARM_DESC(use_cmb_sqes, "use controller's memory buffer for I/O SQes");

अटल अचिन्हित पूर्णांक max_host_mem_size_mb = 128;
module_param(max_host_mem_size_mb, uपूर्णांक, 0444);
MODULE_PARM_DESC(max_host_mem_size_mb,
	"Maximum Host Memory Buffer (HMB) size per controller (in MiB)");

अटल अचिन्हित पूर्णांक sgl_threshold = SZ_32K;
module_param(sgl_threshold, uपूर्णांक, 0644);
MODULE_PARM_DESC(sgl_threshold,
		"Use SGLs when average request segment size is larger or equal to "
		"this size. Use 0 to disable SGLs.");

अटल पूर्णांक io_queue_depth_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल स्थिर काष्ठा kernel_param_ops io_queue_depth_ops = अणु
	.set = io_queue_depth_set,
	.get = param_get_uपूर्णांक,
पूर्ण;

अटल अचिन्हित पूर्णांक io_queue_depth = 1024;
module_param_cb(io_queue_depth, &io_queue_depth_ops, &io_queue_depth, 0644);
MODULE_PARM_DESC(io_queue_depth, "set io queue depth, should >= 2");

अटल पूर्णांक io_queue_count_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित पूर्णांक n;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(val, 10, &n);
	अगर (ret != 0 || n > num_possible_cpus())
		वापस -EINVAL;
	वापस param_set_uपूर्णांक(val, kp);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops io_queue_count_ops = अणु
	.set = io_queue_count_set,
	.get = param_get_uपूर्णांक,
पूर्ण;

अटल अचिन्हित पूर्णांक ग_लिखो_queues;
module_param_cb(ग_लिखो_queues, &io_queue_count_ops, &ग_लिखो_queues, 0644);
MODULE_PARM_DESC(ग_लिखो_queues,
	"Number of queues to use for writes. If not set, reads and writes "
	"will share a queue set.");

अटल अचिन्हित पूर्णांक poll_queues;
module_param_cb(poll_queues, &io_queue_count_ops, &poll_queues, 0644);
MODULE_PARM_DESC(poll_queues, "Number of queues to use for polled IO.");

अटल bool noacpi;
module_param(noacpi, bool, 0444);
MODULE_PARM_DESC(noacpi, "disable acpi bios quirks");

काष्ठा nvme_dev;
काष्ठा nvme_queue;

अटल व्योम nvme_dev_disable(काष्ठा nvme_dev *dev, bool shutकरोwn);
अटल bool __nvme_disable_io_queues(काष्ठा nvme_dev *dev, u8 opcode);

/*
 * Represents an NVM Express device.  Each nvme_dev is a PCI function.
 */
काष्ठा nvme_dev अणु
	काष्ठा nvme_queue *queues;
	काष्ठा blk_mq_tag_set tagset;
	काष्ठा blk_mq_tag_set admin_tagset;
	u32 __iomem *dbs;
	काष्ठा device *dev;
	काष्ठा dma_pool *prp_page_pool;
	काष्ठा dma_pool *prp_small_pool;
	अचिन्हित online_queues;
	अचिन्हित max_qid;
	अचिन्हित io_queues[HCTX_MAX_TYPES];
	अचिन्हित पूर्णांक num_vecs;
	u32 q_depth;
	पूर्णांक io_sqes;
	u32 db_stride;
	व्योम __iomem *bar;
	अचिन्हित दीर्घ bar_mapped_size;
	काष्ठा work_काष्ठा हटाओ_work;
	काष्ठा mutex shutकरोwn_lock;
	bool subप्रणाली;
	u64 cmb_size;
	bool cmb_use_sqes;
	u32 cmbsz;
	u32 cmbloc;
	काष्ठा nvme_ctrl ctrl;
	u32 last_ps;

	mempool_t *iod_mempool;

	/* shaकरोw करोorbell buffer support: */
	u32 *dbbuf_dbs;
	dma_addr_t dbbuf_dbs_dma_addr;
	u32 *dbbuf_eis;
	dma_addr_t dbbuf_eis_dma_addr;

	/* host memory buffer support: */
	u64 host_mem_size;
	u32 nr_host_mem_descs;
	dma_addr_t host_mem_descs_dma;
	काष्ठा nvme_host_mem_buf_desc *host_mem_descs;
	व्योम **host_mem_desc_bufs;
	अचिन्हित पूर्णांक nr_allocated_queues;
	अचिन्हित पूर्णांक nr_ग_लिखो_queues;
	अचिन्हित पूर्णांक nr_poll_queues;
पूर्ण;

अटल पूर्णांक io_queue_depth_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;
	u32 n;

	ret = kstrtou32(val, 10, &n);
	अगर (ret != 0 || n < 2)
		वापस -EINVAL;

	वापस param_set_uपूर्णांक(val, kp);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक sq_idx(अचिन्हित पूर्णांक qid, u32 stride)
अणु
	वापस qid * 2 * stride;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cq_idx(अचिन्हित पूर्णांक qid, u32 stride)
अणु
	वापस (qid * 2 + 1) * stride;
पूर्ण

अटल अंतरभूत काष्ठा nvme_dev *to_nvme_dev(काष्ठा nvme_ctrl *ctrl)
अणु
	वापस container_of(ctrl, काष्ठा nvme_dev, ctrl);
पूर्ण

/*
 * An NVM Express queue.  Each device has at least two (one क्रम admin
 * commands and one क्रम I/O commands).
 */
काष्ठा nvme_queue अणु
	काष्ठा nvme_dev *dev;
	spinlock_t sq_lock;
	व्योम *sq_cmds;
	 /* only used क्रम poll queues: */
	spinlock_t cq_poll_lock ____cacheline_aligned_in_smp;
	काष्ठा nvme_completion *cqes;
	dma_addr_t sq_dma_addr;
	dma_addr_t cq_dma_addr;
	u32 __iomem *q_db;
	u32 q_depth;
	u16 cq_vector;
	u16 sq_tail;
	u16 last_sq_tail;
	u16 cq_head;
	u16 qid;
	u8 cq_phase;
	u8 sqes;
	अचिन्हित दीर्घ flags;
#घोषणा NVMEQ_ENABLED		0
#घोषणा NVMEQ_SQ_CMB		1
#घोषणा NVMEQ_DELETE_ERROR	2
#घोषणा NVMEQ_POLLED		3
	u32 *dbbuf_sq_db;
	u32 *dbbuf_cq_db;
	u32 *dbbuf_sq_ei;
	u32 *dbbuf_cq_ei;
	काष्ठा completion delete_करोne;
पूर्ण;

/*
 * The nvme_iod describes the data in an I/O.
 *
 * The sg poपूर्णांकer contains the list of PRP/SGL chunk allocations in addition
 * to the actual काष्ठा scatterlist.
 */
काष्ठा nvme_iod अणु
	काष्ठा nvme_request req;
	काष्ठा nvme_command cmd;
	काष्ठा nvme_queue *nvmeq;
	bool use_sgl;
	पूर्णांक पातed;
	पूर्णांक npages;		/* In the PRP list. 0 means small pool in use */
	पूर्णांक nents;		/* Used in scatterlist */
	dma_addr_t first_dma;
	अचिन्हित पूर्णांक dma_len;	/* length of single DMA segment mapping */
	dma_addr_t meta_dma;
	काष्ठा scatterlist *sg;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक nvme_dbbuf_size(काष्ठा nvme_dev *dev)
अणु
	वापस dev->nr_allocated_queues * 8 * dev->db_stride;
पूर्ण

अटल पूर्णांक nvme_dbbuf_dma_alloc(काष्ठा nvme_dev *dev)
अणु
	अचिन्हित पूर्णांक mem_size = nvme_dbbuf_size(dev);

	अगर (dev->dbbuf_dbs)
		वापस 0;

	dev->dbbuf_dbs = dma_alloc_coherent(dev->dev, mem_size,
					    &dev->dbbuf_dbs_dma_addr,
					    GFP_KERNEL);
	अगर (!dev->dbbuf_dbs)
		वापस -ENOMEM;
	dev->dbbuf_eis = dma_alloc_coherent(dev->dev, mem_size,
					    &dev->dbbuf_eis_dma_addr,
					    GFP_KERNEL);
	अगर (!dev->dbbuf_eis) अणु
		dma_मुक्त_coherent(dev->dev, mem_size,
				  dev->dbbuf_dbs, dev->dbbuf_dbs_dma_addr);
		dev->dbbuf_dbs = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nvme_dbbuf_dma_मुक्त(काष्ठा nvme_dev *dev)
अणु
	अचिन्हित पूर्णांक mem_size = nvme_dbbuf_size(dev);

	अगर (dev->dbbuf_dbs) अणु
		dma_मुक्त_coherent(dev->dev, mem_size,
				  dev->dbbuf_dbs, dev->dbbuf_dbs_dma_addr);
		dev->dbbuf_dbs = शून्य;
	पूर्ण
	अगर (dev->dbbuf_eis) अणु
		dma_मुक्त_coherent(dev->dev, mem_size,
				  dev->dbbuf_eis, dev->dbbuf_eis_dma_addr);
		dev->dbbuf_eis = शून्य;
	पूर्ण
पूर्ण

अटल व्योम nvme_dbbuf_init(काष्ठा nvme_dev *dev,
			    काष्ठा nvme_queue *nvmeq, पूर्णांक qid)
अणु
	अगर (!dev->dbbuf_dbs || !qid)
		वापस;

	nvmeq->dbbuf_sq_db = &dev->dbbuf_dbs[sq_idx(qid, dev->db_stride)];
	nvmeq->dbbuf_cq_db = &dev->dbbuf_dbs[cq_idx(qid, dev->db_stride)];
	nvmeq->dbbuf_sq_ei = &dev->dbbuf_eis[sq_idx(qid, dev->db_stride)];
	nvmeq->dbbuf_cq_ei = &dev->dbbuf_eis[cq_idx(qid, dev->db_stride)];
पूर्ण

अटल व्योम nvme_dbbuf_मुक्त(काष्ठा nvme_queue *nvmeq)
अणु
	अगर (!nvmeq->qid)
		वापस;

	nvmeq->dbbuf_sq_db = शून्य;
	nvmeq->dbbuf_cq_db = शून्य;
	nvmeq->dbbuf_sq_ei = शून्य;
	nvmeq->dbbuf_cq_ei = शून्य;
पूर्ण

अटल व्योम nvme_dbbuf_set(काष्ठा nvme_dev *dev)
अणु
	काष्ठा nvme_command c;
	अचिन्हित पूर्णांक i;

	अगर (!dev->dbbuf_dbs)
		वापस;

	स_रखो(&c, 0, माप(c));
	c.dbbuf.opcode = nvme_admin_dbbuf;
	c.dbbuf.prp1 = cpu_to_le64(dev->dbbuf_dbs_dma_addr);
	c.dbbuf.prp2 = cpu_to_le64(dev->dbbuf_eis_dma_addr);

	अगर (nvme_submit_sync_cmd(dev->ctrl.admin_q, &c, शून्य, 0)) अणु
		dev_warn(dev->ctrl.device, "unable to set dbbuf\n");
		/* Free memory and जारी on */
		nvme_dbbuf_dma_मुक्त(dev);

		क्रम (i = 1; i <= dev->online_queues; i++)
			nvme_dbbuf_मुक्त(&dev->queues[i]);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक nvme_dbbuf_need_event(u16 event_idx, u16 new_idx, u16 old)
अणु
	वापस (u16)(new_idx - event_idx - 1) < (u16)(new_idx - old);
पूर्ण

/* Update dbbuf and वापस true अगर an MMIO is required */
अटल bool nvme_dbbuf_update_and_check_event(u16 value, u32 *dbbuf_db,
					      अस्थिर u32 *dbbuf_ei)
अणु
	अगर (dbbuf_db) अणु
		u16 old_value;

		/*
		 * Ensure that the queue is written beक्रमe updating
		 * the करोorbell in memory
		 */
		wmb();

		old_value = *dbbuf_db;
		*dbbuf_db = value;

		/*
		 * Ensure that the करोorbell is updated beक्रमe पढ़ोing the event
		 * index from memory.  The controller needs to provide similar
		 * ordering to ensure the envent index is updated beक्रमe पढ़ोing
		 * the करोorbell.
		 */
		mb();

		अगर (!nvme_dbbuf_need_event(*dbbuf_ei, value, old_value))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Will slightly overestimate the number of pages needed.  This is OK
 * as it only leads to a small amount of wasted memory क्रम the lअगरeसमय of
 * the I/O.
 */
अटल पूर्णांक nvme_pci_npages_prp(व्योम)
अणु
	अचिन्हित nprps = DIV_ROUND_UP(NVME_MAX_KB_SZ + NVME_CTRL_PAGE_SIZE,
				      NVME_CTRL_PAGE_SIZE);
	वापस DIV_ROUND_UP(8 * nprps, PAGE_SIZE - 8);
पूर्ण

/*
 * Calculates the number of pages needed क्रम the SGL segments. For example a 4k
 * page can accommodate 256 SGL descriptors.
 */
अटल पूर्णांक nvme_pci_npages_sgl(व्योम)
अणु
	वापस DIV_ROUND_UP(NVME_MAX_SEGS * माप(काष्ठा nvme_sgl_desc),
			PAGE_SIZE);
पूर्ण

अटल माप_प्रकार nvme_pci_iod_alloc_size(व्योम)
अणु
	माप_प्रकार npages = max(nvme_pci_npages_prp(), nvme_pci_npages_sgl());

	वापस माप(__le64 *) * npages +
		माप(काष्ठा scatterlist) * NVME_MAX_SEGS;
पूर्ण

अटल पूर्णांक nvme_admin_init_hctx(काष्ठा blk_mq_hw_ctx *hctx, व्योम *data,
				अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nvme_dev *dev = data;
	काष्ठा nvme_queue *nvmeq = &dev->queues[0];

	WARN_ON(hctx_idx != 0);
	WARN_ON(dev->admin_tagset.tags[0] != hctx->tags);

	hctx->driver_data = nvmeq;
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_init_hctx(काष्ठा blk_mq_hw_ctx *hctx, व्योम *data,
			  अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nvme_dev *dev = data;
	काष्ठा nvme_queue *nvmeq = &dev->queues[hctx_idx + 1];

	WARN_ON(dev->tagset.tags[hctx_idx] != hctx->tags);
	hctx->driver_data = nvmeq;
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_init_request(काष्ठा blk_mq_tag_set *set, काष्ठा request *req,
		अचिन्हित पूर्णांक hctx_idx, अचिन्हित पूर्णांक numa_node)
अणु
	काष्ठा nvme_dev *dev = set->driver_data;
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);
	पूर्णांक queue_idx = (set == &dev->tagset) ? hctx_idx + 1 : 0;
	काष्ठा nvme_queue *nvmeq = &dev->queues[queue_idx];

	BUG_ON(!nvmeq);
	iod->nvmeq = nvmeq;

	nvme_req(req)->ctrl = &dev->ctrl;
	nvme_req(req)->cmd = &iod->cmd;
	वापस 0;
पूर्ण

अटल पूर्णांक queue_irq_offset(काष्ठा nvme_dev *dev)
अणु
	/* अगर we have more than 1 vec, admin queue offsets us by 1 */
	अगर (dev->num_vecs > 1)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक nvme_pci_map_queues(काष्ठा blk_mq_tag_set *set)
अणु
	काष्ठा nvme_dev *dev = set->driver_data;
	पूर्णांक i, qoff, offset;

	offset = queue_irq_offset(dev);
	क्रम (i = 0, qoff = 0; i < set->nr_maps; i++) अणु
		काष्ठा blk_mq_queue_map *map = &set->map[i];

		map->nr_queues = dev->io_queues[i];
		अगर (!map->nr_queues) अणु
			BUG_ON(i == HCTX_TYPE_DEFAULT);
			जारी;
		पूर्ण

		/*
		 * The poll queue(s) करोesn't have an IRQ (and hence IRQ
		 * affinity), so use the regular blk-mq cpu mapping
		 */
		map->queue_offset = qoff;
		अगर (i != HCTX_TYPE_POLL && offset)
			blk_mq_pci_map_queues(map, to_pci_dev(dev->dev), offset);
		अन्यथा
			blk_mq_map_queues(map);
		qoff += map->nr_queues;
		offset += map->nr_queues;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Write sq tail अगर we are asked to, or अगर the next command would wrap.
 */
अटल अंतरभूत व्योम nvme_ग_लिखो_sq_db(काष्ठा nvme_queue *nvmeq, bool ग_लिखो_sq)
अणु
	अगर (!ग_लिखो_sq) अणु
		u16 next_tail = nvmeq->sq_tail + 1;

		अगर (next_tail == nvmeq->q_depth)
			next_tail = 0;
		अगर (next_tail != nvmeq->last_sq_tail)
			वापस;
	पूर्ण

	अगर (nvme_dbbuf_update_and_check_event(nvmeq->sq_tail,
			nvmeq->dbbuf_sq_db, nvmeq->dbbuf_sq_ei))
		ग_लिखोl(nvmeq->sq_tail, nvmeq->q_db);
	nvmeq->last_sq_tail = nvmeq->sq_tail;
पूर्ण

/**
 * nvme_submit_cmd() - Copy a command पूर्णांकo a queue and ring the करोorbell
 * @nvmeq: The queue to use
 * @cmd: The command to send
 * @ग_लिखो_sq: whether to ग_लिखो to the SQ करोorbell
 */
अटल व्योम nvme_submit_cmd(काष्ठा nvme_queue *nvmeq, काष्ठा nvme_command *cmd,
			    bool ग_लिखो_sq)
अणु
	spin_lock(&nvmeq->sq_lock);
	स_नकल(nvmeq->sq_cmds + (nvmeq->sq_tail << nvmeq->sqes),
	       cmd, माप(*cmd));
	अगर (++nvmeq->sq_tail == nvmeq->q_depth)
		nvmeq->sq_tail = 0;
	nvme_ग_लिखो_sq_db(nvmeq, ग_लिखो_sq);
	spin_unlock(&nvmeq->sq_lock);
पूर्ण

अटल व्योम nvme_commit_rqs(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा nvme_queue *nvmeq = hctx->driver_data;

	spin_lock(&nvmeq->sq_lock);
	अगर (nvmeq->sq_tail != nvmeq->last_sq_tail)
		nvme_ग_लिखो_sq_db(nvmeq, true);
	spin_unlock(&nvmeq->sq_lock);
पूर्ण

अटल व्योम **nvme_pci_iod_list(काष्ठा request *req)
अणु
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);
	वापस (व्योम **)(iod->sg + blk_rq_nr_phys_segments(req));
पूर्ण

अटल अंतरभूत bool nvme_pci_use_sgls(काष्ठा nvme_dev *dev, काष्ठा request *req)
अणु
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);
	पूर्णांक nseg = blk_rq_nr_phys_segments(req);
	अचिन्हित पूर्णांक avg_seg_size;

	avg_seg_size = DIV_ROUND_UP(blk_rq_payload_bytes(req), nseg);

	अगर (!(dev->ctrl.sgls & ((1 << 0) | (1 << 1))))
		वापस false;
	अगर (!iod->nvmeq->qid)
		वापस false;
	अगर (!sgl_threshold || avg_seg_size < sgl_threshold)
		वापस false;
	वापस true;
पूर्ण

अटल व्योम nvme_मुक्त_prps(काष्ठा nvme_dev *dev, काष्ठा request *req)
अणु
	स्थिर पूर्णांक last_prp = NVME_CTRL_PAGE_SIZE / माप(__le64) - 1;
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);
	dma_addr_t dma_addr = iod->first_dma;
	पूर्णांक i;

	क्रम (i = 0; i < iod->npages; i++) अणु
		__le64 *prp_list = nvme_pci_iod_list(req)[i];
		dma_addr_t next_dma_addr = le64_to_cpu(prp_list[last_prp]);

		dma_pool_मुक्त(dev->prp_page_pool, prp_list, dma_addr);
		dma_addr = next_dma_addr;
	पूर्ण

पूर्ण

अटल व्योम nvme_मुक्त_sgls(काष्ठा nvme_dev *dev, काष्ठा request *req)
अणु
	स्थिर पूर्णांक last_sg = SGES_PER_PAGE - 1;
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);
	dma_addr_t dma_addr = iod->first_dma;
	पूर्णांक i;

	क्रम (i = 0; i < iod->npages; i++) अणु
		काष्ठा nvme_sgl_desc *sg_list = nvme_pci_iod_list(req)[i];
		dma_addr_t next_dma_addr = le64_to_cpu((sg_list[last_sg]).addr);

		dma_pool_मुक्त(dev->prp_page_pool, sg_list, dma_addr);
		dma_addr = next_dma_addr;
	पूर्ण

पूर्ण

अटल व्योम nvme_unmap_sg(काष्ठा nvme_dev *dev, काष्ठा request *req)
अणु
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);

	अगर (is_pci_p2pdma_page(sg_page(iod->sg)))
		pci_p2pdma_unmap_sg(dev->dev, iod->sg, iod->nents,
				    rq_dma_dir(req));
	अन्यथा
		dma_unmap_sg(dev->dev, iod->sg, iod->nents, rq_dma_dir(req));
पूर्ण

अटल व्योम nvme_unmap_data(काष्ठा nvme_dev *dev, काष्ठा request *req)
अणु
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);

	अगर (iod->dma_len) अणु
		dma_unmap_page(dev->dev, iod->first_dma, iod->dma_len,
			       rq_dma_dir(req));
		वापस;
	पूर्ण

	WARN_ON_ONCE(!iod->nents);

	nvme_unmap_sg(dev, req);
	अगर (iod->npages == 0)
		dma_pool_मुक्त(dev->prp_small_pool, nvme_pci_iod_list(req)[0],
			      iod->first_dma);
	अन्यथा अगर (iod->use_sgl)
		nvme_मुक्त_sgls(dev, req);
	अन्यथा
		nvme_मुक्त_prps(dev, req);
	mempool_मुक्त(iod->sg, dev->iod_mempool);
पूर्ण

अटल व्योम nvme_prपूर्णांक_sgl(काष्ठा scatterlist *sgl, पूर्णांक nents)
अणु
	पूर्णांक i;
	काष्ठा scatterlist *sg;

	क्रम_each_sg(sgl, sg, nents, i) अणु
		dma_addr_t phys = sg_phys(sg);
		pr_warn("sg[%d] phys_addr:%pad offset:%d length:%d "
			"dma_address:%pad dma_length:%d\n",
			i, &phys, sg->offset, sg->length, &sg_dma_address(sg),
			sg_dma_len(sg));
	पूर्ण
पूर्ण

अटल blk_status_t nvme_pci_setup_prps(काष्ठा nvme_dev *dev,
		काष्ठा request *req, काष्ठा nvme_rw_command *cmnd)
अणु
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);
	काष्ठा dma_pool *pool;
	पूर्णांक length = blk_rq_payload_bytes(req);
	काष्ठा scatterlist *sg = iod->sg;
	पूर्णांक dma_len = sg_dma_len(sg);
	u64 dma_addr = sg_dma_address(sg);
	पूर्णांक offset = dma_addr & (NVME_CTRL_PAGE_SIZE - 1);
	__le64 *prp_list;
	व्योम **list = nvme_pci_iod_list(req);
	dma_addr_t prp_dma;
	पूर्णांक nprps, i;

	length -= (NVME_CTRL_PAGE_SIZE - offset);
	अगर (length <= 0) अणु
		iod->first_dma = 0;
		जाओ करोne;
	पूर्ण

	dma_len -= (NVME_CTRL_PAGE_SIZE - offset);
	अगर (dma_len) अणु
		dma_addr += (NVME_CTRL_PAGE_SIZE - offset);
	पूर्ण अन्यथा अणु
		sg = sg_next(sg);
		dma_addr = sg_dma_address(sg);
		dma_len = sg_dma_len(sg);
	पूर्ण

	अगर (length <= NVME_CTRL_PAGE_SIZE) अणु
		iod->first_dma = dma_addr;
		जाओ करोne;
	पूर्ण

	nprps = DIV_ROUND_UP(length, NVME_CTRL_PAGE_SIZE);
	अगर (nprps <= (256 / 8)) अणु
		pool = dev->prp_small_pool;
		iod->npages = 0;
	पूर्ण अन्यथा अणु
		pool = dev->prp_page_pool;
		iod->npages = 1;
	पूर्ण

	prp_list = dma_pool_alloc(pool, GFP_ATOMIC, &prp_dma);
	अगर (!prp_list) अणु
		iod->first_dma = dma_addr;
		iod->npages = -1;
		वापस BLK_STS_RESOURCE;
	पूर्ण
	list[0] = prp_list;
	iod->first_dma = prp_dma;
	i = 0;
	क्रम (;;) अणु
		अगर (i == NVME_CTRL_PAGE_SIZE >> 3) अणु
			__le64 *old_prp_list = prp_list;
			prp_list = dma_pool_alloc(pool, GFP_ATOMIC, &prp_dma);
			अगर (!prp_list)
				जाओ मुक्त_prps;
			list[iod->npages++] = prp_list;
			prp_list[0] = old_prp_list[i - 1];
			old_prp_list[i - 1] = cpu_to_le64(prp_dma);
			i = 1;
		पूर्ण
		prp_list[i++] = cpu_to_le64(dma_addr);
		dma_len -= NVME_CTRL_PAGE_SIZE;
		dma_addr += NVME_CTRL_PAGE_SIZE;
		length -= NVME_CTRL_PAGE_SIZE;
		अगर (length <= 0)
			अवरोध;
		अगर (dma_len > 0)
			जारी;
		अगर (unlikely(dma_len < 0))
			जाओ bad_sgl;
		sg = sg_next(sg);
		dma_addr = sg_dma_address(sg);
		dma_len = sg_dma_len(sg);
	पूर्ण
करोne:
	cmnd->dptr.prp1 = cpu_to_le64(sg_dma_address(iod->sg));
	cmnd->dptr.prp2 = cpu_to_le64(iod->first_dma);
	वापस BLK_STS_OK;
मुक्त_prps:
	nvme_मुक्त_prps(dev, req);
	वापस BLK_STS_RESOURCE;
bad_sgl:
	WARN(DO_ONCE(nvme_prपूर्णांक_sgl, iod->sg, iod->nents),
			"Invalid SGL for payload:%d nents:%d\n",
			blk_rq_payload_bytes(req), iod->nents);
	वापस BLK_STS_IOERR;
पूर्ण

अटल व्योम nvme_pci_sgl_set_data(काष्ठा nvme_sgl_desc *sge,
		काष्ठा scatterlist *sg)
अणु
	sge->addr = cpu_to_le64(sg_dma_address(sg));
	sge->length = cpu_to_le32(sg_dma_len(sg));
	sge->type = NVME_SGL_FMT_DATA_DESC << 4;
पूर्ण

अटल व्योम nvme_pci_sgl_set_seg(काष्ठा nvme_sgl_desc *sge,
		dma_addr_t dma_addr, पूर्णांक entries)
अणु
	sge->addr = cpu_to_le64(dma_addr);
	अगर (entries < SGES_PER_PAGE) अणु
		sge->length = cpu_to_le32(entries * माप(*sge));
		sge->type = NVME_SGL_FMT_LAST_SEG_DESC << 4;
	पूर्ण अन्यथा अणु
		sge->length = cpu_to_le32(PAGE_SIZE);
		sge->type = NVME_SGL_FMT_SEG_DESC << 4;
	पूर्ण
पूर्ण

अटल blk_status_t nvme_pci_setup_sgls(काष्ठा nvme_dev *dev,
		काष्ठा request *req, काष्ठा nvme_rw_command *cmd, पूर्णांक entries)
अणु
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);
	काष्ठा dma_pool *pool;
	काष्ठा nvme_sgl_desc *sg_list;
	काष्ठा scatterlist *sg = iod->sg;
	dma_addr_t sgl_dma;
	पूर्णांक i = 0;

	/* setting the transfer type as SGL */
	cmd->flags = NVME_CMD_SGL_METABUF;

	अगर (entries == 1) अणु
		nvme_pci_sgl_set_data(&cmd->dptr.sgl, sg);
		वापस BLK_STS_OK;
	पूर्ण

	अगर (entries <= (256 / माप(काष्ठा nvme_sgl_desc))) अणु
		pool = dev->prp_small_pool;
		iod->npages = 0;
	पूर्ण अन्यथा अणु
		pool = dev->prp_page_pool;
		iod->npages = 1;
	पूर्ण

	sg_list = dma_pool_alloc(pool, GFP_ATOMIC, &sgl_dma);
	अगर (!sg_list) अणु
		iod->npages = -1;
		वापस BLK_STS_RESOURCE;
	पूर्ण

	nvme_pci_iod_list(req)[0] = sg_list;
	iod->first_dma = sgl_dma;

	nvme_pci_sgl_set_seg(&cmd->dptr.sgl, sgl_dma, entries);

	करो अणु
		अगर (i == SGES_PER_PAGE) अणु
			काष्ठा nvme_sgl_desc *old_sg_desc = sg_list;
			काष्ठा nvme_sgl_desc *link = &old_sg_desc[i - 1];

			sg_list = dma_pool_alloc(pool, GFP_ATOMIC, &sgl_dma);
			अगर (!sg_list)
				जाओ मुक्त_sgls;

			i = 0;
			nvme_pci_iod_list(req)[iod->npages++] = sg_list;
			sg_list[i++] = *link;
			nvme_pci_sgl_set_seg(link, sgl_dma, entries);
		पूर्ण

		nvme_pci_sgl_set_data(&sg_list[i++], sg);
		sg = sg_next(sg);
	पूर्ण जबतक (--entries > 0);

	वापस BLK_STS_OK;
मुक्त_sgls:
	nvme_मुक्त_sgls(dev, req);
	वापस BLK_STS_RESOURCE;
पूर्ण

अटल blk_status_t nvme_setup_prp_simple(काष्ठा nvme_dev *dev,
		काष्ठा request *req, काष्ठा nvme_rw_command *cmnd,
		काष्ठा bio_vec *bv)
अणु
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);
	अचिन्हित पूर्णांक offset = bv->bv_offset & (NVME_CTRL_PAGE_SIZE - 1);
	अचिन्हित पूर्णांक first_prp_len = NVME_CTRL_PAGE_SIZE - offset;

	iod->first_dma = dma_map_bvec(dev->dev, bv, rq_dma_dir(req), 0);
	अगर (dma_mapping_error(dev->dev, iod->first_dma))
		वापस BLK_STS_RESOURCE;
	iod->dma_len = bv->bv_len;

	cmnd->dptr.prp1 = cpu_to_le64(iod->first_dma);
	अगर (bv->bv_len > first_prp_len)
		cmnd->dptr.prp2 = cpu_to_le64(iod->first_dma + first_prp_len);
	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t nvme_setup_sgl_simple(काष्ठा nvme_dev *dev,
		काष्ठा request *req, काष्ठा nvme_rw_command *cmnd,
		काष्ठा bio_vec *bv)
अणु
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);

	iod->first_dma = dma_map_bvec(dev->dev, bv, rq_dma_dir(req), 0);
	अगर (dma_mapping_error(dev->dev, iod->first_dma))
		वापस BLK_STS_RESOURCE;
	iod->dma_len = bv->bv_len;

	cmnd->flags = NVME_CMD_SGL_METABUF;
	cmnd->dptr.sgl.addr = cpu_to_le64(iod->first_dma);
	cmnd->dptr.sgl.length = cpu_to_le32(iod->dma_len);
	cmnd->dptr.sgl.type = NVME_SGL_FMT_DATA_DESC << 4;
	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t nvme_map_data(काष्ठा nvme_dev *dev, काष्ठा request *req,
		काष्ठा nvme_command *cmnd)
अणु
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);
	blk_status_t ret = BLK_STS_RESOURCE;
	पूर्णांक nr_mapped;

	अगर (blk_rq_nr_phys_segments(req) == 1) अणु
		काष्ठा bio_vec bv = req_bvec(req);

		अगर (!is_pci_p2pdma_page(bv.bv_page)) अणु
			अगर (bv.bv_offset + bv.bv_len <= NVME_CTRL_PAGE_SIZE * 2)
				वापस nvme_setup_prp_simple(dev, req,
							     &cmnd->rw, &bv);

			अगर (iod->nvmeq->qid && sgl_threshold &&
			    dev->ctrl.sgls & ((1 << 0) | (1 << 1)))
				वापस nvme_setup_sgl_simple(dev, req,
							     &cmnd->rw, &bv);
		पूर्ण
	पूर्ण

	iod->dma_len = 0;
	iod->sg = mempool_alloc(dev->iod_mempool, GFP_ATOMIC);
	अगर (!iod->sg)
		वापस BLK_STS_RESOURCE;
	sg_init_table(iod->sg, blk_rq_nr_phys_segments(req));
	iod->nents = blk_rq_map_sg(req->q, req, iod->sg);
	अगर (!iod->nents)
		जाओ out_मुक्त_sg;

	अगर (is_pci_p2pdma_page(sg_page(iod->sg)))
		nr_mapped = pci_p2pdma_map_sg_attrs(dev->dev, iod->sg,
				iod->nents, rq_dma_dir(req), DMA_ATTR_NO_WARN);
	अन्यथा
		nr_mapped = dma_map_sg_attrs(dev->dev, iod->sg, iod->nents,
					     rq_dma_dir(req), DMA_ATTR_NO_WARN);
	अगर (!nr_mapped)
		जाओ out_मुक्त_sg;

	iod->use_sgl = nvme_pci_use_sgls(dev, req);
	अगर (iod->use_sgl)
		ret = nvme_pci_setup_sgls(dev, req, &cmnd->rw, nr_mapped);
	अन्यथा
		ret = nvme_pci_setup_prps(dev, req, &cmnd->rw);
	अगर (ret != BLK_STS_OK)
		जाओ out_unmap_sg;
	वापस BLK_STS_OK;

out_unmap_sg:
	nvme_unmap_sg(dev, req);
out_मुक्त_sg:
	mempool_मुक्त(iod->sg, dev->iod_mempool);
	वापस ret;
पूर्ण

अटल blk_status_t nvme_map_metadata(काष्ठा nvme_dev *dev, काष्ठा request *req,
		काष्ठा nvme_command *cmnd)
अणु
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);

	iod->meta_dma = dma_map_bvec(dev->dev, rq_पूर्णांकegrity_vec(req),
			rq_dma_dir(req), 0);
	अगर (dma_mapping_error(dev->dev, iod->meta_dma))
		वापस BLK_STS_IOERR;
	cmnd->rw.metadata = cpu_to_le64(iod->meta_dma);
	वापस BLK_STS_OK;
पूर्ण

/*
 * NOTE: ns is शून्य when called on the admin queue.
 */
अटल blk_status_t nvme_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
			 स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा nvme_ns *ns = hctx->queue->queuedata;
	काष्ठा nvme_queue *nvmeq = hctx->driver_data;
	काष्ठा nvme_dev *dev = nvmeq->dev;
	काष्ठा request *req = bd->rq;
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);
	काष्ठा nvme_command *cmnd = &iod->cmd;
	blk_status_t ret;

	iod->पातed = 0;
	iod->npages = -1;
	iod->nents = 0;

	/*
	 * We should not need to करो this, but we're still using this to
	 * ensure we can drain requests on a dying queue.
	 */
	अगर (unlikely(!test_bit(NVMEQ_ENABLED, &nvmeq->flags)))
		वापस BLK_STS_IOERR;

	अगर (!nvme_check_पढ़ोy(&dev->ctrl, req, true))
		वापस nvme_fail_nonपढ़ोy_command(&dev->ctrl, req);

	ret = nvme_setup_cmd(ns, req);
	अगर (ret)
		वापस ret;

	अगर (blk_rq_nr_phys_segments(req)) अणु
		ret = nvme_map_data(dev, req, cmnd);
		अगर (ret)
			जाओ out_मुक्त_cmd;
	पूर्ण

	अगर (blk_पूर्णांकegrity_rq(req)) अणु
		ret = nvme_map_metadata(dev, req, cmnd);
		अगर (ret)
			जाओ out_unmap_data;
	पूर्ण

	blk_mq_start_request(req);
	nvme_submit_cmd(nvmeq, cmnd, bd->last);
	वापस BLK_STS_OK;
out_unmap_data:
	nvme_unmap_data(dev, req);
out_मुक्त_cmd:
	nvme_cleanup_cmd(req);
	वापस ret;
पूर्ण

अटल व्योम nvme_pci_complete_rq(काष्ठा request *req)
अणु
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);
	काष्ठा nvme_dev *dev = iod->nvmeq->dev;

	अगर (blk_पूर्णांकegrity_rq(req))
		dma_unmap_page(dev->dev, iod->meta_dma,
			       rq_पूर्णांकegrity_vec(req)->bv_len, rq_data_dir(req));
	अगर (blk_rq_nr_phys_segments(req))
		nvme_unmap_data(dev, req);
	nvme_complete_rq(req);
पूर्ण

/* We पढ़ो the CQE phase first to check अगर the rest of the entry is valid */
अटल अंतरभूत bool nvme_cqe_pending(काष्ठा nvme_queue *nvmeq)
अणु
	काष्ठा nvme_completion *hcqe = &nvmeq->cqes[nvmeq->cq_head];

	वापस (le16_to_cpu(READ_ONCE(hcqe->status)) & 1) == nvmeq->cq_phase;
पूर्ण

अटल अंतरभूत व्योम nvme_ring_cq_करोorbell(काष्ठा nvme_queue *nvmeq)
अणु
	u16 head = nvmeq->cq_head;

	अगर (nvme_dbbuf_update_and_check_event(head, nvmeq->dbbuf_cq_db,
					      nvmeq->dbbuf_cq_ei))
		ग_लिखोl(head, nvmeq->q_db + nvmeq->dev->db_stride);
पूर्ण

अटल अंतरभूत काष्ठा blk_mq_tags *nvme_queue_tagset(काष्ठा nvme_queue *nvmeq)
अणु
	अगर (!nvmeq->qid)
		वापस nvmeq->dev->admin_tagset.tags[0];
	वापस nvmeq->dev->tagset.tags[nvmeq->qid - 1];
पूर्ण

अटल अंतरभूत व्योम nvme_handle_cqe(काष्ठा nvme_queue *nvmeq, u16 idx)
अणु
	काष्ठा nvme_completion *cqe = &nvmeq->cqes[idx];
	__u16 command_id = READ_ONCE(cqe->command_id);
	काष्ठा request *req;

	/*
	 * AEN requests are special as they करोn't समय out and can
	 * survive any kind of queue मुक्तze and often करोn't respond to
	 * पातs.  We करोn't even bother to allocate a काष्ठा request
	 * क्रम them but rather special हाल them here.
	 */
	अगर (unlikely(nvme_is_aen_req(nvmeq->qid, command_id))) अणु
		nvme_complete_async_event(&nvmeq->dev->ctrl,
				cqe->status, &cqe->result);
		वापस;
	पूर्ण

	req = blk_mq_tag_to_rq(nvme_queue_tagset(nvmeq), command_id);
	अगर (unlikely(!req)) अणु
		dev_warn(nvmeq->dev->ctrl.device,
			"invalid id %d completed on queue %d\n",
			command_id, le16_to_cpu(cqe->sq_id));
		वापस;
	पूर्ण

	trace_nvme_sq(req, cqe->sq_head, nvmeq->sq_tail);
	अगर (!nvme_try_complete_req(req, cqe->status, cqe->result))
		nvme_pci_complete_rq(req);
पूर्ण

अटल अंतरभूत व्योम nvme_update_cq_head(काष्ठा nvme_queue *nvmeq)
अणु
	u16 पंचांगp = nvmeq->cq_head + 1;

	अगर (पंचांगp == nvmeq->q_depth) अणु
		nvmeq->cq_head = 0;
		nvmeq->cq_phase ^= 1;
	पूर्ण अन्यथा अणु
		nvmeq->cq_head = पंचांगp;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक nvme_process_cq(काष्ठा nvme_queue *nvmeq)
अणु
	पूर्णांक found = 0;

	जबतक (nvme_cqe_pending(nvmeq)) अणु
		found++;
		/*
		 * load-load control dependency between phase and the rest of
		 * the cqe requires a full पढ़ो memory barrier
		 */
		dma_rmb();
		nvme_handle_cqe(nvmeq, nvmeq->cq_head);
		nvme_update_cq_head(nvmeq);
	पूर्ण

	अगर (found)
		nvme_ring_cq_करोorbell(nvmeq);
	वापस found;
पूर्ण

अटल irqवापस_t nvme_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nvme_queue *nvmeq = data;

	अगर (nvme_process_cq(nvmeq))
		वापस IRQ_HANDLED;
	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t nvme_irq_check(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nvme_queue *nvmeq = data;

	अगर (nvme_cqe_pending(nvmeq))
		वापस IRQ_WAKE_THREAD;
	वापस IRQ_NONE;
पूर्ण

/*
 * Poll क्रम completions क्रम any पूर्णांकerrupt driven queue
 * Can be called from any context.
 */
अटल व्योम nvme_poll_irqdisable(काष्ठा nvme_queue *nvmeq)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(nvmeq->dev->dev);

	WARN_ON_ONCE(test_bit(NVMEQ_POLLED, &nvmeq->flags));

	disable_irq(pci_irq_vector(pdev, nvmeq->cq_vector));
	nvme_process_cq(nvmeq);
	enable_irq(pci_irq_vector(pdev, nvmeq->cq_vector));
पूर्ण

अटल पूर्णांक nvme_poll(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा nvme_queue *nvmeq = hctx->driver_data;
	bool found;

	अगर (!nvme_cqe_pending(nvmeq))
		वापस 0;

	spin_lock(&nvmeq->cq_poll_lock);
	found = nvme_process_cq(nvmeq);
	spin_unlock(&nvmeq->cq_poll_lock);

	वापस found;
पूर्ण

अटल व्योम nvme_pci_submit_async_event(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_dev *dev = to_nvme_dev(ctrl);
	काष्ठा nvme_queue *nvmeq = &dev->queues[0];
	काष्ठा nvme_command c;

	स_रखो(&c, 0, माप(c));
	c.common.opcode = nvme_admin_async_event;
	c.common.command_id = NVME_AQ_BLK_MQ_DEPTH;
	nvme_submit_cmd(nvmeq, &c, true);
पूर्ण

अटल पूर्णांक adapter_delete_queue(काष्ठा nvme_dev *dev, u8 opcode, u16 id)
अणु
	काष्ठा nvme_command c;

	स_रखो(&c, 0, माप(c));
	c.delete_queue.opcode = opcode;
	c.delete_queue.qid = cpu_to_le16(id);

	वापस nvme_submit_sync_cmd(dev->ctrl.admin_q, &c, शून्य, 0);
पूर्ण

अटल पूर्णांक adapter_alloc_cq(काष्ठा nvme_dev *dev, u16 qid,
		काष्ठा nvme_queue *nvmeq, s16 vector)
अणु
	काष्ठा nvme_command c;
	पूर्णांक flags = NVME_QUEUE_PHYS_CONTIG;

	अगर (!test_bit(NVMEQ_POLLED, &nvmeq->flags))
		flags |= NVME_CQ_IRQ_ENABLED;

	/*
	 * Note: we (ab)use the fact that the prp fields survive अगर no data
	 * is attached to the request.
	 */
	स_रखो(&c, 0, माप(c));
	c.create_cq.opcode = nvme_admin_create_cq;
	c.create_cq.prp1 = cpu_to_le64(nvmeq->cq_dma_addr);
	c.create_cq.cqid = cpu_to_le16(qid);
	c.create_cq.qsize = cpu_to_le16(nvmeq->q_depth - 1);
	c.create_cq.cq_flags = cpu_to_le16(flags);
	c.create_cq.irq_vector = cpu_to_le16(vector);

	वापस nvme_submit_sync_cmd(dev->ctrl.admin_q, &c, शून्य, 0);
पूर्ण

अटल पूर्णांक adapter_alloc_sq(काष्ठा nvme_dev *dev, u16 qid,
						काष्ठा nvme_queue *nvmeq)
अणु
	काष्ठा nvme_ctrl *ctrl = &dev->ctrl;
	काष्ठा nvme_command c;
	पूर्णांक flags = NVME_QUEUE_PHYS_CONTIG;

	/*
	 * Some drives have a bug that स्वतः-enables WRRU अगर MEDIUM isn't
	 * set. Since URGENT priority is zeroes, it makes all queues
	 * URGENT.
	 */
	अगर (ctrl->quirks & NVME_QUIRK_MEDIUM_PRIO_SQ)
		flags |= NVME_SQ_PRIO_MEDIUM;

	/*
	 * Note: we (ab)use the fact that the prp fields survive अगर no data
	 * is attached to the request.
	 */
	स_रखो(&c, 0, माप(c));
	c.create_sq.opcode = nvme_admin_create_sq;
	c.create_sq.prp1 = cpu_to_le64(nvmeq->sq_dma_addr);
	c.create_sq.sqid = cpu_to_le16(qid);
	c.create_sq.qsize = cpu_to_le16(nvmeq->q_depth - 1);
	c.create_sq.sq_flags = cpu_to_le16(flags);
	c.create_sq.cqid = cpu_to_le16(qid);

	वापस nvme_submit_sync_cmd(dev->ctrl.admin_q, &c, शून्य, 0);
पूर्ण

अटल पूर्णांक adapter_delete_cq(काष्ठा nvme_dev *dev, u16 cqid)
अणु
	वापस adapter_delete_queue(dev, nvme_admin_delete_cq, cqid);
पूर्ण

अटल पूर्णांक adapter_delete_sq(काष्ठा nvme_dev *dev, u16 sqid)
अणु
	वापस adapter_delete_queue(dev, nvme_admin_delete_sq, sqid);
पूर्ण

अटल व्योम पात_endio(काष्ठा request *req, blk_status_t error)
अणु
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);
	काष्ठा nvme_queue *nvmeq = iod->nvmeq;

	dev_warn(nvmeq->dev->ctrl.device,
		 "Abort status: 0x%x", nvme_req(req)->status);
	atomic_inc(&nvmeq->dev->ctrl.पात_limit);
	blk_mq_मुक्त_request(req);
पूर्ण

अटल bool nvme_should_reset(काष्ठा nvme_dev *dev, u32 csts)
अणु
	/* If true, indicates loss of adapter communication, possibly by a
	 * NVMe Subप्रणाली reset.
	 */
	bool nssro = dev->subप्रणाली && (csts & NVME_CSTS_NSSRO);

	/* If there is a reset/reinit ongoing, we shouldn't reset again. */
	चयन (dev->ctrl.state) अणु
	हाल NVME_CTRL_RESETTING:
	हाल NVME_CTRL_CONNECTING:
		वापस false;
	शेष:
		अवरोध;
	पूर्ण

	/* We shouldn't reset unless the controller is on fatal error state
	 * _or_ अगर we lost the communication with it.
	 */
	अगर (!(csts & NVME_CSTS_CFS) && !nssro)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम nvme_warn_reset(काष्ठा nvme_dev *dev, u32 csts)
अणु
	/* Read a config रेजिस्टर to help see what died. */
	u16 pci_status;
	पूर्णांक result;

	result = pci_पढ़ो_config_word(to_pci_dev(dev->dev), PCI_STATUS,
				      &pci_status);
	अगर (result == PCIBIOS_SUCCESSFUL)
		dev_warn(dev->ctrl.device,
			 "controller is down; will reset: CSTS=0x%x, PCI_STATUS=0x%hx\n",
			 csts, pci_status);
	अन्यथा
		dev_warn(dev->ctrl.device,
			 "controller is down; will reset: CSTS=0x%x, PCI_STATUS read failed (%d)\n",
			 csts, result);
पूर्ण

अटल क्रमागत blk_eh_समयr_वापस nvme_समयout(काष्ठा request *req, bool reserved)
अणु
	काष्ठा nvme_iod *iod = blk_mq_rq_to_pdu(req);
	काष्ठा nvme_queue *nvmeq = iod->nvmeq;
	काष्ठा nvme_dev *dev = nvmeq->dev;
	काष्ठा request *पात_req;
	काष्ठा nvme_command cmd;
	u32 csts = पढ़ोl(dev->bar + NVME_REG_CSTS);

	/* If PCI error recovery process is happening, we cannot reset or
	 * the recovery mechanism will surely fail.
	 */
	mb();
	अगर (pci_channel_offline(to_pci_dev(dev->dev)))
		वापस BLK_EH_RESET_TIMER;

	/*
	 * Reset immediately अगर the controller is failed
	 */
	अगर (nvme_should_reset(dev, csts)) अणु
		nvme_warn_reset(dev, csts);
		nvme_dev_disable(dev, false);
		nvme_reset_ctrl(&dev->ctrl);
		वापस BLK_EH_DONE;
	पूर्ण

	/*
	 * Did we miss an पूर्णांकerrupt?
	 */
	अगर (test_bit(NVMEQ_POLLED, &nvmeq->flags))
		nvme_poll(req->mq_hctx);
	अन्यथा
		nvme_poll_irqdisable(nvmeq);

	अगर (blk_mq_request_completed(req)) अणु
		dev_warn(dev->ctrl.device,
			 "I/O %d QID %d timeout, completion polled\n",
			 req->tag, nvmeq->qid);
		वापस BLK_EH_DONE;
	पूर्ण

	/*
	 * Shutकरोwn immediately अगर controller बार out जबतक starting. The
	 * reset work will see the pci device disabled when it माला_लो the क्रमced
	 * cancellation error. All outstanding requests are completed on
	 * shutकरोwn, so we वापस BLK_EH_DONE.
	 */
	चयन (dev->ctrl.state) अणु
	हाल NVME_CTRL_CONNECTING:
		nvme_change_ctrl_state(&dev->ctrl, NVME_CTRL_DELETING);
		fallthrough;
	हाल NVME_CTRL_DELETING:
		dev_warn_ratelimited(dev->ctrl.device,
			 "I/O %d QID %d timeout, disable controller\n",
			 req->tag, nvmeq->qid);
		nvme_req(req)->flags |= NVME_REQ_CANCELLED;
		nvme_dev_disable(dev, true);
		वापस BLK_EH_DONE;
	हाल NVME_CTRL_RESETTING:
		वापस BLK_EH_RESET_TIMER;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Shutकरोwn the controller immediately and schedule a reset अगर the
	 * command was alपढ़ोy पातed once beक्रमe and still hasn't been
	 * वापसed to the driver, or अगर this is the admin queue.
	 */
	अगर (!nvmeq->qid || iod->पातed) अणु
		dev_warn(dev->ctrl.device,
			 "I/O %d QID %d timeout, reset controller\n",
			 req->tag, nvmeq->qid);
		nvme_req(req)->flags |= NVME_REQ_CANCELLED;
		nvme_dev_disable(dev, false);
		nvme_reset_ctrl(&dev->ctrl);

		वापस BLK_EH_DONE;
	पूर्ण

	अगर (atomic_dec_वापस(&dev->ctrl.पात_limit) < 0) अणु
		atomic_inc(&dev->ctrl.पात_limit);
		वापस BLK_EH_RESET_TIMER;
	पूर्ण
	iod->पातed = 1;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.पात.opcode = nvme_admin_पात_cmd;
	cmd.पात.cid = req->tag;
	cmd.पात.sqid = cpu_to_le16(nvmeq->qid);

	dev_warn(nvmeq->dev->ctrl.device,
		"I/O %d QID %d timeout, aborting\n",
		 req->tag, nvmeq->qid);

	पात_req = nvme_alloc_request(dev->ctrl.admin_q, &cmd,
			BLK_MQ_REQ_NOWAIT);
	अगर (IS_ERR(पात_req)) अणु
		atomic_inc(&dev->ctrl.पात_limit);
		वापस BLK_EH_RESET_TIMER;
	पूर्ण

	पात_req->end_io_data = शून्य;
	blk_execute_rq_noरुको(शून्य, पात_req, 0, पात_endio);

	/*
	 * The पातed req will be completed on receiving the पात req.
	 * We enable the समयr again. If hit twice, it'll cause a device reset,
	 * as the device then is in a faulty state.
	 */
	वापस BLK_EH_RESET_TIMER;
पूर्ण

अटल व्योम nvme_मुक्त_queue(काष्ठा nvme_queue *nvmeq)
अणु
	dma_मुक्त_coherent(nvmeq->dev->dev, CQ_SIZE(nvmeq),
				(व्योम *)nvmeq->cqes, nvmeq->cq_dma_addr);
	अगर (!nvmeq->sq_cmds)
		वापस;

	अगर (test_and_clear_bit(NVMEQ_SQ_CMB, &nvmeq->flags)) अणु
		pci_मुक्त_p2pmem(to_pci_dev(nvmeq->dev->dev),
				nvmeq->sq_cmds, SQ_SIZE(nvmeq));
	पूर्ण अन्यथा अणु
		dma_मुक्त_coherent(nvmeq->dev->dev, SQ_SIZE(nvmeq),
				nvmeq->sq_cmds, nvmeq->sq_dma_addr);
	पूर्ण
पूर्ण

अटल व्योम nvme_मुक्त_queues(काष्ठा nvme_dev *dev, पूर्णांक lowest)
अणु
	पूर्णांक i;

	क्रम (i = dev->ctrl.queue_count - 1; i >= lowest; i--) अणु
		dev->ctrl.queue_count--;
		nvme_मुक्त_queue(&dev->queues[i]);
	पूर्ण
पूर्ण

/**
 * nvme_suspend_queue - put queue पूर्णांकo suspended state
 * @nvmeq: queue to suspend
 */
अटल पूर्णांक nvme_suspend_queue(काष्ठा nvme_queue *nvmeq)
अणु
	अगर (!test_and_clear_bit(NVMEQ_ENABLED, &nvmeq->flags))
		वापस 1;

	/* ensure that nvme_queue_rq() sees NVMEQ_ENABLED cleared */
	mb();

	nvmeq->dev->online_queues--;
	अगर (!nvmeq->qid && nvmeq->dev->ctrl.admin_q)
		blk_mq_quiesce_queue(nvmeq->dev->ctrl.admin_q);
	अगर (!test_and_clear_bit(NVMEQ_POLLED, &nvmeq->flags))
		pci_मुक्त_irq(to_pci_dev(nvmeq->dev->dev), nvmeq->cq_vector, nvmeq);
	वापस 0;
पूर्ण

अटल व्योम nvme_suspend_io_queues(काष्ठा nvme_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = dev->ctrl.queue_count - 1; i > 0; i--)
		nvme_suspend_queue(&dev->queues[i]);
पूर्ण

अटल व्योम nvme_disable_admin_queue(काष्ठा nvme_dev *dev, bool shutकरोwn)
अणु
	काष्ठा nvme_queue *nvmeq = &dev->queues[0];

	अगर (shutकरोwn)
		nvme_shutकरोwn_ctrl(&dev->ctrl);
	अन्यथा
		nvme_disable_ctrl(&dev->ctrl);

	nvme_poll_irqdisable(nvmeq);
पूर्ण

/*
 * Called only on a device that has been disabled and after all other thपढ़ोs
 * that can check this device's completion queues have synced, except
 * nvme_poll(). This is the last chance क्रम the driver to see a natural
 * completion beक्रमe nvme_cancel_request() terminates all incomplete requests.
 */
अटल व्योम nvme_reap_pending_cqes(काष्ठा nvme_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = dev->ctrl.queue_count - 1; i > 0; i--) अणु
		spin_lock(&dev->queues[i].cq_poll_lock);
		nvme_process_cq(&dev->queues[i]);
		spin_unlock(&dev->queues[i].cq_poll_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक nvme_cmb_qdepth(काष्ठा nvme_dev *dev, पूर्णांक nr_io_queues,
				पूर्णांक entry_size)
अणु
	पूर्णांक q_depth = dev->q_depth;
	अचिन्हित q_size_aligned = roundup(q_depth * entry_size,
					  NVME_CTRL_PAGE_SIZE);

	अगर (q_size_aligned * nr_io_queues > dev->cmb_size) अणु
		u64 mem_per_q = भाग_u64(dev->cmb_size, nr_io_queues);

		mem_per_q = round_करोwn(mem_per_q, NVME_CTRL_PAGE_SIZE);
		q_depth = भाग_u64(mem_per_q, entry_size);

		/*
		 * Ensure the reduced q_depth is above some threshold where it
		 * would be better to map queues in प्रणाली memory with the
		 * original depth
		 */
		अगर (q_depth < 64)
			वापस -ENOMEM;
	पूर्ण

	वापस q_depth;
पूर्ण

अटल पूर्णांक nvme_alloc_sq_cmds(काष्ठा nvme_dev *dev, काष्ठा nvme_queue *nvmeq,
				पूर्णांक qid)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	अगर (qid && dev->cmb_use_sqes && (dev->cmbsz & NVME_CMBSZ_SQS)) अणु
		nvmeq->sq_cmds = pci_alloc_p2pmem(pdev, SQ_SIZE(nvmeq));
		अगर (nvmeq->sq_cmds) अणु
			nvmeq->sq_dma_addr = pci_p2pmem_virt_to_bus(pdev,
							nvmeq->sq_cmds);
			अगर (nvmeq->sq_dma_addr) अणु
				set_bit(NVMEQ_SQ_CMB, &nvmeq->flags);
				वापस 0;
			पूर्ण

			pci_मुक्त_p2pmem(pdev, nvmeq->sq_cmds, SQ_SIZE(nvmeq));
		पूर्ण
	पूर्ण

	nvmeq->sq_cmds = dma_alloc_coherent(dev->dev, SQ_SIZE(nvmeq),
				&nvmeq->sq_dma_addr, GFP_KERNEL);
	अगर (!nvmeq->sq_cmds)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_alloc_queue(काष्ठा nvme_dev *dev, पूर्णांक qid, पूर्णांक depth)
अणु
	काष्ठा nvme_queue *nvmeq = &dev->queues[qid];

	अगर (dev->ctrl.queue_count > qid)
		वापस 0;

	nvmeq->sqes = qid ? dev->io_sqes : NVME_ADM_SQES;
	nvmeq->q_depth = depth;
	nvmeq->cqes = dma_alloc_coherent(dev->dev, CQ_SIZE(nvmeq),
					 &nvmeq->cq_dma_addr, GFP_KERNEL);
	अगर (!nvmeq->cqes)
		जाओ मुक्त_nvmeq;

	अगर (nvme_alloc_sq_cmds(dev, nvmeq, qid))
		जाओ मुक्त_cqdma;

	nvmeq->dev = dev;
	spin_lock_init(&nvmeq->sq_lock);
	spin_lock_init(&nvmeq->cq_poll_lock);
	nvmeq->cq_head = 0;
	nvmeq->cq_phase = 1;
	nvmeq->q_db = &dev->dbs[qid * 2 * dev->db_stride];
	nvmeq->qid = qid;
	dev->ctrl.queue_count++;

	वापस 0;

 मुक्त_cqdma:
	dma_मुक्त_coherent(dev->dev, CQ_SIZE(nvmeq), (व्योम *)nvmeq->cqes,
			  nvmeq->cq_dma_addr);
 मुक्त_nvmeq:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक queue_request_irq(काष्ठा nvme_queue *nvmeq)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(nvmeq->dev->dev);
	पूर्णांक nr = nvmeq->dev->ctrl.instance;

	अगर (use_thपढ़ोed_पूर्णांकerrupts) अणु
		वापस pci_request_irq(pdev, nvmeq->cq_vector, nvme_irq_check,
				nvme_irq, nvmeq, "nvme%dq%d", nr, nvmeq->qid);
	पूर्ण अन्यथा अणु
		वापस pci_request_irq(pdev, nvmeq->cq_vector, nvme_irq,
				शून्य, nvmeq, "nvme%dq%d", nr, nvmeq->qid);
	पूर्ण
पूर्ण

अटल व्योम nvme_init_queue(काष्ठा nvme_queue *nvmeq, u16 qid)
अणु
	काष्ठा nvme_dev *dev = nvmeq->dev;

	nvmeq->sq_tail = 0;
	nvmeq->last_sq_tail = 0;
	nvmeq->cq_head = 0;
	nvmeq->cq_phase = 1;
	nvmeq->q_db = &dev->dbs[qid * 2 * dev->db_stride];
	स_रखो((व्योम *)nvmeq->cqes, 0, CQ_SIZE(nvmeq));
	nvme_dbbuf_init(dev, nvmeq, qid);
	dev->online_queues++;
	wmb(); /* ensure the first पूर्णांकerrupt sees the initialization */
पूर्ण

अटल पूर्णांक nvme_create_queue(काष्ठा nvme_queue *nvmeq, पूर्णांक qid, bool polled)
अणु
	काष्ठा nvme_dev *dev = nvmeq->dev;
	पूर्णांक result;
	u16 vector = 0;

	clear_bit(NVMEQ_DELETE_ERROR, &nvmeq->flags);

	/*
	 * A queue's vector matches the queue identअगरier unless the controller
	 * has only one vector available.
	 */
	अगर (!polled)
		vector = dev->num_vecs == 1 ? 0 : qid;
	अन्यथा
		set_bit(NVMEQ_POLLED, &nvmeq->flags);

	result = adapter_alloc_cq(dev, qid, nvmeq, vector);
	अगर (result)
		वापस result;

	result = adapter_alloc_sq(dev, qid, nvmeq);
	अगर (result < 0)
		वापस result;
	अगर (result)
		जाओ release_cq;

	nvmeq->cq_vector = vector;
	nvme_init_queue(nvmeq, qid);

	अगर (!polled) अणु
		result = queue_request_irq(nvmeq);
		अगर (result < 0)
			जाओ release_sq;
	पूर्ण

	set_bit(NVMEQ_ENABLED, &nvmeq->flags);
	वापस result;

release_sq:
	dev->online_queues--;
	adapter_delete_sq(dev, qid);
release_cq:
	adapter_delete_cq(dev, qid);
	वापस result;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops nvme_mq_admin_ops = अणु
	.queue_rq	= nvme_queue_rq,
	.complete	= nvme_pci_complete_rq,
	.init_hctx	= nvme_admin_init_hctx,
	.init_request	= nvme_init_request,
	.समयout	= nvme_समयout,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_ops nvme_mq_ops = अणु
	.queue_rq	= nvme_queue_rq,
	.complete	= nvme_pci_complete_rq,
	.commit_rqs	= nvme_commit_rqs,
	.init_hctx	= nvme_init_hctx,
	.init_request	= nvme_init_request,
	.map_queues	= nvme_pci_map_queues,
	.समयout	= nvme_समयout,
	.poll		= nvme_poll,
पूर्ण;

अटल व्योम nvme_dev_हटाओ_admin(काष्ठा nvme_dev *dev)
अणु
	अगर (dev->ctrl.admin_q && !blk_queue_dying(dev->ctrl.admin_q)) अणु
		/*
		 * If the controller was reset during removal, it's possible
		 * user requests may be रुकोing on a stopped queue. Start the
		 * queue to flush these to completion.
		 */
		blk_mq_unquiesce_queue(dev->ctrl.admin_q);
		blk_cleanup_queue(dev->ctrl.admin_q);
		blk_mq_मुक्त_tag_set(&dev->admin_tagset);
	पूर्ण
पूर्ण

अटल पूर्णांक nvme_alloc_admin_tags(काष्ठा nvme_dev *dev)
अणु
	अगर (!dev->ctrl.admin_q) अणु
		dev->admin_tagset.ops = &nvme_mq_admin_ops;
		dev->admin_tagset.nr_hw_queues = 1;

		dev->admin_tagset.queue_depth = NVME_AQ_MQ_TAG_DEPTH;
		dev->admin_tagset.समयout = NVME_ADMIN_TIMEOUT;
		dev->admin_tagset.numa_node = dev->ctrl.numa_node;
		dev->admin_tagset.cmd_size = माप(काष्ठा nvme_iod);
		dev->admin_tagset.flags = BLK_MQ_F_NO_SCHED;
		dev->admin_tagset.driver_data = dev;

		अगर (blk_mq_alloc_tag_set(&dev->admin_tagset))
			वापस -ENOMEM;
		dev->ctrl.admin_tagset = &dev->admin_tagset;

		dev->ctrl.admin_q = blk_mq_init_queue(&dev->admin_tagset);
		अगर (IS_ERR(dev->ctrl.admin_q)) अणु
			blk_mq_मुक्त_tag_set(&dev->admin_tagset);
			वापस -ENOMEM;
		पूर्ण
		अगर (!blk_get_queue(dev->ctrl.admin_q)) अणु
			nvme_dev_हटाओ_admin(dev);
			dev->ctrl.admin_q = शून्य;
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा
		blk_mq_unquiesce_queue(dev->ctrl.admin_q);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ db_bar_size(काष्ठा nvme_dev *dev, अचिन्हित nr_io_queues)
अणु
	वापस NVME_REG_DBS + ((nr_io_queues + 1) * 8 * dev->db_stride);
पूर्ण

अटल पूर्णांक nvme_remap_bar(काष्ठा nvme_dev *dev, अचिन्हित दीर्घ size)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	अगर (size <= dev->bar_mapped_size)
		वापस 0;
	अगर (size > pci_resource_len(pdev, 0))
		वापस -ENOMEM;
	अगर (dev->bar)
		iounmap(dev->bar);
	dev->bar = ioremap(pci_resource_start(pdev, 0), size);
	अगर (!dev->bar) अणु
		dev->bar_mapped_size = 0;
		वापस -ENOMEM;
	पूर्ण
	dev->bar_mapped_size = size;
	dev->dbs = dev->bar + NVME_REG_DBS;

	वापस 0;
पूर्ण

अटल पूर्णांक nvme_pci_configure_admin_queue(काष्ठा nvme_dev *dev)
अणु
	पूर्णांक result;
	u32 aqa;
	काष्ठा nvme_queue *nvmeq;

	result = nvme_remap_bar(dev, db_bar_size(dev, 0));
	अगर (result < 0)
		वापस result;

	dev->subप्रणाली = पढ़ोl(dev->bar + NVME_REG_VS) >= NVME_VS(1, 1, 0) ?
				NVME_CAP_NSSRC(dev->ctrl.cap) : 0;

	अगर (dev->subप्रणाली &&
	    (पढ़ोl(dev->bar + NVME_REG_CSTS) & NVME_CSTS_NSSRO))
		ग_लिखोl(NVME_CSTS_NSSRO, dev->bar + NVME_REG_CSTS);

	result = nvme_disable_ctrl(&dev->ctrl);
	अगर (result < 0)
		वापस result;

	result = nvme_alloc_queue(dev, 0, NVME_AQ_DEPTH);
	अगर (result)
		वापस result;

	dev->ctrl.numa_node = dev_to_node(dev->dev);

	nvmeq = &dev->queues[0];
	aqa = nvmeq->q_depth - 1;
	aqa |= aqa << 16;

	ग_लिखोl(aqa, dev->bar + NVME_REG_AQA);
	lo_hi_ग_लिखोq(nvmeq->sq_dma_addr, dev->bar + NVME_REG_ASQ);
	lo_hi_ग_लिखोq(nvmeq->cq_dma_addr, dev->bar + NVME_REG_ACQ);

	result = nvme_enable_ctrl(&dev->ctrl);
	अगर (result)
		वापस result;

	nvmeq->cq_vector = 0;
	nvme_init_queue(nvmeq, 0);
	result = queue_request_irq(nvmeq);
	अगर (result) अणु
		dev->online_queues--;
		वापस result;
	पूर्ण

	set_bit(NVMEQ_ENABLED, &nvmeq->flags);
	वापस result;
पूर्ण

अटल पूर्णांक nvme_create_io_queues(काष्ठा nvme_dev *dev)
अणु
	अचिन्हित i, max, rw_queues;
	पूर्णांक ret = 0;

	क्रम (i = dev->ctrl.queue_count; i <= dev->max_qid; i++) अणु
		अगर (nvme_alloc_queue(dev, i, dev->q_depth)) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
	पूर्ण

	max = min(dev->max_qid, dev->ctrl.queue_count - 1);
	अगर (max != 1 && dev->io_queues[HCTX_TYPE_POLL]) अणु
		rw_queues = dev->io_queues[HCTX_TYPE_DEFAULT] +
				dev->io_queues[HCTX_TYPE_READ];
	पूर्ण अन्यथा अणु
		rw_queues = max;
	पूर्ण

	क्रम (i = dev->online_queues; i <= max; i++) अणु
		bool polled = i > rw_queues;

		ret = nvme_create_queue(&dev->queues[i], i, polled);
		अगर (ret)
			अवरोध;
	पूर्ण

	/*
	 * Ignore failing Create SQ/CQ commands, we can जारी with less
	 * than the desired amount of queues, and even a controller without
	 * I/O queues can still be used to issue admin commands.  This might
	 * be useful to upgrade a buggy firmware क्रम example.
	 */
	वापस ret >= 0 ? 0 : ret;
पूर्ण

अटल sमाप_प्रकार nvme_cmb_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा nvme_dev *ndev = to_nvme_dev(dev_get_drvdata(dev));

	वापस scnम_लिखो(buf, PAGE_SIZE, "cmbloc : x%08x\ncmbsz  : x%08x\n",
		       ndev->cmbloc, ndev->cmbsz);
पूर्ण
अटल DEVICE_ATTR(cmb, S_IRUGO, nvme_cmb_show, शून्य);

अटल u64 nvme_cmb_size_unit(काष्ठा nvme_dev *dev)
अणु
	u8 szu = (dev->cmbsz >> NVME_CMBSZ_SZU_SHIFT) & NVME_CMBSZ_SZU_MASK;

	वापस 1ULL << (12 + 4 * szu);
पूर्ण

अटल u32 nvme_cmb_size(काष्ठा nvme_dev *dev)
अणु
	वापस (dev->cmbsz >> NVME_CMBSZ_SZ_SHIFT) & NVME_CMBSZ_SZ_MASK;
पूर्ण

अटल व्योम nvme_map_cmb(काष्ठा nvme_dev *dev)
अणु
	u64 size, offset;
	resource_माप_प्रकार bar_size;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	पूर्णांक bar;

	अगर (dev->cmb_size)
		वापस;

	अगर (NVME_CAP_CMBS(dev->ctrl.cap))
		ग_लिखोl(NVME_CMBMSC_CRE, dev->bar + NVME_REG_CMBMSC);

	dev->cmbsz = पढ़ोl(dev->bar + NVME_REG_CMBSZ);
	अगर (!dev->cmbsz)
		वापस;
	dev->cmbloc = पढ़ोl(dev->bar + NVME_REG_CMBLOC);

	size = nvme_cmb_size_unit(dev) * nvme_cmb_size(dev);
	offset = nvme_cmb_size_unit(dev) * NVME_CMB_OFST(dev->cmbloc);
	bar = NVME_CMB_BIR(dev->cmbloc);
	bar_size = pci_resource_len(pdev, bar);

	अगर (offset > bar_size)
		वापस;

	/*
	 * Tell the controller about the host side address mapping the CMB,
	 * and enable CMB decoding क्रम the NVMe 1.4+ scheme:
	 */
	अगर (NVME_CAP_CMBS(dev->ctrl.cap)) अणु
		hi_lo_ग_लिखोq(NVME_CMBMSC_CRE | NVME_CMBMSC_CMSE |
			     (pci_bus_address(pdev, bar) + offset),
			     dev->bar + NVME_REG_CMBMSC);
	पूर्ण

	/*
	 * Controllers may support a CMB size larger than their BAR,
	 * क्रम example, due to being behind a bridge. Reduce the CMB to
	 * the reported size of the BAR
	 */
	अगर (size > bar_size - offset)
		size = bar_size - offset;

	अगर (pci_p2pdma_add_resource(pdev, bar, size, offset)) अणु
		dev_warn(dev->ctrl.device,
			 "failed to register the CMB\n");
		वापस;
	पूर्ण

	dev->cmb_size = size;
	dev->cmb_use_sqes = use_cmb_sqes && (dev->cmbsz & NVME_CMBSZ_SQS);

	अगर ((dev->cmbsz & (NVME_CMBSZ_WDS | NVME_CMBSZ_RDS)) ==
			(NVME_CMBSZ_WDS | NVME_CMBSZ_RDS))
		pci_p2pmem_publish(pdev, true);

	अगर (sysfs_add_file_to_group(&dev->ctrl.device->kobj,
				    &dev_attr_cmb.attr, शून्य))
		dev_warn(dev->ctrl.device,
			 "failed to add sysfs attribute for CMB\n");
पूर्ण

अटल अंतरभूत व्योम nvme_release_cmb(काष्ठा nvme_dev *dev)
अणु
	अगर (dev->cmb_size) अणु
		sysfs_हटाओ_file_from_group(&dev->ctrl.device->kobj,
					     &dev_attr_cmb.attr, शून्य);
		dev->cmb_size = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक nvme_set_host_mem(काष्ठा nvme_dev *dev, u32 bits)
अणु
	u32 host_mem_size = dev->host_mem_size >> NVME_CTRL_PAGE_SHIFT;
	u64 dma_addr = dev->host_mem_descs_dma;
	काष्ठा nvme_command c;
	पूर्णांक ret;

	स_रखो(&c, 0, माप(c));
	c.features.opcode	= nvme_admin_set_features;
	c.features.fid		= cpu_to_le32(NVME_FEAT_HOST_MEM_BUF);
	c.features.dword11	= cpu_to_le32(bits);
	c.features.dword12	= cpu_to_le32(host_mem_size);
	c.features.dword13	= cpu_to_le32(lower_32_bits(dma_addr));
	c.features.dword14	= cpu_to_le32(upper_32_bits(dma_addr));
	c.features.dword15	= cpu_to_le32(dev->nr_host_mem_descs);

	ret = nvme_submit_sync_cmd(dev->ctrl.admin_q, &c, शून्य, 0);
	अगर (ret) अणु
		dev_warn(dev->ctrl.device,
			 "failed to set host mem (err %d, flags %#x).\n",
			 ret, bits);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम nvme_मुक्त_host_mem(काष्ठा nvme_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev->nr_host_mem_descs; i++) अणु
		काष्ठा nvme_host_mem_buf_desc *desc = &dev->host_mem_descs[i];
		माप_प्रकार size = le32_to_cpu(desc->size) * NVME_CTRL_PAGE_SIZE;

		dma_मुक्त_attrs(dev->dev, size, dev->host_mem_desc_bufs[i],
			       le64_to_cpu(desc->addr),
			       DMA_ATTR_NO_KERNEL_MAPPING | DMA_ATTR_NO_WARN);
	पूर्ण

	kमुक्त(dev->host_mem_desc_bufs);
	dev->host_mem_desc_bufs = शून्य;
	dma_मुक्त_coherent(dev->dev,
			dev->nr_host_mem_descs * माप(*dev->host_mem_descs),
			dev->host_mem_descs, dev->host_mem_descs_dma);
	dev->host_mem_descs = शून्य;
	dev->nr_host_mem_descs = 0;
पूर्ण

अटल पूर्णांक __nvme_alloc_host_mem(काष्ठा nvme_dev *dev, u64 preferred,
		u32 chunk_size)
अणु
	काष्ठा nvme_host_mem_buf_desc *descs;
	u32 max_entries, len;
	dma_addr_t descs_dma;
	पूर्णांक i = 0;
	व्योम **bufs;
	u64 size, पंचांगp;

	पंचांगp = (preferred + chunk_size - 1);
	करो_भाग(पंचांगp, chunk_size);
	max_entries = पंचांगp;

	अगर (dev->ctrl.hmmaxd && dev->ctrl.hmmaxd < max_entries)
		max_entries = dev->ctrl.hmmaxd;

	descs = dma_alloc_coherent(dev->dev, max_entries * माप(*descs),
				   &descs_dma, GFP_KERNEL);
	अगर (!descs)
		जाओ out;

	bufs = kसुस्मृति(max_entries, माप(*bufs), GFP_KERNEL);
	अगर (!bufs)
		जाओ out_मुक्त_descs;

	क्रम (size = 0; size < preferred && i < max_entries; size += len) अणु
		dma_addr_t dma_addr;

		len = min_t(u64, chunk_size, preferred - size);
		bufs[i] = dma_alloc_attrs(dev->dev, len, &dma_addr, GFP_KERNEL,
				DMA_ATTR_NO_KERNEL_MAPPING | DMA_ATTR_NO_WARN);
		अगर (!bufs[i])
			अवरोध;

		descs[i].addr = cpu_to_le64(dma_addr);
		descs[i].size = cpu_to_le32(len / NVME_CTRL_PAGE_SIZE);
		i++;
	पूर्ण

	अगर (!size)
		जाओ out_मुक्त_bufs;

	dev->nr_host_mem_descs = i;
	dev->host_mem_size = size;
	dev->host_mem_descs = descs;
	dev->host_mem_descs_dma = descs_dma;
	dev->host_mem_desc_bufs = bufs;
	वापस 0;

out_मुक्त_bufs:
	जबतक (--i >= 0) अणु
		माप_प्रकार size = le32_to_cpu(descs[i].size) * NVME_CTRL_PAGE_SIZE;

		dma_मुक्त_attrs(dev->dev, size, bufs[i],
			       le64_to_cpu(descs[i].addr),
			       DMA_ATTR_NO_KERNEL_MAPPING | DMA_ATTR_NO_WARN);
	पूर्ण

	kमुक्त(bufs);
out_मुक्त_descs:
	dma_मुक्त_coherent(dev->dev, max_entries * माप(*descs), descs,
			descs_dma);
out:
	dev->host_mem_descs = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक nvme_alloc_host_mem(काष्ठा nvme_dev *dev, u64 min, u64 preferred)
अणु
	u64 min_chunk = min_t(u64, preferred, PAGE_SIZE * MAX_ORDER_NR_PAGES);
	u64 hmminds = max_t(u32, dev->ctrl.hmminds * 4096, PAGE_SIZE * 2);
	u64 chunk_size;

	/* start big and work our way करोwn */
	क्रम (chunk_size = min_chunk; chunk_size >= hmminds; chunk_size /= 2) अणु
		अगर (!__nvme_alloc_host_mem(dev, preferred, chunk_size)) अणु
			अगर (!min || dev->host_mem_size >= min)
				वापस 0;
			nvme_मुक्त_host_mem(dev);
		पूर्ण
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक nvme_setup_host_mem(काष्ठा nvme_dev *dev)
अणु
	u64 max = (u64)max_host_mem_size_mb * SZ_1M;
	u64 preferred = (u64)dev->ctrl.hmpre * 4096;
	u64 min = (u64)dev->ctrl.hmmin * 4096;
	u32 enable_bits = NVME_HOST_MEM_ENABLE;
	पूर्णांक ret;

	preferred = min(preferred, max);
	अगर (min > max) अणु
		dev_warn(dev->ctrl.device,
			"min host memory (%lld MiB) above limit (%d MiB).\n",
			min >> ilog2(SZ_1M), max_host_mem_size_mb);
		nvme_मुक्त_host_mem(dev);
		वापस 0;
	पूर्ण

	/*
	 * If we alपढ़ोy have a buffer allocated check अगर we can reuse it.
	 */
	अगर (dev->host_mem_descs) अणु
		अगर (dev->host_mem_size >= min)
			enable_bits |= NVME_HOST_MEM_RETURN;
		अन्यथा
			nvme_मुक्त_host_mem(dev);
	पूर्ण

	अगर (!dev->host_mem_descs) अणु
		अगर (nvme_alloc_host_mem(dev, min, preferred)) अणु
			dev_warn(dev->ctrl.device,
				"failed to allocate host memory buffer.\n");
			वापस 0; /* controller must work without HMB */
		पूर्ण

		dev_info(dev->ctrl.device,
			"allocated %lld MiB host memory buffer.\n",
			dev->host_mem_size >> ilog2(SZ_1M));
	पूर्ण

	ret = nvme_set_host_mem(dev, enable_bits);
	अगर (ret)
		nvme_मुक्त_host_mem(dev);
	वापस ret;
पूर्ण

/*
 * nirqs is the number of पूर्णांकerrupts available क्रम ग_लिखो and पढ़ो
 * queues. The core alपढ़ोy reserved an पूर्णांकerrupt क्रम the admin queue.
 */
अटल व्योम nvme_calc_irq_sets(काष्ठा irq_affinity *affd, अचिन्हित पूर्णांक nrirqs)
अणु
	काष्ठा nvme_dev *dev = affd->priv;
	अचिन्हित पूर्णांक nr_पढ़ो_queues, nr_ग_लिखो_queues = dev->nr_ग_लिखो_queues;

	/*
	 * If there is no पूर्णांकerrupt available क्रम queues, ensure that
	 * the शेष queue is set to 1. The affinity set size is
	 * also set to one, but the irq core ignores it क्रम this हाल.
	 *
	 * If only one पूर्णांकerrupt is available or 'write_queue' == 0, combine
	 * ग_लिखो and पढ़ो queues.
	 *
	 * If 'write_queues' > 0, ensure it leaves room क्रम at least one पढ़ो
	 * queue.
	 */
	अगर (!nrirqs) अणु
		nrirqs = 1;
		nr_पढ़ो_queues = 0;
	पूर्ण अन्यथा अगर (nrirqs == 1 || !nr_ग_लिखो_queues) अणु
		nr_पढ़ो_queues = 0;
	पूर्ण अन्यथा अगर (nr_ग_लिखो_queues >= nrirqs) अणु
		nr_पढ़ो_queues = 1;
	पूर्ण अन्यथा अणु
		nr_पढ़ो_queues = nrirqs - nr_ग_लिखो_queues;
	पूर्ण

	dev->io_queues[HCTX_TYPE_DEFAULT] = nrirqs - nr_पढ़ो_queues;
	affd->set_size[HCTX_TYPE_DEFAULT] = nrirqs - nr_पढ़ो_queues;
	dev->io_queues[HCTX_TYPE_READ] = nr_पढ़ो_queues;
	affd->set_size[HCTX_TYPE_READ] = nr_पढ़ो_queues;
	affd->nr_sets = nr_पढ़ो_queues ? 2 : 1;
पूर्ण

अटल पूर्णांक nvme_setup_irqs(काष्ठा nvme_dev *dev, अचिन्हित पूर्णांक nr_io_queues)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा irq_affinity affd = अणु
		.pre_vectors	= 1,
		.calc_sets	= nvme_calc_irq_sets,
		.priv		= dev,
	पूर्ण;
	अचिन्हित पूर्णांक irq_queues, poll_queues;

	/*
	 * Poll queues करोn't need पूर्णांकerrupts, but we need at least one I/O queue
	 * left over क्रम non-polled I/O.
	 */
	poll_queues = min(dev->nr_poll_queues, nr_io_queues - 1);
	dev->io_queues[HCTX_TYPE_POLL] = poll_queues;

	/*
	 * Initialize क्रम the single पूर्णांकerrupt हाल, will be updated in
	 * nvme_calc_irq_sets().
	 */
	dev->io_queues[HCTX_TYPE_DEFAULT] = 1;
	dev->io_queues[HCTX_TYPE_READ] = 0;

	/*
	 * We need पूर्णांकerrupts क्रम the admin queue and each non-polled I/O queue,
	 * but some Apple controllers require all queues to use the first
	 * vector.
	 */
	irq_queues = 1;
	अगर (!(dev->ctrl.quirks & NVME_QUIRK_SINGLE_VECTOR))
		irq_queues += (nr_io_queues - poll_queues);
	वापस pci_alloc_irq_vectors_affinity(pdev, 1, irq_queues,
			      PCI_IRQ_ALL_TYPES | PCI_IRQ_AFFINITY, &affd);
पूर्ण

अटल व्योम nvme_disable_io_queues(काष्ठा nvme_dev *dev)
अणु
	अगर (__nvme_disable_io_queues(dev, nvme_admin_delete_sq))
		__nvme_disable_io_queues(dev, nvme_admin_delete_cq);
पूर्ण

अटल अचिन्हित पूर्णांक nvme_max_io_queues(काष्ठा nvme_dev *dev)
अणु
	/*
	 * If tags are shared with admin queue (Apple bug), then
	 * make sure we only use one IO queue.
	 */
	अगर (dev->ctrl.quirks & NVME_QUIRK_SHARED_TAGS)
		वापस 1;
	वापस num_possible_cpus() + dev->nr_ग_लिखो_queues + dev->nr_poll_queues;
पूर्ण

अटल पूर्णांक nvme_setup_io_queues(काष्ठा nvme_dev *dev)
अणु
	काष्ठा nvme_queue *adminq = &dev->queues[0];
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	अचिन्हित पूर्णांक nr_io_queues;
	अचिन्हित दीर्घ size;
	पूर्णांक result;

	/*
	 * Sample the module parameters once at reset समय so that we have
	 * stable values to work with.
	 */
	dev->nr_ग_लिखो_queues = ग_लिखो_queues;
	dev->nr_poll_queues = poll_queues;

	nr_io_queues = dev->nr_allocated_queues - 1;
	result = nvme_set_queue_count(&dev->ctrl, &nr_io_queues);
	अगर (result < 0)
		वापस result;

	अगर (nr_io_queues == 0)
		वापस 0;

	clear_bit(NVMEQ_ENABLED, &adminq->flags);

	अगर (dev->cmb_use_sqes) अणु
		result = nvme_cmb_qdepth(dev, nr_io_queues,
				माप(काष्ठा nvme_command));
		अगर (result > 0)
			dev->q_depth = result;
		अन्यथा
			dev->cmb_use_sqes = false;
	पूर्ण

	करो अणु
		size = db_bar_size(dev, nr_io_queues);
		result = nvme_remap_bar(dev, size);
		अगर (!result)
			अवरोध;
		अगर (!--nr_io_queues)
			वापस -ENOMEM;
	पूर्ण जबतक (1);
	adminq->q_db = dev->dbs;

 retry:
	/* Deरेजिस्टर the admin queue's पूर्णांकerrupt */
	pci_मुक्त_irq(pdev, 0, adminq);

	/*
	 * If we enable msix early due to not पूर्णांकx, disable it again beक्रमe
	 * setting up the full range we need.
	 */
	pci_मुक्त_irq_vectors(pdev);

	result = nvme_setup_irqs(dev, nr_io_queues);
	अगर (result <= 0)
		वापस -EIO;

	dev->num_vecs = result;
	result = max(result - 1, 1);
	dev->max_qid = result + dev->io_queues[HCTX_TYPE_POLL];

	/*
	 * Should investigate अगर there's a perक्रमmance win from allocating
	 * more queues than पूर्णांकerrupt vectors; it might allow the submission
	 * path to scale better, even अगर the receive path is limited by the
	 * number of पूर्णांकerrupts.
	 */
	result = queue_request_irq(adminq);
	अगर (result)
		वापस result;
	set_bit(NVMEQ_ENABLED, &adminq->flags);

	result = nvme_create_io_queues(dev);
	अगर (result || dev->online_queues < 2)
		वापस result;

	अगर (dev->online_queues - 1 < dev->max_qid) अणु
		nr_io_queues = dev->online_queues - 1;
		nvme_disable_io_queues(dev);
		nvme_suspend_io_queues(dev);
		जाओ retry;
	पूर्ण
	dev_info(dev->ctrl.device, "%d/%d/%d default/read/poll queues\n",
					dev->io_queues[HCTX_TYPE_DEFAULT],
					dev->io_queues[HCTX_TYPE_READ],
					dev->io_queues[HCTX_TYPE_POLL]);
	वापस 0;
पूर्ण

अटल व्योम nvme_del_queue_end(काष्ठा request *req, blk_status_t error)
अणु
	काष्ठा nvme_queue *nvmeq = req->end_io_data;

	blk_mq_मुक्त_request(req);
	complete(&nvmeq->delete_करोne);
पूर्ण

अटल व्योम nvme_del_cq_end(काष्ठा request *req, blk_status_t error)
अणु
	काष्ठा nvme_queue *nvmeq = req->end_io_data;

	अगर (error)
		set_bit(NVMEQ_DELETE_ERROR, &nvmeq->flags);

	nvme_del_queue_end(req, error);
पूर्ण

अटल पूर्णांक nvme_delete_queue(काष्ठा nvme_queue *nvmeq, u8 opcode)
अणु
	काष्ठा request_queue *q = nvmeq->dev->ctrl.admin_q;
	काष्ठा request *req;
	काष्ठा nvme_command cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.delete_queue.opcode = opcode;
	cmd.delete_queue.qid = cpu_to_le16(nvmeq->qid);

	req = nvme_alloc_request(q, &cmd, BLK_MQ_REQ_NOWAIT);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	req->end_io_data = nvmeq;

	init_completion(&nvmeq->delete_करोne);
	blk_execute_rq_noरुको(शून्य, req, false,
			opcode == nvme_admin_delete_cq ?
				nvme_del_cq_end : nvme_del_queue_end);
	वापस 0;
पूर्ण

अटल bool __nvme_disable_io_queues(काष्ठा nvme_dev *dev, u8 opcode)
अणु
	पूर्णांक nr_queues = dev->online_queues - 1, sent = 0;
	अचिन्हित दीर्घ समयout;

 retry:
	समयout = NVME_ADMIN_TIMEOUT;
	जबतक (nr_queues > 0) अणु
		अगर (nvme_delete_queue(&dev->queues[nr_queues], opcode))
			अवरोध;
		nr_queues--;
		sent++;
	पूर्ण
	जबतक (sent) अणु
		काष्ठा nvme_queue *nvmeq = &dev->queues[nr_queues + sent];

		समयout = रुको_क्रम_completion_io_समयout(&nvmeq->delete_करोne,
				समयout);
		अगर (समयout == 0)
			वापस false;

		sent--;
		अगर (nr_queues)
			जाओ retry;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम nvme_dev_add(काष्ठा nvme_dev *dev)
अणु
	पूर्णांक ret;

	अगर (!dev->ctrl.tagset) अणु
		dev->tagset.ops = &nvme_mq_ops;
		dev->tagset.nr_hw_queues = dev->online_queues - 1;
		dev->tagset.nr_maps = 2; /* शेष + पढ़ो */
		अगर (dev->io_queues[HCTX_TYPE_POLL])
			dev->tagset.nr_maps++;
		dev->tagset.समयout = NVME_IO_TIMEOUT;
		dev->tagset.numa_node = dev->ctrl.numa_node;
		dev->tagset.queue_depth = min_t(अचिन्हित पूर्णांक, dev->q_depth,
						BLK_MQ_MAX_DEPTH) - 1;
		dev->tagset.cmd_size = माप(काष्ठा nvme_iod);
		dev->tagset.flags = BLK_MQ_F_SHOULD_MERGE;
		dev->tagset.driver_data = dev;

		/*
		 * Some Apple controllers requires tags to be unique
		 * across admin and IO queue, so reserve the first 32
		 * tags of the IO queue.
		 */
		अगर (dev->ctrl.quirks & NVME_QUIRK_SHARED_TAGS)
			dev->tagset.reserved_tags = NVME_AQ_DEPTH;

		ret = blk_mq_alloc_tag_set(&dev->tagset);
		अगर (ret) अणु
			dev_warn(dev->ctrl.device,
				"IO queues tagset allocation failed %d\n", ret);
			वापस;
		पूर्ण
		dev->ctrl.tagset = &dev->tagset;
	पूर्ण अन्यथा अणु
		blk_mq_update_nr_hw_queues(&dev->tagset, dev->online_queues - 1);

		/* Free previously allocated queues that are no दीर्घer usable */
		nvme_मुक्त_queues(dev, dev->online_queues);
	पूर्ण

	nvme_dbbuf_set(dev);
पूर्ण

अटल पूर्णांक nvme_pci_enable(काष्ठा nvme_dev *dev)
अणु
	पूर्णांक result = -ENOMEM;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	पूर्णांक dma_address_bits = 64;

	अगर (pci_enable_device_mem(pdev))
		वापस result;

	pci_set_master(pdev);

	अगर (dev->ctrl.quirks & NVME_QUIRK_DMA_ADDRESS_BITS_48)
		dma_address_bits = 48;
	अगर (dma_set_mask_and_coherent(dev->dev, DMA_BIT_MASK(dma_address_bits)))
		जाओ disable;

	अगर (पढ़ोl(dev->bar + NVME_REG_CSTS) == -1) अणु
		result = -ENODEV;
		जाओ disable;
	पूर्ण

	/*
	 * Some devices and/or platक्रमms करोn't advertise or work with INTx
	 * पूर्णांकerrupts. Pre-enable a single MSIX or MSI vec क्रम setup. We'll
	 * adjust this later.
	 */
	result = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (result < 0)
		वापस result;

	dev->ctrl.cap = lo_hi_पढ़ोq(dev->bar + NVME_REG_CAP);

	dev->q_depth = min_t(u32, NVME_CAP_MQES(dev->ctrl.cap) + 1,
				io_queue_depth);
	dev->ctrl.sqsize = dev->q_depth - 1; /* 0's based queue depth */
	dev->db_stride = 1 << NVME_CAP_STRIDE(dev->ctrl.cap);
	dev->dbs = dev->bar + 4096;

	/*
	 * Some Apple controllers require a non-standard SQE size.
	 * Interestingly they also seem to ignore the CC:IOSQES रेजिस्टर
	 * so we करोn't bother updating it here.
	 */
	अगर (dev->ctrl.quirks & NVME_QUIRK_128_BYTES_SQES)
		dev->io_sqes = 7;
	अन्यथा
		dev->io_sqes = NVME_NVM_IOSQES;

	/*
	 * Temporary fix क्रम the Apple controller found in the MacBook8,1 and
	 * some MacBook7,1 to aव्योम controller resets and data loss.
	 */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_APPLE && pdev->device == 0x2001) अणु
		dev->q_depth = 2;
		dev_warn(dev->ctrl.device, "detected Apple NVMe controller, "
			"set queue depth=%u to work around controller resets\n",
			dev->q_depth);
	पूर्ण अन्यथा अगर (pdev->venकरोr == PCI_VENDOR_ID_SAMSUNG &&
		   (pdev->device == 0xa821 || pdev->device == 0xa822) &&
		   NVME_CAP_MQES(dev->ctrl.cap) == 0) अणु
		dev->q_depth = 64;
		dev_err(dev->ctrl.device, "detected PM1725 NVMe controller, "
                        "set queue depth=%u\n", dev->q_depth);
	पूर्ण

	/*
	 * Controllers with the shared tags quirk need the IO queue to be
	 * big enough so that we get 32 tags क्रम the admin queue
	 */
	अगर ((dev->ctrl.quirks & NVME_QUIRK_SHARED_TAGS) &&
	    (dev->q_depth < (NVME_AQ_DEPTH + 2))) अणु
		dev->q_depth = NVME_AQ_DEPTH + 2;
		dev_warn(dev->ctrl.device, "IO queue depth clamped to %d\n",
			 dev->q_depth);
	पूर्ण


	nvme_map_cmb(dev);

	pci_enable_pcie_error_reporting(pdev);
	pci_save_state(pdev);
	वापस 0;

 disable:
	pci_disable_device(pdev);
	वापस result;
पूर्ण

अटल व्योम nvme_dev_unmap(काष्ठा nvme_dev *dev)
अणु
	अगर (dev->bar)
		iounmap(dev->bar);
	pci_release_mem_regions(to_pci_dev(dev->dev));
पूर्ण

अटल व्योम nvme_pci_disable(काष्ठा nvme_dev *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	pci_मुक्त_irq_vectors(pdev);

	अगर (pci_is_enabled(pdev)) अणु
		pci_disable_pcie_error_reporting(pdev);
		pci_disable_device(pdev);
	पूर्ण
पूर्ण

अटल व्योम nvme_dev_disable(काष्ठा nvme_dev *dev, bool shutकरोwn)
अणु
	bool dead = true, मुक्तze = false;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	mutex_lock(&dev->shutकरोwn_lock);
	अगर (pci_is_enabled(pdev)) अणु
		u32 csts = पढ़ोl(dev->bar + NVME_REG_CSTS);

		अगर (dev->ctrl.state == NVME_CTRL_LIVE ||
		    dev->ctrl.state == NVME_CTRL_RESETTING) अणु
			मुक्तze = true;
			nvme_start_मुक्तze(&dev->ctrl);
		पूर्ण
		dead = !!((csts & NVME_CSTS_CFS) || !(csts & NVME_CSTS_RDY) ||
			pdev->error_state  != pci_channel_io_normal);
	पूर्ण

	/*
	 * Give the controller a chance to complete all entered requests अगर
	 * करोing a safe shutकरोwn.
	 */
	अगर (!dead && shutकरोwn && मुक्तze)
		nvme_रुको_मुक्तze_समयout(&dev->ctrl, NVME_IO_TIMEOUT);

	nvme_stop_queues(&dev->ctrl);

	अगर (!dead && dev->ctrl.queue_count > 0) अणु
		nvme_disable_io_queues(dev);
		nvme_disable_admin_queue(dev, shutकरोwn);
	पूर्ण
	nvme_suspend_io_queues(dev);
	nvme_suspend_queue(&dev->queues[0]);
	nvme_pci_disable(dev);
	nvme_reap_pending_cqes(dev);

	blk_mq_tagset_busy_iter(&dev->tagset, nvme_cancel_request, &dev->ctrl);
	blk_mq_tagset_busy_iter(&dev->admin_tagset, nvme_cancel_request, &dev->ctrl);
	blk_mq_tagset_रुको_completed_request(&dev->tagset);
	blk_mq_tagset_रुको_completed_request(&dev->admin_tagset);

	/*
	 * The driver will not be starting up queues again अगर shutting करोwn so
	 * must flush all entered requests to their failed completion to aव्योम
	 * deadlocking blk-mq hot-cpu notअगरier.
	 */
	अगर (shutकरोwn) अणु
		nvme_start_queues(&dev->ctrl);
		अगर (dev->ctrl.admin_q && !blk_queue_dying(dev->ctrl.admin_q))
			blk_mq_unquiesce_queue(dev->ctrl.admin_q);
	पूर्ण
	mutex_unlock(&dev->shutकरोwn_lock);
पूर्ण

अटल पूर्णांक nvme_disable_prepare_reset(काष्ठा nvme_dev *dev, bool shutकरोwn)
अणु
	अगर (!nvme_रुको_reset(&dev->ctrl))
		वापस -EBUSY;
	nvme_dev_disable(dev, shutकरोwn);
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_setup_prp_pools(काष्ठा nvme_dev *dev)
अणु
	dev->prp_page_pool = dma_pool_create("prp list page", dev->dev,
						NVME_CTRL_PAGE_SIZE,
						NVME_CTRL_PAGE_SIZE, 0);
	अगर (!dev->prp_page_pool)
		वापस -ENOMEM;

	/* Optimisation क्रम I/Os between 4k and 128k */
	dev->prp_small_pool = dma_pool_create("prp list 256", dev->dev,
						256, 256, 0);
	अगर (!dev->prp_small_pool) अणु
		dma_pool_destroy(dev->prp_page_pool);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nvme_release_prp_pools(काष्ठा nvme_dev *dev)
अणु
	dma_pool_destroy(dev->prp_page_pool);
	dma_pool_destroy(dev->prp_small_pool);
पूर्ण

अटल व्योम nvme_मुक्त_tagset(काष्ठा nvme_dev *dev)
अणु
	अगर (dev->tagset.tags)
		blk_mq_मुक्त_tag_set(&dev->tagset);
	dev->ctrl.tagset = शून्य;
पूर्ण

अटल व्योम nvme_pci_मुक्त_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_dev *dev = to_nvme_dev(ctrl);

	nvme_dbbuf_dma_मुक्त(dev);
	nvme_मुक्त_tagset(dev);
	अगर (dev->ctrl.admin_q)
		blk_put_queue(dev->ctrl.admin_q);
	मुक्त_opal_dev(dev->ctrl.opal_dev);
	mempool_destroy(dev->iod_mempool);
	put_device(dev->dev);
	kमुक्त(dev->queues);
	kमुक्त(dev);
पूर्ण

अटल व्योम nvme_हटाओ_dead_ctrl(काष्ठा nvme_dev *dev)
अणु
	/*
	 * Set state to deleting now to aव्योम blocking nvme_रुको_reset(), which
	 * may be holding this pci_dev's device lock.
	 */
	nvme_change_ctrl_state(&dev->ctrl, NVME_CTRL_DELETING);
	nvme_get_ctrl(&dev->ctrl);
	nvme_dev_disable(dev, false);
	nvme_समाप्त_queues(&dev->ctrl);
	अगर (!queue_work(nvme_wq, &dev->हटाओ_work))
		nvme_put_ctrl(&dev->ctrl);
पूर्ण

अटल व्योम nvme_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_dev *dev =
		container_of(work, काष्ठा nvme_dev, ctrl.reset_work);
	bool was_suspend = !!(dev->ctrl.ctrl_config & NVME_CC_SHN_NORMAL);
	पूर्णांक result;

	अगर (WARN_ON(dev->ctrl.state != NVME_CTRL_RESETTING)) अणु
		result = -ENODEV;
		जाओ out;
	पूर्ण

	/*
	 * If we're called to reset a live controller first shut it करोwn beक्रमe
	 * moving on.
	 */
	अगर (dev->ctrl.ctrl_config & NVME_CC_ENABLE)
		nvme_dev_disable(dev, false);
	nvme_sync_queues(&dev->ctrl);

	mutex_lock(&dev->shutकरोwn_lock);
	result = nvme_pci_enable(dev);
	अगर (result)
		जाओ out_unlock;

	result = nvme_pci_configure_admin_queue(dev);
	अगर (result)
		जाओ out_unlock;

	result = nvme_alloc_admin_tags(dev);
	अगर (result)
		जाओ out_unlock;

	/*
	 * Limit the max command size to prevent iod->sg allocations going
	 * over a single page.
	 */
	dev->ctrl.max_hw_sectors = min_t(u32,
		NVME_MAX_KB_SZ << 1, dma_max_mapping_size(dev->dev) >> 9);
	dev->ctrl.max_segments = NVME_MAX_SEGS;

	/*
	 * Don't limit the IOMMU merged segment size.
	 */
	dma_set_max_seg_size(dev->dev, 0xffffffff);
	dma_set_min_align_mask(dev->dev, NVME_CTRL_PAGE_SIZE - 1);

	mutex_unlock(&dev->shutकरोwn_lock);

	/*
	 * Introduce CONNECTING state from nvme-fc/rdma transports to mark the
	 * initializing procedure here.
	 */
	अगर (!nvme_change_ctrl_state(&dev->ctrl, NVME_CTRL_CONNECTING)) अणु
		dev_warn(dev->ctrl.device,
			"failed to mark controller CONNECTING\n");
		result = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * We करो not support an SGL क्रम metadata (yet), so we are limited to a
	 * single पूर्णांकegrity segment क्रम the separate metadata poपूर्णांकer.
	 */
	dev->ctrl.max_पूर्णांकegrity_segments = 1;

	result = nvme_init_ctrl_finish(&dev->ctrl);
	अगर (result)
		जाओ out;

	अगर (dev->ctrl.oacs & NVME_CTRL_OACS_SEC_SUPP) अणु
		अगर (!dev->ctrl.opal_dev)
			dev->ctrl.opal_dev =
				init_opal_dev(&dev->ctrl, &nvme_sec_submit);
		अन्यथा अगर (was_suspend)
			opal_unlock_from_suspend(dev->ctrl.opal_dev);
	पूर्ण अन्यथा अणु
		मुक्त_opal_dev(dev->ctrl.opal_dev);
		dev->ctrl.opal_dev = शून्य;
	पूर्ण

	अगर (dev->ctrl.oacs & NVME_CTRL_OACS_DBBUF_SUPP) अणु
		result = nvme_dbbuf_dma_alloc(dev);
		अगर (result)
			dev_warn(dev->dev,
				 "unable to allocate dma for dbbuf\n");
	पूर्ण

	अगर (dev->ctrl.hmpre) अणु
		result = nvme_setup_host_mem(dev);
		अगर (result < 0)
			जाओ out;
	पूर्ण

	result = nvme_setup_io_queues(dev);
	अगर (result)
		जाओ out;

	/*
	 * Keep the controller around but हटाओ all namespaces अगर we करोn't have
	 * any working I/O queue.
	 */
	अगर (dev->online_queues < 2) अणु
		dev_warn(dev->ctrl.device, "IO queues not created\n");
		nvme_समाप्त_queues(&dev->ctrl);
		nvme_हटाओ_namespaces(&dev->ctrl);
		nvme_मुक्त_tagset(dev);
	पूर्ण अन्यथा अणु
		nvme_start_queues(&dev->ctrl);
		nvme_रुको_मुक्तze(&dev->ctrl);
		nvme_dev_add(dev);
		nvme_unमुक्तze(&dev->ctrl);
	पूर्ण

	/*
	 * If only admin queue live, keep it to करो further investigation or
	 * recovery.
	 */
	अगर (!nvme_change_ctrl_state(&dev->ctrl, NVME_CTRL_LIVE)) अणु
		dev_warn(dev->ctrl.device,
			"failed to mark controller live state\n");
		result = -ENODEV;
		जाओ out;
	पूर्ण

	nvme_start_ctrl(&dev->ctrl);
	वापस;

 out_unlock:
	mutex_unlock(&dev->shutकरोwn_lock);
 out:
	अगर (result)
		dev_warn(dev->ctrl.device,
			 "Removing after probe failure status: %d\n", result);
	nvme_हटाओ_dead_ctrl(dev);
पूर्ण

अटल व्योम nvme_हटाओ_dead_ctrl_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_dev *dev = container_of(work, काष्ठा nvme_dev, हटाओ_work);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	अगर (pci_get_drvdata(pdev))
		device_release_driver(&pdev->dev);
	nvme_put_ctrl(&dev->ctrl);
पूर्ण

अटल पूर्णांक nvme_pci_reg_पढ़ो32(काष्ठा nvme_ctrl *ctrl, u32 off, u32 *val)
अणु
	*val = पढ़ोl(to_nvme_dev(ctrl)->bar + off);
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_pci_reg_ग_लिखो32(काष्ठा nvme_ctrl *ctrl, u32 off, u32 val)
अणु
	ग_लिखोl(val, to_nvme_dev(ctrl)->bar + off);
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_pci_reg_पढ़ो64(काष्ठा nvme_ctrl *ctrl, u32 off, u64 *val)
अणु
	*val = lo_hi_पढ़ोq(to_nvme_dev(ctrl)->bar + off);
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_pci_get_address(काष्ठा nvme_ctrl *ctrl, अक्षर *buf, पूर्णांक size)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(to_nvme_dev(ctrl)->dev);

	वापस snम_लिखो(buf, size, "%s\n", dev_name(&pdev->dev));
पूर्ण

अटल स्थिर काष्ठा nvme_ctrl_ops nvme_pci_ctrl_ops = अणु
	.name			= "pcie",
	.module			= THIS_MODULE,
	.flags			= NVME_F_METADATA_SUPPORTED |
				  NVME_F_PCI_P2PDMA,
	.reg_पढ़ो32		= nvme_pci_reg_पढ़ो32,
	.reg_ग_लिखो32		= nvme_pci_reg_ग_लिखो32,
	.reg_पढ़ो64		= nvme_pci_reg_पढ़ो64,
	.मुक्त_ctrl		= nvme_pci_मुक्त_ctrl,
	.submit_async_event	= nvme_pci_submit_async_event,
	.get_address		= nvme_pci_get_address,
पूर्ण;

अटल पूर्णांक nvme_dev_map(काष्ठा nvme_dev *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	अगर (pci_request_mem_regions(pdev, "nvme"))
		वापस -ENODEV;

	अगर (nvme_remap_bar(dev, NVME_REG_DBS + 4096))
		जाओ release;

	वापस 0;
  release:
	pci_release_mem_regions(pdev);
	वापस -ENODEV;
पूर्ण

अटल अचिन्हित दीर्घ check_venकरोr_combination_bug(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->venकरोr == 0x144d && pdev->device == 0xa802) अणु
		/*
		 * Several Samsung devices seem to drop off the PCIe bus
		 * अक्रमomly when APST is on and uses the deepest sleep state.
		 * This has been observed on a Samsung "SM951 NVMe SAMSUNG
		 * 256GB", a "PM951 NVMe SAMSUNG 512GB", and a "Samsung SSD
		 * 950 PRO 256GB", but it seems to be restricted to two Dell
		 * laptops.
		 */
		अगर (dmi_match(DMI_SYS_VENDOR, "Dell Inc.") &&
		    (dmi_match(DMI_PRODUCT_NAME, "XPS 15 9550") ||
		     dmi_match(DMI_PRODUCT_NAME, "Precision 5510")))
			वापस NVME_QUIRK_NO_DEEPEST_PS;
	पूर्ण अन्यथा अगर (pdev->venकरोr == 0x144d && pdev->device == 0xa804) अणु
		/*
		 * Samsung SSD 960 EVO drops off the PCIe bus after प्रणाली
		 * suspend on a Ryzen board, ASUS PRIME B350M-A, as well as
		 * within few minutes after bootup on a Coffee Lake board -
		 * ASUS PRIME Z370-A
		 */
		अगर (dmi_match(DMI_BOARD_VENDOR, "ASUSTeK COMPUTER INC.") &&
		    (dmi_match(DMI_BOARD_NAME, "PRIME B350M-A") ||
		     dmi_match(DMI_BOARD_NAME, "PRIME Z370-A")))
			वापस NVME_QUIRK_NO_APST;
	पूर्ण अन्यथा अगर ((pdev->venकरोr == 0x144d && (pdev->device == 0xa801 ||
		    pdev->device == 0xa808 || pdev->device == 0xa809)) ||
		   (pdev->venकरोr == 0x1e0f && pdev->device == 0x0001)) अणु
		/*
		 * Forcing to use host managed nvme घातer settings क्रम
		 * lowest idle घातer with quick resume latency on
		 * Samsung and Toshiba SSDs based on suspend behavior
		 * on Coffee Lake board क्रम LENOVO C640
		 */
		अगर ((dmi_match(DMI_BOARD_VENDOR, "LENOVO")) &&
		     dmi_match(DMI_BOARD_NAME, "LNVNB161216"))
			वापस NVME_QUIRK_SIMPLE_SUSPEND;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल bool nvme_acpi_storage_d3(काष्ठा pci_dev *dev)
अणु
	काष्ठा acpi_device *adev;
	काष्ठा pci_dev *root;
	acpi_handle handle;
	acpi_status status;
	u8 val;

	/*
	 * Look क्रम _DSD property specअगरying that the storage device on the port
	 * must use D3 to support deep platक्रमm घातer savings during
	 * suspend-to-idle.
	 */
	root = pcie_find_root_port(dev);
	अगर (!root)
		वापस false;

	adev = ACPI_COMPANION(&root->dev);
	अगर (!adev)
		वापस false;

	/*
	 * The property is defined in the PXSX device क्रम South complex ports
	 * and in the PEGP device क्रम North complex ports.
	 */
	status = acpi_get_handle(adev->handle, "PXSX", &handle);
	अगर (ACPI_FAILURE(status)) अणु
		status = acpi_get_handle(adev->handle, "PEGP", &handle);
		अगर (ACPI_FAILURE(status))
			वापस false;
	पूर्ण

	अगर (acpi_bus_get_device(handle, &adev))
		वापस false;

	अगर (fwnode_property_पढ़ो_u8(acpi_fwnode_handle(adev), "StorageD3Enable",
			&val))
		वापस false;
	वापस val == 1;
पूर्ण
#अन्यथा
अटल अंतरभूत bool nvme_acpi_storage_d3(काष्ठा pci_dev *dev)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

अटल व्योम nvme_async_probe(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा nvme_dev *dev = data;

	flush_work(&dev->ctrl.reset_work);
	flush_work(&dev->ctrl.scan_work);
	nvme_put_ctrl(&dev->ctrl);
पूर्ण

अटल पूर्णांक nvme_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक node, result = -ENOMEM;
	काष्ठा nvme_dev *dev;
	अचिन्हित दीर्घ quirks = id->driver_data;
	माप_प्रकार alloc_size;

	node = dev_to_node(&pdev->dev);
	अगर (node == NUMA_NO_NODE)
		set_dev_node(&pdev->dev, first_memory_node);

	dev = kzalloc_node(माप(*dev), GFP_KERNEL, node);
	अगर (!dev)
		वापस -ENOMEM;

	dev->nr_ग_लिखो_queues = ग_लिखो_queues;
	dev->nr_poll_queues = poll_queues;
	dev->nr_allocated_queues = nvme_max_io_queues(dev) + 1;
	dev->queues = kसुस्मृति_node(dev->nr_allocated_queues,
			माप(काष्ठा nvme_queue), GFP_KERNEL, node);
	अगर (!dev->queues)
		जाओ मुक्त;

	dev->dev = get_device(&pdev->dev);
	pci_set_drvdata(pdev, dev);

	result = nvme_dev_map(dev);
	अगर (result)
		जाओ put_pci;

	INIT_WORK(&dev->ctrl.reset_work, nvme_reset_work);
	INIT_WORK(&dev->हटाओ_work, nvme_हटाओ_dead_ctrl_work);
	mutex_init(&dev->shutकरोwn_lock);

	result = nvme_setup_prp_pools(dev);
	अगर (result)
		जाओ unmap;

	quirks |= check_venकरोr_combination_bug(pdev);

	अगर (!noacpi && nvme_acpi_storage_d3(pdev)) अणु
		/*
		 * Some प्रणालीs use a bios work around to ask क्रम D3 on
		 * platक्रमms that support kernel managed suspend.
		 */
		dev_info(&pdev->dev,
			 "platform quirk: setting simple suspend\n");
		quirks |= NVME_QUIRK_SIMPLE_SUSPEND;
	पूर्ण

	/*
	 * Double check that our mempool alloc size will cover the biggest
	 * command we support.
	 */
	alloc_size = nvme_pci_iod_alloc_size();
	WARN_ON_ONCE(alloc_size > PAGE_SIZE);

	dev->iod_mempool = mempool_create_node(1, mempool_kदो_स्मृति,
						mempool_kमुक्त,
						(व्योम *) alloc_size,
						GFP_KERNEL, node);
	अगर (!dev->iod_mempool) अणु
		result = -ENOMEM;
		जाओ release_pools;
	पूर्ण

	result = nvme_init_ctrl(&dev->ctrl, &pdev->dev, &nvme_pci_ctrl_ops,
			quirks);
	अगर (result)
		जाओ release_mempool;

	dev_info(dev->ctrl.device, "pci function %s\n", dev_name(&pdev->dev));

	nvme_reset_ctrl(&dev->ctrl);
	async_schedule(nvme_async_probe, dev);

	वापस 0;

 release_mempool:
	mempool_destroy(dev->iod_mempool);
 release_pools:
	nvme_release_prp_pools(dev);
 unmap:
	nvme_dev_unmap(dev);
 put_pci:
	put_device(dev->dev);
 मुक्त:
	kमुक्त(dev->queues);
	kमुक्त(dev);
	वापस result;
पूर्ण

अटल व्योम nvme_reset_prepare(काष्ठा pci_dev *pdev)
अणु
	काष्ठा nvme_dev *dev = pci_get_drvdata(pdev);

	/*
	 * We करोn't need to check the वापस value from रुकोing क्रम the reset
	 * state as pci_dev device lock is held, making it impossible to race
	 * with ->हटाओ().
	 */
	nvme_disable_prepare_reset(dev, false);
	nvme_sync_queues(&dev->ctrl);
पूर्ण

अटल व्योम nvme_reset_करोne(काष्ठा pci_dev *pdev)
अणु
	काष्ठा nvme_dev *dev = pci_get_drvdata(pdev);

	अगर (!nvme_try_sched_reset(&dev->ctrl))
		flush_work(&dev->ctrl.reset_work);
पूर्ण

अटल व्योम nvme_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा nvme_dev *dev = pci_get_drvdata(pdev);

	nvme_disable_prepare_reset(dev, true);
पूर्ण

/*
 * The driver's हटाओ may be called on a device in a partially initialized
 * state. This function must not have any dependencies on the device state in
 * order to proceed.
 */
अटल व्योम nvme_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा nvme_dev *dev = pci_get_drvdata(pdev);

	nvme_change_ctrl_state(&dev->ctrl, NVME_CTRL_DELETING);
	pci_set_drvdata(pdev, शून्य);

	अगर (!pci_device_is_present(pdev)) अणु
		nvme_change_ctrl_state(&dev->ctrl, NVME_CTRL_DEAD);
		nvme_dev_disable(dev, true);
		nvme_dev_हटाओ_admin(dev);
	पूर्ण

	flush_work(&dev->ctrl.reset_work);
	nvme_stop_ctrl(&dev->ctrl);
	nvme_हटाओ_namespaces(&dev->ctrl);
	nvme_dev_disable(dev, true);
	nvme_release_cmb(dev);
	nvme_मुक्त_host_mem(dev);
	nvme_dev_हटाओ_admin(dev);
	nvme_मुक्त_queues(dev, 0);
	nvme_release_prp_pools(dev);
	nvme_dev_unmap(dev);
	nvme_uninit_ctrl(&dev->ctrl);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक nvme_get_घातer_state(काष्ठा nvme_ctrl *ctrl, u32 *ps)
अणु
	वापस nvme_get_features(ctrl, NVME_FEAT_POWER_MGMT, 0, शून्य, 0, ps);
पूर्ण

अटल पूर्णांक nvme_set_घातer_state(काष्ठा nvme_ctrl *ctrl, u32 ps)
अणु
	वापस nvme_set_features(ctrl, NVME_FEAT_POWER_MGMT, ps, शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक nvme_resume(काष्ठा device *dev)
अणु
	काष्ठा nvme_dev *ndev = pci_get_drvdata(to_pci_dev(dev));
	काष्ठा nvme_ctrl *ctrl = &ndev->ctrl;

	अगर (ndev->last_ps == U32_MAX ||
	    nvme_set_घातer_state(ctrl, ndev->last_ps) != 0)
		वापस nvme_try_sched_reset(&ndev->ctrl);
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा nvme_dev *ndev = pci_get_drvdata(pdev);
	काष्ठा nvme_ctrl *ctrl = &ndev->ctrl;
	पूर्णांक ret = -EBUSY;

	ndev->last_ps = U32_MAX;

	/*
	 * The platक्रमm करोes not हटाओ घातer क्रम a kernel managed suspend so
	 * use host managed nvme घातer settings क्रम lowest idle घातer अगर
	 * possible. This should have quicker resume latency than a full device
	 * shutकरोwn.  But अगर the firmware is involved after the suspend or the
	 * device करोes not support any non-शेष घातer states, shut करोwn the
	 * device fully.
	 *
	 * If ASPM is not enabled क्रम the device, shut करोwn the device and allow
	 * the PCI bus layer to put it पूर्णांकo D3 in order to take the PCIe link
	 * करोwn, so as to allow the platक्रमm to achieve its minimum low-घातer
	 * state (which may not be possible अगर the link is up).
	 *
	 * If a host memory buffer is enabled, shut करोwn the device as the NVMe
	 * specअगरication allows the device to access the host memory buffer in
	 * host DRAM from all घातer states, but hosts will fail access to DRAM
	 * during S3.
	 */
	अगर (pm_suspend_via_firmware() || !ctrl->npss ||
	    !pcie_aspm_enabled(pdev) ||
	    ndev->nr_host_mem_descs ||
	    (ndev->ctrl.quirks & NVME_QUIRK_SIMPLE_SUSPEND))
		वापस nvme_disable_prepare_reset(ndev, true);

	nvme_start_मुक्तze(ctrl);
	nvme_रुको_मुक्तze(ctrl);
	nvme_sync_queues(ctrl);

	अगर (ctrl->state != NVME_CTRL_LIVE)
		जाओ unमुक्तze;

	ret = nvme_get_घातer_state(ctrl, &ndev->last_ps);
	अगर (ret < 0)
		जाओ unमुक्तze;

	/*
	 * A saved state prevents pci pm from generically controlling the
	 * device's power. If we're using protocol specific settings, we don't
	 * want pci पूर्णांकerfering.
	 */
	pci_save_state(pdev);

	ret = nvme_set_घातer_state(ctrl, ctrl->npss);
	अगर (ret < 0)
		जाओ unमुक्तze;

	अगर (ret) अणु
		/* discard the saved state */
		pci_load_saved_state(pdev, शून्य);

		/*
		 * Clearing npss क्रमces a controller reset on resume. The
		 * correct value will be rediscovered then.
		 */
		ret = nvme_disable_prepare_reset(ndev, true);
		ctrl->npss = 0;
	पूर्ण
unमुक्तze:
	nvme_unमुक्तze(ctrl);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_simple_suspend(काष्ठा device *dev)
अणु
	काष्ठा nvme_dev *ndev = pci_get_drvdata(to_pci_dev(dev));

	वापस nvme_disable_prepare_reset(ndev, true);
पूर्ण

अटल पूर्णांक nvme_simple_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा nvme_dev *ndev = pci_get_drvdata(pdev);

	वापस nvme_try_sched_reset(&ndev->ctrl);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops nvme_dev_pm_ops = अणु
	.suspend	= nvme_suspend,
	.resume		= nvme_resume,
	.मुक्तze		= nvme_simple_suspend,
	.thaw		= nvme_simple_resume,
	.घातeroff	= nvme_simple_suspend,
	.restore	= nvme_simple_resume,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल pci_ers_result_t nvme_error_detected(काष्ठा pci_dev *pdev,
						pci_channel_state_t state)
अणु
	काष्ठा nvme_dev *dev = pci_get_drvdata(pdev);

	/*
	 * A frozen channel requires a reset. When detected, this method will
	 * shutकरोwn the controller to quiesce. The controller will be restarted
	 * after the slot reset through driver's slot_reset callback.
	 */
	चयन (state) अणु
	हाल pci_channel_io_normal:
		वापस PCI_ERS_RESULT_CAN_RECOVER;
	हाल pci_channel_io_frozen:
		dev_warn(dev->ctrl.device,
			"frozen state error detected, reset controller\n");
		nvme_dev_disable(dev, false);
		वापस PCI_ERS_RESULT_NEED_RESET;
	हाल pci_channel_io_perm_failure:
		dev_warn(dev->ctrl.device,
			"failure state error detected, request disconnect\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t nvme_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा nvme_dev *dev = pci_get_drvdata(pdev);

	dev_info(dev->ctrl.device, "restart after slot reset\n");
	pci_restore_state(pdev);
	nvme_reset_ctrl(&dev->ctrl);
	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल व्योम nvme_error_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा nvme_dev *dev = pci_get_drvdata(pdev);

	flush_work(&dev->ctrl.reset_work);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers nvme_err_handler = अणु
	.error_detected	= nvme_error_detected,
	.slot_reset	= nvme_slot_reset,
	.resume		= nvme_error_resume,
	.reset_prepare	= nvme_reset_prepare,
	.reset_करोne	= nvme_reset_करोne,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id nvme_id_table[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x0953),	/* Intel 750/P3500/P3600/P3700 */
		.driver_data = NVME_QUIRK_STRIPE_SIZE |
				NVME_QUIRK_DEALLOCATE_ZEROES, पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0a53),	/* Intel P3520 */
		.driver_data = NVME_QUIRK_STRIPE_SIZE |
				NVME_QUIRK_DEALLOCATE_ZEROES, पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0a54),	/* Intel P4500/P4600 */
		.driver_data = NVME_QUIRK_STRIPE_SIZE |
				NVME_QUIRK_DEALLOCATE_ZEROES, पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0a55),	/* Dell Express Flash P4600 */
		.driver_data = NVME_QUIRK_STRIPE_SIZE |
				NVME_QUIRK_DEALLOCATE_ZEROES, पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xf1a5),	/* Intel 600P/P3100 */
		.driver_data = NVME_QUIRK_NO_DEEPEST_PS |
				NVME_QUIRK_MEDIUM_PRIO_SQ |
				NVME_QUIRK_NO_TEMP_THRESH_CHANGE |
				NVME_QUIRK_DISABLE_WRITE_ZEROES, पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xf1a6),	/* Intel 760p/Pro 7600p */
		.driver_data = NVME_QUIRK_IGNORE_DEV_SUBNQN, पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5845),	/* Qemu emulated controller */
		.driver_data = NVME_QUIRK_IDENTIFY_CNS |
				NVME_QUIRK_DISABLE_WRITE_ZEROES, पूर्ण,
	अणु PCI_DEVICE(0x126f, 0x2263),	/* Silicon Motion unidentअगरied */
		.driver_data = NVME_QUIRK_NO_NS_DESC_LIST, पूर्ण,
	अणु PCI_DEVICE(0x1bb1, 0x0100),   /* Seagate Nytro Flash Storage */
		.driver_data = NVME_QUIRK_DELAY_BEFORE_CHK_RDY |
				NVME_QUIRK_NO_NS_DESC_LIST, पूर्ण,
	अणु PCI_DEVICE(0x1c58, 0x0003),	/* HGST adapter */
		.driver_data = NVME_QUIRK_DELAY_BEFORE_CHK_RDY, पूर्ण,
	अणु PCI_DEVICE(0x1c58, 0x0023),	/* WDC SN200 adapter */
		.driver_data = NVME_QUIRK_DELAY_BEFORE_CHK_RDY, पूर्ण,
	अणु PCI_DEVICE(0x1c5f, 0x0540),	/* Memblaze Pblaze4 adapter */
		.driver_data = NVME_QUIRK_DELAY_BEFORE_CHK_RDY, पूर्ण,
	अणु PCI_DEVICE(0x144d, 0xa821),   /* Samsung PM1725 */
		.driver_data = NVME_QUIRK_DELAY_BEFORE_CHK_RDY, पूर्ण,
	अणु PCI_DEVICE(0x144d, 0xa822),   /* Samsung PM1725a */
		.driver_data = NVME_QUIRK_DELAY_BEFORE_CHK_RDY |
				NVME_QUIRK_DISABLE_WRITE_ZEROES|
				NVME_QUIRK_IGNORE_DEV_SUBNQN, पूर्ण,
	अणु PCI_DEVICE(0x1987, 0x5016),	/* Phison E16 */
		.driver_data = NVME_QUIRK_IGNORE_DEV_SUBNQN, पूर्ण,
	अणु PCI_DEVICE(0x1b4b, 0x1092),	/* Lexar 256 GB SSD */
		.driver_data = NVME_QUIRK_NO_NS_DESC_LIST |
				NVME_QUIRK_IGNORE_DEV_SUBNQN, पूर्ण,
	अणु PCI_DEVICE(0x1d1d, 0x1f1f),	/* LighNVM qemu device */
		.driver_data = NVME_QUIRK_LIGHTNVM, पूर्ण,
	अणु PCI_DEVICE(0x1d1d, 0x2807),	/* CNEX WL */
		.driver_data = NVME_QUIRK_LIGHTNVM, पूर्ण,
	अणु PCI_DEVICE(0x1d1d, 0x2601),	/* CNEX Granby */
		.driver_data = NVME_QUIRK_LIGHTNVM, पूर्ण,
	अणु PCI_DEVICE(0x10ec, 0x5762),   /* ADATA SX6000LNP */
		.driver_data = NVME_QUIRK_IGNORE_DEV_SUBNQN, पूर्ण,
	अणु PCI_DEVICE(0x1cc1, 0x8201),   /* ADATA SX8200PNP 512GB */
		.driver_data = NVME_QUIRK_NO_DEEPEST_PS |
				NVME_QUIRK_IGNORE_DEV_SUBNQN, पूर्ण,
	अणु PCI_DEVICE(0x1c5c, 0x1504),   /* SK Hynix PC400 */
		.driver_data = NVME_QUIRK_DISABLE_WRITE_ZEROES, पूर्ण,
	अणु PCI_DEVICE(0x15b7, 0x2001),   /*  Sandisk Skyhawk */
		.driver_data = NVME_QUIRK_DISABLE_WRITE_ZEROES, पूर्ण,
	अणु PCI_DEVICE(0x1d97, 0x2263),   /* SPCC */
		.driver_data = NVME_QUIRK_DISABLE_WRITE_ZEROES, पूर्ण,
	अणु PCI_DEVICE(0x2646, 0x2262),   /* KINGSTON SKC2000 NVMe SSD */
		.driver_data = NVME_QUIRK_NO_DEEPEST_PS, पूर्ण,
	अणु PCI_DEVICE(0x2646, 0x2263),   /* KINGSTON A2000 NVMe SSD  */
		.driver_data = NVME_QUIRK_NO_DEEPEST_PS, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMAZON, 0x0061),
		.driver_data = NVME_QUIRK_DMA_ADDRESS_BITS_48, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMAZON, 0x0065),
		.driver_data = NVME_QUIRK_DMA_ADDRESS_BITS_48, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMAZON, 0x8061),
		.driver_data = NVME_QUIRK_DMA_ADDRESS_BITS_48, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMAZON, 0xcd00),
		.driver_data = NVME_QUIRK_DMA_ADDRESS_BITS_48, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMAZON, 0xcd01),
		.driver_data = NVME_QUIRK_DMA_ADDRESS_BITS_48, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMAZON, 0xcd02),
		.driver_data = NVME_QUIRK_DMA_ADDRESS_BITS_48, पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_APPLE, 0x2001),
		.driver_data = NVME_QUIRK_SINGLE_VECTOR पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_APPLE, 0x2003) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_APPLE, 0x2005),
		.driver_data = NVME_QUIRK_SINGLE_VECTOR |
				NVME_QUIRK_128_BYTES_SQES |
				NVME_QUIRK_SHARED_TAGS पूर्ण,

	अणु PCI_DEVICE_CLASS(PCI_CLASS_STORAGE_EXPRESS, 0xffffff) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, nvme_id_table);

अटल काष्ठा pci_driver nvme_driver = अणु
	.name		= "nvme",
	.id_table	= nvme_id_table,
	.probe		= nvme_probe,
	.हटाओ		= nvme_हटाओ,
	.shutकरोwn	= nvme_shutकरोwn,
#अगर_घोषित CONFIG_PM_SLEEP
	.driver		= अणु
		.pm	= &nvme_dev_pm_ops,
	पूर्ण,
#पूर्ण_अगर
	.sriov_configure = pci_sriov_configure_simple,
	.err_handler	= &nvme_err_handler,
पूर्ण;

अटल पूर्णांक __init nvme_init(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा nvme_create_cq) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_create_sq) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_delete_queue) != 64);
	BUILD_BUG_ON(IRQ_AFFINITY_MAX_SETS < 2);

	वापस pci_रेजिस्टर_driver(&nvme_driver);
पूर्ण

अटल व्योम __निकास nvme_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&nvme_driver);
	flush_workqueue(nvme_wq);
पूर्ण

MODULE_AUTHOR("Matthew Wilcox <willy@linux.intel.com>");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
module_init(nvme_init);
module_निकास(nvme_निकास);
