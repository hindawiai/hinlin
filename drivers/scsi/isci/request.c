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

#समावेश <scsi/scsi_cmnd.h>
#समावेश "isci.h"
#समावेश "task.h"
#समावेश "request.h"
#समावेश "scu_completion_codes.h"
#समावेश "scu_event_codes.h"
#समावेश "sas.h"

#अघोषित C
#घोषणा C(a) (#a)
स्थिर अक्षर *req_state_name(क्रमागत sci_base_request_states state)
अणु
	अटल स्थिर अक्षर * स्थिर strings[] = REQUEST_STATES;

	वापस strings[state];
पूर्ण
#अघोषित C

अटल काष्ठा scu_sgl_element_pair *to_sgl_element_pair(काष्ठा isci_request *ireq,
							पूर्णांक idx)
अणु
	अगर (idx == 0)
		वापस &ireq->tc->sgl_pair_ab;
	अन्यथा अगर (idx == 1)
		वापस &ireq->tc->sgl_pair_cd;
	अन्यथा अगर (idx < 0)
		वापस शून्य;
	अन्यथा
		वापस &ireq->sg_table[idx - 2];
पूर्ण

अटल dma_addr_t to_sgl_element_pair_dma(काष्ठा isci_host *ihost,
					  काष्ठा isci_request *ireq, u32 idx)
अणु
	u32 offset;

	अगर (idx == 0) अणु
		offset = (व्योम *) &ireq->tc->sgl_pair_ab -
			 (व्योम *) &ihost->task_context_table[0];
		वापस ihost->tc_dma + offset;
	पूर्ण अन्यथा अगर (idx == 1) अणु
		offset = (व्योम *) &ireq->tc->sgl_pair_cd -
			 (व्योम *) &ihost->task_context_table[0];
		वापस ihost->tc_dma + offset;
	पूर्ण

	वापस sci_io_request_get_dma_addr(ireq, &ireq->sg_table[idx - 2]);
पूर्ण

अटल व्योम init_sgl_element(काष्ठा scu_sgl_element *e, काष्ठा scatterlist *sg)
अणु
	e->length = sg_dma_len(sg);
	e->address_upper = upper_32_bits(sg_dma_address(sg));
	e->address_lower = lower_32_bits(sg_dma_address(sg));
	e->address_modअगरier = 0;
पूर्ण

अटल व्योम sci_request_build_sgl(काष्ठा isci_request *ireq)
अणु
	काष्ठा isci_host *ihost = ireq->isci_host;
	काष्ठा sas_task *task = isci_request_access_task(ireq);
	काष्ठा scatterlist *sg = शून्य;
	dma_addr_t dma_addr;
	u32 sg_idx = 0;
	काष्ठा scu_sgl_element_pair *scu_sg   = शून्य;
	काष्ठा scu_sgl_element_pair *prev_sg  = शून्य;

	अगर (task->num_scatter > 0) अणु
		sg = task->scatter;

		जबतक (sg) अणु
			scu_sg = to_sgl_element_pair(ireq, sg_idx);
			init_sgl_element(&scu_sg->A, sg);
			sg = sg_next(sg);
			अगर (sg) अणु
				init_sgl_element(&scu_sg->B, sg);
				sg = sg_next(sg);
			पूर्ण अन्यथा
				स_रखो(&scu_sg->B, 0, माप(scu_sg->B));

			अगर (prev_sg) अणु
				dma_addr = to_sgl_element_pair_dma(ihost,
								   ireq,
								   sg_idx);

				prev_sg->next_pair_upper =
					upper_32_bits(dma_addr);
				prev_sg->next_pair_lower =
					lower_32_bits(dma_addr);
			पूर्ण

			prev_sg = scu_sg;
			sg_idx++;
		पूर्ण
	पूर्ण अन्यथा अणु	/* handle when no sg */
		scu_sg = to_sgl_element_pair(ireq, sg_idx);

		dma_addr = dma_map_single(&ihost->pdev->dev,
					  task->scatter,
					  task->total_xfer_len,
					  task->data_dir);

		ireq->zero_scatter_daddr = dma_addr;

		scu_sg->A.length = task->total_xfer_len;
		scu_sg->A.address_upper = upper_32_bits(dma_addr);
		scu_sg->A.address_lower = lower_32_bits(dma_addr);
	पूर्ण

	अगर (scu_sg) अणु
		scu_sg->next_pair_upper = 0;
		scu_sg->next_pair_lower = 0;
	पूर्ण
पूर्ण

अटल व्योम sci_io_request_build_ssp_command_iu(काष्ठा isci_request *ireq)
अणु
	काष्ठा ssp_cmd_iu *cmd_iu;
	काष्ठा sas_task *task = isci_request_access_task(ireq);

	cmd_iu = &ireq->ssp.cmd;

	स_नकल(cmd_iu->LUN, task->ssp_task.LUN, 8);
	cmd_iu->add_cdb_len = 0;
	cmd_iu->_r_a = 0;
	cmd_iu->_r_b = 0;
	cmd_iu->en_fburst = 0; /* unsupported */
	cmd_iu->task_prio = task->ssp_task.task_prio;
	cmd_iu->task_attr = task->ssp_task.task_attr;
	cmd_iu->_r_c = 0;

	sci_swab32_cpy(&cmd_iu->cdb, task->ssp_task.cmd->cmnd,
		       (task->ssp_task.cmd->cmd_len+3) / माप(u32));
पूर्ण

अटल व्योम sci_task_request_build_ssp_task_iu(काष्ठा isci_request *ireq)
अणु
	काष्ठा ssp_task_iu *task_iu;
	काष्ठा sas_task *task = isci_request_access_task(ireq);
	काष्ठा isci_पंचांगf *isci_पंचांगf = isci_request_access_पंचांगf(ireq);

	task_iu = &ireq->ssp.पंचांगf;

	स_रखो(task_iu, 0, माप(काष्ठा ssp_task_iu));

	स_नकल(task_iu->LUN, task->ssp_task.LUN, 8);

	task_iu->task_func = isci_पंचांगf->पंचांगf_code;
	task_iu->task_tag =
		(test_bit(IREQ_TMF, &ireq->flags)) ?
		isci_पंचांगf->io_tag :
		SCI_CONTROLLER_INVALID_IO_TAG;
पूर्ण

/*
 * This method is will fill in the SCU Task Context क्रम any type of SSP request.
 */
अटल व्योम scu_ssp_request_स्थिरruct_task_context(
	काष्ठा isci_request *ireq,
	काष्ठा scu_task_context *task_context)
अणु
	dma_addr_t dma_addr;
	काष्ठा isci_remote_device *idev;
	काष्ठा isci_port *iport;

	idev = ireq->target_device;
	iport = idev->owning_port;

	/* Fill in the TC with its required data */
	task_context->पात = 0;
	task_context->priority = 0;
	task_context->initiator_request = 1;
	task_context->connection_rate = idev->connection_rate;
	task_context->protocol_engine_index = ISCI_PEG;
	task_context->logical_port_index = iport->physical_port_index;
	task_context->protocol_type = SCU_TASK_CONTEXT_PROTOCOL_SSP;
	task_context->valid = SCU_TASK_CONTEXT_VALID;
	task_context->context_type = SCU_TASK_CONTEXT_TYPE;

	task_context->remote_node_index = idev->rnc.remote_node_index;
	task_context->command_code = 0;

	task_context->link_layer_control = 0;
	task_context->करो_not_dma_ssp_good_response = 1;
	task_context->strict_ordering = 0;
	task_context->control_frame = 0;
	task_context->समयout_enable = 0;
	task_context->block_guard_enable = 0;

	task_context->address_modअगरier = 0;

	/* task_context->type.ssp.tag = ireq->io_tag; */
	task_context->task_phase = 0x01;

	ireq->post_context = (SCU_CONTEXT_COMMAND_REQUEST_TYPE_POST_TC |
			      (ISCI_PEG << SCU_CONTEXT_COMMAND_PROTOCOL_ENGINE_GROUP_SHIFT) |
			      (iport->physical_port_index <<
			       SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT) |
			      ISCI_TAG_TCI(ireq->io_tag));

	/*
	 * Copy the physical address क्रम the command buffer to the
	 * SCU Task Context
	 */
	dma_addr = sci_io_request_get_dma_addr(ireq, &ireq->ssp.cmd);

	task_context->command_iu_upper = upper_32_bits(dma_addr);
	task_context->command_iu_lower = lower_32_bits(dma_addr);

	/*
	 * Copy the physical address क्रम the response buffer to the
	 * SCU Task Context
	 */
	dma_addr = sci_io_request_get_dma_addr(ireq, &ireq->ssp.rsp);

	task_context->response_iu_upper = upper_32_bits(dma_addr);
	task_context->response_iu_lower = lower_32_bits(dma_addr);
पूर्ण

अटल u8 scu_bg_blk_size(काष्ठा scsi_device *sdp)
अणु
	चयन (sdp->sector_size) अणु
	हाल 512:
		वापस 0;
	हाल 1024:
		वापस 1;
	हाल 4096:
		वापस 3;
	शेष:
		वापस 0xff;
	पूर्ण
पूर्ण

अटल u32 scu_dअगर_bytes(u32 len, u32 sector_size)
अणु
	वापस (len >> ilog2(sector_size)) * 8;
पूर्ण

अटल व्योम scu_ssp_ireq_dअगर_insert(काष्ठा isci_request *ireq, u8 type, u8 op)
अणु
	काष्ठा scu_task_context *tc = ireq->tc;
	काष्ठा scsi_cmnd *scmd = ireq->ttype_ptr.io_task_ptr->uldd_task;
	u8 blk_sz = scu_bg_blk_size(scmd->device);

	tc->block_guard_enable = 1;
	tc->blk_prot_en = 1;
	tc->blk_sz = blk_sz;
	/* DIF ग_लिखो insert */
	tc->blk_prot_func = 0x2;

	tc->transfer_length_bytes += scu_dअगर_bytes(tc->transfer_length_bytes,
						   scmd->device->sector_size);

	/* always init to 0, used by hw */
	tc->पूर्णांकerm_crc_val = 0;

	tc->init_crc_seed = 0;
	tc->app_tag_verअगरy = 0;
	tc->app_tag_gen = 0;
	tc->ref_tag_seed_verअगरy = 0;

	/* always init to same as bg_blk_sz */
	tc->UD_bytes_immed_val = scmd->device->sector_size;

	tc->reserved_DC_0 = 0;

	/* always init to 8 */
	tc->DIF_bytes_immed_val = 8;

	tc->reserved_DC_1 = 0;
	tc->bgc_blk_sz = scmd->device->sector_size;
	tc->reserved_E0_0 = 0;
	tc->app_tag_gen_mask = 0;

	/** setup block guard control **/
	tc->bgctl = 0;

	/* DIF ग_लिखो insert */
	tc->bgctl_f.op = 0x2;

	tc->app_tag_verअगरy_mask = 0;

	/* must init to 0 क्रम hw */
	tc->blk_guard_err = 0;

	tc->reserved_E8_0 = 0;

	अगर ((type & SCSI_PROT_DIF_TYPE1) || (type & SCSI_PROT_DIF_TYPE2))
		tc->ref_tag_seed_gen = scsi_get_lba(scmd) & 0xffffffff;
	अन्यथा अगर (type & SCSI_PROT_DIF_TYPE3)
		tc->ref_tag_seed_gen = 0;
पूर्ण

अटल व्योम scu_ssp_ireq_dअगर_strip(काष्ठा isci_request *ireq, u8 type, u8 op)
अणु
	काष्ठा scu_task_context *tc = ireq->tc;
	काष्ठा scsi_cmnd *scmd = ireq->ttype_ptr.io_task_ptr->uldd_task;
	u8 blk_sz = scu_bg_blk_size(scmd->device);

	tc->block_guard_enable = 1;
	tc->blk_prot_en = 1;
	tc->blk_sz = blk_sz;
	/* DIF पढ़ो strip */
	tc->blk_prot_func = 0x1;

	tc->transfer_length_bytes += scu_dअगर_bytes(tc->transfer_length_bytes,
						   scmd->device->sector_size);

	/* always init to 0, used by hw */
	tc->पूर्णांकerm_crc_val = 0;

	tc->init_crc_seed = 0;
	tc->app_tag_verअगरy = 0;
	tc->app_tag_gen = 0;

	अगर ((type & SCSI_PROT_DIF_TYPE1) || (type & SCSI_PROT_DIF_TYPE2))
		tc->ref_tag_seed_verअगरy = scsi_get_lba(scmd) & 0xffffffff;
	अन्यथा अगर (type & SCSI_PROT_DIF_TYPE3)
		tc->ref_tag_seed_verअगरy = 0;

	/* always init to same as bg_blk_sz */
	tc->UD_bytes_immed_val = scmd->device->sector_size;

	tc->reserved_DC_0 = 0;

	/* always init to 8 */
	tc->DIF_bytes_immed_val = 8;

	tc->reserved_DC_1 = 0;
	tc->bgc_blk_sz = scmd->device->sector_size;
	tc->reserved_E0_0 = 0;
	tc->app_tag_gen_mask = 0;

	/** setup block guard control **/
	tc->bgctl = 0;

	/* DIF पढ़ो strip */
	tc->bgctl_f.crc_verअगरy = 1;
	tc->bgctl_f.op = 0x1;
	अगर ((type & SCSI_PROT_DIF_TYPE1) || (type & SCSI_PROT_DIF_TYPE2)) अणु
		tc->bgctl_f.ref_tag_chk = 1;
		tc->bgctl_f.app_f_detect = 1;
	पूर्ण अन्यथा अगर (type & SCSI_PROT_DIF_TYPE3)
		tc->bgctl_f.app_ref_f_detect = 1;

	tc->app_tag_verअगरy_mask = 0;

	/* must init to 0 क्रम hw */
	tc->blk_guard_err = 0;

	tc->reserved_E8_0 = 0;
	tc->ref_tag_seed_gen = 0;
पूर्ण

/*
 * This method is will fill in the SCU Task Context क्रम a SSP IO request.
 */
अटल व्योम scu_ssp_io_request_स्थिरruct_task_context(काष्ठा isci_request *ireq,
						      क्रमागत dma_data_direction dir,
						      u32 len)
अणु
	काष्ठा scu_task_context *task_context = ireq->tc;
	काष्ठा sas_task *sas_task = ireq->ttype_ptr.io_task_ptr;
	काष्ठा scsi_cmnd *scmd = sas_task->uldd_task;
	u8 prot_type = scsi_get_prot_type(scmd);
	u8 prot_op = scsi_get_prot_op(scmd);

	scu_ssp_request_स्थिरruct_task_context(ireq, task_context);

	task_context->ssp_command_iu_length =
		माप(काष्ठा ssp_cmd_iu) / माप(u32);
	task_context->type.ssp.frame_type = SSP_COMMAND;

	चयन (dir) अणु
	हाल DMA_FROM_DEVICE:
	हाल DMA_NONE:
	शेष:
		task_context->task_type = SCU_TASK_TYPE_IOREAD;
		अवरोध;
	हाल DMA_TO_DEVICE:
		task_context->task_type = SCU_TASK_TYPE_IOWRITE;
		अवरोध;
	पूर्ण

	task_context->transfer_length_bytes = len;

	अगर (task_context->transfer_length_bytes > 0)
		sci_request_build_sgl(ireq);

	अगर (prot_type != SCSI_PROT_DIF_TYPE0) अणु
		अगर (prot_op == SCSI_PROT_READ_STRIP)
			scu_ssp_ireq_dअगर_strip(ireq, prot_type, prot_op);
		अन्यथा अगर (prot_op == SCSI_PROT_WRITE_INSERT)
			scu_ssp_ireq_dअगर_insert(ireq, prot_type, prot_op);
	पूर्ण
पूर्ण

/**
 * scu_ssp_task_request_स्थिरruct_task_context() - This method will fill in
 *    the SCU Task Context क्रम a SSP Task request.  The following important
 *    settings are utilized: -# priority == SCU_TASK_PRIORITY_HIGH.  This
 *    ensures that the task request is issued ahead of other task destined
 *    क्रम the same Remote Node. -# task_type == SCU_TASK_TYPE_IOREAD.  This
 *    simply indicates that a normal request type (i.e. non-raw frame) is
 *    being utilized to perक्रमm task management. -#control_frame == 1.  This
 *    ensures that the proper endianness is set so that the bytes are
 *    transmitted in the right order क्रम a task frame.
 * @ireq: This parameter specअगरies the task request object being स्थिरructed.
 */
अटल व्योम scu_ssp_task_request_स्थिरruct_task_context(काष्ठा isci_request *ireq)
अणु
	काष्ठा scu_task_context *task_context = ireq->tc;

	scu_ssp_request_स्थिरruct_task_context(ireq, task_context);

	task_context->control_frame                = 1;
	task_context->priority                     = SCU_TASK_PRIORITY_HIGH;
	task_context->task_type                    = SCU_TASK_TYPE_RAW_FRAME;
	task_context->transfer_length_bytes        = 0;
	task_context->type.ssp.frame_type          = SSP_TASK;
	task_context->ssp_command_iu_length =
		माप(काष्ठा ssp_task_iu) / माप(u32);
