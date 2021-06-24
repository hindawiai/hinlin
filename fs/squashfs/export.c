<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * export.c
 */

/*
 * This file implements code to make Squashfs fileप्रणालीs exportable (NFS etc.)
 *
 * The export code uses an inode lookup table to map inode numbers passed in
 * filehandles to an inode location on disk.  This table is stored compressed
 * पूर्णांकo metadata blocks.  A second index table is used to locate these.  This
 * second index table क्रम speed of access (and because it is small) is पढ़ो at
 * mount समय and cached in memory.
 *
 * The inode lookup table is used only by the export code, inode disk
 * locations are directly encoded in directories, enabling direct access
 * without an पूर्णांकermediate lookup क्रम all operations except the export ops.
 */

#समावेश <linux/fs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/dcache.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/slab.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs_fs_i.h"
#समावेश "squashfs.h"

/*
 * Look-up inode number (ino) in table, वापसing the inode location.
 */
अटल दीर्घ दीर्घ squashfs_inode_lookup(काष्ठा super_block *sb, पूर्णांक ino_num)
अणु
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	पूर्णांक blk = SQUASHFS_LOOKUP_BLOCK(ino_num - 1);
	पूर्णांक offset = SQUASHFS_LOOKUP_BLOCK_OFFSET(ino_num - 1);
	u64 start;
	__le64 ino;
	पूर्णांक err;

	TRACE("Entered squashfs_inode_lookup, inode_number = %d\n", ino_num);

	अगर (ino_num == 0 || (ino_num - 1) >= msblk->inodes)
		वापस -EINVAL;

	start = le64_to_cpu(msblk->inode_lookup_table[blk]);

	err = squashfs_पढ़ो_metadata(sb, &ino, &start, &offset, माप(ino));
	अगर (err < 0)
		वापस err;

	TRACE("squashfs_inode_lookup, inode = 0x%llx\n",
		(u64) le64_to_cpu(ino));

	वापस le64_to_cpu(ino);
पूर्ण


अटल काष्ठा dentry *squashfs_export_iget(काष्ठा super_block *sb,
	अचिन्हित पूर्णांक ino_num)
अणु
	दीर्घ दीर्घ ino;
	काष्ठा dentry *dentry = ERR_PTR(-ENOENT);

	TRACE("Entered squashfs_export_iget\n");

	ino = squashfs_inode_lookup(sb, ino_num);
	अगर (ino >= 0)
		dentry = d_obtain_alias(squashfs_iget(sb, ino, ino_num));

	वापस dentry;
पूर्ण


अटल काष्ठा dentry *squashfs_fh_to_dentry(काष्ठा super_block *sb,
		काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	अगर ((fh_type != खाताID_INO32_GEN && fh_type != खाताID_INO32_GEN_PARENT)
			|| fh_len < 2)
		वापस शून्य;

	वापस squashfs_export_iget(sb, fid->i32.ino);
पूर्ण


अटल काष्ठा dentry *squashfs_fh_to_parent(काष्ठा super_block *sb,
		काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	अगर (fh_type != खाताID_INO32_GEN_PARENT || fh_len < 4)
		वापस शून्य;

	वापस squashfs_export_iget(sb, fid->i32.parent_ino);
पूर्ण


अटल काष्ठा dentry *squashfs_get_parent(काष्ठा dentry *child)
अणु
	काष्ठा inode *inode = d_inode(child);
	अचिन्हित पूर्णांक parent_ino = squashfs_i(inode)->parent;

	वापस squashfs_export_iget(inode->i_sb, parent_ino);
पूर्ण


/*
 * Read uncompressed inode lookup table indexes off disk पूर्णांकo memory
 */
__le64 *squashfs_पढ़ो_inode_lookup_table(काष्ठा super_block *sb,
		u64 lookup_table_start, u64 next_table, अचिन्हित पूर्णांक inodes)
अणु
	अचिन्हित पूर्णांक length = SQUASHFS_LOOKUP_BLOCK_BYTES(inodes);
	अचिन्हित पूर्णांक indexes = SQUASHFS_LOOKUP_BLOCKS(inodes);
	पूर्णांक n;
	__le64 *table;
	u64 start, end;

	TRACE("In read_inode_lookup_table, length %d\n", length);

	/* Sanity check values */

	/* there should always be at least one inode */
	अगर (inodes == 0)
		वापस ERR_PTR(-EINVAL);

	/*
	 * The computed size of the lookup table (length bytes) should exactly
	 * match the table start and end poपूर्णांकs
	 */
	अगर (length != (next_table - lookup_table_start))
		वापस ERR_PTR(-EINVAL);

	table = squashfs_पढ़ो_table(sb, lookup_table_start, length);
	अगर (IS_ERR(table))
		वापस table;

	/*
	 * table0], table[1], ... table[indexes - 1] store the locations
	 * of the compressed inode lookup blocks.  Each entry should be
	 * less than the next (i.e. table[0] < table[1]), and the dअगरference
	 * between them should be SQUASHFS_METADATA_SIZE or less.
	 * table[indexes - 1] should  be less than lookup_table_start, and
	 * again the dअगरference should be SQUASHFS_METADATA_SIZE or less
	 */
	क्रम (n = 0; n < (indexes - 1); n++) अणु
		start = le64_to_cpu(table[n]);
		end = le64_to_cpu(table[n + 1]);

		अगर (start >= end
		    || (end - start) >
		    (SQUASHFS_METADATA_SIZE + SQUASHFS_BLOCK_OFFSET)) अणु
			kमुक्त(table);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	start = le64_to_cpu(table[indexes - 1]);
	अगर (start >= lookup_table_start ||
	    (lookup_table_start - start) >
	    (SQUASHFS_METADATA_SIZE + SQUASHFS_BLOCK_OFFSET)) अणु
		kमुक्त(table);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस table;
पूर्ण


स्थिर काष्ठा export_operations squashfs_export_ops = अणु
	.fh_to_dentry = squashfs_fh_to_dentry,
	.fh_to_parent = squashfs_fh_to_parent,
	.get_parent = squashfs_get_parent
पूर्ण;
