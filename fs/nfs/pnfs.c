<शैली गुरु>
/*
 *  pNFS functions to call and manage layout drivers.
 *
 *  Copyright (c) 2002 [year of first खुलाation]
 *  The Regents of the University of Michigan
 *  All Rights Reserved
 *
 *  Dean Hildebअक्रम <dhildebz@umich.edu>
 *
 *  Permission is granted to use, copy, create derivative works, and
 *  redistribute this software and such derivative works क्रम any purpose,
 *  so दीर्घ as the name of the University of Michigan is not used in
 *  any advertising or खुलाity pertaining to the use or distribution
 *  of this software without specअगरic, written prior authorization. If
 *  the above copyright notice or any other identअगरication of the
 *  University of Michigan is included in any copy of any portion of
 *  this software, then the disclaimer below must also be included.
 *
 *  This software is provided as is, without representation or warranty
 *  of any kind either express or implied, including without limitation
 *  the implied warranties of merchantability, fitness क्रम a particular
 *  purpose, or noninfringement.  The Regents of the University of
 *  Michigan shall not be liable क्रम any damages, including special,
 *  indirect, incidental, or consequential damages, with respect to any
 *  claim arising out of or in connection with the use of the software,
 *  even अगर it has been or is hereafter advised of the possibility of
 *  such damages.
 */

#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_page.h>
#समावेश <linux/module.h>
#समावेश <linux/sort.h>
#समावेश "internal.h"
#समावेश "pnfs.h"
#समावेश "iostat.h"
#समावेश "nfs4trace.h"
#समावेश "delegation.h"
#समावेश "nfs42.h"
#समावेश "nfs4_fs.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_PNFS
#घोषणा PNFS_LAYOUTGET_RETRY_TIMEOUT (120*HZ)

/* Locking:
 *
 * pnfs_spinlock:
 *      protects pnfs_modules_tbl.
 */
अटल DEFINE_SPINLOCK(pnfs_spinlock);

/*
 * pnfs_modules_tbl holds all pnfs modules
 */
अटल LIST_HEAD(pnfs_modules_tbl);

अटल व्योम pnfs_layoutवापस_beक्रमe_put_layout_hdr(काष्ठा pnfs_layout_hdr *lo);
अटल व्योम pnfs_मुक्त_वापसed_lsegs(काष्ठा pnfs_layout_hdr *lo,
		काष्ठा list_head *मुक्त_me,
		स्थिर काष्ठा pnfs_layout_range *range,
		u32 seq);
अटल bool pnfs_lseg_dec_and_हटाओ_zero(काष्ठा pnfs_layout_segment *lseg,
		                काष्ठा list_head *पंचांगp_list);

/* Return the रेजिस्टरed pnfs layout driver module matching given id */
अटल काष्ठा pnfs_layoutdriver_type *
find_pnfs_driver_locked(u32 id)
अणु
	काष्ठा pnfs_layoutdriver_type *local;

	list_क्रम_each_entry(local, &pnfs_modules_tbl, pnfs_tblid)
		अगर (local->id == id)
			जाओ out;
	local = शून्य;
out:
	dprपूर्णांकk("%s: Searching for id %u, found %p\n", __func__, id, local);
	वापस local;
पूर्ण

अटल काष्ठा pnfs_layoutdriver_type *
find_pnfs_driver(u32 id)
अणु
	काष्ठा pnfs_layoutdriver_type *local;

	spin_lock(&pnfs_spinlock);
	local = find_pnfs_driver_locked(id);
	अगर (local != शून्य && !try_module_get(local->owner)) अणु
		dprपूर्णांकk("%s: Could not grab reference on module\n", __func__);
		local = शून्य;
	पूर्ण
	spin_unlock(&pnfs_spinlock);
	वापस local;
पूर्ण

व्योम
unset_pnfs_layoutdriver(काष्ठा nfs_server *nfss)
अणु
	अगर (nfss->pnfs_curr_ld) अणु
		अगर (nfss->pnfs_curr_ld->clear_layoutdriver)
			nfss->pnfs_curr_ld->clear_layoutdriver(nfss);
		/* Decrement the MDS count. Purge the deviceid cache अगर zero */
		अगर (atomic_dec_and_test(&nfss->nfs_client->cl_mds_count))
			nfs4_deviceid_purge_client(nfss->nfs_client);
		module_put(nfss->pnfs_curr_ld->owner);
	पूर्ण
	nfss->pnfs_curr_ld = शून्य;
पूर्ण

/*
 * When the server sends a list of layout types, we choose one in the order
 * given in the list below.
 *
 * FIXME: should this list be configurable in some fashion? module param?
 * 	  mount option? something अन्यथा?
 */
अटल स्थिर u32 ld_prefs[] = अणु
	LAYOUT_SCSI,
	LAYOUT_BLOCK_VOLUME,
	LAYOUT_OSD2_OBJECTS,
	LAYOUT_FLEX_खाताS,
	LAYOUT_NFSV4_1_खाताS,
	0
पूर्ण;

अटल पूर्णांक
ld_cmp(स्थिर व्योम *e1, स्थिर व्योम *e2)
अणु
	u32 ld1 = *((u32 *)e1);
	u32 ld2 = *((u32 *)e2);
	पूर्णांक i;

	क्रम (i = 0; ld_prefs[i] != 0; i++) अणु
		अगर (ld1 == ld_prefs[i])
			वापस -1;

		अगर (ld2 == ld_prefs[i])
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Try to set the server's pnfs module to the pnfs layout type specअगरied by id.
 * Currently only one pNFS layout driver per fileप्रणाली is supported.
 *
 * @ids array of layout types supported by MDS.
 */
व्योम
set_pnfs_layoutdriver(काष्ठा nfs_server *server, स्थिर काष्ठा nfs_fh *mntfh,
		      काष्ठा nfs_fsinfo *fsinfo)
अणु
	काष्ठा pnfs_layoutdriver_type *ld_type = शून्य;
	u32 id;
	पूर्णांक i;

	अगर (fsinfo->nlayouttypes == 0)
		जाओ out_no_driver;
	अगर (!(server->nfs_client->cl_exchange_flags &
		 (EXCHGID4_FLAG_USE_NON_PNFS | EXCHGID4_FLAG_USE_PNFS_MDS))) अणु
		prपूर्णांकk(KERN_ERR "NFS: %s: cl_exchange_flags 0x%x\n",
			__func__, server->nfs_client->cl_exchange_flags);
		जाओ out_no_driver;
	पूर्ण

	sort(fsinfo->layouttype, fsinfo->nlayouttypes,
		माप(*fsinfo->layouttype), ld_cmp, शून्य);

	क्रम (i = 0; i < fsinfo->nlayouttypes; i++) अणु
		id = fsinfo->layouttype[i];
		ld_type = find_pnfs_driver(id);
		अगर (!ld_type) अणु
			request_module("%s-%u", LAYOUT_NFSV4_1_MODULE_PREFIX,
					id);
			ld_type = find_pnfs_driver(id);
		पूर्ण
		अगर (ld_type)
			अवरोध;
	पूर्ण

	अगर (!ld_type) अणु
		dprपूर्णांकk("%s: No pNFS module found!\n", __func__);
		जाओ out_no_driver;
	पूर्ण

	server->pnfs_curr_ld = ld_type;
	अगर (ld_type->set_layoutdriver
	    && ld_type->set_layoutdriver(server, mntfh)) अणु
		prपूर्णांकk(KERN_ERR "NFS: %s: Error initializing pNFS layout "
			"driver %u.\n", __func__, id);
		module_put(ld_type->owner);
		जाओ out_no_driver;
	पूर्ण
	/* Bump the MDS count */
	atomic_inc(&server->nfs_client->cl_mds_count);

	dprपूर्णांकk("%s: pNFS module for %u set\n", __func__, id);
	वापस;

out_no_driver:
	dprपूर्णांकk("%s: Using NFSv4 I/O\n", __func__);
	server->pnfs_curr_ld = शून्य;
पूर्ण

पूर्णांक
pnfs_रेजिस्टर_layoutdriver(काष्ठा pnfs_layoutdriver_type *ld_type)
अणु
	पूर्णांक status = -EINVAL;
	काष्ठा pnfs_layoutdriver_type *पंचांगp;

	अगर (ld_type->id == 0) अणु
		prपूर्णांकk(KERN_ERR "NFS: %s id 0 is reserved\n", __func__);
		वापस status;
	पूर्ण
	अगर (!ld_type->alloc_lseg || !ld_type->मुक्त_lseg) अणु
		prपूर्णांकk(KERN_ERR "NFS: %s Layout driver must provide "
		       "alloc_lseg and free_lseg.\n", __func__);
		वापस status;
	पूर्ण

	spin_lock(&pnfs_spinlock);
	पंचांगp = find_pnfs_driver_locked(ld_type->id);
	अगर (!पंचांगp) अणु
		list_add(&ld_type->pnfs_tblid, &pnfs_modules_tbl);
		status = 0;
		dprपूर्णांकk("%s Registering id:%u name:%s\n", __func__, ld_type->id,
			ld_type->name);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "NFS: %s Module with id %d already loaded!\n",
			__func__, ld_type->id);
	पूर्ण
	spin_unlock(&pnfs_spinlock);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_रेजिस्टर_layoutdriver);

व्योम
pnfs_unरेजिस्टर_layoutdriver(काष्ठा pnfs_layoutdriver_type *ld_type)
अणु
	dprपूर्णांकk("%s Deregistering id:%u\n", __func__, ld_type->id);
	spin_lock(&pnfs_spinlock);
	list_del(&ld_type->pnfs_tblid);
	spin_unlock(&pnfs_spinlock);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_unरेजिस्टर_layoutdriver);

/*
 * pNFS client layout cache
 */

/* Need to hold i_lock अगर caller करोes not alपढ़ोy hold reference */
व्योम
pnfs_get_layout_hdr(काष्ठा pnfs_layout_hdr *lo)
अणु
	refcount_inc(&lo->plh_refcount);
पूर्ण

अटल काष्ठा pnfs_layout_hdr *
pnfs_alloc_layout_hdr(काष्ठा inode *ino, gfp_t gfp_flags)
अणु
	काष्ठा pnfs_layoutdriver_type *ld = NFS_SERVER(ino)->pnfs_curr_ld;
	वापस ld->alloc_layout_hdr(ino, gfp_flags);
पूर्ण

अटल व्योम
pnfs_मुक्त_layout_hdr(काष्ठा pnfs_layout_hdr *lo)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(lo->plh_inode);
	काष्ठा pnfs_layoutdriver_type *ld = server->pnfs_curr_ld;

	अगर (test_and_clear_bit(NFS_LAYOUT_HASHED, &lo->plh_flags)) अणु
		काष्ठा nfs_client *clp = server->nfs_client;

		spin_lock(&clp->cl_lock);
		list_del_rcu(&lo->plh_layouts);
		spin_unlock(&clp->cl_lock);
	पूर्ण
	put_cred(lo->plh_lc_cred);
	वापस ld->मुक्त_layout_hdr(lo);
पूर्ण

अटल व्योम
pnfs_detach_layout_hdr(काष्ठा pnfs_layout_hdr *lo)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(lo->plh_inode);
	dprपूर्णांकk("%s: freeing layout cache %p\n", __func__, lo);
	nfsi->layout = शून्य;
	/* Reset MDS Threshold I/O counters */
	nfsi->ग_लिखो_io = 0;
	nfsi->पढ़ो_io = 0;
पूर्ण

व्योम
pnfs_put_layout_hdr(काष्ठा pnfs_layout_hdr *lo)
अणु
	काष्ठा inode *inode;
	अचिन्हित दीर्घ i_state;

	अगर (!lo)
		वापस;
	inode = lo->plh_inode;
	pnfs_layoutवापस_beक्रमe_put_layout_hdr(lo);

	अगर (refcount_dec_and_lock(&lo->plh_refcount, &inode->i_lock)) अणु
		अगर (!list_empty(&lo->plh_segs))
			WARN_ONCE(1, "NFS: BUG unfreed layout segments.\n");
		pnfs_detach_layout_hdr(lo);
		i_state = inode->i_state;
		spin_unlock(&inode->i_lock);
		pnfs_मुक्त_layout_hdr(lo);
		/* Notअगरy pnfs_destroy_layout_final() that we're करोne */
		अगर (i_state & (I_FREEING | I_CLEAR))
			wake_up_var(lo);
	पूर्ण
पूर्ण

अटल काष्ठा inode *
pnfs_grab_inode_layout_hdr(काष्ठा pnfs_layout_hdr *lo)
अणु
	काष्ठा inode *inode = igrab(lo->plh_inode);
	अगर (inode)
		वापस inode;
	set_bit(NFS_LAYOUT_INODE_FREEING, &lo->plh_flags);
	वापस शून्य;
पूर्ण

/*
 * Compare 2 layout stateid sequence ids, to see which is newer,
 * taking पूर्णांकo account wraparound issues.
 */
अटल bool pnfs_seqid_is_newer(u32 s1, u32 s2)
अणु
	वापस (s32)(s1 - s2) > 0;
पूर्ण

अटल व्योम pnfs_barrier_update(काष्ठा pnfs_layout_hdr *lo, u32 newseq)
अणु
	अगर (pnfs_seqid_is_newer(newseq, lo->plh_barrier))
		lo->plh_barrier = newseq;
पूर्ण

अटल व्योम
pnfs_set_plh_वापस_info(काष्ठा pnfs_layout_hdr *lo, क्रमागत pnfs_iomode iomode,
			 u32 seq)
अणु
	अगर (lo->plh_वापस_iomode != 0 && lo->plh_वापस_iomode != iomode)
		iomode = IOMODE_ANY;
	lo->plh_वापस_iomode = iomode;
	set_bit(NFS_LAYOUT_RETURN_REQUESTED, &lo->plh_flags);
	अगर (seq != 0) अणु
		WARN_ON_ONCE(lo->plh_वापस_seq != 0 && lo->plh_वापस_seq != seq);
		lo->plh_वापस_seq = seq;
		pnfs_barrier_update(lo, seq);
	पूर्ण
पूर्ण

अटल व्योम
pnfs_clear_layoutवापस_info(काष्ठा pnfs_layout_hdr *lo)
अणु
	काष्ठा pnfs_layout_segment *lseg;
	lo->plh_वापस_iomode = 0;
	lo->plh_वापस_seq = 0;
	clear_bit(NFS_LAYOUT_RETURN_REQUESTED, &lo->plh_flags);
	list_क्रम_each_entry(lseg, &lo->plh_segs, pls_list) अणु
		अगर (!test_bit(NFS_LSEG_LAYOUTRETURN, &lseg->pls_flags))
			जारी;
		pnfs_set_plh_वापस_info(lo, lseg->pls_range.iomode, 0);
	पूर्ण
पूर्ण

अटल व्योम pnfs_clear_layoutवापस_रुकोbit(काष्ठा pnfs_layout_hdr *lo)
अणु
	clear_bit_unlock(NFS_LAYOUT_RETURN, &lo->plh_flags);
	clear_bit(NFS_LAYOUT_RETURN_LOCK, &lo->plh_flags);
	smp_mb__after_atomic();
	wake_up_bit(&lo->plh_flags, NFS_LAYOUT_RETURN);
	rpc_wake_up(&NFS_SERVER(lo->plh_inode)->roc_rpcरुकोq);
पूर्ण

अटल व्योम
pnfs_clear_lseg_state(काष्ठा pnfs_layout_segment *lseg,
		काष्ठा list_head *मुक्त_me)
अणु
	clear_bit(NFS_LSEG_ROC, &lseg->pls_flags);
	clear_bit(NFS_LSEG_LAYOUTRETURN, &lseg->pls_flags);
	अगर (test_and_clear_bit(NFS_LSEG_VALID, &lseg->pls_flags))
		pnfs_lseg_dec_and_हटाओ_zero(lseg, मुक्त_me);
	अगर (test_and_clear_bit(NFS_LSEG_LAYOUTCOMMIT, &lseg->pls_flags))
		pnfs_lseg_dec_and_हटाओ_zero(lseg, मुक्त_me);
पूर्ण

/*
 * Update the seqid of a layout stateid after receiving
 * NFS4ERR_OLD_STATEID
 */
bool nfs4_layout_refresh_old_stateid(nfs4_stateid *dst,
		काष्ठा pnfs_layout_range *dst_range,
		काष्ठा inode *inode)
अणु
	काष्ठा pnfs_layout_hdr *lo;
	काष्ठा pnfs_layout_range range = अणु
		.iomode = IOMODE_ANY,
		.offset = 0,
		.length = NFS4_MAX_UINT64,
	पूर्ण;
	bool ret = false;
	LIST_HEAD(head);
	पूर्णांक err;

	spin_lock(&inode->i_lock);
	lo = NFS_I(inode)->layout;
	अगर (lo &&  pnfs_layout_is_valid(lo) &&
	    nfs4_stateid_match_other(dst, &lo->plh_stateid)) अणु
		/* Is our call using the most recent seqid? If so, bump it */
		अगर (!nfs4_stateid_is_newer(&lo->plh_stateid, dst)) अणु
			nfs4_stateid_seqid_inc(dst);
			ret = true;
			जाओ out;
		पूर्ण
		/* Try to update the seqid to the most recent */
		err = pnfs_mark_matching_lsegs_वापस(lo, &head, &range, 0);
		अगर (err != -EBUSY) अणु
			dst->seqid = lo->plh_stateid.seqid;
			*dst_range = range;
			ret = true;
		पूर्ण
	पूर्ण
