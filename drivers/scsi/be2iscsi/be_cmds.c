<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017 Broadcom. All Rights Reserved.
 * The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 * Contact Inक्रमmation:
 * linux-drivers@broadcom.com
 */

#समावेश <scsi/iscsi_proto.h>

#समावेश "be_main.h"
#समावेश "be.h"
#समावेश "be_mgmt.h"

/* UE Status Low CSR */
अटल स्थिर अक्षर * स्थिर desc_ue_status_low[] = अणु
	"CEV",
	"CTX",
	"DBUF",
	"ERX",
	"Host",
	"MPU",
	"NDMA",
	"PTC ",
	"RDMA ",
	"RXF ",
	"RXIPS ",
	"RXULP0 ",
	"RXULP1 ",
	"RXULP2 ",
	"TIM ",
	"TPOST ",
	"TPRE ",
	"TXIPS ",
	"TXULP0 ",
	"TXULP1 ",
	"UC ",
	"WDMA ",
	"TXULP2 ",
	"HOST1 ",
	"P0_OB_LINK ",
	"P1_OB_LINK ",
	"HOST_GPIO ",
	"MBOX ",
	"AXGMAC0",
	"AXGMAC1",
	"JTAG",
	"MPU_INTPEND"
पूर्ण;

/* UE Status High CSR */
अटल स्थिर अक्षर * स्थिर desc_ue_status_hi[] = अणु
	"LPCMEMHOST",
	"MGMT_MAC",
	"PCS0ONLINE",
	"MPU_IRAM",
	"PCS1ONLINE",
	"PCTL0",
	"PCTL1",
	"PMEM",
	"RR",
	"TXPB",
	"RXPP",
	"XAUI",
	"TXP",
	"ARM",
	"IPC",
	"HOST2",
	"HOST3",
	"HOST4",
	"HOST5",
	"HOST6",
	"HOST7",
	"HOST8",
	"HOST9",
	"NETC",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown"
पूर्ण;

काष्ठा be_mcc_wrb *alloc_mcc_wrb(काष्ठा beiscsi_hba *phba,
				 अचिन्हित पूर्णांक *ref_tag)
अणु
	काष्ठा be_queue_info *mccq = &phba->ctrl.mcc_obj.q;
	काष्ठा be_mcc_wrb *wrb = शून्य;
	अचिन्हित पूर्णांक tag;

	spin_lock(&phba->ctrl.mcc_lock);
	अगर (mccq->used == mccq->len) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT |
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
			    "BC_%d : MCC queue full: WRB used %u tag avail %u\n",
			    mccq->used, phba->ctrl.mcc_tag_available);
		जाओ alloc_failed;
	पूर्ण

	अगर (!phba->ctrl.mcc_tag_available)
		जाओ alloc_failed;

	tag = phba->ctrl.mcc_tag[phba->ctrl.mcc_alloc_index];
	अगर (!tag) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT |
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
			    "BC_%d : MCC tag 0 allocated: tag avail %u alloc index %u\n",
			    phba->ctrl.mcc_tag_available,
			    phba->ctrl.mcc_alloc_index);
		जाओ alloc_failed;
	पूर्ण

	/* वापस this tag क्रम further reference */
	*ref_tag = tag;
	phba->ctrl.mcc_tag[phba->ctrl.mcc_alloc_index] = 0;
	phba->ctrl.mcc_tag_status[tag] = 0;
	phba->ctrl.ptag_state[tag].tag_state = 0;
	phba->ctrl.ptag_state[tag].cbfn = शून्य;
	phba->ctrl.mcc_tag_available--;
	अगर (phba->ctrl.mcc_alloc_index == (MAX_MCC_CMD - 1))
		phba->ctrl.mcc_alloc_index = 0;
	अन्यथा
		phba->ctrl.mcc_alloc_index++;

	wrb = queue_head_node(mccq);
	स_रखो(wrb, 0, माप(*wrb));
	wrb->tag0 = tag;
	wrb->tag0 |= (mccq->head << MCC_Q_WRB_IDX_SHIFT) & MCC_Q_WRB_IDX_MASK;
	queue_head_inc(mccq);
	mccq->used++;

alloc_failed:
	spin_unlock(&phba->ctrl.mcc_lock);
	वापस wrb;
पूर्ण

व्योम मुक्त_mcc_wrb(काष्ठा be_ctrl_info *ctrl, अचिन्हित पूर्णांक tag)
अणु
	काष्ठा be_queue_info *mccq = &ctrl->mcc_obj.q;

	spin_lock(&ctrl->mcc_lock);
	tag = tag & MCC_Q_CMD_TAG_MASK;
	ctrl->mcc_tag[ctrl->mcc_मुक्त_index] = tag;
	अगर (ctrl->mcc_मुक्त_index == (MAX_MCC_CMD - 1))
		ctrl->mcc_मुक्त_index = 0;
	अन्यथा
		ctrl->mcc_मुक्त_index++;
	ctrl->mcc_tag_available++;
	mccq->used--;
	spin_unlock(&ctrl->mcc_lock);
पूर्ण

/*
 * beiscsi_mcc_compl_status - Return the status of MCC completion
 * @phba: Driver निजी काष्ठाure
 * @tag: Tag क्रम the MBX Command
 * @wrb: the WRB used क्रम the MBX Command
 * @mbx_cmd_mem: ptr to memory allocated क्रम MBX Cmd
 *
 * वापस
 * Success: 0
 * Failure: Non-Zero
 */
पूर्णांक __beiscsi_mcc_compl_status(काष्ठा beiscsi_hba *phba,
			       अचिन्हित पूर्णांक tag,
			       काष्ठा be_mcc_wrb **wrb,
			       काष्ठा be_dma_mem *mbx_cmd_mem)
अणु
	काष्ठा be_queue_info *mccq = &phba->ctrl.mcc_obj.q;
	uपूर्णांक16_t status = 0, addl_status = 0, wrb_num = 0;
	काष्ठा be_cmd_resp_hdr *mbx_resp_hdr;
	काष्ठा be_cmd_req_hdr *mbx_hdr;
	काष्ठा be_mcc_wrb *temp_wrb;
	uपूर्णांक32_t mcc_tag_status;
	पूर्णांक rc = 0;

	mcc_tag_status = phba->ctrl.mcc_tag_status[tag];
	status = (mcc_tag_status & CQE_STATUS_MASK);
	addl_status = ((mcc_tag_status & CQE_STATUS_ADDL_MASK) >>
			CQE_STATUS_ADDL_SHIFT);

	अगर (mbx_cmd_mem) अणु
		mbx_hdr = (काष्ठा be_cmd_req_hdr *)mbx_cmd_mem->va;
	पूर्ण अन्यथा अणु
		wrb_num = (mcc_tag_status & CQE_STATUS_WRB_MASK) >>
			  CQE_STATUS_WRB_SHIFT;
		temp_wrb = (काष्ठा be_mcc_wrb *)queue_get_wrb(mccq, wrb_num);
		mbx_hdr = embedded_payload(temp_wrb);

		अगर (wrb)
			*wrb = temp_wrb;
	पूर्ण

	अगर (status || addl_status) अणु
		beiscsi_log(phba, KERN_WARNING,
			    BEISCSI_LOG_INIT | BEISCSI_LOG_EH |
			    BEISCSI_LOG_CONFIG,
			    "BC_%d : MBX Cmd Failed for Subsys : %d Opcode : %d with Status : %d and Extd_Status : %d\n",
			    mbx_hdr->subप्रणाली, mbx_hdr->opcode,
			    status, addl_status);
		rc = -EIO;
		अगर (status == MCC_STATUS_INSUFFICIENT_BUFFER) अणु
			mbx_resp_hdr = (काष्ठा be_cmd_resp_hdr *)mbx_hdr;
			beiscsi_log(phba, KERN_WARNING,
				    BEISCSI_LOG_INIT | BEISCSI_LOG_EH |
				    BEISCSI_LOG_CONFIG,
				    "BC_%d : Insufficient Buffer Error Resp_Len : %d Actual_Resp_Len : %d\n",
				    mbx_resp_hdr->response_length,
				    mbx_resp_hdr->actual_resp_len);
			rc = -EAGAIN;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/*
 * beiscsi_mccq_compl_रुको()- Process completion in MCC CQ
 * @phba: Driver निजी काष्ठाure
 * @tag: Tag क्रम the MBX Command
 * @wrb: the WRB used क्रम the MBX Command
 * @mbx_cmd_mem: ptr to memory allocated क्रम MBX Cmd
 *
 * Waits क्रम MBX completion with the passed TAG.
 *
 * वापस
 * Success: 0
 * Failure: Non-Zero
 **/
पूर्णांक beiscsi_mccq_compl_रुको(काष्ठा beiscsi_hba *phba,
			    अचिन्हित पूर्णांक tag,
			    काष्ठा be_mcc_wrb **wrb,
			    काष्ठा be_dma_mem *mbx_cmd_mem)
