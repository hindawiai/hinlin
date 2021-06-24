<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Implementation of the Xen vTPM device frontend
 *
 * Author:  Daniel De Graaf <dgdegra@tycho.nsa.gov>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <xen/xen.h>
#समावेश <xen/events.h>
#समावेश <xen/पूर्णांकerface/io/tpmअगर.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/page.h>
#समावेश "tpm.h"
#समावेश <xen/platक्रमm_pci.h>

काष्ठा tpm_निजी अणु
	काष्ठा tpm_chip *chip;
	काष्ठा xenbus_device *dev;

	काष्ठा vtpm_shared_page *shr;

	अचिन्हित पूर्णांक evtchn;
	पूर्णांक ring_ref;
	करोmid_t backend_id;
	पूर्णांक irq;
	रुको_queue_head_t पढ़ो_queue;
पूर्ण;

क्रमागत status_bits अणु
	VTPM_STATUS_RUNNING  = 0x1,
	VTPM_STATUS_IDLE     = 0x2,
	VTPM_STATUS_RESULT   = 0x4,
	VTPM_STATUS_CANCELED = 0x8,
पूर्ण;

अटल bool रुको_क्रम_tpm_stat_cond(काष्ठा tpm_chip *chip, u8 mask,
					bool check_cancel, bool *canceled)
अणु
	u8 status = chip->ops->status(chip);

	*canceled = false;
	अगर ((status & mask) == mask)
		वापस true;
	अगर (check_cancel && chip->ops->req_canceled(chip, status)) अणु
		*canceled = true;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक रुको_क्रम_tpm_stat(काष्ठा tpm_chip *chip, u8 mask,
		अचिन्हित दीर्घ समयout, रुको_queue_head_t *queue,
		bool check_cancel)
अणु
	अचिन्हित दीर्घ stop;
	दीर्घ rc;
	u8 status;
	bool canceled = false;

	/* check current status */
	status = chip->ops->status(chip);
	अगर ((status & mask) == mask)
		वापस 0;

	stop = jअगरfies + समयout;

	अगर (chip->flags & TPM_CHIP_FLAG_IRQ) अणु
again:
		समयout = stop - jअगरfies;
		अगर ((दीर्घ)समयout <= 0)
			वापस -ETIME;
		rc = रुको_event_पूर्णांकerruptible_समयout(*queue,
			रुको_क्रम_tpm_stat_cond(chip, mask, check_cancel,
					       &canceled),
			समयout);
		अगर (rc > 0) अणु
			अगर (canceled)
				वापस -ECANCELED;
			वापस 0;
		पूर्ण
		अगर (rc == -ERESTARTSYS && मुक्तzing(current)) अणु
			clear_thपढ़ो_flag(TIF_SIGPENDING);
			जाओ again;
		पूर्ण
	पूर्ण अन्यथा अणु
		करो अणु
			tpm_msleep(TPM_TIMEOUT);
			status = chip->ops->status(chip);
			अगर ((status & mask) == mask)
				वापस 0;
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));
	पूर्ण
	वापस -ETIME;
पूर्ण

