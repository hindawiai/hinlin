<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Module क्रम pnfs flexfile layout driver.
 *
 * Copyright (c) 2014, Primary Data, Inc. All rights reserved.
 *
 * Tao Peng <bergwolf@primarydata.com>
 */

#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/nfs_page.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/mm.h>

#समावेश <linux/sunrpc/metrics.h>

#समावेश "flexfilelayout.h"
#समावेश "../nfs4session.h"
#समावेश "../nfs4idmap.h"
#समावेश "../internal.h"
#समावेश "../delegation.h"
#समावेश "../nfs4trace.h"
#समावेश "../iostat.h"
#समावेश "../nfs.h"
#समावेश "../nfs42.h"

#घोषणा NFSDBG_FACILITY         NFSDBG_PNFS_LD

#घोषणा FF_LAYOUT_POLL_RETRY_MAX     (15*HZ)
#घोषणा FF_LAYOUTRETURN_MAXERR 20

अटल अचिन्हित लघु io_maxretrans;

अटल स्थिर काष्ठा pnfs_commit_ops ff_layout_commit_ops;
अटल व्योम ff_layout_पढ़ो_record_layoutstats_करोne(काष्ठा rpc_task *task,
		काष्ठा nfs_pgio_header *hdr);
अटल पूर्णांक ff_layout_mirror_prepare_stats(काष्ठा pnfs_layout_hdr *lo,
			       काष्ठा nfs42_layoutstat_devinfo *devinfo,
			       पूर्णांक dev_limit);
अटल व्योम ff_layout_encode_ff_layoutupdate(काष्ठा xdr_stream *xdr,
			      स्थिर काष्ठा nfs42_layoutstat_devinfo *devinfo,
			      काष्ठा nfs4_ff_layout_mirror *mirror);

अटल काष्ठा pnfs_layout_hdr *
ff_layout_alloc_layout_hdr(काष्ठा inode *inode, gfp_t gfp_flags)
अणु
	काष्ठा nfs4_flexfile_layout *ffl;

	ffl = kzalloc(माप(*ffl), gfp_flags);
	अगर (ffl) अणु
		pnfs_init_ds_commit_info(&ffl->commit_info);
		INIT_LIST_HEAD(&ffl->error_list);
		INIT_LIST_HEAD(&ffl->mirrors);
		ffl->last_report_समय = kसमय_get();
		ffl->commit_info.ops = &ff_layout_commit_ops;
		वापस &ffl->generic_hdr;
	पूर्ण अन्यथा
		वापस शून्य;
पूर्ण

अटल व्योम
ff_layout_मुक्त_layout_hdr(काष्ठा pnfs_layout_hdr *lo)
अणु
	काष्ठा nfs4_flexfile_layout *ffl = FF_LAYOUT_FROM_HDR(lo);
	काष्ठा nfs4_ff_layout_ds_err *err, *n;

	list_क्रम_each_entry_safe(err, n, &ffl->error_list, list) अणु
		list_del(&err->list);
		kमुक्त(err);
	पूर्ण
	kमुक्त_rcu(ffl, generic_hdr.plh_rcu);
पूर्ण

अटल पूर्णांक decode_pnfs_stateid(काष्ठा xdr_stream *xdr, nfs4_stateid *stateid)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, NFS4_STATEID_SIZE);
	अगर (unlikely(p == शून्य))
		वापस -ENOBUFS;
	stateid->type = NFS4_PNFS_DS_STATEID_TYPE;
	स_नकल(stateid->data, p, NFS4_STATEID_SIZE);
	dprपूर्णांकk("%s: stateid id= [%x%x%x%x]\n", __func__,
		p[0], p[1], p[2], p[3]);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_deviceid(काष्ठा xdr_stream *xdr, काष्ठा nfs4_deviceid *devid)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, NFS4_DEVICEID4_SIZE);
	अगर (unlikely(!p))
		वापस -ENOBUFS;
	स_नकल(devid, p, NFS4_DEVICEID4_SIZE);
	nfs4_prपूर्णांक_deviceid(devid);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_nfs_fh(काष्ठा xdr_stream *xdr, काष्ठा nfs_fh *fh)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -ENOBUFS;
	fh->size = be32_to_cpup(p++);
	अगर (fh->size > NFS_MAXFHSIZE) अणु
		prपूर्णांकk(KERN_ERR "NFS flexfiles: Too big fh received %d\n",
		       fh->size);
		वापस -EOVERFLOW;
	पूर्ण
	/* fh.data */
	p = xdr_अंतरभूत_decode(xdr, fh->size);
	अगर (unlikely(!p))
		वापस -ENOBUFS;
	स_नकल(&fh->data, p, fh->size);
	dprपूर्णांकk("%s: fh len %d\n", __func__, fh->size);

	वापस 0;
पूर्ण

/*
 * Currently only stringअगरied uids and gids are accepted.
 * I.e., kerberos is not supported to the DSes, so no pricipals.
 *
 * That means that one common function will suffice, but when
 * principals are added, this should be split to accomodate
 * calls to both nfs_map_name_to_uid() and nfs_map_group_to_gid().
 */
अटल पूर्णांक
decode_name(काष्ठा xdr_stream *xdr, u32 *id)
अणु
	__be32 *p;
	पूर्णांक len;

	/* opaque_length(4)*/
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -ENOBUFS;
	len = be32_to_cpup(p++);
	अगर (len < 0)
		वापस -EINVAL;

	dprपूर्णांकk("%s: len %u\n", __func__, len);

	/* opaque body */
	p = xdr_अंतरभूत_decode(xdr, len);
	अगर (unlikely(!p))
		वापस -ENOBUFS;

	अगर (!nfs_map_string_to_numeric((अक्षर *)p, len, id))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल bool ff_mirror_match_fh(स्थिर काष्ठा nfs4_ff_layout_mirror *m1,
		स्थिर काष्ठा nfs4_ff_layout_mirror *m2)
अणु
	पूर्णांक i, j;

	अगर (m1->fh_versions_cnt != m2->fh_versions_cnt)
		वापस false;
	क्रम (i = 0; i < m1->fh_versions_cnt; i++) अणु
		bool found_fh = false;
		क्रम (j = 0; j < m2->fh_versions_cnt; j++) अणु
			अगर (nfs_compare_fh(&m1->fh_versions[i],
					&m2->fh_versions[j]) == 0) अणु
				found_fh = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!found_fh)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल काष्ठा nfs4_ff_layout_mirror *
ff_layout_add_mirror(काष्ठा pnfs_layout_hdr *lo,
		काष्ठा nfs4_ff_layout_mirror *mirror)
अणु
	काष्ठा nfs4_flexfile_layout *ff_layout = FF_LAYOUT_FROM_HDR(lo);
	काष्ठा nfs4_ff_layout_mirror *pos;
	काष्ठा inode *inode = lo->plh_inode;

	spin_lock(&inode->i_lock);
	list_क्रम_each_entry(pos, &ff_layout->mirrors, mirrors) अणु
		अगर (स_भेद(&mirror->devid, &pos->devid, माप(pos->devid)) != 0)
			जारी;
		अगर (!ff_mirror_match_fh(mirror, pos))
			जारी;
		अगर (refcount_inc_not_zero(&pos->ref)) अणु
			spin_unlock(&inode->i_lock);
			वापस pos;
		पूर्ण
	पूर्ण
	list_add(&mirror->mirrors, &ff_layout->mirrors);
	mirror->layout = lo;
	spin_unlock(&inode->i_lock);
	वापस mirror;
पूर्ण

अटल व्योम
ff_layout_हटाओ_mirror(काष्ठा nfs4_ff_layout_mirror *mirror)
अणु
	काष्ठा inode *inode;
	अगर (mirror->layout == शून्य)
		वापस;
	inode = mirror->layout->plh_inode;
	spin_lock(&inode->i_lock);
	list_del(&mirror->mirrors);
	spin_unlock(&inode->i_lock);
	mirror->layout = शून्य;
पूर्ण

अटल काष्ठा nfs4_ff_layout_mirror *ff_layout_alloc_mirror(gfp_t gfp_flags)
अणु
	काष्ठा nfs4_ff_layout_mirror *mirror;

	mirror = kzalloc(माप(*mirror), gfp_flags);
	अगर (mirror != शून्य) अणु
		spin_lock_init(&mirror->lock);
		refcount_set(&mirror->ref, 1);
		INIT_LIST_HEAD(&mirror->mirrors);
	पूर्ण
	वापस mirror;
पूर्ण

अटल व्योम ff_layout_मुक्त_mirror(काष्ठा nfs4_ff_layout_mirror *mirror)
अणु
	स्थिर काष्ठा cred	*cred;

	ff_layout_हटाओ_mirror(mirror);
	kमुक्त(mirror->fh_versions);
	cred = rcu_access_poपूर्णांकer(mirror->ro_cred);
	put_cred(cred);
	cred = rcu_access_poपूर्णांकer(mirror->rw_cred);
	put_cred(cred);
	nfs4_ff_layout_put_deviceid(mirror->mirror_ds);
	kमुक्त(mirror);
पूर्ण

अटल व्योम ff_layout_put_mirror(काष्ठा nfs4_ff_layout_mirror *mirror)
अणु
	अगर (mirror != शून्य && refcount_dec_and_test(&mirror->ref))
		ff_layout_मुक्त_mirror(mirror);
पूर्ण

अटल व्योम ff_layout_मुक्त_mirror_array(काष्ठा nfs4_ff_layout_segment *fls)
अणु
	u32 i;

	क्रम (i = 0; i < fls->mirror_array_cnt; i++)
		ff_layout_put_mirror(fls->mirror_array[i]);
पूर्ण

अटल व्योम _ff_layout_मुक्त_lseg(काष्ठा nfs4_ff_layout_segment *fls)
अणु
	अगर (fls) अणु
		ff_layout_मुक्त_mirror_array(fls);
		kमुक्त(fls);
	पूर्ण
पूर्ण

अटल bool
ff_lseg_match_mirrors(काष्ठा pnfs_layout_segment *l1,
		काष्ठा pnfs_layout_segment *l2)
अणु
	स्थिर काष्ठा nfs4_ff_layout_segment *fl1 = FF_LAYOUT_LSEG(l1);
	स्थिर काष्ठा nfs4_ff_layout_segment *fl2 = FF_LAYOUT_LSEG(l1);
	u32 i;

	अगर (fl1->mirror_array_cnt != fl2->mirror_array_cnt)
		वापस false;
	क्रम (i = 0; i < fl1->mirror_array_cnt; i++) अणु
		अगर (fl1->mirror_array[i] != fl2->mirror_array[i])
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool
ff_lseg_range_is_after(स्थिर काष्ठा pnfs_layout_range *l1,
		स्थिर काष्ठा pnfs_layout_range *l2)
अणु
	u64 end1, end2;

	अगर (l1->iomode != l2->iomode)
		वापस l1->iomode != IOMODE_READ;
	end1 = pnfs_calc_offset_end(l1->offset, l1->length);
	end2 = pnfs_calc_offset_end(l2->offset, l2->length);
	अगर (end1 < l2->offset)
		वापस false;
	अगर (end2 < l1->offset)
		वापस true;
	वापस l2->offset <= l1->offset;
पूर्ण

अटल bool
ff_lseg_merge(काष्ठा pnfs_layout_segment *new,
		काष्ठा pnfs_layout_segment *old)
अणु
	u64 new_end, old_end;

	अगर (test_bit(NFS_LSEG_LAYOUTRETURN, &old->pls_flags))
		वापस false;
	अगर (new->pls_range.iomode != old->pls_range.iomode)
		वापस false;
	old_end = pnfs_calc_offset_end(old->pls_range.offset,
			old->pls_range.length);
	अगर (old_end < new->pls_range.offset)
		वापस false;
	new_end = pnfs_calc_offset_end(new->pls_range.offset,
			new->pls_range.length);
	अगर (new_end < old->pls_range.offset)
		वापस false;
	अगर (!ff_lseg_match_mirrors(new, old))
		वापस false;

	/* Mergeable: copy info from 'old' to 'new' */
	अगर (new_end < old_end)
		new_end = old_end;
	अगर (new->pls_range.offset < old->pls_range.offset)
		new->pls_range.offset = old->pls_range.offset;
	new->pls_range.length = pnfs_calc_offset_length(new->pls_range.offset,
			new_end);
	अगर (test_bit(NFS_LSEG_ROC, &old->pls_flags))
		set_bit(NFS_LSEG_ROC, &new->pls_flags);
	वापस true;
पूर्ण

अटल व्योम
ff_layout_add_lseg(काष्ठा pnfs_layout_hdr *lo,
		काष्ठा pnfs_layout_segment *lseg,
		काष्ठा list_head *मुक्त_me)
अणु
	pnfs_generic_layout_insert_lseg(lo, lseg,
			ff_lseg_range_is_after,
			ff_lseg_merge,
			मुक्त_me);
पूर्ण

अटल व्योम ff_layout_sort_mirrors(काष्ठा nfs4_ff_layout_segment *fls)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < fls->mirror_array_cnt - 1; i++) अणु
		क्रम (j = i + 1; j < fls->mirror_array_cnt; j++)
			अगर (fls->mirror_array[i]->efficiency <
			    fls->mirror_array[j]->efficiency)
				swap(fls->mirror_array[i],
				     fls->mirror_array[j]);
	पूर्ण
