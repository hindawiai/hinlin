<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/**
 * inode.c - NTFS kernel inode handling.
 *
 * Copyright (c) 2001-2014 Anton Altaparmakov and Tuxera Inc.
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/mount.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/slab.h>
#समावेश <linux/log2.h>

#समावेश "aops.h"
#समावेश "attrib.h"
#समावेश "bitmap.h"
#समावेश "dir.h"
#समावेश "debug.h"
#समावेश "inode.h"
#समावेश "lcnalloc.h"
#समावेश "malloc.h"
#समावेश "mft.h"
#समावेश "time.h"
#समावेश "ntfs.h"

/**
 * ntfs_test_inode - compare two (possibly fake) inodes क्रम equality
 * @vi:		vfs inode which to test
 * @data:	data which is being tested with
 *
 * Compare the ntfs attribute embedded in the ntfs specअगरic part of the vfs
 * inode @vi क्रम equality with the ntfs attribute @data.
 *
 * If searching क्रम the normal file/directory inode, set @na->type to AT_UNUSED.
 * @na->name and @na->name_len are then ignored.
 *
 * Return 1 अगर the attributes match and 0 अगर not.
 *
 * NOTE: This function runs with the inode_hash_lock spin lock held so it is not
 * allowed to sleep.
 */
पूर्णांक ntfs_test_inode(काष्ठा inode *vi, व्योम *data)
अणु
	ntfs_attr *na = (ntfs_attr *)data;
	ntfs_inode *ni;

	अगर (vi->i_ino != na->mft_no)
		वापस 0;
	ni = NTFS_I(vi);
	/* If !NInoAttr(ni), @vi is a normal file or directory inode. */
	अगर (likely(!NInoAttr(ni))) अणु
		/* If not looking क्रम a normal inode this is a mismatch. */
		अगर (unlikely(na->type != AT_UNUSED))
			वापस 0;
	पूर्ण अन्यथा अणु
		/* A fake inode describing an attribute. */
		अगर (ni->type != na->type)
			वापस 0;
		अगर (ni->name_len != na->name_len)
			वापस 0;
		अगर (na->name_len && स_भेद(ni->name, na->name,
				na->name_len * माप(ntfsअक्षर)))
			वापस 0;
	पूर्ण
	/* Match! */
	वापस 1;
पूर्ण

/**
 * ntfs_init_locked_inode - initialize an inode
 * @vi:		vfs inode to initialize
 * @data:	data which to initialize @vi to
 *
 * Initialize the vfs inode @vi with the values from the ntfs attribute @data in
 * order to enable ntfs_test_inode() to करो its work.
 *
 * If initializing the normal file/directory inode, set @na->type to AT_UNUSED.
 * In that हाल, @na->name and @na->name_len should be set to शून्य and 0,
 * respectively. Although that is not strictly necessary as
 * ntfs_पढ़ो_locked_inode() will fill them in later.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 *
 * NOTE: This function runs with the inode->i_lock spin lock held so it is not
 * allowed to sleep. (Hence the GFP_ATOMIC allocation.)
 */
अटल पूर्णांक ntfs_init_locked_inode(काष्ठा inode *vi, व्योम *data)
अणु
	ntfs_attr *na = (ntfs_attr *)data;
	ntfs_inode *ni = NTFS_I(vi);

	vi->i_ino = na->mft_no;

	ni->type = na->type;
	अगर (na->type == AT_INDEX_ALLOCATION)
		NInoSetMstProtected(ni);

	ni->name = na->name;
	ni->name_len = na->name_len;

	/* If initializing a normal inode, we are करोne. */
	अगर (likely(na->type == AT_UNUSED)) अणु
		BUG_ON(na->name);
		BUG_ON(na->name_len);
		वापस 0;
	पूर्ण

	/* It is a fake inode. */
	NInoSetAttr(ni);

	/*
	 * We have I30 global स्थिरant as an optimization as it is the name
	 * in >99.9% of named attributes! The other <0.1% incur a GFP_ATOMIC
	 * allocation but that is ok. And most attributes are unnamed anyway,
	 * thus the fraction of named attributes with name != I30 is actually
	 * असलolutely tiny.
	 */
	अगर (na->name_len && na->name != I30) अणु
		अचिन्हित पूर्णांक i;

		BUG_ON(!na->name);
		i = na->name_len * माप(ntfsअक्षर);
		ni->name = kदो_स्मृति(i + माप(ntfsअक्षर), GFP_ATOMIC);
		अगर (!ni->name)
			वापस -ENOMEM;
		स_नकल(ni->name, na->name, i);
		ni->name[na->name_len] = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ntfs_पढ़ो_locked_inode(काष्ठा inode *vi);
अटल पूर्णांक ntfs_पढ़ो_locked_attr_inode(काष्ठा inode *base_vi, काष्ठा inode *vi);
अटल पूर्णांक ntfs_पढ़ो_locked_index_inode(काष्ठा inode *base_vi,
		काष्ठा inode *vi);

/**
 * ntfs_iget - obtain a काष्ठा inode corresponding to a specअगरic normal inode
 * @sb:		super block of mounted volume
 * @mft_no:	mft record number / inode number to obtain
 *
 * Obtain the काष्ठा inode corresponding to a specअगरic normal inode (i.e. a
 * file or directory).
 *
 * If the inode is in the cache, it is just वापसed with an increased
 * reference count. Otherwise, a new काष्ठा inode is allocated and initialized,
 * and finally ntfs_पढ़ो_locked_inode() is called to पढ़ो in the inode and
 * fill in the reमुख्यder of the inode काष्ठाure.
 *
 * Return the काष्ठा inode on success. Check the वापस value with IS_ERR() and
 * अगर true, the function failed and the error code is obtained from PTR_ERR().
 */
काष्ठा inode *ntfs_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ mft_no)
अणु
	काष्ठा inode *vi;
	पूर्णांक err;
	ntfs_attr na;

	na.mft_no = mft_no;
	na.type = AT_UNUSED;
	na.name = शून्य;
	na.name_len = 0;

	vi = iget5_locked(sb, mft_no, ntfs_test_inode,
			ntfs_init_locked_inode, &na);
	अगर (unlikely(!vi))
		वापस ERR_PTR(-ENOMEM);

	err = 0;

	/* If this is a freshly allocated inode, need to पढ़ो it now. */
	अगर (vi->i_state & I_NEW) अणु
		err = ntfs_पढ़ो_locked_inode(vi);
		unlock_new_inode(vi);
	पूर्ण
	/*
	 * There is no poपूर्णांक in keeping bad inodes around अगर the failure was
	 * due to ENOMEM. We want to be able to retry again later.
	 */
	अगर (unlikely(err == -ENOMEM)) अणु
		iput(vi);
		vi = ERR_PTR(err);
	पूर्ण
	वापस vi;
पूर्ण

/**
 * ntfs_attr_iget - obtain a काष्ठा inode corresponding to an attribute
 * @base_vi:	vfs base inode containing the attribute
 * @type:	attribute type
 * @name:	Unicode name of the attribute (शून्य अगर unnamed)
 * @name_len:	length of @name in Unicode अक्षरacters (0 अगर unnamed)
 *
 * Obtain the (fake) काष्ठा inode corresponding to the attribute specअगरied by
 * @type, @name, and @name_len, which is present in the base mft record
 * specअगरied by the vfs inode @base_vi.
 *
 * If the attribute inode is in the cache, it is just वापसed with an
 * increased reference count. Otherwise, a new काष्ठा inode is allocated and
 * initialized, and finally ntfs_पढ़ो_locked_attr_inode() is called to पढ़ो the
 * attribute and fill in the inode काष्ठाure.
 *
 * Note, क्रम index allocation attributes, you need to use ntfs_index_iget()
 * instead of ntfs_attr_iget() as working with indices is a lot more complex.
 *
 * Return the काष्ठा inode of the attribute inode on success. Check the वापस
 * value with IS_ERR() and अगर true, the function failed and the error code is
 * obtained from PTR_ERR().
 */
काष्ठा inode *ntfs_attr_iget(काष्ठा inode *base_vi, ATTR_TYPE type,
		ntfsअक्षर *name, u32 name_len)
अणु
	काष्ठा inode *vi;
	पूर्णांक err;
	ntfs_attr na;

	/* Make sure no one calls ntfs_attr_iget() क्रम indices. */
	BUG_ON(type == AT_INDEX_ALLOCATION);

	na.mft_no = base_vi->i_ino;
	na.type = type;
	na.name = name;
	na.name_len = name_len;

	vi = iget5_locked(base_vi->i_sb, na.mft_no, ntfs_test_inode,
			ntfs_init_locked_inode, &na);
	अगर (unlikely(!vi))
		वापस ERR_PTR(-ENOMEM);

	err = 0;

	/* If this is a freshly allocated inode, need to पढ़ो it now. */
	अगर (vi->i_state & I_NEW) अणु
		err = ntfs_पढ़ो_locked_attr_inode(base_vi, vi);
		unlock_new_inode(vi);
	पूर्ण
	/*
	 * There is no poपूर्णांक in keeping bad attribute inodes around. This also
	 * simplअगरies things in that we never need to check क्रम bad attribute
	 * inodes अन्यथाwhere.
	 */
	अगर (unlikely(err)) अणु
		iput(vi);
		vi = ERR_PTR(err);
	पूर्ण
	वापस vi;
पूर्ण

/**
 * ntfs_index_iget - obtain a काष्ठा inode corresponding to an index
 * @base_vi:	vfs base inode containing the index related attributes
 * @name:	Unicode name of the index
 * @name_len:	length of @name in Unicode अक्षरacters
 *
 * Obtain the (fake) काष्ठा inode corresponding to the index specअगरied by @name
 * and @name_len, which is present in the base mft record specअगरied by the vfs
 * inode @base_vi.
 *
 * If the index inode is in the cache, it is just वापसed with an increased
 * reference count.  Otherwise, a new काष्ठा inode is allocated and
 * initialized, and finally ntfs_पढ़ो_locked_index_inode() is called to पढ़ो
 * the index related attributes and fill in the inode काष्ठाure.
 *
 * Return the काष्ठा inode of the index inode on success. Check the वापस
 * value with IS_ERR() and अगर true, the function failed and the error code is
 * obtained from PTR_ERR().
 */
काष्ठा inode *ntfs_index_iget(काष्ठा inode *base_vi, ntfsअक्षर *name,
		u32 name_len)
अणु
	काष्ठा inode *vi;
	पूर्णांक err;
	ntfs_attr na;

	na.mft_no = base_vi->i_ino;
	na.type = AT_INDEX_ALLOCATION;
	na.name = name;
	na.name_len = name_len;

	vi = iget5_locked(base_vi->i_sb, na.mft_no, ntfs_test_inode,
			ntfs_init_locked_inode, &na);
	अगर (unlikely(!vi))
		वापस ERR_PTR(-ENOMEM);

	err = 0;

	/* If this is a freshly allocated inode, need to पढ़ो it now. */
	अगर (vi->i_state & I_NEW) अणु
		err = ntfs_पढ़ो_locked_index_inode(base_vi, vi);
		unlock_new_inode(vi);
	पूर्ण
	/*
	 * There is no poपूर्णांक in keeping bad index inodes around.  This also
	 * simplअगरies things in that we never need to check क्रम bad index
	 * inodes अन्यथाwhere.
	 */
	अगर (unlikely(err)) अणु
		iput(vi);
		vi = ERR_PTR(err);
	पूर्ण
	वापस vi;
पूर्ण

काष्ठा inode *ntfs_alloc_big_inode(काष्ठा super_block *sb)
अणु
	ntfs_inode *ni;

	ntfs_debug("Entering.");
	ni = kmem_cache_alloc(ntfs_big_inode_cache, GFP_NOFS);
	अगर (likely(ni != शून्य)) अणु
		ni->state = 0;
		वापस VFS_I(ni);
	पूर्ण
	ntfs_error(sb, "Allocation of NTFS big inode structure failed.");
	वापस शून्य;
पूर्ण

व्योम ntfs_मुक्त_big_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(ntfs_big_inode_cache, NTFS_I(inode));
पूर्ण

अटल अंतरभूत ntfs_inode *ntfs_alloc_extent_inode(व्योम)
अणु
	ntfs_inode *ni;

	ntfs_debug("Entering.");
	ni = kmem_cache_alloc(ntfs_inode_cache, GFP_NOFS);
	अगर (likely(ni != शून्य)) अणु
		ni->state = 0;
		वापस ni;
	पूर्ण
	ntfs_error(शून्य, "Allocation of NTFS inode structure failed.");
	वापस शून्य;
पूर्ण

अटल व्योम ntfs_destroy_extent_inode(ntfs_inode *ni)
अणु
	ntfs_debug("Entering.");
	BUG_ON(ni->page);
	अगर (!atomic_dec_and_test(&ni->count))
		BUG();
	kmem_cache_मुक्त(ntfs_inode_cache, ni);
पूर्ण

/*
 * The attribute runlist lock has separate locking rules from the
 * normal runlist lock, so split the two lock-classes:
 */
अटल काष्ठा lock_class_key attr_list_rl_lock_class;

/**
 * __ntfs_init_inode - initialize ntfs specअगरic part of an inode
 * @sb:		super block of mounted volume
 * @ni:		freshly allocated ntfs inode which to initialize
 *
 * Initialize an ntfs inode to शेषs.
 *
 * NOTE: ni->mft_no, ni->state, ni->type, ni->name, and ni->name_len are left
 * untouched. Make sure to initialize them अन्यथाwhere.
 *
 * Return zero on success and -ENOMEM on error.
 */
व्योम __ntfs_init_inode(काष्ठा super_block *sb, ntfs_inode *ni)
अणु
	ntfs_debug("Entering.");
	rwlock_init(&ni->size_lock);
	ni->initialized_size = ni->allocated_size = 0;
	ni->seq_no = 0;
	atomic_set(&ni->count, 1);
	ni->vol = NTFS_SB(sb);
	ntfs_init_runlist(&ni->runlist);
	mutex_init(&ni->mrec_lock);
	ni->page = शून्य;
	ni->page_ofs = 0;
	ni->attr_list_size = 0;
	ni->attr_list = शून्य;
	ntfs_init_runlist(&ni->attr_list_rl);
	lockdep_set_class(&ni->attr_list_rl.lock,
				&attr_list_rl_lock_class);
	ni->itype.index.block_size = 0;
	ni->itype.index.vcn_size = 0;
	ni->itype.index.collation_rule = 0;
	ni->itype.index.block_size_bits = 0;
	ni->itype.index.vcn_size_bits = 0;
	mutex_init(&ni->extent_lock);
	ni->nr_extents = 0;
	ni->ext.base_ntfs_ino = शून्य;
पूर्ण

/*
 * Extent inodes get MFT-mapped in a nested way, जबतक the base inode
 * is still mapped. Teach this nesting to the lock validator by creating
 * a separate class क्रम nested inode's mrec_lock's:
 */
अटल काष्ठा lock_class_key extent_inode_mrec_lock_key;

अंतरभूत ntfs_inode *ntfs_new_extent_inode(काष्ठा super_block *sb,
		अचिन्हित दीर्घ mft_no)
अणु
	ntfs_inode *ni = ntfs_alloc_extent_inode();

	ntfs_debug("Entering.");
	अगर (likely(ni != शून्य)) अणु
		__ntfs_init_inode(sb, ni);
		lockdep_set_class(&ni->mrec_lock, &extent_inode_mrec_lock_key);
		ni->mft_no = mft_no;
		ni->type = AT_UNUSED;
		ni->name = शून्य;
		ni->name_len = 0;
	पूर्ण
	वापस ni;
पूर्ण

/**
 * ntfs_is_extended_प्रणाली_file - check अगर a file is in the $Extend directory
 * @ctx:	initialized attribute search context
 *
 * Search all file name attributes in the inode described by the attribute
 * search context @ctx and check अगर any of the names are in the $Extend प्रणाली
 * directory.
 *
 * Return values:
 *	   1: file is in $Extend directory
 *	   0: file is not in $Extend directory
 *    -त्रुटि_सं: failed to determine अगर the file is in the $Extend directory
 */
