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
#समावेश <scsi/sas_ata.h>
#समावेश "host.h"
#समावेश "isci.h"
#समावेश "remote_device.h"
#समावेश "remote_node_context.h"
#समावेश "scu_event_codes.h"
#समावेश "scu_task_context.h"

#अघोषित C
#घोषणा C(a) (#a)
स्थिर अक्षर *rnc_state_name(क्रमागत scis_sds_remote_node_context_states state)
अणु
	अटल स्थिर अक्षर * स्थिर strings[] = RNC_STATES;

	अगर (state >= ARRAY_SIZE(strings))
		वापस "UNKNOWN";

	वापस strings[state];
पूर्ण
#अघोषित C

/**
 * sci_remote_node_context_is_पढ़ोy()
 * @sci_rnc: The state of the remote node context object to check.
 *
 * This method will वापस true अगर the remote node context is in a READY state
 * otherwise it will वापस false bool true अगर the remote node context is in
 * the पढ़ोy state. false अगर the remote node context is not in the पढ़ोy state.
 */
bool sci_remote_node_context_is_पढ़ोy(
	काष्ठा sci_remote_node_context *sci_rnc)
अणु
	u32 current_state = sci_rnc->sm.current_state_id;

	अगर (current_state == SCI_RNC_READY) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool sci_remote_node_context_is_suspended(काष्ठा sci_remote_node_context *sci_rnc)
अणु
	u32 current_state = sci_rnc->sm.current_state_id;

	अगर (current_state == SCI_RNC_TX_RX_SUSPENDED)
		वापस true;
	वापस false;
पूर्ण

अटल जोड़ scu_remote_node_context *sci_rnc_by_id(काष्ठा isci_host *ihost, u16 id)
अणु
	अगर (id < ihost->remote_node_entries &&
	    ihost->device_table[id])
		वापस &ihost->remote_node_context_table[id];

	वापस शून्य;
पूर्ण

अटल व्योम sci_remote_node_context_स्थिरruct_buffer(काष्ठा sci_remote_node_context *sci_rnc)
अणु
	काष्ठा isci_remote_device *idev = rnc_to_dev(sci_rnc);
	काष्ठा करोमुख्य_device *dev = idev->करोमुख्य_dev;
	पूर्णांक rni = sci_rnc->remote_node_index;
	जोड़ scu_remote_node_context *rnc;
	काष्ठा isci_host *ihost;
	__le64 sas_addr;

	ihost = idev->owning_port->owning_controller;
	rnc = sci_rnc_by_id(ihost, rni);

	स_रखो(rnc, 0, माप(जोड़ scu_remote_node_context)
		* sci_remote_device_node_count(idev));

	rnc->ssp.remote_node_index = rni;
	rnc->ssp.remote_node_port_width = idev->device_port_width;
	rnc->ssp.logical_port_index = idev->owning_port->physical_port_index;

	/* sas address is __be64, context ram क्रमmat is __le64 */
	sas_addr = cpu_to_le64(SAS_ADDR(dev->sas_addr));
	rnc->ssp.remote_sas_address_hi = upper_32_bits(sas_addr);
	rnc->ssp.remote_sas_address_lo = lower_32_bits(sas_addr);

	rnc->ssp.nexus_loss_समयr_enable = true;
	rnc->ssp.check_bit               = false;
	rnc->ssp.is_valid                = false;
	rnc->ssp.is_remote_node_context  = true;
	rnc->ssp.function_number         = 0;

	rnc->ssp.arbitration_रुको_समय = 0;

	अगर (dev_is_sata(dev)) अणु
		rnc->ssp.connection_occupancy_समयout =
			ihost->user_parameters.stp_max_occupancy_समयout;
		rnc->ssp.connection_inactivity_समयout =
			ihost->user_parameters.stp_inactivity_समयout;
	पूर्ण अन्यथा अणु
		rnc->ssp.connection_occupancy_समयout  =
			ihost->user_parameters.ssp_max_occupancy_समयout;
		rnc->ssp.connection_inactivity_समयout =
			ihost->user_parameters.ssp_inactivity_समयout;
	पूर्ण

	rnc->ssp.initial_arbitration_रुको_समय = 0;

	/* Open Address Frame Parameters */
	rnc->ssp.oaf_connection_rate = idev->connection_rate;
	rnc->ssp.oaf_features = 0;
	rnc->ssp.oaf_source_zone_group = 0;
	rnc->ssp.oaf_more_compatibility_features = 0;
