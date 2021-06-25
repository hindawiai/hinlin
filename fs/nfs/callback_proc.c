<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/nfs/callback_proc.c
 *
 * Copyright (C) 2004 Trond Myklebust
 *
 * NFSv4 callback procedures
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/गणित.स>
#समावेश <linux/nfs4.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/types.h>

#समावेश "nfs4_fs.h"
#समावेश "callback.h"
#समावेश "delegation.h"
#समावेश "internal.h"
#समावेश "pnfs.h"
#समावेश "nfs4session.h"
#समावेश "nfs4trace.h"

#घोषणा NFSDBG_FACILITY NFSDBG_CALLBACK

__be32 nfs4_callback_getattr(व्योम *argp, व्योम *resp,
			     काष्ठा cb_process_state *cps)
अणु
	काष्ठा cb_getattrargs *args = argp;
	काष्ठा cb_getattrres *res = resp;
	काष्ठा nfs_delegation *delegation;
	काष्ठा inode *inode;

	res->status = htonl(NFS4ERR_OP_NOT_IN_SESSION);
	अगर (!cps->clp) /* Always set क्रम v4.0. Set in cb_sequence क्रम v4.1 */
		जाओ out;

	res->biपंचांगap[0] = res->biपंचांगap[1] = 0;
	res->status = htonl(NFS4ERR_BADHANDLE);

	dprपूर्णांकk_rcu("NFS: GETATTR callback request from %s\n",
		rpc_peeraddr2str(cps->clp->cl_rpcclient, RPC_DISPLAY_ADDR));

	inode = nfs_delegation_find_inode(cps->clp, &args->fh);
	अगर (IS_ERR(inode)) अणु
		अगर (inode == ERR_PTR(-EAGAIN))
			res->status = htonl(NFS4ERR_DELAY);
		trace_nfs4_cb_getattr(cps->clp, &args->fh, शून्य,
				-ntohl(res->status));
		जाओ out;
	पूर्ण
	rcu_पढ़ो_lock();
	delegation = nfs4_get_valid_delegation(inode);
	अगर (delegation == शून्य || (delegation->type & FMODE_WRITE) == 0)
		जाओ out_iput;
	res->size = i_size_पढ़ो(inode);
	res->change_attr = delegation->change_attr;
	अगर (nfs_have_ग_लिखोbacks(inode))
		res->change_attr++;
	res->स_समय = inode->i_स_समय;
	res->mसमय = inode->i_mसमय;
	res->biपंचांगap[0] = (FATTR4_WORD0_CHANGE|FATTR4_WORD0_SIZE) &
		args->biपंचांगap[0];
	res->biपंचांगap[1] = (FATTR4_WORD1_TIME_METADATA|FATTR4_WORD1_TIME_MODIFY) &
		args->biपंचांगap[1];
	res->status = 0;
out_iput:
	rcu_पढ़ो_unlock();
	trace_nfs4_cb_getattr(cps->clp, &args->fh, inode, -ntohl(res->status));
	nfs_iput_and_deactive(inode);
out:
	dprपूर्णांकk("%s: exit with status = %d\n", __func__, ntohl(res->status));
	वापस res->status;
पूर्ण

__be32 nfs4_callback_recall(व्योम *argp, व्योम *resp,
			    काष्ठा cb_process_state *cps)
अणु
	काष्ठा cb_recallargs *args = argp;
	काष्ठा inode *inode;
	__be32 res;
	
	res = htonl(NFS4ERR_OP_NOT_IN_SESSION);
	अगर (!cps->clp) /* Always set क्रम v4.0. Set in cb_sequence क्रम v4.1 */
		जाओ out;

	dprपूर्णांकk_rcu("NFS: RECALL callback request from %s\n",
		rpc_peeraddr2str(cps->clp->cl_rpcclient, RPC_DISPLAY_ADDR));

	res = htonl(NFS4ERR_BADHANDLE);
	inode = nfs_delegation_find_inode(cps->clp, &args->fh);
	अगर (IS_ERR(inode)) अणु
		अगर (inode == ERR_PTR(-EAGAIN))
			res = htonl(NFS4ERR_DELAY);
		trace_nfs4_cb_recall(cps->clp, &args->fh, शून्य,
				&args->stateid, -ntohl(res));
		जाओ out;
	पूर्ण
	/* Set up a helper thपढ़ो to actually वापस the delegation */
	चयन (nfs_async_inode_वापस_delegation(inode, &args->stateid)) अणु
	हाल 0:
		res = 0;
		अवरोध;
	हाल -ENOENT:
		res = htonl(NFS4ERR_BAD_STATEID);
		अवरोध;
	शेष:
		res = htonl(NFS4ERR_RESOURCE);
	पूर्ण
	trace_nfs4_cb_recall(cps->clp, &args->fh, inode,
			&args->stateid, -ntohl(res));
	nfs_iput_and_deactive(inode);
