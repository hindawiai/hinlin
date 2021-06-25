<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Christoph Hellwig.
 */
#समावेश <linux/blkdev.h>
#समावेश <linux/kmod.h>
#समावेश <linux/file.h>
#समावेश <linux/jhash.h>
#समावेश <linux/sched.h>
#समावेश <linux/sunrpc/addr.h>

#समावेश "pnfs.h"
#समावेश "netns.h"
#समावेश "trace.h"

#घोषणा NFSDDBG_FACILITY                NFSDDBG_PNFS

काष्ठा nfs4_layout अणु
	काष्ठा list_head		lo_perstate;
	काष्ठा nfs4_layout_stateid	*lo_state;
	काष्ठा nfsd4_layout_seg		lo_seg;
पूर्ण;

अटल काष्ठा kmem_cache *nfs4_layout_cache;
अटल काष्ठा kmem_cache *nfs4_layout_stateid_cache;

अटल स्थिर काष्ठा nfsd4_callback_ops nfsd4_cb_layout_ops;
अटल स्थिर काष्ठा lock_manager_operations nfsd4_layouts_lm_ops;

स्थिर काष्ठा nfsd4_layout_ops *nfsd4_layout_ops[LAYOUT_TYPE_MAX] =  अणु
#अगर_घोषित CONFIG_NFSD_FLEXखाताLAYOUT
	[LAYOUT_FLEX_खाताS]	= &ff_layout_ops,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NFSD_BLOCKLAYOUT
	[LAYOUT_BLOCK_VOLUME]	= &bl_layout_ops,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NFSD_SCSILAYOUT
	[LAYOUT_SCSI]		= &scsi_layout_ops,
#पूर्ण_अगर
पूर्ण;

/* pNFS device ID to export fsid mapping */
#घोषणा DEVID_HASH_BITS	8
#घोषणा DEVID_HASH_SIZE	(1 << DEVID_HASH_BITS)
#घोषणा DEVID_HASH_MASK	(DEVID_HASH_SIZE - 1)
अटल u64 nfsd_devid_seq = 1;
अटल काष्ठा list_head nfsd_devid_hash[DEVID_HASH_SIZE];
अटल DEFINE_SPINLOCK(nfsd_devid_lock);

अटल अंतरभूत u32 devid_hashfn(u64 idx)
अणु
	वापस jhash_2words(idx, idx >> 32, 0) & DEVID_HASH_MASK;
पूर्ण

अटल व्योम
nfsd4_alloc_devid_map(स्थिर काष्ठा svc_fh *fhp)
अणु
	स्थिर काष्ठा knfsd_fh *fh = &fhp->fh_handle;
	माप_प्रकार fsid_len = key_len(fh->fh_fsid_type);
	काष्ठा nfsd4_deviceid_map *map, *old;
	पूर्णांक i;

	map = kzalloc(माप(*map) + fsid_len, GFP_KERNEL);
	अगर (!map)
		वापस;

	map->fsid_type = fh->fh_fsid_type;
	स_नकल(&map->fsid, fh->fh_fsid, fsid_len);

	spin_lock(&nfsd_devid_lock);
	अगर (fhp->fh_export->ex_devid_map)
		जाओ out_unlock;

	क्रम (i = 0; i < DEVID_HASH_SIZE; i++) अणु
		list_क्रम_each_entry(old, &nfsd_devid_hash[i], hash) अणु
			अगर (old->fsid_type != fh->fh_fsid_type)
				जारी;
			अगर (स_भेद(old->fsid, fh->fh_fsid,
					key_len(old->fsid_type)))
				जारी;

			fhp->fh_export->ex_devid_map = old;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	map->idx = nfsd_devid_seq++;
	list_add_tail_rcu(&map->hash, &nfsd_devid_hash[devid_hashfn(map->idx)]);
	fhp->fh_export->ex_devid_map = map;
	map = शून्य;