पूर्ण
/*
 * This method will setup the remote node context object so it will transition
 * to its पढ़ोy state.  If the remote node context is alपढ़ोy setup to
 * transition to its final state then this function करोes nothing. none
 */
अटल व्योम sci_remote_node_context_setup_to_resume(
	काष्ठा sci_remote_node_context *sci_rnc,
	scics_sds_remote_node_context_callback callback,
	व्योम *callback_parameter,
	क्रमागत sci_remote_node_context_destination_state dest_param)
अणु
	अगर (sci_rnc->destination_state != RNC_DEST_FINAL) अणु
		sci_rnc->destination_state = dest_param;
		अगर (callback != शून्य) अणु
			sci_rnc->user_callback = callback;
			sci_rnc->user_cookie   = callback_parameter;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sci_remote_node_context_setup_to_destroy(
	काष्ठा sci_remote_node_context *sci_rnc,
	scics_sds_remote_node_context_callback callback,
	व्योम *callback_parameter)
अणु
	काष्ठा isci_host *ihost = idev_to_ihost(rnc_to_dev(sci_rnc));

	sci_rnc->destination_state = RNC_DEST_FINAL;
	sci_rnc->user_callback     = callback;
	sci_rnc->user_cookie       = callback_parameter;

	wake_up(&ihost->eventq);
पूर्ण

/*
 * This method just calls the user callback function and then resets the
 * callback.
 */
अटल व्योम sci_remote_node_context_notअगरy_user(
	काष्ठा sci_remote_node_context *rnc)
अणु
	अगर (rnc->user_callback != शून्य) अणु
		(*rnc->user_callback)(rnc->user_cookie);

		rnc->user_callback = शून्य;
		rnc->user_cookie = शून्य;
	पूर्ण
पूर्ण

अटल व्योम sci_remote_node_context_जारी_state_transitions(काष्ठा sci_remote_node_context *rnc)
अणु
	चयन (rnc->destination_state) अणु
	हाल RNC_DEST_READY:
	हाल RNC_DEST_SUSPENDED_RESUME:
		rnc->destination_state = RNC_DEST_READY;
		fallthrough;
	हाल RNC_DEST_FINAL:
		sci_remote_node_context_resume(rnc, rnc->user_callback,
					       rnc->user_cookie);
		अवरोध;
	शेष:
		rnc->destination_state = RNC_DEST_UNSPECIFIED;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sci_remote_node_context_validate_context_buffer(काष्ठा sci_remote_node_context *sci_rnc)
अणु
	जोड़ scu_remote_node_context *rnc_buffer;
	काष्ठा isci_remote_device *idev = rnc_to_dev(sci_rnc);
	काष्ठा करोमुख्य_device *dev = idev->करोमुख्य_dev;
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;

	rnc_buffer = sci_rnc_by_id(ihost, sci_rnc->remote_node_index);

	rnc_buffer->ssp.is_valid = true;

	अगर (dev_is_sata(dev) && dev->parent) अणु
		sci_remote_device_post_request(idev, SCU_CONTEXT_COMMAND_POST_RNC_96);
	पूर्ण अन्यथा अणु
		sci_remote_device_post_request(idev, SCU_CONTEXT_COMMAND_POST_RNC_32);

		अगर (!dev->parent)
			sci_port_setup_transports(idev->owning_port,
						  sci_rnc->remote_node_index);
	पूर्ण
पूर्ण

