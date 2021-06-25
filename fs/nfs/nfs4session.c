<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fs/nfs/nfs4session.c
 *
 * Copyright (c) 2012 Trond Myklebust <Trond.Myklebust@netapp.com>
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/bc_xprt.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs4.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/module.h>

#समावेश "nfs4_fs.h"
#समावेश "internal.h"
#समावेश "nfs4session.h"
#समावेश "callback.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_STATE

अटल व्योम nfs4_init_slot_table(काष्ठा nfs4_slot_table *tbl, स्थिर अक्षर *queue)
अणु
	tbl->highest_used_slotid = NFS4_NO_SLOT;
	spin_lock_init(&tbl->slot_tbl_lock);
	rpc_init_priority_रुको_queue(&tbl->slot_tbl_रुकोq, queue);
	init_रुकोqueue_head(&tbl->slot_रुकोq);
	init_completion(&tbl->complete);
पूर्ण

/*
 * nfs4_shrink_slot_table - मुक्त retired slots from the slot table
 */
अटल व्योम nfs4_shrink_slot_table(काष्ठा nfs4_slot_table  *tbl, u32 newsize)
अणु
	काष्ठा nfs4_slot **p;
	अगर (newsize >= tbl->max_slots)
		वापस;

	p = &tbl->slots;
	जबतक (newsize--)
		p = &(*p)->next;
	जबतक (*p) अणु
		काष्ठा nfs4_slot *slot = *p;

		*p = slot->next;
		kमुक्त(slot);
		tbl->max_slots--;
	पूर्ण
पूर्ण

/**
 * nfs4_slot_tbl_drain_complete - wake रुकोers when drain is complete
 * @tbl: controlling slot table
 *
 */
व्योम nfs4_slot_tbl_drain_complete(काष्ठा nfs4_slot_table *tbl)
अणु
	अगर (nfs4_slot_tbl_draining(tbl))
		complete(&tbl->complete);
पूर्ण

/*
 * nfs4_मुक्त_slot - मुक्त a slot and efficiently update slot table.
 *
 * मुक्तing a slot is trivially करोne by clearing its respective bit
 * in the biपंचांगap.
 * If the मुक्तd slotid equals highest_used_slotid we want to update it
 * so that the server would be able to size करोwn the slot table अगर needed,
 * otherwise we know that the highest_used_slotid is still in use.
 * When updating highest_used_slotid there may be "holes" in the biपंचांगap
 * so we need to scan करोwn from highest_used_slotid to 0 looking क्रम the now
 * highest slotid in use.
 * If none found, highest_used_slotid is set to NFS4_NO_SLOT.
 *
 * Must be called जबतक holding tbl->slot_tbl_lock
 */
व्योम nfs4_मुक्त_slot(काष्ठा nfs4_slot_table *tbl, काष्ठा nfs4_slot *slot)
अणु
	u32 slotid = slot->slot_nr;

	/* clear used bit in biपंचांगap */
	__clear_bit(slotid, tbl->used_slots);

	/* update highest_used_slotid when it is मुक्तd */
	अगर (slotid == tbl->highest_used_slotid) अणु
		u32 new_max = find_last_bit(tbl->used_slots, slotid);
		अगर (new_max < slotid)
			tbl->highest_used_slotid = new_max;
		अन्यथा अणु
			tbl->highest_used_slotid = NFS4_NO_SLOT;
			nfs4_slot_tbl_drain_complete(tbl);
		पूर्ण
	पूर्ण
	dprपूर्णांकk("%s: slotid %u highest_used_slotid %u\n", __func__,
		slotid, tbl->highest_used_slotid);
पूर्ण

अटल काष्ठा nfs4_slot *nfs4_new_slot(काष्ठा nfs4_slot_table  *tbl,
		u32 slotid, u32 seq_init, gfp_t gfp_mask)
अणु
	काष्ठा nfs4_slot *slot;

	slot = kzalloc(माप(*slot), gfp_mask);
	अगर (slot) अणु
		slot->table = tbl;
		slot->slot_nr = slotid;
		slot->seq_nr = seq_init;
		slot->seq_nr_highest_sent = seq_init;
		slot->seq_nr_last_acked = seq_init - 1;
	पूर्ण
	वापस slot;
पूर्ण

