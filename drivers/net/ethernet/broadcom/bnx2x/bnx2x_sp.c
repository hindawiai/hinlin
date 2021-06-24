<शैली गुरु>
/* bnx2x_sp.c: Qlogic Everest network driver.
 *
 * Copyright 2011-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 * All rights reserved
 *
 * Unless you and Qlogic execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2, available
 * at http://www.gnu.org/licenses/gpl-2.0.hपंचांगl (the "GPL").
 *
 * Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other Qlogic software provided under a
 * license other than the GPL, without Qlogic's express prior written
 * consent.
 *
 * Maपूर्णांकained by: Ariel Elior <ariel.elior@qlogic.com>
 * Written by: Vladislav Zolotarov
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/crc32.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/crc32c.h>
#समावेश "bnx2x.h"
#समावेश "bnx2x_cmn.h"
#समावेश "bnx2x_sp.h"

#घोषणा BNX2X_MAX_EMUL_MULTI		16

/**** Exe Queue पूर्णांकerfaces ****/

/**
 * bnx2x_exe_queue_init - init the Exe Queue object
 *
 * @bp:		driver handle
 * @o:		poपूर्णांकer to the object
 * @exe_len:	length
 * @owner:	poपूर्णांकer to the owner
 * @validate:	validate function poपूर्णांकer
 * @हटाओ:	हटाओ function poपूर्णांकer
 * @optimize:	optimize function poपूर्णांकer
 * @exec:	execute function poपूर्णांकer
 * @get:	get function poपूर्णांकer
 */
अटल अंतरभूत व्योम bnx2x_exe_queue_init(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_exe_queue_obj *o,
					पूर्णांक exe_len,
					जोड़ bnx2x_qable_obj *owner,
					exe_q_validate validate,
					exe_q_हटाओ हटाओ,
					exe_q_optimize optimize,
					exe_q_execute exec,
					exe_q_get get)
अणु
	स_रखो(o, 0, माप(*o));

	INIT_LIST_HEAD(&o->exe_queue);
	INIT_LIST_HEAD(&o->pending_comp);

	spin_lock_init(&o->lock);

	o->exe_chunk_len = exe_len;
	o->owner         = owner;

	/* Owner specअगरic callbacks */
	o->validate      = validate;
	o->हटाओ        = हटाओ;
	o->optimize      = optimize;
	o->execute       = exec;
	o->get           = get;

	DP(BNX2X_MSG_SP, "Setup the execution queue with the chunk length of %d\n",
	   exe_len);
पूर्ण

अटल अंतरभूत व्योम bnx2x_exe_queue_मुक्त_elem(काष्ठा bnx2x *bp,
					     काष्ठा bnx2x_exeq_elem *elem)
अणु
	DP(BNX2X_MSG_SP, "Deleting an exe_queue element\n");
	kमुक्त(elem);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_exe_queue_length(काष्ठा bnx2x_exe_queue_obj *o)
अणु
	काष्ठा bnx2x_exeq_elem *elem;
	पूर्णांक cnt = 0;

	spin_lock_bh(&o->lock);

	list_क्रम_each_entry(elem, &o->exe_queue, link)
		cnt++;

	spin_unlock_bh(&o->lock);

	वापस cnt;
पूर्ण

/**
 * bnx2x_exe_queue_add - add a new element to the execution queue
 *
 * @bp:		driver handle
 * @o:		queue
 * @elem:	new command to add
 * @restore:	true - करो not optimize the command
 *
 * If the element is optimized or is illegal, मुक्तs it.
 */
अटल अंतरभूत पूर्णांक bnx2x_exe_queue_add(काष्ठा bnx2x *bp,
				      काष्ठा bnx2x_exe_queue_obj *o,
				      काष्ठा bnx2x_exeq_elem *elem,
				      bool restore)
अणु
	पूर्णांक rc;

	spin_lock_bh(&o->lock);

	अगर (!restore) अणु
		/* Try to cancel this element queue */
		rc = o->optimize(bp, o->owner, elem);
		अगर (rc)
			जाओ मुक्त_and_निकास;

		/* Check अगर this request is ok */
		rc = o->validate(bp, o->owner, elem);
		अगर (rc) अणु
			DP(BNX2X_MSG_SP, "Preamble failed: %d\n", rc);
			जाओ मुक्त_and_निकास;
		पूर्ण
	पूर्ण

	/* If so, add it to the execution queue */
	list_add_tail(&elem->link, &o->exe_queue);

	spin_unlock_bh(&o->lock);

	वापस 0;

मुक्त_and_निकास:
	bnx2x_exe_queue_मुक्त_elem(bp, elem);

	spin_unlock_bh(&o->lock);

	वापस rc;
पूर्ण

अटल अंतरभूत व्योम __bnx2x_exe_queue_reset_pending(
	काष्ठा bnx2x *bp,
	काष्ठा bnx2x_exe_queue_obj *o)
अणु
	काष्ठा bnx2x_exeq_elem *elem;

	जबतक (!list_empty(&o->pending_comp)) अणु
		elem = list_first_entry(&o->pending_comp,
					काष्ठा bnx2x_exeq_elem, link);

		list_del(&elem->link);
		bnx2x_exe_queue_मुक्त_elem(bp, elem);
	पूर्ण
पूर्ण

/**
 * bnx2x_exe_queue_step - execute one execution chunk atomically
 *
 * @bp:			driver handle
 * @o:			queue
 * @ramrod_flags:	flags
 *
 * (Should be called जबतक holding the exe_queue->lock).
 */
अटल अंतरभूत पूर्णांक bnx2x_exe_queue_step(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_exe_queue_obj *o,
				       अचिन्हित दीर्घ *ramrod_flags)
अणु
	काष्ठा bnx2x_exeq_elem *elem, spacer;
	पूर्णांक cur_len = 0, rc;

	स_रखो(&spacer, 0, माप(spacer));

	/* Next step should not be perक्रमmed until the current is finished,
	 * unless a DRV_CLEAR_ONLY bit is set. In this हाल we just want to
	 * properly clear object पूर्णांकernals without sending any command to the FW
	 * which also implies there won't be any completion to clear the
	 * 'pending' list.
	 */
	अगर (!list_empty(&o->pending_comp)) अणु
		अगर (test_bit(RAMROD_DRV_CLR_ONLY, ramrod_flags)) अणु
			DP(BNX2X_MSG_SP, "RAMROD_DRV_CLR_ONLY requested: resetting a pending_comp list\n");
			__bnx2x_exe_queue_reset_pending(bp, o);
		पूर्ण अन्यथा अणु
			वापस 1;
		पूर्ण
	पूर्ण

	/* Run through the pending commands list and create a next
	 * execution chunk.
	 */
	जबतक (!list_empty(&o->exe_queue)) अणु
		elem = list_first_entry(&o->exe_queue, काष्ठा bnx2x_exeq_elem,
					link);
		WARN_ON(!elem->cmd_len);

		अगर (cur_len + elem->cmd_len <= o->exe_chunk_len) अणु
			cur_len += elem->cmd_len;
			/* Prevent from both lists being empty when moving an
			 * element. This will allow the call of
			 * bnx2x_exe_queue_empty() without locking.
			 */
			list_add_tail(&spacer.link, &o->pending_comp);
			mb();
			list_move_tail(&elem->link, &o->pending_comp);
			list_del(&spacer.link);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	/* Sanity check */
	अगर (!cur_len)
		वापस 0;

	rc = o->execute(bp, o->owner, &o->pending_comp, ramrod_flags);
	अगर (rc < 0)
		/* In हाल of an error वापस the commands back to the queue
		 * and reset the pending_comp.
		 */
		list_splice_init(&o->pending_comp, &o->exe_queue);
	अन्यथा अगर (!rc)
		/* If zero is वापसed, means there are no outstanding pending
		 * completions and we may dismiss the pending list.
		 */
		__bnx2x_exe_queue_reset_pending(bp, o);

	वापस rc;
पूर्ण

अटल अंतरभूत bool bnx2x_exe_queue_empty(काष्ठा bnx2x_exe_queue_obj *o)
अणु
	bool empty = list_empty(&o->exe_queue);

	/* Don't reorder!!! */
	mb();

	वापस empty && list_empty(&o->pending_comp);
पूर्ण

अटल अंतरभूत काष्ठा bnx2x_exeq_elem *bnx2x_exe_queue_alloc_elem(
	काष्ठा bnx2x *bp)
अणु
	DP(BNX2X_MSG_SP, "Allocating a new exe_queue element\n");
	वापस kzalloc(माप(काष्ठा bnx2x_exeq_elem), GFP_ATOMIC);
पूर्ण

/************************ raw_obj functions ***********************************/
अटल bool bnx2x_raw_check_pending(काष्ठा bnx2x_raw_obj *o)
अणु
	वापस !!test_bit(o->state, o->pstate);
पूर्ण

अटल व्योम bnx2x_raw_clear_pending(काष्ठा bnx2x_raw_obj *o)
अणु
	smp_mb__beक्रमe_atomic();
	clear_bit(o->state, o->pstate);
	smp_mb__after_atomic();
पूर्ण

अटल व्योम bnx2x_raw_set_pending(काष्ठा bnx2x_raw_obj *o)
अणु
	smp_mb__beक्रमe_atomic();
	set_bit(o->state, o->pstate);
	smp_mb__after_atomic();
पूर्ण

/**
 * bnx2x_state_रुको - रुको until the given bit(state) is cleared
 *
 * @bp:		device handle
 * @state:	state which is to be cleared
 * @pstate:	state buffer
 *
 */
अटल अंतरभूत पूर्णांक bnx2x_state_रुको(काष्ठा bnx2x *bp, पूर्णांक state,
				   अचिन्हित दीर्घ *pstate)
अणु
	/* can take a जबतक अगर any port is running */
	पूर्णांक cnt = 5000;

	अगर (CHIP_REV_IS_EMUL(bp))
		cnt *= 20;

	DP(BNX2X_MSG_SP, "waiting for state to become %d\n", state);

	might_sleep();
	जबतक (cnt--) अणु
		अगर (!test_bit(state, pstate)) अणु
#अगर_घोषित BNX2X_STOP_ON_ERROR
			DP(BNX2X_MSG_SP, "exit  (cnt %d)\n", 5000 - cnt);
#पूर्ण_अगर
			वापस 0;
		पूर्ण

		usleep_range(1000, 2000);

		अगर (bp->panic)
			वापस -EIO;
	पूर्ण

	/* समयout! */
	BNX2X_ERR("timeout waiting for state %d\n", state);
#अगर_घोषित BNX2X_STOP_ON_ERROR
	bnx2x_panic();
#पूर्ण_अगर

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक bnx2x_raw_रुको(काष्ठा bnx2x *bp, काष्ठा bnx2x_raw_obj *raw)
अणु
	वापस bnx2x_state_रुको(bp, raw->state, raw->pstate);
पूर्ण

/***************** Classअगरication verbs: Set/Del MAC/VLAN/VLAN-MAC ************/
/* credit handling callbacks */
अटल bool bnx2x_get_cam_offset_mac(काष्ठा bnx2x_vlan_mac_obj *o, पूर्णांक *offset)
अणु
	काष्ठा bnx2x_credit_pool_obj *mp = o->macs_pool;

	WARN_ON(!mp);

	वापस mp->get_entry(mp, offset);
पूर्ण

