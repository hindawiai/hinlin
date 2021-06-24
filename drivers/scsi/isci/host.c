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
#समावेश <linux/circ_buf.h>
#समावेश <linux/device.h>
#समावेश <scsi/sas.h>
#समावेश "host.h"
#समावेश "isci.h"
#समावेश "port.h"
#समावेश "probe_roms.h"
#समावेश "remote_device.h"
#समावेश "request.h"
#समावेश "scu_completion_codes.h"
#समावेश "scu_event_codes.h"
#समावेश "registers.h"
#समावेश "scu_remote_node_context.h"
#समावेश "scu_task_context.h"

#घोषणा SCU_CONTEXT_RAM_INIT_STALL_TIME      200

#घोषणा smu_max_ports(dcc_value) \
	(\
		(((dcc_value) & SMU_DEVICE_CONTEXT_CAPACITY_MAX_LP_MASK) \
		 >> SMU_DEVICE_CONTEXT_CAPACITY_MAX_LP_SHIFT) + 1 \
	)

#घोषणा smu_max_task_contexts(dcc_value)	\
	(\
		(((dcc_value) & SMU_DEVICE_CONTEXT_CAPACITY_MAX_TC_MASK) \
		 >> SMU_DEVICE_CONTEXT_CAPACITY_MAX_TC_SHIFT) + 1 \
	)

#घोषणा smu_max_rncs(dcc_value) \
	(\
		(((dcc_value) & SMU_DEVICE_CONTEXT_CAPACITY_MAX_RNC_MASK) \
		 >> SMU_DEVICE_CONTEXT_CAPACITY_MAX_RNC_SHIFT) + 1 \
	)

#घोषणा SCIC_SDS_CONTROLLER_PHY_START_TIMEOUT      100

/*
 * The number of milliseconds to रुको जबतक a given phy is consuming घातer
 * beक्रमe allowing another set of phys to consume घातer. Ultimately, this will
 * be specअगरied by OEM parameter.
 */
#घोषणा SCIC_SDS_CONTROLLER_POWER_CONTROL_INTERVAL 500

/*
 * NORMALIZE_PUT_POINTER() -
 *
 * This macro will normalize the completion queue put poपूर्णांकer so its value can
 * be used as an array inde
 */
#घोषणा NORMALIZE_PUT_POINTER(x) \
	((x) & SMU_COMPLETION_QUEUE_PUT_POINTER_MASK)


/*
 * NORMALIZE_EVENT_POINTER() -
 *
 * This macro will normalize the completion queue event entry so its value can
 * be used as an index.
 */
#घोषणा NORMALIZE_EVENT_POINTER(x) \
	(\
		((x) & SMU_COMPLETION_QUEUE_GET_EVENT_POINTER_MASK) \
		>> SMU_COMPLETION_QUEUE_GET_EVENT_POINTER_SHIFT	\
	)

/*
 * NORMALIZE_GET_POINTER() -
 *
 * This macro will normalize the completion queue get poपूर्णांकer so its value can
 * be used as an index पूर्णांकo an array
 */
#घोषणा NORMALIZE_GET_POINTER(x) \
	((x) & SMU_COMPLETION_QUEUE_GET_POINTER_MASK)

/*
 * NORMALIZE_GET_POINTER_CYCLE_BIT() -
 *
 * This macro will normalize the completion queue cycle poपूर्णांकer so it matches
 * the completion queue cycle bit
 */
#घोषणा NORMALIZE_GET_POINTER_CYCLE_BIT(x) \
	((SMU_CQGR_CYCLE_BIT & (x)) << (31 - SMU_COMPLETION_QUEUE_GET_CYCLE_BIT_SHIFT))

/*
 * COMPLETION_QUEUE_CYCLE_BIT() -
 *
 * This macro will वापस the cycle bit of the completion queue entry
 */
#घोषणा COMPLETION_QUEUE_CYCLE_BIT(x) ((x) & 0x80000000)

/* Init the state machine and call the state entry function (अगर any) */
व्योम sci_init_sm(काष्ठा sci_base_state_machine *sm,
		 स्थिर काष्ठा sci_base_state *state_table, u32 initial_state)
अणु
	sci_state_transition_t handler;

	sm->initial_state_id    = initial_state;
	sm->previous_state_id   = initial_state;
	sm->current_state_id    = initial_state;
	sm->state_table         = state_table;

	handler = sm->state_table[initial_state].enter_state;
	अगर (handler)
		handler(sm);
पूर्ण

/* Call the state निकास fn, update the current state, call the state entry fn */
व्योम sci_change_state(काष्ठा sci_base_state_machine *sm, u32 next_state)
अणु
	sci_state_transition_t handler;

	handler = sm->state_table[sm->current_state_id].निकास_state;
	अगर (handler)
		handler(sm);

	sm->previous_state_id = sm->current_state_id;
	sm->current_state_id = next_state;

	handler = sm->state_table[sm->current_state_id].enter_state;
	अगर (handler)
		handler(sm);
पूर्ण

अटल bool sci_controller_completion_queue_has_entries(काष्ठा isci_host *ihost)
अणु
	u32 get_value = ihost->completion_queue_get;
	u32 get_index = get_value & SMU_COMPLETION_QUEUE_GET_POINTER_MASK;

	अगर (NORMALIZE_GET_POINTER_CYCLE_BIT(get_value) ==
	    COMPLETION_QUEUE_CYCLE_BIT(ihost->completion_queue[get_index]))
		वापस true;

	वापस false;
पूर्ण

अटल bool sci_controller_isr(काष्ठा isci_host *ihost)
अणु
	अगर (sci_controller_completion_queue_has_entries(ihost))
		वापस true;

	/* we have a spurious पूर्णांकerrupt it could be that we have alपढ़ोy
	 * emptied the completion queue from a previous पूर्णांकerrupt
	 * FIXME: really!?
	 */
	ग_लिखोl(SMU_ISR_COMPLETION, &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_status);

	/* There is a race in the hardware that could cause us not to be
	 * notअगरied of an पूर्णांकerrupt completion अगर we करो not take this
	 * step.  We will mask then unmask the पूर्णांकerrupts so अगर there is
	 * another पूर्णांकerrupt pending the clearing of the पूर्णांकerrupt
	 * source we get the next पूर्णांकerrupt message.
	 */
	spin_lock(&ihost->scic_lock);
	अगर (test_bit(IHOST_IRQ_ENABLED, &ihost->flags)) अणु
		ग_लिखोl(0xFF000000, &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_mask);
		ग_लिखोl(0, &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_mask);
	पूर्ण
	spin_unlock(&ihost->scic_lock);

	वापस false;
पूर्ण

irqवापस_t isci_msix_isr(पूर्णांक vec, व्योम *data)
अणु
	काष्ठा isci_host *ihost = data;

	अगर (sci_controller_isr(ihost))
		tasklet_schedule(&ihost->completion_tasklet);

	वापस IRQ_HANDLED;
पूर्ण

अटल bool sci_controller_error_isr(काष्ठा isci_host *ihost)
अणु
	u32 पूर्णांकerrupt_status;

	पूर्णांकerrupt_status =
		पढ़ोl(&ihost->smu_रेजिस्टरs->पूर्णांकerrupt_status);
	पूर्णांकerrupt_status &= (SMU_ISR_QUEUE_ERROR | SMU_ISR_QUEUE_SUSPEND);

	अगर (पूर्णांकerrupt_status != 0) अणु
		/*
		 * There is an error पूर्णांकerrupt pending so let it through and handle
		 * in the callback */
		वापस true;
	पूर्ण

	/*
	 * There is a race in the hardware that could cause us not to be notअगरied
	 * of an पूर्णांकerrupt completion अगर we करो not take this step.  We will mask
	 * then unmask the error पूर्णांकerrupts so अगर there was another पूर्णांकerrupt
	 * pending we will be notअगरied.
	 * Could we ग_लिखो the value of (SMU_ISR_QUEUE_ERROR | SMU_ISR_QUEUE_SUSPEND)? */
	ग_लिखोl(0xff, &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_mask);
	ग_लिखोl(0, &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_mask);

	वापस false;
पूर्ण

अटल व्योम sci_controller_task_completion(काष्ठा isci_host *ihost, u32 ent)
अणु
	u32 index = SCU_GET_COMPLETION_INDEX(ent);
	काष्ठा isci_request *ireq = ihost->reqs[index];

	/* Make sure that we really want to process this IO request */
	अगर (test_bit(IREQ_ACTIVE, &ireq->flags) &&
	    ireq->io_tag != SCI_CONTROLLER_INVALID_IO_TAG &&
	    ISCI_TAG_SEQ(ireq->io_tag) == ihost->io_request_sequence[index])
		/* Yep this is a valid io request pass it aदीर्घ to the
		 * io request handler
		 */
		sci_io_request_tc_completion(ireq, ent);
पूर्ण

अटल व्योम sci_controller_sdma_completion(काष्ठा isci_host *ihost, u32 ent)
अणु
	u32 index;
	काष्ठा isci_request *ireq;
	काष्ठा isci_remote_device *idev;

	index = SCU_GET_COMPLETION_INDEX(ent);

	चयन (scu_get_command_request_type(ent)) अणु
	हाल SCU_CONTEXT_COMMAND_REQUEST_TYPE_POST_TC:
	हाल SCU_CONTEXT_COMMAND_REQUEST_TYPE_DUMP_TC:
		ireq = ihost->reqs[index];
		dev_warn(&ihost->pdev->dev, "%s: %x for io request %p\n",
			 __func__, ent, ireq);
		/* @toकरो For a post TC operation we need to fail the IO
		 * request
		 */
		अवरोध;
	हाल SCU_CONTEXT_COMMAND_REQUEST_TYPE_DUMP_RNC:
	हाल SCU_CONTEXT_COMMAND_REQUEST_TYPE_OTHER_RNC:
	हाल SCU_CONTEXT_COMMAND_REQUEST_TYPE_POST_RNC:
		idev = ihost->device_table[index];
		dev_warn(&ihost->pdev->dev, "%s: %x for device %p\n",
			 __func__, ent, idev);
		/* @toकरो For a port RNC operation we need to fail the
		 * device
		 */
		अवरोध;
	शेष:
		dev_warn(&ihost->pdev->dev, "%s: unknown completion type %x\n",
			 __func__, ent);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sci_controller_unsolicited_frame(काष्ठा isci_host *ihost, u32 ent)
अणु
	u32 index;
	u32 frame_index;

	काष्ठा scu_unsolicited_frame_header *frame_header;
	काष्ठा isci_phy *iphy;
	काष्ठा isci_remote_device *idev;

	क्रमागत sci_status result = SCI_FAILURE;

	frame_index = SCU_GET_FRAME_INDEX(ent);

	frame_header = ihost->uf_control.buffers.array[frame_index].header;
	ihost->uf_control.buffers.array[frame_index].state = UNSOLICITED_FRAME_IN_USE;

	अगर (SCU_GET_FRAME_ERROR(ent)) अणु
		/*
		 * / @toकरो If the IAF frame or SIGNATURE FIS frame has an error will
		 * /       this cause a problem? We expect the phy initialization will
		 * /       fail अगर there is an error in the frame. */
		sci_controller_release_frame(ihost, frame_index);
		वापस;
	पूर्ण

	अगर (frame_header->is_address_frame) अणु
		index = SCU_GET_PROTOCOL_ENGINE_INDEX(ent);
		iphy = &ihost->phys[index];
		result = sci_phy_frame_handler(iphy, frame_index);
	पूर्ण अन्यथा अणु

		index = SCU_GET_COMPLETION_INDEX(ent);

		अगर (index == SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX) अणु
			/*
			 * This is a signature fis or a frame from a direct attached SATA
			 * device that has not yet been created.  In either हाल क्रमwared
			 * the frame to the PE and let it take care of the frame data. */
			index = SCU_GET_PROTOCOL_ENGINE_INDEX(ent);
			iphy = &ihost->phys[index];
			result = sci_phy_frame_handler(iphy, frame_index);
		पूर्ण अन्यथा अणु
			अगर (index < ihost->remote_node_entries)
				idev = ihost->device_table[index];
			अन्यथा
				idev = शून्य;

			अगर (idev != शून्य)
				result = sci_remote_device_frame_handler(idev, frame_index);
			अन्यथा
				sci_controller_release_frame(ihost, frame_index);
		पूर्ण
	पूर्ण

	अगर (result != SCI_SUCCESS) अणु
		/*
		 * / @toकरो Is there any reason to report some additional error message
		 * /       when we get this failure notअगरiction? */
	पूर्ण
पूर्ण