अटल काष्ठा nfs4_slot *nfs4_find_or_create_slot(काष्ठा nfs4_slot_table  *tbl,
		u32 slotid, u32 seq_init, gfp_t gfp_mask)
अणु
	काष्ठा nfs4_slot **p, *slot;

	p = &tbl->slots;
	क्रम (;;) अणु
		अगर (*p == शून्य) अणु
			*p = nfs4_new_slot(tbl, tbl->max_slots,
					seq_init, gfp_mask);
			अगर (*p == शून्य)
				अवरोध;
			tbl->max_slots++;
		पूर्ण
		slot = *p;
		अगर (slot->slot_nr == slotid)
			वापस slot;
		p = &slot->next;
	पूर्ण
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम nfs4_lock_slot(काष्ठा nfs4_slot_table *tbl,
		काष्ठा nfs4_slot *slot)
अणु
	u32 slotid = slot->slot_nr;

	__set_bit(slotid, tbl->used_slots);
	अगर (slotid > tbl->highest_used_slotid ||
	    tbl->highest_used_slotid == NFS4_NO_SLOT)
		tbl->highest_used_slotid = slotid;
	slot->generation = tbl->generation;
पूर्ण

/*
 * nfs4_try_to_lock_slot - Given a slot try to allocate it
 *
 * Note: must be called with the slot_tbl_lock held.
 */
bool nfs4_try_to_lock_slot(काष्ठा nfs4_slot_table *tbl, काष्ठा nfs4_slot *slot)
अणु
	अगर (nfs4_test_locked_slot(tbl, slot->slot_nr))
		वापस false;
	nfs4_lock_slot(tbl, slot);
	वापस true;
पूर्ण

/*
 * nfs4_lookup_slot - Find a slot but करोn't allocate it
 *
 * Note: must be called with the slot_tbl_lock held.
 */
काष्ठा nfs4_slot *nfs4_lookup_slot(काष्ठा nfs4_slot_table *tbl, u32 slotid)
अणु
	अगर (slotid <= tbl->max_slotid)
		वापस nfs4_find_or_create_slot(tbl, slotid, 0, GFP_NOWAIT);
	वापस ERR_PTR(-E2BIG);
पूर्ण

अटल पूर्णांक nfs4_slot_get_seqid(काष्ठा nfs4_slot_table  *tbl, u32 slotid,
		u32 *seq_nr)
	__must_hold(&tbl->slot_tbl_lock)
अणु
	काष्ठा nfs4_slot *slot;
	पूर्णांक ret;

	slot = nfs4_lookup_slot(tbl, slotid);
	ret = PTR_ERR_OR_ZERO(slot);
	अगर (!ret)
		*seq_nr = slot->seq_nr;

	वापस ret;
पूर्ण

/*
 * nfs4_slot_seqid_in_use - test अगर a slot sequence id is still in use
 *
 * Given a slot table, slot id and sequence number, determine अगर the
 * RPC call in question is still in flight. This function is मुख्यly
 * पूर्णांकended क्रम use by the callback channel.
 */
अटल bool nfs4_slot_seqid_in_use(काष्ठा nfs4_slot_table *tbl,
		u32 slotid, u32 seq_nr)
अणु
	u32 cur_seq = 0;
	bool ret = false;

	spin_lock(&tbl->slot_tbl_lock);
	अगर (nfs4_slot_get_seqid(tbl, slotid, &cur_seq) == 0 &&
	    cur_seq == seq_nr && test_bit(slotid, tbl->used_slots))
		ret = true;
	spin_unlock(&tbl->slot_tbl_lock);
	वापस ret;
पूर्ण

/*
 * nfs4_slot_रुको_on_seqid - रुको until a slot sequence id is complete
 *
 * Given a slot table, slot id and sequence number, रुको until the
 * corresponding RPC call completes. This function is मुख्यly
 * पूर्णांकended क्रम use by the callback channel.
 */
पूर्णांक nfs4_slot_रुको_on_seqid(काष्ठा nfs4_slot_table *tbl,
		u32 slotid, u32 seq_nr,
		अचिन्हित दीर्घ समयout)
अणु
	अगर (रुको_event_समयout(tbl->slot_रुकोq,
			!nfs4_slot_seqid_in_use(tbl, slotid, seq_nr),
			समयout) == 0)
		वापस -ETIMEDOUT;
	वापस 0;
पूर्ण

