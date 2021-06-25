<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * finite state machine क्रम device handling
 *
 *    Copyright IBM Corp. 2002, 2008
 *    Author(s): Cornelia Huck (cornelia.huck@de.ibm.com)
 *		 Martin Schwidefsky (schwidefsky@de.ibm.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/chpid.h>

#समावेश "cio.h"
#समावेश "cio_debug.h"
#समावेश "css.h"
#समावेश "device.h"
#समावेश "chsc.h"
#समावेश "ioasm.h"
#समावेश "chp.h"

अटल पूर्णांक समयout_log_enabled;

अटल पूर्णांक __init ccw_समयout_log_setup(अक्षर *unused)
अणु
	समयout_log_enabled = 1;
	वापस 1;
पूर्ण

__setup("ccw_timeout_log", ccw_समयout_log_setup);

अटल व्योम ccw_समयout_log(काष्ठा ccw_device *cdev)
अणु
	काष्ठा schib schib;
	काष्ठा subchannel *sch;
	काष्ठा io_subchannel_निजी *निजी;
	जोड़ orb *orb;
	पूर्णांक cc;

	sch = to_subchannel(cdev->dev.parent);
	निजी = to_io_निजी(sch);
	orb = &निजी->orb;
	cc = stsch(sch->schid, &schib);

	prपूर्णांकk(KERN_WARNING "cio: ccw device timeout occurred at %lx, "
	       "device information:\n", get_tod_घड़ी());
	prपूर्णांकk(KERN_WARNING "cio: orb:\n");
	prपूर्णांक_hex_dump(KERN_WARNING, "cio:  ", DUMP_PREFIX_NONE, 16, 1,
		       orb, माप(*orb), 0);
	prपूर्णांकk(KERN_WARNING "cio: ccw device bus id: %s\n",
	       dev_name(&cdev->dev));
	prपूर्णांकk(KERN_WARNING "cio: subchannel bus id: %s\n",
	       dev_name(&sch->dev));
	prपूर्णांकk(KERN_WARNING "cio: subchannel lpm: %02x, opm: %02x, "
	       "vpm: %02x\n", sch->lpm, sch->opm, sch->vpm);

	अगर (orb->पंचांग.b) अणु
		prपूर्णांकk(KERN_WARNING "cio: orb indicates transport mode\n");
		prपूर्णांकk(KERN_WARNING "cio: last tcw:\n");
		prपूर्णांक_hex_dump(KERN_WARNING, "cio:  ", DUMP_PREFIX_NONE, 16, 1,
			       (व्योम *)(addr_t)orb->पंचांग.tcw,
			       माप(काष्ठा tcw), 0);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "cio: orb indicates command mode\n");
		अगर ((व्योम *)(addr_t)orb->cmd.cpa ==
		    &निजी->dma_area->sense_ccw ||
		    (व्योम *)(addr_t)orb->cmd.cpa ==
		    cdev->निजी->dma_area->iccws)
			prपूर्णांकk(KERN_WARNING "cio: last channel program "
			       "(intern):\n");
		अन्यथा
			prपूर्णांकk(KERN_WARNING "cio: last channel program:\n");

		prपूर्णांक_hex_dump(KERN_WARNING, "cio:  ", DUMP_PREFIX_NONE, 16, 1,
			       (व्योम *)(addr_t)orb->cmd.cpa,
			       माप(काष्ठा ccw1), 0);
	पूर्ण
	prपूर्णांकk(KERN_WARNING "cio: ccw device state: %d\n",
	       cdev->निजी->state);
	prपूर्णांकk(KERN_WARNING "cio: store subchannel returned: cc=%d\n", cc);
	prपूर्णांकk(KERN_WARNING "cio: schib:\n");
	prपूर्णांक_hex_dump(KERN_WARNING, "cio:  ", DUMP_PREFIX_NONE, 16, 1,
		       &schib, माप(schib), 0);
	prपूर्णांकk(KERN_WARNING "cio: ccw device flags:\n");
	prपूर्णांक_hex_dump(KERN_WARNING, "cio:  ", DUMP_PREFIX_NONE, 16, 1,
		       &cdev->निजी->flags, माप(cdev->निजी->flags), 0);
पूर्ण

/*
 * Timeout function. It just triggers a DEV_EVENT_TIMEOUT.
 */
व्योम
ccw_device_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा ccw_device_निजी *priv = from_समयr(priv, t, समयr);
	काष्ठा ccw_device *cdev = priv->cdev;

	spin_lock_irq(cdev->ccwlock);
	अगर (समयout_log_enabled)
		ccw_समयout_log(cdev);
	dev_fsm_event(cdev, DEV_EVENT_TIMEOUT);
	spin_unlock_irq(cdev->ccwlock);
पूर्ण

/*
 * Set समयout
 */
व्योम
ccw_device_set_समयout(काष्ठा ccw_device *cdev, पूर्णांक expires)
अणु
	अगर (expires == 0) अणु
		del_समयr(&cdev->निजी->समयr);
		वापस;
	पूर्ण
	अगर (समयr_pending(&cdev->निजी->समयr)) अणु
		अगर (mod_समयr(&cdev->निजी->समयr, jअगरfies + expires))
			वापस;
	पूर्ण
	cdev->निजी->समयr.expires = jअगरfies + expires;
	add_समयr(&cdev->निजी->समयr);
पूर्ण

