<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 STRATO.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/btrfs.h>
#समावेश <linux/sched/mm.h>

#समावेश "ctree.h"
#समावेश "transaction.h"
#समावेश "disk-io.h"
#समावेश "locking.h"
#समावेश "ulist.h"
#समावेश "backref.h"
#समावेश "extent_io.h"
#समावेश "qgroup.h"
#समावेश "block-group.h"
#समावेश "sysfs.h"
#समावेश "tree-mod-log.h"

/* TODO XXX FIXME
 *  - subvol delete -> delete when ref goes to 0? delete limits also?
 *  - reorganize keys
 *  - compressed
 *  - sync
 *  - copy also limits on subvol creation
 *  - limit
 *  - caches क्रम ulists
 *  - perक्रमmance benchmarks
 *  - check all ioctl parameters
 */

/*
 * Helpers to access qgroup reservation
 *
 * Callers should ensure the lock context and type are valid
 */

अटल u64 qgroup_rsv_total(स्थिर काष्ठा btrfs_qgroup *qgroup)
अणु
	u64 ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < BTRFS_QGROUP_RSV_LAST; i++)
		ret += qgroup->rsv.values[i];

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_BTRFS_DEBUG
अटल स्थिर अक्षर *qgroup_rsv_type_str(क्रमागत btrfs_qgroup_rsv_type type)
अणु
	अगर (type == BTRFS_QGROUP_RSV_DATA)
		वापस "data";
	अगर (type == BTRFS_QGROUP_RSV_META_PERTRANS)
		वापस "meta_pertrans";
	अगर (type == BTRFS_QGROUP_RSV_META_PREALLOC)
		वापस "meta_prealloc";
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल व्योम qgroup_rsv_add(काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_qgroup *qgroup, u64 num_bytes,
			   क्रमागत btrfs_qgroup_rsv_type type)
अणु
	trace_qgroup_update_reserve(fs_info, qgroup, num_bytes, type);
	qgroup->rsv.values[type] += num_bytes;
पूर्ण

अटल व्योम qgroup_rsv_release(काष्ठा btrfs_fs_info *fs_info,
			       काष्ठा btrfs_qgroup *qgroup, u64 num_bytes,
			       क्रमागत btrfs_qgroup_rsv_type type)
अणु
	trace_qgroup_update_reserve(fs_info, qgroup, -(s64)num_bytes, type);
	अगर (qgroup->rsv.values[type] >= num_bytes) अणु
		qgroup->rsv.values[type] -= num_bytes;
		वापस;
	पूर्ण
#अगर_घोषित CONFIG_BTRFS_DEBUG
	WARN_RATELIMIT(1,
		"qgroup %llu %s reserved space underflow, have %llu to free %llu",
		qgroup->qgroupid, qgroup_rsv_type_str(type),
		qgroup->rsv.values[type], num_bytes);
#पूर्ण_अगर
	qgroup->rsv.values[type] = 0;
पूर्ण

अटल व्योम qgroup_rsv_add_by_qgroup(काष्ठा btrfs_fs_info *fs_info,
				     काष्ठा btrfs_qgroup *dest,
				     काष्ठा btrfs_qgroup *src)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BTRFS_QGROUP_RSV_LAST; i++)
		qgroup_rsv_add(fs_info, dest, src->rsv.values[i], i);
पूर्ण

अटल व्योम qgroup_rsv_release_by_qgroup(काष्ठा btrfs_fs_info *fs_info,
					 काष्ठा btrfs_qgroup *dest,
					  काष्ठा btrfs_qgroup *src)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BTRFS_QGROUP_RSV_LAST; i++)
		qgroup_rsv_release(fs_info, dest, src->rsv.values[i], i);
पूर्ण

अटल व्योम btrfs_qgroup_update_old_refcnt(काष्ठा btrfs_qgroup *qg, u64 seq,
					   पूर्णांक mod)
अणु
	अगर (qg->old_refcnt < seq)
		qg->old_refcnt = seq;
	qg->old_refcnt += mod;
पूर्ण

अटल व्योम btrfs_qgroup_update_new_refcnt(काष्ठा btrfs_qgroup *qg, u64 seq,
					   पूर्णांक mod)
अणु
	अगर (qg->new_refcnt < seq)
		qg->new_refcnt = seq;
	qg->new_refcnt += mod;
पूर्ण

अटल अंतरभूत u64 btrfs_qgroup_get_old_refcnt(काष्ठा btrfs_qgroup *qg, u64 seq)
अणु
	अगर (qg->old_refcnt < seq)
		वापस 0;
	वापस qg->old_refcnt - seq;
पूर्ण

अटल अंतरभूत u64 btrfs_qgroup_get_new_refcnt(काष्ठा btrfs_qgroup *qg, u64 seq)
अणु
	अगर (qg->new_refcnt < seq)
		वापस 0;
	वापस qg->new_refcnt - seq;
पूर्ण

/*
 * glue काष्ठाure to represent the relations between qgroups.
 */
काष्ठा btrfs_qgroup_list अणु
	काष्ठा list_head next_group;
	काष्ठा list_head next_member;
	काष्ठा btrfs_qgroup *group;
	काष्ठा btrfs_qgroup *member;
पूर्ण;

अटल अंतरभूत u64 qgroup_to_aux(काष्ठा btrfs_qgroup *qg)
अणु
	वापस (u64)(uपूर्णांकptr_t)qg;
पूर्ण

अटल अंतरभूत काष्ठा btrfs_qgroup* unode_aux_to_qgroup(काष्ठा ulist_node *n)
अणु
	वापस (काष्ठा btrfs_qgroup *)(uपूर्णांकptr_t)n->aux;
पूर्ण

अटल पूर्णांक
qgroup_rescan_init(काष्ठा btrfs_fs_info *fs_info, u64 progress_objectid,
		   पूर्णांक init_flags);
अटल व्योम qgroup_rescan_zero_tracking(काष्ठा btrfs_fs_info *fs_info);

/* must be called with qgroup_ioctl_lock held */
अटल काष्ठा btrfs_qgroup *find_qgroup_rb(काष्ठा btrfs_fs_info *fs_info,
					   u64 qgroupid)
अणु
	काष्ठा rb_node *n = fs_info->qgroup_tree.rb_node;
	काष्ठा btrfs_qgroup *qgroup;

	जबतक (n) अणु
		qgroup = rb_entry(n, काष्ठा btrfs_qgroup, node);
		अगर (qgroup->qgroupid < qgroupid)
			n = n->rb_left;
		अन्यथा अगर (qgroup->qgroupid > qgroupid)
			n = n->rb_right;
		अन्यथा
			वापस qgroup;
	पूर्ण
	वापस शून्य;
पूर्ण

/* must be called with qgroup_lock held */
अटल काष्ठा btrfs_qgroup *add_qgroup_rb(काष्ठा btrfs_fs_info *fs_info,
					  u64 qgroupid)
अणु
	काष्ठा rb_node **p = &fs_info->qgroup_tree.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा btrfs_qgroup *qgroup;

	जबतक (*p) अणु
		parent = *p;
		qgroup = rb_entry(parent, काष्ठा btrfs_qgroup, node);

		अगर (qgroup->qgroupid < qgroupid)
			p = &(*p)->rb_left;
		अन्यथा अगर (qgroup->qgroupid > qgroupid)
			p = &(*p)->rb_right;
		अन्यथा
			वापस qgroup;
	पूर्ण

	qgroup = kzalloc(माप(*qgroup), GFP_ATOMIC);
	अगर (!qgroup)
		वापस ERR_PTR(-ENOMEM);

	qgroup->qgroupid = qgroupid;
	INIT_LIST_HEAD(&qgroup->groups);
	INIT_LIST_HEAD(&qgroup->members);
	INIT_LIST_HEAD(&qgroup->dirty);

	rb_link_node(&qgroup->node, parent, p);
	rb_insert_color(&qgroup->node, &fs_info->qgroup_tree);

	वापस qgroup;
पूर्ण

अटल व्योम __del_qgroup_rb(काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा btrfs_qgroup *qgroup)
अणु
	काष्ठा btrfs_qgroup_list *list;

	list_del(&qgroup->dirty);
	जबतक (!list_empty(&qgroup->groups)) अणु
		list = list_first_entry(&qgroup->groups,
					काष्ठा btrfs_qgroup_list, next_group);
		list_del(&list->next_group);
		list_del(&list->next_member);
		kमुक्त(list);
	पूर्ण

	जबतक (!list_empty(&qgroup->members)) अणु
		list = list_first_entry(&qgroup->members,
					काष्ठा btrfs_qgroup_list, next_member);
		list_del(&list->next_group);
		list_del(&list->next_member);
		kमुक्त(list);
	पूर्ण
पूर्ण

/* must be called with qgroup_lock held */
अटल पूर्णांक del_qgroup_rb(काष्ठा btrfs_fs_info *fs_info, u64 qgroupid)
अणु
	काष्ठा btrfs_qgroup *qgroup = find_qgroup_rb(fs_info, qgroupid);

	अगर (!qgroup)
		वापस -ENOENT;

	rb_erase(&qgroup->node, &fs_info->qgroup_tree);
	__del_qgroup_rb(fs_info, qgroup);
	वापस 0;
पूर्ण

/* must be called with qgroup_lock held */
अटल पूर्णांक add_relation_rb(काष्ठा btrfs_fs_info *fs_info,
			   u64 memberid, u64 parentid)
अणु
	काष्ठा btrfs_qgroup *member;
	काष्ठा btrfs_qgroup *parent;
	काष्ठा btrfs_qgroup_list *list;

	member = find_qgroup_rb(fs_info, memberid);
	parent = find_qgroup_rb(fs_info, parentid);
	अगर (!member || !parent)
		वापस -ENOENT;

	list = kzalloc(माप(*list), GFP_ATOMIC);
	अगर (!list)
		वापस -ENOMEM;

	list->group = parent;
	list->member = member;
	list_add_tail(&list->next_group, &member->groups);
	list_add_tail(&list->next_member, &parent->members);

	वापस 0;
पूर्ण

/* must be called with qgroup_lock held */
अटल पूर्णांक del_relation_rb(काष्ठा btrfs_fs_info *fs_info,
			   u64 memberid, u64 parentid)
अणु
	काष्ठा btrfs_qgroup *member;
	काष्ठा btrfs_qgroup *parent;
	काष्ठा btrfs_qgroup_list *list;

	member = find_qgroup_rb(fs_info, memberid);
	parent = find_qgroup_rb(fs_info, parentid);
	अगर (!member || !parent)
		वापस -ENOENT;

	list_क्रम_each_entry(list, &member->groups, next_group) अणु
		अगर (list->group == parent) अणु
			list_del(&list->next_group);
			list_del(&list->next_member);
			kमुक्त(list);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
पूर्णांक btrfs_verअगरy_qgroup_counts(काष्ठा btrfs_fs_info *fs_info, u64 qgroupid,
			       u64 rfer, u64 excl)
अणु
	काष्ठा btrfs_qgroup *qgroup;

	qgroup = find_qgroup_rb(fs_info, qgroupid);
	अगर (!qgroup)
		वापस -EINVAL;
	अगर (qgroup->rfer != rfer || qgroup->excl != excl)
		वापस -EINVAL;
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * The full config is पढ़ो in one go, only called from खोलो_ctree()
 * It करोesn't use any locking, as at this point we're still single-thपढ़ोed
 */
पूर्णांक btrfs_पढ़ो_qgroup_config(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_root *quota_root = fs_info->quota_root;
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा extent_buffer *l;
	पूर्णांक slot;
	पूर्णांक ret = 0;
	u64 flags = 0;
	u64 rescan_progress = 0;

	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags))
		वापस 0;

	fs_info->qgroup_ulist = ulist_alloc(GFP_KERNEL);
	अगर (!fs_info->qgroup_ulist) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = btrfs_sysfs_add_qgroups(fs_info);
	अगर (ret < 0)
		जाओ out;
	/* शेष this to quota off, in हाल no status key is found */
	fs_info->qgroup_flags = 0;

	/*
	 * pass 1: पढ़ो status, all qgroup infos and limits
	 */
	key.objectid = 0;
	key.type = 0;
	key.offset = 0;
	ret = btrfs_search_slot_क्रम_पढ़ो(quota_root, &key, path, 1, 1);
	अगर (ret)
		जाओ out;

	जबतक (1) अणु
		काष्ठा btrfs_qgroup *qgroup;

		slot = path->slots[0];
		l = path->nodes[0];
		btrfs_item_key_to_cpu(l, &found_key, slot);

		अगर (found_key.type == BTRFS_QGROUP_STATUS_KEY) अणु
			काष्ठा btrfs_qgroup_status_item *ptr;

			ptr = btrfs_item_ptr(l, slot,
					     काष्ठा btrfs_qgroup_status_item);

			अगर (btrfs_qgroup_status_version(l, ptr) !=
			    BTRFS_QGROUP_STATUS_VERSION) अणु
				btrfs_err(fs_info,
				 "old qgroup version, quota disabled");
				जाओ out;
			पूर्ण
			अगर (btrfs_qgroup_status_generation(l, ptr) !=
			    fs_info->generation) अणु
				flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
				btrfs_err(fs_info,
					"qgroup generation mismatch, marked as inconsistent");
			पूर्ण
			fs_info->qgroup_flags = btrfs_qgroup_status_flags(l,
									  ptr);
			rescan_progress = btrfs_qgroup_status_rescan(l, ptr);
			जाओ next1;
		पूर्ण

		अगर (found_key.type != BTRFS_QGROUP_INFO_KEY &&
		    found_key.type != BTRFS_QGROUP_LIMIT_KEY)
			जाओ next1;

		qgroup = find_qgroup_rb(fs_info, found_key.offset);
		अगर ((qgroup && found_key.type == BTRFS_QGROUP_INFO_KEY) ||
		    (!qgroup && found_key.type == BTRFS_QGROUP_LIMIT_KEY)) अणु
			btrfs_err(fs_info, "inconsistent qgroup config");
			flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
		पूर्ण
		अगर (!qgroup) अणु
			qgroup = add_qgroup_rb(fs_info, found_key.offset);
			अगर (IS_ERR(qgroup)) अणु
				ret = PTR_ERR(qgroup);
				जाओ out;
			पूर्ण
		पूर्ण
		ret = btrfs_sysfs_add_one_qgroup(fs_info, qgroup);
		अगर (ret < 0)
			जाओ out;

		चयन (found_key.type) अणु
		हाल BTRFS_QGROUP_INFO_KEY: अणु
			काष्ठा btrfs_qgroup_info_item *ptr;

			ptr = btrfs_item_ptr(l, slot,
					     काष्ठा btrfs_qgroup_info_item);
			qgroup->rfer = btrfs_qgroup_info_rfer(l, ptr);
			qgroup->rfer_cmpr = btrfs_qgroup_info_rfer_cmpr(l, ptr);
			qgroup->excl = btrfs_qgroup_info_excl(l, ptr);
			qgroup->excl_cmpr = btrfs_qgroup_info_excl_cmpr(l, ptr);
			/* generation currently unused */
			अवरोध;
		पूर्ण
		हाल BTRFS_QGROUP_LIMIT_KEY: अणु
			काष्ठा btrfs_qgroup_limit_item *ptr;

			ptr = btrfs_item_ptr(l, slot,
					     काष्ठा btrfs_qgroup_limit_item);
			qgroup->lim_flags = btrfs_qgroup_limit_flags(l, ptr);
			qgroup->max_rfer = btrfs_qgroup_limit_max_rfer(l, ptr);
			qgroup->max_excl = btrfs_qgroup_limit_max_excl(l, ptr);
			qgroup->rsv_rfer = btrfs_qgroup_limit_rsv_rfer(l, ptr);
			qgroup->rsv_excl = btrfs_qgroup_limit_rsv_excl(l, ptr);
			अवरोध;
		पूर्ण
		पूर्ण
next1:
		ret = btrfs_next_item(quota_root, path);
		अगर (ret < 0)
			जाओ out;
		अगर (ret)
			अवरोध;
	पूर्ण
	btrfs_release_path(path);

	/*
	 * pass 2: पढ़ो all qgroup relations
	 */
	key.objectid = 0;
	key.type = BTRFS_QGROUP_RELATION_KEY;
	key.offset = 0;
	ret = btrfs_search_slot_क्रम_पढ़ो(quota_root, &key, path, 1, 0);
	अगर (ret)
		जाओ out;
	जबतक (1) अणु
		slot = path->slots[0];
		l = path->nodes[0];
		btrfs_item_key_to_cpu(l, &found_key, slot);

		अगर (found_key.type != BTRFS_QGROUP_RELATION_KEY)
			जाओ next2;

		अगर (found_key.objectid > found_key.offset) अणु
			/* parent <- member, not needed to build config */
			/* FIXME should we omit the key completely? */
			जाओ next2;
		पूर्ण

		ret = add_relation_rb(fs_info, found_key.objectid,
				      found_key.offset);
		अगर (ret == -ENOENT) अणु
			btrfs_warn(fs_info,
				"orphan qgroup relation 0x%llx->0x%llx",
				found_key.objectid, found_key.offset);
			ret = 0;	/* ignore the error */
		पूर्ण
		अगर (ret)
			जाओ out;
next2:
		ret = btrfs_next_item(quota_root, path);
		अगर (ret < 0)
			जाओ out;
		अगर (ret)
			अवरोध;
	पूर्ण
out:
	btrfs_मुक्त_path(path);
	fs_info->qgroup_flags |= flags;
	अगर (!(fs_info->qgroup_flags & BTRFS_QGROUP_STATUS_FLAG_ON))
		clear_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags);
	अन्यथा अगर (fs_info->qgroup_flags & BTRFS_QGROUP_STATUS_FLAG_RESCAN &&
		 ret >= 0)
		ret = qgroup_rescan_init(fs_info, rescan_progress, 0);

	अगर (ret < 0) अणु
		ulist_मुक्त(fs_info->qgroup_ulist);
		fs_info->qgroup_ulist = शून्य;
		fs_info->qgroup_flags &= ~BTRFS_QGROUP_STATUS_FLAG_RESCAN;
		btrfs_sysfs_del_qgroups(fs_info);
	पूर्ण

	वापस ret < 0 ? ret : 0;
पूर्ण

/*
 * Called in बंद_ctree() when quota is still enabled.  This verअगरies we करोn't
 * leak some reserved space.
 *
 * Return false अगर no reserved space is left.
 * Return true अगर some reserved space is leaked.
 */
