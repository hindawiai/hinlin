<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2005-2008 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#समावेश "dlm_internal.h"
#समावेश "lockspace.h"
#समावेश "member.h"
#समावेश "lowcomms.h"
#समावेश "midcomms.h"
#समावेश "rcom.h"
#समावेश "recover.h"
#समावेश "dir.h"
#समावेश "config.h"
#समावेश "memory.h"
#समावेश "lock.h"
#समावेश "util.h"

अटल पूर्णांक rcom_response(काष्ठा dlm_ls *ls)
अणु
	वापस test_bit(LSFL_RCOM_READY, &ls->ls_flags);
पूर्ण

अटल पूर्णांक create_rcom(काष्ठा dlm_ls *ls, पूर्णांक to_nodeid, पूर्णांक type, पूर्णांक len,
		       काष्ठा dlm_rcom **rc_ret, काष्ठा dlm_mhandle **mh_ret)
अणु
	काष्ठा dlm_rcom *rc;
	काष्ठा dlm_mhandle *mh;
	अक्षर *mb;
	पूर्णांक mb_len = माप(काष्ठा dlm_rcom) + len;

	mh = dlm_lowcomms_get_buffer(to_nodeid, mb_len, GFP_NOFS, &mb);
	अगर (!mh) अणु
		log_prपूर्णांक("create_rcom to %d type %d len %d ENOBUFS",
			  to_nodeid, type, len);
		वापस -ENOBUFS;
	पूर्ण

	rc = (काष्ठा dlm_rcom *) mb;

	rc->rc_header.h_version = (DLM_HEADER_MAJOR | DLM_HEADER_MINOR);
	rc->rc_header.h_lockspace = ls->ls_global_id;
	rc->rc_header.h_nodeid = dlm_our_nodeid();
	rc->rc_header.h_length = mb_len;
	rc->rc_header.h_cmd = DLM_RCOM;

	rc->rc_type = type;

	spin_lock(&ls->ls_recover_lock);
	rc->rc_seq = ls->ls_recover_seq;
	spin_unlock(&ls->ls_recover_lock);

	*mh_ret = mh;
	*rc_ret = rc;
	वापस 0;
पूर्ण

अटल व्योम send_rcom(काष्ठा dlm_ls *ls, काष्ठा dlm_mhandle *mh,
		      काष्ठा dlm_rcom *rc)
अणु
	dlm_rcom_out(rc);
	dlm_lowcomms_commit_buffer(mh);
पूर्ण

अटल व्योम set_rcom_status(काष्ठा dlm_ls *ls, काष्ठा rcom_status *rs,
			    uपूर्णांक32_t flags)
अणु
	rs->rs_flags = cpu_to_le32(flags);
पूर्ण

/* When replying to a status request, a node also sends back its
   configuration values.  The requesting node then checks that the remote
   node is configured the same way as itself. */

अटल व्योम set_rcom_config(काष्ठा dlm_ls *ls, काष्ठा rcom_config *rf,
			    uपूर्णांक32_t num_slots)
अणु
	rf->rf_lvblen = cpu_to_le32(ls->ls_lvblen);
	rf->rf_lsflags = cpu_to_le32(ls->ls_exflags);

	rf->rf_our_slot = cpu_to_le16(ls->ls_slot);
	rf->rf_num_slots = cpu_to_le16(num_slots);
	rf->rf_generation =  cpu_to_le32(ls->ls_generation);
पूर्ण

अटल पूर्णांक check_rcom_config(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc, पूर्णांक nodeid)
अणु
	काष्ठा rcom_config *rf = (काष्ठा rcom_config *) rc->rc_buf;

	अगर ((rc->rc_header.h_version & 0xFFFF0000) != DLM_HEADER_MAJOR) अणु
		log_error(ls, "version mismatch: %x nodeid %d: %x",
			  DLM_HEADER_MAJOR | DLM_HEADER_MINOR, nodeid,
			  rc->rc_header.h_version);
		वापस -EPROTO;
	पूर्ण

	अगर (le32_to_cpu(rf->rf_lvblen) != ls->ls_lvblen ||
	    le32_to_cpu(rf->rf_lsflags) != ls->ls_exflags) अणु
		log_error(ls, "config mismatch: %d,%x nodeid %d: %d,%x",
			  ls->ls_lvblen, ls->ls_exflags, nodeid,
			  le32_to_cpu(rf->rf_lvblen),
			  le32_to_cpu(rf->rf_lsflags));
		वापस -EPROTO;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम allow_sync_reply(काष्ठा dlm_ls *ls, uपूर्णांक64_t *new_seq)