out_unlock:
	spin_unlock(&nfsd_devid_lock);
	kमुक्त(map);
पूर्ण

काष्ठा nfsd4_deviceid_map *
nfsd4_find_devid_map(पूर्णांक idx)
अणु
	काष्ठा nfsd4_deviceid_map *map, *ret = शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(map, &nfsd_devid_hash[devid_hashfn(idx)], hash)
		अगर (map->idx == idx)
			ret = map;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

पूर्णांक
nfsd4_set_deviceid(काष्ठा nfsd4_deviceid *id, स्थिर काष्ठा svc_fh *fhp,
		u32 device_generation)
अणु
	अगर (!fhp->fh_export->ex_devid_map) अणु
		nfsd4_alloc_devid_map(fhp);
		अगर (!fhp->fh_export->ex_devid_map)
			वापस -ENOMEM;
	पूर्ण

	id->fsid_idx = fhp->fh_export->ex_devid_map->idx;
	id->generation = device_generation;
	id->pad = 0;
	वापस 0;
पूर्ण

व्योम nfsd4_setup_layout_type(काष्ठा svc_export *exp)
अणु
#अगर defined(CONFIG_NFSD_BLOCKLAYOUT) || defined(CONFIG_NFSD_SCSILAYOUT)
	काष्ठा super_block *sb = exp->ex_path.mnt->mnt_sb;
#पूर्ण_अगर

	अगर (!(exp->ex_flags & NFSEXP_PNFS))
		वापस;

#अगर_घोषित CONFIG_NFSD_FLEXखाताLAYOUT
	exp->ex_layout_types |= 1 << LAYOUT_FLEX_खाताS;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NFSD_BLOCKLAYOUT
	अगर (sb->s_export_op->get_uuid &&
	    sb->s_export_op->map_blocks &&
	    sb->s_export_op->commit_blocks)
		exp->ex_layout_types |= 1 << LAYOUT_BLOCK_VOLUME;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NFSD_SCSILAYOUT
	अगर (sb->s_export_op->map_blocks &&
	    sb->s_export_op->commit_blocks &&
	    sb->s_bdev && sb->s_bdev->bd_disk->fops->pr_ops &&
		blk_queue_scsi_passthrough(sb->s_bdev->bd_disk->queue))
		exp->ex_layout_types |= 1 << LAYOUT_SCSI;
#पूर्ण_अगर
पूर्ण

अटल व्योम
nfsd4_मुक्त_layout_stateid(काष्ठा nfs4_stid *stid)
अणु
	काष्ठा nfs4_layout_stateid *ls = layoutstateid(stid);
	काष्ठा nfs4_client *clp = ls->ls_stid.sc_client;
	काष्ठा nfs4_file *fp = ls->ls_stid.sc_file;

	trace_nfsd_layoutstate_मुक्त(&ls->ls_stid.sc_stateid);

	spin_lock(&clp->cl_lock);
	list_del_init(&ls->ls_perclnt);
	spin_unlock(&clp->cl_lock);

	spin_lock(&fp->fi_lock);
	list_del_init(&ls->ls_perfile);
	spin_unlock(&fp->fi_lock);

	अगर (!nfsd4_layout_ops[ls->ls_layout_type]->disable_recalls)
		vfs_setlease(ls->ls_file->nf_file, F_UNLCK, शून्य, (व्योम **)&ls);
	nfsd_file_put(ls->ls_file);

	अगर (ls->ls_recalled)
		atomic_dec(&ls->ls_stid.sc_file->fi_lo_recalls);

	kmem_cache_मुक्त(nfs4_layout_stateid_cache, ls);
पूर्ण

