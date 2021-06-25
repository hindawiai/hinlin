<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename:  target_core_पंचांगr.c
 *
 * This file contains SPC-3 task management infraकाष्ठाure
 *
 * (c) Copyright 2009-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 *
 ******************************************************************************/

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/export.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"
#समावेश "target_core_alua.h"
#समावेश "target_core_pr.h"

पूर्णांक core_पंचांगr_alloc_req(
	काष्ठा se_cmd *se_cmd,
	व्योम *fabric_पंचांगr_ptr,
	u8 function,
	gfp_t gfp_flags)
अणु
	काष्ठा se_पंचांगr_req *पंचांगr;

	पंचांगr = kzalloc(माप(काष्ठा se_पंचांगr_req), gfp_flags);
	अगर (!पंचांगr) अणु
		pr_err("Unable to allocate struct se_tmr_req\n");
		वापस -ENOMEM;
	पूर्ण

	se_cmd->se_cmd_flags |= SCF_SCSI_TMR_CDB;
	se_cmd->se_पंचांगr_req = पंचांगr;
	पंचांगr->task_cmd = se_cmd;
	पंचांगr->fabric_पंचांगr_ptr = fabric_पंचांगr_ptr;
	पंचांगr->function = function;
	INIT_LIST_HEAD(&पंचांगr->पंचांगr_list);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(core_पंचांगr_alloc_req);

व्योम core_पंचांगr_release_req(काष्ठा se_पंचांगr_req *पंचांगr)
अणु
	काष्ठा se_device *dev = पंचांगr->पंचांगr_dev;
	अचिन्हित दीर्घ flags;

	अगर (dev) अणु
		spin_lock_irqsave(&dev->se_पंचांगr_lock, flags);
		list_del_init(&पंचांगr->पंचांगr_list);
		spin_unlock_irqrestore(&dev->se_पंचांगr_lock, flags);
	पूर्ण

	kमुक्त(पंचांगr);
पूर्ण

अटल पूर्णांक target_check_cdb_and_preempt(काष्ठा list_head *list,
		काष्ठा se_cmd *cmd)
अणु
	काष्ठा t10_pr_registration *reg;

	अगर (!list)
		वापस 0;
	list_क्रम_each_entry(reg, list, pr_reg_पात_list) अणु
		अगर (reg->pr_res_key == cmd->pr_res_key)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल bool __target_check_io_state(काष्ठा se_cmd *se_cmd,
				    काष्ठा se_session *पंचांगr_sess, bool tas)
अणु
	काष्ठा se_session *sess = se_cmd->se_sess;

	निश्चित_spin_locked(&sess->sess_cmd_lock);
	WARN_ON_ONCE(!irqs_disabled());
	/*
	 * If command alपढ़ोy reached CMD_T_COMPLETE state within
	 * target_complete_cmd() or CMD_T_FABRIC_STOP due to shutकरोwn,
	 * this se_cmd has been passed to fabric driver and will
	 * not be पातed.
	 *
	 * Otherwise, obtain a local se_cmd->cmd_kref now क्रम TMR
	 * ABORT_TASK + LUN_RESET क्रम CMD_T_ABORTED processing as
	 * दीर्घ as se_cmd->cmd_kref is still active unless zero.
	 */
	spin_lock(&se_cmd->t_state_lock);
	अगर (se_cmd->transport_state & (CMD_T_COMPLETE | CMD_T_FABRIC_STOP)) अणु
		pr_debug("Attempted to abort io tag: %llu already complete or"
			" fabric stop, skipping\n", se_cmd->tag);
		spin_unlock(&se_cmd->t_state_lock);
		वापस false;
	पूर्ण
	se_cmd->transport_state |= CMD_T_ABORTED;

	अगर ((पंचांगr_sess != se_cmd->se_sess) && tas)
		se_cmd->transport_state |= CMD_T_TAS;

	spin_unlock(&se_cmd->t_state_lock);

	वापस kref_get_unless_zero(&se_cmd->cmd_kref);
पूर्ण

व्योम core_पंचांगr_पात_task(
	काष्ठा se_device *dev,
	काष्ठा se_पंचांगr_req *पंचांगr,
	काष्ठा se_session *se_sess)