out:
	dprपूर्णांकk("%s: exit with status = %d\n", __func__, ntohl(res));
	वापस res;
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)

/*
 * Lookup a layout inode by stateid
 *
 * Note: वापसs a refcount on the inode and superblock
 */
अटल काष्ठा inode *nfs_layout_find_inode_by_stateid(काष्ठा nfs_client *clp,
		स्थिर nfs4_stateid *stateid)
	__must_hold(RCU)
अणु
	काष्ठा nfs_server *server;
	काष्ठा inode *inode;
	काष्ठा pnfs_layout_hdr *lo;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link) अणु
		list_क्रम_each_entry_rcu(lo, &server->layouts, plh_layouts) अणु
			अगर (!pnfs_layout_is_valid(lo))
				जारी;
			अगर (!nfs4_stateid_match_other(stateid, &lo->plh_stateid))
				जारी;
			अगर (nfs_sb_active(server->super))
				inode = igrab(lo->plh_inode);
			अन्यथा
				inode = ERR_PTR(-EAGAIN);
			rcu_पढ़ो_unlock();
			अगर (inode)
				वापस inode;
			nfs_sb_deactive(server->super);
			वापस ERR_PTR(-EAGAIN);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ERR_PTR(-ENOENT);
पूर्ण

/*
 * Lookup a layout inode by filehandle.
 *
 * Note: वापसs a refcount on the inode and superblock
 *
 */
अटल काष्ठा inode *nfs_layout_find_inode_by_fh(काष्ठा nfs_client *clp,
		स्थिर काष्ठा nfs_fh *fh)
अणु
	काष्ठा nfs_server *server;
	काष्ठा nfs_inode *nfsi;
	काष्ठा inode *inode;
	काष्ठा pnfs_layout_hdr *lo;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link) अणु
		list_क्रम_each_entry_rcu(lo, &server->layouts, plh_layouts) अणु
			nfsi = NFS_I(lo->plh_inode);
			अगर (nfs_compare_fh(fh, &nfsi->fh))
				जारी;
			अगर (nfsi->layout != lo)
				जारी;
			अगर (nfs_sb_active(server->super))
				inode = igrab(lo->plh_inode);
			अन्यथा
				inode = ERR_PTR(-EAGAIN);
			rcu_पढ़ो_unlock();
			अगर (inode)
				वापस inode;
			nfs_sb_deactive(server->super);
			वापस ERR_PTR(-EAGAIN);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल काष्ठा inode *nfs_layout_find_inode(काष्ठा nfs_client *clp,
		स्थिर काष्ठा nfs_fh *fh,
		स्थिर nfs4_stateid *stateid)
अणु
	काष्ठा inode *inode;

	inode = nfs_layout_find_inode_by_stateid(clp, stateid);
	अगर (inode == ERR_PTR(-ENOENT))
		inode = nfs_layout_find_inode_by_fh(clp, fh);
	वापस inode;
पूर्ण

/*
 * Enक्रमce RFC5661 section 12.5.5.2.1. (Layout Recall and Return Sequencing)
 */
अटल u32 pnfs_check_callback_stateid(काष्ठा pnfs_layout_hdr *lo,
					स्थिर nfs4_stateid *new)
