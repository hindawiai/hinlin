<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright 2016-2019 NXP
 *
 */
#समावेश <linux/types.h>
#समावेश <linux/fsl/mc.h>
#समावेश <soc/fsl/dpaa2-पन.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>

#समावेश "dpio.h"
#समावेश "qbman-portal.h"

काष्ठा dpaa2_io अणु
	काष्ठा dpaa2_io_desc dpio_desc;
	काष्ठा qbman_swp_desc swp_desc;
	काष्ठा qbman_swp *swp;
	काष्ठा list_head node;
	/* protect against multiple management commands */
	spinlock_t lock_mgmt_cmd;
	/* protect notअगरications list */
	spinlock_t lock_notअगरications;
	काष्ठा list_head notअगरications;
	काष्ठा device *dev;
पूर्ण;

काष्ठा dpaa2_io_store अणु
	अचिन्हित पूर्णांक max;
	dma_addr_t paddr;
	काष्ठा dpaa2_dq *vaddr;
	व्योम *alloced_addr;    /* unaligned value from kदो_स्मृति() */
	अचिन्हित पूर्णांक idx;      /* position of the next-to-be-वापसed entry */
	काष्ठा qbman_swp *swp; /* portal used to issue VDQCR */
	काष्ठा device *dev;    /* device used क्रम DMA mapping */
पूर्ण;

/* keep a per cpu array of DPIOs क्रम fast access */
अटल काष्ठा dpaa2_io *dpio_by_cpu[NR_CPUS];
अटल काष्ठा list_head dpio_list = LIST_HEAD_INIT(dpio_list);
अटल DEFINE_SPINLOCK(dpio_list_lock);

अटल अंतरभूत काष्ठा dpaa2_io *service_select_by_cpu(काष्ठा dpaa2_io *d,
						     पूर्णांक cpu)
अणु
	अगर (d)
		वापस d;

	अगर (cpu != DPAA2_IO_ANY_CPU && cpu >= num_possible_cpus())
		वापस शून्य;

	/*
	 * If cpu == -1, choose the current cpu, with no guarantees about
	 * potentially being migrated away.
	 */
	अगर (cpu < 0)
		cpu = smp_processor_id();

	/* If a specअगरic cpu was requested, pick it up immediately */
	वापस dpio_by_cpu[cpu];
पूर्ण

अटल अंतरभूत काष्ठा dpaa2_io *service_select(काष्ठा dpaa2_io *d)
अणु
	अगर (d)
		वापस d;

	d = service_select_by_cpu(d, -1);
	अगर (d)
		वापस d;

	spin_lock(&dpio_list_lock);
	d = list_entry(dpio_list.next, काष्ठा dpaa2_io, node);
	list_del(&d->node);
	list_add_tail(&d->node, &dpio_list);
	spin_unlock(&dpio_list_lock);

	वापस d;
पूर्ण

/**
 * dpaa2_io_service_select() - वापस a dpaa2_io service affined to this cpu
 * @cpu: the cpu id
 *
 * Return the affine dpaa2_io service, or शून्य अगर there is no service affined
 * to the specअगरied cpu. If DPAA2_IO_ANY_CPU is used, वापस the next available
 * service.
 */
काष्ठा dpaa2_io *dpaa2_io_service_select(पूर्णांक cpu)
अणु
	अगर (cpu == DPAA2_IO_ANY_CPU)
		वापस service_select(शून्य);

	वापस service_select_by_cpu(शून्य, cpu);
पूर्ण
EXPORT_SYMBOL_GPL(dpaa2_io_service_select);

/**
 * dpaa2_io_create() - create a dpaa2_io object.
 * @desc: the dpaa2_io descriptor
 * @dev: the actual DPIO device
 *
 * Activates a "struct dpaa2_io" corresponding to the given config of an actual
 * DPIO object.
 *
 * Return a valid dpaa2_io object क्रम success, or शून्य क्रम failure.
 */
काष्ठा dpaa2_io *dpaa2_io_create(स्थिर काष्ठा dpaa2_io_desc *desc,
				 काष्ठा device *dev)