पूर्ण

अटल काष्ठा pnfs_layout_segment *
ff_layout_alloc_lseg(काष्ठा pnfs_layout_hdr *lh,
		     काष्ठा nfs4_layoutget_res *lgr,
		     gfp_t gfp_flags)
अणु
	काष्ठा pnfs_layout_segment *ret;
	काष्ठा nfs4_ff_layout_segment *fls = शून्य;
	काष्ठा xdr_stream stream;
	काष्ठा xdr_buf buf;
	काष्ठा page *scratch;
	u64 stripe_unit;
	u32 mirror_array_cnt;
	__be32 *p;
	पूर्णांक i, rc;

	dprपूर्णांकk("--> %s\n", __func__);
	scratch = alloc_page(gfp_flags);
	अगर (!scratch)
		वापस ERR_PTR(-ENOMEM);

	xdr_init_decode_pages(&stream, &buf, lgr->layoutp->pages,
			      lgr->layoutp->len);
	xdr_set_scratch_page(&stream, scratch);

	/* stripe unit and mirror_array_cnt */
	rc = -EIO;
	p = xdr_अंतरभूत_decode(&stream, 8 + 4);
	अगर (!p)
		जाओ out_err_मुक्त;

	p = xdr_decode_hyper(p, &stripe_unit);
	mirror_array_cnt = be32_to_cpup(p++);
	dprपूर्णांकk("%s: stripe_unit=%llu mirror_array_cnt=%u\n", __func__,
		stripe_unit, mirror_array_cnt);

	अगर (mirror_array_cnt > NFS4_FLEXखाता_LAYOUT_MAX_MIRROR_CNT ||
	    mirror_array_cnt == 0)
		जाओ out_err_मुक्त;

	rc = -ENOMEM;
	fls = kzalloc(काष्ठा_size(fls, mirror_array, mirror_array_cnt),
			gfp_flags);
	अगर (!fls)
		जाओ out_err_मुक्त;

	fls->mirror_array_cnt = mirror_array_cnt;
	fls->stripe_unit = stripe_unit;

	क्रम (i = 0; i < fls->mirror_array_cnt; i++) अणु
		काष्ठा nfs4_ff_layout_mirror *mirror;
		काष्ठा cred *kcred;
		स्थिर काष्ठा cred __rcu *cred;
		kuid_t uid;
		kgid_t gid;
		u32 ds_count, fh_count, id;
		पूर्णांक j;

		rc = -EIO;
		p = xdr_अंतरभूत_decode(&stream, 4);
		अगर (!p)
			जाओ out_err_मुक्त;
		ds_count = be32_to_cpup(p);

		/* FIXME: allow क्रम striping? */
		अगर (ds_count != 1)
			जाओ out_err_मुक्त;

		fls->mirror_array[i] = ff_layout_alloc_mirror(gfp_flags);
		अगर (fls->mirror_array[i] == शून्य) अणु
			rc = -ENOMEM;
			जाओ out_err_मुक्त;
		पूर्ण

		fls->mirror_array[i]->ds_count = ds_count;

		/* deviceid */
		rc = decode_deviceid(&stream, &fls->mirror_array[i]->devid);
		अगर (rc)
			जाओ out_err_मुक्त;

		/* efficiency */
		rc = -EIO;
		p = xdr_अंतरभूत_decode(&stream, 4);
		अगर (!p)
			जाओ out_err_मुक्त;
		fls->mirror_array[i]->efficiency = be32_to_cpup(p);

		/* stateid */
		rc = decode_pnfs_stateid(&stream, &fls->mirror_array[i]->stateid);
		अगर (rc)
			जाओ out_err_मुक्त;

		/* fh */
		rc = -EIO;
		p = xdr_अंतरभूत_decode(&stream, 4);
		अगर (!p)
			जाओ out_err_मुक्त;
		fh_count = be32_to_cpup(p);

		fls->mirror_array[i]->fh_versions =
			kसुस्मृति(fh_count, माप(काष्ठा nfs_fh),
				gfp_flags);
		अगर (fls->mirror_array[i]->fh_versions == शून्य) अणु
			rc = -ENOMEM;
			जाओ out_err_मुक्त;
		पूर्ण

		क्रम (j = 0; j < fh_count; j++) अणु
			rc = decode_nfs_fh(&stream,
					   &fls->mirror_array[i]->fh_versions[j]);
			अगर (rc)
				जाओ out_err_मुक्त;
		पूर्ण

		fls->mirror_array[i]->fh_versions_cnt = fh_count;

		/* user */
		rc = decode_name(&stream, &id);
		अगर (rc)
			जाओ out_err_मुक्त;

		uid = make_kuid(&init_user_ns, id);

		/* group */
		rc = decode_name(&stream, &id);
		अगर (rc)
			जाओ out_err_मुक्त;

		gid = make_kgid(&init_user_ns, id);

		अगर (gfp_flags & __GFP_FS)
			kcred = prepare_kernel_cred(शून्य);
		अन्यथा अणु
			अचिन्हित पूर्णांक nofs_flags = meदो_स्मृति_nofs_save();
			kcred = prepare_kernel_cred(शून्य);
			meदो_स्मृति_nofs_restore(nofs_flags);
		पूर्ण
		rc = -ENOMEM;
		अगर (!kcred)
			जाओ out_err_मुक्त;
		kcred->fsuid = uid;
		kcred->fsgid = gid;
		cred = RCU_INITIALIZER(kcred);

		अगर (lgr->range.iomode == IOMODE_READ)
			rcu_assign_poपूर्णांकer(fls->mirror_array[i]->ro_cred, cred);
		अन्यथा
			rcu_assign_poपूर्णांकer(fls->mirror_array[i]->rw_cred, cred);

		mirror = ff_layout_add_mirror(lh, fls->mirror_array[i]);
		अगर (mirror != fls->mirror_array[i]) अणु
			/* swap cred ptrs so मुक्त_mirror will clean up old */
			अगर (lgr->range.iomode == IOMODE_READ) अणु
				cred = xchg(&mirror->ro_cred, cred);
				rcu_assign_poपूर्णांकer(fls->mirror_array[i]->ro_cred, cred);
			पूर्ण अन्यथा अणु
				cred = xchg(&mirror->rw_cred, cred);
				rcu_assign_poपूर्णांकer(fls->mirror_array[i]->rw_cred, cred);
			पूर्ण
			ff_layout_मुक्त_mirror(fls->mirror_array[i]);
			fls->mirror_array[i] = mirror;
		पूर्ण

		dprपूर्णांकk("%s: iomode %s uid %u gid %u\n", __func__,
			lgr->range.iomode == IOMODE_READ ? "READ" : "RW",
			from_kuid(&init_user_ns, uid),
			from_kgid(&init_user_ns, gid));
	पूर्ण

	p = xdr_अंतरभूत_decode(&stream, 4);
	अगर (!p)
		जाओ out_sort_mirrors;
	fls->flags = be32_to_cpup(p);

	p = xdr_अंतरभूत_decode(&stream, 4);
	अगर (!p)
		जाओ out_sort_mirrors;
	क्रम (i=0; i < fls->mirror_array_cnt; i++)
		fls->mirror_array[i]->report_पूर्णांकerval = be32_to_cpup(p);

out_sort_mirrors:
	ff_layout_sort_mirrors(fls);
	ret = &fls->generic_hdr;
	dprपूर्णांकk("<-- %s (success)\n", __func__);
out_मुक्त_page:
	__मुक्त_page(scratch);
	वापस ret;
out_err_मुक्त:
	_ff_layout_मुक्त_lseg(fls);
	ret = ERR_PTR(rc);
	dprपूर्णांकk("<-- %s (%d)\n", __func__, rc);
	जाओ out_मुक्त_page;
पूर्ण