out:
	spin_unlock(&inode->i_lock);
	pnfs_मुक्त_lseg_list(&head);
	वापस ret;
पूर्ण

/*
 * Mark a pnfs_layout_hdr and all associated layout segments as invalid
 *
 * In order to जारी using the pnfs_layout_hdr, a full recovery
 * is required.
 * Note that caller must hold inode->i_lock.
 */
पूर्णांक
pnfs_mark_layout_stateid_invalid(काष्ठा pnfs_layout_hdr *lo,
		काष्ठा list_head *lseg_list)
अणु
	काष्ठा pnfs_layout_range range = अणु
		.iomode = IOMODE_ANY,
		.offset = 0,
		.length = NFS4_MAX_UINT64,
	पूर्ण;
	काष्ठा pnfs_layout_segment *lseg, *next;

	set_bit(NFS_LAYOUT_INVALID_STID, &lo->plh_flags);
	list_क्रम_each_entry_safe(lseg, next, &lo->plh_segs, pls_list)
		pnfs_clear_lseg_state(lseg, lseg_list);
	pnfs_clear_layoutवापस_info(lo);
	pnfs_मुक्त_वापसed_lsegs(lo, lseg_list, &range, 0);
	अगर (test_bit(NFS_LAYOUT_RETURN, &lo->plh_flags) &&
	    !test_and_set_bit(NFS_LAYOUT_RETURN_LOCK, &lo->plh_flags))
		pnfs_clear_layoutवापस_रुकोbit(lo);
	वापस !list_empty(&lo->plh_segs);
पूर्ण

अटल पूर्णांक
pnfs_iomode_to_fail_bit(u32 iomode)
अणु
	वापस iomode == IOMODE_RW ?
		NFS_LAYOUT_RW_FAILED : NFS_LAYOUT_RO_FAILED;
पूर्ण

अटल व्योम
pnfs_layout_set_fail_bit(काष्ठा pnfs_layout_hdr *lo, पूर्णांक fail_bit)
अणु
	lo->plh_retry_बारtamp = jअगरfies;
	अगर (!test_and_set_bit(fail_bit, &lo->plh_flags))
		refcount_inc(&lo->plh_refcount);
पूर्ण

अटल व्योम
pnfs_layout_clear_fail_bit(काष्ठा pnfs_layout_hdr *lo, पूर्णांक fail_bit)
अणु
	अगर (test_and_clear_bit(fail_bit, &lo->plh_flags))
		refcount_dec(&lo->plh_refcount);
पूर्ण

अटल व्योम
pnfs_layout_io_set_failed(काष्ठा pnfs_layout_hdr *lo, u32 iomode)
अणु
	काष्ठा inode *inode = lo->plh_inode;
	काष्ठा pnfs_layout_range range = अणु
		.iomode = iomode,
		.offset = 0,
		.length = NFS4_MAX_UINT64,
	पूर्ण;
	LIST_HEAD(head);

	spin_lock(&inode->i_lock);
	pnfs_layout_set_fail_bit(lo, pnfs_iomode_to_fail_bit(iomode));
	pnfs_mark_matching_lsegs_invalid(lo, &head, &range, 0);
	spin_unlock(&inode->i_lock);
	pnfs_मुक्त_lseg_list(&head);
	dprपूर्णांकk("%s Setting layout IOMODE_%s fail bit\n", __func__,
			iomode == IOMODE_RW ?  "RW" : "READ");
पूर्ण

अटल bool
pnfs_layout_io_test_failed(काष्ठा pnfs_layout_hdr *lo, u32 iomode)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक fail_bit = pnfs_iomode_to_fail_bit(iomode);

	अगर (test_bit(fail_bit, &lo->plh_flags) == 0)
		वापस false;
	end = jअगरfies;
	start = end - PNFS_LAYOUTGET_RETRY_TIMEOUT;
	अगर (!समय_in_range(lo->plh_retry_बारtamp, start, end)) अणु
		/* It is समय to retry the failed layoutमाला_लो */
		pnfs_layout_clear_fail_bit(lo, fail_bit);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम
pnfs_init_lseg(काष्ठा pnfs_layout_hdr *lo, काष्ठा pnfs_layout_segment *lseg,
		स्थिर काष्ठा pnfs_layout_range *range,
		स्थिर nfs4_stateid *stateid)
अणु
	INIT_LIST_HEAD(&lseg->pls_list);
	INIT_LIST_HEAD(&lseg->pls_lc_list);
	INIT_LIST_HEAD(&lseg->pls_commits);
	refcount_set(&lseg->pls_refcount, 1);
	set_bit(NFS_LSEG_VALID, &lseg->pls_flags);
	lseg->pls_layout = lo;
	lseg->pls_range = *range;
	lseg->pls_seq = be32_to_cpu(stateid->seqid);
पूर्ण

अटल व्योम pnfs_मुक्त_lseg(काष्ठा pnfs_layout_segment *lseg)
अणु
	अगर (lseg != शून्य) अणु
		काष्ठा inode *inode = lseg->pls_layout->plh_inode;
		NFS_SERVER(inode)->pnfs_curr_ld->मुक्त_lseg(lseg);
	पूर्ण
पूर्ण

अटल व्योम
pnfs_layout_हटाओ_lseg(काष्ठा pnfs_layout_hdr *lo,
		काष्ठा pnfs_layout_segment *lseg)
अणु
	WARN_ON(test_bit(NFS_LSEG_VALID, &lseg->pls_flags));
	list_del_init(&lseg->pls_list);
	/* Matched by pnfs_get_layout_hdr in pnfs_layout_insert_lseg */
	refcount_dec(&lo->plh_refcount);
	अगर (test_bit(NFS_LSEG_LAYOUTRETURN, &lseg->pls_flags))
		वापस;
	अगर (list_empty(&lo->plh_segs) &&
	    !test_bit(NFS_LAYOUT_RETURN_REQUESTED, &lo->plh_flags) &&
	    !test_bit(NFS_LAYOUT_RETURN, &lo->plh_flags)) अणु
		अगर (atomic_पढ़ो(&lo->plh_outstanding) == 0)
			set_bit(NFS_LAYOUT_INVALID_STID, &lo->plh_flags);
		clear_bit(NFS_LAYOUT_BULK_RECALL, &lo->plh_flags);
	पूर्ण
पूर्ण

अटल bool
pnfs_cache_lseg_क्रम_layoutवापस(काष्ठा pnfs_layout_hdr *lo,
		काष्ठा pnfs_layout_segment *lseg)
अणु
	अगर (test_and_clear_bit(NFS_LSEG_LAYOUTRETURN, &lseg->pls_flags) &&
	    pnfs_layout_is_valid(lo)) अणु
		pnfs_set_plh_वापस_info(lo, lseg->pls_range.iomode, 0);
		list_move_tail(&lseg->pls_list, &lo->plh_वापस_segs);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम
pnfs_put_lseg(काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा pnfs_layout_hdr *lo;
	काष्ठा inode *inode;

	अगर (!lseg)
		वापस;

	dprपूर्णांकk("%s: lseg %p ref %d valid %d\n", __func__, lseg,
		refcount_पढ़ो(&lseg->pls_refcount),
		test_bit(NFS_LSEG_VALID, &lseg->pls_flags));

	lo = lseg->pls_layout;
	inode = lo->plh_inode;

	अगर (refcount_dec_and_lock(&lseg->pls_refcount, &inode->i_lock)) अणु
		अगर (test_bit(NFS_LSEG_VALID, &lseg->pls_flags)) अणु
			spin_unlock(&inode->i_lock);
			वापस;
		पूर्ण
		pnfs_get_layout_hdr(lo);
		pnfs_layout_हटाओ_lseg(lo, lseg);
		अगर (pnfs_cache_lseg_क्रम_layoutवापस(lo, lseg))
			lseg = शून्य;
		spin_unlock(&inode->i_lock);
		pnfs_मुक्त_lseg(lseg);
		pnfs_put_layout_hdr(lo);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_put_lseg);

/*
 * is l2 fully contained in l1?
 *   start1                             end1
 *   [----------------------------------)
 *           start2           end2
 *           [----------------)
 */
अटल bool
pnfs_lseg_range_contained(स्थिर काष्ठा pnfs_layout_range *l1,
		 स्थिर काष्ठा pnfs_layout_range *l2)
अणु
	u64 start1 = l1->offset;
	u64 end1 = pnfs_end_offset(start1, l1->length);
	u64 start2 = l2->offset;
	u64 end2 = pnfs_end_offset(start2, l2->length);

	वापस (start1 <= start2) && (end1 >= end2);
पूर्ण

अटल bool pnfs_lseg_dec_and_हटाओ_zero(काष्ठा pnfs_layout_segment *lseg,
		काष्ठा list_head *पंचांगp_list)
अणु
	अगर (!refcount_dec_and_test(&lseg->pls_refcount))
		वापस false;
	pnfs_layout_हटाओ_lseg(lseg->pls_layout, lseg);
	list_add(&lseg->pls_list, पंचांगp_list);
	वापस true;
पूर्ण

/* Returns 1 अगर lseg is हटाओd from list, 0 otherwise */
अटल पूर्णांक mark_lseg_invalid(काष्ठा pnfs_layout_segment *lseg,
			     काष्ठा list_head *पंचांगp_list)
अणु
	पूर्णांक rv = 0;

	अगर (test_and_clear_bit(NFS_LSEG_VALID, &lseg->pls_flags)) अणु
		/* Remove the reference keeping the lseg in the
		 * list.  It will now be हटाओd when all
		 * outstanding io is finished.
		 */
		dprपूर्णांकk("%s: lseg %p ref %d\n", __func__, lseg,
			refcount_पढ़ो(&lseg->pls_refcount));
		अगर (pnfs_lseg_dec_and_हटाओ_zero(lseg, पंचांगp_list))
			rv = 1;
	पूर्ण
	वापस rv;
पूर्ण

अटल bool
pnfs_should_मुक्त_range(स्थिर काष्ठा pnfs_layout_range *lseg_range,
		 स्थिर काष्ठा pnfs_layout_range *recall_range)
अणु
	वापस (recall_range->iomode == IOMODE_ANY ||
		lseg_range->iomode == recall_range->iomode) &&
	       pnfs_lseg_range_पूर्णांकersecting(lseg_range, recall_range);
पूर्ण

अटल bool
pnfs_match_lseg_recall(स्थिर काष्ठा pnfs_layout_segment *lseg,
		स्थिर काष्ठा pnfs_layout_range *recall_range,
		u32 seq)
अणु
	अगर (seq != 0 && pnfs_seqid_is_newer(lseg->pls_seq, seq))
		वापस false;
	अगर (recall_range == शून्य)
		वापस true;
	वापस pnfs_should_मुक्त_range(&lseg->pls_range, recall_range);
पूर्ण

/**
 * pnfs_mark_matching_lsegs_invalid - tear करोwn lsegs or mark them क्रम later
 * @lo: layout header containing the lsegs
 * @पंचांगp_list: list head where करोomed lsegs should go
 * @recall_range: optional recall range argument to match (may be शून्य)
 * @seq: only invalidate lsegs obtained prior to this sequence (may be 0)
 *
 * Walk the list of lsegs in the layout header, and tear करोwn any that should
 * be destroyed. If "recall_range" is specअगरied then the segment must match
 * that range. If "seq" is non-zero, then only match segments that were handed
 * out at or beक्रमe that sequence.
 *
 * Returns number of matching invalid lsegs reमुख्यing in list after scanning
 * it and purging them.
 */
पूर्णांक
pnfs_mark_matching_lsegs_invalid(काष्ठा pnfs_layout_hdr *lo,
			    काष्ठा list_head *पंचांगp_list,
			    स्थिर काष्ठा pnfs_layout_range *recall_range,
			    u32 seq)
अणु
	काष्ठा pnfs_layout_segment *lseg, *next;
	पूर्णांक reमुख्यing = 0;

	dprपूर्णांकk("%s:Begin lo %p\n", __func__, lo);

	अगर (list_empty(&lo->plh_segs))
		वापस 0;
	list_क्रम_each_entry_safe(lseg, next, &lo->plh_segs, pls_list)
		अगर (pnfs_match_lseg_recall(lseg, recall_range, seq)) अणु
			dprपूर्णांकk("%s: freeing lseg %p iomode %d seq %u "
				"offset %llu length %llu\n", __func__,
				lseg, lseg->pls_range.iomode, lseg->pls_seq,
				lseg->pls_range.offset, lseg->pls_range.length);
			अगर (!mark_lseg_invalid(lseg, पंचांगp_list))
				reमुख्यing++;
		पूर्ण
	dprपूर्णांकk("%s:Return %i\n", __func__, reमुख्यing);
	वापस reमुख्यing;
पूर्ण

अटल व्योम
pnfs_मुक्त_वापसed_lsegs(काष्ठा pnfs_layout_hdr *lo,
		काष्ठा list_head *मुक्त_me,
		स्थिर काष्ठा pnfs_layout_range *range,
		u32 seq)
अणु
	काष्ठा pnfs_layout_segment *lseg, *next;

	list_क्रम_each_entry_safe(lseg, next, &lo->plh_वापस_segs, pls_list) अणु
		अगर (pnfs_match_lseg_recall(lseg, range, seq))
			list_move_tail(&lseg->pls_list, मुक्त_me);
	पूर्ण
पूर्ण

/* note मुक्त_me must contain lsegs from a single layout_hdr */
व्योम
pnfs_मुक्त_lseg_list(काष्ठा list_head *मुक्त_me)
अणु
	काष्ठा pnfs_layout_segment *lseg, *पंचांगp;

	अगर (list_empty(मुक्त_me))
		वापस;

	list_क्रम_each_entry_safe(lseg, पंचांगp, मुक्त_me, pls_list) अणु
		list_del(&lseg->pls_list);
		pnfs_मुक्त_lseg(lseg);
	पूर्ण
पूर्ण

अटल काष्ठा pnfs_layout_hdr *__pnfs_destroy_layout(काष्ठा nfs_inode *nfsi)
अणु
	काष्ठा pnfs_layout_hdr *lo;
	LIST_HEAD(पंचांगp_list);

	spin_lock(&nfsi->vfs_inode.i_lock);
	lo = nfsi->layout;
	अगर (lo) अणु
		pnfs_get_layout_hdr(lo);
		pnfs_mark_layout_stateid_invalid(lo, &पंचांगp_list);
		pnfs_layout_clear_fail_bit(lo, NFS_LAYOUT_RO_FAILED);
		pnfs_layout_clear_fail_bit(lo, NFS_LAYOUT_RW_FAILED);
		spin_unlock(&nfsi->vfs_inode.i_lock);
		pnfs_मुक्त_lseg_list(&पंचांगp_list);
		nfs_commit_inode(&nfsi->vfs_inode, 0);
		pnfs_put_layout_hdr(lo);
	पूर्ण अन्यथा
		spin_unlock(&nfsi->vfs_inode.i_lock);
	वापस lo;
पूर्ण

व्योम pnfs_destroy_layout(काष्ठा nfs_inode *nfsi)
अणु
	__pnfs_destroy_layout(nfsi);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_destroy_layout);

अटल bool pnfs_layout_हटाओd(काष्ठा nfs_inode *nfsi,
				काष्ठा pnfs_layout_hdr *lo)
अणु
	bool ret;

	spin_lock(&nfsi->vfs_inode.i_lock);
	ret = nfsi->layout != lo;
	spin_unlock(&nfsi->vfs_inode.i_lock);
	वापस ret;
पूर्ण

व्योम pnfs_destroy_layout_final(काष्ठा nfs_inode *nfsi)
अणु
	काष्ठा pnfs_layout_hdr *lo = __pnfs_destroy_layout(nfsi);

	अगर (lo)
		रुको_var_event(lo, pnfs_layout_हटाओd(nfsi, lo));
पूर्ण

अटल bool
pnfs_layout_add_bulk_destroy_list(काष्ठा inode *inode,
		काष्ठा list_head *layout_list)
अणु
	काष्ठा pnfs_layout_hdr *lo;
	bool ret = false;

	spin_lock(&inode->i_lock);
	lo = NFS_I(inode)->layout;
	अगर (lo != शून्य && list_empty(&lo->plh_bulk_destroy)) अणु
		pnfs_get_layout_hdr(lo);
		list_add(&lo->plh_bulk_destroy, layout_list);
		ret = true;
	पूर्ण
	spin_unlock(&inode->i_lock);
	वापस ret;
पूर्ण

/* Caller must hold rcu_पढ़ो_lock and clp->cl_lock */
अटल पूर्णांक
pnfs_layout_bulk_destroy_byserver_locked(काष्ठा nfs_client *clp,
		काष्ठा nfs_server *server,
		काष्ठा list_head *layout_list)
	__must_hold(&clp->cl_lock)
	__must_hold(RCU)
