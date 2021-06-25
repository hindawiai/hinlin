<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * CAAM/SEC 4.x transport/backend driver
 * JobR backend functionality
 *
 * Copyright 2008-2012 Freescale Semiconductor, Inc.
 * Copyright 2019 NXP
 */

#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>

#समावेश "compat.h"
#समावेश "ctrl.h"
#समावेश "regs.h"
#समावेश "jr.h"
#समावेश "desc.h"
#समावेश "intern.h"

काष्ठा jr_driver_data अणु
	/* List of Physical JobR's with the Driver */
	काष्ठा list_head	jr_list;
	spinlock_t		jr_alloc_lock;	/* jr_list lock */
पूर्ण ____cacheline_aligned;

अटल काष्ठा jr_driver_data driver_data;
अटल DEFINE_MUTEX(algs_lock);
अटल अचिन्हित पूर्णांक active_devs;

अटल व्योम रेजिस्टर_algs(काष्ठा caam_drv_निजी_jr *jrpriv,
			  काष्ठा device *dev)
अणु
	mutex_lock(&algs_lock);

	अगर (++active_devs != 1)
		जाओ algs_unlock;

	caam_algapi_init(dev);
	caam_algapi_hash_init(dev);
	caam_pkc_init(dev);
	jrpriv->hwrng = !caam_rng_init(dev);
	caam_qi_algapi_init(dev);

algs_unlock:
	mutex_unlock(&algs_lock);
पूर्ण

अटल व्योम unरेजिस्टर_algs(व्योम)
अणु
	mutex_lock(&algs_lock);

	अगर (--active_devs != 0)
		जाओ algs_unlock;

	caam_qi_algapi_निकास();

	caam_pkc_निकास();
	caam_algapi_hash_निकास();
	caam_algapi_निकास();

algs_unlock:
	mutex_unlock(&algs_lock);
पूर्ण

अटल व्योम caam_jr_crypto_engine_निकास(व्योम *data)
अणु
	काष्ठा device *jrdev = data;
	काष्ठा caam_drv_निजी_jr *jrpriv = dev_get_drvdata(jrdev);

	/* Free the resources of crypto-engine */
	crypto_engine_निकास(jrpriv->engine);
पूर्ण

अटल पूर्णांक caam_reset_hw_jr(काष्ठा device *dev)
अणु
	काष्ठा caam_drv_निजी_jr *jrp = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक समयout = 100000;

	/*
	 * mask पूर्णांकerrupts since we are going to poll
	 * क्रम reset completion status
	 */
	clrsetbits_32(&jrp->rregs->rconfig_lo, 0, JRCFG_IMSK);

	/* initiate flush (required prior to reset) */
	wr_reg32(&jrp->rregs->jrcommand, JRCR_RESET);
	जबतक (((rd_reg32(&jrp->rregs->jrपूर्णांकstatus) & JRINT_ERR_HALT_MASK) ==
		JRINT_ERR_HALT_INPROGRESS) && --समयout)
		cpu_relax();

	अगर ((rd_reg32(&jrp->rregs->jrपूर्णांकstatus) & JRINT_ERR_HALT_MASK) !=
	    JRINT_ERR_HALT_COMPLETE || समयout == 0) अणु
		dev_err(dev, "failed to flush job ring %d\n", jrp->ridx);
		वापस -EIO;
	पूर्ण

	/* initiate reset */
	समयout = 100000;
	wr_reg32(&jrp->rregs->jrcommand, JRCR_RESET);
	जबतक ((rd_reg32(&jrp->rregs->jrcommand) & JRCR_RESET) && --समयout)
		cpu_relax();

	अगर (समयout == 0) अणु
		dev_err(dev, "failed to reset job ring %d\n", jrp->ridx);
		वापस -EIO;
	पूर्ण

	/* unmask पूर्णांकerrupts */
	clrsetbits_32(&jrp->rregs->rconfig_lo, JRCFG_IMSK, 0);

	वापस 0;
पूर्ण

/*
 * Shutकरोwn JobR independent of platक्रमm property code
 */
