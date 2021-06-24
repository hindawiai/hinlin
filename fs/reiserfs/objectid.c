<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */

#समावेश <linux/माला.स>
#समावेश <linux/समय.स>
#समावेश <linux/uuid.h>
#समावेश "reiserfs.h"

/* find where objectid map starts */
#घोषणा objectid_map(s,rs) (old_क्रमmat_only (s) ? \
                         (__le32 *)((काष्ठा reiserfs_super_block_v1 *)(rs) + 1) :\
			 (__le32 *)((rs) + 1))

#अगर_घोषित CONFIG_REISERFS_CHECK

अटल व्योम check_objectid_map(काष्ठा super_block *s, __le32 * map)
अणु
	अगर (le32_to_cpu(map[0]) != 1)
		reiserfs_panic(s, "vs-15010", "map corrupted: %lx",
			       (दीर्घ अचिन्हित पूर्णांक)le32_to_cpu(map[0]));

	/* FIXME: add something अन्यथा here */
पूर्ण

#अन्यथा
अटल व्योम check_objectid_map(काष्ठा super_block *s, __le32 * map)
अणु;
पूर्ण
#पूर्ण_अगर

/*
 * When we allocate objectids we allocate the first unused objectid.
 * Each sequence of objectids in use (the odd sequences) is followed
 * by a sequence of objectids not in use (the even sequences).  We
 * only need to record the last objectid in each of these sequences
 * (both the odd and even sequences) in order to fully define the
 * boundaries of the sequences.  A consequence of allocating the first
 * objectid not in use is that under most conditions this scheme is
 * extremely compact.  The exception is immediately after a sequence
 * of operations which deletes a large number of objects of
 * non-sequential objectids, and even then it will become compact
 * again as soon as more objects are created.  Note that many
 * पूर्णांकeresting optimizations of layout could result from complicating
 * objectid assignment, but we have deferred making them क्रम now.
 */

/* get unique object identअगरier */
__u32 reiserfs_get_unused_objectid(काष्ठा reiserfs_transaction_handle *th)
अणु
	काष्ठा super_block *s = th->t_super;
	काष्ठा reiserfs_super_block *rs = SB_DISK_SUPER_BLOCK(s);
	__le32 *map = objectid_map(s, rs);
	__u32 unused_objectid;

	BUG_ON(!th->t_trans_id);

	check_objectid_map(s, map);

	reiserfs_prepare_क्रम_journal(s, SB_BUFFER_WITH_SB(s), 1);
	/* comment needed -Hans */
	unused_objectid = le32_to_cpu(map[1]);
	अगर (unused_objectid == U32_MAX) अणु
		reiserfs_warning(s, "reiserfs-15100", "no more object ids");
		reiserfs_restore_prepared_buffer(s, SB_BUFFER_WITH_SB(s));
		वापस 0;
	पूर्ण

	/*
	 * This incrementation allocates the first unused objectid. That
	 * is to say, the first entry on the objectid map is the first
	 * unused objectid, and by incrementing it we use it.  See below
	 * where we check to see अगर we eliminated a sequence of unused
	 * objectids....
	 */
	map[1] = cpu_to_le32(unused_objectid + 1);

	/*
	 * Now we check to see अगर we eliminated the last reमुख्यing member of
	 * the first even sequence (and can eliminate the sequence by
	 * eliminating its last objectid from oids), and can collapse the
	 * first two odd sequences पूर्णांकo one sequence.  If so, then the net
	 * result is to eliminate a pair of objectids from oids.  We करो this
	 * by shअगरting the entire map to the left.
	 */
	अगर (sb_oid_cursize(rs) > 2 && map[1] == map[2]) अणु
		स_हटाओ(map + 1, map + 3,
			(sb_oid_cursize(rs) - 3) * माप(__u32));
		set_sb_oid_cursize(rs, sb_oid_cursize(rs) - 2);
	पूर्ण

	journal_mark_dirty(th, SB_BUFFER_WITH_SB(s));
	वापस unused_objectid;
पूर्ण

/* makes object identअगरier unused */
व्योम reiserfs_release_objectid(काष्ठा reiserfs_transaction_handle *th,
			       __u32 objectid_to_release)
