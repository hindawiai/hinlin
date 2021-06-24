<शैली गुरु>
/*
 *  linux/fs/hfs/mdb.c
 *
 * Copyright (C) 1995-1997  Paul H. Hargrove
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 * This file may be distributed under the terms of the GNU General Public License.
 *
 * This file contains functions क्रम पढ़ोing/writing the MDB.
 */

#समावेश <linux/cdrom.h>
#समावेश <linux/genhd.h>
#समावेश <linux/nls.h>
#समावेश <linux/slab.h>

#समावेश "hfs_fs.h"
#समावेश "btree.h"

/*================ File-local data types ================*/

/*
 * The HFS Master Directory Block (MDB).
 *
 * Also known as the Volume Inक्रमmation Block (VIB), this काष्ठाure is
 * the HFS equivalent of a superblock.
 *
 * Reference: _Inside Macपूर्णांकosh: Files_ pages 2-59 through 2-62
 *
 * modअगरied क्रम HFS Extended
 */

अटल पूर्णांक hfs_get_last_session(काष्ठा super_block *sb,
				sector_t *start, sector_t *size)
अणु
	काष्ठा cdrom_device_info *cdi = disk_to_cdi(sb->s_bdev->bd_disk);

	/* शेष values */
	*start = 0;
	*size = i_size_पढ़ो(sb->s_bdev->bd_inode) >> 9;

	अगर (HFS_SB(sb)->session >= 0) अणु
		काष्ठा cdrom_tocentry te;
	
		अगर (!cdi)
			वापस -EINVAL;

		te.cdte_track = HFS_SB(sb)->session;
		te.cdte_क्रमmat = CDROM_LBA;
		अगर (cdrom_पढ़ो_tocentry(cdi, &te) ||
		    (te.cdte_ctrl & CDROM_DATA_TRACK) != 4) अणु
			pr_err("invalid session number or type of track\n");
			वापस -EINVAL;
		पूर्ण

		*start = (sector_t)te.cdte_addr.lba << 2;
	पूर्ण अन्यथा अगर (cdi) अणु
		काष्ठा cdrom_multisession ms_info;

		ms_info.addr_क्रमmat = CDROM_LBA;
		अगर (cdrom_multisession(cdi, &ms_info) == 0 && ms_info.xa_flag)
			*start = (sector_t)ms_info.addr.lba << 2;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * hfs_mdb_get()
 *
 * Build the in-core MDB क्रम a fileप्रणाली, including
 * the B-trees and the volume biपंचांगap.
 */
