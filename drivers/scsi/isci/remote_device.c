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
#समावेश <scsi/sas.h>
#समावेश <linux/bitops.h>
#समावेश "isci.h"
#समावेश "port.h"
#समावेश "remote_device.h"
#समावेश "request.h"
#समावेश "remote_node_context.h"
#समावेश "scu_event_codes.h"
#समावेश "task.h"

#अघोषित C
#घोषणा C(a) (#a)
स्थिर अक्षर *dev_state_name(क्रमागत sci_remote_device_states state)
अणु
	अटल स्थिर अक्षर * स्थिर strings[] = REMOTE_DEV_STATES;

	वापस strings[state];
पूर्ण
#अघोषित C

क्रमागत sci_status sci_remote_device_suspend(काष्ठा isci_remote_device *idev,
					  क्रमागत sci_remote_node_suspension_reasons reason)
अणु
	वापस sci_remote_node_context_suspend(&idev->rnc, reason,
					       SCI_SOFTWARE_SUSPEND_EXPECTED_EVENT);
पूर्ण

/**
 * isci_remote_device_पढ़ोy() - This function is called by the ihost when the
 *    remote device is पढ़ोy. We mark the isci device as पढ़ोy and संकेत the
 *    रुकोing proccess.
 * @ihost: our valid isci_host
 * @idev: remote device
 *
 */
अटल व्योम isci_remote_device_पढ़ोy(काष्ठा isci_host *ihost, काष्ठा isci_remote_device *idev)
अणु
	dev_dbg(&ihost->pdev->dev,
		"%s: idev = %p\n", __func__, idev);

	clear_bit(IDEV_IO_NCQERROR, &idev->flags);
	set_bit(IDEV_IO_READY, &idev->flags);
	अगर (test_and_clear_bit(IDEV_START_PENDING, &idev->flags))
		wake_up(&ihost->eventq);
पूर्ण

अटल क्रमागत sci_status sci_remote_device_terminate_req(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	पूर्णांक check_पात,
	काष्ठा isci_request *ireq)
अणु
	अगर (!test_bit(IREQ_ACTIVE, &ireq->flags) ||
	    (ireq->target_device != idev) ||
	    (check_पात && !test_bit(IREQ_PENDING_ABORT, &ireq->flags)))
		वापस SCI_SUCCESS;

	dev_dbg(&ihost->pdev->dev,
		"%s: idev=%p; flags=%lx; req=%p; req target=%p\n",
		__func__, idev, idev->flags, ireq, ireq->target_device);

	set_bit(IREQ_ABORT_PATH_ACTIVE, &ireq->flags);

	वापस sci_controller_terminate_request(ihost, idev, ireq);
पूर्ण

अटल क्रमागत sci_status sci_remote_device_terminate_reqs_checkपात(
	काष्ठा isci_remote_device *idev,
	पूर्णांक chk)
अणु
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;
	क्रमागत sci_status status  = SCI_SUCCESS;
	u32 i;

	क्रम (i = 0; i < SCI_MAX_IO_REQUESTS; i++) अणु
		काष्ठा isci_request *ireq = ihost->reqs[i];
		क्रमागत sci_status s;

		s = sci_remote_device_terminate_req(ihost, idev, chk, ireq);
		अगर (s != SCI_SUCCESS)
			status = s;
	पूर्ण
	वापस status;
पूर्ण

अटल bool isci_compare_suspendcount(
	काष्ठा isci_remote_device *idev,
	u32 localcount)
अणु
	smp_rmb();

	/* Check क्रम a change in the suspend count, or the RNC
	 * being destroyed.
	 */
	वापस (localcount != idev->rnc.suspend_count)
	    || sci_remote_node_context_is_being_destroyed(&idev->rnc);
पूर्ण

अटल bool isci_check_reqterm(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *ireq,
	u32 localcount)
अणु
	अचिन्हित दीर्घ flags;
	bool res;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	res = isci_compare_suspendcount(idev, localcount)
		&& !test_bit(IREQ_ABORT_PATH_ACTIVE, &ireq->flags);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	वापस res;
पूर्ण

अटल bool isci_check_devempty(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	u32 localcount)
अणु
	अचिन्हित दीर्घ flags;
	bool res;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	res = isci_compare_suspendcount(idev, localcount)
		&& idev->started_request_count == 0;
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	वापस res;
पूर्ण

क्रमागत sci_status isci_remote_device_terminate_requests(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *ireq)
अणु
	क्रमागत sci_status status = SCI_SUCCESS;
	अचिन्हित दीर्घ flags;
	u32 rnc_suspend_count;

	spin_lock_irqsave(&ihost->scic_lock, flags);

	अगर (isci_get_device(idev) == शून्य) अणु
		dev_dbg(&ihost->pdev->dev, "%s: failed isci_get_device(idev=%p)\n",
			__func__, idev);
		spin_unlock_irqrestore(&ihost->scic_lock, flags);
		status = SCI_FAILURE;
	पूर्ण अन्यथा अणु
		/* If alपढ़ोy suspended, करोn't रुको क्रम another suspension. */
		smp_rmb();
		rnc_suspend_count
			= sci_remote_node_context_is_suspended(&idev->rnc)
				? 0 : idev->rnc.suspend_count;

		dev_dbg(&ihost->pdev->dev,
			"%s: idev=%p, ireq=%p; started_request_count=%d, "
				"rnc_suspend_count=%d, rnc.suspend_count=%d"
				"about to wait\n",
			__func__, idev, ireq, idev->started_request_count,
			rnc_suspend_count, idev->rnc.suspend_count);

		#घोषणा MAX_SUSPEND_MSECS 10000
		अगर (ireq) अणु
			/* Terminate a specअगरic TC. */
			set_bit(IREQ_NO_AUTO_FREE_TAG, &ireq->flags);
			sci_remote_device_terminate_req(ihost, idev, 0, ireq);
			spin_unlock_irqrestore(&ihost->scic_lock, flags);
			अगर (!रुको_event_समयout(ihost->eventq,
						isci_check_reqterm(ihost, idev, ireq,
								   rnc_suspend_count),
						msecs_to_jअगरfies(MAX_SUSPEND_MSECS))) अणु

				dev_warn(&ihost->pdev->dev, "%s host%d timeout single\n",
					 __func__, ihost->id);
				dev_dbg(&ihost->pdev->dev,
					 "%s: ******* Timeout waiting for "
					 "suspend; idev=%p, current state %s; "
					 "started_request_count=%d, flags=%lx\n\t"
					 "rnc_suspend_count=%d, rnc.suspend_count=%d "
					 "RNC: current state %s, current "
					 "suspend_type %x dest state %d;\n"
					 "ireq=%p, ireq->flags = %lx\n",
					 __func__, idev,
					 dev_state_name(idev->sm.current_state_id),
					 idev->started_request_count, idev->flags,
					 rnc_suspend_count, idev->rnc.suspend_count,
					 rnc_state_name(idev->rnc.sm.current_state_id),
					 idev->rnc.suspend_type,
					 idev->rnc.destination_state,
					 ireq, ireq->flags);
			पूर्ण
			spin_lock_irqsave(&ihost->scic_lock, flags);
			clear_bit(IREQ_NO_AUTO_FREE_TAG, &ireq->flags);
			अगर (!test_bit(IREQ_ABORT_PATH_ACTIVE, &ireq->flags))
				isci_मुक्त_tag(ihost, ireq->io_tag);
			spin_unlock_irqrestore(&ihost->scic_lock, flags);
		पूर्ण अन्यथा अणु
			/* Terminate all TCs. */
			sci_remote_device_terminate_requests(idev);
			spin_unlock_irqrestore(&ihost->scic_lock, flags);
			अगर (!रुको_event_समयout(ihost->eventq,
						isci_check_devempty(ihost, idev,
								    rnc_suspend_count),
						msecs_to_jअगरfies(MAX_SUSPEND_MSECS))) अणु

				dev_warn(&ihost->pdev->dev, "%s host%d timeout all\n",
					 __func__, ihost->id);
				dev_dbg(&ihost->pdev->dev,
					"%s: ******* Timeout waiting for "
					"suspend; idev=%p, current state %s; "
					"started_request_count=%d, flags=%lx\n\t"
					"rnc_suspend_count=%d, "
					"RNC: current state %s, "
					"rnc.suspend_count=%d, current "
					"suspend_type %x dest state %d\n",
					__func__, idev,
					dev_state_name(idev->sm.current_state_id),
					idev->started_request_count, idev->flags,
					rnc_suspend_count,
					rnc_state_name(idev->rnc.sm.current_state_id),
					idev->rnc.suspend_count,
					idev->rnc.suspend_type,
					idev->rnc.destination_state);
			पूर्ण
		पूर्ण
		dev_dbg(&ihost->pdev->dev, "%s: idev=%p, wait done\n",
			__func__, idev);
		isci_put_device(idev);
	पूर्ण
	वापस status;