अटल पूर्णांक ntfs_is_extended_प्रणाली_file(ntfs_attr_search_ctx *ctx)
अणु
	पूर्णांक nr_links, err;

	/* Restart search. */
	ntfs_attr_reinit_search_ctx(ctx);

	/* Get number of hard links. */
	nr_links = le16_to_cpu(ctx->mrec->link_count);

	/* Loop through all hard links. */
	जबतक (!(err = ntfs_attr_lookup(AT_खाता_NAME, शून्य, 0, 0, 0, शून्य, 0,
			ctx))) अणु
		खाता_NAME_ATTR *file_name_attr;
		ATTR_RECORD *attr = ctx->attr;
		u8 *p, *p2;

		nr_links--;
		/*
		 * Maximum sanity checking as we are called on an inode that
		 * we suspect might be corrupt.
		 */
		p = (u8*)attr + le32_to_cpu(attr->length);
		अगर (p < (u8*)ctx->mrec || (u8*)p > (u8*)ctx->mrec +
				le32_to_cpu(ctx->mrec->bytes_in_use)) अणु
err_corrupt_attr:
			ntfs_error(ctx->ntfs_ino->vol->sb, "Corrupt file name "
					"attribute. You should run chkdsk.");
			वापस -EIO;
		पूर्ण
		अगर (attr->non_resident) अणु
			ntfs_error(ctx->ntfs_ino->vol->sb, "Non-resident file "
					"name. You should run chkdsk.");
			वापस -EIO;
		पूर्ण
		अगर (attr->flags) अणु
			ntfs_error(ctx->ntfs_ino->vol->sb, "File name with "
					"invalid flags. You should run "
					"chkdsk.");
			वापस -EIO;
		पूर्ण
		अगर (!(attr->data.resident.flags & RESIDENT_ATTR_IS_INDEXED)) अणु
			ntfs_error(ctx->ntfs_ino->vol->sb, "Unindexed file "
					"name. You should run chkdsk.");
			वापस -EIO;
		पूर्ण
		file_name_attr = (खाता_NAME_ATTR*)((u8*)attr +
				le16_to_cpu(attr->data.resident.value_offset));
		p2 = (u8*)attr + le32_to_cpu(attr->data.resident.value_length);
		अगर (p2 < (u8*)attr || p2 > p)
			जाओ err_corrupt_attr;
		/* This attribute is ok, but is it in the $Extend directory? */
		अगर (MREF_LE(file_name_attr->parent_directory) == खाता_Extend)
			वापस 1;	/* YES, it's an extended प्रणाली file. */
	पूर्ण
	अगर (unlikely(err != -ENOENT))
		वापस err;
	अगर (unlikely(nr_links)) अणु
		ntfs_error(ctx->ntfs_ino->vol->sb, "Inode hard link count "
				"doesn't match number of name attributes. You "
				"should run chkdsk.");
		वापस -EIO;
	पूर्ण
	वापस 0;	/* NO, it is not an extended प्रणाली file. */
पूर्ण

/**
 * ntfs_पढ़ो_locked_inode - पढ़ो an inode from its device
 * @vi:		inode to पढ़ो
 *
 * ntfs_पढ़ो_locked_inode() is called from ntfs_iget() to पढ़ो the inode
 * described by @vi पूर्णांकo memory from the device.
 *
 * The only fields in @vi that we need to/can look at when the function is
 * called are i_sb, poपूर्णांकing to the mounted device's super block, and i_ino,
 * the number of the inode to load.
 *
 * ntfs_पढ़ो_locked_inode() maps, pins and locks the mft record number i_ino
 * क्रम पढ़ोing and sets up the necessary @vi fields as well as initializing
 * the ntfs inode.
 *
 * Q: What locks are held when the function is called?
 * A: i_state has I_NEW set, hence the inode is locked, also
 *    i_count is set to 1, so it is not going to go away
 *    i_flags is set to 0 and we have no business touching it.  Only an ioctl()
 *    is allowed to ग_लिखो to them. We should of course be honouring them but
 *    we need to करो that using the IS_* macros defined in include/linux/fs.h.
 *    In any हाल ntfs_पढ़ो_locked_inode() has nothing to करो with i_flags.
 *
 * Return 0 on success and -त्रुटि_सं on error.  In the error हाल, the inode will
 * have had make_bad_inode() executed on it.
 */
अटल पूर्णांक ntfs_पढ़ो_locked_inode(काष्ठा inode *vi)
अणु
	ntfs_volume *vol = NTFS_SB(vi->i_sb);
	ntfs_inode *ni;
	काष्ठा inode *bvi;
	MFT_RECORD *m;
	ATTR_RECORD *a;
	STANDARD_INFORMATION *si;
	ntfs_attr_search_ctx *ctx;
	पूर्णांक err = 0;

	ntfs_debug("Entering for i_ino 0x%lx.", vi->i_ino);

	/* Setup the generic vfs inode parts now. */
	vi->i_uid = vol->uid;
	vi->i_gid = vol->gid;
	vi->i_mode = 0;

	/*
	 * Initialize the ntfs specअगरic part of @vi special casing
	 * खाता_MFT which we need to करो at mount समय.
	 */
	अगर (vi->i_ino != खाता_MFT)
		ntfs_init_big_inode(vi);
	ni = NTFS_I(vi);

	m = map_mft_record(ni);
	अगर (IS_ERR(m)) अणु
		err = PTR_ERR(m);
		जाओ err_out;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(ni, m);
	अगर (!ctx) अणु
		err = -ENOMEM;
		जाओ unm_err_out;
	पूर्ण

	अगर (!(m->flags & MFT_RECORD_IN_USE)) अणु
		ntfs_error(vi->i_sb, "Inode is not in use!");
		जाओ unm_err_out;
	पूर्ण
	अगर (m->base_mft_record) अणु
		ntfs_error(vi->i_sb, "Inode is an extent inode!");
		जाओ unm_err_out;
	पूर्ण

	/* Transfer inक्रमmation from mft record पूर्णांकo vfs and ntfs inodes. */
	vi->i_generation = ni->seq_no = le16_to_cpu(m->sequence_number);

	/*
	 * FIXME: Keep in mind that link_count is two क्रम files which have both
	 * a दीर्घ file name and a लघु file name as separate entries, so अगर
	 * we are hiding लघु file names this will be too high. Either we need
	 * to account क्रम the लघु file names by subtracting them or we need
	 * to make sure we delete files even though i_nlink is not zero which
	 * might be tricky due to vfs पूर्णांकeractions. Need to think about this
	 * some more when implementing the unlink command.
	 */
	set_nlink(vi, le16_to_cpu(m->link_count));
	/*
	 * FIXME: Reparse poपूर्णांकs can have the directory bit set even though
	 * they would be S_IFLNK. Need to deal with this further below when we
	 * implement reparse poपूर्णांकs / symbolic links but it will करो क्रम now.
	 * Also अगर not a directory, it could be something अन्यथा, rather than
	 * a regular file. But again, will करो क्रम now.
	 */
	/* Everyone माला_लो all permissions. */
	vi->i_mode |= S_IRWXUGO;
	/* If पढ़ो-only, no one माला_लो ग_लिखो permissions. */
	अगर (IS_RDONLY(vi))
		vi->i_mode &= ~S_IWUGO;
	अगर (m->flags & MFT_RECORD_IS_सूचीECTORY) अणु
		vi->i_mode |= S_IFसूची;
		/*
		 * Apply the directory permissions mask set in the mount
		 * options.
		 */
		vi->i_mode &= ~vol->dmask;
		/* Things अवरोध without this kludge! */
		अगर (vi->i_nlink > 1)
			set_nlink(vi, 1);
	पूर्ण अन्यथा अणु
		vi->i_mode |= S_IFREG;
		/* Apply the file permissions mask set in the mount options. */
		vi->i_mode &= ~vol->fmask;
	पूर्ण
	/*
	 * Find the standard inक्रमmation attribute in the mft record. At this
	 * stage we haven't setup the attribute list stuff yet, so this could
	 * in fact fail अगर the standard inक्रमmation is in an extent record, but
	 * I करोn't think this actually ever happens.
	 */
	err = ntfs_attr_lookup(AT_STANDARD_INFORMATION, शून्य, 0, 0, 0, शून्य, 0,
			ctx);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOENT) अणु
			/*
			 * TODO: We should be perक्रमming a hot fix here (अगर the
			 * recover mount option is set) by creating a new
			 * attribute.
			 */
			ntfs_error(vi->i_sb, "$STANDARD_INFORMATION attribute "
					"is missing.");
		पूर्ण
		जाओ unm_err_out;
	पूर्ण
	a = ctx->attr;
	/* Get the standard inक्रमmation attribute value. */
	अगर ((u8 *)a + le16_to_cpu(a->data.resident.value_offset)
			+ le32_to_cpu(a->data.resident.value_length) >
			(u8 *)ctx->mrec + vol->mft_record_size) अणु
		ntfs_error(vi->i_sb, "Corrupt standard information attribute in inode.");
		जाओ unm_err_out;
	पूर्ण
	si = (STANDARD_INFORMATION*)((u8*)a +
			le16_to_cpu(a->data.resident.value_offset));

	/* Transfer inक्रमmation from the standard inक्रमmation पूर्णांकo vi. */
	/*
	 * Note: The i_?बार करो not quite map perfectly onto the NTFS बार,
	 * but they are बंद enough, and in the end it करोesn't really matter
	 * that much...
	 */
	/*
	 * mसमय is the last change of the data within the file. Not changed
	 * when only metadata is changed, e.g. a नाम करोesn't affect mसमय.
	 */
	vi->i_mसमय = ntfs2utc(si->last_data_change_समय);
	/*
	 * स_समय is the last change of the metadata of the file. This obviously
	 * always changes, when mसमय is changed. स_समय can be changed on its
	 * own, mसमय is then not changed, e.g. when a file is नामd.
	 */
	vi->i_स_समय = ntfs2utc(si->last_mft_change_समय);
	/*
	 * Last access to the data within the file. Not changed during a नाम
	 * क्रम example but changed whenever the file is written to.
	 */
	vi->i_aसमय = ntfs2utc(si->last_access_समय);

	/* Find the attribute list attribute अगर present. */
	ntfs_attr_reinit_search_ctx(ctx);
	err = ntfs_attr_lookup(AT_ATTRIBUTE_LIST, शून्य, 0, 0, 0, शून्य, 0, ctx);
	अगर (err) अणु
		अगर (unlikely(err != -ENOENT)) अणु
			ntfs_error(vi->i_sb, "Failed to lookup attribute list "
					"attribute.");
			जाओ unm_err_out;
		पूर्ण
	पूर्ण अन्यथा /* अगर (!err) */ अणु
		अगर (vi->i_ino == खाता_MFT)
			जाओ skip_attr_list_load;
		ntfs_debug("Attribute list found in inode 0x%lx.", vi->i_ino);
		NInoSetAttrList(ni);
		a = ctx->attr;
		अगर (a->flags & ATTR_COMPRESSION_MASK) अणु
			ntfs_error(vi->i_sb, "Attribute list attribute is "
					"compressed.");
			जाओ unm_err_out;
		पूर्ण
		अगर (a->flags & ATTR_IS_ENCRYPTED ||
				a->flags & ATTR_IS_SPARSE) अणु
			अगर (a->non_resident) अणु
				ntfs_error(vi->i_sb, "Non-resident attribute "
						"list attribute is encrypted/"
						"sparse.");
				जाओ unm_err_out;
			पूर्ण
			ntfs_warning(vi->i_sb, "Resident attribute list "
					"attribute in inode 0x%lx is marked "
					"encrypted/sparse which is not true.  "
					"However, Windows allows this and "
					"chkdsk does not detect or correct it "
					"so we will just ignore the invalid "
					"flags and pretend they are not set.",
					vi->i_ino);
		पूर्ण
		/* Now allocate memory क्रम the attribute list. */
		ni->attr_list_size = (u32)ntfs_attr_size(a);
		ni->attr_list = ntfs_दो_स्मृति_nofs(ni->attr_list_size);
		अगर (!ni->attr_list) अणु
			ntfs_error(vi->i_sb, "Not enough memory to allocate "
					"buffer for attribute list.");
			err = -ENOMEM;
			जाओ unm_err_out;
		पूर्ण
		अगर (a->non_resident) अणु
			NInoSetAttrListNonResident(ni);
			अगर (a->data.non_resident.lowest_vcn) अणु
				ntfs_error(vi->i_sb, "Attribute list has non "
						"zero lowest_vcn.");
				जाओ unm_err_out;
			पूर्ण
			/*
			 * Setup the runlist. No need क्रम locking as we have
			 * exclusive access to the inode at this समय.
			 */
			ni->attr_list_rl.rl = ntfs_mapping_pairs_decompress(vol,
					a, शून्य);
			अगर (IS_ERR(ni->attr_list_rl.rl)) अणु
				err = PTR_ERR(ni->attr_list_rl.rl);
				ni->attr_list_rl.rl = शून्य;
				ntfs_error(vi->i_sb, "Mapping pairs "
						"decompression failed.");
				जाओ unm_err_out;
			पूर्ण
			/* Now load the attribute list. */
			अगर ((err = load_attribute_list(vol, &ni->attr_list_rl,
					ni->attr_list, ni->attr_list_size,
					sle64_to_cpu(a->data.non_resident.
					initialized_size)))) अणु
				ntfs_error(vi->i_sb, "Failed to load "
						"attribute list attribute.");
				जाओ unm_err_out;
			पूर्ण
		पूर्ण अन्यथा /* अगर (!a->non_resident) */ अणु
			अगर ((u8*)a + le16_to_cpu(a->data.resident.value_offset)
					+ le32_to_cpu(
					a->data.resident.value_length) >
					(u8*)ctx->mrec + vol->mft_record_size) अणु
				ntfs_error(vi->i_sb, "Corrupt attribute list "
						"in inode.");
				जाओ unm_err_out;
			पूर्ण
			/* Now copy the attribute list. */
			स_नकल(ni->attr_list, (u8*)a + le16_to_cpu(
					a->data.resident.value_offset),
					le32_to_cpu(
					a->data.resident.value_length));
		पूर्ण
	पूर्ण
