<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */

/* MSGQ module source file. */

#समावेश "bfi.h"
#समावेश "bfa_msgq.h"
#समावेश "bfa_ioc.h"

#घोषणा call_cmdq_ent_cbfn(_cmdq_ent, _status)				\
अणु									\
	bfa_msgq_cmdcbfn_t cbfn;					\
	व्योम *cbarg;							\
	cbfn = (_cmdq_ent)->cbfn;					\
	cbarg = (_cmdq_ent)->cbarg;					\
	(_cmdq_ent)->cbfn = शून्य;					\
	(_cmdq_ent)->cbarg = शून्य;					\
	अगर (cbfn) अणु							\
		cbfn(cbarg, (_status));					\
	पूर्ण								\
पूर्ण

अटल व्योम bfa_msgq_cmdq_dbell(काष्ठा bfa_msgq_cmdq *cmdq);
अटल व्योम bfa_msgq_cmdq_copy_rsp(काष्ठा bfa_msgq_cmdq *cmdq);

क्रमागत cmdq_event अणु
	CMDQ_E_START			= 1,
	CMDQ_E_STOP			= 2,
	CMDQ_E_FAIL			= 3,
	CMDQ_E_POST			= 4,
	CMDQ_E_INIT_RESP		= 5,
	CMDQ_E_DB_READY			= 6,
पूर्ण;

bfa_fsm_state_decl(cmdq, stopped, काष्ठा bfa_msgq_cmdq, क्रमागत cmdq_event);
bfa_fsm_state_decl(cmdq, init_रुको, काष्ठा bfa_msgq_cmdq, क्रमागत cmdq_event);
bfa_fsm_state_decl(cmdq, पढ़ोy, काष्ठा bfa_msgq_cmdq, क्रमागत cmdq_event);
bfa_fsm_state_decl(cmdq, dbell_रुको, काष्ठा bfa_msgq_cmdq,
			क्रमागत cmdq_event);

अटल व्योम
cmdq_sm_stopped_entry(काष्ठा bfa_msgq_cmdq *cmdq)
अणु
	काष्ठा bfa_msgq_cmd_entry *cmdq_ent;

	cmdq->producer_index = 0;
	cmdq->consumer_index = 0;
	cmdq->flags = 0;
	cmdq->token = 0;
	cmdq->offset = 0;
	cmdq->bytes_to_copy = 0;
	जबतक (!list_empty(&cmdq->pending_q)) अणु
		cmdq_ent = list_first_entry(&cmdq->pending_q,
					    काष्ठा bfa_msgq_cmd_entry, qe);
		list_del(&cmdq_ent->qe);
		call_cmdq_ent_cbfn(cmdq_ent, BFA_STATUS_FAILED);
	पूर्ण
पूर्ण

अटल व्योम
cmdq_sm_stopped(काष्ठा bfa_msgq_cmdq *cmdq, क्रमागत cmdq_event event)
अणु
	चयन (event) अणु
	हाल CMDQ_E_START:
		bfa_fsm_set_state(cmdq, cmdq_sm_init_रुको);
		अवरोध;

	हाल CMDQ_E_STOP:
	हाल CMDQ_E_FAIL:
		/* No-op */
		अवरोध;

	हाल CMDQ_E_POST:
		cmdq->flags |= BFA_MSGQ_CMDQ_F_DB_UPDATE;
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
cmdq_sm_init_रुको_entry(काष्ठा bfa_msgq_cmdq *cmdq)
अणु
	bfa_wc_करोwn(&cmdq->msgq->init_wc);
पूर्ण