पूर्णांक hfs_mdb_get(काष्ठा super_block *sb)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा hfs_mdb *mdb, *mdb2;
	अचिन्हित पूर्णांक block;
	अक्षर *ptr;
	पूर्णांक off2, len, size, sect;
	sector_t part_start, part_size;
	loff_t off;
	__be16 attrib;

	/* set the device driver to 512-byte blocks */
	size = sb_min_blocksize(sb, HFS_SECTOR_SIZE);
	अगर (!size)
		वापस -EINVAL;

	अगर (hfs_get_last_session(sb, &part_start, &part_size))
		वापस -EINVAL;
	जबतक (1) अणु
		/* See अगर this is an HFS fileप्रणाली */
		bh = sb_bपढ़ो512(sb, part_start + HFS_MDB_BLK, mdb);
		अगर (!bh)
			जाओ out;

		अगर (mdb->drSigWord == cpu_to_be16(HFS_SUPER_MAGIC))
			अवरोध;
		brअन्यथा(bh);

		/* check क्रम a partition block
		 * (should करो this only क्रम cdrom/loop though)
		 */
		अगर (hfs_part_find(sb, &part_start, &part_size))
			जाओ out;
	पूर्ण

	HFS_SB(sb)->alloc_blksz = size = be32_to_cpu(mdb->drAlBlkSiz);
	अगर (!size || (size & (HFS_SECTOR_SIZE - 1))) अणु
		pr_err("bad allocation block size %d\n", size);
		जाओ out_bh;
	पूर्ण

	size = min(HFS_SB(sb)->alloc_blksz, (u32)PAGE_SIZE);
	/* size must be a multiple of 512 */
	जबतक (size & (size - 1))
		size -= HFS_SECTOR_SIZE;
	sect = be16_to_cpu(mdb->drAlBlSt) + part_start;
	/* align block size to first sector */
	जबतक (sect & ((size - 1) >> HFS_SECTOR_SIZE_BITS))
		size >>= 1;
	/* align block size to weird alloc size */
	जबतक (HFS_SB(sb)->alloc_blksz & (size - 1))
		size >>= 1;
	brअन्यथा(bh);
	अगर (!sb_set_blocksize(sb, size)) अणु
		pr_err("unable to set blocksize to %u\n", size);
		जाओ out;
	पूर्ण

	bh = sb_bपढ़ो512(sb, part_start + HFS_MDB_BLK, mdb);
	अगर (!bh)
		जाओ out;
	अगर (mdb->drSigWord != cpu_to_be16(HFS_SUPER_MAGIC))
		जाओ out_bh;

	HFS_SB(sb)->mdb_bh = bh;
	HFS_SB(sb)->mdb = mdb;

	/* These parameters are पढ़ो from the MDB, and never written */
	HFS_SB(sb)->part_start = part_start;
	HFS_SB(sb)->fs_ablocks = be16_to_cpu(mdb->drNmAlBlks);
	HFS_SB(sb)->fs_भाग = HFS_SB(sb)->alloc_blksz >> sb->s_blocksize_bits;
	HFS_SB(sb)->clumpablks = be32_to_cpu(mdb->drClpSiz) /
				 HFS_SB(sb)->alloc_blksz;
	अगर (!HFS_SB(sb)->clumpablks)
		HFS_SB(sb)->clumpablks = 1;
	HFS_SB(sb)->fs_start = (be16_to_cpu(mdb->drAlBlSt) + part_start) >>
			       (sb->s_blocksize_bits - HFS_SECTOR_SIZE_BITS);

	/* These parameters are पढ़ो from and written to the MDB */
	HFS_SB(sb)->मुक्त_ablocks = be16_to_cpu(mdb->drFreeBks);
	HFS_SB(sb)->next_id = be32_to_cpu(mdb->drNxtCNID);
	HFS_SB(sb)->root_files = be16_to_cpu(mdb->drNmFls);
	HFS_SB(sb)->root_dirs = be16_to_cpu(mdb->drNmRtDirs);
	HFS_SB(sb)->file_count = be32_to_cpu(mdb->drFilCnt);
	HFS_SB(sb)->folder_count = be32_to_cpu(mdb->drDirCnt);

	/* TRY to get the alternate (backup) MDB. */
	sect = part_start + part_size - 2;
	bh = sb_bपढ़ो512(sb, sect, mdb2);
	अगर (bh) अणु
		अगर (mdb2->drSigWord == cpu_to_be16(HFS_SUPER_MAGIC)) अणु
			HFS_SB(sb)->alt_mdb_bh = bh;
			HFS_SB(sb)->alt_mdb = mdb2;
		पूर्ण अन्यथा
			brअन्यथा(bh);
	पूर्ण

	अगर (!HFS_SB(sb)->alt_mdb) अणु
		pr_warn("unable to locate alternate MDB\n");
		pr_warn("continuing without an alternate MDB\n");
	पूर्ण

	HFS_SB(sb)->biपंचांगap = kदो_स्मृति(8192, GFP_KERNEL);
	अगर (!HFS_SB(sb)->biपंचांगap)
		जाओ out;

	/* पढ़ो in the biपंचांगap */
	block = be16_to_cpu(mdb->drVBMSt) + part_start;
	off = (loff_t)block << HFS_SECTOR_SIZE_BITS;
	size = (HFS_SB(sb)->fs_ablocks + 8) / 8;
	ptr = (u8 *)HFS_SB(sb)->biपंचांगap;
	जबतक (size) अणु
		bh = sb_bपढ़ो(sb, off >> sb->s_blocksize_bits);
		अगर (!bh) अणु
			pr_err("unable to read volume bitmap\n");
			जाओ out;
		पूर्ण
		off2 = off & (sb->s_blocksize - 1);
		len = min((पूर्णांक)sb->s_blocksize - off2, size);
		स_नकल(ptr, bh->b_data + off2, len);
		brअन्यथा(bh);
		ptr += len;
		off += len;
		size -= len;
	पूर्ण

	HFS_SB(sb)->ext_tree = hfs_btree_खोलो(sb, HFS_EXT_CNID, hfs_ext_keycmp);
	अगर (!HFS_SB(sb)->ext_tree) अणु
		pr_err("unable to open extent tree\n");
		जाओ out;
	पूर्ण
	HFS_SB(sb)->cat_tree = hfs_btree_खोलो(sb, HFS_CAT_CNID, hfs_cat_keycmp);
	अगर (!HFS_SB(sb)->cat_tree) अणु
		pr_err("unable to open catalog tree\n");
		जाओ out;
	पूर्ण

	attrib = mdb->drAtrb;
	अगर (!(attrib & cpu_to_be16(HFS_SB_ATTRIB_UNMNT))) अणु
		pr_warn("filesystem was not cleanly unmounted, running fsck.hfs is recommended.  mounting read-only.\n");
		sb->s_flags |= SB_RDONLY;
	पूर्ण
	अगर ((attrib & cpu_to_be16(HFS_SB_ATTRIB_SLOCK))) अणु
		pr_warn("filesystem is marked locked, mounting read-only.\n");
		sb->s_flags |= SB_RDONLY;
	पूर्ण
	अगर (!sb_rकरोnly(sb)) अणु
		/* Mark the volume uncleanly unmounted in हाल we crash */
		attrib &= cpu_to_be16(~HFS_SB_ATTRIB_UNMNT);
		attrib |= cpu_to_be16(HFS_SB_ATTRIB_INCNSTNT);
		mdb->drAtrb = attrib;
		be32_add_cpu(&mdb->drWrCnt, 1);
		mdb->drLsMod = hfs_mसमय();

		mark_buffer_dirty(HFS_SB(sb)->mdb_bh);
		sync_dirty_buffer(HFS_SB(sb)->mdb_bh);
	पूर्ण

	वापस 0;

