<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * IBM Virtual SCSI Target Driver
 * Copyright (C) 2003-2005 Dave Boutcher (boutcher@us.ibm.com) IBM Corp.
 *			   Santiago Leon (santil@us.ibm.com) IBM Corp.
 *			   Linda Xie (lxie@us.ibm.com) IBM Corp.
 *
 * Copyright (C) 2005-2011 FUJITA Tomonori <tomof@acm.org>
 * Copyright (C) 2010 Nicholas A. Bellinger <nab@kernel.org>
 *
 * Authors: Bryant G. Ly <bryantly@linux.vnet.ibm.com>
 * Authors: Michael Cyr <mikecyr@linux.vnet.ibm.com>
 *
 ****************************************************************************/

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>

#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/vपन.स>

#समावेश <scsi/viosrp.h>

#समावेश "ibmvscsi_tgt.h"

#घोषणा IBMVSCSIS_VERSION	"v0.2"

#घोषणा	INITIAL_SRP_LIMIT	800
#घोषणा	DEFAULT_MAX_SECTORS	256
#घोषणा MAX_TXU			1024 * 1024

अटल uपूर्णांक max_vdma_size = MAX_H_COPY_RDMA;

अटल अक्षर प्रणाली_id[SYS_ID_NAME_LEN] = "";
अटल अक्षर partition_name[PARTITION_NAMELEN] = "UNKNOWN";
अटल uपूर्णांक partition_number = -1;

/* Adapter list and lock to control it */
अटल DEFINE_SPINLOCK(ibmvscsis_dev_lock);
अटल LIST_HEAD(ibmvscsis_dev_list);

अटल दीर्घ ibmvscsis_parse_command(काष्ठा scsi_info *vscsi,
				    काष्ठा viosrp_crq *crq);

अटल व्योम ibmvscsis_adapter_idle(काष्ठा scsi_info *vscsi);

अटल व्योम ibmvscsis_determine_resid(काष्ठा se_cmd *se_cmd,
				      काष्ठा srp_rsp *rsp)
अणु
	u32 residual_count = se_cmd->residual_count;

	अगर (!residual_count)
		वापस;

	अगर (se_cmd->se_cmd_flags & SCF_UNDERFLOW_BIT) अणु
		अगर (se_cmd->data_direction == DMA_TO_DEVICE) अणु
			/* residual data from an underflow ग_लिखो */
			rsp->flags = SRP_RSP_FLAG_DOUNDER;
			rsp->data_out_res_cnt = cpu_to_be32(residual_count);
		पूर्ण अन्यथा अगर (se_cmd->data_direction == DMA_FROM_DEVICE) अणु
			/* residual data from an underflow पढ़ो */
			rsp->flags = SRP_RSP_FLAG_DIUNDER;
			rsp->data_in_res_cnt = cpu_to_be32(residual_count);
		पूर्ण
	पूर्ण अन्यथा अगर (se_cmd->se_cmd_flags & SCF_OVERFLOW_BIT) अणु
		अगर (se_cmd->data_direction == DMA_TO_DEVICE) अणु
			/* residual data from an overflow ग_लिखो */
			rsp->flags = SRP_RSP_FLAG_DOOVER;
			rsp->data_out_res_cnt = cpu_to_be32(residual_count);
		पूर्ण अन्यथा अगर (se_cmd->data_direction == DMA_FROM_DEVICE) अणु
			/* residual data from an overflow पढ़ो */
			rsp->flags = SRP_RSP_FLAG_DIOVER;
			rsp->data_in_res_cnt = cpu_to_be32(residual_count);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * connection_broken() - Determine अगर the connection to the client is good
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * This function attempts to send a ping MAD to the client. If the call to
 * queue the request वापसs H_CLOSED then the connection has been broken
 * and the function वापसs TRUE.
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt or Process environment
 */
अटल bool connection_broken(काष्ठा scsi_info *vscsi)
अणु
	काष्ठा viosrp_crq *crq;
	u64 buffer[2] = अणु 0, 0 पूर्ण;
	दीर्घ h_वापस_code;
	bool rc = false;

	/* create a PING crq */
	crq = (काष्ठा viosrp_crq *)&buffer;
	crq->valid = VALID_CMD_RESP_EL;
	crq->क्रमmat = MESSAGE_IN_CRQ;
	crq->status = PING;

	h_वापस_code = h_send_crq(vscsi->dds.unit_id,
				   cpu_to_be64(buffer[MSG_HI]),
				   cpu_to_be64(buffer[MSG_LOW]));

	dev_dbg(&vscsi->dev, "Connection_broken: rc %ld\n", h_वापस_code);

	अगर (h_वापस_code == H_CLOSED)
		rc = true;

	वापस rc;
पूर्ण

/**
 * ibmvscsis_unरेजिस्टर_command_q() - Helper Function-Unरेजिस्टर Command Queue
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * This function calls h_मुक्त_q then मुक्तs the पूर्णांकerrupt bit etc.
 * It must release the lock beक्रमe करोing so because of the समय it can take
 * क्रम h_मुक्त_crq in PHYP
 * NOTE: * the caller must make sure that state and or flags will prevent
 *	   पूर्णांकerrupt handler from scheduling work.
 *       * anyone calling this function may need to set the CRQ_CLOSED flag
 *	   we can't do it here, because we don't have the lock
 *
 * EXECUTION ENVIRONMENT:
 *	Process level
 */
अटल दीर्घ ibmvscsis_unरेजिस्टर_command_q(काष्ठा scsi_info *vscsi)
अणु
	दीर्घ qrc;
	दीर्घ rc = ADAPT_SUCCESS;
	पूर्णांक ticks = 0;

	करो अणु
		qrc = h_मुक्त_crq(vscsi->dds.unit_id);
		चयन (qrc) अणु
		हाल H_SUCCESS:
			spin_lock_bh(&vscsi->पूर्णांकr_lock);
			vscsi->flags &= ~PREP_FOR_SUSPEND_FLAGS;
			spin_unlock_bh(&vscsi->पूर्णांकr_lock);
			अवरोध;

		हाल H_HARDWARE:
		हाल H_PARAMETER:
			dev_err(&vscsi->dev, "unregister_command_q: error from h_free_crq %ld\n",
				qrc);
			rc = ERROR;
			अवरोध;

		हाल H_BUSY:
		हाल H_LONG_BUSY_ORDER_1_MSEC:
			/* msleep not good क्रम small values */
			usleep_range(1000, 2000);
			ticks += 1;
			अवरोध;
		हाल H_LONG_BUSY_ORDER_10_MSEC:
			usleep_range(10000, 20000);
			ticks += 10;
			अवरोध;
		हाल H_LONG_BUSY_ORDER_100_MSEC:
			msleep(100);
			ticks += 100;
			अवरोध;
		हाल H_LONG_BUSY_ORDER_1_SEC:
			ssleep(1);
			ticks += 1000;
			अवरोध;
		हाल H_LONG_BUSY_ORDER_10_SEC:
			ssleep(10);
			ticks += 10000;
			अवरोध;
		हाल H_LONG_BUSY_ORDER_100_SEC:
			ssleep(100);
			ticks += 100000;
			अवरोध;
		शेष:
			dev_err(&vscsi->dev, "unregister_command_q: unknown error %ld from h_free_crq\n",
				qrc);
			rc = ERROR;
			अवरोध;
		पूर्ण

		/*
		 * करोnt रुको more then 300 seconds
		 * ticks are in milliseconds more or less
		 */
		अगर (ticks > 300000 && qrc != H_SUCCESS) अणु
			rc = ERROR;
			dev_err(&vscsi->dev, "Excessive wait for h_free_crq\n");
		पूर्ण
	पूर्ण जबतक (qrc != H_SUCCESS && rc == ADAPT_SUCCESS);

	dev_dbg(&vscsi->dev, "Freeing CRQ: phyp rc %ld, rc %ld\n", qrc, rc);

	वापस rc;
पूर्ण

/**
 * ibmvscsis_delete_client_info() - Helper function to Delete Client Info
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @client_बंदd:	True अगर client बंदd its queue
 *
 * Deletes inक्रमmation specअगरic to the client when the client goes away
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt or Process
 */
अटल व्योम ibmvscsis_delete_client_info(काष्ठा scsi_info *vscsi,
					 bool client_बंदd)
अणु
	vscsi->client_cap = 0;

	/*
	 * Some things we करोn't want to clear if we're closing the queue,
	 * because some clients करोn't resend the host handshake when they
	 * get a transport event.
	 */
	अगर (client_बंदd)
		vscsi->client_data.os_type = 0;
पूर्ण

/**
 * ibmvscsis_मुक्त_command_q() - Free Command Queue
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * This function calls unरेजिस्टर_command_q, then clears पूर्णांकerrupts and
 * any pending पूर्णांकerrupt acknowledgments associated with the command q.
 * It also clears memory अगर there is no error.
 *
 * PHYP did not meet the PAPR architecture so that we must give up the
 * lock. This causes a timing hole regarding state change.  To बंद the
 * hole this routine करोes accounting on any change that occurred during
 * the समय the lock is not held.
 * NOTE: must give up and then acquire the पूर्णांकerrupt lock, the caller must
 *	 make sure that state and or flags will prevent पूर्णांकerrupt handler from
 *	 scheduling work.
 *
 * EXECUTION ENVIRONMENT:
 *	Process level, पूर्णांकerrupt lock is held
 */
अटल दीर्घ ibmvscsis_मुक्त_command_q(काष्ठा scsi_info *vscsi)
अणु
	पूर्णांक bytes;
	u32 flags_under_lock;
	u16 state_under_lock;
	दीर्घ rc = ADAPT_SUCCESS;

	अगर (!(vscsi->flags & CRQ_CLOSED)) अणु
		vio_disable_पूर्णांकerrupts(vscsi->dma_dev);

		state_under_lock = vscsi->new_state;
		flags_under_lock = vscsi->flags;
		vscsi->phyp_acr_state = 0;
		vscsi->phyp_acr_flags = 0;

		spin_unlock_bh(&vscsi->पूर्णांकr_lock);
		rc = ibmvscsis_unरेजिस्टर_command_q(vscsi);
		spin_lock_bh(&vscsi->पूर्णांकr_lock);

		अगर (state_under_lock != vscsi->new_state)
			vscsi->phyp_acr_state = vscsi->new_state;

		vscsi->phyp_acr_flags = ((~flags_under_lock) & vscsi->flags);

		अगर (rc == ADAPT_SUCCESS) अणु
			bytes = vscsi->cmd_q.size * PAGE_SIZE;
			स_रखो(vscsi->cmd_q.base_addr, 0, bytes);
			vscsi->cmd_q.index = 0;
			vscsi->flags |= CRQ_CLOSED;

			ibmvscsis_delete_client_info(vscsi, false);
		पूर्ण

		dev_dbg(&vscsi->dev, "free_command_q: flags 0x%x, state 0x%hx, acr_flags 0x%x, acr_state 0x%hx\n",
			vscsi->flags, vscsi->state, vscsi->phyp_acr_flags,
			vscsi->phyp_acr_state);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * ibmvscsis_cmd_q_dequeue() - Get valid Command element
 * @mask:	Mask to use in हाल index wraps
 * @current_index:	Current index पूर्णांकo command queue
 * @base_addr:	Poपूर्णांकer to start of command queue
 *
 * Returns a poपूर्णांकer to a valid command element or शून्य, अगर the command
 * queue is empty
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt environment, पूर्णांकerrupt lock held
 */
अटल काष्ठा viosrp_crq *ibmvscsis_cmd_q_dequeue(uपूर्णांक mask,
						  uपूर्णांक *current_index,
						  काष्ठा viosrp_crq *base_addr)
अणु
	काष्ठा viosrp_crq *ptr;

	ptr = base_addr + *current_index;

	अगर (ptr->valid) अणु
		*current_index = (*current_index + 1) & mask;
		dma_rmb();
	पूर्ण अन्यथा अणु
		ptr = शून्य;
	पूर्ण

	वापस ptr;
पूर्ण

/**
 * ibmvscsis_send_init_message() - send initialize message to the client
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @क्रमmat:	Which Init Message क्रमmat to send
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt environment पूर्णांकerrupt lock held
 */
अटल दीर्घ ibmvscsis_send_init_message(काष्ठा scsi_info *vscsi, u8 क्रमmat)
अणु
	काष्ठा viosrp_crq *crq;
	u64 buffer[2] = अणु 0, 0 पूर्ण;
	दीर्घ rc;

	crq = (काष्ठा viosrp_crq *)&buffer;
	crq->valid = VALID_INIT_MSG;
	crq->क्रमmat = क्रमmat;
	rc = h_send_crq(vscsi->dds.unit_id, cpu_to_be64(buffer[MSG_HI]),
			cpu_to_be64(buffer[MSG_LOW]));

	वापस rc;
पूर्ण

/**
 * ibmvscsis_check_init_msg() - Check init message valid
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @क्रमmat:	Poपूर्णांकer to वापस क्रमmat of Init Message, अगर any.
 *		Set to UNUSED_FORMAT अगर no Init Message in queue.
 *
 * Checks अगर an initialize message was queued by the initiatior
 * after the queue was created and beक्रमe the पूर्णांकerrupt was enabled.
 *
 * EXECUTION ENVIRONMENT:
 *	Process level only, पूर्णांकerrupt lock held
 */
अटल दीर्घ ibmvscsis_check_init_msg(काष्ठा scsi_info *vscsi, uपूर्णांक *क्रमmat)
अणु
	काष्ठा viosrp_crq *crq;
	दीर्घ rc = ADAPT_SUCCESS;

	crq = ibmvscsis_cmd_q_dequeue(vscsi->cmd_q.mask, &vscsi->cmd_q.index,
				      vscsi->cmd_q.base_addr);
	अगर (!crq) अणु
		*क्रमmat = (uपूर्णांक)UNUSED_FORMAT;
	पूर्ण अन्यथा अगर (crq->valid == VALID_INIT_MSG && crq->क्रमmat == INIT_MSG) अणु
		*क्रमmat = (uपूर्णांक)INIT_MSG;
		crq->valid = INVALIDATE_CMD_RESP_EL;
		dma_rmb();

		/*
		 * the caller has ensured no initialize message was
		 * sent after the queue was
		 * created so there should be no other message on the queue.
		 */
		crq = ibmvscsis_cmd_q_dequeue(vscsi->cmd_q.mask,
					      &vscsi->cmd_q.index,
					      vscsi->cmd_q.base_addr);
		अगर (crq) अणु
			*क्रमmat = (uपूर्णांक)(crq->क्रमmat);
			rc = ERROR;
			crq->valid = INVALIDATE_CMD_RESP_EL;
			dma_rmb();
		पूर्ण
	पूर्ण अन्यथा अणु
		*क्रमmat = (uपूर्णांक)(crq->क्रमmat);
		rc = ERROR;
		crq->valid = INVALIDATE_CMD_RESP_EL;
		dma_rmb();
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ibmvscsis_disconnect() - Helper function to disconnect
 * @work:	Poपूर्णांकer to work_काष्ठा, gives access to our adapter काष्ठाure
 *
 * An error has occurred or the driver received a Transport event,
 * and the driver is requesting that the command queue be de-रेजिस्टरed
 * in a safe manner. If there is no outstanding I/O then we can stop the
 * queue. If we are restarting the queue it will be reflected in the
 * the state of the adapter.
 *
 * EXECUTION ENVIRONMENT:
 *	Process environment
 */