अणु
	LIST_HEAD(पातed_list);
	काष्ठा se_cmd *se_cmd, *next;
	अचिन्हित दीर्घ flags;
	bool rc;
	u64 ref_tag;
	पूर्णांक i;

	क्रम (i = 0; i < dev->queue_cnt; i++) अणु
		flush_work(&dev->queues[i].sq.work);

		spin_lock_irqsave(&dev->queues[i].lock, flags);
		list_क्रम_each_entry_safe(se_cmd, next, &dev->queues[i].state_list,
					 state_list) अणु
			अगर (se_sess != se_cmd->se_sess)
				जारी;

			/*
			 * skip task management functions, including
			 * पंचांगr->task_cmd
			 */
			अगर (se_cmd->se_cmd_flags & SCF_SCSI_TMR_CDB)
				जारी;

			ref_tag = se_cmd->tag;
			अगर (पंचांगr->ref_task_tag != ref_tag)
				जारी;

			pr_err("ABORT_TASK: Found referenced %s task_tag: %llu\n",
			       se_cmd->se_tfo->fabric_name, ref_tag);

			spin_lock(&se_sess->sess_cmd_lock);
			rc = __target_check_io_state(se_cmd, se_sess, 0);
			spin_unlock(&se_sess->sess_cmd_lock);
			अगर (!rc)
				जारी;

			list_move_tail(&se_cmd->state_list, &पातed_list);
			se_cmd->state_active = false;
			spin_unlock_irqrestore(&dev->queues[i].lock, flags);

			/*
			 * Ensure that this ABORT request is visible to the LU
			 * RESET code.
			 */
			अगर (!पंचांगr->पंचांगr_dev)
				WARN_ON_ONCE(transport_lookup_पंचांगr_lun(पंचांगr->task_cmd) < 0);

			अगर (dev->transport->पंचांगr_notअगरy)
				dev->transport->पंचांगr_notअगरy(dev, TMR_ABORT_TASK,
							   &पातed_list);

			list_del_init(&se_cmd->state_list);
			target_put_cmd_and_रुको(se_cmd);

			pr_err("ABORT_TASK: Sending TMR_FUNCTION_COMPLETE for ref_tag: %llu\n",
			       ref_tag);
			पंचांगr->response = TMR_FUNCTION_COMPLETE;
			atomic_दीर्घ_inc(&dev->पातs_complete);
			वापस;
		पूर्ण
		spin_unlock_irqrestore(&dev->queues[i].lock, flags);
	पूर्ण

	अगर (dev->transport->पंचांगr_notअगरy)
		dev->transport->पंचांगr_notअगरy(dev, TMR_ABORT_TASK, &पातed_list);

	prपूर्णांकk("ABORT_TASK: Sending TMR_TASK_DOES_NOT_EXIST for ref_tag: %lld\n",
			पंचांगr->ref_task_tag);
	पंचांगr->response = TMR_TASK_DOES_NOT_EXIST;
	atomic_दीर्घ_inc(&dev->पातs_no_task);
पूर्ण

अटल व्योम core_पंचांगr_drain_पंचांगr_list(
	काष्ठा se_device *dev,
	काष्ठा se_पंचांगr_req *पंचांगr,
	काष्ठा list_head *preempt_and_पात_list)
अणु
	LIST_HEAD(drain_पंचांगr_list);
	काष्ठा se_session *sess;
	काष्ठा se_पंचांगr_req *पंचांगr_p, *पंचांगr_pp;
	काष्ठा se_cmd *cmd;
	अचिन्हित दीर्घ flags;
	bool rc;
	/*
	 * Release all pending and outgoing TMRs aside from the received
	 * LUN_RESET पंचांगr..
	 */
	spin_lock_irqsave(&dev->se_पंचांगr_lock, flags);
	अगर (पंचांगr)
		list_del_init(&पंचांगr->पंचांगr_list);
	list_क्रम_each_entry_safe(पंचांगr_p, पंचांगr_pp, &dev->dev_पंचांगr_list, पंचांगr_list) अणु
		cmd = पंचांगr_p->task_cmd;
		अगर (!cmd) अणु
			pr_err("Unable to locate struct se_cmd for TMR\n");
			जारी;
		पूर्ण
		/*
		 * If this function was called with a valid pr_res_key
		 * parameter (eg: क्रम PROUT PREEMPT_AND_ABORT service action
		 * skip non registration key matching TMRs.
		 */
		अगर (target_check_cdb_and_preempt(preempt_and_पात_list, cmd))
			जारी;

		sess = cmd->se_sess;
		अगर (WARN_ON_ONCE(!sess))
			जारी;

		spin_lock(&sess->sess_cmd_lock);
		rc = __target_check_io_state(cmd, sess, 0);
		spin_unlock(&sess->sess_cmd_lock);

		अगर (!rc) अणु
			prपूर्णांकk("LUN_RESET TMR: non-zero kref_get_unless_zero\n");
			जारी;
		पूर्ण

		list_move_tail(&पंचांगr_p->पंचांगr_list, &drain_पंचांगr_list);
	पूर्ण
	spin_unlock_irqrestore(&dev->se_पंचांगr_lock, flags);

	list_क्रम_each_entry_safe(पंचांगr_p, पंचांगr_pp, &drain_पंचांगr_list, पंचांगr_list) अणु
		list_del_init(&पंचांगr_p->पंचांगr_list);
		cmd = पंचांगr_p->task_cmd;

		pr_debug("LUN_RESET: %s releasing TMR %p Function: 0x%02x,"
			" Response: 0x%02x, t_state: %d\n",
			(preempt_and_पात_list) ? "Preempt" : "", पंचांगr_p,
			पंचांगr_p->function, पंचांगr_p->response, cmd->t_state);

		target_put_cmd_and_रुको(cmd);
	पूर्ण