अणु
	पूर्णांक rc = 0;

	अगर (!tag || tag > MAX_MCC_CMD) अणु
		__beiscsi_log(phba, KERN_ERR,
			      "BC_%d : invalid tag %u\n", tag);
		वापस -EINVAL;
	पूर्ण

	अगर (beiscsi_hba_in_error(phba)) अणु
		clear_bit(MCC_TAG_STATE_RUNNING,
			  &phba->ctrl.ptag_state[tag].tag_state);
		वापस -EIO;
	पूर्ण

	/* रुको क्रम the mccq completion */
	rc = रुको_event_पूर्णांकerruptible_समयout(phba->ctrl.mcc_रुको[tag],
					      phba->ctrl.mcc_tag_status[tag],
					      msecs_to_jअगरfies(
						BEISCSI_HOST_MBX_TIMEOUT));
	/**
	 * Return EIO अगर port is being disabled. Associated DMA memory, अगर any,
	 * is मुक्तd by the caller. When port goes offline, MCCQ is cleaned up
	 * so करोes WRB.
	 */
	अगर (!test_bit(BEISCSI_HBA_ONLINE, &phba->state)) अणु
		clear_bit(MCC_TAG_STATE_RUNNING,
			  &phba->ctrl.ptag_state[tag].tag_state);
		वापस -EIO;
	पूर्ण

	/**
	 * If MBOX cmd समयout expired, tag and resource allocated
	 * क्रम cmd is not मुक्तd until FW वापसs completion.
	 */
	अगर (rc <= 0) अणु
		काष्ठा be_dma_mem *tag_mem;

		/**
		 * PCI/DMA memory allocated and posted in non-embedded mode
		 * will have mbx_cmd_mem != शून्य.
		 * Save भव and bus addresses क्रम the command so that it
		 * can be मुक्तd later.
		 **/
		tag_mem = &phba->ctrl.ptag_state[tag].tag_mem_state;
		अगर (mbx_cmd_mem) अणु
			tag_mem->size = mbx_cmd_mem->size;
			tag_mem->va = mbx_cmd_mem->va;
			tag_mem->dma = mbx_cmd_mem->dma;
		पूर्ण अन्यथा
			tag_mem->size = 0;

		/* first make tag_mem_state visible to all */
		wmb();
		set_bit(MCC_TAG_STATE_TIMEOUT,
				&phba->ctrl.ptag_state[tag].tag_state);

		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_INIT | BEISCSI_LOG_EH |
			    BEISCSI_LOG_CONFIG,
			    "BC_%d : MBX Cmd Completion timed out\n");
		वापस -EBUSY;
	पूर्ण

	rc = __beiscsi_mcc_compl_status(phba, tag, wrb, mbx_cmd_mem);

	मुक्त_mcc_wrb(&phba->ctrl, tag);
	वापस rc;
पूर्ण

/*
 * beiscsi_process_mbox_compl()- Check the MBX completion status
 * @ctrl: Function specअगरic MBX data काष्ठाure
 * @compl: Completion status of MBX Command
 *
 * Check क्रम the MBX completion status when BMBX method used
 *
 * वापस
 * Success: Zero
 * Failure: Non-Zero
 **/
अटल पूर्णांक beiscsi_process_mbox_compl(काष्ठा be_ctrl_info *ctrl,
				      काष्ठा be_mcc_compl *compl)
अणु
	काष्ठा be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	काष्ठा beiscsi_hba *phba = pci_get_drvdata(ctrl->pdev);
	काष्ठा be_cmd_req_hdr *hdr = embedded_payload(wrb);
	u16 compl_status, extd_status;

	/**
	 * To check अगर valid bit is set, check the entire word as we करोn't know
	 * the endianness of the data (old entry is host endian जबतक a new
	 * entry is little endian)
	 */
	अगर (!compl->flags) अणु
		beiscsi_log(phba, KERN_ERR,
				BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
				"BC_%d : BMBX busy, no completion\n");
		वापस -EBUSY;
	पूर्ण
	compl->flags = le32_to_cpu(compl->flags);
	WARN_ON((compl->flags & CQE_FLAGS_VALID_MASK) == 0);

	/**
	 * Just swap the status to host endian;
	 * mcc tag is opaquely copied from mcc_wrb.
	 */
	be_dws_le_to_cpu(compl, 4);
	compl_status = (compl->status >> CQE_STATUS_COMPL_SHIFT) &
		CQE_STATUS_COMPL_MASK;
	extd_status = (compl->status >> CQE_STATUS_EXTD_SHIFT) &
		CQE_STATUS_EXTD_MASK;
	/* Need to reset the entire word that houses the valid bit */
	compl->flags = 0;

	अगर (compl_status == MCC_STATUS_SUCCESS)
		वापस 0;

	beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
		    "BC_%d : error in cmd completion: Subsystem : %d Opcode : %d status(compl/extd)=%d/%d\n",
		    hdr->subप्रणाली, hdr->opcode, compl_status, extd_status);
	वापस compl_status;
पूर्ण

अटल व्योम beiscsi_process_async_link(काष्ठा beiscsi_hba *phba,
				       काष्ठा be_mcc_compl *compl)
अणु
	काष्ठा be_async_event_link_state *evt;

	evt = (काष्ठा be_async_event_link_state *)compl;

	phba->port_speed = evt->port_speed;
	/**
	 * Check logical link status in ASYNC event.
	 * This has been newly पूर्णांकroduced in SKH-R Firmware 10.0.338.45.
	 **/
	अगर (evt->port_link_status & BE_ASYNC_LINK_UP_MASK) अणु
		set_bit(BEISCSI_HBA_LINK_UP, &phba->state);
		अगर (test_bit(BEISCSI_HBA_BOOT_FOUND, &phba->state))
			beiscsi_start_boot_work(phba, BE_BOOT_INVALID_SHANDLE);
		__beiscsi_log(phba, KERN_ERR,
			      "BC_%d : Link Up on Port %d tag 0x%x\n",
			      evt->physical_port, evt->event_tag);
	पूर्ण अन्यथा अणु
		clear_bit(BEISCSI_HBA_LINK_UP, &phba->state);
		__beiscsi_log(phba, KERN_ERR,
			      "BC_%d : Link Down on Port %d tag 0x%x\n",
			      evt->physical_port, evt->event_tag);
		iscsi_host_क्रम_each_session(phba->shost,
					    beiscsi_session_fail);
	पूर्ण
पूर्ण

अटल अक्षर *beiscsi_port_misconf_event_msg[] = अणु
	"Physical Link is functional.",
	"Optics faulted/incorrectly installed/not installed - Reseat optics, if issue not resolved, replace.",
	"Optics of two types installed - Remove one optic or install matching pair of optics.",
	"Incompatible optics - Replace with compatible optics for card to function.",
	"Unqualified optics - Replace with Avago optics for Warranty and Technical Support.",
	"Uncertified optics - Replace with Avago Certified optics to enable link operation."
पूर्ण;

अटल व्योम beiscsi_process_async_sli(काष्ठा beiscsi_hba *phba,
				      काष्ठा be_mcc_compl *compl)
अणु
	काष्ठा be_async_event_sli *async_sli;
	u8 evt_type, state, old_state, le;
	अक्षर *sev = KERN_WARNING;
	अक्षर *msg = शून्य;

	evt_type = compl->flags >> ASYNC_TRAILER_EVENT_TYPE_SHIFT;
	evt_type &= ASYNC_TRAILER_EVENT_TYPE_MASK;

	/* processing only MISCONFIGURED physical port event */
	अगर (evt_type != ASYNC_SLI_EVENT_TYPE_MISCONFIGURED)
		वापस;

	async_sli = (काष्ठा be_async_event_sli *)compl;
	state = async_sli->event_data1 >>
		 (phba->fw_config.phys_port * 8) & 0xff;
	le = async_sli->event_data2 >>
		 (phba->fw_config.phys_port * 8) & 0xff;

	old_state = phba->optic_state;
	phba->optic_state = state;

	अगर (state >= ARRAY_SIZE(beiscsi_port_misconf_event_msg)) अणु
		/* fw is reporting a state we करोn't know, log and वापस */
		__beiscsi_log(phba, KERN_ERR,
			    "BC_%d : Port %c: Unrecognized optic state 0x%x\n",
			    phba->port_name, async_sli->event_data1);
		वापस;
	पूर्ण

	अगर (ASYNC_SLI_LINK_EFFECT_VALID(le)) अणु
		/* log link effect क्रम unqualअगरied-4, uncertअगरied-5 optics */
		अगर (state > 3)
			msg = (ASYNC_SLI_LINK_EFFECT_STATE(le)) ?
				" Link is non-operational." :
				" Link is operational.";
		/* 1 - info */
		अगर (ASYNC_SLI_LINK_EFFECT_SEV(le) == 1)
			sev = KERN_INFO;
		/* 2 - error */
		अगर (ASYNC_SLI_LINK_EFFECT_SEV(le) == 2)
			sev = KERN_ERR;
	पूर्ण

	अगर (old_state != phba->optic_state)
		__beiscsi_log(phba, sev, "BC_%d : Port %c: %s%s\n",
			      phba->port_name,
			      beiscsi_port_misconf_event_msg[state],
			      !msg ? "" : msg);
पूर्ण

व्योम beiscsi_process_async_event(काष्ठा beiscsi_hba *phba,
				काष्ठा be_mcc_compl *compl)
अणु
	अक्षर *sev = KERN_INFO;
	u8 evt_code;

	/* पूर्णांकerpret flags as an async trailer */
	evt_code = compl->flags >> ASYNC_TRAILER_EVENT_CODE_SHIFT;
	evt_code &= ASYNC_TRAILER_EVENT_CODE_MASK;
	चयन (evt_code) अणु
	हाल ASYNC_EVENT_CODE_LINK_STATE:
		beiscsi_process_async_link(phba, compl);
		अवरोध;
	हाल ASYNC_EVENT_CODE_ISCSI:
		अगर (test_bit(BEISCSI_HBA_BOOT_FOUND, &phba->state))
			beiscsi_start_boot_work(phba, BE_BOOT_INVALID_SHANDLE);
		sev = KERN_ERR;
		अवरोध;
	हाल ASYNC_EVENT_CODE_SLI:
		beiscsi_process_async_sli(phba, compl);
		अवरोध;
	शेष:
		/* event not रेजिस्टरed */
		sev = KERN_ERR;
	पूर्ण

	beiscsi_log(phba, sev, BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
		    "BC_%d : ASYNC Event %x: status 0x%08x flags 0x%08x\n",
		    evt_code, compl->status, compl->flags);
पूर्ण

पूर्णांक beiscsi_process_mcc_compl(काष्ठा be_ctrl_info *ctrl,
			      काष्ठा be_mcc_compl *compl)