अटल व्योम
ff_layout_मुक्त_lseg(काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा nfs4_ff_layout_segment *fls = FF_LAYOUT_LSEG(lseg);

	dprपूर्णांकk("--> %s\n", __func__);

	अगर (lseg->pls_range.iomode == IOMODE_RW) अणु
		काष्ठा nfs4_flexfile_layout *ffl;
		काष्ठा inode *inode;

		ffl = FF_LAYOUT_FROM_HDR(lseg->pls_layout);
		inode = ffl->generic_hdr.plh_inode;
		spin_lock(&inode->i_lock);
		pnfs_generic_ds_cinfo_release_lseg(&ffl->commit_info, lseg);
		spin_unlock(&inode->i_lock);
	पूर्ण
	_ff_layout_मुक्त_lseg(fls);
पूर्ण

अटल व्योम
nfs4_ff_start_busy_समयr(काष्ठा nfs4_ff_busy_समयr *समयr, kसमय_प्रकार now)
अणु
	/* first IO request? */
	अगर (atomic_inc_वापस(&समयr->n_ops) == 1) अणु
		समयr->start_समय = now;
	पूर्ण
पूर्ण

अटल kसमय_प्रकार
nfs4_ff_end_busy_समयr(काष्ठा nfs4_ff_busy_समयr *समयr, kसमय_प्रकार now)
अणु
	kसमय_प्रकार start;

	अगर (atomic_dec_वापस(&समयr->n_ops) < 0)
		WARN_ON_ONCE(1);

	start = समयr->start_समय;
	समयr->start_समय = now;
	वापस kसमय_sub(now, start);
पूर्ण

अटल bool
nfs4_ff_layoutstat_start_io(काष्ठा nfs4_ff_layout_mirror *mirror,
			    काष्ठा nfs4_ff_layoutstat *layoutstat,
			    kसमय_प्रकार now)
अणु
	s64 report_पूर्णांकerval = FF_LAYOUTSTATS_REPORT_INTERVAL;
	काष्ठा nfs4_flexfile_layout *ffl = FF_LAYOUT_FROM_HDR(mirror->layout);

	nfs4_ff_start_busy_समयr(&layoutstat->busy_समयr, now);
	अगर (!mirror->start_समय)
		mirror->start_समय = now;
	अगर (mirror->report_पूर्णांकerval != 0)
		report_पूर्णांकerval = (s64)mirror->report_पूर्णांकerval * 1000LL;
	अन्यथा अगर (layoutstats_समयr != 0)
		report_पूर्णांकerval = (s64)layoutstats_समयr * 1000LL;
	अगर (kसमय_प्रकारo_ms(kसमय_sub(now, ffl->last_report_समय)) >=
			report_पूर्णांकerval) अणु
		ffl->last_report_समय = now;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम
nfs4_ff_layout_stat_io_update_requested(काष्ठा nfs4_ff_layoutstat *layoutstat,
		__u64 requested)
अणु
	काष्ठा nfs4_ff_io_stat *iostat = &layoutstat->io_stat;

	iostat->ops_requested++;
	iostat->bytes_requested += requested;
पूर्ण

अटल व्योम
nfs4_ff_layout_stat_io_update_completed(काष्ठा nfs4_ff_layoutstat *layoutstat,
		__u64 requested,
		__u64 completed,
		kसमय_प्रकार समय_completed,
		kसमय_प्रकार समय_started)
अणु
	काष्ठा nfs4_ff_io_stat *iostat = &layoutstat->io_stat;
	kसमय_प्रकार completion_समय = kसमय_sub(समय_completed, समय_started);
	kसमय_प्रकार समयr;

	iostat->ops_completed++;
	iostat->bytes_completed += completed;
	iostat->bytes_not_delivered += requested - completed;

	समयr = nfs4_ff_end_busy_समयr(&layoutstat->busy_समयr, समय_completed);
	iostat->total_busy_समय =
			kसमय_add(iostat->total_busy_समय, समयr);
	iostat->aggregate_completion_समय =
			kसमय_add(iostat->aggregate_completion_समय,
					completion_समय);
पूर्ण

अटल व्योम
nfs4_ff_layout_stat_io_start_पढ़ो(काष्ठा inode *inode,
		काष्ठा nfs4_ff_layout_mirror *mirror,
		__u64 requested, kसमय_प्रकार now)
अणु
	bool report;

	spin_lock(&mirror->lock);
	report = nfs4_ff_layoutstat_start_io(mirror, &mirror->पढ़ो_stat, now);
	nfs4_ff_layout_stat_io_update_requested(&mirror->पढ़ो_stat, requested);
	set_bit(NFS4_FF_MIRROR_STAT_AVAIL, &mirror->flags);
	spin_unlock(&mirror->lock);

	अगर (report)
		pnfs_report_layoutstat(inode, GFP_KERNEL);
पूर्ण

अटल व्योम
nfs4_ff_layout_stat_io_end_पढ़ो(काष्ठा rpc_task *task,
		काष्ठा nfs4_ff_layout_mirror *mirror,
		__u64 requested,
		__u64 completed)
अणु
	spin_lock(&mirror->lock);
	nfs4_ff_layout_stat_io_update_completed(&mirror->पढ़ो_stat,
			requested, completed,
			kसमय_get(), task->tk_start);
	set_bit(NFS4_FF_MIRROR_STAT_AVAIL, &mirror->flags);
	spin_unlock(&mirror->lock);
पूर्ण

अटल व्योम
nfs4_ff_layout_stat_io_start_ग_लिखो(काष्ठा inode *inode,
		काष्ठा nfs4_ff_layout_mirror *mirror,
		__u64 requested, kसमय_प्रकार now)
अणु
	bool report;

	spin_lock(&mirror->lock);
	report = nfs4_ff_layoutstat_start_io(mirror , &mirror->ग_लिखो_stat, now);
	nfs4_ff_layout_stat_io_update_requested(&mirror->ग_लिखो_stat, requested);
	set_bit(NFS4_FF_MIRROR_STAT_AVAIL, &mirror->flags);
	spin_unlock(&mirror->lock);

	अगर (report)
		pnfs_report_layoutstat(inode, GFP_NOIO);
पूर्ण

अटल व्योम
nfs4_ff_layout_stat_io_end_ग_लिखो(काष्ठा rpc_task *task,
		काष्ठा nfs4_ff_layout_mirror *mirror,
		__u64 requested,
		__u64 completed,
		क्रमागत nfs3_stable_how committed)
अणु
	अगर (committed == NFS_UNSTABLE)
		requested = completed = 0;

	spin_lock(&mirror->lock);
	nfs4_ff_layout_stat_io_update_completed(&mirror->ग_लिखो_stat,
			requested, completed, kसमय_get(), task->tk_start);
	set_bit(NFS4_FF_MIRROR_STAT_AVAIL, &mirror->flags);
	spin_unlock(&mirror->lock);
पूर्ण

अटल व्योम
ff_layout_mark_ds_unreachable(काष्ठा pnfs_layout_segment *lseg, u32 idx)
अणु
	काष्ठा nfs4_deviceid_node *devid = FF_LAYOUT_DEVID_NODE(lseg, idx);

	अगर (devid)
		nfs4_mark_deviceid_unavailable(devid);
पूर्ण

अटल व्योम
ff_layout_mark_ds_reachable(काष्ठा pnfs_layout_segment *lseg, u32 idx)
अणु
	काष्ठा nfs4_deviceid_node *devid = FF_LAYOUT_DEVID_NODE(lseg, idx);

	अगर (devid)
		nfs4_mark_deviceid_available(devid);
पूर्ण

अटल काष्ठा nfs4_pnfs_ds *
ff_layout_choose_ds_क्रम_पढ़ो(काष्ठा pnfs_layout_segment *lseg,
			     u32 start_idx, u32 *best_idx,
			     bool check_device)
अणु
	काष्ठा nfs4_ff_layout_segment *fls = FF_LAYOUT_LSEG(lseg);
	काष्ठा nfs4_ff_layout_mirror *mirror;
	काष्ठा nfs4_pnfs_ds *ds;
	u32 idx;

	/* mirrors are initially sorted by efficiency */
	क्रम (idx = start_idx; idx < fls->mirror_array_cnt; idx++) अणु
		mirror = FF_LAYOUT_COMP(lseg, idx);
		ds = nfs4_ff_layout_prepare_ds(lseg, mirror, false);
		अगर (!ds)
			जारी;

		अगर (check_device &&
		    nfs4_test_deviceid_unavailable(&mirror->mirror_ds->id_node))
			जारी;

		*best_idx = idx;
		वापस ds;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा nfs4_pnfs_ds *
ff_layout_choose_any_ds_क्रम_पढ़ो(काष्ठा pnfs_layout_segment *lseg,
				 u32 start_idx, u32 *best_idx)
अणु
	वापस ff_layout_choose_ds_क्रम_पढ़ो(lseg, start_idx, best_idx, false);
पूर्ण

अटल काष्ठा nfs4_pnfs_ds *
ff_layout_choose_valid_ds_क्रम_पढ़ो(काष्ठा pnfs_layout_segment *lseg,
				   u32 start_idx, u32 *best_idx)
अणु
	वापस ff_layout_choose_ds_क्रम_पढ़ो(lseg, start_idx, best_idx, true);
पूर्ण

अटल काष्ठा nfs4_pnfs_ds *
ff_layout_choose_best_ds_क्रम_पढ़ो(काष्ठा pnfs_layout_segment *lseg,
				  u32 start_idx, u32 *best_idx)
अणु
	काष्ठा nfs4_pnfs_ds *ds;

	ds = ff_layout_choose_valid_ds_क्रम_पढ़ो(lseg, start_idx, best_idx);
	अगर (ds)
		वापस ds;
	वापस ff_layout_choose_any_ds_क्रम_पढ़ो(lseg, start_idx, best_idx);
पूर्ण

अटल काष्ठा nfs4_pnfs_ds *
ff_layout_get_ds_क्रम_पढ़ो(काष्ठा nfs_pageio_descriptor *pgio,
			  u32 *best_idx)
अणु
	काष्ठा pnfs_layout_segment *lseg = pgio->pg_lseg;
	काष्ठा nfs4_pnfs_ds *ds;

	ds = ff_layout_choose_best_ds_क्रम_पढ़ो(lseg, pgio->pg_mirror_idx,
					       best_idx);
	अगर (ds || !pgio->pg_mirror_idx)
		वापस ds;
	वापस ff_layout_choose_best_ds_क्रम_पढ़ो(lseg, 0, best_idx);
पूर्ण

अटल व्योम
ff_layout_pg_get_पढ़ो(काष्ठा nfs_pageio_descriptor *pgio,
		      काष्ठा nfs_page *req,
		      bool strict_iomode)
अणु
	pnfs_put_lseg(pgio->pg_lseg);
	pgio->pg_lseg = pnfs_update_layout(pgio->pg_inode,
					   nfs_req_खोलोctx(req),
					   req_offset(req),
					   req->wb_bytes,
					   IOMODE_READ,
					   strict_iomode,
					   GFP_KERNEL);
	अगर (IS_ERR(pgio->pg_lseg)) अणु
		pgio->pg_error = PTR_ERR(pgio->pg_lseg);
		pgio->pg_lseg = शून्य;
	पूर्ण
पूर्ण

अटल व्योम
ff_layout_pg_check_layout(काष्ठा nfs_pageio_descriptor *pgio,
			  काष्ठा nfs_page *req)
अणु
	pnfs_generic_pg_check_layout(pgio);
	pnfs_generic_pg_check_range(pgio, req);
पूर्ण

अटल व्योम
ff_layout_pg_init_पढ़ो(काष्ठा nfs_pageio_descriptor *pgio,
			काष्ठा nfs_page *req)
अणु
	काष्ठा nfs_pgio_mirror *pgm;
	काष्ठा nfs4_ff_layout_mirror *mirror;
	काष्ठा nfs4_pnfs_ds *ds;
	u32 ds_idx;

retry:
	ff_layout_pg_check_layout(pgio, req);
	/* Use full layout क्रम now */
	अगर (!pgio->pg_lseg) अणु
		ff_layout_pg_get_पढ़ो(pgio, req, false);
		अगर (!pgio->pg_lseg)
			जाओ out_nolseg;
	पूर्ण
	अगर (ff_layout_aव्योम_पढ़ो_on_rw(pgio->pg_lseg)) अणु
		ff_layout_pg_get_पढ़ो(pgio, req, true);
		अगर (!pgio->pg_lseg)
			जाओ out_nolseg;
	पूर्ण

	ds = ff_layout_get_ds_क्रम_पढ़ो(pgio, &ds_idx);
	अगर (!ds) अणु
		अगर (!ff_layout_no_fallback_to_mds(pgio->pg_lseg))
			जाओ out_mds;
		pnfs_generic_pg_cleanup(pgio);
		/* Sleep क्रम 1 second beक्रमe retrying */
		ssleep(1);
		जाओ retry;
	पूर्ण

	mirror = FF_LAYOUT_COMP(pgio->pg_lseg, ds_idx);
	pgm = &pgio->pg_mirrors[0];
	pgm->pg_bsize = mirror->mirror_ds->ds_versions[0].rsize;

	pgio->pg_mirror_idx = ds_idx;

	अगर (NFS_SERVER(pgio->pg_inode)->flags &
			(NFS_MOUNT_SOFT|NFS_MOUNT_SOFTERR))
		pgio->pg_maxretrans = io_maxretrans;
	वापस;
out_nolseg:
	अगर (pgio->pg_error < 0)
		वापस;
out_mds:
	trace_pnfs_mds_fallback_pg_init_पढ़ो(pgio->pg_inode,
			0, NFS4_MAX_UINT64, IOMODE_READ,
			NFS_I(pgio->pg_inode)->layout,
			pgio->pg_lseg);
	pgio->pg_maxretrans = 0;
	nfs_pageio_reset_पढ़ो_mds(pgio);
पूर्ण

अटल व्योम
ff_layout_pg_init_ग_लिखो(काष्ठा nfs_pageio_descriptor *pgio,
			काष्ठा nfs_page *req)
अणु
	काष्ठा nfs4_ff_layout_mirror *mirror;
	काष्ठा nfs_pgio_mirror *pgm;
	काष्ठा nfs4_pnfs_ds *ds;
	u32 i;

retry:
	ff_layout_pg_check_layout(pgio, req);
	अगर (!pgio->pg_lseg) अणु
		pgio->pg_lseg = pnfs_update_layout(pgio->pg_inode,
						   nfs_req_खोलोctx(req),
						   req_offset(req),
						   req->wb_bytes,
						   IOMODE_RW,
						   false,
						   GFP_NOFS);
		अगर (IS_ERR(pgio->pg_lseg)) अणु
			pgio->pg_error = PTR_ERR(pgio->pg_lseg);
			pgio->pg_lseg = शून्य;
			वापस;
		पूर्ण
	पूर्ण
	/* If no lseg, fall back to ग_लिखो through mds */
	अगर (pgio->pg_lseg == शून्य)
		जाओ out_mds;

	/* Use a direct mapping of ds_idx to pgio mirror_idx */
	अगर (pgio->pg_mirror_count != FF_LAYOUT_MIRROR_COUNT(pgio->pg_lseg))
		जाओ out_eagain;

	क्रम (i = 0; i < pgio->pg_mirror_count; i++) अणु
		mirror = FF_LAYOUT_COMP(pgio->pg_lseg, i);
		ds = nfs4_ff_layout_prepare_ds(pgio->pg_lseg, mirror, true);
		अगर (!ds) अणु
			अगर (!ff_layout_no_fallback_to_mds(pgio->pg_lseg))
				जाओ out_mds;
			pnfs_generic_pg_cleanup(pgio);
			/* Sleep क्रम 1 second beक्रमe retrying */
			ssleep(1);
			जाओ retry;
		पूर्ण
		pgm = &pgio->pg_mirrors[i];
		pgm->pg_bsize = mirror->mirror_ds->ds_versions[0].wsize;
	पूर्ण

	अगर (NFS_SERVER(pgio->pg_inode)->flags &
			(NFS_MOUNT_SOFT|NFS_MOUNT_SOFTERR))
		pgio->pg_maxretrans = io_maxretrans;
	वापस;
out_eagain:
	pnfs_generic_pg_cleanup(pgio);
	pgio->pg_error = -EAGAIN;
	वापस;
out_mds:
	trace_pnfs_mds_fallback_pg_init_ग_लिखो(pgio->pg_inode,
			0, NFS4_MAX_UINT64, IOMODE_RW,
			NFS_I(pgio->pg_inode)->layout,
			pgio->pg_lseg);
	pgio->pg_maxretrans = 0;
	nfs_pageio_reset_ग_लिखो_mds(pgio);
	pgio->pg_error = -EAGAIN;
पूर्ण

अटल अचिन्हित पूर्णांक
ff_layout_pg_get_mirror_count_ग_लिखो(काष्ठा nfs_pageio_descriptor *pgio,
				    काष्ठा nfs_page *req)
अणु
	अगर (!pgio->pg_lseg) अणु
		pgio->pg_lseg = pnfs_update_layout(pgio->pg_inode,
						   nfs_req_खोलोctx(req),
						   req_offset(req),
						   req->wb_bytes,
						   IOMODE_RW,
						   false,
						   GFP_NOFS);
		अगर (IS_ERR(pgio->pg_lseg)) अणु
			pgio->pg_error = PTR_ERR(pgio->pg_lseg);
			pgio->pg_lseg = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (pgio->pg_lseg)
		वापस FF_LAYOUT_MIRROR_COUNT(pgio->pg_lseg);

	trace_pnfs_mds_fallback_pg_get_mirror_count(pgio->pg_inode,
			0, NFS4_MAX_UINT64, IOMODE_RW,
			NFS_I(pgio->pg_inode)->layout,
			pgio->pg_lseg);
	/* no lseg means that pnfs is not in use, so no mirroring here */
	nfs_pageio_reset_ग_लिखो_mds(pgio);
out:
	वापस 1;
पूर्ण

अटल u32
ff_layout_pg_set_mirror_ग_लिखो(काष्ठा nfs_pageio_descriptor *desc, u32 idx)
अणु
	u32 old = desc->pg_mirror_idx;

	desc->pg_mirror_idx = idx;
	वापस old;
पूर्ण

अटल काष्ठा nfs_pgio_mirror *
ff_layout_pg_get_mirror_ग_लिखो(काष्ठा nfs_pageio_descriptor *desc, u32 idx)
अणु
	वापस &desc->pg_mirrors[idx];
पूर्ण

अटल स्थिर काष्ठा nfs_pageio_ops ff_layout_pg_पढ़ो_ops = अणु
	.pg_init = ff_layout_pg_init_पढ़ो,
	.pg_test = pnfs_generic_pg_test,
	.pg_करोio = pnfs_generic_pg_पढ़ोpages,
	.pg_cleanup = pnfs_generic_pg_cleanup,
पूर्ण;

अटल स्थिर काष्ठा nfs_pageio_ops ff_layout_pg_ग_लिखो_ops = अणु
	.pg_init = ff_layout_pg_init_ग_लिखो,
	.pg_test = pnfs_generic_pg_test,
	.pg_करोio = pnfs_generic_pg_ग_लिखोpages,
	.pg_get_mirror_count = ff_layout_pg_get_mirror_count_ग_लिखो,
	.pg_cleanup = pnfs_generic_pg_cleanup,
	.pg_get_mirror = ff_layout_pg_get_mirror_ग_लिखो,
	.pg_set_mirror = ff_layout_pg_set_mirror_ग_लिखो,
पूर्ण;

अटल व्योम ff_layout_reset_ग_लिखो(काष्ठा nfs_pgio_header *hdr, bool retry_pnfs)
अणु
	काष्ठा rpc_task *task = &hdr->task;

	pnfs_layoutcommit_inode(hdr->inode, false);

	अगर (retry_pnfs) अणु
		dprपूर्णांकk("%s Reset task %5u for i/o through pNFS "
			"(req %s/%llu, %u bytes @ offset %llu)\n", __func__,
			hdr->task.tk_pid,
			hdr->inode->i_sb->s_id,
			(अचिन्हित दीर्घ दीर्घ)NFS_खाताID(hdr->inode),
			hdr->args.count,
			(अचिन्हित दीर्घ दीर्घ)hdr->args.offset);

		hdr->completion_ops->reschedule_io(hdr);
		वापस;
	पूर्ण

	अगर (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags)) अणु
		dprपूर्णांकk("%s Reset task %5u for i/o through MDS "
			"(req %s/%llu, %u bytes @ offset %llu)\n", __func__,
			hdr->task.tk_pid,
			hdr->inode->i_sb->s_id,
			(अचिन्हित दीर्घ दीर्घ)NFS_खाताID(hdr->inode),
			hdr->args.count,
			(अचिन्हित दीर्घ दीर्घ)hdr->args.offset);

		trace_pnfs_mds_fallback_ग_लिखो_करोne(hdr->inode,
				hdr->args.offset, hdr->args.count,
				IOMODE_RW, NFS_I(hdr->inode)->layout,
				hdr->lseg);
		task->tk_status = pnfs_ग_लिखो_करोne_resend_to_mds(hdr);
	पूर्ण