अटल व्योम sci_remote_node_context_invalidate_context_buffer(काष्ठा sci_remote_node_context *sci_rnc)
अणु
	जोड़ scu_remote_node_context *rnc_buffer;
	काष्ठा isci_remote_device *idev = rnc_to_dev(sci_rnc);
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;

	rnc_buffer = sci_rnc_by_id(ihost, sci_rnc->remote_node_index);

	rnc_buffer->ssp.is_valid = false;

	sci_remote_device_post_request(rnc_to_dev(sci_rnc),
				       SCU_CONTEXT_COMMAND_POST_RNC_INVALIDATE);
पूर्ण

अटल व्योम sci_remote_node_context_initial_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा sci_remote_node_context *rnc = container_of(sm, typeof(*rnc), sm);
	काष्ठा isci_remote_device *idev = rnc_to_dev(rnc);
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;

	/* Check to see अगर we have gotten back to the initial state because
	 * someone requested to destroy the remote node context object.
	 */
	अगर (sm->previous_state_id == SCI_RNC_INVALIDATING) अणु
		rnc->destination_state = RNC_DEST_UNSPECIFIED;
		sci_remote_node_context_notअगरy_user(rnc);

		smp_wmb();
		wake_up(&ihost->eventq);
	पूर्ण
पूर्ण

अटल व्योम sci_remote_node_context_posting_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा sci_remote_node_context *sci_rnc = container_of(sm, typeof(*sci_rnc), sm);

	sci_remote_node_context_validate_context_buffer(sci_rnc);
पूर्ण

अटल व्योम sci_remote_node_context_invalidating_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा sci_remote_node_context *rnc = container_of(sm, typeof(*rnc), sm);

	/* Terminate all outstanding requests. */
	sci_remote_device_terminate_requests(rnc_to_dev(rnc));
	sci_remote_node_context_invalidate_context_buffer(rnc);
पूर्ण

अटल व्योम sci_remote_node_context_resuming_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा sci_remote_node_context *rnc = container_of(sm, typeof(*rnc), sm);
	काष्ठा isci_remote_device *idev;
	काष्ठा करोमुख्य_device *dev;

	idev = rnc_to_dev(rnc);
	dev = idev->करोमुख्य_dev;

	/*
	 * For direct attached SATA devices we need to clear the TLCR
	 * NCQ to TCi tag mapping on the phy and in हालs where we
	 * resume because of a target reset we also need to update
	 * the STPTLDARNI रेजिस्टर with the RNi of the device
	 */
	अगर (dev_is_sata(dev) && !dev->parent)
		sci_port_setup_transports(idev->owning_port, rnc->remote_node_index);

	sci_remote_device_post_request(idev, SCU_CONTEXT_COMMAND_POST_RNC_RESUME);
पूर्ण

अटल व्योम sci_remote_node_context_पढ़ोy_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा sci_remote_node_context *rnc = container_of(sm, typeof(*rnc), sm);
	क्रमागत sci_remote_node_context_destination_state dest_select;
	पूर्णांक tell_user = 1;

	dest_select = rnc->destination_state;
	rnc->destination_state = RNC_DEST_UNSPECIFIED;

	अगर ((dest_select == RNC_DEST_SUSPENDED) ||
	    (dest_select == RNC_DEST_SUSPENDED_RESUME)) अणु
		sci_remote_node_context_suspend(
			rnc, rnc->suspend_reason,
			SCI_SOFTWARE_SUSPEND_EXPECTED_EVENT);

		अगर (dest_select == RNC_DEST_SUSPENDED_RESUME)
			tell_user = 0;  /* Wait until पढ़ोy again. */
	पूर्ण
	अगर (tell_user)
		sci_remote_node_context_notअगरy_user(rnc);
पूर्ण

अटल व्योम sci_remote_node_context_tx_suspended_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा sci_remote_node_context *rnc = container_of(sm, typeof(*rnc), sm);

	sci_remote_node_context_जारी_state_transitions(rnc);
पूर्ण

