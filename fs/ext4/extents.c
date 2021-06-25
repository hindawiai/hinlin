<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2003-2006, Cluster File Systems, Inc, info@clusterfs.com
 * Written by Alex Tomas <alex@clusterfs.com>
 *
 * Architecture independence:
 *   Copyright (c) 2005, Bull S.A.
 *   Written by Pierre Peअगरfer <pierre.peअगरfer@bull.net>
 */

/*
 * Extents support क्रम EXT4
 *
 * TODO:
 *   - ext4*_error() should be used in some situations
 *   - analyze all BUG()/BUG_ON(), use -EIO where appropriate
 *   - smart tree reduction
 */

#समावेश <linux/fs.h>
#समावेश <linux/समय.स>
#समावेश <linux/jbd2.h>
#समावेश <linux/highuid.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fiemap.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/iomap.h>
#समावेश "ext4_jbd2.h"
#समावेश "ext4_extents.h"
#समावेश "xattr.h"

#समावेश <trace/events/ext4.h>

/*
 * used by extent splitting.
 */
#घोषणा EXT4_EXT_MAY_ZEROOUT	0x1  /* safe to zeroout अगर split fails \
					due to ENOSPC */
#घोषणा EXT4_EXT_MARK_UNWRIT1	0x2  /* mark first half unwritten */
#घोषणा EXT4_EXT_MARK_UNWRIT2	0x4  /* mark second half unwritten */

#घोषणा EXT4_EXT_DATA_VALID1	0x8  /* first half contains valid data */
#घोषणा EXT4_EXT_DATA_VALID2	0x10 /* second half contains valid data */

अटल __le32 ext4_extent_block_csum(काष्ठा inode *inode,
				     काष्ठा ext4_extent_header *eh)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	__u32 csum;

	csum = ext4_chksum(sbi, ei->i_csum_seed, (__u8 *)eh,
			   EXT4_EXTENT_TAIL_OFFSET(eh));
	वापस cpu_to_le32(csum);
पूर्ण

अटल पूर्णांक ext4_extent_block_csum_verअगरy(काष्ठा inode *inode,
					 काष्ठा ext4_extent_header *eh)
अणु
	काष्ठा ext4_extent_tail *et;

	अगर (!ext4_has_metadata_csum(inode->i_sb))
		वापस 1;

	et = find_ext4_extent_tail(eh);
	अगर (et->et_checksum != ext4_extent_block_csum(inode, eh))
		वापस 0;
	वापस 1;
पूर्ण

अटल व्योम ext4_extent_block_csum_set(काष्ठा inode *inode,
				       काष्ठा ext4_extent_header *eh)
अणु
	काष्ठा ext4_extent_tail *et;

	अगर (!ext4_has_metadata_csum(inode->i_sb))
		वापस;

	et = find_ext4_extent_tail(eh);
	et->et_checksum = ext4_extent_block_csum(inode, eh);
पूर्ण

अटल पूर्णांक ext4_split_extent_at(handle_t *handle,
			     काष्ठा inode *inode,
			     काष्ठा ext4_ext_path **ppath,
			     ext4_lblk_t split,
			     पूर्णांक split_flag,
			     पूर्णांक flags);

अटल पूर्णांक ext4_ext_trunc_restart_fn(काष्ठा inode *inode, पूर्णांक *dropped)
अणु
	/*
	 * Drop i_data_sem to aव्योम deadlock with ext4_map_blocks.  At this
	 * moment, get_block can be called only क्रम blocks inside i_size since
	 * page cache has been alपढ़ोy dropped and ग_लिखोs are blocked by
	 * i_mutex. So we can safely drop the i_data_sem here.
	 */
	BUG_ON(EXT4_JOURNAL(inode) == शून्य);
	ext4_discard_pपुनः_स्मृतिations(inode, 0);
	up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	*dropped = 1;
	वापस 0;
पूर्ण

/*
 * Make sure 'handle' has at least 'check_cred' credits. If not, restart
 * transaction with 'restart_cred' credits. The function drops i_data_sem
 * when restarting transaction and माला_लो it after transaction is restarted.
 *
 * The function वापसs 0 on success, 1 अगर transaction had to be restarted,
 * and < 0 in हाल of fatal error.
 */
पूर्णांक ext4_datasem_ensure_credits(handle_t *handle, काष्ठा inode *inode,
				पूर्णांक check_cred, पूर्णांक restart_cred,
				पूर्णांक revoke_cred)
अणु
	पूर्णांक ret;
	पूर्णांक dropped = 0;

	ret = ext4_journal_ensure_credits_fn(handle, check_cred, restart_cred,
		revoke_cred, ext4_ext_trunc_restart_fn(inode, &dropped));
	अगर (dropped)
		करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	वापस ret;
पूर्ण

/*
 * could वापस:
 *  - EROFS
 *  - ENOMEM
 */
अटल पूर्णांक ext4_ext_get_access(handle_t *handle, काष्ठा inode *inode,
				काष्ठा ext4_ext_path *path)
अणु
	अगर (path->p_bh) अणु
		/* path poपूर्णांकs to block */
		BUFFER_TRACE(path->p_bh, "get_write_access");
		वापस ext4_journal_get_ग_लिखो_access(handle, path->p_bh);
	पूर्ण
	/* path poपूर्णांकs to leaf/index in inode body */
	/* we use in-core data, no need to protect them */
	वापस 0;
पूर्ण

/*
 * could वापस:
 *  - EROFS
 *  - ENOMEM
 *  - EIO
 */
अटल पूर्णांक __ext4_ext_dirty(स्थिर अक्षर *where, अचिन्हित पूर्णांक line,
			    handle_t *handle, काष्ठा inode *inode,
			    काष्ठा ext4_ext_path *path)
अणु
	पूर्णांक err;

	WARN_ON(!rwsem_is_locked(&EXT4_I(inode)->i_data_sem));
	अगर (path->p_bh) अणु
		ext4_extent_block_csum_set(inode, ext_block_hdr(path->p_bh));
		/* path poपूर्णांकs to block */
		err = __ext4_handle_dirty_metadata(where, line, handle,
						   inode, path->p_bh);
	पूर्ण अन्यथा अणु
		/* path poपूर्णांकs to leaf/index in inode body */
		err = ext4_mark_inode_dirty(handle, inode);
	पूर्ण
	वापस err;
पूर्ण

#घोषणा ext4_ext_dirty(handle, inode, path) \
		__ext4_ext_dirty(__func__, __LINE__, (handle), (inode), (path))

अटल ext4_fsblk_t ext4_ext_find_goal(काष्ठा inode *inode,
			      काष्ठा ext4_ext_path *path,
			      ext4_lblk_t block)
अणु
	अगर (path) अणु
		पूर्णांक depth = path->p_depth;
		काष्ठा ext4_extent *ex;

		/*
		 * Try to predict block placement assuming that we are
		 * filling in a file which will eventually be
		 * non-sparse --- i.e., in the हाल of libbfd writing
		 * an ELF object sections out-of-order but in a way
		 * the eventually results in a contiguous object or
		 * executable file, or some database extending a table
		 * space file.  However, this is actually somewhat
		 * non-ideal अगर we are writing a sparse file such as
		 * qemu or KVM writing a raw image file that is going
		 * to stay fairly sparse, since it will end up
		 * fragmenting the file प्रणाली's मुक्त space.  Maybe we
		 * should have some hueristics or some way to allow
		 * userspace to pass a hपूर्णांक to file प्रणाली,
		 * especially अगर the latter हाल turns out to be
		 * common.
		 */
		ex = path[depth].p_ext;
		अगर (ex) अणु
			ext4_fsblk_t ext_pblk = ext4_ext_pblock(ex);
			ext4_lblk_t ext_block = le32_to_cpu(ex->ee_block);

			अगर (block > ext_block)
				वापस ext_pblk + (block - ext_block);
			अन्यथा
				वापस ext_pblk - (ext_block - block);
		पूर्ण

		/* it looks like index is empty;
		 * try to find starting block from index itself */
		अगर (path[depth].p_bh)
			वापस path[depth].p_bh->b_blocknr;
	पूर्ण

	/* OK. use inode's group */
	वापस ext4_inode_to_goal_block(inode);
पूर्ण

/*
 * Allocation क्रम a meta data block
 */
अटल ext4_fsblk_t
ext4_ext_new_meta_block(handle_t *handle, काष्ठा inode *inode,
			काष्ठा ext4_ext_path *path,
			काष्ठा ext4_extent *ex, पूर्णांक *err, अचिन्हित पूर्णांक flags)
अणु
	ext4_fsblk_t goal, newblock;

	goal = ext4_ext_find_goal(inode, path, le32_to_cpu(ex->ee_block));
	newblock = ext4_new_meta_blocks(handle, inode, goal, flags,
					शून्य, err);
	वापस newblock;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_ext_space_block(काष्ठा inode *inode, पूर्णांक check)
अणु
	पूर्णांक size;

	size = (inode->i_sb->s_blocksize - माप(काष्ठा ext4_extent_header))
			/ माप(काष्ठा ext4_extent);
#अगर_घोषित AGGRESSIVE_TEST
	अगर (!check && size > 6)
		size = 6;
#पूर्ण_अगर
	वापस size;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_ext_space_block_idx(काष्ठा inode *inode, पूर्णांक check)
अणु
	पूर्णांक size;

	size = (inode->i_sb->s_blocksize - माप(काष्ठा ext4_extent_header))
			/ माप(काष्ठा ext4_extent_idx);
#अगर_घोषित AGGRESSIVE_TEST
	अगर (!check && size > 5)
		size = 5;
#पूर्ण_अगर
	वापस size;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_ext_space_root(काष्ठा inode *inode, पूर्णांक check)
अणु
	पूर्णांक size;

	size = माप(EXT4_I(inode)->i_data);
	size -= माप(काष्ठा ext4_extent_header);
	size /= माप(काष्ठा ext4_extent);
#अगर_घोषित AGGRESSIVE_TEST
	अगर (!check && size > 3)
		size = 3;
#पूर्ण_अगर
	वापस size;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_ext_space_root_idx(काष्ठा inode *inode, पूर्णांक check)
अणु
	पूर्णांक size;

	size = माप(EXT4_I(inode)->i_data);
	size -= माप(काष्ठा ext4_extent_header);
	size /= माप(काष्ठा ext4_extent_idx);
#अगर_घोषित AGGRESSIVE_TEST
	अगर (!check && size > 4)
		size = 4;
#पूर्ण_अगर
	वापस size;
पूर्ण

अटल अंतरभूत पूर्णांक
ext4_क्रमce_split_extent_at(handle_t *handle, काष्ठा inode *inode,
			   काष्ठा ext4_ext_path **ppath, ext4_lblk_t lblk,
			   पूर्णांक nofail)
अणु
	काष्ठा ext4_ext_path *path = *ppath;
	पूर्णांक unwritten = ext4_ext_is_unwritten(path[path->p_depth].p_ext);
	पूर्णांक flags = EXT4_EX_NOCACHE | EXT4_GET_BLOCKS_PRE_IO;

	अगर (nofail)
		flags |= EXT4_GET_BLOCKS_METADATA_NOFAIL | EXT4_EX_NOFAIL;

	वापस ext4_split_extent_at(handle, inode, ppath, lblk, unwritten ?
			EXT4_EXT_MARK_UNWRIT1|EXT4_EXT_MARK_UNWRIT2 : 0,
			flags);
पूर्ण

अटल पूर्णांक
ext4_ext_max_entries(काष्ठा inode *inode, पूर्णांक depth)
अणु
	पूर्णांक max;

	अगर (depth == ext_depth(inode)) अणु
		अगर (depth == 0)
			max = ext4_ext_space_root(inode, 1);
		अन्यथा
			max = ext4_ext_space_root_idx(inode, 1);
	पूर्ण अन्यथा अणु
		अगर (depth == 0)
			max = ext4_ext_space_block(inode, 1);
		अन्यथा
			max = ext4_ext_space_block_idx(inode, 1);
	पूर्ण

	वापस max;
पूर्ण

अटल पूर्णांक ext4_valid_extent(काष्ठा inode *inode, काष्ठा ext4_extent *ext)
अणु
	ext4_fsblk_t block = ext4_ext_pblock(ext);
	पूर्णांक len = ext4_ext_get_actual_len(ext);
	ext4_lblk_t lblock = le32_to_cpu(ext->ee_block);

	/*
	 * We allow neither:
	 *  - zero length
	 *  - overflow/wrap-around
	 */
	अगर (lblock + len <= lblock)
		वापस 0;
	वापस ext4_inode_block_valid(inode, block, len);
पूर्ण

अटल पूर्णांक ext4_valid_extent_idx(काष्ठा inode *inode,
				काष्ठा ext4_extent_idx *ext_idx)
अणु
	ext4_fsblk_t block = ext4_idx_pblock(ext_idx);

	वापस ext4_inode_block_valid(inode, block, 1);
पूर्ण

अटल पूर्णांक ext4_valid_extent_entries(काष्ठा inode *inode,
				     काष्ठा ext4_extent_header *eh,
				     ext4_fsblk_t *pblk, पूर्णांक depth)
अणु
	अचिन्हित लघु entries;
	अगर (eh->eh_entries == 0)
		वापस 1;

	entries = le16_to_cpu(eh->eh_entries);

	अगर (depth == 0) अणु
		/* leaf entries */
		काष्ठा ext4_extent *ext = EXT_FIRST_EXTENT(eh);
		ext4_lblk_t lblock = 0;
		ext4_lblk_t prev = 0;
		पूर्णांक len = 0;
		जबतक (entries) अणु
			अगर (!ext4_valid_extent(inode, ext))
				वापस 0;

			/* Check क्रम overlapping extents */
			lblock = le32_to_cpu(ext->ee_block);
			len = ext4_ext_get_actual_len(ext);
			अगर ((lblock <= prev) && prev) अणु
				*pblk = ext4_ext_pblock(ext);
				वापस 0;
			पूर्ण
			ext++;
			entries--;
			prev = lblock + len - 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा ext4_extent_idx *ext_idx = EXT_FIRST_INDEX(eh);
		जबतक (entries) अणु
			अगर (!ext4_valid_extent_idx(inode, ext_idx))
				वापस 0;
			ext_idx++;
			entries--;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक __ext4_ext_check(स्थिर अक्षर *function, अचिन्हित पूर्णांक line,
			    काष्ठा inode *inode, काष्ठा ext4_extent_header *eh,
			    पूर्णांक depth, ext4_fsblk_t pblk)
अणु
	स्थिर अक्षर *error_msg;
	पूर्णांक max = 0, err = -EFSCORRUPTED;

	अगर (unlikely(eh->eh_magic != EXT4_EXT_MAGIC)) अणु
		error_msg = "invalid magic";
		जाओ corrupted;
	पूर्ण
	अगर (unlikely(le16_to_cpu(eh->eh_depth) != depth)) अणु
		error_msg = "unexpected eh_depth";
		जाओ corrupted;
	पूर्ण
	अगर (unlikely(eh->eh_max == 0)) अणु
		error_msg = "invalid eh_max";
		जाओ corrupted;
	पूर्ण
	max = ext4_ext_max_entries(inode, depth);
	अगर (unlikely(le16_to_cpu(eh->eh_max) > max)) अणु
		error_msg = "too large eh_max";
		जाओ corrupted;
	पूर्ण
	अगर (unlikely(le16_to_cpu(eh->eh_entries) > le16_to_cpu(eh->eh_max))) अणु
		error_msg = "invalid eh_entries";
		जाओ corrupted;
	पूर्ण
	अगर (!ext4_valid_extent_entries(inode, eh, &pblk, depth)) अणु
		error_msg = "invalid extent entries";
		जाओ corrupted;
	पूर्ण
	अगर (unlikely(depth > 32)) अणु
		error_msg = "too large eh_depth";
		जाओ corrupted;
	पूर्ण
	/* Verअगरy checksum on non-root extent tree nodes */
	अगर (ext_depth(inode) != depth &&
	    !ext4_extent_block_csum_verअगरy(inode, eh)) अणु
		error_msg = "extent tree corrupted";
		err = -EFSBADCRC;
		जाओ corrupted;
	पूर्ण
	वापस 0;

corrupted:
	ext4_error_inode_err(inode, function, line, 0, -err,
			     "pblk %llu bad header/extent: %s - magic %x, "
			     "entries %u, max %u(%u), depth %u(%u)",
			     (अचिन्हित दीर्घ दीर्घ) pblk, error_msg,
			     le16_to_cpu(eh->eh_magic),
			     le16_to_cpu(eh->eh_entries),
			     le16_to_cpu(eh->eh_max),
			     max, le16_to_cpu(eh->eh_depth), depth);
	वापस err;
पूर्ण

#घोषणा ext4_ext_check(inode, eh, depth, pblk)			\
	__ext4_ext_check(__func__, __LINE__, (inode), (eh), (depth), (pblk))

पूर्णांक ext4_ext_check_inode(काष्ठा inode *inode)
अणु
	वापस ext4_ext_check(inode, ext_inode_hdr(inode), ext_depth(inode), 0);
पूर्ण

अटल व्योम ext4_cache_extents(काष्ठा inode *inode,
			       काष्ठा ext4_extent_header *eh)
अणु
	काष्ठा ext4_extent *ex = EXT_FIRST_EXTENT(eh);
	ext4_lblk_t prev = 0;
	पूर्णांक i;

	क्रम (i = le16_to_cpu(eh->eh_entries); i > 0; i--, ex++) अणु
		अचिन्हित पूर्णांक status = EXTENT_STATUS_WRITTEN;
		ext4_lblk_t lblk = le32_to_cpu(ex->ee_block);
		पूर्णांक len = ext4_ext_get_actual_len(ex);

		अगर (prev && (prev != lblk))
			ext4_es_cache_extent(inode, prev, lblk - prev, ~0,
					     EXTENT_STATUS_HOLE);

		अगर (ext4_ext_is_unwritten(ex))
			status = EXTENT_STATUS_UNWRITTEN;
		ext4_es_cache_extent(inode, lblk, len,
				     ext4_ext_pblock(ex), status);
		prev = lblk + len;
	पूर्ण
पूर्ण

अटल काष्ठा buffer_head *
__पढ़ो_extent_tree_block(स्थिर अक्षर *function, अचिन्हित पूर्णांक line,
			 काष्ठा inode *inode, ext4_fsblk_t pblk, पूर्णांक depth,
			 पूर्णांक flags)
अणु
	काष्ठा buffer_head		*bh;
	पूर्णांक				err;
	gfp_t				gfp_flags = __GFP_MOVABLE | GFP_NOFS;

	अगर (flags & EXT4_EX_NOFAIL)
		gfp_flags |= __GFP_NOFAIL;

	bh = sb_getblk_gfp(inode->i_sb, pblk, gfp_flags);
	अगर (unlikely(!bh))
		वापस ERR_PTR(-ENOMEM);

	अगर (!bh_uptodate_or_lock(bh)) अणु
		trace_ext4_ext_load_extent(inode, pblk, _RET_IP_);
		err = ext4_पढ़ो_bh(bh, 0, शून्य);
		अगर (err < 0)
			जाओ errout;
	पूर्ण
	अगर (buffer_verअगरied(bh) && !(flags & EXT4_EX_FORCE_CACHE))
		वापस bh;
	err = __ext4_ext_check(function, line, inode,
			       ext_block_hdr(bh), depth, pblk);
	अगर (err)
		जाओ errout;
	set_buffer_verअगरied(bh);
	/*
	 * If this is a leaf block, cache all of its entries
	 */
	अगर (!(flags & EXT4_EX_NOCACHE) && depth == 0) अणु
		काष्ठा ext4_extent_header *eh = ext_block_hdr(bh);
		ext4_cache_extents(inode, eh);
	पूर्ण
	वापस bh;
errout:
	put_bh(bh);
	वापस ERR_PTR(err);

पूर्ण

#घोषणा पढ़ो_extent_tree_block(inode, pblk, depth, flags)		\
	__पढ़ो_extent_tree_block(__func__, __LINE__, (inode), (pblk),   \
				 (depth), (flags))

/*
 * This function is called to cache a file's extent inक्रमmation in the
 * extent status tree
 */