पूर्ण

अटल व्योम ff_layout_resend_pnfs_पढ़ो(काष्ठा nfs_pgio_header *hdr)
अणु
	u32 idx = hdr->pgio_mirror_idx + 1;
	u32 new_idx = 0;

	अगर (ff_layout_choose_any_ds_क्रम_पढ़ो(hdr->lseg, idx, &new_idx))
		ff_layout_send_layouterror(hdr->lseg);
	अन्यथा
		pnfs_error_mark_layout_क्रम_वापस(hdr->inode, hdr->lseg);
	pnfs_पढ़ो_resend_pnfs(hdr, new_idx);
पूर्ण

अटल व्योम ff_layout_reset_पढ़ो(काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा rpc_task *task = &hdr->task;

	pnfs_layoutcommit_inode(hdr->inode, false);
	pnfs_error_mark_layout_क्रम_वापस(hdr->inode, hdr->lseg);

	अगर (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags)) अणु
		dprपूर्णांकk("%s Reset task %5u for i/o through MDS "
			"(req %s/%llu, %u bytes @ offset %llu)\n", __func__,
			hdr->task.tk_pid,
			hdr->inode->i_sb->s_id,
			(अचिन्हित दीर्घ दीर्घ)NFS_खाताID(hdr->inode),
			hdr->args.count,
			(अचिन्हित दीर्घ दीर्घ)hdr->args.offset);

		trace_pnfs_mds_fallback_पढ़ो_करोne(hdr->inode,
				hdr->args.offset, hdr->args.count,
				IOMODE_READ, NFS_I(hdr->inode)->layout,
				hdr->lseg);
		task->tk_status = pnfs_पढ़ो_करोne_resend_to_mds(hdr);
	पूर्ण
पूर्ण

अटल पूर्णांक ff_layout_async_handle_error_v4(काष्ठा rpc_task *task,
					   काष्ठा nfs4_state *state,
					   काष्ठा nfs_client *clp,
					   काष्ठा pnfs_layout_segment *lseg,
					   u32 idx)
अणु
	काष्ठा pnfs_layout_hdr *lo = lseg->pls_layout;
	काष्ठा inode *inode = lo->plh_inode;
	काष्ठा nfs4_deviceid_node *devid = FF_LAYOUT_DEVID_NODE(lseg, idx);
	काष्ठा nfs4_slot_table *tbl = &clp->cl_session->fc_slot_table;

	चयन (task->tk_status) अणु
	हाल -NFS4ERR_BADSESSION:
	हाल -NFS4ERR_BADSLOT:
	हाल -NFS4ERR_BAD_HIGH_SLOT:
	हाल -NFS4ERR_DEADSESSION:
	हाल -NFS4ERR_CONN_NOT_BOUND_TO_SESSION:
	हाल -NFS4ERR_SEQ_FALSE_RETRY:
	हाल -NFS4ERR_SEQ_MISORDERED:
		dprपूर्णांकk("%s ERROR %d, Reset session. Exchangeid "
			"flags 0x%x\n", __func__, task->tk_status,
			clp->cl_exchange_flags);
		nfs4_schedule_session_recovery(clp->cl_session, task->tk_status);
		अवरोध;
	हाल -NFS4ERR_DELAY:
	हाल -NFS4ERR_GRACE:
		rpc_delay(task, FF_LAYOUT_POLL_RETRY_MAX);
		अवरोध;
	हाल -NFS4ERR_RETRY_UNCACHED_REP:
		अवरोध;
	/* Invalidate Layout errors */
	हाल -NFS4ERR_PNFS_NO_LAYOUT:
	हाल -ESTALE:           /* mapped NFS4ERR_STALE */
	हाल -EBADHANDLE:       /* mapped NFS4ERR_BADHANDLE */
	हाल -EISसूची:           /* mapped NFS4ERR_ISसूची */
	हाल -NFS4ERR_FHEXPIRED:
	हाल -NFS4ERR_WRONG_TYPE:
		dprपूर्णांकk("%s Invalid layout error %d\n", __func__,
			task->tk_status);
		/*
		 * Destroy layout so new i/o will get a new layout.
		 * Layout will not be destroyed until all current lseg
		 * references are put. Mark layout as invalid to resend failed
		 * i/o and all i/o रुकोing on the slot table to the MDS until
		 * layout is destroyed and a new valid layout is obtained.
		 */
		pnfs_destroy_layout(NFS_I(inode));
		rpc_wake_up(&tbl->slot_tbl_रुकोq);
		जाओ reset;
	/* RPC connection errors */
	हाल -ECONNREFUSED:
	हाल -EHOSTDOWN:
	हाल -EHOSTUNREACH:
	हाल -ENETUNREACH:
	हाल -EIO:
	हाल -ETIMEDOUT:
	हाल -EPIPE:
		dprपूर्णांकk("%s DS connection error %d\n", __func__,
			task->tk_status);
		nfs4_delete_deviceid(devid->ld, devid->nfs_client,
				&devid->deviceid);
		rpc_wake_up(&tbl->slot_tbl_रुकोq);
		fallthrough;
	शेष:
		अगर (ff_layout_aव्योम_mds_available_ds(lseg))
			वापस -NFS4ERR_RESET_TO_PNFS;
reset:
		dprपूर्णांकk("%s Retry through MDS. Error %d\n", __func__,
			task->tk_status);
		वापस -NFS4ERR_RESET_TO_MDS;
	पूर्ण
	task->tk_status = 0;
	वापस -EAGAIN;
पूर्ण

/* Retry all errors through either pNFS or MDS except क्रम -EJUKEBOX */
अटल पूर्णांक ff_layout_async_handle_error_v3(काष्ठा rpc_task *task,
					   काष्ठा pnfs_layout_segment *lseg,
					   u32 idx)
अणु
	काष्ठा nfs4_deviceid_node *devid = FF_LAYOUT_DEVID_NODE(lseg, idx);

	चयन (task->tk_status) अणु
	/* File access problems. Don't mark the device as unavailable */
	हाल -EACCES:
	हाल -ESTALE:
	हाल -EISसूची:
	हाल -EBADHANDLE:
	हाल -ELOOP:
	हाल -ENOSPC:
		अवरोध;
	हाल -EJUKEBOX:
		nfs_inc_stats(lseg->pls_layout->plh_inode, NFSIOS_DELAY);
		जाओ out_retry;
	शेष:
		dprपूर्णांकk("%s DS connection error %d\n", __func__,
			task->tk_status);
		nfs4_delete_deviceid(devid->ld, devid->nfs_client,
				&devid->deviceid);
	पूर्ण
	/* FIXME: Need to prevent infinite looping here. */
	वापस -NFS4ERR_RESET_TO_PNFS;
out_retry:
	task->tk_status = 0;
	rpc_restart_call_prepare(task);
	rpc_delay(task, NFS_JUKEBOX_RETRY_TIME);
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक ff_layout_async_handle_error(काष्ठा rpc_task *task,
					काष्ठा nfs4_state *state,
					काष्ठा nfs_client *clp,
					काष्ठा pnfs_layout_segment *lseg,
					u32 idx)
अणु
	पूर्णांक vers = clp->cl_nfs_mod->rpc_vers->number;

	अगर (task->tk_status >= 0) अणु
		ff_layout_mark_ds_reachable(lseg, idx);
		वापस 0;
	पूर्ण

	/* Handle the हाल of an invalid layout segment */
	अगर (!pnfs_is_valid_lseg(lseg))
		वापस -NFS4ERR_RESET_TO_PNFS;

	चयन (vers) अणु
	हाल 3:
		वापस ff_layout_async_handle_error_v3(task, lseg, idx);
	हाल 4:
		वापस ff_layout_async_handle_error_v4(task, state, clp,
						       lseg, idx);
	शेष:
		/* should never happen */
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम ff_layout_io_track_ds_error(काष्ठा pnfs_layout_segment *lseg,
					u32 idx, u64 offset, u64 length,
					u32 *op_status, पूर्णांक opnum, पूर्णांक error)
अणु
	काष्ठा nfs4_ff_layout_mirror *mirror;
	u32 status = *op_status;
	पूर्णांक err;

	अगर (status == 0) अणु
		चयन (error) अणु
		हाल -ETIMEDOUT:
		हाल -EPFNOSUPPORT:
		हाल -EPROTONOSUPPORT:
		हाल -EOPNOTSUPP:
		हाल -ECONNREFUSED:
		हाल -ECONNRESET:
		हाल -EHOSTDOWN:
		हाल -EHOSTUNREACH:
		हाल -ENETUNREACH:
		हाल -EADDRINUSE:
		हाल -ENOBUFS:
		हाल -EPIPE:
		हाल -EPERM:
			*op_status = status = NFS4ERR_NXIO;
			अवरोध;
		हाल -EACCES:
			*op_status = status = NFS4ERR_ACCESS;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
	पूर्ण

	mirror = FF_LAYOUT_COMP(lseg, idx);
	err = ff_layout_track_ds_error(FF_LAYOUT_FROM_HDR(lseg->pls_layout),
				       mirror, offset, length, status, opnum,
				       GFP_NOIO);

	चयन (status) अणु
	हाल NFS4ERR_DELAY:
	हाल NFS4ERR_GRACE:
		अवरोध;
	हाल NFS4ERR_NXIO:
		ff_layout_mark_ds_unreachable(lseg, idx);
		/*
		 * Don't वापस the layout अगर this is a पढ़ो and we still
		 * have layouts to try
		 */
		अगर (opnum == OP_READ)
			अवरोध;
		fallthrough;
	शेष:
		pnfs_error_mark_layout_क्रम_वापस(lseg->pls_layout->plh_inode,
						  lseg);
	पूर्ण

	dprपूर्णांकk("%s: err %d op %d status %u\n", __func__, err, opnum, status);
पूर्ण

/* NFS_PROTO call करोne callback routines */
अटल पूर्णांक ff_layout_पढ़ो_करोne_cb(काष्ठा rpc_task *task,
				काष्ठा nfs_pgio_header *hdr)