अटल पूर्णांक
nfsd4_layout_setlease(काष्ठा nfs4_layout_stateid *ls)
अणु
	काष्ठा file_lock *fl;
	पूर्णांक status;

	अगर (nfsd4_layout_ops[ls->ls_layout_type]->disable_recalls)
		वापस 0;

	fl = locks_alloc_lock();
	अगर (!fl)
		वापस -ENOMEM;
	locks_init_lock(fl);
	fl->fl_lmops = &nfsd4_layouts_lm_ops;
	fl->fl_flags = FL_LAYOUT;
	fl->fl_type = F_RDLCK;
	fl->fl_end = OFFSET_MAX;
	fl->fl_owner = ls;
	fl->fl_pid = current->tgid;
	fl->fl_file = ls->ls_file->nf_file;

	status = vfs_setlease(fl->fl_file, fl->fl_type, &fl, शून्य);
	अगर (status) अणु
		locks_मुक्त_lock(fl);
		वापस status;
	पूर्ण
	BUG_ON(fl != शून्य);
	वापस 0;
पूर्ण

अटल काष्ठा nfs4_layout_stateid *
nfsd4_alloc_layout_stateid(काष्ठा nfsd4_compound_state *cstate,
		काष्ठा nfs4_stid *parent, u32 layout_type)
अणु
	काष्ठा nfs4_client *clp = cstate->clp;
	काष्ठा nfs4_file *fp = parent->sc_file;
	काष्ठा nfs4_layout_stateid *ls;
	काष्ठा nfs4_stid *stp;

	stp = nfs4_alloc_stid(cstate->clp, nfs4_layout_stateid_cache,
					nfsd4_मुक्त_layout_stateid);
	अगर (!stp)
		वापस शून्य;

	get_nfs4_file(fp);
	stp->sc_file = fp;

	ls = layoutstateid(stp);
	INIT_LIST_HEAD(&ls->ls_perclnt);
	INIT_LIST_HEAD(&ls->ls_perfile);
	spin_lock_init(&ls->ls_lock);
	INIT_LIST_HEAD(&ls->ls_layouts);
	mutex_init(&ls->ls_mutex);
	ls->ls_layout_type = layout_type;
	nfsd4_init_cb(&ls->ls_recall, clp, &nfsd4_cb_layout_ops,
			NFSPROC4_CLNT_CB_LAYOUT);

	अगर (parent->sc_type == NFS4_DELEG_STID)
		ls->ls_file = nfsd_file_get(fp->fi_deleg_file);
	अन्यथा
		ls->ls_file = find_any_file(fp);
	BUG_ON(!ls->ls_file);

	अगर (nfsd4_layout_setlease(ls)) अणु
		nfsd_file_put(ls->ls_file);
		put_nfs4_file(fp);
		kmem_cache_मुक्त(nfs4_layout_stateid_cache, ls);
		वापस शून्य;
	पूर्ण

	spin_lock(&clp->cl_lock);
	stp->sc_type = NFS4_LAYOUT_STID;
	list_add(&ls->ls_perclnt, &clp->cl_lo_states);
	spin_unlock(&clp->cl_lock);

	spin_lock(&fp->fi_lock);
	list_add(&ls->ls_perfile, &fp->fi_lo_states);
	spin_unlock(&fp->fi_lock);

	trace_nfsd_layoutstate_alloc(&ls->ls_stid.sc_stateid);
	वापस ls;
पूर्ण

__be32
nfsd4_preprocess_layout_stateid(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate, stateid_t *stateid,
		bool create, u32 layout_type, काष्ठा nfs4_layout_stateid **lsp)
