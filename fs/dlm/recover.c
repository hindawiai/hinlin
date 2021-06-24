<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2005 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#समावेश "dlm_internal.h"
#समावेश "lockspace.h"
#समावेश "dir.h"
#समावेश "config.h"
#समावेश "ast.h"
#समावेश "memory.h"
#समावेश "rcom.h"
#समावेश "lock.h"
#समावेश "lowcomms.h"
#समावेश "member.h"
#समावेश "recover.h"


/*
 * Recovery रुकोing routines: these functions रुको क्रम a particular reply from
 * a remote node, or क्रम the remote node to report a certain status.  They need
 * to पात अगर the lockspace is stopped indicating a node has failed (perhaps
 * the one being रुकोed क्रम).
 */

/*
 * Wait until given function वापसs non-zero or lockspace is stopped
 * (LS_RECOVERY_STOP set due to failure of a node in ls_nodes).  When another
 * function thinks it could have completed the रुकोed-on task, they should wake
 * up ls_रुको_general to get an immediate response rather than रुकोing क्रम the
 * समयout.  This uses a समयout so it can check periodically अगर the रुको
 * should पात due to node failure (which करोesn't cause a wake_up).
 * This should only be called by the dlm_recoverd thपढ़ो.
 */

पूर्णांक dlm_रुको_function(काष्ठा dlm_ls *ls, पूर्णांक (*testfn) (काष्ठा dlm_ls *ls))
अणु
	पूर्णांक error = 0;
	पूर्णांक rv;

	जबतक (1) अणु
		rv = रुको_event_समयout(ls->ls_रुको_general,
					testfn(ls) || dlm_recovery_stopped(ls),
					dlm_config.ci_recover_समयr * HZ);
		अगर (rv)
			अवरोध;
		अगर (test_bit(LSFL_RCOM_WAIT, &ls->ls_flags)) अणु
			log_debug(ls, "dlm_wait_function timed out");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	अगर (dlm_recovery_stopped(ls)) अणु
		log_debug(ls, "dlm_wait_function aborted");
		error = -EINTR;
	पूर्ण
	वापस error;
पूर्ण

/*
 * An efficient way क्रम all nodes to रुको क्रम all others to have a certain
 * status.  The node with the lowest nodeid polls all the others क्रम their
 * status (रुको_status_all) and all the others poll the node with the low id
 * क्रम its accumulated result (रुको_status_low).  When all nodes have set
 * status flag X, then status flag X_ALL will be set on the low nodeid.
 */

uपूर्णांक32_t dlm_recover_status(काष्ठा dlm_ls *ls)
अणु
	uपूर्णांक32_t status;
	spin_lock(&ls->ls_recover_lock);
	status = ls->ls_recover_status;
	spin_unlock(&ls->ls_recover_lock);
	वापस status;
पूर्ण

अटल व्योम _set_recover_status(काष्ठा dlm_ls *ls, uपूर्णांक32_t status)
अणु
	ls->ls_recover_status |= status;
पूर्ण

व्योम dlm_set_recover_status(काष्ठा dlm_ls *ls, uपूर्णांक32_t status)
अणु
	spin_lock(&ls->ls_recover_lock);
	_set_recover_status(ls, status);
	spin_unlock(&ls->ls_recover_lock);
पूर्ण

अटल पूर्णांक रुको_status_all(काष्ठा dlm_ls *ls, uपूर्णांक32_t रुको_status,
			   पूर्णांक save_slots)
अणु
	काष्ठा dlm_rcom *rc = ls->ls_recover_buf;
	काष्ठा dlm_member *memb;
	पूर्णांक error = 0, delay;

	list_क्रम_each_entry(memb, &ls->ls_nodes, list) अणु
		delay = 0;
		क्रम (;;) अणु
			अगर (dlm_recovery_stopped(ls)) अणु
				error = -EINTR;
				जाओ out;
			पूर्ण

			error = dlm_rcom_status(ls, memb->nodeid, 0);
			अगर (error)
				जाओ out;

			अगर (save_slots)
				dlm_slot_save(ls, rc, memb);

			अगर (rc->rc_result & रुको_status)
				अवरोध;
			अगर (delay < 1000)
				delay += 20;
			msleep(delay);
		पूर्ण
	पूर्ण
 out:
	वापस error;