अटल पूर्णांक caam_jr_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा caam_drv_निजी_jr *jrp = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = caam_reset_hw_jr(dev);

	tasklet_समाप्त(&jrp->irqtask);

	वापस ret;
पूर्ण

अटल पूर्णांक caam_jr_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा device *jrdev;
	काष्ठा caam_drv_निजी_jr *jrpriv;

	jrdev = &pdev->dev;
	jrpriv = dev_get_drvdata(jrdev);

	अगर (jrpriv->hwrng)
		caam_rng_निकास(jrdev->parent);

	/*
	 * Return EBUSY अगर job ring alपढ़ोy allocated.
	 */
	अगर (atomic_पढ़ो(&jrpriv->tfm_count)) अणु
		dev_err(jrdev, "Device is busy\n");
		वापस -EBUSY;
	पूर्ण

	/* Unरेजिस्टर JR-based RNG & crypto algorithms */
	unरेजिस्टर_algs();

	/* Remove the node from Physical JobR list मुख्यtained by driver */
	spin_lock(&driver_data.jr_alloc_lock);
	list_del(&jrpriv->list_node);
	spin_unlock(&driver_data.jr_alloc_lock);

	/* Release ring */
	ret = caam_jr_shutकरोwn(jrdev);
	अगर (ret)
		dev_err(jrdev, "Failed to shut down job ring\n");

	वापस ret;
पूर्ण

/* Main per-ring पूर्णांकerrupt handler */
अटल irqवापस_t caam_jr_पूर्णांकerrupt(पूर्णांक irq, व्योम *st_dev)
अणु
	काष्ठा device *dev = st_dev;
	काष्ठा caam_drv_निजी_jr *jrp = dev_get_drvdata(dev);
	u32 irqstate;

	/*
	 * Check the output ring क्रम पढ़ोy responses, kick
	 * tasklet अगर jobs करोne.
	 */
	irqstate = rd_reg32(&jrp->rregs->jrपूर्णांकstatus);
	अगर (!irqstate)
		वापस IRQ_NONE;

	/*
	 * If JobR error, we got more development work to करो
	 * Flag a bug now, but we really need to shut करोwn and
	 * restart the queue (and fix code).
	 */
	अगर (irqstate & JRINT_JR_ERROR) अणु
		dev_err(dev, "job ring error: irqstate: %08x\n", irqstate);
		BUG();
	पूर्ण

	/* mask valid पूर्णांकerrupts */
	clrsetbits_32(&jrp->rregs->rconfig_lo, 0, JRCFG_IMSK);

	/* Have valid पूर्णांकerrupt at this poपूर्णांक, just ACK and trigger */
	wr_reg32(&jrp->rregs->jrपूर्णांकstatus, irqstate);

	preempt_disable();
	tasklet_schedule(&jrp->irqtask);
	preempt_enable();

	वापस IRQ_HANDLED;
पूर्ण