अणु
	काष्ठा nfs4_layout_stateid *ls;
	काष्ठा nfs4_stid *stid;
	अचिन्हित अक्षर typemask = NFS4_LAYOUT_STID;
	__be32 status;

	अगर (create)
		typemask |= (NFS4_OPEN_STID | NFS4_LOCK_STID | NFS4_DELEG_STID);

	status = nfsd4_lookup_stateid(cstate, stateid, typemask, &stid,
			net_generic(SVC_NET(rqstp), nfsd_net_id));
	अगर (status)
		जाओ out;

	अगर (!fh_match(&cstate->current_fh.fh_handle,
		      &stid->sc_file->fi_fhandle)) अणु
		status = nfserr_bad_stateid;
		जाओ out_put_stid;
	पूर्ण

	अगर (stid->sc_type != NFS4_LAYOUT_STID) अणु
		ls = nfsd4_alloc_layout_stateid(cstate, stid, layout_type);
		nfs4_put_stid(stid);

		status = nfserr_jukebox;
		अगर (!ls)
			जाओ out;
		mutex_lock(&ls->ls_mutex);
	पूर्ण अन्यथा अणु
		ls = container_of(stid, काष्ठा nfs4_layout_stateid, ls_stid);

		status = nfserr_bad_stateid;
		mutex_lock(&ls->ls_mutex);
		अगर (nfsd4_stateid_generation_after(stateid, &stid->sc_stateid))
			जाओ out_unlock_stid;
		अगर (layout_type != ls->ls_layout_type)
			जाओ out_unlock_stid;
	पूर्ण

	*lsp = ls;
	वापस 0;

out_unlock_stid:
	mutex_unlock(&ls->ls_mutex);
out_put_stid:
	nfs4_put_stid(stid);
out:
	वापस status;
पूर्ण

अटल व्योम
nfsd4_recall_file_layout(काष्ठा nfs4_layout_stateid *ls)
अणु
	spin_lock(&ls->ls_lock);
	अगर (ls->ls_recalled)
		जाओ out_unlock;

	ls->ls_recalled = true;
	atomic_inc(&ls->ls_stid.sc_file->fi_lo_recalls);
	अगर (list_empty(&ls->ls_layouts))
		जाओ out_unlock;

	trace_nfsd_layout_recall(&ls->ls_stid.sc_stateid);

	refcount_inc(&ls->ls_stid.sc_count);
	nfsd4_run_cb(&ls->ls_recall);

out_unlock:
	spin_unlock(&ls->ls_lock);
पूर्ण

अटल अंतरभूत u64
layout_end(काष्ठा nfsd4_layout_seg *seg)
अणु
	u64 end = seg->offset + seg->length;
	वापस end >= seg->offset ? end : NFS4_MAX_UINT64;
पूर्ण

अटल व्योम
layout_update_len(काष्ठा nfsd4_layout_seg *lo, u64 end)
अणु
	अगर (end == NFS4_MAX_UINT64)
		lo->length = NFS4_MAX_UINT64;
	अन्यथा
		lo->length = end - lo->offset;
पूर्ण

अटल bool
layouts_overlapping(काष्ठा nfs4_layout *lo, काष्ठा nfsd4_layout_seg *s)
अणु
	अगर (s->iomode != IOMODE_ANY && s->iomode != lo->lo_seg.iomode)
		वापस false;
	अगर (layout_end(&lo->lo_seg) <= s->offset)
		वापस false;
	अगर (layout_end(s) <= lo->lo_seg.offset)
		वापस false;
	वापस true;
पूर्ण

अटल bool
layouts_try_merge(काष्ठा nfsd4_layout_seg *lo, काष्ठा nfsd4_layout_seg *new)
अणु
	अगर (lo->iomode != new->iomode)
		वापस false;
	अगर (layout_end(new) < lo->offset)
		वापस false;
	अगर (layout_end(lo) < new->offset)
		वापस false;

	lo->offset = min(lo->offset, new->offset);
	layout_update_len(lo, max(layout_end(lo), layout_end(new)));
	वापस true;
पूर्ण

अटल __be32
nfsd4_recall_conflict(काष्ठा nfs4_layout_stateid *ls)
अणु
	काष्ठा nfs4_file *fp = ls->ls_stid.sc_file;
	काष्ठा nfs4_layout_stateid *l, *n;
	__be32 nfserr = nfs_ok;

	निश्चित_spin_locked(&fp->fi_lock);

	list_क्रम_each_entry_safe(l, n, &fp->fi_lo_states, ls_perfile) अणु
		अगर (l != ls) अणु
			nfsd4_recall_file_layout(l);
			nfserr = nfserr_recallconflict;
		पूर्ण
	पूर्ण

	वापस nfserr;