skip_attr_list_load:
	/*
	 * If an attribute list is present we now have the attribute list value
	 * in ntfs_ino->attr_list and it is ntfs_ino->attr_list_size bytes.
	 */
	अगर (S_ISसूची(vi->i_mode)) अणु
		loff_t bvi_size;
		ntfs_inode *bni;
		INDEX_ROOT *ir;
		u8 *ir_end, *index_end;

		/* It is a directory, find index root attribute. */
		ntfs_attr_reinit_search_ctx(ctx);
		err = ntfs_attr_lookup(AT_INDEX_ROOT, I30, 4, CASE_SENSITIVE,
				0, शून्य, 0, ctx);
		अगर (unlikely(err)) अणु
			अगर (err == -ENOENT) अणु
				// FIXME: File is corrupt! Hot-fix with empty
				// index root attribute अगर recovery option is
				// set.
				ntfs_error(vi->i_sb, "$INDEX_ROOT attribute "
						"is missing.");
			पूर्ण
			जाओ unm_err_out;
		पूर्ण
		a = ctx->attr;
		/* Set up the state. */
		अगर (unlikely(a->non_resident)) अणु
			ntfs_error(vol->sb, "$INDEX_ROOT attribute is not "
					"resident.");
			जाओ unm_err_out;
		पूर्ण
		/* Ensure the attribute name is placed beक्रमe the value. */
		अगर (unlikely(a->name_length && (le16_to_cpu(a->name_offset) >=
				le16_to_cpu(a->data.resident.value_offset)))) अणु
			ntfs_error(vol->sb, "$INDEX_ROOT attribute name is "
					"placed after the attribute value.");
			जाओ unm_err_out;
		पूर्ण
		/*
		 * Compressed/encrypted index root just means that the newly
		 * created files in that directory should be created compressed/
		 * encrypted. However index root cannot be both compressed and
		 * encrypted.
		 */
		अगर (a->flags & ATTR_COMPRESSION_MASK)
			NInoSetCompressed(ni);
		अगर (a->flags & ATTR_IS_ENCRYPTED) अणु
			अगर (a->flags & ATTR_COMPRESSION_MASK) अणु
				ntfs_error(vi->i_sb, "Found encrypted and "
						"compressed attribute.");
				जाओ unm_err_out;
			पूर्ण
			NInoSetEncrypted(ni);
		पूर्ण
		अगर (a->flags & ATTR_IS_SPARSE)
			NInoSetSparse(ni);
		ir = (INDEX_ROOT*)((u8*)a +
				le16_to_cpu(a->data.resident.value_offset));
		ir_end = (u8*)ir + le32_to_cpu(a->data.resident.value_length);
		अगर (ir_end > (u8*)ctx->mrec + vol->mft_record_size) अणु
			ntfs_error(vi->i_sb, "$INDEX_ROOT attribute is "
					"corrupt.");
			जाओ unm_err_out;
		पूर्ण
		index_end = (u8*)&ir->index +
				le32_to_cpu(ir->index.index_length);
		अगर (index_end > ir_end) अणु
			ntfs_error(vi->i_sb, "Directory index is corrupt.");
			जाओ unm_err_out;
		पूर्ण
		अगर (ir->type != AT_खाता_NAME) अणु
			ntfs_error(vi->i_sb, "Indexed attribute is not "
					"$FILE_NAME.");
			जाओ unm_err_out;
		पूर्ण
		अगर (ir->collation_rule != COLLATION_खाता_NAME) अणु
			ntfs_error(vi->i_sb, "Index collation rule is not "
					"COLLATION_FILE_NAME.");
			जाओ unm_err_out;
		पूर्ण
		ni->itype.index.collation_rule = ir->collation_rule;
		ni->itype.index.block_size = le32_to_cpu(ir->index_block_size);
		अगर (ni->itype.index.block_size &
				(ni->itype.index.block_size - 1)) अणु
			ntfs_error(vi->i_sb, "Index block size (%u) is not a "
					"power of two.",
					ni->itype.index.block_size);
			जाओ unm_err_out;
		पूर्ण
		अगर (ni->itype.index.block_size > PAGE_SIZE) अणु
			ntfs_error(vi->i_sb, "Index block size (%u) > "
					"PAGE_SIZE (%ld) is not "
					"supported.  Sorry.",
					ni->itype.index.block_size,
					PAGE_SIZE);
			err = -EOPNOTSUPP;
			जाओ unm_err_out;
		पूर्ण
		अगर (ni->itype.index.block_size < NTFS_BLOCK_SIZE) अणु
			ntfs_error(vi->i_sb, "Index block size (%u) < "
					"NTFS_BLOCK_SIZE (%i) is not "
					"supported.  Sorry.",
					ni->itype.index.block_size,
					NTFS_BLOCK_SIZE);
			err = -EOPNOTSUPP;
			जाओ unm_err_out;
		पूर्ण
		ni->itype.index.block_size_bits =
				ffs(ni->itype.index.block_size) - 1;
		/* Determine the size of a vcn in the directory index. */
		अगर (vol->cluster_size <= ni->itype.index.block_size) अणु
			ni->itype.index.vcn_size = vol->cluster_size;
			ni->itype.index.vcn_size_bits = vol->cluster_size_bits;
		पूर्ण अन्यथा अणु
			ni->itype.index.vcn_size = vol->sector_size;
			ni->itype.index.vcn_size_bits = vol->sector_size_bits;
		पूर्ण

		/* Setup the index allocation attribute, even अगर not present. */
		NInoSetMstProtected(ni);
		ni->type = AT_INDEX_ALLOCATION;
		ni->name = I30;
		ni->name_len = 4;

		अगर (!(ir->index.flags & LARGE_INDEX)) अणु
			/* No index allocation. */
			vi->i_size = ni->initialized_size =
					ni->allocated_size = 0;
			/* We are करोne with the mft record, so we release it. */
			ntfs_attr_put_search_ctx(ctx);
			unmap_mft_record(ni);
			m = शून्य;
			ctx = शून्य;
			जाओ skip_large_dir_stuff;
		पूर्ण /* LARGE_INDEX: Index allocation present. Setup state. */
		NInoSetIndexAllocPresent(ni);
		/* Find index allocation attribute. */
		ntfs_attr_reinit_search_ctx(ctx);
		err = ntfs_attr_lookup(AT_INDEX_ALLOCATION, I30, 4,
				CASE_SENSITIVE, 0, शून्य, 0, ctx);
		अगर (unlikely(err)) अणु
			अगर (err == -ENOENT)
				ntfs_error(vi->i_sb, "$INDEX_ALLOCATION "
						"attribute is not present but "
						"$INDEX_ROOT indicated it is.");
			अन्यथा
				ntfs_error(vi->i_sb, "Failed to lookup "
						"$INDEX_ALLOCATION "
						"attribute.");
			जाओ unm_err_out;
		पूर्ण
		a = ctx->attr;
		अगर (!a->non_resident) अणु
			ntfs_error(vi->i_sb, "$INDEX_ALLOCATION attribute "
					"is resident.");
			जाओ unm_err_out;
		पूर्ण
		/*
		 * Ensure the attribute name is placed beक्रमe the mapping pairs
		 * array.
		 */
		अगर (unlikely(a->name_length && (le16_to_cpu(a->name_offset) >=
				le16_to_cpu(
				a->data.non_resident.mapping_pairs_offset)))) अणु
			ntfs_error(vol->sb, "$INDEX_ALLOCATION attribute name "
					"is placed after the mapping pairs "
					"array.");
			जाओ unm_err_out;
		पूर्ण
		अगर (a->flags & ATTR_IS_ENCRYPTED) अणु
			ntfs_error(vi->i_sb, "$INDEX_ALLOCATION attribute "
					"is encrypted.");
			जाओ unm_err_out;
		पूर्ण
		अगर (a->flags & ATTR_IS_SPARSE) अणु
			ntfs_error(vi->i_sb, "$INDEX_ALLOCATION attribute "
					"is sparse.");
			जाओ unm_err_out;
		पूर्ण
		अगर (a->flags & ATTR_COMPRESSION_MASK) अणु
			ntfs_error(vi->i_sb, "$INDEX_ALLOCATION attribute "
					"is compressed.");
			जाओ unm_err_out;
		पूर्ण
		अगर (a->data.non_resident.lowest_vcn) अणु
			ntfs_error(vi->i_sb, "First extent of "
					"$INDEX_ALLOCATION attribute has non "
					"zero lowest_vcn.");
			जाओ unm_err_out;
		पूर्ण
		vi->i_size = sle64_to_cpu(a->data.non_resident.data_size);
		ni->initialized_size = sle64_to_cpu(
				a->data.non_resident.initialized_size);
		ni->allocated_size = sle64_to_cpu(
				a->data.non_resident.allocated_size);
		/*
		 * We are करोne with the mft record, so we release it. Otherwise
		 * we would deadlock in ntfs_attr_iget().
		 */
		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(ni);
		m = शून्य;
		ctx = शून्य;
		/* Get the index biपंचांगap attribute inode. */
		bvi = ntfs_attr_iget(vi, AT_BITMAP, I30, 4);
		अगर (IS_ERR(bvi)) अणु
			ntfs_error(vi->i_sb, "Failed to get bitmap attribute.");
			err = PTR_ERR(bvi);
			जाओ unm_err_out;
		पूर्ण
		bni = NTFS_I(bvi);
		अगर (NInoCompressed(bni) || NInoEncrypted(bni) ||
				NInoSparse(bni)) अणु
			ntfs_error(vi->i_sb, "$BITMAP attribute is compressed "
					"and/or encrypted and/or sparse.");
			जाओ iput_unm_err_out;
		पूर्ण
		/* Consistency check biपंचांगap size vs. index allocation size. */
		bvi_size = i_size_पढ़ो(bvi);
		अगर ((bvi_size << 3) < (vi->i_size >>
				ni->itype.index.block_size_bits)) अणु
			ntfs_error(vi->i_sb, "Index bitmap too small (0x%llx) "
					"for index allocation (0x%llx).",
					bvi_size << 3, vi->i_size);
			जाओ iput_unm_err_out;
		पूर्ण
		/* No दीर्घer need the biपंचांगap attribute inode. */
		iput(bvi);
skip_large_dir_stuff:
		/* Setup the operations क्रम this inode. */
		vi->i_op = &ntfs_dir_inode_ops;
		vi->i_fop = &ntfs_dir_ops;
		vi->i_mapping->a_ops = &ntfs_mst_aops;
	पूर्ण अन्यथा अणु
		/* It is a file. */
		ntfs_attr_reinit_search_ctx(ctx);

		/* Setup the data attribute, even अगर not present. */
		ni->type = AT_DATA;
		ni->name = शून्य;
		ni->name_len = 0;

		/* Find first extent of the unnamed data attribute. */
		err = ntfs_attr_lookup(AT_DATA, शून्य, 0, 0, 0, शून्य, 0, ctx);
		अगर (unlikely(err)) अणु
			vi->i_size = ni->initialized_size =
					ni->allocated_size = 0;
			अगर (err != -ENOENT) अणु
				ntfs_error(vi->i_sb, "Failed to lookup $DATA "
						"attribute.");
				जाओ unm_err_out;
			पूर्ण
			/*
			 * खाता_Secure करोes not have an unnamed $DATA
			 * attribute, so we special हाल it here.
			 */
			अगर (vi->i_ino == खाता_Secure)
				जाओ no_data_attr_special_हाल;
			/*
			 * Most अगर not all the प्रणाली files in the $Extend
			 * प्रणाली directory करो not have unnamed data
			 * attributes so we need to check अगर the parent
			 * directory of the file is खाता_Extend and अगर it is
			 * ignore this error. To करो this we need to get the
			 * name of this inode from the mft record as the name
			 * contains the back reference to the parent directory.
			 */
			अगर (ntfs_is_extended_प्रणाली_file(ctx) > 0)
				जाओ no_data_attr_special_हाल;
			// FIXME: File is corrupt! Hot-fix with empty data
			// attribute अगर recovery option is set.
			ntfs_error(vi->i_sb, "$DATA attribute is missing.");
			जाओ unm_err_out;
		पूर्ण
		a = ctx->attr;
		/* Setup the state. */
		अगर (a->flags & (ATTR_COMPRESSION_MASK | ATTR_IS_SPARSE)) अणु
			अगर (a->flags & ATTR_COMPRESSION_MASK) अणु
				NInoSetCompressed(ni);
				अगर (vol->cluster_size > 4096) अणु
					ntfs_error(vi->i_sb, "Found "
							"compressed data but "
							"compression is "
							"disabled due to "
							"cluster size (%i) > "
							"4kiB.",
							vol->cluster_size);
					जाओ unm_err_out;
				पूर्ण
				अगर ((a->flags & ATTR_COMPRESSION_MASK)
						!= ATTR_IS_COMPRESSED) अणु
					ntfs_error(vi->i_sb, "Found unknown "
							"compression method "
							"or corrupt file.");
					जाओ unm_err_out;
				पूर्ण
			पूर्ण
			अगर (a->flags & ATTR_IS_SPARSE)
				NInoSetSparse(ni);
		पूर्ण
		अगर (a->flags & ATTR_IS_ENCRYPTED) अणु
			अगर (NInoCompressed(ni)) अणु
				ntfs_error(vi->i_sb, "Found encrypted and "
						"compressed data.");
				जाओ unm_err_out;
			पूर्ण
			NInoSetEncrypted(ni);
		पूर्ण
		अगर (a->non_resident) अणु
			NInoSetNonResident(ni);
			अगर (NInoCompressed(ni) || NInoSparse(ni)) अणु
				अगर (NInoCompressed(ni) && a->data.non_resident.
						compression_unit != 4) अणु
					ntfs_error(vi->i_sb, "Found "
							"non-standard "
							"compression unit (%u "
							"instead of 4).  "
							"Cannot handle this.",
							a->data.non_resident.
							compression_unit);
					err = -EOPNOTSUPP;
					जाओ unm_err_out;
				पूर्ण
				अगर (a->data.non_resident.compression_unit) अणु
					ni->itype.compressed.block_size = 1U <<
							(a->data.non_resident.
							compression_unit +
							vol->cluster_size_bits);
					ni->itype.compressed.block_size_bits =
							ffs(ni->itype.
							compressed.
							block_size) - 1;
					ni->itype.compressed.block_clusters =
							1U << a->data.
							non_resident.
							compression_unit;
				पूर्ण अन्यथा अणु
					ni->itype.compressed.block_size = 0;
					ni->itype.compressed.block_size_bits =
							0;
					ni->itype.compressed.block_clusters =
							0;
				पूर्ण
				ni->itype.compressed.size = sle64_to_cpu(
						a->data.non_resident.
						compressed_size);
			पूर्ण
			अगर (a->data.non_resident.lowest_vcn) अणु
				ntfs_error(vi->i_sb, "First extent of $DATA "
						"attribute has non zero "
						"lowest_vcn.");
				जाओ unm_err_out;
			पूर्ण
			vi->i_size = sle64_to_cpu(
					a->data.non_resident.data_size);
			ni->initialized_size = sle64_to_cpu(
					a->data.non_resident.initialized_size);
			ni->allocated_size = sle64_to_cpu(
					a->data.non_resident.allocated_size);
		पूर्ण अन्यथा अणु /* Resident attribute. */
			vi->i_size = ni->initialized_size = le32_to_cpu(
					a->data.resident.value_length);
			ni->allocated_size = le32_to_cpu(a->length) -
					le16_to_cpu(
					a->data.resident.value_offset);
			अगर (vi->i_size > ni->allocated_size) अणु
				ntfs_error(vi->i_sb, "Resident data attribute "
						"is corrupt (size exceeds "
						"allocation).");
				जाओ unm_err_out;
			पूर्ण
		पूर्ण
no_data_attr_special_हाल:
		/* We are करोne with the mft record, so we release it. */
		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(ni);
		m = शून्य;
		ctx = शून्य;
		/* Setup the operations क्रम this inode. */
		vi->i_op = &ntfs_file_inode_ops;
		vi->i_fop = &ntfs_file_ops;
		vi->i_mapping->a_ops = &ntfs_normal_aops;
		अगर (NInoMstProtected(ni))
			vi->i_mapping->a_ops = &ntfs_mst_aops;
		अन्यथा अगर (NInoCompressed(ni))
			vi->i_mapping->a_ops = &ntfs_compressed_aops;
	पूर्ण
	/*
	 * The number of 512-byte blocks used on disk (क्रम stat). This is in so
	 * far inaccurate as it करोesn't account क्रम any named streams or other
	 * special non-resident attributes, but that is how Winकरोws works, too,
	 * so we are at least consistent with Winकरोws, अगर not entirely
	 * consistent with the Linux Way. Doing it the Linux Way would cause a
	 * signअगरicant slowकरोwn as it would involve iterating over all
	 * attributes in the mft record and adding the allocated/compressed
	 * sizes of all non-resident attributes present to give us the Linux
	 * correct size that should go पूर्णांकo i_blocks (after भागision by 512).
	 */
	अगर (S_ISREG(vi->i_mode) && (NInoCompressed(ni) || NInoSparse(ni)))
		vi->i_blocks = ni->itype.compressed.size >> 9;
	अन्यथा
		vi->i_blocks = ni->allocated_size >> 9;
	ntfs_debug("Done.");
	वापस 0;
iput_unm_err_out:
	iput(bvi);
unm_err_out:
	अगर (!err)
		err = -EIO;
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (m)
		unmap_mft_record(ni);
err_out:
	ntfs_error(vol->sb, "Failed with error code %i.  Marking corrupt "
			"inode 0x%lx as bad.  Run chkdsk.", err, vi->i_ino);
	make_bad_inode(vi);
	अगर (err != -EOPNOTSUPP && err != -ENOMEM)
		NVolSetErrors(vol);
	वापस err;
पूर्ण

