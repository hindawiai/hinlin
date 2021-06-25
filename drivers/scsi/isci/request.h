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

#अगर_अघोषित _ISCI_REQUEST_H_
#घोषणा _ISCI_REQUEST_H_

#समावेश "isci.h"
#समावेश "host.h"
#समावेश "scu_task_context.h"

/**
 * isci_stp_request - extra request infraकाष्ठाure to handle pio/atapi protocol
 * @pio_len - number of bytes requested at PIO setup
 * @status - pio setup ending status value to tell us अगर we need
 *	     to रुको क्रम another fis or अगर the transfer is complete.  Upon
 *           receipt of a d2h fis this will be the status field of that fis.
 * @sgl - track pio transfer progress as we iterate through the sgl
 */
काष्ठा isci_stp_request अणु
	u32 pio_len;
	u8 status;

	काष्ठा isci_stp_pio_sgl अणु
		पूर्णांक index;
		u8 set;
		u32 offset;
	पूर्ण sgl;
पूर्ण;

काष्ठा isci_request अणु
	#घोषणा IREQ_COMPLETE_IN_TARGET 0
	#घोषणा IREQ_TERMINATED 1
	#घोषणा IREQ_TMF 2
	#घोषणा IREQ_ACTIVE 3
	#घोषणा IREQ_PENDING_ABORT 4 /* Set == device was not suspended yet */
	#घोषणा IREQ_TC_ABORT_POSTED 5
	#घोषणा IREQ_ABORT_PATH_ACTIVE 6
	#घोषणा IREQ_NO_AUTO_FREE_TAG 7 /* Set when being explicitly managed */
	अचिन्हित दीर्घ flags;
	/* XXX समाप्त ttype and ttype_ptr, allocate full sas_task */
	जोड़ ttype_ptr_जोड़ अणु
		काष्ठा sas_task *io_task_ptr;   /* When ttype==io_task  */
		काष्ठा isci_पंचांगf *पंचांगf_task_ptr;  /* When ttype==पंचांगf_task */
	पूर्ण ttype_ptr;
	काष्ठा isci_host *isci_host;
	dma_addr_t request_daddr;
	dma_addr_t zero_scatter_daddr;
	अचिन्हित पूर्णांक num_sg_entries;
	/* Note: "io_request_completion" is completed in two dअगरferent ways
	 * depending on whether this is a TMF or regular request.
	 * - TMF requests are completed in the thपढ़ो that started them;
	 * - regular requests are completed in the request completion callback
	 *   function.
	 * This dअगरference in operation allows the पातer of a TMF request
	 * to be sure that once the TMF request completes, the I/O that the
	 * TMF was पातing is guaranteed to have completed.
	 *
	 * XXX समाप्त io_request_completion
	 */
	काष्ठा completion *io_request_completion;
	काष्ठा sci_base_state_machine sm;
	काष्ठा isci_host *owning_controller;
	काष्ठा isci_remote_device *target_device;
	u16 io_tag;
	क्रमागत sas_protocol protocol;
	u32 scu_status; /* hardware result */
	u32 sci_status; /* upper layer disposition */
	u32 post_context;
	काष्ठा scu_task_context *tc;
	/* could be larger with sg chaining */
	#घोषणा SCU_SGL_SIZE ((SCI_MAX_SCATTER_GATHER_ELEMENTS + 1) / 2)
	काष्ठा scu_sgl_element_pair sg_table[SCU_SGL_SIZE] __attribute__ ((aligned(32)));
	/* This field is a poपूर्णांकer to the stored rx frame data.  It is used in
	 * STP पूर्णांकernal requests and SMP response frames.  If this field is
	 * non-शून्य the saved frame must be released on IO request completion.
	 */
	u32 saved_rx_frame_index;

	जोड़ अणु
		काष्ठा अणु
			जोड़ अणु
				काष्ठा ssp_cmd_iu cmd;
				काष्ठा ssp_task_iu पंचांगf;
			पूर्ण;
			जोड़ अणु
				काष्ठा ssp_response_iu rsp;
				u8 rsp_buf[SSP_RESP_IU_MAX_SIZE];
			पूर्ण;
		पूर्ण ssp;
		काष्ठा अणु
			काष्ठा isci_stp_request req;
			काष्ठा host_to_dev_fis cmd;
			काष्ठा dev_to_host_fis rsp;
		पूर्ण stp;
	पूर्ण;