पूर्ण

__be32
nfsd4_insert_layout(काष्ठा nfsd4_layoutget *lgp, काष्ठा nfs4_layout_stateid *ls)
अणु
	काष्ठा nfsd4_layout_seg *seg = &lgp->lg_seg;
	काष्ठा nfs4_file *fp = ls->ls_stid.sc_file;
	काष्ठा nfs4_layout *lp, *new = शून्य;
	__be32 nfserr;

	spin_lock(&fp->fi_lock);
	nfserr = nfsd4_recall_conflict(ls);
	अगर (nfserr)
		जाओ out;
	spin_lock(&ls->ls_lock);
	list_क्रम_each_entry(lp, &ls->ls_layouts, lo_perstate) अणु
		अगर (layouts_try_merge(&lp->lo_seg, seg))
			जाओ करोne;
	पूर्ण
	spin_unlock(&ls->ls_lock);
	spin_unlock(&fp->fi_lock);

	new = kmem_cache_alloc(nfs4_layout_cache, GFP_KERNEL);
	अगर (!new)
		वापस nfserr_jukebox;
	स_नकल(&new->lo_seg, seg, माप(lp->lo_seg));
	new->lo_state = ls;

	spin_lock(&fp->fi_lock);
	nfserr = nfsd4_recall_conflict(ls);
	अगर (nfserr)
		जाओ out;
	spin_lock(&ls->ls_lock);
	list_क्रम_each_entry(lp, &ls->ls_layouts, lo_perstate) अणु
		अगर (layouts_try_merge(&lp->lo_seg, seg))
			जाओ करोne;
	पूर्ण

	refcount_inc(&ls->ls_stid.sc_count);
	list_add_tail(&new->lo_perstate, &ls->ls_layouts);
	new = शून्य;
करोne:
	nfs4_inc_and_copy_stateid(&lgp->lg_sid, &ls->ls_stid);
	spin_unlock(&ls->ls_lock);
out:
	spin_unlock(&fp->fi_lock);
	अगर (new)
		kmem_cache_मुक्त(nfs4_layout_cache, new);
	वापस nfserr;
पूर्ण

अटल व्योम
nfsd4_मुक्त_layouts(काष्ठा list_head *reaplist)
अणु
	जबतक (!list_empty(reaplist)) अणु
		काष्ठा nfs4_layout *lp = list_first_entry(reaplist,
				काष्ठा nfs4_layout, lo_perstate);

		list_del(&lp->lo_perstate);
		nfs4_put_stid(&lp->lo_state->ls_stid);
		kmem_cache_मुक्त(nfs4_layout_cache, lp);
	पूर्ण
पूर्ण

अटल व्योम
nfsd4_वापस_file_layout(काष्ठा nfs4_layout *lp, काष्ठा nfsd4_layout_seg *seg,
		काष्ठा list_head *reaplist)
अणु
	काष्ठा nfsd4_layout_seg *lo = &lp->lo_seg;
	u64 end = layout_end(lo);

	अगर (seg->offset <= lo->offset) अणु
		अगर (layout_end(seg) >= end) अणु
			list_move_tail(&lp->lo_perstate, reaplist);
			वापस;
		पूर्ण
		lo->offset = layout_end(seg);
	पूर्ण अन्यथा अणु
		/* retain the whole layout segment on a split. */
		अगर (layout_end(seg) < end) अणु
			dprपूर्णांकk("%s: split not supported\n", __func__);
			वापस;
		पूर्ण
		end = seg->offset;
	पूर्ण

	layout_update_len(lo, end);
पूर्ण

__be32
nfsd4_वापस_file_layouts(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate,
		काष्ठा nfsd4_layoutवापस *lrp)
