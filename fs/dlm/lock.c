<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) 2005-2010 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

/* Central locking logic has four stages:

   dlm_lock()
   dlm_unlock()

   request_lock(ls, lkb)
   convert_lock(ls, lkb)
   unlock_lock(ls, lkb)
   cancel_lock(ls, lkb)

   _request_lock(r, lkb)
   _convert_lock(r, lkb)
   _unlock_lock(r, lkb)
   _cancel_lock(r, lkb)

   करो_request(r, lkb)
   करो_convert(r, lkb)
   करो_unlock(r, lkb)
   करो_cancel(r, lkb)

   Stage 1 (lock, unlock) is मुख्यly about checking input args and
   splitting पूर्णांकo one of the four मुख्य operations:

       dlm_lock          = request_lock
       dlm_lock+CONVERT  = convert_lock
       dlm_unlock        = unlock_lock
       dlm_unlock+CANCEL = cancel_lock

   Stage 2, xxxx_lock(), just finds and locks the relevant rsb which is
   provided to the next stage.

   Stage 3, _xxxx_lock(), determines अगर the operation is local or remote.
   When remote, it calls send_xxxx(), when local it calls करो_xxxx().

   Stage 4, करो_xxxx(), is the guts of the operation.  It manipulates the
   given rsb and lkb and queues callbacks.

   For remote operations, send_xxxx() results in the corresponding करो_xxxx()
   function being executed on the remote node.  The connecting send/receive
   calls on local (L) and remote (R) nodes:

   L: send_xxxx()              ->  R: receive_xxxx()
                                   R: करो_xxxx()
   L: receive_xxxx_reply()     <-  R: send_xxxx_reply()
*/
#समावेश <linux/types.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/slab.h>
#समावेश "dlm_internal.h"
#समावेश <linux/dlm_device.h>
#समावेश "memory.h"
#समावेश "lowcomms.h"
#समावेश "requestqueue.h"
#समावेश "util.h"
#समावेश "dir.h"
#समावेश "member.h"
#समावेश "lockspace.h"
#समावेश "ast.h"
#समावेश "lock.h"
#समावेश "rcom.h"
#समावेश "recover.h"
#समावेश "lvb_table.h"
#समावेश "user.h"
#समावेश "config.h"

अटल पूर्णांक send_request(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb);
अटल पूर्णांक send_convert(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb);
अटल पूर्णांक send_unlock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb);
अटल पूर्णांक send_cancel(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb);
अटल पूर्णांक send_grant(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb);
अटल पूर्णांक send_bast(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb, पूर्णांक mode);
अटल पूर्णांक send_lookup(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb);
अटल पूर्णांक send_हटाओ(काष्ठा dlm_rsb *r);
अटल पूर्णांक _request_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb);
अटल पूर्णांक _cancel_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb);
अटल व्योम __receive_convert_reply(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb,
				    काष्ठा dlm_message *ms);
अटल पूर्णांक receive_extralen(काष्ठा dlm_message *ms);
अटल व्योम करो_purge(काष्ठा dlm_ls *ls, पूर्णांक nodeid, पूर्णांक pid);
अटल व्योम del_समयout(काष्ठा dlm_lkb *lkb);
अटल व्योम toss_rsb(काष्ठा kref *kref);

/*
 * Lock compatibilty matrix - thanks Steve
 * UN = Unlocked state. Not really a state, used as a flag
 * PD = Padding. Used to make the matrix a nice घातer of two in size
 * Other states are the same as the VMS DLM.
 * Usage: matrix[grmode+1][rqmode+1]  (although m[rq+1][gr+1] is the same)
 */

अटल स्थिर पूर्णांक __dlm_compat_matrix[8][8] = अणु
      /* UN NL CR CW PR PW EX PD */
        अणु1, 1, 1, 1, 1, 1, 1, 0पूर्ण,       /* UN */
        अणु1, 1, 1, 1, 1, 1, 1, 0पूर्ण,       /* NL */
        अणु1, 1, 1, 1, 1, 1, 0, 0पूर्ण,       /* CR */
        अणु1, 1, 1, 1, 0, 0, 0, 0पूर्ण,       /* CW */
        अणु1, 1, 1, 0, 1, 0, 0, 0पूर्ण,       /* PR */
        अणु1, 1, 1, 0, 0, 0, 0, 0पूर्ण,       /* PW */
        अणु1, 1, 0, 0, 0, 0, 0, 0पूर्ण,       /* EX */
        अणु0, 0, 0, 0, 0, 0, 0, 0पूर्ण        /* PD */
पूर्ण;

/*
 * This defines the direction of transfer of LVB data.
 * Granted mode is the row; requested mode is the column.
 * Usage: matrix[grmode+1][rqmode+1]
 * 1 = LVB is वापसed to the caller
 * 0 = LVB is written to the resource
 * -1 = nothing happens to the LVB
 */

स्थिर पूर्णांक dlm_lvb_operations[8][8] = अणु
        /* UN   NL  CR  CW  PR  PW  EX  PD*/
        अणु  -1,  1,  1,  1,  1,  1,  1, -1 पूर्ण, /* UN */
        अणु  -1,  1,  1,  1,  1,  1,  1,  0 पूर्ण, /* NL */
        अणु  -1, -1,  1,  1,  1,  1,  1,  0 पूर्ण, /* CR */
        अणु  -1, -1, -1,  1,  1,  1,  1,  0 पूर्ण, /* CW */
        अणु  -1, -1, -1, -1,  1,  1,  1,  0 पूर्ण, /* PR */
        अणु  -1,  0,  0,  0,  0,  0,  1,  0 पूर्ण, /* PW */
        अणु  -1,  0,  0,  0,  0,  0,  0,  0 पूर्ण, /* EX */
        अणु  -1,  0,  0,  0,  0,  0,  0,  0 पूर्ण  /* PD */
पूर्ण;

#घोषणा modes_compat(gr, rq) \
	__dlm_compat_matrix[(gr)->lkb_grmode + 1][(rq)->lkb_rqmode + 1]

पूर्णांक dlm_modes_compat(पूर्णांक mode1, पूर्णांक mode2)
अणु
	वापस __dlm_compat_matrix[mode1 + 1][mode2 + 1];
पूर्ण

/*
 * Compatibility matrix क्रम conversions with QUECVT set.
 * Granted mode is the row; requested mode is the column.
 * Usage: matrix[grmode+1][rqmode+1]
 */

अटल स्थिर पूर्णांक __quecvt_compat_matrix[8][8] = अणु
      /* UN NL CR CW PR PW EX PD */
        अणु0, 0, 0, 0, 0, 0, 0, 0पूर्ण,       /* UN */
        अणु0, 0, 1, 1, 1, 1, 1, 0पूर्ण,       /* NL */
        अणु0, 0, 0, 1, 1, 1, 1, 0पूर्ण,       /* CR */
        अणु0, 0, 0, 0, 1, 1, 1, 0पूर्ण,       /* CW */
        अणु0, 0, 0, 1, 0, 1, 1, 0पूर्ण,       /* PR */
        अणु0, 0, 0, 0, 0, 0, 1, 0पूर्ण,       /* PW */
        अणु0, 0, 0, 0, 0, 0, 0, 0पूर्ण,       /* EX */
        अणु0, 0, 0, 0, 0, 0, 0, 0पूर्ण        /* PD */
पूर्ण;

व्योम dlm_prपूर्णांक_lkb(काष्ठा dlm_lkb *lkb)
अणु
	prपूर्णांकk(KERN_ERR "lkb: nodeid %d id %x remid %x exflags %x flags %x "
	       "sts %d rq %d gr %d wait_type %d wait_nodeid %d seq %llu\n",
	       lkb->lkb_nodeid, lkb->lkb_id, lkb->lkb_remid, lkb->lkb_exflags,
	       lkb->lkb_flags, lkb->lkb_status, lkb->lkb_rqmode,
	       lkb->lkb_grmode, lkb->lkb_रुको_type, lkb->lkb_रुको_nodeid,
	       (अचिन्हित दीर्घ दीर्घ)lkb->lkb_recover_seq);
पूर्ण

अटल व्योम dlm_prपूर्णांक_rsb(काष्ठा dlm_rsb *r)
अणु
	prपूर्णांकk(KERN_ERR "rsb: nodeid %d master %d dir %d flags %lx first %x "
	       "rlc %d name %s\n",
	       r->res_nodeid, r->res_master_nodeid, r->res_dir_nodeid,
	       r->res_flags, r->res_first_lkid, r->res_recover_locks_count,
	       r->res_name);
पूर्ण

व्योम dlm_dump_rsb(काष्ठा dlm_rsb *r)
अणु
	काष्ठा dlm_lkb *lkb;

	dlm_prपूर्णांक_rsb(r);

	prपूर्णांकk(KERN_ERR "rsb: root_list empty %d recover_list empty %d\n",
	       list_empty(&r->res_root_list), list_empty(&r->res_recover_list));
	prपूर्णांकk(KERN_ERR "rsb lookup list\n");
	list_क्रम_each_entry(lkb, &r->res_lookup, lkb_rsb_lookup)
		dlm_prपूर्णांक_lkb(lkb);
	prपूर्णांकk(KERN_ERR "rsb grant queue:\n");
	list_क्रम_each_entry(lkb, &r->res_grantqueue, lkb_statequeue)
		dlm_prपूर्णांक_lkb(lkb);
	prपूर्णांकk(KERN_ERR "rsb convert queue:\n");
	list_क्रम_each_entry(lkb, &r->res_convertqueue, lkb_statequeue)
		dlm_prपूर्णांक_lkb(lkb);
	prपूर्णांकk(KERN_ERR "rsb wait queue:\n");
	list_क्रम_each_entry(lkb, &r->res_रुकोqueue, lkb_statequeue)
		dlm_prपूर्णांक_lkb(lkb);
पूर्ण

/* Thपढ़ोs cannot use the lockspace जबतक it's being recovered */

अटल अंतरभूत व्योम dlm_lock_recovery(काष्ठा dlm_ls *ls)
अणु
	करोwn_पढ़ो(&ls->ls_in_recovery);
पूर्ण

व्योम dlm_unlock_recovery(काष्ठा dlm_ls *ls)
अणु
	up_पढ़ो(&ls->ls_in_recovery);
पूर्ण

पूर्णांक dlm_lock_recovery_try(काष्ठा dlm_ls *ls)
अणु
	वापस करोwn_पढ़ो_trylock(&ls->ls_in_recovery);
पूर्ण

अटल अंतरभूत पूर्णांक can_be_queued(काष्ठा dlm_lkb *lkb)
अणु
	वापस !(lkb->lkb_exflags & DLM_LKF_NOQUEUE);
पूर्ण

अटल अंतरभूत पूर्णांक क्रमce_blocking_asts(काष्ठा dlm_lkb *lkb)
अणु
	वापस (lkb->lkb_exflags & DLM_LKF_NOQUEUEBAST);
पूर्ण

अटल अंतरभूत पूर्णांक is_demoted(काष्ठा dlm_lkb *lkb)
अणु
	वापस (lkb->lkb_sbflags & DLM_SBF_DEMOTED);
पूर्ण

अटल अंतरभूत पूर्णांक is_alपंचांगode(काष्ठा dlm_lkb *lkb)
अणु
	वापस (lkb->lkb_sbflags & DLM_SBF_ALTMODE);
पूर्ण

अटल अंतरभूत पूर्णांक is_granted(काष्ठा dlm_lkb *lkb)
अणु
	वापस (lkb->lkb_status == DLM_LKSTS_GRANTED);
पूर्ण

अटल अंतरभूत पूर्णांक is_remote(काष्ठा dlm_rsb *r)
अणु
	DLM_ASSERT(r->res_nodeid >= 0, dlm_prपूर्णांक_rsb(r););
	वापस !!r->res_nodeid;
पूर्ण

अटल अंतरभूत पूर्णांक is_process_copy(काष्ठा dlm_lkb *lkb)
अणु
	वापस (lkb->lkb_nodeid && !(lkb->lkb_flags & DLM_IFL_MSTCPY));
पूर्ण

अटल अंतरभूत पूर्णांक is_master_copy(काष्ठा dlm_lkb *lkb)
अणु
	वापस (lkb->lkb_flags & DLM_IFL_MSTCPY) ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक middle_conversion(काष्ठा dlm_lkb *lkb)
अणु
	अगर ((lkb->lkb_grmode==DLM_LOCK_PR && lkb->lkb_rqmode==DLM_LOCK_CW) ||
	    (lkb->lkb_rqmode==DLM_LOCK_PR && lkb->lkb_grmode==DLM_LOCK_CW))
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक करोwn_conversion(काष्ठा dlm_lkb *lkb)
अणु
	वापस (!middle_conversion(lkb) && lkb->lkb_rqmode < lkb->lkb_grmode);
पूर्ण

अटल अंतरभूत पूर्णांक is_overlap_unlock(काष्ठा dlm_lkb *lkb)
अणु
	वापस lkb->lkb_flags & DLM_IFL_OVERLAP_UNLOCK;
पूर्ण

अटल अंतरभूत पूर्णांक is_overlap_cancel(काष्ठा dlm_lkb *lkb)
अणु
	वापस lkb->lkb_flags & DLM_IFL_OVERLAP_CANCEL;
पूर्ण

अटल अंतरभूत पूर्णांक is_overlap(काष्ठा dlm_lkb *lkb)
अणु
	वापस (lkb->lkb_flags & (DLM_IFL_OVERLAP_UNLOCK |
				  DLM_IFL_OVERLAP_CANCEL));
पूर्ण

अटल व्योम queue_cast(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb, पूर्णांक rv)
अणु
	अगर (is_master_copy(lkb))
		वापस;

	del_समयout(lkb);

	DLM_ASSERT(lkb->lkb_lksb, dlm_prपूर्णांक_lkb(lkb););

	/* अगर the operation was a cancel, then वापस -DLM_ECANCEL, अगर a
	   समयout caused the cancel then वापस -ETIMEDOUT */
	अगर (rv == -DLM_ECANCEL && (lkb->lkb_flags & DLM_IFL_TIMEOUT_CANCEL)) अणु
		lkb->lkb_flags &= ~DLM_IFL_TIMEOUT_CANCEL;
		rv = -ETIMEDOUT;
	पूर्ण

	अगर (rv == -DLM_ECANCEL && (lkb->lkb_flags & DLM_IFL_DEADLOCK_CANCEL)) अणु
		lkb->lkb_flags &= ~DLM_IFL_DEADLOCK_CANCEL;
		rv = -EDEADLK;
	पूर्ण

	dlm_add_cb(lkb, DLM_CB_CAST, lkb->lkb_grmode, rv, lkb->lkb_sbflags);
पूर्ण

अटल अंतरभूत व्योम queue_cast_overlap(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	queue_cast(r, lkb,
		   is_overlap_unlock(lkb) ? -DLM_EUNLOCK : -DLM_ECANCEL);
पूर्ण

अटल व्योम queue_bast(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb, पूर्णांक rqmode)
अणु
	अगर (is_master_copy(lkb)) अणु
		send_bast(r, lkb, rqmode);
	पूर्ण अन्यथा अणु
		dlm_add_cb(lkb, DLM_CB_BAST, rqmode, 0, 0);
	पूर्ण
पूर्ण

/*
 * Basic operations on rsb's and lkb's
 */

/* This is only called to add a reference when the code alपढ़ोy holds
   a valid reference to the rsb, so there's no need क्रम locking. */

अटल अंतरभूत व्योम hold_rsb(काष्ठा dlm_rsb *r)
अणु
	kref_get(&r->res_ref);
पूर्ण

व्योम dlm_hold_rsb(काष्ठा dlm_rsb *r)
अणु
	hold_rsb(r);
पूर्ण

/* When all references to the rsb are gone it's transferred to
   the tossed list क्रम later disposal. */

अटल व्योम put_rsb(काष्ठा dlm_rsb *r)
अणु
	काष्ठा dlm_ls *ls = r->res_ls;
	uपूर्णांक32_t bucket = r->res_bucket;

	spin_lock(&ls->ls_rsbtbl[bucket].lock);
	kref_put(&r->res_ref, toss_rsb);
	spin_unlock(&ls->ls_rsbtbl[bucket].lock);
पूर्ण

व्योम dlm_put_rsb(काष्ठा dlm_rsb *r)
अणु
	put_rsb(r);
पूर्ण

अटल पूर्णांक pre_rsb_काष्ठा(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_rsb *r1, *r2;
	पूर्णांक count = 0;

	spin_lock(&ls->ls_new_rsb_spin);
	अगर (ls->ls_new_rsb_count > dlm_config.ci_new_rsb_count / 2) अणु
		spin_unlock(&ls->ls_new_rsb_spin);
		वापस 0;
	पूर्ण
	spin_unlock(&ls->ls_new_rsb_spin);

	r1 = dlm_allocate_rsb(ls);
	r2 = dlm_allocate_rsb(ls);

	spin_lock(&ls->ls_new_rsb_spin);
	अगर (r1) अणु
		list_add(&r1->res_hashchain, &ls->ls_new_rsb);
		ls->ls_new_rsb_count++;
	पूर्ण
	अगर (r2) अणु
		list_add(&r2->res_hashchain, &ls->ls_new_rsb);
		ls->ls_new_rsb_count++;
	पूर्ण
	count = ls->ls_new_rsb_count;
	spin_unlock(&ls->ls_new_rsb_spin);

	अगर (!count)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/* If ls->ls_new_rsb is empty, वापस -EAGAIN, so the caller can
   unlock any spinlocks, go back and call pre_rsb_काष्ठा again.
   Otherwise, take an rsb off the list and वापस it. */

अटल पूर्णांक get_rsb_काष्ठा(काष्ठा dlm_ls *ls, अक्षर *name, पूर्णांक len,
			  काष्ठा dlm_rsb **r_ret)
अणु
	काष्ठा dlm_rsb *r;
	पूर्णांक count;

	spin_lock(&ls->ls_new_rsb_spin);
	अगर (list_empty(&ls->ls_new_rsb)) अणु
		count = ls->ls_new_rsb_count;
		spin_unlock(&ls->ls_new_rsb_spin);
		log_debug(ls, "find_rsb retry %d %d %s",
			  count, dlm_config.ci_new_rsb_count, name);
		वापस -EAGAIN;
	पूर्ण

	r = list_first_entry(&ls->ls_new_rsb, काष्ठा dlm_rsb, res_hashchain);
	list_del(&r->res_hashchain);
	/* Convert the empty list_head to a शून्य rb_node क्रम tree usage: */
	स_रखो(&r->res_hashnode, 0, माप(काष्ठा rb_node));
	ls->ls_new_rsb_count--;
	spin_unlock(&ls->ls_new_rsb_spin);

	r->res_ls = ls;
	r->res_length = len;
	स_नकल(r->res_name, name, len);
	mutex_init(&r->res_mutex);

	INIT_LIST_HEAD(&r->res_lookup);
	INIT_LIST_HEAD(&r->res_grantqueue);
	INIT_LIST_HEAD(&r->res_convertqueue);
	INIT_LIST_HEAD(&r->res_रुकोqueue);
	INIT_LIST_HEAD(&r->res_root_list);
	INIT_LIST_HEAD(&r->res_recover_list);

	*r_ret = r;
	वापस 0;
पूर्ण

अटल पूर्णांक rsb_cmp(काष्ठा dlm_rsb *r, स्थिर अक्षर *name, पूर्णांक nlen)
अणु
	अक्षर maxname[DLM_RESNAME_MAXLEN];

	स_रखो(maxname, 0, DLM_RESNAME_MAXLEN);
	स_नकल(maxname, name, nlen);
	वापस स_भेद(r->res_name, maxname, DLM_RESNAME_MAXLEN);
पूर्ण

पूर्णांक dlm_search_rsb_tree(काष्ठा rb_root *tree, अक्षर *name, पूर्णांक len,
			काष्ठा dlm_rsb **r_ret)
अणु
	काष्ठा rb_node *node = tree->rb_node;
	काष्ठा dlm_rsb *r;
	पूर्णांक rc;

	जबतक (node) अणु
		r = rb_entry(node, काष्ठा dlm_rsb, res_hashnode);
		rc = rsb_cmp(r, name, len);
		अगर (rc < 0)
			node = node->rb_left;
		अन्यथा अगर (rc > 0)
			node = node->rb_right;
		अन्यथा
			जाओ found;
	पूर्ण
	*r_ret = शून्य;
	वापस -EBADR;

 found:
	*r_ret = r;
	वापस 0;
पूर्ण

अटल पूर्णांक rsb_insert(काष्ठा dlm_rsb *rsb, काष्ठा rb_root *tree)
अणु
	काष्ठा rb_node **newn = &tree->rb_node;
	काष्ठा rb_node *parent = शून्य;
	पूर्णांक rc;

	जबतक (*newn) अणु
		काष्ठा dlm_rsb *cur = rb_entry(*newn, काष्ठा dlm_rsb,
					       res_hashnode);

		parent = *newn;
		rc = rsb_cmp(cur, rsb->res_name, rsb->res_length);
		अगर (rc < 0)
			newn = &parent->rb_left;
		अन्यथा अगर (rc > 0)
			newn = &parent->rb_right;
		अन्यथा अणु
			log_prपूर्णांक("rsb_insert match");
			dlm_dump_rsb(rsb);
			dlm_dump_rsb(cur);
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	rb_link_node(&rsb->res_hashnode, parent, newn);
	rb_insert_color(&rsb->res_hashnode, tree);
	वापस 0;
पूर्ण

/*
 * Find rsb in rsbtbl and potentially create/add one
 *
 * Delaying the release of rsb's has a similar benefit to applications keeping
 * NL locks on an rsb, but without the guarantee that the cached master value
 * will still be valid when the rsb is reused.  Apps aren't always smart enough
 * to keep NL locks on an rsb that they may lock again लघुly; this can lead
 * to excessive master lookups and removals अगर we करोn't delay the release.
 *
 * Searching क्रम an rsb means looking through both the normal list and toss
 * list.  When found on the toss list the rsb is moved to the normal list with
 * ref count of 1; when found on normal list the ref count is incremented.
 *
 * rsb's on the keep list are being used locally and refcounted.
 * rsb's on the toss list are not being used locally, and are not refcounted.
 *
 * The toss list rsb's were either
 * - previously used locally but not any more (were on keep list, then
 *   moved to toss list when last refcount dropped)
 * - created and put on toss list as a directory record क्रम a lookup
 *   (we are the dir node क्रम the res, but are not using the res right now,
 *   but some other node is)
 *
 * The purpose of find_rsb() is to वापस a refcounted rsb क्रम local use.
 * So, अगर the given rsb is on the toss list, it is moved to the keep list
 * beक्रमe being वापसed.
 *
 * toss_rsb() happens when all local usage of the rsb is करोne, i.e. no
 * more refcounts exist, so the rsb is moved from the keep list to the
 * toss list.
 *
 * rsb's on both keep and toss lists are used क्रम करोing a name to master
 * lookups.  rsb's that are in use locally (and being refcounted) are on
 * the keep list, rsb's that are not in use locally (not refcounted) and
 * only exist क्रम name/master lookups are on the toss list.
 *
 * rsb's on the toss list who's dir_nodeid is not local can have stale
 * name/master mappings.  So, remote requests on such rsb's can potentially
 * वापस with an error, which means the mapping is stale and needs to
 * be updated with a new lookup.  (The idea behind MASTER UNCERTAIN and
 * first_lkid is to keep only a single outstanding request on an rsb
 * जबतक that rsb has a potentially stale master.)
 */

अटल पूर्णांक find_rsb_dir(काष्ठा dlm_ls *ls, अक्षर *name, पूर्णांक len,
			uपूर्णांक32_t hash, uपूर्णांक32_t b,
			पूर्णांक dir_nodeid, पूर्णांक from_nodeid,
			अचिन्हित पूर्णांक flags, काष्ठा dlm_rsb **r_ret)
अणु
	काष्ठा dlm_rsb *r = शून्य;
	पूर्णांक our_nodeid = dlm_our_nodeid();
	पूर्णांक from_local = 0;
	पूर्णांक from_other = 0;
	पूर्णांक from_dir = 0;
	पूर्णांक create = 0;
	पूर्णांक error;

	अगर (flags & R_RECEIVE_REQUEST) अणु
		अगर (from_nodeid == dir_nodeid)
			from_dir = 1;
		अन्यथा
			from_other = 1;
	पूर्ण अन्यथा अगर (flags & R_REQUEST) अणु
		from_local = 1;
	पूर्ण

	/*
	 * flags & R_RECEIVE_RECOVER is from dlm_recover_master_copy, so
	 * from_nodeid has sent us a lock in dlm_recover_locks, believing
	 * we're the new master.  Our local recovery may not have set
	 * res_master_nodeid to our_nodeid yet, so allow either.  Don't
	 * create the rsb; dlm_recover_process_copy() will handle EBADR
	 * by resending.
	 *
	 * If someone sends us a request, we are the dir node, and we करो
	 * not find the rsb anywhere, then recreate it.  This happens अगर
	 * someone sends us a request after we have हटाओd/मुक्तd an rsb
	 * from our toss list.  (They sent a request instead of lookup
	 * because they are using an rsb from their toss list.)
	 */

	अगर (from_local || from_dir ||
	    (from_other && (dir_nodeid == our_nodeid))) अणु
		create = 1;
	पूर्ण

 retry:
	अगर (create) अणु
		error = pre_rsb_काष्ठा(ls);
		अगर (error < 0)
			जाओ out;
	पूर्ण

	spin_lock(&ls->ls_rsbtbl[b].lock);

	error = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].keep, name, len, &r);
	अगर (error)
		जाओ करो_toss;
	
	/*
	 * rsb is active, so we can't check master_nodeid without lock_rsb.
	 */

	kref_get(&r->res_ref);
	error = 0;
	जाओ out_unlock;


 करो_toss:
	error = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].toss, name, len, &r);
	अगर (error)
		जाओ करो_new;

	/*
	 * rsb found inactive (master_nodeid may be out of date unless
	 * we are the dir_nodeid or were the master)  No other thपढ़ो
	 * is using this rsb because it's on the toss list, so we can
	 * look at or update res_master_nodeid without lock_rsb.
	 */

	अगर ((r->res_master_nodeid != our_nodeid) && from_other) अणु
		/* our rsb was not master, and another node (not the dir node)
		   has sent us a request */
		log_debug(ls, "find_rsb toss from_other %d master %d dir %d %s",
			  from_nodeid, r->res_master_nodeid, dir_nodeid,
			  r->res_name);
		error = -ENOTBLK;
		जाओ out_unlock;
	पूर्ण

	अगर ((r->res_master_nodeid != our_nodeid) && from_dir) अणु
		/* करोn't think this should ever happen */
		log_error(ls, "find_rsb toss from_dir %d master %d",
			  from_nodeid, r->res_master_nodeid);
		dlm_prपूर्णांक_rsb(r);
		/* fix it and go on */
		r->res_master_nodeid = our_nodeid;
		r->res_nodeid = 0;
		rsb_clear_flag(r, RSB_MASTER_UNCERTAIN);
		r->res_first_lkid = 0;
	पूर्ण

	अगर (from_local && (r->res_master_nodeid != our_nodeid)) अणु
		/* Because we have held no locks on this rsb,
		   res_master_nodeid could have become stale. */
		rsb_set_flag(r, RSB_MASTER_UNCERTAIN);
		r->res_first_lkid = 0;
	पूर्ण

	rb_erase(&r->res_hashnode, &ls->ls_rsbtbl[b].toss);
	error = rsb_insert(r, &ls->ls_rsbtbl[b].keep);
	जाओ out_unlock;


 करो_new:
	/*
	 * rsb not found
	 */

	अगर (error == -EBADR && !create)
		जाओ out_unlock;

	error = get_rsb_काष्ठा(ls, name, len, &r);
	अगर (error == -EAGAIN) अणु
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		जाओ retry;
	पूर्ण
	अगर (error)
		जाओ out_unlock;

	r->res_hash = hash;
	r->res_bucket = b;
	r->res_dir_nodeid = dir_nodeid;
	kref_init(&r->res_ref);

	अगर (from_dir) अणु
		/* want to see how often this happens */
		log_debug(ls, "find_rsb new from_dir %d recreate %s",
			  from_nodeid, r->res_name);
		r->res_master_nodeid = our_nodeid;
		r->res_nodeid = 0;
		जाओ out_add;
	पूर्ण

	अगर (from_other && (dir_nodeid != our_nodeid)) अणु
		/* should never happen */
		log_error(ls, "find_rsb new from_other %d dir %d our %d %s",
			  from_nodeid, dir_nodeid, our_nodeid, r->res_name);
		dlm_मुक्त_rsb(r);
		r = शून्य;
		error = -ENOTBLK;
		जाओ out_unlock;
	पूर्ण

	अगर (from_other) अणु
		log_debug(ls, "find_rsb new from_other %d dir %d %s",
			  from_nodeid, dir_nodeid, r->res_name);
	पूर्ण

	अगर (dir_nodeid == our_nodeid) अणु
		/* When we are the dir nodeid, we can set the master
		   node immediately */
		r->res_master_nodeid = our_nodeid;
		r->res_nodeid = 0;
	पूर्ण अन्यथा अणु
		/* set_master will send_lookup to dir_nodeid */
		r->res_master_nodeid = 0;
		r->res_nodeid = -1;
	पूर्ण

 out_add:
	error = rsb_insert(r, &ls->ls_rsbtbl[b].keep);
 out_unlock:
	spin_unlock(&ls->ls_rsbtbl[b].lock);
 out:
	*r_ret = r;
	वापस error;