अणु
	काष्ठा pnfs_layout_hdr *lo, *next;
	काष्ठा inode *inode;

	list_क्रम_each_entry_safe(lo, next, &server->layouts, plh_layouts) अणु
		अगर (test_bit(NFS_LAYOUT_INVALID_STID, &lo->plh_flags) ||
		    test_bit(NFS_LAYOUT_INODE_FREEING, &lo->plh_flags) ||
		    !list_empty(&lo->plh_bulk_destroy))
			जारी;
		/* If the sb is being destroyed, just bail */
		अगर (!nfs_sb_active(server->super))
			अवरोध;
		inode = pnfs_grab_inode_layout_hdr(lo);
		अगर (inode != शून्य) अणु
			अगर (test_and_clear_bit(NFS_LAYOUT_HASHED, &lo->plh_flags))
				list_del_rcu(&lo->plh_layouts);
			अगर (pnfs_layout_add_bulk_destroy_list(inode,
						layout_list))
				जारी;
			rcu_पढ़ो_unlock();
			spin_unlock(&clp->cl_lock);
			iput(inode);
		पूर्ण अन्यथा अणु
			rcu_पढ़ो_unlock();
			spin_unlock(&clp->cl_lock);
		पूर्ण
		nfs_sb_deactive(server->super);
		spin_lock(&clp->cl_lock);
		rcu_पढ़ो_lock();
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
pnfs_layout_मुक्त_bulk_destroy_list(काष्ठा list_head *layout_list,
		bool is_bulk_recall)
अणु
	काष्ठा pnfs_layout_hdr *lo;
	काष्ठा inode *inode;
	LIST_HEAD(lseg_list);
	पूर्णांक ret = 0;

	जबतक (!list_empty(layout_list)) अणु
		lo = list_entry(layout_list->next, काष्ठा pnfs_layout_hdr,
				plh_bulk_destroy);
		dprपूर्णांकk("%s freeing layout for inode %lu\n", __func__,
			lo->plh_inode->i_ino);
		inode = lo->plh_inode;

		pnfs_layoutcommit_inode(inode, false);

		spin_lock(&inode->i_lock);
		list_del_init(&lo->plh_bulk_destroy);
		अगर (pnfs_mark_layout_stateid_invalid(lo, &lseg_list)) अणु
			अगर (is_bulk_recall)
				set_bit(NFS_LAYOUT_BULK_RECALL, &lo->plh_flags);
			ret = -EAGAIN;
		पूर्ण
		spin_unlock(&inode->i_lock);
		pnfs_मुक्त_lseg_list(&lseg_list);
		/* Free all lsegs that are attached to commit buckets */
		nfs_commit_inode(inode, 0);
		pnfs_put_layout_hdr(lo);
		nfs_iput_and_deactive(inode);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
pnfs_destroy_layouts_byfsid(काष्ठा nfs_client *clp,
		काष्ठा nfs_fsid *fsid,
		bool is_recall)
अणु
	काष्ठा nfs_server *server;
	LIST_HEAD(layout_list);

	spin_lock(&clp->cl_lock);
	rcu_पढ़ो_lock();
restart:
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link) अणु
		अगर (स_भेद(&server->fsid, fsid, माप(*fsid)) != 0)
			जारी;
		अगर (pnfs_layout_bulk_destroy_byserver_locked(clp,
				server,
				&layout_list) != 0)
			जाओ restart;
	पूर्ण
	rcu_पढ़ो_unlock();
	spin_unlock(&clp->cl_lock);

	अगर (list_empty(&layout_list))
		वापस 0;
	वापस pnfs_layout_मुक्त_bulk_destroy_list(&layout_list, is_recall);
पूर्ण

पूर्णांक
pnfs_destroy_layouts_byclid(काष्ठा nfs_client *clp,
		bool is_recall)
अणु
	काष्ठा nfs_server *server;
	LIST_HEAD(layout_list);

	spin_lock(&clp->cl_lock);
	rcu_पढ़ो_lock();
restart:
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link) अणु
		अगर (pnfs_layout_bulk_destroy_byserver_locked(clp,
					server,
					&layout_list) != 0)
			जाओ restart;
	पूर्ण
	rcu_पढ़ो_unlock();
	spin_unlock(&clp->cl_lock);

	अगर (list_empty(&layout_list))
		वापस 0;
	वापस pnfs_layout_मुक्त_bulk_destroy_list(&layout_list, is_recall);
पूर्ण

/*
 * Called by the state manager to हटाओ all layouts established under an
 * expired lease.
 */
व्योम
pnfs_destroy_all_layouts(काष्ठा nfs_client *clp)
अणु
	nfs4_deviceid_mark_client_invalid(clp);
	nfs4_deviceid_purge_client(clp);

	pnfs_destroy_layouts_byclid(clp, false);
पूर्ण

अटल व्योम
pnfs_set_layout_cred(काष्ठा pnfs_layout_hdr *lo, स्थिर काष्ठा cred *cred)
अणु
	स्थिर काष्ठा cred *old;

	अगर (cred && cred_fscmp(lo->plh_lc_cred, cred) != 0) अणु
		old = xchg(&lo->plh_lc_cred, get_cred(cred));
		put_cred(old);
	पूर्ण
पूर्ण

/* update lo->plh_stateid with new अगर is more recent */
व्योम
pnfs_set_layout_stateid(काष्ठा pnfs_layout_hdr *lo, स्थिर nfs4_stateid *new,
			स्थिर काष्ठा cred *cred, bool update_barrier)
अणु
	u32 oldseq, newseq, new_barrier = 0;

	oldseq = be32_to_cpu(lo->plh_stateid.seqid);
	newseq = be32_to_cpu(new->seqid);

	अगर (!pnfs_layout_is_valid(lo)) अणु
		pnfs_set_layout_cred(lo, cred);
		nfs4_stateid_copy(&lo->plh_stateid, new);
		lo->plh_barrier = newseq;
		pnfs_clear_layoutवापस_info(lo);
		clear_bit(NFS_LAYOUT_INVALID_STID, &lo->plh_flags);
		वापस;
	पूर्ण
	अगर (pnfs_seqid_is_newer(newseq, oldseq)) अणु
		nfs4_stateid_copy(&lo->plh_stateid, new);
		/*
		 * Because of wraparound, we want to keep the barrier
		 * "close" to the current seqids.
		 */
		new_barrier = newseq - atomic_पढ़ो(&lo->plh_outstanding);
	पूर्ण
	अगर (update_barrier)
		new_barrier = be32_to_cpu(new->seqid);
	अन्यथा अगर (new_barrier == 0)
		वापस;
	pnfs_barrier_update(lo, new_barrier);
पूर्ण

अटल bool
pnfs_layout_stateid_blocked(स्थिर काष्ठा pnfs_layout_hdr *lo,
		स्थिर nfs4_stateid *stateid)
अणु
	u32 seqid = be32_to_cpu(stateid->seqid);

	वापस !pnfs_seqid_is_newer(seqid, lo->plh_barrier) && lo->plh_barrier;
पूर्ण

/* lget is set to 1 अगर called from inside send_layoutget call chain */
अटल bool
pnfs_layoutमाला_लो_blocked(स्थिर काष्ठा pnfs_layout_hdr *lo)
अणु
	वापस lo->plh_block_lमाला_लो ||
		test_bit(NFS_LAYOUT_BULK_RECALL, &lo->plh_flags);
पूर्ण

अटल काष्ठा nfs_server *
pnfs_find_server(काष्ठा inode *inode, काष्ठा nfs_खोलो_context *ctx)
अणु
	काष्ठा nfs_server *server;

	अगर (inode) अणु
		server = NFS_SERVER(inode);
	पूर्ण अन्यथा अणु
		काष्ठा dentry *parent_dir = dget_parent(ctx->dentry);
		server = NFS_SERVER(parent_dir->d_inode);
		dput(parent_dir);
	पूर्ण
	वापस server;
पूर्ण

अटल व्योम nfs4_मुक्त_pages(काष्ठा page **pages, माप_प्रकार size)
अणु
	पूर्णांक i;

	अगर (!pages)
		वापस;

	क्रम (i = 0; i < size; i++) अणु
		अगर (!pages[i])
			अवरोध;
		__मुक्त_page(pages[i]);
	पूर्ण
	kमुक्त(pages);
पूर्ण

अटल काष्ठा page **nfs4_alloc_pages(माप_प्रकार size, gfp_t gfp_flags)
अणु
	काष्ठा page **pages;
	पूर्णांक i;

	pages = kदो_स्मृति_array(size, माप(काष्ठा page *), gfp_flags);
	अगर (!pages) अणु
		dprपूर्णांकk("%s: can't alloc array of %zu pages\n", __func__, size);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < size; i++) अणु
		pages[i] = alloc_page(gfp_flags);
		अगर (!pages[i]) अणु
			dprपूर्णांकk("%s: failed to allocate page\n", __func__);
			nfs4_मुक्त_pages(pages, i);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस pages;
पूर्ण

अटल काष्ठा nfs4_layoutget *
pnfs_alloc_init_layoutget_args(काष्ठा inode *ino,
	   काष्ठा nfs_खोलो_context *ctx,
	   स्थिर nfs4_stateid *stateid,
	   स्थिर काष्ठा pnfs_layout_range *range,
	   gfp_t gfp_flags)
अणु
	काष्ठा nfs_server *server = pnfs_find_server(ino, ctx);
	माप_प्रकार max_reply_sz = server->pnfs_curr_ld->max_layoutget_response;
	माप_प्रकार max_pages = max_response_pages(server);
	काष्ठा nfs4_layoutget *lgp;

	dprपूर्णांकk("--> %s\n", __func__);

	lgp = kzalloc(माप(*lgp), gfp_flags);
	अगर (lgp == शून्य)
		वापस शून्य;

	अगर (max_reply_sz) अणु
		माप_प्रकार npages = (max_reply_sz + PAGE_SIZE - 1) >> PAGE_SHIFT;
		अगर (npages < max_pages)
			max_pages = npages;
	पूर्ण

	lgp->args.layout.pages = nfs4_alloc_pages(max_pages, gfp_flags);
	अगर (!lgp->args.layout.pages) अणु
		kमुक्त(lgp);
		वापस शून्य;
	पूर्ण
	lgp->args.layout.pglen = max_pages * PAGE_SIZE;
	lgp->res.layoutp = &lgp->args.layout;

	/* Don't confuse uninitialised result and success */
	lgp->res.status = -NFS4ERR_DELAY;

	lgp->args.minlength = PAGE_SIZE;
	अगर (lgp->args.minlength > range->length)
		lgp->args.minlength = range->length;
	अगर (ino) अणु
		loff_t i_size = i_size_पढ़ो(ino);

		अगर (range->iomode == IOMODE_READ) अणु
			अगर (range->offset >= i_size)
				lgp->args.minlength = 0;
			अन्यथा अगर (i_size - range->offset < lgp->args.minlength)
				lgp->args.minlength = i_size - range->offset;
		पूर्ण
	पूर्ण
	lgp->args.maxcount = PNFS_LAYOUT_MAXSIZE;
	pnfs_copy_range(&lgp->args.range, range);
	lgp->args.type = server->pnfs_curr_ld->id;
	lgp->args.inode = ino;
	lgp->args.ctx = get_nfs_खोलो_context(ctx);
	nfs4_stateid_copy(&lgp->args.stateid, stateid);
	lgp->gfp_flags = gfp_flags;
	lgp->cred = ctx->cred;
	वापस lgp;
पूर्ण

व्योम pnfs_layoutget_मुक्त(काष्ठा nfs4_layoutget *lgp)
अणु
	माप_प्रकार max_pages = lgp->args.layout.pglen / PAGE_SIZE;

	nfs4_मुक्त_pages(lgp->args.layout.pages, max_pages);
	अगर (lgp->args.inode)
		pnfs_put_layout_hdr(NFS_I(lgp->args.inode)->layout);
	put_nfs_खोलो_context(lgp->args.ctx);
	kमुक्त(lgp);
पूर्ण

अटल व्योम pnfs_clear_layoutcommit(काष्ठा inode *inode,
		काष्ठा list_head *head)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा pnfs_layout_segment *lseg, *पंचांगp;

	अगर (!test_and_clear_bit(NFS_INO_LAYOUTCOMMIT, &nfsi->flags))
		वापस;
	list_क्रम_each_entry_safe(lseg, पंचांगp, &nfsi->layout->plh_segs, pls_list) अणु
		अगर (!test_and_clear_bit(NFS_LSEG_LAYOUTCOMMIT, &lseg->pls_flags))
			जारी;
		pnfs_lseg_dec_and_हटाओ_zero(lseg, head);
	पूर्ण
पूर्ण

व्योम pnfs_layoutवापस_मुक्त_lsegs(काष्ठा pnfs_layout_hdr *lo,
		स्थिर nfs4_stateid *arg_stateid,
		स्थिर काष्ठा pnfs_layout_range *range,
		स्थिर nfs4_stateid *stateid)
अणु
	काष्ठा inode *inode = lo->plh_inode;
	LIST_HEAD(मुक्तme);

	spin_lock(&inode->i_lock);
	अगर (!pnfs_layout_is_valid(lo) ||
	    !nfs4_stateid_match_other(&lo->plh_stateid, arg_stateid))
		जाओ out_unlock;
	अगर (stateid) अणु
		u32 seq = be32_to_cpu(arg_stateid->seqid);

		pnfs_mark_matching_lsegs_invalid(lo, &मुक्तme, range, seq);
		pnfs_मुक्त_वापसed_lsegs(lo, &मुक्तme, range, seq);
		pnfs_set_layout_stateid(lo, stateid, शून्य, true);
	पूर्ण अन्यथा
		pnfs_mark_layout_stateid_invalid(lo, &मुक्तme);
out_unlock:
	pnfs_clear_layoutवापस_रुकोbit(lo);
	spin_unlock(&inode->i_lock);
	pnfs_मुक्त_lseg_list(&मुक्तme);

पूर्ण

अटल bool
pnfs_prepare_layoutवापस(काष्ठा pnfs_layout_hdr *lo,
		nfs4_stateid *stateid,
		स्थिर काष्ठा cred **cred,
		क्रमागत pnfs_iomode *iomode)
अणु
	/* Serialise LAYOUTGET/LAYOUTRETURN */
	अगर (atomic_पढ़ो(&lo->plh_outstanding) != 0)
		वापस false;
	अगर (test_and_set_bit(NFS_LAYOUT_RETURN_LOCK, &lo->plh_flags))
		वापस false;
	set_bit(NFS_LAYOUT_RETURN, &lo->plh_flags);
	pnfs_get_layout_hdr(lo);
	nfs4_stateid_copy(stateid, &lo->plh_stateid);
	*cred = get_cred(lo->plh_lc_cred);
	अगर (test_bit(NFS_LAYOUT_RETURN_REQUESTED, &lo->plh_flags)) अणु
		अगर (lo->plh_वापस_seq != 0)
			stateid->seqid = cpu_to_be32(lo->plh_वापस_seq);
		अगर (iomode != शून्य)
			*iomode = lo->plh_वापस_iomode;
		pnfs_clear_layoutवापस_info(lo);
	पूर्ण अन्यथा अगर (iomode != शून्य)
		*iomode = IOMODE_ANY;
	pnfs_barrier_update(lo, be32_to_cpu(stateid->seqid));
	वापस true;
पूर्ण

अटल व्योम
pnfs_init_layoutवापस_args(काष्ठा nfs4_layoutवापस_args *args,
		काष्ठा pnfs_layout_hdr *lo,
		स्थिर nfs4_stateid *stateid,
		क्रमागत pnfs_iomode iomode)
अणु
	काष्ठा inode *inode = lo->plh_inode;

	args->layout_type = NFS_SERVER(inode)->pnfs_curr_ld->id;
	args->inode = inode;
	args->range.iomode = iomode;
	args->range.offset = 0;
	args->range.length = NFS4_MAX_UINT64;
	args->layout = lo;
	nfs4_stateid_copy(&args->stateid, stateid);
पूर्ण

अटल पूर्णांक
pnfs_send_layoutवापस(काष्ठा pnfs_layout_hdr *lo,
		       स्थिर nfs4_stateid *stateid,
		       स्थिर काष्ठा cred **pcred,
		       क्रमागत pnfs_iomode iomode,
		       bool sync)
अणु
	काष्ठा inode *ino = lo->plh_inode;
	काष्ठा pnfs_layoutdriver_type *ld = NFS_SERVER(ino)->pnfs_curr_ld;
	काष्ठा nfs4_layoutवापस *lrp;
	स्थिर काष्ठा cred *cred = *pcred;
	पूर्णांक status = 0;

	*pcred = शून्य;
	lrp = kzalloc(माप(*lrp), GFP_NOFS);
	अगर (unlikely(lrp == शून्य)) अणु
		status = -ENOMEM;
		spin_lock(&ino->i_lock);
		pnfs_clear_layoutवापस_रुकोbit(lo);
		spin_unlock(&ino->i_lock);
		put_cred(cred);
		pnfs_put_layout_hdr(lo);
		जाओ out;
	पूर्ण

	pnfs_init_layoutवापस_args(&lrp->args, lo, stateid, iomode);
	lrp->args.ld_निजी = &lrp->ld_निजी;
	lrp->clp = NFS_SERVER(ino)->nfs_client;
	lrp->cred = cred;
	अगर (ld->prepare_layoutवापस)
		ld->prepare_layoutवापस(&lrp->args);

	status = nfs4_proc_layoutवापस(lrp, sync);