bool btrfs_check_quota_leak(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा rb_node *node;
	bool ret = false;

	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags))
		वापस ret;
	/*
	 * Since we're unmounting, there is no race and no need to grab qgroup
	 * lock.  And here we करोn't go post-order to provide a more user
	 * मित्रly sorted result.
	 */
	क्रम (node = rb_first(&fs_info->qgroup_tree); node; node = rb_next(node)) अणु
		काष्ठा btrfs_qgroup *qgroup;
		पूर्णांक i;

		qgroup = rb_entry(node, काष्ठा btrfs_qgroup, node);
		क्रम (i = 0; i < BTRFS_QGROUP_RSV_LAST; i++) अणु
			अगर (qgroup->rsv.values[i]) अणु
				ret = true;
				btrfs_warn(fs_info,
		"qgroup %hu/%llu has unreleased space, type %d rsv %llu",
				   btrfs_qgroup_level(qgroup->qgroupid),
				   btrfs_qgroup_subvolid(qgroup->qgroupid),
				   i, qgroup->rsv.values[i]);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * This is called from बंद_ctree() or खोलो_ctree() or btrfs_quota_disable(),
 * first two are in single-thपढ़ोed paths.And क्रम the third one, we have set
 * quota_root to be null with qgroup_lock held beक्रमe, so it is safe to clean
 * up the in-memory काष्ठाures without qgroup_lock held.
 */
