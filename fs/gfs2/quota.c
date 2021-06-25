<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2007 Red Hat, Inc.  All rights reserved.
 */

/*
 * Quota change tags are associated with each transaction that allocates or
 * deallocates space.  Those changes are accumulated locally to each node (in a
 * per-node file) and then are periodically synced to the quota file.  This
 * aव्योमs the bottleneck of स्थिरantly touching the quota file, but पूर्णांकroduces
 * fuzziness in the current usage value of IDs that are being used on dअगरferent
 * nodes in the cluster simultaneously.  So, it is possible क्रम a user on
 * multiple nodes to overrun their quota, but that overrun is controlable.
 * Since quota tags are part of transactions, there is no need क्रम a quota check
 * program to be run on node crashes or anything like that.
 *
 * There are couple of knobs that let the administrator manage the quota
 * fuzziness.  "quota_quantum" sets the maximum समय a quota change can be
 * sitting on one node beक्रमe being synced to the quota file.  (The शेष is
 * 60 seconds.)  Another knob, "quota_scale" controls how quickly the frequency
 * of quota file syncs increases as the user moves बंदr to their limit.  The
 * more frequent the syncs, the more accurate the quota enक्रमcement, but that
 * means that there is more contention between the nodes क्रम the quota file.
 * The शेष value is one.  This sets the maximum theoretical quota overrun
 * (with infinite node with infinite bandwidth) to twice the user's limit.  (In
 * practice, the maximum overrun you see should be much less.)  A "quota_scale"
 * number greater than one makes quota syncs more frequent and reduces the
 * maximum overrun.  Numbers less than one (but greater than zero) make quota
 * syncs less frequent.
 *
 * GFS quotas also use per-ID Lock Value Blocks (LVBs) to cache the contents of
 * the quota file, so it is not being स्थिरantly पढ़ो.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/sort.h>
#समावेश <linux/fs.h>
#समावेश <linux/bपन.स>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/quota.h>
#समावेश <linux/dqblk_xfs.h>
#समावेश <linux/lockref.h>
#समावेश <linux/list_lru.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rculist_bl.h>
#समावेश <linux/bit_spinlock.h>
#समावेश <linux/jhash.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "bmap.h"
#समावेश "glock.h"
#समावेश "glops.h"
#समावेश "log.h"
#समावेश "meta_io.h"
#समावेश "quota.h"
#समावेश "rgrp.h"
#समावेश "super.h"
#समावेश "trans.h"
#समावेश "inode.h"
#समावेश "util.h"

#घोषणा GFS2_QD_HASH_SHIFT      12
#घोषणा GFS2_QD_HASH_SIZE       BIT(GFS2_QD_HASH_SHIFT)
#घोषणा GFS2_QD_HASH_MASK       (GFS2_QD_HASH_SIZE - 1)

/* Lock order: qd_lock -> bucket lock -> qd->lockref.lock -> lru lock */
/*                     -> sd_biपंचांगap_lock                              */
अटल DEFINE_SPINLOCK(qd_lock);
काष्ठा list_lru gfs2_qd_lru;

अटल काष्ठा hlist_bl_head qd_hash_table[GFS2_QD_HASH_SIZE];

अटल अचिन्हित पूर्णांक gfs2_qd_hash(स्थिर काष्ठा gfs2_sbd *sdp,
				 स्थिर काष्ठा kqid qid)
अणु
	अचिन्हित पूर्णांक h;

	h = jhash(&sdp, माप(काष्ठा gfs2_sbd *), 0);
	h = jhash(&qid, माप(काष्ठा kqid), h);

	वापस h & GFS2_QD_HASH_MASK;
पूर्ण

अटल अंतरभूत व्योम spin_lock_bucket(अचिन्हित पूर्णांक hash)
अणु
        hlist_bl_lock(&qd_hash_table[hash]);
पूर्ण

अटल अंतरभूत व्योम spin_unlock_bucket(अचिन्हित पूर्णांक hash)
अणु
        hlist_bl_unlock(&qd_hash_table[hash]);
पूर्ण

अटल व्योम gfs2_qd_dealloc(काष्ठा rcu_head *rcu)
अणु
	काष्ठा gfs2_quota_data *qd = container_of(rcu, काष्ठा gfs2_quota_data, qd_rcu);
	kmem_cache_मुक्त(gfs2_quotad_cachep, qd);
पूर्ण

अटल व्योम gfs2_qd_dispose(काष्ठा list_head *list)
अणु
	काष्ठा gfs2_quota_data *qd;
	काष्ठा gfs2_sbd *sdp;

	जबतक (!list_empty(list)) अणु
		qd = list_first_entry(list, काष्ठा gfs2_quota_data, qd_lru);
		sdp = qd->qd_gl->gl_name.ln_sbd;

		list_del(&qd->qd_lru);

		/* Free from the fileप्रणाली-specअगरic list */
		spin_lock(&qd_lock);
		list_del(&qd->qd_list);
		spin_unlock(&qd_lock);

		spin_lock_bucket(qd->qd_hash);
		hlist_bl_del_rcu(&qd->qd_hlist);
		spin_unlock_bucket(qd->qd_hash);

		gfs2_निश्चित_warn(sdp, !qd->qd_change);
		gfs2_निश्चित_warn(sdp, !qd->qd_slot_count);
		gfs2_निश्चित_warn(sdp, !qd->qd_bh_count);

		gfs2_glock_put(qd->qd_gl);
		atomic_dec(&sdp->sd_quota_count);

		/* Delete it from the common reclaim list */
		call_rcu(&qd->qd_rcu, gfs2_qd_dealloc);
	पूर्ण
पूर्ण


अटल क्रमागत lru_status gfs2_qd_isolate(काष्ठा list_head *item,
		काष्ठा list_lru_one *lru, spinlock_t *lru_lock, व्योम *arg)
अणु
	काष्ठा list_head *dispose = arg;
	काष्ठा gfs2_quota_data *qd = list_entry(item, काष्ठा gfs2_quota_data, qd_lru);

	अगर (!spin_trylock(&qd->qd_lockref.lock))
		वापस LRU_SKIP;

	अगर (qd->qd_lockref.count == 0) अणु
		lockref_mark_dead(&qd->qd_lockref);
		list_lru_isolate_move(lru, &qd->qd_lru, dispose);
	पूर्ण

	spin_unlock(&qd->qd_lockref.lock);
	वापस LRU_REMOVED;
पूर्ण

अटल अचिन्हित दीर्घ gfs2_qd_shrink_scan(काष्ठा shrinker *shrink,
					 काष्ठा shrink_control *sc)
अणु
	LIST_HEAD(dispose);
	अचिन्हित दीर्घ मुक्तd;

	अगर (!(sc->gfp_mask & __GFP_FS))
		वापस SHRINK_STOP;

	मुक्तd = list_lru_shrink_walk(&gfs2_qd_lru, sc,
				     gfs2_qd_isolate, &dispose);

	gfs2_qd_dispose(&dispose);

	वापस मुक्तd;
पूर्ण

अटल अचिन्हित दीर्घ gfs2_qd_shrink_count(काष्ठा shrinker *shrink,
					  काष्ठा shrink_control *sc)
अणु
	वापस vfs_pressure_ratio(list_lru_shrink_count(&gfs2_qd_lru, sc));
पूर्ण

काष्ठा shrinker gfs2_qd_shrinker = अणु
	.count_objects = gfs2_qd_shrink_count,
	.scan_objects = gfs2_qd_shrink_scan,
	.seeks = DEFAULT_SEEKS,
	.flags = SHRINKER_NUMA_AWARE,
पूर्ण;


अटल u64 qd2index(काष्ठा gfs2_quota_data *qd)
अणु
	काष्ठा kqid qid = qd->qd_id;
	वापस (2 * (u64)from_kqid(&init_user_ns, qid)) +
		((qid.type == USRQUOTA) ? 0 : 1);
पूर्ण

अटल u64 qd2offset(काष्ठा gfs2_quota_data *qd)
अणु
	u64 offset;

	offset = qd2index(qd);
	offset *= माप(काष्ठा gfs2_quota);

	वापस offset;
पूर्ण

अटल काष्ठा gfs2_quota_data *qd_alloc(अचिन्हित hash, काष्ठा gfs2_sbd *sdp, काष्ठा kqid qid)
अणु
	काष्ठा gfs2_quota_data *qd;
	पूर्णांक error;

	qd = kmem_cache_zalloc(gfs2_quotad_cachep, GFP_NOFS);
	अगर (!qd)
		वापस शून्य;

	qd->qd_sbd = sdp;
	qd->qd_lockref.count = 1;
	spin_lock_init(&qd->qd_lockref.lock);
	qd->qd_id = qid;
	qd->qd_slot = -1;
	INIT_LIST_HEAD(&qd->qd_lru);
	qd->qd_hash = hash;

	error = gfs2_glock_get(sdp, qd2index(qd),
			      &gfs2_quota_glops, CREATE, &qd->qd_gl);
	अगर (error)
		जाओ fail;

	वापस qd;