out_bh:
	brअन्यथा(bh);
out:
	hfs_mdb_put(sb);
	वापस -EIO;
पूर्ण

/*
 * hfs_mdb_commit()
 *
 * Description:
 *   This updates the MDB on disk.
 *   It करोes not check, अगर the superblock has been modअगरied, or
 *   अगर the fileप्रणाली has been mounted पढ़ो-only. It is मुख्यly
 *   called by hfs_sync_fs() and flush_mdb().
 * Input Variable(s):
 *   काष्ठा hfs_mdb *mdb: Poपूर्णांकer to the hfs MDB
 *   पूर्णांक backup;
 * Output Variable(s):
 *   NONE
 * Returns:
 *   व्योम
 * Preconditions:
 *   'mdb' poपूर्णांकs to a "valid" (काष्ठा hfs_mdb).
 * Postconditions:
 *   The HFS MDB and on disk will be updated, by copying the possibly
 *   modअगरied fields from the in memory MDB (in native byte order) to
 *   the disk block buffer.
 *   If 'backup' is non-zero then the alternate MDB is also written
 *   and the function करोesn't वापस until it is actually on disk.
 */
व्योम hfs_mdb_commit(काष्ठा super_block *sb)
अणु
	काष्ठा hfs_mdb *mdb = HFS_SB(sb)->mdb;

	अगर (sb_rकरोnly(sb))
		वापस;

	lock_buffer(HFS_SB(sb)->mdb_bh);
	अगर (test_and_clear_bit(HFS_FLG_MDB_सूचीTY, &HFS_SB(sb)->flags)) अणु
		/* These parameters may have been modअगरied, so ग_लिखो them back */
		mdb->drLsMod = hfs_mसमय();
		mdb->drFreeBks = cpu_to_be16(HFS_SB(sb)->मुक्त_ablocks);
		mdb->drNxtCNID = cpu_to_be32(HFS_SB(sb)->next_id);
		mdb->drNmFls = cpu_to_be16(HFS_SB(sb)->root_files);
		mdb->drNmRtDirs = cpu_to_be16(HFS_SB(sb)->root_dirs);
		mdb->drFilCnt = cpu_to_be32(HFS_SB(sb)->file_count);
		mdb->drDirCnt = cpu_to_be32(HFS_SB(sb)->folder_count);

		/* ग_लिखो MDB to disk */
		mark_buffer_dirty(HFS_SB(sb)->mdb_bh);
	पूर्ण

	/* ग_लिखो the backup MDB, not वापसing until it is written.
	 * we only करो this when either the catalog or extents overflow
	 * files grow. */
	अगर (test_and_clear_bit(HFS_FLG_ALT_MDB_सूचीTY, &HFS_SB(sb)->flags) &&
	    HFS_SB(sb)->alt_mdb) अणु
		hfs_inode_ग_लिखो_विभाजन(HFS_SB(sb)->ext_tree->inode, mdb->drXTExtRec,
				     &mdb->drXTFlSize, शून्य);
		hfs_inode_ग_लिखो_विभाजन(HFS_SB(sb)->cat_tree->inode, mdb->drCTExtRec,
				     &mdb->drCTFlSize, शून्य);

		lock_buffer(HFS_SB(sb)->alt_mdb_bh);
		स_नकल(HFS_SB(sb)->alt_mdb, HFS_SB(sb)->mdb, HFS_SECTOR_SIZE);
		HFS_SB(sb)->alt_mdb->drAtrb |= cpu_to_be16(HFS_SB_ATTRIB_UNMNT);
		HFS_SB(sb)->alt_mdb->drAtrb &= cpu_to_be16(~HFS_SB_ATTRIB_INCNSTNT);
		unlock_buffer(HFS_SB(sb)->alt_mdb_bh);

		mark_buffer_dirty(HFS_SB(sb)->alt_mdb_bh);
		sync_dirty_buffer(HFS_SB(sb)->alt_mdb_bh);
	पूर्ण

	अगर (test_and_clear_bit(HFS_FLG_BITMAP_सूचीTY, &HFS_SB(sb)->flags)) अणु
		काष्ठा buffer_head *bh;
		sector_t block;
		अक्षर *ptr;
		पूर्णांक off, size, len;

		block = be16_to_cpu(HFS_SB(sb)->mdb->drVBMSt) + HFS_SB(sb)->part_start;
		off = (block << HFS_SECTOR_SIZE_BITS) & (sb->s_blocksize - 1);
		block >>= sb->s_blocksize_bits - HFS_SECTOR_SIZE_BITS;
		size = (HFS_SB(sb)->fs_ablocks + 7) / 8;
		ptr = (u8 *)HFS_SB(sb)->biपंचांगap;
		जबतक (size) अणु
			bh = sb_bपढ़ो(sb, block);
			अगर (!bh) अणु
				pr_err("unable to read volume bitmap\n");
				अवरोध;
			पूर्ण
			len = min((पूर्णांक)sb->s_blocksize - off, size);

			lock_buffer(bh);
			स_नकल(bh->b_data + off, ptr, len);
			unlock_buffer(bh);

			mark_buffer_dirty(bh);
			brअन्यथा(bh);
			block++;
			off = 0;
			ptr += len;
			size -= len;
		पूर्ण
	पूर्ण
	unlock_buffer(HFS_SB(sb)->mdb_bh);