अणु
	काष्ठा dpaa2_io *obj = kदो_स्मृति(माप(*obj), GFP_KERNEL);

	अगर (!obj)
		वापस शून्य;

	/* check अगर CPU is out of range (-1 means any cpu) */
	अगर (desc->cpu != DPAA2_IO_ANY_CPU && desc->cpu >= num_possible_cpus()) अणु
		kमुक्त(obj);
		वापस शून्य;
	पूर्ण

	obj->dpio_desc = *desc;
	obj->swp_desc.cena_bar = obj->dpio_desc.regs_cena;
	obj->swp_desc.cinh_bar = obj->dpio_desc.regs_cinh;
	obj->swp_desc.qman_version = obj->dpio_desc.qman_version;
	obj->swp = qbman_swp_init(&obj->swp_desc);

	अगर (!obj->swp) अणु
		kमुक्त(obj);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&obj->node);
	spin_lock_init(&obj->lock_mgmt_cmd);
	spin_lock_init(&obj->lock_notअगरications);
	INIT_LIST_HEAD(&obj->notअगरications);

	/* For now only enable DQRR पूर्णांकerrupts */
	qbman_swp_पूर्णांकerrupt_set_trigger(obj->swp,
					QBMAN_SWP_INTERRUPT_DQRI);
	qbman_swp_पूर्णांकerrupt_clear_status(obj->swp, 0xffffffff);
	अगर (obj->dpio_desc.receives_notअगरications)
		qbman_swp_push_set(obj->swp, 0, 1);

	spin_lock(&dpio_list_lock);
	list_add_tail(&obj->node, &dpio_list);
	अगर (desc->cpu >= 0 && !dpio_by_cpu[desc->cpu])
		dpio_by_cpu[desc->cpu] = obj;
	spin_unlock(&dpio_list_lock);

	obj->dev = dev;

	वापस obj;
पूर्ण

/**
 * dpaa2_io_करोwn() - release the dpaa2_io object.
 * @d: the dpaa2_io object to be released.
 *
 * The "struct dpaa2_io" type can represent an inभागidual DPIO object (as
 * described by "struct dpaa2_io_desc") or an instance of a "DPIO service",
 * which can be used to group/encapsulate multiple DPIO objects. In all हालs,
 * each handle obtained should be released using this function.
 */
व्योम dpaa2_io_करोwn(काष्ठा dpaa2_io *d)
अणु
	spin_lock(&dpio_list_lock);
	dpio_by_cpu[d->dpio_desc.cpu] = शून्य;
	list_del(&d->node);
	spin_unlock(&dpio_list_lock);

	kमुक्त(d);
पूर्ण

#घोषणा DPAA_POLL_MAX 32

/**
 * dpaa2_io_irq() - ISR क्रम DPIO पूर्णांकerrupts
 *
 * @obj: the given DPIO object.
 *
 * Return IRQ_HANDLED क्रम success or IRQ_NONE अगर there
 * were no pending पूर्णांकerrupts.
 */
irqवापस_t dpaa2_io_irq(काष्ठा dpaa2_io *obj)
अणु
	स्थिर काष्ठा dpaa2_dq *dq;
	पूर्णांक max = 0;
	काष्ठा qbman_swp *swp;
	u32 status;

	swp = obj->swp;
	status = qbman_swp_पूर्णांकerrupt_पढ़ो_status(swp);
	अगर (!status)
		वापस IRQ_NONE;

	dq = qbman_swp_dqrr_next(swp);
	जबतक (dq) अणु
		अगर (qbman_result_is_SCN(dq)) अणु
			काष्ठा dpaa2_io_notअगरication_ctx *ctx;
			u64 q64;

			q64 = qbman_result_SCN_ctx(dq);
			ctx = (व्योम *)(uपूर्णांकptr_t)q64;
			ctx->cb(ctx);
		पूर्ण अन्यथा अणु
			pr_crit("fsl-mc-dpio: Unrecognised/ignored DQRR entry\n");
		पूर्ण
		qbman_swp_dqrr_consume(swp, dq);
		++max;
		अगर (max > DPAA_POLL_MAX)
			जाओ करोne;
		dq = qbman_swp_dqrr_next(swp);
	पूर्ण
करोne:
	qbman_swp_पूर्णांकerrupt_clear_status(swp, status);
	qbman_swp_पूर्णांकerrupt_set_inhibit(swp, 0);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * dpaa2_io_get_cpu() - get the cpu associated with a given DPIO object
 *
 * @d: the given DPIO object.
 *
 * Return the cpu associated with the DPIO object
 */
