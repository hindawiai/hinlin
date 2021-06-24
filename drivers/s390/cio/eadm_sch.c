<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम s390 eadm subchannels
 *
 * Copyright IBM Corp. 2012
 * Author(s): Sebastian Ott <sebott@linux.vnet.ibm.com>
 */

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/completion.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>

#समावेश <यंत्र/css_अक्षरs.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/isc.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/scsw.h>
#समावेश <यंत्र/eadm.h>

#समावेश "eadm_sch.h"
#समावेश "ioasm.h"
#समावेश "cio.h"
#समावेश "css.h"
#समावेश "orb.h"

MODULE_DESCRIPTION("driver for s390 eadm subchannels");
MODULE_LICENSE("GPL");

#घोषणा EADM_TIMEOUT (7 * HZ)
अटल DEFINE_SPINLOCK(list_lock);
अटल LIST_HEAD(eadm_list);

अटल debug_info_t *eadm_debug;

#घोषणा EADM_LOG(imp, txt) करो अणु					\
		debug_text_event(eadm_debug, imp, txt);		\
	पूर्ण जबतक (0)

अटल व्योम EADM_LOG_HEX(पूर्णांक level, व्योम *data, पूर्णांक length)
अणु
	debug_event(eadm_debug, level, data, length);
पूर्ण

अटल व्योम orb_init(जोड़ orb *orb)
अणु
	स_रखो(orb, 0, माप(जोड़ orb));
	orb->eadm.compat1 = 1;
	orb->eadm.compat2 = 1;
	orb->eadm.fmt = 1;
	orb->eadm.x = 1;
पूर्ण

अटल पूर्णांक eadm_subchannel_start(काष्ठा subchannel *sch, काष्ठा aob *aob)
अणु
	जोड़ orb *orb = &get_eadm_निजी(sch)->orb;
	पूर्णांक cc;

	orb_init(orb);
	orb->eadm.aob = (u32)__pa(aob);
	orb->eadm.पूर्णांकparm = (u32)(addr_t)sch;
	orb->eadm.key = PAGE_DEFAULT_KEY >> 4;

	EADM_LOG(6, "start");
	EADM_LOG_HEX(6, &sch->schid, माप(sch->schid));

	cc = ssch(sch->schid, orb);
	चयन (cc) अणु
	हाल 0:
		sch->schib.scsw.eadm.actl |= SCSW_ACTL_START_PEND;
		अवरोध;
	हाल 1:		/* status pending */
	हाल 2:		/* busy */
		वापस -EBUSY;
	हाल 3:		/* not operational */
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक eadm_subchannel_clear(काष्ठा subchannel *sch)
अणु
	पूर्णांक cc;

	cc = csch(sch->schid);
	अगर (cc)
		वापस -ENODEV;

	sch->schib.scsw.eadm.actl |= SCSW_ACTL_CLEAR_PEND;
	वापस 0;
पूर्ण

अटल व्योम eadm_subchannel_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा eadm_निजी *निजी = from_समयr(निजी, t, समयr);
	काष्ठा subchannel *sch = निजी->sch;

	spin_lock_irq(sch->lock);
	EADM_LOG(1, "timeout");
	EADM_LOG_HEX(1, &sch->schid, माप(sch->schid));
	अगर (eadm_subchannel_clear(sch))
		EADM_LOG(0, "clear failed");
	spin_unlock_irq(sch->lock);
पूर्ण

अटल व्योम eadm_subchannel_set_समयout(काष्ठा subchannel *sch, पूर्णांक expires)
अणु
	काष्ठा eadm_निजी *निजी = get_eadm_निजी(sch);

	अगर (expires == 0) अणु
		del_समयr(&निजी->समयr);
		वापस;
	पूर्ण
	अगर (समयr_pending(&निजी->समयr)) अणु
		अगर (mod_समयr(&निजी->समयr, jअगरfies + expires))
			वापस;
	पूर्ण
	निजी->समयr.expires = jअगरfies + expires;
	add_समयr(&निजी->समयr);
पूर्ण