अणु
	पूर्णांक err;

	अगर (task->tk_status < 0) अणु
		ff_layout_io_track_ds_error(hdr->lseg, hdr->pgio_mirror_idx,
					    hdr->args.offset, hdr->args.count,
					    &hdr->res.op_status, OP_READ,
					    task->tk_status);
		trace_ff_layout_पढ़ो_error(hdr);
	पूर्ण

	err = ff_layout_async_handle_error(task, hdr->args.context->state,
					   hdr->ds_clp, hdr->lseg,
					   hdr->pgio_mirror_idx);

	trace_nfs4_pnfs_पढ़ो(hdr, err);
	clear_bit(NFS_IOHDR_RESEND_PNFS, &hdr->flags);
	clear_bit(NFS_IOHDR_RESEND_MDS, &hdr->flags);
	चयन (err) अणु
	हाल -NFS4ERR_RESET_TO_PNFS:
		set_bit(NFS_IOHDR_RESEND_PNFS, &hdr->flags);
		वापस task->tk_status;
	हाल -NFS4ERR_RESET_TO_MDS:
		set_bit(NFS_IOHDR_RESEND_MDS, &hdr->flags);
		वापस task->tk_status;
	हाल -EAGAIN:
		जाओ out_eagain;
	पूर्ण

	वापस 0;
out_eagain:
	rpc_restart_call_prepare(task);
	वापस -EAGAIN;
पूर्ण

अटल bool
ff_layout_need_layoutcommit(काष्ठा pnfs_layout_segment *lseg)
अणु
	वापस !(FF_LAYOUT_LSEG(lseg)->flags & FF_FLAGS_NO_LAYOUTCOMMIT);
पूर्ण

/*
 * We reference the rpc_cred of the first WRITE that triggers the need क्रम
 * a LAYOUTCOMMIT, and use it to send the layoutcommit compound.
 * rfc5661 is not clear about which credential should be used.
 *
 * Flexlayout client should treat DS replied खाता_SYNC as DATA_SYNC, so
 * to follow http://www.rfc-editor.org/errata_search.php?rfc=5661&eid=2751
 * we always send layoutcommit after DS ग_लिखोs.
 */
अटल व्योम
ff_layout_set_layoutcommit(काष्ठा inode *inode,
		काष्ठा pnfs_layout_segment *lseg,
		loff_t end_offset)
अणु
	अगर (!ff_layout_need_layoutcommit(lseg))
		वापस;

	pnfs_set_layoutcommit(inode, lseg, end_offset);
	dprपूर्णांकk("%s inode %lu pls_end_pos %llu\n", __func__, inode->i_ino,
		(अचिन्हित दीर्घ दीर्घ) NFS_I(inode)->layout->plh_lwb);
पूर्ण