पूर्णांक
ccw_device_cancel_halt_clear(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch;
	पूर्णांक ret;

	sch = to_subchannel(cdev->dev.parent);
	ret = cio_cancel_halt_clear(sch, &cdev->निजी->iretry);

	अगर (ret == -EIO)
		CIO_MSG_EVENT(0, "0.%x.%04x: could not stop I/O\n",
			      cdev->निजी->dev_id.ssid,
			      cdev->निजी->dev_id.devno);

	वापस ret;
पूर्ण

व्योम ccw_device_update_sense_data(काष्ठा ccw_device *cdev)
अणु
	स_रखो(&cdev->id, 0, माप(cdev->id));
	cdev->id.cu_type = cdev->निजी->dma_area->senseid.cu_type;
	cdev->id.cu_model = cdev->निजी->dma_area->senseid.cu_model;
	cdev->id.dev_type = cdev->निजी->dma_area->senseid.dev_type;
	cdev->id.dev_model = cdev->निजी->dma_area->senseid.dev_model;
पूर्ण

पूर्णांक ccw_device_test_sense_data(काष्ठा ccw_device *cdev)
अणु
	वापस cdev->id.cu_type ==
		cdev->निजी->dma_area->senseid.cu_type &&
		cdev->id.cu_model ==
		cdev->निजी->dma_area->senseid.cu_model &&
		cdev->id.dev_type ==
		cdev->निजी->dma_area->senseid.dev_type &&
		cdev->id.dev_model ==
		cdev->निजी->dma_area->senseid.dev_model;
पूर्ण

/*
 * The machine won't give us any notअगरication by machine check अगर a chpid has
 * been varied online on the SE so we have to find out by magic (i. e. driving
 * the channel subप्रणाली to device selection and updating our path masks).
 */
अटल व्योम
__recover_lost_chpids(काष्ठा subchannel *sch, पूर्णांक old_lpm)
अणु
	पूर्णांक mask, i;
	काष्ठा chp_id chpid;

	chp_id_init(&chpid);
	क्रम (i = 0; i<8; i++) अणु
		mask = 0x80 >> i;
		अगर (!(sch->lpm & mask))
			जारी;
		अगर (old_lpm & mask)
			जारी;
		chpid.id = sch->schib.pmcw.chpid[i];
		अगर (!chp_is_रेजिस्टरed(chpid))
			css_schedule_eval_all();
	पूर्ण
पूर्ण

/*
 * Stop device recognition.
 */
अटल व्योम
ccw_device_recog_करोne(काष्ठा ccw_device *cdev, पूर्णांक state)
अणु
	काष्ठा subchannel *sch;
	पूर्णांक old_lpm;

	sch = to_subchannel(cdev->dev.parent);

	अगर (cio_disable_subchannel(sch))
		state = DEV_STATE_NOT_OPER;
	/*
	 * Now that we tried recognition, we have perक्रमmed device selection
	 * through ssch() and the path inक्रमmation is up to date.
	 */
	old_lpm = sch->lpm;

	/* Check since device may again have become not operational. */
	अगर (cio_update_schib(sch))
		state = DEV_STATE_NOT_OPER;
	अन्यथा
		sch->lpm = sch->schib.pmcw.pam & sch->opm;

	अगर (cdev->निजी->state == DEV_STATE_DISCONNECTED_SENSE_ID)
		/* Force reprobe on all chpids. */
		old_lpm = 0;
	अगर (sch->lpm != old_lpm)
		__recover_lost_chpids(sch, old_lpm);
	अगर (cdev->निजी->state == DEV_STATE_DISCONNECTED_SENSE_ID &&
	    (state == DEV_STATE_NOT_OPER || state == DEV_STATE_BOXED)) अणु
		cdev->निजी->flags.recog_करोne = 1;
		cdev->निजी->state = DEV_STATE_DISCONNECTED;
		wake_up(&cdev->निजी->रुको_q);
		वापस;
	पूर्ण
	चयन (state) अणु
	हाल DEV_STATE_NOT_OPER:
		अवरोध;
	हाल DEV_STATE_OFFLINE:
		अगर (!cdev->online) अणु
			ccw_device_update_sense_data(cdev);
			अवरोध;
		पूर्ण
		cdev->निजी->state = DEV_STATE_OFFLINE;
		cdev->निजी->flags.recog_करोne = 1;
		अगर (ccw_device_test_sense_data(cdev)) अणु
			cdev->निजी->flags.करोnotअगरy = 1;
			ccw_device_online(cdev);
			wake_up(&cdev->निजी->रुको_q);
		पूर्ण अन्यथा अणु
			ccw_device_update_sense_data(cdev);
			ccw_device_sched_toकरो(cdev, CDEV_TODO_REBIND);
		पूर्ण
		वापस;
	हाल DEV_STATE_BOXED:
		अगर (cdev->id.cu_type != 0) अणु /* device was recognized beक्रमe */
			cdev->निजी->flags.recog_करोne = 1;
			cdev->निजी->state = DEV_STATE_BOXED;
			wake_up(&cdev->निजी->रुको_q);
			वापस;
		पूर्ण
		अवरोध;
	पूर्ण
	cdev->निजी->state = state;
	io_subchannel_recog_करोne(cdev);
	wake_up(&cdev->निजी->रुको_q);
पूर्ण

/*
 * Function called from device_id.c after sense id has completed.
 */
व्योम
ccw_device_sense_id_करोne(काष्ठा ccw_device *cdev, पूर्णांक err)
अणु
	चयन (err) अणु
	हाल 0:
		ccw_device_recog_करोne(cdev, DEV_STATE_OFFLINE);
		अवरोध;
	हाल -ETIME:		/* Sense id stopped by समयout. */
		ccw_device_recog_करोne(cdev, DEV_STATE_BOXED);
		अवरोध;
	शेष:
		ccw_device_recog_करोne(cdev, DEV_STATE_NOT_OPER);
		अवरोध;
	पूर्ण
पूर्ण

/**
  * ccw_device_notअगरy() - inक्रमm the device's driver about an event
  * @cdev: device क्रम which an event occurred
  * @event: event that occurred
  *
  * Returns:
  *   -%EINVAL अगर the device is offline or has no driver.
  *   -%EOPNOTSUPP अगर the device's driver has no notअगरier रेजिस्टरed.
  *   %NOTIFY_OK अगर the driver wants to keep the device.
  *   %NOTIFY_BAD अगर the driver करोesn't want to keep the device.
  */
पूर्णांक ccw_device_notअगरy(काष्ठा ccw_device *cdev, पूर्णांक event)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!cdev->drv)
		जाओ out;
	अगर (!cdev->online)
		जाओ out;
	CIO_MSG_EVENT(2, "notify called for 0.%x.%04x, event=%d\n",
		      cdev->निजी->dev_id.ssid, cdev->निजी->dev_id.devno,
		      event);
	अगर (!cdev->drv->notअगरy) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	अगर (cdev->drv->notअगरy(cdev, event))
		ret = NOTIFY_OK;
	अन्यथा
		ret = NOTIFY_BAD;