/*
 * nfs4_alloc_slot - efficiently look क्रम a मुक्त slot
 *
 * nfs4_alloc_slot looks क्रम an unset bit in the used_slots biपंचांगap.
 * If found, we mark the slot as used, update the highest_used_slotid,
 * and respectively set up the sequence operation args.
 *
 * Note: must be called with under the slot_tbl_lock.
 */
काष्ठा nfs4_slot *nfs4_alloc_slot(काष्ठा nfs4_slot_table *tbl)
अणु
	काष्ठा nfs4_slot *ret = ERR_PTR(-EBUSY);
	u32 slotid;

	dprपूर्णांकk("--> %s used_slots=%04lx highest_used=%u max_slots=%u\n",
		__func__, tbl->used_slots[0], tbl->highest_used_slotid,
		tbl->max_slotid + 1);
	slotid = find_first_zero_bit(tbl->used_slots, tbl->max_slotid + 1);
	अगर (slotid <= tbl->max_slotid) अणु
		ret = nfs4_find_or_create_slot(tbl, slotid, 1, GFP_NOWAIT);
		अगर (!IS_ERR(ret))
			nfs4_lock_slot(tbl, ret);
	पूर्ण
	dprपूर्णांकk("<-- %s used_slots=%04lx highest_used=%u slotid=%u\n",
		__func__, tbl->used_slots[0], tbl->highest_used_slotid,
		!IS_ERR(ret) ? ret->slot_nr : NFS4_NO_SLOT);
	वापस ret;
पूर्ण

अटल पूर्णांक nfs4_grow_slot_table(काष्ठा nfs4_slot_table *tbl,
		 u32 max_reqs, u32 ivalue)
अणु
	अगर (max_reqs <= tbl->max_slots)
		वापस 0;
	अगर (!IS_ERR(nfs4_find_or_create_slot(tbl, max_reqs - 1, ivalue, GFP_NOFS)))
		वापस 0;
	वापस -ENOMEM;
पूर्ण

अटल व्योम nfs4_reset_slot_table(काष्ठा nfs4_slot_table *tbl,
		u32 server_highest_slotid,
		u32 ivalue)
अणु
	काष्ठा nfs4_slot **p;

	nfs4_shrink_slot_table(tbl, server_highest_slotid + 1);
	p = &tbl->slots;
	जबतक (*p) अणु
		(*p)->seq_nr = ivalue;
		(*p)->seq_nr_highest_sent = ivalue;
		(*p)->seq_nr_last_acked = ivalue - 1;
		p = &(*p)->next;
	पूर्ण
	tbl->highest_used_slotid = NFS4_NO_SLOT;
	tbl->target_highest_slotid = server_highest_slotid;
	tbl->server_highest_slotid = server_highest_slotid;
	tbl->d_target_highest_slotid = 0;
	tbl->d2_target_highest_slotid = 0;
	tbl->max_slotid = server_highest_slotid;
पूर्ण

/*
 * (re)Initialise a slot table
 */
अटल पूर्णांक nfs4_पुनः_स्मृति_slot_table(काष्ठा nfs4_slot_table *tbl,
		u32 max_reqs, u32 ivalue)
अणु
	पूर्णांक ret;

	dprपूर्णांकk("--> %s: max_reqs=%u, tbl->max_slots %u\n", __func__,
		max_reqs, tbl->max_slots);

	अगर (max_reqs > NFS4_MAX_SLOT_TABLE)
		max_reqs = NFS4_MAX_SLOT_TABLE;

	ret = nfs4_grow_slot_table(tbl, max_reqs, ivalue);
	अगर (ret)
		जाओ out;

	spin_lock(&tbl->slot_tbl_lock);
	nfs4_reset_slot_table(tbl, max_reqs - 1, ivalue);
	spin_unlock(&tbl->slot_tbl_lock);

	dprपूर्णांकk("%s: tbl=%p slots=%p max_slots=%u\n", __func__,
		tbl, tbl->slots, tbl->max_slots);
out:
	dprपूर्णांकk("<-- %s: return %d\n", __func__, ret);
	वापस ret;
पूर्ण

/*
 * nfs4_release_slot_table - release all slot table entries
 */
अटल व्योम nfs4_release_slot_table(काष्ठा nfs4_slot_table *tbl)
अणु
	nfs4_shrink_slot_table(tbl, 0);
