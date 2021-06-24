<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/fs.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/gfp.h>
#समावेश <linux/sched.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/bits.h>
#समावेश <linux/kसमय.स>

#समावेश "super.h"
#समावेश "mds_client.h"

#समावेश <linux/ceph/ceph_features.h>
#समावेश <linux/ceph/messenger.h>
#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/pagelist.h>
#समावेश <linux/ceph/auth.h>
#समावेश <linux/ceph/debugfs.h>

#घोषणा RECONNECT_MAX_SIZE (पूर्णांक_उच्च - PAGE_SIZE)

/*
 * A cluster of MDS (metadata server) daemons is responsible क्रम
 * managing the file प्रणाली namespace (the directory hierarchy and
 * inodes) and क्रम coordinating shared access to storage.  Metadata is
 * partitioning hierarchically across a number of servers, and that
 * partition varies over समय as the cluster adjusts the distribution
 * in order to balance load.
 *
 * The MDS client is primarily responsible to managing synchronous
 * metadata requests क्रम operations like खोलो, unlink, and so क्रमth.
 * If there is a MDS failure, we find out about it when we (possibly
 * request and) receive a new MDS map, and can resubmit affected
 * requests.
 *
 * For the most part, though, we take advantage of a lossless
 * communications channel to the MDS, and करो not need to worry about
 * timing out or resubmitting requests.
 *
 * We मुख्यtain a stateful "session" with each MDS we पूर्णांकeract with.
 * Within each session, we sent periodic heartbeat messages to ensure
 * any capabilities or leases we have been issues reमुख्य valid.  If
 * the session बार out and goes stale, our leases and capabilities
 * are no दीर्घer valid.
 */

काष्ठा ceph_reconnect_state अणु
	काष्ठा ceph_mds_session *session;
	पूर्णांक nr_caps, nr_realms;
	काष्ठा ceph_pagelist *pagelist;
	अचिन्हित msg_version;
	bool allow_multi;
पूर्ण;

अटल व्योम __wake_requests(काष्ठा ceph_mds_client *mdsc,
			    काष्ठा list_head *head);
अटल व्योम ceph_cap_release_work(काष्ठा work_काष्ठा *work);
अटल व्योम ceph_cap_reclaim_work(काष्ठा work_काष्ठा *work);

अटल स्थिर काष्ठा ceph_connection_operations mds_con_ops;


/*
 * mds reply parsing
 */

अटल पूर्णांक parse_reply_info_quota(व्योम **p, व्योम *end,
				  काष्ठा ceph_mds_reply_info_in *info)
अणु
	u8 काष्ठा_v, काष्ठा_compat;
	u32 काष्ठा_len;

	ceph_decode_8_safe(p, end, काष्ठा_v, bad);
	ceph_decode_8_safe(p, end, काष्ठा_compat, bad);
	/* काष्ठा_v is expected to be >= 1. we only
	 * understand encoding with काष्ठा_compat == 1. */
	अगर (!काष्ठा_v || काष्ठा_compat != 1)
		जाओ bad;
	ceph_decode_32_safe(p, end, काष्ठा_len, bad);
	ceph_decode_need(p, end, काष्ठा_len, bad);
	end = *p + काष्ठा_len;
	ceph_decode_64_safe(p, end, info->max_bytes, bad);
	ceph_decode_64_safe(p, end, info->max_files, bad);
	*p = end;
	वापस 0;
bad:
	वापस -EIO;
पूर्ण

/*
 * parse inभागidual inode info
 */
अटल पूर्णांक parse_reply_info_in(व्योम **p, व्योम *end,
			       काष्ठा ceph_mds_reply_info_in *info,
			       u64 features)
अणु
	पूर्णांक err = 0;
	u8 काष्ठा_v = 0;

	अगर (features == (u64)-1) अणु
		u32 काष्ठा_len;
		u8 काष्ठा_compat;
		ceph_decode_8_safe(p, end, काष्ठा_v, bad);
		ceph_decode_8_safe(p, end, काष्ठा_compat, bad);
		/* काष्ठा_v is expected to be >= 1. we only understand
		 * encoding with काष्ठा_compat == 1. */
		अगर (!काष्ठा_v || काष्ठा_compat != 1)
			जाओ bad;
		ceph_decode_32_safe(p, end, काष्ठा_len, bad);
		ceph_decode_need(p, end, काष्ठा_len, bad);
		end = *p + काष्ठा_len;
	पूर्ण

	ceph_decode_need(p, end, माप(काष्ठा ceph_mds_reply_inode), bad);
	info->in = *p;
	*p += माप(काष्ठा ceph_mds_reply_inode) +
		माप(*info->in->fragtree.splits) *
		le32_to_cpu(info->in->fragtree.nsplits);

	ceph_decode_32_safe(p, end, info->symlink_len, bad);
	ceph_decode_need(p, end, info->symlink_len, bad);
	info->symlink = *p;
	*p += info->symlink_len;

	ceph_decode_copy_safe(p, end, &info->dir_layout,
			      माप(info->dir_layout), bad);
	ceph_decode_32_safe(p, end, info->xattr_len, bad);
	ceph_decode_need(p, end, info->xattr_len, bad);
	info->xattr_data = *p;
	*p += info->xattr_len;

	अगर (features == (u64)-1) अणु
		/* अंतरभूत data */
		ceph_decode_64_safe(p, end, info->अंतरभूत_version, bad);
		ceph_decode_32_safe(p, end, info->अंतरभूत_len, bad);
		ceph_decode_need(p, end, info->अंतरभूत_len, bad);
		info->अंतरभूत_data = *p;
		*p += info->अंतरभूत_len;
		/* quota */
		err = parse_reply_info_quota(p, end, info);
		अगर (err < 0)
			जाओ out_bad;
		/* pool namespace */
		ceph_decode_32_safe(p, end, info->pool_ns_len, bad);
		अगर (info->pool_ns_len > 0) अणु
			ceph_decode_need(p, end, info->pool_ns_len, bad);
			info->pool_ns_data = *p;
			*p += info->pool_ns_len;
		पूर्ण

		/* bसमय */
		ceph_decode_need(p, end, माप(info->bसमय), bad);
		ceph_decode_copy(p, &info->bसमय, माप(info->bसमय));

		/* change attribute */
		ceph_decode_64_safe(p, end, info->change_attr, bad);

		/* dir pin */
		अगर (काष्ठा_v >= 2) अणु
			ceph_decode_32_safe(p, end, info->dir_pin, bad);
		पूर्ण अन्यथा अणु
			info->dir_pin = -ENODATA;
		पूर्ण

		/* snapshot birth समय, reमुख्यs zero क्रम v<=2 */
		अगर (काष्ठा_v >= 3) अणु
			ceph_decode_need(p, end, माप(info->snap_bसमय), bad);
			ceph_decode_copy(p, &info->snap_bसमय,
					 माप(info->snap_bसमय));
		पूर्ण अन्यथा अणु
			स_रखो(&info->snap_bसमय, 0, माप(info->snap_bसमय));
		पूर्ण

		/* snapshot count, reमुख्यs zero क्रम v<=3 */
		अगर (काष्ठा_v >= 4) अणु
			ceph_decode_64_safe(p, end, info->rsnaps, bad);
		पूर्ण अन्यथा अणु
			info->rsnaps = 0;
		पूर्ण

		*p = end;
	पूर्ण अन्यथा अणु
		अगर (features & CEPH_FEATURE_MDS_INLINE_DATA) अणु
			ceph_decode_64_safe(p, end, info->अंतरभूत_version, bad);
			ceph_decode_32_safe(p, end, info->अंतरभूत_len, bad);
			ceph_decode_need(p, end, info->अंतरभूत_len, bad);
			info->अंतरभूत_data = *p;
			*p += info->अंतरभूत_len;
		पूर्ण अन्यथा
			info->अंतरभूत_version = CEPH_INLINE_NONE;

		अगर (features & CEPH_FEATURE_MDS_QUOTA) अणु
			err = parse_reply_info_quota(p, end, info);
			अगर (err < 0)
				जाओ out_bad;
		पूर्ण अन्यथा अणु
			info->max_bytes = 0;
			info->max_files = 0;
		पूर्ण

		info->pool_ns_len = 0;
		info->pool_ns_data = शून्य;
		अगर (features & CEPH_FEATURE_FS_खाता_LAYOUT_V2) अणु
			ceph_decode_32_safe(p, end, info->pool_ns_len, bad);
			अगर (info->pool_ns_len > 0) अणु
				ceph_decode_need(p, end, info->pool_ns_len, bad);
				info->pool_ns_data = *p;
				*p += info->pool_ns_len;
			पूर्ण
		पूर्ण

		अगर (features & CEPH_FEATURE_FS_BTIME) अणु
			ceph_decode_need(p, end, माप(info->bसमय), bad);
			ceph_decode_copy(p, &info->bसमय, माप(info->bसमय));
			ceph_decode_64_safe(p, end, info->change_attr, bad);
		पूर्ण

		info->dir_pin = -ENODATA;
		/* info->snap_bसमय and info->rsnaps reमुख्य zero */
	पूर्ण
	वापस 0;
bad:
	err = -EIO;
out_bad:
	वापस err;
पूर्ण

अटल पूर्णांक parse_reply_info_dir(व्योम **p, व्योम *end,
				काष्ठा ceph_mds_reply_dirfrag **dirfrag,
				u64 features)
अणु
	अगर (features == (u64)-1) अणु
		u8 काष्ठा_v, काष्ठा_compat;
		u32 काष्ठा_len;
		ceph_decode_8_safe(p, end, काष्ठा_v, bad);
		ceph_decode_8_safe(p, end, काष्ठा_compat, bad);
		/* काष्ठा_v is expected to be >= 1. we only understand
		 * encoding whose काष्ठा_compat == 1. */
		अगर (!काष्ठा_v || काष्ठा_compat != 1)
			जाओ bad;
		ceph_decode_32_safe(p, end, काष्ठा_len, bad);
		ceph_decode_need(p, end, काष्ठा_len, bad);
		end = *p + काष्ठा_len;
	पूर्ण

	ceph_decode_need(p, end, माप(**dirfrag), bad);
	*dirfrag = *p;
	*p += माप(**dirfrag) + माप(u32) * le32_to_cpu((*dirfrag)->ndist);
	अगर (unlikely(*p > end))
		जाओ bad;
	अगर (features == (u64)-1)
		*p = end;
	वापस 0;
bad:
	वापस -EIO;
पूर्ण

अटल पूर्णांक parse_reply_info_lease(व्योम **p, व्योम *end,
				  काष्ठा ceph_mds_reply_lease **lease,
				  u64 features)
अणु
	अगर (features == (u64)-1) अणु
		u8 काष्ठा_v, काष्ठा_compat;
		u32 काष्ठा_len;
		ceph_decode_8_safe(p, end, काष्ठा_v, bad);
		ceph_decode_8_safe(p, end, काष्ठा_compat, bad);
		/* काष्ठा_v is expected to be >= 1. we only understand
		 * encoding whose काष्ठा_compat == 1. */
		अगर (!काष्ठा_v || काष्ठा_compat != 1)
			जाओ bad;
		ceph_decode_32_safe(p, end, काष्ठा_len, bad);
		ceph_decode_need(p, end, काष्ठा_len, bad);
		end = *p + काष्ठा_len;
	पूर्ण

	ceph_decode_need(p, end, माप(**lease), bad);
	*lease = *p;
	*p += माप(**lease);
	अगर (features == (u64)-1)
		*p = end;
	वापस 0;
bad:
	वापस -EIO;
पूर्ण

/*
 * parse a normal reply, which may contain a (dir+)dentry and/or a
 * target inode.
 */
अटल पूर्णांक parse_reply_info_trace(व्योम **p, व्योम *end,
				  काष्ठा ceph_mds_reply_info_parsed *info,
				  u64 features)
अणु
	पूर्णांक err;

	अगर (info->head->is_dentry) अणु
		err = parse_reply_info_in(p, end, &info->diri, features);
		अगर (err < 0)
			जाओ out_bad;

		err = parse_reply_info_dir(p, end, &info->dirfrag, features);
		अगर (err < 0)
			जाओ out_bad;

		ceph_decode_32_safe(p, end, info->dname_len, bad);
		ceph_decode_need(p, end, info->dname_len, bad);
		info->dname = *p;
		*p += info->dname_len;

		err = parse_reply_info_lease(p, end, &info->dlease, features);
		अगर (err < 0)
			जाओ out_bad;
	पूर्ण

	अगर (info->head->is_target) अणु
		err = parse_reply_info_in(p, end, &info->targeti, features);
		अगर (err < 0)
			जाओ out_bad;
	पूर्ण

	अगर (unlikely(*p != end))
		जाओ bad;
	वापस 0;

bad:
	err = -EIO;
out_bad:
	pr_err("problem parsing mds trace %d\n", err);
	वापस err;
पूर्ण

/*
 * parse सूची_पढ़ो results
 */
अटल पूर्णांक parse_reply_info_सूची_पढ़ो(व्योम **p, व्योम *end,
				काष्ठा ceph_mds_reply_info_parsed *info,
				u64 features)
अणु
	u32 num, i = 0;
	पूर्णांक err;

	err = parse_reply_info_dir(p, end, &info->dir_dir, features);
	अगर (err < 0)
		जाओ out_bad;

	ceph_decode_need(p, end, माप(num) + 2, bad);
	num = ceph_decode_32(p);
	अणु
		u16 flags = ceph_decode_16(p);
		info->dir_end = !!(flags & CEPH_READसूची_FRAG_END);
		info->dir_complete = !!(flags & CEPH_READसूची_FRAG_COMPLETE);
		info->hash_order = !!(flags & CEPH_READसूची_HASH_ORDER);
		info->offset_hash = !!(flags & CEPH_READसूची_OFFSET_HASH);
	पूर्ण
	अगर (num == 0)
		जाओ करोne;

	BUG_ON(!info->dir_entries);
	अगर ((अचिन्हित दीर्घ)(info->dir_entries + num) >
	    (अचिन्हित दीर्घ)info->dir_entries + info->dir_buf_size) अणु
		pr_err("dir contents are larger than expected\n");
		WARN_ON(1);
		जाओ bad;
	पूर्ण

	info->dir_nr = num;
	जबतक (num) अणु
		काष्ठा ceph_mds_reply_dir_entry *rde = info->dir_entries + i;
		/* dentry */
		ceph_decode_32_safe(p, end, rde->name_len, bad);
		ceph_decode_need(p, end, rde->name_len, bad);
		rde->name = *p;
		*p += rde->name_len;
		करोut("parsed dir dname '%.*s'\n", rde->name_len, rde->name);

		/* dentry lease */
		err = parse_reply_info_lease(p, end, &rde->lease, features);
		अगर (err)
			जाओ out_bad;
		/* inode */
		err = parse_reply_info_in(p, end, &rde->inode, features);
		अगर (err < 0)
			जाओ out_bad;
		/* ceph_सूची_पढ़ो_prepopulate() will update it */
		rde->offset = 0;
		i++;
		num--;
	पूर्ण

करोne:
	/* Skip over any unrecognized fields */
	*p = end;
	वापस 0;

bad:
	err = -EIO;
out_bad:
	pr_err("problem parsing dir contents %d\n", err);
	वापस err;
पूर्ण

/*
 * parse fcntl F_GETLK results
 */
अटल पूर्णांक parse_reply_info_filelock(व्योम **p, व्योम *end,
				     काष्ठा ceph_mds_reply_info_parsed *info,
				     u64 features)
अणु
	अगर (*p + माप(*info->filelock_reply) > end)
		जाओ bad;

	info->filelock_reply = *p;

	/* Skip over any unrecognized fields */
	*p = end;
	वापस 0;
bad:
	वापस -EIO;
पूर्ण


#अगर BITS_PER_LONG == 64

#घोषणा DELEGATED_INO_AVAILABLE		xa_mk_value(1)

अटल पूर्णांक ceph_parse_deleg_inos(व्योम **p, व्योम *end,
				 काष्ठा ceph_mds_session *s)
अणु
	u32 sets;

	ceph_decode_32_safe(p, end, sets, bad);
	करोut("got %u sets of delegated inodes\n", sets);
	जबतक (sets--) अणु
		u64 start, len, ino;

		ceph_decode_64_safe(p, end, start, bad);
		ceph_decode_64_safe(p, end, len, bad);

		/* Don't accept a delegation of प्रणाली inodes */
		अगर (start < CEPH_INO_SYSTEM_BASE) अणु
			pr_warn_ratelimited("ceph: ignoring reserved inode range delegation (start=0x%llx len=0x%llx)\n",
					start, len);
			जारी;
		पूर्ण
		जबतक (len--) अणु
			पूर्णांक err = xa_insert(&s->s_delegated_inos, ino = start++,
					    DELEGATED_INO_AVAILABLE,
					    GFP_KERNEL);
			अगर (!err) अणु
				करोut("added delegated inode 0x%llx\n",
				     start - 1);
			पूर्ण अन्यथा अगर (err == -EBUSY) अणु
				pr_warn("ceph: MDS delegated inode 0x%llx more than once.\n",
					start - 1);
			पूर्ण अन्यथा अणु
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
bad:
	वापस -EIO;
पूर्ण

u64 ceph_get_deleg_ino(काष्ठा ceph_mds_session *s)
अणु
	अचिन्हित दीर्घ ino;
	व्योम *val;

	xa_क्रम_each(&s->s_delegated_inos, ino, val) अणु
		val = xa_erase(&s->s_delegated_inos, ino);
		अगर (val == DELEGATED_INO_AVAILABLE)
			वापस ino;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ceph_restore_deleg_ino(काष्ठा ceph_mds_session *s, u64 ino)
अणु
	वापस xa_insert(&s->s_delegated_inos, ino, DELEGATED_INO_AVAILABLE,
			 GFP_KERNEL);
पूर्ण
#अन्यथा /* BITS_PER_LONG == 64 */
/*
 * FIXME: xarrays can't handle 64-bit indexes on a 32-bit arch. For now, just
 * ignore delegated_inos on 32 bit arch. Maybe eventually add xarrays क्रम top
 * and bottom words?
 */
अटल पूर्णांक ceph_parse_deleg_inos(व्योम **p, व्योम *end,
				 काष्ठा ceph_mds_session *s)
अणु
	u32 sets;

	ceph_decode_32_safe(p, end, sets, bad);
	अगर (sets)
		ceph_decode_skip_n(p, end, sets * 2 * माप(__le64), bad);
	वापस 0;
bad:
	वापस -EIO;
पूर्ण

u64 ceph_get_deleg_ino(काष्ठा ceph_mds_session *s)
अणु
	वापस 0;
पूर्ण

पूर्णांक ceph_restore_deleg_ino(काष्ठा ceph_mds_session *s, u64 ino)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* BITS_PER_LONG == 64 */

/*
 * parse create results
 */
अटल पूर्णांक parse_reply_info_create(व्योम **p, व्योम *end,
				  काष्ठा ceph_mds_reply_info_parsed *info,
				  u64 features, काष्ठा ceph_mds_session *s)
अणु
	पूर्णांक ret;

	अगर (features == (u64)-1 ||
	    (features & CEPH_FEATURE_REPLY_CREATE_INODE)) अणु
		अगर (*p == end) अणु
			/* Malक्रमmed reply? */
			info->has_create_ino = false;
		पूर्ण अन्यथा अगर (test_bit(CEPHFS_FEATURE_DELEG_INO, &s->s_features)) अणु
			info->has_create_ino = true;
			/* काष्ठा_v, काष्ठा_compat, and len */
			ceph_decode_skip_n(p, end, 2 + माप(u32), bad);
			ceph_decode_64_safe(p, end, info->ino, bad);
			ret = ceph_parse_deleg_inos(p, end, s);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			/* legacy */
			ceph_decode_64_safe(p, end, info->ino, bad);
			info->has_create_ino = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (*p != end)
			जाओ bad;
	पूर्ण

	/* Skip over any unrecognized fields */
	*p = end;
	वापस 0;
bad:
	वापस -EIO;
पूर्ण

/*
 * parse extra results
 */
अटल पूर्णांक parse_reply_info_extra(व्योम **p, व्योम *end,
				  काष्ठा ceph_mds_reply_info_parsed *info,
				  u64 features, काष्ठा ceph_mds_session *s)
अणु
	u32 op = le32_to_cpu(info->head->op);

	अगर (op == CEPH_MDS_OP_GETखाताLOCK)
		वापस parse_reply_info_filelock(p, end, info, features);
	अन्यथा अगर (op == CEPH_MDS_OP_READसूची || op == CEPH_MDS_OP_LSSNAP)
		वापस parse_reply_info_सूची_पढ़ो(p, end, info, features);
	अन्यथा अगर (op == CEPH_MDS_OP_CREATE)
		वापस parse_reply_info_create(p, end, info, features, s);
	अन्यथा
		वापस -EIO;
पूर्ण

/*
 * parse entire mds reply
 */
अटल पूर्णांक parse_reply_info(काष्ठा ceph_mds_session *s, काष्ठा ceph_msg *msg,
			    काष्ठा ceph_mds_reply_info_parsed *info,
			    u64 features)
अणु
	व्योम *p, *end;
	u32 len;
	पूर्णांक err;

	info->head = msg->front.iov_base;
	p = msg->front.iov_base + माप(काष्ठा ceph_mds_reply_head);
	end = p + msg->front.iov_len - माप(काष्ठा ceph_mds_reply_head);

	/* trace */
	ceph_decode_32_safe(&p, end, len, bad);
	अगर (len > 0) अणु
		ceph_decode_need(&p, end, len, bad);
		err = parse_reply_info_trace(&p, p+len, info, features);
		अगर (err < 0)
			जाओ out_bad;
	पूर्ण

	/* extra */
	ceph_decode_32_safe(&p, end, len, bad);
	अगर (len > 0) अणु
		ceph_decode_need(&p, end, len, bad);
		err = parse_reply_info_extra(&p, p+len, info, features, s);
		अगर (err < 0)
			जाओ out_bad;
	पूर्ण

	/* snap blob */
	ceph_decode_32_safe(&p, end, len, bad);
	info->snapblob_len = len;
	info->snapblob = p;
	p += len;

	अगर (p != end)
		जाओ bad;
	वापस 0;

bad:
	err = -EIO;
out_bad:
	pr_err("mds parse_reply err %d\n", err);
	वापस err;
पूर्ण

अटल व्योम destroy_reply_info(काष्ठा ceph_mds_reply_info_parsed *info)
अणु
	अगर (!info->dir_entries)
		वापस;
	मुक्त_pages((अचिन्हित दीर्घ)info->dir_entries, get_order(info->dir_buf_size));
पूर्ण


/*
 * sessions
 */
स्थिर अक्षर *ceph_session_state_name(पूर्णांक s)
अणु
	चयन (s) अणु
	हाल CEPH_MDS_SESSION_NEW: वापस "new";
	हाल CEPH_MDS_SESSION_OPENING: वापस "opening";
	हाल CEPH_MDS_SESSION_OPEN: वापस "open";
	हाल CEPH_MDS_SESSION_HUNG: वापस "hung";
	हाल CEPH_MDS_SESSION_CLOSING: वापस "closing";
	हाल CEPH_MDS_SESSION_CLOSED: वापस "closed";
	हाल CEPH_MDS_SESSION_RESTARTING: वापस "restarting";
	हाल CEPH_MDS_SESSION_RECONNECTING: वापस "reconnecting";
	हाल CEPH_MDS_SESSION_REJECTED: वापस "rejected";
	शेष: वापस "???";
	पूर्ण
पूर्ण

काष्ठा ceph_mds_session *ceph_get_mds_session(काष्ठा ceph_mds_session *s)
अणु
	अगर (refcount_inc_not_zero(&s->s_ref)) अणु
		करोut("mdsc get_session %p %d -> %d\n", s,
		     refcount_पढ़ो(&s->s_ref)-1, refcount_पढ़ो(&s->s_ref));
		वापस s;
	पूर्ण अन्यथा अणु
		करोut("mdsc get_session %p 0 -- FAIL\n", s);
		वापस शून्य;
	पूर्ण
पूर्ण

व्योम ceph_put_mds_session(काष्ठा ceph_mds_session *s)
अणु
	करोut("mdsc put_session %p %d -> %d\n", s,
	     refcount_पढ़ो(&s->s_ref), refcount_पढ़ो(&s->s_ref)-1);
	अगर (refcount_dec_and_test(&s->s_ref)) अणु
		अगर (s->s_auth.authorizer)
			ceph_auth_destroy_authorizer(s->s_auth.authorizer);
		WARN_ON(mutex_is_locked(&s->s_mutex));
		xa_destroy(&s->s_delegated_inos);
		kमुक्त(s);
	पूर्ण
पूर्ण

/*
 * called under mdsc->mutex
 */
काष्ठा ceph_mds_session *__ceph_lookup_mds_session(काष्ठा ceph_mds_client *mdsc,
						   पूर्णांक mds)
अणु
	अगर (mds >= mdsc->max_sessions || !mdsc->sessions[mds])
		वापस शून्य;
	वापस ceph_get_mds_session(mdsc->sessions[mds]);
पूर्ण

अटल bool __have_session(काष्ठा ceph_mds_client *mdsc, पूर्णांक mds)
अणु
	अगर (mds >= mdsc->max_sessions || !mdsc->sessions[mds])
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल पूर्णांक __verअगरy_रेजिस्टरed_session(काष्ठा ceph_mds_client *mdsc,
				       काष्ठा ceph_mds_session *s)
