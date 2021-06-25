<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * id.c
 */

/*
 * This file implements code to handle uids and gids.
 *
 * For space efficiency regular files store uid and gid indexes, which are
 * converted to 32-bit uids/gids using an id look up table.  This table is
 * stored compressed पूर्णांकo metadata blocks.  A second index table is used to
 * locate these.  This second index table क्रम speed of access (and because it
 * is small) is पढ़ो at mount समय and cached in memory.
 */

#समावेश <linux/fs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/slab.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs.h"

/*
 * Map uid/gid index पूर्णांकo real 32-bit uid/gid using the id look up table
 */
पूर्णांक squashfs_get_id(काष्ठा super_block *sb, अचिन्हित पूर्णांक index,
					अचिन्हित पूर्णांक *id)
अणु
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	पूर्णांक block = SQUASHFS_ID_BLOCK(index);
	पूर्णांक offset = SQUASHFS_ID_BLOCK_OFFSET(index);
	u64 start_block;
	__le32 disk_id;
	पूर्णांक err;

	अगर (index >= msblk->ids)
		वापस -EINVAL;

	start_block = le64_to_cpu(msblk->id_table[block]);

	err = squashfs_पढ़ो_metadata(sb, &disk_id, &start_block, &offset,
							माप(disk_id));
	अगर (err < 0)
		वापस err;

	*id = le32_to_cpu(disk_id);
	वापस 0;
पूर्ण


/*
 * Read uncompressed id lookup table indexes from disk पूर्णांकo memory
 */
__le64 *squashfs_पढ़ो_id_index_table(काष्ठा super_block *sb,
		u64 id_table_start, u64 next_table, अचिन्हित लघु no_ids)
अणु
	अचिन्हित पूर्णांक length = SQUASHFS_ID_BLOCK_BYTES(no_ids);
	अचिन्हित पूर्णांक indexes = SQUASHFS_ID_BLOCKS(no_ids);
	पूर्णांक n;
	__le64 *table;
	u64 start, end;

	TRACE("In read_id_index_table, length %d\n", length);

	/* Sanity check values */

	/* there should always be at least one id */
	अगर (no_ids == 0)
		वापस ERR_PTR(-EINVAL);

	/*
	 * The computed size of the index table (length bytes) should exactly
	 * match the table start and end poपूर्णांकs
	 */
	अगर (length != (next_table - id_table_start))
		वापस ERR_PTR(-EINVAL);

	table = squashfs_पढ़ो_table(sb, id_table_start, length);
	अगर (IS_ERR(table))
		वापस table;

	/*
	 * table[0], table[1], ... table[indexes - 1] store the locations
	 * of the compressed id blocks.   Each entry should be less than
	 * the next (i.e. table[0] < table[1]), and the dअगरference between them
	 * should be SQUASHFS_METADATA_SIZE or less.  table[indexes - 1]
	 * should be less than id_table_start, and again the dअगरference
	 * should be SQUASHFS_METADATA_SIZE or less
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
	अगर (start >= id_table_start || (id_table_start - start) >
				(SQUASHFS_METADATA_SIZE + SQUASHFS_BLOCK_OFFSET)) अणु
		kमुक्त(table);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस table;
पूर्ण