fail:
	kmem_cache_मुक्त(gfs2_quotad_cachep, qd);
	वापस शून्य;
पूर्ण

अटल काष्ठा gfs2_quota_data *gfs2_qd_search_bucket(अचिन्हित पूर्णांक hash,
						     स्थिर काष्ठा gfs2_sbd *sdp,
						     काष्ठा kqid qid)
अणु
	काष्ठा gfs2_quota_data *qd;
	काष्ठा hlist_bl_node *h;

	hlist_bl_क्रम_each_entry_rcu(qd, h, &qd_hash_table[hash], qd_hlist) अणु
		अगर (!qid_eq(qd->qd_id, qid))
			जारी;
		अगर (qd->qd_sbd != sdp)
			जारी;
		अगर (lockref_get_not_dead(&qd->qd_lockref)) अणु
			list_lru_del(&gfs2_qd_lru, &qd->qd_lru);
			वापस qd;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण


अटल पूर्णांक qd_get(काष्ठा gfs2_sbd *sdp, काष्ठा kqid qid,
		  काष्ठा gfs2_quota_data **qdp)
अणु
	काष्ठा gfs2_quota_data *qd, *new_qd;
	अचिन्हित पूर्णांक hash = gfs2_qd_hash(sdp, qid);

	rcu_पढ़ो_lock();
	*qdp = qd = gfs2_qd_search_bucket(hash, sdp, qid);
	rcu_पढ़ो_unlock();

	अगर (qd)
		वापस 0;

	new_qd = qd_alloc(hash, sdp, qid);
	अगर (!new_qd)
		वापस -ENOMEM;

	spin_lock(&qd_lock);
	spin_lock_bucket(hash);
	*qdp = qd = gfs2_qd_search_bucket(hash, sdp, qid);
	अगर (qd == शून्य) अणु
		*qdp = new_qd;
		list_add(&new_qd->qd_list, &sdp->sd_quota_list);
		hlist_bl_add_head_rcu(&new_qd->qd_hlist, &qd_hash_table[hash]);
		atomic_inc(&sdp->sd_quota_count);
	पूर्ण
	spin_unlock_bucket(hash);
	spin_unlock(&qd_lock);

	अगर (qd) अणु
		gfs2_glock_put(new_qd->qd_gl);
		kmem_cache_मुक्त(gfs2_quotad_cachep, new_qd);
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम qd_hold(काष्ठा gfs2_quota_data *qd)
अणु
	काष्ठा gfs2_sbd *sdp = qd->qd_gl->gl_name.ln_sbd;
	gfs2_निश्चित(sdp, !__lockref_is_dead(&qd->qd_lockref));
	lockref_get(&qd->qd_lockref);
पूर्ण

अटल व्योम qd_put(काष्ठा gfs2_quota_data *qd)
अणु
	अगर (lockref_put_or_lock(&qd->qd_lockref))
		वापस;

	qd->qd_lockref.count = 0;
	list_lru_add(&gfs2_qd_lru, &qd->qd_lru);
	spin_unlock(&qd->qd_lockref.lock);

पूर्ण

अटल पूर्णांक slot_get(काष्ठा gfs2_quota_data *qd)
अणु
	काष्ठा gfs2_sbd *sdp = qd->qd_sbd;
	अचिन्हित पूर्णांक bit;
	पूर्णांक error = 0;

	spin_lock(&sdp->sd_biपंचांगap_lock);
	अगर (qd->qd_slot_count != 0)
		जाओ out;

	error = -ENOSPC;
	bit = find_first_zero_bit(sdp->sd_quota_biपंचांगap, sdp->sd_quota_slots);
	अगर (bit < sdp->sd_quota_slots) अणु
		set_bit(bit, sdp->sd_quota_biपंचांगap);
		qd->qd_slot = bit;
		error = 0;
out:
		qd->qd_slot_count++;
	पूर्ण
	spin_unlock(&sdp->sd_biपंचांगap_lock);

	वापस error;
पूर्ण

अटल व्योम slot_hold(काष्ठा gfs2_quota_data *qd)
अणु
	काष्ठा gfs2_sbd *sdp = qd->qd_sbd;

	spin_lock(&sdp->sd_biपंचांगap_lock);
	gfs2_निश्चित(sdp, qd->qd_slot_count);
	qd->qd_slot_count++;
	spin_unlock(&sdp->sd_biपंचांगap_lock);
पूर्ण

अटल व्योम slot_put(काष्ठा gfs2_quota_data *qd)
अणु
	काष्ठा gfs2_sbd *sdp = qd->qd_sbd;

	spin_lock(&sdp->sd_biपंचांगap_lock);
	gfs2_निश्चित(sdp, qd->qd_slot_count);
	अगर (!--qd->qd_slot_count) अणु
		BUG_ON(!test_and_clear_bit(qd->qd_slot, sdp->sd_quota_biपंचांगap));
		qd->qd_slot = -1;
	पूर्ण
	spin_unlock(&sdp->sd_biपंचांगap_lock);
पूर्ण

अटल पूर्णांक bh_get(काष्ठा gfs2_quota_data *qd)
अणु
	काष्ठा gfs2_sbd *sdp = qd->qd_gl->gl_name.ln_sbd;
	काष्ठा gfs2_inode *ip = GFS2_I(sdp->sd_qc_inode);
	अचिन्हित पूर्णांक block, offset;
	काष्ठा buffer_head *bh;
	पूर्णांक error;
	काष्ठा buffer_head bh_map = अणु .b_state = 0, .b_blocknr = 0 पूर्ण;

	mutex_lock(&sdp->sd_quota_mutex);

	अगर (qd->qd_bh_count++) अणु
		mutex_unlock(&sdp->sd_quota_mutex);
		वापस 0;
	पूर्ण

	block = qd->qd_slot / sdp->sd_qc_per_block;
	offset = qd->qd_slot % sdp->sd_qc_per_block;

	bh_map.b_size = BIT(ip->i_inode.i_blkbits);
	error = gfs2_block_map(&ip->i_inode, block, &bh_map, 0);
	अगर (error)
		जाओ fail;
	error = gfs2_meta_पढ़ो(ip->i_gl, bh_map.b_blocknr, DIO_WAIT, 0, &bh);
	अगर (error)
		जाओ fail;
	error = -EIO;
	अगर (gfs2_metatype_check(sdp, bh, GFS2_METATYPE_QC))
		जाओ fail_brअन्यथा;

	qd->qd_bh = bh;
	qd->qd_bh_qc = (काष्ठा gfs2_quota_change *)
		(bh->b_data + माप(काष्ठा gfs2_meta_header) +
		 offset * माप(काष्ठा gfs2_quota_change));

	mutex_unlock(&sdp->sd_quota_mutex);

	वापस 0;

fail_brअन्यथा:
	brअन्यथा(bh);
fail:
	qd->qd_bh_count--;
	mutex_unlock(&sdp->sd_quota_mutex);
	वापस error;
पूर्ण

अटल व्योम bh_put(काष्ठा gfs2_quota_data *qd)
अणु
	काष्ठा gfs2_sbd *sdp = qd->qd_gl->gl_name.ln_sbd;

	mutex_lock(&sdp->sd_quota_mutex);
	gfs2_निश्चित(sdp, qd->qd_bh_count);
	अगर (!--qd->qd_bh_count) अणु
		brअन्यथा(qd->qd_bh);
		qd->qd_bh = शून्य;
		qd->qd_bh_qc = शून्य;
	पूर्ण
	mutex_unlock(&sdp->sd_quota_mutex);
पूर्ण

अटल पूर्णांक qd_check_sync(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_quota_data *qd,
			 u64 *sync_gen)
अणु
	अगर (test_bit(QDF_LOCKED, &qd->qd_flags) ||
	    !test_bit(QDF_CHANGE, &qd->qd_flags) ||
	    (sync_gen && (qd->qd_sync_gen >= *sync_gen)))
		वापस 0;

	अगर (!lockref_get_not_dead(&qd->qd_lockref))
		वापस 0;

	list_move_tail(&qd->qd_list, &sdp->sd_quota_list);
	set_bit(QDF_LOCKED, &qd->qd_flags);
	qd->qd_change_sync = qd->qd_change;
	slot_hold(qd);
	वापस 1;