पूर्ण

/**
 * nfs4_shutकरोwn_slot_table - release resources attached to a slot table
 * @tbl: slot table to shut करोwn
 *
 */
व्योम nfs4_shutकरोwn_slot_table(काष्ठा nfs4_slot_table *tbl)
अणु
	nfs4_release_slot_table(tbl);
	rpc_destroy_रुको_queue(&tbl->slot_tbl_रुकोq);
पूर्ण

/**
 * nfs4_setup_slot_table - prepare a stand-alone slot table क्रम use
 * @tbl: slot table to set up
 * @max_reqs: maximum number of requests allowed
 * @queue: name to give RPC रुको queue
 *
 * Returns zero on success, or a negative त्रुटि_सं.
 */
पूर्णांक nfs4_setup_slot_table(काष्ठा nfs4_slot_table *tbl, अचिन्हित पूर्णांक max_reqs,
		स्थिर अक्षर *queue)
अणु
	nfs4_init_slot_table(tbl, queue);
	वापस nfs4_पुनः_स्मृति_slot_table(tbl, max_reqs, 0);
पूर्ण

अटल bool nfs41_assign_slot(काष्ठा rpc_task *task, व्योम *pslot)
अणु
	काष्ठा nfs4_sequence_args *args = task->tk_msg.rpc_argp;
	काष्ठा nfs4_sequence_res *res = task->tk_msg.rpc_resp;
	काष्ठा nfs4_slot *slot = pslot;
	काष्ठा nfs4_slot_table *tbl = slot->table;

	अगर (nfs4_slot_tbl_draining(tbl) && !args->sa_privileged)
		वापस false;
	slot->generation = tbl->generation;
	args->sa_slot = slot;
	res->sr_बारtamp = jअगरfies;
	res->sr_slot = slot;
	res->sr_status_flags = 0;
	res->sr_status = 1;
	वापस true;
पूर्ण

अटल bool __nfs41_wake_and_assign_slot(काष्ठा nfs4_slot_table *tbl,
		काष्ठा nfs4_slot *slot)
अणु
	अगर (rpc_wake_up_first(&tbl->slot_tbl_रुकोq, nfs41_assign_slot, slot))
		वापस true;
	वापस false;
पूर्ण

bool nfs41_wake_and_assign_slot(काष्ठा nfs4_slot_table *tbl,
		काष्ठा nfs4_slot *slot)
अणु
	अगर (slot->slot_nr > tbl->max_slotid)
		वापस false;
	वापस __nfs41_wake_and_assign_slot(tbl, slot);
पूर्ण

अटल bool nfs41_try_wake_next_slot_table_entry(काष्ठा nfs4_slot_table *tbl)
अणु
	काष्ठा nfs4_slot *slot = nfs4_alloc_slot(tbl);
	अगर (!IS_ERR(slot)) अणु
		bool ret = __nfs41_wake_and_assign_slot(tbl, slot);
		अगर (ret)
			वापस ret;
		nfs4_मुक्त_slot(tbl, slot);
	पूर्ण
	वापस false;
पूर्ण

व्योम nfs41_wake_slot_table(काष्ठा nfs4_slot_table *tbl)
अणु
	क्रम (;;) अणु
		अगर (!nfs41_try_wake_next_slot_table_entry(tbl))
			अवरोध;
	पूर्ण
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)

अटल व्योम nfs41_set_max_slotid_locked(काष्ठा nfs4_slot_table *tbl,
		u32 target_highest_slotid)
अणु
	u32 max_slotid;

	max_slotid = min(NFS4_MAX_SLOT_TABLE - 1, target_highest_slotid);
	अगर (max_slotid > tbl->server_highest_slotid)
		max_slotid = tbl->server_highest_slotid;
	अगर (max_slotid > tbl->target_highest_slotid)
		max_slotid = tbl->target_highest_slotid;
	tbl->max_slotid = max_slotid;
	nfs41_wake_slot_table(tbl);
पूर्ण

/* Update the client's idea of target_highest_slotid */
अटल व्योम nfs41_set_target_slotid_locked(काष्ठा nfs4_slot_table *tbl,
		u32 target_highest_slotid)
अणु
	अगर (tbl->target_highest_slotid == target_highest_slotid)
		वापस;
	tbl->target_highest_slotid = target_highest_slotid;
	tbl->generation++;