अणु
	u32 oldseq, newseq;

	/* Is the stateid not initialised? */
	अगर (!pnfs_layout_is_valid(lo))
		वापस NFS4ERR_NOMATCHING_LAYOUT;

	/* Mismatched stateid? */
	अगर (!nfs4_stateid_match_other(&lo->plh_stateid, new))
		वापस NFS4ERR_BAD_STATEID;

	newseq = be32_to_cpu(new->seqid);
	/* Are we alपढ़ोy in a layout recall situation? */
	अगर (test_bit(NFS_LAYOUT_RETURN_REQUESTED, &lo->plh_flags) &&
	    lo->plh_वापस_seq != 0) अणु
		अगर (newseq < lo->plh_वापस_seq)
			वापस NFS4ERR_OLD_STATEID;
		अगर (newseq > lo->plh_वापस_seq)
			वापस NFS4ERR_DELAY;
		जाओ out;
	पूर्ण

	/* Check that the stateid matches what we think it should be. */
	oldseq = be32_to_cpu(lo->plh_stateid.seqid);
	अगर (newseq > oldseq + 1)
		वापस NFS4ERR_DELAY;
	/* Crazy server! */
	अगर (newseq <= oldseq)
		वापस NFS4ERR_OLD_STATEID;
out:
	वापस NFS_OK;
पूर्ण

अटल u32 initiate_file_draining(काष्ठा nfs_client *clp,
				  काष्ठा cb_layoutrecallargs *args)
अणु
	काष्ठा inode *ino;
	काष्ठा pnfs_layout_hdr *lo;
	u32 rv = NFS4ERR_NOMATCHING_LAYOUT;
	LIST_HEAD(मुक्त_me_list);

	ino = nfs_layout_find_inode(clp, &args->cbl_fh, &args->cbl_stateid);
	अगर (IS_ERR(ino)) अणु
		अगर (ino == ERR_PTR(-EAGAIN))
			rv = NFS4ERR_DELAY;
		जाओ out_noput;
	पूर्ण

	pnfs_layoutcommit_inode(ino, false);


	spin_lock(&ino->i_lock);
	lo = NFS_I(ino)->layout;
	अगर (!lo) अणु
		spin_unlock(&ino->i_lock);
		जाओ out;
	पूर्ण
	pnfs_get_layout_hdr(lo);
	rv = pnfs_check_callback_stateid(lo, &args->cbl_stateid);
	अगर (rv != NFS_OK)
		जाओ unlock;

	/*
	 * Enक्रमce RFC5661 Section 12.5.5.2.1.5 (Bulk Recall and Return)
	 */
	अगर (test_bit(NFS_LAYOUT_BULK_RECALL, &lo->plh_flags)) अणु
		rv = NFS4ERR_DELAY;
		जाओ unlock;
	पूर्ण

	pnfs_set_layout_stateid(lo, &args->cbl_stateid, शून्य, true);
	चयन (pnfs_mark_matching_lsegs_वापस(lo, &मुक्त_me_list,
				&args->cbl_range,
				be32_to_cpu(args->cbl_stateid.seqid))) अणु
	हाल 0:
	हाल -EBUSY:
		/* There are layout segments that need to be वापसed */
		rv = NFS4_OK;
		अवरोध;
	हाल -ENOENT:
		/* Embrace your क्रमgetfulness! */
		rv = NFS4ERR_NOMATCHING_LAYOUT;

		अगर (NFS_SERVER(ino)->pnfs_curr_ld->वापस_range) अणु
			NFS_SERVER(ino)->pnfs_curr_ld->वापस_range(lo,
				&args->cbl_range);
		पूर्ण
	पूर्ण
unlock:
	spin_unlock(&ino->i_lock);
	pnfs_मुक्त_lseg_list(&मुक्त_me_list);
	/* Free all lsegs that are attached to commit buckets */
	nfs_commit_inode(ino, 0);
	pnfs_put_layout_hdr(lo);
out:
	nfs_iput_and_deactive(ino);
out_noput:
	trace_nfs4_cb_layoutrecall_file(clp, &args->cbl_fh, ino,
			&args->cbl_stateid, -rv);
	वापस rv;
पूर्ण

अटल u32 initiate_bulk_draining(काष्ठा nfs_client *clp,
				  काष्ठा cb_layoutrecallargs *args)
अणु
	पूर्णांक stat;

	अगर (args->cbl_recall_type == RETURN_FSID)
		stat = pnfs_destroy_layouts_byfsid(clp, &args->cbl_fsid, true);
	अन्यथा
		stat = pnfs_destroy_layouts_byclid(clp, true);
	अगर (stat != 0)
		वापस NFS4ERR_DELAY;
	वापस NFS4ERR_NOMATCHING_LAYOUT;