अटल व्योम ibmvscsis_disconnect(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा scsi_info *vscsi = container_of(work, काष्ठा scsi_info,
					       proc_work);
	u16 new_state;
	bool रुको_idle = false;

	spin_lock_bh(&vscsi->पूर्णांकr_lock);
	new_state = vscsi->new_state;
	vscsi->new_state = 0;

	vscsi->flags |= DISCONNECT_SCHEDULED;
	vscsi->flags &= ~SCHEDULE_DISCONNECT;

	dev_dbg(&vscsi->dev, "disconnect: flags 0x%x, state 0x%hx\n",
		vscsi->flags, vscsi->state);

	/*
	 * check which state we are in and see अगर we
	 * should transitition to the new state
	 */
	चयन (vscsi->state) अणु
	/* Should never be called जबतक in this state. */
	हाल NO_QUEUE:
	/*
	 * Can never transition from this state;
	 * igonore errors and logout.
	 */
	हाल UNCONFIGURING:
		अवरोध;

	/* can transition from this state to UNCONFIGURING */
	हाल ERR_DISCONNECT:
		अगर (new_state == UNCONFIGURING)
			vscsi->state = new_state;
		अवरोध;

	/*
	 * Can transition from this state to to unconfiguring
	 * or err disconnect.
	 */
	हाल ERR_DISCONNECT_RECONNECT:
		चयन (new_state) अणु
		हाल UNCONFIGURING:
		हाल ERR_DISCONNECT:
			vscsi->state = new_state;
			अवरोध;

		हाल WAIT_IDLE:
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	/* can transition from this state to UNCONFIGURING */
	हाल ERR_DISCONNECTED:
		अगर (new_state == UNCONFIGURING)
			vscsi->state = new_state;
		अवरोध;

	हाल WAIT_ENABLED:
		चयन (new_state) अणु
		हाल UNCONFIGURING:
			vscsi->state = new_state;
			vscsi->flags |= RESPONSE_Q_DOWN;
			vscsi->flags &= ~(SCHEDULE_DISCONNECT |
					  DISCONNECT_SCHEDULED);
			dma_rmb();
			अगर (vscsi->flags & CFG_SLEEPING) अणु
				vscsi->flags &= ~CFG_SLEEPING;
				complete(&vscsi->unconfig);
			पूर्ण
			अवरोध;

		/* should never happen */
		हाल ERR_DISCONNECT:
		हाल ERR_DISCONNECT_RECONNECT:
		हाल WAIT_IDLE:
			dev_err(&vscsi->dev, "disconnect: invalid state %d for WAIT_IDLE\n",
				vscsi->state);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल WAIT_IDLE:
		चयन (new_state) अणु
		हाल UNCONFIGURING:
			vscsi->flags |= RESPONSE_Q_DOWN;
			vscsi->state = new_state;
			vscsi->flags &= ~(SCHEDULE_DISCONNECT |
					  DISCONNECT_SCHEDULED);
			ibmvscsis_मुक्त_command_q(vscsi);
			अवरोध;
		हाल ERR_DISCONNECT:
		हाल ERR_DISCONNECT_RECONNECT:
			vscsi->state = new_state;
			अवरोध;
		पूर्ण
		अवरोध;

	/*
	 * Initiator has not करोne a successful srp login
	 * or has करोne a successful srp logout ( adapter was not
	 * busy). In the first हाल there can be responses queued
	 * रुकोing क्रम space on the initiators response queue (MAD)
	 * The second हाल the adapter is idle. Assume the worse हाल,
	 * i.e. the second हाल.
	 */
	हाल WAIT_CONNECTION:
	हाल CONNECTED:
	हाल SRP_PROCESSING:
		रुको_idle = true;
		vscsi->state = new_state;
		अवरोध;

	/* can transition from this state to UNCONFIGURING */
	हाल UNDEFINED:
		अगर (new_state == UNCONFIGURING)
			vscsi->state = new_state;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (रुको_idle) अणु
		dev_dbg(&vscsi->dev, "disconnect start wait, active %d, sched %d\n",
			(पूर्णांक)list_empty(&vscsi->active_q),
			(पूर्णांक)list_empty(&vscsi->schedule_q));
		अगर (!list_empty(&vscsi->active_q) ||
		    !list_empty(&vscsi->schedule_q)) अणु
			vscsi->flags |= WAIT_FOR_IDLE;
			dev_dbg(&vscsi->dev, "disconnect flags 0x%x\n",
				vscsi->flags);
			/*
			 * This routine is can not be called with the पूर्णांकerrupt
			 * lock held.
			 */
			spin_unlock_bh(&vscsi->पूर्णांकr_lock);
			रुको_क्रम_completion(&vscsi->रुको_idle);
			spin_lock_bh(&vscsi->पूर्णांकr_lock);
		पूर्ण
		dev_dbg(&vscsi->dev, "disconnect stop wait\n");

		ibmvscsis_adapter_idle(vscsi);
	पूर्ण

	spin_unlock_bh(&vscsi->पूर्णांकr_lock);
पूर्ण

/**
 * ibmvscsis_post_disconnect() - Schedule the disconnect
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @new_state:	State to move to after disconnecting
 * @flag_bits:	Flags to turn on in adapter काष्ठाure
 *
 * If it's alपढ़ोy been scheduled, then see अगर we need to "upgrade"
 * the new state (अगर the one passed in is more "severe" than the
 * previous one).
 *
 * PRECONDITION:
 *	पूर्णांकerrupt lock is held
 */
अटल व्योम ibmvscsis_post_disconnect(काष्ठा scsi_info *vscsi, uपूर्णांक new_state,
				      uपूर्णांक flag_bits)
अणु
	uपूर्णांक state;

	/* check the validity of the new state */
	चयन (new_state) अणु
	हाल UNCONFIGURING:
	हाल ERR_DISCONNECT:
	हाल ERR_DISCONNECT_RECONNECT:
	हाल WAIT_IDLE:
		अवरोध;

	शेष:
		dev_err(&vscsi->dev, "post_disconnect: Invalid new state %d\n",
			new_state);
		वापस;
	पूर्ण

	vscsi->flags |= flag_bits;

	dev_dbg(&vscsi->dev, "post_disconnect: new_state 0x%x, flag_bits 0x%x, vscsi->flags 0x%x, state %hx\n",
		new_state, flag_bits, vscsi->flags, vscsi->state);

	अगर (!(vscsi->flags & (DISCONNECT_SCHEDULED | SCHEDULE_DISCONNECT))) अणु
		vscsi->flags |= SCHEDULE_DISCONNECT;
		vscsi->new_state = new_state;

		INIT_WORK(&vscsi->proc_work, ibmvscsis_disconnect);
		(व्योम)queue_work(vscsi->work_q, &vscsi->proc_work);
	पूर्ण अन्यथा अणु
		अगर (vscsi->new_state)
			state = vscsi->new_state;
		अन्यथा
			state = vscsi->state;

		चयन (state) अणु
		हाल NO_QUEUE:
		हाल UNCONFIGURING:
			अवरोध;

		हाल ERR_DISCONNECTED:
		हाल ERR_DISCONNECT:
		हाल UNDEFINED:
			अगर (new_state == UNCONFIGURING)
				vscsi->new_state = new_state;
			अवरोध;

		हाल ERR_DISCONNECT_RECONNECT:
			चयन (new_state) अणु
			हाल UNCONFIGURING:
			हाल ERR_DISCONNECT:
				vscsi->new_state = new_state;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;

		हाल WAIT_ENABLED:
		हाल WAIT_IDLE:
		हाल WAIT_CONNECTION:
		हाल CONNECTED:
		हाल SRP_PROCESSING:
			vscsi->new_state = new_state;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	dev_dbg(&vscsi->dev, "Leaving post_disconnect: flags 0x%x, new_state 0x%x\n",
		vscsi->flags, vscsi->new_state);
पूर्ण

/**
 * ibmvscsis_handle_init_compl_msg() - Respond to an Init Complete Message
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * Must be called with पूर्णांकerrupt lock held.
 */
अटल दीर्घ ibmvscsis_handle_init_compl_msg(काष्ठा scsi_info *vscsi)
अणु
	दीर्घ rc = ADAPT_SUCCESS;

	चयन (vscsi->state) अणु
	हाल NO_QUEUE:
	हाल ERR_DISCONNECT:
	हाल ERR_DISCONNECT_RECONNECT:
	हाल ERR_DISCONNECTED:
	हाल UNCONFIGURING:
	हाल UNDEFINED:
		rc = ERROR;
		अवरोध;

	हाल WAIT_CONNECTION:
		vscsi->state = CONNECTED;
		अवरोध;

	हाल WAIT_IDLE:
	हाल SRP_PROCESSING:
	हाल CONNECTED:
	हाल WAIT_ENABLED:
	शेष:
		rc = ERROR;
		dev_err(&vscsi->dev, "init_msg: invalid state %d to get init compl msg\n",
			vscsi->state);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ibmvscsis_handle_init_msg() - Respond to an Init Message
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * Must be called with पूर्णांकerrupt lock held.
 */
अटल दीर्घ ibmvscsis_handle_init_msg(काष्ठा scsi_info *vscsi)
अणु
	दीर्घ rc = ADAPT_SUCCESS;

	चयन (vscsi->state) अणु
	हाल WAIT_CONNECTION:
		rc = ibmvscsis_send_init_message(vscsi, INIT_COMPLETE_MSG);
		चयन (rc) अणु
		हाल H_SUCCESS:
			vscsi->state = CONNECTED;
			अवरोध;

		हाल H_PARAMETER:
			dev_err(&vscsi->dev, "init_msg: failed to send, rc %ld\n",
				rc);
			ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT, 0);
			अवरोध;

		हाल H_DROPPED:
			dev_err(&vscsi->dev, "init_msg: failed to send, rc %ld\n",
				rc);
			rc = ERROR;
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT, 0);
			अवरोध;

		हाल H_CLOSED:
			dev_warn(&vscsi->dev, "init_msg: failed to send, rc %ld\n",
				 rc);
			rc = 0;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल UNDEFINED:
		rc = ERROR;
		अवरोध;

	हाल UNCONFIGURING:
		अवरोध;

	हाल WAIT_ENABLED:
	हाल CONNECTED:
	हाल SRP_PROCESSING:
	हाल WAIT_IDLE:
	हाल NO_QUEUE:
	हाल ERR_DISCONNECT:
	हाल ERR_DISCONNECT_RECONNECT:
	हाल ERR_DISCONNECTED:
	शेष:
		rc = ERROR;
		dev_err(&vscsi->dev, "init_msg: invalid state %d to get init msg\n",
			vscsi->state);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ibmvscsis_init_msg() - Respond to an init message
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @crq:	Poपूर्णांकer to CRQ element containing the Init Message
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt, पूर्णांकerrupt lock held
 */
अटल दीर्घ ibmvscsis_init_msg(काष्ठा scsi_info *vscsi, काष्ठा viosrp_crq *crq)
अणु
	दीर्घ rc = ADAPT_SUCCESS;

	dev_dbg(&vscsi->dev, "init_msg: state 0x%hx\n", vscsi->state);

	rc = h_vioctl(vscsi->dds.unit_id, H_GET_PARTNER_INFO,
		      (u64)vscsi->map_ioba | ((u64)PAGE_SIZE << 32), 0, 0, 0,
		      0);
	अगर (rc == H_SUCCESS) अणु
		vscsi->client_data.partition_number =
			be64_to_cpu(*(u64 *)vscsi->map_buf);
		dev_dbg(&vscsi->dev, "init_msg, part num %d\n",
			vscsi->client_data.partition_number);
	पूर्ण अन्यथा अणु
		dev_dbg(&vscsi->dev, "init_msg h_vioctl rc %ld\n", rc);
		rc = ADAPT_SUCCESS;
	पूर्ण

	अगर (crq->क्रमmat == INIT_MSG) अणु
		rc = ibmvscsis_handle_init_msg(vscsi);
	पूर्ण अन्यथा अगर (crq->क्रमmat == INIT_COMPLETE_MSG) अणु
		rc = ibmvscsis_handle_init_compl_msg(vscsi);
	पूर्ण अन्यथा अणु
		rc = ERROR;
		dev_err(&vscsi->dev, "init_msg: invalid format %d\n",
			(uपूर्णांक)crq->क्रमmat);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ibmvscsis_establish_new_q() - Establish new CRQ queue
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * Must be called with पूर्णांकerrupt lock held.
 */
अटल दीर्घ ibmvscsis_establish_new_q(काष्ठा scsi_info *vscsi)
अणु
	दीर्घ rc = ADAPT_SUCCESS;
	uपूर्णांक क्रमmat;

	rc = h_vioctl(vscsi->dds.unit_id, H_ENABLE_PREPARE_FOR_SUSPEND, 30000,
		      0, 0, 0, 0);
	अगर (rc == H_SUCCESS)
		vscsi->flags |= PREP_FOR_SUSPEND_ENABLED;
	अन्यथा अगर (rc != H_NOT_FOUND)
		dev_err(&vscsi->dev, "Error from Enable Prepare for Suspend: %ld\n",
			rc);

	vscsi->flags &= PRESERVE_FLAG_FIELDS;
	vscsi->rsp_q_समयr.समयr_pops = 0;
	vscsi->debit = 0;
	vscsi->credit = 0;

	rc = vio_enable_पूर्णांकerrupts(vscsi->dma_dev);
	अगर (rc) अणु
		dev_warn(&vscsi->dev, "establish_new_q: failed to enable interrupts, rc %ld\n",
			 rc);
		वापस rc;
	पूर्ण

	rc = ibmvscsis_check_init_msg(vscsi, &क्रमmat);
	अगर (rc) अणु
		dev_err(&vscsi->dev, "establish_new_q: check_init_msg failed, rc %ld\n",
			rc);
		वापस rc;
	पूर्ण

	अगर (क्रमmat == UNUSED_FORMAT) अणु
		rc = ibmvscsis_send_init_message(vscsi, INIT_MSG);
		चयन (rc) अणु
		हाल H_SUCCESS:
		हाल H_DROPPED:
		हाल H_CLOSED:
			rc = ADAPT_SUCCESS;
			अवरोध;

		हाल H_PARAMETER:
		हाल H_HARDWARE:
			अवरोध;

		शेष:
			vscsi->state = UNDEFINED;
			rc = H_HARDWARE;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (क्रमmat == INIT_MSG) अणु
		rc = ibmvscsis_handle_init_msg(vscsi);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ibmvscsis_reset_queue() - Reset CRQ Queue
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * This function calls h_मुक्त_q and then calls h_reg_q and करोes all
 * of the bookkeeping to get us back to where we can communicate.
 *
 * Actually, we करोn't always call h_मुक्त_crq.  A problem was discovered
 * where one partition would बंद and reखोलो his queue, which would
 * cause his partner to get a transport event, which would cause him to
 * बंद and reखोलो his queue, which would cause the original partition
 * to get a transport event, etc., etc.  To prevent this, we करोn't
 * actually बंद our queue अगर the client initiated the reset, (i.e.
 * either we got a transport event or we have detected that the client's
 * queue is gone)
 *
 * EXECUTION ENVIRONMENT:
 *	Process environment, called with पूर्णांकerrupt lock held
 */
अटल व्योम ibmvscsis_reset_queue(काष्ठा scsi_info *vscsi)
अणु
	पूर्णांक bytes;
	दीर्घ rc = ADAPT_SUCCESS;

	dev_dbg(&vscsi->dev, "reset_queue: flags 0x%x\n", vscsi->flags);

	/* करोn't reset, the client did it क्रम us */
	अगर (vscsi->flags & (CLIENT_FAILED | TRANS_EVENT)) अणु
		vscsi->flags &= PRESERVE_FLAG_FIELDS;
		vscsi->rsp_q_समयr.समयr_pops = 0;
		vscsi->debit = 0;
		vscsi->credit = 0;
		vscsi->state = WAIT_CONNECTION;
		vio_enable_पूर्णांकerrupts(vscsi->dma_dev);
	पूर्ण अन्यथा अणु
		rc = ibmvscsis_मुक्त_command_q(vscsi);
		अगर (rc == ADAPT_SUCCESS) अणु
			vscsi->state = WAIT_CONNECTION;

			bytes = vscsi->cmd_q.size * PAGE_SIZE;
			rc = h_reg_crq(vscsi->dds.unit_id,
				       vscsi->cmd_q.crq_token, bytes);
			अगर (rc == H_CLOSED || rc == H_SUCCESS) अणु
				rc = ibmvscsis_establish_new_q(vscsi);
			पूर्ण

			अगर (rc != ADAPT_SUCCESS) अणु
				dev_dbg(&vscsi->dev, "reset_queue: reg_crq rc %ld\n",
					rc);

				vscsi->state = ERR_DISCONNECTED;
				vscsi->flags |= RESPONSE_Q_DOWN;
				ibmvscsis_मुक्त_command_q(vscsi);
			पूर्ण
		पूर्ण अन्यथा अणु
			vscsi->state = ERR_DISCONNECTED;
			vscsi->flags |= RESPONSE_Q_DOWN;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ibmvscsis_मुक्त_cmd_resources() - Free command resources
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @cmd:	Command which is not दीर्घer in use
 *
 * Must be called with पूर्णांकerrupt lock held.
 */
अटल व्योम ibmvscsis_मुक्त_cmd_resources(काष्ठा scsi_info *vscsi,
					 काष्ठा ibmvscsis_cmd *cmd)
अणु
	काष्ठा iu_entry *iue = cmd->iue;

	चयन (cmd->type) अणु
	हाल TASK_MANAGEMENT:
	हाल SCSI_CDB:
		/*
		 * When the queue goes करोwn this value is cleared, so it
		 * cannot be cleared in this general purpose function.
		 */
		अगर (vscsi->debit)
			vscsi->debit -= 1;
		अवरोध;
	हाल ADAPTER_MAD:
		vscsi->flags &= ~PROCESSING_MAD;
		अवरोध;
	हाल UNSET_TYPE:
		अवरोध;
	शेष:
		dev_err(&vscsi->dev, "free_cmd_resources unknown type %d\n",
			cmd->type);
		अवरोध;
	पूर्ण

	cmd->iue = शून्य;
	list_add_tail(&cmd->list, &vscsi->मुक्त_cmd);
	srp_iu_put(iue);

	अगर (list_empty(&vscsi->active_q) && list_empty(&vscsi->schedule_q) &&
	    list_empty(&vscsi->रुकोing_rsp) && (vscsi->flags & WAIT_FOR_IDLE)) अणु
		vscsi->flags &= ~WAIT_FOR_IDLE;
		complete(&vscsi->रुको_idle);
	पूर्ण
पूर्ण

/**
 * ibmvscsis_पढ़ोy_क्रम_suspend() - Helper function to call VIOCTL
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @idle:	Indicates whether we were called from adapter_idle.  This
 *		is important to know अगर we need to करो a disconnect, since अगर
 *		we're called from adapter_idle, we're still processing the
 *		current disconnect, so we can't just call post_disconnect.
 *
 * This function is called when the adapter is idle when phyp has sent
 * us a Prepare क्रम Suspend Transport Event.
 *
 * EXECUTION ENVIRONMENT:
 *	Process or पूर्णांकerrupt environment called with पूर्णांकerrupt lock held
 */
अटल दीर्घ ibmvscsis_पढ़ोy_क्रम_suspend(काष्ठा scsi_info *vscsi, bool idle)
अणु
	दीर्घ rc = 0;
	काष्ठा viosrp_crq *crq;

	/* See अगर there is a Resume event in the queue */
	crq = vscsi->cmd_q.base_addr + vscsi->cmd_q.index;

	dev_dbg(&vscsi->dev, "ready_suspend: flags 0x%x, state 0x%hx crq_valid:%x\n",
		vscsi->flags, vscsi->state, (पूर्णांक)crq->valid);

	अगर (!(vscsi->flags & PREP_FOR_SUSPEND_ABORTED) && !(crq->valid)) अणु
		rc = h_vioctl(vscsi->dds.unit_id, H_READY_FOR_SUSPEND, 0, 0, 0,
			      0, 0);
		अगर (rc) अणु
			dev_err(&vscsi->dev, "Ready for Suspend Vioctl failed: %ld\n",
				rc);
			rc = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (((vscsi->flags & PREP_FOR_SUSPEND_OVERWRITE) &&
		    (vscsi->flags & PREP_FOR_SUSPEND_ABORTED)) ||
		   ((crq->valid) && ((crq->valid != VALID_TRANS_EVENT) ||
				     (crq->क्रमmat != RESUME_FROM_SUSP)))) अणु
		अगर (idle) अणु
			vscsi->state = ERR_DISCONNECT_RECONNECT;
			ibmvscsis_reset_queue(vscsi);
			rc = -1;
		पूर्ण अन्यथा अगर (vscsi->state == CONNECTED) अणु
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT, 0);
		पूर्ण

		vscsi->flags &= ~PREP_FOR_SUSPEND_OVERWRITE;

		अगर ((crq->valid) && ((crq->valid != VALID_TRANS_EVENT) ||
				     (crq->क्रमmat != RESUME_FROM_SUSP)))
			dev_err(&vscsi->dev, "Invalid element in CRQ after Prepare for Suspend");
	पूर्ण

	vscsi->flags &= ~(PREP_FOR_SUSPEND_PENDING | PREP_FOR_SUSPEND_ABORTED);

	वापस rc;
पूर्ण

/**
 * ibmvscsis_trans_event() - Handle a Transport Event
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @crq:	Poपूर्णांकer to CRQ entry containing the Transport Event
 *
 * Do the logic to बंद the I_T nexus.  This function may not
 * behave to specअगरication.
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt, पूर्णांकerrupt lock held
 */
अटल दीर्घ ibmvscsis_trans_event(काष्ठा scsi_info *vscsi,
				  काष्ठा viosrp_crq *crq)
अणु
	दीर्घ rc = ADAPT_SUCCESS;

	dev_dbg(&vscsi->dev, "trans_event: format %d, flags 0x%x, state 0x%hx\n",
		(पूर्णांक)crq->क्रमmat, vscsi->flags, vscsi->state);

	चयन (crq->क्रमmat) अणु
	हाल MIGRATED:
	हाल PARTNER_FAILED:
	हाल PARTNER_DEREGISTER:
		ibmvscsis_delete_client_info(vscsi, true);
		अगर (crq->क्रमmat == MIGRATED)
			vscsi->flags &= ~PREP_FOR_SUSPEND_OVERWRITE;
		चयन (vscsi->state) अणु
		हाल NO_QUEUE:
		हाल ERR_DISCONNECTED:
		हाल UNDEFINED:
			अवरोध;

		हाल UNCONFIGURING:
			vscsi->flags |= (RESPONSE_Q_DOWN | TRANS_EVENT);
			अवरोध;

		हाल WAIT_ENABLED:
			अवरोध;

		हाल WAIT_CONNECTION:
			अवरोध;

		हाल CONNECTED:
			ibmvscsis_post_disconnect(vscsi, WAIT_IDLE,
						  (RESPONSE_Q_DOWN |
						   TRANS_EVENT));
			अवरोध;

		हाल SRP_PROCESSING:
			अगर ((vscsi->debit > 0) ||
			    !list_empty(&vscsi->schedule_q) ||
			    !list_empty(&vscsi->रुकोing_rsp) ||
			    !list_empty(&vscsi->active_q)) अणु
				dev_dbg(&vscsi->dev, "debit %d, sched %d, wait %d, active %d\n",
					vscsi->debit,
					(पूर्णांक)list_empty(&vscsi->schedule_q),
					(पूर्णांक)list_empty(&vscsi->रुकोing_rsp),
					(पूर्णांक)list_empty(&vscsi->active_q));
				dev_warn(&vscsi->dev, "connection lost with outstanding work\n");
			पूर्ण अन्यथा अणु
				dev_dbg(&vscsi->dev, "trans_event: SRP Processing, but no outstanding work\n");
			पूर्ण

			ibmvscsis_post_disconnect(vscsi, WAIT_IDLE,
						  (RESPONSE_Q_DOWN |
						   TRANS_EVENT));
			अवरोध;

		हाल ERR_DISCONNECT:
		हाल ERR_DISCONNECT_RECONNECT:
		हाल WAIT_IDLE:
			vscsi->flags |= (RESPONSE_Q_DOWN | TRANS_EVENT);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल PREPARE_FOR_SUSPEND:
		dev_dbg(&vscsi->dev, "Prep for Suspend, crq status = 0x%x\n",
			(पूर्णांक)crq->status);
		चयन (vscsi->state) अणु
		हाल ERR_DISCONNECTED:
		हाल WAIT_CONNECTION:
		हाल CONNECTED:
			ibmvscsis_पढ़ोy_क्रम_suspend(vscsi, false);
			अवरोध;
		हाल SRP_PROCESSING:
			vscsi->resume_state = vscsi->state;
			vscsi->flags |= PREP_FOR_SUSPEND_PENDING;
			अगर (crq->status == CRQ_ENTRY_OVERWRITTEN)
				vscsi->flags |= PREP_FOR_SUSPEND_OVERWRITE;
			ibmvscsis_post_disconnect(vscsi, WAIT_IDLE, 0);
			अवरोध;
		हाल NO_QUEUE:
		हाल UNDEFINED:
		हाल UNCONFIGURING:
		हाल WAIT_ENABLED:
		हाल ERR_DISCONNECT:
		हाल ERR_DISCONNECT_RECONNECT:
		हाल WAIT_IDLE:
			dev_err(&vscsi->dev, "Invalid state for Prepare for Suspend Trans Event: 0x%x\n",
				vscsi->state);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल RESUME_FROM_SUSP:
		dev_dbg(&vscsi->dev, "Resume from Suspend, crq status = 0x%x\n",
			(पूर्णांक)crq->status);
		अगर (vscsi->flags & PREP_FOR_SUSPEND_PENDING) अणु
			vscsi->flags |= PREP_FOR_SUSPEND_ABORTED;
		पूर्ण अन्यथा अणु
			अगर ((crq->status == CRQ_ENTRY_OVERWRITTEN) ||
			    (vscsi->flags & PREP_FOR_SUSPEND_OVERWRITE)) अणु
				ibmvscsis_post_disconnect(vscsi,
							  ERR_DISCONNECT_RECONNECT,
							  0);
				vscsi->flags &= ~PREP_FOR_SUSPEND_OVERWRITE;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		rc = ERROR;
		dev_err(&vscsi->dev, "trans_event: invalid format %d\n",
			(uपूर्णांक)crq->क्रमmat);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT,
					  RESPONSE_Q_DOWN);
		अवरोध;
	पूर्ण

	rc = vscsi->flags & SCHEDULE_DISCONNECT;

	dev_dbg(&vscsi->dev, "Leaving trans_event: flags 0x%x, state 0x%hx, rc %ld\n",
		vscsi->flags, vscsi->state, rc);

	वापस rc;
