<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * VFIO based Physical Subchannel device driver
 *
 * Copyright IBM Corp. 2017
 * Copyright Red Hat, Inc. 2019
 *
 * Author(s): Dong Jia Shi <bjsdjshi@linux.vnet.ibm.com>
 *            Xiao Feng Ren <renxiaof@linux.vnet.ibm.com>
 *            Cornelia Huck <cohuck@redhat.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/uuid.h>
#समावेश <linux/mdev.h>

#समावेश <यंत्र/isc.h>

#समावेश "chp.h"
#समावेश "ioasm.h"
#समावेश "css.h"
#समावेश "vfio_ccw_private.h"

काष्ठा workqueue_काष्ठा *vfio_ccw_work_q;
अटल काष्ठा kmem_cache *vfio_ccw_io_region;
अटल काष्ठा kmem_cache *vfio_ccw_cmd_region;
अटल काष्ठा kmem_cache *vfio_ccw_schib_region;
अटल काष्ठा kmem_cache *vfio_ccw_crw_region;

debug_info_t *vfio_ccw_debug_msg_id;
debug_info_t *vfio_ccw_debug_trace_id;

/*
 * Helpers
 */
पूर्णांक vfio_ccw_sch_quiesce(काष्ठा subchannel *sch)
अणु
	काष्ठा vfio_ccw_निजी *निजी = dev_get_drvdata(&sch->dev);
	DECLARE_COMPLETION_ONSTACK(completion);
	पूर्णांक iretry, ret = 0;

	spin_lock_irq(sch->lock);
	अगर (!sch->schib.pmcw.ena)
		जाओ out_unlock;
	ret = cio_disable_subchannel(sch);
	अगर (ret != -EBUSY)
		जाओ out_unlock;

	iretry = 255;
	करो अणु

		ret = cio_cancel_halt_clear(sch, &iretry);

		अगर (ret == -EIO) अणु
			pr_err("vfio_ccw: could not quiesce subchannel 0.%x.%04x!\n",
			       sch->schid.ssid, sch->schid.sch_no);
			अवरोध;
		पूर्ण

		/*
		 * Flush all I/O and रुको क्रम
		 * cancel/halt/clear completion.
		 */
		निजी->completion = &completion;
		spin_unlock_irq(sch->lock);

		अगर (ret == -EBUSY)
			रुको_क्रम_completion_समयout(&completion, 3*HZ);

		निजी->completion = शून्य;
		flush_workqueue(vfio_ccw_work_q);
		spin_lock_irq(sch->lock);
		ret = cio_disable_subchannel(sch);
	पूर्ण जबतक (ret == -EBUSY);
out_unlock:
	निजी->state = VFIO_CCW_STATE_NOT_OPER;
	spin_unlock_irq(sch->lock);
	वापस ret;
पूर्ण

अटल व्योम vfio_ccw_sch_io_toकरो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vfio_ccw_निजी *निजी;
	काष्ठा irb *irb;
	bool is_final;
	bool cp_is_finished = false;

	निजी = container_of(work, काष्ठा vfio_ccw_निजी, io_work);
	irb = &निजी->irb;

	is_final = !(scsw_actl(&irb->scsw) &
		     (SCSW_ACTL_DEVACT | SCSW_ACTL_SCHACT));
	अगर (scsw_is_solicited(&irb->scsw)) अणु
		cp_update_scsw(&निजी->cp, &irb->scsw);
		अगर (is_final && निजी->state == VFIO_CCW_STATE_CP_PENDING) अणु
			cp_मुक्त(&निजी->cp);
			cp_is_finished = true;
		पूर्ण
	पूर्ण
	mutex_lock(&निजी->io_mutex);
	स_नकल(निजी->io_region->irb_area, irb, माप(*irb));
	mutex_unlock(&निजी->io_mutex);

	/*
	 * Reset to IDLE only अगर processing of a channel program
	 * has finished. Do not overग_लिखो a possible processing
	 * state अगर the final पूर्णांकerrupt was क्रम HSCH or CSCH.
	 */
	अगर (निजी->mdev && cp_is_finished)
		निजी->state = VFIO_CCW_STATE_IDLE;

	अगर (निजी->io_trigger)
		eventfd_संकेत(निजी->io_trigger, 1);