/* Deferred service handler, run as पूर्णांकerrupt-fired tasklet */
अटल व्योम caam_jr_dequeue(अचिन्हित दीर्घ devarg)
अणु
	पूर्णांक hw_idx, sw_idx, i, head, tail;
	काष्ठा device *dev = (काष्ठा device *)devarg;
	काष्ठा caam_drv_निजी_jr *jrp = dev_get_drvdata(dev);
	व्योम (*usercall)(काष्ठा device *dev, u32 *desc, u32 status, व्योम *arg);
	u32 *userdesc, userstatus;
	व्योम *userarg;
	u32 outring_used = 0;

	जबतक (outring_used ||
	       (outring_used = rd_reg32(&jrp->rregs->outring_used))) अणु

		head = READ_ONCE(jrp->head);

		sw_idx = tail = jrp->tail;
		hw_idx = jrp->out_ring_पढ़ो_index;

		क्रम (i = 0; CIRC_CNT(head, tail + i, JOBR_DEPTH) >= 1; i++) अणु
			sw_idx = (tail + i) & (JOBR_DEPTH - 1);

			अगर (jr_outentry_desc(jrp->outring, hw_idx) ==
			    caam_dma_to_cpu(jrp->entinfo[sw_idx].desc_addr_dma))
				अवरोध; /* found */
		पूर्ण
		/* we should never fail to find a matching descriptor */
		BUG_ON(CIRC_CNT(head, tail + i, JOBR_DEPTH) <= 0);

		/* Unmap just-run descriptor so we can post-process */
		dma_unmap_single(dev,
				 caam_dma_to_cpu(jr_outentry_desc(jrp->outring,
								  hw_idx)),
				 jrp->entinfo[sw_idx].desc_size,
				 DMA_TO_DEVICE);

		/* mark completed, aव्योम matching on a recycled desc addr */
		jrp->entinfo[sw_idx].desc_addr_dma = 0;

		/* Stash callback params */
		usercall = jrp->entinfo[sw_idx].callbk;
		userarg = jrp->entinfo[sw_idx].cbkarg;
		userdesc = jrp->entinfo[sw_idx].desc_addr_virt;
		userstatus = caam32_to_cpu(jr_outentry_jrstatus(jrp->outring,
								hw_idx));

		/*
		 * Make sure all inक्रमmation from the job has been obtained
		 * beक्रमe telling CAAM that the job has been हटाओd from the
		 * output ring.
		 */
		mb();

		/* set करोne */
		wr_reg32(&jrp->rregs->outring_rmvd, 1);

		jrp->out_ring_पढ़ो_index = (jrp->out_ring_पढ़ो_index + 1) &
					   (JOBR_DEPTH - 1);

		/*
		 * अगर this job completed out-of-order, करो not increment
		 * the tail.  Otherwise, increment tail by 1 plus the
		 * number of subsequent jobs alपढ़ोy completed out-of-order
		 */
		अगर (sw_idx == tail) अणु
			करो अणु
				tail = (tail + 1) & (JOBR_DEPTH - 1);
			पूर्ण जबतक (CIRC_CNT(head, tail, JOBR_DEPTH) >= 1 &&
				 jrp->entinfo[tail].desc_addr_dma == 0);

			jrp->tail = tail;
		पूर्ण

		/* Finally, execute user's callback */
		usercall(dev, userdesc, userstatus, userarg);
		outring_used--;
	पूर्ण

	/* reenable / unmask IRQs */
	clrsetbits_32(&jrp->rregs->rconfig_lo, JRCFG_IMSK, 0);
पूर्ण

/**
 * caam_jr_alloc() - Alloc a job ring क्रम someone to use as needed.
 *
 * वापसs :  poपूर्णांकer to the newly allocated physical
 *	      JobR dev can be written to अगर successful.
 **/
काष्ठा device *caam_jr_alloc(व्योम)
अणु
	काष्ठा caam_drv_निजी_jr *jrpriv, *min_jrpriv = शून्य;
	काष्ठा device *dev = ERR_PTR(-ENODEV);
	पूर्णांक min_tfm_cnt	= पूर्णांक_उच्च;
	पूर्णांक tfm_cnt;

	spin_lock(&driver_data.jr_alloc_lock);

	अगर (list_empty(&driver_data.jr_list)) अणु
		spin_unlock(&driver_data.jr_alloc_lock);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	list_क्रम_each_entry(jrpriv, &driver_data.jr_list, list_node) अणु
		tfm_cnt = atomic_पढ़ो(&jrpriv->tfm_count);
		अगर (tfm_cnt < min_tfm_cnt) अणु
			min_tfm_cnt = tfm_cnt;
			min_jrpriv = jrpriv;
		पूर्ण
		अगर (!min_tfm_cnt)
			अवरोध;
	पूर्ण

	अगर (min_jrpriv) अणु
		atomic_inc(&min_jrpriv->tfm_count);
		dev = min_jrpriv->dev;
	पूर्ण
	spin_unlock(&driver_data.jr_alloc_lock);

	वापस dev;
पूर्ण
EXPORT_SYMBOL(caam_jr_alloc);

