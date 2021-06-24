<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2010
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * xattr_id.c
 */

/*
 * This file implements code to map the 32-bit xattr id stored in the inode
 * पूर्णांकo the on disk location of the xattr data.
 */

#समावेश <linux/fs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/slab.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs.h"
#समावेश "xattr.h"

/*
 * Map xattr id using the xattr id look up table
 */
पूर्णांक squashfs_xattr_lookup(काष्ठा super_block *sb, अचिन्हित पूर्णांक index,
		पूर्णांक *count, अचिन्हित पूर्णांक *size, अचिन्हित दीर्घ दीर्घ *xattr)
अणु
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	पूर्णांक block = SQUASHFS_XATTR_BLOCK(index);
	पूर्णांक offset = SQUASHFS_XATTR_BLOCK_OFFSET(index);
	u64 start_block;
	काष्ठा squashfs_xattr_id id;
	पूर्णांक err;

	अगर (index >= msblk->xattr_ids)
		वापस -EINVAL;

	start_block = le64_to_cpu(msblk->xattr_id_table[block]);

	err = squashfs_पढ़ो_metadata(sb, &id, &start_block, &offset,
							माप(id));
	अगर (err < 0)
		वापस err;

	*xattr = le64_to_cpu(id.xattr);
	*size = le32_to_cpu(id.size);
	*count = le32_to_cpu(id.count);
	वापस 0;
पूर्ण


/*
 * Read uncompressed xattr id lookup table indexes from disk पूर्णांकo memory
 */
__le64 *squashfs_पढ़ो_xattr_id_table(काष्ठा super_block *sb, u64 table_start,
		u64 *xattr_table_start, पूर्णांक *xattr_ids)
अणु
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	अचिन्हित पूर्णांक len, indexes;
	काष्ठा squashfs_xattr_id_table *id_table;
	__le64 *table;
	u64 start, end;
	पूर्णांक n;

	id_table = squashfs_पढ़ो_table(sb, table_start, माप(*id_table));
	अगर (IS_ERR(id_table))
		वापस (__le64 *) id_table;

	*xattr_table_start = le64_to_cpu(id_table->xattr_table_start);
	*xattr_ids = le32_to_cpu(id_table->xattr_ids);
	kमुक्त(id_table);

	/* Sanity check values */

	/* there is always at least one xattr id */
	अगर (*xattr_ids == 0)
		वापस ERR_PTR(-EINVAL);

	len = SQUASHFS_XATTR_BLOCK_BYTES(*xattr_ids);
	indexes = SQUASHFS_XATTR_BLOCKS(*xattr_ids);

	/*
	 * The computed size of the index table (len bytes) should exactly
	 * match the table start and end poपूर्णांकs
	 */
	start = table_start + माप(*id_table);
	end = msblk->bytes_used;

	अगर (len != (end - start))
		वापस ERR_PTR(-EINVAL);

	table = squashfs_पढ़ो_table(sb, start, len);
	अगर (IS_ERR(table))
		वापस table;

	/* table[0], table[1], ... table[indexes - 1] store the locations
	 * of the compressed xattr id blocks.  Each entry should be less than
	 * the next (i.e. table[0] < table[1]), and the dअगरference between them
	 * should be SQUASHFS_METADATA_SIZE or less.  table[indexes - 1]
	 * should be less than table_start, and again the dअगरference
	 * shouls be SQUASHFS_METADATA_SIZE or less.
	 *
	 * Finally xattr_table_start should be less than table[0].
	 */
	क्रम (n = 0; n < (indexes - 1); n++) अणु
		start = le64_to_cpu(table[n]);
		end = le64_to_cpu(table[n + 1]);

		अगर (start >= end || (end - start) >
				(SQUASHFS_METADATA_SIZE + SQUASHFS_BLOCK_OFFSET)) अणु
			kमुक्त(table);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	start = le64_to_cpu(table[indexes - 1]);
	अगर (start >= table_start || (table_start - start) >
				(SQUASHFS_METADATA_SIZE + SQUASHFS_BLOCK_OFFSET)) अणु
		kमुक्त(table);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (*xattr_table_start >= le64_to_cpu(table[0])) अणु
		kमुक्त(table);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस table;
पूर्ण
