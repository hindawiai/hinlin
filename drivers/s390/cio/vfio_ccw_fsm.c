<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Finite state machine क्रम vfio-ccw device handling
 *
 * Copyright IBM Corp. 2017
 * Copyright Red Hat, Inc. 2019
 *
 * Author(s): Dong Jia Shi <bjsdjshi@linux.vnet.ibm.com>
 *            Cornelia Huck <cohuck@redhat.com>
 */

#समावेश <linux/vfपन.स>
#समावेश <linux/mdev.h>

#समावेश "ioasm.h"
#समावेश "vfio_ccw_private.h"

अटल पूर्णांक fsm_io_helper(काष्ठा vfio_ccw_निजी *निजी)
अणु
	काष्ठा subchannel *sch;
	जोड़ orb *orb;
	पूर्णांक ccode;
	__u8 lpm;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	sch = निजी->sch;

	spin_lock_irqsave(sch->lock, flags);

	orb = cp_get_orb(&निजी->cp, (u32)(addr_t)sch, sch->lpm);
	अगर (!orb) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	VFIO_CCW_TRACE_EVENT(5, "stIO");
	VFIO_CCW_TRACE_EVENT(5, dev_name(&sch->dev));

	/* Issue "Start Subchannel" */
	ccode = ssch(sch->schid, orb);

	VFIO_CCW_HEX_EVENT(5, &ccode, माप(ccode));

	चयन (ccode) अणु
	हाल 0:
		/*
		 * Initialize device status inक्रमmation
		 */
		sch->schib.scsw.cmd.actl |= SCSW_ACTL_START_PEND;
		ret = 0;
		निजी->state = VFIO_CCW_STATE_CP_PENDING;
		अवरोध;
	हाल 1:		/* Status pending */
	हाल 2:		/* Busy */
		ret = -EBUSY;
		अवरोध;
	हाल 3:		/* Device/path not operational */
	अणु
		lpm = orb->cmd.lpm;
		अगर (lpm != 0)
			sch->lpm &= ~lpm;
		अन्यथा
			sch->lpm = 0;

		अगर (cio_update_schib(sch))
			ret = -ENODEV;
		अन्यथा
			ret = sch->lpm ? -EACCES : -ENODEV;
		अवरोध;
	पूर्ण
	शेष:
		ret = ccode;
	पूर्ण