पूर्ण

/* During recovery, other nodes can send us new MSTCPY locks (from
   dlm_recover_locks) beक्रमe we've made ourself master (in
   dlm_recover_masters). */

अटल पूर्णांक find_rsb_nodir(काष्ठा dlm_ls *ls, अक्षर *name, पूर्णांक len,
			  uपूर्णांक32_t hash, uपूर्णांक32_t b,
			  पूर्णांक dir_nodeid, पूर्णांक from_nodeid,
			  अचिन्हित पूर्णांक flags, काष्ठा dlm_rsb **r_ret)
अणु
	काष्ठा dlm_rsb *r = शून्य;
	पूर्णांक our_nodeid = dlm_our_nodeid();
	पूर्णांक recover = (flags & R_RECEIVE_RECOVER);
	पूर्णांक error;

 retry:
	error = pre_rsb_काष्ठा(ls);
	अगर (error < 0)
		जाओ out;

	spin_lock(&ls->ls_rsbtbl[b].lock);

	error = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].keep, name, len, &r);
	अगर (error)
		जाओ करो_toss;

	/*
	 * rsb is active, so we can't check master_nodeid without lock_rsb.
	 */

	kref_get(&r->res_ref);
	जाओ out_unlock;


 करो_toss:
	error = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].toss, name, len, &r);
	अगर (error)
		जाओ करो_new;

	/*
	 * rsb found inactive. No other thपढ़ो is using this rsb because
	 * it's on the toss list, so we can look at or update
	 * res_master_nodeid without lock_rsb.
	 */

	अगर (!recover && (r->res_master_nodeid != our_nodeid) && from_nodeid) अणु
		/* our rsb is not master, and another node has sent us a
		   request; this should never happen */
		log_error(ls, "find_rsb toss from_nodeid %d master %d dir %d",
			  from_nodeid, r->res_master_nodeid, dir_nodeid);
		dlm_prपूर्णांक_rsb(r);
		error = -ENOTBLK;
		जाओ out_unlock;
	पूर्ण

	अगर (!recover && (r->res_master_nodeid != our_nodeid) &&
	    (dir_nodeid == our_nodeid)) अणु
		/* our rsb is not master, and we are dir; may as well fix it;
		   this should never happen */
		log_error(ls, "find_rsb toss our %d master %d dir %d",
			  our_nodeid, r->res_master_nodeid, dir_nodeid);
		dlm_prपूर्णांक_rsb(r);
		r->res_master_nodeid = our_nodeid;
		r->res_nodeid = 0;
	पूर्ण

	rb_erase(&r->res_hashnode, &ls->ls_rsbtbl[b].toss);
	error = rsb_insert(r, &ls->ls_rsbtbl[b].keep);
	जाओ out_unlock;


 करो_new:
	/*
	 * rsb not found
	 */

	error = get_rsb_काष्ठा(ls, name, len, &r);
	अगर (error == -EAGAIN) अणु
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		जाओ retry;
	पूर्ण
	अगर (error)
		जाओ out_unlock;

	r->res_hash = hash;
	r->res_bucket = b;
	r->res_dir_nodeid = dir_nodeid;
	r->res_master_nodeid = dir_nodeid;
	r->res_nodeid = (dir_nodeid == our_nodeid) ? 0 : dir_nodeid;
	kref_init(&r->res_ref);

	error = rsb_insert(r, &ls->ls_rsbtbl[b].keep);
 out_unlock:
	spin_unlock(&ls->ls_rsbtbl[b].lock);
 out:
	*r_ret = r;
	वापस error;
पूर्ण

अटल पूर्णांक find_rsb(काष्ठा dlm_ls *ls, अक्षर *name, पूर्णांक len, पूर्णांक from_nodeid,
		    अचिन्हित पूर्णांक flags, काष्ठा dlm_rsb **r_ret)
अणु
	uपूर्णांक32_t hash, b;
	पूर्णांक dir_nodeid;

	अगर (len > DLM_RESNAME_MAXLEN)
		वापस -EINVAL;

	hash = jhash(name, len, 0);
	b = hash & (ls->ls_rsbtbl_size - 1);

	dir_nodeid = dlm_hash2nodeid(ls, hash);

	अगर (dlm_no_directory(ls))
		वापस find_rsb_nodir(ls, name, len, hash, b, dir_nodeid,
				      from_nodeid, flags, r_ret);
	अन्यथा
		वापस find_rsb_dir(ls, name, len, hash, b, dir_nodeid,
				      from_nodeid, flags, r_ret);
पूर्ण

/* we have received a request and found that res_master_nodeid != our_nodeid,
   so we need to वापस an error or make ourself the master */

अटल पूर्णांक validate_master_nodeid(काष्ठा dlm_ls *ls, काष्ठा dlm_rsb *r,
				  पूर्णांक from_nodeid)
अणु
	अगर (dlm_no_directory(ls)) अणु
		log_error(ls, "find_rsb keep from_nodeid %d master %d dir %d",
			  from_nodeid, r->res_master_nodeid,
			  r->res_dir_nodeid);
		dlm_prपूर्णांक_rsb(r);
		वापस -ENOTBLK;
	पूर्ण

	अगर (from_nodeid != r->res_dir_nodeid) अणु
		/* our rsb is not master, and another node (not the dir node)
	   	   has sent us a request.  this is much more common when our
	   	   master_nodeid is zero, so limit debug to non-zero.  */

		अगर (r->res_master_nodeid) अणु
			log_debug(ls, "validate master from_other %d master %d "
				  "dir %d first %x %s", from_nodeid,
				  r->res_master_nodeid, r->res_dir_nodeid,
				  r->res_first_lkid, r->res_name);
		पूर्ण
		वापस -ENOTBLK;
	पूर्ण अन्यथा अणु
		/* our rsb is not master, but the dir nodeid has sent us a
	   	   request; this could happen with master 0 / res_nodeid -1 */

		अगर (r->res_master_nodeid) अणु
			log_error(ls, "validate master from_dir %d master %d "
				  "first %x %s",
				  from_nodeid, r->res_master_nodeid,
				  r->res_first_lkid, r->res_name);
		पूर्ण

		r->res_master_nodeid = dlm_our_nodeid();
		r->res_nodeid = 0;
		वापस 0;
	पूर्ण
पूर्ण

/*
 * We're the dir node क्रम this res and another node wants to know the
 * master nodeid.  During normal operation (non recovery) this is only
 * called from receive_lookup(); master lookups when the local node is
 * the dir node are करोne by find_rsb().
 *
 * normal operation, we are the dir node क्रम a resource
 * . _request_lock
 * . set_master
 * . send_lookup
 * . receive_lookup
 * . dlm_master_lookup flags 0
 *
 * recover directory, we are rebuilding dir क्रम all resources
 * . dlm_recover_directory
 * . dlm_rcom_names
 *   remote node sends back the rsb names it is master of and we are dir of
 * . dlm_master_lookup RECOVER_सूची (fix_master 0, from_master 1)
 *   we either create new rsb setting remote node as master, or find existing
 *   rsb and set master to be the remote node.
 *
 * recover masters, we are finding the new master क्रम resources
 * . dlm_recover_masters
 * . recover_master
 * . dlm_send_rcom_lookup
 * . receive_rcom_lookup
 * . dlm_master_lookup RECOVER_MASTER (fix_master 1, from_master 0)
 */

पूर्णांक dlm_master_lookup(काष्ठा dlm_ls *ls, पूर्णांक from_nodeid, अक्षर *name, पूर्णांक len,
		      अचिन्हित पूर्णांक flags, पूर्णांक *r_nodeid, पूर्णांक *result)
अणु
	काष्ठा dlm_rsb *r = शून्य;
	uपूर्णांक32_t hash, b;
	पूर्णांक from_master = (flags & DLM_LU_RECOVER_सूची);
	पूर्णांक fix_master = (flags & DLM_LU_RECOVER_MASTER);
	पूर्णांक our_nodeid = dlm_our_nodeid();
	पूर्णांक dir_nodeid, error, toss_list = 0;

	अगर (len > DLM_RESNAME_MAXLEN)
		वापस -EINVAL;

	अगर (from_nodeid == our_nodeid) अणु
		log_error(ls, "dlm_master_lookup from our_nodeid %d flags %x",
			  our_nodeid, flags);
		वापस -EINVAL;
	पूर्ण

	hash = jhash(name, len, 0);
	b = hash & (ls->ls_rsbtbl_size - 1);

	dir_nodeid = dlm_hash2nodeid(ls, hash);
	अगर (dir_nodeid != our_nodeid) अणु
		log_error(ls, "dlm_master_lookup from %d dir %d our %d h %x %d",
			  from_nodeid, dir_nodeid, our_nodeid, hash,
			  ls->ls_num_nodes);
		*r_nodeid = -1;
		वापस -EINVAL;
	पूर्ण

 retry:
	error = pre_rsb_काष्ठा(ls);
	अगर (error < 0)
		वापस error;

	spin_lock(&ls->ls_rsbtbl[b].lock);
	error = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].keep, name, len, &r);
	अगर (!error) अणु
		/* because the rsb is active, we need to lock_rsb beक्रमe
		   checking/changing re_master_nodeid */

		hold_rsb(r);
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		lock_rsb(r);
		जाओ found;
	पूर्ण

	error = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].toss, name, len, &r);
	अगर (error)
		जाओ not_found;

	/* because the rsb is inactive (on toss list), it's not refcounted
	   and lock_rsb is not used, but is रक्षित by the rsbtbl lock */

	toss_list = 1;
 found:
	अगर (r->res_dir_nodeid != our_nodeid) अणु
		/* should not happen, but may as well fix it and carry on */
		log_error(ls, "dlm_master_lookup res_dir %d our %d %s",
			  r->res_dir_nodeid, our_nodeid, r->res_name);
		r->res_dir_nodeid = our_nodeid;
	पूर्ण

	अगर (fix_master && dlm_is_हटाओd(ls, r->res_master_nodeid)) अणु
		/* Recovery uses this function to set a new master when
		   the previous master failed.  Setting NEW_MASTER will
		   क्रमce dlm_recover_masters to call recover_master on this
		   rsb even though the res_nodeid is no दीर्घer हटाओd. */

		r->res_master_nodeid = from_nodeid;
		r->res_nodeid = from_nodeid;
		rsb_set_flag(r, RSB_NEW_MASTER);

		अगर (toss_list) अणु
			/* I करोn't think we should ever find it on toss list. */
			log_error(ls, "dlm_master_lookup fix_master on toss");
			dlm_dump_rsb(r);
		पूर्ण
	पूर्ण

	अगर (from_master && (r->res_master_nodeid != from_nodeid)) अणु
		/* this will happen अगर from_nodeid became master during
		   a previous recovery cycle, and we पातed the previous
		   cycle beक्रमe recovering this master value */

		log_limit(ls, "dlm_master_lookup from_master %d "
			  "master_nodeid %d res_nodeid %d first %x %s",
			  from_nodeid, r->res_master_nodeid, r->res_nodeid,
			  r->res_first_lkid, r->res_name);

		अगर (r->res_master_nodeid == our_nodeid) अणु
			log_error(ls, "from_master %d our_master", from_nodeid);
			dlm_dump_rsb(r);
			जाओ out_found;
		पूर्ण

		r->res_master_nodeid = from_nodeid;
		r->res_nodeid = from_nodeid;
		rsb_set_flag(r, RSB_NEW_MASTER);
	पूर्ण

	अगर (!r->res_master_nodeid) अणु
		/* this will happen अगर recovery happens जबतक we're looking
		   up the master क्रम this rsb */

		log_debug(ls, "dlm_master_lookup master 0 to %d first %x %s",
			  from_nodeid, r->res_first_lkid, r->res_name);
		r->res_master_nodeid = from_nodeid;
		r->res_nodeid = from_nodeid;
	पूर्ण

	अगर (!from_master && !fix_master &&
	    (r->res_master_nodeid == from_nodeid)) अणु
		/* this can happen when the master sends हटाओ, the dir node
		   finds the rsb on the keep list and ignores the हटाओ,
		   and the क्रमmer master sends a lookup */

		log_limit(ls, "dlm_master_lookup from master %d flags %x "
			  "first %x %s", from_nodeid, flags,
			  r->res_first_lkid, r->res_name);
	पूर्ण

 out_found:
	*r_nodeid = r->res_master_nodeid;
	अगर (result)
		*result = DLM_LU_MATCH;

	अगर (toss_list) अणु
		r->res_toss_समय = jअगरfies;
		/* the rsb was inactive (on toss list) */
		spin_unlock(&ls->ls_rsbtbl[b].lock);
	पूर्ण अन्यथा अणु
		/* the rsb was active */
		unlock_rsb(r);
		put_rsb(r);
	पूर्ण
	वापस 0;

 not_found:
	error = get_rsb_काष्ठा(ls, name, len, &r);
	अगर (error == -EAGAIN) अणु
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		जाओ retry;
	पूर्ण
	अगर (error)
		जाओ out_unlock;

	r->res_hash = hash;
	r->res_bucket = b;
	r->res_dir_nodeid = our_nodeid;
	r->res_master_nodeid = from_nodeid;
	r->res_nodeid = from_nodeid;
	kref_init(&r->res_ref);
	r->res_toss_समय = jअगरfies;

	error = rsb_insert(r, &ls->ls_rsbtbl[b].toss);
	अगर (error) अणु
		/* should never happen */
		dlm_मुक्त_rsb(r);
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		जाओ retry;
	पूर्ण

	अगर (result)
		*result = DLM_LU_ADD;
	*r_nodeid = from_nodeid;
	error = 0;
 out_unlock:
	spin_unlock(&ls->ls_rsbtbl[b].lock);
	वापस error;
पूर्ण

अटल व्योम dlm_dump_rsb_hash(काष्ठा dlm_ls *ls, uपूर्णांक32_t hash)
अणु
	काष्ठा rb_node *n;
	काष्ठा dlm_rsb *r;
	पूर्णांक i;

	क्रम (i = 0; i < ls->ls_rsbtbl_size; i++) अणु
		spin_lock(&ls->ls_rsbtbl[i].lock);
		क्रम (n = rb_first(&ls->ls_rsbtbl[i].keep); n; n = rb_next(n)) अणु
			r = rb_entry(n, काष्ठा dlm_rsb, res_hashnode);
			अगर (r->res_hash == hash)
				dlm_dump_rsb(r);
		पूर्ण
		spin_unlock(&ls->ls_rsbtbl[i].lock);
	पूर्ण
पूर्ण

व्योम dlm_dump_rsb_name(काष्ठा dlm_ls *ls, अक्षर *name, पूर्णांक len)
अणु
	काष्ठा dlm_rsb *r = शून्य;
	uपूर्णांक32_t hash, b;
	पूर्णांक error;

	hash = jhash(name, len, 0);
	b = hash & (ls->ls_rsbtbl_size - 1);

	spin_lock(&ls->ls_rsbtbl[b].lock);
	error = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].keep, name, len, &r);
	अगर (!error)
		जाओ out_dump;

	error = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].toss, name, len, &r);
	अगर (error)
		जाओ out;
 out_dump:
	dlm_dump_rsb(r);
 out:
	spin_unlock(&ls->ls_rsbtbl[b].lock);
पूर्ण

अटल व्योम toss_rsb(काष्ठा kref *kref)
अणु
	काष्ठा dlm_rsb *r = container_of(kref, काष्ठा dlm_rsb, res_ref);
	काष्ठा dlm_ls *ls = r->res_ls;

	DLM_ASSERT(list_empty(&r->res_root_list), dlm_prपूर्णांक_rsb(r););
	kref_init(&r->res_ref);
	rb_erase(&r->res_hashnode, &ls->ls_rsbtbl[r->res_bucket].keep);
	rsb_insert(r, &ls->ls_rsbtbl[r->res_bucket].toss);
	r->res_toss_समय = jअगरfies;
	ls->ls_rsbtbl[r->res_bucket].flags |= DLM_RTF_SHRINK;
	अगर (r->res_lvbptr) अणु
		dlm_मुक्त_lvb(r->res_lvbptr);
		r->res_lvbptr = शून्य;
	पूर्ण
पूर्ण

/* See comment क्रम unhold_lkb */

अटल व्योम unhold_rsb(काष्ठा dlm_rsb *r)
अणु
	पूर्णांक rv;
	rv = kref_put(&r->res_ref, toss_rsb);
	DLM_ASSERT(!rv, dlm_dump_rsb(r););
पूर्ण

अटल व्योम समाप्त_rsb(काष्ठा kref *kref)
अणु
	काष्ठा dlm_rsb *r = container_of(kref, काष्ठा dlm_rsb, res_ref);

	/* All work is करोne after the वापस from kref_put() so we
	   can release the ग_लिखो_lock beक्रमe the हटाओ and मुक्त. */

	DLM_ASSERT(list_empty(&r->res_lookup), dlm_dump_rsb(r););
	DLM_ASSERT(list_empty(&r->res_grantqueue), dlm_dump_rsb(r););
	DLM_ASSERT(list_empty(&r->res_convertqueue), dlm_dump_rsb(r););
	DLM_ASSERT(list_empty(&r->res_रुकोqueue), dlm_dump_rsb(r););
	DLM_ASSERT(list_empty(&r->res_root_list), dlm_dump_rsb(r););
	DLM_ASSERT(list_empty(&r->res_recover_list), dlm_dump_rsb(r););
पूर्ण

/* Attaching/detaching lkb's from rsb's is क्रम rsb reference counting.
   The rsb must exist as दीर्घ as any lkb's क्रम it करो. */

