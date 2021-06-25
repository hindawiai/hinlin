<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St - Fअगरth Floor, Boston, MA 02110-1301 USA.
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * BSD LICENSE
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the करोcumentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/completion.h>
#समावेश <linux/irqflags.h>
#समावेश "sas.h"
#समावेश <scsi/libsas.h>
#समावेश "remote_device.h"
#समावेश "remote_node_context.h"
#समावेश "isci.h"
#समावेश "request.h"
#समावेश "task.h"
#समावेश "host.h"

/**
* isci_task_refuse() - complete the request to the upper layer driver in
*     the हाल where an I/O needs to be completed back in the submit path.
* @ihost: host on which the the request was queued
* @task: request to complete
* @response: response code क्रम the completed task.
* @status: status code क्रम the completed task.
*
*/
अटल व्योम isci_task_refuse(काष्ठा isci_host *ihost, काष्ठा sas_task *task,
			     क्रमागत service_response response,
			     क्रमागत exec_status status)

अणु
	अचिन्हित दीर्घ flags;

	/* Normal notअगरication (task_करोne) */
	dev_dbg(&ihost->pdev->dev, "%s: task = %p, response=%d, status=%d\n",
		__func__, task, response, status);

	spin_lock_irqsave(&task->task_state_lock, flags);

	task->task_status.resp = response;
	task->task_status.stat = status;

	/* Normal notअगरication (task_करोne) */
	task->task_state_flags |= SAS_TASK_STATE_DONE;
	task->task_state_flags &= ~(SAS_TASK_AT_INITIATOR |
				    SAS_TASK_STATE_PENDING);
	task->lldd_task = शून्य;
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	task->task_करोne(task);
पूर्ण

#घोषणा क्रम_each_sas_task(num, task) \
	क्रम (; num > 0; num--,\
	     task = list_entry(task->list.next, काष्ठा sas_task, list))


अटल अंतरभूत पूर्णांक isci_device_io_पढ़ोy(काष्ठा isci_remote_device *idev,
				       काष्ठा sas_task *task)
अणु
	वापस idev ? test_bit(IDEV_IO_READY, &idev->flags) ||
		      (test_bit(IDEV_IO_NCQERROR, &idev->flags) &&
		       isci_task_is_ncq_recovery(task))
		    : 0;
पूर्ण
/**
 * isci_task_execute_task() - This function is one of the SAS Doमुख्य Template
 *    functions. This function is called by libsas to send a task करोwn to
 *    hardware.
 * @task: This parameter specअगरies the SAS task to send.
 * @gfp_flags: This parameter specअगरies the context of this call.
 *
 * status, zero indicates success.
 */