अटल व्योम sci_controller_event_completion(काष्ठा isci_host *ihost, u32 ent)
अणु
	काष्ठा isci_remote_device *idev;
	काष्ठा isci_request *ireq;
	काष्ठा isci_phy *iphy;
	u32 index;

	index = SCU_GET_COMPLETION_INDEX(ent);

	चयन (scu_get_event_type(ent)) अणु
	हाल SCU_EVENT_TYPE_SMU_COMMAND_ERROR:
		/* / @toकरो The driver did something wrong and we need to fix the condtion. */
		dev_err(&ihost->pdev->dev,
			"%s: SCIC Controller 0x%p received SMU command error "
			"0x%x\n",
			__func__,
			ihost,
			ent);
		अवरोध;

	हाल SCU_EVENT_TYPE_SMU_PCQ_ERROR:
	हाल SCU_EVENT_TYPE_SMU_ERROR:
	हाल SCU_EVENT_TYPE_FATAL_MEMORY_ERROR:
		/*
		 * / @toकरो This is a hardware failure and its likely that we want to
		 * /       reset the controller. */
		dev_err(&ihost->pdev->dev,
			"%s: SCIC Controller 0x%p received fatal controller "
			"event  0x%x\n",
			__func__,
			ihost,
			ent);
		अवरोध;

	हाल SCU_EVENT_TYPE_TRANSPORT_ERROR:
		ireq = ihost->reqs[index];
		sci_io_request_event_handler(ireq, ent);
		अवरोध;

	हाल SCU_EVENT_TYPE_PTX_SCHEDULE_EVENT:
		चयन (scu_get_event_specअगरier(ent)) अणु
		हाल SCU_EVENT_SPECIFIC_SMP_RESPONSE_NO_PE:
		हाल SCU_EVENT_SPECIFIC_TASK_TIMEOUT:
			ireq = ihost->reqs[index];
			अगर (ireq != शून्य)
				sci_io_request_event_handler(ireq, ent);
			अन्यथा
				dev_warn(&ihost->pdev->dev,
					 "%s: SCIC Controller 0x%p received "
					 "event 0x%x for io request object "
					 "that doesnt exist.\n",
					 __func__,
					 ihost,
					 ent);

			अवरोध;

		हाल SCU_EVENT_SPECIFIC_IT_NEXUS_TIMEOUT:
			idev = ihost->device_table[index];
			अगर (idev != शून्य)
				sci_remote_device_event_handler(idev, ent);
			अन्यथा
				dev_warn(&ihost->pdev->dev,
					 "%s: SCIC Controller 0x%p received "
					 "event 0x%x for remote device object "
					 "that doesnt exist.\n",
					 __func__,
					 ihost,
					 ent);

			अवरोध;
		पूर्ण
		अवरोध;

	हाल SCU_EVENT_TYPE_BROADCAST_CHANGE:
	/*
	 * direct the broadcast change event to the phy first and then let
	 * the phy redirect the broadcast change to the port object */
	हाल SCU_EVENT_TYPE_ERR_CNT_EVENT:
	/*
	 * direct error counter event to the phy object since that is where
	 * we get the event notअगरication.  This is a type 4 event. */
	हाल SCU_EVENT_TYPE_OSSP_EVENT:
		index = SCU_GET_PROTOCOL_ENGINE_INDEX(ent);
		iphy = &ihost->phys[index];
		sci_phy_event_handler(iphy, ent);
		अवरोध;

	हाल SCU_EVENT_TYPE_RNC_SUSPEND_TX:
	हाल SCU_EVENT_TYPE_RNC_SUSPEND_TX_RX:
	हाल SCU_EVENT_TYPE_RNC_OPS_MISC:
		अगर (index < ihost->remote_node_entries) अणु
			idev = ihost->device_table[index];

			अगर (idev != शून्य)
				sci_remote_device_event_handler(idev, ent);
		पूर्ण अन्यथा
			dev_err(&ihost->pdev->dev,
				"%s: SCIC Controller 0x%p received event 0x%x "
				"for remote device object 0x%0x that doesnt "
				"exist.\n",
				__func__,
				ihost,
				ent,
				index);

		अवरोध;

	शेष:
		dev_warn(&ihost->pdev->dev,
			 "%s: SCIC Controller received unknown event code %x\n",
			 __func__,
			 ent);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sci_controller_process_completions(काष्ठा isci_host *ihost)
अणु
	u32 completion_count = 0;
	u32 ent;
	u32 get_index;
	u32 get_cycle;
	u32 event_get;
	u32 event_cycle;

	dev_dbg(&ihost->pdev->dev,
		"%s: completion queue beginning get:0x%08x\n",
		__func__,
		ihost->completion_queue_get);

	/* Get the component parts of the completion queue */
	get_index = NORMALIZE_GET_POINTER(ihost->completion_queue_get);
	get_cycle = SMU_CQGR_CYCLE_BIT & ihost->completion_queue_get;

	event_get = NORMALIZE_EVENT_POINTER(ihost->completion_queue_get);
	event_cycle = SMU_CQGR_EVENT_CYCLE_BIT & ihost->completion_queue_get;

	जबतक (
		NORMALIZE_GET_POINTER_CYCLE_BIT(get_cycle)
		== COMPLETION_QUEUE_CYCLE_BIT(ihost->completion_queue[get_index])
		) अणु
		completion_count++;

		ent = ihost->completion_queue[get_index];

		/* increment the get poपूर्णांकer and check क्रम rollover to toggle the cycle bit */
		get_cycle ^= ((get_index+1) & SCU_MAX_COMPLETION_QUEUE_ENTRIES) <<
			     (SMU_COMPLETION_QUEUE_GET_CYCLE_BIT_SHIFT - SCU_MAX_COMPLETION_QUEUE_SHIFT);
		get_index = (get_index+1) & (SCU_MAX_COMPLETION_QUEUE_ENTRIES-1);

		dev_dbg(&ihost->pdev->dev,
			"%s: completion queue entry:0x%08x\n",
			__func__,
			ent);

		चयन (SCU_GET_COMPLETION_TYPE(ent)) अणु
		हाल SCU_COMPLETION_TYPE_TASK:
			sci_controller_task_completion(ihost, ent);
			अवरोध;

		हाल SCU_COMPLETION_TYPE_SDMA:
			sci_controller_sdma_completion(ihost, ent);
			अवरोध;

		हाल SCU_COMPLETION_TYPE_UFI:
			sci_controller_unsolicited_frame(ihost, ent);
			अवरोध;

		हाल SCU_COMPLETION_TYPE_EVENT:
			sci_controller_event_completion(ihost, ent);
			अवरोध;

		हाल SCU_COMPLETION_TYPE_NOTIFY: अणु
			event_cycle ^= ((event_get+1) & SCU_MAX_EVENTS) <<
				       (SMU_COMPLETION_QUEUE_GET_EVENT_CYCLE_BIT_SHIFT - SCU_MAX_EVENTS_SHIFT);
			event_get = (event_get+1) & (SCU_MAX_EVENTS-1);

			sci_controller_event_completion(ihost, ent);
			अवरोध;
		पूर्ण
		शेष:
			dev_warn(&ihost->pdev->dev,
				 "%s: SCIC Controller received unknown "
				 "completion type %x\n",
				 __func__,
				 ent);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Update the get रेजिस्टर अगर we completed one or more entries */
	अगर (completion_count > 0) अणु
		ihost->completion_queue_get =
			SMU_CQGR_GEN_BIT(ENABLE) |
			SMU_CQGR_GEN_BIT(EVENT_ENABLE) |
			event_cycle |
			SMU_CQGR_GEN_VAL(EVENT_POINTER, event_get) |
			get_cycle |
			SMU_CQGR_GEN_VAL(POINTER, get_index);

		ग_लिखोl(ihost->completion_queue_get,
		       &ihost->smu_रेजिस्टरs->completion_queue_get);

	पूर्ण

	dev_dbg(&ihost->pdev->dev,
		"%s: completion queue ending get:0x%08x\n",
		__func__,
		ihost->completion_queue_get);

पूर्ण

अटल व्योम sci_controller_error_handler(काष्ठा isci_host *ihost)
अणु
	u32 पूर्णांकerrupt_status;

	पूर्णांकerrupt_status =
		पढ़ोl(&ihost->smu_रेजिस्टरs->पूर्णांकerrupt_status);

	अगर ((पूर्णांकerrupt_status & SMU_ISR_QUEUE_SUSPEND) &&
	    sci_controller_completion_queue_has_entries(ihost)) अणु

		sci_controller_process_completions(ihost);
		ग_लिखोl(SMU_ISR_QUEUE_SUSPEND, &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_status);
	पूर्ण अन्यथा अणु
		dev_err(&ihost->pdev->dev, "%s: status: %#x\n", __func__,
			पूर्णांकerrupt_status);

		sci_change_state(&ihost->sm, SCIC_FAILED);

		वापस;
	पूर्ण

	/* If we करोnt process any completions I am not sure that we want to करो this.
	 * We are in the middle of a hardware fault and should probably be reset.
	 */
	ग_लिखोl(0, &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_mask);
पूर्ण

irqवापस_t isci_पूर्णांकx_isr(पूर्णांक vec, व्योम *data)
अणु
	irqवापस_t ret = IRQ_NONE;
	काष्ठा isci_host *ihost = data;

	अगर (sci_controller_isr(ihost)) अणु
		ग_लिखोl(SMU_ISR_COMPLETION, &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_status);
		tasklet_schedule(&ihost->completion_tasklet);
		ret = IRQ_HANDLED;
	पूर्ण अन्यथा अगर (sci_controller_error_isr(ihost)) अणु
		spin_lock(&ihost->scic_lock);
		sci_controller_error_handler(ihost);
		spin_unlock(&ihost->scic_lock);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

irqवापस_t isci_error_isr(पूर्णांक vec, व्योम *data)
अणु
	काष्ठा isci_host *ihost = data;

	अगर (sci_controller_error_isr(ihost))
		sci_controller_error_handler(ihost);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * isci_host_start_complete() - This function is called by the core library,
 *    through the ISCI Module, to indicate controller start status.
 * @ihost: This parameter specअगरies the ISCI host object
 * @completion_status: This parameter specअगरies the completion status from the
 *    core library.
 *
 */
अटल व्योम isci_host_start_complete(काष्ठा isci_host *ihost, क्रमागत sci_status completion_status)
अणु
	अगर (completion_status != SCI_SUCCESS)
		dev_info(&ihost->pdev->dev,
			"controller start timed out, continuing...\n");
	clear_bit(IHOST_START_PENDING, &ihost->flags);
	wake_up(&ihost->eventq);
पूर्ण

पूर्णांक isci_host_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ समय)
अणु
	काष्ठा sas_ha_काष्ठा *ha = SHOST_TO_SAS_HA(shost);
	काष्ठा isci_host *ihost = ha->lldd_ha;

	अगर (test_bit(IHOST_START_PENDING, &ihost->flags))
		वापस 0;

	sas_drain_work(ha);

	वापस 1;
पूर्ण

/**
 * sci_controller_get_suggested_start_समयout() - This method वापसs the
 *    suggested sci_controller_start() समयout amount.  The user is मुक्त to
 *    use any समयout value, but this method provides the suggested minimum
 *    start समयout value.  The वापसed value is based upon empirical
 *    inक्रमmation determined as a result of पूर्णांकeroperability testing.
 * @ihost: the handle to the controller object क्रम which to वापस the
 *    suggested start समयout.
 *
 * This method वापसs the number of milliseconds क्रम the suggested start
 * operation समयout.
 */
अटल u32 sci_controller_get_suggested_start_समयout(काष्ठा isci_host *ihost)
अणु
	/* Validate the user supplied parameters. */
	अगर (!ihost)
		वापस 0;

	/*
	 * The suggested minimum समयout value क्रम a controller start operation:
	 *
	 *     Signature FIS Timeout
	 *   + Phy Start Timeout
	 *   + Number of Phy Spin Up Intervals
	 *   ---------------------------------
	 *   Number of milliseconds क्रम the controller start operation.
	 *
	 * NOTE: The number of phy spin up पूर्णांकervals will be equivalent
	 *       to the number of phys भागided by the number phys allowed
	 *       per पूर्णांकerval - 1 (once OEM parameters are supported).
	 *       Currently we assume only 1 phy per पूर्णांकerval. */

	वापस SCIC_SDS_SIGNATURE_FIS_TIMEOUT
		+ SCIC_SDS_CONTROLLER_PHY_START_TIMEOUT
		+ ((SCI_MAX_PHYS - 1) * SCIC_SDS_CONTROLLER_POWER_CONTROL_INTERVAL);
पूर्ण

अटल व्योम sci_controller_enable_पूर्णांकerrupts(काष्ठा isci_host *ihost)
अणु
	set_bit(IHOST_IRQ_ENABLED, &ihost->flags);
	ग_लिखोl(0, &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_mask);
पूर्ण

व्योम sci_controller_disable_पूर्णांकerrupts(काष्ठा isci_host *ihost)
अणु
	clear_bit(IHOST_IRQ_ENABLED, &ihost->flags);
	ग_लिखोl(0xffffffff, &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_mask);
	पढ़ोl(&ihost->smu_रेजिस्टरs->पूर्णांकerrupt_mask); /* flush */
पूर्ण

अटल व्योम sci_controller_enable_port_task_scheduler(काष्ठा isci_host *ihost)
अणु
	u32 port_task_scheduler_value;

	port_task_scheduler_value =
		पढ़ोl(&ihost->scu_रेजिस्टरs->peg0.ptsg.control);
	port_task_scheduler_value |=
		(SCU_PTSGCR_GEN_BIT(ETM_ENABLE) |
		 SCU_PTSGCR_GEN_BIT(PTSG_ENABLE));
	ग_लिखोl(port_task_scheduler_value,
	       &ihost->scu_रेजिस्टरs->peg0.ptsg.control);
पूर्ण

अटल व्योम sci_controller_assign_task_entries(काष्ठा isci_host *ihost)
अणु
	u32 task_assignment;

	/*
	 * Assign all the TCs to function 0
	 * TODO: Do we actually need to पढ़ो this रेजिस्टर to ग_लिखो it back?
	 */

	task_assignment =
		पढ़ोl(&ihost->smu_रेजिस्टरs->task_context_assignment[0]);

	task_assignment |= (SMU_TCA_GEN_VAL(STARTING, 0)) |
		(SMU_TCA_GEN_VAL(ENDING,  ihost->task_context_entries - 1)) |
		(SMU_TCA_GEN_BIT(RANGE_CHECK_ENABLE));

	ग_लिखोl(task_assignment,
		&ihost->smu_रेजिस्टरs->task_context_assignment[0]);

पूर्ण