पूर्ण

/**
* isci_remote_device_not_पढ़ोy() - This function is called by the ihost when
*    the remote device is not पढ़ोy. We mark the isci device as पढ़ोy (not
*    "ready_for_io") and संकेत the रुकोing proccess.
* @ihost: This parameter specअगरies the isci host object.
* @idev: This parameter specअगरies the remote device
* @reason: Reason to चयन on
*
* sci_lock is held on entrance to this function.
*/
अटल व्योम isci_remote_device_not_पढ़ोy(काष्ठा isci_host *ihost,
					 काष्ठा isci_remote_device *idev,
					 u32 reason)
अणु
	dev_dbg(&ihost->pdev->dev,
		"%s: isci_device = %p; reason = %d\n", __func__, idev, reason);

	चयन (reason) अणु
	हाल SCIC_REMOTE_DEVICE_NOT_READY_SATA_SDB_ERROR_FIS_RECEIVED:
		set_bit(IDEV_IO_NCQERROR, &idev->flags);

		/* Suspend the remote device so the I/O can be terminated. */
		sci_remote_device_suspend(idev, SCI_SW_SUSPEND_NORMAL);

		/* Kill all outstanding requests क्रम the device. */
		sci_remote_device_terminate_requests(idev);

		fallthrough;	/* पूर्णांकo the शेष हाल */
	शेष:
		clear_bit(IDEV_IO_READY, &idev->flags);
		अवरोध;
	पूर्ण
पूर्ण

/* called once the remote node context is पढ़ोy to be मुक्तd.
 * The remote device can now report that its stop operation is complete. none
 */
अटल व्योम rnc_deकाष्ठा_करोne(व्योम *_dev)
अणु
	काष्ठा isci_remote_device *idev = _dev;

	BUG_ON(idev->started_request_count != 0);
	sci_change_state(&idev->sm, SCI_DEV_STOPPED);
पूर्ण

क्रमागत sci_status sci_remote_device_terminate_requests(
	काष्ठा isci_remote_device *idev)
अणु
	वापस sci_remote_device_terminate_reqs_checkपात(idev, 0);
पूर्ण

क्रमागत sci_status sci_remote_device_stop(काष्ठा isci_remote_device *idev,
					u32 समयout)