अटल bool bnx2x_get_credit_mac(काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	काष्ठा bnx2x_credit_pool_obj *mp = o->macs_pool;

	WARN_ON(!mp);

	वापस mp->get(mp, 1);
पूर्ण

अटल bool bnx2x_get_cam_offset_vlan(काष्ठा bnx2x_vlan_mac_obj *o, पूर्णांक *offset)
अणु
	काष्ठा bnx2x_credit_pool_obj *vp = o->vlans_pool;

	WARN_ON(!vp);

	वापस vp->get_entry(vp, offset);
पूर्ण

अटल bool bnx2x_get_credit_vlan(काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	काष्ठा bnx2x_credit_pool_obj *vp = o->vlans_pool;

	WARN_ON(!vp);

	वापस vp->get(vp, 1);
पूर्ण

अटल bool bnx2x_get_credit_vlan_mac(काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	काष्ठा bnx2x_credit_pool_obj *mp = o->macs_pool;
	काष्ठा bnx2x_credit_pool_obj *vp = o->vlans_pool;

	अगर (!mp->get(mp, 1))
		वापस false;

	अगर (!vp->get(vp, 1)) अणु
		mp->put(mp, 1);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool bnx2x_put_cam_offset_mac(काष्ठा bnx2x_vlan_mac_obj *o, पूर्णांक offset)
अणु
	काष्ठा bnx2x_credit_pool_obj *mp = o->macs_pool;

	वापस mp->put_entry(mp, offset);
पूर्ण

अटल bool bnx2x_put_credit_mac(काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	काष्ठा bnx2x_credit_pool_obj *mp = o->macs_pool;

	वापस mp->put(mp, 1);
पूर्ण

अटल bool bnx2x_put_cam_offset_vlan(काष्ठा bnx2x_vlan_mac_obj *o, पूर्णांक offset)
अणु
	काष्ठा bnx2x_credit_pool_obj *vp = o->vlans_pool;

	वापस vp->put_entry(vp, offset);
पूर्ण

अटल bool bnx2x_put_credit_vlan(काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	काष्ठा bnx2x_credit_pool_obj *vp = o->vlans_pool;

	वापस vp->put(vp, 1);
पूर्ण

अटल bool bnx2x_put_credit_vlan_mac(काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	काष्ठा bnx2x_credit_pool_obj *mp = o->macs_pool;
	काष्ठा bnx2x_credit_pool_obj *vp = o->vlans_pool;

	अगर (!mp->put(mp, 1))
		वापस false;

	अगर (!vp->put(vp, 1)) अणु
		mp->get(mp, 1);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * __bnx2x_vlan_mac_h_ग_लिखो_trylock - try getting the vlan mac ग_लिखोr lock
 *
 * @bp:		device handle
 * @o:		vlan_mac object
 *
 * Context: Non-blocking implementation; should be called under execution
 *          queue lock.
 */
अटल पूर्णांक __bnx2x_vlan_mac_h_ग_लिखो_trylock(काष्ठा bnx2x *bp,
					    काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	अगर (o->head_पढ़ोer) अणु
		DP(BNX2X_MSG_SP, "vlan_mac_lock writer - There are readers; Busy\n");
		वापस -EBUSY;
	पूर्ण

	DP(BNX2X_MSG_SP, "vlan_mac_lock writer - Taken\n");
	वापस 0;
पूर्ण

/**
 * __bnx2x_vlan_mac_h_exec_pending - execute step instead of a previous step
 *
 * @bp:		device handle
 * @o:		vlan_mac object
 *
 * details Should be called under execution queue lock; notice it might release
 *          and reclaim it during its run.
 */
अटल व्योम __bnx2x_vlan_mac_h_exec_pending(काष्ठा bnx2x *bp,
					    काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ ramrod_flags = o->saved_ramrod_flags;

	DP(BNX2X_MSG_SP, "vlan_mac_lock execute pending command with ramrod flags %lu\n",
	   ramrod_flags);
	o->head_exe_request = false;
	o->saved_ramrod_flags = 0;
	rc = bnx2x_exe_queue_step(bp, &o->exe_queue, &ramrod_flags);
	अगर ((rc != 0) && (rc != 1)) अणु
		BNX2X_ERR("execution of pending commands failed with rc %d\n",
			  rc);
#अगर_घोषित BNX2X_STOP_ON_ERROR
		bnx2x_panic();
#पूर्ण_अगर
	पूर्ण
पूर्ण

/**
 * __bnx2x_vlan_mac_h_pend - Pend an execution step which couldn't run
 *
 * @bp:			device handle
 * @o:			vlan_mac object
 * @ramrod_flags:	ramrod flags of missed execution
 *
 * Context: Should be called under execution queue lock.
 */
अटल व्योम __bnx2x_vlan_mac_h_pend(काष्ठा bnx2x *bp,
				    काष्ठा bnx2x_vlan_mac_obj *o,
				    अचिन्हित दीर्घ ramrod_flags)
अणु
	o->head_exe_request = true;
	o->saved_ramrod_flags = ramrod_flags;
	DP(BNX2X_MSG_SP, "Placing pending execution with ramrod flags %lu\n",
	   ramrod_flags);
पूर्ण

/**
 * __bnx2x_vlan_mac_h_ग_लिखो_unlock - unlock the vlan mac head list ग_लिखोr lock
 *
 * @bp:			device handle
 * @o:			vlan_mac object
 *
 * Context: Should be called under execution queue lock. Notice अगर a pending
 *          execution exists, it would perक्रमm it - possibly releasing and
 *          reclaiming the execution queue lock.
 */
अटल व्योम __bnx2x_vlan_mac_h_ग_लिखो_unlock(काष्ठा bnx2x *bp,
					    काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	/* It's possible a new pending execution was added since this ग_लिखोr
	 * executed. If so, execute again. [Ad infinitum]
	 */
	जबतक (o->head_exe_request) अणु
		DP(BNX2X_MSG_SP, "vlan_mac_lock - writer release encountered a pending request\n");
		__bnx2x_vlan_mac_h_exec_pending(bp, o);
	पूर्ण
पूर्ण


/**
 * __bnx2x_vlan_mac_h_पढ़ो_lock - lock the vlan mac head list पढ़ोer lock
 *
 * @bp:			device handle
 * @o:			vlan_mac object
 *
 * Context: Should be called under the execution queue lock. May sleep. May
 *          release and reclaim execution queue lock during its run.
 */
अटल पूर्णांक __bnx2x_vlan_mac_h_पढ़ो_lock(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	/* If we got here, we're holding lock --> no WRITER exists */
	o->head_पढ़ोer++;
	DP(BNX2X_MSG_SP, "vlan_mac_lock - locked reader - number %d\n",
	   o->head_पढ़ोer);

	वापस 0;
पूर्ण

/**
 * bnx2x_vlan_mac_h_पढ़ो_lock - lock the vlan mac head list पढ़ोer lock
 *
 * @bp:			device handle
 * @o:			vlan_mac object
 *
 * Context: May sleep. Claims and releases execution queue lock during its run.
 */
पूर्णांक bnx2x_vlan_mac_h_पढ़ो_lock(काष्ठा bnx2x *bp,
			       काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	पूर्णांक rc;

	spin_lock_bh(&o->exe_queue.lock);
	rc = __bnx2x_vlan_mac_h_पढ़ो_lock(bp, o);
	spin_unlock_bh(&o->exe_queue.lock);

	वापस rc;
पूर्ण

/**
 * __bnx2x_vlan_mac_h_पढ़ो_unlock - unlock the vlan mac head list पढ़ोer lock
 *
 * @bp:			device handle
 * @o:			vlan_mac object
 *
 * Context: Should be called under execution queue lock. Notice अगर a pending
 *          execution exists, it would be perक्रमmed अगर this was the last
 *          पढ़ोer. possibly releasing and reclaiming the execution queue lock.
 */
अटल व्योम __bnx2x_vlan_mac_h_पढ़ो_unlock(काष्ठा bnx2x *bp,
					  काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	अगर (!o->head_पढ़ोer) अणु
		BNX2X_ERR("Need to release vlan mac reader lock, but lock isn't taken\n");
#अगर_घोषित BNX2X_STOP_ON_ERROR
		bnx2x_panic();
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		o->head_पढ़ोer--;
		DP(BNX2X_MSG_SP, "vlan_mac_lock - decreased readers to %d\n",
		   o->head_पढ़ोer);
	पूर्ण

	/* It's possible a new pending execution was added, and that this पढ़ोer
	 * was last - अगर so we need to execute the command.
	 */
	अगर (!o->head_पढ़ोer && o->head_exe_request) अणु
		DP(BNX2X_MSG_SP, "vlan_mac_lock - reader release encountered a pending request\n");

		/* Writer release will करो the trick */
		__bnx2x_vlan_mac_h_ग_लिखो_unlock(bp, o);
	पूर्ण
पूर्ण

/**
 * bnx2x_vlan_mac_h_पढ़ो_unlock - unlock the vlan mac head list पढ़ोer lock
 *
 * @bp:			device handle
 * @o:			vlan_mac object
 *
 * Context: Notice अगर a pending execution exists, it would be perक्रमmed अगर this
 *          was the last पढ़ोer. Claims and releases the execution queue lock
 *          during its run.
 */
व्योम bnx2x_vlan_mac_h_पढ़ो_unlock(काष्ठा bnx2x *bp,
				  काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	spin_lock_bh(&o->exe_queue.lock);
	__bnx2x_vlan_mac_h_पढ़ो_unlock(bp, o);
	spin_unlock_bh(&o->exe_queue.lock);
पूर्ण

अटल पूर्णांक bnx2x_get_n_elements(काष्ठा bnx2x *bp, काष्ठा bnx2x_vlan_mac_obj *o,
				पूर्णांक n, u8 *base, u8 stride, u8 size)
अणु
	काष्ठा bnx2x_vlan_mac_registry_elem *pos;
	u8 *next = base;
	पूर्णांक counter = 0;
	पूर्णांक पढ़ो_lock;

	DP(BNX2X_MSG_SP, "get_n_elements - taking vlan_mac_lock (reader)\n");
	पढ़ो_lock = bnx2x_vlan_mac_h_पढ़ो_lock(bp, o);
	अगर (पढ़ो_lock != 0)
		BNX2X_ERR("get_n_elements failed to get vlan mac reader lock; Access without lock\n");

	/* traverse list */
	list_क्रम_each_entry(pos, &o->head, link) अणु
		अगर (counter < n) अणु
			स_नकल(next, &pos->u, size);
			counter++;
			DP(BNX2X_MSG_SP, "copied element number %d to address %p element was:\n",
			   counter, next);
			next += stride + size;
		पूर्ण
	पूर्ण

	अगर (पढ़ो_lock == 0) अणु
		DP(BNX2X_MSG_SP, "get_n_elements - releasing vlan_mac_lock (reader)\n");
		bnx2x_vlan_mac_h_पढ़ो_unlock(bp, o);
	पूर्ण

	वापस counter * ETH_ALEN;
पूर्ण

/* check_add() callbacks */
अटल पूर्णांक bnx2x_check_mac_add(काष्ठा bnx2x *bp,
			       काष्ठा bnx2x_vlan_mac_obj *o,
			       जोड़ bnx2x_classअगरication_ramrod_data *data)
अणु
	काष्ठा bnx2x_vlan_mac_registry_elem *pos;

	DP(BNX2X_MSG_SP, "Checking MAC %pM for ADD command\n", data->mac.mac);

	अगर (!is_valid_ether_addr(data->mac.mac))
		वापस -EINVAL;

	/* Check अगर a requested MAC alपढ़ोy exists */
	list_क्रम_each_entry(pos, &o->head, link)
		अगर (ether_addr_equal(data->mac.mac, pos->u.mac.mac) &&
		    (data->mac.is_inner_mac == pos->u.mac.is_inner_mac))
			वापस -EEXIST;

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_check_vlan_add(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_vlan_mac_obj *o,
				जोड़ bnx2x_classअगरication_ramrod_data *data)
अणु
	काष्ठा bnx2x_vlan_mac_registry_elem *pos;

	DP(BNX2X_MSG_SP, "Checking VLAN %d for ADD command\n", data->vlan.vlan);

	list_क्रम_each_entry(pos, &o->head, link)
		अगर (data->vlan.vlan == pos->u.vlan.vlan)
			वापस -EEXIST;

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_check_vlan_mac_add(काष्ठा bnx2x *bp,
				    काष्ठा bnx2x_vlan_mac_obj *o,
				   जोड़ bnx2x_classअगरication_ramrod_data *data)
अणु
	काष्ठा bnx2x_vlan_mac_registry_elem *pos;

	DP(BNX2X_MSG_SP, "Checking VLAN_MAC (%pM, %d) for ADD command\n",
	   data->vlan_mac.mac, data->vlan_mac.vlan);

	list_क्रम_each_entry(pos, &o->head, link)
		अगर ((data->vlan_mac.vlan == pos->u.vlan_mac.vlan) &&
		    (!स_भेद(data->vlan_mac.mac, pos->u.vlan_mac.mac,
				  ETH_ALEN)) &&
		    (data->vlan_mac.is_inner_mac ==
		     pos->u.vlan_mac.is_inner_mac))
			वापस -EEXIST;

	वापस 0;
पूर्ण

/* check_del() callbacks */
अटल काष्ठा bnx2x_vlan_mac_registry_elem *
	bnx2x_check_mac_del(काष्ठा bnx2x *bp,
			    काष्ठा bnx2x_vlan_mac_obj *o,
			    जोड़ bnx2x_classअगरication_ramrod_data *data)
अणु
	काष्ठा bnx2x_vlan_mac_registry_elem *pos;

	DP(BNX2X_MSG_SP, "Checking MAC %pM for DEL command\n", data->mac.mac);

	list_क्रम_each_entry(pos, &o->head, link)
		अगर (ether_addr_equal(data->mac.mac, pos->u.mac.mac) &&
		    (data->mac.is_inner_mac == pos->u.mac.is_inner_mac))
			वापस pos;

	वापस शून्य;
पूर्ण

अटल काष्ठा bnx2x_vlan_mac_registry_elem *
	bnx2x_check_vlan_del(काष्ठा bnx2x *bp,
			     काष्ठा bnx2x_vlan_mac_obj *o,
			     जोड़ bnx2x_classअगरication_ramrod_data *data)
अणु
	काष्ठा bnx2x_vlan_mac_registry_elem *pos;

	DP(BNX2X_MSG_SP, "Checking VLAN %d for DEL command\n", data->vlan.vlan);

	list_क्रम_each_entry(pos, &o->head, link)
		अगर (data->vlan.vlan == pos->u.vlan.vlan)
			वापस pos;

	वापस शून्य;
पूर्ण

अटल काष्ठा bnx2x_vlan_mac_registry_elem *
	bnx2x_check_vlan_mac_del(काष्ठा bnx2x *bp,
				 काष्ठा bnx2x_vlan_mac_obj *o,
				 जोड़ bnx2x_classअगरication_ramrod_data *data)
अणु
	काष्ठा bnx2x_vlan_mac_registry_elem *pos;

	DP(BNX2X_MSG_SP, "Checking VLAN_MAC (%pM, %d) for DEL command\n",
	   data->vlan_mac.mac, data->vlan_mac.vlan);

	list_क्रम_each_entry(pos, &o->head, link)
		अगर ((data->vlan_mac.vlan == pos->u.vlan_mac.vlan) &&
		    (!स_भेद(data->vlan_mac.mac, pos->u.vlan_mac.mac,
			     ETH_ALEN)) &&
		    (data->vlan_mac.is_inner_mac ==
		     pos->u.vlan_mac.is_inner_mac))
			वापस pos;

	वापस शून्य;
पूर्ण

/* check_move() callback */
अटल bool bnx2x_check_move(काष्ठा bnx2x *bp,
			     काष्ठा bnx2x_vlan_mac_obj *src_o,
			     काष्ठा bnx2x_vlan_mac_obj *dst_o,
			     जोड़ bnx2x_classअगरication_ramrod_data *data)
अणु
	काष्ठा bnx2x_vlan_mac_registry_elem *pos;
	पूर्णांक rc;

	/* Check अगर we can delete the requested configuration from the first
	 * object.
	 */
	pos = src_o->check_del(bp, src_o, data);

	/*  check अगर configuration can be added */
	rc = dst_o->check_add(bp, dst_o, data);

	/* If this classअगरication can not be added (is alपढ़ोy set)
	 * or can't be deleted - वापस an error.
	 */
	अगर (rc || !pos)
		वापस false;

	वापस true;
पूर्ण

अटल bool bnx2x_check_move_always_err(
	काष्ठा bnx2x *bp,
	काष्ठा bnx2x_vlan_mac_obj *src_o,
	काष्ठा bnx2x_vlan_mac_obj *dst_o,
	जोड़ bnx2x_classअगरication_ramrod_data *data)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत u8 bnx2x_vlan_mac_get_rx_tx_flag(काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	काष्ठा bnx2x_raw_obj *raw = &o->raw;
	u8 rx_tx_flag = 0;

	अगर ((raw->obj_type == BNX2X_OBJ_TYPE_TX) ||
	    (raw->obj_type == BNX2X_OBJ_TYPE_RX_TX))
		rx_tx_flag |= ETH_CLASSIFY_CMD_HEADER_TX_CMD;

	अगर ((raw->obj_type == BNX2X_OBJ_TYPE_RX) ||
	    (raw->obj_type == BNX2X_OBJ_TYPE_RX_TX))
		rx_tx_flag |= ETH_CLASSIFY_CMD_HEADER_RX_CMD;

	वापस rx_tx_flag;
पूर्ण

अटल व्योम bnx2x_set_mac_in_nig(काष्ठा bnx2x *bp,
				 bool add, अचिन्हित अक्षर *dev_addr, पूर्णांक index)
अणु
	u32 wb_data[2];
	u32 reg_offset = BP_PORT(bp) ? NIG_REG_LLH1_FUNC_MEM :
			 NIG_REG_LLH0_FUNC_MEM;

	अगर (!IS_MF_SI(bp) && !IS_MF_AFEX(bp))
		वापस;

	अगर (index > BNX2X_LLH_CAM_MAX_PF_LINE)
		वापस;

	DP(BNX2X_MSG_SP, "Going to %s LLH configuration at entry %d\n",
			 (add ? "ADD" : "DELETE"), index);

	अगर (add) अणु
		/* LLH_FUNC_MEM is a u64 WB रेजिस्टर */
		reg_offset += 8*index;

		wb_data[0] = ((dev_addr[2] << 24) | (dev_addr[3] << 16) |
			      (dev_addr[4] <<  8) |  dev_addr[5]);
		wb_data[1] = ((dev_addr[0] <<  8) |  dev_addr[1]);

		REG_WR_DMAE(bp, reg_offset, wb_data, 2);
	पूर्ण

	REG_WR(bp, (BP_PORT(bp) ? NIG_REG_LLH1_FUNC_MEM_ENABLE :
				  NIG_REG_LLH0_FUNC_MEM_ENABLE) + 4*index, add);
पूर्ण

/**
 * bnx2x_vlan_mac_set_cmd_hdr_e2 - set a header in a single classअगरy ramrod
 *
 * @bp:		device handle
 * @o:		queue क्रम which we want to configure this rule
 * @add:	अगर true the command is an ADD command, DEL otherwise
 * @opcode:	CLASSIFY_RULE_OPCODE_XXX
 * @hdr:	poपूर्णांकer to a header to setup
 *
 */
अटल अंतरभूत व्योम bnx2x_vlan_mac_set_cmd_hdr_e2(काष्ठा bnx2x *bp,
	काष्ठा bnx2x_vlan_mac_obj *o, bool add, पूर्णांक opcode,
	काष्ठा eth_classअगरy_cmd_header *hdr)
अणु
	काष्ठा bnx2x_raw_obj *raw = &o->raw;

	hdr->client_id = raw->cl_id;
	hdr->func_id = raw->func_id;

	/* Rx or/and Tx (पूर्णांकernal चयनing) configuration ? */
	hdr->cmd_general_data |=
		bnx2x_vlan_mac_get_rx_tx_flag(o);

	अगर (add)
		hdr->cmd_general_data |= ETH_CLASSIFY_CMD_HEADER_IS_ADD;

	hdr->cmd_general_data |=
		(opcode << ETH_CLASSIFY_CMD_HEADER_OPCODE_SHIFT);
पूर्ण

/**
 * bnx2x_vlan_mac_set_rdata_hdr_e2 - set the classअगरy ramrod data header
 *
 * @cid:	connection id
 * @type:	BNX2X_FILTER_XXX_PENDING
 * @hdr:	poपूर्णांकer to header to setup
 * @rule_cnt:
 *
 * currently we always configure one rule and echo field to contain a CID and an
 * opcode type.
 */
अटल अंतरभूत व्योम bnx2x_vlan_mac_set_rdata_hdr_e2(u32 cid, पूर्णांक type,
				काष्ठा eth_classअगरy_header *hdr, पूर्णांक rule_cnt)
अणु
	hdr->echo = cpu_to_le32((cid & BNX2X_SWCID_MASK) |
				(type << BNX2X_SWCID_SHIFT));
	hdr->rule_cnt = (u8)rule_cnt;
पूर्ण

/* hw_config() callbacks */
अटल व्योम bnx2x_set_one_mac_e2(काष्ठा bnx2x *bp,
				 काष्ठा bnx2x_vlan_mac_obj *o,
				 काष्ठा bnx2x_exeq_elem *elem, पूर्णांक rule_idx,
				 पूर्णांक cam_offset)
अणु
	काष्ठा bnx2x_raw_obj *raw = &o->raw;
	काष्ठा eth_classअगरy_rules_ramrod_data *data =
		(काष्ठा eth_classअगरy_rules_ramrod_data *)(raw->rdata);
	पूर्णांक rule_cnt = rule_idx + 1, cmd = elem->cmd_data.vlan_mac.cmd;
	जोड़ eth_classअगरy_rule_cmd *rule_entry = &data->rules[rule_idx];
	bool add = (cmd == BNX2X_VLAN_MAC_ADD) ? true : false;
	अचिन्हित दीर्घ *vlan_mac_flags = &elem->cmd_data.vlan_mac.vlan_mac_flags;
	u8 *mac = elem->cmd_data.vlan_mac.u.mac.mac;

	/* Set LLH CAM entry: currently only iSCSI and ETH macs are
	 * relevant. In addition, current implementation is tuned क्रम a
	 * single ETH MAC.
	 *
	 * When multiple unicast ETH MACs PF configuration in चयन
	 * independent mode is required (NetQ, multiple netdev MACs,
	 * etc.), consider better utilisation of 8 per function MAC
	 * entries in the LLH रेजिस्टर. There is also
	 * NIG_REG_P[01]_LLH_FUNC_MEM2 रेजिस्टरs that complete the
	 * total number of CAM entries to 16.
	 *
	 * Currently we won't configure NIG क्रम MACs other than a primary ETH
	 * MAC and iSCSI L2 MAC.
	 *
	 * If this MAC is moving from one Queue to another, no need to change
	 * NIG configuration.
	 */
	अगर (cmd != BNX2X_VLAN_MAC_MOVE) अणु
		अगर (test_bit(BNX2X_ISCSI_ETH_MAC, vlan_mac_flags))
			bnx2x_set_mac_in_nig(bp, add, mac,
					     BNX2X_LLH_CAM_ISCSI_ETH_LINE);
		अन्यथा अगर (test_bit(BNX2X_ETH_MAC, vlan_mac_flags))
			bnx2x_set_mac_in_nig(bp, add, mac,
					     BNX2X_LLH_CAM_ETH_LINE);
	पूर्ण

	/* Reset the ramrod data buffer क्रम the first rule */
	अगर (rule_idx == 0)
		स_रखो(data, 0, माप(*data));

	/* Setup a command header */
	bnx2x_vlan_mac_set_cmd_hdr_e2(bp, o, add, CLASSIFY_RULE_OPCODE_MAC,
				      &rule_entry->mac.header);

	DP(BNX2X_MSG_SP, "About to %s MAC %pM for Queue %d\n",
	   (add ? "add" : "delete"), mac, raw->cl_id);

	/* Set a MAC itself */
	bnx2x_set_fw_mac_addr(&rule_entry->mac.mac_msb,
			      &rule_entry->mac.mac_mid,
			      &rule_entry->mac.mac_lsb, mac);
	rule_entry->mac.inner_mac =
		cpu_to_le16(elem->cmd_data.vlan_mac.u.mac.is_inner_mac);

	/* MOVE: Add a rule that will add this MAC to the target Queue */
	अगर (cmd == BNX2X_VLAN_MAC_MOVE) अणु
		rule_entry++;
		rule_cnt++;

		/* Setup ramrod data */
		bnx2x_vlan_mac_set_cmd_hdr_e2(bp,
					elem->cmd_data.vlan_mac.target_obj,
					      true, CLASSIFY_RULE_OPCODE_MAC,
					      &rule_entry->mac.header);

		/* Set a MAC itself */
		bnx2x_set_fw_mac_addr(&rule_entry->mac.mac_msb,
				      &rule_entry->mac.mac_mid,
				      &rule_entry->mac.mac_lsb, mac);
		rule_entry->mac.inner_mac =
			cpu_to_le16(elem->cmd_data.vlan_mac.
						u.mac.is_inner_mac);
	पूर्ण

	/* Set the ramrod data header */
	/* TODO: take this to the higher level in order to prevent multiple
		 writing */
	bnx2x_vlan_mac_set_rdata_hdr_e2(raw->cid, raw->state, &data->header,
					rule_cnt);
पूर्ण

/**
 * bnx2x_vlan_mac_set_rdata_hdr_e1x - set a header in a single classअगरy ramrod
 *
 * @bp:		device handle
 * @o:		queue
 * @type:	the type of echo
 * @cam_offset:	offset in cam memory
 * @hdr:	poपूर्णांकer to a header to setup
 *
 * E1/E1H
 */
अटल अंतरभूत व्योम bnx2x_vlan_mac_set_rdata_hdr_e1x(काष्ठा bnx2x *bp,
	काष्ठा bnx2x_vlan_mac_obj *o, पूर्णांक type, पूर्णांक cam_offset,
	काष्ठा mac_configuration_hdr *hdr)
अणु
	काष्ठा bnx2x_raw_obj *r = &o->raw;

	hdr->length = 1;
	hdr->offset = (u8)cam_offset;
	hdr->client_id = cpu_to_le16(0xff);
	hdr->echo = cpu_to_le32((r->cid & BNX2X_SWCID_MASK) |
				(type << BNX2X_SWCID_SHIFT));
पूर्ण

अटल अंतरभूत व्योम bnx2x_vlan_mac_set_cfg_entry_e1x(काष्ठा bnx2x *bp,
	काष्ठा bnx2x_vlan_mac_obj *o, bool add, पूर्णांक opcode, u8 *mac,
	u16 vlan_id, काष्ठा mac_configuration_entry *cfg_entry)
अणु
	काष्ठा bnx2x_raw_obj *r = &o->raw;
	u32 cl_bit_vec = (1 << r->cl_id);

	cfg_entry->clients_bit_vector = cpu_to_le32(cl_bit_vec);
	cfg_entry->pf_id = r->func_id;
	cfg_entry->vlan_id = cpu_to_le16(vlan_id);

	अगर (add) अणु
		SET_FLAG(cfg_entry->flags, MAC_CONFIGURATION_ENTRY_ACTION_TYPE,
			 T_ETH_MAC_COMMAND_SET);
		SET_FLAG(cfg_entry->flags,
			 MAC_CONFIGURATION_ENTRY_VLAN_FILTERING_MODE, opcode);

		/* Set a MAC in a ramrod data */
		bnx2x_set_fw_mac_addr(&cfg_entry->msb_mac_addr,
				      &cfg_entry->middle_mac_addr,
				      &cfg_entry->lsb_mac_addr, mac);
	पूर्ण अन्यथा
		SET_FLAG(cfg_entry->flags, MAC_CONFIGURATION_ENTRY_ACTION_TYPE,
			 T_ETH_MAC_COMMAND_INVALIDATE);
पूर्ण

अटल अंतरभूत व्योम bnx2x_vlan_mac_set_rdata_e1x(काष्ठा bnx2x *bp,
	काष्ठा bnx2x_vlan_mac_obj *o, पूर्णांक type, पूर्णांक cam_offset, bool add,
	u8 *mac, u16 vlan_id, पूर्णांक opcode, काष्ठा mac_configuration_cmd *config)
अणु
	काष्ठा mac_configuration_entry *cfg_entry = &config->config_table[0];
	काष्ठा bnx2x_raw_obj *raw = &o->raw;

	bnx2x_vlan_mac_set_rdata_hdr_e1x(bp, o, type, cam_offset,
					 &config->hdr);
	bnx2x_vlan_mac_set_cfg_entry_e1x(bp, o, add, opcode, mac, vlan_id,
					 cfg_entry);

	DP(BNX2X_MSG_SP, "%s MAC %pM CLID %d CAM offset %d\n",
			 (add ? "setting" : "clearing"),
			 mac, raw->cl_id, cam_offset);
पूर्ण

/**
 * bnx2x_set_one_mac_e1x - fill a single MAC rule ramrod data
 *
 * @bp:		device handle
 * @o:		bnx2x_vlan_mac_obj
 * @elem:	bnx2x_exeq_elem
 * @rule_idx:	rule_idx
 * @cam_offset: cam_offset
 */
अटल व्योम bnx2x_set_one_mac_e1x(काष्ठा bnx2x *bp,
				  काष्ठा bnx2x_vlan_mac_obj *o,
				  काष्ठा bnx2x_exeq_elem *elem, पूर्णांक rule_idx,
				  पूर्णांक cam_offset)
अणु
	काष्ठा bnx2x_raw_obj *raw = &o->raw;
	काष्ठा mac_configuration_cmd *config =
		(काष्ठा mac_configuration_cmd *)(raw->rdata);
	/* 57710 and 57711 करो not support MOVE command,
	 * so it's either ADD or DEL
	 */
	bool add = (elem->cmd_data.vlan_mac.cmd == BNX2X_VLAN_MAC_ADD) ?
		true : false;

	/* Reset the ramrod data buffer */
	स_रखो(config, 0, माप(*config));

	bnx2x_vlan_mac_set_rdata_e1x(bp, o, raw->state,
				     cam_offset, add,
				     elem->cmd_data.vlan_mac.u.mac.mac, 0,
				     ETH_VLAN_FILTER_ANY_VLAN, config);
पूर्ण

अटल व्योम bnx2x_set_one_vlan_e2(काष्ठा bnx2x *bp,
				  काष्ठा bnx2x_vlan_mac_obj *o,
				  काष्ठा bnx2x_exeq_elem *elem, पूर्णांक rule_idx,
				  पूर्णांक cam_offset)
अणु
	काष्ठा bnx2x_raw_obj *raw = &o->raw;
	काष्ठा eth_classअगरy_rules_ramrod_data *data =
		(काष्ठा eth_classअगरy_rules_ramrod_data *)(raw->rdata);
	पूर्णांक rule_cnt = rule_idx + 1;
	जोड़ eth_classअगरy_rule_cmd *rule_entry = &data->rules[rule_idx];
	क्रमागत bnx2x_vlan_mac_cmd cmd = elem->cmd_data.vlan_mac.cmd;
	bool add = (cmd == BNX2X_VLAN_MAC_ADD) ? true : false;
	u16 vlan = elem->cmd_data.vlan_mac.u.vlan.vlan;

	/* Reset the ramrod data buffer क्रम the first rule */
	अगर (rule_idx == 0)
		स_रखो(data, 0, माप(*data));

	/* Set a rule header */
	bnx2x_vlan_mac_set_cmd_hdr_e2(bp, o, add, CLASSIFY_RULE_OPCODE_VLAN,
				      &rule_entry->vlan.header);

	DP(BNX2X_MSG_SP, "About to %s VLAN %d\n", (add ? "add" : "delete"),
			 vlan);

	/* Set a VLAN itself */
	rule_entry->vlan.vlan = cpu_to_le16(vlan);

	/* MOVE: Add a rule that will add this MAC to the target Queue */
	अगर (cmd == BNX2X_VLAN_MAC_MOVE) अणु
		rule_entry++;
		rule_cnt++;

		/* Setup ramrod data */
		bnx2x_vlan_mac_set_cmd_hdr_e2(bp,
					elem->cmd_data.vlan_mac.target_obj,
					      true, CLASSIFY_RULE_OPCODE_VLAN,
					      &rule_entry->vlan.header);

		/* Set a VLAN itself */
		rule_entry->vlan.vlan = cpu_to_le16(vlan);
	पूर्ण

	/* Set the ramrod data header */
	/* TODO: take this to the higher level in order to prevent multiple
		 writing */
	bnx2x_vlan_mac_set_rdata_hdr_e2(raw->cid, raw->state, &data->header,
					rule_cnt);
पूर्ण

अटल व्योम bnx2x_set_one_vlan_mac_e2(काष्ठा bnx2x *bp,
				      काष्ठा bnx2x_vlan_mac_obj *o,
				      काष्ठा bnx2x_exeq_elem *elem,
				      पूर्णांक rule_idx, पूर्णांक cam_offset)
अणु
	काष्ठा bnx2x_raw_obj *raw = &o->raw;
	काष्ठा eth_classअगरy_rules_ramrod_data *data =
		(काष्ठा eth_classअगरy_rules_ramrod_data *)(raw->rdata);
	पूर्णांक rule_cnt = rule_idx + 1;
	जोड़ eth_classअगरy_rule_cmd *rule_entry = &data->rules[rule_idx];
	क्रमागत bnx2x_vlan_mac_cmd cmd = elem->cmd_data.vlan_mac.cmd;
	bool add = (cmd == BNX2X_VLAN_MAC_ADD) ? true : false;
	u16 vlan = elem->cmd_data.vlan_mac.u.vlan_mac.vlan;
	u8 *mac = elem->cmd_data.vlan_mac.u.vlan_mac.mac;
	u16 inner_mac;

	/* Reset the ramrod data buffer क्रम the first rule */
	अगर (rule_idx == 0)
		स_रखो(data, 0, माप(*data));

	/* Set a rule header */
	bnx2x_vlan_mac_set_cmd_hdr_e2(bp, o, add, CLASSIFY_RULE_OPCODE_PAIR,
				      &rule_entry->pair.header);

	/* Set VLAN and MAC themselves */
	rule_entry->pair.vlan = cpu_to_le16(vlan);
	bnx2x_set_fw_mac_addr(&rule_entry->pair.mac_msb,
			      &rule_entry->pair.mac_mid,
			      &rule_entry->pair.mac_lsb, mac);
	inner_mac = elem->cmd_data.vlan_mac.u.vlan_mac.is_inner_mac;
	rule_entry->pair.inner_mac = cpu_to_le16(inner_mac);
	/* MOVE: Add a rule that will add this MAC/VLAN to the target Queue */
	अगर (cmd == BNX2X_VLAN_MAC_MOVE) अणु
		काष्ठा bnx2x_vlan_mac_obj *target_obj;

		rule_entry++;
		rule_cnt++;

		/* Setup ramrod data */
		target_obj = elem->cmd_data.vlan_mac.target_obj;
		bnx2x_vlan_mac_set_cmd_hdr_e2(bp, target_obj,
					      true, CLASSIFY_RULE_OPCODE_PAIR,
					      &rule_entry->pair.header);

		/* Set a VLAN itself */
		rule_entry->pair.vlan = cpu_to_le16(vlan);
		bnx2x_set_fw_mac_addr(&rule_entry->pair.mac_msb,
				      &rule_entry->pair.mac_mid,
				      &rule_entry->pair.mac_lsb, mac);
		rule_entry->pair.inner_mac = cpu_to_le16(inner_mac);
	पूर्ण

	/* Set the ramrod data header */
	bnx2x_vlan_mac_set_rdata_hdr_e2(raw->cid, raw->state, &data->header,
					rule_cnt);
पूर्ण

/**
 * bnx2x_set_one_vlan_mac_e1h -
 *
 * @bp:		device handle
 * @o:		bnx2x_vlan_mac_obj
 * @elem:	bnx2x_exeq_elem
 * @rule_idx:	rule_idx
 * @cam_offset:	cam_offset
 */
अटल व्योम bnx2x_set_one_vlan_mac_e1h(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_vlan_mac_obj *o,
				       काष्ठा bnx2x_exeq_elem *elem,
				       पूर्णांक rule_idx, पूर्णांक cam_offset)
अणु
	काष्ठा bnx2x_raw_obj *raw = &o->raw;
	काष्ठा mac_configuration_cmd *config =
		(काष्ठा mac_configuration_cmd *)(raw->rdata);
	/* 57710 and 57711 करो not support MOVE command,
	 * so it's either ADD or DEL
	 */
	bool add = (elem->cmd_data.vlan_mac.cmd == BNX2X_VLAN_MAC_ADD) ?
		true : false;

	/* Reset the ramrod data buffer */
	स_रखो(config, 0, माप(*config));

	bnx2x_vlan_mac_set_rdata_e1x(bp, o, BNX2X_FILTER_VLAN_MAC_PENDING,
				     cam_offset, add,
				     elem->cmd_data.vlan_mac.u.vlan_mac.mac,
				     elem->cmd_data.vlan_mac.u.vlan_mac.vlan,
				     ETH_VLAN_FILTER_CLASSIFY, config);
पूर्ण

/**
 * bnx2x_vlan_mac_restore - reconfigure next MAC/VLAN/VLAN-MAC element
 *
 * @bp:		device handle
 * @p:		command parameters
 * @ppos:	poपूर्णांकer to the cookie
 *
 * reconfigure next MAC/VLAN/VLAN-MAC element from the
 * previously configured elements list.
 *
 * from command parameters only RAMROD_COMP_WAIT bit in ramrod_flags is	taken
 * पूर्णांकo an account
 *
 * poपूर्णांकer to the cookie  - that should be given back in the next call to make
 * function handle the next element. If *ppos is set to शून्य it will restart the
 * iterator. If वापसed *ppos == शून्य this means that the last element has been
 * handled.
 *
 */
अटल पूर्णांक bnx2x_vlan_mac_restore(काष्ठा bnx2x *bp,
			   काष्ठा bnx2x_vlan_mac_ramrod_params *p,
			   काष्ठा bnx2x_vlan_mac_registry_elem **ppos)
अणु
	काष्ठा bnx2x_vlan_mac_registry_elem *pos;
	काष्ठा bnx2x_vlan_mac_obj *o = p->vlan_mac_obj;

	/* If list is empty - there is nothing to करो here */
	अगर (list_empty(&o->head)) अणु
		*ppos = शून्य;
		वापस 0;
	पूर्ण

	/* make a step... */
	अगर (*ppos == शून्य)
		*ppos = list_first_entry(&o->head,
					 काष्ठा bnx2x_vlan_mac_registry_elem,
					 link);
	अन्यथा
		*ppos = list_next_entry(*ppos, link);

	pos = *ppos;

	/* If it's the last step - वापस शून्य */
	अगर (list_is_last(&pos->link, &o->head))
		*ppos = शून्य;

	/* Prepare a 'user_req' */
	स_नकल(&p->user_req.u, &pos->u, माप(pos->u));

	/* Set the command */
	p->user_req.cmd = BNX2X_VLAN_MAC_ADD;

	/* Set vlan_mac_flags */
	p->user_req.vlan_mac_flags = pos->vlan_mac_flags;

	/* Set a restore bit */
	__set_bit(RAMROD_RESTORE, &p->ramrod_flags);

	वापस bnx2x_config_vlan_mac(bp, p);
पूर्ण

/* bnx2x_exeq_get_mac/bnx2x_exeq_get_vlan/bnx2x_exeq_get_vlan_mac वापस a
 * poपूर्णांकer to an element with a specअगरic criteria and शून्य अगर such an element
 * hasn't been found.
 */
अटल काष्ठा bnx2x_exeq_elem *bnx2x_exeq_get_mac(
	काष्ठा bnx2x_exe_queue_obj *o,
	काष्ठा bnx2x_exeq_elem *elem)
अणु
	काष्ठा bnx2x_exeq_elem *pos;
	काष्ठा bnx2x_mac_ramrod_data *data = &elem->cmd_data.vlan_mac.u.mac;

	/* Check pending क्रम execution commands */
	list_क्रम_each_entry(pos, &o->exe_queue, link)
		अगर (!स_भेद(&pos->cmd_data.vlan_mac.u.mac, data,
			      माप(*data)) &&
		    (pos->cmd_data.vlan_mac.cmd == elem->cmd_data.vlan_mac.cmd))
			वापस pos;

	वापस शून्य;
पूर्ण

अटल काष्ठा bnx2x_exeq_elem *bnx2x_exeq_get_vlan(
	काष्ठा bnx2x_exe_queue_obj *o,
	काष्ठा bnx2x_exeq_elem *elem)
अणु
	काष्ठा bnx2x_exeq_elem *pos;
	काष्ठा bnx2x_vlan_ramrod_data *data = &elem->cmd_data.vlan_mac.u.vlan;

	/* Check pending क्रम execution commands */
	list_क्रम_each_entry(pos, &o->exe_queue, link)
		अगर (!स_भेद(&pos->cmd_data.vlan_mac.u.vlan, data,
			      माप(*data)) &&
		    (pos->cmd_data.vlan_mac.cmd == elem->cmd_data.vlan_mac.cmd))
			वापस pos;

	वापस शून्य;
पूर्ण

अटल काष्ठा bnx2x_exeq_elem *bnx2x_exeq_get_vlan_mac(
	काष्ठा bnx2x_exe_queue_obj *o,
	काष्ठा bnx2x_exeq_elem *elem)
अणु
	काष्ठा bnx2x_exeq_elem *pos;
	काष्ठा bnx2x_vlan_mac_ramrod_data *data =
		&elem->cmd_data.vlan_mac.u.vlan_mac;

	/* Check pending क्रम execution commands */
	list_क्रम_each_entry(pos, &o->exe_queue, link)
		अगर (!स_भेद(&pos->cmd_data.vlan_mac.u.vlan_mac, data,
			    माप(*data)) &&
		    (pos->cmd_data.vlan_mac.cmd ==
		     elem->cmd_data.vlan_mac.cmd))
			वापस pos;

	वापस शून्य;
पूर्ण

/**
 * bnx2x_validate_vlan_mac_add - check अगर an ADD command can be executed
 *
 * @bp:		device handle
 * @qo:		bnx2x_qable_obj
 * @elem:	bnx2x_exeq_elem
 *
 * Checks that the requested configuration can be added. If yes and अगर
 * requested, consume CAM credit.
 *
 * The 'validate' is run after the 'optimize'.
 *
 */
अटल अंतरभूत पूर्णांक bnx2x_validate_vlan_mac_add(काष्ठा bnx2x *bp,
					      जोड़ bnx2x_qable_obj *qo,
					      काष्ठा bnx2x_exeq_elem *elem)
अणु
	काष्ठा bnx2x_vlan_mac_obj *o = &qo->vlan_mac;
	काष्ठा bnx2x_exe_queue_obj *exeq = &o->exe_queue;
	पूर्णांक rc;

	/* Check the registry */
	rc = o->check_add(bp, o, &elem->cmd_data.vlan_mac.u);
	अगर (rc) अणु
		DP(BNX2X_MSG_SP, "ADD command is not allowed considering current registry state.\n");
		वापस rc;
	पूर्ण

	/* Check अगर there is a pending ADD command क्रम this
	 * MAC/VLAN/VLAN-MAC. Return an error अगर there is.
	 */
	अगर (exeq->get(exeq, elem)) अणु
		DP(BNX2X_MSG_SP, "There is a pending ADD command already\n");
		वापस -EEXIST;
	पूर्ण

	/* TODO: Check the pending MOVE from other objects where this
	 * object is a destination object.
	 */

	/* Consume the credit अगर not requested not to */
	अगर (!(test_bit(BNX2X_DONT_CONSUME_CAM_CREDIT,
		       &elem->cmd_data.vlan_mac.vlan_mac_flags) ||
	    o->get_credit(o)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * bnx2x_validate_vlan_mac_del - check अगर the DEL command can be executed
 *
 * @bp:		device handle
 * @qo:		quable object to check
 * @elem:	element that needs to be deleted
 *
 * Checks that the requested configuration can be deleted. If yes and अगर
 * requested, वापसs a CAM credit.
 *
 * The 'validate' is run after the 'optimize'.
 */
अटल अंतरभूत पूर्णांक bnx2x_validate_vlan_mac_del(काष्ठा bnx2x *bp,
					      जोड़ bnx2x_qable_obj *qo,
					      काष्ठा bnx2x_exeq_elem *elem)
अणु
	काष्ठा bnx2x_vlan_mac_obj *o = &qo->vlan_mac;
	काष्ठा bnx2x_vlan_mac_registry_elem *pos;
	काष्ठा bnx2x_exe_queue_obj *exeq = &o->exe_queue;
	काष्ठा bnx2x_exeq_elem query_elem;

	/* If this classअगरication can not be deleted (करोesn't exist)
	 * - वापस a BNX2X_EXIST.
	 */
	pos = o->check_del(bp, o, &elem->cmd_data.vlan_mac.u);
	अगर (!pos) अणु
		DP(BNX2X_MSG_SP, "DEL command is not allowed considering current registry state\n");
		वापस -EEXIST;
	पूर्ण

	/* Check अगर there are pending DEL or MOVE commands क्रम this
	 * MAC/VLAN/VLAN-MAC. Return an error अगर so.
	 */
	स_नकल(&query_elem, elem, माप(query_elem));

	/* Check क्रम MOVE commands */
	query_elem.cmd_data.vlan_mac.cmd = BNX2X_VLAN_MAC_MOVE;
	अगर (exeq->get(exeq, &query_elem)) अणु
		BNX2X_ERR("There is a pending MOVE command already\n");
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम DEL commands */
	अगर (exeq->get(exeq, elem)) अणु
		DP(BNX2X_MSG_SP, "There is a pending DEL command already\n");
		वापस -EEXIST;
	पूर्ण

	/* Return the credit to the credit pool अगर not requested not to */
	अगर (!(test_bit(BNX2X_DONT_CONSUME_CAM_CREDIT,
		       &elem->cmd_data.vlan_mac.vlan_mac_flags) ||
	    o->put_credit(o))) अणु
		BNX2X_ERR("Failed to return a credit\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * bnx2x_validate_vlan_mac_move - check अगर the MOVE command can be executed
 *
 * @bp:		device handle
 * @qo:		quable object to check (source)
 * @elem:	element that needs to be moved
 *
 * Checks that the requested configuration can be moved. If yes and अगर
 * requested, वापसs a CAM credit.
 *
 * The 'validate' is run after the 'optimize'.
 */
अटल अंतरभूत पूर्णांक bnx2x_validate_vlan_mac_move(काष्ठा bnx2x *bp,
					       जोड़ bnx2x_qable_obj *qo,
					       काष्ठा bnx2x_exeq_elem *elem)
अणु
	काष्ठा bnx2x_vlan_mac_obj *src_o = &qo->vlan_mac;
	काष्ठा bnx2x_vlan_mac_obj *dest_o = elem->cmd_data.vlan_mac.target_obj;
	काष्ठा bnx2x_exeq_elem query_elem;
	काष्ठा bnx2x_exe_queue_obj *src_exeq = &src_o->exe_queue;
	काष्ठा bnx2x_exe_queue_obj *dest_exeq = &dest_o->exe_queue;

	/* Check अगर we can perक्रमm this operation based on the current registry
	 * state.
	 */
	अगर (!src_o->check_move(bp, src_o, dest_o,
			       &elem->cmd_data.vlan_mac.u)) अणु
		DP(BNX2X_MSG_SP, "MOVE command is not allowed considering current registry state\n");
		वापस -EINVAL;
	पूर्ण

	/* Check अगर there is an alपढ़ोy pending DEL or MOVE command क्रम the
	 * source object or ADD command क्रम a destination object. Return an
	 * error अगर so.
	 */
	स_नकल(&query_elem, elem, माप(query_elem));

	/* Check DEL on source */
	query_elem.cmd_data.vlan_mac.cmd = BNX2X_VLAN_MAC_DEL;
	अगर (src_exeq->get(src_exeq, &query_elem)) अणु
		BNX2X_ERR("There is a pending DEL command on the source queue already\n");
		वापस -EINVAL;
	पूर्ण

	/* Check MOVE on source */
	अगर (src_exeq->get(src_exeq, elem)) अणु
		DP(BNX2X_MSG_SP, "There is a pending MOVE command already\n");
		वापस -EEXIST;
	पूर्ण

	/* Check ADD on destination */
	query_elem.cmd_data.vlan_mac.cmd = BNX2X_VLAN_MAC_ADD;
	अगर (dest_exeq->get(dest_exeq, &query_elem)) अणु
		BNX2X_ERR("There is a pending ADD command on the destination queue already\n");
		वापस -EINVAL;
	पूर्ण

	/* Consume the credit अगर not requested not to */
	अगर (!(test_bit(BNX2X_DONT_CONSUME_CAM_CREDIT_DEST,
		       &elem->cmd_data.vlan_mac.vlan_mac_flags) ||
	    dest_o->get_credit(dest_o)))
		वापस -EINVAL;

	अगर (!(test_bit(BNX2X_DONT_CONSUME_CAM_CREDIT,
		       &elem->cmd_data.vlan_mac.vlan_mac_flags) ||
	    src_o->put_credit(src_o))) अणु
		/* वापस the credit taken from dest... */
		dest_o->put_credit(dest_o);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_validate_vlan_mac(काष्ठा bnx2x *bp,
				   जोड़ bnx2x_qable_obj *qo,
				   काष्ठा bnx2x_exeq_elem *elem)
अणु
	चयन (elem->cmd_data.vlan_mac.cmd) अणु
	हाल BNX2X_VLAN_MAC_ADD:
		वापस bnx2x_validate_vlan_mac_add(bp, qo, elem);
	हाल BNX2X_VLAN_MAC_DEL:
		वापस bnx2x_validate_vlan_mac_del(bp, qo, elem);
	हाल BNX2X_VLAN_MAC_MOVE:
		वापस bnx2x_validate_vlan_mac_move(bp, qo, elem);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_हटाओ_vlan_mac(काष्ठा bnx2x *bp,
				  जोड़ bnx2x_qable_obj *qo,
				  काष्ठा bnx2x_exeq_elem *elem)
अणु
	पूर्णांक rc = 0;

	/* If consumption wasn't required, nothing to करो */
	अगर (test_bit(BNX2X_DONT_CONSUME_CAM_CREDIT,
		     &elem->cmd_data.vlan_mac.vlan_mac_flags))
		वापस 0;

	चयन (elem->cmd_data.vlan_mac.cmd) अणु
	हाल BNX2X_VLAN_MAC_ADD:
	हाल BNX2X_VLAN_MAC_MOVE:
		rc = qo->vlan_mac.put_credit(&qo->vlan_mac);
		अवरोध;
	हाल BNX2X_VLAN_MAC_DEL:
		rc = qo->vlan_mac.get_credit(&qo->vlan_mac);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (rc != true)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * bnx2x_रुको_vlan_mac - passively रुको क्रम 5 seconds until all work completes.
 *
 * @bp:		device handle
 * @o:		bnx2x_vlan_mac_obj
 *
 */
अटल पूर्णांक bnx2x_रुको_vlan_mac(काष्ठा bnx2x *bp,
			       काष्ठा bnx2x_vlan_mac_obj *o)
अणु
	पूर्णांक cnt = 5000, rc;
	काष्ठा bnx2x_exe_queue_obj *exeq = &o->exe_queue;
	काष्ठा bnx2x_raw_obj *raw = &o->raw;

	जबतक (cnt--) अणु
		/* Wait क्रम the current command to complete */
		rc = raw->रुको_comp(bp, raw);
		अगर (rc)
			वापस rc;

		/* Wait until there are no pending commands */
		अगर (!bnx2x_exe_queue_empty(exeq))
			usleep_range(1000, 2000);
		अन्यथा
			वापस 0;
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक __bnx2x_vlan_mac_execute_step(काष्ठा bnx2x *bp,
					 काष्ठा bnx2x_vlan_mac_obj *o,
					 अचिन्हित दीर्घ *ramrod_flags)
अणु
	पूर्णांक rc = 0;

	spin_lock_bh(&o->exe_queue.lock);

	DP(BNX2X_MSG_SP, "vlan_mac_execute_step - trying to take writer lock\n");
	rc = __bnx2x_vlan_mac_h_ग_लिखो_trylock(bp, o);

	अगर (rc != 0) अणु
		__bnx2x_vlan_mac_h_pend(bp, o, *ramrod_flags);

		/* Calling function should not dअगरferentiate between this हाल
		 * and the हाल in which there is alपढ़ोy a pending ramrod
		 */
		rc = 1;
	पूर्ण अन्यथा अणु
		rc = bnx2x_exe_queue_step(bp, &o->exe_queue, ramrod_flags);
	पूर्ण
	spin_unlock_bh(&o->exe_queue.lock);

	वापस rc;
पूर्ण

/**
 * bnx2x_complete_vlan_mac - complete one VLAN-MAC ramrod
 *
 * @bp:		device handle
 * @o:		bnx2x_vlan_mac_obj
 * @cqe:	completion element
 * @ramrod_flags: अगर set schedule next execution chunk
 *
 */
अटल पूर्णांक bnx2x_complete_vlan_mac(काष्ठा bnx2x *bp,
				   काष्ठा bnx2x_vlan_mac_obj *o,
				   जोड़ event_ring_elem *cqe,
				   अचिन्हित दीर्घ *ramrod_flags)
अणु
	काष्ठा bnx2x_raw_obj *r = &o->raw;
	पूर्णांक rc;

	/* Clearing the pending list & raw state should be made
	 * atomically (as execution flow assumes they represent the same).
	 */
	spin_lock_bh(&o->exe_queue.lock);

	/* Reset pending list */
	__bnx2x_exe_queue_reset_pending(bp, &o->exe_queue);

	/* Clear pending */
	r->clear_pending(r);

	spin_unlock_bh(&o->exe_queue.lock);

	/* If ramrod failed this is most likely a SW bug */
	अगर (cqe->message.error)
		वापस -EINVAL;

	/* Run the next bulk of pending commands अगर requested */
	अगर (test_bit(RAMROD_CONT, ramrod_flags)) अणु
		rc = __bnx2x_vlan_mac_execute_step(bp, o, ramrod_flags);

		अगर (rc < 0)
			वापस rc;
	पूर्ण

	/* If there is more work to करो वापस PENDING */
	अगर (!bnx2x_exe_queue_empty(&o->exe_queue))
		वापस 1;

	वापस 0;
पूर्ण

/**
 * bnx2x_optimize_vlan_mac - optimize ADD and DEL commands.
 *
 * @bp:		device handle
 * @qo:		bnx2x_qable_obj
 * @elem:	bnx2x_exeq_elem
 */
अटल पूर्णांक bnx2x_optimize_vlan_mac(काष्ठा bnx2x *bp,
				   जोड़ bnx2x_qable_obj *qo,
				   काष्ठा bnx2x_exeq_elem *elem)
अणु
	काष्ठा bnx2x_exeq_elem query, *pos;
	काष्ठा bnx2x_vlan_mac_obj *o = &qo->vlan_mac;
	काष्ठा bnx2x_exe_queue_obj *exeq = &o->exe_queue;

	स_नकल(&query, elem, माप(query));

	चयन (elem->cmd_data.vlan_mac.cmd) अणु
	हाल BNX2X_VLAN_MAC_ADD:
		query.cmd_data.vlan_mac.cmd = BNX2X_VLAN_MAC_DEL;
		अवरोध;
	हाल BNX2X_VLAN_MAC_DEL:
		query.cmd_data.vlan_mac.cmd = BNX2X_VLAN_MAC_ADD;
		अवरोध;
	शेष:
		/* Don't handle anything other than ADD or DEL */
		वापस 0;
	पूर्ण

	/* If we found the appropriate element - delete it */
	pos = exeq->get(exeq, &query);
	अगर (pos) अणु

		/* Return the credit of the optimized command */
		अगर (!test_bit(BNX2X_DONT_CONSUME_CAM_CREDIT,
			      &pos->cmd_data.vlan_mac.vlan_mac_flags)) अणु
			अगर ((query.cmd_data.vlan_mac.cmd ==
			     BNX2X_VLAN_MAC_ADD) && !o->put_credit(o)) अणु
				BNX2X_ERR("Failed to return the credit for the optimized ADD command\n");
				वापस -EINVAL;
			पूर्ण अन्यथा अगर (!o->get_credit(o)) अणु /* VLAN_MAC_DEL */
				BNX2X_ERR("Failed to recover the credit from the optimized DEL command\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		DP(BNX2X_MSG_SP, "Optimizing %s command\n",
			   (elem->cmd_data.vlan_mac.cmd == BNX2X_VLAN_MAC_ADD) ?
			   "ADD" : "DEL");

		list_del(&pos->link);
		bnx2x_exe_queue_मुक्त_elem(bp, pos);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * bnx2x_vlan_mac_get_registry_elem - prepare a registry element
 *
 * @bp:	  device handle
 * @o:	vlan object
 * @elem: element
 * @restore: to restore or not
 * @re: registry
 *
 * prepare a registry element according to the current command request.
 */
अटल अंतरभूत पूर्णांक bnx2x_vlan_mac_get_registry_elem(
	काष्ठा bnx2x *bp,
	काष्ठा bnx2x_vlan_mac_obj *o,
	काष्ठा bnx2x_exeq_elem *elem,
	bool restore,
	काष्ठा bnx2x_vlan_mac_registry_elem **re)
अणु
	क्रमागत bnx2x_vlan_mac_cmd cmd = elem->cmd_data.vlan_mac.cmd;
	काष्ठा bnx2x_vlan_mac_registry_elem *reg_elem;

	/* Allocate a new registry element अगर needed. */
	अगर (!restore &&
	    ((cmd == BNX2X_VLAN_MAC_ADD) || (cmd == BNX2X_VLAN_MAC_MOVE))) अणु
		reg_elem = kzalloc(माप(*reg_elem), GFP_ATOMIC);
		अगर (!reg_elem)
			वापस -ENOMEM;

		/* Get a new CAM offset */
		अगर (!o->get_cam_offset(o, &reg_elem->cam_offset)) अणु
			/* This shall never happen, because we have checked the
			 * CAM availability in the 'validate'.
			 */
			WARN_ON(1);
			kमुक्त(reg_elem);
			वापस -EINVAL;
		पूर्ण

		DP(BNX2X_MSG_SP, "Got cam offset %d\n", reg_elem->cam_offset);

		/* Set a VLAN-MAC data */
		स_नकल(&reg_elem->u, &elem->cmd_data.vlan_mac.u,
			  माप(reg_elem->u));

		/* Copy the flags (needed क्रम DEL and RESTORE flows) */
		reg_elem->vlan_mac_flags =
			elem->cmd_data.vlan_mac.vlan_mac_flags;
	पूर्ण अन्यथा /* DEL, RESTORE */
		reg_elem = o->check_del(bp, o, &elem->cmd_data.vlan_mac.u);

	*re = reg_elem;
	वापस 0;
पूर्ण

/**
 * bnx2x_execute_vlan_mac - execute vlan mac command
 *
 * @bp:			device handle
 * @qo:			bnx2x_qable_obj poपूर्णांकer
 * @exe_chunk:		chunk
 * @ramrod_flags:	flags
 *
 * go and send a ramrod!
 */
अटल पूर्णांक bnx2x_execute_vlan_mac(काष्ठा bnx2x *bp,
				  जोड़ bnx2x_qable_obj *qo,
				  काष्ठा list_head *exe_chunk,
				  अचिन्हित दीर्घ *ramrod_flags)
अणु
	काष्ठा bnx2x_exeq_elem *elem;
	काष्ठा bnx2x_vlan_mac_obj *o = &qo->vlan_mac, *cam_obj;
	काष्ठा bnx2x_raw_obj *r = &o->raw;
	पूर्णांक rc, idx = 0;
	bool restore = test_bit(RAMROD_RESTORE, ramrod_flags);
	bool drv_only = test_bit(RAMROD_DRV_CLR_ONLY, ramrod_flags);
	काष्ठा bnx2x_vlan_mac_registry_elem *reg_elem;
	क्रमागत bnx2x_vlan_mac_cmd cmd;

	/* If DRIVER_ONLY execution is requested, cleanup a registry
	 * and निकास. Otherwise send a ramrod to FW.
	 */
	अगर (!drv_only) अणु
		WARN_ON(r->check_pending(r));

		/* Set pending */
		r->set_pending(r);

		/* Fill the ramrod data */
		list_क्रम_each_entry(elem, exe_chunk, link) अणु
			cmd = elem->cmd_data.vlan_mac.cmd;
			/* We will add to the target object in MOVE command, so
			 * change the object क्रम a CAM search.
			 */
			अगर (cmd == BNX2X_VLAN_MAC_MOVE)
				cam_obj = elem->cmd_data.vlan_mac.target_obj;
			अन्यथा
				cam_obj = o;

			rc = bnx2x_vlan_mac_get_registry_elem(bp, cam_obj,
							      elem, restore,
							      &reg_elem);
			अगर (rc)
				जाओ error_निकास;

			WARN_ON(!reg_elem);

			/* Push a new entry पूर्णांकo the registry */
			अगर (!restore &&
			    ((cmd == BNX2X_VLAN_MAC_ADD) ||
			    (cmd == BNX2X_VLAN_MAC_MOVE)))
				list_add(&reg_elem->link, &cam_obj->head);

			/* Configure a single command in a ramrod data buffer */
			o->set_one_rule(bp, o, elem, idx,
					reg_elem->cam_offset);

			/* MOVE command consumes 2 entries in the ramrod data */
			अगर (cmd == BNX2X_VLAN_MAC_MOVE)
				idx += 2;
			अन्यथा
				idx++;
		पूर्ण

		/* No need क्रम an explicit memory barrier here as दीर्घ we would
		 * need to ensure the ordering of writing to the SPQ element
		 * and updating of the SPQ producer which involves a memory
		 * पढ़ो and we will have to put a full memory barrier there
		 * (inside bnx2x_sp_post()).
		 */

		rc = bnx2x_sp_post(bp, o->ramrod_cmd, r->cid,
				   U64_HI(r->rdata_mapping),
				   U64_LO(r->rdata_mapping),
				   ETH_CONNECTION_TYPE);
		अगर (rc)
			जाओ error_निकास;
	पूर्ण

	/* Now, when we are करोne with the ramrod - clean up the registry */
	list_क्रम_each_entry(elem, exe_chunk, link) अणु
		cmd = elem->cmd_data.vlan_mac.cmd;
		अगर ((cmd == BNX2X_VLAN_MAC_DEL) ||
		    (cmd == BNX2X_VLAN_MAC_MOVE)) अणु
			reg_elem = o->check_del(bp, o,
						&elem->cmd_data.vlan_mac.u);

			WARN_ON(!reg_elem);

			o->put_cam_offset(o, reg_elem->cam_offset);
			list_del(&reg_elem->link);
			kमुक्त(reg_elem);
		पूर्ण
	पूर्ण

	अगर (!drv_only)
		वापस 1;
	अन्यथा
		वापस 0;

error_निकास:
	r->clear_pending(r);

	/* Cleanup a registry in हाल of a failure */
	list_क्रम_each_entry(elem, exe_chunk, link) अणु
		cmd = elem->cmd_data.vlan_mac.cmd;

		अगर (cmd == BNX2X_VLAN_MAC_MOVE)
			cam_obj = elem->cmd_data.vlan_mac.target_obj;
		अन्यथा
			cam_obj = o;

		/* Delete all newly added above entries */
		अगर (!restore &&
		    ((cmd == BNX2X_VLAN_MAC_ADD) ||
		    (cmd == BNX2X_VLAN_MAC_MOVE))) अणु
			reg_elem = o->check_del(bp, cam_obj,
						&elem->cmd_data.vlan_mac.u);
			अगर (reg_elem) अणु
				list_del(&reg_elem->link);
				kमुक्त(reg_elem);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_vlan_mac_push_new_cmd(
	काष्ठा bnx2x *bp,
	काष्ठा bnx2x_vlan_mac_ramrod_params *p)
अणु
	काष्ठा bnx2x_exeq_elem *elem;
	काष्ठा bnx2x_vlan_mac_obj *o = p->vlan_mac_obj;
	bool restore = test_bit(RAMROD_RESTORE, &p->ramrod_flags);

	/* Allocate the execution queue element */
	elem = bnx2x_exe_queue_alloc_elem(bp);
	अगर (!elem)
		वापस -ENOMEM;

	/* Set the command 'length' */
	चयन (p->user_req.cmd) अणु
	हाल BNX2X_VLAN_MAC_MOVE:
		elem->cmd_len = 2;
		अवरोध;
	शेष:
		elem->cmd_len = 1;
	पूर्ण

	/* Fill the object specअगरic info */
	स_नकल(&elem->cmd_data.vlan_mac, &p->user_req, माप(p->user_req));

	/* Try to add a new command to the pending list */
	वापस bnx2x_exe_queue_add(bp, &o->exe_queue, elem, restore);
पूर्ण

/**
 * bnx2x_config_vlan_mac - configure VLAN/MAC/VLAN_MAC filtering rules.
 *
 * @bp:	  device handle
 * @p:
 *
 */
पूर्णांक bnx2x_config_vlan_mac(काष्ठा bnx2x *bp,
			   काष्ठा bnx2x_vlan_mac_ramrod_params *p)
अणु
	पूर्णांक rc = 0;
	काष्ठा bnx2x_vlan_mac_obj *o = p->vlan_mac_obj;
	अचिन्हित दीर्घ *ramrod_flags = &p->ramrod_flags;
	bool cont = test_bit(RAMROD_CONT, ramrod_flags);
	काष्ठा bnx2x_raw_obj *raw = &o->raw;

	/*
	 * Add new elements to the execution list क्रम commands that require it.
	 */
	अगर (!cont) अणु
		rc = bnx2x_vlan_mac_push_new_cmd(bp, p);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* If nothing will be executed further in this iteration we want to
	 * वापस PENDING अगर there are pending commands
	 */
	अगर (!bnx2x_exe_queue_empty(&o->exe_queue))
		rc = 1;

	अगर (test_bit(RAMROD_DRV_CLR_ONLY, ramrod_flags))  अणु
		DP(BNX2X_MSG_SP, "RAMROD_DRV_CLR_ONLY requested: clearing a pending bit.\n");
		raw->clear_pending(raw);
	पूर्ण

	/* Execute commands अगर required */
	अगर (cont || test_bit(RAMROD_EXEC, ramrod_flags) ||
	    test_bit(RAMROD_COMP_WAIT, ramrod_flags)) अणु
		rc = __bnx2x_vlan_mac_execute_step(bp, p->vlan_mac_obj,
						   &p->ramrod_flags);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	/* RAMROD_COMP_WAIT is a superset of RAMROD_EXEC. If it was set
	 * then user want to रुको until the last command is करोne.
	 */
	अगर (test_bit(RAMROD_COMP_WAIT, &p->ramrod_flags)) अणु
		/* Wait maximum क्रम the current exe_queue length iterations plus
		 * one (क्रम the current pending command).
		 */
		पूर्णांक max_iterations = bnx2x_exe_queue_length(&o->exe_queue) + 1;

		जबतक (!bnx2x_exe_queue_empty(&o->exe_queue) &&
		       max_iterations--) अणु

			/* Wait क्रम the current command to complete */
			rc = raw->रुको_comp(bp, raw);
			अगर (rc)
				वापस rc;

			/* Make a next step */
			rc = __bnx2x_vlan_mac_execute_step(bp,
							   p->vlan_mac_obj,
							   &p->ramrod_flags);
			अगर (rc < 0)
				वापस rc;
		पूर्ण

		वापस 0;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * bnx2x_vlan_mac_del_all - delete elements with given vlan_mac_flags spec
 *
 * @bp:			device handle
 * @o:			vlan object info
 * @vlan_mac_flags:	vlan flags
 * @ramrod_flags:	execution flags to be used क्रम this deletion
 *
 * अगर the last operation has completed successfully and there are no
 * more elements left, positive value अगर the last operation has completed
 * successfully and there are more previously configured elements, negative
 * value is current operation has failed.
 */
अटल पूर्णांक bnx2x_vlan_mac_del_all(काष्ठा bnx2x *bp,
				  काष्ठा bnx2x_vlan_mac_obj *o,
				  अचिन्हित दीर्घ *vlan_mac_flags,
				  अचिन्हित दीर्घ *ramrod_flags)
अणु
	काष्ठा bnx2x_vlan_mac_registry_elem *pos = शून्य;
	काष्ठा bnx2x_vlan_mac_ramrod_params p;
	काष्ठा bnx2x_exe_queue_obj *exeq = &o->exe_queue;
	काष्ठा bnx2x_exeq_elem *exeq_pos, *exeq_pos_n;
	अचिन्हित दीर्घ flags;
	पूर्णांक पढ़ो_lock;
	पूर्णांक rc = 0;

	/* Clear pending commands first */

	spin_lock_bh(&exeq->lock);

	list_क्रम_each_entry_safe(exeq_pos, exeq_pos_n, &exeq->exe_queue, link) अणु
		flags = exeq_pos->cmd_data.vlan_mac.vlan_mac_flags;
		अगर (BNX2X_VLAN_MAC_CMP_FLAGS(flags) ==
		    BNX2X_VLAN_MAC_CMP_FLAGS(*vlan_mac_flags)) अणु
			rc = exeq->हटाओ(bp, exeq->owner, exeq_pos);
			अगर (rc) अणु
				BNX2X_ERR("Failed to remove command\n");
				spin_unlock_bh(&exeq->lock);
				वापस rc;
			पूर्ण
			list_del(&exeq_pos->link);
			bnx2x_exe_queue_मुक्त_elem(bp, exeq_pos);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&exeq->lock);

	/* Prepare a command request */
	स_रखो(&p, 0, माप(p));
	p.vlan_mac_obj = o;
	p.ramrod_flags = *ramrod_flags;
	p.user_req.cmd = BNX2X_VLAN_MAC_DEL;

	/* Add all but the last VLAN-MAC to the execution queue without actually
	 * execution anything.
	 */
	__clear_bit(RAMROD_COMP_WAIT, &p.ramrod_flags);
	__clear_bit(RAMROD_EXEC, &p.ramrod_flags);
	__clear_bit(RAMROD_CONT, &p.ramrod_flags);

	DP(BNX2X_MSG_SP, "vlan_mac_del_all -- taking vlan_mac_lock (reader)\n");
	पढ़ो_lock = bnx2x_vlan_mac_h_पढ़ो_lock(bp, o);
	अगर (पढ़ो_lock != 0)
		वापस पढ़ो_lock;

	list_क्रम_each_entry(pos, &o->head, link) अणु
		flags = pos->vlan_mac_flags;
		अगर (BNX2X_VLAN_MAC_CMP_FLAGS(flags) ==
		    BNX2X_VLAN_MAC_CMP_FLAGS(*vlan_mac_flags)) अणु
			p.user_req.vlan_mac_flags = pos->vlan_mac_flags;
			स_नकल(&p.user_req.u, &pos->u, माप(pos->u));
			rc = bnx2x_config_vlan_mac(bp, &p);
			अगर (rc < 0) अणु
				BNX2X_ERR("Failed to add a new DEL command\n");
				bnx2x_vlan_mac_h_पढ़ो_unlock(bp, o);
				वापस rc;
			पूर्ण
		पूर्ण
	पूर्ण

	DP(BNX2X_MSG_SP, "vlan_mac_del_all -- releasing vlan_mac_lock (reader)\n");
	bnx2x_vlan_mac_h_पढ़ो_unlock(bp, o);

	p.ramrod_flags = *ramrod_flags;
	__set_bit(RAMROD_CONT, &p.ramrod_flags);

	वापस bnx2x_config_vlan_mac(bp, &p);
पूर्ण

अटल अंतरभूत व्योम bnx2x_init_raw_obj(काष्ठा bnx2x_raw_obj *raw, u8 cl_id,
	u32 cid, u8 func_id, व्योम *rdata, dma_addr_t rdata_mapping, पूर्णांक state,
	अचिन्हित दीर्घ *pstate, bnx2x_obj_type type)
अणु
	raw->func_id = func_id;
	raw->cid = cid;
	raw->cl_id = cl_id;
	raw->rdata = rdata;
	raw->rdata_mapping = rdata_mapping;
	raw->state = state;
	raw->pstate = pstate;
	raw->obj_type = type;
	raw->check_pending = bnx2x_raw_check_pending;
	raw->clear_pending = bnx2x_raw_clear_pending;
	raw->set_pending = bnx2x_raw_set_pending;
	raw->रुको_comp = bnx2x_raw_रुको;
पूर्ण

अटल अंतरभूत व्योम bnx2x_init_vlan_mac_common(काष्ठा bnx2x_vlan_mac_obj *o,
	u8 cl_id, u32 cid, u8 func_id, व्योम *rdata, dma_addr_t rdata_mapping,
	पूर्णांक state, अचिन्हित दीर्घ *pstate, bnx2x_obj_type type,
	काष्ठा bnx2x_credit_pool_obj *macs_pool,
	काष्ठा bnx2x_credit_pool_obj *vlans_pool)
अणु
	INIT_LIST_HEAD(&o->head);
	o->head_पढ़ोer = 0;
	o->head_exe_request = false;
	o->saved_ramrod_flags = 0;

	o->macs_pool = macs_pool;
	o->vlans_pool = vlans_pool;

	o->delete_all = bnx2x_vlan_mac_del_all;
	o->restore = bnx2x_vlan_mac_restore;
	o->complete = bnx2x_complete_vlan_mac;
	o->रुको = bnx2x_रुको_vlan_mac;

	bnx2x_init_raw_obj(&o->raw, cl_id, cid, func_id, rdata, rdata_mapping,
			   state, pstate, type);
पूर्ण

व्योम bnx2x_init_mac_obj(काष्ठा bnx2x *bp,
			काष्ठा bnx2x_vlan_mac_obj *mac_obj,
			u8 cl_id, u32 cid, u8 func_id, व्योम *rdata,
			dma_addr_t rdata_mapping, पूर्णांक state,
			अचिन्हित दीर्घ *pstate, bnx2x_obj_type type,
			काष्ठा bnx2x_credit_pool_obj *macs_pool)
अणु
	जोड़ bnx2x_qable_obj *qable_obj = (जोड़ bnx2x_qable_obj *)mac_obj;

	bnx2x_init_vlan_mac_common(mac_obj, cl_id, cid, func_id, rdata,
				   rdata_mapping, state, pstate, type,
				   macs_pool, शून्य);

	/* CAM credit pool handling */
	mac_obj->get_credit = bnx2x_get_credit_mac;
	mac_obj->put_credit = bnx2x_put_credit_mac;
	mac_obj->get_cam_offset = bnx2x_get_cam_offset_mac;
	mac_obj->put_cam_offset = bnx2x_put_cam_offset_mac;

	अगर (CHIP_IS_E1x(bp)) अणु
		mac_obj->set_one_rule      = bnx2x_set_one_mac_e1x;
		mac_obj->check_del         = bnx2x_check_mac_del;
		mac_obj->check_add         = bnx2x_check_mac_add;
		mac_obj->check_move        = bnx2x_check_move_always_err;
		mac_obj->ramrod_cmd        = RAMROD_CMD_ID_ETH_SET_MAC;

		/* Exe Queue */
		bnx2x_exe_queue_init(bp,
				     &mac_obj->exe_queue, 1, qable_obj,
				     bnx2x_validate_vlan_mac,
				     bnx2x_हटाओ_vlan_mac,
				     bnx2x_optimize_vlan_mac,
				     bnx2x_execute_vlan_mac,
				     bnx2x_exeq_get_mac);
	पूर्ण अन्यथा अणु
		mac_obj->set_one_rule      = bnx2x_set_one_mac_e2;
		mac_obj->check_del         = bnx2x_check_mac_del;
		mac_obj->check_add         = bnx2x_check_mac_add;
		mac_obj->check_move        = bnx2x_check_move;
		mac_obj->ramrod_cmd        =
			RAMROD_CMD_ID_ETH_CLASSIFICATION_RULES;
		mac_obj->get_n_elements    = bnx2x_get_n_elements;

		/* Exe Queue */
		bnx2x_exe_queue_init(bp,
				     &mac_obj->exe_queue, CLASSIFY_RULES_COUNT,
				     qable_obj, bnx2x_validate_vlan_mac,
				     bnx2x_हटाओ_vlan_mac,
				     bnx2x_optimize_vlan_mac,
				     bnx2x_execute_vlan_mac,
				     bnx2x_exeq_get_mac);
	पूर्ण
पूर्ण

व्योम bnx2x_init_vlan_obj(काष्ठा bnx2x *bp,
			 काष्ठा bnx2x_vlan_mac_obj *vlan_obj,
			 u8 cl_id, u32 cid, u8 func_id, व्योम *rdata,
			 dma_addr_t rdata_mapping, पूर्णांक state,
			 अचिन्हित दीर्घ *pstate, bnx2x_obj_type type,
			 काष्ठा bnx2x_credit_pool_obj *vlans_pool)
अणु
	जोड़ bnx2x_qable_obj *qable_obj = (जोड़ bnx2x_qable_obj *)vlan_obj;

	bnx2x_init_vlan_mac_common(vlan_obj, cl_id, cid, func_id, rdata,
				   rdata_mapping, state, pstate, type, शून्य,
				   vlans_pool);

	vlan_obj->get_credit = bnx2x_get_credit_vlan;
	vlan_obj->put_credit = bnx2x_put_credit_vlan;
	vlan_obj->get_cam_offset = bnx2x_get_cam_offset_vlan;
	vlan_obj->put_cam_offset = bnx2x_put_cam_offset_vlan;

	अगर (CHIP_IS_E1x(bp)) अणु
		BNX2X_ERR("Do not support chips others than E2 and newer\n");
		BUG();
	पूर्ण अन्यथा अणु
		vlan_obj->set_one_rule      = bnx2x_set_one_vlan_e2;
		vlan_obj->check_del         = bnx2x_check_vlan_del;
		vlan_obj->check_add         = bnx2x_check_vlan_add;
		vlan_obj->check_move        = bnx2x_check_move;
		vlan_obj->ramrod_cmd        =
			RAMROD_CMD_ID_ETH_CLASSIFICATION_RULES;
		vlan_obj->get_n_elements    = bnx2x_get_n_elements;

		/* Exe Queue */
		bnx2x_exe_queue_init(bp,
				     &vlan_obj->exe_queue, CLASSIFY_RULES_COUNT,
				     qable_obj, bnx2x_validate_vlan_mac,
				     bnx2x_हटाओ_vlan_mac,
				     bnx2x_optimize_vlan_mac,
				     bnx2x_execute_vlan_mac,
				     bnx2x_exeq_get_vlan);
	पूर्ण
पूर्ण

व्योम bnx2x_init_vlan_mac_obj(काष्ठा bnx2x *bp,
			     काष्ठा bnx2x_vlan_mac_obj *vlan_mac_obj,
			     u8 cl_id, u32 cid, u8 func_id, व्योम *rdata,
			     dma_addr_t rdata_mapping, पूर्णांक state,
			     अचिन्हित दीर्घ *pstate, bnx2x_obj_type type,
			     काष्ठा bnx2x_credit_pool_obj *macs_pool,
			     काष्ठा bnx2x_credit_pool_obj *vlans_pool)
अणु
	जोड़ bnx2x_qable_obj *qable_obj =
		(जोड़ bnx2x_qable_obj *)vlan_mac_obj;

	bnx2x_init_vlan_mac_common(vlan_mac_obj, cl_id, cid, func_id, rdata,
				   rdata_mapping, state, pstate, type,
				   macs_pool, vlans_pool);

	/* CAM pool handling */
	vlan_mac_obj->get_credit = bnx2x_get_credit_vlan_mac;
	vlan_mac_obj->put_credit = bnx2x_put_credit_vlan_mac;
	/* CAM offset is relevant क्रम 57710 and 57711 chips only which have a
	 * single CAM क्रम both MACs and VLAN-MAC pairs. So the offset
	 * will be taken from MACs' pool object only.
	 */
	vlan_mac_obj->get_cam_offset = bnx2x_get_cam_offset_mac;
	vlan_mac_obj->put_cam_offset = bnx2x_put_cam_offset_mac;

	अगर (CHIP_IS_E1(bp)) अणु
		BNX2X_ERR("Do not support chips others than E2\n");
		BUG();
	पूर्ण अन्यथा अगर (CHIP_IS_E1H(bp)) अणु
		vlan_mac_obj->set_one_rule      = bnx2x_set_one_vlan_mac_e1h;
		vlan_mac_obj->check_del         = bnx2x_check_vlan_mac_del;
		vlan_mac_obj->check_add         = bnx2x_check_vlan_mac_add;
		vlan_mac_obj->check_move        = bnx2x_check_move_always_err;
		vlan_mac_obj->ramrod_cmd        = RAMROD_CMD_ID_ETH_SET_MAC;

		/* Exe Queue */
		bnx2x_exe_queue_init(bp,
				     &vlan_mac_obj->exe_queue, 1, qable_obj,
				     bnx2x_validate_vlan_mac,
				     bnx2x_हटाओ_vlan_mac,
				     bnx2x_optimize_vlan_mac,
				     bnx2x_execute_vlan_mac,
				     bnx2x_exeq_get_vlan_mac);
	पूर्ण अन्यथा अणु
		vlan_mac_obj->set_one_rule      = bnx2x_set_one_vlan_mac_e2;
		vlan_mac_obj->check_del         = bnx2x_check_vlan_mac_del;
		vlan_mac_obj->check_add         = bnx2x_check_vlan_mac_add;
		vlan_mac_obj->check_move        = bnx2x_check_move;
		vlan_mac_obj->ramrod_cmd        =
			RAMROD_CMD_ID_ETH_CLASSIFICATION_RULES;

		/* Exe Queue */
		bnx2x_exe_queue_init(bp,
				     &vlan_mac_obj->exe_queue,
				     CLASSIFY_RULES_COUNT,
				     qable_obj, bnx2x_validate_vlan_mac,
				     bnx2x_हटाओ_vlan_mac,
				     bnx2x_optimize_vlan_mac,
				     bnx2x_execute_vlan_mac,
				     bnx2x_exeq_get_vlan_mac);
	पूर्ण
पूर्ण
/* RX_MODE verbs: DROP_ALL/ACCEPT_ALL/ACCEPT_ALL_MULTI/ACCEPT_ALL_VLAN/NORMAL */
अटल अंतरभूत व्योम __storm_स_रखो_mac_filters(काष्ठा bnx2x *bp,
			काष्ठा tstorm_eth_mac_filter_config *mac_filters,
			u16 pf_id)
अणु
	माप_प्रकार size = माप(काष्ठा tstorm_eth_mac_filter_config);

	u32 addr = BAR_TSTRORM_INTMEM +
			TSTORM_MAC_FILTER_CONFIG_OFFSET(pf_id);

	__storm_स_रखो_काष्ठा(bp, addr, size, (u32 *)mac_filters);
पूर्ण

अटल पूर्णांक bnx2x_set_rx_mode_e1x(काष्ठा bnx2x *bp,
				 काष्ठा bnx2x_rx_mode_ramrod_params *p)
अणु
	/* update the bp MAC filter काष्ठाure */
	u32 mask = (1 << p->cl_id);

	काष्ठा tstorm_eth_mac_filter_config *mac_filters =
		(काष्ठा tstorm_eth_mac_filter_config *)p->rdata;

	/* initial setting is drop-all */
	u8 drop_all_ucast = 1, drop_all_mcast = 1;
	u8 accp_all_ucast = 0, accp_all_bcast = 0, accp_all_mcast = 0;
	u8 unmatched_unicast = 0;

    /* In e1x there we only take पूर्णांकo account rx accept flag since tx चयनing
     * isn't enabled. */
	अगर (test_bit(BNX2X_ACCEPT_UNICAST, &p->rx_accept_flags))
		/* accept matched ucast */
		drop_all_ucast = 0;

	अगर (test_bit(BNX2X_ACCEPT_MULTICAST, &p->rx_accept_flags))
		/* accept matched mcast */
		drop_all_mcast = 0;

	अगर (test_bit(BNX2X_ACCEPT_ALL_UNICAST, &p->rx_accept_flags)) अणु
		/* accept all mcast */
		drop_all_ucast = 0;
		accp_all_ucast = 1;
	पूर्ण
	अगर (test_bit(BNX2X_ACCEPT_ALL_MULTICAST, &p->rx_accept_flags)) अणु
		/* accept all mcast */
		drop_all_mcast = 0;
		accp_all_mcast = 1;
	पूर्ण
	अगर (test_bit(BNX2X_ACCEPT_BROADCAST, &p->rx_accept_flags))
		/* accept (all) bcast */
		accp_all_bcast = 1;
	अगर (test_bit(BNX2X_ACCEPT_UNMATCHED, &p->rx_accept_flags))
		/* accept unmatched unicasts */
		unmatched_unicast = 1;

	mac_filters->ucast_drop_all = drop_all_ucast ?
		mac_filters->ucast_drop_all | mask :
		mac_filters->ucast_drop_all & ~mask;

	mac_filters->mcast_drop_all = drop_all_mcast ?
		mac_filters->mcast_drop_all | mask :
		mac_filters->mcast_drop_all & ~mask;

	mac_filters->ucast_accept_all = accp_all_ucast ?
		mac_filters->ucast_accept_all | mask :
		mac_filters->ucast_accept_all & ~mask;

	mac_filters->mcast_accept_all = accp_all_mcast ?
		mac_filters->mcast_accept_all | mask :
		mac_filters->mcast_accept_all & ~mask;

	mac_filters->bcast_accept_all = accp_all_bcast ?
		mac_filters->bcast_accept_all | mask :
		mac_filters->bcast_accept_all & ~mask;

	mac_filters->unmatched_unicast = unmatched_unicast ?
		mac_filters->unmatched_unicast | mask :
		mac_filters->unmatched_unicast & ~mask;

	DP(BNX2X_MSG_SP, "drop_ucast 0x%x\ndrop_mcast 0x%x\n accp_ucast 0x%x\n"
			 "accp_mcast 0x%x\naccp_bcast 0x%x\n",
	   mac_filters->ucast_drop_all, mac_filters->mcast_drop_all,
	   mac_filters->ucast_accept_all, mac_filters->mcast_accept_all,
	   mac_filters->bcast_accept_all);

	/* ग_लिखो the MAC filter काष्ठाure*/
	__storm_स_रखो_mac_filters(bp, mac_filters, p->func_id);

	/* The operation is completed */
	clear_bit(p->state, p->pstate);
	smp_mb__after_atomic();

	वापस 0;
पूर्ण

/* Setup ramrod data */
अटल अंतरभूत व्योम bnx2x_rx_mode_set_rdata_hdr_e2(u32 cid,
				काष्ठा eth_classअगरy_header *hdr,
				u8 rule_cnt)
अणु
	hdr->echo = cpu_to_le32(cid);
	hdr->rule_cnt = rule_cnt;
पूर्ण

अटल अंतरभूत व्योम bnx2x_rx_mode_set_cmd_state_e2(काष्ठा bnx2x *bp,
				अचिन्हित दीर्घ *accept_flags,
				काष्ठा eth_filter_rules_cmd *cmd,
				bool clear_accept_all)
अणु
	u16 state;

	/* start with 'drop-all' */
	state = ETH_FILTER_RULES_CMD_UCAST_DROP_ALL |
		ETH_FILTER_RULES_CMD_MCAST_DROP_ALL;

	अगर (test_bit(BNX2X_ACCEPT_UNICAST, accept_flags))
		state &= ~ETH_FILTER_RULES_CMD_UCAST_DROP_ALL;

	अगर (test_bit(BNX2X_ACCEPT_MULTICAST, accept_flags))
		state &= ~ETH_FILTER_RULES_CMD_MCAST_DROP_ALL;

	अगर (test_bit(BNX2X_ACCEPT_ALL_UNICAST, accept_flags)) अणु
		state &= ~ETH_FILTER_RULES_CMD_UCAST_DROP_ALL;
		state |= ETH_FILTER_RULES_CMD_UCAST_ACCEPT_ALL;
	पूर्ण

	अगर (test_bit(BNX2X_ACCEPT_ALL_MULTICAST, accept_flags)) अणु
		state |= ETH_FILTER_RULES_CMD_MCAST_ACCEPT_ALL;
		state &= ~ETH_FILTER_RULES_CMD_MCAST_DROP_ALL;
	पूर्ण

	अगर (test_bit(BNX2X_ACCEPT_BROADCAST, accept_flags))
		state |= ETH_FILTER_RULES_CMD_BCAST_ACCEPT_ALL;

	अगर (test_bit(BNX2X_ACCEPT_UNMATCHED, accept_flags)) अणु
		state &= ~ETH_FILTER_RULES_CMD_UCAST_DROP_ALL;
		state |= ETH_FILTER_RULES_CMD_UCAST_ACCEPT_UNMATCHED;
	पूर्ण

	अगर (test_bit(BNX2X_ACCEPT_ANY_VLAN, accept_flags))
		state |= ETH_FILTER_RULES_CMD_ACCEPT_ANY_VLAN;

	/* Clear ACCEPT_ALL_XXX flags क्रम FCoE L2 Queue */
	अगर (clear_accept_all) अणु
		state &= ~ETH_FILTER_RULES_CMD_MCAST_ACCEPT_ALL;
		state &= ~ETH_FILTER_RULES_CMD_BCAST_ACCEPT_ALL;
		state &= ~ETH_FILTER_RULES_CMD_UCAST_ACCEPT_ALL;
		state &= ~ETH_FILTER_RULES_CMD_UCAST_ACCEPT_UNMATCHED;
	पूर्ण

	cmd->state = cpu_to_le16(state);
पूर्ण

अटल पूर्णांक bnx2x_set_rx_mode_e2(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_rx_mode_ramrod_params *p)
अणु
	काष्ठा eth_filter_rules_ramrod_data *data = p->rdata;
	पूर्णांक rc;
	u8 rule_idx = 0;

	/* Reset the ramrod data buffer */
	स_रखो(data, 0, माप(*data));

	/* Setup ramrod data */

	/* Tx (पूर्णांकernal चयनing) */
	अगर (test_bit(RAMROD_TX, &p->ramrod_flags)) अणु
		data->rules[rule_idx].client_id = p->cl_id;
		data->rules[rule_idx].func_id = p->func_id;

		data->rules[rule_idx].cmd_general_data =
			ETH_FILTER_RULES_CMD_TX_CMD;

		bnx2x_rx_mode_set_cmd_state_e2(bp, &p->tx_accept_flags,
					       &(data->rules[rule_idx++]),
					       false);
	पूर्ण

	/* Rx */
	अगर (test_bit(RAMROD_RX, &p->ramrod_flags)) अणु
		data->rules[rule_idx].client_id = p->cl_id;
		data->rules[rule_idx].func_id = p->func_id;

		data->rules[rule_idx].cmd_general_data =
			ETH_FILTER_RULES_CMD_RX_CMD;

		bnx2x_rx_mode_set_cmd_state_e2(bp, &p->rx_accept_flags,
					       &(data->rules[rule_idx++]),
					       false);
	पूर्ण

	/* If FCoE Queue configuration has been requested configure the Rx and
	 * पूर्णांकernal चयनing modes क्रम this queue in separate rules.
	 *
	 * FCoE queue shell never be set to ACCEPT_ALL packets of any sort:
	 * MCAST_ALL, UCAST_ALL, BCAST_ALL and UNMATCHED.
	 */
	अगर (test_bit(BNX2X_RX_MODE_FCOE_ETH, &p->rx_mode_flags)) अणु
		/*  Tx (पूर्णांकernal चयनing) */
		अगर (test_bit(RAMROD_TX, &p->ramrod_flags)) अणु
			data->rules[rule_idx].client_id = bnx2x_fcoe(bp, cl_id);
			data->rules[rule_idx].func_id = p->func_id;

			data->rules[rule_idx].cmd_general_data =
						ETH_FILTER_RULES_CMD_TX_CMD;

			bnx2x_rx_mode_set_cmd_state_e2(bp, &p->tx_accept_flags,
						       &(data->rules[rule_idx]),
						       true);
			rule_idx++;
		पूर्ण

		/* Rx */
		अगर (test_bit(RAMROD_RX, &p->ramrod_flags)) अणु
			data->rules[rule_idx].client_id = bnx2x_fcoe(bp, cl_id);
			data->rules[rule_idx].func_id = p->func_id;

			data->rules[rule_idx].cmd_general_data =
						ETH_FILTER_RULES_CMD_RX_CMD;

			bnx2x_rx_mode_set_cmd_state_e2(bp, &p->rx_accept_flags,
						       &(data->rules[rule_idx]),
						       true);
			rule_idx++;
		पूर्ण
	पूर्ण

	/* Set the ramrod header (most importantly - number of rules to
	 * configure).
	 */
	bnx2x_rx_mode_set_rdata_hdr_e2(p->cid, &data->header, rule_idx);

	DP(BNX2X_MSG_SP, "About to configure %d rules, rx_accept_flags 0x%lx, tx_accept_flags 0x%lx\n",
			 data->header.rule_cnt, p->rx_accept_flags,
			 p->tx_accept_flags);

	/* No need क्रम an explicit memory barrier here as दीर्घ as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * पढ़ो. If the memory पढ़ो is हटाओd we will have to put a
	 * full memory barrier there (inside bnx2x_sp_post()).
	 */

	/* Send a ramrod */
	rc = bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_FILTER_RULES, p->cid,
			   U64_HI(p->rdata_mapping),
			   U64_LO(p->rdata_mapping),
			   ETH_CONNECTION_TYPE);
	अगर (rc)
		वापस rc;

	/* Ramrod completion is pending */
	वापस 1;
पूर्ण

अटल पूर्णांक bnx2x_रुको_rx_mode_comp_e2(काष्ठा bnx2x *bp,
				      काष्ठा bnx2x_rx_mode_ramrod_params *p)
अणु
	वापस bnx2x_state_रुको(bp, p->state, p->pstate);
पूर्ण

अटल पूर्णांक bnx2x_empty_rx_mode_रुको(काष्ठा bnx2x *bp,
				    काष्ठा bnx2x_rx_mode_ramrod_params *p)
अणु
	/* Do nothing */
	वापस 0;
पूर्ण

पूर्णांक bnx2x_config_rx_mode(काष्ठा bnx2x *bp,
			 काष्ठा bnx2x_rx_mode_ramrod_params *p)
अणु
	पूर्णांक rc;

	/* Configure the new classअगरication in the chip */
	rc = p->rx_mode_obj->config_rx_mode(bp, p);
	अगर (rc < 0)
		वापस rc;

	/* Wait क्रम a ramrod completion अगर was requested */
	अगर (test_bit(RAMROD_COMP_WAIT, &p->ramrod_flags)) अणु
		rc = p->rx_mode_obj->रुको_comp(bp, p);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस rc;
पूर्ण

व्योम bnx2x_init_rx_mode_obj(काष्ठा bnx2x *bp,
			    काष्ठा bnx2x_rx_mode_obj *o)
अणु
	अगर (CHIP_IS_E1x(bp)) अणु
		o->रुको_comp      = bnx2x_empty_rx_mode_रुको;
		o->config_rx_mode = bnx2x_set_rx_mode_e1x;
	पूर्ण अन्यथा अणु
		o->रुको_comp      = bnx2x_रुको_rx_mode_comp_e2;
		o->config_rx_mode = bnx2x_set_rx_mode_e2;
	पूर्ण
पूर्ण

/********************* Multicast verbs: SET, CLEAR ****************************/
अटल अंतरभूत u8 bnx2x_mcast_bin_from_mac(u8 *mac)
अणु
	वापस (crc32c_le(0, mac, ETH_ALEN) >> 24) & 0xff;
पूर्ण

काष्ठा bnx2x_mcast_mac_elem अणु
	काष्ठा list_head link;
	u8 mac[ETH_ALEN];
	u8 pad[2]; /* For a natural alignment of the following buffer */
पूर्ण;

काष्ठा bnx2x_mcast_bin_elem अणु
	काष्ठा list_head link;
	पूर्णांक bin;
	पूर्णांक type; /* BNX2X_MCAST_CMD_SET_अणुADD, DELपूर्ण */
पूर्ण;

जोड़ bnx2x_mcast_elem अणु
	काष्ठा bnx2x_mcast_bin_elem bin_elem;
	काष्ठा bnx2x_mcast_mac_elem mac_elem;
पूर्ण;

काष्ठा bnx2x_mcast_elem_group अणु
	काष्ठा list_head mcast_group_link;
	जोड़ bnx2x_mcast_elem mcast_elems[];
पूर्ण;

#घोषणा MCAST_MAC_ELEMS_PER_PG \
	((PAGE_SIZE - माप(काष्ठा bnx2x_mcast_elem_group)) / \
	माप(जोड़ bnx2x_mcast_elem))

काष्ठा bnx2x_pending_mcast_cmd अणु
	काष्ठा list_head link;
	काष्ठा list_head group_head;
	पूर्णांक type; /* BNX2X_MCAST_CMD_X */
	जोड़ अणु
		काष्ठा list_head macs_head;
		u32 macs_num; /* Needed क्रम DEL command */
		पूर्णांक next_bin; /* Needed क्रम RESTORE flow with aprox match */
	पूर्ण data;

	bool set_convert; /* in हाल type == BNX2X_MCAST_CMD_SET, this is set
			   * when macs_head had been converted to a list of
			   * bnx2x_mcast_bin_elem.
			   */

	bool करोne; /* set to true, when the command has been handled,
		    * practically used in 57712 handling only, where one pending
		    * command may be handled in a few operations. As दीर्घ as क्रम
		    * other chips every operation handling is completed in a
		    * single ramrod, there is no need to utilize this field.
		    */
पूर्ण;

अटल पूर्णांक bnx2x_mcast_रुको(काष्ठा bnx2x *bp,
			    काष्ठा bnx2x_mcast_obj *o)
अणु
	अगर (bnx2x_state_रुको(bp, o->sched_state, o->raw.pstate) ||
			o->raw.रुको_comp(bp, &o->raw))
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल व्योम bnx2x_मुक्त_groups(काष्ठा list_head *mcast_group_list)
अणु
	काष्ठा bnx2x_mcast_elem_group *current_mcast_group;

	जबतक (!list_empty(mcast_group_list)) अणु
		current_mcast_group = list_first_entry(mcast_group_list,
				      काष्ठा bnx2x_mcast_elem_group,
				      mcast_group_link);
		list_del(&current_mcast_group->mcast_group_link);
		मुक्त_page((अचिन्हित दीर्घ)current_mcast_group);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_mcast_enqueue_cmd(काष्ठा bnx2x *bp,
				   काष्ठा bnx2x_mcast_obj *o,
				   काष्ठा bnx2x_mcast_ramrod_params *p,
				   क्रमागत bnx2x_mcast_cmd cmd)
अणु
	काष्ठा bnx2x_pending_mcast_cmd *new_cmd;
	काष्ठा bnx2x_mcast_list_elem *pos;
	काष्ठा bnx2x_mcast_elem_group *elem_group;
	काष्ठा bnx2x_mcast_mac_elem *mac_elem;
	पूर्णांक total_elems = 0, macs_list_len = 0, offset = 0;

	/* When adding MACs we'll need to store their values */
	अगर (cmd == BNX2X_MCAST_CMD_ADD || cmd == BNX2X_MCAST_CMD_SET)
		macs_list_len = p->mcast_list_len;

	/* If the command is empty ("handle pending commands only"), अवरोध */
	अगर (!p->mcast_list_len)
		वापस 0;

	/* Add mcast is called under spin_lock, thus calling with GFP_ATOMIC */
	new_cmd = kzalloc(माप(*new_cmd), GFP_ATOMIC);
	अगर (!new_cmd)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&new_cmd->data.macs_head);
	INIT_LIST_HEAD(&new_cmd->group_head);
	new_cmd->type = cmd;
	new_cmd->करोne = false;

	DP(BNX2X_MSG_SP, "About to enqueue a new %d command. macs_list_len=%d\n",
	   cmd, macs_list_len);

	चयन (cmd) अणु
	हाल BNX2X_MCAST_CMD_ADD:
	हाल BNX2X_MCAST_CMD_SET:
		/* For a set command, we need to allocate sufficient memory क्रम
		 * all the bins, since we can't analyze at this poपूर्णांक how much
		 * memory would be required.
		 */
		total_elems = macs_list_len;
		अगर (cmd == BNX2X_MCAST_CMD_SET) अणु
			अगर (total_elems < BNX2X_MCAST_BINS_NUM)
				total_elems = BNX2X_MCAST_BINS_NUM;
		पूर्ण
		जबतक (total_elems > 0) अणु
			elem_group = (काष्ठा bnx2x_mcast_elem_group *)
				     __get_मुक्त_page(GFP_ATOMIC | __GFP_ZERO);
			अगर (!elem_group) अणु
				bnx2x_मुक्त_groups(&new_cmd->group_head);
				kमुक्त(new_cmd);
				वापस -ENOMEM;
			पूर्ण
			total_elems -= MCAST_MAC_ELEMS_PER_PG;
			list_add_tail(&elem_group->mcast_group_link,
				      &new_cmd->group_head);
		पूर्ण
		elem_group = list_first_entry(&new_cmd->group_head,
					      काष्ठा bnx2x_mcast_elem_group,
					      mcast_group_link);
		list_क्रम_each_entry(pos, &p->mcast_list, link) अणु
			mac_elem = &elem_group->mcast_elems[offset].mac_elem;
			स_नकल(mac_elem->mac, pos->mac, ETH_ALEN);
			/* Push the MACs of the current command पूर्णांकo the pending
			 * command MACs list: FIFO
			 */
			list_add_tail(&mac_elem->link,
				      &new_cmd->data.macs_head);
			offset++;
			अगर (offset == MCAST_MAC_ELEMS_PER_PG) अणु
				offset = 0;
				elem_group = list_next_entry(elem_group,
							     mcast_group_link);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल BNX2X_MCAST_CMD_DEL:
		new_cmd->data.macs_num = p->mcast_list_len;
		अवरोध;

	हाल BNX2X_MCAST_CMD_RESTORE:
		new_cmd->data.next_bin = 0;
		अवरोध;

	शेष:
		kमुक्त(new_cmd);
		BNX2X_ERR("Unknown command: %d\n", cmd);
		वापस -EINVAL;
	पूर्ण

	/* Push the new pending command to the tail of the pending list: FIFO */
	list_add_tail(&new_cmd->link, &o->pending_cmds_head);

	o->set_sched(o);

	वापस 1;
पूर्ण

/**
 * bnx2x_mcast_get_next_bin - get the next set bin (index)
 *
 * @o:		multicast object info
 * @last:	index to start looking from (including)
 *
 * वापसs the next found (set) bin or a negative value अगर none is found.
 */
अटल अंतरभूत पूर्णांक bnx2x_mcast_get_next_bin(काष्ठा bnx2x_mcast_obj *o, पूर्णांक last)
अणु
	पूर्णांक i, j, inner_start = last % BIT_VEC64_ELEM_SZ;

	क्रम (i = last / BIT_VEC64_ELEM_SZ; i < BNX2X_MCAST_VEC_SZ; i++) अणु
		अगर (o->registry.aprox_match.vec[i])
			क्रम (j = inner_start; j < BIT_VEC64_ELEM_SZ; j++) अणु
				पूर्णांक cur_bit = j + BIT_VEC64_ELEM_SZ * i;
				अगर (BIT_VEC64_TEST_BIT(o->registry.aprox_match.
						       vec, cur_bit)) अणु
					वापस cur_bit;
				पूर्ण
			पूर्ण
		inner_start = 0;
	पूर्ण

	/* None found */
	वापस -1;
पूर्ण

/**
 * bnx2x_mcast_clear_first_bin - find the first set bin and clear it
 *
 * @o:
 *
 * वापसs the index of the found bin or -1 अगर none is found
 */
अटल अंतरभूत पूर्णांक bnx2x_mcast_clear_first_bin(काष्ठा bnx2x_mcast_obj *o)
अणु
	पूर्णांक cur_bit = bnx2x_mcast_get_next_bin(o, 0);

	अगर (cur_bit >= 0)
		BIT_VEC64_CLEAR_BIT(o->registry.aprox_match.vec, cur_bit);

	वापस cur_bit;
पूर्ण

अटल अंतरभूत u8 bnx2x_mcast_get_rx_tx_flag(काष्ठा bnx2x_mcast_obj *o)
अणु
	काष्ठा bnx2x_raw_obj *raw = &o->raw;
	u8 rx_tx_flag = 0;

	अगर ((raw->obj_type == BNX2X_OBJ_TYPE_TX) ||
	    (raw->obj_type == BNX2X_OBJ_TYPE_RX_TX))
		rx_tx_flag |= ETH_MULTICAST_RULES_CMD_TX_CMD;

	अगर ((raw->obj_type == BNX2X_OBJ_TYPE_RX) ||
	    (raw->obj_type == BNX2X_OBJ_TYPE_RX_TX))
		rx_tx_flag |= ETH_MULTICAST_RULES_CMD_RX_CMD;

	वापस rx_tx_flag;
पूर्ण

अटल व्योम bnx2x_mcast_set_one_rule_e2(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_mcast_obj *o, पूर्णांक idx,
					जोड़ bnx2x_mcast_config_data *cfg_data,
					क्रमागत bnx2x_mcast_cmd cmd)
अणु
	काष्ठा bnx2x_raw_obj *r = &o->raw;
	काष्ठा eth_multicast_rules_ramrod_data *data =
		(काष्ठा eth_multicast_rules_ramrod_data *)(r->rdata);
	u8 func_id = r->func_id;
	u8 rx_tx_add_flag = bnx2x_mcast_get_rx_tx_flag(o);
	पूर्णांक bin;

	अगर ((cmd == BNX2X_MCAST_CMD_ADD) || (cmd == BNX2X_MCAST_CMD_RESTORE) ||
	    (cmd == BNX2X_MCAST_CMD_SET_ADD))
		rx_tx_add_flag |= ETH_MULTICAST_RULES_CMD_IS_ADD;

	data->rules[idx].cmd_general_data |= rx_tx_add_flag;

	/* Get a bin and update a bins' vector */
	चयन (cmd) अणु
	हाल BNX2X_MCAST_CMD_ADD:
		bin = bnx2x_mcast_bin_from_mac(cfg_data->mac);
		BIT_VEC64_SET_BIT(o->registry.aprox_match.vec, bin);
		अवरोध;

	हाल BNX2X_MCAST_CMD_DEL:
		/* If there were no more bins to clear
		 * (bnx2x_mcast_clear_first_bin() वापसs -1) then we would
		 * clear any (0xff) bin.
		 * See bnx2x_mcast_validate_e2() क्रम explanation when it may
		 * happen.
		 */
		bin = bnx2x_mcast_clear_first_bin(o);
		अवरोध;

	हाल BNX2X_MCAST_CMD_RESTORE:
		bin = cfg_data->bin;
		अवरोध;

	हाल BNX2X_MCAST_CMD_SET_ADD:
		bin = cfg_data->bin;
		BIT_VEC64_SET_BIT(o->registry.aprox_match.vec, bin);
		अवरोध;

	हाल BNX2X_MCAST_CMD_SET_DEL:
		bin = cfg_data->bin;
		BIT_VEC64_CLEAR_BIT(o->registry.aprox_match.vec, bin);
		अवरोध;

	शेष:
		BNX2X_ERR("Unknown command: %d\n", cmd);
		वापस;
	पूर्ण

	DP(BNX2X_MSG_SP, "%s bin %d\n",
			 ((rx_tx_add_flag & ETH_MULTICAST_RULES_CMD_IS_ADD) ?
			 "Setting"  : "Clearing"), bin);

	data->rules[idx].bin_id    = (u8)bin;
	data->rules[idx].func_id   = func_id;
	data->rules[idx].engine_id = o->engine_id;
पूर्ण

/**
 * bnx2x_mcast_handle_restore_cmd_e2 - restore configuration from the registry
 *
 * @bp:		device handle
 * @o:		multicast object info
 * @start_bin:	index in the registry to start from (including)
 * @rdata_idx:	index in the ramrod data to start from
 *
 * वापसs last handled bin index or -1 अगर all bins have been handled
 */
अटल अंतरभूत पूर्णांक bnx2x_mcast_handle_restore_cmd_e2(
	काष्ठा bnx2x *bp, काष्ठा bnx2x_mcast_obj *o , पूर्णांक start_bin,
	पूर्णांक *rdata_idx)
अणु
	पूर्णांक cur_bin, cnt = *rdata_idx;
	जोड़ bnx2x_mcast_config_data cfg_data = अणुशून्यपूर्ण;

	/* go through the registry and configure the bins from it */
	क्रम (cur_bin = bnx2x_mcast_get_next_bin(o, start_bin); cur_bin >= 0;
	    cur_bin = bnx2x_mcast_get_next_bin(o, cur_bin + 1)) अणु

		cfg_data.bin = (u8)cur_bin;
		o->set_one_rule(bp, o, cnt, &cfg_data,
				BNX2X_MCAST_CMD_RESTORE);

		cnt++;

		DP(BNX2X_MSG_SP, "About to configure a bin %d\n", cur_bin);

		/* Break अगर we reached the maximum number
		 * of rules.
		 */
		अगर (cnt >= o->max_cmd_len)
			अवरोध;
	पूर्ण

	*rdata_idx = cnt;

	वापस cur_bin;
पूर्ण

अटल अंतरभूत व्योम bnx2x_mcast_hdl_pending_add_e2(काष्ठा bnx2x *bp,
	काष्ठा bnx2x_mcast_obj *o, काष्ठा bnx2x_pending_mcast_cmd *cmd_pos,
	पूर्णांक *line_idx)
अणु
	काष्ठा bnx2x_mcast_mac_elem *pmac_pos, *pmac_pos_n;
	पूर्णांक cnt = *line_idx;
	जोड़ bnx2x_mcast_config_data cfg_data = अणुशून्यपूर्ण;

	list_क्रम_each_entry_safe(pmac_pos, pmac_pos_n, &cmd_pos->data.macs_head,
				 link) अणु

		cfg_data.mac = &pmac_pos->mac[0];
		o->set_one_rule(bp, o, cnt, &cfg_data, cmd_pos->type);

		cnt++;

		DP(BNX2X_MSG_SP, "About to configure %pM mcast MAC\n",
		   pmac_pos->mac);

		list_del(&pmac_pos->link);

		/* Break अगर we reached the maximum number
		 * of rules.
		 */
		अगर (cnt >= o->max_cmd_len)
			अवरोध;
	पूर्ण

	*line_idx = cnt;

	/* अगर no more MACs to configure - we are करोne */
	अगर (list_empty(&cmd_pos->data.macs_head))
		cmd_pos->करोne = true;
पूर्ण

अटल अंतरभूत व्योम bnx2x_mcast_hdl_pending_del_e2(काष्ठा bnx2x *bp,
	काष्ठा bnx2x_mcast_obj *o, काष्ठा bnx2x_pending_mcast_cmd *cmd_pos,
	पूर्णांक *line_idx)
अणु
	पूर्णांक cnt = *line_idx;

	जबतक (cmd_pos->data.macs_num) अणु
		o->set_one_rule(bp, o, cnt, शून्य, cmd_pos->type);

		cnt++;

		cmd_pos->data.macs_num--;

		DP(BNX2X_MSG_SP, "Deleting MAC. %d left,cnt is %d\n",
		   cmd_pos->data.macs_num, cnt);

		/* Break अगर we reached the maximum
		 * number of rules.
		 */
		अगर (cnt >= o->max_cmd_len)
			अवरोध;
	पूर्ण

	*line_idx = cnt;

	/* If we cleared all bins - we are करोne */
	अगर (!cmd_pos->data.macs_num)
		cmd_pos->करोne = true;
पूर्ण

अटल अंतरभूत व्योम bnx2x_mcast_hdl_pending_restore_e2(काष्ठा bnx2x *bp,
	काष्ठा bnx2x_mcast_obj *o, काष्ठा bnx2x_pending_mcast_cmd *cmd_pos,
	पूर्णांक *line_idx)
अणु
	cmd_pos->data.next_bin = o->hdl_restore(bp, o, cmd_pos->data.next_bin,
						line_idx);

	अगर (cmd_pos->data.next_bin < 0)
		/* If o->set_restore वापसed -1 we are करोne */
		cmd_pos->करोne = true;
	अन्यथा
		/* Start from the next bin next समय */
		cmd_pos->data.next_bin++;
पूर्ण

अटल व्योम
bnx2x_mcast_hdl_pending_set_e2_convert(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_mcast_obj *o,
				       काष्ठा bnx2x_pending_mcast_cmd *cmd_pos)
अणु
	u64 cur[BNX2X_MCAST_VEC_SZ], req[BNX2X_MCAST_VEC_SZ];
	काष्ठा bnx2x_mcast_mac_elem *pmac_pos, *pmac_pos_n;
	काष्ठा bnx2x_mcast_bin_elem *p_item;
	काष्ठा bnx2x_mcast_elem_group *elem_group;
	पूर्णांक cnt = 0, mac_cnt = 0, offset = 0, i;

	स_रखो(req, 0, माप(u64) * BNX2X_MCAST_VEC_SZ);
	स_नकल(cur, o->registry.aprox_match.vec,
	       माप(u64) * BNX2X_MCAST_VEC_SZ);

	/* Fill `current' with the required set of bins to configure */
	list_क्रम_each_entry_safe(pmac_pos, pmac_pos_n, &cmd_pos->data.macs_head,
				 link) अणु
		पूर्णांक bin = bnx2x_mcast_bin_from_mac(pmac_pos->mac);

		DP(BNX2X_MSG_SP, "Set contains %pM mcast MAC\n",
		   pmac_pos->mac);

		BIT_VEC64_SET_BIT(req, bin);
		list_del(&pmac_pos->link);
		mac_cnt++;
	पूर्ण

	/* We no दीर्घer have use क्रम the MACs; Need to re-use memory क्रम
	 * a list that will be used to configure bins.
	 */
	cmd_pos->set_convert = true;
	INIT_LIST_HEAD(&cmd_pos->data.macs_head);
	elem_group = list_first_entry(&cmd_pos->group_head,
				      काष्ठा bnx2x_mcast_elem_group,
				      mcast_group_link);
	क्रम (i = 0; i < BNX2X_MCAST_BINS_NUM; i++) अणु
		bool b_current = !!BIT_VEC64_TEST_BIT(cur, i);
		bool b_required = !!BIT_VEC64_TEST_BIT(req, i);

		अगर (b_current == b_required)
			जारी;

		p_item = &elem_group->mcast_elems[offset].bin_elem;
		p_item->bin = i;
		p_item->type = b_required ? BNX2X_MCAST_CMD_SET_ADD
					  : BNX2X_MCAST_CMD_SET_DEL;
		list_add_tail(&p_item->link , &cmd_pos->data.macs_head);
		cnt++;
		offset++;
		अगर (offset == MCAST_MAC_ELEMS_PER_PG) अणु
			offset = 0;
			elem_group = list_next_entry(elem_group,
						     mcast_group_link);
		पूर्ण
	पूर्ण

	/* We now definitely know how many commands are hiding here.
	 * Also need to correct the disruption we've added to guarantee this
	 * would be enqueued.
	 */
	o->total_pending_num -= (o->max_cmd_len + mac_cnt);
	o->total_pending_num += cnt;

	DP(BNX2X_MSG_SP, "o->total_pending_num=%d\n", o->total_pending_num);
पूर्ण

अटल व्योम
bnx2x_mcast_hdl_pending_set_e2(काष्ठा bnx2x *bp,
			       काष्ठा bnx2x_mcast_obj *o,
			       काष्ठा bnx2x_pending_mcast_cmd *cmd_pos,
			       पूर्णांक *cnt)
अणु
	जोड़ bnx2x_mcast_config_data cfg_data = अणुशून्यपूर्ण;
	काष्ठा bnx2x_mcast_bin_elem *p_item, *p_item_n;

	/* This is actually a 2-part scheme - it starts by converting the MACs
	 * पूर्णांकo a list of bins to be added/हटाओd, and correcting the numbers
	 * on the object. this is now allowed, as we're now sure that all
	 * previous configured requests have alपढ़ोy applied.
	 * The second part is actually adding rules क्रम the newly पूर्णांकroduced
	 * entries [like all the rest of the hdl_pending functions].
	 */
	अगर (!cmd_pos->set_convert)
		bnx2x_mcast_hdl_pending_set_e2_convert(bp, o, cmd_pos);

	list_क्रम_each_entry_safe(p_item, p_item_n, &cmd_pos->data.macs_head,
				 link) अणु
		cfg_data.bin = (u8)p_item->bin;
		o->set_one_rule(bp, o, *cnt, &cfg_data, p_item->type);
		(*cnt)++;

		list_del(&p_item->link);

		/* Break अगर we reached the maximum number of rules. */
		अगर (*cnt >= o->max_cmd_len)
			अवरोध;
	पूर्ण

	/* अगर no more MACs to configure - we are करोne */
	अगर (list_empty(&cmd_pos->data.macs_head))
		cmd_pos->करोne = true;
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_mcast_handle_pending_cmds_e2(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_mcast_ramrod_params *p)
अणु
	काष्ठा bnx2x_pending_mcast_cmd *cmd_pos, *cmd_pos_n;
	पूर्णांक cnt = 0;
	काष्ठा bnx2x_mcast_obj *o = p->mcast_obj;

	list_क्रम_each_entry_safe(cmd_pos, cmd_pos_n, &o->pending_cmds_head,
				 link) अणु
		चयन (cmd_pos->type) अणु
		हाल BNX2X_MCAST_CMD_ADD:
			bnx2x_mcast_hdl_pending_add_e2(bp, o, cmd_pos, &cnt);
			अवरोध;

		हाल BNX2X_MCAST_CMD_DEL:
			bnx2x_mcast_hdl_pending_del_e2(bp, o, cmd_pos, &cnt);
			अवरोध;

		हाल BNX2X_MCAST_CMD_RESTORE:
			bnx2x_mcast_hdl_pending_restore_e2(bp, o, cmd_pos,
							   &cnt);
			अवरोध;

		हाल BNX2X_MCAST_CMD_SET:
			bnx2x_mcast_hdl_pending_set_e2(bp, o, cmd_pos, &cnt);
			अवरोध;

		शेष:
			BNX2X_ERR("Unknown command: %d\n", cmd_pos->type);
			वापस -EINVAL;
		पूर्ण

		/* If the command has been completed - हटाओ it from the list
		 * and मुक्त the memory
		 */
		अगर (cmd_pos->करोne) अणु
			list_del(&cmd_pos->link);
			bnx2x_मुक्त_groups(&cmd_pos->group_head);
			kमुक्त(cmd_pos);
		पूर्ण

		/* Break अगर we reached the maximum number of rules */
		अगर (cnt >= o->max_cmd_len)
			अवरोध;
	पूर्ण

	वापस cnt;
पूर्ण

अटल अंतरभूत व्योम bnx2x_mcast_hdl_add(काष्ठा bnx2x *bp,
	काष्ठा bnx2x_mcast_obj *o, काष्ठा bnx2x_mcast_ramrod_params *p,
	पूर्णांक *line_idx)
अणु
	काष्ठा bnx2x_mcast_list_elem *mlist_pos;
	जोड़ bnx2x_mcast_config_data cfg_data = अणुशून्यपूर्ण;
	पूर्णांक cnt = *line_idx;

	list_क्रम_each_entry(mlist_pos, &p->mcast_list, link) अणु
		cfg_data.mac = mlist_pos->mac;
		o->set_one_rule(bp, o, cnt, &cfg_data, BNX2X_MCAST_CMD_ADD);

		cnt++;

		DP(BNX2X_MSG_SP, "About to configure %pM mcast MAC\n",
		   mlist_pos->mac);
	पूर्ण

	*line_idx = cnt;
पूर्ण

अटल अंतरभूत व्योम bnx2x_mcast_hdl_del(काष्ठा bnx2x *bp,
	काष्ठा bnx2x_mcast_obj *o, काष्ठा bnx2x_mcast_ramrod_params *p,
	पूर्णांक *line_idx)
अणु
	पूर्णांक cnt = *line_idx, i;

	क्रम (i = 0; i < p->mcast_list_len; i++) अणु
		o->set_one_rule(bp, o, cnt, शून्य, BNX2X_MCAST_CMD_DEL);

		cnt++;

		DP(BNX2X_MSG_SP, "Deleting MAC. %d left\n",
				 p->mcast_list_len - i - 1);
	पूर्ण

	*line_idx = cnt;
पूर्ण

/**
 * bnx2x_mcast_handle_current_cmd - send command अगर room
 *
 * @bp:		device handle
 * @p:		ramrod mcast info
 * @cmd:	command
 * @start_cnt:	first line in the ramrod data that may be used
 *
 * This function is called अगरf there is enough place क्रम the current command in
 * the ramrod data.
 * Returns number of lines filled in the ramrod data in total.
 */
अटल अंतरभूत पूर्णांक bnx2x_mcast_handle_current_cmd(काष्ठा bnx2x *bp,
			काष्ठा bnx2x_mcast_ramrod_params *p,
			क्रमागत bnx2x_mcast_cmd cmd,
			पूर्णांक start_cnt)
अणु
	काष्ठा bnx2x_mcast_obj *o = p->mcast_obj;
	पूर्णांक cnt = start_cnt;

	DP(BNX2X_MSG_SP, "p->mcast_list_len=%d\n", p->mcast_list_len);

	चयन (cmd) अणु
	हाल BNX2X_MCAST_CMD_ADD:
		bnx2x_mcast_hdl_add(bp, o, p, &cnt);
		अवरोध;

	हाल BNX2X_MCAST_CMD_DEL:
		bnx2x_mcast_hdl_del(bp, o, p, &cnt);
		अवरोध;

	हाल BNX2X_MCAST_CMD_RESTORE:
		o->hdl_restore(bp, o, 0, &cnt);
		अवरोध;

	शेष:
		BNX2X_ERR("Unknown command: %d\n", cmd);
		वापस -EINVAL;
	पूर्ण

	/* The current command has been handled */
	p->mcast_list_len = 0;

	वापस cnt;
पूर्ण

अटल पूर्णांक bnx2x_mcast_validate_e2(काष्ठा bnx2x *bp,
				   काष्ठा bnx2x_mcast_ramrod_params *p,
				   क्रमागत bnx2x_mcast_cmd cmd)
अणु
	काष्ठा bnx2x_mcast_obj *o = p->mcast_obj;
	पूर्णांक reg_sz = o->get_registry_size(o);

	चयन (cmd) अणु
	/* DEL command deletes all currently configured MACs */
	हाल BNX2X_MCAST_CMD_DEL:
		o->set_registry_size(o, 0);
		fallthrough;

	/* RESTORE command will restore the entire multicast configuration */
	हाल BNX2X_MCAST_CMD_RESTORE:
		/* Here we set the approximate amount of work to करो, which in
		 * fact may be only less as some MACs in postponed ADD
		 * command(s) scheduled beक्रमe this command may fall पूर्णांकo
		 * the same bin and the actual number of bins set in the
		 * registry would be less than we estimated here. See
		 * bnx2x_mcast_set_one_rule_e2() क्रम further details.
		 */
		p->mcast_list_len = reg_sz;
		अवरोध;

	हाल BNX2X_MCAST_CMD_ADD:
	हाल BNX2X_MCAST_CMD_CONT:
		/* Here we assume that all new MACs will fall पूर्णांकo new bins.
		 * However we will correct the real registry size after we
		 * handle all pending commands.
		 */
		o->set_registry_size(o, reg_sz + p->mcast_list_len);
		अवरोध;

	हाल BNX2X_MCAST_CMD_SET:
		/* We can only learn how many commands would actually be used
		 * when this is being configured. So क्रम now, simply guarantee
		 * the command will be enqueued [to refrain from adding logic
		 * that handles this and THEN learns it needs several ramrods].
		 * Just like क्रम ADD/Cont, the mcast_list_len might be an over
		 * estimation; or even more so, since we करोn't take पूर्णांकo
		 * account the possibility of removal of existing bins.
		 */
		o->set_registry_size(o, reg_sz + p->mcast_list_len);
		o->total_pending_num += o->max_cmd_len;
		अवरोध;

	शेष:
		BNX2X_ERR("Unknown command: %d\n", cmd);
		वापस -EINVAL;
	पूर्ण

	/* Increase the total number of MACs pending to be configured */
	o->total_pending_num += p->mcast_list_len;

	वापस 0;
पूर्ण

अटल व्योम bnx2x_mcast_revert_e2(काष्ठा bnx2x *bp,
				      काष्ठा bnx2x_mcast_ramrod_params *p,
				  पूर्णांक old_num_bins,
				  क्रमागत bnx2x_mcast_cmd cmd)
अणु
	काष्ठा bnx2x_mcast_obj *o = p->mcast_obj;

	o->set_registry_size(o, old_num_bins);
	o->total_pending_num -= p->mcast_list_len;

	अगर (cmd == BNX2X_MCAST_CMD_SET)
		o->total_pending_num -= o->max_cmd_len;
पूर्ण

/**
 * bnx2x_mcast_set_rdata_hdr_e2 - sets a header values
 *
 * @bp:		device handle
 * @p:		ramrod parameters
 * @len:	number of rules to handle
 */
अटल अंतरभूत व्योम bnx2x_mcast_set_rdata_hdr_e2(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_mcast_ramrod_params *p,
					u8 len)
अणु
	काष्ठा bnx2x_raw_obj *r = &p->mcast_obj->raw;
	काष्ठा eth_multicast_rules_ramrod_data *data =
		(काष्ठा eth_multicast_rules_ramrod_data *)(r->rdata);

	data->header.echo = cpu_to_le32((r->cid & BNX2X_SWCID_MASK) |
					(BNX2X_FILTER_MCAST_PENDING <<
					 BNX2X_SWCID_SHIFT));
	data->header.rule_cnt = len;
पूर्ण

/**
 * bnx2x_mcast_refresh_registry_e2 - recalculate the actual number of set bins
 *
 * @bp:		device handle
 * @o:
 *
 * Recalculate the actual number of set bins in the registry using Brian
 * Kernighan's algorithm: it's execution complनिकासy is as a number of set bins.
 *
 * वापसs 0 क्रम the compliance with bnx2x_mcast_refresh_registry_e1().
 */
अटल अंतरभूत पूर्णांक bnx2x_mcast_refresh_registry_e2(काष्ठा bnx2x *bp,
						  काष्ठा bnx2x_mcast_obj *o)
अणु
	पूर्णांक i, cnt = 0;
	u64 elem;

	क्रम (i = 0; i < BNX2X_MCAST_VEC_SZ; i++) अणु
		elem = o->registry.aprox_match.vec[i];
		क्रम (; elem; cnt++)
			elem &= elem - 1;
	पूर्ण

	o->set_registry_size(o, cnt);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_mcast_setup_e2(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_mcast_ramrod_params *p,
				क्रमागत bnx2x_mcast_cmd cmd)
अणु
	काष्ठा bnx2x_raw_obj *raw = &p->mcast_obj->raw;
	काष्ठा bnx2x_mcast_obj *o = p->mcast_obj;
	काष्ठा eth_multicast_rules_ramrod_data *data =
		(काष्ठा eth_multicast_rules_ramrod_data *)(raw->rdata);
	पूर्णांक cnt = 0, rc;

	/* Reset the ramrod data buffer */
	स_रखो(data, 0, माप(*data));

	cnt = bnx2x_mcast_handle_pending_cmds_e2(bp, p);

	/* If there are no more pending commands - clear SCHEDULED state */
	अगर (list_empty(&o->pending_cmds_head))
		o->clear_sched(o);

	/* The below may be true अगरf there was enough room in ramrod
	 * data क्रम all pending commands and क्रम the current
	 * command. Otherwise the current command would have been added
	 * to the pending commands and p->mcast_list_len would have been
	 * zeroed.
	 */
	अगर (p->mcast_list_len > 0)
		cnt = bnx2x_mcast_handle_current_cmd(bp, p, cmd, cnt);

	/* We've pulled out some MACs - update the total number of
	 * outstanding.
	 */
	o->total_pending_num -= cnt;

	/* send a ramrod */
	WARN_ON(o->total_pending_num < 0);
	WARN_ON(cnt > o->max_cmd_len);

	bnx2x_mcast_set_rdata_hdr_e2(bp, p, (u8)cnt);

	/* Update a registry size अगर there are no more pending operations.
	 *
	 * We करोn't want to change the value of the registry size अगर there are
	 * pending operations because we want it to always be equal to the
	 * exact or the approximate number (see bnx2x_mcast_validate_e2()) of
	 * set bins after the last requested operation in order to properly
	 * evaluate the size of the next DEL/RESTORE operation.
	 *
	 * Note that we update the registry itself during command(s) handling
	 * - see bnx2x_mcast_set_one_rule_e2(). That's because क्रम 57712 we
	 * aggregate multiple commands (ADD/DEL/RESTORE) पूर्णांकo one ramrod but
	 * with a limited amount of update commands (per MAC/bin) and we करोn't
	 * know in this scope what the actual state of bins configuration is
	 * going to be after this ramrod.
	 */
	अगर (!o->total_pending_num)
		bnx2x_mcast_refresh_registry_e2(bp, o);

	/* If CLEAR_ONLY was requested - करोn't send a ramrod and clear
	 * RAMROD_PENDING status immediately. due to the SET option, it's also
	 * possible that after evaluating the dअगरferences there's no need क्रम
	 * a ramrod. In that हाल, we can skip it as well.
	 */
	अगर (test_bit(RAMROD_DRV_CLR_ONLY, &p->ramrod_flags) || !cnt) अणु
		raw->clear_pending(raw);
		वापस 0;
	पूर्ण अन्यथा अणु
		/* No need क्रम an explicit memory barrier here as दीर्घ as we
		 * ensure the ordering of writing to the SPQ element
		 * and updating of the SPQ producer which involves a memory
		 * पढ़ो. If the memory पढ़ो is हटाओd we will have to put a
		 * full memory barrier there (inside bnx2x_sp_post()).
		 */

		/* Send a ramrod */
		rc = bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_MULTICAST_RULES,
				   raw->cid, U64_HI(raw->rdata_mapping),
				   U64_LO(raw->rdata_mapping),
				   ETH_CONNECTION_TYPE);
		अगर (rc)
			वापस rc;

		/* Ramrod completion is pending */
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_mcast_validate_e1h(काष्ठा bnx2x *bp,
				    काष्ठा bnx2x_mcast_ramrod_params *p,
				    क्रमागत bnx2x_mcast_cmd cmd)
अणु
	अगर (cmd == BNX2X_MCAST_CMD_SET) अणु
		BNX2X_ERR("Can't use `set' command on e1h!\n");
		वापस -EINVAL;
	पूर्ण

	/* Mark, that there is a work to करो */
	अगर ((cmd == BNX2X_MCAST_CMD_DEL) || (cmd == BNX2X_MCAST_CMD_RESTORE))
		p->mcast_list_len = 1;

	वापस 0;
पूर्ण

अटल व्योम bnx2x_mcast_revert_e1h(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_mcast_ramrod_params *p,
				       पूर्णांक old_num_bins,
				       क्रमागत bnx2x_mcast_cmd cmd)
अणु
	/* Do nothing */
पूर्ण

#घोषणा BNX2X_57711_SET_MC_FILTER(filter, bit) \
करो अणु \
	(filter)[(bit) >> 5] |= (1 << ((bit) & 0x1f)); \
पूर्ण जबतक (0)

अटल अंतरभूत व्योम bnx2x_mcast_hdl_add_e1h(काष्ठा bnx2x *bp,
					   काष्ठा bnx2x_mcast_obj *o,
					   काष्ठा bnx2x_mcast_ramrod_params *p,
					   u32 *mc_filter)
अणु
	काष्ठा bnx2x_mcast_list_elem *mlist_pos;
	पूर्णांक bit;

	list_क्रम_each_entry(mlist_pos, &p->mcast_list, link) अणु
		bit = bnx2x_mcast_bin_from_mac(mlist_pos->mac);
		BNX2X_57711_SET_MC_FILTER(mc_filter, bit);

		DP(BNX2X_MSG_SP, "About to configure %pM mcast MAC, bin %d\n",
		   mlist_pos->mac, bit);

		/* bookkeeping... */
		BIT_VEC64_SET_BIT(o->registry.aprox_match.vec,
				  bit);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bnx2x_mcast_hdl_restore_e1h(काष्ठा bnx2x *bp,
	काष्ठा bnx2x_mcast_obj *o, काष्ठा bnx2x_mcast_ramrod_params *p,
	u32 *mc_filter)
अणु
	पूर्णांक bit;

	क्रम (bit = bnx2x_mcast_get_next_bin(o, 0);
	     bit >= 0;
	     bit = bnx2x_mcast_get_next_bin(o, bit + 1)) अणु
		BNX2X_57711_SET_MC_FILTER(mc_filter, bit);
		DP(BNX2X_MSG_SP, "About to set bin %d\n", bit);
	पूर्ण
पूर्ण

/* On 57711 we ग_लिखो the multicast MACs' approximate match
 * table by directly पूर्णांकo the TSTORM's internal RAM. So we don't
 * really need to handle any tricks to make it work.
 */
अटल पूर्णांक bnx2x_mcast_setup_e1h(काष्ठा bnx2x *bp,
				 काष्ठा bnx2x_mcast_ramrod_params *p,
				 क्रमागत bnx2x_mcast_cmd cmd)
अणु
	पूर्णांक i;
	काष्ठा bnx2x_mcast_obj *o = p->mcast_obj;
	काष्ठा bnx2x_raw_obj *r = &o->raw;

	/* If CLEAR_ONLY has been requested - clear the registry
	 * and clear a pending bit.
	 */
	अगर (!test_bit(RAMROD_DRV_CLR_ONLY, &p->ramrod_flags)) अणु
		u32 mc_filter[MC_HASH_SIZE] = अणु0पूर्ण;

		/* Set the multicast filter bits beक्रमe writing it पूर्णांकo
		 * the पूर्णांकernal memory.
		 */
		चयन (cmd) अणु
		हाल BNX2X_MCAST_CMD_ADD:
			bnx2x_mcast_hdl_add_e1h(bp, o, p, mc_filter);
			अवरोध;

		हाल BNX2X_MCAST_CMD_DEL:
			DP(BNX2X_MSG_SP,
			   "Invalidating multicast MACs configuration\n");

			/* clear the registry */
			स_रखो(o->registry.aprox_match.vec, 0,
			       माप(o->registry.aprox_match.vec));
			अवरोध;

		हाल BNX2X_MCAST_CMD_RESTORE:
			bnx2x_mcast_hdl_restore_e1h(bp, o, p, mc_filter);
			अवरोध;

		शेष:
			BNX2X_ERR("Unknown command: %d\n", cmd);
			वापस -EINVAL;
		पूर्ण

		/* Set the mcast filter in the पूर्णांकernal memory */
		क्रम (i = 0; i < MC_HASH_SIZE; i++)
			REG_WR(bp, MC_HASH_OFFSET(bp, i), mc_filter[i]);
	पूर्ण अन्यथा
		/* clear the registry */
		स_रखो(o->registry.aprox_match.vec, 0,
		       माप(o->registry.aprox_match.vec));

	/* We are करोne */
	r->clear_pending(r);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_mcast_validate_e1(काष्ठा bnx2x *bp,
				   काष्ठा bnx2x_mcast_ramrod_params *p,
				   क्रमागत bnx2x_mcast_cmd cmd)
अणु
	काष्ठा bnx2x_mcast_obj *o = p->mcast_obj;
	पूर्णांक reg_sz = o->get_registry_size(o);

	अगर (cmd == BNX2X_MCAST_CMD_SET) अणु
		BNX2X_ERR("Can't use `set' command on e1!\n");
		वापस -EINVAL;
	पूर्ण

	चयन (cmd) अणु
	/* DEL command deletes all currently configured MACs */
	हाल BNX2X_MCAST_CMD_DEL:
		o->set_registry_size(o, 0);
		fallthrough;

	/* RESTORE command will restore the entire multicast configuration */
	हाल BNX2X_MCAST_CMD_RESTORE:
		p->mcast_list_len = reg_sz;
		DP(BNX2X_MSG_SP, "Command %d, p->mcast_list_len=%d\n",
		   cmd, p->mcast_list_len);
		अवरोध;

	हाल BNX2X_MCAST_CMD_ADD:
	हाल BNX2X_MCAST_CMD_CONT:
		/* Multicast MACs on 57710 are configured as unicast MACs and
		 * there is only a limited number of CAM entries क्रम that
		 * matter.
		 */
		अगर (p->mcast_list_len > o->max_cmd_len) अणु
			BNX2X_ERR("Can't configure more than %d multicast MACs on 57710\n",
				  o->max_cmd_len);
			वापस -EINVAL;
		पूर्ण
		/* Every configured MAC should be cleared अगर DEL command is
		 * called. Only the last ADD command is relevant as दीर्घ as
		 * every ADD commands overrides the previous configuration.
		 */
		DP(BNX2X_MSG_SP, "p->mcast_list_len=%d\n", p->mcast_list_len);
		अगर (p->mcast_list_len > 0)
			o->set_registry_size(o, p->mcast_list_len);

		अवरोध;

	शेष:
		BNX2X_ERR("Unknown command: %d\n", cmd);
		वापस -EINVAL;
	पूर्ण

	/* We want to ensure that commands are executed one by one क्रम 57710.
	 * Thereक्रमe each none-empty command will consume o->max_cmd_len.
	 */
	अगर (p->mcast_list_len)
		o->total_pending_num += o->max_cmd_len;

	वापस 0;
पूर्ण

अटल व्योम bnx2x_mcast_revert_e1(काष्ठा bnx2x *bp,
				      काष्ठा bnx2x_mcast_ramrod_params *p,
				   पूर्णांक old_num_macs,
				   क्रमागत bnx2x_mcast_cmd cmd)
अणु
	काष्ठा bnx2x_mcast_obj *o = p->mcast_obj;

	o->set_registry_size(o, old_num_macs);

	/* If current command hasn't been handled yet and we are
	 * here means that it's meant to be dropped and we have to
	 * update the number of outstanding MACs accordingly.
	 */
	अगर (p->mcast_list_len)
		o->total_pending_num -= o->max_cmd_len;
पूर्ण

अटल व्योम bnx2x_mcast_set_one_rule_e1(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_mcast_obj *o, पूर्णांक idx,
					जोड़ bnx2x_mcast_config_data *cfg_data,
					क्रमागत bnx2x_mcast_cmd cmd)
अणु
	काष्ठा bnx2x_raw_obj *r = &o->raw;
	काष्ठा mac_configuration_cmd *data =
		(काष्ठा mac_configuration_cmd *)(r->rdata);

	/* copy mac */
	अगर ((cmd == BNX2X_MCAST_CMD_ADD) || (cmd == BNX2X_MCAST_CMD_RESTORE)) अणु
		bnx2x_set_fw_mac_addr(&data->config_table[idx].msb_mac_addr,
				      &data->config_table[idx].middle_mac_addr,
				      &data->config_table[idx].lsb_mac_addr,
				      cfg_data->mac);

		data->config_table[idx].vlan_id = 0;
		data->config_table[idx].pf_id = r->func_id;
		data->config_table[idx].clients_bit_vector =
			cpu_to_le32(1 << r->cl_id);

		SET_FLAG(data->config_table[idx].flags,
			 MAC_CONFIGURATION_ENTRY_ACTION_TYPE,
			 T_ETH_MAC_COMMAND_SET);
	पूर्ण
पूर्ण

/**
 * bnx2x_mcast_set_rdata_hdr_e1  - set header values in mac_configuration_cmd
 *
 * @bp:		device handle
 * @p:		ramrod parameters
 * @len:	number of rules to handle
 */
अटल अंतरभूत व्योम bnx2x_mcast_set_rdata_hdr_e1(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_mcast_ramrod_params *p,
					u8 len)
अणु
	काष्ठा bnx2x_raw_obj *r = &p->mcast_obj->raw;
	काष्ठा mac_configuration_cmd *data =
		(काष्ठा mac_configuration_cmd *)(r->rdata);

	u8 offset = (CHIP_REV_IS_SLOW(bp) ?
		     BNX2X_MAX_EMUL_MULTI*(1 + r->func_id) :
		     BNX2X_MAX_MULTICAST*(1 + r->func_id));

	data->hdr.offset = offset;
	data->hdr.client_id = cpu_to_le16(0xff);
	data->hdr.echo = cpu_to_le32((r->cid & BNX2X_SWCID_MASK) |
				     (BNX2X_FILTER_MCAST_PENDING <<
				      BNX2X_SWCID_SHIFT));
	data->hdr.length = len;
पूर्ण

/**
 * bnx2x_mcast_handle_restore_cmd_e1 - restore command क्रम 57710
 *
 * @bp:		device handle
 * @o:		multicast info
 * @start_idx:	index in the registry to start from
 * @rdata_idx:	index in the ramrod data to start from
 *
 * restore command क्रम 57710 is like all other commands - always a stand alone
 * command - start_idx and rdata_idx will always be 0. This function will always
 * succeed.
 * वापसs -1 to comply with 57712 variant.
 */
अटल अंतरभूत पूर्णांक bnx2x_mcast_handle_restore_cmd_e1(
	काष्ठा bnx2x *bp, काष्ठा bnx2x_mcast_obj *o , पूर्णांक start_idx,
	पूर्णांक *rdata_idx)
अणु
	काष्ठा bnx2x_mcast_mac_elem *elem;
	पूर्णांक i = 0;
	जोड़ bnx2x_mcast_config_data cfg_data = अणुशून्यपूर्ण;

	/* go through the registry and configure the MACs from it. */
	list_क्रम_each_entry(elem, &o->registry.exact_match.macs, link) अणु
		cfg_data.mac = &elem->mac[0];
		o->set_one_rule(bp, o, i, &cfg_data, BNX2X_MCAST_CMD_RESTORE);

		i++;

		DP(BNX2X_MSG_SP, "About to configure %pM mcast MAC\n",
		   cfg_data.mac);
	पूर्ण

	*rdata_idx = i;

	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_mcast_handle_pending_cmds_e1(
	काष्ठा bnx2x *bp, काष्ठा bnx2x_mcast_ramrod_params *p)
अणु
	काष्ठा bnx2x_pending_mcast_cmd *cmd_pos;
	काष्ठा bnx2x_mcast_mac_elem *pmac_pos;
	काष्ठा bnx2x_mcast_obj *o = p->mcast_obj;
	जोड़ bnx2x_mcast_config_data cfg_data = अणुशून्यपूर्ण;
	पूर्णांक cnt = 0;

	/* If nothing to be करोne - वापस */
	अगर (list_empty(&o->pending_cmds_head))
		वापस 0;

	/* Handle the first command */
	cmd_pos = list_first_entry(&o->pending_cmds_head,
				   काष्ठा bnx2x_pending_mcast_cmd, link);

	चयन (cmd_pos->type) अणु
	हाल BNX2X_MCAST_CMD_ADD:
		list_क्रम_each_entry(pmac_pos, &cmd_pos->data.macs_head, link) अणु
			cfg_data.mac = &pmac_pos->mac[0];
			o->set_one_rule(bp, o, cnt, &cfg_data, cmd_pos->type);

			cnt++;

			DP(BNX2X_MSG_SP, "About to configure %pM mcast MAC\n",
			   pmac_pos->mac);
		पूर्ण
		अवरोध;

	हाल BNX2X_MCAST_CMD_DEL:
		cnt = cmd_pos->data.macs_num;
		DP(BNX2X_MSG_SP, "About to delete %d multicast MACs\n", cnt);
		अवरोध;

	हाल BNX2X_MCAST_CMD_RESTORE:
		o->hdl_restore(bp, o, 0, &cnt);
		अवरोध;

	शेष:
		BNX2X_ERR("Unknown command: %d\n", cmd_pos->type);
		वापस -EINVAL;
	पूर्ण

	list_del(&cmd_pos->link);
	bnx2x_मुक्त_groups(&cmd_pos->group_head);
	kमुक्त(cmd_pos);

	वापस cnt;
पूर्ण

/**
 * bnx2x_get_fw_mac_addr - revert the bnx2x_set_fw_mac_addr().
 *
 * @fw_hi: address
 * @fw_mid: address
 * @fw_lo: address
 * @mac: mac address
 */
अटल अंतरभूत व्योम bnx2x_get_fw_mac_addr(__le16 *fw_hi, __le16 *fw_mid,
					 __le16 *fw_lo, u8 *mac)
अणु
	mac[1] = ((u8 *)fw_hi)[0];
	mac[0] = ((u8 *)fw_hi)[1];
	mac[3] = ((u8 *)fw_mid)[0];
	mac[2] = ((u8 *)fw_mid)[1];
	mac[5] = ((u8 *)fw_lo)[0];
	mac[4] = ((u8 *)fw_lo)[1];
पूर्ण

/**
 * bnx2x_mcast_refresh_registry_e1 -
 *
 * @bp:		device handle
 * @o:		multicast info
 *
 * Check the ramrod data first entry flag to see अगर it's a DELETE or ADD command
 * and update the registry correspondingly: अगर ADD - allocate a memory and add
 * the entries to the registry (list), अगर DELETE - clear the registry and मुक्त
 * the memory.
 */
अटल अंतरभूत पूर्णांक bnx2x_mcast_refresh_registry_e1(काष्ठा bnx2x *bp,
						  काष्ठा bnx2x_mcast_obj *o)
अणु
	काष्ठा bnx2x_raw_obj *raw = &o->raw;
	काष्ठा bnx2x_mcast_mac_elem *elem;
	काष्ठा mac_configuration_cmd *data =
			(काष्ठा mac_configuration_cmd *)(raw->rdata);

	/* If first entry contains a SET bit - the command was ADD,
	 * otherwise - DEL_ALL
	 */
	अगर (GET_FLAG(data->config_table[0].flags,
			MAC_CONFIGURATION_ENTRY_ACTION_TYPE)) अणु
		पूर्णांक i, len = data->hdr.length;

		/* Break अगर it was a RESTORE command */
		अगर (!list_empty(&o->registry.exact_match.macs))
			वापस 0;

		elem = kसुस्मृति(len, माप(*elem), GFP_ATOMIC);
		अगर (!elem) अणु
			BNX2X_ERR("Failed to allocate registry memory\n");
			वापस -ENOMEM;
		पूर्ण

		क्रम (i = 0; i < len; i++, elem++) अणु
			bnx2x_get_fw_mac_addr(
				&data->config_table[i].msb_mac_addr,
				&data->config_table[i].middle_mac_addr,
				&data->config_table[i].lsb_mac_addr,
				elem->mac);
			DP(BNX2X_MSG_SP, "Adding registry entry for [%pM]\n",
			   elem->mac);
			list_add_tail(&elem->link,
				      &o->registry.exact_match.macs);
		पूर्ण
	पूर्ण अन्यथा अणु
		elem = list_first_entry(&o->registry.exact_match.macs,
					काष्ठा bnx2x_mcast_mac_elem, link);
		DP(BNX2X_MSG_SP, "Deleting a registry\n");
		kमुक्त(elem);
		INIT_LIST_HEAD(&o->registry.exact_match.macs);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_mcast_setup_e1(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_mcast_ramrod_params *p,
				क्रमागत bnx2x_mcast_cmd cmd)
अणु
	काष्ठा bnx2x_mcast_obj *o = p->mcast_obj;
	काष्ठा bnx2x_raw_obj *raw = &o->raw;
	काष्ठा mac_configuration_cmd *data =
		(काष्ठा mac_configuration_cmd *)(raw->rdata);
	पूर्णांक cnt = 0, i, rc;

	/* Reset the ramrod data buffer */
	स_रखो(data, 0, माप(*data));

	/* First set all entries as invalid */
	क्रम (i = 0; i < o->max_cmd_len ; i++)
		SET_FLAG(data->config_table[i].flags,
			 MAC_CONFIGURATION_ENTRY_ACTION_TYPE,
			 T_ETH_MAC_COMMAND_INVALIDATE);

	/* Handle pending commands first */
	cnt = bnx2x_mcast_handle_pending_cmds_e1(bp, p);

	/* If there are no more pending commands - clear SCHEDULED state */
	अगर (list_empty(&o->pending_cmds_head))
		o->clear_sched(o);

	/* The below may be true अगरf there were no pending commands */
	अगर (!cnt)
		cnt = bnx2x_mcast_handle_current_cmd(bp, p, cmd, 0);

	/* For 57710 every command has o->max_cmd_len length to ensure that
	 * commands are करोne one at a समय.
	 */
	o->total_pending_num -= o->max_cmd_len;

	/* send a ramrod */

	WARN_ON(cnt > o->max_cmd_len);

	/* Set ramrod header (in particular, a number of entries to update) */
	bnx2x_mcast_set_rdata_hdr_e1(bp, p, (u8)cnt);

	/* update a registry: we need the registry contents to be always up
	 * to date in order to be able to execute a RESTORE opcode. Here
	 * we use the fact that क्रम 57710 we sent one command at a समय
	 * hence we may take the registry update out of the command handling
	 * and करो it in a simpler way here.
	 */
	rc = bnx2x_mcast_refresh_registry_e1(bp, o);
	अगर (rc)
		वापस rc;

	/* If CLEAR_ONLY was requested - करोn't send a ramrod and clear
	 * RAMROD_PENDING status immediately.
	 */
	अगर (test_bit(RAMROD_DRV_CLR_ONLY, &p->ramrod_flags)) अणु
		raw->clear_pending(raw);
		वापस 0;
	पूर्ण अन्यथा अणु
		/* No need क्रम an explicit memory barrier here as दीर्घ as we
		 * ensure the ordering of writing to the SPQ element
		 * and updating of the SPQ producer which involves a memory
		 * पढ़ो. If the memory पढ़ो is हटाओd we will have to put a
		 * full memory barrier there (inside bnx2x_sp_post()).
		 */

		/* Send a ramrod */
		rc = bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_SET_MAC, raw->cid,
				   U64_HI(raw->rdata_mapping),
				   U64_LO(raw->rdata_mapping),
				   ETH_CONNECTION_TYPE);
		अगर (rc)
			वापस rc;

		/* Ramrod completion is pending */
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_mcast_get_registry_size_exact(काष्ठा bnx2x_mcast_obj *o)
अणु
	वापस o->registry.exact_match.num_macs_set;
पूर्ण

अटल पूर्णांक bnx2x_mcast_get_registry_size_aprox(काष्ठा bnx2x_mcast_obj *o)
अणु
	वापस o->registry.aprox_match.num_bins_set;
पूर्ण

अटल व्योम bnx2x_mcast_set_registry_size_exact(काष्ठा bnx2x_mcast_obj *o,
						पूर्णांक n)
अणु
	o->registry.exact_match.num_macs_set = n;
पूर्ण

अटल व्योम bnx2x_mcast_set_registry_size_aprox(काष्ठा bnx2x_mcast_obj *o,
						पूर्णांक n)
अणु
	o->registry.aprox_match.num_bins_set = n;
पूर्ण

पूर्णांक bnx2x_config_mcast(काष्ठा bnx2x *bp,
		       काष्ठा bnx2x_mcast_ramrod_params *p,
		       क्रमागत bnx2x_mcast_cmd cmd)
अणु
	काष्ठा bnx2x_mcast_obj *o = p->mcast_obj;
	काष्ठा bnx2x_raw_obj *r = &o->raw;
	पूर्णांक rc = 0, old_reg_size;

	/* This is needed to recover number of currently configured mcast macs
	 * in हाल of failure.
	 */
	old_reg_size = o->get_registry_size(o);

	/* Do some calculations and checks */
	rc = o->validate(bp, p, cmd);
	अगर (rc)
		वापस rc;

	/* Return अगर there is no work to करो */
	अगर ((!p->mcast_list_len) && (!o->check_sched(o)))
		वापस 0;

	DP(BNX2X_MSG_SP, "o->total_pending_num=%d p->mcast_list_len=%d o->max_cmd_len=%d\n",
	   o->total_pending_num, p->mcast_list_len, o->max_cmd_len);

	/* Enqueue the current command to the pending list अगर we can't complete
	 * it in the current iteration
	 */
	अगर (r->check_pending(r) ||
	    ((o->max_cmd_len > 0) && (o->total_pending_num > o->max_cmd_len))) अणु
		rc = o->enqueue_cmd(bp, p->mcast_obj, p, cmd);
		अगर (rc < 0)
			जाओ error_निकास1;

		/* As दीर्घ as the current command is in a command list we
		 * करोn't need to handle it separately.
		 */
		p->mcast_list_len = 0;
	पूर्ण

	अगर (!r->check_pending(r)) अणु

		/* Set 'pending' state */
		r->set_pending(r);

		/* Configure the new classअगरication in the chip */
		rc = o->config_mcast(bp, p, cmd);
		अगर (rc < 0)
			जाओ error_निकास2;

		/* Wait क्रम a ramrod completion अगर was requested */
		अगर (test_bit(RAMROD_COMP_WAIT, &p->ramrod_flags))
			rc = o->रुको_comp(bp, o);
	पूर्ण

	वापस rc;

error_निकास2:
	r->clear_pending(r);

error_निकास1:
	o->revert(bp, p, old_reg_size, cmd);

	वापस rc;
पूर्ण

अटल व्योम bnx2x_mcast_clear_sched(काष्ठा bnx2x_mcast_obj *o)
अणु
	smp_mb__beक्रमe_atomic();
	clear_bit(o->sched_state, o->raw.pstate);
	smp_mb__after_atomic();
पूर्ण

अटल व्योम bnx2x_mcast_set_sched(काष्ठा bnx2x_mcast_obj *o)
अणु
	smp_mb__beक्रमe_atomic();
	set_bit(o->sched_state, o->raw.pstate);
	smp_mb__after_atomic();
पूर्ण

अटल bool bnx2x_mcast_check_sched(काष्ठा bnx2x_mcast_obj *o)
अणु
	वापस !!test_bit(o->sched_state, o->raw.pstate);
पूर्ण

अटल bool bnx2x_mcast_check_pending(काष्ठा bnx2x_mcast_obj *o)
अणु
	वापस o->raw.check_pending(&o->raw) || o->check_sched(o);
पूर्ण

व्योम bnx2x_init_mcast_obj(काष्ठा bnx2x *bp,
			  काष्ठा bnx2x_mcast_obj *mcast_obj,
			  u8 mcast_cl_id, u32 mcast_cid, u8 func_id,
			  u8 engine_id, व्योम *rdata, dma_addr_t rdata_mapping,
			  पूर्णांक state, अचिन्हित दीर्घ *pstate, bnx2x_obj_type type)
अणु
	स_रखो(mcast_obj, 0, माप(*mcast_obj));

	bnx2x_init_raw_obj(&mcast_obj->raw, mcast_cl_id, mcast_cid, func_id,
			   rdata, rdata_mapping, state, pstate, type);

	mcast_obj->engine_id = engine_id;

	INIT_LIST_HEAD(&mcast_obj->pending_cmds_head);

	mcast_obj->sched_state = BNX2X_FILTER_MCAST_SCHED;
	mcast_obj->check_sched = bnx2x_mcast_check_sched;
	mcast_obj->set_sched = bnx2x_mcast_set_sched;
	mcast_obj->clear_sched = bnx2x_mcast_clear_sched;

	अगर (CHIP_IS_E1(bp)) अणु
		mcast_obj->config_mcast      = bnx2x_mcast_setup_e1;
		mcast_obj->enqueue_cmd       = bnx2x_mcast_enqueue_cmd;
		mcast_obj->hdl_restore       =
			bnx2x_mcast_handle_restore_cmd_e1;
		mcast_obj->check_pending     = bnx2x_mcast_check_pending;

		अगर (CHIP_REV_IS_SLOW(bp))
			mcast_obj->max_cmd_len = BNX2X_MAX_EMUL_MULTI;
		अन्यथा
			mcast_obj->max_cmd_len = BNX2X_MAX_MULTICAST;

		mcast_obj->रुको_comp         = bnx2x_mcast_रुको;
		mcast_obj->set_one_rule      = bnx2x_mcast_set_one_rule_e1;
		mcast_obj->validate          = bnx2x_mcast_validate_e1;
		mcast_obj->revert            = bnx2x_mcast_revert_e1;
		mcast_obj->get_registry_size =
			bnx2x_mcast_get_registry_size_exact;
		mcast_obj->set_registry_size =
			bnx2x_mcast_set_registry_size_exact;

		/* 57710 is the only chip that uses the exact match क्रम mcast
		 * at the moment.
		 */
		INIT_LIST_HEAD(&mcast_obj->registry.exact_match.macs);

	पूर्ण अन्यथा अगर (CHIP_IS_E1H(bp)) अणु
		mcast_obj->config_mcast  = bnx2x_mcast_setup_e1h;
		mcast_obj->enqueue_cmd   = शून्य;
		mcast_obj->hdl_restore   = शून्य;
		mcast_obj->check_pending = bnx2x_mcast_check_pending;

		/* 57711 करोesn't send a ramrod, so it has unlimited credit
		 * क्रम one command.
		 */
		mcast_obj->max_cmd_len       = -1;
		mcast_obj->रुको_comp         = bnx2x_mcast_रुको;
		mcast_obj->set_one_rule      = शून्य;
		mcast_obj->validate          = bnx2x_mcast_validate_e1h;
		mcast_obj->revert            = bnx2x_mcast_revert_e1h;
		mcast_obj->get_registry_size =
			bnx2x_mcast_get_registry_size_aprox;
		mcast_obj->set_registry_size =
			bnx2x_mcast_set_registry_size_aprox;
	पूर्ण अन्यथा अणु
		mcast_obj->config_mcast      = bnx2x_mcast_setup_e2;
		mcast_obj->enqueue_cmd       = bnx2x_mcast_enqueue_cmd;
		mcast_obj->hdl_restore       =
			bnx2x_mcast_handle_restore_cmd_e2;
		mcast_obj->check_pending     = bnx2x_mcast_check_pending;
		/* TODO: There should be a proper HSI define क्रम this number!!!
		 */
		mcast_obj->max_cmd_len       = 16;
		mcast_obj->रुको_comp         = bnx2x_mcast_रुको;
		mcast_obj->set_one_rule      = bnx2x_mcast_set_one_rule_e2;
		mcast_obj->validate          = bnx2x_mcast_validate_e2;
		mcast_obj->revert            = bnx2x_mcast_revert_e2;
		mcast_obj->get_registry_size =
			bnx2x_mcast_get_registry_size_aprox;
		mcast_obj->set_registry_size =
			bnx2x_mcast_set_registry_size_aprox;
	पूर्ण
पूर्ण

/*************************** Credit handling **********************************/

/**
 * atomic_add_अगरless - add अगर the result is less than a given value.
 *
 * @v:	poपूर्णांकer of type atomic_t
 * @a:	the amount to add to v...
 * @u:	...अगर (v + a) is less than u.
 *
 * वापसs true अगर (v + a) was less than u, and false otherwise.
 *
 */
अटल अंतरभूत bool __atomic_add_अगरless(atomic_t *v, पूर्णांक a, पूर्णांक u)
अणु
	पूर्णांक c, old;

	c = atomic_पढ़ो(v);
	क्रम (;;) अणु
		अगर (unlikely(c + a >= u))
			वापस false;

		old = atomic_cmpxchg((v), c, c + a);
		अगर (likely(old == c))
			अवरोध;
		c = old;
	पूर्ण

	वापस true;
पूर्ण

/**
 * atomic_dec_अगरmoe - dec अगर the result is more or equal than a given value.
 *
 * @v:	poपूर्णांकer of type atomic_t
 * @a:	the amount to dec from v...
 * @u:	...अगर (v - a) is more or equal than u.
 *
 * वापसs true अगर (v - a) was more or equal than u, and false
 * otherwise.
 */
अटल अंतरभूत bool __atomic_dec_अगरmoe(atomic_t *v, पूर्णांक a, पूर्णांक u)
अणु
	पूर्णांक c, old;

	c = atomic_पढ़ो(v);
	क्रम (;;) अणु
		अगर (unlikely(c - a < u))
			वापस false;

		old = atomic_cmpxchg((v), c, c - a);
		अगर (likely(old == c))
			अवरोध;
		c = old;
	पूर्ण

	वापस true;
पूर्ण

अटल bool bnx2x_credit_pool_get(काष्ठा bnx2x_credit_pool_obj *o, पूर्णांक cnt)
अणु
	bool rc;

	smp_mb();
	rc = __atomic_dec_अगरmoe(&o->credit, cnt, 0);
	smp_mb();

	वापस rc;
पूर्ण

अटल bool bnx2x_credit_pool_put(काष्ठा bnx2x_credit_pool_obj *o, पूर्णांक cnt)
अणु
	bool rc;

	smp_mb();

	/* Don't let to refill अगर credit + cnt > pool_sz */
	rc = __atomic_add_अगरless(&o->credit, cnt, o->pool_sz + 1);

	smp_mb();

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_credit_pool_check(काष्ठा bnx2x_credit_pool_obj *o)
अणु
	पूर्णांक cur_credit;

	smp_mb();
	cur_credit = atomic_पढ़ो(&o->credit);

	वापस cur_credit;
पूर्ण

अटल bool bnx2x_credit_pool_always_true(काष्ठा bnx2x_credit_pool_obj *o,
					  पूर्णांक cnt)
अणु
	वापस true;
पूर्ण

अटल bool bnx2x_credit_pool_get_entry(
	काष्ठा bnx2x_credit_pool_obj *o,
	पूर्णांक *offset)
अणु
	पूर्णांक idx, vec, i;

	*offset = -1;

	/* Find "internal cam-offset" then add to base क्रम this object... */
	क्रम (vec = 0; vec < BNX2X_POOL_VEC_SIZE; vec++) अणु

		/* Skip the current vector अगर there are no मुक्त entries in it */
		अगर (!o->pool_mirror[vec])
			जारी;

		/* If we've got here we are going to find a मुक्त entry */
		क्रम (idx = vec * BIT_VEC64_ELEM_SZ, i = 0;
		      i < BIT_VEC64_ELEM_SZ; idx++, i++)

			अगर (BIT_VEC64_TEST_BIT(o->pool_mirror, idx)) अणु
				/* Got one!! */
				BIT_VEC64_CLEAR_BIT(o->pool_mirror, idx);
				*offset = o->base_pool_offset + idx;
				वापस true;
			पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool bnx2x_credit_pool_put_entry(
	काष्ठा bnx2x_credit_pool_obj *o,
	पूर्णांक offset)
अणु
	अगर (offset < o->base_pool_offset)
		वापस false;

	offset -= o->base_pool_offset;

	अगर (offset >= o->pool_sz)
		वापस false;

	/* Return the entry to the pool */
	BIT_VEC64_SET_BIT(o->pool_mirror, offset);

	वापस true;
पूर्ण

अटल bool bnx2x_credit_pool_put_entry_always_true(
	काष्ठा bnx2x_credit_pool_obj *o,
	पूर्णांक offset)
अणु
	वापस true;
पूर्ण

अटल bool bnx2x_credit_pool_get_entry_always_true(
	काष्ठा bnx2x_credit_pool_obj *o,
	पूर्णांक *offset)
अणु
	*offset = -1;
	वापस true;
पूर्ण
/**
 * bnx2x_init_credit_pool - initialize credit pool पूर्णांकernals.
 *
 * @p:		credit pool
 * @base:	Base entry in the CAM to use.
 * @credit:	pool size.
 *
 * If base is negative no CAM entries handling will be perक्रमmed.
 * If credit is negative pool operations will always succeed (unlimited pool).
 *
 */
व्योम bnx2x_init_credit_pool(काष्ठा bnx2x_credit_pool_obj *p,
			    पूर्णांक base, पूर्णांक credit)
अणु
	/* Zero the object first */
	स_रखो(p, 0, माप(*p));

	/* Set the table to all 1s */
	स_रखो(&p->pool_mirror, 0xff, माप(p->pool_mirror));

	/* Init a pool as full */
	atomic_set(&p->credit, credit);

	/* The total poll size */
	p->pool_sz = credit;

	p->base_pool_offset = base;

	/* Commit the change */
	smp_mb();

	p->check = bnx2x_credit_pool_check;

	/* अगर pool credit is negative - disable the checks */
	अगर (credit >= 0) अणु
		p->put      = bnx2x_credit_pool_put;
		p->get      = bnx2x_credit_pool_get;
		p->put_entry = bnx2x_credit_pool_put_entry;
		p->get_entry = bnx2x_credit_pool_get_entry;
	पूर्ण अन्यथा अणु
		p->put      = bnx2x_credit_pool_always_true;
		p->get      = bnx2x_credit_pool_always_true;
		p->put_entry = bnx2x_credit_pool_put_entry_always_true;
		p->get_entry = bnx2x_credit_pool_get_entry_always_true;
	पूर्ण

	/* If base is negative - disable entries handling */
	अगर (base < 0) अणु
		p->put_entry = bnx2x_credit_pool_put_entry_always_true;
		p->get_entry = bnx2x_credit_pool_get_entry_always_true;
	पूर्ण
पूर्ण

व्योम bnx2x_init_mac_credit_pool(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_credit_pool_obj *p, u8 func_id,
				u8 func_num)
अणु
/* TODO: this will be defined in स्थिरs as well... */
#घोषणा BNX2X_CAM_SIZE_EMUL 5

	पूर्णांक cam_sz;

	अगर (CHIP_IS_E1(bp)) अणु
		/* In E1, Multicast is saved in cam... */
		अगर (!CHIP_REV_IS_SLOW(bp))
			cam_sz = (MAX_MAC_CREDIT_E1 / 2) - BNX2X_MAX_MULTICAST;
		अन्यथा
			cam_sz = BNX2X_CAM_SIZE_EMUL - BNX2X_MAX_EMUL_MULTI;

		bnx2x_init_credit_pool(p, func_id * cam_sz, cam_sz);

	पूर्ण अन्यथा अगर (CHIP_IS_E1H(bp)) अणु
		/* CAM credit is equaly भागided between all active functions
		 * on the PORT!.
		 */
		अगर ((func_num > 0)) अणु
			अगर (!CHIP_REV_IS_SLOW(bp))
				cam_sz = (MAX_MAC_CREDIT_E1H / (2*func_num));
			अन्यथा
				cam_sz = BNX2X_CAM_SIZE_EMUL;
			bnx2x_init_credit_pool(p, func_id * cam_sz, cam_sz);
		पूर्ण अन्यथा अणु
			/* this should never happen! Block MAC operations. */
			bnx2x_init_credit_pool(p, 0, 0);
		पूर्ण

	पूर्ण अन्यथा अणु

		/* CAM credit is equaly भागided between all active functions
		 * on the PATH.
		 */
		अगर (func_num > 0) अणु
			अगर (!CHIP_REV_IS_SLOW(bp))
				cam_sz = PF_MAC_CREDIT_E2(bp, func_num);
			अन्यथा
				cam_sz = BNX2X_CAM_SIZE_EMUL;

			/* No need क्रम CAM entries handling क्रम 57712 and
			 * newer.
			 */
			bnx2x_init_credit_pool(p, -1, cam_sz);
		पूर्ण अन्यथा अणु
			/* this should never happen! Block MAC operations. */
			bnx2x_init_credit_pool(p, 0, 0);
		पूर्ण
	पूर्ण
पूर्ण

व्योम bnx2x_init_vlan_credit_pool(काष्ठा bnx2x *bp,
				 काष्ठा bnx2x_credit_pool_obj *p,
				 u8 func_id,
				 u8 func_num)
अणु
	अगर (CHIP_IS_E1x(bp)) अणु
		/* There is no VLAN credit in HW on 57710 and 57711 only
		 * MAC / MAC-VLAN can be set
		 */
		bnx2x_init_credit_pool(p, 0, -1);
	पूर्ण अन्यथा अणु
		/* CAM credit is equally भागided between all active functions
		 * on the PATH.
		 */
		अगर (func_num > 0) अणु
			पूर्णांक credit = PF_VLAN_CREDIT_E2(bp, func_num);

			bnx2x_init_credit_pool(p, -1/*unused क्रम E2*/, credit);
		पूर्ण अन्यथा
			/* this should never happen! Block VLAN operations. */
			bnx2x_init_credit_pool(p, 0, 0);
	पूर्ण
पूर्ण

/****************** RSS Configuration ******************/
/**
 * bnx2x_debug_prपूर्णांक_ind_table - prपूर्णांकs the indirection table configuration.
 *
 * @bp:		driver handle
 * @p:		poपूर्णांकer to rss configuration
 *
 * Prपूर्णांकs it when NETIF_MSG_IFUP debug level is configured.
 */
अटल अंतरभूत व्योम bnx2x_debug_prपूर्णांक_ind_table(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_config_rss_params *p)
अणु
	पूर्णांक i;

	DP(BNX2X_MSG_SP, "Setting indirection table to:\n");
	DP(BNX2X_MSG_SP, "0x0000: ");
	क्रम (i = 0; i < T_ETH_INसूचीECTION_TABLE_SIZE; i++) अणु
		DP_CONT(BNX2X_MSG_SP, "0x%02x ", p->ind_table[i]);

		/* Prपूर्णांक 4 bytes in a line */
		अगर ((i + 1 < T_ETH_INसूचीECTION_TABLE_SIZE) &&
		    (((i + 1) & 0x3) == 0)) अणु
			DP_CONT(BNX2X_MSG_SP, "\n");
			DP(BNX2X_MSG_SP, "0x%04x: ", i + 1);
		पूर्ण
	पूर्ण

	DP_CONT(BNX2X_MSG_SP, "\n");
पूर्ण

/**
 * bnx2x_setup_rss - configure RSS
 *
 * @bp:		device handle
 * @p:		rss configuration
 *
 * sends on UPDATE ramrod क्रम that matter.
 */
अटल पूर्णांक bnx2x_setup_rss(काष्ठा bnx2x *bp,
			   काष्ठा bnx2x_config_rss_params *p)
अणु
	काष्ठा bnx2x_rss_config_obj *o = p->rss_obj;
	काष्ठा bnx2x_raw_obj *r = &o->raw;
	काष्ठा eth_rss_update_ramrod_data *data =
		(काष्ठा eth_rss_update_ramrod_data *)(r->rdata);
	u16 caps = 0;
	u8 rss_mode = 0;
	पूर्णांक rc;

	स_रखो(data, 0, माप(*data));

	DP(BNX2X_MSG_SP, "Configuring RSS\n");

	/* Set an echo field */
	data->echo = cpu_to_le32((r->cid & BNX2X_SWCID_MASK) |
				 (r->state << BNX2X_SWCID_SHIFT));

	/* RSS mode */
	अगर (test_bit(BNX2X_RSS_MODE_DISABLED, &p->rss_flags))
		rss_mode = ETH_RSS_MODE_DISABLED;
	अन्यथा अगर (test_bit(BNX2X_RSS_MODE_REGULAR, &p->rss_flags))
		rss_mode = ETH_RSS_MODE_REGULAR;

	data->rss_mode = rss_mode;

	DP(BNX2X_MSG_SP, "rss_mode=%d\n", rss_mode);

	/* RSS capabilities */
	अगर (test_bit(BNX2X_RSS_IPV4, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV4_CAPABILITY;

	अगर (test_bit(BNX2X_RSS_IPV4_TCP, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV4_TCP_CAPABILITY;

	अगर (test_bit(BNX2X_RSS_IPV4_UDP, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV4_UDP_CAPABILITY;

	अगर (test_bit(BNX2X_RSS_IPV6, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV6_CAPABILITY;

	अगर (test_bit(BNX2X_RSS_IPV6_TCP, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV6_TCP_CAPABILITY;

	अगर (test_bit(BNX2X_RSS_IPV6_UDP, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV6_UDP_CAPABILITY;

	अगर (test_bit(BNX2X_RSS_IPV4_VXLAN, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV4_VXLAN_CAPABILITY;

	अगर (test_bit(BNX2X_RSS_IPV6_VXLAN, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV6_VXLAN_CAPABILITY;

	अगर (test_bit(BNX2X_RSS_TUNN_INNER_HDRS, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_TUNN_INNER_HDRS_CAPABILITY;

	/* RSS keys */
	अगर (test_bit(BNX2X_RSS_SET_SRCH, &p->rss_flags)) अणु
		u8 *dst = (u8 *)(data->rss_key) + माप(data->rss_key);
		स्थिर u8 *src = (स्थिर u8 *)p->rss_key;
		पूर्णांक i;

		/* Apparently, bnx2x पढ़ोs this array in reverse order
		 * We need to byte swap rss_key to comply with Toeplitz specs.
		 */
		क्रम (i = 0; i < माप(data->rss_key); i++)
			*--dst = *src++;

		caps |= ETH_RSS_UPDATE_RAMROD_DATA_UPDATE_RSS_KEY;
	पूर्ण

	data->capabilities = cpu_to_le16(caps);

	/* Hashing mask */
	data->rss_result_mask = p->rss_result_mask;

	/* RSS engine ID */
	data->rss_engine_id = o->engine_id;

	DP(BNX2X_MSG_SP, "rss_engine_id=%d\n", data->rss_engine_id);

	/* Indirection table */
	स_नकल(data->indirection_table, p->ind_table,
		  T_ETH_INसूचीECTION_TABLE_SIZE);

	/* Remember the last configuration */
	स_नकल(o->ind_table, p->ind_table, T_ETH_INसूचीECTION_TABLE_SIZE);

	/* Prपूर्णांक the indirection table */
	अगर (netअगर_msg_अगरup(bp))
		bnx2x_debug_prपूर्णांक_ind_table(bp, p);

	/* No need क्रम an explicit memory barrier here as दीर्घ as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * पढ़ो. If the memory पढ़ो is हटाओd we will have to put a
	 * full memory barrier there (inside bnx2x_sp_post()).
	 */

	/* Send a ramrod */
	rc = bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_RSS_UPDATE, r->cid,
			   U64_HI(r->rdata_mapping),
			   U64_LO(r->rdata_mapping),
			   ETH_CONNECTION_TYPE);

	अगर (rc < 0)
		वापस rc;

	वापस 1;
पूर्ण

व्योम bnx2x_get_rss_ind_table(काष्ठा bnx2x_rss_config_obj *rss_obj,
			     u8 *ind_table)
अणु
	स_नकल(ind_table, rss_obj->ind_table, माप(rss_obj->ind_table));
पूर्ण

पूर्णांक bnx2x_config_rss(काष्ठा bnx2x *bp,
		     काष्ठा bnx2x_config_rss_params *p)
अणु
	पूर्णांक rc;
	काष्ठा bnx2x_rss_config_obj *o = p->rss_obj;
	काष्ठा bnx2x_raw_obj *r = &o->raw;

	/* Do nothing अगर only driver cleanup was requested */
	अगर (test_bit(RAMROD_DRV_CLR_ONLY, &p->ramrod_flags)) अणु
		DP(BNX2X_MSG_SP, "Not configuring RSS ramrod_flags=%lx\n",
		   p->ramrod_flags);
		वापस 0;
	पूर्ण

	r->set_pending(r);

	rc = o->config_rss(bp, p);
	अगर (rc < 0) अणु
		r->clear_pending(r);
		वापस rc;
	पूर्ण

	अगर (test_bit(RAMROD_COMP_WAIT, &p->ramrod_flags))
		rc = r->रुको_comp(bp, r);

	वापस rc;
पूर्ण

व्योम bnx2x_init_rss_config_obj(काष्ठा bnx2x *bp,
			       काष्ठा bnx2x_rss_config_obj *rss_obj,
			       u8 cl_id, u32 cid, u8 func_id, u8 engine_id,
			       व्योम *rdata, dma_addr_t rdata_mapping,
			       पूर्णांक state, अचिन्हित दीर्घ *pstate,
			       bnx2x_obj_type type)
अणु
	bnx2x_init_raw_obj(&rss_obj->raw, cl_id, cid, func_id, rdata,
			   rdata_mapping, state, pstate, type);

	rss_obj->engine_id  = engine_id;
	rss_obj->config_rss = bnx2x_setup_rss;
पूर्ण

/********************** Queue state object ***********************************/

/**
 * bnx2x_queue_state_change - perक्रमm Queue state change transition
 *
 * @bp:		device handle
 * @params:	parameters to perक्रमm the transition
 *
 * वापसs 0 in हाल of successfully completed transition, negative error
 * code in हाल of failure, positive (EBUSY) value अगर there is a completion
 * to that is still pending (possible only अगर RAMROD_COMP_WAIT is
 * not set in params->ramrod_flags क्रम asynchronous commands).
 *
 */
पूर्णांक bnx2x_queue_state_change(काष्ठा bnx2x *bp,
			     काष्ठा bnx2x_queue_state_params *params)
अणु
	काष्ठा bnx2x_queue_sp_obj *o = params->q_obj;
	पूर्णांक rc, pending_bit;
	अचिन्हित दीर्घ *pending = &o->pending;

	/* Check that the requested transition is legal */
	rc = o->check_transition(bp, o, params);
	अगर (rc) अणु
		BNX2X_ERR("check transition returned an error. rc %d\n", rc);
		वापस -EINVAL;
	पूर्ण

	/* Set "pending" bit */
	DP(BNX2X_MSG_SP, "pending bit was=%lx\n", o->pending);
	pending_bit = o->set_pending(o, params);
	DP(BNX2X_MSG_SP, "pending bit now=%lx\n", o->pending);

	/* Don't send a command अगर only driver cleanup was requested */
	अगर (test_bit(RAMROD_DRV_CLR_ONLY, &params->ramrod_flags))
		o->complete_cmd(bp, o, pending_bit);
	अन्यथा अणु
		/* Send a ramrod */
		rc = o->send_cmd(bp, params);
		अगर (rc) अणु
			o->next_state = BNX2X_Q_STATE_MAX;
			clear_bit(pending_bit, pending);
			smp_mb__after_atomic();
			वापस rc;
		पूर्ण

		अगर (test_bit(RAMROD_COMP_WAIT, &params->ramrod_flags)) अणु
			rc = o->रुको_comp(bp, o, pending_bit);
			अगर (rc)
				वापस rc;

			वापस 0;
		पूर्ण
	पूर्ण

	वापस !!test_bit(pending_bit, pending);
पूर्ण

अटल पूर्णांक bnx2x_queue_set_pending(काष्ठा bnx2x_queue_sp_obj *obj,
				   काष्ठा bnx2x_queue_state_params *params)
अणु
	क्रमागत bnx2x_queue_cmd cmd = params->cmd, bit;

	/* ACTIVATE and DEACTIVATE commands are implemented on top of
	 * UPDATE command.
	 */
	अगर ((cmd == BNX2X_Q_CMD_ACTIVATE) ||
	    (cmd == BNX2X_Q_CMD_DEACTIVATE))
		bit = BNX2X_Q_CMD_UPDATE;
	अन्यथा
		bit = cmd;

	set_bit(bit, &obj->pending);
	वापस bit;
पूर्ण

अटल पूर्णांक bnx2x_queue_रुको_comp(काष्ठा bnx2x *bp,
				 काष्ठा bnx2x_queue_sp_obj *o,
				 क्रमागत bnx2x_queue_cmd cmd)
अणु
	वापस bnx2x_state_रुको(bp, cmd, &o->pending);
पूर्ण

/**
 * bnx2x_queue_comp_cmd - complete the state change command.
 *
 * @bp:		device handle
 * @o:		queue info
 * @cmd:	command to exec
 *
 * Checks that the arrived completion is expected.
 */
अटल पूर्णांक bnx2x_queue_comp_cmd(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_queue_sp_obj *o,
				क्रमागत bnx2x_queue_cmd cmd)
अणु
	अचिन्हित दीर्घ cur_pending = o->pending;

	अगर (!test_and_clear_bit(cmd, &cur_pending)) अणु
		BNX2X_ERR("Bad MC reply %d for queue %d in state %d pending 0x%lx, next_state %d\n",
			  cmd, o->cids[BNX2X_PRIMARY_CID_INDEX],
			  o->state, cur_pending, o->next_state);
		वापस -EINVAL;
	पूर्ण

	अगर (o->next_tx_only >= o->max_cos)
		/* >= because tx only must always be smaller than cos since the
		 * primary connection supports COS 0
		 */
		BNX2X_ERR("illegal value for next tx_only: %d. max cos was %d",
			   o->next_tx_only, o->max_cos);

	DP(BNX2X_MSG_SP,
	   "Completing command %d for queue %d, setting state to %d\n",
	   cmd, o->cids[BNX2X_PRIMARY_CID_INDEX], o->next_state);

	अगर (o->next_tx_only)  /* prपूर्णांक num tx-only अगर any exist */
		DP(BNX2X_MSG_SP, "primary cid %d: num tx-only cons %d\n",
		   o->cids[BNX2X_PRIMARY_CID_INDEX], o->next_tx_only);

	o->state = o->next_state;
	o->num_tx_only = o->next_tx_only;
	o->next_state = BNX2X_Q_STATE_MAX;

	/* It's important that o->state and o->next_state are
	 * updated beक्रमe o->pending.
	 */
	wmb();

	clear_bit(cmd, &o->pending);
	smp_mb__after_atomic();

	वापस 0;
पूर्ण

अटल व्योम bnx2x_q_fill_setup_data_e2(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_queue_state_params *cmd_params,
				काष्ठा client_init_ramrod_data *data)
अणु
	काष्ठा bnx2x_queue_setup_params *params = &cmd_params->params.setup;

	/* Rx data */

	/* IPv6 TPA supported क्रम E2 and above only */
	data->rx.tpa_en |= test_bit(BNX2X_Q_FLG_TPA_IPV6, &params->flags) *
				CLIENT_INIT_RX_DATA_TPA_EN_IPV6;
पूर्ण

अटल व्योम bnx2x_q_fill_init_general_data(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_queue_sp_obj *o,
				काष्ठा bnx2x_general_setup_params *params,
				काष्ठा client_init_general_data *gen_data,
				अचिन्हित दीर्घ *flags)
अणु
	gen_data->client_id = o->cl_id;

	अगर (test_bit(BNX2X_Q_FLG_STATS, flags)) अणु
		gen_data->statistics_counter_id =
					params->stat_id;
		gen_data->statistics_en_flg = 1;
		gen_data->statistics_zero_flg =
			test_bit(BNX2X_Q_FLG_ZERO_STATS, flags);
	पूर्ण अन्यथा
		gen_data->statistics_counter_id =
					DISABLE_STATISTIC_COUNTER_ID_VALUE;

	gen_data->is_fcoe_flg = test_bit(BNX2X_Q_FLG_FCOE, flags);
	gen_data->activate_flg = test_bit(BNX2X_Q_FLG_ACTIVE, flags);
	gen_data->sp_client_id = params->spcl_id;
	gen_data->mtu = cpu_to_le16(params->mtu);
	gen_data->func_id = o->func_id;

	gen_data->cos = params->cos;

	gen_data->traffic_type =
		test_bit(BNX2X_Q_FLG_FCOE, flags) ?
		LLFC_TRAFFIC_TYPE_FCOE : LLFC_TRAFFIC_TYPE_NW;

	gen_data->fp_hsi_ver = params->fp_hsi;

	DP(BNX2X_MSG_SP, "flags: active %d, cos %d, stats en %d\n",
	   gen_data->activate_flg, gen_data->cos, gen_data->statistics_en_flg);
पूर्ण

अटल व्योम bnx2x_q_fill_init_tx_data(काष्ठा bnx2x_queue_sp_obj *o,
				काष्ठा bnx2x_txq_setup_params *params,
				काष्ठा client_init_tx_data *tx_data,
				अचिन्हित दीर्घ *flags)
अणु
	tx_data->enक्रमce_security_flg =
		test_bit(BNX2X_Q_FLG_TX_SEC, flags);
	tx_data->शेष_vlan =
		cpu_to_le16(params->शेष_vlan);
	tx_data->शेष_vlan_flg =
		test_bit(BNX2X_Q_FLG_DEF_VLAN, flags);
	tx_data->tx_चयनing_flg =
		test_bit(BNX2X_Q_FLG_TX_SWITCH, flags);
	tx_data->anti_spoofing_flg =
		test_bit(BNX2X_Q_FLG_ANTI_SPOOF, flags);
	tx_data->क्रमce_शेष_pri_flg =
		test_bit(BNX2X_Q_FLG_FORCE_DEFAULT_PRI, flags);
	tx_data->refuse_outband_vlan_flg =
		test_bit(BNX2X_Q_FLG_REFUSE_OUTBAND_VLAN, flags);
	tx_data->tunnel_lso_inc_ip_id =
		test_bit(BNX2X_Q_FLG_TUN_INC_INNER_IP_ID, flags);
	tx_data->tunnel_non_lso_pcsum_location =
		test_bit(BNX2X_Q_FLG_PCSUM_ON_PKT, flags) ? CSUM_ON_PKT :
							    CSUM_ON_BD;

	tx_data->tx_status_block_id = params->fw_sb_id;
	tx_data->tx_sb_index_number = params->sb_cq_index;
	tx_data->tss_leading_client_id = params->tss_leading_cl_id;

	tx_data->tx_bd_page_base.lo =
		cpu_to_le32(U64_LO(params->dscr_map));
	tx_data->tx_bd_page_base.hi =
		cpu_to_le32(U64_HI(params->dscr_map));

	/* Don't configure any Tx चयनing mode during queue SETUP */
	tx_data->state = 0;
पूर्ण

अटल व्योम bnx2x_q_fill_init_छोड़ो_data(काष्ठा bnx2x_queue_sp_obj *o,
				काष्ठा rxq_छोड़ो_params *params,
				काष्ठा client_init_rx_data *rx_data)
अणु
	/* flow control data */
	rx_data->cqe_छोड़ो_thr_low = cpu_to_le16(params->rcq_th_lo);
	rx_data->cqe_छोड़ो_thr_high = cpu_to_le16(params->rcq_th_hi);
	rx_data->bd_छोड़ो_thr_low = cpu_to_le16(params->bd_th_lo);
	rx_data->bd_छोड़ो_thr_high = cpu_to_le16(params->bd_th_hi);
	rx_data->sge_छोड़ो_thr_low = cpu_to_le16(params->sge_th_lo);
	rx_data->sge_छोड़ो_thr_high = cpu_to_le16(params->sge_th_hi);
	rx_data->rx_cos_mask = cpu_to_le16(params->pri_map);
पूर्ण

अटल व्योम bnx2x_q_fill_init_rx_data(काष्ठा bnx2x_queue_sp_obj *o,
				काष्ठा bnx2x_rxq_setup_params *params,
				काष्ठा client_init_rx_data *rx_data,
				अचिन्हित दीर्घ *flags)
अणु
	rx_data->tpa_en = test_bit(BNX2X_Q_FLG_TPA, flags) *
				CLIENT_INIT_RX_DATA_TPA_EN_IPV4;
	rx_data->tpa_en |= test_bit(BNX2X_Q_FLG_TPA_GRO, flags) *
				CLIENT_INIT_RX_DATA_TPA_MODE;
	rx_data->vmqueue_mode_en_flg = 0;

	rx_data->cache_line_alignment_log_size =
		params->cache_line_log;
	rx_data->enable_dynamic_hc =
		test_bit(BNX2X_Q_FLG_DHC, flags);
	rx_data->max_sges_क्रम_packet = params->max_sges_pkt;
	rx_data->client_qzone_id = params->cl_qzone_id;
	rx_data->max_agg_size = cpu_to_le16(params->tpa_agg_sz);

	/* Always start in DROP_ALL mode */
	rx_data->state = cpu_to_le16(CLIENT_INIT_RX_DATA_UCAST_DROP_ALL |
				     CLIENT_INIT_RX_DATA_MCAST_DROP_ALL);

	/* We करोn't set drop flags */
	rx_data->drop_ip_cs_err_flg = 0;
	rx_data->drop_tcp_cs_err_flg = 0;
	rx_data->drop_ttl0_flg = 0;
	rx_data->drop_udp_cs_err_flg = 0;
	rx_data->inner_vlan_removal_enable_flg =
		test_bit(BNX2X_Q_FLG_VLAN, flags);
	rx_data->outer_vlan_removal_enable_flg =
		test_bit(BNX2X_Q_FLG_OV, flags);
	rx_data->status_block_id = params->fw_sb_id;
	rx_data->rx_sb_index_number = params->sb_cq_index;
	rx_data->max_tpa_queues = params->max_tpa_queues;
	rx_data->max_bytes_on_bd = cpu_to_le16(params->buf_sz);
	rx_data->sge_buff_size = cpu_to_le16(params->sge_buf_sz);
	rx_data->bd_page_base.lo =
		cpu_to_le32(U64_LO(params->dscr_map));
	rx_data->bd_page_base.hi =
		cpu_to_le32(U64_HI(params->dscr_map));
	rx_data->sge_page_base.lo =
		cpu_to_le32(U64_LO(params->sge_map));
	rx_data->sge_page_base.hi =
		cpu_to_le32(U64_HI(params->sge_map));
	rx_data->cqe_page_base.lo =
		cpu_to_le32(U64_LO(params->rcq_map));
	rx_data->cqe_page_base.hi =
		cpu_to_le32(U64_HI(params->rcq_map));
	rx_data->is_leading_rss = test_bit(BNX2X_Q_FLG_LEADING_RSS, flags);

	अगर (test_bit(BNX2X_Q_FLG_MCAST, flags)) अणु
		rx_data->approx_mcast_engine_id = params->mcast_engine_id;
		rx_data->is_approx_mcast = 1;
	पूर्ण

	rx_data->rss_engine_id = params->rss_engine_id;

	/* silent vlan removal */
	rx_data->silent_vlan_removal_flg =
		test_bit(BNX2X_Q_FLG_SILENT_VLAN_REM, flags);
	rx_data->silent_vlan_value =
		cpu_to_le16(params->silent_removal_value);
	rx_data->silent_vlan_mask =
		cpu_to_le16(params->silent_removal_mask);
पूर्ण

/* initialize the general, tx and rx parts of a queue object */
अटल व्योम bnx2x_q_fill_setup_data_cmn(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_queue_state_params *cmd_params,
				काष्ठा client_init_ramrod_data *data)
अणु
	bnx2x_q_fill_init_general_data(bp, cmd_params->q_obj,
				       &cmd_params->params.setup.gen_params,
				       &data->general,
				       &cmd_params->params.setup.flags);

	bnx2x_q_fill_init_tx_data(cmd_params->q_obj,
				  &cmd_params->params.setup.txq_params,
				  &data->tx,
				  &cmd_params->params.setup.flags);

	bnx2x_q_fill_init_rx_data(cmd_params->q_obj,
				  &cmd_params->params.setup.rxq_params,
				  &data->rx,
				  &cmd_params->params.setup.flags);

	bnx2x_q_fill_init_छोड़ो_data(cmd_params->q_obj,
				     &cmd_params->params.setup.छोड़ो_params,
				     &data->rx);
पूर्ण

/* initialize the general and tx parts of a tx-only queue object */
अटल व्योम bnx2x_q_fill_setup_tx_only(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_queue_state_params *cmd_params,
				काष्ठा tx_queue_init_ramrod_data *data)
अणु
	bnx2x_q_fill_init_general_data(bp, cmd_params->q_obj,
				       &cmd_params->params.tx_only.gen_params,
				       &data->general,
				       &cmd_params->params.tx_only.flags);

	bnx2x_q_fill_init_tx_data(cmd_params->q_obj,
				  &cmd_params->params.tx_only.txq_params,
				  &data->tx,
				  &cmd_params->params.tx_only.flags);

	DP(BNX2X_MSG_SP, "cid %d, tx bd page lo %x hi %x",
			 cmd_params->q_obj->cids[0],
			 data->tx.tx_bd_page_base.lo,
			 data->tx.tx_bd_page_base.hi);
पूर्ण

/**
 * bnx2x_q_init - init HW/FW queue
 *
 * @bp:		device handle
 * @params:
 *
 * HW/FW initial Queue configuration:
 *      - HC: Rx and Tx
 *      - CDU context validation
 *
 */
अटल अंतरभूत पूर्णांक bnx2x_q_init(काष्ठा bnx2x *bp,
			       काष्ठा bnx2x_queue_state_params *params)
अणु
	काष्ठा bnx2x_queue_sp_obj *o = params->q_obj;
	काष्ठा bnx2x_queue_init_params *init = &params->params.init;
	u16 hc_usec;
	u8 cos;

	/* Tx HC configuration */
	अगर (test_bit(BNX2X_Q_TYPE_HAS_TX, &o->type) &&
	    test_bit(BNX2X_Q_FLG_HC, &init->tx.flags)) अणु
		hc_usec = init->tx.hc_rate ? 1000000 / init->tx.hc_rate : 0;

		bnx2x_update_coalesce_sb_index(bp, init->tx.fw_sb_id,
			init->tx.sb_cq_index,
			!test_bit(BNX2X_Q_FLG_HC_EN, &init->tx.flags),
			hc_usec);
	पूर्ण

	/* Rx HC configuration */
	अगर (test_bit(BNX2X_Q_TYPE_HAS_RX, &o->type) &&
	    test_bit(BNX2X_Q_FLG_HC, &init->rx.flags)) अणु
		hc_usec = init->rx.hc_rate ? 1000000 / init->rx.hc_rate : 0;

		bnx2x_update_coalesce_sb_index(bp, init->rx.fw_sb_id,
			init->rx.sb_cq_index,
			!test_bit(BNX2X_Q_FLG_HC_EN, &init->rx.flags),
			hc_usec);
	पूर्ण

	/* Set CDU context validation values */
	क्रम (cos = 0; cos < o->max_cos; cos++) अणु
		DP(BNX2X_MSG_SP, "setting context validation. cid %d, cos %d\n",
				 o->cids[cos], cos);
		DP(BNX2X_MSG_SP, "context pointer %p\n", init->cxts[cos]);
		bnx2x_set_ctx_validation(bp, init->cxts[cos], o->cids[cos]);
	पूर्ण

	/* As no ramrod is sent, complete the command immediately  */
	o->complete_cmd(bp, o, BNX2X_Q_CMD_INIT);

	smp_mb();

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_q_send_setup_e1x(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_queue_state_params *params)
अणु
	काष्ठा bnx2x_queue_sp_obj *o = params->q_obj;
	काष्ठा client_init_ramrod_data *rdata =
		(काष्ठा client_init_ramrod_data *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	पूर्णांक ramrod = RAMROD_CMD_ID_ETH_CLIENT_SETUP;

	/* Clear the ramrod data */
	स_रखो(rdata, 0, माप(*rdata));

	/* Fill the ramrod data */
	bnx2x_q_fill_setup_data_cmn(bp, params, rdata);

	/* No need क्रम an explicit memory barrier here as दीर्घ as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * पढ़ो. If the memory पढ़ो is हटाओd we will have to put a
	 * full memory barrier there (inside bnx2x_sp_post()).
	 */
	वापस bnx2x_sp_post(bp, ramrod, o->cids[BNX2X_PRIMARY_CID_INDEX],
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), ETH_CONNECTION_TYPE);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_q_send_setup_e2(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_queue_state_params *params)
अणु
	काष्ठा bnx2x_queue_sp_obj *o = params->q_obj;
	काष्ठा client_init_ramrod_data *rdata =
		(काष्ठा client_init_ramrod_data *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	पूर्णांक ramrod = RAMROD_CMD_ID_ETH_CLIENT_SETUP;

	/* Clear the ramrod data */
	स_रखो(rdata, 0, माप(*rdata));

	/* Fill the ramrod data */
	bnx2x_q_fill_setup_data_cmn(bp, params, rdata);
	bnx2x_q_fill_setup_data_e2(bp, params, rdata);

	/* No need क्रम an explicit memory barrier here as दीर्घ as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * पढ़ो. If the memory पढ़ो is हटाओd we will have to put a
	 * full memory barrier there (inside bnx2x_sp_post()).
	 */
	वापस bnx2x_sp_post(bp, ramrod, o->cids[BNX2X_PRIMARY_CID_INDEX],
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), ETH_CONNECTION_TYPE);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_q_send_setup_tx_only(काष्ठा bnx2x *bp,
				  काष्ठा bnx2x_queue_state_params *params)
अणु
	काष्ठा bnx2x_queue_sp_obj *o = params->q_obj;
	काष्ठा tx_queue_init_ramrod_data *rdata =
		(काष्ठा tx_queue_init_ramrod_data *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	पूर्णांक ramrod = RAMROD_CMD_ID_ETH_TX_QUEUE_SETUP;
	काष्ठा bnx2x_queue_setup_tx_only_params *tx_only_params =
		&params->params.tx_only;
	u8 cid_index = tx_only_params->cid_index;

	अगर (cid_index >= o->max_cos) अणु
		BNX2X_ERR("queue[%d]: cid_index (%d) is out of range\n",
			  o->cl_id, cid_index);
		वापस -EINVAL;
	पूर्ण

	DP(BNX2X_MSG_SP, "parameters received: cos: %d sp-id: %d\n",
			 tx_only_params->gen_params.cos,
			 tx_only_params->gen_params.spcl_id);

	/* Clear the ramrod data */
	स_रखो(rdata, 0, माप(*rdata));

	/* Fill the ramrod data */
	bnx2x_q_fill_setup_tx_only(bp, params, rdata);

	DP(BNX2X_MSG_SP, "sending tx-only ramrod: cid %d, client-id %d, sp-client id %d, cos %d\n",
			 o->cids[cid_index], rdata->general.client_id,
			 rdata->general.sp_client_id, rdata->general.cos);

	/* No need क्रम an explicit memory barrier here as दीर्घ as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * पढ़ो. If the memory पढ़ो is हटाओd we will have to put a
	 * full memory barrier there (inside bnx2x_sp_post()).
	 */
	वापस bnx2x_sp_post(bp, ramrod, o->cids[cid_index],
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), ETH_CONNECTION_TYPE);
पूर्ण

अटल व्योम bnx2x_q_fill_update_data(काष्ठा bnx2x *bp,
				     काष्ठा bnx2x_queue_sp_obj *obj,
				     काष्ठा bnx2x_queue_update_params *params,
				     काष्ठा client_update_ramrod_data *data)
अणु
	/* Client ID of the client to update */
	data->client_id = obj->cl_id;

	/* Function ID of the client to update */
	data->func_id = obj->func_id;

	/* Default VLAN value */
	data->शेष_vlan = cpu_to_le16(params->def_vlan);

	/* Inner VLAN stripping */
	data->inner_vlan_removal_enable_flg =
		test_bit(BNX2X_Q_UPDATE_IN_VLAN_REM, &params->update_flags);
	data->inner_vlan_removal_change_flg =
		test_bit(BNX2X_Q_UPDATE_IN_VLAN_REM_CHNG,
			 &params->update_flags);

	/* Outer VLAN stripping */
	data->outer_vlan_removal_enable_flg =
		test_bit(BNX2X_Q_UPDATE_OUT_VLAN_REM, &params->update_flags);
	data->outer_vlan_removal_change_flg =
		test_bit(BNX2X_Q_UPDATE_OUT_VLAN_REM_CHNG,
			 &params->update_flags);

	/* Drop packets that have source MAC that करोesn't beदीर्घ to this
	 * Queue.
	 */
	data->anti_spoofing_enable_flg =
		test_bit(BNX2X_Q_UPDATE_ANTI_SPOOF, &params->update_flags);
	data->anti_spoofing_change_flg =
		test_bit(BNX2X_Q_UPDATE_ANTI_SPOOF_CHNG, &params->update_flags);

	/* Activate/Deactivate */
	data->activate_flg =
		test_bit(BNX2X_Q_UPDATE_ACTIVATE, &params->update_flags);
	data->activate_change_flg =
		test_bit(BNX2X_Q_UPDATE_ACTIVATE_CHNG, &params->update_flags);

	/* Enable शेष VLAN */
	data->शेष_vlan_enable_flg =
		test_bit(BNX2X_Q_UPDATE_DEF_VLAN_EN, &params->update_flags);
	data->शेष_vlan_change_flg =
		test_bit(BNX2X_Q_UPDATE_DEF_VLAN_EN_CHNG,
			 &params->update_flags);

	/* silent vlan removal */
	data->silent_vlan_change_flg =
		test_bit(BNX2X_Q_UPDATE_SILENT_VLAN_REM_CHNG,
			 &params->update_flags);
	data->silent_vlan_removal_flg =
		test_bit(BNX2X_Q_UPDATE_SILENT_VLAN_REM, &params->update_flags);
	data->silent_vlan_value = cpu_to_le16(params->silent_removal_value);
	data->silent_vlan_mask = cpu_to_le16(params->silent_removal_mask);

	/* tx चयनing */
	data->tx_चयनing_flg =
		test_bit(BNX2X_Q_UPDATE_TX_SWITCHING, &params->update_flags);
	data->tx_चयनing_change_flg =
		test_bit(BNX2X_Q_UPDATE_TX_SWITCHING_CHNG,
			 &params->update_flags);

	/* PTP */
	data->handle_ptp_pkts_flg =
		test_bit(BNX2X_Q_UPDATE_PTP_PKTS, &params->update_flags);
	data->handle_ptp_pkts_change_flg =
		test_bit(BNX2X_Q_UPDATE_PTP_PKTS_CHNG, &params->update_flags);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_q_send_update(काष्ठा bnx2x *bp,
				      काष्ठा bnx2x_queue_state_params *params)
अणु
	काष्ठा bnx2x_queue_sp_obj *o = params->q_obj;
	काष्ठा client_update_ramrod_data *rdata =
		(काष्ठा client_update_ramrod_data *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	काष्ठा bnx2x_queue_update_params *update_params =
		&params->params.update;
	u8 cid_index = update_params->cid_index;

	अगर (cid_index >= o->max_cos) अणु
		BNX2X_ERR("queue[%d]: cid_index (%d) is out of range\n",
			  o->cl_id, cid_index);
		वापस -EINVAL;
	पूर्ण

	/* Clear the ramrod data */
	स_रखो(rdata, 0, माप(*rdata));

	/* Fill the ramrod data */
	bnx2x_q_fill_update_data(bp, o, update_params, rdata);

	/* No need क्रम an explicit memory barrier here as दीर्घ as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * पढ़ो. If the memory पढ़ो is हटाओd we will have to put a
	 * full memory barrier there (inside bnx2x_sp_post()).
	 */
	वापस bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_CLIENT_UPDATE,
			     o->cids[cid_index], U64_HI(data_mapping),
			     U64_LO(data_mapping), ETH_CONNECTION_TYPE);
पूर्ण

/**
 * bnx2x_q_send_deactivate - send DEACTIVATE command
 *
 * @bp:		device handle
 * @params:
 *
 * implemented using the UPDATE command.
 */
अटल अंतरभूत पूर्णांक bnx2x_q_send_deactivate(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_queue_state_params *params)
अणु
	काष्ठा bnx2x_queue_update_params *update = &params->params.update;

	स_रखो(update, 0, माप(*update));

	__set_bit(BNX2X_Q_UPDATE_ACTIVATE_CHNG, &update->update_flags);

	वापस bnx2x_q_send_update(bp, params);
पूर्ण

/**
 * bnx2x_q_send_activate - send ACTIVATE command
 *
 * @bp:		device handle
 * @params:
 *
 * implemented using the UPDATE command.
 */
अटल अंतरभूत पूर्णांक bnx2x_q_send_activate(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_queue_state_params *params)
अणु
	काष्ठा bnx2x_queue_update_params *update = &params->params.update;

	स_रखो(update, 0, माप(*update));

	__set_bit(BNX2X_Q_UPDATE_ACTIVATE, &update->update_flags);
	__set_bit(BNX2X_Q_UPDATE_ACTIVATE_CHNG, &update->update_flags);

	वापस bnx2x_q_send_update(bp, params);
पूर्ण

अटल व्योम bnx2x_q_fill_update_tpa_data(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_queue_sp_obj *obj,
				काष्ठा bnx2x_queue_update_tpa_params *params,
				काष्ठा tpa_update_ramrod_data *data)
अणु
	data->client_id = obj->cl_id;
	data->complete_on_both_clients = params->complete_on_both_clients;
	data->करोnt_verअगरy_rings_छोड़ो_thr_flg =
		params->करोnt_verअगरy_thr;
	data->max_agg_size = cpu_to_le16(params->max_agg_sz);
	data->max_sges_क्रम_packet = params->max_sges_pkt;
	data->max_tpa_queues = params->max_tpa_queues;
	data->sge_buff_size = cpu_to_le16(params->sge_buff_sz);
	data->sge_page_base_hi = cpu_to_le32(U64_HI(params->sge_map));
	data->sge_page_base_lo = cpu_to_le32(U64_LO(params->sge_map));
	data->sge_छोड़ो_thr_high = cpu_to_le16(params->sge_छोड़ो_thr_high);
	data->sge_छोड़ो_thr_low = cpu_to_le16(params->sge_छोड़ो_thr_low);
	data->tpa_mode = params->tpa_mode;
	data->update_ipv4 = params->update_ipv4;
	data->update_ipv6 = params->update_ipv6;
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_q_send_update_tpa(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_queue_state_params *params)
अणु
	काष्ठा bnx2x_queue_sp_obj *o = params->q_obj;
	काष्ठा tpa_update_ramrod_data *rdata =
		(काष्ठा tpa_update_ramrod_data *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	काष्ठा bnx2x_queue_update_tpa_params *update_tpa_params =
		&params->params.update_tpa;
	u16 type;

	/* Clear the ramrod data */
	स_रखो(rdata, 0, माप(*rdata));

	/* Fill the ramrod data */
	bnx2x_q_fill_update_tpa_data(bp, o, update_tpa_params, rdata);

	/* Add the function id inside the type, so that sp post function
	 * करोesn't स्वतःmatically add the PF func-id, this is required
	 * क्रम operations करोne by PFs on behalf of their VFs
	 */
	type = ETH_CONNECTION_TYPE |
		((o->func_id) << SPE_HDR_FUNCTION_ID_SHIFT);

	/* No need क्रम an explicit memory barrier here as दीर्घ as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * पढ़ो. If the memory पढ़ो is हटाओd we will have to put a
	 * full memory barrier there (inside bnx2x_sp_post()).
	 */
	वापस bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_TPA_UPDATE,
			     o->cids[BNX2X_PRIMARY_CID_INDEX],
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), type);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_q_send_halt(काष्ठा bnx2x *bp,
				    काष्ठा bnx2x_queue_state_params *params)
अणु
	काष्ठा bnx2x_queue_sp_obj *o = params->q_obj;

	वापस bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_HALT,
			     o->cids[BNX2X_PRIMARY_CID_INDEX], 0, o->cl_id,
			     ETH_CONNECTION_TYPE);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_q_send_cfc_del(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_queue_state_params *params)
अणु
	काष्ठा bnx2x_queue_sp_obj *o = params->q_obj;
	u8 cid_idx = params->params.cfc_del.cid_index;

	अगर (cid_idx >= o->max_cos) अणु
		BNX2X_ERR("queue[%d]: cid_index (%d) is out of range\n",
			  o->cl_id, cid_idx);
		वापस -EINVAL;
	पूर्ण

	वापस bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_CFC_DEL,
			     o->cids[cid_idx], 0, 0, NONE_CONNECTION_TYPE);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_q_send_terminate(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_queue_state_params *params)
अणु
	काष्ठा bnx2x_queue_sp_obj *o = params->q_obj;
	u8 cid_index = params->params.terminate.cid_index;

	अगर (cid_index >= o->max_cos) अणु
		BNX2X_ERR("queue[%d]: cid_index (%d) is out of range\n",
			  o->cl_id, cid_index);
		वापस -EINVAL;
	पूर्ण

	वापस bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_TERMINATE,
			     o->cids[cid_index], 0, 0, ETH_CONNECTION_TYPE);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_q_send_empty(काष्ठा bnx2x *bp,
				     काष्ठा bnx2x_queue_state_params *params)
अणु
	काष्ठा bnx2x_queue_sp_obj *o = params->q_obj;

	वापस bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_EMPTY,
			     o->cids[BNX2X_PRIMARY_CID_INDEX], 0, 0,
			     ETH_CONNECTION_TYPE);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_queue_send_cmd_cmn(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_queue_state_params *params)
अणु
	चयन (params->cmd) अणु
	हाल BNX2X_Q_CMD_INIT:
		वापस bnx2x_q_init(bp, params);
	हाल BNX2X_Q_CMD_SETUP_TX_ONLY:
		वापस bnx2x_q_send_setup_tx_only(bp, params);
	हाल BNX2X_Q_CMD_DEACTIVATE:
		वापस bnx2x_q_send_deactivate(bp, params);
	हाल BNX2X_Q_CMD_ACTIVATE:
		वापस bnx2x_q_send_activate(bp, params);
	हाल BNX2X_Q_CMD_UPDATE:
		वापस bnx2x_q_send_update(bp, params);
	हाल BNX2X_Q_CMD_UPDATE_TPA:
		वापस bnx2x_q_send_update_tpa(bp, params);
	हाल BNX2X_Q_CMD_HALT:
		वापस bnx2x_q_send_halt(bp, params);
	हाल BNX2X_Q_CMD_CFC_DEL:
		वापस bnx2x_q_send_cfc_del(bp, params);
	हाल BNX2X_Q_CMD_TERMINATE:
		वापस bnx2x_q_send_terminate(bp, params);
	हाल BNX2X_Q_CMD_EMPTY:
		वापस bnx2x_q_send_empty(bp, params);
	शेष:
		BNX2X_ERR("Unknown command: %d\n", params->cmd);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_queue_send_cmd_e1x(काष्ठा bnx2x *bp,
				    काष्ठा bnx2x_queue_state_params *params)
अणु
	चयन (params->cmd) अणु
	हाल BNX2X_Q_CMD_SETUP:
		वापस bnx2x_q_send_setup_e1x(bp, params);
	हाल BNX2X_Q_CMD_INIT:
	हाल BNX2X_Q_CMD_SETUP_TX_ONLY:
	हाल BNX2X_Q_CMD_DEACTIVATE:
	हाल BNX2X_Q_CMD_ACTIVATE:
	हाल BNX2X_Q_CMD_UPDATE:
	हाल BNX2X_Q_CMD_UPDATE_TPA:
	हाल BNX2X_Q_CMD_HALT:
	हाल BNX2X_Q_CMD_CFC_DEL:
	हाल BNX2X_Q_CMD_TERMINATE:
	हाल BNX2X_Q_CMD_EMPTY:
		वापस bnx2x_queue_send_cmd_cmn(bp, params);
	शेष:
		BNX2X_ERR("Unknown command: %d\n", params->cmd);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_queue_send_cmd_e2(काष्ठा bnx2x *bp,
				   काष्ठा bnx2x_queue_state_params *params)
अणु
	चयन (params->cmd) अणु
	हाल BNX2X_Q_CMD_SETUP:
		वापस bnx2x_q_send_setup_e2(bp, params);
	हाल BNX2X_Q_CMD_INIT:
	हाल BNX2X_Q_CMD_SETUP_TX_ONLY:
	हाल BNX2X_Q_CMD_DEACTIVATE:
	हाल BNX2X_Q_CMD_ACTIVATE:
	हाल BNX2X_Q_CMD_UPDATE:
	हाल BNX2X_Q_CMD_UPDATE_TPA:
	हाल BNX2X_Q_CMD_HALT:
	हाल BNX2X_Q_CMD_CFC_DEL:
	हाल BNX2X_Q_CMD_TERMINATE:
	हाल BNX2X_Q_CMD_EMPTY:
		वापस bnx2x_queue_send_cmd_cmn(bp, params);
	शेष:
		BNX2X_ERR("Unknown command: %d\n", params->cmd);
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * bnx2x_queue_chk_transition - check state machine of a regular Queue
 *
 * @bp:		device handle
 * @o:		queue info
 * @params:	queue state
 *
 * (not Forwarding)
 * It both checks अगर the requested command is legal in a current
 * state and, अगर it's legal, sets a `next_state' in the object
 * that will be used in the completion flow to set the `state'
 * of the object.
 *
 * वापसs 0 अगर a requested command is a legal transition,
 *         -EINVAL otherwise.
 */
अटल पूर्णांक bnx2x_queue_chk_transition(काष्ठा bnx2x *bp,
				      काष्ठा bnx2x_queue_sp_obj *o,
				      काष्ठा bnx2x_queue_state_params *params)
अणु
	क्रमागत bnx2x_q_state state = o->state, next_state = BNX2X_Q_STATE_MAX;
	क्रमागत bnx2x_queue_cmd cmd = params->cmd;
	काष्ठा bnx2x_queue_update_params *update_params =
		 &params->params.update;
	u8 next_tx_only = o->num_tx_only;

	/* Forget all pending क्रम completion commands अगर a driver only state
	 * transition has been requested.
	 */
	अगर (test_bit(RAMROD_DRV_CLR_ONLY, &params->ramrod_flags)) अणु
		o->pending = 0;
		o->next_state = BNX2X_Q_STATE_MAX;
	पूर्ण

	/* Don't allow a next state transition अगर we are in the middle of
	 * the previous one.
	 */
	अगर (o->pending) अणु
		BNX2X_ERR("Blocking transition since pending was %lx\n",
			  o->pending);
		वापस -EBUSY;
	पूर्ण

	चयन (state) अणु
	हाल BNX2X_Q_STATE_RESET:
		अगर (cmd == BNX2X_Q_CMD_INIT)
			next_state = BNX2X_Q_STATE_INITIALIZED;

		अवरोध;
	हाल BNX2X_Q_STATE_INITIALIZED:
		अगर (cmd == BNX2X_Q_CMD_SETUP) अणु
			अगर (test_bit(BNX2X_Q_FLG_ACTIVE,
				     &params->params.setup.flags))
				next_state = BNX2X_Q_STATE_ACTIVE;
			अन्यथा
				next_state = BNX2X_Q_STATE_INACTIVE;
		पूर्ण

		अवरोध;
	हाल BNX2X_Q_STATE_ACTIVE:
		अगर (cmd == BNX2X_Q_CMD_DEACTIVATE)
			next_state = BNX2X_Q_STATE_INACTIVE;

		अन्यथा अगर ((cmd == BNX2X_Q_CMD_EMPTY) ||
			 (cmd == BNX2X_Q_CMD_UPDATE_TPA))
			next_state = BNX2X_Q_STATE_ACTIVE;

		अन्यथा अगर (cmd == BNX2X_Q_CMD_SETUP_TX_ONLY) अणु
			next_state = BNX2X_Q_STATE_MULTI_COS;
			next_tx_only = 1;
		पूर्ण

		अन्यथा अगर (cmd == BNX2X_Q_CMD_HALT)
			next_state = BNX2X_Q_STATE_STOPPED;

		अन्यथा अगर (cmd == BNX2X_Q_CMD_UPDATE) अणु
			/* If "active" state change is requested, update the
			 *  state accordingly.
			 */
			अगर (test_bit(BNX2X_Q_UPDATE_ACTIVATE_CHNG,
				     &update_params->update_flags) &&
			    !test_bit(BNX2X_Q_UPDATE_ACTIVATE,
				      &update_params->update_flags))
				next_state = BNX2X_Q_STATE_INACTIVE;
			अन्यथा
				next_state = BNX2X_Q_STATE_ACTIVE;
		पूर्ण

		अवरोध;
	हाल BNX2X_Q_STATE_MULTI_COS:
		अगर (cmd == BNX2X_Q_CMD_TERMINATE)
			next_state = BNX2X_Q_STATE_MCOS_TERMINATED;

		अन्यथा अगर (cmd == BNX2X_Q_CMD_SETUP_TX_ONLY) अणु
			next_state = BNX2X_Q_STATE_MULTI_COS;
			next_tx_only = o->num_tx_only + 1;
		पूर्ण

		अन्यथा अगर ((cmd == BNX2X_Q_CMD_EMPTY) ||
			 (cmd == BNX2X_Q_CMD_UPDATE_TPA))
			next_state = BNX2X_Q_STATE_MULTI_COS;

		अन्यथा अगर (cmd == BNX2X_Q_CMD_UPDATE) अणु
			/* If "active" state change is requested, update the
			 *  state accordingly.
			 */
			अगर (test_bit(BNX2X_Q_UPDATE_ACTIVATE_CHNG,
				     &update_params->update_flags) &&
			    !test_bit(BNX2X_Q_UPDATE_ACTIVATE,
				      &update_params->update_flags))
				next_state = BNX2X_Q_STATE_INACTIVE;
			अन्यथा
				next_state = BNX2X_Q_STATE_MULTI_COS;
		पूर्ण

		अवरोध;
	हाल BNX2X_Q_STATE_MCOS_TERMINATED:
		अगर (cmd == BNX2X_Q_CMD_CFC_DEL) अणु
			next_tx_only = o->num_tx_only - 1;
			अगर (next_tx_only == 0)
				next_state = BNX2X_Q_STATE_ACTIVE;
			अन्यथा
				next_state = BNX2X_Q_STATE_MULTI_COS;
		पूर्ण

		अवरोध;
	हाल BNX2X_Q_STATE_INACTIVE:
		अगर (cmd == BNX2X_Q_CMD_ACTIVATE)
			next_state = BNX2X_Q_STATE_ACTIVE;

		अन्यथा अगर ((cmd == BNX2X_Q_CMD_EMPTY) ||
			 (cmd == BNX2X_Q_CMD_UPDATE_TPA))
			next_state = BNX2X_Q_STATE_INACTIVE;

		अन्यथा अगर (cmd == BNX2X_Q_CMD_HALT)
			next_state = BNX2X_Q_STATE_STOPPED;

		अन्यथा अगर (cmd == BNX2X_Q_CMD_UPDATE) अणु
			/* If "active" state change is requested, update the
			 * state accordingly.
			 */
			अगर (test_bit(BNX2X_Q_UPDATE_ACTIVATE_CHNG,
				     &update_params->update_flags) &&
			    test_bit(BNX2X_Q_UPDATE_ACTIVATE,
				     &update_params->update_flags))अणु
				अगर (o->num_tx_only == 0)
					next_state = BNX2X_Q_STATE_ACTIVE;
				अन्यथा /* tx only queues exist क्रम this queue */
					next_state = BNX2X_Q_STATE_MULTI_COS;
			पूर्ण अन्यथा
				next_state = BNX2X_Q_STATE_INACTIVE;
		पूर्ण

		अवरोध;
	हाल BNX2X_Q_STATE_STOPPED:
		अगर (cmd == BNX2X_Q_CMD_TERMINATE)
			next_state = BNX2X_Q_STATE_TERMINATED;

		अवरोध;
	हाल BNX2X_Q_STATE_TERMINATED:
		अगर (cmd == BNX2X_Q_CMD_CFC_DEL)
			next_state = BNX2X_Q_STATE_RESET;

		अवरोध;
	शेष:
		BNX2X_ERR("Illegal state: %d\n", state);
	पूर्ण

	/* Transition is assured */
	अगर (next_state != BNX2X_Q_STATE_MAX) अणु
		DP(BNX2X_MSG_SP, "Good state transition: %d(%d)->%d\n",
				 state, cmd, next_state);
		o->next_state = next_state;
		o->next_tx_only = next_tx_only;
		वापस 0;
	पूर्ण

	DP(BNX2X_MSG_SP, "Bad state transition request: %d %d\n", state, cmd);

	वापस -EINVAL;
पूर्ण

व्योम bnx2x_init_queue_obj(काष्ठा bnx2x *bp,
			  काष्ठा bnx2x_queue_sp_obj *obj,
			  u8 cl_id, u32 *cids, u8 cid_cnt, u8 func_id,
			  व्योम *rdata,
			  dma_addr_t rdata_mapping, अचिन्हित दीर्घ type)
अणु
	स_रखो(obj, 0, माप(*obj));

	/* We support only BNX2X_MULTI_TX_COS Tx CoS at the moment */
	BUG_ON(BNX2X_MULTI_TX_COS < cid_cnt);

	स_नकल(obj->cids, cids, माप(obj->cids[0]) * cid_cnt);
	obj->max_cos = cid_cnt;
	obj->cl_id = cl_id;
	obj->func_id = func_id;
	obj->rdata = rdata;
	obj->rdata_mapping = rdata_mapping;
	obj->type = type;
	obj->next_state = BNX2X_Q_STATE_MAX;

	अगर (CHIP_IS_E1x(bp))
		obj->send_cmd = bnx2x_queue_send_cmd_e1x;
	अन्यथा
		obj->send_cmd = bnx2x_queue_send_cmd_e2;

	obj->check_transition = bnx2x_queue_chk_transition;

	obj->complete_cmd = bnx2x_queue_comp_cmd;
	obj->रुको_comp = bnx2x_queue_रुको_comp;
	obj->set_pending = bnx2x_queue_set_pending;
पूर्ण

/* वापस a queue object's logical state*/
पूर्णांक bnx2x_get_q_logical_state(काष्ठा bnx2x *bp,
			       काष्ठा bnx2x_queue_sp_obj *obj)
अणु
	चयन (obj->state) अणु
	हाल BNX2X_Q_STATE_ACTIVE:
	हाल BNX2X_Q_STATE_MULTI_COS:
		वापस BNX2X_Q_LOGICAL_STATE_ACTIVE;
	हाल BNX2X_Q_STATE_RESET:
	हाल BNX2X_Q_STATE_INITIALIZED:
	हाल BNX2X_Q_STATE_MCOS_TERMINATED:
	हाल BNX2X_Q_STATE_INACTIVE:
	हाल BNX2X_Q_STATE_STOPPED:
	हाल BNX2X_Q_STATE_TERMINATED:
	हाल BNX2X_Q_STATE_FLRED:
		वापस BNX2X_Q_LOGICAL_STATE_STOPPED;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/********************** Function state object *********************************/
क्रमागत bnx2x_func_state bnx2x_func_get_state(काष्ठा bnx2x *bp,
					   काष्ठा bnx2x_func_sp_obj *o)
अणु
	/* in the middle of transaction - वापस INVALID state */
	अगर (o->pending)
		वापस BNX2X_F_STATE_MAX;

	/* unsure the order of पढ़ोing of o->pending and o->state
	 * o->pending should be पढ़ो first
	 */
	rmb();

	वापस o->state;
पूर्ण

अटल पूर्णांक bnx2x_func_रुको_comp(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_func_sp_obj *o,
				क्रमागत bnx2x_func_cmd cmd)
अणु
	वापस bnx2x_state_रुको(bp, cmd, &o->pending);
पूर्ण

/**
 * bnx2x_func_state_change_comp - complete the state machine transition
 *
 * @bp:		device handle
 * @o:		function info
 * @cmd:	more info
 *
 * Called on state change transition. Completes the state
 * machine transition only - no HW पूर्णांकeraction.
 */
अटल अंतरभूत पूर्णांक bnx2x_func_state_change_comp(काष्ठा bnx2x *bp,
					       काष्ठा bnx2x_func_sp_obj *o,
					       क्रमागत bnx2x_func_cmd cmd)
अणु
	अचिन्हित दीर्घ cur_pending = o->pending;

	अगर (!test_and_clear_bit(cmd, &cur_pending)) अणु
		BNX2X_ERR("Bad MC reply %d for func %d in state %d pending 0x%lx, next_state %d\n",
			  cmd, BP_FUNC(bp), o->state,
			  cur_pending, o->next_state);
		वापस -EINVAL;
	पूर्ण

	DP(BNX2X_MSG_SP,
	   "Completing command %d for func %d, setting state to %d\n",
	   cmd, BP_FUNC(bp), o->next_state);

	o->state = o->next_state;
	o->next_state = BNX2X_F_STATE_MAX;

	/* It's important that o->state and o->next_state are
	 * updated beक्रमe o->pending.
	 */
	wmb();

	clear_bit(cmd, &o->pending);
	smp_mb__after_atomic();

	वापस 0;
पूर्ण

/**
 * bnx2x_func_comp_cmd - complete the state change command
 *
 * @bp:		device handle
 * @o:		function info
 * @cmd:	more info
 *
 * Checks that the arrived completion is expected.
 */
अटल पूर्णांक bnx2x_func_comp_cmd(काष्ठा bnx2x *bp,
			       काष्ठा bnx2x_func_sp_obj *o,
			       क्रमागत bnx2x_func_cmd cmd)
अणु
	/* Complete the state machine part first, check अगर it's a
	 * legal completion.
	 */
	पूर्णांक rc = bnx2x_func_state_change_comp(bp, o, cmd);
	वापस rc;
पूर्ण

/**
 * bnx2x_func_chk_transition - perक्रमm function state machine transition
 *
 * @bp:		device handle
 * @o:		function info
 * @params:	state parameters
 *
 * It both checks अगर the requested command is legal in a current
 * state and, अगर it's legal, sets a `next_state' in the object
 * that will be used in the completion flow to set the `state'
 * of the object.
 *
 * वापसs 0 अगर a requested command is a legal transition,
 *         -EINVAL otherwise.
 */
अटल पूर्णांक bnx2x_func_chk_transition(काष्ठा bnx2x *bp,
				     काष्ठा bnx2x_func_sp_obj *o,
				     काष्ठा bnx2x_func_state_params *params)
अणु
	क्रमागत bnx2x_func_state state = o->state, next_state = BNX2X_F_STATE_MAX;
	क्रमागत bnx2x_func_cmd cmd = params->cmd;

	/* Forget all pending क्रम completion commands अगर a driver only state
	 * transition has been requested.
	 */
	अगर (test_bit(RAMROD_DRV_CLR_ONLY, &params->ramrod_flags)) अणु
		o->pending = 0;
		o->next_state = BNX2X_F_STATE_MAX;
	पूर्ण

	/* Don't allow a next state transition अगर we are in the middle of
	 * the previous one.
	 */
	अगर (o->pending)
		वापस -EBUSY;

	चयन (state) अणु
	हाल BNX2X_F_STATE_RESET:
		अगर (cmd == BNX2X_F_CMD_HW_INIT)
			next_state = BNX2X_F_STATE_INITIALIZED;

		अवरोध;
	हाल BNX2X_F_STATE_INITIALIZED:
		अगर (cmd == BNX2X_F_CMD_START)
			next_state = BNX2X_F_STATE_STARTED;

		अन्यथा अगर (cmd == BNX2X_F_CMD_HW_RESET)
			next_state = BNX2X_F_STATE_RESET;

		अवरोध;
	हाल BNX2X_F_STATE_STARTED:
		अगर (cmd == BNX2X_F_CMD_STOP)
			next_state = BNX2X_F_STATE_INITIALIZED;
		/* afex ramrods can be sent only in started mode, and only
		 * अगर not pending क्रम function_stop ramrod completion
		 * क्रम these events - next state reमुख्यed STARTED.
		 */
		अन्यथा अगर ((cmd == BNX2X_F_CMD_AFEX_UPDATE) &&
			 (!test_bit(BNX2X_F_CMD_STOP, &o->pending)))
			next_state = BNX2X_F_STATE_STARTED;

		अन्यथा अगर ((cmd == BNX2X_F_CMD_AFEX_VIFLISTS) &&
			 (!test_bit(BNX2X_F_CMD_STOP, &o->pending)))
			next_state = BNX2X_F_STATE_STARTED;

		/* Switch_update ramrod can be sent in either started or
		 * tx_stopped state, and it करोesn't change the state.
		 */
		अन्यथा अगर ((cmd == BNX2X_F_CMD_SWITCH_UPDATE) &&
			 (!test_bit(BNX2X_F_CMD_STOP, &o->pending)))
			next_state = BNX2X_F_STATE_STARTED;

		अन्यथा अगर ((cmd == BNX2X_F_CMD_SET_TIMESYNC) &&
			 (!test_bit(BNX2X_F_CMD_STOP, &o->pending)))
			next_state = BNX2X_F_STATE_STARTED;

		अन्यथा अगर (cmd == BNX2X_F_CMD_TX_STOP)
			next_state = BNX2X_F_STATE_TX_STOPPED;

		अवरोध;
	हाल BNX2X_F_STATE_TX_STOPPED:
		अगर ((cmd == BNX2X_F_CMD_SWITCH_UPDATE) &&
		    (!test_bit(BNX2X_F_CMD_STOP, &o->pending)))
			next_state = BNX2X_F_STATE_TX_STOPPED;

		अन्यथा अगर ((cmd == BNX2X_F_CMD_SET_TIMESYNC) &&
			 (!test_bit(BNX2X_F_CMD_STOP, &o->pending)))
			next_state = BNX2X_F_STATE_TX_STOPPED;

		अन्यथा अगर (cmd == BNX2X_F_CMD_TX_START)
			next_state = BNX2X_F_STATE_STARTED;

		अवरोध;
	शेष:
		BNX2X_ERR("Unknown state: %d\n", state);
	पूर्ण

	/* Transition is assured */
	अगर (next_state != BNX2X_F_STATE_MAX) अणु
		DP(BNX2X_MSG_SP, "Good function state transition: %d(%d)->%d\n",
				 state, cmd, next_state);
		o->next_state = next_state;
		वापस 0;
	पूर्ण

	DP(BNX2X_MSG_SP, "Bad function state transition request: %d %d\n",
			 state, cmd);

	वापस -EINVAL;
पूर्ण

/**
 * bnx2x_func_init_func - perक्रमms HW init at function stage
 *
 * @bp:		device handle
 * @drv:
 *
 * Init HW when the current phase is
 * FW_MSG_CODE_DRV_LOAD_FUNCTION: initialize only FUNCTION-only
 * HW blocks.
 */
अटल अंतरभूत पूर्णांक bnx2x_func_init_func(काष्ठा bnx2x *bp,
				       स्थिर काष्ठा bnx2x_func_sp_drv_ops *drv)
अणु
	वापस drv->init_hw_func(bp);
पूर्ण

/**
 * bnx2x_func_init_port - perक्रमms HW init at port stage
 *
 * @bp:		device handle
 * @drv:
 *
 * Init HW when the current phase is
 * FW_MSG_CODE_DRV_LOAD_PORT: initialize PORT-only and
 * FUNCTION-only HW blocks.
 *
 */
अटल अंतरभूत पूर्णांक bnx2x_func_init_port(काष्ठा bnx2x *bp,
				       स्थिर काष्ठा bnx2x_func_sp_drv_ops *drv)
अणु
	पूर्णांक rc = drv->init_hw_port(bp);
	अगर (rc)
		वापस rc;

	वापस bnx2x_func_init_func(bp, drv);
पूर्ण

/**
 * bnx2x_func_init_cmn_chip - perक्रमms HW init at chip-common stage
 *
 * @bp:		device handle
 * @drv:
 *
 * Init HW when the current phase is
 * FW_MSG_CODE_DRV_LOAD_COMMON_CHIP: initialize COMMON_CHIP,
 * PORT-only and FUNCTION-only HW blocks.
 */
अटल अंतरभूत पूर्णांक bnx2x_func_init_cmn_chip(काष्ठा bnx2x *bp,
					स्थिर काष्ठा bnx2x_func_sp_drv_ops *drv)
अणु
	पूर्णांक rc = drv->init_hw_cmn_chip(bp);
	अगर (rc)
		वापस rc;

	वापस bnx2x_func_init_port(bp, drv);
पूर्ण

/**
 * bnx2x_func_init_cmn - perक्रमms HW init at common stage
 *
 * @bp:		device handle
 * @drv:
 *
 * Init HW when the current phase is
 * FW_MSG_CODE_DRV_LOAD_COMMON_CHIP: initialize COMMON,
 * PORT-only and FUNCTION-only HW blocks.
 */
अटल अंतरभूत पूर्णांक bnx2x_func_init_cmn(काष्ठा bnx2x *bp,
				      स्थिर काष्ठा bnx2x_func_sp_drv_ops *drv)
अणु
	पूर्णांक rc = drv->init_hw_cmn(bp);
	अगर (rc)
		वापस rc;

	वापस bnx2x_func_init_port(bp, drv);
पूर्ण

अटल पूर्णांक bnx2x_func_hw_init(काष्ठा bnx2x *bp,
			      काष्ठा bnx2x_func_state_params *params)
अणु
	u32 load_code = params->params.hw_init.load_phase;
	काष्ठा bnx2x_func_sp_obj *o = params->f_obj;
	स्थिर काष्ठा bnx2x_func_sp_drv_ops *drv = o->drv;
	पूर्णांक rc = 0;

	DP(BNX2X_MSG_SP, "function %d  load_code %x\n",
			 BP_ABS_FUNC(bp), load_code);

	/* Prepare buffers क्रम unzipping the FW */
	rc = drv->gunzip_init(bp);
	अगर (rc)
		वापस rc;

	/* Prepare FW */
	rc = drv->init_fw(bp);
	अगर (rc) अणु
		BNX2X_ERR("Error loading firmware\n");
		जाओ init_err;
	पूर्ण

	/* Handle the beginning of COMMON_XXX pases separately... */
	चयन (load_code) अणु
	हाल FW_MSG_CODE_DRV_LOAD_COMMON_CHIP:
		rc = bnx2x_func_init_cmn_chip(bp, drv);
		अगर (rc)
			जाओ init_err;

		अवरोध;
	हाल FW_MSG_CODE_DRV_LOAD_COMMON:
		rc = bnx2x_func_init_cmn(bp, drv);
		अगर (rc)
			जाओ init_err;

		अवरोध;
	हाल FW_MSG_CODE_DRV_LOAD_PORT:
		rc = bnx2x_func_init_port(bp, drv);
		अगर (rc)
			जाओ init_err;

		अवरोध;
	हाल FW_MSG_CODE_DRV_LOAD_FUNCTION:
		rc = bnx2x_func_init_func(bp, drv);
		अगर (rc)
			जाओ init_err;

		अवरोध;
	शेष:
		BNX2X_ERR("Unknown load_code (0x%x) from MCP\n", load_code);
		rc = -EINVAL;
	पूर्ण

init_err:
	drv->gunzip_end(bp);

	/* In हाल of success, complete the command immediately: no ramrods
	 * have been sent.
	 */
	अगर (!rc)
		o->complete_cmd(bp, o, BNX2X_F_CMD_HW_INIT);

	वापस rc;
पूर्ण

/**
 * bnx2x_func_reset_func - reset HW at function stage
 *
 * @bp:		device handle
 * @drv:
 *
 * Reset HW at FW_MSG_CODE_DRV_UNLOAD_FUNCTION stage: reset only
 * FUNCTION-only HW blocks.
 */
अटल अंतरभूत व्योम bnx2x_func_reset_func(काष्ठा bnx2x *bp,
					स्थिर काष्ठा bnx2x_func_sp_drv_ops *drv)
अणु
	drv->reset_hw_func(bp);
पूर्ण

/**
 * bnx2x_func_reset_port - reset HW at port stage
 *
 * @bp:		device handle
 * @drv:
 *
 * Reset HW at FW_MSG_CODE_DRV_UNLOAD_PORT stage: reset
 * FUNCTION-only and PORT-only HW blocks.
 *
 *                 !!!IMPORTANT!!!
 *
 * It's important to call reset_port beक्रमe reset_func() as the last thing
 * reset_func करोes is pf_disable() thus disabling PGLUE_B, which
 * makes impossible any DMAE transactions.
 */
अटल अंतरभूत व्योम bnx2x_func_reset_port(काष्ठा bnx2x *bp,
					स्थिर काष्ठा bnx2x_func_sp_drv_ops *drv)
अणु
	drv->reset_hw_port(bp);
	bnx2x_func_reset_func(bp, drv);
पूर्ण

/**
 * bnx2x_func_reset_cmn - reset HW at common stage
 *
 * @bp:		device handle
 * @drv:
 *
 * Reset HW at FW_MSG_CODE_DRV_UNLOAD_COMMON and
 * FW_MSG_CODE_DRV_UNLOAD_COMMON_CHIP stages: reset COMMON,
 * COMMON_CHIP, FUNCTION-only and PORT-only HW blocks.
 */
अटल अंतरभूत व्योम bnx2x_func_reset_cmn(काष्ठा bnx2x *bp,
					स्थिर काष्ठा bnx2x_func_sp_drv_ops *drv)
अणु
	bnx2x_func_reset_port(bp, drv);
	drv->reset_hw_cmn(bp);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_func_hw_reset(काष्ठा bnx2x *bp,
				      काष्ठा bnx2x_func_state_params *params)
अणु
	u32 reset_phase = params->params.hw_reset.reset_phase;
	काष्ठा bnx2x_func_sp_obj *o = params->f_obj;
	स्थिर काष्ठा bnx2x_func_sp_drv_ops *drv = o->drv;

	DP(BNX2X_MSG_SP, "function %d  reset_phase %x\n", BP_ABS_FUNC(bp),
			 reset_phase);

	चयन (reset_phase) अणु
	हाल FW_MSG_CODE_DRV_UNLOAD_COMMON:
		bnx2x_func_reset_cmn(bp, drv);
		अवरोध;
	हाल FW_MSG_CODE_DRV_UNLOAD_PORT:
		bnx2x_func_reset_port(bp, drv);
		अवरोध;
	हाल FW_MSG_CODE_DRV_UNLOAD_FUNCTION:
		bnx2x_func_reset_func(bp, drv);
		अवरोध;
	शेष:
		BNX2X_ERR("Unknown reset_phase (0x%x) from MCP\n",
			   reset_phase);
		अवरोध;
	पूर्ण

	/* Complete the command immediately: no ramrods have been sent. */
	o->complete_cmd(bp, o, BNX2X_F_CMD_HW_RESET);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_func_send_start(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_func_state_params *params)
अणु
	काष्ठा bnx2x_func_sp_obj *o = params->f_obj;
	काष्ठा function_start_data *rdata =
		(काष्ठा function_start_data *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	काष्ठा bnx2x_func_start_params *start_params = &params->params.start;

	स_रखो(rdata, 0, माप(*rdata));

	/* Fill the ramrod data with provided parameters */
	rdata->function_mode	= (u8)start_params->mf_mode;
	rdata->sd_vlan_tag	= cpu_to_le16(start_params->sd_vlan_tag);
	rdata->path_id		= BP_PATH(bp);
	rdata->network_cos_mode	= start_params->network_cos_mode;
	rdata->dmae_cmd_id	= BNX2X_FW_DMAE_C;

	rdata->vxlan_dst_port	= cpu_to_le16(start_params->vxlan_dst_port);
	rdata->geneve_dst_port	= cpu_to_le16(start_params->geneve_dst_port);
	rdata->inner_clss_l2gre	= start_params->inner_clss_l2gre;
	rdata->inner_clss_l2geneve = start_params->inner_clss_l2geneve;
	rdata->inner_clss_vxlan	= start_params->inner_clss_vxlan;
	rdata->inner_rss	= start_params->inner_rss;

	rdata->sd_accept_mf_clss_fail = start_params->class_fail;
	अगर (start_params->class_fail_ethtype) अणु
		rdata->sd_accept_mf_clss_fail_match_ethtype = 1;
		rdata->sd_accept_mf_clss_fail_ethtype =
			cpu_to_le16(start_params->class_fail_ethtype);
	पूर्ण

	rdata->sd_vlan_क्रमce_pri_flg = start_params->sd_vlan_क्रमce_pri;
	rdata->sd_vlan_क्रमce_pri_val = start_params->sd_vlan_क्रमce_pri_val;
	अगर (start_params->sd_vlan_eth_type)
		rdata->sd_vlan_eth_type =
			cpu_to_le16(start_params->sd_vlan_eth_type);
	अन्यथा
		rdata->sd_vlan_eth_type =
			cpu_to_le16(0x8100);

	rdata->no_added_tags = start_params->no_added_tags;

	rdata->c2s_pri_tt_valid = start_params->c2s_pri_valid;
	अगर (rdata->c2s_pri_tt_valid) अणु
		स_नकल(rdata->c2s_pri_trans_table.val,
		       start_params->c2s_pri,
		       MAX_VLAN_PRIORITIES);
		rdata->c2s_pri_शेष = start_params->c2s_pri_शेष;
	पूर्ण
	/* No need क्रम an explicit memory barrier here as दीर्घ we would
	 * need to ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * पढ़ो and we will have to put a full memory barrier there
	 * (inside bnx2x_sp_post()).
	 */

	वापस bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_FUNCTION_START, 0,
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), NONE_CONNECTION_TYPE);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_func_send_चयन_update(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_func_state_params *params)
अणु
	काष्ठा bnx2x_func_sp_obj *o = params->f_obj;
	काष्ठा function_update_data *rdata =
		(काष्ठा function_update_data *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	काष्ठा bnx2x_func_चयन_update_params *चयन_update_params =
		&params->params.चयन_update;

	स_रखो(rdata, 0, माप(*rdata));

	/* Fill the ramrod data with provided parameters */
	अगर (test_bit(BNX2X_F_UPDATE_TX_SWITCH_SUSPEND_CHNG,
		     &चयन_update_params->changes)) अणु
		rdata->tx_चयन_suspend_change_flg = 1;
		rdata->tx_चयन_suspend =
			test_bit(BNX2X_F_UPDATE_TX_SWITCH_SUSPEND,
				 &चयन_update_params->changes);
	पूर्ण

	अगर (test_bit(BNX2X_F_UPDATE_SD_VLAN_TAG_CHNG,
		     &चयन_update_params->changes)) अणु
		rdata->sd_vlan_tag_change_flg = 1;
		rdata->sd_vlan_tag =
			cpu_to_le16(चयन_update_params->vlan);
	पूर्ण

	अगर (test_bit(BNX2X_F_UPDATE_SD_VLAN_ETH_TYPE_CHNG,
		     &चयन_update_params->changes)) अणु
		rdata->sd_vlan_eth_type_change_flg = 1;
		rdata->sd_vlan_eth_type =
			cpu_to_le16(चयन_update_params->vlan_eth_type);
	पूर्ण

	अगर (test_bit(BNX2X_F_UPDATE_VLAN_FORCE_PRIO_CHNG,
		     &चयन_update_params->changes)) अणु
		rdata->sd_vlan_क्रमce_pri_change_flg = 1;
		अगर (test_bit(BNX2X_F_UPDATE_VLAN_FORCE_PRIO_FLAG,
			     &चयन_update_params->changes))
			rdata->sd_vlan_क्रमce_pri_flg = 1;
		rdata->sd_vlan_क्रमce_pri_flg =
			चयन_update_params->vlan_क्रमce_prio;
	पूर्ण

	अगर (test_bit(BNX2X_F_UPDATE_TUNNEL_CFG_CHNG,
		     &चयन_update_params->changes)) अणु
		rdata->update_tunn_cfg_flg = 1;
		अगर (test_bit(BNX2X_F_UPDATE_TUNNEL_INNER_CLSS_L2GRE,
			     &चयन_update_params->changes))
			rdata->inner_clss_l2gre = 1;
		अगर (test_bit(BNX2X_F_UPDATE_TUNNEL_INNER_CLSS_VXLAN,
			     &चयन_update_params->changes))
			rdata->inner_clss_vxlan = 1;
		अगर (test_bit(BNX2X_F_UPDATE_TUNNEL_INNER_CLSS_L2GENEVE,
			     &चयन_update_params->changes))
			rdata->inner_clss_l2geneve = 1;
		अगर (test_bit(BNX2X_F_UPDATE_TUNNEL_INNER_RSS,
			     &चयन_update_params->changes))
			rdata->inner_rss = 1;
		rdata->vxlan_dst_port =
			cpu_to_le16(चयन_update_params->vxlan_dst_port);
		rdata->geneve_dst_port =
			cpu_to_le16(चयन_update_params->geneve_dst_port);
	पूर्ण

	rdata->echo = SWITCH_UPDATE;

	/* No need क्रम an explicit memory barrier here as दीर्घ as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * पढ़ो. If the memory पढ़ो is हटाओd we will have to put a
	 * full memory barrier there (inside bnx2x_sp_post()).
	 */
	वापस bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_FUNCTION_UPDATE, 0,
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), NONE_CONNECTION_TYPE);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_func_send_afex_update(काष्ठा bnx2x *bp,
					 काष्ठा bnx2x_func_state_params *params)
अणु
	काष्ठा bnx2x_func_sp_obj *o = params->f_obj;
	काष्ठा function_update_data *rdata =
		(काष्ठा function_update_data *)o->afex_rdata;
	dma_addr_t data_mapping = o->afex_rdata_mapping;
	काष्ठा bnx2x_func_afex_update_params *afex_update_params =
		&params->params.afex_update;

	स_रखो(rdata, 0, माप(*rdata));

	/* Fill the ramrod data with provided parameters */
	rdata->vअगर_id_change_flg = 1;
	rdata->vअगर_id = cpu_to_le16(afex_update_params->vअगर_id);
	rdata->afex_शेष_vlan_change_flg = 1;
	rdata->afex_शेष_vlan =
		cpu_to_le16(afex_update_params->afex_शेष_vlan);
	rdata->allowed_priorities_change_flg = 1;
	rdata->allowed_priorities = afex_update_params->allowed_priorities;
	rdata->echo = AFEX_UPDATE;

	/* No need क्रम an explicit memory barrier here as दीर्घ as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * पढ़ो. If the memory पढ़ो is हटाओd we will have to put a
	 * full memory barrier there (inside bnx2x_sp_post()).
	 */
	DP(BNX2X_MSG_SP,
	   "afex: sending func_update vif_id 0x%x dvlan 0x%x prio 0x%x\n",
	   rdata->vअगर_id,
	   rdata->afex_शेष_vlan, rdata->allowed_priorities);

	वापस bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_FUNCTION_UPDATE, 0,
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), NONE_CONNECTION_TYPE);
पूर्ण

अटल
अंतरभूत पूर्णांक bnx2x_func_send_afex_vअगरlists(काष्ठा bnx2x *bp,
					 काष्ठा bnx2x_func_state_params *params)
अणु
	काष्ठा bnx2x_func_sp_obj *o = params->f_obj;
	काष्ठा afex_vअगर_list_ramrod_data *rdata =
		(काष्ठा afex_vअगर_list_ramrod_data *)o->afex_rdata;
	काष्ठा bnx2x_func_afex_vअगरlists_params *afex_vअगर_params =
		&params->params.afex_vअगरlists;
	u64 *p_rdata = (u64 *)rdata;

	स_रखो(rdata, 0, माप(*rdata));

	/* Fill the ramrod data with provided parameters */
	rdata->vअगर_list_index = cpu_to_le16(afex_vअगर_params->vअगर_list_index);
	rdata->func_bit_map          = afex_vअगर_params->func_bit_map;
	rdata->afex_vअगर_list_command = afex_vअगर_params->afex_vअगर_list_command;
	rdata->func_to_clear         = afex_vअगर_params->func_to_clear;

	/* send in echo type of sub command */
	rdata->echo = afex_vअगर_params->afex_vअगर_list_command;

	/*  No need क्रम an explicit memory barrier here as दीर्घ we would
	 *  need to ensure the ordering of writing to the SPQ element
	 *  and updating of the SPQ producer which involves a memory
	 *  पढ़ो and we will have to put a full memory barrier there
	 *  (inside bnx2x_sp_post()).
	 */

	DP(BNX2X_MSG_SP, "afex: ramrod lists, cmd 0x%x index 0x%x func_bit_map 0x%x func_to_clr 0x%x\n",
	   rdata->afex_vअगर_list_command, rdata->vअगर_list_index,
	   rdata->func_bit_map, rdata->func_to_clear);

	/* this ramrod sends data directly and not through DMA mapping */
	वापस bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_AFEX_VIF_LISTS, 0,
			     U64_HI(*p_rdata), U64_LO(*p_rdata),
			     NONE_CONNECTION_TYPE);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_func_send_stop(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_func_state_params *params)
अणु
	वापस bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_FUNCTION_STOP, 0, 0, 0,
			     NONE_CONNECTION_TYPE);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_func_send_tx_stop(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_func_state_params *params)
अणु
	वापस bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_STOP_TRAFFIC, 0, 0, 0,
			     NONE_CONNECTION_TYPE);
पूर्ण
अटल अंतरभूत पूर्णांक bnx2x_func_send_tx_start(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_func_state_params *params)
अणु
	काष्ठा bnx2x_func_sp_obj *o = params->f_obj;
	काष्ठा flow_control_configuration *rdata =
		(काष्ठा flow_control_configuration *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	काष्ठा bnx2x_func_tx_start_params *tx_start_params =
		&params->params.tx_start;
	पूर्णांक i;

	स_रखो(rdata, 0, माप(*rdata));

	rdata->dcb_enabled = tx_start_params->dcb_enabled;
	rdata->dcb_version = tx_start_params->dcb_version;
	rdata->करोnt_add_pri_0_en = tx_start_params->करोnt_add_pri_0_en;

	क्रम (i = 0; i < ARRAY_SIZE(rdata->traffic_type_to_priority_cos); i++)
		rdata->traffic_type_to_priority_cos[i] =
			tx_start_params->traffic_type_to_priority_cos[i];

	क्रम (i = 0; i < MAX_TRAFFIC_TYPES; i++)
		rdata->dcb_outer_pri[i] = tx_start_params->dcb_outer_pri[i];
	/* No need क्रम an explicit memory barrier here as दीर्घ as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * पढ़ो. If the memory पढ़ो is हटाओd we will have to put a
	 * full memory barrier there (inside bnx2x_sp_post()).
	 */
	वापस bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_START_TRAFFIC, 0,
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), NONE_CONNECTION_TYPE);
पूर्ण

अटल अंतरभूत
पूर्णांक bnx2x_func_send_set_बारync(काष्ठा bnx2x *bp,
				 काष्ठा bnx2x_func_state_params *params)
अणु
	काष्ठा bnx2x_func_sp_obj *o = params->f_obj;
	काष्ठा set_बारync_ramrod_data *rdata =
		(काष्ठा set_बारync_ramrod_data *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	काष्ठा bnx2x_func_set_बारync_params *set_बारync_params =
		&params->params.set_बारync;

	स_रखो(rdata, 0, माप(*rdata));

	/* Fill the ramrod data with provided parameters */
	rdata->drअगरt_adjust_cmd = set_बारync_params->drअगरt_adjust_cmd;
	rdata->offset_cmd = set_बारync_params->offset_cmd;
	rdata->add_sub_drअगरt_adjust_value =
		set_बारync_params->add_sub_drअगरt_adjust_value;
	rdata->drअगरt_adjust_value = set_बारync_params->drअगरt_adjust_value;
	rdata->drअगरt_adjust_period = set_बारync_params->drअगरt_adjust_period;
	rdata->offset_delta.lo =
		cpu_to_le32(U64_LO(set_बारync_params->offset_delta));
	rdata->offset_delta.hi =
		cpu_to_le32(U64_HI(set_बारync_params->offset_delta));

	DP(BNX2X_MSG_SP, "Set timesync command params: drift_cmd = %d, offset_cmd = %d, add_sub_drift = %d, drift_val = %d, drift_period = %d, offset_lo = %d, offset_hi = %d\n",
	   rdata->drअगरt_adjust_cmd, rdata->offset_cmd,
	   rdata->add_sub_drअगरt_adjust_value, rdata->drअगरt_adjust_value,
	   rdata->drअगरt_adjust_period, rdata->offset_delta.lo,
	   rdata->offset_delta.hi);

	वापस bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_SET_TIMESYNC, 0,
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), NONE_CONNECTION_TYPE);
पूर्ण

अटल पूर्णांक bnx2x_func_send_cmd(काष्ठा bnx2x *bp,
			       काष्ठा bnx2x_func_state_params *params)
अणु
	चयन (params->cmd) अणु
	हाल BNX2X_F_CMD_HW_INIT:
		वापस bnx2x_func_hw_init(bp, params);
	हाल BNX2X_F_CMD_START:
		वापस bnx2x_func_send_start(bp, params);
	हाल BNX2X_F_CMD_STOP:
		वापस bnx2x_func_send_stop(bp, params);
	हाल BNX2X_F_CMD_HW_RESET:
		वापस bnx2x_func_hw_reset(bp, params);
	हाल BNX2X_F_CMD_AFEX_UPDATE:
		वापस bnx2x_func_send_afex_update(bp, params);
	हाल BNX2X_F_CMD_AFEX_VIFLISTS:
		वापस bnx2x_func_send_afex_vअगरlists(bp, params);
	हाल BNX2X_F_CMD_TX_STOP:
		वापस bnx2x_func_send_tx_stop(bp, params);
	हाल BNX2X_F_CMD_TX_START:
		वापस bnx2x_func_send_tx_start(bp, params);
	हाल BNX2X_F_CMD_SWITCH_UPDATE:
		वापस bnx2x_func_send_चयन_update(bp, params);
	हाल BNX2X_F_CMD_SET_TIMESYNC:
		वापस bnx2x_func_send_set_बारync(bp, params);
	शेष:
		BNX2X_ERR("Unknown command: %d\n", params->cmd);
		वापस -EINVAL;
	पूर्ण
पूर्ण

व्योम bnx2x_init_func_obj(काष्ठा bnx2x *bp,
			 काष्ठा bnx2x_func_sp_obj *obj,
			 व्योम *rdata, dma_addr_t rdata_mapping,
			 व्योम *afex_rdata, dma_addr_t afex_rdata_mapping,
			 काष्ठा bnx2x_func_sp_drv_ops *drv_अगरace)
अणु
	स_रखो(obj, 0, माप(*obj));

	mutex_init(&obj->one_pending_mutex);

	obj->rdata = rdata;
	obj->rdata_mapping = rdata_mapping;
	obj->afex_rdata = afex_rdata;
	obj->afex_rdata_mapping = afex_rdata_mapping;
	obj->send_cmd = bnx2x_func_send_cmd;
	obj->check_transition = bnx2x_func_chk_transition;
	obj->complete_cmd = bnx2x_func_comp_cmd;
	obj->रुको_comp = bnx2x_func_रुको_comp;

	obj->drv = drv_अगरace;
पूर्ण

/**
 * bnx2x_func_state_change - perक्रमm Function state change transition
 *
 * @bp:		device handle
 * @params:	parameters to perक्रमm the transaction
 *
 * वापसs 0 in हाल of successfully completed transition,
 *         negative error code in हाल of failure, positive
 *         (EBUSY) value अगर there is a completion to that is
 *         still pending (possible only अगर RAMROD_COMP_WAIT is
 *         not set in params->ramrod_flags क्रम asynchronous
 *         commands).
 */
पूर्णांक bnx2x_func_state_change(काष्ठा bnx2x *bp,
			    काष्ठा bnx2x_func_state_params *params)
अणु
	काष्ठा bnx2x_func_sp_obj *o = params->f_obj;
	पूर्णांक rc, cnt = 300;
	क्रमागत bnx2x_func_cmd cmd = params->cmd;
	अचिन्हित दीर्घ *pending = &o->pending;

	mutex_lock(&o->one_pending_mutex);

	/* Check that the requested transition is legal */
	rc = o->check_transition(bp, o, params);
	अगर ((rc == -EBUSY) &&
	    (test_bit(RAMROD_RETRY, &params->ramrod_flags))) अणु
		जबतक ((rc == -EBUSY) && (--cnt > 0)) अणु
			mutex_unlock(&o->one_pending_mutex);
			msleep(10);
			mutex_lock(&o->one_pending_mutex);
			rc = o->check_transition(bp, o, params);
		पूर्ण
		अगर (rc == -EBUSY) अणु
			mutex_unlock(&o->one_pending_mutex);
			BNX2X_ERR("timeout waiting for previous ramrod completion\n");
			वापस rc;
		पूर्ण
	पूर्ण अन्यथा अगर (rc) अणु
		mutex_unlock(&o->one_pending_mutex);
		वापस rc;
	पूर्ण

	/* Set "pending" bit */
	set_bit(cmd, pending);

	/* Don't send a command अगर only driver cleanup was requested */
	अगर (test_bit(RAMROD_DRV_CLR_ONLY, &params->ramrod_flags)) अणु
		bnx2x_func_state_change_comp(bp, o, cmd);
		mutex_unlock(&o->one_pending_mutex);
	पूर्ण अन्यथा अणु
		/* Send a ramrod */
		rc = o->send_cmd(bp, params);

		mutex_unlock(&o->one_pending_mutex);

		अगर (rc) अणु
			o->next_state = BNX2X_F_STATE_MAX;
			clear_bit(cmd, pending);
			smp_mb__after_atomic();
			वापस rc;
		पूर्ण

		अगर (test_bit(RAMROD_COMP_WAIT, &params->ramrod_flags)) अणु
			rc = o->रुको_comp(bp, o, cmd);
			अगर (rc)
				वापस rc;

			वापस 0;
		पूर्ण
	पूर्ण

	वापस !!test_bit(cmd, pending);
पूर्ण