out:
	dprपूर्णांकk("<-- %s status: %d\n", __func__, status);
	वापस status;
पूर्ण

अटल bool
pnfs_layout_segments_वापसable(काष्ठा pnfs_layout_hdr *lo,
				क्रमागत pnfs_iomode iomode,
				u32 seq)
अणु
	काष्ठा pnfs_layout_range recall_range = अणु
		.length = NFS4_MAX_UINT64,
		.iomode = iomode,
	पूर्ण;
	वापस pnfs_mark_matching_lsegs_वापस(lo, &lo->plh_वापस_segs,
					       &recall_range, seq) != -EBUSY;
पूर्ण

/* Return true अगर layoutवापस is needed */
अटल bool
pnfs_layout_need_वापस(काष्ठा pnfs_layout_hdr *lo)
अणु
	अगर (!test_bit(NFS_LAYOUT_RETURN_REQUESTED, &lo->plh_flags))
		वापस false;
	वापस pnfs_layout_segments_वापसable(lo, lo->plh_वापस_iomode,
					       lo->plh_वापस_seq);
पूर्ण

अटल व्योम pnfs_layoutवापस_beक्रमe_put_layout_hdr(काष्ठा pnfs_layout_hdr *lo)
अणु
	काष्ठा inode *inode= lo->plh_inode;

	अगर (!test_bit(NFS_LAYOUT_RETURN_REQUESTED, &lo->plh_flags))
		वापस;
	spin_lock(&inode->i_lock);
	अगर (pnfs_layout_need_वापस(lo)) अणु
		स्थिर काष्ठा cred *cred;
		nfs4_stateid stateid;
		क्रमागत pnfs_iomode iomode;
		bool send;

		send = pnfs_prepare_layoutवापस(lo, &stateid, &cred, &iomode);
		spin_unlock(&inode->i_lock);
		अगर (send) अणु
			/* Send an async layoutवापस so we करोnt deadlock */
			pnfs_send_layoutवापस(lo, &stateid, &cred, iomode, false);
		पूर्ण
	पूर्ण अन्यथा
		spin_unlock(&inode->i_lock);
पूर्ण

/*
 * Initiates a LAYOUTRETURN(खाता), and हटाओs the pnfs_layout_hdr
 * when the layout segment list is empty.
 *
 * Note that a pnfs_layout_hdr can exist with an empty layout segment
 * list when LAYOUTGET has failed, or when LAYOUTGET succeeded, but the
 * deviceid is marked invalid.
 */
पूर्णांक
_pnfs_वापस_layout(काष्ठा inode *ino)
अणु
	काष्ठा pnfs_layout_hdr *lo = शून्य;
	काष्ठा nfs_inode *nfsi = NFS_I(ino);
	काष्ठा pnfs_layout_range range = अणु
		.iomode		= IOMODE_ANY,
		.offset		= 0,
		.length		= NFS4_MAX_UINT64,
	पूर्ण;
	LIST_HEAD(पंचांगp_list);
	स्थिर काष्ठा cred *cred;
	nfs4_stateid stateid;
	पूर्णांक status = 0;
	bool send, valid_layout;

	dprपूर्णांकk("NFS: %s for inode %lu\n", __func__, ino->i_ino);

	spin_lock(&ino->i_lock);
	lo = nfsi->layout;
	अगर (!lo) अणु
		spin_unlock(&ino->i_lock);
		dprपूर्णांकk("NFS: %s no layout to return\n", __func__);
		जाओ out;
	पूर्ण
	/* Reference matched in nfs4_layoutवापस_release */
	pnfs_get_layout_hdr(lo);
	/* Is there an outstanding layoutवापस ? */
	अगर (test_bit(NFS_LAYOUT_RETURN_LOCK, &lo->plh_flags)) अणु
		spin_unlock(&ino->i_lock);
		अगर (रुको_on_bit(&lo->plh_flags, NFS_LAYOUT_RETURN,
					TASK_UNINTERRUPTIBLE))
			जाओ out_put_layout_hdr;
		spin_lock(&ino->i_lock);
	पूर्ण
	valid_layout = pnfs_layout_is_valid(lo);
	pnfs_clear_layoutcommit(ino, &पंचांगp_list);
	pnfs_mark_matching_lsegs_वापस(lo, &पंचांगp_list, &range, 0);

	अगर (NFS_SERVER(ino)->pnfs_curr_ld->वापस_range)
		NFS_SERVER(ino)->pnfs_curr_ld->वापस_range(lo, &range);

	/* Don't send a LAYOUTRETURN अगर list was initially empty */
	अगर (!test_bit(NFS_LAYOUT_RETURN_REQUESTED, &lo->plh_flags) ||
			!valid_layout) अणु
		spin_unlock(&ino->i_lock);
		dprपूर्णांकk("NFS: %s no layout segments to return\n", __func__);
		जाओ out_रुको_layoutवापस;
	पूर्ण

	send = pnfs_prepare_layoutवापस(lo, &stateid, &cred, शून्य);
	spin_unlock(&ino->i_lock);
	अगर (send)
		status = pnfs_send_layoutवापस(lo, &stateid, &cred, IOMODE_ANY, true);
out_रुको_layoutवापस:
	रुको_on_bit(&lo->plh_flags, NFS_LAYOUT_RETURN, TASK_UNINTERRUPTIBLE);
out_put_layout_hdr:
	pnfs_मुक्त_lseg_list(&पंचांगp_list);
	pnfs_put_layout_hdr(lo);
out:
	dprपूर्णांकk("<-- %s status: %d\n", __func__, status);
	वापस status;
पूर्ण

पूर्णांक
pnfs_commit_and_वापस_layout(काष्ठा inode *inode)
अणु
	काष्ठा pnfs_layout_hdr *lo;
	पूर्णांक ret;

	spin_lock(&inode->i_lock);
	lo = NFS_I(inode)->layout;
	अगर (lo == शून्य) अणु
		spin_unlock(&inode->i_lock);
		वापस 0;
	पूर्ण
	pnfs_get_layout_hdr(lo);
	/* Block new layoutमाला_लो and पढ़ो/ग_लिखो to ds */
	lo->plh_block_lमाला_लो++;
	spin_unlock(&inode->i_lock);
	filemap_fdataरुको(inode->i_mapping);
	ret = pnfs_layoutcommit_inode(inode, true);
	अगर (ret == 0)
		ret = _pnfs_वापस_layout(inode);
	spin_lock(&inode->i_lock);
	lo->plh_block_lमाला_लो--;
	spin_unlock(&inode->i_lock);
	pnfs_put_layout_hdr(lo);
	वापस ret;
पूर्ण

bool pnfs_roc(काष्ठा inode *ino,
		काष्ठा nfs4_layoutवापस_args *args,
		काष्ठा nfs4_layoutवापस_res *res,
		स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(ino);
	काष्ठा nfs_खोलो_context *ctx;
	काष्ठा nfs4_state *state;
	काष्ठा pnfs_layout_hdr *lo;
	काष्ठा pnfs_layout_segment *lseg, *next;
	स्थिर काष्ठा cred *lc_cred;
	nfs4_stateid stateid;
	क्रमागत pnfs_iomode iomode = 0;
	bool layoutवापस = false, roc = false;
	bool skip_पढ़ो = false;

	अगर (!nfs_have_layout(ino))
		वापस false;
retry:
	rcu_पढ़ो_lock();
	spin_lock(&ino->i_lock);
	lo = nfsi->layout;
	अगर (!lo || !pnfs_layout_is_valid(lo) ||
	    test_bit(NFS_LAYOUT_BULK_RECALL, &lo->plh_flags)) अणु
		lo = शून्य;
		जाओ out_noroc;
	पूर्ण
	pnfs_get_layout_hdr(lo);
	अगर (test_bit(NFS_LAYOUT_RETURN_LOCK, &lo->plh_flags)) अणु
		spin_unlock(&ino->i_lock);
		rcu_पढ़ो_unlock();
		रुको_on_bit(&lo->plh_flags, NFS_LAYOUT_RETURN,
				TASK_UNINTERRUPTIBLE);
		pnfs_put_layout_hdr(lo);
		जाओ retry;
	पूर्ण

	/* no roc अगर we hold a delegation */
	अगर (nfs4_check_delegation(ino, FMODE_READ)) अणु
		अगर (nfs4_check_delegation(ino, FMODE_WRITE))
			जाओ out_noroc;
		skip_पढ़ो = true;
	पूर्ण

	list_क्रम_each_entry_rcu(ctx, &nfsi->खोलो_files, list) अणु
		state = ctx->state;
		अगर (state == शून्य)
			जारी;
		/* Don't वापस layout अगर there is खोलो file state */
		अगर (state->state & FMODE_WRITE)
			जाओ out_noroc;
		अगर (state->state & FMODE_READ)
			skip_पढ़ो = true;
	पूर्ण


	list_क्रम_each_entry_safe(lseg, next, &lo->plh_segs, pls_list) अणु
		अगर (skip_पढ़ो && lseg->pls_range.iomode == IOMODE_READ)
			जारी;
		/* If we are sending layoutवापस, invalidate all valid lsegs */
		अगर (!test_and_clear_bit(NFS_LSEG_ROC, &lseg->pls_flags))
			जारी;
		/*
		 * Note: mark lseg क्रम वापस so pnfs_layout_हटाओ_lseg
		 * करोesn't invalidate the layout क्रम us.
		 */
		set_bit(NFS_LSEG_LAYOUTRETURN, &lseg->pls_flags);
		अगर (!mark_lseg_invalid(lseg, &lo->plh_वापस_segs))
			जारी;
		pnfs_set_plh_वापस_info(lo, lseg->pls_range.iomode, 0);
	पूर्ण

	अगर (!test_bit(NFS_LAYOUT_RETURN_REQUESTED, &lo->plh_flags))
		जाओ out_noroc;

	/* ROC in two conditions:
	 * 1. there are ROC lsegs
	 * 2. we करोn't send layoutवापस
	 */
	/* lo ref dropped in pnfs_roc_release() */
	layoutवापस = pnfs_prepare_layoutवापस(lo, &stateid, &lc_cred, &iomode);
	/* If the creds करोn't match, we can't compound the layoutवापस */
	अगर (!layoutवापस || cred_fscmp(cred, lc_cred) != 0)
		जाओ out_noroc;

	roc = layoutवापस;
	pnfs_init_layoutवापस_args(args, lo, &stateid, iomode);
	res->lrs_present = 0;
	layoutवापस = false;
	put_cred(lc_cred);

out_noroc:
	spin_unlock(&ino->i_lock);
	rcu_पढ़ो_unlock();
	pnfs_layoutcommit_inode(ino, true);
	अगर (roc) अणु
		काष्ठा pnfs_layoutdriver_type *ld = NFS_SERVER(ino)->pnfs_curr_ld;
		अगर (ld->prepare_layoutवापस)
			ld->prepare_layoutवापस(args);
		pnfs_put_layout_hdr(lo);
		वापस true;
	पूर्ण
	अगर (layoutवापस)
		pnfs_send_layoutवापस(lo, &stateid, &lc_cred, iomode, true);
	pnfs_put_layout_hdr(lo);
	वापस false;
पूर्ण

पूर्णांक pnfs_roc_करोne(काष्ठा rpc_task *task, काष्ठा nfs4_layoutवापस_args **argpp,
		  काष्ठा nfs4_layoutवापस_res **respp, पूर्णांक *ret)
अणु
	काष्ठा nfs4_layoutवापस_args *arg = *argpp;
	पूर्णांक retval = -EAGAIN;

	अगर (!arg)
		वापस 0;
	/* Handle Layoutवापस errors */
	चयन (*ret) अणु
	हाल 0:
		retval = 0;
		अवरोध;
	हाल -NFS4ERR_NOMATCHING_LAYOUT:
		/* Was there an RPC level error? If not, retry */
		अगर (task->tk_rpc_status == 0)
			अवरोध;
		/* If the call was not sent, let caller handle it */
		अगर (!RPC_WAS_SENT(task))
			वापस 0;
		/*
		 * Otherwise, assume the call succeeded and
		 * that we need to release the layout
		 */
		*ret = 0;
		(*respp)->lrs_present = 0;
		retval = 0;
		अवरोध;
	हाल -NFS4ERR_DELAY:
		/* Let the caller handle the retry */
		*ret = -NFS4ERR_NOMATCHING_LAYOUT;
		वापस 0;
	हाल -NFS4ERR_OLD_STATEID:
		अगर (!nfs4_layout_refresh_old_stateid(&arg->stateid,
						     &arg->range, arg->inode))
			अवरोध;
		*ret = -NFS4ERR_NOMATCHING_LAYOUT;
		वापस -EAGAIN;
	पूर्ण
	*argpp = शून्य;
	*respp = शून्य;
	वापस retval;
पूर्ण

व्योम pnfs_roc_release(काष्ठा nfs4_layoutवापस_args *args,
		काष्ठा nfs4_layoutवापस_res *res,
		पूर्णांक ret)
अणु
	काष्ठा pnfs_layout_hdr *lo = args->layout;
	काष्ठा inode *inode = args->inode;
	स्थिर nfs4_stateid *res_stateid = शून्य;
	काष्ठा nfs4_xdr_opaque_data *ld_निजी = args->ld_निजी;

	चयन (ret) अणु
	हाल -NFS4ERR_NOMATCHING_LAYOUT:
		spin_lock(&inode->i_lock);
		अगर (pnfs_layout_is_valid(lo) &&
		    nfs4_stateid_match_other(&args->stateid, &lo->plh_stateid))
			pnfs_set_plh_वापस_info(lo, args->range.iomode, 0);
		pnfs_clear_layoutवापस_रुकोbit(lo);
		spin_unlock(&inode->i_lock);
		अवरोध;
	हाल 0:
		अगर (res->lrs_present)
			res_stateid = &res->stateid;
		fallthrough;
	शेष:
		pnfs_layoutवापस_मुक्त_lsegs(lo, &args->stateid, &args->range,
					     res_stateid);
	पूर्ण
	trace_nfs4_layoutवापस_on_बंद(args->inode, &args->stateid, ret);
	अगर (ld_निजी && ld_निजी->ops && ld_निजी->ops->मुक्त)
		ld_निजी->ops->मुक्त(ld_निजी);
	pnfs_put_layout_hdr(lo);
पूर्ण

bool pnfs_रुको_on_layoutवापस(काष्ठा inode *ino, काष्ठा rpc_task *task)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(ino);
        काष्ठा pnfs_layout_hdr *lo;
        bool sleep = false;

	/* we might not have grabbed lo reference. so need to check under
	 * i_lock */
        spin_lock(&ino->i_lock);
        lo = nfsi->layout;
        अगर (lo && test_bit(NFS_LAYOUT_RETURN, &lo->plh_flags)) अणु
                rpc_sleep_on(&NFS_SERVER(ino)->roc_rpcरुकोq, task, शून्य);
                sleep = true;
	पूर्ण
        spin_unlock(&ino->i_lock);
        वापस sleep;
पूर्ण

/*
 * Compare two layout segments क्रम sorting पूर्णांकo layout cache.
 * We want to preferentially वापस RW over RO layouts, so ensure those
 * are seen first.
 */
अटल s64
pnfs_lseg_range_cmp(स्थिर काष्ठा pnfs_layout_range *l1,
	   स्थिर काष्ठा pnfs_layout_range *l2)
अणु
	s64 d;

	/* high offset > low offset */
	d = l1->offset - l2->offset;
	अगर (d)
		वापस d;

	/* लघु length > दीर्घ length */
	d = l2->length - l1->length;
	अगर (d)
		वापस d;

	/* पढ़ो > पढ़ो/ग_लिखो */
	वापस (पूर्णांक)(l1->iomode == IOMODE_READ) - (पूर्णांक)(l2->iomode == IOMODE_READ);
पूर्ण

अटल bool
pnfs_lseg_range_is_after(स्थिर काष्ठा pnfs_layout_range *l1,
		स्थिर काष्ठा pnfs_layout_range *l2)
अणु
	वापस pnfs_lseg_range_cmp(l1, l2) > 0;
पूर्ण

अटल bool
pnfs_lseg_no_merge(काष्ठा pnfs_layout_segment *lseg,
		काष्ठा pnfs_layout_segment *old)
अणु
	वापस false;
पूर्ण

व्योम
pnfs_generic_layout_insert_lseg(काष्ठा pnfs_layout_hdr *lo,
		   काष्ठा pnfs_layout_segment *lseg,
		   bool (*is_after)(स्थिर काष्ठा pnfs_layout_range *,
			   स्थिर काष्ठा pnfs_layout_range *),
		   bool (*करो_merge)(काष्ठा pnfs_layout_segment *,
			   काष्ठा pnfs_layout_segment *),
		   काष्ठा list_head *मुक्त_me)
अणु
	काष्ठा pnfs_layout_segment *lp, *पंचांगp;

	dprपूर्णांकk("%s:Begin\n", __func__);

	list_क्रम_each_entry_safe(lp, पंचांगp, &lo->plh_segs, pls_list) अणु
		अगर (test_bit(NFS_LSEG_VALID, &lp->pls_flags) == 0)
			जारी;
		अगर (करो_merge(lseg, lp)) अणु
			mark_lseg_invalid(lp, मुक्त_me);
			जारी;
		पूर्ण
		अगर (is_after(&lseg->pls_range, &lp->pls_range))
			जारी;
		list_add_tail(&lseg->pls_list, &lp->pls_list);
		dprपूर्णांकk("%s: inserted lseg %p "
			"iomode %d offset %llu length %llu before "
			"lp %p iomode %d offset %llu length %llu\n",
			__func__, lseg, lseg->pls_range.iomode,
			lseg->pls_range.offset, lseg->pls_range.length,
			lp, lp->pls_range.iomode, lp->pls_range.offset,
			lp->pls_range.length);
		जाओ out;
	पूर्ण
	list_add_tail(&lseg->pls_list, &lo->plh_segs);
	dprपूर्णांकk("%s: inserted lseg %p "
		"iomode %d offset %llu length %llu at tail\n",
		__func__, lseg, lseg->pls_range.iomode,
		lseg->pls_range.offset, lseg->pls_range.length);
out:
	pnfs_get_layout_hdr(lo);

	dprपूर्णांकk("%s:Return\n", __func__);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_layout_insert_lseg);