/**
 * caam_jr_मुक्त() - Free the Job Ring
 * @rdev:      poपूर्णांकs to the dev that identअगरies the Job ring to
 *             be released.
 **/
व्योम caam_jr_मुक्त(काष्ठा device *rdev)
अणु
	काष्ठा caam_drv_निजी_jr *jrpriv = dev_get_drvdata(rdev);

	atomic_dec(&jrpriv->tfm_count);
पूर्ण
EXPORT_SYMBOL(caam_jr_मुक्त);

/**
 * caam_jr_enqueue() - Enqueue a job descriptor head. Returns -EINPROGRESS
 * अगर OK, -ENOSPC अगर the queue is full, -EIO अगर it cannot map the caller's
 * descriptor.
 * @dev:  काष्ठा device of the job ring to be used
 * @desc: poपूर्णांकs to a job descriptor that execute our request. All
 *        descriptors (and all referenced data) must be in a DMAable
 *        region, and all data references must be physical addresses
 *        accessible to CAAM (i.e. within a PAMU winकरोw granted
 *        to it).
 * @cbk:  poपूर्णांकer to a callback function to be invoked upon completion
 *        of this request. This has the क्रमm:
 *        callback(काष्ठा device *dev, u32 *desc, u32 stat, व्योम *arg)
 *        where:
 *        dev:     contains the job ring device that processed this
 *                 response.
 *        desc:    descriptor that initiated the request, same as
 *                 "desc" being argued to caam_jr_enqueue().
 *        status:  untranslated status received from CAAM. See the
 *                 reference manual क्रम a detailed description of
 *                 error meaning, or see the JRSTA definitions in the
 *                 रेजिस्टर header file
 *        areq:    optional poपूर्णांकer to an argument passed with the
 *                 original request
 * @areq: optional poपूर्णांकer to a user argument क्रम use at callback
 *        समय.
 **/
पूर्णांक caam_jr_enqueue(काष्ठा device *dev, u32 *desc,
		    व्योम (*cbk)(काष्ठा device *dev, u32 *desc,
				u32 status, व्योम *areq),
		    व्योम *areq)
अणु
	काष्ठा caam_drv_निजी_jr *jrp = dev_get_drvdata(dev);
	काष्ठा caam_jrentry_info *head_entry;
	पूर्णांक head, tail, desc_size;
	dma_addr_t desc_dma;

	desc_size = (caam32_to_cpu(*desc) & HDR_JD_LENGTH_MASK) * माप(u32);
	desc_dma = dma_map_single(dev, desc, desc_size, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, desc_dma)) अणु
		dev_err(dev, "caam_jr_enqueue(): can't map jobdesc\n");
		वापस -EIO;
	पूर्ण

	spin_lock_bh(&jrp->inplock);

	head = jrp->head;
	tail = READ_ONCE(jrp->tail);

	अगर (!jrp->inpring_avail ||
	    CIRC_SPACE(head, tail, JOBR_DEPTH) <= 0) अणु
		spin_unlock_bh(&jrp->inplock);
		dma_unmap_single(dev, desc_dma, desc_size, DMA_TO_DEVICE);
		वापस -ENOSPC;
	पूर्ण

	head_entry = &jrp->entinfo[head];
	head_entry->desc_addr_virt = desc;
	head_entry->desc_size = desc_size;
	head_entry->callbk = (व्योम *)cbk;
	head_entry->cbkarg = areq;
	head_entry->desc_addr_dma = desc_dma;

	jr_inpentry_set(jrp->inpring, head, cpu_to_caam_dma(desc_dma));

	/*
	 * Guarantee that the descriptor's DMA address has been written to
	 * the next slot in the ring beक्रमe the ग_लिखो index is updated, since
	 * other cores may update this index independently.
	 */
	smp_wmb();

	jrp->head = (head + 1) & (JOBR_DEPTH - 1);

	/*
	 * Ensure that all job inक्रमmation has been written beक्रमe
	 * notअगरying CAAM that a new job was added to the input ring
	 * using a memory barrier. The wr_reg32() uses api ioग_लिखो32()
	 * to करो the रेजिस्टर ग_लिखो. ioग_लिखो32() issues a memory barrier
	 * beक्रमe the ग_लिखो operation.
	 */

	wr_reg32(&jrp->rregs->inpring_jobadd, 1);

	jrp->inpring_avail--;
	अगर (!jrp->inpring_avail)
		jrp->inpring_avail = rd_reg32(&jrp->rregs->inpring_avail);

	spin_unlock_bh(&jrp->inplock);

	वापस -EINPROGRESS;