अणु
	अगर (s->s_mds >= mdsc->max_sessions ||
	    mdsc->sessions[s->s_mds] != s)
		वापस -ENOENT;
	वापस 0;
पूर्ण

/*
 * create+रेजिस्टर a new session क्रम given mds.
 * called under mdsc->mutex.
 */
अटल काष्ठा ceph_mds_session *रेजिस्टर_session(काष्ठा ceph_mds_client *mdsc,
						 पूर्णांक mds)
अणु
	काष्ठा ceph_mds_session *s;

	अगर (mds >= mdsc->mdsmap->possible_max_rank)
		वापस ERR_PTR(-EINVAL);

	s = kzalloc(माप(*s), GFP_NOFS);
	अगर (!s)
		वापस ERR_PTR(-ENOMEM);

	अगर (mds >= mdsc->max_sessions) अणु
		पूर्णांक newmax = 1 << get_count_order(mds + 1);
		काष्ठा ceph_mds_session **sa;

		करोut("%s: realloc to %d\n", __func__, newmax);
		sa = kसुस्मृति(newmax, माप(व्योम *), GFP_NOFS);
		अगर (!sa)
			जाओ fail_पुनः_स्मृति;
		अगर (mdsc->sessions) अणु
			स_नकल(sa, mdsc->sessions,
			       mdsc->max_sessions * माप(व्योम *));
			kमुक्त(mdsc->sessions);
		पूर्ण
		mdsc->sessions = sa;
		mdsc->max_sessions = newmax;
	पूर्ण

	करोut("%s: mds%d\n", __func__, mds);
	s->s_mdsc = mdsc;
	s->s_mds = mds;
	s->s_state = CEPH_MDS_SESSION_NEW;
	s->s_ttl = 0;
	s->s_seq = 0;
	mutex_init(&s->s_mutex);

	ceph_con_init(&s->s_con, s, &mds_con_ops, &mdsc->fsc->client->msgr);

	spin_lock_init(&s->s_gen_ttl_lock);
	s->s_cap_gen = 1;
	s->s_cap_ttl = jअगरfies - 1;

	spin_lock_init(&s->s_cap_lock);
	s->s_renew_requested = 0;
	s->s_renew_seq = 0;
	INIT_LIST_HEAD(&s->s_caps);
	s->s_nr_caps = 0;
	refcount_set(&s->s_ref, 1);
	INIT_LIST_HEAD(&s->s_रुकोing);
	INIT_LIST_HEAD(&s->s_unsafe);
	xa_init(&s->s_delegated_inos);
	s->s_num_cap_releases = 0;
	s->s_cap_reconnect = 0;
	s->s_cap_iterator = शून्य;
	INIT_LIST_HEAD(&s->s_cap_releases);
	INIT_WORK(&s->s_cap_release_work, ceph_cap_release_work);

	INIT_LIST_HEAD(&s->s_cap_dirty);
	INIT_LIST_HEAD(&s->s_cap_flushing);

	mdsc->sessions[mds] = s;
	atomic_inc(&mdsc->num_sessions);
	refcount_inc(&s->s_ref);  /* one ref to sessions[], one to caller */

	ceph_con_खोलो(&s->s_con, CEPH_ENTITY_TYPE_MDS, mds,
		      ceph_mdsmap_get_addr(mdsc->mdsmap, mds));

	वापस s;

fail_पुनः_स्मृति:
	kमुक्त(s);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/*
 * called under mdsc->mutex
 */
अटल व्योम __unरेजिस्टर_session(काष्ठा ceph_mds_client *mdsc,
			       काष्ठा ceph_mds_session *s)
अणु
	करोut("__unregister_session mds%d %p\n", s->s_mds, s);
	BUG_ON(mdsc->sessions[s->s_mds] != s);
	mdsc->sessions[s->s_mds] = शून्य;
	ceph_con_बंद(&s->s_con);
	ceph_put_mds_session(s);
	atomic_dec(&mdsc->num_sessions);
पूर्ण

/*
 * drop session refs in request.
 *
 * should be last request ref, or hold mdsc->mutex
 */
अटल व्योम put_request_session(काष्ठा ceph_mds_request *req)
अणु
	अगर (req->r_session) अणु
		ceph_put_mds_session(req->r_session);
		req->r_session = शून्य;
	पूर्ण
पूर्ण

व्योम ceph_mdsc_release_request(काष्ठा kref *kref)
अणु
	काष्ठा ceph_mds_request *req = container_of(kref,
						    काष्ठा ceph_mds_request,
						    r_kref);
	ceph_mdsc_release_dir_caps_no_check(req);
	destroy_reply_info(&req->r_reply_info);
	अगर (req->r_request)
		ceph_msg_put(req->r_request);
	अगर (req->r_reply)
		ceph_msg_put(req->r_reply);
	अगर (req->r_inode) अणु
		ceph_put_cap_refs(ceph_inode(req->r_inode), CEPH_CAP_PIN);
		/* aव्योम calling iput_final() in mds dispatch thपढ़ोs */
		ceph_async_iput(req->r_inode);
	पूर्ण
	अगर (req->r_parent) अणु
		ceph_put_cap_refs(ceph_inode(req->r_parent), CEPH_CAP_PIN);
		ceph_async_iput(req->r_parent);
	पूर्ण
	ceph_async_iput(req->r_target_inode);
	अगर (req->r_dentry)
		dput(req->r_dentry);
	अगर (req->r_old_dentry)
		dput(req->r_old_dentry);
	अगर (req->r_old_dentry_dir) अणु
		/*
		 * track (and drop pins क्रम) r_old_dentry_dir
		 * separately, since r_old_dentry's d_parent may have
		 * changed between the dir mutex being dropped and
		 * this request being मुक्तd.
		 */
		ceph_put_cap_refs(ceph_inode(req->r_old_dentry_dir),
				  CEPH_CAP_PIN);
		ceph_async_iput(req->r_old_dentry_dir);
	पूर्ण
	kमुक्त(req->r_path1);
	kमुक्त(req->r_path2);
	put_cred(req->r_cred);
	अगर (req->r_pagelist)
		ceph_pagelist_release(req->r_pagelist);
	put_request_session(req);
	ceph_unreserve_caps(req->r_mdsc, &req->r_caps_reservation);
	WARN_ON_ONCE(!list_empty(&req->r_रुको));
	kmem_cache_मुक्त(ceph_mds_request_cachep, req);
पूर्ण

DEFINE_RB_FUNCS(request, काष्ठा ceph_mds_request, r_tid, r_node)

/*
 * lookup session, bump ref अगर found.
 *
 * called under mdsc->mutex.
 */
अटल काष्ठा ceph_mds_request *
lookup_get_request(काष्ठा ceph_mds_client *mdsc, u64 tid)
अणु
	काष्ठा ceph_mds_request *req;

	req = lookup_request(&mdsc->request_tree, tid);
	अगर (req)
		ceph_mdsc_get_request(req);

	वापस req;
पूर्ण

/*
 * Register an in-flight request, and assign a tid.  Link to directory
 * are modअगरying (अगर any).
 *
 * Called under mdsc->mutex.
 */
अटल व्योम __रेजिस्टर_request(काष्ठा ceph_mds_client *mdsc,
			       काष्ठा ceph_mds_request *req,
			       काष्ठा inode *dir)
अणु
	पूर्णांक ret = 0;

	req->r_tid = ++mdsc->last_tid;
	अगर (req->r_num_caps) अणु
		ret = ceph_reserve_caps(mdsc, &req->r_caps_reservation,
					req->r_num_caps);
		अगर (ret < 0) अणु
			pr_err("__register_request %p "
			       "failed to reserve caps: %d\n", req, ret);
			/* set req->r_err to fail early from __करो_request */
			req->r_err = ret;
			वापस;
		पूर्ण
	पूर्ण
	करोut("__register_request %p tid %lld\n", req, req->r_tid);
	ceph_mdsc_get_request(req);
	insert_request(&mdsc->request_tree, req);

	req->r_cred = get_current_cred();

	अगर (mdsc->oldest_tid == 0 && req->r_op != CEPH_MDS_OP_SETखाताLOCK)
		mdsc->oldest_tid = req->r_tid;

	अगर (dir) अणु
		काष्ठा ceph_inode_info *ci = ceph_inode(dir);

		ihold(dir);
		req->r_unsafe_dir = dir;
		spin_lock(&ci->i_unsafe_lock);
		list_add_tail(&req->r_unsafe_dir_item, &ci->i_unsafe_dirops);
		spin_unlock(&ci->i_unsafe_lock);
	पूर्ण
पूर्ण

अटल व्योम __unरेजिस्टर_request(काष्ठा ceph_mds_client *mdsc,
				 काष्ठा ceph_mds_request *req)
अणु
	करोut("__unregister_request %p tid %lld\n", req, req->r_tid);

	/* Never leave an unरेजिस्टरed request on an unsafe list! */
	list_del_init(&req->r_unsafe_item);

	अगर (req->r_tid == mdsc->oldest_tid) अणु
		काष्ठा rb_node *p = rb_next(&req->r_node);
		mdsc->oldest_tid = 0;
		जबतक (p) अणु
			काष्ठा ceph_mds_request *next_req =
				rb_entry(p, काष्ठा ceph_mds_request, r_node);
			अगर (next_req->r_op != CEPH_MDS_OP_SETखाताLOCK) अणु
				mdsc->oldest_tid = next_req->r_tid;
				अवरोध;
			पूर्ण
			p = rb_next(p);
		पूर्ण
	पूर्ण

	erase_request(&mdsc->request_tree, req);

	अगर (req->r_unsafe_dir) अणु
		काष्ठा ceph_inode_info *ci = ceph_inode(req->r_unsafe_dir);
		spin_lock(&ci->i_unsafe_lock);
		list_del_init(&req->r_unsafe_dir_item);
		spin_unlock(&ci->i_unsafe_lock);
	पूर्ण
	अगर (req->r_target_inode &&
	    test_bit(CEPH_MDS_R_GOT_UNSAFE, &req->r_req_flags)) अणु
		काष्ठा ceph_inode_info *ci = ceph_inode(req->r_target_inode);
		spin_lock(&ci->i_unsafe_lock);
		list_del_init(&req->r_unsafe_target_item);
		spin_unlock(&ci->i_unsafe_lock);
	पूर्ण

	अगर (req->r_unsafe_dir) अणु
		/* aव्योम calling iput_final() in mds dispatch thपढ़ोs */
		ceph_async_iput(req->r_unsafe_dir);
		req->r_unsafe_dir = शून्य;
	पूर्ण

	complete_all(&req->r_safe_completion);

	ceph_mdsc_put_request(req);
पूर्ण

/*
 * Walk back up the dentry tree until we hit a dentry representing a
 * non-snapshot inode. We करो this using the rcu_पढ़ो_lock (which must be held
 * when calling this) to ensure that the objects won't disappear while we're
 * working with them. Once we hit a candidate dentry, we attempt to take a
 * reference to it, and वापस that as the result.
 */
