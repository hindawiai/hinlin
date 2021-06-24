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

#अगर_अघोषित __ISCI_H__
#घोषणा __ISCI_H__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>

#घोषणा DRV_NAME "isci"
#घोषणा SCI_PCI_BAR_COUNT 2
#घोषणा SCI_NUM_MSI_X_INT 2
#घोषणा SCI_SMU_BAR       0
#घोषणा SCI_SMU_BAR_SIZE  (16*1024)
#घोषणा SCI_SCU_BAR       1
#घोषणा SCI_SCU_BAR_SIZE  (4*1024*1024)
#घोषणा SCI_IO_SPACE_BAR0 2
#घोषणा SCI_IO_SPACE_BAR1 3
#घोषणा ISCI_CAN_QUEUE_VAL 250 /* < SCI_MAX_IO_REQUESTS ? */
#घोषणा SCIC_CONTROLLER_STOP_TIMEOUT 5000

#घोषणा SCI_CONTROLLER_INVALID_IO_TAG 0xFFFF

#घोषणा SCI_MAX_PHYS  (4UL)
#घोषणा SCI_MAX_PORTS SCI_MAX_PHYS
#घोषणा SCI_MAX_SMP_PHYS  (384) /* not silicon स्थिरrained */
#घोषणा SCI_MAX_REMOTE_DEVICES (256UL)
#घोषणा SCI_MAX_IO_REQUESTS (256UL)
#घोषणा SCI_MAX_SEQ (16)
#घोषणा SCI_MAX_MSIX_MESSAGES  (2)
#घोषणा SCI_MAX_SCATTER_GATHER_ELEMENTS 130 /* not silicon स्थिरrained */
#घोषणा SCI_MAX_CONTROLLERS 2
#घोषणा SCI_MAX_DOMAINS  SCI_MAX_PORTS

#घोषणा SCU_MAX_CRITICAL_NOTIFICATIONS    (384)
#घोषणा SCU_MAX_EVENTS_SHIFT		  (7)
#घोषणा SCU_MAX_EVENTS                    (1 << SCU_MAX_EVENTS_SHIFT)
#घोषणा SCU_MAX_UNSOLICITED_FRAMES        (128)
#घोषणा SCU_MAX_COMPLETION_QUEUE_SCRATCH  (128)
#घोषणा SCU_MAX_COMPLETION_QUEUE_ENTRIES  (SCU_MAX_CRITICAL_NOTIFICATIONS \
					   + SCU_MAX_EVENTS \
					   + SCU_MAX_UNSOLICITED_FRAMES	\
					   + SCI_MAX_IO_REQUESTS \
					   + SCU_MAX_COMPLETION_QUEUE_SCRATCH)
#घोषणा SCU_MAX_COMPLETION_QUEUE_SHIFT	  (ilog2(SCU_MAX_COMPLETION_QUEUE_ENTRIES))

#घोषणा SCU_ABSOLUTE_MAX_UNSOLICITED_FRAMES (4096)
#घोषणा SCU_UNSOLICITED_FRAME_BUFFER_SIZE   (1024U)
#घोषणा SCU_INVALID_FRAME_INDEX             (0xFFFF)

#घोषणा SCU_IO_REQUEST_MAX_SGE_SIZE         (0x00FFFFFF)
#घोषणा SCU_IO_REQUEST_MAX_TRANSFER_LENGTH  (0x00FFFFFF)

अटल अंतरभूत व्योम check_sizes(व्योम)
अणु
	BUILD_BUG_ON_NOT_POWER_OF_2(SCU_MAX_EVENTS);
	BUILD_BUG_ON(SCU_MAX_UNSOLICITED_FRAMES <= 8);
	BUILD_BUG_ON_NOT_POWER_OF_2(SCU_MAX_UNSOLICITED_FRAMES);
	BUILD_BUG_ON_NOT_POWER_OF_2(SCU_MAX_COMPLETION_QUEUE_ENTRIES);
	BUILD_BUG_ON(SCU_MAX_UNSOLICITED_FRAMES > SCU_ABSOLUTE_MAX_UNSOLICITED_FRAMES);
	BUILD_BUG_ON_NOT_POWER_OF_2(SCI_MAX_IO_REQUESTS);
	BUILD_BUG_ON_NOT_POWER_OF_2(SCI_MAX_SEQ);
पूर्ण

/**
 * क्रमागत sci_status - This is the general वापस status क्रमागतeration क्रम non-IO,
 *    non-task management related SCI पूर्णांकerface methods.
 *
 *
 */