पूर्णांक isci_task_execute_task(काष्ठा sas_task *task, gfp_t gfp_flags)
अणु
	काष्ठा isci_host *ihost = dev_to_ihost(task->dev);
	काष्ठा isci_remote_device *idev;
	अचिन्हित दीर्घ flags;
	क्रमागत sci_status status = SCI_FAILURE;
	bool io_पढ़ोy;
	u16 tag;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	idev = isci_lookup_device(task->dev);
	io_पढ़ोy = isci_device_io_पढ़ोy(idev, task);
	tag = isci_alloc_tag(ihost);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	dev_dbg(&ihost->pdev->dev,
		"task: %p, dev: %p idev: %p:%#lx cmd = %p\n",
		task, task->dev, idev, idev ? idev->flags : 0,
		task->uldd_task);

	अगर (!idev) अणु
		isci_task_refuse(ihost, task, SAS_TASK_UNDELIVERED,
				 SAS_DEVICE_UNKNOWN);
	पूर्ण अन्यथा अगर (!io_पढ़ोy || tag == SCI_CONTROLLER_INVALID_IO_TAG) अणु
		/* Indicate QUEUE_FULL so that the scsi midlayer
		 * retries.
		  */
		isci_task_refuse(ihost, task, SAS_TASK_COMPLETE,
				 SAS_QUEUE_FULL);
	पूर्ण अन्यथा अणु
		/* There is a device and it's पढ़ोy क्रम I/O. */
		spin_lock_irqsave(&task->task_state_lock, flags);

		अगर (task->task_state_flags & SAS_TASK_STATE_ABORTED) अणु
			/* The I/O was पातed. */
			spin_unlock_irqrestore(&task->task_state_lock, flags);

			isci_task_refuse(ihost, task,
					 SAS_TASK_UNDELIVERED,
					 SAM_STAT_TASK_ABORTED);
		पूर्ण अन्यथा अणु
			task->task_state_flags |= SAS_TASK_AT_INITIATOR;
			spin_unlock_irqrestore(&task->task_state_lock, flags);

			/* build and send the request. */
			status = isci_request_execute(ihost, idev, task, tag);

			अगर (status != SCI_SUCCESS) अणु
				spin_lock_irqsave(&task->task_state_lock, flags);
				/* Did not really start this command. */
				task->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
				spin_unlock_irqrestore(&task->task_state_lock, flags);

				अगर (test_bit(IDEV_GONE, &idev->flags)) अणु
					/* Indicate that the device
					 * is gone.
					 */
					isci_task_refuse(ihost, task,
						SAS_TASK_UNDELIVERED,
						SAS_DEVICE_UNKNOWN);
				पूर्ण अन्यथा अणु
					/* Indicate QUEUE_FULL so that
					 * the scsi midlayer retries.
					 * If the request failed क्रम
					 * remote device reasons, it
					 * माला_लो वापसed as
					 * SAS_TASK_UNDELIVERED next
					 * समय through.
					 */
					isci_task_refuse(ihost, task,
						SAS_TASK_COMPLETE,
						SAS_QUEUE_FULL);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (status != SCI_SUCCESS && tag != SCI_CONTROLLER_INVALID_IO_TAG) अणु
		spin_lock_irqsave(&ihost->scic_lock, flags);
		/* command never hit the device, so just मुक्त
		 * the tci and skip the sequence increment
		 */
		isci_tci_मुक्त(ihost, ISCI_TAG_TCI(tag));
		spin_unlock_irqrestore(&ihost->scic_lock, flags);
	पूर्ण

	isci_put_device(idev);
	वापस 0;
पूर्ण

अटल काष्ठा isci_request *isci_task_request_build(काष्ठा isci_host *ihost,
						    काष्ठा isci_remote_device *idev,
						    u16 tag, काष्ठा isci_पंचांगf *isci_पंचांगf)
अणु
	क्रमागत sci_status status = SCI_FAILURE;
	काष्ठा isci_request *ireq = शून्य;
	काष्ठा करोमुख्य_device *dev;

	dev_dbg(&ihost->pdev->dev,
		"%s: isci_tmf = %p\n", __func__, isci_पंचांगf);

	dev = idev->करोमुख्य_dev;

	/* करो common allocation and init of request object. */
	ireq = isci_पंचांगf_request_from_tag(ihost, isci_पंचांगf, tag);
	अगर (!ireq)
		वापस शून्य;

	/* let the core करो it's स्थिरruct. */
	status = sci_task_request_स्थिरruct(ihost, idev, tag,
					     ireq);

	अगर (status != SCI_SUCCESS) अणु
		dev_warn(&ihost->pdev->dev,
			 "%s: sci_task_request_construct failed - "
			 "status = 0x%x\n",
			 __func__,
			 status);
		वापस शून्य;
	पूर्ण

	/* XXX convert to get this from task->tproto like other drivers */
	अगर (dev->dev_type == SAS_END_DEVICE) अणु
		isci_पंचांगf->proto = SAS_PROTOCOL_SSP;
		status = sci_task_request_स्थिरruct_ssp(ireq);
		अगर (status != SCI_SUCCESS)
			वापस शून्य;
	पूर्ण

	वापस ireq;
पूर्ण

अटल पूर्णांक isci_task_execute_पंचांगf(काष्ठा isci_host *ihost,
				 काष्ठा isci_remote_device *idev,
				 काष्ठा isci_पंचांगf *पंचांगf, अचिन्हित दीर्घ समयout_ms)