पूर्ण

अटल पूर्णांक qd_fish(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_quota_data **qdp)
अणु
	काष्ठा gfs2_quota_data *qd = शून्य;
	पूर्णांक error;
	पूर्णांक found = 0;

	*qdp = शून्य;

	अगर (sb_rकरोnly(sdp->sd_vfs))
		वापस 0;

	spin_lock(&qd_lock);

	list_क्रम_each_entry(qd, &sdp->sd_quota_list, qd_list) अणु
		found = qd_check_sync(sdp, qd, &sdp->sd_quota_sync_gen);
		अगर (found)
			अवरोध;
	पूर्ण

	अगर (!found)
		qd = शून्य;

	spin_unlock(&qd_lock);

	अगर (qd) अणु
		gfs2_निश्चित_warn(sdp, qd->qd_change_sync);
		error = bh_get(qd);
		अगर (error) अणु
			clear_bit(QDF_LOCKED, &qd->qd_flags);
			slot_put(qd);
			qd_put(qd);
			वापस error;
		पूर्ण
	पूर्ण

	*qdp = qd;

	वापस 0;
पूर्ण

अटल व्योम qd_unlock(काष्ठा gfs2_quota_data *qd)
अणु
	gfs2_निश्चित_warn(qd->qd_gl->gl_name.ln_sbd,
			 test_bit(QDF_LOCKED, &qd->qd_flags));
	clear_bit(QDF_LOCKED, &qd->qd_flags);
	bh_put(qd);
	slot_put(qd);
	qd_put(qd);
पूर्ण

अटल पूर्णांक qdsb_get(काष्ठा gfs2_sbd *sdp, काष्ठा kqid qid,
		    काष्ठा gfs2_quota_data **qdp)
अणु
	पूर्णांक error;

	error = qd_get(sdp, qid, qdp);
	अगर (error)
		वापस error;

	error = slot_get(*qdp);
	अगर (error)
		जाओ fail;

	error = bh_get(*qdp);
	अगर (error)
		जाओ fail_slot;

	वापस 0;

fail_slot:
	slot_put(*qdp);
fail:
	qd_put(*qdp);
	वापस error;
पूर्ण

अटल व्योम qdsb_put(काष्ठा gfs2_quota_data *qd)
अणु
	bh_put(qd);
	slot_put(qd);
	qd_put(qd);
पूर्ण

/**
 * gfs2_qa_get - make sure we have a quota allocations data काष्ठाure,
 *               अगर necessary
 * @ip: the inode क्रम this reservation
 */
पूर्णांक gfs2_qa_get(काष्ठा gfs2_inode *ip)
अणु
	पूर्णांक error = 0;
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);

	अगर (sdp->sd_args.ar_quota == GFS2_QUOTA_OFF)
		वापस 0;

	करोwn_ग_लिखो(&ip->i_rw_mutex);
	अगर (ip->i_qadata == शून्य) अणु
		ip->i_qadata = kmem_cache_zalloc(gfs2_qadata_cachep, GFP_NOFS);
		अगर (!ip->i_qadata) अणु
			error = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण
	ip->i_qadata->qa_ref++;
out:
	up_ग_लिखो(&ip->i_rw_mutex);
	वापस error;
पूर्ण

व्योम gfs2_qa_put(काष्ठा gfs2_inode *ip)
अणु
	करोwn_ग_लिखो(&ip->i_rw_mutex);
	अगर (ip->i_qadata && --ip->i_qadata->qa_ref == 0) अणु
		kmem_cache_मुक्त(gfs2_qadata_cachep, ip->i_qadata);
		ip->i_qadata = शून्य;
	पूर्ण
	up_ग_लिखो(&ip->i_rw_mutex);
पूर्ण

पूर्णांक gfs2_quota_hold(काष्ठा gfs2_inode *ip, kuid_t uid, kgid_t gid)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_quota_data **qd;
	पूर्णांक error;

	अगर (sdp->sd_args.ar_quota == GFS2_QUOTA_OFF)
		वापस 0;

	error = gfs2_qa_get(ip);
	अगर (error)
		वापस error;

	qd = ip->i_qadata->qa_qd;

	अगर (gfs2_निश्चित_warn(sdp, !ip->i_qadata->qa_qd_num) ||
	    gfs2_निश्चित_warn(sdp, !test_bit(GIF_QD_LOCKED, &ip->i_flags))) अणु
		error = -EIO;
		जाओ out;
	पूर्ण

	error = qdsb_get(sdp, make_kqid_uid(ip->i_inode.i_uid), qd);
	अगर (error)
		जाओ out_unhold;
	ip->i_qadata->qa_qd_num++;
	qd++;

	error = qdsb_get(sdp, make_kqid_gid(ip->i_inode.i_gid), qd);
	अगर (error)
		जाओ out_unhold;
	ip->i_qadata->qa_qd_num++;
	qd++;

	अगर (!uid_eq(uid, NO_UID_QUOTA_CHANGE) &&
	    !uid_eq(uid, ip->i_inode.i_uid)) अणु
		error = qdsb_get(sdp, make_kqid_uid(uid), qd);
		अगर (error)
			जाओ out_unhold;
		ip->i_qadata->qa_qd_num++;
		qd++;
	पूर्ण

	अगर (!gid_eq(gid, NO_GID_QUOTA_CHANGE) &&
	    !gid_eq(gid, ip->i_inode.i_gid)) अणु
		error = qdsb_get(sdp, make_kqid_gid(gid), qd);
		अगर (error)
			जाओ out_unhold;
		ip->i_qadata->qa_qd_num++;
		qd++;
	पूर्ण

out_unhold:
	अगर (error)
		gfs2_quota_unhold(ip);
out:
	वापस error;
पूर्ण