अटल व्योम
cmdq_sm_init_रुको(काष्ठा bfa_msgq_cmdq *cmdq, क्रमागत cmdq_event event)
अणु
	चयन (event) अणु
	हाल CMDQ_E_STOP:
	हाल CMDQ_E_FAIL:
		bfa_fsm_set_state(cmdq, cmdq_sm_stopped);
		अवरोध;

	हाल CMDQ_E_POST:
		cmdq->flags |= BFA_MSGQ_CMDQ_F_DB_UPDATE;
		अवरोध;

	हाल CMDQ_E_INIT_RESP:
		अगर (cmdq->flags & BFA_MSGQ_CMDQ_F_DB_UPDATE) अणु
			cmdq->flags &= ~BFA_MSGQ_CMDQ_F_DB_UPDATE;
			bfa_fsm_set_state(cmdq, cmdq_sm_dbell_रुको);
		पूर्ण अन्यथा
			bfa_fsm_set_state(cmdq, cmdq_sm_पढ़ोy);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
cmdq_sm_पढ़ोy_entry(काष्ठा bfa_msgq_cmdq *cmdq)
अणु
पूर्ण

अटल व्योम
cmdq_sm_पढ़ोy(काष्ठा bfa_msgq_cmdq *cmdq, क्रमागत cmdq_event event)
अणु
	चयन (event) अणु
	हाल CMDQ_E_STOP:
	हाल CMDQ_E_FAIL:
		bfa_fsm_set_state(cmdq, cmdq_sm_stopped);
		अवरोध;

	हाल CMDQ_E_POST:
		bfa_fsm_set_state(cmdq, cmdq_sm_dbell_रुको);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
cmdq_sm_dbell_रुको_entry(काष्ठा bfa_msgq_cmdq *cmdq)
अणु
	bfa_msgq_cmdq_dbell(cmdq);
पूर्ण

अटल व्योम
cmdq_sm_dbell_रुको(काष्ठा bfa_msgq_cmdq *cmdq, क्रमागत cmdq_event event)
अणु
	चयन (event) अणु
	हाल CMDQ_E_STOP:
	हाल CMDQ_E_FAIL:
		bfa_fsm_set_state(cmdq, cmdq_sm_stopped);
		अवरोध;

	हाल CMDQ_E_POST:
		cmdq->flags |= BFA_MSGQ_CMDQ_F_DB_UPDATE;
		अवरोध;

	हाल CMDQ_E_DB_READY:
		अगर (cmdq->flags & BFA_MSGQ_CMDQ_F_DB_UPDATE) अणु
			cmdq->flags &= ~BFA_MSGQ_CMDQ_F_DB_UPDATE;
			bfa_fsm_set_state(cmdq, cmdq_sm_dbell_रुको);
		पूर्ण अन्यथा
			bfa_fsm_set_state(cmdq, cmdq_sm_पढ़ोy);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_msgq_cmdq_dbell_पढ़ोy(व्योम *arg)
अणु
	काष्ठा bfa_msgq_cmdq *cmdq = (काष्ठा bfa_msgq_cmdq *)arg;
	bfa_fsm_send_event(cmdq, CMDQ_E_DB_READY);
पूर्ण

अटल व्योम
bfa_msgq_cmdq_dbell(काष्ठा bfa_msgq_cmdq *cmdq)
अणु
	काष्ठा bfi_msgq_h2i_db *dbell =
		(काष्ठा bfi_msgq_h2i_db *)(&cmdq->dbell_mb.msg[0]);

	स_रखो(dbell, 0, माप(काष्ठा bfi_msgq_h2i_db));
	bfi_h2i_set(dbell->mh, BFI_MC_MSGQ, BFI_MSGQ_H2I_DOORBELL_PI, 0);
	dbell->mh.mtag.i2htok = 0;
	dbell->idx.cmdq_pi = htons(cmdq->producer_index);

	अगर (!bfa_nw_ioc_mbox_queue(cmdq->msgq->ioc, &cmdq->dbell_mb,
				bfa_msgq_cmdq_dbell_पढ़ोy, cmdq)) अणु
		bfa_msgq_cmdq_dbell_पढ़ोy(cmdq);
	पूर्ण
पूर्ण