पूर्णांक ext4_ext_precache(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा ext4_ext_path *path = शून्य;
	काष्ठा buffer_head *bh;
	पूर्णांक i = 0, depth, ret = 0;

	अगर (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		वापस 0;	/* not an extent-mapped inode */

	करोwn_पढ़ो(&ei->i_data_sem);
	depth = ext_depth(inode);

	/* Don't cache anything अगर there are no बाह्यal extent blocks */
	अगर (!depth) अणु
		up_पढ़ो(&ei->i_data_sem);
		वापस ret;
	पूर्ण

	path = kसुस्मृति(depth + 1, माप(काष्ठा ext4_ext_path),
		       GFP_NOFS);
	अगर (path == शून्य) अणु
		up_पढ़ो(&ei->i_data_sem);
		वापस -ENOMEM;
	पूर्ण

	path[0].p_hdr = ext_inode_hdr(inode);
	ret = ext4_ext_check(inode, path[0].p_hdr, depth, 0);
	अगर (ret)
		जाओ out;
	path[0].p_idx = EXT_FIRST_INDEX(path[0].p_hdr);
	जबतक (i >= 0) अणु
		/*
		 * If this is a leaf block or we've reached the end of
		 * the index block, go up
		 */
		अगर ((i == depth) ||
		    path[i].p_idx > EXT_LAST_INDEX(path[i].p_hdr)) अणु
			brअन्यथा(path[i].p_bh);
			path[i].p_bh = शून्य;
			i--;
			जारी;
		पूर्ण
		bh = पढ़ो_extent_tree_block(inode,
					    ext4_idx_pblock(path[i].p_idx++),
					    depth - i - 1,
					    EXT4_EX_FORCE_CACHE);
		अगर (IS_ERR(bh)) अणु
			ret = PTR_ERR(bh);
			अवरोध;
		पूर्ण
		i++;
		path[i].p_bh = bh;
		path[i].p_hdr = ext_block_hdr(bh);
		path[i].p_idx = EXT_FIRST_INDEX(path[i].p_hdr);
	पूर्ण
	ext4_set_inode_state(inode, EXT4_STATE_EXT_PRECACHED);
out:
	up_पढ़ो(&ei->i_data_sem);
	ext4_ext_drop_refs(path);
	kमुक्त(path);
	वापस ret;
पूर्ण

#अगर_घोषित EXT_DEBUG
अटल व्योम ext4_ext_show_path(काष्ठा inode *inode, काष्ठा ext4_ext_path *path)
अणु
	पूर्णांक k, l = path->p_depth;

	ext_debug(inode, "path:");
	क्रम (k = 0; k <= l; k++, path++) अणु
		अगर (path->p_idx) अणु
			ext_debug(inode, "  %d->%llu",
				  le32_to_cpu(path->p_idx->ei_block),
				  ext4_idx_pblock(path->p_idx));
		पूर्ण अन्यथा अगर (path->p_ext) अणु
			ext_debug(inode, "  %d:[%d]%d:%llu ",
				  le32_to_cpu(path->p_ext->ee_block),
				  ext4_ext_is_unwritten(path->p_ext),
				  ext4_ext_get_actual_len(path->p_ext),
				  ext4_ext_pblock(path->p_ext));
		पूर्ण अन्यथा
			ext_debug(inode, "  []");
	पूर्ण
	ext_debug(inode, "\n");
पूर्ण

अटल व्योम ext4_ext_show_leaf(काष्ठा inode *inode, काष्ठा ext4_ext_path *path)
अणु
	पूर्णांक depth = ext_depth(inode);
	काष्ठा ext4_extent_header *eh;
	काष्ठा ext4_extent *ex;
	पूर्णांक i;

	अगर (!path)
		वापस;

	eh = path[depth].p_hdr;
	ex = EXT_FIRST_EXTENT(eh);

	ext_debug(inode, "Displaying leaf extents\n");

	क्रम (i = 0; i < le16_to_cpu(eh->eh_entries); i++, ex++) अणु
		ext_debug(inode, "%d:[%d]%d:%llu ", le32_to_cpu(ex->ee_block),
			  ext4_ext_is_unwritten(ex),
			  ext4_ext_get_actual_len(ex), ext4_ext_pblock(ex));
	पूर्ण
	ext_debug(inode, "\n");
पूर्ण

अटल व्योम ext4_ext_show_move(काष्ठा inode *inode, काष्ठा ext4_ext_path *path,
			ext4_fsblk_t newblock, पूर्णांक level)
अणु
	पूर्णांक depth = ext_depth(inode);
	काष्ठा ext4_extent *ex;

	अगर (depth != level) अणु
		काष्ठा ext4_extent_idx *idx;
		idx = path[level].p_idx;
		जबतक (idx <= EXT_MAX_INDEX(path[level].p_hdr)) अणु
			ext_debug(inode, "%d: move %d:%llu in new index %llu\n",
				  level, le32_to_cpu(idx->ei_block),
				  ext4_idx_pblock(idx), newblock);
			idx++;
		पूर्ण

		वापस;
	पूर्ण

	ex = path[depth].p_ext;
	जबतक (ex <= EXT_MAX_EXTENT(path[depth].p_hdr)) अणु
		ext_debug(inode, "move %d:%llu:[%d]%d in new leaf %llu\n",
				le32_to_cpu(ex->ee_block),
				ext4_ext_pblock(ex),
				ext4_ext_is_unwritten(ex),
				ext4_ext_get_actual_len(ex),
				newblock);
		ex++;
	पूर्ण
पूर्ण

#अन्यथा
#घोषणा ext4_ext_show_path(inode, path)
#घोषणा ext4_ext_show_leaf(inode, path)
#घोषणा ext4_ext_show_move(inode, path, newblock, level)
#पूर्ण_अगर

व्योम ext4_ext_drop_refs(काष्ठा ext4_ext_path *path)
अणु
	पूर्णांक depth, i;

	अगर (!path)
		वापस;
	depth = path->p_depth;
	क्रम (i = 0; i <= depth; i++, path++) अणु
		brअन्यथा(path->p_bh);
		path->p_bh = शून्य;
	पूर्ण
पूर्ण

/*
 * ext4_ext_binsearch_idx:
 * binary search क्रम the बंदst index of the given block
 * the header must be checked beक्रमe calling this
 */
अटल व्योम
ext4_ext_binsearch_idx(काष्ठा inode *inode,
			काष्ठा ext4_ext_path *path, ext4_lblk_t block)
अणु
	काष्ठा ext4_extent_header *eh = path->p_hdr;
	काष्ठा ext4_extent_idx *r, *l, *m;


	ext_debug(inode, "binsearch for %u(idx):  ", block);

	l = EXT_FIRST_INDEX(eh) + 1;
	r = EXT_LAST_INDEX(eh);
	जबतक (l <= r) अणु
		m = l + (r - l) / 2;
		अगर (block < le32_to_cpu(m->ei_block))
			r = m - 1;
		अन्यथा
			l = m + 1;
		ext_debug(inode, "%p(%u):%p(%u):%p(%u) ", l,
			  le32_to_cpu(l->ei_block), m, le32_to_cpu(m->ei_block),
			  r, le32_to_cpu(r->ei_block));
	पूर्ण

	path->p_idx = l - 1;
	ext_debug(inode, "  -> %u->%lld ", le32_to_cpu(path->p_idx->ei_block),
		  ext4_idx_pblock(path->p_idx));

#अगर_घोषित CHECK_BINSEARCH
	अणु
		काष्ठा ext4_extent_idx *chix, *ix;
		पूर्णांक k;

		chix = ix = EXT_FIRST_INDEX(eh);
		क्रम (k = 0; k < le16_to_cpu(eh->eh_entries); k++, ix++) अणु
			अगर (k != 0 && le32_to_cpu(ix->ei_block) <=
			    le32_to_cpu(ix[-1].ei_block)) अणु
				prपूर्णांकk(KERN_DEBUG "k=%d, ix=0x%p, "
				       "first=0x%p\n", k,
				       ix, EXT_FIRST_INDEX(eh));
				prपूर्णांकk(KERN_DEBUG "%u <= %u\n",
				       le32_to_cpu(ix->ei_block),
				       le32_to_cpu(ix[-1].ei_block));
			पूर्ण
			BUG_ON(k && le32_to_cpu(ix->ei_block)
					   <= le32_to_cpu(ix[-1].ei_block));
			अगर (block < le32_to_cpu(ix->ei_block))
				अवरोध;
			chix = ix;
		पूर्ण
		BUG_ON(chix != path->p_idx);
	पूर्ण
#पूर्ण_अगर

पूर्ण

/*
 * ext4_ext_binsearch:
 * binary search क्रम बंदst extent of the given block
 * the header must be checked beक्रमe calling this
 */
अटल व्योम
ext4_ext_binsearch(काष्ठा inode *inode,
		काष्ठा ext4_ext_path *path, ext4_lblk_t block)
अणु
	काष्ठा ext4_extent_header *eh = path->p_hdr;
	काष्ठा ext4_extent *r, *l, *m;

	अगर (eh->eh_entries == 0) अणु
		/*
		 * this leaf is empty:
		 * we get such a leaf in split/add हाल
		 */
		वापस;
	पूर्ण

	ext_debug(inode, "binsearch for %u:  ", block);

	l = EXT_FIRST_EXTENT(eh) + 1;
	r = EXT_LAST_EXTENT(eh);

	जबतक (l <= r) अणु
		m = l + (r - l) / 2;
		अगर (block < le32_to_cpu(m->ee_block))
			r = m - 1;
		अन्यथा
			l = m + 1;
		ext_debug(inode, "%p(%u):%p(%u):%p(%u) ", l,
			  le32_to_cpu(l->ee_block), m, le32_to_cpu(m->ee_block),
			  r, le32_to_cpu(r->ee_block));
	पूर्ण

	path->p_ext = l - 1;
	ext_debug(inode, "  -> %d:%llu:[%d]%d ",
			le32_to_cpu(path->p_ext->ee_block),
			ext4_ext_pblock(path->p_ext),
			ext4_ext_is_unwritten(path->p_ext),
			ext4_ext_get_actual_len(path->p_ext));

#अगर_घोषित CHECK_BINSEARCH
	अणु
		काष्ठा ext4_extent *chex, *ex;
		पूर्णांक k;

		chex = ex = EXT_FIRST_EXTENT(eh);
		क्रम (k = 0; k < le16_to_cpu(eh->eh_entries); k++, ex++) अणु
			BUG_ON(k && le32_to_cpu(ex->ee_block)
					  <= le32_to_cpu(ex[-1].ee_block));
			अगर (block < le32_to_cpu(ex->ee_block))
				अवरोध;
			chex = ex;
		पूर्ण
		BUG_ON(chex != path->p_ext);
	पूर्ण
#पूर्ण_अगर

पूर्ण

व्योम ext4_ext_tree_init(handle_t *handle, काष्ठा inode *inode)
अणु
	काष्ठा ext4_extent_header *eh;

	eh = ext_inode_hdr(inode);
	eh->eh_depth = 0;
	eh->eh_entries = 0;
	eh->eh_magic = EXT4_EXT_MAGIC;
	eh->eh_max = cpu_to_le16(ext4_ext_space_root(inode, 0));
	ext4_mark_inode_dirty(handle, inode);
पूर्ण

काष्ठा ext4_ext_path *
ext4_find_extent(काष्ठा inode *inode, ext4_lblk_t block,
		 काष्ठा ext4_ext_path **orig_path, पूर्णांक flags)
अणु
	काष्ठा ext4_extent_header *eh;
	काष्ठा buffer_head *bh;
	काष्ठा ext4_ext_path *path = orig_path ? *orig_path : शून्य;
	लघु पूर्णांक depth, i, ppos = 0;
	पूर्णांक ret;
	gfp_t gfp_flags = GFP_NOFS;

	अगर (flags & EXT4_EX_NOFAIL)
		gfp_flags |= __GFP_NOFAIL;

	eh = ext_inode_hdr(inode);
	depth = ext_depth(inode);
	अगर (depth < 0 || depth > EXT4_MAX_EXTENT_DEPTH) अणु
		EXT4_ERROR_INODE(inode, "inode has invalid extent depth: %d",
				 depth);
		ret = -EFSCORRUPTED;
		जाओ err;
	पूर्ण

	अगर (path) अणु
		ext4_ext_drop_refs(path);
		अगर (depth > path[0].p_maxdepth) अणु
			kमुक्त(path);
			*orig_path = path = शून्य;
		पूर्ण
	पूर्ण
	अगर (!path) अणु
		/* account possible depth increase */
		path = kसुस्मृति(depth + 2, माप(काष्ठा ext4_ext_path),
				gfp_flags);
		अगर (unlikely(!path))
			वापस ERR_PTR(-ENOMEM);
		path[0].p_maxdepth = depth + 1;
	पूर्ण
	path[0].p_hdr = eh;
	path[0].p_bh = शून्य;

	i = depth;
	अगर (!(flags & EXT4_EX_NOCACHE) && depth == 0)
		ext4_cache_extents(inode, eh);
	/* walk through the tree */
	जबतक (i) अणु
		ext_debug(inode, "depth %d: num %d, max %d\n",
			  ppos, le16_to_cpu(eh->eh_entries), le16_to_cpu(eh->eh_max));

		ext4_ext_binsearch_idx(inode, path + ppos, block);
		path[ppos].p_block = ext4_idx_pblock(path[ppos].p_idx);
		path[ppos].p_depth = i;
		path[ppos].p_ext = शून्य;

		bh = पढ़ो_extent_tree_block(inode, path[ppos].p_block, --i,
					    flags);
		अगर (IS_ERR(bh)) अणु
			ret = PTR_ERR(bh);
			जाओ err;
		पूर्ण

		eh = ext_block_hdr(bh);
		ppos++;
		path[ppos].p_bh = bh;
		path[ppos].p_hdr = eh;
	पूर्ण

	path[ppos].p_depth = i;
	path[ppos].p_ext = शून्य;
	path[ppos].p_idx = शून्य;

	/* find extent */
	ext4_ext_binsearch(inode, path + ppos, block);
	/* अगर not an empty leaf */
	अगर (path[ppos].p_ext)
		path[ppos].p_block = ext4_ext_pblock(path[ppos].p_ext);

	ext4_ext_show_path(inode, path);

	वापस path;

err:
	ext4_ext_drop_refs(path);
	kमुक्त(path);
	अगर (orig_path)
		*orig_path = शून्य;
	वापस ERR_PTR(ret);
पूर्ण

/*
 * ext4_ext_insert_index:
 * insert new index [@logical;@ptr] पूर्णांकo the block at @curp;
 * check where to insert: beक्रमe @curp or after @curp
 */
अटल पूर्णांक ext4_ext_insert_index(handle_t *handle, काष्ठा inode *inode,
				 काष्ठा ext4_ext_path *curp,
				 पूर्णांक logical, ext4_fsblk_t ptr)
अणु
	काष्ठा ext4_extent_idx *ix;
	पूर्णांक len, err;

	err = ext4_ext_get_access(handle, inode, curp);
	अगर (err)
		वापस err;

	अगर (unlikely(logical == le32_to_cpu(curp->p_idx->ei_block))) अणु
		EXT4_ERROR_INODE(inode,
				 "logical %d == ei_block %d!",
				 logical, le32_to_cpu(curp->p_idx->ei_block));
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (unlikely(le16_to_cpu(curp->p_hdr->eh_entries)
			     >= le16_to_cpu(curp->p_hdr->eh_max))) अणु
		EXT4_ERROR_INODE(inode,
				 "eh_entries %d >= eh_max %d!",
				 le16_to_cpu(curp->p_hdr->eh_entries),
				 le16_to_cpu(curp->p_hdr->eh_max));
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (logical > le32_to_cpu(curp->p_idx->ei_block)) अणु
		/* insert after */
		ext_debug(inode, "insert new index %d after: %llu\n",
			  logical, ptr);
		ix = curp->p_idx + 1;
	पूर्ण अन्यथा अणु
		/* insert beक्रमe */
		ext_debug(inode, "insert new index %d before: %llu\n",
			  logical, ptr);
		ix = curp->p_idx;
	पूर्ण

	len = EXT_LAST_INDEX(curp->p_hdr) - ix + 1;
	BUG_ON(len < 0);
	अगर (len > 0) अणु
		ext_debug(inode, "insert new index %d: "
				"move %d indices from 0x%p to 0x%p\n",
				logical, len, ix, ix + 1);
		स_हटाओ(ix + 1, ix, len * माप(काष्ठा ext4_extent_idx));
	पूर्ण

	अगर (unlikely(ix > EXT_MAX_INDEX(curp->p_hdr))) अणु
		EXT4_ERROR_INODE(inode, "ix > EXT_MAX_INDEX!");
		वापस -EFSCORRUPTED;
	पूर्ण

	ix->ei_block = cpu_to_le32(logical);
	ext4_idx_store_pblock(ix, ptr);
	le16_add_cpu(&curp->p_hdr->eh_entries, 1);

	अगर (unlikely(ix > EXT_LAST_INDEX(curp->p_hdr))) अणु
		EXT4_ERROR_INODE(inode, "ix > EXT_LAST_INDEX!");
		वापस -EFSCORRUPTED;
	पूर्ण

	err = ext4_ext_dirty(handle, inode, curp);
	ext4_std_error(inode->i_sb, err);

	वापस err;
पूर्ण

/*
 * ext4_ext_split:
 * inserts new subtree पूर्णांकo the path, using मुक्त index entry
 * at depth @at:
 * - allocates all needed blocks (new leaf and all पूर्णांकermediate index blocks)
 * - makes decision where to split
 * - moves reमुख्यing extents and index entries (right to the split poपूर्णांक)
 *   पूर्णांकo the newly allocated blocks
 * - initializes subtree
 */
अटल पूर्णांक ext4_ext_split(handle_t *handle, काष्ठा inode *inode,
			  अचिन्हित पूर्णांक flags,
			  काष्ठा ext4_ext_path *path,
			  काष्ठा ext4_extent *newext, पूर्णांक at)
अणु
	काष्ठा buffer_head *bh = शून्य;
	पूर्णांक depth = ext_depth(inode);
	काष्ठा ext4_extent_header *neh;
	काष्ठा ext4_extent_idx *fidx;
	पूर्णांक i = at, k, m, a;
	ext4_fsblk_t newblock, oldblock;
	__le32 border;
	ext4_fsblk_t *ablocks = शून्य; /* array of allocated blocks */
	gfp_t gfp_flags = GFP_NOFS;
	पूर्णांक err = 0;
	माप_प्रकार ext_size = 0;

	अगर (flags & EXT4_EX_NOFAIL)
		gfp_flags |= __GFP_NOFAIL;

	/* make decision: where to split? */
	/* FIXME: now decision is simplest: at current extent */

	/* अगर current leaf will be split, then we should use
	 * border from split poपूर्णांक */
	अगर (unlikely(path[depth].p_ext > EXT_MAX_EXTENT(path[depth].p_hdr))) अणु
		EXT4_ERROR_INODE(inode, "p_ext > EXT_MAX_EXTENT!");
		वापस -EFSCORRUPTED;
	पूर्ण
	अगर (path[depth].p_ext != EXT_MAX_EXTENT(path[depth].p_hdr)) अणु
		border = path[depth].p_ext[1].ee_block;
		ext_debug(inode, "leaf will be split."
				" next leaf starts at %d\n",
				  le32_to_cpu(border));
	पूर्ण अन्यथा अणु
		border = newext->ee_block;
		ext_debug(inode, "leaf will be added."
				" next leaf starts at %d\n",
				le32_to_cpu(border));
	पूर्ण

	/*
	 * If error occurs, then we अवरोध processing
	 * and mark fileप्रणाली पढ़ो-only. index won't
	 * be inserted and tree will be in consistent
	 * state. Next mount will repair buffers too.
	 */

	/*
	 * Get array to track all allocated blocks.
	 * We need this to handle errors and मुक्त blocks
	 * upon them.
	 */
	ablocks = kसुस्मृति(depth, माप(ext4_fsblk_t), gfp_flags);
	अगर (!ablocks)
		वापस -ENOMEM;

	/* allocate all needed blocks */
	ext_debug(inode, "allocate %d blocks for indexes/leaf\n", depth - at);
	क्रम (a = 0; a < depth - at; a++) अणु
		newblock = ext4_ext_new_meta_block(handle, inode, path,
						   newext, &err, flags);
		अगर (newblock == 0)
			जाओ cleanup;
		ablocks[a] = newblock;
	पूर्ण

	/* initialize new leaf */
	newblock = ablocks[--a];
	अगर (unlikely(newblock == 0)) अणु
		EXT4_ERROR_INODE(inode, "newblock == 0!");
		err = -EFSCORRUPTED;
		जाओ cleanup;
	पूर्ण
	bh = sb_getblk_gfp(inode->i_sb, newblock, __GFP_MOVABLE | GFP_NOFS);
	अगर (unlikely(!bh)) अणु
		err = -ENOMEM;
		जाओ cleanup;
	पूर्ण
	lock_buffer(bh);

	err = ext4_journal_get_create_access(handle, bh);
	अगर (err)
		जाओ cleanup;

	neh = ext_block_hdr(bh);
	neh->eh_entries = 0;
	neh->eh_max = cpu_to_le16(ext4_ext_space_block(inode, 0));
	neh->eh_magic = EXT4_EXT_MAGIC;
	neh->eh_depth = 0;

	/* move reमुख्यder of path[depth] to the new leaf */
	अगर (unlikely(path[depth].p_hdr->eh_entries !=
		     path[depth].p_hdr->eh_max)) अणु
		EXT4_ERROR_INODE(inode, "eh_entries %d != eh_max %d!",
				 path[depth].p_hdr->eh_entries,
				 path[depth].p_hdr->eh_max);
		err = -EFSCORRUPTED;
		जाओ cleanup;
	पूर्ण
	/* start copy from next extent */
	m = EXT_MAX_EXTENT(path[depth].p_hdr) - path[depth].p_ext++;
	ext4_ext_show_move(inode, path, newblock, depth);
	अगर (m) अणु
		काष्ठा ext4_extent *ex;
		ex = EXT_FIRST_EXTENT(neh);
		स_हटाओ(ex, path[depth].p_ext, माप(काष्ठा ext4_extent) * m);
		le16_add_cpu(&neh->eh_entries, m);
	पूर्ण

	/* zero out unused area in the extent block */
	ext_size = माप(काष्ठा ext4_extent_header) +
		माप(काष्ठा ext4_extent) * le16_to_cpu(neh->eh_entries);
	स_रखो(bh->b_data + ext_size, 0, inode->i_sb->s_blocksize - ext_size);
	ext4_extent_block_csum_set(inode, neh);
	set_buffer_uptodate(bh);
	unlock_buffer(bh);

	err = ext4_handle_dirty_metadata(handle, inode, bh);
	अगर (err)
		जाओ cleanup;
	brअन्यथा(bh);
	bh = शून्य;

	/* correct old leaf */
	अगर (m) अणु
		err = ext4_ext_get_access(handle, inode, path + depth);
		अगर (err)
			जाओ cleanup;
		le16_add_cpu(&path[depth].p_hdr->eh_entries, -m);
		err = ext4_ext_dirty(handle, inode, path + depth);
		अगर (err)
			जाओ cleanup;

	पूर्ण

	/* create पूर्णांकermediate indexes */
	k = depth - at - 1;
	अगर (unlikely(k < 0)) अणु
		EXT4_ERROR_INODE(inode, "k %d < 0!", k);
		err = -EFSCORRUPTED;
		जाओ cleanup;
	पूर्ण
	अगर (k)
		ext_debug(inode, "create %d intermediate indices\n", k);
	/* insert new index पूर्णांकo current index block */
	/* current depth stored in i var */
	i = depth - 1;
	जबतक (k--) अणु
		oldblock = newblock;
		newblock = ablocks[--a];
		bh = sb_getblk(inode->i_sb, newblock);
		अगर (unlikely(!bh)) अणु
			err = -ENOMEM;
			जाओ cleanup;
		पूर्ण
		lock_buffer(bh);

		err = ext4_journal_get_create_access(handle, bh);
		अगर (err)
			जाओ cleanup;

		neh = ext_block_hdr(bh);
		neh->eh_entries = cpu_to_le16(1);
		neh->eh_magic = EXT4_EXT_MAGIC;
		neh->eh_max = cpu_to_le16(ext4_ext_space_block_idx(inode, 0));
		neh->eh_depth = cpu_to_le16(depth - i);
		fidx = EXT_FIRST_INDEX(neh);
		fidx->ei_block = border;
		ext4_idx_store_pblock(fidx, oldblock);

		ext_debug(inode, "int.index at %d (block %llu): %u -> %llu\n",
				i, newblock, le32_to_cpu(border), oldblock);

		/* move reमुख्यder of path[i] to the new index block */
		अगर (unlikely(EXT_MAX_INDEX(path[i].p_hdr) !=
					EXT_LAST_INDEX(path[i].p_hdr))) अणु
			EXT4_ERROR_INODE(inode,
					 "EXT_MAX_INDEX != EXT_LAST_INDEX ee_block %d!",
					 le32_to_cpu(path[i].p_ext->ee_block));
			err = -EFSCORRUPTED;
			जाओ cleanup;
		पूर्ण
		/* start copy indexes */
		m = EXT_MAX_INDEX(path[i].p_hdr) - path[i].p_idx++;
		ext_debug(inode, "cur 0x%p, last 0x%p\n", path[i].p_idx,
				EXT_MAX_INDEX(path[i].p_hdr));
		ext4_ext_show_move(inode, path, newblock, i);
		अगर (m) अणु
			स_हटाओ(++fidx, path[i].p_idx,
				माप(काष्ठा ext4_extent_idx) * m);
			le16_add_cpu(&neh->eh_entries, m);
		पूर्ण
		/* zero out unused area in the extent block */
		ext_size = माप(काष्ठा ext4_extent_header) +
		   (माप(काष्ठा ext4_extent) * le16_to_cpu(neh->eh_entries));
		स_रखो(bh->b_data + ext_size, 0,
			inode->i_sb->s_blocksize - ext_size);
		ext4_extent_block_csum_set(inode, neh);
		set_buffer_uptodate(bh);
		unlock_buffer(bh);

		err = ext4_handle_dirty_metadata(handle, inode, bh);
		अगर (err)
			जाओ cleanup;
		brअन्यथा(bh);
		bh = शून्य;

		/* correct old index */
		अगर (m) अणु
			err = ext4_ext_get_access(handle, inode, path + i);
			अगर (err)
				जाओ cleanup;
			le16_add_cpu(&path[i].p_hdr->eh_entries, -m);
			err = ext4_ext_dirty(handle, inode, path + i);
			अगर (err)
				जाओ cleanup;
		पूर्ण

		i--;
	पूर्ण

	/* insert new index */
	err = ext4_ext_insert_index(handle, inode, path + at,
				    le32_to_cpu(border), newblock);

cleanup:
	अगर (bh) अणु
		अगर (buffer_locked(bh))
			unlock_buffer(bh);
		brअन्यथा(bh);
	पूर्ण

	अगर (err) अणु
		/* मुक्त all allocated blocks in error हाल */
		क्रम (i = 0; i < depth; i++) अणु
			अगर (!ablocks[i])
				जारी;
			ext4_मुक्त_blocks(handle, inode, शून्य, ablocks[i], 1,
					 EXT4_FREE_BLOCKS_METADATA);
		पूर्ण
	पूर्ण
	kमुक्त(ablocks);

	वापस err;
पूर्ण

/*
 * ext4_ext_grow_indepth:
 * implements tree growing procedure:
 * - allocates new block
 * - moves top-level data (index block or leaf) पूर्णांकo the new block
 * - initializes new top-level, creating index that poपूर्णांकs to the
 *   just created block
 */
अटल पूर्णांक ext4_ext_grow_indepth(handle_t *handle, काष्ठा inode *inode,
				 अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ext4_extent_header *neh;
	काष्ठा buffer_head *bh;
	ext4_fsblk_t newblock, goal = 0;
	काष्ठा ext4_super_block *es = EXT4_SB(inode->i_sb)->s_es;
	पूर्णांक err = 0;
	माप_प्रकार ext_size = 0;

	/* Try to prepend new index to old one */
	अगर (ext_depth(inode))
		goal = ext4_idx_pblock(EXT_FIRST_INDEX(ext_inode_hdr(inode)));
	अगर (goal > le32_to_cpu(es->s_first_data_block)) अणु
		flags |= EXT4_MB_HINT_TRY_GOAL;
		goal--;
	पूर्ण अन्यथा
		goal = ext4_inode_to_goal_block(inode);
	newblock = ext4_new_meta_blocks(handle, inode, goal, flags,
					शून्य, &err);
	अगर (newblock == 0)
		वापस err;

	bh = sb_getblk_gfp(inode->i_sb, newblock, __GFP_MOVABLE | GFP_NOFS);
	अगर (unlikely(!bh))
		वापस -ENOMEM;
	lock_buffer(bh);

	err = ext4_journal_get_create_access(handle, bh);
	अगर (err) अणु
		unlock_buffer(bh);
		जाओ out;
	पूर्ण

	ext_size = माप(EXT4_I(inode)->i_data);
	/* move top-level index/leaf पूर्णांकo new block */
	स_हटाओ(bh->b_data, EXT4_I(inode)->i_data, ext_size);
	/* zero out unused area in the extent block */
	स_रखो(bh->b_data + ext_size, 0, inode->i_sb->s_blocksize - ext_size);

	/* set size of new block */
	neh = ext_block_hdr(bh);
	/* old root could have indexes or leaves
	 * so calculate e_max right way */
	अगर (ext_depth(inode))
		neh->eh_max = cpu_to_le16(ext4_ext_space_block_idx(inode, 0));
	अन्यथा
		neh->eh_max = cpu_to_le16(ext4_ext_space_block(inode, 0));
	neh->eh_magic = EXT4_EXT_MAGIC;
	ext4_extent_block_csum_set(inode, neh);
	set_buffer_uptodate(bh);
	unlock_buffer(bh);

	err = ext4_handle_dirty_metadata(handle, inode, bh);
	अगर (err)
		जाओ out;

	/* Update top-level index: num,max,poपूर्णांकer */
	neh = ext_inode_hdr(inode);
	neh->eh_entries = cpu_to_le16(1);
	ext4_idx_store_pblock(EXT_FIRST_INDEX(neh), newblock);
	अगर (neh->eh_depth == 0) अणु
		/* Root extent block becomes index block */
		neh->eh_max = cpu_to_le16(ext4_ext_space_root_idx(inode, 0));
		EXT_FIRST_INDEX(neh)->ei_block =
			EXT_FIRST_EXTENT(neh)->ee_block;
	पूर्ण
	ext_debug(inode, "new root: num %d(%d), lblock %d, ptr %llu\n",
		  le16_to_cpu(neh->eh_entries), le16_to_cpu(neh->eh_max),
		  le32_to_cpu(EXT_FIRST_INDEX(neh)->ei_block),
		  ext4_idx_pblock(EXT_FIRST_INDEX(neh)));

	le16_add_cpu(&neh->eh_depth, 1);
	err = ext4_mark_inode_dirty(handle, inode);
out:
	brअन्यथा(bh);

	वापस err;
पूर्ण

/*
 * ext4_ext_create_new_leaf:
 * finds empty index and adds new leaf.
 * अगर no मुक्त index is found, then it requests in-depth growing.
 */
अटल पूर्णांक ext4_ext_create_new_leaf(handle_t *handle, काष्ठा inode *inode,
				    अचिन्हित पूर्णांक mb_flags,
				    अचिन्हित पूर्णांक gb_flags,
				    काष्ठा ext4_ext_path **ppath,
				    काष्ठा ext4_extent *newext)
अणु
	काष्ठा ext4_ext_path *path = *ppath;
	काष्ठा ext4_ext_path *curp;
	पूर्णांक depth, i, err = 0;

repeat:
	i = depth = ext_depth(inode);

	/* walk up to the tree and look क्रम मुक्त index entry */
	curp = path + depth;
	जबतक (i > 0 && !EXT_HAS_FREE_INDEX(curp)) अणु
		i--;
		curp--;
	पूर्ण

	/* we use alपढ़ोy allocated block क्रम index block,
	 * so subsequent data blocks should be contiguous */
	अगर (EXT_HAS_FREE_INDEX(curp)) अणु
		/* अगर we found index with मुक्त entry, then use that
		 * entry: create all needed subtree and add new leaf */
		err = ext4_ext_split(handle, inode, mb_flags, path, newext, i);
		अगर (err)
			जाओ out;

		/* refill path */
		path = ext4_find_extent(inode,
				    (ext4_lblk_t)le32_to_cpu(newext->ee_block),
				    ppath, gb_flags);
		अगर (IS_ERR(path))
			err = PTR_ERR(path);
	पूर्ण अन्यथा अणु
		/* tree is full, समय to grow in depth */
		err = ext4_ext_grow_indepth(handle, inode, mb_flags);
		अगर (err)
			जाओ out;

		/* refill path */
		path = ext4_find_extent(inode,
				   (ext4_lblk_t)le32_to_cpu(newext->ee_block),
				    ppath, gb_flags);
		अगर (IS_ERR(path)) अणु
			err = PTR_ERR(path);
			जाओ out;
		पूर्ण

		/*
		 * only first (depth 0 -> 1) produces मुक्त space;
		 * in all other हालs we have to split the grown tree
		 */
		depth = ext_depth(inode);
		अगर (path[depth].p_hdr->eh_entries == path[depth].p_hdr->eh_max) अणु
			/* now we need to split */
			जाओ repeat;
		पूर्ण
	पूर्ण

out:
	वापस err;
पूर्ण

/*
 * search the बंदst allocated block to the left क्रम *logical
 * and वापसs it at @logical + it's physical address at @phys
 * अगर *logical is the smallest allocated block, the function
 * वापसs 0 at @phys
 * वापस value contains 0 (success) or error code
 */
अटल पूर्णांक ext4_ext_search_left(काष्ठा inode *inode,
				काष्ठा ext4_ext_path *path,
				ext4_lblk_t *logical, ext4_fsblk_t *phys)
अणु
	काष्ठा ext4_extent_idx *ix;
	काष्ठा ext4_extent *ex;
	पूर्णांक depth, ee_len;

	अगर (unlikely(path == शून्य)) अणु
		EXT4_ERROR_INODE(inode, "path == NULL *logical %d!", *logical);
		वापस -EFSCORRUPTED;
	पूर्ण
	depth = path->p_depth;
	*phys = 0;

	अगर (depth == 0 && path->p_ext == शून्य)
		वापस 0;

	/* usually extent in the path covers blocks smaller
	 * then *logical, but it can be that extent is the
	 * first one in the file */

	ex = path[depth].p_ext;
	ee_len = ext4_ext_get_actual_len(ex);
	अगर (*logical < le32_to_cpu(ex->ee_block)) अणु
		अगर (unlikely(EXT_FIRST_EXTENT(path[depth].p_hdr) != ex)) अणु
			EXT4_ERROR_INODE(inode,
					 "EXT_FIRST_EXTENT != ex *logical %d ee_block %d!",
					 *logical, le32_to_cpu(ex->ee_block));
			वापस -EFSCORRUPTED;
		पूर्ण
		जबतक (--depth >= 0) अणु
			ix = path[depth].p_idx;
			अगर (unlikely(ix != EXT_FIRST_INDEX(path[depth].p_hdr))) अणु
				EXT4_ERROR_INODE(inode,
				  "ix (%d) != EXT_FIRST_INDEX (%d) (depth %d)!",
				  ix != शून्य ? le32_to_cpu(ix->ei_block) : 0,
				  EXT_FIRST_INDEX(path[depth].p_hdr) != शून्य ?
		le32_to_cpu(EXT_FIRST_INDEX(path[depth].p_hdr)->ei_block) : 0,
				  depth);
				वापस -EFSCORRUPTED;
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (unlikely(*logical < (le32_to_cpu(ex->ee_block) + ee_len))) अणु
		EXT4_ERROR_INODE(inode,
				 "logical %d < ee_block %d + ee_len %d!",
				 *logical, le32_to_cpu(ex->ee_block), ee_len);
		वापस -EFSCORRUPTED;
	पूर्ण

	*logical = le32_to_cpu(ex->ee_block) + ee_len - 1;
	*phys = ext4_ext_pblock(ex) + ee_len - 1;
	वापस 0;
पूर्ण

/*
 * Search the बंदst allocated block to the right क्रम *logical
 * and वापसs it at @logical + it's physical address at @phys.
 * If not exists, वापस 0 and @phys is set to 0. We will वापस
 * 1 which means we found an allocated block and ret_ex is valid.
 * Or वापस a (< 0) error code.
 */
अटल पूर्णांक ext4_ext_search_right(काष्ठा inode *inode,
				 काष्ठा ext4_ext_path *path,
				 ext4_lblk_t *logical, ext4_fsblk_t *phys,
				 काष्ठा ext4_extent *ret_ex)
अणु
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ext4_extent_header *eh;
	काष्ठा ext4_extent_idx *ix;
	काष्ठा ext4_extent *ex;
	ext4_fsblk_t block;
	पूर्णांक depth;	/* Note, NOT eh_depth; depth from top of tree */
	पूर्णांक ee_len;

	अगर (unlikely(path == शून्य)) अणु
		EXT4_ERROR_INODE(inode, "path == NULL *logical %d!", *logical);
		वापस -EFSCORRUPTED;
	पूर्ण
	depth = path->p_depth;
	*phys = 0;

	अगर (depth == 0 && path->p_ext == शून्य)
		वापस 0;

	/* usually extent in the path covers blocks smaller
	 * then *logical, but it can be that extent is the
	 * first one in the file */

	ex = path[depth].p_ext;
	ee_len = ext4_ext_get_actual_len(ex);
	अगर (*logical < le32_to_cpu(ex->ee_block)) अणु
		अगर (unlikely(EXT_FIRST_EXTENT(path[depth].p_hdr) != ex)) अणु
			EXT4_ERROR_INODE(inode,
					 "first_extent(path[%d].p_hdr) != ex",
					 depth);
			वापस -EFSCORRUPTED;
		पूर्ण
		जबतक (--depth >= 0) अणु
			ix = path[depth].p_idx;
			अगर (unlikely(ix != EXT_FIRST_INDEX(path[depth].p_hdr))) अणु
				EXT4_ERROR_INODE(inode,
						 "ix != EXT_FIRST_INDEX *logical %d!",
						 *logical);
				वापस -EFSCORRUPTED;
			पूर्ण
		पूर्ण
		जाओ found_extent;
	पूर्ण

	अगर (unlikely(*logical < (le32_to_cpu(ex->ee_block) + ee_len))) अणु
		EXT4_ERROR_INODE(inode,
				 "logical %d < ee_block %d + ee_len %d!",
				 *logical, le32_to_cpu(ex->ee_block), ee_len);
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (ex != EXT_LAST_EXTENT(path[depth].p_hdr)) अणु
		/* next allocated block in this leaf */
		ex++;
		जाओ found_extent;
	पूर्ण

	/* go up and search क्रम index to the right */
	जबतक (--depth >= 0) अणु
		ix = path[depth].p_idx;
		अगर (ix != EXT_LAST_INDEX(path[depth].p_hdr))
			जाओ got_index;
	पूर्ण

	/* we've gone up to the root and found no index to the right */
	वापस 0;

got_index:
	/* we've found index to the right, let's
	 * follow it and find the बंदst allocated
	 * block to the right */
	ix++;
	block = ext4_idx_pblock(ix);
	जबतक (++depth < path->p_depth) अणु
		/* subtract from p_depth to get proper eh_depth */
		bh = पढ़ो_extent_tree_block(inode, block,
					    path->p_depth - depth, 0);
		अगर (IS_ERR(bh))
			वापस PTR_ERR(bh);
		eh = ext_block_hdr(bh);
		ix = EXT_FIRST_INDEX(eh);
		block = ext4_idx_pblock(ix);
		put_bh(bh);
	पूर्ण

	bh = पढ़ो_extent_tree_block(inode, block, path->p_depth - depth, 0);
	अगर (IS_ERR(bh))
		वापस PTR_ERR(bh);
	eh = ext_block_hdr(bh);
	ex = EXT_FIRST_EXTENT(eh);
found_extent:
	*logical = le32_to_cpu(ex->ee_block);
	*phys = ext4_ext_pblock(ex);
	अगर (ret_ex)
		*ret_ex = *ex;
	अगर (bh)
		put_bh(bh);
	वापस 1;
पूर्ण

/*
 * ext4_ext_next_allocated_block:
 * वापसs allocated block in subsequent extent or EXT_MAX_BLOCKS.
 * NOTE: it considers block number from index entry as
 * allocated block. Thus, index entries have to be consistent
 * with leaves.
 */
ext4_lblk_t
ext4_ext_next_allocated_block(काष्ठा ext4_ext_path *path)
अणु
	पूर्णांक depth;

	BUG_ON(path == शून्य);
	depth = path->p_depth;

	अगर (depth == 0 && path->p_ext == शून्य)
		वापस EXT_MAX_BLOCKS;

	जबतक (depth >= 0) अणु
		काष्ठा ext4_ext_path *p = &path[depth];

		अगर (depth == path->p_depth) अणु
			/* leaf */
			अगर (p->p_ext && p->p_ext != EXT_LAST_EXTENT(p->p_hdr))
				वापस le32_to_cpu(p->p_ext[1].ee_block);
		पूर्ण अन्यथा अणु
			/* index */
			अगर (p->p_idx != EXT_LAST_INDEX(p->p_hdr))
				वापस le32_to_cpu(p->p_idx[1].ei_block);
		पूर्ण
		depth--;
	पूर्ण

	वापस EXT_MAX_BLOCKS;
पूर्ण

/*
 * ext4_ext_next_leaf_block:
 * वापसs first allocated block from next leaf or EXT_MAX_BLOCKS
 */
अटल ext4_lblk_t ext4_ext_next_leaf_block(काष्ठा ext4_ext_path *path)
अणु
	पूर्णांक depth;

	BUG_ON(path == शून्य);
	depth = path->p_depth;

	/* zero-tree has no leaf blocks at all */
	अगर (depth == 0)
		वापस EXT_MAX_BLOCKS;

	/* go to index block */
	depth--;

	जबतक (depth >= 0) अणु
		अगर (path[depth].p_idx !=
				EXT_LAST_INDEX(path[depth].p_hdr))
			वापस (ext4_lblk_t)
				le32_to_cpu(path[depth].p_idx[1].ei_block);
		depth--;
	पूर्ण

	वापस EXT_MAX_BLOCKS;
पूर्ण

/*
 * ext4_ext_correct_indexes:
 * अगर leaf माला_लो modअगरied and modअगरied extent is first in the leaf,
 * then we have to correct all indexes above.
 * TODO: करो we need to correct tree in all हालs?
 */
अटल पूर्णांक ext4_ext_correct_indexes(handle_t *handle, काष्ठा inode *inode,
				काष्ठा ext4_ext_path *path)
अणु
	काष्ठा ext4_extent_header *eh;
	पूर्णांक depth = ext_depth(inode);
	काष्ठा ext4_extent *ex;
	__le32 border;
	पूर्णांक k, err = 0;

	eh = path[depth].p_hdr;
	ex = path[depth].p_ext;

	अगर (unlikely(ex == शून्य || eh == शून्य)) अणु
		EXT4_ERROR_INODE(inode,
				 "ex %p == NULL or eh %p == NULL", ex, eh);
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (depth == 0) अणु
		/* there is no tree at all */
		वापस 0;
	पूर्ण

	अगर (ex != EXT_FIRST_EXTENT(eh)) अणु
		/* we correct tree अगर first leaf got modअगरied only */
		वापस 0;
	पूर्ण

	/*
	 * TODO: we need correction अगर border is smaller than current one
	 */
	k = depth - 1;
	border = path[depth].p_ext->ee_block;
	err = ext4_ext_get_access(handle, inode, path + k);
	अगर (err)
		वापस err;
	path[k].p_idx->ei_block = border;
	err = ext4_ext_dirty(handle, inode, path + k);
	अगर (err)
		वापस err;

	जबतक (k--) अणु
		/* change all left-side indexes */
		अगर (path[k+1].p_idx != EXT_FIRST_INDEX(path[k+1].p_hdr))
			अवरोध;
		err = ext4_ext_get_access(handle, inode, path + k);
		अगर (err)
			अवरोध;
		path[k].p_idx->ei_block = border;
		err = ext4_ext_dirty(handle, inode, path + k);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ext4_can_extents_be_merged(काष्ठा inode *inode,
				      काष्ठा ext4_extent *ex1,
				      काष्ठा ext4_extent *ex2)
अणु
	अचिन्हित लघु ext1_ee_len, ext2_ee_len;

	अगर (ext4_ext_is_unwritten(ex1) != ext4_ext_is_unwritten(ex2))
		वापस 0;

	ext1_ee_len = ext4_ext_get_actual_len(ex1);
	ext2_ee_len = ext4_ext_get_actual_len(ex2);

	अगर (le32_to_cpu(ex1->ee_block) + ext1_ee_len !=
			le32_to_cpu(ex2->ee_block))
		वापस 0;

	अगर (ext1_ee_len + ext2_ee_len > EXT_INIT_MAX_LEN)
		वापस 0;

	अगर (ext4_ext_is_unwritten(ex1) &&
	    ext1_ee_len + ext2_ee_len > EXT_UNWRITTEN_MAX_LEN)
		वापस 0;
#अगर_घोषित AGGRESSIVE_TEST
	अगर (ext1_ee_len >= 4)
		वापस 0;
#पूर्ण_अगर

	अगर (ext4_ext_pblock(ex1) + ext1_ee_len == ext4_ext_pblock(ex2))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * This function tries to merge the "ex" extent to the next extent in the tree.
 * It always tries to merge towards right. If you want to merge towards
 * left, pass "ex - 1" as argument instead of "ex".
 * Returns 0 अगर the extents (ex and ex+1) were _not_ merged and वापसs
 * 1 अगर they got merged.
 */
अटल पूर्णांक ext4_ext_try_to_merge_right(काष्ठा inode *inode,
				 काष्ठा ext4_ext_path *path,
				 काष्ठा ext4_extent *ex)
अणु
	काष्ठा ext4_extent_header *eh;
	अचिन्हित पूर्णांक depth, len;
	पूर्णांक merge_करोne = 0, unwritten;

	depth = ext_depth(inode);
	BUG_ON(path[depth].p_hdr == शून्य);
	eh = path[depth].p_hdr;

	जबतक (ex < EXT_LAST_EXTENT(eh)) अणु
		अगर (!ext4_can_extents_be_merged(inode, ex, ex + 1))
			अवरोध;
		/* merge with next extent! */
		unwritten = ext4_ext_is_unwritten(ex);
		ex->ee_len = cpu_to_le16(ext4_ext_get_actual_len(ex)
				+ ext4_ext_get_actual_len(ex + 1));
		अगर (unwritten)
			ext4_ext_mark_unwritten(ex);

		अगर (ex + 1 < EXT_LAST_EXTENT(eh)) अणु
			len = (EXT_LAST_EXTENT(eh) - ex - 1)
				* माप(काष्ठा ext4_extent);
			स_हटाओ(ex + 1, ex + 2, len);
		पूर्ण
		le16_add_cpu(&eh->eh_entries, -1);
		merge_करोne = 1;
		WARN_ON(eh->eh_entries == 0);
		अगर (!eh->eh_entries)
			EXT4_ERROR_INODE(inode, "eh->eh_entries = 0!");
	पूर्ण

	वापस merge_करोne;
पूर्ण

/*
 * This function करोes a very simple check to see अगर we can collapse
 * an extent tree with a single extent tree leaf block पूर्णांकo the inode.
 */
अटल व्योम ext4_ext_try_to_merge_up(handle_t *handle,
				     काष्ठा inode *inode,
				     काष्ठा ext4_ext_path *path)
अणु
	माप_प्रकार s;
	अचिन्हित max_root = ext4_ext_space_root(inode, 0);
	ext4_fsblk_t blk;

	अगर ((path[0].p_depth != 1) ||
	    (le16_to_cpu(path[0].p_hdr->eh_entries) != 1) ||
	    (le16_to_cpu(path[1].p_hdr->eh_entries) > max_root))
		वापस;

	/*
	 * We need to modअगरy the block allocation biपंचांगap and the block
	 * group descriptor to release the extent tree block.  If we
	 * can't get the journal credits, give up.
	 */
	अगर (ext4_journal_extend(handle, 2,
			ext4_मुक्त_metadata_revoke_credits(inode->i_sb, 1)))
		वापस;

	/*
	 * Copy the extent data up to the inode
	 */
	blk = ext4_idx_pblock(path[0].p_idx);
	s = le16_to_cpu(path[1].p_hdr->eh_entries) *
		माप(काष्ठा ext4_extent_idx);
	s += माप(काष्ठा ext4_extent_header);

	path[1].p_maxdepth = path[0].p_maxdepth;
	स_नकल(path[0].p_hdr, path[1].p_hdr, s);
	path[0].p_depth = 0;
	path[0].p_ext = EXT_FIRST_EXTENT(path[0].p_hdr) +
		(path[1].p_ext - EXT_FIRST_EXTENT(path[1].p_hdr));
	path[0].p_hdr->eh_max = cpu_to_le16(max_root);

	brअन्यथा(path[1].p_bh);
	ext4_मुक्त_blocks(handle, inode, शून्य, blk, 1,
			 EXT4_FREE_BLOCKS_METADATA | EXT4_FREE_BLOCKS_FORGET);
पूर्ण

/*
 * This function tries to merge the @ex extent to neighbours in the tree, then
 * tries to collapse the extent tree पूर्णांकo the inode.
 */
अटल व्योम ext4_ext_try_to_merge(handle_t *handle,
				  काष्ठा inode *inode,
				  काष्ठा ext4_ext_path *path,
				  काष्ठा ext4_extent *ex)
अणु
	काष्ठा ext4_extent_header *eh;
	अचिन्हित पूर्णांक depth;
	पूर्णांक merge_करोne = 0;

	depth = ext_depth(inode);
	BUG_ON(path[depth].p_hdr == शून्य);
	eh = path[depth].p_hdr;

	अगर (ex > EXT_FIRST_EXTENT(eh))
		merge_करोne = ext4_ext_try_to_merge_right(inode, path, ex - 1);

	अगर (!merge_करोne)
		(व्योम) ext4_ext_try_to_merge_right(inode, path, ex);

	ext4_ext_try_to_merge_up(handle, inode, path);
पूर्ण

/*
 * check अगर a portion of the "newext" extent overlaps with an
 * existing extent.
 *
 * If there is an overlap discovered, it updates the length of the newext
 * such that there will be no overlap, and then वापसs 1.
 * If there is no overlap found, it वापसs 0.
 */
अटल अचिन्हित पूर्णांक ext4_ext_check_overlap(काष्ठा ext4_sb_info *sbi,
					   काष्ठा inode *inode,
					   काष्ठा ext4_extent *newext,
					   काष्ठा ext4_ext_path *path)
अणु
	ext4_lblk_t b1, b2;
	अचिन्हित पूर्णांक depth, len1;
	अचिन्हित पूर्णांक ret = 0;

	b1 = le32_to_cpu(newext->ee_block);
	len1 = ext4_ext_get_actual_len(newext);
	depth = ext_depth(inode);
	अगर (!path[depth].p_ext)
		जाओ out;
	b2 = EXT4_LBLK_CMASK(sbi, le32_to_cpu(path[depth].p_ext->ee_block));

	/*
	 * get the next allocated block अगर the extent in the path
	 * is beक्रमe the requested block(s)
	 */
	अगर (b2 < b1) अणु
		b2 = ext4_ext_next_allocated_block(path);
		अगर (b2 == EXT_MAX_BLOCKS)
			जाओ out;
		b2 = EXT4_LBLK_CMASK(sbi, b2);
	पूर्ण

	/* check क्रम wrap through zero on extent logical start block*/
	अगर (b1 + len1 < b1) अणु
		len1 = EXT_MAX_BLOCKS - b1;
		newext->ee_len = cpu_to_le16(len1);
		ret = 1;
	पूर्ण

	/* check क्रम overlap */
	अगर (b1 + len1 > b2) अणु
		newext->ee_len = cpu_to_le16(b2 - b1);
		ret = 1;
	पूर्ण
out:
	वापस ret;
पूर्ण

/*
 * ext4_ext_insert_extent:
 * tries to merge requested extent पूर्णांकo the existing extent or
 * inserts requested extent as new one पूर्णांकo the tree,
 * creating new leaf in the no-space हाल.
 */
पूर्णांक ext4_ext_insert_extent(handle_t *handle, काष्ठा inode *inode,
				काष्ठा ext4_ext_path **ppath,
				काष्ठा ext4_extent *newext, पूर्णांक gb_flags)
अणु
	काष्ठा ext4_ext_path *path = *ppath;
	काष्ठा ext4_extent_header *eh;
	काष्ठा ext4_extent *ex, *fex;
	काष्ठा ext4_extent *nearex; /* nearest extent */
	काष्ठा ext4_ext_path *npath = शून्य;
	पूर्णांक depth, len, err;
	ext4_lblk_t next;
	पूर्णांक mb_flags = 0, unwritten;

	अगर (gb_flags & EXT4_GET_BLOCKS_DELALLOC_RESERVE)
		mb_flags |= EXT4_MB_DELALLOC_RESERVED;
	अगर (unlikely(ext4_ext_get_actual_len(newext) == 0)) अणु
		EXT4_ERROR_INODE(inode, "ext4_ext_get_actual_len(newext) == 0");
		वापस -EFSCORRUPTED;
	पूर्ण
	depth = ext_depth(inode);
	ex = path[depth].p_ext;
	eh = path[depth].p_hdr;
	अगर (unlikely(path[depth].p_hdr == शून्य)) अणु
		EXT4_ERROR_INODE(inode, "path[%d].p_hdr == NULL", depth);
		वापस -EFSCORRUPTED;
	पूर्ण

	/* try to insert block पूर्णांकo found extent and वापस */
	अगर (ex && !(gb_flags & EXT4_GET_BLOCKS_PRE_IO)) अणु

		/*
		 * Try to see whether we should rather test the extent on
		 * right from ex, or from the left of ex. This is because
		 * ext4_find_extent() can वापस either extent on the
		 * left, or on the right from the searched position. This
		 * will make merging more effective.
		 */
		अगर (ex < EXT_LAST_EXTENT(eh) &&
		    (le32_to_cpu(ex->ee_block) +
		    ext4_ext_get_actual_len(ex) <
		    le32_to_cpu(newext->ee_block))) अणु
			ex += 1;
			जाओ prepend;
		पूर्ण अन्यथा अगर ((ex > EXT_FIRST_EXTENT(eh)) &&
			   (le32_to_cpu(newext->ee_block) +
			   ext4_ext_get_actual_len(newext) <
			   le32_to_cpu(ex->ee_block)))
			ex -= 1;

		/* Try to append newex to the ex */
		अगर (ext4_can_extents_be_merged(inode, ex, newext)) अणु
			ext_debug(inode, "append [%d]%d block to %u:[%d]%d"
				  "(from %llu)\n",
				  ext4_ext_is_unwritten(newext),
				  ext4_ext_get_actual_len(newext),
				  le32_to_cpu(ex->ee_block),
				  ext4_ext_is_unwritten(ex),
				  ext4_ext_get_actual_len(ex),
				  ext4_ext_pblock(ex));
			err = ext4_ext_get_access(handle, inode,
						  path + depth);
			अगर (err)
				वापस err;
			unwritten = ext4_ext_is_unwritten(ex);
			ex->ee_len = cpu_to_le16(ext4_ext_get_actual_len(ex)
					+ ext4_ext_get_actual_len(newext));
			अगर (unwritten)
				ext4_ext_mark_unwritten(ex);
			eh = path[depth].p_hdr;
			nearex = ex;
			जाओ merge;
		पूर्ण

prepend:
		/* Try to prepend newex to the ex */
		अगर (ext4_can_extents_be_merged(inode, newext, ex)) अणु
			ext_debug(inode, "prepend %u[%d]%d block to %u:[%d]%d"
				  "(from %llu)\n",
				  le32_to_cpu(newext->ee_block),
				  ext4_ext_is_unwritten(newext),
				  ext4_ext_get_actual_len(newext),
				  le32_to_cpu(ex->ee_block),
				  ext4_ext_is_unwritten(ex),
				  ext4_ext_get_actual_len(ex),
				  ext4_ext_pblock(ex));
			err = ext4_ext_get_access(handle, inode,
						  path + depth);
			अगर (err)
				वापस err;

			unwritten = ext4_ext_is_unwritten(ex);
			ex->ee_block = newext->ee_block;
			ext4_ext_store_pblock(ex, ext4_ext_pblock(newext));
			ex->ee_len = cpu_to_le16(ext4_ext_get_actual_len(ex)
					+ ext4_ext_get_actual_len(newext));
			अगर (unwritten)
				ext4_ext_mark_unwritten(ex);
			eh = path[depth].p_hdr;
			nearex = ex;
			जाओ merge;
		पूर्ण
	पूर्ण

	depth = ext_depth(inode);
	eh = path[depth].p_hdr;
	अगर (le16_to_cpu(eh->eh_entries) < le16_to_cpu(eh->eh_max))
		जाओ has_space;

	/* probably next leaf has space क्रम us? */
	fex = EXT_LAST_EXTENT(eh);
	next = EXT_MAX_BLOCKS;
	अगर (le32_to_cpu(newext->ee_block) > le32_to_cpu(fex->ee_block))
		next = ext4_ext_next_leaf_block(path);
	अगर (next != EXT_MAX_BLOCKS) अणु
		ext_debug(inode, "next leaf block - %u\n", next);
		BUG_ON(npath != शून्य);
		npath = ext4_find_extent(inode, next, शून्य, gb_flags);
		अगर (IS_ERR(npath))
			वापस PTR_ERR(npath);
		BUG_ON(npath->p_depth != path->p_depth);
		eh = npath[depth].p_hdr;
		अगर (le16_to_cpu(eh->eh_entries) < le16_to_cpu(eh->eh_max)) अणु
			ext_debug(inode, "next leaf isn't full(%d)\n",
				  le16_to_cpu(eh->eh_entries));
			path = npath;
			जाओ has_space;
		पूर्ण
		ext_debug(inode, "next leaf has no free space(%d,%d)\n",
			  le16_to_cpu(eh->eh_entries), le16_to_cpu(eh->eh_max));
	पूर्ण

	/*
	 * There is no मुक्त space in the found leaf.
	 * We're gonna add a new leaf in the tree.
	 */
	अगर (gb_flags & EXT4_GET_BLOCKS_METADATA_NOFAIL)
		mb_flags |= EXT4_MB_USE_RESERVED;
	err = ext4_ext_create_new_leaf(handle, inode, mb_flags, gb_flags,
				       ppath, newext);
	अगर (err)
		जाओ cleanup;
	depth = ext_depth(inode);
	eh = path[depth].p_hdr;

has_space:
	nearex = path[depth].p_ext;

	err = ext4_ext_get_access(handle, inode, path + depth);
	अगर (err)
		जाओ cleanup;

	अगर (!nearex) अणु
		/* there is no extent in this leaf, create first one */
		ext_debug(inode, "first extent in the leaf: %u:%llu:[%d]%d\n",
				le32_to_cpu(newext->ee_block),
				ext4_ext_pblock(newext),
				ext4_ext_is_unwritten(newext),
				ext4_ext_get_actual_len(newext));
		nearex = EXT_FIRST_EXTENT(eh);
	पूर्ण अन्यथा अणु
		अगर (le32_to_cpu(newext->ee_block)
			   > le32_to_cpu(nearex->ee_block)) अणु
			/* Insert after */
			ext_debug(inode, "insert %u:%llu:[%d]%d before: "
					"nearest %p\n",
					le32_to_cpu(newext->ee_block),
					ext4_ext_pblock(newext),
					ext4_ext_is_unwritten(newext),
					ext4_ext_get_actual_len(newext),
					nearex);
			nearex++;
		पूर्ण अन्यथा अणु
			/* Insert beक्रमe */
			BUG_ON(newext->ee_block == nearex->ee_block);
			ext_debug(inode, "insert %u:%llu:[%d]%d after: "
					"nearest %p\n",
					le32_to_cpu(newext->ee_block),
					ext4_ext_pblock(newext),
					ext4_ext_is_unwritten(newext),
					ext4_ext_get_actual_len(newext),
					nearex);
		पूर्ण
		len = EXT_LAST_EXTENT(eh) - nearex + 1;
		अगर (len > 0) अणु
			ext_debug(inode, "insert %u:%llu:[%d]%d: "
					"move %d extents from 0x%p to 0x%p\n",
					le32_to_cpu(newext->ee_block),
					ext4_ext_pblock(newext),
					ext4_ext_is_unwritten(newext),
					ext4_ext_get_actual_len(newext),
					len, nearex, nearex + 1);
			स_हटाओ(nearex + 1, nearex,
				len * माप(काष्ठा ext4_extent));
		पूर्ण
	पूर्ण

	le16_add_cpu(&eh->eh_entries, 1);
	path[depth].p_ext = nearex;
	nearex->ee_block = newext->ee_block;
	ext4_ext_store_pblock(nearex, ext4_ext_pblock(newext));
	nearex->ee_len = newext->ee_len;

merge:
	/* try to merge extents */
	अगर (!(gb_flags & EXT4_GET_BLOCKS_PRE_IO))
		ext4_ext_try_to_merge(handle, inode, path, nearex);


	/* समय to correct all indexes above */
	err = ext4_ext_correct_indexes(handle, inode, path);
	अगर (err)
		जाओ cleanup;

	err = ext4_ext_dirty(handle, inode, path + path->p_depth);

cleanup:
	ext4_ext_drop_refs(npath);
	kमुक्त(npath);
	वापस err;
पूर्ण

अटल पूर्णांक ext4_fill_es_cache_info(काष्ठा inode *inode,
				   ext4_lblk_t block, ext4_lblk_t num,
				   काष्ठा fiemap_extent_info *fieinfo)
अणु
	ext4_lblk_t next, end = block + num - 1;
	काष्ठा extent_status es;
	अचिन्हित अक्षर blksize_bits = inode->i_sb->s_blocksize_bits;
	अचिन्हित पूर्णांक flags;
	पूर्णांक err;

	जबतक (block <= end) अणु
		next = 0;
		flags = 0;
		अगर (!ext4_es_lookup_extent(inode, block, &next, &es))
			अवरोध;
		अगर (ext4_es_is_unwritten(&es))
			flags |= FIEMAP_EXTENT_UNWRITTEN;
		अगर (ext4_es_is_delayed(&es))
			flags |= (FIEMAP_EXTENT_DELALLOC |
				  FIEMAP_EXTENT_UNKNOWN);
		अगर (ext4_es_is_hole(&es))
			flags |= EXT4_FIEMAP_EXTENT_HOLE;
		अगर (next == 0)
			flags |= FIEMAP_EXTENT_LAST;
		अगर (flags & (FIEMAP_EXTENT_DELALLOC|
			     EXT4_FIEMAP_EXTENT_HOLE))
			es.es_pblk = 0;
		अन्यथा
			es.es_pblk = ext4_es_pblock(&es);
		err = fiemap_fill_next_extent(fieinfo,
				(__u64)es.es_lblk << blksize_bits,
				(__u64)es.es_pblk << blksize_bits,
				(__u64)es.es_len << blksize_bits,
				flags);
		अगर (next == 0)
			अवरोध;
		block = next;
		अगर (err < 0)
			वापस err;
		अगर (err == 1)
			वापस 0;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * ext4_ext_determine_hole - determine hole around given block
 * @inode:	inode we lookup in
 * @path:	path in extent tree to @lblk
 * @lblk:	poपूर्णांकer to logical block around which we want to determine hole
 *
 * Determine hole length (and start अगर easily possible) around given logical
 * block. We करोn't try too hard to find the beginning of the hole but @path
 * actually poपूर्णांकs to extent beक्रमe @lblk, we provide it.
 *
 * The function वापसs the length of a hole starting at @lblk. We update @lblk
 * to the beginning of the hole अगर we managed to find it.
 */
अटल ext4_lblk_t ext4_ext_determine_hole(काष्ठा inode *inode,
					   काष्ठा ext4_ext_path *path,
					   ext4_lblk_t *lblk)
अणु
	पूर्णांक depth = ext_depth(inode);
	काष्ठा ext4_extent *ex;
	ext4_lblk_t len;

	ex = path[depth].p_ext;
	अगर (ex == शून्य) अणु
		/* there is no extent yet, so gap is [0;-] */
		*lblk = 0;
		len = EXT_MAX_BLOCKS;
	पूर्ण अन्यथा अगर (*lblk < le32_to_cpu(ex->ee_block)) अणु
		len = le32_to_cpu(ex->ee_block) - *lblk;
	पूर्ण अन्यथा अगर (*lblk >= le32_to_cpu(ex->ee_block)
			+ ext4_ext_get_actual_len(ex)) अणु
		ext4_lblk_t next;

		*lblk = le32_to_cpu(ex->ee_block) + ext4_ext_get_actual_len(ex);
		next = ext4_ext_next_allocated_block(path);
		BUG_ON(next == *lblk);
		len = next - *lblk;
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण
	वापस len;
पूर्ण

/*
 * ext4_ext_put_gap_in_cache:
 * calculate boundaries of the gap that the requested block fits पूर्णांकo
 * and cache this gap
 */
अटल व्योम
ext4_ext_put_gap_in_cache(काष्ठा inode *inode, ext4_lblk_t hole_start,
			  ext4_lblk_t hole_len)
अणु
	काष्ठा extent_status es;

	ext4_es_find_extent_range(inode, &ext4_es_is_delayed, hole_start,
				  hole_start + hole_len - 1, &es);
	अगर (es.es_len) अणु
		/* There's delayed extent containing lblock? */
		अगर (es.es_lblk <= hole_start)
			वापस;
		hole_len = min(es.es_lblk - hole_start, hole_len);
	पूर्ण
	ext_debug(inode, " -> %u:%u\n", hole_start, hole_len);
	ext4_es_insert_extent(inode, hole_start, hole_len, ~0,
			      EXTENT_STATUS_HOLE);
पूर्ण

/*
 * ext4_ext_rm_idx:
 * हटाओs index from the index block.
 */
अटल पूर्णांक ext4_ext_rm_idx(handle_t *handle, काष्ठा inode *inode,
			काष्ठा ext4_ext_path *path, पूर्णांक depth)
अणु
	पूर्णांक err;
	ext4_fsblk_t leaf;

	/* मुक्त index block */
	depth--;
	path = path + depth;
	leaf = ext4_idx_pblock(path->p_idx);
	अगर (unlikely(path->p_hdr->eh_entries == 0)) अणु
		EXT4_ERROR_INODE(inode, "path->p_hdr->eh_entries == 0");
		वापस -EFSCORRUPTED;
	पूर्ण
	err = ext4_ext_get_access(handle, inode, path);
	अगर (err)
		वापस err;

	अगर (path->p_idx != EXT_LAST_INDEX(path->p_hdr)) अणु
		पूर्णांक len = EXT_LAST_INDEX(path->p_hdr) - path->p_idx;
		len *= माप(काष्ठा ext4_extent_idx);
		स_हटाओ(path->p_idx, path->p_idx + 1, len);
	पूर्ण

	le16_add_cpu(&path->p_hdr->eh_entries, -1);
	err = ext4_ext_dirty(handle, inode, path);
	अगर (err)
		वापस err;
	ext_debug(inode, "index is empty, remove it, free block %llu\n", leaf);
	trace_ext4_ext_rm_idx(inode, leaf);

	ext4_मुक्त_blocks(handle, inode, शून्य, leaf, 1,
			 EXT4_FREE_BLOCKS_METADATA | EXT4_FREE_BLOCKS_FORGET);

	जबतक (--depth >= 0) अणु
		अगर (path->p_idx != EXT_FIRST_INDEX(path->p_hdr))
			अवरोध;
		path--;
		err = ext4_ext_get_access(handle, inode, path);
		अगर (err)
			अवरोध;
		path->p_idx->ei_block = (path+1)->p_idx->ei_block;
		err = ext4_ext_dirty(handle, inode, path);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/*
 * ext4_ext_calc_credits_क्रम_single_extent:
 * This routine वापसs max. credits that needed to insert an extent
 * to the extent tree.
 * When pass the actual path, the caller should calculate credits
 * under i_data_sem.
 */
पूर्णांक ext4_ext_calc_credits_क्रम_single_extent(काष्ठा inode *inode, पूर्णांक nrblocks,
						काष्ठा ext4_ext_path *path)
अणु
	अगर (path) अणु
		पूर्णांक depth = ext_depth(inode);
		पूर्णांक ret = 0;

		/* probably there is space in leaf? */
		अगर (le16_to_cpu(path[depth].p_hdr->eh_entries)
				< le16_to_cpu(path[depth].p_hdr->eh_max)) अणु

			/*
			 *  There are some space in the leaf tree, no
			 *  need to account क्रम leaf block credit
			 *
			 *  biपंचांगaps and block group descriptor blocks
			 *  and other metadata blocks still need to be
			 *  accounted.
			 */
			/* 1 biपंचांगap, 1 block group descriptor */
			ret = 2 + EXT4_META_TRANS_BLOCKS(inode->i_sb);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ext4_chunk_trans_blocks(inode, nrblocks);
पूर्ण

/*
 * How many index/leaf blocks need to change/allocate to add @extents extents?
 *
 * If we add a single extent, then in the worse हाल, each tree level
 * index/leaf need to be changed in हाल of the tree split.
 *
 * If more extents are inserted, they could cause the whole tree split more
 * than once, but this is really rare.
 */
पूर्णांक ext4_ext_index_trans_blocks(काष्ठा inode *inode, पूर्णांक extents)
अणु
	पूर्णांक index;
	पूर्णांक depth;

	/* If we are converting the अंतरभूत data, only one is needed here. */
	अगर (ext4_has_अंतरभूत_data(inode))
		वापस 1;

	depth = ext_depth(inode);

	अगर (extents <= 1)
		index = depth * 2;
	अन्यथा
		index = depth * 3;

	वापस index;
पूर्ण

अटल अंतरभूत पूर्णांक get_शेष_मुक्त_blocks_flags(काष्ठा inode *inode)
अणु
	अगर (S_ISसूची(inode->i_mode) || S_ISLNK(inode->i_mode) ||
	    ext4_test_inode_flag(inode, EXT4_INODE_EA_INODE))
		वापस EXT4_FREE_BLOCKS_METADATA | EXT4_FREE_BLOCKS_FORGET;
	अन्यथा अगर (ext4_should_journal_data(inode))
		वापस EXT4_FREE_BLOCKS_FORGET;
	वापस 0;
पूर्ण

/*
 * ext4_rereserve_cluster - increment the reserved cluster count when
 *                          मुक्तing a cluster with a pending reservation
 *
 * @inode - file containing the cluster
 * @lblk - logical block in cluster to be reserved
 *
 * Increments the reserved cluster count and adjusts quota in a bigalloc
 * file प्रणाली when मुक्तing a partial cluster containing at least one
 * delayed and unwritten block.  A partial cluster meeting that
 * requirement will have a pending reservation.  If so, the
 * RERESERVE_CLUSTER flag is used when calling ext4_मुक्त_blocks() to
 * defer reserved and allocated space accounting to a subsequent call
 * to this function.
 */
अटल व्योम ext4_rereserve_cluster(काष्ठा inode *inode, ext4_lblk_t lblk)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

	dquot_reclaim_block(inode, EXT4_C2B(sbi, 1));

	spin_lock(&ei->i_block_reservation_lock);
	ei->i_reserved_data_blocks++;
	percpu_counter_add(&sbi->s_dirtyclusters_counter, 1);
	spin_unlock(&ei->i_block_reservation_lock);

	percpu_counter_add(&sbi->s_मुक्तclusters_counter, 1);
	ext4_हटाओ_pending(inode, lblk);
पूर्ण

अटल पूर्णांक ext4_हटाओ_blocks(handle_t *handle, काष्ठा inode *inode,
			      काष्ठा ext4_extent *ex,
			      काष्ठा partial_cluster *partial,
			      ext4_lblk_t from, ext4_lblk_t to)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	अचिन्हित लघु ee_len = ext4_ext_get_actual_len(ex);
	ext4_fsblk_t last_pblk, pblk;
	ext4_lblk_t num;
	पूर्णांक flags;

	/* only extent tail removal is allowed */
	अगर (from < le32_to_cpu(ex->ee_block) ||
	    to != le32_to_cpu(ex->ee_block) + ee_len - 1) अणु
		ext4_error(sbi->s_sb,
			   "strange request: removal(2) %u-%u from %u:%u",
			   from, to, le32_to_cpu(ex->ee_block), ee_len);
		वापस 0;
	पूर्ण

#अगर_घोषित EXTENTS_STATS
	spin_lock(&sbi->s_ext_stats_lock);
	sbi->s_ext_blocks += ee_len;
	sbi->s_ext_extents++;
	अगर (ee_len < sbi->s_ext_min)
		sbi->s_ext_min = ee_len;
	अगर (ee_len > sbi->s_ext_max)
		sbi->s_ext_max = ee_len;
	अगर (ext_depth(inode) > sbi->s_depth_max)
		sbi->s_depth_max = ext_depth(inode);
	spin_unlock(&sbi->s_ext_stats_lock);
#पूर्ण_अगर

	trace_ext4_हटाओ_blocks(inode, ex, from, to, partial);

	/*
	 * अगर we have a partial cluster, and it's dअगरferent from the
	 * cluster of the last block in the extent, we मुक्त it
	 */
	last_pblk = ext4_ext_pblock(ex) + ee_len - 1;

	अगर (partial->state != initial &&
	    partial->pclu != EXT4_B2C(sbi, last_pblk)) अणु
		अगर (partial->state == toमुक्त) अणु
			flags = get_शेष_मुक्त_blocks_flags(inode);
			अगर (ext4_is_pending(inode, partial->lblk))
				flags |= EXT4_FREE_BLOCKS_RERESERVE_CLUSTER;
			ext4_मुक्त_blocks(handle, inode, शून्य,
					 EXT4_C2B(sbi, partial->pclu),
					 sbi->s_cluster_ratio, flags);
			अगर (flags & EXT4_FREE_BLOCKS_RERESERVE_CLUSTER)
				ext4_rereserve_cluster(inode, partial->lblk);
		पूर्ण
		partial->state = initial;
	पूर्ण

	num = le32_to_cpu(ex->ee_block) + ee_len - from;
	pblk = ext4_ext_pblock(ex) + ee_len - num;

	/*
	 * We मुक्त the partial cluster at the end of the extent (अगर any),
	 * unless the cluster is used by another extent (partial_cluster
	 * state is noमुक्त).  If a partial cluster exists here, it must be
	 * shared with the last block in the extent.
	 */
	flags = get_शेष_मुक्त_blocks_flags(inode);

	/* partial, left end cluster aligned, right end unaligned */
	अगर ((EXT4_LBLK_COFF(sbi, to) != sbi->s_cluster_ratio - 1) &&
	    (EXT4_LBLK_CMASK(sbi, to) >= from) &&
	    (partial->state != noमुक्त)) अणु
		अगर (ext4_is_pending(inode, to))
			flags |= EXT4_FREE_BLOCKS_RERESERVE_CLUSTER;
		ext4_मुक्त_blocks(handle, inode, शून्य,
				 EXT4_PBLK_CMASK(sbi, last_pblk),
				 sbi->s_cluster_ratio, flags);
		अगर (flags & EXT4_FREE_BLOCKS_RERESERVE_CLUSTER)
			ext4_rereserve_cluster(inode, to);
		partial->state = initial;
		flags = get_शेष_मुक्त_blocks_flags(inode);
	पूर्ण

	flags |= EXT4_FREE_BLOCKS_NOFREE_LAST_CLUSTER;

	/*
	 * For bigalloc file प्रणालीs, we never मुक्त a partial cluster
	 * at the beginning of the extent.  Instead, we check to see अगर we
	 * need to मुक्त it on a subsequent call to ext4_हटाओ_blocks,
	 * or at the end of ext4_ext_rm_leaf or ext4_ext_हटाओ_space.
	 */
	flags |= EXT4_FREE_BLOCKS_NOFREE_FIRST_CLUSTER;
	ext4_मुक्त_blocks(handle, inode, शून्य, pblk, num, flags);

	/* reset the partial cluster अगर we've मुक्तd past it */
	अगर (partial->state != initial && partial->pclu != EXT4_B2C(sbi, pblk))
		partial->state = initial;

	/*
	 * If we've मुक्तd the entire extent but the beginning is not left
	 * cluster aligned and is not marked as ineligible क्रम मुक्तing we
	 * record the partial cluster at the beginning of the extent.  It
	 * wasn't मुक्तd by the preceding ext4_मुक्त_blocks() call, and we
	 * need to look farther to the left to determine अगर it's to be मुक्तd
	 * (not shared with another extent). Else, reset the partial
	 * cluster - we're either  करोne मुक्तing or the beginning of the
	 * extent is left cluster aligned.
	 */
	अगर (EXT4_LBLK_COFF(sbi, from) && num == ee_len) अणु
		अगर (partial->state == initial) अणु
			partial->pclu = EXT4_B2C(sbi, pblk);
			partial->lblk = from;
			partial->state = toमुक्त;
		पूर्ण
	पूर्ण अन्यथा अणु
		partial->state = initial;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ext4_ext_rm_leaf() Removes the extents associated with the
 * blocks appearing between "start" and "end".  Both "start"
 * and "end" must appear in the same extent or EIO is वापसed.
 *
 * @handle: The journal handle
 * @inode:  The files inode
 * @path:   The path to the leaf
 * @partial_cluster: The cluster which we'll have to मुक्त अगर all extents
 *                   has been released from it.  However, अगर this value is
 *                   negative, it's a cluster just to the right of the
 *                   punched region and it must not be मुक्तd.
 * @start:  The first block to हटाओ
 * @end:   The last block to हटाओ
 */
अटल पूर्णांक
ext4_ext_rm_leaf(handle_t *handle, काष्ठा inode *inode,
		 काष्ठा ext4_ext_path *path,
		 काष्ठा partial_cluster *partial,
		 ext4_lblk_t start, ext4_lblk_t end)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	पूर्णांक err = 0, correct_index = 0;
	पूर्णांक depth = ext_depth(inode), credits, revoke_credits;
	काष्ठा ext4_extent_header *eh;
	ext4_lblk_t a, b;
	अचिन्हित num;
	ext4_lblk_t ex_ee_block;
	अचिन्हित लघु ex_ee_len;
	अचिन्हित unwritten = 0;
	काष्ठा ext4_extent *ex;
	ext4_fsblk_t pblk;

	/* the header must be checked alपढ़ोy in ext4_ext_हटाओ_space() */
	ext_debug(inode, "truncate since %u in leaf to %u\n", start, end);
	अगर (!path[depth].p_hdr)
		path[depth].p_hdr = ext_block_hdr(path[depth].p_bh);
	eh = path[depth].p_hdr;
	अगर (unlikely(path[depth].p_hdr == शून्य)) अणु
		EXT4_ERROR_INODE(inode, "path[%d].p_hdr == NULL", depth);
		वापस -EFSCORRUPTED;
	पूर्ण
	/* find where to start removing */
	ex = path[depth].p_ext;
	अगर (!ex)
		ex = EXT_LAST_EXTENT(eh);

	ex_ee_block = le32_to_cpu(ex->ee_block);
	ex_ee_len = ext4_ext_get_actual_len(ex);

	trace_ext4_ext_rm_leaf(inode, start, ex, partial);

	जबतक (ex >= EXT_FIRST_EXTENT(eh) &&
			ex_ee_block + ex_ee_len > start) अणु

		अगर (ext4_ext_is_unwritten(ex))
			unwritten = 1;
		अन्यथा
			unwritten = 0;

		ext_debug(inode, "remove ext %u:[%d]%d\n", ex_ee_block,
			  unwritten, ex_ee_len);
		path[depth].p_ext = ex;

		a = ex_ee_block > start ? ex_ee_block : start;
		b = ex_ee_block+ex_ee_len - 1 < end ?
			ex_ee_block+ex_ee_len - 1 : end;

		ext_debug(inode, "  border %u:%u\n", a, b);

		/* If this extent is beyond the end of the hole, skip it */
		अगर (end < ex_ee_block) अणु
			/*
			 * We're going to skip this extent and move to another,
			 * so note that its first cluster is in use to aव्योम
			 * मुक्तing it when removing blocks.  Eventually, the
			 * right edge of the truncated/punched region will
			 * be just to the left.
			 */
			अगर (sbi->s_cluster_ratio > 1) अणु
				pblk = ext4_ext_pblock(ex);
				partial->pclu = EXT4_B2C(sbi, pblk);
				partial->state = noमुक्त;
			पूर्ण
			ex--;
			ex_ee_block = le32_to_cpu(ex->ee_block);
			ex_ee_len = ext4_ext_get_actual_len(ex);
			जारी;
		पूर्ण अन्यथा अगर (b != ex_ee_block + ex_ee_len - 1) अणु
			EXT4_ERROR_INODE(inode,
					 "can not handle truncate %u:%u "
					 "on extent %u:%u",
					 start, end, ex_ee_block,
					 ex_ee_block + ex_ee_len - 1);
			err = -EFSCORRUPTED;
			जाओ out;
		पूर्ण अन्यथा अगर (a != ex_ee_block) अणु
			/* हटाओ tail of the extent */
			num = a - ex_ee_block;
		पूर्ण अन्यथा अणु
			/* हटाओ whole extent: excellent! */
			num = 0;
		पूर्ण
		/*
		 * 3 क्रम leaf, sb, and inode plus 2 (bmap and group
		 * descriptor) क्रम each block group; assume two block
		 * groups plus ex_ee_len/blocks_per_block_group क्रम
		 * the worst हाल
		 */
		credits = 7 + 2*(ex_ee_len/EXT4_BLOCKS_PER_GROUP(inode->i_sb));
		अगर (ex == EXT_FIRST_EXTENT(eh)) अणु
			correct_index = 1;
			credits += (ext_depth(inode)) + 1;
		पूर्ण
		credits += EXT4_MAXQUOTAS_TRANS_BLOCKS(inode->i_sb);
		/*
		 * We may end up मुक्तing some index blocks and data from the
		 * punched range. Note that partial clusters are accounted क्रम
		 * by ext4_मुक्त_data_revoke_credits().
		 */
		revoke_credits =
			ext4_मुक्त_metadata_revoke_credits(inode->i_sb,
							  ext_depth(inode)) +
			ext4_मुक्त_data_revoke_credits(inode, b - a + 1);

		err = ext4_datasem_ensure_credits(handle, inode, credits,
						  credits, revoke_credits);
		अगर (err) अणु
			अगर (err > 0)
				err = -EAGAIN;
			जाओ out;
		पूर्ण

		err = ext4_ext_get_access(handle, inode, path + depth);
		अगर (err)
			जाओ out;

		err = ext4_हटाओ_blocks(handle, inode, ex, partial, a, b);
		अगर (err)
			जाओ out;

		अगर (num == 0)
			/* this extent is हटाओd; mark slot entirely unused */
			ext4_ext_store_pblock(ex, 0);

		ex->ee_len = cpu_to_le16(num);
		/*
		 * Do not mark unwritten अगर all the blocks in the
		 * extent have been हटाओd.
		 */
		अगर (unwritten && num)
			ext4_ext_mark_unwritten(ex);
		/*
		 * If the extent was completely released,
		 * we need to हटाओ it from the leaf
		 */
		अगर (num == 0) अणु
			अगर (end != EXT_MAX_BLOCKS - 1) अणु
				/*
				 * For hole punching, we need to scoot all the
				 * extents up when an extent is हटाओd so that
				 * we करोnt have blank extents in the middle
				 */
				स_हटाओ(ex, ex+1, (EXT_LAST_EXTENT(eh) - ex) *
					माप(काष्ठा ext4_extent));

				/* Now get rid of the one at the end */
				स_रखो(EXT_LAST_EXTENT(eh), 0,
					माप(काष्ठा ext4_extent));
			पूर्ण
			le16_add_cpu(&eh->eh_entries, -1);
		पूर्ण

		err = ext4_ext_dirty(handle, inode, path + depth);
		अगर (err)
			जाओ out;

		ext_debug(inode, "new extent: %u:%u:%llu\n", ex_ee_block, num,
				ext4_ext_pblock(ex));
		ex--;
		ex_ee_block = le32_to_cpu(ex->ee_block);
		ex_ee_len = ext4_ext_get_actual_len(ex);
	पूर्ण

	अगर (correct_index && eh->eh_entries)
		err = ext4_ext_correct_indexes(handle, inode, path);

	/*
	 * If there's a partial cluster and at least one extent reमुख्यs in
	 * the leaf, मुक्त the partial cluster अगर it isn't shared with the
	 * current extent.  If it is shared with the current extent
	 * we reset the partial cluster because we've reached the start of the
	 * truncated/punched region and we're करोne removing blocks.
	 */
	अगर (partial->state == toमुक्त && ex >= EXT_FIRST_EXTENT(eh)) अणु
		pblk = ext4_ext_pblock(ex) + ex_ee_len - 1;
		अगर (partial->pclu != EXT4_B2C(sbi, pblk)) अणु
			पूर्णांक flags = get_शेष_मुक्त_blocks_flags(inode);

			अगर (ext4_is_pending(inode, partial->lblk))
				flags |= EXT4_FREE_BLOCKS_RERESERVE_CLUSTER;
			ext4_मुक्त_blocks(handle, inode, शून्य,
					 EXT4_C2B(sbi, partial->pclu),
					 sbi->s_cluster_ratio, flags);
			अगर (flags & EXT4_FREE_BLOCKS_RERESERVE_CLUSTER)
				ext4_rereserve_cluster(inode, partial->lblk);
		पूर्ण
		partial->state = initial;
	पूर्ण

	/* अगर this leaf is मुक्त, then we should
	 * हटाओ it from index block above */
	अगर (err == 0 && eh->eh_entries == 0 && path[depth].p_bh != शून्य)
		err = ext4_ext_rm_idx(handle, inode, path, depth);

out:
	वापस err;
पूर्ण

/*
 * ext4_ext_more_to_rm:
 * वापसs 1 अगर current index has to be मुक्तd (even partial)
 */
अटल पूर्णांक
ext4_ext_more_to_rm(काष्ठा ext4_ext_path *path)
अणु
	BUG_ON(path->p_idx == शून्य);

	अगर (path->p_idx < EXT_FIRST_INDEX(path->p_hdr))
		वापस 0;

	/*
	 * अगर truncate on deeper level happened, it wasn't partial,
	 * so we have to consider current index क्रम truncation
	 */
	अगर (le16_to_cpu(path->p_hdr->eh_entries) == path->p_block)
		वापस 0;
	वापस 1;
पूर्ण

पूर्णांक ext4_ext_हटाओ_space(काष्ठा inode *inode, ext4_lblk_t start,
			  ext4_lblk_t end)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	पूर्णांक depth = ext_depth(inode);
	काष्ठा ext4_ext_path *path = शून्य;
	काष्ठा partial_cluster partial;
	handle_t *handle;
	पूर्णांक i = 0, err = 0;

	partial.pclu = 0;
	partial.lblk = 0;
	partial.state = initial;

	ext_debug(inode, "truncate since %u to %u\n", start, end);

	/* probably first extent we're gonna मुक्त will be last in block */
	handle = ext4_journal_start_with_revoke(inode, EXT4_HT_TRUNCATE,
			depth + 1,
			ext4_मुक्त_metadata_revoke_credits(inode->i_sb, depth));
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

again:
	trace_ext4_ext_हटाओ_space(inode, start, end, depth);

	/*
	 * Check अगर we are removing extents inside the extent tree. If that
	 * is the हाल, we are going to punch a hole inside the extent tree
	 * so we have to check whether we need to split the extent covering
	 * the last block to हटाओ so we can easily हटाओ the part of it
	 * in ext4_ext_rm_leaf().
	 */
	अगर (end < EXT_MAX_BLOCKS - 1) अणु
		काष्ठा ext4_extent *ex;
		ext4_lblk_t ee_block, ex_end, lblk;
		ext4_fsblk_t pblk;

		/* find extent क्रम or बंदst extent to this block */
		path = ext4_find_extent(inode, end, शून्य,
					EXT4_EX_NOCACHE | EXT4_EX_NOFAIL);
		अगर (IS_ERR(path)) अणु
			ext4_journal_stop(handle);
			वापस PTR_ERR(path);
		पूर्ण
		depth = ext_depth(inode);
		/* Leaf not may not exist only अगर inode has no blocks at all */
		ex = path[depth].p_ext;
		अगर (!ex) अणु
			अगर (depth) अणु
				EXT4_ERROR_INODE(inode,
						 "path[%d].p_hdr == NULL",
						 depth);
				err = -EFSCORRUPTED;
			पूर्ण
			जाओ out;
		पूर्ण

		ee_block = le32_to_cpu(ex->ee_block);
		ex_end = ee_block + ext4_ext_get_actual_len(ex) - 1;

		/*
		 * See अगर the last block is inside the extent, अगर so split
		 * the extent at 'end' block so we can easily हटाओ the
		 * tail of the first part of the split extent in
		 * ext4_ext_rm_leaf().
		 */
		अगर (end >= ee_block && end < ex_end) अणु

			/*
			 * If we're going to split the extent, note that
			 * the cluster containing the block after 'end' is
			 * in use to aव्योम मुक्तing it when removing blocks.
			 */
			अगर (sbi->s_cluster_ratio > 1) अणु
				pblk = ext4_ext_pblock(ex) + end - ee_block + 1;
				partial.pclu = EXT4_B2C(sbi, pblk);
				partial.state = noमुक्त;
			पूर्ण

			/*
			 * Split the extent in two so that 'end' is the last
			 * block in the first new extent. Also we should not
			 * fail removing space due to ENOSPC so try to use
			 * reserved block अगर that happens.
			 */
			err = ext4_क्रमce_split_extent_at(handle, inode, &path,
							 end + 1, 1);
			अगर (err < 0)
				जाओ out;

		पूर्ण अन्यथा अगर (sbi->s_cluster_ratio > 1 && end >= ex_end &&
			   partial.state == initial) अणु
			/*
			 * If we're punching, there's an extent to the right.
			 * If the partial cluster hasn't been set, set it to
			 * that extent's first cluster and its state to noमुक्त
			 * so it won't be मुक्तd should it contain blocks to be
			 * हटाओd. If it's already set (tofree/nofree), we're
			 * retrying and keep the original partial cluster info
			 * so a cluster marked toमुक्त as a result of earlier
			 * extent removal is not lost.
			 */
			lblk = ex_end + 1;
			err = ext4_ext_search_right(inode, path, &lblk, &pblk,
						    शून्य);
			अगर (err < 0)
				जाओ out;
			अगर (pblk) अणु
				partial.pclu = EXT4_B2C(sbi, pblk);
				partial.state = noमुक्त;
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * We start scanning from right side, मुक्तing all the blocks
	 * after i_size and walking पूर्णांकo the tree depth-wise.
	 */
	depth = ext_depth(inode);
	अगर (path) अणु
		पूर्णांक k = i = depth;
		जबतक (--k > 0)
			path[k].p_block =
				le16_to_cpu(path[k].p_hdr->eh_entries)+1;
	पूर्ण अन्यथा अणु
		path = kसुस्मृति(depth + 1, माप(काष्ठा ext4_ext_path),
			       GFP_NOFS | __GFP_NOFAIL);
		अगर (path == शून्य) अणु
			ext4_journal_stop(handle);
			वापस -ENOMEM;
		पूर्ण
		path[0].p_maxdepth = path[0].p_depth = depth;
		path[0].p_hdr = ext_inode_hdr(inode);
		i = 0;

		अगर (ext4_ext_check(inode, path[0].p_hdr, depth, 0)) अणु
			err = -EFSCORRUPTED;
			जाओ out;
		पूर्ण
	पूर्ण
	err = 0;

	जबतक (i >= 0 && err == 0) अणु
		अगर (i == depth) अणु
			/* this is leaf block */
			err = ext4_ext_rm_leaf(handle, inode, path,
					       &partial, start, end);
			/* root level has p_bh == शून्य, brअन्यथा() eats this */
			brअन्यथा(path[i].p_bh);
			path[i].p_bh = शून्य;
			i--;
			जारी;
		पूर्ण

		/* this is index block */
		अगर (!path[i].p_hdr) अणु
			ext_debug(inode, "initialize header\n");
			path[i].p_hdr = ext_block_hdr(path[i].p_bh);
		पूर्ण

		अगर (!path[i].p_idx) अणु
			/* this level hasn't been touched yet */
			path[i].p_idx = EXT_LAST_INDEX(path[i].p_hdr);
			path[i].p_block = le16_to_cpu(path[i].p_hdr->eh_entries)+1;
			ext_debug(inode, "init index ptr: hdr 0x%p, num %d\n",
				  path[i].p_hdr,
				  le16_to_cpu(path[i].p_hdr->eh_entries));
		पूर्ण अन्यथा अणु
			/* we were alपढ़ोy here, see at next index */
			path[i].p_idx--;
		पूर्ण

		ext_debug(inode, "level %d - index, first 0x%p, cur 0x%p\n",
				i, EXT_FIRST_INDEX(path[i].p_hdr),
				path[i].p_idx);
		अगर (ext4_ext_more_to_rm(path + i)) अणु
			काष्ठा buffer_head *bh;
			/* go to the next level */
			ext_debug(inode, "move to level %d (block %llu)\n",
				  i + 1, ext4_idx_pblock(path[i].p_idx));
			स_रखो(path + i + 1, 0, माप(*path));
			bh = पढ़ो_extent_tree_block(inode,
				ext4_idx_pblock(path[i].p_idx), depth - i - 1,
				EXT4_EX_NOCACHE);
			अगर (IS_ERR(bh)) अणु
				/* should we reset i_size? */
				err = PTR_ERR(bh);
				अवरोध;
			पूर्ण
			/* Yield here to deal with large extent trees.
			 * Should be a no-op अगर we did IO above. */
			cond_resched();
			अगर (WARN_ON(i + 1 > depth)) अणु
				err = -EFSCORRUPTED;
				अवरोध;
			पूर्ण
			path[i + 1].p_bh = bh;

			/* save actual number of indexes since this
			 * number is changed at the next iteration */
			path[i].p_block = le16_to_cpu(path[i].p_hdr->eh_entries);
			i++;
		पूर्ण अन्यथा अणु
			/* we finished processing this index, go up */
			अगर (path[i].p_hdr->eh_entries == 0 && i > 0) अणु
				/* index is empty, हटाओ it;
				 * handle must be alपढ़ोy prepared by the
				 * truncatei_leaf() */
				err = ext4_ext_rm_idx(handle, inode, path, i);
			पूर्ण
			/* root level has p_bh == शून्य, brअन्यथा() eats this */
			brअन्यथा(path[i].p_bh);
			path[i].p_bh = शून्य;
			i--;
			ext_debug(inode, "return to level %d\n", i);
		पूर्ण
	पूर्ण

	trace_ext4_ext_हटाओ_space_करोne(inode, start, end, depth, &partial,
					 path->p_hdr->eh_entries);

	/*
	 * अगर there's a partial cluster and we have हटाओd the first extent
	 * in the file, then we also मुक्त the partial cluster, अगर any
	 */
	अगर (partial.state == toमुक्त && err == 0) अणु
		पूर्णांक flags = get_शेष_मुक्त_blocks_flags(inode);

		अगर (ext4_is_pending(inode, partial.lblk))
			flags |= EXT4_FREE_BLOCKS_RERESERVE_CLUSTER;
		ext4_मुक्त_blocks(handle, inode, शून्य,
				 EXT4_C2B(sbi, partial.pclu),
				 sbi->s_cluster_ratio, flags);
		अगर (flags & EXT4_FREE_BLOCKS_RERESERVE_CLUSTER)
			ext4_rereserve_cluster(inode, partial.lblk);
		partial.state = initial;
	पूर्ण

	/* TODO: flexible tree reduction should be here */
	अगर (path->p_hdr->eh_entries == 0) अणु
		/*
		 * truncate to zero मुक्तd all the tree,
		 * so we need to correct eh_depth
		 */
		err = ext4_ext_get_access(handle, inode, path);
		अगर (err == 0) अणु
			ext_inode_hdr(inode)->eh_depth = 0;
			ext_inode_hdr(inode)->eh_max =
				cpu_to_le16(ext4_ext_space_root(inode, 0));
			err = ext4_ext_dirty(handle, inode, path);
		पूर्ण
	पूर्ण
out:
	ext4_ext_drop_refs(path);
	kमुक्त(path);
	path = शून्य;
	अगर (err == -EAGAIN)
		जाओ again;
	ext4_journal_stop(handle);

	वापस err;
पूर्ण

/*
 * called at mount समय
 */
व्योम ext4_ext_init(काष्ठा super_block *sb)
अणु
	/*
	 * possible initialization would be here
	 */

	अगर (ext4_has_feature_extents(sb)) अणु
#अगर defined(AGGRESSIVE_TEST) || defined(CHECK_BINSEARCH) || defined(EXTENTS_STATS)
		prपूर्णांकk(KERN_INFO "EXT4-fs: file extents enabled"
#अगर_घोषित AGGRESSIVE_TEST
		       ", aggressive tests"
#पूर्ण_अगर
#अगर_घोषित CHECK_BINSEARCH
		       ", check binsearch"
#पूर्ण_अगर
#अगर_घोषित EXTENTS_STATS
		       ", stats"
#पूर्ण_अगर
		       "\n");
#पूर्ण_अगर
#अगर_घोषित EXTENTS_STATS
		spin_lock_init(&EXT4_SB(sb)->s_ext_stats_lock);
		EXT4_SB(sb)->s_ext_min = 1 << 30;
		EXT4_SB(sb)->s_ext_max = 0;
#पूर्ण_अगर
	पूर्ण
पूर्ण

/*
 * called at umount समय
 */
व्योम ext4_ext_release(काष्ठा super_block *sb)
अणु
	अगर (!ext4_has_feature_extents(sb))
		वापस;

#अगर_घोषित EXTENTS_STATS
	अगर (EXT4_SB(sb)->s_ext_blocks && EXT4_SB(sb)->s_ext_extents) अणु
		काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
		prपूर्णांकk(KERN_ERR "EXT4-fs: %lu blocks in %lu extents (%lu ave)\n",
			sbi->s_ext_blocks, sbi->s_ext_extents,
			sbi->s_ext_blocks / sbi->s_ext_extents);
		prपूर्णांकk(KERN_ERR "EXT4-fs: extents: %lu min, %lu max, max depth %lu\n",
			sbi->s_ext_min, sbi->s_ext_max, sbi->s_depth_max);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ext4_zeroout_es(काष्ठा inode *inode, काष्ठा ext4_extent *ex)
अणु
	ext4_lblk_t  ee_block;
	ext4_fsblk_t ee_pblock;
	अचिन्हित पूर्णांक ee_len;

	ee_block  = le32_to_cpu(ex->ee_block);
	ee_len    = ext4_ext_get_actual_len(ex);
	ee_pblock = ext4_ext_pblock(ex);

	अगर (ee_len == 0)
		वापस 0;

	वापस ext4_es_insert_extent(inode, ee_block, ee_len, ee_pblock,
				     EXTENT_STATUS_WRITTEN);
पूर्ण

/* FIXME!! we need to try to merge to left or right after zero-out  */
अटल पूर्णांक ext4_ext_zeroout(काष्ठा inode *inode, काष्ठा ext4_extent *ex)
अणु
	ext4_fsblk_t ee_pblock;
	अचिन्हित पूर्णांक ee_len;

	ee_len    = ext4_ext_get_actual_len(ex);
	ee_pblock = ext4_ext_pblock(ex);
	वापस ext4_issue_zeroout(inode, le32_to_cpu(ex->ee_block), ee_pblock,
				  ee_len);
पूर्ण

/*
 * ext4_split_extent_at() splits an extent at given block.
 *
 * @handle: the journal handle
 * @inode: the file inode
 * @path: the path to the extent
 * @split: the logical block where the extent is splitted.
 * @split_flags: indicates अगर the extent could be zeroout अगर split fails, and
 *		 the states(init or unwritten) of new extents.
 * @flags: flags used to insert new extent to extent tree.
 *
 *
 * Splits extent [a, b] पूर्णांकo two extents [a, @split) and [@split, b], states
 * of which are determined by split_flag.
 *
 * There are two हालs:
 *  a> the extent are splitted पूर्णांकo two extent.
 *  b> split is not needed, and just mark the extent.
 *
 * वापस 0 on success.
 */
अटल पूर्णांक ext4_split_extent_at(handle_t *handle,
			     काष्ठा inode *inode,
			     काष्ठा ext4_ext_path **ppath,
			     ext4_lblk_t split,
			     पूर्णांक split_flag,
			     पूर्णांक flags)
अणु
	काष्ठा ext4_ext_path *path = *ppath;
	ext4_fsblk_t newblock;
	ext4_lblk_t ee_block;
	काष्ठा ext4_extent *ex, newex, orig_ex, zero_ex;
	काष्ठा ext4_extent *ex2 = शून्य;
	अचिन्हित पूर्णांक ee_len, depth;
	पूर्णांक err = 0;

	BUG_ON((split_flag & (EXT4_EXT_DATA_VALID1 | EXT4_EXT_DATA_VALID2)) ==
	       (EXT4_EXT_DATA_VALID1 | EXT4_EXT_DATA_VALID2));

	ext_debug(inode, "logical block %llu\n", (अचिन्हित दीर्घ दीर्घ)split);

	ext4_ext_show_leaf(inode, path);

	depth = ext_depth(inode);
	ex = path[depth].p_ext;
	ee_block = le32_to_cpu(ex->ee_block);
	ee_len = ext4_ext_get_actual_len(ex);
	newblock = split - ee_block + ext4_ext_pblock(ex);

	BUG_ON(split < ee_block || split >= (ee_block + ee_len));
	BUG_ON(!ext4_ext_is_unwritten(ex) &&
	       split_flag & (EXT4_EXT_MAY_ZEROOUT |
			     EXT4_EXT_MARK_UNWRIT1 |
			     EXT4_EXT_MARK_UNWRIT2));

	err = ext4_ext_get_access(handle, inode, path + depth);
	अगर (err)
		जाओ out;

	अगर (split == ee_block) अणु
		/*
		 * हाल b: block @split is the block that the extent begins with
		 * then we just change the state of the extent, and splitting
		 * is not needed.
		 */
		अगर (split_flag & EXT4_EXT_MARK_UNWRIT2)
			ext4_ext_mark_unwritten(ex);
		अन्यथा
			ext4_ext_mark_initialized(ex);

		अगर (!(flags & EXT4_GET_BLOCKS_PRE_IO))
			ext4_ext_try_to_merge(handle, inode, path, ex);

		err = ext4_ext_dirty(handle, inode, path + path->p_depth);
		जाओ out;
	पूर्ण

	/* हाल a */
	स_नकल(&orig_ex, ex, माप(orig_ex));
	ex->ee_len = cpu_to_le16(split - ee_block);
	अगर (split_flag & EXT4_EXT_MARK_UNWRIT1)
		ext4_ext_mark_unwritten(ex);

	/*
	 * path may lead to new leaf, not to original leaf any more
	 * after ext4_ext_insert_extent() वापसs,
	 */
	err = ext4_ext_dirty(handle, inode, path + depth);
	अगर (err)
		जाओ fix_extent_len;

	ex2 = &newex;
	ex2->ee_block = cpu_to_le32(split);
	ex2->ee_len   = cpu_to_le16(ee_len - (split - ee_block));
	ext4_ext_store_pblock(ex2, newblock);
	अगर (split_flag & EXT4_EXT_MARK_UNWRIT2)
		ext4_ext_mark_unwritten(ex2);

	err = ext4_ext_insert_extent(handle, inode, ppath, &newex, flags);
	अगर (err != -ENOSPC && err != -EDQUOT)
		जाओ out;

	अगर (EXT4_EXT_MAY_ZEROOUT & split_flag) अणु
		अगर (split_flag & (EXT4_EXT_DATA_VALID1|EXT4_EXT_DATA_VALID2)) अणु
			अगर (split_flag & EXT4_EXT_DATA_VALID1) अणु
				err = ext4_ext_zeroout(inode, ex2);
				zero_ex.ee_block = ex2->ee_block;
				zero_ex.ee_len = cpu_to_le16(
						ext4_ext_get_actual_len(ex2));
				ext4_ext_store_pblock(&zero_ex,
						      ext4_ext_pblock(ex2));
			पूर्ण अन्यथा अणु
				err = ext4_ext_zeroout(inode, ex);
				zero_ex.ee_block = ex->ee_block;
				zero_ex.ee_len = cpu_to_le16(
						ext4_ext_get_actual_len(ex));
				ext4_ext_store_pblock(&zero_ex,
						      ext4_ext_pblock(ex));
			पूर्ण
		पूर्ण अन्यथा अणु
			err = ext4_ext_zeroout(inode, &orig_ex);
			zero_ex.ee_block = orig_ex.ee_block;
			zero_ex.ee_len = cpu_to_le16(
						ext4_ext_get_actual_len(&orig_ex));
			ext4_ext_store_pblock(&zero_ex,
					      ext4_ext_pblock(&orig_ex));
		पूर्ण

		अगर (!err) अणु
			/* update the extent length and mark as initialized */
			ex->ee_len = cpu_to_le16(ee_len);
			ext4_ext_try_to_merge(handle, inode, path, ex);
			err = ext4_ext_dirty(handle, inode, path + path->p_depth);
			अगर (!err)
				/* update extent status tree */
				err = ext4_zeroout_es(inode, &zero_ex);
			/* If we failed at this poपूर्णांक, we करोn't know in which
			 * state the extent tree exactly is so करोn't try to fix
			 * length of the original extent as it may करो even more
			 * damage.
			 */
			जाओ out;
		पूर्ण
	पूर्ण

fix_extent_len:
	ex->ee_len = orig_ex.ee_len;
	/*
	 * Ignore ext4_ext_dirty वापस value since we are alपढ़ोy in error path
	 * and err is a non-zero error code.
	 */
	ext4_ext_dirty(handle, inode, path + path->p_depth);
	वापस err;
out:
	ext4_ext_show_leaf(inode, path);
	वापस err;
पूर्ण

/*
 * ext4_split_extents() splits an extent and mark extent which is covered
 * by @map as split_flags indicates
 *
 * It may result in splitting the extent पूर्णांकo multiple extents (up to three)
 * There are three possibilities:
 *   a> There is no split required
 *   b> Splits in two extents: Split is happening at either end of the extent
 *   c> Splits in three extents: Somone is splitting in middle of the extent
 *
 */
अटल पूर्णांक ext4_split_extent(handle_t *handle,
			      काष्ठा inode *inode,
			      काष्ठा ext4_ext_path **ppath,
			      काष्ठा ext4_map_blocks *map,
			      पूर्णांक split_flag,
			      पूर्णांक flags)
अणु
	काष्ठा ext4_ext_path *path = *ppath;
	ext4_lblk_t ee_block;
	काष्ठा ext4_extent *ex;
	अचिन्हित पूर्णांक ee_len, depth;
	पूर्णांक err = 0;
	पूर्णांक unwritten;
	पूर्णांक split_flag1, flags1;
	पूर्णांक allocated = map->m_len;

	depth = ext_depth(inode);
	ex = path[depth].p_ext;
	ee_block = le32_to_cpu(ex->ee_block);
	ee_len = ext4_ext_get_actual_len(ex);
	unwritten = ext4_ext_is_unwritten(ex);

	अगर (map->m_lblk + map->m_len < ee_block + ee_len) अणु
		split_flag1 = split_flag & EXT4_EXT_MAY_ZEROOUT;
		flags1 = flags | EXT4_GET_BLOCKS_PRE_IO;
		अगर (unwritten)
			split_flag1 |= EXT4_EXT_MARK_UNWRIT1 |
				       EXT4_EXT_MARK_UNWRIT2;
		अगर (split_flag & EXT4_EXT_DATA_VALID2)
			split_flag1 |= EXT4_EXT_DATA_VALID1;
		err = ext4_split_extent_at(handle, inode, ppath,
				map->m_lblk + map->m_len, split_flag1, flags1);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अणु
		allocated = ee_len - (map->m_lblk - ee_block);
	पूर्ण
	/*
	 * Update path is required because previous ext4_split_extent_at() may
	 * result in split of original leaf or extent zeroout.
	 */
	path = ext4_find_extent(inode, map->m_lblk, ppath, flags);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);
	depth = ext_depth(inode);
	ex = path[depth].p_ext;
	अगर (!ex) अणु
		EXT4_ERROR_INODE(inode, "unexpected hole at %lu",
				 (अचिन्हित दीर्घ) map->m_lblk);
		वापस -EFSCORRUPTED;
	पूर्ण
	unwritten = ext4_ext_is_unwritten(ex);
	split_flag1 = 0;

	अगर (map->m_lblk >= ee_block) अणु
		split_flag1 = split_flag & EXT4_EXT_DATA_VALID2;
		अगर (unwritten) अणु
			split_flag1 |= EXT4_EXT_MARK_UNWRIT1;
			split_flag1 |= split_flag & (EXT4_EXT_MAY_ZEROOUT |
						     EXT4_EXT_MARK_UNWRIT2);
		पूर्ण
		err = ext4_split_extent_at(handle, inode, ppath,
				map->m_lblk, split_flag1, flags);
		अगर (err)
			जाओ out;
	पूर्ण

	ext4_ext_show_leaf(inode, path);
out:
	वापस err ? err : allocated;
पूर्ण

/*
 * This function is called by ext4_ext_map_blocks() अगर someone tries to ग_लिखो
 * to an unwritten extent. It may result in splitting the unwritten
 * extent पूर्णांकo multiple extents (up to three - one initialized and two
 * unwritten).
 * There are three possibilities:
 *   a> There is no split required: Entire extent should be initialized
 *   b> Splits in two extents: Write is happening at either end of the extent
 *   c> Splits in three extents: Somone is writing in middle of the extent
 *
 * Pre-conditions:
 *  - The extent poपूर्णांकed to by 'path' is unwritten.
 *  - The extent poपूर्णांकed to by 'path' contains a superset
 *    of the logical span [map->m_lblk, map->m_lblk + map->m_len).
 *
 * Post-conditions on success:
 *  - the वापसed value is the number of blocks beyond map->l_lblk
 *    that are allocated and initialized.
 *    It is guaranteed to be >= map->m_len.
 */
अटल पूर्णांक ext4_ext_convert_to_initialized(handle_t *handle,
					   काष्ठा inode *inode,
					   काष्ठा ext4_map_blocks *map,
					   काष्ठा ext4_ext_path **ppath,
					   पूर्णांक flags)
अणु
	काष्ठा ext4_ext_path *path = *ppath;
	काष्ठा ext4_sb_info *sbi;
	काष्ठा ext4_extent_header *eh;
	काष्ठा ext4_map_blocks split_map;
	काष्ठा ext4_extent zero_ex1, zero_ex2;
	काष्ठा ext4_extent *ex, *abut_ex;
	ext4_lblk_t ee_block, eof_block;
	अचिन्हित पूर्णांक ee_len, depth, map_len = map->m_len;
	पूर्णांक allocated = 0, max_zeroout = 0;
	पूर्णांक err = 0;
	पूर्णांक split_flag = EXT4_EXT_DATA_VALID2;

	ext_debug(inode, "logical block %llu, max_blocks %u\n",
		  (अचिन्हित दीर्घ दीर्घ)map->m_lblk, map_len);

	sbi = EXT4_SB(inode->i_sb);
	eof_block = (EXT4_I(inode)->i_disksize + inode->i_sb->s_blocksize - 1)
			>> inode->i_sb->s_blocksize_bits;
	अगर (eof_block < map->m_lblk + map_len)
		eof_block = map->m_lblk + map_len;

	depth = ext_depth(inode);
	eh = path[depth].p_hdr;
	ex = path[depth].p_ext;
	ee_block = le32_to_cpu(ex->ee_block);
	ee_len = ext4_ext_get_actual_len(ex);
	zero_ex1.ee_len = 0;
	zero_ex2.ee_len = 0;

	trace_ext4_ext_convert_to_initialized_enter(inode, map, ex);

	/* Pre-conditions */
	BUG_ON(!ext4_ext_is_unwritten(ex));
	BUG_ON(!in_range(map->m_lblk, ee_block, ee_len));

	/*
	 * Attempt to transfer newly initialized blocks from the currently
	 * unwritten extent to its neighbor. This is much cheaper
	 * than an insertion followed by a merge as those involve costly
	 * स_हटाओ() calls. Transferring to the left is the common हाल in
	 * steady state क्रम workloads करोing fallocate(FALLOC_FL_KEEP_SIZE)
	 * followed by append ग_लिखोs.
	 *
	 * Limitations of the current logic:
	 *  - L1: we करो not deal with ग_लिखोs covering the whole extent.
	 *    This would require removing the extent अगर the transfer
	 *    is possible.
	 *  - L2: we only attempt to merge with an extent stored in the
	 *    same extent tree node.
	 */
	अगर ((map->m_lblk == ee_block) &&
		/* See अगर we can merge left */
		(map_len < ee_len) &&		/*L1*/
		(ex > EXT_FIRST_EXTENT(eh))) अणु	/*L2*/
		ext4_lblk_t prev_lblk;
		ext4_fsblk_t prev_pblk, ee_pblk;
		अचिन्हित पूर्णांक prev_len;

		abut_ex = ex - 1;
		prev_lblk = le32_to_cpu(abut_ex->ee_block);
		prev_len = ext4_ext_get_actual_len(abut_ex);
		prev_pblk = ext4_ext_pblock(abut_ex);
		ee_pblk = ext4_ext_pblock(ex);

		/*
		 * A transfer of blocks from 'ex' to 'abut_ex' is allowed
		 * upon those conditions:
		 * - C1: abut_ex is initialized,
		 * - C2: abut_ex is logically abutting ex,
		 * - C3: abut_ex is physically abutting ex,
		 * - C4: abut_ex can receive the additional blocks without
		 *   overflowing the (initialized) length limit.
		 */
		अगर ((!ext4_ext_is_unwritten(abut_ex)) &&		/*C1*/
			((prev_lblk + prev_len) == ee_block) &&		/*C2*/
			((prev_pblk + prev_len) == ee_pblk) &&		/*C3*/
			(prev_len < (EXT_INIT_MAX_LEN - map_len))) अणु	/*C4*/
			err = ext4_ext_get_access(handle, inode, path + depth);
			अगर (err)
				जाओ out;

			trace_ext4_ext_convert_to_initialized_fastpath(inode,
				map, ex, abut_ex);

			/* Shअगरt the start of ex by 'map_len' blocks */
			ex->ee_block = cpu_to_le32(ee_block + map_len);
			ext4_ext_store_pblock(ex, ee_pblk + map_len);
			ex->ee_len = cpu_to_le16(ee_len - map_len);
			ext4_ext_mark_unwritten(ex); /* Restore the flag */

			/* Extend abut_ex by 'map_len' blocks */
			abut_ex->ee_len = cpu_to_le16(prev_len + map_len);

			/* Result: number of initialized blocks past m_lblk */
			allocated = map_len;
		पूर्ण
	पूर्ण अन्यथा अगर (((map->m_lblk + map_len) == (ee_block + ee_len)) &&
		   (map_len < ee_len) &&	/*L1*/
		   ex < EXT_LAST_EXTENT(eh)) अणु	/*L2*/
		/* See अगर we can merge right */
		ext4_lblk_t next_lblk;
		ext4_fsblk_t next_pblk, ee_pblk;
		अचिन्हित पूर्णांक next_len;

		abut_ex = ex + 1;
		next_lblk = le32_to_cpu(abut_ex->ee_block);
		next_len = ext4_ext_get_actual_len(abut_ex);
		next_pblk = ext4_ext_pblock(abut_ex);
		ee_pblk = ext4_ext_pblock(ex);

		/*
		 * A transfer of blocks from 'ex' to 'abut_ex' is allowed
		 * upon those conditions:
		 * - C1: abut_ex is initialized,
		 * - C2: abut_ex is logically abutting ex,
		 * - C3: abut_ex is physically abutting ex,
		 * - C4: abut_ex can receive the additional blocks without
		 *   overflowing the (initialized) length limit.
		 */
		अगर ((!ext4_ext_is_unwritten(abut_ex)) &&		/*C1*/
		    ((map->m_lblk + map_len) == next_lblk) &&		/*C2*/
		    ((ee_pblk + ee_len) == next_pblk) &&		/*C3*/
		    (next_len < (EXT_INIT_MAX_LEN - map_len))) अणु	/*C4*/
			err = ext4_ext_get_access(handle, inode, path + depth);
			अगर (err)
				जाओ out;

			trace_ext4_ext_convert_to_initialized_fastpath(inode,
				map, ex, abut_ex);

			/* Shअगरt the start of abut_ex by 'map_len' blocks */
			abut_ex->ee_block = cpu_to_le32(next_lblk - map_len);
			ext4_ext_store_pblock(abut_ex, next_pblk - map_len);
			ex->ee_len = cpu_to_le16(ee_len - map_len);
			ext4_ext_mark_unwritten(ex); /* Restore the flag */

			/* Extend abut_ex by 'map_len' blocks */
			abut_ex->ee_len = cpu_to_le16(next_len + map_len);

			/* Result: number of initialized blocks past m_lblk */
			allocated = map_len;
		पूर्ण
	पूर्ण
	अगर (allocated) अणु
		/* Mark the block containing both extents as dirty */
		err = ext4_ext_dirty(handle, inode, path + depth);

		/* Update path to poपूर्णांक to the right extent */
		path[depth].p_ext = abut_ex;
		जाओ out;
	पूर्ण अन्यथा
		allocated = ee_len - (map->m_lblk - ee_block);

	WARN_ON(map->m_lblk < ee_block);
	/*
	 * It is safe to convert extent to initialized via explicit
	 * zeroout only अगर extent is fully inside i_size or new_size.
	 */
	split_flag |= ee_block + ee_len <= eof_block ? EXT4_EXT_MAY_ZEROOUT : 0;

	अगर (EXT4_EXT_MAY_ZEROOUT & split_flag)
		max_zeroout = sbi->s_extent_max_zeroout_kb >>
			(inode->i_sb->s_blocksize_bits - 10);

	/*
	 * five हालs:
	 * 1. split the extent पूर्णांकo three extents.
	 * 2. split the extent पूर्णांकo two extents, zeroout the head of the first
	 *    extent.
	 * 3. split the extent पूर्णांकo two extents, zeroout the tail of the second
	 *    extent.
	 * 4. split the extent पूर्णांकo two extents with out zeroout.
	 * 5. no splitting needed, just possibly zeroout the head and / or the
	 *    tail of the extent.
	 */
	split_map.m_lblk = map->m_lblk;
	split_map.m_len = map->m_len;

	अगर (max_zeroout && (allocated > split_map.m_len)) अणु
		अगर (allocated <= max_zeroout) अणु
			/* हाल 3 or 5 */
			zero_ex1.ee_block =
				 cpu_to_le32(split_map.m_lblk +
					     split_map.m_len);
			zero_ex1.ee_len =
				cpu_to_le16(allocated - split_map.m_len);
			ext4_ext_store_pblock(&zero_ex1,
				ext4_ext_pblock(ex) + split_map.m_lblk +
				split_map.m_len - ee_block);
			err = ext4_ext_zeroout(inode, &zero_ex1);
			अगर (err)
				जाओ out;
			split_map.m_len = allocated;
		पूर्ण
		अगर (split_map.m_lblk - ee_block + split_map.m_len <
								max_zeroout) अणु
			/* हाल 2 or 5 */
			अगर (split_map.m_lblk != ee_block) अणु
				zero_ex2.ee_block = ex->ee_block;
				zero_ex2.ee_len = cpu_to_le16(split_map.m_lblk -
							ee_block);
				ext4_ext_store_pblock(&zero_ex2,
						      ext4_ext_pblock(ex));
				err = ext4_ext_zeroout(inode, &zero_ex2);
				अगर (err)
					जाओ out;
			पूर्ण

			split_map.m_len += split_map.m_lblk - ee_block;
			split_map.m_lblk = ee_block;
			allocated = map->m_len;
		पूर्ण
	पूर्ण

	err = ext4_split_extent(handle, inode, ppath, &split_map, split_flag,
				flags);
	अगर (err > 0)
		err = 0;
out:
	/* If we have gotten a failure, करोn't zero out status tree */
	अगर (!err) अणु
		err = ext4_zeroout_es(inode, &zero_ex1);
		अगर (!err)
			err = ext4_zeroout_es(inode, &zero_ex2);
	पूर्ण
	वापस err ? err : allocated;
पूर्ण

/*
 * This function is called by ext4_ext_map_blocks() from
 * ext4_get_blocks_dio_ग_लिखो() when DIO to ग_लिखो
 * to an unwritten extent.
 *
 * Writing to an unwritten extent may result in splitting the unwritten
 * extent पूर्णांकo multiple initialized/unwritten extents (up to three)
 * There are three possibilities:
 *   a> There is no split required: Entire extent should be unwritten
 *   b> Splits in two extents: Write is happening at either end of the extent
 *   c> Splits in three extents: Somone is writing in middle of the extent
 *
 * This works the same way in the हाल of initialized -> unwritten conversion.
 *
 * One of more index blocks maybe needed अगर the extent tree grow after
 * the unwritten extent split. To prevent ENOSPC occur at the IO
 * complete, we need to split the unwritten extent beक्रमe DIO submit
 * the IO. The unwritten extent called at this समय will be split
 * पूर्णांकo three unwritten extent(at most). After IO complete, the part
 * being filled will be convert to initialized by the end_io callback function
 * via ext4_convert_unwritten_extents().
 *
 * Returns the size of unwritten extent to be written on success.
 */
अटल पूर्णांक ext4_split_convert_extents(handle_t *handle,
					काष्ठा inode *inode,
					काष्ठा ext4_map_blocks *map,
					काष्ठा ext4_ext_path **ppath,
					पूर्णांक flags)
अणु
	काष्ठा ext4_ext_path *path = *ppath;
	ext4_lblk_t eof_block;
	ext4_lblk_t ee_block;
	काष्ठा ext4_extent *ex;
	अचिन्हित पूर्णांक ee_len;
	पूर्णांक split_flag = 0, depth;

	ext_debug(inode, "logical block %llu, max_blocks %u\n",
		  (अचिन्हित दीर्घ दीर्घ)map->m_lblk, map->m_len);

	eof_block = (EXT4_I(inode)->i_disksize + inode->i_sb->s_blocksize - 1)
			>> inode->i_sb->s_blocksize_bits;
	अगर (eof_block < map->m_lblk + map->m_len)
		eof_block = map->m_lblk + map->m_len;
	/*
	 * It is safe to convert extent to initialized via explicit
	 * zeroout only अगर extent is fully inside i_size or new_size.
	 */
	depth = ext_depth(inode);
	ex = path[depth].p_ext;
	ee_block = le32_to_cpu(ex->ee_block);
	ee_len = ext4_ext_get_actual_len(ex);

	/* Convert to unwritten */
	अगर (flags & EXT4_GET_BLOCKS_CONVERT_UNWRITTEN) अणु
		split_flag |= EXT4_EXT_DATA_VALID1;
	/* Convert to initialized */
	पूर्ण अन्यथा अगर (flags & EXT4_GET_BLOCKS_CONVERT) अणु
		split_flag |= ee_block + ee_len <= eof_block ?
			      EXT4_EXT_MAY_ZEROOUT : 0;
		split_flag |= (EXT4_EXT_MARK_UNWRIT2 | EXT4_EXT_DATA_VALID2);
	पूर्ण
	flags |= EXT4_GET_BLOCKS_PRE_IO;
	वापस ext4_split_extent(handle, inode, ppath, map, split_flag, flags);
पूर्ण

अटल पूर्णांक ext4_convert_unwritten_extents_endio(handle_t *handle,
						काष्ठा inode *inode,
						काष्ठा ext4_map_blocks *map,
						काष्ठा ext4_ext_path **ppath)
अणु
	काष्ठा ext4_ext_path *path = *ppath;
	काष्ठा ext4_extent *ex;
	ext4_lblk_t ee_block;
	अचिन्हित पूर्णांक ee_len;
	पूर्णांक depth;
	पूर्णांक err = 0;

	depth = ext_depth(inode);
	ex = path[depth].p_ext;
	ee_block = le32_to_cpu(ex->ee_block);
	ee_len = ext4_ext_get_actual_len(ex);

	ext_debug(inode, "logical block %llu, max_blocks %u\n",
		  (अचिन्हित दीर्घ दीर्घ)ee_block, ee_len);

	/* If extent is larger than requested it is a clear sign that we still
	 * have some extent state machine issues left. So extent_split is still
	 * required.
	 * TODO: Once all related issues will be fixed this situation should be
	 * illegal.
	 */
	अगर (ee_block != map->m_lblk || ee_len > map->m_len) अणु
#अगर_घोषित CONFIG_EXT4_DEBUG
		ext4_warning(inode->i_sb, "Inode (%ld) finished: extent logical block %llu,"
			     " len %u; IO logical block %llu, len %u",
			     inode->i_ino, (अचिन्हित दीर्घ दीर्घ)ee_block, ee_len,
			     (अचिन्हित दीर्घ दीर्घ)map->m_lblk, map->m_len);
#पूर्ण_अगर
		err = ext4_split_convert_extents(handle, inode, map, ppath,
						 EXT4_GET_BLOCKS_CONVERT);
		अगर (err < 0)
			वापस err;
		path = ext4_find_extent(inode, map->m_lblk, ppath, 0);
		अगर (IS_ERR(path))
			वापस PTR_ERR(path);
		depth = ext_depth(inode);
		ex = path[depth].p_ext;
	पूर्ण

	err = ext4_ext_get_access(handle, inode, path + depth);
	अगर (err)
		जाओ out;
	/* first mark the extent as initialized */
	ext4_ext_mark_initialized(ex);

	/* note: ext4_ext_correct_indexes() isn't needed here because
	 * borders are not changed
	 */
	ext4_ext_try_to_merge(handle, inode, path, ex);

	/* Mark modअगरied extent as dirty */
	err = ext4_ext_dirty(handle, inode, path + path->p_depth);
out:
	ext4_ext_show_leaf(inode, path);
	वापस err;
पूर्ण

अटल पूर्णांक
convert_initialized_extent(handle_t *handle, काष्ठा inode *inode,
			   काष्ठा ext4_map_blocks *map,
			   काष्ठा ext4_ext_path **ppath,
			   अचिन्हित पूर्णांक *allocated)
अणु
	काष्ठा ext4_ext_path *path = *ppath;
	काष्ठा ext4_extent *ex;
	ext4_lblk_t ee_block;
	अचिन्हित पूर्णांक ee_len;
	पूर्णांक depth;
	पूर्णांक err = 0;

	/*
	 * Make sure that the extent is no bigger than we support with
	 * unwritten extent
	 */
	अगर (map->m_len > EXT_UNWRITTEN_MAX_LEN)
		map->m_len = EXT_UNWRITTEN_MAX_LEN / 2;

	depth = ext_depth(inode);
	ex = path[depth].p_ext;
	ee_block = le32_to_cpu(ex->ee_block);
	ee_len = ext4_ext_get_actual_len(ex);

	ext_debug(inode, "logical block %llu, max_blocks %u\n",
		  (अचिन्हित दीर्घ दीर्घ)ee_block, ee_len);

	अगर (ee_block != map->m_lblk || ee_len > map->m_len) अणु
		err = ext4_split_convert_extents(handle, inode, map, ppath,
				EXT4_GET_BLOCKS_CONVERT_UNWRITTEN);
		अगर (err < 0)
			वापस err;
		path = ext4_find_extent(inode, map->m_lblk, ppath, 0);
		अगर (IS_ERR(path))
			वापस PTR_ERR(path);
		depth = ext_depth(inode);
		ex = path[depth].p_ext;
		अगर (!ex) अणु
			EXT4_ERROR_INODE(inode, "unexpected hole at %lu",
					 (अचिन्हित दीर्घ) map->m_lblk);
			वापस -EFSCORRUPTED;
		पूर्ण
	पूर्ण

	err = ext4_ext_get_access(handle, inode, path + depth);
	अगर (err)
		वापस err;
	/* first mark the extent as unwritten */
	ext4_ext_mark_unwritten(ex);

	/* note: ext4_ext_correct_indexes() isn't needed here because
	 * borders are not changed
	 */
	ext4_ext_try_to_merge(handle, inode, path, ex);

	/* Mark modअगरied extent as dirty */
	err = ext4_ext_dirty(handle, inode, path + path->p_depth);
	अगर (err)
		वापस err;
	ext4_ext_show_leaf(inode, path);

	ext4_update_inode_fsync_trans(handle, inode, 1);

	map->m_flags |= EXT4_MAP_UNWRITTEN;
	अगर (*allocated > map->m_len)
		*allocated = map->m_len;
	map->m_len = *allocated;
	वापस 0;
पूर्ण

अटल पूर्णांक
ext4_ext_handle_unwritten_extents(handle_t *handle, काष्ठा inode *inode,
			काष्ठा ext4_map_blocks *map,
			काष्ठा ext4_ext_path **ppath, पूर्णांक flags,
			अचिन्हित पूर्णांक allocated, ext4_fsblk_t newblock)
अणु
	काष्ठा ext4_ext_path __maybe_unused *path = *ppath;
	पूर्णांक ret = 0;
	पूर्णांक err = 0;

	ext_debug(inode, "logical block %llu, max_blocks %u, flags 0x%x, allocated %u\n",
		  (अचिन्हित दीर्घ दीर्घ)map->m_lblk, map->m_len, flags,
		  allocated);
	ext4_ext_show_leaf(inode, path);

	/*
	 * When writing पूर्णांकo unwritten space, we should not fail to
	 * allocate metadata blocks क्रम the new extent block अगर needed.
	 */
	flags |= EXT4_GET_BLOCKS_METADATA_NOFAIL;

	trace_ext4_ext_handle_unwritten_extents(inode, map, flags,
						    allocated, newblock);

	/* get_block() beक्रमe submitting IO, split the extent */
	अगर (flags & EXT4_GET_BLOCKS_PRE_IO) अणु
		ret = ext4_split_convert_extents(handle, inode, map, ppath,
					 flags | EXT4_GET_BLOCKS_CONVERT);
		अगर (ret < 0) अणु
			err = ret;
			जाओ out2;
		पूर्ण
		/*
		 * shouldn't get a 0 वापस when splitting an extent unless
		 * m_len is 0 (bug) or extent has been corrupted
		 */
		अगर (unlikely(ret == 0)) अणु
			EXT4_ERROR_INODE(inode,
					 "unexpected ret == 0, m_len = %u",
					 map->m_len);
			err = -EFSCORRUPTED;
			जाओ out2;
		पूर्ण
		map->m_flags |= EXT4_MAP_UNWRITTEN;
		जाओ out;
	पूर्ण
	/* IO end_io complete, convert the filled extent to written */
	अगर (flags & EXT4_GET_BLOCKS_CONVERT) अणु
		err = ext4_convert_unwritten_extents_endio(handle, inode, map,
							   ppath);
		अगर (err < 0)
			जाओ out2;
		ext4_update_inode_fsync_trans(handle, inode, 1);
		जाओ map_out;
	पूर्ण
	/* buffered IO हालs */
	/*
	 * repeat fallocate creation request
	 * we alपढ़ोy have an unwritten extent
	 */
	अगर (flags & EXT4_GET_BLOCKS_UNWRIT_EXT) अणु
		map->m_flags |= EXT4_MAP_UNWRITTEN;
		जाओ map_out;
	पूर्ण

	/* buffered READ or buffered ग_लिखो_begin() lookup */
	अगर ((flags & EXT4_GET_BLOCKS_CREATE) == 0) अणु
		/*
		 * We have blocks reserved alपढ़ोy.  We
		 * वापस allocated blocks so that delalloc
		 * won't करो block reservation क्रम us.  But
		 * the buffer head will be unmapped so that
		 * a पढ़ो from the block वापसs 0s.
		 */
		map->m_flags |= EXT4_MAP_UNWRITTEN;
		जाओ out1;
	पूर्ण

	/*
	 * Default हाल when (flags & EXT4_GET_BLOCKS_CREATE) == 1.
	 * For buffered ग_लिखोs, at ग_लिखोpage समय, etc.  Convert a
	 * discovered unwritten extent to written.
	 */
	ret = ext4_ext_convert_to_initialized(handle, inode, map, ppath, flags);
	अगर (ret < 0) अणु
		err = ret;
		जाओ out2;
	पूर्ण
	ext4_update_inode_fsync_trans(handle, inode, 1);
	/*
	 * shouldn't get a 0 वापस when converting an unwritten extent
	 * unless m_len is 0 (bug) or extent has been corrupted
	 */
	अगर (unlikely(ret == 0)) अणु
		EXT4_ERROR_INODE(inode, "unexpected ret == 0, m_len = %u",
				 map->m_len);
		err = -EFSCORRUPTED;
		जाओ out2;
	पूर्ण

out:
	allocated = ret;
	map->m_flags |= EXT4_MAP_NEW;
map_out:
	map->m_flags |= EXT4_MAP_MAPPED;
out1:
	map->m_pblk = newblock;
	अगर (allocated > map->m_len)
		allocated = map->m_len;
	map->m_len = allocated;
	ext4_ext_show_leaf(inode, path);
out2:
	वापस err ? err : allocated;
पूर्ण

/*
 * get_implied_cluster_alloc - check to see अगर the requested
 * allocation (in the map काष्ठाure) overlaps with a cluster alपढ़ोy
 * allocated in an extent.
 *	@sb	The fileप्रणाली superblock काष्ठाure
 *	@map	The requested lblk->pblk mapping
 *	@ex	The extent काष्ठाure which might contain an implied
 *			cluster allocation
 *
 * This function is called by ext4_ext_map_blocks() after we failed to
 * find blocks that were alपढ़ोy in the inode's extent tree.  Hence,
 * we know that the beginning of the requested region cannot overlap
 * the extent from the inode's extent tree.  There are three हालs we
 * want to catch.  The first is this हाल:
 *
 *		 |--- cluster # N--|
 *    |--- extent ---|	|---- requested region ---|
 *			|==========|
 *
 * The second हाल that we need to test क्रम is this one:
 *
 *   |--------- cluster # N ----------------|
 *	   |--- requested region --|   |------- extent ----|
 *	   |=======================|
 *
 * The third हाल is when the requested region lies between two extents
 * within the same cluster:
 *          |------------- cluster # N-------------|
 * |----- ex -----|                  |---- ex_right ----|
 *                  |------ requested region ------|
 *                  |================|
 *
 * In each of the above हालs, we need to set the map->m_pblk and
 * map->m_len so it corresponds to the वापस the extent labelled as
 * "|====|" from cluster #N, since it is alपढ़ोy in use क्रम data in
 * cluster EXT4_B2C(sbi, map->m_lblk).	We will then वापस 1 to
 * संकेत to ext4_ext_map_blocks() that map->m_pblk should be treated
 * as a new "allocated" block region.  Otherwise, we will वापस 0 and
 * ext4_ext_map_blocks() will then allocate one or more new clusters
 * by calling ext4_mb_new_blocks().
 */
अटल पूर्णांक get_implied_cluster_alloc(काष्ठा super_block *sb,
				     काष्ठा ext4_map_blocks *map,
				     काष्ठा ext4_extent *ex,
				     काष्ठा ext4_ext_path *path)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_lblk_t c_offset = EXT4_LBLK_COFF(sbi, map->m_lblk);
	ext4_lblk_t ex_cluster_start, ex_cluster_end;
	ext4_lblk_t rr_cluster_start;
	ext4_lblk_t ee_block = le32_to_cpu(ex->ee_block);
	ext4_fsblk_t ee_start = ext4_ext_pblock(ex);
	अचिन्हित लघु ee_len = ext4_ext_get_actual_len(ex);

	/* The extent passed in that we are trying to match */
	ex_cluster_start = EXT4_B2C(sbi, ee_block);
	ex_cluster_end = EXT4_B2C(sbi, ee_block + ee_len - 1);

	/* The requested region passed पूर्णांकo ext4_map_blocks() */
	rr_cluster_start = EXT4_B2C(sbi, map->m_lblk);

	अगर ((rr_cluster_start == ex_cluster_end) ||
	    (rr_cluster_start == ex_cluster_start)) अणु
		अगर (rr_cluster_start == ex_cluster_end)
			ee_start += ee_len - 1;
		map->m_pblk = EXT4_PBLK_CMASK(sbi, ee_start) + c_offset;
		map->m_len = min(map->m_len,
				 (अचिन्हित) sbi->s_cluster_ratio - c_offset);
		/*
		 * Check क्रम and handle this हाल:
		 *
		 *   |--------- cluster # N-------------|
		 *		       |------- extent ----|
		 *	   |--- requested region ---|
		 *	   |===========|
		 */

		अगर (map->m_lblk < ee_block)
			map->m_len = min(map->m_len, ee_block - map->m_lblk);

		/*
		 * Check क्रम the हाल where there is alपढ़ोy another allocated
		 * block to the right of 'ex' but beक्रमe the end of the cluster.
		 *
		 *          |------------- cluster # N-------------|
		 * |----- ex -----|                  |---- ex_right ----|
		 *                  |------ requested region ------|
		 *                  |================|
		 */
		अगर (map->m_lblk > ee_block) अणु
			ext4_lblk_t next = ext4_ext_next_allocated_block(path);
			map->m_len = min(map->m_len, next - map->m_lblk);
		पूर्ण

		trace_ext4_get_implied_cluster_alloc_निकास(sb, map, 1);
		वापस 1;
	पूर्ण

	trace_ext4_get_implied_cluster_alloc_निकास(sb, map, 0);
	वापस 0;
पूर्ण


/*
 * Block allocation/map/pपुनः_स्मृतिation routine क्रम extents based files
 *
 *
 * Need to be called with
 * करोwn_पढ़ो(&EXT4_I(inode)->i_data_sem) अगर not allocating file प्रणाली block
 * (ie, create is zero). Otherwise करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem)
 *
 * वापस > 0, number of blocks alपढ़ोy mapped/allocated
 *          अगर create == 0 and these are pre-allocated blocks
 *          	buffer head is unmapped
 *          otherwise blocks are mapped
 *
 * वापस = 0, अगर plain look up failed (blocks have not been allocated)
 *          buffer head is unmapped
 *
 * वापस < 0, error हाल.
 */
पूर्णांक ext4_ext_map_blocks(handle_t *handle, काष्ठा inode *inode,
			काष्ठा ext4_map_blocks *map, पूर्णांक flags)
अणु
	काष्ठा ext4_ext_path *path = शून्य;
	काष्ठा ext4_extent newex, *ex, ex2;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	ext4_fsblk_t newblock = 0, pblk;
	पूर्णांक err = 0, depth, ret;
	अचिन्हित पूर्णांक allocated = 0, offset = 0;
	अचिन्हित पूर्णांक allocated_clusters = 0;
	काष्ठा ext4_allocation_request ar;
	ext4_lblk_t cluster_offset;

	ext_debug(inode, "blocks %u/%u requested\n", map->m_lblk, map->m_len);
	trace_ext4_ext_map_blocks_enter(inode, map->m_lblk, map->m_len, flags);

	/* find extent क्रम this block */
	path = ext4_find_extent(inode, map->m_lblk, शून्य, 0);
	अगर (IS_ERR(path)) अणु
		err = PTR_ERR(path);
		path = शून्य;
		जाओ out;
	पूर्ण

	depth = ext_depth(inode);

	/*
	 * consistent leaf must not be empty;
	 * this situation is possible, though, _during_ tree modअगरication;
	 * this is why निश्चित can't be put in ext4_find_extent()
	 */
	अगर (unlikely(path[depth].p_ext == शून्य && depth != 0)) अणु
		EXT4_ERROR_INODE(inode, "bad extent address "
				 "lblock: %lu, depth: %d pblock %lld",
				 (अचिन्हित दीर्घ) map->m_lblk, depth,
				 path[depth].p_block);
		err = -EFSCORRUPTED;
		जाओ out;
	पूर्ण

	ex = path[depth].p_ext;
	अगर (ex) अणु
		ext4_lblk_t ee_block = le32_to_cpu(ex->ee_block);
		ext4_fsblk_t ee_start = ext4_ext_pblock(ex);
		अचिन्हित लघु ee_len;


		/*
		 * unwritten extents are treated as holes, except that
		 * we split out initialized portions during a ग_लिखो.
		 */
		ee_len = ext4_ext_get_actual_len(ex);

		trace_ext4_ext_show_extent(inode, ee_block, ee_start, ee_len);

		/* अगर found extent covers block, simply वापस it */
		अगर (in_range(map->m_lblk, ee_block, ee_len)) अणु
			newblock = map->m_lblk - ee_block + ee_start;
			/* number of reमुख्यing blocks in the extent */
			allocated = ee_len - (map->m_lblk - ee_block);
			ext_debug(inode, "%u fit into %u:%d -> %llu\n",
				  map->m_lblk, ee_block, ee_len, newblock);

			/*
			 * If the extent is initialized check whether the
			 * caller wants to convert it to unwritten.
			 */
			अगर ((!ext4_ext_is_unwritten(ex)) &&
			    (flags & EXT4_GET_BLOCKS_CONVERT_UNWRITTEN)) अणु
				err = convert_initialized_extent(handle,
					inode, map, &path, &allocated);
				जाओ out;
			पूर्ण अन्यथा अगर (!ext4_ext_is_unwritten(ex)) अणु
				map->m_flags |= EXT4_MAP_MAPPED;
				map->m_pblk = newblock;
				अगर (allocated > map->m_len)
					allocated = map->m_len;
				map->m_len = allocated;
				ext4_ext_show_leaf(inode, path);
				जाओ out;
			पूर्ण

			ret = ext4_ext_handle_unwritten_extents(
				handle, inode, map, &path, flags,
				allocated, newblock);
			अगर (ret < 0)
				err = ret;
			अन्यथा
				allocated = ret;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * requested block isn't allocated yet;
	 * we couldn't try to create block अगर create flag is zero
	 */
	अगर ((flags & EXT4_GET_BLOCKS_CREATE) == 0) अणु
		ext4_lblk_t hole_start, hole_len;

		hole_start = map->m_lblk;
		hole_len = ext4_ext_determine_hole(inode, path, &hole_start);
		/*
		 * put just found gap पूर्णांकo cache to speed up
		 * subsequent requests
		 */
		ext4_ext_put_gap_in_cache(inode, hole_start, hole_len);

		/* Update hole_len to reflect hole size after map->m_lblk */
		अगर (hole_start != map->m_lblk)
			hole_len -= map->m_lblk - hole_start;
		map->m_pblk = 0;
		map->m_len = min_t(अचिन्हित पूर्णांक, map->m_len, hole_len);

		जाओ out;
	पूर्ण

	/*
	 * Okay, we need to करो block allocation.
	 */
	newex.ee_block = cpu_to_le32(map->m_lblk);
	cluster_offset = EXT4_LBLK_COFF(sbi, map->m_lblk);

	/*
	 * If we are करोing bigalloc, check to see अगर the extent वापसed
	 * by ext4_find_extent() implies a cluster we can use.
	 */
	अगर (cluster_offset && ex &&
	    get_implied_cluster_alloc(inode->i_sb, map, ex, path)) अणु
		ar.len = allocated = map->m_len;
		newblock = map->m_pblk;
		जाओ got_allocated_blocks;
	पूर्ण

	/* find neighbour allocated blocks */
	ar.lleft = map->m_lblk;
	err = ext4_ext_search_left(inode, path, &ar.lleft, &ar.pleft);
	अगर (err)
		जाओ out;
	ar.lright = map->m_lblk;
	err = ext4_ext_search_right(inode, path, &ar.lright, &ar.pright, &ex2);
	अगर (err < 0)
		जाओ out;

	/* Check अगर the extent after searching to the right implies a
	 * cluster we can use. */
	अगर ((sbi->s_cluster_ratio > 1) && err &&
	    get_implied_cluster_alloc(inode->i_sb, map, &ex2, path)) अणु
		ar.len = allocated = map->m_len;
		newblock = map->m_pblk;
		जाओ got_allocated_blocks;
	पूर्ण

	/*
	 * See अगर request is beyond maximum number of blocks we can have in
	 * a single extent. For an initialized extent this limit is
	 * EXT_INIT_MAX_LEN and क्रम an unwritten extent this limit is
	 * EXT_UNWRITTEN_MAX_LEN.
	 */
	अगर (map->m_len > EXT_INIT_MAX_LEN &&
	    !(flags & EXT4_GET_BLOCKS_UNWRIT_EXT))
		map->m_len = EXT_INIT_MAX_LEN;
	अन्यथा अगर (map->m_len > EXT_UNWRITTEN_MAX_LEN &&
		 (flags & EXT4_GET_BLOCKS_UNWRIT_EXT))
		map->m_len = EXT_UNWRITTEN_MAX_LEN;

	/* Check अगर we can really insert (m_lblk)::(m_lblk + m_len) extent */
	newex.ee_len = cpu_to_le16(map->m_len);
	err = ext4_ext_check_overlap(sbi, inode, &newex, path);
	अगर (err)
		allocated = ext4_ext_get_actual_len(&newex);
	अन्यथा
		allocated = map->m_len;

	/* allocate new block */
	ar.inode = inode;
	ar.goal = ext4_ext_find_goal(inode, path, map->m_lblk);
	ar.logical = map->m_lblk;
	/*
	 * We calculate the offset from the beginning of the cluster
	 * क्रम the logical block number, since when we allocate a
	 * physical cluster, the physical block should start at the
	 * same offset from the beginning of the cluster.  This is
	 * needed so that future calls to get_implied_cluster_alloc()
	 * work correctly.
	 */
	offset = EXT4_LBLK_COFF(sbi, map->m_lblk);
	ar.len = EXT4_NUM_B2C(sbi, offset+allocated);
	ar.goal -= offset;
	ar.logical -= offset;
	अगर (S_ISREG(inode->i_mode))
		ar.flags = EXT4_MB_HINT_DATA;
	अन्यथा
		/* disable in-core pपुनः_स्मृतिation क्रम non-regular files */
		ar.flags = 0;
	अगर (flags & EXT4_GET_BLOCKS_NO_NORMALIZE)
		ar.flags |= EXT4_MB_HINT_NOPREALLOC;
	अगर (flags & EXT4_GET_BLOCKS_DELALLOC_RESERVE)
		ar.flags |= EXT4_MB_DELALLOC_RESERVED;
	अगर (flags & EXT4_GET_BLOCKS_METADATA_NOFAIL)
		ar.flags |= EXT4_MB_USE_RESERVED;
	newblock = ext4_mb_new_blocks(handle, &ar, &err);
	अगर (!newblock)
		जाओ out;
	allocated_clusters = ar.len;
	ar.len = EXT4_C2B(sbi, ar.len) - offset;
	ext_debug(inode, "allocate new block: goal %llu, found %llu/%u, requested %u\n",
		  ar.goal, newblock, ar.len, allocated);
	अगर (ar.len > allocated)
		ar.len = allocated;

got_allocated_blocks:
	/* try to insert new extent पूर्णांकo found leaf and वापस */
	pblk = newblock + offset;
	ext4_ext_store_pblock(&newex, pblk);
	newex.ee_len = cpu_to_le16(ar.len);
	/* Mark unwritten */
	अगर (flags & EXT4_GET_BLOCKS_UNWRIT_EXT) अणु
		ext4_ext_mark_unwritten(&newex);
		map->m_flags |= EXT4_MAP_UNWRITTEN;
	पूर्ण

	err = ext4_ext_insert_extent(handle, inode, &path, &newex, flags);
	अगर (err) अणु
		अगर (allocated_clusters) अणु
			पूर्णांक fb_flags = 0;

			/*
			 * मुक्त data blocks we just allocated.
			 * not a good idea to call discard here directly,
			 * but otherwise we'd need to call it every मुक्त().
			 */
			ext4_discard_pपुनः_स्मृतिations(inode, 0);
			अगर (flags & EXT4_GET_BLOCKS_DELALLOC_RESERVE)
				fb_flags = EXT4_FREE_BLOCKS_NO_QUOT_UPDATE;
			ext4_मुक्त_blocks(handle, inode, शून्य, newblock,
					 EXT4_C2B(sbi, allocated_clusters),
					 fb_flags);
		पूर्ण
		जाओ out;
	पूर्ण

	/*
	 * Reduce the reserved cluster count to reflect successful deferred
	 * allocation of delayed allocated clusters or direct allocation of
	 * clusters discovered to be delayed allocated.  Once allocated, a
	 * cluster is not included in the reserved count.
	 */
	अगर (test_opt(inode->i_sb, DELALLOC) && allocated_clusters) अणु
		अगर (flags & EXT4_GET_BLOCKS_DELALLOC_RESERVE) अणु
			/*
			 * When allocating delayed allocated clusters, simply
			 * reduce the reserved cluster count and claim quota
			 */
			ext4_da_update_reserve_space(inode, allocated_clusters,
							1);
		पूर्ण अन्यथा अणु
			ext4_lblk_t lblk, len;
			अचिन्हित पूर्णांक n;

			/*
			 * When allocating non-delayed allocated clusters
			 * (from fallocate, filemap, DIO, or clusters
			 * allocated when delalloc has been disabled by
			 * ext4_nonda_चयन), reduce the reserved cluster
			 * count by the number of allocated clusters that
			 * have previously been delayed allocated.  Quota
			 * has been claimed by ext4_mb_new_blocks() above,
			 * so release the quota reservations made क्रम any
			 * previously delayed allocated clusters.
			 */
			lblk = EXT4_LBLK_CMASK(sbi, map->m_lblk);
			len = allocated_clusters << sbi->s_cluster_bits;
			n = ext4_es_delayed_clu(inode, lblk, len);
			अगर (n > 0)
				ext4_da_update_reserve_space(inode, (पूर्णांक) n, 0);
		पूर्ण
	पूर्ण

	/*
	 * Cache the extent and update transaction to commit on fdatasync only
	 * when it is _not_ an unwritten extent.
	 */
	अगर ((flags & EXT4_GET_BLOCKS_UNWRIT_EXT) == 0)
		ext4_update_inode_fsync_trans(handle, inode, 1);
	अन्यथा
		ext4_update_inode_fsync_trans(handle, inode, 0);

	map->m_flags |= (EXT4_MAP_NEW | EXT4_MAP_MAPPED);
	map->m_pblk = pblk;
	map->m_len = ar.len;
	allocated = map->m_len;
	ext4_ext_show_leaf(inode, path);
out:
	ext4_ext_drop_refs(path);
	kमुक्त(path);

	trace_ext4_ext_map_blocks_निकास(inode, flags, map,
				       err ? err : allocated);
	वापस err ? err : allocated;
पूर्ण

पूर्णांक ext4_ext_truncate(handle_t *handle, काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	ext4_lblk_t last_block;
	पूर्णांक err = 0;

	/*
	 * TODO: optimization is possible here.
	 * Probably we need not scan at all,
	 * because page truncation is enough.
	 */

	/* we have to know where to truncate from in crash हाल */
	EXT4_I(inode)->i_disksize = inode->i_size;
	err = ext4_mark_inode_dirty(handle, inode);
	अगर (err)
		वापस err;

	last_block = (inode->i_size + sb->s_blocksize - 1)
			>> EXT4_BLOCK_SIZE_BITS(sb);
retry:
	err = ext4_es_हटाओ_extent(inode, last_block,
				    EXT_MAX_BLOCKS - last_block);
	अगर (err == -ENOMEM) अणु
		cond_resched();
		congestion_रुको(BLK_RW_ASYNC, HZ/50);
		जाओ retry;
	पूर्ण
	अगर (err)
		वापस err;
retry_हटाओ_space:
	err = ext4_ext_हटाओ_space(inode, last_block, EXT_MAX_BLOCKS - 1);
	अगर (err == -ENOMEM) अणु
		cond_resched();
		congestion_रुको(BLK_RW_ASYNC, HZ/50);
		जाओ retry_हटाओ_space;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ext4_alloc_file_blocks(काष्ठा file *file, ext4_lblk_t offset,
				  ext4_lblk_t len, loff_t new_size,
				  पूर्णांक flags)
अणु
	काष्ठा inode *inode = file_inode(file);
	handle_t *handle;
	पूर्णांक ret = 0, ret2 = 0, ret3 = 0;
	पूर्णांक retries = 0;
	पूर्णांक depth = 0;
	काष्ठा ext4_map_blocks map;
	अचिन्हित पूर्णांक credits;
	loff_t epos;

	BUG_ON(!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS));
	map.m_lblk = offset;
	map.m_len = len;
	/*
	 * Don't normalize the request अगर it can fit in one extent so
	 * that it करोesn't get unnecessarily split पूर्णांकo multiple
	 * extents.
	 */
	अगर (len <= EXT_UNWRITTEN_MAX_LEN)
		flags |= EXT4_GET_BLOCKS_NO_NORMALIZE;

	/*
	 * credits to insert 1 extent पूर्णांकo extent tree
	 */
	credits = ext4_chunk_trans_blocks(inode, len);
	depth = ext_depth(inode);

retry:
	जबतक (len) अणु
		/*
		 * Recalculate credits when extent tree depth changes.
		 */
		अगर (depth != ext_depth(inode)) अणु
			credits = ext4_chunk_trans_blocks(inode, len);
			depth = ext_depth(inode);
		पूर्ण

		handle = ext4_journal_start(inode, EXT4_HT_MAP_BLOCKS,
					    credits);
		अगर (IS_ERR(handle)) अणु
			ret = PTR_ERR(handle);
			अवरोध;
		पूर्ण
		ret = ext4_map_blocks(handle, inode, &map, flags);
		अगर (ret <= 0) अणु
			ext4_debug("inode #%lu: block %u: len %u: "
				   "ext4_ext_map_blocks returned %d",
				   inode->i_ino, map.m_lblk,
				   map.m_len, ret);
			ext4_mark_inode_dirty(handle, inode);
			ext4_journal_stop(handle);
			अवरोध;
		पूर्ण
		/*
		 * allow a full retry cycle क्रम any reमुख्यing allocations
		 */
		retries = 0;
		map.m_lblk += ret;
		map.m_len = len = len - ret;
		epos = (loff_t)map.m_lblk << inode->i_blkbits;
		inode->i_स_समय = current_समय(inode);
		अगर (new_size) अणु
			अगर (epos > new_size)
				epos = new_size;
			अगर (ext4_update_inode_size(inode, epos) & 0x1)
				inode->i_mसमय = inode->i_स_समय;
		पूर्ण
		ret2 = ext4_mark_inode_dirty(handle, inode);
		ext4_update_inode_fsync_trans(handle, inode, 1);
		ret3 = ext4_journal_stop(handle);
		ret2 = ret3 ? ret3 : ret2;
		अगर (unlikely(ret2))
			अवरोध;
	पूर्ण
	अगर (ret == -ENOSPC && ext4_should_retry_alloc(inode->i_sb, &retries))
		जाओ retry;

	वापस ret > 0 ? ret2 : ret;
पूर्ण

अटल पूर्णांक ext4_collapse_range(काष्ठा inode *inode, loff_t offset, loff_t len);

अटल पूर्णांक ext4_insert_range(काष्ठा inode *inode, loff_t offset, loff_t len);

अटल दीर्घ ext4_zero_range(काष्ठा file *file, loff_t offset,
			    loff_t len, पूर्णांक mode)
अणु
	काष्ठा inode *inode = file_inode(file);
	handle_t *handle = शून्य;
	अचिन्हित पूर्णांक max_blocks;
	loff_t new_size = 0;
	पूर्णांक ret = 0;
	पूर्णांक flags;
	पूर्णांक credits;
	पूर्णांक partial_begin, partial_end;
	loff_t start, end;
	ext4_lblk_t lblk;
	अचिन्हित पूर्णांक blkbits = inode->i_blkbits;

	trace_ext4_zero_range(inode, offset, len, mode);

	/* Call ext4_क्रमce_commit to flush all data in हाल of data=journal. */
	अगर (ext4_should_journal_data(inode)) अणु
		ret = ext4_क्रमce_commit(inode->i_sb);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Round up offset. This is not fallocate, we need to zero out
	 * blocks, so convert पूर्णांकerior block aligned part of the range to
	 * unwritten and possibly manually zero out unaligned parts of the
	 * range.
	 */
	start = round_up(offset, 1 << blkbits);
	end = round_करोwn((offset + len), 1 << blkbits);

	अगर (start < offset || end > offset + len)
		वापस -EINVAL;
	partial_begin = offset & ((1 << blkbits) - 1);
	partial_end = (offset + len) & ((1 << blkbits) - 1);

	lblk = start >> blkbits;
	max_blocks = (end >> blkbits);
	अगर (max_blocks < lblk)
		max_blocks = 0;
	अन्यथा
		max_blocks -= lblk;

	inode_lock(inode);

	/*
	 * Indirect files करो not support unwritten extents
	 */
	अगर (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))) अणु
		ret = -EOPNOTSUPP;
		जाओ out_mutex;
	पूर्ण

	अगर (!(mode & FALLOC_FL_KEEP_SIZE) &&
	    (offset + len > inode->i_size ||
	     offset + len > EXT4_I(inode)->i_disksize)) अणु
		new_size = offset + len;
		ret = inode_newsize_ok(inode, new_size);
		अगर (ret)
			जाओ out_mutex;
	पूर्ण

	flags = EXT4_GET_BLOCKS_CREATE_UNWRIT_EXT;

	/* Wait all existing dio workers, newcomers will block on i_mutex */
	inode_dio_रुको(inode);

	/* Pपुनः_स्मृतिate the range including the unaligned edges */
	अगर (partial_begin || partial_end) अणु
		ret = ext4_alloc_file_blocks(file,
				round_करोwn(offset, 1 << blkbits) >> blkbits,
				(round_up((offset + len), 1 << blkbits) -
				 round_करोwn(offset, 1 << blkbits)) >> blkbits,
				new_size, flags);
		अगर (ret)
			जाओ out_mutex;

	पूर्ण

	/* Zero range excluding the unaligned edges */
	अगर (max_blocks > 0) अणु
		flags |= (EXT4_GET_BLOCKS_CONVERT_UNWRITTEN |
			  EXT4_EX_NOCACHE);

		/*
		 * Prevent page faults from reinstantiating pages we have
		 * released from page cache.
		 */
		करोwn_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);

		ret = ext4_अवरोध_layouts(inode);
		अगर (ret) अणु
			up_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
			जाओ out_mutex;
		पूर्ण

		ret = ext4_update_disksize_beक्रमe_punch(inode, offset, len);
		अगर (ret) अणु
			up_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
			जाओ out_mutex;
		पूर्ण
		/* Now release the pages and zero block aligned part of pages */
		truncate_pagecache_range(inode, start, end - 1);
		inode->i_mसमय = inode->i_स_समय = current_समय(inode);

		ret = ext4_alloc_file_blocks(file, lblk, max_blocks, new_size,
					     flags);
		up_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
		अगर (ret)
			जाओ out_mutex;
	पूर्ण
	अगर (!partial_begin && !partial_end)
		जाओ out_mutex;

	/*
	 * In worst हाल we have to ग_लिखोout two nonadjacent unwritten
	 * blocks and update the inode
	 */
	credits = (2 * ext4_ext_index_trans_blocks(inode, 2)) + 1;
	अगर (ext4_should_journal_data(inode))
		credits += 2;
	handle = ext4_journal_start(inode, EXT4_HT_MISC, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		ext4_std_error(inode->i_sb, ret);
		जाओ out_mutex;
	पूर्ण

	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	अगर (new_size)
		ext4_update_inode_size(inode, new_size);
	ret = ext4_mark_inode_dirty(handle, inode);
	अगर (unlikely(ret))
		जाओ out_handle;
	ext4_fc_track_range(handle, inode, offset >> inode->i_sb->s_blocksize_bits,
			(offset + len - 1) >> inode->i_sb->s_blocksize_bits);
	/* Zero out partial block at the edges of the range */
	ret = ext4_zero_partial_blocks(handle, inode, offset, len);
	अगर (ret >= 0)
		ext4_update_inode_fsync_trans(handle, inode, 1);

	अगर (file->f_flags & O_SYNC)
		ext4_handle_sync(handle);

out_handle:
	ext4_journal_stop(handle);
out_mutex:
	inode_unlock(inode);
	वापस ret;
पूर्ण

/*
 * pपुनः_स्मृतिate space क्रम a file. This implements ext4's fallocate file
 * operation, which माला_लो called from sys_fallocate प्रणाली call.
 * For block-mapped files, posix_fallocate should fall back to the method
 * of writing zeroes to the required new blocks (the same behavior which is
 * expected क्रम file प्रणालीs which करो not support fallocate() प्रणाली call).
 */
दीर्घ ext4_fallocate(काष्ठा file *file, पूर्णांक mode, loff_t offset, loff_t len)
अणु
	काष्ठा inode *inode = file_inode(file);
	loff_t new_size = 0;
	अचिन्हित पूर्णांक max_blocks;
	पूर्णांक ret = 0;
	पूर्णांक flags;
	ext4_lblk_t lblk;
	अचिन्हित पूर्णांक blkbits = inode->i_blkbits;

	/*
	 * Encrypted inodes can't handle collapse range or insert
	 * range since we would need to re-encrypt blocks with a
	 * dअगरferent IV or XTS tweak (which are based on the logical
	 * block number).
	 */
	अगर (IS_ENCRYPTED(inode) &&
	    (mode & (FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_INSERT_RANGE)))
		वापस -EOPNOTSUPP;

	/* Return error अगर mode is not supported */
	अगर (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE |
		     FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE |
		     FALLOC_FL_INSERT_RANGE))
		वापस -EOPNOTSUPP;

	ext4_fc_start_update(inode);

	अगर (mode & FALLOC_FL_PUNCH_HOLE) अणु
		ret = ext4_punch_hole(inode, offset, len);
		जाओ निकास;
	पूर्ण

	ret = ext4_convert_अंतरभूत_data(inode);
	अगर (ret)
		जाओ निकास;

	अगर (mode & FALLOC_FL_COLLAPSE_RANGE) अणु
		ret = ext4_collapse_range(inode, offset, len);
		जाओ निकास;
	पूर्ण

	अगर (mode & FALLOC_FL_INSERT_RANGE) अणु
		ret = ext4_insert_range(inode, offset, len);
		जाओ निकास;
	पूर्ण

	अगर (mode & FALLOC_FL_ZERO_RANGE) अणु
		ret = ext4_zero_range(file, offset, len, mode);
		जाओ निकास;
	पूर्ण
	trace_ext4_fallocate_enter(inode, offset, len, mode);
	lblk = offset >> blkbits;

	max_blocks = EXT4_MAX_BLOCKS(len, offset, blkbits);
	flags = EXT4_GET_BLOCKS_CREATE_UNWRIT_EXT;

	inode_lock(inode);

	/*
	 * We only support pपुनः_स्मृतिation क्रम extent-based files only
	 */
	अगर (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (!(mode & FALLOC_FL_KEEP_SIZE) &&
	    (offset + len > inode->i_size ||
	     offset + len > EXT4_I(inode)->i_disksize)) अणु
		new_size = offset + len;
		ret = inode_newsize_ok(inode, new_size);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* Wait all existing dio workers, newcomers will block on i_mutex */
	inode_dio_रुको(inode);

	ret = ext4_alloc_file_blocks(file, lblk, max_blocks, new_size, flags);
	अगर (ret)
		जाओ out;

	अगर (file->f_flags & O_SYNC && EXT4_SB(inode->i_sb)->s_journal) अणु
		ret = ext4_fc_commit(EXT4_SB(inode->i_sb)->s_journal,
					EXT4_I(inode)->i_sync_tid);
	पूर्ण
out:
	inode_unlock(inode);
	trace_ext4_fallocate_निकास(inode, offset, max_blocks, ret);
निकास:
	ext4_fc_stop_update(inode);
	वापस ret;
पूर्ण

/*
 * This function convert a range of blocks to written extents
 * The caller of this function will pass the start offset and the size.
 * all unwritten extents within this range will be converted to
 * written extents.
 *
 * This function is called from the direct IO end io call back
 * function, to convert the fallocated extents after IO is completed.
 * Returns 0 on success.
 */
पूर्णांक ext4_convert_unwritten_extents(handle_t *handle, काष्ठा inode *inode,
				   loff_t offset, sमाप_प्रकार len)
अणु
	अचिन्हित पूर्णांक max_blocks;
	पूर्णांक ret = 0, ret2 = 0, ret3 = 0;
	काष्ठा ext4_map_blocks map;
	अचिन्हित पूर्णांक blkbits = inode->i_blkbits;
	अचिन्हित पूर्णांक credits = 0;

	map.m_lblk = offset >> blkbits;
	max_blocks = EXT4_MAX_BLOCKS(len, offset, blkbits);

	अगर (!handle) अणु
		/*
		 * credits to insert 1 extent पूर्णांकo extent tree
		 */
		credits = ext4_chunk_trans_blocks(inode, max_blocks);
	पूर्ण
	जबतक (ret >= 0 && ret < max_blocks) अणु
		map.m_lblk += ret;
		map.m_len = (max_blocks -= ret);
		अगर (credits) अणु
			handle = ext4_journal_start(inode, EXT4_HT_MAP_BLOCKS,
						    credits);
			अगर (IS_ERR(handle)) अणु
				ret = PTR_ERR(handle);
				अवरोध;
			पूर्ण
		पूर्ण
		ret = ext4_map_blocks(handle, inode, &map,
				      EXT4_GET_BLOCKS_IO_CONVERT_EXT);
		अगर (ret <= 0)
			ext4_warning(inode->i_sb,
				     "inode #%lu: block %u: len %u: "
				     "ext4_ext_map_blocks returned %d",
				     inode->i_ino, map.m_lblk,
				     map.m_len, ret);
		ret2 = ext4_mark_inode_dirty(handle, inode);
		अगर (credits) अणु
			ret3 = ext4_journal_stop(handle);
			अगर (unlikely(ret3))
				ret2 = ret3;
		पूर्ण

		अगर (ret <= 0 || ret2)
			अवरोध;
	पूर्ण
	वापस ret > 0 ? ret2 : ret;
पूर्ण

पूर्णांक ext4_convert_unwritten_io_end_vec(handle_t *handle, ext4_io_end_t *io_end)
अणु
	पूर्णांक ret = 0, err = 0;
	काष्ठा ext4_io_end_vec *io_end_vec;

	/*
	 * This is somewhat ugly but the idea is clear: When transaction is
	 * reserved, everything goes पूर्णांकo it. Otherwise we rather start several
	 * smaller transactions क्रम conversion of each extent separately.
	 */
	अगर (handle) अणु
		handle = ext4_journal_start_reserved(handle,
						     EXT4_HT_EXT_CONVERT);
		अगर (IS_ERR(handle))
			वापस PTR_ERR(handle);
	पूर्ण

	list_क्रम_each_entry(io_end_vec, &io_end->list_vec, list) अणु
		ret = ext4_convert_unwritten_extents(handle, io_end->inode,
						     io_end_vec->offset,
						     io_end_vec->size);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (handle)
		err = ext4_journal_stop(handle);

	वापस ret < 0 ? ret : err;
पूर्ण

अटल पूर्णांक ext4_iomap_xattr_fiemap(काष्ठा inode *inode, काष्ठा iomap *iomap)
अणु
	__u64 physical = 0;
	__u64 length = 0;
	पूर्णांक blockbits = inode->i_sb->s_blocksize_bits;
	पूर्णांक error = 0;
	u16 iomap_type;

	/* in-inode? */
	अगर (ext4_test_inode_state(inode, EXT4_STATE_XATTR)) अणु
		काष्ठा ext4_iloc iloc;
		पूर्णांक offset;	/* offset of xattr in inode */

		error = ext4_get_inode_loc(inode, &iloc);
		अगर (error)
			वापस error;
		physical = (__u64)iloc.bh->b_blocknr << blockbits;
		offset = EXT4_GOOD_OLD_INODE_SIZE +
				EXT4_I(inode)->i_extra_isize;
		physical += offset;
		length = EXT4_SB(inode->i_sb)->s_inode_size - offset;
		brअन्यथा(iloc.bh);
		iomap_type = IOMAP_INLINE;
	पूर्ण अन्यथा अगर (EXT4_I(inode)->i_file_acl) अणु /* बाह्यal block */
		physical = (__u64)EXT4_I(inode)->i_file_acl << blockbits;
		length = inode->i_sb->s_blocksize;
		iomap_type = IOMAP_MAPPED;
	पूर्ण अन्यथा अणु
		/* no in-inode or बाह्यal block क्रम xattr, so वापस -ENOENT */
		error = -ENOENT;
		जाओ out;
	पूर्ण

	iomap->addr = physical;
	iomap->offset = 0;
	iomap->length = length;
	iomap->type = iomap_type;
	iomap->flags = 0;
out:
	वापस error;
पूर्ण

अटल पूर्णांक ext4_iomap_xattr_begin(काष्ठा inode *inode, loff_t offset,
				  loff_t length, अचिन्हित flags,
				  काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	पूर्णांक error;

	error = ext4_iomap_xattr_fiemap(inode, iomap);
	अगर (error == 0 && (offset >= iomap->length))
		error = -ENOENT;
	वापस error;
पूर्ण

अटल स्थिर काष्ठा iomap_ops ext4_iomap_xattr_ops = अणु
	.iomap_begin		= ext4_iomap_xattr_begin,
पूर्ण;

अटल पूर्णांक ext4_fiemap_check_ranges(काष्ठा inode *inode, u64 start, u64 *len)
अणु
	u64 maxbytes;

	अगर (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		maxbytes = inode->i_sb->s_maxbytes;
	अन्यथा
		maxbytes = EXT4_SB(inode->i_sb)->s_biपंचांगap_maxbytes;

	अगर (*len == 0)
		वापस -EINVAL;
	अगर (start > maxbytes)
		वापस -EFBIG;

	/*
	 * Shrink request scope to what the fs can actually handle.
	 */
	अगर (*len > maxbytes || (maxbytes - *len) < start)
		*len = maxbytes - start;
	वापस 0;
पूर्ण

पूर्णांक ext4_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		u64 start, u64 len)
अणु
	पूर्णांक error = 0;

	अगर (fieinfo->fi_flags & FIEMAP_FLAG_CACHE) अणु
		error = ext4_ext_precache(inode);
		अगर (error)
			वापस error;
		fieinfo->fi_flags &= ~FIEMAP_FLAG_CACHE;
	पूर्ण

	/*
	 * For biपंचांगap files the maximum size limit could be smaller than
	 * s_maxbytes, so check len here manually instead of just relying on the
	 * generic check.
	 */
	error = ext4_fiemap_check_ranges(inode, start, &len);
	अगर (error)
		वापस error;

	अगर (fieinfo->fi_flags & FIEMAP_FLAG_XATTR) अणु
		fieinfo->fi_flags &= ~FIEMAP_FLAG_XATTR;
		वापस iomap_fiemap(inode, fieinfo, start, len,
				    &ext4_iomap_xattr_ops);
	पूर्ण

	वापस iomap_fiemap(inode, fieinfo, start, len, &ext4_iomap_report_ops);
पूर्ण

पूर्णांक ext4_get_es_cache(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		      __u64 start, __u64 len)
अणु
	ext4_lblk_t start_blk, len_blks;
	__u64 last_blk;
	पूर्णांक error = 0;

	अगर (ext4_has_अंतरभूत_data(inode)) अणु
		पूर्णांक has_अंतरभूत;

		करोwn_पढ़ो(&EXT4_I(inode)->xattr_sem);
		has_अंतरभूत = ext4_has_अंतरभूत_data(inode);
		up_पढ़ो(&EXT4_I(inode)->xattr_sem);
		अगर (has_अंतरभूत)
			वापस 0;
	पूर्ण

	अगर (fieinfo->fi_flags & FIEMAP_FLAG_CACHE) अणु
		error = ext4_ext_precache(inode);
		अगर (error)
			वापस error;
		fieinfo->fi_flags &= ~FIEMAP_FLAG_CACHE;
	पूर्ण

	error = fiemap_prep(inode, fieinfo, start, &len, 0);
	अगर (error)
		वापस error;

	error = ext4_fiemap_check_ranges(inode, start, &len);
	अगर (error)
		वापस error;

	start_blk = start >> inode->i_sb->s_blocksize_bits;
	last_blk = (start + len - 1) >> inode->i_sb->s_blocksize_bits;
	अगर (last_blk >= EXT_MAX_BLOCKS)
		last_blk = EXT_MAX_BLOCKS-1;
	len_blks = ((ext4_lblk_t) last_blk) - start_blk + 1;

	/*
	 * Walk the extent tree gathering extent inक्रमmation
	 * and pushing extents back to the user.
	 */
	वापस ext4_fill_es_cache_info(inode, start_blk, len_blks, fieinfo);
पूर्ण

/*
 * ext4_access_path:
 * Function to access the path buffer क्रम marking it dirty.
 * It also checks अगर there are sufficient credits left in the journal handle
 * to update path.
 */
अटल पूर्णांक
ext4_access_path(handle_t *handle, काष्ठा inode *inode,
		काष्ठा ext4_ext_path *path)
अणु
	पूर्णांक credits, err;

	अगर (!ext4_handle_valid(handle))
		वापस 0;

	/*
	 * Check अगर need to extend journal credits
	 * 3 क्रम leaf, sb, and inode plus 2 (bmap and group
	 * descriptor) क्रम each block group; assume two block
	 * groups
	 */
	credits = ext4_ग_लिखोpage_trans_blocks(inode);
	err = ext4_datasem_ensure_credits(handle, inode, 7, credits, 0);
	अगर (err < 0)
		वापस err;

	err = ext4_ext_get_access(handle, inode, path);
	वापस err;
पूर्ण

/*
 * ext4_ext_shअगरt_path_extents:
 * Shअगरt the extents of a path काष्ठाure lying between path[depth].p_ext
 * and EXT_LAST_EXTENT(path[depth].p_hdr), by @shअगरt blocks. @SHIFT tells
 * अगर it is right shअगरt or left shअगरt operation.
 */
अटल पूर्णांक
ext4_ext_shअगरt_path_extents(काष्ठा ext4_ext_path *path, ext4_lblk_t shअगरt,
			    काष्ठा inode *inode, handle_t *handle,
			    क्रमागत SHIFT_सूचीECTION SHIFT)
अणु
	पूर्णांक depth, err = 0;
	काष्ठा ext4_extent *ex_start, *ex_last;
	bool update = false;
	depth = path->p_depth;

	जबतक (depth >= 0) अणु
		अगर (depth == path->p_depth) अणु
			ex_start = path[depth].p_ext;
			अगर (!ex_start)
				वापस -EFSCORRUPTED;

			ex_last = EXT_LAST_EXTENT(path[depth].p_hdr);

			err = ext4_access_path(handle, inode, path + depth);
			अगर (err)
				जाओ out;

			अगर (ex_start == EXT_FIRST_EXTENT(path[depth].p_hdr))
				update = true;

			जबतक (ex_start <= ex_last) अणु
				अगर (SHIFT == SHIFT_LEFT) अणु
					le32_add_cpu(&ex_start->ee_block,
						-shअगरt);
					/* Try to merge to the left. */
					अगर ((ex_start >
					    EXT_FIRST_EXTENT(path[depth].p_hdr))
					    &&
					    ext4_ext_try_to_merge_right(inode,
					    path, ex_start - 1))
						ex_last--;
					अन्यथा
						ex_start++;
				पूर्ण अन्यथा अणु
					le32_add_cpu(&ex_last->ee_block, shअगरt);
					ext4_ext_try_to_merge_right(inode, path,
						ex_last);
					ex_last--;
				पूर्ण
			पूर्ण
			err = ext4_ext_dirty(handle, inode, path + depth);
			अगर (err)
				जाओ out;

			अगर (--depth < 0 || !update)
				अवरोध;
		पूर्ण

		/* Update index too */
		err = ext4_access_path(handle, inode, path + depth);
		अगर (err)
			जाओ out;

		अगर (SHIFT == SHIFT_LEFT)
			le32_add_cpu(&path[depth].p_idx->ei_block, -shअगरt);
		अन्यथा
			le32_add_cpu(&path[depth].p_idx->ei_block, shअगरt);
		err = ext4_ext_dirty(handle, inode, path + depth);
		अगर (err)
			जाओ out;

		/* we are करोne अगर current index is not a starting index */
		अगर (path[depth].p_idx != EXT_FIRST_INDEX(path[depth].p_hdr))
			अवरोध;

		depth--;
	पूर्ण

out:
	वापस err;
पूर्ण

/*
 * ext4_ext_shअगरt_extents:
 * All the extents which lies in the range from @start to the last allocated
 * block क्रम the @inode are shअगरted either towards left or right (depending
 * upon @SHIFT) by @shअगरt blocks.
 * On success, 0 is वापसed, error otherwise.
 */
अटल पूर्णांक
ext4_ext_shअगरt_extents(काष्ठा inode *inode, handle_t *handle,
		       ext4_lblk_t start, ext4_lblk_t shअगरt,
		       क्रमागत SHIFT_सूचीECTION SHIFT)
अणु
	काष्ठा ext4_ext_path *path;
	पूर्णांक ret = 0, depth;
	काष्ठा ext4_extent *extent;
	ext4_lblk_t stop, *iterator, ex_start, ex_end;

	/* Let path poपूर्णांक to the last extent */
	path = ext4_find_extent(inode, EXT_MAX_BLOCKS - 1, शून्य,
				EXT4_EX_NOCACHE);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);

	depth = path->p_depth;
	extent = path[depth].p_ext;
	अगर (!extent)
		जाओ out;

	stop = le32_to_cpu(extent->ee_block);

       /*
	* For left shअगरts, make sure the hole on the left is big enough to
	* accommodate the shअगरt.  For right shअगरts, make sure the last extent
	* won't be shअगरted beyond EXT_MAX_BLOCKS.
	*/
	अगर (SHIFT == SHIFT_LEFT) अणु
		path = ext4_find_extent(inode, start - 1, &path,
					EXT4_EX_NOCACHE);
		अगर (IS_ERR(path))
			वापस PTR_ERR(path);
		depth = path->p_depth;
		extent =  path[depth].p_ext;
		अगर (extent) अणु
			ex_start = le32_to_cpu(extent->ee_block);
			ex_end = le32_to_cpu(extent->ee_block) +
				ext4_ext_get_actual_len(extent);
		पूर्ण अन्यथा अणु
			ex_start = 0;
			ex_end = 0;
		पूर्ण

		अगर ((start == ex_start && shअगरt > ex_start) ||
		    (shअगरt > start - ex_end)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (shअगरt > EXT_MAX_BLOCKS -
		    (stop + ext4_ext_get_actual_len(extent))) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * In हाल of left shअगरt, iterator poपूर्णांकs to start and it is increased
	 * till we reach stop. In हाल of right shअगरt, iterator poपूर्णांकs to stop
	 * and it is decreased till we reach start.
	 */
	अगर (SHIFT == SHIFT_LEFT)
		iterator = &start;
	अन्यथा
		iterator = &stop;

	/*
	 * Its safe to start updating extents.  Start and stop are अचिन्हित, so
	 * in हाल of right shअगरt अगर extent with 0 block is reached, iterator
	 * becomes शून्य to indicate the end of the loop.
	 */
	जबतक (iterator && start <= stop) अणु
		path = ext4_find_extent(inode, *iterator, &path,
					EXT4_EX_NOCACHE);
		अगर (IS_ERR(path))
			वापस PTR_ERR(path);
		depth = path->p_depth;
		extent = path[depth].p_ext;
		अगर (!extent) अणु
			EXT4_ERROR_INODE(inode, "unexpected hole at %lu",
					 (अचिन्हित दीर्घ) *iterator);
			वापस -EFSCORRUPTED;
		पूर्ण
		अगर (SHIFT == SHIFT_LEFT && *iterator >
		    le32_to_cpu(extent->ee_block)) अणु
			/* Hole, move to the next extent */
			अगर (extent < EXT_LAST_EXTENT(path[depth].p_hdr)) अणु
				path[depth].p_ext++;
			पूर्ण अन्यथा अणु
				*iterator = ext4_ext_next_allocated_block(path);
				जारी;
			पूर्ण
		पूर्ण

		अगर (SHIFT == SHIFT_LEFT) अणु
			extent = EXT_LAST_EXTENT(path[depth].p_hdr);
			*iterator = le32_to_cpu(extent->ee_block) +
					ext4_ext_get_actual_len(extent);
		पूर्ण अन्यथा अणु
			extent = EXT_FIRST_EXTENT(path[depth].p_hdr);
			अगर (le32_to_cpu(extent->ee_block) > 0)
				*iterator = le32_to_cpu(extent->ee_block) - 1;
			अन्यथा
				/* Beginning is reached, end of the loop */
				iterator = शून्य;
			/* Update path extent in हाल we need to stop */
			जबतक (le32_to_cpu(extent->ee_block) < start)
				extent++;
			path[depth].p_ext = extent;
		पूर्ण
		ret = ext4_ext_shअगरt_path_extents(path, shअगरt, inode,
				handle, SHIFT);
		अगर (ret)
			अवरोध;
	पूर्ण
out:
	ext4_ext_drop_refs(path);
	kमुक्त(path);
	वापस ret;
पूर्ण

/*
 * ext4_collapse_range:
 * This implements the fallocate's collapse range functionality क्रम ext4
 * Returns: 0 and non-zero on error.
 */
अटल पूर्णांक ext4_collapse_range(काष्ठा inode *inode, loff_t offset, loff_t len)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	ext4_lblk_t punch_start, punch_stop;
	handle_t *handle;
	अचिन्हित पूर्णांक credits;
	loff_t new_size, ioffset;
	पूर्णांक ret;

	/*
	 * We need to test this early because xfstests assumes that a
	 * collapse range of (0, 1) will वापस EOPNOTSUPP अगर the file
	 * प्रणाली करोes not support collapse range.
	 */
	अगर (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		वापस -EOPNOTSUPP;

	/* Collapse range works only on fs cluster size aligned regions. */
	अगर (!IS_ALIGNED(offset | len, EXT4_CLUSTER_SIZE(sb)))
		वापस -EINVAL;

	trace_ext4_collapse_range(inode, offset, len);

	punch_start = offset >> EXT4_BLOCK_SIZE_BITS(sb);
	punch_stop = (offset + len) >> EXT4_BLOCK_SIZE_BITS(sb);

	/* Call ext4_क्रमce_commit to flush all data in हाल of data=journal. */
	अगर (ext4_should_journal_data(inode)) अणु
		ret = ext4_क्रमce_commit(inode->i_sb);
		अगर (ret)
			वापस ret;
	पूर्ण

	inode_lock(inode);
	/*
	 * There is no need to overlap collapse range with खातापूर्ण, in which हाल
	 * it is effectively a truncate operation
	 */
	अगर (offset + len >= inode->i_size) अणु
		ret = -EINVAL;
		जाओ out_mutex;
	पूर्ण

	/* Currently just क्रम extent based files */
	अगर (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) अणु
		ret = -EOPNOTSUPP;
		जाओ out_mutex;
	पूर्ण

	/* Wait क्रम existing dio to complete */
	inode_dio_रुको(inode);

	/*
	 * Prevent page faults from reinstantiating pages we have released from
	 * page cache.
	 */
	करोwn_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);

	ret = ext4_अवरोध_layouts(inode);
	अगर (ret)
		जाओ out_mmap;

	/*
	 * Need to round करोwn offset to be aligned with page size boundary
	 * क्रम page size > block size.
	 */
	ioffset = round_करोwn(offset, PAGE_SIZE);
	/*
	 * Write tail of the last page beक्रमe हटाओd range since it will get
	 * हटाओd from the page cache below.
	 */
	ret = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, ioffset, offset);
	अगर (ret)
		जाओ out_mmap;
	/*
	 * Write data that will be shअगरted to preserve them when discarding
	 * page cache below. We are also रक्षित from pages becoming dirty
	 * by i_mmap_sem.
	 */
	ret = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, offset + len,
					   Lदीर्घ_उच्च);
	अगर (ret)
		जाओ out_mmap;
	truncate_pagecache(inode, ioffset);

	credits = ext4_ग_लिखोpage_trans_blocks(inode);
	handle = ext4_journal_start(inode, EXT4_HT_TRUNCATE, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		जाओ out_mmap;
	पूर्ण
	ext4_fc_start_ineligible(sb, EXT4_FC_REASON_FALLOC_RANGE);

	करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	ext4_discard_pपुनः_स्मृतिations(inode, 0);

	ret = ext4_es_हटाओ_extent(inode, punch_start,
				    EXT_MAX_BLOCKS - punch_start);
	अगर (ret) अणु
		up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
		जाओ out_stop;
	पूर्ण

	ret = ext4_ext_हटाओ_space(inode, punch_start, punch_stop - 1);
	अगर (ret) अणु
		up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
		जाओ out_stop;
	पूर्ण
	ext4_discard_pपुनः_स्मृतिations(inode, 0);

	ret = ext4_ext_shअगरt_extents(inode, handle, punch_stop,
				     punch_stop - punch_start, SHIFT_LEFT);
	अगर (ret) अणु
		up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
		जाओ out_stop;
	पूर्ण

	new_size = inode->i_size - len;
	i_size_ग_लिखो(inode, new_size);
	EXT4_I(inode)->i_disksize = new_size;

	up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	अगर (IS_SYNC(inode))
		ext4_handle_sync(handle);
	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	ret = ext4_mark_inode_dirty(handle, inode);
	ext4_update_inode_fsync_trans(handle, inode, 1);

out_stop:
	ext4_journal_stop(handle);
	ext4_fc_stop_ineligible(sb);
out_mmap:
	up_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
out_mutex:
	inode_unlock(inode);
	वापस ret;
पूर्ण

/*
 * ext4_insert_range:
 * This function implements the FALLOC_FL_INSERT_RANGE flag of fallocate.
 * The data blocks starting from @offset to the खातापूर्ण are shअगरted by @len
 * towards right to create a hole in the @inode. Inode size is increased
 * by len bytes.
 * Returns 0 on success, error otherwise.
 */
अटल पूर्णांक ext4_insert_range(काष्ठा inode *inode, loff_t offset, loff_t len)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	handle_t *handle;
	काष्ठा ext4_ext_path *path;
	काष्ठा ext4_extent *extent;
	ext4_lblk_t offset_lblk, len_lblk, ee_start_lblk = 0;
	अचिन्हित पूर्णांक credits, ee_len;
	पूर्णांक ret = 0, depth, split_flag = 0;
	loff_t ioffset;

	/*
	 * We need to test this early because xfstests assumes that an
	 * insert range of (0, 1) will वापस EOPNOTSUPP अगर the file
	 * प्रणाली करोes not support insert range.
	 */
	अगर (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		वापस -EOPNOTSUPP;

	/* Insert range works only on fs cluster size aligned regions. */
	अगर (!IS_ALIGNED(offset | len, EXT4_CLUSTER_SIZE(sb)))
		वापस -EINVAL;

	trace_ext4_insert_range(inode, offset, len);

	offset_lblk = offset >> EXT4_BLOCK_SIZE_BITS(sb);
	len_lblk = len >> EXT4_BLOCK_SIZE_BITS(sb);

	/* Call ext4_क्रमce_commit to flush all data in हाल of data=journal */
	अगर (ext4_should_journal_data(inode)) अणु
		ret = ext4_क्रमce_commit(inode->i_sb);
		अगर (ret)
			वापस ret;
	पूर्ण

	inode_lock(inode);
	/* Currently just क्रम extent based files */
	अगर (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) अणु
		ret = -EOPNOTSUPP;
		जाओ out_mutex;
	पूर्ण

	/* Check whether the maximum file size would be exceeded */
	अगर (len > inode->i_sb->s_maxbytes - inode->i_size) अणु
		ret = -EFBIG;
		जाओ out_mutex;
	पूर्ण

	/* Offset must be less than i_size */
	अगर (offset >= inode->i_size) अणु
		ret = -EINVAL;
		जाओ out_mutex;
	पूर्ण

	/* Wait क्रम existing dio to complete */
	inode_dio_रुको(inode);

	/*
	 * Prevent page faults from reinstantiating pages we have released from
	 * page cache.
	 */
	करोwn_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);

	ret = ext4_अवरोध_layouts(inode);
	अगर (ret)
		जाओ out_mmap;

	/*
	 * Need to round करोwn to align start offset to page size boundary
	 * क्रम page size > block size.
	 */
	ioffset = round_करोwn(offset, PAGE_SIZE);
	/* Write out all dirty pages */
	ret = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, ioffset,
			Lदीर्घ_उच्च);
	अगर (ret)
		जाओ out_mmap;
	truncate_pagecache(inode, ioffset);

	credits = ext4_ग_लिखोpage_trans_blocks(inode);
	handle = ext4_journal_start(inode, EXT4_HT_TRUNCATE, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		जाओ out_mmap;
	पूर्ण
	ext4_fc_start_ineligible(sb, EXT4_FC_REASON_FALLOC_RANGE);

	/* Expand file to aव्योम data loss अगर there is error जबतक shअगरting */
	inode->i_size += len;
	EXT4_I(inode)->i_disksize += len;
	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	ret = ext4_mark_inode_dirty(handle, inode);
	अगर (ret)
		जाओ out_stop;

	करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	ext4_discard_pपुनः_स्मृतिations(inode, 0);

	path = ext4_find_extent(inode, offset_lblk, शून्य, 0);
	अगर (IS_ERR(path)) अणु
		up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
		जाओ out_stop;
	पूर्ण

	depth = ext_depth(inode);
	extent = path[depth].p_ext;
	अगर (extent) अणु
		ee_start_lblk = le32_to_cpu(extent->ee_block);
		ee_len = ext4_ext_get_actual_len(extent);

		/*
		 * If offset_lblk is not the starting block of extent, split
		 * the extent @offset_lblk
		 */
		अगर ((offset_lblk > ee_start_lblk) &&
				(offset_lblk < (ee_start_lblk + ee_len))) अणु
			अगर (ext4_ext_is_unwritten(extent))
				split_flag = EXT4_EXT_MARK_UNWRIT1 |
					EXT4_EXT_MARK_UNWRIT2;
			ret = ext4_split_extent_at(handle, inode, &path,
					offset_lblk, split_flag,
					EXT4_EX_NOCACHE |
					EXT4_GET_BLOCKS_PRE_IO |
					EXT4_GET_BLOCKS_METADATA_NOFAIL);
		पूर्ण

		ext4_ext_drop_refs(path);
		kमुक्त(path);
		अगर (ret < 0) अणु
			up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
			जाओ out_stop;
		पूर्ण
	पूर्ण अन्यथा अणु
		ext4_ext_drop_refs(path);
		kमुक्त(path);
	पूर्ण

	ret = ext4_es_हटाओ_extent(inode, offset_lblk,
			EXT_MAX_BLOCKS - offset_lblk);
	अगर (ret) अणु
		up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
		जाओ out_stop;
	पूर्ण

	/*
	 * अगर offset_lblk lies in a hole which is at start of file, use
	 * ee_start_lblk to shअगरt extents
	 */
	ret = ext4_ext_shअगरt_extents(inode, handle,
		ee_start_lblk > offset_lblk ? ee_start_lblk : offset_lblk,
		len_lblk, SHIFT_RIGHT);

	up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	अगर (IS_SYNC(inode))
		ext4_handle_sync(handle);
	अगर (ret >= 0)
		ext4_update_inode_fsync_trans(handle, inode, 1);

out_stop:
	ext4_journal_stop(handle);
	ext4_fc_stop_ineligible(sb);
out_mmap:
	up_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
out_mutex:
	inode_unlock(inode);
	वापस ret;
पूर्ण

/**
 * ext4_swap_extents() - Swap extents between two inodes
 * @handle: handle क्रम this transaction
 * @inode1:	First inode
 * @inode2:	Second inode
 * @lblk1:	Start block क्रम first inode
 * @lblk2:	Start block क्रम second inode
 * @count:	Number of blocks to swap
 * @unwritten: Mark second inode's extents as unwritten after swap
 * @erp:	Poपूर्णांकer to save error value
 *
 * This helper routine करोes exactly what is promise "swap extents". All other
 * stuff such as page-cache locking consistency, bh mapping consistency or
 * extent's data copying must be perक्रमmed by caller.
 * Locking:
 * 		i_mutex is held क्रम both inodes
 * 		i_data_sem is locked क्रम ग_लिखो क्रम both inodes
 * Assumptions:
 *		All pages from requested range are locked क्रम both inodes
 */
पूर्णांक
ext4_swap_extents(handle_t *handle, काष्ठा inode *inode1,
		  काष्ठा inode *inode2, ext4_lblk_t lblk1, ext4_lblk_t lblk2,
		  ext4_lblk_t count, पूर्णांक unwritten, पूर्णांक *erp)
अणु
	काष्ठा ext4_ext_path *path1 = शून्य;
	काष्ठा ext4_ext_path *path2 = शून्य;
	पूर्णांक replaced_count = 0;

	BUG_ON(!rwsem_is_locked(&EXT4_I(inode1)->i_data_sem));
	BUG_ON(!rwsem_is_locked(&EXT4_I(inode2)->i_data_sem));
	BUG_ON(!inode_is_locked(inode1));
	BUG_ON(!inode_is_locked(inode2));

	*erp = ext4_es_हटाओ_extent(inode1, lblk1, count);
	अगर (unlikely(*erp))
		वापस 0;
	*erp = ext4_es_हटाओ_extent(inode2, lblk2, count);
	अगर (unlikely(*erp))
		वापस 0;

	जबतक (count) अणु
		काष्ठा ext4_extent *ex1, *ex2, पंचांगp_ex;
		ext4_lblk_t e1_blk, e2_blk;
		पूर्णांक e1_len, e2_len, len;
		पूर्णांक split = 0;

		path1 = ext4_find_extent(inode1, lblk1, शून्य, EXT4_EX_NOCACHE);
		अगर (IS_ERR(path1)) अणु
			*erp = PTR_ERR(path1);
			path1 = शून्य;
		finish:
			count = 0;
			जाओ repeat;
		पूर्ण
		path2 = ext4_find_extent(inode2, lblk2, शून्य, EXT4_EX_NOCACHE);
		अगर (IS_ERR(path2)) अणु
			*erp = PTR_ERR(path2);
			path2 = शून्य;
			जाओ finish;
		पूर्ण
		ex1 = path1[path1->p_depth].p_ext;
		ex2 = path2[path2->p_depth].p_ext;
		/* Do we have something to swap ? */
		अगर (unlikely(!ex2 || !ex1))
			जाओ finish;

		e1_blk = le32_to_cpu(ex1->ee_block);
		e2_blk = le32_to_cpu(ex2->ee_block);
		e1_len = ext4_ext_get_actual_len(ex1);
		e2_len = ext4_ext_get_actual_len(ex2);

		/* Hole handling */
		अगर (!in_range(lblk1, e1_blk, e1_len) ||
		    !in_range(lblk2, e2_blk, e2_len)) अणु
			ext4_lblk_t next1, next2;

			/* अगर hole after extent, then go to next extent */
			next1 = ext4_ext_next_allocated_block(path1);
			next2 = ext4_ext_next_allocated_block(path2);
			/* If hole beक्रमe extent, then shअगरt to that extent */
			अगर (e1_blk > lblk1)
				next1 = e1_blk;
			अगर (e2_blk > lblk2)
				next2 = e2_blk;
			/* Do we have something to swap */
			अगर (next1 == EXT_MAX_BLOCKS || next2 == EXT_MAX_BLOCKS)
				जाओ finish;
			/* Move to the rightest boundary */
			len = next1 - lblk1;
			अगर (len < next2 - lblk2)
				len = next2 - lblk2;
			अगर (len > count)
				len = count;
			lblk1 += len;
			lblk2 += len;
			count -= len;
			जाओ repeat;
		पूर्ण

		/* Prepare left boundary */
		अगर (e1_blk < lblk1) अणु
			split = 1;
			*erp = ext4_क्रमce_split_extent_at(handle, inode1,
						&path1, lblk1, 0);
			अगर (unlikely(*erp))
				जाओ finish;
		पूर्ण
		अगर (e2_blk < lblk2) अणु
			split = 1;
			*erp = ext4_क्रमce_split_extent_at(handle, inode2,
						&path2,  lblk2, 0);
			अगर (unlikely(*erp))
				जाओ finish;
		पूर्ण
		/* ext4_split_extent_at() may result in leaf extent split,
		 * path must to be revalidated. */
		अगर (split)
			जाओ repeat;

		/* Prepare right boundary */
		len = count;
		अगर (len > e1_blk + e1_len - lblk1)
			len = e1_blk + e1_len - lblk1;
		अगर (len > e2_blk + e2_len - lblk2)
			len = e2_blk + e2_len - lblk2;

		अगर (len != e1_len) अणु
			split = 1;
			*erp = ext4_क्रमce_split_extent_at(handle, inode1,
						&path1, lblk1 + len, 0);
			अगर (unlikely(*erp))
				जाओ finish;
		पूर्ण
		अगर (len != e2_len) अणु
			split = 1;
			*erp = ext4_क्रमce_split_extent_at(handle, inode2,
						&path2, lblk2 + len, 0);
			अगर (*erp)
				जाओ finish;
		पूर्ण
		/* ext4_split_extent_at() may result in leaf extent split,
		 * path must to be revalidated. */
		अगर (split)
			जाओ repeat;

		BUG_ON(e2_len != e1_len);
		*erp = ext4_ext_get_access(handle, inode1, path1 + path1->p_depth);
		अगर (unlikely(*erp))
			जाओ finish;
		*erp = ext4_ext_get_access(handle, inode2, path2 + path2->p_depth);
		अगर (unlikely(*erp))
			जाओ finish;

		/* Both extents are fully inside boundaries. Swap it now */
		पंचांगp_ex = *ex1;
		ext4_ext_store_pblock(ex1, ext4_ext_pblock(ex2));
		ext4_ext_store_pblock(ex2, ext4_ext_pblock(&पंचांगp_ex));
		ex1->ee_len = cpu_to_le16(e2_len);
		ex2->ee_len = cpu_to_le16(e1_len);
		अगर (unwritten)
			ext4_ext_mark_unwritten(ex2);
		अगर (ext4_ext_is_unwritten(&पंचांगp_ex))
			ext4_ext_mark_unwritten(ex1);

		ext4_ext_try_to_merge(handle, inode2, path2, ex2);
		ext4_ext_try_to_merge(handle, inode1, path1, ex1);
		*erp = ext4_ext_dirty(handle, inode2, path2 +
				      path2->p_depth);
		अगर (unlikely(*erp))
			जाओ finish;
		*erp = ext4_ext_dirty(handle, inode1, path1 +
				      path1->p_depth);
		/*
		 * Looks scarry ah..? second inode alपढ़ोy poपूर्णांकs to new blocks,
		 * and it was successfully dirtied. But luckily error may happen
		 * only due to journal error, so full transaction will be
		 * पातed anyway.
		 */
		अगर (unlikely(*erp))
			जाओ finish;
		lblk1 += len;
		lblk2 += len;
		replaced_count += len;
		count -= len;

	repeat:
		ext4_ext_drop_refs(path1);
		kमुक्त(path1);
		ext4_ext_drop_refs(path2);
		kमुक्त(path2);
		path1 = path2 = शून्य;
	पूर्ण
	वापस replaced_count;
पूर्ण

/*
 * ext4_clu_mapped - determine whether any block in a logical cluster has
 *                   been mapped to a physical cluster
 *
 * @inode - file containing the logical cluster
 * @lclu - logical cluster of पूर्णांकerest
 *
 * Returns 1 अगर any block in the logical cluster is mapped, signअगरying
 * that a physical cluster has been allocated क्रम it.  Otherwise,
 * वापसs 0.  Can also वापस negative error codes.  Derived from
 * ext4_ext_map_blocks().
 */
पूर्णांक ext4_clu_mapped(काष्ठा inode *inode, ext4_lblk_t lclu)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा ext4_ext_path *path;
	पूर्णांक depth, mapped = 0, err = 0;
	काष्ठा ext4_extent *extent;
	ext4_lblk_t first_lblk, first_lclu, last_lclu;

	/* search क्रम the extent बंदst to the first block in the cluster */
	path = ext4_find_extent(inode, EXT4_C2B(sbi, lclu), शून्य, 0);
	अगर (IS_ERR(path)) अणु
		err = PTR_ERR(path);
		path = शून्य;
		जाओ out;
	पूर्ण

	depth = ext_depth(inode);

	/*
	 * A consistent leaf must not be empty.  This situation is possible,
	 * though, _during_ tree modअगरication, and it's why an assert can't
	 * be put in ext4_find_extent().
	 */
	अगर (unlikely(path[depth].p_ext == शून्य && depth != 0)) अणु
		EXT4_ERROR_INODE(inode,
		    "bad extent address - lblock: %lu, depth: %d, pblock: %lld",
				 (अचिन्हित दीर्घ) EXT4_C2B(sbi, lclu),
				 depth, path[depth].p_block);
		err = -EFSCORRUPTED;
		जाओ out;
	पूर्ण

	extent = path[depth].p_ext;

	/* can't be mapped अगर the extent tree is empty */
	अगर (extent == शून्य)
		जाओ out;

	first_lblk = le32_to_cpu(extent->ee_block);
	first_lclu = EXT4_B2C(sbi, first_lblk);

	/*
	 * Three possible outcomes at this poपूर्णांक - found extent spanning
	 * the target cluster, to the left of the target cluster, or to the
	 * right of the target cluster.  The first two हालs are handled here.
	 * The last हाल indicates the target cluster is not mapped.
	 */
	अगर (lclu >= first_lclu) अणु
		last_lclu = EXT4_B2C(sbi, first_lblk +
				     ext4_ext_get_actual_len(extent) - 1);
		अगर (lclu <= last_lclu) अणु
			mapped = 1;
		पूर्ण अन्यथा अणु
			first_lblk = ext4_ext_next_allocated_block(path);
			first_lclu = EXT4_B2C(sbi, first_lblk);
			अगर (lclu == first_lclu)
				mapped = 1;
		पूर्ण
	पूर्ण

out:
	ext4_ext_drop_refs(path);
	kमुक्त(path);

	वापस err ? err : mapped;
पूर्ण

/*
 * Updates physical block address and unwritten status of extent
 * starting at lblk start and of len. If such an extent करोesn't exist,
 * this function splits the extent tree appropriately to create an
 * extent like this.  This function is called in the fast commit
 * replay path.  Returns 0 on success and error on failure.
 */
पूर्णांक ext4_ext_replay_update_ex(काष्ठा inode *inode, ext4_lblk_t start,
			      पूर्णांक len, पूर्णांक unwritten, ext4_fsblk_t pblk)
अणु
	काष्ठा ext4_ext_path *path = शून्य, *ppath;
	काष्ठा ext4_extent *ex;
	पूर्णांक ret;

	path = ext4_find_extent(inode, start, शून्य, 0);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);
	ex = path[path->p_depth].p_ext;
	अगर (!ex) अणु
		ret = -EFSCORRUPTED;
		जाओ out;
	पूर्ण

	अगर (le32_to_cpu(ex->ee_block) != start ||
		ext4_ext_get_actual_len(ex) != len) अणु
		/* We need to split this extent to match our extent first */
		ppath = path;
		करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
		ret = ext4_क्रमce_split_extent_at(शून्य, inode, &ppath, start, 1);
		up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
		अगर (ret)
			जाओ out;
		kमुक्त(path);
		path = ext4_find_extent(inode, start, शून्य, 0);
		अगर (IS_ERR(path))
			वापस -1;
		ppath = path;
		ex = path[path->p_depth].p_ext;
		WARN_ON(le32_to_cpu(ex->ee_block) != start);
		अगर (ext4_ext_get_actual_len(ex) != len) अणु
			करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
			ret = ext4_क्रमce_split_extent_at(शून्य, inode, &ppath,
							 start + len, 1);
			up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
			अगर (ret)
				जाओ out;
			kमुक्त(path);
			path = ext4_find_extent(inode, start, शून्य, 0);
			अगर (IS_ERR(path))
				वापस -EINVAL;
			ex = path[path->p_depth].p_ext;
		पूर्ण
	पूर्ण
	अगर (unwritten)
		ext4_ext_mark_unwritten(ex);
	अन्यथा
		ext4_ext_mark_initialized(ex);
	ext4_ext_store_pblock(ex, pblk);
	करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	ret = ext4_ext_dirty(शून्य, inode, &path[path->p_depth]);
	up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
