<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) 2005-2007 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#समावेश "dlm_internal.h"
#समावेश "member.h"
#समावेश "lock.h"
#समावेश "dir.h"
#समावेश "config.h"
#समावेश "requestqueue.h"

काष्ठा rq_entry अणु
	काष्ठा list_head list;
	uपूर्णांक32_t recover_seq;
	पूर्णांक nodeid;
	काष्ठा dlm_message request;
पूर्ण;

/*
 * Requests received जबतक the lockspace is in recovery get added to the
 * request queue and processed when recovery is complete.  This happens when
 * the lockspace is suspended on some nodes beक्रमe it is on others, or the
 * lockspace is enabled on some जबतक still suspended on others.
 */

व्योम dlm_add_requestqueue(काष्ठा dlm_ls *ls, पूर्णांक nodeid, काष्ठा dlm_message *ms)
अणु
	काष्ठा rq_entry *e;
	पूर्णांक length = ms->m_header.h_length - माप(काष्ठा dlm_message);

	e = kदो_स्मृति(माप(काष्ठा rq_entry) + length, GFP_NOFS);
	अगर (!e) अणु
		log_prपूर्णांक("dlm_add_requestqueue: out of memory len %d", length);
		वापस;
	पूर्ण

	e->recover_seq = ls->ls_recover_seq & 0xFFFFFFFF;
	e->nodeid = nodeid;
	स_नकल(&e->request, ms, ms->m_header.h_length);

	mutex_lock(&ls->ls_requestqueue_mutex);
	list_add_tail(&e->list, &ls->ls_requestqueue);
	mutex_unlock(&ls->ls_requestqueue_mutex);
पूर्ण

/*
 * Called by dlm_recoverd to process normal messages saved जबतक recovery was
 * happening.  Normal locking has been enabled beक्रमe this is called.  dlm_recv
 * upon receiving a message, will रुको क्रम all saved messages to be drained
 * here beक्रमe processing the message it got.  If a new dlm_ls_stop() arrives
 * जबतक we're processing these saved messages, it may block trying to suspend
 * dlm_recv अगर dlm_recv is रुकोing क्रम us in dlm_रुको_requestqueue.  In that
 * हाल, we करोn't पात since locking_stopped is still 0.  If dlm_recv is not
 * रुकोing क्रम us, then this processing may be पातed due to locking_stopped.
 */

पूर्णांक dlm_process_requestqueue(काष्ठा dlm_ls *ls)
अणु
	काष्ठा rq_entry *e;
	काष्ठा dlm_message *ms;
	पूर्णांक error = 0;

	mutex_lock(&ls->ls_requestqueue_mutex);

	क्रम (;;) अणु
		अगर (list_empty(&ls->ls_requestqueue)) अणु
			mutex_unlock(&ls->ls_requestqueue_mutex);
			error = 0;
			अवरोध;
		पूर्ण
		e = list_entry(ls->ls_requestqueue.next, काष्ठा rq_entry, list);
		mutex_unlock(&ls->ls_requestqueue_mutex);

		ms = &e->request;

		log_limit(ls, "dlm_process_requestqueue msg %d from %d "
			  "lkid %x remid %x result %d seq %u",
			  ms->m_type, ms->m_header.h_nodeid,
			  ms->m_lkid, ms->m_remid, ms->m_result,
			  e->recover_seq);

		dlm_receive_message_saved(ls, &e->request, e->recover_seq);

		mutex_lock(&ls->ls_requestqueue_mutex);
		list_del(&e->list);
		kमुक्त(e);

		अगर (dlm_locking_stopped(ls)) अणु
			log_debug(ls, "process_requestqueue abort running");
			mutex_unlock(&ls->ls_requestqueue_mutex);
			error = -EINTR;
			अवरोध;
		पूर्ण
		schedule();
	पूर्ण

	वापस error;
पूर्ण

/*
 * After recovery is करोne, locking is resumed and dlm_recoverd takes all the
 * saved requests and processes them as they would have been by dlm_recv.  At
 * the same समय, dlm_recv will start receiving new requests from remote nodes.
 * We want to delay dlm_recv processing new requests until dlm_recoverd has
 * finished processing the old saved requests.  We करोn't check क्रम locking
 * stopped here because dlm_ls_stop won't stop locking until it's suspended us
 * (dlm_recv).
 */

व्योम dlm_रुको_requestqueue(काष्ठा dlm_ls *ls)
अणु
	क्रम (;;) अणु
		mutex_lock(&ls->ls_requestqueue_mutex);
		अगर (list_empty(&ls->ls_requestqueue))
			अवरोध;
		mutex_unlock(&ls->ls_requestqueue_mutex);
		schedule();
	पूर्ण
	mutex_unlock(&ls->ls_requestqueue_mutex);
पूर्ण

अटल पूर्णांक purge_request(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms, पूर्णांक nodeid)
अणु
	uपूर्णांक32_t type = ms->m_type;

	/* the ls is being cleaned up and मुक्तd by release_lockspace */
	अगर (!ls->ls_count)
		वापस 1;

	अगर (dlm_is_हटाओd(ls, nodeid))
		वापस 1;

	/* directory operations are always purged because the directory is
	   always rebuilt during recovery and the lookups resent */

	अगर (type == DLM_MSG_REMOVE ||
	    type == DLM_MSG_LOOKUP ||
	    type == DLM_MSG_LOOKUP_REPLY)
		वापस 1;

	अगर (!dlm_no_directory(ls))
		वापस 0;

	वापस 1;
पूर्ण

व्योम dlm_purge_requestqueue(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_message *ms;
	काष्ठा rq_entry *e, *safe;

	mutex_lock(&ls->ls_requestqueue_mutex);
	list_क्रम_each_entry_safe(e, safe, &ls->ls_requestqueue, list) अणु
		ms =  &e->request;

		अगर (purge_request(ls, ms, e->nodeid)) अणु
			list_del(&e->list);
			kमुक्त(e);
		पूर्ण
	पूर्ण
	mutex_unlock(&ls->ls_requestqueue_mutex);
पूर्ण