अटल व्योम attach_lkb(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	hold_rsb(r);
	lkb->lkb_resource = r;
पूर्ण

अटल व्योम detach_lkb(काष्ठा dlm_lkb *lkb)
अणु
	अगर (lkb->lkb_resource) अणु
		put_rsb(lkb->lkb_resource);
		lkb->lkb_resource = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक create_lkb(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb **lkb_ret)
अणु
	काष्ठा dlm_lkb *lkb;
	पूर्णांक rv;

	lkb = dlm_allocate_lkb(ls);
	अगर (!lkb)
		वापस -ENOMEM;

	lkb->lkb_nodeid = -1;
	lkb->lkb_grmode = DLM_LOCK_IV;
	kref_init(&lkb->lkb_ref);
	INIT_LIST_HEAD(&lkb->lkb_ownqueue);
	INIT_LIST_HEAD(&lkb->lkb_rsb_lookup);
	INIT_LIST_HEAD(&lkb->lkb_समय_list);
	INIT_LIST_HEAD(&lkb->lkb_cb_list);
	mutex_init(&lkb->lkb_cb_mutex);
	INIT_WORK(&lkb->lkb_cb_work, dlm_callback_work);

	idr_preload(GFP_NOFS);
	spin_lock(&ls->ls_lkbidr_spin);
	rv = idr_alloc(&ls->ls_lkbidr, lkb, 1, 0, GFP_NOWAIT);
	अगर (rv >= 0)
		lkb->lkb_id = rv;
	spin_unlock(&ls->ls_lkbidr_spin);
	idr_preload_end();

	अगर (rv < 0) अणु
		log_error(ls, "create_lkb idr error %d", rv);
		dlm_मुक्त_lkb(lkb);
		वापस rv;
	पूर्ण

	*lkb_ret = lkb;
	वापस 0;
पूर्ण

अटल पूर्णांक find_lkb(काष्ठा dlm_ls *ls, uपूर्णांक32_t lkid, काष्ठा dlm_lkb **lkb_ret)
अणु
	काष्ठा dlm_lkb *lkb;

	spin_lock(&ls->ls_lkbidr_spin);
	lkb = idr_find(&ls->ls_lkbidr, lkid);
	अगर (lkb)
		kref_get(&lkb->lkb_ref);
	spin_unlock(&ls->ls_lkbidr_spin);

	*lkb_ret = lkb;
	वापस lkb ? 0 : -ENOENT;
पूर्ण

अटल व्योम समाप्त_lkb(काष्ठा kref *kref)
अणु
	काष्ठा dlm_lkb *lkb = container_of(kref, काष्ठा dlm_lkb, lkb_ref);

	/* All work is करोne after the वापस from kref_put() so we
	   can release the ग_लिखो_lock beक्रमe the detach_lkb */

	DLM_ASSERT(!lkb->lkb_status, dlm_prपूर्णांक_lkb(lkb););
पूर्ण

/* __put_lkb() is used when an lkb may not have an rsb attached to
   it so we need to provide the lockspace explicitly */

अटल पूर्णांक __put_lkb(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb)
अणु
	uपूर्णांक32_t lkid = lkb->lkb_id;

	spin_lock(&ls->ls_lkbidr_spin);
	अगर (kref_put(&lkb->lkb_ref, समाप्त_lkb)) अणु
		idr_हटाओ(&ls->ls_lkbidr, lkid);
		spin_unlock(&ls->ls_lkbidr_spin);

		detach_lkb(lkb);

		/* क्रम local/process lkbs, lvbptr poपूर्णांकs to caller's lksb */
		अगर (lkb->lkb_lvbptr && is_master_copy(lkb))
			dlm_मुक्त_lvb(lkb->lkb_lvbptr);
		dlm_मुक्त_lkb(lkb);
		वापस 1;
	पूर्ण अन्यथा अणु
		spin_unlock(&ls->ls_lkbidr_spin);
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक dlm_put_lkb(काष्ठा dlm_lkb *lkb)
अणु
	काष्ठा dlm_ls *ls;

	DLM_ASSERT(lkb->lkb_resource, dlm_prपूर्णांक_lkb(lkb););
	DLM_ASSERT(lkb->lkb_resource->res_ls, dlm_prपूर्णांक_lkb(lkb););

	ls = lkb->lkb_resource->res_ls;
	वापस __put_lkb(ls, lkb);
पूर्ण

/* This is only called to add a reference when the code alपढ़ोy holds
   a valid reference to the lkb, so there's no need क्रम locking. */

अटल अंतरभूत व्योम hold_lkb(काष्ठा dlm_lkb *lkb)
अणु
	kref_get(&lkb->lkb_ref);
पूर्ण

/* This is called when we need to हटाओ a reference and are certain
   it's not the last ref.  e.g. del_lkb is always called between a
   find_lkb/put_lkb and is always the inverse of a previous add_lkb.
   put_lkb would work fine, but would involve unnecessary locking */

अटल अंतरभूत व्योम unhold_lkb(काष्ठा dlm_lkb *lkb)
अणु
	पूर्णांक rv;
	rv = kref_put(&lkb->lkb_ref, समाप्त_lkb);
	DLM_ASSERT(!rv, dlm_prपूर्णांक_lkb(lkb););
पूर्ण

अटल व्योम lkb_add_ordered(काष्ठा list_head *new, काष्ठा list_head *head,
			    पूर्णांक mode)
अणु
	काष्ठा dlm_lkb *lkb = शून्य;

	list_क्रम_each_entry(lkb, head, lkb_statequeue)
		अगर (lkb->lkb_rqmode < mode)
			अवरोध;

	__list_add(new, lkb->lkb_statequeue.prev, &lkb->lkb_statequeue);
पूर्ण

/* add/हटाओ lkb to rsb's grant/convert/रुको queue */

अटल व्योम add_lkb(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb, पूर्णांक status)
अणु
	kref_get(&lkb->lkb_ref);

	DLM_ASSERT(!lkb->lkb_status, dlm_prपूर्णांक_lkb(lkb););

	lkb->lkb_बारtamp = kसमय_get();

	lkb->lkb_status = status;

	चयन (status) अणु
	हाल DLM_LKSTS_WAITING:
		अगर (lkb->lkb_exflags & DLM_LKF_HEADQUE)
			list_add(&lkb->lkb_statequeue, &r->res_रुकोqueue);
		अन्यथा
			list_add_tail(&lkb->lkb_statequeue, &r->res_रुकोqueue);
		अवरोध;
	हाल DLM_LKSTS_GRANTED:
		/* convention says granted locks kept in order of grmode */
		lkb_add_ordered(&lkb->lkb_statequeue, &r->res_grantqueue,
				lkb->lkb_grmode);
		अवरोध;
	हाल DLM_LKSTS_CONVERT:
		अगर (lkb->lkb_exflags & DLM_LKF_HEADQUE)
			list_add(&lkb->lkb_statequeue, &r->res_convertqueue);
		अन्यथा
			list_add_tail(&lkb->lkb_statequeue,
				      &r->res_convertqueue);
		अवरोध;
	शेष:
		DLM_ASSERT(0, dlm_prपूर्णांक_lkb(lkb); prपूर्णांकk("sts=%d\n", status););
	पूर्ण
पूर्ण

अटल व्योम del_lkb(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	lkb->lkb_status = 0;
	list_del(&lkb->lkb_statequeue);
	unhold_lkb(lkb);
पूर्ण

अटल व्योम move_lkb(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb, पूर्णांक sts)
अणु
	hold_lkb(lkb);
	del_lkb(r, lkb);
	add_lkb(r, lkb, sts);
	unhold_lkb(lkb);
पूर्ण

अटल पूर्णांक msg_reply_type(पूर्णांक mstype)
अणु
	चयन (mstype) अणु
	हाल DLM_MSG_REQUEST:
		वापस DLM_MSG_REQUEST_REPLY;
	हाल DLM_MSG_CONVERT:
		वापस DLM_MSG_CONVERT_REPLY;
	हाल DLM_MSG_UNLOCK:
		वापस DLM_MSG_UNLOCK_REPLY;
	हाल DLM_MSG_CANCEL:
		वापस DLM_MSG_CANCEL_REPLY;
	हाल DLM_MSG_LOOKUP:
		वापस DLM_MSG_LOOKUP_REPLY;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक nodeid_warned(पूर्णांक nodeid, पूर्णांक num_nodes, पूर्णांक *warned)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_nodes; i++) अणु
		अगर (!warned[i]) अणु
			warned[i] = nodeid;
			वापस 0;
		पूर्ण
		अगर (warned[i] == nodeid)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम dlm_scan_रुकोers(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_lkb *lkb;
	s64 us;
	s64 debug_maxus = 0;
	u32 debug_scanned = 0;
	u32 debug_expired = 0;
	पूर्णांक num_nodes = 0;
	पूर्णांक *warned = शून्य;

	अगर (!dlm_config.ci_रुकोwarn_us)
		वापस;

	mutex_lock(&ls->ls_रुकोers_mutex);

	list_क्रम_each_entry(lkb, &ls->ls_रुकोers, lkb_रुको_reply) अणु
		अगर (!lkb->lkb_रुको_समय)
			जारी;

		debug_scanned++;

		us = kसमय_प्रकारo_us(kसमय_sub(kसमय_get(), lkb->lkb_रुको_समय));

		अगर (us < dlm_config.ci_रुकोwarn_us)
			जारी;

		lkb->lkb_रुको_समय = 0;

		debug_expired++;
		अगर (us > debug_maxus)
			debug_maxus = us;

		अगर (!num_nodes) अणु
			num_nodes = ls->ls_num_nodes;
			warned = kसुस्मृति(num_nodes, माप(पूर्णांक), GFP_KERNEL);
		पूर्ण
		अगर (!warned)
			जारी;
		अगर (nodeid_warned(lkb->lkb_रुको_nodeid, num_nodes, warned))
			जारी;

		log_error(ls, "waitwarn %x %lld %d us check connection to "
			  "node %d", lkb->lkb_id, (दीर्घ दीर्घ)us,
			  dlm_config.ci_रुकोwarn_us, lkb->lkb_रुको_nodeid);
	पूर्ण
	mutex_unlock(&ls->ls_रुकोers_mutex);
	kमुक्त(warned);

	अगर (debug_expired)
		log_debug(ls, "scan_waiters %u warn %u over %d us max %lld us",
			  debug_scanned, debug_expired,
			  dlm_config.ci_रुकोwarn_us, (दीर्घ दीर्घ)debug_maxus);
पूर्ण

/* add/हटाओ lkb from global रुकोers list of lkb's रुकोing क्रम
   a reply from a remote node */

अटल पूर्णांक add_to_रुकोers(काष्ठा dlm_lkb *lkb, पूर्णांक mstype, पूर्णांक to_nodeid)
अणु
	काष्ठा dlm_ls *ls = lkb->lkb_resource->res_ls;
	पूर्णांक error = 0;

	mutex_lock(&ls->ls_रुकोers_mutex);

	अगर (is_overlap_unlock(lkb) ||
	    (is_overlap_cancel(lkb) && (mstype == DLM_MSG_CANCEL))) अणु
		error = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (lkb->lkb_रुको_type || is_overlap_cancel(lkb)) अणु
		चयन (mstype) अणु
		हाल DLM_MSG_UNLOCK:
			lkb->lkb_flags |= DLM_IFL_OVERLAP_UNLOCK;
			अवरोध;
		हाल DLM_MSG_CANCEL:
			lkb->lkb_flags |= DLM_IFL_OVERLAP_CANCEL;
			अवरोध;
		शेष:
			error = -EBUSY;
			जाओ out;
		पूर्ण
		lkb->lkb_रुको_count++;
		hold_lkb(lkb);

		log_debug(ls, "addwait %x cur %d overlap %d count %d f %x",
			  lkb->lkb_id, lkb->lkb_रुको_type, mstype,
			  lkb->lkb_रुको_count, lkb->lkb_flags);
		जाओ out;
	पूर्ण

	DLM_ASSERT(!lkb->lkb_रुको_count,
		   dlm_prपूर्णांक_lkb(lkb);
		   prपूर्णांकk("wait_count %d\n", lkb->lkb_रुको_count););

	lkb->lkb_रुको_count++;
	lkb->lkb_रुको_type = mstype;
	lkb->lkb_रुको_समय = kसमय_get();
	lkb->lkb_रुको_nodeid = to_nodeid; /* क्रम debugging */
	hold_lkb(lkb);
	list_add(&lkb->lkb_रुको_reply, &ls->ls_रुकोers);
 out:
	अगर (error)
		log_error(ls, "addwait error %x %d flags %x %d %d %s",
			  lkb->lkb_id, error, lkb->lkb_flags, mstype,
			  lkb->lkb_रुको_type, lkb->lkb_resource->res_name);
	mutex_unlock(&ls->ls_रुकोers_mutex);
	वापस error;
पूर्ण

/* We clear the RESEND flag because we might be taking an lkb off the रुकोers
   list as part of process_requestqueue (e.g. a lookup that has an optimized
   request reply on the requestqueue) between dlm_recover_रुकोers_pre() which
   set RESEND and dlm_recover_रुकोers_post() */

अटल पूर्णांक _हटाओ_from_रुकोers(काष्ठा dlm_lkb *lkb, पूर्णांक mstype,
				काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_ls *ls = lkb->lkb_resource->res_ls;
	पूर्णांक overlap_करोne = 0;

	अगर (is_overlap_unlock(lkb) && (mstype == DLM_MSG_UNLOCK_REPLY)) अणु
		log_debug(ls, "remwait %x unlock_reply overlap", lkb->lkb_id);
		lkb->lkb_flags &= ~DLM_IFL_OVERLAP_UNLOCK;
		overlap_करोne = 1;
		जाओ out_del;
	पूर्ण

	अगर (is_overlap_cancel(lkb) && (mstype == DLM_MSG_CANCEL_REPLY)) अणु
		log_debug(ls, "remwait %x cancel_reply overlap", lkb->lkb_id);
		lkb->lkb_flags &= ~DLM_IFL_OVERLAP_CANCEL;
		overlap_करोne = 1;
		जाओ out_del;
	पूर्ण

	/* Cancel state was preemptively cleared by a successful convert,
	   see next comment, nothing to करो. */

	अगर ((mstype == DLM_MSG_CANCEL_REPLY) &&
	    (lkb->lkb_रुको_type != DLM_MSG_CANCEL)) अणु
		log_debug(ls, "remwait %x cancel_reply wait_type %d",
			  lkb->lkb_id, lkb->lkb_रुको_type);
		वापस -1;
	पूर्ण

	/* Remove क्रम the convert reply, and premptively हटाओ क्रम the
	   cancel reply.  A convert has been granted जबतक there's still
	   an outstanding cancel on it (the cancel is moot and the result
	   in the cancel reply should be 0).  We preempt the cancel reply
	   because the app माला_लो the convert result and then can follow up
	   with another op, like convert.  This subsequent op would see the
	   lingering state of the cancel and fail with -EBUSY. */

	अगर ((mstype == DLM_MSG_CONVERT_REPLY) &&
	    (lkb->lkb_रुको_type == DLM_MSG_CONVERT) &&
	    is_overlap_cancel(lkb) && ms && !ms->m_result) अणु
		log_debug(ls, "remwait %x convert_reply zap overlap_cancel",
			  lkb->lkb_id);
		lkb->lkb_रुको_type = 0;
		lkb->lkb_flags &= ~DLM_IFL_OVERLAP_CANCEL;
		lkb->lkb_रुको_count--;
		जाओ out_del;
	पूर्ण

	/* N.B. type of reply may not always correspond to type of original
	   msg due to lookup->request optimization, verअगरy others? */

	अगर (lkb->lkb_रुको_type) अणु
		lkb->lkb_रुको_type = 0;
		जाओ out_del;
	पूर्ण

	log_error(ls, "remwait error %x remote %d %x msg %d flags %x no wait",
		  lkb->lkb_id, ms ? ms->m_header.h_nodeid : 0, lkb->lkb_remid,
		  mstype, lkb->lkb_flags);
	वापस -1;

 out_del:
	/* the क्रमce-unlock/cancel has completed and we haven't recvd a reply
	   to the op that was in progress prior to the unlock/cancel; we
	   give up on any reply to the earlier op.  FIXME: not sure when/how
	   this would happen */

	अगर (overlap_करोne && lkb->lkb_रुको_type) अणु
		log_error(ls, "remwait error %x reply %d wait_type %d overlap",
			  lkb->lkb_id, mstype, lkb->lkb_रुको_type);
		lkb->lkb_रुको_count--;
		lkb->lkb_रुको_type = 0;
	पूर्ण

	DLM_ASSERT(lkb->lkb_रुको_count, dlm_prपूर्णांक_lkb(lkb););

	lkb->lkb_flags &= ~DLM_IFL_RESEND;
	lkb->lkb_रुको_count--;
	अगर (!lkb->lkb_रुको_count)
		list_del_init(&lkb->lkb_रुको_reply);
	unhold_lkb(lkb);
	वापस 0;
पूर्ण

अटल पूर्णांक हटाओ_from_रुकोers(काष्ठा dlm_lkb *lkb, पूर्णांक mstype)
अणु
	काष्ठा dlm_ls *ls = lkb->lkb_resource->res_ls;
	पूर्णांक error;

	mutex_lock(&ls->ls_रुकोers_mutex);
	error = _हटाओ_from_रुकोers(lkb, mstype, शून्य);
	mutex_unlock(&ls->ls_रुकोers_mutex);
	वापस error;
पूर्ण

/* Handles situations where we might be processing a "fake" or "stub" reply in
   which we can't try to take रुकोers_mutex again. */

अटल पूर्णांक हटाओ_from_रुकोers_ms(काष्ठा dlm_lkb *lkb, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_ls *ls = lkb->lkb_resource->res_ls;
	पूर्णांक error;

	अगर (ms->m_flags != DLM_IFL_STUB_MS)
		mutex_lock(&ls->ls_रुकोers_mutex);
	error = _हटाओ_from_रुकोers(lkb, ms->m_type, ms);
	अगर (ms->m_flags != DLM_IFL_STUB_MS)
		mutex_unlock(&ls->ls_रुकोers_mutex);
	वापस error;
पूर्ण

/* If there's an rsb क्रम the same resource being हटाओd, ensure
   that the हटाओ message is sent beक्रमe the new lookup message.
   It should be rare to need a delay here, but अगर not, then it may
   be worthजबतक to add a proper रुको mechanism rather than a delay. */

अटल व्योम रुको_pending_हटाओ(काष्ठा dlm_rsb *r)
अणु
	काष्ठा dlm_ls *ls = r->res_ls;
 restart:
	spin_lock(&ls->ls_हटाओ_spin);
	अगर (ls->ls_हटाओ_len &&
	    !rsb_cmp(r, ls->ls_हटाओ_name, ls->ls_हटाओ_len)) अणु
		log_debug(ls, "delay lookup for remove dir %d %s",
		  	  r->res_dir_nodeid, r->res_name);
		spin_unlock(&ls->ls_हटाओ_spin);
		msleep(1);
		जाओ restart;
	पूर्ण
	spin_unlock(&ls->ls_हटाओ_spin);
पूर्ण

/*
 * ls_हटाओ_spin protects ls_हटाओ_name and ls_हटाओ_len which are
 * पढ़ो by other thपढ़ोs in रुको_pending_हटाओ.  ls_हटाओ_names
 * and ls_हटाओ_lens are only used by the scan thपढ़ो, so they करो
 * not need protection.
 */

अटल व्योम shrink_bucket(काष्ठा dlm_ls *ls, पूर्णांक b)
अणु
	काष्ठा rb_node *n, *next;
	काष्ठा dlm_rsb *r;
	अक्षर *name;
	पूर्णांक our_nodeid = dlm_our_nodeid();
	पूर्णांक remote_count = 0;
	पूर्णांक need_shrink = 0;
	पूर्णांक i, len, rv;

	स_रखो(&ls->ls_हटाओ_lens, 0, माप(पूर्णांक) * DLM_REMOVE_NAMES_MAX);

	spin_lock(&ls->ls_rsbtbl[b].lock);

	अगर (!(ls->ls_rsbtbl[b].flags & DLM_RTF_SHRINK)) अणु
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		वापस;
	पूर्ण

	क्रम (n = rb_first(&ls->ls_rsbtbl[b].toss); n; n = next) अणु
		next = rb_next(n);
		r = rb_entry(n, काष्ठा dlm_rsb, res_hashnode);

		/* If we're the directory record क्रम this rsb, and
		   we're not the master of it, then we need to रुको
		   क्रम the master node to send us a dir हटाओ क्रम
		   beक्रमe removing the dir record. */

		अगर (!dlm_no_directory(ls) &&
		    (r->res_master_nodeid != our_nodeid) &&
		    (dlm_dir_nodeid(r) == our_nodeid)) अणु
			जारी;
		पूर्ण

		need_shrink = 1;

		अगर (!समय_after_eq(jअगरfies, r->res_toss_समय +
				   dlm_config.ci_toss_secs * HZ)) अणु
			जारी;
		पूर्ण

		अगर (!dlm_no_directory(ls) &&
		    (r->res_master_nodeid == our_nodeid) &&
		    (dlm_dir_nodeid(r) != our_nodeid)) अणु

			/* We're the master of this rsb but we're not
			   the directory record, so we need to tell the
			   dir node to हटाओ the dir record. */

			ls->ls_हटाओ_lens[remote_count] = r->res_length;
			स_नकल(ls->ls_हटाओ_names[remote_count], r->res_name,
			       DLM_RESNAME_MAXLEN);
			remote_count++;

			अगर (remote_count >= DLM_REMOVE_NAMES_MAX)
				अवरोध;
			जारी;
		पूर्ण

		अगर (!kref_put(&r->res_ref, समाप्त_rsb)) अणु
			log_error(ls, "tossed rsb in use %s", r->res_name);
			जारी;
		पूर्ण

		rb_erase(&r->res_hashnode, &ls->ls_rsbtbl[b].toss);
		dlm_मुक्त_rsb(r);
	पूर्ण

	अगर (need_shrink)
		ls->ls_rsbtbl[b].flags |= DLM_RTF_SHRINK;
	अन्यथा
		ls->ls_rsbtbl[b].flags &= ~DLM_RTF_SHRINK;
	spin_unlock(&ls->ls_rsbtbl[b].lock);

	/*
	 * While searching क्रम rsb's to मुक्त, we found some that require
	 * remote removal.  We leave them in place and find them again here
	 * so there is a very small gap between removing them from the toss
	 * list and sending the removal.  Keeping this gap small is
	 * important to keep us (the master node) from being out of sync
	 * with the remote dir node क्रम very दीर्घ.
	 *
	 * From the समय the rsb is हटाओd from toss until just after
	 * send_हटाओ, the rsb name is saved in ls_हटाओ_name.  A new
	 * lookup checks this to ensure that a new lookup message क्रम the
	 * same resource name is not sent just beक्रमe the हटाओ message.
	 */

	क्रम (i = 0; i < remote_count; i++) अणु
		name = ls->ls_हटाओ_names[i];
		len = ls->ls_हटाओ_lens[i];

		spin_lock(&ls->ls_rsbtbl[b].lock);
		rv = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].toss, name, len, &r);
		अगर (rv) अणु
			spin_unlock(&ls->ls_rsbtbl[b].lock);
			log_debug(ls, "remove_name not toss %s", name);
			जारी;
		पूर्ण

		अगर (r->res_master_nodeid != our_nodeid) अणु
			spin_unlock(&ls->ls_rsbtbl[b].lock);
			log_debug(ls, "remove_name master %d dir %d our %d %s",
				  r->res_master_nodeid, r->res_dir_nodeid,
				  our_nodeid, name);
			जारी;
		पूर्ण

		अगर (r->res_dir_nodeid == our_nodeid) अणु
			/* should never happen */
			spin_unlock(&ls->ls_rsbtbl[b].lock);
			log_error(ls, "remove_name dir %d master %d our %d %s",
				  r->res_dir_nodeid, r->res_master_nodeid,
				  our_nodeid, name);
			जारी;
		पूर्ण

		अगर (!समय_after_eq(jअगरfies, r->res_toss_समय +
				   dlm_config.ci_toss_secs * HZ)) अणु
			spin_unlock(&ls->ls_rsbtbl[b].lock);
			log_debug(ls, "remove_name toss_time %lu now %lu %s",
				  r->res_toss_समय, jअगरfies, name);
			जारी;
		पूर्ण

		अगर (!kref_put(&r->res_ref, समाप्त_rsb)) अणु
			spin_unlock(&ls->ls_rsbtbl[b].lock);
			log_error(ls, "remove_name in use %s", name);
			जारी;
		पूर्ण

		rb_erase(&r->res_hashnode, &ls->ls_rsbtbl[b].toss);

		/* block lookup of same name until we've sent हटाओ */
		spin_lock(&ls->ls_हटाओ_spin);
		ls->ls_हटाओ_len = len;
		स_नकल(ls->ls_हटाओ_name, name, DLM_RESNAME_MAXLEN);
		spin_unlock(&ls->ls_हटाओ_spin);
		spin_unlock(&ls->ls_rsbtbl[b].lock);

		send_हटाओ(r);

		/* allow lookup of name again */
		spin_lock(&ls->ls_हटाओ_spin);
		ls->ls_हटाओ_len = 0;
		स_रखो(ls->ls_हटाओ_name, 0, DLM_RESNAME_MAXLEN);
		spin_unlock(&ls->ls_हटाओ_spin);

		dlm_मुक्त_rsb(r);
	पूर्ण
पूर्ण

व्योम dlm_scan_rsbs(काष्ठा dlm_ls *ls)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ls->ls_rsbtbl_size; i++) अणु
		shrink_bucket(ls, i);
		अगर (dlm_locking_stopped(ls))
			अवरोध;
		cond_resched();
	पूर्ण
पूर्ण

अटल व्योम add_समयout(काष्ठा dlm_lkb *lkb)
अणु
	काष्ठा dlm_ls *ls = lkb->lkb_resource->res_ls;

	अगर (is_master_copy(lkb))
		वापस;

	अगर (test_bit(LSFL_TIMEWARN, &ls->ls_flags) &&
	    !(lkb->lkb_exflags & DLM_LKF_NODLCKWT)) अणु
		lkb->lkb_flags |= DLM_IFL_WATCH_TIMEWARN;
		जाओ add_it;
	पूर्ण
	अगर (lkb->lkb_exflags & DLM_LKF_TIMEOUT)
		जाओ add_it;
	वापस;

 add_it:
	DLM_ASSERT(list_empty(&lkb->lkb_समय_list), dlm_prपूर्णांक_lkb(lkb););
	mutex_lock(&ls->ls_समयout_mutex);
	hold_lkb(lkb);
	list_add_tail(&lkb->lkb_समय_list, &ls->ls_समयout);
	mutex_unlock(&ls->ls_समयout_mutex);
पूर्ण

अटल व्योम del_समयout(काष्ठा dlm_lkb *lkb)
अणु
	काष्ठा dlm_ls *ls = lkb->lkb_resource->res_ls;

	mutex_lock(&ls->ls_समयout_mutex);
	अगर (!list_empty(&lkb->lkb_समय_list)) अणु
		list_del_init(&lkb->lkb_समय_list);
		unhold_lkb(lkb);
	पूर्ण
	mutex_unlock(&ls->ls_समयout_mutex);
पूर्ण

/* FIXME: is it safe to look at lkb_exflags, lkb_flags, lkb_बारtamp, and
   lkb_lksb_समयout without lock_rsb?  Note: we can't lock समयout_mutex
   and then lock rsb because of lock ordering in add_समयout.  We may need
   to specअगरy some special समयout-related bits in the lkb that are just to
   be accessed under the समयout_mutex. */

व्योम dlm_scan_समयout(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_rsb *r;
	काष्ठा dlm_lkb *lkb;
	पूर्णांक करो_cancel, करो_warn;
	s64 रुको_us;

	क्रम (;;) अणु
		अगर (dlm_locking_stopped(ls))
			अवरोध;

		करो_cancel = 0;
		करो_warn = 0;
		mutex_lock(&ls->ls_समयout_mutex);
		list_क्रम_each_entry(lkb, &ls->ls_समयout, lkb_समय_list) अणु

			रुको_us = kसमय_प्रकारo_us(kसमय_sub(kसमय_get(),
					      		lkb->lkb_बारtamp));

			अगर ((lkb->lkb_exflags & DLM_LKF_TIMEOUT) &&
			    रुको_us >= (lkb->lkb_समयout_cs * 10000))
				करो_cancel = 1;

			अगर ((lkb->lkb_flags & DLM_IFL_WATCH_TIMEWARN) &&
			    रुको_us >= dlm_config.ci_समयwarn_cs * 10000)
				करो_warn = 1;

			अगर (!करो_cancel && !करो_warn)
				जारी;
			hold_lkb(lkb);
			अवरोध;
		पूर्ण
		mutex_unlock(&ls->ls_समयout_mutex);

		अगर (!करो_cancel && !करो_warn)
			अवरोध;

		r = lkb->lkb_resource;
		hold_rsb(r);
		lock_rsb(r);

		अगर (करो_warn) अणु
			/* clear flag so we only warn once */
			lkb->lkb_flags &= ~DLM_IFL_WATCH_TIMEWARN;
			अगर (!(lkb->lkb_exflags & DLM_LKF_TIMEOUT))
				del_समयout(lkb);
			dlm_समयout_warn(lkb);
		पूर्ण

		अगर (करो_cancel) अणु
			log_debug(ls, "timeout cancel %x node %d %s",
				  lkb->lkb_id, lkb->lkb_nodeid, r->res_name);
			lkb->lkb_flags &= ~DLM_IFL_WATCH_TIMEWARN;
			lkb->lkb_flags |= DLM_IFL_TIMEOUT_CANCEL;
			del_समयout(lkb);
			_cancel_lock(r, lkb);
		पूर्ण

		unlock_rsb(r);
		unhold_rsb(r);
		dlm_put_lkb(lkb);
	पूर्ण
पूर्ण

/* This is only called by dlm_recoverd, and we rely on dlm_ls_stop() stopping
   dlm_recoverd beक्रमe checking/setting ls_recover_begin. */

व्योम dlm_adjust_समयouts(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_lkb *lkb;
	u64 adj_us = jअगरfies_to_usecs(jअगरfies - ls->ls_recover_begin);

	ls->ls_recover_begin = 0;
	mutex_lock(&ls->ls_समयout_mutex);
	list_क्रम_each_entry(lkb, &ls->ls_समयout, lkb_समय_list)
		lkb->lkb_बारtamp = kसमय_add_us(lkb->lkb_बारtamp, adj_us);
	mutex_unlock(&ls->ls_समयout_mutex);

	अगर (!dlm_config.ci_रुकोwarn_us)
		वापस;

	mutex_lock(&ls->ls_रुकोers_mutex);
	list_क्रम_each_entry(lkb, &ls->ls_रुकोers, lkb_रुको_reply) अणु
		अगर (kसमय_प्रकारo_us(lkb->lkb_रुको_समय))
			lkb->lkb_रुको_समय = kसमय_get();
	पूर्ण
	mutex_unlock(&ls->ls_रुकोers_mutex);
पूर्ण

/* lkb is master or local copy */

अटल व्योम set_lvb_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	पूर्णांक b, len = r->res_ls->ls_lvblen;

	/* b=1 lvb वापसed to caller
	   b=0 lvb written to rsb or invalidated
	   b=-1 करो nothing */

	b =  dlm_lvb_operations[lkb->lkb_grmode + 1][lkb->lkb_rqmode + 1];

	अगर (b == 1) अणु
		अगर (!lkb->lkb_lvbptr)
			वापस;

		अगर (!(lkb->lkb_exflags & DLM_LKF_VALBLK))
			वापस;

		अगर (!r->res_lvbptr)
			वापस;

		स_नकल(lkb->lkb_lvbptr, r->res_lvbptr, len);
		lkb->lkb_lvbseq = r->res_lvbseq;

	पूर्ण अन्यथा अगर (b == 0) अणु
		अगर (lkb->lkb_exflags & DLM_LKF_IVVALBLK) अणु
			rsb_set_flag(r, RSB_VALNOTVALID);
			वापस;
		पूर्ण

		अगर (!lkb->lkb_lvbptr)
			वापस;

		अगर (!(lkb->lkb_exflags & DLM_LKF_VALBLK))
			वापस;

		अगर (!r->res_lvbptr)
			r->res_lvbptr = dlm_allocate_lvb(r->res_ls);

		अगर (!r->res_lvbptr)
			वापस;

		स_नकल(r->res_lvbptr, lkb->lkb_lvbptr, len);
		r->res_lvbseq++;
		lkb->lkb_lvbseq = r->res_lvbseq;
		rsb_clear_flag(r, RSB_VALNOTVALID);
	पूर्ण

	अगर (rsb_flag(r, RSB_VALNOTVALID))
		lkb->lkb_sbflags |= DLM_SBF_VALNOTVALID;
पूर्ण

अटल व्योम set_lvb_unlock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	अगर (lkb->lkb_grmode < DLM_LOCK_PW)
		वापस;

	अगर (lkb->lkb_exflags & DLM_LKF_IVVALBLK) अणु
		rsb_set_flag(r, RSB_VALNOTVALID);
		वापस;
	पूर्ण

	अगर (!lkb->lkb_lvbptr)
		वापस;

	अगर (!(lkb->lkb_exflags & DLM_LKF_VALBLK))
		वापस;

	अगर (!r->res_lvbptr)
		r->res_lvbptr = dlm_allocate_lvb(r->res_ls);

	अगर (!r->res_lvbptr)
		वापस;

	स_नकल(r->res_lvbptr, lkb->lkb_lvbptr, r->res_ls->ls_lvblen);
	r->res_lvbseq++;
	rsb_clear_flag(r, RSB_VALNOTVALID);
पूर्ण

/* lkb is process copy (pc) */

अटल व्योम set_lvb_lock_pc(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb,
			    काष्ठा dlm_message *ms)
अणु
	पूर्णांक b;

	अगर (!lkb->lkb_lvbptr)
		वापस;

	अगर (!(lkb->lkb_exflags & DLM_LKF_VALBLK))
		वापस;

	b = dlm_lvb_operations[lkb->lkb_grmode + 1][lkb->lkb_rqmode + 1];
	अगर (b == 1) अणु
		पूर्णांक len = receive_extralen(ms);
		अगर (len > r->res_ls->ls_lvblen)
			len = r->res_ls->ls_lvblen;
		स_नकल(lkb->lkb_lvbptr, ms->m_extra, len);
		lkb->lkb_lvbseq = ms->m_lvbseq;
	पूर्ण
पूर्ण

/* Manipulate lkb's on rsb's convert/granted/रुकोing queues
   हटाओ_lock -- used क्रम unlock, हटाओs lkb from granted
   revert_lock -- used क्रम cancel, moves lkb from convert to granted
   grant_lock  -- used क्रम request and convert, adds lkb to granted or
                  moves lkb from convert or रुकोing to granted

   Each of these is used क्रम master or local copy lkb's.  There is
   also a _pc() variation used to make the corresponding change on
   a process copy (pc) lkb. */

अटल व्योम _हटाओ_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	del_lkb(r, lkb);
	lkb->lkb_grmode = DLM_LOCK_IV;
	/* this unhold unकरोes the original ref from create_lkb()
	   so this leads to the lkb being मुक्तd */
	unhold_lkb(lkb);
पूर्ण

अटल व्योम हटाओ_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	set_lvb_unlock(r, lkb);
	_हटाओ_lock(r, lkb);
पूर्ण

अटल व्योम हटाओ_lock_pc(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	_हटाओ_lock(r, lkb);
पूर्ण

/* वापसs: 0 did nothing
	    1 moved lock to granted
	   -1 हटाओd lock */

अटल पूर्णांक revert_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	पूर्णांक rv = 0;

	lkb->lkb_rqmode = DLM_LOCK_IV;

	चयन (lkb->lkb_status) अणु
	हाल DLM_LKSTS_GRANTED:
		अवरोध;
	हाल DLM_LKSTS_CONVERT:
		move_lkb(r, lkb, DLM_LKSTS_GRANTED);
		rv = 1;
		अवरोध;
	हाल DLM_LKSTS_WAITING:
		del_lkb(r, lkb);
		lkb->lkb_grmode = DLM_LOCK_IV;
		/* this unhold unकरोes the original ref from create_lkb()
		   so this leads to the lkb being मुक्तd */
		unhold_lkb(lkb);
		rv = -1;
		अवरोध;
	शेष:
		log_prपूर्णांक("invalid status for revert %d", lkb->lkb_status);
	पूर्ण
	वापस rv;
पूर्ण

अटल पूर्णांक revert_lock_pc(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	वापस revert_lock(r, lkb);
पूर्ण

अटल व्योम _grant_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	अगर (lkb->lkb_grmode != lkb->lkb_rqmode) अणु
		lkb->lkb_grmode = lkb->lkb_rqmode;
		अगर (lkb->lkb_status)
			move_lkb(r, lkb, DLM_LKSTS_GRANTED);
		अन्यथा
			add_lkb(r, lkb, DLM_LKSTS_GRANTED);
	पूर्ण

	lkb->lkb_rqmode = DLM_LOCK_IV;
	lkb->lkb_highbast = 0;
पूर्ण

अटल व्योम grant_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	set_lvb_lock(r, lkb);
	_grant_lock(r, lkb);
पूर्ण

अटल व्योम grant_lock_pc(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb,
			  काष्ठा dlm_message *ms)
अणु
	set_lvb_lock_pc(r, lkb, ms);
	_grant_lock(r, lkb);
पूर्ण

/* called by grant_pending_locks() which means an async grant message must
   be sent to the requesting node in addition to granting the lock अगर the
   lkb beदीर्घs to a remote node. */

अटल व्योम grant_lock_pending(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	grant_lock(r, lkb);
	अगर (is_master_copy(lkb))
		send_grant(r, lkb);
	अन्यथा
		queue_cast(r, lkb, 0);
पूर्ण

/* The special CONVDEADLK, ALTPR and ALTCW flags allow the master to
   change the granted/requested modes.  We're munging things accordingly in
   the process copy.
   CONVDEADLK: our grmode may have been क्रमced करोwn to NL to resolve a
   conversion deadlock
   ALTPR/ALTCW: our rqmode may have been changed to PR or CW to become
   compatible with other granted locks */

अटल व्योम munge_demoted(काष्ठा dlm_lkb *lkb)
अणु
	अगर (lkb->lkb_rqmode == DLM_LOCK_IV || lkb->lkb_grmode == DLM_LOCK_IV) अणु
		log_prपूर्णांक("munge_demoted %x invalid modes gr %d rq %d",
			  lkb->lkb_id, lkb->lkb_grmode, lkb->lkb_rqmode);
		वापस;
	पूर्ण

	lkb->lkb_grmode = DLM_LOCK_NL;
पूर्ण

अटल व्योम munge_alपंचांगode(काष्ठा dlm_lkb *lkb, काष्ठा dlm_message *ms)
अणु
	अगर (ms->m_type != DLM_MSG_REQUEST_REPLY &&
	    ms->m_type != DLM_MSG_GRANT) अणु
		log_prपूर्णांक("munge_altmode %x invalid reply type %d",
			  lkb->lkb_id, ms->m_type);
		वापस;
	पूर्ण

	अगर (lkb->lkb_exflags & DLM_LKF_ALTPR)
		lkb->lkb_rqmode = DLM_LOCK_PR;
	अन्यथा अगर (lkb->lkb_exflags & DLM_LKF_ALTCW)
		lkb->lkb_rqmode = DLM_LOCK_CW;
	अन्यथा अणु
		log_prपूर्णांक("munge_altmode invalid exflags %x", lkb->lkb_exflags);
		dlm_prपूर्णांक_lkb(lkb);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक first_in_list(काष्ठा dlm_lkb *lkb, काष्ठा list_head *head)
अणु
	काष्ठा dlm_lkb *first = list_entry(head->next, काष्ठा dlm_lkb,
					   lkb_statequeue);
	अगर (lkb->lkb_id == first->lkb_id)
		वापस 1;

	वापस 0;
पूर्ण

/* Check अगर the given lkb conflicts with another lkb on the queue. */

अटल पूर्णांक queue_conflict(काष्ठा list_head *head, काष्ठा dlm_lkb *lkb)
अणु
	काष्ठा dlm_lkb *this;

	list_क्रम_each_entry(this, head, lkb_statequeue) अणु
		अगर (this == lkb)
			जारी;
		अगर (!modes_compat(this, lkb))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * "A conversion deadlock arises with a pair of lock requests in the converting
 * queue क्रम one resource.  The granted mode of each lock blocks the requested
 * mode of the other lock."
 *
 * Part 2: अगर the granted mode of lkb is preventing an earlier lkb in the
 * convert queue from being granted, then deadlk/demote lkb.
 *
 * Example:
 * Granted Queue: empty
 * Convert Queue: NL->EX (first lock)
 *                PR->EX (second lock)
 *
 * The first lock can't be granted because of the granted mode of the second
 * lock and the second lock can't be granted because it's not first in the
 * list.  We either cancel lkb's conversion (PR->EX) and वापस EDEADLK, or we
 * demote the granted mode of lkb (from PR to NL) अगर it has the CONVDEADLK
 * flag set and वापस DEMOTED in the lksb flags.
 *
 * Originally, this function detected conv-deadlk in a more limited scope:
 * - अगर !modes_compat(lkb1, lkb2) && !modes_compat(lkb2, lkb1), or
 * - अगर lkb1 was the first entry in the queue (not just earlier), and was
 *   blocked by the granted mode of lkb2, and there was nothing on the
 *   granted queue preventing lkb1 from being granted immediately, i.e.
 *   lkb2 was the only thing preventing lkb1 from being granted.
 *
 * That second condition meant we'd only say there was conv-deadlk अगर
 * resolving it (by demotion) would lead to the first lock on the convert
 * queue being granted right away.  It allowed conversion deadlocks to exist
 * between locks on the convert queue जबतक they couldn't be granted anyway.
 *
 * Now, we detect and take action on conversion deadlocks immediately when
 * they're created, even अगर they may not be immediately consequential.  If
 * lkb1 exists anywhere in the convert queue and lkb2 comes in with a granted
 * mode that would prevent lkb1's conversion from being granted, we करो a
 * deadlk/demote on lkb2 right away and करोn't let it onto the convert queue.
 * I think this means that the lkb_is_ahead condition below should always
 * be zero, i.e. there will never be conv-deadlk between two locks that are
 * both alपढ़ोy on the convert queue.
 */

अटल पूर्णांक conversion_deadlock_detect(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb2)
अणु
	काष्ठा dlm_lkb *lkb1;
	पूर्णांक lkb_is_ahead = 0;

	list_क्रम_each_entry(lkb1, &r->res_convertqueue, lkb_statequeue) अणु
		अगर (lkb1 == lkb2) अणु
			lkb_is_ahead = 1;
			जारी;
		पूर्ण

		अगर (!lkb_is_ahead) अणु
			अगर (!modes_compat(lkb2, lkb1))
				वापस 1;
		पूर्ण अन्यथा अणु
			अगर (!modes_compat(lkb2, lkb1) &&
			    !modes_compat(lkb1, lkb2))
				वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return 1 अगर the lock can be granted, 0 otherwise.
 * Also detect and resolve conversion deadlocks.
 *
 * lkb is the lock to be granted
 *
 * now is 1 अगर the function is being called in the context of the
 * immediate request, it is 0 अगर called later, after the lock has been
 * queued.
 *
 * recover is 1 अगर dlm_recover_grant() is trying to grant conversions
 * after recovery.
 *
 * References are from chapter 6 of "VAXcluster Principles" by Roy Davis
 */

अटल पूर्णांक _can_be_granted(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb, पूर्णांक now,
			   पूर्णांक recover)
अणु
	पूर्णांक8_t conv = (lkb->lkb_grmode != DLM_LOCK_IV);

	/*
	 * 6-10: Version 5.4 पूर्णांकroduced an option to address the phenomenon of
	 * a new request क्रम a NL mode lock being blocked.
	 *
	 * 6-11: If the optional EXPEDITE flag is used with the new NL mode
	 * request, then it would be granted.  In essence, the use of this flag
	 * tells the Lock Manager to expedite theis request by not considering
	 * what may be in the CONVERTING or WAITING queues...  As of this
	 * writing, the EXPEDITE flag can be used only with new requests क्रम NL
	 * mode locks.  This flag is not valid क्रम conversion requests.
	 *
	 * A लघुcut.  Earlier checks वापस an error अगर EXPEDITE is used in a
	 * conversion or used with a non-NL requested mode.  We also know an
	 * EXPEDITE request is always granted immediately, so now must always
	 * be 1.  The full condition to grant an expedite request: (now &&
	 * !conv && lkb->rqmode == DLM_LOCK_NL && (flags & EXPEDITE)) can
	 * thereक्रमe be लघुened to just checking the flag.
	 */

	अगर (lkb->lkb_exflags & DLM_LKF_EXPEDITE)
		वापस 1;

	/*
	 * A लघुcut. Without this, !queue_conflict(grantqueue, lkb) would be
	 * added to the reमुख्यing conditions.
	 */

	अगर (queue_conflict(&r->res_grantqueue, lkb))
		वापस 0;

	/*
	 * 6-3: By शेष, a conversion request is immediately granted अगर the
	 * requested mode is compatible with the modes of all other granted
	 * locks
	 */

	अगर (queue_conflict(&r->res_convertqueue, lkb))
		वापस 0;

	/*
	 * The RECOVER_GRANT flag means dlm_recover_grant() is granting
	 * locks क्रम a recovered rsb, on which lkb's have been rebuilt.
	 * The lkb's may have been rebuilt on the queues in a dअगरferent
	 * order than they were in on the previous master.  So, granting
	 * queued conversions in order after recovery करोesn't make sense
	 * since the order hasn't been preserved anyway.  The new order
	 * could also have created a new "in place" conversion deadlock.
	 * (e.g. old, failed master held granted EX, with PR->EX, NL->EX.
	 * After recovery, there would be no granted locks, and possibly
	 * NL->EX, PR->EX, an in-place conversion deadlock.)  So, after
	 * recovery, grant conversions without considering order.
	 */

	अगर (conv && recover)
		वापस 1;

	/*
	 * 6-5: But the शेष algorithm क्रम deciding whether to grant or
	 * queue conversion requests करोes not by itself guarantee that such
	 * requests are serviced on a "first come first serve" basis.  This, in
	 * turn, can lead to a phenomenon known as "indefinate postponement".
	 *
	 * 6-7: This issue is dealt with by using the optional QUECVT flag with
	 * the प्रणाली service employed to request a lock conversion.  This flag
	 * क्रमces certain conversion requests to be queued, even अगर they are
	 * compatible with the granted modes of other locks on the same
	 * resource.  Thus, the use of this flag results in conversion requests
	 * being ordered on a "first come first servce" basis.
	 *
	 * DCT: This condition is all about new conversions being able to occur
	 * "in place" जबतक the lock reमुख्यs on the granted queue (assuming
	 * nothing अन्यथा conflicts.)  IOW अगर QUECVT isn't set, a conversion
	 * करोesn't _have_ to go onto the convert queue where it's processed in
	 * order.  The "now" variable is necessary to distinguish converts
	 * being received and processed क्रम the first समय now, because once a
	 * convert is moved to the conversion queue the condition below applies
	 * requiring fअगरo granting.
	 */

	अगर (now && conv && !(lkb->lkb_exflags & DLM_LKF_QUECVT))
		वापस 1;

	/*
	 * Even अगर the convert is compat with all granted locks,
	 * QUECVT क्रमces it behind other locks on the convert queue.
	 */

	अगर (now && conv && (lkb->lkb_exflags & DLM_LKF_QUECVT)) अणु
		अगर (list_empty(&r->res_convertqueue))
			वापस 1;
		अन्यथा
			वापस 0;
	पूर्ण

	/*
	 * The NOORDER flag is set to aव्योम the standard vms rules on grant
	 * order.
	 */

	अगर (lkb->lkb_exflags & DLM_LKF_NOORDER)
		वापस 1;

	/*
	 * 6-3: Once in that queue [CONVERTING], a conversion request cannot be
	 * granted until all other conversion requests ahead of it are granted
	 * and/or canceled.
	 */

	अगर (!now && conv && first_in_list(lkb, &r->res_convertqueue))
		वापस 1;

	/*
	 * 6-4: By शेष, a new request is immediately granted only अगर all
	 * three of the following conditions are satisfied when the request is
	 * issued:
	 * - The queue of ungranted conversion requests क्रम the resource is
	 *   empty.
	 * - The queue of ungranted new requests क्रम the resource is empty.
	 * - The mode of the new request is compatible with the most
	 *   restrictive mode of all granted locks on the resource.
	 */

	अगर (now && !conv && list_empty(&r->res_convertqueue) &&
	    list_empty(&r->res_रुकोqueue))
		वापस 1;

	/*
	 * 6-4: Once a lock request is in the queue of ungranted new requests,
	 * it cannot be granted until the queue of ungranted conversion
	 * requests is empty, all ungranted new requests ahead of it are
	 * granted and/or canceled, and it is compatible with the granted mode
	 * of the most restrictive lock granted on the resource.
	 */

	अगर (!now && !conv && list_empty(&r->res_convertqueue) &&
	    first_in_list(lkb, &r->res_रुकोqueue))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक can_be_granted(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb, पूर्णांक now,
			  पूर्णांक recover, पूर्णांक *err)
अणु
	पूर्णांक rv;
	पूर्णांक8_t alt = 0, rqmode = lkb->lkb_rqmode;
	पूर्णांक8_t is_convert = (lkb->lkb_grmode != DLM_LOCK_IV);

	अगर (err)
		*err = 0;

	rv = _can_be_granted(r, lkb, now, recover);
	अगर (rv)
		जाओ out;

	/*
	 * The CONVDEADLK flag is non-standard and tells the dlm to resolve
	 * conversion deadlocks by demoting grmode to NL, otherwise the dlm
	 * cancels one of the locks.
	 */

	अगर (is_convert && can_be_queued(lkb) &&
	    conversion_deadlock_detect(r, lkb)) अणु
		अगर (lkb->lkb_exflags & DLM_LKF_CONVDEADLK) अणु
			lkb->lkb_grmode = DLM_LOCK_NL;
			lkb->lkb_sbflags |= DLM_SBF_DEMOTED;
		पूर्ण अन्यथा अगर (err) अणु
			*err = -EDEADLK;
		पूर्ण अन्यथा अणु
			log_prपूर्णांक("can_be_granted deadlock %x now %d",
				  lkb->lkb_id, now);
			dlm_dump_rsb(r);
		पूर्ण
		जाओ out;
	पूर्ण

	/*
	 * The ALTPR and ALTCW flags are non-standard and tell the dlm to try
	 * to grant a request in a mode other than the normal rqmode.  It's a
	 * simple way to provide a big optimization to applications that can
	 * use them.
	 */

	अगर (rqmode != DLM_LOCK_PR && (lkb->lkb_exflags & DLM_LKF_ALTPR))
		alt = DLM_LOCK_PR;
	अन्यथा अगर (rqmode != DLM_LOCK_CW && (lkb->lkb_exflags & DLM_LKF_ALTCW))
		alt = DLM_LOCK_CW;

	अगर (alt) अणु
		lkb->lkb_rqmode = alt;
		rv = _can_be_granted(r, lkb, now, 0);
		अगर (rv)
			lkb->lkb_sbflags |= DLM_SBF_ALTMODE;
		अन्यथा
			lkb->lkb_rqmode = rqmode;
	पूर्ण
 out:
	वापस rv;
पूर्ण

/* Returns the highest requested mode of all blocked conversions; sets
   cw अगर there's a blocked conversion to DLM_LOCK_CW. */

अटल पूर्णांक grant_pending_convert(काष्ठा dlm_rsb *r, पूर्णांक high, पूर्णांक *cw,
				 अचिन्हित पूर्णांक *count)
अणु
	काष्ठा dlm_lkb *lkb, *s;
	पूर्णांक recover = rsb_flag(r, RSB_RECOVER_GRANT);
	पूर्णांक hi, demoted, quit, grant_restart, demote_restart;
	पूर्णांक deadlk;

	quit = 0;
 restart:
	grant_restart = 0;
	demote_restart = 0;
	hi = DLM_LOCK_IV;

	list_क्रम_each_entry_safe(lkb, s, &r->res_convertqueue, lkb_statequeue) अणु
		demoted = is_demoted(lkb);
		deadlk = 0;

		अगर (can_be_granted(r, lkb, 0, recover, &deadlk)) अणु
			grant_lock_pending(r, lkb);
			grant_restart = 1;
			अगर (count)
				(*count)++;
			जारी;
		पूर्ण

		अगर (!demoted && is_demoted(lkb)) अणु
			log_prपूर्णांक("WARN: pending demoted %x node %d %s",
				  lkb->lkb_id, lkb->lkb_nodeid, r->res_name);
			demote_restart = 1;
			जारी;
		पूर्ण

		अगर (deadlk) अणु
			/*
			 * If DLM_LKB_NODLKWT flag is set and conversion
			 * deadlock is detected, we request blocking AST and
			 * करोwn (or cancel) conversion.
			 */
			अगर (lkb->lkb_exflags & DLM_LKF_NODLCKWT) अणु
				अगर (lkb->lkb_highbast < lkb->lkb_rqmode) अणु
					queue_bast(r, lkb, lkb->lkb_rqmode);
					lkb->lkb_highbast = lkb->lkb_rqmode;
				पूर्ण
			पूर्ण अन्यथा अणु
				log_prपूर्णांक("WARN: pending deadlock %x node %d %s",
					  lkb->lkb_id, lkb->lkb_nodeid,
					  r->res_name);
				dlm_dump_rsb(r);
			पूर्ण
			जारी;
		पूर्ण

		hi = max_t(पूर्णांक, lkb->lkb_rqmode, hi);

		अगर (cw && lkb->lkb_rqmode == DLM_LOCK_CW)
			*cw = 1;
	पूर्ण

	अगर (grant_restart)
		जाओ restart;
	अगर (demote_restart && !quit) अणु
		quit = 1;
		जाओ restart;
	पूर्ण

	वापस max_t(पूर्णांक, high, hi);
पूर्ण

अटल पूर्णांक grant_pending_रुको(काष्ठा dlm_rsb *r, पूर्णांक high, पूर्णांक *cw,
			      अचिन्हित पूर्णांक *count)
अणु
	काष्ठा dlm_lkb *lkb, *s;

	list_क्रम_each_entry_safe(lkb, s, &r->res_रुकोqueue, lkb_statequeue) अणु
		अगर (can_be_granted(r, lkb, 0, 0, शून्य)) अणु
			grant_lock_pending(r, lkb);
			अगर (count)
				(*count)++;
		पूर्ण अन्यथा अणु
			high = max_t(पूर्णांक, lkb->lkb_rqmode, high);
			अगर (lkb->lkb_rqmode == DLM_LOCK_CW)
				*cw = 1;
		पूर्ण
	पूर्ण

	वापस high;
पूर्ण

/* cw of 1 means there's a lock with a rqmode of DLM_LOCK_CW that's blocked
   on either the convert or रुकोing queue.
   high is the largest rqmode of all locks blocked on the convert or
   रुकोing queue. */

अटल पूर्णांक lock_requires_bast(काष्ठा dlm_lkb *gr, पूर्णांक high, पूर्णांक cw)
अणु
	अगर (gr->lkb_grmode == DLM_LOCK_PR && cw) अणु
		अगर (gr->lkb_highbast < DLM_LOCK_EX)
			वापस 1;
		वापस 0;
	पूर्ण

	अगर (gr->lkb_highbast < high &&
	    !__dlm_compat_matrix[gr->lkb_grmode+1][high+1])
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम grant_pending_locks(काष्ठा dlm_rsb *r, अचिन्हित पूर्णांक *count)
अणु
	काष्ठा dlm_lkb *lkb, *s;
	पूर्णांक high = DLM_LOCK_IV;
	पूर्णांक cw = 0;

	अगर (!is_master(r)) अणु
		log_prपूर्णांक("grant_pending_locks r nodeid %d", r->res_nodeid);
		dlm_dump_rsb(r);
		वापस;
	पूर्ण

	high = grant_pending_convert(r, high, &cw, count);
	high = grant_pending_रुको(r, high, &cw, count);

	अगर (high == DLM_LOCK_IV)
		वापस;

	/*
	 * If there are locks left on the रुको/convert queue then send blocking
	 * ASTs to granted locks based on the largest requested mode (high)
	 * found above.
	 */

	list_क्रम_each_entry_safe(lkb, s, &r->res_grantqueue, lkb_statequeue) अणु
		अगर (lkb->lkb_bastfn && lock_requires_bast(lkb, high, cw)) अणु
			अगर (cw && high == DLM_LOCK_PR &&
			    lkb->lkb_grmode == DLM_LOCK_PR)
				queue_bast(r, lkb, DLM_LOCK_CW);
			अन्यथा
				queue_bast(r, lkb, high);
			lkb->lkb_highbast = high;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक modes_require_bast(काष्ठा dlm_lkb *gr, काष्ठा dlm_lkb *rq)
अणु
	अगर ((gr->lkb_grmode == DLM_LOCK_PR && rq->lkb_rqmode == DLM_LOCK_CW) ||
	    (gr->lkb_grmode == DLM_LOCK_CW && rq->lkb_rqmode == DLM_LOCK_PR)) अणु
		अगर (gr->lkb_highbast < DLM_LOCK_EX)
			वापस 1;
		वापस 0;
	पूर्ण

	अगर (gr->lkb_highbast < rq->lkb_rqmode && !modes_compat(gr, rq))
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम send_bast_queue(काष्ठा dlm_rsb *r, काष्ठा list_head *head,
			    काष्ठा dlm_lkb *lkb)
अणु
	काष्ठा dlm_lkb *gr;

	list_क्रम_each_entry(gr, head, lkb_statequeue) अणु
		/* skip self when sending basts to convertqueue */
		अगर (gr == lkb)
			जारी;
		अगर (gr->lkb_bastfn && modes_require_bast(gr, lkb)) अणु
			queue_bast(r, gr, lkb->lkb_rqmode);
			gr->lkb_highbast = lkb->lkb_rqmode;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम send_blocking_asts(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	send_bast_queue(r, &r->res_grantqueue, lkb);
पूर्ण

अटल व्योम send_blocking_asts_all(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	send_bast_queue(r, &r->res_grantqueue, lkb);
	send_bast_queue(r, &r->res_convertqueue, lkb);
पूर्ण

/* set_master(r, lkb) -- set the master nodeid of a resource

   The purpose of this function is to set the nodeid field in the given
   lkb using the nodeid field in the given rsb.  If the rsb's nodeid is
   known, it can just be copied to the lkb and the function will वापस
   0.  If the rsb's nodeid is _not_ known, it needs to be looked up
   beक्रमe it can be copied to the lkb.

   When the rsb nodeid is being looked up remotely, the initial lkb
   causing the lookup is kept on the ls_रुकोers list रुकोing क्रम the
   lookup reply.  Other lkb's रुकोing क्रम the same rsb lookup are kept
   on the rsb's res_lookup list until the master is verअगरied.

   Return values:
   0: nodeid is set in rsb/lkb and the caller should go ahead and use it
   1: the rsb master is not available and the lkb has been placed on
      a रुको queue
*/

अटल पूर्णांक set_master(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	पूर्णांक our_nodeid = dlm_our_nodeid();

	अगर (rsb_flag(r, RSB_MASTER_UNCERTAIN)) अणु
		rsb_clear_flag(r, RSB_MASTER_UNCERTAIN);
		r->res_first_lkid = lkb->lkb_id;
		lkb->lkb_nodeid = r->res_nodeid;
		वापस 0;
	पूर्ण

	अगर (r->res_first_lkid && r->res_first_lkid != lkb->lkb_id) अणु
		list_add_tail(&lkb->lkb_rsb_lookup, &r->res_lookup);
		वापस 1;
	पूर्ण

	अगर (r->res_master_nodeid == our_nodeid) अणु
		lkb->lkb_nodeid = 0;
		वापस 0;
	पूर्ण

	अगर (r->res_master_nodeid) अणु
		lkb->lkb_nodeid = r->res_master_nodeid;
		वापस 0;
	पूर्ण

	अगर (dlm_dir_nodeid(r) == our_nodeid) अणु
		/* This is a somewhat unusual हाल; find_rsb will usually
		   have set res_master_nodeid when dir nodeid is local, but
		   there are हालs where we become the dir node after we've
		   past find_rsb and go through _request_lock again.
		   confirm_master() or process_lookup_list() needs to be
		   called after this. */
		log_debug(r->res_ls, "set_master %x self master %d dir %d %s",
			  lkb->lkb_id, r->res_master_nodeid, r->res_dir_nodeid,
			  r->res_name);
		r->res_master_nodeid = our_nodeid;
		r->res_nodeid = 0;
		lkb->lkb_nodeid = 0;
		वापस 0;
	पूर्ण

	रुको_pending_हटाओ(r);

	r->res_first_lkid = lkb->lkb_id;
	send_lookup(r, lkb);
	वापस 1;
पूर्ण

अटल व्योम process_lookup_list(काष्ठा dlm_rsb *r)
अणु
	काष्ठा dlm_lkb *lkb, *safe;

	list_क्रम_each_entry_safe(lkb, safe, &r->res_lookup, lkb_rsb_lookup) अणु
		list_del_init(&lkb->lkb_rsb_lookup);
		_request_lock(r, lkb);
		schedule();
	पूर्ण
पूर्ण

/* confirm_master -- confirm (or deny) an rsb's master nodeid */

अटल व्योम confirm_master(काष्ठा dlm_rsb *r, पूर्णांक error)
अणु
	काष्ठा dlm_lkb *lkb;

	अगर (!r->res_first_lkid)
		वापस;

	चयन (error) अणु
	हाल 0:
	हाल -EINPROGRESS:
		r->res_first_lkid = 0;
		process_lookup_list(r);
		अवरोध;

	हाल -EAGAIN:
	हाल -EBADR:
	हाल -ENOTBLK:
		/* the remote request failed and won't be retried (it was
		   a NOQUEUE, or has been canceled/unlocked); make a रुकोing
		   lkb the first_lkid */

		r->res_first_lkid = 0;

		अगर (!list_empty(&r->res_lookup)) अणु
			lkb = list_entry(r->res_lookup.next, काष्ठा dlm_lkb,
					 lkb_rsb_lookup);
			list_del_init(&lkb->lkb_rsb_lookup);
			r->res_first_lkid = lkb->lkb_id;
			_request_lock(r, lkb);
		पूर्ण
		अवरोध;

	शेष:
		log_error(r->res_ls, "confirm_master unknown error %d", error);
	पूर्ण
पूर्ण

अटल पूर्णांक set_lock_args(पूर्णांक mode, काष्ठा dlm_lksb *lksb, uपूर्णांक32_t flags,
			 पूर्णांक namelen, अचिन्हित दीर्घ समयout_cs,
			 व्योम (*ast) (व्योम *astparam),
			 व्योम *astparam,
			 व्योम (*bast) (व्योम *astparam, पूर्णांक mode),
			 काष्ठा dlm_args *args)
अणु
	पूर्णांक rv = -EINVAL;

	/* check क्रम invalid arg usage */

	अगर (mode < 0 || mode > DLM_LOCK_EX)
		जाओ out;

	अगर (!(flags & DLM_LKF_CONVERT) && (namelen > DLM_RESNAME_MAXLEN))
		जाओ out;

	अगर (flags & DLM_LKF_CANCEL)
		जाओ out;

	अगर (flags & DLM_LKF_QUECVT && !(flags & DLM_LKF_CONVERT))
		जाओ out;

	अगर (flags & DLM_LKF_CONVDEADLK && !(flags & DLM_LKF_CONVERT))
		जाओ out;

	अगर (flags & DLM_LKF_CONVDEADLK && flags & DLM_LKF_NOQUEUE)
		जाओ out;

	अगर (flags & DLM_LKF_EXPEDITE && flags & DLM_LKF_CONVERT)
		जाओ out;

	अगर (flags & DLM_LKF_EXPEDITE && flags & DLM_LKF_QUECVT)
		जाओ out;

	अगर (flags & DLM_LKF_EXPEDITE && flags & DLM_LKF_NOQUEUE)
		जाओ out;

	अगर (flags & DLM_LKF_EXPEDITE && mode != DLM_LOCK_NL)
		जाओ out;

	अगर (!ast || !lksb)
		जाओ out;

	अगर (flags & DLM_LKF_VALBLK && !lksb->sb_lvbptr)
		जाओ out;

	अगर (flags & DLM_LKF_CONVERT && !lksb->sb_lkid)
		जाओ out;

	/* these args will be copied to the lkb in validate_lock_args,
	   it cannot be करोne now because when converting locks, fields in
	   an active lkb cannot be modअगरied beक्रमe locking the rsb */

	args->flags = flags;
	args->astfn = ast;
	args->astparam = astparam;
	args->bastfn = bast;
	args->समयout = समयout_cs;
	args->mode = mode;
	args->lksb = lksb;
	rv = 0;
 out:
	वापस rv;
पूर्ण

अटल पूर्णांक set_unlock_args(uपूर्णांक32_t flags, व्योम *astarg, काष्ठा dlm_args *args)
अणु
	अगर (flags & ~(DLM_LKF_CANCEL | DLM_LKF_VALBLK | DLM_LKF_IVVALBLK |
 		      DLM_LKF_FORCEUNLOCK))
		वापस -EINVAL;

	अगर (flags & DLM_LKF_CANCEL && flags & DLM_LKF_FORCEUNLOCK)
		वापस -EINVAL;

	args->flags = flags;
	args->astparam = astarg;
	वापस 0;
पूर्ण

अटल पूर्णांक validate_lock_args(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb,
			      काष्ठा dlm_args *args)
अणु
	पूर्णांक rv = -EINVAL;

	अगर (args->flags & DLM_LKF_CONVERT) अणु
		अगर (lkb->lkb_flags & DLM_IFL_MSTCPY)
			जाओ out;

		अगर (args->flags & DLM_LKF_QUECVT &&
		    !__quecvt_compat_matrix[lkb->lkb_grmode+1][args->mode+1])
			जाओ out;

		rv = -EBUSY;
		अगर (lkb->lkb_status != DLM_LKSTS_GRANTED)
			जाओ out;

		अगर (lkb->lkb_रुको_type)
			जाओ out;

		अगर (is_overlap(lkb))
			जाओ out;
	पूर्ण

	lkb->lkb_exflags = args->flags;
	lkb->lkb_sbflags = 0;
	lkb->lkb_astfn = args->astfn;
	lkb->lkb_astparam = args->astparam;
	lkb->lkb_bastfn = args->bastfn;
	lkb->lkb_rqmode = args->mode;
	lkb->lkb_lksb = args->lksb;
	lkb->lkb_lvbptr = args->lksb->sb_lvbptr;
	lkb->lkb_ownpid = (पूर्णांक) current->pid;
	lkb->lkb_समयout_cs = args->समयout;
	rv = 0;
 out:
	अगर (rv)
		log_debug(ls, "validate_lock_args %d %x %x %x %d %d %s",
			  rv, lkb->lkb_id, lkb->lkb_flags, args->flags,
			  lkb->lkb_status, lkb->lkb_रुको_type,
			  lkb->lkb_resource->res_name);
	वापस rv;
पूर्ण

/* when dlm_unlock() sees -EBUSY with CANCEL/FORCEUNLOCK it वापसs 0
   क्रम success */

/* note: it's valid क्रम lkb_nodeid/res_nodeid to be -1 when we get here
   because there may be a lookup in progress and it's valid to करो
   cancel/unlockf on it */

अटल पूर्णांक validate_unlock_args(काष्ठा dlm_lkb *lkb, काष्ठा dlm_args *args)
अणु
	काष्ठा dlm_ls *ls = lkb->lkb_resource->res_ls;
	पूर्णांक rv = -EINVAL;

	अगर (lkb->lkb_flags & DLM_IFL_MSTCPY) अणु
		log_error(ls, "unlock on MSTCPY %x", lkb->lkb_id);
		dlm_prपूर्णांक_lkb(lkb);
		जाओ out;
	पूर्ण

	/* an lkb may still exist even though the lock is EOL'ed due to a
	   cancel, unlock or failed noqueue request; an app can't use these
	   locks; वापस same error as अगर the lkid had not been found at all */

	अगर (lkb->lkb_flags & DLM_IFL_ENDOFLIFE) अणु
		log_debug(ls, "unlock on ENDOFLIFE %x", lkb->lkb_id);
		rv = -ENOENT;
		जाओ out;
	पूर्ण

	/* an lkb may be रुकोing क्रम an rsb lookup to complete where the
	   lookup was initiated by another lock */

	अगर (!list_empty(&lkb->lkb_rsb_lookup)) अणु
		अगर (args->flags & (DLM_LKF_CANCEL | DLM_LKF_FORCEUNLOCK)) अणु
			log_debug(ls, "unlock on rsb_lookup %x", lkb->lkb_id);
			list_del_init(&lkb->lkb_rsb_lookup);
			queue_cast(lkb->lkb_resource, lkb,
				   args->flags & DLM_LKF_CANCEL ?
				   -DLM_ECANCEL : -DLM_EUNLOCK);
			unhold_lkb(lkb); /* unकरोes create_lkb() */
		पूर्ण
		/* caller changes -EBUSY to 0 क्रम CANCEL and FORCEUNLOCK */
		rv = -EBUSY;
		जाओ out;
	पूर्ण

	/* cancel not allowed with another cancel/unlock in progress */

	अगर (args->flags & DLM_LKF_CANCEL) अणु
		अगर (lkb->lkb_exflags & DLM_LKF_CANCEL)
			जाओ out;

		अगर (is_overlap(lkb))
			जाओ out;

		/* करोn't let scand try to करो a cancel */
		del_समयout(lkb);

		अगर (lkb->lkb_flags & DLM_IFL_RESEND) अणु
			lkb->lkb_flags |= DLM_IFL_OVERLAP_CANCEL;
			rv = -EBUSY;
			जाओ out;
		पूर्ण

		/* there's nothing to cancel */
		अगर (lkb->lkb_status == DLM_LKSTS_GRANTED &&
		    !lkb->lkb_रुको_type) अणु
			rv = -EBUSY;
			जाओ out;
		पूर्ण

		चयन (lkb->lkb_रुको_type) अणु
		हाल DLM_MSG_LOOKUP:
		हाल DLM_MSG_REQUEST:
			lkb->lkb_flags |= DLM_IFL_OVERLAP_CANCEL;
			rv = -EBUSY;
			जाओ out;
		हाल DLM_MSG_UNLOCK:
		हाल DLM_MSG_CANCEL:
			जाओ out;
		पूर्ण
		/* add_to_रुकोers() will set OVERLAP_CANCEL */
		जाओ out_ok;
	पूर्ण

	/* करो we need to allow a क्रमce-unlock अगर there's a normal unlock
	   alपढ़ोy in progress?  in what conditions could the normal unlock
	   fail such that we'd want to send a क्रमce-unlock to be sure? */

	अगर (args->flags & DLM_LKF_FORCEUNLOCK) अणु
		अगर (lkb->lkb_exflags & DLM_LKF_FORCEUNLOCK)
			जाओ out;

		अगर (is_overlap_unlock(lkb))
			जाओ out;

		/* करोn't let scand try to करो a cancel */
		del_समयout(lkb);

		अगर (lkb->lkb_flags & DLM_IFL_RESEND) अणु
			lkb->lkb_flags |= DLM_IFL_OVERLAP_UNLOCK;
			rv = -EBUSY;
			जाओ out;
		पूर्ण

		चयन (lkb->lkb_रुको_type) अणु
		हाल DLM_MSG_LOOKUP:
		हाल DLM_MSG_REQUEST:
			lkb->lkb_flags |= DLM_IFL_OVERLAP_UNLOCK;
			rv = -EBUSY;
			जाओ out;
		हाल DLM_MSG_UNLOCK:
			जाओ out;
		पूर्ण
		/* add_to_रुकोers() will set OVERLAP_UNLOCK */
		जाओ out_ok;
	पूर्ण

	/* normal unlock not allowed अगर there's any op in progress */
	rv = -EBUSY;
	अगर (lkb->lkb_रुको_type || lkb->lkb_रुको_count)
		जाओ out;

 out_ok:
	/* an overlapping op shouldn't blow away exflags from other op */
	lkb->lkb_exflags |= args->flags;
	lkb->lkb_sbflags = 0;
	lkb->lkb_astparam = args->astparam;
	rv = 0;
 out:
	अगर (rv)
		log_debug(ls, "validate_unlock_args %d %x %x %x %x %d %s", rv,
			  lkb->lkb_id, lkb->lkb_flags, lkb->lkb_exflags,
			  args->flags, lkb->lkb_रुको_type,
			  lkb->lkb_resource->res_name);
	वापस rv;
पूर्ण

/*
 * Four stage 4 varieties:
 * करो_request(), करो_convert(), करो_unlock(), करो_cancel()
 * These are called on the master node क्रम the given lock and
 * from the central locking logic.
 */

अटल पूर्णांक करो_request(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	पूर्णांक error = 0;

	अगर (can_be_granted(r, lkb, 1, 0, शून्य)) अणु
		grant_lock(r, lkb);
		queue_cast(r, lkb, 0);
		जाओ out;
	पूर्ण

	अगर (can_be_queued(lkb)) अणु
		error = -EINPROGRESS;
		add_lkb(r, lkb, DLM_LKSTS_WAITING);
		add_समयout(lkb);
		जाओ out;
	पूर्ण

	error = -EAGAIN;
	queue_cast(r, lkb, -EAGAIN);
 out:
	वापस error;
पूर्ण

अटल व्योम करो_request_effects(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb,
			       पूर्णांक error)
अणु
	चयन (error) अणु
	हाल -EAGAIN:
		अगर (क्रमce_blocking_asts(lkb))
			send_blocking_asts_all(r, lkb);
		अवरोध;
	हाल -EINPROGRESS:
		send_blocking_asts(r, lkb);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक करो_convert(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	पूर्णांक error = 0;
	पूर्णांक deadlk = 0;

	/* changing an existing lock may allow others to be granted */

	अगर (can_be_granted(r, lkb, 1, 0, &deadlk)) अणु
		grant_lock(r, lkb);
		queue_cast(r, lkb, 0);
		जाओ out;
	पूर्ण

	/* can_be_granted() detected that this lock would block in a conversion
	   deadlock, so we leave it on the granted queue and वापस EDEADLK in
	   the ast क्रम the convert. */

	अगर (deadlk && !(lkb->lkb_exflags & DLM_LKF_NODLCKWT)) अणु
		/* it's left on the granted queue */
		revert_lock(r, lkb);
		queue_cast(r, lkb, -EDEADLK);
		error = -EDEADLK;
		जाओ out;
	पूर्ण

	/* is_demoted() means the can_be_granted() above set the grmode
	   to NL, and left us on the granted queue.  This स्वतः-demotion
	   (due to CONVDEADLK) might mean other locks, and/or this lock, are
	   now grantable.  We have to try to grant other converting locks
	   beक्रमe we try again to grant this one. */

	अगर (is_demoted(lkb)) अणु
		grant_pending_convert(r, DLM_LOCK_IV, शून्य, शून्य);
		अगर (_can_be_granted(r, lkb, 1, 0)) अणु
			grant_lock(r, lkb);
			queue_cast(r, lkb, 0);
			जाओ out;
		पूर्ण
		/* अन्यथा fall through and move to convert queue */
	पूर्ण

	अगर (can_be_queued(lkb)) अणु
		error = -EINPROGRESS;
		del_lkb(r, lkb);
		add_lkb(r, lkb, DLM_LKSTS_CONVERT);
		add_समयout(lkb);
		जाओ out;
	पूर्ण

	error = -EAGAIN;
	queue_cast(r, lkb, -EAGAIN);
 out:
	वापस error;
पूर्ण

अटल व्योम करो_convert_effects(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb,
			       पूर्णांक error)
अणु
	चयन (error) अणु
	हाल 0:
		grant_pending_locks(r, शून्य);
		/* grant_pending_locks also sends basts */
		अवरोध;
	हाल -EAGAIN:
		अगर (क्रमce_blocking_asts(lkb))
			send_blocking_asts_all(r, lkb);
		अवरोध;
	हाल -EINPROGRESS:
		send_blocking_asts(r, lkb);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक करो_unlock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	हटाओ_lock(r, lkb);
	queue_cast(r, lkb, -DLM_EUNLOCK);
	वापस -DLM_EUNLOCK;
पूर्ण

अटल व्योम करो_unlock_effects(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb,
			      पूर्णांक error)
अणु
	grant_pending_locks(r, शून्य);
पूर्ण

/* वापसs: 0 did nothing, -DLM_ECANCEL canceled lock */

अटल पूर्णांक करो_cancel(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	पूर्णांक error;

	error = revert_lock(r, lkb);
	अगर (error) अणु
		queue_cast(r, lkb, -DLM_ECANCEL);
		वापस -DLM_ECANCEL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम करो_cancel_effects(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb,
			      पूर्णांक error)
अणु
	अगर (error)
		grant_pending_locks(r, शून्य);
पूर्ण

/*
 * Four stage 3 varieties:
 * _request_lock(), _convert_lock(), _unlock_lock(), _cancel_lock()
 */

/* add a new lkb to a possibly new rsb, called by requesting process */

अटल पूर्णांक _request_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	पूर्णांक error;

	/* set_master: sets lkb nodeid from r */

	error = set_master(r, lkb);
	अगर (error < 0)
		जाओ out;
	अगर (error) अणु
		error = 0;
		जाओ out;
	पूर्ण

	अगर (is_remote(r)) अणु
		/* receive_request() calls करो_request() on remote node */
		error = send_request(r, lkb);
	पूर्ण अन्यथा अणु
		error = करो_request(r, lkb);
		/* क्रम remote locks the request_reply is sent
		   between करो_request and करो_request_effects */
		करो_request_effects(r, lkb, error);
	पूर्ण
 out:
	वापस error;
पूर्ण

/* change some property of an existing lkb, e.g. mode */

अटल पूर्णांक _convert_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	पूर्णांक error;

	अगर (is_remote(r)) अणु
		/* receive_convert() calls करो_convert() on remote node */
		error = send_convert(r, lkb);
	पूर्ण अन्यथा अणु
		error = करो_convert(r, lkb);
		/* क्रम remote locks the convert_reply is sent
		   between करो_convert and करो_convert_effects */
		करो_convert_effects(r, lkb, error);
	पूर्ण

	वापस error;
पूर्ण

/* हटाओ an existing lkb from the granted queue */

अटल पूर्णांक _unlock_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	पूर्णांक error;

	अगर (is_remote(r)) अणु
		/* receive_unlock() calls करो_unlock() on remote node */
		error = send_unlock(r, lkb);
	पूर्ण अन्यथा अणु
		error = करो_unlock(r, lkb);
		/* क्रम remote locks the unlock_reply is sent
		   between करो_unlock and करो_unlock_effects */
		करो_unlock_effects(r, lkb, error);
	पूर्ण

	वापस error;
पूर्ण

/* हटाओ an existing lkb from the convert or रुको queue */

अटल पूर्णांक _cancel_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	पूर्णांक error;

	अगर (is_remote(r)) अणु
		/* receive_cancel() calls करो_cancel() on remote node */
		error = send_cancel(r, lkb);
	पूर्ण अन्यथा अणु
		error = करो_cancel(r, lkb);
		/* क्रम remote locks the cancel_reply is sent
		   between करो_cancel and करो_cancel_effects */
		करो_cancel_effects(r, lkb, error);
	पूर्ण

	वापस error;
पूर्ण

/*
 * Four stage 2 varieties:
 * request_lock(), convert_lock(), unlock_lock(), cancel_lock()
 */

अटल पूर्णांक request_lock(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb, अक्षर *name,
			पूर्णांक len, काष्ठा dlm_args *args)
अणु
	काष्ठा dlm_rsb *r;
	पूर्णांक error;

	error = validate_lock_args(ls, lkb, args);
	अगर (error)
		वापस error;

	error = find_rsb(ls, name, len, 0, R_REQUEST, &r);
	अगर (error)
		वापस error;

	lock_rsb(r);

	attach_lkb(r, lkb);
	lkb->lkb_lksb->sb_lkid = lkb->lkb_id;

	error = _request_lock(r, lkb);

	unlock_rsb(r);
	put_rsb(r);
	वापस error;
पूर्ण

अटल पूर्णांक convert_lock(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb,
			काष्ठा dlm_args *args)
अणु
	काष्ठा dlm_rsb *r;
	पूर्णांक error;

	r = lkb->lkb_resource;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_lock_args(ls, lkb, args);
	अगर (error)
		जाओ out;

	error = _convert_lock(r, lkb);
 out:
	unlock_rsb(r);
	put_rsb(r);
	वापस error;
पूर्ण

अटल पूर्णांक unlock_lock(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb,
		       काष्ठा dlm_args *args)
अणु
	काष्ठा dlm_rsb *r;
	पूर्णांक error;

	r = lkb->lkb_resource;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_unlock_args(lkb, args);
	अगर (error)
		जाओ out;

	error = _unlock_lock(r, lkb);
 out:
	unlock_rsb(r);
	put_rsb(r);
	वापस error;
पूर्ण

अटल पूर्णांक cancel_lock(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb,
		       काष्ठा dlm_args *args)
अणु
	काष्ठा dlm_rsb *r;
	पूर्णांक error;

	r = lkb->lkb_resource;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_unlock_args(lkb, args);
	अगर (error)
		जाओ out;

	error = _cancel_lock(r, lkb);
 out:
	unlock_rsb(r);
	put_rsb(r);
	वापस error;
पूर्ण

/*
 * Two stage 1 varieties:  dlm_lock() and dlm_unlock()
 */

पूर्णांक dlm_lock(dlm_lockspace_t *lockspace,
	     पूर्णांक mode,
	     काष्ठा dlm_lksb *lksb,
	     uपूर्णांक32_t flags,
	     व्योम *name,
	     अचिन्हित पूर्णांक namelen,
	     uपूर्णांक32_t parent_lkid,
	     व्योम (*ast) (व्योम *astarg),
	     व्योम *astarg,
	     व्योम (*bast) (व्योम *astarg, पूर्णांक mode))
अणु
	काष्ठा dlm_ls *ls;
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_args args;
	पूर्णांक error, convert = flags & DLM_LKF_CONVERT;

	ls = dlm_find_lockspace_local(lockspace);
	अगर (!ls)
		वापस -EINVAL;

	dlm_lock_recovery(ls);

	अगर (convert)
		error = find_lkb(ls, lksb->sb_lkid, &lkb);
	अन्यथा
		error = create_lkb(ls, &lkb);

	अगर (error)
		जाओ out;

	error = set_lock_args(mode, lksb, flags, namelen, 0, ast,
			      astarg, bast, &args);
	अगर (error)
		जाओ out_put;

	अगर (convert)
		error = convert_lock(ls, lkb, &args);
	अन्यथा
		error = request_lock(ls, lkb, name, namelen, &args);

	अगर (error == -EINPROGRESS)
		error = 0;
 out_put:
	अगर (convert || error)
		__put_lkb(ls, lkb);
	अगर (error == -EAGAIN || error == -EDEADLK)
		error = 0;
 out:
	dlm_unlock_recovery(ls);
	dlm_put_lockspace(ls);
	वापस error;
पूर्ण

पूर्णांक dlm_unlock(dlm_lockspace_t *lockspace,
	       uपूर्णांक32_t lkid,
	       uपूर्णांक32_t flags,
	       काष्ठा dlm_lksb *lksb,
	       व्योम *astarg)
अणु
	काष्ठा dlm_ls *ls;
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_args args;
	पूर्णांक error;

	ls = dlm_find_lockspace_local(lockspace);
	अगर (!ls)
		वापस -EINVAL;

	dlm_lock_recovery(ls);

	error = find_lkb(ls, lkid, &lkb);
	अगर (error)
		जाओ out;

	error = set_unlock_args(flags, astarg, &args);
	अगर (error)
		जाओ out_put;

	अगर (flags & DLM_LKF_CANCEL)
		error = cancel_lock(ls, lkb, &args);
	अन्यथा
		error = unlock_lock(ls, lkb, &args);

	अगर (error == -DLM_EUNLOCK || error == -DLM_ECANCEL)
		error = 0;
	अगर (error == -EBUSY && (flags & (DLM_LKF_CANCEL | DLM_LKF_FORCEUNLOCK)))
		error = 0;
 out_put:
	dlm_put_lkb(lkb);
 out:
	dlm_unlock_recovery(ls);
	dlm_put_lockspace(ls);
	वापस error;
पूर्ण

/*
 * send/receive routines क्रम remote operations and replies
 *
 * send_args
 * send_common
 * send_request			receive_request
 * send_convert			receive_convert
 * send_unlock			receive_unlock
 * send_cancel			receive_cancel
 * send_grant			receive_grant
 * send_bast			receive_bast
 * send_lookup			receive_lookup
 * send_हटाओ			receive_हटाओ
 *
 * 				send_common_reply
 * receive_request_reply	send_request_reply
 * receive_convert_reply	send_convert_reply
 * receive_unlock_reply		send_unlock_reply
 * receive_cancel_reply		send_cancel_reply
 * receive_lookup_reply		send_lookup_reply
 */

अटल पूर्णांक _create_message(काष्ठा dlm_ls *ls, पूर्णांक mb_len,
			   पूर्णांक to_nodeid, पूर्णांक mstype,
			   काष्ठा dlm_message **ms_ret,
			   काष्ठा dlm_mhandle **mh_ret)
अणु
	काष्ठा dlm_message *ms;
	काष्ठा dlm_mhandle *mh;
	अक्षर *mb;

	/* get_buffer gives us a message handle (mh) that we need to
	   pass पूर्णांकo lowcomms_commit and a message buffer (mb) that we
	   ग_लिखो our data पूर्णांकo */

	mh = dlm_lowcomms_get_buffer(to_nodeid, mb_len, GFP_NOFS, &mb);
	अगर (!mh)
		वापस -ENOBUFS;

	ms = (काष्ठा dlm_message *) mb;

	ms->m_header.h_version = (DLM_HEADER_MAJOR | DLM_HEADER_MINOR);
	ms->m_header.h_lockspace = ls->ls_global_id;
	ms->m_header.h_nodeid = dlm_our_nodeid();
	ms->m_header.h_length = mb_len;
	ms->m_header.h_cmd = DLM_MSG;

	ms->m_type = mstype;

	*mh_ret = mh;
	*ms_ret = ms;
	वापस 0;
पूर्ण

अटल पूर्णांक create_message(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb,
			  पूर्णांक to_nodeid, पूर्णांक mstype,
			  काष्ठा dlm_message **ms_ret,
			  काष्ठा dlm_mhandle **mh_ret)
अणु
	पूर्णांक mb_len = माप(काष्ठा dlm_message);

	चयन (mstype) अणु
	हाल DLM_MSG_REQUEST:
	हाल DLM_MSG_LOOKUP:
	हाल DLM_MSG_REMOVE:
		mb_len += r->res_length;
		अवरोध;
	हाल DLM_MSG_CONVERT:
	हाल DLM_MSG_UNLOCK:
	हाल DLM_MSG_REQUEST_REPLY:
	हाल DLM_MSG_CONVERT_REPLY:
	हाल DLM_MSG_GRANT:
		अगर (lkb && lkb->lkb_lvbptr)
			mb_len += r->res_ls->ls_lvblen;
		अवरोध;
	पूर्ण

	वापस _create_message(r->res_ls, mb_len, to_nodeid, mstype,
			       ms_ret, mh_ret);
पूर्ण

/* further lowcomms enhancements or alternate implementations may make
   the वापस value from this function useful at some poपूर्णांक */

अटल पूर्णांक send_message(काष्ठा dlm_mhandle *mh, काष्ठा dlm_message *ms)
अणु
	dlm_message_out(ms);
	dlm_lowcomms_commit_buffer(mh);
	वापस 0;
पूर्ण

अटल व्योम send_args(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb,
		      काष्ठा dlm_message *ms)
अणु
	ms->m_nodeid   = lkb->lkb_nodeid;
	ms->m_pid      = lkb->lkb_ownpid;
	ms->m_lkid     = lkb->lkb_id;
	ms->m_remid    = lkb->lkb_remid;
	ms->m_exflags  = lkb->lkb_exflags;
	ms->m_sbflags  = lkb->lkb_sbflags;
	ms->m_flags    = lkb->lkb_flags;
	ms->m_lvbseq   = lkb->lkb_lvbseq;
	ms->m_status   = lkb->lkb_status;
	ms->m_grmode   = lkb->lkb_grmode;
	ms->m_rqmode   = lkb->lkb_rqmode;
	ms->m_hash     = r->res_hash;

	/* m_result and m_basपंचांगode are set from function args,
	   not from lkb fields */

	अगर (lkb->lkb_bastfn)
		ms->m_asts |= DLM_CB_BAST;
	अगर (lkb->lkb_astfn)
		ms->m_asts |= DLM_CB_CAST;

	/* compare with चयन in create_message; send_हटाओ() करोesn't
	   use send_args() */

	चयन (ms->m_type) अणु
	हाल DLM_MSG_REQUEST:
	हाल DLM_MSG_LOOKUP:
		स_नकल(ms->m_extra, r->res_name, r->res_length);
		अवरोध;
	हाल DLM_MSG_CONVERT:
	हाल DLM_MSG_UNLOCK:
	हाल DLM_MSG_REQUEST_REPLY:
	हाल DLM_MSG_CONVERT_REPLY:
	हाल DLM_MSG_GRANT:
		अगर (!lkb->lkb_lvbptr)
			अवरोध;
		स_नकल(ms->m_extra, lkb->lkb_lvbptr, r->res_ls->ls_lvblen);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक send_common(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb, पूर्णांक mstype)
अणु
	काष्ठा dlm_message *ms;
	काष्ठा dlm_mhandle *mh;
	पूर्णांक to_nodeid, error;

	to_nodeid = r->res_nodeid;

	error = add_to_रुकोers(lkb, mstype, to_nodeid);
	अगर (error)
		वापस error;

	error = create_message(r, lkb, to_nodeid, mstype, &ms, &mh);
	अगर (error)
		जाओ fail;

	send_args(r, lkb, ms);

	error = send_message(mh, ms);
	अगर (error)
		जाओ fail;
	वापस 0;

 fail:
	हटाओ_from_रुकोers(lkb, msg_reply_type(mstype));
	वापस error;
पूर्ण

अटल पूर्णांक send_request(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	वापस send_common(r, lkb, DLM_MSG_REQUEST);
पूर्ण

अटल पूर्णांक send_convert(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	पूर्णांक error;

	error = send_common(r, lkb, DLM_MSG_CONVERT);

	/* करोwn conversions go without a reply from the master */
	अगर (!error && करोwn_conversion(lkb)) अणु
		हटाओ_from_रुकोers(lkb, DLM_MSG_CONVERT_REPLY);
		r->res_ls->ls_stub_ms.m_flags = DLM_IFL_STUB_MS;
		r->res_ls->ls_stub_ms.m_type = DLM_MSG_CONVERT_REPLY;
		r->res_ls->ls_stub_ms.m_result = 0;
		__receive_convert_reply(r, lkb, &r->res_ls->ls_stub_ms);
	पूर्ण

	वापस error;
पूर्ण

/* FIXME: अगर this lkb is the only lock we hold on the rsb, then set
   MASTER_UNCERTAIN to क्रमce the next request on the rsb to confirm
   that the master is still correct. */

अटल पूर्णांक send_unlock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	वापस send_common(r, lkb, DLM_MSG_UNLOCK);
पूर्ण

अटल पूर्णांक send_cancel(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	वापस send_common(r, lkb, DLM_MSG_CANCEL);
पूर्ण

अटल पूर्णांक send_grant(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	काष्ठा dlm_message *ms;
	काष्ठा dlm_mhandle *mh;
	पूर्णांक to_nodeid, error;

	to_nodeid = lkb->lkb_nodeid;

	error = create_message(r, lkb, to_nodeid, DLM_MSG_GRANT, &ms, &mh);
	अगर (error)
		जाओ out;

	send_args(r, lkb, ms);

	ms->m_result = 0;

	error = send_message(mh, ms);
 out:
	वापस error;
पूर्ण

अटल पूर्णांक send_bast(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb, पूर्णांक mode)
अणु
	काष्ठा dlm_message *ms;
	काष्ठा dlm_mhandle *mh;
	पूर्णांक to_nodeid, error;

	to_nodeid = lkb->lkb_nodeid;

	error = create_message(r, शून्य, to_nodeid, DLM_MSG_BAST, &ms, &mh);
	अगर (error)
		जाओ out;

	send_args(r, lkb, ms);

	ms->m_basपंचांगode = mode;

	error = send_message(mh, ms);
 out:
	वापस error;
पूर्ण

अटल पूर्णांक send_lookup(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	काष्ठा dlm_message *ms;
	काष्ठा dlm_mhandle *mh;
	पूर्णांक to_nodeid, error;

	to_nodeid = dlm_dir_nodeid(r);

	error = add_to_रुकोers(lkb, DLM_MSG_LOOKUP, to_nodeid);
	अगर (error)
		वापस error;

	error = create_message(r, शून्य, to_nodeid, DLM_MSG_LOOKUP, &ms, &mh);
	अगर (error)
		जाओ fail;

	send_args(r, lkb, ms);

	error = send_message(mh, ms);
	अगर (error)
		जाओ fail;
	वापस 0;

 fail:
	हटाओ_from_रुकोers(lkb, DLM_MSG_LOOKUP_REPLY);
	वापस error;
पूर्ण

अटल पूर्णांक send_हटाओ(काष्ठा dlm_rsb *r)
अणु
	काष्ठा dlm_message *ms;
	काष्ठा dlm_mhandle *mh;
	पूर्णांक to_nodeid, error;

	to_nodeid = dlm_dir_nodeid(r);

	error = create_message(r, शून्य, to_nodeid, DLM_MSG_REMOVE, &ms, &mh);
	अगर (error)
		जाओ out;

	स_नकल(ms->m_extra, r->res_name, r->res_length);
	ms->m_hash = r->res_hash;

	error = send_message(mh, ms);
 out:
	वापस error;
पूर्ण

अटल पूर्णांक send_common_reply(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb,
			     पूर्णांक mstype, पूर्णांक rv)
अणु
	काष्ठा dlm_message *ms;
	काष्ठा dlm_mhandle *mh;
	पूर्णांक to_nodeid, error;

	to_nodeid = lkb->lkb_nodeid;

	error = create_message(r, lkb, to_nodeid, mstype, &ms, &mh);
	अगर (error)
		जाओ out;

	send_args(r, lkb, ms);

	ms->m_result = rv;

	error = send_message(mh, ms);
 out:
	वापस error;
पूर्ण

अटल पूर्णांक send_request_reply(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb, पूर्णांक rv)
अणु
	वापस send_common_reply(r, lkb, DLM_MSG_REQUEST_REPLY, rv);
पूर्ण

अटल पूर्णांक send_convert_reply(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb, पूर्णांक rv)
अणु
	वापस send_common_reply(r, lkb, DLM_MSG_CONVERT_REPLY, rv);
पूर्ण

अटल पूर्णांक send_unlock_reply(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb, पूर्णांक rv)
अणु
	वापस send_common_reply(r, lkb, DLM_MSG_UNLOCK_REPLY, rv);
पूर्ण

अटल पूर्णांक send_cancel_reply(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb, पूर्णांक rv)
अणु
	वापस send_common_reply(r, lkb, DLM_MSG_CANCEL_REPLY, rv);
पूर्ण

अटल पूर्णांक send_lookup_reply(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms_in,
			     पूर्णांक ret_nodeid, पूर्णांक rv)
अणु
	काष्ठा dlm_rsb *r = &ls->ls_stub_rsb;
	काष्ठा dlm_message *ms;
	काष्ठा dlm_mhandle *mh;
	पूर्णांक error, nodeid = ms_in->m_header.h_nodeid;

	error = create_message(r, शून्य, nodeid, DLM_MSG_LOOKUP_REPLY, &ms, &mh);
	अगर (error)
		जाओ out;

	ms->m_lkid = ms_in->m_lkid;
	ms->m_result = rv;
	ms->m_nodeid = ret_nodeid;

	error = send_message(mh, ms);
 out:
	वापस error;
पूर्ण

/* which args we save from a received message depends heavily on the type
   of message, unlike the send side where we can safely send everything about
   the lkb क्रम any type of message */

अटल व्योम receive_flags(काष्ठा dlm_lkb *lkb, काष्ठा dlm_message *ms)
अणु
	lkb->lkb_exflags = ms->m_exflags;
	lkb->lkb_sbflags = ms->m_sbflags;
	lkb->lkb_flags = (lkb->lkb_flags & 0xFFFF0000) |
		         (ms->m_flags & 0x0000FFFF);
पूर्ण

अटल व्योम receive_flags_reply(काष्ठा dlm_lkb *lkb, काष्ठा dlm_message *ms)
अणु
	अगर (ms->m_flags == DLM_IFL_STUB_MS)
		वापस;

	lkb->lkb_sbflags = ms->m_sbflags;
	lkb->lkb_flags = (lkb->lkb_flags & 0xFFFF0000) |
		         (ms->m_flags & 0x0000FFFF);
पूर्ण

अटल पूर्णांक receive_extralen(काष्ठा dlm_message *ms)
अणु
	वापस (ms->m_header.h_length - माप(काष्ठा dlm_message));
पूर्ण

अटल पूर्णांक receive_lvb(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb,
		       काष्ठा dlm_message *ms)
अणु
	पूर्णांक len;

	अगर (lkb->lkb_exflags & DLM_LKF_VALBLK) अणु
		अगर (!lkb->lkb_lvbptr)
			lkb->lkb_lvbptr = dlm_allocate_lvb(ls);
		अगर (!lkb->lkb_lvbptr)
			वापस -ENOMEM;
		len = receive_extralen(ms);
		अगर (len > ls->ls_lvblen)
			len = ls->ls_lvblen;
		स_नकल(lkb->lkb_lvbptr, ms->m_extra, len);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम fake_bastfn(व्योम *astparam, पूर्णांक mode)
अणु
	log_prपूर्णांक("fake_bastfn should not be called");
पूर्ण

अटल व्योम fake_astfn(व्योम *astparam)
अणु
	log_prपूर्णांक("fake_astfn should not be called");
पूर्ण

अटल पूर्णांक receive_request_args(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb,
				काष्ठा dlm_message *ms)
अणु
	lkb->lkb_nodeid = ms->m_header.h_nodeid;
	lkb->lkb_ownpid = ms->m_pid;
	lkb->lkb_remid = ms->m_lkid;
	lkb->lkb_grmode = DLM_LOCK_IV;
	lkb->lkb_rqmode = ms->m_rqmode;

	lkb->lkb_bastfn = (ms->m_asts & DLM_CB_BAST) ? &fake_bastfn : शून्य;
	lkb->lkb_astfn = (ms->m_asts & DLM_CB_CAST) ? &fake_astfn : शून्य;

	अगर (lkb->lkb_exflags & DLM_LKF_VALBLK) अणु
		/* lkb was just created so there won't be an lvb yet */
		lkb->lkb_lvbptr = dlm_allocate_lvb(ls);
		अगर (!lkb->lkb_lvbptr)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक receive_convert_args(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb,
				काष्ठा dlm_message *ms)
अणु
	अगर (lkb->lkb_status != DLM_LKSTS_GRANTED)
		वापस -EBUSY;

	अगर (receive_lvb(ls, lkb, ms))
		वापस -ENOMEM;

	lkb->lkb_rqmode = ms->m_rqmode;
	lkb->lkb_lvbseq = ms->m_lvbseq;

	वापस 0;
पूर्ण

अटल पूर्णांक receive_unlock_args(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb,
			       काष्ठा dlm_message *ms)
अणु
	अगर (receive_lvb(ls, lkb, ms))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/* We fill in the stub-lkb fields with the info that send_xxxx_reply()
   uses to send a reply and that the remote end uses to process the reply. */

अटल व्योम setup_stub_lkb(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_lkb *lkb = &ls->ls_stub_lkb;
	lkb->lkb_nodeid = ms->m_header.h_nodeid;
	lkb->lkb_remid = ms->m_lkid;
पूर्ण

/* This is called after the rsb is locked so that we can safely inspect
   fields in the lkb. */

अटल पूर्णांक validate_message(काष्ठा dlm_lkb *lkb, काष्ठा dlm_message *ms)
अणु
	पूर्णांक from = ms->m_header.h_nodeid;
	पूर्णांक error = 0;

	चयन (ms->m_type) अणु
	हाल DLM_MSG_CONVERT:
	हाल DLM_MSG_UNLOCK:
	हाल DLM_MSG_CANCEL:
		अगर (!is_master_copy(lkb) || lkb->lkb_nodeid != from)
			error = -EINVAL;
		अवरोध;

	हाल DLM_MSG_CONVERT_REPLY:
	हाल DLM_MSG_UNLOCK_REPLY:
	हाल DLM_MSG_CANCEL_REPLY:
	हाल DLM_MSG_GRANT:
	हाल DLM_MSG_BAST:
		अगर (!is_process_copy(lkb) || lkb->lkb_nodeid != from)
			error = -EINVAL;
		अवरोध;

	हाल DLM_MSG_REQUEST_REPLY:
		अगर (!is_process_copy(lkb))
			error = -EINVAL;
		अन्यथा अगर (lkb->lkb_nodeid != -1 && lkb->lkb_nodeid != from)
			error = -EINVAL;
		अवरोध;

	शेष:
		error = -EINVAL;
	पूर्ण

	अगर (error)
		log_error(lkb->lkb_resource->res_ls,
			  "ignore invalid message %d from %d %x %x %x %d",
			  ms->m_type, from, lkb->lkb_id, lkb->lkb_remid,
			  lkb->lkb_flags, lkb->lkb_nodeid);
	वापस error;
पूर्ण

अटल व्योम send_repeat_हटाओ(काष्ठा dlm_ls *ls, अक्षर *ms_name, पूर्णांक len)
अणु
	अक्षर name[DLM_RESNAME_MAXLEN + 1];
	काष्ठा dlm_message *ms;
	काष्ठा dlm_mhandle *mh;
	काष्ठा dlm_rsb *r;
	uपूर्णांक32_t hash, b;
	पूर्णांक rv, dir_nodeid;

	स_रखो(name, 0, माप(name));
	स_नकल(name, ms_name, len);

	hash = jhash(name, len, 0);
	b = hash & (ls->ls_rsbtbl_size - 1);

	dir_nodeid = dlm_hash2nodeid(ls, hash);

	log_error(ls, "send_repeat_remove dir %d %s", dir_nodeid, name);

	spin_lock(&ls->ls_rsbtbl[b].lock);
	rv = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].keep, name, len, &r);
	अगर (!rv) अणु
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		log_error(ls, "repeat_remove on keep %s", name);
		वापस;
	पूर्ण

	rv = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].toss, name, len, &r);
	अगर (!rv) अणु
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		log_error(ls, "repeat_remove on toss %s", name);
		वापस;
	पूर्ण

	/* use ls->हटाओ_name2 to aव्योम conflict with shrink? */

	spin_lock(&ls->ls_हटाओ_spin);
	ls->ls_हटाओ_len = len;
	स_नकल(ls->ls_हटाओ_name, name, DLM_RESNAME_MAXLEN);
	spin_unlock(&ls->ls_हटाओ_spin);
	spin_unlock(&ls->ls_rsbtbl[b].lock);

	rv = _create_message(ls, माप(काष्ठा dlm_message) + len,
			     dir_nodeid, DLM_MSG_REMOVE, &ms, &mh);
	अगर (rv)
		वापस;

	स_नकल(ms->m_extra, name, len);
	ms->m_hash = hash;

	send_message(mh, ms);

	spin_lock(&ls->ls_हटाओ_spin);
	ls->ls_हटाओ_len = 0;
	स_रखो(ls->ls_हटाओ_name, 0, DLM_RESNAME_MAXLEN);
	spin_unlock(&ls->ls_हटाओ_spin);
पूर्ण

अटल पूर्णांक receive_request(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_rsb *r;
	पूर्णांक from_nodeid;
	पूर्णांक error, namelen = 0;

	from_nodeid = ms->m_header.h_nodeid;

	error = create_lkb(ls, &lkb);
	अगर (error)
		जाओ fail;

	receive_flags(lkb, ms);
	lkb->lkb_flags |= DLM_IFL_MSTCPY;
	error = receive_request_args(ls, lkb, ms);
	अगर (error) अणु
		__put_lkb(ls, lkb);
		जाओ fail;
	पूर्ण

	/* The dir node is the authority on whether we are the master
	   क्रम this rsb or not, so अगर the master sends us a request, we should
	   recreate the rsb अगर we've destroyed it.   This race happens when we
	   send a हटाओ message to the dir node at the same समय that the dir
	   node sends us a request क्रम the rsb. */

	namelen = receive_extralen(ms);

	error = find_rsb(ls, ms->m_extra, namelen, from_nodeid,
			 R_RECEIVE_REQUEST, &r);
	अगर (error) अणु
		__put_lkb(ls, lkb);
		जाओ fail;
	पूर्ण

	lock_rsb(r);

	अगर (r->res_master_nodeid != dlm_our_nodeid()) अणु
		error = validate_master_nodeid(ls, r, from_nodeid);
		अगर (error) अणु
			unlock_rsb(r);
			put_rsb(r);
			__put_lkb(ls, lkb);
			जाओ fail;
		पूर्ण
	पूर्ण

	attach_lkb(r, lkb);
	error = करो_request(r, lkb);
	send_request_reply(r, lkb, error);
	करो_request_effects(r, lkb, error);

	unlock_rsb(r);
	put_rsb(r);

	अगर (error == -EINPROGRESS)
		error = 0;
	अगर (error)
		dlm_put_lkb(lkb);
	वापस 0;

 fail:
	/* TODO: instead of वापसing ENOTBLK, add the lkb to res_lookup
	   and करो this receive_request again from process_lookup_list once
	   we get the lookup reply.  This would aव्योम a many repeated
	   ENOTBLK request failures when the lookup reply designating us
	   as master is delayed. */

	/* We could repeatedly वापस -EBADR here अगर our send_हटाओ() is
	   delayed in being sent/arriving/being processed on the dir node.
	   Another node would repeatedly lookup up the master, and the dir
	   node would जारी वापसing our nodeid until our send_हटाओ
	   took effect.

	   We send another हटाओ message in हाल our previous send_हटाओ
	   was lost/ignored/missed somehow. */

	अगर (error != -ENOTBLK) अणु
		log_limit(ls, "receive_request %x from %d %d",
			  ms->m_lkid, from_nodeid, error);
	पूर्ण

	अगर (namelen && error == -EBADR) अणु
		send_repeat_हटाओ(ls, ms->m_extra, namelen);
		msleep(1000);
	पूर्ण

	setup_stub_lkb(ls, ms);
	send_request_reply(&ls->ls_stub_rsb, &ls->ls_stub_lkb, error);
	वापस error;
पूर्ण

अटल पूर्णांक receive_convert(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_rsb *r;
	पूर्णांक error, reply = 1;

	error = find_lkb(ls, ms->m_remid, &lkb);
	अगर (error)
		जाओ fail;

	अगर (lkb->lkb_remid != ms->m_lkid) अणु
		log_error(ls, "receive_convert %x remid %x recover_seq %llu "
			  "remote %d %x", lkb->lkb_id, lkb->lkb_remid,
			  (अचिन्हित दीर्घ दीर्घ)lkb->lkb_recover_seq,
			  ms->m_header.h_nodeid, ms->m_lkid);
		error = -ENOENT;
		dlm_put_lkb(lkb);
		जाओ fail;
	पूर्ण

	r = lkb->lkb_resource;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_message(lkb, ms);
	अगर (error)
		जाओ out;

	receive_flags(lkb, ms);

	error = receive_convert_args(ls, lkb, ms);
	अगर (error) अणु
		send_convert_reply(r, lkb, error);
		जाओ out;
	पूर्ण

	reply = !करोwn_conversion(lkb);

	error = करो_convert(r, lkb);
	अगर (reply)
		send_convert_reply(r, lkb, error);
	करो_convert_effects(r, lkb, error);
 out:
	unlock_rsb(r);
	put_rsb(r);
	dlm_put_lkb(lkb);
	वापस 0;

 fail:
	setup_stub_lkb(ls, ms);
	send_convert_reply(&ls->ls_stub_rsb, &ls->ls_stub_lkb, error);
	वापस error;
पूर्ण

अटल पूर्णांक receive_unlock(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_rsb *r;
	पूर्णांक error;

	error = find_lkb(ls, ms->m_remid, &lkb);
	अगर (error)
		जाओ fail;

	अगर (lkb->lkb_remid != ms->m_lkid) अणु
		log_error(ls, "receive_unlock %x remid %x remote %d %x",
			  lkb->lkb_id, lkb->lkb_remid,
			  ms->m_header.h_nodeid, ms->m_lkid);
		error = -ENOENT;
		dlm_put_lkb(lkb);
		जाओ fail;
	पूर्ण

	r = lkb->lkb_resource;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_message(lkb, ms);
	अगर (error)
		जाओ out;

	receive_flags(lkb, ms);

	error = receive_unlock_args(ls, lkb, ms);
	अगर (error) अणु
		send_unlock_reply(r, lkb, error);
		जाओ out;
	पूर्ण

	error = करो_unlock(r, lkb);
	send_unlock_reply(r, lkb, error);
	करो_unlock_effects(r, lkb, error);
 out:
	unlock_rsb(r);
	put_rsb(r);
	dlm_put_lkb(lkb);
	वापस 0;

 fail:
	setup_stub_lkb(ls, ms);
	send_unlock_reply(&ls->ls_stub_rsb, &ls->ls_stub_lkb, error);
	वापस error;
पूर्ण

अटल पूर्णांक receive_cancel(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_rsb *r;
	पूर्णांक error;

	error = find_lkb(ls, ms->m_remid, &lkb);
	अगर (error)
		जाओ fail;

	receive_flags(lkb, ms);

	r = lkb->lkb_resource;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_message(lkb, ms);
	अगर (error)
		जाओ out;

	error = करो_cancel(r, lkb);
	send_cancel_reply(r, lkb, error);
	करो_cancel_effects(r, lkb, error);
 out:
	unlock_rsb(r);
	put_rsb(r);
	dlm_put_lkb(lkb);
	वापस 0;

 fail:
	setup_stub_lkb(ls, ms);
	send_cancel_reply(&ls->ls_stub_rsb, &ls->ls_stub_lkb, error);
	वापस error;
पूर्ण

अटल पूर्णांक receive_grant(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_rsb *r;
	पूर्णांक error;

	error = find_lkb(ls, ms->m_remid, &lkb);
	अगर (error)
		वापस error;

	r = lkb->lkb_resource;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_message(lkb, ms);
	अगर (error)
		जाओ out;

	receive_flags_reply(lkb, ms);
	अगर (is_alपंचांगode(lkb))
		munge_alपंचांगode(lkb, ms);
	grant_lock_pc(r, lkb, ms);
	queue_cast(r, lkb, 0);
 out:
	unlock_rsb(r);
	put_rsb(r);
	dlm_put_lkb(lkb);
	वापस 0;
पूर्ण

अटल पूर्णांक receive_bast(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_rsb *r;
	पूर्णांक error;

	error = find_lkb(ls, ms->m_remid, &lkb);
	अगर (error)
		वापस error;

	r = lkb->lkb_resource;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_message(lkb, ms);
	अगर (error)
		जाओ out;

	queue_bast(r, lkb, ms->m_basपंचांगode);
	lkb->lkb_highbast = ms->m_basपंचांगode;
 out:
	unlock_rsb(r);
	put_rsb(r);
	dlm_put_lkb(lkb);
	वापस 0;
पूर्ण

अटल व्योम receive_lookup(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	पूर्णांक len, error, ret_nodeid, from_nodeid, our_nodeid;

	from_nodeid = ms->m_header.h_nodeid;
	our_nodeid = dlm_our_nodeid();

	len = receive_extralen(ms);

	error = dlm_master_lookup(ls, from_nodeid, ms->m_extra, len, 0,
				  &ret_nodeid, शून्य);

	/* Optimization: we're master so treat lookup as a request */
	अगर (!error && ret_nodeid == our_nodeid) अणु
		receive_request(ls, ms);
		वापस;
	पूर्ण
	send_lookup_reply(ls, ms, ret_nodeid, error);
पूर्ण

अटल व्योम receive_हटाओ(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	अक्षर name[DLM_RESNAME_MAXLEN+1];
	काष्ठा dlm_rsb *r;
	uपूर्णांक32_t hash, b;
	पूर्णांक rv, len, dir_nodeid, from_nodeid;

	from_nodeid = ms->m_header.h_nodeid;

	len = receive_extralen(ms);

	अगर (len > DLM_RESNAME_MAXLEN) अणु
		log_error(ls, "receive_remove from %d bad len %d",
			  from_nodeid, len);
		वापस;
	पूर्ण

	dir_nodeid = dlm_hash2nodeid(ls, ms->m_hash);
	अगर (dir_nodeid != dlm_our_nodeid()) अणु
		log_error(ls, "receive_remove from %d bad nodeid %d",
			  from_nodeid, dir_nodeid);
		वापस;
	पूर्ण

	/* Look क्रम name on rsbtbl.toss, अगर it's there, समाप्त it.
	   If it's on rsbtbl.keep, it's being used, and we should ignore this
	   message.  This is an expected race between the dir node sending a
	   request to the master node at the same समय as the master node sends
	   a हटाओ to the dir node.  The resolution to that race is क्रम the
	   dir node to ignore the हटाओ message, and the master node to
	   recreate the master rsb when it माला_लो a request from the dir node क्रम
	   an rsb it करोesn't have. */

	स_रखो(name, 0, माप(name));
	स_नकल(name, ms->m_extra, len);

	hash = jhash(name, len, 0);
	b = hash & (ls->ls_rsbtbl_size - 1);

	spin_lock(&ls->ls_rsbtbl[b].lock);

	rv = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].toss, name, len, &r);
	अगर (rv) अणु
		/* verअगरy the rsb is on keep list per comment above */
		rv = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].keep, name, len, &r);
		अगर (rv) अणु
			/* should not happen */
			log_error(ls, "receive_remove from %d not found %s",
				  from_nodeid, name);
			spin_unlock(&ls->ls_rsbtbl[b].lock);
			वापस;
		पूर्ण
		अगर (r->res_master_nodeid != from_nodeid) अणु
			/* should not happen */
			log_error(ls, "receive_remove keep from %d master %d",
				  from_nodeid, r->res_master_nodeid);
			dlm_prपूर्णांक_rsb(r);
			spin_unlock(&ls->ls_rsbtbl[b].lock);
			वापस;
		पूर्ण

		log_debug(ls, "receive_remove from %d master %d first %x %s",
			  from_nodeid, r->res_master_nodeid, r->res_first_lkid,
			  name);
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		वापस;
	पूर्ण

	अगर (r->res_master_nodeid != from_nodeid) अणु
		log_error(ls, "receive_remove toss from %d master %d",
			  from_nodeid, r->res_master_nodeid);
		dlm_prपूर्णांक_rsb(r);
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		वापस;
	पूर्ण

	अगर (kref_put(&r->res_ref, समाप्त_rsb)) अणु
		rb_erase(&r->res_hashnode, &ls->ls_rsbtbl[b].toss);
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		dlm_मुक्त_rsb(r);
	पूर्ण अन्यथा अणु
		log_error(ls, "receive_remove from %d rsb ref error",
			  from_nodeid);
		dlm_prपूर्णांक_rsb(r);
		spin_unlock(&ls->ls_rsbtbl[b].lock);
	पूर्ण
पूर्ण

अटल व्योम receive_purge(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	करो_purge(ls, ms->m_nodeid, ms->m_pid);
पूर्ण

अटल पूर्णांक receive_request_reply(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_rsb *r;
	पूर्णांक error, mstype, result;
	पूर्णांक from_nodeid = ms->m_header.h_nodeid;

	error = find_lkb(ls, ms->m_remid, &lkb);
	अगर (error)
		वापस error;

	r = lkb->lkb_resource;
	hold_rsb(r);
	lock_rsb(r);

	error = validate_message(lkb, ms);
	अगर (error)
		जाओ out;

	mstype = lkb->lkb_रुको_type;
	error = हटाओ_from_रुकोers(lkb, DLM_MSG_REQUEST_REPLY);
	अगर (error) अणु
		log_error(ls, "receive_request_reply %x remote %d %x result %d",
			  lkb->lkb_id, from_nodeid, ms->m_lkid, ms->m_result);
		dlm_dump_rsb(r);
		जाओ out;
	पूर्ण

	/* Optimization: the dir node was also the master, so it took our
	   lookup as a request and sent request reply instead of lookup reply */
	अगर (mstype == DLM_MSG_LOOKUP) अणु
		r->res_master_nodeid = from_nodeid;
		r->res_nodeid = from_nodeid;
		lkb->lkb_nodeid = from_nodeid;
	पूर्ण

	/* this is the value वापसed from करो_request() on the master */
	result = ms->m_result;

	चयन (result) अणु
	हाल -EAGAIN:
		/* request would block (be queued) on remote master */
		queue_cast(r, lkb, -EAGAIN);
		confirm_master(r, -EAGAIN);
		unhold_lkb(lkb); /* unकरोes create_lkb() */
		अवरोध;

	हाल -EINPROGRESS:
	हाल 0:
		/* request was queued or granted on remote master */
		receive_flags_reply(lkb, ms);
		lkb->lkb_remid = ms->m_lkid;
		अगर (is_alपंचांगode(lkb))
			munge_alपंचांगode(lkb, ms);
		अगर (result) अणु
			add_lkb(r, lkb, DLM_LKSTS_WAITING);
			add_समयout(lkb);
		पूर्ण अन्यथा अणु
			grant_lock_pc(r, lkb, ms);
			queue_cast(r, lkb, 0);
		पूर्ण
		confirm_master(r, result);
		अवरोध;

	हाल -EBADR:
	हाल -ENOTBLK:
		/* find_rsb failed to find rsb or rsb wasn't master */
		log_limit(ls, "receive_request_reply %x from %d %d "
			  "master %d dir %d first %x %s", lkb->lkb_id,
			  from_nodeid, result, r->res_master_nodeid,
			  r->res_dir_nodeid, r->res_first_lkid, r->res_name);

		अगर (r->res_dir_nodeid != dlm_our_nodeid() &&
		    r->res_master_nodeid != dlm_our_nodeid()) अणु
			/* cause _request_lock->set_master->send_lookup */
			r->res_master_nodeid = 0;
			r->res_nodeid = -1;
			lkb->lkb_nodeid = -1;
		पूर्ण

		अगर (is_overlap(lkb)) अणु
			/* we'll ignore error in cancel/unlock reply */
			queue_cast_overlap(r, lkb);
			confirm_master(r, result);
			unhold_lkb(lkb); /* unकरोes create_lkb() */
		पूर्ण अन्यथा अणु
			_request_lock(r, lkb);

			अगर (r->res_master_nodeid == dlm_our_nodeid())
				confirm_master(r, 0);
		पूर्ण
		अवरोध;

	शेष:
		log_error(ls, "receive_request_reply %x error %d",
			  lkb->lkb_id, result);
	पूर्ण

	अगर (is_overlap_unlock(lkb) && (result == 0 || result == -EINPROGRESS)) अणु
		log_debug(ls, "receive_request_reply %x result %d unlock",
			  lkb->lkb_id, result);
		lkb->lkb_flags &= ~DLM_IFL_OVERLAP_UNLOCK;
		lkb->lkb_flags &= ~DLM_IFL_OVERLAP_CANCEL;
		send_unlock(r, lkb);
	पूर्ण अन्यथा अगर (is_overlap_cancel(lkb) && (result == -EINPROGRESS)) अणु
		log_debug(ls, "receive_request_reply %x cancel", lkb->lkb_id);
		lkb->lkb_flags &= ~DLM_IFL_OVERLAP_UNLOCK;
		lkb->lkb_flags &= ~DLM_IFL_OVERLAP_CANCEL;
		send_cancel(r, lkb);
	पूर्ण अन्यथा अणु
		lkb->lkb_flags &= ~DLM_IFL_OVERLAP_CANCEL;
		lkb->lkb_flags &= ~DLM_IFL_OVERLAP_UNLOCK;
	पूर्ण
 out:
	unlock_rsb(r);
	put_rsb(r);
	dlm_put_lkb(lkb);
	वापस 0;
पूर्ण

अटल व्योम __receive_convert_reply(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb,
				    काष्ठा dlm_message *ms)
अणु
	/* this is the value वापसed from करो_convert() on the master */
	चयन (ms->m_result) अणु
	हाल -EAGAIN:
		/* convert would block (be queued) on remote master */
		queue_cast(r, lkb, -EAGAIN);
		अवरोध;

	हाल -EDEADLK:
		receive_flags_reply(lkb, ms);
		revert_lock_pc(r, lkb);
		queue_cast(r, lkb, -EDEADLK);
		अवरोध;

	हाल -EINPROGRESS:
		/* convert was queued on remote master */
		receive_flags_reply(lkb, ms);
		अगर (is_demoted(lkb))
			munge_demoted(lkb);
		del_lkb(r, lkb);
		add_lkb(r, lkb, DLM_LKSTS_CONVERT);
		add_समयout(lkb);
		अवरोध;

	हाल 0:
		/* convert was granted on remote master */
		receive_flags_reply(lkb, ms);
		अगर (is_demoted(lkb))
			munge_demoted(lkb);
		grant_lock_pc(r, lkb, ms);
		queue_cast(r, lkb, 0);
		अवरोध;

	शेष:
		log_error(r->res_ls, "receive_convert_reply %x remote %d %x %d",
			  lkb->lkb_id, ms->m_header.h_nodeid, ms->m_lkid,
			  ms->m_result);
		dlm_prपूर्णांक_rsb(r);
		dlm_prपूर्णांक_lkb(lkb);
	पूर्ण
पूर्ण

अटल व्योम _receive_convert_reply(काष्ठा dlm_lkb *lkb, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_rsb *r = lkb->lkb_resource;
	पूर्णांक error;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_message(lkb, ms);
	अगर (error)
		जाओ out;

	/* stub reply can happen with रुकोers_mutex held */
	error = हटाओ_from_रुकोers_ms(lkb, ms);
	अगर (error)
		जाओ out;

	__receive_convert_reply(r, lkb, ms);
 out:
	unlock_rsb(r);
	put_rsb(r);
पूर्ण

अटल पूर्णांक receive_convert_reply(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_lkb *lkb;
	पूर्णांक error;

	error = find_lkb(ls, ms->m_remid, &lkb);
	अगर (error)
		वापस error;

	_receive_convert_reply(lkb, ms);
	dlm_put_lkb(lkb);
	वापस 0;
पूर्ण

अटल व्योम _receive_unlock_reply(काष्ठा dlm_lkb *lkb, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_rsb *r = lkb->lkb_resource;
	पूर्णांक error;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_message(lkb, ms);
	अगर (error)
		जाओ out;

	/* stub reply can happen with रुकोers_mutex held */
	error = हटाओ_from_रुकोers_ms(lkb, ms);
	अगर (error)
		जाओ out;

	/* this is the value वापसed from करो_unlock() on the master */

	चयन (ms->m_result) अणु
	हाल -DLM_EUNLOCK:
		receive_flags_reply(lkb, ms);
		हटाओ_lock_pc(r, lkb);
		queue_cast(r, lkb, -DLM_EUNLOCK);
		अवरोध;
	हाल -ENOENT:
		अवरोध;
	शेष:
		log_error(r->res_ls, "receive_unlock_reply %x error %d",
			  lkb->lkb_id, ms->m_result);
	पूर्ण
 out:
	unlock_rsb(r);
	put_rsb(r);
पूर्ण

अटल पूर्णांक receive_unlock_reply(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_lkb *lkb;
	पूर्णांक error;

	error = find_lkb(ls, ms->m_remid, &lkb);
	अगर (error)
		वापस error;

	_receive_unlock_reply(lkb, ms);
	dlm_put_lkb(lkb);
	वापस 0;
पूर्ण

अटल व्योम _receive_cancel_reply(काष्ठा dlm_lkb *lkb, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_rsb *r = lkb->lkb_resource;
	पूर्णांक error;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_message(lkb, ms);
	अगर (error)
		जाओ out;

	/* stub reply can happen with रुकोers_mutex held */
	error = हटाओ_from_रुकोers_ms(lkb, ms);
	अगर (error)
		जाओ out;

	/* this is the value वापसed from करो_cancel() on the master */

	चयन (ms->m_result) अणु
	हाल -DLM_ECANCEL:
		receive_flags_reply(lkb, ms);
		revert_lock_pc(r, lkb);
		queue_cast(r, lkb, -DLM_ECANCEL);
		अवरोध;
	हाल 0:
		अवरोध;
	शेष:
		log_error(r->res_ls, "receive_cancel_reply %x error %d",
			  lkb->lkb_id, ms->m_result);
	पूर्ण
 out:
	unlock_rsb(r);
	put_rsb(r);
पूर्ण

अटल पूर्णांक receive_cancel_reply(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_lkb *lkb;
	पूर्णांक error;

	error = find_lkb(ls, ms->m_remid, &lkb);
	अगर (error)
		वापस error;

	_receive_cancel_reply(lkb, ms);
	dlm_put_lkb(lkb);
	वापस 0;
पूर्ण

अटल व्योम receive_lookup_reply(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_rsb *r;
	पूर्णांक error, ret_nodeid;
	पूर्णांक करो_lookup_list = 0;

	error = find_lkb(ls, ms->m_lkid, &lkb);
	अगर (error) अणु
		log_error(ls, "receive_lookup_reply no lkid %x", ms->m_lkid);
		वापस;
	पूर्ण

	/* ms->m_result is the value वापसed by dlm_master_lookup on dir node
	   FIXME: will a non-zero error ever be वापसed? */

	r = lkb->lkb_resource;
	hold_rsb(r);
	lock_rsb(r);

	error = हटाओ_from_रुकोers(lkb, DLM_MSG_LOOKUP_REPLY);
	अगर (error)
		जाओ out;

	ret_nodeid = ms->m_nodeid;

	/* We someबार receive a request from the dir node क्रम this
	   rsb beक्रमe we've received the dir node's loookup_reply क्रम it.
	   The request from the dir node implies we're the master, so we set
	   ourself as master in receive_request_reply, and verअगरy here that
	   we are indeed the master. */

	अगर (r->res_master_nodeid && (r->res_master_nodeid != ret_nodeid)) अणु
		/* This should never happen */
		log_error(ls, "receive_lookup_reply %x from %d ret %d "
			  "master %d dir %d our %d first %x %s",
			  lkb->lkb_id, ms->m_header.h_nodeid, ret_nodeid,
			  r->res_master_nodeid, r->res_dir_nodeid,
			  dlm_our_nodeid(), r->res_first_lkid, r->res_name);
	पूर्ण

	अगर (ret_nodeid == dlm_our_nodeid()) अणु
		r->res_master_nodeid = ret_nodeid;
		r->res_nodeid = 0;
		करो_lookup_list = 1;
		r->res_first_lkid = 0;
	पूर्ण अन्यथा अगर (ret_nodeid == -1) अणु
		/* the remote node करोesn't believe it's the dir node */
		log_error(ls, "receive_lookup_reply %x from %d bad ret_nodeid",
			  lkb->lkb_id, ms->m_header.h_nodeid);
		r->res_master_nodeid = 0;
		r->res_nodeid = -1;
		lkb->lkb_nodeid = -1;
	पूर्ण अन्यथा अणु
		/* set_master() will set lkb_nodeid from r */
		r->res_master_nodeid = ret_nodeid;
		r->res_nodeid = ret_nodeid;
	पूर्ण

	अगर (is_overlap(lkb)) अणु
		log_debug(ls, "receive_lookup_reply %x unlock %x",
			  lkb->lkb_id, lkb->lkb_flags);
		queue_cast_overlap(r, lkb);
		unhold_lkb(lkb); /* unकरोes create_lkb() */
		जाओ out_list;
	पूर्ण

	_request_lock(r, lkb);

 out_list:
	अगर (करो_lookup_list)
		process_lookup_list(r);
 out:
	unlock_rsb(r);
	put_rsb(r);
	dlm_put_lkb(lkb);
पूर्ण

अटल व्योम _receive_message(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms,
			     uपूर्णांक32_t saved_seq)
अणु
	पूर्णांक error = 0, noent = 0;

	अगर (!dlm_is_member(ls, ms->m_header.h_nodeid)) अणु
		log_limit(ls, "receive %d from non-member %d %x %x %d",
			  ms->m_type, ms->m_header.h_nodeid, ms->m_lkid,
			  ms->m_remid, ms->m_result);
		वापस;
	पूर्ण

	चयन (ms->m_type) अणु

	/* messages sent to a master node */

	हाल DLM_MSG_REQUEST:
		error = receive_request(ls, ms);
		अवरोध;

	हाल DLM_MSG_CONVERT:
		error = receive_convert(ls, ms);
		अवरोध;

	हाल DLM_MSG_UNLOCK:
		error = receive_unlock(ls, ms);
		अवरोध;

	हाल DLM_MSG_CANCEL:
		noent = 1;
		error = receive_cancel(ls, ms);
		अवरोध;

	/* messages sent from a master node (replies to above) */

	हाल DLM_MSG_REQUEST_REPLY:
		error = receive_request_reply(ls, ms);
		अवरोध;

	हाल DLM_MSG_CONVERT_REPLY:
		error = receive_convert_reply(ls, ms);
		अवरोध;

	हाल DLM_MSG_UNLOCK_REPLY:
		error = receive_unlock_reply(ls, ms);
		अवरोध;

	हाल DLM_MSG_CANCEL_REPLY:
		error = receive_cancel_reply(ls, ms);
		अवरोध;

	/* messages sent from a master node (only two types of async msg) */

	हाल DLM_MSG_GRANT:
		noent = 1;
		error = receive_grant(ls, ms);
		अवरोध;

	हाल DLM_MSG_BAST:
		noent = 1;
		error = receive_bast(ls, ms);
		अवरोध;

	/* messages sent to a dir node */

	हाल DLM_MSG_LOOKUP:
		receive_lookup(ls, ms);
		अवरोध;

	हाल DLM_MSG_REMOVE:
		receive_हटाओ(ls, ms);
		अवरोध;

	/* messages sent from a dir node (हटाओ has no reply) */

	हाल DLM_MSG_LOOKUP_REPLY:
		receive_lookup_reply(ls, ms);
		अवरोध;

	/* other messages */

	हाल DLM_MSG_PURGE:
		receive_purge(ls, ms);
		अवरोध;

	शेष:
		log_error(ls, "unknown message type %d", ms->m_type);
	पूर्ण

	/*
	 * When checking क्रम ENOENT, we're checking the result of
	 * find_lkb(m_remid):
	 *
	 * The lock id referenced in the message wasn't found.  This may
	 * happen in normal usage क्रम the async messages and cancel, so
	 * only use log_debug क्रम them.
	 *
	 * Some errors are expected and normal.
	 */

	अगर (error == -ENOENT && noent) अणु
		log_debug(ls, "receive %d no %x remote %d %x saved_seq %u",
			  ms->m_type, ms->m_remid, ms->m_header.h_nodeid,
			  ms->m_lkid, saved_seq);
	पूर्ण अन्यथा अगर (error == -ENOENT) अणु
		log_error(ls, "receive %d no %x remote %d %x saved_seq %u",
			  ms->m_type, ms->m_remid, ms->m_header.h_nodeid,
			  ms->m_lkid, saved_seq);

		अगर (ms->m_type == DLM_MSG_CONVERT)
			dlm_dump_rsb_hash(ls, ms->m_hash);
	पूर्ण

	अगर (error == -EINVAL) अणु
		log_error(ls, "receive %d inval from %d lkid %x remid %x "
			  "saved_seq %u",
			  ms->m_type, ms->m_header.h_nodeid,
			  ms->m_lkid, ms->m_remid, saved_seq);
	पूर्ण
पूर्ण

/* If the lockspace is in recovery mode (locking stopped), then normal
   messages are saved on the requestqueue क्रम processing after recovery is
   करोne.  When not in recovery mode, we रुको क्रम dlm_recoverd to drain saved
   messages off the requestqueue beक्रमe we process new ones. This occurs right
   after recovery completes when we transition from saving all messages on
   requestqueue, to processing all the saved messages, to processing new
   messages as they arrive. */

अटल व्योम dlm_receive_message(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms,
				पूर्णांक nodeid)
अणु
	अगर (dlm_locking_stopped(ls)) अणु
		/* If we were a member of this lockspace, left, and rejoined,
		   other nodes may still be sending us messages from the
		   lockspace generation beक्रमe we left. */
		अगर (!ls->ls_generation) अणु
			log_limit(ls, "receive %d from %d ignore old gen",
				  ms->m_type, nodeid);
			वापस;
		पूर्ण

		dlm_add_requestqueue(ls, nodeid, ms);
	पूर्ण अन्यथा अणु
		dlm_रुको_requestqueue(ls);
		_receive_message(ls, ms, 0);
	पूर्ण
पूर्ण

/* This is called by dlm_recoverd to process messages that were saved on
   the requestqueue. */

व्योम dlm_receive_message_saved(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms,
			       uपूर्णांक32_t saved_seq)
अणु
	_receive_message(ls, ms, saved_seq);
पूर्ण

/* This is called by the midcomms layer when something is received क्रम
   the lockspace.  It could be either a MSG (normal message sent as part of
   standard locking activity) or an RCOM (recovery message sent as part of
   lockspace recovery). */

व्योम dlm_receive_buffer(जोड़ dlm_packet *p, पूर्णांक nodeid)
अणु
	काष्ठा dlm_header *hd = &p->header;
	काष्ठा dlm_ls *ls;
	पूर्णांक type = 0;

	चयन (hd->h_cmd) अणु
	हाल DLM_MSG:
		dlm_message_in(&p->message);
		type = p->message.m_type;
		अवरोध;
	हाल DLM_RCOM:
		dlm_rcom_in(&p->rcom);
		type = p->rcom.rc_type;
		अवरोध;
	शेष:
		log_prपूर्णांक("invalid h_cmd %d from %u", hd->h_cmd, nodeid);
		वापस;
	पूर्ण

	अगर (hd->h_nodeid != nodeid) अणु
		log_prपूर्णांक("invalid h_nodeid %d from %d lockspace %x",
			  hd->h_nodeid, nodeid, hd->h_lockspace);
		वापस;
	पूर्ण

	ls = dlm_find_lockspace_global(hd->h_lockspace);
	अगर (!ls) अणु
		अगर (dlm_config.ci_log_debug) अणु
			prपूर्णांकk_ratelimited(KERN_DEBUG "dlm: invalid lockspace "
				"%u from %d cmd %d type %d\n",
				hd->h_lockspace, nodeid, hd->h_cmd, type);
		पूर्ण

		अगर (hd->h_cmd == DLM_RCOM && type == DLM_RCOM_STATUS)
			dlm_send_ls_not_पढ़ोy(nodeid, &p->rcom);
		वापस;
	पूर्ण

	/* this rwsem allows dlm_ls_stop() to रुको क्रम all dlm_recv thपढ़ोs to
	   be inactive (in this ls) beक्रमe transitioning to recovery mode */

	करोwn_पढ़ो(&ls->ls_recv_active);
	अगर (hd->h_cmd == DLM_MSG)
		dlm_receive_message(ls, &p->message, nodeid);
	अन्यथा
		dlm_receive_rcom(ls, &p->rcom, nodeid);
	up_पढ़ो(&ls->ls_recv_active);

	dlm_put_lockspace(ls);
पूर्ण

अटल व्योम recover_convert_रुकोer(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb,
				   काष्ठा dlm_message *ms_stub)
अणु
	अगर (middle_conversion(lkb)) अणु
		hold_lkb(lkb);
		स_रखो(ms_stub, 0, माप(काष्ठा dlm_message));
		ms_stub->m_flags = DLM_IFL_STUB_MS;
		ms_stub->m_type = DLM_MSG_CONVERT_REPLY;
		ms_stub->m_result = -EINPROGRESS;
		ms_stub->m_header.h_nodeid = lkb->lkb_nodeid;
		_receive_convert_reply(lkb, ms_stub);

		/* Same special हाल as in receive_rcom_lock_args() */
		lkb->lkb_grmode = DLM_LOCK_IV;
		rsb_set_flag(lkb->lkb_resource, RSB_RECOVER_CONVERT);
		unhold_lkb(lkb);

	पूर्ण अन्यथा अगर (lkb->lkb_rqmode >= lkb->lkb_grmode) अणु
		lkb->lkb_flags |= DLM_IFL_RESEND;
	पूर्ण

	/* lkb->lkb_rqmode < lkb->lkb_grmode shouldn't happen since करोwn
	   conversions are async; there's no reply from the remote master */
पूर्ण

/* A रुकोing lkb needs recovery अगर the master node has failed, or
   the master node is changing (only when no directory is used) */

अटल पूर्णांक रुकोer_needs_recovery(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb,
				 पूर्णांक dir_nodeid)
अणु
	अगर (dlm_no_directory(ls))
		वापस 1;

	अगर (dlm_is_हटाओd(ls, lkb->lkb_रुको_nodeid))
		वापस 1;

	वापस 0;
पूर्ण

/* Recovery क्रम locks that are रुकोing क्रम replies from nodes that are now
   gone.  We can just complete unlocks and cancels by faking a reply from the
   dead node.  Requests and up-conversions we flag to be resent after
   recovery.  Down-conversions can just be completed with a fake reply like
   unlocks.  Conversions between PR and CW need special attention. */

व्योम dlm_recover_रुकोers_pre(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_lkb *lkb, *safe;
	काष्ठा dlm_message *ms_stub;
	पूर्णांक रुको_type, stub_unlock_result, stub_cancel_result;
	पूर्णांक dir_nodeid;

	ms_stub = kदो_स्मृति(माप(*ms_stub), GFP_KERNEL);
	अगर (!ms_stub)
		वापस;

	mutex_lock(&ls->ls_रुकोers_mutex);

	list_क्रम_each_entry_safe(lkb, safe, &ls->ls_रुकोers, lkb_रुको_reply) अणु

		dir_nodeid = dlm_dir_nodeid(lkb->lkb_resource);

		/* exclude debug messages about unlocks because there can be so
		   many and they aren't very पूर्णांकeresting */

		अगर (lkb->lkb_रुको_type != DLM_MSG_UNLOCK) अणु
			log_debug(ls, "waiter %x remote %x msg %d r_nodeid %d "
				  "lkb_nodeid %d wait_nodeid %d dir_nodeid %d",
				  lkb->lkb_id,
				  lkb->lkb_remid,
				  lkb->lkb_रुको_type,
				  lkb->lkb_resource->res_nodeid,
				  lkb->lkb_nodeid,
				  lkb->lkb_रुको_nodeid,
				  dir_nodeid);
		पूर्ण

		/* all outstanding lookups, regardless of destination  will be
		   resent after recovery is करोne */

		अगर (lkb->lkb_रुको_type == DLM_MSG_LOOKUP) अणु
			lkb->lkb_flags |= DLM_IFL_RESEND;
			जारी;
		पूर्ण

		अगर (!रुकोer_needs_recovery(ls, lkb, dir_nodeid))
			जारी;

		रुको_type = lkb->lkb_रुको_type;
		stub_unlock_result = -DLM_EUNLOCK;
		stub_cancel_result = -DLM_ECANCEL;

		/* Main reply may have been received leaving a zero रुको_type,
		   but a reply क्रम the overlapping op may not have been
		   received.  In that हाल we need to fake the appropriate
		   reply क्रम the overlap op. */

		अगर (!रुको_type) अणु
			अगर (is_overlap_cancel(lkb)) अणु
				रुको_type = DLM_MSG_CANCEL;
				अगर (lkb->lkb_grmode == DLM_LOCK_IV)
					stub_cancel_result = 0;
			पूर्ण
			अगर (is_overlap_unlock(lkb)) अणु
				रुको_type = DLM_MSG_UNLOCK;
				अगर (lkb->lkb_grmode == DLM_LOCK_IV)
					stub_unlock_result = -ENOENT;
			पूर्ण

			log_debug(ls, "rwpre overlap %x %x %d %d %d",
				  lkb->lkb_id, lkb->lkb_flags, रुको_type,
				  stub_cancel_result, stub_unlock_result);
		पूर्ण

		चयन (रुको_type) अणु

		हाल DLM_MSG_REQUEST:
			lkb->lkb_flags |= DLM_IFL_RESEND;
			अवरोध;

		हाल DLM_MSG_CONVERT:
			recover_convert_रुकोer(ls, lkb, ms_stub);
			अवरोध;

		हाल DLM_MSG_UNLOCK:
			hold_lkb(lkb);
			स_रखो(ms_stub, 0, माप(काष्ठा dlm_message));
			ms_stub->m_flags = DLM_IFL_STUB_MS;
			ms_stub->m_type = DLM_MSG_UNLOCK_REPLY;
			ms_stub->m_result = stub_unlock_result;
			ms_stub->m_header.h_nodeid = lkb->lkb_nodeid;
			_receive_unlock_reply(lkb, ms_stub);
			dlm_put_lkb(lkb);
			अवरोध;

		हाल DLM_MSG_CANCEL:
			hold_lkb(lkb);
			स_रखो(ms_stub, 0, माप(काष्ठा dlm_message));
			ms_stub->m_flags = DLM_IFL_STUB_MS;
			ms_stub->m_type = DLM_MSG_CANCEL_REPLY;
			ms_stub->m_result = stub_cancel_result;
			ms_stub->m_header.h_nodeid = lkb->lkb_nodeid;
			_receive_cancel_reply(lkb, ms_stub);
			dlm_put_lkb(lkb);
			अवरोध;

		शेष:
			log_error(ls, "invalid lkb wait_type %d %d",
				  lkb->lkb_रुको_type, रुको_type);
		पूर्ण
		schedule();
	पूर्ण
	mutex_unlock(&ls->ls_रुकोers_mutex);
	kमुक्त(ms_stub);
पूर्ण

अटल काष्ठा dlm_lkb *find_resend_रुकोer(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_lkb *lkb;
	पूर्णांक found = 0;

	mutex_lock(&ls->ls_रुकोers_mutex);
	list_क्रम_each_entry(lkb, &ls->ls_रुकोers, lkb_रुको_reply) अणु
		अगर (lkb->lkb_flags & DLM_IFL_RESEND) अणु
			hold_lkb(lkb);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ls->ls_रुकोers_mutex);

	अगर (!found)
		lkb = शून्य;
	वापस lkb;
पूर्ण

/* Deal with lookups and lkb's marked RESEND from _pre.  We may now be the
   master or dir-node क्रम r.  Processing the lkb may result in it being placed
   back on रुकोers. */

/* We करो this after normal locking has been enabled and any saved messages
   (in requestqueue) have been processed.  We should be confident that at
   this poपूर्णांक we won't get or process a reply to any of these रुकोing
   operations.  But, new ops may be coming in on the rsbs/locks here from
   userspace or remotely. */

/* there may have been an overlap unlock/cancel prior to recovery or after
   recovery.  अगर beक्रमe, the lkb may still have a pos रुको_count; अगर after, the
   overlap flag would just have been set and nothing new sent.  we can be
   confident here than any replies to either the initial op or overlap ops
   prior to recovery have been received. */

पूर्णांक dlm_recover_रुकोers_post(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_rsb *r;
	पूर्णांक error = 0, mstype, err, oc, ou;

	जबतक (1) अणु
		अगर (dlm_locking_stopped(ls)) अणु
			log_debug(ls, "recover_waiters_post aborted");
			error = -EINTR;
			अवरोध;
		पूर्ण

		lkb = find_resend_रुकोer(ls);
		अगर (!lkb)
			अवरोध;

		r = lkb->lkb_resource;
		hold_rsb(r);
		lock_rsb(r);

		mstype = lkb->lkb_रुको_type;
		oc = is_overlap_cancel(lkb);
		ou = is_overlap_unlock(lkb);
		err = 0;

		log_debug(ls, "waiter %x remote %x msg %d r_nodeid %d "
			  "lkb_nodeid %d wait_nodeid %d dir_nodeid %d "
			  "overlap %d %d", lkb->lkb_id, lkb->lkb_remid, mstype,
			  r->res_nodeid, lkb->lkb_nodeid, lkb->lkb_रुको_nodeid,
			  dlm_dir_nodeid(r), oc, ou);

		/* At this poपूर्णांक we assume that we won't get a reply to any
		   previous op or overlap op on this lock.  First, करो a big
		   हटाओ_from_रुकोers() क्रम all previous ops. */

		lkb->lkb_flags &= ~DLM_IFL_RESEND;
		lkb->lkb_flags &= ~DLM_IFL_OVERLAP_UNLOCK;
		lkb->lkb_flags &= ~DLM_IFL_OVERLAP_CANCEL;
		lkb->lkb_रुको_type = 0;
		lkb->lkb_रुको_count = 0;
		mutex_lock(&ls->ls_रुकोers_mutex);
		list_del_init(&lkb->lkb_रुको_reply);
		mutex_unlock(&ls->ls_रुकोers_mutex);
		unhold_lkb(lkb); /* क्रम रुकोers list */

		अगर (oc || ou) अणु
			/* करो an unlock or cancel instead of resending */
			चयन (mstype) अणु
			हाल DLM_MSG_LOOKUP:
			हाल DLM_MSG_REQUEST:
				queue_cast(r, lkb, ou ? -DLM_EUNLOCK :
							-DLM_ECANCEL);
				unhold_lkb(lkb); /* unकरोes create_lkb() */
				अवरोध;
			हाल DLM_MSG_CONVERT:
				अगर (oc) अणु
					queue_cast(r, lkb, -DLM_ECANCEL);
				पूर्ण अन्यथा अणु
					lkb->lkb_exflags |= DLM_LKF_FORCEUNLOCK;
					_unlock_lock(r, lkb);
				पूर्ण
				अवरोध;
			शेष:
				err = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (mstype) अणु
			हाल DLM_MSG_LOOKUP:
			हाल DLM_MSG_REQUEST:
				_request_lock(r, lkb);
				अगर (is_master(r))
					confirm_master(r, 0);
				अवरोध;
			हाल DLM_MSG_CONVERT:
				_convert_lock(r, lkb);
				अवरोध;
			शेष:
				err = 1;
			पूर्ण
		पूर्ण

		अगर (err) अणु
			log_error(ls, "waiter %x msg %d r_nodeid %d "
				  "dir_nodeid %d overlap %d %d",
				  lkb->lkb_id, mstype, r->res_nodeid,
				  dlm_dir_nodeid(r), oc, ou);
		पूर्ण
		unlock_rsb(r);
		put_rsb(r);
		dlm_put_lkb(lkb);
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम purge_mstcpy_list(काष्ठा dlm_ls *ls, काष्ठा dlm_rsb *r,
			      काष्ठा list_head *list)
अणु
	काष्ठा dlm_lkb *lkb, *safe;

	list_क्रम_each_entry_safe(lkb, safe, list, lkb_statequeue) अणु
		अगर (!is_master_copy(lkb))
			जारी;

		/* करोn't purge lkbs we've added in recover_master_copy क्रम
		   the current recovery seq */

		अगर (lkb->lkb_recover_seq == ls->ls_recover_seq)
			जारी;

		del_lkb(r, lkb);

		/* this put should मुक्त the lkb */
		अगर (!dlm_put_lkb(lkb))
			log_error(ls, "purged mstcpy lkb not released");
	पूर्ण
पूर्ण

व्योम dlm_purge_mstcpy_locks(काष्ठा dlm_rsb *r)
अणु
	काष्ठा dlm_ls *ls = r->res_ls;

	purge_mstcpy_list(ls, r, &r->res_grantqueue);
	purge_mstcpy_list(ls, r, &r->res_convertqueue);
	purge_mstcpy_list(ls, r, &r->res_रुकोqueue);
पूर्ण

अटल व्योम purge_dead_list(काष्ठा dlm_ls *ls, काष्ठा dlm_rsb *r,
			    काष्ठा list_head *list,
			    पूर्णांक nodeid_gone, अचिन्हित पूर्णांक *count)
अणु
	काष्ठा dlm_lkb *lkb, *safe;

	list_क्रम_each_entry_safe(lkb, safe, list, lkb_statequeue) अणु
		अगर (!is_master_copy(lkb))
			जारी;

		अगर ((lkb->lkb_nodeid == nodeid_gone) ||
		    dlm_is_हटाओd(ls, lkb->lkb_nodeid)) अणु

			/* tell recover_lvb to invalidate the lvb
			   because a node holding EX/PW failed */
			अगर ((lkb->lkb_exflags & DLM_LKF_VALBLK) &&
			    (lkb->lkb_grmode >= DLM_LOCK_PW)) अणु
				rsb_set_flag(r, RSB_RECOVER_LVB_INVAL);
			पूर्ण

			del_lkb(r, lkb);

			/* this put should मुक्त the lkb */
			अगर (!dlm_put_lkb(lkb))
				log_error(ls, "purged dead lkb not released");

			rsb_set_flag(r, RSB_RECOVER_GRANT);

			(*count)++;
		पूर्ण
	पूर्ण
पूर्ण

/* Get rid of locks held by nodes that are gone. */

व्योम dlm_recover_purge(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_rsb *r;
	काष्ठा dlm_member *memb;
	पूर्णांक nodes_count = 0;
	पूर्णांक nodeid_gone = 0;
	अचिन्हित पूर्णांक lkb_count = 0;

	/* cache one हटाओd nodeid to optimize the common
	   हाल of a single node हटाओd */

	list_क्रम_each_entry(memb, &ls->ls_nodes_gone, list) अणु
		nodes_count++;
		nodeid_gone = memb->nodeid;
	पूर्ण

	अगर (!nodes_count)
		वापस;

	करोwn_ग_लिखो(&ls->ls_root_sem);
	list_क्रम_each_entry(r, &ls->ls_root_list, res_root_list) अणु
		hold_rsb(r);
		lock_rsb(r);
		अगर (is_master(r)) अणु
			purge_dead_list(ls, r, &r->res_grantqueue,
					nodeid_gone, &lkb_count);
			purge_dead_list(ls, r, &r->res_convertqueue,
					nodeid_gone, &lkb_count);
			purge_dead_list(ls, r, &r->res_रुकोqueue,
					nodeid_gone, &lkb_count);
		पूर्ण
		unlock_rsb(r);
		unhold_rsb(r);
		cond_resched();
	पूर्ण
	up_ग_लिखो(&ls->ls_root_sem);

	अगर (lkb_count)
		log_rinfo(ls, "dlm_recover_purge %u locks for %u nodes",
			  lkb_count, nodes_count);
पूर्ण

अटल काष्ठा dlm_rsb *find_grant_rsb(काष्ठा dlm_ls *ls, पूर्णांक bucket)
अणु
	काष्ठा rb_node *n;
	काष्ठा dlm_rsb *r;

	spin_lock(&ls->ls_rsbtbl[bucket].lock);
	क्रम (n = rb_first(&ls->ls_rsbtbl[bucket].keep); n; n = rb_next(n)) अणु
		r = rb_entry(n, काष्ठा dlm_rsb, res_hashnode);

		अगर (!rsb_flag(r, RSB_RECOVER_GRANT))
			जारी;
		अगर (!is_master(r)) अणु
			rsb_clear_flag(r, RSB_RECOVER_GRANT);
			जारी;
		पूर्ण
		hold_rsb(r);
		spin_unlock(&ls->ls_rsbtbl[bucket].lock);
		वापस r;
	पूर्ण
	spin_unlock(&ls->ls_rsbtbl[bucket].lock);
	वापस शून्य;
पूर्ण

/*
 * Attempt to grant locks on resources that we are the master of.
 * Locks may have become grantable during recovery because locks
 * from departed nodes have been purged (or not rebuilt), allowing
 * previously blocked locks to now be granted.  The subset of rsb's
 * we are पूर्णांकerested in are those with lkb's on either the convert or
 * रुकोing queues.
 *
 * Simplest would be to go through each master rsb and check क्रम non-empty
 * convert or रुकोing queues, and attempt to grant on those rsbs.
 * Checking the queues requires lock_rsb, though, क्रम which we'd need
 * to release the rsbtbl lock.  This would make iterating through all
 * rsb's very inefficient.  So, we rely on earlier recovery routines
 * to set RECOVER_GRANT on any rsb's that we should attempt to grant
 * locks क्रम.
 */

व्योम dlm_recover_grant(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_rsb *r;
	पूर्णांक bucket = 0;
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित पूर्णांक rsb_count = 0;
	अचिन्हित पूर्णांक lkb_count = 0;

	जबतक (1) अणु
		r = find_grant_rsb(ls, bucket);
		अगर (!r) अणु
			अगर (bucket == ls->ls_rsbtbl_size - 1)
				अवरोध;
			bucket++;
			जारी;
		पूर्ण
		rsb_count++;
		count = 0;
		lock_rsb(r);
		/* the RECOVER_GRANT flag is checked in the grant path */
		grant_pending_locks(r, &count);
		rsb_clear_flag(r, RSB_RECOVER_GRANT);
		lkb_count += count;
		confirm_master(r, 0);
		unlock_rsb(r);
		put_rsb(r);
		cond_resched();
	पूर्ण

	अगर (lkb_count)
		log_rinfo(ls, "dlm_recover_grant %u locks on %u resources",
			  lkb_count, rsb_count);
पूर्ण

अटल काष्ठा dlm_lkb *search_remid_list(काष्ठा list_head *head, पूर्णांक nodeid,
					 uपूर्णांक32_t remid)
अणु
	काष्ठा dlm_lkb *lkb;

	list_क्रम_each_entry(lkb, head, lkb_statequeue) अणु
		अगर (lkb->lkb_nodeid == nodeid && lkb->lkb_remid == remid)
			वापस lkb;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा dlm_lkb *search_remid(काष्ठा dlm_rsb *r, पूर्णांक nodeid,
				    uपूर्णांक32_t remid)
अणु
	काष्ठा dlm_lkb *lkb;

	lkb = search_remid_list(&r->res_grantqueue, nodeid, remid);
	अगर (lkb)
		वापस lkb;
	lkb = search_remid_list(&r->res_convertqueue, nodeid, remid);
	अगर (lkb)
		वापस lkb;
	lkb = search_remid_list(&r->res_रुकोqueue, nodeid, remid);
	अगर (lkb)
		वापस lkb;
	वापस शून्य;
पूर्ण

/* needs at least dlm_rcom + rcom_lock */
अटल पूर्णांक receive_rcom_lock_args(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb,
				  काष्ठा dlm_rsb *r, काष्ठा dlm_rcom *rc)
अणु
	काष्ठा rcom_lock *rl = (काष्ठा rcom_lock *) rc->rc_buf;

	lkb->lkb_nodeid = rc->rc_header.h_nodeid;
	lkb->lkb_ownpid = le32_to_cpu(rl->rl_ownpid);
	lkb->lkb_remid = le32_to_cpu(rl->rl_lkid);
	lkb->lkb_exflags = le32_to_cpu(rl->rl_exflags);
	lkb->lkb_flags = le32_to_cpu(rl->rl_flags) & 0x0000FFFF;
	lkb->lkb_flags |= DLM_IFL_MSTCPY;
	lkb->lkb_lvbseq = le32_to_cpu(rl->rl_lvbseq);
	lkb->lkb_rqmode = rl->rl_rqmode;
	lkb->lkb_grmode = rl->rl_grmode;
	/* करोn't set lkb_status because add_lkb wants to itself */

	lkb->lkb_bastfn = (rl->rl_asts & DLM_CB_BAST) ? &fake_bastfn : शून्य;
	lkb->lkb_astfn = (rl->rl_asts & DLM_CB_CAST) ? &fake_astfn : शून्य;

	अगर (lkb->lkb_exflags & DLM_LKF_VALBLK) अणु
		पूर्णांक lvblen = rc->rc_header.h_length - माप(काष्ठा dlm_rcom) -
			 माप(काष्ठा rcom_lock);
		अगर (lvblen > ls->ls_lvblen)
			वापस -EINVAL;
		lkb->lkb_lvbptr = dlm_allocate_lvb(ls);
		अगर (!lkb->lkb_lvbptr)
			वापस -ENOMEM;
		स_नकल(lkb->lkb_lvbptr, rl->rl_lvb, lvblen);
	पूर्ण

	/* Conversions between PR and CW (middle modes) need special handling.
	   The real granted mode of these converting locks cannot be determined
	   until all locks have been rebuilt on the rsb (recover_conversion) */

	अगर (rl->rl_रुको_type == cpu_to_le16(DLM_MSG_CONVERT) &&
	    middle_conversion(lkb)) अणु
		rl->rl_status = DLM_LKSTS_CONVERT;
		lkb->lkb_grmode = DLM_LOCK_IV;
		rsb_set_flag(r, RSB_RECOVER_CONVERT);
	पूर्ण

	वापस 0;
पूर्ण

/* This lkb may have been recovered in a previous पातed recovery so we need
   to check अगर the rsb alपढ़ोy has an lkb with the given remote nodeid/lkid.
   If so we just send back a standard reply.  If not, we create a new lkb with
   the given values and send back our lkid.  We send back our lkid by sending
   back the rcom_lock काष्ठा we got but with the remid field filled in. */

/* needs at least dlm_rcom + rcom_lock */
पूर्णांक dlm_recover_master_copy(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc)
अणु
	काष्ठा rcom_lock *rl = (काष्ठा rcom_lock *) rc->rc_buf;
	काष्ठा dlm_rsb *r;
	काष्ठा dlm_lkb *lkb;
	uपूर्णांक32_t remid = 0;
	पूर्णांक from_nodeid = rc->rc_header.h_nodeid;
	पूर्णांक error;

	अगर (rl->rl_parent_lkid) अणु
		error = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	remid = le32_to_cpu(rl->rl_lkid);

	/* In general we expect the rsb वापसed to be R_MASTER, but we करोn't
	   have to require it.  Recovery of masters on one node can overlap
	   recovery of locks on another node, so one node can send us MSTCPY
	   locks beक्रमe we've made ourselves master of this rsb.  We can still
	   add new MSTCPY locks that we receive here without any harm; when
	   we make ourselves master, dlm_recover_masters() won't touch the
	   MSTCPY locks we've received early. */

	error = find_rsb(ls, rl->rl_name, le16_to_cpu(rl->rl_namelen),
			 from_nodeid, R_RECEIVE_RECOVER, &r);
	अगर (error)
		जाओ out;

	lock_rsb(r);

	अगर (dlm_no_directory(ls) && (dlm_dir_nodeid(r) != dlm_our_nodeid())) अणु
		log_error(ls, "dlm_recover_master_copy remote %d %x not dir",
			  from_nodeid, remid);
		error = -EBADR;
		जाओ out_unlock;
	पूर्ण

	lkb = search_remid(r, from_nodeid, remid);
	अगर (lkb) अणु
		error = -EEXIST;
		जाओ out_remid;
	पूर्ण

	error = create_lkb(ls, &lkb);
	अगर (error)
		जाओ out_unlock;

	error = receive_rcom_lock_args(ls, lkb, r, rc);
	अगर (error) अणु
		__put_lkb(ls, lkb);
		जाओ out_unlock;
	पूर्ण

	attach_lkb(r, lkb);
	add_lkb(r, lkb, rl->rl_status);
	error = 0;
	ls->ls_recover_locks_in++;

	अगर (!list_empty(&r->res_रुकोqueue) || !list_empty(&r->res_convertqueue))
		rsb_set_flag(r, RSB_RECOVER_GRANT);

 out_remid:
	/* this is the new value वापसed to the lock holder क्रम
	   saving in its process-copy lkb */
	rl->rl_remid = cpu_to_le32(lkb->lkb_id);

	lkb->lkb_recover_seq = ls->ls_recover_seq;

 out_unlock:
	unlock_rsb(r);
	put_rsb(r);
 out:
	अगर (error && error != -EEXIST)
		log_rinfo(ls, "dlm_recover_master_copy remote %d %x error %d",
			  from_nodeid, remid, error);
	rl->rl_result = cpu_to_le32(error);
	वापस error;
पूर्ण

/* needs at least dlm_rcom + rcom_lock */
पूर्णांक dlm_recover_process_copy(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc)
अणु
	काष्ठा rcom_lock *rl = (काष्ठा rcom_lock *) rc->rc_buf;
	काष्ठा dlm_rsb *r;
	काष्ठा dlm_lkb *lkb;
	uपूर्णांक32_t lkid, remid;
	पूर्णांक error, result;

	lkid = le32_to_cpu(rl->rl_lkid);
	remid = le32_to_cpu(rl->rl_remid);
	result = le32_to_cpu(rl->rl_result);

	error = find_lkb(ls, lkid, &lkb);
	अगर (error) अणु
		log_error(ls, "dlm_recover_process_copy no %x remote %d %x %d",
			  lkid, rc->rc_header.h_nodeid, remid, result);
		वापस error;
	पूर्ण

	r = lkb->lkb_resource;
	hold_rsb(r);
	lock_rsb(r);

	अगर (!is_process_copy(lkb)) अणु
		log_error(ls, "dlm_recover_process_copy bad %x remote %d %x %d",
			  lkid, rc->rc_header.h_nodeid, remid, result);
		dlm_dump_rsb(r);
		unlock_rsb(r);
		put_rsb(r);
		dlm_put_lkb(lkb);
		वापस -EINVAL;
	पूर्ण

	चयन (result) अणु
	हाल -EBADR:
		/* There's a chance the new master received our lock beक्रमe
		   dlm_recover_master_reply(), this wouldn't happen अगर we did
		   a barrier between recover_masters and recover_locks. */

		log_debug(ls, "dlm_recover_process_copy %x remote %d %x %d",
			  lkid, rc->rc_header.h_nodeid, remid, result);
	
		dlm_send_rcom_lock(r, lkb);
		जाओ out;
	हाल -EEXIST:
	हाल 0:
		lkb->lkb_remid = remid;
		अवरोध;
	शेष:
		log_error(ls, "dlm_recover_process_copy %x remote %d %x %d unk",
			  lkid, rc->rc_header.h_nodeid, remid, result);
	पूर्ण

	/* an ack क्रम dlm_recover_locks() which रुकोs क्रम replies from
	   all the locks it sends to new masters */
	dlm_recovered_lock(r);
 out:
	unlock_rsb(r);
	put_rsb(r);
	dlm_put_lkb(lkb);

	वापस 0;
पूर्ण

पूर्णांक dlm_user_request(काष्ठा dlm_ls *ls, काष्ठा dlm_user_args *ua,
		     पूर्णांक mode, uपूर्णांक32_t flags, व्योम *name, अचिन्हित पूर्णांक namelen,
		     अचिन्हित दीर्घ समयout_cs)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_args args;
	पूर्णांक error;

	dlm_lock_recovery(ls);

	error = create_lkb(ls, &lkb);
	अगर (error) अणु
		kमुक्त(ua);
		जाओ out;
	पूर्ण

	अगर (flags & DLM_LKF_VALBLK) अणु
		ua->lksb.sb_lvbptr = kzalloc(DLM_USER_LVB_LEN, GFP_NOFS);
		अगर (!ua->lksb.sb_lvbptr) अणु
			kमुक्त(ua);
			__put_lkb(ls, lkb);
			error = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण
	error = set_lock_args(mode, &ua->lksb, flags, namelen, समयout_cs,
			      fake_astfn, ua, fake_bastfn, &args);
	अगर (error) अणु
		kमुक्त(ua->lksb.sb_lvbptr);
		ua->lksb.sb_lvbptr = शून्य;
		kमुक्त(ua);
		__put_lkb(ls, lkb);
		जाओ out;
	पूर्ण

	/* After ua is attached to lkb it will be मुक्तd by dlm_मुक्त_lkb().
	   When DLM_IFL_USER is set, the dlm knows that this is a userspace
	   lock and that lkb_astparam is the dlm_user_args काष्ठाure. */
	lkb->lkb_flags |= DLM_IFL_USER;
	error = request_lock(ls, lkb, name, namelen, &args);

	चयन (error) अणु
	हाल 0:
		अवरोध;
	हाल -EINPROGRESS:
		error = 0;
		अवरोध;
	हाल -EAGAIN:
		error = 0;
		fallthrough;
	शेष:
		__put_lkb(ls, lkb);
		जाओ out;
	पूर्ण

	/* add this new lkb to the per-process list of locks */
	spin_lock(&ua->proc->locks_spin);
	hold_lkb(lkb);
	list_add_tail(&lkb->lkb_ownqueue, &ua->proc->locks);
	spin_unlock(&ua->proc->locks_spin);
 out:
	dlm_unlock_recovery(ls);
	वापस error;
पूर्ण

पूर्णांक dlm_user_convert(काष्ठा dlm_ls *ls, काष्ठा dlm_user_args *ua_पंचांगp,
		     पूर्णांक mode, uपूर्णांक32_t flags, uपूर्णांक32_t lkid, अक्षर *lvb_in,
		     अचिन्हित दीर्घ समयout_cs)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_args args;
	काष्ठा dlm_user_args *ua;
	पूर्णांक error;

	dlm_lock_recovery(ls);

	error = find_lkb(ls, lkid, &lkb);
	अगर (error)
		जाओ out;

	/* user can change the params on its lock when it converts it, or
	   add an lvb that didn't exist beक्रमe */

	ua = lkb->lkb_ua;

	अगर (flags & DLM_LKF_VALBLK && !ua->lksb.sb_lvbptr) अणु
		ua->lksb.sb_lvbptr = kzalloc(DLM_USER_LVB_LEN, GFP_NOFS);
		अगर (!ua->lksb.sb_lvbptr) अणु
			error = -ENOMEM;
			जाओ out_put;
		पूर्ण
	पूर्ण
	अगर (lvb_in && ua->lksb.sb_lvbptr)
		स_नकल(ua->lksb.sb_lvbptr, lvb_in, DLM_USER_LVB_LEN);

	ua->xid = ua_पंचांगp->xid;
	ua->castparam = ua_पंचांगp->castparam;
	ua->castaddr = ua_पंचांगp->castaddr;
	ua->bastparam = ua_पंचांगp->bastparam;
	ua->bastaddr = ua_पंचांगp->bastaddr;
	ua->user_lksb = ua_पंचांगp->user_lksb;

	error = set_lock_args(mode, &ua->lksb, flags, 0, समयout_cs,
			      fake_astfn, ua, fake_bastfn, &args);
	अगर (error)
		जाओ out_put;

	error = convert_lock(ls, lkb, &args);

	अगर (error == -EINPROGRESS || error == -EAGAIN || error == -EDEADLK)
		error = 0;
 out_put:
	dlm_put_lkb(lkb);
 out:
	dlm_unlock_recovery(ls);
	kमुक्त(ua_पंचांगp);
	वापस error;
पूर्ण

/*
 * The caller asks क्रम an orphan lock on a given resource with a given mode.
 * If a matching lock exists, it's moved to the owner's list of locks and
 * the lkid is वापसed.
 */

पूर्णांक dlm_user_aकरोpt_orphan(काष्ठा dlm_ls *ls, काष्ठा dlm_user_args *ua_पंचांगp,
		     पूर्णांक mode, uपूर्णांक32_t flags, व्योम *name, अचिन्हित पूर्णांक namelen,
		     अचिन्हित दीर्घ समयout_cs, uपूर्णांक32_t *lkid)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_user_args *ua;
	पूर्णांक found_other_mode = 0;
	पूर्णांक found = 0;
	पूर्णांक rv = 0;

	mutex_lock(&ls->ls_orphans_mutex);
	list_क्रम_each_entry(lkb, &ls->ls_orphans, lkb_ownqueue) अणु
		अगर (lkb->lkb_resource->res_length != namelen)
			जारी;
		अगर (स_भेद(lkb->lkb_resource->res_name, name, namelen))
			जारी;
		अगर (lkb->lkb_grmode != mode) अणु
			found_other_mode = 1;
			जारी;
		पूर्ण

		found = 1;
		list_del_init(&lkb->lkb_ownqueue);
		lkb->lkb_flags &= ~DLM_IFL_ORPHAN;
		*lkid = lkb->lkb_id;
		अवरोध;
	पूर्ण
	mutex_unlock(&ls->ls_orphans_mutex);

	अगर (!found && found_other_mode) अणु
		rv = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (!found) अणु
		rv = -ENOENT;
		जाओ out;
	पूर्ण

	lkb->lkb_exflags = flags;
	lkb->lkb_ownpid = (पूर्णांक) current->pid;

	ua = lkb->lkb_ua;

	ua->proc = ua_पंचांगp->proc;
	ua->xid = ua_पंचांगp->xid;
	ua->castparam = ua_पंचांगp->castparam;
	ua->castaddr = ua_पंचांगp->castaddr;
	ua->bastparam = ua_पंचांगp->bastparam;
	ua->bastaddr = ua_पंचांगp->bastaddr;
	ua->user_lksb = ua_पंचांगp->user_lksb;

	/*
	 * The lkb reference from the ls_orphans list was not
	 * हटाओd above, and is now considered the reference
	 * क्रम the proc locks list.
	 */

	spin_lock(&ua->proc->locks_spin);
	list_add_tail(&lkb->lkb_ownqueue, &ua->proc->locks);
	spin_unlock(&ua->proc->locks_spin);
 out:
	kमुक्त(ua_पंचांगp);
	वापस rv;
पूर्ण

पूर्णांक dlm_user_unlock(काष्ठा dlm_ls *ls, काष्ठा dlm_user_args *ua_पंचांगp,
		    uपूर्णांक32_t flags, uपूर्णांक32_t lkid, अक्षर *lvb_in)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_args args;
	काष्ठा dlm_user_args *ua;
	पूर्णांक error;

	dlm_lock_recovery(ls);

	error = find_lkb(ls, lkid, &lkb);
	अगर (error)
		जाओ out;

	ua = lkb->lkb_ua;

	अगर (lvb_in && ua->lksb.sb_lvbptr)
		स_नकल(ua->lksb.sb_lvbptr, lvb_in, DLM_USER_LVB_LEN);
	अगर (ua_पंचांगp->castparam)
		ua->castparam = ua_पंचांगp->castparam;
	ua->user_lksb = ua_पंचांगp->user_lksb;

	error = set_unlock_args(flags, ua, &args);
	अगर (error)
		जाओ out_put;

	error = unlock_lock(ls, lkb, &args);

	अगर (error == -DLM_EUNLOCK)
		error = 0;
	/* from validate_unlock_args() */
	अगर (error == -EBUSY && (flags & DLM_LKF_FORCEUNLOCK))
		error = 0;
	अगर (error)
		जाओ out_put;

	spin_lock(&ua->proc->locks_spin);
	/* dlm_user_add_cb() may have alपढ़ोy taken lkb off the proc list */
	अगर (!list_empty(&lkb->lkb_ownqueue))
		list_move(&lkb->lkb_ownqueue, &ua->proc->unlocking);
	spin_unlock(&ua->proc->locks_spin);
 out_put:
	dlm_put_lkb(lkb);
 out:
	dlm_unlock_recovery(ls);
	kमुक्त(ua_पंचांगp);
	वापस error;
पूर्ण

पूर्णांक dlm_user_cancel(काष्ठा dlm_ls *ls, काष्ठा dlm_user_args *ua_पंचांगp,
		    uपूर्णांक32_t flags, uपूर्णांक32_t lkid)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_args args;
	काष्ठा dlm_user_args *ua;
	पूर्णांक error;

	dlm_lock_recovery(ls);

	error = find_lkb(ls, lkid, &lkb);
	अगर (error)
		जाओ out;

	ua = lkb->lkb_ua;
	अगर (ua_पंचांगp->castparam)
		ua->castparam = ua_पंचांगp->castparam;
	ua->user_lksb = ua_पंचांगp->user_lksb;

	error = set_unlock_args(flags, ua, &args);
	अगर (error)
		जाओ out_put;

	error = cancel_lock(ls, lkb, &args);

	अगर (error == -DLM_ECANCEL)
		error = 0;
	/* from validate_unlock_args() */
	अगर (error == -EBUSY)
		error = 0;
 out_put:
	dlm_put_lkb(lkb);
 out:
	dlm_unlock_recovery(ls);
	kमुक्त(ua_पंचांगp);
	वापस error;
पूर्ण

पूर्णांक dlm_user_deadlock(काष्ठा dlm_ls *ls, uपूर्णांक32_t flags, uपूर्णांक32_t lkid)
अणु
	काष्ठा dlm_lkb *lkb;
	काष्ठा dlm_args args;
	काष्ठा dlm_user_args *ua;
	काष्ठा dlm_rsb *r;
	पूर्णांक error;

	dlm_lock_recovery(ls);

	error = find_lkb(ls, lkid, &lkb);
	अगर (error)
		जाओ out;

	ua = lkb->lkb_ua;

	error = set_unlock_args(flags, ua, &args);
	अगर (error)
		जाओ out_put;

	/* same as cancel_lock(), but set DEADLOCK_CANCEL after lock_rsb */

	r = lkb->lkb_resource;
	hold_rsb(r);
	lock_rsb(r);

	error = validate_unlock_args(lkb, &args);
	अगर (error)
		जाओ out_r;
	lkb->lkb_flags |= DLM_IFL_DEADLOCK_CANCEL;

	error = _cancel_lock(r, lkb);
 out_r:
	unlock_rsb(r);
	put_rsb(r);

	अगर (error == -DLM_ECANCEL)
		error = 0;
	/* from validate_unlock_args() */
	अगर (error == -EBUSY)
		error = 0;
 out_put:
	dlm_put_lkb(lkb);
 out:
	dlm_unlock_recovery(ls);
	वापस error;
पूर्ण

/* lkb's that are हटाओd from the रुकोers list by revert are just left on the
   orphans list with the granted orphan locks, to be मुक्तd by purge */

अटल पूर्णांक orphan_proc_lock(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb)
अणु
	काष्ठा dlm_args args;
	पूर्णांक error;

	hold_lkb(lkb); /* reference क्रम the ls_orphans list */
	mutex_lock(&ls->ls_orphans_mutex);
	list_add_tail(&lkb->lkb_ownqueue, &ls->ls_orphans);
	mutex_unlock(&ls->ls_orphans_mutex);

	set_unlock_args(0, lkb->lkb_ua, &args);

	error = cancel_lock(ls, lkb, &args);
	अगर (error == -DLM_ECANCEL)
		error = 0;
	वापस error;
पूर्ण

/* The FORCEUNLOCK flag allows the unlock to go ahead even अगर the lkb isn't
   granted.  Regardless of what rsb queue the lock is on, it's हटाओd and
   मुक्तd.  The IVVALBLK flag causes the lvb on the resource to be invalidated
   अगर our lock is PW/EX (it's ignored अगर our granted mode is smaller.) */

अटल पूर्णांक unlock_proc_lock(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb)
अणु
	काष्ठा dlm_args args;
	पूर्णांक error;

	set_unlock_args(DLM_LKF_FORCEUNLOCK | DLM_LKF_IVVALBLK,
			lkb->lkb_ua, &args);

	error = unlock_lock(ls, lkb, &args);
	अगर (error == -DLM_EUNLOCK)
		error = 0;
	वापस error;
पूर्ण

/* We have to release clear_proc_locks mutex beक्रमe calling unlock_proc_lock()
   (which करोes lock_rsb) due to deadlock with receiving a message that करोes
   lock_rsb followed by dlm_user_add_cb() */

अटल काष्ठा dlm_lkb *del_proc_lock(काष्ठा dlm_ls *ls,
				     काष्ठा dlm_user_proc *proc)
अणु
	काष्ठा dlm_lkb *lkb = शून्य;

	mutex_lock(&ls->ls_clear_proc_locks);
	अगर (list_empty(&proc->locks))
		जाओ out;

	lkb = list_entry(proc->locks.next, काष्ठा dlm_lkb, lkb_ownqueue);
	list_del_init(&lkb->lkb_ownqueue);

	अगर (lkb->lkb_exflags & DLM_LKF_PERSISTENT)
		lkb->lkb_flags |= DLM_IFL_ORPHAN;
	अन्यथा
		lkb->lkb_flags |= DLM_IFL_DEAD;
 out:
	mutex_unlock(&ls->ls_clear_proc_locks);
	वापस lkb;
पूर्ण

/* The ls_clear_proc_locks mutex protects against dlm_user_add_cb() which
   1) references lkb->ua which we मुक्त here and 2) adds lkbs to proc->asts,
   which we clear here. */

/* proc CLOSING flag is set so no more device_पढ़ोs should look at proc->asts
   list, and no more device_ग_लिखोs should add lkb's to proc->locks list; so we
   shouldn't need to take asts_spin or locks_spin here.  this assumes that
   device पढ़ोs/ग_लिखोs/बंदs are serialized -- FIXME: we may need to serialize
   them ourself. */

व्योम dlm_clear_proc_locks(काष्ठा dlm_ls *ls, काष्ठा dlm_user_proc *proc)
अणु
	काष्ठा dlm_lkb *lkb, *safe;

	dlm_lock_recovery(ls);

	जबतक (1) अणु
		lkb = del_proc_lock(ls, proc);
		अगर (!lkb)
			अवरोध;
		del_समयout(lkb);
		अगर (lkb->lkb_exflags & DLM_LKF_PERSISTENT)
			orphan_proc_lock(ls, lkb);
		अन्यथा
			unlock_proc_lock(ls, lkb);

		/* this हटाओs the reference क्रम the proc->locks list
		   added by dlm_user_request, it may result in the lkb
		   being मुक्तd */

		dlm_put_lkb(lkb);
	पूर्ण

	mutex_lock(&ls->ls_clear_proc_locks);

	/* in-progress unlocks */
	list_क्रम_each_entry_safe(lkb, safe, &proc->unlocking, lkb_ownqueue) अणु
		list_del_init(&lkb->lkb_ownqueue);
		lkb->lkb_flags |= DLM_IFL_DEAD;
		dlm_put_lkb(lkb);
	पूर्ण

	list_क्रम_each_entry_safe(lkb, safe, &proc->asts, lkb_cb_list) अणु
		स_रखो(&lkb->lkb_callbacks, 0,
		       माप(काष्ठा dlm_callback) * DLM_CALLBACKS_SIZE);
		list_del_init(&lkb->lkb_cb_list);
		dlm_put_lkb(lkb);
	पूर्ण

	mutex_unlock(&ls->ls_clear_proc_locks);
	dlm_unlock_recovery(ls);
पूर्ण

अटल व्योम purge_proc_locks(काष्ठा dlm_ls *ls, काष्ठा dlm_user_proc *proc)
अणु
	काष्ठा dlm_lkb *lkb, *safe;

	जबतक (1) अणु
		lkb = शून्य;
		spin_lock(&proc->locks_spin);
		अगर (!list_empty(&proc->locks)) अणु
			lkb = list_entry(proc->locks.next, काष्ठा dlm_lkb,
					 lkb_ownqueue);
			list_del_init(&lkb->lkb_ownqueue);
		पूर्ण
		spin_unlock(&proc->locks_spin);

		अगर (!lkb)
			अवरोध;

		lkb->lkb_flags |= DLM_IFL_DEAD;
		unlock_proc_lock(ls, lkb);
		dlm_put_lkb(lkb); /* ref from proc->locks list */
	पूर्ण

	spin_lock(&proc->locks_spin);
	list_क्रम_each_entry_safe(lkb, safe, &proc->unlocking, lkb_ownqueue) अणु
		list_del_init(&lkb->lkb_ownqueue);
		lkb->lkb_flags |= DLM_IFL_DEAD;
		dlm_put_lkb(lkb);
	पूर्ण
	spin_unlock(&proc->locks_spin);

	spin_lock(&proc->asts_spin);
	list_क्रम_each_entry_safe(lkb, safe, &proc->asts, lkb_cb_list) अणु
		स_रखो(&lkb->lkb_callbacks, 0,
		       माप(काष्ठा dlm_callback) * DLM_CALLBACKS_SIZE);
		list_del_init(&lkb->lkb_cb_list);
		dlm_put_lkb(lkb);
	पूर्ण
	spin_unlock(&proc->asts_spin);
पूर्ण

/* pid of 0 means purge all orphans */

अटल व्योम करो_purge(काष्ठा dlm_ls *ls, पूर्णांक nodeid, पूर्णांक pid)
अणु
	काष्ठा dlm_lkb *lkb, *safe;

	mutex_lock(&ls->ls_orphans_mutex);
	list_क्रम_each_entry_safe(lkb, safe, &ls->ls_orphans, lkb_ownqueue) अणु
		अगर (pid && lkb->lkb_ownpid != pid)
			जारी;
		unlock_proc_lock(ls, lkb);
		list_del_init(&lkb->lkb_ownqueue);
		dlm_put_lkb(lkb);
	पूर्ण
	mutex_unlock(&ls->ls_orphans_mutex);
पूर्ण

अटल पूर्णांक send_purge(काष्ठा dlm_ls *ls, पूर्णांक nodeid, पूर्णांक pid)
अणु
	काष्ठा dlm_message *ms;
	काष्ठा dlm_mhandle *mh;
	पूर्णांक error;

	error = _create_message(ls, माप(काष्ठा dlm_message), nodeid,
				DLM_MSG_PURGE, &ms, &mh);
	अगर (error)
		वापस error;
	ms->m_nodeid = nodeid;
	ms->m_pid = pid;

	वापस send_message(mh, ms);
पूर्ण

पूर्णांक dlm_user_purge(काष्ठा dlm_ls *ls, काष्ठा dlm_user_proc *proc,
		   पूर्णांक nodeid, पूर्णांक pid)
अणु
	पूर्णांक error = 0;

	अगर (nodeid && (nodeid != dlm_our_nodeid())) अणु
		error = send_purge(ls, nodeid, pid);
	पूर्ण अन्यथा अणु
		dlm_lock_recovery(ls);
		अगर (pid == current->pid)
			purge_proc_locks(ls, proc);
		अन्यथा
			करो_purge(ls, nodeid, pid);
		dlm_unlock_recovery(ls);
	पूर्ण
	वापस error;
पूर्ण

