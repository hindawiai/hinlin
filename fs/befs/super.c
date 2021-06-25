<शैली गुरु>
/*
 * super.c
 *
 * Copyright (C) 2001-2002 Will Dyson <will_dyson@pobox.com>
 *
 * Licensed under the GNU GPL. See the file COPYING क्रम details.
 *
 */

#समावेश <linux/fs.h>
#समावेश <यंत्र/page.h> /* क्रम PAGE_SIZE */

#समावेश "befs.h"
#समावेश "super.h"

/*
 * befs_load_sb -- Read from disk and properly byteswap all the fields
 * of the befs superblock
 */
पूर्णांक
befs_load_sb(काष्ठा super_block *sb, befs_super_block *disk_sb)
अणु
	काष्ठा befs_sb_info *befs_sb = BEFS_SB(sb);

	/* Check the byte order of the fileप्रणाली */
	अगर (disk_sb->fs_byte_order == BEFS_BYTEORDER_NATIVE_LE)
		befs_sb->byte_order = BEFS_BYTESEX_LE;
	अन्यथा अगर (disk_sb->fs_byte_order == BEFS_BYTEORDER_NATIVE_BE)
		befs_sb->byte_order = BEFS_BYTESEX_BE;

	befs_sb->magic1 = fs32_to_cpu(sb, disk_sb->magic1);
	befs_sb->magic2 = fs32_to_cpu(sb, disk_sb->magic2);
	befs_sb->magic3 = fs32_to_cpu(sb, disk_sb->magic3);
	befs_sb->block_size = fs32_to_cpu(sb, disk_sb->block_size);
	befs_sb->block_shअगरt = fs32_to_cpu(sb, disk_sb->block_shअगरt);
	befs_sb->num_blocks = fs64_to_cpu(sb, disk_sb->num_blocks);
	befs_sb->used_blocks = fs64_to_cpu(sb, disk_sb->used_blocks);
	befs_sb->inode_size = fs32_to_cpu(sb, disk_sb->inode_size);

	befs_sb->blocks_per_ag = fs32_to_cpu(sb, disk_sb->blocks_per_ag);
	befs_sb->ag_shअगरt = fs32_to_cpu(sb, disk_sb->ag_shअगरt);
	befs_sb->num_ags = fs32_to_cpu(sb, disk_sb->num_ags);

	befs_sb->flags = fs32_to_cpu(sb, disk_sb->flags);

	befs_sb->log_blocks = fsrun_to_cpu(sb, disk_sb->log_blocks);
	befs_sb->log_start = fs64_to_cpu(sb, disk_sb->log_start);
	befs_sb->log_end = fs64_to_cpu(sb, disk_sb->log_end);

	befs_sb->root_dir = fsrun_to_cpu(sb, disk_sb->root_dir);
	befs_sb->indices = fsrun_to_cpu(sb, disk_sb->indices);
	befs_sb->nls = शून्य;

	वापस BEFS_OK;
पूर्ण

पूर्णांक
befs_check_sb(काष्ठा super_block *sb)
अणु
	काष्ठा befs_sb_info *befs_sb = BEFS_SB(sb);

	/* Check magic headers of super block */
	अगर ((befs_sb->magic1 != BEFS_SUPER_MAGIC1)
	    || (befs_sb->magic2 != BEFS_SUPER_MAGIC2)
	    || (befs_sb->magic3 != BEFS_SUPER_MAGIC3)) अणु
		befs_error(sb, "invalid magic header");
		वापस BEFS_ERR;
	पूर्ण

	/*
	 * Check blocksize of BEFS.
	 *
	 * Blocksize of BEFS is 1024, 2048, 4096 or 8192.
	 */

	अगर ((befs_sb->block_size != 1024)
	    && (befs_sb->block_size != 2048)
	    && (befs_sb->block_size != 4096)
	    && (befs_sb->block_size != 8192)) अणु
		befs_error(sb, "invalid blocksize: %u", befs_sb->block_size);
		वापस BEFS_ERR;
	पूर्ण

	अगर (befs_sb->block_size > PAGE_SIZE) अणु
		befs_error(sb, "blocksize(%u) cannot be larger "
			   "than system pagesize(%lu)", befs_sb->block_size,
			   PAGE_SIZE);
		वापस BEFS_ERR;
	पूर्ण

	/*
	 * block_shअगरt and block_size encode the same inक्रमmation
	 * in dअगरferent ways as a consistency check.
	 */

	अगर ((1 << befs_sb->block_shअगरt) != befs_sb->block_size) अणु
		befs_error(sb, "block_shift disagrees with block_size. "
			   "Corruption likely.");
		वापस BEFS_ERR;
	पूर्ण


	/* ag_shअगरt also encodes the same inक्रमmation as blocks_per_ag in a
	 * dअगरferent way, non-fatal consistency check
	 */
	अगर ((1 << befs_sb->ag_shअगरt) != befs_sb->blocks_per_ag)
		befs_error(sb, "ag_shift disagrees with blocks_per_ag.");

	अगर (befs_sb->log_start != befs_sb->log_end ||
	    befs_sb->flags == BEFS_सूचीTY) अणु
		befs_error(sb, "Filesystem not clean! There are blocks in the "
			   "journal. You must boot into BeOS and mount this "
			   "volume to make it clean.");
		वापस BEFS_ERR;
	पूर्ण

	वापस BEFS_OK;
पूर्ण