अटल व्योम sci_remote_node_context_tx_rx_suspended_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा sci_remote_node_context *rnc = container_of(sm, typeof(*rnc), sm);
	काष्ठा isci_remote_device *idev = rnc_to_dev(rnc);
	काष्ठा isci_host *ihost = idev->owning_port->owning_controller;
	u32 new_count = rnc->suspend_count + 1;

	अगर (new_count == 0)
		rnc->suspend_count = 1;
	अन्यथा
		rnc->suspend_count = new_count;
	smp_wmb();

	/* Terminate outstanding requests pending पात. */
	sci_remote_device_पात_requests_pending_पात(idev);

	wake_up(&ihost->eventq);
	sci_remote_node_context_जारी_state_transitions(rnc);
पूर्ण

अटल व्योम sci_remote_node_context_aरुको_suspend_state_निकास(
	काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा sci_remote_node_context *rnc
		= container_of(sm, typeof(*rnc), sm);
	काष्ठा isci_remote_device *idev = rnc_to_dev(rnc);

	अगर (dev_is_sata(idev->करोमुख्य_dev))
		isci_dev_set_hang_detection_समयout(idev, 0);
पूर्ण

अटल स्थिर काष्ठा sci_base_state sci_remote_node_context_state_table[] = अणु
	[SCI_RNC_INITIAL] = अणु
		.enter_state = sci_remote_node_context_initial_state_enter,
	पूर्ण,
	[SCI_RNC_POSTING] = अणु
		.enter_state = sci_remote_node_context_posting_state_enter,
	पूर्ण,
	[SCI_RNC_INVALIDATING] = अणु
		.enter_state = sci_remote_node_context_invalidating_state_enter,
	पूर्ण,
	[SCI_RNC_RESUMING] = अणु
		.enter_state = sci_remote_node_context_resuming_state_enter,
	पूर्ण,
	[SCI_RNC_READY] = अणु
		.enter_state = sci_remote_node_context_पढ़ोy_state_enter,
	पूर्ण,
	[SCI_RNC_TX_SUSPENDED] = अणु
		.enter_state = sci_remote_node_context_tx_suspended_state_enter,
	पूर्ण,
	[SCI_RNC_TX_RX_SUSPENDED] = अणु
		.enter_state = sci_remote_node_context_tx_rx_suspended_state_enter,
	पूर्ण,
	[SCI_RNC_AWAIT_SUSPENSION] = अणु
		.निकास_state = sci_remote_node_context_aरुको_suspend_state_निकास,
	पूर्ण,
पूर्ण;

व्योम sci_remote_node_context_स्थिरruct(काष्ठा sci_remote_node_context *rnc,
					    u16 remote_node_index)
अणु
	स_रखो(rnc, 0, माप(काष्ठा sci_remote_node_context));

	rnc->remote_node_index = remote_node_index;
	rnc->destination_state = RNC_DEST_UNSPECIFIED;

	sci_init_sm(&rnc->sm, sci_remote_node_context_state_table, SCI_RNC_INITIAL);
पूर्ण

क्रमागत sci_status sci_remote_node_context_event_handler(काष्ठा sci_remote_node_context *sci_rnc,
							   u32 event_code)
अणु
	क्रमागत scis_sds_remote_node_context_states state;
	u32 next_state;

	state = sci_rnc->sm.current_state_id;
	चयन (state) अणु
	हाल SCI_RNC_POSTING:
		चयन (scu_get_event_code(event_code)) अणु
		हाल SCU_EVENT_POST_RNC_COMPLETE:
			sci_change_state(&sci_rnc->sm, SCI_RNC_READY);
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण
		अवरोध;
	हाल SCI_RNC_INVALIDATING:
		अगर (scu_get_event_code(event_code) == SCU_EVENT_POST_RNC_INVALIDATE_COMPLETE) अणु
			अगर (sci_rnc->destination_state == RNC_DEST_FINAL)
				next_state = SCI_RNC_INITIAL;
			अन्यथा
				next_state = SCI_RNC_POSTING;
			sci_change_state(&sci_rnc->sm, next_state);
		पूर्ण अन्यथा अणु
			चयन (scu_get_event_type(event_code)) अणु
			हाल SCU_EVENT_TYPE_RNC_SUSPEND_TX:
			हाल SCU_EVENT_TYPE_RNC_SUSPEND_TX_RX:
				/* We really करोnt care अगर the hardware is going to suspend
				 * the device since it's being invalidated anyway */
				dev_warn(scirdev_to_dev(rnc_to_dev(sci_rnc)),
					"%s: SCIC Remote Node Context 0x%p was "
					"suspended by hardware while being "
					"invalidated.\n", __func__, sci_rnc);
				अवरोध;
			शेष:
				जाओ out;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SCI_RNC_RESUMING:
		अगर (scu_get_event_code(event_code) == SCU_EVENT_POST_RCN_RELEASE) अणु
			sci_change_state(&sci_rnc->sm, SCI_RNC_READY);
		पूर्ण अन्यथा अणु
			चयन (scu_get_event_type(event_code)) अणु
			हाल SCU_EVENT_TYPE_RNC_SUSPEND_TX:
			हाल SCU_EVENT_TYPE_RNC_SUSPEND_TX_RX:
				/* We really करोnt care अगर the hardware is going to suspend
				 * the device since it's being resumed anyway */
				dev_warn(scirdev_to_dev(rnc_to_dev(sci_rnc)),
					"%s: SCIC Remote Node Context 0x%p was "
					"suspended by hardware while being resumed.\n",
					__func__, sci_rnc);
				अवरोध;
			शेष:
				जाओ out;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SCI_RNC_READY:
		चयन (scu_get_event_type(event_code)) अणु
		हाल SCU_EVENT_TL_RNC_SUSPEND_TX:
			sci_change_state(&sci_rnc->sm, SCI_RNC_TX_SUSPENDED);
			sci_rnc->suspend_type = scu_get_event_type(event_code);
			अवरोध;
		हाल SCU_EVENT_TL_RNC_SUSPEND_TX_RX:
			sci_change_state(&sci_rnc->sm, SCI_RNC_TX_RX_SUSPENDED);
			sci_rnc->suspend_type = scu_get_event_type(event_code);
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण
		अवरोध;
	हाल SCI_RNC_AWAIT_SUSPENSION:
		चयन (scu_get_event_type(event_code)) अणु
		हाल SCU_EVENT_TL_RNC_SUSPEND_TX:
			next_state = SCI_RNC_TX_SUSPENDED;
			अवरोध;
		हाल SCU_EVENT_TL_RNC_SUSPEND_TX_RX:
			next_state = SCI_RNC_TX_RX_SUSPENDED;
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण
		अगर (sci_rnc->suspend_type == scu_get_event_type(event_code))
			sci_change_state(&sci_rnc->sm, next_state);
		अवरोध;
	शेष:
		dev_warn(scirdev_to_dev(rnc_to_dev(sci_rnc)),
			 "%s: invalid state: %s\n", __func__,
			 rnc_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
	वापस SCI_SUCCESS;

 out:
	dev_warn(scirdev_to_dev(rnc_to_dev(sci_rnc)),
		 "%s: code: %#x state: %s\n", __func__, event_code,
		 rnc_state_name(state));
	वापस SCI_FAILURE;

पूर्ण

क्रमागत sci_status sci_remote_node_context_deकाष्ठा(काष्ठा sci_remote_node_context *sci_rnc,
						      scics_sds_remote_node_context_callback cb_fn,
						      व्योम *cb_p)
अणु
	क्रमागत scis_sds_remote_node_context_states state;

	state = sci_rnc->sm.current_state_id;
	चयन (state) अणु
	हाल SCI_RNC_INVALIDATING:
		sci_remote_node_context_setup_to_destroy(sci_rnc, cb_fn, cb_p);
		वापस SCI_SUCCESS;
	हाल SCI_RNC_POSTING:
	हाल SCI_RNC_RESUMING:
	हाल SCI_RNC_READY:
	हाल SCI_RNC_TX_SUSPENDED:
	हाल SCI_RNC_TX_RX_SUSPENDED:
		sci_remote_node_context_setup_to_destroy(sci_rnc, cb_fn, cb_p);
		sci_change_state(&sci_rnc->sm, SCI_RNC_INVALIDATING);
		वापस SCI_SUCCESS;
	हाल SCI_RNC_AWAIT_SUSPENSION:
		sci_remote_node_context_setup_to_destroy(sci_rnc, cb_fn, cb_p);
		वापस SCI_SUCCESS;
	हाल SCI_RNC_INITIAL:
		dev_warn(scirdev_to_dev(rnc_to_dev(sci_rnc)),
			 "%s: invalid state: %s\n", __func__,
			 rnc_state_name(state));
		/* We have decided that the deकाष्ठा request on the remote node context
		 * can not fail since it is either in the initial/destroyed state or is
		 * can be destroyed.
		 */
		वापस SCI_SUCCESS;
	शेष:
		dev_warn(scirdev_to_dev(rnc_to_dev(sci_rnc)),
			 "%s: invalid state %s\n", __func__,
			 rnc_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
पूर्ण

क्रमागत sci_status sci_remote_node_context_suspend(
			काष्ठा sci_remote_node_context *sci_rnc,
			क्रमागत sci_remote_node_suspension_reasons suspend_reason,
			u32 suspend_type)
अणु
	क्रमागत scis_sds_remote_node_context_states state
		= sci_rnc->sm.current_state_id;
	काष्ठा isci_remote_device *idev = rnc_to_dev(sci_rnc);
	क्रमागत sci_status status = SCI_FAILURE_INVALID_STATE;
	क्रमागत sci_remote_node_context_destination_state dest_param =
		RNC_DEST_UNSPECIFIED;

	dev_dbg(scirdev_to_dev(idev),
		"%s: current state %s, current suspend_type %x dest state %d,"
			" arg suspend_reason %d, arg suspend_type %x",
		__func__, rnc_state_name(state), sci_rnc->suspend_type,
		sci_rnc->destination_state, suspend_reason,
		suspend_type);

	/* Disable स्वतःmatic state continuations अगर explicitly suspending. */
	अगर ((suspend_reason == SCI_HW_SUSPEND) ||
	    (sci_rnc->destination_state == RNC_DEST_FINAL))
		dest_param = sci_rnc->destination_state;

	चयन (state) अणु
	हाल SCI_RNC_READY:
		अवरोध;
	हाल SCI_RNC_INVALIDATING:
		अगर (sci_rnc->destination_state == RNC_DEST_FINAL) अणु
			dev_warn(scirdev_to_dev(idev),
				 "%s: already destroying %p\n",
				 __func__, sci_rnc);
			वापस SCI_FAILURE_INVALID_STATE;
		पूर्ण
		fallthrough;	/* and handle like SCI_RNC_POSTING */
	हाल SCI_RNC_RESUMING:
		fallthrough;	/* and handle like SCI_RNC_POSTING */
	हाल SCI_RNC_POSTING:
		/* Set the destination state to AWAIT - this संकेतs the
		 * entry पूर्णांकo the SCI_RNC_READY state that a suspension
		 * needs to be करोne immediately.
		 */
		अगर (sci_rnc->destination_state != RNC_DEST_FINAL)
			sci_rnc->destination_state = RNC_DEST_SUSPENDED;
		sci_rnc->suspend_type = suspend_type;
		sci_rnc->suspend_reason = suspend_reason;
		वापस SCI_SUCCESS;

	हाल SCI_RNC_TX_SUSPENDED:
		अगर (suspend_type == SCU_EVENT_TL_RNC_SUSPEND_TX)
			status = SCI_SUCCESS;
		अवरोध;
	हाल SCI_RNC_TX_RX_SUSPENDED:
		अगर (suspend_type == SCU_EVENT_TL_RNC_SUSPEND_TX_RX)
			status = SCI_SUCCESS;
		अवरोध;
	हाल SCI_RNC_AWAIT_SUSPENSION:
		अगर ((sci_rnc->suspend_type == SCU_EVENT_TL_RNC_SUSPEND_TX_RX)
		    || (suspend_type == sci_rnc->suspend_type))
			वापस SCI_SUCCESS;
		अवरोध;
	शेष:
		dev_warn(scirdev_to_dev(rnc_to_dev(sci_rnc)),
			 "%s: invalid state %s\n", __func__,
			 rnc_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
	sci_rnc->destination_state = dest_param;
	sci_rnc->suspend_type = suspend_type;
	sci_rnc->suspend_reason = suspend_reason;

	अगर (status == SCI_SUCCESS) अणु /* Alपढ़ोy in the destination state? */
		काष्ठा isci_host *ihost = idev->owning_port->owning_controller;

		wake_up_all(&ihost->eventq); /* Let observers look. */
		वापस SCI_SUCCESS;
	पूर्ण
	अगर ((suspend_reason == SCI_SW_SUSPEND_NORMAL) ||
	    (suspend_reason == SCI_SW_SUSPEND_LINKHANG_DETECT)) अणु

		अगर (suspend_reason == SCI_SW_SUSPEND_LINKHANG_DETECT)
			isci_dev_set_hang_detection_समयout(idev, 0x00000001);

		sci_remote_device_post_request(
			idev, SCI_SOFTWARE_SUSPEND_CMD);
	पूर्ण
	अगर (state != SCI_RNC_AWAIT_SUSPENSION)
		sci_change_state(&sci_rnc->sm, SCI_RNC_AWAIT_SUSPENSION);

	वापस SCI_SUCCESS;
पूर्ण

क्रमागत sci_status sci_remote_node_context_resume(काष्ठा sci_remote_node_context *sci_rnc,
						    scics_sds_remote_node_context_callback cb_fn,
						    व्योम *cb_p)
अणु
	क्रमागत scis_sds_remote_node_context_states state;
	काष्ठा isci_remote_device *idev = rnc_to_dev(sci_rnc);

	state = sci_rnc->sm.current_state_id;
	dev_dbg(scirdev_to_dev(idev),
		"%s: state %s, cb_fn = %p, cb_p = %p; dest_state = %d; "
			"dev resume path %s\n",
		__func__, rnc_state_name(state), cb_fn, cb_p,
		sci_rnc->destination_state,
		test_bit(IDEV_ABORT_PATH_ACTIVE, &idev->flags)
			? "<abort active>" : "<normal>");

	चयन (state) अणु
	हाल SCI_RNC_INITIAL:
		अगर (sci_rnc->remote_node_index == SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX)
			वापस SCI_FAILURE_INVALID_STATE;

		sci_remote_node_context_setup_to_resume(sci_rnc, cb_fn,	cb_p,
							RNC_DEST_READY);
		अगर (!test_bit(IDEV_ABORT_PATH_ACTIVE, &idev->flags)) अणु
			sci_remote_node_context_स्थिरruct_buffer(sci_rnc);
			sci_change_state(&sci_rnc->sm, SCI_RNC_POSTING);
		पूर्ण
		वापस SCI_SUCCESS;

	हाल SCI_RNC_POSTING:
	हाल SCI_RNC_INVALIDATING:
	हाल SCI_RNC_RESUMING:
		/* We are still रुकोing to post when a resume was
		 * requested.
		 */
		चयन (sci_rnc->destination_state) अणु
		हाल RNC_DEST_SUSPENDED:
		हाल RNC_DEST_SUSPENDED_RESUME:
			/* Previously रुकोing to suspend after posting.
			 * Now जारी onto resumption.
			 */
			sci_remote_node_context_setup_to_resume(
				sci_rnc, cb_fn, cb_p,
				RNC_DEST_SUSPENDED_RESUME);
			अवरोध;
		शेष:
			sci_remote_node_context_setup_to_resume(
				sci_rnc, cb_fn, cb_p,
				RNC_DEST_READY);
			अवरोध;
		पूर्ण
		वापस SCI_SUCCESS;

	हाल SCI_RNC_TX_SUSPENDED:
	हाल SCI_RNC_TX_RX_SUSPENDED:
		अणु
			काष्ठा करोमुख्य_device *dev = idev->करोमुख्य_dev;
			/* If this is an expander attached SATA device we must
			 * invalidate and repost the RNC since this is the only
			 * way to clear the TCi to NCQ tag mapping table क्रम
			 * the RNi. All other device types we can just resume.
			 */
			sci_remote_node_context_setup_to_resume(
				sci_rnc, cb_fn, cb_p, RNC_DEST_READY);

			अगर (!test_bit(IDEV_ABORT_PATH_ACTIVE, &idev->flags)) अणु
				अगर ((dev_is_sata(dev) && dev->parent) ||
				    (sci_rnc->destination_state == RNC_DEST_FINAL))
					sci_change_state(&sci_rnc->sm,
							 SCI_RNC_INVALIDATING);
				अन्यथा
					sci_change_state(&sci_rnc->sm,
							 SCI_RNC_RESUMING);
			पूर्ण
		पूर्ण
		वापस SCI_SUCCESS;

	हाल SCI_RNC_AWAIT_SUSPENSION:
		sci_remote_node_context_setup_to_resume(
			sci_rnc, cb_fn, cb_p, RNC_DEST_SUSPENDED_RESUME);
		वापस SCI_SUCCESS;
	शेष:
		dev_warn(scirdev_to_dev(rnc_to_dev(sci_rnc)),
			 "%s: invalid state %s\n", __func__,
			 rnc_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
पूर्ण

क्रमागत sci_status sci_remote_node_context_start_io(काष्ठा sci_remote_node_context *sci_rnc,
							     काष्ठा isci_request *ireq)
अणु
	क्रमागत scis_sds_remote_node_context_states state;

	state = sci_rnc->sm.current_state_id;

	चयन (state) अणु
	हाल SCI_RNC_READY:
		वापस SCI_SUCCESS;
	हाल SCI_RNC_TX_SUSPENDED:
	हाल SCI_RNC_TX_RX_SUSPENDED:
	हाल SCI_RNC_AWAIT_SUSPENSION:
		dev_warn(scirdev_to_dev(rnc_to_dev(sci_rnc)),
			 "%s: invalid state %s\n", __func__,
			 rnc_state_name(state));
		वापस SCI_FAILURE_REMOTE_DEVICE_RESET_REQUIRED;
	शेष:
		dev_dbg(scirdev_to_dev(rnc_to_dev(sci_rnc)),
			"%s: invalid state %s\n", __func__,
			rnc_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
पूर्ण

क्रमागत sci_status sci_remote_node_context_start_task(
	काष्ठा sci_remote_node_context *sci_rnc,
	काष्ठा isci_request *ireq,
	scics_sds_remote_node_context_callback cb_fn,
	व्योम *cb_p)
अणु
	क्रमागत sci_status status = sci_remote_node_context_resume(sci_rnc,
								cb_fn, cb_p);
	अगर (status != SCI_SUCCESS)
		dev_warn(scirdev_to_dev(rnc_to_dev(sci_rnc)),
			"%s: resume failed: %d\n", __func__, status);
	वापस status;
पूर्ण

पूर्णांक sci_remote_node_context_is_safe_to_पात(
	काष्ठा sci_remote_node_context *sci_rnc)
अणु
	क्रमागत scis_sds_remote_node_context_states state;

	state = sci_rnc->sm.current_state_id;
	चयन (state) अणु
	हाल SCI_RNC_INVALIDATING:
	हाल SCI_RNC_TX_RX_SUSPENDED:
		वापस 1;
	हाल SCI_RNC_POSTING:
	हाल SCI_RNC_RESUMING:
	हाल SCI_RNC_READY:
	हाल SCI_RNC_TX_SUSPENDED:
	हाल SCI_RNC_AWAIT_SUSPENSION:
	हाल SCI_RNC_INITIAL:
		वापस 0;
	शेष:
		dev_warn(scirdev_to_dev(rnc_to_dev(sci_rnc)),
			 "%s: invalid state %d\n", __func__, state);
		वापस 0;
	पूर्ण
पूर्ण