व्योम btrfs_मुक्त_qgroup_config(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा rb_node *n;
	काष्ठा btrfs_qgroup *qgroup;

	जबतक ((n = rb_first(&fs_info->qgroup_tree))) अणु
		qgroup = rb_entry(n, काष्ठा btrfs_qgroup, node);
		rb_erase(n, &fs_info->qgroup_tree);
		__del_qgroup_rb(fs_info, qgroup);
		btrfs_sysfs_del_one_qgroup(fs_info, qgroup);
		kमुक्त(qgroup);
	पूर्ण
	/*
	 * We call btrfs_मुक्त_qgroup_config() when unmounting
	 * fileप्रणाली and disabling quota, so we set qgroup_ulist
	 * to be null here to aव्योम द्विगुन मुक्त.
	 */
	ulist_मुक्त(fs_info->qgroup_ulist);
	fs_info->qgroup_ulist = शून्य;
	btrfs_sysfs_del_qgroups(fs_info);
पूर्ण

अटल पूर्णांक add_qgroup_relation_item(काष्ठा btrfs_trans_handle *trans, u64 src,
				    u64 dst)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_root *quota_root = trans->fs_info->quota_root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = src;
	key.type = BTRFS_QGROUP_RELATION_KEY;
	key.offset = dst;

	ret = btrfs_insert_empty_item(trans, quota_root, path, &key, 0);

	btrfs_mark_buffer_dirty(path->nodes[0]);

	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक del_qgroup_relation_item(काष्ठा btrfs_trans_handle *trans, u64 src,
				    u64 dst)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_root *quota_root = trans->fs_info->quota_root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = src;
	key.type = BTRFS_QGROUP_RELATION_KEY;
	key.offset = dst;

	ret = btrfs_search_slot(trans, quota_root, &key, path, -1, 1);
	अगर (ret < 0)
		जाओ out;

	अगर (ret > 0) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	ret = btrfs_del_item(trans, quota_root, path);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक add_qgroup_item(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *quota_root, u64 qgroupid)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_qgroup_info_item *qgroup_info;
	काष्ठा btrfs_qgroup_limit_item *qgroup_limit;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;

	अगर (btrfs_is_testing(quota_root->fs_info))
		वापस 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = 0;
	key.type = BTRFS_QGROUP_INFO_KEY;
	key.offset = qgroupid;

	/*
	 * Aव्योम a transaction पात by catching -EEXIST here. In that
	 * हाल, we proceed by re-initializing the existing काष्ठाure
	 * on disk.
	 */

	ret = btrfs_insert_empty_item(trans, quota_root, path, &key,
				      माप(*qgroup_info));
	अगर (ret && ret != -EEXIST)
		जाओ out;

	leaf = path->nodes[0];
	qgroup_info = btrfs_item_ptr(leaf, path->slots[0],
				 काष्ठा btrfs_qgroup_info_item);
	btrfs_set_qgroup_info_generation(leaf, qgroup_info, trans->transid);
	btrfs_set_qgroup_info_rfer(leaf, qgroup_info, 0);
	btrfs_set_qgroup_info_rfer_cmpr(leaf, qgroup_info, 0);
	btrfs_set_qgroup_info_excl(leaf, qgroup_info, 0);
	btrfs_set_qgroup_info_excl_cmpr(leaf, qgroup_info, 0);

	btrfs_mark_buffer_dirty(leaf);

	btrfs_release_path(path);

	key.type = BTRFS_QGROUP_LIMIT_KEY;
	ret = btrfs_insert_empty_item(trans, quota_root, path, &key,
				      माप(*qgroup_limit));
	अगर (ret && ret != -EEXIST)
		जाओ out;

	leaf = path->nodes[0];
	qgroup_limit = btrfs_item_ptr(leaf, path->slots[0],
				  काष्ठा btrfs_qgroup_limit_item);
	btrfs_set_qgroup_limit_flags(leaf, qgroup_limit, 0);
	btrfs_set_qgroup_limit_max_rfer(leaf, qgroup_limit, 0);
	btrfs_set_qgroup_limit_max_excl(leaf, qgroup_limit, 0);
	btrfs_set_qgroup_limit_rsv_rfer(leaf, qgroup_limit, 0);
	btrfs_set_qgroup_limit_rsv_excl(leaf, qgroup_limit, 0);

	btrfs_mark_buffer_dirty(leaf);

	ret = 0;
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक del_qgroup_item(काष्ठा btrfs_trans_handle *trans, u64 qgroupid)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_root *quota_root = trans->fs_info->quota_root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = 0;
	key.type = BTRFS_QGROUP_INFO_KEY;
	key.offset = qgroupid;
	ret = btrfs_search_slot(trans, quota_root, &key, path, -1, 1);
	अगर (ret < 0)
		जाओ out;

	अगर (ret > 0) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	ret = btrfs_del_item(trans, quota_root, path);
	अगर (ret)
		जाओ out;

	btrfs_release_path(path);

	key.type = BTRFS_QGROUP_LIMIT_KEY;
	ret = btrfs_search_slot(trans, quota_root, &key, path, -1, 1);
	अगर (ret < 0)
		जाओ out;

	अगर (ret > 0) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	ret = btrfs_del_item(trans, quota_root, path);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक update_qgroup_limit_item(काष्ठा btrfs_trans_handle *trans,
				    काष्ठा btrfs_qgroup *qgroup)
अणु
	काष्ठा btrfs_root *quota_root = trans->fs_info->quota_root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *l;
	काष्ठा btrfs_qgroup_limit_item *qgroup_limit;
	पूर्णांक ret;
	पूर्णांक slot;

	key.objectid = 0;
	key.type = BTRFS_QGROUP_LIMIT_KEY;
	key.offset = qgroup->qgroupid;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_search_slot(trans, quota_root, &key, path, 0, 1);
	अगर (ret > 0)
		ret = -ENOENT;

	अगर (ret)
		जाओ out;

	l = path->nodes[0];
	slot = path->slots[0];
	qgroup_limit = btrfs_item_ptr(l, slot, काष्ठा btrfs_qgroup_limit_item);
	btrfs_set_qgroup_limit_flags(l, qgroup_limit, qgroup->lim_flags);
	btrfs_set_qgroup_limit_max_rfer(l, qgroup_limit, qgroup->max_rfer);
	btrfs_set_qgroup_limit_max_excl(l, qgroup_limit, qgroup->max_excl);
	btrfs_set_qgroup_limit_rsv_rfer(l, qgroup_limit, qgroup->rsv_rfer);
	btrfs_set_qgroup_limit_rsv_excl(l, qgroup_limit, qgroup->rsv_excl);

	btrfs_mark_buffer_dirty(l);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक update_qgroup_info_item(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_qgroup *qgroup)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *quota_root = fs_info->quota_root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *l;
	काष्ठा btrfs_qgroup_info_item *qgroup_info;
	पूर्णांक ret;
	पूर्णांक slot;

	अगर (btrfs_is_testing(fs_info))
		वापस 0;

	key.objectid = 0;
	key.type = BTRFS_QGROUP_INFO_KEY;
	key.offset = qgroup->qgroupid;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_search_slot(trans, quota_root, &key, path, 0, 1);
	अगर (ret > 0)
		ret = -ENOENT;

	अगर (ret)
		जाओ out;

	l = path->nodes[0];
	slot = path->slots[0];
	qgroup_info = btrfs_item_ptr(l, slot, काष्ठा btrfs_qgroup_info_item);
	btrfs_set_qgroup_info_generation(l, qgroup_info, trans->transid);
	btrfs_set_qgroup_info_rfer(l, qgroup_info, qgroup->rfer);
	btrfs_set_qgroup_info_rfer_cmpr(l, qgroup_info, qgroup->rfer_cmpr);
	btrfs_set_qgroup_info_excl(l, qgroup_info, qgroup->excl);
	btrfs_set_qgroup_info_excl_cmpr(l, qgroup_info, qgroup->excl_cmpr);

	btrfs_mark_buffer_dirty(l);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक update_qgroup_status_item(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *quota_root = fs_info->quota_root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *l;
	काष्ठा btrfs_qgroup_status_item *ptr;
	पूर्णांक ret;
	पूर्णांक slot;

	key.objectid = 0;
	key.type = BTRFS_QGROUP_STATUS_KEY;
	key.offset = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_search_slot(trans, quota_root, &key, path, 0, 1);
	अगर (ret > 0)
		ret = -ENOENT;

	अगर (ret)
		जाओ out;

	l = path->nodes[0];
	slot = path->slots[0];
	ptr = btrfs_item_ptr(l, slot, काष्ठा btrfs_qgroup_status_item);
	btrfs_set_qgroup_status_flags(l, ptr, fs_info->qgroup_flags);
	btrfs_set_qgroup_status_generation(l, ptr, trans->transid);
	btrfs_set_qgroup_status_rescan(l, ptr,
				fs_info->qgroup_rescan_progress.objectid);

	btrfs_mark_buffer_dirty(l);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * called with qgroup_lock held
 */
अटल पूर्णांक btrfs_clean_quota_tree(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *leaf = शून्य;
	पूर्णांक ret;
	पूर्णांक nr = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = 0;
	key.offset = 0;
	key.type = 0;

	जबतक (1) अणु
		ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
		अगर (ret < 0)
			जाओ out;
		leaf = path->nodes[0];
		nr = btrfs_header_nritems(leaf);
		अगर (!nr)
			अवरोध;
		/*
		 * delete the leaf one by one
		 * since the whole tree is going
		 * to be deleted.
		 */
		path->slots[0] = 0;
		ret = btrfs_del_items(trans, root, path, 0, nr);
		अगर (ret)
			जाओ out;

		btrfs_release_path(path);
	पूर्ण
	ret = 0;
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_quota_enable(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *quota_root;
	काष्ठा btrfs_root *tree_root = fs_info->tree_root;
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा btrfs_qgroup_status_item *ptr;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_qgroup *qgroup = शून्य;
	काष्ठा btrfs_trans_handle *trans = शून्य;
	काष्ठा ulist *ulist = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक slot;

	mutex_lock(&fs_info->qgroup_ioctl_lock);
	अगर (fs_info->quota_root)
		जाओ out;

	ulist = ulist_alloc(GFP_KERNEL);
	अगर (!ulist) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = btrfs_sysfs_add_qgroups(fs_info);
	अगर (ret < 0)
		जाओ out;

	/*
	 * Unlock qgroup_ioctl_lock beक्रमe starting the transaction. This is to
	 * aव्योम lock acquisition inversion problems (reported by lockdep) between
	 * qgroup_ioctl_lock and the vfs मुक्तze semaphores, acquired when we
	 * start a transaction.
	 * After we started the transaction lock qgroup_ioctl_lock again and
	 * check अगर someone अन्यथा created the quota root in the meanजबतक. If so,
	 * just वापस success and release the transaction handle.
	 *
	 * Also we करोn't need to worry about someone अन्यथा calling
	 * btrfs_sysfs_add_qgroups() after we unlock and getting an error because
	 * that function वापसs 0 (success) when the sysfs entries alपढ़ोy exist.
	 */
	mutex_unlock(&fs_info->qgroup_ioctl_lock);

	/*
	 * 1 क्रम quota root item
	 * 1 क्रम BTRFS_QGROUP_STATUS item
	 *
	 * Yet we also need 2*n items क्रम a QGROUP_INFO/QGROUP_LIMIT items
	 * per subvolume. However those are not currently reserved since it
	 * would be a lot of overसमाप्त.
	 */
	trans = btrfs_start_transaction(tree_root, 2);

	mutex_lock(&fs_info->qgroup_ioctl_lock);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		trans = शून्य;
		जाओ out;
	पूर्ण

	अगर (fs_info->quota_root)
		जाओ out;

	fs_info->qgroup_ulist = ulist;
	ulist = शून्य;

	/*
	 * initially create the quota tree
	 */
	quota_root = btrfs_create_tree(trans, BTRFS_QUOTA_TREE_OBJECTID);
	अगर (IS_ERR(quota_root)) अणु
		ret =  PTR_ERR(quota_root);
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		btrfs_पात_transaction(trans, ret);
		जाओ out_मुक्त_root;
	पूर्ण

	key.objectid = 0;
	key.type = BTRFS_QGROUP_STATUS_KEY;
	key.offset = 0;

	ret = btrfs_insert_empty_item(trans, quota_root, path, &key,
				      माप(*ptr));
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out_मुक्त_path;
	पूर्ण

	leaf = path->nodes[0];
	ptr = btrfs_item_ptr(leaf, path->slots[0],
				 काष्ठा btrfs_qgroup_status_item);
	btrfs_set_qgroup_status_generation(leaf, ptr, trans->transid);
	btrfs_set_qgroup_status_version(leaf, ptr, BTRFS_QGROUP_STATUS_VERSION);
	fs_info->qgroup_flags = BTRFS_QGROUP_STATUS_FLAG_ON |
				BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
	btrfs_set_qgroup_status_flags(leaf, ptr, fs_info->qgroup_flags);
	btrfs_set_qgroup_status_rescan(leaf, ptr, 0);

	btrfs_mark_buffer_dirty(leaf);

	key.objectid = 0;
	key.type = BTRFS_ROOT_REF_KEY;
	key.offset = 0;

	btrfs_release_path(path);
	ret = btrfs_search_slot_क्रम_पढ़ो(tree_root, &key, path, 1, 0);
	अगर (ret > 0)
		जाओ out_add_root;
	अगर (ret < 0) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out_मुक्त_path;
	पूर्ण

	जबतक (1) अणु
		slot = path->slots[0];
		leaf = path->nodes[0];
		btrfs_item_key_to_cpu(leaf, &found_key, slot);

		अगर (found_key.type == BTRFS_ROOT_REF_KEY) अणु

			/* Release locks on tree_root beक्रमe we access quota_root */
			btrfs_release_path(path);

			ret = add_qgroup_item(trans, quota_root,
					      found_key.offset);
			अगर (ret) अणु
				btrfs_पात_transaction(trans, ret);
				जाओ out_मुक्त_path;
			पूर्ण

			qgroup = add_qgroup_rb(fs_info, found_key.offset);
			अगर (IS_ERR(qgroup)) अणु
				ret = PTR_ERR(qgroup);
				btrfs_पात_transaction(trans, ret);
				जाओ out_मुक्त_path;
			पूर्ण
			ret = btrfs_sysfs_add_one_qgroup(fs_info, qgroup);
			अगर (ret < 0) अणु
				btrfs_पात_transaction(trans, ret);
				जाओ out_मुक्त_path;
			पूर्ण
			ret = btrfs_search_slot_क्रम_पढ़ो(tree_root, &found_key,
							 path, 1, 0);
			अगर (ret < 0) अणु
				btrfs_पात_transaction(trans, ret);
				जाओ out_मुक्त_path;
			पूर्ण
			अगर (ret > 0) अणु
				/*
				 * Shouldn't happen, but in हाल it करोes we
				 * करोn't need to करो the btrfs_next_item, just
				 * जारी.
				 */
				जारी;
			पूर्ण
		पूर्ण
		ret = btrfs_next_item(tree_root, path);
		अगर (ret < 0) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out_मुक्त_path;
		पूर्ण
		अगर (ret)
			अवरोध;
	पूर्ण

out_add_root:
	btrfs_release_path(path);
	ret = add_qgroup_item(trans, quota_root, BTRFS_FS_TREE_OBJECTID);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out_मुक्त_path;
	पूर्ण

	qgroup = add_qgroup_rb(fs_info, BTRFS_FS_TREE_OBJECTID);
	अगर (IS_ERR(qgroup)) अणु
		ret = PTR_ERR(qgroup);
		btrfs_पात_transaction(trans, ret);
		जाओ out_मुक्त_path;
	पूर्ण
	ret = btrfs_sysfs_add_one_qgroup(fs_info, qgroup);
	अगर (ret < 0) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out_मुक्त_path;
	पूर्ण

	ret = btrfs_commit_transaction(trans);
	trans = शून्य;
	अगर (ret)
		जाओ out_मुक्त_path;

	/*
	 * Set quota enabled flag after committing the transaction, to aव्योम
	 * deadlocks on fs_info->qgroup_ioctl_lock with concurrent snapshot
	 * creation.
	 */
	spin_lock(&fs_info->qgroup_lock);
	fs_info->quota_root = quota_root;
	set_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags);
	spin_unlock(&fs_info->qgroup_lock);

	ret = qgroup_rescan_init(fs_info, 0, 1);
	अगर (!ret) अणु
	        qgroup_rescan_zero_tracking(fs_info);
		fs_info->qgroup_rescan_running = true;
	        btrfs_queue_work(fs_info->qgroup_rescan_workers,
	                         &fs_info->qgroup_rescan_work);
	पूर्ण

out_मुक्त_path:
	btrfs_मुक्त_path(path);
out_मुक्त_root:
	अगर (ret)
		btrfs_put_root(quota_root);
out:
	अगर (ret) अणु
		ulist_मुक्त(fs_info->qgroup_ulist);
		fs_info->qgroup_ulist = शून्य;
		btrfs_sysfs_del_qgroups(fs_info);
	पूर्ण
	mutex_unlock(&fs_info->qgroup_ioctl_lock);
	अगर (ret && trans)
		btrfs_end_transaction(trans);
	अन्यथा अगर (trans)
		ret = btrfs_end_transaction(trans);
	ulist_मुक्त(ulist);
	वापस ret;
पूर्ण

पूर्णांक btrfs_quota_disable(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *quota_root;
	काष्ठा btrfs_trans_handle *trans = शून्य;
	पूर्णांक ret = 0;

	mutex_lock(&fs_info->qgroup_ioctl_lock);
	अगर (!fs_info->quota_root)
		जाओ out;
	mutex_unlock(&fs_info->qgroup_ioctl_lock);

	/*
	 * 1 For the root item
	 *
	 * We should also reserve enough items क्रम the quota tree deletion in
	 * btrfs_clean_quota_tree but this is not करोne.
	 *
	 * Also, we must always start a transaction without holding the mutex
	 * qgroup_ioctl_lock, see btrfs_quota_enable().
	 */
	trans = btrfs_start_transaction(fs_info->tree_root, 1);

	mutex_lock(&fs_info->qgroup_ioctl_lock);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		trans = शून्य;
		जाओ out;
	पूर्ण

	अगर (!fs_info->quota_root)
		जाओ out;

	clear_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags);
	btrfs_qgroup_रुको_क्रम_completion(fs_info, false);
	spin_lock(&fs_info->qgroup_lock);
	quota_root = fs_info->quota_root;
	fs_info->quota_root = शून्य;
	fs_info->qgroup_flags &= ~BTRFS_QGROUP_STATUS_FLAG_ON;
	spin_unlock(&fs_info->qgroup_lock);

	btrfs_मुक्त_qgroup_config(fs_info);

	ret = btrfs_clean_quota_tree(trans, quota_root);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

	ret = btrfs_del_root(trans, &quota_root->root_key);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

	list_del(&quota_root->dirty_list);

	btrfs_tree_lock(quota_root->node);
	btrfs_clean_tree_block(quota_root->node);
	btrfs_tree_unlock(quota_root->node);
	btrfs_मुक्त_tree_block(trans, quota_root, quota_root->node, 0, 1);

	btrfs_put_root(quota_root);

out:
	mutex_unlock(&fs_info->qgroup_ioctl_lock);
	अगर (ret && trans)
		btrfs_end_transaction(trans);
	अन्यथा अगर (trans)
		ret = btrfs_end_transaction(trans);

	वापस ret;
पूर्ण

अटल व्योम qgroup_dirty(काष्ठा btrfs_fs_info *fs_info,
			 काष्ठा btrfs_qgroup *qgroup)
अणु
	अगर (list_empty(&qgroup->dirty))
		list_add(&qgroup->dirty, &fs_info->dirty_qgroups);
पूर्ण

/*
 * The easy accounting, we're updating qgroup relationship whose child qgroup
 * only has exclusive extents.
 *
 * In this हाल, all exclusive extents will also be exclusive क्रम parent, so
 * excl/rfer just get added/हटाओd.
 *
 * So is qgroup reservation space, which should also be added/हटाओd to
 * parent.
 * Or when child tries to release reservation space, parent will underflow its
 * reservation (क्रम relationship adding हाल).
 *
 * Caller should hold fs_info->qgroup_lock.
 */
अटल पूर्णांक __qgroup_excl_accounting(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा ulist *पंचांगp, u64 ref_root,
				    काष्ठा btrfs_qgroup *src, पूर्णांक sign)
अणु
	काष्ठा btrfs_qgroup *qgroup;
	काष्ठा btrfs_qgroup_list *glist;
	काष्ठा ulist_node *unode;
	काष्ठा ulist_iterator uiter;
	u64 num_bytes = src->excl;
	पूर्णांक ret = 0;

	qgroup = find_qgroup_rb(fs_info, ref_root);
	अगर (!qgroup)
		जाओ out;

	qgroup->rfer += sign * num_bytes;
	qgroup->rfer_cmpr += sign * num_bytes;

	WARN_ON(sign < 0 && qgroup->excl < num_bytes);
	qgroup->excl += sign * num_bytes;
	qgroup->excl_cmpr += sign * num_bytes;

	अगर (sign > 0)
		qgroup_rsv_add_by_qgroup(fs_info, qgroup, src);
	अन्यथा
		qgroup_rsv_release_by_qgroup(fs_info, qgroup, src);

	qgroup_dirty(fs_info, qgroup);

	/* Get all of the parent groups that contain this qgroup */
	list_क्रम_each_entry(glist, &qgroup->groups, next_group) अणु
		ret = ulist_add(पंचांगp, glist->group->qgroupid,
				qgroup_to_aux(glist->group), GFP_ATOMIC);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	/* Iterate all of the parents and adjust their reference counts */
	ULIST_ITER_INIT(&uiter);
	जबतक ((unode = ulist_next(पंचांगp, &uiter))) अणु
		qgroup = unode_aux_to_qgroup(unode);
		qgroup->rfer += sign * num_bytes;
		qgroup->rfer_cmpr += sign * num_bytes;
		WARN_ON(sign < 0 && qgroup->excl < num_bytes);
		qgroup->excl += sign * num_bytes;
		अगर (sign > 0)
			qgroup_rsv_add_by_qgroup(fs_info, qgroup, src);
		अन्यथा
			qgroup_rsv_release_by_qgroup(fs_info, qgroup, src);
		qgroup->excl_cmpr += sign * num_bytes;
		qgroup_dirty(fs_info, qgroup);

		/* Add any parents of the parents */
		list_क्रम_each_entry(glist, &qgroup->groups, next_group) अणु
			ret = ulist_add(पंचांगp, glist->group->qgroupid,
					qgroup_to_aux(glist->group), GFP_ATOMIC);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण
	ret = 0;
out:
	वापस ret;
पूर्ण


/*
 * Quick path क्रम updating qgroup with only excl refs.
 *
 * In that हाल, just update all parent will be enough.
 * Or we needs to करो a full rescan.
 * Caller should also hold fs_info->qgroup_lock.
 *
 * Return 0 क्रम quick update, वापस >0 क्रम need to full rescan
 * and mark INCONSISTENT flag.
 * Return < 0 क्रम other error.
 */
अटल पूर्णांक quick_update_accounting(काष्ठा btrfs_fs_info *fs_info,
				   काष्ठा ulist *पंचांगp, u64 src, u64 dst,
				   पूर्णांक sign)
अणु
	काष्ठा btrfs_qgroup *qgroup;
	पूर्णांक ret = 1;
	पूर्णांक err = 0;

	qgroup = find_qgroup_rb(fs_info, src);
	अगर (!qgroup)
		जाओ out;
	अगर (qgroup->excl == qgroup->rfer) अणु
		ret = 0;
		err = __qgroup_excl_accounting(fs_info, पंचांगp, dst,
					       qgroup, sign);
		अगर (err < 0) अणु
			ret = err;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	अगर (ret)
		fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
	वापस ret;
पूर्ण

पूर्णांक btrfs_add_qgroup_relation(काष्ठा btrfs_trans_handle *trans, u64 src,
			      u64 dst)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_qgroup *parent;
	काष्ठा btrfs_qgroup *member;
	काष्ठा btrfs_qgroup_list *list;
	काष्ठा ulist *पंचांगp;
	अचिन्हित पूर्णांक nofs_flag;
	पूर्णांक ret = 0;

	/* Check the level of src and dst first */
	अगर (btrfs_qgroup_level(src) >= btrfs_qgroup_level(dst))
		वापस -EINVAL;

	/* We hold a transaction handle खोलो, must करो a NOFS allocation. */
	nofs_flag = meदो_स्मृति_nofs_save();
	पंचांगp = ulist_alloc(GFP_KERNEL);
	meदो_स्मृति_nofs_restore(nofs_flag);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	mutex_lock(&fs_info->qgroup_ioctl_lock);
	अगर (!fs_info->quota_root) अणु
		ret = -ENOTCONN;
		जाओ out;
	पूर्ण
	member = find_qgroup_rb(fs_info, src);
	parent = find_qgroup_rb(fs_info, dst);
	अगर (!member || !parent) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* check अगर such qgroup relation exist firstly */
	list_क्रम_each_entry(list, &member->groups, next_group) अणु
		अगर (list->group == parent) अणु
			ret = -EEXIST;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = add_qgroup_relation_item(trans, src, dst);
	अगर (ret)
		जाओ out;

	ret = add_qgroup_relation_item(trans, dst, src);
	अगर (ret) अणु
		del_qgroup_relation_item(trans, src, dst);
		जाओ out;
	पूर्ण

	spin_lock(&fs_info->qgroup_lock);
	ret = add_relation_rb(fs_info, src, dst);
	अगर (ret < 0) अणु
		spin_unlock(&fs_info->qgroup_lock);
		जाओ out;
	पूर्ण
	ret = quick_update_accounting(fs_info, पंचांगp, src, dst, 1);
	spin_unlock(&fs_info->qgroup_lock);
out:
	mutex_unlock(&fs_info->qgroup_ioctl_lock);
	ulist_मुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल पूर्णांक __del_qgroup_relation(काष्ठा btrfs_trans_handle *trans, u64 src,
				 u64 dst)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_qgroup *parent;
	काष्ठा btrfs_qgroup *member;
	काष्ठा btrfs_qgroup_list *list;
	काष्ठा ulist *पंचांगp;
	bool found = false;
	अचिन्हित पूर्णांक nofs_flag;
	पूर्णांक ret = 0;
	पूर्णांक ret2;

	/* We hold a transaction handle खोलो, must करो a NOFS allocation. */
	nofs_flag = meदो_स्मृति_nofs_save();
	पंचांगp = ulist_alloc(GFP_KERNEL);
	meदो_स्मृति_nofs_restore(nofs_flag);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	अगर (!fs_info->quota_root) अणु
		ret = -ENOTCONN;
		जाओ out;
	पूर्ण

	member = find_qgroup_rb(fs_info, src);
	parent = find_qgroup_rb(fs_info, dst);
	/*
	 * The parent/member pair करोesn't exist, then try to delete the dead
	 * relation items only.
	 */
	अगर (!member || !parent)
		जाओ delete_item;

	/* check अगर such qgroup relation exist firstly */
	list_क्रम_each_entry(list, &member->groups, next_group) अणु
		अगर (list->group == parent) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

delete_item:
	ret = del_qgroup_relation_item(trans, src, dst);
	अगर (ret < 0 && ret != -ENOENT)
		जाओ out;
	ret2 = del_qgroup_relation_item(trans, dst, src);
	अगर (ret2 < 0 && ret2 != -ENOENT)
		जाओ out;

	/* At least one deletion succeeded, वापस 0 */
	अगर (!ret || !ret2)
		ret = 0;

	अगर (found) अणु
		spin_lock(&fs_info->qgroup_lock);
		del_relation_rb(fs_info, src, dst);
		ret = quick_update_accounting(fs_info, पंचांगp, src, dst, -1);
		spin_unlock(&fs_info->qgroup_lock);
	पूर्ण
out:
	ulist_मुक्त(पंचांगp);
	वापस ret;
पूर्ण

पूर्णांक btrfs_del_qgroup_relation(काष्ठा btrfs_trans_handle *trans, u64 src,
			      u64 dst)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक ret = 0;

	mutex_lock(&fs_info->qgroup_ioctl_lock);
	ret = __del_qgroup_relation(trans, src, dst);
	mutex_unlock(&fs_info->qgroup_ioctl_lock);

	वापस ret;
पूर्ण

पूर्णांक btrfs_create_qgroup(काष्ठा btrfs_trans_handle *trans, u64 qgroupid)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *quota_root;
	काष्ठा btrfs_qgroup *qgroup;
	पूर्णांक ret = 0;

	mutex_lock(&fs_info->qgroup_ioctl_lock);
	अगर (!fs_info->quota_root) अणु
		ret = -ENOTCONN;
		जाओ out;
	पूर्ण
	quota_root = fs_info->quota_root;
	qgroup = find_qgroup_rb(fs_info, qgroupid);
	अगर (qgroup) अणु
		ret = -EEXIST;
		जाओ out;
	पूर्ण

	ret = add_qgroup_item(trans, quota_root, qgroupid);
	अगर (ret)
		जाओ out;

	spin_lock(&fs_info->qgroup_lock);
	qgroup = add_qgroup_rb(fs_info, qgroupid);
	spin_unlock(&fs_info->qgroup_lock);

	अगर (IS_ERR(qgroup)) अणु
		ret = PTR_ERR(qgroup);
		जाओ out;
	पूर्ण
	ret = btrfs_sysfs_add_one_qgroup(fs_info, qgroup);
out:
	mutex_unlock(&fs_info->qgroup_ioctl_lock);
	वापस ret;
पूर्ण

पूर्णांक btrfs_हटाओ_qgroup(काष्ठा btrfs_trans_handle *trans, u64 qgroupid)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_qgroup *qgroup;
	काष्ठा btrfs_qgroup_list *list;
	पूर्णांक ret = 0;

	mutex_lock(&fs_info->qgroup_ioctl_lock);
	अगर (!fs_info->quota_root) अणु
		ret = -ENOTCONN;
		जाओ out;
	पूर्ण

	qgroup = find_qgroup_rb(fs_info, qgroupid);
	अगर (!qgroup) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	/* Check अगर there are no children of this qgroup */
	अगर (!list_empty(&qgroup->members)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = del_qgroup_item(trans, qgroupid);
	अगर (ret && ret != -ENOENT)
		जाओ out;

	जबतक (!list_empty(&qgroup->groups)) अणु
		list = list_first_entry(&qgroup->groups,
					काष्ठा btrfs_qgroup_list, next_group);
		ret = __del_qgroup_relation(trans, qgroupid,
					    list->group->qgroupid);
		अगर (ret)
			जाओ out;
	पूर्ण

	spin_lock(&fs_info->qgroup_lock);
	del_qgroup_rb(fs_info, qgroupid);
	spin_unlock(&fs_info->qgroup_lock);

	/*
	 * Remove the qgroup from sysfs now without holding the qgroup_lock
	 * spinlock, since the sysfs_हटाओ_group() function needs to take
	 * the mutex kernfs_mutex through kernfs_हटाओ_by_name_ns().
	 */
	btrfs_sysfs_del_one_qgroup(fs_info, qgroup);
	kमुक्त(qgroup);
out:
	mutex_unlock(&fs_info->qgroup_ioctl_lock);
	वापस ret;
पूर्ण

पूर्णांक btrfs_limit_qgroup(काष्ठा btrfs_trans_handle *trans, u64 qgroupid,
		       काष्ठा btrfs_qgroup_limit *limit)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_qgroup *qgroup;
	पूर्णांक ret = 0;
	/* Someबार we would want to clear the limit on this qgroup.
	 * To meet this requirement, we treat the -1 as a special value
	 * which tell kernel to clear the limit on this qgroup.
	 */
	स्थिर u64 CLEAR_VALUE = -1;

	mutex_lock(&fs_info->qgroup_ioctl_lock);
	अगर (!fs_info->quota_root) अणु
		ret = -ENOTCONN;
		जाओ out;
	पूर्ण

	qgroup = find_qgroup_rb(fs_info, qgroupid);
	अगर (!qgroup) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	spin_lock(&fs_info->qgroup_lock);
	अगर (limit->flags & BTRFS_QGROUP_LIMIT_MAX_RFER) अणु
		अगर (limit->max_rfer == CLEAR_VALUE) अणु
			qgroup->lim_flags &= ~BTRFS_QGROUP_LIMIT_MAX_RFER;
			limit->flags &= ~BTRFS_QGROUP_LIMIT_MAX_RFER;
			qgroup->max_rfer = 0;
		पूर्ण अन्यथा अणु
			qgroup->max_rfer = limit->max_rfer;
		पूर्ण
	पूर्ण
	अगर (limit->flags & BTRFS_QGROUP_LIMIT_MAX_EXCL) अणु
		अगर (limit->max_excl == CLEAR_VALUE) अणु
			qgroup->lim_flags &= ~BTRFS_QGROUP_LIMIT_MAX_EXCL;
			limit->flags &= ~BTRFS_QGROUP_LIMIT_MAX_EXCL;
			qgroup->max_excl = 0;
		पूर्ण अन्यथा अणु
			qgroup->max_excl = limit->max_excl;
		पूर्ण
	पूर्ण
	अगर (limit->flags & BTRFS_QGROUP_LIMIT_RSV_RFER) अणु
		अगर (limit->rsv_rfer == CLEAR_VALUE) अणु
			qgroup->lim_flags &= ~BTRFS_QGROUP_LIMIT_RSV_RFER;
			limit->flags &= ~BTRFS_QGROUP_LIMIT_RSV_RFER;
			qgroup->rsv_rfer = 0;
		पूर्ण अन्यथा अणु
			qgroup->rsv_rfer = limit->rsv_rfer;
		पूर्ण
	पूर्ण
	अगर (limit->flags & BTRFS_QGROUP_LIMIT_RSV_EXCL) अणु
		अगर (limit->rsv_excl == CLEAR_VALUE) अणु
			qgroup->lim_flags &= ~BTRFS_QGROUP_LIMIT_RSV_EXCL;
			limit->flags &= ~BTRFS_QGROUP_LIMIT_RSV_EXCL;
			qgroup->rsv_excl = 0;
		पूर्ण अन्यथा अणु
			qgroup->rsv_excl = limit->rsv_excl;
		पूर्ण
	पूर्ण
	qgroup->lim_flags |= limit->flags;

	spin_unlock(&fs_info->qgroup_lock);

	ret = update_qgroup_limit_item(trans, qgroup);
	अगर (ret) अणु
		fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
		btrfs_info(fs_info, "unable to update quota limit for %llu",
		       qgroupid);
	पूर्ण

out:
	mutex_unlock(&fs_info->qgroup_ioctl_lock);
	वापस ret;
पूर्ण

पूर्णांक btrfs_qgroup_trace_extent_nolock(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा btrfs_delayed_ref_root *delayed_refs,
				काष्ठा btrfs_qgroup_extent_record *record)
अणु
	काष्ठा rb_node **p = &delayed_refs->dirty_extent_root.rb_node;
	काष्ठा rb_node *parent_node = शून्य;
	काष्ठा btrfs_qgroup_extent_record *entry;
	u64 bytenr = record->bytenr;

	lockdep_निश्चित_held(&delayed_refs->lock);
	trace_btrfs_qgroup_trace_extent(fs_info, record);

	जबतक (*p) अणु
		parent_node = *p;
		entry = rb_entry(parent_node, काष्ठा btrfs_qgroup_extent_record,
				 node);
		अगर (bytenr < entry->bytenr) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (bytenr > entry->bytenr) अणु
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			अगर (record->data_rsv && !entry->data_rsv) अणु
				entry->data_rsv = record->data_rsv;
				entry->data_rsv_refroot =
					record->data_rsv_refroot;
			पूर्ण
			वापस 1;
		पूर्ण
	पूर्ण

	rb_link_node(&record->node, parent_node, p);
	rb_insert_color(&record->node, &delayed_refs->dirty_extent_root);
	वापस 0;
पूर्ण

पूर्णांक btrfs_qgroup_trace_extent_post(काष्ठा btrfs_fs_info *fs_info,
				   काष्ठा btrfs_qgroup_extent_record *qrecord)
अणु
	काष्ठा ulist *old_root;
	u64 bytenr = qrecord->bytenr;
	पूर्णांक ret;

	ret = btrfs_find_all_roots(शून्य, fs_info, bytenr, 0, &old_root, false);
	अगर (ret < 0) अणु
		fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
		btrfs_warn(fs_info,
"error accounting new delayed refs extent (err code: %d), quota inconsistent",
			ret);
		वापस 0;
	पूर्ण

	/*
	 * Here we करोn't need to get the lock of
	 * trans->transaction->delayed_refs, since inserted qrecord won't
	 * be deleted, only qrecord->node may be modअगरied (new qrecord insert)
	 *
	 * So modअगरying qrecord->old_roots is safe here
	 */
	qrecord->old_roots = old_root;
	वापस 0;
पूर्ण

पूर्णांक btrfs_qgroup_trace_extent(काष्ठा btrfs_trans_handle *trans, u64 bytenr,
			      u64 num_bytes, gfp_t gfp_flag)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_qgroup_extent_record *record;
	काष्ठा btrfs_delayed_ref_root *delayed_refs;
	पूर्णांक ret;

	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags)
	    || bytenr == 0 || num_bytes == 0)
		वापस 0;
	record = kzalloc(माप(*record), gfp_flag);
	अगर (!record)
		वापस -ENOMEM;

	delayed_refs = &trans->transaction->delayed_refs;
	record->bytenr = bytenr;
	record->num_bytes = num_bytes;
	record->old_roots = शून्य;

	spin_lock(&delayed_refs->lock);
	ret = btrfs_qgroup_trace_extent_nolock(fs_info, delayed_refs, record);
	spin_unlock(&delayed_refs->lock);
	अगर (ret > 0) अणु
		kमुक्त(record);
		वापस 0;
	पूर्ण
	वापस btrfs_qgroup_trace_extent_post(fs_info, record);
पूर्ण

पूर्णांक btrfs_qgroup_trace_leaf_items(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा extent_buffer *eb)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक nr = btrfs_header_nritems(eb);
	पूर्णांक i, extent_type, ret;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_file_extent_item *fi;
	u64 bytenr, num_bytes;

	/* We can be called directly from walk_up_proc() */
	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags))
		वापस 0;

	क्रम (i = 0; i < nr; i++) अणु
		btrfs_item_key_to_cpu(eb, &key, i);

		अगर (key.type != BTRFS_EXTENT_DATA_KEY)
			जारी;

		fi = btrfs_item_ptr(eb, i, काष्ठा btrfs_file_extent_item);
		/* filter out non qgroup-accountable extents  */
		extent_type = btrfs_file_extent_type(eb, fi);

		अगर (extent_type == BTRFS_खाता_EXTENT_INLINE)
			जारी;

		bytenr = btrfs_file_extent_disk_bytenr(eb, fi);
		अगर (!bytenr)
			जारी;

		num_bytes = btrfs_file_extent_disk_num_bytes(eb, fi);

		ret = btrfs_qgroup_trace_extent(trans, bytenr, num_bytes,
						GFP_NOFS);
		अगर (ret)
			वापस ret;
	पूर्ण
	cond_resched();
	वापस 0;
