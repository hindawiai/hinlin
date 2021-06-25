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

#अगर_अघोषित _SCIC_SDS_REMOTE_NODE_CONTEXT_H_
#घोषणा _SCIC_SDS_REMOTE_NODE_CONTEXT_H_

/**
 * This file contains the काष्ठाures, स्थिरants, and prototypes associated with
 *    the remote node context in the silicon.  It exists to model and manage
 *    the remote node context in the silicon.
 *
 *
 */

#समावेश "isci.h"

/**
 *
 *
 * This स्थिरant represents an invalid remote device id, it is used to program
 * the STPDARNI रेजिस्टर so the driver knows when it has received a SIGNATURE
 * FIS from the SCU.
 */
#घोषणा SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX    0x0FFF

क्रमागत sci_remote_node_suspension_reasons अणु
	SCI_HW_SUSPEND,
	SCI_SW_SUSPEND_NORMAL,
	SCI_SW_SUSPEND_LINKHANG_DETECT
पूर्ण;
#घोषणा SCI_SOFTWARE_SUSPEND_CMD SCU_CONTEXT_COMMAND_POST_RNC_SUSPEND_TX_RX
#घोषणा SCI_SOFTWARE_SUSPEND_EXPECTED_EVENT SCU_EVENT_TL_RNC_SUSPEND_TX_RX

काष्ठा isci_request;
काष्ठा isci_remote_device;
काष्ठा sci_remote_node_context;

प्रकार व्योम (*scics_sds_remote_node_context_callback)(व्योम *);

/**
 * क्रमागत sci_remote_node_context_states
 * @SCI_RNC_INITIAL initial state क्रम a remote node context.  On a resume
 * request the remote node context will transition to the posting state.
 *
 * @SCI_RNC_POSTING: transition state that posts the RNi to the hardware. Once
 * the RNC is posted the remote node context will be made पढ़ोy.
 *
 * @SCI_RNC_INVALIDATING: transition state that will post an RNC invalidate to
 * the hardware.  Once the invalidate is complete the remote node context will
 * transition to the posting state.
 *
 * @SCI_RNC_RESUMING: transition state that will post an RNC resume to the
 * hardare.  Once the event notअगरication of resume complete is received the
 * remote node context will transition to the पढ़ोy state.
 *
 * @SCI_RNC_READY: state that the remote node context must be in to accept io
 * request operations.
 *
 * @SCI_RNC_TX_SUSPENDED: state that the remote node context transitions to when
 * it माला_लो a TX suspend notअगरication from the hardware.
 *
 * @SCI_RNC_TX_RX_SUSPENDED: state that the remote node context transitions to
 * when it माला_लो a TX RX suspend notअगरication from the hardware.
 *
 * @SCI_RNC_AWAIT_SUSPENSION: रुको state क्रम the remote node context that रुकोs
 * क्रम a suspend notअगरication from the hardware.  This state is entered when
 * either there is a request to supend the remote node context or when there is
 * a TC completion where the remote node will be suspended by the hardware.
 */
#घोषणा RNC_STATES अणु\
	C(RNC_INITIAL),\
	C(RNC_POSTING),\
	C(RNC_INVALIDATING),\
	C(RNC_RESUMING),\
	C(RNC_READY),\
	C(RNC_TX_SUSPENDED),\
	C(RNC_TX_RX_SUSPENDED),\
	C(RNC_AWAIT_SUSPENSION),\
	पूर्ण
#अघोषित C
#घोषणा C(a) SCI_##a
क्रमागत scis_sds_remote_node_context_states RNC_STATES;
#अघोषित C
स्थिर अक्षर *rnc_state_name(क्रमागत scis_sds_remote_node_context_states state);

/**
 *
 *
 * This क्रमागतeration is used to define the end destination state क्रम the remote
 * node context.
 */