पूर्णांक dpaa2_io_get_cpu(काष्ठा dpaa2_io *d)
अणु
	वापस d->dpio_desc.cpu;
पूर्ण
EXPORT_SYMBOL(dpaa2_io_get_cpu);

/**
 * dpaa2_io_service_रेजिस्टर() - Prepare क्रम servicing of FQDAN or CDAN
 *                               notअगरications on the given DPIO service.
 * @d:   the given DPIO service.
 * @ctx: the notअगरication context.
 * @dev: the device that requests the रेजिस्टर
 *
 * The caller should make the MC command to attach a DPAA2 object to
 * a DPIO after this function completes successfully.  In that way:
 *    (a) The DPIO service is "ready" to handle a notअगरication arrival
 *        (which might happen beक्रमe the "attach" command to MC has
 *        वापसed control of execution back to the caller)
 *    (b) The DPIO service can provide back to the caller the 'dpio_id' and
 *        'qman64' parameters that it should pass aदीर्घ in the MC command
 *        in order क्रम the object to be configured to produce the right
 *        notअगरication fields to the DPIO service.
 *
 * Return 0 क्रम success, or -ENODEV क्रम failure.
 */
पूर्णांक dpaa2_io_service_रेजिस्टर(काष्ठा dpaa2_io *d,
			      काष्ठा dpaa2_io_notअगरication_ctx *ctx,
			      काष्ठा device *dev)
अणु
	काष्ठा device_link *link;
	अचिन्हित दीर्घ irqflags;

	d = service_select_by_cpu(d, ctx->desired_cpu);
	अगर (!d)
		वापस -ENODEV;

	link = device_link_add(dev, d->dev, DL_FLAG_AUTOREMOVE_CONSUMER);
	अगर (!link)
		वापस -EINVAL;

	ctx->dpio_id = d->dpio_desc.dpio_id;
	ctx->qman64 = (u64)(uपूर्णांकptr_t)ctx;
	ctx->dpio_निजी = d;
	spin_lock_irqsave(&d->lock_notअगरications, irqflags);
	list_add(&ctx->node, &d->notअगरications);
	spin_unlock_irqrestore(&d->lock_notअगरications, irqflags);

	/* Enable the generation of CDAN notअगरications */
	अगर (ctx->is_cdan)
		वापस qbman_swp_CDAN_set_context_enable(d->swp,
							 (u16)ctx->id,
							 ctx->qman64);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dpaa2_io_service_रेजिस्टर);

/**
 * dpaa2_io_service_deरेजिस्टर - The opposite of 'register'.
 * @service: the given DPIO service.
 * @ctx: the notअगरication context.
 * @dev: the device that requests to be deरेजिस्टरed
 *
 * This function should be called only after sending the MC command to
 * to detach the notअगरication-producing device from the DPIO.
 */
व्योम dpaa2_io_service_deरेजिस्टर(काष्ठा dpaa2_io *service,
				 काष्ठा dpaa2_io_notअगरication_ctx *ctx,
				 काष्ठा device *dev)
अणु
	काष्ठा dpaa2_io *d = ctx->dpio_निजी;
	अचिन्हित दीर्घ irqflags;

	अगर (ctx->is_cdan)
		qbman_swp_CDAN_disable(d->swp, (u16)ctx->id);

	spin_lock_irqsave(&d->lock_notअगरications, irqflags);
	list_del(&ctx->node);
	spin_unlock_irqrestore(&d->lock_notअगरications, irqflags);

पूर्ण
EXPORT_SYMBOL_GPL(dpaa2_io_service_deरेजिस्टर);

/**
 * dpaa2_io_service_rearm() - Rearm the notअगरication क्रम the given DPIO service.
 * @d: the given DPIO service.
 * @ctx: the notअगरication context.
 *
 * Once a FQDAN/CDAN has been produced, the corresponding FQ/channel is
 * considered "disarmed". Ie. the user can issue pull dequeue operations on that
 * traffic source क्रम as दीर्घ as it likes. Eventually it may wish to "rearm"
 * that source to allow it to produce another FQDAN/CDAN, that's what this
 * function achieves.
 *
 * Return 0 क्रम success.
 */
