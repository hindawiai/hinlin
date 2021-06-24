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

#अगर_अघोषित _ISCI_REMOTE_DEVICE_H_
#घोषणा _ISCI_REMOTE_DEVICE_H_
#समावेश <scsi/libsas.h>
#समावेश <linux/kref.h>
#समावेश "scu_remote_node_context.h"
#समावेश "remote_node_context.h"
#समावेश "port.h"

क्रमागत sci_remote_device_not_पढ़ोy_reason_code अणु
	SCIC_REMOTE_DEVICE_NOT_READY_START_REQUESTED,
	SCIC_REMOTE_DEVICE_NOT_READY_STOP_REQUESTED,
	SCIC_REMOTE_DEVICE_NOT_READY_SATA_REQUEST_STARTED,
	SCIC_REMOTE_DEVICE_NOT_READY_SATA_SDB_ERROR_FIS_RECEIVED,
	SCIC_REMOTE_DEVICE_NOT_READY_SMP_REQUEST_STARTED,
	SCIC_REMOTE_DEVICE_NOT_READY_REASON_CODE_MAX
पूर्ण;

/**
 * isci_remote_device - isci representation of a sas expander / end poपूर्णांक
 * @device_port_width: hw setting क्रम number of simultaneous connections
 * @connection_rate: per-taskcontext connection rate क्रम this device
 * @working_request: SATA requests have no tag we क्रम unaccelerated
 *                   protocols we need a method to associate unsolicited
 *                   frames with a pending request
 */
काष्ठा isci_remote_device अणु
	#घोषणा IDEV_START_PENDING 0
	#घोषणा IDEV_STOP_PENDING 1
	#घोषणा IDEV_ALLOCATED 2
	#घोषणा IDEV_GONE 3
	#घोषणा IDEV_IO_READY 4
	#घोषणा IDEV_IO_NCQERROR 5
	#घोषणा IDEV_RNC_LLHANG_ENABLED 6
	#घोषणा IDEV_ABORT_PATH_ACTIVE 7
	#घोषणा IDEV_ABORT_PATH_RESUME_PENDING 8
	अचिन्हित दीर्घ flags;
	काष्ठा kref kref;
	काष्ठा isci_port *isci_port;
	काष्ठा करोमुख्य_device *करोमुख्य_dev;
	काष्ठा list_head node;
	काष्ठा sci_base_state_machine sm;
	u32 device_port_width;
	क्रमागत sas_linkrate connection_rate;
	काष्ठा isci_port *owning_port;
	काष्ठा sci_remote_node_context rnc;
	/* XXX unअगरy with device reference counting and delete */
	u32 started_request_count;
	काष्ठा isci_request *working_request;
	u32 not_पढ़ोy_reason;
	scics_sds_remote_node_context_callback पात_resume_cb;
	व्योम *पात_resume_cbparam;
पूर्ण;

#घोषणा ISCI_REMOTE_DEVICE_START_TIMEOUT 5000

/* device reference routines must be called under sci_lock */
अटल अंतरभूत काष्ठा isci_remote_device *isci_get_device(
	काष्ठा isci_remote_device *idev)
अणु
	अगर (idev)
		kref_get(&idev->kref);
	वापस idev;
पूर्ण