अटल व्योम eadm_subchannel_irq(काष्ठा subchannel *sch)
अणु
	काष्ठा eadm_निजी *निजी = get_eadm_निजी(sch);
	काष्ठा eadm_scsw *scsw = &sch->schib.scsw.eadm;
	काष्ठा irb *irb = this_cpu_ptr(&cio_irb);
	blk_status_t error = BLK_STS_OK;

	EADM_LOG(6, "irq");
	EADM_LOG_HEX(6, irb, माप(*irb));

	inc_irq_stat(IRQIO_ADM);

	अगर ((scsw->stctl & (SCSW_STCTL_ALERT_STATUS | SCSW_STCTL_STATUS_PEND))
	    && scsw->eswf == 1 && irb->esw.eadm.erw.r)
		error = BLK_STS_IOERR;

	अगर (scsw->fctl & SCSW_FCTL_CLEAR_FUNC)
		error = BLK_STS_TIMEOUT;

	eadm_subchannel_set_समयout(sch, 0);

	अगर (निजी->state != EADM_BUSY) अणु
		EADM_LOG(1, "irq unsol");
		EADM_LOG_HEX(1, irb, माप(*irb));
		निजी->state = EADM_NOT_OPER;
		css_sched_sch_toकरो(sch, SCH_TODO_EVAL);
		वापस;
	पूर्ण
	scm_irq_handler((काष्ठा aob *)(अचिन्हित दीर्घ)scsw->aob, error);
	निजी->state = EADM_IDLE;

	अगर (निजी->completion)
		complete(निजी->completion);
पूर्ण

अटल काष्ठा subchannel *eadm_get_idle_sch(व्योम)
अणु
	काष्ठा eadm_निजी *निजी;
	काष्ठा subchannel *sch;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&list_lock, flags);
	list_क्रम_each_entry(निजी, &eadm_list, head) अणु
		sch = निजी->sch;
		spin_lock(sch->lock);
		अगर (निजी->state == EADM_IDLE) अणु
			निजी->state = EADM_BUSY;
			list_move_tail(&निजी->head, &eadm_list);
			spin_unlock(sch->lock);
			spin_unlock_irqrestore(&list_lock, flags);

			वापस sch;
		पूर्ण
		spin_unlock(sch->lock);
	पूर्ण
	spin_unlock_irqrestore(&list_lock, flags);

	वापस शून्य;
पूर्ण

पूर्णांक eadm_start_aob(काष्ठा aob *aob)
अणु
	काष्ठा eadm_निजी *निजी;
	काष्ठा subchannel *sch;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	sch = eadm_get_idle_sch();
	अगर (!sch)
		वापस -EBUSY;

	spin_lock_irqsave(sch->lock, flags);
	eadm_subchannel_set_समयout(sch, EADM_TIMEOUT);
	ret = eadm_subchannel_start(sch, aob);
	अगर (!ret)
		जाओ out_unlock;

	/* Handle start subchannel failure. */
	eadm_subchannel_set_समयout(sch, 0);
	निजी = get_eadm_निजी(sch);
	निजी->state = EADM_NOT_OPER;
	css_sched_sch_toकरो(sch, SCH_TODO_EVAL);

out_unlock:
	spin_unlock_irqrestore(sch->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(eadm_start_aob);

अटल पूर्णांक eadm_subchannel_probe(काष्ठा subchannel *sch)
अणु
	काष्ठा eadm_निजी *निजी;
	पूर्णांक ret;

	निजी = kzalloc(माप(*निजी), GFP_KERNEL | GFP_DMA);
	अगर (!निजी)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&निजी->head);
	समयr_setup(&निजी->समयr, eadm_subchannel_समयout, 0);

	spin_lock_irq(sch->lock);
	set_eadm_निजी(sch, निजी);
	निजी->state = EADM_IDLE;
	निजी->sch = sch;
	sch->isc = EADM_SCH_ISC;
	ret = cio_enable_subchannel(sch, (u32)(अचिन्हित दीर्घ)sch);
	अगर (ret) अणु
		set_eadm_निजी(sch, शून्य);
		spin_unlock_irq(sch->lock);
		kमुक्त(निजी);
		जाओ out;
	पूर्ण
	spin_unlock_irq(sch->lock);

	spin_lock_irq(&list_lock);
	list_add(&निजी->head, &eadm_list);
	spin_unlock_irq(&list_lock);

	अगर (dev_get_uevent_suppress(&sch->dev)) अणु
		dev_set_uevent_suppress(&sch->dev, 0);
		kobject_uevent(&sch->dev.kobj, KOBJ_ADD);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल व्योम eadm_quiesce(काष्ठा subchannel *sch)