पूर्ण

/*
 * Walk up the tree from the bottom, मुक्तing leaves and any पूर्णांकerior
 * nodes which have had all slots visited. If a node (leaf or
 * पूर्णांकerior) is मुक्तd, the node above it will have it's slot
 * incremented. The root node will never be मुक्तd.
 *
 * At the end of this function, we should have a path which has all
 * slots incremented to the next position क्रम a search. If we need to
 * पढ़ो a new node it will be शून्य and the node above it will have the
 * correct slot selected क्रम a later पढ़ो.
 *
 * If we increment the root nodes slot counter past the number of
 * elements, 1 is वापसed to संकेत completion of the search.
 */
अटल पूर्णांक adjust_slots_upwards(काष्ठा btrfs_path *path, पूर्णांक root_level)
अणु
	पूर्णांक level = 0;
	पूर्णांक nr, slot;
	काष्ठा extent_buffer *eb;

	अगर (root_level == 0)
		वापस 1;

	जबतक (level <= root_level) अणु
		eb = path->nodes[level];
		nr = btrfs_header_nritems(eb);
		path->slots[level]++;
		slot = path->slots[level];
		अगर (slot >= nr || level == 0) अणु
			/*
			 * Don't मुक्त the root -  we will detect this
			 * condition after our loop and वापस a
			 * positive value क्रम caller to stop walking the tree.
			 */
			अगर (level != root_level) अणु
				btrfs_tree_unlock_rw(eb, path->locks[level]);
				path->locks[level] = 0;

				मुक्त_extent_buffer(eb);
				path->nodes[level] = शून्य;
				path->slots[level] = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * We have a valid slot to walk back करोwn
			 * from. Stop here so caller can process these
			 * new nodes.
			 */
			अवरोध;
		पूर्ण

		level++;
	पूर्ण

	eb = path->nodes[root_level];
	अगर (path->slots[root_level] >= btrfs_header_nritems(eb))
		वापस 1;

	वापस 0;
पूर्ण

/*
 * Helper function to trace a subtree tree block swap.
 *
 * The swap will happen in highest tree block, but there may be a lot of
 * tree blocks involved.
 *
 * For example:
 *  OO = Old tree blocks
 *  NN = New tree blocks allocated during balance
 *
 *           File tree (257)                  Reloc tree क्रम 257
 * L2              OO                                NN
 *               /    \                            /    \
 * L1          OO      OO (a)                    OO      NN (a)
 *            / \     / \                       / \     / \
 * L0       OO   OO OO   OO                   OO   OO NN   NN
 *                  (b)  (c)                          (b)  (c)
 *
 * When calling qgroup_trace_extent_swap(), we will pass:
 * @src_eb = OO(a)
 * @dst_path = [ nodes[1] = NN(a), nodes[0] = NN(c) ]
 * @dst_level = 0
 * @root_level = 1
 *
 * In that हाल, qgroup_trace_extent_swap() will search from OO(a) to
 * reach OO(c), then mark both OO(c) and NN(c) as qgroup dirty.
 *
 * The मुख्य work of qgroup_trace_extent_swap() can be split पूर्णांकo 3 parts:
 *
 * 1) Tree search from @src_eb
 *    It should acts as a simplअगरied btrfs_search_slot().
 *    The key क्रम search can be extracted from @dst_path->nodes[dst_level]
 *    (first key).
 *
 * 2) Mark the final tree blocks in @src_path and @dst_path qgroup dirty
 *    NOTE: In above हाल, OO(a) and NN(a) won't be marked qgroup dirty.
 *    They should be marked during previous (@dst_level = 1) iteration.
 *
 * 3) Mark file extents in leaves dirty
 *    We करोn't have good way to pick out new file extents only.
 *    So we still follow the old method by scanning all file extents in
 *    the leave.
 *
 * This function can मुक्त us from keeping two paths, thus later we only need
 * to care about how to iterate all new tree blocks in reloc tree.
 */
अटल पूर्णांक qgroup_trace_extent_swap(काष्ठा btrfs_trans_handle* trans,
				    काष्ठा extent_buffer *src_eb,
				    काष्ठा btrfs_path *dst_path,
				    पूर्णांक dst_level, पूर्णांक root_level,
				    bool trace_leaf)
अणु
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *src_path;
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	u32 nodesize = fs_info->nodesize;
	पूर्णांक cur_level = root_level;
	पूर्णांक ret;

	BUG_ON(dst_level > root_level);
	/* Level mismatch */
	अगर (btrfs_header_level(src_eb) != root_level)
		वापस -EINVAL;

	src_path = btrfs_alloc_path();
	अगर (!src_path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (dst_level)
		btrfs_node_key_to_cpu(dst_path->nodes[dst_level], &key, 0);
	अन्यथा
		btrfs_item_key_to_cpu(dst_path->nodes[dst_level], &key, 0);

	/* For src_path */
	atomic_inc(&src_eb->refs);
	src_path->nodes[root_level] = src_eb;
	src_path->slots[root_level] = dst_path->slots[root_level];
	src_path->locks[root_level] = 0;

	/* A simplअगरied version of btrfs_search_slot() */
	जबतक (cur_level >= dst_level) अणु
		काष्ठा btrfs_key src_key;
		काष्ठा btrfs_key dst_key;

		अगर (src_path->nodes[cur_level] == शून्य) अणु
			काष्ठा extent_buffer *eb;
			पूर्णांक parent_slot;

			eb = src_path->nodes[cur_level + 1];
			parent_slot = src_path->slots[cur_level + 1];

			eb = btrfs_पढ़ो_node_slot(eb, parent_slot);
			अगर (IS_ERR(eb)) अणु
				ret = PTR_ERR(eb);
				जाओ out;
			पूर्ण

			src_path->nodes[cur_level] = eb;

			btrfs_tree_पढ़ो_lock(eb);
			src_path->locks[cur_level] = BTRFS_READ_LOCK;
		पूर्ण

		src_path->slots[cur_level] = dst_path->slots[cur_level];
		अगर (cur_level) अणु
			btrfs_node_key_to_cpu(dst_path->nodes[cur_level],
					&dst_key, dst_path->slots[cur_level]);
			btrfs_node_key_to_cpu(src_path->nodes[cur_level],
					&src_key, src_path->slots[cur_level]);
		पूर्ण अन्यथा अणु
			btrfs_item_key_to_cpu(dst_path->nodes[cur_level],
					&dst_key, dst_path->slots[cur_level]);
			btrfs_item_key_to_cpu(src_path->nodes[cur_level],
					&src_key, src_path->slots[cur_level]);
		पूर्ण
		/* Content mismatch, something went wrong */
		अगर (btrfs_comp_cpu_keys(&dst_key, &src_key)) अणु
			ret = -ENOENT;
			जाओ out;
		पूर्ण
		cur_level--;
	पूर्ण

	/*
	 * Now both @dst_path and @src_path have been populated, record the tree
	 * blocks क्रम qgroup accounting.
	 */
	ret = btrfs_qgroup_trace_extent(trans, src_path->nodes[dst_level]->start,
			nodesize, GFP_NOFS);
	अगर (ret < 0)
		जाओ out;
	ret = btrfs_qgroup_trace_extent(trans,
			dst_path->nodes[dst_level]->start,
			nodesize, GFP_NOFS);
	अगर (ret < 0)
		जाओ out;

	/* Record leaf file extents */
	अगर (dst_level == 0 && trace_leaf) अणु
		ret = btrfs_qgroup_trace_leaf_items(trans, src_path->nodes[0]);
		अगर (ret < 0)
			जाओ out;
		ret = btrfs_qgroup_trace_leaf_items(trans, dst_path->nodes[0]);
	पूर्ण
out:
	btrfs_मुक्त_path(src_path);
	वापस ret;
पूर्ण

/*
 * Helper function to करो recursive generation-aware depth-first search, to
 * locate all new tree blocks in a subtree of reloc tree.
 *
 * E.g. (OO = Old tree blocks, NN = New tree blocks, whose gen == last_snapshot)
 *         reloc tree
 * L2         NN (a)
 *          /    \
 * L1    OO        NN (b)
 *      /  \      /  \
 * L0  OO  OO    OO  NN
 *               (c) (d)
 * If we pass:
 * @dst_path = [ nodes[1] = NN(b), nodes[0] = शून्य ],
 * @cur_level = 1
 * @root_level = 1
 *
 * We will iterate through tree blocks NN(b), NN(d) and info qgroup to trace
 * above tree blocks aदीर्घ with their counter parts in file tree.
 * While during search, old tree blocks OO(c) will be skipped as tree block swap
 * won't affect OO(c).
 */
अटल पूर्णांक qgroup_trace_new_subtree_blocks(काष्ठा btrfs_trans_handle* trans,
					   काष्ठा extent_buffer *src_eb,
					   काष्ठा btrfs_path *dst_path,
					   पूर्णांक cur_level, पूर्णांक root_level,
					   u64 last_snapshot, bool trace_leaf)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा extent_buffer *eb;
	bool need_cleanup = false;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* Level sanity check */
	अगर (cur_level < 0 || cur_level >= BTRFS_MAX_LEVEL - 1 ||
	    root_level < 0 || root_level >= BTRFS_MAX_LEVEL - 1 ||
	    root_level < cur_level) अणु
		btrfs_err_rl(fs_info,
			"%s: bad levels, cur_level=%d root_level=%d",
			__func__, cur_level, root_level);
		वापस -EUCLEAN;
	पूर्ण

	/* Read the tree block अगर needed */
	अगर (dst_path->nodes[cur_level] == शून्य) अणु
		पूर्णांक parent_slot;
		u64 child_gen;

		/*
		 * dst_path->nodes[root_level] must be initialized beक्रमe
		 * calling this function.
		 */
		अगर (cur_level == root_level) अणु
			btrfs_err_rl(fs_info,
	"%s: dst_path->nodes[%d] not initialized, root_level=%d cur_level=%d",
				__func__, root_level, root_level, cur_level);
			वापस -EUCLEAN;
		पूर्ण

		/*
		 * We need to get child blockptr/gen from parent beक्रमe we can
		 * पढ़ो it.
		  */
		eb = dst_path->nodes[cur_level + 1];
		parent_slot = dst_path->slots[cur_level + 1];
		child_gen = btrfs_node_ptr_generation(eb, parent_slot);

		/* This node is old, no need to trace */
		अगर (child_gen < last_snapshot)
			जाओ out;

		eb = btrfs_पढ़ो_node_slot(eb, parent_slot);
		अगर (IS_ERR(eb)) अणु
			ret = PTR_ERR(eb);
			जाओ out;
		पूर्ण

		dst_path->nodes[cur_level] = eb;
		dst_path->slots[cur_level] = 0;

		btrfs_tree_पढ़ो_lock(eb);
		dst_path->locks[cur_level] = BTRFS_READ_LOCK;
		need_cleanup = true;
	पूर्ण

	/* Now record this tree block and its counter part क्रम qgroups */
	ret = qgroup_trace_extent_swap(trans, src_eb, dst_path, cur_level,
				       root_level, trace_leaf);
	अगर (ret < 0)
		जाओ cleanup;

	eb = dst_path->nodes[cur_level];

	अगर (cur_level > 0) अणु
		/* Iterate all child tree blocks */
		क्रम (i = 0; i < btrfs_header_nritems(eb); i++) अणु
			/* Skip old tree blocks as they won't be swapped */
			अगर (btrfs_node_ptr_generation(eb, i) < last_snapshot)
				जारी;
			dst_path->slots[cur_level] = i;

			/* Recursive call (at most 7 बार) */
			ret = qgroup_trace_new_subtree_blocks(trans, src_eb,
					dst_path, cur_level - 1, root_level,
					last_snapshot, trace_leaf);
			अगर (ret < 0)
				जाओ cleanup;
		पूर्ण
	पूर्ण

cleanup:
	अगर (need_cleanup) अणु
		/* Clean up */
		btrfs_tree_unlock_rw(dst_path->nodes[cur_level],
				     dst_path->locks[cur_level]);
		मुक्त_extent_buffer(dst_path->nodes[cur_level]);
		dst_path->nodes[cur_level] = शून्य;
		dst_path->slots[cur_level] = 0;
		dst_path->locks[cur_level] = 0;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक qgroup_trace_subtree_swap(काष्ठा btrfs_trans_handle *trans,
				काष्ठा extent_buffer *src_eb,
				काष्ठा extent_buffer *dst_eb,
				u64 last_snapshot, bool trace_leaf)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_path *dst_path = शून्य;
	पूर्णांक level;
	पूर्णांक ret;

	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags))
		वापस 0;

	/* Wrong parameter order */
	अगर (btrfs_header_generation(src_eb) > btrfs_header_generation(dst_eb)) अणु
		btrfs_err_rl(fs_info,
		"%s: bad parameter order, src_gen=%llu dst_gen=%llu", __func__,
			     btrfs_header_generation(src_eb),
			     btrfs_header_generation(dst_eb));
		वापस -EUCLEAN;
	पूर्ण

	अगर (!extent_buffer_uptodate(src_eb) || !extent_buffer_uptodate(dst_eb)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	level = btrfs_header_level(dst_eb);
	dst_path = btrfs_alloc_path();
	अगर (!dst_path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	/* For dst_path */
	atomic_inc(&dst_eb->refs);
	dst_path->nodes[level] = dst_eb;
	dst_path->slots[level] = 0;
	dst_path->locks[level] = 0;

	/* Do the generation aware bपढ़ोth-first search */
	ret = qgroup_trace_new_subtree_blocks(trans, src_eb, dst_path, level,
					      level, last_snapshot, trace_leaf);
	अगर (ret < 0)
		जाओ out;
	ret = 0;

out:
	btrfs_मुक्त_path(dst_path);
	अगर (ret < 0)
		fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
	वापस ret;
पूर्ण

पूर्णांक btrfs_qgroup_trace_subtree(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा extent_buffer *root_eb,
			       u64 root_gen, पूर्णांक root_level)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक ret = 0;
	पूर्णांक level;
	काष्ठा extent_buffer *eb = root_eb;
	काष्ठा btrfs_path *path = शून्य;

	BUG_ON(root_level < 0 || root_level >= BTRFS_MAX_LEVEL);
	BUG_ON(root_eb == शून्य);

	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags))
		वापस 0;

	अगर (!extent_buffer_uptodate(root_eb)) अणु
		ret = btrfs_पढ़ो_buffer(root_eb, root_gen, root_level, शून्य);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (root_level == 0) अणु
		ret = btrfs_qgroup_trace_leaf_items(trans, root_eb);
		जाओ out;
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	/*
	 * Walk करोwn the tree.  Missing extent blocks are filled in as
	 * we go. Metadata is accounted every समय we पढ़ो a new
	 * extent block.
	 *
	 * When we reach a leaf, we account क्रम file extent items in it,
	 * walk back up the tree (adjusting slot poपूर्णांकers as we go)
	 * and restart the search process.
	 */
	atomic_inc(&root_eb->refs);	/* For path */
	path->nodes[root_level] = root_eb;
	path->slots[root_level] = 0;
	path->locks[root_level] = 0; /* so release_path करोesn't try to unlock */