अटल व्योम sci_controller_initialize_completion_queue(काष्ठा isci_host *ihost)
अणु
	u32 index;
	u32 completion_queue_control_value;
	u32 completion_queue_get_value;
	u32 completion_queue_put_value;

	ihost->completion_queue_get = 0;

	completion_queue_control_value =
		(SMU_CQC_QUEUE_LIMIT_SET(SCU_MAX_COMPLETION_QUEUE_ENTRIES - 1) |
		 SMU_CQC_EVENT_LIMIT_SET(SCU_MAX_EVENTS - 1));

	ग_लिखोl(completion_queue_control_value,
	       &ihost->smu_रेजिस्टरs->completion_queue_control);


	/* Set the completion queue get poपूर्णांकer and enable the queue */
	completion_queue_get_value = (
		(SMU_CQGR_GEN_VAL(POINTER, 0))
		| (SMU_CQGR_GEN_VAL(EVENT_POINTER, 0))
		| (SMU_CQGR_GEN_BIT(ENABLE))
		| (SMU_CQGR_GEN_BIT(EVENT_ENABLE))
		);

	ग_लिखोl(completion_queue_get_value,
	       &ihost->smu_रेजिस्टरs->completion_queue_get);

	/* Set the completion queue put poपूर्णांकer */
	completion_queue_put_value = (
		(SMU_CQPR_GEN_VAL(POINTER, 0))
		| (SMU_CQPR_GEN_VAL(EVENT_POINTER, 0))
		);

	ग_लिखोl(completion_queue_put_value,
	       &ihost->smu_रेजिस्टरs->completion_queue_put);

	/* Initialize the cycle bit of the completion queue entries */
	क्रम (index = 0; index < SCU_MAX_COMPLETION_QUEUE_ENTRIES; index++) अणु
		/*
		 * If get.cycle_bit != completion_queue.cycle_bit
		 * its not a valid completion queue entry
		 * so at प्रणाली start all entries are invalid */
		ihost->completion_queue[index] = 0x80000000;
	पूर्ण
पूर्ण

अटल व्योम sci_controller_initialize_unsolicited_frame_queue(काष्ठा isci_host *ihost)
अणु
	u32 frame_queue_control_value;
	u32 frame_queue_get_value;
	u32 frame_queue_put_value;

	/* Write the queue size */
	frame_queue_control_value =
		SCU_UFQC_GEN_VAL(QUEUE_SIZE, SCU_MAX_UNSOLICITED_FRAMES);

	ग_लिखोl(frame_queue_control_value,
	       &ihost->scu_रेजिस्टरs->sdma.unsolicited_frame_queue_control);

	/* Setup the get poपूर्णांकer क्रम the unsolicited frame queue */
	frame_queue_get_value = (
		SCU_UFQGP_GEN_VAL(POINTER, 0)
		|  SCU_UFQGP_GEN_BIT(ENABLE_BIT)
		);

	ग_लिखोl(frame_queue_get_value,
	       &ihost->scu_रेजिस्टरs->sdma.unsolicited_frame_get_poपूर्णांकer);
	/* Setup the put poपूर्णांकer क्रम the unsolicited frame queue */
	frame_queue_put_value = SCU_UFQPP_GEN_VAL(POINTER, 0);
	ग_लिखोl(frame_queue_put_value,
	       &ihost->scu_रेजिस्टरs->sdma.unsolicited_frame_put_poपूर्णांकer);
पूर्ण

व्योम sci_controller_transition_to_पढ़ोy(काष्ठा isci_host *ihost, क्रमागत sci_status status)
अणु
	अगर (ihost->sm.current_state_id == SCIC_STARTING) अणु
		/*
		 * We move पूर्णांकo the पढ़ोy state, because some of the phys/ports
		 * may be up and operational.
		 */
		sci_change_state(&ihost->sm, SCIC_READY);

		isci_host_start_complete(ihost, status);
	पूर्ण
पूर्ण

अटल bool is_phy_starting(काष्ठा isci_phy *iphy)
अणु
	क्रमागत sci_phy_states state;

	state = iphy->sm.current_state_id;
	चयन (state) अणु
	हाल SCI_PHY_STARTING:
	हाल SCI_PHY_SUB_INITIAL:
	हाल SCI_PHY_SUB_AWAIT_SAS_SPEED_EN:
	हाल SCI_PHY_SUB_AWAIT_IAF_UF:
	हाल SCI_PHY_SUB_AWAIT_SAS_POWER:
	हाल SCI_PHY_SUB_AWAIT_SATA_POWER:
	हाल SCI_PHY_SUB_AWAIT_SATA_PHY_EN:
	हाल SCI_PHY_SUB_AWAIT_SATA_SPEED_EN:
	हाल SCI_PHY_SUB_AWAIT_OSSP_EN:
	हाल SCI_PHY_SUB_AWAIT_SIG_FIS_UF:
	हाल SCI_PHY_SUB_FINAL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

bool is_controller_start_complete(काष्ठा isci_host *ihost)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SCI_MAX_PHYS; i++) अणु
		काष्ठा isci_phy *iphy = &ihost->phys[i];
		u32 state = iphy->sm.current_state_id;

		/* in apc mode we need to check every phy, in
		 * mpc mode we only need to check phys that have
		 * been configured पूर्णांकo a port
		 */
		अगर (is_port_config_apc(ihost))
			/* pass */;
		अन्यथा अगर (!phy_get_non_dummy_port(iphy))
			जारी;

		/* The controller start operation is complete अगरf:
		 * - all links have been given an opportunity to start
		 * - have no indication of a connected device
		 * - have an indication of a connected device and it has
		 *   finished the link training process.
		 */
		अगर ((iphy->is_in_link_training == false && state == SCI_PHY_INITIAL) ||
		    (iphy->is_in_link_training == false && state == SCI_PHY_STOPPED) ||
		    (iphy->is_in_link_training == true && is_phy_starting(iphy)) ||
		    (ihost->port_agent.phy_पढ़ोy_mask != ihost->port_agent.phy_configured_mask))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * sci_controller_start_next_phy - start phy
 * @ihost: controller
 *
 * If all the phys have been started, then attempt to transition the
 * controller to the READY state and inक्रमm the user
 * (sci_cb_controller_start_complete()).
 */
अटल क्रमागत sci_status sci_controller_start_next_phy(काष्ठा isci_host *ihost)
अणु
	काष्ठा sci_oem_params *oem = &ihost->oem_parameters;
	काष्ठा isci_phy *iphy;
	क्रमागत sci_status status;

	status = SCI_SUCCESS;

	अगर (ihost->phy_startup_समयr_pending)
		वापस status;

	अगर (ihost->next_phy_to_start >= SCI_MAX_PHYS) अणु
		अगर (is_controller_start_complete(ihost)) अणु
			sci_controller_transition_to_पढ़ोy(ihost, SCI_SUCCESS);
			sci_del_समयr(&ihost->phy_समयr);
			ihost->phy_startup_समयr_pending = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		iphy = &ihost->phys[ihost->next_phy_to_start];

		अगर (oem->controller.mode_type == SCIC_PORT_MANUAL_CONFIGURATION_MODE) अणु
			अगर (phy_get_non_dummy_port(iphy) == शून्य) अणु
				ihost->next_phy_to_start++;

				/* Caution recursion ahead be क्रमwarned
				 *
				 * The PHY was never added to a PORT in MPC mode
				 * so start the next phy in sequence This phy
				 * will never go link up and will not draw घातer
				 * the OEM parameters either configured the phy
				 * incorrectly क्रम the PORT or it was never
				 * asचिन्हित to a PORT
				 */
				वापस sci_controller_start_next_phy(ihost);
			पूर्ण
		पूर्ण

		status = sci_phy_start(iphy);

		अगर (status == SCI_SUCCESS) अणु
			sci_mod_समयr(&ihost->phy_समयr,
				      SCIC_SDS_CONTROLLER_PHY_START_TIMEOUT);
			ihost->phy_startup_समयr_pending = true;
		पूर्ण अन्यथा अणु
			dev_warn(&ihost->pdev->dev,
				 "%s: Controller stop operation failed "
				 "to stop phy %d because of status "
				 "%d.\n",
				 __func__,
				 ihost->phys[ihost->next_phy_to_start].phy_index,
				 status);
		पूर्ण

		ihost->next_phy_to_start++;
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम phy_startup_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा sci_समयr *पंचांगr = from_समयr(पंचांगr, t, समयr);
	काष्ठा isci_host *ihost = container_of(पंचांगr, typeof(*ihost), phy_समयr);
	अचिन्हित दीर्घ flags;
	क्रमागत sci_status status;

	spin_lock_irqsave(&ihost->scic_lock, flags);

	अगर (पंचांगr->cancel)
		जाओ करोne;

	ihost->phy_startup_समयr_pending = false;

	करो अणु
		status = sci_controller_start_next_phy(ihost);
	पूर्ण जबतक (status != SCI_SUCCESS);

करोne:
	spin_unlock_irqrestore(&ihost->scic_lock, flags);
पूर्ण

अटल u16 isci_tci_active(काष्ठा isci_host *ihost)
अणु
	वापस CIRC_CNT(ihost->tci_head, ihost->tci_tail, SCI_MAX_IO_REQUESTS);
पूर्ण

अटल क्रमागत sci_status sci_controller_start(काष्ठा isci_host *ihost,
					     u32 समयout)
अणु
	क्रमागत sci_status result;
	u16 index;

	अगर (ihost->sm.current_state_id != SCIC_INITIALIZED) अणु
		dev_warn(&ihost->pdev->dev, "%s invalid state: %d\n",
			 __func__, ihost->sm.current_state_id);
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	/* Build the TCi मुक्त pool */
	BUILD_BUG_ON(SCI_MAX_IO_REQUESTS > 1 << माप(ihost->tci_pool[0]) * 8);
	ihost->tci_head = 0;
	ihost->tci_tail = 0;
	क्रम (index = 0; index < ihost->task_context_entries; index++)
		isci_tci_मुक्त(ihost, index);

	/* Build the RNi मुक्त pool */
	sci_remote_node_table_initialize(&ihost->available_remote_nodes,
					 ihost->remote_node_entries);

	/*
	 * Beक्रमe anything अन्यथा lets make sure we will not be
	 * पूर्णांकerrupted by the hardware.
	 */
	sci_controller_disable_पूर्णांकerrupts(ihost);

	/* Enable the port task scheduler */
	sci_controller_enable_port_task_scheduler(ihost);

	/* Assign all the task entries to ihost physical function */
	sci_controller_assign_task_entries(ihost);

	/* Now initialize the completion queue */
	sci_controller_initialize_completion_queue(ihost);

	/* Initialize the unsolicited frame queue क्रम use */
	sci_controller_initialize_unsolicited_frame_queue(ihost);

	/* Start all of the ports on this controller */
	क्रम (index = 0; index < ihost->logical_port_entries; index++) अणु
		काष्ठा isci_port *iport = &ihost->ports[index];

		result = sci_port_start(iport);
		अगर (result)
			वापस result;
	पूर्ण

	sci_controller_start_next_phy(ihost);

	sci_mod_समयr(&ihost->समयr, समयout);

	sci_change_state(&ihost->sm, SCIC_STARTING);

	वापस SCI_SUCCESS;
पूर्ण