/**
 * ntfs_पढ़ो_locked_attr_inode - पढ़ो an attribute inode from its base inode
 * @base_vi:	base inode
 * @vi:		attribute inode to पढ़ो
 *
 * ntfs_पढ़ो_locked_attr_inode() is called from ntfs_attr_iget() to पढ़ो the
 * attribute inode described by @vi पूर्णांकo memory from the base mft record
 * described by @base_ni.
 *
 * ntfs_पढ़ो_locked_attr_inode() maps, pins and locks the base inode क्रम
 * पढ़ोing and looks up the attribute described by @vi beक्रमe setting up the
 * necessary fields in @vi as well as initializing the ntfs inode.
 *
 * Q: What locks are held when the function is called?
 * A: i_state has I_NEW set, hence the inode is locked, also
 *    i_count is set to 1, so it is not going to go away
 *
 * Return 0 on success and -त्रुटि_सं on error.  In the error हाल, the inode will
 * have had make_bad_inode() executed on it.
 *
 * Note this cannot be called क्रम AT_INDEX_ALLOCATION.
 */
अटल पूर्णांक ntfs_पढ़ो_locked_attr_inode(काष्ठा inode *base_vi, काष्ठा inode *vi)
अणु
	ntfs_volume *vol = NTFS_SB(vi->i_sb);
	ntfs_inode *ni, *base_ni;
	MFT_RECORD *m;
	ATTR_RECORD *a;
	ntfs_attr_search_ctx *ctx;
	पूर्णांक err = 0;

	ntfs_debug("Entering for i_ino 0x%lx.", vi->i_ino);

	ntfs_init_big_inode(vi);

	ni	= NTFS_I(vi);
	base_ni = NTFS_I(base_vi);

	/* Just mirror the values from the base inode. */
	vi->i_uid	= base_vi->i_uid;
	vi->i_gid	= base_vi->i_gid;
	set_nlink(vi, base_vi->i_nlink);
	vi->i_mसमय	= base_vi->i_mसमय;
	vi->i_स_समय	= base_vi->i_स_समय;
	vi->i_aसमय	= base_vi->i_aसमय;
	vi->i_generation = ni->seq_no = base_ni->seq_no;

	/* Set inode type to zero but preserve permissions. */
	vi->i_mode	= base_vi->i_mode & ~S_IFMT;

	m = map_mft_record(base_ni);
	अगर (IS_ERR(m)) अणु
		err = PTR_ERR(m);
		जाओ err_out;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(base_ni, m);
	अगर (!ctx) अणु
		err = -ENOMEM;
		जाओ unm_err_out;
	पूर्ण
	/* Find the attribute. */
	err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
			CASE_SENSITIVE, 0, शून्य, 0, ctx);
	अगर (unlikely(err))
		जाओ unm_err_out;
	a = ctx->attr;
	अगर (a->flags & (ATTR_COMPRESSION_MASK | ATTR_IS_SPARSE)) अणु
		अगर (a->flags & ATTR_COMPRESSION_MASK) अणु
			NInoSetCompressed(ni);
			अगर ((ni->type != AT_DATA) || (ni->type == AT_DATA &&
					ni->name_len)) अणु
				ntfs_error(vi->i_sb, "Found compressed "
						"non-data or named data "
						"attribute.  Please report "
						"you saw this message to "
						"linux-ntfs-dev@lists."
						"sourceforge.net");
				जाओ unm_err_out;
			पूर्ण
			अगर (vol->cluster_size > 4096) अणु
				ntfs_error(vi->i_sb, "Found compressed "
						"attribute but compression is "
						"disabled due to cluster size "
						"(%i) > 4kiB.",
						vol->cluster_size);
				जाओ unm_err_out;
			पूर्ण
			अगर ((a->flags & ATTR_COMPRESSION_MASK) !=
					ATTR_IS_COMPRESSED) अणु
				ntfs_error(vi->i_sb, "Found unknown "
						"compression method.");
				जाओ unm_err_out;
			पूर्ण
		पूर्ण
		/*
		 * The compressed/sparse flag set in an index root just means
		 * to compress all files.
		 */
		अगर (NInoMstProtected(ni) && ni->type != AT_INDEX_ROOT) अणु
			ntfs_error(vi->i_sb, "Found mst protected attribute "
					"but the attribute is %s.  Please "
					"report you saw this message to "
					"linux-ntfs-dev@lists.sourceforge.net",
					NInoCompressed(ni) ? "compressed" :
					"sparse");
			जाओ unm_err_out;
		पूर्ण
		अगर (a->flags & ATTR_IS_SPARSE)
			NInoSetSparse(ni);
	पूर्ण
	अगर (a->flags & ATTR_IS_ENCRYPTED) अणु
		अगर (NInoCompressed(ni)) अणु
			ntfs_error(vi->i_sb, "Found encrypted and compressed "
					"data.");
			जाओ unm_err_out;
		पूर्ण
		/*
		 * The encryption flag set in an index root just means to
		 * encrypt all files.
		 */
		अगर (NInoMstProtected(ni) && ni->type != AT_INDEX_ROOT) अणु
			ntfs_error(vi->i_sb, "Found mst protected attribute "
					"but the attribute is encrypted.  "
					"Please report you saw this message "
					"to linux-ntfs-dev@lists.sourceforge."
					"net");
			जाओ unm_err_out;
		पूर्ण
		अगर (ni->type != AT_DATA) अणु
			ntfs_error(vi->i_sb, "Found encrypted non-data "
					"attribute.");
			जाओ unm_err_out;
		पूर्ण
		NInoSetEncrypted(ni);
	पूर्ण
	अगर (!a->non_resident) अणु
		/* Ensure the attribute name is placed beक्रमe the value. */
		अगर (unlikely(a->name_length && (le16_to_cpu(a->name_offset) >=
				le16_to_cpu(a->data.resident.value_offset)))) अणु
			ntfs_error(vol->sb, "Attribute name is placed after "
					"the attribute value.");
			जाओ unm_err_out;
		पूर्ण
		अगर (NInoMstProtected(ni)) अणु
			ntfs_error(vi->i_sb, "Found mst protected attribute "
					"but the attribute is resident.  "
					"Please report you saw this message to "
					"linux-ntfs-dev@lists.sourceforge.net");
			जाओ unm_err_out;
		पूर्ण
		vi->i_size = ni->initialized_size = le32_to_cpu(
				a->data.resident.value_length);
		ni->allocated_size = le32_to_cpu(a->length) -
				le16_to_cpu(a->data.resident.value_offset);
		अगर (vi->i_size > ni->allocated_size) अणु
			ntfs_error(vi->i_sb, "Resident attribute is corrupt "
					"(size exceeds allocation).");
			जाओ unm_err_out;
		पूर्ण
	पूर्ण अन्यथा अणु
		NInoSetNonResident(ni);
		/*
		 * Ensure the attribute name is placed beक्रमe the mapping pairs
		 * array.
		 */
		अगर (unlikely(a->name_length && (le16_to_cpu(a->name_offset) >=
				le16_to_cpu(
				a->data.non_resident.mapping_pairs_offset)))) अणु
			ntfs_error(vol->sb, "Attribute name is placed after "
					"the mapping pairs array.");
			जाओ unm_err_out;
		पूर्ण
		अगर (NInoCompressed(ni) || NInoSparse(ni)) अणु
			अगर (NInoCompressed(ni) && a->data.non_resident.
					compression_unit != 4) अणु
				ntfs_error(vi->i_sb, "Found non-standard "
						"compression unit (%u instead "
						"of 4).  Cannot handle this.",
						a->data.non_resident.
						compression_unit);
				err = -EOPNOTSUPP;
				जाओ unm_err_out;
			पूर्ण
			अगर (a->data.non_resident.compression_unit) अणु
				ni->itype.compressed.block_size = 1U <<
						(a->data.non_resident.
						compression_unit +
						vol->cluster_size_bits);
				ni->itype.compressed.block_size_bits =
						ffs(ni->itype.compressed.
						block_size) - 1;
				ni->itype.compressed.block_clusters = 1U <<
						a->data.non_resident.
						compression_unit;
			पूर्ण अन्यथा अणु
				ni->itype.compressed.block_size = 0;
				ni->itype.compressed.block_size_bits = 0;
				ni->itype.compressed.block_clusters = 0;
			पूर्ण
			ni->itype.compressed.size = sle64_to_cpu(
					a->data.non_resident.compressed_size);
		पूर्ण
		अगर (a->data.non_resident.lowest_vcn) अणु
			ntfs_error(vi->i_sb, "First extent of attribute has "
					"non-zero lowest_vcn.");
			जाओ unm_err_out;
		पूर्ण
		vi->i_size = sle64_to_cpu(a->data.non_resident.data_size);
		ni->initialized_size = sle64_to_cpu(
				a->data.non_resident.initialized_size);
		ni->allocated_size = sle64_to_cpu(
				a->data.non_resident.allocated_size);
	पूर्ण
	vi->i_mapping->a_ops = &ntfs_normal_aops;
	अगर (NInoMstProtected(ni))
		vi->i_mapping->a_ops = &ntfs_mst_aops;
	अन्यथा अगर (NInoCompressed(ni))
		vi->i_mapping->a_ops = &ntfs_compressed_aops;
	अगर ((NInoCompressed(ni) || NInoSparse(ni)) && ni->type != AT_INDEX_ROOT)
		vi->i_blocks = ni->itype.compressed.size >> 9;
	अन्यथा
		vi->i_blocks = ni->allocated_size >> 9;
	/*
	 * Make sure the base inode करोes not go away and attach it to the
	 * attribute inode.
	 */
	igrab(base_vi);
	ni->ext.base_ntfs_ino = base_ni;
	ni->nr_extents = -1;

	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(base_ni);

	ntfs_debug("Done.");
	वापस 0;

unm_err_out:
	अगर (!err)
		err = -EIO;
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(base_ni);
err_out:
	ntfs_error(vol->sb, "Failed with error code %i while reading attribute "
			"inode (mft_no 0x%lx, type 0x%x, name_len %i).  "
			"Marking corrupt inode and base inode 0x%lx as bad.  "
			"Run chkdsk.", err, vi->i_ino, ni->type, ni->name_len,
			base_vi->i_ino);
	make_bad_inode(vi);
	अगर (err != -ENOMEM)
		NVolSetErrors(vol);
	वापस err;
पूर्ण

/**
 * ntfs_पढ़ो_locked_index_inode - पढ़ो an index inode from its base inode
 * @base_vi:	base inode
 * @vi:		index inode to पढ़ो
 *
 * ntfs_पढ़ो_locked_index_inode() is called from ntfs_index_iget() to पढ़ो the
 * index inode described by @vi पूर्णांकo memory from the base mft record described
 * by @base_ni.
 *
 * ntfs_पढ़ो_locked_index_inode() maps, pins and locks the base inode क्रम
 * पढ़ोing and looks up the attributes relating to the index described by @vi
 * beक्रमe setting up the necessary fields in @vi as well as initializing the
 * ntfs inode.
 *
 * Note, index inodes are essentially attribute inodes (NInoAttr() is true)
 * with the attribute type set to AT_INDEX_ALLOCATION.  Apart from that, they
 * are setup like directory inodes since directories are a special हाल of
 * indices ao they need to be treated in much the same way.  Most importantly,
 * क्रम small indices the index allocation attribute might not actually exist.
 * However, the index root attribute always exists but this करोes not need to
 * have an inode associated with it and this is why we define a new inode type
 * index.  Also, like क्रम directories, we need to have an attribute inode क्रम
 * the biपंचांगap attribute corresponding to the index allocation attribute and we
 * can store this in the appropriate field of the inode, just like we करो क्रम
 * normal directory inodes.
 *
 * Q: What locks are held when the function is called?
 * A: i_state has I_NEW set, hence the inode is locked, also
 *    i_count is set to 1, so it is not going to go away
 *
 * Return 0 on success and -त्रुटि_सं on error.  In the error हाल, the inode will
 * have had make_bad_inode() executed on it.
 */