walk_करोwn:
	level = root_level;
	जबतक (level >= 0) अणु
		अगर (path->nodes[level] == शून्य) अणु
			पूर्णांक parent_slot;
			u64 child_bytenr;

			/*
			 * We need to get child blockptr from parent beक्रमe we
			 * can पढ़ो it.
			  */
			eb = path->nodes[level + 1];
			parent_slot = path->slots[level + 1];
			child_bytenr = btrfs_node_blockptr(eb, parent_slot);

			eb = btrfs_पढ़ो_node_slot(eb, parent_slot);
			अगर (IS_ERR(eb)) अणु
				ret = PTR_ERR(eb);
				जाओ out;
			पूर्ण

			path->nodes[level] = eb;
			path->slots[level] = 0;

			btrfs_tree_पढ़ो_lock(eb);
			path->locks[level] = BTRFS_READ_LOCK;

			ret = btrfs_qgroup_trace_extent(trans, child_bytenr,
							fs_info->nodesize,
							GFP_NOFS);
			अगर (ret)
				जाओ out;
		पूर्ण

		अगर (level == 0) अणु
			ret = btrfs_qgroup_trace_leaf_items(trans,
							    path->nodes[level]);
			अगर (ret)
				जाओ out;

			/* Nonzero वापस here means we completed our search */
			ret = adjust_slots_upwards(path, root_level);
			अगर (ret)
				अवरोध;

			/* Restart search with new slots */
			जाओ walk_करोwn;
		पूर्ण

		level--;
	पूर्ण

	ret = 0;
out:
	btrfs_मुक्त_path(path);

	वापस ret;
पूर्ण

#घोषणा UPDATE_NEW	0
#घोषणा UPDATE_OLD	1
/*
 * Walk all of the roots that poपूर्णांकs to the bytenr and adjust their refcnts.
 */
अटल पूर्णांक qgroup_update_refcnt(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा ulist *roots, काष्ठा ulist *पंचांगp,
				काष्ठा ulist *qgroups, u64 seq, पूर्णांक update_old)
अणु
	काष्ठा ulist_node *unode;
	काष्ठा ulist_iterator uiter;
	काष्ठा ulist_node *पंचांगp_unode;
	काष्ठा ulist_iterator पंचांगp_uiter;
	काष्ठा btrfs_qgroup *qg;
	पूर्णांक ret = 0;

	अगर (!roots)
		वापस 0;
	ULIST_ITER_INIT(&uiter);
	जबतक ((unode = ulist_next(roots, &uiter))) अणु
		qg = find_qgroup_rb(fs_info, unode->val);
		अगर (!qg)
			जारी;

		ulist_reinit(पंचांगp);
		ret = ulist_add(qgroups, qg->qgroupid, qgroup_to_aux(qg),
				GFP_ATOMIC);
		अगर (ret < 0)
			वापस ret;
		ret = ulist_add(पंचांगp, qg->qgroupid, qgroup_to_aux(qg), GFP_ATOMIC);
		अगर (ret < 0)
			वापस ret;
		ULIST_ITER_INIT(&पंचांगp_uiter);
		जबतक ((पंचांगp_unode = ulist_next(पंचांगp, &पंचांगp_uiter))) अणु
			काष्ठा btrfs_qgroup_list *glist;

			qg = unode_aux_to_qgroup(पंचांगp_unode);
			अगर (update_old)
				btrfs_qgroup_update_old_refcnt(qg, seq, 1);
			अन्यथा
				btrfs_qgroup_update_new_refcnt(qg, seq, 1);
			list_क्रम_each_entry(glist, &qg->groups, next_group) अणु
				ret = ulist_add(qgroups, glist->group->qgroupid,
						qgroup_to_aux(glist->group),
						GFP_ATOMIC);
				अगर (ret < 0)
					वापस ret;
				ret = ulist_add(पंचांगp, glist->group->qgroupid,
						qgroup_to_aux(glist->group),
						GFP_ATOMIC);
				अगर (ret < 0)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Update qgroup rfer/excl counters.
 * Rfer update is easy, codes can explain themselves.
 *
 * Excl update is tricky, the update is split पूर्णांकo 2 parts.
 * Part 1: Possible exclusive <-> sharing detect:
 *	|	A	|	!A	|
 *  -------------------------------------
 *  B	|	*	|	-	|
 *  -------------------------------------
 *  !B	|	+	|	**	|
 *  -------------------------------------
 *
 * Conditions:
 * A:	cur_old_roots < nr_old_roots	(not exclusive beक्रमe)
 * !A:	cur_old_roots == nr_old_roots	(possible exclusive beक्रमe)
 * B:	cur_new_roots < nr_new_roots	(not exclusive now)
 * !B:	cur_new_roots == nr_new_roots	(possible exclusive now)
 *
 * Results:
 * +: Possible sharing -> exclusive	-: Possible exclusive -> sharing
 * *: Definitely not changed.		**: Possible unchanged.
 *
 * For !A and !B condition, the exception is cur_old/new_roots == 0 हाल.
 *
 * To make the logic clear, we first use condition A and B to split
 * combination पूर्णांकo 4 results.
 *
 * Then, क्रम result "+" and "-", check old/new_roots == 0 हाल, as in them
 * only on variant maybe 0.
 *
 * Lastly, check result **, since there are 2 variants maybe 0, split them
 * again(2x2).
 * But this समय we करोn't need to consider other things, the codes and logic
 * is easy to understand now.
 */
अटल पूर्णांक qgroup_update_counters(काष्ठा btrfs_fs_info *fs_info,
				  काष्ठा ulist *qgroups,
				  u64 nr_old_roots,
				  u64 nr_new_roots,
				  u64 num_bytes, u64 seq)
अणु
	काष्ठा ulist_node *unode;
	काष्ठा ulist_iterator uiter;
	काष्ठा btrfs_qgroup *qg;
	u64 cur_new_count, cur_old_count;

	ULIST_ITER_INIT(&uiter);
	जबतक ((unode = ulist_next(qgroups, &uiter))) अणु
		bool dirty = false;

		qg = unode_aux_to_qgroup(unode);
		cur_old_count = btrfs_qgroup_get_old_refcnt(qg, seq);
		cur_new_count = btrfs_qgroup_get_new_refcnt(qg, seq);

		trace_qgroup_update_counters(fs_info, qg, cur_old_count,
					     cur_new_count);

		/* Rfer update part */
		अगर (cur_old_count == 0 && cur_new_count > 0) अणु
			qg->rfer += num_bytes;
			qg->rfer_cmpr += num_bytes;
			dirty = true;
		पूर्ण
		अगर (cur_old_count > 0 && cur_new_count == 0) अणु
			qg->rfer -= num_bytes;
			qg->rfer_cmpr -= num_bytes;
			dirty = true;
		पूर्ण

		/* Excl update part */
		/* Exclusive/none -> shared हाल */
		अगर (cur_old_count == nr_old_roots &&
		    cur_new_count < nr_new_roots) अणु
			/* Exclusive -> shared */
			अगर (cur_old_count != 0) अणु
				qg->excl -= num_bytes;
				qg->excl_cmpr -= num_bytes;
				dirty = true;
			पूर्ण
		पूर्ण

		/* Shared -> exclusive/none हाल */
		अगर (cur_old_count < nr_old_roots &&
		    cur_new_count == nr_new_roots) अणु
			/* Shared->exclusive */
			अगर (cur_new_count != 0) अणु
				qg->excl += num_bytes;
				qg->excl_cmpr += num_bytes;
				dirty = true;
			पूर्ण
		पूर्ण

		/* Exclusive/none -> exclusive/none हाल */
		अगर (cur_old_count == nr_old_roots &&
		    cur_new_count == nr_new_roots) अणु
			अगर (cur_old_count == 0) अणु
				/* None -> exclusive/none */

				अगर (cur_new_count != 0) अणु
					/* None -> exclusive */
					qg->excl += num_bytes;
					qg->excl_cmpr += num_bytes;
					dirty = true;
				पूर्ण
				/* None -> none, nothing changed */
			पूर्ण अन्यथा अणु
				/* Exclusive -> exclusive/none */

				अगर (cur_new_count == 0) अणु
					/* Exclusive -> none */
					qg->excl -= num_bytes;
					qg->excl_cmpr -= num_bytes;
					dirty = true;
				पूर्ण
				/* Exclusive -> exclusive, nothing changed */
			पूर्ण
		पूर्ण

		अगर (dirty)
			qgroup_dirty(fs_info, qg);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Check अगर the @roots potentially is a list of fs tree roots
 *
 * Return 0 क्रम definitely not a fs/subvol tree roots ulist
 * Return 1 क्रम possible fs/subvol tree roots in the list (considering an empty
 *          one as well)
 */
अटल पूर्णांक maybe_fs_roots(काष्ठा ulist *roots)
अणु
	काष्ठा ulist_node *unode;
	काष्ठा ulist_iterator uiter;

	/* Empty one, still possible क्रम fs roots */
	अगर (!roots || roots->nnodes == 0)
		वापस 1;

	ULIST_ITER_INIT(&uiter);
	unode = ulist_next(roots, &uiter);
	अगर (!unode)
		वापस 1;

	/*
	 * If it contains fs tree roots, then it must beदीर्घ to fs/subvol
	 * trees.
	 * If it contains a non-fs tree, it won't be shared with fs/subvol trees.
	 */
	वापस is_fstree(unode->val);
पूर्ण

पूर्णांक btrfs_qgroup_account_extent(काष्ठा btrfs_trans_handle *trans, u64 bytenr,
				u64 num_bytes, काष्ठा ulist *old_roots,
				काष्ठा ulist *new_roots)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा ulist *qgroups = शून्य;
	काष्ठा ulist *पंचांगp = शून्य;
	u64 seq;
	u64 nr_new_roots = 0;
	u64 nr_old_roots = 0;
	पूर्णांक ret = 0;

	/*
	 * If quotas get disabled meanजबतक, the resouces need to be मुक्तd and
	 * we can't just निकास here.
	 */
	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags))
		जाओ out_मुक्त;

	अगर (new_roots) अणु
		अगर (!maybe_fs_roots(new_roots))
			जाओ out_मुक्त;
		nr_new_roots = new_roots->nnodes;
	पूर्ण
	अगर (old_roots) अणु
		अगर (!maybe_fs_roots(old_roots))
			जाओ out_मुक्त;
		nr_old_roots = old_roots->nnodes;
	पूर्ण

	/* Quick निकास, either not fs tree roots, or won't affect any qgroup */
	अगर (nr_old_roots == 0 && nr_new_roots == 0)
		जाओ out_मुक्त;

	BUG_ON(!fs_info->quota_root);

	trace_btrfs_qgroup_account_extent(fs_info, trans->transid, bytenr,
					num_bytes, nr_old_roots, nr_new_roots);

	qgroups = ulist_alloc(GFP_NOFS);
	अगर (!qgroups) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	पंचांगp = ulist_alloc(GFP_NOFS);
	अगर (!पंचांगp) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	mutex_lock(&fs_info->qgroup_rescan_lock);
	अगर (fs_info->qgroup_flags & BTRFS_QGROUP_STATUS_FLAG_RESCAN) अणु
		अगर (fs_info->qgroup_rescan_progress.objectid <= bytenr) अणु
			mutex_unlock(&fs_info->qgroup_rescan_lock);
			ret = 0;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण
	mutex_unlock(&fs_info->qgroup_rescan_lock);

	spin_lock(&fs_info->qgroup_lock);
	seq = fs_info->qgroup_seq;

	/* Update old refcnts using old_roots */
	ret = qgroup_update_refcnt(fs_info, old_roots, पंचांगp, qgroups, seq,
				   UPDATE_OLD);
	अगर (ret < 0)
		जाओ out;

	/* Update new refcnts using new_roots */
	ret = qgroup_update_refcnt(fs_info, new_roots, पंचांगp, qgroups, seq,
				   UPDATE_NEW);
	अगर (ret < 0)
		जाओ out;

	qgroup_update_counters(fs_info, qgroups, nr_old_roots, nr_new_roots,
			       num_bytes, seq);

	/*
	 * Bump qgroup_seq to aव्योम seq overlap
	 */
	fs_info->qgroup_seq += max(nr_old_roots, nr_new_roots) + 1;
out:
	spin_unlock(&fs_info->qgroup_lock);
out_मुक्त:
	ulist_मुक्त(पंचांगp);
	ulist_मुक्त(qgroups);
	ulist_मुक्त(old_roots);
	ulist_मुक्त(new_roots);
	वापस ret;
पूर्ण

पूर्णांक btrfs_qgroup_account_extents(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_qgroup_extent_record *record;
	काष्ठा btrfs_delayed_ref_root *delayed_refs;
	काष्ठा ulist *new_roots = शून्य;
	काष्ठा rb_node *node;
	u64 num_dirty_extents = 0;
	u64 qgroup_to_skip;
	पूर्णांक ret = 0;

	delayed_refs = &trans->transaction->delayed_refs;
	qgroup_to_skip = delayed_refs->qgroup_to_skip;
	जबतक ((node = rb_first(&delayed_refs->dirty_extent_root))) अणु
		record = rb_entry(node, काष्ठा btrfs_qgroup_extent_record,
				  node);

		num_dirty_extents++;
		trace_btrfs_qgroup_account_extents(fs_info, record);

		अगर (!ret) अणु
			/*
			 * Old roots should be searched when inserting qgroup
			 * extent record
			 */
			अगर (WARN_ON(!record->old_roots)) अणु
				/* Search commit root to find old_roots */
				ret = btrfs_find_all_roots(शून्य, fs_info,
						record->bytenr, 0,
						&record->old_roots, false);
				अगर (ret < 0)
					जाओ cleanup;
			पूर्ण

			/* Free the reserved data space */
			btrfs_qgroup_मुक्त_refroot(fs_info,
					record->data_rsv_refroot,
					record->data_rsv,
					BTRFS_QGROUP_RSV_DATA);
			/*
			 * Use BTRFS_SEQ_LAST as समय_seq to करो special search,
			 * which करोesn't lock tree or delayed_refs and search
			 * current root. It's safe inside commit_transaction().
			 */
			ret = btrfs_find_all_roots(trans, fs_info,
				record->bytenr, BTRFS_SEQ_LAST, &new_roots, false);
			अगर (ret < 0)
				जाओ cleanup;
			अगर (qgroup_to_skip) अणु
				ulist_del(new_roots, qgroup_to_skip, 0);
				ulist_del(record->old_roots, qgroup_to_skip,
					  0);
			पूर्ण
			ret = btrfs_qgroup_account_extent(trans, record->bytenr,
							  record->num_bytes,
							  record->old_roots,
							  new_roots);
			record->old_roots = शून्य;
			new_roots = शून्य;
		पूर्ण
cleanup:
		ulist_मुक्त(record->old_roots);
		ulist_मुक्त(new_roots);
		new_roots = शून्य;
		rb_erase(node, &delayed_refs->dirty_extent_root);
		kमुक्त(record);

	पूर्ण
	trace_qgroup_num_dirty_extents(fs_info, trans->transid,
				       num_dirty_extents);
	वापस ret;
पूर्ण

/*
 * called from commit_transaction. Writes all changed qgroups to disk.
 */
पूर्णांक btrfs_run_qgroups(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक ret = 0;

	अगर (!fs_info->quota_root)
		वापस ret;

	spin_lock(&fs_info->qgroup_lock);
	जबतक (!list_empty(&fs_info->dirty_qgroups)) अणु
		काष्ठा btrfs_qgroup *qgroup;
		qgroup = list_first_entry(&fs_info->dirty_qgroups,
					  काष्ठा btrfs_qgroup, dirty);
		list_del_init(&qgroup->dirty);
		spin_unlock(&fs_info->qgroup_lock);
		ret = update_qgroup_info_item(trans, qgroup);
		अगर (ret)
			fs_info->qgroup_flags |=
					BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
		ret = update_qgroup_limit_item(trans, qgroup);
		अगर (ret)
			fs_info->qgroup_flags |=
					BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
		spin_lock(&fs_info->qgroup_lock);
	पूर्ण
	अगर (test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags))
		fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_ON;
	अन्यथा
		fs_info->qgroup_flags &= ~BTRFS_QGROUP_STATUS_FLAG_ON;
	spin_unlock(&fs_info->qgroup_lock);

	ret = update_qgroup_status_item(trans);
	अगर (ret)
		fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;

	वापस ret;
पूर्ण

/*
 * Copy the accounting inक्रमmation between qgroups. This is necessary
 * when a snapshot or a subvolume is created. Throwing an error will
 * cause a transaction पात so we take extra care here to only error
 * when a पढ़ोonly fs is a reasonable outcome.
 */
पूर्णांक btrfs_qgroup_inherit(काष्ठा btrfs_trans_handle *trans, u64 srcid,
			 u64 objectid, काष्ठा btrfs_qgroup_inherit *inherit)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;
	u64 *i_qgroups;
	bool committing = false;
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *quota_root;
	काष्ठा btrfs_qgroup *srcgroup;
	काष्ठा btrfs_qgroup *dstgroup;
	bool need_rescan = false;
	u32 level_size = 0;
	u64 nums;

	/*
	 * There are only two callers of this function.
	 *
	 * One in create_subvol() in the ioctl context, which needs to hold
	 * the qgroup_ioctl_lock.
	 *
	 * The other one in create_pending_snapshot() where no other qgroup
	 * code can modअगरy the fs as they all need to either start a new trans
	 * or hold a trans handler, thus we करोn't need to hold
	 * qgroup_ioctl_lock.
	 * This would aव्योम दीर्घ and complex lock chain and make lockdep happy.
	 */
	spin_lock(&fs_info->trans_lock);
	अगर (trans->transaction->state == TRANS_STATE_COMMIT_DOING)
		committing = true;
	spin_unlock(&fs_info->trans_lock);

	अगर (!committing)
		mutex_lock(&fs_info->qgroup_ioctl_lock);
	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags))
		जाओ out;

	quota_root = fs_info->quota_root;
	अगर (!quota_root) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (inherit) अणु
		i_qgroups = (u64 *)(inherit + 1);
		nums = inherit->num_qgroups + 2 * inherit->num_ref_copies +
		       2 * inherit->num_excl_copies;
		क्रम (i = 0; i < nums; ++i) अणु
			srcgroup = find_qgroup_rb(fs_info, *i_qgroups);

			/*
			 * Zero out invalid groups so we can ignore
			 * them later.
			 */
			अगर (!srcgroup ||
			    ((srcgroup->qgroupid >> 48) <= (objectid >> 48)))
				*i_qgroups = 0ULL;

			++i_qgroups;
		पूर्ण
	पूर्ण

	/*
	 * create a tracking group क्रम the subvol itself
	 */
	ret = add_qgroup_item(trans, quota_root, objectid);
	अगर (ret)
		जाओ out;

	/*
	 * add qgroup to all inherited groups
	 */
	अगर (inherit) अणु
		i_qgroups = (u64 *)(inherit + 1);
		क्रम (i = 0; i < inherit->num_qgroups; ++i, ++i_qgroups) अणु
			अगर (*i_qgroups == 0)
				जारी;
			ret = add_qgroup_relation_item(trans, objectid,
						       *i_qgroups);
			अगर (ret && ret != -EEXIST)
				जाओ out;
			ret = add_qgroup_relation_item(trans, *i_qgroups,
						       objectid);
			अगर (ret && ret != -EEXIST)
				जाओ out;
		पूर्ण
		ret = 0;
	पूर्ण


	spin_lock(&fs_info->qgroup_lock);

	dstgroup = add_qgroup_rb(fs_info, objectid);
	अगर (IS_ERR(dstgroup)) अणु
		ret = PTR_ERR(dstgroup);
		जाओ unlock;
	पूर्ण

	अगर (inherit && inherit->flags & BTRFS_QGROUP_INHERIT_SET_LIMITS) अणु
		dstgroup->lim_flags = inherit->lim.flags;
		dstgroup->max_rfer = inherit->lim.max_rfer;
		dstgroup->max_excl = inherit->lim.max_excl;
		dstgroup->rsv_rfer = inherit->lim.rsv_rfer;
		dstgroup->rsv_excl = inherit->lim.rsv_excl;

		ret = update_qgroup_limit_item(trans, dstgroup);
		अगर (ret) अणु
			fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
			btrfs_info(fs_info,
				   "unable to update quota limit for %llu",
				   dstgroup->qgroupid);
			जाओ unlock;
		पूर्ण
	पूर्ण

	अगर (srcid) अणु
		srcgroup = find_qgroup_rb(fs_info, srcid);
		अगर (!srcgroup)
			जाओ unlock;

		/*
		 * We call inherit after we clone the root in order to make sure
		 * our counts करोn't go crazy, so at this poपूर्णांक the only
		 * dअगरference between the two roots should be the root node.
		 */
		level_size = fs_info->nodesize;
		dstgroup->rfer = srcgroup->rfer;
		dstgroup->rfer_cmpr = srcgroup->rfer_cmpr;
		dstgroup->excl = level_size;
		dstgroup->excl_cmpr = level_size;
		srcgroup->excl = level_size;
		srcgroup->excl_cmpr = level_size;

		/* inherit the limit info */
		dstgroup->lim_flags = srcgroup->lim_flags;
		dstgroup->max_rfer = srcgroup->max_rfer;
		dstgroup->max_excl = srcgroup->max_excl;
		dstgroup->rsv_rfer = srcgroup->rsv_rfer;
		dstgroup->rsv_excl = srcgroup->rsv_excl;

		qgroup_dirty(fs_info, dstgroup);
		qgroup_dirty(fs_info, srcgroup);
	पूर्ण

	अगर (!inherit)
		जाओ unlock;

	i_qgroups = (u64 *)(inherit + 1);
	क्रम (i = 0; i < inherit->num_qgroups; ++i) अणु
		अगर (*i_qgroups) अणु
			ret = add_relation_rb(fs_info, objectid, *i_qgroups);
			अगर (ret)
				जाओ unlock;
		पूर्ण
		++i_qgroups;

		/*
		 * If we're करोing a snapshot, and adding the snapshot to a new
		 * qgroup, the numbers are guaranteed to be incorrect.
		 */
		अगर (srcid)
			need_rescan = true;
	पूर्ण

	क्रम (i = 0; i <  inherit->num_ref_copies; ++i, i_qgroups += 2) अणु
		काष्ठा btrfs_qgroup *src;
		काष्ठा btrfs_qgroup *dst;

		अगर (!i_qgroups[0] || !i_qgroups[1])
			जारी;

		src = find_qgroup_rb(fs_info, i_qgroups[0]);
		dst = find_qgroup_rb(fs_info, i_qgroups[1]);

		अगर (!src || !dst) अणु
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण

		dst->rfer = src->rfer - level_size;
		dst->rfer_cmpr = src->rfer_cmpr - level_size;

		/* Manually tweaking numbers certainly needs a rescan */
		need_rescan = true;
	पूर्ण
	क्रम (i = 0; i <  inherit->num_excl_copies; ++i, i_qgroups += 2) अणु
		काष्ठा btrfs_qgroup *src;
		काष्ठा btrfs_qgroup *dst;

		अगर (!i_qgroups[0] || !i_qgroups[1])
			जारी;

		src = find_qgroup_rb(fs_info, i_qgroups[0]);
		dst = find_qgroup_rb(fs_info, i_qgroups[1]);

		अगर (!src || !dst) अणु
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण

		dst->excl = src->excl + level_size;
		dst->excl_cmpr = src->excl_cmpr + level_size;
		need_rescan = true;
	पूर्ण

