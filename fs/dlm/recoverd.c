<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2011 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#समावेश "dlm_internal.h"
#समावेश "lockspace.h"
#समावेश "member.h"
#समावेश "dir.h"
#समावेश "ast.h"
#समावेश "recover.h"
#समावेश "lowcomms.h"
#समावेश "lock.h"
#समावेश "requestqueue.h"
#समावेश "recoverd.h"


/* If the start क्रम which we're re-enabling locking (seq) has been superseded
   by a newer stop (ls_recover_seq), we need to leave locking disabled.

   We suspend dlm_recv thपढ़ोs here to aव्योम the race where dlm_recv a) sees
   locking stopped and b) adds a message to the requestqueue, but dlm_recoverd
   enables locking and clears the requestqueue between a and b. */

अटल पूर्णांक enable_locking(काष्ठा dlm_ls *ls, uपूर्णांक64_t seq)
अणु
	पूर्णांक error = -EINTR;

	करोwn_ग_लिखो(&ls->ls_recv_active);

	spin_lock(&ls->ls_recover_lock);
	अगर (ls->ls_recover_seq == seq) अणु
		set_bit(LSFL_RUNNING, &ls->ls_flags);
		/* unblocks processes रुकोing to enter the dlm */
		up_ग_लिखो(&ls->ls_in_recovery);
		clear_bit(LSFL_RECOVER_LOCK, &ls->ls_flags);
		error = 0;
	पूर्ण
	spin_unlock(&ls->ls_recover_lock);

	up_ग_लिखो(&ls->ls_recv_active);
	वापस error;
पूर्ण