अटल पूर्णांक ntfs_पढ़ो_locked_index_inode(काष्ठा inode *base_vi, काष्ठा inode *vi)
अणु
	loff_t bvi_size;
	ntfs_volume *vol = NTFS_SB(vi->i_sb);
	ntfs_inode *ni, *base_ni, *bni;
	काष्ठा inode *bvi;
	MFT_RECORD *m;
	ATTR_RECORD *a;
	ntfs_attr_search_ctx *ctx;
	INDEX_ROOT *ir;
	u8 *ir_end, *index_end;
	पूर्णांक err = 0;

	ntfs_debug("Entering for i_ino 0x%lx.", vi->i_ino);
	ntfs_init_big_inode(vi);
	ni	= NTFS_I(vi);
	base_ni = NTFS_I(base_vi);
	/* Just mirror the values from the base inode. */
	vi->i_uid	= base_vi->i_uid;
	vi->i_gid	= base_vi->i_gid;
	set_nlink(vi, base_vi->i_nlink);
	vi->i_mसमय	= base_vi->i_mसमय;
	vi->i_स_समय	= base_vi->i_स_समय;
	vi->i_aसमय	= base_vi->i_aसमय;
	vi->i_generation = ni->seq_no = base_ni->seq_no;
	/* Set inode type to zero but preserve permissions. */
	vi->i_mode	= base_vi->i_mode & ~S_IFMT;
	/* Map the mft record क्रम the base inode. */
	m = map_mft_record(base_ni);
	अगर (IS_ERR(m)) अणु
		err = PTR_ERR(m);
		जाओ err_out;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(base_ni, m);
	अगर (!ctx) अणु
		err = -ENOMEM;
		जाओ unm_err_out;
	पूर्ण
	/* Find the index root attribute. */
	err = ntfs_attr_lookup(AT_INDEX_ROOT, ni->name, ni->name_len,
			CASE_SENSITIVE, 0, शून्य, 0, ctx);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOENT)
			ntfs_error(vi->i_sb, "$INDEX_ROOT attribute is "
					"missing.");
		जाओ unm_err_out;
	पूर्ण
	a = ctx->attr;
	/* Set up the state. */
	अगर (unlikely(a->non_resident)) अणु
		ntfs_error(vol->sb, "$INDEX_ROOT attribute is not resident.");
		जाओ unm_err_out;
	पूर्ण
	/* Ensure the attribute name is placed beक्रमe the value. */
	अगर (unlikely(a->name_length && (le16_to_cpu(a->name_offset) >=
			le16_to_cpu(a->data.resident.value_offset)))) अणु
		ntfs_error(vol->sb, "$INDEX_ROOT attribute name is placed "
				"after the attribute value.");
		जाओ unm_err_out;
	पूर्ण
	/*
	 * Compressed/encrypted/sparse index root is not allowed, except क्रम
	 * directories of course but those are not dealt with here.
	 */
	अगर (a->flags & (ATTR_COMPRESSION_MASK | ATTR_IS_ENCRYPTED |
			ATTR_IS_SPARSE)) अणु
		ntfs_error(vi->i_sb, "Found compressed/encrypted/sparse index "
				"root attribute.");
		जाओ unm_err_out;
	पूर्ण
	ir = (INDEX_ROOT*)((u8*)a + le16_to_cpu(a->data.resident.value_offset));
	ir_end = (u8*)ir + le32_to_cpu(a->data.resident.value_length);
	अगर (ir_end > (u8*)ctx->mrec + vol->mft_record_size) अणु
		ntfs_error(vi->i_sb, "$INDEX_ROOT attribute is corrupt.");
		जाओ unm_err_out;
	पूर्ण
	index_end = (u8*)&ir->index + le32_to_cpu(ir->index.index_length);
	अगर (index_end > ir_end) अणु
		ntfs_error(vi->i_sb, "Index is corrupt.");
		जाओ unm_err_out;
	पूर्ण
	अगर (ir->type) अणु
		ntfs_error(vi->i_sb, "Index type is not 0 (type is 0x%x).",
				le32_to_cpu(ir->type));
		जाओ unm_err_out;
	पूर्ण
	ni->itype.index.collation_rule = ir->collation_rule;
	ntfs_debug("Index collation rule is 0x%x.",
			le32_to_cpu(ir->collation_rule));
	ni->itype.index.block_size = le32_to_cpu(ir->index_block_size);
	अगर (!is_घातer_of_2(ni->itype.index.block_size)) अणु
		ntfs_error(vi->i_sb, "Index block size (%u) is not a power of "
				"two.", ni->itype.index.block_size);
		जाओ unm_err_out;
	पूर्ण
	अगर (ni->itype.index.block_size > PAGE_SIZE) अणु
		ntfs_error(vi->i_sb, "Index block size (%u) > PAGE_SIZE "
				"(%ld) is not supported.  Sorry.",
				ni->itype.index.block_size, PAGE_SIZE);
		err = -EOPNOTSUPP;
		जाओ unm_err_out;
	पूर्ण
	अगर (ni->itype.index.block_size < NTFS_BLOCK_SIZE) अणु
		ntfs_error(vi->i_sb, "Index block size (%u) < NTFS_BLOCK_SIZE "
				"(%i) is not supported.  Sorry.",
				ni->itype.index.block_size, NTFS_BLOCK_SIZE);
		err = -EOPNOTSUPP;
		जाओ unm_err_out;
	पूर्ण
	ni->itype.index.block_size_bits = ffs(ni->itype.index.block_size) - 1;
	/* Determine the size of a vcn in the index. */
	अगर (vol->cluster_size <= ni->itype.index.block_size) अणु
		ni->itype.index.vcn_size = vol->cluster_size;
		ni->itype.index.vcn_size_bits = vol->cluster_size_bits;
	पूर्ण अन्यथा अणु
		ni->itype.index.vcn_size = vol->sector_size;
		ni->itype.index.vcn_size_bits = vol->sector_size_bits;
	पूर्ण
	/* Check क्रम presence of index allocation attribute. */
	अगर (!(ir->index.flags & LARGE_INDEX)) अणु
		/* No index allocation. */
		vi->i_size = ni->initialized_size = ni->allocated_size = 0;
		/* We are करोne with the mft record, so we release it. */
		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(base_ni);
		m = शून्य;
		ctx = शून्य;
		जाओ skip_large_index_stuff;
	पूर्ण /* LARGE_INDEX:  Index allocation present.  Setup state. */
	NInoSetIndexAllocPresent(ni);
	/* Find index allocation attribute. */
	ntfs_attr_reinit_search_ctx(ctx);
	err = ntfs_attr_lookup(AT_INDEX_ALLOCATION, ni->name, ni->name_len,
			CASE_SENSITIVE, 0, शून्य, 0, ctx);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOENT)
			ntfs_error(vi->i_sb, "$INDEX_ALLOCATION attribute is "
					"not present but $INDEX_ROOT "
					"indicated it is.");
		अन्यथा
			ntfs_error(vi->i_sb, "Failed to lookup "
					"$INDEX_ALLOCATION attribute.");
		जाओ unm_err_out;
	पूर्ण
	a = ctx->attr;
	अगर (!a->non_resident) अणु
		ntfs_error(vi->i_sb, "$INDEX_ALLOCATION attribute is "
				"resident.");
		जाओ unm_err_out;
	पूर्ण
	/*
	 * Ensure the attribute name is placed beक्रमe the mapping pairs array.
	 */
	अगर (unlikely(a->name_length && (le16_to_cpu(a->name_offset) >=
			le16_to_cpu(
			a->data.non_resident.mapping_pairs_offset)))) अणु
		ntfs_error(vol->sb, "$INDEX_ALLOCATION attribute name is "
				"placed after the mapping pairs array.");
		जाओ unm_err_out;
	पूर्ण
	अगर (a->flags & ATTR_IS_ENCRYPTED) अणु
		ntfs_error(vi->i_sb, "$INDEX_ALLOCATION attribute is "
				"encrypted.");
		जाओ unm_err_out;
	पूर्ण
	अगर (a->flags & ATTR_IS_SPARSE) अणु
		ntfs_error(vi->i_sb, "$INDEX_ALLOCATION attribute is sparse.");
		जाओ unm_err_out;
	पूर्ण
	अगर (a->flags & ATTR_COMPRESSION_MASK) अणु
		ntfs_error(vi->i_sb, "$INDEX_ALLOCATION attribute is "
				"compressed.");
		जाओ unm_err_out;
	पूर्ण
	अगर (a->data.non_resident.lowest_vcn) अणु
		ntfs_error(vi->i_sb, "First extent of $INDEX_ALLOCATION "
				"attribute has non zero lowest_vcn.");
		जाओ unm_err_out;
	पूर्ण
	vi->i_size = sle64_to_cpu(a->data.non_resident.data_size);
	ni->initialized_size = sle64_to_cpu(
			a->data.non_resident.initialized_size);
	ni->allocated_size = sle64_to_cpu(a->data.non_resident.allocated_size);
	/*
	 * We are करोne with the mft record, so we release it.  Otherwise
	 * we would deadlock in ntfs_attr_iget().
	 */
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(base_ni);
	m = शून्य;
	ctx = शून्य;
	/* Get the index biपंचांगap attribute inode. */
	bvi = ntfs_attr_iget(base_vi, AT_BITMAP, ni->name, ni->name_len);
	अगर (IS_ERR(bvi)) अणु
		ntfs_error(vi->i_sb, "Failed to get bitmap attribute.");
		err = PTR_ERR(bvi);
		जाओ unm_err_out;
	पूर्ण
	bni = NTFS_I(bvi);
	अगर (NInoCompressed(bni) || NInoEncrypted(bni) ||
			NInoSparse(bni)) अणु
		ntfs_error(vi->i_sb, "$BITMAP attribute is compressed and/or "
				"encrypted and/or sparse.");
		जाओ iput_unm_err_out;
	पूर्ण
	/* Consistency check biपंचांगap size vs. index allocation size. */
	bvi_size = i_size_पढ़ो(bvi);
	अगर ((bvi_size << 3) < (vi->i_size >> ni->itype.index.block_size_bits)) अणु
		ntfs_error(vi->i_sb, "Index bitmap too small (0x%llx) for "
				"index allocation (0x%llx).", bvi_size << 3,
				vi->i_size);
		जाओ iput_unm_err_out;
	पूर्ण
	iput(bvi);
skip_large_index_stuff:
	/* Setup the operations क्रम this index inode. */
	vi->i_mapping->a_ops = &ntfs_mst_aops;
	vi->i_blocks = ni->allocated_size >> 9;
	/*
	 * Make sure the base inode करोesn't go away and attach it to the
	 * index inode.
	 */
	igrab(base_vi);
	ni->ext.base_ntfs_ino = base_ni;
	ni->nr_extents = -1;

	ntfs_debug("Done.");
	वापस 0;
iput_unm_err_out:
	iput(bvi);
unm_err_out:
	अगर (!err)
		err = -EIO;
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (m)
		unmap_mft_record(base_ni);
err_out:
	ntfs_error(vi->i_sb, "Failed with error code %i while reading index "
			"inode (mft_no 0x%lx, name_len %i.", err, vi->i_ino,
			ni->name_len);
	make_bad_inode(vi);
	अगर (err != -EOPNOTSUPP && err != -ENOMEM)
		NVolSetErrors(vol);
	वापस err;
पूर्ण

/*
 * The MFT inode has special locking, so teach the lock validator
 * about this by splitting off the locking rules of the MFT from
 * the locking rules of other inodes. The MFT inode can never be
 * accessed from the VFS side (or even पूर्णांकernally), only by the
 * map_mft functions.
 */
अटल काष्ठा lock_class_key mft_ni_runlist_lock_key, mft_ni_mrec_lock_key;

/**
 * ntfs_पढ़ो_inode_mount - special पढ़ो_inode क्रम mount समय use only
 * @vi:		inode to पढ़ो
 *
 * Read inode खाता_MFT at mount समय, only called with super_block lock
 * held from within the पढ़ो_super() code path.
 *
 * This function exists because when it is called the page cache क्रम $MFT/$DATA
 * is not initialized and hence we cannot get at the contents of mft records
 * by calling map_mft_record*().
 *
 * Further it needs to cope with the circular references problem, i.e. cannot
 * load any attributes other than $ATTRIBUTE_LIST until $DATA is loaded, because
 * we करो not know where the other extent mft records are yet and again, because
 * we cannot call map_mft_record*() yet.  Obviously this applies only when an
 * attribute list is actually present in $MFT inode.
 *
 * We solve these problems by starting with the $DATA attribute beक्रमe anything
 * अन्यथा and iterating using ntfs_attr_lookup($DATA) over all extents.  As each
 * extent is found, we ntfs_mapping_pairs_decompress() including the implied
 * ntfs_runlists_merge().  Each step of the iteration necessarily provides
 * sufficient inक्रमmation क्रम the next step to complete.
 *
 * This should work but there are two possible pit falls (see अंतरभूत comments
 * below), but only समय will tell अगर they are real pits or just smoke...
 */