अटल अंतरभूत काष्ठा isci_remote_device *isci_lookup_device(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा isci_remote_device *idev = dev->lldd_dev;

	अगर (idev && !test_bit(IDEV_GONE, &idev->flags)) अणु
		kref_get(&idev->kref);
		वापस idev;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम isci_remote_device_release(काष्ठा kref *kref);
अटल अंतरभूत व्योम isci_put_device(काष्ठा isci_remote_device *idev)
अणु
	अगर (idev)
		kref_put(&idev->kref, isci_remote_device_release);
पूर्ण

क्रमागत sci_status isci_remote_device_stop(काष्ठा isci_host *ihost,
					काष्ठा isci_remote_device *idev);
व्योम isci_remote_device_nuke_requests(काष्ठा isci_host *ihost,
				      काष्ठा isci_remote_device *idev);
व्योम isci_remote_device_gone(काष्ठा करोमुख्य_device *करोमुख्य_dev);
पूर्णांक isci_remote_device_found(काष्ठा करोमुख्य_device *करोमुख्य_dev);

/**
 * sci_remote_device_stop() - This method will stop both transmission and
 *    reception of link activity क्रम the supplied remote device.  This method
 *    disables normal IO requests from flowing through to the remote device.
 * @remote_device: This parameter specअगरies the device to be stopped.
 * @समयout: This parameter specअगरies the number of milliseconds in which the
 *    stop operation should complete.
 *
 * An indication of whether the device was successfully stopped. SCI_SUCCESS
 * This value is वापसed अगर the transmission and reception क्रम the device was
 * successfully stopped.
 */
क्रमागत sci_status sci_remote_device_stop(
	काष्ठा isci_remote_device *idev,
	u32 समयout);

/**
 * sci_remote_device_reset() - This method will reset the device making it
 *    पढ़ोy क्रम operation. This method must be called anyसमय the device is
 *    reset either through a SMP phy control or a port hard reset request.
 * @remote_device: This parameter specअगरies the device to be reset.
 *
 * This method करोes not actually cause the device hardware to be reset. This
 * method resets the software object so that it will be operational after a
 * device hardware reset completes. An indication of whether the device reset
 * was accepted. SCI_SUCCESS This value is वापसed अगर the device reset is
 * started.
 */
क्रमागत sci_status sci_remote_device_reset(
	काष्ठा isci_remote_device *idev);

/**
 * sci_remote_device_reset_complete() - This method inक्रमms the device object
 *    that the reset operation is complete and the device can resume operation
 *    again.
 * @remote_device: This parameter specअगरies the device which is to be inक्रमmed
 *    of the reset complete operation.
 *
 * An indication that the device is resuming operation. SCI_SUCCESS the device
 * is resuming operation.
 */
क्रमागत sci_status sci_remote_device_reset_complete(
	काष्ठा isci_remote_device *idev);

/**
 * क्रमागत sci_remote_device_states - This क्रमागतeration depicts all the states
 *    क्रम the common remote device state machine.
 * @SCI_DEV_INITIAL: Simply the initial state क्रम the base remote device
 * state machine.
 *
 * @SCI_DEV_STOPPED: This state indicates that the remote device has
 * successfully been stopped.  In this state no new IO operations are
 * permitted.  This state is entered from the INITIAL state.  This state
 * is entered from the STOPPING state.
 *
 * @SCI_DEV_STARTING: This state indicates the the remote device is in
 * the process of becoming पढ़ोy (i.e. starting).  In this state no new
 * IO operations are permitted.  This state is entered from the STOPPED
 * state.
 *
 * @SCI_DEV_READY: This state indicates the remote device is now पढ़ोy.
 * Thus, the user is able to perक्रमm IO operations on the remote device.
 * This state is entered from the STARTING state.
 *
 * @SCI_STP_DEV_IDLE: This is the idle substate क्रम the stp remote
 * device.  When there are no active IO क्रम the device it is is in this
 * state.
 *
 * @SCI_STP_DEV_CMD: This is the command state क्रम क्रम the STP remote
 * device.  This state is entered when the device is processing a
 * non-NCQ command.  The device object will fail any new start IO
 * requests until this command is complete.
 *
 * @SCI_STP_DEV_NCQ: This is the NCQ state क्रम the STP remote device.
 * This state is entered when the device is processing an NCQ reuqest.
 * It will reमुख्य in this state so दीर्घ as there is one or more NCQ
 * requests being processed.
 *
 * @SCI_STP_DEV_NCQ_ERROR: This is the NCQ error state क्रम the STP
 * remote device.  This state is entered when an SDB error FIS is
 * received by the device object जबतक in the NCQ state.  The device
 * object will only accept a READ LOG command जबतक in this state.
 *
 * @SCI_STP_DEV_ATAPI_ERROR: This is the ATAPI error state क्रम the STP
 * ATAPI remote device.  This state is entered when ATAPI device sends
 * error status FIS without data जबतक the device object is in CMD
 * state.  A suspension event is expected in this state.  The device
 * object will resume right away.
 *
 * @SCI_STP_DEV_AWAIT_RESET: This is the READY substate indicates the
 * device is रुकोing क्रम the RESET task coming to be recovered from
 * certain hardware specअगरic error.
 *
 * @SCI_SMP_DEV_IDLE: This is the पढ़ोy operational substate क्रम the
 * remote device.  This is the normal operational state क्रम a remote
 * device.
 *
 * @SCI_SMP_DEV_CMD: This is the suspended state क्रम the remote device.
 * This is the state that the device is placed in when a RNC suspend is
 * received by the SCU hardware.
 *
 * @SCI_DEV_STOPPING: This state indicates that the remote device is in
 * the process of stopping.  In this state no new IO operations are
 * permitted, but existing IO operations are allowed to complete.  This
 * state is entered from the READY state.  This state is entered from
 * the FAILED state.
 *
 * @SCI_DEV_FAILED: This state indicates that the remote device has
 * failed.  In this state no new IO operations are permitted.  This
 * state is entered from the INITIALIZING state.  This state is entered
 * from the READY state.
 *
 * @SCI_DEV_RESETTING: This state indicates the device is being reset.
 * In this state no new IO operations are permitted.  This state is
 * entered from the READY state.
 *
 * @SCI_DEV_FINAL: Simply the final state क्रम the base remote device
 * state machine.
 */
#घोषणा REMOTE_DEV_STATES अणु\
	C(DEV_INITIAL),\
	C(DEV_STOPPED),\
	C(DEV_STARTING),\
	C(DEV_READY),\
	C(STP_DEV_IDLE),\
	C(STP_DEV_CMD),\
	C(STP_DEV_NCQ),\
	C(STP_DEV_NCQ_ERROR),\
	C(STP_DEV_ATAPI_ERROR),\
	C(STP_DEV_AWAIT_RESET),\
	C(SMP_DEV_IDLE),\
	C(SMP_DEV_CMD),\
	C(DEV_STOPPING),\
	C(DEV_FAILED),\
	C(DEV_RESETTING),\
	C(DEV_FINAL),\
	पूर्ण
#अघोषित C
#घोषणा C(a) SCI_##a
क्रमागत sci_remote_device_states REMOTE_DEV_STATES;
#अघोषित C
स्थिर अक्षर *dev_state_name(क्रमागत sci_remote_device_states state);

अटल अंतरभूत काष्ठा isci_remote_device *rnc_to_dev(काष्ठा sci_remote_node_context *rnc)
अणु
	काष्ठा isci_remote_device *idev;

	idev = container_of(rnc, typeof(*idev), rnc);

	वापस idev;
पूर्ण

अटल अंतरभूत व्योम sci_remote_device_decrement_request_count(काष्ठा isci_remote_device *idev)
अणु
	/* XXX delete this vooकरोo when converting to the top-level device
	 * reference count
	 */
	अगर (WARN_ONCE(idev->started_request_count == 0,
		      "%s: tried to decrement started_request_count past 0!?",
			__func__))
		/* pass */;
	अन्यथा
		idev->started_request_count--;
पूर्ण

व्योम isci_dev_set_hang_detection_समयout(काष्ठा isci_remote_device *idev, u32 समयout);

क्रमागत sci_status sci_remote_device_frame_handler(
	काष्ठा isci_remote_device *idev,
	u32 frame_index);

क्रमागत sci_status sci_remote_device_event_handler(
	काष्ठा isci_remote_device *idev,
	u32 event_code);

क्रमागत sci_status sci_remote_device_start_io(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *ireq);

क्रमागत sci_status sci_remote_device_start_task(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *ireq);

क्रमागत sci_status sci_remote_device_complete_io(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *ireq);

व्योम sci_remote_device_post_request(
	काष्ठा isci_remote_device *idev,
	u32 request);

क्रमागत sci_status sci_remote_device_terminate_requests(
	काष्ठा isci_remote_device *idev);

पूर्णांक isci_remote_device_is_safe_to_पात(
	काष्ठा isci_remote_device *idev);

क्रमागत sci_status
sci_remote_device_पात_requests_pending_पात(
	काष्ठा isci_remote_device *idev);

क्रमागत sci_status isci_remote_device_suspend(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev);

क्रमागत sci_status sci_remote_device_resume(
	काष्ठा isci_remote_device *idev,
	scics_sds_remote_node_context_callback cb_fn,
	व्योम *cb_p);

क्रमागत sci_status isci_remote_device_resume_from_पात(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev);

क्रमागत sci_status isci_remote_device_reset(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev);

क्रमागत sci_status isci_remote_device_reset_complete(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev);

क्रमागत sci_status isci_remote_device_suspend_terminate(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *ireq);

क्रमागत sci_status isci_remote_device_terminate_requests(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *ireq);
क्रमागत sci_status sci_remote_device_suspend(काष्ठा isci_remote_device *idev,
					  क्रमागत sci_remote_node_suspension_reasons reason);
#पूर्ण_अगर /* !defined(_ISCI_REMOTE_DEVICE_H_) */