पूर्ण

/**
 * scu_sata_request_स्थिरruct_task_context()
 * This method is will fill in the SCU Task Context क्रम any type of SATA
 *    request.  This is called from the various SATA स्थिरructors.
 * @ireq: The general IO request object which is to be used in
 *    स्थिरructing the SCU task context.
 * @task_context: The buffer poपूर्णांकer क्रम the SCU task context which is being
 *    स्थिरructed.
 *
 * The general io request स्थिरruction is complete. The buffer assignment क्रम
 * the command buffer is complete. none Revisit task context स्थिरruction to
 * determine what is common क्रम SSP/SMP/STP task context काष्ठाures.
 */
अटल व्योम scu_sata_request_स्थिरruct_task_context(
	काष्ठा isci_request *ireq,
	काष्ठा scu_task_context *task_context)
अणु
	dma_addr_t dma_addr;
	काष्ठा isci_remote_device *idev;
	काष्ठा isci_port *iport;

	idev = ireq->target_device;
	iport = idev->owning_port;

	/* Fill in the TC with its required data */
	task_context->पात = 0;
	task_context->priority = SCU_TASK_PRIORITY_NORMAL;
	task_context->initiator_request = 1;
	task_context->connection_rate = idev->connection_rate;
	task_context->protocol_engine_index = ISCI_PEG;
	task_context->logical_port_index = iport->physical_port_index;
	task_context->protocol_type = SCU_TASK_CONTEXT_PROTOCOL_STP;
	task_context->valid = SCU_TASK_CONTEXT_VALID;
	task_context->context_type = SCU_TASK_CONTEXT_TYPE;

	task_context->remote_node_index = idev->rnc.remote_node_index;
	task_context->command_code = 0;

	task_context->link_layer_control = 0;
	task_context->करो_not_dma_ssp_good_response = 1;
	task_context->strict_ordering = 0;
	task_context->control_frame = 0;
	task_context->समयout_enable = 0;
	task_context->block_guard_enable = 0;

	task_context->address_modअगरier = 0;
	task_context->task_phase = 0x01;

	task_context->ssp_command_iu_length =
		(माप(काष्ठा host_to_dev_fis) - माप(u32)) / माप(u32);

	/* Set the first word of the H2D REG FIS */
	task_context->type.words[0] = *(u32 *)&ireq->stp.cmd;

	ireq->post_context = (SCU_CONTEXT_COMMAND_REQUEST_TYPE_POST_TC |
			      (ISCI_PEG << SCU_CONTEXT_COMMAND_PROTOCOL_ENGINE_GROUP_SHIFT) |
			      (iport->physical_port_index <<
			       SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT) |
			      ISCI_TAG_TCI(ireq->io_tag));
	/*
	 * Copy the physical address क्रम the command buffer to the SCU Task
	 * Context. We must offset the command buffer by 4 bytes because the
	 * first 4 bytes are transfered in the body of the TC.
	 */
	dma_addr = sci_io_request_get_dma_addr(ireq,
						((अक्षर *) &ireq->stp.cmd) +
						माप(u32));

	task_context->command_iu_upper = upper_32_bits(dma_addr);
	task_context->command_iu_lower = lower_32_bits(dma_addr);

	/* SATA Requests करो not have a response buffer */
	task_context->response_iu_upper = 0;
	task_context->response_iu_lower = 0;
पूर्ण

अटल व्योम scu_stp_raw_request_स्थिरruct_task_context(काष्ठा isci_request *ireq)
अणु
	काष्ठा scu_task_context *task_context = ireq->tc;

	scu_sata_request_स्थिरruct_task_context(ireq, task_context);

	task_context->control_frame         = 0;
	task_context->priority              = SCU_TASK_PRIORITY_NORMAL;
	task_context->task_type             = SCU_TASK_TYPE_SATA_RAW_FRAME;
	task_context->type.stp.fis_type     = FIS_REGH2D;
	task_context->transfer_length_bytes = माप(काष्ठा host_to_dev_fis) - माप(u32);
पूर्ण

अटल क्रमागत sci_status sci_stp_pio_request_स्थिरruct(काष्ठा isci_request *ireq,
							  bool copy_rx_frame)
अणु
	काष्ठा isci_stp_request *stp_req = &ireq->stp.req;

	scu_stp_raw_request_स्थिरruct_task_context(ireq);

	stp_req->status = 0;
	stp_req->sgl.offset = 0;
	stp_req->sgl.set = SCU_SGL_ELEMENT_PAIR_A;

	अगर (copy_rx_frame) अणु
		sci_request_build_sgl(ireq);
		stp_req->sgl.index = 0;
	पूर्ण अन्यथा अणु
		/* The user करोes not want the data copied to the SGL buffer location */
		stp_req->sgl.index = -1;
	पूर्ण

	वापस SCI_SUCCESS;
पूर्ण

/*
 * sci_stp_optimized_request_स्थिरruct()
 * @ireq: This parameter specअगरies the request to be स्थिरructed as an
 *    optimized request.
 * @optimized_task_type: This parameter specअगरies whether the request is to be
 *    an UDMA request or a NCQ request. - A value of 0 indicates UDMA. - A
 *    value of 1 indicates NCQ.
 *
 * This method will perक्रमm request स्थिरruction common to all types of STP
 * requests that are optimized by the silicon (i.e. UDMA, NCQ). This method
 * वापसs an indication as to whether the स्थिरruction was successful.
 */
अटल व्योम sci_stp_optimized_request_स्थिरruct(काष्ठा isci_request *ireq,
						     u8 optimized_task_type,
						     u32 len,
						     क्रमागत dma_data_direction dir)
अणु
	काष्ठा scu_task_context *task_context = ireq->tc;

	/* Build the STP task context काष्ठाure */
	scu_sata_request_स्थिरruct_task_context(ireq, task_context);

	/* Copy over the SGL elements */
	sci_request_build_sgl(ireq);

	/* Copy over the number of bytes to be transfered */
	task_context->transfer_length_bytes = len;

	अगर (dir == DMA_TO_DEVICE) अणु
		/*
		 * The dअगरference between the DMA IN and DMA OUT request task type
		 * values are consistent with the dअगरference between FPDMA READ
		 * and FPDMA WRITE values.  Add the supplied task type parameter
		 * to this dअगरference to set the task type properly क्रम this
		 * DATA OUT (WRITE) हाल. */
		task_context->task_type = optimized_task_type + (SCU_TASK_TYPE_DMA_OUT
								 - SCU_TASK_TYPE_DMA_IN);
	पूर्ण अन्यथा अणु
		/*
		 * For the DATA IN (READ) हाल, simply save the supplied
		 * optimized task type. */
		task_context->task_type = optimized_task_type;
	पूर्ण
पूर्ण

अटल व्योम sci_atapi_स्थिरruct(काष्ठा isci_request *ireq)
अणु
	काष्ठा host_to_dev_fis *h2d_fis = &ireq->stp.cmd;
	काष्ठा sas_task *task;

	/* To simplअगरy the implementation we take advantage of the
	 * silicon's partial acceleration of atapi protocol (dma data
	 * transfers), so we promote all commands to dma protocol.  This
	 * अवरोधs compatibility with ATA_HORKAGE_ATAPI_MOD16_DMA drives.
	 */
	h2d_fis->features |= ATAPI_PKT_DMA;

	scu_stp_raw_request_स्थिरruct_task_context(ireq);

	task = isci_request_access_task(ireq);
	अगर (task->data_dir == DMA_NONE)
		task->total_xfer_len = 0;

	/* clear the response so we can detect arrivial of an
	 * unsolicited h2d fis
	 */
	ireq->stp.rsp.fis_type = 0;
पूर्ण

अटल क्रमागत sci_status
sci_io_request_स्थिरruct_sata(काष्ठा isci_request *ireq,
			       u32 len,
			       क्रमागत dma_data_direction dir,
			       bool copy)
अणु
	क्रमागत sci_status status = SCI_SUCCESS;
	काष्ठा sas_task *task = isci_request_access_task(ireq);
	काष्ठा करोमुख्य_device *dev = ireq->target_device->करोमुख्य_dev;

	/* check क्रम management protocols */
	अगर (test_bit(IREQ_TMF, &ireq->flags)) अणु
		काष्ठा isci_पंचांगf *पंचांगf = isci_request_access_पंचांगf(ireq);

		dev_err(&ireq->owning_controller->pdev->dev,
			"%s: Request 0x%p received un-handled SAT "
			"management protocol 0x%x.\n",
			__func__, ireq, पंचांगf->पंचांगf_code);

		वापस SCI_FAILURE;
	पूर्ण

	अगर (!sas_protocol_ata(task->task_proto)) अणु
		dev_err(&ireq->owning_controller->pdev->dev,
			"%s: Non-ATA protocol in SATA path: 0x%x\n",
			__func__,
			task->task_proto);
		वापस SCI_FAILURE;

	पूर्ण

	/* ATAPI */
	अगर (dev->sata_dev.class == ATA_DEV_ATAPI &&
	    task->ata_task.fis.command == ATA_CMD_PACKET) अणु
		sci_atapi_स्थिरruct(ireq);
		वापस SCI_SUCCESS;
	पूर्ण

	/* non data */
	अगर (task->data_dir == DMA_NONE) अणु
		scu_stp_raw_request_स्थिरruct_task_context(ireq);
		वापस SCI_SUCCESS;
	पूर्ण

	/* NCQ */
	अगर (task->ata_task.use_ncq) अणु
		sci_stp_optimized_request_स्थिरruct(ireq,
							 SCU_TASK_TYPE_FPDMAQ_READ,
							 len, dir);
		वापस SCI_SUCCESS;
	पूर्ण

	/* DMA */
	अगर (task->ata_task.dma_xfer) अणु
		sci_stp_optimized_request_स्थिरruct(ireq,
							 SCU_TASK_TYPE_DMA_IN,
							 len, dir);
		वापस SCI_SUCCESS;
	पूर्ण अन्यथा /* PIO */
		वापस sci_stp_pio_request_स्थिरruct(ireq, copy);

	वापस status;
पूर्ण

अटल क्रमागत sci_status sci_io_request_स्थिरruct_basic_ssp(काष्ठा isci_request *ireq)
अणु
	काष्ठा sas_task *task = isci_request_access_task(ireq);

	ireq->protocol = SAS_PROTOCOL_SSP;

	scu_ssp_io_request_स्थिरruct_task_context(ireq,
						  task->data_dir,
						  task->total_xfer_len);

	sci_io_request_build_ssp_command_iu(ireq);

	sci_change_state(&ireq->sm, SCI_REQ_CONSTRUCTED);

	वापस SCI_SUCCESS;
पूर्ण

क्रमागत sci_status sci_task_request_स्थिरruct_ssp(
	काष्ठा isci_request *ireq)
अणु
	/* Conकाष्ठा the SSP Task SCU Task Context */
	scu_ssp_task_request_स्थिरruct_task_context(ireq);

	/* Fill in the SSP Task IU */
	sci_task_request_build_ssp_task_iu(ireq);

	sci_change_state(&ireq->sm, SCI_REQ_CONSTRUCTED);

	वापस SCI_SUCCESS;
पूर्ण

अटल क्रमागत sci_status sci_io_request_स्थिरruct_basic_sata(काष्ठा isci_request *ireq)
अणु
	क्रमागत sci_status status;
	bool copy = false;
	काष्ठा sas_task *task = isci_request_access_task(ireq);

	ireq->protocol = SAS_PROTOCOL_STP;

	copy = (task->data_dir == DMA_NONE) ? false : true;

	status = sci_io_request_स्थिरruct_sata(ireq,
						task->total_xfer_len,
						task->data_dir,
						copy);

	अगर (status == SCI_SUCCESS)
		sci_change_state(&ireq->sm, SCI_REQ_CONSTRUCTED);

	वापस status;
पूर्ण

#घोषणा SCU_TASK_CONTEXT_SRAM 0x200000
/**
 * sci_req_tx_bytes - bytes transferred when reply underruns request
 * @ireq: request that was terminated early
 */
अटल u32 sci_req_tx_bytes(काष्ठा isci_request *ireq)
अणु
	काष्ठा isci_host *ihost = ireq->owning_controller;
	u32 ret_val = 0;

	अगर (पढ़ोl(&ihost->smu_रेजिस्टरs->address_modअगरier) == 0) अणु
		व्योम __iomem *scu_reg_base = ihost->scu_रेजिस्टरs;

		/* get the bytes of data from the Address == BAR1 + 20002Ch + (256*TCi) where
		 *   BAR1 is the scu_रेजिस्टरs
		 *   0x20002C = 0x200000 + 0x2c
		 *            = start of task context SRAM + offset of (type.ssp.data_offset)
		 *   TCi is the io_tag of काष्ठा sci_request
		 */
		ret_val = पढ़ोl(scu_reg_base +
				(SCU_TASK_CONTEXT_SRAM + दुरत्व(काष्ठा scu_task_context, type.ssp.data_offset)) +
				((माप(काष्ठा scu_task_context)) * ISCI_TAG_TCI(ireq->io_tag)));
	पूर्ण

	वापस ret_val;
पूर्ण

क्रमागत sci_status sci_request_start(काष्ठा isci_request *ireq)
अणु
	क्रमागत sci_base_request_states state;
	काष्ठा scu_task_context *tc = ireq->tc;
	काष्ठा isci_host *ihost = ireq->owning_controller;

	state = ireq->sm.current_state_id;
	अगर (state != SCI_REQ_CONSTRUCTED) अणु
		dev_warn(&ihost->pdev->dev,
			"%s: SCIC IO Request requested to start while in wrong "
			 "state %d\n", __func__, state);
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	tc->task_index = ISCI_TAG_TCI(ireq->io_tag);

	चयन (tc->protocol_type) अणु
	हाल SCU_TASK_CONTEXT_PROTOCOL_SMP:
	हाल SCU_TASK_CONTEXT_PROTOCOL_SSP:
		/* SSP/SMP Frame */
		tc->type.ssp.tag = ireq->io_tag;
		tc->type.ssp.target_port_transfer_tag = 0xFFFF;
		अवरोध;

	हाल SCU_TASK_CONTEXT_PROTOCOL_STP:
		/* STP/SATA Frame
		 * tc->type.stp.ncq_tag = ireq->ncq_tag;
		 */
		अवरोध;

	हाल SCU_TASK_CONTEXT_PROTOCOL_NONE:
		/* / @toकरो When करो we set no protocol type? */
		अवरोध;

	शेष:
		/* This should never happen since we build the IO
		 * requests */
		अवरोध;
	पूर्ण

	/* Add to the post_context the io tag value */
	ireq->post_context |= ISCI_TAG_TCI(ireq->io_tag);

	/* Everything is good go ahead and change state */
	sci_change_state(&ireq->sm, SCI_REQ_STARTED);

	वापस SCI_SUCCESS;
पूर्ण

क्रमागत sci_status
sci_io_request_terminate(काष्ठा isci_request *ireq)
अणु
	क्रमागत sci_base_request_states state;

	state = ireq->sm.current_state_id;

	चयन (state) अणु
	हाल SCI_REQ_CONSTRUCTED:
		/* Set to make sure no HW terminate posting is करोne: */
		set_bit(IREQ_TC_ABORT_POSTED, &ireq->flags);
		ireq->scu_status = SCU_TASK_DONE_TASK_ABORT;
		ireq->sci_status = SCI_FAILURE_IO_TERMINATED;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		वापस SCI_SUCCESS;
	हाल SCI_REQ_STARTED:
	हाल SCI_REQ_TASK_WAIT_TC_COMP:
	हाल SCI_REQ_SMP_WAIT_RESP:
	हाल SCI_REQ_SMP_WAIT_TC_COMP:
	हाल SCI_REQ_STP_UDMA_WAIT_TC_COMP:
	हाल SCI_REQ_STP_UDMA_WAIT_D2H:
	हाल SCI_REQ_STP_NON_DATA_WAIT_H2D:
	हाल SCI_REQ_STP_NON_DATA_WAIT_D2H:
	हाल SCI_REQ_STP_PIO_WAIT_H2D:
	हाल SCI_REQ_STP_PIO_WAIT_FRAME:
	हाल SCI_REQ_STP_PIO_DATA_IN:
	हाल SCI_REQ_STP_PIO_DATA_OUT:
	हाल SCI_REQ_ATAPI_WAIT_H2D:
	हाल SCI_REQ_ATAPI_WAIT_PIO_SETUP:
	हाल SCI_REQ_ATAPI_WAIT_D2H:
	हाल SCI_REQ_ATAPI_WAIT_TC_COMP:
		/* Fall through and change state to ABORTING... */
	हाल SCI_REQ_TASK_WAIT_TC_RESP:
		/* The task frame was alपढ़ोy confirmed to have been
		 * sent by the SCU HW.  Since the state machine is
		 * now only रुकोing क्रम the task response itself,
		 * पात the request and complete it immediately
		 * and करोn't रुको क्रम the task response.
		 */
		sci_change_state(&ireq->sm, SCI_REQ_ABORTING);
		fallthrough;	/* and handle like ABORTING */
	हाल SCI_REQ_ABORTING:
		अगर (!isci_remote_device_is_safe_to_पात(ireq->target_device))
			set_bit(IREQ_PENDING_ABORT, &ireq->flags);
		अन्यथा
			clear_bit(IREQ_PENDING_ABORT, &ireq->flags);
		/* If the request is only रुकोing on the remote device
		 * suspension, वापस SUCCESS so the caller will रुको too.
		 */
		वापस SCI_SUCCESS;
	हाल SCI_REQ_COMPLETED:
	शेष:
		dev_warn(&ireq->owning_controller->pdev->dev,
			 "%s: SCIC IO Request requested to abort while in wrong "
			 "state %d\n", __func__, ireq->sm.current_state_id);
		अवरोध;
	पूर्ण

	वापस SCI_FAILURE_INVALID_STATE;