पूर्णांक ntfs_पढ़ो_inode_mount(काष्ठा inode *vi)
अणु
	VCN next_vcn, last_vcn, highest_vcn;
	s64 block;
	काष्ठा super_block *sb = vi->i_sb;
	ntfs_volume *vol = NTFS_SB(sb);
	काष्ठा buffer_head *bh;
	ntfs_inode *ni;
	MFT_RECORD *m = शून्य;
	ATTR_RECORD *a;
	ntfs_attr_search_ctx *ctx;
	अचिन्हित पूर्णांक i, nr_blocks;
	पूर्णांक err;

	ntfs_debug("Entering.");

	/* Initialize the ntfs specअगरic part of @vi. */
	ntfs_init_big_inode(vi);

	ni = NTFS_I(vi);

	/* Setup the data attribute. It is special as it is mst रक्षित. */
	NInoSetNonResident(ni);
	NInoSetMstProtected(ni);
	NInoSetSparseDisabled(ni);
	ni->type = AT_DATA;
	ni->name = शून्य;
	ni->name_len = 0;
	/*
	 * This sets up our little cheat allowing us to reuse the async पढ़ो io
	 * completion handler क्रम directories.
	 */
	ni->itype.index.block_size = vol->mft_record_size;
	ni->itype.index.block_size_bits = vol->mft_record_size_bits;

	/* Very important! Needed to be able to call map_mft_record*(). */
	vol->mft_ino = vi;

	/* Allocate enough memory to पढ़ो the first mft record. */
	अगर (vol->mft_record_size > 64 * 1024) अणु
		ntfs_error(sb, "Unsupported mft record size %i (max 64kiB).",
				vol->mft_record_size);
		जाओ err_out;
	पूर्ण
	i = vol->mft_record_size;
	अगर (i < sb->s_blocksize)
		i = sb->s_blocksize;
	m = (MFT_RECORD*)ntfs_दो_स्मृति_nofs(i);
	अगर (!m) अणु
		ntfs_error(sb, "Failed to allocate buffer for $MFT record 0.");
		जाओ err_out;
	पूर्ण

	/* Determine the first block of the $MFT/$DATA attribute. */
	block = vol->mft_lcn << vol->cluster_size_bits >>
			sb->s_blocksize_bits;
	nr_blocks = vol->mft_record_size >> sb->s_blocksize_bits;
	अगर (!nr_blocks)
		nr_blocks = 1;

	/* Load $MFT/$DATA's first mft record. */
	क्रम (i = 0; i < nr_blocks; i++) अणु
		bh = sb_bपढ़ो(sb, block++);
		अगर (!bh) अणु
			ntfs_error(sb, "Device read failed.");
			जाओ err_out;
		पूर्ण
		स_नकल((अक्षर*)m + (i << sb->s_blocksize_bits), bh->b_data,
				sb->s_blocksize);
		brअन्यथा(bh);
	पूर्ण

	अगर (le32_to_cpu(m->bytes_allocated) != vol->mft_record_size) अणु
		ntfs_error(sb, "Incorrect mft record size %u in superblock, should be %u.",
				le32_to_cpu(m->bytes_allocated), vol->mft_record_size);
		जाओ err_out;
	पूर्ण

	/* Apply the mst fixups. */
	अगर (post_पढ़ो_mst_fixup((NTFS_RECORD*)m, vol->mft_record_size)) अणु
		/* FIXME: Try to use the $MFTMirr now. */
		ntfs_error(sb, "MST fixup failed. $MFT is corrupt.");
		जाओ err_out;
	पूर्ण

	/* Need this to sanity check attribute list references to $MFT. */
	vi->i_generation = ni->seq_no = le16_to_cpu(m->sequence_number);

	/* Provides पढ़ोpage() क्रम map_mft_record(). */
	vi->i_mapping->a_ops = &ntfs_mst_aops;

	ctx = ntfs_attr_get_search_ctx(ni, m);
	अगर (!ctx) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	/* Find the attribute list attribute अगर present. */
	err = ntfs_attr_lookup(AT_ATTRIBUTE_LIST, शून्य, 0, 0, 0, शून्य, 0, ctx);
	अगर (err) अणु
		अगर (unlikely(err != -ENOENT)) अणु
			ntfs_error(sb, "Failed to lookup attribute list "
					"attribute. You should run chkdsk.");
			जाओ put_err_out;
		पूर्ण
	पूर्ण अन्यथा /* अगर (!err) */ अणु
		ATTR_LIST_ENTRY *al_entry, *next_al_entry;
		u8 *al_end;
		अटल स्थिर अक्षर *es = "  Not allowed.  $MFT is corrupt.  "
				"You should run chkdsk.";

		ntfs_debug("Attribute list attribute found in $MFT.");
		NInoSetAttrList(ni);
		a = ctx->attr;
		अगर (a->flags & ATTR_COMPRESSION_MASK) अणु
			ntfs_error(sb, "Attribute list attribute is "
					"compressed.%s", es);
			जाओ put_err_out;
		पूर्ण
		अगर (a->flags & ATTR_IS_ENCRYPTED ||
				a->flags & ATTR_IS_SPARSE) अणु
			अगर (a->non_resident) अणु
				ntfs_error(sb, "Non-resident attribute list "
						"attribute is encrypted/"
						"sparse.%s", es);
				जाओ put_err_out;
			पूर्ण
			ntfs_warning(sb, "Resident attribute list attribute "
					"in $MFT system file is marked "
					"encrypted/sparse which is not true.  "
					"However, Windows allows this and "
					"chkdsk does not detect or correct it "
					"so we will just ignore the invalid "
					"flags and pretend they are not set.");
		पूर्ण
		/* Now allocate memory क्रम the attribute list. */
		ni->attr_list_size = (u32)ntfs_attr_size(a);
		ni->attr_list = ntfs_दो_स्मृति_nofs(ni->attr_list_size);
		अगर (!ni->attr_list) अणु
			ntfs_error(sb, "Not enough memory to allocate buffer "
					"for attribute list.");
			जाओ put_err_out;
		पूर्ण
		अगर (a->non_resident) अणु
			NInoSetAttrListNonResident(ni);
			अगर (a->data.non_resident.lowest_vcn) अणु
				ntfs_error(sb, "Attribute list has non zero "
						"lowest_vcn. $MFT is corrupt. "
						"You should run chkdsk.");
				जाओ put_err_out;
			पूर्ण
			/* Setup the runlist. */
			ni->attr_list_rl.rl = ntfs_mapping_pairs_decompress(vol,
					a, शून्य);
			अगर (IS_ERR(ni->attr_list_rl.rl)) अणु
				err = PTR_ERR(ni->attr_list_rl.rl);
				ni->attr_list_rl.rl = शून्य;
				ntfs_error(sb, "Mapping pairs decompression "
						"failed with error code %i.",
						-err);
				जाओ put_err_out;
			पूर्ण
			/* Now load the attribute list. */
			अगर ((err = load_attribute_list(vol, &ni->attr_list_rl,
					ni->attr_list, ni->attr_list_size,
					sle64_to_cpu(a->data.
					non_resident.initialized_size)))) अणु
				ntfs_error(sb, "Failed to load attribute list "
						"attribute with error code %i.",
						-err);
				जाओ put_err_out;
			पूर्ण
		पूर्ण अन्यथा /* अगर (!ctx.attr->non_resident) */ अणु
			अगर ((u8*)a + le16_to_cpu(
					a->data.resident.value_offset) +
					le32_to_cpu(
					a->data.resident.value_length) >
					(u8*)ctx->mrec + vol->mft_record_size) अणु
				ntfs_error(sb, "Corrupt attribute list "
						"attribute.");
				जाओ put_err_out;
			पूर्ण
			/* Now copy the attribute list. */
			स_नकल(ni->attr_list, (u8*)a + le16_to_cpu(
					a->data.resident.value_offset),
					le32_to_cpu(
					a->data.resident.value_length));
		पूर्ण
		/* The attribute list is now setup in memory. */
		/*
		 * FIXME: I करोn't know अगर this हाल is actually possible.
		 * According to logic it is not possible but I have seen too
		 * many weird things in MS software to rely on logic... Thus we
		 * perक्रमm a manual search and make sure the first $MFT/$DATA
		 * extent is in the base inode. If it is not we पात with an
		 * error and अगर we ever see a report of this error we will need
		 * to करो some magic in order to have the necessary mft record
		 * loaded and in the right place in the page cache. But
		 * hopefully logic will prevail and this never happens...
		 */
		al_entry = (ATTR_LIST_ENTRY*)ni->attr_list;
		al_end = (u8*)al_entry + ni->attr_list_size;
		क्रम (;; al_entry = next_al_entry) अणु
			/* Out of bounds check. */
			अगर ((u8*)al_entry < ni->attr_list ||
					(u8*)al_entry > al_end)
				जाओ em_put_err_out;
			/* Catch the end of the attribute list. */
			अगर ((u8*)al_entry == al_end)
				जाओ em_put_err_out;
			अगर (!al_entry->length)
				जाओ em_put_err_out;
			अगर ((u8*)al_entry + 6 > al_end || (u8*)al_entry +
					le16_to_cpu(al_entry->length) > al_end)
				जाओ em_put_err_out;
			next_al_entry = (ATTR_LIST_ENTRY*)((u8*)al_entry +
					le16_to_cpu(al_entry->length));
			अगर (le32_to_cpu(al_entry->type) > le32_to_cpu(AT_DATA))
				जाओ em_put_err_out;
			अगर (AT_DATA != al_entry->type)
				जारी;
			/* We want an unnamed attribute. */
			अगर (al_entry->name_length)
				जाओ em_put_err_out;
			/* Want the first entry, i.e. lowest_vcn == 0. */
			अगर (al_entry->lowest_vcn)
				जाओ em_put_err_out;
			/* First entry has to be in the base mft record. */
			अगर (MREF_LE(al_entry->mft_reference) != vi->i_ino) अणु
				/* MFT references करो not match, logic fails. */
				ntfs_error(sb, "BUG: The first $DATA extent "
						"of $MFT is not in the base "
						"mft record. Please report "
						"you saw this message to "
						"linux-ntfs-dev@lists."
						"sourceforge.net");
				जाओ put_err_out;
			पूर्ण अन्यथा अणु
				/* Sequence numbers must match. */
				अगर (MSEQNO_LE(al_entry->mft_reference) !=
						ni->seq_no)
					जाओ em_put_err_out;
				/* Got it. All is ok. We can stop now. */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	ntfs_attr_reinit_search_ctx(ctx);

	/* Now load all attribute extents. */
	a = शून्य;
	next_vcn = last_vcn = highest_vcn = 0;
	जबतक (!(err = ntfs_attr_lookup(AT_DATA, शून्य, 0, 0, next_vcn, शून्य, 0,
			ctx))) अणु
		runlist_element *nrl;

		/* Cache the current attribute. */
		a = ctx->attr;
		/* $MFT must be non-resident. */
		अगर (!a->non_resident) अणु
			ntfs_error(sb, "$MFT must be non-resident but a "
					"resident extent was found. $MFT is "
					"corrupt. Run chkdsk.");
			जाओ put_err_out;
		पूर्ण
		/* $MFT must be uncompressed and unencrypted. */
		अगर (a->flags & ATTR_COMPRESSION_MASK ||
				a->flags & ATTR_IS_ENCRYPTED ||
				a->flags & ATTR_IS_SPARSE) अणु
			ntfs_error(sb, "$MFT must be uncompressed, "
					"non-sparse, and unencrypted but a "
					"compressed/sparse/encrypted extent "
					"was found. $MFT is corrupt. Run "
					"chkdsk.");
			जाओ put_err_out;
		पूर्ण
		/*
		 * Decompress the mapping pairs array of this extent and merge
		 * the result पूर्णांकo the existing runlist. No need क्रम locking
		 * as we have exclusive access to the inode at this समय and we
		 * are a mount in progress task, too.
		 */
		nrl = ntfs_mapping_pairs_decompress(vol, a, ni->runlist.rl);
		अगर (IS_ERR(nrl)) अणु
			ntfs_error(sb, "ntfs_mapping_pairs_decompress() "
					"failed with error code %ld.  $MFT is "
					"corrupt.", PTR_ERR(nrl));
			जाओ put_err_out;
		पूर्ण
		ni->runlist.rl = nrl;

		/* Are we in the first extent? */
		अगर (!next_vcn) अणु
			अगर (a->data.non_resident.lowest_vcn) अणु
				ntfs_error(sb, "First extent of $DATA "
						"attribute has non zero "
						"lowest_vcn. $MFT is corrupt. "
						"You should run chkdsk.");
				जाओ put_err_out;
			पूर्ण
			/* Get the last vcn in the $DATA attribute. */
			last_vcn = sle64_to_cpu(
					a->data.non_resident.allocated_size)
					>> vol->cluster_size_bits;
			/* Fill in the inode size. */
			vi->i_size = sle64_to_cpu(
					a->data.non_resident.data_size);
			ni->initialized_size = sle64_to_cpu(
					a->data.non_resident.initialized_size);
			ni->allocated_size = sle64_to_cpu(
					a->data.non_resident.allocated_size);
			/*
			 * Verअगरy the number of mft records करोes not exceed
			 * 2^32 - 1.
			 */
			अगर ((vi->i_size >> vol->mft_record_size_bits) >=
					(1ULL << 32)) अणु
				ntfs_error(sb, "$MFT is too big! Aborting.");
				जाओ put_err_out;
			पूर्ण
			/*
			 * We have got the first extent of the runlist क्रम
			 * $MFT which means it is now relatively safe to call
			 * the normal ntfs_पढ़ो_inode() function.
			 * Complete पढ़ोing the inode, this will actually
			 * re-पढ़ो the mft record क्रम $MFT, this समय entering
			 * it पूर्णांकo the page cache with which we complete the
			 * kick start of the volume. It should be safe to करो
			 * this now as the first extent of $MFT/$DATA is
			 * alपढ़ोy known and we would hope that we करोn't need
			 * further extents in order to find the other
			 * attributes beदीर्घing to $MFT. Only समय will tell अगर
			 * this is really the हाल. If not we will have to play
			 * magic at this poपूर्णांक, possibly duplicating a lot of
			 * ntfs_पढ़ो_inode() at this poपूर्णांक. We will need to
			 * ensure we करो enough of its work to be able to call
			 * ntfs_पढ़ो_inode() on extents of $MFT/$DATA. But lets
			 * hope this never happens...
			 */
			ntfs_पढ़ो_locked_inode(vi);
			अगर (is_bad_inode(vi)) अणु
				ntfs_error(sb, "ntfs_read_inode() of $MFT "
						"failed. BUG or corrupt $MFT. "
						"Run chkdsk and if no errors "
						"are found, please report you "
						"saw this message to "
						"linux-ntfs-dev@lists."
						"sourceforge.net");
				ntfs_attr_put_search_ctx(ctx);
				/* Revert to the safe super operations. */
				ntfs_मुक्त(m);
				वापस -1;
			पूर्ण
			/*
			 * Re-initialize some specअगरics about $MFT's inode as
			 * ntfs_पढ़ो_inode() will have set up the शेष ones.
			 */
			/* Set uid and gid to root. */
			vi->i_uid = GLOBAL_ROOT_UID;
			vi->i_gid = GLOBAL_ROOT_GID;
			/* Regular file. No access क्रम anyone. */
			vi->i_mode = S_IFREG;
			/* No VFS initiated operations allowed क्रम $MFT. */
			vi->i_op = &ntfs_empty_inode_ops;
			vi->i_fop = &ntfs_empty_file_ops;
		पूर्ण

		/* Get the lowest vcn क्रम the next extent. */
		highest_vcn = sle64_to_cpu(a->data.non_resident.highest_vcn);
		next_vcn = highest_vcn + 1;

		/* Only one extent or error, which we catch below. */
		अगर (next_vcn <= 0)
			अवरोध;

		/* Aव्योम endless loops due to corruption. */
		अगर (next_vcn < sle64_to_cpu(
				a->data.non_resident.lowest_vcn)) अणु
			ntfs_error(sb, "$MFT has corrupt attribute list "
					"attribute. Run chkdsk.");
			जाओ put_err_out;
		पूर्ण
	पूर्ण
	अगर (err != -ENOENT) अणु
		ntfs_error(sb, "Failed to lookup $MFT/$DATA attribute extent. "
				"$MFT is corrupt. Run chkdsk.");
		जाओ put_err_out;
	पूर्ण
	अगर (!a) अणु
		ntfs_error(sb, "$MFT/$DATA attribute not found. $MFT is "
				"corrupt. Run chkdsk.");
		जाओ put_err_out;
	पूर्ण
	अगर (highest_vcn && highest_vcn != last_vcn - 1) अणु
		ntfs_error(sb, "Failed to load the complete runlist for "
				"$MFT/$DATA. Driver bug or corrupt $MFT. "
				"Run chkdsk.");
		ntfs_debug("highest_vcn = 0x%llx, last_vcn - 1 = 0x%llx",
				(अचिन्हित दीर्घ दीर्घ)highest_vcn,
				(अचिन्हित दीर्घ दीर्घ)last_vcn - 1);
		जाओ put_err_out;
	पूर्ण
	ntfs_attr_put_search_ctx(ctx);
	ntfs_debug("Done.");
	ntfs_मुक्त(m);

	/*
	 * Split the locking rules of the MFT inode from the
	 * locking rules of other inodes:
	 */
	lockdep_set_class(&ni->runlist.lock, &mft_ni_runlist_lock_key);
	lockdep_set_class(&ni->mrec_lock, &mft_ni_mrec_lock_key);

	वापस 0;

em_put_err_out:
	ntfs_error(sb, "Couldn't find first extent of $DATA attribute in "
			"attribute list. $MFT is corrupt. Run chkdsk.");
put_err_out:
	ntfs_attr_put_search_ctx(ctx);
err_out:
	ntfs_error(sb, "Failed. Marking inode as bad.");
	make_bad_inode(vi);
	ntfs_मुक्त(m);
	वापस -1;
पूर्ण

अटल व्योम __ntfs_clear_inode(ntfs_inode *ni)
अणु
	/* Free all alocated memory. */
	करोwn_ग_लिखो(&ni->runlist.lock);
	अगर (ni->runlist.rl) अणु
		ntfs_मुक्त(ni->runlist.rl);
		ni->runlist.rl = शून्य;
	पूर्ण
	up_ग_लिखो(&ni->runlist.lock);

	अगर (ni->attr_list) अणु
		ntfs_मुक्त(ni->attr_list);
		ni->attr_list = शून्य;
	पूर्ण

	करोwn_ग_लिखो(&ni->attr_list_rl.lock);
	अगर (ni->attr_list_rl.rl) अणु
		ntfs_मुक्त(ni->attr_list_rl.rl);
		ni->attr_list_rl.rl = शून्य;
	पूर्ण
	up_ग_लिखो(&ni->attr_list_rl.lock);

	अगर (ni->name_len && ni->name != I30) अणु
		/* Catch bugs... */
		BUG_ON(!ni->name);
		kमुक्त(ni->name);
	पूर्ण
पूर्ण

व्योम ntfs_clear_extent_inode(ntfs_inode *ni)
अणु
	ntfs_debug("Entering for inode 0x%lx.", ni->mft_no);

	BUG_ON(NInoAttr(ni));
	BUG_ON(ni->nr_extents != -1);

#अगर_घोषित NTFS_RW
	अगर (NInoDirty(ni)) अणु
		अगर (!is_bad_inode(VFS_I(ni->ext.base_ntfs_ino)))
			ntfs_error(ni->vol->sb, "Clearing dirty extent inode!  "
					"Losing data!  This is a BUG!!!");
		// FIXME:  Do something!!!
	पूर्ण
#पूर्ण_अगर /* NTFS_RW */

	__ntfs_clear_inode(ni);

	/* Bye, bye... */
	ntfs_destroy_extent_inode(ni);
पूर्ण

/**
 * ntfs_evict_big_inode - clean up the ntfs specअगरic part of an inode
 * @vi:		vfs inode pending annihilation
 *
 * When the VFS is going to हटाओ an inode from memory, ntfs_clear_big_inode()
 * is called, which deallocates all memory beदीर्घing to the NTFS specअगरic part
 * of the inode and वापसs.
 *
 * If the MFT record is dirty, we commit it beक्रमe करोing anything अन्यथा.
 */
व्योम ntfs_evict_big_inode(काष्ठा inode *vi)
अणु
	ntfs_inode *ni = NTFS_I(vi);

	truncate_inode_pages_final(&vi->i_data);
	clear_inode(vi);

#अगर_घोषित NTFS_RW
	अगर (NInoDirty(ni)) अणु
		bool was_bad = (is_bad_inode(vi));

		/* Committing the inode also commits all extent inodes. */
		ntfs_commit_inode(vi);

		अगर (!was_bad && (is_bad_inode(vi) || NInoDirty(ni))) अणु
			ntfs_error(vi->i_sb, "Failed to commit dirty inode "
					"0x%lx.  Losing data!", vi->i_ino);
			// FIXME:  Do something!!!
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* NTFS_RW */

	/* No need to lock at this stage as no one अन्यथा has a reference. */
	अगर (ni->nr_extents > 0) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ni->nr_extents; i++)
			ntfs_clear_extent_inode(ni->ext.extent_ntfs_inos[i]);
		kमुक्त(ni->ext.extent_ntfs_inos);
	पूर्ण

	__ntfs_clear_inode(ni);

	अगर (NInoAttr(ni)) अणु
		/* Release the base inode अगर we are holding it. */
		अगर (ni->nr_extents == -1) अणु
			iput(VFS_I(ni->ext.base_ntfs_ino));
			ni->nr_extents = 0;
			ni->ext.base_ntfs_ino = शून्य;
		पूर्ण
	पूर्ण
	BUG_ON(ni->page);
	अगर (!atomic_dec_and_test(&ni->count))
		BUG();
	वापस;
पूर्ण

/**
 * ntfs_show_options - show mount options in /proc/mounts
 * @sf:		seq_file in which to ग_लिखो our mount options
 * @root:	root of the mounted tree whose mount options to display
 *
 * Called by the VFS once क्रम each mounted ntfs volume when someone पढ़ोs
 * /proc/mounts in order to display the NTFS specअगरic mount options of each
 * mount. The mount options of fs specअगरied by @root are written to the seq file
 * @sf and success is वापसed.
 */
पूर्णांक ntfs_show_options(काष्ठा seq_file *sf, काष्ठा dentry *root)
अणु
	ntfs_volume *vol = NTFS_SB(root->d_sb);
	पूर्णांक i;

	seq_म_लिखो(sf, ",uid=%i", from_kuid_munged(&init_user_ns, vol->uid));
	seq_म_लिखो(sf, ",gid=%i", from_kgid_munged(&init_user_ns, vol->gid));
	अगर (vol->fmask == vol->dmask)
		seq_म_लिखो(sf, ",umask=0%o", vol->fmask);
	अन्यथा अणु
		seq_म_लिखो(sf, ",fmask=0%o", vol->fmask);
		seq_म_लिखो(sf, ",dmask=0%o", vol->dmask);
	पूर्ण
	seq_म_लिखो(sf, ",nls=%s", vol->nls_map->अक्षरset);
	अगर (NVolCaseSensitive(vol))
		seq_म_लिखो(sf, ",case_sensitive");
	अगर (NVolShowSystemFiles(vol))
		seq_म_लिखो(sf, ",show_sys_files");
	अगर (!NVolSparseEnabled(vol))
		seq_म_लिखो(sf, ",disable_sparse");
	क्रम (i = 0; on_errors_arr[i].val; i++) अणु
		अगर (on_errors_arr[i].val & vol->on_errors)
			seq_म_लिखो(sf, ",errors=%s", on_errors_arr[i].str);
	पूर्ण
	seq_म_लिखो(sf, ",mft_zone_multiplier=%i", vol->mft_zone_multiplier);
	वापस 0;
पूर्ण

#अगर_घोषित NTFS_RW