out:
	ext4_ext_drop_refs(path);
	kमुक्त(path);
	ext4_mark_inode_dirty(शून्य, inode);
	वापस ret;
पूर्ण

/* Try to shrink the extent tree */
व्योम ext4_ext_replay_shrink_inode(काष्ठा inode *inode, ext4_lblk_t end)
अणु
	काष्ठा ext4_ext_path *path = शून्य;
	काष्ठा ext4_extent *ex;
	ext4_lblk_t old_cur, cur = 0;

	जबतक (cur < end) अणु
		path = ext4_find_extent(inode, cur, शून्य, 0);
		अगर (IS_ERR(path))
			वापस;
		ex = path[path->p_depth].p_ext;
		अगर (!ex) अणु
			ext4_ext_drop_refs(path);
			kमुक्त(path);
			ext4_mark_inode_dirty(शून्य, inode);
			वापस;
		पूर्ण
		old_cur = cur;
		cur = le32_to_cpu(ex->ee_block) + ext4_ext_get_actual_len(ex);
		अगर (cur <= old_cur)
			cur = old_cur + 1;
		ext4_ext_try_to_merge(शून्य, inode, path, ex);
		करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
		ext4_ext_dirty(शून्य, inode, &path[path->p_depth]);
		up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
		ext4_mark_inode_dirty(शून्य, inode);
		ext4_ext_drop_refs(path);
		kमुक्त(path);
	पूर्ण