पूर्ण

क्रमागत sci_status sci_request_complete(काष्ठा isci_request *ireq)
अणु
	क्रमागत sci_base_request_states state;
	काष्ठा isci_host *ihost = ireq->owning_controller;

	state = ireq->sm.current_state_id;
	अगर (WARN_ONCE(state != SCI_REQ_COMPLETED,
		      "isci: request completion from wrong state (%s)\n",
		      req_state_name(state)))
		वापस SCI_FAILURE_INVALID_STATE;

	अगर (ireq->saved_rx_frame_index != SCU_INVALID_FRAME_INDEX)
		sci_controller_release_frame(ihost,
						  ireq->saved_rx_frame_index);

	/* XXX can we just stop the machine and हटाओ the 'final' state? */
	sci_change_state(&ireq->sm, SCI_REQ_FINAL);
	वापस SCI_SUCCESS;
पूर्ण

क्रमागत sci_status sci_io_request_event_handler(काष्ठा isci_request *ireq,
						  u32 event_code)
अणु
	क्रमागत sci_base_request_states state;
	काष्ठा isci_host *ihost = ireq->owning_controller;

	state = ireq->sm.current_state_id;

	अगर (state != SCI_REQ_STP_PIO_DATA_IN) अणु
		dev_warn(&ihost->pdev->dev, "%s: (%x) in wrong state %s\n",
			 __func__, event_code, req_state_name(state));

		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	चयन (scu_get_event_specअगरier(event_code)) अणु
	हाल SCU_TASK_DONE_CRC_ERR << SCU_EVENT_SPECIFIC_CODE_SHIFT:
		/* We are रुकोing क्रम data and the SCU has R_ERR the data frame.
		 * Go back to रुकोing क्रम the D2H Register FIS
		 */
		sci_change_state(&ireq->sm, SCI_REQ_STP_PIO_WAIT_FRAME);
		वापस SCI_SUCCESS;
	शेष:
		dev_err(&ihost->pdev->dev,
			"%s: pio request unexpected event %#x\n",
			__func__, event_code);

		/* TODO Should we fail the PIO request when we get an
		 * unexpected event?
		 */
		वापस SCI_FAILURE;
	पूर्ण
पूर्ण

/*
 * This function copies response data क्रम requests वापसing response data
 *    instead of sense data.
 * @sci_req: This parameter specअगरies the request object क्रम which to copy
 *    the response data.
 */
अटल व्योम sci_io_request_copy_response(काष्ठा isci_request *ireq)
अणु
	व्योम *resp_buf;
	u32 len;
	काष्ठा ssp_response_iu *ssp_response;
	काष्ठा isci_पंचांगf *isci_पंचांगf = isci_request_access_पंचांगf(ireq);

	ssp_response = &ireq->ssp.rsp;

	resp_buf = &isci_पंचांगf->resp.resp_iu;

	len = min_t(u32,
		    SSP_RESP_IU_MAX_SIZE,
		    be32_to_cpu(ssp_response->response_data_len));

	स_नकल(resp_buf, ssp_response->resp_data, len);
पूर्ण

अटल क्रमागत sci_status
request_started_state_tc_event(काष्ठा isci_request *ireq,
			       u32 completion_code)
अणु
	काष्ठा ssp_response_iu *resp_iu;
	u8 datapres;

	/* TODO: Any SDMA वापस code of other than 0 is bad decode 0x003C0000
	 * to determine SDMA status
	 */
	चयन (SCU_GET_COMPLETION_TL_STATUS(completion_code)) अणु
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_GOOD):
		ireq->scu_status = SCU_TASK_DONE_GOOD;
		ireq->sci_status = SCI_SUCCESS;
		अवरोध;
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_EARLY_RESP): अणु
		/* There are बार when the SCU hardware will वापस an early
		 * response because the io request specअगरied more data than is
		 * वापसed by the target device (mode pages, inquiry data,
		 * etc.).  We must check the response stats to see अगर this is
		 * truly a failed request or a good request that just got
		 * completed early.
		 */
		काष्ठा ssp_response_iu *resp = &ireq->ssp.rsp;
		sमाप_प्रकार word_cnt = SSP_RESP_IU_MAX_SIZE / माप(u32);

		sci_swab32_cpy(&ireq->ssp.rsp,
			       &ireq->ssp.rsp,
			       word_cnt);

		अगर (resp->status == 0) अणु
			ireq->scu_status = SCU_TASK_DONE_GOOD;
			ireq->sci_status = SCI_SUCCESS_IO_DONE_EARLY;
		पूर्ण अन्यथा अणु
			ireq->scu_status = SCU_TASK_DONE_CHECK_RESPONSE;
			ireq->sci_status = SCI_FAILURE_IO_RESPONSE_VALID;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_CHECK_RESPONSE): अणु
		sमाप_प्रकार word_cnt = SSP_RESP_IU_MAX_SIZE / माप(u32);

		sci_swab32_cpy(&ireq->ssp.rsp,
			       &ireq->ssp.rsp,
			       word_cnt);

		ireq->scu_status = SCU_TASK_DONE_CHECK_RESPONSE;
		ireq->sci_status = SCI_FAILURE_IO_RESPONSE_VALID;
		अवरोध;
	पूर्ण

	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_RESP_LEN_ERR):
		/* TODO With TASK_DONE_RESP_LEN_ERR is the response frame
		 * guaranteed to be received beक्रमe this completion status is
		 * posted?
		 */
		resp_iu = &ireq->ssp.rsp;
		datapres = resp_iu->datapres;

		अगर (datapres == 1 || datapres == 2) अणु
			ireq->scu_status = SCU_TASK_DONE_CHECK_RESPONSE;
			ireq->sci_status = SCI_FAILURE_IO_RESPONSE_VALID;
		पूर्ण अन्यथा अणु
			ireq->scu_status = SCU_TASK_DONE_GOOD;
			ireq->sci_status = SCI_SUCCESS;
		पूर्ण
		अवरोध;
	/* only stp device माला_लो suspended. */
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_ACK_NAK_TO):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_LL_PERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_NAK_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_DATA_LEN_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_LL_ABORT_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_XR_WD_LEN):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_MAX_PLD_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_UNEXP_RESP):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_UNEXP_SDBFIS):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_REG_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_SDB_ERR):
		अगर (ireq->protocol == SAS_PROTOCOL_STP) अणु
			ireq->scu_status = SCU_GET_COMPLETION_TL_STATUS(completion_code) >>
					   SCU_COMPLETION_TL_STATUS_SHIFT;
			ireq->sci_status = SCI_FAILURE_REMOTE_DEVICE_RESET_REQUIRED;
		पूर्ण अन्यथा अणु
			ireq->scu_status = SCU_GET_COMPLETION_TL_STATUS(completion_code) >>
					   SCU_COMPLETION_TL_STATUS_SHIFT;
			ireq->sci_status = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR;
		पूर्ण
		अवरोध;

	/* both stp/ssp device माला_लो suspended */
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_LF_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_OPEN_REJECT_WRONG_DESTINATION):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_1):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_2):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_3):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_OPEN_REJECT_BAD_DESTINATION):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_OPEN_REJECT_ZONE_VIOLATION):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_OPEN_REJECT_STP_RESOURCES_BUSY):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_OPEN_REJECT_PROTOCOL_NOT_SUPPORTED):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_OPEN_REJECT_CONNECTION_RATE_NOT_SUPPORTED):
		ireq->scu_status = SCU_GET_COMPLETION_TL_STATUS(completion_code) >>
				   SCU_COMPLETION_TL_STATUS_SHIFT;
		ireq->sci_status = SCI_FAILURE_REMOTE_DEVICE_RESET_REQUIRED;
		अवरोध;

	/* neither ssp nor stp माला_लो suspended. */
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_NAK_CMD_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_UNEXP_XR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_XR_IU_LEN_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_SDMA_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_OFFSET_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_EXCESS_DATA):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_SMP_RESP_TO_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_SMP_UFI_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_SMP_FRM_TYPE_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_SMP_LL_RX_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_UNEXP_DATA):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_OPEN_FAIL):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_VIIT_ENTRY_NV):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_IIT_ENTRY_NV):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_RNCNV_OUTBOUND):
	शेष:
		ireq->scu_status = SCU_GET_COMPLETION_TL_STATUS(completion_code) >>
				   SCU_COMPLETION_TL_STATUS_SHIFT;
		ireq->sci_status = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR;
		अवरोध;
	पूर्ण

	/*
	 * TODO: This is probably wrong क्रम ACK/NAK समयout conditions
	 */

	/* In all हालs we will treat this as the completion of the IO req. */
	sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
	वापस SCI_SUCCESS;
पूर्ण

अटल क्रमागत sci_status
request_पातing_state_tc_event(काष्ठा isci_request *ireq,
				u32 completion_code)
अणु
	चयन (SCU_GET_COMPLETION_TL_STATUS(completion_code)) अणु
	हाल (SCU_TASK_DONE_GOOD << SCU_COMPLETION_TL_STATUS_SHIFT):
	हाल (SCU_TASK_DONE_TASK_ABORT << SCU_COMPLETION_TL_STATUS_SHIFT):
		ireq->scu_status = SCU_TASK_DONE_TASK_ABORT;
		ireq->sci_status = SCI_FAILURE_IO_TERMINATED;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;

	शेष:
		/* Unless we get some strange error रुको क्रम the task पात to complete
		 * TODO: Should there be a state change क्रम this completion?
		 */
		अवरोध;
	पूर्ण

	वापस SCI_SUCCESS;
पूर्ण

अटल क्रमागत sci_status ssp_task_request_aरुको_tc_event(काष्ठा isci_request *ireq,
						       u32 completion_code)
अणु
	चयन (SCU_GET_COMPLETION_TL_STATUS(completion_code)) अणु
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_GOOD):
		ireq->scu_status = SCU_TASK_DONE_GOOD;
		ireq->sci_status = SCI_SUCCESS;
		sci_change_state(&ireq->sm, SCI_REQ_TASK_WAIT_TC_RESP);
		अवरोध;
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_ACK_NAK_TO):
		/* Currently, the decision is to simply allow the task request
		 * to समयout अगर the task IU wasn't received successfully.
		 * There is a potential क्रम receiving multiple task responses अगर
		 * we decide to send the task IU again.
		 */
		dev_warn(&ireq->owning_controller->pdev->dev,
			 "%s: TaskRequest:0x%p CompletionCode:%x - "
			 "ACK/NAK timeout\n", __func__, ireq,
			 completion_code);

		sci_change_state(&ireq->sm, SCI_REQ_TASK_WAIT_TC_RESP);
		अवरोध;
	शेष:
		/*
		 * All other completion status cause the IO to be complete.
		 * If a NAK was received, then it is up to the user to retry
		 * the request.
		 */
		ireq->scu_status = SCU_NORMALIZE_COMPLETION_STATUS(completion_code);
		ireq->sci_status = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;
	पूर्ण

	वापस SCI_SUCCESS;
पूर्ण

अटल क्रमागत sci_status
smp_request_aरुको_response_tc_event(काष्ठा isci_request *ireq,
				    u32 completion_code)
अणु
	चयन (SCU_GET_COMPLETION_TL_STATUS(completion_code)) अणु
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_GOOD):
		/* In the AWAIT RESPONSE state, any TC completion is
		 * unexpected.  but अगर the TC has success status, we
		 * complete the IO anyway.
		 */
		ireq->scu_status = SCU_TASK_DONE_GOOD;
		ireq->sci_status = SCI_SUCCESS;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_SMP_RESP_TO_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_SMP_UFI_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_SMP_FRM_TYPE_ERR):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_SMP_LL_RX_ERR):
		/* These status has been seen in a specअगरic LSI
		 * expander, which someबार is not able to send smp
		 * response within 2 ms. This causes our hardware अवरोध
		 * the connection and set TC completion with one of
		 * these SMP_XXX_XX_ERR status. For these type of error,
		 * we ask ihost user to retry the request.
		 */
		ireq->scu_status = SCU_TASK_DONE_SMP_RESP_TO_ERR;
		ireq->sci_status = SCI_FAILURE_RETRY_REQUIRED;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;
	शेष:
		/* All other completion status cause the IO to be complete.  If a NAK
		 * was received, then it is up to the user to retry the request
		 */
		ireq->scu_status = SCU_NORMALIZE_COMPLETION_STATUS(completion_code);
		ireq->sci_status = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;
	पूर्ण

	वापस SCI_SUCCESS;
पूर्ण

अटल क्रमागत sci_status
smp_request_aरुको_tc_event(काष्ठा isci_request *ireq,
			   u32 completion_code)
अणु
	चयन (SCU_GET_COMPLETION_TL_STATUS(completion_code)) अणु
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_GOOD):
		ireq->scu_status = SCU_TASK_DONE_GOOD;
		ireq->sci_status = SCI_SUCCESS;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;
	शेष:
		/* All other completion status cause the IO to be
		 * complete.  If a NAK was received, then it is up to
		 * the user to retry the request.
		 */
		ireq->scu_status = SCU_NORMALIZE_COMPLETION_STATUS(completion_code);
		ireq->sci_status = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;
	पूर्ण

	वापस SCI_SUCCESS;
पूर्ण

अटल काष्ठा scu_sgl_element *pio_sgl_next(काष्ठा isci_stp_request *stp_req)
अणु
	काष्ठा scu_sgl_element *sgl;
	काष्ठा scu_sgl_element_pair *sgl_pair;
	काष्ठा isci_request *ireq = to_ireq(stp_req);
	काष्ठा isci_stp_pio_sgl *pio_sgl = &stp_req->sgl;

	sgl_pair = to_sgl_element_pair(ireq, pio_sgl->index);
	अगर (!sgl_pair)
		sgl = शून्य;
	अन्यथा अगर (pio_sgl->set == SCU_SGL_ELEMENT_PAIR_A) अणु
		अगर (sgl_pair->B.address_lower == 0 &&
		    sgl_pair->B.address_upper == 0) अणु
			sgl = शून्य;
		पूर्ण अन्यथा अणु
			pio_sgl->set = SCU_SGL_ELEMENT_PAIR_B;
			sgl = &sgl_pair->B;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (sgl_pair->next_pair_lower == 0 &&
		    sgl_pair->next_pair_upper == 0) अणु
			sgl = शून्य;
		पूर्ण अन्यथा अणु
			pio_sgl->index++;
			pio_sgl->set = SCU_SGL_ELEMENT_PAIR_A;
			sgl_pair = to_sgl_element_pair(ireq, pio_sgl->index);
			sgl = &sgl_pair->A;
		पूर्ण
	पूर्ण

	वापस sgl;
पूर्ण

अटल क्रमागत sci_status
stp_request_non_data_aरुको_h2d_tc_event(काष्ठा isci_request *ireq,
					u32 completion_code)
अणु
	चयन (SCU_GET_COMPLETION_TL_STATUS(completion_code)) अणु
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_GOOD):
		ireq->scu_status = SCU_TASK_DONE_GOOD;
		ireq->sci_status = SCI_SUCCESS;
		sci_change_state(&ireq->sm, SCI_REQ_STP_NON_DATA_WAIT_D2H);
		अवरोध;

	शेष:
		/* All other completion status cause the IO to be
		 * complete.  If a NAK was received, then it is up to
		 * the user to retry the request.
		 */
		ireq->scu_status = SCU_NORMALIZE_COMPLETION_STATUS(completion_code);
		ireq->sci_status = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;
	पूर्ण

	वापस SCI_SUCCESS;
पूर्ण

#घोषणा SCU_MAX_FRAME_BUFFER_SIZE  0x400  /* 1K is the maximum SCU frame data payload */

/* transmit DATA_FIS from (current sgl + offset) क्रम input
 * parameter length. current sgl and offset is alreay stored in the IO request
 */
अटल क्रमागत sci_status sci_stp_request_pio_data_out_trयंत्रit_data_frame(
	काष्ठा isci_request *ireq,
	u32 length)