पूर्ण

अटल पूर्णांक रुको_status_low(काष्ठा dlm_ls *ls, uपूर्णांक32_t रुको_status,
			   uपूर्णांक32_t status_flags)
अणु
	काष्ठा dlm_rcom *rc = ls->ls_recover_buf;
	पूर्णांक error = 0, delay = 0, nodeid = ls->ls_low_nodeid;

	क्रम (;;) अणु
		अगर (dlm_recovery_stopped(ls)) अणु
			error = -EINTR;
			जाओ out;
		पूर्ण

		error = dlm_rcom_status(ls, nodeid, status_flags);
		अगर (error)
			अवरोध;

		अगर (rc->rc_result & रुको_status)
			अवरोध;
		अगर (delay < 1000)
			delay += 20;
		msleep(delay);
	पूर्ण
 out:
	वापस error;
पूर्ण

अटल पूर्णांक रुको_status(काष्ठा dlm_ls *ls, uपूर्णांक32_t status)
अणु
	uपूर्णांक32_t status_all = status << 1;
	पूर्णांक error;

	अगर (ls->ls_low_nodeid == dlm_our_nodeid()) अणु
		error = रुको_status_all(ls, status, 0);
		अगर (!error)
			dlm_set_recover_status(ls, status_all);
	पूर्ण अन्यथा
		error = रुको_status_low(ls, status_all, 0);

	वापस error;
पूर्ण