व्योम isci_host_start(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा isci_host *ihost = SHOST_TO_SAS_HA(shost)->lldd_ha;
	अचिन्हित दीर्घ पंचांगo = sci_controller_get_suggested_start_समयout(ihost);

	set_bit(IHOST_START_PENDING, &ihost->flags);

	spin_lock_irq(&ihost->scic_lock);
	sci_controller_start(ihost, पंचांगo);
	sci_controller_enable_पूर्णांकerrupts(ihost);
	spin_unlock_irq(&ihost->scic_lock);
पूर्ण

अटल व्योम isci_host_stop_complete(काष्ठा isci_host *ihost)
अणु
	sci_controller_disable_पूर्णांकerrupts(ihost);
	clear_bit(IHOST_STOP_PENDING, &ihost->flags);
	wake_up(&ihost->eventq);
पूर्ण

अटल व्योम sci_controller_completion_handler(काष्ठा isci_host *ihost)
अणु
	/* Empty out the completion queue */
	अगर (sci_controller_completion_queue_has_entries(ihost))
		sci_controller_process_completions(ihost);

	/* Clear the पूर्णांकerrupt and enable all पूर्णांकerrupts again */
	ग_लिखोl(SMU_ISR_COMPLETION, &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_status);
	/* Could we ग_लिखो the value of SMU_ISR_COMPLETION? */
	ग_लिखोl(0xFF000000, &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_mask);
	ग_लिखोl(0, &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_mask);
पूर्ण

व्योम ireq_करोne(काष्ठा isci_host *ihost, काष्ठा isci_request *ireq, काष्ठा sas_task *task)
अणु
	अगर (!test_bit(IREQ_ABORT_PATH_ACTIVE, &ireq->flags) &&
	    !(task->task_state_flags & SAS_TASK_STATE_ABORTED)) अणु
		अगर (test_bit(IREQ_COMPLETE_IN_TARGET, &ireq->flags)) अणु
			/* Normal notअगरication (task_करोne) */
			dev_dbg(&ihost->pdev->dev,
				"%s: Normal - ireq/task = %p/%p\n",
				__func__, ireq, task);
			task->lldd_task = शून्य;
			task->task_करोne(task);
		पूर्ण अन्यथा अणु
			dev_dbg(&ihost->pdev->dev,
				"%s: Error - ireq/task = %p/%p\n",
				__func__, ireq, task);
			अगर (sas_protocol_ata(task->task_proto))
				task->lldd_task = शून्य;
			sas_task_पात(task);
		पूर्ण
	पूर्ण अन्यथा
		task->lldd_task = शून्य;

	अगर (test_and_clear_bit(IREQ_ABORT_PATH_ACTIVE, &ireq->flags))
		wake_up_all(&ihost->eventq);

	अगर (!test_bit(IREQ_NO_AUTO_FREE_TAG, &ireq->flags))
		isci_मुक्त_tag(ihost, ireq->io_tag);
पूर्ण
/**
 * isci_host_completion_routine() - This function is the delayed service
 *    routine that calls the sci core library's completion handler. It's
 *    scheduled as a tasklet from the पूर्णांकerrupt service routine when पूर्णांकerrupts
 *    in use, or set as the समयout function in polled mode.
 * @data: This parameter specअगरies the ISCI host object
 *
 */
व्योम isci_host_completion_routine(अचिन्हित दीर्घ data)
अणु
	काष्ठा isci_host *ihost = (काष्ठा isci_host *)data;
	u16 active;

	spin_lock_irq(&ihost->scic_lock);
	sci_controller_completion_handler(ihost);
	spin_unlock_irq(&ihost->scic_lock);

	/*
	 * we subtract SCI_MAX_PORTS to account क्रम the number of dummy TCs
	 * issued क्रम hardware issue workaround
	 */
	active = isci_tci_active(ihost) - SCI_MAX_PORTS;

	/*
	 * the coalesence समयout द्विगुनs at each encoding step, so
	 * update it based on the ilog2 value of the outstanding requests
	 */
	ग_लिखोl(SMU_ICC_GEN_VAL(NUMBER, active) |
	       SMU_ICC_GEN_VAL(TIMER, ISCI_COALESCE_BASE + ilog2(active)),
	       &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_coalesce_control);
पूर्ण

/**
 * sci_controller_stop() - This method will stop an inभागidual controller
 *    object.This method will invoke the associated user callback upon
 *    completion.  The completion callback is called when the following
 *    conditions are met: -# the method वापस status is SCI_SUCCESS. -# the
 *    controller has been quiesced. This method will ensure that all IO
 *    requests are quiesced, phys are stopped, and all additional operation by
 *    the hardware is halted.
 * @ihost: the handle to the controller object to stop.
 * @समयout: This parameter specअगरies the number of milliseconds in which the
 *    stop operation should complete.
 *
 * The controller must be in the STARTED or STOPPED state. Indicate अगर the
 * controller stop method succeeded or failed in some way. SCI_SUCCESS अगर the
 * stop operation successfully began. SCI_WARNING_ALREADY_IN_STATE अगर the
 * controller is alपढ़ोy in the STOPPED state. SCI_FAILURE_INVALID_STATE अगर the
 * controller is not either in the STARTED or STOPPED states.
 */
अटल क्रमागत sci_status sci_controller_stop(काष्ठा isci_host *ihost, u32 समयout)
अणु
	अगर (ihost->sm.current_state_id != SCIC_READY) अणु
		dev_warn(&ihost->pdev->dev, "%s invalid state: %d\n",
			 __func__, ihost->sm.current_state_id);
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	sci_mod_समयr(&ihost->समयr, समयout);
	sci_change_state(&ihost->sm, SCIC_STOPPING);
	वापस SCI_SUCCESS;
पूर्ण

/**
 * sci_controller_reset() - This method will reset the supplied core
 *    controller regardless of the state of said controller.  This operation is
 *    considered deकाष्ठाive.  In other words, all current operations are wiped
 *    out.  No IO completions क्रम outstanding devices occur.  Outstanding IO
 *    requests are not पातed or completed at the actual remote device.
 * @ihost: the handle to the controller object to reset.
 *
 * Indicate अगर the controller reset method succeeded or failed in some way.
 * SCI_SUCCESS अगर the reset operation successfully started. SCI_FATAL_ERROR अगर
 * the controller reset operation is unable to complete.
 */
अटल क्रमागत sci_status sci_controller_reset(काष्ठा isci_host *ihost)
अणु
	चयन (ihost->sm.current_state_id) अणु
	हाल SCIC_RESET:
	हाल SCIC_READY:
	हाल SCIC_STOPPING:
	हाल SCIC_FAILED:
		/*
		 * The reset operation is not a graceful cleanup, just
		 * perक्रमm the state transition.
		 */
		sci_change_state(&ihost->sm, SCIC_RESETTING);
		वापस SCI_SUCCESS;
	शेष:
		dev_warn(&ihost->pdev->dev, "%s invalid state: %d\n",
			 __func__, ihost->sm.current_state_id);
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
पूर्ण

अटल क्रमागत sci_status sci_controller_stop_phys(काष्ठा isci_host *ihost)
अणु
	u32 index;
	क्रमागत sci_status status;
	क्रमागत sci_status phy_status;

	status = SCI_SUCCESS;

	क्रम (index = 0; index < SCI_MAX_PHYS; index++) अणु
		phy_status = sci_phy_stop(&ihost->phys[index]);

		अगर (phy_status != SCI_SUCCESS &&
		    phy_status != SCI_FAILURE_INVALID_STATE) अणु
			status = SCI_FAILURE;

			dev_warn(&ihost->pdev->dev,
				 "%s: Controller stop operation failed to stop "
				 "phy %d because of status %d.\n",
				 __func__,
				 ihost->phys[index].phy_index, phy_status);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण


/**
 * isci_host_deinit - shutकरोwn frame reception and dma
 * @ihost: host to take करोwn
 *
 * This is called in either the driver shutकरोwn or the suspend path.  In
 * the shutकरोwn हाल libsas went through port tearकरोwn and normal device
 * removal (i.e. physical links stayed up to service scsi_device removal
 * commands).  In the suspend हाल we disable the hardware without
 * notअगरying libsas of the link करोwn events since we want libsas to
 * remember the करोमुख्य across the suspend/resume cycle
 */
व्योम isci_host_deinit(काष्ठा isci_host *ihost)
अणु
	पूर्णांक i;

	/* disable output data selects */
	क्रम (i = 0; i < isci_gpio_count(ihost); i++)
		ग_लिखोl(SGPIO_HW_CONTROL, &ihost->scu_रेजिस्टरs->peg0.sgpio.output_data_select[i]);

	set_bit(IHOST_STOP_PENDING, &ihost->flags);

	spin_lock_irq(&ihost->scic_lock);
	sci_controller_stop(ihost, SCIC_CONTROLLER_STOP_TIMEOUT);
	spin_unlock_irq(&ihost->scic_lock);

	रुको_क्रम_stop(ihost);

	/* phy stop is after controller stop to allow port and device to
	 * go idle beक्रमe shutting करोwn the phys, but the expectation is
	 * that i/o has been shut off well beक्रमe we reach this
	 * function.
	 */
	sci_controller_stop_phys(ihost);

	/* disable sgpio: where the above रुको should give समय क्रम the
	 * enclosure to sample the gpios going inactive
	 */
	ग_लिखोl(0, &ihost->scu_रेजिस्टरs->peg0.sgpio.पूर्णांकerface_control);

	spin_lock_irq(&ihost->scic_lock);
	sci_controller_reset(ihost);
	spin_unlock_irq(&ihost->scic_lock);

	/* Cancel any/all outstanding port समयrs */
	क्रम (i = 0; i < ihost->logical_port_entries; i++) अणु
		काष्ठा isci_port *iport = &ihost->ports[i];
		del_समयr_sync(&iport->समयr.समयr);
	पूर्ण

	/* Cancel any/all outstanding phy समयrs */
	क्रम (i = 0; i < SCI_MAX_PHYS; i++) अणु
		काष्ठा isci_phy *iphy = &ihost->phys[i];
		del_समयr_sync(&iphy->sata_समयr.समयr);
	पूर्ण

	del_समयr_sync(&ihost->port_agent.समयr.समयr);

	del_समयr_sync(&ihost->घातer_control.समयr.समयr);

	del_समयr_sync(&ihost->समयr.समयr);

	del_समयr_sync(&ihost->phy_समयr.समयr);
पूर्ण

अटल व्योम __iomem *scu_base(काष्ठा isci_host *isci_host)
अणु
	काष्ठा pci_dev *pdev = isci_host->pdev;
	पूर्णांक id = isci_host->id;

	वापस pcim_iomap_table(pdev)[SCI_SCU_BAR * 2] + SCI_SCU_BAR_SIZE * id;
पूर्ण

अटल व्योम __iomem *smu_base(काष्ठा isci_host *isci_host)
अणु
	काष्ठा pci_dev *pdev = isci_host->pdev;
	पूर्णांक id = isci_host->id;

	वापस pcim_iomap_table(pdev)[SCI_SMU_BAR * 2] + SCI_SMU_BAR_SIZE * id;
पूर्ण

अटल व्योम sci_controller_initial_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_host *ihost = container_of(sm, typeof(*ihost), sm);

	sci_change_state(&ihost->sm, SCIC_RESET);
पूर्ण

अटल अंतरभूत व्योम sci_controller_starting_state_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_host *ihost = container_of(sm, typeof(*ihost), sm);

	sci_del_समयr(&ihost->समयr);
पूर्ण

#घोषणा INTERRUPT_COALESCE_TIMEOUT_BASE_RANGE_LOWER_BOUND_NS 853
#घोषणा INTERRUPT_COALESCE_TIMEOUT_BASE_RANGE_UPPER_BOUND_NS 1280
#घोषणा INTERRUPT_COALESCE_TIMEOUT_MAX_US                    2700000
#घोषणा INTERRUPT_COALESCE_NUMBER_MAX                        256
#घोषणा INTERRUPT_COALESCE_TIMEOUT_ENCODE_MIN                7
#घोषणा INTERRUPT_COALESCE_TIMEOUT_ENCODE_MAX                28

/**
 * sci_controller_set_पूर्णांकerrupt_coalescence() - This method allows the user to
 *    configure the पूर्णांकerrupt coalescence.
 * @ihost: This parameter represents the handle to the controller object
 *    क्रम which its पूर्णांकerrupt coalesce रेजिस्टर is overridden.
 * @coalesce_number: Used to control the number of entries in the Completion
 *    Queue beक्रमe an पूर्णांकerrupt is generated. If the number of entries exceed
 *    this number, an पूर्णांकerrupt will be generated. The valid range of the input
 *    is [0, 256]. A setting of 0 results in coalescing being disabled.
 * @coalesce_समयout: Timeout value in microseconds. The valid range of the
 *    input is [0, 2700000] . A setting of 0 is allowed and results in no
 *    पूर्णांकerrupt coalescing समयout.
 *
 * Indicate अगर the user successfully set the पूर्णांकerrupt coalesce parameters.
 * SCI_SUCCESS The user successfully updated the पूर्णांकerrutp coalescence.
 * SCI_FAILURE_INVALID_PARAMETER_VALUE The user input value is out of range.
 */
अटल क्रमागत sci_status
sci_controller_set_पूर्णांकerrupt_coalescence(काष्ठा isci_host *ihost,
					 u32 coalesce_number,
					 u32 coalesce_समयout)
अणु
	u8 समयout_encode = 0;
	u32 min = 0;
	u32 max = 0;

	/* Check अगर the input parameters fall in the range. */
	अगर (coalesce_number > INTERRUPT_COALESCE_NUMBER_MAX)
		वापस SCI_FAILURE_INVALID_PARAMETER_VALUE;

	/*
	 *  Defined encoding क्रम पूर्णांकerrupt coalescing समयout:
	 *              Value   Min      Max     Units
	 *              -----   ---      ---     -----
	 *              0       -        -       Disabled
	 *              1       13.3     20.0    ns
	 *              2       26.7     40.0
	 *              3       53.3     80.0
	 *              4       106.7    160.0
	 *              5       213.3    320.0
	 *              6       426.7    640.0
	 *              7       853.3    1280.0
	 *              8       1.7      2.6     us
	 *              9       3.4      5.1
	 *              10      6.8      10.2
	 *              11      13.7     20.5
	 *              12      27.3     41.0
	 *              13      54.6     81.9
	 *              14      109.2    163.8
	 *              15      218.5    327.7
	 *              16      436.9    655.4
	 *              17      873.8    1310.7
	 *              18      1.7      2.6     ms
	 *              19      3.5      5.2
	 *              20      7.0      10.5
	 *              21      14.0     21.0
	 *              22      28.0     41.9
	 *              23      55.9     83.9
	 *              24      111.8    167.8
	 *              25      223.7    335.5
	 *              26      447.4    671.1
	 *              27      894.8    1342.2
	 *              28      1.8      2.7     s
	 *              Others Undefined */

	/*
	 * Use the table above to decide the encode of पूर्णांकerrupt coalescing समयout
	 * value क्रम रेजिस्टर writing. */
	अगर (coalesce_समयout == 0)
		समयout_encode = 0;
	अन्यथाअणु
		/* make the समयout value in unit of (10 ns). */
		coalesce_समयout = coalesce_समयout * 100;
		min = INTERRUPT_COALESCE_TIMEOUT_BASE_RANGE_LOWER_BOUND_NS / 10;
		max = INTERRUPT_COALESCE_TIMEOUT_BASE_RANGE_UPPER_BOUND_NS / 10;

		/* get the encode of समयout क्रम रेजिस्टर writing. */
		क्रम (समयout_encode = INTERRUPT_COALESCE_TIMEOUT_ENCODE_MIN;
		      समयout_encode <= INTERRUPT_COALESCE_TIMEOUT_ENCODE_MAX;
		      समयout_encode++) अणु
			अगर (min <= coalesce_समयout &&  max > coalesce_समयout)
				अवरोध;
			अन्यथा अगर (coalesce_समयout >= max && coalesce_समयout < min * 2
				 && coalesce_समयout <= INTERRUPT_COALESCE_TIMEOUT_MAX_US * 100) अणु
				अगर ((coalesce_समयout - max) < (2 * min - coalesce_समयout))
					अवरोध;
				अन्यथाअणु
					समयout_encode++;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				max = max * 2;
				min = min * 2;
			पूर्ण
		पूर्ण

		अगर (समयout_encode == INTERRUPT_COALESCE_TIMEOUT_ENCODE_MAX + 1)
			/* the value is out of range. */
			वापस SCI_FAILURE_INVALID_PARAMETER_VALUE;
	पूर्ण

	ग_लिखोl(SMU_ICC_GEN_VAL(NUMBER, coalesce_number) |
	       SMU_ICC_GEN_VAL(TIMER, समयout_encode),
	       &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_coalesce_control);


	ihost->पूर्णांकerrupt_coalesce_number = (u16)coalesce_number;
	ihost->पूर्णांकerrupt_coalesce_समयout = coalesce_समयout / 100;

	वापस SCI_SUCCESS;
पूर्ण


अटल व्योम sci_controller_पढ़ोy_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_host *ihost = container_of(sm, typeof(*ihost), sm);
	u32 val;

	/* enable घड़ी gating क्रम घातer control of the scu unit */
	val = पढ़ोl(&ihost->smu_रेजिस्टरs->घड़ी_gating_control);
	val &= ~(SMU_CGUCR_GEN_BIT(REGCLK_ENABLE) |
		 SMU_CGUCR_GEN_BIT(TXCLK_ENABLE) |
		 SMU_CGUCR_GEN_BIT(XCLK_ENABLE));
	val |= SMU_CGUCR_GEN_BIT(IDLE_ENABLE);
	ग_लिखोl(val, &ihost->smu_रेजिस्टरs->घड़ी_gating_control);

	/* set the शेष पूर्णांकerrupt coalescence number and समयout value. */
	sci_controller_set_पूर्णांकerrupt_coalescence(ihost, 0, 0);
पूर्ण

अटल व्योम sci_controller_पढ़ोy_state_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_host *ihost = container_of(sm, typeof(*ihost), sm);

	/* disable पूर्णांकerrupt coalescence. */
	sci_controller_set_पूर्णांकerrupt_coalescence(ihost, 0, 0);
पूर्ण

अटल क्रमागत sci_status sci_controller_stop_ports(काष्ठा isci_host *ihost)
अणु
	u32 index;
	क्रमागत sci_status port_status;
	क्रमागत sci_status status = SCI_SUCCESS;

	क्रम (index = 0; index < ihost->logical_port_entries; index++) अणु
		काष्ठा isci_port *iport = &ihost->ports[index];

		port_status = sci_port_stop(iport);

		अगर ((port_status != SCI_SUCCESS) &&
		    (port_status != SCI_FAILURE_INVALID_STATE)) अणु
			status = SCI_FAILURE;

			dev_warn(&ihost->pdev->dev,
				 "%s: Controller stop operation failed to "
				 "stop port %d because of status %d.\n",
				 __func__,
				 iport->logical_port_index,
				 port_status);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल क्रमागत sci_status sci_controller_stop_devices(काष्ठा isci_host *ihost)
अणु
	u32 index;
	क्रमागत sci_status status;
	क्रमागत sci_status device_status;

	status = SCI_SUCCESS;

	क्रम (index = 0; index < ihost->remote_node_entries; index++) अणु
		अगर (ihost->device_table[index] != शून्य) अणु
			/* / @toकरो What समयout value करो we want to provide to this request? */
			device_status = sci_remote_device_stop(ihost->device_table[index], 0);

			अगर ((device_status != SCI_SUCCESS) &&
			    (device_status != SCI_FAILURE_INVALID_STATE)) अणु
				dev_warn(&ihost->pdev->dev,
					 "%s: Controller stop operation failed "
					 "to stop device 0x%p because of "
					 "status %d.\n",
					 __func__,
					 ihost->device_table[index], device_status);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम sci_controller_stopping_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_host *ihost = container_of(sm, typeof(*ihost), sm);

	sci_controller_stop_devices(ihost);
	sci_controller_stop_ports(ihost);

	अगर (!sci_controller_has_remote_devices_stopping(ihost))
		isci_host_stop_complete(ihost);
पूर्ण

अटल व्योम sci_controller_stopping_state_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_host *ihost = container_of(sm, typeof(*ihost), sm);

	sci_del_समयr(&ihost->समयr);
पूर्ण

अटल व्योम sci_controller_reset_hardware(काष्ठा isci_host *ihost)
अणु
	/* Disable पूर्णांकerrupts so we करोnt take any spurious पूर्णांकerrupts */
	sci_controller_disable_पूर्णांकerrupts(ihost);

	/* Reset the SCU */
	ग_लिखोl(0xFFFFFFFF, &ihost->smu_रेजिस्टरs->soft_reset_control);

	/* Delay क्रम 1ms to beक्रमe clearing the CQP and UFQPR. */
	udelay(1000);

	/* The ग_लिखो to the CQGR clears the CQP */
	ग_लिखोl(0x00000000, &ihost->smu_रेजिस्टरs->completion_queue_get);

	/* The ग_लिखो to the UFQGP clears the UFQPR */
	ग_लिखोl(0, &ihost->scu_रेजिस्टरs->sdma.unsolicited_frame_get_poपूर्णांकer);

	/* clear all पूर्णांकerrupts */
	ग_लिखोl(~SMU_INTERRUPT_STATUS_RESERVED_MASK, &ihost->smu_रेजिस्टरs->पूर्णांकerrupt_status);
पूर्ण

अटल व्योम sci_controller_resetting_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_host *ihost = container_of(sm, typeof(*ihost), sm);

	sci_controller_reset_hardware(ihost);
	sci_change_state(&ihost->sm, SCIC_RESET);
पूर्ण

अटल स्थिर काष्ठा sci_base_state sci_controller_state_table[] = अणु
	[SCIC_INITIAL] = अणु
		.enter_state = sci_controller_initial_state_enter,
	पूर्ण,
	[SCIC_RESET] = अणुपूर्ण,
	[SCIC_INITIALIZING] = अणुपूर्ण,
	[SCIC_INITIALIZED] = अणुपूर्ण,
	[SCIC_STARTING] = अणु
		.निकास_state  = sci_controller_starting_state_निकास,
	पूर्ण,
	[SCIC_READY] = अणु
		.enter_state = sci_controller_पढ़ोy_state_enter,
		.निकास_state  = sci_controller_पढ़ोy_state_निकास,
	पूर्ण,
	[SCIC_RESETTING] = अणु
		.enter_state = sci_controller_resetting_state_enter,
	पूर्ण,
	[SCIC_STOPPING] = अणु
		.enter_state = sci_controller_stopping_state_enter,
		.निकास_state = sci_controller_stopping_state_निकास,
	पूर्ण,
	[SCIC_FAILED] = अणुपूर्ण
पूर्ण;

अटल व्योम controller_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा sci_समयr *पंचांगr = from_समयr(पंचांगr, t, समयr);
	काष्ठा isci_host *ihost = container_of(पंचांगr, typeof(*ihost), समयr);
	काष्ठा sci_base_state_machine *sm = &ihost->sm;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ihost->scic_lock, flags);

	अगर (पंचांगr->cancel)
		जाओ करोne;

	अगर (sm->current_state_id == SCIC_STARTING)
		sci_controller_transition_to_पढ़ोy(ihost, SCI_FAILURE_TIMEOUT);
	अन्यथा अगर (sm->current_state_id == SCIC_STOPPING) अणु
		sci_change_state(sm, SCIC_FAILED);
		isci_host_stop_complete(ihost);
	पूर्ण अन्यथा	/* / @toकरो Now what करो we want to करो in this हाल? */
		dev_err(&ihost->pdev->dev,
			"%s: Controller timer fired when controller was not "
			"in a state being timed.\n",
			__func__);