अणु
	काष्ठा isci_stp_request *stp_req = &ireq->stp.req;
	काष्ठा scu_task_context *task_context = ireq->tc;
	काष्ठा scu_sgl_element_pair *sgl_pair;
	काष्ठा scu_sgl_element *current_sgl;

	/* Recycle the TC and reस्थिरruct it क्रम sending out DATA FIS containing
	 * क्रम the data from current_sgl+offset क्रम the input length
	 */
	sgl_pair = to_sgl_element_pair(ireq, stp_req->sgl.index);
	अगर (stp_req->sgl.set == SCU_SGL_ELEMENT_PAIR_A)
		current_sgl = &sgl_pair->A;
	अन्यथा
		current_sgl = &sgl_pair->B;

	/* update the TC */
	task_context->command_iu_upper = current_sgl->address_upper;
	task_context->command_iu_lower = current_sgl->address_lower;
	task_context->transfer_length_bytes = length;
	task_context->type.stp.fis_type = FIS_DATA;

	/* send the new TC out. */
	वापस sci_controller_जारी_io(ireq);
पूर्ण

अटल क्रमागत sci_status sci_stp_request_pio_data_out_transmit_data(काष्ठा isci_request *ireq)
अणु
	काष्ठा isci_stp_request *stp_req = &ireq->stp.req;
	काष्ठा scu_sgl_element_pair *sgl_pair;
	क्रमागत sci_status status = SCI_SUCCESS;
	काष्ठा scu_sgl_element *sgl;
	u32 offset;
	u32 len = 0;

	offset = stp_req->sgl.offset;
	sgl_pair = to_sgl_element_pair(ireq, stp_req->sgl.index);
	अगर (WARN_ONCE(!sgl_pair, "%s: null sgl element", __func__))
		वापस SCI_FAILURE;

	अगर (stp_req->sgl.set == SCU_SGL_ELEMENT_PAIR_A) अणु
		sgl = &sgl_pair->A;
		len = sgl_pair->A.length - offset;
	पूर्ण अन्यथा अणु
		sgl = &sgl_pair->B;
		len = sgl_pair->B.length - offset;
	पूर्ण

	अगर (stp_req->pio_len == 0)
		वापस SCI_SUCCESS;

	अगर (stp_req->pio_len >= len) अणु
		status = sci_stp_request_pio_data_out_trयंत्रit_data_frame(ireq, len);
		अगर (status != SCI_SUCCESS)
			वापस status;
		stp_req->pio_len -= len;

		/* update the current sgl, offset and save क्रम future */
		sgl = pio_sgl_next(stp_req);
		offset = 0;
	पूर्ण अन्यथा अगर (stp_req->pio_len < len) अणु
		sci_stp_request_pio_data_out_trयंत्रit_data_frame(ireq, stp_req->pio_len);

		/* Sgl offset will be adjusted and saved क्रम future */
		offset += stp_req->pio_len;
		sgl->address_lower += stp_req->pio_len;
		stp_req->pio_len = 0;
	पूर्ण

	stp_req->sgl.offset = offset;

	वापस status;
पूर्ण

/**
 * sci_stp_request_pio_data_in_copy_data_buffer()
 * @stp_req: The request that is used क्रम the SGL processing.
 * @data_buf: The buffer of data to be copied.
 * @len: The length of the data transfer.
 *
 * Copy the data from the buffer क्रम the length specअगरied to the IO request SGL
 * specअगरied data region. क्रमागत sci_status
 */
अटल क्रमागत sci_status
sci_stp_request_pio_data_in_copy_data_buffer(काष्ठा isci_stp_request *stp_req,
					     u8 *data_buf, u32 len)
अणु
	काष्ठा isci_request *ireq;
	u8 *src_addr;
	पूर्णांक copy_len;
	काष्ठा sas_task *task;
	काष्ठा scatterlist *sg;
	व्योम *kaddr;
	पूर्णांक total_len = len;

	ireq = to_ireq(stp_req);
	task = isci_request_access_task(ireq);
	src_addr = data_buf;

	अगर (task->num_scatter > 0) अणु
		sg = task->scatter;

		जबतक (total_len > 0) अणु
			काष्ठा page *page = sg_page(sg);

			copy_len = min_t(पूर्णांक, total_len, sg_dma_len(sg));
			kaddr = kmap_atomic(page);
			स_नकल(kaddr + sg->offset, src_addr, copy_len);
			kunmap_atomic(kaddr);
			total_len -= copy_len;
			src_addr += copy_len;
			sg = sg_next(sg);
		पूर्ण
	पूर्ण अन्यथा अणु
		BUG_ON(task->total_xfer_len < total_len);
		स_नकल(task->scatter, src_addr, total_len);
	पूर्ण

	वापस SCI_SUCCESS;
पूर्ण

/**
 * sci_stp_request_pio_data_in_copy_data()
 * @stp_req: The PIO DATA IN request that is to receive the data.
 * @data_buffer: The buffer to copy from.
 *
 * Copy the data buffer to the io request data region. क्रमागत sci_status
 */
अटल क्रमागत sci_status sci_stp_request_pio_data_in_copy_data(
	काष्ठा isci_stp_request *stp_req,
	u8 *data_buffer)
अणु
	क्रमागत sci_status status;

	/*
	 * If there is less than 1K reमुख्यing in the transfer request
	 * copy just the data क्रम the transfer */
	अगर (stp_req->pio_len < SCU_MAX_FRAME_BUFFER_SIZE) अणु
		status = sci_stp_request_pio_data_in_copy_data_buffer(
			stp_req, data_buffer, stp_req->pio_len);

		अगर (status == SCI_SUCCESS)
			stp_req->pio_len = 0;
	पूर्ण अन्यथा अणु
		/* We are transfering the whole frame so copy */
		status = sci_stp_request_pio_data_in_copy_data_buffer(
			stp_req, data_buffer, SCU_MAX_FRAME_BUFFER_SIZE);

		अगर (status == SCI_SUCCESS)
			stp_req->pio_len -= SCU_MAX_FRAME_BUFFER_SIZE;
	पूर्ण

	वापस status;
पूर्ण

अटल क्रमागत sci_status
stp_request_pio_aरुको_h2d_completion_tc_event(काष्ठा isci_request *ireq,
					      u32 completion_code)
अणु
	चयन (SCU_GET_COMPLETION_TL_STATUS(completion_code)) अणु
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_GOOD):
		ireq->scu_status = SCU_TASK_DONE_GOOD;
		ireq->sci_status = SCI_SUCCESS;
		sci_change_state(&ireq->sm, SCI_REQ_STP_PIO_WAIT_FRAME);
		अवरोध;

	शेष:
		/* All other completion status cause the IO to be
		 * complete.  If a NAK was received, then it is up to
		 * the user to retry the request.
		 */
		ireq->scu_status = SCU_NORMALIZE_COMPLETION_STATUS(completion_code);
		ireq->sci_status = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;
	पूर्ण

	वापस SCI_SUCCESS;
पूर्ण

अटल क्रमागत sci_status
pio_data_out_tx_करोne_tc_event(काष्ठा isci_request *ireq,
			      u32 completion_code)
अणु
	क्रमागत sci_status status = SCI_SUCCESS;
	bool all_frames_transferred = false;
	काष्ठा isci_stp_request *stp_req = &ireq->stp.req;

	चयन (SCU_GET_COMPLETION_TL_STATUS(completion_code)) अणु
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_GOOD):
		/* Transmit data */
		अगर (stp_req->pio_len != 0) अणु
			status = sci_stp_request_pio_data_out_transmit_data(ireq);
			अगर (status == SCI_SUCCESS) अणु
				अगर (stp_req->pio_len == 0)
					all_frames_transferred = true;
			पूर्ण
		पूर्ण अन्यथा अगर (stp_req->pio_len == 0) अणु
			/*
			 * this will happen अगर the all data is written at the
			 * first समय after the pio setup fis is received
			 */
			all_frames_transferred  = true;
		पूर्ण

		/* all data transferred. */
		अगर (all_frames_transferred) अणु
			/*
			 * Change the state to SCI_REQ_STP_PIO_DATA_IN
			 * and रुको क्रम PIO_SETUP fis / or D2H REg fis. */
			sci_change_state(&ireq->sm, SCI_REQ_STP_PIO_WAIT_FRAME);
		पूर्ण
		अवरोध;

	शेष:
		/*
		 * All other completion status cause the IO to be complete.
		 * If a NAK was received, then it is up to the user to retry
		 * the request.
		 */
		ireq->scu_status = SCU_NORMALIZE_COMPLETION_STATUS(completion_code);
		ireq->sci_status = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

अटल क्रमागत sci_status sci_stp_request_udma_general_frame_handler(काष्ठा isci_request *ireq,
								       u32 frame_index)
अणु
	काष्ठा isci_host *ihost = ireq->owning_controller;
	काष्ठा dev_to_host_fis *frame_header;
	क्रमागत sci_status status;
	u32 *frame_buffer;

	status = sci_unsolicited_frame_control_get_header(&ihost->uf_control,
							       frame_index,
							       (व्योम **)&frame_header);

	अगर ((status == SCI_SUCCESS) &&
	    (frame_header->fis_type == FIS_REGD2H)) अणु
		sci_unsolicited_frame_control_get_buffer(&ihost->uf_control,
							      frame_index,
							      (व्योम **)&frame_buffer);

		sci_controller_copy_sata_response(&ireq->stp.rsp,
						       frame_header,
						       frame_buffer);
	पूर्ण

	sci_controller_release_frame(ihost, frame_index);

	वापस status;
पूर्ण

अटल क्रमागत sci_status process_unsolicited_fis(काष्ठा isci_request *ireq,
					       u32 frame_index)
अणु
	काष्ठा isci_host *ihost = ireq->owning_controller;
	क्रमागत sci_status status;
	काष्ठा dev_to_host_fis *frame_header;
	u32 *frame_buffer;

	status = sci_unsolicited_frame_control_get_header(&ihost->uf_control,
							  frame_index,
							  (व्योम **)&frame_header);

	अगर (status != SCI_SUCCESS)
		वापस status;

	अगर (frame_header->fis_type != FIS_REGD2H) अणु
		dev_err(&ireq->isci_host->pdev->dev,
			"%s ERROR: invalid fis type 0x%X\n",
			__func__, frame_header->fis_type);
		वापस SCI_FAILURE;
	पूर्ण

	sci_unsolicited_frame_control_get_buffer(&ihost->uf_control,
						 frame_index,
						 (व्योम **)&frame_buffer);

	sci_controller_copy_sata_response(&ireq->stp.rsp,
					  (u32 *)frame_header,
					  frame_buffer);

	/* Frame has been decoded वापस it to the controller */
	sci_controller_release_frame(ihost, frame_index);

	वापस status;
पूर्ण

अटल क्रमागत sci_status atapi_d2h_reg_frame_handler(काष्ठा isci_request *ireq,
						   u32 frame_index)
अणु
	काष्ठा sas_task *task = isci_request_access_task(ireq);
	क्रमागत sci_status status;

	status = process_unsolicited_fis(ireq, frame_index);

	अगर (status == SCI_SUCCESS) अणु
		अगर (ireq->stp.rsp.status & ATA_ERR)
			status = SCI_FAILURE_IO_RESPONSE_VALID;
	पूर्ण अन्यथा अणु
		status = SCI_FAILURE_IO_RESPONSE_VALID;
	पूर्ण

	अगर (status != SCI_SUCCESS) अणु
		ireq->scu_status = SCU_TASK_DONE_CHECK_RESPONSE;
		ireq->sci_status = status;
	पूर्ण अन्यथा अणु
		ireq->scu_status = SCU_TASK_DONE_GOOD;
		ireq->sci_status = SCI_SUCCESS;
	पूर्ण

	/* the d2h ufi is the end of non-data commands */
	अगर (task->data_dir == DMA_NONE)
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);

	वापस status;
पूर्ण

अटल व्योम scu_atapi_reस्थिरruct_raw_frame_task_context(काष्ठा isci_request *ireq)
अणु
	काष्ठा ata_device *dev = sas_to_ata_dev(ireq->target_device->करोमुख्य_dev);
	व्योम *atapi_cdb = ireq->ttype_ptr.io_task_ptr->ata_task.atapi_packet;
	काष्ठा scu_task_context *task_context = ireq->tc;

	/* fill in the SCU Task Context क्रम a DATA fis containing CDB in Raw Frame
	 * type. The TC क्रम previous Packet fis was alपढ़ोy there, we only need to
	 * change the H2D fis content.
	 */
	स_रखो(&ireq->stp.cmd, 0, माप(काष्ठा host_to_dev_fis));
	स_नकल(((u8 *)&ireq->stp.cmd + माप(u32)), atapi_cdb, ATAPI_CDB_LEN);
	स_रखो(&(task_context->type.stp), 0, माप(काष्ठा stp_task_context));
	task_context->type.stp.fis_type = FIS_DATA;
	task_context->transfer_length_bytes = dev->cdb_len;
पूर्ण

अटल व्योम scu_atapi_स्थिरruct_task_context(काष्ठा isci_request *ireq)
अणु
	काष्ठा ata_device *dev = sas_to_ata_dev(ireq->target_device->करोमुख्य_dev);
	काष्ठा sas_task *task = isci_request_access_task(ireq);
	काष्ठा scu_task_context *task_context = ireq->tc;
	पूर्णांक cdb_len = dev->cdb_len;

	/* reference: SSTL 1.13.4.2
	 * task_type, sata_direction
	 */
	अगर (task->data_dir == DMA_TO_DEVICE) अणु
		task_context->task_type = SCU_TASK_TYPE_PACKET_DMA_OUT;
		task_context->sata_direction = 0;
	पूर्ण अन्यथा अणु
		/* toकरो: क्रम NO_DATA command, we need to send out raw frame. */
		task_context->task_type = SCU_TASK_TYPE_PACKET_DMA_IN;
		task_context->sata_direction = 1;
	पूर्ण

	स_रखो(&task_context->type.stp, 0, माप(task_context->type.stp));
	task_context->type.stp.fis_type = FIS_DATA;

	स_रखो(&ireq->stp.cmd, 0, माप(ireq->stp.cmd));
	स_नकल(&ireq->stp.cmd.lbal, task->ata_task.atapi_packet, cdb_len);
	task_context->ssp_command_iu_length = cdb_len / माप(u32);

	/* task phase is set to TX_CMD */
	task_context->task_phase = 0x1;

	/* retry counter */
	task_context->stp_retry_count = 0;

	/* data transfer size. */
	task_context->transfer_length_bytes = task->total_xfer_len;

	/* setup sgl */
	sci_request_build_sgl(ireq);
पूर्ण

क्रमागत sci_status
sci_io_request_frame_handler(काष्ठा isci_request *ireq,
				  u32 frame_index)