अणु
	काष्ठा beiscsi_hba *phba = pci_get_drvdata(ctrl->pdev);
	u16 compl_status, extd_status;
	काष्ठा be_dma_mem *tag_mem;
	अचिन्हित पूर्णांक tag, wrb_idx;

	be_dws_le_to_cpu(compl, 4);
	tag = (compl->tag0 & MCC_Q_CMD_TAG_MASK);
	wrb_idx = (compl->tag0 & CQE_STATUS_WRB_MASK) >> CQE_STATUS_WRB_SHIFT;

	अगर (!test_bit(MCC_TAG_STATE_RUNNING,
		      &ctrl->ptag_state[tag].tag_state)) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_MBOX |
			    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
			    "BC_%d : MBX cmd completed but not posted\n");
		वापस 0;
	पूर्ण

	/* end MCC with this tag */
	clear_bit(MCC_TAG_STATE_RUNNING, &ctrl->ptag_state[tag].tag_state);

	अगर (test_bit(MCC_TAG_STATE_TIMEOUT, &ctrl->ptag_state[tag].tag_state)) अणु
		beiscsi_log(phba, KERN_WARNING,
			    BEISCSI_LOG_MBOX | BEISCSI_LOG_INIT |
			    BEISCSI_LOG_CONFIG,
			    "BC_%d : MBX Completion for timeout Command from FW\n");
		/**
		 * Check क्रम the size beक्रमe मुक्तing resource.
		 * Only क्रम non-embedded cmd, PCI resource is allocated.
		 **/
		tag_mem = &ctrl->ptag_state[tag].tag_mem_state;
		अगर (tag_mem->size) अणु
			dma_मुक्त_coherent(&ctrl->pdev->dev, tag_mem->size,
					tag_mem->va, tag_mem->dma);
			tag_mem->size = 0;
		पूर्ण
		मुक्त_mcc_wrb(ctrl, tag);
		वापस 0;
	पूर्ण

	compl_status = (compl->status >> CQE_STATUS_COMPL_SHIFT) &
		       CQE_STATUS_COMPL_MASK;
	extd_status = (compl->status >> CQE_STATUS_EXTD_SHIFT) &
		      CQE_STATUS_EXTD_MASK;
	/* The ctrl.mcc_tag_status[tag] is filled with
	 * [31] = valid, [30:24] = Rsvd, [23:16] = wrb, [15:8] = extd_status,
	 * [7:0] = compl_status
	 */
	ctrl->mcc_tag_status[tag] = CQE_VALID_MASK;
	ctrl->mcc_tag_status[tag] |= (wrb_idx << CQE_STATUS_WRB_SHIFT);
	ctrl->mcc_tag_status[tag] |= (extd_status << CQE_STATUS_ADDL_SHIFT) &
				     CQE_STATUS_ADDL_MASK;
	ctrl->mcc_tag_status[tag] |= (compl_status & CQE_STATUS_MASK);

	अगर (test_bit(MCC_TAG_STATE_ASYNC, &ctrl->ptag_state[tag].tag_state)) अणु
		अगर (ctrl->ptag_state[tag].cbfn)
			ctrl->ptag_state[tag].cbfn(phba, tag);
		अन्यथा
			__beiscsi_log(phba, KERN_ERR,
				      "BC_%d : MBX ASYNC command with no callback\n");
		मुक्त_mcc_wrb(ctrl, tag);
		वापस 0;
	पूर्ण

	अगर (test_bit(MCC_TAG_STATE_IGNORE, &ctrl->ptag_state[tag].tag_state)) अणु
		/* just check completion status and मुक्त wrb */
		__beiscsi_mcc_compl_status(phba, tag, शून्य, शून्य);
		मुक्त_mcc_wrb(ctrl, tag);
		वापस 0;
	पूर्ण

	wake_up_पूर्णांकerruptible(&ctrl->mcc_रुको[tag]);
	वापस 0;
पूर्ण

व्योम be_mcc_notअगरy(काष्ठा beiscsi_hba *phba, अचिन्हित पूर्णांक tag)
अणु
	काष्ठा be_queue_info *mccq = &phba->ctrl.mcc_obj.q;
	u32 val = 0;

	set_bit(MCC_TAG_STATE_RUNNING, &phba->ctrl.ptag_state[tag].tag_state);
	val |= mccq->id & DB_MCCQ_RING_ID_MASK;
	val |= 1 << DB_MCCQ_NUM_POSTED_SHIFT;
	/* make request available क्रम DMA */
	wmb();
	ioग_लिखो32(val, phba->db_va + DB_MCCQ_OFFSET);
पूर्ण

/*
 * be_mbox_db_पढ़ोy_poll()- Check पढ़ोy status
 * @ctrl: Function specअगरic MBX data काष्ठाure
 *
 * Check क्रम the पढ़ोy status of FW to send BMBX
 * commands to adapter.
 *
 * वापस
 * Success: 0
 * Failure: Non-Zero
 **/
अटल पूर्णांक be_mbox_db_पढ़ोy_poll(काष्ठा be_ctrl_info *ctrl)
अणु
	/* रुको 30s क्रम generic non-flash MBOX operation */
#घोषणा BEISCSI_MBX_RDY_BIT_TIMEOUT	30000
	व्योम __iomem *db = ctrl->db + MPU_MAILBOX_DB_OFFSET;
	काष्ठा beiscsi_hba *phba = pci_get_drvdata(ctrl->pdev);
	अचिन्हित दीर्घ समयout;
	u32 पढ़ोy;

	/*
	 * This BMBX busy रुको path is used during init only.
	 * For the commands executed during init, 5s should suffice.
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(BEISCSI_MBX_RDY_BIT_TIMEOUT);
	करो अणु
		अगर (beiscsi_hba_in_error(phba))
			वापस -EIO;

		पढ़ोy = ioपढ़ो32(db);
		अगर (पढ़ोy == 0xffffffff)
			वापस -EIO;

		पढ़ोy &= MPU_MAILBOX_DB_RDY_MASK;
		अगर (पढ़ोy)
			वापस 0;

		अगर (समय_after(jअगरfies, समयout))
			अवरोध;
		/* 1ms sleep is enough in most हालs */
		schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(1));
	पूर्ण जबतक (!पढ़ोy);

	beiscsi_log(phba, KERN_ERR,
			BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
			"BC_%d : FW Timed Out\n");
	set_bit(BEISCSI_HBA_FW_TIMEOUT, &phba->state);
	वापस -EBUSY;
पूर्ण

/*
 * be_mbox_notअगरy: Notअगरy adapter of new BMBX command
 * @ctrl: Function specअगरic MBX data काष्ठाure
 *
 * Ring करोorbell to inक्रमm adapter of a BMBX command
 * to process
 *
 * वापस
 * Success: 0
 * Failure: Non-Zero
 **/
अटल पूर्णांक be_mbox_notअगरy(काष्ठा be_ctrl_info *ctrl)
अणु
	पूर्णांक status;
	u32 val = 0;
	व्योम __iomem *db = ctrl->db + MPU_MAILBOX_DB_OFFSET;
	काष्ठा be_dma_mem *mbox_mem = &ctrl->mbox_mem;
	काष्ठा be_mcc_mailbox *mbox = mbox_mem->va;

	status = be_mbox_db_पढ़ोy_poll(ctrl);
	अगर (status)
		वापस status;

	val &= ~MPU_MAILBOX_DB_RDY_MASK;
	val |= MPU_MAILBOX_DB_HI_MASK;
	val |= (upper_32_bits(mbox_mem->dma) >> 2) << 2;
	ioग_लिखो32(val, db);

	status = be_mbox_db_पढ़ोy_poll(ctrl);
	अगर (status)
		वापस status;

	val = 0;
	val &= ~MPU_MAILBOX_DB_RDY_MASK;
	val &= ~MPU_MAILBOX_DB_HI_MASK;
	val |= (u32) (mbox_mem->dma >> 4) << 2;
	ioग_लिखो32(val, db);

	status = be_mbox_db_पढ़ोy_poll(ctrl);
	अगर (status)
		वापस status;

	/* RDY is set; small delay beक्रमe CQE पढ़ो. */
	udelay(1);

	status = beiscsi_process_mbox_compl(ctrl, &mbox->compl);
	वापस status;
पूर्ण

व्योम be_wrb_hdr_prepare(काष्ठा be_mcc_wrb *wrb, u32 payload_len,
			bool embedded, u8 sge_cnt)
अणु
	अगर (embedded)
		wrb->emb_sgecnt_special |= MCC_WRB_EMBEDDED_MASK;
	अन्यथा
		wrb->emb_sgecnt_special |= (sge_cnt & MCC_WRB_SGE_CNT_MASK) <<
					   MCC_WRB_SGE_CNT_SHIFT;
	wrb->payload_length = payload_len;
	be_dws_cpu_to_le(wrb, 8);
पूर्ण

व्योम be_cmd_hdr_prepare(काष्ठा be_cmd_req_hdr *req_hdr,
			u8 subप्रणाली, u8 opcode, u32 cmd_len)
अणु
	req_hdr->opcode = opcode;
	req_hdr->subप्रणाली = subप्रणाली;
	req_hdr->request_length = cpu_to_le32(cmd_len - माप(*req_hdr));
	req_hdr->समयout = BEISCSI_FW_MBX_TIMEOUT;
पूर्ण

अटल व्योम be_cmd_page_addrs_prepare(काष्ठा phys_addr *pages, u32 max_pages,
							काष्ठा be_dma_mem *mem)
अणु
	पूर्णांक i, buf_pages;
	u64 dma = (u64) mem->dma;

	buf_pages = min(PAGES_4K_SPANNED(mem->va, mem->size), max_pages);
	क्रम (i = 0; i < buf_pages; i++) अणु
		pages[i].lo = cpu_to_le32(dma & 0xFFFFFFFF);
		pages[i].hi = cpu_to_le32(upper_32_bits(dma));
		dma += PAGE_SIZE_4K;
	पूर्ण
पूर्ण

