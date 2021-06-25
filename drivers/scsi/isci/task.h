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
#अगर_अघोषित _ISCI_TASK_H_
#घोषणा _ISCI_TASK_H_

#समावेश <scsi/sas_ata.h>
#समावेश "host.h"

#घोषणा ISCI_TERMINATION_TIMEOUT_MSEC 500

काष्ठा isci_request;

/**
 * क्रमागत isci_पंचांगf_function_codes - This क्रमागत defines the possible preparations
 *    of task management requests.
 *
 *
 */
क्रमागत isci_पंचांगf_function_codes अणु

	isci_पंचांगf_func_none      = 0,
	isci_पंचांगf_ssp_task_पात = TMF_ABORT_TASK,
	isci_पंचांगf_ssp_lun_reset  = TMF_LU_RESET,
पूर्ण;

/**
 * काष्ठा isci_पंचांगf - This class represents the task management object which
 *    acts as an पूर्णांकerface to libsas क्रम processing task management requests
 *
 *
 */
काष्ठा isci_पंचांगf अणु

	काष्ठा completion *complete;
	क्रमागत sas_protocol proto;
	जोड़ अणु
		काष्ठा ssp_response_iu resp_iu;
		काष्ठा dev_to_host_fis d2h_fis;
		u8 rsp_buf[SSP_RESP_IU_MAX_SIZE];
	पूर्ण resp;
	अचिन्हित अक्षर lun[8];
	u16 io_tag;
	क्रमागत isci_पंचांगf_function_codes पंचांगf_code;
	पूर्णांक status;
पूर्ण;

अटल अंतरभूत व्योम isci_prपूर्णांक_पंचांगf(काष्ठा isci_host *ihost, काष्ठा isci_पंचांगf *पंचांगf)
अणु
	अगर (SAS_PROTOCOL_SATA == पंचांगf->proto)
		dev_dbg(&ihost->pdev->dev,
			"%s: status = %x\n"
			"tmf->resp.d2h_fis.status = %x\n"
			"tmf->resp.d2h_fis.error = %x\n",
			__func__,
			पंचांगf->status,
			पंचांगf->resp.d2h_fis.status,
			पंचांगf->resp.d2h_fis.error);
	अन्यथा
		dev_dbg(&ihost->pdev->dev,
			"%s: status = %x\n"
			"tmf->resp.resp_iu.data_present = %x\n"
			"tmf->resp.resp_iu.status = %x\n"
			"tmf->resp.resp_iu.data_length = %x\n"
			"tmf->resp.resp_iu.data[0] = %x\n"
			"tmf->resp.resp_iu.data[1] = %x\n"
			"tmf->resp.resp_iu.data[2] = %x\n"
			"tmf->resp.resp_iu.data[3] = %x\n",
			__func__,
			पंचांगf->status,
			पंचांगf->resp.resp_iu.datapres,
			पंचांगf->resp.resp_iu.status,
			be32_to_cpu(पंचांगf->resp.resp_iu.response_data_len),
			पंचांगf->resp.resp_iu.resp_data[0],
			पंचांगf->resp.resp_iu.resp_data[1],
			पंचांगf->resp.resp_iu.resp_data[2],
			पंचांगf->resp.resp_iu.resp_data[3]);
पूर्ण


पूर्णांक isci_task_execute_task(
	काष्ठा sas_task *task,
	gfp_t gfp_flags);

पूर्णांक isci_task_पात_task(
	काष्ठा sas_task *task);

पूर्णांक isci_task_पात_task_set(
	काष्ठा करोमुख्य_device *d_device,
	u8 *lun);

पूर्णांक isci_task_clear_aca(
	काष्ठा करोमुख्य_device *d_device,
	u8 *lun);

पूर्णांक isci_task_clear_task_set(
	काष्ठा करोमुख्य_device *d_device,
	u8 *lun);

पूर्णांक isci_task_query_task(
	काष्ठा sas_task *task);

पूर्णांक isci_task_lu_reset(
	काष्ठा करोमुख्य_device *d_device,
	u8 *lun);

पूर्णांक isci_task_clear_nexus_port(
	काष्ठा asd_sas_port *port);

पूर्णांक isci_task_clear_nexus_ha(
	काष्ठा sas_ha_काष्ठा *ha);

पूर्णांक isci_task_I_T_nexus_reset(
	काष्ठा करोमुख्य_device *d_device);

व्योम isci_task_request_complete(
	काष्ठा isci_host *isci_host,
	काष्ठा isci_request *request,
	क्रमागत sci_task_status completion_status);

u16 isci_task_ssp_request_get_io_tag_to_manage(
	काष्ठा isci_request *request);

u8 isci_task_ssp_request_get_function(
	काष्ठा isci_request *request);


व्योम *isci_task_ssp_request_get_response_data_address(
	काष्ठा isci_request *request);

u32 isci_task_ssp_request_get_response_data_length(
	काष्ठा isci_request *request);

पूर्णांक isci_queuecommand(
	काष्ठा scsi_cmnd *scsi_cmd,
	व्योम (*करोnefunc)(काष्ठा scsi_cmnd *));

#पूर्ण_अगर /* !defined(_SCI_TASK_H_) */