अणु
	काष्ठा isci_host *ihost = ireq->owning_controller;
	काष्ठा isci_stp_request *stp_req = &ireq->stp.req;
	क्रमागत sci_base_request_states state;
	क्रमागत sci_status status;
	sमाप_प्रकार word_cnt;

	state = ireq->sm.current_state_id;
	चयन (state)  अणु
	हाल SCI_REQ_STARTED: अणु
		काष्ठा ssp_frame_hdr ssp_hdr;
		व्योम *frame_header;

		sci_unsolicited_frame_control_get_header(&ihost->uf_control,
							      frame_index,
							      &frame_header);

		word_cnt = माप(काष्ठा ssp_frame_hdr) / माप(u32);
		sci_swab32_cpy(&ssp_hdr, frame_header, word_cnt);

		अगर (ssp_hdr.frame_type == SSP_RESPONSE) अणु
			काष्ठा ssp_response_iu *resp_iu;
			sमाप_प्रकार word_cnt = SSP_RESP_IU_MAX_SIZE / माप(u32);

			sci_unsolicited_frame_control_get_buffer(&ihost->uf_control,
								      frame_index,
								      (व्योम **)&resp_iu);

			sci_swab32_cpy(&ireq->ssp.rsp, resp_iu, word_cnt);

			resp_iu = &ireq->ssp.rsp;

			अगर (resp_iu->datapres == 0x01 ||
			    resp_iu->datapres == 0x02) अणु
				ireq->scu_status = SCU_TASK_DONE_CHECK_RESPONSE;
				ireq->sci_status = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR;
			पूर्ण अन्यथा अणु
				ireq->scu_status = SCU_TASK_DONE_GOOD;
				ireq->sci_status = SCI_SUCCESS;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* not a response frame, why did it get क्रमwarded? */
			dev_err(&ihost->pdev->dev,
				"%s: SCIC IO Request 0x%p received unexpected "
				"frame %d type 0x%02x\n", __func__, ireq,
				frame_index, ssp_hdr.frame_type);
		पूर्ण

		/*
		 * In any हाल we are करोne with this frame buffer वापस it to
		 * the controller
		 */
		sci_controller_release_frame(ihost, frame_index);

		वापस SCI_SUCCESS;
	पूर्ण

	हाल SCI_REQ_TASK_WAIT_TC_RESP:
		sci_io_request_copy_response(ireq);
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		sci_controller_release_frame(ihost, frame_index);
		वापस SCI_SUCCESS;

	हाल SCI_REQ_SMP_WAIT_RESP: अणु
		काष्ठा sas_task *task = isci_request_access_task(ireq);
		काष्ठा scatterlist *sg = &task->smp_task.smp_resp;
		व्योम *frame_header, *kaddr;
		u8 *rsp;

		sci_unsolicited_frame_control_get_header(&ihost->uf_control,
							 frame_index,
							 &frame_header);
		kaddr = kmap_atomic(sg_page(sg));
		rsp = kaddr + sg->offset;
		sci_swab32_cpy(rsp, frame_header, 1);

		अगर (rsp[0] == SMP_RESPONSE) अणु
			व्योम *smp_resp;

			sci_unsolicited_frame_control_get_buffer(&ihost->uf_control,
								 frame_index,
								 &smp_resp);

			word_cnt = (sg->length/4)-1;
			अगर (word_cnt > 0)
				word_cnt = min_t(अचिन्हित पूर्णांक, word_cnt,
						 SCU_UNSOLICITED_FRAME_BUFFER_SIZE/4);
			sci_swab32_cpy(rsp + 4, smp_resp, word_cnt);

			ireq->scu_status = SCU_TASK_DONE_GOOD;
			ireq->sci_status = SCI_SUCCESS;
			sci_change_state(&ireq->sm, SCI_REQ_SMP_WAIT_TC_COMP);
		पूर्ण अन्यथा अणु
			/*
			 * This was not a response frame why did it get
			 * क्रमwarded?
			 */
			dev_err(&ihost->pdev->dev,
				"%s: SCIC SMP Request 0x%p received unexpected "
				"frame %d type 0x%02x\n",
				__func__,
				ireq,
				frame_index,
				rsp[0]);

			ireq->scu_status = SCU_TASK_DONE_SMP_FRM_TYPE_ERR;
			ireq->sci_status = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR;
			sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		पूर्ण
		kunmap_atomic(kaddr);

		sci_controller_release_frame(ihost, frame_index);

		वापस SCI_SUCCESS;
	पूर्ण

	हाल SCI_REQ_STP_UDMA_WAIT_TC_COMP:
		वापस sci_stp_request_udma_general_frame_handler(ireq,
								       frame_index);

	हाल SCI_REQ_STP_UDMA_WAIT_D2H:
		/* Use the general frame handler to copy the resposne data */
		status = sci_stp_request_udma_general_frame_handler(ireq, frame_index);

		अगर (status != SCI_SUCCESS)
			वापस status;

		ireq->scu_status = SCU_TASK_DONE_CHECK_RESPONSE;
		ireq->sci_status = SCI_FAILURE_IO_RESPONSE_VALID;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		वापस SCI_SUCCESS;

	हाल SCI_REQ_STP_NON_DATA_WAIT_D2H: अणु
		काष्ठा dev_to_host_fis *frame_header;
		u32 *frame_buffer;

		status = sci_unsolicited_frame_control_get_header(&ihost->uf_control,
								       frame_index,
								       (व्योम **)&frame_header);

		अगर (status != SCI_SUCCESS) अणु
			dev_err(&ihost->pdev->dev,
				"%s: SCIC IO Request 0x%p could not get frame "
				"header for frame index %d, status %x\n",
				__func__,
				stp_req,
				frame_index,
				status);

			वापस status;
		पूर्ण

		चयन (frame_header->fis_type) अणु
		हाल FIS_REGD2H:
			sci_unsolicited_frame_control_get_buffer(&ihost->uf_control,
								      frame_index,
								      (व्योम **)&frame_buffer);

			sci_controller_copy_sata_response(&ireq->stp.rsp,
							       frame_header,
							       frame_buffer);

			/* The command has completed with error */
			ireq->scu_status = SCU_TASK_DONE_CHECK_RESPONSE;
			ireq->sci_status = SCI_FAILURE_IO_RESPONSE_VALID;
			अवरोध;

		शेष:
			dev_warn(&ihost->pdev->dev,
				 "%s: IO Request:0x%p Frame Id:%d protocol "
				  "violation occurred\n", __func__, stp_req,
				  frame_index);

			ireq->scu_status = SCU_TASK_DONE_UNEXP_FIS;
			ireq->sci_status = SCI_FAILURE_PROTOCOL_VIOLATION;
			अवरोध;
		पूर्ण

		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);

		/* Frame has been decoded वापस it to the controller */
		sci_controller_release_frame(ihost, frame_index);

		वापस status;
	पूर्ण

	हाल SCI_REQ_STP_PIO_WAIT_FRAME: अणु
		काष्ठा sas_task *task = isci_request_access_task(ireq);
		काष्ठा dev_to_host_fis *frame_header;
		u32 *frame_buffer;

		status = sci_unsolicited_frame_control_get_header(&ihost->uf_control,
								       frame_index,
								       (व्योम **)&frame_header);

		अगर (status != SCI_SUCCESS) अणु
			dev_err(&ihost->pdev->dev,
				"%s: SCIC IO Request 0x%p could not get frame "
				"header for frame index %d, status %x\n",
				__func__, stp_req, frame_index, status);
			वापस status;
		पूर्ण

		चयन (frame_header->fis_type) अणु
		हाल FIS_PIO_SETUP:
			/* Get from the frame buffer the PIO Setup Data */
			sci_unsolicited_frame_control_get_buffer(&ihost->uf_control,
								      frame_index,
								      (व्योम **)&frame_buffer);

			/* Get the data from the PIO Setup The SCU Hardware
			 * वापसs first word in the frame_header and the rest
			 * of the data is in the frame buffer so we need to
			 * back up one dword
			 */

			/* transfer_count: first 16bits in the 4th dword */
			stp_req->pio_len = frame_buffer[3] & 0xffff;

			/* status: 4th byte in the 3rd dword */
			stp_req->status = (frame_buffer[2] >> 24) & 0xff;

			sci_controller_copy_sata_response(&ireq->stp.rsp,
							       frame_header,
							       frame_buffer);

			ireq->stp.rsp.status = stp_req->status;

			/* The next state is dependent on whether the
			 * request was PIO Data-in or Data out
			 */
			अगर (task->data_dir == DMA_FROM_DEVICE) अणु
				sci_change_state(&ireq->sm, SCI_REQ_STP_PIO_DATA_IN);
			पूर्ण अन्यथा अगर (task->data_dir == DMA_TO_DEVICE) अणु
				/* Transmit data */
				status = sci_stp_request_pio_data_out_transmit_data(ireq);
				अगर (status != SCI_SUCCESS)
					अवरोध;
				sci_change_state(&ireq->sm, SCI_REQ_STP_PIO_DATA_OUT);
			पूर्ण
			अवरोध;

		हाल FIS_SETDEVBITS:
			sci_change_state(&ireq->sm, SCI_REQ_STP_PIO_WAIT_FRAME);
			अवरोध;

		हाल FIS_REGD2H:
			अगर (frame_header->status & ATA_BUSY) अणु
				/*
				 * Now why is the drive sending a D2H Register
				 * FIS when it is still busy?  Do nothing since
				 * we are still in the right state.
				 */
				dev_dbg(&ihost->pdev->dev,
					"%s: SCIC PIO Request 0x%p received "
					"D2H Register FIS with BSY status "
					"0x%x\n",
					__func__,
					stp_req,
					frame_header->status);
				अवरोध;
			पूर्ण

			sci_unsolicited_frame_control_get_buffer(&ihost->uf_control,
								      frame_index,
								      (व्योम **)&frame_buffer);

			sci_controller_copy_sata_response(&ireq->stp.rsp,
							       frame_header,
							       frame_buffer);

			ireq->scu_status = SCU_TASK_DONE_CHECK_RESPONSE;
			ireq->sci_status = SCI_FAILURE_IO_RESPONSE_VALID;
			sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
			अवरोध;

		शेष:
			/* FIXME: what करो we करो here? */
			अवरोध;
		पूर्ण

		/* Frame is decoded वापस it to the controller */
		sci_controller_release_frame(ihost, frame_index);

		वापस status;
	पूर्ण

	हाल SCI_REQ_STP_PIO_DATA_IN: अणु
		काष्ठा dev_to_host_fis *frame_header;
		काष्ठा sata_fis_data *frame_buffer;

		status = sci_unsolicited_frame_control_get_header(&ihost->uf_control,
								       frame_index,
								       (व्योम **)&frame_header);

		अगर (status != SCI_SUCCESS) अणु
			dev_err(&ihost->pdev->dev,
				"%s: SCIC IO Request 0x%p could not get frame "
				"header for frame index %d, status %x\n",
				__func__,
				stp_req,
				frame_index,
				status);
			वापस status;
		पूर्ण

		अगर (frame_header->fis_type != FIS_DATA) अणु
			dev_err(&ihost->pdev->dev,
				"%s: SCIC PIO Request 0x%p received frame %d "
				"with fis type 0x%02x when expecting a data "
				"fis.\n",
				__func__,
				stp_req,
				frame_index,
				frame_header->fis_type);

			ireq->scu_status = SCU_TASK_DONE_GOOD;
			ireq->sci_status = SCI_FAILURE_IO_REQUIRES_SCSI_ABORT;
			sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);

			/* Frame is decoded वापस it to the controller */
			sci_controller_release_frame(ihost, frame_index);
			वापस status;
		पूर्ण

		अगर (stp_req->sgl.index < 0) अणु
			ireq->saved_rx_frame_index = frame_index;
			stp_req->pio_len = 0;
		पूर्ण अन्यथा अणु
			sci_unsolicited_frame_control_get_buffer(&ihost->uf_control,
								      frame_index,
								      (व्योम **)&frame_buffer);

			status = sci_stp_request_pio_data_in_copy_data(stp_req,
									    (u8 *)frame_buffer);

			/* Frame is decoded वापस it to the controller */
			sci_controller_release_frame(ihost, frame_index);
		पूर्ण

		/* Check क्रम the end of the transfer, are there more
		 * bytes reमुख्यing क्रम this data transfer
		 */
		अगर (status != SCI_SUCCESS || stp_req->pio_len != 0)
			वापस status;

		अगर ((stp_req->status & ATA_BUSY) == 0) अणु
			ireq->scu_status = SCU_TASK_DONE_CHECK_RESPONSE;
			ireq->sci_status = SCI_FAILURE_IO_RESPONSE_VALID;
			sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		पूर्ण अन्यथा अणु
			sci_change_state(&ireq->sm, SCI_REQ_STP_PIO_WAIT_FRAME);
		पूर्ण
		वापस status;
	पूर्ण

	हाल SCI_REQ_ATAPI_WAIT_PIO_SETUP: अणु
		काष्ठा sas_task *task = isci_request_access_task(ireq);

		sci_controller_release_frame(ihost, frame_index);
		ireq->target_device->working_request = ireq;
		अगर (task->data_dir == DMA_NONE) अणु
			sci_change_state(&ireq->sm, SCI_REQ_ATAPI_WAIT_TC_COMP);
			scu_atapi_reस्थिरruct_raw_frame_task_context(ireq);
		पूर्ण अन्यथा अणु
			sci_change_state(&ireq->sm, SCI_REQ_ATAPI_WAIT_D2H);
			scu_atapi_स्थिरruct_task_context(ireq);
		पूर्ण

		sci_controller_जारी_io(ireq);
		वापस SCI_SUCCESS;
	पूर्ण
	हाल SCI_REQ_ATAPI_WAIT_D2H:
		वापस atapi_d2h_reg_frame_handler(ireq, frame_index);
	हाल SCI_REQ_ABORTING:
		/*
		 * TODO: Is it even possible to get an unsolicited frame in the
		 * पातing state?
		 */
		sci_controller_release_frame(ihost, frame_index);
		वापस SCI_SUCCESS;

	शेष:
		dev_warn(&ihost->pdev->dev,
			 "%s: SCIC IO Request given unexpected frame %x while "
			 "in state %d\n",
			 __func__,
			 frame_index,
			 state);

		sci_controller_release_frame(ihost, frame_index);
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
पूर्ण

अटल क्रमागत sci_status stp_request_udma_aरुको_tc_event(काष्ठा isci_request *ireq,
						       u32 completion_code)
अणु
	चयन (SCU_GET_COMPLETION_TL_STATUS(completion_code)) अणु
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_GOOD):
		ireq->scu_status = SCU_TASK_DONE_GOOD;
		ireq->sci_status = SCI_SUCCESS;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_UNEXP_FIS):
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_REG_ERR):
		/* We must check ther response buffer to see अगर the D2H
		 * Register FIS was received beक्रमe we got the TC
		 * completion.
		 */
		अगर (ireq->stp.rsp.fis_type == FIS_REGD2H) अणु
			sci_remote_device_suspend(ireq->target_device,
						  SCI_SW_SUSPEND_NORMAL);

			ireq->scu_status = SCU_TASK_DONE_CHECK_RESPONSE;
			ireq->sci_status = SCI_FAILURE_IO_RESPONSE_VALID;
			sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		पूर्ण अन्यथा अणु
			/* If we have an error completion status क्रम the
			 * TC then we can expect a D2H रेजिस्टर FIS from
			 * the device so we must change state to रुको
			 * क्रम it
			 */
			sci_change_state(&ireq->sm, SCI_REQ_STP_UDMA_WAIT_D2H);
		पूर्ण
		अवरोध;

	/* TODO Check to see अगर any of these completion status need to
	 * रुको क्रम the device to host रेजिस्टर fis.
	 */
	/* TODO We can retry the command क्रम SCU_TASK_DONE_CMD_LL_R_ERR
	 * - this comes only क्रम B0
	 */
	शेष:
		/* All other completion status cause the IO to be complete. */
		ireq->scu_status = SCU_NORMALIZE_COMPLETION_STATUS(completion_code);
		ireq->sci_status = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;
	पूर्ण

	वापस SCI_SUCCESS;
पूर्ण

अटल क्रमागत sci_status atapi_raw_completion(काष्ठा isci_request *ireq, u32 completion_code,
						  क्रमागत sci_base_request_states next)
अणु
	चयन (SCU_GET_COMPLETION_TL_STATUS(completion_code)) अणु
	हाल SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_GOOD):
		ireq->scu_status = SCU_TASK_DONE_GOOD;
		ireq->sci_status = SCI_SUCCESS;
		sci_change_state(&ireq->sm, next);
		अवरोध;
	शेष:
		/* All other completion status cause the IO to be complete.
		 * If a NAK was received, then it is up to the user to retry
		 * the request.
		 */
		ireq->scu_status = SCU_NORMALIZE_COMPLETION_STATUS(completion_code);
		ireq->sci_status = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR;

		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;
	पूर्ण

	वापस SCI_SUCCESS;
पूर्ण

अटल क्रमागत sci_status atapi_data_tc_completion_handler(काष्ठा isci_request *ireq,
							u32 completion_code)
अणु
	काष्ठा isci_remote_device *idev = ireq->target_device;
	काष्ठा dev_to_host_fis *d2h = &ireq->stp.rsp;
	क्रमागत sci_status status = SCI_SUCCESS;

	चयन (SCU_GET_COMPLETION_TL_STATUS(completion_code)) अणु
	हाल (SCU_TASK_DONE_GOOD << SCU_COMPLETION_TL_STATUS_SHIFT):
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;

	हाल (SCU_TASK_DONE_UNEXP_FIS << SCU_COMPLETION_TL_STATUS_SHIFT): अणु
		u16 len = sci_req_tx_bytes(ireq);

		/* likely non-error data underrrun, workaround missing
		 * d2h frame from the controller
		 */
		अगर (d2h->fis_type != FIS_REGD2H) अणु
			d2h->fis_type = FIS_REGD2H;
			d2h->flags = (1 << 6);
			d2h->status = 0x50;
			d2h->error = 0;
			d2h->lbal = 0;
			d2h->byte_count_low = len & 0xff;
			d2h->byte_count_high = len >> 8;
			d2h->device = 0xa0;
			d2h->lbal_exp = 0;
			d2h->lbam_exp = 0;
			d2h->lbah_exp = 0;
			d2h->_r_a = 0;
			d2h->sector_count = 0x3;
			d2h->sector_count_exp = 0;
			d2h->_r_b = 0;
			d2h->_r_c = 0;
			d2h->_r_d = 0;
		पूर्ण

		ireq->scu_status = SCU_TASK_DONE_GOOD;
		ireq->sci_status = SCI_SUCCESS_IO_DONE_EARLY;
		status = ireq->sci_status;

		/* the hw will have suspended the rnc, so complete the
		 * request upon pending resume
		 */
		sci_change_state(&idev->sm, SCI_STP_DEV_ATAPI_ERROR);
		अवरोध;
	पूर्ण
	हाल (SCU_TASK_DONE_EXCESS_DATA << SCU_COMPLETION_TL_STATUS_SHIFT):
		/* In this हाल, there is no UF coming after.
		 * compelte the IO now.
		 */
		ireq->scu_status = SCU_TASK_DONE_GOOD;
		ireq->sci_status = SCI_SUCCESS;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		अवरोध;

	शेष:
		अगर (d2h->fis_type == FIS_REGD2H) अणु
			/* UF received change the device state to ATAPI_ERROR */
			status = ireq->sci_status;
			sci_change_state(&idev->sm, SCI_STP_DEV_ATAPI_ERROR);
		पूर्ण अन्यथा अणु
			/* If receiving any non-success TC status, no UF
			 * received yet, then an UF क्रम the status fis
			 * is coming after (XXX: suspect this is
			 * actually a protocol error or a bug like the
			 * DONE_UNEXP_FIS हाल)
			 */
			ireq->scu_status = SCU_TASK_DONE_CHECK_RESPONSE;
			ireq->sci_status = SCI_FAILURE_IO_RESPONSE_VALID;

			sci_change_state(&ireq->sm, SCI_REQ_ATAPI_WAIT_D2H);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक sci_request_smp_completion_status_is_tx_suspend(
	अचिन्हित पूर्णांक completion_status)