पूर्ण

अटल व्योम vfio_ccw_crw_toकरो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vfio_ccw_निजी *निजी;

	निजी = container_of(work, काष्ठा vfio_ccw_निजी, crw_work);

	अगर (!list_empty(&निजी->crw) && निजी->crw_trigger)
		eventfd_संकेत(निजी->crw_trigger, 1);
पूर्ण

/*
 * Css driver callbacks
 */
अटल व्योम vfio_ccw_sch_irq(काष्ठा subchannel *sch)
अणु
	काष्ठा vfio_ccw_निजी *निजी = dev_get_drvdata(&sch->dev);

	inc_irq_stat(IRQIO_CIO);
	vfio_ccw_fsm_event(निजी, VFIO_CCW_EVENT_INTERRUPT);
पूर्ण

अटल व्योम vfio_ccw_मुक्त_regions(काष्ठा vfio_ccw_निजी *निजी)
अणु
	अगर (निजी->crw_region)
		kmem_cache_मुक्त(vfio_ccw_crw_region, निजी->crw_region);
	अगर (निजी->schib_region)
		kmem_cache_मुक्त(vfio_ccw_schib_region, निजी->schib_region);
	अगर (निजी->cmd_region)
		kmem_cache_मुक्त(vfio_ccw_cmd_region, निजी->cmd_region);
	अगर (निजी->io_region)
		kmem_cache_मुक्त(vfio_ccw_io_region, निजी->io_region);
पूर्ण

अटल पूर्णांक vfio_ccw_sch_probe(काष्ठा subchannel *sch)
अणु
	काष्ठा pmcw *pmcw = &sch->schib.pmcw;
	काष्ठा vfio_ccw_निजी *निजी;
	पूर्णांक ret = -ENOMEM;

	अगर (pmcw->qf) अणु
		dev_warn(&sch->dev, "vfio: ccw: does not support QDIO: %s\n",
			 dev_name(&sch->dev));
		वापस -ENODEV;
	पूर्ण

	निजी = kzalloc(माप(*निजी), GFP_KERNEL | GFP_DMA);
	अगर (!निजी)
		वापस -ENOMEM;

	निजी->cp.guest_cp = kसुस्मृति(CCWCHAIN_LEN_MAX, माप(काष्ठा ccw1),
				       GFP_KERNEL);
	अगर (!निजी->cp.guest_cp)
		जाओ out_मुक्त;

	निजी->io_region = kmem_cache_zalloc(vfio_ccw_io_region,
					       GFP_KERNEL | GFP_DMA);
	अगर (!निजी->io_region)
		जाओ out_मुक्त;

	निजी->cmd_region = kmem_cache_zalloc(vfio_ccw_cmd_region,
						GFP_KERNEL | GFP_DMA);
	अगर (!निजी->cmd_region)
		जाओ out_मुक्त;

	निजी->schib_region = kmem_cache_zalloc(vfio_ccw_schib_region,
						  GFP_KERNEL | GFP_DMA);

	अगर (!निजी->schib_region)
		जाओ out_मुक्त;

	निजी->crw_region = kmem_cache_zalloc(vfio_ccw_crw_region,
						GFP_KERNEL | GFP_DMA);

	अगर (!निजी->crw_region)
		जाओ out_मुक्त;

	निजी->sch = sch;
	dev_set_drvdata(&sch->dev, निजी);
	mutex_init(&निजी->io_mutex);

	spin_lock_irq(sch->lock);
	निजी->state = VFIO_CCW_STATE_NOT_OPER;
	sch->isc = VFIO_CCW_ISC;
	ret = cio_enable_subchannel(sch, (u32)(अचिन्हित दीर्घ)sch);
	spin_unlock_irq(sch->lock);
	अगर (ret)
		जाओ out_मुक्त;

	INIT_LIST_HEAD(&निजी->crw);
	INIT_WORK(&निजी->io_work, vfio_ccw_sch_io_toकरो);
	INIT_WORK(&निजी->crw_work, vfio_ccw_crw_toकरो);
	atomic_set(&निजी->avail, 1);
	निजी->state = VFIO_CCW_STATE_STANDBY;

	ret = vfio_ccw_mdev_reg(sch);
	अगर (ret)
		जाओ out_disable;

	अगर (dev_get_uevent_suppress(&sch->dev)) अणु
		dev_set_uevent_suppress(&sch->dev, 0);
		kobject_uevent(&sch->dev.kobj, KOBJ_ADD);
	पूर्ण

	VFIO_CCW_MSG_EVENT(4, "bound to subchannel %x.%x.%04x\n",
			   sch->schid.cssid, sch->schid.ssid,
			   sch->schid.sch_no);
	वापस 0;