क्रमागत sci_status अणु
	/**
	 * This member indicates successful completion.
	 */
	SCI_SUCCESS = 0,

	/**
	 * This value indicates that the calling method completed successfully,
	 * but that the IO may have completed beक्रमe having it's start method
	 * invoked.  This occurs during SAT translation क्रम requests that करो
	 * not require an IO to the target or क्रम any other requests that may
	 * be completed without having to submit IO.
	 */
	SCI_SUCCESS_IO_COMPLETE_BEFORE_START,

	/**
	 *  This Value indicates that the SCU hardware वापसed an early response
	 *  because the io request specअगरied more data than is वापसed by the
	 *  target device (mode pages, inquiry data, etc.). The completion routine
	 *  will handle this हाल to get the actual number of bytes transferred.
	 */
	SCI_SUCCESS_IO_DONE_EARLY,

	/**
	 * This member indicates that the object क्रम which a state change is
	 * being requested is alपढ़ोy in said state.
	 */
	SCI_WARNING_ALREADY_IN_STATE,

	/**
	 * This member indicates पूर्णांकerrupt coalescence समयr may cause SAS
	 * specअगरication compliance issues (i.e. SMP target mode response
	 * frames must be वापसed within 1.9 milliseconds).
	 */
	SCI_WARNING_TIMER_CONFLICT,

	/**
	 * This field indicates a sequence of action is not completed yet. Mostly,
	 * this status is used when multiple ATA commands are needed in a SATI translation.
	 */
	SCI_WARNING_SEQUENCE_INCOMPLETE,

	/**
	 * This member indicates that there was a general failure.
	 */
	SCI_FAILURE,

	/**
	 * This member indicates that the SCI implementation is unable to complete
	 * an operation due to a critical flaw the prevents any further operation
	 * (i.e. an invalid poपूर्णांकer).
	 */
	SCI_FATAL_ERROR,

	/**
	 * This member indicates the calling function failed, because the state
	 * of the controller is in a state that prevents successful completion.
	 */
	SCI_FAILURE_INVALID_STATE,

	/**
	 * This member indicates the calling function failed, because there is
	 * insufficient resources/memory to complete the request.
	 */
	SCI_FAILURE_INSUFFICIENT_RESOURCES,

	/**
	 * This member indicates the calling function failed, because the
	 * controller object required क्रम the operation can't be located.
	 */
	SCI_FAILURE_CONTROLLER_NOT_FOUND,

	/**
	 * This member indicates the calling function failed, because the
	 * discovered controller type is not supported by the library.
	 */
	SCI_FAILURE_UNSUPPORTED_CONTROLLER_TYPE,

	/**
	 * This member indicates the calling function failed, because the
	 * requested initialization data version isn't supported.
	 */
	SCI_FAILURE_UNSUPPORTED_INIT_DATA_VERSION,

	/**
	 * This member indicates the calling function failed, because the
	 * requested configuration of SAS Phys पूर्णांकo SAS Ports is not supported.
	 */
	SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION,

	/**
	 * This member indicates the calling function failed, because the
	 * requested protocol is not supported by the remote device, port,
	 * or controller.
	 */
	SCI_FAILURE_UNSUPPORTED_PROTOCOL,

	/**
	 * This member indicates the calling function failed, because the
	 * requested inक्रमmation type is not supported by the SCI implementation.
	 */
	SCI_FAILURE_UNSUPPORTED_INFORMATION_TYPE,

	/**
	 * This member indicates the calling function failed, because the
	 * device alपढ़ोy exists.
	 */
	SCI_FAILURE_DEVICE_EXISTS,

	/**
	 * This member indicates the calling function failed, because adding
	 * a phy to the object is not possible.
	 */
	SCI_FAILURE_ADDING_PHY_UNSUPPORTED,

	/**
	 * This member indicates the calling function failed, because the
	 * requested inक्रमmation type is not supported by the SCI implementation.
	 */
	SCI_FAILURE_UNSUPPORTED_INFORMATION_FIELD,

	/**
	 * This member indicates the calling function failed, because the SCI
	 * implementation करोes not support the supplied समय limit.
	 */
	SCI_FAILURE_UNSUPPORTED_TIME_LIMIT,

	/**
	 * This member indicates the calling method failed, because the SCI
	 * implementation करोes not contain the specअगरied Phy.
	 */
	SCI_FAILURE_INVALID_PHY,

	/**
	 * This member indicates the calling method failed, because the SCI
	 * implementation करोes not contain the specअगरied Port.
	 */
	SCI_FAILURE_INVALID_PORT,

	/**
	 * This member indicates the calling method was partly successful
	 * The port was reset but not all phys in port are operational
	 */
	SCI_FAILURE_RESET_PORT_PARTIAL_SUCCESS,

	/**
	 * This member indicates that calling method failed
	 * The port reset did not complete because none of the phys are operational
	 */
	SCI_FAILURE_RESET_PORT_FAILURE,

	/**
	 * This member indicates the calling method failed, because the SCI
	 * implementation करोes not contain the specअगरied remote device.
	 */
	SCI_FAILURE_INVALID_REMOTE_DEVICE,

	/**
	 * This member indicates the calling method failed, because the remote
	 * device is in a bad state and requires a reset.
	 */
	SCI_FAILURE_REMOTE_DEVICE_RESET_REQUIRED,

	/**
	 * This member indicates the calling method failed, because the SCI
	 * implementation करोes not contain or support the specअगरied IO tag.
	 */
	SCI_FAILURE_INVALID_IO_TAG,

	/**
	 * This member indicates that the operation failed and the user should
	 * check the response data associated with the IO.
	 */
	SCI_FAILURE_IO_RESPONSE_VALID,

	/**
	 * This member indicates that the operation failed, the failure is
	 * controller implementation specअगरic, and the response data associated
	 * with the request is not valid.  You can query क्रम the controller
	 * specअगरic error inक्रमmation via sci_controller_get_request_status()
	 */
	SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR,

	/**
	 * This member indicated that the operation failed because the
	 * user requested this IO to be terminated.
	 */
	SCI_FAILURE_IO_TERMINATED,

	/**
	 * This member indicates that the operation failed and the associated
	 * request requires a SCSI पात task to be sent to the target.
	 */
	SCI_FAILURE_IO_REQUIRES_SCSI_ABORT,

	/**
	 * This member indicates that the operation failed because the supplied
	 * device could not be located.
	 */
	SCI_FAILURE_DEVICE_NOT_FOUND,

	/**
	 * This member indicates that the operation failed because the
	 * objects association is required and is not correctly set.
	 */
	SCI_FAILURE_INVALID_ASSOCIATION,

	/**
	 * This member indicates that the operation failed, because a समयout
	 * occurred.
	 */
	SCI_FAILURE_TIMEOUT,

	/**
	 * This member indicates that the operation failed, because the user
	 * specअगरied a value that is either invalid or not supported.
	 */
	SCI_FAILURE_INVALID_PARAMETER_VALUE,

	/**
	 * This value indicates that the operation failed, because the number
	 * of messages (MSI-X) is not supported.
	 */
	SCI_FAILURE_UNSUPPORTED_MESSAGE_COUNT,

	/**
	 * This value indicates that the method failed due to a lack of
	 * available NCQ tags.
	 */
	SCI_FAILURE_NO_NCQ_TAG_AVAILABLE,

	/**
	 * This value indicates that a protocol violation has occurred on the
	 * link.
	 */
	SCI_FAILURE_PROTOCOL_VIOLATION,

	/**
	 * This value indicates a failure condition that retry may help to clear.
	 */
	SCI_FAILURE_RETRY_REQUIRED,

	/**
	 * This field indicates the retry limit was reached when a retry is attempted
	 */
	SCI_FAILURE_RETRY_LIMIT_REACHED,

	/**
	 * This member indicates the calling method was partly successful.
	 * Mostly, this status is used when a LUN_RESET issued to an expander attached
	 * STP device in READY NCQ substate needs to have RNC suspended/resumed
	 * beक्रमe posting TC.
	 */
	SCI_FAILURE_RESET_DEVICE_PARTIAL_SUCCESS,

	/**
	 * This field indicates an illegal phy connection based on the routing attribute
	 * of both expander phy attached to each other.
	 */
	SCI_FAILURE_ILLEGAL_ROUTING_ATTRIBUTE_CONFIGURATION,

	/**
	 * This field indicates a CONFIG ROUTE INFO command has a response with function result
	 * INDEX DOES NOT EXIST, usually means exceeding max route index.
	 */
	SCI_FAILURE_EXCEED_MAX_ROUTE_INDEX,

	/**
	 * This value indicates that an unsupported PCI device ID has been
	 * specअगरied.  This indicates that attempts to invoke
	 * sci_library_allocate_controller() will fail.
	 */
	SCI_FAILURE_UNSUPPORTED_PCI_DEVICE_ID