अटल u32 eq_delay_to_mult(u32 usec_delay)
अणु
#घोषणा MAX_INTR_RATE 651042
	स्थिर u32 round = 10;
	u32 multiplier;

	अगर (usec_delay == 0)
		multiplier = 0;
	अन्यथा अणु
		u32 पूर्णांकerrupt_rate = 1000000 / usec_delay;
		अगर (पूर्णांकerrupt_rate == 0)
			multiplier = 1023;
		अन्यथा अणु
			multiplier = (MAX_INTR_RATE - पूर्णांकerrupt_rate) * round;
			multiplier /= पूर्णांकerrupt_rate;
			multiplier = (multiplier + round / 2) / round;
			multiplier = min(multiplier, (u32) 1023);
		पूर्ण
	पूर्ण
	वापस multiplier;
पूर्ण

काष्ठा be_mcc_wrb *wrb_from_mbox(काष्ठा be_dma_mem *mbox_mem)
अणु
	वापस &((काष्ठा be_mcc_mailbox *)(mbox_mem->va))->wrb;
पूर्ण

पूर्णांक beiscsi_cmd_eq_create(काष्ठा be_ctrl_info *ctrl,
			  काष्ठा be_queue_info *eq, पूर्णांक eq_delay)
अणु
	काष्ठा be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	काष्ठा be_cmd_req_eq_create *req = embedded_payload(wrb);
	काष्ठा be_cmd_resp_eq_create *resp = embedded_payload(wrb);
	काष्ठा be_dma_mem *q_mem = &eq->dma_mem;
	पूर्णांक status;

	mutex_lock(&ctrl->mbox_lock);
	स_रखो(wrb, 0, माप(*wrb));

	be_wrb_hdr_prepare(wrb, माप(*req), true, 0);

	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			OPCODE_COMMON_EQ_CREATE, माप(*req));

	req->num_pages = cpu_to_le16(PAGES_4K_SPANNED(q_mem->va, q_mem->size));

	AMAP_SET_BITS(काष्ठा amap_eq_context, func, req->context,
						PCI_FUNC(ctrl->pdev->devfn));
	AMAP_SET_BITS(काष्ठा amap_eq_context, valid, req->context, 1);
	AMAP_SET_BITS(काष्ठा amap_eq_context, size, req->context, 0);
	AMAP_SET_BITS(काष्ठा amap_eq_context, count, req->context,
					__ilog2_u32(eq->len / 256));
	AMAP_SET_BITS(काष्ठा amap_eq_context, delaymult, req->context,
					eq_delay_to_mult(eq_delay));
	be_dws_cpu_to_le(req->context, माप(req->context));

	be_cmd_page_addrs_prepare(req->pages, ARRAY_SIZE(req->pages), q_mem);

	status = be_mbox_notअगरy(ctrl);
	अगर (!status) अणु
		eq->id = le16_to_cpu(resp->eq_id);
		eq->created = true;
	पूर्ण
	mutex_unlock(&ctrl->mbox_lock);
	वापस status;
पूर्ण

पूर्णांक beiscsi_cmd_cq_create(काष्ठा be_ctrl_info *ctrl,
			  काष्ठा be_queue_info *cq, काष्ठा be_queue_info *eq,
			  bool sol_evts, bool no_delay, पूर्णांक coalesce_wm)
अणु
	काष्ठा be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	काष्ठा be_cmd_req_cq_create *req = embedded_payload(wrb);
	काष्ठा be_cmd_resp_cq_create *resp = embedded_payload(wrb);
	काष्ठा beiscsi_hba *phba = pci_get_drvdata(ctrl->pdev);
	काष्ठा be_dma_mem *q_mem = &cq->dma_mem;
	व्योम *ctxt = &req->context;
	पूर्णांक status;

	mutex_lock(&ctrl->mbox_lock);
	स_रखो(wrb, 0, माप(*wrb));

	be_wrb_hdr_prepare(wrb, माप(*req), true, 0);

	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			OPCODE_COMMON_CQ_CREATE, माप(*req));

	req->num_pages = cpu_to_le16(PAGES_4K_SPANNED(q_mem->va, q_mem->size));
	अगर (is_chip_be2_be3r(phba)) अणु
		AMAP_SET_BITS(काष्ठा amap_cq_context, coalescwm,
			      ctxt, coalesce_wm);
		AMAP_SET_BITS(काष्ठा amap_cq_context, nodelay, ctxt, no_delay);
		AMAP_SET_BITS(काष्ठा amap_cq_context, count, ctxt,
			      __ilog2_u32(cq->len / 256));
		AMAP_SET_BITS(काष्ठा amap_cq_context, valid, ctxt, 1);
		AMAP_SET_BITS(काष्ठा amap_cq_context, solevent, ctxt, sol_evts);
		AMAP_SET_BITS(काष्ठा amap_cq_context, eventable, ctxt, 1);
		AMAP_SET_BITS(काष्ठा amap_cq_context, eqid, ctxt, eq->id);
		AMAP_SET_BITS(काष्ठा amap_cq_context, armed, ctxt, 1);
		AMAP_SET_BITS(काष्ठा amap_cq_context, func, ctxt,
			      PCI_FUNC(ctrl->pdev->devfn));
	पूर्ण अन्यथा अणु
		req->hdr.version = MBX_CMD_VER2;
		req->page_size = 1;
		AMAP_SET_BITS(काष्ठा amap_cq_context_v2, coalescwm,
			      ctxt, coalesce_wm);
		AMAP_SET_BITS(काष्ठा amap_cq_context_v2, nodelay,
			      ctxt, no_delay);
		AMAP_SET_BITS(काष्ठा amap_cq_context_v2, count, ctxt,
			      __ilog2_u32(cq->len / 256));
		AMAP_SET_BITS(काष्ठा amap_cq_context_v2, valid, ctxt, 1);
		AMAP_SET_BITS(काष्ठा amap_cq_context_v2, eventable, ctxt, 1);
		AMAP_SET_BITS(काष्ठा amap_cq_context_v2, eqid, ctxt, eq->id);
		AMAP_SET_BITS(काष्ठा amap_cq_context_v2, armed, ctxt, 1);
	पूर्ण

	be_dws_cpu_to_le(ctxt, माप(req->context));

	be_cmd_page_addrs_prepare(req->pages, ARRAY_SIZE(req->pages), q_mem);

	status = be_mbox_notअगरy(ctrl);
	अगर (!status) अणु
		cq->id = le16_to_cpu(resp->cq_id);
		cq->created = true;
	पूर्ण अन्यथा
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BC_%d : In be_cmd_cq_create, status=ox%08x\n",
			    status);

	mutex_unlock(&ctrl->mbox_lock);

	वापस status;
पूर्ण

अटल u32 be_encoded_q_len(पूर्णांक q_len)
अणु
	u32 len_encoded = fls(q_len);	/* log2(len) + 1 */
	अगर (len_encoded == 16)
		len_encoded = 0;
	वापस len_encoded;
पूर्ण

पूर्णांक beiscsi_cmd_mccq_create(काष्ठा beiscsi_hba *phba,
			काष्ठा be_queue_info *mccq,
			काष्ठा be_queue_info *cq)
अणु
	काष्ठा be_mcc_wrb *wrb;
	काष्ठा be_cmd_req_mcc_create_ext *req;
	काष्ठा be_dma_mem *q_mem = &mccq->dma_mem;
	काष्ठा be_ctrl_info *ctrl;
	व्योम *ctxt;
	पूर्णांक status;

	mutex_lock(&phba->ctrl.mbox_lock);
	ctrl = &phba->ctrl;
	wrb = wrb_from_mbox(&ctrl->mbox_mem);
	स_रखो(wrb, 0, माप(*wrb));
	req = embedded_payload(wrb);
	ctxt = &req->context;

	be_wrb_hdr_prepare(wrb, माप(*req), true, 0);

	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			OPCODE_COMMON_MCC_CREATE_EXT, माप(*req));

	req->num_pages = PAGES_4K_SPANNED(q_mem->va, q_mem->size);
	req->async_evt_biपंचांगap = 1 << ASYNC_EVENT_CODE_LINK_STATE;
	req->async_evt_biपंचांगap |= 1 << ASYNC_EVENT_CODE_ISCSI;
	req->async_evt_biपंचांगap |= 1 << ASYNC_EVENT_CODE_SLI;

	AMAP_SET_BITS(काष्ठा amap_mcc_context, fid, ctxt,
		      PCI_FUNC(phba->pcidev->devfn));
	AMAP_SET_BITS(काष्ठा amap_mcc_context, valid, ctxt, 1);
	AMAP_SET_BITS(काष्ठा amap_mcc_context, ring_size, ctxt,
		be_encoded_q_len(mccq->len));
	AMAP_SET_BITS(काष्ठा amap_mcc_context, cq_id, ctxt, cq->id);

	be_dws_cpu_to_le(ctxt, माप(req->context));

	be_cmd_page_addrs_prepare(req->pages, ARRAY_SIZE(req->pages), q_mem);

	status = be_mbox_notअगरy(ctrl);
	अगर (!status) अणु
		काष्ठा be_cmd_resp_mcc_create *resp = embedded_payload(wrb);
		mccq->id = le16_to_cpu(resp->id);
		mccq->created = true;
	पूर्ण
	mutex_unlock(&phba->ctrl.mbox_lock);

	वापस status;
पूर्ण

पूर्णांक beiscsi_cmd_q_destroy(काष्ठा be_ctrl_info *ctrl, काष्ठा be_queue_info *q,
			  पूर्णांक queue_type)