पूर्ण

/**
 * ibmvscsis_poll_cmd_q() - Poll Command Queue
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * Called to handle command elements that may have arrived जबतक
 * पूर्णांकerrupts were disabled.
 *
 * EXECUTION ENVIRONMENT:
 *	पूर्णांकr_lock must be held
 */
अटल व्योम ibmvscsis_poll_cmd_q(काष्ठा scsi_info *vscsi)
अणु
	काष्ठा viosrp_crq *crq;
	दीर्घ rc;
	bool ack = true;
	अस्थिर u8 valid;

	dev_dbg(&vscsi->dev, "poll_cmd_q: flags 0x%x, state 0x%hx, q index %ud\n",
		vscsi->flags, vscsi->state, vscsi->cmd_q.index);

	rc = vscsi->flags & SCHEDULE_DISCONNECT;
	crq = vscsi->cmd_q.base_addr + vscsi->cmd_q.index;
	valid = crq->valid;
	dma_rmb();

	जबतक (valid) अणु
poll_work:
		vscsi->cmd_q.index =
			(vscsi->cmd_q.index + 1) & vscsi->cmd_q.mask;

		अगर (!rc) अणु
			rc = ibmvscsis_parse_command(vscsi, crq);
		पूर्ण अन्यथा अणु
			अगर ((uपूर्णांक)crq->valid == VALID_TRANS_EVENT) अणु
				/*
				 * must service the transport layer events even
				 * in an error state, करोnt अवरोध out until all
				 * the consecutive transport events have been
				 * processed
				 */
				rc = ibmvscsis_trans_event(vscsi, crq);
			पूर्ण अन्यथा अगर (vscsi->flags & TRANS_EVENT) अणु
				/*
				 * अगर a tranport event has occurred leave
				 * everything but transport events on the queue
				 */
				dev_dbg(&vscsi->dev, "poll_cmd_q, ignoring\n");

				/*
				 * need to decrement the queue index so we can
				 * look at the elment again
				 */
				अगर (vscsi->cmd_q.index)
					vscsi->cmd_q.index -= 1;
				अन्यथा
					/*
					 * index is at 0 it just wrapped.
					 * have it index last element in q
					 */
					vscsi->cmd_q.index = vscsi->cmd_q.mask;
				अवरोध;
			पूर्ण
		पूर्ण

		crq->valid = INVALIDATE_CMD_RESP_EL;

		crq = vscsi->cmd_q.base_addr + vscsi->cmd_q.index;
		valid = crq->valid;
		dma_rmb();
	पूर्ण

	अगर (!rc) अणु
		अगर (ack) अणु
			vio_enable_पूर्णांकerrupts(vscsi->dma_dev);
			ack = false;
			dev_dbg(&vscsi->dev, "poll_cmd_q, reenabling interrupts\n");
		पूर्ण
		valid = crq->valid;
		dma_rmb();
		अगर (valid)
			जाओ poll_work;
	पूर्ण

	dev_dbg(&vscsi->dev, "Leaving poll_cmd_q: rc %ld\n", rc);
पूर्ण

/**
 * ibmvscsis_मुक्त_cmd_qs() - Free elements in queue
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * Free all of the elements on all queues that are रुकोing क्रम
 * whatever reason.
 *
 * PRECONDITION:
 *	Called with पूर्णांकerrupt lock held
 */
अटल व्योम ibmvscsis_मुक्त_cmd_qs(काष्ठा scsi_info *vscsi)
अणु
	काष्ठा ibmvscsis_cmd *cmd, *nxt;

	dev_dbg(&vscsi->dev, "free_cmd_qs: waiting_rsp empty %d, timer starter %d\n",
		(पूर्णांक)list_empty(&vscsi->रुकोing_rsp),
		vscsi->rsp_q_समयr.started);

	list_क्रम_each_entry_safe(cmd, nxt, &vscsi->रुकोing_rsp, list) अणु
		list_del(&cmd->list);
		ibmvscsis_मुक्त_cmd_resources(vscsi, cmd);
	पूर्ण
पूर्ण

/**
 * ibmvscsis_get_मुक्त_cmd() - Get मुक्त command from list
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * Must be called with पूर्णांकerrupt lock held.
 */
अटल काष्ठा ibmvscsis_cmd *ibmvscsis_get_मुक्त_cmd(काष्ठा scsi_info *vscsi)
अणु
	काष्ठा ibmvscsis_cmd *cmd = शून्य;
	काष्ठा iu_entry *iue;

	iue = srp_iu_get(&vscsi->target);
	अगर (iue) अणु
		cmd = list_first_entry_or_null(&vscsi->मुक्त_cmd,
					       काष्ठा ibmvscsis_cmd, list);
		अगर (cmd) अणु
			अगर (cmd->पात_cmd)
				cmd->पात_cmd = शून्य;
			cmd->flags &= ~(DELAY_SEND);
			list_del(&cmd->list);
			cmd->iue = iue;
			cmd->type = UNSET_TYPE;
			स_रखो(&cmd->se_cmd, 0, माप(cmd->se_cmd));
		पूर्ण अन्यथा अणु
			srp_iu_put(iue);
		पूर्ण
	पूर्ण

	वापस cmd;
पूर्ण

/**
 * ibmvscsis_adapter_idle() - Helper function to handle idle adapter
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * This function is called when the adapter is idle when the driver
 * is attempting to clear an error condition.
 * The adapter is considered busy अगर any of its cmd queues
 * are non-empty. This function can be invoked
 * from the off level disconnect function.
 *
 * EXECUTION ENVIRONMENT:
 *	Process environment called with पूर्णांकerrupt lock held
 */
अटल व्योम ibmvscsis_adapter_idle(काष्ठा scsi_info *vscsi)
अणु
	पूर्णांक मुक्त_qs = false;
	दीर्घ rc = 0;

	dev_dbg(&vscsi->dev, "adapter_idle: flags 0x%x, state 0x%hx\n",
		vscsi->flags, vscsi->state);

	/* Only need to मुक्त qs अगर we're disconnecting from client */
	अगर (vscsi->state != WAIT_CONNECTION || vscsi->flags & TRANS_EVENT)
		मुक्त_qs = true;

	चयन (vscsi->state) अणु
	हाल UNCONFIGURING:
		ibmvscsis_मुक्त_command_q(vscsi);
		dma_rmb();
		isync();
		अगर (vscsi->flags & CFG_SLEEPING) अणु
			vscsi->flags &= ~CFG_SLEEPING;
			complete(&vscsi->unconfig);
		पूर्ण
		अवरोध;
	हाल ERR_DISCONNECT_RECONNECT:
		ibmvscsis_reset_queue(vscsi);
		dev_dbg(&vscsi->dev, "adapter_idle, disc_rec: flags 0x%x\n",
			vscsi->flags);
		अवरोध;

	हाल ERR_DISCONNECT:
		ibmvscsis_मुक्त_command_q(vscsi);
		vscsi->flags &= ~(SCHEDULE_DISCONNECT | DISCONNECT_SCHEDULED);
		vscsi->flags |= RESPONSE_Q_DOWN;
		अगर (vscsi->tport.enabled)
			vscsi->state = ERR_DISCONNECTED;
		अन्यथा
			vscsi->state = WAIT_ENABLED;
		dev_dbg(&vscsi->dev, "adapter_idle, disc: flags 0x%x, state 0x%hx\n",
			vscsi->flags, vscsi->state);
		अवरोध;

	हाल WAIT_IDLE:
		vscsi->rsp_q_समयr.समयr_pops = 0;
		vscsi->debit = 0;
		vscsi->credit = 0;
		अगर (vscsi->flags & PREP_FOR_SUSPEND_PENDING) अणु
			vscsi->state = vscsi->resume_state;
			vscsi->resume_state = 0;
			rc = ibmvscsis_पढ़ोy_क्रम_suspend(vscsi, true);
			vscsi->flags &= ~DISCONNECT_SCHEDULED;
			अगर (rc)
				अवरोध;
		पूर्ण अन्यथा अगर (vscsi->flags & TRANS_EVENT) अणु
			vscsi->state = WAIT_CONNECTION;
			vscsi->flags &= PRESERVE_FLAG_FIELDS;
		पूर्ण अन्यथा अणु
			vscsi->state = CONNECTED;
			vscsi->flags &= ~DISCONNECT_SCHEDULED;
		पूर्ण

		dev_dbg(&vscsi->dev, "adapter_idle, wait: flags 0x%x, state 0x%hx\n",
			vscsi->flags, vscsi->state);
		ibmvscsis_poll_cmd_q(vscsi);
		अवरोध;

	हाल ERR_DISCONNECTED:
		vscsi->flags &= ~DISCONNECT_SCHEDULED;
		dev_dbg(&vscsi->dev, "adapter_idle, disconnected: flags 0x%x, state 0x%hx\n",
			vscsi->flags, vscsi->state);
		अवरोध;

	शेष:
		dev_err(&vscsi->dev, "adapter_idle: in invalid state %d\n",
			vscsi->state);
		अवरोध;
	पूर्ण

	अगर (मुक्त_qs)
		ibmvscsis_मुक्त_cmd_qs(vscsi);

	/*
	 * There is a timing winकरोw where we could lose a disconnect request.
	 * The known path to this winकरोw occurs during the DISCONNECT_RECONNECT
	 * हाल above: reset_queue calls मुक्त_command_q, which will release the
	 * पूर्णांकerrupt lock.  During that समय, a new post_disconnect call can be
	 * made with a "more severe" state (DISCONNECT or UNCONFIGURING).
	 * Because the DISCONNECT_SCHEDULED flag is alपढ़ोy set, post_disconnect
	 * will only set the new_state.  Now मुक्त_command_q reacquires the पूर्णांकr
	 * lock and clears the DISCONNECT_SCHEDULED flag (using PRESERVE_FLAG_
	 * FIELDS), and the disconnect is lost.  This is particularly bad when
	 * the new disconnect was क्रम UNCONFIGURING, since the unconfigure hangs
	 * क्रमever.
	 * Fix is that मुक्त command queue sets acr state and acr flags अगर there
	 * is a change under the lock
	 * note मुक्त command queue ग_लिखोs to this state it clears it
	 * beक्रमe releasing the lock, dअगरferent drivers call the मुक्त command
	 * queue dअगरferent बार so करोnt initialize above
	 */
	अगर (vscsi->phyp_acr_state != 0)	अणु
		/*
		 * set any bits in flags that may have been cleared by
		 * a call to मुक्त command queue in चयन statement
		 * or reset queue
		 */
		vscsi->flags |= vscsi->phyp_acr_flags;
		ibmvscsis_post_disconnect(vscsi, vscsi->phyp_acr_state, 0);
		vscsi->phyp_acr_state = 0;
		vscsi->phyp_acr_flags = 0;

		dev_dbg(&vscsi->dev, "adapter_idle: flags 0x%x, state 0x%hx, acr_flags 0x%x, acr_state 0x%hx\n",
			vscsi->flags, vscsi->state, vscsi->phyp_acr_flags,
			vscsi->phyp_acr_state);
	पूर्ण

	dev_dbg(&vscsi->dev, "Leaving adapter_idle: flags 0x%x, state 0x%hx, new_state 0x%x\n",
		vscsi->flags, vscsi->state, vscsi->new_state);
पूर्ण

/**
 * ibmvscsis_copy_crq_packet() - Copy CRQ Packet
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @cmd:	Poपूर्णांकer to command element to use to process the request
 * @crq:	Poपूर्णांकer to CRQ entry containing the request
 *
 * Copy the srp inक्रमmation unit from the hosted
 * partition using remote dma
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt, पूर्णांकerrupt lock held
 */
अटल दीर्घ ibmvscsis_copy_crq_packet(काष्ठा scsi_info *vscsi,
				      काष्ठा ibmvscsis_cmd *cmd,
				      काष्ठा viosrp_crq *crq)
अणु
	काष्ठा iu_entry *iue = cmd->iue;
	दीर्घ rc = 0;
	u16 len;

	len = be16_to_cpu(crq->IU_length);
	अगर ((len > SRP_MAX_IU_LEN) || (len == 0)) अणु
		dev_err(&vscsi->dev, "copy_crq: Invalid len %d passed", len);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		वापस SRP_VIOLATION;
	पूर्ण

	rc = h_copy_rdma(len, vscsi->dds.winकरोw[REMOTE].liobn,
			 be64_to_cpu(crq->IU_data_ptr),
			 vscsi->dds.winकरोw[LOCAL].liobn, iue->sbuf->dma);

	चयन (rc) अणु
	हाल H_SUCCESS:
		cmd->init_समय = mftb();
		iue->remote_token = crq->IU_data_ptr;
		iue->iu_len = len;
		dev_dbg(&vscsi->dev, "copy_crq: ioba 0x%llx, init_time 0x%llx\n",
			be64_to_cpu(crq->IU_data_ptr), cmd->init_समय);
		अवरोध;
	हाल H_PERMISSION:
		अगर (connection_broken(vscsi))
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT,
						  (RESPONSE_Q_DOWN |
						   CLIENT_FAILED));
		अन्यथा
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT, 0);

		dev_err(&vscsi->dev, "copy_crq: h_copy_rdma failed, rc %ld\n",
			rc);
		अवरोध;
	हाल H_DEST_PARM:
	हाल H_SOURCE_PARM:
	शेष:
		dev_err(&vscsi->dev, "copy_crq: h_copy_rdma failed, rc %ld\n",
			rc);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ibmvscsis_adapter_info - Service an Adapter Info MAnagement Data gram
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @iue:	Inक्रमmation Unit containing the Adapter Info MAD request
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt adapter lock is held
 */
अटल दीर्घ ibmvscsis_adapter_info(काष्ठा scsi_info *vscsi,
				   काष्ठा iu_entry *iue)
अणु
	काष्ठा viosrp_adapter_info *mad = &vio_iu(iue)->mad.adapter_info;
	काष्ठा mad_adapter_info_data *info;
	uपूर्णांक flag_bits = 0;
	dma_addr_t token;
	दीर्घ rc;

	mad->common.status = cpu_to_be16(VIOSRP_MAD_SUCCESS);

	अगर (be16_to_cpu(mad->common.length) > माप(*info)) अणु
		mad->common.status = cpu_to_be16(VIOSRP_MAD_FAILED);
		वापस 0;
	पूर्ण

	info = dma_alloc_coherent(&vscsi->dma_dev->dev, माप(*info), &token,
				  GFP_ATOMIC);
	अगर (!info) अणु
		dev_err(&vscsi->dev, "bad dma_alloc_coherent %p\n",
			iue->target);
		mad->common.status = cpu_to_be16(VIOSRP_MAD_FAILED);
		वापस 0;
	पूर्ण

	/* Get remote info */
	rc = h_copy_rdma(be16_to_cpu(mad->common.length),
			 vscsi->dds.winकरोw[REMOTE].liobn,
			 be64_to_cpu(mad->buffer),
			 vscsi->dds.winकरोw[LOCAL].liobn, token);

	अगर (rc != H_SUCCESS) अणु
		अगर (rc == H_PERMISSION) अणु
			अगर (connection_broken(vscsi))
				flag_bits = (RESPONSE_Q_DOWN | CLIENT_FAILED);
		पूर्ण
		dev_warn(&vscsi->dev, "adapter_info: h_copy_rdma from client failed, rc %ld\n",
			 rc);
		dev_dbg(&vscsi->dev, "adapter_info: ioba 0x%llx, flags 0x%x, flag_bits 0x%x\n",
			be64_to_cpu(mad->buffer), vscsi->flags, flag_bits);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT,
					  flag_bits);
		जाओ मुक्त_dma;
	पूर्ण

	/*
	 * Copy client info, but ignore partition number, which we
	 * alपढ़ोy got from phyp - unless we failed to get it from
	 * phyp (e.g. अगर we're running on a p5 प्रणाली).
	 */
	अगर (vscsi->client_data.partition_number == 0)
		vscsi->client_data.partition_number =
			be32_to_cpu(info->partition_number);
	म_नकलन(vscsi->client_data.srp_version, info->srp_version,
		माप(vscsi->client_data.srp_version));
	म_नकलन(vscsi->client_data.partition_name, info->partition_name,
		माप(vscsi->client_data.partition_name));
	vscsi->client_data.mad_version = be32_to_cpu(info->mad_version);
	vscsi->client_data.os_type = be32_to_cpu(info->os_type);

	/* Copy our info */
	म_नकलन(info->srp_version, SRP_VERSION,
		माप(info->srp_version));
	म_नकलन(info->partition_name, vscsi->dds.partition_name,
		माप(info->partition_name));
	info->partition_number = cpu_to_be32(vscsi->dds.partition_num);
	info->mad_version = cpu_to_be32(MAD_VERSION_1);
	info->os_type = cpu_to_be32(LINUX);
	स_रखो(&info->port_max_txu[0], 0, माप(info->port_max_txu));
	info->port_max_txu[0] = cpu_to_be32(MAX_TXU);

	dma_wmb();
	rc = h_copy_rdma(माप(*info), vscsi->dds.winकरोw[LOCAL].liobn,
			 token, vscsi->dds.winकरोw[REMOTE].liobn,
			 be64_to_cpu(mad->buffer));
	चयन (rc) अणु
	हाल H_SUCCESS:
		अवरोध;

	हाल H_SOURCE_PARM:
	हाल H_DEST_PARM:
	हाल H_PERMISSION:
		अगर (connection_broken(vscsi))
			flag_bits = (RESPONSE_Q_DOWN | CLIENT_FAILED);
		fallthrough;
	शेष:
		dev_err(&vscsi->dev, "adapter_info: h_copy_rdma to client failed, rc %ld\n",
			rc);
		ibmvscsis_post_disconnect(vscsi,
					  ERR_DISCONNECT_RECONNECT,
					  flag_bits);
		अवरोध;
	पूर्ण