out:
	वापस ret;
पूर्ण

अटल व्योम ccw_device_oper_notअगरy(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);

	अगर (ccw_device_notअगरy(cdev, CIO_OPER) == NOTIFY_OK) अणु
		/* Reenable channel measurements, अगर needed. */
		ccw_device_sched_toकरो(cdev, CDEV_TODO_ENABLE_CMF);
		/* Save indication क्रम new paths. */
		cdev->निजी->path_new_mask = sch->vpm;
		वापस;
	पूर्ण
	/* Driver करोesn't want device back. */
	ccw_device_set_notoper(cdev);
	ccw_device_sched_toकरो(cdev, CDEV_TODO_REBIND);
पूर्ण

/*
 * Finished with online/offline processing.
 */
अटल व्योम
ccw_device_करोne(काष्ठा ccw_device *cdev, पूर्णांक state)
अणु
	काष्ठा subchannel *sch;

	sch = to_subchannel(cdev->dev.parent);

	ccw_device_set_समयout(cdev, 0);

	अगर (state != DEV_STATE_ONLINE)
		cio_disable_subchannel(sch);

	/* Reset device status. */
	स_रखो(&cdev->निजी->dma_area->irb, 0, माप(काष्ठा irb));

	cdev->निजी->state = state;

	चयन (state) अणु
	हाल DEV_STATE_BOXED:
		CIO_MSG_EVENT(0, "Boxed device %04x on subchannel %04x\n",
			      cdev->निजी->dev_id.devno, sch->schid.sch_no);
		अगर (cdev->online &&
		    ccw_device_notअगरy(cdev, CIO_BOXED) != NOTIFY_OK)
			ccw_device_sched_toकरो(cdev, CDEV_TODO_UNREG);
		cdev->निजी->flags.करोnotअगरy = 0;
		अवरोध;
	हाल DEV_STATE_NOT_OPER:
		CIO_MSG_EVENT(0, "Device %04x gone on subchannel %04x\n",
			      cdev->निजी->dev_id.devno, sch->schid.sch_no);
		अगर (ccw_device_notअगरy(cdev, CIO_GONE) != NOTIFY_OK)
			ccw_device_sched_toकरो(cdev, CDEV_TODO_UNREG);
		अन्यथा
			ccw_device_set_disconnected(cdev);
		cdev->निजी->flags.करोnotअगरy = 0;
		अवरोध;
	हाल DEV_STATE_DISCONNECTED:
		CIO_MSG_EVENT(0, "Disconnected device %04x on subchannel "
			      "%04x\n", cdev->निजी->dev_id.devno,
			      sch->schid.sch_no);
		अगर (ccw_device_notअगरy(cdev, CIO_NO_PATH) != NOTIFY_OK) अणु
			cdev->निजी->state = DEV_STATE_NOT_OPER;
			ccw_device_sched_toकरो(cdev, CDEV_TODO_UNREG);
		पूर्ण अन्यथा
			ccw_device_set_disconnected(cdev);
		cdev->निजी->flags.करोnotअगरy = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (cdev->निजी->flags.करोnotअगरy) अणु
		cdev->निजी->flags.करोnotअगरy = 0;
		ccw_device_oper_notअगरy(cdev);
	पूर्ण
	wake_up(&cdev->निजी->रुको_q);
पूर्ण

/*
 * Start device recognition.
 */
व्योम ccw_device_recognition(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);

	/*
	 * We used to start here with a sense pgid to find out whether a device
	 * is locked by someone अन्यथा. Unक्रमtunately, the sense pgid command
	 * code has other meanings on devices predating the path grouping
	 * algorithm, so we start with sense id and box the device after an
	 * समयout (or अगर sense pgid during path verअगरication detects the device
	 * is locked, as may happen on newer devices).
	 */
	cdev->निजी->flags.recog_करोne = 0;
	cdev->निजी->state = DEV_STATE_SENSE_ID;
	अगर (cio_enable_subchannel(sch, (u32) (addr_t) sch)) अणु
		ccw_device_recog_करोne(cdev, DEV_STATE_NOT_OPER);
		वापस;
	पूर्ण
	ccw_device_sense_id_start(cdev);
पूर्ण

/*
 * Handle events क्रम states that use the ccw request infraकाष्ठाure.
 */