पूर्ण

अटल u32 करो_callback_layoutrecall(काष्ठा nfs_client *clp,
				    काष्ठा cb_layoutrecallargs *args)
अणु
	अगर (args->cbl_recall_type == RETURN_खाता)
		वापस initiate_file_draining(clp, args);
	वापस initiate_bulk_draining(clp, args);
पूर्ण

__be32 nfs4_callback_layoutrecall(व्योम *argp, व्योम *resp,
				  काष्ठा cb_process_state *cps)
अणु
	काष्ठा cb_layoutrecallargs *args = argp;
	u32 res = NFS4ERR_OP_NOT_IN_SESSION;

	अगर (cps->clp)
		res = करो_callback_layoutrecall(cps->clp, args);
	वापस cpu_to_be32(res);
पूर्ण

अटल व्योम pnfs_recall_all_layouts(काष्ठा nfs_client *clp)
अणु
	काष्ठा cb_layoutrecallargs args;

	/* Pretend we got a CB_LAYOUTRECALL(ALL) */
	स_रखो(&args, 0, माप(args));
	args.cbl_recall_type = RETURN_ALL;
	/* FIXME we ignore errors, what should we करो? */
	करो_callback_layoutrecall(clp, &args);
पूर्ण

__be32 nfs4_callback_devicenotअगरy(व्योम *argp, व्योम *resp,
				  काष्ठा cb_process_state *cps)
अणु
	काष्ठा cb_devicenotअगरyargs *args = argp;
	पूर्णांक i;
	__be32 res = 0;
	काष्ठा nfs_client *clp = cps->clp;
	काष्ठा nfs_server *server = शून्य;

	अगर (!clp) अणु
		res = cpu_to_be32(NFS4ERR_OP_NOT_IN_SESSION);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < args->ndevs; i++) अणु
		काष्ठा cb_devicenotअगरyitem *dev = &args->devs[i];

		अगर (!server ||
		    server->pnfs_curr_ld->id != dev->cbd_layout_type) अणु
			rcu_पढ़ो_lock();
			list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link)
				अगर (server->pnfs_curr_ld &&
				    server->pnfs_curr_ld->id == dev->cbd_layout_type) अणु
					rcu_पढ़ो_unlock();
					जाओ found;
				पूर्ण
			rcu_पढ़ो_unlock();
			जारी;
		पूर्ण

	found:
		nfs4_delete_deviceid(server->pnfs_curr_ld, clp, &dev->cbd_dev_id);
	पूर्ण

out:
	kमुक्त(args->devs);
	वापस res;
पूर्ण

/*
 * Validate the sequenceID sent by the server.
 * Return success अगर the sequenceID is one more than what we last saw on
 * this slot, accounting क्रम wraparound.  Increments the slot's sequence.
 *
 * We करोn't yet implement a duplicate request cache, instead we set the
 * back channel ca_maxresponsesize_cached to zero. This is OK क्रम now
 * since we only currently implement idempotent callbacks anyway.
 *
 * We have a single slot backchannel at this समय, so we करोn't bother
 * checking the used_slots bit array on the table.  The lower layer guarantees
 * a single outstanding callback request at a समय.
 */
अटल __be32
validate_seqid(स्थिर काष्ठा nfs4_slot_table *tbl, स्थिर काष्ठा nfs4_slot *slot,
		स्थिर काष्ठा cb_sequenceargs * args)
अणु
	__be32 ret;

	ret = cpu_to_be32(NFS4ERR_BADSLOT);
	अगर (args->csa_slotid > tbl->server_highest_slotid)
		जाओ out_err;

	/* Replay */
	अगर (args->csa_sequenceid == slot->seq_nr) अणु
		ret = cpu_to_be32(NFS4ERR_DELAY);
		अगर (nfs4_test_locked_slot(tbl, slot->slot_nr))
			जाओ out_err;

		/* Signal process_op to set this error on next op */
		ret = cpu_to_be32(NFS4ERR_RETRY_UNCACHED_REP);
		अगर (args->csa_cachethis == 0)
			जाओ out_err;

		/* Liar! We never allowed you to set csa_cachethis != 0 */
		ret = cpu_to_be32(NFS4ERR_SEQ_FALSE_RETRY);
		जाओ out_err;
	पूर्ण

	/* Note: wraparound relies on seq_nr being of type u32 */
	/* Misordered request */
	ret = cpu_to_be32(NFS4ERR_SEQ_MISORDERED);
	अगर (args->csa_sequenceid != slot->seq_nr + 1)
		जाओ out_err;

	वापस cpu_to_be32(NFS4_OK);