unlock:
	spin_unlock(&fs_info->qgroup_lock);
	अगर (!ret)
		ret = btrfs_sysfs_add_one_qgroup(fs_info, dstgroup);
out:
	अगर (!committing)
		mutex_unlock(&fs_info->qgroup_ioctl_lock);
	अगर (need_rescan)
		fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
	वापस ret;
पूर्ण

अटल bool qgroup_check_limits(स्थिर काष्ठा btrfs_qgroup *qg, u64 num_bytes)
अणु
	अगर ((qg->lim_flags & BTRFS_QGROUP_LIMIT_MAX_RFER) &&
	    qgroup_rsv_total(qg) + (s64)qg->rfer + num_bytes > qg->max_rfer)
		वापस false;

	अगर ((qg->lim_flags & BTRFS_QGROUP_LIMIT_MAX_EXCL) &&
	    qgroup_rsv_total(qg) + (s64)qg->excl + num_bytes > qg->max_excl)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक qgroup_reserve(काष्ठा btrfs_root *root, u64 num_bytes, bool enक्रमce,
			  क्रमागत btrfs_qgroup_rsv_type type)
अणु
	काष्ठा btrfs_qgroup *qgroup;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 ref_root = root->root_key.objectid;
	पूर्णांक ret = 0;
	काष्ठा ulist_node *unode;
	काष्ठा ulist_iterator uiter;

	अगर (!is_fstree(ref_root))
		वापस 0;

	अगर (num_bytes == 0)
		वापस 0;

	अगर (test_bit(BTRFS_FS_QUOTA_OVERRIDE, &fs_info->flags) &&
	    capable(CAP_SYS_RESOURCE))
		enक्रमce = false;

	spin_lock(&fs_info->qgroup_lock);
	अगर (!fs_info->quota_root)
		जाओ out;

	qgroup = find_qgroup_rb(fs_info, ref_root);
	अगर (!qgroup)
		जाओ out;

	/*
	 * in a first step, we check all affected qgroups अगर any limits would
	 * be exceeded
	 */
	ulist_reinit(fs_info->qgroup_ulist);
	ret = ulist_add(fs_info->qgroup_ulist, qgroup->qgroupid,
			qgroup_to_aux(qgroup), GFP_ATOMIC);
	अगर (ret < 0)
		जाओ out;
	ULIST_ITER_INIT(&uiter);
	जबतक ((unode = ulist_next(fs_info->qgroup_ulist, &uiter))) अणु
		काष्ठा btrfs_qgroup *qg;
		काष्ठा btrfs_qgroup_list *glist;

		qg = unode_aux_to_qgroup(unode);

		अगर (enक्रमce && !qgroup_check_limits(qg, num_bytes)) अणु
			ret = -EDQUOT;
			जाओ out;
		पूर्ण

		list_क्रम_each_entry(glist, &qg->groups, next_group) अणु
			ret = ulist_add(fs_info->qgroup_ulist,
					glist->group->qgroupid,
					qgroup_to_aux(glist->group), GFP_ATOMIC);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण
	ret = 0;
	/*
	 * no limits exceeded, now record the reservation पूर्णांकo all qgroups
	 */
	ULIST_ITER_INIT(&uiter);
	जबतक ((unode = ulist_next(fs_info->qgroup_ulist, &uiter))) अणु
		काष्ठा btrfs_qgroup *qg;

		qg = unode_aux_to_qgroup(unode);

		qgroup_rsv_add(fs_info, qg, num_bytes, type);
	पूर्ण

out:
	spin_unlock(&fs_info->qgroup_lock);
	वापस ret;
पूर्ण

/*
 * Free @num_bytes of reserved space with @type क्रम qgroup.  (Normally level 0
 * qgroup).
 *
 * Will handle all higher level qgroup too.
 *
 * NOTE: If @num_bytes is (u64)-1, this means to मुक्त all bytes of this qgroup.
 * This special हाल is only used क्रम META_PERTRANS type.
 */
व्योम btrfs_qgroup_मुक्त_refroot(काष्ठा btrfs_fs_info *fs_info,
			       u64 ref_root, u64 num_bytes,
			       क्रमागत btrfs_qgroup_rsv_type type)
अणु
	काष्ठा btrfs_qgroup *qgroup;
	काष्ठा ulist_node *unode;
	काष्ठा ulist_iterator uiter;
	पूर्णांक ret = 0;

	अगर (!is_fstree(ref_root))
		वापस;

	अगर (num_bytes == 0)
		वापस;

	अगर (num_bytes == (u64)-1 && type != BTRFS_QGROUP_RSV_META_PERTRANS) अणु
		WARN(1, "%s: Invalid type to free", __func__);
		वापस;
	पूर्ण
	spin_lock(&fs_info->qgroup_lock);

	अगर (!fs_info->quota_root)
		जाओ out;

	qgroup = find_qgroup_rb(fs_info, ref_root);
	अगर (!qgroup)
		जाओ out;

	अगर (num_bytes == (u64)-1)
		/*
		 * We're मुक्तing all pertrans rsv, get reserved value from
		 * level 0 qgroup as real num_bytes to मुक्त.
		 */
		num_bytes = qgroup->rsv.values[type];

	ulist_reinit(fs_info->qgroup_ulist);
	ret = ulist_add(fs_info->qgroup_ulist, qgroup->qgroupid,
			qgroup_to_aux(qgroup), GFP_ATOMIC);
	अगर (ret < 0)
		जाओ out;
	ULIST_ITER_INIT(&uiter);
	जबतक ((unode = ulist_next(fs_info->qgroup_ulist, &uiter))) अणु
		काष्ठा btrfs_qgroup *qg;
		काष्ठा btrfs_qgroup_list *glist;

		qg = unode_aux_to_qgroup(unode);

		qgroup_rsv_release(fs_info, qg, num_bytes, type);

		list_क्रम_each_entry(glist, &qg->groups, next_group) अणु
			ret = ulist_add(fs_info->qgroup_ulist,
					glist->group->qgroupid,
					qgroup_to_aux(glist->group), GFP_ATOMIC);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	spin_unlock(&fs_info->qgroup_lock);
पूर्ण

/*
 * Check अगर the leaf is the last leaf. Which means all node poपूर्णांकers
 * are at their last position.
 */
अटल bool is_last_leaf(काष्ठा btrfs_path *path)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < BTRFS_MAX_LEVEL && path->nodes[i]; i++) अणु
		अगर (path->slots[i] != btrfs_header_nritems(path->nodes[i]) - 1)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * वापसs < 0 on error, 0 when more leafs are to be scanned.
 * वापसs 1 when करोne.
 */
अटल पूर्णांक qgroup_rescan_leaf(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_key found;
	काष्ठा extent_buffer *scratch_leaf = शून्य;
	काष्ठा ulist *roots = शून्य;
	u64 num_bytes;
	bool करोne;
	पूर्णांक slot;
	पूर्णांक ret;

	mutex_lock(&fs_info->qgroup_rescan_lock);
	ret = btrfs_search_slot_क्रम_पढ़ो(fs_info->extent_root,
					 &fs_info->qgroup_rescan_progress,
					 path, 1, 0);

	btrfs_debug(fs_info,
		"current progress key (%llu %u %llu), search_slot ret %d",
		fs_info->qgroup_rescan_progress.objectid,
		fs_info->qgroup_rescan_progress.type,
		fs_info->qgroup_rescan_progress.offset, ret);

	अगर (ret) अणु
		/*
		 * The rescan is about to end, we will not be scanning any
		 * further blocks. We cannot unset the RESCAN flag here, because
		 * we want to commit the transaction अगर everything went well.
		 * To make the live accounting work in this phase, we set our
		 * scan progress poपूर्णांकer such that every real extent objectid
		 * will be smaller.
		 */
		fs_info->qgroup_rescan_progress.objectid = (u64)-1;
		btrfs_release_path(path);
		mutex_unlock(&fs_info->qgroup_rescan_lock);
		वापस ret;
	पूर्ण
	करोne = is_last_leaf(path);

	btrfs_item_key_to_cpu(path->nodes[0], &found,
			      btrfs_header_nritems(path->nodes[0]) - 1);
	fs_info->qgroup_rescan_progress.objectid = found.objectid + 1;

	scratch_leaf = btrfs_clone_extent_buffer(path->nodes[0]);
	अगर (!scratch_leaf) अणु
		ret = -ENOMEM;
		mutex_unlock(&fs_info->qgroup_rescan_lock);
		जाओ out;
	पूर्ण
	slot = path->slots[0];
	btrfs_release_path(path);
	mutex_unlock(&fs_info->qgroup_rescan_lock);

	क्रम (; slot < btrfs_header_nritems(scratch_leaf); ++slot) अणु
		btrfs_item_key_to_cpu(scratch_leaf, &found, slot);
		अगर (found.type != BTRFS_EXTENT_ITEM_KEY &&
		    found.type != BTRFS_METADATA_ITEM_KEY)
			जारी;
		अगर (found.type == BTRFS_METADATA_ITEM_KEY)
			num_bytes = fs_info->nodesize;
		अन्यथा
			num_bytes = found.offset;

		ret = btrfs_find_all_roots(शून्य, fs_info, found.objectid, 0,
					   &roots, false);
		अगर (ret < 0)
			जाओ out;
		/* For rescan, just pass old_roots as शून्य */
		ret = btrfs_qgroup_account_extent(trans, found.objectid,
						  num_bytes, शून्य, roots);
		अगर (ret < 0)
			जाओ out;
	पूर्ण
out:
	अगर (scratch_leaf)
		मुक्त_extent_buffer(scratch_leaf);

	अगर (करोne && !ret) अणु
		ret = 1;
		fs_info->qgroup_rescan_progress.objectid = (u64)-1;
	पूर्ण
	वापस ret;
पूर्ण

अटल bool rescan_should_stop(काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस btrfs_fs_closing(fs_info) ||
		test_bit(BTRFS_FS_STATE_REMOUNTING, &fs_info->fs_state);
पूर्ण

अटल व्योम btrfs_qgroup_rescan_worker(काष्ठा btrfs_work *work)
अणु
	काष्ठा btrfs_fs_info *fs_info = container_of(work, काष्ठा btrfs_fs_info,
						     qgroup_rescan_work);
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_trans_handle *trans = शून्य;
	पूर्णांक err = -ENOMEM;
	पूर्णांक ret = 0;
	bool stopped = false;

	path = btrfs_alloc_path();
	अगर (!path)
		जाओ out;
	/*
	 * Rescan should only search क्रम commit root, and any later dअगरference
	 * should be recorded by qgroup
	 */
	path->search_commit_root = 1;
	path->skip_locking = 1;

	err = 0;
	जबतक (!err && !(stopped = rescan_should_stop(fs_info))) अणु
		trans = btrfs_start_transaction(fs_info->fs_root, 0);
		अगर (IS_ERR(trans)) अणु
			err = PTR_ERR(trans);
			अवरोध;
		पूर्ण
		अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags)) अणु
			err = -EINTR;
		पूर्ण अन्यथा अणु
			err = qgroup_rescan_leaf(trans, path);
		पूर्ण
		अगर (err > 0)
			btrfs_commit_transaction(trans);
		अन्यथा
			btrfs_end_transaction(trans);
	पूर्ण

out:
	btrfs_मुक्त_path(path);

	mutex_lock(&fs_info->qgroup_rescan_lock);
	अगर (err > 0 &&
	    fs_info->qgroup_flags & BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT) अणु
		fs_info->qgroup_flags &= ~BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
	पूर्ण अन्यथा अगर (err < 0) अणु
		fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
	पूर्ण
	mutex_unlock(&fs_info->qgroup_rescan_lock);

	/*
	 * only update status, since the previous part has alपढ़ोy updated the
	 * qgroup info.
	 */
	trans = btrfs_start_transaction(fs_info->quota_root, 1);
	अगर (IS_ERR(trans)) अणु
		err = PTR_ERR(trans);
		trans = शून्य;
		btrfs_err(fs_info,
			  "fail to start transaction for status update: %d",
			  err);
	पूर्ण

	mutex_lock(&fs_info->qgroup_rescan_lock);
	अगर (!stopped)
		fs_info->qgroup_flags &= ~BTRFS_QGROUP_STATUS_FLAG_RESCAN;
	अगर (trans) अणु
		ret = update_qgroup_status_item(trans);
		अगर (ret < 0) अणु
			err = ret;
			btrfs_err(fs_info, "fail to update qgroup status: %d",
				  err);
		पूर्ण
	पूर्ण
	fs_info->qgroup_rescan_running = false;
	complete_all(&fs_info->qgroup_rescan_completion);
	mutex_unlock(&fs_info->qgroup_rescan_lock);

	अगर (!trans)
		वापस;

	btrfs_end_transaction(trans);

	अगर (stopped) अणु
		btrfs_info(fs_info, "qgroup scan paused");
	पूर्ण अन्यथा अगर (err >= 0) अणु
		btrfs_info(fs_info, "qgroup scan completed%s",
			err > 0 ? " (inconsistency flag cleared)" : "");
	पूर्ण अन्यथा अणु
		btrfs_err(fs_info, "qgroup scan failed with %d", err);
	पूर्ण
