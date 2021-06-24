<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rculist_bl.h>
#समावेश <linux/atomic.h>
#समावेश <linux/mempool.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "super.h"
#समावेश "sys.h"
#समावेश "util.h"
#समावेश "glock.h"
#समावेश "quota.h"
#समावेश "recovery.h"
#समावेश "dir.h"
#समावेश "glops.h"

काष्ठा workqueue_काष्ठा *gfs2_control_wq;

अटल व्योम gfs2_init_inode_once(व्योम *foo)
अणु
	काष्ठा gfs2_inode *ip = foo;

	inode_init_once(&ip->i_inode);
	atomic_set(&ip->i_sizehपूर्णांक, 0);
	init_rwsem(&ip->i_rw_mutex);
	INIT_LIST_HEAD(&ip->i_trunc_list);
	INIT_LIST_HEAD(&ip->i_ordered);
	ip->i_qadata = शून्य;
	gfs2_holder_mark_uninitialized(&ip->i_rgd_gh);
	स_रखो(&ip->i_res, 0, माप(ip->i_res));
	RB_CLEAR_NODE(&ip->i_res.rs_node);
	ip->i_hash_cache = शून्य;
	gfs2_holder_mark_uninitialized(&ip->i_iखोलो_gh);
पूर्ण

अटल व्योम gfs2_init_glock_once(व्योम *foo)
अणु
	काष्ठा gfs2_glock *gl = foo;

	spin_lock_init(&gl->gl_lockref.lock);
	INIT_LIST_HEAD(&gl->gl_holders);
	INIT_LIST_HEAD(&gl->gl_lru);
	INIT_LIST_HEAD(&gl->gl_ail_list);
	atomic_set(&gl->gl_ail_count, 0);
	atomic_set(&gl->gl_revokes, 0);
पूर्ण

अटल व्योम gfs2_init_gl_aspace_once(व्योम *foo)
अणु
	काष्ठा gfs2_glock *gl = foo;
	काष्ठा address_space *mapping = (काष्ठा address_space *)(gl + 1);

	gfs2_init_glock_once(gl);
	address_space_init_once(mapping);
पूर्ण

/**
 * init_gfs2_fs - Register GFS2 as a fileप्रणाली
 *
 * Returns: 0 on success, error code on failure
 */

अटल पूर्णांक __init init_gfs2_fs(व्योम)
अणु
	पूर्णांक error;

	gfs2_str2qstr(&gfs2_qकरोt, ".");
	gfs2_str2qstr(&gfs2_qकरोtकरोt, "..");
	gfs2_quota_hash_init();

	error = gfs2_sys_init();
	अगर (error)
		वापस error;

	error = list_lru_init(&gfs2_qd_lru);
	अगर (error)
		जाओ fail_lru;

	error = gfs2_glock_init();
	अगर (error)
		जाओ fail_glock;

	error = -ENOMEM;
	gfs2_glock_cachep = kmem_cache_create("gfs2_glock",
					      माप(काष्ठा gfs2_glock),
					      0, SLAB_RECLAIM_ACCOUNT,
					      gfs2_init_glock_once);
	अगर (!gfs2_glock_cachep)
		जाओ fail_cachep1;

	gfs2_glock_aspace_cachep = kmem_cache_create("gfs2_glock(aspace)",
					माप(काष्ठा gfs2_glock) +
					माप(काष्ठा address_space),
					0, 0, gfs2_init_gl_aspace_once);

	अगर (!gfs2_glock_aspace_cachep)
		जाओ fail_cachep2;

	gfs2_inode_cachep = kmem_cache_create("gfs2_inode",
					      माप(काष्ठा gfs2_inode),
					      0,  SLAB_RECLAIM_ACCOUNT|
						  SLAB_MEM_SPREAD|
						  SLAB_ACCOUNT,
					      gfs2_init_inode_once);
	अगर (!gfs2_inode_cachep)
		जाओ fail_cachep3;

	gfs2_bufdata_cachep = kmem_cache_create("gfs2_bufdata",
						माप(काष्ठा gfs2_bufdata),
					        0, 0, शून्य);
	अगर (!gfs2_bufdata_cachep)
		जाओ fail_cachep4;

	gfs2_rgrpd_cachep = kmem_cache_create("gfs2_rgrpd",
					      माप(काष्ठा gfs2_rgrpd),
					      0, 0, शून्य);
	अगर (!gfs2_rgrpd_cachep)
		जाओ fail_cachep5;

	gfs2_quotad_cachep = kmem_cache_create("gfs2_quotad",
					       माप(काष्ठा gfs2_quota_data),
					       0, SLAB_RECLAIM_ACCOUNT, शून्य);
	अगर (!gfs2_quotad_cachep)
		जाओ fail_cachep6;

	gfs2_qadata_cachep = kmem_cache_create("gfs2_qadata",
					       माप(काष्ठा gfs2_qadata),
					       0, 0, शून्य);
	अगर (!gfs2_qadata_cachep)
		जाओ fail_cachep7;

	gfs2_trans_cachep = kmem_cache_create("gfs2_trans",
					       माप(काष्ठा gfs2_trans),
					       0, 0, शून्य);
	अगर (!gfs2_trans_cachep)
		जाओ fail_cachep8;

	error = रेजिस्टर_shrinker(&gfs2_qd_shrinker);
	अगर (error)
		जाओ fail_shrinker;

	error = रेजिस्टर_fileप्रणाली(&gfs2_fs_type);
	अगर (error)
		जाओ fail_fs1;

	error = रेजिस्टर_fileप्रणाली(&gfs2meta_fs_type);
	अगर (error)
		जाओ fail_fs2;

	error = -ENOMEM;
	gfs_recovery_wq = alloc_workqueue("gfs_recovery",
					  WQ_MEM_RECLAIM | WQ_FREEZABLE, 0);
	अगर (!gfs_recovery_wq)
		जाओ fail_wq1;

	gfs2_control_wq = alloc_workqueue("gfs2_control",
					  WQ_UNBOUND | WQ_FREEZABLE, 0);
	अगर (!gfs2_control_wq)
		जाओ fail_wq2;

	gfs2_मुक्तze_wq = alloc_workqueue("freeze_workqueue", 0, 0);

	अगर (!gfs2_मुक्तze_wq)
		जाओ fail_wq3;

	gfs2_page_pool = mempool_create_page_pool(64, 0);
	अगर (!gfs2_page_pool)
		जाओ fail_mempool;

	gfs2_रेजिस्टर_debugfs();

	pr_info("GFS2 installed\n");

	वापस 0;