अटल व्योम
__cmd_copy(काष्ठा bfa_msgq_cmdq *cmdq, काष्ठा bfa_msgq_cmd_entry *cmd)
अणु
	माप_प्रकार len = cmd->msg_size;
	पूर्णांक num_entries = 0;
	माप_प्रकार to_copy;
	u8 *src, *dst;

	src = (u8 *)cmd->msg_hdr;
	dst = (u8 *)cmdq->addr.kva;
	dst += (cmdq->producer_index * BFI_MSGQ_CMD_ENTRY_SIZE);

	जबतक (len) अणु
		to_copy = (len < BFI_MSGQ_CMD_ENTRY_SIZE) ?
				len : BFI_MSGQ_CMD_ENTRY_SIZE;
		स_नकल(dst, src, to_copy);
		len -= to_copy;
		src += BFI_MSGQ_CMD_ENTRY_SIZE;
		BFA_MSGQ_INDX_ADD(cmdq->producer_index, 1, cmdq->depth);
		dst = (u8 *)cmdq->addr.kva;
		dst += (cmdq->producer_index * BFI_MSGQ_CMD_ENTRY_SIZE);
		num_entries++;
	पूर्ण

पूर्ण

अटल व्योम
bfa_msgq_cmdq_ci_update(काष्ठा bfa_msgq_cmdq *cmdq, काष्ठा bfi_mbmsg *mb)
अणु
	काष्ठा bfi_msgq_i2h_db *dbell = (काष्ठा bfi_msgq_i2h_db *)mb;
	काष्ठा bfa_msgq_cmd_entry *cmd;
	पूर्णांक posted = 0;

	cmdq->consumer_index = ntohs(dbell->idx.cmdq_ci);

	/* Walk through pending list to see अगर the command can be posted */
	जबतक (!list_empty(&cmdq->pending_q)) अणु
		cmd = list_first_entry(&cmdq->pending_q,
				       काष्ठा bfa_msgq_cmd_entry, qe);
		अगर (ntohs(cmd->msg_hdr->num_entries) <=
			BFA_MSGQ_FREE_CNT(cmdq)) अणु
			list_del(&cmd->qe);
			__cmd_copy(cmdq, cmd);
			posted = 1;
			call_cmdq_ent_cbfn(cmd, BFA_STATUS_OK);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (posted)
		bfa_fsm_send_event(cmdq, CMDQ_E_POST);
पूर्ण

अटल व्योम
bfa_msgq_cmdq_copy_next(व्योम *arg)
अणु
	काष्ठा bfa_msgq_cmdq *cmdq = (काष्ठा bfa_msgq_cmdq *)arg;

	अगर (cmdq->bytes_to_copy)
		bfa_msgq_cmdq_copy_rsp(cmdq);
पूर्ण

अटल व्योम
bfa_msgq_cmdq_copy_req(काष्ठा bfa_msgq_cmdq *cmdq, काष्ठा bfi_mbmsg *mb)
अणु
	काष्ठा bfi_msgq_i2h_cmdq_copy_req *req =
		(काष्ठा bfi_msgq_i2h_cmdq_copy_req *)mb;

	cmdq->token = 0;
	cmdq->offset = ntohs(req->offset);
	cmdq->bytes_to_copy = ntohs(req->len);
	bfa_msgq_cmdq_copy_rsp(cmdq);
पूर्ण

अटल व्योम
bfa_msgq_cmdq_copy_rsp(काष्ठा bfa_msgq_cmdq *cmdq)
अणु
	काष्ठा bfi_msgq_h2i_cmdq_copy_rsp *rsp =
		(काष्ठा bfi_msgq_h2i_cmdq_copy_rsp *)&cmdq->copy_mb.msg[0];
	पूर्णांक copied;
	u8 *addr = (u8 *)cmdq->addr.kva;

	स_रखो(rsp, 0, माप(काष्ठा bfi_msgq_h2i_cmdq_copy_rsp));
	bfi_h2i_set(rsp->mh, BFI_MC_MSGQ, BFI_MSGQ_H2I_CMDQ_COPY_RSP, 0);
	rsp->mh.mtag.i2htok = htons(cmdq->token);
	copied = (cmdq->bytes_to_copy >= BFI_CMD_COPY_SZ) ? BFI_CMD_COPY_SZ :
		cmdq->bytes_to_copy;
	addr += cmdq->offset;
	स_नकल(rsp->data, addr, copied);

	cmdq->token++;
	cmdq->offset += copied;
	cmdq->bytes_to_copy -= copied;

	अगर (!bfa_nw_ioc_mbox_queue(cmdq->msgq->ioc, &cmdq->copy_mb,
				bfa_msgq_cmdq_copy_next, cmdq)) अणु
		bfa_msgq_cmdq_copy_next(cmdq);
	पूर्ण