अटल व्योम ff_layout_पढ़ो_record_layoutstats_start(काष्ठा rpc_task *task,
		काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (test_and_set_bit(NFS_IOHDR_STAT, &hdr->flags))
		वापस;
	nfs4_ff_layout_stat_io_start_पढ़ो(hdr->inode,
			FF_LAYOUT_COMP(hdr->lseg, hdr->pgio_mirror_idx),
			hdr->args.count,
			task->tk_start);
पूर्ण

अटल व्योम ff_layout_पढ़ो_record_layoutstats_करोne(काष्ठा rpc_task *task,
		काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (!test_and_clear_bit(NFS_IOHDR_STAT, &hdr->flags))
		वापस;
	nfs4_ff_layout_stat_io_end_पढ़ो(task,
			FF_LAYOUT_COMP(hdr->lseg, hdr->pgio_mirror_idx),
			hdr->args.count,
			hdr->res.count);
	set_bit(NFS_LSEG_LAYOUTRETURN, &hdr->lseg->pls_flags);
पूर्ण

अटल पूर्णांक ff_layout_पढ़ो_prepare_common(काष्ठा rpc_task *task,
					 काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (unlikely(test_bit(NFS_CONTEXT_BAD, &hdr->args.context->flags))) अणु
		rpc_निकास(task, -EIO);
		वापस -EIO;
	पूर्ण

	ff_layout_पढ़ो_record_layoutstats_start(task, hdr);
	वापस 0;
पूर्ण

/*
 * Call ops क्रम the async पढ़ो/ग_लिखो हालs
 * In the हाल of dense layouts, the offset needs to be reset to its
 * original value.
 */
अटल व्योम ff_layout_पढ़ो_prepare_v3(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	अगर (ff_layout_पढ़ो_prepare_common(task, hdr))
		वापस;

	rpc_call_start(task);
पूर्ण

अटल व्योम ff_layout_पढ़ो_prepare_v4(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	अगर (nfs4_setup_sequence(hdr->ds_clp,
				&hdr->args.seq_args,
				&hdr->res.seq_res,
				task))
		वापस;

	ff_layout_पढ़ो_prepare_common(task, hdr);
पूर्ण

अटल व्योम ff_layout_पढ़ो_call_करोne(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	dprपूर्णांकk("--> %s task->tk_status %d\n", __func__, task->tk_status);

	अगर (test_bit(NFS_IOHDR_REDO, &hdr->flags) &&
	    task->tk_status == 0) अणु
		nfs4_sequence_करोne(task, &hdr->res.seq_res);
		वापस;
	पूर्ण

	/* Note this may cause RPC to be resent */
	hdr->mds_ops->rpc_call_करोne(task, hdr);
पूर्ण

अटल व्योम ff_layout_पढ़ो_count_stats(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	ff_layout_पढ़ो_record_layoutstats_करोne(task, hdr);
	rpc_count_iostats_metrics(task,
	    &NFS_CLIENT(hdr->inode)->cl_metrics[NFSPROC4_CLNT_READ]);
पूर्ण

अटल व्योम ff_layout_पढ़ो_release(व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	ff_layout_पढ़ो_record_layoutstats_करोne(&hdr->task, hdr);
	अगर (test_bit(NFS_IOHDR_RESEND_PNFS, &hdr->flags))
		ff_layout_resend_pnfs_पढ़ो(hdr);
	अन्यथा अगर (test_bit(NFS_IOHDR_RESEND_MDS, &hdr->flags))
		ff_layout_reset_पढ़ो(hdr);
	pnfs_generic_rw_release(data);
पूर्ण


अटल पूर्णांक ff_layout_ग_लिखो_करोne_cb(काष्ठा rpc_task *task,
				काष्ठा nfs_pgio_header *hdr)
अणु
	loff_t end_offs = 0;
	पूर्णांक err;

	अगर (task->tk_status < 0) अणु
		ff_layout_io_track_ds_error(hdr->lseg, hdr->pgio_mirror_idx,
					    hdr->args.offset, hdr->args.count,
					    &hdr->res.op_status, OP_WRITE,
					    task->tk_status);
		trace_ff_layout_ग_लिखो_error(hdr);
	पूर्ण

	err = ff_layout_async_handle_error(task, hdr->args.context->state,
					   hdr->ds_clp, hdr->lseg,
					   hdr->pgio_mirror_idx);

	trace_nfs4_pnfs_ग_लिखो(hdr, err);
	clear_bit(NFS_IOHDR_RESEND_PNFS, &hdr->flags);
	clear_bit(NFS_IOHDR_RESEND_MDS, &hdr->flags);
	चयन (err) अणु
	हाल -NFS4ERR_RESET_TO_PNFS:
		set_bit(NFS_IOHDR_RESEND_PNFS, &hdr->flags);
		वापस task->tk_status;
	हाल -NFS4ERR_RESET_TO_MDS:
		set_bit(NFS_IOHDR_RESEND_MDS, &hdr->flags);
		वापस task->tk_status;
	हाल -EAGAIN:
		वापस -EAGAIN;
	पूर्ण

	अगर (hdr->res.verf->committed == NFS_खाता_SYNC ||
	    hdr->res.verf->committed == NFS_DATA_SYNC)
		end_offs = hdr->mds_offset + (loff_t)hdr->res.count;

	/* Note: अगर the ग_लिखो is unstable, करोn't set end_offs until commit */
	ff_layout_set_layoutcommit(hdr->inode, hdr->lseg, end_offs);

	/* zero out fattr since we करोn't care DS attr at all */
	hdr->fattr.valid = 0;
	अगर (task->tk_status >= 0)
		nfs_ग_लिखोback_update_inode(hdr);

	वापस 0;
पूर्ण

अटल पूर्णांक ff_layout_commit_करोne_cb(काष्ठा rpc_task *task,
				     काष्ठा nfs_commit_data *data)
अणु
	पूर्णांक err;

	अगर (task->tk_status < 0) अणु
		ff_layout_io_track_ds_error(data->lseg, data->ds_commit_index,
					    data->args.offset, data->args.count,
					    &data->res.op_status, OP_COMMIT,
					    task->tk_status);
		trace_ff_layout_commit_error(data);
	पूर्ण

	err = ff_layout_async_handle_error(task, शून्य, data->ds_clp,
					   data->lseg, data->ds_commit_index);

	trace_nfs4_pnfs_commit_ds(data, err);
	चयन (err) अणु
	हाल -NFS4ERR_RESET_TO_PNFS:
		pnfs_generic_prepare_to_resend_ग_लिखोs(data);
		वापस -EAGAIN;
	हाल -NFS4ERR_RESET_TO_MDS:
		pnfs_generic_prepare_to_resend_ग_लिखोs(data);
		वापस -EAGAIN;
	हाल -EAGAIN:
		rpc_restart_call_prepare(task);
		वापस -EAGAIN;
	पूर्ण

	ff_layout_set_layoutcommit(data->inode, data->lseg, data->lwb);

	वापस 0;
पूर्ण

अटल व्योम ff_layout_ग_लिखो_record_layoutstats_start(काष्ठा rpc_task *task,
		काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (test_and_set_bit(NFS_IOHDR_STAT, &hdr->flags))
		वापस;
	nfs4_ff_layout_stat_io_start_ग_लिखो(hdr->inode,
			FF_LAYOUT_COMP(hdr->lseg, hdr->pgio_mirror_idx),
			hdr->args.count,
			task->tk_start);
पूर्ण

अटल व्योम ff_layout_ग_लिखो_record_layoutstats_करोne(काष्ठा rpc_task *task,
		काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (!test_and_clear_bit(NFS_IOHDR_STAT, &hdr->flags))
		वापस;
	nfs4_ff_layout_stat_io_end_ग_लिखो(task,
			FF_LAYOUT_COMP(hdr->lseg, hdr->pgio_mirror_idx),
			hdr->args.count, hdr->res.count,
			hdr->res.verf->committed);
	set_bit(NFS_LSEG_LAYOUTRETURN, &hdr->lseg->pls_flags);
पूर्ण

अटल पूर्णांक ff_layout_ग_लिखो_prepare_common(काष्ठा rpc_task *task,
					  काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (unlikely(test_bit(NFS_CONTEXT_BAD, &hdr->args.context->flags))) अणु
		rpc_निकास(task, -EIO);
		वापस -EIO;
	पूर्ण

	ff_layout_ग_लिखो_record_layoutstats_start(task, hdr);
	वापस 0;
पूर्ण

अटल व्योम ff_layout_ग_लिखो_prepare_v3(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	अगर (ff_layout_ग_लिखो_prepare_common(task, hdr))
		वापस;

	rpc_call_start(task);
पूर्ण

अटल व्योम ff_layout_ग_लिखो_prepare_v4(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	अगर (nfs4_setup_sequence(hdr->ds_clp,
				&hdr->args.seq_args,
				&hdr->res.seq_res,
				task))
		वापस;

	ff_layout_ग_लिखो_prepare_common(task, hdr);
पूर्ण

अटल व्योम ff_layout_ग_लिखो_call_करोne(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	अगर (test_bit(NFS_IOHDR_REDO, &hdr->flags) &&
	    task->tk_status == 0) अणु
		nfs4_sequence_करोne(task, &hdr->res.seq_res);
		वापस;
	पूर्ण

	/* Note this may cause RPC to be resent */
	hdr->mds_ops->rpc_call_करोne(task, hdr);
पूर्ण

अटल व्योम ff_layout_ग_लिखो_count_stats(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	ff_layout_ग_लिखो_record_layoutstats_करोne(task, hdr);
	rpc_count_iostats_metrics(task,
	    &NFS_CLIENT(hdr->inode)->cl_metrics[NFSPROC4_CLNT_WRITE]);
पूर्ण

अटल व्योम ff_layout_ग_लिखो_release(व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	ff_layout_ग_लिखो_record_layoutstats_करोne(&hdr->task, hdr);
	अगर (test_bit(NFS_IOHDR_RESEND_PNFS, &hdr->flags)) अणु
		ff_layout_send_layouterror(hdr->lseg);
		ff_layout_reset_ग_लिखो(hdr, true);
	पूर्ण अन्यथा अगर (test_bit(NFS_IOHDR_RESEND_MDS, &hdr->flags))
		ff_layout_reset_ग_लिखो(hdr, false);
	pnfs_generic_rw_release(data);
पूर्ण

अटल व्योम ff_layout_commit_record_layoutstats_start(काष्ठा rpc_task *task,
		काष्ठा nfs_commit_data *cdata)
अणु
	अगर (test_and_set_bit(NFS_IOHDR_STAT, &cdata->flags))
		वापस;
	nfs4_ff_layout_stat_io_start_ग_लिखो(cdata->inode,
			FF_LAYOUT_COMP(cdata->lseg, cdata->ds_commit_index),
			0, task->tk_start);
पूर्ण

अटल व्योम ff_layout_commit_record_layoutstats_करोne(काष्ठा rpc_task *task,
		काष्ठा nfs_commit_data *cdata)
अणु
	काष्ठा nfs_page *req;
	__u64 count = 0;

	अगर (!test_and_clear_bit(NFS_IOHDR_STAT, &cdata->flags))
		वापस;

	अगर (task->tk_status == 0) अणु
		list_क्रम_each_entry(req, &cdata->pages, wb_list)
			count += req->wb_bytes;
	पूर्ण
	nfs4_ff_layout_stat_io_end_ग_लिखो(task,
			FF_LAYOUT_COMP(cdata->lseg, cdata->ds_commit_index),
			count, count, NFS_खाता_SYNC);
	set_bit(NFS_LSEG_LAYOUTRETURN, &cdata->lseg->pls_flags);
पूर्ण

अटल व्योम ff_layout_commit_prepare_common(काष्ठा rpc_task *task,
		काष्ठा nfs_commit_data *cdata)
अणु
	ff_layout_commit_record_layoutstats_start(task, cdata);
पूर्ण

अटल व्योम ff_layout_commit_prepare_v3(काष्ठा rpc_task *task, व्योम *data)
अणु
	ff_layout_commit_prepare_common(task, data);
	rpc_call_start(task);
पूर्ण

अटल व्योम ff_layout_commit_prepare_v4(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_commit_data *wdata = data;

	अगर (nfs4_setup_sequence(wdata->ds_clp,
				&wdata->args.seq_args,
				&wdata->res.seq_res,
				task))
		वापस;
	ff_layout_commit_prepare_common(task, data);
पूर्ण

अटल व्योम ff_layout_commit_करोne(काष्ठा rpc_task *task, व्योम *data)
अणु
	pnfs_generic_ग_लिखो_commit_करोne(task, data);
पूर्ण

अटल व्योम ff_layout_commit_count_stats(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_commit_data *cdata = data;

	ff_layout_commit_record_layoutstats_करोne(task, cdata);
	rpc_count_iostats_metrics(task,
	    &NFS_CLIENT(cdata->inode)->cl_metrics[NFSPROC4_CLNT_COMMIT]);
पूर्ण

अटल व्योम ff_layout_commit_release(व्योम *data)
अणु
	काष्ठा nfs_commit_data *cdata = data;

	ff_layout_commit_record_layoutstats_करोne(&cdata->task, cdata);
	pnfs_generic_commit_release(data);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops ff_layout_पढ़ो_call_ops_v3 = अणु
	.rpc_call_prepare = ff_layout_पढ़ो_prepare_v3,
	.rpc_call_करोne = ff_layout_पढ़ो_call_करोne,
	.rpc_count_stats = ff_layout_पढ़ो_count_stats,
	.rpc_release = ff_layout_पढ़ो_release,
पूर्ण;

अटल स्थिर काष्ठा rpc_call_ops ff_layout_पढ़ो_call_ops_v4 = अणु
	.rpc_call_prepare = ff_layout_पढ़ो_prepare_v4,
	.rpc_call_करोne = ff_layout_पढ़ो_call_करोne,
	.rpc_count_stats = ff_layout_पढ़ो_count_stats,
	.rpc_release = ff_layout_पढ़ो_release,
पूर्ण;

अटल स्थिर काष्ठा rpc_call_ops ff_layout_ग_लिखो_call_ops_v3 = अणु
	.rpc_call_prepare = ff_layout_ग_लिखो_prepare_v3,
	.rpc_call_करोne = ff_layout_ग_लिखो_call_करोne,
	.rpc_count_stats = ff_layout_ग_लिखो_count_stats,
	.rpc_release = ff_layout_ग_लिखो_release,
पूर्ण;

अटल स्थिर काष्ठा rpc_call_ops ff_layout_ग_लिखो_call_ops_v4 = अणु
	.rpc_call_prepare = ff_layout_ग_लिखो_prepare_v4,
	.rpc_call_करोne = ff_layout_ग_लिखो_call_करोne,
	.rpc_count_stats = ff_layout_ग_लिखो_count_stats,
	.rpc_release = ff_layout_ग_लिखो_release,
पूर्ण;

अटल स्थिर काष्ठा rpc_call_ops ff_layout_commit_call_ops_v3 = अणु
	.rpc_call_prepare = ff_layout_commit_prepare_v3,
	.rpc_call_करोne = ff_layout_commit_करोne,
	.rpc_count_stats = ff_layout_commit_count_stats,
	.rpc_release = ff_layout_commit_release,
पूर्ण;

अटल स्थिर काष्ठा rpc_call_ops ff_layout_commit_call_ops_v4 = अणु
	.rpc_call_prepare = ff_layout_commit_prepare_v4,
	.rpc_call_करोne = ff_layout_commit_करोne,
	.rpc_count_stats = ff_layout_commit_count_stats,
	.rpc_release = ff_layout_commit_release,
पूर्ण;

अटल क्रमागत pnfs_try_status
ff_layout_पढ़ो_pagelist(काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा pnfs_layout_segment *lseg = hdr->lseg;
	काष्ठा nfs4_pnfs_ds *ds;
	काष्ठा rpc_clnt *ds_clnt;
	काष्ठा nfs4_ff_layout_mirror *mirror;
	स्थिर काष्ठा cred *ds_cred;
	loff_t offset = hdr->args.offset;
	u32 idx = hdr->pgio_mirror_idx;
	पूर्णांक vers;
	काष्ठा nfs_fh *fh;

	dprपूर्णांकk("--> %s ino %lu pgbase %u req %zu@%llu\n",
		__func__, hdr->inode->i_ino,
		hdr->args.pgbase, (माप_प्रकार)hdr->args.count, offset);

	mirror = FF_LAYOUT_COMP(lseg, idx);
	ds = nfs4_ff_layout_prepare_ds(lseg, mirror, false);
	अगर (!ds)
		जाओ out_failed;

	ds_clnt = nfs4_ff_find_or_create_ds_client(mirror, ds->ds_clp,
						   hdr->inode);
	अगर (IS_ERR(ds_clnt))
		जाओ out_failed;

	ds_cred = ff_layout_get_ds_cred(mirror, &lseg->pls_range, hdr->cred);
	अगर (!ds_cred)
		जाओ out_failed;

	vers = nfs4_ff_layout_ds_version(mirror);

	dprपूर्णांकk("%s USE DS: %s cl_count %d vers %d\n", __func__,
		ds->ds_remotestr, refcount_पढ़ो(&ds->ds_clp->cl_count), vers);

	hdr->pgio_करोne_cb = ff_layout_पढ़ो_करोne_cb;
	refcount_inc(&ds->ds_clp->cl_count);
	hdr->ds_clp = ds->ds_clp;
	fh = nfs4_ff_layout_select_ds_fh(mirror);
	अगर (fh)
		hdr->args.fh = fh;

	nfs4_ff_layout_select_ds_stateid(mirror, &hdr->args.stateid);

	/*
	 * Note that अगर we ever decide to split across DSes,
	 * then we may need to handle dense-like offsets.
	 */
	hdr->args.offset = offset;
	hdr->mds_offset = offset;

	/* Perक्रमm an asynchronous पढ़ो to ds */
	nfs_initiate_pgio(ds_clnt, hdr, ds_cred, ds->ds_clp->rpc_ops,
			  vers == 3 ? &ff_layout_पढ़ो_call_ops_v3 :
				      &ff_layout_पढ़ो_call_ops_v4,
			  0, RPC_TASK_SOFTCONN);
	put_cred(ds_cred);
	वापस PNFS_ATTEMPTED;

out_failed:
	अगर (ff_layout_aव्योम_mds_available_ds(lseg))
		वापस PNFS_TRY_AGAIN;
	trace_pnfs_mds_fallback_पढ़ो_pagelist(hdr->inode,
			hdr->args.offset, hdr->args.count,
			IOMODE_READ, NFS_I(hdr->inode)->layout, lseg);
	वापस PNFS_NOT_ATTEMPTED;
पूर्ण

/* Perक्रमm async ग_लिखोs. */
अटल क्रमागत pnfs_try_status
ff_layout_ग_लिखो_pagelist(काष्ठा nfs_pgio_header *hdr, पूर्णांक sync)
अणु
	काष्ठा pnfs_layout_segment *lseg = hdr->lseg;
	काष्ठा nfs4_pnfs_ds *ds;
	काष्ठा rpc_clnt *ds_clnt;
	काष्ठा nfs4_ff_layout_mirror *mirror;
	स्थिर काष्ठा cred *ds_cred;
	loff_t offset = hdr->args.offset;
	पूर्णांक vers;
	काष्ठा nfs_fh *fh;
	u32 idx = hdr->pgio_mirror_idx;

	mirror = FF_LAYOUT_COMP(lseg, idx);
	ds = nfs4_ff_layout_prepare_ds(lseg, mirror, true);
	अगर (!ds)
		जाओ out_failed;

	ds_clnt = nfs4_ff_find_or_create_ds_client(mirror, ds->ds_clp,
						   hdr->inode);
	अगर (IS_ERR(ds_clnt))
		जाओ out_failed;

	ds_cred = ff_layout_get_ds_cred(mirror, &lseg->pls_range, hdr->cred);
	अगर (!ds_cred)
		जाओ out_failed;

	vers = nfs4_ff_layout_ds_version(mirror);

	dprपूर्णांकk("%s ino %lu sync %d req %zu@%llu DS: %s cl_count %d vers %d\n",
		__func__, hdr->inode->i_ino, sync, (माप_प्रकार) hdr->args.count,
		offset, ds->ds_remotestr, refcount_पढ़ो(&ds->ds_clp->cl_count),
		vers);

	hdr->pgio_करोne_cb = ff_layout_ग_लिखो_करोne_cb;
	refcount_inc(&ds->ds_clp->cl_count);
	hdr->ds_clp = ds->ds_clp;
	hdr->ds_commit_idx = idx;
	fh = nfs4_ff_layout_select_ds_fh(mirror);
	अगर (fh)
		hdr->args.fh = fh;

	nfs4_ff_layout_select_ds_stateid(mirror, &hdr->args.stateid);

	/*
	 * Note that अगर we ever decide to split across DSes,
	 * then we may need to handle dense-like offsets.
	 */
	hdr->args.offset = offset;

	/* Perक्रमm an asynchronous ग_लिखो */
	nfs_initiate_pgio(ds_clnt, hdr, ds_cred, ds->ds_clp->rpc_ops,
			  vers == 3 ? &ff_layout_ग_लिखो_call_ops_v3 :
				      &ff_layout_ग_लिखो_call_ops_v4,
			  sync, RPC_TASK_SOFTCONN);
	put_cred(ds_cred);
	वापस PNFS_ATTEMPTED;

out_failed:
	अगर (ff_layout_aव्योम_mds_available_ds(lseg))
		वापस PNFS_TRY_AGAIN;
	trace_pnfs_mds_fallback_ग_लिखो_pagelist(hdr->inode,
			hdr->args.offset, hdr->args.count,
			IOMODE_RW, NFS_I(hdr->inode)->layout, lseg);
	वापस PNFS_NOT_ATTEMPTED;
पूर्ण

अटल u32 calc_ds_index_from_commit(काष्ठा pnfs_layout_segment *lseg, u32 i)
अणु
	वापस i;
पूर्ण

अटल काष्ठा nfs_fh *
select_ds_fh_from_commit(काष्ठा pnfs_layout_segment *lseg, u32 i)
अणु
	काष्ठा nfs4_ff_layout_segment *flseg = FF_LAYOUT_LSEG(lseg);

	/* FIXME: Assume that there is only one NFS version available
	 * क्रम the DS.
	 */
	वापस &flseg->mirror_array[i]->fh_versions[0];
पूर्ण

अटल पूर्णांक ff_layout_initiate_commit(काष्ठा nfs_commit_data *data, पूर्णांक how)
अणु
	काष्ठा pnfs_layout_segment *lseg = data->lseg;
	काष्ठा nfs4_pnfs_ds *ds;
	काष्ठा rpc_clnt *ds_clnt;
	काष्ठा nfs4_ff_layout_mirror *mirror;
	स्थिर काष्ठा cred *ds_cred;
	u32 idx;
	पूर्णांक vers, ret;
	काष्ठा nfs_fh *fh;

	अगर (!lseg || !(pnfs_is_valid_lseg(lseg) ||
	    test_bit(NFS_LSEG_LAYOUTRETURN, &lseg->pls_flags)))
		जाओ out_err;

	idx = calc_ds_index_from_commit(lseg, data->ds_commit_index);
	mirror = FF_LAYOUT_COMP(lseg, idx);
	ds = nfs4_ff_layout_prepare_ds(lseg, mirror, true);
	अगर (!ds)
		जाओ out_err;

	ds_clnt = nfs4_ff_find_or_create_ds_client(mirror, ds->ds_clp,
						   data->inode);
	अगर (IS_ERR(ds_clnt))
		जाओ out_err;

	ds_cred = ff_layout_get_ds_cred(mirror, &lseg->pls_range, data->cred);
	अगर (!ds_cred)
		जाओ out_err;

	vers = nfs4_ff_layout_ds_version(mirror);

	dprपूर्णांकk("%s ino %lu, how %d cl_count %d vers %d\n", __func__,
		data->inode->i_ino, how, refcount_पढ़ो(&ds->ds_clp->cl_count),
		vers);
	data->commit_करोne_cb = ff_layout_commit_करोne_cb;
	data->cred = ds_cred;
	refcount_inc(&ds->ds_clp->cl_count);
	data->ds_clp = ds->ds_clp;
	fh = select_ds_fh_from_commit(lseg, data->ds_commit_index);
	अगर (fh)
		data->args.fh = fh;

	ret = nfs_initiate_commit(ds_clnt, data, ds->ds_clp->rpc_ops,
				   vers == 3 ? &ff_layout_commit_call_ops_v3 :
					       &ff_layout_commit_call_ops_v4,
				   how, RPC_TASK_SOFTCONN);
	put_cred(ds_cred);
	वापस ret;
out_err:
	pnfs_generic_prepare_to_resend_ग_लिखोs(data);
	pnfs_generic_commit_release(data);
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक
ff_layout_commit_pagelist(काष्ठा inode *inode, काष्ठा list_head *mds_pages,
			   पूर्णांक how, काष्ठा nfs_commit_info *cinfo)
अणु
	वापस pnfs_generic_commit_pagelist(inode, mds_pages, how, cinfo,
					    ff_layout_initiate_commit);
पूर्ण

अटल काष्ठा pnfs_ds_commit_info *
ff_layout_get_ds_info(काष्ठा inode *inode)
अणु
	काष्ठा pnfs_layout_hdr *layout = NFS_I(inode)->layout;

	अगर (layout == शून्य)
		वापस शून्य;

	वापस &FF_LAYOUT_FROM_HDR(layout)->commit_info;
पूर्ण

अटल व्योम
ff_layout_setup_ds_info(काष्ठा pnfs_ds_commit_info *fl_cinfo,
		काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा nfs4_ff_layout_segment *flseg = FF_LAYOUT_LSEG(lseg);
	काष्ठा inode *inode = lseg->pls_layout->plh_inode;
	काष्ठा pnfs_commit_array *array, *new;

	new = pnfs_alloc_commit_array(flseg->mirror_array_cnt, GFP_NOIO);
	अगर (new) अणु
		spin_lock(&inode->i_lock);
		array = pnfs_add_commit_array(fl_cinfo, new, lseg);
		spin_unlock(&inode->i_lock);
		अगर (array != new)
			pnfs_मुक्त_commit_array(new);
	पूर्ण
पूर्ण

अटल व्योम
ff_layout_release_ds_info(काष्ठा pnfs_ds_commit_info *fl_cinfo,
		काष्ठा inode *inode)
अणु
	spin_lock(&inode->i_lock);
	pnfs_generic_ds_cinfo_destroy(fl_cinfo);
	spin_unlock(&inode->i_lock);
पूर्ण

अटल व्योम
ff_layout_मुक्त_deviceid_node(काष्ठा nfs4_deviceid_node *d)
अणु
	nfs4_ff_layout_मुक्त_deviceid(container_of(d, काष्ठा nfs4_ff_layout_ds,
						  id_node));
पूर्ण

अटल पूर्णांक ff_layout_encode_ioerr(काष्ठा xdr_stream *xdr,
				  स्थिर काष्ठा nfs4_layoutवापस_args *args,
				  स्थिर काष्ठा nfs4_flexfile_layoutवापस_args *ff_args)
अणु
	__be32 *start;

	start = xdr_reserve_space(xdr, 4);
	अगर (unlikely(!start))
		वापस -E2BIG;

	*start = cpu_to_be32(ff_args->num_errors);
	/* This assume we always वापस _ALL_ layouts */
	वापस ff_layout_encode_ds_ioerr(xdr, &ff_args->errors);
पूर्ण

अटल व्योम
encode_opaque_fixed(काष्ठा xdr_stream *xdr, स्थिर व्योम *buf, माप_प्रकार len)
अणु
	WARN_ON_ONCE(xdr_stream_encode_opaque_fixed(xdr, buf, len) < 0);
पूर्ण

अटल व्योम
ff_layout_encode_ff_iostat_head(काष्ठा xdr_stream *xdr,
			    स्थिर nfs4_stateid *stateid,
			    स्थिर काष्ठा nfs42_layoutstat_devinfo *devinfo)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 8 + 8);
	p = xdr_encode_hyper(p, devinfo->offset);
	p = xdr_encode_hyper(p, devinfo->length);
	encode_opaque_fixed(xdr, stateid->data, NFS4_STATEID_SIZE);
	p = xdr_reserve_space(xdr, 4*8);
	p = xdr_encode_hyper(p, devinfo->पढ़ो_count);
	p = xdr_encode_hyper(p, devinfo->पढ़ो_bytes);
	p = xdr_encode_hyper(p, devinfo->ग_लिखो_count);
	p = xdr_encode_hyper(p, devinfo->ग_लिखो_bytes);
	encode_opaque_fixed(xdr, devinfo->dev_id.data, NFS4_DEVICEID4_SIZE);
पूर्ण

अटल व्योम
ff_layout_encode_ff_iostat(काष्ठा xdr_stream *xdr,
			    स्थिर nfs4_stateid *stateid,
			    स्थिर काष्ठा nfs42_layoutstat_devinfo *devinfo)
अणु
	ff_layout_encode_ff_iostat_head(xdr, stateid, devinfo);
	ff_layout_encode_ff_layoutupdate(xdr, devinfo,
			devinfo->ld_निजी.data);
पूर्ण

/* report nothing क्रम now */
अटल व्योम ff_layout_encode_iostats_array(काष्ठा xdr_stream *xdr,
		स्थिर काष्ठा nfs4_layoutवापस_args *args,
		काष्ठा nfs4_flexfile_layoutवापस_args *ff_args)
अणु
	__be32 *p;
	पूर्णांक i;

	p = xdr_reserve_space(xdr, 4);
	*p = cpu_to_be32(ff_args->num_dev);
	क्रम (i = 0; i < ff_args->num_dev; i++)
		ff_layout_encode_ff_iostat(xdr,
				&args->layout->plh_stateid,
				&ff_args->devinfo[i]);
पूर्ण

अटल व्योम
ff_layout_मुक्त_iostats_array(काष्ठा nfs42_layoutstat_devinfo *devinfo,
		अचिन्हित पूर्णांक num_entries)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_entries; i++) अणु
		अगर (!devinfo[i].ld_निजी.ops)
			जारी;
		अगर (!devinfo[i].ld_निजी.ops->मुक्त)
			जारी;
		devinfo[i].ld_निजी.ops->मुक्त(&devinfo[i].ld_निजी);
	पूर्ण
पूर्ण

अटल काष्ठा nfs4_deviceid_node *
ff_layout_alloc_deviceid_node(काष्ठा nfs_server *server,
			      काष्ठा pnfs_device *pdev, gfp_t gfp_flags)
अणु
	काष्ठा nfs4_ff_layout_ds *dsaddr;

	dsaddr = nfs4_ff_alloc_deviceid_node(server, pdev, gfp_flags);
	अगर (!dsaddr)
		वापस शून्य;
	वापस &dsaddr->id_node;
पूर्ण

अटल व्योम
ff_layout_encode_layoutवापस(काष्ठा xdr_stream *xdr,
		स्थिर व्योम *व्योमargs,
		स्थिर काष्ठा nfs4_xdr_opaque_data *ff_opaque)
अणु
	स्थिर काष्ठा nfs4_layoutवापस_args *args = व्योमargs;
	काष्ठा nfs4_flexfile_layoutवापस_args *ff_args = ff_opaque->data;
	काष्ठा xdr_buf पंचांगp_buf = अणु
		.head = अणु
			[0] = अणु
				.iov_base = page_address(ff_args->pages[0]),
			पूर्ण,
		पूर्ण,
		.buflen = PAGE_SIZE,
	पूर्ण;
	काष्ठा xdr_stream पंचांगp_xdr;
	__be32 *start;

	dprपूर्णांकk("%s: Begin\n", __func__);

	xdr_init_encode(&पंचांगp_xdr, &पंचांगp_buf, शून्य, शून्य);

	ff_layout_encode_ioerr(&पंचांगp_xdr, args, ff_args);
	ff_layout_encode_iostats_array(&पंचांगp_xdr, args, ff_args);

	start = xdr_reserve_space(xdr, 4);
	*start = cpu_to_be32(पंचांगp_buf.len);
	xdr_ग_लिखो_pages(xdr, ff_args->pages, 0, पंचांगp_buf.len);

	dprपूर्णांकk("%s: Return\n", __func__);
पूर्ण

अटल व्योम
ff_layout_मुक्त_layoutवापस(काष्ठा nfs4_xdr_opaque_data *args)
अणु
	काष्ठा nfs4_flexfile_layoutवापस_args *ff_args;

	अगर (!args->data)
		वापस;
	ff_args = args->data;
	args->data = शून्य;

	ff_layout_मुक्त_ds_ioerr(&ff_args->errors);
	ff_layout_मुक्त_iostats_array(ff_args->devinfo, ff_args->num_dev);

	put_page(ff_args->pages[0]);
	kमुक्त(ff_args);
पूर्ण

अटल स्थिर काष्ठा nfs4_xdr_opaque_ops layoutवापस_ops = अणु
	.encode = ff_layout_encode_layoutवापस,
	.मुक्त = ff_layout_मुक्त_layoutवापस,
पूर्ण;

अटल पूर्णांक
ff_layout_prepare_layoutवापस(काष्ठा nfs4_layoutवापस_args *args)
अणु
	काष्ठा nfs4_flexfile_layoutवापस_args *ff_args;
	काष्ठा nfs4_flexfile_layout *ff_layout = FF_LAYOUT_FROM_HDR(args->layout);

	ff_args = kदो_स्मृति(माप(*ff_args), GFP_KERNEL);
	अगर (!ff_args)
		जाओ out_nomem;
	ff_args->pages[0] = alloc_page(GFP_KERNEL);
	अगर (!ff_args->pages[0])
		जाओ out_nomem_मुक्त;

	INIT_LIST_HEAD(&ff_args->errors);
	ff_args->num_errors = ff_layout_fetch_ds_ioerr(args->layout,
			&args->range, &ff_args->errors,
			FF_LAYOUTRETURN_MAXERR);

	spin_lock(&args->inode->i_lock);
	ff_args->num_dev = ff_layout_mirror_prepare_stats(&ff_layout->generic_hdr,
			&ff_args->devinfo[0], ARRAY_SIZE(ff_args->devinfo));
	spin_unlock(&args->inode->i_lock);

	args->ld_निजी->ops = &layoutवापस_ops;
	args->ld_निजी->data = ff_args;
	वापस 0;
out_nomem_मुक्त:
	kमुक्त(ff_args);
out_nomem:
	वापस -ENOMEM;
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_2
व्योम
ff_layout_send_layouterror(काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा pnfs_layout_hdr *lo = lseg->pls_layout;
	काष्ठा nfs42_layout_error *errors;
	LIST_HEAD(head);

	अगर (!nfs_server_capable(lo->plh_inode, NFS_CAP_LAYOUTERROR))
		वापस;
	ff_layout_fetch_ds_ioerr(lo, &lseg->pls_range, &head, -1);
	अगर (list_empty(&head))
		वापस;

	errors = kदो_स्मृति_array(NFS42_LAYOUTERROR_MAX,
			माप(*errors), GFP_NOFS);
	अगर (errors != शून्य) अणु
		स्थिर काष्ठा nfs4_ff_layout_ds_err *pos;
		माप_प्रकार n = 0;

		list_क्रम_each_entry(pos, &head, list) अणु
			errors[n].offset = pos->offset;
			errors[n].length = pos->length;
			nfs4_stateid_copy(&errors[n].stateid, &pos->stateid);
			errors[n].errors[0].dev_id = pos->deviceid;
			errors[n].errors[0].status = pos->status;
			errors[n].errors[0].opnum = pos->opnum;
			n++;
			अगर (!list_is_last(&pos->list, &head) &&
			    n < NFS42_LAYOUTERROR_MAX)
				जारी;
			अगर (nfs42_proc_layouterror(lseg, errors, n) < 0)
				अवरोध;
			n = 0;
		पूर्ण
		kमुक्त(errors);
	पूर्ण
	ff_layout_मुक्त_ds_ioerr(&head);
पूर्ण
#अन्यथा
व्योम
ff_layout_send_layouterror(काष्ठा pnfs_layout_segment *lseg)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
ff_layout_ntop4(स्थिर काष्ठा sockaddr *sap, अक्षर *buf, स्थिर माप_प्रकार buflen)
अणु
	स्थिर काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)sap;

	वापस snम_लिखो(buf, buflen, "%pI4", &sin->sin_addr);
पूर्ण

अटल माप_प्रकार
ff_layout_ntop6_noscopeid(स्थिर काष्ठा sockaddr *sap, अक्षर *buf,
			  स्थिर पूर्णांक buflen)
अणु
	स्थिर काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)sap;
	स्थिर काष्ठा in6_addr *addr = &sin6->sin6_addr;

	/*
	 * RFC 4291, Section 2.2.2
	 *
	 * Shorthanded ANY address
	 */
	अगर (ipv6_addr_any(addr))
		वापस snम_लिखो(buf, buflen, "::");

	/*
	 * RFC 4291, Section 2.2.2
	 *
	 * Shorthanded loopback address
	 */
	अगर (ipv6_addr_loopback(addr))
		वापस snम_लिखो(buf, buflen, "::1");

	/*
	 * RFC 4291, Section 2.2.3
	 *
	 * Special presentation address क्रमmat क्रम mapped v4
	 * addresses.
	 */
	अगर (ipv6_addr_v4mapped(addr))
		वापस snम_लिखो(buf, buflen, "::ffff:%pI4",
					&addr->s6_addr32[3]);

	/*
	 * RFC 4291, Section 2.2.1
	 */
	वापस snम_लिखो(buf, buflen, "%pI6c", addr);
पूर्ण

/* Derived from rpc_sockaddr2uaddr */
अटल व्योम
ff_layout_encode_netaddr(काष्ठा xdr_stream *xdr, काष्ठा nfs4_pnfs_ds_addr *da)
अणु
	काष्ठा sockaddr *sap = (काष्ठा sockaddr *)&da->da_addr;
	अक्षर portbuf[RPCBIND_MAXUADDRPLEN];
	अक्षर addrbuf[RPCBIND_MAXUADDRLEN];
	अचिन्हित लघु port;
	पूर्णांक len, netid_len;
	__be32 *p;

	चयन (sap->sa_family) अणु
	हाल AF_INET:
		अगर (ff_layout_ntop4(sap, addrbuf, माप(addrbuf)) == 0)
			वापस;
		port = ntohs(((काष्ठा sockaddr_in *)sap)->sin_port);
		अवरोध;
	हाल AF_INET6:
		अगर (ff_layout_ntop6_noscopeid(sap, addrbuf, माप(addrbuf)) == 0)
			वापस;
		port = ntohs(((काष्ठा sockaddr_in6 *)sap)->sin6_port);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	snम_लिखो(portbuf, माप(portbuf), ".%u.%u", port >> 8, port & 0xff);
	len = strlcat(addrbuf, portbuf, माप(addrbuf));

	netid_len = म_माप(da->da_netid);
	p = xdr_reserve_space(xdr, 4 + netid_len);
	xdr_encode_opaque(p, da->da_netid, netid_len);

	p = xdr_reserve_space(xdr, 4 + len);
	xdr_encode_opaque(p, addrbuf, len);
पूर्ण

अटल व्योम
ff_layout_encode_nfsसमय(काष्ठा xdr_stream *xdr,
			 kसमय_प्रकार t)
अणु
	काष्ठा बारpec64 ts;
	__be32 *p;

	p = xdr_reserve_space(xdr, 12);
	ts = kसमय_प्रकारo_बारpec64(t);
	p = xdr_encode_hyper(p, ts.tv_sec);
	*p++ = cpu_to_be32(ts.tv_nsec);
पूर्ण

अटल व्योम
ff_layout_encode_io_latency(काष्ठा xdr_stream *xdr,
			    काष्ठा nfs4_ff_io_stat *stat)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 5 * 8);
	p = xdr_encode_hyper(p, stat->ops_requested);
	p = xdr_encode_hyper(p, stat->bytes_requested);
	p = xdr_encode_hyper(p, stat->ops_completed);
	p = xdr_encode_hyper(p, stat->bytes_completed);
	p = xdr_encode_hyper(p, stat->bytes_not_delivered);
	ff_layout_encode_nfsसमय(xdr, stat->total_busy_समय);
	ff_layout_encode_nfsसमय(xdr, stat->aggregate_completion_समय);
पूर्ण

अटल व्योम
ff_layout_encode_ff_layoutupdate(काष्ठा xdr_stream *xdr,
			      स्थिर काष्ठा nfs42_layoutstat_devinfo *devinfo,
			      काष्ठा nfs4_ff_layout_mirror *mirror)
अणु
	काष्ठा nfs4_pnfs_ds_addr *da;
	काष्ठा nfs4_pnfs_ds *ds = mirror->mirror_ds->ds;
	काष्ठा nfs_fh *fh = &mirror->fh_versions[0];
	__be32 *p;

	da = list_first_entry(&ds->ds_addrs, काष्ठा nfs4_pnfs_ds_addr, da_node);
	dprपूर्णांकk("%s: DS %s: encoding address %s\n",
		__func__, ds->ds_remotestr, da->da_remotestr);
	/* netaddr4 */
	ff_layout_encode_netaddr(xdr, da);
	/* nfs_fh4 */
	p = xdr_reserve_space(xdr, 4 + fh->size);
	xdr_encode_opaque(p, fh->data, fh->size);
	/* ff_io_latency4 पढ़ो */
	spin_lock(&mirror->lock);
	ff_layout_encode_io_latency(xdr, &mirror->पढ़ो_stat.io_stat);
	/* ff_io_latency4 ग_लिखो */
	ff_layout_encode_io_latency(xdr, &mirror->ग_लिखो_stat.io_stat);
	spin_unlock(&mirror->lock);
	/* nfsसमय4 */
	ff_layout_encode_nfsसमय(xdr, kसमय_sub(kसमय_get(), mirror->start_समय));
	/* bool */
	p = xdr_reserve_space(xdr, 4);
	*p = cpu_to_be32(false);
पूर्ण

अटल व्योम
ff_layout_encode_layoutstats(काष्ठा xdr_stream *xdr, स्थिर व्योम *args,
			     स्थिर काष्ठा nfs4_xdr_opaque_data *opaque)
अणु
	काष्ठा nfs42_layoutstat_devinfo *devinfo = container_of(opaque,
			काष्ठा nfs42_layoutstat_devinfo, ld_निजी);
	__be32 *start;

	/* layoutupdate length */
	start = xdr_reserve_space(xdr, 4);
	ff_layout_encode_ff_layoutupdate(xdr, devinfo, opaque->data);

	*start = cpu_to_be32((xdr->p - start - 1) * 4);
पूर्ण

अटल व्योम
ff_layout_मुक्त_layoutstats(काष्ठा nfs4_xdr_opaque_data *opaque)
अणु
	काष्ठा nfs4_ff_layout_mirror *mirror = opaque->data;

	ff_layout_put_mirror(mirror);
पूर्ण

अटल स्थिर काष्ठा nfs4_xdr_opaque_ops layoutstat_ops = अणु
	.encode = ff_layout_encode_layoutstats,
	.मुक्त	= ff_layout_मुक्त_layoutstats,
पूर्ण;

अटल पूर्णांक
ff_layout_mirror_prepare_stats(काष्ठा pnfs_layout_hdr *lo,
			       काष्ठा nfs42_layoutstat_devinfo *devinfo,
			       पूर्णांक dev_limit)
अणु
	काष्ठा nfs4_flexfile_layout *ff_layout = FF_LAYOUT_FROM_HDR(lo);
	काष्ठा nfs4_ff_layout_mirror *mirror;
	काष्ठा nfs4_deviceid_node *dev;
	पूर्णांक i = 0;

	list_क्रम_each_entry(mirror, &ff_layout->mirrors, mirrors) अणु
		अगर (i >= dev_limit)
			अवरोध;
		अगर (IS_ERR_OR_शून्य(mirror->mirror_ds))
			जारी;
		अगर (!test_and_clear_bit(NFS4_FF_MIRROR_STAT_AVAIL, &mirror->flags))
			जारी;
		/* mirror refcount put in cleanup_layoutstats */
		अगर (!refcount_inc_not_zero(&mirror->ref))
			जारी;
		dev = &mirror->mirror_ds->id_node; 
		स_नकल(&devinfo->dev_id, &dev->deviceid, NFS4_DEVICEID4_SIZE);
		devinfo->offset = 0;
		devinfo->length = NFS4_MAX_UINT64;
		spin_lock(&mirror->lock);
		devinfo->पढ़ो_count = mirror->पढ़ो_stat.io_stat.ops_completed;
		devinfo->पढ़ो_bytes = mirror->पढ़ो_stat.io_stat.bytes_completed;
		devinfo->ग_लिखो_count = mirror->ग_लिखो_stat.io_stat.ops_completed;
		devinfo->ग_लिखो_bytes = mirror->ग_लिखो_stat.io_stat.bytes_completed;
		spin_unlock(&mirror->lock);
		devinfo->layout_type = LAYOUT_FLEX_खाताS;
		devinfo->ld_निजी.ops = &layoutstat_ops;
		devinfo->ld_निजी.data = mirror;

		devinfo++;
		i++;
	पूर्ण
	वापस i;
पूर्ण

अटल पूर्णांक
ff_layout_prepare_layoutstats(काष्ठा nfs42_layoutstat_args *args)
अणु
	काष्ठा nfs4_flexfile_layout *ff_layout;
	स्थिर पूर्णांक dev_count = PNFS_LAYOUTSTATS_MAXDEV;

	/* For now, send at most PNFS_LAYOUTSTATS_MAXDEV statistics */
	args->devinfo = kदो_स्मृति_array(dev_count, माप(*args->devinfo), GFP_NOIO);
	अगर (!args->devinfo)
		वापस -ENOMEM;

	spin_lock(&args->inode->i_lock);
	ff_layout = FF_LAYOUT_FROM_HDR(NFS_I(args->inode)->layout);
	args->num_dev = ff_layout_mirror_prepare_stats(&ff_layout->generic_hdr,
			&args->devinfo[0], dev_count);
	spin_unlock(&args->inode->i_lock);
	अगर (!args->num_dev) अणु
		kमुक्त(args->devinfo);
		args->devinfo = शून्य;
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ff_layout_set_layoutdriver(काष्ठा nfs_server *server,
		स्थिर काष्ठा nfs_fh *dummy)
अणु
#अगर IS_ENABLED(CONFIG_NFS_V4_2)
	server->caps |= NFS_CAP_LAYOUTSTATS;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pnfs_commit_ops ff_layout_commit_ops = अणु
	.setup_ds_info		= ff_layout_setup_ds_info,
	.release_ds_info	= ff_layout_release_ds_info,
	.mark_request_commit	= pnfs_layout_mark_request_commit,
	.clear_request_commit	= pnfs_generic_clear_request_commit,
	.scan_commit_lists	= pnfs_generic_scan_commit_lists,
	.recover_commit_reqs	= pnfs_generic_recover_commit_reqs,
	.commit_pagelist	= ff_layout_commit_pagelist,
पूर्ण;

अटल काष्ठा pnfs_layoutdriver_type flexfilelayout_type = अणु
	.id			= LAYOUT_FLEX_खाताS,
	.name			= "LAYOUT_FLEX_FILES",
	.owner			= THIS_MODULE,
	.flags			= PNFS_LAYOUTGET_ON_OPEN,
	.max_layoutget_response	= 4096, /* 1 page or so... */
	.set_layoutdriver	= ff_layout_set_layoutdriver,
	.alloc_layout_hdr	= ff_layout_alloc_layout_hdr,
	.मुक्त_layout_hdr	= ff_layout_मुक्त_layout_hdr,
	.alloc_lseg		= ff_layout_alloc_lseg,
	.मुक्त_lseg		= ff_layout_मुक्त_lseg,
	.add_lseg		= ff_layout_add_lseg,
	.pg_पढ़ो_ops		= &ff_layout_pg_पढ़ो_ops,
	.pg_ग_लिखो_ops		= &ff_layout_pg_ग_लिखो_ops,
	.get_ds_info		= ff_layout_get_ds_info,
	.मुक्त_deviceid_node	= ff_layout_मुक्त_deviceid_node,
	.पढ़ो_pagelist		= ff_layout_पढ़ो_pagelist,
	.ग_लिखो_pagelist		= ff_layout_ग_लिखो_pagelist,
	.alloc_deviceid_node    = ff_layout_alloc_deviceid_node,
	.prepare_layoutवापस   = ff_layout_prepare_layoutवापस,
	.sync			= pnfs_nfs_generic_sync,
	.prepare_layoutstats	= ff_layout_prepare_layoutstats,
पूर्ण;

अटल पूर्णांक __init nfs4flexfilelayout_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "%s: NFSv4 Flexfile Layout Driver Registering...\n",
	       __func__);
	वापस pnfs_रेजिस्टर_layoutdriver(&flexfilelayout_type);
पूर्ण

अटल व्योम __निकास nfs4flexfilelayout_निकास(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "%s: NFSv4 Flexfile Layout Driver Unregistering...\n",
	       __func__);
	pnfs_unरेजिस्टर_layoutdriver(&flexfilelayout_type);
पूर्ण

MODULE_ALIAS("nfs-layouttype4-4");

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("The NFSv4 flexfile layout driver");

module_init(nfs4flexfilelayout_init);
module_निकास(nfs4flexfilelayout_निकास);

module_param(io_maxretrans, uलघु, 0644);
MODULE_PARM_DESC(io_maxretrans, "The  number of times the NFSv4.1 client "
			"retries an I/O request before returning an error. ");