अणु
	spin_lock(&ls->ls_rcom_spin);
	*new_seq = ++ls->ls_rcom_seq;
	set_bit(LSFL_RCOM_WAIT, &ls->ls_flags);
	spin_unlock(&ls->ls_rcom_spin);
पूर्ण

अटल व्योम disallow_sync_reply(काष्ठा dlm_ls *ls)
अणु
	spin_lock(&ls->ls_rcom_spin);
	clear_bit(LSFL_RCOM_WAIT, &ls->ls_flags);
	clear_bit(LSFL_RCOM_READY, &ls->ls_flags);
	spin_unlock(&ls->ls_rcom_spin);
पूर्ण

/*
 * low nodeid gathers one slot value at a समय from each node.
 * it sets need_slots=0, and saves rf_our_slot वापसed from each
 * rcom_config.
 *
 * other nodes gather all slot values at once from the low nodeid.
 * they set need_slots=1, and ignore the rf_our_slot वापसed from each
 * rcom_config.  they use the rf_num_slots वापसed from the low
 * node's rcom_config.
 */

पूर्णांक dlm_rcom_status(काष्ठा dlm_ls *ls, पूर्णांक nodeid, uपूर्णांक32_t status_flags)
अणु
	काष्ठा dlm_rcom *rc;
	काष्ठा dlm_mhandle *mh;
	पूर्णांक error = 0;

	ls->ls_recover_nodeid = nodeid;

	अगर (nodeid == dlm_our_nodeid()) अणु
		rc = ls->ls_recover_buf;
		rc->rc_result = dlm_recover_status(ls);
		जाओ out;
	पूर्ण

retry:
	error = create_rcom(ls, nodeid, DLM_RCOM_STATUS,
			    माप(काष्ठा rcom_status), &rc, &mh);
	अगर (error)
		जाओ out;

	set_rcom_status(ls, (काष्ठा rcom_status *)rc->rc_buf, status_flags);

	allow_sync_reply(ls, &rc->rc_id);
	स_रखो(ls->ls_recover_buf, 0, LOWCOMMS_MAX_TX_BUFFER_LEN);

	send_rcom(ls, mh, rc);

	error = dlm_रुको_function(ls, &rcom_response);
	disallow_sync_reply(ls);
	अगर (error == -ETIMEDOUT)
		जाओ retry;
	अगर (error)
		जाओ out;

	rc = ls->ls_recover_buf;

	अगर (rc->rc_result == -ESRCH) अणु
		/* we pretend the remote lockspace exists with 0 status */
		log_debug(ls, "remote node %d not ready", nodeid);
		rc->rc_result = 0;
		error = 0;
	पूर्ण अन्यथा अणु
		error = check_rcom_config(ls, rc, nodeid);
	पूर्ण

	/* the caller looks at rc_result क्रम the remote recovery status */
 out:
	वापस error;
पूर्ण