अणु
	काष्ठा be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	काष्ठा be_cmd_req_q_destroy *req = embedded_payload(wrb);
	काष्ठा beiscsi_hba *phba = pci_get_drvdata(ctrl->pdev);
	u8 subsys = 0, opcode = 0;
	पूर्णांक status;

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
		    "BC_%d : In beiscsi_cmd_q_destroy "
		    "queue_type : %d\n", queue_type);

	mutex_lock(&ctrl->mbox_lock);
	स_रखो(wrb, 0, माप(*wrb));
	be_wrb_hdr_prepare(wrb, माप(*req), true, 0);

	चयन (queue_type) अणु
	हाल QTYPE_EQ:
		subsys = CMD_SUBSYSTEM_COMMON;
		opcode = OPCODE_COMMON_EQ_DESTROY;
		अवरोध;
	हाल QTYPE_CQ:
		subsys = CMD_SUBSYSTEM_COMMON;
		opcode = OPCODE_COMMON_CQ_DESTROY;
		अवरोध;
	हाल QTYPE_MCCQ:
		subsys = CMD_SUBSYSTEM_COMMON;
		opcode = OPCODE_COMMON_MCC_DESTROY;
		अवरोध;
	हाल QTYPE_WRBQ:
		subsys = CMD_SUBSYSTEM_ISCSI;
		opcode = OPCODE_COMMON_ISCSI_WRBQ_DESTROY;
		अवरोध;
	हाल QTYPE_DPDUQ:
		subsys = CMD_SUBSYSTEM_ISCSI;
		opcode = OPCODE_COMMON_ISCSI_DEFQ_DESTROY;
		अवरोध;
	हाल QTYPE_SGL:
		subsys = CMD_SUBSYSTEM_ISCSI;
		opcode = OPCODE_COMMON_ISCSI_CFG_REMOVE_SGL_PAGES;
		अवरोध;
	शेष:
		mutex_unlock(&ctrl->mbox_lock);
		BUG();
	पूर्ण
	be_cmd_hdr_prepare(&req->hdr, subsys, opcode, माप(*req));
	अगर (queue_type != QTYPE_SGL)
		req->id = cpu_to_le16(q->id);

	status = be_mbox_notअगरy(ctrl);

	mutex_unlock(&ctrl->mbox_lock);
	वापस status;
पूर्ण

/**
 * be_cmd_create_शेष_pdu_queue()- Create DEFQ क्रम the adapter
 * @ctrl: ptr to ctrl_info
 * @cq: Completion Queue
 * @dq: Default Queue
 * @length: ring size
 * @entry_size: size of each entry in DEFQ
 * @is_header: Header or Data DEFQ
 * @ulp_num: Bind to which ULP
 *
 * Create HDR/Data DEFQ क्रम the passed ULP. Unsol PDU are posted
 * on this queue by the FW
 *
 * वापस
 *	Success: 0
 *	Failure: Non-Zero Value
 *
 **/
पूर्णांक be_cmd_create_शेष_pdu_queue(काष्ठा be_ctrl_info *ctrl,
				    काष्ठा be_queue_info *cq,
				    काष्ठा be_queue_info *dq, पूर्णांक length,
				    पूर्णांक entry_size, uपूर्णांक8_t is_header,
				    uपूर्णांक8_t ulp_num)
अणु
	काष्ठा be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	काष्ठा be_defq_create_req *req = embedded_payload(wrb);
	काष्ठा be_dma_mem *q_mem = &dq->dma_mem;
	काष्ठा beiscsi_hba *phba = pci_get_drvdata(ctrl->pdev);
	व्योम *ctxt = &req->context;
	पूर्णांक status;

	mutex_lock(&ctrl->mbox_lock);
	स_रखो(wrb, 0, माप(*wrb));

	be_wrb_hdr_prepare(wrb, माप(*req), true, 0);

	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI,
			   OPCODE_COMMON_ISCSI_DEFQ_CREATE, माप(*req));

	req->num_pages = PAGES_4K_SPANNED(q_mem->va, q_mem->size);
	अगर (phba->fw_config.dual_ulp_aware) अणु
		req->ulp_num = ulp_num;
		req->dua_feature |= (1 << BEISCSI_DUAL_ULP_AWARE_BIT);
		req->dua_feature |= (1 << BEISCSI_BIND_Q_TO_ULP_BIT);
	पूर्ण

	अगर (is_chip_be2_be3r(phba)) अणु
		AMAP_SET_BITS(काष्ठा amap_be_शेष_pdu_context,
			      rx_pdid, ctxt, 0);
		AMAP_SET_BITS(काष्ठा amap_be_शेष_pdu_context,
			      rx_pdid_valid, ctxt, 1);
		AMAP_SET_BITS(काष्ठा amap_be_शेष_pdu_context,
			      pci_func_id, ctxt, PCI_FUNC(ctrl->pdev->devfn));
		AMAP_SET_BITS(काष्ठा amap_be_शेष_pdu_context,
			      ring_size, ctxt,
			      be_encoded_q_len(length /
			      माप(काष्ठा phys_addr)));
		AMAP_SET_BITS(काष्ठा amap_be_शेष_pdu_context,
			      शेष_buffer_size, ctxt, entry_size);
		AMAP_SET_BITS(काष्ठा amap_be_शेष_pdu_context,
			      cq_id_recv, ctxt,	cq->id);
	पूर्ण अन्यथा अणु
		AMAP_SET_BITS(काष्ठा amap_शेष_pdu_context_ext,
			      rx_pdid, ctxt, 0);
		AMAP_SET_BITS(काष्ठा amap_शेष_pdu_context_ext,
			      rx_pdid_valid, ctxt, 1);
		AMAP_SET_BITS(काष्ठा amap_शेष_pdu_context_ext,
			      ring_size, ctxt,
			      be_encoded_q_len(length /
			      माप(काष्ठा phys_addr)));
		AMAP_SET_BITS(काष्ठा amap_शेष_pdu_context_ext,
			      शेष_buffer_size, ctxt, entry_size);
		AMAP_SET_BITS(काष्ठा amap_शेष_pdu_context_ext,
			      cq_id_recv, ctxt, cq->id);
	पूर्ण

	be_dws_cpu_to_le(ctxt, माप(req->context));

	be_cmd_page_addrs_prepare(req->pages, ARRAY_SIZE(req->pages), q_mem);

	status = be_mbox_notअगरy(ctrl);
	अगर (!status) अणु
		काष्ठा be_ring *defq_ring;
		काष्ठा be_defq_create_resp *resp = embedded_payload(wrb);

		dq->id = le16_to_cpu(resp->id);
		dq->created = true;
		अगर (is_header)
			defq_ring = &phba->phwi_ctrlr->शेष_pdu_hdr[ulp_num];
		अन्यथा
			defq_ring = &phba->phwi_ctrlr->
				    शेष_pdu_data[ulp_num];

		defq_ring->id = dq->id;

		अगर (!phba->fw_config.dual_ulp_aware) अणु
			defq_ring->ulp_num = BEISCSI_ULP0;
			defq_ring->करोorbell_offset = DB_RXULP0_OFFSET;
		पूर्ण अन्यथा अणु
			defq_ring->ulp_num = resp->ulp_num;
			defq_ring->करोorbell_offset = resp->करोorbell_offset;
		पूर्ण
	पूर्ण
	mutex_unlock(&ctrl->mbox_lock);

	वापस status;
पूर्ण

/**
 * be_cmd_wrbq_create()- Create WRBQ
 * @ctrl: ptr to ctrl_info
 * @q_mem: memory details क्रम the queue
 * @wrbq: queue info
 * @pwrb_context: ptr to wrb_context
 * @ulp_num: ULP on which the WRBQ is to be created
 *
 * Create WRBQ on the passed ULP_NUM.
 *
 **/
पूर्णांक be_cmd_wrbq_create(काष्ठा be_ctrl_info *ctrl,
			काष्ठा be_dma_mem *q_mem,
			काष्ठा be_queue_info *wrbq,
			काष्ठा hwi_wrb_context *pwrb_context,
			uपूर्णांक8_t ulp_num)
अणु
	काष्ठा be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	काष्ठा be_wrbq_create_req *req = embedded_payload(wrb);
	काष्ठा be_wrbq_create_resp *resp = embedded_payload(wrb);
	काष्ठा beiscsi_hba *phba = pci_get_drvdata(ctrl->pdev);
	पूर्णांक status;

	mutex_lock(&ctrl->mbox_lock);
	स_रखो(wrb, 0, माप(*wrb));

	be_wrb_hdr_prepare(wrb, माप(*req), true, 0);

	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI,
		OPCODE_COMMON_ISCSI_WRBQ_CREATE, माप(*req));
	req->num_pages = PAGES_4K_SPANNED(q_mem->va, q_mem->size);

	अगर (phba->fw_config.dual_ulp_aware) अणु
		req->ulp_num = ulp_num;
		req->dua_feature |= (1 << BEISCSI_DUAL_ULP_AWARE_BIT);
		req->dua_feature |= (1 << BEISCSI_BIND_Q_TO_ULP_BIT);
	पूर्ण

	be_cmd_page_addrs_prepare(req->pages, ARRAY_SIZE(req->pages), q_mem);

	status = be_mbox_notअगरy(ctrl);
	अगर (!status) अणु
		wrbq->id = le16_to_cpu(resp->cid);
		wrbq->created = true;

		pwrb_context->cid = wrbq->id;
		अगर (!phba->fw_config.dual_ulp_aware) अणु
			pwrb_context->करोorbell_offset = DB_TXULP0_OFFSET;
			pwrb_context->ulp_num = BEISCSI_ULP0;
		पूर्ण अन्यथा अणु
			pwrb_context->ulp_num = resp->ulp_num;
			pwrb_context->करोorbell_offset = resp->करोorbell_offset;
		पूर्ण
	पूर्ण
	mutex_unlock(&ctrl->mbox_lock);
	वापस status;
पूर्ण

पूर्णांक be_cmd_iscsi_post_ढाँचा_hdr(काष्ठा be_ctrl_info *ctrl,
				    काष्ठा be_dma_mem *q_mem)
अणु
	काष्ठा be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	काष्ठा be_post_ढाँचा_pages_req *req = embedded_payload(wrb);
	पूर्णांक status;

	mutex_lock(&ctrl->mbox_lock);

	स_रखो(wrb, 0, माप(*wrb));
	be_wrb_hdr_prepare(wrb, माप(*req), true, 0);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_ADD_TEMPLATE_HEADER_BUFFERS,
			   माप(*req));

	req->num_pages = PAGES_4K_SPANNED(q_mem->va, q_mem->size);
	req->type = BEISCSI_TEMPLATE_HDR_TYPE_ISCSI;
	be_cmd_page_addrs_prepare(req->pages, ARRAY_SIZE(req->pages), q_mem);

	status = be_mbox_notअगरy(ctrl);
	mutex_unlock(&ctrl->mbox_lock);
	वापस status;