out_err:
	trace_nfs4_cb_seqid_err(args, ret);
	वापस ret;
पूर्ण

/*
 * For each referring call triple, check the session's slot table क्रम
 * a match.  If the slot is in use and the sequence numbers match, the
 * client is still रुकोing क्रम a response to the original request.
 */
अटल पूर्णांक referring_call_exists(काष्ठा nfs_client *clp,
				  uपूर्णांक32_t nrclists,
				  काष्ठा referring_call_list *rclists,
				  spinlock_t *lock)
	__releases(lock)
	__acquires(lock)
अणु
	पूर्णांक status = 0;
	पूर्णांक i, j;
	काष्ठा nfs4_session *session;
	काष्ठा nfs4_slot_table *tbl;
	काष्ठा referring_call_list *rclist;
	काष्ठा referring_call *ref;

	/*
	 * XXX When client trunking is implemented, this becomes
	 * a session lookup from within the loop
	 */
	session = clp->cl_session;
	tbl = &session->fc_slot_table;

	क्रम (i = 0; i < nrclists; i++) अणु
		rclist = &rclists[i];
		अगर (स_भेद(session->sess_id.data,
			   rclist->rcl_sessionid.data,
			   NFS4_MAX_SESSIONID_LEN) != 0)
			जारी;

		क्रम (j = 0; j < rclist->rcl_nrefcalls; j++) अणु
			ref = &rclist->rcl_refcalls[j];
			spin_unlock(lock);
			status = nfs4_slot_रुको_on_seqid(tbl, ref->rc_slotid,
					ref->rc_sequenceid, HZ >> 1) < 0;
			spin_lock(lock);
			अगर (status)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस status;
पूर्ण

__be32 nfs4_callback_sequence(व्योम *argp, व्योम *resp,
			      काष्ठा cb_process_state *cps)
अणु
	काष्ठा cb_sequenceargs *args = argp;
	काष्ठा cb_sequenceres *res = resp;
	काष्ठा nfs4_slot_table *tbl;
	काष्ठा nfs4_slot *slot;
	काष्ठा nfs_client *clp;
	पूर्णांक i;
	__be32 status = htonl(NFS4ERR_BADSESSION);

	clp = nfs4_find_client_sessionid(cps->net, args->csa_addr,
					 &args->csa_sessionid, cps->minorversion);
	अगर (clp == शून्य)
		जाओ out;

	अगर (!(clp->cl_session->flags & SESSION4_BACK_CHAN))
		जाओ out;

	tbl = &clp->cl_session->bc_slot_table;

	/* Set up res beक्रमe grabbing the spinlock */
	स_नकल(&res->csr_sessionid, &args->csa_sessionid,
	       माप(res->csr_sessionid));
	res->csr_sequenceid = args->csa_sequenceid;
	res->csr_slotid = args->csa_slotid;

	spin_lock(&tbl->slot_tbl_lock);
	/* state manager is resetting the session */
	अगर (test_bit(NFS4_SLOT_TBL_DRAINING, &tbl->slot_tbl_state)) अणु
		status = htonl(NFS4ERR_DELAY);
		/* Return NFS4ERR_BADSESSION अगर we're draining the session
		 * in order to reset it.
		 */
		अगर (test_bit(NFS4CLNT_SESSION_RESET, &clp->cl_state))
			status = htonl(NFS4ERR_BADSESSION);
		जाओ out_unlock;
	पूर्ण

	status = htonl(NFS4ERR_BADSLOT);
	slot = nfs4_lookup_slot(tbl, args->csa_slotid);
	अगर (IS_ERR(slot))
		जाओ out_unlock;

	res->csr_highestslotid = tbl->server_highest_slotid;
	res->csr_target_highestslotid = tbl->target_highest_slotid;

	status = validate_seqid(tbl, slot, args);
	अगर (status)
		जाओ out_unlock;
	अगर (!nfs4_try_to_lock_slot(tbl, slot)) अणु
		status = htonl(NFS4ERR_DELAY);
		जाओ out_unlock;
	पूर्ण
	cps->slot = slot;

	/* The ca_maxresponsesize_cached is 0 with no DRC */
	अगर (args->csa_cachethis != 0) अणु
		status = htonl(NFS4ERR_REP_TOO_BIG_TO_CACHE);
		जाओ out_unlock;
	पूर्ण

	/*
	 * Check क्रम pending referring calls.  If a match is found, a
	 * related callback was received beक्रमe the response to the original
	 * call.
	 */
	अगर (referring_call_exists(clp, args->csa_nrclists, args->csa_rclists,
				&tbl->slot_tbl_lock) < 0) अणु
		status = htonl(NFS4ERR_DELAY);
		जाओ out_unlock;
	पूर्ण

	/*
	 * RFC5661 20.9.3
	 * If CB_SEQUENCE वापसs an error, then the state of the slot
	 * (sequence ID, cached reply) MUST NOT change.
	 */
	slot->seq_nr = args->csa_sequenceid;