पूर्ण

/*
 * Checks that (a) no rescan is running and (b) quota is enabled. Allocates all
 * memory required क्रम the rescan context.
 */
अटल पूर्णांक
qgroup_rescan_init(काष्ठा btrfs_fs_info *fs_info, u64 progress_objectid,
		   पूर्णांक init_flags)
अणु
	पूर्णांक ret = 0;

	अगर (!init_flags) अणु
		/* we're resuming qgroup rescan at mount समय */
		अगर (!(fs_info->qgroup_flags &
		      BTRFS_QGROUP_STATUS_FLAG_RESCAN)) अणु
			btrfs_warn(fs_info,
			"qgroup rescan init failed, qgroup rescan is not queued");
			ret = -EINVAL;
		पूर्ण अन्यथा अगर (!(fs_info->qgroup_flags &
			     BTRFS_QGROUP_STATUS_FLAG_ON)) अणु
			btrfs_warn(fs_info,
			"qgroup rescan init failed, qgroup is not enabled");
			ret = -EINVAL;
		पूर्ण

		अगर (ret)
			वापस ret;
	पूर्ण

	mutex_lock(&fs_info->qgroup_rescan_lock);

	अगर (init_flags) अणु
		अगर (fs_info->qgroup_flags & BTRFS_QGROUP_STATUS_FLAG_RESCAN) अणु
			btrfs_warn(fs_info,
				   "qgroup rescan is already in progress");
			ret = -EINPROGRESS;
		पूर्ण अन्यथा अगर (!(fs_info->qgroup_flags &
			     BTRFS_QGROUP_STATUS_FLAG_ON)) अणु
			btrfs_warn(fs_info,
			"qgroup rescan init failed, qgroup is not enabled");
			ret = -EINVAL;
		पूर्ण

		अगर (ret) अणु
			mutex_unlock(&fs_info->qgroup_rescan_lock);
			वापस ret;
		पूर्ण
		fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_RESCAN;
	पूर्ण

	स_रखो(&fs_info->qgroup_rescan_progress, 0,
		माप(fs_info->qgroup_rescan_progress));
	fs_info->qgroup_rescan_progress.objectid = progress_objectid;
	init_completion(&fs_info->qgroup_rescan_completion);
	mutex_unlock(&fs_info->qgroup_rescan_lock);

	btrfs_init_work(&fs_info->qgroup_rescan_work,
			btrfs_qgroup_rescan_worker, शून्य, शून्य);
	वापस 0;
पूर्ण

अटल व्योम
qgroup_rescan_zero_tracking(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा rb_node *n;
	काष्ठा btrfs_qgroup *qgroup;

	spin_lock(&fs_info->qgroup_lock);
	/* clear all current qgroup tracking inक्रमmation */
	क्रम (n = rb_first(&fs_info->qgroup_tree); n; n = rb_next(n)) अणु
		qgroup = rb_entry(n, काष्ठा btrfs_qgroup, node);
		qgroup->rfer = 0;
		qgroup->rfer_cmpr = 0;
		qgroup->excl = 0;
		qgroup->excl_cmpr = 0;
		qgroup_dirty(fs_info, qgroup);
	पूर्ण
	spin_unlock(&fs_info->qgroup_lock);
पूर्ण

पूर्णांक
btrfs_qgroup_rescan(काष्ठा btrfs_fs_info *fs_info)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_trans_handle *trans;

	ret = qgroup_rescan_init(fs_info, 0, 1);
	अगर (ret)
		वापस ret;

	/*
	 * We have set the rescan_progress to 0, which means no more
	 * delayed refs will be accounted by btrfs_qgroup_account_ref.
	 * However, btrfs_qgroup_account_ref may be right after its call
	 * to btrfs_find_all_roots, in which हाल it would still करो the
	 * accounting.
	 * To solve this, we're committing the transaction, which will
	 * ensure we run all delayed refs and only after that, we are
	 * going to clear all tracking inक्रमmation क्रम a clean start.
	 */

	trans = btrfs_join_transaction(fs_info->fs_root);
	अगर (IS_ERR(trans)) अणु
		fs_info->qgroup_flags &= ~BTRFS_QGROUP_STATUS_FLAG_RESCAN;
		वापस PTR_ERR(trans);
	पूर्ण
	ret = btrfs_commit_transaction(trans);
	अगर (ret) अणु
		fs_info->qgroup_flags &= ~BTRFS_QGROUP_STATUS_FLAG_RESCAN;
		वापस ret;
	पूर्ण

	qgroup_rescan_zero_tracking(fs_info);

	mutex_lock(&fs_info->qgroup_rescan_lock);
	fs_info->qgroup_rescan_running = true;
	btrfs_queue_work(fs_info->qgroup_rescan_workers,
			 &fs_info->qgroup_rescan_work);
	mutex_unlock(&fs_info->qgroup_rescan_lock);

	वापस 0;
पूर्ण

पूर्णांक btrfs_qgroup_रुको_क्रम_completion(काष्ठा btrfs_fs_info *fs_info,
				     bool पूर्णांकerruptible)
अणु
	पूर्णांक running;
	पूर्णांक ret = 0;

	mutex_lock(&fs_info->qgroup_rescan_lock);
	running = fs_info->qgroup_rescan_running;
	mutex_unlock(&fs_info->qgroup_rescan_lock);

	अगर (!running)
		वापस 0;

	अगर (पूर्णांकerruptible)
		ret = रुको_क्रम_completion_पूर्णांकerruptible(
					&fs_info->qgroup_rescan_completion);
	अन्यथा
		रुको_क्रम_completion(&fs_info->qgroup_rescan_completion);

	वापस ret;
पूर्ण

/*
 * this is only called from खोलो_ctree where we're still single thपढ़ोed, thus
 * locking is omitted here.
 */
व्योम
btrfs_qgroup_rescan_resume(काष्ठा btrfs_fs_info *fs_info)
अणु
	अगर (fs_info->qgroup_flags & BTRFS_QGROUP_STATUS_FLAG_RESCAN) अणु
		mutex_lock(&fs_info->qgroup_rescan_lock);
		fs_info->qgroup_rescan_running = true;
		btrfs_queue_work(fs_info->qgroup_rescan_workers,
				 &fs_info->qgroup_rescan_work);
		mutex_unlock(&fs_info->qgroup_rescan_lock);
	पूर्ण
पूर्ण

#घोषणा rbtree_iterate_from_safe(node, next, start)				\
       क्रम (node = start; node && (अणु next = rb_next(node); 1;पूर्ण); node = next)

अटल पूर्णांक qgroup_unreserve_range(काष्ठा btrfs_inode *inode,
				  काष्ठा extent_changeset *reserved, u64 start,
				  u64 len)
अणु
	काष्ठा rb_node *node;
	काष्ठा rb_node *next;
	काष्ठा ulist_node *entry;
	पूर्णांक ret = 0;

	node = reserved->range_changed.root.rb_node;
	अगर (!node)
		वापस 0;
	जबतक (node) अणु
		entry = rb_entry(node, काष्ठा ulist_node, rb_node);
		अगर (entry->val < start)
			node = node->rb_right;
		अन्यथा
			node = node->rb_left;
	पूर्ण

	अगर (entry->val > start && rb_prev(&entry->rb_node))
		entry = rb_entry(rb_prev(&entry->rb_node), काष्ठा ulist_node,
				 rb_node);

	rbtree_iterate_from_safe(node, next, &entry->rb_node) अणु
		u64 entry_start;
		u64 entry_end;
		u64 entry_len;
		पूर्णांक clear_ret;

		entry = rb_entry(node, काष्ठा ulist_node, rb_node);
		entry_start = entry->val;
		entry_end = entry->aux;
		entry_len = entry_end - entry_start + 1;

		अगर (entry_start >= start + len)
			अवरोध;
		अगर (entry_start + entry_len <= start)
			जारी;
		/*
		 * Now the entry is in [start, start + len), revert the
		 * EXTENT_QGROUP_RESERVED bit.
		 */
		clear_ret = clear_extent_bits(&inode->io_tree, entry_start,
					      entry_end, EXTENT_QGROUP_RESERVED);
		अगर (!ret && clear_ret < 0)
			ret = clear_ret;

		ulist_del(&reserved->range_changed, entry->val, entry->aux);
		अगर (likely(reserved->bytes_changed >= entry_len)) अणु
			reserved->bytes_changed -= entry_len;
		पूर्ण अन्यथा अणु
			WARN_ON(1);
			reserved->bytes_changed = 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Try to मुक्त some space क्रम qgroup.
 *
 * For qgroup, there are only 3 ways to मुक्त qgroup space:
 * - Flush nodatacow ग_लिखो
 *   Any nodatacow ग_लिखो will मुक्त its reserved data space at run_delalloc_range().
 *   In theory, we should only flush nodatacow inodes, but it's not yet
 *   possible, so we need to flush the whole root.
 *
 * - Wait क्रम ordered extents
 *   When ordered extents are finished, their reserved metadata is finally
 *   converted to per_trans status, which can be मुक्तd by later commit
 *   transaction.
 *
 * - Commit transaction
 *   This would मुक्त the meta_per_trans space.
 *   In theory this shouldn't provide much space, but any more qgroup space
 *   is needed.
 */
अटल पूर्णांक try_flush_qgroup(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret;

	/*
	 * Can't hold an खोलो transaction or we run the risk of deadlocking,
	 * and can't either be under the context of a send operation (where
	 * current->journal_info is set to BTRFS_SEND_TRANS_STUB), as that
	 * would result in a crash when starting a transaction and करोes not
	 * make sense either (send is a पढ़ो-only operation).
	 */
	ASSERT(current->journal_info == शून्य);
	अगर (WARN_ON(current->journal_info))
		वापस 0;

	/*
	 * We करोn't want to run flush again and again, so अगर there is a running
	 * one, we won't try to start a new flush, but निकास directly.
	 */
	अगर (test_and_set_bit(BTRFS_ROOT_QGROUP_FLUSHING, &root->state)) अणु
		रुको_event(root->qgroup_flush_रुको,
			!test_bit(BTRFS_ROOT_QGROUP_FLUSHING, &root->state));
		वापस 0;
	पूर्ण

	ret = btrfs_start_delalloc_snapshot(root, true);
	अगर (ret < 0)
		जाओ out;
	btrfs_रुको_ordered_extents(root, U64_MAX, 0, (u64)-1);

	trans = btrfs_join_transaction(root);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out;
	पूर्ण

	ret = btrfs_commit_transaction(trans);
out:
	clear_bit(BTRFS_ROOT_QGROUP_FLUSHING, &root->state);
	wake_up(&root->qgroup_flush_रुको);
	वापस ret;
पूर्ण

अटल पूर्णांक qgroup_reserve_data(काष्ठा btrfs_inode *inode,
			काष्ठा extent_changeset **reserved_ret, u64 start,
			u64 len)
अणु
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा extent_changeset *reserved;
	bool new_reserved = false;
	u64 orig_reserved;
	u64 to_reserve;
	पूर्णांक ret;

	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &root->fs_info->flags) ||
	    !is_fstree(root->root_key.objectid) || len == 0)
		वापस 0;

	/* @reserved parameter is mandatory क्रम qgroup */
	अगर (WARN_ON(!reserved_ret))
		वापस -EINVAL;
	अगर (!*reserved_ret) अणु
		new_reserved = true;
		*reserved_ret = extent_changeset_alloc();
		अगर (!*reserved_ret)
			वापस -ENOMEM;
	पूर्ण
	reserved = *reserved_ret;
	/* Record alपढ़ोy reserved space */
	orig_reserved = reserved->bytes_changed;
	ret = set_record_extent_bits(&inode->io_tree, start,
			start + len -1, EXTENT_QGROUP_RESERVED, reserved);

	/* Newly reserved space */
	to_reserve = reserved->bytes_changed - orig_reserved;
	trace_btrfs_qgroup_reserve_data(&inode->vfs_inode, start, len,
					to_reserve, QGROUP_RESERVE);
	अगर (ret < 0)
		जाओ out;
	ret = qgroup_reserve(root, to_reserve, true, BTRFS_QGROUP_RSV_DATA);
	अगर (ret < 0)
		जाओ cleanup;

	वापस ret;

cleanup:
	qgroup_unreserve_range(inode, reserved, start, len);
out:
	अगर (new_reserved) अणु
		extent_changeset_मुक्त(reserved);
		*reserved_ret = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Reserve qgroup space क्रम range [start, start + len).
 *
 * This function will either reserve space from related qgroups or करो nothing
 * अगर the range is alपढ़ोy reserved.
 *
 * Return 0 क्रम successful reservation
 * Return <0 क्रम error (including -EQUOT)
 *
 * NOTE: This function may sleep क्रम memory allocation, dirty page flushing and
 *	 commit transaction. So caller should not hold any dirty page locked.
 */
पूर्णांक btrfs_qgroup_reserve_data(काष्ठा btrfs_inode *inode,
			काष्ठा extent_changeset **reserved_ret, u64 start,
			u64 len)
अणु
	पूर्णांक ret;

	ret = qgroup_reserve_data(inode, reserved_ret, start, len);
	अगर (ret <= 0 && ret != -EDQUOT)
		वापस ret;

	ret = try_flush_qgroup(inode->root);
	अगर (ret < 0)
		वापस ret;
	वापस qgroup_reserve_data(inode, reserved_ret, start, len);
पूर्ण

/* Free ranges specअगरied by @reserved, normally in error path */
अटल पूर्णांक qgroup_मुक्त_reserved_data(काष्ठा btrfs_inode *inode,
			काष्ठा extent_changeset *reserved, u64 start, u64 len)
अणु
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा ulist_node *unode;
	काष्ठा ulist_iterator uiter;
	काष्ठा extent_changeset changeset;
	पूर्णांक मुक्तd = 0;
	पूर्णांक ret;

	extent_changeset_init(&changeset);
	len = round_up(start + len, root->fs_info->sectorsize);
	start = round_करोwn(start, root->fs_info->sectorsize);

	ULIST_ITER_INIT(&uiter);
	जबतक ((unode = ulist_next(&reserved->range_changed, &uiter))) अणु
		u64 range_start = unode->val;
		/* unode->aux is the inclusive end */
		u64 range_len = unode->aux - range_start + 1;
		u64 मुक्त_start;
		u64 मुक्त_len;

		extent_changeset_release(&changeset);

		/* Only मुक्त range in range [start, start + len) */
		अगर (range_start >= start + len ||
		    range_start + range_len <= start)
			जारी;
		मुक्त_start = max(range_start, start);
		मुक्त_len = min(start + len, range_start + range_len) -
			   मुक्त_start;
		/*
		 * TODO: To also modअगरy reserved->ranges_reserved to reflect
		 * the modअगरication.
		 *
		 * However as दीर्घ as we मुक्त qgroup reserved according to
		 * EXTENT_QGROUP_RESERVED, we won't द्विगुन मुक्त.
		 * So not need to rush.
		 */
		ret = clear_record_extent_bits(&inode->io_tree, मुक्त_start,
				मुक्त_start + मुक्त_len - 1,
				EXTENT_QGROUP_RESERVED, &changeset);
		अगर (ret < 0)
			जाओ out;
		मुक्तd += changeset.bytes_changed;
	पूर्ण
	btrfs_qgroup_मुक्त_refroot(root->fs_info, root->root_key.objectid, मुक्तd,
				  BTRFS_QGROUP_RSV_DATA);
	ret = मुक्तd;
out:
	extent_changeset_release(&changeset);
	वापस ret;
पूर्ण

अटल पूर्णांक __btrfs_qgroup_release_data(काष्ठा btrfs_inode *inode,
			काष्ठा extent_changeset *reserved, u64 start, u64 len,
			पूर्णांक मुक्त)
अणु
	काष्ठा extent_changeset changeset;
	पूर्णांक trace_op = QGROUP_RELEASE;
	पूर्णांक ret;

	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &inode->root->fs_info->flags))
		वापस 0;

	/* In release हाल, we shouldn't have @reserved */
	WARN_ON(!मुक्त && reserved);
	अगर (मुक्त && reserved)
		वापस qgroup_मुक्त_reserved_data(inode, reserved, start, len);
	extent_changeset_init(&changeset);
	ret = clear_record_extent_bits(&inode->io_tree, start, start + len -1,
				       EXTENT_QGROUP_RESERVED, &changeset);
	अगर (ret < 0)
		जाओ out;

	अगर (मुक्त)
		trace_op = QGROUP_FREE;
	trace_btrfs_qgroup_release_data(&inode->vfs_inode, start, len,
					changeset.bytes_changed, trace_op);
	अगर (मुक्त)
		btrfs_qgroup_मुक्त_refroot(inode->root->fs_info,
				inode->root->root_key.objectid,
				changeset.bytes_changed, BTRFS_QGROUP_RSV_DATA);
	ret = changeset.bytes_changed;
out:
	extent_changeset_release(&changeset);
	वापस ret;
पूर्ण

/*
 * Free a reserved space range from io_tree and related qgroups
 *
 * Should be called when a range of pages get invalidated beक्रमe reaching disk.
 * Or क्रम error cleanup हाल.
 * अगर @reserved is given, only reserved range in [@start, @start + @len) will
 * be मुक्तd.
 *
 * For data written to disk, use btrfs_qgroup_release_data().
 *
 * NOTE: This function may sleep क्रम memory allocation.
 */
पूर्णांक btrfs_qgroup_मुक्त_data(काष्ठा btrfs_inode *inode,
			काष्ठा extent_changeset *reserved, u64 start, u64 len)
अणु
	वापस __btrfs_qgroup_release_data(inode, reserved, start, len, 1);
पूर्ण

/*
 * Release a reserved space range from io_tree only.
 *
 * Should be called when a range of pages get written to disk and corresponding
 * खाता_EXTENT is inserted पूर्णांकo corresponding root.
 *
 * Since new qgroup accounting framework will only update qgroup numbers at
 * commit_transaction() समय, its reserved space shouldn't be मुक्तd from
 * related qgroups.
 *
 * But we should release the range from io_tree, to allow further ग_लिखो to be
 * COWed.
 *
 * NOTE: This function may sleep क्रम memory allocation.
 */
पूर्णांक btrfs_qgroup_release_data(काष्ठा btrfs_inode *inode, u64 start, u64 len)
अणु
	वापस __btrfs_qgroup_release_data(inode, शून्य, start, len, 0);
पूर्ण