क्रमागत sci_remote_node_context_destination_state अणु
	RNC_DEST_UNSPECIFIED,
	RNC_DEST_READY,
	RNC_DEST_FINAL,
	RNC_DEST_SUSPENDED,       /* Set when suspend during post/invalidate */
	RNC_DEST_SUSPENDED_RESUME /* Set when a resume was करोne during posting
				   * or invalidating and alपढ़ोy suspending.
				   */
पूर्ण;

/**
 * काष्ठा sci_remote_node_context - This काष्ठाure contains the data
 *    associated with the remote node context object.  The remote node context
 *    (RNC) object models the the remote device inक्रमmation necessary to manage
 *    the silicon RNC.
 */
काष्ठा sci_remote_node_context अणु
	/**
	 * This field indicates the remote node index (RNI) associated with
	 * this RNC.
	 */
	u16 remote_node_index;

	/**
	 * This field is the recored suspension type of the remote node
	 * context suspension.
	 */
	u32 suspend_type;
	क्रमागत sci_remote_node_suspension_reasons suspend_reason;
	u32 suspend_count;

	/**
	 * This field is true अगर the remote node context is resuming from its current
	 * state.  This can cause an स्वतःmatic resume on receiving a suspension
	 * notअगरication.
	 */
	क्रमागत sci_remote_node_context_destination_state destination_state;

	/**
	 * This field contains the callback function that the user requested to be
	 * called when the requested state transition is complete.
	 */
	scics_sds_remote_node_context_callback user_callback;

	/**
	 * This field contains the parameter that is called when the user requested
	 * state transition is completed.
	 */
	व्योम *user_cookie;

	/**
	 * This field contains the data क्रम the object's state machine.
	 */
	काष्ठा sci_base_state_machine sm;
पूर्ण;

व्योम sci_remote_node_context_स्थिरruct(काष्ठा sci_remote_node_context *rnc,
					    u16 remote_node_index);


bool sci_remote_node_context_is_पढ़ोy(
	काष्ठा sci_remote_node_context *sci_rnc);

bool sci_remote_node_context_is_suspended(काष्ठा sci_remote_node_context *sci_rnc);

क्रमागत sci_status sci_remote_node_context_event_handler(काष्ठा sci_remote_node_context *sci_rnc,
							   u32 event_code);
क्रमागत sci_status sci_remote_node_context_deकाष्ठा(काष्ठा sci_remote_node_context *sci_rnc,
						      scics_sds_remote_node_context_callback callback,
						      व्योम *callback_parameter);
क्रमागत sci_status sci_remote_node_context_suspend(काष्ठा sci_remote_node_context *sci_rnc,
						     क्रमागत sci_remote_node_suspension_reasons reason,
						     u32 suspension_code);
क्रमागत sci_status sci_remote_node_context_resume(काष्ठा sci_remote_node_context *sci_rnc,
						    scics_sds_remote_node_context_callback cb_fn,
						    व्योम *cb_p);
क्रमागत sci_status sci_remote_node_context_start_task(काष्ठा sci_remote_node_context *sci_rnc,
						   काष्ठा isci_request *ireq,
						   scics_sds_remote_node_context_callback cb_fn,
						   व्योम *cb_p);
क्रमागत sci_status sci_remote_node_context_start_io(काष्ठा sci_remote_node_context *sci_rnc,
						      काष्ठा isci_request *ireq);
पूर्णांक sci_remote_node_context_is_safe_to_पात(
	काष्ठा sci_remote_node_context *sci_rnc);

अटल अंतरभूत bool sci_remote_node_context_is_being_destroyed(
	काष्ठा sci_remote_node_context *sci_rnc)
अणु
	वापस (sci_rnc->destination_state == RNC_DEST_FINAL)
		|| ((sci_rnc->sm.current_state_id == SCI_RNC_INITIAL)
		    && (sci_rnc->destination_state == RNC_DEST_UNSPECIFIED));
पूर्ण
#पूर्ण_अगर  /* _SCIC_SDS_REMOTE_NODE_CONTEXT_H_ */