अणु
	काष्ठा nfs4_layout_stateid *ls;
	काष्ठा nfs4_layout *lp, *n;
	LIST_HEAD(reaplist);
	__be32 nfserr;
	पूर्णांक found = 0;

	nfserr = nfsd4_preprocess_layout_stateid(rqstp, cstate, &lrp->lr_sid,
						false, lrp->lr_layout_type,
						&ls);
	अगर (nfserr) अणु
		trace_nfsd_layout_वापस_lookup_fail(&lrp->lr_sid);
		वापस nfserr;
	पूर्ण

	spin_lock(&ls->ls_lock);
	list_क्रम_each_entry_safe(lp, n, &ls->ls_layouts, lo_perstate) अणु
		अगर (layouts_overlapping(lp, &lrp->lr_seg)) अणु
			nfsd4_वापस_file_layout(lp, &lrp->lr_seg, &reaplist);
			found++;
		पूर्ण
	पूर्ण
	अगर (!list_empty(&ls->ls_layouts)) अणु
		अगर (found)
			nfs4_inc_and_copy_stateid(&lrp->lr_sid, &ls->ls_stid);
		lrp->lrs_present = 1;
	पूर्ण अन्यथा अणु
		trace_nfsd_layoutstate_unhash(&ls->ls_stid.sc_stateid);
		nfs4_unhash_stid(&ls->ls_stid);
		lrp->lrs_present = 0;
	पूर्ण
	spin_unlock(&ls->ls_lock);

	mutex_unlock(&ls->ls_mutex);
	nfs4_put_stid(&ls->ls_stid);
	nfsd4_मुक्त_layouts(&reaplist);
	वापस nfs_ok;
पूर्ण

__be32
nfsd4_वापस_client_layouts(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate,
		काष्ठा nfsd4_layoutवापस *lrp)
अणु
	काष्ठा nfs4_layout_stateid *ls, *n;
	काष्ठा nfs4_client *clp = cstate->clp;
	काष्ठा nfs4_layout *lp, *t;
	LIST_HEAD(reaplist);

	lrp->lrs_present = 0;

	spin_lock(&clp->cl_lock);
	list_क्रम_each_entry_safe(ls, n, &clp->cl_lo_states, ls_perclnt) अणु
		अगर (ls->ls_layout_type != lrp->lr_layout_type)
			जारी;

		अगर (lrp->lr_वापस_type == RETURN_FSID &&
		    !fh_fsid_match(&ls->ls_stid.sc_file->fi_fhandle,
				   &cstate->current_fh.fh_handle))
			जारी;

		spin_lock(&ls->ls_lock);
		list_क्रम_each_entry_safe(lp, t, &ls->ls_layouts, lo_perstate) अणु
			अगर (lrp->lr_seg.iomode == IOMODE_ANY ||
			    lrp->lr_seg.iomode == lp->lo_seg.iomode)
				list_move_tail(&lp->lo_perstate, &reaplist);
		पूर्ण
		spin_unlock(&ls->ls_lock);
	पूर्ण
	spin_unlock(&clp->cl_lock);

	nfsd4_मुक्त_layouts(&reaplist);
	वापस 0;
पूर्ण

अटल व्योम
nfsd4_वापस_all_layouts(काष्ठा nfs4_layout_stateid *ls,
		काष्ठा list_head *reaplist)
अणु
	spin_lock(&ls->ls_lock);
	list_splice_init(&ls->ls_layouts, reaplist);
	spin_unlock(&ls->ls_lock);
पूर्ण