पूर्ण
EXPORT_SYMBOL(caam_jr_enqueue);

/*
 * Init JobR independent of platक्रमm property detection
 */
अटल पूर्णांक caam_jr_init(काष्ठा device *dev)
अणु
	काष्ठा caam_drv_निजी_jr *jrp;
	dma_addr_t inpbusaddr, outbusaddr;
	पूर्णांक i, error;

	jrp = dev_get_drvdata(dev);

	error = caam_reset_hw_jr(dev);
	अगर (error)
		वापस error;

	jrp->inpring = dmam_alloc_coherent(dev, SIZखातापूर्ण_JR_INPENTRY *
					   JOBR_DEPTH, &inpbusaddr,
					   GFP_KERNEL);
	अगर (!jrp->inpring)
		वापस -ENOMEM;

	jrp->outring = dmam_alloc_coherent(dev, SIZखातापूर्ण_JR_OUTENTRY *
					   JOBR_DEPTH, &outbusaddr,
					   GFP_KERNEL);
	अगर (!jrp->outring)
		वापस -ENOMEM;

	jrp->entinfo = devm_kसुस्मृति(dev, JOBR_DEPTH, माप(*jrp->entinfo),
				    GFP_KERNEL);
	अगर (!jrp->entinfo)
		वापस -ENOMEM;

	क्रम (i = 0; i < JOBR_DEPTH; i++)
		jrp->entinfo[i].desc_addr_dma = !0;

	/* Setup rings */
	jrp->out_ring_पढ़ो_index = 0;
	jrp->head = 0;
	jrp->tail = 0;

	wr_reg64(&jrp->rregs->inpring_base, inpbusaddr);
	wr_reg64(&jrp->rregs->outring_base, outbusaddr);
	wr_reg32(&jrp->rregs->inpring_size, JOBR_DEPTH);
	wr_reg32(&jrp->rregs->outring_size, JOBR_DEPTH);

	jrp->inpring_avail = JOBR_DEPTH;

	spin_lock_init(&jrp->inplock);

	/* Select पूर्णांकerrupt coalescing parameters */
	clrsetbits_32(&jrp->rregs->rconfig_lo, 0, JOBR_INTC |
		      (JOBR_INTC_COUNT_THLD << JRCFG_ICDCT_SHIFT) |
		      (JOBR_INTC_TIME_THLD << JRCFG_ICTT_SHIFT));

	tasklet_init(&jrp->irqtask, caam_jr_dequeue, (अचिन्हित दीर्घ)dev);

	/* Connect job ring पूर्णांकerrupt handler. */
	error = devm_request_irq(dev, jrp->irq, caam_jr_पूर्णांकerrupt, IRQF_SHARED,
				 dev_name(dev), dev);
	अगर (error) अणु
		dev_err(dev, "can't connect JobR %d interrupt (%d)\n",
			jrp->ridx, jrp->irq);
		tasklet_समाप्त(&jrp->irqtask);
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम caam_jr_irq_dispose_mapping(व्योम *data)
अणु
	irq_dispose_mapping((अचिन्हित दीर्घ)data);
पूर्ण

/*
 * Probe routine क्रम each detected JobR subप्रणाली.
 */
