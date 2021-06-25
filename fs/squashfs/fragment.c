<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * fragment.c
 */

/*
 * This file implements code to handle compressed fragments (tail-end packed
 * datablocks).
 *
 * Regular files contain a fragment index which is mapped to a fragment
 * location on disk and compressed size using a fragment lookup table.
 * Like everything in Squashfs this fragment lookup table is itself stored
 * compressed पूर्णांकo metadata blocks.  A second index table is used to locate
 * these.  This second index table क्रम speed of access (and because it
 * is small) is पढ़ो at mount समय and cached in memory.
 */

#समावेश <linux/fs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/slab.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs.h"

/*
 * Look-up fragment using the fragment index table.  Return the on disk
 * location of the fragment and its compressed size
 */
पूर्णांक squashfs_frag_lookup(काष्ठा super_block *sb, अचिन्हित पूर्णांक fragment,
				u64 *fragment_block)
अणु
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	पूर्णांक block, offset, size;
	काष्ठा squashfs_fragment_entry fragment_entry;
	u64 start_block;

	अगर (fragment >= msblk->fragments)
		वापस -EIO;
	block = SQUASHFS_FRAGMENT_INDEX(fragment);
	offset = SQUASHFS_FRAGMENT_INDEX_OFFSET(fragment);

	start_block = le64_to_cpu(msblk->fragment_index[block]);

	size = squashfs_पढ़ो_metadata(sb, &fragment_entry, &start_block,
					&offset, माप(fragment_entry));
	अगर (size < 0)
		वापस size;

	*fragment_block = le64_to_cpu(fragment_entry.start_block);
	वापस squashfs_block_size(fragment_entry.size);
पूर्ण


/*
 * Read the uncompressed fragment lookup table indexes off disk पूर्णांकo memory
 */
__le64 *squashfs_पढ़ो_fragment_index_table(काष्ठा super_block *sb,
	u64 fragment_table_start, u64 next_table, अचिन्हित पूर्णांक fragments)
अणु
	अचिन्हित पूर्णांक length = SQUASHFS_FRAGMENT_INDEX_BYTES(fragments);
	__le64 *table;

	/*
	 * Sanity check, length bytes should not extend पूर्णांकo the next table -
	 * this check also traps instances where fragment_table_start is
	 * incorrectly larger than the next table start
	 */
	अगर (fragment_table_start + length > next_table)
		वापस ERR_PTR(-EINVAL);

	table = squashfs_पढ़ो_table(sb, fragment_table_start, length);

	/*
	 * table[0] poपूर्णांकs to the first fragment table metadata block, this
	 * should be less than fragment_table_start
	 */
	अगर (!IS_ERR(table) && le64_to_cpu(table[0]) >= fragment_table_start) अणु
		kमुक्त(table);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस table;
पूर्ण