मुक्त_dma:
	dma_मुक्त_coherent(&vscsi->dma_dev->dev, माप(*info), info, token);
	dev_dbg(&vscsi->dev, "Leaving adapter_info, rc %ld\n", rc);

	वापस rc;
पूर्ण

/**
 * ibmvscsis_cap_mad() - Service a Capabilities MAnagement Data gram
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @iue:	Inक्रमmation Unit containing the Capabilities MAD request
 *
 * NOTE: अगर you वापस an error from this routine you must be
 * disconnecting or you will cause a hang
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt called with adapter lock held
 */
अटल पूर्णांक ibmvscsis_cap_mad(काष्ठा scsi_info *vscsi, काष्ठा iu_entry *iue)
अणु
	काष्ठा viosrp_capabilities *mad = &vio_iu(iue)->mad.capabilities;
	काष्ठा capabilities *cap;
	काष्ठा mad_capability_common *common;
	dma_addr_t token;
	u16 olen, len, status, min_len, cap_len;
	u32 flag;
	uपूर्णांक flag_bits = 0;
	दीर्घ rc = 0;

	olen = be16_to_cpu(mad->common.length);
	/*
	 * काष्ठा capabilities hardcodes a couple capabilities after the
	 * header, but the capabilities can actually be in any order.
	 */
	min_len = दुरत्व(काष्ठा capabilities, migration);
	अगर ((olen < min_len) || (olen > PAGE_SIZE)) अणु
		dev_warn(&vscsi->dev, "cap_mad: invalid len %d\n", olen);
		mad->common.status = cpu_to_be16(VIOSRP_MAD_FAILED);
		वापस 0;
	पूर्ण

	cap = dma_alloc_coherent(&vscsi->dma_dev->dev, olen, &token,
				 GFP_ATOMIC);
	अगर (!cap) अणु
		dev_err(&vscsi->dev, "bad dma_alloc_coherent %p\n",
			iue->target);
		mad->common.status = cpu_to_be16(VIOSRP_MAD_FAILED);
		वापस 0;
	पूर्ण
	rc = h_copy_rdma(olen, vscsi->dds.winकरोw[REMOTE].liobn,
			 be64_to_cpu(mad->buffer),
			 vscsi->dds.winकरोw[LOCAL].liobn, token);
	अगर (rc == H_SUCCESS) अणु
		म_नकलन(cap->name, dev_name(&vscsi->dma_dev->dev),
			SRP_MAX_LOC_LEN);

		len = olen - min_len;
		status = VIOSRP_MAD_SUCCESS;
		common = (काष्ठा mad_capability_common *)&cap->migration;

		जबतक ((len > 0) && (status == VIOSRP_MAD_SUCCESS) && !rc) अणु
			dev_dbg(&vscsi->dev, "cap_mad: len left %hd, cap type %d, cap len %hd\n",
				len, be32_to_cpu(common->cap_type),
				be16_to_cpu(common->length));

			cap_len = be16_to_cpu(common->length);
			अगर (cap_len > len) अणु
				dev_err(&vscsi->dev, "cap_mad: cap len mismatch with total len\n");
				status = VIOSRP_MAD_FAILED;
				अवरोध;
			पूर्ण

			अगर (cap_len == 0) अणु
				dev_err(&vscsi->dev, "cap_mad: cap len is 0\n");
				status = VIOSRP_MAD_FAILED;
				अवरोध;
			पूर्ण

			चयन (common->cap_type) अणु
			शेष:
				dev_dbg(&vscsi->dev, "cap_mad: unsupported capability\n");
				common->server_support = 0;
				flag = cpu_to_be32((u32)CAP_LIST_SUPPORTED);
				cap->flags &= ~flag;
				अवरोध;
			पूर्ण

			len = len - cap_len;
			common = (काष्ठा mad_capability_common *)
				((अक्षर *)common + cap_len);
		पूर्ण

		mad->common.status = cpu_to_be16(status);

		dma_wmb();
		rc = h_copy_rdma(olen, vscsi->dds.winकरोw[LOCAL].liobn, token,
				 vscsi->dds.winकरोw[REMOTE].liobn,
				 be64_to_cpu(mad->buffer));

		अगर (rc != H_SUCCESS) अणु
			dev_dbg(&vscsi->dev, "cap_mad: failed to copy to client, rc %ld\n",
				rc);

			अगर (rc == H_PERMISSION) अणु
				अगर (connection_broken(vscsi))
					flag_bits = (RESPONSE_Q_DOWN |
						     CLIENT_FAILED);
			पूर्ण

			dev_warn(&vscsi->dev, "cap_mad: error copying data to client, rc %ld\n",
				 rc);
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT,
						  flag_bits);
		पूर्ण
	पूर्ण

	dma_मुक्त_coherent(&vscsi->dma_dev->dev, olen, cap, token);

	dev_dbg(&vscsi->dev, "Leaving cap_mad, rc %ld, client_cap 0x%x\n",
		rc, vscsi->client_cap);

	वापस rc;
पूर्ण

/**
 * ibmvscsis_process_mad() - Service a MAnagement Data gram
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @iue:	Inक्रमmation Unit containing the MAD request
 *
 * Must be called with पूर्णांकerrupt lock held.
 */
अटल दीर्घ ibmvscsis_process_mad(काष्ठा scsi_info *vscsi, काष्ठा iu_entry *iue)
अणु
	काष्ठा mad_common *mad = (काष्ठा mad_common *)&vio_iu(iue)->mad;
	काष्ठा viosrp_empty_iu *empty;
	दीर्घ rc = ADAPT_SUCCESS;

	चयन (be32_to_cpu(mad->type)) अणु
	हाल VIOSRP_EMPTY_IU_TYPE:
		empty = &vio_iu(iue)->mad.empty_iu;
		vscsi->empty_iu_id = be64_to_cpu(empty->buffer);
		vscsi->empty_iu_tag = be64_to_cpu(empty->common.tag);
		mad->status = cpu_to_be16(VIOSRP_MAD_SUCCESS);
		अवरोध;
	हाल VIOSRP_ADAPTER_INFO_TYPE:
		rc = ibmvscsis_adapter_info(vscsi, iue);
		अवरोध;
	हाल VIOSRP_CAPABILITIES_TYPE:
		rc = ibmvscsis_cap_mad(vscsi, iue);
		अवरोध;
	हाल VIOSRP_ENABLE_FAST_FAIL:
		अगर (vscsi->state == CONNECTED) अणु
			vscsi->fast_fail = true;
			mad->status = cpu_to_be16(VIOSRP_MAD_SUCCESS);
		पूर्ण अन्यथा अणु
			dev_warn(&vscsi->dev, "fast fail mad sent after login\n");
			mad->status = cpu_to_be16(VIOSRP_MAD_FAILED);
		पूर्ण
		अवरोध;
	शेष:
		mad->status = cpu_to_be16(VIOSRP_MAD_NOT_SUPPORTED);
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * srp_snd_msg_failed() - Handle an error when sending a response
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @rc:		The वापस code from the h_send_crq command
 *
 * Must be called with पूर्णांकerrupt lock held.
 */
अटल व्योम srp_snd_msg_failed(काष्ठा scsi_info *vscsi, दीर्घ rc)
अणु
	kसमय_प्रकार kt;

	अगर (rc != H_DROPPED) अणु
		ibmvscsis_मुक्त_cmd_qs(vscsi);

		अगर (rc == H_CLOSED)
			vscsi->flags |= CLIENT_FAILED;

		/* करोn't flag the same problem multiple बार */
		अगर (!(vscsi->flags & RESPONSE_Q_DOWN)) अणु
			vscsi->flags |= RESPONSE_Q_DOWN;
			अगर (!(vscsi->state & (ERR_DISCONNECT |
					      ERR_DISCONNECT_RECONNECT |
					      ERR_DISCONNECTED | UNDEFINED))) अणु
				dev_err(&vscsi->dev, "snd_msg_failed: setting RESPONSE_Q_DOWN, state 0x%hx, flags 0x%x, rc %ld\n",
					vscsi->state, vscsi->flags, rc);
			पूर्ण
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT, 0);
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * The response queue is full.
	 * If the server is processing SRP requests, i.e.
	 * the client has successfully करोne an
	 * SRP_LOGIN, then it will रुको क्रमever क्रम room in
	 * the queue.  However अगर the प्रणाली admin
	 * is attempting to unconfigure the server then one
	 * or more children will be in a state where
	 * they are being हटाओd. So अगर there is even one
	 * child being हटाओd then the driver assumes
	 * the प्रणाली admin is attempting to अवरोध the
	 * connection with the client and MAX_TIMER_POPS
	 * is honored.
	 */
	अगर ((vscsi->rsp_q_समयr.समयr_pops < MAX_TIMER_POPS) ||
	    (vscsi->state == SRP_PROCESSING)) अणु
		dev_dbg(&vscsi->dev, "snd_msg_failed: response queue full, flags 0x%x, timer started %d, pops %d\n",
			vscsi->flags, (पूर्णांक)vscsi->rsp_q_समयr.started,
			vscsi->rsp_q_समयr.समयr_pops);

		/*
		 * Check अगर the समयr is running; अगर it
		 * is not then start it up.
		 */
		अगर (!vscsi->rsp_q_समयr.started) अणु
			अगर (vscsi->rsp_q_समयr.समयr_pops <
			    MAX_TIMER_POPS) अणु
				kt = WAIT_न_अंकO_SECONDS;
			पूर्ण अन्यथा अणु
				/*
				 * slide the बारlice अगर the maximum
				 * समयr pops have alपढ़ोy happened
				 */
				kt = kसमय_set(WAIT_SECONDS, 0);
			पूर्ण

			vscsi->rsp_q_समयr.started = true;
			hrसमयr_start(&vscsi->rsp_q_समयr.समयr, kt,
				      HRTIMER_MODE_REL);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * TBD: Do we need to worry about this? Need to get
		 *      हटाओ working.
		 */
		/*
		 * रुकोed a दीर्घ समय and it appears the प्रणाली admin
		 * is bring this driver करोwn
		 */
		vscsi->flags |= RESPONSE_Q_DOWN;
		ibmvscsis_मुक्त_cmd_qs(vscsi);
		/*
		 * अगर the driver is alपढ़ोy attempting to disconnect
		 * from the client and has alपढ़ोy logged an error
		 * trace this event but करोn't put it in the error log
		 */
		अगर (!(vscsi->state & (ERR_DISCONNECT |
				      ERR_DISCONNECT_RECONNECT |
				      ERR_DISCONNECTED | UNDEFINED))) अणु
			dev_err(&vscsi->dev, "client crq full too long\n");
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT,
						  0);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ibmvscsis_send_messages() - Send a Response
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * Send a response, first checking the रुकोing queue. Responses are
 * sent in order they are received. If the response cannot be sent,
 * because the client queue is full, it stays on the रुकोing queue.
 *
 * PRECONDITION:
 *	Called with पूर्णांकerrupt lock held
 */
अटल व्योम ibmvscsis_send_messages(काष्ठा scsi_info *vscsi)
अणु
	u64 msg_hi = 0;
	/* note करो not attempt to access the IU_data_ptr with this poपूर्णांकer
	 * it is not valid
	 */
	काष्ठा viosrp_crq *crq = (काष्ठा viosrp_crq *)&msg_hi;
	काष्ठा ibmvscsis_cmd *cmd, *nxt;
	दीर्घ rc = ADAPT_SUCCESS;
	bool retry = false;

	अगर (!(vscsi->flags & RESPONSE_Q_DOWN)) अणु
		करो अणु
			retry = false;
			list_क्रम_each_entry_safe(cmd, nxt, &vscsi->रुकोing_rsp,
						 list) अणु
				/*
				 * Check to make sure पात cmd माला_लो processed
				 * prior to the पात पंचांगr cmd
				 */
				अगर (cmd->flags & DELAY_SEND)
					जारी;

				अगर (cmd->पात_cmd) अणु
					retry = true;
					cmd->पात_cmd->flags &= ~(DELAY_SEND);
					cmd->पात_cmd = शून्य;
				पूर्ण

				/*
				 * If CMD_T_ABORTED w/o CMD_T_TAS scenarios and
				 * the हाल where LIO issued a
				 * ABORT_TASK: Sending TMR_TASK_DOES_NOT_EXIST
				 * हाल then we करोnt send a response, since it
				 * was alपढ़ोy करोne.
				 */
				अगर (cmd->se_cmd.transport_state & CMD_T_ABORTED &&
				    !(cmd->se_cmd.transport_state & CMD_T_TAS)) अणु
					list_del(&cmd->list);
					ibmvscsis_मुक्त_cmd_resources(vscsi,
								     cmd);
					/*
					 * With a successfully पातed op
					 * through LIO we want to increment the
					 * the vscsi credit so that when we करोnt
					 * send a rsp to the original scsi पात
					 * op (h_send_crq), but the पंचांग rsp to
					 * the पात is sent, the credit is
					 * correctly sent with the पात पंचांग rsp.
					 * We would need 1 क्रम the पात पंचांग rsp
					 * and 1 credit क्रम the पातed scsi op.
					 * Thus we need to increment here.
					 * Also we want to increment the credit
					 * here because we want to make sure
					 * cmd is actually released first
					 * otherwise the client will think it
					 * it can send a new cmd, and we could
					 * find ourselves लघु of cmd elements.
					 */
					vscsi->credit += 1;
				पूर्ण अन्यथा अणु
					crq->valid = VALID_CMD_RESP_EL;
					crq->क्रमmat = cmd->rsp.क्रमmat;

					अगर (cmd->flags & CMD_FAST_FAIL)
						crq->status = VIOSRP_ADAPTER_FAIL;

					crq->IU_length = cpu_to_be16(cmd->rsp.len);

					rc = h_send_crq(vscsi->dma_dev->unit_address,
							be64_to_cpu(msg_hi),
							be64_to_cpu(cmd->rsp.tag));

					dev_dbg(&vscsi->dev, "send_messages: cmd %p, tag 0x%llx, rc %ld\n",
						cmd, be64_to_cpu(cmd->rsp.tag),
						rc);

					/* अगर all ok मुक्त up the command
					 * element resources
					 */
					अगर (rc == H_SUCCESS) अणु
						/* some movement has occurred */
						vscsi->rsp_q_समयr.समयr_pops = 0;
						list_del(&cmd->list);

						ibmvscsis_मुक्त_cmd_resources(vscsi,
									     cmd);
					पूर्ण अन्यथा अणु
						srp_snd_msg_failed(vscsi, rc);
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण जबतक (retry);

		अगर (!rc) अणु
			/*
			 * The समयr could pop with the queue empty.  If
			 * this happens, rc will always indicate a
			 * success; clear the pop count.
			 */
			vscsi->rsp_q_समयr.समयr_pops = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		ibmvscsis_मुक्त_cmd_qs(vscsi);
	पूर्ण
पूर्ण

/* Called with पूर्णांकr lock held */
अटल व्योम ibmvscsis_send_mad_resp(काष्ठा scsi_info *vscsi,
				    काष्ठा ibmvscsis_cmd *cmd,
				    काष्ठा viosrp_crq *crq)
अणु
	काष्ठा iu_entry *iue = cmd->iue;
	काष्ठा mad_common *mad = (काष्ठा mad_common *)&vio_iu(iue)->mad;
	uपूर्णांक flag_bits = 0;
	दीर्घ rc;

	dma_wmb();
	rc = h_copy_rdma(माप(काष्ठा mad_common),
			 vscsi->dds.winकरोw[LOCAL].liobn, iue->sbuf->dma,
			 vscsi->dds.winकरोw[REMOTE].liobn,
			 be64_to_cpu(crq->IU_data_ptr));
	अगर (!rc) अणु
		cmd->rsp.क्रमmat = VIOSRP_MAD_FORMAT;
		cmd->rsp.len = माप(काष्ठा mad_common);
		cmd->rsp.tag = mad->tag;
		list_add_tail(&cmd->list, &vscsi->रुकोing_rsp);
		ibmvscsis_send_messages(vscsi);
	पूर्ण अन्यथा अणु
		dev_dbg(&vscsi->dev, "Error sending mad response, rc %ld\n",
			rc);
		अगर (rc == H_PERMISSION) अणु
			अगर (connection_broken(vscsi))
				flag_bits = (RESPONSE_Q_DOWN | CLIENT_FAILED);
		पूर्ण
		dev_err(&vscsi->dev, "mad: failed to copy to client, rc %ld\n",
			rc);

		ibmvscsis_मुक्त_cmd_resources(vscsi, cmd);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT,
					  flag_bits);
	पूर्ण
पूर्ण

/**
 * ibmvscsis_mad() - Service a MAnagement Data gram.
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @crq:	Poपूर्णांकer to the CRQ entry containing the MAD request
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt, called with adapter lock held
 */
अटल दीर्घ ibmvscsis_mad(काष्ठा scsi_info *vscsi, काष्ठा viosrp_crq *crq)
अणु
	काष्ठा iu_entry *iue;
	काष्ठा ibmvscsis_cmd *cmd;
	काष्ठा mad_common *mad;
	दीर्घ rc = ADAPT_SUCCESS;

	चयन (vscsi->state) अणु
		/*
		 * We have not exchanged Init Msgs yet, so this MAD was sent
		 * beक्रमe the last Transport Event; client will not be
		 * expecting a response.
		 */
	हाल WAIT_CONNECTION:
		dev_dbg(&vscsi->dev, "mad: in Wait Connection state, ignoring MAD, flags %d\n",
			vscsi->flags);
		वापस ADAPT_SUCCESS;

	हाल SRP_PROCESSING:
	हाल CONNECTED:
		अवरोध;

		/*
		 * We should never get here जबतक we're in these states.
		 * Just log an error and get out.
		 */
	हाल UNCONFIGURING:
	हाल WAIT_IDLE:
	हाल ERR_DISCONNECT:
	हाल ERR_DISCONNECT_RECONNECT:
	शेष:
		dev_err(&vscsi->dev, "mad: invalid adapter state %d for mad\n",
			vscsi->state);
		वापस ADAPT_SUCCESS;
	पूर्ण

	cmd = ibmvscsis_get_मुक्त_cmd(vscsi);
	अगर (!cmd) अणु
		dev_err(&vscsi->dev, "mad: failed to get cmd, debit %d\n",
			vscsi->debit);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		वापस ERROR;
	पूर्ण
	iue = cmd->iue;
	cmd->type = ADAPTER_MAD;

	rc = ibmvscsis_copy_crq_packet(vscsi, cmd, crq);
	अगर (!rc) अणु
		mad = (काष्ठा mad_common *)&vio_iu(iue)->mad;

		dev_dbg(&vscsi->dev, "mad: type %d\n", be32_to_cpu(mad->type));

		rc = ibmvscsis_process_mad(vscsi, iue);

		dev_dbg(&vscsi->dev, "mad: status %hd, rc %ld\n",
			be16_to_cpu(mad->status), rc);

		अगर (!rc)
			ibmvscsis_send_mad_resp(vscsi, cmd, crq);
	पूर्ण अन्यथा अणु
		ibmvscsis_मुक्त_cmd_resources(vscsi, cmd);
	पूर्ण

	dev_dbg(&vscsi->dev, "Leaving mad, rc %ld\n", rc);
	वापस rc;
पूर्ण

/**
 * ibmvscsis_login_rsp() - Create/copy a login response notice to the client
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @cmd:	Poपूर्णांकer to the command क्रम the SRP Login request
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt, पूर्णांकerrupt lock held
 */