अटल स्थिर अक्षर *es = "  Leaving inconsistent metadata.  Unmount and run "
		"chkdsk.";

/**
 * ntfs_truncate - called when the i_size of an ntfs inode is changed
 * @vi:		inode क्रम which the i_size was changed
 *
 * We only support i_size changes क्रम normal files at present, i.e. not
 * compressed and not encrypted.  This is enक्रमced in ntfs_setattr(), see
 * below.
 *
 * The kernel guarantees that @vi is a regular file (S_ISREG() is true) and
 * that the change is allowed.
 *
 * This implies क्रम us that @vi is a file inode rather than a directory, index,
 * or attribute inode as well as that @vi is a base inode.
 *
 * Returns 0 on success or -त्रुटि_सं on error.
 *
 * Called with ->i_mutex held.
 */
पूर्णांक ntfs_truncate(काष्ठा inode *vi)
अणु
	s64 new_size, old_size, nr_मुक्तd, new_alloc_size, old_alloc_size;
	VCN highest_vcn;
	अचिन्हित दीर्घ flags;
	ntfs_inode *base_ni, *ni = NTFS_I(vi);
	ntfs_volume *vol = ni->vol;
	ntfs_attr_search_ctx *ctx;
	MFT_RECORD *m;
	ATTR_RECORD *a;
	स्थिर अक्षर *te = "  Leaving file length out of sync with i_size.";
	पूर्णांक err, mp_size, size_change, alloc_change;

	ntfs_debug("Entering for inode 0x%lx.", vi->i_ino);
	BUG_ON(NInoAttr(ni));
	BUG_ON(S_ISसूची(vi->i_mode));
	BUG_ON(NInoMstProtected(ni));
	BUG_ON(ni->nr_extents < 0);
retry_truncate:
	/*
	 * Lock the runlist क्रम writing and map the mft record to ensure it is
	 * safe to mess with the attribute runlist and sizes.
	 */
	करोwn_ग_लिखो(&ni->runlist.lock);
	अगर (!NInoAttr(ni))
		base_ni = ni;
	अन्यथा
		base_ni = ni->ext.base_ntfs_ino;
	m = map_mft_record(base_ni);
	अगर (IS_ERR(m)) अणु
		err = PTR_ERR(m);
		ntfs_error(vi->i_sb, "Failed to map mft record for inode 0x%lx "
				"(error code %d).%s", vi->i_ino, err, te);
		ctx = शून्य;
		m = शून्य;
		जाओ old_bad_out;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(base_ni, m);
	अगर (unlikely(!ctx)) अणु
		ntfs_error(vi->i_sb, "Failed to allocate a search context for "
				"inode 0x%lx (not enough memory).%s",
				vi->i_ino, te);
		err = -ENOMEM;
		जाओ old_bad_out;
	पूर्ण
	err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
			CASE_SENSITIVE, 0, शून्य, 0, ctx);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOENT) अणु
			ntfs_error(vi->i_sb, "Open attribute is missing from "
					"mft record.  Inode 0x%lx is corrupt.  "
					"Run chkdsk.%s", vi->i_ino, te);
			err = -EIO;
		पूर्ण अन्यथा
			ntfs_error(vi->i_sb, "Failed to lookup attribute in "
					"inode 0x%lx (error code %d).%s",
					vi->i_ino, err, te);
		जाओ old_bad_out;
	पूर्ण
	m = ctx->mrec;
	a = ctx->attr;
	/*
	 * The i_size of the vfs inode is the new size क्रम the attribute value.
	 */
	new_size = i_size_पढ़ो(vi);
	/* The current size of the attribute value is the old size. */
	old_size = ntfs_attr_size(a);
	/* Calculate the new allocated size. */
	अगर (NInoNonResident(ni))
		new_alloc_size = (new_size + vol->cluster_size - 1) &
				~(s64)vol->cluster_size_mask;
	अन्यथा
		new_alloc_size = (new_size + 7) & ~7;
	/* The current allocated size is the old allocated size. */
	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	old_alloc_size = ni->allocated_size;
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	/*
	 * The change in the file size.  This will be 0 अगर no change, >0 अगर the
	 * size is growing, and <0 अगर the size is shrinking.
	 */
	size_change = -1;
	अगर (new_size - old_size >= 0) अणु
		size_change = 1;
		अगर (new_size == old_size)
			size_change = 0;
	पूर्ण
	/* As above क्रम the allocated size. */
	alloc_change = -1;
	अगर (new_alloc_size - old_alloc_size >= 0) अणु
		alloc_change = 1;
		अगर (new_alloc_size == old_alloc_size)
			alloc_change = 0;
	पूर्ण
	/*
	 * If neither the size nor the allocation are being changed there is
	 * nothing to करो.
	 */
	अगर (!size_change && !alloc_change)
		जाओ unm_करोne;
	/* If the size is changing, check अगर new size is allowed in $AttrDef. */
	अगर (size_change) अणु
		err = ntfs_attr_size_bounds_check(vol, ni->type, new_size);
		अगर (unlikely(err)) अणु
			अगर (err == -दुस्फल) अणु
				ntfs_error(vol->sb, "Truncate would cause the "
						"inode 0x%lx to %simum size "
						"for its attribute type "
						"(0x%x).  Aborting truncate.",
						vi->i_ino,
						new_size > old_size ? "exceed "
						"the max" : "go under the min",
						le32_to_cpu(ni->type));
				err = -EFBIG;
			पूर्ण अन्यथा अणु
				ntfs_error(vol->sb, "Inode 0x%lx has unknown "
						"attribute type 0x%x.  "
						"Aborting truncate.",
						vi->i_ino,
						le32_to_cpu(ni->type));
				err = -EIO;
			पूर्ण
			/* Reset the vfs inode size to the old size. */
			i_size_ग_लिखो(vi, old_size);
			जाओ err_out;
		पूर्ण
	पूर्ण
	अगर (NInoCompressed(ni) || NInoEncrypted(ni)) अणु
		ntfs_warning(vi->i_sb, "Changes in inode size are not "
				"supported yet for %s files, ignoring.",
				NInoCompressed(ni) ? "compressed" :
				"encrypted");
		err = -EOPNOTSUPP;
		जाओ bad_out;
	पूर्ण
	अगर (a->non_resident)
		जाओ करो_non_resident_truncate;
	BUG_ON(NInoNonResident(ni));
	/* Resize the attribute record to best fit the new attribute size. */
	अगर (new_size < vol->mft_record_size &&
			!ntfs_resident_attr_value_resize(m, a, new_size)) अणु
		/* The resize succeeded! */
		flush_dcache_mft_record_page(ctx->ntfs_ino);
		mark_mft_record_dirty(ctx->ntfs_ino);
		ग_लिखो_lock_irqsave(&ni->size_lock, flags);
		/* Update the sizes in the ntfs inode and all is करोne. */
		ni->allocated_size = le32_to_cpu(a->length) -
				le16_to_cpu(a->data.resident.value_offset);
		/*
		 * Note ntfs_resident_attr_value_resize() has alपढ़ोy करोne any
		 * necessary data clearing in the attribute record.  When the
		 * file is being shrunk vmtruncate() will alपढ़ोy have cleared
		 * the top part of the last partial page, i.e. since this is
		 * the resident हाल this is the page with index 0.  However,
		 * when the file is being expanded, the page cache page data
		 * between the old data_size, i.e. old_size, and the new_size
		 * has not been zeroed.  Fortunately, we करो not need to zero it
		 * either since on one hand it will either alपढ़ोy be zero due
		 * to both पढ़ोpage and ग_लिखोpage clearing partial page data
		 * beyond i_size in which हाल there is nothing to करो or in the
		 * हाल of the file being mmap()ped at the same समय, POSIX
		 * specअगरies that the behaviour is unspecअगरied thus we करो not
		 * have to करो anything.  This means that in our implementation
		 * in the rare हाल that the file is mmap()ped and a ग_लिखो
		 * occurred पूर्णांकo the mmap()ped region just beyond the file size
		 * and ग_लिखोpage has not yet been called to ग_लिखो out the page
		 * (which would clear the area beyond the file size) and we now
		 * extend the file size to incorporate this dirty region
		 * outside the file size, a ग_लिखो of the page would result in
		 * this data being written to disk instead of being cleared.
		 * Given both POSIX and the Linux mmap(2) man page specअगरy that
		 * this corner हाल is undefined, we choose to leave it like
		 * that as this is much simpler क्रम us as we cannot lock the
		 * relevant page now since we are holding too many ntfs locks
		 * which would result in a lock reversal deadlock.
		 */
		ni->initialized_size = new_size;
		ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
		जाओ unm_करोne;
	पूर्ण
	/* If the above resize failed, this must be an attribute extension. */
	BUG_ON(size_change < 0);
	/*
	 * We have to drop all the locks so we can call
	 * ntfs_attr_make_non_resident().  This could be optimised by try-
	 * locking the first page cache page and only अगर that fails dropping
	 * the locks, locking the page, and reकरोing all the locking and
	 * lookups.  While this would be a huge optimisation, it is not worth
	 * it as this is definitely a slow code path as it only ever can happen
	 * once क्रम any given file.
	 */
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(base_ni);
	up_ग_लिखो(&ni->runlist.lock);
	/*
	 * Not enough space in the mft record, try to make the attribute
	 * non-resident and अगर successful restart the truncation process.
	 */
	err = ntfs_attr_make_non_resident(ni, old_size);
	अगर (likely(!err))
		जाओ retry_truncate;
	/*
	 * Could not make non-resident.  If this is due to this not being
	 * permitted क्रम this attribute type or there not being enough space,
	 * try to make other attributes non-resident.  Otherwise fail.
	 */
	अगर (unlikely(err != -EPERM && err != -ENOSPC)) अणु
		ntfs_error(vol->sb, "Cannot truncate inode 0x%lx, attribute "
				"type 0x%x, because the conversion from "
				"resident to non-resident attribute failed "
				"with error code %i.", vi->i_ino,
				(अचिन्हित)le32_to_cpu(ni->type), err);
		अगर (err != -ENOMEM)
			err = -EIO;
		जाओ conv_err_out;
	पूर्ण
	/* TODO: Not implemented from here, पात. */
	अगर (err == -ENOSPC)
		ntfs_error(vol->sb, "Not enough space in the mft record/on "
				"disk for the non-resident attribute value.  "
				"This case is not implemented yet.");
	अन्यथा /* अगर (err == -EPERM) */
		ntfs_error(vol->sb, "This attribute type may not be "
				"non-resident.  This case is not implemented "
				"yet.");
	err = -EOPNOTSUPP;
	जाओ conv_err_out;
#अगर 0
	// TODO: Attempt to make other attributes non-resident.
	अगर (!err)
		जाओ करो_resident_extend;
	/*
	 * Both the attribute list attribute and the standard inक्रमmation
	 * attribute must reमुख्य in the base inode.  Thus, अगर this is one of
	 * these attributes, we have to try to move other attributes out पूर्णांकo
	 * extent mft records instead.
	 */
	अगर (ni->type == AT_ATTRIBUTE_LIST ||
			ni->type == AT_STANDARD_INFORMATION) अणु
		// TODO: Attempt to move other attributes पूर्णांकo extent mft
		// records.
		err = -EOPNOTSUPP;
		अगर (!err)
			जाओ करो_resident_extend;
		जाओ err_out;
	पूर्ण
	// TODO: Attempt to move this attribute to an extent mft record, but
	// only अगर it is not alपढ़ोy the only attribute in an mft record in
	// which हाल there would be nothing to gain.
	err = -EOPNOTSUPP;
	अगर (!err)
		जाओ करो_resident_extend;
	/* There is nothing we can करो to make enough space. )-: */
	जाओ err_out;
#पूर्ण_अगर
करो_non_resident_truncate:
	BUG_ON(!NInoNonResident(ni));
	अगर (alloc_change < 0) अणु
		highest_vcn = sle64_to_cpu(a->data.non_resident.highest_vcn);
		अगर (highest_vcn > 0 &&
				old_alloc_size >> vol->cluster_size_bits >
				highest_vcn + 1) अणु
			/*
			 * This attribute has multiple extents.  Not yet
			 * supported.
			 */
			ntfs_error(vol->sb, "Cannot truncate inode 0x%lx, "
					"attribute type 0x%x, because the "
					"attribute is highly fragmented (it "
					"consists of multiple extents) and "
					"this case is not implemented yet.",
					vi->i_ino,
					(अचिन्हित)le32_to_cpu(ni->type));
			err = -EOPNOTSUPP;
			जाओ bad_out;
		पूर्ण
	पूर्ण
	/*
	 * If the size is shrinking, need to reduce the initialized_size and
	 * the data_size beक्रमe reducing the allocation.
	 */
	अगर (size_change < 0) अणु
		/*
		 * Make the valid size smaller (i_size is alपढ़ोy up-to-date).
		 */
		ग_लिखो_lock_irqsave(&ni->size_lock, flags);
		अगर (new_size < ni->initialized_size) अणु
			ni->initialized_size = new_size;
			a->data.non_resident.initialized_size =
					cpu_to_sle64(new_size);
		पूर्ण
		a->data.non_resident.data_size = cpu_to_sle64(new_size);
		ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
		flush_dcache_mft_record_page(ctx->ntfs_ino);
		mark_mft_record_dirty(ctx->ntfs_ino);
		/* If the allocated size is not changing, we are करोne. */
		अगर (!alloc_change)
			जाओ unm_करोne;
		/*
		 * If the size is shrinking it makes no sense क्रम the
		 * allocation to be growing.
		 */
		BUG_ON(alloc_change > 0);
	पूर्ण अन्यथा /* अगर (size_change >= 0) */ अणु
		/*
		 * The file size is growing or staying the same but the
		 * allocation can be shrinking, growing or staying the same.
		 */
		अगर (alloc_change > 0) अणु
			/*
			 * We need to extend the allocation and possibly update
			 * the data size.  If we are updating the data size,
			 * since we are not touching the initialized_size we करो
			 * not need to worry about the actual data on disk.
			 * And as far as the page cache is concerned, there
			 * will be no pages beyond the old data size and any
			 * partial region in the last page between the old and
			 * new data size (or the end of the page अगर the new
			 * data size is outside the page) करोes not need to be
			 * modअगरied as explained above क्रम the resident
			 * attribute truncate हाल.  To करो this, we simply drop
			 * the locks we hold and leave all the work to our
			 * मित्रly helper ntfs_attr_extend_allocation().
			 */
			ntfs_attr_put_search_ctx(ctx);
			unmap_mft_record(base_ni);
			up_ग_लिखो(&ni->runlist.lock);
			err = ntfs_attr_extend_allocation(ni, new_size,
					size_change > 0 ? new_size : -1, -1);
			/*
			 * ntfs_attr_extend_allocation() will have करोne error
			 * output alपढ़ोy.
			 */
			जाओ करोne;
		पूर्ण
		अगर (!alloc_change)
			जाओ alloc_करोne;
	पूर्ण
	/* alloc_change < 0 */
	/* Free the clusters. */
	nr_मुक्तd = ntfs_cluster_मुक्त(ni, new_alloc_size >>
			vol->cluster_size_bits, -1, ctx);
	m = ctx->mrec;
	a = ctx->attr;
	अगर (unlikely(nr_मुक्तd < 0)) अणु
		ntfs_error(vol->sb, "Failed to release cluster(s) (error code "
				"%lli).  Unmount and run chkdsk to recover "
				"the lost cluster(s).", (दीर्घ दीर्घ)nr_मुक्तd);
		NVolSetErrors(vol);
		nr_मुक्तd = 0;
	पूर्ण
	/* Truncate the runlist. */
	err = ntfs_rl_truncate_nolock(vol, &ni->runlist,
			new_alloc_size >> vol->cluster_size_bits);
	/*
	 * If the runlist truncation failed and/or the search context is no
	 * दीर्घer valid, we cannot resize the attribute record or build the
	 * mapping pairs array thus we mark the inode bad so that no access to
	 * the मुक्तd clusters can happen.
	 */
	अगर (unlikely(err || IS_ERR(m))) अणु
		ntfs_error(vol->sb, "Failed to %s (error code %li).%s",
				IS_ERR(m) ?
				"restore attribute search context" :
				"truncate attribute runlist",
				IS_ERR(m) ? PTR_ERR(m) : err, es);
		err = -EIO;
		जाओ bad_out;
	पूर्ण
	/* Get the size क्रम the shrunk mapping pairs array क्रम the runlist. */
	mp_size = ntfs_get_size_क्रम_mapping_pairs(vol, ni->runlist.rl, 0, -1);
	अगर (unlikely(mp_size <= 0)) अणु
		ntfs_error(vol->sb, "Cannot shrink allocation of inode 0x%lx, "
				"attribute type 0x%x, because determining the "
				"size for the mapping pairs failed with error "
				"code %i.%s", vi->i_ino,
				(अचिन्हित)le32_to_cpu(ni->type), mp_size, es);
		err = -EIO;
		जाओ bad_out;
	पूर्ण
	/*
	 * Shrink the attribute record क्रम the new mapping pairs array.  Note,
	 * this cannot fail since we are making the attribute smaller thus by
	 * definition there is enough space to करो so.
	 */
	err = ntfs_attr_record_resize(m, a, mp_size +
			le16_to_cpu(a->data.non_resident.mapping_pairs_offset));
	BUG_ON(err);
	/*
	 * Generate the mapping pairs array directly पूर्णांकo the attribute record.
	 */
	err = ntfs_mapping_pairs_build(vol, (u8*)a +
			le16_to_cpu(a->data.non_resident.mapping_pairs_offset),
			mp_size, ni->runlist.rl, 0, -1, शून्य);
	अगर (unlikely(err)) अणु
		ntfs_error(vol->sb, "Cannot shrink allocation of inode 0x%lx, "
				"attribute type 0x%x, because building the "
				"mapping pairs failed with error code %i.%s",
				vi->i_ino, (अचिन्हित)le32_to_cpu(ni->type),
				err, es);
		err = -EIO;
		जाओ bad_out;
	पूर्ण
	/* Update the allocated/compressed size as well as the highest vcn. */
	a->data.non_resident.highest_vcn = cpu_to_sle64((new_alloc_size >>
			vol->cluster_size_bits) - 1);
	ग_लिखो_lock_irqsave(&ni->size_lock, flags);
	ni->allocated_size = new_alloc_size;
	a->data.non_resident.allocated_size = cpu_to_sle64(new_alloc_size);
	अगर (NInoSparse(ni) || NInoCompressed(ni)) अणु
		अगर (nr_मुक्तd) अणु
			ni->itype.compressed.size -= nr_मुक्तd <<
					vol->cluster_size_bits;
			BUG_ON(ni->itype.compressed.size < 0);
			a->data.non_resident.compressed_size = cpu_to_sle64(
					ni->itype.compressed.size);
			vi->i_blocks = ni->itype.compressed.size >> 9;
		पूर्ण
	पूर्ण अन्यथा
		vi->i_blocks = new_alloc_size >> 9;
	ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
	/*
	 * We have shrunk the allocation.  If this is a shrinking truncate we
	 * have alपढ़ोy dealt with the initialized_size and the data_size above
	 * and we are करोne.  If the truncate is only changing the allocation
	 * and not the data_size, we are also करोne.  If this is an extending
	 * truncate, need to extend the data_size now which is ensured by the
	 * fact that @size_change is positive.
	 */