fail_mempool:
	destroy_workqueue(gfs2_मुक्तze_wq);
fail_wq3:
	destroy_workqueue(gfs2_control_wq);
fail_wq2:
	destroy_workqueue(gfs_recovery_wq);
fail_wq1:
	unरेजिस्टर_fileप्रणाली(&gfs2meta_fs_type);
fail_fs2:
	unरेजिस्टर_fileप्रणाली(&gfs2_fs_type);
fail_fs1:
	unरेजिस्टर_shrinker(&gfs2_qd_shrinker);
fail_shrinker:
	kmem_cache_destroy(gfs2_trans_cachep);
fail_cachep8:
	kmem_cache_destroy(gfs2_qadata_cachep);
fail_cachep7:
	kmem_cache_destroy(gfs2_quotad_cachep);
fail_cachep6:
	kmem_cache_destroy(gfs2_rgrpd_cachep);
fail_cachep5:
	kmem_cache_destroy(gfs2_bufdata_cachep);
fail_cachep4:
	kmem_cache_destroy(gfs2_inode_cachep);
fail_cachep3:
	kmem_cache_destroy(gfs2_glock_aspace_cachep);
fail_cachep2:
	kmem_cache_destroy(gfs2_glock_cachep);
fail_cachep1:
	gfs2_glock_निकास();
fail_glock:
	list_lru_destroy(&gfs2_qd_lru);
fail_lru:
	gfs2_sys_uninit();
	वापस error;
पूर्ण

/**
 * निकास_gfs2_fs - Unरेजिस्टर the file प्रणाली
 *
 */

अटल व्योम __निकास निकास_gfs2_fs(व्योम)
अणु
	unरेजिस्टर_shrinker(&gfs2_qd_shrinker);
	gfs2_glock_निकास();
	gfs2_unरेजिस्टर_debugfs();
	unरेजिस्टर_fileप्रणाली(&gfs2_fs_type);
	unरेजिस्टर_fileप्रणाली(&gfs2meta_fs_type);
	destroy_workqueue(gfs_recovery_wq);
	destroy_workqueue(gfs2_control_wq);
	destroy_workqueue(gfs2_मुक्तze_wq);
	list_lru_destroy(&gfs2_qd_lru);

	rcu_barrier();

	mempool_destroy(gfs2_page_pool);
	kmem_cache_destroy(gfs2_trans_cachep);
	kmem_cache_destroy(gfs2_qadata_cachep);
	kmem_cache_destroy(gfs2_quotad_cachep);
	kmem_cache_destroy(gfs2_rgrpd_cachep);
	kmem_cache_destroy(gfs2_bufdata_cachep);
	kmem_cache_destroy(gfs2_inode_cachep);
	kmem_cache_destroy(gfs2_glock_aspace_cachep);
	kmem_cache_destroy(gfs2_glock_cachep);

	gfs2_sys_uninit();
पूर्ण

MODULE_DESCRIPTION("Global File System");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");

module_init(init_gfs2_fs);
module_निकास(निकास_gfs2_fs);