अटल व्योम
pnfs_layout_insert_lseg(काष्ठा pnfs_layout_hdr *lo,
		   काष्ठा pnfs_layout_segment *lseg,
		   काष्ठा list_head *मुक्त_me)
अणु
	काष्ठा inode *inode = lo->plh_inode;
	काष्ठा pnfs_layoutdriver_type *ld = NFS_SERVER(inode)->pnfs_curr_ld;

	अगर (ld->add_lseg != शून्य)
		ld->add_lseg(lo, lseg, मुक्त_me);
	अन्यथा
		pnfs_generic_layout_insert_lseg(lo, lseg,
				pnfs_lseg_range_is_after,
				pnfs_lseg_no_merge,
				मुक्त_me);
पूर्ण

अटल काष्ठा pnfs_layout_hdr *
alloc_init_layout_hdr(काष्ठा inode *ino,
		      काष्ठा nfs_खोलो_context *ctx,
		      gfp_t gfp_flags)
अणु
	काष्ठा pnfs_layout_hdr *lo;

	lo = pnfs_alloc_layout_hdr(ino, gfp_flags);
	अगर (!lo)
		वापस शून्य;
	refcount_set(&lo->plh_refcount, 1);
	INIT_LIST_HEAD(&lo->plh_layouts);
	INIT_LIST_HEAD(&lo->plh_segs);
	INIT_LIST_HEAD(&lo->plh_वापस_segs);
	INIT_LIST_HEAD(&lo->plh_bulk_destroy);
	lo->plh_inode = ino;
	lo->plh_lc_cred = get_cred(ctx->cred);
	lo->plh_flags |= 1 << NFS_LAYOUT_INVALID_STID;
	वापस lo;
पूर्ण

अटल काष्ठा pnfs_layout_hdr *
pnfs_find_alloc_layout(काष्ठा inode *ino,
		       काष्ठा nfs_खोलो_context *ctx,
		       gfp_t gfp_flags)
	__releases(&ino->i_lock)
	__acquires(&ino->i_lock)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(ino);
	काष्ठा pnfs_layout_hdr *new = शून्य;

	dprपूर्णांकk("%s Begin ino=%p layout=%p\n", __func__, ino, nfsi->layout);

	अगर (nfsi->layout != शून्य)
		जाओ out_existing;
	spin_unlock(&ino->i_lock);
	new = alloc_init_layout_hdr(ino, ctx, gfp_flags);
	spin_lock(&ino->i_lock);

	अगर (likely(nfsi->layout == शून्य)) अणु	/* Won the race? */
		nfsi->layout = new;
		वापस new;
	पूर्ण अन्यथा अगर (new != शून्य)
		pnfs_मुक्त_layout_hdr(new);
out_existing:
	pnfs_get_layout_hdr(nfsi->layout);
	वापस nfsi->layout;
पूर्ण

/*
 * iomode matching rules:
 * iomode	lseg	strict match
 *                      iomode
 * -----	-----	------ -----
 * ANY		READ	N/A    true
 * ANY		RW	N/A    true
 * RW		READ	N/A    false
 * RW		RW	N/A    true
 * READ		READ	N/A    true
 * READ		RW	true   false
 * READ		RW	false  true
 */
अटल bool
pnfs_lseg_range_match(स्थिर काष्ठा pnfs_layout_range *ls_range,
		 स्थिर काष्ठा pnfs_layout_range *range,
		 bool strict_iomode)
अणु
	काष्ठा pnfs_layout_range range1;

	अगर ((range->iomode == IOMODE_RW &&
	     ls_range->iomode != IOMODE_RW) ||
	    (range->iomode != ls_range->iomode &&
	     strict_iomode) ||
	    !pnfs_lseg_range_पूर्णांकersecting(ls_range, range))
		वापस false;

	/* range1 covers only the first byte in the range */
	range1 = *range;
	range1.length = 1;
	वापस pnfs_lseg_range_contained(ls_range, &range1);
पूर्ण

/*
 * lookup range in layout
 */
अटल काष्ठा pnfs_layout_segment *
pnfs_find_lseg(काष्ठा pnfs_layout_hdr *lo,
		काष्ठा pnfs_layout_range *range,
		bool strict_iomode)
अणु
	काष्ठा pnfs_layout_segment *lseg, *ret = शून्य;

	dprपूर्णांकk("%s:Begin\n", __func__);

	list_क्रम_each_entry(lseg, &lo->plh_segs, pls_list) अणु
		अगर (test_bit(NFS_LSEG_VALID, &lseg->pls_flags) &&
		    pnfs_lseg_range_match(&lseg->pls_range, range,
					  strict_iomode)) अणु
			ret = pnfs_get_lseg(lseg);
			अवरोध;
		पूर्ण
	पूर्ण

	dprपूर्णांकk("%s:Return lseg %p ref %d\n",
		__func__, ret, ret ? refcount_पढ़ो(&ret->pls_refcount) : 0);
	वापस ret;
पूर्ण

/*
 * Use mdsthreshold hपूर्णांकs set at each OPEN to determine अगर I/O should go
 * to the MDS or over pNFS
 *
 * The nfs_inode पढ़ो_io and ग_लिखो_io fields are cumulative counters reset
 * when there are no layout segments. Note that in pnfs_update_layout iomode
 * is set to IOMODE_READ क्रम a READ request, and set to IOMODE_RW क्रम a
 * WRITE request.
 *
 * A वापस of true means use MDS I/O.
 *
 * From rfc 5661:
 * If a file's size is smaller than the file size threshold, data accesses
 * SHOULD be sent to the metadata server.  If an I/O request has a length that
 * is below the I/O size threshold, the I/O SHOULD be sent to the metadata
 * server.  If both file size and I/O size are provided, the client SHOULD
 * reach or exceed  both thresholds beक्रमe sending its पढ़ो or ग_लिखो
 * requests to the data server.
 */
अटल bool pnfs_within_mdsthreshold(काष्ठा nfs_खोलो_context *ctx,
				     काष्ठा inode *ino, पूर्णांक iomode)
अणु
	काष्ठा nfs4_threshold *t = ctx->mdsthreshold;
	काष्ठा nfs_inode *nfsi = NFS_I(ino);
	loff_t fsize = i_size_पढ़ो(ino);
	bool size = false, size_set = false, io = false, io_set = false, ret = false;

	अगर (t == शून्य)
		वापस ret;

	dprपूर्णांकk("%s bm=0x%x rd_sz=%llu wr_sz=%llu rd_io=%llu wr_io=%llu\n",
		__func__, t->bm, t->rd_sz, t->wr_sz, t->rd_io_sz, t->wr_io_sz);

	चयन (iomode) अणु
	हाल IOMODE_READ:
		अगर (t->bm & THRESHOLD_RD) अणु
			dprपूर्णांकk("%s fsize %llu\n", __func__, fsize);
			size_set = true;
			अगर (fsize < t->rd_sz)
				size = true;
		पूर्ण
		अगर (t->bm & THRESHOLD_RD_IO) अणु
			dprपूर्णांकk("%s nfsi->read_io %llu\n", __func__,
				nfsi->पढ़ो_io);
			io_set = true;
			अगर (nfsi->पढ़ो_io < t->rd_io_sz)
				io = true;
		पूर्ण
		अवरोध;
	हाल IOMODE_RW:
		अगर (t->bm & THRESHOLD_WR) अणु
			dprपूर्णांकk("%s fsize %llu\n", __func__, fsize);
			size_set = true;
			अगर (fsize < t->wr_sz)
				size = true;
		पूर्ण
		अगर (t->bm & THRESHOLD_WR_IO) अणु
			dprपूर्णांकk("%s nfsi->write_io %llu\n", __func__,
				nfsi->ग_लिखो_io);
			io_set = true;
			अगर (nfsi->ग_लिखो_io < t->wr_io_sz)
				io = true;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (size_set && io_set) अणु
		अगर (size && io)
			ret = true;
	पूर्ण अन्यथा अगर (size || io)
		ret = true;

	dprपूर्णांकk("<-- %s size %d io %d ret %d\n", __func__, size, io, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक pnfs_prepare_to_retry_layoutget(काष्ठा pnfs_layout_hdr *lo)
अणु
	/*
	 * send layoutcommit as it can hold up layoutवापस due to lseg
	 * reference
	 */
	pnfs_layoutcommit_inode(lo->plh_inode, false);
	वापस रुको_on_bit_action(&lo->plh_flags, NFS_LAYOUT_RETURN,
				   nfs_रुको_bit_समाप्तable,
				   TASK_KILLABLE);
पूर्ण

अटल व्योम nfs_layoutget_begin(काष्ठा pnfs_layout_hdr *lo)
अणु
	atomic_inc(&lo->plh_outstanding);
पूर्ण

अटल व्योम nfs_layoutget_end(काष्ठा pnfs_layout_hdr *lo)
अणु
	अगर (atomic_dec_and_test(&lo->plh_outstanding))
		wake_up_var(&lo->plh_outstanding);
पूर्ण

अटल bool pnfs_is_first_layoutget(काष्ठा pnfs_layout_hdr *lo)
अणु
	वापस test_bit(NFS_LAYOUT_FIRST_LAYOUTGET, &lo->plh_flags);
पूर्ण

अटल व्योम pnfs_clear_first_layoutget(काष्ठा pnfs_layout_hdr *lo)
अणु
	अचिन्हित दीर्घ *bitlock = &lo->plh_flags;

	clear_bit_unlock(NFS_LAYOUT_FIRST_LAYOUTGET, bitlock);
	smp_mb__after_atomic();
	wake_up_bit(bitlock, NFS_LAYOUT_FIRST_LAYOUTGET);
पूर्ण

अटल व्योम _add_to_server_list(काष्ठा pnfs_layout_hdr *lo,
				काष्ठा nfs_server *server)
अणु
	अगर (!test_and_set_bit(NFS_LAYOUT_HASHED, &lo->plh_flags)) अणु
		काष्ठा nfs_client *clp = server->nfs_client;

		/* The lo must be on the clp list अगर there is any
		 * chance of a CB_LAYOUTRECALL(खाता) coming in.
		 */
		spin_lock(&clp->cl_lock);
		list_add_tail_rcu(&lo->plh_layouts, &server->layouts);
		spin_unlock(&clp->cl_lock);
	पूर्ण
पूर्ण

/*
 * Layout segment is retreived from the server अगर not cached.
 * The appropriate layout segment is referenced and वापसed to the caller.
 */
काष्ठा pnfs_layout_segment *
pnfs_update_layout(काष्ठा inode *ino,
		   काष्ठा nfs_खोलो_context *ctx,
		   loff_t pos,
		   u64 count,
		   क्रमागत pnfs_iomode iomode,
		   bool strict_iomode,
		   gfp_t gfp_flags)
अणु
	काष्ठा pnfs_layout_range arg = अणु
		.iomode = iomode,
		.offset = pos,
		.length = count,
	पूर्ण;
	अचिन्हित pg_offset;
	काष्ठा nfs_server *server = NFS_SERVER(ino);
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा pnfs_layout_hdr *lo = शून्य;
	काष्ठा pnfs_layout_segment *lseg = शून्य;
	काष्ठा nfs4_layoutget *lgp;
	nfs4_stateid stateid;
	दीर्घ समयout = 0;
	अचिन्हित दीर्घ giveup = jअगरfies + (clp->cl_lease_समय << 1);
	bool first;

	अगर (!pnfs_enabled_sb(NFS_SERVER(ino))) अणु
		trace_pnfs_update_layout(ino, pos, count, iomode, lo, lseg,
				 PNFS_UPDATE_LAYOUT_NO_PNFS);
		जाओ out;
	पूर्ण

	अगर (pnfs_within_mdsthreshold(ctx, ino, iomode)) अणु
		trace_pnfs_update_layout(ino, pos, count, iomode, lo, lseg,
				 PNFS_UPDATE_LAYOUT_MDSTHRESH);
		जाओ out;
	पूर्ण

lookup_again:
	lseg = ERR_PTR(nfs4_client_recover_expired_lease(clp));
	अगर (IS_ERR(lseg))
		जाओ out;
	first = false;
	spin_lock(&ino->i_lock);
	lo = pnfs_find_alloc_layout(ino, ctx, gfp_flags);
	अगर (lo == शून्य) अणु
		spin_unlock(&ino->i_lock);
		trace_pnfs_update_layout(ino, pos, count, iomode, lo, lseg,
				 PNFS_UPDATE_LAYOUT_NOMEM);
		जाओ out;
	पूर्ण

	/* Do we even need to bother with this? */
	अगर (test_bit(NFS_LAYOUT_BULK_RECALL, &lo->plh_flags)) अणु
		trace_pnfs_update_layout(ino, pos, count, iomode, lo, lseg,
				 PNFS_UPDATE_LAYOUT_BULK_RECALL);
		dprपूर्णांकk("%s matches recall, use MDS\n", __func__);
		जाओ out_unlock;
	पूर्ण

	/* अगर LAYOUTGET alपढ़ोy failed once we करोn't try again */
	अगर (pnfs_layout_io_test_failed(lo, iomode)) अणु
		trace_pnfs_update_layout(ino, pos, count, iomode, lo, lseg,
				 PNFS_UPDATE_LAYOUT_IO_TEST_FAIL);
		जाओ out_unlock;
	पूर्ण

	/*
	 * If the layout segment list is empty, but there are outstanding
	 * layoutget calls, then they might be subject to a layoutrecall.
	 */
	अगर (list_empty(&lo->plh_segs) &&
	    atomic_पढ़ो(&lo->plh_outstanding) != 0) अणु
		spin_unlock(&ino->i_lock);
		lseg = ERR_PTR(रुको_var_event_समाप्तable(&lo->plh_outstanding,
					!atomic_पढ़ो(&lo->plh_outstanding)));
		अगर (IS_ERR(lseg))
			जाओ out_put_layout_hdr;
		pnfs_put_layout_hdr(lo);
		जाओ lookup_again;
	पूर्ण

	/*
	 * Because we मुक्त lsegs when sending LAYOUTRETURN, we need to रुको
	 * क्रम LAYOUTRETURN.
	 */
	अगर (test_bit(NFS_LAYOUT_RETURN, &lo->plh_flags)) अणु
		spin_unlock(&ino->i_lock);
		dprपूर्णांकk("%s wait for layoutreturn\n", __func__);
		lseg = ERR_PTR(pnfs_prepare_to_retry_layoutget(lo));
		अगर (!IS_ERR(lseg)) अणु
			pnfs_put_layout_hdr(lo);
			dprपूर्णांकk("%s retrying\n", __func__);
			trace_pnfs_update_layout(ino, pos, count, iomode, lo,
						 lseg,
						 PNFS_UPDATE_LAYOUT_RETRY);
			जाओ lookup_again;
		पूर्ण
		trace_pnfs_update_layout(ino, pos, count, iomode, lo, lseg,
					 PNFS_UPDATE_LAYOUT_RETURN);
		जाओ out_put_layout_hdr;
	पूर्ण

	lseg = pnfs_find_lseg(lo, &arg, strict_iomode);
	अगर (lseg) अणु
		trace_pnfs_update_layout(ino, pos, count, iomode, lo, lseg,
				PNFS_UPDATE_LAYOUT_FOUND_CACHED);
		जाओ out_unlock;
	पूर्ण

	/*
	 * Choose a stateid क्रम the LAYOUTGET. If we करोn't have a layout
	 * stateid, or it has been invalidated, then we must use the खोलो
	 * stateid.
	 */
	अगर (test_bit(NFS_LAYOUT_INVALID_STID, &lo->plh_flags)) अणु
		पूर्णांक status;

		/*
		 * The first layoutget क्रम the file. Need to serialize per
		 * RFC 5661 Errata 3208.
		 */
		अगर (test_and_set_bit(NFS_LAYOUT_FIRST_LAYOUTGET,
				     &lo->plh_flags)) अणु
			spin_unlock(&ino->i_lock);
			lseg = ERR_PTR(रुको_on_bit(&lo->plh_flags,
						NFS_LAYOUT_FIRST_LAYOUTGET,
						TASK_KILLABLE));
			अगर (IS_ERR(lseg))
				जाओ out_put_layout_hdr;
			pnfs_put_layout_hdr(lo);
			dprपूर्णांकk("%s retrying\n", __func__);
			जाओ lookup_again;
		पूर्ण

		spin_unlock(&ino->i_lock);
		first = true;
		status = nfs4_select_rw_stateid(ctx->state,
					iomode == IOMODE_RW ? FMODE_WRITE : FMODE_READ,
					शून्य, &stateid, शून्य);
		अगर (status != 0) अणु
			lseg = ERR_PTR(status);
			trace_pnfs_update_layout(ino, pos, count,
					iomode, lo, lseg,
					PNFS_UPDATE_LAYOUT_INVALID_OPEN);
			nfs4_schedule_stateid_recovery(server, ctx->state);
			pnfs_clear_first_layoutget(lo);
			pnfs_put_layout_hdr(lo);
			जाओ lookup_again;
		पूर्ण
		spin_lock(&ino->i_lock);
	पूर्ण अन्यथा अणु
		nfs4_stateid_copy(&stateid, &lo->plh_stateid);
	पूर्ण

	अगर (pnfs_layoutमाला_लो_blocked(lo)) अणु
		trace_pnfs_update_layout(ino, pos, count, iomode, lo, lseg,
				PNFS_UPDATE_LAYOUT_BLOCKED);
		जाओ out_unlock;
	पूर्ण
	nfs_layoutget_begin(lo);
	spin_unlock(&ino->i_lock);

	_add_to_server_list(lo, server);

	pg_offset = arg.offset & ~PAGE_MASK;
	अगर (pg_offset) अणु
		arg.offset -= pg_offset;
		arg.length += pg_offset;
	पूर्ण
	अगर (arg.length != NFS4_MAX_UINT64)
		arg.length = PAGE_ALIGN(arg.length);

	lgp = pnfs_alloc_init_layoutget_args(ino, ctx, &stateid, &arg, gfp_flags);
	अगर (!lgp) अणु
		trace_pnfs_update_layout(ino, pos, count, iomode, lo, शून्य,
					 PNFS_UPDATE_LAYOUT_NOMEM);
		nfs_layoutget_end(lo);
		जाओ out_put_layout_hdr;
	पूर्ण

	lseg = nfs4_proc_layoutget(lgp, &समयout);
	trace_pnfs_update_layout(ino, pos, count, iomode, lo, lseg,
				 PNFS_UPDATE_LAYOUT_SEND_LAYOUTGET);
	nfs_layoutget_end(lo);
	अगर (IS_ERR(lseg)) अणु
		चयन(PTR_ERR(lseg)) अणु
		हाल -EBUSY:
			अगर (समय_after(jअगरfies, giveup))
				lseg = शून्य;
			अवरोध;
		हाल -ERECALLCONFLICT:
		हाल -EAGAIN:
			अवरोध;
		शेष:
			अगर (!nfs_error_is_fatal(PTR_ERR(lseg))) अणु
				pnfs_layout_clear_fail_bit(lo, pnfs_iomode_to_fail_bit(iomode));
				lseg = शून्य;
			पूर्ण
			जाओ out_put_layout_hdr;
		पूर्ण
		अगर (lseg) अणु
			अगर (first)
				pnfs_clear_first_layoutget(lo);
			trace_pnfs_update_layout(ino, pos, count,
				iomode, lo, lseg, PNFS_UPDATE_LAYOUT_RETRY);
			pnfs_put_layout_hdr(lo);
			जाओ lookup_again;
		पूर्ण
	पूर्ण अन्यथा अणु
		pnfs_layout_clear_fail_bit(lo, pnfs_iomode_to_fail_bit(iomode));
	पूर्ण

out_put_layout_hdr:
	अगर (first)
		pnfs_clear_first_layoutget(lo);
	trace_pnfs_update_layout(ino, pos, count, iomode, lo, lseg,
				 PNFS_UPDATE_LAYOUT_EXIT);
	pnfs_put_layout_hdr(lo);
out:
	dprपूर्णांकk("%s: inode %s/%llu pNFS layout segment %s for "
			"(%s, offset: %llu, length: %llu)\n",
			__func__, ino->i_sb->s_id,
			(अचिन्हित दीर्घ दीर्घ)NFS_खाताID(ino),
			IS_ERR_OR_शून्य(lseg) ? "not found" : "found",
			iomode==IOMODE_RW ?  "read/write" : "read-only",
			(अचिन्हित दीर्घ दीर्घ)pos,
			(अचिन्हित दीर्घ दीर्घ)count);
	वापस lseg;
out_unlock:
	spin_unlock(&ino->i_lock);
	जाओ out_put_layout_hdr;
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_update_layout);

