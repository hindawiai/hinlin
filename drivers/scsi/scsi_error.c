<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  scsi_error.c Copyright (C) 1997 Eric Youngdale
 *
 *  SCSI error/समयout handling
 *      Initial versions: Eric Youngdale.  Based upon conversations with
 *                        Leonard Zubkoff and David Miller at Linux Expo,
 *                        ideas originating from all over the place.
 *
 *	Reकाष्ठाured scsi_unjam_host and associated functions.
 *	September 04, 2002 Mike Anderson (andmike@us.ibm.com)
 *
 *	Forward port of Russell King's (rmk@arm.linux.org.uk) changes and
 *	minor cleanups.
 *	September 30, 2002 Mike Anderson (andmike@us.ibm.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/gfp.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_common.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_ioctl.h>
#समावेश <scsi/scsi_dh.h>
#समावेश <scsi/scsi_devinfo.h>
#समावेश <scsi/sg.h>

#समावेश "scsi_priv.h"
#समावेश "scsi_logging.h"
#समावेश "scsi_transport_api.h"

#समावेश <trace/events/scsi.h>

#समावेश <यंत्र/unaligned.h>

अटल व्योम scsi_eh_करोne(काष्ठा scsi_cmnd *scmd);

/*
 * These should *probably* be handled by the host itself.
 * Since it is allowed to sleep, it probably should.
 */
#घोषणा BUS_RESET_SETTLE_TIME   (10)
#घोषणा HOST_RESET_SETTLE_TIME  (10)

अटल पूर्णांक scsi_eh_try_stu(काष्ठा scsi_cmnd *scmd);
अटल क्रमागत scsi_disposition scsi_try_to_पात_cmd(काष्ठा scsi_host_ढाँचा *,
						   काष्ठा scsi_cmnd *);

व्योम scsi_eh_wakeup(काष्ठा Scsi_Host *shost)
अणु
	lockdep_निश्चित_held(shost->host_lock);

	अगर (scsi_host_busy(shost) == shost->host_failed) अणु
		trace_scsi_eh_wakeup(shost);
		wake_up_process(shost->ehandler);
		SCSI_LOG_ERROR_RECOVERY(5, shost_prपूर्णांकk(KERN_INFO, shost,
			"Waking error handler thread\n"));
	पूर्ण
पूर्ण

/**
 * scsi_schedule_eh - schedule EH क्रम SCSI host
 * @shost:	SCSI host to invoke error handling on.
 *
 * Schedule SCSI EH without scmd.
 */
व्योम scsi_schedule_eh(काष्ठा Scsi_Host *shost)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);

	अगर (scsi_host_set_state(shost, SHOST_RECOVERY) == 0 ||
	    scsi_host_set_state(shost, SHOST_CANCEL_RECOVERY) == 0) अणु
		shost->host_eh_scheduled++;
		scsi_eh_wakeup(shost);
	पूर्ण

	spin_unlock_irqrestore(shost->host_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(scsi_schedule_eh);

अटल पूर्णांक scsi_host_eh_past_deadline(काष्ठा Scsi_Host *shost)
अणु
	अगर (!shost->last_reset || shost->eh_deadline == -1)
		वापस 0;

	/*
	 * 32bit accesses are guaranteed to be atomic
	 * (on all supported architectures), so instead
	 * of using a spinlock we can as well द्विगुन check
	 * अगर eh_deadline has been set to 'off' during the
	 * समय_beक्रमe call.
	 */
	अगर (समय_beक्रमe(jअगरfies, shost->last_reset + shost->eh_deadline) &&
	    shost->eh_deadline > -1)
		वापस 0;

	वापस 1;
पूर्ण

अटल bool scsi_cmd_retry_allowed(काष्ठा scsi_cmnd *cmd)
अणु
	अगर (cmd->allowed == SCSI_CMD_RETRIES_NO_LIMIT)
		वापस true;

	वापस ++cmd->retries <= cmd->allowed;
पूर्ण

अटल bool scsi_eh_should_retry_cmd(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_device *sdev = cmd->device;
	काष्ठा Scsi_Host *host = sdev->host;

	अगर (host->hostt->eh_should_retry_cmd)
		वापस  host->hostt->eh_should_retry_cmd(cmd);

	वापस true;
पूर्ण

/**
 * scmd_eh_पात_handler - Handle command पातs
 * @work:	command to be पातed.
 *
 * Note: this function must be called only क्रम a command that has समयd out.
 * Because the block layer marks a request as complete beक्रमe it calls
 * scsi_बार_out(), a .scsi_करोne() call from the LLD क्रम a command that has
 * समयd out करो not have any effect. Hence it is safe to call
 * scsi_finish_command() from this function.
 */
व्योम
scmd_eh_पात_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा scsi_cmnd *scmd =
		container_of(work, काष्ठा scsi_cmnd, पात_work.work);
	काष्ठा scsi_device *sdev = scmd->device;
	क्रमागत scsi_disposition rtn;

	अगर (scsi_host_eh_past_deadline(sdev->host)) अणु
		SCSI_LOG_ERROR_RECOVERY(3,
			scmd_prपूर्णांकk(KERN_INFO, scmd,
				    "eh timeout, not aborting\n"));
	पूर्ण अन्यथा अणु
		SCSI_LOG_ERROR_RECOVERY(3,
			scmd_prपूर्णांकk(KERN_INFO, scmd,
				    "aborting command\n"));
		rtn = scsi_try_to_पात_cmd(sdev->host->hostt, scmd);
		अगर (rtn == SUCCESS) अणु
			set_host_byte(scmd, DID_TIME_OUT);
			अगर (scsi_host_eh_past_deadline(sdev->host)) अणु
				SCSI_LOG_ERROR_RECOVERY(3,
					scmd_prपूर्णांकk(KERN_INFO, scmd,
						    "eh timeout, not retrying "
						    "aborted command\n"));
			पूर्ण अन्यथा अगर (!scsi_noretry_cmd(scmd) &&
				   scsi_cmd_retry_allowed(scmd) &&
				scsi_eh_should_retry_cmd(scmd)) अणु
				SCSI_LOG_ERROR_RECOVERY(3,
					scmd_prपूर्णांकk(KERN_WARNING, scmd,
						    "retry aborted command\n"));
				scsi_queue_insert(scmd, SCSI_MLQUEUE_EH_RETRY);
				वापस;
			पूर्ण अन्यथा अणु
				SCSI_LOG_ERROR_RECOVERY(3,
					scmd_prपूर्णांकk(KERN_WARNING, scmd,
						    "finish aborted command\n"));
				scsi_finish_command(scmd);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			SCSI_LOG_ERROR_RECOVERY(3,
				scmd_prपूर्णांकk(KERN_INFO, scmd,
					    "cmd abort %s\n",
					    (rtn == FAST_IO_FAIL) ?
					    "not send" : "failed"));
		पूर्ण
	पूर्ण

	scsi_eh_scmd_add(scmd);
पूर्ण

/**
 * scsi_पात_command - schedule a command पात
 * @scmd:	scmd to पात.
 *
 * We only need to पात commands after a command समयout
 */
अटल पूर्णांक
scsi_पात_command(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा scsi_device *sdev = scmd->device;
	काष्ठा Scsi_Host *shost = sdev->host;
	अचिन्हित दीर्घ flags;

	अगर (scmd->eh_eflags & SCSI_EH_ABORT_SCHEDULED) अणु
		/*
		 * Retry after पात failed, escalate to next level.
		 */
		SCSI_LOG_ERROR_RECOVERY(3,
			scmd_prपूर्णांकk(KERN_INFO, scmd,
				    "previous abort failed\n"));
		BUG_ON(delayed_work_pending(&scmd->पात_work));
		वापस FAILED;
	पूर्ण

	spin_lock_irqsave(shost->host_lock, flags);
	अगर (shost->eh_deadline != -1 && !shost->last_reset)
		shost->last_reset = jअगरfies;
	spin_unlock_irqrestore(shost->host_lock, flags);

	scmd->eh_eflags |= SCSI_EH_ABORT_SCHEDULED;
	SCSI_LOG_ERROR_RECOVERY(3,
		scmd_prपूर्णांकk(KERN_INFO, scmd, "abort scheduled\n"));
	queue_delayed_work(shost->पंचांगf_work_q, &scmd->पात_work, HZ / 100);
	वापस SUCCESS;
पूर्ण

/**
 * scsi_eh_reset - call पूर्णांकo ->eh_action to reset पूर्णांकernal counters
 * @scmd:	scmd to run eh on.
 *
 * The scsi driver might be carrying पूर्णांकernal state about the
 * devices, so we need to call पूर्णांकo the driver to reset the
 * पूर्णांकernal state once the error handler is started.
 */
अटल व्योम scsi_eh_reset(काष्ठा scsi_cmnd *scmd)
अणु
	अगर (!blk_rq_is_passthrough(scmd->request)) अणु
		काष्ठा scsi_driver *sdrv = scsi_cmd_to_driver(scmd);
		अगर (sdrv->eh_reset)
			sdrv->eh_reset(scmd);
	पूर्ण
पूर्ण

अटल व्योम scsi_eh_inc_host_failed(काष्ठा rcu_head *head)
अणु
	काष्ठा scsi_cmnd *scmd = container_of(head, typeof(*scmd), rcu);
	काष्ठा Scsi_Host *shost = scmd->device->host;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);
	shost->host_failed++;
	scsi_eh_wakeup(shost);
	spin_unlock_irqrestore(shost->host_lock, flags);
पूर्ण

/**
 * scsi_eh_scmd_add - add scsi cmd to error handling.
 * @scmd:	scmd to run eh on.
 */
व्योम scsi_eh_scmd_add(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा Scsi_Host *shost = scmd->device->host;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	WARN_ON_ONCE(!shost->ehandler);

	spin_lock_irqsave(shost->host_lock, flags);
	अगर (scsi_host_set_state(shost, SHOST_RECOVERY)) अणु
		ret = scsi_host_set_state(shost, SHOST_CANCEL_RECOVERY);
		WARN_ON_ONCE(ret);
	पूर्ण
	अगर (shost->eh_deadline != -1 && !shost->last_reset)
		shost->last_reset = jअगरfies;

	scsi_eh_reset(scmd);
	list_add_tail(&scmd->eh_entry, &shost->eh_cmd_q);
	spin_unlock_irqrestore(shost->host_lock, flags);
	/*
	 * Ensure that all tasks observe the host state change beक्रमe the
	 * host_failed change.
	 */
	call_rcu(&scmd->rcu, scsi_eh_inc_host_failed);
पूर्ण

/**
 * scsi_बार_out - Timeout function क्रम normal scsi commands.
 * @req:	request that is timing out.
 *
 * Notes:
 *     We करो not need to lock this.  There is the potential क्रम a race
 *     only in that the normal completion handling might run, but अगर the
 *     normal completion function determines that the समयr has alपढ़ोy
 *     fired, then it mustn't करो anything.
 */
क्रमागत blk_eh_समयr_वापस scsi_बार_out(काष्ठा request *req)
अणु
	काष्ठा scsi_cmnd *scmd = blk_mq_rq_to_pdu(req);
	क्रमागत blk_eh_समयr_वापस rtn = BLK_EH_DONE;
	काष्ठा Scsi_Host *host = scmd->device->host;

	trace_scsi_dispatch_cmd_समयout(scmd);
	scsi_log_completion(scmd, TIMEOUT_ERROR);

	अगर (host->eh_deadline != -1 && !host->last_reset)
		host->last_reset = jअगरfies;

	अगर (host->hostt->eh_समयd_out)
		rtn = host->hostt->eh_समयd_out(scmd);

	अगर (rtn == BLK_EH_DONE) अणु
		/*
		 * Set the command to complete first in order to prevent a real
		 * completion from releasing the command जबतक error handling
		 * is using it. If the command was alपढ़ोy completed, then the
		 * lower level driver beat the समयout handler, and it is safe
		 * to वापस without escalating error recovery.
		 *
		 * If समयout handling lost the race to a real completion, the
		 * block layer may ignore that due to a fake समयout injection,
		 * so वापस RESET_TIMER to allow error handling another shot
		 * at this command.
		 */
		अगर (test_and_set_bit(SCMD_STATE_COMPLETE, &scmd->state))
			वापस BLK_EH_RESET_TIMER;
		अगर (scsi_पात_command(scmd) != SUCCESS) अणु
			set_host_byte(scmd, DID_TIME_OUT);
			scsi_eh_scmd_add(scmd);
		पूर्ण
	पूर्ण

	वापस rtn;
पूर्ण

/**
 * scsi_block_when_processing_errors - Prevent cmds from being queued.
 * @sdev:	Device on which we are perक्रमming recovery.
 *
 * Description:
 *     We block until the host is out of error recovery, and then check to
 *     see whether the host or the device is offline.
 *
 * Return value:
 *     0 when dev was taken offline by error recovery. 1 OK to proceed.
 */
पूर्णांक scsi_block_when_processing_errors(काष्ठा scsi_device *sdev)
अणु
	पूर्णांक online;

	रुको_event(sdev->host->host_रुको, !scsi_host_in_recovery(sdev->host));

	online = scsi_device_online(sdev);

	वापस online;
पूर्ण
EXPORT_SYMBOL(scsi_block_when_processing_errors);

#अगर_घोषित CONFIG_SCSI_LOGGING
/**
 * scsi_eh_prt_fail_stats - Log info on failures.
 * @shost:	scsi host being recovered.
 * @work_q:	Queue of scsi cmds to process.
 */
अटल अंतरभूत व्योम scsi_eh_prt_fail_stats(काष्ठा Scsi_Host *shost,
					  काष्ठा list_head *work_q)
अणु
	काष्ठा scsi_cmnd *scmd;
	काष्ठा scsi_device *sdev;
	पूर्णांक total_failures = 0;
	पूर्णांक cmd_failed = 0;
	पूर्णांक cmd_cancel = 0;
	पूर्णांक devices_failed = 0;

	shost_क्रम_each_device(sdev, shost) अणु
		list_क्रम_each_entry(scmd, work_q, eh_entry) अणु
			अगर (scmd->device == sdev) अणु
				++total_failures;
				अगर (scmd->eh_eflags & SCSI_EH_ABORT_SCHEDULED)
					++cmd_cancel;
				अन्यथा
					++cmd_failed;
			पूर्ण
		पूर्ण

		अगर (cmd_cancel || cmd_failed) अणु
			SCSI_LOG_ERROR_RECOVERY(3,
				shost_prपूर्णांकk(KERN_INFO, shost,
					    "%s: cmds failed: %d, cancel: %d\n",
					    __func__, cmd_failed,
					    cmd_cancel));
			cmd_cancel = 0;
			cmd_failed = 0;
			++devices_failed;
		पूर्ण
	पूर्ण

	SCSI_LOG_ERROR_RECOVERY(2, shost_prपूर्णांकk(KERN_INFO, shost,
				   "Total of %d commands on %d"
				   " devices require eh work\n",
				   total_failures, devices_failed));
पूर्ण
#पूर्ण_अगर

 /**
 * scsi_report_lun_change - Set flag on all *other* devices on the same target
 *                          to indicate that a UNIT ATTENTION is expected.
 * @sdev:	Device reporting the UNIT ATTENTION
 */
अटल व्योम scsi_report_lun_change(काष्ठा scsi_device *sdev)
अणु
	sdev->sdev_target->expecting_lun_change = 1;
पूर्ण

/**
 * scsi_report_sense - Examine scsi sense inक्रमmation and log messages क्रम
 *		       certain conditions, also issue uevents क्रम some of them.
 * @sdev:	Device reporting the sense code
 * @sshdr:	sshdr to be examined
 */
अटल व्योम scsi_report_sense(काष्ठा scsi_device *sdev,
			      काष्ठा scsi_sense_hdr *sshdr)
अणु
	क्रमागत scsi_device_event evt_type = SDEV_EVT_MAXBITS;	/* i.e. none */

	अगर (sshdr->sense_key == UNIT_ATTENTION) अणु
		अगर (sshdr->asc == 0x3f && sshdr->ascq == 0x03) अणु
			evt_type = SDEV_EVT_INQUIRY_CHANGE_REPORTED;
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				    "Inquiry data has changed");
		पूर्ण अन्यथा अगर (sshdr->asc == 0x3f && sshdr->ascq == 0x0e) अणु
			evt_type = SDEV_EVT_LUN_CHANGE_REPORTED;
			scsi_report_lun_change(sdev);
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				    "Warning! Received an indication that the "
				    "LUN assignments on this target have "
				    "changed. The Linux SCSI layer does not "
				    "automatically remap LUN assignments.\n");
		पूर्ण अन्यथा अगर (sshdr->asc == 0x3f)
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				    "Warning! Received an indication that the "
				    "operating parameters on this target have "
				    "changed. The Linux SCSI layer does not "
				    "automatically adjust these parameters.\n");

		अगर (sshdr->asc == 0x38 && sshdr->ascq == 0x07) अणु
			evt_type = SDEV_EVT_SOFT_THRESHOLD_REACHED_REPORTED;
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				    "Warning! Received an indication that the "
				    "LUN reached a thin provisioning soft "
				    "threshold.\n");
		पूर्ण

		अगर (sshdr->asc == 0x29) अणु
			evt_type = SDEV_EVT_POWER_ON_RESET_OCCURRED;
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				    "Power-on or device reset occurred\n");
		पूर्ण

		अगर (sshdr->asc == 0x2a && sshdr->ascq == 0x01) अणु
			evt_type = SDEV_EVT_MODE_PARAMETER_CHANGE_REPORTED;
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				    "Mode parameters changed");
		पूर्ण अन्यथा अगर (sshdr->asc == 0x2a && sshdr->ascq == 0x06) अणु
			evt_type = SDEV_EVT_ALUA_STATE_CHANGE_REPORTED;
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				    "Asymmetric access state changed");
		पूर्ण अन्यथा अगर (sshdr->asc == 0x2a && sshdr->ascq == 0x09) अणु
			evt_type = SDEV_EVT_CAPACITY_CHANGE_REPORTED;
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				    "Capacity data has changed");
		पूर्ण अन्यथा अगर (sshdr->asc == 0x2a)
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				    "Parameters changed");
	पूर्ण

	अगर (evt_type != SDEV_EVT_MAXBITS) अणु
		set_bit(evt_type, sdev->pending_events);
		schedule_work(&sdev->event_work);
	पूर्ण