पूर्णांक dpaa2_io_service_rearm(काष्ठा dpaa2_io *d,
			   काष्ठा dpaa2_io_notअगरication_ctx *ctx)
अणु
	अचिन्हित दीर्घ irqflags;
	पूर्णांक err;

	d = service_select_by_cpu(d, ctx->desired_cpu);
	अगर (!unlikely(d))
		वापस -ENODEV;

	spin_lock_irqsave(&d->lock_mgmt_cmd, irqflags);
	अगर (ctx->is_cdan)
		err = qbman_swp_CDAN_enable(d->swp, (u16)ctx->id);
	अन्यथा
		err = qbman_swp_fq_schedule(d->swp, ctx->id);
	spin_unlock_irqrestore(&d->lock_mgmt_cmd, irqflags);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(dpaa2_io_service_rearm);

/**
 * dpaa2_io_service_pull_fq() - pull dequeue functions from a fq.
 * @d: the given DPIO service.
 * @fqid: the given frame queue id.
 * @s: the dpaa2_io_store object क्रम the result.
 *
 * Return 0 क्रम success, or error code क्रम failure.
 */
पूर्णांक dpaa2_io_service_pull_fq(काष्ठा dpaa2_io *d, u32 fqid,
			     काष्ठा dpaa2_io_store *s)
अणु
	काष्ठा qbman_pull_desc pd;
	पूर्णांक err;

	qbman_pull_desc_clear(&pd);
	qbman_pull_desc_set_storage(&pd, s->vaddr, s->paddr, 1);
	qbman_pull_desc_set_numframes(&pd, (u8)s->max);
	qbman_pull_desc_set_fq(&pd, fqid);

	d = service_select(d);
	अगर (!d)
		वापस -ENODEV;
	s->swp = d->swp;
	err = qbman_swp_pull(d->swp, &pd);
	अगर (err)
		s->swp = शून्य;

	वापस err;
पूर्ण
EXPORT_SYMBOL(dpaa2_io_service_pull_fq);

/**
 * dpaa2_io_service_pull_channel() - pull dequeue functions from a channel.
 * @d: the given DPIO service.
 * @channelid: the given channel id.
 * @s: the dpaa2_io_store object क्रम the result.
 *
 * Return 0 क्रम success, or error code क्रम failure.
 */
पूर्णांक dpaa2_io_service_pull_channel(काष्ठा dpaa2_io *d, u32 channelid,
				  काष्ठा dpaa2_io_store *s)
अणु
	काष्ठा qbman_pull_desc pd;
	पूर्णांक err;

	qbman_pull_desc_clear(&pd);
	qbman_pull_desc_set_storage(&pd, s->vaddr, s->paddr, 1);
	qbman_pull_desc_set_numframes(&pd, (u8)s->max);
	qbman_pull_desc_set_channel(&pd, channelid, qbman_pull_type_prio);

	d = service_select(d);
	अगर (!d)
		वापस -ENODEV;

	s->swp = d->swp;
	err = qbman_swp_pull(d->swp, &pd);
	अगर (err)
		s->swp = शून्य;

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(dpaa2_io_service_pull_channel);

/**
 * dpaa2_io_service_enqueue_fq() - Enqueue a frame to a frame queue.
 * @d: the given DPIO service.
 * @fqid: the given frame queue id.
 * @fd: the frame descriptor which is enqueued.
 *
 * Return 0 क्रम successful enqueue, -EBUSY अगर the enqueue ring is not पढ़ोy,
 * or -ENODEV अगर there is no dpio service.
 */
पूर्णांक dpaa2_io_service_enqueue_fq(काष्ठा dpaa2_io *d,
				u32 fqid,
				स्थिर काष्ठा dpaa2_fd *fd)
अणु
	काष्ठा qbman_eq_desc ed;

	d = service_select(d);
	अगर (!d)
		वापस -ENODEV;

	qbman_eq_desc_clear(&ed);
	qbman_eq_desc_set_no_orp(&ed, 0);
	qbman_eq_desc_set_fq(&ed, fqid);

	वापस qbman_swp_enqueue(d->swp, &ed, fd);
पूर्ण
EXPORT_SYMBOL(dpaa2_io_service_enqueue_fq);