अटल bool
pnfs_sanity_check_layout_range(काष्ठा pnfs_layout_range *range)
अणु
	चयन (range->iomode) अणु
	हाल IOMODE_READ:
	हाल IOMODE_RW:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	अगर (range->offset == NFS4_MAX_UINT64)
		वापस false;
	अगर (range->length == 0)
		वापस false;
	अगर (range->length != NFS4_MAX_UINT64 &&
	    range->length > NFS4_MAX_UINT64 - range->offset)
		वापस false;
	वापस true;
पूर्ण

अटल काष्ठा pnfs_layout_hdr *
_pnfs_grab_empty_layout(काष्ठा inode *ino, काष्ठा nfs_खोलो_context *ctx)
अणु
	काष्ठा pnfs_layout_hdr *lo;

	spin_lock(&ino->i_lock);
	lo = pnfs_find_alloc_layout(ino, ctx, GFP_KERNEL);
	अगर (!lo)
		जाओ out_unlock;
	अगर (!test_bit(NFS_LAYOUT_INVALID_STID, &lo->plh_flags))
		जाओ out_unlock;
	अगर (test_bit(NFS_LAYOUT_RETURN, &lo->plh_flags))
		जाओ out_unlock;
	अगर (pnfs_layoutमाला_लो_blocked(lo))
		जाओ out_unlock;
	अगर (test_and_set_bit(NFS_LAYOUT_FIRST_LAYOUTGET, &lo->plh_flags))
		जाओ out_unlock;
	nfs_layoutget_begin(lo);
	spin_unlock(&ino->i_lock);
	_add_to_server_list(lo, NFS_SERVER(ino));
	वापस lo;

out_unlock:
	spin_unlock(&ino->i_lock);
	pnfs_put_layout_hdr(lo);
	वापस शून्य;
पूर्ण

अटल व्योम _lgखोलो_prepare_attached(काष्ठा nfs4_खोलोdata *data,
				     काष्ठा nfs_खोलो_context *ctx)
अणु
	काष्ठा inode *ino = data->dentry->d_inode;
	काष्ठा pnfs_layout_range rng = अणु
		.iomode = (data->o_arg.भ_शेषe & FMODE_WRITE) ?
			  IOMODE_RW: IOMODE_READ,
		.offset = 0,
		.length = NFS4_MAX_UINT64,
	पूर्ण;
	काष्ठा nfs4_layoutget *lgp;
	काष्ठा pnfs_layout_hdr *lo;

	/* Heuristic: करोn't send layoutget अगर we have cached data */
	अगर (rng.iomode == IOMODE_READ &&
	   (i_size_पढ़ो(ino) == 0 || ino->i_mapping->nrpages != 0))
		वापस;

	lo = _pnfs_grab_empty_layout(ino, ctx);
	अगर (!lo)
		वापस;
	lgp = pnfs_alloc_init_layoutget_args(ino, ctx, &current_stateid,
					     &rng, GFP_KERNEL);
	अगर (!lgp) अणु
		pnfs_clear_first_layoutget(lo);
		nfs_layoutget_end(lo);
		pnfs_put_layout_hdr(lo);
		वापस;
	पूर्ण
	data->lgp = lgp;
	data->o_arg.lg_args = &lgp->args;
	data->o_res.lg_res = &lgp->res;
पूर्ण

अटल व्योम _lgखोलो_prepare_भग्नing(काष्ठा nfs4_खोलोdata *data,
				     काष्ठा nfs_खोलो_context *ctx)
अणु
	काष्ठा pnfs_layout_range rng = अणु
		.iomode = (data->o_arg.भ_शेषe & FMODE_WRITE) ?
			  IOMODE_RW: IOMODE_READ,
		.offset = 0,
		.length = NFS4_MAX_UINT64,
	पूर्ण;
	काष्ठा nfs4_layoutget *lgp;

	lgp = pnfs_alloc_init_layoutget_args(शून्य, ctx, &current_stateid,
					     &rng, GFP_KERNEL);
	अगर (!lgp)
		वापस;
	data->lgp = lgp;
	data->o_arg.lg_args = &lgp->args;
	data->o_res.lg_res = &lgp->res;
पूर्ण

व्योम pnfs_lgखोलो_prepare(काष्ठा nfs4_खोलोdata *data,
			 काष्ठा nfs_खोलो_context *ctx)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(data->dir->d_inode);

	अगर (!(pnfs_enabled_sb(server) &&
	      server->pnfs_curr_ld->flags & PNFS_LAYOUTGET_ON_OPEN))
		वापस;
	/* Could check on max_ops, but currently hardcoded high enough */
	अगर (!nfs_server_capable(data->dir->d_inode, NFS_CAP_LGOPEN))
		वापस;
	अगर (data->state)
		_lgखोलो_prepare_attached(data, ctx);
	अन्यथा
		_lgखोलो_prepare_भग्नing(data, ctx);
पूर्ण

व्योम pnfs_parse_lgखोलो(काष्ठा inode *ino, काष्ठा nfs4_layoutget *lgp,
		       काष्ठा nfs_खोलो_context *ctx)
अणु
	काष्ठा pnfs_layout_hdr *lo;
	काष्ठा pnfs_layout_segment *lseg;
	काष्ठा nfs_server *srv = NFS_SERVER(ino);
	u32 iomode;

	अगर (!lgp)
		वापस;
	dprपूर्णांकk("%s: entered with status %i\n", __func__, lgp->res.status);
	अगर (lgp->res.status) अणु
		चयन (lgp->res.status) अणु
		शेष:
			अवरोध;
		/*
		 * Halt lgखोलो attempts अगर the server करोesn't recognise
		 * the "current stateid" value, the layout type, or the
		 * layoutget operation as being valid.
		 * Also अगर it complains about too many ops in the compound
		 * or of the request/reply being too big.
		 */
		हाल -NFS4ERR_BAD_STATEID:
		हाल -NFS4ERR_NOTSUPP:
		हाल -NFS4ERR_REP_TOO_BIG:
		हाल -NFS4ERR_REP_TOO_BIG_TO_CACHE:
		हाल -NFS4ERR_REQ_TOO_BIG:
		हाल -NFS4ERR_TOO_MANY_OPS:
		हाल -NFS4ERR_UNKNOWN_LAYOUTTYPE:
			srv->caps &= ~NFS_CAP_LGOPEN;
		पूर्ण
		वापस;
	पूर्ण
	अगर (!lgp->args.inode) अणु
		lo = _pnfs_grab_empty_layout(ino, ctx);
		अगर (!lo)
			वापस;
		lgp->args.inode = ino;
	पूर्ण अन्यथा
		lo = NFS_I(lgp->args.inode)->layout;

	lseg = pnfs_layout_process(lgp);
	अगर (!IS_ERR(lseg)) अणु
		iomode = lgp->args.range.iomode;
		pnfs_layout_clear_fail_bit(lo, pnfs_iomode_to_fail_bit(iomode));
		pnfs_put_lseg(lseg);
	पूर्ण
पूर्ण

व्योम nfs4_lgखोलो_release(काष्ठा nfs4_layoutget *lgp)
अणु
	अगर (lgp != शून्य) अणु
		काष्ठा inode *inode = lgp->args.inode;
		अगर (inode) अणु
			काष्ठा pnfs_layout_hdr *lo = NFS_I(inode)->layout;
			pnfs_clear_first_layoutget(lo);
			nfs_layoutget_end(lo);
		पूर्ण
		pnfs_layoutget_मुक्त(lgp);
	पूर्ण
पूर्ण

काष्ठा pnfs_layout_segment *
pnfs_layout_process(काष्ठा nfs4_layoutget *lgp)
अणु
	काष्ठा pnfs_layout_hdr *lo = NFS_I(lgp->args.inode)->layout;
	काष्ठा nfs4_layoutget_res *res = &lgp->res;
	काष्ठा pnfs_layout_segment *lseg;
	काष्ठा inode *ino = lo->plh_inode;
	LIST_HEAD(मुक्त_me);

	अगर (!pnfs_sanity_check_layout_range(&res->range))
		वापस ERR_PTR(-EINVAL);

	/* Inject layout blob पूर्णांकo I/O device driver */
	lseg = NFS_SERVER(ino)->pnfs_curr_ld->alloc_lseg(lo, res, lgp->gfp_flags);
	अगर (IS_ERR_OR_शून्य(lseg)) अणु
		अगर (!lseg)
			lseg = ERR_PTR(-ENOMEM);

		dprपूर्णांकk("%s: Could not allocate layout: error %ld\n",
		       __func__, PTR_ERR(lseg));
		वापस lseg;
	पूर्ण

	pnfs_init_lseg(lo, lseg, &res->range, &res->stateid);

	spin_lock(&ino->i_lock);
	अगर (pnfs_layoutमाला_लो_blocked(lo)) अणु
		dprपूर्णांकk("%s forget reply due to state\n", __func__);
		जाओ out_क्रमget;
	पूर्ण

	अगर (nfs4_stateid_match_other(&lo->plh_stateid, &res->stateid)) अणु
		/* existing state ID, make sure the sequence number matches. */
		अगर (pnfs_layout_stateid_blocked(lo, &res->stateid)) अणु
			अगर (!pnfs_layout_is_valid(lo) &&
			    pnfs_is_first_layoutget(lo))
				lo->plh_barrier = 0;
			dprपूर्णांकk("%s forget reply due to sequence\n", __func__);
			जाओ out_क्रमget;
		पूर्ण
		pnfs_set_layout_stateid(lo, &res->stateid, lgp->cred, false);
	पूर्ण अन्यथा अगर (pnfs_layout_is_valid(lo)) अणु
		/*
		 * We got an entirely new state ID.  Mark all segments क्रम the
		 * inode invalid, and retry the layoutget
		 */
		काष्ठा pnfs_layout_range range = अणु
			.iomode = IOMODE_ANY,
			.length = NFS4_MAX_UINT64,
		पूर्ण;
		pnfs_mark_matching_lsegs_वापस(lo, &मुक्त_me, &range, 0);
		जाओ out_क्रमget;
	पूर्ण अन्यथा अणु
		/* We have a completely new layout */
		अगर (!pnfs_is_first_layoutget(lo))
			जाओ out_क्रमget;
		pnfs_set_layout_stateid(lo, &res->stateid, lgp->cred, true);
	पूर्ण

	pnfs_get_lseg(lseg);
	pnfs_layout_insert_lseg(lo, lseg, &मुक्त_me);


	अगर (res->वापस_on_बंद)
		set_bit(NFS_LSEG_ROC, &lseg->pls_flags);

	spin_unlock(&ino->i_lock);
	pnfs_मुक्त_lseg_list(&मुक्त_me);
	वापस lseg;

out_क्रमget:
	spin_unlock(&ino->i_lock);
	lseg->pls_layout = lo;
	NFS_SERVER(ino)->pnfs_curr_ld->मुक्त_lseg(lseg);
	वापस ERR_PTR(-EAGAIN);
पूर्ण

/**
 * pnfs_mark_matching_lsegs_वापस - Free or वापस matching layout segments
 * @lo: poपूर्णांकer to layout header
 * @पंचांगp_list: list header to be used with pnfs_मुक्त_lseg_list()
 * @वापस_range: describe layout segment ranges to be वापसed
 * @seq: stateid seqid to match
 *
 * This function is मुख्यly पूर्णांकended क्रम use by layoutrecall. It attempts
 * to मुक्त the layout segment immediately, or अन्यथा to mark it क्रम वापस
 * as soon as its reference count drops to zero.
 *
 * Returns
 * - 0: a layoutवापस needs to be scheduled.
 * - EBUSY: there are layout segment that are still in use.
 * - ENOENT: there are no layout segments that need to be वापसed.
 */
पूर्णांक
pnfs_mark_matching_lsegs_वापस(काष्ठा pnfs_layout_hdr *lo,
				काष्ठा list_head *पंचांगp_list,
				स्थिर काष्ठा pnfs_layout_range *वापस_range,
				u32 seq)