अटल व्योम add_root_meta_rsv(काष्ठा btrfs_root *root, पूर्णांक num_bytes,
			      क्रमागत btrfs_qgroup_rsv_type type)
अणु
	अगर (type != BTRFS_QGROUP_RSV_META_PREALLOC &&
	    type != BTRFS_QGROUP_RSV_META_PERTRANS)
		वापस;
	अगर (num_bytes == 0)
		वापस;

	spin_lock(&root->qgroup_meta_rsv_lock);
	अगर (type == BTRFS_QGROUP_RSV_META_PREALLOC)
		root->qgroup_meta_rsv_pपुनः_स्मृति += num_bytes;
	अन्यथा
		root->qgroup_meta_rsv_pertrans += num_bytes;
	spin_unlock(&root->qgroup_meta_rsv_lock);
पूर्ण

अटल पूर्णांक sub_root_meta_rsv(काष्ठा btrfs_root *root, पूर्णांक num_bytes,
			     क्रमागत btrfs_qgroup_rsv_type type)
अणु
	अगर (type != BTRFS_QGROUP_RSV_META_PREALLOC &&
	    type != BTRFS_QGROUP_RSV_META_PERTRANS)
		वापस 0;
	अगर (num_bytes == 0)
		वापस 0;

	spin_lock(&root->qgroup_meta_rsv_lock);
	अगर (type == BTRFS_QGROUP_RSV_META_PREALLOC) अणु
		num_bytes = min_t(u64, root->qgroup_meta_rsv_pपुनः_स्मृति,
				  num_bytes);
		root->qgroup_meta_rsv_pपुनः_स्मृति -= num_bytes;
	पूर्ण अन्यथा अणु
		num_bytes = min_t(u64, root->qgroup_meta_rsv_pertrans,
				  num_bytes);
		root->qgroup_meta_rsv_pertrans -= num_bytes;
	पूर्ण
	spin_unlock(&root->qgroup_meta_rsv_lock);
	वापस num_bytes;
पूर्ण

पूर्णांक btrfs_qgroup_reserve_meta(काष्ठा btrfs_root *root, पूर्णांक num_bytes,
			      क्रमागत btrfs_qgroup_rsv_type type, bool enक्रमce)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक ret;

	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags) ||
	    !is_fstree(root->root_key.objectid) || num_bytes == 0)
		वापस 0;

	BUG_ON(num_bytes != round_करोwn(num_bytes, fs_info->nodesize));
	trace_qgroup_meta_reserve(root, (s64)num_bytes, type);
	ret = qgroup_reserve(root, num_bytes, enक्रमce, type);
	अगर (ret < 0)
		वापस ret;
	/*
	 * Record what we have reserved पूर्णांकo root.
	 *
	 * To aव्योम quota disabled->enabled underflow.
	 * In that हाल, we may try to मुक्त space we haven't reserved
	 * (since quota was disabled), so record what we reserved पूर्णांकo root.
	 * And ensure later release won't underflow this number.
	 */
	add_root_meta_rsv(root, num_bytes, type);
	वापस ret;
पूर्ण

पूर्णांक __btrfs_qgroup_reserve_meta(काष्ठा btrfs_root *root, पूर्णांक num_bytes,
				क्रमागत btrfs_qgroup_rsv_type type, bool enक्रमce)
अणु
	पूर्णांक ret;

	ret = btrfs_qgroup_reserve_meta(root, num_bytes, type, enक्रमce);
	अगर (ret <= 0 && ret != -EDQUOT)
		वापस ret;

	ret = try_flush_qgroup(root);
	अगर (ret < 0)
		वापस ret;
	वापस btrfs_qgroup_reserve_meta(root, num_bytes, type, enक्रमce);
पूर्ण

व्योम btrfs_qgroup_मुक्त_meta_all_pertrans(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;

	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags) ||
	    !is_fstree(root->root_key.objectid))
		वापस;

	/* TODO: Update trace poपूर्णांक to handle such मुक्त */
	trace_qgroup_meta_मुक्त_all_pertrans(root);
	/* Special value -1 means to मुक्त all reserved space */
	btrfs_qgroup_मुक्त_refroot(fs_info, root->root_key.objectid, (u64)-1,
				  BTRFS_QGROUP_RSV_META_PERTRANS);
पूर्ण

व्योम __btrfs_qgroup_मुक्त_meta(काष्ठा btrfs_root *root, पूर्णांक num_bytes,
			      क्रमागत btrfs_qgroup_rsv_type type)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;

	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags) ||
	    !is_fstree(root->root_key.objectid))
		वापस;

	/*
	 * reservation क्रम META_PREALLOC can happen beक्रमe quota is enabled,
	 * which can lead to underflow.
	 * Here ensure we will only मुक्त what we really have reserved.
	 */
	num_bytes = sub_root_meta_rsv(root, num_bytes, type);
	BUG_ON(num_bytes != round_करोwn(num_bytes, fs_info->nodesize));
	trace_qgroup_meta_reserve(root, -(s64)num_bytes, type);
	btrfs_qgroup_मुक्त_refroot(fs_info, root->root_key.objectid,
				  num_bytes, type);
पूर्ण

अटल व्योम qgroup_convert_meta(काष्ठा btrfs_fs_info *fs_info, u64 ref_root,
				पूर्णांक num_bytes)
अणु
	काष्ठा btrfs_qgroup *qgroup;
	काष्ठा ulist_node *unode;
	काष्ठा ulist_iterator uiter;
	पूर्णांक ret = 0;

	अगर (num_bytes == 0)
		वापस;
	अगर (!fs_info->quota_root)
		वापस;

	spin_lock(&fs_info->qgroup_lock);
	qgroup = find_qgroup_rb(fs_info, ref_root);
	अगर (!qgroup)
		जाओ out;
	ulist_reinit(fs_info->qgroup_ulist);
	ret = ulist_add(fs_info->qgroup_ulist, qgroup->qgroupid,
		       qgroup_to_aux(qgroup), GFP_ATOMIC);
	अगर (ret < 0)
		जाओ out;
	ULIST_ITER_INIT(&uiter);
	जबतक ((unode = ulist_next(fs_info->qgroup_ulist, &uiter))) अणु
		काष्ठा btrfs_qgroup *qg;
		काष्ठा btrfs_qgroup_list *glist;

		qg = unode_aux_to_qgroup(unode);

		qgroup_rsv_release(fs_info, qg, num_bytes,
				BTRFS_QGROUP_RSV_META_PREALLOC);
		qgroup_rsv_add(fs_info, qg, num_bytes,
				BTRFS_QGROUP_RSV_META_PERTRANS);
		list_क्रम_each_entry(glist, &qg->groups, next_group) अणु
			ret = ulist_add(fs_info->qgroup_ulist,
					glist->group->qgroupid,
					qgroup_to_aux(glist->group), GFP_ATOMIC);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण
out:
	spin_unlock(&fs_info->qgroup_lock);
पूर्ण

व्योम btrfs_qgroup_convert_reserved_meta(काष्ठा btrfs_root *root, पूर्णांक num_bytes)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;

	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags) ||
	    !is_fstree(root->root_key.objectid))
		वापस;
	/* Same as btrfs_qgroup_मुक्त_meta_pपुनः_स्मृति() */
	num_bytes = sub_root_meta_rsv(root, num_bytes,
				      BTRFS_QGROUP_RSV_META_PREALLOC);
	trace_qgroup_meta_convert(root, num_bytes);
	qgroup_convert_meta(fs_info, root->root_key.objectid, num_bytes);
पूर्ण

/*
 * Check qgroup reserved space leaking, normally at destroy inode
 * समय
 */
व्योम btrfs_qgroup_check_reserved_leak(काष्ठा btrfs_inode *inode)
अणु
	काष्ठा extent_changeset changeset;
	काष्ठा ulist_node *unode;
	काष्ठा ulist_iterator iter;
	पूर्णांक ret;

	extent_changeset_init(&changeset);
	ret = clear_record_extent_bits(&inode->io_tree, 0, (u64)-1,
			EXTENT_QGROUP_RESERVED, &changeset);

	WARN_ON(ret < 0);
	अगर (WARN_ON(changeset.bytes_changed)) अणु
		ULIST_ITER_INIT(&iter);
		जबतक ((unode = ulist_next(&changeset.range_changed, &iter))) अणु
			btrfs_warn(inode->root->fs_info,
		"leaking qgroup reserved space, ino: %llu, start: %llu, end: %llu",
				btrfs_ino(inode), unode->val, unode->aux);
		पूर्ण
		btrfs_qgroup_मुक्त_refroot(inode->root->fs_info,
				inode->root->root_key.objectid,
				changeset.bytes_changed, BTRFS_QGROUP_RSV_DATA);

	पूर्ण
	extent_changeset_release(&changeset);
पूर्ण

व्योम btrfs_qgroup_init_swapped_blocks(
	काष्ठा btrfs_qgroup_swapped_blocks *swapped_blocks)
अणु
	पूर्णांक i;

	spin_lock_init(&swapped_blocks->lock);
	क्रम (i = 0; i < BTRFS_MAX_LEVEL; i++)
		swapped_blocks->blocks[i] = RB_ROOT;
	swapped_blocks->swapped = false;
पूर्ण

/*
 * Delete all swapped blocks record of @root.
 * Every record here means we skipped a full subtree scan क्रम qgroup.
 *
 * Gets called when committing one transaction.
 */
व्योम btrfs_qgroup_clean_swapped_blocks(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_qgroup_swapped_blocks *swapped_blocks;
	पूर्णांक i;

	swapped_blocks = &root->swapped_blocks;

	spin_lock(&swapped_blocks->lock);
	अगर (!swapped_blocks->swapped)
		जाओ out;
	क्रम (i = 0; i < BTRFS_MAX_LEVEL; i++) अणु
		काष्ठा rb_root *cur_root = &swapped_blocks->blocks[i];
		काष्ठा btrfs_qgroup_swapped_block *entry;
		काष्ठा btrfs_qgroup_swapped_block *next;

		rbtree_postorder_क्रम_each_entry_safe(entry, next, cur_root,
						     node)
			kमुक्त(entry);
		swapped_blocks->blocks[i] = RB_ROOT;
	पूर्ण
	swapped_blocks->swapped = false;
out:
	spin_unlock(&swapped_blocks->lock);
पूर्ण

/*
 * Add subtree roots record पूर्णांकo @subvol_root.
 *
 * @subvol_root:	tree root of the subvolume tree get swapped
 * @bg:			block group under balance
 * @subvol_parent/slot:	poपूर्णांकer to the subtree root in subvolume tree
 * @reloc_parent/slot:	poपूर्णांकer to the subtree root in reloc tree
 *			BOTH POINTERS ARE BEFORE TREE SWAP
 * @last_snapshot:	last snapshot generation of the subvolume tree
 */
पूर्णांक btrfs_qgroup_add_swapped_blocks(काष्ठा btrfs_trans_handle *trans,
		काष्ठा btrfs_root *subvol_root,
		काष्ठा btrfs_block_group *bg,
		काष्ठा extent_buffer *subvol_parent, पूर्णांक subvol_slot,
		काष्ठा extent_buffer *reloc_parent, पूर्णांक reloc_slot,
		u64 last_snapshot)
अणु
	काष्ठा btrfs_fs_info *fs_info = subvol_root->fs_info;
	काष्ठा btrfs_qgroup_swapped_blocks *blocks = &subvol_root->swapped_blocks;
	काष्ठा btrfs_qgroup_swapped_block *block;
	काष्ठा rb_node **cur;
	काष्ठा rb_node *parent = शून्य;
	पूर्णांक level = btrfs_header_level(subvol_parent) - 1;
	पूर्णांक ret = 0;

	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags))
		वापस 0;

	अगर (btrfs_node_ptr_generation(subvol_parent, subvol_slot) >
	    btrfs_node_ptr_generation(reloc_parent, reloc_slot)) अणु
		btrfs_err_rl(fs_info,
		"%s: bad parameter order, subvol_gen=%llu reloc_gen=%llu",
			__func__,
			btrfs_node_ptr_generation(subvol_parent, subvol_slot),
			btrfs_node_ptr_generation(reloc_parent, reloc_slot));
		वापस -EUCLEAN;
	पूर्ण

	block = kदो_स्मृति(माप(*block), GFP_NOFS);
	अगर (!block) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * @reloc_parent/slot is still beक्रमe swap, जबतक @block is going to
	 * record the bytenr after swap, so we करो the swap here.
	 */
	block->subvol_bytenr = btrfs_node_blockptr(reloc_parent, reloc_slot);
	block->subvol_generation = btrfs_node_ptr_generation(reloc_parent,
							     reloc_slot);
	block->reloc_bytenr = btrfs_node_blockptr(subvol_parent, subvol_slot);
	block->reloc_generation = btrfs_node_ptr_generation(subvol_parent,
							    subvol_slot);
	block->last_snapshot = last_snapshot;
	block->level = level;

	/*
	 * If we have bg == शून्य, we're called from btrfs_recover_relocation(),
	 * no one अन्यथा can modअगरy tree blocks thus we qgroup will not change
	 * no matter the value of trace_leaf.
	 */
	अगर (bg && bg->flags & BTRFS_BLOCK_GROUP_DATA)
		block->trace_leaf = true;
	अन्यथा
		block->trace_leaf = false;
	btrfs_node_key_to_cpu(reloc_parent, &block->first_key, reloc_slot);

	/* Insert @block पूर्णांकo @blocks */
	spin_lock(&blocks->lock);
	cur = &blocks->blocks[level].rb_node;
	जबतक (*cur) अणु
		काष्ठा btrfs_qgroup_swapped_block *entry;

		parent = *cur;
		entry = rb_entry(parent, काष्ठा btrfs_qgroup_swapped_block,
				 node);

		अगर (entry->subvol_bytenr < block->subvol_bytenr) अणु
			cur = &(*cur)->rb_left;
		पूर्ण अन्यथा अगर (entry->subvol_bytenr > block->subvol_bytenr) अणु
			cur = &(*cur)->rb_right;
		पूर्ण अन्यथा अणु
			अगर (entry->subvol_generation !=
					block->subvol_generation ||
			    entry->reloc_bytenr != block->reloc_bytenr ||
			    entry->reloc_generation !=
					block->reloc_generation) अणु
				/*
				 * Duplicated but mismatch entry found.
				 * Shouldn't happen.
				 *
				 * Marking qgroup inconsistent should be enough
				 * क्रम end users.
				 */
				WARN_ON(IS_ENABLED(CONFIG_BTRFS_DEBUG));
				ret = -EEXIST;
			पूर्ण
			kमुक्त(block);
			जाओ out_unlock;
		पूर्ण
	पूर्ण
	rb_link_node(&block->node, parent, cur);
	rb_insert_color(&block->node, &blocks->blocks[level]);
	blocks->swapped = true;
out_unlock:
	spin_unlock(&blocks->lock);
out:
	अगर (ret < 0)
		fs_info->qgroup_flags |=
			BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
	वापस ret;
पूर्ण

/*
 * Check अगर the tree block is a subtree root, and अगर so करो the needed
 * delayed subtree trace क्रम qgroup.
 *
 * This is called during btrfs_cow_block().
 */
पूर्णांक btrfs_qgroup_trace_subtree_after_cow(काष्ठा btrfs_trans_handle *trans,
					 काष्ठा btrfs_root *root,
					 काष्ठा extent_buffer *subvol_eb)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_qgroup_swapped_blocks *blocks = &root->swapped_blocks;
	काष्ठा btrfs_qgroup_swapped_block *block;
	काष्ठा extent_buffer *reloc_eb = शून्य;
	काष्ठा rb_node *node;
	bool found = false;
	bool swapped = false;
	पूर्णांक level = btrfs_header_level(subvol_eb);
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags))
		वापस 0;
	अगर (!is_fstree(root->root_key.objectid) || !root->reloc_root)
		वापस 0;

	spin_lock(&blocks->lock);
	अगर (!blocks->swapped) अणु
		spin_unlock(&blocks->lock);
		वापस 0;
	पूर्ण
	node = blocks->blocks[level].rb_node;

	जबतक (node) अणु
		block = rb_entry(node, काष्ठा btrfs_qgroup_swapped_block, node);
		अगर (block->subvol_bytenr < subvol_eb->start) अणु
			node = node->rb_left;
		पूर्ण अन्यथा अगर (block->subvol_bytenr > subvol_eb->start) अणु
			node = node->rb_right;
		पूर्ण अन्यथा अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		spin_unlock(&blocks->lock);
		जाओ out;
	पूर्ण
	/* Found one, हटाओ it from @blocks first and update blocks->swapped */
	rb_erase(&block->node, &blocks->blocks[level]);
	क्रम (i = 0; i < BTRFS_MAX_LEVEL; i++) अणु
		अगर (RB_EMPTY_ROOT(&blocks->blocks[i])) अणु
			swapped = true;
			अवरोध;
		पूर्ण
	पूर्ण
	blocks->swapped = swapped;
	spin_unlock(&blocks->lock);

	/* Read out reloc subtree root */
	reloc_eb = पढ़ो_tree_block(fs_info, block->reloc_bytenr, 0,
				   block->reloc_generation, block->level,
				   &block->first_key);
	अगर (IS_ERR(reloc_eb)) अणु
		ret = PTR_ERR(reloc_eb);
		reloc_eb = शून्य;
		जाओ मुक्त_out;
	पूर्ण
	अगर (!extent_buffer_uptodate(reloc_eb)) अणु
		ret = -EIO;
		जाओ मुक्त_out;
	पूर्ण

	ret = qgroup_trace_subtree_swap(trans, reloc_eb, subvol_eb,
			block->last_snapshot, block->trace_leaf);
मुक्त_out:
	kमुक्त(block);
	मुक्त_extent_buffer(reloc_eb);
out:
	अगर (ret < 0) अणु
		btrfs_err_rl(fs_info,
			     "failed to account subtree at bytenr %llu: %d",
			     subvol_eb->start, ret);
		fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
	पूर्ण
	वापस ret;
पूर्ण

व्योम btrfs_qgroup_destroy_extent_records(काष्ठा btrfs_transaction *trans)
अणु
	काष्ठा btrfs_qgroup_extent_record *entry;
	काष्ठा btrfs_qgroup_extent_record *next;
	काष्ठा rb_root *root;

	root = &trans->delayed_refs.dirty_extent_root;
	rbtree_postorder_क्रम_each_entry_safe(entry, next, root, node) अणु
		ulist_मुक्त(entry->old_roots);
		kमुक्त(entry);
	पूर्ण
पूर्ण