अणु
	काष्ठा eadm_निजी *निजी = get_eadm_निजी(sch);
	DECLARE_COMPLETION_ONSTACK(completion);
	पूर्णांक ret;

	spin_lock_irq(sch->lock);
	अगर (निजी->state != EADM_BUSY)
		जाओ disable;

	अगर (eadm_subchannel_clear(sch))
		जाओ disable;

	निजी->completion = &completion;
	spin_unlock_irq(sch->lock);

	रुको_क्रम_completion_io(&completion);

	spin_lock_irq(sch->lock);
	निजी->completion = शून्य;

disable:
	eadm_subchannel_set_समयout(sch, 0);
	करो अणु
		ret = cio_disable_subchannel(sch);
	पूर्ण जबतक (ret == -EBUSY);

	spin_unlock_irq(sch->lock);
पूर्ण

अटल पूर्णांक eadm_subchannel_हटाओ(काष्ठा subchannel *sch)
अणु
	काष्ठा eadm_निजी *निजी = get_eadm_निजी(sch);

	spin_lock_irq(&list_lock);
	list_del(&निजी->head);
	spin_unlock_irq(&list_lock);

	eadm_quiesce(sch);

	spin_lock_irq(sch->lock);
	set_eadm_निजी(sch, शून्य);
	spin_unlock_irq(sch->lock);

	kमुक्त(निजी);

	वापस 0;
पूर्ण

अटल व्योम eadm_subchannel_shutकरोwn(काष्ठा subchannel *sch)
अणु
	eadm_quiesce(sch);
पूर्ण

/**
 * eadm_subchannel_sch_event - process subchannel event
 * @sch: subchannel
 * @process: non-zero अगर function is called in process context
 *
 * An unspecअगरied event occurred क्रम this subchannel. Adjust data according
 * to the current operational state of the subchannel. Return zero when the
 * event has been handled sufficiently or -EAGAIN when this function should
 * be called again in process context.
 */
अटल पूर्णांक eadm_subchannel_sch_event(काष्ठा subchannel *sch, पूर्णांक process)
अणु
	काष्ठा eadm_निजी *निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(sch->lock, flags);
	अगर (!device_is_रेजिस्टरed(&sch->dev))
		जाओ out_unlock;

	अगर (work_pending(&sch->toकरो_work))
		जाओ out_unlock;

	अगर (cio_update_schib(sch)) अणु
		css_sched_sch_toकरो(sch, SCH_TODO_UNREG);
		जाओ out_unlock;
	पूर्ण
	निजी = get_eadm_निजी(sch);
	अगर (निजी->state == EADM_NOT_OPER)
		निजी->state = EADM_IDLE;

out_unlock:
	spin_unlock_irqrestore(sch->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा css_device_id eadm_subchannel_ids[] = अणु
	अणु .match_flags = 0x1, .type = SUBCHANNEL_TYPE_ADM, पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(css, eadm_subchannel_ids);

अटल काष्ठा css_driver eadm_subchannel_driver = अणु
	.drv = अणु
		.name = "eadm_subchannel",
		.owner = THIS_MODULE,
	पूर्ण,
	.subchannel_type = eadm_subchannel_ids,
	.irq = eadm_subchannel_irq,
	.probe = eadm_subchannel_probe,
	.हटाओ = eadm_subchannel_हटाओ,
	.shutकरोwn = eadm_subchannel_shutकरोwn,
	.sch_event = eadm_subchannel_sch_event,
पूर्ण;

अटल पूर्णांक __init eadm_sch_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!css_general_अक्षरacteristics.eadm)
		वापस -ENXIO;

	eadm_debug = debug_रेजिस्टर("eadm_log", 16, 1, 16);
	अगर (!eadm_debug)
		वापस -ENOMEM;

	debug_रेजिस्टर_view(eadm_debug, &debug_hex_ascii_view);
	debug_set_level(eadm_debug, 2);

	isc_रेजिस्टर(EADM_SCH_ISC);
	ret = css_driver_रेजिस्टर(&eadm_subchannel_driver);
	अगर (ret)
		जाओ cleanup;

	वापस ret;

cleanup:
	isc_unरेजिस्टर(EADM_SCH_ISC);
	debug_unरेजिस्टर(eadm_debug);
	वापस ret;
पूर्ण

अटल व्योम __निकास eadm_sch_निकास(व्योम)
अणु
	css_driver_unरेजिस्टर(&eadm_subchannel_driver);
	isc_unरेजिस्टर(EADM_SCH_ISC);
	debug_unरेजिस्टर(eadm_debug);
पूर्ण
module_init(eadm_sch_init);
module_निकास(eadm_sch_निकास);