अटल व्योम receive_rcom_status(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc_in)
अणु
	काष्ठा dlm_rcom *rc;
	काष्ठा dlm_mhandle *mh;
	काष्ठा rcom_status *rs;
	uपूर्णांक32_t status;
	पूर्णांक nodeid = rc_in->rc_header.h_nodeid;
	पूर्णांक len = माप(काष्ठा rcom_config);
	पूर्णांक num_slots = 0;
	पूर्णांक error;

	अगर (!dlm_slots_version(&rc_in->rc_header)) अणु
		status = dlm_recover_status(ls);
		जाओ करो_create;
	पूर्ण

	rs = (काष्ठा rcom_status *)rc_in->rc_buf;

	अगर (!(le32_to_cpu(rs->rs_flags) & DLM_RSF_NEED_SLOTS)) अणु
		status = dlm_recover_status(ls);
		जाओ करो_create;
	पूर्ण

	spin_lock(&ls->ls_recover_lock);
	status = ls->ls_recover_status;
	num_slots = ls->ls_num_slots;
	spin_unlock(&ls->ls_recover_lock);
	len += num_slots * माप(काष्ठा rcom_slot);

 करो_create:
	error = create_rcom(ls, nodeid, DLM_RCOM_STATUS_REPLY,
			    len, &rc, &mh);
	अगर (error)
		वापस;

	rc->rc_id = rc_in->rc_id;
	rc->rc_seq_reply = rc_in->rc_seq;
	rc->rc_result = status;

	set_rcom_config(ls, (काष्ठा rcom_config *)rc->rc_buf, num_slots);

	अगर (!num_slots)
		जाओ करो_send;

	spin_lock(&ls->ls_recover_lock);
	अगर (ls->ls_num_slots != num_slots) अणु
		spin_unlock(&ls->ls_recover_lock);
		log_debug(ls, "receive_rcom_status num_slots %d to %d",
			  num_slots, ls->ls_num_slots);
		rc->rc_result = 0;
		set_rcom_config(ls, (काष्ठा rcom_config *)rc->rc_buf, 0);
		जाओ करो_send;
	पूर्ण

	dlm_slots_copy_out(ls, rc);
	spin_unlock(&ls->ls_recover_lock);

 करो_send:
	send_rcom(ls, mh, rc);
पूर्ण

अटल व्योम receive_sync_reply(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc_in)
अणु
	spin_lock(&ls->ls_rcom_spin);
	अगर (!test_bit(LSFL_RCOM_WAIT, &ls->ls_flags) ||
	    rc_in->rc_id != ls->ls_rcom_seq) अणु
		log_debug(ls, "reject reply %d from %d seq %llx expect %llx",
			  rc_in->rc_type, rc_in->rc_header.h_nodeid,
			  (अचिन्हित दीर्घ दीर्घ)rc_in->rc_id,
			  (अचिन्हित दीर्घ दीर्घ)ls->ls_rcom_seq);
		जाओ out;
	पूर्ण
	स_नकल(ls->ls_recover_buf, rc_in, rc_in->rc_header.h_length);
	set_bit(LSFL_RCOM_READY, &ls->ls_flags);
	clear_bit(LSFL_RCOM_WAIT, &ls->ls_flags);
	wake_up(&ls->ls_रुको_general);
 out:
	spin_unlock(&ls->ls_rcom_spin);
पूर्ण

पूर्णांक dlm_rcom_names(काष्ठा dlm_ls *ls, पूर्णांक nodeid, अक्षर *last_name, पूर्णांक last_len)
अणु
	काष्ठा dlm_rcom *rc;
	काष्ठा dlm_mhandle *mh;
	पूर्णांक error = 0;

	ls->ls_recover_nodeid = nodeid;

retry:
	error = create_rcom(ls, nodeid, DLM_RCOM_NAMES, last_len, &rc, &mh);
	अगर (error)
		जाओ out;
	स_नकल(rc->rc_buf, last_name, last_len);

	allow_sync_reply(ls, &rc->rc_id);
	स_रखो(ls->ls_recover_buf, 0, LOWCOMMS_MAX_TX_BUFFER_LEN);

	send_rcom(ls, mh, rc);

	error = dlm_रुको_function(ls, &rcom_response);
	disallow_sync_reply(ls);
	अगर (error == -ETIMEDOUT)
		जाओ retry;
 out:
	वापस error;
पूर्ण

अटल व्योम receive_rcom_names(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc_in)
अणु
	काष्ठा dlm_rcom *rc;
	काष्ठा dlm_mhandle *mh;
	पूर्णांक error, inlen, outlen, nodeid;

	nodeid = rc_in->rc_header.h_nodeid;
	inlen = rc_in->rc_header.h_length - माप(काष्ठा dlm_rcom);
	outlen = LOWCOMMS_MAX_TX_BUFFER_LEN - माप(काष्ठा dlm_rcom);

	error = create_rcom(ls, nodeid, DLM_RCOM_NAMES_REPLY, outlen, &rc, &mh);
	अगर (error)
		वापस;
	rc->rc_id = rc_in->rc_id;
	rc->rc_seq_reply = rc_in->rc_seq;

	dlm_copy_master_names(ls, rc_in->rc_buf, inlen, rc->rc_buf, outlen,
			      nodeid);
	send_rcom(ls, mh, rc);