करोne:
	spin_unlock_irqrestore(&ihost->scic_lock, flags);
पूर्ण

अटल क्रमागत sci_status sci_controller_स्थिरruct(काष्ठा isci_host *ihost,
						व्योम __iomem *scu_base,
						व्योम __iomem *smu_base)
अणु
	u8 i;

	sci_init_sm(&ihost->sm, sci_controller_state_table, SCIC_INITIAL);

	ihost->scu_रेजिस्टरs = scu_base;
	ihost->smu_रेजिस्टरs = smu_base;

	sci_port_configuration_agent_स्थिरruct(&ihost->port_agent);

	/* Conकाष्ठा the ports क्रम this controller */
	क्रम (i = 0; i < SCI_MAX_PORTS; i++)
		sci_port_स्थिरruct(&ihost->ports[i], i, ihost);
	sci_port_स्थिरruct(&ihost->ports[i], SCIC_SDS_DUMMY_PORT, ihost);

	/* Conकाष्ठा the phys क्रम this controller */
	क्रम (i = 0; i < SCI_MAX_PHYS; i++) अणु
		/* Add all the PHYs to the dummy port */
		sci_phy_स्थिरruct(&ihost->phys[i],
				  &ihost->ports[SCI_MAX_PORTS], i);
	पूर्ण

	ihost->invalid_phy_mask = 0;

	sci_init_समयr(&ihost->समयr, controller_समयout);

	वापस sci_controller_reset(ihost);
पूर्ण

पूर्णांक sci_oem_parameters_validate(काष्ठा sci_oem_params *oem, u8 version)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SCI_MAX_PORTS; i++)
		अगर (oem->ports[i].phy_mask > SCIC_SDS_PARM_PHY_MASK_MAX)
			वापस -EINVAL;

	क्रम (i = 0; i < SCI_MAX_PHYS; i++)
		अगर (oem->phys[i].sas_address.high == 0 &&
		    oem->phys[i].sas_address.low == 0)
			वापस -EINVAL;

	अगर (oem->controller.mode_type == SCIC_PORT_AUTOMATIC_CONFIGURATION_MODE) अणु
		क्रम (i = 0; i < SCI_MAX_PHYS; i++)
			अगर (oem->ports[i].phy_mask != 0)
				वापस -EINVAL;
	पूर्ण अन्यथा अगर (oem->controller.mode_type == SCIC_PORT_MANUAL_CONFIGURATION_MODE) अणु
		u8 phy_mask = 0;

		क्रम (i = 0; i < SCI_MAX_PHYS; i++)
			phy_mask |= oem->ports[i].phy_mask;

		अगर (phy_mask == 0)
			वापस -EINVAL;
	पूर्ण अन्यथा
		वापस -EINVAL;

	अगर (oem->controller.max_concurr_spin_up > MAX_CONCURRENT_DEVICE_SPIN_UP_COUNT ||
	    oem->controller.max_concurr_spin_up < 1)
		वापस -EINVAL;

	अगर (oem->controller.करो_enable_ssc) अणु
		अगर (version < ISCI_ROM_VER_1_1 && oem->controller.करो_enable_ssc != 1)
			वापस -EINVAL;

		अगर (version >= ISCI_ROM_VER_1_1) अणु
			u8 test = oem->controller.ssc_sata_tx_spपढ़ो_level;

			चयन (test) अणु
			हाल 0:
			हाल 2:
			हाल 3:
			हाल 6:
			हाल 7:
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण

			test = oem->controller.ssc_sas_tx_spपढ़ो_level;
			अगर (oem->controller.ssc_sas_tx_type == 0) अणु
				चयन (test) अणु
				हाल 0:
				हाल 2:
				हाल 3:
					अवरोध;
				शेष:
					वापस -EINVAL;
				पूर्ण
			पूर्ण अन्यथा अगर (oem->controller.ssc_sas_tx_type == 1) अणु
				चयन (test) अणु
				हाल 0:
				हाल 3:
				हाल 6:
					अवरोध;
				शेष:
					वापस -EINVAL;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 max_spin_up(काष्ठा isci_host *ihost)
अणु
	अगर (ihost->user_parameters.max_concurr_spinup)
		वापस min_t(u8, ihost->user_parameters.max_concurr_spinup,
			     MAX_CONCURRENT_DEVICE_SPIN_UP_COUNT);
	अन्यथा
		वापस min_t(u8, ihost->oem_parameters.controller.max_concurr_spin_up,
			     MAX_CONCURRENT_DEVICE_SPIN_UP_COUNT);
पूर्ण

अटल व्योम घातer_control_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा sci_समयr *पंचांगr = from_समयr(पंचांगr, t, समयr);
	काष्ठा isci_host *ihost = container_of(पंचांगr, typeof(*ihost), घातer_control.समयr);
	काष्ठा isci_phy *iphy;
	अचिन्हित दीर्घ flags;
	u8 i;

	spin_lock_irqsave(&ihost->scic_lock, flags);

	अगर (पंचांगr->cancel)
		जाओ करोne;

	ihost->घातer_control.phys_granted_घातer = 0;

	अगर (ihost->घातer_control.phys_रुकोing == 0) अणु
		ihost->घातer_control.समयr_started = false;
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < SCI_MAX_PHYS; i++) अणु

		अगर (ihost->घातer_control.phys_रुकोing == 0)
			अवरोध;

		iphy = ihost->घातer_control.requesters[i];
		अगर (iphy == शून्य)
			जारी;

		अगर (ihost->घातer_control.phys_granted_घातer >= max_spin_up(ihost))
			अवरोध;

		ihost->घातer_control.requesters[i] = शून्य;
		ihost->घातer_control.phys_रुकोing--;
		ihost->घातer_control.phys_granted_घातer++;
		sci_phy_consume_घातer_handler(iphy);

		अगर (iphy->protocol == SAS_PROTOCOL_SSP) अणु
			u8 j;

			क्रम (j = 0; j < SCI_MAX_PHYS; j++) अणु
				काष्ठा isci_phy *requester = ihost->घातer_control.requesters[j];

				/*
				 * Search the घातer_control queue to see अगर there are other phys
				 * attached to the same remote device. If found, take all of
				 * them out of aरुको_sas_घातer state.
				 */
				अगर (requester != शून्य && requester != iphy) अणु
					u8 other = स_भेद(requester->frame_rcvd.iaf.sas_addr,
							  iphy->frame_rcvd.iaf.sas_addr,
							  माप(requester->frame_rcvd.iaf.sas_addr));

					अगर (other == 0) अणु
						ihost->घातer_control.requesters[j] = शून्य;
						ihost->घातer_control.phys_रुकोing--;
						sci_phy_consume_घातer_handler(requester);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * It करोesn't matter अगर the घातer list is empty, we need to start the
	 * समयr in हाल another phy becomes पढ़ोy.
	 */
	sci_mod_समयr(पंचांगr, SCIC_SDS_CONTROLLER_POWER_CONTROL_INTERVAL);
	ihost->घातer_control.समयr_started = true;