पूर्ण

पूर्णांक be_cmd_iscsi_हटाओ_ढाँचा_hdr(काष्ठा be_ctrl_info *ctrl)
अणु
	काष्ठा be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	काष्ठा be_हटाओ_ढाँचा_pages_req *req = embedded_payload(wrb);
	पूर्णांक status;

	mutex_lock(&ctrl->mbox_lock);

	स_रखो(wrb, 0, माप(*wrb));
	be_wrb_hdr_prepare(wrb, माप(*req), true, 0);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_REMOVE_TEMPLATE_HEADER_BUFFERS,
			   माप(*req));

	req->type = BEISCSI_TEMPLATE_HDR_TYPE_ISCSI;

	status = be_mbox_notअगरy(ctrl);
	mutex_unlock(&ctrl->mbox_lock);
	वापस status;
पूर्ण

पूर्णांक be_cmd_iscsi_post_sgl_pages(काष्ठा be_ctrl_info *ctrl,
				काष्ठा be_dma_mem *q_mem,
				u32 page_offset, u32 num_pages)
अणु
	काष्ठा be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	काष्ठा be_post_sgl_pages_req *req = embedded_payload(wrb);
	काष्ठा beiscsi_hba *phba = pci_get_drvdata(ctrl->pdev);
	पूर्णांक status;
	अचिन्हित पूर्णांक curr_pages;
	u32 पूर्णांकernal_page_offset = 0;
	u32 temp_num_pages = num_pages;

	अगर (num_pages == 0xff)
		num_pages = 1;

	mutex_lock(&ctrl->mbox_lock);
	करो अणु
		स_रखो(wrb, 0, माप(*wrb));
		be_wrb_hdr_prepare(wrb, माप(*req), true, 0);
		be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI,
				   OPCODE_COMMON_ISCSI_CFG_POST_SGL_PAGES,
				   माप(*req));
		curr_pages = BE_NUMBER_OF_FIELD(काष्ठा be_post_sgl_pages_req,
						pages);
		req->num_pages = min(num_pages, curr_pages);
		req->page_offset = page_offset;
		be_cmd_page_addrs_prepare(req->pages, req->num_pages, q_mem);
		q_mem->dma = q_mem->dma + (req->num_pages * PAGE_SIZE);
		पूर्णांकernal_page_offset += req->num_pages;
		page_offset += req->num_pages;
		num_pages -= req->num_pages;

		अगर (temp_num_pages == 0xff)
			req->num_pages = temp_num_pages;

		status = be_mbox_notअगरy(ctrl);
		अगर (status) अणु
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
				    "BC_%d : FW CMD to map iscsi frags failed.\n");

			जाओ error;
		पूर्ण
	पूर्ण जबतक (num_pages > 0);
error:
	mutex_unlock(&ctrl->mbox_lock);
	अगर (status != 0)
		beiscsi_cmd_q_destroy(ctrl, शून्य, QTYPE_SGL);
	वापस status;
पूर्ण

/**
 * be_cmd_set_vlan()- Configure VLAN paramters on the adapter
 * @phba: device priv काष्ठाure instance
 * @vlan_tag: TAG to be set
 *
 * Set the VLAN_TAG क्रम the adapter or Disable VLAN on adapter
 *
 * वापसs
 *	TAG क्रम the MBX Cmd
 * **/
पूर्णांक be_cmd_set_vlan(काष्ठा beiscsi_hba *phba,
		     uपूर्णांक16_t vlan_tag)
अणु
	अचिन्हित पूर्णांक tag;
	काष्ठा be_mcc_wrb *wrb;
	काष्ठा be_cmd_set_vlan_req *req;
	काष्ठा be_ctrl_info *ctrl = &phba->ctrl;

	अगर (mutex_lock_पूर्णांकerruptible(&ctrl->mbox_lock))
		वापस 0;
	wrb = alloc_mcc_wrb(phba, &tag);
	अगर (!wrb) अणु
		mutex_unlock(&ctrl->mbox_lock);
		वापस 0;
	पूर्ण

	req = embedded_payload(wrb);
	be_wrb_hdr_prepare(wrb, माप(*wrb), true, 0);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI,
			   OPCODE_COMMON_ISCSI_NTWK_SET_VLAN,
			   माप(*req));

	req->पूर्णांकerface_hndl = phba->पूर्णांकerface_handle;
	req->vlan_priority = vlan_tag;

	be_mcc_notअगरy(phba, tag);
	mutex_unlock(&ctrl->mbox_lock);

	वापस tag;
पूर्ण

पूर्णांक beiscsi_check_supported_fw(काष्ठा be_ctrl_info *ctrl,
			       काष्ठा beiscsi_hba *phba)
अणु
	काष्ठा be_dma_mem nonemb_cmd;
	काष्ठा be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	काष्ठा be_mgmt_controller_attributes *req;
	काष्ठा be_sge *sge = nonembedded_sgl(wrb);
	पूर्णांक status = 0;

	nonemb_cmd.va = dma_alloc_coherent(&ctrl->pdev->dev,
				माप(काष्ठा be_mgmt_controller_attributes),
				&nonemb_cmd.dma, GFP_KERNEL);
	अगर (nonemb_cmd.va == शून्य) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BG_%d : dma_alloc_coherent failed in %s\n",
			    __func__);
		वापस -ENOMEM;
	पूर्ण
	nonemb_cmd.size = माप(काष्ठा be_mgmt_controller_attributes);
	req = nonemb_cmd.va;
	स_रखो(req, 0, माप(*req));
	mutex_lock(&ctrl->mbox_lock);
	स_रखो(wrb, 0, माप(*wrb));
	be_wrb_hdr_prepare(wrb, माप(*req), false, 1);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_GET_CNTL_ATTRIBUTES, माप(*req));
	sge->pa_hi = cpu_to_le32(upper_32_bits(nonemb_cmd.dma));
	sge->pa_lo = cpu_to_le32(nonemb_cmd.dma & 0xFFFFFFFF);
	sge->len = cpu_to_le32(nonemb_cmd.size);
	status = be_mbox_notअगरy(ctrl);
	अगर (!status) अणु
		काष्ठा be_mgmt_controller_attributes_resp *resp = nonemb_cmd.va;

		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BG_%d : Firmware Version of CMD : %s\n"
			    "Firmware Version is : %s\n"
			    "Developer Build, not performing version check...\n",
			    resp->params.hba_attribs
			    .flashrom_version_string,
			    resp->params.hba_attribs.
			    firmware_version_string);

		phba->fw_config.iscsi_features =
				resp->params.hba_attribs.iscsi_features;
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BM_%d : phba->fw_config.iscsi_features = %d\n",
			    phba->fw_config.iscsi_features);
		स_नकल(phba->fw_ver_str, resp->params.hba_attribs.
		       firmware_version_string, BEISCSI_VER_STRLEN);
	पूर्ण अन्यथा
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BG_%d :  Failed in beiscsi_check_supported_fw\n");
	mutex_unlock(&ctrl->mbox_lock);
	अगर (nonemb_cmd.va)
		dma_मुक्त_coherent(&ctrl->pdev->dev, nonemb_cmd.size,
				    nonemb_cmd.va, nonemb_cmd.dma);

	वापस status;
पूर्ण

/**
 * beiscsi_get_fw_config()- Get the FW config क्रम the function
 * @ctrl: ptr to Ctrl Info
 * @phba: ptr to the dev priv काष्ठाure
 *
 * Get the FW config and resources available क्रम the function.
 * The resources are created based on the count received here.
 *
 * वापस
 *	Success: 0
 *	Failure: Non-Zero Value
 **/
पूर्णांक beiscsi_get_fw_config(काष्ठा be_ctrl_info *ctrl,
			  काष्ठा beiscsi_hba *phba)