अणु
	चयन (completion_status) अणु
	हाल SCU_TASK_OPEN_REJECT_WRONG_DESTINATION:
	हाल SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_1:
	हाल SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_2:
	हाल SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_3:
	हाल SCU_TASK_OPEN_REJECT_BAD_DESTINATION:
	हाल SCU_TASK_OPEN_REJECT_ZONE_VIOLATION:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sci_request_smp_completion_status_is_tx_rx_suspend(
	अचिन्हित पूर्णांक completion_status)
अणु
	वापस 0; /* There are no Tx/Rx SMP suspend conditions. */
पूर्ण

अटल पूर्णांक sci_request_ssp_completion_status_is_tx_suspend(
	अचिन्हित पूर्णांक completion_status)
अणु
	चयन (completion_status) अणु
	हाल SCU_TASK_DONE_TX_RAW_CMD_ERR:
	हाल SCU_TASK_DONE_LF_ERR:
	हाल SCU_TASK_OPEN_REJECT_WRONG_DESTINATION:
	हाल SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_1:
	हाल SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_2:
	हाल SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_3:
	हाल SCU_TASK_OPEN_REJECT_BAD_DESTINATION:
	हाल SCU_TASK_OPEN_REJECT_ZONE_VIOLATION:
	हाल SCU_TASK_OPEN_REJECT_STP_RESOURCES_BUSY:
	हाल SCU_TASK_OPEN_REJECT_PROTOCOL_NOT_SUPPORTED:
	हाल SCU_TASK_OPEN_REJECT_CONNECTION_RATE_NOT_SUPPORTED:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sci_request_ssp_completion_status_is_tx_rx_suspend(
	अचिन्हित पूर्णांक completion_status)
अणु
	वापस 0; /* There are no Tx/Rx SSP suspend conditions. */
पूर्ण

अटल पूर्णांक sci_request_stpsata_completion_status_is_tx_suspend(
	अचिन्हित पूर्णांक completion_status)
अणु
	चयन (completion_status) अणु
	हाल SCU_TASK_DONE_TX_RAW_CMD_ERR:
	हाल SCU_TASK_DONE_LL_R_ERR:
	हाल SCU_TASK_DONE_LL_PERR:
	हाल SCU_TASK_DONE_REG_ERR:
	हाल SCU_TASK_DONE_SDB_ERR:
	हाल SCU_TASK_OPEN_REJECT_WRONG_DESTINATION:
	हाल SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_1:
	हाल SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_2:
	हाल SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_3:
	हाल SCU_TASK_OPEN_REJECT_BAD_DESTINATION:
	हाल SCU_TASK_OPEN_REJECT_ZONE_VIOLATION:
	हाल SCU_TASK_OPEN_REJECT_STP_RESOURCES_BUSY:
	हाल SCU_TASK_OPEN_REJECT_PROTOCOL_NOT_SUPPORTED:
	हाल SCU_TASK_OPEN_REJECT_CONNECTION_RATE_NOT_SUPPORTED:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक sci_request_stpsata_completion_status_is_tx_rx_suspend(
	अचिन्हित पूर्णांक completion_status)
अणु
	चयन (completion_status) अणु
	हाल SCU_TASK_DONE_LF_ERR:
	हाल SCU_TASK_DONE_LL_SY_TERM:
	हाल SCU_TASK_DONE_LL_LF_TERM:
	हाल SCU_TASK_DONE_BREAK_RCVD:
	हाल SCU_TASK_DONE_INV_FIS_LEN:
	हाल SCU_TASK_DONE_UNEXP_FIS:
	हाल SCU_TASK_DONE_UNEXP_SDBFIS:
	हाल SCU_TASK_DONE_MAX_PLD_ERR:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sci_request_handle_suspending_completions(
	काष्ठा isci_request *ireq,
	u32 completion_code)
अणु
	पूर्णांक is_tx = 0;
	पूर्णांक is_tx_rx = 0;

	चयन (ireq->protocol) अणु
	हाल SAS_PROTOCOL_SMP:
		is_tx = sci_request_smp_completion_status_is_tx_suspend(
			completion_code);
		is_tx_rx = sci_request_smp_completion_status_is_tx_rx_suspend(
			completion_code);
		अवरोध;
	हाल SAS_PROTOCOL_SSP:
		is_tx = sci_request_ssp_completion_status_is_tx_suspend(
			completion_code);
		is_tx_rx = sci_request_ssp_completion_status_is_tx_rx_suspend(
			completion_code);
		अवरोध;
	हाल SAS_PROTOCOL_STP:
		is_tx = sci_request_stpsata_completion_status_is_tx_suspend(
			completion_code);
		is_tx_rx =
			sci_request_stpsata_completion_status_is_tx_rx_suspend(
				completion_code);
		अवरोध;
	शेष:
		dev_warn(&ireq->isci_host->pdev->dev,
			 "%s: request %p has no valid protocol\n",
			 __func__, ireq);
		अवरोध;
	पूर्ण
	अगर (is_tx || is_tx_rx) अणु
		BUG_ON(is_tx && is_tx_rx);

		sci_remote_node_context_suspend(
			&ireq->target_device->rnc,
			SCI_HW_SUSPEND,
			(is_tx_rx) ? SCU_EVENT_TL_RNC_SUSPEND_TX_RX
				   : SCU_EVENT_TL_RNC_SUSPEND_TX);
	पूर्ण
पूर्ण

क्रमागत sci_status
sci_io_request_tc_completion(काष्ठा isci_request *ireq,
			     u32 completion_code)