व्योम gfs2_quota_unhold(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	u32 x;

	अगर (ip->i_qadata == शून्य)
		वापस;

	gfs2_निश्चित_warn(sdp, !test_bit(GIF_QD_LOCKED, &ip->i_flags));

	क्रम (x = 0; x < ip->i_qadata->qa_qd_num; x++) अणु
		qdsb_put(ip->i_qadata->qa_qd[x]);
		ip->i_qadata->qa_qd[x] = शून्य;
	पूर्ण
	ip->i_qadata->qa_qd_num = 0;
	gfs2_qa_put(ip);
पूर्ण

अटल पूर्णांक sort_qd(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा gfs2_quota_data *qd_a = *(स्थिर काष्ठा gfs2_quota_data **)a;
	स्थिर काष्ठा gfs2_quota_data *qd_b = *(स्थिर काष्ठा gfs2_quota_data **)b;

	अगर (qid_lt(qd_a->qd_id, qd_b->qd_id))
		वापस -1;
	अगर (qid_lt(qd_b->qd_id, qd_a->qd_id))
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम करो_qc(काष्ठा gfs2_quota_data *qd, s64 change)
अणु
	काष्ठा gfs2_sbd *sdp = qd->qd_gl->gl_name.ln_sbd;
	काष्ठा gfs2_inode *ip = GFS2_I(sdp->sd_qc_inode);
	काष्ठा gfs2_quota_change *qc = qd->qd_bh_qc;
	s64 x;

	mutex_lock(&sdp->sd_quota_mutex);
	gfs2_trans_add_meta(ip->i_gl, qd->qd_bh);

	अगर (!test_bit(QDF_CHANGE, &qd->qd_flags)) अणु
		qc->qc_change = 0;
		qc->qc_flags = 0;
		अगर (qd->qd_id.type == USRQUOTA)
			qc->qc_flags = cpu_to_be32(GFS2_QCF_USER);
		qc->qc_id = cpu_to_be32(from_kqid(&init_user_ns, qd->qd_id));
	पूर्ण

	x = be64_to_cpu(qc->qc_change) + change;
	qc->qc_change = cpu_to_be64(x);

	spin_lock(&qd_lock);
	qd->qd_change = x;
	spin_unlock(&qd_lock);

	अगर (!x) अणु
		gfs2_निश्चित_warn(sdp, test_bit(QDF_CHANGE, &qd->qd_flags));
		clear_bit(QDF_CHANGE, &qd->qd_flags);
		qc->qc_flags = 0;
		qc->qc_id = 0;
		slot_put(qd);
		qd_put(qd);
	पूर्ण अन्यथा अगर (!test_and_set_bit(QDF_CHANGE, &qd->qd_flags)) अणु
		qd_hold(qd);
		slot_hold(qd);
	पूर्ण

	अगर (change < 0) /* Reset quiet flag अगर we मुक्तd some blocks */
		clear_bit(QDF_QMSG_QUIET, &qd->qd_flags);
	mutex_unlock(&sdp->sd_quota_mutex);
पूर्ण

अटल पूर्णांक gfs2_ग_लिखो_buf_to_page(काष्ठा gfs2_inode *ip, अचिन्हित दीर्घ index,
				  अचिन्हित off, व्योम *buf, अचिन्हित bytes)
अणु
	काष्ठा inode *inode = &ip->i_inode;
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा page *page;
	काष्ठा buffer_head *bh;
	व्योम *kaddr;
	u64 blk;
	अचिन्हित bsize = sdp->sd_sb.sb_bsize, bnum = 0, boff = 0;
	अचिन्हित to_ग_लिखो = bytes, pg_off = off;
	पूर्णांक करोne = 0;

	blk = index << (PAGE_SHIFT - sdp->sd_sb.sb_bsize_shअगरt);
	boff = off % bsize;

	page = find_or_create_page(mapping, index, GFP_NOFS);
	अगर (!page)
		वापस -ENOMEM;
	अगर (!page_has_buffers(page))
		create_empty_buffers(page, bsize, 0);

	bh = page_buffers(page);
	जबतक (!करोne) अणु
		/* Find the beginning block within the page */
		अगर (pg_off >= ((bnum * bsize) + bsize)) अणु
			bh = bh->b_this_page;
			bnum++;
			blk++;
			जारी;
		पूर्ण
		अगर (!buffer_mapped(bh)) अणु
			gfs2_block_map(inode, blk, bh, 1);
			अगर (!buffer_mapped(bh))
				जाओ unlock_out;
			/* If it's a newly allocated disk block, zero it */
			अगर (buffer_new(bh))
				zero_user(page, bnum * bsize, bh->b_size);
		पूर्ण
		अगर (PageUptodate(page))
			set_buffer_uptodate(bh);
		अगर (!buffer_uptodate(bh)) अणु
			ll_rw_block(REQ_OP_READ, REQ_META | REQ_PRIO, 1, &bh);
			रुको_on_buffer(bh);
			अगर (!buffer_uptodate(bh))
				जाओ unlock_out;
		पूर्ण
		अगर (gfs2_is_jdata(ip))
			gfs2_trans_add_data(ip->i_gl, bh);
		अन्यथा
			gfs2_ordered_add_inode(ip);

		/* If we need to ग_लिखो to the next block as well */
		अगर (to_ग_लिखो > (bsize - boff)) अणु
			pg_off += (bsize - boff);
			to_ग_लिखो -= (bsize - boff);
			boff = pg_off % bsize;
			जारी;
		पूर्ण
		करोne = 1;
	पूर्ण

	/* Write to the page, now that we have setup the buffer(s) */
	kaddr = kmap_atomic(page);
	स_नकल(kaddr + off, buf, bytes);
	flush_dcache_page(page);
	kunmap_atomic(kaddr);
	unlock_page(page);
	put_page(page);

	वापस 0;

unlock_out:
	unlock_page(page);
	put_page(page);
	वापस -EIO;
पूर्ण

अटल पूर्णांक gfs2_ग_लिखो_disk_quota(काष्ठा gfs2_inode *ip, काष्ठा gfs2_quota *qp,
				 loff_t loc)
अणु
	अचिन्हित दीर्घ pg_beg;
	अचिन्हित pg_off, nbytes, overflow = 0;
	पूर्णांक pg_oflow = 0, error;
	व्योम *ptr;

	nbytes = माप(काष्ठा gfs2_quota);

	pg_beg = loc >> PAGE_SHIFT;
	pg_off = offset_in_page(loc);

	/* If the quota straddles a page boundary, split the ग_लिखो in two */
	अगर ((pg_off + nbytes) > PAGE_SIZE) अणु
		pg_oflow = 1;
		overflow = (pg_off + nbytes) - PAGE_SIZE;
	पूर्ण

	ptr = qp;
	error = gfs2_ग_लिखो_buf_to_page(ip, pg_beg, pg_off, ptr,
				       nbytes - overflow);
	/* If there's an overflow, ग_लिखो the reमुख्यing bytes to the next page */
	अगर (!error && pg_oflow)
		error = gfs2_ग_लिखो_buf_to_page(ip, pg_beg + 1, 0,
					       ptr + nbytes - overflow,
					       overflow);
	वापस error;
पूर्ण

/**
 * gfs2_adjust_quota - adjust record of current block usage
 * @ip: The quota inode
 * @loc: Offset of the entry in the quota file
 * @change: The amount of usage change to record
 * @qd: The quota data
 * @fdq: The updated limits to record
 *
 * This function was mostly borrowed from gfs2_block_truncate_page which was
 * in turn mostly borrowed from ext3
 *
 * Returns: 0 or -ve on error
 */

अटल पूर्णांक gfs2_adjust_quota(काष्ठा gfs2_inode *ip, loff_t loc,
			     s64 change, काष्ठा gfs2_quota_data *qd,
			     काष्ठा qc_dqblk *fdq)
अणु
	काष्ठा inode *inode = &ip->i_inode;
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा gfs2_quota q;
	पूर्णांक err;
	u64 size;

	अगर (gfs2_is_stuffed(ip)) अणु
		err = gfs2_unstuff_dinode(ip, शून्य);
		अगर (err)
			वापस err;
	पूर्ण

	स_रखो(&q, 0, माप(काष्ठा gfs2_quota));
	err = gfs2_पूर्णांकernal_पढ़ो(ip, (अक्षर *)&q, &loc, माप(q));
	अगर (err < 0)
		वापस err;

	loc -= माप(q); /* gfs2_पूर्णांकernal_पढ़ो would've advanced the loc ptr */
	err = -EIO;
	be64_add_cpu(&q.qu_value, change);
	अगर (((s64)be64_to_cpu(q.qu_value)) < 0)
		q.qu_value = 0; /* Never go negative on quota usage */
	qd->qd_qb.qb_value = q.qu_value;
	अगर (fdq) अणु
		अगर (fdq->d_fieldmask & QC_SPC_SOFT) अणु
			q.qu_warn = cpu_to_be64(fdq->d_spc_softlimit >> sdp->sd_sb.sb_bsize_shअगरt);
			qd->qd_qb.qb_warn = q.qu_warn;
		पूर्ण
		अगर (fdq->d_fieldmask & QC_SPC_HARD) अणु
			q.qu_limit = cpu_to_be64(fdq->d_spc_hardlimit >> sdp->sd_sb.sb_bsize_shअगरt);
			qd->qd_qb.qb_limit = q.qu_limit;
		पूर्ण
		अगर (fdq->d_fieldmask & QC_SPACE) अणु
			q.qu_value = cpu_to_be64(fdq->d_space >> sdp->sd_sb.sb_bsize_shअगरt);
			qd->qd_qb.qb_value = q.qu_value;
		पूर्ण
	पूर्ण

	err = gfs2_ग_लिखो_disk_quota(ip, &q, loc);
	अगर (!err) अणु
		size = loc + माप(काष्ठा gfs2_quota);
		अगर (size > inode->i_size)
			i_size_ग_लिखो(inode, size);
		inode->i_mसमय = inode->i_aसमय = current_समय(inode);
		mark_inode_dirty(inode);
		set_bit(QDF_REFRESH, &qd->qd_flags);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक करो_sync(अचिन्हित पूर्णांक num_qd, काष्ठा gfs2_quota_data **qda)
अणु
	काष्ठा gfs2_sbd *sdp = (*qda)->qd_gl->gl_name.ln_sbd;
	काष्ठा gfs2_inode *ip = GFS2_I(sdp->sd_quota_inode);
	काष्ठा gfs2_alloc_parms ap = अणु .aflags = 0, पूर्ण;
	अचिन्हित पूर्णांक data_blocks, ind_blocks;
	काष्ठा gfs2_holder *ghs, i_gh;
	अचिन्हित पूर्णांक qx, x;
	काष्ठा gfs2_quota_data *qd;
	अचिन्हित reserved;
	loff_t offset;
	अचिन्हित पूर्णांक nalloc = 0, blocks;
	पूर्णांक error;

	error = gfs2_qa_get(ip);
	अगर (error)
		वापस error;

	gfs2_ग_लिखो_calc_reserv(ip, माप(काष्ठा gfs2_quota),
			      &data_blocks, &ind_blocks);

	ghs = kदो_स्मृति_array(num_qd, माप(काष्ठा gfs2_holder), GFP_NOFS);
	अगर (!ghs) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	sort(qda, num_qd, माप(काष्ठा gfs2_quota_data *), sort_qd, शून्य);
	inode_lock(&ip->i_inode);
	क्रम (qx = 0; qx < num_qd; qx++) अणु
		error = gfs2_glock_nq_init(qda[qx]->qd_gl, LM_ST_EXCLUSIVE,
					   GL_NOCACHE, &ghs[qx]);
		अगर (error)
			जाओ out_dq;
	पूर्ण

	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &i_gh);
	अगर (error)
		जाओ out_dq;

	क्रम (x = 0; x < num_qd; x++) अणु
		offset = qd2offset(qda[x]);
		अगर (gfs2_ग_लिखो_alloc_required(ip, offset,
					      माप(काष्ठा gfs2_quota)))
			nalloc++;
	पूर्ण

	/* 
	 * 1 blk क्रम unstuffing inode अगर stuffed. We add this extra
	 * block to the reservation unconditionally. If the inode
	 * करोesn't need unstuffing, the block will be released to the 
	 * rgrp since it won't be allocated during the transaction
	 */
	/* +3 in the end क्रम unstuffing block, inode size update block
	 * and another block in हाल quota straddles page boundary and 
	 * two blocks need to be updated instead of 1 */
	blocks = num_qd * data_blocks + RES_DINODE + num_qd + 3;

	reserved = 1 + (nalloc * (data_blocks + ind_blocks));
	ap.target = reserved;
	error = gfs2_inplace_reserve(ip, &ap);
	अगर (error)
		जाओ out_alloc;

	अगर (nalloc)
		blocks += gfs2_rg_blocks(ip, reserved) + nalloc * ind_blocks + RES_STATFS;

	error = gfs2_trans_begin(sdp, blocks, 0);
	अगर (error)
		जाओ out_ipres;

	क्रम (x = 0; x < num_qd; x++) अणु
		qd = qda[x];
		offset = qd2offset(qd);
		error = gfs2_adjust_quota(ip, offset, qd->qd_change_sync, qd, शून्य);
		अगर (error)
			जाओ out_end_trans;

		करो_qc(qd, -qd->qd_change_sync);
		set_bit(QDF_REFRESH, &qd->qd_flags);
	पूर्ण

	error = 0;

out_end_trans:
	gfs2_trans_end(sdp);
out_ipres:
	gfs2_inplace_release(ip);
out_alloc:
	gfs2_glock_dq_uninit(&i_gh);
out_dq:
	जबतक (qx--)
		gfs2_glock_dq_uninit(&ghs[qx]);
	inode_unlock(&ip->i_inode);
	kमुक्त(ghs);
	gfs2_log_flush(ip->i_gl->gl_name.ln_sbd, ip->i_gl,
		       GFS2_LOG_HEAD_FLUSH_NORMAL | GFS2_LFC_DO_SYNC);
out:
	gfs2_qa_put(ip);
	वापस error;
पूर्ण

अटल पूर्णांक update_qd(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_quota_data *qd)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(sdp->sd_quota_inode);
	काष्ठा gfs2_quota q;
	काष्ठा gfs2_quota_lvb *qlvb;
	loff_t pos;
	पूर्णांक error;

	स_रखो(&q, 0, माप(काष्ठा gfs2_quota));
	pos = qd2offset(qd);
	error = gfs2_पूर्णांकernal_पढ़ो(ip, (अक्षर *)&q, &pos, माप(q));
	अगर (error < 0)
		वापस error;

	qlvb = (काष्ठा gfs2_quota_lvb *)qd->qd_gl->gl_lksb.sb_lvbptr;
	qlvb->qb_magic = cpu_to_be32(GFS2_MAGIC);
	qlvb->__pad = 0;
	qlvb->qb_limit = q.qu_limit;
	qlvb->qb_warn = q.qu_warn;
	qlvb->qb_value = q.qu_value;
	qd->qd_qb = *qlvb;

	वापस 0;
पूर्ण

अटल पूर्णांक करो_glock(काष्ठा gfs2_quota_data *qd, पूर्णांक क्रमce_refresh,
		    काष्ठा gfs2_holder *q_gh)
अणु
	काष्ठा gfs2_sbd *sdp = qd->qd_gl->gl_name.ln_sbd;
	काष्ठा gfs2_inode *ip = GFS2_I(sdp->sd_quota_inode);
	काष्ठा gfs2_holder i_gh;
	पूर्णांक error;

restart:
	error = gfs2_glock_nq_init(qd->qd_gl, LM_ST_SHARED, 0, q_gh);
	अगर (error)
		वापस error;

	अगर (test_and_clear_bit(QDF_REFRESH, &qd->qd_flags))
		क्रमce_refresh = FORCE;

	qd->qd_qb = *(काष्ठा gfs2_quota_lvb *)qd->qd_gl->gl_lksb.sb_lvbptr;

	अगर (क्रमce_refresh || qd->qd_qb.qb_magic != cpu_to_be32(GFS2_MAGIC)) अणु
		gfs2_glock_dq_uninit(q_gh);
		error = gfs2_glock_nq_init(qd->qd_gl, LM_ST_EXCLUSIVE,
					   GL_NOCACHE, q_gh);
		अगर (error)
			वापस error;

		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, 0, &i_gh);
		अगर (error)
			जाओ fail;

		error = update_qd(sdp, qd);
		अगर (error)
			जाओ fail_gunlock;

		gfs2_glock_dq_uninit(&i_gh);
		gfs2_glock_dq_uninit(q_gh);
		क्रमce_refresh = 0;
		जाओ restart;
	पूर्ण

	वापस 0;