out:
	spin_unlock_irqrestore(sch->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक fsm_करो_halt(काष्ठा vfio_ccw_निजी *निजी)
अणु
	काष्ठा subchannel *sch;
	अचिन्हित दीर्घ flags;
	पूर्णांक ccode;
	पूर्णांक ret;

	sch = निजी->sch;

	spin_lock_irqsave(sch->lock, flags);

	VFIO_CCW_TRACE_EVENT(2, "haltIO");
	VFIO_CCW_TRACE_EVENT(2, dev_name(&sch->dev));

	/* Issue "Halt Subchannel" */
	ccode = hsch(sch->schid);

	VFIO_CCW_HEX_EVENT(2, &ccode, माप(ccode));

	चयन (ccode) अणु
	हाल 0:
		/*
		 * Initialize device status inक्रमmation
		 */
		sch->schib.scsw.cmd.actl |= SCSW_ACTL_HALT_PEND;
		ret = 0;
		अवरोध;
	हाल 1:		/* Status pending */
	हाल 2:		/* Busy */
		ret = -EBUSY;
		अवरोध;
	हाल 3:		/* Device not operational */
		ret = -ENODEV;
		अवरोध;
	शेष:
		ret = ccode;
	पूर्ण
	spin_unlock_irqrestore(sch->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक fsm_करो_clear(काष्ठा vfio_ccw_निजी *निजी)
अणु
	काष्ठा subchannel *sch;
	अचिन्हित दीर्घ flags;
	पूर्णांक ccode;
	पूर्णांक ret;

	sch = निजी->sch;

	spin_lock_irqsave(sch->lock, flags);

	VFIO_CCW_TRACE_EVENT(2, "clearIO");
	VFIO_CCW_TRACE_EVENT(2, dev_name(&sch->dev));

	/* Issue "Clear Subchannel" */
	ccode = csch(sch->schid);

	VFIO_CCW_HEX_EVENT(2, &ccode, माप(ccode));

	चयन (ccode) अणु
	हाल 0:
		/*
		 * Initialize device status inक्रमmation
		 */
		sch->schib.scsw.cmd.actl = SCSW_ACTL_CLEAR_PEND;
		/* TODO: check what अन्यथा we might need to clear */
		ret = 0;
		अवरोध;
	हाल 3:		/* Device not operational */
		ret = -ENODEV;
		अवरोध;
	शेष:
		ret = ccode;
	पूर्ण
	spin_unlock_irqrestore(sch->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम fsm_notoper(काष्ठा vfio_ccw_निजी *निजी,
			क्रमागत vfio_ccw_event event)
अणु
	काष्ठा subchannel *sch = निजी->sch;

	VFIO_CCW_TRACE_EVENT(2, "notoper");
	VFIO_CCW_TRACE_EVENT(2, dev_name(&sch->dev));

	/*
	 * TODO:
	 * Probably we should send the machine check to the guest.
	 */
	css_sched_sch_toकरो(sch, SCH_TODO_UNREG);
	निजी->state = VFIO_CCW_STATE_NOT_OPER;
पूर्ण

/*
 * No operation action.
 */
अटल व्योम fsm_nop(काष्ठा vfio_ccw_निजी *निजी,
		    क्रमागत vfio_ccw_event event)
अणु
पूर्ण

अटल व्योम fsm_io_error(काष्ठा vfio_ccw_निजी *निजी,
			 क्रमागत vfio_ccw_event event)
अणु
	pr_err("vfio-ccw: FSM: I/O request from state:%d\n", निजी->state);
	निजी->io_region->ret_code = -EIO;
पूर्ण

अटल व्योम fsm_io_busy(काष्ठा vfio_ccw_निजी *निजी,
			क्रमागत vfio_ccw_event event)
अणु
	निजी->io_region->ret_code = -EBUSY;
पूर्ण

अटल व्योम fsm_io_retry(काष्ठा vfio_ccw_निजी *निजी,
			 क्रमागत vfio_ccw_event event)
अणु
	निजी->io_region->ret_code = -EAGAIN;
पूर्ण

अटल व्योम fsm_async_error(काष्ठा vfio_ccw_निजी *निजी,
			    क्रमागत vfio_ccw_event event)
अणु
	काष्ठा ccw_cmd_region *cmd_region = निजी->cmd_region;

	pr_err("vfio-ccw: FSM: %s request from state:%d\n",
	       cmd_region->command == VFIO_CCW_ASYNC_CMD_HSCH ? "halt" :
	       cmd_region->command == VFIO_CCW_ASYNC_CMD_CSCH ? "clear" :
	       "<unknown>", निजी->state);
	cmd_region->ret_code = -EIO;
पूर्ण

अटल व्योम fsm_async_retry(काष्ठा vfio_ccw_निजी *निजी,
			    क्रमागत vfio_ccw_event event)
अणु
	निजी->cmd_region->ret_code = -EAGAIN;
पूर्ण

अटल व्योम fsm_disabled_irq(काष्ठा vfio_ccw_निजी *निजी,
			     क्रमागत vfio_ccw_event event)
अणु
	काष्ठा subchannel *sch = निजी->sch;

	/*
	 * An पूर्णांकerrupt in a disabled state means a previous disable was not
	 * successful - should not happen, but we try to disable again.
	 */
	cio_disable_subchannel(sch);
पूर्ण
अंतरभूत काष्ठा subchannel_id get_schid(काष्ठा vfio_ccw_निजी *p)
अणु
	वापस p->sch->schid;
पूर्ण

/*
 * Deal with the ccw command request from the userspace.
 */
अटल व्योम fsm_io_request(काष्ठा vfio_ccw_निजी *निजी,
			   क्रमागत vfio_ccw_event event)
अणु
	जोड़ orb *orb;
	जोड़ scsw *scsw = &निजी->scsw;
	काष्ठा ccw_io_region *io_region = निजी->io_region;
	काष्ठा mdev_device *mdev = निजी->mdev;
	अक्षर *errstr = "request";
	काष्ठा subchannel_id schid = get_schid(निजी);

	निजी->state = VFIO_CCW_STATE_CP_PROCESSING;
	स_नकल(scsw, io_region->scsw_area, माप(*scsw));

	अगर (scsw->cmd.fctl & SCSW_FCTL_START_FUNC) अणु
		orb = (जोड़ orb *)io_region->orb_area;

		/* Don't try to build a cp अगर transport mode is specअगरied. */
		अगर (orb->पंचांग.b) अणु
			io_region->ret_code = -EOPNOTSUPP;
			VFIO_CCW_MSG_EVENT(2,
					   "%pUl (%x.%x.%04x): transport mode\n",
					   mdev_uuid(mdev), schid.cssid,
					   schid.ssid, schid.sch_no);
			errstr = "transport mode";
			जाओ err_out;
		पूर्ण
		io_region->ret_code = cp_init(&निजी->cp, mdev_dev(mdev),
					      orb);
		अगर (io_region->ret_code) अणु
			VFIO_CCW_MSG_EVENT(2,
					   "%pUl (%x.%x.%04x): cp_init=%d\n",
					   mdev_uuid(mdev), schid.cssid,
					   schid.ssid, schid.sch_no,
					   io_region->ret_code);
			errstr = "cp init";
			जाओ err_out;
		पूर्ण

		io_region->ret_code = cp_prefetch(&निजी->cp);
		अगर (io_region->ret_code) अणु
			VFIO_CCW_MSG_EVENT(2,
					   "%pUl (%x.%x.%04x): cp_prefetch=%d\n",
					   mdev_uuid(mdev), schid.cssid,
					   schid.ssid, schid.sch_no,
					   io_region->ret_code);
			errstr = "cp prefetch";
			cp_मुक्त(&निजी->cp);
			जाओ err_out;
		पूर्ण

		/* Start channel program and रुको क्रम I/O पूर्णांकerrupt. */
		io_region->ret_code = fsm_io_helper(निजी);
		अगर (io_region->ret_code) अणु
			VFIO_CCW_MSG_EVENT(2,
					   "%pUl (%x.%x.%04x): fsm_io_helper=%d\n",
					   mdev_uuid(mdev), schid.cssid,
					   schid.ssid, schid.sch_no,
					   io_region->ret_code);
			errstr = "cp fsm_io_helper";
			cp_मुक्त(&निजी->cp);
			जाओ err_out;
		पूर्ण
		वापस;
	पूर्ण अन्यथा अगर (scsw->cmd.fctl & SCSW_FCTL_HALT_FUNC) अणु
		VFIO_CCW_MSG_EVENT(2,
				   "%pUl (%x.%x.%04x): halt on io_region\n",
				   mdev_uuid(mdev), schid.cssid,
				   schid.ssid, schid.sch_no);
		/* halt is handled via the async cmd region */
		io_region->ret_code = -EOPNOTSUPP;
		जाओ err_out;
	पूर्ण अन्यथा अगर (scsw->cmd.fctl & SCSW_FCTL_CLEAR_FUNC) अणु
		VFIO_CCW_MSG_EVENT(2,
				   "%pUl (%x.%x.%04x): clear on io_region\n",
				   mdev_uuid(mdev), schid.cssid,
				   schid.ssid, schid.sch_no);
		/* clear is handled via the async cmd region */
		io_region->ret_code = -EOPNOTSUPP;
		जाओ err_out;
	पूर्ण

err_out:
	निजी->state = VFIO_CCW_STATE_IDLE;
	trace_vfio_ccw_fsm_io_request(scsw->cmd.fctl, schid,
				      io_region->ret_code, errstr);
पूर्ण

/*
 * Deal with an async request from userspace.
 */
अटल व्योम fsm_async_request(काष्ठा vfio_ccw_निजी *निजी,
			      क्रमागत vfio_ccw_event event)
अणु
	काष्ठा ccw_cmd_region *cmd_region = निजी->cmd_region;

	चयन (cmd_region->command) अणु
	हाल VFIO_CCW_ASYNC_CMD_HSCH:
		cmd_region->ret_code = fsm_करो_halt(निजी);
		अवरोध;
	हाल VFIO_CCW_ASYNC_CMD_CSCH:
		cmd_region->ret_code = fsm_करो_clear(निजी);
		अवरोध;
	शेष:
		/* should not happen? */
		cmd_region->ret_code = -EINVAL;
	पूर्ण

	trace_vfio_ccw_fsm_async_request(get_schid(निजी),
					 cmd_region->command,
					 cmd_region->ret_code);
पूर्ण

/*
 * Got an पूर्णांकerrupt क्रम a normal io (state busy).
 */
अटल व्योम fsm_irq(काष्ठा vfio_ccw_निजी *निजी,
		    क्रमागत vfio_ccw_event event)
अणु
	काष्ठा irb *irb = this_cpu_ptr(&cio_irb);

	VFIO_CCW_TRACE_EVENT(6, "IRQ");
	VFIO_CCW_TRACE_EVENT(6, dev_name(&निजी->sch->dev));

	स_नकल(&निजी->irb, irb, माप(*irb));

	queue_work(vfio_ccw_work_q, &निजी->io_work);

	अगर (निजी->completion)
		complete(निजी->completion);
पूर्ण

/*
 * Device statemachine
 */
fsm_func_t *vfio_ccw_jumptable[NR_VFIO_CCW_STATES][NR_VFIO_CCW_EVENTS] = अणु
	[VFIO_CCW_STATE_NOT_OPER] = अणु
		[VFIO_CCW_EVENT_NOT_OPER]	= fsm_nop,
		[VFIO_CCW_EVENT_IO_REQ]		= fsm_io_error,
		[VFIO_CCW_EVENT_ASYNC_REQ]	= fsm_async_error,
		[VFIO_CCW_EVENT_INTERRUPT]	= fsm_disabled_irq,
	पूर्ण,
	[VFIO_CCW_STATE_STANDBY] = अणु
		[VFIO_CCW_EVENT_NOT_OPER]	= fsm_notoper,
		[VFIO_CCW_EVENT_IO_REQ]		= fsm_io_error,
		[VFIO_CCW_EVENT_ASYNC_REQ]	= fsm_async_error,
		[VFIO_CCW_EVENT_INTERRUPT]	= fsm_irq,
	पूर्ण,
	[VFIO_CCW_STATE_IDLE] = अणु
		[VFIO_CCW_EVENT_NOT_OPER]	= fsm_notoper,
		[VFIO_CCW_EVENT_IO_REQ]		= fsm_io_request,
		[VFIO_CCW_EVENT_ASYNC_REQ]	= fsm_async_request,
		[VFIO_CCW_EVENT_INTERRUPT]	= fsm_irq,
	पूर्ण,
	[VFIO_CCW_STATE_CP_PROCESSING] = अणु
		[VFIO_CCW_EVENT_NOT_OPER]	= fsm_notoper,
		[VFIO_CCW_EVENT_IO_REQ]		= fsm_io_retry,
		[VFIO_CCW_EVENT_ASYNC_REQ]	= fsm_async_retry,
		[VFIO_CCW_EVENT_INTERRUPT]	= fsm_irq,
	पूर्ण,
	[VFIO_CCW_STATE_CP_PENDING] = अणु
		[VFIO_CCW_EVENT_NOT_OPER]	= fsm_notoper,
		[VFIO_CCW_EVENT_IO_REQ]		= fsm_io_busy,
		[VFIO_CCW_EVENT_ASYNC_REQ]	= fsm_async_request,
		[VFIO_CCW_EVENT_INTERRUPT]	= fsm_irq,
	पूर्ण,
पूर्ण;