अणु
	काष्ठा pnfs_layout_segment *lseg, *next;
	पूर्णांक reमुख्यing = 0;

	dprपूर्णांकk("%s:Begin lo %p\n", __func__, lo);

	निश्चित_spin_locked(&lo->plh_inode->i_lock);

	अगर (test_bit(NFS_LAYOUT_RETURN_REQUESTED, &lo->plh_flags))
		पंचांगp_list = &lo->plh_वापस_segs;

	list_क्रम_each_entry_safe(lseg, next, &lo->plh_segs, pls_list)
		अगर (pnfs_match_lseg_recall(lseg, वापस_range, seq)) अणु
			dprपूर्णांकk("%s: marking lseg %p iomode %d "
				"offset %llu length %llu\n", __func__,
				lseg, lseg->pls_range.iomode,
				lseg->pls_range.offset,
				lseg->pls_range.length);
			अगर (test_bit(NFS_LSEG_LAYOUTRETURN, &lseg->pls_flags))
				पंचांगp_list = &lo->plh_वापस_segs;
			अगर (mark_lseg_invalid(lseg, पंचांगp_list))
				जारी;
			reमुख्यing++;
			set_bit(NFS_LSEG_LAYOUTRETURN, &lseg->pls_flags);
		पूर्ण

	अगर (reमुख्यing) अणु
		pnfs_set_plh_वापस_info(lo, वापस_range->iomode, seq);
		वापस -EBUSY;
	पूर्ण

	अगर (!list_empty(&lo->plh_वापस_segs)) अणु
		pnfs_set_plh_वापस_info(lo, वापस_range->iomode, seq);
		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल व्योम
pnfs_mark_layout_क्रम_वापस(काष्ठा inode *inode,
			    स्थिर काष्ठा pnfs_layout_range *range)
अणु
	काष्ठा pnfs_layout_hdr *lo;
	bool वापस_now = false;

	spin_lock(&inode->i_lock);
	lo = NFS_I(inode)->layout;
	अगर (!pnfs_layout_is_valid(lo)) अणु
		spin_unlock(&inode->i_lock);
		वापस;
	पूर्ण
	pnfs_set_plh_वापस_info(lo, range->iomode, 0);
	/*
	 * mark all matching lsegs so that we are sure to have no live
	 * segments at hand when sending layoutवापस. See pnfs_put_lseg()
	 * क्रम how it works.
	 */
	अगर (pnfs_mark_matching_lsegs_वापस(lo, &lo->plh_वापस_segs, range, 0) != -EBUSY) अणु
		स्थिर काष्ठा cred *cred;
		nfs4_stateid stateid;
		क्रमागत pnfs_iomode iomode;

		वापस_now = pnfs_prepare_layoutवापस(lo, &stateid, &cred, &iomode);
		spin_unlock(&inode->i_lock);
		अगर (वापस_now)
			pnfs_send_layoutवापस(lo, &stateid, &cred, iomode, false);
	पूर्ण अन्यथा अणु
		spin_unlock(&inode->i_lock);
		nfs_commit_inode(inode, 0);
	पूर्ण
पूर्ण

व्योम pnfs_error_mark_layout_क्रम_वापस(काष्ठा inode *inode,
				       काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा pnfs_layout_range range = अणु
		.iomode = lseg->pls_range.iomode,
		.offset = 0,
		.length = NFS4_MAX_UINT64,
	पूर्ण;

	pnfs_mark_layout_क्रम_वापस(inode, &range);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_error_mark_layout_क्रम_वापस);

अटल bool
pnfs_layout_can_be_वापसed(काष्ठा pnfs_layout_hdr *lo)
अणु
	वापस pnfs_layout_is_valid(lo) &&
		!test_bit(NFS_LAYOUT_INODE_FREEING, &lo->plh_flags) &&
		!test_bit(NFS_LAYOUT_RETURN, &lo->plh_flags);
पूर्ण

अटल काष्ठा pnfs_layout_segment *
pnfs_find_first_lseg(काष्ठा pnfs_layout_hdr *lo,
		     स्थिर काष्ठा pnfs_layout_range *range,
		     क्रमागत pnfs_iomode iomode)
अणु
	काष्ठा pnfs_layout_segment *lseg;

	list_क्रम_each_entry(lseg, &lo->plh_segs, pls_list) अणु
		अगर (!test_bit(NFS_LSEG_VALID, &lseg->pls_flags))
			जारी;
		अगर (test_bit(NFS_LSEG_LAYOUTRETURN, &lseg->pls_flags))
			जारी;
		अगर (lseg->pls_range.iomode != iomode && iomode != IOMODE_ANY)
			जारी;
		अगर (pnfs_lseg_range_पूर्णांकersecting(&lseg->pls_range, range))
			वापस lseg;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Find खोलो file states whose mode matches that of the range */
अटल bool
pnfs_should_वापस_unused_layout(काष्ठा pnfs_layout_hdr *lo,
				 स्थिर काष्ठा pnfs_layout_range *range)
अणु
	काष्ठा list_head *head;
	काष्ठा nfs_खोलो_context *ctx;
	भ_शेषe_t mode = 0;

	अगर (!pnfs_layout_can_be_वापसed(lo) ||
	    !pnfs_find_first_lseg(lo, range, range->iomode))
		वापस false;

	head = &NFS_I(lo->plh_inode)->खोलो_files;
	list_क्रम_each_entry_rcu(ctx, head, list) अणु
		अगर (ctx->state)
			mode |= ctx->state->state & (FMODE_READ|FMODE_WRITE);
	पूर्ण

	चयन (range->iomode) अणु
	शेष:
		अवरोध;
	हाल IOMODE_READ:
		mode &= ~FMODE_WRITE;
		अवरोध;
	हाल IOMODE_RW:
		अगर (pnfs_find_first_lseg(lo, range, IOMODE_READ))
			mode &= ~FMODE_READ;
	पूर्ण
	वापस mode == 0;
पूर्ण

अटल पूर्णांक
pnfs_layout_वापस_unused_byserver(काष्ठा nfs_server *server, व्योम *data)
अणु
	स्थिर काष्ठा pnfs_layout_range *range = data;
	काष्ठा pnfs_layout_hdr *lo;
	काष्ठा inode *inode;
restart:
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(lo, &server->layouts, plh_layouts) अणु
		अगर (!pnfs_layout_can_be_वापसed(lo) ||
		    test_bit(NFS_LAYOUT_RETURN_REQUESTED, &lo->plh_flags))
			जारी;
		inode = lo->plh_inode;
		spin_lock(&inode->i_lock);
		अगर (!pnfs_should_वापस_unused_layout(lo, range)) अणु
			spin_unlock(&inode->i_lock);
			जारी;
		पूर्ण
		spin_unlock(&inode->i_lock);
		inode = pnfs_grab_inode_layout_hdr(lo);
		अगर (!inode)
			जारी;
		rcu_पढ़ो_unlock();
		pnfs_mark_layout_क्रम_वापस(inode, range);
		iput(inode);
		cond_resched();
		जाओ restart;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

व्योम
pnfs_layout_वापस_unused_byclid(काष्ठा nfs_client *clp,
				 क्रमागत pnfs_iomode iomode)
अणु
	काष्ठा pnfs_layout_range range = अणु
		.iomode = iomode,
		.offset = 0,
		.length = NFS4_MAX_UINT64,
	पूर्ण;

	nfs_client_क्रम_each_server(clp, pnfs_layout_वापस_unused_byserver,
			&range);
पूर्ण

व्योम
pnfs_generic_pg_check_layout(काष्ठा nfs_pageio_descriptor *pgio)
अणु
	अगर (pgio->pg_lseg == शून्य ||
	    test_bit(NFS_LSEG_VALID, &pgio->pg_lseg->pls_flags))
		वापस;
	pnfs_put_lseg(pgio->pg_lseg);
	pgio->pg_lseg = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_pg_check_layout);

/*
 * Check क्रम any पूर्णांकersection between the request and the pgio->pg_lseg,
 * and अगर none, put this pgio->pg_lseg away.
 */
व्योम
pnfs_generic_pg_check_range(काष्ठा nfs_pageio_descriptor *pgio, काष्ठा nfs_page *req)
अणु
	अगर (pgio->pg_lseg && !pnfs_lseg_request_पूर्णांकersecting(pgio->pg_lseg, req)) अणु
		pnfs_put_lseg(pgio->pg_lseg);
		pgio->pg_lseg = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_pg_check_range);

व्योम
pnfs_generic_pg_init_पढ़ो(काष्ठा nfs_pageio_descriptor *pgio, काष्ठा nfs_page *req)
अणु
	u64 rd_size;

	pnfs_generic_pg_check_layout(pgio);
	pnfs_generic_pg_check_range(pgio, req);
	अगर (pgio->pg_lseg == शून्य) अणु
		अगर (pgio->pg_dreq == शून्य)
			rd_size = i_size_पढ़ो(pgio->pg_inode) - req_offset(req);
		अन्यथा
			rd_size = nfs_dreq_bytes_left(pgio->pg_dreq);

		pgio->pg_lseg = pnfs_update_layout(pgio->pg_inode,
						   nfs_req_खोलोctx(req),
						   req_offset(req),
						   rd_size,
						   IOMODE_READ,
						   false,
						   GFP_KERNEL);
		अगर (IS_ERR(pgio->pg_lseg)) अणु
			pgio->pg_error = PTR_ERR(pgio->pg_lseg);
			pgio->pg_lseg = शून्य;
			वापस;
		पूर्ण
	पूर्ण
	/* If no lseg, fall back to पढ़ो through mds */
	अगर (pgio->pg_lseg == शून्य)
		nfs_pageio_reset_पढ़ो_mds(pgio);

पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_pg_init_पढ़ो);

व्योम
pnfs_generic_pg_init_ग_लिखो(काष्ठा nfs_pageio_descriptor *pgio,
			   काष्ठा nfs_page *req, u64 wb_size)
अणु
	pnfs_generic_pg_check_layout(pgio);
	pnfs_generic_pg_check_range(pgio, req);
	अगर (pgio->pg_lseg == शून्य) अणु
		pgio->pg_lseg = pnfs_update_layout(pgio->pg_inode,
						   nfs_req_खोलोctx(req),
						   req_offset(req),
						   wb_size,
						   IOMODE_RW,
						   false,
						   GFP_KERNEL);
		अगर (IS_ERR(pgio->pg_lseg)) अणु
			pgio->pg_error = PTR_ERR(pgio->pg_lseg);
			pgio->pg_lseg = शून्य;
			वापस;
		पूर्ण
	पूर्ण
	/* If no lseg, fall back to ग_लिखो through mds */
	अगर (pgio->pg_lseg == शून्य)
		nfs_pageio_reset_ग_लिखो_mds(pgio);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_pg_init_ग_लिखो);

व्योम
pnfs_generic_pg_cleanup(काष्ठा nfs_pageio_descriptor *desc)
अणु
	अगर (desc->pg_lseg) अणु
		pnfs_put_lseg(desc->pg_lseg);
		desc->pg_lseg = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_pg_cleanup);

/*
 * Return 0 अगर @req cannot be coalesced पूर्णांकo @pgio, otherwise वापस the number
 * of bytes (maximum @req->wb_bytes) that can be coalesced.
 */
माप_प्रकार
pnfs_generic_pg_test(काष्ठा nfs_pageio_descriptor *pgio,
		     काष्ठा nfs_page *prev, काष्ठा nfs_page *req)
अणु
	अचिन्हित पूर्णांक size;
	u64 seg_end, req_start, seg_left;

	size = nfs_generic_pg_test(pgio, prev, req);
	अगर (!size)
		वापस 0;

	/*
	 * 'size' contains the number of bytes left in the current page (up
	 * to the original size asked क्रम in @req->wb_bytes).
	 *
	 * Calculate how many bytes are left in the layout segment
	 * and अगर there are less bytes than 'size', वापस that instead.
	 *
	 * Please also note that 'end_offset' is actually the offset of the
	 * first byte that lies outside the pnfs_layout_range. FIXME?
	 *
	 */
	अगर (pgio->pg_lseg) अणु
		seg_end = pnfs_end_offset(pgio->pg_lseg->pls_range.offset,
				     pgio->pg_lseg->pls_range.length);
		req_start = req_offset(req);

		/* start of request is past the last byte of this segment */
		अगर (req_start >= seg_end)
			वापस 0;

		/* adjust 'size' अगरf there are fewer bytes left in the
		 * segment than what nfs_generic_pg_test वापसed */
		seg_left = seg_end - req_start;
		अगर (seg_left < size)
			size = (अचिन्हित पूर्णांक)seg_left;
	पूर्ण

	वापस size;
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_pg_test);

पूर्णांक pnfs_ग_लिखो_करोne_resend_to_mds(काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा nfs_pageio_descriptor pgio;

	/* Resend all requests through the MDS */
	nfs_pageio_init_ग_लिखो(&pgio, hdr->inode, FLUSH_STABLE, true,
			      hdr->completion_ops);
	set_bit(NFS_CONTEXT_RESEND_WRITES, &hdr->args.context->flags);
	वापस nfs_pageio_resend(&pgio, hdr);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_ग_लिखो_करोne_resend_to_mds);

अटल व्योम pnfs_ld_handle_ग_लिखो_error(काष्ठा nfs_pgio_header *hdr)
अणु

	dprपूर्णांकk("pnfs write error = %d\n", hdr->pnfs_error);
	अगर (NFS_SERVER(hdr->inode)->pnfs_curr_ld->flags &
	    PNFS_LAYOUTRET_ON_ERROR) अणु
		pnfs_वापस_layout(hdr->inode);
	पूर्ण
	अगर (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags))
		hdr->task.tk_status = pnfs_ग_लिखो_करोne_resend_to_mds(hdr);
पूर्ण

/*
 * Called by non rpc-based layout drivers
 */
व्योम pnfs_ld_ग_लिखो_करोne(काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (likely(!hdr->pnfs_error)) अणु
		pnfs_set_layoutcommit(hdr->inode, hdr->lseg,
				hdr->mds_offset + hdr->res.count);
		hdr->mds_ops->rpc_call_करोne(&hdr->task, hdr);
	पूर्ण
	trace_nfs4_pnfs_ग_लिखो(hdr, hdr->pnfs_error);
	अगर (unlikely(hdr->pnfs_error))
		pnfs_ld_handle_ग_लिखो_error(hdr);
	hdr->mds_ops->rpc_release(hdr);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_ld_ग_लिखो_करोne);

अटल व्योम
pnfs_ग_लिखो_through_mds(काष्ठा nfs_pageio_descriptor *desc,
		काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);

	अगर (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags)) अणु
		list_splice_tail_init(&hdr->pages, &mirror->pg_list);
		nfs_pageio_reset_ग_लिखो_mds(desc);
		mirror->pg_recoalesce = 1;
	पूर्ण
	hdr->completion_ops->completion(hdr);
पूर्ण

अटल क्रमागत pnfs_try_status
pnfs_try_to_ग_लिखो_data(काष्ठा nfs_pgio_header *hdr,
			स्थिर काष्ठा rpc_call_ops *call_ops,
			काष्ठा pnfs_layout_segment *lseg,
			पूर्णांक how)
अणु
	काष्ठा inode *inode = hdr->inode;
	क्रमागत pnfs_try_status trypnfs;
	काष्ठा nfs_server *nfss = NFS_SERVER(inode);

	hdr->mds_ops = call_ops;

	dprपूर्णांकk("%s: Writing ino:%lu %u@%llu (how %d)\n", __func__,
		inode->i_ino, hdr->args.count, hdr->args.offset, how);
	trypnfs = nfss->pnfs_curr_ld->ग_लिखो_pagelist(hdr, how);
	अगर (trypnfs != PNFS_NOT_ATTEMPTED)
		nfs_inc_stats(inode, NFSIOS_PNFS_WRITE);
	dprपूर्णांकk("%s End (trypnfs:%d)\n", __func__, trypnfs);
	वापस trypnfs;
पूर्ण

अटल व्योम
pnfs_करो_ग_लिखो(काष्ठा nfs_pageio_descriptor *desc,
	      काष्ठा nfs_pgio_header *hdr, पूर्णांक how)
अणु
	स्थिर काष्ठा rpc_call_ops *call_ops = desc->pg_rpc_callops;
	काष्ठा pnfs_layout_segment *lseg = desc->pg_lseg;
	क्रमागत pnfs_try_status trypnfs;

	trypnfs = pnfs_try_to_ग_लिखो_data(hdr, call_ops, lseg, how);
	चयन (trypnfs) अणु
	हाल PNFS_NOT_ATTEMPTED:
		pnfs_ग_लिखो_through_mds(desc, hdr);
		अवरोध;
	हाल PNFS_ATTEMPTED:
		अवरोध;
	हाल PNFS_TRY_AGAIN:
		/* cleanup hdr and prepare to reकरो pnfs */
		अगर (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags)) अणु
			काष्ठा nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);
			list_splice_init(&hdr->pages, &mirror->pg_list);
			mirror->pg_recoalesce = 1;
		पूर्ण
		hdr->mds_ops->rpc_release(hdr);
	पूर्ण
पूर्ण