पूर्ण;

अटल अंतरभूत काष्ठा isci_request *to_ireq(काष्ठा isci_stp_request *stp_req)
अणु
	काष्ठा isci_request *ireq;

	ireq = container_of(stp_req, typeof(*ireq), stp.req);
	वापस ireq;
पूर्ण

/**
 * क्रमागत sci_base_request_states - request state machine states
 *
 * @SCI_REQ_INIT: Simply the initial state क्रम the base request state machine.
 *
 * @SCI_REQ_CONSTRUCTED: This state indicates that the request has been
 * स्थिरructed.  This state is entered from the INITIAL state.
 *
 * @SCI_REQ_STARTED: This state indicates that the request has been started.
 * This state is entered from the CONSTRUCTED state.
 *
 * @SCI_REQ_STP_UDMA_WAIT_TC_COMP:
 * @SCI_REQ_STP_UDMA_WAIT_D2H:
 * @SCI_REQ_STP_NON_DATA_WAIT_H2D:
 * @SCI_REQ_STP_NON_DATA_WAIT_D2H:
 *
 * @SCI_REQ_STP_PIO_WAIT_H2D: While in this state the IO request object is
 * रुकोing क्रम the TC completion notअगरication क्रम the H2D Register FIS
 *
 * @SCI_REQ_STP_PIO_WAIT_FRAME: While in this state the IO request object is
 * रुकोing क्रम either a PIO Setup FIS or a D2H रेजिस्टर FIS.  The type of frame
 * received is based on the result of the prior frame and line conditions.
 *
 * @SCI_REQ_STP_PIO_DATA_IN: While in this state the IO request object is
 * रुकोing क्रम a DATA frame from the device.
 *
 * @SCI_REQ_STP_PIO_DATA_OUT: While in this state the IO request object is
 * रुकोing to transmit the next data frame to the device.
 *
 * @SCI_REQ_ATAPI_WAIT_H2D: While in this state the IO request object is
 * रुकोing क्रम the TC completion notअगरication क्रम the H2D Register FIS
 *
 * @SCI_REQ_ATAPI_WAIT_PIO_SETUP: While in this state the IO request object is
 * रुकोing क्रम either a PIO Setup.
 *
 * @SCI_REQ_ATAPI_WAIT_D2H: The non-data IO transit to this state in this state
 * after receiving TC completion. While in this state IO request object is
 * रुकोing क्रम D2H status frame as UF.
 *
 * @SCI_REQ_ATAPI_WAIT_TC_COMP: When transmitting raw frames hardware reports
 * task context completion after every frame submission, so in the
 * non-accelerated हाल we need to expect the completion क्रम the "cdb" frame.
 *
 * @SCI_REQ_TASK_WAIT_TC_COMP: The AWAIT_TC_COMPLETION sub-state indicates that
 * the started raw task management request is रुकोing क्रम the transmission of
 * the initial frame (i.e. command, task, etc.).
 *
 * @SCI_REQ_TASK_WAIT_TC_RESP: This sub-state indicates that the started task
 * management request is रुकोing क्रम the reception of an unsolicited frame
 * (i.e.  response IU).
 *
 * @SCI_REQ_SMP_WAIT_RESP: This sub-state indicates that the started task
 * management request is रुकोing क्रम the reception of an unsolicited frame
 * (i.e.  response IU).
 *
 * @SCI_REQ_SMP_WAIT_TC_COMP: The AWAIT_TC_COMPLETION sub-state indicates that
 * the started SMP request is रुकोing क्रम the transmission of the initial frame
 * (i.e.  command, task, etc.).
 *
 * @SCI_REQ_COMPLETED: This state indicates that the request has completed.
 * This state is entered from the STARTED state. This state is entered from the
 * ABORTING state.
 *
 * @SCI_REQ_ABORTING: This state indicates that the request is in the process
 * of being terminated/पातed.  This state is entered from the CONSTRUCTED
 * state.  This state is entered from the STARTED state.
 *
 * @SCI_REQ_FINAL: Simply the final state क्रम the base request state machine.
 */