अणु
	काष्ठा super_block *s = th->t_super;
	काष्ठा reiserfs_super_block *rs = SB_DISK_SUPER_BLOCK(s);
	__le32 *map = objectid_map(s, rs);
	पूर्णांक i = 0;

	BUG_ON(!th->t_trans_id);
	/*वापस; */
	check_objectid_map(s, map);

	reiserfs_prepare_क्रम_journal(s, SB_BUFFER_WITH_SB(s), 1);
	journal_mark_dirty(th, SB_BUFFER_WITH_SB(s));

	/*
	 * start at the beginning of the objectid map (i = 0) and go to
	 * the end of it (i = disk_sb->s_oid_cursize).  Linear search is
	 * what we use, though it is possible that binary search would be
	 * more efficient after perक्रमming lots of deletions (which is
	 * when oids is large.)  We only check even i's.
	 */
	जबतक (i < sb_oid_cursize(rs)) अणु
		अगर (objectid_to_release == le32_to_cpu(map[i])) अणु
			/* This incrementation unallocates the objectid. */
			le32_add_cpu(&map[i], 1);

			/*
			 * Did we unallocate the last member of an
			 * odd sequence, and can shrink oids?
			 */
			अगर (map[i] == map[i + 1]) अणु
				/* shrink objectid map */
				स_हटाओ(map + i, map + i + 2,
					(sb_oid_cursize(rs) - i -
					 2) * माप(__u32));
				set_sb_oid_cursize(rs, sb_oid_cursize(rs) - 2);

				RFALSE(sb_oid_cursize(rs) < 2 ||
				       sb_oid_cursize(rs) > sb_oid_maxsize(rs),
				       "vs-15005: objectid map corrupted cur_size == %d (max == %d)",
				       sb_oid_cursize(rs), sb_oid_maxsize(rs));
			पूर्ण
			वापस;
		पूर्ण

		अगर (objectid_to_release > le32_to_cpu(map[i]) &&
		    objectid_to_release < le32_to_cpu(map[i + 1])) अणु
			/* size of objectid map is not changed */
			अगर (objectid_to_release + 1 == le32_to_cpu(map[i + 1])) अणु
				le32_add_cpu(&map[i + 1], -1);
				वापस;
			पूर्ण

			/*
			 * JDM comparing two little-endian values क्रम
			 * equality -- safe
			 */
			/*
			 * objectid map must be expanded, but
			 * there is no space
			 */
			अगर (sb_oid_cursize(rs) == sb_oid_maxsize(rs)) अणु
				PROC_INFO_INC(s, leaked_oid);
				वापस;
			पूर्ण

			/* expand the objectid map */
			स_हटाओ(map + i + 3, map + i + 1,
				(sb_oid_cursize(rs) - i - 1) * माप(__u32));
			map[i + 1] = cpu_to_le32(objectid_to_release);
			map[i + 2] = cpu_to_le32(objectid_to_release + 1);
			set_sb_oid_cursize(rs, sb_oid_cursize(rs) + 2);
			वापस;
		पूर्ण
		i += 2;
	पूर्ण

	reiserfs_error(s, "vs-15011", "tried to free free object id (%lu)",
		       (दीर्घ अचिन्हित)objectid_to_release);
पूर्ण

पूर्णांक reiserfs_convert_objectid_map_v1(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_super_block *disk_sb = SB_DISK_SUPER_BLOCK(s);
	पूर्णांक cur_size = sb_oid_cursize(disk_sb);
	पूर्णांक new_size = (s->s_blocksize - SB_SIZE) / माप(__u32) / 2 * 2;
	पूर्णांक old_max = sb_oid_maxsize(disk_sb);
	काष्ठा reiserfs_super_block_v1 *disk_sb_v1;
	__le32 *objectid_map;
	पूर्णांक i;

	disk_sb_v1 =
	    (काष्ठा reiserfs_super_block_v1 *)(SB_BUFFER_WITH_SB(s)->b_data);
	objectid_map = (__le32 *) (disk_sb_v1 + 1);

	अगर (cur_size > new_size) अणु
		/*
		 * mark everyone used that was listed as मुक्त at
		 * the end of the objectid map
		 */
		objectid_map[new_size - 1] = objectid_map[cur_size - 1];
		set_sb_oid_cursize(disk_sb, new_size);
	पूर्ण
	/* move the smaller objectid map past the end of the new super */
	क्रम (i = new_size - 1; i >= 0; i--) अणु
		objectid_map[i + (old_max - new_size)] = objectid_map[i];
	पूर्ण

	/* set the max size so we करोn't overflow later */
	set_sb_oid_maxsize(disk_sb, new_size);

	/* Zero out label and generate अक्रमom UUID */
	स_रखो(disk_sb->s_label, 0, माप(disk_sb->s_label));
	generate_अक्रमom_uuid(disk_sb->s_uuid);

	/* finally, zero out the unused chunk of the new super */
	स_रखो(disk_sb->s_unused, 0, माप(disk_sb->s_unused));
	वापस 0;
पूर्ण