पूर्ण;

/**
 * क्रमागत sci_io_status - This क्रमागतeration depicts all of the possible IO
 *    completion status values.  Each value in this क्रमागतeration maps directly
 *    to a value in the क्रमागत sci_status क्रमागतeration.  Please refer to that
 *    क्रमागतeration क्रम detailed comments concerning what the status represents.
 *
 * Add the API to retrieve the SCU status from the core. Check to see that the
 * following status are properly handled: - SCI_IO_FAILURE_UNSUPPORTED_PROTOCOL
 * - SCI_IO_FAILURE_INVALID_IO_TAG
 */
क्रमागत sci_io_status अणु
	SCI_IO_SUCCESS                         = SCI_SUCCESS,
	SCI_IO_FAILURE                         = SCI_FAILURE,
	SCI_IO_SUCCESS_COMPLETE_BEFORE_START   = SCI_SUCCESS_IO_COMPLETE_BEFORE_START,
	SCI_IO_SUCCESS_IO_DONE_EARLY           = SCI_SUCCESS_IO_DONE_EARLY,
	SCI_IO_FAILURE_INVALID_STATE           = SCI_FAILURE_INVALID_STATE,
	SCI_IO_FAILURE_INSUFFICIENT_RESOURCES  = SCI_FAILURE_INSUFFICIENT_RESOURCES,
	SCI_IO_FAILURE_UNSUPPORTED_PROTOCOL    = SCI_FAILURE_UNSUPPORTED_PROTOCOL,
	SCI_IO_FAILURE_RESPONSE_VALID          = SCI_FAILURE_IO_RESPONSE_VALID,
	SCI_IO_FAILURE_CONTROLLER_SPECIFIC_ERR = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR,
	SCI_IO_FAILURE_TERMINATED              = SCI_FAILURE_IO_TERMINATED,
	SCI_IO_FAILURE_REQUIRES_SCSI_ABORT     = SCI_FAILURE_IO_REQUIRES_SCSI_ABORT,
	SCI_IO_FAILURE_INVALID_PARAMETER_VALUE = SCI_FAILURE_INVALID_PARAMETER_VALUE,
	SCI_IO_FAILURE_NO_NCQ_TAG_AVAILABLE    = SCI_FAILURE_NO_NCQ_TAG_AVAILABLE,
	SCI_IO_FAILURE_PROTOCOL_VIOLATION      = SCI_FAILURE_PROTOCOL_VIOLATION,

	SCI_IO_FAILURE_REMOTE_DEVICE_RESET_REQUIRED = SCI_FAILURE_REMOTE_DEVICE_RESET_REQUIRED,

	SCI_IO_FAILURE_RETRY_REQUIRED      = SCI_FAILURE_RETRY_REQUIRED,
	SCI_IO_FAILURE_RETRY_LIMIT_REACHED = SCI_FAILURE_RETRY_LIMIT_REACHED,
	SCI_IO_FAILURE_INVALID_REMOTE_DEVICE = SCI_FAILURE_INVALID_REMOTE_DEVICE
