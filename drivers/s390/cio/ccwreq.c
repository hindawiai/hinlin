<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Handling of पूर्णांकernal CCW device requests.
 *
 *    Copyright IBM Corp. 2009, 2011
 *    Author(s): Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "cio"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/cपन.स>

#समावेश "io_sch.h"
#समावेश "cio.h"
#समावेश "device.h"
#समावेश "cio_debug.h"

/**
 * lpm_adjust - adjust path mask
 * @lpm: path mask to adjust
 * @mask: mask of available paths
 *
 * Shअगरt @lpm right until @lpm and @mask have at least one bit in common or
 * until @lpm is zero. Return the resulting lpm.
 */
पूर्णांक lpm_adjust(पूर्णांक lpm, पूर्णांक mask)
अणु
	जबतक (lpm && ((lpm & mask) == 0))
		lpm >>= 1;
	वापस lpm;
पूर्ण

/*
 * Adjust path mask to use next path and reset retry count. Return resulting
 * path mask.
 */
अटल u16 ccwreq_next_path(काष्ठा ccw_device *cdev)
अणु
	काष्ठा ccw_request *req = &cdev->निजी->req;

	अगर (!req->singlepath) अणु
		req->mask = 0;
		जाओ out;
	पूर्ण
	req->retries	= req->maxretries;
	req->mask	= lpm_adjust(req->mask >> 1, req->lpm);
out:
	वापस req->mask;
पूर्ण

/*
 * Clean up device state and report to callback.
 */
अटल व्योम ccwreq_stop(काष्ठा ccw_device *cdev, पूर्णांक rc)
अणु
	काष्ठा ccw_request *req = &cdev->निजी->req;

	अगर (req->करोne)
		वापस;
	req->करोne = 1;
	ccw_device_set_समयout(cdev, 0);
	स_रखो(&cdev->निजी->dma_area->irb, 0, माप(काष्ठा irb));
	अगर (rc && rc != -ENODEV && req->drc)
		rc = req->drc;
	req->callback(cdev, req->data, rc);
पूर्ण

/*
 * (Re-)Start the operation until retries and paths are exhausted.
 */
अटल व्योम ccwreq_करो(काष्ठा ccw_device *cdev)
अणु
	काष्ठा ccw_request *req = &cdev->निजी->req;
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw1 *cp = req->cp;
	पूर्णांक rc = -EACCES;

	जबतक (req->mask) अणु
		अगर (req->retries-- == 0) अणु
			/* Retries exhausted, try next path. */
			ccwreq_next_path(cdev);
			जारी;
		पूर्ण
		/* Perक्रमm start function. */
		स_रखो(&cdev->निजी->dma_area->irb, 0, माप(काष्ठा irb));
		rc = cio_start(sch, cp, (u8) req->mask);
		अगर (rc == 0) अणु
			/* I/O started successfully. */
			ccw_device_set_समयout(cdev, req->समयout);
			वापस;
		पूर्ण
		अगर (rc == -ENODEV) अणु
			/* Permanent device error. */
			अवरोध;
		पूर्ण
		अगर (rc == -EACCES) अणु
			/* Permant path error. */
			ccwreq_next_path(cdev);
			जारी;
		पूर्ण
		/* Temporary improper status. */
		rc = cio_clear(sch);
		अगर (rc)
			अवरोध;
		वापस;
	पूर्ण
	ccwreq_stop(cdev, rc);
पूर्ण

/**
 * ccw_request_start - perक्रमm I/O request
 * @cdev: ccw device
 *
 * Perक्रमm the I/O request specअगरied by cdev->req.
 */
व्योम ccw_request_start(काष्ठा ccw_device *cdev)
अणु
	काष्ठा ccw_request *req = &cdev->निजी->req;

	अगर (req->singlepath) अणु
		/* Try all paths twice to counter link flapping. */
		req->mask = 0x8080;
	पूर्ण अन्यथा
		req->mask = req->lpm;

	req->retries	= req->maxretries;
	req->mask	= lpm_adjust(req->mask, req->lpm);
	req->drc	= 0;
	req->करोne	= 0;
	req->cancel	= 0;
	अगर (!req->mask)
		जाओ out_nopath;
	ccwreq_करो(cdev);
	वापस;