पूर्ण

पूर्णांक dlm_send_rcom_lookup(काष्ठा dlm_rsb *r, पूर्णांक dir_nodeid)
अणु
	काष्ठा dlm_rcom *rc;
	काष्ठा dlm_mhandle *mh;
	काष्ठा dlm_ls *ls = r->res_ls;
	पूर्णांक error;

	error = create_rcom(ls, dir_nodeid, DLM_RCOM_LOOKUP, r->res_length,
			    &rc, &mh);
	अगर (error)
		जाओ out;
	स_नकल(rc->rc_buf, r->res_name, r->res_length);
	rc->rc_id = (अचिन्हित दीर्घ) r->res_id;

	send_rcom(ls, mh, rc);
 out:
	वापस error;
पूर्ण

अटल व्योम receive_rcom_lookup(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc_in)
अणु
	काष्ठा dlm_rcom *rc;
	काष्ठा dlm_mhandle *mh;
	पूर्णांक error, ret_nodeid, nodeid = rc_in->rc_header.h_nodeid;
	पूर्णांक len = rc_in->rc_header.h_length - माप(काष्ठा dlm_rcom);

	error = create_rcom(ls, nodeid, DLM_RCOM_LOOKUP_REPLY, 0, &rc, &mh);
	अगर (error)
		वापस;

	/* Old code would send this special id to trigger a debug dump. */
	अगर (rc_in->rc_id == 0xFFFFFFFF) अणु
		log_error(ls, "receive_rcom_lookup dump from %d", nodeid);
		dlm_dump_rsb_name(ls, rc_in->rc_buf, len);
		वापस;
	पूर्ण

	error = dlm_master_lookup(ls, nodeid, rc_in->rc_buf, len,
				  DLM_LU_RECOVER_MASTER, &ret_nodeid, शून्य);
	अगर (error)
		ret_nodeid = error;
	rc->rc_result = ret_nodeid;
	rc->rc_id = rc_in->rc_id;
	rc->rc_seq_reply = rc_in->rc_seq;

	send_rcom(ls, mh, rc);
पूर्ण

अटल व्योम receive_rcom_lookup_reply(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc_in)
अणु
	dlm_recover_master_reply(ls, rc_in);
पूर्ण

अटल व्योम pack_rcom_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb,
			   काष्ठा rcom_lock *rl)
अणु
	स_रखो(rl, 0, माप(*rl));

	rl->rl_ownpid = cpu_to_le32(lkb->lkb_ownpid);
	rl->rl_lkid = cpu_to_le32(lkb->lkb_id);
	rl->rl_exflags = cpu_to_le32(lkb->lkb_exflags);
	rl->rl_flags = cpu_to_le32(lkb->lkb_flags);
	rl->rl_lvbseq = cpu_to_le32(lkb->lkb_lvbseq);
	rl->rl_rqmode = lkb->lkb_rqmode;
	rl->rl_grmode = lkb->lkb_grmode;
	rl->rl_status = lkb->lkb_status;
	rl->rl_रुको_type = cpu_to_le16(lkb->lkb_रुको_type);

	अगर (lkb->lkb_bastfn)
		rl->rl_asts |= DLM_CB_BAST;
	अगर (lkb->lkb_astfn)
		rl->rl_asts |= DLM_CB_CAST;

	rl->rl_namelen = cpu_to_le16(r->res_length);
	स_नकल(rl->rl_name, r->res_name, r->res_length);

	/* FIXME: might we have an lvb without DLM_LKF_VALBLK set ?
	   If so, receive_rcom_lock_args() won't take this copy. */

	अगर (lkb->lkb_lvbptr)
		स_नकल(rl->rl_lvb, lkb->lkb_lvbptr, r->res_ls->ls_lvblen);
पूर्ण

