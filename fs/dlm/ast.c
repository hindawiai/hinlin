<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2010 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#समावेश "dlm_internal.h"
#समावेश "lock.h"
#समावेश "user.h"
#समावेश "ast.h"

अटल uपूर्णांक64_t dlm_cb_seq;
अटल DEFINE_SPINLOCK(dlm_cb_seq_spin);

अटल व्योम dlm_dump_lkb_callbacks(काष्ठा dlm_lkb *lkb)
अणु
	पूर्णांक i;

	log_prपूर्णांक("last_bast %x %llu flags %x mode %d sb %d %x",
		  lkb->lkb_id,
		  (अचिन्हित दीर्घ दीर्घ)lkb->lkb_last_bast.seq,
		  lkb->lkb_last_bast.flags,
		  lkb->lkb_last_bast.mode,
		  lkb->lkb_last_bast.sb_status,
		  lkb->lkb_last_bast.sb_flags);

	log_prपूर्णांक("last_cast %x %llu flags %x mode %d sb %d %x",
		  lkb->lkb_id,
		  (अचिन्हित दीर्घ दीर्घ)lkb->lkb_last_cast.seq,
		  lkb->lkb_last_cast.flags,
		  lkb->lkb_last_cast.mode,
		  lkb->lkb_last_cast.sb_status,
		  lkb->lkb_last_cast.sb_flags);

	क्रम (i = 0; i < DLM_CALLBACKS_SIZE; i++) अणु
		log_prपूर्णांक("cb %x %llu flags %x mode %d sb %d %x",
			  lkb->lkb_id,
			  (अचिन्हित दीर्घ दीर्घ)lkb->lkb_callbacks[i].seq,
			  lkb->lkb_callbacks[i].flags,
			  lkb->lkb_callbacks[i].mode,
			  lkb->lkb_callbacks[i].sb_status,
			  lkb->lkb_callbacks[i].sb_flags);
	पूर्ण
पूर्ण

पूर्णांक dlm_add_lkb_callback(काष्ठा dlm_lkb *lkb, uपूर्णांक32_t flags, पूर्णांक mode,
			 पूर्णांक status, uपूर्णांक32_t sbflags, uपूर्णांक64_t seq)
अणु
	काष्ठा dlm_ls *ls = lkb->lkb_resource->res_ls;
	uपूर्णांक64_t prev_seq;
	पूर्णांक prev_mode;
	पूर्णांक i, rv;

	क्रम (i = 0; i < DLM_CALLBACKS_SIZE; i++) अणु
		अगर (lkb->lkb_callbacks[i].seq)
			जारी;

		/*
		 * Suppress some redundant basts here, करो more on removal.
		 * Don't even add a bast अगर the callback just beक्रमe it
		 * is a bast क्रम the same mode or a more restrictive mode.
		 * (the addional > PR check is needed क्रम PR/CW inversion)
		 */

		अगर ((i > 0) && (flags & DLM_CB_BAST) &&
		    (lkb->lkb_callbacks[i-1].flags & DLM_CB_BAST)) अणु

			prev_seq = lkb->lkb_callbacks[i-1].seq;
			prev_mode = lkb->lkb_callbacks[i-1].mode;

			अगर ((prev_mode == mode) ||
			    (prev_mode > mode && prev_mode > DLM_LOCK_PR)) अणु

				log_debug(ls, "skip %x add bast %llu mode %d "
					  "for bast %llu mode %d",
					  lkb->lkb_id,
					  (अचिन्हित दीर्घ दीर्घ)seq,
					  mode,
					  (अचिन्हित दीर्घ दीर्घ)prev_seq,
					  prev_mode);
				rv = 0;
				जाओ out;
			पूर्ण
		पूर्ण

		lkb->lkb_callbacks[i].seq = seq;
		lkb->lkb_callbacks[i].flags = flags;
		lkb->lkb_callbacks[i].mode = mode;
		lkb->lkb_callbacks[i].sb_status = status;
		lkb->lkb_callbacks[i].sb_flags = (sbflags & 0x000000FF);
		rv = 0;
		अवरोध;
	पूर्ण

	अगर (i == DLM_CALLBACKS_SIZE) अणु
		log_error(ls, "no callbacks %x %llu flags %x mode %d sb %d %x",
			  lkb->lkb_id, (अचिन्हित दीर्घ दीर्घ)seq,
			  flags, mode, status, sbflags);
		dlm_dump_lkb_callbacks(lkb);
		rv = -1;
		जाओ out;
	पूर्ण
 out:
	वापस rv;