पूर्ण

/* Check अगर *cur is a hole and अगर it is, skip it */
अटल व्योम skip_hole(काष्ठा inode *inode, ext4_lblk_t *cur)
अणु
	पूर्णांक ret;
	काष्ठा ext4_map_blocks map;

	map.m_lblk = *cur;
	map.m_len = ((inode->i_size) >> inode->i_sb->s_blocksize_bits) - *cur;

	ret = ext4_map_blocks(शून्य, inode, &map, 0);
	अगर (ret != 0)
		वापस;
	*cur = *cur + map.m_len;
पूर्ण

/* Count number of blocks used by this inode and update i_blocks */
पूर्णांक ext4_ext_replay_set_iblocks(काष्ठा inode *inode)
अणु
	काष्ठा ext4_ext_path *path = शून्य, *path2 = शून्य;
	काष्ठा ext4_extent *ex;
	ext4_lblk_t cur = 0, end;
	पूर्णांक numblks = 0, i, ret = 0;
	ext4_fsblk_t cmp1, cmp2;
	काष्ठा ext4_map_blocks map;

	/* Determin the size of the file first */
	path = ext4_find_extent(inode, EXT_MAX_BLOCKS - 1, शून्य,
					EXT4_EX_NOCACHE);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);
	ex = path[path->p_depth].p_ext;
	अगर (!ex) अणु
		ext4_ext_drop_refs(path);
		kमुक्त(path);
		जाओ out;
	पूर्ण
	end = le32_to_cpu(ex->ee_block) + ext4_ext_get_actual_len(ex);
	ext4_ext_drop_refs(path);
	kमुक्त(path);

	/* Count the number of data blocks */
	cur = 0;
	जबतक (cur < end) अणु
		map.m_lblk = cur;
		map.m_len = end - cur;
		ret = ext4_map_blocks(शून्य, inode, &map, 0);
		अगर (ret < 0)
			अवरोध;
		अगर (ret > 0)
			numblks += ret;
		cur = cur + map.m_len;
	पूर्ण

	/*
	 * Count the number of extent tree blocks. We करो it by looking up
	 * two successive extents and determining the dअगरference between
	 * their paths. When path is dअगरferent क्रम 2 successive extents
	 * we compare the blocks in the path at each level and increment
	 * iblocks by total number of dअगरferences found.
	 */
	cur = 0;
	skip_hole(inode, &cur);
	path = ext4_find_extent(inode, cur, शून्य, 0);
	अगर (IS_ERR(path))
		जाओ out;
	numblks += path->p_depth;
	ext4_ext_drop_refs(path);
	kमुक्त(path);
	जबतक (cur < end) अणु
		path = ext4_find_extent(inode, cur, शून्य, 0);
		अगर (IS_ERR(path))
			अवरोध;
		ex = path[path->p_depth].p_ext;
		अगर (!ex) अणु
			ext4_ext_drop_refs(path);
			kमुक्त(path);
			वापस 0;
		पूर्ण
		cur = max(cur + 1, le32_to_cpu(ex->ee_block) +
					ext4_ext_get_actual_len(ex));
		skip_hole(inode, &cur);

		path2 = ext4_find_extent(inode, cur, शून्य, 0);
		अगर (IS_ERR(path2)) अणु
			ext4_ext_drop_refs(path);
			kमुक्त(path);
			अवरोध;
		पूर्ण
		क्रम (i = 0; i <= max(path->p_depth, path2->p_depth); i++) अणु
			cmp1 = cmp2 = 0;
			अगर (i <= path->p_depth)
				cmp1 = path[i].p_bh ?
					path[i].p_bh->b_blocknr : 0;
			अगर (i <= path2->p_depth)
				cmp2 = path2[i].p_bh ?
					path2[i].p_bh->b_blocknr : 0;
			अगर (cmp1 != cmp2 && cmp2 != 0)
				numblks++;
		पूर्ण
		ext4_ext_drop_refs(path);
		ext4_ext_drop_refs(path2);
		kमुक्त(path);
		kमुक्त(path2);
	पूर्ण