अटल पूर्णांक caam_jr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *jrdev;
	काष्ठा device_node *nprop;
	काष्ठा caam_job_ring __iomem *ctrl;
	काष्ठा caam_drv_निजी_jr *jrpriv;
	अटल पूर्णांक total_jobrs;
	काष्ठा resource *r;
	पूर्णांक error;

	jrdev = &pdev->dev;
	jrpriv = devm_kzalloc(jrdev, माप(*jrpriv), GFP_KERNEL);
	अगर (!jrpriv)
		वापस -ENOMEM;

	dev_set_drvdata(jrdev, jrpriv);

	/* save ring identity relative to detection */
	jrpriv->ridx = total_jobrs++;

	nprop = pdev->dev.of_node;
	/* Get configuration properties from device tree */
	/* First, get रेजिस्टर page */
	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(jrdev, "platform_get_resource() failed\n");
		वापस -ENOMEM;
	पूर्ण

	ctrl = devm_ioremap(jrdev, r->start, resource_size(r));
	अगर (!ctrl) अणु
		dev_err(jrdev, "devm_ioremap() failed\n");
		वापस -ENOMEM;
	पूर्ण

	jrpriv->rregs = (काष्ठा caam_job_ring __iomem __क्रमce *)ctrl;

	error = dma_set_mask_and_coherent(jrdev, caam_get_dma_mask(jrdev));
	अगर (error) अणु
		dev_err(jrdev, "dma_set_mask_and_coherent failed (%d)\n",
			error);
		वापस error;
	पूर्ण

	/* Initialize crypto engine */
	jrpriv->engine = crypto_engine_alloc_init_and_set(jrdev, true, शून्य,
							  false,
							  CRYPTO_ENGINE_MAX_QLEN);
	अगर (!jrpriv->engine) अणु
		dev_err(jrdev, "Could not init crypto-engine\n");
		वापस -ENOMEM;
	पूर्ण

	error = devm_add_action_or_reset(jrdev, caam_jr_crypto_engine_निकास,
					 jrdev);
	अगर (error)
		वापस error;

	/* Start crypto engine */
	error = crypto_engine_start(jrpriv->engine);
	अगर (error) अणु
		dev_err(jrdev, "Could not start crypto-engine\n");
		वापस error;
	पूर्ण

	/* Identअगरy the पूर्णांकerrupt */
	jrpriv->irq = irq_of_parse_and_map(nprop, 0);
	अगर (!jrpriv->irq) अणु
		dev_err(jrdev, "irq_of_parse_and_map failed\n");
		वापस -EINVAL;
	पूर्ण

	error = devm_add_action_or_reset(jrdev, caam_jr_irq_dispose_mapping,
					 (व्योम *)(अचिन्हित दीर्घ)jrpriv->irq);
	अगर (error)
		वापस error;

	/* Now करो the platक्रमm independent part */
	error = caam_jr_init(jrdev); /* now turn on hardware */
	अगर (error)
		वापस error;

	jrpriv->dev = jrdev;
	spin_lock(&driver_data.jr_alloc_lock);
	list_add_tail(&jrpriv->list_node, &driver_data.jr_list);
	spin_unlock(&driver_data.jr_alloc_lock);

	atomic_set(&jrpriv->tfm_count, 0);

	रेजिस्टर_algs(jrpriv, jrdev->parent);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id caam_jr_match[] = अणु
	अणु
		.compatible = "fsl,sec-v4.0-job-ring",
	पूर्ण,
	अणु
		.compatible = "fsl,sec4.0-job-ring",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, caam_jr_match);

अटल काष्ठा platक्रमm_driver caam_jr_driver = अणु
	.driver = अणु
		.name = "caam_jr",
		.of_match_table = caam_jr_match,
	पूर्ण,
	.probe       = caam_jr_probe,
	.हटाओ      = caam_jr_हटाओ,
पूर्ण;

अटल पूर्णांक __init jr_driver_init(व्योम)
अणु
	spin_lock_init(&driver_data.jr_alloc_lock);
	INIT_LIST_HEAD(&driver_data.jr_list);
	वापस platक्रमm_driver_रेजिस्टर(&caam_jr_driver);
पूर्ण

अटल व्योम __निकास jr_driver_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&caam_jr_driver);
पूर्ण

module_init(jr_driver_init);
module_निकास(jr_driver_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("FSL CAAM JR request backend");
MODULE_AUTHOR("Freescale Semiconductor - NMG/STC");