/**
 * dpaa2_io_service_enqueue_multiple_fq() - Enqueue multiple frames
 * to a frame queue using one fqid.
 * @d: the given DPIO service.
 * @fqid: the given frame queue id.
 * @fd: the frame descriptor which is enqueued.
 * @nb: number of frames to be enqueud
 *
 * Return 0 क्रम successful enqueue, -EBUSY अगर the enqueue ring is not पढ़ोy,
 * or -ENODEV अगर there is no dpio service.
 */
पूर्णांक dpaa2_io_service_enqueue_multiple_fq(काष्ठा dpaa2_io *d,
				u32 fqid,
				स्थिर काष्ठा dpaa2_fd *fd,
				पूर्णांक nb)
अणु
	काष्ठा qbman_eq_desc ed;

	d = service_select(d);
	अगर (!d)
		वापस -ENODEV;

	qbman_eq_desc_clear(&ed);
	qbman_eq_desc_set_no_orp(&ed, 0);
	qbman_eq_desc_set_fq(&ed, fqid);

	वापस qbman_swp_enqueue_multiple(d->swp, &ed, fd, 0, nb);
पूर्ण
EXPORT_SYMBOL(dpaa2_io_service_enqueue_multiple_fq);

/**
 * dpaa2_io_service_enqueue_multiple_desc_fq() - Enqueue multiple frames
 * to dअगरferent frame queue using a list of fqids.
 * @d: the given DPIO service.
 * @fqid: the given list of frame queue ids.
 * @fd: the frame descriptor which is enqueued.
 * @nb: number of frames to be enqueud
 *
 * Return 0 क्रम successful enqueue, -EBUSY अगर the enqueue ring is not पढ़ोy,
 * or -ENODEV अगर there is no dpio service.
 */
पूर्णांक dpaa2_io_service_enqueue_multiple_desc_fq(काष्ठा dpaa2_io *d,
				u32 *fqid,
				स्थिर काष्ठा dpaa2_fd *fd,
				पूर्णांक nb)
अणु
	काष्ठा qbman_eq_desc *ed;
	पूर्णांक i, ret;

	ed = kसुस्मृति(माप(काष्ठा qbman_eq_desc), 32, GFP_KERNEL);
	अगर (!ed)
		वापस -ENOMEM;

	d = service_select(d);
	अगर (!d) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < nb; i++) अणु
		qbman_eq_desc_clear(&ed[i]);
		qbman_eq_desc_set_no_orp(&ed[i], 0);
		qbman_eq_desc_set_fq(&ed[i], fqid[i]);
	पूर्ण

	ret = qbman_swp_enqueue_multiple_desc(d->swp, &ed[0], fd, nb);
out:
	kमुक्त(ed);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dpaa2_io_service_enqueue_multiple_desc_fq);

/**
 * dpaa2_io_service_enqueue_qd() - Enqueue a frame to a QD.
 * @d: the given DPIO service.
 * @qdid: the given queuing destination id.
 * @prio: the given queuing priority.
 * @qdbin: the given queuing destination bin.
 * @fd: the frame descriptor which is enqueued.
 *
 * Return 0 क्रम successful enqueue, or -EBUSY अगर the enqueue ring is not पढ़ोy,
 * or -ENODEV अगर there is no dpio service.
 */
पूर्णांक dpaa2_io_service_enqueue_qd(काष्ठा dpaa2_io *d,
				u32 qdid, u8 prio, u16 qdbin,
				स्थिर काष्ठा dpaa2_fd *fd)
अणु
	काष्ठा qbman_eq_desc ed;

	d = service_select(d);
	अगर (!d)
		वापस -ENODEV;

	qbman_eq_desc_clear(&ed);
	qbman_eq_desc_set_no_orp(&ed, 0);
	qbman_eq_desc_set_qd(&ed, qdid, qdbin, prio);

	वापस qbman_swp_enqueue(d->swp, &ed, fd);
पूर्ण
EXPORT_SYMBOL_GPL(dpaa2_io_service_enqueue_qd);

/**
 * dpaa2_io_service_release() - Release buffers to a buffer pool.
 * @d: the given DPIO object.
 * @bpid: the buffer pool id.
 * @buffers: the buffers to be released.
 * @num_buffers: the number of the buffers to be released.
 *
 * Return 0 क्रम success, and negative error code क्रम failure.
 */