पूर्ण

पूर्णांक dlm_rem_lkb_callback(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb,
			 काष्ठा dlm_callback *cb, पूर्णांक *resid)
अणु
	पूर्णांक i, rv;

	*resid = 0;

	अगर (!lkb->lkb_callbacks[0].seq) अणु
		rv = -ENOENT;
		जाओ out;
	पूर्ण

	/* oldest undelivered cb is callbacks[0] */

	स_नकल(cb, &lkb->lkb_callbacks[0], माप(काष्ठा dlm_callback));
	स_रखो(&lkb->lkb_callbacks[0], 0, माप(काष्ठा dlm_callback));

	/* shअगरt others करोwn */

	क्रम (i = 1; i < DLM_CALLBACKS_SIZE; i++) अणु
		अगर (!lkb->lkb_callbacks[i].seq)
			अवरोध;
		स_नकल(&lkb->lkb_callbacks[i-1], &lkb->lkb_callbacks[i],
		       माप(काष्ठा dlm_callback));
		स_रखो(&lkb->lkb_callbacks[i], 0, माप(काष्ठा dlm_callback));
		(*resid)++;
	पूर्ण

	/* अगर cb is a bast, it should be skipped अगर the blocking mode is
	   compatible with the last granted mode */

	अगर ((cb->flags & DLM_CB_BAST) && lkb->lkb_last_cast.seq) अणु
		अगर (dlm_modes_compat(cb->mode, lkb->lkb_last_cast.mode)) अणु
			cb->flags |= DLM_CB_SKIP;

			log_debug(ls, "skip %x bast %llu mode %d "
				  "for cast %llu mode %d",
				  lkb->lkb_id,
				  (अचिन्हित दीर्घ दीर्घ)cb->seq,
				  cb->mode,
				  (अचिन्हित दीर्घ दीर्घ)lkb->lkb_last_cast.seq,
				  lkb->lkb_last_cast.mode);
			rv = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (cb->flags & DLM_CB_CAST) अणु
		स_नकल(&lkb->lkb_last_cast, cb, माप(काष्ठा dlm_callback));
		lkb->lkb_last_cast_समय = kसमय_get();
	पूर्ण

	अगर (cb->flags & DLM_CB_BAST) अणु
		स_नकल(&lkb->lkb_last_bast, cb, माप(काष्ठा dlm_callback));
		lkb->lkb_last_bast_समय = kसमय_get();
	पूर्ण
	rv = 0;
 out:
	वापस rv;
पूर्ण

व्योम dlm_add_cb(काष्ठा dlm_lkb *lkb, uपूर्णांक32_t flags, पूर्णांक mode, पूर्णांक status,
		uपूर्णांक32_t sbflags)
अणु
	काष्ठा dlm_ls *ls = lkb->lkb_resource->res_ls;
	uपूर्णांक64_t new_seq, prev_seq;
	पूर्णांक rv;

	spin_lock(&dlm_cb_seq_spin);
	new_seq = ++dlm_cb_seq;
	अगर (!dlm_cb_seq)
		new_seq = ++dlm_cb_seq;
	spin_unlock(&dlm_cb_seq_spin);

	अगर (lkb->lkb_flags & DLM_IFL_USER) अणु
		dlm_user_add_ast(lkb, flags, mode, status, sbflags, new_seq);
		वापस;
	पूर्ण

	mutex_lock(&lkb->lkb_cb_mutex);
	prev_seq = lkb->lkb_callbacks[0].seq;

	rv = dlm_add_lkb_callback(lkb, flags, mode, status, sbflags, new_seq);
	अगर (rv < 0)
		जाओ out;

	अगर (!prev_seq) अणु
		kref_get(&lkb->lkb_ref);

		अगर (test_bit(LSFL_CB_DELAY, &ls->ls_flags)) अणु
			mutex_lock(&ls->ls_cb_mutex);
			list_add(&lkb->lkb_cb_list, &ls->ls_cb_delay);
			mutex_unlock(&ls->ls_cb_mutex);
		पूर्ण अन्यथा अणु
			queue_work(ls->ls_callback_wq, &lkb->lkb_cb_work);
		पूर्ण
	पूर्ण
 out:
	mutex_unlock(&lkb->lkb_cb_mutex);
पूर्ण