अटल पूर्णांक ls_recover(काष्ठा dlm_ls *ls, काष्ठा dlm_recover *rv)
अणु
	अचिन्हित दीर्घ start;
	पूर्णांक error, neg = 0;

	log_rinfo(ls, "dlm_recover %llu", (अचिन्हित दीर्घ दीर्घ)rv->seq);

	mutex_lock(&ls->ls_recoverd_active);

	dlm_callback_suspend(ls);

	dlm_clear_toss(ls);

	/*
	 * This list of root rsb's will be the basis of most of the recovery
	 * routines.
	 */

	dlm_create_root_list(ls);

	/*
	 * Add or हटाओ nodes from the lockspace's ls_nodes list.
	 */

	error = dlm_recover_members(ls, rv, &neg);
	अगर (error) अणु
		log_rinfo(ls, "dlm_recover_members error %d", error);
		जाओ fail;
	पूर्ण

	dlm_recover_dir_nodeid(ls);

	ls->ls_recover_dir_sent_res = 0;
	ls->ls_recover_dir_sent_msg = 0;
	ls->ls_recover_locks_in = 0;

	dlm_set_recover_status(ls, DLM_RS_NODES);

	error = dlm_recover_members_रुको(ls);
	अगर (error) अणु
		log_rinfo(ls, "dlm_recover_members_wait error %d", error);
		जाओ fail;
	पूर्ण

	start = jअगरfies;

	/*
	 * Rebuild our own share of the directory by collecting from all other
	 * nodes their master rsb names that hash to us.
	 */

	error = dlm_recover_directory(ls);
	अगर (error) अणु
		log_rinfo(ls, "dlm_recover_directory error %d", error);
		जाओ fail;
	पूर्ण

	dlm_set_recover_status(ls, DLM_RS_सूची);

	error = dlm_recover_directory_रुको(ls);
	अगर (error) अणु
		log_rinfo(ls, "dlm_recover_directory_wait error %d", error);
		जाओ fail;
	पूर्ण

	log_rinfo(ls, "dlm_recover_directory %u out %u messages",
		  ls->ls_recover_dir_sent_res, ls->ls_recover_dir_sent_msg);

	/*
	 * We may have outstanding operations that are रुकोing क्रम a reply from
	 * a failed node.  Mark these to be resent after recovery.  Unlock and
	 * cancel ops can just be completed.
	 */

	dlm_recover_रुकोers_pre(ls);

	error = dlm_recovery_stopped(ls);
	अगर (error)
		जाओ fail;

	अगर (neg || dlm_no_directory(ls)) अणु
		/*
		 * Clear lkb's क्रम departed nodes.
		 */

		dlm_recover_purge(ls);

		/*
		 * Get new master nodeid's for rsb's that were mastered on
		 * departed nodes.
		 */

		error = dlm_recover_masters(ls);
		अगर (error) अणु
			log_rinfo(ls, "dlm_recover_masters error %d", error);
			जाओ fail;
		पूर्ण

		/*
		 * Send our locks on remastered rsb's to the new masters.
		 */

		error = dlm_recover_locks(ls);
		अगर (error) अणु
			log_rinfo(ls, "dlm_recover_locks error %d", error);
			जाओ fail;
		पूर्ण

		dlm_set_recover_status(ls, DLM_RS_LOCKS);

		error = dlm_recover_locks_रुको(ls);
		अगर (error) अणु
			log_rinfo(ls, "dlm_recover_locks_wait error %d", error);
			जाओ fail;
		पूर्ण

		log_rinfo(ls, "dlm_recover_locks %u in",
			  ls->ls_recover_locks_in);

		/*
		 * Finalize state in master rsb's now that all locks can be
		 * checked.  This includes conversion resolution and lvb
		 * settings.
		 */

		dlm_recover_rsbs(ls);
	पूर्ण अन्यथा अणु
		/*
		 * Other lockspace members may be going through the "neg" steps
		 * जबतक also adding us to the lockspace, in which हाल they'll
		 * be करोing the recover_locks (RS_LOCKS) barrier.
		 */
		dlm_set_recover_status(ls, DLM_RS_LOCKS);

		error = dlm_recover_locks_रुको(ls);
		अगर (error) अणु
			log_rinfo(ls, "dlm_recover_locks_wait error %d", error);
			जाओ fail;
		पूर्ण
	पूर्ण

	dlm_release_root_list(ls);

	/*
	 * Purge directory-related requests that are saved in requestqueue.
	 * All dir requests from beक्रमe recovery are invalid now due to the dir
	 * rebuild and will be resent by the requesting nodes.
	 */

	dlm_purge_requestqueue(ls);

	dlm_set_recover_status(ls, DLM_RS_DONE);

	error = dlm_recover_करोne_रुको(ls);
	अगर (error) अणु
		log_rinfo(ls, "dlm_recover_done_wait error %d", error);
		जाओ fail;
	पूर्ण

	dlm_clear_members_gone(ls);

	dlm_adjust_समयouts(ls);

	dlm_callback_resume(ls);

	error = enable_locking(ls, rv->seq);
	अगर (error) अणु
		log_rinfo(ls, "enable_locking error %d", error);
		जाओ fail;
	पूर्ण

	error = dlm_process_requestqueue(ls);
	अगर (error) अणु
		log_rinfo(ls, "dlm_process_requestqueue error %d", error);
		जाओ fail;
	पूर्ण

	error = dlm_recover_रुकोers_post(ls);
	अगर (error) अणु
		log_rinfo(ls, "dlm_recover_waiters_post error %d", error);
		जाओ fail;
	पूर्ण

	dlm_recover_grant(ls);

	log_rinfo(ls, "dlm_recover %llu generation %u done: %u ms",
		  (अचिन्हित दीर्घ दीर्घ)rv->seq, ls->ls_generation,
		  jअगरfies_to_msecs(jअगरfies - start));
	mutex_unlock(&ls->ls_recoverd_active);

	dlm_lsop_recover_करोne(ls);
	वापस 0;

 fail:
	dlm_release_root_list(ls);
	log_rinfo(ls, "dlm_recover %llu error %d",
		  (अचिन्हित दीर्घ दीर्घ)rv->seq, error);
	mutex_unlock(&ls->ls_recoverd_active);
	वापस error;