पूर्ण

अटल व्योम
bfa_msgq_cmdq_attach(काष्ठा bfa_msgq_cmdq *cmdq, काष्ठा bfa_msgq *msgq)
अणु
	cmdq->depth = BFA_MSGQ_CMDQ_NUM_ENTRY;
	INIT_LIST_HEAD(&cmdq->pending_q);
	cmdq->msgq = msgq;
	bfa_fsm_set_state(cmdq, cmdq_sm_stopped);
पूर्ण

अटल व्योम bfa_msgq_rspq_dbell(काष्ठा bfa_msgq_rspq *rspq);

क्रमागत rspq_event अणु
	RSPQ_E_START			= 1,
	RSPQ_E_STOP			= 2,
	RSPQ_E_FAIL			= 3,
	RSPQ_E_RESP			= 4,
	RSPQ_E_INIT_RESP		= 5,
	RSPQ_E_DB_READY			= 6,
पूर्ण;

bfa_fsm_state_decl(rspq, stopped, काष्ठा bfa_msgq_rspq, क्रमागत rspq_event);
bfa_fsm_state_decl(rspq, init_रुको, काष्ठा bfa_msgq_rspq,
			क्रमागत rspq_event);
bfa_fsm_state_decl(rspq, पढ़ोy, काष्ठा bfa_msgq_rspq, क्रमागत rspq_event);
bfa_fsm_state_decl(rspq, dbell_रुको, काष्ठा bfa_msgq_rspq,
			क्रमागत rspq_event);

अटल व्योम
rspq_sm_stopped_entry(काष्ठा bfa_msgq_rspq *rspq)
अणु
	rspq->producer_index = 0;
	rspq->consumer_index = 0;
	rspq->flags = 0;
पूर्ण

अटल व्योम
rspq_sm_stopped(काष्ठा bfa_msgq_rspq *rspq, क्रमागत rspq_event event)
अणु
	चयन (event) अणु
	हाल RSPQ_E_START:
		bfa_fsm_set_state(rspq, rspq_sm_init_रुको);
		अवरोध;

	हाल RSPQ_E_STOP:
	हाल RSPQ_E_FAIL:
		/* No-op */
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
rspq_sm_init_रुको_entry(काष्ठा bfa_msgq_rspq *rspq)
अणु
	bfa_wc_करोwn(&rspq->msgq->init_wc);
पूर्ण

अटल व्योम
rspq_sm_init_रुको(काष्ठा bfa_msgq_rspq *rspq, क्रमागत rspq_event event)
अणु
	चयन (event) अणु
	हाल RSPQ_E_FAIL:
	हाल RSPQ_E_STOP:
		bfa_fsm_set_state(rspq, rspq_sm_stopped);
		अवरोध;

	हाल RSPQ_E_INIT_RESP:
		bfa_fsm_set_state(rspq, rspq_sm_पढ़ोy);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
rspq_sm_पढ़ोy_entry(काष्ठा bfa_msgq_rspq *rspq)
अणु
पूर्ण

अटल व्योम
rspq_sm_पढ़ोy(काष्ठा bfa_msgq_rspq *rspq, क्रमागत rspq_event event)
अणु
	चयन (event) अणु
	हाल RSPQ_E_STOP:
	हाल RSPQ_E_FAIL:
		bfa_fsm_set_state(rspq, rspq_sm_stopped);
		अवरोध;

	हाल RSPQ_E_RESP:
		bfa_fsm_set_state(rspq, rspq_sm_dbell_रुको);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