पूर्ण

/**
 * core_पंचांगr_drain_state_list() - पात SCSI commands associated with a device
 *
 * @dev:       Device क्रम which to पात outstanding SCSI commands.
 * @prout_cmd: Poपूर्णांकer to the SCSI PREEMPT AND ABORT अगर this function is called
 *             to realize the PREEMPT AND ABORT functionality.
 * @पंचांगr_sess:  Session through which the LUN RESET has been received.
 * @tas:       Task Aborted Status (TAS) bit from the SCSI control mode page.
 *             A quote from SPC-4, paragraph "7.5.10 Control mode page":
 *             "A task पातed status (TAS) bit set to zero specअगरies that
 *             पातed commands shall be terminated by the device server
 *             without any response to the application client. A TAS bit set
 *             to one specअगरies that commands पातed by the actions of an I_T
 *             nexus other than the I_T nexus on which the command was
 *             received shall be completed with TASK ABORTED status."
 * @preempt_and_पात_list: For the PREEMPT AND ABORT functionality, a list
 *             with registrations that will be preempted.
 */
अटल व्योम core_पंचांगr_drain_state_list(
	काष्ठा se_device *dev,
	काष्ठा se_cmd *prout_cmd,
	काष्ठा se_session *पंचांगr_sess,
	bool tas,
	काष्ठा list_head *preempt_and_पात_list)
अणु
	LIST_HEAD(drain_task_list);
	काष्ठा se_session *sess;
	काष्ठा se_cmd *cmd, *next;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc, i;

	/*
	 * Complete outstanding commands with TASK_ABORTED SAM status.
	 *
	 * This is following sam4r17, section 5.6 Aborting commands, Table 38
	 * क्रम TMR LUN_RESET:
	 *
	 * a) "Yes" indicates that each command that is पातed on an I_T nexus
	 * other than the one that caused the SCSI device condition is
	 * completed with TASK ABORTED status, अगर the TAS bit is set to one in
	 * the Control mode page (see SPC-4). "No" indicates that no status is
	 * वापसed क्रम पातed commands.
	 *
	 * d) If the logical unit reset is caused by a particular I_T nexus
	 * (e.g., by a LOGICAL UNIT RESET task management function), then "yes"
	 * (TASK_ABORTED status) applies.
	 *
	 * Otherwise (e.g., अगर triggered by a hard reset), "no"
	 * (no TASK_ABORTED SAM status) applies.
	 *
	 * Note that this seems to be independent of TAS (Task Aborted Status)
	 * in the Control Mode Page.
	 */
	क्रम (i = 0; i < dev->queue_cnt; i++) अणु
		flush_work(&dev->queues[i].sq.work);

		spin_lock_irqsave(&dev->queues[i].lock, flags);
		list_क्रम_each_entry_safe(cmd, next, &dev->queues[i].state_list,
					 state_list) अणु
			/*
			 * For PREEMPT_AND_ABORT usage, only process commands
			 * with a matching reservation key.
			 */
			अगर (target_check_cdb_and_preempt(preempt_and_पात_list,
							 cmd))
				जारी;

			/*
			 * Not पातing PROUT PREEMPT_AND_ABORT CDB..
			 */
			अगर (prout_cmd == cmd)
				जारी;

			sess = cmd->se_sess;
			अगर (WARN_ON_ONCE(!sess))
				जारी;

			spin_lock(&sess->sess_cmd_lock);
			rc = __target_check_io_state(cmd, पंचांगr_sess, tas);
			spin_unlock(&sess->sess_cmd_lock);
			अगर (!rc)
				जारी;

			list_move_tail(&cmd->state_list, &drain_task_list);
			cmd->state_active = false;
		पूर्ण
		spin_unlock_irqrestore(&dev->queues[i].lock, flags);
	पूर्ण

	अगर (dev->transport->पंचांगr_notअगरy)
		dev->transport->पंचांगr_notअगरy(dev, preempt_and_पात_list ?
					   TMR_LUN_RESET_PRO : TMR_LUN_RESET,
					   &drain_task_list);

	जबतक (!list_empty(&drain_task_list)) अणु
		cmd = list_entry(drain_task_list.next, काष्ठा se_cmd, state_list);
		list_del_init(&cmd->state_list);

		target_show_cmd("LUN_RESET: ", cmd);
		pr_debug("LUN_RESET: ITT[0x%08llx] - %s pr_res_key: 0x%016Lx\n",
			 cmd->tag, (preempt_and_पात_list) ? "preempt" : "",
			 cmd->pr_res_key);

		target_put_cmd_and_रुको(cmd);
	पूर्ण