#घोषणा REQUEST_STATES अणु\
	C(REQ_INIT),\
	C(REQ_CONSTRUCTED),\
	C(REQ_STARTED),\
	C(REQ_STP_UDMA_WAIT_TC_COMP),\
	C(REQ_STP_UDMA_WAIT_D2H),\
	C(REQ_STP_NON_DATA_WAIT_H2D),\
	C(REQ_STP_NON_DATA_WAIT_D2H),\
	C(REQ_STP_PIO_WAIT_H2D),\
	C(REQ_STP_PIO_WAIT_FRAME),\
	C(REQ_STP_PIO_DATA_IN),\
	C(REQ_STP_PIO_DATA_OUT),\
	C(REQ_ATAPI_WAIT_H2D),\
	C(REQ_ATAPI_WAIT_PIO_SETUP),\
	C(REQ_ATAPI_WAIT_D2H),\
	C(REQ_ATAPI_WAIT_TC_COMP),\
	C(REQ_TASK_WAIT_TC_COMP),\
	C(REQ_TASK_WAIT_TC_RESP),\
	C(REQ_SMP_WAIT_RESP),\
	C(REQ_SMP_WAIT_TC_COMP),\
	C(REQ_COMPLETED),\
	C(REQ_ABORTING),\
	C(REQ_FINAL),\
	पूर्ण
#अघोषित C
#घोषणा C(a) SCI_##a
क्रमागत sci_base_request_states REQUEST_STATES;
#अघोषित C
स्थिर अक्षर *req_state_name(क्रमागत sci_base_request_states state);

क्रमागत sci_status sci_request_start(काष्ठा isci_request *ireq);
क्रमागत sci_status sci_io_request_terminate(काष्ठा isci_request *ireq);
क्रमागत sci_status
sci_io_request_event_handler(काष्ठा isci_request *ireq,
				  u32 event_code);
क्रमागत sci_status
sci_io_request_frame_handler(काष्ठा isci_request *ireq,
				  u32 frame_index);
क्रमागत sci_status
sci_task_request_terminate(काष्ठा isci_request *ireq);
बाह्य क्रमागत sci_status
sci_request_complete(काष्ठा isci_request *ireq);
बाह्य क्रमागत sci_status
sci_io_request_tc_completion(काष्ठा isci_request *ireq, u32 code);

/* XXX खोलो code in caller */
अटल अंतरभूत dma_addr_t
sci_io_request_get_dma_addr(काष्ठा isci_request *ireq, व्योम *virt_addr)
अणु

	अक्षर *requested_addr = (अक्षर *)virt_addr;
	अक्षर *base_addr = (अक्षर *)ireq;

	BUG_ON(requested_addr < base_addr);
	BUG_ON((requested_addr - base_addr) >= माप(*ireq));

	वापस ireq->request_daddr + (requested_addr - base_addr);
पूर्ण

#घोषणा isci_request_access_task(req) ((req)->ttype_ptr.io_task_ptr)

#घोषणा isci_request_access_पंचांगf(req) ((req)->ttype_ptr.पंचांगf_task_ptr)

काष्ठा isci_request *isci_पंचांगf_request_from_tag(काष्ठा isci_host *ihost,
					       काष्ठा isci_पंचांगf *isci_पंचांगf,
					       u16 tag);
पूर्णांक isci_request_execute(काष्ठा isci_host *ihost, काष्ठा isci_remote_device *idev,
			 काष्ठा sas_task *task, u16 tag);
क्रमागत sci_status
sci_task_request_स्थिरruct(काष्ठा isci_host *ihost,
			    काष्ठा isci_remote_device *idev,
			    u16 io_tag,
			    काष्ठा isci_request *ireq);
क्रमागत sci_status sci_task_request_स्थिरruct_ssp(काष्ठा isci_request *ireq);
व्योम sci_smp_request_copy_response(काष्ठा isci_request *ireq);

अटल अंतरभूत पूर्णांक isci_task_is_ncq_recovery(काष्ठा sas_task *task)
अणु
	वापस (sas_protocol_ata(task->task_proto) &&
		task->ata_task.fis.command == ATA_CMD_READ_LOG_EXT &&
		task->ata_task.fis.lbal == ATA_LOG_SATA_NCQ);

पूर्ण
#पूर्ण_अगर /* !defined(_ISCI_REQUEST_H_) */