अणु
	DECLARE_COMPLETION_ONSTACK(completion);
	क्रमागत sci_status status = SCI_FAILURE;
	काष्ठा isci_request *ireq;
	पूर्णांक ret = TMF_RESP_FUNC_FAILED;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ समयleft;
	u16 tag;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	tag = isci_alloc_tag(ihost);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	अगर (tag == SCI_CONTROLLER_INVALID_IO_TAG)
		वापस ret;

	/* sanity check, वापस TMF_RESP_FUNC_FAILED
	 * अगर the device is not there and पढ़ोy.
	 */
	अगर (!idev ||
	    (!test_bit(IDEV_IO_READY, &idev->flags) &&
	     !test_bit(IDEV_IO_NCQERROR, &idev->flags))) अणु
		dev_dbg(&ihost->pdev->dev,
			"%s: idev = %p not ready (%#lx)\n",
			__func__,
			idev, idev ? idev->flags : 0);
		जाओ err_tci;
	पूर्ण अन्यथा
		dev_dbg(&ihost->pdev->dev,
			"%s: idev = %p\n",
			__func__, idev);

	/* Assign the poपूर्णांकer to the TMF's completion kernel रुको काष्ठाure. */
	पंचांगf->complete = &completion;
	पंचांगf->status = SCI_FAILURE_TIMEOUT;

	ireq = isci_task_request_build(ihost, idev, tag, पंचांगf);
	अगर (!ireq)
		जाओ err_tci;

	spin_lock_irqsave(&ihost->scic_lock, flags);

	/* start the TMF io. */
	status = sci_controller_start_task(ihost, idev, ireq);

	अगर (status != SCI_SUCCESS) अणु
		dev_dbg(&ihost->pdev->dev,
			 "%s: start_io failed - status = 0x%x, request = %p\n",
			 __func__,
			 status,
			 ireq);
		spin_unlock_irqrestore(&ihost->scic_lock, flags);
		जाओ err_tci;
	पूर्ण
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	/* The RNC must be unsuspended beक्रमe the TMF can get a response. */
	isci_remote_device_resume_from_पात(ihost, idev);

	/* Wait क्रम the TMF to complete, or a समयout. */
	समयleft = रुको_क्रम_completion_समयout(&completion,
					       msecs_to_jअगरfies(समयout_ms));

	अगर (समयleft == 0) अणु
		/* The TMF did not complete - this could be because
		 * of an unplug.  Terminate the TMF request now.
		 */
		isci_remote_device_suspend_terminate(ihost, idev, ireq);
	पूर्ण

	isci_prपूर्णांक_पंचांगf(ihost, पंचांगf);

	अगर (पंचांगf->status == SCI_SUCCESS)
		ret =  TMF_RESP_FUNC_COMPLETE;
	अन्यथा अगर (पंचांगf->status == SCI_FAILURE_IO_RESPONSE_VALID) अणु
		dev_dbg(&ihost->pdev->dev,
			"%s: tmf.status == "
			"SCI_FAILURE_IO_RESPONSE_VALID\n",
			__func__);
		ret =  TMF_RESP_FUNC_COMPLETE;
	पूर्ण
	/* Else - leave the शेष "failed" status alone. */

	dev_dbg(&ihost->pdev->dev,
		"%s: completed request = %p\n",
		__func__,
		ireq);

	वापस ret;

 err_tci:
	spin_lock_irqsave(&ihost->scic_lock, flags);
	isci_tci_मुक्त(ihost, ISCI_TAG_TCI(tag));
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम isci_task_build_पंचांगf(काष्ठा isci_पंचांगf *पंचांगf,
				क्रमागत isci_पंचांगf_function_codes code)
अणु
	स_रखो(पंचांगf, 0, माप(*पंचांगf));
	पंचांगf->पंचांगf_code = code;
पूर्ण

अटल व्योम isci_task_build_पात_task_पंचांगf(काष्ठा isci_पंचांगf *पंचांगf,
					   क्रमागत isci_पंचांगf_function_codes code,
					   काष्ठा isci_request *old_request)
अणु
	isci_task_build_पंचांगf(पंचांगf, code);
	पंचांगf->io_tag = old_request->io_tag;
पूर्ण

/*
 * isci_task_send_lu_reset_sas() - This function is called by of the SAS Doमुख्य
 *    Template functions.
 * @lun: This parameter specअगरies the lun to be reset.
 *
 * status, zero indicates success.
 */
अटल पूर्णांक isci_task_send_lu_reset_sas(
	काष्ठा isci_host *isci_host,
	काष्ठा isci_remote_device *isci_device,
	u8 *lun)