पूर्ण

व्योम hfs_mdb_बंद(काष्ठा super_block *sb)
अणु
	/* update volume attributes */
	अगर (sb_rकरोnly(sb))
		वापस;
	HFS_SB(sb)->mdb->drAtrb |= cpu_to_be16(HFS_SB_ATTRIB_UNMNT);
	HFS_SB(sb)->mdb->drAtrb &= cpu_to_be16(~HFS_SB_ATTRIB_INCNSTNT);
	mark_buffer_dirty(HFS_SB(sb)->mdb_bh);
पूर्ण

/*
 * hfs_mdb_put()
 *
 * Release the resources associated with the in-core MDB.  */
व्योम hfs_mdb_put(काष्ठा super_block *sb)
अणु
	अगर (!HFS_SB(sb))
		वापस;
	/* मुक्त the B-trees */
	hfs_btree_बंद(HFS_SB(sb)->ext_tree);
	hfs_btree_बंद(HFS_SB(sb)->cat_tree);

	/* मुक्त the buffers holding the primary and alternate MDBs */
	brअन्यथा(HFS_SB(sb)->mdb_bh);
	brअन्यथा(HFS_SB(sb)->alt_mdb_bh);

	unload_nls(HFS_SB(sb)->nls_io);
	unload_nls(HFS_SB(sb)->nls_disk);

	kमुक्त(HFS_SB(sb)->biपंचांगap);
	kमुक्त(HFS_SB(sb));
	sb->s_fs_info = शून्य;
पूर्ण