पूर्ण

/**
 * scsi_check_sense - Examine scsi cmd sense
 * @scmd:	Cmd to have sense checked.
 *
 * Return value:
 *	SUCCESS or FAILED or NEEDS_RETRY or ADD_TO_MLQUEUE
 *
 * Notes:
 *	When a deferred error is detected the current command has
 *	not been executed and needs retrying.
 */
क्रमागत scsi_disposition scsi_check_sense(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा scsi_device *sdev = scmd->device;
	काष्ठा scsi_sense_hdr sshdr;

	अगर (! scsi_command_normalize_sense(scmd, &sshdr))
		वापस FAILED;	/* no valid sense data */

	scsi_report_sense(sdev, &sshdr);

	अगर (scsi_sense_is_deferred(&sshdr))
		वापस NEEDS_RETRY;

	अगर (sdev->handler && sdev->handler->check_sense) अणु
		क्रमागत scsi_disposition rc;

		rc = sdev->handler->check_sense(sdev, &sshdr);
		अगर (rc != SCSI_RETURN_NOT_HANDLED)
			वापस rc;
		/* handler करोes not care. Drop करोwn to शेष handling */
	पूर्ण

	अगर (scmd->cmnd[0] == TEST_UNIT_READY && scmd->scsi_करोne != scsi_eh_करोne)
		/*
		 * nasty: क्रम mid-layer issued TURs, we need to वापस the
		 * actual sense data without any recovery attempt.  For eh
		 * issued ones, we need to try to recover and पूर्णांकerpret
		 */
		वापस SUCCESS;

	/*
	 * Previous logic looked क्रम खाताMARK, EOM or ILI which are
	 * मुख्यly associated with tapes and वापसed SUCCESS.
	 */
	अगर (sshdr.response_code == 0x70) अणु
		/* fixed क्रमmat */
		अगर (scmd->sense_buffer[2] & 0xe0)
			वापस SUCCESS;
	पूर्ण अन्यथा अणु
		/*
		 * descriptor क्रमmat: look क्रम "stream commands sense data
		 * descriptor" (see SSC-3). Assume single sense data
		 * descriptor. Ignore ILI from SBC-2 READ LONG and WRITE LONG.
		 */
		अगर ((sshdr.additional_length > 3) &&
		    (scmd->sense_buffer[8] == 0x4) &&
		    (scmd->sense_buffer[11] & 0xe0))
			वापस SUCCESS;
	पूर्ण

	चयन (sshdr.sense_key) अणु
	हाल NO_SENSE:
		वापस SUCCESS;
	हाल RECOVERED_ERROR:
		वापस /* soft_error */ SUCCESS;

	हाल ABORTED_COMMAND:
		अगर (sshdr.asc == 0x10) /* DIF */
			वापस SUCCESS;

		अगर (sshdr.asc == 0x44 && sdev->sdev_bflags & BLIST_RETRY_ITF)
			वापस ADD_TO_MLQUEUE;
		अगर (sshdr.asc == 0xc1 && sshdr.ascq == 0x01 &&
		    sdev->sdev_bflags & BLIST_RETRY_ASC_C1)
			वापस ADD_TO_MLQUEUE;

		वापस NEEDS_RETRY;
	हाल NOT_READY:
	हाल UNIT_ATTENTION:
		/*
		 * अगर we are expecting a cc/ua because of a bus reset that we
		 * perक्रमmed, treat this just as a retry.  otherwise this is
		 * inक्रमmation that we should pass up to the upper-level driver
		 * so that we can deal with it there.
		 */
		अगर (scmd->device->expecting_cc_ua) अणु
			/*
			 * Because some device करोes not queue unit
			 * attentions correctly, we carefully check
			 * additional sense code and qualअगरier so as
			 * not to squash media change unit attention.
			 */
			अगर (sshdr.asc != 0x28 || sshdr.ascq != 0x00) अणु
				scmd->device->expecting_cc_ua = 0;
				वापस NEEDS_RETRY;
			पूर्ण
		पूर्ण
		/*
		 * we might also expect a cc/ua अगर another LUN on the target
		 * reported a UA with an ASC/ASCQ of 3F 0E -
		 * REPORTED LUNS DATA HAS CHANGED.
		 */
		अगर (scmd->device->sdev_target->expecting_lun_change &&
		    sshdr.asc == 0x3f && sshdr.ascq == 0x0e)
			वापस NEEDS_RETRY;
		/*
		 * अगर the device is in the process of becoming पढ़ोy, we
		 * should retry.
		 */
		अगर ((sshdr.asc == 0x04) && (sshdr.ascq == 0x01))
			वापस NEEDS_RETRY;
		/*
		 * अगर the device is not started, we need to wake
		 * the error handler to start the motor
		 */
		अगर (scmd->device->allow_restart &&
		    (sshdr.asc == 0x04) && (sshdr.ascq == 0x02))
			वापस FAILED;
		/*
		 * Pass the UA upwards क्रम a determination in the completion
		 * functions.
		 */
		वापस SUCCESS;

		/* these are not supported */
	हाल DATA_PROTECT:
		अगर (sshdr.asc == 0x27 && sshdr.ascq == 0x07) अणु
			/* Thin provisioning hard threshold reached */
			set_host_byte(scmd, DID_ALLOC_FAILURE);
			वापस SUCCESS;
		पूर्ण
		fallthrough;
	हाल COPY_ABORTED:
	हाल VOLUME_OVERFLOW:
	हाल MISCOMPARE:
	हाल BLANK_CHECK:
		set_host_byte(scmd, DID_TARGET_FAILURE);
		वापस SUCCESS;

	हाल MEDIUM_ERROR:
		अगर (sshdr.asc == 0x11 || /* UNRECOVERED READ ERR */
		    sshdr.asc == 0x13 || /* AMNF DATA FIELD */
		    sshdr.asc == 0x14) अणु /* RECORD NOT FOUND */
			set_host_byte(scmd, DID_MEDIUM_ERROR);
			वापस SUCCESS;
		पूर्ण
		वापस NEEDS_RETRY;

	हाल HARDWARE_ERROR:
		अगर (scmd->device->retry_hwerror)
			वापस ADD_TO_MLQUEUE;
		अन्यथा
			set_host_byte(scmd, DID_TARGET_FAILURE);
		fallthrough;

	हाल ILLEGAL_REQUEST:
		अगर (sshdr.asc == 0x20 || /* Invalid command operation code */
		    sshdr.asc == 0x21 || /* Logical block address out of range */
		    sshdr.asc == 0x22 || /* Invalid function */
		    sshdr.asc == 0x24 || /* Invalid field in cdb */
		    sshdr.asc == 0x26 || /* Parameter value invalid */
		    sshdr.asc == 0x27) अणु /* Write रक्षित */
			set_host_byte(scmd, DID_TARGET_FAILURE);
		पूर्ण
		वापस SUCCESS;

	शेष:
		वापस SUCCESS;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(scsi_check_sense);

अटल व्योम scsi_handle_queue_ramp_up(काष्ठा scsi_device *sdev)
अणु
	काष्ठा scsi_host_ढाँचा *sht = sdev->host->hostt;
	काष्ठा scsi_device *पंचांगp_sdev;

	अगर (!sht->track_queue_depth ||
	    sdev->queue_depth >= sdev->max_queue_depth)
		वापस;

	अगर (समय_beक्रमe(jअगरfies,
	    sdev->last_queue_ramp_up + sdev->queue_ramp_up_period))
		वापस;

	अगर (समय_beक्रमe(jअगरfies,
	    sdev->last_queue_full_समय + sdev->queue_ramp_up_period))
		वापस;

	/*
	 * Walk all devices of a target and करो
	 * ramp up on them.
	 */
	shost_क्रम_each_device(पंचांगp_sdev, sdev->host) अणु
		अगर (पंचांगp_sdev->channel != sdev->channel ||
		    पंचांगp_sdev->id != sdev->id ||
		    पंचांगp_sdev->queue_depth == sdev->max_queue_depth)
			जारी;

		scsi_change_queue_depth(पंचांगp_sdev, पंचांगp_sdev->queue_depth + 1);
		sdev->last_queue_ramp_up = jअगरfies;
	पूर्ण
पूर्ण

अटल व्योम scsi_handle_queue_full(काष्ठा scsi_device *sdev)
अणु
	काष्ठा scsi_host_ढाँचा *sht = sdev->host->hostt;
	काष्ठा scsi_device *पंचांगp_sdev;

	अगर (!sht->track_queue_depth)
		वापस;

	shost_क्रम_each_device(पंचांगp_sdev, sdev->host) अणु
		अगर (पंचांगp_sdev->channel != sdev->channel ||
		    पंचांगp_sdev->id != sdev->id)
			जारी;
		/*
		 * We करो not know the number of commands that were at
		 * the device when we got the queue full so we start
		 * from the highest possible value and work our way करोwn.
		 */
		scsi_track_queue_full(पंचांगp_sdev, पंचांगp_sdev->queue_depth - 1);
	पूर्ण
पूर्ण

/**
 * scsi_eh_completed_normally - Disposition a eh cmd on वापस from LLD.
 * @scmd:	SCSI cmd to examine.
 *
 * Notes:
 *    This is *only* called when we are examining the status of commands
 *    queued during error recovery.  the मुख्य dअगरference here is that we
 *    करोn't allow क्रम the possibility of retries here, and we are a lot
 *    more restrictive about what we consider acceptable.
 */
अटल क्रमागत scsi_disposition scsi_eh_completed_normally(काष्ठा scsi_cmnd *scmd)
अणु
	/*
	 * first check the host byte, to see अगर there is anything in there
	 * that would indicate what we need to करो.
	 */
	अगर (host_byte(scmd->result) == DID_RESET) अणु
		/*
		 * rats.  we are alपढ़ोy in the error handler, so we now
		 * get to try and figure out what to करो next.  अगर the sense
		 * is valid, we have a pretty good idea of what to करो.
		 * अगर not, we mark it as FAILED.
		 */
		वापस scsi_check_sense(scmd);
	पूर्ण
	अगर (host_byte(scmd->result) != DID_OK)
		वापस FAILED;

	/*
	 * next, check the message byte.
	 */
	अगर (msg_byte(scmd->result) != COMMAND_COMPLETE)
		वापस FAILED;

	/*
	 * now, check the status byte to see अगर this indicates
	 * anything special.
	 */
	चयन (status_byte(scmd->result)) अणु
	हाल GOOD:
		scsi_handle_queue_ramp_up(scmd->device);
		fallthrough;
	हाल COMMAND_TERMINATED:
		वापस SUCCESS;
	हाल CHECK_CONDITION:
		वापस scsi_check_sense(scmd);
	हाल CONDITION_GOOD:
	हाल INTERMEDIATE_GOOD:
	हाल INTERMEDIATE_C_GOOD:
		/*
		 * who knows?  FIXME(eric)
		 */
		वापस SUCCESS;
	हाल RESERVATION_CONFLICT:
		अगर (scmd->cmnd[0] == TEST_UNIT_READY)
			/* it is a success, we probed the device and
			 * found it */
			वापस SUCCESS;
		/* otherwise, we failed to send the command */
		वापस FAILED;
	हाल QUEUE_FULL:
		scsi_handle_queue_full(scmd->device);
		fallthrough;
	हाल BUSY:
		वापस NEEDS_RETRY;
	शेष:
		वापस FAILED;
	पूर्ण
	वापस FAILED;
पूर्ण

/**
 * scsi_eh_करोne - Completion function क्रम error handling.
 * @scmd:	Cmd that is करोne.
 */
अटल व्योम scsi_eh_करोne(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा completion *eh_action;

	SCSI_LOG_ERROR_RECOVERY(3, scmd_prपूर्णांकk(KERN_INFO, scmd,
			"%s result: %x\n", __func__, scmd->result));

	eh_action = scmd->device->host->eh_action;
	अगर (eh_action)
		complete(eh_action);
पूर्ण

/**
 * scsi_try_host_reset - ask host adapter to reset itself
 * @scmd:	SCSI cmd to send host reset.
 */
अटल क्रमागत scsi_disposition scsi_try_host_reset(काष्ठा scsi_cmnd *scmd)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत scsi_disposition rtn;
	काष्ठा Scsi_Host *host = scmd->device->host;
	काष्ठा scsi_host_ढाँचा *hostt = host->hostt;

	SCSI_LOG_ERROR_RECOVERY(3,
		shost_prपूर्णांकk(KERN_INFO, host, "Snd Host RST\n"));

	अगर (!hostt->eh_host_reset_handler)
		वापस FAILED;

	rtn = hostt->eh_host_reset_handler(scmd);

	अगर (rtn == SUCCESS) अणु
		अगर (!hostt->skip_settle_delay)
			ssleep(HOST_RESET_SETTLE_TIME);
		spin_lock_irqsave(host->host_lock, flags);
		scsi_report_bus_reset(host, scmd_channel(scmd));
		spin_unlock_irqrestore(host->host_lock, flags);
	पूर्ण

	वापस rtn;
पूर्ण

/**
 * scsi_try_bus_reset - ask host to perक्रमm a bus reset
 * @scmd:	SCSI cmd to send bus reset.
 */
अटल क्रमागत scsi_disposition scsi_try_bus_reset(काष्ठा scsi_cmnd *scmd)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत scsi_disposition rtn;
	काष्ठा Scsi_Host *host = scmd->device->host;
	काष्ठा scsi_host_ढाँचा *hostt = host->hostt;

	SCSI_LOG_ERROR_RECOVERY(3, scmd_prपूर्णांकk(KERN_INFO, scmd,
		"%s: Snd Bus RST\n", __func__));

	अगर (!hostt->eh_bus_reset_handler)
		वापस FAILED;

	rtn = hostt->eh_bus_reset_handler(scmd);

	अगर (rtn == SUCCESS) अणु
		अगर (!hostt->skip_settle_delay)
			ssleep(BUS_RESET_SETTLE_TIME);
		spin_lock_irqsave(host->host_lock, flags);
		scsi_report_bus_reset(host, scmd_channel(scmd));
		spin_unlock_irqrestore(host->host_lock, flags);
	पूर्ण

	वापस rtn;
पूर्ण

अटल व्योम __scsi_report_device_reset(काष्ठा scsi_device *sdev, व्योम *data)
अणु
	sdev->was_reset = 1;
	sdev->expecting_cc_ua = 1;
पूर्ण

/**
 * scsi_try_target_reset - Ask host to perक्रमm a target reset
 * @scmd:	SCSI cmd used to send a target reset
 *
 * Notes:
 *    There is no समयout क्रम this operation.  अगर this operation is
 *    unreliable क्रम a given host, then the host itself needs to put a
 *    समयr on it, and set the host back to a consistent state prior to
 *    वापसing.
 */
अटल क्रमागत scsi_disposition scsi_try_target_reset(काष्ठा scsi_cmnd *scmd)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत scsi_disposition rtn;
	काष्ठा Scsi_Host *host = scmd->device->host;
	काष्ठा scsi_host_ढाँचा *hostt = host->hostt;

	अगर (!hostt->eh_target_reset_handler)
		वापस FAILED;

	rtn = hostt->eh_target_reset_handler(scmd);
	अगर (rtn == SUCCESS) अणु
		spin_lock_irqsave(host->host_lock, flags);
		__starget_क्रम_each_device(scsi_target(scmd->device), शून्य,
					  __scsi_report_device_reset);
		spin_unlock_irqrestore(host->host_lock, flags);
	पूर्ण

	वापस rtn;
पूर्ण

/**
 * scsi_try_bus_device_reset - Ask host to perक्रमm a BDR on a dev
 * @scmd:	SCSI cmd used to send BDR
 *
 * Notes:
 *    There is no समयout क्रम this operation.  अगर this operation is
 *    unreliable क्रम a given host, then the host itself needs to put a
 *    समयr on it, and set the host back to a consistent state prior to
 *    वापसing.
 */
अटल क्रमागत scsi_disposition scsi_try_bus_device_reset(काष्ठा scsi_cmnd *scmd)
अणु
	क्रमागत scsi_disposition rtn;
	काष्ठा scsi_host_ढाँचा *hostt = scmd->device->host->hostt;

	अगर (!hostt->eh_device_reset_handler)
		वापस FAILED;

	rtn = hostt->eh_device_reset_handler(scmd);
	अगर (rtn == SUCCESS)
		__scsi_report_device_reset(scmd->device, शून्य);
	वापस rtn;
पूर्ण

/**
 * scsi_try_to_पात_cmd - Ask host to पात a SCSI command
 * @hostt:	SCSI driver host ढाँचा
 * @scmd:	SCSI cmd used to send a target reset
 *
 * Return value:
 *	SUCCESS, FAILED, or FAST_IO_FAIL
 *
 * Notes:
 *    SUCCESS करोes not necessarily indicate that the command
 *    has been पातed; it only indicates that the LLDDs
 *    has cleared all references to that command.
 *    LLDDs should वापस FAILED only अगर an पात was required
 *    but could not be executed. LLDDs should वापस FAST_IO_FAIL
 *    अगर the device is temporarily unavailable (eg due to a
 *    link करोwn on FibreChannel)
 */
अटल क्रमागत scsi_disposition
scsi_try_to_पात_cmd(काष्ठा scsi_host_ढाँचा *hostt, काष्ठा scsi_cmnd *scmd)
अणु
	अगर (!hostt->eh_पात_handler)
		वापस FAILED;

	वापस hostt->eh_पात_handler(scmd);
पूर्ण

अटल व्योम scsi_पात_eh_cmnd(काष्ठा scsi_cmnd *scmd)
अणु
	अगर (scsi_try_to_पात_cmd(scmd->device->host->hostt, scmd) != SUCCESS)
		अगर (scsi_try_bus_device_reset(scmd) != SUCCESS)
			अगर (scsi_try_target_reset(scmd) != SUCCESS)
				अगर (scsi_try_bus_reset(scmd) != SUCCESS)
					scsi_try_host_reset(scmd);
पूर्ण

/**
 * scsi_eh_prep_cmnd  - Save a scsi command info as part of error recovery
 * @scmd:       SCSI command काष्ठाure to hijack
 * @ses:        काष्ठाure to save restore inक्रमmation
 * @cmnd:       CDB to send. Can be शून्य अगर no new cmnd is needed
 * @cmnd_size:  size in bytes of @cmnd (must be <= BLK_MAX_CDB)
 * @sense_bytes: size of sense data to copy. or 0 (अगर != 0 @cmnd is ignored)
 *
 * This function is used to save a scsi command inक्रमmation beक्रमe re-execution
 * as part of the error recovery process.  If @sense_bytes is 0 the command
 * sent must be one that करोes not transfer any data.  If @sense_bytes != 0
 * @cmnd is ignored and this functions sets up a REQUEST_SENSE command
 * and cmnd buffers to पढ़ो @sense_bytes पूर्णांकo @scmd->sense_buffer.
 */
व्योम scsi_eh_prep_cmnd(काष्ठा scsi_cmnd *scmd, काष्ठा scsi_eh_save *ses,
			अचिन्हित अक्षर *cmnd, पूर्णांक cmnd_size, अचिन्हित sense_bytes)
अणु
	काष्ठा scsi_device *sdev = scmd->device;

	/*
	 * We need saved copies of a number of fields - this is because
	 * error handling may need to overग_लिखो these with dअगरferent values
	 * to run dअगरferent commands, and once error handling is complete,
	 * we will need to restore these values prior to running the actual
	 * command.
	 */
	ses->cmd_len = scmd->cmd_len;
	ses->cmnd = scmd->cmnd;
	ses->data_direction = scmd->sc_data_direction;
	ses->sdb = scmd->sdb;
	ses->result = scmd->result;
	ses->resid_len = scmd->req.resid_len;
	ses->underflow = scmd->underflow;
	ses->prot_op = scmd->prot_op;
	ses->eh_eflags = scmd->eh_eflags;

	scmd->prot_op = SCSI_PROT_NORMAL;
	scmd->eh_eflags = 0;
	scmd->cmnd = ses->eh_cmnd;
	स_रखो(scmd->cmnd, 0, BLK_MAX_CDB);
	स_रखो(&scmd->sdb, 0, माप(scmd->sdb));
	scmd->result = 0;
	scmd->req.resid_len = 0;

	अगर (sense_bytes) अणु
		scmd->sdb.length = min_t(अचिन्हित, SCSI_SENSE_BUFFERSIZE,
					 sense_bytes);
		sg_init_one(&ses->sense_sgl, scmd->sense_buffer,
			    scmd->sdb.length);
		scmd->sdb.table.sgl = &ses->sense_sgl;
		scmd->sc_data_direction = DMA_FROM_DEVICE;
		scmd->sdb.table.nents = scmd->sdb.table.orig_nents = 1;
		scmd->cmnd[0] = REQUEST_SENSE;
		scmd->cmnd[4] = scmd->sdb.length;
		scmd->cmd_len = COMMAND_SIZE(scmd->cmnd[0]);
	पूर्ण अन्यथा अणु
		scmd->sc_data_direction = DMA_NONE;
		अगर (cmnd) अणु
			BUG_ON(cmnd_size > BLK_MAX_CDB);
			स_नकल(scmd->cmnd, cmnd, cmnd_size);
			scmd->cmd_len = COMMAND_SIZE(scmd->cmnd[0]);
		पूर्ण
	पूर्ण

	scmd->underflow = 0;

	अगर (sdev->scsi_level <= SCSI_2 && sdev->scsi_level != SCSI_UNKNOWN)
		scmd->cmnd[1] = (scmd->cmnd[1] & 0x1f) |
			(sdev->lun << 5 & 0xe0);

	/*
	 * Zero the sense buffer.  The scsi spec mandates that any
	 * untransferred sense data should be पूर्णांकerpreted as being zero.
	 */
	स_रखो(scmd->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
पूर्ण
EXPORT_SYMBOL(scsi_eh_prep_cmnd);

/**
 * scsi_eh_restore_cmnd  - Restore a scsi command info as part of error recovery
 * @scmd:       SCSI command काष्ठाure to restore
 * @ses:        saved inक्रमmation from a coresponding call to scsi_eh_prep_cmnd
 *
 * Unकरो any damage करोne by above scsi_eh_prep_cmnd().
 */
व्योम scsi_eh_restore_cmnd(काष्ठा scsi_cmnd* scmd, काष्ठा scsi_eh_save *ses)
अणु
	/*
	 * Restore original data
	 */
	scmd->cmd_len = ses->cmd_len;
	scmd->cmnd = ses->cmnd;
	scmd->sc_data_direction = ses->data_direction;
	scmd->sdb = ses->sdb;
	scmd->result = ses->result;
	scmd->req.resid_len = ses->resid_len;
	scmd->underflow = ses->underflow;
	scmd->prot_op = ses->prot_op;
	scmd->eh_eflags = ses->eh_eflags;
पूर्ण
EXPORT_SYMBOL(scsi_eh_restore_cmnd);

/**
 * scsi_send_eh_cmnd  - submit a scsi command as part of error recovery
 * @scmd:       SCSI command काष्ठाure to hijack
 * @cmnd:       CDB to send
 * @cmnd_size:  size in bytes of @cmnd
 * @समयout:    समयout क्रम this request
 * @sense_bytes: size of sense data to copy or 0
 *
 * This function is used to send a scsi command करोwn to a target device
 * as part of the error recovery process. See also scsi_eh_prep_cmnd() above.
 *
 * Return value:
 *    SUCCESS or FAILED or NEEDS_RETRY
 */
अटल क्रमागत scsi_disposition scsi_send_eh_cmnd(काष्ठा scsi_cmnd *scmd,
	अचिन्हित अक्षर *cmnd, पूर्णांक cmnd_size, पूर्णांक समयout, अचिन्हित sense_bytes)
अणु
	काष्ठा scsi_device *sdev = scmd->device;
	काष्ठा Scsi_Host *shost = sdev->host;
	DECLARE_COMPLETION_ONSTACK(करोne);
	अचिन्हित दीर्घ समयleft = समयout, delay;
	काष्ठा scsi_eh_save ses;
	स्थिर अचिन्हित दीर्घ stall_क्रम = msecs_to_jअगरfies(100);
	पूर्णांक rtn;

retry:
	scsi_eh_prep_cmnd(scmd, &ses, cmnd, cmnd_size, sense_bytes);
	shost->eh_action = &करोne;

	scsi_log_send(scmd);
	scmd->scsi_करोne = scsi_eh_करोne;

	/*
	 * Lock sdev->state_mutex to aव्योम that scsi_device_quiesce() can
	 * change the SCSI device state after we have examined it and beक्रमe
	 * .queuecommand() is called.
	 */
	mutex_lock(&sdev->state_mutex);
	जबतक (sdev->sdev_state == SDEV_BLOCK && समयleft > 0) अणु
		mutex_unlock(&sdev->state_mutex);
		SCSI_LOG_ERROR_RECOVERY(5, sdev_prपूर्णांकk(KERN_DEBUG, sdev,
			"%s: state %d <> %d\n", __func__, sdev->sdev_state,
			SDEV_BLOCK));
		delay = min(समयleft, stall_क्रम);
		समयleft -= delay;
		msleep(jअगरfies_to_msecs(delay));
		mutex_lock(&sdev->state_mutex);
	पूर्ण
	अगर (sdev->sdev_state != SDEV_BLOCK)
		rtn = shost->hostt->queuecommand(shost, scmd);
	अन्यथा
		rtn = FAILED;
	mutex_unlock(&sdev->state_mutex);

	अगर (rtn) अणु
		अगर (समयleft > stall_क्रम) अणु
			scsi_eh_restore_cmnd(scmd, &ses);
			समयleft -= stall_क्रम;
			msleep(jअगरfies_to_msecs(stall_क्रम));
			जाओ retry;
		पूर्ण
		/* संकेत not to enter either branch of the अगर () below */
		समयleft = 0;
		rtn = FAILED;
	पूर्ण अन्यथा अणु
		समयleft = रुको_क्रम_completion_समयout(&करोne, समयout);
		rtn = SUCCESS;
	पूर्ण

	shost->eh_action = शून्य;

	scsi_log_completion(scmd, rtn);

	SCSI_LOG_ERROR_RECOVERY(3, scmd_prपूर्णांकk(KERN_INFO, scmd,
			"%s timeleft: %ld\n",
			__func__, समयleft));

	/*
	 * If there is समय left scsi_eh_करोne got called, and we will examine
	 * the actual status codes to see whether the command actually did
	 * complete normally, अन्यथा अगर we have a zero वापस and no समय left,
	 * the command must still be pending, so पात it and वापस FAILED.
	 * If we never actually managed to issue the command, because
	 * ->queuecommand() kept वापसing non zero, use the rtn = FAILED
	 * value above (so करोn't execute either branch of the अगर)
	 */
	अगर (समयleft) अणु
		rtn = scsi_eh_completed_normally(scmd);
		SCSI_LOG_ERROR_RECOVERY(3, scmd_prपूर्णांकk(KERN_INFO, scmd,
			"%s: scsi_eh_completed_normally %x\n", __func__, rtn));

		चयन (rtn) अणु
		हाल SUCCESS:
		हाल NEEDS_RETRY:
		हाल FAILED:
			अवरोध;
		हाल ADD_TO_MLQUEUE:
			rtn = NEEDS_RETRY;
			अवरोध;
		शेष:
			rtn = FAILED;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (rtn != FAILED) अणु
		scsi_पात_eh_cmnd(scmd);
		rtn = FAILED;
	पूर्ण

	scsi_eh_restore_cmnd(scmd, &ses);

	वापस rtn;
पूर्ण

/**
 * scsi_request_sense - Request sense data from a particular target.
 * @scmd:	SCSI cmd क्रम request sense.
 *
 * Notes:
 *    Some hosts स्वतःmatically obtain this inक्रमmation, others require
 *    that we obtain it on our own. This function will *not* वापस until
 *    the command either बार out, or it completes.
 */
अटल क्रमागत scsi_disposition scsi_request_sense(काष्ठा scsi_cmnd *scmd)
अणु
	वापस scsi_send_eh_cmnd(scmd, शून्य, 0, scmd->device->eh_समयout, ~0);
पूर्ण

अटल क्रमागत scsi_disposition
scsi_eh_action(काष्ठा scsi_cmnd *scmd, क्रमागत scsi_disposition rtn)
अणु
	अगर (!blk_rq_is_passthrough(scmd->request)) अणु
		काष्ठा scsi_driver *sdrv = scsi_cmd_to_driver(scmd);
		अगर (sdrv->eh_action)
			rtn = sdrv->eh_action(scmd, rtn);
	पूर्ण
	वापस rtn;
पूर्ण

/**
 * scsi_eh_finish_cmd - Handle a cmd that eh is finished with.
 * @scmd:	Original SCSI cmd that eh has finished.
 * @करोne_q:	Queue क्रम processed commands.
 *
 * Notes:
 *    We करोn't want to use the normal command completion जबतक we are are
 *    still handling errors - it may cause other commands to be queued,
 *    and that would disturb what we are करोing.  Thus we really want to
 *    keep a list of pending commands क्रम final completion, and once we
 *    are पढ़ोy to leave error handling we handle completion क्रम real.
 */
व्योम scsi_eh_finish_cmd(काष्ठा scsi_cmnd *scmd, काष्ठा list_head *करोne_q)
अणु
	list_move_tail(&scmd->eh_entry, करोne_q);
पूर्ण
EXPORT_SYMBOL(scsi_eh_finish_cmd);

/**
 * scsi_eh_get_sense - Get device sense data.
 * @work_q:	Queue of commands to process.
 * @करोne_q:	Queue of processed commands.
 *
 * Description:
 *    See अगर we need to request sense inक्रमmation.  अगर so, then get it
 *    now, so we have a better idea of what to करो.
 *
 * Notes:
 *    This has the unक्रमtunate side effect that अगर a shost adapter करोes
 *    not स्वतःmatically request sense inक्रमmation, we end up shutting
 *    it करोwn beक्रमe we request it.
 *
 *    All drivers should request sense inक्रमmation पूर्णांकernally these days,
 *    so क्रम now all I have to say is tough noogies अगर you end up in here.
 *
 *    XXX: Long term this code should go away, but that needs an audit of
 *         all LLDDs first.
 */
पूर्णांक scsi_eh_get_sense(काष्ठा list_head *work_q,
		      काष्ठा list_head *करोne_q)
अणु
	काष्ठा scsi_cmnd *scmd, *next;
	काष्ठा Scsi_Host *shost;
	क्रमागत scsi_disposition rtn;

	/*
	 * If SCSI_EH_ABORT_SCHEDULED has been set, it is समयout IO,
	 * should not get sense.
	 */
	list_क्रम_each_entry_safe(scmd, next, work_q, eh_entry) अणु
		अगर ((scmd->eh_eflags & SCSI_EH_ABORT_SCHEDULED) ||
		    SCSI_SENSE_VALID(scmd))
			जारी;

		shost = scmd->device->host;
		अगर (scsi_host_eh_past_deadline(shost)) अणु
			SCSI_LOG_ERROR_RECOVERY(3,
				scmd_prपूर्णांकk(KERN_INFO, scmd,
					    "%s: skip request sense, past eh deadline\n",
					     current->comm));
			अवरोध;
		पूर्ण
		अगर (status_byte(scmd->result) != CHECK_CONDITION)
			/*
			 * करोn't request sense if there's no check condition
			 * status because the error we're processing isn't one
			 * that has a sense code (and some devices get
			 * confused by sense requests out of the blue)
			 */
			जारी;

		SCSI_LOG_ERROR_RECOVERY(2, scmd_prपूर्णांकk(KERN_INFO, scmd,
						  "%s: requesting sense\n",
						  current->comm));
		rtn = scsi_request_sense(scmd);
		अगर (rtn != SUCCESS)
			जारी;

		SCSI_LOG_ERROR_RECOVERY(3, scmd_prपूर्णांकk(KERN_INFO, scmd,
			"sense requested, result %x\n", scmd->result));
		SCSI_LOG_ERROR_RECOVERY(3, scsi_prपूर्णांक_sense(scmd));

		rtn = scsi_decide_disposition(scmd);

		/*
		 * अगर the result was normal, then just pass it aदीर्घ to the
		 * upper level.
		 */
		अगर (rtn == SUCCESS)
			/*
			 * We करोn't want this command reissued, just finished
			 * with the sense data, so set retries to the max
			 * allowed to ensure it won't get reissued. If the user
			 * has requested infinite retries, we also want to
			 * finish this command, so क्रमce completion by setting
			 * retries and allowed to the same value.
			 */
			अगर (scmd->allowed == SCSI_CMD_RETRIES_NO_LIMIT)
				scmd->retries = scmd->allowed = 1;
			अन्यथा
				scmd->retries = scmd->allowed;
		अन्यथा अगर (rtn != NEEDS_RETRY)
			जारी;

		scsi_eh_finish_cmd(scmd, करोne_q);
	पूर्ण

	वापस list_empty(work_q);
पूर्ण
EXPORT_SYMBOL_GPL(scsi_eh_get_sense);

/**
 * scsi_eh_tur - Send TUR to device.
 * @scmd:	&scsi_cmnd to send TUR
 *
 * Return value:
 *    0 - Device is पढ़ोy. 1 - Device NOT पढ़ोy.
 */
अटल पूर्णांक scsi_eh_tur(काष्ठा scsi_cmnd *scmd)
अणु
	अटल अचिन्हित अक्षर tur_command[6] = अणुTEST_UNIT_READY, 0, 0, 0, 0, 0पूर्ण;
	पूर्णांक retry_cnt = 1;
	क्रमागत scsi_disposition rtn;

retry_tur:
	rtn = scsi_send_eh_cmnd(scmd, tur_command, 6,
				scmd->device->eh_समयout, 0);

	SCSI_LOG_ERROR_RECOVERY(3, scmd_prपूर्णांकk(KERN_INFO, scmd,
		"%s return: %x\n", __func__, rtn));

	चयन (rtn) अणु
	हाल NEEDS_RETRY:
		अगर (retry_cnt--)
			जाओ retry_tur;
		fallthrough;
	हाल SUCCESS:
		वापस 0;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

/**
 * scsi_eh_test_devices - check अगर devices are responding from error recovery.
 * @cmd_list:	scsi commands in error recovery.
 * @work_q:	queue क्रम commands which still need more error recovery
 * @करोne_q:	queue क्रम commands which are finished
 * @try_stu:	boolean on अगर a STU command should be tried in addition to TUR.
 *
 * Decription:
 *    Tests अगर devices are in a working state.  Commands to devices now in
 *    a working state are sent to the करोne_q जबतक commands to devices which
 *    are still failing to respond are वापसed to the work_q क्रम more
 *    processing.
 **/
अटल पूर्णांक scsi_eh_test_devices(काष्ठा list_head *cmd_list,
				काष्ठा list_head *work_q,
				काष्ठा list_head *करोne_q, पूर्णांक try_stu)
अणु
	काष्ठा scsi_cmnd *scmd, *next;
	काष्ठा scsi_device *sdev;
	पूर्णांक finish_cmds;

	जबतक (!list_empty(cmd_list)) अणु
		scmd = list_entry(cmd_list->next, काष्ठा scsi_cmnd, eh_entry);
		sdev = scmd->device;

		अगर (!try_stu) अणु
			अगर (scsi_host_eh_past_deadline(sdev->host)) अणु
				/* Push items back onto work_q */
				list_splice_init(cmd_list, work_q);
				SCSI_LOG_ERROR_RECOVERY(3,
					sdev_prपूर्णांकk(KERN_INFO, sdev,
						    "%s: skip test device, past eh deadline",
						    current->comm));
				अवरोध;
			पूर्ण
		पूर्ण

		finish_cmds = !scsi_device_online(scmd->device) ||
			(try_stu && !scsi_eh_try_stu(scmd) &&
			 !scsi_eh_tur(scmd)) ||
			!scsi_eh_tur(scmd);

		list_क्रम_each_entry_safe(scmd, next, cmd_list, eh_entry)
			अगर (scmd->device == sdev) अणु
				अगर (finish_cmds &&
				    (try_stu ||
				     scsi_eh_action(scmd, SUCCESS) == SUCCESS))
					scsi_eh_finish_cmd(scmd, करोne_q);
				अन्यथा
					list_move_tail(&scmd->eh_entry, work_q);
			पूर्ण
	पूर्ण
	वापस list_empty(work_q);
पूर्ण

/**
 * scsi_eh_try_stu - Send START_UNIT to device.
 * @scmd:	&scsi_cmnd to send START_UNIT
 *
 * Return value:
 *    0 - Device is पढ़ोy. 1 - Device NOT पढ़ोy.
 */
अटल पूर्णांक scsi_eh_try_stu(काष्ठा scsi_cmnd *scmd)
अणु
	अटल अचिन्हित अक्षर stu_command[6] = अणुSTART_STOP, 0, 0, 0, 1, 0पूर्ण;

	अगर (scmd->device->allow_restart) अणु
		पूर्णांक i;
		क्रमागत scsi_disposition rtn = NEEDS_RETRY;

		क्रम (i = 0; rtn == NEEDS_RETRY && i < 2; i++)
			rtn = scsi_send_eh_cmnd(scmd, stu_command, 6, scmd->device->request_queue->rq_समयout, 0);

		अगर (rtn == SUCCESS)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

 /**
 * scsi_eh_stu - send START_UNIT अगर needed
 * @shost:	&scsi host being recovered.
 * @work_q:	&list_head क्रम pending commands.
 * @करोne_q:	&list_head क्रम processed commands.
 *
 * Notes:
 *    If commands are failing due to not पढ़ोy, initializing command required,
 *	try revalidating the device, which will end up sending a start unit.
 */
अटल पूर्णांक scsi_eh_stu(काष्ठा Scsi_Host *shost,
			      काष्ठा list_head *work_q,
			      काष्ठा list_head *करोne_q)
अणु
	काष्ठा scsi_cmnd *scmd, *stu_scmd, *next;
	काष्ठा scsi_device *sdev;

	shost_क्रम_each_device(sdev, shost) अणु
		अगर (scsi_host_eh_past_deadline(shost)) अणु
			SCSI_LOG_ERROR_RECOVERY(3,
				sdev_prपूर्णांकk(KERN_INFO, sdev,
					    "%s: skip START_UNIT, past eh deadline\n",
					    current->comm));
			scsi_device_put(sdev);
			अवरोध;
		पूर्ण
		stu_scmd = शून्य;
		list_क्रम_each_entry(scmd, work_q, eh_entry)
			अगर (scmd->device == sdev && SCSI_SENSE_VALID(scmd) &&
			    scsi_check_sense(scmd) == FAILED ) अणु
				stu_scmd = scmd;
				अवरोध;
			पूर्ण

		अगर (!stu_scmd)
			जारी;

		SCSI_LOG_ERROR_RECOVERY(3,
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				     "%s: Sending START_UNIT\n",
				    current->comm));

		अगर (!scsi_eh_try_stu(stu_scmd)) अणु
			अगर (!scsi_device_online(sdev) ||
			    !scsi_eh_tur(stu_scmd)) अणु
				list_क्रम_each_entry_safe(scmd, next,
							  work_q, eh_entry) अणु
					अगर (scmd->device == sdev &&
					    scsi_eh_action(scmd, SUCCESS) == SUCCESS)
						scsi_eh_finish_cmd(scmd, करोne_q);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			SCSI_LOG_ERROR_RECOVERY(3,
				sdev_prपूर्णांकk(KERN_INFO, sdev,
					    "%s: START_UNIT failed\n",
					    current->comm));
		पूर्ण
	पूर्ण

	वापस list_empty(work_q);
पूर्ण


/**
 * scsi_eh_bus_device_reset - send bdr अगर needed
 * @shost:	scsi host being recovered.
 * @work_q:	&list_head क्रम pending commands.
 * @करोne_q:	&list_head क्रम processed commands.
 *
 * Notes:
 *    Try a bus device reset.  Still, look to see whether we have multiple
 *    devices that are jammed or not - अगर we have multiple devices, it
 *    makes no sense to try bus_device_reset - we really would need to try
 *    a bus_reset instead.
 */
अटल पूर्णांक scsi_eh_bus_device_reset(काष्ठा Scsi_Host *shost,
				    काष्ठा list_head *work_q,
				    काष्ठा list_head *करोne_q)
अणु
	काष्ठा scsi_cmnd *scmd, *bdr_scmd, *next;
	काष्ठा scsi_device *sdev;
	क्रमागत scsi_disposition rtn;

	shost_क्रम_each_device(sdev, shost) अणु
		अगर (scsi_host_eh_past_deadline(shost)) अणु
			SCSI_LOG_ERROR_RECOVERY(3,
				sdev_prपूर्णांकk(KERN_INFO, sdev,
					    "%s: skip BDR, past eh deadline\n",
					     current->comm));
			scsi_device_put(sdev);
			अवरोध;
		पूर्ण
		bdr_scmd = शून्य;
		list_क्रम_each_entry(scmd, work_q, eh_entry)
			अगर (scmd->device == sdev) अणु
				bdr_scmd = scmd;
				अवरोध;
			पूर्ण

		अगर (!bdr_scmd)
			जारी;

		SCSI_LOG_ERROR_RECOVERY(3,
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				     "%s: Sending BDR\n", current->comm));
		rtn = scsi_try_bus_device_reset(bdr_scmd);
		अगर (rtn == SUCCESS || rtn == FAST_IO_FAIL) अणु
			अगर (!scsi_device_online(sdev) ||
			    rtn == FAST_IO_FAIL ||
			    !scsi_eh_tur(bdr_scmd)) अणु
				list_क्रम_each_entry_safe(scmd, next,
							 work_q, eh_entry) अणु
					अगर (scmd->device == sdev &&
					    scsi_eh_action(scmd, rtn) != FAILED)
						scsi_eh_finish_cmd(scmd,
								   करोne_q);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			SCSI_LOG_ERROR_RECOVERY(3,
				sdev_prपूर्णांकk(KERN_INFO, sdev,
					    "%s: BDR failed\n", current->comm));
		पूर्ण
	पूर्ण

	वापस list_empty(work_q);
पूर्ण

/**
 * scsi_eh_target_reset - send target reset अगर needed
 * @shost:	scsi host being recovered.
 * @work_q:	&list_head क्रम pending commands.
 * @करोne_q:	&list_head क्रम processed commands.
 *
 * Notes:
 *    Try a target reset.
 */
अटल पूर्णांक scsi_eh_target_reset(काष्ठा Scsi_Host *shost,
				काष्ठा list_head *work_q,
				काष्ठा list_head *करोne_q)
अणु
	LIST_HEAD(पंचांगp_list);
	LIST_HEAD(check_list);

	list_splice_init(work_q, &पंचांगp_list);

	जबतक (!list_empty(&पंचांगp_list)) अणु
		काष्ठा scsi_cmnd *next, *scmd;
		क्रमागत scsi_disposition rtn;
		अचिन्हित पूर्णांक id;

		अगर (scsi_host_eh_past_deadline(shost)) अणु
			/* push back on work queue क्रम further processing */
			list_splice_init(&check_list, work_q);
			list_splice_init(&पंचांगp_list, work_q);
			SCSI_LOG_ERROR_RECOVERY(3,
				shost_prपूर्णांकk(KERN_INFO, shost,
					    "%s: Skip target reset, past eh deadline\n",
					     current->comm));
			वापस list_empty(work_q);
		पूर्ण

		scmd = list_entry(पंचांगp_list.next, काष्ठा scsi_cmnd, eh_entry);
		id = scmd_id(scmd);

		SCSI_LOG_ERROR_RECOVERY(3,
			shost_prपूर्णांकk(KERN_INFO, shost,
				     "%s: Sending target reset to target %d\n",
				     current->comm, id));
		rtn = scsi_try_target_reset(scmd);
		अगर (rtn != SUCCESS && rtn != FAST_IO_FAIL)
			SCSI_LOG_ERROR_RECOVERY(3,
				shost_prपूर्णांकk(KERN_INFO, shost,
					     "%s: Target reset failed"
					     " target: %d\n",
					     current->comm, id));
		list_क्रम_each_entry_safe(scmd, next, &पंचांगp_list, eh_entry) अणु
			अगर (scmd_id(scmd) != id)
				जारी;

			अगर (rtn == SUCCESS)
				list_move_tail(&scmd->eh_entry, &check_list);
			अन्यथा अगर (rtn == FAST_IO_FAIL)
				scsi_eh_finish_cmd(scmd, करोne_q);
			अन्यथा
				/* push back on work queue क्रम further processing */
				list_move(&scmd->eh_entry, work_q);
		पूर्ण
	पूर्ण

	वापस scsi_eh_test_devices(&check_list, work_q, करोne_q, 0);
पूर्ण

/**
 * scsi_eh_bus_reset - send a bus reset
 * @shost:	&scsi host being recovered.
 * @work_q:	&list_head क्रम pending commands.
 * @करोne_q:	&list_head क्रम processed commands.
 */
अटल पूर्णांक scsi_eh_bus_reset(काष्ठा Scsi_Host *shost,
			     काष्ठा list_head *work_q,
			     काष्ठा list_head *करोne_q)
अणु
	काष्ठा scsi_cmnd *scmd, *chan_scmd, *next;
	LIST_HEAD(check_list);
	अचिन्हित पूर्णांक channel;
	क्रमागत scsi_disposition rtn;

	/*
	 * we really want to loop over the various channels, and करो this on
	 * a channel by channel basis.  we should also check to see अगर any
	 * of the failed commands are on soft_reset devices, and अगर so, skip
	 * the reset.
	 */

	क्रम (channel = 0; channel <= shost->max_channel; channel++) अणु
		अगर (scsi_host_eh_past_deadline(shost)) अणु
			list_splice_init(&check_list, work_q);
			SCSI_LOG_ERROR_RECOVERY(3,
				shost_prपूर्णांकk(KERN_INFO, shost,
					    "%s: skip BRST, past eh deadline\n",
					     current->comm));
			वापस list_empty(work_q);
		पूर्ण

		chan_scmd = शून्य;
		list_क्रम_each_entry(scmd, work_q, eh_entry) अणु
			अगर (channel == scmd_channel(scmd)) अणु
				chan_scmd = scmd;
				अवरोध;
				/*
				 * FIXME add back in some support क्रम
				 * soft_reset devices.
				 */
			पूर्ण
		पूर्ण

		अगर (!chan_scmd)
			जारी;
		SCSI_LOG_ERROR_RECOVERY(3,
			shost_prपूर्णांकk(KERN_INFO, shost,
				     "%s: Sending BRST chan: %d\n",
				     current->comm, channel));
		rtn = scsi_try_bus_reset(chan_scmd);
		अगर (rtn == SUCCESS || rtn == FAST_IO_FAIL) अणु
			list_क्रम_each_entry_safe(scmd, next, work_q, eh_entry) अणु
				अगर (channel == scmd_channel(scmd)) अणु
					अगर (rtn == FAST_IO_FAIL)
						scsi_eh_finish_cmd(scmd,
								   करोne_q);
					अन्यथा
						list_move_tail(&scmd->eh_entry,
							       &check_list);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			SCSI_LOG_ERROR_RECOVERY(3,
				shost_prपूर्णांकk(KERN_INFO, shost,
					     "%s: BRST failed chan: %d\n",
					     current->comm, channel));
		पूर्ण
	पूर्ण
	वापस scsi_eh_test_devices(&check_list, work_q, करोne_q, 0);
पूर्ण

/**
 * scsi_eh_host_reset - send a host reset
 * @shost:	host to be reset.
 * @work_q:	&list_head क्रम pending commands.
 * @करोne_q:	&list_head क्रम processed commands.
 */
अटल पूर्णांक scsi_eh_host_reset(काष्ठा Scsi_Host *shost,
			      काष्ठा list_head *work_q,
			      काष्ठा list_head *करोne_q)
अणु
	काष्ठा scsi_cmnd *scmd, *next;
	LIST_HEAD(check_list);
	क्रमागत scsi_disposition rtn;

	अगर (!list_empty(work_q)) अणु
		scmd = list_entry(work_q->next,
				  काष्ठा scsi_cmnd, eh_entry);

		SCSI_LOG_ERROR_RECOVERY(3,
			shost_prपूर्णांकk(KERN_INFO, shost,
				     "%s: Sending HRST\n",
				     current->comm));

		rtn = scsi_try_host_reset(scmd);
		अगर (rtn == SUCCESS) अणु
			list_splice_init(work_q, &check_list);
		पूर्ण अन्यथा अगर (rtn == FAST_IO_FAIL) अणु
			list_क्रम_each_entry_safe(scmd, next, work_q, eh_entry) अणु
					scsi_eh_finish_cmd(scmd, करोne_q);
			पूर्ण
		पूर्ण अन्यथा अणु
			SCSI_LOG_ERROR_RECOVERY(3,
				shost_prपूर्णांकk(KERN_INFO, shost,
					     "%s: HRST failed\n",
					     current->comm));
		पूर्ण
	पूर्ण
	वापस scsi_eh_test_devices(&check_list, work_q, करोne_q, 1);
पूर्ण

/**
 * scsi_eh_offline_sdevs - offline scsi devices that fail to recover
 * @work_q:	&list_head क्रम pending commands.
 * @करोne_q:	&list_head क्रम processed commands.
 */
अटल व्योम scsi_eh_offline_sdevs(काष्ठा list_head *work_q,
				  काष्ठा list_head *करोne_q)
अणु
	काष्ठा scsi_cmnd *scmd, *next;
	काष्ठा scsi_device *sdev;

	list_क्रम_each_entry_safe(scmd, next, work_q, eh_entry) अणु
		sdev_prपूर्णांकk(KERN_INFO, scmd->device, "Device offlined - "
			    "not ready after error recovery\n");
		sdev = scmd->device;

		mutex_lock(&sdev->state_mutex);
		scsi_device_set_state(sdev, SDEV_OFFLINE);
		mutex_unlock(&sdev->state_mutex);

		scsi_eh_finish_cmd(scmd, करोne_q);
	पूर्ण
	वापस;
पूर्ण

/**
 * scsi_noretry_cmd - determine अगर command should be failed fast
 * @scmd:	SCSI cmd to examine.
 */
पूर्णांक scsi_noretry_cmd(काष्ठा scsi_cmnd *scmd)
अणु
	चयन (host_byte(scmd->result)) अणु
	हाल DID_OK:
		अवरोध;
	हाल DID_TIME_OUT:
		जाओ check_type;
	हाल DID_BUS_BUSY:
		वापस (scmd->request->cmd_flags & REQ_FAILFAST_TRANSPORT);
	हाल DID_PARITY:
		वापस (scmd->request->cmd_flags & REQ_FAILFAST_DEV);
	हाल DID_ERROR:
		अगर (msg_byte(scmd->result) == COMMAND_COMPLETE &&
		    status_byte(scmd->result) == RESERVATION_CONFLICT)
			वापस 0;
		fallthrough;
	हाल DID_SOFT_ERROR:
		वापस (scmd->request->cmd_flags & REQ_FAILFAST_DRIVER);
	पूर्ण

	अगर (status_byte(scmd->result) != CHECK_CONDITION)
		वापस 0;

check_type:
	/*
	 * assume caller has checked sense and determined
	 * the check condition was retryable.
	 */
	अगर (scmd->request->cmd_flags & REQ_FAILFAST_DEV ||
	    blk_rq_is_passthrough(scmd->request))
		वापस 1;

	वापस 0;
पूर्ण

/**
 * scsi_decide_disposition - Disposition a cmd on वापस from LLD.
 * @scmd:	SCSI cmd to examine.
 *
 * Notes:
 *    This is *only* called when we are examining the status after sending
 *    out the actual data command.  any commands that are queued क्रम error
 *    recovery (e.g. test_unit_पढ़ोy) करो *not* come through here.
 *
 *    When this routine वापसs failed, it means the error handler thपढ़ो
 *    is woken.  In हालs where the error code indicates an error that
 *    करोesn't require the error handler read (i.e. we don't need to
 *    पात/reset), this function should वापस SUCCESS.
 */
क्रमागत scsi_disposition scsi_decide_disposition(काष्ठा scsi_cmnd *scmd)
अणु
	क्रमागत scsi_disposition rtn;

	/*
	 * अगर the device is offline, then we clearly just pass the result back
	 * up to the top level.
	 */
	अगर (!scsi_device_online(scmd->device)) अणु
		SCSI_LOG_ERROR_RECOVERY(5, scmd_prपूर्णांकk(KERN_INFO, scmd,
			"%s: device offline - report as SUCCESS\n", __func__));
		वापस SUCCESS;
	पूर्ण

	/*
	 * first check the host byte, to see अगर there is anything in there
	 * that would indicate what we need to करो.
	 */
	चयन (host_byte(scmd->result)) अणु
	हाल DID_PASSTHROUGH:
		/*
		 * no matter what, pass this through to the upper layer.
		 * nuke this special code so that it looks like we are saying
		 * did_ok.
		 */
		scmd->result &= 0xff00ffff;
		वापस SUCCESS;
	हाल DID_OK:
		/*
		 * looks good.  drop through, and check the next byte.
		 */
		अवरोध;
	हाल DID_ABORT:
		अगर (scmd->eh_eflags & SCSI_EH_ABORT_SCHEDULED) अणु
			set_host_byte(scmd, DID_TIME_OUT);
			वापस SUCCESS;
		पूर्ण
		fallthrough;
	हाल DID_NO_CONNECT:
	हाल DID_BAD_TARGET:
		/*
		 * note - this means that we just report the status back
		 * to the top level driver, not that we actually think
		 * that it indicates SUCCESS.
		 */
		वापस SUCCESS;
	हाल DID_SOFT_ERROR:
		/*
		 * when the low level driver वापसs did_soft_error,
		 * it is responsible क्रम keeping an पूर्णांकernal retry counter
		 * in order to aव्योम endless loops (db)
		 */
		जाओ maybe_retry;
	हाल DID_IMM_RETRY:
		वापस NEEDS_RETRY;

	हाल DID_REQUEUE:
		वापस ADD_TO_MLQUEUE;
	हाल DID_TRANSPORT_DISRUPTED:
		/*
		 * LLD/transport was disrupted during processing of the IO.
		 * The transport class is now blocked/blocking,
		 * and the transport will decide what to करो with the IO
		 * based on its समयrs and recovery capablilities अगर
		 * there are enough retries.
		 */
		जाओ maybe_retry;
	हाल DID_TRANSPORT_FAILFAST:
		/*
		 * The transport decided to failfast the IO (most likely
		 * the fast io fail पंचांगo fired), so send IO directly upwards.
		 */
		वापस SUCCESS;
	हाल DID_TRANSPORT_MARGINAL:
		/*
		 * caller has decided not to करो retries on
		 * पात success, so send IO directly upwards
		 */
		वापस SUCCESS;
	हाल DID_ERROR:
		अगर (msg_byte(scmd->result) == COMMAND_COMPLETE &&
		    status_byte(scmd->result) == RESERVATION_CONFLICT)
			/*
			 * execute reservation conflict processing code
			 * lower करोwn
			 */
			अवरोध;
		fallthrough;
	हाल DID_BUS_BUSY:
	हाल DID_PARITY:
		जाओ maybe_retry;
	हाल DID_TIME_OUT:
		/*
		 * when we scan the bus, we get समयout messages क्रम
		 * these commands अगर there is no device available.
		 * other hosts report did_no_connect क्रम the same thing.
		 */
		अगर ((scmd->cmnd[0] == TEST_UNIT_READY ||
		     scmd->cmnd[0] == INQUIRY)) अणु
			वापस SUCCESS;
		पूर्ण अन्यथा अणु
			वापस FAILED;
		पूर्ण
	हाल DID_RESET:
		वापस SUCCESS;
	शेष:
		वापस FAILED;
	पूर्ण

	/*
	 * next, check the message byte.
	 */
	अगर (msg_byte(scmd->result) != COMMAND_COMPLETE)
		वापस FAILED;

	/*
	 * check the status byte to see अगर this indicates anything special.
	 */
	चयन (status_byte(scmd->result)) अणु
	हाल QUEUE_FULL:
		scsi_handle_queue_full(scmd->device);
		/*
		 * the हाल of trying to send too many commands to a
		 * tagged queueing device.
		 */
		fallthrough;
	हाल BUSY:
		/*
		 * device can't talk to us at the moment.  Should only
		 * occur (SAM-3) when the task queue is empty, so will cause
		 * the empty queue handling to trigger a stall in the
		 * device.
		 */
		वापस ADD_TO_MLQUEUE;
	हाल GOOD:
		अगर (scmd->cmnd[0] == REPORT_LUNS)
			scmd->device->sdev_target->expecting_lun_change = 0;
		scsi_handle_queue_ramp_up(scmd->device);
		fallthrough;
	हाल COMMAND_TERMINATED:
		वापस SUCCESS;
	हाल TASK_ABORTED:
		जाओ maybe_retry;
	हाल CHECK_CONDITION:
		rtn = scsi_check_sense(scmd);
		अगर (rtn == NEEDS_RETRY)
			जाओ maybe_retry;
		/* अगर rtn == FAILED, we have no sense inक्रमmation;
		 * वापसing FAILED will wake the error handler thपढ़ो
		 * to collect the sense and reकरो the decide
		 * disposition */
		वापस rtn;
	हाल CONDITION_GOOD:
	हाल INTERMEDIATE_GOOD:
	हाल INTERMEDIATE_C_GOOD:
	हाल ACA_ACTIVE:
		/*
		 * who knows?  FIXME(eric)
		 */
		वापस SUCCESS;

	हाल RESERVATION_CONFLICT:
		sdev_prपूर्णांकk(KERN_INFO, scmd->device,
			    "reservation conflict\n");
		set_host_byte(scmd, DID_NEXUS_FAILURE);
		वापस SUCCESS; /* causes immediate i/o error */
	शेष:
		वापस FAILED;
	पूर्ण
	वापस FAILED;

maybe_retry:

	/* we requeue क्रम retry because the error was retryable, and
	 * the request was not marked fast fail.  Note that above,
	 * even अगर the request is marked fast fail, we still requeue
	 * क्रम queue congestion conditions (QUEUE_FULL or BUSY) */
	अगर (scsi_cmd_retry_allowed(scmd) && !scsi_noretry_cmd(scmd)) अणु
		वापस NEEDS_RETRY;
	पूर्ण अन्यथा अणु
		/*
		 * no more retries - report this one back to upper level.
		 */
		वापस SUCCESS;
	पूर्ण
पूर्ण

अटल व्योम eh_lock_करोor_करोne(काष्ठा request *req, blk_status_t status)
अणु
	blk_put_request(req);
पूर्ण

/**
 * scsi_eh_lock_करोor - Prevent medium removal क्रम the specअगरied device
 * @sdev:	SCSI device to prevent medium removal
 *
 * Locking:
 * 	We must be called from process context.
 *
 * Notes:
 * 	We queue up an asynchronous "ALLOW MEDIUM REMOVAL" request on the
 * 	head of the devices request queue, and जारी.
 */
अटल व्योम scsi_eh_lock_करोor(काष्ठा scsi_device *sdev)
अणु
	काष्ठा request *req;
	काष्ठा scsi_request *rq;

	req = blk_get_request(sdev->request_queue, REQ_OP_SCSI_IN, 0);
	अगर (IS_ERR(req))
		वापस;
	rq = scsi_req(req);

	rq->cmd[0] = ALLOW_MEDIUM_REMOVAL;
	rq->cmd[1] = 0;
	rq->cmd[2] = 0;
	rq->cmd[3] = 0;
	rq->cmd[4] = SCSI_REMOVAL_PREVENT;
	rq->cmd[5] = 0;
	rq->cmd_len = COMMAND_SIZE(rq->cmd[0]);

	req->rq_flags |= RQF_QUIET;
	req->समयout = 10 * HZ;
	rq->retries = 5;

	blk_execute_rq_noरुको(शून्य, req, 1, eh_lock_करोor_करोne);
पूर्ण

/**
 * scsi_restart_operations - restart io operations to the specअगरied host.
 * @shost:	Host we are restarting.
 *
 * Notes:
 *    When we entered the error handler, we blocked all further i/o to
 *    this device.  we need to 'reverse' this process.
 */
अटल व्योम scsi_restart_operations(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा scsi_device *sdev;
	अचिन्हित दीर्घ flags;

	/*
	 * If the करोor was locked, we need to insert a करोor lock request
	 * onto the head of the SCSI request queue क्रम the device.  There
	 * is no poपूर्णांक trying to lock the करोor of an off-line device.
	 */
	shost_क्रम_each_device(sdev, shost) अणु
		अगर (scsi_device_online(sdev) && sdev->was_reset && sdev->locked) अणु
			scsi_eh_lock_करोor(sdev);
			sdev->was_reset = 0;
		पूर्ण
	पूर्ण

	/*
	 * next मुक्त up anything directly रुकोing upon the host.  this
	 * will be requests क्रम अक्षरacter device operations, and also क्रम
	 * ioctls to queued block devices.
	 */
	SCSI_LOG_ERROR_RECOVERY(3,
		shost_prपूर्णांकk(KERN_INFO, shost, "waking up host to restart\n"));

	spin_lock_irqsave(shost->host_lock, flags);
	अगर (scsi_host_set_state(shost, SHOST_RUNNING))
		अगर (scsi_host_set_state(shost, SHOST_CANCEL))
			BUG_ON(scsi_host_set_state(shost, SHOST_DEL));
	spin_unlock_irqrestore(shost->host_lock, flags);

	wake_up(&shost->host_रुको);

	/*
	 * finally we need to re-initiate requests that may be pending.  we will
	 * have had everything blocked जबतक error handling is taking place, and
	 * now that error recovery is करोne, we will need to ensure that these
	 * requests are started.
	 */
	scsi_run_host_queues(shost);

	/*
	 * अगर eh is active and host_eh_scheduled is pending we need to re-run
	 * recovery.  we करो this check after scsi_run_host_queues() to allow
	 * everything pent up since the last eh run a chance to make क्रमward
	 * progress beक्रमe we sync again.  Either we'll immediately re-run
	 * recovery or scsi_device_unbusy() will wake us again when these
	 * pending commands complete.
	 */
	spin_lock_irqsave(shost->host_lock, flags);
	अगर (shost->host_eh_scheduled)
		अगर (scsi_host_set_state(shost, SHOST_RECOVERY))
			WARN_ON(scsi_host_set_state(shost, SHOST_CANCEL_RECOVERY));
	spin_unlock_irqrestore(shost->host_lock, flags);
पूर्ण

/**
 * scsi_eh_पढ़ोy_devs - check device पढ़ोy state and recover अगर not.
 * @shost:	host to be recovered.
 * @work_q:	&list_head क्रम pending commands.
 * @करोne_q:	&list_head क्रम processed commands.
 */
व्योम scsi_eh_पढ़ोy_devs(काष्ठा Scsi_Host *shost,
			काष्ठा list_head *work_q,
			काष्ठा list_head *करोne_q)
अणु
	अगर (!scsi_eh_stu(shost, work_q, करोne_q))
		अगर (!scsi_eh_bus_device_reset(shost, work_q, करोne_q))
			अगर (!scsi_eh_target_reset(shost, work_q, करोne_q))
				अगर (!scsi_eh_bus_reset(shost, work_q, करोne_q))
					अगर (!scsi_eh_host_reset(shost, work_q, करोne_q))
						scsi_eh_offline_sdevs(work_q,
								      करोne_q);
पूर्ण
EXPORT_SYMBOL_GPL(scsi_eh_पढ़ोy_devs);

/**
 * scsi_eh_flush_करोne_q - finish processed commands or retry them.
 * @करोne_q:	list_head of processed commands.
 */
व्योम scsi_eh_flush_करोne_q(काष्ठा list_head *करोne_q)
अणु
	काष्ठा scsi_cmnd *scmd, *next;

	list_क्रम_each_entry_safe(scmd, next, करोne_q, eh_entry) अणु
		list_del_init(&scmd->eh_entry);
		अगर (scsi_device_online(scmd->device) &&
		    !scsi_noretry_cmd(scmd) && scsi_cmd_retry_allowed(scmd) &&
			scsi_eh_should_retry_cmd(scmd)) अणु
			SCSI_LOG_ERROR_RECOVERY(3,
				scmd_prपूर्णांकk(KERN_INFO, scmd,
					     "%s: flush retry cmd\n",
					     current->comm));
				scsi_queue_insert(scmd, SCSI_MLQUEUE_EH_RETRY);
		पूर्ण अन्यथा अणु
			/*
			 * If just we got sense क्रम the device (called
			 * scsi_eh_get_sense), scmd->result is alपढ़ोy
			 * set, करो not set DRIVER_TIMEOUT.
			 */
			अगर (!scmd->result)
				scmd->result |= (DRIVER_TIMEOUT << 24);
			SCSI_LOG_ERROR_RECOVERY(3,
				scmd_prपूर्णांकk(KERN_INFO, scmd,
					     "%s: flush finish cmd\n",
					     current->comm));
			scsi_finish_command(scmd);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(scsi_eh_flush_करोne_q);

/**
 * scsi_unjam_host - Attempt to fix a host which has a cmd that failed.
 * @shost:	Host to unjam.
 *
 * Notes:
 *    When we come in here, we *know* that all commands on the bus have
 *    either completed, failed or समयd out.  we also know that no further
 *    commands are being sent to the host, so things are relatively quiet
 *    and we have मुक्तकरोm to fiddle with things as we wish.
 *
 *    This is only the *शेष* implementation.  it is possible क्रम
 *    inभागidual drivers to supply their own version of this function, and
 *    अगर the मुख्यtainer wishes to करो this, it is strongly suggested that
 *    this function be taken as a ढाँचा and modअगरied.  this function
 *    was deचिन्हित to correctly handle problems क्रम about 95% of the
 *    dअगरferent हालs out there, and it should always provide at least a
 *    reasonable amount of error recovery.
 *
 *    Any command marked 'failed' or 'timeout' must eventually have
 *    scsi_finish_cmd() called क्रम it.  we करो all of the retry stuff
 *    here, so when we restart the host after we वापस it should have an
 *    empty queue.
 */
अटल व्योम scsi_unjam_host(काष्ठा Scsi_Host *shost)
अणु
	अचिन्हित दीर्घ flags;
	LIST_HEAD(eh_work_q);
	LIST_HEAD(eh_करोne_q);

	spin_lock_irqsave(shost->host_lock, flags);
	list_splice_init(&shost->eh_cmd_q, &eh_work_q);
	spin_unlock_irqrestore(shost->host_lock, flags);

	SCSI_LOG_ERROR_RECOVERY(1, scsi_eh_prt_fail_stats(shost, &eh_work_q));

	अगर (!scsi_eh_get_sense(&eh_work_q, &eh_करोne_q))
		scsi_eh_पढ़ोy_devs(shost, &eh_work_q, &eh_करोne_q);

	spin_lock_irqsave(shost->host_lock, flags);
	अगर (shost->eh_deadline != -1)
		shost->last_reset = 0;
	spin_unlock_irqrestore(shost->host_lock, flags);
	scsi_eh_flush_करोne_q(&eh_करोne_q);
पूर्ण

/**
 * scsi_error_handler - SCSI error handler thपढ़ो
 * @data:	Host क्रम which we are running.
 *
 * Notes:
 *    This is the मुख्य error handling loop.  This is run as a kernel thपढ़ो
 *    क्रम every SCSI host and handles all error handling activity.
 */
पूर्णांक scsi_error_handler(व्योम *data)
अणु
	काष्ठा Scsi_Host *shost = data;

	/*
	 * We use TASK_INTERRUPTIBLE so that the thपढ़ो is not
	 * counted against the load average as a running process.
	 * We never actually get पूर्णांकerrupted because kthपढ़ो_run
	 * disables संकेत delivery क्रम the created thपढ़ो.
	 */
	जबतक (true) अणु
		/*
		 * The sequence in kthपढ़ो_stop() sets the stop flag first
		 * then wakes the process.  To aव्योम missed wakeups, the task
		 * should always be in a non running state beक्रमe the stop
		 * flag is checked
		 */
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		अगर ((shost->host_failed == 0 && shost->host_eh_scheduled == 0) ||
		    shost->host_failed != scsi_host_busy(shost)) अणु
			SCSI_LOG_ERROR_RECOVERY(1,
				shost_prपूर्णांकk(KERN_INFO, shost,
					     "scsi_eh_%d: sleeping\n",
					     shost->host_no));
			schedule();
			जारी;
		पूर्ण

		__set_current_state(TASK_RUNNING);
		SCSI_LOG_ERROR_RECOVERY(1,
			shost_prपूर्णांकk(KERN_INFO, shost,
				     "scsi_eh_%d: waking up %d/%d/%d\n",
				     shost->host_no, shost->host_eh_scheduled,
				     shost->host_failed,
				     scsi_host_busy(shost)));

		/*
		 * We have a host that is failing क्रम some reason.  Figure out
		 * what we need to करो to get it up and online again (अगर we can).
		 * If we fail, we end up taking the thing offline.
		 */
		अगर (!shost->eh_noresume && scsi_स्वतःpm_get_host(shost) != 0) अणु
			SCSI_LOG_ERROR_RECOVERY(1,
				shost_prपूर्णांकk(KERN_ERR, shost,
					     "scsi_eh_%d: unable to autoresume\n",
					     shost->host_no));
			जारी;
		पूर्ण

		अगर (shost->transportt->eh_strategy_handler)
			shost->transportt->eh_strategy_handler(shost);
		अन्यथा
			scsi_unjam_host(shost);

		/* All scmds have been handled */
		shost->host_failed = 0;

		/*
		 * Note - अगर the above fails completely, the action is to take
		 * inभागidual devices offline and flush the queue of any
		 * outstanding requests that may have been pending.  When we
		 * restart, we restart any I/O to any other devices on the bus
		 * which are still online.
		 */
		scsi_restart_operations(shost);
		अगर (!shost->eh_noresume)
			scsi_स्वतःpm_put_host(shost);
	पूर्ण
	__set_current_state(TASK_RUNNING);

	SCSI_LOG_ERROR_RECOVERY(1,
		shost_prपूर्णांकk(KERN_INFO, shost,
			     "Error handler scsi_eh_%d exiting\n",
			     shost->host_no));
	shost->ehandler = शून्य;
	वापस 0;
पूर्ण

/*
 * Function:    scsi_report_bus_reset()
 *
 * Purpose:     Utility function used by low-level drivers to report that
 *		they have observed a bus reset on the bus being handled.
 *
 * Arguments:   shost       - Host in question
 *		channel     - channel on which reset was observed.
 *
 * Returns:     Nothing
 *
 * Lock status: Host lock must be held.
 *
 * Notes:       This only needs to be called अगर the reset is one which
 *		originates from an unknown location.  Resets originated
 *		by the mid-level itself करोn't need to call this, but there
 *		should be no harm.
 *
 *		The मुख्य purpose of this is to make sure that a CHECK_CONDITION
 *		is properly treated.
 */
व्योम scsi_report_bus_reset(काष्ठा Scsi_Host *shost, पूर्णांक channel)
अणु
	काष्ठा scsi_device *sdev;

	__shost_क्रम_each_device(sdev, shost) अणु
		अगर (channel == sdev_channel(sdev))
			__scsi_report_device_reset(sdev, शून्य);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(scsi_report_bus_reset);

/*
 * Function:    scsi_report_device_reset()
 *
 * Purpose:     Utility function used by low-level drivers to report that
 *		they have observed a device reset on the device being handled.
 *
 * Arguments:   shost       - Host in question
 *		channel     - channel on which reset was observed
 *		target	    - target on which reset was observed
 *
 * Returns:     Nothing
 *
 * Lock status: Host lock must be held
 *
 * Notes:       This only needs to be called अगर the reset is one which
 *		originates from an unknown location.  Resets originated
 *		by the mid-level itself करोn't need to call this, but there
 *		should be no harm.
 *
 *		The मुख्य purpose of this is to make sure that a CHECK_CONDITION
 *		is properly treated.
 */
व्योम scsi_report_device_reset(काष्ठा Scsi_Host *shost, पूर्णांक channel, पूर्णांक target)
अणु
	काष्ठा scsi_device *sdev;

	__shost_क्रम_each_device(sdev, shost) अणु
		अगर (channel == sdev_channel(sdev) &&
		    target == sdev_id(sdev))
			__scsi_report_device_reset(sdev, शून्य);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(scsi_report_device_reset);

अटल व्योम
scsi_reset_provider_करोne_command(काष्ठा scsi_cmnd *scmd)
अणु
पूर्ण

/**
 * scsi_ioctl_reset: explicitly reset a host/bus/target/device
 * @dev:	scsi_device to operate on
 * @arg:	reset type (see sg.h)
 */
पूर्णांक
scsi_ioctl_reset(काष्ठा scsi_device *dev, पूर्णांक __user *arg)
अणु
	काष्ठा scsi_cmnd *scmd;
	काष्ठा Scsi_Host *shost = dev->host;
	काष्ठा request *rq;
	अचिन्हित दीर्घ flags;
	पूर्णांक error = 0, val;
	क्रमागत scsi_disposition rtn;

	अगर (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
		वापस -EACCES;

	error = get_user(val, arg);
	अगर (error)
		वापस error;

	अगर (scsi_स्वतःpm_get_host(shost) < 0)
		वापस -EIO;

	error = -EIO;
	rq = kzalloc(माप(काष्ठा request) + माप(काष्ठा scsi_cmnd) +
			shost->hostt->cmd_size, GFP_KERNEL);
	अगर (!rq)
		जाओ out_put_स्वतःpm_host;
	blk_rq_init(शून्य, rq);

	scmd = (काष्ठा scsi_cmnd *)(rq + 1);
	scsi_init_command(dev, scmd);
	scmd->request = rq;
	scmd->cmnd = scsi_req(rq)->cmd;

	scmd->scsi_करोne		= scsi_reset_provider_करोne_command;
	स_रखो(&scmd->sdb, 0, माप(scmd->sdb));

	scmd->cmd_len			= 0;

	scmd->sc_data_direction		= DMA_BIसूचीECTIONAL;

	spin_lock_irqsave(shost->host_lock, flags);
	shost->पंचांगf_in_progress = 1;
	spin_unlock_irqrestore(shost->host_lock, flags);

	चयन (val & ~SG_SCSI_RESET_NO_ESCALATE) अणु
	हाल SG_SCSI_RESET_NOTHING:
		rtn = SUCCESS;
		अवरोध;
	हाल SG_SCSI_RESET_DEVICE:
		rtn = scsi_try_bus_device_reset(scmd);
		अगर (rtn == SUCCESS || (val & SG_SCSI_RESET_NO_ESCALATE))
			अवरोध;
		fallthrough;
	हाल SG_SCSI_RESET_TARGET:
		rtn = scsi_try_target_reset(scmd);
		अगर (rtn == SUCCESS || (val & SG_SCSI_RESET_NO_ESCALATE))
			अवरोध;
		fallthrough;
	हाल SG_SCSI_RESET_BUS:
		rtn = scsi_try_bus_reset(scmd);
		अगर (rtn == SUCCESS || (val & SG_SCSI_RESET_NO_ESCALATE))
			अवरोध;
		fallthrough;
	हाल SG_SCSI_RESET_HOST:
		rtn = scsi_try_host_reset(scmd);
		अगर (rtn == SUCCESS)
			अवरोध;
		fallthrough;
	शेष:
		rtn = FAILED;
		अवरोध;
	पूर्ण

	error = (rtn == SUCCESS) ? 0 : -EIO;

	spin_lock_irqsave(shost->host_lock, flags);
	shost->पंचांगf_in_progress = 0;
	spin_unlock_irqrestore(shost->host_lock, flags);

	/*
	 * be sure to wake up anyone who was sleeping or had their queue
	 * suspended जबतक we perक्रमmed the TMF.
	 */
	SCSI_LOG_ERROR_RECOVERY(3,
		shost_prपूर्णांकk(KERN_INFO, shost,
			     "waking up host to restart after TMF\n"));

	wake_up(&shost->host_रुको);
	scsi_run_host_queues(shost);

	kमुक्त(rq);

out_put_स्वतःpm_host:
	scsi_स्वतःpm_put_host(shost);
	वापस error;
पूर्ण

bool scsi_command_normalize_sense(स्थिर काष्ठा scsi_cmnd *cmd,
				  काष्ठा scsi_sense_hdr *sshdr)
अणु
	वापस scsi_normalize_sense(cmd->sense_buffer,
			SCSI_SENSE_BUFFERSIZE, sshdr);
पूर्ण
EXPORT_SYMBOL(scsi_command_normalize_sense);

/**
 * scsi_get_sense_info_fld - get inक्रमmation field from sense data (either fixed or descriptor क्रमmat)
 * @sense_buffer:	byte array of sense data
 * @sb_len:		number of valid bytes in sense_buffer
 * @info_out:		poपूर्णांकer to 64 पूर्णांकeger where 8 or 4 byte inक्रमmation
 *			field will be placed अगर found.
 *
 * Return value:
 *	true अगर inक्रमmation field found, false अगर not found.
 */
bool scsi_get_sense_info_fld(स्थिर u8 *sense_buffer, पूर्णांक sb_len,
			     u64 *info_out)
अणु
	स्थिर u8 * ucp;

	अगर (sb_len < 7)
		वापस false;
	चयन (sense_buffer[0] & 0x7f) अणु
	हाल 0x70:
	हाल 0x71:
		अगर (sense_buffer[0] & 0x80) अणु
			*info_out = get_unaligned_be32(&sense_buffer[3]);
			वापस true;
		पूर्ण
		वापस false;
	हाल 0x72:
	हाल 0x73:
		ucp = scsi_sense_desc_find(sense_buffer, sb_len,
					   0 /* info desc */);
		अगर (ucp && (0xa == ucp[1])) अणु
			*info_out = get_unaligned_be64(&ucp[4]);
			वापस true;
		पूर्ण
		वापस false;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(scsi_get_sense_info_fld);