करोne:
	spin_unlock_irqrestore(&ihost->scic_lock, flags);
पूर्ण

व्योम sci_controller_घातer_control_queue_insert(काष्ठा isci_host *ihost,
					       काष्ठा isci_phy *iphy)
अणु
	BUG_ON(iphy == शून्य);

	अगर (ihost->घातer_control.phys_granted_घातer < max_spin_up(ihost)) अणु
		ihost->घातer_control.phys_granted_घातer++;
		sci_phy_consume_घातer_handler(iphy);

		/*
		 * stop and start the घातer_control समयr. When the समयr fires, the
		 * no_of_phys_granted_घातer will be set to 0
		 */
		अगर (ihost->घातer_control.समयr_started)
			sci_del_समयr(&ihost->घातer_control.समयr);

		sci_mod_समयr(&ihost->घातer_control.समयr,
				 SCIC_SDS_CONTROLLER_POWER_CONTROL_INTERVAL);
		ihost->घातer_control.समयr_started = true;

	पूर्ण अन्यथा अणु
		/*
		 * There are phys, attached to the same sas address as this phy, are
		 * alपढ़ोy in READY state, this phy करोn't need रुको.
		 */
		u8 i;
		काष्ठा isci_phy *current_phy;

		क्रम (i = 0; i < SCI_MAX_PHYS; i++) अणु
			u8 other;
			current_phy = &ihost->phys[i];

			other = स_भेद(current_phy->frame_rcvd.iaf.sas_addr,
				       iphy->frame_rcvd.iaf.sas_addr,
				       माप(current_phy->frame_rcvd.iaf.sas_addr));

			अगर (current_phy->sm.current_state_id == SCI_PHY_READY &&
			    current_phy->protocol == SAS_PROTOCOL_SSP &&
			    other == 0) अणु
				sci_phy_consume_घातer_handler(iphy);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == SCI_MAX_PHYS) अणु
			/* Add the phy in the रुकोing list */
			ihost->घातer_control.requesters[iphy->phy_index] = iphy;
			ihost->घातer_control.phys_रुकोing++;
		पूर्ण
	पूर्ण
पूर्ण

व्योम sci_controller_घातer_control_queue_हटाओ(काष्ठा isci_host *ihost,
					       काष्ठा isci_phy *iphy)
अणु
	BUG_ON(iphy == शून्य);

	अगर (ihost->घातer_control.requesters[iphy->phy_index])
		ihost->घातer_control.phys_रुकोing--;

	ihost->घातer_control.requesters[iphy->phy_index] = शून्य;
पूर्ण

अटल पूर्णांक is_दीर्घ_cable(पूर्णांक phy, अचिन्हित अक्षर selection_byte)
अणु
	वापस !!(selection_byte & (1 << phy));
पूर्ण

अटल पूर्णांक is_medium_cable(पूर्णांक phy, अचिन्हित अक्षर selection_byte)
अणु
	वापस !!(selection_byte & (1 << (phy + 4)));
पूर्ण

अटल क्रमागत cable_selections decode_selection_byte(
	पूर्णांक phy,
	अचिन्हित अक्षर selection_byte)
अणु
	वापस ((selection_byte & (1 << phy)) ? 1 : 0)
		+ (selection_byte & (1 << (phy + 4)) ? 2 : 0);
पूर्ण

अटल अचिन्हित अक्षर *to_cable_select(काष्ठा isci_host *ihost)
अणु
	अगर (is_cable_select_overridden())
		वापस ((अचिन्हित अक्षर *)&cable_selection_override)
			+ ihost->id;
	अन्यथा
		वापस &ihost->oem_parameters.controller.cable_selection_mask;
पूर्ण

क्रमागत cable_selections decode_cable_selection(काष्ठा isci_host *ihost, पूर्णांक phy)
अणु
	वापस decode_selection_byte(phy, *to_cable_select(ihost));
पूर्ण

अक्षर *lookup_cable_names(क्रमागत cable_selections selection)
अणु
	अटल अक्षर *cable_names[] = अणु
		[लघु_cable]     = "short",
		[दीर्घ_cable]      = "long",
		[medium_cable]    = "medium",
		[undefined_cable] = "<undefined, assumed long>" /* bit 0==1 */
	पूर्ण;
	वापस (selection <= undefined_cable) ? cable_names[selection]
					      : cable_names[undefined_cable];
पूर्ण

#घोषणा AFE_REGISTER_WRITE_DELAY 10

अटल व्योम sci_controller_afe_initialization(काष्ठा isci_host *ihost)
अणु
	काष्ठा scu_afe_रेजिस्टरs __iomem *afe = &ihost->scu_रेजिस्टरs->afe;
	स्थिर काष्ठा sci_oem_params *oem = &ihost->oem_parameters;
	काष्ठा pci_dev *pdev = ihost->pdev;
	u32 afe_status;
	u32 phy_id;
	अचिन्हित अक्षर cable_selection_mask = *to_cable_select(ihost);

	/* Clear DFX Status रेजिस्टरs */
	ग_लिखोl(0x0081000f, &afe->afe_dfx_master_control0);
	udelay(AFE_REGISTER_WRITE_DELAY);

	अगर (is_b0(pdev) || is_c0(pdev) || is_c1(pdev)) अणु
		/* PM Rx Equalization Save, PM SPhy Rx Acknowledgement
		 * Timer, PM Stagger Timer
		 */
		ग_लिखोl(0x0007FFFF, &afe->afe_pmsn_master_control2);
		udelay(AFE_REGISTER_WRITE_DELAY);
	पूर्ण

	/* Configure bias currents to normal */
	अगर (is_a2(pdev))
		ग_लिखोl(0x00005A00, &afe->afe_bias_control);
	अन्यथा अगर (is_b0(pdev) || is_c0(pdev))
		ग_लिखोl(0x00005F00, &afe->afe_bias_control);
	अन्यथा अगर (is_c1(pdev))
		ग_लिखोl(0x00005500, &afe->afe_bias_control);

	udelay(AFE_REGISTER_WRITE_DELAY);

	/* Enable PLL */
	अगर (is_a2(pdev))
		ग_लिखोl(0x80040908, &afe->afe_pll_control0);
	अन्यथा अगर (is_b0(pdev) || is_c0(pdev))
		ग_लिखोl(0x80040A08, &afe->afe_pll_control0);
	अन्यथा अगर (is_c1(pdev)) अणु
		ग_लिखोl(0x80000B08, &afe->afe_pll_control0);
		udelay(AFE_REGISTER_WRITE_DELAY);
		ग_लिखोl(0x00000B08, &afe->afe_pll_control0);
		udelay(AFE_REGISTER_WRITE_DELAY);
		ग_लिखोl(0x80000B08, &afe->afe_pll_control0);
	पूर्ण

	udelay(AFE_REGISTER_WRITE_DELAY);

	/* Wait क्रम the PLL to lock */
	करो अणु
		afe_status = पढ़ोl(&afe->afe_common_block_status);
		udelay(AFE_REGISTER_WRITE_DELAY);
	पूर्ण जबतक ((afe_status & 0x00001000) == 0);

	अगर (is_a2(pdev)) अणु
		/* Shorten SAS SNW lock समय (RxLock समयr value from 76
		 * us to 50 us)
		 */
		ग_लिखोl(0x7bcc96ad, &afe->afe_pmsn_master_control0);
		udelay(AFE_REGISTER_WRITE_DELAY);
	पूर्ण

	क्रम (phy_id = 0; phy_id < SCI_MAX_PHYS; phy_id++) अणु
		काष्ठा scu_afe_transceiver __iomem *xcvr = &afe->scu_afe_xcvr[phy_id];
		स्थिर काष्ठा sci_phy_oem_params *oem_phy = &oem->phys[phy_id];
		पूर्णांक cable_length_दीर्घ =
			is_दीर्घ_cable(phy_id, cable_selection_mask);
		पूर्णांक cable_length_medium =
			is_medium_cable(phy_id, cable_selection_mask);

		अगर (is_a2(pdev)) अणु
			/* All शेषs, except the Receive Word
			 * Alignament/Comma Detect Enable....(0xe800)
			 */
			ग_लिखोl(0x00004512, &xcvr->afe_xcvr_control0);
			udelay(AFE_REGISTER_WRITE_DELAY);

			ग_लिखोl(0x0050100F, &xcvr->afe_xcvr_control1);
			udelay(AFE_REGISTER_WRITE_DELAY);
		पूर्ण अन्यथा अगर (is_b0(pdev)) अणु
			/* Configure transmitter SSC parameters */
			ग_लिखोl(0x00030000, &xcvr->afe_tx_ssc_control);
			udelay(AFE_REGISTER_WRITE_DELAY);
		पूर्ण अन्यथा अगर (is_c0(pdev)) अणु
			/* Configure transmitter SSC parameters */
			ग_लिखोl(0x00010202, &xcvr->afe_tx_ssc_control);
			udelay(AFE_REGISTER_WRITE_DELAY);

			/* All शेषs, except the Receive Word
			 * Alignament/Comma Detect Enable....(0xe800)
			 */
			ग_लिखोl(0x00014500, &xcvr->afe_xcvr_control0);
			udelay(AFE_REGISTER_WRITE_DELAY);
		पूर्ण अन्यथा अगर (is_c1(pdev)) अणु
			/* Configure transmitter SSC parameters */
			ग_लिखोl(0x00010202, &xcvr->afe_tx_ssc_control);
			udelay(AFE_REGISTER_WRITE_DELAY);

			/* All शेषs, except the Receive Word
			 * Alignament/Comma Detect Enable....(0xe800)
			 */
			ग_लिखोl(0x0001C500, &xcvr->afe_xcvr_control0);
			udelay(AFE_REGISTER_WRITE_DELAY);
		पूर्ण

		/* Power up TX and RX out from घातer करोwn (PWRDNTX and
		 * PWRDNRX) & increase TX पूर्णांक & ext bias 20%....(0xe85c)
		 */
		अगर (is_a2(pdev))
			ग_लिखोl(0x000003F0, &xcvr->afe_channel_control);
		अन्यथा अगर (is_b0(pdev)) अणु
			ग_लिखोl(0x000003D7, &xcvr->afe_channel_control);
			udelay(AFE_REGISTER_WRITE_DELAY);

			ग_लिखोl(0x000003D4, &xcvr->afe_channel_control);
		पूर्ण अन्यथा अगर (is_c0(pdev)) अणु
			ग_लिखोl(0x000001E7, &xcvr->afe_channel_control);
			udelay(AFE_REGISTER_WRITE_DELAY);

			ग_लिखोl(0x000001E4, &xcvr->afe_channel_control);
		पूर्ण अन्यथा अगर (is_c1(pdev)) अणु
			ग_लिखोl(cable_length_दीर्घ ? 0x000002F7 : 0x000001F7,
			       &xcvr->afe_channel_control);
			udelay(AFE_REGISTER_WRITE_DELAY);

			ग_लिखोl(cable_length_दीर्घ ? 0x000002F4 : 0x000001F4,
			       &xcvr->afe_channel_control);
		पूर्ण
		udelay(AFE_REGISTER_WRITE_DELAY);

		अगर (is_a2(pdev)) अणु
			/* Enable TX equalization (0xe824) */
			ग_लिखोl(0x00040000, &xcvr->afe_tx_control);
			udelay(AFE_REGISTER_WRITE_DELAY);
		पूर्ण

		अगर (is_a2(pdev) || is_b0(pdev))
			/* RDPI=0x0(RX Power On), RXOOBDETPDNC=0x0,
			 * TPD=0x0(TX Power On), RDD=0x0(RX Detect
			 * Enabled) ....(0xe800)
			 */
			ग_लिखोl(0x00004100, &xcvr->afe_xcvr_control0);
		अन्यथा अगर (is_c0(pdev))
			ग_लिखोl(0x00014100, &xcvr->afe_xcvr_control0);
		अन्यथा अगर (is_c1(pdev))
			ग_लिखोl(0x0001C100, &xcvr->afe_xcvr_control0);
		udelay(AFE_REGISTER_WRITE_DELAY);

		/* Leave DFE/FFE on */
		अगर (is_a2(pdev))
			ग_लिखोl(0x3F11103F, &xcvr->afe_rx_ssc_control0);
		अन्यथा अगर (is_b0(pdev)) अणु
			ग_लिखोl(0x3F11103F, &xcvr->afe_rx_ssc_control0);
			udelay(AFE_REGISTER_WRITE_DELAY);
			/* Enable TX equalization (0xe824) */
			ग_लिखोl(0x00040000, &xcvr->afe_tx_control);
		पूर्ण अन्यथा अगर (is_c0(pdev)) अणु
			ग_लिखोl(0x01400C0F, &xcvr->afe_rx_ssc_control1);
			udelay(AFE_REGISTER_WRITE_DELAY);

			ग_लिखोl(0x3F6F103F, &xcvr->afe_rx_ssc_control0);
			udelay(AFE_REGISTER_WRITE_DELAY);

			/* Enable TX equalization (0xe824) */
			ग_लिखोl(0x00040000, &xcvr->afe_tx_control);
		पूर्ण अन्यथा अगर (is_c1(pdev)) अणु
			ग_लिखोl(cable_length_दीर्घ ? 0x01500C0C :
			       cable_length_medium ? 0x01400C0D : 0x02400C0D,
			       &xcvr->afe_xcvr_control1);
			udelay(AFE_REGISTER_WRITE_DELAY);

			ग_लिखोl(0x000003E0, &xcvr->afe_dfx_rx_control1);
			udelay(AFE_REGISTER_WRITE_DELAY);

			ग_लिखोl(cable_length_दीर्घ ? 0x33091C1F :
			       cable_length_medium ? 0x3315181F : 0x2B17161F,
			       &xcvr->afe_rx_ssc_control0);
			udelay(AFE_REGISTER_WRITE_DELAY);

			/* Enable TX equalization (0xe824) */
			ग_लिखोl(0x00040000, &xcvr->afe_tx_control);
		पूर्ण

		udelay(AFE_REGISTER_WRITE_DELAY);

		ग_लिखोl(oem_phy->afe_tx_amp_control0, &xcvr->afe_tx_amp_control0);
		udelay(AFE_REGISTER_WRITE_DELAY);

		ग_लिखोl(oem_phy->afe_tx_amp_control1, &xcvr->afe_tx_amp_control1);
		udelay(AFE_REGISTER_WRITE_DELAY);

		ग_लिखोl(oem_phy->afe_tx_amp_control2, &xcvr->afe_tx_amp_control2);
		udelay(AFE_REGISTER_WRITE_DELAY);

		ग_लिखोl(oem_phy->afe_tx_amp_control3, &xcvr->afe_tx_amp_control3);
		udelay(AFE_REGISTER_WRITE_DELAY);
	पूर्ण

	/* Transfer control to the PEs */
	ग_लिखोl(0x00010f00, &afe->afe_dfx_master_control0);
	udelay(AFE_REGISTER_WRITE_DELAY);