अणु
	काष्ठा sci_base_state_machine *sm = &idev->sm;
	क्रमागत sci_remote_device_states state = sm->current_state_id;

	चयन (state) अणु
	हाल SCI_DEV_INITIAL:
	हाल SCI_DEV_FAILED:
	हाल SCI_DEV_FINAL:
	शेष:
		dev_warn(scirdev_to_dev(idev), "%s: in wrong state: %s\n",
			 __func__, dev_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	हाल SCI_DEV_STOPPED:
		वापस SCI_SUCCESS;
	हाल SCI_DEV_STARTING:
		/* device not started so there had better be no requests */
		BUG_ON(idev->started_request_count != 0);
		sci_remote_node_context_deकाष्ठा(&idev->rnc,
						      rnc_deकाष्ठा_करोne, idev);
		/* Transition to the stopping state and रुको क्रम the
		 * remote node to complete being posted and invalidated.
		 */
		sci_change_state(sm, SCI_DEV_STOPPING);
		वापस SCI_SUCCESS;
	हाल SCI_DEV_READY:
	हाल SCI_STP_DEV_IDLE:
	हाल SCI_STP_DEV_CMD:
	हाल SCI_STP_DEV_NCQ:
	हाल SCI_STP_DEV_NCQ_ERROR:
	हाल SCI_STP_DEV_AWAIT_RESET:
	हाल SCI_SMP_DEV_IDLE:
	हाल SCI_SMP_DEV_CMD:
		sci_change_state(sm, SCI_DEV_STOPPING);
		अगर (idev->started_request_count == 0)
			sci_remote_node_context_deकाष्ठा(&idev->rnc,
							 rnc_deकाष्ठा_करोne,
							 idev);
		अन्यथा अणु
			sci_remote_device_suspend(
				idev, SCI_SW_SUSPEND_LINKHANG_DETECT);
			sci_remote_device_terminate_requests(idev);
		पूर्ण
		वापस SCI_SUCCESS;
	हाल SCI_DEV_STOPPING:
		/* All requests should have been terminated, but अगर there is an
		 * attempt to stop a device alपढ़ोy in the stopping state, then
		 * try again to terminate.
		 */
		वापस sci_remote_device_terminate_requests(idev);
	हाल SCI_DEV_RESETTING:
		sci_change_state(sm, SCI_DEV_STOPPING);
		वापस SCI_SUCCESS;
	पूर्ण
पूर्ण

क्रमागत sci_status sci_remote_device_reset(काष्ठा isci_remote_device *idev)
अणु
	काष्ठा sci_base_state_machine *sm = &idev->sm;
	क्रमागत sci_remote_device_states state = sm->current_state_id;

	चयन (state) अणु
	हाल SCI_DEV_INITIAL:
	हाल SCI_DEV_STOPPED:
	हाल SCI_DEV_STARTING:
	हाल SCI_SMP_DEV_IDLE:
	हाल SCI_SMP_DEV_CMD:
	हाल SCI_DEV_STOPPING:
	हाल SCI_DEV_FAILED:
	हाल SCI_DEV_RESETTING:
	हाल SCI_DEV_FINAL:
	शेष:
		dev_warn(scirdev_to_dev(idev), "%s: in wrong state: %s\n",
			 __func__, dev_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	हाल SCI_DEV_READY:
	हाल SCI_STP_DEV_IDLE:
	हाल SCI_STP_DEV_CMD:
	हाल SCI_STP_DEV_NCQ:
	हाल SCI_STP_DEV_NCQ_ERROR:
	हाल SCI_STP_DEV_AWAIT_RESET:
		sci_change_state(sm, SCI_DEV_RESETTING);
		वापस SCI_SUCCESS;
	पूर्ण
पूर्ण

क्रमागत sci_status sci_remote_device_reset_complete(काष्ठा isci_remote_device *idev)
अणु
	काष्ठा sci_base_state_machine *sm = &idev->sm;
	क्रमागत sci_remote_device_states state = sm->current_state_id;

	अगर (state != SCI_DEV_RESETTING) अणु
		dev_warn(scirdev_to_dev(idev), "%s: in wrong state: %s\n",
			 __func__, dev_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	sci_change_state(sm, SCI_DEV_READY);
	वापस SCI_SUCCESS;
पूर्ण

क्रमागत sci_status sci_remote_device_frame_handler(काष्ठा isci_remote_device *idev,
						     u32 frame_index)
अणु
	काष्ठा sci_base_state_machine *sm = &idev->sm;
	क्रमागत sci_remote_device_states state = sm->current_state_id;
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;
	क्रमागत sci_status status;

	चयन (state) अणु
	हाल SCI_DEV_INITIAL:
	हाल SCI_DEV_STOPPED:
	हाल SCI_DEV_STARTING:
	हाल SCI_STP_DEV_IDLE:
	हाल SCI_SMP_DEV_IDLE:
	हाल SCI_DEV_FINAL:
	शेष:
		dev_warn(scirdev_to_dev(idev), "%s: in wrong state: %s\n",
			 __func__, dev_state_name(state));
		/* Return the frame back to the controller */
		sci_controller_release_frame(ihost, frame_index);
		वापस SCI_FAILURE_INVALID_STATE;
	हाल SCI_DEV_READY:
	हाल SCI_STP_DEV_NCQ_ERROR:
	हाल SCI_STP_DEV_AWAIT_RESET:
	हाल SCI_DEV_STOPPING:
	हाल SCI_DEV_FAILED:
	हाल SCI_DEV_RESETTING: अणु
		काष्ठा isci_request *ireq;
		काष्ठा ssp_frame_hdr hdr;
		व्योम *frame_header;
		sमाप_प्रकार word_cnt;

		status = sci_unsolicited_frame_control_get_header(&ihost->uf_control,
								       frame_index,
								       &frame_header);
		अगर (status != SCI_SUCCESS)
			वापस status;

		word_cnt = माप(hdr) / माप(u32);
		sci_swab32_cpy(&hdr, frame_header, word_cnt);

		ireq = sci_request_by_tag(ihost, be16_to_cpu(hdr.tag));
		अगर (ireq && ireq->target_device == idev) अणु
			/* The IO request is now in अक्षरge of releasing the frame */
			status = sci_io_request_frame_handler(ireq, frame_index);
		पूर्ण अन्यथा अणु
			/* We could not map this tag to a valid IO
			 * request Just toss the frame and जारी
			 */
			sci_controller_release_frame(ihost, frame_index);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल SCI_STP_DEV_NCQ: अणु
		काष्ठा dev_to_host_fis *hdr;

		status = sci_unsolicited_frame_control_get_header(&ihost->uf_control,
								       frame_index,
								       (व्योम **)&hdr);
		अगर (status != SCI_SUCCESS)
			वापस status;

		अगर (hdr->fis_type == FIS_SETDEVBITS &&
		    (hdr->status & ATA_ERR)) अणु
			idev->not_पढ़ोy_reason = SCIC_REMOTE_DEVICE_NOT_READY_SATA_SDB_ERROR_FIS_RECEIVED;

			/* TODO Check sactive and complete associated IO अगर any. */
			sci_change_state(sm, SCI_STP_DEV_NCQ_ERROR);
		पूर्ण अन्यथा अगर (hdr->fis_type == FIS_REGD2H &&
			   (hdr->status & ATA_ERR)) अणु
			/*
			 * Some devices वापस D2H FIS when an NCQ error is detected.
			 * Treat this like an SDB error FIS पढ़ोy reason.
			 */
			idev->not_पढ़ोy_reason = SCIC_REMOTE_DEVICE_NOT_READY_SATA_SDB_ERROR_FIS_RECEIVED;
			sci_change_state(&idev->sm, SCI_STP_DEV_NCQ_ERROR);
		पूर्ण अन्यथा
			status = SCI_FAILURE;

		sci_controller_release_frame(ihost, frame_index);
		अवरोध;
	पूर्ण
	हाल SCI_STP_DEV_CMD:
	हाल SCI_SMP_DEV_CMD:
		/* The device करोes not process any UF received from the hardware जबतक
		 * in this state.  All unsolicited frames are क्रमwarded to the io request
		 * object.
		 */
		status = sci_io_request_frame_handler(idev->working_request, frame_index);
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

अटल bool is_remote_device_पढ़ोy(काष्ठा isci_remote_device *idev)
अणु

	काष्ठा sci_base_state_machine *sm = &idev->sm;
	क्रमागत sci_remote_device_states state = sm->current_state_id;

	चयन (state) अणु
	हाल SCI_DEV_READY:
	हाल SCI_STP_DEV_IDLE:
	हाल SCI_STP_DEV_CMD:
	हाल SCI_STP_DEV_NCQ:
	हाल SCI_STP_DEV_NCQ_ERROR:
	हाल SCI_STP_DEV_AWAIT_RESET:
	हाल SCI_SMP_DEV_IDLE:
	हाल SCI_SMP_DEV_CMD:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * called once the remote node context has transisitioned to a पढ़ोy
 * state (after suspending RX and/or TX due to early D2H fis)
 */
अटल व्योम atapi_remote_device_resume_करोne(व्योम *_dev)
अणु
	काष्ठा isci_remote_device *idev = _dev;
	काष्ठा isci_request *ireq = idev->working_request;

	sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
पूर्ण

क्रमागत sci_status sci_remote_device_event_handler(काष्ठा isci_remote_device *idev,
						     u32 event_code)
अणु
	क्रमागत sci_status status;
	काष्ठा sci_base_state_machine *sm = &idev->sm;
	क्रमागत sci_remote_device_states state = sm->current_state_id;

	चयन (scu_get_event_type(event_code)) अणु
	हाल SCU_EVENT_TYPE_RNC_OPS_MISC:
	हाल SCU_EVENT_TYPE_RNC_SUSPEND_TX:
	हाल SCU_EVENT_TYPE_RNC_SUSPEND_TX_RX:
		status = sci_remote_node_context_event_handler(&idev->rnc, event_code);
		अवरोध;
	हाल SCU_EVENT_TYPE_PTX_SCHEDULE_EVENT:
		अगर (scu_get_event_code(event_code) == SCU_EVENT_IT_NEXUS_TIMEOUT) अणु
			status = SCI_SUCCESS;

			/* Suspend the associated RNC */
			sci_remote_device_suspend(idev, SCI_SW_SUSPEND_NORMAL);

			dev_dbg(scirdev_to_dev(idev),
				"%s: device: %p event code: %x: %s\n",
				__func__, idev, event_code,
				is_remote_device_पढ़ोy(idev)
				? "I_T_Nexus_Timeout event"
				: "I_T_Nexus_Timeout event in wrong state");

			अवरोध;
		पूर्ण
		fallthrough;	/* and treat as unhandled */
	शेष:
		dev_dbg(scirdev_to_dev(idev),
			"%s: device: %p event code: %x: %s\n",
			__func__, idev, event_code,
			is_remote_device_पढ़ोy(idev)
			? "unexpected event"
			: "unexpected event in wrong state");
		status = SCI_FAILURE_INVALID_STATE;
		अवरोध;
	पूर्ण

	अगर (status != SCI_SUCCESS)
		वापस status;

	/* Decode device-specअगरic states that may require an RNC resume during
	 * normal operation.  When the पात path is active, these resumes are
	 * managed when the पात path निकासs.
	 */
	अगर (state == SCI_STP_DEV_ATAPI_ERROR) अणु
		/* For ATAPI error state resume the RNC right away. */
		अगर (scu_get_event_type(event_code) == SCU_EVENT_TYPE_RNC_SUSPEND_TX ||
		    scu_get_event_type(event_code) == SCU_EVENT_TYPE_RNC_SUSPEND_TX_RX) अणु
			वापस sci_remote_node_context_resume(&idev->rnc,
							      atapi_remote_device_resume_करोne,
							      idev);
		पूर्ण
	पूर्ण

	अगर (state == SCI_STP_DEV_IDLE) अणु

		/* We pick up suspension events to handle specअगरically to this
		 * state. We resume the RNC right away.
		 */
		अगर (scu_get_event_type(event_code) == SCU_EVENT_TYPE_RNC_SUSPEND_TX ||
		    scu_get_event_type(event_code) == SCU_EVENT_TYPE_RNC_SUSPEND_TX_RX)
			status = sci_remote_node_context_resume(&idev->rnc, शून्य, शून्य);
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम sci_remote_device_start_request(काष्ठा isci_remote_device *idev,
						 काष्ठा isci_request *ireq,
						 क्रमागत sci_status status)
अणु
	काष्ठा isci_port *iport = idev->owning_port;

	/* cleanup requests that failed after starting on the port */
	अगर (status != SCI_SUCCESS)
		sci_port_complete_io(iport, idev, ireq);
	अन्यथा अणु
		kref_get(&idev->kref);
		idev->started_request_count++;
	पूर्ण
पूर्ण

क्रमागत sci_status sci_remote_device_start_io(काष्ठा isci_host *ihost,
						काष्ठा isci_remote_device *idev,
						काष्ठा isci_request *ireq)
अणु
	काष्ठा sci_base_state_machine *sm = &idev->sm;
	क्रमागत sci_remote_device_states state = sm->current_state_id;
	काष्ठा isci_port *iport = idev->owning_port;
	क्रमागत sci_status status;

	चयन (state) अणु
	हाल SCI_DEV_INITIAL:
	हाल SCI_DEV_STOPPED:
	हाल SCI_DEV_STARTING:
	हाल SCI_STP_DEV_NCQ_ERROR:
	हाल SCI_DEV_STOPPING:
	हाल SCI_DEV_FAILED:
	हाल SCI_DEV_RESETTING:
	हाल SCI_DEV_FINAL:
	शेष:
		dev_warn(scirdev_to_dev(idev), "%s: in wrong state: %s\n",
			 __func__, dev_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	हाल SCI_DEV_READY:
		/* attempt to start an io request क्रम this device object. The remote
		 * device object will issue the start request क्रम the io and अगर
		 * successful it will start the request क्रम the port object then
		 * increment its own request count.
		 */
		status = sci_port_start_io(iport, idev, ireq);
		अगर (status != SCI_SUCCESS)
			वापस status;

		status = sci_remote_node_context_start_io(&idev->rnc, ireq);
		अगर (status != SCI_SUCCESS)
			अवरोध;

		status = sci_request_start(ireq);
		अवरोध;
	हाल SCI_STP_DEV_IDLE: अणु
		/* handle the start io operation क्रम a sata device that is in
		 * the command idle state. - Evalute the type of IO request to
		 * be started - If its an NCQ request change to NCQ substate -
		 * If its any other command change to the CMD substate
		 *
		 * If this is a softreset we may want to have a dअगरferent
		 * substate.
		 */
		क्रमागत sci_remote_device_states new_state;
		काष्ठा sas_task *task = isci_request_access_task(ireq);

		status = sci_port_start_io(iport, idev, ireq);
		अगर (status != SCI_SUCCESS)
			वापस status;

		status = sci_remote_node_context_start_io(&idev->rnc, ireq);
		अगर (status != SCI_SUCCESS)
			अवरोध;

		status = sci_request_start(ireq);
		अगर (status != SCI_SUCCESS)
			अवरोध;

		अगर (task->ata_task.use_ncq)
			new_state = SCI_STP_DEV_NCQ;
		अन्यथा अणु
			idev->working_request = ireq;
			new_state = SCI_STP_DEV_CMD;
		पूर्ण
		sci_change_state(sm, new_state);
		अवरोध;
	पूर्ण
	हाल SCI_STP_DEV_NCQ: अणु
		काष्ठा sas_task *task = isci_request_access_task(ireq);

		अगर (task->ata_task.use_ncq) अणु
			status = sci_port_start_io(iport, idev, ireq);
			अगर (status != SCI_SUCCESS)
				वापस status;

			status = sci_remote_node_context_start_io(&idev->rnc, ireq);
			अगर (status != SCI_SUCCESS)
				अवरोध;

			status = sci_request_start(ireq);
		पूर्ण अन्यथा
			वापस SCI_FAILURE_INVALID_STATE;
		अवरोध;
	पूर्ण
	हाल SCI_STP_DEV_AWAIT_RESET:
		वापस SCI_FAILURE_REMOTE_DEVICE_RESET_REQUIRED;
	हाल SCI_SMP_DEV_IDLE:
		status = sci_port_start_io(iport, idev, ireq);
		अगर (status != SCI_SUCCESS)
			वापस status;

		status = sci_remote_node_context_start_io(&idev->rnc, ireq);
		अगर (status != SCI_SUCCESS)
			अवरोध;

		status = sci_request_start(ireq);
		अगर (status != SCI_SUCCESS)
			अवरोध;

		idev->working_request = ireq;
		sci_change_state(&idev->sm, SCI_SMP_DEV_CMD);
		अवरोध;
	हाल SCI_STP_DEV_CMD:
	हाल SCI_SMP_DEV_CMD:
		/* device is alपढ़ोy handling a command it can not accept new commands
		 * until this one is complete.
		 */
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	sci_remote_device_start_request(idev, ireq, status);
	वापस status;
पूर्ण

अटल क्रमागत sci_status common_complete_io(काष्ठा isci_port *iport,
					  काष्ठा isci_remote_device *idev,
					  काष्ठा isci_request *ireq)
अणु
	क्रमागत sci_status status;

	status = sci_request_complete(ireq);
	अगर (status != SCI_SUCCESS)
		वापस status;

	status = sci_port_complete_io(iport, idev, ireq);
	अगर (status != SCI_SUCCESS)
		वापस status;

	sci_remote_device_decrement_request_count(idev);
	वापस status;
पूर्ण

क्रमागत sci_status sci_remote_device_complete_io(काष्ठा isci_host *ihost,
						   काष्ठा isci_remote_device *idev,
						   काष्ठा isci_request *ireq)
अणु
	काष्ठा sci_base_state_machine *sm = &idev->sm;
	क्रमागत sci_remote_device_states state = sm->current_state_id;
	काष्ठा isci_port *iport = idev->owning_port;
	क्रमागत sci_status status;

	चयन (state) अणु
	हाल SCI_DEV_INITIAL:
	हाल SCI_DEV_STOPPED:
	हाल SCI_DEV_STARTING:
	हाल SCI_STP_DEV_IDLE:
	हाल SCI_SMP_DEV_IDLE:
	हाल SCI_DEV_FAILED:
	हाल SCI_DEV_FINAL:
	शेष:
		dev_warn(scirdev_to_dev(idev), "%s: in wrong state: %s\n",
			 __func__, dev_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	हाल SCI_DEV_READY:
	हाल SCI_STP_DEV_AWAIT_RESET:
	हाल SCI_DEV_RESETTING:
		status = common_complete_io(iport, idev, ireq);
		अवरोध;
	हाल SCI_STP_DEV_CMD:
	हाल SCI_STP_DEV_NCQ:
	हाल SCI_STP_DEV_NCQ_ERROR:
	हाल SCI_STP_DEV_ATAPI_ERROR:
		status = common_complete_io(iport, idev, ireq);
		अगर (status != SCI_SUCCESS)
			अवरोध;

		अगर (ireq->sci_status == SCI_FAILURE_REMOTE_DEVICE_RESET_REQUIRED) अणु
			/* This request causes hardware error, device needs to be Lun Reset.
			 * So here we क्रमce the state machine to IDLE state so the rest IOs
			 * can reach RNC state handler, these IOs will be completed by RNC with
			 * status of "DEVICE_RESET_REQUIRED", instead of "INVALID STATE".
			 */
			sci_change_state(sm, SCI_STP_DEV_AWAIT_RESET);
		पूर्ण अन्यथा अगर (idev->started_request_count == 0)
			sci_change_state(sm, SCI_STP_DEV_IDLE);
		अवरोध;
	हाल SCI_SMP_DEV_CMD:
		status = common_complete_io(iport, idev, ireq);
		अगर (status != SCI_SUCCESS)
			अवरोध;
		sci_change_state(sm, SCI_SMP_DEV_IDLE);
		अवरोध;
	हाल SCI_DEV_STOPPING:
		status = common_complete_io(iport, idev, ireq);
		अगर (status != SCI_SUCCESS)
			अवरोध;

		अगर (idev->started_request_count == 0)
			sci_remote_node_context_deकाष्ठा(&idev->rnc,
							 rnc_deकाष्ठा_करोne,
							 idev);
		अवरोध;
	पूर्ण

	अगर (status != SCI_SUCCESS)
		dev_err(scirdev_to_dev(idev),
			"%s: Port:0x%p Device:0x%p Request:0x%p Status:0x%x "
			"could not complete\n", __func__, iport,
			idev, ireq, status);
	अन्यथा
		isci_put_device(idev);

	वापस status;
पूर्ण

अटल व्योम sci_remote_device_जारी_request(व्योम *dev)
अणु
	काष्ठा isci_remote_device *idev = dev;

	/* we need to check अगर this request is still valid to जारी. */
	अगर (idev->working_request)
		sci_controller_जारी_io(idev->working_request);
पूर्ण

क्रमागत sci_status sci_remote_device_start_task(काष्ठा isci_host *ihost,
						  काष्ठा isci_remote_device *idev,
						  काष्ठा isci_request *ireq)
अणु
	काष्ठा sci_base_state_machine *sm = &idev->sm;
	क्रमागत sci_remote_device_states state = sm->current_state_id;
	काष्ठा isci_port *iport = idev->owning_port;
	क्रमागत sci_status status;

	चयन (state) अणु
	हाल SCI_DEV_INITIAL:
	हाल SCI_DEV_STOPPED:
	हाल SCI_DEV_STARTING:
	हाल SCI_SMP_DEV_IDLE:
	हाल SCI_SMP_DEV_CMD:
	हाल SCI_DEV_STOPPING:
	हाल SCI_DEV_FAILED:
	हाल SCI_DEV_RESETTING:
	हाल SCI_DEV_FINAL:
	शेष:
		dev_warn(scirdev_to_dev(idev), "%s: in wrong state: %s\n",
			 __func__, dev_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	हाल SCI_STP_DEV_IDLE:
	हाल SCI_STP_DEV_CMD:
	हाल SCI_STP_DEV_NCQ:
	हाल SCI_STP_DEV_NCQ_ERROR:
	हाल SCI_STP_DEV_AWAIT_RESET:
		status = sci_port_start_io(iport, idev, ireq);
		अगर (status != SCI_SUCCESS)
			वापस status;

		status = sci_request_start(ireq);
		अगर (status != SCI_SUCCESS)
			जाओ out;

		/* Note: If the remote device state is not IDLE this will
		 * replace the request that probably resulted in the task
		 * management request.
		 */
		idev->working_request = ireq;
		sci_change_state(sm, SCI_STP_DEV_CMD);

		/* The remote node context must cleanup the TCi to NCQ mapping
		 * table.  The only way to करो this correctly is to either ग_लिखो
		 * to the TLCR रेजिस्टर or to invalidate and repost the RNC. In
		 * either हाल the remote node context state machine will take
		 * the correct action when the remote node context is suspended
		 * and later resumed.
		 */
		sci_remote_device_suspend(idev,
					  SCI_SW_SUSPEND_LINKHANG_DETECT);

		status = sci_remote_node_context_start_task(&idev->rnc, ireq,
				sci_remote_device_जारी_request, idev);

	out:
		sci_remote_device_start_request(idev, ireq, status);
		/* We need to let the controller start request handler know that
		 * it can't post TC yet. We will provide a callback function to
		 * post TC when RNC माला_लो resumed.
		 */
		वापस SCI_FAILURE_RESET_DEVICE_PARTIAL_SUCCESS;
	हाल SCI_DEV_READY:
		status = sci_port_start_io(iport, idev, ireq);
		अगर (status != SCI_SUCCESS)
			वापस status;

		/* Resume the RNC as needed: */
		status = sci_remote_node_context_start_task(&idev->rnc, ireq,
							    शून्य, शून्य);
		अगर (status != SCI_SUCCESS)
			अवरोध;

		status = sci_request_start(ireq);
		अवरोध;
	पूर्ण
	sci_remote_device_start_request(idev, ireq, status);

	वापस status;
पूर्ण

व्योम sci_remote_device_post_request(काष्ठा isci_remote_device *idev, u32 request)
अणु
	काष्ठा isci_port *iport = idev->owning_port;
	u32 context;

	context = request |
		  (ISCI_PEG << SCU_CONTEXT_COMMAND_PROTOCOL_ENGINE_GROUP_SHIFT) |
		  (iport->physical_port_index << SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT) |
		  idev->rnc.remote_node_index;

	sci_controller_post_request(iport->owning_controller, context);
पूर्ण

/* called once the remote node context has transisitioned to a
 * पढ़ोy state.  This is the indication that the remote device object can also
 * transition to पढ़ोy.
 */
अटल व्योम remote_device_resume_करोne(व्योम *_dev)
अणु
	काष्ठा isci_remote_device *idev = _dev;

	अगर (is_remote_device_पढ़ोy(idev))
		वापस;

	/* go 'ready' अगर we are not alपढ़ोy in a पढ़ोy state */
	sci_change_state(&idev->sm, SCI_DEV_READY);
पूर्ण

अटल व्योम sci_stp_remote_device_पढ़ोy_idle_substate_resume_complete_handler(व्योम *_dev)
अणु
	काष्ठा isci_remote_device *idev = _dev;
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;

	/* For NCQ operation we करो not issue a isci_remote_device_not_पढ़ोy().
	 * As a result, aव्योम sending the पढ़ोy notअगरication.
	 */
	अगर (idev->sm.previous_state_id != SCI_STP_DEV_NCQ)
		isci_remote_device_पढ़ोy(ihost, idev);
पूर्ण

अटल व्योम sci_remote_device_initial_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_remote_device *idev = container_of(sm, typeof(*idev), sm);

	/* Initial state is a transitional state to the stopped state */
	sci_change_state(&idev->sm, SCI_DEV_STOPPED);
पूर्ण

/**
 * sci_remote_device_deकाष्ठा() - मुक्त remote node context and deकाष्ठा
 * @idev: This parameter specअगरies the remote device to be deकाष्ठाed.
 *
 * Remote device objects are a limited resource.  As such, they must be
 * रक्षित.  Thus calls to स्थिरruct and deकाष्ठा are mutually exclusive and
 * non-reentrant. The वापस value shall indicate अगर the device was
 * successfully deकाष्ठाed or अगर some failure occurred. क्रमागत sci_status This value
 * is वापसed अगर the device is successfully deकाष्ठाed.
 * SCI_FAILURE_INVALID_REMOTE_DEVICE This value is वापसed अगर the supplied
 * device isn't valid (e.g. it's already been destoryed, the handle isn't
 * valid, etc.).
 */
अटल क्रमागत sci_status sci_remote_device_deकाष्ठा(काष्ठा isci_remote_device *idev)
अणु
	काष्ठा sci_base_state_machine *sm = &idev->sm;
	क्रमागत sci_remote_device_states state = sm->current_state_id;
	काष्ठा isci_host *ihost;

	अगर (state != SCI_DEV_STOPPED) अणु
		dev_warn(scirdev_to_dev(idev), "%s: in wrong state: %s\n",
			 __func__, dev_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	ihost = idev->owning_port->owning_controller;
	sci_controller_मुक्त_remote_node_context(ihost, idev,
						     idev->rnc.remote_node_index);
	idev->rnc.remote_node_index = SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX;
	sci_change_state(sm, SCI_DEV_FINAL);

	वापस SCI_SUCCESS;
पूर्ण

/**
 * isci_remote_device_deस्थिरruct() - This function मुक्तs an isci_remote_device.
 * @ihost: This parameter specअगरies the isci host object.
 * @idev: This parameter specअगरies the remote device to be मुक्तd.
 *
 */
अटल व्योम isci_remote_device_deस्थिरruct(काष्ठा isci_host *ihost, काष्ठा isci_remote_device *idev)
अणु
	dev_dbg(&ihost->pdev->dev,
		"%s: isci_device = %p\n", __func__, idev);

	/* There should not be any outstanding io's. All paths to
	 * here should go through isci_remote_device_nuke_requests.
	 * If we hit this condition, we will need a way to complete
	 * io requests in process */
	BUG_ON(idev->started_request_count > 0);

	sci_remote_device_deकाष्ठा(idev);
	list_del_init(&idev->node);
	isci_put_device(idev);
पूर्ण

अटल व्योम sci_remote_device_stopped_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_remote_device *idev = container_of(sm, typeof(*idev), sm);
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;
	u32 prev_state;

	/* If we are entering from the stopping state let the SCI User know that
	 * the stop operation has completed.
	 */
	prev_state = idev->sm.previous_state_id;
	अगर (prev_state == SCI_DEV_STOPPING)
		isci_remote_device_deस्थिरruct(ihost, idev);

	sci_controller_remote_device_stopped(ihost, idev);
पूर्ण

अटल व्योम sci_remote_device_starting_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_remote_device *idev = container_of(sm, typeof(*idev), sm);
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;

	isci_remote_device_not_पढ़ोy(ihost, idev,
				     SCIC_REMOTE_DEVICE_NOT_READY_START_REQUESTED);
पूर्ण

अटल व्योम sci_remote_device_पढ़ोy_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_remote_device *idev = container_of(sm, typeof(*idev), sm);
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;
	काष्ठा करोमुख्य_device *dev = idev->करोमुख्य_dev;

	अगर (dev->dev_type == SAS_SATA_DEV || (dev->tproto & SAS_PROTOCOL_SATA)) अणु
		sci_change_state(&idev->sm, SCI_STP_DEV_IDLE);
	पूर्ण अन्यथा अगर (dev_is_expander(dev->dev_type)) अणु
		sci_change_state(&idev->sm, SCI_SMP_DEV_IDLE);
	पूर्ण अन्यथा
		isci_remote_device_पढ़ोy(ihost, idev);
पूर्ण

अटल व्योम sci_remote_device_पढ़ोy_state_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_remote_device *idev = container_of(sm, typeof(*idev), sm);
	काष्ठा करोमुख्य_device *dev = idev->करोमुख्य_dev;

	अगर (dev->dev_type == SAS_END_DEVICE) अणु
		काष्ठा isci_host *ihost = idev->owning_port->owning_controller;

		isci_remote_device_not_पढ़ोy(ihost, idev,
					     SCIC_REMOTE_DEVICE_NOT_READY_STOP_REQUESTED);
	पूर्ण
पूर्ण

अटल व्योम sci_remote_device_resetting_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_remote_device *idev = container_of(sm, typeof(*idev), sm);
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;

	dev_dbg(&ihost->pdev->dev,
		"%s: isci_device = %p\n", __func__, idev);

	sci_remote_device_suspend(idev, SCI_SW_SUSPEND_LINKHANG_DETECT);
पूर्ण

अटल व्योम sci_remote_device_resetting_state_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_remote_device *idev = container_of(sm, typeof(*idev), sm);
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;

	dev_dbg(&ihost->pdev->dev,
		"%s: isci_device = %p\n", __func__, idev);

	sci_remote_node_context_resume(&idev->rnc, शून्य, शून्य);
पूर्ण

अटल व्योम sci_stp_remote_device_पढ़ोy_idle_substate_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_remote_device *idev = container_of(sm, typeof(*idev), sm);

	idev->working_request = शून्य;
	अगर (sci_remote_node_context_is_पढ़ोy(&idev->rnc)) अणु
		/*
		 * Since the RNC is पढ़ोy, it's alright to finish completion
		 * processing (e.g. संकेत the remote device is पढ़ोy). */
		sci_stp_remote_device_पढ़ोy_idle_substate_resume_complete_handler(idev);
	पूर्ण अन्यथा अणु
		sci_remote_node_context_resume(&idev->rnc,
			sci_stp_remote_device_पढ़ोy_idle_substate_resume_complete_handler,
			idev);
	पूर्ण
पूर्ण

अटल व्योम sci_stp_remote_device_पढ़ोy_cmd_substate_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_remote_device *idev = container_of(sm, typeof(*idev), sm);
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;

	BUG_ON(idev->working_request == शून्य);

	isci_remote_device_not_पढ़ोy(ihost, idev,
				     SCIC_REMOTE_DEVICE_NOT_READY_SATA_REQUEST_STARTED);
पूर्ण

अटल व्योम sci_stp_remote_device_पढ़ोy_ncq_error_substate_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_remote_device *idev = container_of(sm, typeof(*idev), sm);
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;

	अगर (idev->not_पढ़ोy_reason == SCIC_REMOTE_DEVICE_NOT_READY_SATA_SDB_ERROR_FIS_RECEIVED)
		isci_remote_device_not_पढ़ोy(ihost, idev,
					     idev->not_पढ़ोy_reason);
पूर्ण

अटल व्योम sci_smp_remote_device_पढ़ोy_idle_substate_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_remote_device *idev = container_of(sm, typeof(*idev), sm);
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;

	isci_remote_device_पढ़ोy(ihost, idev);
पूर्ण

अटल व्योम sci_smp_remote_device_पढ़ोy_cmd_substate_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_remote_device *idev = container_of(sm, typeof(*idev), sm);
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;

	BUG_ON(idev->working_request == शून्य);

	isci_remote_device_not_पढ़ोy(ihost, idev,
				     SCIC_REMOTE_DEVICE_NOT_READY_SMP_REQUEST_STARTED);
पूर्ण

अटल व्योम sci_smp_remote_device_पढ़ोy_cmd_substate_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_remote_device *idev = container_of(sm, typeof(*idev), sm);

	idev->working_request = शून्य;
पूर्ण

अटल स्थिर काष्ठा sci_base_state sci_remote_device_state_table[] = अणु
	[SCI_DEV_INITIAL] = अणु
		.enter_state = sci_remote_device_initial_state_enter,
	पूर्ण,
	[SCI_DEV_STOPPED] = अणु
		.enter_state = sci_remote_device_stopped_state_enter,
	पूर्ण,
	[SCI_DEV_STARTING] = अणु
		.enter_state = sci_remote_device_starting_state_enter,
	पूर्ण,
	[SCI_DEV_READY] = अणु
		.enter_state = sci_remote_device_पढ़ोy_state_enter,
		.निकास_state  = sci_remote_device_पढ़ोy_state_निकास
	पूर्ण,
	[SCI_STP_DEV_IDLE] = अणु
		.enter_state = sci_stp_remote_device_पढ़ोy_idle_substate_enter,
	पूर्ण,
	[SCI_STP_DEV_CMD] = अणु
		.enter_state = sci_stp_remote_device_पढ़ोy_cmd_substate_enter,
	पूर्ण,
	[SCI_STP_DEV_NCQ] = अणु पूर्ण,
	[SCI_STP_DEV_NCQ_ERROR] = अणु
		.enter_state = sci_stp_remote_device_पढ़ोy_ncq_error_substate_enter,
	पूर्ण,
	[SCI_STP_DEV_ATAPI_ERROR] = अणु पूर्ण,
	[SCI_STP_DEV_AWAIT_RESET] = अणु पूर्ण,
	[SCI_SMP_DEV_IDLE] = अणु
		.enter_state = sci_smp_remote_device_पढ़ोy_idle_substate_enter,
	पूर्ण,
	[SCI_SMP_DEV_CMD] = अणु
		.enter_state = sci_smp_remote_device_पढ़ोy_cmd_substate_enter,
		.निकास_state  = sci_smp_remote_device_पढ़ोy_cmd_substate_निकास,
	पूर्ण,
	[SCI_DEV_STOPPING] = अणु पूर्ण,
	[SCI_DEV_FAILED] = अणु पूर्ण,
	[SCI_DEV_RESETTING] = अणु
		.enter_state = sci_remote_device_resetting_state_enter,
		.निकास_state  = sci_remote_device_resetting_state_निकास
	पूर्ण,
	[SCI_DEV_FINAL] = अणु पूर्ण,
पूर्ण;

/**
 * sci_remote_device_स्थिरruct() - common स्थिरruction
 * @iport: SAS/SATA port through which this device is accessed.
 * @idev: remote device to स्थिरruct
 *
 * This routine just perक्रमms benign initialization and करोes not
 * allocate the remote_node_context which is left to
 * sci_remote_device_[de]a_स्थिरruct().  sci_remote_device_deकाष्ठा()
 * मुक्तs the remote_node_context(s) क्रम the device.
 */
अटल व्योम sci_remote_device_स्थिरruct(काष्ठा isci_port *iport,
				  काष्ठा isci_remote_device *idev)
अणु
	idev->owning_port = iport;
	idev->started_request_count = 0;

	sci_init_sm(&idev->sm, sci_remote_device_state_table, SCI_DEV_INITIAL);

	sci_remote_node_context_स्थिरruct(&idev->rnc,
					       SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX);
पूर्ण

/*
 * sci_remote_device_da_स्थिरruct() - स्थिरruct direct attached device.
 *
 * The inक्रमmation (e.g. IAF, Signature FIS, etc.) necessary to build
 * the device is known to the SCI Core since it is contained in the
 * sci_phy object.  Remote node context(s) is/are a global resource
 * allocated by this routine, मुक्तd by sci_remote_device_deकाष्ठा().
 *
 * Returns:
 * SCI_FAILURE_DEVICE_EXISTS - device has alपढ़ोy been स्थिरructed.
 * SCI_FAILURE_UNSUPPORTED_PROTOCOL - e.g. sas device attached to
 * sata-only controller instance.
 * SCI_FAILURE_INSUFFICIENT_RESOURCES - remote node contexts exhausted.
 */
अटल क्रमागत sci_status sci_remote_device_da_स्थिरruct(काष्ठा isci_port *iport,
						       काष्ठा isci_remote_device *idev)
अणु
	क्रमागत sci_status status;
	काष्ठा sci_port_properties properties;

	sci_remote_device_स्थिरruct(iport, idev);

	sci_port_get_properties(iport, &properties);
	/* Get accurate port width from port's phy mask क्रम a DA device. */
	idev->device_port_width = hweight32(properties.phy_mask);

	status = sci_controller_allocate_remote_node_context(iport->owning_controller,
							     idev,
							     &idev->rnc.remote_node_index);

	अगर (status != SCI_SUCCESS)
		वापस status;

	idev->connection_rate = sci_port_get_max_allowed_speed(iport);

	वापस SCI_SUCCESS;
पूर्ण

/*
 * sci_remote_device_ea_स्थिरruct() - स्थिरruct expander attached device
 *
 * Remote node context(s) is/are a global resource allocated by this
 * routine, मुक्तd by sci_remote_device_deकाष्ठा().
 *
 * Returns:
 * SCI_FAILURE_DEVICE_EXISTS - device has alपढ़ोy been स्थिरructed.
 * SCI_FAILURE_UNSUPPORTED_PROTOCOL - e.g. sas device attached to
 * sata-only controller instance.
 * SCI_FAILURE_INSUFFICIENT_RESOURCES - remote node contexts exhausted.
 */
अटल क्रमागत sci_status sci_remote_device_ea_स्थिरruct(काष्ठा isci_port *iport,
						       काष्ठा isci_remote_device *idev)
अणु
	काष्ठा करोमुख्य_device *dev = idev->करोमुख्य_dev;
	क्रमागत sci_status status;

	sci_remote_device_स्थिरruct(iport, idev);

	status = sci_controller_allocate_remote_node_context(iport->owning_controller,
								  idev,
								  &idev->rnc.remote_node_index);
	अगर (status != SCI_SUCCESS)
		वापस status;

	/* For SAS-2 the physical link rate is actually a logical link
	 * rate that incorporates multiplexing.  The SCU करोesn't
	 * incorporate multiplexing and क्रम the purposes of the
	 * connection the logical link rate is that same as the
	 * physical.  Furthermore, the SAS-2 and SAS-1.1 fields overlay
	 * one another, so this code works क्रम both situations.
	 */
	idev->connection_rate = min_t(u16, sci_port_get_max_allowed_speed(iport),
					 dev->linkrate);

	/* / @toकरो Should I assign the port width by पढ़ोing all of the phys on the port? */
	idev->device_port_width = 1;

	वापस SCI_SUCCESS;
पूर्ण

क्रमागत sci_status sci_remote_device_resume(
	काष्ठा isci_remote_device *idev,
	scics_sds_remote_node_context_callback cb_fn,
	व्योम *cb_p)
अणु
	क्रमागत sci_status status;

	status = sci_remote_node_context_resume(&idev->rnc, cb_fn, cb_p);
	अगर (status != SCI_SUCCESS)
		dev_dbg(scirdev_to_dev(idev), "%s: failed to resume: %d\n",
			__func__, status);
	वापस status;
पूर्ण

अटल व्योम isci_remote_device_resume_from_पात_complete(व्योम *cbparam)
अणु
	काष्ठा isci_remote_device *idev = cbparam;
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;
	scics_sds_remote_node_context_callback पात_resume_cb =
		idev->पात_resume_cb;

	dev_dbg(scirdev_to_dev(idev), "%s: passing-along resume: %p\n",
		__func__, पात_resume_cb);

	अगर (पात_resume_cb != शून्य) अणु
		idev->पात_resume_cb = शून्य;
		पात_resume_cb(idev->पात_resume_cbparam);
	पूर्ण
	clear_bit(IDEV_ABORT_PATH_RESUME_PENDING, &idev->flags);
	wake_up(&ihost->eventq);
पूर्ण

अटल bool isci_remote_device_test_resume_करोne(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev)
अणु
	अचिन्हित दीर्घ flags;
	bool करोne;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	करोne = !test_bit(IDEV_ABORT_PATH_RESUME_PENDING, &idev->flags)
		|| test_bit(IDEV_STOP_PENDING, &idev->flags)
		|| sci_remote_node_context_is_being_destroyed(&idev->rnc);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	वापस करोne;
पूर्ण

अटल व्योम isci_remote_device_रुको_क्रम_resume_from_पात(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev)
अणु
	dev_dbg(&ihost->pdev->dev, "%s: starting resume wait: %p\n",
		 __func__, idev);

	#घोषणा MAX_RESUME_MSECS 10000
	अगर (!रुको_event_समयout(ihost->eventq,
				isci_remote_device_test_resume_करोne(ihost, idev),
				msecs_to_jअगरfies(MAX_RESUME_MSECS))) अणु

		dev_warn(&ihost->pdev->dev, "%s: #### Timeout waiting for "
			 "resume: %p\n", __func__, idev);
	पूर्ण
	clear_bit(IDEV_ABORT_PATH_RESUME_PENDING, &idev->flags);

	dev_dbg(&ihost->pdev->dev, "%s: resume wait done: %p\n",
		 __func__, idev);
पूर्ण

क्रमागत sci_status isci_remote_device_resume_from_पात(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत sci_status status = SCI_SUCCESS;
	पूर्णांक destroyed;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	/* Preserve any current resume callbacks, क्रम instance from other
	 * resumptions.
	 */
	idev->पात_resume_cb = idev->rnc.user_callback;
	idev->पात_resume_cbparam = idev->rnc.user_cookie;
	set_bit(IDEV_ABORT_PATH_RESUME_PENDING, &idev->flags);
	clear_bit(IDEV_ABORT_PATH_ACTIVE, &idev->flags);
	destroyed = sci_remote_node_context_is_being_destroyed(&idev->rnc);
	अगर (!destroyed)
		status = sci_remote_device_resume(
			idev, isci_remote_device_resume_from_पात_complete,
			idev);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);
	अगर (!destroyed && (status == SCI_SUCCESS))
		isci_remote_device_रुको_क्रम_resume_from_पात(ihost, idev);
	अन्यथा
		clear_bit(IDEV_ABORT_PATH_RESUME_PENDING, &idev->flags);

	वापस status;
पूर्ण

/**
 * sci_remote_device_start() - This method will start the supplied remote
 *    device.  This method enables normal IO requests to flow through to the
 *    remote device.
 * @idev: This parameter specअगरies the device to be started.
 * @समयout: This parameter specअगरies the number of milliseconds in which the
 *    start operation should complete.
 *
 * An indication of whether the device was successfully started. SCI_SUCCESS
 * This value is वापसed अगर the device was successfully started.
 * SCI_FAILURE_INVALID_PHY This value is वापसed अगर the user attempts to start
 * the device when there have been no phys added to it.
 */
अटल क्रमागत sci_status sci_remote_device_start(काष्ठा isci_remote_device *idev,
					       u32 समयout)
अणु
	काष्ठा sci_base_state_machine *sm = &idev->sm;
	क्रमागत sci_remote_device_states state = sm->current_state_id;
	क्रमागत sci_status status;

	अगर (state != SCI_DEV_STOPPED) अणु
		dev_warn(scirdev_to_dev(idev), "%s: in wrong state: %s\n",
			 __func__, dev_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	status = sci_remote_device_resume(idev, remote_device_resume_करोne,
					  idev);
	अगर (status != SCI_SUCCESS)
		वापस status;

	sci_change_state(sm, SCI_DEV_STARTING);

	वापस SCI_SUCCESS;
पूर्ण

अटल क्रमागत sci_status isci_remote_device_स्थिरruct(काष्ठा isci_port *iport,
						    काष्ठा isci_remote_device *idev)
अणु
	काष्ठा isci_host *ihost = iport->isci_host;
	काष्ठा करोमुख्य_device *dev = idev->करोमुख्य_dev;
	क्रमागत sci_status status;

	अगर (dev->parent && dev_is_expander(dev->parent->dev_type))
		status = sci_remote_device_ea_स्थिरruct(iport, idev);
	अन्यथा
		status = sci_remote_device_da_स्थिरruct(iport, idev);

	अगर (status != SCI_SUCCESS) अणु
		dev_dbg(&ihost->pdev->dev, "%s: construct failed: %d\n",
			__func__, status);

		वापस status;
	पूर्ण

	/* start the device. */
	status = sci_remote_device_start(idev, ISCI_REMOTE_DEVICE_START_TIMEOUT);

	अगर (status != SCI_SUCCESS)
		dev_warn(&ihost->pdev->dev, "remote device start failed: %d\n",
			 status);

	वापस status;
पूर्ण

/**
 * isci_remote_device_alloc()
 * This function builds the isci_remote_device when a libsas dev_found message
 *    is received.
 * @ihost: This parameter specअगरies the isci host object.
 * @iport: This parameter specअगरies the isci_port connected to this device.
 *
 * poपूर्णांकer to new isci_remote_device.
 */
अटल काष्ठा isci_remote_device *
isci_remote_device_alloc(काष्ठा isci_host *ihost, काष्ठा isci_port *iport)
अणु
	काष्ठा isci_remote_device *idev;
	पूर्णांक i;

	क्रम (i = 0; i < SCI_MAX_REMOTE_DEVICES; i++) अणु
		idev = &ihost->devices[i];
		अगर (!test_and_set_bit(IDEV_ALLOCATED, &idev->flags))
			अवरोध;
	पूर्ण

	अगर (i >= SCI_MAX_REMOTE_DEVICES) अणु
		dev_warn(&ihost->pdev->dev, "%s: failed\n", __func__);
		वापस शून्य;
	पूर्ण
	अगर (WARN_ONCE(!list_empty(&idev->node), "found non-idle remote device\n"))
		वापस शून्य;

	वापस idev;
पूर्ण

व्योम isci_remote_device_release(काष्ठा kref *kref)
अणु
	काष्ठा isci_remote_device *idev = container_of(kref, typeof(*idev), kref);
	काष्ठा isci_host *ihost = idev->isci_port->isci_host;

	idev->करोमुख्य_dev = शून्य;
	idev->isci_port = शून्य;
	clear_bit(IDEV_START_PENDING, &idev->flags);
	clear_bit(IDEV_STOP_PENDING, &idev->flags);
	clear_bit(IDEV_IO_READY, &idev->flags);
	clear_bit(IDEV_GONE, &idev->flags);
	smp_mb__beक्रमe_atomic();
	clear_bit(IDEV_ALLOCATED, &idev->flags);
	wake_up(&ihost->eventq);
पूर्ण

/**
 * isci_remote_device_stop() - This function is called पूर्णांकernally to stop the
 *    remote device.
 * @ihost: This parameter specअगरies the isci host object.
 * @idev: This parameter specअगरies the remote device.
 *
 * The status of the ihost request to stop.
 */
क्रमागत sci_status isci_remote_device_stop(काष्ठा isci_host *ihost, काष्ठा isci_remote_device *idev)
अणु
	क्रमागत sci_status status;
	अचिन्हित दीर्घ flags;

	dev_dbg(&ihost->pdev->dev,
		"%s: isci_device = %p\n", __func__, idev);

	spin_lock_irqsave(&ihost->scic_lock, flags);
	idev->करोमुख्य_dev->lldd_dev = शून्य; /* disable new lookups */
	set_bit(IDEV_GONE, &idev->flags);

	set_bit(IDEV_STOP_PENDING, &idev->flags);
	status = sci_remote_device_stop(idev, 50);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	/* Wait क्रम the stop complete callback. */
	अगर (WARN_ONCE(status != SCI_SUCCESS, "failed to stop device\n"))
		/* nothing to रुको क्रम */;
	अन्यथा
		रुको_क्रम_device_stop(ihost, idev);

	dev_dbg(&ihost->pdev->dev,
		"%s: isci_device = %p, waiting done.\n", __func__, idev);

	वापस status;
पूर्ण

/**
 * isci_remote_device_gone() - This function is called by libsas when a करोमुख्य
 *    device is हटाओd.
 * @dev: This parameter specअगरies the libsas करोमुख्य device.
 */
व्योम isci_remote_device_gone(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा isci_host *ihost = dev_to_ihost(dev);
	काष्ठा isci_remote_device *idev = dev->lldd_dev;

	dev_dbg(&ihost->pdev->dev,
		"%s: domain_device = %p, isci_device = %p, isci_port = %p\n",
		__func__, dev, idev, idev->isci_port);

	isci_remote_device_stop(ihost, idev);
पूर्ण


/**
 * isci_remote_device_found() - This function is called by libsas when a remote
 *    device is discovered. A remote device object is created and started. the
 *    function then sleeps until the sci core device started message is
 *    received.
 * @dev: This parameter specअगरies the libsas करोमुख्य device.
 *
 * status, zero indicates success.
 */
पूर्णांक isci_remote_device_found(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा isci_host *isci_host = dev_to_ihost(dev);
	काष्ठा isci_port *isci_port = dev->port->lldd_port;
	काष्ठा isci_remote_device *isci_device;
	क्रमागत sci_status status;

	dev_dbg(&isci_host->pdev->dev,
		"%s: domain_device = %p\n", __func__, dev);

	अगर (!isci_port)
		वापस -ENODEV;

	isci_device = isci_remote_device_alloc(isci_host, isci_port);
	अगर (!isci_device)
		वापस -ENODEV;

	kref_init(&isci_device->kref);
	INIT_LIST_HEAD(&isci_device->node);

	spin_lock_irq(&isci_host->scic_lock);
	isci_device->करोमुख्य_dev = dev;
	isci_device->isci_port = isci_port;
	list_add_tail(&isci_device->node, &isci_port->remote_dev_list);

	set_bit(IDEV_START_PENDING, &isci_device->flags);
	status = isci_remote_device_स्थिरruct(isci_port, isci_device);

	dev_dbg(&isci_host->pdev->dev,
		"%s: isci_device = %p\n",
		__func__, isci_device);

	अगर (status == SCI_SUCCESS) अणु
		/* device came up, advertise it to the world */
		dev->lldd_dev = isci_device;
	पूर्ण अन्यथा
		isci_put_device(isci_device);
	spin_unlock_irq(&isci_host->scic_lock);

	/* रुको क्रम the device पढ़ोy callback. */
	रुको_क्रम_device_start(isci_host, isci_device);

	वापस status == SCI_SUCCESS ? 0 : -ENODEV;
पूर्ण

क्रमागत sci_status isci_remote_device_suspend_terminate(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *ireq)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत sci_status status;

	/* Put the device पूर्णांकo suspension. */
	spin_lock_irqsave(&ihost->scic_lock, flags);
	set_bit(IDEV_ABORT_PATH_ACTIVE, &idev->flags);
	sci_remote_device_suspend(idev, SCI_SW_SUSPEND_LINKHANG_DETECT);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	/* Terminate and रुको क्रम the completions. */
	status = isci_remote_device_terminate_requests(ihost, idev, ireq);
	अगर (status != SCI_SUCCESS)
		dev_dbg(&ihost->pdev->dev,
			"%s: isci_remote_device_terminate_requests(%p) "
				"returned %d!\n",
			__func__, idev, status);

	/* NOTE: RNC resumption is left to the caller! */
	वापस status;
पूर्ण

पूर्णांक isci_remote_device_is_safe_to_पात(
	काष्ठा isci_remote_device *idev)
अणु
	वापस sci_remote_node_context_is_safe_to_पात(&idev->rnc);
पूर्ण

क्रमागत sci_status sci_remote_device_पात_requests_pending_पात(
	काष्ठा isci_remote_device *idev)
अणु
	वापस sci_remote_device_terminate_reqs_checkपात(idev, 1);
पूर्ण

क्रमागत sci_status isci_remote_device_reset_complete(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत sci_status status;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	status = sci_remote_device_reset_complete(idev);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	वापस status;
पूर्ण

व्योम isci_dev_set_hang_detection_समयout(
	काष्ठा isci_remote_device *idev,
	u32 समयout)
अणु
	अगर (dev_is_sata(idev->करोमुख्य_dev)) अणु
		अगर (समयout) अणु
			अगर (test_and_set_bit(IDEV_RNC_LLHANG_ENABLED,
					     &idev->flags))
				वापस;  /* Alपढ़ोy enabled. */
		पूर्ण अन्यथा अगर (!test_and_clear_bit(IDEV_RNC_LLHANG_ENABLED,
					       &idev->flags))
			वापस;  /* Not enabled. */

		sci_port_set_hang_detection_समयout(idev->owning_port,
						    समयout);
	पूर्ण
पूर्ण