अटल दीर्घ ibmvscsis_login_rsp(काष्ठा scsi_info *vscsi,
				काष्ठा ibmvscsis_cmd *cmd)
अणु
	काष्ठा iu_entry *iue = cmd->iue;
	काष्ठा srp_login_rsp *rsp = &vio_iu(iue)->srp.login_rsp;
	काष्ठा क्रमmat_code *fmt;
	uपूर्णांक flag_bits = 0;
	दीर्घ rc = ADAPT_SUCCESS;

	स_रखो(rsp, 0, माप(काष्ठा srp_login_rsp));

	rsp->opcode = SRP_LOGIN_RSP;
	rsp->req_lim_delta = cpu_to_be32(vscsi->request_limit);
	rsp->tag = cmd->rsp.tag;
	rsp->max_it_iu_len = cpu_to_be32(SRP_MAX_IU_LEN);
	rsp->max_ti_iu_len = cpu_to_be32(SRP_MAX_IU_LEN);
	fmt = (काष्ठा क्रमmat_code *)&rsp->buf_fmt;
	fmt->buffers = SUPPORTED_FORMATS;
	vscsi->credit = 0;

	cmd->rsp.len = माप(काष्ठा srp_login_rsp);

	dma_wmb();
	rc = h_copy_rdma(cmd->rsp.len, vscsi->dds.winकरोw[LOCAL].liobn,
			 iue->sbuf->dma, vscsi->dds.winकरोw[REMOTE].liobn,
			 be64_to_cpu(iue->remote_token));

	चयन (rc) अणु
	हाल H_SUCCESS:
		अवरोध;

	हाल H_PERMISSION:
		अगर (connection_broken(vscsi))
			flag_bits = RESPONSE_Q_DOWN | CLIENT_FAILED;
		dev_err(&vscsi->dev, "login_rsp: error copying to client, rc %ld\n",
			rc);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT,
					  flag_bits);
		अवरोध;
	हाल H_SOURCE_PARM:
	हाल H_DEST_PARM:
	शेष:
		dev_err(&vscsi->dev, "login_rsp: error copying to client, rc %ld\n",
			rc);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ibmvscsis_srp_login_rej() - Create/copy a login rejection notice to client
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @cmd:	Poपूर्णांकer to the command क्रम the SRP Login request
 * @reason:	The reason the SRP Login is being rejected, per SRP protocol
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt, पूर्णांकerrupt lock held
 */
अटल दीर्घ ibmvscsis_srp_login_rej(काष्ठा scsi_info *vscsi,
				    काष्ठा ibmvscsis_cmd *cmd, u32 reason)
अणु
	काष्ठा iu_entry *iue = cmd->iue;
	काष्ठा srp_login_rej *rej = &vio_iu(iue)->srp.login_rej;
	काष्ठा क्रमmat_code *fmt;
	uपूर्णांक flag_bits = 0;
	दीर्घ rc = ADAPT_SUCCESS;

	स_रखो(rej, 0, माप(*rej));

	rej->opcode = SRP_LOGIN_REJ;
	rej->reason = cpu_to_be32(reason);
	rej->tag = cmd->rsp.tag;
	fmt = (काष्ठा क्रमmat_code *)&rej->buf_fmt;
	fmt->buffers = SUPPORTED_FORMATS;

	cmd->rsp.len = माप(*rej);

	dma_wmb();
	rc = h_copy_rdma(cmd->rsp.len, vscsi->dds.winकरोw[LOCAL].liobn,
			 iue->sbuf->dma, vscsi->dds.winकरोw[REMOTE].liobn,
			 be64_to_cpu(iue->remote_token));

	चयन (rc) अणु
	हाल H_SUCCESS:
		अवरोध;
	हाल H_PERMISSION:
		अगर (connection_broken(vscsi))
			flag_bits = RESPONSE_Q_DOWN | CLIENT_FAILED;
		dev_err(&vscsi->dev, "login_rej: error copying to client, rc %ld\n",
			rc);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT,
					  flag_bits);
		अवरोध;
	हाल H_SOURCE_PARM:
	हाल H_DEST_PARM:
	शेष:
		dev_err(&vscsi->dev, "login_rej: error copying to client, rc %ld\n",
			rc);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक ibmvscsis_make_nexus(काष्ठा ibmvscsis_tport *tport)
अणु
	अक्षर *name = tport->tport_name;
	काष्ठा ibmvscsis_nexus *nexus;
	काष्ठा scsi_info *vscsi = container_of(tport, काष्ठा scsi_info, tport);
	पूर्णांक rc;

	अगर (tport->ibmv_nexus) अणु
		dev_dbg(&vscsi->dev, "tport->ibmv_nexus already exists\n");
		वापस 0;
	पूर्ण

	nexus = kzalloc(माप(*nexus), GFP_KERNEL);
	अगर (!nexus) अणु
		dev_err(&vscsi->dev, "Unable to allocate struct ibmvscsis_nexus\n");
		वापस -ENOMEM;
	पूर्ण

	nexus->se_sess = target_setup_session(&tport->se_tpg, 0, 0,
					      TARGET_PROT_NORMAL, name, nexus,
					      शून्य);
	अगर (IS_ERR(nexus->se_sess)) अणु
		rc = PTR_ERR(nexus->se_sess);
		जाओ transport_init_fail;
	पूर्ण

	tport->ibmv_nexus = nexus;

	वापस 0;

transport_init_fail:
	kमुक्त(nexus);
	वापस rc;
पूर्ण

अटल पूर्णांक ibmvscsis_drop_nexus(काष्ठा ibmvscsis_tport *tport)
अणु
	काष्ठा se_session *se_sess;
	काष्ठा ibmvscsis_nexus *nexus;

	nexus = tport->ibmv_nexus;
	अगर (!nexus)
		वापस -ENODEV;

	se_sess = nexus->se_sess;
	अगर (!se_sess)
		वापस -ENODEV;

	/*
	 * Release the SCSI I_T Nexus to the emulated ibmvscsis Target Port
	 */
	target_हटाओ_session(se_sess);
	tport->ibmv_nexus = शून्य;
	kमुक्त(nexus);

	वापस 0;
पूर्ण

/**
 * ibmvscsis_srp_login() - Process an SRP Login Request
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @cmd:	Command element to use to process the SRP Login request
 * @crq:	Poपूर्णांकer to CRQ entry containing the SRP Login request
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt, called with पूर्णांकerrupt lock held
 */
अटल दीर्घ ibmvscsis_srp_login(काष्ठा scsi_info *vscsi,
				काष्ठा ibmvscsis_cmd *cmd,
				काष्ठा viosrp_crq *crq)
अणु
	काष्ठा iu_entry *iue = cmd->iue;
	काष्ठा srp_login_req *req = &vio_iu(iue)->srp.login_req;
	काष्ठा port_id अणु
		__be64 id_extension;
		__be64 io_guid;
	पूर्ण *iport, *tport;
	काष्ठा क्रमmat_code *fmt;
	u32 reason = 0x0;
	दीर्घ rc = ADAPT_SUCCESS;

	iport = (काष्ठा port_id *)req->initiator_port_id;
	tport = (काष्ठा port_id *)req->target_port_id;
	fmt = (काष्ठा क्रमmat_code *)&req->req_buf_fmt;
	अगर (be32_to_cpu(req->req_it_iu_len) > SRP_MAX_IU_LEN)
		reason = SRP_LOGIN_REJ_REQ_IT_IU_LENGTH_TOO_LARGE;
	अन्यथा अगर (be32_to_cpu(req->req_it_iu_len) < 64)
		reason = SRP_LOGIN_REJ_UNABLE_ESTABLISH_CHANNEL;
	अन्यथा अगर ((be64_to_cpu(iport->id_extension) > (MAX_NUM_PORTS - 1)) ||
		 (be64_to_cpu(tport->id_extension) > (MAX_NUM_PORTS - 1)))
		reason = SRP_LOGIN_REJ_UNABLE_ASSOCIATE_CHANNEL;
	अन्यथा अगर (req->req_flags & SRP_MULTICHAN_MULTI)
		reason = SRP_LOGIN_REJ_MULTI_CHANNEL_UNSUPPORTED;
	अन्यथा अगर (fmt->buffers & (~SUPPORTED_FORMATS))
		reason = SRP_LOGIN_REJ_UNSUPPORTED_DESCRIPTOR_FMT;
	अन्यथा अगर ((fmt->buffers & SUPPORTED_FORMATS) == 0)
		reason = SRP_LOGIN_REJ_UNSUPPORTED_DESCRIPTOR_FMT;

	अगर (vscsi->state == SRP_PROCESSING)
		reason = SRP_LOGIN_REJ_CHANNEL_LIMIT_REACHED;

	rc = ibmvscsis_make_nexus(&vscsi->tport);
	अगर (rc)
		reason = SRP_LOGIN_REJ_UNABLE_ESTABLISH_CHANNEL;

	cmd->rsp.क्रमmat = VIOSRP_SRP_FORMAT;
	cmd->rsp.tag = req->tag;

	dev_dbg(&vscsi->dev, "srp_login: reason 0x%x\n", reason);

	अगर (reason)
		rc = ibmvscsis_srp_login_rej(vscsi, cmd, reason);
	अन्यथा
		rc = ibmvscsis_login_rsp(vscsi, cmd);

	अगर (!rc) अणु
		अगर (!reason)
			vscsi->state = SRP_PROCESSING;

		list_add_tail(&cmd->list, &vscsi->रुकोing_rsp);
		ibmvscsis_send_messages(vscsi);
	पूर्ण अन्यथा अणु
		ibmvscsis_मुक्त_cmd_resources(vscsi, cmd);
	पूर्ण

	dev_dbg(&vscsi->dev, "Leaving srp_login, rc %ld\n", rc);
	वापस rc;
पूर्ण

/**
 * ibmvscsis_srp_i_logout() - Helper Function to बंद I_T Nexus
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @cmd:	Command element to use to process the Implicit Logout request
 * @crq:	Poपूर्णांकer to CRQ entry containing the Implicit Logout request
 *
 * Do the logic to बंद the I_T nexus.  This function may not
 * behave to specअगरication.
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt, पूर्णांकerrupt lock held
 */
अटल दीर्घ ibmvscsis_srp_i_logout(काष्ठा scsi_info *vscsi,
				   काष्ठा ibmvscsis_cmd *cmd,
				   काष्ठा viosrp_crq *crq)
अणु
	काष्ठा iu_entry *iue = cmd->iue;
	काष्ठा srp_i_logout *log_out = &vio_iu(iue)->srp.i_logout;

	अगर ((vscsi->debit > 0) || !list_empty(&vscsi->schedule_q) ||
	    !list_empty(&vscsi->रुकोing_rsp)) अणु
		dev_err(&vscsi->dev, "i_logout: outstanding work\n");
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT, 0);
	पूर्ण अन्यथा अणु
		cmd->rsp.क्रमmat = SRP_FORMAT;
		cmd->rsp.tag = log_out->tag;
		cmd->rsp.len = माप(काष्ठा mad_common);
		list_add_tail(&cmd->list, &vscsi->रुकोing_rsp);
		ibmvscsis_send_messages(vscsi);

		ibmvscsis_post_disconnect(vscsi, WAIT_IDLE, 0);
	पूर्ण

	वापस ADAPT_SUCCESS;
पूर्ण

/* Called with पूर्णांकr lock held */
अटल व्योम ibmvscsis_srp_cmd(काष्ठा scsi_info *vscsi, काष्ठा viosrp_crq *crq)
अणु
	काष्ठा ibmvscsis_cmd *cmd;
	काष्ठा iu_entry *iue;
	काष्ठा srp_cmd *srp;
	काष्ठा srp_tsk_mgmt *tsk;
	दीर्घ rc;

	अगर (vscsi->request_limit - vscsi->debit <= 0) अणु
		/* Client has exceeded request limit */
		dev_err(&vscsi->dev, "Client exceeded the request limit (%d), debit %d\n",
			vscsi->request_limit, vscsi->debit);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		वापस;
	पूर्ण

	cmd = ibmvscsis_get_मुक्त_cmd(vscsi);
	अगर (!cmd) अणु
		dev_err(&vscsi->dev, "srp_cmd failed to get cmd, debit %d\n",
			vscsi->debit);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		वापस;
	पूर्ण
	iue = cmd->iue;
	srp = &vio_iu(iue)->srp.cmd;

	rc = ibmvscsis_copy_crq_packet(vscsi, cmd, crq);
	अगर (rc) अणु
		ibmvscsis_मुक्त_cmd_resources(vscsi, cmd);
		वापस;
	पूर्ण

	अगर (vscsi->state == SRP_PROCESSING) अणु
		चयन (srp->opcode) अणु
		हाल SRP_LOGIN_REQ:
			rc = ibmvscsis_srp_login(vscsi, cmd, crq);
			अवरोध;

		हाल SRP_TSK_MGMT:
			tsk = &vio_iu(iue)->srp.tsk_mgmt;
			dev_dbg(&vscsi->dev, "tsk_mgmt tag: %llu (0x%llx)\n",
				tsk->tag, tsk->tag);
			cmd->rsp.tag = tsk->tag;
			vscsi->debit += 1;
			cmd->type = TASK_MANAGEMENT;
			list_add_tail(&cmd->list, &vscsi->schedule_q);
			queue_work(vscsi->work_q, &cmd->work);
			अवरोध;

		हाल SRP_CMD:
			dev_dbg(&vscsi->dev, "srp_cmd tag: %llu (0x%llx)\n",
				srp->tag, srp->tag);
			cmd->rsp.tag = srp->tag;
			vscsi->debit += 1;
			cmd->type = SCSI_CDB;
			/*
			 * We want to keep track of work रुकोing क्रम
			 * the workqueue.
			 */
			list_add_tail(&cmd->list, &vscsi->schedule_q);
			queue_work(vscsi->work_q, &cmd->work);
			अवरोध;

		हाल SRP_I_LOGOUT:
			rc = ibmvscsis_srp_i_logout(vscsi, cmd, crq);
			अवरोध;

		हाल SRP_CRED_RSP:
		हाल SRP_AER_RSP:
		शेष:
			ibmvscsis_मुक्त_cmd_resources(vscsi, cmd);
			dev_err(&vscsi->dev, "invalid srp cmd, opcode %d\n",
				(uपूर्णांक)srp->opcode);
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT, 0);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (srp->opcode == SRP_LOGIN_REQ && vscsi->state == CONNECTED) अणु
		rc = ibmvscsis_srp_login(vscsi, cmd, crq);
	पूर्ण अन्यथा अणु
		ibmvscsis_मुक्त_cmd_resources(vscsi, cmd);
		dev_err(&vscsi->dev, "Invalid state %d to handle srp cmd\n",
			vscsi->state);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
	पूर्ण
पूर्ण

/**
 * ibmvscsis_ping_response() - Respond to a ping request
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * Let the client know that the server is alive and रुकोing on
 * its native I/O stack.
 * If any type of error occurs from the call to queue a ping
 * response then the client is either not accepting or receiving
 * पूर्णांकerrupts.  Disconnect with an error.
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt, पूर्णांकerrupt lock held
 */
अटल दीर्घ ibmvscsis_ping_response(काष्ठा scsi_info *vscsi)
अणु
	काष्ठा viosrp_crq *crq;
	u64 buffer[2] = अणु 0, 0 पूर्ण;
	दीर्घ rc;

	crq = (काष्ठा viosrp_crq *)&buffer;
	crq->valid = VALID_CMD_RESP_EL;
	crq->क्रमmat = (u8)MESSAGE_IN_CRQ;
	crq->status = PING_RESPONSE;

	rc = h_send_crq(vscsi->dds.unit_id, cpu_to_be64(buffer[MSG_HI]),
			cpu_to_be64(buffer[MSG_LOW]));

	चयन (rc) अणु
	हाल H_SUCCESS:
		अवरोध;
	हाल H_CLOSED:
		vscsi->flags |= CLIENT_FAILED;
		fallthrough;
	हाल H_DROPPED:
		vscsi->flags |= RESPONSE_Q_DOWN;
		fallthrough;
	हाल H_REMOTE_PARM:
		dev_err(&vscsi->dev, "ping_response: h_send_crq failed, rc %ld\n",
			rc);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		अवरोध;
	शेष:
		dev_err(&vscsi->dev, "ping_response: h_send_crq returned unknown rc %ld\n",
			rc);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT, 0);
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ibmvscsis_parse_command() - Parse an element taken from the cmd rsp queue.
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @crq:	Poपूर्णांकer to CRQ element containing the SRP request
 *
 * This function will वापस success अगर the command queue element is valid
 * and the srp iu or MAD request it poपूर्णांकed to was also valid.  That करोes
 * not mean that an error was not वापसed to the client.
 *
 * EXECUTION ENVIRONMENT:
 *	Interrupt, पूर्णांकr lock held
 */
अटल दीर्घ ibmvscsis_parse_command(काष्ठा scsi_info *vscsi,
				    काष्ठा viosrp_crq *crq)
अणु
	दीर्घ rc = ADAPT_SUCCESS;

	चयन (crq->valid) अणु
	हाल VALID_CMD_RESP_EL:
		चयन (crq->क्रमmat) अणु
		हाल OS400_FORMAT:
		हाल AIX_FORMAT:
		हाल LINUX_FORMAT:
		हाल MAD_FORMAT:
			अगर (vscsi->flags & PROCESSING_MAD) अणु
				rc = ERROR;
				dev_err(&vscsi->dev, "parse_command: already processing mad\n");
				ibmvscsis_post_disconnect(vscsi,
						       ERR_DISCONNECT_RECONNECT,
						       0);
			पूर्ण अन्यथा अणु
				vscsi->flags |= PROCESSING_MAD;
				rc = ibmvscsis_mad(vscsi, crq);
			पूर्ण
			अवरोध;

		हाल SRP_FORMAT:
			ibmvscsis_srp_cmd(vscsi, crq);
			अवरोध;

		हाल MESSAGE_IN_CRQ:
			अगर (crq->status == PING)
				ibmvscsis_ping_response(vscsi);
			अवरोध;

		शेष:
			dev_err(&vscsi->dev, "parse_command: invalid format %d\n",
				(uपूर्णांक)crq->क्रमmat);
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT, 0);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल VALID_TRANS_EVENT:
		rc = ibmvscsis_trans_event(vscsi, crq);
		अवरोध;

	हाल VALID_INIT_MSG:
		rc = ibmvscsis_init_msg(vscsi, crq);
		अवरोध;

	शेष:
		dev_err(&vscsi->dev, "parse_command: invalid valid field %d\n",
			(uपूर्णांक)crq->valid);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		अवरोध;
	पूर्ण

	/*
	 * Return only what the पूर्णांकerrupt handler cares
	 * about. Most errors we keep right on trucking.
	 */
	rc = vscsi->flags & SCHEDULE_DISCONNECT;

	वापस rc;
पूर्ण

अटल पूर्णांक पढ़ो_dma_winकरोw(काष्ठा scsi_info *vscsi)
अणु
	काष्ठा vio_dev *vdev = vscsi->dma_dev;
	स्थिर __be32 *dma_winकरोw;
	स्थिर __be32 *prop;

	/* TODO Using of_parse_dma_winकरोw would be better, but it करोesn't give
	 * a way to पढ़ो multiple winकरोws without alपढ़ोy knowing the size of
	 * a winकरोw or the number of winकरोws.
	 */
	dma_winकरोw = (स्थिर __be32 *)vio_get_attribute(vdev,
						       "ibm,my-dma-window",
						       शून्य);
	अगर (!dma_winकरोw) अणु
		dev_err(&vscsi->dev, "Couldn't find ibm,my-dma-window property\n");
		वापस -1;
	पूर्ण

	vscsi->dds.winकरोw[LOCAL].liobn = be32_to_cpu(*dma_winकरोw);
	dma_winकरोw++;

	prop = (स्थिर __be32 *)vio_get_attribute(vdev, "ibm,#dma-address-cells",
						 शून्य);
	अगर (!prop) अणु
		dev_warn(&vscsi->dev, "Couldn't find ibm,#dma-address-cells property\n");
		dma_winकरोw++;
	पूर्ण अन्यथा अणु
		dma_winकरोw += be32_to_cpu(*prop);
	पूर्ण

	prop = (स्थिर __be32 *)vio_get_attribute(vdev, "ibm,#dma-size-cells",
						 शून्य);
	अगर (!prop) अणु
		dev_warn(&vscsi->dev, "Couldn't find ibm,#dma-size-cells property\n");
		dma_winकरोw++;
	पूर्ण अन्यथा अणु
		dma_winकरोw += be32_to_cpu(*prop);
	पूर्ण

	/* dma_winकरोw should poपूर्णांक to the second winकरोw now */
	vscsi->dds.winकरोw[REMOTE].liobn = be32_to_cpu(*dma_winकरोw);

	वापस 0;