alloc_करोne:
	/*
	 * If the size is growing, need to update it now.  If it is shrinking,
	 * we have alपढ़ोy updated it above (beक्रमe the allocation change).
	 */
	अगर (size_change > 0)
		a->data.non_resident.data_size = cpu_to_sle64(new_size);
	/* Ensure the modअगरied mft record is written out. */
	flush_dcache_mft_record_page(ctx->ntfs_ino);
	mark_mft_record_dirty(ctx->ntfs_ino);
unm_करोne:
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(base_ni);
	up_ग_लिखो(&ni->runlist.lock);
करोne:
	/* Update the mसमय and स_समय on the base inode. */
	/* normally ->truncate shouldn't update स_समय or mसमय,
	 * but ntfs did beक्रमe so it got a copy & paste version
	 * of file_update_समय.  one day someone should fix this
	 * क्रम real.
	 */
	अगर (!IS_NOCMTIME(VFS_I(base_ni)) && !IS_RDONLY(VFS_I(base_ni))) अणु
		काष्ठा बारpec64 now = current_समय(VFS_I(base_ni));
		पूर्णांक sync_it = 0;

		अगर (!बारpec64_equal(&VFS_I(base_ni)->i_mसमय, &now) ||
		    !बारpec64_equal(&VFS_I(base_ni)->i_स_समय, &now))
			sync_it = 1;
		VFS_I(base_ni)->i_mसमय = now;
		VFS_I(base_ni)->i_स_समय = now;

		अगर (sync_it)
			mark_inode_dirty_sync(VFS_I(base_ni));
	पूर्ण

	अगर (likely(!err)) अणु
		NInoClearTruncateFailed(ni);
		ntfs_debug("Done.");
	पूर्ण
	वापस err;
old_bad_out:
	old_size = -1;
bad_out:
	अगर (err != -ENOMEM && err != -EOPNOTSUPP)
		NVolSetErrors(vol);
	अगर (err != -EOPNOTSUPP)
		NInoSetTruncateFailed(ni);
	अन्यथा अगर (old_size >= 0)
		i_size_ग_लिखो(vi, old_size);
err_out:
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (m)
		unmap_mft_record(base_ni);
	up_ग_लिखो(&ni->runlist.lock);
out:
	ntfs_debug("Failed.  Returning error code %i.", err);
	वापस err;
conv_err_out:
	अगर (err != -ENOMEM && err != -EOPNOTSUPP)
		NVolSetErrors(vol);
	अगर (err != -EOPNOTSUPP)
		NInoSetTruncateFailed(ni);
	अन्यथा
		i_size_ग_लिखो(vi, old_size);
	जाओ out;
पूर्ण

/**
 * ntfs_truncate_vfs - wrapper क्रम ntfs_truncate() that has no वापस value
 * @vi:		inode क्रम which the i_size was changed
 *
 * Wrapper क्रम ntfs_truncate() that has no वापस value.
 *
 * See ntfs_truncate() description above क्रम details.
 */
#अगर_घोषित NTFS_RW
व्योम ntfs_truncate_vfs(काष्ठा inode *vi) अणु
	ntfs_truncate(vi);
पूर्ण
#पूर्ण_अगर

/**
 * ntfs_setattr - called from notअगरy_change() when an attribute is being changed
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dentry:	dentry whose attributes to change
 * @attr:	काष्ठाure describing the attributes and the changes
 *
 * We have to trap VFS attempts to truncate the file described by @dentry as
 * soon as possible, because we करो not implement changes in i_size yet.  So we
 * पात all i_size changes here.
 *
 * We also पात all changes of user, group, and mode as we करो not implement
 * the NTFS ACLs yet.
 *
 * Called with ->i_mutex held.
 */
पूर्णांक ntfs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		 काष्ठा iattr *attr)
अणु
	काष्ठा inode *vi = d_inode(dentry);
	पूर्णांक err;
	अचिन्हित पूर्णांक ia_valid = attr->ia_valid;

	err = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (err)
		जाओ out;
	/* We करो not support NTFS ACLs yet. */
	अगर (ia_valid & (ATTR_UID | ATTR_GID | ATTR_MODE)) अणु
		ntfs_warning(vi->i_sb, "Changes in user/group/mode are not "
				"supported yet, ignoring.");
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	अगर (ia_valid & ATTR_SIZE) अणु
		अगर (attr->ia_size != i_size_पढ़ो(vi)) अणु
			ntfs_inode *ni = NTFS_I(vi);
			/*
			 * FIXME: For now we करो not support resizing of
			 * compressed or encrypted files yet.
			 */
			अगर (NInoCompressed(ni) || NInoEncrypted(ni)) अणु
				ntfs_warning(vi->i_sb, "Changes in inode size "
						"are not supported yet for "
						"%s files, ignoring.",
						NInoCompressed(ni) ?
						"compressed" : "encrypted");
				err = -EOPNOTSUPP;
			पूर्ण अन्यथा अणु
				truncate_setsize(vi, attr->ia_size);
				ntfs_truncate_vfs(vi);
			पूर्ण
			अगर (err || ia_valid == ATTR_SIZE)
				जाओ out;
		पूर्ण अन्यथा अणु
			/*
			 * We skipped the truncate but must still update
			 * बारtamps.
			 */
			ia_valid |= ATTR_MTIME | ATTR_CTIME;
		पूर्ण
	पूर्ण
	अगर (ia_valid & ATTR_ATIME)
		vi->i_aसमय = attr->ia_aसमय;
	अगर (ia_valid & ATTR_MTIME)
		vi->i_mसमय = attr->ia_mसमय;
	अगर (ia_valid & ATTR_CTIME)
		vi->i_स_समय = attr->ia_स_समय;
	mark_inode_dirty(vi);
out:
	वापस err;
पूर्ण

/**
 * ntfs_ग_लिखो_inode - ग_लिखो out a dirty inode
 * @vi:		inode to ग_लिखो out
 * @sync:	अगर true, ग_लिखो out synchronously
 *
 * Write out a dirty inode to disk including any extent inodes अगर present.
 *
 * If @sync is true, commit the inode to disk and रुको क्रम io completion.  This
 * is करोne using ग_लिखो_mft_record().
 *
 * If @sync is false, just schedule the ग_लिखो to happen but करो not रुको क्रम i/o
 * completion.  In 2.6 kernels, scheduling usually happens just by virtue of
 * marking the page (and in this हाल mft record) dirty but we करो not implement
 * this yet as ग_लिखो_mft_record() largely ignores the @sync parameter and
 * always perक्रमms synchronous ग_लिखोs.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 */
पूर्णांक __ntfs_ग_लिखो_inode(काष्ठा inode *vi, पूर्णांक sync)
अणु
	sle64 nt;
	ntfs_inode *ni = NTFS_I(vi);
	ntfs_attr_search_ctx *ctx;
	MFT_RECORD *m;
	STANDARD_INFORMATION *si;
	पूर्णांक err = 0;
	bool modअगरied = false;

	ntfs_debug("Entering for %sinode 0x%lx.", NInoAttr(ni) ? "attr " : "",
			vi->i_ino);
	/*
	 * Dirty attribute inodes are written via their real inodes so just
	 * clean them here.  Access समय updates are taken care off when the
	 * real inode is written.
	 */
	अगर (NInoAttr(ni)) अणु
		NInoClearDirty(ni);
		ntfs_debug("Done.");
		वापस 0;
	पूर्ण
	/* Map, pin, and lock the mft record beदीर्घing to the inode. */
	m = map_mft_record(ni);
	अगर (IS_ERR(m)) अणु
		err = PTR_ERR(m);
		जाओ err_out;
	पूर्ण
	/* Update the access बार in the standard inक्रमmation attribute. */
	ctx = ntfs_attr_get_search_ctx(ni, m);
	अगर (unlikely(!ctx)) अणु
		err = -ENOMEM;
		जाओ unm_err_out;
	पूर्ण
	err = ntfs_attr_lookup(AT_STANDARD_INFORMATION, शून्य, 0,
			CASE_SENSITIVE, 0, शून्य, 0, ctx);
	अगर (unlikely(err)) अणु
		ntfs_attr_put_search_ctx(ctx);
		जाओ unm_err_out;
	पूर्ण
	si = (STANDARD_INFORMATION*)((u8*)ctx->attr +
			le16_to_cpu(ctx->attr->data.resident.value_offset));
	/* Update the access बार अगर they have changed. */
	nt = utc2ntfs(vi->i_mसमय);
	अगर (si->last_data_change_समय != nt) अणु
		ntfs_debug("Updating mtime for inode 0x%lx: old = 0x%llx, "
				"new = 0x%llx", vi->i_ino, (दीर्घ दीर्घ)
				sle64_to_cpu(si->last_data_change_समय),
				(दीर्घ दीर्घ)sle64_to_cpu(nt));
		si->last_data_change_समय = nt;
		modअगरied = true;
	पूर्ण
	nt = utc2ntfs(vi->i_स_समय);
	अगर (si->last_mft_change_समय != nt) अणु
		ntfs_debug("Updating ctime for inode 0x%lx: old = 0x%llx, "
				"new = 0x%llx", vi->i_ino, (दीर्घ दीर्घ)
				sle64_to_cpu(si->last_mft_change_समय),
				(दीर्घ दीर्घ)sle64_to_cpu(nt));
		si->last_mft_change_समय = nt;
		modअगरied = true;
	पूर्ण
	nt = utc2ntfs(vi->i_aसमय);
	अगर (si->last_access_समय != nt) अणु
		ntfs_debug("Updating atime for inode 0x%lx: old = 0x%llx, "
				"new = 0x%llx", vi->i_ino,
				(दीर्घ दीर्घ)sle64_to_cpu(si->last_access_समय),
				(दीर्घ दीर्घ)sle64_to_cpu(nt));
		si->last_access_समय = nt;
		modअगरied = true;
	पूर्ण
	/*
	 * If we just modअगरied the standard inक्रमmation attribute we need to
	 * mark the mft record it is in dirty.  We करो this manually so that
	 * mark_inode_dirty() is not called which would redirty the inode and
	 * hence result in an infinite loop of trying to ग_लिखो the inode.
	 * There is no need to mark the base inode nor the base mft record
	 * dirty, since we are going to ग_लिखो this mft record below in any हाल
	 * and the base mft record may actually not have been modअगरied so it
	 * might not need to be written out.
	 * NOTE: It is not a problem when the inode क्रम $MFT itself is being
	 * written out as mark_ntfs_record_dirty() will only set I_सूचीTY_PAGES
	 * on the $MFT inode and hence ntfs_ग_लिखो_inode() will not be
	 * re-invoked because of it which in turn is ok since the dirtied mft
	 * record will be cleaned and written out to disk below, i.e. beक्रमe
	 * this function वापसs.
	 */
	अगर (modअगरied) अणु
		flush_dcache_mft_record_page(ctx->ntfs_ino);
		अगर (!NInoTestSetDirty(ctx->ntfs_ino))
			mark_ntfs_record_dirty(ctx->ntfs_ino->page,
					ctx->ntfs_ino->page_ofs);
	पूर्ण
	ntfs_attr_put_search_ctx(ctx);
	/* Now the access बार are updated, ग_लिखो the base mft record. */
	अगर (NInoDirty(ni))
		err = ग_लिखो_mft_record(ni, m, sync);
	/* Write all attached extent mft records. */
	mutex_lock(&ni->extent_lock);
	अगर (ni->nr_extents > 0) अणु
		ntfs_inode **extent_nis = ni->ext.extent_ntfs_inos;
		पूर्णांक i;

		ntfs_debug("Writing %i extent inodes.", ni->nr_extents);
		क्रम (i = 0; i < ni->nr_extents; i++) अणु
			ntfs_inode *tni = extent_nis[i];

			अगर (NInoDirty(tni)) अणु
				MFT_RECORD *पंचांग = map_mft_record(tni);
				पूर्णांक ret;

				अगर (IS_ERR(पंचांग)) अणु
					अगर (!err || err == -ENOMEM)
						err = PTR_ERR(पंचांग);
					जारी;
				पूर्ण
				ret = ग_लिखो_mft_record(tni, पंचांग, sync);
				unmap_mft_record(tni);
				अगर (unlikely(ret)) अणु
					अगर (!err || err == -ENOMEM)
						err = ret;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&ni->extent_lock);
	unmap_mft_record(ni);
	अगर (unlikely(err))
		जाओ err_out;
	ntfs_debug("Done.");
	वापस 0;
unm_err_out:
	unmap_mft_record(ni);
err_out:
	अगर (err == -ENOMEM) अणु
		ntfs_warning(vi->i_sb, "Not enough memory to write inode.  "
				"Marking the inode dirty again, so the VFS "
				"retries later.");
		mark_inode_dirty(vi);
	पूर्ण अन्यथा अणु
		ntfs_error(vi->i_sb, "Failed (error %i):  Run chkdsk.", -err);
		NVolSetErrors(ni->vol);
	पूर्ण
	वापस err;
पूर्ण

#पूर्ण_अगर /* NTFS_RW */
