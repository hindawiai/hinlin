<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * quota.c - CephFS quota
 *
 * Copyright (C) 2017-2018 SUSE
 */

#समावेश <linux/statfs.h>

#समावेश "super.h"
#समावेश "mds_client.h"

व्योम ceph_adjust_quota_realms_count(काष्ठा inode *inode, bool inc)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(inode->i_sb);
	अगर (inc)
		atomic64_inc(&mdsc->quotarealms_count);
	अन्यथा
		atomic64_dec(&mdsc->quotarealms_count);
पूर्ण

अटल अंतरभूत bool ceph_has_realms_with_quotas(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(sb);
	काष्ठा inode *root = d_inode(sb->s_root);

	अगर (atomic64_पढ़ो(&mdsc->quotarealms_count) > 0)
		वापस true;
	/* अगर root is the real CephFS root, we करोn't have quota realms */
	अगर (root && ceph_ino(root) == CEPH_INO_ROOT)
		वापस false;
	/* otherwise, we can't know क्रम sure */
	वापस true;
पूर्ण

व्योम ceph_handle_quota(काष्ठा ceph_mds_client *mdsc,
		       काष्ठा ceph_mds_session *session,
		       काष्ठा ceph_msg *msg)
अणु
	काष्ठा super_block *sb = mdsc->fsc->sb;
	काष्ठा ceph_mds_quota *h = msg->front.iov_base;
	काष्ठा ceph_vino vino;
	काष्ठा inode *inode;
	काष्ठा ceph_inode_info *ci;

	अगर (msg->front.iov_len < माप(*h)) अणु
		pr_err("%s corrupt message mds%d len %d\n", __func__,
		       session->s_mds, (पूर्णांक)msg->front.iov_len);
		ceph_msg_dump(msg);
		वापस;
	पूर्ण

	/* increment msg sequence number */
	mutex_lock(&session->s_mutex);
	inc_session_sequence(session);
	mutex_unlock(&session->s_mutex);

	/* lookup inode */
	vino.ino = le64_to_cpu(h->ino);
	vino.snap = CEPH_NOSNAP;
	inode = ceph_find_inode(sb, vino);
	अगर (!inode) अणु
		pr_warn("Failed to find inode %llu\n", vino.ino);
		वापस;
	पूर्ण
	ci = ceph_inode(inode);

	spin_lock(&ci->i_ceph_lock);
	ci->i_rbytes = le64_to_cpu(h->rbytes);
	ci->i_rfiles = le64_to_cpu(h->rfiles);
	ci->i_rsubdirs = le64_to_cpu(h->rsubdirs);
	__ceph_update_quota(ci, le64_to_cpu(h->max_bytes),
		            le64_to_cpu(h->max_files));
	spin_unlock(&ci->i_ceph_lock);

	/* aव्योम calling iput_final() in dispatch thपढ़ो */
	ceph_async_iput(inode);
पूर्ण

अटल काष्ठा ceph_quotarealm_inode *
find_quotarealm_inode(काष्ठा ceph_mds_client *mdsc, u64 ino)
अणु
	काष्ठा ceph_quotarealm_inode *qri = शून्य;
	काष्ठा rb_node **node, *parent = शून्य;

	mutex_lock(&mdsc->quotarealms_inodes_mutex);
	node = &(mdsc->quotarealms_inodes.rb_node);
	जबतक (*node) अणु
		parent = *node;
		qri = container_of(*node, काष्ठा ceph_quotarealm_inode, node);

		अगर (ino < qri->ino)
			node = &((*node)->rb_left);
		अन्यथा अगर (ino > qri->ino)
			node = &((*node)->rb_right);
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (!qri || (qri->ino != ino)) अणु
		/* Not found, create a new one and insert it */
		qri = kदो_स्मृति(माप(*qri), GFP_KERNEL);
		अगर (qri) अणु
			qri->ino = ino;
			qri->inode = शून्य;
			qri->समयout = 0;
			mutex_init(&qri->mutex);
			rb_link_node(&qri->node, parent, node);
			rb_insert_color(&qri->node, &mdsc->quotarealms_inodes);
		पूर्ण अन्यथा
			pr_warn("Failed to alloc quotarealms_inode\n");
	पूर्ण
	mutex_unlock(&mdsc->quotarealms_inodes_mutex);

	वापस qri;
पूर्ण

/*
 * This function will try to lookup a realm inode which isn't visible in the
 * fileप्रणाली mountpoपूर्णांक.  A list of these kind of inodes (not visible) is
 * मुख्यtained in the mdsc and मुक्तd only when the fileप्रणाली is umounted.
 *
 * Note that these inodes are kept in this list even अगर the lookup fails, which
 * allows to prevent useless lookup requests.
 */
अटल काष्ठा inode *lookup_quotarealm_inode(काष्ठा ceph_mds_client *mdsc,
					     काष्ठा super_block *sb,
					     काष्ठा ceph_snap_realm *realm)
अणु
	काष्ठा ceph_quotarealm_inode *qri;
	काष्ठा inode *in;

	qri = find_quotarealm_inode(mdsc, realm->ino);
	अगर (!qri)
		वापस शून्य;

	mutex_lock(&qri->mutex);
	अगर (qri->inode && ceph_is_any_caps(qri->inode)) अणु
		/* A request has alपढ़ोy वापसed the inode */
		mutex_unlock(&qri->mutex);
		वापस qri->inode;
	पूर्ण
	/* Check अगर this inode lookup has failed recently */
	अगर (qri->समयout &&
	    समय_beक्रमe_eq(jअगरfies, qri->समयout)) अणु
		mutex_unlock(&qri->mutex);
		वापस शून्य;
	पूर्ण
	अगर (qri->inode) अणु
		/* get caps */
		पूर्णांक ret = __ceph_करो_getattr(qri->inode, शून्य,
					    CEPH_STAT_CAP_INODE, true);
		अगर (ret >= 0)
			in = qri->inode;
		अन्यथा
			in = ERR_PTR(ret);
	पूर्ण  अन्यथा अणु
		in = ceph_lookup_inode(sb, realm->ino);
	पूर्ण

	अगर (IS_ERR(in)) अणु
		करोut("Can't lookup inode %llx (err: %ld)\n",
		     realm->ino, PTR_ERR(in));
		qri->समयout = jअगरfies + msecs_to_jअगरfies(60 * 1000); /* XXX */
	पूर्ण अन्यथा अणु
		qri->समयout = 0;
		qri->inode = in;
	पूर्ण
	mutex_unlock(&qri->mutex);

	वापस in;
पूर्ण

व्योम ceph_cleanup_quotarealms_inodes(काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा ceph_quotarealm_inode *qri;
	काष्ठा rb_node *node;

	/*
	 * It should now be safe to clean quotarealms_inode tree without holding
	 * mdsc->quotarealms_inodes_mutex...
	 */
	mutex_lock(&mdsc->quotarealms_inodes_mutex);
	जबतक (!RB_EMPTY_ROOT(&mdsc->quotarealms_inodes)) अणु
		node = rb_first(&mdsc->quotarealms_inodes);
		qri = rb_entry(node, काष्ठा ceph_quotarealm_inode, node);
		rb_erase(node, &mdsc->quotarealms_inodes);
		iput(qri->inode);
		kमुक्त(qri);
	पूर्ण
	mutex_unlock(&mdsc->quotarealms_inodes_mutex);
पूर्ण

/*
 * This function walks through the snaprealm क्रम an inode and वापसs the
 * ceph_snap_realm क्रम the first snaprealm that has quotas set (either max_files
 * or max_bytes).  If the root is reached, वापस the root ceph_snap_realm
 * instead.
 *
 * Note that the caller is responsible क्रम calling ceph_put_snap_realm() on the
 * वापसed realm.
 *
 * Callers of this function need to hold mdsc->snap_rwsem.  However, अगर there's
 * a need to करो an inode lookup, this rwsem will be temporarily dropped.  Hence
 * the 'retry' argument: if rwsem needs to be dropped and 'retry' is 'false'
 * this function will वापस -EAGAIN; otherwise, the snaprealms walk-through
 * will be restarted.
 */
अटल काष्ठा ceph_snap_realm *get_quota_realm(काष्ठा ceph_mds_client *mdsc,
					       काष्ठा inode *inode, bool retry)
अणु
	काष्ठा ceph_inode_info *ci = शून्य;
	काष्ठा ceph_snap_realm *realm, *next;
	काष्ठा inode *in;
	bool has_quota;

	अगर (ceph_snap(inode) != CEPH_NOSNAP)
		वापस शून्य;

restart:
	realm = ceph_inode(inode)->i_snap_realm;
	अगर (realm)
		ceph_get_snap_realm(mdsc, realm);
	अन्यथा
		pr_err_ratelimited("get_quota_realm: ino (%llx.%llx) "
				   "null i_snap_realm\n", ceph_vinop(inode));
	जबतक (realm) अणु
		bool has_inode;

		spin_lock(&realm->inodes_with_caps_lock);
		has_inode = realm->inode;
		in = has_inode ? igrab(realm->inode) : शून्य;
		spin_unlock(&realm->inodes_with_caps_lock);
		अगर (has_inode && !in)
			अवरोध;
		अगर (!in) अणु
			up_पढ़ो(&mdsc->snap_rwsem);
			in = lookup_quotarealm_inode(mdsc, inode->i_sb, realm);
			करोwn_पढ़ो(&mdsc->snap_rwsem);
			अगर (IS_ERR_OR_शून्य(in))
				अवरोध;
			ceph_put_snap_realm(mdsc, realm);
			अगर (!retry)
				वापस ERR_PTR(-EAGAIN);
			जाओ restart;
		पूर्ण

		ci = ceph_inode(in);
		has_quota = __ceph_has_any_quota(ci);
		/* aव्योम calling iput_final() जबतक holding mdsc->snap_rwsem */
		ceph_async_iput(in);

		next = realm->parent;
		अगर (has_quota || !next)
		       वापस realm;

		ceph_get_snap_realm(mdsc, next);
		ceph_put_snap_realm(mdsc, realm);
		realm = next;
	पूर्ण
	अगर (realm)
		ceph_put_snap_realm(mdsc, realm);

	वापस शून्य;
पूर्ण

bool ceph_quota_is_same_realm(काष्ठा inode *old, काष्ठा inode *new)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(old->i_sb);
	काष्ठा ceph_snap_realm *old_realm, *new_realm;
	bool is_same;

restart:
	/*
	 * We need to lookup 2 quota realms atomically, i.e. with snap_rwsem.
	 * However, get_quota_realm may drop it temporarily.  By setting the
	 * 'retry' parameter to 'false', we'll get -EAGAIN अगर the rwsem was
	 * dropped and we can then restart the whole operation.
	 */
	करोwn_पढ़ो(&mdsc->snap_rwsem);
	old_realm = get_quota_realm(mdsc, old, true);
	new_realm = get_quota_realm(mdsc, new, false);
	अगर (PTR_ERR(new_realm) == -EAGAIN) अणु
		up_पढ़ो(&mdsc->snap_rwsem);
		अगर (old_realm)
			ceph_put_snap_realm(mdsc, old_realm);
		जाओ restart;
	पूर्ण
	is_same = (old_realm == new_realm);
	up_पढ़ो(&mdsc->snap_rwsem);

	अगर (old_realm)
		ceph_put_snap_realm(mdsc, old_realm);
	अगर (new_realm)
		ceph_put_snap_realm(mdsc, new_realm);

	वापस is_same;
पूर्ण

क्रमागत quota_check_op अणु
	QUOTA_CHECK_MAX_खाताS_OP,	/* check quota max_files limit */
	QUOTA_CHECK_MAX_BYTES_OP,	/* check quota max_files limit */
	QUOTA_CHECK_MAX_BYTES_APPROACHING_OP	/* check अगर quota max_files
						   limit is approaching */
पूर्ण;

/*
 * check_quota_exceeded() will walk up the snaprealm hierarchy and, क्रम each
 * realm, it will execute quota check operation defined by the 'op' parameter.
 * The snaprealm walk is पूर्णांकerrupted अगर the quota check detects that the quota
 * is exceeded or अगर the root inode is reached.
 */
अटल bool check_quota_exceeded(काष्ठा inode *inode, क्रमागत quota_check_op op,
				 loff_t delta)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(inode->i_sb);
	काष्ठा ceph_inode_info *ci;
	काष्ठा ceph_snap_realm *realm, *next;
	काष्ठा inode *in;
	u64 max, rvalue;
	bool exceeded = false;

	अगर (ceph_snap(inode) != CEPH_NOSNAP)
		वापस false;

	करोwn_पढ़ो(&mdsc->snap_rwsem);
restart:
	realm = ceph_inode(inode)->i_snap_realm;
	अगर (realm)
		ceph_get_snap_realm(mdsc, realm);
	अन्यथा
		pr_err_ratelimited("check_quota_exceeded: ino (%llx.%llx) "
				   "null i_snap_realm\n", ceph_vinop(inode));
	जबतक (realm) अणु
		bool has_inode;

		spin_lock(&realm->inodes_with_caps_lock);
		has_inode = realm->inode;
		in = has_inode ? igrab(realm->inode) : शून्य;
		spin_unlock(&realm->inodes_with_caps_lock);
		अगर (has_inode && !in)
			अवरोध;
		अगर (!in) अणु
			up_पढ़ो(&mdsc->snap_rwsem);
			in = lookup_quotarealm_inode(mdsc, inode->i_sb, realm);
			करोwn_पढ़ो(&mdsc->snap_rwsem);
			अगर (IS_ERR_OR_शून्य(in))
				अवरोध;
			ceph_put_snap_realm(mdsc, realm);
			जाओ restart;
		पूर्ण
		ci = ceph_inode(in);
		spin_lock(&ci->i_ceph_lock);
		अगर (op == QUOTA_CHECK_MAX_खाताS_OP) अणु
			max = ci->i_max_files;
			rvalue = ci->i_rfiles + ci->i_rsubdirs;
		पूर्ण अन्यथा अणु
			max = ci->i_max_bytes;
			rvalue = ci->i_rbytes;
		पूर्ण
		spin_unlock(&ci->i_ceph_lock);
		चयन (op) अणु
		हाल QUOTA_CHECK_MAX_खाताS_OP:
		हाल QUOTA_CHECK_MAX_BYTES_OP:
			exceeded = (max && (rvalue + delta > max));
			अवरोध;
		हाल QUOTA_CHECK_MAX_BYTES_APPROACHING_OP:
			अगर (max) अणु
				अगर (rvalue >= max)
					exceeded = true;
				अन्यथा अणु
					/*
					 * when we're writing more that 1/16th
					 * of the available space
					 */
					exceeded =
						(((max - rvalue) >> 4) < delta);
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			/* Shouldn't happen */
			pr_warn("Invalid quota check op (%d)\n", op);
			exceeded = true; /* Just अवरोध the loop */
		पूर्ण
		/* aव्योम calling iput_final() जबतक holding mdsc->snap_rwsem */
		ceph_async_iput(in);

		next = realm->parent;
		अगर (exceeded || !next)
			अवरोध;
		ceph_get_snap_realm(mdsc, next);
		ceph_put_snap_realm(mdsc, realm);
		realm = next;
	पूर्ण
	अगर (realm)
		ceph_put_snap_realm(mdsc, realm);
	up_पढ़ो(&mdsc->snap_rwsem);

	वापस exceeded;
पूर्ण

/*
 * ceph_quota_is_max_files_exceeded - check अगर we can create a new file
 * @inode:	directory where a new file is being created
 *
 * This functions वापसs true is max_files quota allows a new file to be
 * created.  It is necessary to walk through the snaprealm hierarchy (until the
 * FS root) to check all realms with quotas set.
 */
bool ceph_quota_is_max_files_exceeded(काष्ठा inode *inode)
अणु
	अगर (!ceph_has_realms_with_quotas(inode))
		वापस false;

	WARN_ON(!S_ISसूची(inode->i_mode));

	वापस check_quota_exceeded(inode, QUOTA_CHECK_MAX_खाताS_OP, 1);
पूर्ण

/*
 * ceph_quota_is_max_bytes_exceeded - check अगर we can ग_लिखो to a file
 * @inode:	inode being written
 * @newsize:	new size अगर ग_लिखो succeeds
 *
 * This functions वापसs true is max_bytes quota allows a file size to reach
 * @newsize; it वापसs false otherwise.
 */
bool ceph_quota_is_max_bytes_exceeded(काष्ठा inode *inode, loff_t newsize)
अणु
	loff_t size = i_size_पढ़ो(inode);

	अगर (!ceph_has_realms_with_quotas(inode))
		वापस false;

	/* वापस immediately अगर we're decreasing file size */
	अगर (newsize <= size)
		वापस false;

	वापस check_quota_exceeded(inode, QUOTA_CHECK_MAX_BYTES_OP, (newsize - size));
पूर्ण

/*
 * ceph_quota_is_max_bytes_approaching - check अगर we're reaching max_bytes
 * @inode:	inode being written
 * @newsize:	new size अगर ग_लिखो succeeds
 *
 * This function वापसs true अगर the new file size @newsize will be consuming
 * more than 1/16th of the available quota space; it वापसs false otherwise.
 */
bool ceph_quota_is_max_bytes_approaching(काष्ठा inode *inode, loff_t newsize)
अणु
	loff_t size = ceph_inode(inode)->i_reported_size;

	अगर (!ceph_has_realms_with_quotas(inode))
		वापस false;

	/* वापस immediately अगर we're decreasing file size */
	अगर (newsize <= size)
		वापस false;

	वापस check_quota_exceeded(inode, QUOTA_CHECK_MAX_BYTES_APPROACHING_OP,
				    (newsize - size));
पूर्ण

/*
 * ceph_quota_update_statfs - अगर root has quota update statfs with quota status
 * @fsc:	fileप्रणाली client instance
 * @buf:	statfs to update
 *
 * If the mounted fileप्रणाली root has max_bytes quota set, update the fileप्रणाली
 * statistics with the quota status.
 *
 * This function वापसs true अगर the stats have been updated, false otherwise.
 */
bool ceph_quota_update_statfs(काष्ठा ceph_fs_client *fsc, काष्ठा kstatfs *buf)
अणु
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
	काष्ठा ceph_inode_info *ci;
	काष्ठा ceph_snap_realm *realm;
	काष्ठा inode *in;
	u64 total = 0, used, मुक्त;
	bool is_updated = false;

	करोwn_पढ़ो(&mdsc->snap_rwsem);
	realm = get_quota_realm(mdsc, d_inode(fsc->sb->s_root), true);
	up_पढ़ो(&mdsc->snap_rwsem);
	अगर (!realm)
		वापस false;

	spin_lock(&realm->inodes_with_caps_lock);
	in = realm->inode ? igrab(realm->inode) : शून्य;
	spin_unlock(&realm->inodes_with_caps_lock);
	अगर (in) अणु
		ci = ceph_inode(in);
		spin_lock(&ci->i_ceph_lock);
		अगर (ci->i_max_bytes) अणु
			total = ci->i_max_bytes >> CEPH_BLOCK_SHIFT;
			used = ci->i_rbytes >> CEPH_BLOCK_SHIFT;
			/* It is possible क्रम a quota to be exceeded.
			 * Report 'zero' in that हाल
			 */
			मुक्त = total > used ? total - used : 0;
		पूर्ण
		spin_unlock(&ci->i_ceph_lock);
		अगर (total) अणु
			buf->f_blocks = total;
			buf->f_bमुक्त = मुक्त;
			buf->f_bavail = मुक्त;
			is_updated = true;
		पूर्ण
		iput(in);
	पूर्ण
	ceph_put_snap_realm(mdsc, realm);

	वापस is_updated;
पूर्ण