पूर्ण

अटल काष्ठा ibmvscsis_tport *ibmvscsis_lookup_port(स्थिर अक्षर *name)
अणु
	काष्ठा ibmvscsis_tport *tport = शून्य;
	काष्ठा vio_dev *vdev;
	काष्ठा scsi_info *vscsi;

	spin_lock_bh(&ibmvscsis_dev_lock);
	list_क्रम_each_entry(vscsi, &ibmvscsis_dev_list, list) अणु
		vdev = vscsi->dma_dev;
		अगर (!म_भेद(dev_name(&vdev->dev), name)) अणु
			tport = &vscsi->tport;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ibmvscsis_dev_lock);

	वापस tport;
पूर्ण

/**
 * ibmvscsis_parse_cmd() - Parse SRP Command
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @cmd:	Poपूर्णांकer to command element with SRP command
 *
 * Parse the srp command; अगर it is valid then submit it to tcm.
 * Note: The वापस code करोes not reflect the status of the SCSI CDB.
 *
 * EXECUTION ENVIRONMENT:
 *	Process level
 */
अटल व्योम ibmvscsis_parse_cmd(काष्ठा scsi_info *vscsi,
				काष्ठा ibmvscsis_cmd *cmd)
अणु
	काष्ठा iu_entry *iue = cmd->iue;
	काष्ठा srp_cmd *srp = (काष्ठा srp_cmd *)iue->sbuf->buf;
	काष्ठा ibmvscsis_nexus *nexus;
	u64 data_len = 0;
	क्रमागत dma_data_direction dir;
	पूर्णांक attr = 0;

	nexus = vscsi->tport.ibmv_nexus;
	/*
	 * additional length in bytes.  Note that the SRP spec says that
	 * additional length is in 4-byte words, but technically the
	 * additional length field is only the upper 6 bits of the byte.
	 * The lower 2 bits are reserved.  If the lower 2 bits are 0 (as
	 * all reserved fields should be), then पूर्णांकerpreting the byte as
	 * an पूर्णांक will yield the length in bytes.
	 */
	अगर (srp->add_cdb_len & 0x03) अणु
		dev_err(&vscsi->dev, "parse_cmd: reserved bits set in IU\n");
		spin_lock_bh(&vscsi->पूर्णांकr_lock);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		ibmvscsis_मुक्त_cmd_resources(vscsi, cmd);
		spin_unlock_bh(&vscsi->पूर्णांकr_lock);
		वापस;
	पूर्ण

	अगर (srp_get_desc_table(srp, &dir, &data_len)) अणु
		dev_err(&vscsi->dev, "0x%llx: parsing SRP descriptor table failed.\n",
			srp->tag);
		जाओ fail;
	पूर्ण

	cmd->rsp.sol_not = srp->sol_not;

	चयन (srp->task_attr) अणु
	हाल SRP_SIMPLE_TASK:
		attr = TCM_SIMPLE_TAG;
		अवरोध;
	हाल SRP_ORDERED_TASK:
		attr = TCM_ORDERED_TAG;
		अवरोध;
	हाल SRP_HEAD_TASK:
		attr = TCM_HEAD_TAG;
		अवरोध;
	हाल SRP_ACA_TASK:
		attr = TCM_ACA_TAG;
		अवरोध;
	शेष:
		dev_err(&vscsi->dev, "Invalid task attribute %d\n",
			srp->task_attr);
		जाओ fail;
	पूर्ण

	cmd->se_cmd.tag = be64_to_cpu(srp->tag);

	spin_lock_bh(&vscsi->पूर्णांकr_lock);
	list_add_tail(&cmd->list, &vscsi->active_q);
	spin_unlock_bh(&vscsi->पूर्णांकr_lock);

	srp->lun.scsi_lun[0] &= 0x3f;

	target_submit_cmd(&cmd->se_cmd, nexus->se_sess, srp->cdb,
			  cmd->sense_buf, scsilun_to_पूर्णांक(&srp->lun),
			  data_len, attr, dir, 0);
	वापस;

fail:
	spin_lock_bh(&vscsi->पूर्णांकr_lock);
	ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
	spin_unlock_bh(&vscsi->पूर्णांकr_lock);
पूर्ण

/**
 * ibmvscsis_parse_task() - Parse SRP Task Management Request
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @cmd:	Poपूर्णांकer to command element with SRP task management request
 *
 * Parse the srp task management request; अगर it is valid then submit it to tcm.
 * Note: The वापस code करोes not reflect the status of the task management
 * request.
 *
 * EXECUTION ENVIRONMENT:
 *	Processor level
 */
अटल व्योम ibmvscsis_parse_task(काष्ठा scsi_info *vscsi,
				 काष्ठा ibmvscsis_cmd *cmd)
अणु
	काष्ठा iu_entry *iue = cmd->iue;
	काष्ठा srp_tsk_mgmt *srp_tsk = &vio_iu(iue)->srp.tsk_mgmt;
	पूर्णांक tcm_type;
	u64 tag_to_पात = 0;
	पूर्णांक rc = 0;
	काष्ठा ibmvscsis_nexus *nexus;

	nexus = vscsi->tport.ibmv_nexus;

	cmd->rsp.sol_not = srp_tsk->sol_not;

	चयन (srp_tsk->tsk_mgmt_func) अणु
	हाल SRP_TSK_ABORT_TASK:
		tcm_type = TMR_ABORT_TASK;
		tag_to_पात = be64_to_cpu(srp_tsk->task_tag);
		अवरोध;
	हाल SRP_TSK_ABORT_TASK_SET:
		tcm_type = TMR_ABORT_TASK_SET;
		अवरोध;
	हाल SRP_TSK_CLEAR_TASK_SET:
		tcm_type = TMR_CLEAR_TASK_SET;
		अवरोध;
	हाल SRP_TSK_LUN_RESET:
		tcm_type = TMR_LUN_RESET;
		अवरोध;
	हाल SRP_TSK_CLEAR_ACA:
		tcm_type = TMR_CLEAR_ACA;
		अवरोध;
	शेष:
		dev_err(&vscsi->dev, "unknown task mgmt func %d\n",
			srp_tsk->tsk_mgmt_func);
		cmd->se_cmd.se_पंचांगr_req->response =
			TMR_TASK_MGMT_FUNCTION_NOT_SUPPORTED;
		rc = -1;
		अवरोध;
	पूर्ण

	अगर (!rc) अणु
		cmd->se_cmd.tag = be64_to_cpu(srp_tsk->tag);

		spin_lock_bh(&vscsi->पूर्णांकr_lock);
		list_add_tail(&cmd->list, &vscsi->active_q);
		spin_unlock_bh(&vscsi->पूर्णांकr_lock);

		srp_tsk->lun.scsi_lun[0] &= 0x3f;

		dev_dbg(&vscsi->dev, "calling submit_tmr, func %d\n",
			srp_tsk->tsk_mgmt_func);
		rc = target_submit_पंचांगr(&cmd->se_cmd, nexus->se_sess, शून्य,
				       scsilun_to_पूर्णांक(&srp_tsk->lun), srp_tsk,
				       tcm_type, GFP_KERNEL, tag_to_पात, 0);
		अगर (rc) अणु
			dev_err(&vscsi->dev, "target_submit_tmr failed, rc %d\n",
				rc);
			spin_lock_bh(&vscsi->पूर्णांकr_lock);
			list_del(&cmd->list);
			spin_unlock_bh(&vscsi->पूर्णांकr_lock);
			cmd->se_cmd.se_पंचांगr_req->response =
				TMR_FUNCTION_REJECTED;
		पूर्ण
	पूर्ण

	अगर (rc)
		transport_send_check_condition_and_sense(&cmd->se_cmd, 0, 0);
पूर्ण

अटल व्योम ibmvscsis_scheduler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ibmvscsis_cmd *cmd = container_of(work, काष्ठा ibmvscsis_cmd,
						 work);
	काष्ठा scsi_info *vscsi = cmd->adapter;

	spin_lock_bh(&vscsi->पूर्णांकr_lock);

	/* Remove from schedule_q */
	list_del(&cmd->list);

	/* Don't submit cmd if we're disconnecting */
	अगर (vscsi->flags & (SCHEDULE_DISCONNECT | DISCONNECT_SCHEDULED)) अणु
		ibmvscsis_मुक्त_cmd_resources(vscsi, cmd);

		/* ibmvscsis_disconnect might be रुकोing क्रम us */
		अगर (list_empty(&vscsi->active_q) &&
		    list_empty(&vscsi->schedule_q) &&
		    (vscsi->flags & WAIT_FOR_IDLE)) अणु
			vscsi->flags &= ~WAIT_FOR_IDLE;
			complete(&vscsi->रुको_idle);
		पूर्ण

		spin_unlock_bh(&vscsi->पूर्णांकr_lock);
		वापस;
	पूर्ण

	spin_unlock_bh(&vscsi->पूर्णांकr_lock);

	चयन (cmd->type) अणु
	हाल SCSI_CDB:
		ibmvscsis_parse_cmd(vscsi, cmd);
		अवरोध;
	हाल TASK_MANAGEMENT:
		ibmvscsis_parse_task(vscsi, cmd);
		अवरोध;
	शेष:
		dev_err(&vscsi->dev, "scheduler, invalid cmd type %d\n",
			cmd->type);
		spin_lock_bh(&vscsi->पूर्णांकr_lock);
		ibmvscsis_मुक्त_cmd_resources(vscsi, cmd);
		spin_unlock_bh(&vscsi->पूर्णांकr_lock);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ibmvscsis_alloc_cmds(काष्ठा scsi_info *vscsi, पूर्णांक num)
अणु
	काष्ठा ibmvscsis_cmd *cmd;
	पूर्णांक i;

	INIT_LIST_HEAD(&vscsi->मुक्त_cmd);
	vscsi->cmd_pool = kसुस्मृति(num, माप(काष्ठा ibmvscsis_cmd),
				  GFP_KERNEL);
	अगर (!vscsi->cmd_pool)
		वापस -ENOMEM;

	क्रम (i = 0, cmd = (काष्ठा ibmvscsis_cmd *)vscsi->cmd_pool; i < num;
	     i++, cmd++) अणु
		cmd->पात_cmd = शून्य;
		cmd->adapter = vscsi;
		INIT_WORK(&cmd->work, ibmvscsis_scheduler);
		list_add_tail(&cmd->list, &vscsi->मुक्त_cmd);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ibmvscsis_मुक्त_cmds(काष्ठा scsi_info *vscsi)
अणु
	kमुक्त(vscsi->cmd_pool);
	vscsi->cmd_pool = शून्य;
	INIT_LIST_HEAD(&vscsi->मुक्त_cmd);
पूर्ण

/**
 * ibmvscsis_service_रुको_q() - Service Waiting Queue
 * @समयr:	Poपूर्णांकer to समयr which has expired
 *
 * This routine is called when the समयr pops to service the रुकोing
 * queue. Elements on the queue have completed, their responses have been
 * copied to the client, but the client's response queue was full so
 * the queue message could not be sent. The routine grअसल the proper locks
 * and calls send messages.
 *
 * EXECUTION ENVIRONMENT:
 *	called at पूर्णांकerrupt level
 */