पूर्णांक dlm_recover_members_रुको(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_member *memb;
	काष्ठा dlm_slot *slots;
	पूर्णांक num_slots, slots_size;
	पूर्णांक error, rv;
	uपूर्णांक32_t gen;

	list_क्रम_each_entry(memb, &ls->ls_nodes, list) अणु
		memb->slot = -1;
		memb->generation = 0;
	पूर्ण

	अगर (ls->ls_low_nodeid == dlm_our_nodeid()) अणु
		error = रुको_status_all(ls, DLM_RS_NODES, 1);
		अगर (error)
			जाओ out;

		/* slots array is sparse, slots_size may be > num_slots */

		rv = dlm_slots_assign(ls, &num_slots, &slots_size, &slots, &gen);
		अगर (!rv) अणु
			spin_lock(&ls->ls_recover_lock);
			_set_recover_status(ls, DLM_RS_NODES_ALL);
			ls->ls_num_slots = num_slots;
			ls->ls_slots_size = slots_size;
			ls->ls_slots = slots;
			ls->ls_generation = gen;
			spin_unlock(&ls->ls_recover_lock);
		पूर्ण अन्यथा अणु
			dlm_set_recover_status(ls, DLM_RS_NODES_ALL);
		पूर्ण
	पूर्ण अन्यथा अणु
		error = रुको_status_low(ls, DLM_RS_NODES_ALL, DLM_RSF_NEED_SLOTS);
		अगर (error)
			जाओ out;

		dlm_slots_copy_in(ls);
	पूर्ण
 out:
	वापस error;
पूर्ण

पूर्णांक dlm_recover_directory_रुको(काष्ठा dlm_ls *ls)
अणु
	वापस रुको_status(ls, DLM_RS_सूची);
पूर्ण

पूर्णांक dlm_recover_locks_रुको(काष्ठा dlm_ls *ls)
अणु
	वापस रुको_status(ls, DLM_RS_LOCKS);
पूर्ण

पूर्णांक dlm_recover_करोne_रुको(काष्ठा dlm_ls *ls)
अणु
	वापस रुको_status(ls, DLM_RS_DONE);
पूर्ण

/*
 * The recover_list contains all the rsb's for which we've requested the new
 * master nodeid.  As replies are वापसed from the resource directories the
 * rsb's are removed from the list.  When the list is empty we're करोne.
 *
 * The recover_list is later similarly used क्रम all rsb's for which we've sent
 * new lkb's and need to receive new corresponding lkid's.
 *
 * We use the address of the rsb काष्ठा as a simple local identअगरier क्रम the
 * rsb so we can match an rcom reply with the rsb it was sent क्रम.
 */

अटल पूर्णांक recover_list_empty(काष्ठा dlm_ls *ls)
अणु
	पूर्णांक empty;

	spin_lock(&ls->ls_recover_list_lock);
	empty = list_empty(&ls->ls_recover_list);
	spin_unlock(&ls->ls_recover_list_lock);

	वापस empty;
पूर्ण

अटल व्योम recover_list_add(काष्ठा dlm_rsb *r)
अणु
	काष्ठा dlm_ls *ls = r->res_ls;

	spin_lock(&ls->ls_recover_list_lock);
	अगर (list_empty(&r->res_recover_list)) अणु
		list_add_tail(&r->res_recover_list, &ls->ls_recover_list);
		ls->ls_recover_list_count++;
		dlm_hold_rsb(r);
	पूर्ण
	spin_unlock(&ls->ls_recover_list_lock);
पूर्ण

अटल व्योम recover_list_del(काष्ठा dlm_rsb *r)
अणु
	काष्ठा dlm_ls *ls = r->res_ls;

	spin_lock(&ls->ls_recover_list_lock);
	list_del_init(&r->res_recover_list);
	ls->ls_recover_list_count--;
	spin_unlock(&ls->ls_recover_list_lock);

	dlm_put_rsb(r);
पूर्ण

अटल व्योम recover_list_clear(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_rsb *r, *s;

	spin_lock(&ls->ls_recover_list_lock);
	list_क्रम_each_entry_safe(r, s, &ls->ls_recover_list, res_recover_list) अणु
		list_del_init(&r->res_recover_list);
		r->res_recover_locks_count = 0;
		dlm_put_rsb(r);
		ls->ls_recover_list_count--;
	पूर्ण

	अगर (ls->ls_recover_list_count != 0) अणु
		log_error(ls, "warning: recover_list_count %d",
			  ls->ls_recover_list_count);
		ls->ls_recover_list_count = 0;
	पूर्ण
	spin_unlock(&ls->ls_recover_list_lock);
पूर्ण

अटल पूर्णांक recover_idr_empty(काष्ठा dlm_ls *ls)
अणु
	पूर्णांक empty = 1;

	spin_lock(&ls->ls_recover_idr_lock);
	अगर (ls->ls_recover_list_count)
		empty = 0;
	spin_unlock(&ls->ls_recover_idr_lock);

	वापस empty;
पूर्ण

अटल पूर्णांक recover_idr_add(काष्ठा dlm_rsb *r)
अणु
	काष्ठा dlm_ls *ls = r->res_ls;
	पूर्णांक rv;

	idr_preload(GFP_NOFS);
	spin_lock(&ls->ls_recover_idr_lock);
	अगर (r->res_id) अणु
		rv = -1;
		जाओ out_unlock;
	पूर्ण
	rv = idr_alloc(&ls->ls_recover_idr, r, 1, 0, GFP_NOWAIT);
	अगर (rv < 0)
		जाओ out_unlock;

	r->res_id = rv;
	ls->ls_recover_list_count++;
	dlm_hold_rsb(r);
	rv = 0;
out_unlock:
	spin_unlock(&ls->ls_recover_idr_lock);
	idr_preload_end();
	वापस rv;
पूर्ण

अटल व्योम recover_idr_del(काष्ठा dlm_rsb *r)
अणु
	काष्ठा dlm_ls *ls = r->res_ls;

	spin_lock(&ls->ls_recover_idr_lock);
	idr_हटाओ(&ls->ls_recover_idr, r->res_id);
	r->res_id = 0;
	ls->ls_recover_list_count--;
	spin_unlock(&ls->ls_recover_idr_lock);

	dlm_put_rsb(r);
पूर्ण

अटल काष्ठा dlm_rsb *recover_idr_find(काष्ठा dlm_ls *ls, uपूर्णांक64_t id)
अणु
	काष्ठा dlm_rsb *r;

	spin_lock(&ls->ls_recover_idr_lock);
	r = idr_find(&ls->ls_recover_idr, (पूर्णांक)id);
	spin_unlock(&ls->ls_recover_idr_lock);
	वापस r;
पूर्ण

अटल व्योम recover_idr_clear(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_rsb *r;
	पूर्णांक id;

	spin_lock(&ls->ls_recover_idr_lock);

	idr_क्रम_each_entry(&ls->ls_recover_idr, r, id) अणु
		idr_हटाओ(&ls->ls_recover_idr, id);
		r->res_id = 0;
		r->res_recover_locks_count = 0;
		ls->ls_recover_list_count--;

		dlm_put_rsb(r);
	पूर्ण

	अगर (ls->ls_recover_list_count != 0) अणु
		log_error(ls, "warning: recover_list_count %d",
			  ls->ls_recover_list_count);
		ls->ls_recover_list_count = 0;
	पूर्ण
	spin_unlock(&ls->ls_recover_idr_lock);
पूर्ण


/* Master recovery: find new master node क्रम rsb's that were
   mastered on nodes that have been हटाओd.

   dlm_recover_masters
   recover_master
   dlm_send_rcom_lookup            ->  receive_rcom_lookup
                                       dlm_dir_lookup
   receive_rcom_lookup_reply       <-
   dlm_recover_master_reply
   set_new_master
   set_master_lkbs
   set_lock_master
*/

/*
 * Set the lock master क्रम all LKBs in a lock queue
 * If we are the new master of the rsb, we may have received new
 * MSTCPY locks from other nodes alपढ़ोy which we need to ignore
 * when setting the new nodeid.
 */

अटल व्योम set_lock_master(काष्ठा list_head *queue, पूर्णांक nodeid)
अणु
	काष्ठा dlm_lkb *lkb;

	list_क्रम_each_entry(lkb, queue, lkb_statequeue) अणु
		अगर (!(lkb->lkb_flags & DLM_IFL_MSTCPY)) अणु
			lkb->lkb_nodeid = nodeid;
			lkb->lkb_remid = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम set_master_lkbs(काष्ठा dlm_rsb *r)
अणु
	set_lock_master(&r->res_grantqueue, r->res_nodeid);
	set_lock_master(&r->res_convertqueue, r->res_nodeid);
	set_lock_master(&r->res_रुकोqueue, r->res_nodeid);
पूर्ण

/*
 * Propagate the new master nodeid to locks
 * The NEW_MASTER flag tells dlm_recover_locks() which rsb's to consider.
 * The NEW_MASTER2 flag tells recover_lvb() and recover_grant() which
 * rsb's to consider.
 */

अटल व्योम set_new_master(काष्ठा dlm_rsb *r)
अणु
	set_master_lkbs(r);
	rsb_set_flag(r, RSB_NEW_MASTER);
	rsb_set_flag(r, RSB_NEW_MASTER2);
पूर्ण

/*
 * We करो async lookups on rsb's that need new masters.  The rsb's
 * रुकोing क्रम a lookup reply are kept on the recover_list.
 *
 * Another node recovering the master may have sent us a rcom lookup,
 * and our dlm_master_lookup() set it as the new master, aदीर्घ with
 * NEW_MASTER so that we'll recover it here (this implies dir_nodeid
 * equals our_nodeid below).
 */

अटल पूर्णांक recover_master(काष्ठा dlm_rsb *r, अचिन्हित पूर्णांक *count)
अणु
	काष्ठा dlm_ls *ls = r->res_ls;
	पूर्णांक our_nodeid, dir_nodeid;
	पूर्णांक is_हटाओd = 0;
	पूर्णांक error;

	अगर (is_master(r))
		वापस 0;

	is_हटाओd = dlm_is_हटाओd(ls, r->res_nodeid);

	अगर (!is_हटाओd && !rsb_flag(r, RSB_NEW_MASTER))
		वापस 0;

	our_nodeid = dlm_our_nodeid();
	dir_nodeid = dlm_dir_nodeid(r);

	अगर (dir_nodeid == our_nodeid) अणु
		अगर (is_हटाओd) अणु
			r->res_master_nodeid = our_nodeid;
			r->res_nodeid = 0;
		पूर्ण

		/* set master of lkbs to ourself when is_हटाओd, or to
		   another new master which we set aदीर्घ with NEW_MASTER
		   in dlm_master_lookup */
		set_new_master(r);
		error = 0;
	पूर्ण अन्यथा अणु
		recover_idr_add(r);
		error = dlm_send_rcom_lookup(r, dir_nodeid);
	पूर्ण

	(*count)++;
	वापस error;
पूर्ण

/*
 * All MSTCPY locks are purged and rebuilt, even अगर the master stayed the same.
 * This is necessary because recovery can be started, पातed and restarted,
 * causing the master nodeid to briefly change during the पातed recovery, and
 * change back to the original value in the second recovery.  The MSTCPY locks
 * may or may not have been purged during the पातed recovery.  Another node
 * with an outstanding request in रुकोers list and a request reply saved in the
 * requestqueue, cannot know whether it should ignore the reply and resend the
 * request, or accept the reply and complete the request.  It must करो the
 * क्रमmer अगर the remote node purged MSTCPY locks, and it must करो the later अगर
 * the remote node did not.  This is solved by always purging MSTCPY locks, in
 * which हाल, the request reply would always be ignored and the request
 * resent.
 */

अटल पूर्णांक recover_master_अटल(काष्ठा dlm_rsb *r, अचिन्हित पूर्णांक *count)
अणु
	पूर्णांक dir_nodeid = dlm_dir_nodeid(r);
	पूर्णांक new_master = dir_nodeid;

	अगर (dir_nodeid == dlm_our_nodeid())
		new_master = 0;

	dlm_purge_mstcpy_locks(r);
	r->res_master_nodeid = dir_nodeid;
	r->res_nodeid = new_master;
	set_new_master(r);
	(*count)++;
	वापस 0;
पूर्ण

/*
 * Go through local root resources and क्रम each rsb which has a master which
 * has departed, get the new master nodeid from the directory.  The dir will
 * assign mastery to the first node to look up the new master.  That means
 * we'll discover in this lookup if we're the new master of any rsb's.
 *
 * We fire off all the dir lookup requests inभागidually and asynchronously to
 * the correct dir node.
 */

पूर्णांक dlm_recover_masters(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_rsb *r;
	अचिन्हित पूर्णांक total = 0;
	अचिन्हित पूर्णांक count = 0;
	पूर्णांक nodir = dlm_no_directory(ls);
	पूर्णांक error;

	log_rinfo(ls, "dlm_recover_masters");

	करोwn_पढ़ो(&ls->ls_root_sem);
	list_क्रम_each_entry(r, &ls->ls_root_list, res_root_list) अणु
		अगर (dlm_recovery_stopped(ls)) अणु
			up_पढ़ो(&ls->ls_root_sem);
			error = -EINTR;
			जाओ out;
		पूर्ण

		lock_rsb(r);
		अगर (nodir)
			error = recover_master_अटल(r, &count);
		अन्यथा
			error = recover_master(r, &count);
		unlock_rsb(r);
		cond_resched();
		total++;

		अगर (error) अणु
			up_पढ़ो(&ls->ls_root_sem);
			जाओ out;
		पूर्ण
	पूर्ण
	up_पढ़ो(&ls->ls_root_sem);

	log_rinfo(ls, "dlm_recover_masters %u of %u", count, total);

	error = dlm_रुको_function(ls, &recover_idr_empty);
 out:
	अगर (error)
		recover_idr_clear(ls);
	वापस error;
पूर्ण

पूर्णांक dlm_recover_master_reply(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc)
अणु
	काष्ठा dlm_rsb *r;
	पूर्णांक ret_nodeid, new_master;

	r = recover_idr_find(ls, rc->rc_id);
	अगर (!r) अणु
		log_error(ls, "dlm_recover_master_reply no id %llx",
			  (अचिन्हित दीर्घ दीर्घ)rc->rc_id);
		जाओ out;
	पूर्ण

	ret_nodeid = rc->rc_result;

	अगर (ret_nodeid == dlm_our_nodeid())
		new_master = 0;
	अन्यथा
		new_master = ret_nodeid;

	lock_rsb(r);
	r->res_master_nodeid = ret_nodeid;
	r->res_nodeid = new_master;
	set_new_master(r);
	unlock_rsb(r);
	recover_idr_del(r);

	अगर (recover_idr_empty(ls))
		wake_up(&ls->ls_रुको_general);
 out:
	वापस 0;
पूर्ण


/* Lock recovery: rebuild the process-copy locks we hold on a
   remastered rsb on the new rsb master.

   dlm_recover_locks
   recover_locks
   recover_locks_queue
   dlm_send_rcom_lock              ->  receive_rcom_lock
                                       dlm_recover_master_copy
   receive_rcom_lock_reply         <-
   dlm_recover_process_copy
*/


/*
 * keep a count of the number of lkb's we send to the new master; when we get
 * an equal number of replies then recovery क्रम the rsb is करोne
 */

अटल पूर्णांक recover_locks_queue(काष्ठा dlm_rsb *r, काष्ठा list_head *head)
अणु
	काष्ठा dlm_lkb *lkb;
	पूर्णांक error = 0;

	list_क्रम_each_entry(lkb, head, lkb_statequeue) अणु
	   	error = dlm_send_rcom_lock(r, lkb);
		अगर (error)
			अवरोध;
		r->res_recover_locks_count++;
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक recover_locks(काष्ठा dlm_rsb *r)
अणु
	पूर्णांक error = 0;

	lock_rsb(r);

	DLM_ASSERT(!r->res_recover_locks_count, dlm_dump_rsb(r););

	error = recover_locks_queue(r, &r->res_grantqueue);
	अगर (error)
		जाओ out;
	error = recover_locks_queue(r, &r->res_convertqueue);
	अगर (error)
		जाओ out;
	error = recover_locks_queue(r, &r->res_रुकोqueue);
	अगर (error)
		जाओ out;

	अगर (r->res_recover_locks_count)
		recover_list_add(r);
	अन्यथा
		rsb_clear_flag(r, RSB_NEW_MASTER);
 out:
	unlock_rsb(r);
	वापस error;
पूर्ण

पूर्णांक dlm_recover_locks(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_rsb *r;
	पूर्णांक error, count = 0;

	करोwn_पढ़ो(&ls->ls_root_sem);
	list_क्रम_each_entry(r, &ls->ls_root_list, res_root_list) अणु
		अगर (is_master(r)) अणु
			rsb_clear_flag(r, RSB_NEW_MASTER);
			जारी;
		पूर्ण

		अगर (!rsb_flag(r, RSB_NEW_MASTER))
			जारी;

		अगर (dlm_recovery_stopped(ls)) अणु
			error = -EINTR;
			up_पढ़ो(&ls->ls_root_sem);
			जाओ out;
		पूर्ण

		error = recover_locks(r);
		अगर (error) अणु
			up_पढ़ो(&ls->ls_root_sem);
			जाओ out;
		पूर्ण

		count += r->res_recover_locks_count;
	पूर्ण
	up_पढ़ो(&ls->ls_root_sem);

	log_rinfo(ls, "dlm_recover_locks %d out", count);

	error = dlm_रुको_function(ls, &recover_list_empty);
 out:
	अगर (error)
		recover_list_clear(ls);
	वापस error;
पूर्ण

व्योम dlm_recovered_lock(काष्ठा dlm_rsb *r)
अणु
	DLM_ASSERT(rsb_flag(r, RSB_NEW_MASTER), dlm_dump_rsb(r););

	r->res_recover_locks_count--;
	अगर (!r->res_recover_locks_count) अणु
		rsb_clear_flag(r, RSB_NEW_MASTER);
		recover_list_del(r);
	पूर्ण

	अगर (recover_list_empty(r->res_ls))
		wake_up(&r->res_ls->ls_रुको_general);
पूर्ण

/*
 * The lvb needs to be recovered on all master rsb's.  This includes setting
 * the VALNOTVALID flag अगर necessary, and determining the correct lvb contents
 * based on the lvb's of the locks held on the rsb.
 *
 * RSB_VALNOTVALID is set in two हालs:
 *
 * 1. we are master, but not new, and we purged an EX/PW lock held by a
 * failed node (in dlm_recover_purge which set RSB_RECOVER_LVB_INVAL)
 *
 * 2. we are a new master, and there are only NL/CR locks left.
 * (We could probably improve this by only invaliding in this way when
 * the previous master left uncleanly.  VMS करोcs mention that.)
 *
 * The LVB contents are only considered क्रम changing when this is a new master
 * of the rsb (NEW_MASTER2).  Then, the rsb's lvb is taken from any lkb with
 * mode > CR.  If no lkb's exist with mode above CR, the lvb contents are taken
 * from the lkb with the largest lvb sequence number.
 */

अटल व्योम recover_lvb(काष्ठा dlm_rsb *r)
अणु
	काष्ठा dlm_lkb *lkb, *high_lkb = शून्य;
	uपूर्णांक32_t high_seq = 0;
	पूर्णांक lock_lvb_exists = 0;
	पूर्णांक big_lock_exists = 0;
	पूर्णांक lvblen = r->res_ls->ls_lvblen;

	अगर (!rsb_flag(r, RSB_NEW_MASTER2) &&
	    rsb_flag(r, RSB_RECOVER_LVB_INVAL)) अणु
		/* हाल 1 above */
		rsb_set_flag(r, RSB_VALNOTVALID);
		वापस;
	पूर्ण

	अगर (!rsb_flag(r, RSB_NEW_MASTER2))
		वापस;

	/* we are the new master, so figure out अगर VALNOTVALID should
	   be set, and set the rsb lvb from the best lkb available. */

	list_क्रम_each_entry(lkb, &r->res_grantqueue, lkb_statequeue) अणु
		अगर (!(lkb->lkb_exflags & DLM_LKF_VALBLK))
			जारी;

		lock_lvb_exists = 1;

		अगर (lkb->lkb_grmode > DLM_LOCK_CR) अणु
			big_lock_exists = 1;
			जाओ setflag;
		पूर्ण

		अगर (((पूर्णांक)lkb->lkb_lvbseq - (पूर्णांक)high_seq) >= 0) अणु
			high_lkb = lkb;
			high_seq = lkb->lkb_lvbseq;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(lkb, &r->res_convertqueue, lkb_statequeue) अणु
		अगर (!(lkb->lkb_exflags & DLM_LKF_VALBLK))
			जारी;

		lock_lvb_exists = 1;

		अगर (lkb->lkb_grmode > DLM_LOCK_CR) अणु
			big_lock_exists = 1;
			जाओ setflag;
		पूर्ण

		अगर (((पूर्णांक)lkb->lkb_lvbseq - (पूर्णांक)high_seq) >= 0) अणु
			high_lkb = lkb;
			high_seq = lkb->lkb_lvbseq;
		पूर्ण
	पूर्ण

 setflag:
	अगर (!lock_lvb_exists)
		जाओ out;

	/* lvb is invalidated अगर only NL/CR locks reमुख्य */
	अगर (!big_lock_exists)
		rsb_set_flag(r, RSB_VALNOTVALID);

	अगर (!r->res_lvbptr) अणु
		r->res_lvbptr = dlm_allocate_lvb(r->res_ls);
		अगर (!r->res_lvbptr)
			जाओ out;
	पूर्ण

	अगर (big_lock_exists) अणु
		r->res_lvbseq = lkb->lkb_lvbseq;
		स_नकल(r->res_lvbptr, lkb->lkb_lvbptr, lvblen);
	पूर्ण अन्यथा अगर (high_lkb) अणु
		r->res_lvbseq = high_lkb->lkb_lvbseq;
		स_नकल(r->res_lvbptr, high_lkb->lkb_lvbptr, lvblen);
	पूर्ण अन्यथा अणु
		r->res_lvbseq = 0;
		स_रखो(r->res_lvbptr, 0, lvblen);
	पूर्ण
 out:
	वापस;
पूर्ण

/* All master rsb's flagged RECOVER_CONVERT need to be looked at.  The locks
   converting PR->CW or CW->PR need to have their lkb_grmode set. */

अटल व्योम recover_conversion(काष्ठा dlm_rsb *r)
अणु
	काष्ठा dlm_ls *ls = r->res_ls;
	काष्ठा dlm_lkb *lkb;
	पूर्णांक grmode = -1;

	list_क्रम_each_entry(lkb, &r->res_grantqueue, lkb_statequeue) अणु
		अगर (lkb->lkb_grmode == DLM_LOCK_PR ||
		    lkb->lkb_grmode == DLM_LOCK_CW) अणु
			grmode = lkb->lkb_grmode;
			अवरोध;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(lkb, &r->res_convertqueue, lkb_statequeue) अणु
		अगर (lkb->lkb_grmode != DLM_LOCK_IV)
			जारी;
		अगर (grmode == -1) अणु
			log_debug(ls, "recover_conversion %x set gr to rq %d",
				  lkb->lkb_id, lkb->lkb_rqmode);
			lkb->lkb_grmode = lkb->lkb_rqmode;
		पूर्ण अन्यथा अणु
			log_debug(ls, "recover_conversion %x set gr %d",
				  lkb->lkb_id, grmode);
			lkb->lkb_grmode = grmode;
		पूर्ण
	पूर्ण
पूर्ण

/* We've become the new master क्रम this rsb and रुकोing/converting locks may
   need to be granted in dlm_recover_grant() due to locks that may have
   existed from a हटाओd node. */

अटल व्योम recover_grant(काष्ठा dlm_rsb *r)
अणु
	अगर (!list_empty(&r->res_रुकोqueue) || !list_empty(&r->res_convertqueue))
		rsb_set_flag(r, RSB_RECOVER_GRANT);
पूर्ण

व्योम dlm_recover_rsbs(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_rsb *r;
	अचिन्हित पूर्णांक count = 0;

	करोwn_पढ़ो(&ls->ls_root_sem);
	list_क्रम_each_entry(r, &ls->ls_root_list, res_root_list) अणु
		lock_rsb(r);
		अगर (is_master(r)) अणु
			अगर (rsb_flag(r, RSB_RECOVER_CONVERT))
				recover_conversion(r);

			/* recover lvb beक्रमe granting locks so the updated
			   lvb/VALNOTVALID is presented in the completion */
			recover_lvb(r);

			अगर (rsb_flag(r, RSB_NEW_MASTER2))
				recover_grant(r);
			count++;
		पूर्ण अन्यथा अणु
			rsb_clear_flag(r, RSB_VALNOTVALID);
		पूर्ण
		rsb_clear_flag(r, RSB_RECOVER_CONVERT);
		rsb_clear_flag(r, RSB_RECOVER_LVB_INVAL);
		rsb_clear_flag(r, RSB_NEW_MASTER2);
		unlock_rsb(r);
	पूर्ण
	up_पढ़ो(&ls->ls_root_sem);

	अगर (count)
		log_rinfo(ls, "dlm_recover_rsbs %d done", count);
पूर्ण

/* Create a single list of all root rsb's to be used during recovery */

पूर्णांक dlm_create_root_list(काष्ठा dlm_ls *ls)
अणु
	काष्ठा rb_node *n;
	काष्ठा dlm_rsb *r;
	पूर्णांक i, error = 0;

	करोwn_ग_लिखो(&ls->ls_root_sem);
	अगर (!list_empty(&ls->ls_root_list)) अणु
		log_error(ls, "root list not empty");
		error = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < ls->ls_rsbtbl_size; i++) अणु
		spin_lock(&ls->ls_rsbtbl[i].lock);
		क्रम (n = rb_first(&ls->ls_rsbtbl[i].keep); n; n = rb_next(n)) अणु
			r = rb_entry(n, काष्ठा dlm_rsb, res_hashnode);
			list_add(&r->res_root_list, &ls->ls_root_list);
			dlm_hold_rsb(r);
		पूर्ण

		अगर (!RB_EMPTY_ROOT(&ls->ls_rsbtbl[i].toss))
			log_error(ls, "dlm_create_root_list toss not empty");
		spin_unlock(&ls->ls_rsbtbl[i].lock);
	पूर्ण
 out:
	up_ग_लिखो(&ls->ls_root_sem);
	वापस error;
पूर्ण

व्योम dlm_release_root_list(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_rsb *r, *safe;

	करोwn_ग_लिखो(&ls->ls_root_sem);
	list_क्रम_each_entry_safe(r, safe, &ls->ls_root_list, res_root_list) अणु
		list_del_init(&r->res_root_list);
		dlm_put_rsb(r);
	पूर्ण
	up_ग_लिखो(&ls->ls_root_sem);
पूर्ण

व्योम dlm_clear_toss(काष्ठा dlm_ls *ls)
अणु
	काष्ठा rb_node *n, *next;
	काष्ठा dlm_rsb *r;
	अचिन्हित पूर्णांक count = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ls->ls_rsbtbl_size; i++) अणु
		spin_lock(&ls->ls_rsbtbl[i].lock);
		क्रम (n = rb_first(&ls->ls_rsbtbl[i].toss); n; n = next) अणु
			next = rb_next(n);
			r = rb_entry(n, काष्ठा dlm_rsb, res_hashnode);
			rb_erase(n, &ls->ls_rsbtbl[i].toss);
			dlm_मुक्त_rsb(r);
			count++;
		पूर्ण
		spin_unlock(&ls->ls_rsbtbl[i].lock);
	पूर्ण

	अगर (count)
		log_rinfo(ls, "dlm_clear_toss %u done", count);
पूर्ण