अणु
	काष्ठा be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	काष्ठा be_fw_cfg *pfw_cfg = embedded_payload(wrb);
	uपूर्णांक32_t cid_count, icd_count;
	पूर्णांक status = -EINVAL;
	uपूर्णांक8_t ulp_num = 0;

	mutex_lock(&ctrl->mbox_lock);
	स_रखो(wrb, 0, माप(*wrb));
	be_wrb_hdr_prepare(wrb, माप(*pfw_cfg), true, 0);

	be_cmd_hdr_prepare(&pfw_cfg->hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_QUERY_FIRMWARE_CONFIG,
			   EMBED_MBX_MAX_PAYLOAD_SIZE);

	अगर (be_mbox_notअगरy(ctrl)) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BG_%d : Failed in beiscsi_get_fw_config\n");
		जाओ fail_init;
	पूर्ण

	/* FW response क्रमmats depend on port id */
	phba->fw_config.phys_port = pfw_cfg->phys_port;
	अगर (phba->fw_config.phys_port >= BEISCSI_PHYS_PORT_MAX) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BG_%d : invalid physical port id %d\n",
			    phba->fw_config.phys_port);
		जाओ fail_init;
	पूर्ण

	/* populate and check FW config against min and max values */
	अगर (!is_chip_be2_be3r(phba)) अणु
		phba->fw_config.eqid_count = pfw_cfg->eqid_count;
		phba->fw_config.cqid_count = pfw_cfg->cqid_count;
		अगर (phba->fw_config.eqid_count == 0 ||
		    phba->fw_config.eqid_count > 2048) अणु
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
				    "BG_%d : invalid EQ count %d\n",
				    phba->fw_config.eqid_count);
			जाओ fail_init;
		पूर्ण
		अगर (phba->fw_config.cqid_count == 0 ||
		    phba->fw_config.cqid_count > 4096) अणु
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
				    "BG_%d : invalid CQ count %d\n",
				    phba->fw_config.cqid_count);
			जाओ fail_init;
		पूर्ण
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BG_%d : EQ_Count : %d CQ_Count : %d\n",
			    phba->fw_config.eqid_count,
			    phba->fw_config.cqid_count);
	पूर्ण

	/**
	 * Check on which all ULP iSCSI Protocol is loaded.
	 * Set the Bit क्रम those ULP. This set flag is used
	 * at all places in the code to check on which ULP
	 * iSCSi Protocol is loaded
	 **/
	क्रम (ulp_num = 0; ulp_num < BEISCSI_ULP_COUNT; ulp_num++) अणु
		अगर (pfw_cfg->ulp[ulp_num].ulp_mode &
		    BEISCSI_ULP_ISCSI_INI_MODE) अणु
			set_bit(ulp_num, &phba->fw_config.ulp_supported);

			/* Get the CID, ICD and Chain count क्रम each ULP */
			phba->fw_config.iscsi_cid_start[ulp_num] =
				pfw_cfg->ulp[ulp_num].sq_base;
			phba->fw_config.iscsi_cid_count[ulp_num] =
				pfw_cfg->ulp[ulp_num].sq_count;

			phba->fw_config.iscsi_icd_start[ulp_num] =
				pfw_cfg->ulp[ulp_num].icd_base;
			phba->fw_config.iscsi_icd_count[ulp_num] =
				pfw_cfg->ulp[ulp_num].icd_count;

			phba->fw_config.iscsi_chain_start[ulp_num] =
				pfw_cfg->chain_icd[ulp_num].chain_base;
			phba->fw_config.iscsi_chain_count[ulp_num] =
				pfw_cfg->chain_icd[ulp_num].chain_count;

			beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
				    "BG_%d : Function loaded on ULP : %d\n"
				    "\tiscsi_cid_count : %d\n"
				    "\tiscsi_cid_start : %d\n"
				    "\t iscsi_icd_count : %d\n"
				    "\t iscsi_icd_start : %d\n",
				    ulp_num,
				    phba->fw_config.
				    iscsi_cid_count[ulp_num],
				    phba->fw_config.
				    iscsi_cid_start[ulp_num],
				    phba->fw_config.
				    iscsi_icd_count[ulp_num],
				    phba->fw_config.
				    iscsi_icd_start[ulp_num]);
		पूर्ण
	पूर्ण

	अगर (phba->fw_config.ulp_supported == 0) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BG_%d : iSCSI initiator mode not set: ULP0 %x ULP1 %x\n",
			    pfw_cfg->ulp[BEISCSI_ULP0].ulp_mode,
			    pfw_cfg->ulp[BEISCSI_ULP1].ulp_mode);
		जाओ fail_init;
	पूर्ण

	/**
	 * ICD is shared among ULPs. Use icd_count of any one loaded ULP
	 **/
	क्रम (ulp_num = 0; ulp_num < BEISCSI_ULP_COUNT; ulp_num++)
		अगर (test_bit(ulp_num, &phba->fw_config.ulp_supported))
			अवरोध;
	icd_count = phba->fw_config.iscsi_icd_count[ulp_num];
	अगर (icd_count == 0 || icd_count > 65536) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BG_%d: invalid ICD count %d\n", icd_count);
		जाओ fail_init;
	पूर्ण

	cid_count = BEISCSI_GET_CID_COUNT(phba, BEISCSI_ULP0) +
		    BEISCSI_GET_CID_COUNT(phba, BEISCSI_ULP1);
	अगर (cid_count == 0 || cid_count > 4096) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BG_%d: invalid CID count %d\n", cid_count);
		जाओ fail_init;
	पूर्ण

	/**
	 * Check FW is dual ULP aware i.e. can handle either
	 * of the protocols.
	 */
	phba->fw_config.dual_ulp_aware = (pfw_cfg->function_mode &
					  BEISCSI_FUNC_DUA_MODE);

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
		    "BG_%d : DUA Mode : 0x%x\n",
		    phba->fw_config.dual_ulp_aware);

	/* all set, जारी using this FW config */
	status = 0;
fail_init:
	mutex_unlock(&ctrl->mbox_lock);
	वापस status;
पूर्ण

/**
 * beiscsi_get_port_name()- Get port name क्रम the function
 * @ctrl: ptr to Ctrl Info
 * @phba: ptr to the dev priv काष्ठाure
 *
 * Get the alphanumeric अक्षरacter क्रम port
 *
 **/
पूर्णांक beiscsi_get_port_name(काष्ठा be_ctrl_info *ctrl, काष्ठा beiscsi_hba *phba)
अणु
	पूर्णांक ret = 0;
	काष्ठा be_mcc_wrb *wrb;
	काष्ठा be_cmd_get_port_name *ioctl;

	mutex_lock(&ctrl->mbox_lock);
	wrb = wrb_from_mbox(&ctrl->mbox_mem);
	स_रखो(wrb, 0, माप(*wrb));
	ioctl = embedded_payload(wrb);

	be_wrb_hdr_prepare(wrb, माप(*ioctl), true, 0);
	be_cmd_hdr_prepare(&ioctl->h.req_hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_GET_PORT_NAME,
			   EMBED_MBX_MAX_PAYLOAD_SIZE);
	ret = be_mbox_notअगरy(ctrl);
	phba->port_name = 0;
	अगर (!ret) अणु
		phba->port_name = ioctl->p.resp.port_names >>
				  (phba->fw_config.phys_port * 8) & 0xff;
	पूर्ण अन्यथा अणु
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BG_%d : GET_PORT_NAME ret 0x%x status 0x%x\n",
			    ret, ioctl->h.resp_hdr.status);
	पूर्ण

	अगर (phba->port_name == 0)
		phba->port_name = '?';

	mutex_unlock(&ctrl->mbox_lock);
	वापस ret;
पूर्ण

पूर्णांक beiscsi_set_host_data(काष्ठा beiscsi_hba *phba)
अणु
	काष्ठा be_ctrl_info *ctrl = &phba->ctrl;
	काष्ठा be_cmd_set_host_data *ioctl;
	काष्ठा be_mcc_wrb *wrb;
	पूर्णांक ret = 0;

	अगर (is_chip_be2_be3r(phba))
		वापस ret;

	mutex_lock(&ctrl->mbox_lock);
	wrb = wrb_from_mbox(&ctrl->mbox_mem);
	स_रखो(wrb, 0, माप(*wrb));
	ioctl = embedded_payload(wrb);

	be_wrb_hdr_prepare(wrb, माप(*ioctl), true, 0);
	be_cmd_hdr_prepare(&ioctl->h.req_hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_SET_HOST_DATA,
			   EMBED_MBX_MAX_PAYLOAD_SIZE);
	ioctl->param.req.param_id = BE_CMD_SET_HOST_PARAM_ID;
	ioctl->param.req.param_len =
		snम_लिखो((अक्षर *)ioctl->param.req.param_data,
			 माप(ioctl->param.req.param_data),
			 "Linux iSCSI v%s", BUILD_STR);
	ioctl->param.req.param_len = ALIGN(ioctl->param.req.param_len + 1, 4);
	अगर (ioctl->param.req.param_len > BE_CMD_MAX_DRV_VERSION)
		ioctl->param.req.param_len = BE_CMD_MAX_DRV_VERSION;
	ret = be_mbox_notअगरy(ctrl);
	अगर (!ret) अणु
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BG_%d : HBA set host driver version\n");
	पूर्ण अन्यथा अणु
		/**
		 * Check "MCC_STATUS_INVALID_LENGTH" क्रम SKH.
		 * Older FW versions वापस this error.
		 */
		अगर (ret == MCC_STATUS_ILLEGAL_REQUEST ||
				ret == MCC_STATUS_INVALID_LENGTH)
			__beiscsi_log(phba, KERN_INFO,
				      "BG_%d : HBA failed to set host driver version\n");
	पूर्ण

	mutex_unlock(&ctrl->mbox_lock);
	वापस ret;
पूर्ण

पूर्णांक beiscsi_set_uer_feature(काष्ठा beiscsi_hba *phba)
अणु
	काष्ठा be_ctrl_info *ctrl = &phba->ctrl;
	काष्ठा be_cmd_set_features *ioctl;
	काष्ठा be_mcc_wrb *wrb;
	पूर्णांक ret = 0;

	mutex_lock(&ctrl->mbox_lock);
	wrb = wrb_from_mbox(&ctrl->mbox_mem);
	स_रखो(wrb, 0, माप(*wrb));
	ioctl = embedded_payload(wrb);

	be_wrb_hdr_prepare(wrb, माप(*ioctl), true, 0);
	be_cmd_hdr_prepare(&ioctl->h.req_hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_SET_FEATURES,
			   EMBED_MBX_MAX_PAYLOAD_SIZE);
	ioctl->feature = BE_CMD_SET_FEATURE_UER;
	ioctl->param_len = माप(ioctl->param.req);
	ioctl->param.req.uer = BE_CMD_UER_SUPP_BIT;
	ret = be_mbox_notअगरy(ctrl);
	अगर (!ret) अणु
		phba->ue2rp = ioctl->param.resp.ue2rp;
		set_bit(BEISCSI_HBA_UER_SUPP, &phba->state);
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BG_%d : HBA error recovery supported\n");
	पूर्ण अन्यथा अणु
		/**
		 * Check "MCC_STATUS_INVALID_LENGTH" क्रम SKH.
		 * Older FW versions वापस this error.
		 */
		अगर (ret == MCC_STATUS_ILLEGAL_REQUEST ||
		    ret == MCC_STATUS_INVALID_LENGTH)
			__beiscsi_log(phba, KERN_INFO,
				      "BG_%d : HBA error recovery not supported\n");
	पूर्ण

	mutex_unlock(&ctrl->mbox_lock);
	वापस ret;
पूर्ण