rspq_sm_dbell_रुको_entry(काष्ठा bfa_msgq_rspq *rspq)
अणु
	अगर (!bfa_nw_ioc_is_disabled(rspq->msgq->ioc))
		bfa_msgq_rspq_dbell(rspq);
पूर्ण

अटल व्योम
rspq_sm_dbell_रुको(काष्ठा bfa_msgq_rspq *rspq, क्रमागत rspq_event event)
अणु
	चयन (event) अणु
	हाल RSPQ_E_STOP:
	हाल RSPQ_E_FAIL:
		bfa_fsm_set_state(rspq, rspq_sm_stopped);
		अवरोध;

	हाल RSPQ_E_RESP:
		rspq->flags |= BFA_MSGQ_RSPQ_F_DB_UPDATE;
		अवरोध;

	हाल RSPQ_E_DB_READY:
		अगर (rspq->flags & BFA_MSGQ_RSPQ_F_DB_UPDATE) अणु
			rspq->flags &= ~BFA_MSGQ_RSPQ_F_DB_UPDATE;
			bfa_fsm_set_state(rspq, rspq_sm_dbell_रुको);
		पूर्ण अन्यथा
			bfa_fsm_set_state(rspq, rspq_sm_पढ़ोy);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_msgq_rspq_dbell_पढ़ोy(व्योम *arg)
अणु
	काष्ठा bfa_msgq_rspq *rspq = (काष्ठा bfa_msgq_rspq *)arg;
	bfa_fsm_send_event(rspq, RSPQ_E_DB_READY);
पूर्ण

अटल व्योम
bfa_msgq_rspq_dbell(काष्ठा bfa_msgq_rspq *rspq)
अणु
	काष्ठा bfi_msgq_h2i_db *dbell =
		(काष्ठा bfi_msgq_h2i_db *)(&rspq->dbell_mb.msg[0]);

	स_रखो(dbell, 0, माप(काष्ठा bfi_msgq_h2i_db));
	bfi_h2i_set(dbell->mh, BFI_MC_MSGQ, BFI_MSGQ_H2I_DOORBELL_CI, 0);
	dbell->mh.mtag.i2htok = 0;
	dbell->idx.rspq_ci = htons(rspq->consumer_index);

	अगर (!bfa_nw_ioc_mbox_queue(rspq->msgq->ioc, &rspq->dbell_mb,
				bfa_msgq_rspq_dbell_पढ़ोy, rspq)) अणु
		bfa_msgq_rspq_dbell_पढ़ोy(rspq);
	पूर्ण
पूर्ण

अटल व्योम
bfa_msgq_rspq_pi_update(काष्ठा bfa_msgq_rspq *rspq, काष्ठा bfi_mbmsg *mb)
अणु
	काष्ठा bfi_msgq_i2h_db *dbell = (काष्ठा bfi_msgq_i2h_db *)mb;
	काष्ठा bfi_msgq_mhdr *msghdr;
	पूर्णांक num_entries;
	पूर्णांक mc;
	u8 *rspq_qe;

	rspq->producer_index = ntohs(dbell->idx.rspq_pi);

	जबतक (rspq->consumer_index != rspq->producer_index) अणु
		rspq_qe = (u8 *)rspq->addr.kva;
		rspq_qe += (rspq->consumer_index * BFI_MSGQ_RSP_ENTRY_SIZE);
		msghdr = (काष्ठा bfi_msgq_mhdr *)rspq_qe;

		mc = msghdr->msg_class;
		num_entries = ntohs(msghdr->num_entries);

		अगर ((mc >= BFI_MC_MAX) || (rspq->rsphdlr[mc].cbfn == शून्य))
			अवरोध;

		(rspq->rsphdlr[mc].cbfn)(rspq->rsphdlr[mc].cbarg, msghdr);

		BFA_MSGQ_INDX_ADD(rspq->consumer_index, num_entries,
				rspq->depth);
	पूर्ण

	bfa_fsm_send_event(rspq, RSPQ_E_RESP);