out_disable:
	cio_disable_subchannel(sch);
out_मुक्त:
	dev_set_drvdata(&sch->dev, शून्य);
	vfio_ccw_मुक्त_regions(निजी);
	kमुक्त(निजी->cp.guest_cp);
	kमुक्त(निजी);
	वापस ret;
पूर्ण

अटल पूर्णांक vfio_ccw_sch_हटाओ(काष्ठा subchannel *sch)
अणु
	काष्ठा vfio_ccw_निजी *निजी = dev_get_drvdata(&sch->dev);
	काष्ठा vfio_ccw_crw *crw, *temp;

	vfio_ccw_sch_quiesce(sch);

	list_क्रम_each_entry_safe(crw, temp, &निजी->crw, next) अणु
		list_del(&crw->next);
		kमुक्त(crw);
	पूर्ण

	vfio_ccw_mdev_unreg(sch);

	dev_set_drvdata(&sch->dev, शून्य);

	vfio_ccw_मुक्त_regions(निजी);
	kमुक्त(निजी->cp.guest_cp);
	kमुक्त(निजी);

	VFIO_CCW_MSG_EVENT(4, "unbound from subchannel %x.%x.%04x\n",
			   sch->schid.cssid, sch->schid.ssid,
			   sch->schid.sch_no);
	वापस 0;
पूर्ण

अटल व्योम vfio_ccw_sch_shutकरोwn(काष्ठा subchannel *sch)
अणु
	vfio_ccw_sch_quiesce(sch);
पूर्ण

/**
 * vfio_ccw_sch_event - process subchannel event
 * @sch: subchannel
 * @process: non-zero अगर function is called in process context
 *
 * An unspecअगरied event occurred क्रम this subchannel. Adjust data according
 * to the current operational state of the subchannel. Return zero when the
 * event has been handled sufficiently or -EAGAIN when this function should
 * be called again in process context.
 */
