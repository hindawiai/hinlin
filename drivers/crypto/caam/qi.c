<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CAAM/SEC 4.x QI transport/backend driver
 * Queue Interface backend functionality
 *
 * Copyright 2013-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2019-2020 NXP
 */

#समावेश <linux/cpumask.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <soc/fsl/qman.h>

#समावेश "debugfs.h"
#समावेश "regs.h"
#समावेश "qi.h"
#समावेश "desc.h"
#समावेश "intern.h"
#समावेश "desc_constr.h"

#घोषणा PREHDR_RSLS_SHIFT	31
#घोषणा PREHDR_ABS		BIT(25)

/*
 * Use a reasonable backlog of frames (per CPU) as congestion threshold,
 * so that resources used by the in-flight buffers करो not become a memory hog.
 */
#घोषणा MAX_RSP_FQ_BACKLOG_PER_CPU	256

#घोषणा CAAM_QI_ENQUEUE_RETRIES	10000

#घोषणा CAAM_NAPI_WEIGHT	63

/*
 * caam_napi - काष्ठा holding CAAM NAPI-related params
 * @irqtask: IRQ task क्रम QI backend
 * @p: QMan portal
 */
काष्ठा caam_napi अणु
	काष्ठा napi_काष्ठा irqtask;
	काष्ठा qman_portal *p;
पूर्ण;

/*
 * caam_qi_pcpu_priv - percpu निजी data काष्ठाure to मुख्य list of pending
 *                     responses expected on each cpu.
 * @caam_napi: CAAM NAPI params
 * @net_dev: netdev used by NAPI
 * @rsp_fq: response FQ from CAAM
 */
काष्ठा caam_qi_pcpu_priv अणु
	काष्ठा caam_napi caam_napi;
	काष्ठा net_device net_dev;
	काष्ठा qman_fq *rsp_fq;
पूर्ण ____cacheline_aligned;

अटल DEFINE_PER_CPU(काष्ठा caam_qi_pcpu_priv, pcpu_qipriv);
अटल DEFINE_PER_CPU(पूर्णांक, last_cpu);

/*
 * caam_qi_priv - CAAM QI backend निजी params
 * @cgr: QMan congestion group
 */
काष्ठा caam_qi_priv अणु
	काष्ठा qman_cgr cgr;
पूर्ण;

अटल काष्ठा caam_qi_priv qipriv ____cacheline_aligned;

/*
 * This is written by only one core - the one that initialized the CGR - and
 * पढ़ो by multiple cores (all the others).
 */
bool caam_congested __पढ़ो_mostly;
EXPORT_SYMBOL(caam_congested);

/*
 * This is a a cache of buffers, from which the users of CAAM QI driver
 * can allocate लघु (CAAM_QI_MEMCACHE_SIZE) buffers. It's faster than
 * करोing दो_स्मृति on the hotpath.
 * NOTE: A more elegant solution would be to have some headroom in the frames
 *       being processed. This could be added by the dpaa-ethernet driver.
 *       This would pose a problem क्रम userspace application processing which
 *       cannot know of this limitation. So क्रम now, this will work.
 * NOTE: The memcache is SMP-safe. No need to handle spinlocks in-here
 */
अटल काष्ठा kmem_cache *qi_cache;

अटल व्योम *caam_iova_to_virt(काष्ठा iommu_करोमुख्य *करोमुख्य,
			       dma_addr_t iova_addr)
अणु
	phys_addr_t phys_addr;

	phys_addr = करोमुख्य ? iommu_iova_to_phys(करोमुख्य, iova_addr) : iova_addr;

	वापस phys_to_virt(phys_addr);
पूर्ण