पूर्ण

/* The dlm_ls_start() that created the rv we take here may alपढ़ोy have been
   stopped via dlm_ls_stop(); in that हाल we need to leave the RECOVERY_STOP
   flag set. */

अटल व्योम करो_ls_recovery(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_recover *rv = शून्य;

	spin_lock(&ls->ls_recover_lock);
	rv = ls->ls_recover_args;
	ls->ls_recover_args = शून्य;
	अगर (rv && ls->ls_recover_seq == rv->seq)
		clear_bit(LSFL_RECOVER_STOP, &ls->ls_flags);
	spin_unlock(&ls->ls_recover_lock);

	अगर (rv) अणु
		ls_recover(ls, rv);
		kमुक्त(rv->nodes);
		kमुक्त(rv);
	पूर्ण
पूर्ण

अटल पूर्णांक dlm_recoverd(व्योम *arg)
अणु
	काष्ठा dlm_ls *ls;

	ls = dlm_find_lockspace_local(arg);
	अगर (!ls) अणु
		log_prपूर्णांक("dlm_recoverd: no lockspace %p", arg);
		वापस -1;
	पूर्ण

	करोwn_ग_लिखो(&ls->ls_in_recovery);
	set_bit(LSFL_RECOVER_LOCK, &ls->ls_flags);
	wake_up(&ls->ls_recover_lock_रुको);

	जबतक (1) अणु
		/*
		 * We call kthपढ़ो_should_stop() after set_current_state().
		 * This is because it works correctly अगर kthपढ़ो_stop() is
		 * called just beक्रमe set_current_state().
		 */
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (kthपढ़ो_should_stop()) अणु
			set_current_state(TASK_RUNNING);
			अवरोध;
		पूर्ण
		अगर (!test_bit(LSFL_RECOVER_WORK, &ls->ls_flags) &&
		    !test_bit(LSFL_RECOVER_DOWN, &ls->ls_flags)) अणु
			अगर (kthपढ़ो_should_stop())
				अवरोध;
			schedule();
		पूर्ण
		set_current_state(TASK_RUNNING);

		अगर (test_and_clear_bit(LSFL_RECOVER_DOWN, &ls->ls_flags)) अणु
			करोwn_ग_लिखो(&ls->ls_in_recovery);
			set_bit(LSFL_RECOVER_LOCK, &ls->ls_flags);
			wake_up(&ls->ls_recover_lock_रुको);
		पूर्ण

		अगर (test_and_clear_bit(LSFL_RECOVER_WORK, &ls->ls_flags))
			करो_ls_recovery(ls);
	पूर्ण

	अगर (test_bit(LSFL_RECOVER_LOCK, &ls->ls_flags))
		up_ग_लिखो(&ls->ls_in_recovery);

	dlm_put_lockspace(ls);
	वापस 0;
पूर्ण

पूर्णांक dlm_recoverd_start(काष्ठा dlm_ls *ls)
अणु
	काष्ठा task_काष्ठा *p;
	पूर्णांक error = 0;

	p = kthपढ़ो_run(dlm_recoverd, ls, "dlm_recoverd");
	अगर (IS_ERR(p))
		error = PTR_ERR(p);
	अन्यथा
                ls->ls_recoverd_task = p;
	वापस error;
पूर्ण

व्योम dlm_recoverd_stop(काष्ठा dlm_ls *ls)
अणु
	kthपढ़ो_stop(ls->ls_recoverd_task);
पूर्ण

व्योम dlm_recoverd_suspend(काष्ठा dlm_ls *ls)
अणु
	wake_up(&ls->ls_रुको_general);
	mutex_lock(&ls->ls_recoverd_active);
पूर्ण

व्योम dlm_recoverd_resume(काष्ठा dlm_ls *ls)
अणु
	mutex_unlock(&ls->ls_recoverd_active);
पूर्ण