अणु
	काष्ठा isci_पंचांगf पंचांगf;
	पूर्णांक ret = TMF_RESP_FUNC_FAILED;

	dev_dbg(&isci_host->pdev->dev,
		"%s: isci_host = %p, isci_device = %p\n",
		__func__, isci_host, isci_device);
	/* Send the LUN reset to the target.  By the समय the call वापसs,
	 * the TMF has fully exected in the target (in which हाल the वापस
	 * value is "TMF_RESP_FUNC_COMPLETE", or the request समयd-out (or
	 * was otherwise unable to be executed ("TMF_RESP_FUNC_FAILED").
	 */
	isci_task_build_पंचांगf(&पंचांगf, isci_पंचांगf_ssp_lun_reset);

	#घोषणा ISCI_LU_RESET_TIMEOUT_MS 2000 /* 2 second समयout. */
	ret = isci_task_execute_पंचांगf(isci_host, isci_device, &पंचांगf, ISCI_LU_RESET_TIMEOUT_MS);

	अगर (ret == TMF_RESP_FUNC_COMPLETE)
		dev_dbg(&isci_host->pdev->dev,
			"%s: %p: TMF_LU_RESET passed\n",
			__func__, isci_device);
	अन्यथा
		dev_dbg(&isci_host->pdev->dev,
			"%s: %p: TMF_LU_RESET failed (%x)\n",
			__func__, isci_device, ret);

	वापस ret;
पूर्ण

पूर्णांक isci_task_lu_reset(काष्ठा करोमुख्य_device *dev, u8 *lun)
अणु
	काष्ठा isci_host *ihost = dev_to_ihost(dev);
	काष्ठा isci_remote_device *idev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = TMF_RESP_FUNC_COMPLETE;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	idev = isci_get_device(dev->lldd_dev);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	dev_dbg(&ihost->pdev->dev,
		"%s: domain_device=%p, isci_host=%p; isci_device=%p\n",
		__func__, dev, ihost, idev);

	अगर (!idev) अणु
		/* If the device is gone, escalate to I_T_Nexus_Reset. */
		dev_dbg(&ihost->pdev->dev, "%s: No dev\n", __func__);

		ret = TMF_RESP_FUNC_FAILED;
		जाओ out;
	पूर्ण

	/* Suspend the RNC, समाप्त all TCs */
	अगर (isci_remote_device_suspend_terminate(ihost, idev, शून्य)
	    != SCI_SUCCESS) अणु
		/* The suspend/terminate only fails अगर isci_get_device fails */
		ret = TMF_RESP_FUNC_FAILED;
		जाओ out;
	पूर्ण
	/* All pending I/Os have been terminated and cleaned up. */
	अगर (!test_bit(IDEV_GONE, &idev->flags)) अणु
		अगर (dev_is_sata(dev))
			sas_ata_schedule_reset(dev);
		अन्यथा
			/* Send the task management part of the reset. */
			ret = isci_task_send_lu_reset_sas(ihost, idev, lun);
	पूर्ण
 out:
	isci_put_device(idev);
	वापस ret;
पूर्ण


/*	 पूर्णांक (*lldd_clear_nexus_port)(काष्ठा asd_sas_port *); */
पूर्णांक isci_task_clear_nexus_port(काष्ठा asd_sas_port *port)
अणु
	वापस TMF_RESP_FUNC_FAILED;
पूर्ण



पूर्णांक isci_task_clear_nexus_ha(काष्ठा sas_ha_काष्ठा *ha)
अणु
	वापस TMF_RESP_FUNC_FAILED;
पूर्ण

/* Task Management Functions. Must be called from process context.	 */

/**
 * isci_task_पात_task() - This function is one of the SAS Doमुख्य Template
 *    functions. This function is called by libsas to पात a specअगरied task.
 * @task: This parameter specअगरies the SAS task to पात.
 *
 * status, zero indicates success.
 */