अटल काष्ठा inode *get_nonsnap_parent(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = शून्य;

	जबतक (dentry && !IS_ROOT(dentry)) अणु
		inode = d_inode_rcu(dentry);
		अगर (!inode || ceph_snap(inode) == CEPH_NOSNAP)
			अवरोध;
		dentry = dentry->d_parent;
	पूर्ण
	अगर (inode)
		inode = igrab(inode);
	वापस inode;
पूर्ण

/*
 * Choose mds to send request to next.  If there is a hपूर्णांक set in the
 * request (e.g., due to a prior क्रमward hपूर्णांक from the mds), use that.
 * Otherwise, consult frag tree and/or caps to identअगरy the
 * appropriate mds.  If all अन्यथा fails, choose अक्रमomly.
 *
 * Called under mdsc->mutex.
 */
अटल पूर्णांक __choose_mds(काष्ठा ceph_mds_client *mdsc,
			काष्ठा ceph_mds_request *req,
			bool *अक्रमom)
अणु
	काष्ठा inode *inode;
	काष्ठा ceph_inode_info *ci;
	काष्ठा ceph_cap *cap;
	पूर्णांक mode = req->r_direct_mode;
	पूर्णांक mds = -1;
	u32 hash = req->r_direct_hash;
	bool is_hash = test_bit(CEPH_MDS_R_सूचीECT_IS_HASH, &req->r_req_flags);

	अगर (अक्रमom)
		*अक्रमom = false;

	/*
	 * is there a specअगरic mds we should try?  ignore hपूर्णांक अगर we have
	 * no session and the mds is not up (active or recovering).
	 */
	अगर (req->r_resend_mds >= 0 &&
	    (__have_session(mdsc, req->r_resend_mds) ||
	     ceph_mdsmap_get_state(mdsc->mdsmap, req->r_resend_mds) > 0)) अणु
		करोut("%s using resend_mds mds%d\n", __func__,
		     req->r_resend_mds);
		वापस req->r_resend_mds;
	पूर्ण

	अगर (mode == USE_RANDOM_MDS)
		जाओ अक्रमom;

	inode = शून्य;
	अगर (req->r_inode) अणु
		अगर (ceph_snap(req->r_inode) != CEPH_SNAPसूची) अणु
			inode = req->r_inode;
			ihold(inode);
		पूर्ण अन्यथा अणु
			/* req->r_dentry is non-null क्रम LSSNAP request */
			rcu_पढ़ो_lock();
			inode = get_nonsnap_parent(req->r_dentry);
			rcu_पढ़ो_unlock();
			करोut("%s using snapdir's parent %p\n", __func__, inode);
		पूर्ण
	पूर्ण अन्यथा अगर (req->r_dentry) अणु
		/* ignore race with नाम; old or new d_parent is okay */
		काष्ठा dentry *parent;
		काष्ठा inode *dir;

		rcu_पढ़ो_lock();
		parent = READ_ONCE(req->r_dentry->d_parent);
		dir = req->r_parent ? : d_inode_rcu(parent);

		अगर (!dir || dir->i_sb != mdsc->fsc->sb) अणु
			/*  not this fs or parent went negative */
			inode = d_inode(req->r_dentry);
			अगर (inode)
				ihold(inode);
		पूर्ण अन्यथा अगर (ceph_snap(dir) != CEPH_NOSNAP) अणु
			/* direct snapped/भव snapdir requests
			 * based on parent dir inode */
			inode = get_nonsnap_parent(parent);
			करोut("%s using nonsnap parent %p\n", __func__, inode);
		पूर्ण अन्यथा अणु
			/* dentry target */
			inode = d_inode(req->r_dentry);
			अगर (!inode || mode == USE_AUTH_MDS) अणु
				/* dir + name */
				inode = igrab(dir);
				hash = ceph_dentry_hash(dir, req->r_dentry);
				is_hash = true;
			पूर्ण अन्यथा अणु
				ihold(inode);
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	करोut("%s %p is_hash=%d (0x%x) mode %d\n", __func__, inode, (पूर्णांक)is_hash,
	     hash, mode);
	अगर (!inode)
		जाओ अक्रमom;
	ci = ceph_inode(inode);

	अगर (is_hash && S_ISसूची(inode->i_mode)) अणु
		काष्ठा ceph_inode_frag frag;
		पूर्णांक found;

		ceph_choose_frag(ci, hash, &frag, &found);
		अगर (found) अणु
			अगर (mode == USE_ANY_MDS && frag.ndist > 0) अणु
				u8 r;

				/* choose a अक्रमom replica */
				get_अक्रमom_bytes(&r, 1);
				r %= frag.ndist;
				mds = frag.dist[r];
				करोut("%s %p %llx.%llx frag %u mds%d (%d/%d)\n",
				     __func__, inode, ceph_vinop(inode),
				     frag.frag, mds, (पूर्णांक)r, frag.ndist);
				अगर (ceph_mdsmap_get_state(mdsc->mdsmap, mds) >=
				    CEPH_MDS_STATE_ACTIVE &&
				    !ceph_mdsmap_is_laggy(mdsc->mdsmap, mds))
					जाओ out;
			पूर्ण

			/* since this file/dir wasn't known to be
			 * replicated, then we want to look क्रम the
			 * authoritative mds. */
			अगर (frag.mds >= 0) अणु
				/* choose auth mds */
				mds = frag.mds;
				करोut("%s %p %llx.%llx frag %u mds%d (auth)\n",
				     __func__, inode, ceph_vinop(inode),
				     frag.frag, mds);
				अगर (ceph_mdsmap_get_state(mdsc->mdsmap, mds) >=
				    CEPH_MDS_STATE_ACTIVE) अणु
					अगर (!ceph_mdsmap_is_laggy(mdsc->mdsmap,
								  mds))
						जाओ out;
				पूर्ण
			पूर्ण
			mode = USE_AUTH_MDS;
		पूर्ण
	पूर्ण

	spin_lock(&ci->i_ceph_lock);
	cap = शून्य;
	अगर (mode == USE_AUTH_MDS)
		cap = ci->i_auth_cap;
	अगर (!cap && !RB_EMPTY_ROOT(&ci->i_caps))
		cap = rb_entry(rb_first(&ci->i_caps), काष्ठा ceph_cap, ci_node);
	अगर (!cap) अणु
		spin_unlock(&ci->i_ceph_lock);
		ceph_async_iput(inode);
		जाओ अक्रमom;
	पूर्ण
	mds = cap->session->s_mds;
	करोut("%s %p %llx.%llx mds%d (%scap %p)\n", __func__,
	     inode, ceph_vinop(inode), mds,
	     cap == ci->i_auth_cap ? "auth " : "", cap);
	spin_unlock(&ci->i_ceph_lock);
out:
	/* aव्योम calling iput_final() जबतक holding mdsc->mutex or
	 * in mds dispatch thपढ़ोs */
	ceph_async_iput(inode);
	वापस mds;

अक्रमom:
	अगर (अक्रमom)
		*अक्रमom = true;

	mds = ceph_mdsmap_get_अक्रमom_mds(mdsc->mdsmap);
	करोut("%s chose random mds%d\n", __func__, mds);
	वापस mds;
पूर्ण


/*
 * session messages
 */
अटल काष्ठा ceph_msg *create_session_msg(u32 op, u64 seq)
अणु
	काष्ठा ceph_msg *msg;
	काष्ठा ceph_mds_session_head *h;

	msg = ceph_msg_new(CEPH_MSG_CLIENT_SESSION, माप(*h), GFP_NOFS,
			   false);
	अगर (!msg) अणु
		pr_err("create_session_msg ENOMEM creating msg\n");
		वापस शून्य;
	पूर्ण
	h = msg->front.iov_base;
	h->op = cpu_to_le32(op);
	h->seq = cpu_to_le64(seq);

	वापस msg;
पूर्ण

अटल स्थिर अचिन्हित अक्षर feature_bits[] = CEPHFS_FEATURES_CLIENT_SUPPORTED;
#घोषणा FEATURE_BYTES(c) (DIV_ROUND_UP((माप_प्रकार)feature_bits[c - 1] + 1, 64) * 8)
अटल पूर्णांक encode_supported_features(व्योम **p, व्योम *end)
अणु
	अटल स्थिर माप_प्रकार count = ARRAY_SIZE(feature_bits);

	अगर (count > 0) अणु
		माप_प्रकार i;
		माप_प्रकार size = FEATURE_BYTES(count);

		अगर (WARN_ON_ONCE(*p + 4 + size > end))
			वापस -दुस्फल;

		ceph_encode_32(p, size);
		स_रखो(*p, 0, size);
		क्रम (i = 0; i < count; i++)
			((अचिन्हित अक्षर*)(*p))[i / 8] |= BIT(feature_bits[i] % 8);
		*p += size;
	पूर्ण अन्यथा अणु
		अगर (WARN_ON_ONCE(*p + 4 > end))
			वापस -दुस्फल;

		ceph_encode_32(p, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित अक्षर metric_bits[] = CEPHFS_METRIC_SPEC_CLIENT_SUPPORTED;
#घोषणा METRIC_BYTES(cnt) (DIV_ROUND_UP((माप_प्रकार)metric_bits[cnt - 1] + 1, 64) * 8)
अटल पूर्णांक encode_metric_spec(व्योम **p, व्योम *end)
अणु
	अटल स्थिर माप_प्रकार count = ARRAY_SIZE(metric_bits);

	/* header */
	अगर (WARN_ON_ONCE(*p + 2 > end))
		वापस -दुस्फल;

	ceph_encode_8(p, 1); /* version */
	ceph_encode_8(p, 1); /* compat */

	अगर (count > 0) अणु
		माप_प्रकार i;
		माप_प्रकार size = METRIC_BYTES(count);

		अगर (WARN_ON_ONCE(*p + 4 + 4 + size > end))
			वापस -दुस्फल;

		/* metric spec info length */
		ceph_encode_32(p, 4 + size);

		/* metric spec */
		ceph_encode_32(p, size);
		स_रखो(*p, 0, size);
		क्रम (i = 0; i < count; i++)
			((अचिन्हित अक्षर *)(*p))[i / 8] |= BIT(metric_bits[i] % 8);
		*p += size;
	पूर्ण अन्यथा अणु
		अगर (WARN_ON_ONCE(*p + 4 + 4 > end))
			वापस -दुस्फल;

		/* metric spec info length */
		ceph_encode_32(p, 4);
		/* metric spec */
		ceph_encode_32(p, 0);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * session message, specialization क्रम CEPH_SESSION_REQUEST_OPEN
 * to include additional client metadata fields.
 */
अटल काष्ठा ceph_msg *create_session_खोलो_msg(काष्ठा ceph_mds_client *mdsc, u64 seq)
अणु
	काष्ठा ceph_msg *msg;
	काष्ठा ceph_mds_session_head *h;
	पूर्णांक i;
	पूर्णांक extra_bytes = 0;
	पूर्णांक metadata_key_count = 0;
	काष्ठा ceph_options *opt = mdsc->fsc->client->options;
	काष्ठा ceph_mount_options *fsopt = mdsc->fsc->mount_options;
	माप_प्रकार size, count;
	व्योम *p, *end;
	पूर्णांक ret;

	स्थिर अक्षर* metadata[][2] = अणु
		अणु"hostname", mdsc->nodenameपूर्ण,
		अणु"kernel_version", init_utsname()->releaseपूर्ण,
		अणु"entity_id", opt->name ? : ""पूर्ण,
		अणु"root", fsopt->server_path ? : "/"पूर्ण,
		अणुशून्य, शून्यपूर्ण
	पूर्ण;

	/* Calculate serialized length of metadata */
	extra_bytes = 4;  /* map length */
	क्रम (i = 0; metadata[i][0]; ++i) अणु
		extra_bytes += 8 + म_माप(metadata[i][0]) +
			म_माप(metadata[i][1]);
		metadata_key_count++;
	पूर्ण

	/* supported feature */
	size = 0;
	count = ARRAY_SIZE(feature_bits);
	अगर (count > 0)
		size = FEATURE_BYTES(count);
	extra_bytes += 4 + size;

	/* metric spec */
	size = 0;
	count = ARRAY_SIZE(metric_bits);
	अगर (count > 0)
		size = METRIC_BYTES(count);
	extra_bytes += 2 + 4 + 4 + size;

	/* Allocate the message */
	msg = ceph_msg_new(CEPH_MSG_CLIENT_SESSION, माप(*h) + extra_bytes,
			   GFP_NOFS, false);
	अगर (!msg) अणु
		pr_err("create_session_msg ENOMEM creating msg\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	p = msg->front.iov_base;
	end = p + msg->front.iov_len;

	h = p;
	h->op = cpu_to_le32(CEPH_SESSION_REQUEST_OPEN);
	h->seq = cpu_to_le64(seq);

	/*
	 * Serialize client metadata पूर्णांकo रुकोing buffer space, using
	 * the क्रमmat that userspace expects क्रम map<string, string>
	 *
	 * ClientSession messages with metadata are v4
	 */
	msg->hdr.version = cpu_to_le16(4);
	msg->hdr.compat_version = cpu_to_le16(1);

	/* The ग_लिखो poपूर्णांकer, following the session_head काष्ठाure */
	p += माप(*h);

	/* Number of entries in the map */
	ceph_encode_32(&p, metadata_key_count);

	/* Two length-prefixed strings क्रम each entry in the map */
	क्रम (i = 0; metadata[i][0]; ++i) अणु
		माप_प्रकार स्थिर key_len = म_माप(metadata[i][0]);
		माप_प्रकार स्थिर val_len = म_माप(metadata[i][1]);

		ceph_encode_32(&p, key_len);
		स_नकल(p, metadata[i][0], key_len);
		p += key_len;
		ceph_encode_32(&p, val_len);
		स_नकल(p, metadata[i][1], val_len);
		p += val_len;
	पूर्ण

	ret = encode_supported_features(&p, end);
	अगर (ret) अणु
		pr_err("encode_supported_features failed!\n");
		ceph_msg_put(msg);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = encode_metric_spec(&p, end);
	अगर (ret) अणु
		pr_err("encode_metric_spec failed!\n");
		ceph_msg_put(msg);
		वापस ERR_PTR(ret);
	पूर्ण

	msg->front.iov_len = p - msg->front.iov_base;
	msg->hdr.front_len = cpu_to_le32(msg->front.iov_len);

	वापस msg;
पूर्ण

/*
 * send session खोलो request.
 *
 * called under mdsc->mutex
 */
अटल पूर्णांक __खोलो_session(काष्ठा ceph_mds_client *mdsc,
			  काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_msg *msg;
	पूर्णांक mstate;
	पूर्णांक mds = session->s_mds;

	/* रुको क्रम mds to go active? */
	mstate = ceph_mdsmap_get_state(mdsc->mdsmap, mds);
	करोut("open_session to mds%d (%s)\n", mds,
	     ceph_mds_state_name(mstate));
	session->s_state = CEPH_MDS_SESSION_OPENING;
	session->s_renew_requested = jअगरfies;

	/* send connect message */
	msg = create_session_खोलो_msg(mdsc, session->s_seq);
	अगर (IS_ERR(msg))
		वापस PTR_ERR(msg);
	ceph_con_send(&session->s_con, msg);
	वापस 0;
पूर्ण

/*
 * खोलो sessions क्रम any export tarमाला_लो क्रम the given mds
 *
 * called under mdsc->mutex
 */
अटल काष्ठा ceph_mds_session *
__खोलो_export_target_session(काष्ठा ceph_mds_client *mdsc, पूर्णांक target)
अणु
	काष्ठा ceph_mds_session *session;
	पूर्णांक ret;

	session = __ceph_lookup_mds_session(mdsc, target);
	अगर (!session) अणु
		session = रेजिस्टर_session(mdsc, target);
		अगर (IS_ERR(session))
			वापस session;
	पूर्ण
	अगर (session->s_state == CEPH_MDS_SESSION_NEW ||
	    session->s_state == CEPH_MDS_SESSION_CLOSING) अणु
		ret = __खोलो_session(mdsc, session);
		अगर (ret)
			वापस ERR_PTR(ret);
	पूर्ण

	वापस session;
पूर्ण

काष्ठा ceph_mds_session *
ceph_mdsc_खोलो_export_target_session(काष्ठा ceph_mds_client *mdsc, पूर्णांक target)
अणु
	काष्ठा ceph_mds_session *session;

	करोut("open_export_target_session to mds%d\n", target);

	mutex_lock(&mdsc->mutex);
	session = __खोलो_export_target_session(mdsc, target);
	mutex_unlock(&mdsc->mutex);

	वापस session;
पूर्ण

अटल व्योम __खोलो_export_target_sessions(काष्ठा ceph_mds_client *mdsc,
					  काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_mds_info *mi;
	काष्ठा ceph_mds_session *ts;
	पूर्णांक i, mds = session->s_mds;

	अगर (mds >= mdsc->mdsmap->possible_max_rank)
		वापस;

	mi = &mdsc->mdsmap->m_info[mds];
	करोut("open_export_target_sessions for mds%d (%d targets)\n",
	     session->s_mds, mi->num_export_tarमाला_लो);

	क्रम (i = 0; i < mi->num_export_tarमाला_लो; i++) अणु
		ts = __खोलो_export_target_session(mdsc, mi->export_tarमाला_लो[i]);
		अगर (!IS_ERR(ts))
			ceph_put_mds_session(ts);
	पूर्ण
पूर्ण

व्योम ceph_mdsc_खोलो_export_target_sessions(काष्ठा ceph_mds_client *mdsc,
					   काष्ठा ceph_mds_session *session)
अणु
	mutex_lock(&mdsc->mutex);
	__खोलो_export_target_sessions(mdsc, session);
	mutex_unlock(&mdsc->mutex);
पूर्ण

/*
 * session caps
 */

अटल व्योम detach_cap_releases(काष्ठा ceph_mds_session *session,
				काष्ठा list_head *target)
अणु
	lockdep_निश्चित_held(&session->s_cap_lock);

	list_splice_init(&session->s_cap_releases, target);
	session->s_num_cap_releases = 0;
	करोut("dispose_cap_releases mds%d\n", session->s_mds);
पूर्ण

अटल व्योम dispose_cap_releases(काष्ठा ceph_mds_client *mdsc,
				 काष्ठा list_head *dispose)
अणु
	जबतक (!list_empty(dispose)) अणु
		काष्ठा ceph_cap *cap;
		/* zero out the in-progress message */
		cap = list_first_entry(dispose, काष्ठा ceph_cap, session_caps);
		list_del(&cap->session_caps);
		ceph_put_cap(mdsc, cap);
	पूर्ण
पूर्ण

अटल व्योम cleanup_session_requests(काष्ठा ceph_mds_client *mdsc,
				     काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_mds_request *req;
	काष्ठा rb_node *p;
	काष्ठा ceph_inode_info *ci;

	करोut("cleanup_session_requests mds%d\n", session->s_mds);
	mutex_lock(&mdsc->mutex);
	जबतक (!list_empty(&session->s_unsafe)) अणु
		req = list_first_entry(&session->s_unsafe,
				       काष्ठा ceph_mds_request, r_unsafe_item);
		pr_warn_ratelimited(" dropping unsafe request %llu\n",
				    req->r_tid);
		अगर (req->r_target_inode) अणु
			/* dropping unsafe change of inode's attributes */
			ci = ceph_inode(req->r_target_inode);
			errseq_set(&ci->i_meta_err, -EIO);
		पूर्ण
		अगर (req->r_unsafe_dir) अणु
			/* dropping unsafe directory operation */
			ci = ceph_inode(req->r_unsafe_dir);
			errseq_set(&ci->i_meta_err, -EIO);
		पूर्ण
		__unरेजिस्टर_request(mdsc, req);
	पूर्ण
	/* zero r_attempts, so kick_requests() will re-send requests */
	p = rb_first(&mdsc->request_tree);
	जबतक (p) अणु
		req = rb_entry(p, काष्ठा ceph_mds_request, r_node);
		p = rb_next(p);
		अगर (req->r_session &&
		    req->r_session->s_mds == session->s_mds)
			req->r_attempts = 0;
	पूर्ण
	mutex_unlock(&mdsc->mutex);
पूर्ण

/*
 * Helper to safely iterate over all caps associated with a session, with
 * special care taken to handle a racing __ceph_हटाओ_cap().
 *
 * Caller must hold session s_mutex.
 */
पूर्णांक ceph_iterate_session_caps(काष्ठा ceph_mds_session *session,
			      पूर्णांक (*cb)(काष्ठा inode *, काष्ठा ceph_cap *,
					व्योम *), व्योम *arg)
अणु
	काष्ठा list_head *p;
	काष्ठा ceph_cap *cap;
	काष्ठा inode *inode, *last_inode = शून्य;
	काष्ठा ceph_cap *old_cap = शून्य;
	पूर्णांक ret;

	करोut("iterate_session_caps %p mds%d\n", session, session->s_mds);
	spin_lock(&session->s_cap_lock);
	p = session->s_caps.next;
	जबतक (p != &session->s_caps) अणु
		cap = list_entry(p, काष्ठा ceph_cap, session_caps);
		inode = igrab(&cap->ci->vfs_inode);
		अगर (!inode) अणु
			p = p->next;
			जारी;
		पूर्ण
		session->s_cap_iterator = cap;
		spin_unlock(&session->s_cap_lock);

		अगर (last_inode) अणु
			/* aव्योम calling iput_final() जबतक holding
			 * s_mutex or in mds dispatch thपढ़ोs */
			ceph_async_iput(last_inode);
			last_inode = शून्य;
		पूर्ण
		अगर (old_cap) अणु
			ceph_put_cap(session->s_mdsc, old_cap);
			old_cap = शून्य;
		पूर्ण

		ret = cb(inode, cap, arg);
		last_inode = inode;

		spin_lock(&session->s_cap_lock);
		p = p->next;
		अगर (!cap->ci) अणु
			करोut("iterate_session_caps  finishing cap %p removal\n",
			     cap);
			BUG_ON(cap->session != session);
			cap->session = शून्य;
			list_del_init(&cap->session_caps);
			session->s_nr_caps--;
			atomic64_dec(&session->s_mdsc->metric.total_caps);
			अगर (cap->queue_release)
				__ceph_queue_cap_release(session, cap);
			अन्यथा
				old_cap = cap;  /* put_cap it w/o locks held */
		पूर्ण
		अगर (ret < 0)
			जाओ out;
	पूर्ण
	ret = 0;
out:
	session->s_cap_iterator = शून्य;
	spin_unlock(&session->s_cap_lock);

	ceph_async_iput(last_inode);
	अगर (old_cap)
		ceph_put_cap(session->s_mdsc, old_cap);

	वापस ret;
पूर्ण

अटल पूर्णांक हटाओ_session_caps_cb(काष्ठा inode *inode, काष्ठा ceph_cap *cap,
				  व्योम *arg)
अणु
	काष्ठा ceph_fs_client *fsc = (काष्ठा ceph_fs_client *)arg;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	LIST_HEAD(to_हटाओ);
	bool dirty_dropped = false;
	bool invalidate = false;

	करोut("removing cap %p, ci is %p, inode is %p\n",
	     cap, ci, &ci->vfs_inode);
	spin_lock(&ci->i_ceph_lock);
	__ceph_हटाओ_cap(cap, false);
	अगर (!ci->i_auth_cap) अणु
		काष्ठा ceph_cap_flush *cf;
		काष्ठा ceph_mds_client *mdsc = fsc->mdsc;

		अगर (READ_ONCE(fsc->mount_state) >= CEPH_MOUNT_SHUTDOWN) अणु
			अगर (inode->i_data.nrpages > 0)
				invalidate = true;
			अगर (ci->i_wrbuffer_ref > 0)
				mapping_set_error(&inode->i_data, -EIO);
		पूर्ण

		जबतक (!list_empty(&ci->i_cap_flush_list)) अणु
			cf = list_first_entry(&ci->i_cap_flush_list,
					      काष्ठा ceph_cap_flush, i_list);
			list_move(&cf->i_list, &to_हटाओ);
		पूर्ण

		spin_lock(&mdsc->cap_dirty_lock);

		list_क्रम_each_entry(cf, &to_हटाओ, i_list)
			list_del(&cf->g_list);

		अगर (!list_empty(&ci->i_dirty_item)) अणु
			pr_warn_ratelimited(
				" dropping dirty %s state for %p %lld\n",
				ceph_cap_string(ci->i_dirty_caps),
				inode, ceph_ino(inode));
			ci->i_dirty_caps = 0;
			list_del_init(&ci->i_dirty_item);
			dirty_dropped = true;
		पूर्ण
		अगर (!list_empty(&ci->i_flushing_item)) अणु
			pr_warn_ratelimited(
				" dropping dirty+flushing %s state for %p %lld\n",
				ceph_cap_string(ci->i_flushing_caps),
				inode, ceph_ino(inode));
			ci->i_flushing_caps = 0;
			list_del_init(&ci->i_flushing_item);
			mdsc->num_cap_flushing--;
			dirty_dropped = true;
		पूर्ण
		spin_unlock(&mdsc->cap_dirty_lock);

		अगर (dirty_dropped) अणु
			errseq_set(&ci->i_meta_err, -EIO);

			अगर (ci->i_wrbuffer_ref_head == 0 &&
			    ci->i_wr_ref == 0 &&
			    ci->i_dirty_caps == 0 &&
			    ci->i_flushing_caps == 0) अणु
				ceph_put_snap_context(ci->i_head_snapc);
				ci->i_head_snapc = शून्य;
			पूर्ण
		पूर्ण

		अगर (atomic_पढ़ो(&ci->i_filelock_ref) > 0) अणु
			/* make further file lock syscall वापस -EIO */
			ci->i_ceph_flags |= CEPH_I_ERROR_खाताLOCK;
			pr_warn_ratelimited(" dropping file locks for %p %lld\n",
					    inode, ceph_ino(inode));
		पूर्ण

		अगर (!ci->i_dirty_caps && ci->i_pपुनः_स्मृति_cap_flush) अणु
			list_add(&ci->i_pपुनः_स्मृति_cap_flush->i_list, &to_हटाओ);
			ci->i_pपुनः_स्मृति_cap_flush = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);
	जबतक (!list_empty(&to_हटाओ)) अणु
		काष्ठा ceph_cap_flush *cf;
		cf = list_first_entry(&to_हटाओ,
				      काष्ठा ceph_cap_flush, i_list);
		list_del(&cf->i_list);
		ceph_मुक्त_cap_flush(cf);
	पूर्ण

	wake_up_all(&ci->i_cap_wq);
	अगर (invalidate)
		ceph_queue_invalidate(inode);
	अगर (dirty_dropped)
		iput(inode);
	वापस 0;
पूर्ण

/*
 * caller must hold session s_mutex
 */
अटल व्योम हटाओ_session_caps(काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_fs_client *fsc = session->s_mdsc->fsc;
	काष्ठा super_block *sb = fsc->sb;
	LIST_HEAD(dispose);

	करोut("remove_session_caps on %p\n", session);
	ceph_iterate_session_caps(session, हटाओ_session_caps_cb, fsc);

	wake_up_all(&fsc->mdsc->cap_flushing_wq);

	spin_lock(&session->s_cap_lock);
	अगर (session->s_nr_caps > 0) अणु
		काष्ठा inode *inode;
		काष्ठा ceph_cap *cap, *prev = शून्य;
		काष्ठा ceph_vino vino;
		/*
		 * iterate_session_caps() skips inodes that are being
		 * deleted, we need to रुको until deletions are complete.
		 * __रुको_on_मुक्तing_inode() is deचिन्हित क्रम the job,
		 * but it is not exported, so use lookup inode function
		 * to access it.
		 */
		जबतक (!list_empty(&session->s_caps)) अणु
			cap = list_entry(session->s_caps.next,
					 काष्ठा ceph_cap, session_caps);
			अगर (cap == prev)
				अवरोध;
			prev = cap;
			vino = cap->ci->i_vino;
			spin_unlock(&session->s_cap_lock);

			inode = ceph_find_inode(sb, vino);
			 /* aव्योम calling iput_final() जबतक holding s_mutex */
			ceph_async_iput(inode);

			spin_lock(&session->s_cap_lock);
		पूर्ण
	पूर्ण

	// drop cap expires and unlock s_cap_lock
	detach_cap_releases(session, &dispose);

	BUG_ON(session->s_nr_caps > 0);
	BUG_ON(!list_empty(&session->s_cap_flushing));
	spin_unlock(&session->s_cap_lock);
	dispose_cap_releases(session->s_mdsc, &dispose);
पूर्ण

क्रमागत अणु
	RECONNECT,
	RENEWCAPS,
	FORCE_RO,
पूर्ण;

/*
 * wake up any thपढ़ोs रुकोing on this session's caps.  अगर the cap is
 * old (didn't get renewed on the client reconnect), हटाओ it now.
 *
 * caller must hold s_mutex.
 */
अटल पूर्णांक wake_up_session_cb(काष्ठा inode *inode, काष्ठा ceph_cap *cap,
			      व्योम *arg)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	अचिन्हित दीर्घ ev = (अचिन्हित दीर्घ)arg;

	अगर (ev == RECONNECT) अणु
		spin_lock(&ci->i_ceph_lock);
		ci->i_wanted_max_size = 0;
		ci->i_requested_max_size = 0;
		spin_unlock(&ci->i_ceph_lock);
	पूर्ण अन्यथा अगर (ev == RENEWCAPS) अणु
		अगर (cap->cap_gen < cap->session->s_cap_gen) अणु
			/* mds did not re-issue stale cap */
			spin_lock(&ci->i_ceph_lock);
			cap->issued = cap->implemented = CEPH_CAP_PIN;
			spin_unlock(&ci->i_ceph_lock);
		पूर्ण
	पूर्ण अन्यथा अगर (ev == FORCE_RO) अणु
	पूर्ण
	wake_up_all(&ci->i_cap_wq);
	वापस 0;
पूर्ण

अटल व्योम wake_up_session_caps(काष्ठा ceph_mds_session *session, पूर्णांक ev)
अणु
	करोut("wake_up_session_caps %p mds%d\n", session, session->s_mds);
	ceph_iterate_session_caps(session, wake_up_session_cb,
				  (व्योम *)(अचिन्हित दीर्घ)ev);
पूर्ण

/*
 * Send periodic message to MDS renewing all currently held caps.  The
 * ack will reset the expiration क्रम all caps from this session.
 *
 * caller holds s_mutex
 */
अटल पूर्णांक send_renew_caps(काष्ठा ceph_mds_client *mdsc,
			   काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_msg *msg;
	पूर्णांक state;

	अगर (समय_after_eq(jअगरfies, session->s_cap_ttl) &&
	    समय_after_eq(session->s_cap_ttl, session->s_renew_requested))
		pr_info("mds%d caps stale\n", session->s_mds);
	session->s_renew_requested = jअगरfies;

	/* करो not try to renew caps until a recovering mds has reconnected
	 * with its clients. */
	state = ceph_mdsmap_get_state(mdsc->mdsmap, session->s_mds);
	अगर (state < CEPH_MDS_STATE_RECONNECT) अणु
		करोut("send_renew_caps ignoring mds%d (%s)\n",
		     session->s_mds, ceph_mds_state_name(state));
		वापस 0;
	पूर्ण

	करोut("send_renew_caps to mds%d (%s)\n", session->s_mds,
		ceph_mds_state_name(state));
	msg = create_session_msg(CEPH_SESSION_REQUEST_RENEWCAPS,
				 ++session->s_renew_seq);
	अगर (!msg)
		वापस -ENOMEM;
	ceph_con_send(&session->s_con, msg);
	वापस 0;
पूर्ण

अटल पूर्णांक send_flushmsg_ack(काष्ठा ceph_mds_client *mdsc,
			     काष्ठा ceph_mds_session *session, u64 seq)
अणु
	काष्ठा ceph_msg *msg;

	करोut("send_flushmsg_ack to mds%d (%s)s seq %lld\n",
	     session->s_mds, ceph_session_state_name(session->s_state), seq);
	msg = create_session_msg(CEPH_SESSION_FLUSHMSG_ACK, seq);
	अगर (!msg)
		वापस -ENOMEM;
	ceph_con_send(&session->s_con, msg);
	वापस 0;
पूर्ण


/*
 * Note new cap ttl, and any transition from stale -> not stale (fresh?).
 *
 * Called under session->s_mutex
 */
अटल व्योम renewed_caps(काष्ठा ceph_mds_client *mdsc,
			 काष्ठा ceph_mds_session *session, पूर्णांक is_renew)
अणु
	पूर्णांक was_stale;
	पूर्णांक wake = 0;

	spin_lock(&session->s_cap_lock);
	was_stale = is_renew && समय_after_eq(jअगरfies, session->s_cap_ttl);

	session->s_cap_ttl = session->s_renew_requested +
		mdsc->mdsmap->m_session_समयout*HZ;

	अगर (was_stale) अणु
		अगर (समय_beक्रमe(jअगरfies, session->s_cap_ttl)) अणु
			pr_info("mds%d caps renewed\n", session->s_mds);
			wake = 1;
		पूर्ण अन्यथा अणु
			pr_info("mds%d caps still stale\n", session->s_mds);
		पूर्ण
	पूर्ण
	करोut("renewed_caps mds%d ttl now %lu, was %s, now %s\n",
	     session->s_mds, session->s_cap_ttl, was_stale ? "stale" : "fresh",
	     समय_beक्रमe(jअगरfies, session->s_cap_ttl) ? "stale" : "fresh");
	spin_unlock(&session->s_cap_lock);

	अगर (wake)
		wake_up_session_caps(session, RENEWCAPS);
पूर्ण

/*
 * send a session बंद request
 */
अटल पूर्णांक request_बंद_session(काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_msg *msg;

	करोut("request_close_session mds%d state %s seq %lld\n",
	     session->s_mds, ceph_session_state_name(session->s_state),
	     session->s_seq);
	msg = create_session_msg(CEPH_SESSION_REQUEST_CLOSE, session->s_seq);
	अगर (!msg)
		वापस -ENOMEM;
	ceph_con_send(&session->s_con, msg);
	वापस 1;
पूर्ण

/*
 * Called with s_mutex held.
 */
अटल पूर्णांक __बंद_session(काष्ठा ceph_mds_client *mdsc,
			 काष्ठा ceph_mds_session *session)
अणु
	अगर (session->s_state >= CEPH_MDS_SESSION_CLOSING)
		वापस 0;
	session->s_state = CEPH_MDS_SESSION_CLOSING;
	वापस request_बंद_session(session);
पूर्ण

अटल bool drop_negative_children(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *child;
	bool all_negative = true;

	अगर (!d_is_dir(dentry))
		जाओ out;

	spin_lock(&dentry->d_lock);
	list_क्रम_each_entry(child, &dentry->d_subdirs, d_child) अणु
		अगर (d_really_is_positive(child)) अणु
			all_negative = false;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&dentry->d_lock);

	अगर (all_negative)
		shrink_dcache_parent(dentry);
out:
	वापस all_negative;
पूर्ण

/*
 * Trim old(er) caps.
 *
 * Because we can't cache an inode without one or more caps, we करो
 * this indirectly: अगर a cap is unused, we prune its aliases, at which
 * poपूर्णांक the inode will hopefully get dropped to.
 *
 * Yes, this is a bit sloppy.  Our only real goal here is to respond to
 * memory pressure from the MDS, though, so it needn't be perfect.
 */
अटल पूर्णांक trim_caps_cb(काष्ठा inode *inode, काष्ठा ceph_cap *cap, व्योम *arg)
अणु
	पूर्णांक *reमुख्यing = arg;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक used, wanted, oissued, mine;

	अगर (*reमुख्यing <= 0)
		वापस -1;

	spin_lock(&ci->i_ceph_lock);
	mine = cap->issued | cap->implemented;
	used = __ceph_caps_used(ci);
	wanted = __ceph_caps_file_wanted(ci);
	oissued = __ceph_caps_issued_other(ci, cap);

	करोut("trim_caps_cb %p cap %p mine %s oissued %s used %s wanted %s\n",
	     inode, cap, ceph_cap_string(mine), ceph_cap_string(oissued),
	     ceph_cap_string(used), ceph_cap_string(wanted));
	अगर (cap == ci->i_auth_cap) अणु
		अगर (ci->i_dirty_caps || ci->i_flushing_caps ||
		    !list_empty(&ci->i_cap_snaps))
			जाओ out;
		अगर ((used | wanted) & CEPH_CAP_ANY_WR)
			जाओ out;
		/* Note: it's possible that i_filelock_ref becomes non-zero
		 * after dropping auth caps. It करोesn't hurt because reply
		 * of lock mds request will re-add auth caps. */
		अगर (atomic_पढ़ो(&ci->i_filelock_ref) > 0)
			जाओ out;
	पूर्ण
	/* The inode has cached pages, but it's no दीर्घer used.
	 * we can safely drop it */
	अगर (S_ISREG(inode->i_mode) &&
	    wanted == 0 && used == CEPH_CAP_खाता_CACHE &&
	    !(oissued & CEPH_CAP_खाता_CACHE)) अणु
	  used = 0;
	  oissued = 0;
	पूर्ण
	अगर ((used | wanted) & ~oissued & mine)
		जाओ out;   /* we need these caps */

	अगर (oissued) अणु
		/* we aren't the only cap.. just हटाओ us */
		__ceph_हटाओ_cap(cap, true);
		(*reमुख्यing)--;
	पूर्ण अन्यथा अणु
		काष्ठा dentry *dentry;
		/* try dropping referring dentries */
		spin_unlock(&ci->i_ceph_lock);
		dentry = d_find_any_alias(inode);
		अगर (dentry && drop_negative_children(dentry)) अणु
			पूर्णांक count;
			dput(dentry);
			d_prune_aliases(inode);
			count = atomic_पढ़ो(&inode->i_count);
			अगर (count == 1)
				(*reमुख्यing)--;
			करोut("trim_caps_cb %p cap %p pruned, count now %d\n",
			     inode, cap, count);
		पूर्ण अन्यथा अणु
			dput(dentry);
		पूर्ण
		वापस 0;
	पूर्ण

out:
	spin_unlock(&ci->i_ceph_lock);
	वापस 0;
पूर्ण

/*
 * Trim session cap count करोwn to some max number.
 */
पूर्णांक ceph_trim_caps(काष्ठा ceph_mds_client *mdsc,
		   काष्ठा ceph_mds_session *session,
		   पूर्णांक max_caps)
अणु
	पूर्णांक trim_caps = session->s_nr_caps - max_caps;

	करोut("trim_caps mds%d start: %d / %d, trim %d\n",
	     session->s_mds, session->s_nr_caps, max_caps, trim_caps);
	अगर (trim_caps > 0) अणु
		पूर्णांक reमुख्यing = trim_caps;

		ceph_iterate_session_caps(session, trim_caps_cb, &reमुख्यing);
		करोut("trim_caps mds%d done: %d / %d, trimmed %d\n",
		     session->s_mds, session->s_nr_caps, max_caps,
			trim_caps - reमुख्यing);
	पूर्ण

	ceph_flush_cap_releases(mdsc, session);
	वापस 0;
पूर्ण

अटल पूर्णांक check_caps_flush(काष्ठा ceph_mds_client *mdsc,
			    u64 want_flush_tid)
अणु
	पूर्णांक ret = 1;

	spin_lock(&mdsc->cap_dirty_lock);
	अगर (!list_empty(&mdsc->cap_flush_list)) अणु
		काष्ठा ceph_cap_flush *cf =
			list_first_entry(&mdsc->cap_flush_list,
					 काष्ठा ceph_cap_flush, g_list);
		अगर (cf->tid <= want_flush_tid) अणु
			करोut("check_caps_flush still flushing tid "
			     "%llu <= %llu\n", cf->tid, want_flush_tid);
			ret = 0;
		पूर्ण
	पूर्ण
	spin_unlock(&mdsc->cap_dirty_lock);
	वापस ret;
पूर्ण

/*
 * flush all dirty inode data to disk.
 *
 * वापसs true अगर we've flushed through want_flush_tid
 */
अटल व्योम रुको_caps_flush(काष्ठा ceph_mds_client *mdsc,
			    u64 want_flush_tid)
अणु
	करोut("check_caps_flush want %llu\n", want_flush_tid);

	रुको_event(mdsc->cap_flushing_wq,
		   check_caps_flush(mdsc, want_flush_tid));

	करोut("check_caps_flush ok, flushed thru %llu\n", want_flush_tid);
पूर्ण

/*
 * called under s_mutex
 */
अटल व्योम ceph_send_cap_releases(काष्ठा ceph_mds_client *mdsc,
				   काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_msg *msg = शून्य;
	काष्ठा ceph_mds_cap_release *head;
	काष्ठा ceph_mds_cap_item *item;
	काष्ठा ceph_osd_client *osdc = &mdsc->fsc->client->osdc;
	काष्ठा ceph_cap *cap;
	LIST_HEAD(पंचांगp_list);
	पूर्णांक num_cap_releases;
	__le32	barrier, *cap_barrier;

	करोwn_पढ़ो(&osdc->lock);
	barrier = cpu_to_le32(osdc->epoch_barrier);
	up_पढ़ो(&osdc->lock);

	spin_lock(&session->s_cap_lock);
again:
	list_splice_init(&session->s_cap_releases, &पंचांगp_list);
	num_cap_releases = session->s_num_cap_releases;
	session->s_num_cap_releases = 0;
	spin_unlock(&session->s_cap_lock);

	जबतक (!list_empty(&पंचांगp_list)) अणु
		अगर (!msg) अणु
			msg = ceph_msg_new(CEPH_MSG_CLIENT_CAPRELEASE,
					PAGE_SIZE, GFP_NOFS, false);
			अगर (!msg)
				जाओ out_err;
			head = msg->front.iov_base;
			head->num = cpu_to_le32(0);
			msg->front.iov_len = माप(*head);

			msg->hdr.version = cpu_to_le16(2);
			msg->hdr.compat_version = cpu_to_le16(1);
		पूर्ण

		cap = list_first_entry(&पंचांगp_list, काष्ठा ceph_cap,
					session_caps);
		list_del(&cap->session_caps);
		num_cap_releases--;

		head = msg->front.iov_base;
		put_unaligned_le32(get_unaligned_le32(&head->num) + 1,
				   &head->num);
		item = msg->front.iov_base + msg->front.iov_len;
		item->ino = cpu_to_le64(cap->cap_ino);
		item->cap_id = cpu_to_le64(cap->cap_id);
		item->migrate_seq = cpu_to_le32(cap->mseq);
		item->seq = cpu_to_le32(cap->issue_seq);
		msg->front.iov_len += माप(*item);

		ceph_put_cap(mdsc, cap);

		अगर (le32_to_cpu(head->num) == CEPH_CAPS_PER_RELEASE) अणु
			// Append cap_barrier field
			cap_barrier = msg->front.iov_base + msg->front.iov_len;
			*cap_barrier = barrier;
			msg->front.iov_len += माप(*cap_barrier);

			msg->hdr.front_len = cpu_to_le32(msg->front.iov_len);
			करोut("send_cap_releases mds%d %p\n", session->s_mds, msg);
			ceph_con_send(&session->s_con, msg);
			msg = शून्य;
		पूर्ण
	पूर्ण

	BUG_ON(num_cap_releases != 0);

	spin_lock(&session->s_cap_lock);
	अगर (!list_empty(&session->s_cap_releases))
		जाओ again;
	spin_unlock(&session->s_cap_lock);

	अगर (msg) अणु
		// Append cap_barrier field
		cap_barrier = msg->front.iov_base + msg->front.iov_len;
		*cap_barrier = barrier;
		msg->front.iov_len += माप(*cap_barrier);

		msg->hdr.front_len = cpu_to_le32(msg->front.iov_len);
		करोut("send_cap_releases mds%d %p\n", session->s_mds, msg);
		ceph_con_send(&session->s_con, msg);
	पूर्ण
	वापस;
out_err:
	pr_err("send_cap_releases mds%d, failed to allocate message\n",
		session->s_mds);
	spin_lock(&session->s_cap_lock);
	list_splice(&पंचांगp_list, &session->s_cap_releases);
	session->s_num_cap_releases += num_cap_releases;
	spin_unlock(&session->s_cap_lock);
पूर्ण

अटल व्योम ceph_cap_release_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ceph_mds_session *session =
		container_of(work, काष्ठा ceph_mds_session, s_cap_release_work);

	mutex_lock(&session->s_mutex);
	अगर (session->s_state == CEPH_MDS_SESSION_OPEN ||
	    session->s_state == CEPH_MDS_SESSION_HUNG)
		ceph_send_cap_releases(session->s_mdsc, session);
	mutex_unlock(&session->s_mutex);
	ceph_put_mds_session(session);
पूर्ण

व्योम ceph_flush_cap_releases(काष्ठा ceph_mds_client *mdsc,
		             काष्ठा ceph_mds_session *session)
अणु
	अगर (mdsc->stopping)
		वापस;

	ceph_get_mds_session(session);
	अगर (queue_work(mdsc->fsc->cap_wq,
		       &session->s_cap_release_work)) अणु
		करोut("cap release work queued\n");
	पूर्ण अन्यथा अणु
		ceph_put_mds_session(session);
		करोut("failed to queue cap release work\n");
	पूर्ण
पूर्ण

/*
 * caller holds session->s_cap_lock
 */
व्योम __ceph_queue_cap_release(काष्ठा ceph_mds_session *session,
			      काष्ठा ceph_cap *cap)
अणु
	list_add_tail(&cap->session_caps, &session->s_cap_releases);
	session->s_num_cap_releases++;

	अगर (!(session->s_num_cap_releases % CEPH_CAPS_PER_RELEASE))
		ceph_flush_cap_releases(session->s_mdsc, session);
पूर्ण

अटल व्योम ceph_cap_reclaim_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ceph_mds_client *mdsc =
		container_of(work, काष्ठा ceph_mds_client, cap_reclaim_work);
	पूर्णांक ret = ceph_trim_dentries(mdsc);
	अगर (ret == -EAGAIN)
		ceph_queue_cap_reclaim_work(mdsc);
पूर्ण

व्योम ceph_queue_cap_reclaim_work(काष्ठा ceph_mds_client *mdsc)
अणु
	अगर (mdsc->stopping)
		वापस;

        अगर (queue_work(mdsc->fsc->cap_wq, &mdsc->cap_reclaim_work)) अणु
                करोut("caps reclaim work queued\n");
        पूर्ण अन्यथा अणु
                करोut("failed to queue caps release work\n");
        पूर्ण
पूर्ण

व्योम ceph_reclaim_caps_nr(काष्ठा ceph_mds_client *mdsc, पूर्णांक nr)
अणु
	पूर्णांक val;
	अगर (!nr)
		वापस;
	val = atomic_add_वापस(nr, &mdsc->cap_reclaim_pending);
	अगर ((val % CEPH_CAPS_PER_RELEASE) < nr) अणु
		atomic_set(&mdsc->cap_reclaim_pending, 0);
		ceph_queue_cap_reclaim_work(mdsc);
	पूर्ण
पूर्ण

/*
 * requests
 */

पूर्णांक ceph_alloc_सूची_पढ़ो_reply_buffer(काष्ठा ceph_mds_request *req,
				    काष्ठा inode *dir)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(dir);
	काष्ठा ceph_mds_reply_info_parsed *rinfo = &req->r_reply_info;
	काष्ठा ceph_mount_options *opt = req->r_mdsc->fsc->mount_options;
	माप_प्रकार size = माप(काष्ठा ceph_mds_reply_dir_entry);
	अचिन्हित पूर्णांक num_entries;
	पूर्णांक order;

	spin_lock(&ci->i_ceph_lock);
	num_entries = ci->i_files + ci->i_subdirs;
	spin_unlock(&ci->i_ceph_lock);
	num_entries = max(num_entries, 1U);
	num_entries = min(num_entries, opt->max_सूची_पढ़ो);

	order = get_order(size * num_entries);
	जबतक (order >= 0) अणु
		rinfo->dir_entries = (व्योम*)__get_मुक्त_pages(GFP_KERNEL |
							     __GFP_NOWARN,
							     order);
		अगर (rinfo->dir_entries)
			अवरोध;
		order--;
	पूर्ण
	अगर (!rinfo->dir_entries)
		वापस -ENOMEM;

	num_entries = (PAGE_SIZE << order) / size;
	num_entries = min(num_entries, opt->max_सूची_पढ़ो);

	rinfo->dir_buf_size = PAGE_SIZE << order;
	req->r_num_caps = num_entries + 1;
	req->r_args.सूची_पढ़ो.max_entries = cpu_to_le32(num_entries);
	req->r_args.सूची_पढ़ो.max_bytes = cpu_to_le32(opt->max_सूची_पढ़ो_bytes);
	वापस 0;
पूर्ण

/*
 * Create an mds request.
 */
काष्ठा ceph_mds_request *
ceph_mdsc_create_request(काष्ठा ceph_mds_client *mdsc, पूर्णांक op, पूर्णांक mode)
अणु
	काष्ठा ceph_mds_request *req;

	req = kmem_cache_zalloc(ceph_mds_request_cachep, GFP_NOFS);
	अगर (!req)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&req->r_fill_mutex);
	req->r_mdsc = mdsc;
	req->r_started = jअगरfies;
	req->r_start_latency = kसमय_get();
	req->r_resend_mds = -1;
	INIT_LIST_HEAD(&req->r_unsafe_dir_item);
	INIT_LIST_HEAD(&req->r_unsafe_target_item);
	req->r_भ_शेषe = -1;
	kref_init(&req->r_kref);
	RB_CLEAR_NODE(&req->r_node);
	INIT_LIST_HEAD(&req->r_रुको);
	init_completion(&req->r_completion);
	init_completion(&req->r_safe_completion);
	INIT_LIST_HEAD(&req->r_unsafe_item);

	kसमय_get_coarse_real_ts64(&req->r_stamp);

	req->r_op = op;
	req->r_direct_mode = mode;
	वापस req;
पूर्ण

/*
 * वापस oldest (lowest) request, tid in request tree, 0 अगर none.
 *
 * called under mdsc->mutex.
 */
अटल काष्ठा ceph_mds_request *__get_oldest_req(काष्ठा ceph_mds_client *mdsc)
अणु
	अगर (RB_EMPTY_ROOT(&mdsc->request_tree))
		वापस शून्य;
	वापस rb_entry(rb_first(&mdsc->request_tree),
			काष्ठा ceph_mds_request, r_node);
पूर्ण

अटल अंतरभूत  u64 __get_oldest_tid(काष्ठा ceph_mds_client *mdsc)
अणु
	वापस mdsc->oldest_tid;
पूर्ण

/*
 * Build a dentry's path.  Allocate on heap; caller must kमुक्त.  Based
 * on build_path_from_dentry in fs/cअगरs/dir.c.
 *
 * If @stop_on_nosnap, generate path relative to the first non-snapped
 * inode.
 *
 * Encode hidden .snap dirs as a द्विगुन /, i.e.
 *   foo/.snap/bar -> foo//bar
 */
अक्षर *ceph_mdsc_build_path(काष्ठा dentry *dentry, पूर्णांक *plen, u64 *pbase,
			   पूर्णांक stop_on_nosnap)
अणु
	काष्ठा dentry *temp;
	अक्षर *path;
	पूर्णांक pos;
	अचिन्हित seq;
	u64 base;

	अगर (!dentry)
		वापस ERR_PTR(-EINVAL);

	path = __getname();
	अगर (!path)
		वापस ERR_PTR(-ENOMEM);
retry:
	pos = PATH_MAX - 1;
	path[pos] = '\0';

	seq = पढ़ो_seqbegin(&नाम_lock);
	rcu_पढ़ो_lock();
	temp = dentry;
	क्रम (;;) अणु
		काष्ठा inode *inode;

		spin_lock(&temp->d_lock);
		inode = d_inode(temp);
		अगर (inode && ceph_snap(inode) == CEPH_SNAPसूची) अणु
			करोut("build_path path+%d: %p SNAPDIR\n",
			     pos, temp);
		पूर्ण अन्यथा अगर (stop_on_nosnap && inode && dentry != temp &&
			   ceph_snap(inode) == CEPH_NOSNAP) अणु
			spin_unlock(&temp->d_lock);
			pos++; /* get rid of any prepended '/' */
			अवरोध;
		पूर्ण अन्यथा अणु
			pos -= temp->d_name.len;
			अगर (pos < 0) अणु
				spin_unlock(&temp->d_lock);
				अवरोध;
			पूर्ण
			स_नकल(path + pos, temp->d_name.name, temp->d_name.len);
		पूर्ण
		spin_unlock(&temp->d_lock);
		temp = READ_ONCE(temp->d_parent);

		/* Are we at the root? */
		अगर (IS_ROOT(temp))
			अवरोध;

		/* Are we out of buffer? */
		अगर (--pos < 0)
			अवरोध;

		path[pos] = '/';
	पूर्ण
	base = ceph_ino(d_inode(temp));
	rcu_पढ़ो_unlock();

	अगर (पढ़ो_seqretry(&नाम_lock, seq))
		जाओ retry;

	अगर (pos < 0) अणु
		/*
		 * A नाम didn't occur, but somehow we didn't end up where
		 * we thought we would. Throw a warning and try again.
		 */
		pr_warn("build_path did not end path lookup where "
			"expected, pos is %d\n", pos);
		जाओ retry;
	पूर्ण

	*pbase = base;
	*plen = PATH_MAX - 1 - pos;
	करोut("build_path on %p %d built %llx '%.*s'\n",
	     dentry, d_count(dentry), base, *plen, path + pos);
	वापस path + pos;
पूर्ण

अटल पूर्णांक build_dentry_path(काष्ठा dentry *dentry, काष्ठा inode *dir,
			     स्थिर अक्षर **ppath, पूर्णांक *ppathlen, u64 *pino,
			     bool *pमुक्तpath, bool parent_locked)
अणु
	अक्षर *path;

	rcu_पढ़ो_lock();
	अगर (!dir)
		dir = d_inode_rcu(dentry->d_parent);
	अगर (dir && parent_locked && ceph_snap(dir) == CEPH_NOSNAP) अणु
		*pino = ceph_ino(dir);
		rcu_पढ़ो_unlock();
		*ppath = dentry->d_name.name;
		*ppathlen = dentry->d_name.len;
		वापस 0;
	पूर्ण
	rcu_पढ़ो_unlock();
	path = ceph_mdsc_build_path(dentry, ppathlen, pino, 1);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);
	*ppath = path;
	*pमुक्तpath = true;
	वापस 0;
पूर्ण

अटल पूर्णांक build_inode_path(काष्ठा inode *inode,
			    स्थिर अक्षर **ppath, पूर्णांक *ppathlen, u64 *pino,
			    bool *pमुक्तpath)
अणु
	काष्ठा dentry *dentry;
	अक्षर *path;

	अगर (ceph_snap(inode) == CEPH_NOSNAP) अणु
		*pino = ceph_ino(inode);
		*ppathlen = 0;
		वापस 0;
	पूर्ण
	dentry = d_find_alias(inode);
	path = ceph_mdsc_build_path(dentry, ppathlen, pino, 1);
	dput(dentry);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);
	*ppath = path;
	*pमुक्तpath = true;
	वापस 0;
पूर्ण

/*
 * request arguments may be specअगरied via an inode *, a dentry *, or
 * an explicit ino+path.
 */
अटल पूर्णांक set_request_path_attr(काष्ठा inode *rinode, काष्ठा dentry *rdentry,
				  काष्ठा inode *rdiri, स्थिर अक्षर *rpath,
				  u64 rino, स्थिर अक्षर **ppath, पूर्णांक *pathlen,
				  u64 *ino, bool *मुक्तpath, bool parent_locked)
अणु
	पूर्णांक r = 0;

	अगर (rinode) अणु
		r = build_inode_path(rinode, ppath, pathlen, ino, मुक्तpath);
		करोut(" inode %p %llx.%llx\n", rinode, ceph_ino(rinode),
		     ceph_snap(rinode));
	पूर्ण अन्यथा अगर (rdentry) अणु
		r = build_dentry_path(rdentry, rdiri, ppath, pathlen, ino,
					मुक्तpath, parent_locked);
		करोut(" dentry %p %llx/%.*s\n", rdentry, *ino, *pathlen,
		     *ppath);
	पूर्ण अन्यथा अगर (rpath || rino) अणु
		*ino = rino;
		*ppath = rpath;
		*pathlen = rpath ? म_माप(rpath) : 0;
		करोut(" path %.*s\n", *pathlen, rpath);
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम encode_बारtamp_and_gids(व्योम **p,
				      स्थिर काष्ठा ceph_mds_request *req)
अणु
	काष्ठा ceph_बारpec ts;
	पूर्णांक i;

	ceph_encode_बारpec64(&ts, &req->r_stamp);
	ceph_encode_copy(p, &ts, माप(ts));

	/* gid_list */
	ceph_encode_32(p, req->r_cred->group_info->ngroups);
	क्रम (i = 0; i < req->r_cred->group_info->ngroups; i++)
		ceph_encode_64(p, from_kgid(&init_user_ns,
					    req->r_cred->group_info->gid[i]));
पूर्ण

/*
 * called under mdsc->mutex
 */
अटल काष्ठा ceph_msg *create_request_message(काष्ठा ceph_mds_session *session,
					       काष्ठा ceph_mds_request *req,
					       bool drop_cap_releases)
अणु
	पूर्णांक mds = session->s_mds;
	काष्ठा ceph_mds_client *mdsc = session->s_mdsc;
	काष्ठा ceph_msg *msg;
	काष्ठा ceph_mds_request_head_old *head;
	स्थिर अक्षर *path1 = शून्य;
	स्थिर अक्षर *path2 = शून्य;
	u64 ino1 = 0, ino2 = 0;
	पूर्णांक pathlen1 = 0, pathlen2 = 0;
	bool मुक्तpath1 = false, मुक्तpath2 = false;
	पूर्णांक len;
	u16 releases;
	व्योम *p, *end;
	पूर्णांक ret;
	bool legacy = !(session->s_con.peer_features & CEPH_FEATURE_FS_BTIME);

	ret = set_request_path_attr(req->r_inode, req->r_dentry,
			      req->r_parent, req->r_path1, req->r_ino1.ino,
			      &path1, &pathlen1, &ino1, &मुक्तpath1,
			      test_bit(CEPH_MDS_R_PARENT_LOCKED,
					&req->r_req_flags));
	अगर (ret < 0) अणु
		msg = ERR_PTR(ret);
		जाओ out;
	पूर्ण

	/* If r_old_dentry is set, then assume that its parent is locked */
	ret = set_request_path_attr(शून्य, req->r_old_dentry,
			      req->r_old_dentry_dir,
			      req->r_path2, req->r_ino2.ino,
			      &path2, &pathlen2, &ino2, &मुक्तpath2, true);
	अगर (ret < 0) अणु
		msg = ERR_PTR(ret);
		जाओ out_मुक्त1;
	पूर्ण

	len = legacy ? माप(*head) : माप(काष्ठा ceph_mds_request_head);
	len += pathlen1 + pathlen2 + 2*(1 + माप(u32) + माप(u64)) +
		माप(काष्ठा ceph_बारpec);
	len += माप(u32) + (माप(u64) * req->r_cred->group_info->ngroups);

	/* calculate (max) length क्रम cap releases */
	len += माप(काष्ठा ceph_mds_request_release) *
		(!!req->r_inode_drop + !!req->r_dentry_drop +
		 !!req->r_old_inode_drop + !!req->r_old_dentry_drop);

	अगर (req->r_dentry_drop)
		len += pathlen1;
	अगर (req->r_old_dentry_drop)
		len += pathlen2;

	msg = ceph_msg_new2(CEPH_MSG_CLIENT_REQUEST, len, 1, GFP_NOFS, false);
	अगर (!msg) अणु
		msg = ERR_PTR(-ENOMEM);
		जाओ out_मुक्त2;
	पूर्ण

	msg->hdr.tid = cpu_to_le64(req->r_tid);

	/*
	 * The old ceph_mds_request_head didn't contain a version field, and
	 * one was added when we moved the message version from 3->4.
	 */
	अगर (legacy) अणु
		msg->hdr.version = cpu_to_le16(3);
		head = msg->front.iov_base;
		p = msg->front.iov_base + माप(*head);
	पूर्ण अन्यथा अणु
		काष्ठा ceph_mds_request_head *new_head = msg->front.iov_base;

		msg->hdr.version = cpu_to_le16(4);
		new_head->version = cpu_to_le16(CEPH_MDS_REQUEST_HEAD_VERSION);
		head = (काष्ठा ceph_mds_request_head_old *)&new_head->oldest_client_tid;
		p = msg->front.iov_base + माप(*new_head);
	पूर्ण

	end = msg->front.iov_base + msg->front.iov_len;

	head->mdsmap_epoch = cpu_to_le32(mdsc->mdsmap->m_epoch);
	head->op = cpu_to_le32(req->r_op);
	head->caller_uid = cpu_to_le32(from_kuid(&init_user_ns,
						 req->r_cred->fsuid));
	head->caller_gid = cpu_to_le32(from_kgid(&init_user_ns,
						 req->r_cred->fsgid));
	head->ino = cpu_to_le64(req->r_deleg_ino);
	head->args = req->r_args;

	ceph_encode_filepath(&p, end, ino1, path1);
	ceph_encode_filepath(&p, end, ino2, path2);

	/* make note of release offset, in हाल we need to replay */
	req->r_request_release_offset = p - msg->front.iov_base;

	/* cap releases */
	releases = 0;
	अगर (req->r_inode_drop)
		releases += ceph_encode_inode_release(&p,
		      req->r_inode ? req->r_inode : d_inode(req->r_dentry),
		      mds, req->r_inode_drop, req->r_inode_unless,
		      req->r_op == CEPH_MDS_OP_READसूची);
	अगर (req->r_dentry_drop)
		releases += ceph_encode_dentry_release(&p, req->r_dentry,
				req->r_parent, mds, req->r_dentry_drop,
				req->r_dentry_unless);
	अगर (req->r_old_dentry_drop)
		releases += ceph_encode_dentry_release(&p, req->r_old_dentry,
				req->r_old_dentry_dir, mds,
				req->r_old_dentry_drop,
				req->r_old_dentry_unless);
	अगर (req->r_old_inode_drop)
		releases += ceph_encode_inode_release(&p,
		      d_inode(req->r_old_dentry),
		      mds, req->r_old_inode_drop, req->r_old_inode_unless, 0);

	अगर (drop_cap_releases) अणु
		releases = 0;
		p = msg->front.iov_base + req->r_request_release_offset;
	पूर्ण

	head->num_releases = cpu_to_le16(releases);

	encode_बारtamp_and_gids(&p, req);

	अगर (WARN_ON_ONCE(p > end)) अणु
		ceph_msg_put(msg);
		msg = ERR_PTR(-दुस्फल);
		जाओ out_मुक्त2;
	पूर्ण

	msg->front.iov_len = p - msg->front.iov_base;
	msg->hdr.front_len = cpu_to_le32(msg->front.iov_len);

	अगर (req->r_pagelist) अणु
		काष्ठा ceph_pagelist *pagelist = req->r_pagelist;
		ceph_msg_data_add_pagelist(msg, pagelist);
		msg->hdr.data_len = cpu_to_le32(pagelist->length);
	पूर्ण अन्यथा अणु
		msg->hdr.data_len = 0;
	पूर्ण

	msg->hdr.data_off = cpu_to_le16(0);

out_मुक्त2:
	अगर (मुक्तpath2)
		ceph_mdsc_मुक्त_path((अक्षर *)path2, pathlen2);
out_मुक्त1:
	अगर (मुक्तpath1)
		ceph_mdsc_मुक्त_path((अक्षर *)path1, pathlen1);
out:
	वापस msg;
पूर्ण

/*
 * called under mdsc->mutex अगर error, under no mutex अगर
 * success.
 */
अटल व्योम complete_request(काष्ठा ceph_mds_client *mdsc,
			     काष्ठा ceph_mds_request *req)
अणु
	req->r_end_latency = kसमय_get();

	अगर (req->r_callback)
		req->r_callback(mdsc, req);
	complete_all(&req->r_completion);
पूर्ण

अटल काष्ठा ceph_mds_request_head_old *
find_old_request_head(व्योम *p, u64 features)
अणु
	bool legacy = !(features & CEPH_FEATURE_FS_BTIME);
	काष्ठा ceph_mds_request_head *new_head;

	अगर (legacy)
		वापस (काष्ठा ceph_mds_request_head_old *)p;
	new_head = (काष्ठा ceph_mds_request_head *)p;
	वापस (काष्ठा ceph_mds_request_head_old *)&new_head->oldest_client_tid;
पूर्ण

/*
 * called under mdsc->mutex
 */
अटल पूर्णांक __prepare_send_request(काष्ठा ceph_mds_session *session,
				  काष्ठा ceph_mds_request *req,
				  bool drop_cap_releases)
अणु
	पूर्णांक mds = session->s_mds;
	काष्ठा ceph_mds_client *mdsc = session->s_mdsc;
	काष्ठा ceph_mds_request_head_old *rhead;
	काष्ठा ceph_msg *msg;
	पूर्णांक flags = 0;

	req->r_attempts++;
	अगर (req->r_inode) अणु
		काष्ठा ceph_cap *cap =
			ceph_get_cap_क्रम_mds(ceph_inode(req->r_inode), mds);

		अगर (cap)
			req->r_sent_on_mseq = cap->mseq;
		अन्यथा
			req->r_sent_on_mseq = -1;
	पूर्ण
	करोut("prepare_send_request %p tid %lld %s (attempt %d)\n", req,
	     req->r_tid, ceph_mds_op_name(req->r_op), req->r_attempts);

	अगर (test_bit(CEPH_MDS_R_GOT_UNSAFE, &req->r_req_flags)) अणु
		व्योम *p;

		/*
		 * Replay.  Do not regenerate message (and rebuild
		 * paths, etc.); just use the original message.
		 * Rebuilding paths will अवरोध क्रम नामs because
		 * d_move mangles the src name.
		 */
		msg = req->r_request;
		rhead = find_old_request_head(msg->front.iov_base,
					      session->s_con.peer_features);

		flags = le32_to_cpu(rhead->flags);
		flags |= CEPH_MDS_FLAG_REPLAY;
		rhead->flags = cpu_to_le32(flags);

		अगर (req->r_target_inode)
			rhead->ino = cpu_to_le64(ceph_ino(req->r_target_inode));

		rhead->num_retry = req->r_attempts - 1;

		/* हटाओ cap/dentry releases from message */
		rhead->num_releases = 0;

		p = msg->front.iov_base + req->r_request_release_offset;
		encode_बारtamp_and_gids(&p, req);

		msg->front.iov_len = p - msg->front.iov_base;
		msg->hdr.front_len = cpu_to_le32(msg->front.iov_len);
		वापस 0;
	पूर्ण

	अगर (req->r_request) अणु
		ceph_msg_put(req->r_request);
		req->r_request = शून्य;
	पूर्ण
	msg = create_request_message(session, req, drop_cap_releases);
	अगर (IS_ERR(msg)) अणु
		req->r_err = PTR_ERR(msg);
		वापस PTR_ERR(msg);
	पूर्ण
	req->r_request = msg;

	rhead = find_old_request_head(msg->front.iov_base,
				      session->s_con.peer_features);
	rhead->oldest_client_tid = cpu_to_le64(__get_oldest_tid(mdsc));
	अगर (test_bit(CEPH_MDS_R_GOT_UNSAFE, &req->r_req_flags))
		flags |= CEPH_MDS_FLAG_REPLAY;
	अगर (test_bit(CEPH_MDS_R_ASYNC, &req->r_req_flags))
		flags |= CEPH_MDS_FLAG_ASYNC;
	अगर (req->r_parent)
		flags |= CEPH_MDS_FLAG_WANT_DENTRY;
	rhead->flags = cpu_to_le32(flags);
	rhead->num_fwd = req->r_num_fwd;
	rhead->num_retry = req->r_attempts - 1;

	करोut(" r_parent = %p\n", req->r_parent);
	वापस 0;
पूर्ण

/*
 * called under mdsc->mutex
 */
अटल पूर्णांक __send_request(काष्ठा ceph_mds_session *session,
			  काष्ठा ceph_mds_request *req,
			  bool drop_cap_releases)
अणु
	पूर्णांक err;

	err = __prepare_send_request(session, req, drop_cap_releases);
	अगर (!err) अणु
		ceph_msg_get(req->r_request);
		ceph_con_send(&session->s_con, req->r_request);
	पूर्ण

	वापस err;
पूर्ण

/*
 * send request, or put it on the appropriate रुको list.
 */
अटल व्योम __करो_request(काष्ठा ceph_mds_client *mdsc,
			काष्ठा ceph_mds_request *req)
अणु
	काष्ठा ceph_mds_session *session = शून्य;
	पूर्णांक mds = -1;
	पूर्णांक err = 0;
	bool अक्रमom;

	अगर (req->r_err || test_bit(CEPH_MDS_R_GOT_RESULT, &req->r_req_flags)) अणु
		अगर (test_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags))
			__unरेजिस्टर_request(mdsc, req);
		वापस;
	पूर्ण

	अगर (req->r_समयout &&
	    समय_after_eq(jअगरfies, req->r_started + req->r_समयout)) अणु
		करोut("do_request timed out\n");
		err = -ETIMEDOUT;
		जाओ finish;
	पूर्ण
	अगर (READ_ONCE(mdsc->fsc->mount_state) == CEPH_MOUNT_SHUTDOWN) अणु
		करोut("do_request forced umount\n");
		err = -EIO;
		जाओ finish;
	पूर्ण
	अगर (READ_ONCE(mdsc->fsc->mount_state) == CEPH_MOUNT_MOUNTING) अणु
		अगर (mdsc->mdsmap_err) अणु
			err = mdsc->mdsmap_err;
			करोut("do_request mdsmap err %d\n", err);
			जाओ finish;
		पूर्ण
		अगर (mdsc->mdsmap->m_epoch == 0) अणु
			करोut("do_request no mdsmap, waiting for map\n");
			list_add(&req->r_रुको, &mdsc->रुकोing_क्रम_map);
			वापस;
		पूर्ण
		अगर (!(mdsc->fsc->mount_options->flags &
		      CEPH_MOUNT_OPT_MOUNTWAIT) &&
		    !ceph_mdsmap_is_cluster_available(mdsc->mdsmap)) अणु
			err = -EHOSTUNREACH;
			जाओ finish;
		पूर्ण
	पूर्ण

	put_request_session(req);

	mds = __choose_mds(mdsc, req, &अक्रमom);
	अगर (mds < 0 ||
	    ceph_mdsmap_get_state(mdsc->mdsmap, mds) < CEPH_MDS_STATE_ACTIVE) अणु
		अगर (test_bit(CEPH_MDS_R_ASYNC, &req->r_req_flags)) अणु
			err = -EJUKEBOX;
			जाओ finish;
		पूर्ण
		करोut("do_request no mds or not active, waiting for map\n");
		list_add(&req->r_रुको, &mdsc->रुकोing_क्रम_map);
		वापस;
	पूर्ण

	/* get, खोलो session */
	session = __ceph_lookup_mds_session(mdsc, mds);
	अगर (!session) अणु
		session = रेजिस्टर_session(mdsc, mds);
		अगर (IS_ERR(session)) अणु
			err = PTR_ERR(session);
			जाओ finish;
		पूर्ण
	पूर्ण
	req->r_session = ceph_get_mds_session(session);

	करोut("do_request mds%d session %p state %s\n", mds, session,
	     ceph_session_state_name(session->s_state));
	अगर (session->s_state != CEPH_MDS_SESSION_OPEN &&
	    session->s_state != CEPH_MDS_SESSION_HUNG) अणु
		/*
		 * We cannot queue async requests since the caps and delegated
		 * inodes are bound to the session. Just वापस -EJUKEBOX and
		 * let the caller retry a sync request in that हाल.
		 */
		अगर (test_bit(CEPH_MDS_R_ASYNC, &req->r_req_flags)) अणु
			err = -EJUKEBOX;
			जाओ out_session;
		पूर्ण

		/*
		 * If the session has been REJECTED, then वापस a hard error,
		 * unless it's a CLEANRECOVER mount, in which case we'll queue
		 * it to the mdsc queue.
		 */
		अगर (session->s_state == CEPH_MDS_SESSION_REJECTED) अणु
			अगर (ceph_test_mount_opt(mdsc->fsc, CLEANRECOVER))
				list_add(&req->r_रुको, &mdsc->रुकोing_क्रम_map);
			अन्यथा
				err = -EACCES;
			जाओ out_session;
		पूर्ण

		अगर (session->s_state == CEPH_MDS_SESSION_NEW ||
		    session->s_state == CEPH_MDS_SESSION_CLOSING) अणु
			err = __खोलो_session(mdsc, session);
			अगर (err)
				जाओ out_session;
			/* retry the same mds later */
			अगर (अक्रमom)
				req->r_resend_mds = mds;
		पूर्ण
		list_add(&req->r_रुको, &session->s_रुकोing);
		जाओ out_session;
	पूर्ण

	/* send request */
	req->r_resend_mds = -1;   /* क्रमget any previous mds hपूर्णांक */

	अगर (req->r_request_started == 0)   /* note request start समय */
		req->r_request_started = jअगरfies;

	err = __send_request(session, req, false);

out_session:
	ceph_put_mds_session(session);
finish:
	अगर (err) अणु
		करोut("__do_request early error %d\n", err);
		req->r_err = err;
		complete_request(mdsc, req);
		__unरेजिस्टर_request(mdsc, req);
	पूर्ण
	वापस;
पूर्ण

/*
 * called under mdsc->mutex
 */
अटल व्योम __wake_requests(काष्ठा ceph_mds_client *mdsc,
			    काष्ठा list_head *head)
अणु
	काष्ठा ceph_mds_request *req;
	LIST_HEAD(पंचांगp_list);

	list_splice_init(head, &पंचांगp_list);

	जबतक (!list_empty(&पंचांगp_list)) अणु
		req = list_entry(पंचांगp_list.next,
				 काष्ठा ceph_mds_request, r_रुको);
		list_del_init(&req->r_रुको);
		करोut(" wake request %p tid %llu\n", req, req->r_tid);
		__करो_request(mdsc, req);
	पूर्ण
पूर्ण

/*
 * Wake up thपढ़ोs with requests pending क्रम @mds, so that they can
 * resubmit their requests to a possibly dअगरferent mds.
 */
अटल व्योम kick_requests(काष्ठा ceph_mds_client *mdsc, पूर्णांक mds)
अणु
	काष्ठा ceph_mds_request *req;
	काष्ठा rb_node *p = rb_first(&mdsc->request_tree);

	करोut("kick_requests mds%d\n", mds);
	जबतक (p) अणु
		req = rb_entry(p, काष्ठा ceph_mds_request, r_node);
		p = rb_next(p);
		अगर (test_bit(CEPH_MDS_R_GOT_UNSAFE, &req->r_req_flags))
			जारी;
		अगर (req->r_attempts > 0)
			जारी; /* only new requests */
		अगर (req->r_session &&
		    req->r_session->s_mds == mds) अणु
			करोut(" kicking tid %llu\n", req->r_tid);
			list_del_init(&req->r_रुको);
			__करो_request(mdsc, req);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक ceph_mdsc_submit_request(काष्ठा ceph_mds_client *mdsc, काष्ठा inode *dir,
			      काष्ठा ceph_mds_request *req)
अणु
	पूर्णांक err = 0;

	/* take CAP_PIN refs क्रम r_inode, r_parent, r_old_dentry */
	अगर (req->r_inode)
		ceph_get_cap_refs(ceph_inode(req->r_inode), CEPH_CAP_PIN);
	अगर (req->r_parent) अणु
		काष्ठा ceph_inode_info *ci = ceph_inode(req->r_parent);
		पूर्णांक भ_शेषe = (req->r_op & CEPH_MDS_OP_WRITE) ?
			    CEPH_खाता_MODE_WR : CEPH_खाता_MODE_RD;
		spin_lock(&ci->i_ceph_lock);
		ceph_take_cap_refs(ci, CEPH_CAP_PIN, false);
		__ceph_touch_भ_शेषe(ci, mdsc, भ_शेषe);
		spin_unlock(&ci->i_ceph_lock);
		ihold(req->r_parent);
	पूर्ण
	अगर (req->r_old_dentry_dir)
		ceph_get_cap_refs(ceph_inode(req->r_old_dentry_dir),
				  CEPH_CAP_PIN);

	अगर (req->r_inode) अणु
		err = ceph_रुको_on_async_create(req->r_inode);
		अगर (err) अणु
			करोut("%s: wait for async create returned: %d\n",
			     __func__, err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (!err && req->r_old_inode) अणु
		err = ceph_रुको_on_async_create(req->r_old_inode);
		अगर (err) अणु
			करोut("%s: wait for async create returned: %d\n",
			     __func__, err);
			वापस err;
		पूर्ण
	पूर्ण

	करोut("submit_request on %p for inode %p\n", req, dir);
	mutex_lock(&mdsc->mutex);
	__रेजिस्टर_request(mdsc, req, dir);
	__करो_request(mdsc, req);
	err = req->r_err;
	mutex_unlock(&mdsc->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ceph_mdsc_रुको_request(काष्ठा ceph_mds_client *mdsc,
				  काष्ठा ceph_mds_request *req)
अणु
	पूर्णांक err;

	/* रुको */
	करोut("do_request waiting\n");
	अगर (!req->r_समयout && req->r_रुको_क्रम_completion) अणु
		err = req->r_रुको_क्रम_completion(mdsc, req);
	पूर्ण अन्यथा अणु
		दीर्घ समयleft = रुको_क्रम_completion_समाप्तable_समयout(
					&req->r_completion,
					ceph_समयout_jअगरfies(req->r_समयout));
		अगर (समयleft > 0)
			err = 0;
		अन्यथा अगर (!समयleft)
			err = -ETIMEDOUT;  /* समयd out */
		अन्यथा
			err = समयleft;  /* समाप्तed */
	पूर्ण
	करोut("do_request waited, got %d\n", err);
	mutex_lock(&mdsc->mutex);

	/* only पात अगर we didn't race with a real reply */
	अगर (test_bit(CEPH_MDS_R_GOT_RESULT, &req->r_req_flags)) अणु
		err = le32_to_cpu(req->r_reply_info.head->result);
	पूर्ण अन्यथा अगर (err < 0) अणु
		करोut("aborted request %lld with %d\n", req->r_tid, err);

		/*
		 * ensure we aren't running concurrently with
		 * ceph_fill_trace or ceph_सूची_पढ़ो_prepopulate, which
		 * rely on locks (dir mutex) held by our caller.
		 */
		mutex_lock(&req->r_fill_mutex);
		req->r_err = err;
		set_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags);
		mutex_unlock(&req->r_fill_mutex);

		अगर (req->r_parent &&
		    (req->r_op & CEPH_MDS_OP_WRITE))
			ceph_invalidate_dir_request(req);
	पूर्ण अन्यथा अणु
		err = req->r_err;
	पूर्ण

	mutex_unlock(&mdsc->mutex);
	वापस err;
पूर्ण

/*
 * Synchrously perक्रमm an mds request.  Take care of all of the
 * session setup, क्रमwarding, retry details.
 */
पूर्णांक ceph_mdsc_करो_request(काष्ठा ceph_mds_client *mdsc,
			 काष्ठा inode *dir,
			 काष्ठा ceph_mds_request *req)
अणु
	पूर्णांक err;

	करोut("do_request on %p\n", req);

	/* issue */
	err = ceph_mdsc_submit_request(mdsc, dir, req);
	अगर (!err)
		err = ceph_mdsc_रुको_request(mdsc, req);
	करोut("do_request %p done, result %d\n", req, err);
	वापस err;
पूर्ण

/*
 * Invalidate dir's completeness, dentry lease state on an पातed MDS
 * namespace request.
 */
व्योम ceph_invalidate_dir_request(काष्ठा ceph_mds_request *req)
अणु
	काष्ठा inode *dir = req->r_parent;
	काष्ठा inode *old_dir = req->r_old_dentry_dir;

	करोut("invalidate_dir_request %p %p (complete, lease(s))\n", dir, old_dir);

	ceph_dir_clear_complete(dir);
	अगर (old_dir)
		ceph_dir_clear_complete(old_dir);
	अगर (req->r_dentry)
		ceph_invalidate_dentry_lease(req->r_dentry);
	अगर (req->r_old_dentry)
		ceph_invalidate_dentry_lease(req->r_old_dentry);
पूर्ण

/*
 * Handle mds reply.
 *
 * We take the session mutex and parse and process the reply immediately.
 * This preserves the logical ordering of replies, capabilities, etc., sent
 * by the MDS as they are applied to our local cache.
 */
अटल व्योम handle_reply(काष्ठा ceph_mds_session *session, काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_mds_client *mdsc = session->s_mdsc;
	काष्ठा ceph_mds_request *req;
	काष्ठा ceph_mds_reply_head *head = msg->front.iov_base;
	काष्ठा ceph_mds_reply_info_parsed *rinfo;  /* parsed reply info */
	काष्ठा ceph_snap_realm *realm;
	u64 tid;
	पूर्णांक err, result;
	पूर्णांक mds = session->s_mds;

	अगर (msg->front.iov_len < माप(*head)) अणु
		pr_err("mdsc_handle_reply got corrupt (short) reply\n");
		ceph_msg_dump(msg);
		वापस;
	पूर्ण

	/* get request, session */
	tid = le64_to_cpu(msg->hdr.tid);
	mutex_lock(&mdsc->mutex);
	req = lookup_get_request(mdsc, tid);
	अगर (!req) अणु
		करोut("handle_reply on unknown tid %llu\n", tid);
		mutex_unlock(&mdsc->mutex);
		वापस;
	पूर्ण
	करोut("handle_reply %p\n", req);

	/* correct session? */
	अगर (req->r_session != session) अणु
		pr_err("mdsc_handle_reply got %llu on session mds%d"
		       " not mds%d\n", tid, session->s_mds,
		       req->r_session ? req->r_session->s_mds : -1);
		mutex_unlock(&mdsc->mutex);
		जाओ out;
	पूर्ण

	/* dup? */
	अगर ((test_bit(CEPH_MDS_R_GOT_UNSAFE, &req->r_req_flags) && !head->safe) ||
	    (test_bit(CEPH_MDS_R_GOT_SAFE, &req->r_req_flags) && head->safe)) अणु
		pr_warn("got a dup %s reply on %llu from mds%d\n",
			   head->safe ? "safe" : "unsafe", tid, mds);
		mutex_unlock(&mdsc->mutex);
		जाओ out;
	पूर्ण
	अगर (test_bit(CEPH_MDS_R_GOT_SAFE, &req->r_req_flags)) अणु
		pr_warn("got unsafe after safe on %llu from mds%d\n",
			   tid, mds);
		mutex_unlock(&mdsc->mutex);
		जाओ out;
	पूर्ण

	result = le32_to_cpu(head->result);

	/*
	 * Handle an ESTALE
	 * अगर we're not talking to the authority, send to them
	 * अगर the authority has changed जबतक we weren't looking,
	 * send to new authority
	 * Otherwise we just have to वापस an ESTALE
	 */
	अगर (result == -ESTALE) अणु
		करोut("got ESTALE on request %llu\n", req->r_tid);
		req->r_resend_mds = -1;
		अगर (req->r_direct_mode != USE_AUTH_MDS) अणु
			करोut("not using auth, setting for that now\n");
			req->r_direct_mode = USE_AUTH_MDS;
			__करो_request(mdsc, req);
			mutex_unlock(&mdsc->mutex);
			जाओ out;
		पूर्ण अन्यथा  अणु
			पूर्णांक mds = __choose_mds(mdsc, req, शून्य);
			अगर (mds >= 0 && mds != req->r_session->s_mds) अणु
				करोut("but auth changed, so resending\n");
				__करो_request(mdsc, req);
				mutex_unlock(&mdsc->mutex);
				जाओ out;
			पूर्ण
		पूर्ण
		करोut("have to return ESTALE on request %llu\n", req->r_tid);
	पूर्ण


	अगर (head->safe) अणु
		set_bit(CEPH_MDS_R_GOT_SAFE, &req->r_req_flags);
		__unरेजिस्टर_request(mdsc, req);

		/* last request during umount? */
		अगर (mdsc->stopping && !__get_oldest_req(mdsc))
			complete_all(&mdsc->safe_umount_रुकोers);

		अगर (test_bit(CEPH_MDS_R_GOT_UNSAFE, &req->r_req_flags)) अणु
			/*
			 * We alपढ़ोy handled the unsafe response, now करो the
			 * cleanup.  No need to examine the response; the MDS
			 * करोesn't include any result info in the safe
			 * response.  And even अगर it did, there is nothing
			 * useful we could करो with a revised वापस value.
			 */
			करोut("got safe reply %llu, mds%d\n", tid, mds);

			mutex_unlock(&mdsc->mutex);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		set_bit(CEPH_MDS_R_GOT_UNSAFE, &req->r_req_flags);
		list_add_tail(&req->r_unsafe_item, &req->r_session->s_unsafe);
	पूर्ण

	करोut("handle_reply tid %lld result %d\n", tid, result);
	rinfo = &req->r_reply_info;
	अगर (test_bit(CEPHFS_FEATURE_REPLY_ENCODING, &session->s_features))
		err = parse_reply_info(session, msg, rinfo, (u64)-1);
	अन्यथा
		err = parse_reply_info(session, msg, rinfo, session->s_con.peer_features);
	mutex_unlock(&mdsc->mutex);

	/* Must find target inode outside of mutexes to aव्योम deadlocks */
	अगर ((err >= 0) && rinfo->head->is_target) अणु
		काष्ठा inode *in;
		काष्ठा ceph_vino tvino = अणु
			.ino  = le64_to_cpu(rinfo->targeti.in->ino),
			.snap = le64_to_cpu(rinfo->targeti.in->snapid)
		पूर्ण;

		in = ceph_get_inode(mdsc->fsc->sb, tvino);
		अगर (IS_ERR(in)) अणु
			err = PTR_ERR(in);
			mutex_lock(&session->s_mutex);
			जाओ out_err;
		पूर्ण
		req->r_target_inode = in;
	पूर्ण

	mutex_lock(&session->s_mutex);
	अगर (err < 0) अणु
		pr_err("mdsc_handle_reply got corrupt reply mds%d(tid:%lld)\n", mds, tid);
		ceph_msg_dump(msg);
		जाओ out_err;
	पूर्ण

	/* snap trace */
	realm = शून्य;
	अगर (rinfo->snapblob_len) अणु
		करोwn_ग_लिखो(&mdsc->snap_rwsem);
		ceph_update_snap_trace(mdsc, rinfo->snapblob,
				rinfo->snapblob + rinfo->snapblob_len,
				le32_to_cpu(head->op) == CEPH_MDS_OP_RMSNAP,
				&realm);
		करोwngrade_ग_लिखो(&mdsc->snap_rwsem);
	पूर्ण अन्यथा अणु
		करोwn_पढ़ो(&mdsc->snap_rwsem);
	पूर्ण

	/* insert trace पूर्णांकo our cache */
	mutex_lock(&req->r_fill_mutex);
	current->journal_info = req;
	err = ceph_fill_trace(mdsc->fsc->sb, req);
	अगर (err == 0) अणु
		अगर (result == 0 && (req->r_op == CEPH_MDS_OP_READसूची ||
				    req->r_op == CEPH_MDS_OP_LSSNAP))
			ceph_सूची_पढ़ो_prepopulate(req, req->r_session);
	पूर्ण
	current->journal_info = शून्य;
	mutex_unlock(&req->r_fill_mutex);

	up_पढ़ो(&mdsc->snap_rwsem);
	अगर (realm)
		ceph_put_snap_realm(mdsc, realm);

	अगर (err == 0) अणु
		अगर (req->r_target_inode &&
		    test_bit(CEPH_MDS_R_GOT_UNSAFE, &req->r_req_flags)) अणु
			काष्ठा ceph_inode_info *ci =
				ceph_inode(req->r_target_inode);
			spin_lock(&ci->i_unsafe_lock);
			list_add_tail(&req->r_unsafe_target_item,
				      &ci->i_unsafe_iops);
			spin_unlock(&ci->i_unsafe_lock);
		पूर्ण

		ceph_unreserve_caps(mdsc, &req->r_caps_reservation);
	पूर्ण
out_err:
	mutex_lock(&mdsc->mutex);
	अगर (!test_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags)) अणु
		अगर (err) अणु
			req->r_err = err;
		पूर्ण अन्यथा अणु
			req->r_reply =  ceph_msg_get(msg);
			set_bit(CEPH_MDS_R_GOT_RESULT, &req->r_req_flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		करोut("reply arrived after request %lld was aborted\n", tid);
	पूर्ण
	mutex_unlock(&mdsc->mutex);

	mutex_unlock(&session->s_mutex);

	/* kick calling process */
	complete_request(mdsc, req);

	ceph_update_metadata_metrics(&mdsc->metric, req->r_start_latency,
				     req->r_end_latency, err);
out:
	ceph_mdsc_put_request(req);
	वापस;
पूर्ण



/*
 * handle mds notअगरication that our request has been क्रमwarded.
 */
अटल व्योम handle_क्रमward(काष्ठा ceph_mds_client *mdsc,
			   काष्ठा ceph_mds_session *session,
			   काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_mds_request *req;
	u64 tid = le64_to_cpu(msg->hdr.tid);
	u32 next_mds;
	u32 fwd_seq;
	पूर्णांक err = -EINVAL;
	व्योम *p = msg->front.iov_base;
	व्योम *end = p + msg->front.iov_len;

	ceph_decode_need(&p, end, 2*माप(u32), bad);
	next_mds = ceph_decode_32(&p);
	fwd_seq = ceph_decode_32(&p);

	mutex_lock(&mdsc->mutex);
	req = lookup_get_request(mdsc, tid);
	अगर (!req) अणु
		करोut("forward tid %llu to mds%d - req dne\n", tid, next_mds);
		जाओ out;  /* dup reply? */
	पूर्ण

	अगर (test_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags)) अणु
		करोut("forward tid %llu aborted, unregistering\n", tid);
		__unरेजिस्टर_request(mdsc, req);
	पूर्ण अन्यथा अगर (fwd_seq <= req->r_num_fwd) अणु
		करोut("forward tid %llu to mds%d - old seq %d <= %d\n",
		     tid, next_mds, req->r_num_fwd, fwd_seq);
	पूर्ण अन्यथा अणु
		/* resend. क्रमward race not possible; mds would drop */
		करोut("forward tid %llu to mds%d (we resend)\n", tid, next_mds);
		BUG_ON(req->r_err);
		BUG_ON(test_bit(CEPH_MDS_R_GOT_RESULT, &req->r_req_flags));
		req->r_attempts = 0;
		req->r_num_fwd = fwd_seq;
		req->r_resend_mds = next_mds;
		put_request_session(req);
		__करो_request(mdsc, req);
	पूर्ण
	ceph_mdsc_put_request(req);
out:
	mutex_unlock(&mdsc->mutex);
	वापस;

bad:
	pr_err("mdsc_handle_forward decode error err=%d\n", err);
पूर्ण

अटल पूर्णांक __decode_session_metadata(व्योम **p, व्योम *end,
				     bool *blocklisted)
अणु
	/* map<string,string> */
	u32 n;
	bool err_str;
	ceph_decode_32_safe(p, end, n, bad);
	जबतक (n-- > 0) अणु
		u32 len;
		ceph_decode_32_safe(p, end, len, bad);
		ceph_decode_need(p, end, len, bad);
		err_str = !म_भेदन(*p, "error_string", len);
		*p += len;
		ceph_decode_32_safe(p, end, len, bad);
		ceph_decode_need(p, end, len, bad);
		/*
		 * Match "blocklisted (blacklisted)" from newer MDSes,
		 * or "blacklisted" from older MDSes.
		 */
		अगर (err_str && strnstr(*p, "blacklisted", len))
			*blocklisted = true;
		*p += len;
	पूर्ण
	वापस 0;
bad:
	वापस -1;
पूर्ण

/*
 * handle a mds session control message
 */
अटल व्योम handle_session(काष्ठा ceph_mds_session *session,
			   काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_mds_client *mdsc = session->s_mdsc;
	पूर्णांक mds = session->s_mds;
	पूर्णांक msg_version = le16_to_cpu(msg->hdr.version);
	व्योम *p = msg->front.iov_base;
	व्योम *end = p + msg->front.iov_len;
	काष्ठा ceph_mds_session_head *h;
	u32 op;
	u64 seq, features = 0;
	पूर्णांक wake = 0;
	bool blocklisted = false;

	/* decode */
	ceph_decode_need(&p, end, माप(*h), bad);
	h = p;
	p += माप(*h);

	op = le32_to_cpu(h->op);
	seq = le64_to_cpu(h->seq);

	अगर (msg_version >= 3) अणु
		u32 len;
		/* version >= 2, metadata */
		अगर (__decode_session_metadata(&p, end, &blocklisted) < 0)
			जाओ bad;
		/* version >= 3, feature bits */
		ceph_decode_32_safe(&p, end, len, bad);
		अगर (len) अणु
			ceph_decode_64_safe(&p, end, features, bad);
			p += len - माप(features);
		पूर्ण
	पूर्ण

	mutex_lock(&mdsc->mutex);
	अगर (op == CEPH_SESSION_CLOSE) अणु
		ceph_get_mds_session(session);
		__unरेजिस्टर_session(mdsc, session);
	पूर्ण
	/* FIXME: this ttl calculation is generous */
	session->s_ttl = jअगरfies + HZ*mdsc->mdsmap->m_session_स्वतःबंद;
	mutex_unlock(&mdsc->mutex);

	mutex_lock(&session->s_mutex);

	करोut("handle_session mds%d %s %p state %s seq %llu\n",
	     mds, ceph_session_op_name(op), session,
	     ceph_session_state_name(session->s_state), seq);

	अगर (session->s_state == CEPH_MDS_SESSION_HUNG) अणु
		session->s_state = CEPH_MDS_SESSION_OPEN;
		pr_info("mds%d came back\n", session->s_mds);
	पूर्ण

	चयन (op) अणु
	हाल CEPH_SESSION_OPEN:
		अगर (session->s_state == CEPH_MDS_SESSION_RECONNECTING)
			pr_info("mds%d reconnect success\n", session->s_mds);
		session->s_state = CEPH_MDS_SESSION_OPEN;
		session->s_features = features;
		renewed_caps(mdsc, session, 0);
		अगर (test_bit(CEPHFS_FEATURE_METRIC_COLLECT, &session->s_features))
			metric_schedule_delayed(&mdsc->metric);
		wake = 1;
		अगर (mdsc->stopping)
			__बंद_session(mdsc, session);
		अवरोध;

	हाल CEPH_SESSION_RENEWCAPS:
		अगर (session->s_renew_seq == seq)
			renewed_caps(mdsc, session, 1);
		अवरोध;

	हाल CEPH_SESSION_CLOSE:
		अगर (session->s_state == CEPH_MDS_SESSION_RECONNECTING)
			pr_info("mds%d reconnect denied\n", session->s_mds);
		session->s_state = CEPH_MDS_SESSION_CLOSED;
		cleanup_session_requests(mdsc, session);
		हटाओ_session_caps(session);
		wake = 2; /* क्रम good measure */
		wake_up_all(&mdsc->session_बंद_wq);
		अवरोध;

	हाल CEPH_SESSION_STALE:
		pr_info("mds%d caps went stale, renewing\n",
			session->s_mds);
		spin_lock(&session->s_gen_ttl_lock);
		session->s_cap_gen++;
		session->s_cap_ttl = jअगरfies - 1;
		spin_unlock(&session->s_gen_ttl_lock);
		send_renew_caps(mdsc, session);
		अवरोध;

	हाल CEPH_SESSION_RECALL_STATE:
		ceph_trim_caps(mdsc, session, le32_to_cpu(h->max_caps));
		अवरोध;

	हाल CEPH_SESSION_FLUSHMSG:
		send_flushmsg_ack(mdsc, session, seq);
		अवरोध;

	हाल CEPH_SESSION_FORCE_RO:
		करोut("force_session_readonly %p\n", session);
		spin_lock(&session->s_cap_lock);
		session->s_पढ़ोonly = true;
		spin_unlock(&session->s_cap_lock);
		wake_up_session_caps(session, FORCE_RO);
		अवरोध;

	हाल CEPH_SESSION_REJECT:
		WARN_ON(session->s_state != CEPH_MDS_SESSION_OPENING);
		pr_info("mds%d rejected session\n", session->s_mds);
		session->s_state = CEPH_MDS_SESSION_REJECTED;
		cleanup_session_requests(mdsc, session);
		हटाओ_session_caps(session);
		अगर (blocklisted)
			mdsc->fsc->blocklisted = true;
		wake = 2; /* क्रम good measure */
		अवरोध;

	शेष:
		pr_err("mdsc_handle_session bad op %d mds%d\n", op, mds);
		WARN_ON(1);
	पूर्ण

	mutex_unlock(&session->s_mutex);
	अगर (wake) अणु
		mutex_lock(&mdsc->mutex);
		__wake_requests(mdsc, &session->s_रुकोing);
		अगर (wake == 2)
			kick_requests(mdsc, mds);
		mutex_unlock(&mdsc->mutex);
	पूर्ण
	अगर (op == CEPH_SESSION_CLOSE)
		ceph_put_mds_session(session);
	वापस;

bad:
	pr_err("mdsc_handle_session corrupt message mds%d len %d\n", mds,
	       (पूर्णांक)msg->front.iov_len);
	ceph_msg_dump(msg);
	वापस;
पूर्ण

व्योम ceph_mdsc_release_dir_caps(काष्ठा ceph_mds_request *req)
अणु
	पूर्णांक dcaps;

	dcaps = xchg(&req->r_dir_caps, 0);
	अगर (dcaps) अणु
		करोut("releasing r_dir_caps=%s\n", ceph_cap_string(dcaps));
		ceph_put_cap_refs(ceph_inode(req->r_parent), dcaps);
	पूर्ण
पूर्ण

व्योम ceph_mdsc_release_dir_caps_no_check(काष्ठा ceph_mds_request *req)
अणु
	पूर्णांक dcaps;

	dcaps = xchg(&req->r_dir_caps, 0);
	अगर (dcaps) अणु
		करोut("releasing r_dir_caps=%s\n", ceph_cap_string(dcaps));
		ceph_put_cap_refs_no_check_caps(ceph_inode(req->r_parent),
						dcaps);
	पूर्ण
पूर्ण

/*
 * called under session->mutex.
 */
अटल व्योम replay_unsafe_requests(काष्ठा ceph_mds_client *mdsc,
				   काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_mds_request *req, *nreq;
	काष्ठा rb_node *p;

	करोut("replay_unsafe_requests mds%d\n", session->s_mds);

	mutex_lock(&mdsc->mutex);
	list_क्रम_each_entry_safe(req, nreq, &session->s_unsafe, r_unsafe_item)
		__send_request(session, req, true);

	/*
	 * also re-send old requests when MDS enters reconnect stage. So that MDS
	 * can process completed request in clientreplay stage.
	 */
	p = rb_first(&mdsc->request_tree);
	जबतक (p) अणु
		req = rb_entry(p, काष्ठा ceph_mds_request, r_node);
		p = rb_next(p);
		अगर (test_bit(CEPH_MDS_R_GOT_UNSAFE, &req->r_req_flags))
			जारी;
		अगर (req->r_attempts == 0)
			जारी; /* only old requests */
		अगर (!req->r_session)
			जारी;
		अगर (req->r_session->s_mds != session->s_mds)
			जारी;

		ceph_mdsc_release_dir_caps_no_check(req);

		__send_request(session, req, true);
	पूर्ण
	mutex_unlock(&mdsc->mutex);
पूर्ण

अटल पूर्णांक send_reconnect_partial(काष्ठा ceph_reconnect_state *recon_state)
अणु
	काष्ठा ceph_msg *reply;
	काष्ठा ceph_pagelist *_pagelist;
	काष्ठा page *page;
	__le32 *addr;
	पूर्णांक err = -ENOMEM;

	अगर (!recon_state->allow_multi)
		वापस -ENOSPC;

	/* can't handle message that contains both caps and realm */
	BUG_ON(!recon_state->nr_caps == !recon_state->nr_realms);

	/* pre-allocate new pagelist */
	_pagelist = ceph_pagelist_alloc(GFP_NOFS);
	अगर (!_pagelist)
		वापस -ENOMEM;

	reply = ceph_msg_new2(CEPH_MSG_CLIENT_RECONNECT, 0, 1, GFP_NOFS, false);
	अगर (!reply)
		जाओ fail_msg;

	/* placeholder क्रम nr_caps */
	err = ceph_pagelist_encode_32(_pagelist, 0);
	अगर (err < 0)
		जाओ fail;

	अगर (recon_state->nr_caps) अणु
		/* currently encoding caps */
		err = ceph_pagelist_encode_32(recon_state->pagelist, 0);
		अगर (err)
			जाओ fail;
	पूर्ण अन्यथा अणु
		/* placeholder क्रम nr_realms (currently encoding relams) */
		err = ceph_pagelist_encode_32(_pagelist, 0);
		अगर (err < 0)
			जाओ fail;
	पूर्ण

	err = ceph_pagelist_encode_8(recon_state->pagelist, 1);
	अगर (err)
		जाओ fail;

	page = list_first_entry(&recon_state->pagelist->head, काष्ठा page, lru);
	addr = kmap_atomic(page);
	अगर (recon_state->nr_caps) अणु
		/* currently encoding caps */
		*addr = cpu_to_le32(recon_state->nr_caps);
	पूर्ण अन्यथा अणु
		/* currently encoding relams */
		*(addr + 1) = cpu_to_le32(recon_state->nr_realms);
	पूर्ण
	kunmap_atomic(addr);

	reply->hdr.version = cpu_to_le16(5);
	reply->hdr.compat_version = cpu_to_le16(4);

	reply->hdr.data_len = cpu_to_le32(recon_state->pagelist->length);
	ceph_msg_data_add_pagelist(reply, recon_state->pagelist);

	ceph_con_send(&recon_state->session->s_con, reply);
	ceph_pagelist_release(recon_state->pagelist);

	recon_state->pagelist = _pagelist;
	recon_state->nr_caps = 0;
	recon_state->nr_realms = 0;
	recon_state->msg_version = 5;
	वापस 0;
fail:
	ceph_msg_put(reply);
fail_msg:
	ceph_pagelist_release(_pagelist);
	वापस err;
पूर्ण

अटल काष्ठा dentry* d_find_primary(काष्ठा inode *inode)
अणु
	काष्ठा dentry *alias, *dn = शून्य;

	अगर (hlist_empty(&inode->i_dentry))
		वापस शून्य;

	spin_lock(&inode->i_lock);
	अगर (hlist_empty(&inode->i_dentry))
		जाओ out_unlock;

	अगर (S_ISसूची(inode->i_mode)) अणु
		alias = hlist_entry(inode->i_dentry.first, काष्ठा dentry, d_u.d_alias);
		अगर (!IS_ROOT(alias))
			dn = dget(alias);
		जाओ out_unlock;
	पूर्ण

	hlist_क्रम_each_entry(alias, &inode->i_dentry, d_u.d_alias) अणु
		spin_lock(&alias->d_lock);
		अगर (!d_unhashed(alias) &&
		    (ceph_dentry(alias)->flags & CEPH_DENTRY_PRIMARY_LINK)) अणु
			dn = dget_dlock(alias);
		पूर्ण
		spin_unlock(&alias->d_lock);
		अगर (dn)
			अवरोध;
	पूर्ण
out_unlock:
	spin_unlock(&inode->i_lock);
	वापस dn;
पूर्ण

/*
 * Encode inक्रमmation about a cap क्रम a reconnect with the MDS.
 */
अटल पूर्णांक reconnect_caps_cb(काष्ठा inode *inode, काष्ठा ceph_cap *cap,
			  व्योम *arg)
अणु
	जोड़ अणु
		काष्ठा ceph_mds_cap_reconnect v2;
		काष्ठा ceph_mds_cap_reconnect_v1 v1;
	पूर्ण rec;
	काष्ठा ceph_inode_info *ci = cap->ci;
	काष्ठा ceph_reconnect_state *recon_state = arg;
	काष्ठा ceph_pagelist *pagelist = recon_state->pagelist;
	काष्ठा dentry *dentry;
	अक्षर *path;
	पूर्णांक pathlen, err;
	u64 pathbase;
	u64 snap_follows;

	करोut(" adding %p ino %llx.%llx cap %p %lld %s\n",
	     inode, ceph_vinop(inode), cap, cap->cap_id,
	     ceph_cap_string(cap->issued));

	dentry = d_find_primary(inode);
	अगर (dentry) अणु
		/* set pathbase to parent dir when msg_version >= 2 */
		path = ceph_mdsc_build_path(dentry, &pathlen, &pathbase,
					    recon_state->msg_version >= 2);
		dput(dentry);
		अगर (IS_ERR(path)) अणु
			err = PTR_ERR(path);
			जाओ out_err;
		पूर्ण
	पूर्ण अन्यथा अणु
		path = शून्य;
		pathlen = 0;
		pathbase = 0;
	पूर्ण

	spin_lock(&ci->i_ceph_lock);
	cap->seq = 0;        /* reset cap seq */
	cap->issue_seq = 0;  /* and issue_seq */
	cap->mseq = 0;       /* and migrate_seq */
	cap->cap_gen = cap->session->s_cap_gen;

	/* These are lost when the session goes away */
	अगर (S_ISसूची(inode->i_mode)) अणु
		अगर (cap->issued & CEPH_CAP_सूची_CREATE) अणु
			ceph_put_string(rcu_dereference_raw(ci->i_cached_layout.pool_ns));
			स_रखो(&ci->i_cached_layout, 0, माप(ci->i_cached_layout));
		पूर्ण
		cap->issued &= ~CEPH_CAP_ANY_सूची_OPS;
	पूर्ण

	अगर (recon_state->msg_version >= 2) अणु
		rec.v2.cap_id = cpu_to_le64(cap->cap_id);
		rec.v2.wanted = cpu_to_le32(__ceph_caps_wanted(ci));
		rec.v2.issued = cpu_to_le32(cap->issued);
		rec.v2.snaprealm = cpu_to_le64(ci->i_snap_realm->ino);
		rec.v2.pathbase = cpu_to_le64(pathbase);
		rec.v2.flock_len = (__क्रमce __le32)
			((ci->i_ceph_flags & CEPH_I_ERROR_खाताLOCK) ? 0 : 1);
	पूर्ण अन्यथा अणु
		rec.v1.cap_id = cpu_to_le64(cap->cap_id);
		rec.v1.wanted = cpu_to_le32(__ceph_caps_wanted(ci));
		rec.v1.issued = cpu_to_le32(cap->issued);
		rec.v1.size = cpu_to_le64(i_size_पढ़ो(inode));
		ceph_encode_बारpec64(&rec.v1.mसमय, &inode->i_mसमय);
		ceph_encode_बारpec64(&rec.v1.aसमय, &inode->i_aसमय);
		rec.v1.snaprealm = cpu_to_le64(ci->i_snap_realm->ino);
		rec.v1.pathbase = cpu_to_le64(pathbase);
	पूर्ण

	अगर (list_empty(&ci->i_cap_snaps)) अणु
		snap_follows = ci->i_head_snapc ? ci->i_head_snapc->seq : 0;
	पूर्ण अन्यथा अणु
		काष्ठा ceph_cap_snap *capsnap =
			list_first_entry(&ci->i_cap_snaps,
					 काष्ठा ceph_cap_snap, ci_item);
		snap_follows = capsnap->follows;
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);

	अगर (recon_state->msg_version >= 2) अणु
		पूर्णांक num_fcntl_locks, num_flock_locks;
		काष्ठा ceph_filelock *flocks = शून्य;
		माप_प्रकार काष्ठा_len, total_len = माप(u64);
		u8 काष्ठा_v = 0;

encode_again:
		अगर (rec.v2.flock_len) अणु
			ceph_count_locks(inode, &num_fcntl_locks, &num_flock_locks);
		पूर्ण अन्यथा अणु
			num_fcntl_locks = 0;
			num_flock_locks = 0;
		पूर्ण
		अगर (num_fcntl_locks + num_flock_locks > 0) अणु
			flocks = kदो_स्मृति_array(num_fcntl_locks + num_flock_locks,
					       माप(काष्ठा ceph_filelock),
					       GFP_NOFS);
			अगर (!flocks) अणु
				err = -ENOMEM;
				जाओ out_err;
			पूर्ण
			err = ceph_encode_locks_to_buffer(inode, flocks,
							  num_fcntl_locks,
							  num_flock_locks);
			अगर (err) अणु
				kमुक्त(flocks);
				flocks = शून्य;
				अगर (err == -ENOSPC)
					जाओ encode_again;
				जाओ out_err;
			पूर्ण
		पूर्ण अन्यथा अणु
			kमुक्त(flocks);
			flocks = शून्य;
		पूर्ण

		अगर (recon_state->msg_version >= 3) अणु
			/* version, compat_version and काष्ठा_len */
			total_len += 2 * माप(u8) + माप(u32);
			काष्ठा_v = 2;
		पूर्ण
		/*
		 * number of encoded locks is stable, so copy to pagelist
		 */
		काष्ठा_len = 2 * माप(u32) +
			    (num_fcntl_locks + num_flock_locks) *
			    माप(काष्ठा ceph_filelock);
		rec.v2.flock_len = cpu_to_le32(काष्ठा_len);

		काष्ठा_len += माप(u32) + pathlen + माप(rec.v2);

		अगर (काष्ठा_v >= 2)
			काष्ठा_len += माप(u64); /* snap_follows */

		total_len += काष्ठा_len;

		अगर (pagelist->length + total_len > RECONNECT_MAX_SIZE) अणु
			err = send_reconnect_partial(recon_state);
			अगर (err)
				जाओ out_मुक्तflocks;
			pagelist = recon_state->pagelist;
		पूर्ण

		err = ceph_pagelist_reserve(pagelist, total_len);
		अगर (err)
			जाओ out_मुक्तflocks;

		ceph_pagelist_encode_64(pagelist, ceph_ino(inode));
		अगर (recon_state->msg_version >= 3) अणु
			ceph_pagelist_encode_8(pagelist, काष्ठा_v);
			ceph_pagelist_encode_8(pagelist, 1);
			ceph_pagelist_encode_32(pagelist, काष्ठा_len);
		पूर्ण
		ceph_pagelist_encode_string(pagelist, path, pathlen);
		ceph_pagelist_append(pagelist, &rec, माप(rec.v2));
		ceph_locks_to_pagelist(flocks, pagelist,
				       num_fcntl_locks, num_flock_locks);
		अगर (काष्ठा_v >= 2)
			ceph_pagelist_encode_64(pagelist, snap_follows);
out_मुक्तflocks:
		kमुक्त(flocks);
	पूर्ण अन्यथा अणु
		err = ceph_pagelist_reserve(pagelist,
					    माप(u64) + माप(u32) +
					    pathlen + माप(rec.v1));
		अगर (err)
			जाओ out_err;

		ceph_pagelist_encode_64(pagelist, ceph_ino(inode));
		ceph_pagelist_encode_string(pagelist, path, pathlen);
		ceph_pagelist_append(pagelist, &rec, माप(rec.v1));
	पूर्ण

out_err:
	ceph_mdsc_मुक्त_path(path, pathlen);
	अगर (!err)
		recon_state->nr_caps++;
	वापस err;
पूर्ण

अटल पूर्णांक encode_snap_realms(काष्ठा ceph_mds_client *mdsc,
			      काष्ठा ceph_reconnect_state *recon_state)
अणु
	काष्ठा rb_node *p;
	काष्ठा ceph_pagelist *pagelist = recon_state->pagelist;
	पूर्णांक err = 0;

	अगर (recon_state->msg_version >= 4) अणु
		err = ceph_pagelist_encode_32(pagelist, mdsc->num_snap_realms);
		अगर (err < 0)
			जाओ fail;
	पूर्ण

	/*
	 * snaprealms.  we provide mds with the ino, seq (version), and
	 * parent क्रम all of our realms.  If the mds has any newer info,
	 * it will tell us.
	 */
	क्रम (p = rb_first(&mdsc->snap_realms); p; p = rb_next(p)) अणु
		काष्ठा ceph_snap_realm *realm =
		       rb_entry(p, काष्ठा ceph_snap_realm, node);
		काष्ठा ceph_mds_snaprealm_reconnect sr_rec;

		अगर (recon_state->msg_version >= 4) अणु
			माप_प्रकार need = माप(u8) * 2 + माप(u32) +
				      माप(sr_rec);

			अगर (pagelist->length + need > RECONNECT_MAX_SIZE) अणु
				err = send_reconnect_partial(recon_state);
				अगर (err)
					जाओ fail;
				pagelist = recon_state->pagelist;
			पूर्ण

			err = ceph_pagelist_reserve(pagelist, need);
			अगर (err)
				जाओ fail;

			ceph_pagelist_encode_8(pagelist, 1);
			ceph_pagelist_encode_8(pagelist, 1);
			ceph_pagelist_encode_32(pagelist, माप(sr_rec));
		पूर्ण

		करोut(" adding snap realm %llx seq %lld parent %llx\n",
		     realm->ino, realm->seq, realm->parent_ino);
		sr_rec.ino = cpu_to_le64(realm->ino);
		sr_rec.seq = cpu_to_le64(realm->seq);
		sr_rec.parent = cpu_to_le64(realm->parent_ino);

		err = ceph_pagelist_append(pagelist, &sr_rec, माप(sr_rec));
		अगर (err)
			जाओ fail;

		recon_state->nr_realms++;
	पूर्ण
fail:
	वापस err;
पूर्ण


/*
 * If an MDS fails and recovers, clients need to reconnect in order to
 * reestablish shared state.  This includes all caps issued through
 * this session _and_ the snap_realm hierarchy.  Because it's not
 * clear which snap realms the mds cares about, we send everything we
 * know about.. that ensures we'll then get any new info the
 * recovering MDS might have.
 *
 * This is a relatively heavyweight operation, but it's rare.
 */
अटल व्योम send_mds_reconnect(काष्ठा ceph_mds_client *mdsc,
			       काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_msg *reply;
	पूर्णांक mds = session->s_mds;
	पूर्णांक err = -ENOMEM;
	काष्ठा ceph_reconnect_state recon_state = अणु
		.session = session,
	पूर्ण;
	LIST_HEAD(dispose);

	pr_info("mds%d reconnect start\n", mds);

	recon_state.pagelist = ceph_pagelist_alloc(GFP_NOFS);
	अगर (!recon_state.pagelist)
		जाओ fail_nopagelist;

	reply = ceph_msg_new2(CEPH_MSG_CLIENT_RECONNECT, 0, 1, GFP_NOFS, false);
	अगर (!reply)
		जाओ fail_nomsg;

	xa_destroy(&session->s_delegated_inos);

	mutex_lock(&session->s_mutex);
	session->s_state = CEPH_MDS_SESSION_RECONNECTING;
	session->s_seq = 0;

	करोut("session %p state %s\n", session,
	     ceph_session_state_name(session->s_state));

	spin_lock(&session->s_gen_ttl_lock);
	session->s_cap_gen++;
	spin_unlock(&session->s_gen_ttl_lock);

	spin_lock(&session->s_cap_lock);
	/* करोn't know अगर session is पढ़ोonly */
	session->s_पढ़ोonly = 0;
	/*
	 * notअगरy __ceph_हटाओ_cap() that we are composing cap reconnect.
	 * If a cap get released beक्रमe being added to the cap reconnect,
	 * __ceph_हटाओ_cap() should skip queuing cap release.
	 */
	session->s_cap_reconnect = 1;
	/* drop old cap expires; we're about to reestablish that state */
	detach_cap_releases(session, &dispose);
	spin_unlock(&session->s_cap_lock);
	dispose_cap_releases(mdsc, &dispose);

	/* trim unused caps to reduce MDS's cache rejoin समय */
	अगर (mdsc->fsc->sb->s_root)
		shrink_dcache_parent(mdsc->fsc->sb->s_root);

	ceph_con_बंद(&session->s_con);
	ceph_con_खोलो(&session->s_con,
		      CEPH_ENTITY_TYPE_MDS, mds,
		      ceph_mdsmap_get_addr(mdsc->mdsmap, mds));

	/* replay unsafe requests */
	replay_unsafe_requests(mdsc, session);

	ceph_early_kick_flushing_caps(mdsc, session);

	करोwn_पढ़ो(&mdsc->snap_rwsem);

	/* placeholder क्रम nr_caps */
	err = ceph_pagelist_encode_32(recon_state.pagelist, 0);
	अगर (err)
		जाओ fail;

	अगर (test_bit(CEPHFS_FEATURE_MULTI_RECONNECT, &session->s_features)) अणु
		recon_state.msg_version = 3;
		recon_state.allow_multi = true;
	पूर्ण अन्यथा अगर (session->s_con.peer_features & CEPH_FEATURE_MDSENC) अणु
		recon_state.msg_version = 3;
	पूर्ण अन्यथा अणु
		recon_state.msg_version = 2;
	पूर्ण
	/* trsaverse this session's caps */
	err = ceph_iterate_session_caps(session, reconnect_caps_cb, &recon_state);

	spin_lock(&session->s_cap_lock);
	session->s_cap_reconnect = 0;
	spin_unlock(&session->s_cap_lock);

	अगर (err < 0)
		जाओ fail;

	/* check अगर all realms can be encoded पूर्णांकo current message */
	अगर (mdsc->num_snap_realms) अणु
		माप_प्रकार total_len =
			recon_state.pagelist->length +
			mdsc->num_snap_realms *
			माप(काष्ठा ceph_mds_snaprealm_reconnect);
		अगर (recon_state.msg_version >= 4) अणु
			/* number of realms */
			total_len += माप(u32);
			/* version, compat_version and काष्ठा_len */
			total_len += mdsc->num_snap_realms *
				     (2 * माप(u8) + माप(u32));
		पूर्ण
		अगर (total_len > RECONNECT_MAX_SIZE) अणु
			अगर (!recon_state.allow_multi) अणु
				err = -ENOSPC;
				जाओ fail;
			पूर्ण
			अगर (recon_state.nr_caps) अणु
				err = send_reconnect_partial(&recon_state);
				अगर (err)
					जाओ fail;
			पूर्ण
			recon_state.msg_version = 5;
		पूर्ण
	पूर्ण

	err = encode_snap_realms(mdsc, &recon_state);
	अगर (err < 0)
		जाओ fail;

	अगर (recon_state.msg_version >= 5) अणु
		err = ceph_pagelist_encode_8(recon_state.pagelist, 0);
		अगर (err < 0)
			जाओ fail;
	पूर्ण

	अगर (recon_state.nr_caps || recon_state.nr_realms) अणु
		काष्ठा page *page =
			list_first_entry(&recon_state.pagelist->head,
					काष्ठा page, lru);
		__le32 *addr = kmap_atomic(page);
		अगर (recon_state.nr_caps) अणु
			WARN_ON(recon_state.nr_realms != mdsc->num_snap_realms);
			*addr = cpu_to_le32(recon_state.nr_caps);
		पूर्ण अन्यथा अगर (recon_state.msg_version >= 4) अणु
			*(addr + 1) = cpu_to_le32(recon_state.nr_realms);
		पूर्ण
		kunmap_atomic(addr);
	पूर्ण

	reply->hdr.version = cpu_to_le16(recon_state.msg_version);
	अगर (recon_state.msg_version >= 4)
		reply->hdr.compat_version = cpu_to_le16(4);

	reply->hdr.data_len = cpu_to_le32(recon_state.pagelist->length);
	ceph_msg_data_add_pagelist(reply, recon_state.pagelist);

	ceph_con_send(&session->s_con, reply);

	mutex_unlock(&session->s_mutex);

	mutex_lock(&mdsc->mutex);
	__wake_requests(mdsc, &session->s_रुकोing);
	mutex_unlock(&mdsc->mutex);

	up_पढ़ो(&mdsc->snap_rwsem);
	ceph_pagelist_release(recon_state.pagelist);
	वापस;

fail:
	ceph_msg_put(reply);
	up_पढ़ो(&mdsc->snap_rwsem);
	mutex_unlock(&session->s_mutex);
fail_nomsg:
	ceph_pagelist_release(recon_state.pagelist);
fail_nopagelist:
	pr_err("error %d preparing reconnect for mds%d\n", err, mds);
	वापस;
पूर्ण


/*
 * compare old and new mdsmaps, kicking requests
 * and closing out old connections as necessary
 *
 * called under mdsc->mutex.
 */
अटल व्योम check_new_map(काष्ठा ceph_mds_client *mdsc,
			  काष्ठा ceph_mdsmap *newmap,
			  काष्ठा ceph_mdsmap *oldmap)
अणु
	पूर्णांक i;
	पूर्णांक oldstate, newstate;
	काष्ठा ceph_mds_session *s;

	करोut("check_new_map new %u old %u\n",
	     newmap->m_epoch, oldmap->m_epoch);

	क्रम (i = 0; i < oldmap->possible_max_rank && i < mdsc->max_sessions; i++) अणु
		अगर (!mdsc->sessions[i])
			जारी;
		s = mdsc->sessions[i];
		oldstate = ceph_mdsmap_get_state(oldmap, i);
		newstate = ceph_mdsmap_get_state(newmap, i);

		करोut("check_new_map mds%d state %s%s -> %s%s (session %s)\n",
		     i, ceph_mds_state_name(oldstate),
		     ceph_mdsmap_is_laggy(oldmap, i) ? " (laggy)" : "",
		     ceph_mds_state_name(newstate),
		     ceph_mdsmap_is_laggy(newmap, i) ? " (laggy)" : "",
		     ceph_session_state_name(s->s_state));

		अगर (i >= newmap->possible_max_rank) अणु
			/* क्रमce बंद session क्रम stopped mds */
			ceph_get_mds_session(s);
			__unरेजिस्टर_session(mdsc, s);
			__wake_requests(mdsc, &s->s_रुकोing);
			mutex_unlock(&mdsc->mutex);

			mutex_lock(&s->s_mutex);
			cleanup_session_requests(mdsc, s);
			हटाओ_session_caps(s);
			mutex_unlock(&s->s_mutex);

			ceph_put_mds_session(s);

			mutex_lock(&mdsc->mutex);
			kick_requests(mdsc, i);
			जारी;
		पूर्ण

		अगर (स_भेद(ceph_mdsmap_get_addr(oldmap, i),
			   ceph_mdsmap_get_addr(newmap, i),
			   माप(काष्ठा ceph_entity_addr))) अणु
			/* just बंद it */
			mutex_unlock(&mdsc->mutex);
			mutex_lock(&s->s_mutex);
			mutex_lock(&mdsc->mutex);
			ceph_con_बंद(&s->s_con);
			mutex_unlock(&s->s_mutex);
			s->s_state = CEPH_MDS_SESSION_RESTARTING;
		पूर्ण अन्यथा अगर (oldstate == newstate) अणु
			जारी;  /* nothing new with this mds */
		पूर्ण

		/*
		 * send reconnect?
		 */
		अगर (s->s_state == CEPH_MDS_SESSION_RESTARTING &&
		    newstate >= CEPH_MDS_STATE_RECONNECT) अणु
			mutex_unlock(&mdsc->mutex);
			send_mds_reconnect(mdsc, s);
			mutex_lock(&mdsc->mutex);
		पूर्ण

		/*
		 * kick request on any mds that has gone active.
		 */
		अगर (oldstate < CEPH_MDS_STATE_ACTIVE &&
		    newstate >= CEPH_MDS_STATE_ACTIVE) अणु
			अगर (oldstate != CEPH_MDS_STATE_CREATING &&
			    oldstate != CEPH_MDS_STATE_STARTING)
				pr_info("mds%d recovery completed\n", s->s_mds);
			kick_requests(mdsc, i);
			mutex_unlock(&mdsc->mutex);
			mutex_lock(&s->s_mutex);
			mutex_lock(&mdsc->mutex);
			ceph_kick_flushing_caps(mdsc, s);
			mutex_unlock(&s->s_mutex);
			wake_up_session_caps(s, RECONNECT);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < newmap->possible_max_rank && i < mdsc->max_sessions; i++) अणु
		s = mdsc->sessions[i];
		अगर (!s)
			जारी;
		अगर (!ceph_mdsmap_is_laggy(newmap, i))
			जारी;
		अगर (s->s_state == CEPH_MDS_SESSION_OPEN ||
		    s->s_state == CEPH_MDS_SESSION_HUNG ||
		    s->s_state == CEPH_MDS_SESSION_CLOSING) अणु
			करोut(" connecting to export targets of laggy mds%d\n",
			     i);
			__खोलो_export_target_sessions(mdsc, s);
		पूर्ण
	पूर्ण
पूर्ण



/*
 * leases
 */

/*
 * caller must hold session s_mutex, dentry->d_lock
 */
व्योम __ceph_mdsc_drop_dentry_lease(काष्ठा dentry *dentry)
अणु
	काष्ठा ceph_dentry_info *di = ceph_dentry(dentry);

	ceph_put_mds_session(di->lease_session);
	di->lease_session = शून्य;
पूर्ण

अटल व्योम handle_lease(काष्ठा ceph_mds_client *mdsc,
			 काष्ठा ceph_mds_session *session,
			 काष्ठा ceph_msg *msg)
अणु
	काष्ठा super_block *sb = mdsc->fsc->sb;
	काष्ठा inode *inode;
	काष्ठा dentry *parent, *dentry;
	काष्ठा ceph_dentry_info *di;
	पूर्णांक mds = session->s_mds;
	काष्ठा ceph_mds_lease *h = msg->front.iov_base;
	u32 seq;
	काष्ठा ceph_vino vino;
	काष्ठा qstr dname;
	पूर्णांक release = 0;

	करोut("handle_lease from mds%d\n", mds);

	/* decode */
	अगर (msg->front.iov_len < माप(*h) + माप(u32))
		जाओ bad;
	vino.ino = le64_to_cpu(h->ino);
	vino.snap = CEPH_NOSNAP;
	seq = le32_to_cpu(h->seq);
	dname.len = get_unaligned_le32(h + 1);
	अगर (msg->front.iov_len < माप(*h) + माप(u32) + dname.len)
		जाओ bad;
	dname.name = (व्योम *)(h + 1) + माप(u32);

	/* lookup inode */
	inode = ceph_find_inode(sb, vino);
	करोut("handle_lease %s, ino %llx %p %.*s\n",
	     ceph_lease_op_name(h->action), vino.ino, inode,
	     dname.len, dname.name);

	mutex_lock(&session->s_mutex);
	inc_session_sequence(session);

	अगर (!inode) अणु
		करोut("handle_lease no inode %llx\n", vino.ino);
		जाओ release;
	पूर्ण

	/* dentry */
	parent = d_find_alias(inode);
	अगर (!parent) अणु
		करोut("no parent dentry on inode %p\n", inode);
		WARN_ON(1);
		जाओ release;  /* hrm... */
	पूर्ण
	dname.hash = full_name_hash(parent, dname.name, dname.len);
	dentry = d_lookup(parent, &dname);
	dput(parent);
	अगर (!dentry)
		जाओ release;

	spin_lock(&dentry->d_lock);
	di = ceph_dentry(dentry);
	चयन (h->action) अणु
	हाल CEPH_MDS_LEASE_REVOKE:
		अगर (di->lease_session == session) अणु
			अगर (ceph_seq_cmp(di->lease_seq, seq) > 0)
				h->seq = cpu_to_le32(di->lease_seq);
			__ceph_mdsc_drop_dentry_lease(dentry);
		पूर्ण
		release = 1;
		अवरोध;

	हाल CEPH_MDS_LEASE_RENEW:
		अगर (di->lease_session == session &&
		    di->lease_gen == session->s_cap_gen &&
		    di->lease_renew_from &&
		    di->lease_renew_after == 0) अणु
			अचिन्हित दीर्घ duration =
				msecs_to_jअगरfies(le32_to_cpu(h->duration_ms));

			di->lease_seq = seq;
			di->समय = di->lease_renew_from + duration;
			di->lease_renew_after = di->lease_renew_from +
				(duration >> 1);
			di->lease_renew_from = 0;
		पूर्ण
		अवरोध;
	पूर्ण
	spin_unlock(&dentry->d_lock);
	dput(dentry);

	अगर (!release)
		जाओ out;

release:
	/* let's just reuse the same message */
	h->action = CEPH_MDS_LEASE_REVOKE_ACK;
	ceph_msg_get(msg);
	ceph_con_send(&session->s_con, msg);

out:
	mutex_unlock(&session->s_mutex);
	/* aव्योम calling iput_final() in mds dispatch thपढ़ोs */
	ceph_async_iput(inode);
	वापस;

bad:
	pr_err("corrupt lease message\n");
	ceph_msg_dump(msg);
पूर्ण

व्योम ceph_mdsc_lease_send_msg(काष्ठा ceph_mds_session *session,
			      काष्ठा dentry *dentry, अक्षर action,
			      u32 seq)
अणु
	काष्ठा ceph_msg *msg;
	काष्ठा ceph_mds_lease *lease;
	काष्ठा inode *dir;
	पूर्णांक len = माप(*lease) + माप(u32) + NAME_MAX;

	करोut("lease_send_msg identry %p %s to mds%d\n",
	     dentry, ceph_lease_op_name(action), session->s_mds);

	msg = ceph_msg_new(CEPH_MSG_CLIENT_LEASE, len, GFP_NOFS, false);
	अगर (!msg)
		वापस;
	lease = msg->front.iov_base;
	lease->action = action;
	lease->seq = cpu_to_le32(seq);

	spin_lock(&dentry->d_lock);
	dir = d_inode(dentry->d_parent);
	lease->ino = cpu_to_le64(ceph_ino(dir));
	lease->first = lease->last = cpu_to_le64(ceph_snap(dir));

	put_unaligned_le32(dentry->d_name.len, lease + 1);
	स_नकल((व्योम *)(lease + 1) + 4,
	       dentry->d_name.name, dentry->d_name.len);
	spin_unlock(&dentry->d_lock);
	/*
	 * अगर this is a preemptive lease RELEASE, no need to
	 * flush request stream, since the actual request will
	 * soon follow.
	 */
	msg->more_to_follow = (action == CEPH_MDS_LEASE_RELEASE);

	ceph_con_send(&session->s_con, msg);
पूर्ण

/*
 * lock unlock sessions, to रुको ongoing session activities
 */
अटल व्योम lock_unlock_sessions(काष्ठा ceph_mds_client *mdsc)
अणु
	पूर्णांक i;

	mutex_lock(&mdsc->mutex);
	क्रम (i = 0; i < mdsc->max_sessions; i++) अणु
		काष्ठा ceph_mds_session *s = __ceph_lookup_mds_session(mdsc, i);
		अगर (!s)
			जारी;
		mutex_unlock(&mdsc->mutex);
		mutex_lock(&s->s_mutex);
		mutex_unlock(&s->s_mutex);
		ceph_put_mds_session(s);
		mutex_lock(&mdsc->mutex);
	पूर्ण
	mutex_unlock(&mdsc->mutex);
पूर्ण

अटल व्योम maybe_recover_session(काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा ceph_fs_client *fsc = mdsc->fsc;

	अगर (!ceph_test_mount_opt(fsc, CLEANRECOVER))
		वापस;

	अगर (READ_ONCE(fsc->mount_state) != CEPH_MOUNT_MOUNTED)
		वापस;

	अगर (!READ_ONCE(fsc->blocklisted))
		वापस;

	pr_info("auto reconnect after blocklisted\n");
	ceph_क्रमce_reconnect(fsc->sb);
पूर्ण

bool check_session_state(काष्ठा ceph_mds_session *s)
अणु
	चयन (s->s_state) अणु
	हाल CEPH_MDS_SESSION_OPEN:
		अगर (s->s_ttl && समय_after(jअगरfies, s->s_ttl)) अणु
			s->s_state = CEPH_MDS_SESSION_HUNG;
			pr_info("mds%d hung\n", s->s_mds);
		पूर्ण
		अवरोध;
	हाल CEPH_MDS_SESSION_CLOSING:
		/* Should never reach this when we're unmounting */
		WARN_ON_ONCE(true);
		fallthrough;
	हाल CEPH_MDS_SESSION_NEW:
	हाल CEPH_MDS_SESSION_RESTARTING:
	हाल CEPH_MDS_SESSION_CLOSED:
	हाल CEPH_MDS_SESSION_REJECTED:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * If the sequence is incremented जबतक we're रुकोing on a REQUEST_CLOSE reply,
 * then we need to retransmit that request.
 */
व्योम inc_session_sequence(काष्ठा ceph_mds_session *s)
अणु
	lockdep_निश्चित_held(&s->s_mutex);

	s->s_seq++;

	अगर (s->s_state == CEPH_MDS_SESSION_CLOSING) अणु
		पूर्णांक ret;

		करोut("resending session close request for mds%d\n", s->s_mds);
		ret = request_बंद_session(s);
		अगर (ret < 0)
			pr_err("unable to close session to mds%d: %d\n",
			       s->s_mds, ret);
	पूर्ण
पूर्ण

/*
 * delayed work -- periodically trim expired leases, renew caps with mds
 */
अटल व्योम schedule_delayed(काष्ठा ceph_mds_client *mdsc)
अणु
	पूर्णांक delay = 5;
	अचिन्हित hz = round_jअगरfies_relative(HZ * delay);
	schedule_delayed_work(&mdsc->delayed_work, hz);
पूर्ण

अटल व्योम delayed_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक i;
	काष्ठा ceph_mds_client *mdsc =
		container_of(work, काष्ठा ceph_mds_client, delayed_work.work);
	पूर्णांक renew_पूर्णांकerval;
	पूर्णांक renew_caps;

	करोut("mdsc delayed_work\n");

	अगर (mdsc->stopping)
		वापस;

	mutex_lock(&mdsc->mutex);
	renew_पूर्णांकerval = mdsc->mdsmap->m_session_समयout >> 2;
	renew_caps = समय_after_eq(jअगरfies, HZ*renew_पूर्णांकerval +
				   mdsc->last_renew_caps);
	अगर (renew_caps)
		mdsc->last_renew_caps = jअगरfies;

	क्रम (i = 0; i < mdsc->max_sessions; i++) अणु
		काष्ठा ceph_mds_session *s = __ceph_lookup_mds_session(mdsc, i);
		अगर (!s)
			जारी;

		अगर (!check_session_state(s)) अणु
			ceph_put_mds_session(s);
			जारी;
		पूर्ण
		mutex_unlock(&mdsc->mutex);

		mutex_lock(&s->s_mutex);
		अगर (renew_caps)
			send_renew_caps(mdsc, s);
		अन्यथा
			ceph_con_keepalive(&s->s_con);
		अगर (s->s_state == CEPH_MDS_SESSION_OPEN ||
		    s->s_state == CEPH_MDS_SESSION_HUNG)
			ceph_send_cap_releases(mdsc, s);
		mutex_unlock(&s->s_mutex);
		ceph_put_mds_session(s);

		mutex_lock(&mdsc->mutex);
	पूर्ण
	mutex_unlock(&mdsc->mutex);

	ceph_check_delayed_caps(mdsc);

	ceph_queue_cap_reclaim_work(mdsc);

	ceph_trim_snapid_map(mdsc);

	maybe_recover_session(mdsc);

	schedule_delayed(mdsc);
पूर्ण

पूर्णांक ceph_mdsc_init(काष्ठा ceph_fs_client *fsc)

अणु
	काष्ठा ceph_mds_client *mdsc;
	पूर्णांक err;

	mdsc = kzalloc(माप(काष्ठा ceph_mds_client), GFP_NOFS);
	अगर (!mdsc)
		वापस -ENOMEM;
	mdsc->fsc = fsc;
	mutex_init(&mdsc->mutex);
	mdsc->mdsmap = kzalloc(माप(*mdsc->mdsmap), GFP_NOFS);
	अगर (!mdsc->mdsmap) अणु
		err = -ENOMEM;
		जाओ err_mdsc;
	पूर्ण

	init_completion(&mdsc->safe_umount_रुकोers);
	init_रुकोqueue_head(&mdsc->session_बंद_wq);
	INIT_LIST_HEAD(&mdsc->रुकोing_क्रम_map);
	mdsc->sessions = शून्य;
	atomic_set(&mdsc->num_sessions, 0);
	mdsc->max_sessions = 0;
	mdsc->stopping = 0;
	atomic64_set(&mdsc->quotarealms_count, 0);
	mdsc->quotarealms_inodes = RB_ROOT;
	mutex_init(&mdsc->quotarealms_inodes_mutex);
	mdsc->last_snap_seq = 0;
	init_rwsem(&mdsc->snap_rwsem);
	mdsc->snap_realms = RB_ROOT;
	INIT_LIST_HEAD(&mdsc->snap_empty);
	mdsc->num_snap_realms = 0;
	spin_lock_init(&mdsc->snap_empty_lock);
	mdsc->last_tid = 0;
	mdsc->oldest_tid = 0;
	mdsc->request_tree = RB_ROOT;
	INIT_DELAYED_WORK(&mdsc->delayed_work, delayed_work);
	mdsc->last_renew_caps = jअगरfies;
	INIT_LIST_HEAD(&mdsc->cap_delay_list);
	INIT_LIST_HEAD(&mdsc->cap_रुको_list);
	spin_lock_init(&mdsc->cap_delay_lock);
	INIT_LIST_HEAD(&mdsc->snap_flush_list);
	spin_lock_init(&mdsc->snap_flush_lock);
	mdsc->last_cap_flush_tid = 1;
	INIT_LIST_HEAD(&mdsc->cap_flush_list);
	INIT_LIST_HEAD(&mdsc->cap_dirty_migrating);
	mdsc->num_cap_flushing = 0;
	spin_lock_init(&mdsc->cap_dirty_lock);
	init_रुकोqueue_head(&mdsc->cap_flushing_wq);
	INIT_WORK(&mdsc->cap_reclaim_work, ceph_cap_reclaim_work);
	atomic_set(&mdsc->cap_reclaim_pending, 0);
	err = ceph_metric_init(&mdsc->metric);
	अगर (err)
		जाओ err_mdsmap;

	spin_lock_init(&mdsc->dentry_list_lock);
	INIT_LIST_HEAD(&mdsc->dentry_leases);
	INIT_LIST_HEAD(&mdsc->dentry_dir_leases);

	ceph_caps_init(mdsc);
	ceph_adjust_caps_max_min(mdsc, fsc->mount_options);

	spin_lock_init(&mdsc->snapid_map_lock);
	mdsc->snapid_map_tree = RB_ROOT;
	INIT_LIST_HEAD(&mdsc->snapid_map_lru);

	init_rwsem(&mdsc->pool_perm_rwsem);
	mdsc->pool_perm_tree = RB_ROOT;

	strscpy(mdsc->nodename, utsname()->nodename,
		माप(mdsc->nodename));

	fsc->mdsc = mdsc;
	वापस 0;

err_mdsmap:
	kमुक्त(mdsc->mdsmap);
err_mdsc:
	kमुक्त(mdsc);
	वापस err;
पूर्ण

/*
 * Wait क्रम safe replies on खोलो mds requests.  If we समय out, drop
 * all requests from the tree to aव्योम dangling dentry refs.
 */
अटल व्योम रुको_requests(काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा ceph_options *opts = mdsc->fsc->client->options;
	काष्ठा ceph_mds_request *req;

	mutex_lock(&mdsc->mutex);
	अगर (__get_oldest_req(mdsc)) अणु
		mutex_unlock(&mdsc->mutex);

		करोut("wait_requests waiting for requests\n");
		रुको_क्रम_completion_समयout(&mdsc->safe_umount_रुकोers,
				    ceph_समयout_jअगरfies(opts->mount_समयout));

		/* tear करोwn reमुख्यing requests */
		mutex_lock(&mdsc->mutex);
		जबतक ((req = __get_oldest_req(mdsc))) अणु
			करोut("wait_requests timed out on tid %llu\n",
			     req->r_tid);
			list_del_init(&req->r_रुको);
			__unरेजिस्टर_request(mdsc, req);
		पूर्ण
	पूर्ण
	mutex_unlock(&mdsc->mutex);
	करोut("wait_requests done\n");
पूर्ण

/*
 * called beक्रमe mount is ro, and beक्रमe dentries are torn करोwn.
 * (hmm, करोes this still race with new lookups?)
 */
व्योम ceph_mdsc_pre_umount(काष्ठा ceph_mds_client *mdsc)
अणु
	करोut("pre_umount\n");
	mdsc->stopping = 1;

	lock_unlock_sessions(mdsc);
	ceph_flush_dirty_caps(mdsc);
	रुको_requests(mdsc);

	/*
	 * रुको क्रम reply handlers to drop their request refs and
	 * their inode/dcache refs
	 */
	ceph_msgr_flush();

	ceph_cleanup_quotarealms_inodes(mdsc);
पूर्ण

/*
 * रुको क्रम all ग_लिखो mds requests to flush.
 */
अटल व्योम रुको_unsafe_requests(काष्ठा ceph_mds_client *mdsc, u64 want_tid)
अणु
	काष्ठा ceph_mds_request *req = शून्य, *nextreq;
	काष्ठा rb_node *n;

	mutex_lock(&mdsc->mutex);
	करोut("wait_unsafe_requests want %lld\n", want_tid);
restart:
	req = __get_oldest_req(mdsc);
	जबतक (req && req->r_tid <= want_tid) अणु
		/* find next request */
		n = rb_next(&req->r_node);
		अगर (n)
			nextreq = rb_entry(n, काष्ठा ceph_mds_request, r_node);
		अन्यथा
			nextreq = शून्य;
		अगर (req->r_op != CEPH_MDS_OP_SETखाताLOCK &&
		    (req->r_op & CEPH_MDS_OP_WRITE)) अणु
			/* ग_लिखो op */
			ceph_mdsc_get_request(req);
			अगर (nextreq)
				ceph_mdsc_get_request(nextreq);
			mutex_unlock(&mdsc->mutex);
			करोut("wait_unsafe_requests  wait on %llu (want %llu)\n",
			     req->r_tid, want_tid);
			रुको_क्रम_completion(&req->r_safe_completion);
			mutex_lock(&mdsc->mutex);
			ceph_mdsc_put_request(req);
			अगर (!nextreq)
				अवरोध;  /* next dne beक्रमe, so we're करोne! */
			अगर (RB_EMPTY_NODE(&nextreq->r_node)) अणु
				/* next request was हटाओd from tree */
				ceph_mdsc_put_request(nextreq);
				जाओ restart;
			पूर्ण
			ceph_mdsc_put_request(nextreq);  /* won't go away */
		पूर्ण
		req = nextreq;
	पूर्ण
	mutex_unlock(&mdsc->mutex);
	करोut("wait_unsafe_requests done\n");
पूर्ण

व्योम ceph_mdsc_sync(काष्ठा ceph_mds_client *mdsc)
अणु
	u64 want_tid, want_flush;

	अगर (READ_ONCE(mdsc->fsc->mount_state) >= CEPH_MOUNT_SHUTDOWN)
		वापस;

	करोut("sync\n");
	mutex_lock(&mdsc->mutex);
	want_tid = mdsc->last_tid;
	mutex_unlock(&mdsc->mutex);

	ceph_flush_dirty_caps(mdsc);
	spin_lock(&mdsc->cap_dirty_lock);
	want_flush = mdsc->last_cap_flush_tid;
	अगर (!list_empty(&mdsc->cap_flush_list)) अणु
		काष्ठा ceph_cap_flush *cf =
			list_last_entry(&mdsc->cap_flush_list,
					काष्ठा ceph_cap_flush, g_list);
		cf->wake = true;
	पूर्ण
	spin_unlock(&mdsc->cap_dirty_lock);

	करोut("sync want tid %lld flush_seq %lld\n",
	     want_tid, want_flush);

	रुको_unsafe_requests(mdsc, want_tid);
	रुको_caps_flush(mdsc, want_flush);
पूर्ण

/*
 * true अगर all sessions are बंदd, or we क्रमce unmount
 */
अटल bool करोne_closing_sessions(काष्ठा ceph_mds_client *mdsc, पूर्णांक skipped)
अणु
	अगर (READ_ONCE(mdsc->fsc->mount_state) == CEPH_MOUNT_SHUTDOWN)
		वापस true;
	वापस atomic_पढ़ो(&mdsc->num_sessions) <= skipped;
पूर्ण

/*
 * called after sb is ro.
 */
व्योम ceph_mdsc_बंद_sessions(काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा ceph_options *opts = mdsc->fsc->client->options;
	काष्ठा ceph_mds_session *session;
	पूर्णांक i;
	पूर्णांक skipped = 0;

	करोut("close_sessions\n");

	/* बंद sessions */
	mutex_lock(&mdsc->mutex);
	क्रम (i = 0; i < mdsc->max_sessions; i++) अणु
		session = __ceph_lookup_mds_session(mdsc, i);
		अगर (!session)
			जारी;
		mutex_unlock(&mdsc->mutex);
		mutex_lock(&session->s_mutex);
		अगर (__बंद_session(mdsc, session) <= 0)
			skipped++;
		mutex_unlock(&session->s_mutex);
		ceph_put_mds_session(session);
		mutex_lock(&mdsc->mutex);
	पूर्ण
	mutex_unlock(&mdsc->mutex);

	करोut("waiting for sessions to close\n");
	रुको_event_समयout(mdsc->session_बंद_wq,
			   करोne_closing_sessions(mdsc, skipped),
			   ceph_समयout_jअगरfies(opts->mount_समयout));

	/* tear करोwn reमुख्यing sessions */
	mutex_lock(&mdsc->mutex);
	क्रम (i = 0; i < mdsc->max_sessions; i++) अणु
		अगर (mdsc->sessions[i]) अणु
			session = ceph_get_mds_session(mdsc->sessions[i]);
			__unरेजिस्टर_session(mdsc, session);
			mutex_unlock(&mdsc->mutex);
			mutex_lock(&session->s_mutex);
			हटाओ_session_caps(session);
			mutex_unlock(&session->s_mutex);
			ceph_put_mds_session(session);
			mutex_lock(&mdsc->mutex);
		पूर्ण
	पूर्ण
	WARN_ON(!list_empty(&mdsc->cap_delay_list));
	mutex_unlock(&mdsc->mutex);

	ceph_cleanup_snapid_map(mdsc);
	ceph_cleanup_empty_realms(mdsc);

	cancel_work_sync(&mdsc->cap_reclaim_work);
	cancel_delayed_work_sync(&mdsc->delayed_work); /* cancel समयr */

	करोut("stopped\n");
पूर्ण

व्योम ceph_mdsc_क्रमce_umount(काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा ceph_mds_session *session;
	पूर्णांक mds;

	करोut("force umount\n");

	mutex_lock(&mdsc->mutex);
	क्रम (mds = 0; mds < mdsc->max_sessions; mds++) अणु
		session = __ceph_lookup_mds_session(mdsc, mds);
		अगर (!session)
			जारी;

		अगर (session->s_state == CEPH_MDS_SESSION_REJECTED)
			__unरेजिस्टर_session(mdsc, session);
		__wake_requests(mdsc, &session->s_रुकोing);
		mutex_unlock(&mdsc->mutex);

		mutex_lock(&session->s_mutex);
		__बंद_session(mdsc, session);
		अगर (session->s_state == CEPH_MDS_SESSION_CLOSING) अणु
			cleanup_session_requests(mdsc, session);
			हटाओ_session_caps(session);
		पूर्ण
		mutex_unlock(&session->s_mutex);
		ceph_put_mds_session(session);

		mutex_lock(&mdsc->mutex);
		kick_requests(mdsc, mds);
	पूर्ण
	__wake_requests(mdsc, &mdsc->रुकोing_क्रम_map);
	mutex_unlock(&mdsc->mutex);
पूर्ण

अटल व्योम ceph_mdsc_stop(काष्ठा ceph_mds_client *mdsc)
अणु
	करोut("stop\n");
	/*
	 * Make sure the delayed work stopped beक्रमe releasing
	 * the resources.
	 *
	 * Because the cancel_delayed_work_sync() will only
	 * guarantee that the work finishes executing. But the
	 * delayed work will re-arm itself again after that.
	 */
	flush_delayed_work(&mdsc->delayed_work);

	अगर (mdsc->mdsmap)
		ceph_mdsmap_destroy(mdsc->mdsmap);
	kमुक्त(mdsc->sessions);
	ceph_caps_finalize(mdsc);
	ceph_pool_perm_destroy(mdsc);
पूर्ण

व्योम ceph_mdsc_destroy(काष्ठा ceph_fs_client *fsc)
अणु
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
	करोut("mdsc_destroy %p\n", mdsc);

	अगर (!mdsc)
		वापस;

	/* flush out any connection work with references to us */
	ceph_msgr_flush();

	ceph_mdsc_stop(mdsc);

	ceph_metric_destroy(&mdsc->metric);

	flush_delayed_work(&mdsc->metric.delayed_work);
	fsc->mdsc = शून्य;
	kमुक्त(mdsc);
	करोut("mdsc_destroy %p done\n", mdsc);
पूर्ण

व्योम ceph_mdsc_handle_fsmap(काष्ठा ceph_mds_client *mdsc, काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_fs_client *fsc = mdsc->fsc;
	स्थिर अक्षर *mds_namespace = fsc->mount_options->mds_namespace;
	व्योम *p = msg->front.iov_base;
	व्योम *end = p + msg->front.iov_len;
	u32 epoch;
	u32 num_fs;
	u32 mount_fscid = (u32)-1;
	पूर्णांक err = -EINVAL;

	ceph_decode_need(&p, end, माप(u32), bad);
	epoch = ceph_decode_32(&p);

	करोut("handle_fsmap epoch %u\n", epoch);

	/* काष्ठा_v, काष्ठा_cv, map_len, epoch, legacy_client_fscid */
	ceph_decode_skip_n(&p, end, 2 + माप(u32) * 3, bad);

	ceph_decode_32_safe(&p, end, num_fs, bad);
	जबतक (num_fs-- > 0) अणु
		व्योम *info_p, *info_end;
		u32 info_len;
		u32 fscid, namelen;

		ceph_decode_need(&p, end, 2 + माप(u32), bad);
		p += 2;		// info_v, info_cv
		info_len = ceph_decode_32(&p);
		ceph_decode_need(&p, end, info_len, bad);
		info_p = p;
		info_end = p + info_len;
		p = info_end;

		ceph_decode_need(&info_p, info_end, माप(u32) * 2, bad);
		fscid = ceph_decode_32(&info_p);
		namelen = ceph_decode_32(&info_p);
		ceph_decode_need(&info_p, info_end, namelen, bad);

		अगर (mds_namespace &&
		    म_माप(mds_namespace) == namelen &&
		    !म_भेदन(mds_namespace, (अक्षर *)info_p, namelen)) अणु
			mount_fscid = fscid;
			अवरोध;
		पूर्ण
	पूर्ण

	ceph_monc_got_map(&fsc->client->monc, CEPH_SUB_FSMAP, epoch);
	अगर (mount_fscid != (u32)-1) अणु
		fsc->client->monc.fs_cluster_id = mount_fscid;
		ceph_monc_want_map(&fsc->client->monc, CEPH_SUB_MDSMAP,
				   0, true);
		ceph_monc_renew_subs(&fsc->client->monc);
	पूर्ण अन्यथा अणु
		err = -ENOENT;
		जाओ err_out;
	पूर्ण
	वापस;

bad:
	pr_err("error decoding fsmap\n");
err_out:
	mutex_lock(&mdsc->mutex);
	mdsc->mdsmap_err = err;
	__wake_requests(mdsc, &mdsc->रुकोing_क्रम_map);
	mutex_unlock(&mdsc->mutex);
पूर्ण

/*
 * handle mds map update.
 */
व्योम ceph_mdsc_handle_mdsmap(काष्ठा ceph_mds_client *mdsc, काष्ठा ceph_msg *msg)
अणु
	u32 epoch;
	u32 maplen;
	व्योम *p = msg->front.iov_base;
	व्योम *end = p + msg->front.iov_len;
	काष्ठा ceph_mdsmap *newmap, *oldmap;
	काष्ठा ceph_fsid fsid;
	पूर्णांक err = -EINVAL;

	ceph_decode_need(&p, end, माप(fsid)+2*माप(u32), bad);
	ceph_decode_copy(&p, &fsid, माप(fsid));
	अगर (ceph_check_fsid(mdsc->fsc->client, &fsid) < 0)
		वापस;
	epoch = ceph_decode_32(&p);
	maplen = ceph_decode_32(&p);
	करोut("handle_map epoch %u len %d\n", epoch, (पूर्णांक)maplen);

	/* करो we need it? */
	mutex_lock(&mdsc->mutex);
	अगर (mdsc->mdsmap && epoch <= mdsc->mdsmap->m_epoch) अणु
		करोut("handle_map epoch %u <= our %u\n",
		     epoch, mdsc->mdsmap->m_epoch);
		mutex_unlock(&mdsc->mutex);
		वापस;
	पूर्ण

	newmap = ceph_mdsmap_decode(&p, end, ceph_msgr2(mdsc->fsc->client));
	अगर (IS_ERR(newmap)) अणु
		err = PTR_ERR(newmap);
		जाओ bad_unlock;
	पूर्ण

	/* swap पूर्णांकo place */
	अगर (mdsc->mdsmap) अणु
		oldmap = mdsc->mdsmap;
		mdsc->mdsmap = newmap;
		check_new_map(mdsc, newmap, oldmap);
		ceph_mdsmap_destroy(oldmap);
	पूर्ण अन्यथा अणु
		mdsc->mdsmap = newmap;  /* first mds map */
	पूर्ण
	mdsc->fsc->max_file_size = min((loff_t)mdsc->mdsmap->m_max_file_size,
					MAX_LFS_खाताSIZE);

	__wake_requests(mdsc, &mdsc->रुकोing_क्रम_map);
	ceph_monc_got_map(&mdsc->fsc->client->monc, CEPH_SUB_MDSMAP,
			  mdsc->mdsmap->m_epoch);

	mutex_unlock(&mdsc->mutex);
	schedule_delayed(mdsc);
	वापस;

bad_unlock:
	mutex_unlock(&mdsc->mutex);
bad:
	pr_err("error decoding mdsmap %d\n", err);
	वापस;
पूर्ण

अटल काष्ठा ceph_connection *mds_get_con(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_mds_session *s = con->निजी;

	अगर (ceph_get_mds_session(s))
		वापस con;
	वापस शून्य;
पूर्ण

अटल व्योम mds_put_con(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_mds_session *s = con->निजी;

	ceph_put_mds_session(s);
पूर्ण

/*
 * अगर the client is unresponsive क्रम दीर्घ enough, the mds will समाप्त
 * the session entirely.
 */
अटल व्योम mds_peer_reset(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_mds_session *s = con->निजी;
	काष्ठा ceph_mds_client *mdsc = s->s_mdsc;

	pr_warn("mds%d closed our session\n", s->s_mds);
	send_mds_reconnect(mdsc, s);
पूर्ण

अटल व्योम mds_dispatch(काष्ठा ceph_connection *con, काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_mds_session *s = con->निजी;
	काष्ठा ceph_mds_client *mdsc = s->s_mdsc;
	पूर्णांक type = le16_to_cpu(msg->hdr.type);

	mutex_lock(&mdsc->mutex);
	अगर (__verअगरy_रेजिस्टरed_session(mdsc, s) < 0) अणु
		mutex_unlock(&mdsc->mutex);
		जाओ out;
	पूर्ण
	mutex_unlock(&mdsc->mutex);

	चयन (type) अणु
	हाल CEPH_MSG_MDS_MAP:
		ceph_mdsc_handle_mdsmap(mdsc, msg);
		अवरोध;
	हाल CEPH_MSG_FS_MAP_USER:
		ceph_mdsc_handle_fsmap(mdsc, msg);
		अवरोध;
	हाल CEPH_MSG_CLIENT_SESSION:
		handle_session(s, msg);
		अवरोध;
	हाल CEPH_MSG_CLIENT_REPLY:
		handle_reply(s, msg);
		अवरोध;
	हाल CEPH_MSG_CLIENT_REQUEST_FORWARD:
		handle_क्रमward(mdsc, s, msg);
		अवरोध;
	हाल CEPH_MSG_CLIENT_CAPS:
		ceph_handle_caps(s, msg);
		अवरोध;
	हाल CEPH_MSG_CLIENT_SNAP:
		ceph_handle_snap(mdsc, s, msg);
		अवरोध;
	हाल CEPH_MSG_CLIENT_LEASE:
		handle_lease(mdsc, s, msg);
		अवरोध;
	हाल CEPH_MSG_CLIENT_QUOTA:
		ceph_handle_quota(mdsc, s, msg);
		अवरोध;

	शेष:
		pr_err("received unknown message type %d %s\n", type,
		       ceph_msg_type_name(type));
	पूर्ण
out:
	ceph_msg_put(msg);
पूर्ण

/*
 * authentication
 */

/*
 * Note: वापसed poपूर्णांकer is the address of a काष्ठाure that's
 * managed separately.  Caller must *not* attempt to मुक्त it.
 */
अटल काष्ठा ceph_auth_handshake *
mds_get_authorizer(काष्ठा ceph_connection *con, पूर्णांक *proto, पूर्णांक क्रमce_new)
अणु
	काष्ठा ceph_mds_session *s = con->निजी;
	काष्ठा ceph_mds_client *mdsc = s->s_mdsc;
	काष्ठा ceph_auth_client *ac = mdsc->fsc->client->monc.auth;
	काष्ठा ceph_auth_handshake *auth = &s->s_auth;
	पूर्णांक ret;

	ret = __ceph_auth_get_authorizer(ac, auth, CEPH_ENTITY_TYPE_MDS,
					 क्रमce_new, proto, शून्य, शून्य);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस auth;
पूर्ण

अटल पूर्णांक mds_add_authorizer_challenge(काष्ठा ceph_connection *con,
				    व्योम *challenge_buf, पूर्णांक challenge_buf_len)
अणु
	काष्ठा ceph_mds_session *s = con->निजी;
	काष्ठा ceph_mds_client *mdsc = s->s_mdsc;
	काष्ठा ceph_auth_client *ac = mdsc->fsc->client->monc.auth;

	वापस ceph_auth_add_authorizer_challenge(ac, s->s_auth.authorizer,
					    challenge_buf, challenge_buf_len);
पूर्ण

अटल पूर्णांक mds_verअगरy_authorizer_reply(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_mds_session *s = con->निजी;
	काष्ठा ceph_mds_client *mdsc = s->s_mdsc;
	काष्ठा ceph_auth_client *ac = mdsc->fsc->client->monc.auth;
	काष्ठा ceph_auth_handshake *auth = &s->s_auth;

	वापस ceph_auth_verअगरy_authorizer_reply(ac, auth->authorizer,
		auth->authorizer_reply_buf, auth->authorizer_reply_buf_len,
		शून्य, शून्य, शून्य, शून्य);
पूर्ण

अटल पूर्णांक mds_invalidate_authorizer(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_mds_session *s = con->निजी;
	काष्ठा ceph_mds_client *mdsc = s->s_mdsc;
	काष्ठा ceph_auth_client *ac = mdsc->fsc->client->monc.auth;

	ceph_auth_invalidate_authorizer(ac, CEPH_ENTITY_TYPE_MDS);

	वापस ceph_monc_validate_auth(&mdsc->fsc->client->monc);
पूर्ण

अटल पूर्णांक mds_get_auth_request(काष्ठा ceph_connection *con,
				व्योम *buf, पूर्णांक *buf_len,
				व्योम **authorizer, पूर्णांक *authorizer_len)
अणु
	काष्ठा ceph_mds_session *s = con->निजी;
	काष्ठा ceph_auth_client *ac = s->s_mdsc->fsc->client->monc.auth;
	काष्ठा ceph_auth_handshake *auth = &s->s_auth;
	पूर्णांक ret;

	ret = ceph_auth_get_authorizer(ac, auth, CEPH_ENTITY_TYPE_MDS,
				       buf, buf_len);
	अगर (ret)
		वापस ret;

	*authorizer = auth->authorizer_buf;
	*authorizer_len = auth->authorizer_buf_len;
	वापस 0;
पूर्ण

अटल पूर्णांक mds_handle_auth_reply_more(काष्ठा ceph_connection *con,
				      व्योम *reply, पूर्णांक reply_len,
				      व्योम *buf, पूर्णांक *buf_len,
				      व्योम **authorizer, पूर्णांक *authorizer_len)
अणु
	काष्ठा ceph_mds_session *s = con->निजी;
	काष्ठा ceph_auth_client *ac = s->s_mdsc->fsc->client->monc.auth;
	काष्ठा ceph_auth_handshake *auth = &s->s_auth;
	पूर्णांक ret;

	ret = ceph_auth_handle_svc_reply_more(ac, auth, reply, reply_len,
					      buf, buf_len);
	अगर (ret)
		वापस ret;

	*authorizer = auth->authorizer_buf;
	*authorizer_len = auth->authorizer_buf_len;
	वापस 0;
पूर्ण

अटल पूर्णांक mds_handle_auth_करोne(काष्ठा ceph_connection *con,
				u64 global_id, व्योम *reply, पूर्णांक reply_len,
				u8 *session_key, पूर्णांक *session_key_len,
				u8 *con_secret, पूर्णांक *con_secret_len)
अणु
	काष्ठा ceph_mds_session *s = con->निजी;
	काष्ठा ceph_auth_client *ac = s->s_mdsc->fsc->client->monc.auth;
	काष्ठा ceph_auth_handshake *auth = &s->s_auth;

	वापस ceph_auth_handle_svc_reply_करोne(ac, auth, reply, reply_len,
					       session_key, session_key_len,
					       con_secret, con_secret_len);
पूर्ण

अटल पूर्णांक mds_handle_auth_bad_method(काष्ठा ceph_connection *con,
				      पूर्णांक used_proto, पूर्णांक result,
				      स्थिर पूर्णांक *allowed_protos, पूर्णांक proto_cnt,
				      स्थिर पूर्णांक *allowed_modes, पूर्णांक mode_cnt)
अणु
	काष्ठा ceph_mds_session *s = con->निजी;
	काष्ठा ceph_mon_client *monc = &s->s_mdsc->fsc->client->monc;
	पूर्णांक ret;

	अगर (ceph_auth_handle_bad_authorizer(monc->auth, CEPH_ENTITY_TYPE_MDS,
					    used_proto, result,
					    allowed_protos, proto_cnt,
					    allowed_modes, mode_cnt)) अणु
		ret = ceph_monc_validate_auth(monc);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस -EACCES;
पूर्ण

अटल काष्ठा ceph_msg *mds_alloc_msg(काष्ठा ceph_connection *con,
				काष्ठा ceph_msg_header *hdr, पूर्णांक *skip)
अणु
	काष्ठा ceph_msg *msg;
	पूर्णांक type = (पूर्णांक) le16_to_cpu(hdr->type);
	पूर्णांक front_len = (पूर्णांक) le32_to_cpu(hdr->front_len);

	अगर (con->in_msg)
		वापस con->in_msg;

	*skip = 0;
	msg = ceph_msg_new(type, front_len, GFP_NOFS, false);
	अगर (!msg) अणु
		pr_err("unable to allocate msg type %d len %d\n",
		       type, front_len);
		वापस शून्य;
	पूर्ण

	वापस msg;
पूर्ण

अटल पूर्णांक mds_sign_message(काष्ठा ceph_msg *msg)
अणु
       काष्ठा ceph_mds_session *s = msg->con->निजी;
       काष्ठा ceph_auth_handshake *auth = &s->s_auth;

       वापस ceph_auth_sign_message(auth, msg);
पूर्ण

अटल पूर्णांक mds_check_message_signature(काष्ठा ceph_msg *msg)
अणु
       काष्ठा ceph_mds_session *s = msg->con->निजी;
       काष्ठा ceph_auth_handshake *auth = &s->s_auth;

       वापस ceph_auth_check_message_signature(auth, msg);
पूर्ण

अटल स्थिर काष्ठा ceph_connection_operations mds_con_ops = अणु
	.get = mds_get_con,
	.put = mds_put_con,
	.alloc_msg = mds_alloc_msg,
	.dispatch = mds_dispatch,
	.peer_reset = mds_peer_reset,
	.get_authorizer = mds_get_authorizer,
	.add_authorizer_challenge = mds_add_authorizer_challenge,
	.verअगरy_authorizer_reply = mds_verअगरy_authorizer_reply,
	.invalidate_authorizer = mds_invalidate_authorizer,
	.sign_message = mds_sign_message,
	.check_message_signature = mds_check_message_signature,
	.get_auth_request = mds_get_auth_request,
	.handle_auth_reply_more = mds_handle_auth_reply_more,
	.handle_auth_करोne = mds_handle_auth_करोne,
	.handle_auth_bad_method = mds_handle_auth_bad_method,
पूर्ण;

/* eof */