out_unlock:
	spin_unlock(&tbl->slot_tbl_lock);

out:
	cps->clp = clp; /* put in nfs4_callback_compound */
	क्रम (i = 0; i < args->csa_nrclists; i++)
		kमुक्त(args->csa_rclists[i].rcl_refcalls);
	kमुक्त(args->csa_rclists);

	अगर (status == htonl(NFS4ERR_RETRY_UNCACHED_REP)) अणु
		cps->drc_status = status;
		status = 0;
	पूर्ण अन्यथा
		res->csr_status = status;

	trace_nfs4_cb_sequence(args, res, status);
	वापस status;
पूर्ण

अटल bool
validate_biपंचांगap_values(अचिन्हित पूर्णांक mask)
अणु
	वापस (mask & ~RCA4_TYPE_MASK_ALL) == 0;
पूर्ण

__be32 nfs4_callback_recallany(व्योम *argp, व्योम *resp,
			       काष्ठा cb_process_state *cps)
अणु
	काष्ठा cb_recallanyargs *args = argp;
	__be32 status;
	भ_शेषe_t flags = 0;
	bool schedule_manager = false;

	status = cpu_to_be32(NFS4ERR_OP_NOT_IN_SESSION);
	अगर (!cps->clp) /* set in cb_sequence */
		जाओ out;

	dprपूर्णांकk_rcu("NFS: RECALL_ANY callback request from %s\n",
		rpc_peeraddr2str(cps->clp->cl_rpcclient, RPC_DISPLAY_ADDR));

	status = cpu_to_be32(NFS4ERR_INVAL);
	अगर (!validate_biपंचांगap_values(args->craa_type_mask))
		जाओ out;

	status = cpu_to_be32(NFS4_OK);
	अगर (args->craa_type_mask & BIT(RCA4_TYPE_MASK_RDATA_DLG))
		flags = FMODE_READ;
	अगर (args->craa_type_mask & BIT(RCA4_TYPE_MASK_WDATA_DLG))
		flags |= FMODE_WRITE;
	अगर (flags)
		nfs_expire_unused_delegation_types(cps->clp, flags);

	अगर (args->craa_type_mask & BIT(RCA4_TYPE_MASK_खाता_LAYOUT))
		pnfs_recall_all_layouts(cps->clp);

	अगर (args->craa_type_mask & BIT(PNFS_FF_RCA4_TYPE_MASK_READ)) अणु
		set_bit(NFS4CLNT_RECALL_ANY_LAYOUT_READ, &cps->clp->cl_state);
		schedule_manager = true;
	पूर्ण
	अगर (args->craa_type_mask & BIT(PNFS_FF_RCA4_TYPE_MASK_RW)) अणु
		set_bit(NFS4CLNT_RECALL_ANY_LAYOUT_RW, &cps->clp->cl_state);
		schedule_manager = true;
	पूर्ण
	अगर (schedule_manager)
		nfs4_schedule_state_manager(cps->clp);