पूर्ण

पूर्णांक core_पंचांगr_lun_reset(
        काष्ठा se_device *dev,
        काष्ठा se_पंचांगr_req *पंचांगr,
        काष्ठा list_head *preempt_and_पात_list,
        काष्ठा se_cmd *prout_cmd)
अणु
	काष्ठा se_node_acl *पंचांगr_nacl = शून्य;
	काष्ठा se_portal_group *पंचांगr_tpg = शून्य;
	काष्ठा se_session *पंचांगr_sess = शून्य;
	bool tas;
        /*
	 * TASK_ABORTED status bit, this is configurable via ConfigFS
	 * काष्ठा se_device attributes.  spc4r17 section 7.4.6 Control mode page
	 *
	 * A task पातed status (TAS) bit set to zero specअगरies that पातed
	 * tasks shall be terminated by the device server without any response
	 * to the application client. A TAS bit set to one specअगरies that tasks
	 * पातed by the actions of an I_T nexus other than the I_T nexus on
	 * which the command was received shall be completed with TASK ABORTED
	 * status (see SAM-4).
	 */
	tas = dev->dev_attrib.emulate_tas;
	/*
	 * Determine अगर this se_पंचांगr is coming from a $FABRIC_MOD
	 * or काष्ठा se_device passthrough..
	 */
	अगर (पंचांगr && पंचांगr->task_cmd && पंचांगr->task_cmd->se_sess) अणु
		पंचांगr_sess = पंचांगr->task_cmd->se_sess;
		पंचांगr_nacl = पंचांगr_sess->se_node_acl;
		पंचांगr_tpg = पंचांगr_sess->se_tpg;
		अगर (पंचांगr_nacl && पंचांगr_tpg) अणु
			pr_debug("LUN_RESET: TMR caller fabric: %s"
				" initiator port %s\n",
				पंचांगr_tpg->se_tpg_tfo->fabric_name,
				पंचांगr_nacl->initiatorname);
		पूर्ण
	पूर्ण
	pr_debug("LUN_RESET: %s starting for [%s], tas: %d\n",
		(preempt_and_पात_list) ? "Preempt" : "TMR",
		dev->transport->name, tas);

	core_पंचांगr_drain_पंचांगr_list(dev, पंचांगr, preempt_and_पात_list);
	core_पंचांगr_drain_state_list(dev, prout_cmd, पंचांगr_sess, tas,
				preempt_and_पात_list);

	/*
	 * Clear any legacy SPC-2 reservation when called during
	 * LOGICAL UNIT RESET
	 */
	अगर (!preempt_and_पात_list &&
	     (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS)) अणु
		spin_lock(&dev->dev_reservation_lock);
		dev->reservation_holder = शून्य;
		dev->dev_reservation_flags &= ~DRF_SPC2_RESERVATIONS;
		spin_unlock(&dev->dev_reservation_lock);
		pr_debug("LUN_RESET: SCSI-2 Released reservation\n");
	पूर्ण

	atomic_दीर्घ_inc(&dev->num_resets);

	pr_debug("LUN_RESET: %s for [%s] Complete\n",
			(preempt_and_पात_list) ? "Preempt" : "TMR",
			dev->transport->name);
	वापस 0;
पूर्ण