अटल पूर्णांक vfio_ccw_sch_event(काष्ठा subchannel *sch, पूर्णांक process)
अणु
	काष्ठा vfio_ccw_निजी *निजी = dev_get_drvdata(&sch->dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = -EAGAIN;

	spin_lock_irqsave(sch->lock, flags);
	अगर (!device_is_रेजिस्टरed(&sch->dev))
		जाओ out_unlock;

	अगर (work_pending(&sch->toकरो_work))
		जाओ out_unlock;

	अगर (cio_update_schib(sch)) अणु
		vfio_ccw_fsm_event(निजी, VFIO_CCW_EVENT_NOT_OPER);
		rc = 0;
		जाओ out_unlock;
	पूर्ण

	निजी = dev_get_drvdata(&sch->dev);
	अगर (निजी->state == VFIO_CCW_STATE_NOT_OPER) अणु
		निजी->state = निजी->mdev ? VFIO_CCW_STATE_IDLE :
				 VFIO_CCW_STATE_STANDBY;
	पूर्ण
	rc = 0;

out_unlock:
	spin_unlock_irqrestore(sch->lock, flags);

	वापस rc;
पूर्ण

अटल व्योम vfio_ccw_queue_crw(काष्ठा vfio_ccw_निजी *निजी,
			       अचिन्हित पूर्णांक rsc,
			       अचिन्हित पूर्णांक erc,
			       अचिन्हित पूर्णांक rsid)
अणु
	काष्ठा vfio_ccw_crw *crw;

	/*
	 * If unable to allocate a CRW, just drop the event and
	 * carry on.  The guest will either see a later one or
	 * learn when it issues its own store subchannel.
	 */
	crw = kzalloc(माप(*crw), GFP_ATOMIC);
	अगर (!crw)
		वापस;

	/*
	 * Build the CRW based on the inमाला_दो given to us.
	 */
	crw->crw.rsc = rsc;
	crw->crw.erc = erc;
	crw->crw.rsid = rsid;

	list_add_tail(&crw->next, &निजी->crw);
	queue_work(vfio_ccw_work_q, &निजी->crw_work);
पूर्ण

अटल पूर्णांक vfio_ccw_chp_event(काष्ठा subchannel *sch,
			      काष्ठा chp_link *link, पूर्णांक event)
अणु
	काष्ठा vfio_ccw_निजी *निजी = dev_get_drvdata(&sch->dev);
	पूर्णांक mask = chp_ssd_get_mask(&sch->ssd_info, link);
	पूर्णांक retry = 255;

	अगर (!निजी || !mask)
		वापस 0;

	trace_vfio_ccw_chp_event(निजी->sch->schid, mask, event);
	VFIO_CCW_MSG_EVENT(2, "%pUl (%x.%x.%04x): mask=0x%x event=%d\n",
			   mdev_uuid(निजी->mdev), sch->schid.cssid,
			   sch->schid.ssid, sch->schid.sch_no,
			   mask, event);

	अगर (cio_update_schib(sch))
		वापस -ENODEV;

	चयन (event) अणु
	हाल CHP_VARY_OFF:
		/* Path logically turned off */
		sch->opm &= ~mask;
		sch->lpm &= ~mask;
		अगर (sch->schib.pmcw.lpum & mask)
			cio_cancel_halt_clear(sch, &retry);
		अवरोध;
	हाल CHP_OFFLINE:
		/* Path is gone */
		अगर (sch->schib.pmcw.lpum & mask)
			cio_cancel_halt_clear(sch, &retry);
		vfio_ccw_queue_crw(निजी, CRW_RSC_CPATH, CRW_ERC_PERRN,
				   link->chpid.id);
		अवरोध;
	हाल CHP_VARY_ON:
		/* Path logically turned on */
		sch->opm |= mask;
		sch->lpm |= mask;
		अवरोध;
	हाल CHP_ONLINE:
		/* Path became available */
		sch->lpm |= mask & sch->opm;
		vfio_ccw_queue_crw(निजी, CRW_RSC_CPATH, CRW_ERC_INIT,
				   link->chpid.id);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा css_device_id vfio_ccw_sch_ids[] = अणु
	अणु .match_flags = 0x1, .type = SUBCHANNEL_TYPE_IO, पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(css, vfio_ccw_sch_ids);

अटल काष्ठा css_driver vfio_ccw_sch_driver = अणु
	.drv = अणु
		.name = "vfio_ccw",
		.owner = THIS_MODULE,
	पूर्ण,
	.subchannel_type = vfio_ccw_sch_ids,
	.irq = vfio_ccw_sch_irq,
	.probe = vfio_ccw_sch_probe,
	.हटाओ = vfio_ccw_sch_हटाओ,
	.shutकरोwn = vfio_ccw_sch_shutकरोwn,
	.sch_event = vfio_ccw_sch_event,
	.chp_event = vfio_ccw_chp_event,
पूर्ण;

अटल पूर्णांक __init vfio_ccw_debug_init(व्योम)
अणु
	vfio_ccw_debug_msg_id = debug_रेजिस्टर("vfio_ccw_msg", 16, 1,
					       11 * माप(दीर्घ));
	अगर (!vfio_ccw_debug_msg_id)
		जाओ out_unरेजिस्टर;
	debug_रेजिस्टर_view(vfio_ccw_debug_msg_id, &debug_प्र_लिखो_view);
	debug_set_level(vfio_ccw_debug_msg_id, 2);
	vfio_ccw_debug_trace_id = debug_रेजिस्टर("vfio_ccw_trace", 16, 1, 16);
	अगर (!vfio_ccw_debug_trace_id)
		जाओ out_unरेजिस्टर;
	debug_रेजिस्टर_view(vfio_ccw_debug_trace_id, &debug_hex_ascii_view);
	debug_set_level(vfio_ccw_debug_trace_id, 2);
	वापस 0;

out_unरेजिस्टर:
	debug_unरेजिस्टर(vfio_ccw_debug_msg_id);
	debug_unरेजिस्टर(vfio_ccw_debug_trace_id);
	वापस -1;
पूर्ण

अटल व्योम vfio_ccw_debug_निकास(व्योम)
अणु
	debug_unरेजिस्टर(vfio_ccw_debug_msg_id);
	debug_unरेजिस्टर(vfio_ccw_debug_trace_id);
पूर्ण

अटल व्योम vfio_ccw_destroy_regions(व्योम)
अणु
	kmem_cache_destroy(vfio_ccw_crw_region);
	kmem_cache_destroy(vfio_ccw_schib_region);
	kmem_cache_destroy(vfio_ccw_cmd_region);
	kmem_cache_destroy(vfio_ccw_io_region);
पूर्ण

अटल पूर्णांक __init vfio_ccw_sch_init(व्योम)
अणु
	पूर्णांक ret;

	ret = vfio_ccw_debug_init();
	अगर (ret)
		वापस ret;

	vfio_ccw_work_q = create_singlethपढ़ो_workqueue("vfio-ccw");
	अगर (!vfio_ccw_work_q) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	vfio_ccw_io_region = kmem_cache_create_usercopy("vfio_ccw_io_region",
					माप(काष्ठा ccw_io_region), 0,
					SLAB_ACCOUNT, 0,
					माप(काष्ठा ccw_io_region), शून्य);
	अगर (!vfio_ccw_io_region) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	vfio_ccw_cmd_region = kmem_cache_create_usercopy("vfio_ccw_cmd_region",
					माप(काष्ठा ccw_cmd_region), 0,
					SLAB_ACCOUNT, 0,
					माप(काष्ठा ccw_cmd_region), शून्य);
	अगर (!vfio_ccw_cmd_region) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	vfio_ccw_schib_region = kmem_cache_create_usercopy("vfio_ccw_schib_region",
					माप(काष्ठा ccw_schib_region), 0,
					SLAB_ACCOUNT, 0,
					माप(काष्ठा ccw_schib_region), शून्य);

	अगर (!vfio_ccw_schib_region) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	vfio_ccw_crw_region = kmem_cache_create_usercopy("vfio_ccw_crw_region",
					माप(काष्ठा ccw_crw_region), 0,
					SLAB_ACCOUNT, 0,
					माप(काष्ठा ccw_crw_region), शून्य);

	अगर (!vfio_ccw_crw_region) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	isc_रेजिस्टर(VFIO_CCW_ISC);
	ret = css_driver_रेजिस्टर(&vfio_ccw_sch_driver);
	अगर (ret) अणु
		isc_unरेजिस्टर(VFIO_CCW_ISC);
		जाओ out_err;
	पूर्ण

	वापस ret;

out_err:
	vfio_ccw_destroy_regions();
	destroy_workqueue(vfio_ccw_work_q);
	vfio_ccw_debug_निकास();
	वापस ret;
पूर्ण

अटल व्योम __निकास vfio_ccw_sch_निकास(व्योम)
अणु
	css_driver_unरेजिस्टर(&vfio_ccw_sch_driver);
	isc_unरेजिस्टर(VFIO_CCW_ISC);
	vfio_ccw_destroy_regions();
	destroy_workqueue(vfio_ccw_work_q);
	vfio_ccw_debug_निकास();
पूर्ण
module_init(vfio_ccw_sch_init);
module_निकास(vfio_ccw_sch_निकास);

MODULE_LICENSE("GPL v2");