पूर्ण

अटल व्योम
bfa_msgq_rspq_attach(काष्ठा bfa_msgq_rspq *rspq, काष्ठा bfa_msgq *msgq)
अणु
	rspq->depth = BFA_MSGQ_RSPQ_NUM_ENTRY;
	rspq->msgq = msgq;
	bfa_fsm_set_state(rspq, rspq_sm_stopped);
पूर्ण

अटल व्योम
bfa_msgq_init_rsp(काष्ठा bfa_msgq *msgq,
		 काष्ठा bfi_mbmsg *mb)
अणु
	bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_INIT_RESP);
	bfa_fsm_send_event(&msgq->rspq, RSPQ_E_INIT_RESP);
पूर्ण

अटल व्योम
bfa_msgq_init(व्योम *arg)
अणु
	काष्ठा bfa_msgq *msgq = (काष्ठा bfa_msgq *)arg;
	काष्ठा bfi_msgq_cfg_req *msgq_cfg =
		(काष्ठा bfi_msgq_cfg_req *)&msgq->init_mb.msg[0];

	स_रखो(msgq_cfg, 0, माप(काष्ठा bfi_msgq_cfg_req));
	bfi_h2i_set(msgq_cfg->mh, BFI_MC_MSGQ, BFI_MSGQ_H2I_INIT_REQ, 0);
	msgq_cfg->mh.mtag.i2htok = 0;

	bfa_dma_be_addr_set(msgq_cfg->cmdq.addr, msgq->cmdq.addr.pa);
	msgq_cfg->cmdq.q_depth = htons(msgq->cmdq.depth);
	bfa_dma_be_addr_set(msgq_cfg->rspq.addr, msgq->rspq.addr.pa);
	msgq_cfg->rspq.q_depth = htons(msgq->rspq.depth);

	bfa_nw_ioc_mbox_queue(msgq->ioc, &msgq->init_mb, शून्य, शून्य);
पूर्ण

अटल व्योम
bfa_msgq_isr(व्योम *cbarg, काष्ठा bfi_mbmsg *msg)
अणु
	काष्ठा bfa_msgq *msgq = (काष्ठा bfa_msgq *)cbarg;

	चयन (msg->mh.msg_id) अणु
	हाल BFI_MSGQ_I2H_INIT_RSP:
		bfa_msgq_init_rsp(msgq, msg);
		अवरोध;

	हाल BFI_MSGQ_I2H_DOORBELL_PI:
		bfa_msgq_rspq_pi_update(&msgq->rspq, msg);
		अवरोध;

	हाल BFI_MSGQ_I2H_DOORBELL_CI:
		bfa_msgq_cmdq_ci_update(&msgq->cmdq, msg);
		अवरोध;

	हाल BFI_MSGQ_I2H_CMDQ_COPY_REQ:
		bfa_msgq_cmdq_copy_req(&msgq->cmdq, msg);
		अवरोध;

	शेष:
		BUG_ON(1);
	पूर्ण
पूर्ण

अटल व्योम
bfa_msgq_notअगरy(व्योम *cbarg, क्रमागत bfa_ioc_event event)
अणु
	काष्ठा bfa_msgq *msgq = (काष्ठा bfa_msgq *)cbarg;

	चयन (event) अणु
	हाल BFA_IOC_E_ENABLED:
		bfa_wc_init(&msgq->init_wc, bfa_msgq_init, msgq);
		bfa_wc_up(&msgq->init_wc);
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_START);
		bfa_wc_up(&msgq->init_wc);
		bfa_fsm_send_event(&msgq->rspq, RSPQ_E_START);
		bfa_wc_रुको(&msgq->init_wc);
		अवरोध;

	हाल BFA_IOC_E_DISABLED:
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_STOP);
		bfa_fsm_send_event(&msgq->rspq, RSPQ_E_STOP);
		अवरोध;

	हाल BFA_IOC_E_FAILED:
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_FAIL);
		bfa_fsm_send_event(&msgq->rspq, RSPQ_E_FAIL);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