पूर्णांक isci_task_पात_task(काष्ठा sas_task *task)
अणु
	काष्ठा isci_host *ihost = dev_to_ihost(task->dev);
	DECLARE_COMPLETION_ONSTACK(पातed_io_completion);
	काष्ठा isci_request       *old_request = शून्य;
	काष्ठा isci_remote_device *idev = शून्य;
	काष्ठा isci_पंचांगf           पंचांगf;
	पूर्णांक                       ret = TMF_RESP_FUNC_FAILED;
	अचिन्हित दीर्घ             flags;
	पूर्णांक                       target_करोne_alपढ़ोy = 0;

	/* Get the isci_request reference from the task.  Note that
	 * this check करोes not depend on the pending request list
	 * in the device, because tasks driving resets may land here
	 * after completion in the core.
	 */
	spin_lock_irqsave(&ihost->scic_lock, flags);
	spin_lock(&task->task_state_lock);

	old_request = task->lldd_task;

	/* If task is alपढ़ोy करोne, the request isn't valid */
	अगर (!(task->task_state_flags & SAS_TASK_STATE_DONE) &&
	    (task->task_state_flags & SAS_TASK_AT_INITIATOR) &&
	    old_request) अणु
		idev = isci_get_device(task->dev->lldd_dev);
		target_करोne_alपढ़ोy = test_bit(IREQ_COMPLETE_IN_TARGET,
					       &old_request->flags);
	पूर्ण
	spin_unlock(&task->task_state_lock);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	dev_warn(&ihost->pdev->dev,
		 "%s: dev = %p (%s%s), task = %p, old_request == %p\n",
		 __func__, idev,
		 (dev_is_sata(task->dev) ? "STP/SATA"
					 : ((dev_is_expander(task->dev->dev_type))
						? "SMP"
						: "SSP")),
		 ((idev) ? ((test_bit(IDEV_GONE, &idev->flags))
			   ? " IDEV_GONE"
			   : "")
			 : " <NULL>"),
		 task, old_request);

	/* Device reset conditions संकेतled in task_state_flags are the
	 * responsbility of libsas to observe at the start of the error
	 * handler thपढ़ो.
	 */
	अगर (!idev || !old_request) अणु
		/* The request has alपढ़ोy completed and there
		* is nothing to करो here other than to set the task
		* करोne bit, and indicate that the task पात function
		* was successful.
		*/
		spin_lock_irqsave(&task->task_state_lock, flags);
		task->task_state_flags |= SAS_TASK_STATE_DONE;
		task->task_state_flags &= ~(SAS_TASK_AT_INITIATOR |
					    SAS_TASK_STATE_PENDING);
		spin_unlock_irqrestore(&task->task_state_lock, flags);

		ret = TMF_RESP_FUNC_COMPLETE;

		dev_warn(&ihost->pdev->dev,
			 "%s: abort task not needed for %p\n",
			 __func__, task);
		जाओ out;
	पूर्ण
	/* Suspend the RNC, समाप्त the TC */
	अगर (isci_remote_device_suspend_terminate(ihost, idev, old_request)
	    != SCI_SUCCESS) अणु
		dev_warn(&ihost->pdev->dev,
			 "%s: isci_remote_device_reset_terminate(dev=%p, "
				 "req=%p, task=%p) failed\n",
			 __func__, idev, old_request, task);
		ret = TMF_RESP_FUNC_FAILED;
		जाओ out;
	पूर्ण
	spin_lock_irqsave(&ihost->scic_lock, flags);

	अगर (task->task_proto == SAS_PROTOCOL_SMP ||
	    sas_protocol_ata(task->task_proto) ||
	    target_करोne_alपढ़ोy ||
	    test_bit(IDEV_GONE, &idev->flags)) अणु

		spin_unlock_irqrestore(&ihost->scic_lock, flags);

		/* No task to send, so explicitly resume the device here */
		isci_remote_device_resume_from_पात(ihost, idev);

		dev_warn(&ihost->pdev->dev,
			 "%s: %s request"
				 " or complete_in_target (%d), "
				 "or IDEV_GONE (%d), thus no TMF\n",
			 __func__,
			 ((task->task_proto == SAS_PROTOCOL_SMP)
			  ? "SMP"
			  : (sas_protocol_ata(task->task_proto)
				? "SATA/STP"
				: "<other>")
			  ),
			 test_bit(IREQ_COMPLETE_IN_TARGET,
				  &old_request->flags),
			 test_bit(IDEV_GONE, &idev->flags));

		spin_lock_irqsave(&task->task_state_lock, flags);
		task->task_state_flags &= ~(SAS_TASK_AT_INITIATOR |
					    SAS_TASK_STATE_PENDING);
		task->task_state_flags |= SAS_TASK_STATE_DONE;
		spin_unlock_irqrestore(&task->task_state_lock, flags);

		ret = TMF_RESP_FUNC_COMPLETE;
	पूर्ण अन्यथा अणु
		/* Fill in the पंचांगf काष्ठाure */
		isci_task_build_पात_task_पंचांगf(&पंचांगf, isci_पंचांगf_ssp_task_पात,
					       old_request);

		spin_unlock_irqrestore(&ihost->scic_lock, flags);

		/* Send the task management request. */
		#घोषणा ISCI_ABORT_TASK_TIMEOUT_MS 500 /* 1/2 second समयout */
		ret = isci_task_execute_पंचांगf(ihost, idev, &पंचांगf,
					    ISCI_ABORT_TASK_TIMEOUT_MS);
	पूर्ण