पूर्ण

व्योम nfs41_set_target_slotid(काष्ठा nfs4_slot_table *tbl,
		u32 target_highest_slotid)
अणु
	spin_lock(&tbl->slot_tbl_lock);
	nfs41_set_target_slotid_locked(tbl, target_highest_slotid);
	tbl->d_target_highest_slotid = 0;
	tbl->d2_target_highest_slotid = 0;
	nfs41_set_max_slotid_locked(tbl, target_highest_slotid);
	spin_unlock(&tbl->slot_tbl_lock);
पूर्ण

अटल व्योम nfs41_set_server_slotid_locked(काष्ठा nfs4_slot_table *tbl,
		u32 highest_slotid)
अणु
	अगर (tbl->server_highest_slotid == highest_slotid)
		वापस;
	अगर (tbl->highest_used_slotid > highest_slotid)
		वापस;
	/* Deallocate slots */
	nfs4_shrink_slot_table(tbl, highest_slotid + 1);
	tbl->server_highest_slotid = highest_slotid;
पूर्ण

अटल s32 nfs41_derivative_target_slotid(s32 s1, s32 s2)
अणु
	s1 -= s2;
	अगर (s1 == 0)
		वापस 0;
	अगर (s1 < 0)
		वापस (s1 - 1) >> 1;
	वापस (s1 + 1) >> 1;
पूर्ण

अटल पूर्णांक nfs41_sign_s32(s32 s1)
अणु
	अगर (s1 > 0)
		वापस 1;
	अगर (s1 < 0)
		वापस -1;
	वापस 0;
पूर्ण

अटल bool nfs41_same_sign_or_zero_s32(s32 s1, s32 s2)
अणु
	अगर (!s1 || !s2)
		वापस true;
	वापस nfs41_sign_s32(s1) == nfs41_sign_s32(s2);
पूर्ण

/* Try to eliminate outliers by checking क्रम sharp changes in the
 * derivatives and second derivatives
 */
अटल bool nfs41_is_outlier_target_slotid(काष्ठा nfs4_slot_table *tbl,
		u32 new_target)
अणु
	s32 d_target, d2_target;
	bool ret = true;

	d_target = nfs41_derivative_target_slotid(new_target,
			tbl->target_highest_slotid);
	d2_target = nfs41_derivative_target_slotid(d_target,
			tbl->d_target_highest_slotid);
	/* Is first derivative same sign? */
	अगर (nfs41_same_sign_or_zero_s32(d_target, tbl->d_target_highest_slotid))
		ret = false;
	/* Is second derivative same sign? */
	अगर (nfs41_same_sign_or_zero_s32(d2_target, tbl->d2_target_highest_slotid))
		ret = false;
	tbl->d_target_highest_slotid = d_target;
	tbl->d2_target_highest_slotid = d2_target;
	वापस ret;
पूर्ण

व्योम nfs41_update_target_slotid(काष्ठा nfs4_slot_table *tbl,
		काष्ठा nfs4_slot *slot,
		काष्ठा nfs4_sequence_res *res)
अणु
	spin_lock(&tbl->slot_tbl_lock);
	अगर (!nfs41_is_outlier_target_slotid(tbl, res->sr_target_highest_slotid))
		nfs41_set_target_slotid_locked(tbl, res->sr_target_highest_slotid);
	अगर (tbl->generation == slot->generation)
		nfs41_set_server_slotid_locked(tbl, res->sr_highest_slotid);
	nfs41_set_max_slotid_locked(tbl, res->sr_target_highest_slotid);
	spin_unlock(&tbl->slot_tbl_lock);
पूर्ण

अटल व्योम nfs4_release_session_slot_tables(काष्ठा nfs4_session *session)
अणु
	nfs4_release_slot_table(&session->fc_slot_table);
	nfs4_release_slot_table(&session->bc_slot_table);
पूर्ण

/*
 * Initialize or reset the क्रमechannel and backchannel tables
 */