u32
bfa_msgq_meminfo(व्योम)
अणु
	वापस roundup(BFA_MSGQ_CMDQ_SIZE, BFA_DMA_ALIGN_SZ) +
		roundup(BFA_MSGQ_RSPQ_SIZE, BFA_DMA_ALIGN_SZ);
पूर्ण

व्योम
bfa_msgq_memclaim(काष्ठा bfa_msgq *msgq, u8 *kva, u64 pa)
अणु
	msgq->cmdq.addr.kva = kva;
	msgq->cmdq.addr.pa  = pa;

	kva += roundup(BFA_MSGQ_CMDQ_SIZE, BFA_DMA_ALIGN_SZ);
	pa += roundup(BFA_MSGQ_CMDQ_SIZE, BFA_DMA_ALIGN_SZ);

	msgq->rspq.addr.kva = kva;
	msgq->rspq.addr.pa = pa;
पूर्ण

व्योम
bfa_msgq_attach(काष्ठा bfa_msgq *msgq, काष्ठा bfa_ioc *ioc)
अणु
	msgq->ioc    = ioc;

	bfa_msgq_cmdq_attach(&msgq->cmdq, msgq);
	bfa_msgq_rspq_attach(&msgq->rspq, msgq);

	bfa_nw_ioc_mbox_regisr(msgq->ioc, BFI_MC_MSGQ, bfa_msgq_isr, msgq);
	bfa_ioc_notअगरy_init(&msgq->ioc_notअगरy, bfa_msgq_notअगरy, msgq);
	bfa_nw_ioc_notअगरy_रेजिस्टर(msgq->ioc, &msgq->ioc_notअगरy);
पूर्ण

व्योम
bfa_msgq_regisr(काष्ठा bfa_msgq *msgq, क्रमागत bfi_mclass mc,
		bfa_msgq_mcfunc_t cbfn, व्योम *cbarg)
अणु
	msgq->rspq.rsphdlr[mc].cbfn	= cbfn;
	msgq->rspq.rsphdlr[mc].cbarg	= cbarg;
पूर्ण

व्योम
bfa_msgq_cmd_post(काष्ठा bfa_msgq *msgq,  काष्ठा bfa_msgq_cmd_entry *cmd)
अणु
	अगर (ntohs(cmd->msg_hdr->num_entries) <=
		BFA_MSGQ_FREE_CNT(&msgq->cmdq)) अणु
		__cmd_copy(&msgq->cmdq, cmd);
		call_cmdq_ent_cbfn(cmd, BFA_STATUS_OK);
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_POST);
	पूर्ण अन्यथा अणु
		list_add_tail(&cmd->qe, &msgq->cmdq.pending_q);
	पूर्ण
पूर्ण

व्योम
bfa_msgq_rsp_copy(काष्ठा bfa_msgq *msgq, u8 *buf, माप_प्रकार buf_len)
अणु
	काष्ठा bfa_msgq_rspq *rspq = &msgq->rspq;
	माप_प्रकार len = buf_len;
	माप_प्रकार to_copy;
	पूर्णांक ci;
	u8 *src, *dst;

	ci = rspq->consumer_index;
	src = (u8 *)rspq->addr.kva;
	src += (ci * BFI_MSGQ_RSP_ENTRY_SIZE);
	dst = buf;

	जबतक (len) अणु
		to_copy = (len < BFI_MSGQ_RSP_ENTRY_SIZE) ?
				len : BFI_MSGQ_RSP_ENTRY_SIZE;
		स_नकल(dst, src, to_copy);
		len -= to_copy;
		dst += BFI_MSGQ_RSP_ENTRY_SIZE;
		BFA_MSGQ_INDX_ADD(ci, 1, rspq->depth);
		src = (u8 *)rspq->addr.kva;
		src += (ci * BFI_MSGQ_RSP_ENTRY_SIZE);
	पूर्ण
पूर्ण