पूर्णांक dpaa2_io_service_release(काष्ठा dpaa2_io *d,
			     u16 bpid,
			     स्थिर u64 *buffers,
			     अचिन्हित पूर्णांक num_buffers)
अणु
	काष्ठा qbman_release_desc rd;

	d = service_select(d);
	अगर (!d)
		वापस -ENODEV;

	qbman_release_desc_clear(&rd);
	qbman_release_desc_set_bpid(&rd, bpid);

	वापस qbman_swp_release(d->swp, &rd, buffers, num_buffers);
पूर्ण
EXPORT_SYMBOL_GPL(dpaa2_io_service_release);

/**
 * dpaa2_io_service_acquire() - Acquire buffers from a buffer pool.
 * @d: the given DPIO object.
 * @bpid: the buffer pool id.
 * @buffers: the buffer addresses क्रम acquired buffers.
 * @num_buffers: the expected number of the buffers to acquire.
 *
 * Return a negative error code अगर the command failed, otherwise it वापसs
 * the number of buffers acquired, which may be less than the number requested.
 * Eg. अगर the buffer pool is empty, this will वापस zero.
 */
पूर्णांक dpaa2_io_service_acquire(काष्ठा dpaa2_io *d,
			     u16 bpid,
			     u64 *buffers,
			     अचिन्हित पूर्णांक num_buffers)
अणु
	अचिन्हित दीर्घ irqflags;
	पूर्णांक err;

	d = service_select(d);
	अगर (!d)
		वापस -ENODEV;

	spin_lock_irqsave(&d->lock_mgmt_cmd, irqflags);
	err = qbman_swp_acquire(d->swp, bpid, buffers, num_buffers);
	spin_unlock_irqrestore(&d->lock_mgmt_cmd, irqflags);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(dpaa2_io_service_acquire);

/*
 * 'Stores' are reusable memory blocks क्रम holding dequeue results, and to
 * assist with parsing those results.
 */

/**
 * dpaa2_io_store_create() - Create the dma memory storage क्रम dequeue result.
 * @max_frames: the maximum number of dequeued result क्रम frames, must be <= 32.
 * @dev:        the device to allow mapping/unmapping the DMAable region.
 *
 * The size of the storage is "max_frames*sizeof(struct dpaa2_dq)".
 * The 'dpaa2_io_store' वापसed is a DPIO service managed object.
 *
 * Return poपूर्णांकer to dpaa2_io_store काष्ठा क्रम successfully created storage
 * memory, or शून्य on error.
 */
काष्ठा dpaa2_io_store *dpaa2_io_store_create(अचिन्हित पूर्णांक max_frames,
					     काष्ठा device *dev)
अणु
	काष्ठा dpaa2_io_store *ret;
	माप_प्रकार size;

	अगर (!max_frames || (max_frames > 32))
		वापस शून्य;

	ret = kदो_स्मृति(माप(*ret), GFP_KERNEL);
	अगर (!ret)
		वापस शून्य;

	ret->max = max_frames;
	size = max_frames * माप(काष्ठा dpaa2_dq) + 64;
	ret->alloced_addr = kzalloc(size, GFP_KERNEL);
	अगर (!ret->alloced_addr) अणु
		kमुक्त(ret);
		वापस शून्य;
	पूर्ण

	ret->vaddr = PTR_ALIGN(ret->alloced_addr, 64);
	ret->paddr = dma_map_single(dev, ret->vaddr,
				    माप(काष्ठा dpaa2_dq) * max_frames,
				    DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, ret->paddr)) अणु
		kमुक्त(ret->alloced_addr);
		kमुक्त(ret);
		वापस शून्य;
	पूर्ण

	ret->idx = 0;
	ret->dev = dev;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dpaa2_io_store_create);

/**
 * dpaa2_io_store_destroy() - Frees the dma memory storage क्रम dequeue
 *                            result.
 * @s: the storage memory to be destroyed.
 */
व्योम dpaa2_io_store_destroy(काष्ठा dpaa2_io_store *s)
अणु
	dma_unmap_single(s->dev, s->paddr, माप(काष्ठा dpaa2_dq) * s->max,
			 DMA_FROM_DEVICE);
	kमुक्त(s->alloced_addr);
	kमुक्त(s);
पूर्ण
EXPORT_SYMBOL_GPL(dpaa2_io_store_destroy);