अणु
	क्रमागत sci_base_request_states state;
	काष्ठा isci_host *ihost = ireq->owning_controller;

	state = ireq->sm.current_state_id;

	/* Decode those completions that संकेत upcoming suspension events. */
	sci_request_handle_suspending_completions(
		ireq, SCU_GET_COMPLETION_TL_STATUS(completion_code));

	चयन (state) अणु
	हाल SCI_REQ_STARTED:
		वापस request_started_state_tc_event(ireq, completion_code);

	हाल SCI_REQ_TASK_WAIT_TC_COMP:
		वापस ssp_task_request_aरुको_tc_event(ireq,
						       completion_code);

	हाल SCI_REQ_SMP_WAIT_RESP:
		वापस smp_request_aरुको_response_tc_event(ireq,
							   completion_code);

	हाल SCI_REQ_SMP_WAIT_TC_COMP:
		वापस smp_request_aरुको_tc_event(ireq, completion_code);

	हाल SCI_REQ_STP_UDMA_WAIT_TC_COMP:
		वापस stp_request_udma_aरुको_tc_event(ireq,
						       completion_code);

	हाल SCI_REQ_STP_NON_DATA_WAIT_H2D:
		वापस stp_request_non_data_aरुको_h2d_tc_event(ireq,
							       completion_code);

	हाल SCI_REQ_STP_PIO_WAIT_H2D:
		वापस stp_request_pio_aरुको_h2d_completion_tc_event(ireq,
								     completion_code);

	हाल SCI_REQ_STP_PIO_DATA_OUT:
		वापस pio_data_out_tx_करोne_tc_event(ireq, completion_code);

	हाल SCI_REQ_ABORTING:
		वापस request_पातing_state_tc_event(ireq,
						       completion_code);

	हाल SCI_REQ_ATAPI_WAIT_H2D:
		वापस atapi_raw_completion(ireq, completion_code,
					    SCI_REQ_ATAPI_WAIT_PIO_SETUP);

	हाल SCI_REQ_ATAPI_WAIT_TC_COMP:
		वापस atapi_raw_completion(ireq, completion_code,
					    SCI_REQ_ATAPI_WAIT_D2H);

	हाल SCI_REQ_ATAPI_WAIT_D2H:
		वापस atapi_data_tc_completion_handler(ireq, completion_code);

	शेष:
		dev_warn(&ihost->pdev->dev, "%s: %x in wrong state %s\n",
			 __func__, completion_code, req_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
पूर्ण

/**
 * isci_request_process_response_iu() - This function sets the status and
 *    response iu, in the task काष्ठा, from the request object क्रम the upper
 *    layer driver.
 * @task: This parameter is the task काष्ठा from the upper layer driver.
 * @resp_iu: This parameter poपूर्णांकs to the response iu of the completed request.
 * @dev: This parameter specअगरies the linux device काष्ठा.
 *
 * none.
 */
अटल व्योम isci_request_process_response_iu(
	काष्ठा sas_task *task,
	काष्ठा ssp_response_iu *resp_iu,
	काष्ठा device *dev)
अणु
	dev_dbg(dev,
		"%s: resp_iu = %p "
		"resp_iu->status = 0x%x,\nresp_iu->datapres = %d "
		"resp_iu->response_data_len = %x, "
		"resp_iu->sense_data_len = %x\nresponse data: ",
		__func__,
		resp_iu,
		resp_iu->status,
		resp_iu->datapres,
		resp_iu->response_data_len,
		resp_iu->sense_data_len);

	task->task_status.stat = resp_iu->status;

	/* libsas updates the task status fields based on the response iu. */
	sas_ssp_task_response(dev, task, resp_iu);
पूर्ण

/**
 * isci_request_set_खोलो_reject_status() - This function prepares the I/O
 *    completion क्रम OPEN_REJECT conditions.
 * @request: This parameter is the completed isci_request object.
 * @task: This parameter is the task काष्ठा from the upper layer driver.
 * @response_ptr: This parameter specअगरies the service response क्रम the I/O.
 * @status_ptr: This parameter specअगरies the exec status क्रम the I/O.
 * @खोलो_rej_reason: This parameter specअगरies the encoded reason क्रम the
 *    abanकरोn-class reject.
 *
 * none.
 */
अटल व्योम isci_request_set_खोलो_reject_status(
	काष्ठा isci_request *request,
	काष्ठा sas_task *task,
	क्रमागत service_response *response_ptr,
	क्रमागत exec_status *status_ptr,
	क्रमागत sas_खोलो_rej_reason खोलो_rej_reason)
अणु
	/* Task in the target is करोne. */
	set_bit(IREQ_COMPLETE_IN_TARGET, &request->flags);
	*response_ptr                     = SAS_TASK_UNDELIVERED;
	*status_ptr                       = SAS_OPEN_REJECT;
	task->task_status.खोलो_rej_reason = खोलो_rej_reason;
पूर्ण

/**
 * isci_request_handle_controller_specअगरic_errors() - This function decodes
 *    controller-specअगरic I/O completion error conditions.
 * @idev: Remote device
 * @request: This parameter is the completed isci_request object.
 * @task: This parameter is the task काष्ठा from the upper layer driver.
 * @response_ptr: This parameter specअगरies the service response क्रम the I/O.
 * @status_ptr: This parameter specअगरies the exec status क्रम the I/O.
 *
 * none.
 */
अटल व्योम isci_request_handle_controller_specअगरic_errors(
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *request,
	काष्ठा sas_task *task,
	क्रमागत service_response *response_ptr,
	क्रमागत exec_status *status_ptr)
अणु
	अचिन्हित पूर्णांक cstatus;

	cstatus = request->scu_status;

	dev_dbg(&request->isci_host->pdev->dev,
		"%s: %p SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR "
		"- controller status = 0x%x\n",
		__func__, request, cstatus);

	/* Decode the controller-specअगरic errors; most
	 * important is to recognize those conditions in which
	 * the target may still have a task outstanding that
	 * must be पातed.
	 *
	 * Note that there are SCU completion codes being
	 * named in the decode below क्रम which SCIC has alपढ़ोy
	 * करोne work to handle them in a way other than as
	 * a controller-specअगरic completion code; these are left
	 * in the decode below क्रम completeness sake.
	 */
	चयन (cstatus) अणु
	हाल SCU_TASK_DONE_DMASETUP_सूचीERR:
	/* Also SCU_TASK_DONE_SMP_FRM_TYPE_ERR: */
	हाल SCU_TASK_DONE_XFERCNT_ERR:
		/* Also SCU_TASK_DONE_SMP_UFI_ERR: */
		अगर (task->task_proto == SAS_PROTOCOL_SMP) अणु
			/* SCU_TASK_DONE_SMP_UFI_ERR == Task Done. */
			*response_ptr = SAS_TASK_COMPLETE;

			/* See अगर the device has been/is being stopped. Note
			 * that we ignore the quiesce state, since we are
			 * concerned about the actual device state.
			 */
			अगर (!idev)
				*status_ptr = SAS_DEVICE_UNKNOWN;
			अन्यथा
				*status_ptr = SAS_ABORTED_TASK;

			set_bit(IREQ_COMPLETE_IN_TARGET, &request->flags);
		पूर्ण अन्यथा अणु
			/* Task in the target is not करोne. */
			*response_ptr = SAS_TASK_UNDELIVERED;

			अगर (!idev)
				*status_ptr = SAS_DEVICE_UNKNOWN;
			अन्यथा
				*status_ptr = SAM_STAT_TASK_ABORTED;

			clear_bit(IREQ_COMPLETE_IN_TARGET, &request->flags);
		पूर्ण

		अवरोध;

	हाल SCU_TASK_DONE_CRC_ERR:
	हाल SCU_TASK_DONE_NAK_CMD_ERR:
	हाल SCU_TASK_DONE_EXCESS_DATA:
	हाल SCU_TASK_DONE_UNEXP_FIS:
	/* Also SCU_TASK_DONE_UNEXP_RESP: */
	हाल SCU_TASK_DONE_VIIT_ENTRY_NV:       /* TODO - conditions? */
	हाल SCU_TASK_DONE_IIT_ENTRY_NV:        /* TODO - conditions? */
	हाल SCU_TASK_DONE_RNCNV_OUTBOUND:      /* TODO - conditions? */
		/* These are conditions in which the target
		 * has completed the task, so that no cleanup
		 * is necessary.
		 */
		*response_ptr = SAS_TASK_COMPLETE;

		/* See अगर the device has been/is being stopped. Note
		 * that we ignore the quiesce state, since we are
		 * concerned about the actual device state.
		 */
		अगर (!idev)
			*status_ptr = SAS_DEVICE_UNKNOWN;
		अन्यथा
			*status_ptr = SAS_ABORTED_TASK;

		set_bit(IREQ_COMPLETE_IN_TARGET, &request->flags);
		अवरोध;


	/* Note that the only खोलो reject completion codes seen here will be
	 * abanकरोn-class codes; all others are स्वतःmatically retried in the SCU.
	 */
	हाल SCU_TASK_OPEN_REJECT_WRONG_DESTINATION:

		isci_request_set_खोलो_reject_status(
			request, task, response_ptr, status_ptr,
			SAS_OREJ_WRONG_DEST);
		अवरोध;

	हाल SCU_TASK_OPEN_REJECT_ZONE_VIOLATION:

		/* Note - the वापस of AB0 will change when
		 * libsas implements detection of zone violations.
		 */
		isci_request_set_खोलो_reject_status(
			request, task, response_ptr, status_ptr,
			SAS_OREJ_RESV_AB0);
		अवरोध;

	हाल SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_1:

		isci_request_set_खोलो_reject_status(
			request, task, response_ptr, status_ptr,
			SAS_OREJ_RESV_AB1);
		अवरोध;

	हाल SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_2:

		isci_request_set_खोलो_reject_status(
			request, task, response_ptr, status_ptr,
			SAS_OREJ_RESV_AB2);
		अवरोध;

	हाल SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_3:

		isci_request_set_खोलो_reject_status(
			request, task, response_ptr, status_ptr,
			SAS_OREJ_RESV_AB3);
		अवरोध;

	हाल SCU_TASK_OPEN_REJECT_BAD_DESTINATION:

		isci_request_set_खोलो_reject_status(
			request, task, response_ptr, status_ptr,
			SAS_OREJ_BAD_DEST);
		अवरोध;

	हाल SCU_TASK_OPEN_REJECT_STP_RESOURCES_BUSY:

		isci_request_set_खोलो_reject_status(
			request, task, response_ptr, status_ptr,
			SAS_OREJ_STP_NORES);
		अवरोध;

	हाल SCU_TASK_OPEN_REJECT_PROTOCOL_NOT_SUPPORTED:

		isci_request_set_खोलो_reject_status(
			request, task, response_ptr, status_ptr,
			SAS_OREJ_EPROTO);
		अवरोध;

	हाल SCU_TASK_OPEN_REJECT_CONNECTION_RATE_NOT_SUPPORTED:

		isci_request_set_खोलो_reject_status(
			request, task, response_ptr, status_ptr,
			SAS_OREJ_CONN_RATE);
		अवरोध;

	हाल SCU_TASK_DONE_LL_R_ERR:
	/* Also SCU_TASK_DONE_ACK_NAK_TO: */
	हाल SCU_TASK_DONE_LL_PERR:
	हाल SCU_TASK_DONE_LL_SY_TERM:
	/* Also SCU_TASK_DONE_NAK_ERR:*/
	हाल SCU_TASK_DONE_LL_LF_TERM:
	/* Also SCU_TASK_DONE_DATA_LEN_ERR: */
	हाल SCU_TASK_DONE_LL_ABORT_ERR:
	हाल SCU_TASK_DONE_SEQ_INV_TYPE:
	/* Also SCU_TASK_DONE_UNEXP_XR: */
	हाल SCU_TASK_DONE_XR_IU_LEN_ERR:
	हाल SCU_TASK_DONE_INV_FIS_LEN:
	/* Also SCU_TASK_DONE_XR_WD_LEN: */
	हाल SCU_TASK_DONE_SDMA_ERR:
	हाल SCU_TASK_DONE_OFFSET_ERR:
	हाल SCU_TASK_DONE_MAX_PLD_ERR:
	हाल SCU_TASK_DONE_LF_ERR:
	हाल SCU_TASK_DONE_SMP_RESP_TO_ERR:  /* Escalate to dev reset? */
	हाल SCU_TASK_DONE_SMP_LL_RX_ERR:
	हाल SCU_TASK_DONE_UNEXP_DATA:
	हाल SCU_TASK_DONE_UNEXP_SDBFIS:
	हाल SCU_TASK_DONE_REG_ERR:
	हाल SCU_TASK_DONE_SDB_ERR:
	हाल SCU_TASK_DONE_TASK_ABORT:
	शेष:
		/* Task in the target is not करोne. */
		*response_ptr = SAS_TASK_UNDELIVERED;
		*status_ptr = SAM_STAT_TASK_ABORTED;

		अगर (task->task_proto == SAS_PROTOCOL_SMP)
			set_bit(IREQ_COMPLETE_IN_TARGET, &request->flags);
		अन्यथा
			clear_bit(IREQ_COMPLETE_IN_TARGET, &request->flags);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम isci_process_stp_response(काष्ठा sas_task *task, काष्ठा dev_to_host_fis *fis)
अणु
	काष्ठा task_status_काष्ठा *ts = &task->task_status;
	काष्ठा ata_task_resp *resp = (व्योम *)&ts->buf[0];

	resp->frame_len = माप(*fis);
	स_नकल(resp->ending_fis, fis, माप(*fis));
	ts->buf_valid_size = माप(*resp);

	/* If an error is flagged let libata decode the fis */
	अगर (ac_err_mask(fis->status))
		ts->stat = SAS_PROTO_RESPONSE;
	अन्यथा
		ts->stat = SAM_STAT_GOOD;

	ts->resp = SAS_TASK_COMPLETE;
पूर्ण

अटल व्योम isci_request_io_request_complete(काष्ठा isci_host *ihost,
					     काष्ठा isci_request *request,
					     क्रमागत sci_io_status completion_status)
अणु
	काष्ठा sas_task *task = isci_request_access_task(request);
	काष्ठा ssp_response_iu *resp_iu;
	अचिन्हित दीर्घ task_flags;
	काष्ठा isci_remote_device *idev = request->target_device;
	क्रमागत service_response response = SAS_TASK_UNDELIVERED;
	क्रमागत exec_status status = SAS_ABORTED_TASK;

	dev_dbg(&ihost->pdev->dev,
		"%s: request = %p, task = %p, "
		"task->data_dir = %d completion_status = 0x%x\n",
		__func__, request, task, task->data_dir, completion_status);

	/* The request is करोne from an SCU HW perspective. */

	/* This is an active request being completed from the core. */
	चयन (completion_status) अणु

	हाल SCI_IO_FAILURE_RESPONSE_VALID:
		dev_dbg(&ihost->pdev->dev,
			"%s: SCI_IO_FAILURE_RESPONSE_VALID (%p/%p)\n",
			__func__, request, task);

		अगर (sas_protocol_ata(task->task_proto)) अणु
			isci_process_stp_response(task, &request->stp.rsp);
		पूर्ण अन्यथा अगर (SAS_PROTOCOL_SSP == task->task_proto) अणु

			/* crack the iu response buffer. */
			resp_iu = &request->ssp.rsp;
			isci_request_process_response_iu(task, resp_iu,
							 &ihost->pdev->dev);

		पूर्ण अन्यथा अगर (SAS_PROTOCOL_SMP == task->task_proto) अणु

			dev_err(&ihost->pdev->dev,
				"%s: SCI_IO_FAILURE_RESPONSE_VALID: "
					"SAS_PROTOCOL_SMP protocol\n",
				__func__);

		पूर्ण अन्यथा
			dev_err(&ihost->pdev->dev,
				"%s: unknown protocol\n", __func__);

		/* use the task status set in the task काष्ठा by the
		* isci_request_process_response_iu call.
		*/
		set_bit(IREQ_COMPLETE_IN_TARGET, &request->flags);
		response = task->task_status.resp;
		status = task->task_status.stat;
		अवरोध;

	हाल SCI_IO_SUCCESS:
	हाल SCI_IO_SUCCESS_IO_DONE_EARLY:

		response = SAS_TASK_COMPLETE;
		status   = SAM_STAT_GOOD;
		set_bit(IREQ_COMPLETE_IN_TARGET, &request->flags);

		अगर (completion_status == SCI_IO_SUCCESS_IO_DONE_EARLY) अणु

			/* This was an SSP / STP / SATA transfer.
			* There is a possibility that less data than
			* the maximum was transferred.
			*/
			u32 transferred_length = sci_req_tx_bytes(request);

			task->task_status.residual
				= task->total_xfer_len - transferred_length;

			/* If there were residual bytes, call this an
			* underrun.
			*/
			अगर (task->task_status.residual != 0)
				status = SAS_DATA_UNDERRUN;

			dev_dbg(&ihost->pdev->dev,
				"%s: SCI_IO_SUCCESS_IO_DONE_EARLY %d\n",
				__func__, status);

		पूर्ण अन्यथा
			dev_dbg(&ihost->pdev->dev, "%s: SCI_IO_SUCCESS\n",
				__func__);
		अवरोध;

	हाल SCI_IO_FAILURE_TERMINATED:

		dev_dbg(&ihost->pdev->dev,
			"%s: SCI_IO_FAILURE_TERMINATED (%p/%p)\n",
			__func__, request, task);

		/* The request was terminated explicitly. */
		set_bit(IREQ_COMPLETE_IN_TARGET, &request->flags);
		response = SAS_TASK_UNDELIVERED;

		/* See अगर the device has been/is being stopped. Note
		* that we ignore the quiesce state, since we are
		* concerned about the actual device state.
		*/
		अगर (!idev)
			status = SAS_DEVICE_UNKNOWN;
		अन्यथा
			status = SAS_ABORTED_TASK;
		अवरोध;

	हाल SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR:

		isci_request_handle_controller_specअगरic_errors(idev, request,
							       task, &response,
							       &status);
		अवरोध;

	हाल SCI_IO_FAILURE_REMOTE_DEVICE_RESET_REQUIRED:
		/* This is a special हाल, in that the I/O completion
		* is telling us that the device needs a reset.
		* In order क्रम the device reset condition to be
		* noticed, the I/O has to be handled in the error
		* handler.  Set the reset flag and cause the
		* SCSI error thपढ़ो to be scheduled.
		*/
		spin_lock_irqsave(&task->task_state_lock, task_flags);
		task->task_state_flags |= SAS_TASK_NEED_DEV_RESET;
		spin_unlock_irqrestore(&task->task_state_lock, task_flags);

		/* Fail the I/O. */
		response = SAS_TASK_UNDELIVERED;
		status = SAM_STAT_TASK_ABORTED;

		clear_bit(IREQ_COMPLETE_IN_TARGET, &request->flags);
		अवरोध;

	हाल SCI_FAILURE_RETRY_REQUIRED:

		/* Fail the I/O so it can be retried. */
		response = SAS_TASK_UNDELIVERED;
		अगर (!idev)
			status = SAS_DEVICE_UNKNOWN;
		अन्यथा
			status = SAS_ABORTED_TASK;

		set_bit(IREQ_COMPLETE_IN_TARGET, &request->flags);
		अवरोध;


	शेष:
		/* Catch any otherwise unhandled error codes here. */
		dev_dbg(&ihost->pdev->dev,
			"%s: invalid completion code: 0x%x - "
				"isci_request = %p\n",
			__func__, completion_status, request);

		response = SAS_TASK_UNDELIVERED;

		/* See अगर the device has been/is being stopped. Note
		* that we ignore the quiesce state, since we are
		* concerned about the actual device state.
		*/
		अगर (!idev)
			status = SAS_DEVICE_UNKNOWN;
		अन्यथा
			status = SAS_ABORTED_TASK;

		अगर (SAS_PROTOCOL_SMP == task->task_proto)
			set_bit(IREQ_COMPLETE_IN_TARGET, &request->flags);
		अन्यथा
			clear_bit(IREQ_COMPLETE_IN_TARGET, &request->flags);
		अवरोध;
	पूर्ण

	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SSP:
		अगर (task->data_dir == DMA_NONE)
			अवरोध;
		अगर (task->num_scatter == 0)
			/* 0 indicates a single dma address */
			dma_unmap_single(&ihost->pdev->dev,
					 request->zero_scatter_daddr,
					 task->total_xfer_len, task->data_dir);
		अन्यथा  /* unmap the sgl dma addresses */
			dma_unmap_sg(&ihost->pdev->dev, task->scatter,
				     request->num_sg_entries, task->data_dir);
		अवरोध;
	हाल SAS_PROTOCOL_SMP: अणु
		काष्ठा scatterlist *sg = &task->smp_task.smp_req;
		काष्ठा smp_req *smp_req;
		व्योम *kaddr;

		dma_unmap_sg(&ihost->pdev->dev, sg, 1, DMA_TO_DEVICE);

		/* need to swab it back in हाल the command buffer is re-used */
		kaddr = kmap_atomic(sg_page(sg));
		smp_req = kaddr + sg->offset;
		sci_swab32_cpy(smp_req, smp_req, sg->length / माप(u32));
		kunmap_atomic(kaddr);
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&task->task_state_lock, task_flags);

	task->task_status.resp = response;
	task->task_status.stat = status;

	अगर (test_bit(IREQ_COMPLETE_IN_TARGET, &request->flags)) अणु
		/* Normal notअगरication (task_करोne) */
		task->task_state_flags |= SAS_TASK_STATE_DONE;
		task->task_state_flags &= ~(SAS_TASK_AT_INITIATOR |
					    SAS_TASK_STATE_PENDING);
	पूर्ण
	spin_unlock_irqrestore(&task->task_state_lock, task_flags);

	/* complete the io request to the core. */
	sci_controller_complete_io(ihost, request->target_device, request);

	/* set terminated handle so it cannot be completed or
	 * terminated again, and to cause any calls पूर्णांकo पात
	 * task to recognize the alपढ़ोy completed हाल.
	 */
	set_bit(IREQ_TERMINATED, &request->flags);

	ireq_करोne(ihost, request, task);
पूर्ण

अटल व्योम sci_request_started_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_request *ireq = container_of(sm, typeof(*ireq), sm);
	काष्ठा करोमुख्य_device *dev = ireq->target_device->करोमुख्य_dev;
	क्रमागत sci_base_request_states state;
	काष्ठा sas_task *task;

	/* XXX as hch said always creating an पूर्णांकernal sas_task क्रम पंचांगf
	 * requests would simplअगरy the driver
	 */
	task = (test_bit(IREQ_TMF, &ireq->flags)) ? शून्य : isci_request_access_task(ireq);

	/* all unaccelerated request types (non ssp or ncq) handled with
	 * substates
	 */
	अगर (!task && dev->dev_type == SAS_END_DEVICE) अणु
		state = SCI_REQ_TASK_WAIT_TC_COMP;
	पूर्ण अन्यथा अगर (task && task->task_proto == SAS_PROTOCOL_SMP) अणु
		state = SCI_REQ_SMP_WAIT_RESP;
	पूर्ण अन्यथा अगर (task && sas_protocol_ata(task->task_proto) &&
		   !task->ata_task.use_ncq) अणु
		अगर (dev->sata_dev.class == ATA_DEV_ATAPI &&
			task->ata_task.fis.command == ATA_CMD_PACKET) अणु
			state = SCI_REQ_ATAPI_WAIT_H2D;
		पूर्ण अन्यथा अगर (task->data_dir == DMA_NONE) अणु
			state = SCI_REQ_STP_NON_DATA_WAIT_H2D;
		पूर्ण अन्यथा अगर (task->ata_task.dma_xfer) अणु
			state = SCI_REQ_STP_UDMA_WAIT_TC_COMP;
		पूर्ण अन्यथा /* PIO */ अणु
			state = SCI_REQ_STP_PIO_WAIT_H2D;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* SSP or NCQ are fully accelerated, no substates */
		वापस;
	पूर्ण
	sci_change_state(sm, state);
पूर्ण

अटल व्योम sci_request_completed_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_request *ireq = container_of(sm, typeof(*ireq), sm);
	काष्ठा isci_host *ihost = ireq->owning_controller;

	/* Tell the SCI_USER that the IO request is complete */
	अगर (!test_bit(IREQ_TMF, &ireq->flags))
		isci_request_io_request_complete(ihost, ireq,
						 ireq->sci_status);
	अन्यथा
		isci_task_request_complete(ihost, ireq, ireq->sci_status);
पूर्ण

अटल व्योम sci_request_पातing_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_request *ireq = container_of(sm, typeof(*ireq), sm);

	/* Setting the पात bit in the Task Context is required by the silicon. */
	ireq->tc->पात = 1;
पूर्ण

अटल व्योम sci_stp_request_started_non_data_aरुको_h2d_completion_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_request *ireq = container_of(sm, typeof(*ireq), sm);

	ireq->target_device->working_request = ireq;
पूर्ण

अटल व्योम sci_stp_request_started_pio_aरुको_h2d_completion_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_request *ireq = container_of(sm, typeof(*ireq), sm);

	ireq->target_device->working_request = ireq;
पूर्ण

अटल स्थिर काष्ठा sci_base_state sci_request_state_table[] = अणु
	[SCI_REQ_INIT] = अणु पूर्ण,
	[SCI_REQ_CONSTRUCTED] = अणु पूर्ण,
	[SCI_REQ_STARTED] = अणु
		.enter_state = sci_request_started_state_enter,
	पूर्ण,
	[SCI_REQ_STP_NON_DATA_WAIT_H2D] = अणु
		.enter_state = sci_stp_request_started_non_data_aरुको_h2d_completion_enter,
	पूर्ण,
	[SCI_REQ_STP_NON_DATA_WAIT_D2H] = अणु पूर्ण,
	[SCI_REQ_STP_PIO_WAIT_H2D] = अणु
		.enter_state = sci_stp_request_started_pio_aरुको_h2d_completion_enter,
	पूर्ण,
	[SCI_REQ_STP_PIO_WAIT_FRAME] = अणु पूर्ण,
	[SCI_REQ_STP_PIO_DATA_IN] = अणु पूर्ण,
	[SCI_REQ_STP_PIO_DATA_OUT] = अणु पूर्ण,
	[SCI_REQ_STP_UDMA_WAIT_TC_COMP] = अणु पूर्ण,
	[SCI_REQ_STP_UDMA_WAIT_D2H] = अणु पूर्ण,
	[SCI_REQ_TASK_WAIT_TC_COMP] = अणु पूर्ण,
	[SCI_REQ_TASK_WAIT_TC_RESP] = अणु पूर्ण,
	[SCI_REQ_SMP_WAIT_RESP] = अणु पूर्ण,
	[SCI_REQ_SMP_WAIT_TC_COMP] = अणु पूर्ण,
	[SCI_REQ_ATAPI_WAIT_H2D] = अणु पूर्ण,
	[SCI_REQ_ATAPI_WAIT_PIO_SETUP] = अणु पूर्ण,
	[SCI_REQ_ATAPI_WAIT_D2H] = अणु पूर्ण,
	[SCI_REQ_ATAPI_WAIT_TC_COMP] = अणु पूर्ण,
	[SCI_REQ_COMPLETED] = अणु
		.enter_state = sci_request_completed_state_enter,
	पूर्ण,
	[SCI_REQ_ABORTING] = अणु
		.enter_state = sci_request_पातing_state_enter,
	पूर्ण,
	[SCI_REQ_FINAL] = अणु पूर्ण,
पूर्ण;