अटल u32 beiscsi_get_post_stage(काष्ठा beiscsi_hba *phba)
अणु
	u32 sem;

	अगर (is_chip_be2_be3r(phba))
		sem = ioपढ़ो32(phba->csr_va + SLIPORT_SEMAPHORE_OFFSET_BEx);
	अन्यथा
		pci_पढ़ो_config_dword(phba->pcidev,
				      SLIPORT_SEMAPHORE_OFFSET_SH, &sem);
	वापस sem;
पूर्ण

पूर्णांक beiscsi_check_fw_rdy(काष्ठा beiscsi_hba *phba)
अणु
	u32 loop, post, rdy = 0;

	loop = 1000;
	जबतक (loop--) अणु
		post = beiscsi_get_post_stage(phba);
		अगर (post & POST_ERROR_BIT)
			अवरोध;
		अगर ((post & POST_STAGE_MASK) == POST_STAGE_ARMFW_RDY) अणु
			rdy = 1;
			अवरोध;
		पूर्ण
		msleep(60);
	पूर्ण

	अगर (!rdy) अणु
		__beiscsi_log(phba, KERN_ERR,
			      "BC_%d : FW not ready 0x%x\n", post);
	पूर्ण

	वापस rdy;
पूर्ण

पूर्णांक beiscsi_cmd_function_reset(काष्ठा beiscsi_hba *phba)
अणु
	काष्ठा be_ctrl_info *ctrl = &phba->ctrl;
	काष्ठा be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	काष्ठा be_post_sgl_pages_req *req;
	पूर्णांक status;

	mutex_lock(&ctrl->mbox_lock);

	req = embedded_payload(wrb);
	be_wrb_hdr_prepare(wrb, माप(*req), true, 0);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_FUNCTION_RESET, माप(*req));
	status = be_mbox_notअगरy(ctrl);

	mutex_unlock(&ctrl->mbox_lock);
	वापस status;
पूर्ण

पूर्णांक beiscsi_cmd_special_wrb(काष्ठा be_ctrl_info *ctrl, u32 load)
अणु
	काष्ठा be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	काष्ठा beiscsi_hba *phba = pci_get_drvdata(ctrl->pdev);
	u8 *endian_check;
	पूर्णांक status;

	mutex_lock(&ctrl->mbox_lock);
	स_रखो(wrb, 0, माप(*wrb));

	endian_check = (u8 *) wrb;
	अगर (load) अणु
		/* to start communicating */
		*endian_check++ = 0xFF;
		*endian_check++ = 0x12;
		*endian_check++ = 0x34;
		*endian_check++ = 0xFF;
		*endian_check++ = 0xFF;
		*endian_check++ = 0x56;
		*endian_check++ = 0x78;
		*endian_check++ = 0xFF;
	पूर्ण अन्यथा अणु
		/* to stop communicating */
		*endian_check++ = 0xFF;
		*endian_check++ = 0xAA;
		*endian_check++ = 0xBB;
		*endian_check++ = 0xFF;
		*endian_check++ = 0xFF;
		*endian_check++ = 0xCC;
		*endian_check++ = 0xDD;
		*endian_check = 0xFF;
	पूर्ण
	be_dws_cpu_to_le(wrb, माप(*wrb));

	status = be_mbox_notअगरy(ctrl);
	अगर (status)
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BC_%d : special WRB message failed\n");
	mutex_unlock(&ctrl->mbox_lock);
	वापस status;
पूर्ण

पूर्णांक beiscsi_init_sliport(काष्ठा beiscsi_hba *phba)
अणु
	पूर्णांक status;

	/* check POST stage beक्रमe talking to FW */
	status = beiscsi_check_fw_rdy(phba);
	अगर (!status)
		वापस -EIO;

	/* clear all error states after checking FW rdy */
	phba->state &= ~BEISCSI_HBA_IN_ERR;

	/* check again UER support */
	phba->state &= ~BEISCSI_HBA_UER_SUPP;

	/*
	 * SLI COMMON_FUNCTION_RESET completion is indicated by BMBX RDY bit.
	 * It should clean up any stale info in FW क्रम this fn.
	 */
	status = beiscsi_cmd_function_reset(phba);
	अगर (status) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BC_%d : SLI Function Reset failed\n");
		वापस status;
	पूर्ण

	/* indicate driver is loading */
	वापस beiscsi_cmd_special_wrb(&phba->ctrl, 1);
पूर्ण

/**
 * beiscsi_cmd_iscsi_cleanup()- Inक्रमm FW to cleanup EP data काष्ठाures.
 * @phba: poपूर्णांकer to dev priv काष्ठाure
 * @ulp: ULP number.
 *
 * वापस
 *	Success: 0
 *	Failure: Non-Zero Value
 **/
पूर्णांक beiscsi_cmd_iscsi_cleanup(काष्ठा beiscsi_hba *phba, अचिन्हित लघु ulp)
अणु
	काष्ठा be_ctrl_info *ctrl = &phba->ctrl;
	काष्ठा iscsi_cleanup_req_v1 *req_v1;
	काष्ठा iscsi_cleanup_req *req;
	u16 hdr_ring_id, data_ring_id;
	काष्ठा be_mcc_wrb *wrb;
	पूर्णांक status;

	mutex_lock(&ctrl->mbox_lock);
	wrb = wrb_from_mbox(&ctrl->mbox_mem);

	hdr_ring_id = HWI_GET_DEF_HDRQ_ID(phba, ulp);
	data_ring_id = HWI_GET_DEF_BUFQ_ID(phba, ulp);
	अगर (is_chip_be2_be3r(phba)) अणु
		req = embedded_payload(wrb);
		be_wrb_hdr_prepare(wrb, माप(*req), true, 0);
		be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI,
				   OPCODE_COMMON_ISCSI_CLEANUP, माप(*req));
		req->chute = (1 << ulp);
		/* BE2/BE3 FW creates 8-bit ring id */
		req->hdr_ring_id = hdr_ring_id;
		req->data_ring_id = data_ring_id;
	पूर्ण अन्यथा अणु
		req_v1 = embedded_payload(wrb);
		be_wrb_hdr_prepare(wrb, माप(*req_v1), true, 0);
		be_cmd_hdr_prepare(&req_v1->hdr, CMD_SUBSYSTEM_ISCSI,
				   OPCODE_COMMON_ISCSI_CLEANUP,
				   माप(*req_v1));
		req_v1->hdr.version = 1;
		req_v1->chute = (1 << ulp);
		req_v1->hdr_ring_id = cpu_to_le16(hdr_ring_id);
		req_v1->data_ring_id = cpu_to_le16(data_ring_id);
	पूर्ण

	status = be_mbox_notअगरy(ctrl);
	अगर (status)
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_INIT,
			    "BG_%d : %s failed %d\n", __func__, ulp);
	mutex_unlock(&ctrl->mbox_lock);
	वापस status;
पूर्ण

/*
 * beiscsi_detect_ue()- Detect Unrecoverable Error on adapter
 * @phba: Driver priv काष्ठाure
 *
 * Read रेजिस्टरs linked to UE and check क्रम the UE status
 **/
पूर्णांक beiscsi_detect_ue(काष्ठा beiscsi_hba *phba)
अणु
	uपूर्णांक32_t ue_mask_hi = 0, ue_mask_lo = 0;
	uपूर्णांक32_t ue_hi = 0, ue_lo = 0;
	uपूर्णांक8_t i = 0;
	पूर्णांक ret = 0;

	pci_पढ़ो_config_dword(phba->pcidev,
			      PCICFG_UE_STATUS_LOW, &ue_lo);
	pci_पढ़ो_config_dword(phba->pcidev,
			      PCICFG_UE_STATUS_MASK_LOW,
			      &ue_mask_lo);
	pci_पढ़ो_config_dword(phba->pcidev,
			      PCICFG_UE_STATUS_HIGH,
			      &ue_hi);
	pci_पढ़ो_config_dword(phba->pcidev,
			      PCICFG_UE_STATUS_MASK_HI,
			      &ue_mask_hi);

	ue_lo = (ue_lo & ~ue_mask_lo);
	ue_hi = (ue_hi & ~ue_mask_hi);


	अगर (ue_lo || ue_hi) अणु
		set_bit(BEISCSI_HBA_IN_UE, &phba->state);
		__beiscsi_log(phba, KERN_ERR,
			      "BC_%d : HBA error detected\n");
		ret = 1;
	पूर्ण

	अगर (ue_lo) अणु
		क्रम (i = 0; ue_lo; ue_lo >>= 1, i++) अणु
			अगर (ue_lo & 1)
				__beiscsi_log(phba, KERN_ERR,
					      "BC_%d : UE_LOW %s bit set\n",
					      desc_ue_status_low[i]);
		पूर्ण
	पूर्ण

	अगर (ue_hi) अणु
		क्रम (i = 0; ue_hi; ue_hi >>= 1, i++) अणु
			अगर (ue_hi & 1)
				__beiscsi_log(phba, KERN_ERR,
					      "BC_%d : UE_HIGH %s bit set\n",
					      desc_ue_status_hi[i]);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * beiscsi_detect_tpe()- Detect Transient Parity Error on adapter
 * @phba: Driver priv काष्ठाure
 *
 * Read SLIPORT SEMAPHORE रेजिस्टर to check क्रम UER
 *
 **/
पूर्णांक beiscsi_detect_tpe(काष्ठा beiscsi_hba *phba)
अणु
	u32 post, status;
	पूर्णांक ret = 0;

	post = beiscsi_get_post_stage(phba);
	status = post & POST_STAGE_MASK;
	अगर ((status & POST_ERR_RECOVERY_CODE_MASK) ==
	    POST_STAGE_RECOVERABLE_ERR) अणु
		set_bit(BEISCSI_HBA_IN_TPE, &phba->state);
		__beiscsi_log(phba, KERN_INFO,
			      "BC_%d : HBA error recoverable: 0x%x\n", post);
		ret = 1;
	पूर्ण अन्यथा अणु
		__beiscsi_log(phba, KERN_INFO,
			      "BC_%d : HBA in UE: 0x%x\n", post);
	पूर्ण

	वापस ret;
पूर्ण