पूर्णांक dlm_send_rcom_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb)
अणु
	काष्ठा dlm_ls *ls = r->res_ls;
	काष्ठा dlm_rcom *rc;
	काष्ठा dlm_mhandle *mh;
	काष्ठा rcom_lock *rl;
	पूर्णांक error, len = माप(काष्ठा rcom_lock);

	अगर (lkb->lkb_lvbptr)
		len += ls->ls_lvblen;

	error = create_rcom(ls, r->res_nodeid, DLM_RCOM_LOCK, len, &rc, &mh);
	अगर (error)
		जाओ out;

	rl = (काष्ठा rcom_lock *) rc->rc_buf;
	pack_rcom_lock(r, lkb, rl);
	rc->rc_id = (अचिन्हित दीर्घ) r;

	send_rcom(ls, mh, rc);
 out:
	वापस error;
पूर्ण

/* needs at least dlm_rcom + rcom_lock */
अटल व्योम receive_rcom_lock(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc_in)
अणु
	काष्ठा dlm_rcom *rc;
	काष्ठा dlm_mhandle *mh;
	पूर्णांक error, nodeid = rc_in->rc_header.h_nodeid;

	dlm_recover_master_copy(ls, rc_in);

	error = create_rcom(ls, nodeid, DLM_RCOM_LOCK_REPLY,
			    माप(काष्ठा rcom_lock), &rc, &mh);
	अगर (error)
		वापस;

	/* We send back the same rcom_lock काष्ठा we received, but
	   dlm_recover_master_copy() has filled in rl_remid and rl_result */

	स_नकल(rc->rc_buf, rc_in->rc_buf, माप(काष्ठा rcom_lock));
	rc->rc_id = rc_in->rc_id;
	rc->rc_seq_reply = rc_in->rc_seq;

	send_rcom(ls, mh, rc);
पूर्ण

/* If the lockspace करोesn't exist then still send a status message
   back; it's possible that it just doesn't have its global_id yet. */

पूर्णांक dlm_send_ls_not_पढ़ोy(पूर्णांक nodeid, काष्ठा dlm_rcom *rc_in)
अणु
	काष्ठा dlm_rcom *rc;
	काष्ठा rcom_config *rf;
	काष्ठा dlm_mhandle *mh;
	अक्षर *mb;
	पूर्णांक mb_len = माप(काष्ठा dlm_rcom) + माप(काष्ठा rcom_config);

	mh = dlm_lowcomms_get_buffer(nodeid, mb_len, GFP_NOFS, &mb);
	अगर (!mh)
		वापस -ENOBUFS;

	rc = (काष्ठा dlm_rcom *) mb;

	rc->rc_header.h_version = (DLM_HEADER_MAJOR | DLM_HEADER_MINOR);
	rc->rc_header.h_lockspace = rc_in->rc_header.h_lockspace;
	rc->rc_header.h_nodeid = dlm_our_nodeid();
	rc->rc_header.h_length = mb_len;
	rc->rc_header.h_cmd = DLM_RCOM;

	rc->rc_type = DLM_RCOM_STATUS_REPLY;
	rc->rc_id = rc_in->rc_id;
	rc->rc_seq_reply = rc_in->rc_seq;
	rc->rc_result = -ESRCH;

	rf = (काष्ठा rcom_config *) rc->rc_buf;
	rf->rf_lvblen = cpu_to_le32(~0U);

	dlm_rcom_out(rc);
	dlm_lowcomms_commit_buffer(mh);

	वापस 0;
पूर्ण

/*
 * Ignore messages क्रम stage Y beक्रमe we set
 * recover_status bit क्रम stage X:
 *
 * recover_status = 0
 *
 * dlm_recover_members()
 * - send nothing
 * - recv nothing
 * - ignore NAMES, NAMES_REPLY
 * - ignore LOOKUP, LOOKUP_REPLY
 * - ignore LOCK, LOCK_REPLY
 *
 * recover_status |= NODES
 *
 * dlm_recover_members_रुको()
 *
 * dlm_recover_directory()
 * - send NAMES
 * - recv NAMES_REPLY
 * - ignore LOOKUP, LOOKUP_REPLY
 * - ignore LOCK, LOCK_REPLY
 *
 * recover_status |= सूची
 *
 * dlm_recover_directory_रुको()
 *
 * dlm_recover_masters()
 * - send LOOKUP
 * - recv LOOKUP_REPLY
 *
 * dlm_recover_locks()
 * - send LOCKS
 * - recv LOCKS_REPLY
 *
 * recover_status |= LOCKS
 *
 * dlm_recover_locks_रुको()
 *
 * recover_status |= DONE
 */

/* Called by dlm_recv; corresponds to dlm_receive_message() but special
   recovery-only comms are sent through here. */

व्योम dlm_receive_rcom(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc, पूर्णांक nodeid)
अणु
	पूर्णांक lock_size = माप(काष्ठा dlm_rcom) + माप(काष्ठा rcom_lock);
	पूर्णांक stop, reply = 0, names = 0, lookup = 0, lock = 0;
	uपूर्णांक32_t status;
	uपूर्णांक64_t seq;

	चयन (rc->rc_type) अणु
	हाल DLM_RCOM_STATUS_REPLY:
		reply = 1;
		अवरोध;
	हाल DLM_RCOM_NAMES:
		names = 1;
		अवरोध;
	हाल DLM_RCOM_NAMES_REPLY:
		names = 1;
		reply = 1;
		अवरोध;
	हाल DLM_RCOM_LOOKUP:
		lookup = 1;
		अवरोध;
	हाल DLM_RCOM_LOOKUP_REPLY:
		lookup = 1;
		reply = 1;
		अवरोध;
	हाल DLM_RCOM_LOCK:
		lock = 1;
		अवरोध;
	हाल DLM_RCOM_LOCK_REPLY:
		lock = 1;
		reply = 1;
		अवरोध;
	पूर्ण

	spin_lock(&ls->ls_recover_lock);
	status = ls->ls_recover_status;
	stop = test_bit(LSFL_RECOVER_STOP, &ls->ls_flags);
	seq = ls->ls_recover_seq;
	spin_unlock(&ls->ls_recover_lock);

	अगर (stop && (rc->rc_type != DLM_RCOM_STATUS))
		जाओ ignore;

	अगर (reply && (rc->rc_seq_reply != seq))
		जाओ ignore;

	अगर (!(status & DLM_RS_NODES) && (names || lookup || lock))
		जाओ ignore;

	अगर (!(status & DLM_RS_सूची) && (lookup || lock))
		जाओ ignore;

	चयन (rc->rc_type) अणु
	हाल DLM_RCOM_STATUS:
		receive_rcom_status(ls, rc);
		अवरोध;

	हाल DLM_RCOM_NAMES:
		receive_rcom_names(ls, rc);
		अवरोध;

	हाल DLM_RCOM_LOOKUP:
		receive_rcom_lookup(ls, rc);
		अवरोध;

	हाल DLM_RCOM_LOCK:
		अगर (rc->rc_header.h_length < lock_size)
			जाओ Eलघु;
		receive_rcom_lock(ls, rc);
		अवरोध;

	हाल DLM_RCOM_STATUS_REPLY:
		receive_sync_reply(ls, rc);
		अवरोध;

	हाल DLM_RCOM_NAMES_REPLY:
		receive_sync_reply(ls, rc);
		अवरोध;

	हाल DLM_RCOM_LOOKUP_REPLY:
		receive_rcom_lookup_reply(ls, rc);
		अवरोध;

	हाल DLM_RCOM_LOCK_REPLY:
		अगर (rc->rc_header.h_length < lock_size)
			जाओ Eलघु;
		dlm_recover_process_copy(ls, rc);
		अवरोध;

	शेष:
		log_error(ls, "receive_rcom bad type %d", rc->rc_type);
	पूर्ण
	वापस;

ignore:
	log_limit(ls, "dlm_receive_rcom ignore msg %d "
		  "from %d %llu %llu recover seq %llu sts %x gen %u",
		   rc->rc_type,
		   nodeid,
		   (अचिन्हित दीर्घ दीर्घ)rc->rc_seq,
		   (अचिन्हित दीर्घ दीर्घ)rc->rc_seq_reply,
		   (अचिन्हित दीर्घ दीर्घ)seq,
		   status, ls->ls_generation);
	वापस;
Eलघु:
	log_error(ls, "recovery message %d from %d is too short",
		  rc->rc_type, nodeid);
पूर्ण