पूर्ण

अटल व्योम sci_controller_initialize_घातer_control(काष्ठा isci_host *ihost)
अणु
	sci_init_समयr(&ihost->घातer_control.समयr, घातer_control_समयout);

	स_रखो(ihost->घातer_control.requesters, 0,
	       माप(ihost->घातer_control.requesters));

	ihost->घातer_control.phys_रुकोing = 0;
	ihost->घातer_control.phys_granted_घातer = 0;
पूर्ण

अटल क्रमागत sci_status sci_controller_initialize(काष्ठा isci_host *ihost)
अणु
	काष्ठा sci_base_state_machine *sm = &ihost->sm;
	क्रमागत sci_status result = SCI_FAILURE;
	अचिन्हित दीर्घ i, state, val;

	अगर (ihost->sm.current_state_id != SCIC_RESET) अणु
		dev_warn(&ihost->pdev->dev, "%s invalid state: %d\n",
			 __func__, ihost->sm.current_state_id);
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	sci_change_state(sm, SCIC_INITIALIZING);

	sci_init_समयr(&ihost->phy_समयr, phy_startup_समयout);

	ihost->next_phy_to_start = 0;
	ihost->phy_startup_समयr_pending = false;

	sci_controller_initialize_घातer_control(ihost);

	/*
	 * There is nothing to करो here क्रम B0 since we करो not have to
	 * program the AFE रेजिस्टरs.
	 * / @toकरो The AFE settings are supposed to be correct क्रम the B0 but
	 * /       presently they seem to be wrong. */
	sci_controller_afe_initialization(ihost);


	/* Take the hardware out of reset */
	ग_लिखोl(0, &ihost->smu_रेजिस्टरs->soft_reset_control);

	/*
	 * / @toकरो Provide meaningfull error code क्रम hardware failure
	 * result = SCI_FAILURE_CONTROLLER_HARDWARE; */
	क्रम (i = 100; i >= 1; i--) अणु
		u32 status;

		/* Loop until the hardware reports success */
		udelay(SCU_CONTEXT_RAM_INIT_STALL_TIME);
		status = पढ़ोl(&ihost->smu_रेजिस्टरs->control_status);

		अगर ((status & SCU_RAM_INIT_COMPLETED) == SCU_RAM_INIT_COMPLETED)
			अवरोध;
	पूर्ण
	अगर (i == 0)
		जाओ out;

	/*
	 * Determine what are the actaul device capacities that the
	 * hardware will support */
	val = पढ़ोl(&ihost->smu_रेजिस्टरs->device_context_capacity);

	/* Record the smaller of the two capacity values */
	ihost->logical_port_entries = min(smu_max_ports(val), SCI_MAX_PORTS);
	ihost->task_context_entries = min(smu_max_task_contexts(val), SCI_MAX_IO_REQUESTS);
	ihost->remote_node_entries = min(smu_max_rncs(val), SCI_MAX_REMOTE_DEVICES);

	/*
	 * Make all PEs that are unasचिन्हित match up with the
	 * logical ports
	 */
	क्रम (i = 0; i < ihost->logical_port_entries; i++) अणु
		काष्ठा scu_port_task_scheduler_group_रेजिस्टरs __iomem
			*ptsg = &ihost->scu_रेजिस्टरs->peg0.ptsg;

		ग_लिखोl(i, &ptsg->protocol_engine[i]);
	पूर्ण

	/* Initialize hardware PCI Relaxed ordering in DMA engines */
	val = पढ़ोl(&ihost->scu_रेजिस्टरs->sdma.pdma_configuration);
	val |= SCU_PDMACR_GEN_BIT(PCI_RELAXED_ORDERING_ENABLE);
	ग_लिखोl(val, &ihost->scu_रेजिस्टरs->sdma.pdma_configuration);

	val = पढ़ोl(&ihost->scu_रेजिस्टरs->sdma.cdma_configuration);
	val |= SCU_CDMACR_GEN_BIT(PCI_RELAXED_ORDERING_ENABLE);
	ग_लिखोl(val, &ihost->scu_रेजिस्टरs->sdma.cdma_configuration);

	/*
	 * Initialize the PHYs beक्रमe the PORTs because the PHY रेजिस्टरs
	 * are accessed during the port initialization.
	 */
	क्रम (i = 0; i < SCI_MAX_PHYS; i++) अणु
		result = sci_phy_initialize(&ihost->phys[i],
					    &ihost->scu_रेजिस्टरs->peg0.pe[i].tl,
					    &ihost->scu_रेजिस्टरs->peg0.pe[i].ll);
		अगर (result != SCI_SUCCESS)
			जाओ out;
	पूर्ण

	क्रम (i = 0; i < ihost->logical_port_entries; i++) अणु
		काष्ठा isci_port *iport = &ihost->ports[i];

		iport->port_task_scheduler_रेजिस्टरs = &ihost->scu_रेजिस्टरs->peg0.ptsg.port[i];
		iport->port_pe_configuration_रेजिस्टर = &ihost->scu_रेजिस्टरs->peg0.ptsg.protocol_engine[0];
		iport->viit_रेजिस्टरs = &ihost->scu_रेजिस्टरs->peg0.viit[i];
	पूर्ण

	result = sci_port_configuration_agent_initialize(ihost, &ihost->port_agent);

 out:
	/* Advance the controller state machine */
	अगर (result == SCI_SUCCESS)
		state = SCIC_INITIALIZED;
	अन्यथा
		state = SCIC_FAILED;
	sci_change_state(sm, state);

	वापस result;
पूर्ण

अटल पूर्णांक sci_controller_dma_alloc(काष्ठा isci_host *ihost)
अणु
	काष्ठा device *dev = &ihost->pdev->dev;
	माप_प्रकार size;
	पूर्णांक i;

	/* detect re-initialization */
	अगर (ihost->completion_queue)
		वापस 0;

	size = SCU_MAX_COMPLETION_QUEUE_ENTRIES * माप(u32);
	ihost->completion_queue = dmam_alloc_coherent(dev, size, &ihost->cq_dma,
						      GFP_KERNEL);
	अगर (!ihost->completion_queue)
		वापस -ENOMEM;

	size = ihost->remote_node_entries * माप(जोड़ scu_remote_node_context);
	ihost->remote_node_context_table = dmam_alloc_coherent(dev, size, &ihost->rnc_dma,
							       GFP_KERNEL);

	अगर (!ihost->remote_node_context_table)
		वापस -ENOMEM;

	size = ihost->task_context_entries * माप(काष्ठा scu_task_context),
	ihost->task_context_table = dmam_alloc_coherent(dev, size, &ihost->tc_dma,
							GFP_KERNEL);
	अगर (!ihost->task_context_table)
		वापस -ENOMEM;

	size = SCI_UFI_TOTAL_SIZE;
	ihost->ufi_buf = dmam_alloc_coherent(dev, size, &ihost->ufi_dma, GFP_KERNEL);
	अगर (!ihost->ufi_buf)
		वापस -ENOMEM;

	क्रम (i = 0; i < SCI_MAX_IO_REQUESTS; i++) अणु
		काष्ठा isci_request *ireq;
		dma_addr_t dma;

		ireq = dmam_alloc_coherent(dev, माप(*ireq), &dma, GFP_KERNEL);
		अगर (!ireq)
			वापस -ENOMEM;

		ireq->tc = &ihost->task_context_table[i];
		ireq->owning_controller = ihost;
		ireq->request_daddr = dma;
		ireq->isci_host = ihost;
		ihost->reqs[i] = ireq;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sci_controller_mem_init(काष्ठा isci_host *ihost)
अणु
	पूर्णांक err = sci_controller_dma_alloc(ihost);

	अगर (err)
		वापस err;

	ग_लिखोl(lower_32_bits(ihost->cq_dma), &ihost->smu_रेजिस्टरs->completion_queue_lower);
	ग_लिखोl(upper_32_bits(ihost->cq_dma), &ihost->smu_रेजिस्टरs->completion_queue_upper);

	ग_लिखोl(lower_32_bits(ihost->rnc_dma), &ihost->smu_रेजिस्टरs->remote_node_context_lower);
	ग_लिखोl(upper_32_bits(ihost->rnc_dma), &ihost->smu_रेजिस्टरs->remote_node_context_upper);

	ग_लिखोl(lower_32_bits(ihost->tc_dma), &ihost->smu_रेजिस्टरs->host_task_table_lower);
	ग_लिखोl(upper_32_bits(ihost->tc_dma), &ihost->smu_रेजिस्टरs->host_task_table_upper);

	sci_unsolicited_frame_control_स्थिरruct(ihost);

	/*
	 * Inक्रमm the silicon as to the location of the UF headers and
	 * address table.
	 */
	ग_लिखोl(lower_32_bits(ihost->uf_control.headers.physical_address),
		&ihost->scu_रेजिस्टरs->sdma.uf_header_base_address_lower);
	ग_लिखोl(upper_32_bits(ihost->uf_control.headers.physical_address),
		&ihost->scu_रेजिस्टरs->sdma.uf_header_base_address_upper);

	ग_लिखोl(lower_32_bits(ihost->uf_control.address_table.physical_address),
		&ihost->scu_रेजिस्टरs->sdma.uf_address_table_lower);
	ग_लिखोl(upper_32_bits(ihost->uf_control.address_table.physical_address),
		&ihost->scu_रेजिस्टरs->sdma.uf_address_table_upper);

	वापस 0;
पूर्ण

/**
 * isci_host_init - (re-)initialize hardware and पूर्णांकernal (निजी) state
 * @ihost: host to init
 *
 * Any खुला facing objects (like asd_sas_port, and asd_sas_phys), or
 * one-समय initialization objects like locks and रुकोqueues, are
 * not touched (they are initialized in isci_host_alloc)
 */
पूर्णांक isci_host_init(काष्ठा isci_host *ihost)
अणु
	पूर्णांक i, err;
	क्रमागत sci_status status;

	spin_lock_irq(&ihost->scic_lock);
	status = sci_controller_स्थिरruct(ihost, scu_base(ihost), smu_base(ihost));
	spin_unlock_irq(&ihost->scic_lock);
	अगर (status != SCI_SUCCESS) अणु
		dev_err(&ihost->pdev->dev,
			"%s: sci_controller_construct failed - status = %x\n",
			__func__,
			status);
		वापस -ENODEV;
	पूर्ण

	spin_lock_irq(&ihost->scic_lock);
	status = sci_controller_initialize(ihost);
	spin_unlock_irq(&ihost->scic_lock);
	अगर (status != SCI_SUCCESS) अणु
		dev_warn(&ihost->pdev->dev,
			 "%s: sci_controller_initialize failed -"
			 " status = 0x%x\n",
			 __func__, status);
		वापस -ENODEV;
	पूर्ण

	err = sci_controller_mem_init(ihost);
	अगर (err)
		वापस err;

	/* enable sgpio */
	ग_लिखोl(1, &ihost->scu_रेजिस्टरs->peg0.sgpio.पूर्णांकerface_control);
	क्रम (i = 0; i < isci_gpio_count(ihost); i++)
		ग_लिखोl(SGPIO_HW_CONTROL, &ihost->scu_रेजिस्टरs->peg0.sgpio.output_data_select[i]);
	ग_लिखोl(0, &ihost->scu_रेजिस्टरs->peg0.sgpio.venकरोr_specअगरic_code);

	वापस 0;
पूर्ण

व्योम sci_controller_link_up(काष्ठा isci_host *ihost, काष्ठा isci_port *iport,
			    काष्ठा isci_phy *iphy)
अणु
	चयन (ihost->sm.current_state_id) अणु
	हाल SCIC_STARTING:
		sci_del_समयr(&ihost->phy_समयr);
		ihost->phy_startup_समयr_pending = false;
		ihost->port_agent.link_up_handler(ihost, &ihost->port_agent,
						  iport, iphy);
		sci_controller_start_next_phy(ihost);
		अवरोध;
	हाल SCIC_READY:
		ihost->port_agent.link_up_handler(ihost, &ihost->port_agent,
						  iport, iphy);
		अवरोध;
	शेष:
		dev_dbg(&ihost->pdev->dev,
			"%s: SCIC Controller linkup event from phy %d in "
			"unexpected state %d\n", __func__, iphy->phy_index,
			ihost->sm.current_state_id);
	पूर्ण
पूर्ण

व्योम sci_controller_link_करोwn(काष्ठा isci_host *ihost, काष्ठा isci_port *iport,
			      काष्ठा isci_phy *iphy)
अणु
	चयन (ihost->sm.current_state_id) अणु
	हाल SCIC_STARTING:
	हाल SCIC_READY:
		ihost->port_agent.link_करोwn_handler(ihost, &ihost->port_agent,
						   iport, iphy);
		अवरोध;
	शेष:
		dev_dbg(&ihost->pdev->dev,
			"%s: SCIC Controller linkdown event from phy %d in "
			"unexpected state %d\n",
			__func__,
			iphy->phy_index,
			ihost->sm.current_state_id);
	पूर्ण