out:
	dprपूर्णांकk("%s: exit with status = %d\n", __func__, ntohl(status));
	वापस status;
पूर्ण

/* Reduce the क्रमe channel's max_slots to the target value */
__be32 nfs4_callback_recallslot(व्योम *argp, व्योम *resp,
				काष्ठा cb_process_state *cps)
अणु
	काष्ठा cb_recallslotargs *args = argp;
	काष्ठा nfs4_slot_table *fc_tbl;
	__be32 status;

	status = htonl(NFS4ERR_OP_NOT_IN_SESSION);
	अगर (!cps->clp) /* set in cb_sequence */
		जाओ out;

	dprपूर्णांकk_rcu("NFS: CB_RECALL_SLOT request from %s target highest slotid %u\n",
		rpc_peeraddr2str(cps->clp->cl_rpcclient, RPC_DISPLAY_ADDR),
		args->crsa_target_highest_slotid);

	fc_tbl = &cps->clp->cl_session->fc_slot_table;

	status = htonl(NFS4_OK);

	nfs41_set_target_slotid(fc_tbl, args->crsa_target_highest_slotid);
	nfs41_notअगरy_server(cps->clp);
out:
	dprपूर्णांकk("%s: exit with status = %d\n", __func__, ntohl(status));
	वापस status;
पूर्ण

__be32 nfs4_callback_notअगरy_lock(व्योम *argp, व्योम *resp,
				 काष्ठा cb_process_state *cps)
अणु
	काष्ठा cb_notअगरy_lock_args *args = argp;

	अगर (!cps->clp) /* set in cb_sequence */
		वापस htonl(NFS4ERR_OP_NOT_IN_SESSION);

	dprपूर्णांकk_rcu("NFS: CB_NOTIFY_LOCK request from %s\n",
		rpc_peeraddr2str(cps->clp->cl_rpcclient, RPC_DISPLAY_ADDR));

	/* Don't wake anybody अगर the string looked bogus */
	अगर (args->cbnl_valid)
		__wake_up(&cps->clp->cl_lock_रुकोq, TASK_NORMAL, 0, args);

	वापस htonl(NFS4_OK);
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */
#अगर_घोषित CONFIG_NFS_V4_2
अटल व्योम nfs4_copy_cb_args(काष्ठा nfs4_copy_state *cp_state,
				काष्ठा cb_offloadargs *args)
अणु
	cp_state->count = args->wr_count;
	cp_state->error = args->error;
	अगर (!args->error) अणु
		cp_state->verf.committed = args->wr_ग_लिखोverf.committed;
		स_नकल(&cp_state->verf.verअगरier.data[0],
			&args->wr_ग_लिखोverf.verअगरier.data[0],
			NFS4_VERIFIER_SIZE);
	पूर्ण
पूर्ण

__be32 nfs4_callback_offload(व्योम *data, व्योम *dummy,
			     काष्ठा cb_process_state *cps)
अणु
	काष्ठा cb_offloadargs *args = data;
	काष्ठा nfs_server *server;
	काष्ठा nfs4_copy_state *copy, *पंचांगp_copy;
	bool found = false;

	copy = kzalloc(माप(काष्ठा nfs4_copy_state), GFP_NOFS);
	अगर (!copy)
		वापस htonl(NFS4ERR_SERVERFAULT);

	spin_lock(&cps->clp->cl_lock);
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &cps->clp->cl_superblocks,
				client_link) अणु
		list_क्रम_each_entry(पंचांगp_copy, &server->ss_copies, copies) अणु
			अगर (स_भेद(args->coa_stateid.other,
					पंचांगp_copy->stateid.other,
					माप(args->coa_stateid.other)))
				जारी;
			nfs4_copy_cb_args(पंचांगp_copy, args);
			complete(&पंचांगp_copy->completion);
			found = true;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	अगर (!found) अणु
		स_नकल(&copy->stateid, &args->coa_stateid, NFS4_STATEID_SIZE);
		nfs4_copy_cb_args(copy, args);
		list_add_tail(&copy->copies, &cps->clp->pending_cb_stateids);
	पूर्ण अन्यथा
		kमुक्त(copy);
	spin_unlock(&cps->clp->cl_lock);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */
