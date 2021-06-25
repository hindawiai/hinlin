<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/affs/amigaffs.c
 *
 *  (c) 1996  Hans-Joachim Widmaier - Rewritten
 *
 *  (C) 1993  Ray Burr - Amiga FFS fileप्रणाली.
 *
 *  Please send bug reports to: hjw@zvw.de
 */

#समावेश <linux/math64.h>
#समावेश <linux/iversion.h>
#समावेश "affs.h"

/*
 * Functions क्रम accessing Amiga-FFS काष्ठाures.
 */


/* Insert a header block bh पूर्णांकo the directory dir
 * caller must hold AFFS_सूची->i_hash_lock!
 */

पूर्णांक
affs_insert_hash(काष्ठा inode *dir, काष्ठा buffer_head *bh)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा buffer_head *dir_bh;
	u32 ino, hash_ino;
	पूर्णांक offset;

	ino = bh->b_blocknr;
	offset = affs_hash_name(sb, AFFS_TAIL(sb, bh)->name + 1, AFFS_TAIL(sb, bh)->name[0]);

	pr_debug("%s(dir=%lu, ino=%d)\n", __func__, dir->i_ino, ino);

	dir_bh = affs_bपढ़ो(sb, dir->i_ino);
	अगर (!dir_bh)
		वापस -EIO;

	hash_ino = be32_to_cpu(AFFS_HEAD(dir_bh)->table[offset]);
	जबतक (hash_ino) अणु
		affs_brअन्यथा(dir_bh);
		dir_bh = affs_bपढ़ो(sb, hash_ino);
		अगर (!dir_bh)
			वापस -EIO;
		hash_ino = be32_to_cpu(AFFS_TAIL(sb, dir_bh)->hash_chain);
	पूर्ण
	AFFS_TAIL(sb, bh)->parent = cpu_to_be32(dir->i_ino);
	AFFS_TAIL(sb, bh)->hash_chain = 0;
	affs_fix_checksum(sb, bh);

	अगर (dir->i_ino == dir_bh->b_blocknr)
		AFFS_HEAD(dir_bh)->table[offset] = cpu_to_be32(ino);
	अन्यथा
		AFFS_TAIL(sb, dir_bh)->hash_chain = cpu_to_be32(ino);

	affs_adjust_checksum(dir_bh, ino);
	mark_buffer_dirty_inode(dir_bh, dir);
	affs_brअन्यथा(dir_bh);

	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	inode_inc_iversion(dir);
	mark_inode_dirty(dir);

	वापस 0;
पूर्ण

/* Remove a header block from its directory.
 * caller must hold AFFS_सूची->i_hash_lock!
 */

पूर्णांक
affs_हटाओ_hash(काष्ठा inode *dir, काष्ठा buffer_head *rem_bh)
अणु
	काष्ठा super_block *sb;
	काष्ठा buffer_head *bh;
	u32 rem_ino, hash_ino;
	__be32 ino;
	पूर्णांक offset, retval;

	sb = dir->i_sb;
	rem_ino = rem_bh->b_blocknr;
	offset = affs_hash_name(sb, AFFS_TAIL(sb, rem_bh)->name+1, AFFS_TAIL(sb, rem_bh)->name[0]);
	pr_debug("%s(dir=%lu, ino=%d, hashval=%d)\n", __func__, dir->i_ino,
		 rem_ino, offset);

	bh = affs_bपढ़ो(sb, dir->i_ino);
	अगर (!bh)
		वापस -EIO;

	retval = -ENOENT;
	hash_ino = be32_to_cpu(AFFS_HEAD(bh)->table[offset]);
	जबतक (hash_ino) अणु
		अगर (hash_ino == rem_ino) अणु
			ino = AFFS_TAIL(sb, rem_bh)->hash_chain;
			अगर (dir->i_ino == bh->b_blocknr)
				AFFS_HEAD(bh)->table[offset] = ino;
			अन्यथा
				AFFS_TAIL(sb, bh)->hash_chain = ino;
			affs_adjust_checksum(bh, be32_to_cpu(ino) - hash_ino);
			mark_buffer_dirty_inode(bh, dir);
			AFFS_TAIL(sb, rem_bh)->parent = 0;
			retval = 0;
			अवरोध;
		पूर्ण
		affs_brअन्यथा(bh);
		bh = affs_bपढ़ो(sb, hash_ino);
		अगर (!bh)
			वापस -EIO;
		hash_ino = be32_to_cpu(AFFS_TAIL(sb, bh)->hash_chain);
	पूर्ण

	affs_brअन्यथा(bh);

	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	inode_inc_iversion(dir);
	mark_inode_dirty(dir);

	वापस retval;
पूर्ण

अटल व्योम
affs_fix_dcache(काष्ठा inode *inode, u32 entry_ino)
अणु
	काष्ठा dentry *dentry;
	spin_lock(&inode->i_lock);
	hlist_क्रम_each_entry(dentry, &inode->i_dentry, d_u.d_alias) अणु
		अगर (entry_ino == (u32)(दीर्घ)dentry->d_fsdata) अणु
			dentry->d_fsdata = (व्योम *)inode->i_ino;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&inode->i_lock);
पूर्ण


/* Remove header from link chain */

अटल पूर्णांक
affs_हटाओ_link(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *dir, *inode = d_inode(dentry);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *bh, *link_bh = शून्य;
	u32 link_ino, ino;
	पूर्णांक retval;

	pr_debug("%s(key=%ld)\n", __func__, inode->i_ino);
	retval = -EIO;
	bh = affs_bपढ़ो(sb, inode->i_ino);
	अगर (!bh)
		जाओ करोne;

	link_ino = (u32)(दीर्घ)dentry->d_fsdata;
	अगर (inode->i_ino == link_ino) अणु
		/* we can't हटाओ the head of the link, as its blocknr is still used as ino,
		 * so we हटाओ the block of the first link instead.
		 */ 
		link_ino = be32_to_cpu(AFFS_TAIL(sb, bh)->link_chain);
		link_bh = affs_bपढ़ो(sb, link_ino);
		अगर (!link_bh)
			जाओ करोne;

		dir = affs_iget(sb, be32_to_cpu(AFFS_TAIL(sb, link_bh)->parent));
		अगर (IS_ERR(dir)) अणु
			retval = PTR_ERR(dir);
			जाओ करोne;
		पूर्ण

		affs_lock_dir(dir);
		/*
		 * अगर there's a dentry क्रम that block, make it
		 * refer to inode itself.
		 */
		affs_fix_dcache(inode, link_ino);
		retval = affs_हटाओ_hash(dir, link_bh);
		अगर (retval) अणु
			affs_unlock_dir(dir);
			जाओ करोne;
		पूर्ण
		mark_buffer_dirty_inode(link_bh, inode);

		स_नकल(AFFS_TAIL(sb, bh)->name, AFFS_TAIL(sb, link_bh)->name, 32);
		retval = affs_insert_hash(dir, bh);
		अगर (retval) अणु
			affs_unlock_dir(dir);
			जाओ करोne;
		पूर्ण
		mark_buffer_dirty_inode(bh, inode);

		affs_unlock_dir(dir);
		iput(dir);
	पूर्ण अन्यथा अणु
		link_bh = affs_bपढ़ो(sb, link_ino);
		अगर (!link_bh)
			जाओ करोne;
	पूर्ण

	जबतक ((ino = be32_to_cpu(AFFS_TAIL(sb, bh)->link_chain)) != 0) अणु
		अगर (ino == link_ino) अणु
			__be32 ino2 = AFFS_TAIL(sb, link_bh)->link_chain;
			AFFS_TAIL(sb, bh)->link_chain = ino2;
			affs_adjust_checksum(bh, be32_to_cpu(ino2) - link_ino);
			mark_buffer_dirty_inode(bh, inode);
			retval = 0;
			/* Fix the link count, अगर bh is a normal header block without links */
			चयन (be32_to_cpu(AFFS_TAIL(sb, bh)->stype)) अणु
			हाल ST_LINKसूची:
			हाल ST_LINKखाता:
				अवरोध;
			शेष:
				अगर (!AFFS_TAIL(sb, bh)->link_chain)
					set_nlink(inode, 1);
			पूर्ण
			affs_मुक्त_block(sb, link_ino);
			जाओ करोne;
		पूर्ण
		affs_brअन्यथा(bh);
		bh = affs_bपढ़ो(sb, ino);
		अगर (!bh)
			जाओ करोne;
	पूर्ण
	retval = -ENOENT;
करोne:
	affs_brअन्यथा(link_bh);
	affs_brअन्यथा(bh);
	वापस retval;
पूर्ण


अटल पूर्णांक
affs_empty_dir(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *bh;
	पूर्णांक retval, size;

	retval = -EIO;
	bh = affs_bपढ़ो(sb, inode->i_ino);
	अगर (!bh)
		जाओ करोne;

	retval = -ENOTEMPTY;
	क्रम (size = AFFS_SB(sb)->s_hashsize - 1; size >= 0; size--)
		अगर (AFFS_HEAD(bh)->table[size])
			जाओ not_empty;
	retval = 0;
not_empty:
	affs_brअन्यथा(bh);
करोne:
	वापस retval;
पूर्ण


/* Remove a fileप्रणाली object. If the object to be हटाओd has
 * links to it, one of the links must be changed to inherit
 * the file or directory. As above, any inode will करो.
 * The buffer will not be मुक्तd. If the header is a link, the
 * block will be marked as मुक्त.
 * This function वापसs a negative error number in हाल of
 * an error, अन्यथा 0 अगर the inode is to be deleted or 1 अगर not.
 */

पूर्णांक
affs_हटाओ_header(काष्ठा dentry *dentry)
अणु
	काष्ठा super_block *sb;
	काष्ठा inode *inode, *dir;
	काष्ठा buffer_head *bh = शून्य;
	पूर्णांक retval;

	dir = d_inode(dentry->d_parent);
	sb = dir->i_sb;

	retval = -ENOENT;
	inode = d_inode(dentry);
	अगर (!inode)
		जाओ करोne;

	pr_debug("%s(key=%ld)\n", __func__, inode->i_ino);
	retval = -EIO;
	bh = affs_bपढ़ो(sb, (u32)(दीर्घ)dentry->d_fsdata);
	अगर (!bh)
		जाओ करोne;

	affs_lock_link(inode);
	affs_lock_dir(dir);
	चयन (be32_to_cpu(AFFS_TAIL(sb, bh)->stype)) अणु
	हाल ST_USERसूची:
		/* अगर we ever want to support links to dirs
		 * i_hash_lock of the inode must only be
		 * taken after some checks
		 */
		affs_lock_dir(inode);
		retval = affs_empty_dir(inode);
		affs_unlock_dir(inode);
		अगर (retval)
			जाओ करोne_unlock;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	retval = affs_हटाओ_hash(dir, bh);
	अगर (retval)
		जाओ करोne_unlock;
	mark_buffer_dirty_inode(bh, inode);

	affs_unlock_dir(dir);

	अगर (inode->i_nlink > 1)
		retval = affs_हटाओ_link(dentry);
	अन्यथा
		clear_nlink(inode);
	affs_unlock_link(inode);
	inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);

करोne:
	affs_brअन्यथा(bh);
	वापस retval;

करोne_unlock:
	affs_unlock_dir(dir);
	affs_unlock_link(inode);
	जाओ करोne;
पूर्ण

/* Checksum a block, करो various consistency checks and optionally वापस
   the blocks type number.  DATA poपूर्णांकs to the block.  If their poपूर्णांकers
   are non-null, *PTYPE and *STYPE are set to the primary and secondary
   block types respectively, *HASHSIZE is set to the size of the hashtable
   (which lets us calculate the block size).
   Returns non-zero अगर the block is not consistent. */

u32
affs_checksum_block(काष्ठा super_block *sb, काष्ठा buffer_head *bh)
अणु
	__be32 *ptr = (__be32 *)bh->b_data;
	u32 sum;
	पूर्णांक bsize;

	sum = 0;
	क्रम (bsize = sb->s_blocksize / माप(__be32); bsize > 0; bsize--)
		sum += be32_to_cpu(*ptr++);
	वापस sum;
पूर्ण

/*
 * Calculate the checksum of a disk block and store it
 * at the indicated position.
 */

व्योम
affs_fix_checksum(काष्ठा super_block *sb, काष्ठा buffer_head *bh)
अणु
	पूर्णांक cnt = sb->s_blocksize / माप(__be32);
	__be32 *ptr = (__be32 *)bh->b_data;
	u32 checksum;
	__be32 *checksumptr;

	checksumptr = ptr + 5;
	*checksumptr = 0;
	क्रम (checksum = 0; cnt > 0; ptr++, cnt--)
		checksum += be32_to_cpu(*ptr);
	*checksumptr = cpu_to_be32(-checksum);
पूर्ण

व्योम
affs_secs_to_datestamp(समय64_t secs, काष्ठा affs_date *ds)
अणु
	u32	 days;
	u32	 minute;
	s32	 rem;

	secs -= sys_tz.tz_minuteswest * 60 + AFFS_EPOCH_DELTA;
	अगर (secs < 0)
		secs = 0;
	days    = भाग_s64_rem(secs, 86400, &rem);
	minute  = rem / 60;
	rem    -= minute * 60;

	ds->days = cpu_to_be32(days);
	ds->mins = cpu_to_be32(minute);
	ds->ticks = cpu_to_be32(rem * 50);
पूर्ण

umode_t
affs_prot_to_mode(u32 prot)
अणु
	umode_t mode = 0;

	अगर (!(prot & FIBF_NOWRITE))
		mode |= 0200;
	अगर (!(prot & FIBF_NOREAD))
		mode |= 0400;
	अगर (!(prot & FIBF_NOEXECUTE))
		mode |= 0100;
	अगर (prot & FIBF_GRP_WRITE)
		mode |= 0020;
	अगर (prot & FIBF_GRP_READ)
		mode |= 0040;
	अगर (prot & FIBF_GRP_EXECUTE)
		mode |= 0010;
	अगर (prot & FIBF_OTR_WRITE)
		mode |= 0002;
	अगर (prot & FIBF_OTR_READ)
		mode |= 0004;
	अगर (prot & FIBF_OTR_EXECUTE)
		mode |= 0001;

	वापस mode;
पूर्ण

व्योम
affs_mode_to_prot(काष्ठा inode *inode)
अणु
	u32 prot = AFFS_I(inode)->i_protect;
	umode_t mode = inode->i_mode;

	/*
	 * First, clear all RWED bits क्रम owner, group, other.
	 * Then, recalculate them afresh.
	 *
	 * We'll always clear the delete-inhibit bit क्रम the owner, as that is
	 * the classic single-user mode AmigaOS protection bit and we need to
	 * stay compatible with all scenarios.
	 *
	 * Since multi-user AmigaOS is an extension, we'll only set the
	 * delete-allow bit अगर any of the other bits in the same user class
	 * (group/other) are used.
	 */
	prot &= ~(FIBF_NOEXECUTE | FIBF_NOREAD
		  | FIBF_NOWRITE | FIBF_NODELETE
		  | FIBF_GRP_EXECUTE | FIBF_GRP_READ
		  | FIBF_GRP_WRITE   | FIBF_GRP_DELETE
		  | FIBF_OTR_EXECUTE | FIBF_OTR_READ
		  | FIBF_OTR_WRITE   | FIBF_OTR_DELETE);

	/* Classic single-user AmigaOS flags. These are inverted. */
	अगर (!(mode & 0100))
		prot |= FIBF_NOEXECUTE;
	अगर (!(mode & 0400))
		prot |= FIBF_NOREAD;
	अगर (!(mode & 0200))
		prot |= FIBF_NOWRITE;

	/* Multi-user extended flags. Not inverted. */
	अगर (mode & 0010)
		prot |= FIBF_GRP_EXECUTE;
	अगर (mode & 0040)
		prot |= FIBF_GRP_READ;
	अगर (mode & 0020)
		prot |= FIBF_GRP_WRITE;
	अगर (mode & 0070)
		prot |= FIBF_GRP_DELETE;

	अगर (mode & 0001)
		prot |= FIBF_OTR_EXECUTE;
	अगर (mode & 0004)
		prot |= FIBF_OTR_READ;
	अगर (mode & 0002)
		prot |= FIBF_OTR_WRITE;
	अगर (mode & 0007)
		prot |= FIBF_OTR_DELETE;

	AFFS_I(inode)->i_protect = prot;
पूर्ण

व्योम
affs_error(काष्ठा super_block *sb, स्थिर अक्षर *function, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	pr_crit("error (device %s): %s(): %pV\n", sb->s_id, function, &vaf);
	अगर (!sb_rकरोnly(sb))
		pr_warn("Remounting filesystem read-only\n");
	sb->s_flags |= SB_RDONLY;
	बहु_पूर्ण(args);
पूर्ण

व्योम
affs_warning(काष्ठा super_block *sb, स्थिर अक्षर *function, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	pr_warn("(device %s): %s(): %pV\n", sb->s_id, function, &vaf);
	बहु_पूर्ण(args);
पूर्ण

bool
affs_nofilenametruncate(स्थिर काष्ठा dentry *dentry)
अणु
	वापस affs_test_opt(AFFS_SB(dentry->d_sb)->s_flags, SF_NO_TRUNCATE);
पूर्ण

/* Check अगर the name is valid क्रम a affs object. */

पूर्णांक
affs_check_name(स्थिर अचिन्हित अक्षर *name, पूर्णांक len, bool notruncate)
अणु
	पूर्णांक	 i;

	अगर (len > AFFSNAMEMAX) अणु
		अगर (notruncate)
			वापस -ENAMETOOLONG;
		len = AFFSNAMEMAX;
	पूर्ण
	क्रम (i = 0; i < len; i++) अणु
		अगर (name[i] < ' ' || name[i] == ':'
		    || (name[i] > 0x7e && name[i] < 0xa0))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* This function copies name to bstr, with at most 30
 * अक्षरacters length. The bstr will be prepended by
 * a length byte.
 * NOTE: The name will must be alपढ़ोy checked by
 *       affs_check_name()!
 */

पूर्णांक
affs_copy_name(अचिन्हित अक्षर *bstr, काष्ठा dentry *dentry)
अणु
	u32 len = min(dentry->d_name.len, AFFSNAMEMAX);

	*bstr++ = len;
	स_नकल(bstr, dentry->d_name.name, len);
	वापस len;
पूर्ण