पूर्ण

bool sci_controller_has_remote_devices_stopping(काष्ठा isci_host *ihost)
अणु
	u32 index;

	क्रम (index = 0; index < ihost->remote_node_entries; index++) अणु
		अगर ((ihost->device_table[index] != शून्य) &&
		   (ihost->device_table[index]->sm.current_state_id == SCI_DEV_STOPPING))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम sci_controller_remote_device_stopped(काष्ठा isci_host *ihost,
					  काष्ठा isci_remote_device *idev)
अणु
	अगर (ihost->sm.current_state_id != SCIC_STOPPING) अणु
		dev_dbg(&ihost->pdev->dev,
			"SCIC Controller 0x%p remote device stopped event "
			"from device 0x%p in unexpected state %d\n",
			ihost, idev,
			ihost->sm.current_state_id);
		वापस;
	पूर्ण

	अगर (!sci_controller_has_remote_devices_stopping(ihost))
		isci_host_stop_complete(ihost);
पूर्ण

व्योम sci_controller_post_request(काष्ठा isci_host *ihost, u32 request)
अणु
	dev_dbg(&ihost->pdev->dev, "%s[%d]: %#x\n",
		__func__, ihost->id, request);

	ग_लिखोl(request, &ihost->smu_रेजिस्टरs->post_context_port);
पूर्ण

काष्ठा isci_request *sci_request_by_tag(काष्ठा isci_host *ihost, u16 io_tag)
अणु
	u16 task_index;
	u16 task_sequence;

	task_index = ISCI_TAG_TCI(io_tag);

	अगर (task_index < ihost->task_context_entries) अणु
		काष्ठा isci_request *ireq = ihost->reqs[task_index];

		अगर (test_bit(IREQ_ACTIVE, &ireq->flags)) अणु
			task_sequence = ISCI_TAG_SEQ(io_tag);

			अगर (task_sequence == ihost->io_request_sequence[task_index])
				वापस ireq;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * sci_controller_allocate_remote_node_context()
 * This method allocates remote node index and the reserves the remote node
 *    context space क्रम use. This method can fail अगर there are no more remote
 *    node index available.
 * @ihost: This is the controller object which contains the set of
 *    मुक्त remote node ids
 * @idev: This is the device object which is requesting the a remote node
 *    id
 * @node_id: This is the remote node id that is assinged to the device अगर one
 *    is available
 *
 * क्रमागत sci_status SCI_FAILURE_OUT_OF_RESOURCES अगर there are no available remote
 * node index available.
 */
क्रमागत sci_status sci_controller_allocate_remote_node_context(काष्ठा isci_host *ihost,
							    काष्ठा isci_remote_device *idev,
							    u16 *node_id)
अणु
	u16 node_index;
	u32 remote_node_count = sci_remote_device_node_count(idev);

	node_index = sci_remote_node_table_allocate_remote_node(
		&ihost->available_remote_nodes, remote_node_count
		);

	अगर (node_index != SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX) अणु
		ihost->device_table[node_index] = idev;

		*node_id = node_index;

		वापस SCI_SUCCESS;
	पूर्ण

	वापस SCI_FAILURE_INSUFFICIENT_RESOURCES;
पूर्ण

व्योम sci_controller_मुक्त_remote_node_context(काष्ठा isci_host *ihost,
					     काष्ठा isci_remote_device *idev,
					     u16 node_id)
अणु
	u32 remote_node_count = sci_remote_device_node_count(idev);

	अगर (ihost->device_table[node_id] == idev) अणु
		ihost->device_table[node_id] = शून्य;

		sci_remote_node_table_release_remote_node_index(
			&ihost->available_remote_nodes, remote_node_count, node_id
			);
	पूर्ण
पूर्ण

व्योम sci_controller_copy_sata_response(व्योम *response_buffer,
				       व्योम *frame_header,
				       व्योम *frame_buffer)
अणु
	/* XXX type safety? */
	स_नकल(response_buffer, frame_header, माप(u32));

	स_नकल(response_buffer + माप(u32),
	       frame_buffer,
	       माप(काष्ठा dev_to_host_fis) - माप(u32));
पूर्ण

व्योम sci_controller_release_frame(काष्ठा isci_host *ihost, u32 frame_index)
अणु
	अगर (sci_unsolicited_frame_control_release_frame(&ihost->uf_control, frame_index))
		ग_लिखोl(ihost->uf_control.get,
			&ihost->scu_रेजिस्टरs->sdma.unsolicited_frame_get_poपूर्णांकer);
पूर्ण

व्योम isci_tci_मुक्त(काष्ठा isci_host *ihost, u16 tci)
अणु
	u16 tail = ihost->tci_tail & (SCI_MAX_IO_REQUESTS-1);

	ihost->tci_pool[tail] = tci;
	ihost->tci_tail = tail + 1;
पूर्ण

अटल u16 isci_tci_alloc(काष्ठा isci_host *ihost)
अणु
	u16 head = ihost->tci_head & (SCI_MAX_IO_REQUESTS-1);
	u16 tci = ihost->tci_pool[head];

	ihost->tci_head = head + 1;
	वापस tci;
पूर्ण

अटल u16 isci_tci_space(काष्ठा isci_host *ihost)
अणु
	वापस CIRC_SPACE(ihost->tci_head, ihost->tci_tail, SCI_MAX_IO_REQUESTS);
पूर्ण

u16 isci_alloc_tag(काष्ठा isci_host *ihost)
अणु
	अगर (isci_tci_space(ihost)) अणु
		u16 tci = isci_tci_alloc(ihost);
		u8 seq = ihost->io_request_sequence[tci];

		वापस ISCI_TAG(seq, tci);
	पूर्ण

	वापस SCI_CONTROLLER_INVALID_IO_TAG;
पूर्ण

क्रमागत sci_status isci_मुक्त_tag(काष्ठा isci_host *ihost, u16 io_tag)
अणु
	u16 tci = ISCI_TAG_TCI(io_tag);
	u16 seq = ISCI_TAG_SEQ(io_tag);

	/* prevent tail from passing head */
	अगर (isci_tci_active(ihost) == 0)
		वापस SCI_FAILURE_INVALID_IO_TAG;

	अगर (seq == ihost->io_request_sequence[tci]) अणु
		ihost->io_request_sequence[tci] = (seq+1) & (SCI_MAX_SEQ-1);

		isci_tci_मुक्त(ihost, tci);

		वापस SCI_SUCCESS;
	पूर्ण
	वापस SCI_FAILURE_INVALID_IO_TAG;
पूर्ण

क्रमागत sci_status sci_controller_start_io(काष्ठा isci_host *ihost,
					काष्ठा isci_remote_device *idev,
					काष्ठा isci_request *ireq)
अणु
	क्रमागत sci_status status;

	अगर (ihost->sm.current_state_id != SCIC_READY) अणु
		dev_warn(&ihost->pdev->dev, "%s invalid state: %d\n",
			 __func__, ihost->sm.current_state_id);
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	status = sci_remote_device_start_io(ihost, idev, ireq);
	अगर (status != SCI_SUCCESS)
		वापस status;

	set_bit(IREQ_ACTIVE, &ireq->flags);
	sci_controller_post_request(ihost, ireq->post_context);
	वापस SCI_SUCCESS;
पूर्ण

क्रमागत sci_status sci_controller_terminate_request(काष्ठा isci_host *ihost,
						 काष्ठा isci_remote_device *idev,
						 काष्ठा isci_request *ireq)
अणु
	/* terminate an ongoing (i.e. started) core IO request.  This करोes not
	 * पात the IO request at the target, but rather हटाओs the IO
	 * request from the host controller.
	 */
	क्रमागत sci_status status;

	अगर (ihost->sm.current_state_id != SCIC_READY) अणु
		dev_warn(&ihost->pdev->dev, "%s invalid state: %d\n",
			 __func__, ihost->sm.current_state_id);
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
	status = sci_io_request_terminate(ireq);

	dev_dbg(&ihost->pdev->dev, "%s: status=%d; ireq=%p; flags=%lx\n",
		__func__, status, ireq, ireq->flags);

	अगर ((status == SCI_SUCCESS) &&
	    !test_bit(IREQ_PENDING_ABORT, &ireq->flags) &&
	    !test_and_set_bit(IREQ_TC_ABORT_POSTED, &ireq->flags)) अणु
		/* Utilize the original post context command and or in the
		 * POST_TC_ABORT request sub-type.
		 */
		sci_controller_post_request(
			ihost, ireq->post_context |
				SCU_CONTEXT_COMMAND_REQUEST_POST_TC_ABORT);
	पूर्ण
	वापस status;
पूर्ण

/**
 * sci_controller_complete_io() - This method will perक्रमm core specअगरic
 *    completion operations क्रम an IO request.  After this method is invoked,
 *    the user should consider the IO request as invalid until it is properly
 *    reused (i.e. re-स्थिरructed).
 * @ihost: The handle to the controller object क्रम which to complete the
 *    IO request.
 * @idev: The handle to the remote device object क्रम which to complete
 *    the IO request.
 * @ireq: the handle to the io request object to complete.
 */
क्रमागत sci_status sci_controller_complete_io(काष्ठा isci_host *ihost,
					   काष्ठा isci_remote_device *idev,
					   काष्ठा isci_request *ireq)
अणु
	क्रमागत sci_status status;

	चयन (ihost->sm.current_state_id) अणु
	हाल SCIC_STOPPING:
		/* XXX: Implement this function */
		वापस SCI_FAILURE;
	हाल SCIC_READY:
		status = sci_remote_device_complete_io(ihost, idev, ireq);
		अगर (status != SCI_SUCCESS)
			वापस status;

		clear_bit(IREQ_ACTIVE, &ireq->flags);
		वापस SCI_SUCCESS;
	शेष:
		dev_warn(&ihost->pdev->dev, "%s invalid state: %d\n",
			 __func__, ihost->sm.current_state_id);
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

पूर्ण

क्रमागत sci_status sci_controller_जारी_io(काष्ठा isci_request *ireq)
अणु
	काष्ठा isci_host *ihost = ireq->owning_controller;

	अगर (ihost->sm.current_state_id != SCIC_READY) अणु
		dev_warn(&ihost->pdev->dev, "%s invalid state: %d\n",
			 __func__, ihost->sm.current_state_id);
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	set_bit(IREQ_ACTIVE, &ireq->flags);
	sci_controller_post_request(ihost, ireq->post_context);
	वापस SCI_SUCCESS;
पूर्ण

/**
 * sci_controller_start_task() - This method is called by the SCIC user to
 *    send/start a framework task management request.
 * @ihost: the handle to the controller object क्रम which to start the task
 *    management request.
 * @idev: the handle to the remote device object क्रम which to start
 *    the task management request.
 * @ireq: the handle to the task request object to start.
 */
क्रमागत sci_status sci_controller_start_task(काष्ठा isci_host *ihost,
					  काष्ठा isci_remote_device *idev,
					  काष्ठा isci_request *ireq)
अणु
	क्रमागत sci_status status;

	अगर (ihost->sm.current_state_id != SCIC_READY) अणु
		dev_warn(&ihost->pdev->dev,
			 "%s: SCIC Controller starting task from invalid "
			 "state\n",
			 __func__);
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	status = sci_remote_device_start_task(ihost, idev, ireq);
	चयन (status) अणु
	हाल SCI_FAILURE_RESET_DEVICE_PARTIAL_SUCCESS:
		set_bit(IREQ_ACTIVE, &ireq->flags);

		/*
		 * We will let framework know this task request started successfully,
		 * although core is still woring on starting the request (to post tc when
		 * RNC is resumed.)
		 */
		वापस SCI_SUCCESS;
	हाल SCI_SUCCESS:
		set_bit(IREQ_ACTIVE, &ireq->flags);
		sci_controller_post_request(ihost, ireq->post_context);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक sci_ग_लिखो_gpio_tx_gp(काष्ठा isci_host *ihost, u8 reg_index, u8 reg_count, u8 *ग_लिखो_data)
अणु
	पूर्णांक d;

	/* no support क्रम TX_GP_CFG */
	अगर (reg_index == 0)
		वापस -EINVAL;

	क्रम (d = 0; d < isci_gpio_count(ihost); d++) अणु
		u32 val = 0x444; /* all ODx.n clear */
		पूर्णांक i;

		क्रम (i = 0; i < 3; i++) अणु
			पूर्णांक bit;

			bit = try_test_sas_gpio_gp_bit(to_sas_gpio_od(d, i),
						       ग_लिखो_data, reg_index,
						       reg_count);
			अगर (bit < 0)
				अवरोध;

			/* अगर od is set, clear the 'invert' bit */
			val &= ~(bit << ((i << 2) + 2));
		पूर्ण

		अगर (i < 3)
			अवरोध;
		ग_लिखोl(val, &ihost->scu_रेजिस्टरs->peg0.sgpio.output_data_select[d]);
	पूर्ण

	/* unless reg_index is > 1, we should always be able to ग_लिखो at
	 * least one रेजिस्टर
	 */
	वापस d > 0;
पूर्ण

पूर्णांक isci_gpio_ग_लिखो(काष्ठा sas_ha_काष्ठा *sas_ha, u8 reg_type, u8 reg_index,
		    u8 reg_count, u8 *ग_लिखो_data)
अणु
	काष्ठा isci_host *ihost = sas_ha->lldd_ha;
	पूर्णांक written;

	चयन (reg_type) अणु
	हाल SAS_GPIO_REG_TX_GP:
		written = sci_ग_लिखो_gpio_tx_gp(ihost, reg_index, reg_count, ग_लिखो_data);
		अवरोध;
	शेष:
		written = -EINVAL;
	पूर्ण

	वापस written;
पूर्ण