व्योम
nfsd4_वापस_all_client_layouts(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfs4_layout_stateid *ls, *n;
	LIST_HEAD(reaplist);

	spin_lock(&clp->cl_lock);
	list_क्रम_each_entry_safe(ls, n, &clp->cl_lo_states, ls_perclnt)
		nfsd4_वापस_all_layouts(ls, &reaplist);
	spin_unlock(&clp->cl_lock);

	nfsd4_मुक्त_layouts(&reaplist);
पूर्ण

व्योम
nfsd4_वापस_all_file_layouts(काष्ठा nfs4_client *clp, काष्ठा nfs4_file *fp)
अणु
	काष्ठा nfs4_layout_stateid *ls, *n;
	LIST_HEAD(reaplist);

	spin_lock(&fp->fi_lock);
	list_क्रम_each_entry_safe(ls, n, &fp->fi_lo_states, ls_perfile) अणु
		अगर (ls->ls_stid.sc_client == clp)
			nfsd4_वापस_all_layouts(ls, &reaplist);
	पूर्ण
	spin_unlock(&fp->fi_lock);

	nfsd4_मुक्त_layouts(&reaplist);
पूर्ण

अटल व्योम
nfsd4_cb_layout_fail(काष्ठा nfs4_layout_stateid *ls)
अणु
	काष्ठा nfs4_client *clp = ls->ls_stid.sc_client;
	अक्षर addr_str[INET6_ADDRSTRLEN];
	अटल अक्षर स्थिर nfsd_recall_failed[] = "/sbin/nfsd-recall-failed";
	अटल अक्षर *envp[] = अणु
		"HOME=/",
		"TERM=linux",
		"PATH=/sbin:/usr/sbin:/bin:/usr/bin",
		शून्य
	पूर्ण;
	अक्षर *argv[8];
	पूर्णांक error;

	rpc_ntop((काष्ठा sockaddr *)&clp->cl_addr, addr_str, माप(addr_str));

	prपूर्णांकk(KERN_WARNING
		"nfsd: client %s failed to respond to layout recall. "
		"  Fencing..\n", addr_str);

	argv[0] = (अक्षर *)nfsd_recall_failed;
	argv[1] = addr_str;
	argv[2] = ls->ls_file->nf_file->f_path.mnt->mnt_sb->s_id;
	argv[3] = शून्य;

	error = call_usermodehelper(nfsd_recall_failed, argv, envp,
				    UMH_WAIT_PROC);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "nfsd: fence failed for client %s: %d!\n",
			addr_str, error);
	पूर्ण
पूर्ण

अटल व्योम
nfsd4_cb_layout_prepare(काष्ठा nfsd4_callback *cb)
अणु
	काष्ठा nfs4_layout_stateid *ls =
		container_of(cb, काष्ठा nfs4_layout_stateid, ls_recall);

	mutex_lock(&ls->ls_mutex);
	nfs4_inc_and_copy_stateid(&ls->ls_recall_sid, &ls->ls_stid);
	mutex_unlock(&ls->ls_mutex);
पूर्ण

अटल पूर्णांक
nfsd4_cb_layout_करोne(काष्ठा nfsd4_callback *cb, काष्ठा rpc_task *task)
अणु
	काष्ठा nfs4_layout_stateid *ls =
		container_of(cb, काष्ठा nfs4_layout_stateid, ls_recall);
	काष्ठा nfsd_net *nn;
	kसमय_प्रकार now, cutoff;
	स्थिर काष्ठा nfsd4_layout_ops *ops;


	चयन (task->tk_status) अणु
	हाल 0:
	हाल -NFS4ERR_DELAY:
		/*
		 * Anything left? If not, then call it करोne. Note that we करोn't
		 * take the spinlock since this is an optimization and nothing
		 * should get added until the cb counter goes to zero.
		 */
		अगर (list_empty(&ls->ls_layouts))
			वापस 1;

		/* Poll the client until it's करोne with the layout */
		now = kसमय_get();
		nn = net_generic(ls->ls_stid.sc_client->net, nfsd_net_id);

		/* Client माला_लो 2 lease periods to वापस it */
		cutoff = kसमय_add_ns(task->tk_start,
					 (u64)nn->nfsd4_lease * NSEC_PER_SEC * 2);

		अगर (kसमय_beक्रमe(now, cutoff)) अणु
			rpc_delay(task, HZ/100); /* 10 mili-seconds */
			वापस 0;
		पूर्ण
		fallthrough;
	शेष:
		/*
		 * Unknown error or non-responding client, we'll need to fence.
		 */
		trace_nfsd_layout_recall_fail(&ls->ls_stid.sc_stateid);

		ops = nfsd4_layout_ops[ls->ls_layout_type];
		अगर (ops->fence_client)
			ops->fence_client(ls);
		अन्यथा
			nfsd4_cb_layout_fail(ls);
		वापस 1;
	हाल -NFS4ERR_NOMATCHING_LAYOUT:
		trace_nfsd_layout_recall_करोne(&ls->ls_stid.sc_stateid);
		task->tk_status = 0;
		वापस 1;
	पूर्ण