पूर्ण;

/**
 * क्रमागत sci_task_status - This क्रमागतeration depicts all of the possible task
 *    completion status values.  Each value in this क्रमागतeration maps directly
 *    to a value in the क्रमागत sci_status क्रमागतeration.  Please refer to that
 *    क्रमागतeration क्रम detailed comments concerning what the status represents.
 *
 * Check to see that the following status are properly handled:
 */
क्रमागत sci_task_status अणु
	SCI_TASK_SUCCESS                         = SCI_SUCCESS,
	SCI_TASK_FAILURE                         = SCI_FAILURE,
	SCI_TASK_FAILURE_INVALID_STATE           = SCI_FAILURE_INVALID_STATE,
	SCI_TASK_FAILURE_INSUFFICIENT_RESOURCES  = SCI_FAILURE_INSUFFICIENT_RESOURCES,
	SCI_TASK_FAILURE_UNSUPPORTED_PROTOCOL    = SCI_FAILURE_UNSUPPORTED_PROTOCOL,
	SCI_TASK_FAILURE_INVALID_TAG             = SCI_FAILURE_INVALID_IO_TAG,
	SCI_TASK_FAILURE_RESPONSE_VALID          = SCI_FAILURE_IO_RESPONSE_VALID,
	SCI_TASK_FAILURE_CONTROLLER_SPECIFIC_ERR = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR,
	SCI_TASK_FAILURE_TERMINATED              = SCI_FAILURE_IO_TERMINATED,
	SCI_TASK_FAILURE_INVALID_PARAMETER_VALUE = SCI_FAILURE_INVALID_PARAMETER_VALUE,

	SCI_TASK_FAILURE_REMOTE_DEVICE_RESET_REQUIRED = SCI_FAILURE_REMOTE_DEVICE_RESET_REQUIRED,
	SCI_TASK_FAILURE_RESET_DEVICE_PARTIAL_SUCCESS = SCI_FAILURE_RESET_DEVICE_PARTIAL_SUCCESS