out:
	dev_warn(&ihost->pdev->dev,
		 "%s: Done; dev = %p, task = %p , old_request == %p\n",
		 __func__, idev, task, old_request);
	isci_put_device(idev);
	वापस ret;
पूर्ण

/**
 * isci_task_पात_task_set() - This function is one of the SAS Doमुख्य Template
 *    functions. This is one of the Task Management functoins called by libsas,
 *    to पात all task क्रम the given lun.
 * @d_device: This parameter specअगरies the करोमुख्य device associated with this
 *    request.
 * @lun: This parameter specअगरies the lun associated with this request.
 *
 * status, zero indicates success.
 */
पूर्णांक isci_task_पात_task_set(
	काष्ठा करोमुख्य_device *d_device,
	u8 *lun)
अणु
	वापस TMF_RESP_FUNC_FAILED;
पूर्ण


/**
 * isci_task_clear_aca() - This function is one of the SAS Doमुख्य Template
 *    functions. This is one of the Task Management functoins called by libsas.
 * @d_device: This parameter specअगरies the करोमुख्य device associated with this
 *    request.
 * @lun: This parameter specअगरies the lun	 associated with this request.
 *
 * status, zero indicates success.
 */
पूर्णांक isci_task_clear_aca(
	काष्ठा करोमुख्य_device *d_device,
	u8 *lun)
अणु
	वापस TMF_RESP_FUNC_FAILED;
पूर्ण



/**
 * isci_task_clear_task_set() - This function is one of the SAS Doमुख्य Template
 *    functions. This is one of the Task Management functoins called by libsas.
 * @d_device: This parameter specअगरies the करोमुख्य device associated with this
 *    request.
 * @lun: This parameter specअगरies the lun	 associated with this request.
 *
 * status, zero indicates success.
 */
पूर्णांक isci_task_clear_task_set(
	काष्ठा करोमुख्य_device *d_device,
	u8 *lun)
अणु
	वापस TMF_RESP_FUNC_FAILED;
पूर्ण


/**
 * isci_task_query_task() - This function is implemented to cause libsas to
 *    correctly escalate the failed पात to a LUN or target reset (this is
 *    because sas_scsi_find_task libsas function करोes not correctly पूर्णांकerpret
 *    all वापस codes from the पात task call).  When TMF_RESP_FUNC_SUCC is
 *    वापसed, libsas turns this पूर्णांकo a LUN reset; when FUNC_FAILED is
 *    वापसed, libsas will turn this पूर्णांकo a target reset
 * @task: This parameter specअगरies the sas task being queried.
 *
 * status, zero indicates success.
 */
पूर्णांक isci_task_query_task(
	काष्ठा sas_task *task)
अणु
	/* See अगर there is a pending device reset क्रम this device. */
	अगर (task->task_state_flags & SAS_TASK_NEED_DEV_RESET)
		वापस TMF_RESP_FUNC_FAILED;
	अन्यथा
		वापस TMF_RESP_FUNC_SUCC;
पूर्ण

/*
 * isci_task_request_complete() - This function is called by the sci core when
 *    an task request completes.
 * @ihost: This parameter specअगरies the ISCI host object
 * @ireq: This parameter is the completed isci_request object.
 * @completion_status: This parameter specअगरies the completion status from the
 *    sci core.
 *
 * none.
 */
व्योम
isci_task_request_complete(काष्ठा isci_host *ihost,
			   काष्ठा isci_request *ireq,
			   क्रमागत sci_task_status completion_status)