fail_gunlock:
	gfs2_glock_dq_uninit(&i_gh);
fail:
	gfs2_glock_dq_uninit(q_gh);
	वापस error;
पूर्ण

पूर्णांक gfs2_quota_lock(काष्ठा gfs2_inode *ip, kuid_t uid, kgid_t gid)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_quota_data *qd;
	u32 x;
	पूर्णांक error = 0;

	अगर (sdp->sd_args.ar_quota != GFS2_QUOTA_ON)
		वापस 0;

	error = gfs2_quota_hold(ip, uid, gid);
	अगर (error)
		वापस error;

	sort(ip->i_qadata->qa_qd, ip->i_qadata->qa_qd_num,
	     माप(काष्ठा gfs2_quota_data *), sort_qd, शून्य);

	क्रम (x = 0; x < ip->i_qadata->qa_qd_num; x++) अणु
		qd = ip->i_qadata->qa_qd[x];
		error = करो_glock(qd, NO_FORCE, &ip->i_qadata->qa_qd_ghs[x]);
		अगर (error)
			अवरोध;
	पूर्ण

	अगर (!error)
		set_bit(GIF_QD_LOCKED, &ip->i_flags);
	अन्यथा अणु
		जबतक (x--)
			gfs2_glock_dq_uninit(&ip->i_qadata->qa_qd_ghs[x]);
		gfs2_quota_unhold(ip);
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक need_sync(काष्ठा gfs2_quota_data *qd)
अणु
	काष्ठा gfs2_sbd *sdp = qd->qd_gl->gl_name.ln_sbd;
	काष्ठा gfs2_tune *gt = &sdp->sd_tune;
	s64 value;
	अचिन्हित पूर्णांक num, den;
	पूर्णांक करो_sync = 1;

	अगर (!qd->qd_qb.qb_limit)
		वापस 0;

	spin_lock(&qd_lock);
	value = qd->qd_change;
	spin_unlock(&qd_lock);

	spin_lock(&gt->gt_spin);
	num = gt->gt_quota_scale_num;
	den = gt->gt_quota_scale_den;
	spin_unlock(&gt->gt_spin);

	अगर (value < 0)
		करो_sync = 0;
	अन्यथा अगर ((s64)be64_to_cpu(qd->qd_qb.qb_value) >=
		 (s64)be64_to_cpu(qd->qd_qb.qb_limit))
		करो_sync = 0;
	अन्यथा अणु
		value *= gfs2_jindex_size(sdp) * num;
		value = भाग_s64(value, den);
		value += (s64)be64_to_cpu(qd->qd_qb.qb_value);
		अगर (value < (s64)be64_to_cpu(qd->qd_qb.qb_limit))
			करो_sync = 0;
	पूर्ण

	वापस करो_sync;
पूर्ण