अटल व्योम pnfs_ग_लिखोhdr_मुक्त(काष्ठा nfs_pgio_header *hdr)
अणु
	pnfs_put_lseg(hdr->lseg);
	nfs_pgio_header_मुक्त(hdr);
पूर्ण

पूर्णांक
pnfs_generic_pg_ग_लिखोpages(काष्ठा nfs_pageio_descriptor *desc)
अणु
	काष्ठा nfs_pgio_header *hdr;
	पूर्णांक ret;

	hdr = nfs_pgio_header_alloc(desc->pg_rw_ops);
	अगर (!hdr) अणु
		desc->pg_error = -ENOMEM;
		वापस desc->pg_error;
	पूर्ण
	nfs_pgheader_init(desc, hdr, pnfs_ग_लिखोhdr_मुक्त);

	hdr->lseg = pnfs_get_lseg(desc->pg_lseg);
	ret = nfs_generic_pgio(desc, hdr);
	अगर (!ret)
		pnfs_करो_ग_लिखो(desc, hdr, desc->pg_ioflags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_pg_ग_लिखोpages);

पूर्णांक pnfs_पढ़ो_करोne_resend_to_mds(काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा nfs_pageio_descriptor pgio;

	/* Resend all requests through the MDS */
	nfs_pageio_init_पढ़ो(&pgio, hdr->inode, true, hdr->completion_ops);
	वापस nfs_pageio_resend(&pgio, hdr);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_पढ़ो_करोne_resend_to_mds);

अटल व्योम pnfs_ld_handle_पढ़ो_error(काष्ठा nfs_pgio_header *hdr)
अणु
	dprपूर्णांकk("pnfs read error = %d\n", hdr->pnfs_error);
	अगर (NFS_SERVER(hdr->inode)->pnfs_curr_ld->flags &
	    PNFS_LAYOUTRET_ON_ERROR) अणु
		pnfs_वापस_layout(hdr->inode);
	पूर्ण
	अगर (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags))
		hdr->task.tk_status = pnfs_पढ़ो_करोne_resend_to_mds(hdr);
पूर्ण

/*
 * Called by non rpc-based layout drivers
 */
व्योम pnfs_ld_पढ़ो_करोne(काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (likely(!hdr->pnfs_error))
		hdr->mds_ops->rpc_call_करोne(&hdr->task, hdr);
	trace_nfs4_pnfs_पढ़ो(hdr, hdr->pnfs_error);
	अगर (unlikely(hdr->pnfs_error))
		pnfs_ld_handle_पढ़ो_error(hdr);
	hdr->mds_ops->rpc_release(hdr);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_ld_पढ़ो_करोne);

अटल व्योम
pnfs_पढ़ो_through_mds(काष्ठा nfs_pageio_descriptor *desc,
		काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);

	अगर (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags)) अणु
		list_splice_tail_init(&hdr->pages, &mirror->pg_list);
		nfs_pageio_reset_पढ़ो_mds(desc);
		mirror->pg_recoalesce = 1;
	पूर्ण
	hdr->completion_ops->completion(hdr);
पूर्ण

/*
 * Call the appropriate parallel I/O subप्रणाली पढ़ो function.
 */
अटल क्रमागत pnfs_try_status
pnfs_try_to_पढ़ो_data(काष्ठा nfs_pgio_header *hdr,
		       स्थिर काष्ठा rpc_call_ops *call_ops,
		       काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा inode *inode = hdr->inode;
	काष्ठा nfs_server *nfss = NFS_SERVER(inode);
	क्रमागत pnfs_try_status trypnfs;

	hdr->mds_ops = call_ops;

	dprपूर्णांकk("%s: Reading ino:%lu %u@%llu\n",
		__func__, inode->i_ino, hdr->args.count, hdr->args.offset);

	trypnfs = nfss->pnfs_curr_ld->पढ़ो_pagelist(hdr);
	अगर (trypnfs != PNFS_NOT_ATTEMPTED)
		nfs_inc_stats(inode, NFSIOS_PNFS_READ);
	dprपूर्णांकk("%s End (trypnfs:%d)\n", __func__, trypnfs);
	वापस trypnfs;
पूर्ण

/* Resend all requests through pnfs. */
व्योम pnfs_पढ़ो_resend_pnfs(काष्ठा nfs_pgio_header *hdr,
			   अचिन्हित पूर्णांक mirror_idx)
अणु
	काष्ठा nfs_pageio_descriptor pgio;

	अगर (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags)) अणु
		/* Prevent deadlocks with layoutवापस! */
		pnfs_put_lseg(hdr->lseg);
		hdr->lseg = शून्य;

		nfs_pageio_init_पढ़ो(&pgio, hdr->inode, false,
					hdr->completion_ops);
		pgio.pg_mirror_idx = mirror_idx;
		hdr->task.tk_status = nfs_pageio_resend(&pgio, hdr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_पढ़ो_resend_pnfs);

अटल व्योम
pnfs_करो_पढ़ो(काष्ठा nfs_pageio_descriptor *desc, काष्ठा nfs_pgio_header *hdr)
अणु
	स्थिर काष्ठा rpc_call_ops *call_ops = desc->pg_rpc_callops;
	काष्ठा pnfs_layout_segment *lseg = desc->pg_lseg;
	क्रमागत pnfs_try_status trypnfs;

	trypnfs = pnfs_try_to_पढ़ो_data(hdr, call_ops, lseg);
	चयन (trypnfs) अणु
	हाल PNFS_NOT_ATTEMPTED:
		pnfs_पढ़ो_through_mds(desc, hdr);
		अवरोध;
	हाल PNFS_ATTEMPTED:
		अवरोध;
	हाल PNFS_TRY_AGAIN:
		/* cleanup hdr and prepare to reकरो pnfs */
		अगर (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags)) अणु
			काष्ठा nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);
			list_splice_init(&hdr->pages, &mirror->pg_list);
			mirror->pg_recoalesce = 1;
		पूर्ण
		hdr->mds_ops->rpc_release(hdr);
	पूर्ण
पूर्ण

अटल व्योम pnfs_पढ़ोhdr_मुक्त(काष्ठा nfs_pgio_header *hdr)
अणु
	pnfs_put_lseg(hdr->lseg);
	nfs_pgio_header_मुक्त(hdr);
पूर्ण

पूर्णांक
pnfs_generic_pg_पढ़ोpages(काष्ठा nfs_pageio_descriptor *desc)
अणु
	काष्ठा nfs_pgio_header *hdr;
	पूर्णांक ret;

	hdr = nfs_pgio_header_alloc(desc->pg_rw_ops);
	अगर (!hdr) अणु
		desc->pg_error = -ENOMEM;
		वापस desc->pg_error;
	पूर्ण
	nfs_pgheader_init(desc, hdr, pnfs_पढ़ोhdr_मुक्त);
	hdr->lseg = pnfs_get_lseg(desc->pg_lseg);
	ret = nfs_generic_pgio(desc, hdr);
	अगर (!ret)
		pnfs_करो_पढ़ो(desc, hdr);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_pg_पढ़ोpages);

अटल व्योम pnfs_clear_layoutcommitting(काष्ठा inode *inode)
अणु
	अचिन्हित दीर्घ *bitlock = &NFS_I(inode)->flags;

	clear_bit_unlock(NFS_INO_LAYOUTCOMMITTING, bitlock);
	smp_mb__after_atomic();
	wake_up_bit(bitlock, NFS_INO_LAYOUTCOMMITTING);
पूर्ण

/*
 * There can be multiple RW segments.
 */
अटल व्योम pnfs_list_ग_लिखो_lseg(काष्ठा inode *inode, काष्ठा list_head *listp)
अणु
	काष्ठा pnfs_layout_segment *lseg;

	list_क्रम_each_entry(lseg, &NFS_I(inode)->layout->plh_segs, pls_list) अणु
		अगर (lseg->pls_range.iomode == IOMODE_RW &&
		    test_and_clear_bit(NFS_LSEG_LAYOUTCOMMIT, &lseg->pls_flags))
			list_add(&lseg->pls_lc_list, listp);
	पूर्ण
पूर्ण

अटल व्योम pnfs_list_ग_लिखो_lseg_करोne(काष्ठा inode *inode, काष्ठा list_head *listp)
अणु
	काष्ठा pnfs_layout_segment *lseg, *पंचांगp;

	/* Matched by references in pnfs_set_layoutcommit */
	list_क्रम_each_entry_safe(lseg, पंचांगp, listp, pls_lc_list) अणु
		list_del_init(&lseg->pls_lc_list);
		pnfs_put_lseg(lseg);
	पूर्ण

	pnfs_clear_layoutcommitting(inode);
पूर्ण

व्योम pnfs_set_lo_fail(काष्ठा pnfs_layout_segment *lseg)
अणु
	pnfs_layout_io_set_failed(lseg->pls_layout, lseg->pls_range.iomode);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_set_lo_fail);

व्योम
pnfs_set_layoutcommit(काष्ठा inode *inode, काष्ठा pnfs_layout_segment *lseg,
		loff_t end_pos)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	bool mark_as_dirty = false;

	spin_lock(&inode->i_lock);
	अगर (!test_and_set_bit(NFS_INO_LAYOUTCOMMIT, &nfsi->flags)) अणु
		nfsi->layout->plh_lwb = end_pos;
		mark_as_dirty = true;
		dprपूर्णांकk("%s: Set layoutcommit for inode %lu ",
			__func__, inode->i_ino);
	पूर्ण अन्यथा अगर (end_pos > nfsi->layout->plh_lwb)
		nfsi->layout->plh_lwb = end_pos;
	अगर (!test_and_set_bit(NFS_LSEG_LAYOUTCOMMIT, &lseg->pls_flags)) अणु
		/* references matched in nfs4_layoutcommit_release */
		pnfs_get_lseg(lseg);
	पूर्ण
	spin_unlock(&inode->i_lock);
	dprपूर्णांकk("%s: lseg %p end_pos %llu\n",
		__func__, lseg, nfsi->layout->plh_lwb);

	/* अगर pnfs_layoutcommit_inode() runs between inode locks, the next one
	 * will be a noop because NFS_INO_LAYOUTCOMMIT will not be set */
	अगर (mark_as_dirty)
		mark_inode_dirty_sync(inode);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_set_layoutcommit);

व्योम pnfs_cleanup_layoutcommit(काष्ठा nfs4_layoutcommit_data *data)
अणु
	काष्ठा nfs_server *nfss = NFS_SERVER(data->args.inode);

	अगर (nfss->pnfs_curr_ld->cleanup_layoutcommit)
		nfss->pnfs_curr_ld->cleanup_layoutcommit(data);
	pnfs_list_ग_लिखो_lseg_करोne(data->args.inode, &data->lseg_list);
पूर्ण

/*
 * For the LAYOUT4_NFSV4_1_खाताS layout type, NFS_DATA_SYNC WRITEs and
 * NFS_UNSTABLE WRITEs with a COMMIT to data servers must store enough
 * data to disk to allow the server to recover the data अगर it crashes.
 * LAYOUTCOMMIT is only needed when the NFL4_UFLG_COMMIT_THRU_MDS flag
 * is off, and a COMMIT is sent to a data server, or
 * अगर WRITEs to a data server वापस NFS_DATA_SYNC.
 */
पूर्णांक
pnfs_layoutcommit_inode(काष्ठा inode *inode, bool sync)
अणु
	काष्ठा pnfs_layoutdriver_type *ld = NFS_SERVER(inode)->pnfs_curr_ld;
	काष्ठा nfs4_layoutcommit_data *data;
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	loff_t end_pos;
	पूर्णांक status;

	अगर (!pnfs_layoutcommit_outstanding(inode))
		वापस 0;

	dprपूर्णांकk("--> %s inode %lu\n", __func__, inode->i_ino);

	status = -EAGAIN;
	अगर (test_and_set_bit(NFS_INO_LAYOUTCOMMITTING, &nfsi->flags)) अणु
		अगर (!sync)
			जाओ out;
		status = रुको_on_bit_lock_action(&nfsi->flags,
				NFS_INO_LAYOUTCOMMITTING,
				nfs_रुको_bit_समाप्तable,
				TASK_KILLABLE);
		अगर (status)
			जाओ out;
	पूर्ण

	status = -ENOMEM;
	/* Note kzalloc ensures data->res.seq_res.sr_slot == शून्य */
	data = kzalloc(माप(*data), GFP_NOFS);
	अगर (!data)
		जाओ clear_layoutcommitting;

	status = 0;
	spin_lock(&inode->i_lock);
	अगर (!test_and_clear_bit(NFS_INO_LAYOUTCOMMIT, &nfsi->flags))
		जाओ out_unlock;

	INIT_LIST_HEAD(&data->lseg_list);
	pnfs_list_ग_लिखो_lseg(inode, &data->lseg_list);

	end_pos = nfsi->layout->plh_lwb;

	nfs4_stateid_copy(&data->args.stateid, &nfsi->layout->plh_stateid);
	data->cred = get_cred(nfsi->layout->plh_lc_cred);
	spin_unlock(&inode->i_lock);

	data->args.inode = inode;
	nfs_fattr_init(&data->fattr);
	data->args.biपंचांगask = NFS_SERVER(inode)->cache_consistency_biपंचांगask;
	data->res.fattr = &data->fattr;
	अगर (end_pos != 0)
		data->args.lastbytewritten = end_pos - 1;
	अन्यथा
		data->args.lastbytewritten = U64_MAX;
	data->res.server = NFS_SERVER(inode);

	अगर (ld->prepare_layoutcommit) अणु
		status = ld->prepare_layoutcommit(&data->args);
		अगर (status) अणु
			put_cred(data->cred);
			spin_lock(&inode->i_lock);
			set_bit(NFS_INO_LAYOUTCOMMIT, &nfsi->flags);
			अगर (end_pos > nfsi->layout->plh_lwb)
				nfsi->layout->plh_lwb = end_pos;
			जाओ out_unlock;
		पूर्ण
	पूर्ण


	status = nfs4_proc_layoutcommit(data, sync);
out:
	अगर (status)
		mark_inode_dirty_sync(inode);
	dprपूर्णांकk("<-- %s status %d\n", __func__, status);
	वापस status;
out_unlock:
	spin_unlock(&inode->i_lock);
	kमुक्त(data);
clear_layoutcommitting:
	pnfs_clear_layoutcommitting(inode);
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_layoutcommit_inode);

पूर्णांक
pnfs_generic_sync(काष्ठा inode *inode, bool datasync)
अणु
	वापस pnfs_layoutcommit_inode(inode, true);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_sync);

काष्ठा nfs4_threshold *pnfs_mdsthreshold_alloc(व्योम)
अणु
	काष्ठा nfs4_threshold *thp;

	thp = kzalloc(माप(*thp), GFP_NOFS);
	अगर (!thp) अणु
		dprपूर्णांकk("%s mdsthreshold allocation failed\n", __func__);
		वापस शून्य;
	पूर्ण
	वापस thp;
पूर्ण

#अगर IS_ENABLED(CONFIG_NFS_V4_2)
पूर्णांक
pnfs_report_layoutstat(काष्ठा inode *inode, gfp_t gfp_flags)
अणु
	काष्ठा pnfs_layoutdriver_type *ld = NFS_SERVER(inode)->pnfs_curr_ld;
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs42_layoutstat_data *data;
	काष्ठा pnfs_layout_hdr *hdr;
	पूर्णांक status = 0;

	अगर (!pnfs_enabled_sb(server) || !ld->prepare_layoutstats)
		जाओ out;

	अगर (!nfs_server_capable(inode, NFS_CAP_LAYOUTSTATS))
		जाओ out;

	अगर (test_and_set_bit(NFS_INO_LAYOUTSTATS, &nfsi->flags))
		जाओ out;

	spin_lock(&inode->i_lock);
	अगर (!NFS_I(inode)->layout) अणु
		spin_unlock(&inode->i_lock);
		जाओ out_clear_layoutstats;
	पूर्ण
	hdr = NFS_I(inode)->layout;
	pnfs_get_layout_hdr(hdr);
	spin_unlock(&inode->i_lock);

	data = kzalloc(माप(*data), gfp_flags);
	अगर (!data) अणु
		status = -ENOMEM;
		जाओ out_put;
	पूर्ण

	data->args.fh = NFS_FH(inode);
	data->args.inode = inode;
	status = ld->prepare_layoutstats(&data->args);
	अगर (status)
		जाओ out_मुक्त;

	status = nfs42_proc_layoutstats_generic(NFS_SERVER(inode), data);

out:
	dprपूर्णांकk("%s returns %d\n", __func__, status);
	वापस status;

out_मुक्त:
	kमुक्त(data);
out_put:
	pnfs_put_layout_hdr(hdr);
out_clear_layoutstats:
	smp_mb__beक्रमe_atomic();
	clear_bit(NFS_INO_LAYOUTSTATS, &nfsi->flags);
	smp_mb__after_atomic();
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_report_layoutstat);
#पूर्ण_अगर

अचिन्हित पूर्णांक layoutstats_समयr;
module_param(layoutstats_समयr, uपूर्णांक, 0644);
EXPORT_SYMBOL_GPL(layoutstats_समयr);