पूर्णांक nfs4_setup_session_slot_tables(काष्ठा nfs4_session *ses)
अणु
	काष्ठा nfs4_slot_table *tbl;
	पूर्णांक status;

	dprपूर्णांकk("--> %s\n", __func__);
	/* Fore channel */
	tbl = &ses->fc_slot_table;
	tbl->session = ses;
	status = nfs4_पुनः_स्मृति_slot_table(tbl, ses->fc_attrs.max_reqs, 1);
	अगर (status || !(ses->flags & SESSION4_BACK_CHAN)) /* -ENOMEM */
		वापस status;
	/* Back channel */
	tbl = &ses->bc_slot_table;
	tbl->session = ses;
	status = nfs4_पुनः_स्मृति_slot_table(tbl, ses->bc_attrs.max_reqs, 0);
	अगर (status && tbl->slots == शून्य)
		/* Fore and back channel share a connection so get
		 * both slot tables or neither */
		nfs4_release_session_slot_tables(ses);
	वापस status;
पूर्ण

काष्ठा nfs4_session *nfs4_alloc_session(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs4_session *session;

	session = kzalloc(माप(काष्ठा nfs4_session), GFP_NOFS);
	अगर (!session)
		वापस शून्य;

	nfs4_init_slot_table(&session->fc_slot_table, "ForeChannel Slot table");
	nfs4_init_slot_table(&session->bc_slot_table, "BackChannel Slot table");
	session->session_state = 1<<NFS4_SESSION_INITING;

	session->clp = clp;
	वापस session;
पूर्ण

अटल व्योम nfs4_destroy_session_slot_tables(काष्ठा nfs4_session *session)
अणु
	nfs4_shutकरोwn_slot_table(&session->fc_slot_table);
	nfs4_shutकरोwn_slot_table(&session->bc_slot_table);
पूर्ण

व्योम nfs4_destroy_session(काष्ठा nfs4_session *session)
अणु
	काष्ठा rpc_xprt *xprt;
	स्थिर काष्ठा cred *cred;

	cred = nfs4_get_clid_cred(session->clp);
	nfs4_proc_destroy_session(session, cred);
	put_cred(cred);

	rcu_पढ़ो_lock();
	xprt = rcu_dereference(session->clp->cl_rpcclient->cl_xprt);
	rcu_पढ़ो_unlock();
	dprपूर्णांकk("%s Destroy backchannel for xprt %p\n",
		__func__, xprt);
	xprt_destroy_backchannel(xprt, NFS41_BC_MIN_CALLBACKS);
	nfs4_destroy_session_slot_tables(session);
	kमुक्त(session);
पूर्ण

/*
 * With sessions, the client is not marked पढ़ोy until after a
 * successful EXCHANGE_ID and CREATE_SESSION.
 *
 * Map errors cl_cons_state errors to EPROTONOSUPPORT to indicate
 * other versions of NFS can be tried.
 */
अटल पूर्णांक nfs41_check_session_पढ़ोy(काष्ठा nfs_client *clp)
अणु
	पूर्णांक ret;
	
	अगर (clp->cl_cons_state == NFS_CS_SESSION_INITING) अणु
		ret = nfs4_client_recover_expired_lease(clp);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (clp->cl_cons_state < NFS_CS_READY)
		वापस -EPROTONOSUPPORT;
	smp_rmb();
	वापस 0;
पूर्ण

पूर्णांक nfs4_init_session(काष्ठा nfs_client *clp)
अणु
	अगर (!nfs4_has_session(clp))
		वापस 0;

	clear_bit(NFS4_SESSION_INITING, &clp->cl_session->session_state);
	वापस nfs41_check_session_पढ़ोy(clp);
पूर्ण

पूर्णांक nfs4_init_ds_session(काष्ठा nfs_client *clp, अचिन्हित दीर्घ lease_समय)
अणु
	काष्ठा nfs4_session *session = clp->cl_session;
	पूर्णांक ret;

	spin_lock(&clp->cl_lock);
	अगर (test_and_clear_bit(NFS4_SESSION_INITING, &session->session_state)) अणु
		/*
		 * Do not set NFS_CS_CHECK_LEASE_TIME instead set the
		 * DS lease to be equal to the MDS lease.
		 */
		clp->cl_lease_समय = lease_समय;
		clp->cl_last_renewal = jअगरfies;
	पूर्ण
	spin_unlock(&clp->cl_lock);

	ret = nfs41_check_session_पढ़ोy(clp);
	अगर (ret)
		वापस ret;
	/* Test क्रम the DS role */
	अगर (!is_ds_client(clp))
		वापस -ENODEV;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_init_ds_session);

#पूर्ण_अगर	/* defined(CONFIG_NFS_V4_1) */