व्योम gfs2_quota_unlock(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_quota_data *qda[4];
	अचिन्हित पूर्णांक count = 0;
	u32 x;
	पूर्णांक found;

	अगर (!test_and_clear_bit(GIF_QD_LOCKED, &ip->i_flags))
		वापस;

	क्रम (x = 0; x < ip->i_qadata->qa_qd_num; x++) अणु
		काष्ठा gfs2_quota_data *qd;
		पूर्णांक sync;

		qd = ip->i_qadata->qa_qd[x];
		sync = need_sync(qd);

		gfs2_glock_dq_uninit(&ip->i_qadata->qa_qd_ghs[x]);
		अगर (!sync)
			जारी;

		spin_lock(&qd_lock);
		found = qd_check_sync(sdp, qd, शून्य);
		spin_unlock(&qd_lock);

		अगर (!found)
			जारी;

		gfs2_निश्चित_warn(sdp, qd->qd_change_sync);
		अगर (bh_get(qd)) अणु
			clear_bit(QDF_LOCKED, &qd->qd_flags);
			slot_put(qd);
			qd_put(qd);
			जारी;
		पूर्ण

		qda[count++] = qd;
	पूर्ण

	अगर (count) अणु
		करो_sync(count, qda);
		क्रम (x = 0; x < count; x++)
			qd_unlock(qda[x]);
	पूर्ण

	gfs2_quota_unhold(ip);
पूर्ण

#घोषणा MAX_LINE 256

अटल पूर्णांक prपूर्णांक_message(काष्ठा gfs2_quota_data *qd, अक्षर *type)
अणु
	काष्ठा gfs2_sbd *sdp = qd->qd_gl->gl_name.ln_sbd;

	fs_info(sdp, "quota %s for %s %u\n",
		type,
		(qd->qd_id.type == USRQUOTA) ? "user" : "group",
		from_kqid(&init_user_ns, qd->qd_id));

	वापस 0;
पूर्ण

/**
 * gfs2_quota_check - check अगर allocating new blocks will exceed quota
 * @ip:  The inode क्रम which this check is being perक्रमmed
 * @uid: The uid to check against
 * @gid: The gid to check against
 * @ap:  The allocation parameters. ap->target contains the requested
 *       blocks. ap->min_target, अगर set, contains the minimum blks
 *       requested.
 *
 * Returns: 0 on success.
 *                  min_req = ap->min_target ? ap->min_target : ap->target;
 *                  quota must allow at least min_req blks क्रम success and
 *                  ap->allowed is set to the number of blocks allowed
 *
 *          -EDQUOT otherwise, quota violation. ap->allowed is set to number
 *                  of blocks available.
 */
पूर्णांक gfs2_quota_check(काष्ठा gfs2_inode *ip, kuid_t uid, kgid_t gid,
		     काष्ठा gfs2_alloc_parms *ap)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_quota_data *qd;
	s64 value, warn, limit;
	u32 x;
	पूर्णांक error = 0;

	ap->allowed = अच_पूर्णांक_उच्च; /* Assume we are permitted a whole lot */
	अगर (!test_bit(GIF_QD_LOCKED, &ip->i_flags))
		वापस 0;

	क्रम (x = 0; x < ip->i_qadata->qa_qd_num; x++) अणु
		qd = ip->i_qadata->qa_qd[x];

		अगर (!(qid_eq(qd->qd_id, make_kqid_uid(uid)) ||
		      qid_eq(qd->qd_id, make_kqid_gid(gid))))
			जारी;

		warn = (s64)be64_to_cpu(qd->qd_qb.qb_warn);
		limit = (s64)be64_to_cpu(qd->qd_qb.qb_limit);
		value = (s64)be64_to_cpu(qd->qd_qb.qb_value);
		spin_lock(&qd_lock);
		value += qd->qd_change;
		spin_unlock(&qd_lock);

		अगर (limit > 0 && (limit - value) < ap->allowed)
			ap->allowed = limit - value;
		/* If we can't meet the target */
		अगर (limit && limit < (value + (s64)ap->target)) अणु
			/* If no min_target specअगरied or we करोn't meet
			 * min_target, वापस -EDQUOT */
			अगर (!ap->min_target || ap->min_target > ap->allowed) अणु
				अगर (!test_and_set_bit(QDF_QMSG_QUIET,
						      &qd->qd_flags)) अणु
					prपूर्णांक_message(qd, "exceeded");
					quota_send_warning(qd->qd_id,
							   sdp->sd_vfs->s_dev,
							   QUOTA_NL_BHARDWARN);
				पूर्ण
				error = -EDQUOT;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (warn && warn < value &&
			   समय_after_eq(jअगरfies, qd->qd_last_warn +
					 gfs2_tune_get(sdp, gt_quota_warn_period)
					 * HZ)) अणु
			quota_send_warning(qd->qd_id,
					   sdp->sd_vfs->s_dev, QUOTA_NL_BSOFTWARN);
			error = prपूर्णांक_message(qd, "warning");
			qd->qd_last_warn = jअगरfies;
		पूर्ण
	पूर्ण
	वापस error;
पूर्ण

व्योम gfs2_quota_change(काष्ठा gfs2_inode *ip, s64 change,
		       kuid_t uid, kgid_t gid)
अणु
	काष्ठा gfs2_quota_data *qd;
	u32 x;
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);

	अगर (sdp->sd_args.ar_quota != GFS2_QUOTA_ON ||
	    gfs2_निश्चित_warn(sdp, change))
		वापस;
	अगर (ip->i_diskflags & GFS2_DIF_SYSTEM)
		वापस;

	अगर (gfs2_निश्चित_withdraw(sdp, ip->i_qadata &&
				 ip->i_qadata->qa_ref > 0))
		वापस;
	क्रम (x = 0; x < ip->i_qadata->qa_qd_num; x++) अणु
		qd = ip->i_qadata->qa_qd[x];

		अगर (qid_eq(qd->qd_id, make_kqid_uid(uid)) ||
		    qid_eq(qd->qd_id, make_kqid_gid(gid))) अणु
			करो_qc(qd, change);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक gfs2_quota_sync(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;
	काष्ठा gfs2_quota_data **qda;
	अचिन्हित पूर्णांक max_qd = PAGE_SIZE / माप(काष्ठा gfs2_holder);
	अचिन्हित पूर्णांक num_qd;
	अचिन्हित पूर्णांक x;
	पूर्णांक error = 0;

	qda = kसुस्मृति(max_qd, माप(काष्ठा gfs2_quota_data *), GFP_KERNEL);
	अगर (!qda)
		वापस -ENOMEM;

	mutex_lock(&sdp->sd_quota_sync_mutex);
	sdp->sd_quota_sync_gen++;

	करो अणु
		num_qd = 0;

		क्रम (;;) अणु
			error = qd_fish(sdp, qda + num_qd);
			अगर (error || !qda[num_qd])
				अवरोध;
			अगर (++num_qd == max_qd)
				अवरोध;
		पूर्ण

		अगर (num_qd) अणु
			अगर (!error)
				error = करो_sync(num_qd, qda);
			अगर (!error)
				क्रम (x = 0; x < num_qd; x++)
					qda[x]->qd_sync_gen =
						sdp->sd_quota_sync_gen;

			क्रम (x = 0; x < num_qd; x++)
				qd_unlock(qda[x]);
		पूर्ण
	पूर्ण जबतक (!error && num_qd == max_qd);

	mutex_unlock(&sdp->sd_quota_sync_mutex);
	kमुक्त(qda);

	वापस error;
पूर्ण

पूर्णांक gfs2_quota_refresh(काष्ठा gfs2_sbd *sdp, काष्ठा kqid qid)
अणु
	काष्ठा gfs2_quota_data *qd;
	काष्ठा gfs2_holder q_gh;
	पूर्णांक error;

	error = qd_get(sdp, qid, &qd);
	अगर (error)
		वापस error;

	error = करो_glock(qd, FORCE, &q_gh);
	अगर (!error)
		gfs2_glock_dq_uninit(&q_gh);

	qd_put(qd);
	वापस error;
पूर्ण

पूर्णांक gfs2_quota_init(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(sdp->sd_qc_inode);
	u64 size = i_size_पढ़ो(sdp->sd_qc_inode);
	अचिन्हित पूर्णांक blocks = size >> sdp->sd_sb.sb_bsize_shअगरt;
	अचिन्हित पूर्णांक x, slot = 0;
	अचिन्हित पूर्णांक found = 0;
	अचिन्हित पूर्णांक hash;
	अचिन्हित पूर्णांक bm_size;
	u64 dblock;
	u32 extlen = 0;
	पूर्णांक error;

	अगर (gfs2_check_पूर्णांकernal_file_size(sdp->sd_qc_inode, 1, 64 << 20))
		वापस -EIO;

	sdp->sd_quota_slots = blocks * sdp->sd_qc_per_block;
	bm_size = DIV_ROUND_UP(sdp->sd_quota_slots, 8 * माप(अचिन्हित दीर्घ));
	bm_size *= माप(अचिन्हित दीर्घ);
	error = -ENOMEM;
	sdp->sd_quota_biपंचांगap = kzalloc(bm_size, GFP_NOFS | __GFP_NOWARN);
	अगर (sdp->sd_quota_biपंचांगap == शून्य)
		sdp->sd_quota_biपंचांगap = __vदो_स्मृति(bm_size, GFP_NOFS |
						 __GFP_ZERO);
	अगर (!sdp->sd_quota_biपंचांगap)
		वापस error;

	क्रम (x = 0; x < blocks; x++) अणु
		काष्ठा buffer_head *bh;
		स्थिर काष्ठा gfs2_quota_change *qc;
		अचिन्हित पूर्णांक y;

		अगर (!extlen) अणु
			extlen = 32;
			error = gfs2_get_extent(&ip->i_inode, x, &dblock, &extlen);
			अगर (error)
				जाओ fail;
		पूर्ण
		error = -EIO;
		bh = gfs2_meta_ra(ip->i_gl, dblock, extlen);
		अगर (!bh)
			जाओ fail;
		अगर (gfs2_metatype_check(sdp, bh, GFS2_METATYPE_QC)) अणु
			brअन्यथा(bh);
			जाओ fail;
		पूर्ण

		qc = (स्थिर काष्ठा gfs2_quota_change *)(bh->b_data + माप(काष्ठा gfs2_meta_header));
		क्रम (y = 0; y < sdp->sd_qc_per_block && slot < sdp->sd_quota_slots;
		     y++, slot++) अणु
			काष्ठा gfs2_quota_data *qd;
			s64 qc_change = be64_to_cpu(qc->qc_change);
			u32 qc_flags = be32_to_cpu(qc->qc_flags);
			क्रमागत quota_type qtype = (qc_flags & GFS2_QCF_USER) ?
						USRQUOTA : GRPQUOTA;
			काष्ठा kqid qc_id = make_kqid(&init_user_ns, qtype,
						      be32_to_cpu(qc->qc_id));
			qc++;
			अगर (!qc_change)
				जारी;

			hash = gfs2_qd_hash(sdp, qc_id);
			qd = qd_alloc(hash, sdp, qc_id);
			अगर (qd == शून्य) अणु
				brअन्यथा(bh);
				जाओ fail;
			पूर्ण

			set_bit(QDF_CHANGE, &qd->qd_flags);
			qd->qd_change = qc_change;
			qd->qd_slot = slot;
			qd->qd_slot_count = 1;

			spin_lock(&qd_lock);
			BUG_ON(test_and_set_bit(slot, sdp->sd_quota_biपंचांगap));
			list_add(&qd->qd_list, &sdp->sd_quota_list);
			atomic_inc(&sdp->sd_quota_count);
			spin_unlock(&qd_lock);

			spin_lock_bucket(hash);
			hlist_bl_add_head_rcu(&qd->qd_hlist, &qd_hash_table[hash]);
			spin_unlock_bucket(hash);

			found++;
		पूर्ण

		brअन्यथा(bh);
		dblock++;
		extlen--;
	पूर्ण

	अगर (found)
		fs_info(sdp, "found %u quota changes\n", found);

	वापस 0;

fail:
	gfs2_quota_cleanup(sdp);
	वापस error;
पूर्ण

व्योम gfs2_quota_cleanup(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा list_head *head = &sdp->sd_quota_list;
	काष्ठा gfs2_quota_data *qd;

	spin_lock(&qd_lock);
	जबतक (!list_empty(head)) अणु
		qd = list_last_entry(head, काष्ठा gfs2_quota_data, qd_list);

		list_del(&qd->qd_list);

		/* Also हटाओ अगर this qd exists in the reclaim list */
		list_lru_del(&gfs2_qd_lru, &qd->qd_lru);
		atomic_dec(&sdp->sd_quota_count);
		spin_unlock(&qd_lock);

		spin_lock_bucket(qd->qd_hash);
		hlist_bl_del_rcu(&qd->qd_hlist);
		spin_unlock_bucket(qd->qd_hash);

		gfs2_निश्चित_warn(sdp, !qd->qd_change);
		gfs2_निश्चित_warn(sdp, !qd->qd_slot_count);
		gfs2_निश्चित_warn(sdp, !qd->qd_bh_count);

		gfs2_glock_put(qd->qd_gl);
		call_rcu(&qd->qd_rcu, gfs2_qd_dealloc);

		spin_lock(&qd_lock);
	पूर्ण
	spin_unlock(&qd_lock);

	gfs2_निश्चित_warn(sdp, !atomic_पढ़ो(&sdp->sd_quota_count));

	kvमुक्त(sdp->sd_quota_biपंचांगap);
	sdp->sd_quota_biपंचांगap = शून्य;
पूर्ण

अटल व्योम quotad_error(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *msg, पूर्णांक error)
अणु
	अगर (error == 0 || error == -EROFS)
		वापस;
	अगर (!gfs2_withdrawn(sdp)) अणु
		अगर (!cmpxchg(&sdp->sd_log_error, 0, error))
			fs_err(sdp, "gfs2_quotad: %s error %d\n", msg, error);
		wake_up(&sdp->sd_logd_रुकोq);
	पूर्ण
पूर्ण

अटल व्योम quotad_check_समयo(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *msg,
			       पूर्णांक (*fxn)(काष्ठा super_block *sb, पूर्णांक type),
			       अचिन्हित दीर्घ t, अचिन्हित दीर्घ *समयo,
			       अचिन्हित पूर्णांक *new_समयo)
अणु
	अगर (t >= *समयo) अणु
		पूर्णांक error = fxn(sdp->sd_vfs, 0);
		quotad_error(sdp, msg, error);
		*समयo = gfs2_tune_get_i(&sdp->sd_tune, new_समयo) * HZ;
	पूर्ण अन्यथा अणु
		*समयo -= t;
	पूर्ण
पूर्ण

अटल व्योम quotad_check_trunc_list(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_inode *ip;

	जबतक(1) अणु
		ip = शून्य;
		spin_lock(&sdp->sd_trunc_lock);
		अगर (!list_empty(&sdp->sd_trunc_list)) अणु
			ip = list_first_entry(&sdp->sd_trunc_list,
					काष्ठा gfs2_inode, i_trunc_list);
			list_del_init(&ip->i_trunc_list);
		पूर्ण
		spin_unlock(&sdp->sd_trunc_lock);
		अगर (ip == शून्य)
			वापस;
		gfs2_glock_finish_truncate(ip);
	पूर्ण
पूर्ण

व्योम gfs2_wake_up_statfs(काष्ठा gfs2_sbd *sdp) अणु
	अगर (!sdp->sd_statfs_क्रमce_sync) अणु
		sdp->sd_statfs_क्रमce_sync = 1;
		wake_up(&sdp->sd_quota_रुको);
	पूर्ण
पूर्ण


/**
 * gfs2_quotad - Write cached quota changes पूर्णांकo the quota file
 * @data: Poपूर्णांकer to GFS2 superblock
 *
 */

पूर्णांक gfs2_quotad(व्योम *data)
अणु
	काष्ठा gfs2_sbd *sdp = data;
	काष्ठा gfs2_tune *tune = &sdp->sd_tune;
	अचिन्हित दीर्घ statfs_समयo = 0;
	अचिन्हित दीर्घ quotad_समयo = 0;
	अचिन्हित दीर्घ t = 0;
	DEFINE_WAIT(रुको);
	पूर्णांक empty;

	जबतक (!kthपढ़ो_should_stop()) अणु

		अगर (gfs2_withdrawn(sdp))
			जाओ bypass;
		/* Update the master statfs file */
		अगर (sdp->sd_statfs_क्रमce_sync) अणु
			पूर्णांक error = gfs2_statfs_sync(sdp->sd_vfs, 0);
			quotad_error(sdp, "statfs", error);
			statfs_समयo = gfs2_tune_get(sdp, gt_statfs_quantum) * HZ;
		पूर्ण
		अन्यथा
			quotad_check_समयo(sdp, "statfs", gfs2_statfs_sync, t,
				   	   &statfs_समयo,
					   &tune->gt_statfs_quantum);

		/* Update quota file */
		quotad_check_समयo(sdp, "sync", gfs2_quota_sync, t,
				   &quotad_समयo, &tune->gt_quota_quantum);

		/* Check क्रम & recover partially truncated inodes */
		quotad_check_trunc_list(sdp);

		try_to_मुक्तze();

bypass:
		t = min(quotad_समयo, statfs_समयo);

		prepare_to_रुको(&sdp->sd_quota_रुको, &रुको, TASK_INTERRUPTIBLE);
		spin_lock(&sdp->sd_trunc_lock);
		empty = list_empty(&sdp->sd_trunc_list);
		spin_unlock(&sdp->sd_trunc_lock);
		अगर (empty && !sdp->sd_statfs_क्रमce_sync)
			t -= schedule_समयout(t);
		अन्यथा
			t = 0;
		finish_रुको(&sdp->sd_quota_रुको, &रुको);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gfs2_quota_get_state(काष्ठा super_block *sb, काष्ठा qc_state *state)
अणु
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;

	स_रखो(state, 0, माप(*state));

	चयन (sdp->sd_args.ar_quota) अणु
	हाल GFS2_QUOTA_ON:
		state->s_state[USRQUOTA].flags |= QCI_LIMITS_ENFORCED;
		state->s_state[GRPQUOTA].flags |= QCI_LIMITS_ENFORCED;
		fallthrough;
	हाल GFS2_QUOTA_ACCOUNT:
		state->s_state[USRQUOTA].flags |= QCI_ACCT_ENABLED |
						  QCI_SYSखाता;
		state->s_state[GRPQUOTA].flags |= QCI_ACCT_ENABLED |
						  QCI_SYSखाता;
		अवरोध;
	हाल GFS2_QUOTA_OFF:
		अवरोध;
	पूर्ण
	अगर (sdp->sd_quota_inode) अणु
		state->s_state[USRQUOTA].ino =
					GFS2_I(sdp->sd_quota_inode)->i_no_addr;
		state->s_state[USRQUOTA].blocks = sdp->sd_quota_inode->i_blocks;
	पूर्ण
	state->s_state[USRQUOTA].nextents = 1;	/* unsupported */
	state->s_state[GRPQUOTA] = state->s_state[USRQUOTA];
	state->s_incoredqs = list_lru_count(&gfs2_qd_lru);
	वापस 0;
पूर्ण

अटल पूर्णांक gfs2_get_dqblk(काष्ठा super_block *sb, काष्ठा kqid qid,
			  काष्ठा qc_dqblk *fdq)
अणु
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;
	काष्ठा gfs2_quota_lvb *qlvb;
	काष्ठा gfs2_quota_data *qd;
	काष्ठा gfs2_holder q_gh;
	पूर्णांक error;

	स_रखो(fdq, 0, माप(*fdq));

	अगर (sdp->sd_args.ar_quota == GFS2_QUOTA_OFF)
		वापस -ESRCH; /* Crazy XFS error code */

	अगर ((qid.type != USRQUOTA) &&
	    (qid.type != GRPQUOTA))
		वापस -EINVAL;

	error = qd_get(sdp, qid, &qd);
	अगर (error)
		वापस error;
	error = करो_glock(qd, FORCE, &q_gh);
	अगर (error)
		जाओ out;

	qlvb = (काष्ठा gfs2_quota_lvb *)qd->qd_gl->gl_lksb.sb_lvbptr;
	fdq->d_spc_hardlimit = be64_to_cpu(qlvb->qb_limit) << sdp->sd_sb.sb_bsize_shअगरt;
	fdq->d_spc_softlimit = be64_to_cpu(qlvb->qb_warn) << sdp->sd_sb.sb_bsize_shअगरt;
	fdq->d_space = be64_to_cpu(qlvb->qb_value) << sdp->sd_sb.sb_bsize_shअगरt;

	gfs2_glock_dq_uninit(&q_gh);
out:
	qd_put(qd);
	वापस error;
पूर्ण

/* GFS2 only supports a subset of the XFS fields */
#घोषणा GFS2_FIELDMASK (QC_SPC_SOFT|QC_SPC_HARD|QC_SPACE)

अटल पूर्णांक gfs2_set_dqblk(काष्ठा super_block *sb, काष्ठा kqid qid,
			  काष्ठा qc_dqblk *fdq)
अणु
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;
	काष्ठा gfs2_inode *ip = GFS2_I(sdp->sd_quota_inode);
	काष्ठा gfs2_quota_data *qd;
	काष्ठा gfs2_holder q_gh, i_gh;
	अचिन्हित पूर्णांक data_blocks, ind_blocks;
	अचिन्हित पूर्णांक blocks = 0;
	पूर्णांक alloc_required;
	loff_t offset;
	पूर्णांक error;

	अगर (sdp->sd_args.ar_quota == GFS2_QUOTA_OFF)
		वापस -ESRCH; /* Crazy XFS error code */

	अगर ((qid.type != USRQUOTA) &&
	    (qid.type != GRPQUOTA))
		वापस -EINVAL;

	अगर (fdq->d_fieldmask & ~GFS2_FIELDMASK)
		वापस -EINVAL;

	error = qd_get(sdp, qid, &qd);
	अगर (error)
		वापस error;

	error = gfs2_qa_get(ip);
	अगर (error)
		जाओ out_put;

	inode_lock(&ip->i_inode);
	error = gfs2_glock_nq_init(qd->qd_gl, LM_ST_EXCLUSIVE, 0, &q_gh);
	अगर (error)
		जाओ out_unlockput;
	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &i_gh);
	अगर (error)
		जाओ out_q;

	/* Check क्रम existing entry, अगर none then alloc new blocks */
	error = update_qd(sdp, qd);
	अगर (error)
		जाओ out_i;

	/* If nothing has changed, this is a no-op */
	अगर ((fdq->d_fieldmask & QC_SPC_SOFT) &&
	    ((fdq->d_spc_softlimit >> sdp->sd_sb.sb_bsize_shअगरt) == be64_to_cpu(qd->qd_qb.qb_warn)))
		fdq->d_fieldmask ^= QC_SPC_SOFT;

	अगर ((fdq->d_fieldmask & QC_SPC_HARD) &&
	    ((fdq->d_spc_hardlimit >> sdp->sd_sb.sb_bsize_shअगरt) == be64_to_cpu(qd->qd_qb.qb_limit)))
		fdq->d_fieldmask ^= QC_SPC_HARD;

	अगर ((fdq->d_fieldmask & QC_SPACE) &&
	    ((fdq->d_space >> sdp->sd_sb.sb_bsize_shअगरt) == be64_to_cpu(qd->qd_qb.qb_value)))
		fdq->d_fieldmask ^= QC_SPACE;

	अगर (fdq->d_fieldmask == 0)
		जाओ out_i;

	offset = qd2offset(qd);
	alloc_required = gfs2_ग_लिखो_alloc_required(ip, offset, माप(काष्ठा gfs2_quota));
	अगर (gfs2_is_stuffed(ip))
		alloc_required = 1;
	अगर (alloc_required) अणु
		काष्ठा gfs2_alloc_parms ap = अणु .aflags = 0, पूर्ण;
		gfs2_ग_लिखो_calc_reserv(ip, माप(काष्ठा gfs2_quota),
				       &data_blocks, &ind_blocks);
		blocks = 1 + data_blocks + ind_blocks;
		ap.target = blocks;
		error = gfs2_inplace_reserve(ip, &ap);
		अगर (error)
			जाओ out_i;
		blocks += gfs2_rg_blocks(ip, blocks);
	पूर्ण

	/* Some quotas span block boundaries and can update two blocks,
	   adding an extra block to the transaction to handle such quotas */
	error = gfs2_trans_begin(sdp, blocks + RES_DINODE + 2, 0);
	अगर (error)
		जाओ out_release;

	/* Apply changes */
	error = gfs2_adjust_quota(ip, offset, 0, qd, fdq);
	अगर (!error)
		clear_bit(QDF_QMSG_QUIET, &qd->qd_flags);

	gfs2_trans_end(sdp);
out_release:
	अगर (alloc_required)
		gfs2_inplace_release(ip);
out_i:
	gfs2_glock_dq_uninit(&i_gh);
out_q:
	gfs2_glock_dq_uninit(&q_gh);
out_unlockput:
	gfs2_qa_put(ip);
	inode_unlock(&ip->i_inode);
out_put:
	qd_put(qd);
	वापस error;
पूर्ण

स्थिर काष्ठा quotactl_ops gfs2_quotactl_ops = अणु
	.quota_sync     = gfs2_quota_sync,
	.get_state	= gfs2_quota_get_state,
	.get_dqblk	= gfs2_get_dqblk,
	.set_dqblk	= gfs2_set_dqblk,
पूर्ण;

व्योम __init gfs2_quota_hash_init(व्योम)
अणु
	अचिन्हित i;

	क्रम(i = 0; i < GFS2_QD_HASH_SIZE; i++)
		INIT_HLIST_BL_HEAD(&qd_hash_table[i]);
पूर्ण