अटल u8 vtpm_status(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_निजी *priv = dev_get_drvdata(&chip->dev);
	चयन (priv->shr->state) अणु
	हाल VTPM_STATE_IDLE:
		वापस VTPM_STATUS_IDLE | VTPM_STATUS_CANCELED;
	हाल VTPM_STATE_FINISH:
		वापस VTPM_STATUS_IDLE | VTPM_STATUS_RESULT;
	हाल VTPM_STATE_SUBMIT:
	हाल VTPM_STATE_CANCEL: /* cancel requested, not yet canceled */
		वापस VTPM_STATUS_RUNNING;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल bool vtpm_req_canceled(काष्ठा tpm_chip *chip, u8 status)
अणु
	वापस status & VTPM_STATUS_CANCELED;
पूर्ण

अटल व्योम vtpm_cancel(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_निजी *priv = dev_get_drvdata(&chip->dev);
	priv->shr->state = VTPM_STATE_CANCEL;
	wmb();
	notअगरy_remote_via_evtchn(priv->evtchn);
पूर्ण

अटल अचिन्हित पूर्णांक shr_data_offset(काष्ठा vtpm_shared_page *shr)
अणु
	वापस माप(*shr) + माप(u32) * shr->nr_extra_pages;
पूर्ण

अटल पूर्णांक vtpm_send(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा tpm_निजी *priv = dev_get_drvdata(&chip->dev);
	काष्ठा vtpm_shared_page *shr = priv->shr;
	अचिन्हित पूर्णांक offset = shr_data_offset(shr);

	u32 ordinal;
	अचिन्हित दीर्घ duration;

	अगर (offset > PAGE_SIZE)
		वापस -EINVAL;

	अगर (offset + count > PAGE_SIZE)
		वापस -EINVAL;

	/* Wait क्रम completion of any existing command or cancellation */
	अगर (रुको_क्रम_tpm_stat(chip, VTPM_STATUS_IDLE, chip->समयout_c,
			&priv->पढ़ो_queue, true) < 0) अणु
		vtpm_cancel(chip);
		वापस -ETIME;
	पूर्ण

	स_नकल(offset + (u8 *)shr, buf, count);
	shr->length = count;
	barrier();
	shr->state = VTPM_STATE_SUBMIT;
	wmb();
	notअगरy_remote_via_evtchn(priv->evtchn);

	ordinal = be32_to_cpu(((काष्ठा tpm_header *)buf)->ordinal);
	duration = tpm_calc_ordinal_duration(chip, ordinal);

	अगर (रुको_क्रम_tpm_stat(chip, VTPM_STATUS_IDLE, duration,
			&priv->पढ़ो_queue, true) < 0) अणु
		/* got a संकेत or समयout, try to cancel */
		vtpm_cancel(chip);
		वापस -ETIME;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vtpm_recv(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा tpm_निजी *priv = dev_get_drvdata(&chip->dev);
	काष्ठा vtpm_shared_page *shr = priv->shr;
	अचिन्हित पूर्णांक offset = shr_data_offset(shr);
	माप_प्रकार length = shr->length;

	अगर (shr->state == VTPM_STATE_IDLE)
		वापस -ECANCELED;

	/* In theory the रुको at the end of _send makes this one unnecessary */
	अगर (रुको_क्रम_tpm_stat(chip, VTPM_STATUS_RESULT, chip->समयout_c,
			&priv->पढ़ो_queue, true) < 0) अणु
		vtpm_cancel(chip);
		वापस -ETIME;
	पूर्ण

	अगर (offset > PAGE_SIZE)
		वापस -EIO;

	अगर (offset + length > PAGE_SIZE)
		length = PAGE_SIZE - offset;

	अगर (length > count)
		length = count;

	स_नकल(buf, offset + (u8 *)shr, length);

	वापस length;
पूर्ण

अटल स्थिर काष्ठा tpm_class_ops tpm_vtpm = अणु
	.status = vtpm_status,
	.recv = vtpm_recv,
	.send = vtpm_send,
	.cancel = vtpm_cancel,
	.req_complete_mask = VTPM_STATUS_IDLE | VTPM_STATUS_RESULT,
	.req_complete_val  = VTPM_STATUS_IDLE | VTPM_STATUS_RESULT,
	.req_canceled      = vtpm_req_canceled,
पूर्ण;

अटल irqवापस_t tpmअगर_पूर्णांकerrupt(पूर्णांक dummy, व्योम *dev_id)
अणु
	काष्ठा tpm_निजी *priv = dev_id;

	चयन (priv->shr->state) अणु
	हाल VTPM_STATE_IDLE:
	हाल VTPM_STATE_FINISH:
		wake_up_पूर्णांकerruptible(&priv->पढ़ो_queue);
		अवरोध;
	हाल VTPM_STATE_SUBMIT:
	हाल VTPM_STATE_CANCEL:
	शेष:
		अवरोध;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक setup_chip(काष्ठा device *dev, काष्ठा tpm_निजी *priv)
अणु
	काष्ठा tpm_chip *chip;

	chip = tpmm_chip_alloc(dev, &tpm_vtpm);
	अगर (IS_ERR(chip))
		वापस PTR_ERR(chip);

	init_रुकोqueue_head(&priv->पढ़ो_queue);

	priv->chip = chip;
	dev_set_drvdata(&chip->dev, priv);

	वापस 0;
पूर्ण

/* caller must clean up in हाल of errors */
अटल पूर्णांक setup_ring(काष्ठा xenbus_device *dev, काष्ठा tpm_निजी *priv)
अणु
	काष्ठा xenbus_transaction xbt;
	स्थिर अक्षर *message = शून्य;
	पूर्णांक rv;
	grant_ref_t gref;

	priv->shr = (व्योम *)__get_मुक्त_page(GFP_KERNEL|__GFP_ZERO);
	अगर (!priv->shr) अणु
		xenbus_dev_fatal(dev, -ENOMEM, "allocating shared ring");
		वापस -ENOMEM;
	पूर्ण

	rv = xenbus_grant_ring(dev, priv->shr, 1, &gref);
	अगर (rv < 0)
		वापस rv;

	priv->ring_ref = gref;

	rv = xenbus_alloc_evtchn(dev, &priv->evtchn);
	अगर (rv)
		वापस rv;

	rv = bind_evtchn_to_irqhandler(priv->evtchn, tpmअगर_पूर्णांकerrupt, 0,
				       "tpmif", priv);
	अगर (rv <= 0) अणु
		xenbus_dev_fatal(dev, rv, "allocating TPM irq");
		वापस rv;
	पूर्ण
	priv->irq = rv;

 again:
	rv = xenbus_transaction_start(&xbt);
	अगर (rv) अणु
		xenbus_dev_fatal(dev, rv, "starting transaction");
		वापस rv;
	पूर्ण

	rv = xenbus_म_लिखो(xbt, dev->nodename,
			"ring-ref", "%u", priv->ring_ref);
	अगर (rv) अणु
		message = "writing ring-ref";
		जाओ पात_transaction;
	पूर्ण

	rv = xenbus_म_लिखो(xbt, dev->nodename, "event-channel", "%u",
			priv->evtchn);
	अगर (rv) अणु
		message = "writing event-channel";
		जाओ पात_transaction;
	पूर्ण

	rv = xenbus_म_लिखो(xbt, dev->nodename, "feature-protocol-v2", "1");
	अगर (rv) अणु
		message = "writing feature-protocol-v2";
		जाओ पात_transaction;
	पूर्ण

	rv = xenbus_transaction_end(xbt, 0);
	अगर (rv == -EAGAIN)
		जाओ again;
	अगर (rv) अणु
		xenbus_dev_fatal(dev, rv, "completing transaction");
		वापस rv;
	पूर्ण

	xenbus_चयन_state(dev, XenbusStateInitialised);

	वापस 0;

 पात_transaction:
	xenbus_transaction_end(xbt, 1);
	अगर (message)
		xenbus_dev_error(dev, rv, "%s", message);

	वापस rv;
पूर्ण

अटल व्योम ring_मुक्त(काष्ठा tpm_निजी *priv)
अणु
	अगर (!priv)
		वापस;

	अगर (priv->ring_ref)
		gnttab_end_क्रमeign_access(priv->ring_ref, 0,
				(अचिन्हित दीर्घ)priv->shr);
	अन्यथा
		मुक्त_page((अचिन्हित दीर्घ)priv->shr);

	अगर (priv->irq)
		unbind_from_irqhandler(priv->irq, priv);

	kमुक्त(priv);
पूर्ण

अटल पूर्णांक tpmfront_probe(काष्ठा xenbus_device *dev,
		स्थिर काष्ठा xenbus_device_id *id)
अणु
	काष्ठा tpm_निजी *priv;
	पूर्णांक rv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		xenbus_dev_fatal(dev, -ENOMEM, "allocating priv structure");
		वापस -ENOMEM;
	पूर्ण

	rv = setup_chip(&dev->dev, priv);
	अगर (rv) अणु
		kमुक्त(priv);
		वापस rv;
	पूर्ण

	rv = setup_ring(dev, priv);
	अगर (rv) अणु
		ring_मुक्त(priv);
		वापस rv;
	पूर्ण

	tpm_get_समयouts(priv->chip);

	वापस tpm_chip_रेजिस्टर(priv->chip);
पूर्ण

अटल पूर्णांक tpmfront_हटाओ(काष्ठा xenbus_device *dev)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(&dev->dev);
	काष्ठा tpm_निजी *priv = dev_get_drvdata(&chip->dev);
	tpm_chip_unरेजिस्टर(chip);
	ring_मुक्त(priv);
	dev_set_drvdata(&chip->dev, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक tpmfront_resume(काष्ठा xenbus_device *dev)
अणु
	/* A suspend/resume/migrate will पूर्णांकerrupt a vTPM anyway */
	tpmfront_हटाओ(dev);
	वापस tpmfront_probe(dev, शून्य);
पूर्ण

अटल व्योम backend_changed(काष्ठा xenbus_device *dev,
		क्रमागत xenbus_state backend_state)
अणु
	चयन (backend_state) अणु
	हाल XenbusStateInitialised:
	हाल XenbusStateConnected:
		अगर (dev->state == XenbusStateConnected)
			अवरोध;

		अगर (!xenbus_पढ़ो_अचिन्हित(dev->otherend, "feature-protocol-v2",
					  0)) अणु
			xenbus_dev_fatal(dev, -EINVAL,
					"vTPM protocol 2 required");
			वापस;
		पूर्ण
		xenbus_चयन_state(dev, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateClosing:
	हाल XenbusStateClosed:
		device_unरेजिस्टर(&dev->dev);
		xenbus_frontend_बंदd(dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा xenbus_device_id tpmfront_ids[] = अणु
	अणु "vtpm" पूर्ण,
	अणु "" पूर्ण
पूर्ण;
MODULE_ALIAS("xen:vtpm");

अटल काष्ठा xenbus_driver tpmfront_driver = अणु
	.ids = tpmfront_ids,
	.probe = tpmfront_probe,
	.हटाओ = tpmfront_हटाओ,
	.resume = tpmfront_resume,
	.otherend_changed = backend_changed,
पूर्ण;

अटल पूर्णांक __init xen_tpmfront_init(व्योम)
अणु
	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	अगर (!xen_has_pv_devices())
		वापस -ENODEV;

	वापस xenbus_रेजिस्टर_frontend(&tpmfront_driver);
पूर्ण
module_init(xen_tpmfront_init);

अटल व्योम __निकास xen_tpmfront_निकास(व्योम)
अणु
	xenbus_unरेजिस्टर_driver(&tpmfront_driver);
पूर्ण
module_निकास(xen_tpmfront_निकास);

MODULE_AUTHOR("Daniel De Graaf <dgdegra@tycho.nsa.gov>");
MODULE_DESCRIPTION("Xen vTPM Driver");
MODULE_LICENSE("GPL");