out:
	inode->i_blocks = numblks << (inode->i_sb->s_blocksize_bits - 9);
	ext4_mark_inode_dirty(शून्य, inode);
	वापस 0;
पूर्ण

पूर्णांक ext4_ext_clear_bb(काष्ठा inode *inode)
अणु
	काष्ठा ext4_ext_path *path = शून्य;
	काष्ठा ext4_extent *ex;
	ext4_lblk_t cur = 0, end;
	पूर्णांक j, ret = 0;
	काष्ठा ext4_map_blocks map;

	/* Determin the size of the file first */
	path = ext4_find_extent(inode, EXT_MAX_BLOCKS - 1, शून्य,
					EXT4_EX_NOCACHE);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);
	ex = path[path->p_depth].p_ext;
	अगर (!ex) अणु
		ext4_ext_drop_refs(path);
		kमुक्त(path);
		वापस 0;
	पूर्ण
	end = le32_to_cpu(ex->ee_block) + ext4_ext_get_actual_len(ex);
	ext4_ext_drop_refs(path);
	kमुक्त(path);

	cur = 0;
	जबतक (cur < end) अणु
		map.m_lblk = cur;
		map.m_len = end - cur;
		ret = ext4_map_blocks(शून्य, inode, &map, 0);
		अगर (ret < 0)
			अवरोध;
		अगर (ret > 0) अणु
			path = ext4_find_extent(inode, map.m_lblk, शून्य, 0);
			अगर (!IS_ERR_OR_शून्य(path)) अणु
				क्रम (j = 0; j < path->p_depth; j++) अणु

					ext4_mb_mark_bb(inode->i_sb,
							path[j].p_block, 1, 0);
				पूर्ण
				ext4_ext_drop_refs(path);
				kमुक्त(path);
			पूर्ण
			ext4_mb_mark_bb(inode->i_sb, map.m_pblk, map.m_len, 0);
		पूर्ण
		cur = cur + map.m_len;
	पूर्ण

	वापस 0;
पूर्ण