अटल व्योम
sci_general_request_स्थिरruct(काष्ठा isci_host *ihost,
				   काष्ठा isci_remote_device *idev,
				   काष्ठा isci_request *ireq)
अणु
	sci_init_sm(&ireq->sm, sci_request_state_table, SCI_REQ_INIT);

	ireq->target_device = idev;
	ireq->protocol = SAS_PROTOCOL_NONE;
	ireq->saved_rx_frame_index = SCU_INVALID_FRAME_INDEX;

	ireq->sci_status   = SCI_SUCCESS;
	ireq->scu_status   = 0;
	ireq->post_context = 0xFFFFFFFF;
पूर्ण

अटल क्रमागत sci_status
sci_io_request_स्थिरruct(काष्ठा isci_host *ihost,
			  काष्ठा isci_remote_device *idev,
			  काष्ठा isci_request *ireq)
अणु
	काष्ठा करोमुख्य_device *dev = idev->करोमुख्य_dev;
	क्रमागत sci_status status = SCI_SUCCESS;

	/* Build the common part of the request */
	sci_general_request_स्थिरruct(ihost, idev, ireq);

	अगर (idev->rnc.remote_node_index == SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX)
		वापस SCI_FAILURE_INVALID_REMOTE_DEVICE;

	अगर (dev->dev_type == SAS_END_DEVICE)
		/* pass */;
	अन्यथा अगर (dev_is_sata(dev))
		स_रखो(&ireq->stp.cmd, 0, माप(ireq->stp.cmd));
	अन्यथा अगर (dev_is_expander(dev->dev_type))
		/* pass */;
	अन्यथा
		वापस SCI_FAILURE_UNSUPPORTED_PROTOCOL;

	स_रखो(ireq->tc, 0, दुरत्व(काष्ठा scu_task_context, sgl_pair_ab));

	वापस status;
पूर्ण

क्रमागत sci_status sci_task_request_स्थिरruct(काष्ठा isci_host *ihost,
					    काष्ठा isci_remote_device *idev,
					    u16 io_tag, काष्ठा isci_request *ireq)
अणु
	काष्ठा करोमुख्य_device *dev = idev->करोमुख्य_dev;
	क्रमागत sci_status status = SCI_SUCCESS;

	/* Build the common part of the request */
	sci_general_request_स्थिरruct(ihost, idev, ireq);

	अगर (dev->dev_type == SAS_END_DEVICE || dev_is_sata(dev)) अणु
		set_bit(IREQ_TMF, &ireq->flags);
		स_रखो(ireq->tc, 0, माप(काष्ठा scu_task_context));

		/* Set the protocol indicator. */
		अगर (dev_is_sata(dev))
			ireq->protocol = SAS_PROTOCOL_STP;
		अन्यथा
			ireq->protocol = SAS_PROTOCOL_SSP;
	पूर्ण अन्यथा
		status = SCI_FAILURE_UNSUPPORTED_PROTOCOL;

	वापस status;
पूर्ण

अटल क्रमागत sci_status isci_request_ssp_request_स्थिरruct(
	काष्ठा isci_request *request)
अणु
	क्रमागत sci_status status;

	dev_dbg(&request->isci_host->pdev->dev,
		"%s: request = %p\n",
		__func__,
		request);
	status = sci_io_request_स्थिरruct_basic_ssp(request);
	वापस status;
पूर्ण

अटल क्रमागत sci_status isci_request_stp_request_स्थिरruct(काष्ठा isci_request *ireq)
अणु
	काष्ठा sas_task *task = isci_request_access_task(ireq);
	काष्ठा host_to_dev_fis *fis = &ireq->stp.cmd;
	काष्ठा ata_queued_cmd *qc = task->uldd_task;
	क्रमागत sci_status status;

	dev_dbg(&ireq->isci_host->pdev->dev,
		"%s: ireq = %p\n",
		__func__,
		ireq);

	स_नकल(fis, &task->ata_task.fis, माप(काष्ठा host_to_dev_fis));
	अगर (!task->ata_task.device_control_reg_update)
		fis->flags |= 0x80;
	fis->flags &= 0xF0;

	status = sci_io_request_स्थिरruct_basic_sata(ireq);

	अगर (qc && (qc->tf.command == ATA_CMD_FPDMA_WRITE ||
		   qc->tf.command == ATA_CMD_FPDMA_READ ||
		   qc->tf.command == ATA_CMD_FPDMA_RECV ||
		   qc->tf.command == ATA_CMD_FPDMA_SEND ||
		   qc->tf.command == ATA_CMD_NCQ_NON_DATA)) अणु
		fis->sector_count = qc->tag << 3;
		ireq->tc->type.stp.ncq_tag = qc->tag;
	पूर्ण

	वापस status;
पूर्ण

अटल क्रमागत sci_status
sci_io_request_स्थिरruct_smp(काष्ठा device *dev,
			      काष्ठा isci_request *ireq,
			      काष्ठा sas_task *task)
अणु
	काष्ठा scatterlist *sg = &task->smp_task.smp_req;
	काष्ठा isci_remote_device *idev;
	काष्ठा scu_task_context *task_context;
	काष्ठा isci_port *iport;
	काष्ठा smp_req *smp_req;
	व्योम *kaddr;
	u8 req_len;
	u32 cmd;

	kaddr = kmap_atomic(sg_page(sg));
	smp_req = kaddr + sg->offset;
	/*
	 * Look at the SMP requests' header fields; क्रम certain SAS 1.x SMP
	 * functions under SAS 2.0, a zero request length really indicates
	 * a non-zero शेष length.
	 */
	अगर (smp_req->req_len == 0) अणु
		चयन (smp_req->func) अणु
		हाल SMP_DISCOVER:
		हाल SMP_REPORT_PHY_ERR_LOG:
		हाल SMP_REPORT_PHY_SATA:
		हाल SMP_REPORT_ROUTE_INFO:
			smp_req->req_len = 2;
			अवरोध;
		हाल SMP_CONF_ROUTE_INFO:
		हाल SMP_PHY_CONTROL:
		हाल SMP_PHY_TEST_FUNCTION:
			smp_req->req_len = 9;
			अवरोध;
			/* Default - zero is a valid शेष क्रम 2.0. */
		पूर्ण
	पूर्ण
	req_len = smp_req->req_len;
	sci_swab32_cpy(smp_req, smp_req, sg->length / माप(u32));
	cmd = *(u32 *) smp_req;
	kunmap_atomic(kaddr);

	अगर (!dma_map_sg(dev, sg, 1, DMA_TO_DEVICE))
		वापस SCI_FAILURE;

	ireq->protocol = SAS_PROTOCOL_SMP;

	/* byte swap the smp request. */

	task_context = ireq->tc;

	idev = ireq->target_device;
	iport = idev->owning_port;

	/*
	 * Fill in the TC with its required data
	 * 00h
	 */
	task_context->priority = 0;
	task_context->initiator_request = 1;
	task_context->connection_rate = idev->connection_rate;
	task_context->protocol_engine_index = ISCI_PEG;
	task_context->logical_port_index = iport->physical_port_index;
	task_context->protocol_type = SCU_TASK_CONTEXT_PROTOCOL_SMP;
	task_context->पात = 0;
	task_context->valid = SCU_TASK_CONTEXT_VALID;
	task_context->context_type = SCU_TASK_CONTEXT_TYPE;

	/* 04h */
	task_context->remote_node_index = idev->rnc.remote_node_index;
	task_context->command_code = 0;
	task_context->task_type = SCU_TASK_TYPE_SMP_REQUEST;

	/* 08h */
	task_context->link_layer_control = 0;
	task_context->करो_not_dma_ssp_good_response = 1;
	task_context->strict_ordering = 0;
	task_context->control_frame = 1;
	task_context->समयout_enable = 0;
	task_context->block_guard_enable = 0;

	/* 0ch */
	task_context->address_modअगरier = 0;

	/* 10h */
	task_context->ssp_command_iu_length = req_len;

	/* 14h */
	task_context->transfer_length_bytes = 0;

	/*
	 * 18h ~ 30h, protocol specअगरic
	 * since commandIU has been build by framework at this poपूर्णांक, we just
	 * copy the frist DWord from command IU to this location. */
	स_नकल(&task_context->type.smp, &cmd, माप(u32));

	/*
	 * 40h
	 * "For SMP you could program it to zero. We would prefer that way
	 * so that करोne code will be consistent." - Venki
	 */
	task_context->task_phase = 0;

	ireq->post_context = (SCU_CONTEXT_COMMAND_REQUEST_TYPE_POST_TC |
			      (ISCI_PEG << SCU_CONTEXT_COMMAND_PROTOCOL_ENGINE_GROUP_SHIFT) |
			       (iport->physical_port_index <<
				SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT) |
			      ISCI_TAG_TCI(ireq->io_tag));
	/*
	 * Copy the physical address क्रम the command buffer to the SCU Task
	 * Context command buffer should not contain command header.
	 */
	task_context->command_iu_upper = upper_32_bits(sg_dma_address(sg));
	task_context->command_iu_lower = lower_32_bits(sg_dma_address(sg) + माप(u32));

	/* SMP response comes as UF, so no need to set response IU address. */
	task_context->response_iu_upper = 0;
	task_context->response_iu_lower = 0;

	sci_change_state(&ireq->sm, SCI_REQ_CONSTRUCTED);

	वापस SCI_SUCCESS;
पूर्ण

/*
 * isci_smp_request_build() - This function builds the smp request.
 * @ireq: This parameter poपूर्णांकs to the isci_request allocated in the
 *    request स्थिरruct function.
 *
 * SCI_SUCCESS on successfull completion, or specअगरic failure code.
 */
अटल क्रमागत sci_status isci_smp_request_build(काष्ठा isci_request *ireq)
अणु
	काष्ठा sas_task *task = isci_request_access_task(ireq);
	काष्ठा device *dev = &ireq->isci_host->pdev->dev;
	क्रमागत sci_status status = SCI_FAILURE;

	status = sci_io_request_स्थिरruct_smp(dev, ireq, task);
	अगर (status != SCI_SUCCESS)
		dev_dbg(&ireq->isci_host->pdev->dev,
			 "%s: failed with status = %d\n",
			 __func__,
			 status);

	वापस status;
पूर्ण

/**
 * isci_io_request_build() - This function builds the io request object.
 * @ihost: This parameter specअगरies the ISCI host object
 * @request: This parameter poपूर्णांकs to the isci_request object allocated in the
 *    request स्थिरruct function.
 * @idev: This parameter is the handle क्रम the sci core's remote device
 *    object that is the destination क्रम this request.
 *
 * SCI_SUCCESS on successfull completion, or specअगरic failure code.
 */
अटल क्रमागत sci_status isci_io_request_build(काष्ठा isci_host *ihost,
					     काष्ठा isci_request *request,
					     काष्ठा isci_remote_device *idev)
अणु
	क्रमागत sci_status status = SCI_SUCCESS;
	काष्ठा sas_task *task = isci_request_access_task(request);

	dev_dbg(&ihost->pdev->dev,
		"%s: idev = 0x%p; request = %p, "
		"num_scatter = %d\n",
		__func__,
		idev,
		request,
		task->num_scatter);

	/* map the sgl addresses, अगर present.
	 * libata करोes the mapping क्रम sata devices
	 * beक्रमe we get the request.
	 */
	अगर (task->num_scatter &&
	    !sas_protocol_ata(task->task_proto) &&
	    !(SAS_PROTOCOL_SMP & task->task_proto)) अणु

		request->num_sg_entries = dma_map_sg(
			&ihost->pdev->dev,
			task->scatter,
			task->num_scatter,
			task->data_dir
			);

		अगर (request->num_sg_entries == 0)
			वापस SCI_FAILURE_INSUFFICIENT_RESOURCES;
	पूर्ण

	status = sci_io_request_स्थिरruct(ihost, idev, request);

	अगर (status != SCI_SUCCESS) अणु
		dev_dbg(&ihost->pdev->dev,
			 "%s: failed request construct\n",
			 __func__);
		वापस SCI_FAILURE;
	पूर्ण

	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SMP:
		status = isci_smp_request_build(request);
		अवरोध;
	हाल SAS_PROTOCOL_SSP:
		status = isci_request_ssp_request_स्थिरruct(request);
		अवरोध;
	हाल SAS_PROTOCOL_SATA:
	हाल SAS_PROTOCOL_STP:
	हाल SAS_PROTOCOL_SATA | SAS_PROTOCOL_STP:
		status = isci_request_stp_request_स्थिरruct(request);
		अवरोध;
	शेष:
		dev_dbg(&ihost->pdev->dev,
			 "%s: unknown protocol\n", __func__);
		वापस SCI_FAILURE;
	पूर्ण

	वापस SCI_SUCCESS;
पूर्ण

अटल काष्ठा isci_request *isci_request_from_tag(काष्ठा isci_host *ihost, u16 tag)
अणु
	काष्ठा isci_request *ireq;

	ireq = ihost->reqs[ISCI_TAG_TCI(tag)];
	ireq->io_tag = tag;
	ireq->io_request_completion = शून्य;
	ireq->flags = 0;
	ireq->num_sg_entries = 0;

	वापस ireq;
पूर्ण

अटल काष्ठा isci_request *isci_io_request_from_tag(काष्ठा isci_host *ihost,
						     काष्ठा sas_task *task,
						     u16 tag)
अणु
	काष्ठा isci_request *ireq;

	ireq = isci_request_from_tag(ihost, tag);
	ireq->ttype_ptr.io_task_ptr = task;
	clear_bit(IREQ_TMF, &ireq->flags);
	task->lldd_task = ireq;

	वापस ireq;
पूर्ण

काष्ठा isci_request *isci_पंचांगf_request_from_tag(काष्ठा isci_host *ihost,
					       काष्ठा isci_पंचांगf *isci_पंचांगf,
					       u16 tag)
अणु
	काष्ठा isci_request *ireq;

	ireq = isci_request_from_tag(ihost, tag);
	ireq->ttype_ptr.पंचांगf_task_ptr = isci_पंचांगf;
	set_bit(IREQ_TMF, &ireq->flags);

	वापस ireq;
पूर्ण

पूर्णांक isci_request_execute(काष्ठा isci_host *ihost, काष्ठा isci_remote_device *idev,
			 काष्ठा sas_task *task, u16 tag)
अणु
	क्रमागत sci_status status;
	काष्ठा isci_request *ireq;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/* करो common allocation and init of request object. */
	ireq = isci_io_request_from_tag(ihost, task, tag);

	status = isci_io_request_build(ihost, ireq, idev);
	अगर (status != SCI_SUCCESS) अणु
		dev_dbg(&ihost->pdev->dev,
			 "%s: request_construct failed - status = 0x%x\n",
			 __func__,
			 status);
		वापस status;
	पूर्ण

	spin_lock_irqsave(&ihost->scic_lock, flags);

	अगर (test_bit(IDEV_IO_NCQERROR, &idev->flags)) अणु

		अगर (isci_task_is_ncq_recovery(task)) अणु

			/* The device is in an NCQ recovery state.  Issue the
			 * request on the task side.  Note that it will
			 * complete on the I/O request side because the
			 * request was built that way (ie.
			 * ireq->is_task_management_request is false).
			 */
			status = sci_controller_start_task(ihost,
							    idev,
							    ireq);
		पूर्ण अन्यथा अणु
			status = SCI_FAILURE;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* send the request, let the core assign the IO TAG.	*/
		status = sci_controller_start_io(ihost, idev,
						  ireq);
	पूर्ण

	अगर (status != SCI_SUCCESS &&
	    status != SCI_FAILURE_REMOTE_DEVICE_RESET_REQUIRED) अणु
		dev_dbg(&ihost->pdev->dev,
			 "%s: failed request start (0x%x)\n",
			 __func__, status);
		spin_unlock_irqrestore(&ihost->scic_lock, flags);
		वापस status;
	पूर्ण
	/* Either I/O started OK, or the core has संकेतed that
	 * the device needs a target reset.
	 */
	अगर (status != SCI_SUCCESS) अणु
		/* The request did not really start in the
		 * hardware, so clear the request handle
		 * here so no terminations will be करोne.
		 */
		set_bit(IREQ_TERMINATED, &ireq->flags);
	पूर्ण
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	अगर (status ==
	    SCI_FAILURE_REMOTE_DEVICE_RESET_REQUIRED) अणु
		/* Signal libsas that we need the SCSI error
		 * handler thपढ़ो to work on this I/O and that
		 * we want a device reset.
		 */
		spin_lock_irqsave(&task->task_state_lock, flags);
		task->task_state_flags |= SAS_TASK_NEED_DEV_RESET;
		spin_unlock_irqrestore(&task->task_state_lock, flags);

		/* Cause this task to be scheduled in the SCSI error
		 * handler thपढ़ो.
		 */
		sas_task_पात(task);

		/* Change the status, since we are holding
		 * the I/O until it is managed by the SCSI
		 * error handler.
		 */
		status = SCI_SUCCESS;
	पूर्ण

	वापस ret;
पूर्ण