अणु
	काष्ठा isci_पंचांगf *पंचांगf = isci_request_access_पंचांगf(ireq);
	काष्ठा completion *पंचांगf_complete = शून्य;

	dev_dbg(&ihost->pdev->dev,
		"%s: request = %p, status=%d\n",
		__func__, ireq, completion_status);

	set_bit(IREQ_COMPLETE_IN_TARGET, &ireq->flags);

	अगर (पंचांगf) अणु
		पंचांगf->status = completion_status;

		अगर (पंचांगf->proto == SAS_PROTOCOL_SSP) अणु
			स_नकल(&पंचांगf->resp.resp_iu,
			       &ireq->ssp.rsp,
			       SSP_RESP_IU_MAX_SIZE);
		पूर्ण अन्यथा अगर (पंचांगf->proto == SAS_PROTOCOL_SATA) अणु
			स_नकल(&पंचांगf->resp.d2h_fis,
			       &ireq->stp.rsp,
			       माप(काष्ठा dev_to_host_fis));
		पूर्ण
		/* PRINT_TMF( ((काष्ठा isci_पंचांगf *)request->task)); */
		पंचांगf_complete = पंचांगf->complete;
	पूर्ण
	sci_controller_complete_io(ihost, ireq->target_device, ireq);
	/* set the 'terminated' flag handle to make sure it cannot be terminated
	 *  or completed again.
	 */
	set_bit(IREQ_TERMINATED, &ireq->flags);

	अगर (test_and_clear_bit(IREQ_ABORT_PATH_ACTIVE, &ireq->flags))
		wake_up_all(&ihost->eventq);

	अगर (!test_bit(IREQ_NO_AUTO_FREE_TAG, &ireq->flags))
		isci_मुक्त_tag(ihost, ireq->io_tag);

	/* The task management part completes last. */
	अगर (पंचांगf_complete)
		complete(पंचांगf_complete);
पूर्ण

अटल पूर्णांक isci_reset_device(काष्ठा isci_host *ihost,
			     काष्ठा करोमुख्य_device *dev,
			     काष्ठा isci_remote_device *idev)
अणु
	पूर्णांक rc = TMF_RESP_FUNC_COMPLETE, reset_stat = -1;
	काष्ठा sas_phy *phy = sas_get_local_phy(dev);
	काष्ठा isci_port *iport = dev->port->lldd_port;

	dev_dbg(&ihost->pdev->dev, "%s: idev %p\n", __func__, idev);

	/* Suspend the RNC, terminate all outstanding TCs. */
	अगर (isci_remote_device_suspend_terminate(ihost, idev, शून्य)
	    != SCI_SUCCESS) अणु
		rc = TMF_RESP_FUNC_FAILED;
		जाओ out;
	पूर्ण
	/* Note that since the termination क्रम outstanding requests succeeded,
	 * this function will वापस success.  This is because the resets will
	 * only fail अगर the device has been हटाओd (ie. hotplug), and the
	 * primary duty of this function is to cleanup tasks, so that is the
	 * relevant status.
	 */
	अगर (!test_bit(IDEV_GONE, &idev->flags)) अणु
		अगर (scsi_is_sas_phy_local(phy)) अणु
			काष्ठा isci_phy *iphy = &ihost->phys[phy->number];

			reset_stat = isci_port_perक्रमm_hard_reset(ihost, iport,
								  iphy);
		पूर्ण अन्यथा
			reset_stat = sas_phy_reset(phy, !dev_is_sata(dev));
	पूर्ण
	/* Explicitly resume the RNC here, since there was no task sent. */
	isci_remote_device_resume_from_पात(ihost, idev);

	dev_dbg(&ihost->pdev->dev, "%s: idev %p complete, reset_stat=%d.\n",
		__func__, idev, reset_stat);
 out:
	sas_put_local_phy(phy);
	वापस rc;
पूर्ण

पूर्णांक isci_task_I_T_nexus_reset(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा isci_host *ihost = dev_to_ihost(dev);
	काष्ठा isci_remote_device *idev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	idev = isci_get_device(dev->lldd_dev);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	अगर (!idev) अणु
		/* XXX: need to cleanup any ireqs targeting this
		 * करोमुख्य_device
		 */
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	ret = isci_reset_device(ihost, dev, idev);
 out:
	isci_put_device(idev);
	वापस ret;
पूर्ण