व्योम dlm_callback_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dlm_lkb *lkb = container_of(work, काष्ठा dlm_lkb, lkb_cb_work);
	काष्ठा dlm_ls *ls = lkb->lkb_resource->res_ls;
	व्योम (*castfn) (व्योम *astparam);
	व्योम (*bastfn) (व्योम *astparam, पूर्णांक mode);
	काष्ठा dlm_callback callbacks[DLM_CALLBACKS_SIZE];
	पूर्णांक i, rv, resid;

	स_रखो(&callbacks, 0, माप(callbacks));

	mutex_lock(&lkb->lkb_cb_mutex);
	अगर (!lkb->lkb_callbacks[0].seq) अणु
		/* no callback work exists, shouldn't happen */
		log_error(ls, "dlm_callback_work %x no work", lkb->lkb_id);
		dlm_prपूर्णांक_lkb(lkb);
		dlm_dump_lkb_callbacks(lkb);
	पूर्ण

	क्रम (i = 0; i < DLM_CALLBACKS_SIZE; i++) अणु
		rv = dlm_rem_lkb_callback(ls, lkb, &callbacks[i], &resid);
		अगर (rv < 0)
			अवरोध;
	पूर्ण

	अगर (resid) अणु
		/* cbs reमुख्य, loop should have हटाओd all, shouldn't happen */
		log_error(ls, "dlm_callback_work %x resid %d", lkb->lkb_id,
			  resid);
		dlm_prपूर्णांक_lkb(lkb);
		dlm_dump_lkb_callbacks(lkb);
	पूर्ण
	mutex_unlock(&lkb->lkb_cb_mutex);

	castfn = lkb->lkb_astfn;
	bastfn = lkb->lkb_bastfn;

	क्रम (i = 0; i < DLM_CALLBACKS_SIZE; i++) अणु
		अगर (!callbacks[i].seq)
			अवरोध;
		अगर (callbacks[i].flags & DLM_CB_SKIP) अणु
			जारी;
		पूर्ण अन्यथा अगर (callbacks[i].flags & DLM_CB_BAST) अणु
			bastfn(lkb->lkb_astparam, callbacks[i].mode);
		पूर्ण अन्यथा अगर (callbacks[i].flags & DLM_CB_CAST) अणु
			lkb->lkb_lksb->sb_status = callbacks[i].sb_status;
			lkb->lkb_lksb->sb_flags = callbacks[i].sb_flags;
			castfn(lkb->lkb_astparam);
		पूर्ण
	पूर्ण

	/* unकरो kref_get from dlm_add_callback, may cause lkb to be मुक्तd */
	dlm_put_lkb(lkb);
पूर्ण

पूर्णांक dlm_callback_start(काष्ठा dlm_ls *ls)
अणु
	ls->ls_callback_wq = alloc_workqueue("dlm_callback",
					     WQ_HIGHPRI | WQ_MEM_RECLAIM, 0);
	अगर (!ls->ls_callback_wq) अणु
		log_prपूर्णांक("can't start dlm_callback workqueue");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम dlm_callback_stop(काष्ठा dlm_ls *ls)
अणु
	अगर (ls->ls_callback_wq)
		destroy_workqueue(ls->ls_callback_wq);
पूर्ण

व्योम dlm_callback_suspend(काष्ठा dlm_ls *ls)
अणु
	set_bit(LSFL_CB_DELAY, &ls->ls_flags);

	अगर (ls->ls_callback_wq)
		flush_workqueue(ls->ls_callback_wq);
पूर्ण

#घोषणा MAX_CB_QUEUE 25

व्योम dlm_callback_resume(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_lkb *lkb, *safe;
	पूर्णांक count = 0;

	clear_bit(LSFL_CB_DELAY, &ls->ls_flags);

	अगर (!ls->ls_callback_wq)
		वापस;

more:
	mutex_lock(&ls->ls_cb_mutex);
	list_क्रम_each_entry_safe(lkb, safe, &ls->ls_cb_delay, lkb_cb_list) अणु
		list_del_init(&lkb->lkb_cb_list);
		queue_work(ls->ls_callback_wq, &lkb->lkb_cb_work);
		count++;
		अगर (count == MAX_CB_QUEUE)
			अवरोध;
	पूर्ण
	mutex_unlock(&ls->ls_cb_mutex);

	अगर (count)
		log_rinfo(ls, "dlm_callback_resume %d", count);
	अगर (count == MAX_CB_QUEUE) अणु
		count = 0;
		cond_resched();
		जाओ more;
	पूर्ण
पूर्ण