पूर्ण;

/**
 * sci_swab32_cpy - convert between scsi and scu-hardware byte क्रमmat
 * @dest: receive the 4-byte endian swapped version of src
 * @src: word aligned source buffer
 *
 * scu hardware handles SSP/SMP control, response, and unidentअगरied
 * frames in "big endian dword" order.  Regardless of host endian this
 * is always a swab32()-per-dword conversion of the standard definition,
 * i.e. single byte fields swapped and multi-byte fields in little-
 * endian
 */
अटल अंतरभूत व्योम sci_swab32_cpy(व्योम *_dest, व्योम *_src, sमाप_प्रकार word_cnt)
अणु
	u32 *dest = _dest, *src = _src;

	जबतक (--word_cnt >= 0)
		dest[word_cnt] = swab32(src[word_cnt]);
पूर्ण

बाह्य अचिन्हित अक्षर no_outbound_task_to;
बाह्य u16 ssp_max_occ_to;
बाह्य u16 stp_max_occ_to;
बाह्य u16 ssp_inactive_to;
बाह्य u16 stp_inactive_to;
बाह्य अचिन्हित अक्षर phy_gen;
बाह्य अचिन्हित अक्षर max_concurr_spinup;
बाह्य uपूर्णांक cable_selection_override;

irqवापस_t isci_msix_isr(पूर्णांक vec, व्योम *data);
irqवापस_t isci_पूर्णांकx_isr(पूर्णांक vec, व्योम *data);
irqवापस_t isci_error_isr(पूर्णांक vec, व्योम *data);

/*
 * Each समयr is associated with a cancellation flag that is set when
 * del_समयr() is called and checked in the समयr callback function. This
 * is needed since del_समयr_sync() cannot be called with sci_lock held.
 * For deinit however, del_समयr_sync() is used without holding the lock.
 */
काष्ठा sci_समयr अणु
	काष्ठा समयr_list	समयr;
	bool			cancel;
पूर्ण;

अटल अंतरभूत
व्योम sci_init_समयr(काष्ठा sci_समयr *पंचांगr, व्योम (*fn)(काष्ठा समयr_list *t))
अणु
	पंचांगr->cancel = false;
	समयr_setup(&पंचांगr->समयr, fn, 0);
पूर्ण

अटल अंतरभूत व्योम sci_mod_समयr(काष्ठा sci_समयr *पंचांगr, अचिन्हित दीर्घ msec)
अणु
	पंचांगr->cancel = false;
	mod_समयr(&पंचांगr->समयr, jअगरfies + msecs_to_jअगरfies(msec));
पूर्ण

अटल अंतरभूत व्योम sci_del_समयr(काष्ठा sci_समयr *पंचांगr)
अणु
	पंचांगr->cancel = true;
	del_समयr(&पंचांगr->समयr);
पूर्ण

काष्ठा sci_base_state_machine अणु
	स्थिर काष्ठा sci_base_state *state_table;
	u32 initial_state_id;
	u32 current_state_id;
	u32 previous_state_id;
पूर्ण;

प्रकार व्योम (*sci_state_transition_t)(काष्ठा sci_base_state_machine *sm);

काष्ठा sci_base_state अणु
	sci_state_transition_t enter_state;	/* Called on state entry */
	sci_state_transition_t निकास_state;	/* Called on state निकास */
पूर्ण;

बाह्य व्योम sci_init_sm(काष्ठा sci_base_state_machine *sm,
			स्थिर काष्ठा sci_base_state *state_table,
			u32 initial_state);
बाह्य व्योम sci_change_state(काष्ठा sci_base_state_machine *sm, u32 next_state);
#पूर्ण_अगर  /* __ISCI_H__ */