/**
 * dpaa2_io_store_next() - Determine when the next dequeue result is available.
 * @s: the dpaa2_io_store object.
 * @is_last: indicate whether this is the last frame in the pull command.
 *
 * When an object driver perक्रमms dequeues to a dpaa2_io_store, this function
 * can be used to determine when the next frame result is available. Once
 * this function वापसs non-शून्य, a subsequent call to it will try to find
 * the next dequeue result.
 *
 * Note that अगर a pull-dequeue has a शून्य result because the target FQ/channel
 * was empty, then this function will also वापस शून्य (rather than expecting
 * the caller to always check क्रम this. As such, "is_last" can be used to
 * dअगरferentiate between "end-of-empty-dequeue" and "still-waiting".
 *
 * Return dequeue result क्रम a valid dequeue result, or शून्य क्रम empty dequeue.
 */
काष्ठा dpaa2_dq *dpaa2_io_store_next(काष्ठा dpaa2_io_store *s, पूर्णांक *is_last)
अणु
	पूर्णांक match;
	काष्ठा dpaa2_dq *ret = &s->vaddr[s->idx];

	match = qbman_result_has_new_result(s->swp, ret);
	अगर (!match) अणु
		*is_last = 0;
		वापस शून्य;
	पूर्ण

	s->idx++;

	अगर (dpaa2_dq_is_pull_complete(ret)) अणु
		*is_last = 1;
		s->idx = 0;
		/*
		 * If we get an empty dequeue result to terminate a zero-results
		 * vdqcr, वापस शून्य to the caller rather than expecting him to
		 * check non-शून्य results every समय.
		 */
		अगर (!(dpaa2_dq_flags(ret) & DPAA2_DQ_STAT_VALIDFRAME))
			ret = शून्य;
	पूर्ण अन्यथा अणु
		prefetch(&s->vaddr[s->idx]);
		*is_last = 0;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dpaa2_io_store_next);

/**
 * dpaa2_io_query_fq_count() - Get the frame and byte count क्रम a given fq.
 * @d: the given DPIO object.
 * @fqid: the id of frame queue to be queried.
 * @fcnt: the queried frame count.
 * @bcnt: the queried byte count.
 *
 * Knowing the FQ count at run-समय can be useful in debugging situations.
 * The instantaneous frame- and byte-count are hereby वापसed.
 *
 * Return 0 क्रम a successful query, and negative error code अगर query fails.
 */
पूर्णांक dpaa2_io_query_fq_count(काष्ठा dpaa2_io *d, u32 fqid,
			    u32 *fcnt, u32 *bcnt)
अणु
	काष्ठा qbman_fq_query_np_rslt state;
	काष्ठा qbman_swp *swp;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक ret;

	d = service_select(d);
	अगर (!d)
		वापस -ENODEV;

	swp = d->swp;
	spin_lock_irqsave(&d->lock_mgmt_cmd, irqflags);
	ret = qbman_fq_query_state(swp, fqid, &state);
	spin_unlock_irqrestore(&d->lock_mgmt_cmd, irqflags);
	अगर (ret)
		वापस ret;
	*fcnt = qbman_fq_state_frame_count(&state);
	*bcnt = qbman_fq_state_byte_count(&state);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dpaa2_io_query_fq_count);

/**
 * dpaa2_io_query_bp_count() - Query the number of buffers currently in a
 * buffer pool.
 * @d: the given DPIO object.
 * @bpid: the index of buffer pool to be queried.
 * @num: the queried number of buffers in the buffer pool.
 *
 * Return 0 क्रम a successful query, and negative error code अगर query fails.
 */
पूर्णांक dpaa2_io_query_bp_count(काष्ठा dpaa2_io *d, u16 bpid, u32 *num)
अणु
	काष्ठा qbman_bp_query_rslt state;
	काष्ठा qbman_swp *swp;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक ret;

	d = service_select(d);
	अगर (!d)
		वापस -ENODEV;

	swp = d->swp;
	spin_lock_irqsave(&d->lock_mgmt_cmd, irqflags);
	ret = qbman_bp_query(swp, bpid, &state);
	spin_unlock_irqrestore(&d->lock_mgmt_cmd, irqflags);
	अगर (ret)
		वापस ret;
	*num = qbman_bp_info_num_मुक्त_bufs(&state);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dpaa2_io_query_bp_count);