out_nopath:
	ccwreq_stop(cdev, -EACCES);
पूर्ण

/**
 * ccw_request_cancel - cancel running I/O request
 * @cdev: ccw device
 *
 * Cancel the I/O request specअगरied by cdev->req. Return non-zero अगर request
 * has alपढ़ोy finished, zero otherwise.
 */
पूर्णांक ccw_request_cancel(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw_request *req = &cdev->निजी->req;
	पूर्णांक rc;

	अगर (req->करोne)
		वापस 1;
	req->cancel = 1;
	rc = cio_clear(sch);
	अगर (rc)
		ccwreq_stop(cdev, rc);
	वापस 0;
पूर्ण

/*
 * Return the status of the पूर्णांकernal I/O started on the specअगरied ccw device.
 * Perक्रमm BASIC SENSE अगर required.
 */
अटल क्रमागत io_status ccwreq_status(काष्ठा ccw_device *cdev, काष्ठा irb *lcirb)
अणु
	काष्ठा irb *irb = &cdev->निजी->dma_area->irb;
	काष्ठा cmd_scsw *scsw = &irb->scsw.cmd;
	क्रमागत uc_toकरो toकरो;

	/* Perक्रमm BASIC SENSE अगर needed. */
	अगर (ccw_device_accumulate_and_sense(cdev, lcirb))
		वापस IO_RUNNING;
	/* Check क्रम halt/clear पूर्णांकerrupt. */
	अगर (scsw->fctl & (SCSW_FCTL_HALT_FUNC | SCSW_FCTL_CLEAR_FUNC))
		वापस IO_KILLED;
	/* Check क्रम path error. */
	अगर (scsw->cc == 3 || scsw->pno)
		वापस IO_PATH_ERROR;
	/* Handle BASIC SENSE data. */
	अगर (irb->esw.esw0.erw.cons) अणु
		CIO_TRACE_EVENT(2, "sensedata");
		CIO_HEX_EVENT(2, &cdev->निजी->dev_id,
			      माप(काष्ठा ccw_dev_id));
		CIO_HEX_EVENT(2, &cdev->निजी->dma_area->irb.ecw,
			      SENSE_MAX_COUNT);
		/* Check क्रम command reject. */
		अगर (irb->ecw[0] & SNS0_CMD_REJECT)
			वापस IO_REJECTED;
		/* Ask the driver what to करो */
		अगर (cdev->drv && cdev->drv->uc_handler) अणु
			toकरो = cdev->drv->uc_handler(cdev, lcirb);
			CIO_TRACE_EVENT(2, "uc_response");
			CIO_HEX_EVENT(2, &toकरो, माप(toकरो));
			चयन (toकरो) अणु
			हाल UC_TODO_RETRY:
				वापस IO_STATUS_ERROR;
			हाल UC_TODO_RETRY_ON_NEW_PATH:
				वापस IO_PATH_ERROR;
			हाल UC_TODO_STOP:
				वापस IO_REJECTED;
			शेष:
				वापस IO_STATUS_ERROR;
			पूर्ण
		पूर्ण
		/* Assume that unexpected SENSE data implies an error. */
		वापस IO_STATUS_ERROR;
	पूर्ण
	/* Check क्रम channel errors. */
	अगर (scsw->cstat != 0)
		वापस IO_STATUS_ERROR;
	/* Check क्रम device errors. */
	अगर (scsw->dstat & ~(DEV_STAT_CHN_END | DEV_STAT_DEV_END))
		वापस IO_STATUS_ERROR;
	/* Check क्रम final state. */
	अगर (!(scsw->dstat & DEV_STAT_DEV_END))
		वापस IO_RUNNING;
	/* Check क्रम other improper status. */
	अगर (scsw->cc == 1 && (scsw->stctl & SCSW_STCTL_ALERT_STATUS))
		वापस IO_STATUS_ERROR;
	वापस IO_DONE;
पूर्ण

/*
 * Log ccw request status.
 */
अटल व्योम ccwreq_log_status(काष्ठा ccw_device *cdev, क्रमागत io_status status)
अणु
	काष्ठा ccw_request *req = &cdev->निजी->req;
	काष्ठा अणु
		काष्ठा ccw_dev_id dev_id;
		u16 retries;
		u8 lpm;
		u8 status;
	पूर्ण  __attribute__ ((packed)) data;
	data.dev_id	= cdev->निजी->dev_id;
	data.retries	= req->retries;
	data.lpm	= (u8) req->mask;
	data.status	= (u8) status;
	CIO_TRACE_EVENT(2, "reqstat");
	CIO_HEX_EVENT(2, &data, माप(data));
पूर्ण

/**
 * ccw_request_handler - पूर्णांकerrupt handler क्रम I/O request procedure.
 * @cdev: ccw device
 *
 * Handle पूर्णांकerrupt during I/O request procedure.
 */
व्योम ccw_request_handler(काष्ठा ccw_device *cdev)
अणु
	काष्ठा irb *irb = this_cpu_ptr(&cio_irb);
	काष्ठा ccw_request *req = &cdev->निजी->req;
	क्रमागत io_status status;
	पूर्णांक rc = -EOPNOTSUPP;

	/* Check status of I/O request. */
	status = ccwreq_status(cdev, irb);
	अगर (req->filter)
		status = req->filter(cdev, req->data, irb, status);
	अगर (status != IO_RUNNING)
		ccw_device_set_समयout(cdev, 0);
	अगर (status != IO_DONE && status != IO_RUNNING)
		ccwreq_log_status(cdev, status);
	चयन (status) अणु
	हाल IO_DONE:
		अवरोध;
	हाल IO_RUNNING:
		वापस;
	हाल IO_REJECTED:
		जाओ err;
	हाल IO_PATH_ERROR:
		जाओ out_next_path;
	हाल IO_STATUS_ERROR:
		जाओ out_restart;
	हाल IO_KILLED:
		/* Check अगर request was cancelled on purpose. */
		अगर (req->cancel) अणु
			rc = -EIO;
			जाओ err;
		पूर्ण
		जाओ out_restart;
	पूर्ण
	/* Check back with request initiator. */
	अगर (!req->check)
		जाओ out;
	चयन (req->check(cdev, req->data)) अणु
	हाल 0:
		अवरोध;
	हाल -EAGAIN:
		जाओ out_restart;
	हाल -EACCES:
		जाओ out_next_path;
	शेष:
		जाओ err;
	पूर्ण
out:
	ccwreq_stop(cdev, 0);
	वापस;

out_next_path:
	/* Try next path and restart I/O. */
	अगर (!ccwreq_next_path(cdev)) अणु
		rc = -EACCES;
		जाओ err;
	पूर्ण
out_restart:
	/* Restart. */
	ccwreq_करो(cdev);
	वापस;
err:
	ccwreq_stop(cdev, rc);
पूर्ण


/**
 * ccw_request_समयout - समयout handler क्रम I/O request procedure
 * @cdev: ccw device
 *
 * Handle समयout during I/O request procedure.
 */
व्योम ccw_request_समयout(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw_request *req = &cdev->निजी->req;
	पूर्णांक rc = -ENODEV, chp;

	अगर (cio_update_schib(sch))
		जाओ err;

	क्रम (chp = 0; chp < 8; chp++) अणु
		अगर ((0x80 >> chp) & sch->schib.pmcw.lpum)
			pr_warn("%s: No interrupt was received within %lus (CS=%02x, DS=%02x, CHPID=%x.%02x)\n",
				dev_name(&cdev->dev), req->समयout / HZ,
				scsw_cstat(&sch->schib.scsw),
				scsw_dstat(&sch->schib.scsw),
				sch->schid.cssid,
				sch->schib.pmcw.chpid[chp]);
	पूर्ण

	अगर (!ccwreq_next_path(cdev)) अणु
		/* set the final वापस code क्रम this request */
		req->drc = -ETIME;
	पूर्ण
	rc = cio_clear(sch);
	अगर (rc)
		जाओ err;
	वापस;

err:
	ccwreq_stop(cdev, rc);
पूर्ण

/**
 * ccw_request_notoper - notoper handler क्रम I/O request procedure
 * @cdev: ccw device
 *
 * Handle notoper during I/O request procedure.
 */
व्योम ccw_request_notoper(काष्ठा ccw_device *cdev)
अणु
	ccwreq_stop(cdev, -ENODEV);
पूर्ण