पूर्ण

अटल व्योम
nfsd4_cb_layout_release(काष्ठा nfsd4_callback *cb)
अणु
	काष्ठा nfs4_layout_stateid *ls =
		container_of(cb, काष्ठा nfs4_layout_stateid, ls_recall);
	LIST_HEAD(reaplist);

	trace_nfsd_layout_recall_release(&ls->ls_stid.sc_stateid);

	nfsd4_वापस_all_layouts(ls, &reaplist);
	nfsd4_मुक्त_layouts(&reaplist);
	nfs4_put_stid(&ls->ls_stid);
पूर्ण

अटल स्थिर काष्ठा nfsd4_callback_ops nfsd4_cb_layout_ops = अणु
	.prepare	= nfsd4_cb_layout_prepare,
	.करोne		= nfsd4_cb_layout_करोne,
	.release	= nfsd4_cb_layout_release,
पूर्ण;

अटल bool
nfsd4_layout_lm_अवरोध(काष्ठा file_lock *fl)
अणु
	/*
	 * We करोn't want the locks code to समयout the lease क्रम us;
	 * we'll remove it ourself if a layout isn't वापसed
	 * in समय:
	 */
	fl->fl_अवरोध_समय = 0;
	nfsd4_recall_file_layout(fl->fl_owner);
	वापस false;
पूर्ण

अटल पूर्णांक
nfsd4_layout_lm_change(काष्ठा file_lock *onlist, पूर्णांक arg,
		काष्ठा list_head *dispose)
अणु
	BUG_ON(!(arg & F_UNLCK));
	वापस lease_modअगरy(onlist, arg, dispose);
पूर्ण

अटल स्थिर काष्ठा lock_manager_operations nfsd4_layouts_lm_ops = अणु
	.lm_अवरोध	= nfsd4_layout_lm_अवरोध,
	.lm_change	= nfsd4_layout_lm_change,
पूर्ण;

पूर्णांक
nfsd4_init_pnfs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DEVID_HASH_SIZE; i++)
		INIT_LIST_HEAD(&nfsd_devid_hash[i]);

	nfs4_layout_cache = kmem_cache_create("nfs4_layout",
			माप(काष्ठा nfs4_layout), 0, 0, शून्य);
	अगर (!nfs4_layout_cache)
		वापस -ENOMEM;

	nfs4_layout_stateid_cache = kmem_cache_create("nfs4_layout_stateid",
			माप(काष्ठा nfs4_layout_stateid), 0, 0, शून्य);
	अगर (!nfs4_layout_stateid_cache) अणु
		kmem_cache_destroy(nfs4_layout_cache);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम
nfsd4_निकास_pnfs(व्योम)
अणु
	पूर्णांक i;

	kmem_cache_destroy(nfs4_layout_cache);
	kmem_cache_destroy(nfs4_layout_stateid_cache);

	क्रम (i = 0; i < DEVID_HASH_SIZE; i++) अणु
		काष्ठा nfsd4_deviceid_map *map, *n;

		list_क्रम_each_entry_safe(map, n, &nfsd_devid_hash[i], hash)
			kमुक्त(map);
	पूर्ण
पूर्ण