अटल क्रमागत hrसमयr_restart ibmvscsis_service_रुको_q(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा समयr_cb *p_समयr = container_of(समयr, काष्ठा समयr_cb, समयr);
	काष्ठा scsi_info *vscsi = container_of(p_समयr, काष्ठा scsi_info,
					       rsp_q_समयr);

	spin_lock_bh(&vscsi->पूर्णांकr_lock);
	p_समयr->समयr_pops += 1;
	p_समयr->started = false;
	ibmvscsis_send_messages(vscsi);
	spin_unlock_bh(&vscsi->पूर्णांकr_lock);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल दीर्घ ibmvscsis_alloस_समयr(काष्ठा scsi_info *vscsi)
अणु
	काष्ठा समयr_cb *p_समयr;

	p_समयr = &vscsi->rsp_q_समयr;
	hrसमयr_init(&p_समयr->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);

	p_समयr->समयr.function = ibmvscsis_service_रुको_q;
	p_समयr->started = false;
	p_समयr->समयr_pops = 0;

	वापस ADAPT_SUCCESS;
पूर्ण

अटल व्योम ibmvscsis_मुक्तसमयr(काष्ठा scsi_info *vscsi)
अणु
	काष्ठा समयr_cb *p_समयr;

	p_समयr = &vscsi->rsp_q_समयr;

	(व्योम)hrसमयr_cancel(&p_समयr->समयr);

	p_समयr->started = false;
	p_समयr->समयr_pops = 0;
पूर्ण

अटल irqवापस_t ibmvscsis_पूर्णांकerrupt(पूर्णांक dummy, व्योम *data)
अणु
	काष्ठा scsi_info *vscsi = data;

	vio_disable_पूर्णांकerrupts(vscsi->dma_dev);
	tasklet_schedule(&vscsi->work_task);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ibmvscsis_enable_change_state() - Set new state based on enabled status
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * This function determines our new state now that we are enabled.  This
 * may involve sending an Init Complete message to the client.
 *
 * Must be called with पूर्णांकerrupt lock held.
 */
अटल दीर्घ ibmvscsis_enable_change_state(काष्ठा scsi_info *vscsi)
अणु
	पूर्णांक bytes;
	दीर्घ rc = ADAPT_SUCCESS;

	bytes = vscsi->cmd_q.size * PAGE_SIZE;
	rc = h_reg_crq(vscsi->dds.unit_id, vscsi->cmd_q.crq_token, bytes);
	अगर (rc == H_CLOSED || rc == H_SUCCESS) अणु
		vscsi->state = WAIT_CONNECTION;
		rc = ibmvscsis_establish_new_q(vscsi);
	पूर्ण

	अगर (rc != ADAPT_SUCCESS) अणु
		vscsi->state = ERR_DISCONNECTED;
		vscsi->flags |= RESPONSE_Q_DOWN;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ibmvscsis_create_command_q() - Create Command Queue
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @num_cmds:	Currently unused.  In the future, may be used to determine
 *		the size of the CRQ.
 *
 * Allocates memory क्रम command queue maps remote memory पूर्णांकo an ioba
 * initializes the command response queue
 *
 * EXECUTION ENVIRONMENT:
 *	Process level only
 */
अटल दीर्घ ibmvscsis_create_command_q(काष्ठा scsi_info *vscsi, पूर्णांक num_cmds)
अणु
	पूर्णांक pages;
	काष्ठा vio_dev *vdev = vscsi->dma_dev;

	/* We might support multiple pages in the future, but just 1 क्रम now */
	pages = 1;

	vscsi->cmd_q.size = pages;

	vscsi->cmd_q.base_addr =
		(काष्ठा viosrp_crq *)get_zeroed_page(GFP_KERNEL);
	अगर (!vscsi->cmd_q.base_addr)
		वापस -ENOMEM;

	vscsi->cmd_q.mask = ((uपूर्णांक)pages * CRQ_PER_PAGE) - 1;

	vscsi->cmd_q.crq_token = dma_map_single(&vdev->dev,
						vscsi->cmd_q.base_addr,
						PAGE_SIZE, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(&vdev->dev, vscsi->cmd_q.crq_token)) अणु
		मुक्त_page((अचिन्हित दीर्घ)vscsi->cmd_q.base_addr);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ibmvscsis_destroy_command_q - Destroy Command Queue
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * Releases memory क्रम command queue and unmaps mapped remote memory.
 *
 * EXECUTION ENVIRONMENT:
 *	Process level only
 */
अटल व्योम ibmvscsis_destroy_command_q(काष्ठा scsi_info *vscsi)
अणु
	dma_unmap_single(&vscsi->dma_dev->dev, vscsi->cmd_q.crq_token,
			 PAGE_SIZE, DMA_BIसूचीECTIONAL);
	मुक्त_page((अचिन्हित दीर्घ)vscsi->cmd_q.base_addr);
	vscsi->cmd_q.base_addr = शून्य;
	vscsi->state = NO_QUEUE;
पूर्ण

अटल u8 ibmvscsis_fast_fail(काष्ठा scsi_info *vscsi,
			      काष्ठा ibmvscsis_cmd *cmd)
अणु
	काष्ठा iu_entry *iue = cmd->iue;
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	काष्ठा srp_cmd *srp = (काष्ठा srp_cmd *)iue->sbuf->buf;
	काष्ठा scsi_sense_hdr sshdr;
	u8 rc = se_cmd->scsi_status;

	अगर (vscsi->fast_fail && (READ_CMD(srp->cdb) || WRITE_CMD(srp->cdb)))
		अगर (scsi_normalize_sense(se_cmd->sense_buffer,
					 se_cmd->scsi_sense_length, &sshdr))
			अगर (sshdr.sense_key == HARDWARE_ERROR &&
			    (se_cmd->residual_count == 0 ||
			     se_cmd->residual_count == se_cmd->data_length)) अणु
				rc = NO_SENSE;
				cmd->flags |= CMD_FAST_FAIL;
			पूर्ण

	वापस rc;
पूर्ण

/**
 * srp_build_response() - Build an SRP response buffer
 * @vscsi:	Poपूर्णांकer to our adapter काष्ठाure
 * @cmd:	Poपूर्णांकer to command क्रम which to send the response
 * @len_p:	Where to वापस the length of the IU response sent.  This
 *		is needed to स्थिरruct the CRQ response.
 *
 * Build the SRP response buffer and copy it to the client's memory space.
 */
अटल दीर्घ srp_build_response(काष्ठा scsi_info *vscsi,
			       काष्ठा ibmvscsis_cmd *cmd, uपूर्णांक *len_p)
अणु
	काष्ठा iu_entry *iue = cmd->iue;
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	काष्ठा srp_rsp *rsp;
	uपूर्णांक len;
	u32 rsp_code;
	अक्षर *data;
	u32 *tsk_status;
	दीर्घ rc = ADAPT_SUCCESS;

	spin_lock_bh(&vscsi->पूर्णांकr_lock);

	rsp = &vio_iu(iue)->srp.rsp;
	len = माप(*rsp);
	स_रखो(rsp, 0, len);
	data = rsp->data;

	rsp->opcode = SRP_RSP;

	rsp->req_lim_delta = cpu_to_be32(1 + vscsi->credit);
	rsp->tag = cmd->rsp.tag;
	rsp->flags = 0;

	अगर (cmd->type == SCSI_CDB) अणु
		rsp->status = ibmvscsis_fast_fail(vscsi, cmd);
		अगर (rsp->status) अणु
			dev_dbg(&vscsi->dev, "build_resp: cmd %p, scsi status %d\n",
				cmd, (पूर्णांक)rsp->status);
			ibmvscsis_determine_resid(se_cmd, rsp);
			अगर (se_cmd->scsi_sense_length && se_cmd->sense_buffer) अणु
				rsp->sense_data_len =
					cpu_to_be32(se_cmd->scsi_sense_length);
				rsp->flags |= SRP_RSP_FLAG_SNSVALID;
				len += se_cmd->scsi_sense_length;
				स_नकल(data, se_cmd->sense_buffer,
				       se_cmd->scsi_sense_length);
			पूर्ण
			rsp->sol_not = (cmd->rsp.sol_not & UCSOLNT) >>
				UCSOLNT_RESP_SHIFT;
		पूर्ण अन्यथा अगर (cmd->flags & CMD_FAST_FAIL) अणु
			dev_dbg(&vscsi->dev, "build_resp: cmd %p, fast fail\n",
				cmd);
			rsp->sol_not = (cmd->rsp.sol_not & UCSOLNT) >>
				UCSOLNT_RESP_SHIFT;
		पूर्ण अन्यथा अणु
			rsp->sol_not = (cmd->rsp.sol_not & SCSOLNT) >>
				SCSOLNT_RESP_SHIFT;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* this is task management */
		rsp->status = 0;
		rsp->resp_data_len = cpu_to_be32(4);
		rsp->flags |= SRP_RSP_FLAG_RSPVALID;

		चयन (se_cmd->se_पंचांगr_req->response) अणु
		हाल TMR_FUNCTION_COMPLETE:
		हाल TMR_TASK_DOES_NOT_EXIST:
			rsp_code = SRP_TASK_MANAGEMENT_FUNCTION_COMPLETE;
			rsp->sol_not = (cmd->rsp.sol_not & SCSOLNT) >>
				SCSOLNT_RESP_SHIFT;
			अवरोध;
		हाल TMR_TASK_MGMT_FUNCTION_NOT_SUPPORTED:
		हाल TMR_LUN_DOES_NOT_EXIST:
			rsp_code = SRP_TASK_MANAGEMENT_FUNCTION_NOT_SUPPORTED;
			rsp->sol_not = (cmd->rsp.sol_not & UCSOLNT) >>
				UCSOLNT_RESP_SHIFT;
			अवरोध;
		हाल TMR_FUNCTION_FAILED:
		हाल TMR_FUNCTION_REJECTED:
		शेष:
			rsp_code = SRP_TASK_MANAGEMENT_FUNCTION_FAILED;
			rsp->sol_not = (cmd->rsp.sol_not & UCSOLNT) >>
				UCSOLNT_RESP_SHIFT;
			अवरोध;
		पूर्ण

		tsk_status = (u32 *)data;
		*tsk_status = cpu_to_be32(rsp_code);
		data = (अक्षर *)(tsk_status + 1);
		len += 4;
	पूर्ण

	dma_wmb();
	rc = h_copy_rdma(len, vscsi->dds.winकरोw[LOCAL].liobn, iue->sbuf->dma,
			 vscsi->dds.winकरोw[REMOTE].liobn,
			 be64_to_cpu(iue->remote_token));

	चयन (rc) अणु
	हाल H_SUCCESS:
		vscsi->credit = 0;
		*len_p = len;
		अवरोध;
	हाल H_PERMISSION:
		अगर (connection_broken(vscsi))
			vscsi->flags |= RESPONSE_Q_DOWN | CLIENT_FAILED;

		dev_err(&vscsi->dev, "build_response: error copying to client, rc %ld, flags 0x%x, state 0x%hx\n",
			rc, vscsi->flags, vscsi->state);
		अवरोध;
	हाल H_SOURCE_PARM:
	हाल H_DEST_PARM:
	शेष:
		dev_err(&vscsi->dev, "build_response: error copying to client, rc %ld\n",
			rc);
		अवरोध;
	पूर्ण

	spin_unlock_bh(&vscsi->पूर्णांकr_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक ibmvscsis_rdma(काष्ठा ibmvscsis_cmd *cmd, काष्ठा scatterlist *sg,
			  पूर्णांक nsg, काष्ठा srp_direct_buf *md, पूर्णांक nmd,
			  क्रमागत dma_data_direction dir, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा iu_entry *iue = cmd->iue;
	काष्ठा srp_target *target = iue->target;
	काष्ठा scsi_info *vscsi = target->ldata;
	काष्ठा scatterlist *sgp;
	dma_addr_t client_ioba, server_ioba;
	uदीर्घ buf_len;
	uदीर्घ client_len, server_len;
	पूर्णांक md_idx;
	दीर्घ tx_len;
	दीर्घ rc = 0;

	अगर (bytes == 0)
		वापस 0;

	sgp = sg;
	client_len = 0;
	server_len = 0;
	md_idx = 0;
	tx_len = bytes;

	करो अणु
		अगर (client_len == 0) अणु
			अगर (md_idx >= nmd) अणु
				dev_err(&vscsi->dev, "rdma: ran out of client memory descriptors\n");
				rc = -EIO;
				अवरोध;
			पूर्ण
			client_ioba = be64_to_cpu(md[md_idx].va);
			client_len = be32_to_cpu(md[md_idx].len);
		पूर्ण
		अगर (server_len == 0) अणु
			अगर (!sgp) अणु
				dev_err(&vscsi->dev, "rdma: ran out of scatter/gather list\n");
				rc = -EIO;
				अवरोध;
			पूर्ण
			server_ioba = sg_dma_address(sgp);
			server_len = sg_dma_len(sgp);
		पूर्ण

		buf_len = tx_len;

		अगर (buf_len > client_len)
			buf_len = client_len;

		अगर (buf_len > server_len)
			buf_len = server_len;

		अगर (buf_len > max_vdma_size)
			buf_len = max_vdma_size;

		अगर (dir == DMA_TO_DEVICE) अणु
			/* पढ़ो from client */
			rc = h_copy_rdma(buf_len,
					 vscsi->dds.winकरोw[REMOTE].liobn,
					 client_ioba,
					 vscsi->dds.winकरोw[LOCAL].liobn,
					 server_ioba);
		पूर्ण अन्यथा अणु
			/* The h_copy_rdma will cause phyp, running in another
			 * partition, to पढ़ो memory, so we need to make sure
			 * the data has been written out, hence these syncs.
			 */
			/* ensure that everything is in memory */
			isync();
			/* ensure that memory has been made visible */
			dma_wmb();
			rc = h_copy_rdma(buf_len,
					 vscsi->dds.winकरोw[LOCAL].liobn,
					 server_ioba,
					 vscsi->dds.winकरोw[REMOTE].liobn,
					 client_ioba);
		पूर्ण
		चयन (rc) अणु
		हाल H_SUCCESS:
			अवरोध;
		हाल H_PERMISSION:
		हाल H_SOURCE_PARM:
		हाल H_DEST_PARM:
			अगर (connection_broken(vscsi)) अणु
				spin_lock_bh(&vscsi->पूर्णांकr_lock);
				vscsi->flags |=
					(RESPONSE_Q_DOWN | CLIENT_FAILED);
				spin_unlock_bh(&vscsi->पूर्णांकr_lock);
			पूर्ण
			dev_err(&vscsi->dev, "rdma: h_copy_rdma failed, rc %ld\n",
				rc);
			अवरोध;

		शेष:
			dev_err(&vscsi->dev, "rdma: unknown error %ld from h_copy_rdma\n",
				rc);
			अवरोध;
		पूर्ण

		अगर (!rc) अणु
			tx_len -= buf_len;
			अगर (tx_len) अणु
				client_len -= buf_len;
				अगर (client_len == 0)
					md_idx++;
				अन्यथा
					client_ioba += buf_len;

				server_len -= buf_len;
				अगर (server_len == 0)
					sgp = sg_next(sgp);
				अन्यथा
					server_ioba += buf_len;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (!rc);

	वापस rc;
पूर्ण

/**
 * ibmvscsis_handle_crq() - Handle CRQ
 * @data:	Poपूर्णांकer to our adapter काष्ठाure
 *
 * Read the command elements from the command queue and copy the payloads
 * associated with the command elements to local memory and execute the
 * SRP requests.
 *
 * Note: this is an edge triggered पूर्णांकerrupt. It can not be shared.
 */
अटल व्योम ibmvscsis_handle_crq(अचिन्हित दीर्घ data)
अणु
	काष्ठा scsi_info *vscsi = (काष्ठा scsi_info *)data;
	काष्ठा viosrp_crq *crq;
	दीर्घ rc;
	bool ack = true;
	अस्थिर u8 valid;

	spin_lock_bh(&vscsi->पूर्णांकr_lock);

	dev_dbg(&vscsi->dev, "got interrupt\n");

	/*
	 * अगर we are in a path where we are रुकोing क्रम all pending commands
	 * to complete because we received a transport event and anything in
	 * the command queue is क्रम a new connection, करो nothing
	 */
	अगर (TARGET_STOP(vscsi)) अणु
		vio_enable_पूर्णांकerrupts(vscsi->dma_dev);

		dev_dbg(&vscsi->dev, "handle_crq, don't process: flags 0x%x, state 0x%hx\n",
			vscsi->flags, vscsi->state);
		spin_unlock_bh(&vscsi->पूर्णांकr_lock);
		वापस;
	पूर्ण

	rc = vscsi->flags & SCHEDULE_DISCONNECT;
	crq = vscsi->cmd_q.base_addr + vscsi->cmd_q.index;
	valid = crq->valid;
	dma_rmb();

	जबतक (valid) अणु
		/*
		 * These are edege triggered पूर्णांकerrupts. After dropping out of
		 * the जबतक loop, the code must check क्रम work since an
		 * पूर्णांकerrupt could be lost, and an elment be left on the queue,
		 * hence the label.
		 */
cmd_work:
		vscsi->cmd_q.index =
			(vscsi->cmd_q.index + 1) & vscsi->cmd_q.mask;

		अगर (!rc) अणु
			rc = ibmvscsis_parse_command(vscsi, crq);
		पूर्ण अन्यथा अणु
			अगर ((uपूर्णांक)crq->valid == VALID_TRANS_EVENT) अणु
				/*
				 * must service the transport layer events even
				 * in an error state, करोnt अवरोध out until all
				 * the consecutive transport events have been
				 * processed
				 */
				rc = ibmvscsis_trans_event(vscsi, crq);
			पूर्ण अन्यथा अगर (vscsi->flags & TRANS_EVENT) अणु
				/*
				 * अगर a transport event has occurred leave
				 * everything but transport events on the queue
				 *
				 * need to decrement the queue index so we can
				 * look at the element again
				 */
				अगर (vscsi->cmd_q.index)
					vscsi->cmd_q.index -= 1;
				अन्यथा
					/*
					 * index is at 0 it just wrapped.
					 * have it index last element in q
					 */
					vscsi->cmd_q.index = vscsi->cmd_q.mask;
				अवरोध;
			पूर्ण
		पूर्ण

		crq->valid = INVALIDATE_CMD_RESP_EL;

		crq = vscsi->cmd_q.base_addr + vscsi->cmd_q.index;
		valid = crq->valid;
		dma_rmb();
	पूर्ण

	अगर (!rc) अणु
		अगर (ack) अणु
			vio_enable_पूर्णांकerrupts(vscsi->dma_dev);
			ack = false;
			dev_dbg(&vscsi->dev, "handle_crq, reenabling interrupts\n");
		पूर्ण
		valid = crq->valid;
		dma_rmb();
		अगर (valid)
			जाओ cmd_work;
	पूर्ण अन्यथा अणु
		dev_dbg(&vscsi->dev, "handle_crq, error: flags 0x%x, state 0x%hx, crq index 0x%x\n",
			vscsi->flags, vscsi->state, vscsi->cmd_q.index);
	पूर्ण

	dev_dbg(&vscsi->dev, "Leaving handle_crq: schedule_q empty %d, flags 0x%x, state 0x%hx\n",
		(पूर्णांक)list_empty(&vscsi->schedule_q), vscsi->flags,
		vscsi->state);

	spin_unlock_bh(&vscsi->पूर्णांकr_lock);
पूर्ण

अटल पूर्णांक ibmvscsis_probe(काष्ठा vio_dev *vdev,
			   स्थिर काष्ठा vio_device_id *id)
अणु
	काष्ठा scsi_info *vscsi;
	पूर्णांक rc = 0;
	दीर्घ hrc = 0;
	अक्षर wq_name[24];

	vscsi = kzalloc(माप(*vscsi), GFP_KERNEL);
	अगर (!vscsi) अणु
		rc = -ENOMEM;
		dev_err(&vdev->dev, "probe: allocation of adapter failed\n");
		वापस rc;
	पूर्ण

	vscsi->dma_dev = vdev;
	vscsi->dev = vdev->dev;
	INIT_LIST_HEAD(&vscsi->schedule_q);
	INIT_LIST_HEAD(&vscsi->रुकोing_rsp);
	INIT_LIST_HEAD(&vscsi->active_q);

	snम_लिखो(vscsi->tport.tport_name, IBMVSCSIS_NAMELEN, "%s",
		 dev_name(&vdev->dev));

	dev_dbg(&vscsi->dev, "probe tport_name: %s\n", vscsi->tport.tport_name);

	rc = पढ़ो_dma_winकरोw(vscsi);
	अगर (rc)
		जाओ मुक्त_adapter;
	dev_dbg(&vscsi->dev, "Probe: liobn 0x%x, riobn 0x%x\n",
		vscsi->dds.winकरोw[LOCAL].liobn,
		vscsi->dds.winकरोw[REMOTE].liobn);

	snम_लिखो(vscsi->eye, माप(vscsi->eye), "VSCSI %s", vdev->name);

	vscsi->dds.unit_id = vdev->unit_address;
	strscpy(vscsi->dds.partition_name, partition_name,
		माप(vscsi->dds.partition_name));
	vscsi->dds.partition_num = partition_number;

	spin_lock_bh(&ibmvscsis_dev_lock);
	list_add_tail(&vscsi->list, &ibmvscsis_dev_list);
	spin_unlock_bh(&ibmvscsis_dev_lock);

	/*
	 * TBD: How करो we determine # of cmds to request?  Do we know how
	 * many "children" we have?
	 */
	vscsi->request_limit = INITIAL_SRP_LIMIT;
	rc = srp_target_alloc(&vscsi->target, &vdev->dev, vscsi->request_limit,
			      SRP_MAX_IU_LEN);
	अगर (rc)
		जाओ rem_list;

	vscsi->target.ldata = vscsi;

	rc = ibmvscsis_alloc_cmds(vscsi, vscsi->request_limit);
	अगर (rc) अणु
		dev_err(&vscsi->dev, "alloc_cmds failed, rc %d, num %d\n",
			rc, vscsi->request_limit);
		जाओ मुक्त_target;
	पूर्ण

	/*
	 * Note: the lock is used in मुक्तing समयrs, so must initialize
	 * first so that ordering in हाल of error is correct.
	 */
	spin_lock_init(&vscsi->पूर्णांकr_lock);

	rc = ibmvscsis_alloस_समयr(vscsi);
	अगर (rc) अणु
		dev_err(&vscsi->dev, "probe: alloctimer failed, rc %d\n", rc);
		जाओ मुक्त_cmds;
	पूर्ण

	rc = ibmvscsis_create_command_q(vscsi, 256);
	अगर (rc) अणु
		dev_err(&vscsi->dev, "probe: create_command_q failed, rc %d\n",
			rc);
		जाओ मुक्त_समयr;
	पूर्ण

	vscsi->map_buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	अगर (!vscsi->map_buf) अणु
		rc = -ENOMEM;
		dev_err(&vscsi->dev, "probe: allocating cmd buffer failed\n");
		जाओ destroy_queue;
	पूर्ण

	vscsi->map_ioba = dma_map_single(&vdev->dev, vscsi->map_buf, PAGE_SIZE,
					 DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(&vdev->dev, vscsi->map_ioba)) अणु
		rc = -ENOMEM;
		dev_err(&vscsi->dev, "probe: error mapping command buffer\n");
		जाओ मुक्त_buf;
	पूर्ण

	hrc = h_vioctl(vscsi->dds.unit_id, H_GET_PARTNER_INFO,
		       (u64)vscsi->map_ioba | ((u64)PAGE_SIZE << 32), 0, 0, 0,
		       0);
	अगर (hrc == H_SUCCESS)
		vscsi->client_data.partition_number =
			be64_to_cpu(*(u64 *)vscsi->map_buf);
	/*
	 * We expect the VIOCTL to fail अगर we're configured as "any
	 * client can connect" and the client isn't activated yet.
	 * We'll make the call again when he sends an init msg.
	 */
	dev_dbg(&vscsi->dev, "probe hrc %ld, client partition num %d\n",
		hrc, vscsi->client_data.partition_number);

	tasklet_init(&vscsi->work_task, ibmvscsis_handle_crq,
		     (अचिन्हित दीर्घ)vscsi);

	init_completion(&vscsi->रुको_idle);
	init_completion(&vscsi->unconfig);

	snम_लिखो(wq_name, 24, "ibmvscsis%s", dev_name(&vdev->dev));
	vscsi->work_q = create_workqueue(wq_name);
	अगर (!vscsi->work_q) अणु
		rc = -ENOMEM;
		dev_err(&vscsi->dev, "create_workqueue failed\n");
		जाओ unmap_buf;
	पूर्ण

	rc = request_irq(vdev->irq, ibmvscsis_पूर्णांकerrupt, 0, "ibmvscsis", vscsi);
	अगर (rc) अणु
		rc = -EPERM;
		dev_err(&vscsi->dev, "probe: request_irq failed, rc %d\n", rc);
		जाओ destroy_WQ;
	पूर्ण

	vscsi->state = WAIT_ENABLED;

	dev_set_drvdata(&vdev->dev, vscsi);

	वापस 0;

destroy_WQ:
	destroy_workqueue(vscsi->work_q);
unmap_buf:
	dma_unmap_single(&vdev->dev, vscsi->map_ioba, PAGE_SIZE,
			 DMA_BIसूचीECTIONAL);
मुक्त_buf:
	kमुक्त(vscsi->map_buf);
destroy_queue:
	tasklet_समाप्त(&vscsi->work_task);
	ibmvscsis_unरेजिस्टर_command_q(vscsi);
	ibmvscsis_destroy_command_q(vscsi);
मुक्त_समयr:
	ibmvscsis_मुक्तसमयr(vscsi);
मुक्त_cmds:
	ibmvscsis_मुक्त_cmds(vscsi);
मुक्त_target:
	srp_target_मुक्त(&vscsi->target);
rem_list:
	spin_lock_bh(&ibmvscsis_dev_lock);
	list_del(&vscsi->list);
	spin_unlock_bh(&ibmvscsis_dev_lock);
मुक्त_adapter:
	kमुक्त(vscsi);

	वापस rc;
पूर्ण

अटल व्योम ibmvscsis_हटाओ(काष्ठा vio_dev *vdev)
अणु
	काष्ठा scsi_info *vscsi = dev_get_drvdata(&vdev->dev);

	dev_dbg(&vscsi->dev, "remove (%s)\n", dev_name(&vscsi->dma_dev->dev));

	spin_lock_bh(&vscsi->पूर्णांकr_lock);
	ibmvscsis_post_disconnect(vscsi, UNCONFIGURING, 0);
	vscsi->flags |= CFG_SLEEPING;
	spin_unlock_bh(&vscsi->पूर्णांकr_lock);
	रुको_क्रम_completion(&vscsi->unconfig);

	vio_disable_पूर्णांकerrupts(vdev);
	मुक्त_irq(vdev->irq, vscsi);
	destroy_workqueue(vscsi->work_q);
	dma_unmap_single(&vdev->dev, vscsi->map_ioba, PAGE_SIZE,
			 DMA_BIसूचीECTIONAL);
	kमुक्त(vscsi->map_buf);
	tasklet_समाप्त(&vscsi->work_task);
	ibmvscsis_destroy_command_q(vscsi);
	ibmvscsis_मुक्तसमयr(vscsi);
	ibmvscsis_मुक्त_cmds(vscsi);
	srp_target_मुक्त(&vscsi->target);
	spin_lock_bh(&ibmvscsis_dev_lock);
	list_del(&vscsi->list);
	spin_unlock_bh(&ibmvscsis_dev_lock);
	kमुक्त(vscsi);
पूर्ण

अटल sमाप_प्रकार प्रणाली_id_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", प्रणाली_id);
पूर्ण

अटल sमाप_प्रकार partition_number_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%x\n", partition_number);
पूर्ण

अटल sमाप_प्रकार unit_address_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_info *vscsi = container_of(dev, काष्ठा scsi_info, dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%x\n", vscsi->dma_dev->unit_address);
पूर्ण

अटल पूर्णांक ibmvscsis_get_प्रणाली_info(व्योम)
अणु
	काष्ठा device_node *rootdn, *vdevdn;
	स्थिर अक्षर *id, *model, *name;
	स्थिर uपूर्णांक *num;

	rootdn = of_find_node_by_path("/");
	अगर (!rootdn)
		वापस -ENOENT;

	model = of_get_property(rootdn, "model", शून्य);
	id = of_get_property(rootdn, "system-id", शून्य);
	अगर (model && id)
		snम_लिखो(प्रणाली_id, माप(प्रणाली_id), "%s-%s", model, id);

	name = of_get_property(rootdn, "ibm,partition-name", शून्य);
	अगर (name)
		म_नकलन(partition_name, name, माप(partition_name));

	num = of_get_property(rootdn, "ibm,partition-no", शून्य);
	अगर (num)
		partition_number = of_पढ़ो_number(num, 1);

	of_node_put(rootdn);

	vdevdn = of_find_node_by_path("/vdevice");
	अगर (vdevdn) अणु
		स्थिर uपूर्णांक *mvds;

		mvds = of_get_property(vdevdn, "ibm,max-virtual-dma-size",
				       शून्य);
		अगर (mvds)
			max_vdma_size = *mvds;
		of_node_put(vdevdn);
	पूर्ण

	वापस 0;
पूर्ण

अटल अक्षर *ibmvscsis_get_fabric_wwn(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा ibmvscsis_tport *tport =
		container_of(se_tpg, काष्ठा ibmvscsis_tport, se_tpg);

	वापस tport->tport_name;
पूर्ण

अटल u16 ibmvscsis_get_tag(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा ibmvscsis_tport *tport =
		container_of(se_tpg, काष्ठा ibmvscsis_tport, se_tpg);

	वापस tport->tport_tpgt;
पूर्ण

अटल u32 ibmvscsis_get_शेष_depth(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक ibmvscsis_check_true(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक ibmvscsis_check_false(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 0;
पूर्ण

अटल u32 ibmvscsis_tpg_get_inst_index(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक ibmvscsis_check_stop_मुक्त(काष्ठा se_cmd *se_cmd)
अणु
	वापस target_put_sess_cmd(se_cmd);
पूर्ण

अटल व्योम ibmvscsis_release_cmd(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा ibmvscsis_cmd *cmd = container_of(se_cmd, काष्ठा ibmvscsis_cmd,
						 se_cmd);
	काष्ठा scsi_info *vscsi = cmd->adapter;

	spin_lock_bh(&vscsi->पूर्णांकr_lock);
	/* Remove from active_q */
	list_move_tail(&cmd->list, &vscsi->रुकोing_rsp);
	ibmvscsis_send_messages(vscsi);
	spin_unlock_bh(&vscsi->पूर्णांकr_lock);
पूर्ण

अटल u32 ibmvscsis_sess_get_index(काष्ठा se_session *se_sess)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ibmvscsis_ग_लिखो_pending(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा ibmvscsis_cmd *cmd = container_of(se_cmd, काष्ठा ibmvscsis_cmd,
						 se_cmd);
	काष्ठा scsi_info *vscsi = cmd->adapter;
	काष्ठा iu_entry *iue = cmd->iue;
	पूर्णांक rc;

	/*
	 * If CLIENT_FAILED OR RESPONSE_Q_DOWN, then just वापस success
	 * since LIO can't करो anything about it, and we करोnt want to
	 * attempt an srp_transfer_data.
	 */
	अगर ((vscsi->flags & (CLIENT_FAILED | RESPONSE_Q_DOWN))) अणु
		dev_err(&vscsi->dev, "write_pending failed since: %d\n",
			vscsi->flags);
		वापस -EIO;

	पूर्ण

	rc = srp_transfer_data(cmd, &vio_iu(iue)->srp.cmd, ibmvscsis_rdma,
			       1, 1);
	अगर (rc) अणु
		dev_err(&vscsi->dev, "srp_transfer_data() failed: %d\n", rc);
		वापस -EIO;
	पूर्ण
	/*
	 * We now tell TCM to add this WRITE CDB directly पूर्णांकo the TCM storage
	 * object execution queue.
	 */
	target_execute_cmd(se_cmd);
	वापस 0;
पूर्ण

अटल व्योम ibmvscsis_set_शेष_node_attrs(काष्ठा se_node_acl *nacl)
अणु
पूर्ण

अटल पूर्णांक ibmvscsis_get_cmd_state(काष्ठा se_cmd *se_cmd)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ibmvscsis_queue_data_in(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा ibmvscsis_cmd *cmd = container_of(se_cmd, काष्ठा ibmvscsis_cmd,
						 se_cmd);
	काष्ठा iu_entry *iue = cmd->iue;
	काष्ठा scsi_info *vscsi = cmd->adapter;
	uपूर्णांक len = 0;
	पूर्णांक rc;

	rc = srp_transfer_data(cmd, &vio_iu(iue)->srp.cmd, ibmvscsis_rdma, 1,
			       1);
	अगर (rc) अणु
		dev_err(&vscsi->dev, "srp_transfer_data failed: %d\n", rc);
		se_cmd->scsi_sense_length = 18;
		स_रखो(se_cmd->sense_buffer, 0, se_cmd->scsi_sense_length);
		/* Logical Unit Communication Time-out asc/ascq = 0x0801 */
		scsi_build_sense_buffer(0, se_cmd->sense_buffer, MEDIUM_ERROR,
					0x08, 0x01);
	पूर्ण

	srp_build_response(vscsi, cmd, &len);
	cmd->rsp.क्रमmat = SRP_FORMAT;
	cmd->rsp.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक ibmvscsis_queue_status(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा ibmvscsis_cmd *cmd = container_of(se_cmd, काष्ठा ibmvscsis_cmd,
						 se_cmd);
	काष्ठा scsi_info *vscsi = cmd->adapter;
	uपूर्णांक len;

	dev_dbg(&vscsi->dev, "queue_status %p\n", se_cmd);

	srp_build_response(vscsi, cmd, &len);
	cmd->rsp.क्रमmat = SRP_FORMAT;
	cmd->rsp.len = len;

	वापस 0;
पूर्ण

अटल व्योम ibmvscsis_queue_पंचांग_rsp(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा ibmvscsis_cmd *cmd = container_of(se_cmd, काष्ठा ibmvscsis_cmd,
						 se_cmd);
	काष्ठा scsi_info *vscsi = cmd->adapter;
	काष्ठा ibmvscsis_cmd *cmd_itr;
	काष्ठा iu_entry *iue = iue = cmd->iue;
	काष्ठा srp_tsk_mgmt *srp_tsk = &vio_iu(iue)->srp.tsk_mgmt;
	u64 tag_to_पात = be64_to_cpu(srp_tsk->task_tag);
	uपूर्णांक len;

	dev_dbg(&vscsi->dev, "queue_tm_rsp %p, status %d\n",
		se_cmd, (पूर्णांक)se_cmd->se_पंचांगr_req->response);

	अगर (srp_tsk->tsk_mgmt_func == SRP_TSK_ABORT_TASK &&
	    cmd->se_cmd.se_पंचांगr_req->response == TMR_TASK_DOES_NOT_EXIST) अणु
		spin_lock_bh(&vscsi->पूर्णांकr_lock);
		list_क्रम_each_entry(cmd_itr, &vscsi->active_q, list) अणु
			अगर (tag_to_पात == cmd_itr->se_cmd.tag) अणु
				cmd_itr->पात_cmd = cmd;
				cmd->flags |= DELAY_SEND;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&vscsi->पूर्णांकr_lock);
	पूर्ण

	srp_build_response(vscsi, cmd, &len);
	cmd->rsp.क्रमmat = SRP_FORMAT;
	cmd->rsp.len = len;
पूर्ण

अटल व्योम ibmvscsis_पातed_task(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा ibmvscsis_cmd *cmd = container_of(se_cmd, काष्ठा ibmvscsis_cmd,
						 se_cmd);
	काष्ठा scsi_info *vscsi = cmd->adapter;

	dev_dbg(&vscsi->dev, "ibmvscsis_aborted_task %p task_tag: %llu\n",
		se_cmd, se_cmd->tag);
पूर्ण

अटल काष्ठा se_wwn *ibmvscsis_make_tport(काष्ठा target_fabric_configfs *tf,
					   काष्ठा config_group *group,
					   स्थिर अक्षर *name)
अणु
	काष्ठा ibmvscsis_tport *tport;
	काष्ठा scsi_info *vscsi;

	tport = ibmvscsis_lookup_port(name);
	अगर (tport) अणु
		vscsi = container_of(tport, काष्ठा scsi_info, tport);
		tport->tport_proto_id = SCSI_PROTOCOL_SRP;
		dev_dbg(&vscsi->dev, "make_tport(%s), pointer:%p, tport_id:%x\n",
			name, tport, tport->tport_proto_id);
		वापस &tport->tport_wwn;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल व्योम ibmvscsis_drop_tport(काष्ठा se_wwn *wwn)
अणु
	काष्ठा ibmvscsis_tport *tport = container_of(wwn,
						     काष्ठा ibmvscsis_tport,
						     tport_wwn);
	काष्ठा scsi_info *vscsi = container_of(tport, काष्ठा scsi_info, tport);

	dev_dbg(&vscsi->dev, "drop_tport(%s)\n",
		config_item_name(&tport->tport_wwn.wwn_group.cg_item));
पूर्ण

अटल काष्ठा se_portal_group *ibmvscsis_make_tpg(काष्ठा se_wwn *wwn,
						  स्थिर अक्षर *name)
अणु
	काष्ठा ibmvscsis_tport *tport =
		container_of(wwn, काष्ठा ibmvscsis_tport, tport_wwn);
	u16 tpgt;
	पूर्णांक rc;

	अगर (म_माला(name, "tpgt_") != name)
		वापस ERR_PTR(-EINVAL);
	rc = kstrtou16(name + 5, 0, &tpgt);
	अगर (rc)
		वापस ERR_PTR(rc);
	tport->tport_tpgt = tpgt;

	tport->releasing = false;

	rc = core_tpg_रेजिस्टर(&tport->tport_wwn, &tport->se_tpg,
			       tport->tport_proto_id);
	अगर (rc)
		वापस ERR_PTR(rc);

	वापस &tport->se_tpg;
पूर्ण

अटल व्योम ibmvscsis_drop_tpg(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा ibmvscsis_tport *tport = container_of(se_tpg,
						     काष्ठा ibmvscsis_tport,
						     se_tpg);

	tport->releasing = true;
	tport->enabled = false;

	/*
	 * Release the भव I_T Nexus क्रम this ibmvscsis TPG
	 */
	ibmvscsis_drop_nexus(tport);
	/*
	 * Deरेजिस्टर the se_tpg from TCM..
	 */
	core_tpg_deरेजिस्टर(se_tpg);
पूर्ण

अटल sमाप_प्रकार ibmvscsis_wwn_version_show(काष्ठा config_item *item,
					  अक्षर *page)
अणु
	वापस scnम_लिखो(page, PAGE_SIZE, "%s\n", IBMVSCSIS_VERSION);
पूर्ण
CONFIGFS_ATTR_RO(ibmvscsis_wwn_, version);

अटल काष्ठा configfs_attribute *ibmvscsis_wwn_attrs[] = अणु
	&ibmvscsis_wwn_attr_version,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार ibmvscsis_tpg_enable_show(काष्ठा config_item *item,
					 अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा ibmvscsis_tport *tport = container_of(se_tpg,
						     काष्ठा ibmvscsis_tport,
						     se_tpg);

	वापस snम_लिखो(page, PAGE_SIZE, "%d\n", (tport->enabled) ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार ibmvscsis_tpg_enable_store(काष्ठा config_item *item,
					  स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा ibmvscsis_tport *tport = container_of(se_tpg,
						     काष्ठा ibmvscsis_tport,
						     se_tpg);
	काष्ठा scsi_info *vscsi = container_of(tport, काष्ठा scsi_info, tport);
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक rc;
	दीर्घ lrc;

	rc = kम_से_अदीर्घ(page, 0, &पंचांगp);
	अगर (rc < 0) अणु
		dev_err(&vscsi->dev, "Unable to extract srpt_tpg_store_enable\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((पंचांगp != 0) && (पंचांगp != 1)) अणु
		dev_err(&vscsi->dev, "Illegal value for srpt_tpg_store_enable\n");
		वापस -EINVAL;
	पूर्ण

	अगर (पंचांगp) अणु
		spin_lock_bh(&vscsi->पूर्णांकr_lock);
		tport->enabled = true;
		lrc = ibmvscsis_enable_change_state(vscsi);
		अगर (lrc)
			dev_err(&vscsi->dev, "enable_change_state failed, rc %ld state %d\n",
				lrc, vscsi->state);
		spin_unlock_bh(&vscsi->पूर्णांकr_lock);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&vscsi->पूर्णांकr_lock);
		tport->enabled = false;
		/* This simulates the server going करोwn */
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT, 0);
		spin_unlock_bh(&vscsi->पूर्णांकr_lock);
	पूर्ण

	dev_dbg(&vscsi->dev, "tpg_enable_store, tmp %ld, state %d\n", पंचांगp,
		vscsi->state);

	वापस count;
पूर्ण
CONFIGFS_ATTR(ibmvscsis_tpg_, enable);

अटल काष्ठा configfs_attribute *ibmvscsis_tpg_attrs[] = अणु
	&ibmvscsis_tpg_attr_enable,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा target_core_fabric_ops ibmvscsis_ops = अणु
	.module				= THIS_MODULE,
	.fabric_name			= "ibmvscsis",
	.max_data_sg_nents		= MAX_TXU / PAGE_SIZE,
	.tpg_get_wwn			= ibmvscsis_get_fabric_wwn,
	.tpg_get_tag			= ibmvscsis_get_tag,
	.tpg_get_शेष_depth		= ibmvscsis_get_शेष_depth,
	.tpg_check_demo_mode		= ibmvscsis_check_true,
	.tpg_check_demo_mode_cache	= ibmvscsis_check_true,
	.tpg_check_demo_mode_ग_लिखो_protect = ibmvscsis_check_false,
	.tpg_check_prod_mode_ग_लिखो_protect = ibmvscsis_check_false,
	.tpg_get_inst_index		= ibmvscsis_tpg_get_inst_index,
	.check_stop_मुक्त		= ibmvscsis_check_stop_मुक्त,
	.release_cmd			= ibmvscsis_release_cmd,
	.sess_get_index			= ibmvscsis_sess_get_index,
	.ग_लिखो_pending			= ibmvscsis_ग_लिखो_pending,
	.set_शेष_node_attributes	= ibmvscsis_set_शेष_node_attrs,
	.get_cmd_state			= ibmvscsis_get_cmd_state,
	.queue_data_in			= ibmvscsis_queue_data_in,
	.queue_status			= ibmvscsis_queue_status,
	.queue_पंचांग_rsp			= ibmvscsis_queue_पंचांग_rsp,
	.पातed_task			= ibmvscsis_पातed_task,
	/*
	 * Setup function poपूर्णांकers क्रम logic in target_core_fabric_configfs.c
	 */
	.fabric_make_wwn		= ibmvscsis_make_tport,
	.fabric_drop_wwn		= ibmvscsis_drop_tport,
	.fabric_make_tpg		= ibmvscsis_make_tpg,
	.fabric_drop_tpg		= ibmvscsis_drop_tpg,

	.tfc_wwn_attrs			= ibmvscsis_wwn_attrs,
	.tfc_tpg_base_attrs		= ibmvscsis_tpg_attrs,
पूर्ण;

अटल व्योम ibmvscsis_dev_release(काष्ठा device *dev) अणुपूर्ण;

अटल काष्ठा device_attribute dev_attr_प्रणाली_id =
	__ATTR(प्रणाली_id, S_IRUGO, प्रणाली_id_show, शून्य);

अटल काष्ठा device_attribute dev_attr_partition_number =
	__ATTR(partition_number, S_IRUGO, partition_number_show, शून्य);

अटल काष्ठा device_attribute dev_attr_unit_address =
	__ATTR(unit_address, S_IRUGO, unit_address_show, शून्य);

अटल काष्ठा attribute *ibmvscsis_dev_attrs[] = अणु
	&dev_attr_प्रणाली_id.attr,
	&dev_attr_partition_number.attr,
	&dev_attr_unit_address.attr,
पूर्ण;
ATTRIBUTE_GROUPS(ibmvscsis_dev);

अटल काष्ठा class ibmvscsis_class = अणु
	.name		= "ibmvscsis",
	.dev_release	= ibmvscsis_dev_release,
	.dev_groups	= ibmvscsis_dev_groups,
पूर्ण;

अटल स्थिर काष्ठा vio_device_id ibmvscsis_device_table[] = अणु
	अणु "v-scsi-host", "IBM,v-scsi-host" पूर्ण,
	अणु "", "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(vio, ibmvscsis_device_table);

अटल काष्ठा vio_driver ibmvscsis_driver = अणु
	.name = "ibmvscsis",
	.id_table = ibmvscsis_device_table,
	.probe = ibmvscsis_probe,
	.हटाओ = ibmvscsis_हटाओ,
पूर्ण;

/*
 * ibmvscsis_init() - Kernel Module initialization
 *
 * Note: vio_रेजिस्टर_driver() रेजिस्टरs callback functions, and at least one
 * of those callback functions calls TCM - Linux IO Target Subप्रणाली, thus
 * the SCSI Target ढाँचा must be रेजिस्टरed beक्रमe vio_रेजिस्टर_driver()
 * is called.
 */
अटल पूर्णांक __init ibmvscsis_init(व्योम)
अणु
	पूर्णांक rc = 0;

	rc = ibmvscsis_get_प्रणाली_info();
	अगर (rc) अणु
		pr_err("rc %d from get_system_info\n", rc);
		जाओ out;
	पूर्ण

	rc = class_रेजिस्टर(&ibmvscsis_class);
	अगर (rc) अणु
		pr_err("failed class register\n");
		जाओ out;
	पूर्ण

	rc = target_रेजिस्टर_ढाँचा(&ibmvscsis_ops);
	अगर (rc) अणु
		pr_err("rc %d from target_register_template\n", rc);
		जाओ unरेजिस्टर_class;
	पूर्ण

	rc = vio_रेजिस्टर_driver(&ibmvscsis_driver);
	अगर (rc) अणु
		pr_err("rc %d from vio_register_driver\n", rc);
		जाओ unरेजिस्टर_target;
	पूर्ण

	वापस 0;

unरेजिस्टर_target:
	target_unरेजिस्टर_ढाँचा(&ibmvscsis_ops);
unरेजिस्टर_class:
	class_unरेजिस्टर(&ibmvscsis_class);
out:
	वापस rc;
पूर्ण

अटल व्योम __निकास ibmvscsis_निकास(व्योम)
अणु
	pr_info("Unregister IBM virtual SCSI host driver\n");
	vio_unरेजिस्टर_driver(&ibmvscsis_driver);
	target_unरेजिस्टर_ढाँचा(&ibmvscsis_ops);
	class_unरेजिस्टर(&ibmvscsis_class);
पूर्ण

MODULE_DESCRIPTION("IBMVSCSIS fabric driver");
MODULE_AUTHOR("Bryant G. Ly and Michael Cyr");
MODULE_LICENSE("GPL");
MODULE_VERSION(IBMVSCSIS_VERSION);
module_init(ibmvscsis_init);
module_निकास(ibmvscsis_निकास);