पूर्णांक caam_qi_enqueue(काष्ठा device *qidev, काष्ठा caam_drv_req *req)
अणु
	काष्ठा qm_fd fd;
	dma_addr_t addr;
	पूर्णांक ret;
	पूर्णांक num_retries = 0;

	qm_fd_clear_fd(&fd);
	qm_fd_set_compound(&fd, qm_sg_entry_get_len(&req->fd_sgt[1]));

	addr = dma_map_single(qidev, req->fd_sgt, माप(req->fd_sgt),
			      DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(qidev, addr)) अणु
		dev_err(qidev, "DMA mapping error for QI enqueue request\n");
		वापस -EIO;
	पूर्ण
	qm_fd_addr_set64(&fd, addr);

	करो अणु
		ret = qman_enqueue(req->drv_ctx->req_fq, &fd);
		अगर (likely(!ret)) अणु
			refcount_inc(&req->drv_ctx->refcnt);
			वापस 0;
		पूर्ण

		अगर (ret != -EBUSY)
			अवरोध;
		num_retries++;
	पूर्ण जबतक (num_retries < CAAM_QI_ENQUEUE_RETRIES);

	dev_err(qidev, "qman_enqueue failed: %d\n", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(caam_qi_enqueue);

अटल व्योम caam_fq_ern_cb(काष्ठा qman_portal *qm, काष्ठा qman_fq *fq,
			   स्थिर जोड़ qm_mr_entry *msg)
अणु
	स्थिर काष्ठा qm_fd *fd;
	काष्ठा caam_drv_req *drv_req;
	काष्ठा device *qidev = &(raw_cpu_ptr(&pcpu_qipriv)->net_dev.dev);
	काष्ठा caam_drv_निजी *priv = dev_get_drvdata(qidev);

	fd = &msg->ern.fd;

	drv_req = caam_iova_to_virt(priv->करोमुख्य, qm_fd_addr_get64(fd));
	अगर (!drv_req) अणु
		dev_err(qidev,
			"Can't find original request for CAAM response\n");
		वापस;
	पूर्ण

	refcount_dec(&drv_req->drv_ctx->refcnt);

	अगर (qm_fd_get_क्रमmat(fd) != qm_fd_compound) अणु
		dev_err(qidev, "Non-compound FD from CAAM\n");
		वापस;
	पूर्ण

	dma_unmap_single(drv_req->drv_ctx->qidev, qm_fd_addr(fd),
			 माप(drv_req->fd_sgt), DMA_BIसूचीECTIONAL);

	अगर (fd->status)
		drv_req->cbk(drv_req, be32_to_cpu(fd->status));
	अन्यथा
		drv_req->cbk(drv_req, JRSTA_SSRC_QI);
पूर्ण

अटल काष्ठा qman_fq *create_caam_req_fq(काष्ठा device *qidev,
					  काष्ठा qman_fq *rsp_fq,
					  dma_addr_t hwdesc,
					  पूर्णांक fq_sched_flag)
अणु
	पूर्णांक ret;
	काष्ठा qman_fq *req_fq;
	काष्ठा qm_mcc_initfq opts;

	req_fq = kzalloc(माप(*req_fq), GFP_ATOMIC);
	अगर (!req_fq)
		वापस ERR_PTR(-ENOMEM);

	req_fq->cb.ern = caam_fq_ern_cb;
	req_fq->cb.fqs = शून्य;

	ret = qman_create_fq(0, QMAN_FQ_FLAG_DYNAMIC_FQID |
				QMAN_FQ_FLAG_TO_DCPORTAL, req_fq);
	अगर (ret) अणु
		dev_err(qidev, "Failed to create session req FQ\n");
		जाओ create_req_fq_fail;
	पूर्ण

	स_रखो(&opts, 0, माप(opts));
	opts.we_mask = cpu_to_be16(QM_INITFQ_WE_FQCTRL | QM_INITFQ_WE_DESTWQ |
				   QM_INITFQ_WE_CONTEXTB |
				   QM_INITFQ_WE_CONTEXTA | QM_INITFQ_WE_CGID);
	opts.fqd.fq_ctrl = cpu_to_be16(QM_FQCTRL_CPCSTASH | QM_FQCTRL_CGE);
	qm_fqd_set_destwq(&opts.fqd, qm_channel_caam, 2);
	opts.fqd.context_b = cpu_to_be32(qman_fq_fqid(rsp_fq));
	qm_fqd_context_a_set64(&opts.fqd, hwdesc);
	opts.fqd.cgid = qipriv.cgr.cgrid;

	ret = qman_init_fq(req_fq, fq_sched_flag, &opts);
	अगर (ret) अणु
		dev_err(qidev, "Failed to init session req FQ\n");
		जाओ init_req_fq_fail;
	पूर्ण

	dev_dbg(qidev, "Allocated request FQ %u for CPU %u\n", req_fq->fqid,
		smp_processor_id());
	वापस req_fq;

init_req_fq_fail:
	qman_destroy_fq(req_fq);
create_req_fq_fail:
	kमुक्त(req_fq);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक empty_retired_fq(काष्ठा device *qidev, काष्ठा qman_fq *fq)
अणु
	पूर्णांक ret;

	ret = qman_अस्थिर_dequeue(fq, QMAN_VOLATILE_FLAG_WAIT_INT |
				    QMAN_VOLATILE_FLAG_FINISH,
				    QM_VDQCR_PRECEDENCE_VDQCR |
				    QM_VDQCR_NUMFRAMES_TILLEMPTY);
	अगर (ret) अणु
		dev_err(qidev, "Volatile dequeue fail for FQ: %u\n", fq->fqid);
		वापस ret;
	पूर्ण

	करो अणु
		काष्ठा qman_portal *p;

		p = qman_get_affine_portal(smp_processor_id());
		qman_p_poll_dqrr(p, 16);
	पूर्ण जबतक (fq->flags & QMAN_FQ_STATE_NE);

	वापस 0;
पूर्ण

अटल पूर्णांक समाप्त_fq(काष्ठा device *qidev, काष्ठा qman_fq *fq)
अणु
	u32 flags;
	पूर्णांक ret;

	ret = qman_retire_fq(fq, &flags);
	अगर (ret < 0) अणु
		dev_err(qidev, "qman_retire_fq failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!ret)
		जाओ empty_fq;

	/* Async FQ retirement condition */
	अगर (ret == 1) अणु
		/* Retry till FQ माला_लो in retired state */
		करो अणु
			msleep(20);
		पूर्ण जबतक (fq->state != qman_fq_state_retired);

		WARN_ON(fq->flags & QMAN_FQ_STATE_BLOCKOOS);
		WARN_ON(fq->flags & QMAN_FQ_STATE_ORL);
	पूर्ण

empty_fq:
	अगर (fq->flags & QMAN_FQ_STATE_NE) अणु
		ret = empty_retired_fq(qidev, fq);
		अगर (ret) अणु
			dev_err(qidev, "empty_retired_fq fail for FQ: %u\n",
				fq->fqid);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = qman_oos_fq(fq);
	अगर (ret)
		dev_err(qidev, "OOS of FQID: %u failed\n", fq->fqid);

	qman_destroy_fq(fq);
	kमुक्त(fq);

	वापस ret;
पूर्ण

अटल पूर्णांक empty_caam_fq(काष्ठा qman_fq *fq, काष्ठा caam_drv_ctx *drv_ctx)
अणु
	पूर्णांक ret;
	पूर्णांक retries = 10;
	काष्ठा qm_mcr_queryfq_np np;

	/* Wait till the older CAAM FQ get empty */
	करो अणु
		ret = qman_query_fq_np(fq, &np);
		अगर (ret)
			वापस ret;

		अगर (!qm_mcr_np_get(&np, frm_cnt))
			अवरोध;

		msleep(20);
	पूर्ण जबतक (1);

	/* Wait until pending jobs from this FQ are processed by CAAM */
	करो अणु
		अगर (refcount_पढ़ो(&drv_ctx->refcnt) == 1)
			अवरोध;

		msleep(20);
	पूर्ण जबतक (--retries);

	अगर (!retries)
		dev_warn_once(drv_ctx->qidev, "%d frames from FQID %u still pending in CAAM\n",
			      refcount_पढ़ो(&drv_ctx->refcnt), fq->fqid);

	वापस 0;
पूर्ण

पूर्णांक caam_drv_ctx_update(काष्ठा caam_drv_ctx *drv_ctx, u32 *sh_desc)
अणु
	पूर्णांक ret;
	u32 num_words;
	काष्ठा qman_fq *new_fq, *old_fq;
	काष्ठा device *qidev = drv_ctx->qidev;

	num_words = desc_len(sh_desc);
	अगर (num_words > MAX_SDLEN) अणु
		dev_err(qidev, "Invalid descriptor len: %d words\n", num_words);
		वापस -EINVAL;
	पूर्ण

	/* Note करोwn older req FQ */
	old_fq = drv_ctx->req_fq;

	/* Create a new req FQ in parked state */
	new_fq = create_caam_req_fq(drv_ctx->qidev, drv_ctx->rsp_fq,
				    drv_ctx->context_a, 0);
	अगर (IS_ERR(new_fq)) अणु
		dev_err(qidev, "FQ allocation for shdesc update failed\n");
		वापस PTR_ERR(new_fq);
	पूर्ण

	/* Hook up new FQ to context so that new requests keep queuing */
	drv_ctx->req_fq = new_fq;

	/* Empty and हटाओ the older FQ */
	ret = empty_caam_fq(old_fq, drv_ctx);
	अगर (ret) अणु
		dev_err(qidev, "Old CAAM FQ empty failed: %d\n", ret);

		/* We can revert to older FQ */
		drv_ctx->req_fq = old_fq;

		अगर (समाप्त_fq(qidev, new_fq))
			dev_warn(qidev, "New CAAM FQ kill failed\n");

		वापस ret;
	पूर्ण

	/*
	 * Re-initialise pre-header. Set RSLS and SDLEN.
	 * Update the shared descriptor क्रम driver context.
	 */
	drv_ctx->prehdr[0] = cpu_to_caam32((1 << PREHDR_RSLS_SHIFT) |
					   num_words);
	drv_ctx->prehdr[1] = cpu_to_caam32(PREHDR_ABS);
	स_नकल(drv_ctx->sh_desc, sh_desc, desc_bytes(sh_desc));
	dma_sync_single_क्रम_device(qidev, drv_ctx->context_a,
				   माप(drv_ctx->sh_desc) +
				   माप(drv_ctx->prehdr),
				   DMA_BIसूचीECTIONAL);

	/* Put the new FQ in scheduled state */
	ret = qman_schedule_fq(new_fq);
	अगर (ret) अणु
		dev_err(qidev, "Fail to sched new CAAM FQ, ecode = %d\n", ret);

		/*
		 * We can समाप्त new FQ and revert to old FQ.
		 * Since the desc is alपढ़ोy modअगरied, it is success हाल
		 */

		drv_ctx->req_fq = old_fq;

		अगर (समाप्त_fq(qidev, new_fq))
			dev_warn(qidev, "New CAAM FQ kill failed\n");
	पूर्ण अन्यथा अगर (समाप्त_fq(qidev, old_fq)) अणु
		dev_warn(qidev, "Old CAAM FQ kill failed\n");
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(caam_drv_ctx_update);

काष्ठा caam_drv_ctx *caam_drv_ctx_init(काष्ठा device *qidev,
				       पूर्णांक *cpu,
				       u32 *sh_desc)
अणु
	माप_प्रकार size;
	u32 num_words;
	dma_addr_t hwdesc;
	काष्ठा caam_drv_ctx *drv_ctx;
	स्थिर cpumask_t *cpus = qman_affine_cpus();

	num_words = desc_len(sh_desc);
	अगर (num_words > MAX_SDLEN) अणु
		dev_err(qidev, "Invalid descriptor len: %d words\n",
			num_words);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	drv_ctx = kzalloc(माप(*drv_ctx), GFP_ATOMIC);
	अगर (!drv_ctx)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * Initialise pre-header - set RSLS and SDLEN - and shared descriptor
	 * and dma-map them.
	 */
	drv_ctx->prehdr[0] = cpu_to_caam32((1 << PREHDR_RSLS_SHIFT) |
					   num_words);
	drv_ctx->prehdr[1] = cpu_to_caam32(PREHDR_ABS);
	स_नकल(drv_ctx->sh_desc, sh_desc, desc_bytes(sh_desc));
	size = माप(drv_ctx->prehdr) + माप(drv_ctx->sh_desc);
	hwdesc = dma_map_single(qidev, drv_ctx->prehdr, size,
				DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(qidev, hwdesc)) अणु
		dev_err(qidev, "DMA map error for preheader + shdesc\n");
		kमुक्त(drv_ctx);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	drv_ctx->context_a = hwdesc;

	/* If given CPU करोes not own the portal, choose another one that करोes */
	अगर (!cpumask_test_cpu(*cpu, cpus)) अणु
		पूर्णांक *pcpu = &get_cpu_var(last_cpu);

		*pcpu = cpumask_next(*pcpu, cpus);
		अगर (*pcpu >= nr_cpu_ids)
			*pcpu = cpumask_first(cpus);
		*cpu = *pcpu;

		put_cpu_var(last_cpu);
	पूर्ण
	drv_ctx->cpu = *cpu;

	/* Find response FQ hooked with this CPU */
	drv_ctx->rsp_fq = per_cpu(pcpu_qipriv.rsp_fq, drv_ctx->cpu);

	/* Attach request FQ */
	drv_ctx->req_fq = create_caam_req_fq(qidev, drv_ctx->rsp_fq, hwdesc,
					     QMAN_INITFQ_FLAG_SCHED);
	अगर (IS_ERR(drv_ctx->req_fq)) अणु
		dev_err(qidev, "create_caam_req_fq failed\n");
		dma_unmap_single(qidev, hwdesc, size, DMA_BIसूचीECTIONAL);
		kमुक्त(drv_ctx);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* init reference counter used to track references to request FQ */
	refcount_set(&drv_ctx->refcnt, 1);

	drv_ctx->qidev = qidev;
	वापस drv_ctx;
पूर्ण
EXPORT_SYMBOL(caam_drv_ctx_init);

व्योम *qi_cache_alloc(gfp_t flags)
अणु
	वापस kmem_cache_alloc(qi_cache, flags);
पूर्ण
EXPORT_SYMBOL(qi_cache_alloc);

व्योम qi_cache_मुक्त(व्योम *obj)
अणु
	kmem_cache_मुक्त(qi_cache, obj);
पूर्ण
EXPORT_SYMBOL(qi_cache_मुक्त);

अटल पूर्णांक caam_qi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा caam_napi *np = container_of(napi, काष्ठा caam_napi, irqtask);

	पूर्णांक cleaned = qman_p_poll_dqrr(np->p, budget);

	अगर (cleaned < budget) अणु
		napi_complete(napi);
		qman_p_irqsource_add(np->p, QM_PIRQ_DQRI);
	पूर्ण

	वापस cleaned;
पूर्ण

व्योम caam_drv_ctx_rel(काष्ठा caam_drv_ctx *drv_ctx)
अणु
	अगर (IS_ERR_OR_शून्य(drv_ctx))
		वापस;

	/* Remove request FQ */
	अगर (समाप्त_fq(drv_ctx->qidev, drv_ctx->req_fq))
		dev_err(drv_ctx->qidev, "Crypto session req FQ kill failed\n");

	dma_unmap_single(drv_ctx->qidev, drv_ctx->context_a,
			 माप(drv_ctx->sh_desc) + माप(drv_ctx->prehdr),
			 DMA_BIसूचीECTIONAL);
	kमुक्त(drv_ctx);
पूर्ण
EXPORT_SYMBOL(caam_drv_ctx_rel);

अटल व्योम caam_qi_shutकरोwn(व्योम *data)
अणु
	पूर्णांक i;
	काष्ठा device *qidev = data;
	काष्ठा caam_qi_priv *priv = &qipriv;
	स्थिर cpumask_t *cpus = qman_affine_cpus();

	क्रम_each_cpu(i, cpus) अणु
		काष्ठा napi_काष्ठा *irqtask;

		irqtask = &per_cpu_ptr(&pcpu_qipriv.caam_napi, i)->irqtask;
		napi_disable(irqtask);
		netअगर_napi_del(irqtask);

		अगर (समाप्त_fq(qidev, per_cpu(pcpu_qipriv.rsp_fq, i)))
			dev_err(qidev, "Rsp FQ kill failed, cpu: %d\n", i);
	पूर्ण

	qman_delete_cgr_safe(&priv->cgr);
	qman_release_cgrid(priv->cgr.cgrid);

	kmem_cache_destroy(qi_cache);
पूर्ण

अटल व्योम cgr_cb(काष्ठा qman_portal *qm, काष्ठा qman_cgr *cgr, पूर्णांक congested)
अणु
	caam_congested = congested;

	अगर (congested) अणु
		caam_debugfs_qi_congested();

		pr_debug_ratelimited("CAAM entered congestion\n");

	पूर्ण अन्यथा अणु
		pr_debug_ratelimited("CAAM exited congestion\n");
	पूर्ण
पूर्ण

अटल पूर्णांक caam_qi_napi_schedule(काष्ठा qman_portal *p, काष्ठा caam_napi *np,
				 bool sched_napi)
अणु
	अगर (sched_napi) अणु
		/* Disable QMan IRQ source and invoke NAPI */
		qman_p_irqsource_हटाओ(p, QM_PIRQ_DQRI);
		np->p = p;
		napi_schedule(&np->irqtask);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत qman_cb_dqrr_result caam_rsp_fq_dqrr_cb(काष्ठा qman_portal *p,
						    काष्ठा qman_fq *rsp_fq,
						    स्थिर काष्ठा qm_dqrr_entry *dqrr,
						    bool sched_napi)
अणु
	काष्ठा caam_napi *caam_napi = raw_cpu_ptr(&pcpu_qipriv.caam_napi);
	काष्ठा caam_drv_req *drv_req;
	स्थिर काष्ठा qm_fd *fd;
	काष्ठा device *qidev = &(raw_cpu_ptr(&pcpu_qipriv)->net_dev.dev);
	काष्ठा caam_drv_निजी *priv = dev_get_drvdata(qidev);
	u32 status;

	अगर (caam_qi_napi_schedule(p, caam_napi, sched_napi))
		वापस qman_cb_dqrr_stop;

	fd = &dqrr->fd;

	drv_req = caam_iova_to_virt(priv->करोमुख्य, qm_fd_addr_get64(fd));
	अगर (unlikely(!drv_req)) अणु
		dev_err(qidev,
			"Can't find original request for caam response\n");
		वापस qman_cb_dqrr_consume;
	पूर्ण

	refcount_dec(&drv_req->drv_ctx->refcnt);

	status = be32_to_cpu(fd->status);
	अगर (unlikely(status)) अणु
		u32 ssrc = status & JRSTA_SSRC_MASK;
		u8 err_id = status & JRSTA_CCBERR_ERRID_MASK;

		अगर (ssrc != JRSTA_SSRC_CCB_ERROR ||
		    err_id != JRSTA_CCBERR_ERRID_ICVCHK)
			dev_err_ratelimited(qidev,
					    "Error: %#x in CAAM response FD\n",
					    status);
	पूर्ण

	अगर (unlikely(qm_fd_get_क्रमmat(fd) != qm_fd_compound)) अणु
		dev_err(qidev, "Non-compound FD from CAAM\n");
		वापस qman_cb_dqrr_consume;
	पूर्ण

	dma_unmap_single(drv_req->drv_ctx->qidev, qm_fd_addr(fd),
			 माप(drv_req->fd_sgt), DMA_BIसूचीECTIONAL);

	drv_req->cbk(drv_req, status);
	वापस qman_cb_dqrr_consume;
पूर्ण

अटल पूर्णांक alloc_rsp_fq_cpu(काष्ठा device *qidev, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा qm_mcc_initfq opts;
	काष्ठा qman_fq *fq;
	पूर्णांक ret;

	fq = kzalloc(माप(*fq), GFP_KERNEL | GFP_DMA);
	अगर (!fq)
		वापस -ENOMEM;

	fq->cb.dqrr = caam_rsp_fq_dqrr_cb;

	ret = qman_create_fq(0, QMAN_FQ_FLAG_NO_ENQUEUE |
			     QMAN_FQ_FLAG_DYNAMIC_FQID, fq);
	अगर (ret) अणु
		dev_err(qidev, "Rsp FQ create failed\n");
		kमुक्त(fq);
		वापस -ENODEV;
	पूर्ण

	स_रखो(&opts, 0, माप(opts));
	opts.we_mask = cpu_to_be16(QM_INITFQ_WE_FQCTRL | QM_INITFQ_WE_DESTWQ |
				   QM_INITFQ_WE_CONTEXTB |
				   QM_INITFQ_WE_CONTEXTA | QM_INITFQ_WE_CGID);
	opts.fqd.fq_ctrl = cpu_to_be16(QM_FQCTRL_CTXASTASHING |
				       QM_FQCTRL_CPCSTASH | QM_FQCTRL_CGE);
	qm_fqd_set_destwq(&opts.fqd, qman_affine_channel(cpu), 3);
	opts.fqd.cgid = qipriv.cgr.cgrid;
	opts.fqd.context_a.stashing.exclusive =	QM_STASHING_EXCL_CTX |
						QM_STASHING_EXCL_DATA;
	qm_fqd_set_stashing(&opts.fqd, 0, 1, 1);

	ret = qman_init_fq(fq, QMAN_INITFQ_FLAG_SCHED, &opts);
	अगर (ret) अणु
		dev_err(qidev, "Rsp FQ init failed\n");
		kमुक्त(fq);
		वापस -ENODEV;
	पूर्ण

	per_cpu(pcpu_qipriv.rsp_fq, cpu) = fq;

	dev_dbg(qidev, "Allocated response FQ %u for CPU %u", fq->fqid, cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक init_cgr(काष्ठा device *qidev)
अणु
	पूर्णांक ret;
	काष्ठा qm_mcc_initcgr opts;
	स्थिर u64 val = (u64)cpumask_weight(qman_affine_cpus()) *
			MAX_RSP_FQ_BACKLOG_PER_CPU;

	ret = qman_alloc_cgrid(&qipriv.cgr.cgrid);
	अगर (ret) अणु
		dev_err(qidev, "CGR alloc failed for rsp FQs: %d\n", ret);
		वापस ret;
	पूर्ण

	qipriv.cgr.cb = cgr_cb;
	स_रखो(&opts, 0, माप(opts));
	opts.we_mask = cpu_to_be16(QM_CGR_WE_CSCN_EN | QM_CGR_WE_CS_THRES |
				   QM_CGR_WE_MODE);
	opts.cgr.cscn_en = QM_CGR_EN;
	opts.cgr.mode = QMAN_CGR_MODE_FRAME;
	qm_cgr_cs_thres_set64(&opts.cgr.cs_thres, val, 1);

	ret = qman_create_cgr(&qipriv.cgr, QMAN_CGR_FLAG_USE_INIT, &opts);
	अगर (ret) अणु
		dev_err(qidev, "Error %d creating CAAM CGRID: %u\n", ret,
			qipriv.cgr.cgrid);
		वापस ret;
	पूर्ण

	dev_dbg(qidev, "Congestion threshold set to %llu\n", val);
	वापस 0;
पूर्ण

अटल पूर्णांक alloc_rsp_fqs(काष्ठा device *qidev)
अणु
	पूर्णांक ret, i;
	स्थिर cpumask_t *cpus = qman_affine_cpus();

	/*Now create response FQs*/
	क्रम_each_cpu(i, cpus) अणु
		ret = alloc_rsp_fq_cpu(qidev, i);
		अगर (ret) अणु
			dev_err(qidev, "CAAM rsp FQ alloc failed, cpu: %u", i);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम मुक्त_rsp_fqs(व्योम)
अणु
	पूर्णांक i;
	स्थिर cpumask_t *cpus = qman_affine_cpus();

	क्रम_each_cpu(i, cpus)
		kमुक्त(per_cpu(pcpu_qipriv.rsp_fq, i));
पूर्ण

पूर्णांक caam_qi_init(काष्ठा platक्रमm_device *caam_pdev)
अणु
	पूर्णांक err, i;
	काष्ठा device *ctrldev = &caam_pdev->dev, *qidev;
	काष्ठा caam_drv_निजी *ctrlpriv;
	स्थिर cpumask_t *cpus = qman_affine_cpus();

	ctrlpriv = dev_get_drvdata(ctrldev);
	qidev = ctrldev;

	/* Initialize the congestion detection */
	err = init_cgr(qidev);
	अगर (err) अणु
		dev_err(qidev, "CGR initialization failed: %d\n", err);
		वापस err;
	पूर्ण

	/* Initialise response FQs */
	err = alloc_rsp_fqs(qidev);
	अगर (err) अणु
		dev_err(qidev, "Can't allocate CAAM response FQs: %d\n", err);
		मुक्त_rsp_fqs();
		वापस err;
	पूर्ण

	/*
	 * Enable the NAPI contexts on each of the core which has an affine
	 * portal.
	 */
	क्रम_each_cpu(i, cpus) अणु
		काष्ठा caam_qi_pcpu_priv *priv = per_cpu_ptr(&pcpu_qipriv, i);
		काष्ठा caam_napi *caam_napi = &priv->caam_napi;
		काष्ठा napi_काष्ठा *irqtask = &caam_napi->irqtask;
		काष्ठा net_device *net_dev = &priv->net_dev;

		net_dev->dev = *qidev;
		INIT_LIST_HEAD(&net_dev->napi_list);

		netअगर_napi_add(net_dev, irqtask, caam_qi_poll,
			       CAAM_NAPI_WEIGHT);

		napi_enable(irqtask);
	पूर्ण

	qi_cache = kmem_cache_create("caamqicache", CAAM_QI_MEMCACHE_SIZE, 0,
				     SLAB_CACHE_DMA, शून्य);
	अगर (!qi_cache) अणु
		dev_err(qidev, "Can't allocate CAAM cache\n");
		मुक्त_rsp_fqs();
		वापस -ENOMEM;
	पूर्ण

	caam_debugfs_qi_init(ctrlpriv);

	err = devm_add_action_or_reset(qidev, caam_qi_shutकरोwn, ctrlpriv);
	अगर (err)
		वापस err;

	dev_info(qidev, "Linux CAAM Queue I/F driver initialised\n");
	वापस 0;
पूर्ण