अटल व्योम ccw_device_request_event(काष्ठा ccw_device *cdev, क्रमागत dev_event e)
अणु
	चयन (e) अणु
	हाल DEV_EVENT_NOTOPER:
		ccw_request_notoper(cdev);
		अवरोध;
	हाल DEV_EVENT_INTERRUPT:
		ccw_request_handler(cdev);
		अवरोध;
	हाल DEV_EVENT_TIMEOUT:
		ccw_request_समयout(cdev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ccw_device_report_path_events(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	पूर्णांक path_event[8];
	पूर्णांक chp, mask;

	क्रम (chp = 0, mask = 0x80; chp < 8; chp++, mask >>= 1) अणु
		path_event[chp] = PE_NONE;
		अगर (mask & cdev->निजी->path_gone_mask & ~(sch->vpm))
			path_event[chp] |= PE_PATH_GONE;
		अगर (mask & cdev->निजी->path_new_mask & sch->vpm)
			path_event[chp] |= PE_PATH_AVAILABLE;
		अगर (mask & cdev->निजी->pgid_reset_mask & sch->vpm)
			path_event[chp] |= PE_PATHGROUP_ESTABLISHED;
	पूर्ण
	अगर (cdev->online && cdev->drv->path_event)
		cdev->drv->path_event(cdev, path_event);
पूर्ण

अटल व्योम ccw_device_reset_path_events(काष्ठा ccw_device *cdev)
अणु
	cdev->निजी->path_gone_mask = 0;
	cdev->निजी->path_new_mask = 0;
	cdev->निजी->pgid_reset_mask = 0;
पूर्ण

अटल व्योम create_fake_irb(काष्ठा irb *irb, पूर्णांक type)
अणु
	स_रखो(irb, 0, माप(*irb));
	अगर (type == FAKE_CMD_IRB) अणु
		काष्ठा cmd_scsw *scsw = &irb->scsw.cmd;
		scsw->cc = 1;
		scsw->fctl = SCSW_FCTL_START_FUNC;
		scsw->actl = SCSW_ACTL_START_PEND;
		scsw->stctl = SCSW_STCTL_STATUS_PEND;
	पूर्ण अन्यथा अगर (type == FAKE_TM_IRB) अणु
		काष्ठा पंचांग_scsw *scsw = &irb->scsw.पंचांग;
		scsw->x = 1;
		scsw->cc = 1;
		scsw->fctl = SCSW_FCTL_START_FUNC;
		scsw->actl = SCSW_ACTL_START_PEND;
		scsw->stctl = SCSW_STCTL_STATUS_PEND;
	पूर्ण
पूर्ण

अटल व्योम ccw_device_handle_broken_paths(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	u8 broken_paths = (sch->schib.pmcw.pam & sch->opm) ^ sch->vpm;

	अगर (broken_paths && (cdev->निजी->path_broken_mask != broken_paths))
		ccw_device_schedule_recovery();

	cdev->निजी->path_broken_mask = broken_paths;
पूर्ण

व्योम ccw_device_verअगरy_करोne(काष्ठा ccw_device *cdev, पूर्णांक err)
अणु
	काष्ठा subchannel *sch;

	sch = to_subchannel(cdev->dev.parent);
	/* Update schib - pom may have changed. */
	अगर (cio_update_schib(sch)) अणु
		err = -ENODEV;
		जाओ callback;
	पूर्ण
	/* Update lpm with verअगरied path mask. */
	sch->lpm = sch->vpm;
	/* Repeat path verअगरication? */
	अगर (cdev->निजी->flags.करोverअगरy) अणु
		ccw_device_verअगरy_start(cdev);
		वापस;
	पूर्ण
callback:
	चयन (err) अणु
	हाल 0:
		ccw_device_करोne(cdev, DEV_STATE_ONLINE);
		/* Deliver fake irb to device driver, अगर needed. */
		अगर (cdev->निजी->flags.fake_irb) अणु
			create_fake_irb(&cdev->निजी->dma_area->irb,
					cdev->निजी->flags.fake_irb);
			cdev->निजी->flags.fake_irb = 0;
			अगर (cdev->handler)
				cdev->handler(cdev, cdev->निजी->पूर्णांकparm,
					      &cdev->निजी->dma_area->irb);
			स_रखो(&cdev->निजी->dma_area->irb, 0,
			       माप(काष्ठा irb));
		पूर्ण
		ccw_device_report_path_events(cdev);
		ccw_device_handle_broken_paths(cdev);
		अवरोध;
	हाल -ETIME:
	हाल -EUSERS:
		/* Reset oper notअगरy indication after verअगरy error. */
		cdev->निजी->flags.करोnotअगरy = 0;
		ccw_device_करोne(cdev, DEV_STATE_BOXED);
		अवरोध;
	हाल -EACCES:
		/* Reset oper notअगरy indication after verअगरy error. */
		cdev->निजी->flags.करोnotअगरy = 0;
		ccw_device_करोne(cdev, DEV_STATE_DISCONNECTED);
		अवरोध;
	शेष:
		/* Reset oper notअगरy indication after verअगरy error. */
		cdev->निजी->flags.करोnotअगरy = 0;
		ccw_device_करोne(cdev, DEV_STATE_NOT_OPER);
		अवरोध;
	पूर्ण
	ccw_device_reset_path_events(cdev);
पूर्ण

/*
 * Get device online.
 */
पूर्णांक
ccw_device_online(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch;
	पूर्णांक ret;

	अगर ((cdev->निजी->state != DEV_STATE_OFFLINE) &&
	    (cdev->निजी->state != DEV_STATE_BOXED))
		वापस -EINVAL;
	sch = to_subchannel(cdev->dev.parent);
	ret = cio_enable_subchannel(sch, (u32)(addr_t)sch);
	अगर (ret != 0) अणु
		/* Couldn't enable the subchannel क्रम i/o. Sick device. */
		अगर (ret == -ENODEV)
			dev_fsm_event(cdev, DEV_EVENT_NOTOPER);
		वापस ret;
	पूर्ण
	/* Start initial path verअगरication. */
	cdev->निजी->state = DEV_STATE_VERIFY;
	ccw_device_verअगरy_start(cdev);
	वापस 0;
पूर्ण

व्योम
ccw_device_disband_करोne(काष्ठा ccw_device *cdev, पूर्णांक err)
अणु
	चयन (err) अणु
	हाल 0:
		ccw_device_करोne(cdev, DEV_STATE_OFFLINE);
		अवरोध;
	हाल -ETIME:
		ccw_device_करोne(cdev, DEV_STATE_BOXED);
		अवरोध;
	शेष:
		cdev->निजी->flags.करोnotअगरy = 0;
		ccw_device_करोne(cdev, DEV_STATE_NOT_OPER);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Shutकरोwn device.
 */
पूर्णांक
ccw_device_offline(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch;

	/* Allow ccw_device_offline जबतक disconnected. */
	अगर (cdev->निजी->state == DEV_STATE_DISCONNECTED ||
	    cdev->निजी->state == DEV_STATE_NOT_OPER) अणु
		cdev->निजी->flags.करोnotअगरy = 0;
		ccw_device_करोne(cdev, DEV_STATE_NOT_OPER);
		वापस 0;
	पूर्ण
	अगर (cdev->निजी->state == DEV_STATE_BOXED) अणु
		ccw_device_करोne(cdev, DEV_STATE_BOXED);
		वापस 0;
	पूर्ण
	अगर (ccw_device_is_orphan(cdev)) अणु
		ccw_device_करोne(cdev, DEV_STATE_OFFLINE);
		वापस 0;
	पूर्ण
	sch = to_subchannel(cdev->dev.parent);
	अगर (cio_update_schib(sch))
		वापस -ENODEV;
	अगर (scsw_actl(&sch->schib.scsw) != 0)
		वापस -EBUSY;
	अगर (cdev->निजी->state != DEV_STATE_ONLINE)
		वापस -EINVAL;
	/* Are we करोing path grouping? */
	अगर (!cdev->निजी->flags.pgroup) अणु
		/* No, set state offline immediately. */
		ccw_device_करोne(cdev, DEV_STATE_OFFLINE);
		वापस 0;
	पूर्ण
	/* Start Set Path Group commands. */
	cdev->निजी->state = DEV_STATE_DISBAND_PGID;
	ccw_device_disband_start(cdev);
	वापस 0;
पूर्ण

/*
 * Handle not operational event in non-special state.
 */
अटल व्योम ccw_device_generic_notoper(काष्ठा ccw_device *cdev,
				       क्रमागत dev_event dev_event)
अणु
	अगर (ccw_device_notअगरy(cdev, CIO_GONE) != NOTIFY_OK)
		ccw_device_sched_toकरो(cdev, CDEV_TODO_UNREG);
	अन्यथा
		ccw_device_set_disconnected(cdev);
पूर्ण

/*
 * Handle path verअगरication event in offline state.
 */
अटल व्योम ccw_device_offline_verअगरy(काष्ठा ccw_device *cdev,
				      क्रमागत dev_event dev_event)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);

	css_schedule_eval(sch->schid);
पूर्ण

/*
 * Handle path verअगरication event.
 */
अटल व्योम
ccw_device_online_verअगरy(काष्ठा ccw_device *cdev, क्रमागत dev_event dev_event)
अणु
	काष्ठा subchannel *sch;

	अगर (cdev->निजी->state == DEV_STATE_W4SENSE) अणु
		cdev->निजी->flags.करोverअगरy = 1;
		वापस;
	पूर्ण
	sch = to_subchannel(cdev->dev.parent);
	/*
	 * Since we might not just be coming from an पूर्णांकerrupt from the
	 * subchannel we have to update the schib.
	 */
	अगर (cio_update_schib(sch)) अणु
		ccw_device_verअगरy_करोne(cdev, -ENODEV);
		वापस;
	पूर्ण

	अगर (scsw_actl(&sch->schib.scsw) != 0 ||
	    (scsw_stctl(&sch->schib.scsw) & SCSW_STCTL_STATUS_PEND) ||
	    (scsw_stctl(&cdev->निजी->dma_area->irb.scsw) &
	     SCSW_STCTL_STATUS_PEND)) अणु
		/*
		 * No final status yet or final status not yet delivered
		 * to the device driver. Can't करो path verअगरication now,
		 * delay until final status was delivered.
		 */
		cdev->निजी->flags.करोverअगरy = 1;
		वापस;
	पूर्ण
	/* Device is idle, we can करो the path verअगरication. */
	cdev->निजी->state = DEV_STATE_VERIFY;
	ccw_device_verअगरy_start(cdev);
पूर्ण

/*
 * Handle path verअगरication event in boxed state.
 */
अटल व्योम ccw_device_boxed_verअगरy(काष्ठा ccw_device *cdev,
				    क्रमागत dev_event dev_event)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);

	अगर (cdev->online) अणु
		अगर (cio_enable_subchannel(sch, (u32) (addr_t) sch))
			ccw_device_करोne(cdev, DEV_STATE_NOT_OPER);
		अन्यथा
			ccw_device_online_verअगरy(cdev, dev_event);
	पूर्ण अन्यथा
		css_schedule_eval(sch->schid);
पूर्ण

/*
 * Pass पूर्णांकerrupt to device driver.
 */
अटल पूर्णांक ccw_device_call_handler(काष्ठा ccw_device *cdev)
अणु
	अचिन्हित पूर्णांक stctl;
	पूर्णांक ending_status;

	/*
	 * we allow क्रम the device action handler अगर .
	 *  - we received ending status
	 *  - the action handler requested to see all पूर्णांकerrupts
	 *  - we received an पूर्णांकermediate status
	 *  - fast notअगरication was requested (primary status)
	 *  - unsolicited पूर्णांकerrupts
	 */
	stctl = scsw_stctl(&cdev->निजी->dma_area->irb.scsw);
	ending_status = (stctl & SCSW_STCTL_SEC_STATUS) ||
		(stctl == (SCSW_STCTL_ALERT_STATUS | SCSW_STCTL_STATUS_PEND)) ||
		(stctl == SCSW_STCTL_STATUS_PEND);
	अगर (!ending_status &&
	    !cdev->निजी->options.repall &&
	    !(stctl & SCSW_STCTL_INTER_STATUS) &&
	    !(cdev->निजी->options.fast &&
	      (stctl & SCSW_STCTL_PRIM_STATUS)))
		वापस 0;

	अगर (ending_status)
		ccw_device_set_समयout(cdev, 0);

	अगर (cdev->handler)
		cdev->handler(cdev, cdev->निजी->पूर्णांकparm,
			      &cdev->निजी->dma_area->irb);

	स_रखो(&cdev->निजी->dma_area->irb, 0, माप(काष्ठा irb));
	वापस 1;
पूर्ण

/*
 * Got an पूर्णांकerrupt क्रम a normal io (state online).
 */
अटल व्योम
ccw_device_irq(काष्ठा ccw_device *cdev, क्रमागत dev_event dev_event)
अणु
	काष्ठा irb *irb;
	पूर्णांक is_cmd;

	irb = this_cpu_ptr(&cio_irb);
	is_cmd = !scsw_is_पंचांग(&irb->scsw);
	/* Check क्रम unsolicited पूर्णांकerrupt. */
	अगर (!scsw_is_solicited(&irb->scsw)) अणु
		अगर (is_cmd && (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) &&
		    !irb->esw.esw0.erw.cons) अणु
			/* Unit check but no sense data. Need basic sense. */
			अगर (ccw_device_करो_sense(cdev, irb) != 0)
				जाओ call_handler_unsol;
			स_नकल(&cdev->निजी->dma_area->irb, irb,
			       माप(काष्ठा irb));
			cdev->निजी->state = DEV_STATE_W4SENSE;
			cdev->निजी->पूर्णांकparm = 0;
			वापस;
		पूर्ण
call_handler_unsol:
		अगर (cdev->handler)
			cdev->handler (cdev, 0, irb);
		अगर (cdev->निजी->flags.करोverअगरy)
			ccw_device_online_verअगरy(cdev, 0);
		वापस;
	पूर्ण
	/* Accumulate status and find out अगर a basic sense is needed. */
	ccw_device_accumulate_irb(cdev, irb);
	अगर (is_cmd && cdev->निजी->flags.करोsense) अणु
		अगर (ccw_device_करो_sense(cdev, irb) == 0) अणु
			cdev->निजी->state = DEV_STATE_W4SENSE;
		पूर्ण
		वापस;
	पूर्ण
	/* Call the handler. */
	अगर (ccw_device_call_handler(cdev) && cdev->निजी->flags.करोverअगरy)
		/* Start delayed path verअगरication. */
		ccw_device_online_verअगरy(cdev, 0);
पूर्ण

/*
 * Got an समयout in online state.
 */
अटल व्योम
ccw_device_online_समयout(काष्ठा ccw_device *cdev, क्रमागत dev_event dev_event)
अणु
	पूर्णांक ret;

	ccw_device_set_समयout(cdev, 0);
	cdev->निजी->iretry = 255;
	cdev->निजी->async_समाप्त_io_rc = -ETIMEDOUT;
	ret = ccw_device_cancel_halt_clear(cdev);
	अगर (ret == -EBUSY) अणु
		ccw_device_set_समयout(cdev, 3*HZ);
		cdev->निजी->state = DEV_STATE_TIMEOUT_KILL;
		वापस;
	पूर्ण
	अगर (ret)
		dev_fsm_event(cdev, DEV_EVENT_NOTOPER);
	अन्यथा अगर (cdev->handler)
		cdev->handler(cdev, cdev->निजी->पूर्णांकparm,
			      ERR_PTR(-ETIMEDOUT));
पूर्ण

/*
 * Got an पूर्णांकerrupt क्रम a basic sense.
 */
अटल व्योम
ccw_device_w4sense(काष्ठा ccw_device *cdev, क्रमागत dev_event dev_event)
अणु
	काष्ठा irb *irb;

	irb = this_cpu_ptr(&cio_irb);
	/* Check क्रम unsolicited पूर्णांकerrupt. */
	अगर (scsw_stctl(&irb->scsw) ==
	    (SCSW_STCTL_STATUS_PEND | SCSW_STCTL_ALERT_STATUS)) अणु
		अगर (scsw_cc(&irb->scsw) == 1)
			/* Basic sense hasn't started. Try again. */
			ccw_device_करो_sense(cdev, irb);
		अन्यथा अणु
			CIO_MSG_EVENT(0, "0.%x.%04x: unsolicited "
				      "interrupt during w4sense...\n",
				      cdev->निजी->dev_id.ssid,
				      cdev->निजी->dev_id.devno);
			अगर (cdev->handler)
				cdev->handler (cdev, 0, irb);
		पूर्ण
		वापस;
	पूर्ण
	/*
	 * Check अगर a halt or clear has been issued in the meanजबतक. If yes,
	 * only deliver the halt/clear पूर्णांकerrupt to the device driver as अगर it
	 * had समाप्तed the original request.
	 */
	अगर (scsw_fctl(&irb->scsw) &
	    (SCSW_FCTL_CLEAR_FUNC | SCSW_FCTL_HALT_FUNC)) अणु
		cdev->निजी->flags.करोsense = 0;
		स_रखो(&cdev->निजी->dma_area->irb, 0, माप(काष्ठा irb));
		ccw_device_accumulate_irb(cdev, irb);
		जाओ call_handler;
	पूर्ण
	/* Add basic sense info to irb. */
	ccw_device_accumulate_basic_sense(cdev, irb);
	अगर (cdev->निजी->flags.करोsense) अणु
		/* Another basic sense is needed. */
		ccw_device_करो_sense(cdev, irb);
		वापस;
	पूर्ण
call_handler:
	cdev->निजी->state = DEV_STATE_ONLINE;
	/* In हाल sensing पूर्णांकerfered with setting the device online */
	wake_up(&cdev->निजी->रुको_q);
	/* Call the handler. */
	अगर (ccw_device_call_handler(cdev) && cdev->निजी->flags.करोverअगरy)
		/* Start delayed path verअगरication. */
		ccw_device_online_verअगरy(cdev, 0);
पूर्ण

अटल व्योम
ccw_device_समाप्तing_irq(काष्ठा ccw_device *cdev, क्रमागत dev_event dev_event)
अणु
	ccw_device_set_समयout(cdev, 0);
	/* Start delayed path verअगरication. */
	ccw_device_online_verअगरy(cdev, 0);
	/* OK, i/o is dead now. Call पूर्णांकerrupt handler. */
	अगर (cdev->handler)
		cdev->handler(cdev, cdev->निजी->पूर्णांकparm,
			      ERR_PTR(cdev->निजी->async_समाप्त_io_rc));
पूर्ण

अटल व्योम
ccw_device_समाप्तing_समयout(काष्ठा ccw_device *cdev, क्रमागत dev_event dev_event)
अणु
	पूर्णांक ret;

	ret = ccw_device_cancel_halt_clear(cdev);
	अगर (ret == -EBUSY) अणु
		ccw_device_set_समयout(cdev, 3*HZ);
		वापस;
	पूर्ण
	/* Start delayed path verअगरication. */
	ccw_device_online_verअगरy(cdev, 0);
	अगर (cdev->handler)
		cdev->handler(cdev, cdev->निजी->पूर्णांकparm,
			      ERR_PTR(cdev->निजी->async_समाप्त_io_rc));
पूर्ण

व्योम ccw_device_समाप्त_io(काष्ठा ccw_device *cdev)
अणु
	पूर्णांक ret;

	ccw_device_set_समयout(cdev, 0);
	cdev->निजी->iretry = 255;
	cdev->निजी->async_समाप्त_io_rc = -EIO;
	ret = ccw_device_cancel_halt_clear(cdev);
	अगर (ret == -EBUSY) अणु
		ccw_device_set_समयout(cdev, 3*HZ);
		cdev->निजी->state = DEV_STATE_TIMEOUT_KILL;
		वापस;
	पूर्ण
	/* Start delayed path verअगरication. */
	ccw_device_online_verअगरy(cdev, 0);
	अगर (cdev->handler)
		cdev->handler(cdev, cdev->निजी->पूर्णांकparm,
			      ERR_PTR(-EIO));
पूर्ण

अटल व्योम
ccw_device_delay_verअगरy(काष्ठा ccw_device *cdev, क्रमागत dev_event dev_event)
अणु
	/* Start verअगरication after current task finished. */
	cdev->निजी->flags.करोverअगरy = 1;
पूर्ण

अटल व्योम
ccw_device_start_id(काष्ठा ccw_device *cdev, क्रमागत dev_event dev_event)
अणु
	काष्ठा subchannel *sch;

	sch = to_subchannel(cdev->dev.parent);
	अगर (cio_enable_subchannel(sch, (u32)(addr_t)sch) != 0)
		/* Couldn't enable the subchannel क्रम i/o. Sick device. */
		वापस;
	cdev->निजी->state = DEV_STATE_DISCONNECTED_SENSE_ID;
	ccw_device_sense_id_start(cdev);
पूर्ण

व्योम ccw_device_trigger_reprobe(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch;

	अगर (cdev->निजी->state != DEV_STATE_DISCONNECTED)
		वापस;

	sch = to_subchannel(cdev->dev.parent);
	/* Update some values. */
	अगर (cio_update_schib(sch))
		वापस;
	/*
	 * The pim, pam, pom values may not be accurate, but they are the best
	 * we have beक्रमe perक्रमming device selection :/
	 */
	sch->lpm = sch->schib.pmcw.pam & sch->opm;
	/*
	 * Use the initial configuration since we can't be shure that the old
	 * paths are valid.
	 */
	io_subchannel_init_config(sch);
	अगर (cio_commit_config(sch))
		वापस;

	/* We should also udate ssd info, but this has to रुको. */
	/* Check अगर this is another device which appeared on the same sch. */
	अगर (sch->schib.pmcw.dev != cdev->निजी->dev_id.devno)
		css_schedule_eval(sch->schid);
	अन्यथा
		ccw_device_start_id(cdev, 0);
पूर्ण

अटल व्योम ccw_device_disabled_irq(काष्ठा ccw_device *cdev,
				    क्रमागत dev_event dev_event)
अणु
	काष्ठा subchannel *sch;

	sch = to_subchannel(cdev->dev.parent);
	/*
	 * An पूर्णांकerrupt in a disabled state means a previous disable was not
	 * successful - should not happen, but we try to disable again.
	 */
	cio_disable_subchannel(sch);
पूर्ण

अटल व्योम
ccw_device_change_cmख_स्थितिe(काष्ठा ccw_device *cdev, क्रमागत dev_event dev_event)
अणु
	retry_set_schib(cdev);
	cdev->निजी->state = DEV_STATE_ONLINE;
	dev_fsm_event(cdev, dev_event);
पूर्ण

अटल व्योम ccw_device_update_cmfblock(काष्ठा ccw_device *cdev,
				       क्रमागत dev_event dev_event)
अणु
	cmf_retry_copy_block(cdev);
	cdev->निजी->state = DEV_STATE_ONLINE;
	dev_fsm_event(cdev, dev_event);
पूर्ण

अटल व्योम
ccw_device_quiesce_करोne(काष्ठा ccw_device *cdev, क्रमागत dev_event dev_event)
अणु
	ccw_device_set_समयout(cdev, 0);
	cdev->निजी->state = DEV_STATE_NOT_OPER;
	wake_up(&cdev->निजी->रुको_q);
पूर्ण

अटल व्योम
ccw_device_quiesce_समयout(काष्ठा ccw_device *cdev, क्रमागत dev_event dev_event)
अणु
	पूर्णांक ret;

	ret = ccw_device_cancel_halt_clear(cdev);
	अगर (ret == -EBUSY) अणु
		ccw_device_set_समयout(cdev, HZ/10);
	पूर्ण अन्यथा अणु
		cdev->निजी->state = DEV_STATE_NOT_OPER;
		wake_up(&cdev->निजी->रुको_q);
	पूर्ण
पूर्ण

/*
 * No operation action. This is used e.g. to ignore a समयout event in
 * state offline.
 */
अटल व्योम
ccw_device_nop(काष्ठा ccw_device *cdev, क्रमागत dev_event dev_event)
अणु
पूर्ण

/*
 * device statemachine
 */
fsm_func_t *dev_jumptable[NR_DEV_STATES][NR_DEV_EVENTS] = अणु
	[DEV_STATE_NOT_OPER] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_nop,
		[DEV_EVENT_INTERRUPT]	= ccw_device_disabled_irq,
		[DEV_EVENT_TIMEOUT]	= ccw_device_nop,
		[DEV_EVENT_VERIFY]	= ccw_device_nop,
	पूर्ण,
	[DEV_STATE_SENSE_ID] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_request_event,
		[DEV_EVENT_INTERRUPT]	= ccw_device_request_event,
		[DEV_EVENT_TIMEOUT]	= ccw_device_request_event,
		[DEV_EVENT_VERIFY]	= ccw_device_nop,
	पूर्ण,
	[DEV_STATE_OFFLINE] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_generic_notoper,
		[DEV_EVENT_INTERRUPT]	= ccw_device_disabled_irq,
		[DEV_EVENT_TIMEOUT]	= ccw_device_nop,
		[DEV_EVENT_VERIFY]	= ccw_device_offline_verअगरy,
	पूर्ण,
	[DEV_STATE_VERIFY] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_request_event,
		[DEV_EVENT_INTERRUPT]	= ccw_device_request_event,
		[DEV_EVENT_TIMEOUT]	= ccw_device_request_event,
		[DEV_EVENT_VERIFY]	= ccw_device_delay_verअगरy,
	पूर्ण,
	[DEV_STATE_ONLINE] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_generic_notoper,
		[DEV_EVENT_INTERRUPT]	= ccw_device_irq,
		[DEV_EVENT_TIMEOUT]	= ccw_device_online_समयout,
		[DEV_EVENT_VERIFY]	= ccw_device_online_verअगरy,
	पूर्ण,
	[DEV_STATE_W4SENSE] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_generic_notoper,
		[DEV_EVENT_INTERRUPT]	= ccw_device_w4sense,
		[DEV_EVENT_TIMEOUT]	= ccw_device_nop,
		[DEV_EVENT_VERIFY]	= ccw_device_online_verअगरy,
	पूर्ण,
	[DEV_STATE_DISBAND_PGID] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_request_event,
		[DEV_EVENT_INTERRUPT]	= ccw_device_request_event,
		[DEV_EVENT_TIMEOUT]	= ccw_device_request_event,
		[DEV_EVENT_VERIFY]	= ccw_device_nop,
	पूर्ण,
	[DEV_STATE_BOXED] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_generic_notoper,
		[DEV_EVENT_INTERRUPT]	= ccw_device_nop,
		[DEV_EVENT_TIMEOUT]	= ccw_device_nop,
		[DEV_EVENT_VERIFY]	= ccw_device_boxed_verअगरy,
	पूर्ण,
	/* states to रुको क्रम i/o completion beक्रमe करोing something */
	[DEV_STATE_TIMEOUT_KILL] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_generic_notoper,
		[DEV_EVENT_INTERRUPT]	= ccw_device_समाप्तing_irq,
		[DEV_EVENT_TIMEOUT]	= ccw_device_समाप्तing_समयout,
		[DEV_EVENT_VERIFY]	= ccw_device_nop, //FIXME
	पूर्ण,
	[DEV_STATE_QUIESCE] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_quiesce_करोne,
		[DEV_EVENT_INTERRUPT]	= ccw_device_quiesce_करोne,
		[DEV_EVENT_TIMEOUT]	= ccw_device_quiesce_समयout,
		[DEV_EVENT_VERIFY]	= ccw_device_nop,
	पूर्ण,
	/* special states क्रम devices gone not operational */
	[DEV_STATE_DISCONNECTED] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_nop,
		[DEV_EVENT_INTERRUPT]	= ccw_device_start_id,
		[DEV_EVENT_TIMEOUT]	= ccw_device_nop,
		[DEV_EVENT_VERIFY]	= ccw_device_start_id,
	पूर्ण,
	[DEV_STATE_DISCONNECTED_SENSE_ID] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_request_event,
		[DEV_EVENT_INTERRUPT]	= ccw_device_request_event,
		[DEV_EVENT_TIMEOUT]	= ccw_device_request_event,
		[DEV_EVENT_VERIFY]	= ccw_device_nop,
	पूर्ण,
	[DEV_STATE_CMFCHANGE] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_change_cmख_स्थितिe,
		[DEV_EVENT_INTERRUPT]	= ccw_device_change_cmख_स्थितिe,
		[DEV_EVENT_TIMEOUT]	= ccw_device_change_cmख_स्थितिe,
		[DEV_EVENT_VERIFY]	= ccw_device_change_cmख_स्थितिe,
	पूर्ण,
	[DEV_STATE_CMFUPDATE] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_update_cmfblock,
		[DEV_EVENT_INTERRUPT]	= ccw_device_update_cmfblock,
		[DEV_EVENT_TIMEOUT]	= ccw_device_update_cmfblock,
		[DEV_EVENT_VERIFY]	= ccw_device_update_cmfblock,
	पूर्ण,
	[DEV_STATE_STEAL_LOCK] = अणु
		[DEV_EVENT_NOTOPER]	= ccw_device_request_event,
		[DEV_EVENT_INTERRUPT]	= ccw_device_request_event,
		[DEV_EVENT_TIMEOUT]	= ccw_device_request_event,
		[DEV_EVENT_VERIFY]	= ccw_device_nop,
	पूर्ण,
पूर्ण;

EXPORT_SYMBOL_GPL(ccw_device_set_समयout);
