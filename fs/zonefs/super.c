<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Simple file प्रणाली क्रम zoned block devices exposing zones as files.
 *
 * Copyright (C) 2019 Western Digital Corporation or its affiliates.
 */
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/magic.h>
#समावेश <linux/iomap.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/statfs.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/parser.h>
#समावेश <linux/uपन.स>
#समावेश <linux/mman.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/crc32.h>
#समावेश <linux/task_io_accounting_ops.h>

#समावेश "zonefs.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

अटल अंतरभूत पूर्णांक zonefs_zone_mgmt(काष्ठा inode *inode,
				   क्रमागत req_opf op)
अणु
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	पूर्णांक ret;

	lockdep_निश्चित_held(&zi->i_truncate_mutex);

	trace_zonefs_zone_mgmt(inode, op);
	ret = blkdev_zone_mgmt(inode->i_sb->s_bdev, op, zi->i_zsector,
			       zi->i_zone_size >> SECTOR_SHIFT, GFP_NOFS);
	अगर (ret) अणु
		zonefs_err(inode->i_sb,
			   "Zone management operation %s at %llu failed %d\n",
			   blk_op_str(op), zi->i_zsector, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम zonefs_i_size_ग_लिखो(काष्ठा inode *inode, loff_t isize)
अणु
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);

	i_size_ग_लिखो(inode, isize);
	/*
	 * A full zone is no दीर्घer खोलो/active and करोes not need
	 * explicit closing.
	 */
	अगर (isize >= zi->i_max_size)
		zi->i_flags &= ~ZONEFS_ZONE_OPEN;
पूर्ण

अटल पूर्णांक zonefs_iomap_begin(काष्ठा inode *inode, loff_t offset, loff_t length,
			      अचिन्हित पूर्णांक flags, काष्ठा iomap *iomap,
			      काष्ठा iomap *srcmap)
अणु
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	loff_t isize;

	/* All I/Os should always be within the file maximum size */
	अगर (WARN_ON_ONCE(offset + length > zi->i_max_size))
		वापस -EIO;

	/*
	 * Sequential zones can only accept direct ग_लिखोs. This is alपढ़ोy
	 * checked when ग_लिखोs are issued, so warn अगर we see a page ग_लिखोback
	 * operation.
	 */
	अगर (WARN_ON_ONCE(zi->i_ztype == ZONEFS_ZTYPE_SEQ &&
			 (flags & IOMAP_WRITE) && !(flags & IOMAP_सूचीECT)))
		वापस -EIO;

	/*
	 * For conventional zones, all blocks are always mapped. For sequential
	 * zones, all blocks after always mapped below the inode size (zone
	 * ग_लिखो poपूर्णांकer) and unग_लिखोn beyond.
	 */
	mutex_lock(&zi->i_truncate_mutex);
	isize = i_size_पढ़ो(inode);
	अगर (offset >= isize)
		iomap->type = IOMAP_UNWRITTEN;
	अन्यथा
		iomap->type = IOMAP_MAPPED;
	अगर (flags & IOMAP_WRITE)
		length = zi->i_max_size - offset;
	अन्यथा
		length = min(length, isize - offset);
	mutex_unlock(&zi->i_truncate_mutex);

	iomap->offset = ALIGN_DOWN(offset, sb->s_blocksize);
	iomap->length = ALIGN(offset + length, sb->s_blocksize) - iomap->offset;
	iomap->bdev = inode->i_sb->s_bdev;
	iomap->addr = (zi->i_zsector << SECTOR_SHIFT) + iomap->offset;

	trace_zonefs_iomap_begin(inode, iomap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iomap_ops zonefs_iomap_ops = अणु
	.iomap_begin	= zonefs_iomap_begin,
पूर्ण;

अटल पूर्णांक zonefs_पढ़ोpage(काष्ठा file *unused, काष्ठा page *page)
अणु
	वापस iomap_पढ़ोpage(page, &zonefs_iomap_ops);
पूर्ण

अटल व्योम zonefs_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	iomap_पढ़ोahead(rac, &zonefs_iomap_ops);
पूर्ण

/*
 * Map blocks क्रम page ग_लिखोback. This is used only on conventional zone files,
 * which implies that the page range can only be within the fixed inode size.
 */
अटल पूर्णांक zonefs_map_blocks(काष्ठा iomap_ग_लिखोpage_ctx *wpc,
			     काष्ठा inode *inode, loff_t offset)
अणु
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);

	अगर (WARN_ON_ONCE(zi->i_ztype != ZONEFS_ZTYPE_CNV))
		वापस -EIO;
	अगर (WARN_ON_ONCE(offset >= i_size_पढ़ो(inode)))
		वापस -EIO;

	/* If the mapping is alपढ़ोy OK, nothing needs to be करोne */
	अगर (offset >= wpc->iomap.offset &&
	    offset < wpc->iomap.offset + wpc->iomap.length)
		वापस 0;

	वापस zonefs_iomap_begin(inode, offset, zi->i_max_size - offset,
				  IOMAP_WRITE, &wpc->iomap, शून्य);
पूर्ण

अटल स्थिर काष्ठा iomap_ग_लिखोback_ops zonefs_ग_लिखोback_ops = अणु
	.map_blocks		= zonefs_map_blocks,
पूर्ण;

अटल पूर्णांक zonefs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा iomap_ग_लिखोpage_ctx wpc = अणु पूर्ण;

	वापस iomap_ग_लिखोpage(page, wbc, &wpc, &zonefs_ग_लिखोback_ops);
पूर्ण

अटल पूर्णांक zonefs_ग_लिखोpages(काष्ठा address_space *mapping,
			     काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा iomap_ग_लिखोpage_ctx wpc = अणु पूर्ण;

	वापस iomap_ग_लिखोpages(mapping, wbc, &wpc, &zonefs_ग_लिखोback_ops);
पूर्ण

अटल पूर्णांक zonefs_swap_activate(काष्ठा swap_info_काष्ठा *sis,
				काष्ठा file *swap_file, sector_t *span)
अणु
	काष्ठा inode *inode = file_inode(swap_file);
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);

	अगर (zi->i_ztype != ZONEFS_ZTYPE_CNV) अणु
		zonefs_err(inode->i_sb,
			   "swap file: not a conventional zone file\n");
		वापस -EINVAL;
	पूर्ण

	वापस iomap_swapfile_activate(sis, swap_file, span, &zonefs_iomap_ops);
पूर्ण

अटल स्थिर काष्ठा address_space_operations zonefs_file_aops = अणु
	.पढ़ोpage		= zonefs_पढ़ोpage,
	.पढ़ोahead		= zonefs_पढ़ोahead,
	.ग_लिखोpage		= zonefs_ग_लिखोpage,
	.ग_लिखोpages		= zonefs_ग_लिखोpages,
	.set_page_dirty		= iomap_set_page_dirty,
	.releasepage		= iomap_releasepage,
	.invalidatepage		= iomap_invalidatepage,
	.migratepage		= iomap_migrate_page,
	.is_partially_uptodate	= iomap_is_partially_uptodate,
	.error_हटाओ_page	= generic_error_हटाओ_page,
	.direct_IO		= noop_direct_IO,
	.swap_activate		= zonefs_swap_activate,
पूर्ण;

अटल व्योम zonefs_update_stats(काष्ठा inode *inode, loff_t new_isize)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा zonefs_sb_info *sbi = ZONEFS_SB(sb);
	loff_t old_isize = i_size_पढ़ो(inode);
	loff_t nr_blocks;

	अगर (new_isize == old_isize)
		वापस;

	spin_lock(&sbi->s_lock);

	/*
	 * This may be called क्रम an update after an IO error.
	 * So beware of the values seen.
	 */
	अगर (new_isize < old_isize) अणु
		nr_blocks = (old_isize - new_isize) >> sb->s_blocksize_bits;
		अगर (sbi->s_used_blocks > nr_blocks)
			sbi->s_used_blocks -= nr_blocks;
		अन्यथा
			sbi->s_used_blocks = 0;
	पूर्ण अन्यथा अणु
		sbi->s_used_blocks +=
			(new_isize - old_isize) >> sb->s_blocksize_bits;
		अगर (sbi->s_used_blocks > sbi->s_blocks)
			sbi->s_used_blocks = sbi->s_blocks;
	पूर्ण

	spin_unlock(&sbi->s_lock);
पूर्ण

/*
 * Check a zone condition and adjust its file inode access permissions क्रम
 * offline and पढ़ोonly zones. Return the inode size corresponding to the
 * amount of पढ़ोable data in the zone.
 */
अटल loff_t zonefs_check_zone_condition(काष्ठा inode *inode,
					  काष्ठा blk_zone *zone, bool warn,
					  bool mount)
अणु
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);

	चयन (zone->cond) अणु
	हाल BLK_ZONE_COND_OFFLINE:
		/*
		 * Dead zone: make the inode immutable, disable all accesses
		 * and set the file size to 0 (zone wp set to zone start).
		 */
		अगर (warn)
			zonefs_warn(inode->i_sb, "inode %lu: offline zone\n",
				    inode->i_ino);
		inode->i_flags |= S_IMMUTABLE;
		inode->i_mode &= ~0777;
		zone->wp = zone->start;
		वापस 0;
	हाल BLK_ZONE_COND_READONLY:
		/*
		 * The ग_लिखो poपूर्णांकer of पढ़ो-only zones is invalid. If such a
		 * zone is found during mount, the file size cannot be retrieved
		 * so we treat the zone as offline (mount == true हाल).
		 * Otherwise, keep the file size as it was when last updated
		 * so that the user can recover data. In both हालs, ग_लिखोs are
		 * always disabled क्रम the zone.
		 */
		अगर (warn)
			zonefs_warn(inode->i_sb, "inode %lu: read-only zone\n",
				    inode->i_ino);
		inode->i_flags |= S_IMMUTABLE;
		अगर (mount) अणु
			zone->cond = BLK_ZONE_COND_OFFLINE;
			inode->i_mode &= ~0777;
			zone->wp = zone->start;
			वापस 0;
		पूर्ण
		inode->i_mode &= ~0222;
		वापस i_size_पढ़ो(inode);
	हाल BLK_ZONE_COND_FULL:
		/* The ग_लिखो poपूर्णांकer of full zones is invalid. */
		वापस zi->i_max_size;
	शेष:
		अगर (zi->i_ztype == ZONEFS_ZTYPE_CNV)
			वापस zi->i_max_size;
		वापस (zone->wp - zone->start) << SECTOR_SHIFT;
	पूर्ण
पूर्ण

काष्ठा zonefs_ioerr_data अणु
	काष्ठा inode	*inode;
	bool		ग_लिखो;
पूर्ण;

अटल पूर्णांक zonefs_io_error_cb(काष्ठा blk_zone *zone, अचिन्हित पूर्णांक idx,
			      व्योम *data)
अणु
	काष्ठा zonefs_ioerr_data *err = data;
	काष्ठा inode *inode = err->inode;
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा zonefs_sb_info *sbi = ZONEFS_SB(sb);
	loff_t isize, data_size;

	/*
	 * Check the zone condition: अगर the zone is not "bad" (offline or
	 * पढ़ो-only), पढ़ो errors are simply संकेतed to the IO issuer as दीर्घ
	 * as there is no inconsistency between the inode size and the amount of
	 * data ग_लिखोn in the zone (data_size).
	 */
	data_size = zonefs_check_zone_condition(inode, zone, true, false);
	isize = i_size_पढ़ो(inode);
	अगर (zone->cond != BLK_ZONE_COND_OFFLINE &&
	    zone->cond != BLK_ZONE_COND_READONLY &&
	    !err->ग_लिखो && isize == data_size)
		वापस 0;

	/*
	 * At this poपूर्णांक, we detected either a bad zone or an inconsistency
	 * between the inode size and the amount of data written in the zone.
	 * For the latter हाल, the cause may be a ग_लिखो IO error or an बाह्यal
	 * action on the device. Two error patterns exist:
	 * 1) The inode size is lower than the amount of data in the zone:
	 *    a ग_लिखो operation partially failed and data was ग_लिखोn at the end
	 *    of the file. This can happen in the हाल of a large direct IO
	 *    needing several BIOs and/or ग_लिखो requests to be processed.
	 * 2) The inode size is larger than the amount of data in the zone:
	 *    this can happen with a deferred ग_लिखो error with the use of the
	 *    device side ग_लिखो cache after getting successful ग_लिखो IO
	 *    completions. Other possibilities are (a) an बाह्यal corruption,
	 *    e.g. an application reset the zone directly, or (b) the device
	 *    has a serious problem (e.g. firmware bug).
	 *
	 * In all हालs, warn about inode size inconsistency and handle the
	 * IO error according to the zone condition and to the mount options.
	 */
	अगर (zi->i_ztype == ZONEFS_ZTYPE_SEQ && isize != data_size)
		zonefs_warn(sb, "inode %lu: invalid size %lld (should be %lld)\n",
			    inode->i_ino, isize, data_size);

	/*
	 * First handle bad zones संकेतed by hardware. The mount options
	 * errors=zone-ro and errors=zone-offline result in changing the
	 * zone condition to पढ़ो-only and offline respectively, as अगर the
	 * condition was संकेतed by the hardware.
	 */
	अगर (zone->cond == BLK_ZONE_COND_OFFLINE ||
	    sbi->s_mount_opts & ZONEFS_MNTOPT_ERRORS_ZOL) अणु
		zonefs_warn(sb, "inode %lu: read/write access disabled\n",
			    inode->i_ino);
		अगर (zone->cond != BLK_ZONE_COND_OFFLINE) अणु
			zone->cond = BLK_ZONE_COND_OFFLINE;
			data_size = zonefs_check_zone_condition(inode, zone,
								false, false);
		पूर्ण
	पूर्ण अन्यथा अगर (zone->cond == BLK_ZONE_COND_READONLY ||
		   sbi->s_mount_opts & ZONEFS_MNTOPT_ERRORS_ZRO) अणु
		zonefs_warn(sb, "inode %lu: write access disabled\n",
			    inode->i_ino);
		अगर (zone->cond != BLK_ZONE_COND_READONLY) अणु
			zone->cond = BLK_ZONE_COND_READONLY;
			data_size = zonefs_check_zone_condition(inode, zone,
								false, false);
		पूर्ण
	पूर्ण

	/*
	 * If the fileप्रणाली is mounted with the explicit-खोलो mount option, we
	 * need to clear the ZONEFS_ZONE_OPEN flag अगर the zone transitioned to
	 * the पढ़ो-only or offline condition, to aव्योम attempting an explicit
	 * बंद of the zone when the inode file is बंदd.
	 */
	अगर ((sbi->s_mount_opts & ZONEFS_MNTOPT_EXPLICIT_OPEN) &&
	    (zone->cond == BLK_ZONE_COND_OFFLINE ||
	     zone->cond == BLK_ZONE_COND_READONLY))
		zi->i_flags &= ~ZONEFS_ZONE_OPEN;

	/*
	 * If error=remount-ro was specअगरied, any error result in remounting
	 * the volume as पढ़ो-only.
	 */
	अगर ((sbi->s_mount_opts & ZONEFS_MNTOPT_ERRORS_RO) && !sb_rकरोnly(sb)) अणु
		zonefs_warn(sb, "remounting filesystem read-only\n");
		sb->s_flags |= SB_RDONLY;
	पूर्ण

	/*
	 * Update block usage stats and the inode size  to prevent access to
	 * invalid data.
	 */
	zonefs_update_stats(inode, data_size);
	zonefs_i_size_ग_लिखो(inode, data_size);
	zi->i_wpoffset = data_size;

	वापस 0;
पूर्ण

/*
 * When an file IO error occurs, check the file zone to see अगर there is a change
 * in the zone condition (e.g. offline or पढ़ो-only). For a failed ग_लिखो to a
 * sequential zone, the zone ग_लिखो poपूर्णांकer position must also be checked to
 * eventually correct the file size and zonefs inode ग_लिखो poपूर्णांकer offset
 * (which can be out of sync with the drive due to partial ग_लिखो failures).
 */
अटल व्योम __zonefs_io_error(काष्ठा inode *inode, bool ग_लिखो)
अणु
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा zonefs_sb_info *sbi = ZONEFS_SB(sb);
	अचिन्हित पूर्णांक noio_flag;
	अचिन्हित पूर्णांक nr_zones =
		zi->i_zone_size >> (sbi->s_zone_sectors_shअगरt + SECTOR_SHIFT);
	काष्ठा zonefs_ioerr_data err = अणु
		.inode = inode,
		.ग_लिखो = ग_लिखो,
	पूर्ण;
	पूर्णांक ret;

	/*
	 * Memory allocations in blkdev_report_zones() can trigger a memory
	 * reclaim which may in turn cause a recursion पूर्णांकo zonefs as well as
	 * काष्ठा request allocations क्रम the same device. The क्रमmer हाल may
	 * end up in a deadlock on the inode truncate mutex, जबतक the latter
	 * may prevent IO क्रमward progress. Executing the report zones under
	 * the GFP_NOIO context aव्योमs both problems.
	 */
	noio_flag = meदो_स्मृति_noio_save();
	ret = blkdev_report_zones(sb->s_bdev, zi->i_zsector, nr_zones,
				  zonefs_io_error_cb, &err);
	अगर (ret != nr_zones)
		zonefs_err(sb, "Get inode %lu zone information failed %d\n",
			   inode->i_ino, ret);
	meदो_स्मृति_noio_restore(noio_flag);
पूर्ण

अटल व्योम zonefs_io_error(काष्ठा inode *inode, bool ग_लिखो)
अणु
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);

	mutex_lock(&zi->i_truncate_mutex);
	__zonefs_io_error(inode, ग_लिखो);
	mutex_unlock(&zi->i_truncate_mutex);
पूर्ण

अटल पूर्णांक zonefs_file_truncate(काष्ठा inode *inode, loff_t isize)
अणु
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	loff_t old_isize;
	क्रमागत req_opf op;
	पूर्णांक ret = 0;

	/*
	 * Only sequential zone files can be truncated and truncation is allowed
	 * only करोwn to a 0 size, which is equivalent to a zone reset, and to
	 * the maximum file size, which is equivalent to a zone finish.
	 */
	अगर (zi->i_ztype != ZONEFS_ZTYPE_SEQ)
		वापस -EPERM;

	अगर (!isize)
		op = REQ_OP_ZONE_RESET;
	अन्यथा अगर (isize == zi->i_max_size)
		op = REQ_OP_ZONE_FINISH;
	अन्यथा
		वापस -EPERM;

	inode_dio_रुको(inode);

	/* Serialize against page faults */
	करोwn_ग_लिखो(&zi->i_mmap_sem);

	/* Serialize against zonefs_iomap_begin() */
	mutex_lock(&zi->i_truncate_mutex);

	old_isize = i_size_पढ़ो(inode);
	अगर (isize == old_isize)
		जाओ unlock;

	ret = zonefs_zone_mgmt(inode, op);
	अगर (ret)
		जाओ unlock;

	/*
	 * If the mount option ZONEFS_MNTOPT_EXPLICIT_OPEN is set,
	 * take care of खोलो zones.
	 */
	अगर (zi->i_flags & ZONEFS_ZONE_OPEN) अणु
		/*
		 * Truncating a zone to EMPTY or FULL is the equivalent of
		 * closing the zone. For a truncation to 0, we need to
		 * re-खोलो the zone to ensure new ग_लिखोs can be processed.
		 * For a truncation to the maximum file size, the zone is
		 * बंदd and ग_लिखोs cannot be accepted anymore, so clear
		 * the खोलो flag.
		 */
		अगर (!isize)
			ret = zonefs_zone_mgmt(inode, REQ_OP_ZONE_OPEN);
		अन्यथा
			zi->i_flags &= ~ZONEFS_ZONE_OPEN;
	पूर्ण

	zonefs_update_stats(inode, isize);
	truncate_setsize(inode, isize);
	zi->i_wpoffset = isize;

unlock:
	mutex_unlock(&zi->i_truncate_mutex);
	up_ग_लिखो(&zi->i_mmap_sem);

	वापस ret;
पूर्ण

अटल पूर्णांक zonefs_inode_setattr(काष्ठा user_namespace *mnt_userns,
				काष्ठा dentry *dentry, काष्ठा iattr *iattr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक ret;

	अगर (unlikely(IS_IMMUTABLE(inode)))
		वापस -EPERM;

	ret = setattr_prepare(&init_user_ns, dentry, iattr);
	अगर (ret)
		वापस ret;

	/*
	 * Since files and directories cannot be created nor deleted, करो not
	 * allow setting any ग_लिखो attributes on the sub-directories grouping
	 * files by zone type.
	 */
	अगर ((iattr->ia_valid & ATTR_MODE) && S_ISसूची(inode->i_mode) &&
	    (iattr->ia_mode & 0222))
		वापस -EPERM;

	अगर (((iattr->ia_valid & ATTR_UID) &&
	     !uid_eq(iattr->ia_uid, inode->i_uid)) ||
	    ((iattr->ia_valid & ATTR_GID) &&
	     !gid_eq(iattr->ia_gid, inode->i_gid))) अणु
		ret = dquot_transfer(inode, iattr);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (iattr->ia_valid & ATTR_SIZE) अणु
		ret = zonefs_file_truncate(inode, iattr->ia_size);
		अगर (ret)
			वापस ret;
	पूर्ण

	setattr_copy(&init_user_ns, inode, iattr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा inode_operations zonefs_file_inode_operations = अणु
	.setattr	= zonefs_inode_setattr,
पूर्ण;

अटल पूर्णांक zonefs_file_fsync(काष्ठा file *file, loff_t start, loff_t end,
			     पूर्णांक datasync)
अणु
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक ret = 0;

	अगर (unlikely(IS_IMMUTABLE(inode)))
		वापस -EPERM;

	/*
	 * Since only direct ग_लिखोs are allowed in sequential files, page cache
	 * flush is needed only क्रम conventional zone files.
	 */
	अगर (ZONEFS_I(inode)->i_ztype == ZONEFS_ZTYPE_CNV)
		ret = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (!ret)
		ret = blkdev_issue_flush(inode->i_sb->s_bdev);

	अगर (ret)
		zonefs_io_error(inode, true);

	वापस ret;
पूर्ण

अटल vm_fault_t zonefs_filemap_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(file_inode(vmf->vma->vm_file));
	vm_fault_t ret;

	करोwn_पढ़ो(&zi->i_mmap_sem);
	ret = filemap_fault(vmf);
	up_पढ़ो(&zi->i_mmap_sem);

	वापस ret;
पूर्ण

अटल vm_fault_t zonefs_filemap_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा inode *inode = file_inode(vmf->vma->vm_file);
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	vm_fault_t ret;

	अगर (unlikely(IS_IMMUTABLE(inode)))
		वापस VM_FAULT_SIGBUS;

	/*
	 * Sanity check: only conventional zone files can have shared
	 * ग_लिखोable mappings.
	 */
	अगर (WARN_ON_ONCE(zi->i_ztype != ZONEFS_ZTYPE_CNV))
		वापस VM_FAULT_NOPAGE;

	sb_start_pagefault(inode->i_sb);
	file_update_समय(vmf->vma->vm_file);

	/* Serialize against truncates */
	करोwn_पढ़ो(&zi->i_mmap_sem);
	ret = iomap_page_mkग_लिखो(vmf, &zonefs_iomap_ops);
	up_पढ़ो(&zi->i_mmap_sem);

	sb_end_pagefault(inode->i_sb);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा zonefs_file_vm_ops = अणु
	.fault		= zonefs_filemap_fault,
	.map_pages	= filemap_map_pages,
	.page_mkग_लिखो	= zonefs_filemap_page_mkग_लिखो,
पूर्ण;

अटल पूर्णांक zonefs_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	/*
	 * Conventional zones accept अक्रमom ग_लिखोs, so their files can support
	 * shared writable mappings. For sequential zone files, only पढ़ो
	 * mappings are possible since there are no guarantees क्रम ग_लिखो
	 * ordering between msync() and page cache ग_लिखोback.
	 */
	अगर (ZONEFS_I(file_inode(file))->i_ztype == ZONEFS_ZTYPE_SEQ &&
	    (vma->vm_flags & VM_SHARED) && (vma->vm_flags & VM_MAYWRITE))
		वापस -EINVAL;

	file_accessed(file);
	vma->vm_ops = &zonefs_file_vm_ops;

	वापस 0;
पूर्ण

अटल loff_t zonefs_file_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	loff_t isize = i_size_पढ़ो(file_inode(file));

	/*
	 * Seeks are limited to below the zone size क्रम conventional zones
	 * and below the zone ग_लिखो poपूर्णांकer क्रम sequential zones. In both
	 * हालs, this limit is the inode size.
	 */
	वापस generic_file_llseek_size(file, offset, whence, isize, isize);
पूर्ण

अटल पूर्णांक zonefs_file_ग_लिखो_dio_end_io(काष्ठा kiocb *iocb, sमाप_प्रकार size,
					पूर्णांक error, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);

	अगर (error) अणु
		zonefs_io_error(inode, true);
		वापस error;
	पूर्ण

	अगर (size && zi->i_ztype != ZONEFS_ZTYPE_CNV) अणु
		/*
		 * Note that we may be seeing completions out of order,
		 * but that is not a problem since a ग_लिखो completed
		 * successfully necessarily means that all preceding ग_लिखोs
		 * were also successful. So we can safely increase the inode
		 * size to the ग_लिखो end location.
		 */
		mutex_lock(&zi->i_truncate_mutex);
		अगर (i_size_पढ़ो(inode) < iocb->ki_pos + size) अणु
			zonefs_update_stats(inode, iocb->ki_pos + size);
			zonefs_i_size_ग_लिखो(inode, iocb->ki_pos + size);
		पूर्ण
		mutex_unlock(&zi->i_truncate_mutex);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iomap_dio_ops zonefs_ग_लिखो_dio_ops = अणु
	.end_io			= zonefs_file_ग_लिखो_dio_end_io,
पूर्ण;

अटल sमाप_प्रकार zonefs_file_dio_append(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	काष्ठा block_device *bdev = inode->i_sb->s_bdev;
	अचिन्हित पूर्णांक max;
	काष्ठा bio *bio;
	sमाप_प्रकार size;
	पूर्णांक nr_pages;
	sमाप_प्रकार ret;

	max = queue_max_zone_append_sectors(bdev_get_queue(bdev));
	max = ALIGN_DOWN(max << SECTOR_SHIFT, inode->i_sb->s_blocksize);
	iov_iter_truncate(from, max);

	nr_pages = iov_iter_npages(from, BIO_MAX_VECS);
	अगर (!nr_pages)
		वापस 0;

	bio = bio_alloc(GFP_NOFS, nr_pages);
	अगर (!bio)
		वापस -ENOMEM;

	bio_set_dev(bio, bdev);
	bio->bi_iter.bi_sector = zi->i_zsector;
	bio->bi_ग_लिखो_hपूर्णांक = iocb->ki_hपूर्णांक;
	bio->bi_ioprio = iocb->ki_ioprio;
	bio->bi_opf = REQ_OP_ZONE_APPEND | REQ_SYNC | REQ_IDLE;
	अगर (iocb->ki_flags & IOCB_DSYNC)
		bio->bi_opf |= REQ_FUA;

	ret = bio_iov_iter_get_pages(bio, from);
	अगर (unlikely(ret))
		जाओ out_release;

	size = bio->bi_iter.bi_size;
	task_io_account_ग_लिखो(size);

	अगर (iocb->ki_flags & IOCB_HIPRI)
		bio_set_polled(bio, iocb);

	ret = submit_bio_रुको(bio);

	zonefs_file_ग_लिखो_dio_end_io(iocb, size, ret, 0);
	trace_zonefs_file_dio_append(inode, size, ret);

out_release:
	bio_release_pages(bio, false);
	bio_put(bio);

	अगर (ret >= 0) अणु
		iocb->ki_pos += size;
		वापस size;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Do not exceed the LFS limits nor the file zone size. If pos is under the
 * limit it becomes a लघु access. If it exceeds the limit, वापस -EFBIG.
 */
अटल loff_t zonefs_ग_लिखो_check_limits(काष्ठा file *file, loff_t pos,
					loff_t count)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	loff_t limit = rlimit(RLIMIT_FSIZE);
	loff_t max_size = zi->i_max_size;

	अगर (limit != RLIM_अनन्त) अणु
		अगर (pos >= limit) अणु
			send_sig(SIGXFSZ, current, 0);
			वापस -EFBIG;
		पूर्ण
		count = min(count, limit - pos);
	पूर्ण

	अगर (!(file->f_flags & O_LARGEखाता))
		max_size = min_t(loff_t, MAX_NON_LFS, max_size);

	अगर (unlikely(pos >= max_size))
		वापस -EFBIG;

	वापस min(count, max_size - pos);
पूर्ण

अटल sमाप_प्रकार zonefs_ग_लिखो_checks(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	loff_t count;

	अगर (IS_SWAPखाता(inode))
		वापस -ETXTBSY;

	अगर (!iov_iter_count(from))
		वापस 0;

	अगर ((iocb->ki_flags & IOCB_NOWAIT) && !(iocb->ki_flags & IOCB_सूचीECT))
		वापस -EINVAL;

	अगर (iocb->ki_flags & IOCB_APPEND) अणु
		अगर (zi->i_ztype != ZONEFS_ZTYPE_SEQ)
			वापस -EINVAL;
		mutex_lock(&zi->i_truncate_mutex);
		iocb->ki_pos = zi->i_wpoffset;
		mutex_unlock(&zi->i_truncate_mutex);
	पूर्ण

	count = zonefs_ग_लिखो_check_limits(file, iocb->ki_pos,
					  iov_iter_count(from));
	अगर (count < 0)
		वापस count;

	iov_iter_truncate(from, count);
	वापस iov_iter_count(from);
पूर्ण

/*
 * Handle direct ग_लिखोs. For sequential zone files, this is the only possible
 * ग_लिखो path. For these files, check that the user is issuing ग_लिखोs
 * sequentially from the end of the file. This code assumes that the block layer
 * delivers ग_लिखो requests to the device in sequential order. This is always the
 * हाल अगर a block IO scheduler implementing the ELEVATOR_F_ZBD_SEQ_WRITE
 * elevator feature is being used (e.g. mq-deadline). The block layer always
 * स्वतःmatically select such an elevator क्रम zoned block devices during the
 * device initialization.
 */
अटल sमाप_प्रकार zonefs_file_dio_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	bool sync = is_sync_kiocb(iocb);
	bool append = false;
	sमाप_प्रकार ret, count;

	/*
	 * For async direct IOs to sequential zone files, refuse IOCB_NOWAIT
	 * as this can cause ग_लिखो reordering (e.g. the first aio माला_लो EAGAIN
	 * on the inode lock but the second goes through but is now unaligned).
	 */
	अगर (zi->i_ztype == ZONEFS_ZTYPE_SEQ && !sync &&
	    (iocb->ki_flags & IOCB_NOWAIT))
		वापस -EOPNOTSUPP;

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		अगर (!inode_trylock(inode))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		inode_lock(inode);
	पूर्ण

	count = zonefs_ग_लिखो_checks(iocb, from);
	अगर (count <= 0) अणु
		ret = count;
		जाओ inode_unlock;
	पूर्ण

	अगर ((iocb->ki_pos | count) & (sb->s_blocksize - 1)) अणु
		ret = -EINVAL;
		जाओ inode_unlock;
	पूर्ण

	/* Enक्रमce sequential ग_लिखोs (append only) in sequential zones */
	अगर (zi->i_ztype == ZONEFS_ZTYPE_SEQ) अणु
		mutex_lock(&zi->i_truncate_mutex);
		अगर (iocb->ki_pos != zi->i_wpoffset) अणु
			mutex_unlock(&zi->i_truncate_mutex);
			ret = -EINVAL;
			जाओ inode_unlock;
		पूर्ण
		mutex_unlock(&zi->i_truncate_mutex);
		append = sync;
	पूर्ण

	अगर (append)
		ret = zonefs_file_dio_append(iocb, from);
	अन्यथा
		ret = iomap_dio_rw(iocb, from, &zonefs_iomap_ops,
				   &zonefs_ग_लिखो_dio_ops, 0);
	अगर (zi->i_ztype == ZONEFS_ZTYPE_SEQ &&
	    (ret > 0 || ret == -EIOCBQUEUED)) अणु
		अगर (ret > 0)
			count = ret;
		mutex_lock(&zi->i_truncate_mutex);
		zi->i_wpoffset += count;
		mutex_unlock(&zi->i_truncate_mutex);
	पूर्ण

inode_unlock:
	inode_unlock(inode);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार zonefs_file_buffered_ग_लिखो(काष्ठा kiocb *iocb,
					  काष्ठा iov_iter *from)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	sमाप_प्रकार ret;

	/*
	 * Direct IO ग_लिखोs are mandatory क्रम sequential zone files so that the
	 * ग_लिखो IO issuing order is preserved.
	 */
	अगर (zi->i_ztype != ZONEFS_ZTYPE_CNV)
		वापस -EIO;

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		अगर (!inode_trylock(inode))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		inode_lock(inode);
	पूर्ण

	ret = zonefs_ग_लिखो_checks(iocb, from);
	अगर (ret <= 0)
		जाओ inode_unlock;

	ret = iomap_file_buffered_ग_लिखो(iocb, from, &zonefs_iomap_ops);
	अगर (ret > 0)
		iocb->ki_pos += ret;
	अन्यथा अगर (ret == -EIO)
		zonefs_io_error(inode, true);

inode_unlock:
	inode_unlock(inode);
	अगर (ret > 0)
		ret = generic_ग_लिखो_sync(iocb, ret);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार zonefs_file_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);

	अगर (unlikely(IS_IMMUTABLE(inode)))
		वापस -EPERM;

	अगर (sb_rकरोnly(inode->i_sb))
		वापस -EROFS;

	/* Write operations beyond the zone size are not allowed */
	अगर (iocb->ki_pos >= ZONEFS_I(inode)->i_max_size)
		वापस -EFBIG;

	अगर (iocb->ki_flags & IOCB_सूचीECT) अणु
		sमाप_प्रकार ret = zonefs_file_dio_ग_लिखो(iocb, from);
		अगर (ret != -ENOTBLK)
			वापस ret;
	पूर्ण

	वापस zonefs_file_buffered_ग_लिखो(iocb, from);
पूर्ण

अटल पूर्णांक zonefs_file_पढ़ो_dio_end_io(काष्ठा kiocb *iocb, sमाप_प्रकार size,
				       पूर्णांक error, अचिन्हित पूर्णांक flags)
अणु
	अगर (error) अणु
		zonefs_io_error(file_inode(iocb->ki_filp), false);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iomap_dio_ops zonefs_पढ़ो_dio_ops = अणु
	.end_io			= zonefs_file_पढ़ो_dio_end_io,
पूर्ण;

अटल sमाप_प्रकार zonefs_file_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	loff_t isize;
	sमाप_प्रकार ret;

	/* Offline zones cannot be पढ़ो */
	अगर (unlikely(IS_IMMUTABLE(inode) && !(inode->i_mode & 0777)))
		वापस -EPERM;

	अगर (iocb->ki_pos >= zi->i_max_size)
		वापस 0;

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		अगर (!inode_trylock_shared(inode))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		inode_lock_shared(inode);
	पूर्ण

	/* Limit पढ़ो operations to written data */
	mutex_lock(&zi->i_truncate_mutex);
	isize = i_size_पढ़ो(inode);
	अगर (iocb->ki_pos >= isize) अणु
		mutex_unlock(&zi->i_truncate_mutex);
		ret = 0;
		जाओ inode_unlock;
	पूर्ण
	iov_iter_truncate(to, isize - iocb->ki_pos);
	mutex_unlock(&zi->i_truncate_mutex);

	अगर (iocb->ki_flags & IOCB_सूचीECT) अणु
		माप_प्रकार count = iov_iter_count(to);

		अगर ((iocb->ki_pos | count) & (sb->s_blocksize - 1)) अणु
			ret = -EINVAL;
			जाओ inode_unlock;
		पूर्ण
		file_accessed(iocb->ki_filp);
		ret = iomap_dio_rw(iocb, to, &zonefs_iomap_ops,
				   &zonefs_पढ़ो_dio_ops, 0);
	पूर्ण अन्यथा अणु
		ret = generic_file_पढ़ो_iter(iocb, to);
		अगर (ret == -EIO)
			zonefs_io_error(inode, false);
	पूर्ण

inode_unlock:
	inode_unlock_shared(inode);

	वापस ret;
पूर्ण

अटल अंतरभूत bool zonefs_file_use_exp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	काष्ठा zonefs_sb_info *sbi = ZONEFS_SB(inode->i_sb);

	अगर (!(sbi->s_mount_opts & ZONEFS_MNTOPT_EXPLICIT_OPEN))
		वापस false;

	अगर (zi->i_ztype != ZONEFS_ZTYPE_SEQ)
		वापस false;

	अगर (!(file->f_mode & FMODE_WRITE))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक zonefs_खोलो_zone(काष्ठा inode *inode)
अणु
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	काष्ठा zonefs_sb_info *sbi = ZONEFS_SB(inode->i_sb);
	पूर्णांक ret = 0;

	mutex_lock(&zi->i_truncate_mutex);

	अगर (!zi->i_wr_refcnt) अणु
		अगर (atomic_inc_वापस(&sbi->s_खोलो_zones) > sbi->s_max_खोलो_zones) अणु
			atomic_dec(&sbi->s_खोलो_zones);
			ret = -EBUSY;
			जाओ unlock;
		पूर्ण

		अगर (i_size_पढ़ो(inode) < zi->i_max_size) अणु
			ret = zonefs_zone_mgmt(inode, REQ_OP_ZONE_OPEN);
			अगर (ret) अणु
				atomic_dec(&sbi->s_खोलो_zones);
				जाओ unlock;
			पूर्ण
			zi->i_flags |= ZONEFS_ZONE_OPEN;
		पूर्ण
	पूर्ण

	zi->i_wr_refcnt++;

unlock:
	mutex_unlock(&zi->i_truncate_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक zonefs_file_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	ret = generic_file_खोलो(inode, file);
	अगर (ret)
		वापस ret;

	अगर (zonefs_file_use_exp_खोलो(inode, file))
		वापस zonefs_खोलो_zone(inode);

	वापस 0;
पूर्ण

अटल व्योम zonefs_बंद_zone(काष्ठा inode *inode)
अणु
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);
	पूर्णांक ret = 0;

	mutex_lock(&zi->i_truncate_mutex);
	zi->i_wr_refcnt--;
	अगर (!zi->i_wr_refcnt) अणु
		काष्ठा zonefs_sb_info *sbi = ZONEFS_SB(inode->i_sb);
		काष्ठा super_block *sb = inode->i_sb;

		/*
		 * If the file zone is full, it is not खोलो anymore and we only
		 * need to decrement the खोलो count.
		 */
		अगर (!(zi->i_flags & ZONEFS_ZONE_OPEN))
			जाओ dec;

		ret = zonefs_zone_mgmt(inode, REQ_OP_ZONE_CLOSE);
		अगर (ret) अणु
			__zonefs_io_error(inode, false);
			/*
			 * Leaving zones explicitly खोलो may lead to a state
			 * where most zones cannot be written (zone resources
			 * exhausted). So take preventive action by remounting
			 * पढ़ो-only.
			 */
			अगर (zi->i_flags & ZONEFS_ZONE_OPEN &&
			    !(sb->s_flags & SB_RDONLY)) अणु
				zonefs_warn(sb, "closing zone failed, remounting filesystem read-only\n");
				sb->s_flags |= SB_RDONLY;
			पूर्ण
		पूर्ण
		zi->i_flags &= ~ZONEFS_ZONE_OPEN;
dec:
		atomic_dec(&sbi->s_खोलो_zones);
	पूर्ण
	mutex_unlock(&zi->i_truncate_mutex);
पूर्ण

अटल पूर्णांक zonefs_file_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/*
	 * If we explicitly खोलो a zone we must बंद it again as well, but the
	 * zone management operation can fail (either due to an IO error or as
	 * the zone has gone offline or पढ़ो-only). Make sure we करोn't fail the
	 * बंद(2) क्रम user-space.
	 */
	अगर (zonefs_file_use_exp_खोलो(inode, file))
		zonefs_बंद_zone(inode);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations zonefs_file_operations = अणु
	.खोलो		= zonefs_file_खोलो,
	.release	= zonefs_file_release,
	.fsync		= zonefs_file_fsync,
	.mmap		= zonefs_file_mmap,
	.llseek		= zonefs_file_llseek,
	.पढ़ो_iter	= zonefs_file_पढ़ो_iter,
	.ग_लिखो_iter	= zonefs_file_ग_लिखो_iter,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.iopoll		= iomap_dio_iopoll,
पूर्ण;

अटल काष्ठा kmem_cache *zonefs_inode_cachep;

अटल काष्ठा inode *zonefs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा zonefs_inode_info *zi;

	zi = kmem_cache_alloc(zonefs_inode_cachep, GFP_KERNEL);
	अगर (!zi)
		वापस शून्य;

	inode_init_once(&zi->i_vnode);
	mutex_init(&zi->i_truncate_mutex);
	init_rwsem(&zi->i_mmap_sem);
	zi->i_wr_refcnt = 0;

	वापस &zi->i_vnode;
पूर्ण

अटल व्योम zonefs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(zonefs_inode_cachep, ZONEFS_I(inode));
पूर्ण

/*
 * File प्रणाली stat.
 */
अटल पूर्णांक zonefs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा zonefs_sb_info *sbi = ZONEFS_SB(sb);
	क्रमागत zonefs_ztype t;

	buf->f_type = ZONEFS_MAGIC;
	buf->f_bsize = sb->s_blocksize;
	buf->f_namelen = ZONEFS_NAME_MAX;

	spin_lock(&sbi->s_lock);

	buf->f_blocks = sbi->s_blocks;
	अगर (WARN_ON(sbi->s_used_blocks > sbi->s_blocks))
		buf->f_bमुक्त = 0;
	अन्यथा
		buf->f_bमुक्त = buf->f_blocks - sbi->s_used_blocks;
	buf->f_bavail = buf->f_bमुक्त;

	क्रम (t = 0; t < ZONEFS_ZTYPE_MAX; t++) अणु
		अगर (sbi->s_nr_files[t])
			buf->f_files += sbi->s_nr_files[t] + 1;
	पूर्ण
	buf->f_fमुक्त = 0;

	spin_unlock(&sbi->s_lock);

	buf->f_fsid = uuid_to_fsid(sbi->s_uuid.b);

	वापस 0;
पूर्ण

क्रमागत अणु
	Opt_errors_ro, Opt_errors_zro, Opt_errors_zol, Opt_errors_repair,
	Opt_explicit_खोलो, Opt_err,
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणु Opt_errors_ro,	"errors=remount-ro"पूर्ण,
	अणु Opt_errors_zro,	"errors=zone-ro"पूर्ण,
	अणु Opt_errors_zol,	"errors=zone-offline"पूर्ण,
	अणु Opt_errors_repair,	"errors=repair"पूर्ण,
	अणु Opt_explicit_खोलो,	"explicit-open" पूर्ण,
	अणु Opt_err,		शून्यपूर्ण
पूर्ण;

अटल पूर्णांक zonefs_parse_options(काष्ठा super_block *sb, अक्षर *options)
अणु
	काष्ठा zonefs_sb_info *sbi = ZONEFS_SB(sb);
	substring_t args[MAX_OPT_ARGS];
	अक्षर *p;

	अगर (!options)
		वापस 0;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token;

		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_errors_ro:
			sbi->s_mount_opts &= ~ZONEFS_MNTOPT_ERRORS_MASK;
			sbi->s_mount_opts |= ZONEFS_MNTOPT_ERRORS_RO;
			अवरोध;
		हाल Opt_errors_zro:
			sbi->s_mount_opts &= ~ZONEFS_MNTOPT_ERRORS_MASK;
			sbi->s_mount_opts |= ZONEFS_MNTOPT_ERRORS_ZRO;
			अवरोध;
		हाल Opt_errors_zol:
			sbi->s_mount_opts &= ~ZONEFS_MNTOPT_ERRORS_MASK;
			sbi->s_mount_opts |= ZONEFS_MNTOPT_ERRORS_ZOL;
			अवरोध;
		हाल Opt_errors_repair:
			sbi->s_mount_opts &= ~ZONEFS_MNTOPT_ERRORS_MASK;
			sbi->s_mount_opts |= ZONEFS_MNTOPT_ERRORS_REPAIR;
			अवरोध;
		हाल Opt_explicit_खोलो:
			sbi->s_mount_opts |= ZONEFS_MNTOPT_EXPLICIT_OPEN;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zonefs_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा zonefs_sb_info *sbi = ZONEFS_SB(root->d_sb);

	अगर (sbi->s_mount_opts & ZONEFS_MNTOPT_ERRORS_RO)
		seq_माला_दो(seq, ",errors=remount-ro");
	अगर (sbi->s_mount_opts & ZONEFS_MNTOPT_ERRORS_ZRO)
		seq_माला_दो(seq, ",errors=zone-ro");
	अगर (sbi->s_mount_opts & ZONEFS_MNTOPT_ERRORS_ZOL)
		seq_माला_दो(seq, ",errors=zone-offline");
	अगर (sbi->s_mount_opts & ZONEFS_MNTOPT_ERRORS_REPAIR)
		seq_माला_दो(seq, ",errors=repair");

	वापस 0;
पूर्ण

अटल पूर्णांक zonefs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	sync_fileप्रणाली(sb);

	वापस zonefs_parse_options(sb, data);
पूर्ण

अटल स्थिर काष्ठा super_operations zonefs_sops = अणु
	.alloc_inode	= zonefs_alloc_inode,
	.मुक्त_inode	= zonefs_मुक्त_inode,
	.statfs		= zonefs_statfs,
	.remount_fs	= zonefs_remount,
	.show_options	= zonefs_show_options,
पूर्ण;

अटल स्थिर काष्ठा inode_operations zonefs_dir_inode_operations = अणु
	.lookup		= simple_lookup,
	.setattr	= zonefs_inode_setattr,
पूर्ण;

अटल व्योम zonefs_init_dir_inode(काष्ठा inode *parent, काष्ठा inode *inode,
				  क्रमागत zonefs_ztype type)
अणु
	काष्ठा super_block *sb = parent->i_sb;

	inode->i_ino = blkdev_nr_zones(sb->s_bdev->bd_disk) + type + 1;
	inode_init_owner(&init_user_ns, inode, parent, S_IFसूची | 0555);
	inode->i_op = &zonefs_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;
	set_nlink(inode, 2);
	inc_nlink(parent);
पूर्ण

अटल व्योम zonefs_init_file_inode(काष्ठा inode *inode, काष्ठा blk_zone *zone,
				   क्रमागत zonefs_ztype type)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा zonefs_sb_info *sbi = ZONEFS_SB(sb);
	काष्ठा zonefs_inode_info *zi = ZONEFS_I(inode);

	inode->i_ino = zone->start >> sbi->s_zone_sectors_shअगरt;
	inode->i_mode = S_IFREG | sbi->s_perm;

	zi->i_ztype = type;
	zi->i_zsector = zone->start;
	zi->i_zone_size = zone->len << SECTOR_SHIFT;

	zi->i_max_size = min_t(loff_t, MAX_LFS_खाताSIZE,
			       zone->capacity << SECTOR_SHIFT);
	zi->i_wpoffset = zonefs_check_zone_condition(inode, zone, true, true);

	inode->i_uid = sbi->s_uid;
	inode->i_gid = sbi->s_gid;
	inode->i_size = zi->i_wpoffset;
	inode->i_blocks = zi->i_max_size >> SECTOR_SHIFT;

	inode->i_op = &zonefs_file_inode_operations;
	inode->i_fop = &zonefs_file_operations;
	inode->i_mapping->a_ops = &zonefs_file_aops;

	sb->s_maxbytes = max(zi->i_max_size, sb->s_maxbytes);
	sbi->s_blocks += zi->i_max_size >> sb->s_blocksize_bits;
	sbi->s_used_blocks += zi->i_wpoffset >> sb->s_blocksize_bits;
पूर्ण

अटल काष्ठा dentry *zonefs_create_inode(काष्ठा dentry *parent,
					स्थिर अक्षर *name, काष्ठा blk_zone *zone,
					क्रमागत zonefs_ztype type)
अणु
	काष्ठा inode *dir = d_inode(parent);
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;

	dentry = d_alloc_name(parent, name);
	अगर (!dentry)
		वापस शून्य;

	inode = new_inode(parent->d_sb);
	अगर (!inode)
		जाओ dput;

	inode->i_स_समय = inode->i_mसमय = inode->i_aसमय = dir->i_स_समय;
	अगर (zone)
		zonefs_init_file_inode(inode, zone, type);
	अन्यथा
		zonefs_init_dir_inode(dir, inode, type);
	d_add(dentry, inode);
	dir->i_size++;

	वापस dentry;

dput:
	dput(dentry);

	वापस शून्य;
पूर्ण

काष्ठा zonefs_zone_data अणु
	काष्ठा super_block	*sb;
	अचिन्हित पूर्णांक		nr_zones[ZONEFS_ZTYPE_MAX];
	काष्ठा blk_zone		*zones;
पूर्ण;

/*
 * Create a zone group and populate it with zone files.
 */
अटल पूर्णांक zonefs_create_zgroup(काष्ठा zonefs_zone_data *zd,
				क्रमागत zonefs_ztype type)
अणु
	काष्ठा super_block *sb = zd->sb;
	काष्ठा zonefs_sb_info *sbi = ZONEFS_SB(sb);
	काष्ठा blk_zone *zone, *next, *end;
	स्थिर अक्षर *zgroup_name;
	अक्षर *file_name;
	काष्ठा dentry *dir;
	अचिन्हित पूर्णांक n = 0;
	पूर्णांक ret;

	/* If the group is empty, there is nothing to करो */
	अगर (!zd->nr_zones[type])
		वापस 0;

	file_name = kदो_स्मृति(ZONEFS_NAME_MAX, GFP_KERNEL);
	अगर (!file_name)
		वापस -ENOMEM;

	अगर (type == ZONEFS_ZTYPE_CNV)
		zgroup_name = "cnv";
	अन्यथा
		zgroup_name = "seq";

	dir = zonefs_create_inode(sb->s_root, zgroup_name, शून्य, type);
	अगर (!dir) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	/*
	 * The first zone contains the super block: skip it.
	 */
	end = zd->zones + blkdev_nr_zones(sb->s_bdev->bd_disk);
	क्रम (zone = &zd->zones[1]; zone < end; zone = next) अणु

		next = zone + 1;
		अगर (zonefs_zone_type(zone) != type)
			जारी;

		/*
		 * For conventional zones, contiguous zones can be aggregated
		 * together to क्रमm larger files. Note that this overग_लिखोs the
		 * length of the first zone of the set of contiguous zones
		 * aggregated together. If one offline or पढ़ो-only zone is
		 * found, assume that all zones aggregated have the same
		 * condition.
		 */
		अगर (type == ZONEFS_ZTYPE_CNV &&
		    (sbi->s_features & ZONEFS_F_AGGRCNV)) अणु
			क्रम (; next < end; next++) अणु
				अगर (zonefs_zone_type(next) != type)
					अवरोध;
				zone->len += next->len;
				zone->capacity += next->capacity;
				अगर (next->cond == BLK_ZONE_COND_READONLY &&
				    zone->cond != BLK_ZONE_COND_OFFLINE)
					zone->cond = BLK_ZONE_COND_READONLY;
				अन्यथा अगर (next->cond == BLK_ZONE_COND_OFFLINE)
					zone->cond = BLK_ZONE_COND_OFFLINE;
			पूर्ण
			अगर (zone->capacity != zone->len) अणु
				zonefs_err(sb, "Invalid conventional zone capacity\n");
				ret = -EINVAL;
				जाओ मुक्त;
			पूर्ण
		पूर्ण

		/*
		 * Use the file number within its group as file name.
		 */
		snम_लिखो(file_name, ZONEFS_NAME_MAX - 1, "%u", n);
		अगर (!zonefs_create_inode(dir, file_name, zone, type)) अणु
			ret = -ENOMEM;
			जाओ मुक्त;
		पूर्ण

		n++;
	पूर्ण

	zonefs_info(sb, "Zone group \"%s\" has %u file%s\n",
		    zgroup_name, n, n > 1 ? "s" : "");

	sbi->s_nr_files[type] = n;
	ret = 0;

मुक्त:
	kमुक्त(file_name);

	वापस ret;
पूर्ण

अटल पूर्णांक zonefs_get_zone_info_cb(काष्ठा blk_zone *zone, अचिन्हित पूर्णांक idx,
				   व्योम *data)
अणु
	काष्ठा zonefs_zone_data *zd = data;

	/*
	 * Count the number of usable zones: the first zone at index 0 contains
	 * the super block and is ignored.
	 */
	चयन (zone->type) अणु
	हाल BLK_ZONE_TYPE_CONVENTIONAL:
		zone->wp = zone->start + zone->len;
		अगर (idx)
			zd->nr_zones[ZONEFS_ZTYPE_CNV]++;
		अवरोध;
	हाल BLK_ZONE_TYPE_SEQWRITE_REQ:
	हाल BLK_ZONE_TYPE_SEQWRITE_PREF:
		अगर (idx)
			zd->nr_zones[ZONEFS_ZTYPE_SEQ]++;
		अवरोध;
	शेष:
		zonefs_err(zd->sb, "Unsupported zone type 0x%x\n",
			   zone->type);
		वापस -EIO;
	पूर्ण

	स_नकल(&zd->zones[idx], zone, माप(काष्ठा blk_zone));

	वापस 0;
पूर्ण

अटल पूर्णांक zonefs_get_zone_info(काष्ठा zonefs_zone_data *zd)
अणु
	काष्ठा block_device *bdev = zd->sb->s_bdev;
	पूर्णांक ret;

	zd->zones = kvसुस्मृति(blkdev_nr_zones(bdev->bd_disk),
			     माप(काष्ठा blk_zone), GFP_KERNEL);
	अगर (!zd->zones)
		वापस -ENOMEM;

	/* Get zones inक्रमmation from the device */
	ret = blkdev_report_zones(bdev, 0, BLK_ALL_ZONES,
				  zonefs_get_zone_info_cb, zd);
	अगर (ret < 0) अणु
		zonefs_err(zd->sb, "Zone report failed %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ret != blkdev_nr_zones(bdev->bd_disk)) अणु
		zonefs_err(zd->sb, "Invalid zone report (%d/%u zones)\n",
			   ret, blkdev_nr_zones(bdev->bd_disk));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम zonefs_cleanup_zone_info(काष्ठा zonefs_zone_data *zd)
अणु
	kvमुक्त(zd->zones);
पूर्ण

/*
 * Read super block inक्रमmation from the device.
 */
अटल पूर्णांक zonefs_पढ़ो_super(काष्ठा super_block *sb)
अणु
	काष्ठा zonefs_sb_info *sbi = ZONEFS_SB(sb);
	काष्ठा zonefs_super *super;
	u32 crc, stored_crc;
	काष्ठा page *page;
	काष्ठा bio_vec bio_vec;
	काष्ठा bio bio;
	पूर्णांक ret;

	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	bio_init(&bio, &bio_vec, 1);
	bio.bi_iter.bi_sector = 0;
	bio.bi_opf = REQ_OP_READ;
	bio_set_dev(&bio, sb->s_bdev);
	bio_add_page(&bio, page, PAGE_SIZE, 0);

	ret = submit_bio_रुको(&bio);
	अगर (ret)
		जाओ मुक्त_page;

	super = kmap(page);

	ret = -EINVAL;
	अगर (le32_to_cpu(super->s_magic) != ZONEFS_MAGIC)
		जाओ unmap;

	stored_crc = le32_to_cpu(super->s_crc);
	super->s_crc = 0;
	crc = crc32(~0U, (अचिन्हित अक्षर *)super, माप(काष्ठा zonefs_super));
	अगर (crc != stored_crc) अणु
		zonefs_err(sb, "Invalid checksum (Expected 0x%08x, got 0x%08x)",
			   crc, stored_crc);
		जाओ unmap;
	पूर्ण

	sbi->s_features = le64_to_cpu(super->s_features);
	अगर (sbi->s_features & ~ZONEFS_F_DEFINED_FEATURES) अणु
		zonefs_err(sb, "Unknown features set 0x%llx\n",
			   sbi->s_features);
		जाओ unmap;
	पूर्ण

	अगर (sbi->s_features & ZONEFS_F_UID) अणु
		sbi->s_uid = make_kuid(current_user_ns(),
				       le32_to_cpu(super->s_uid));
		अगर (!uid_valid(sbi->s_uid)) अणु
			zonefs_err(sb, "Invalid UID feature\n");
			जाओ unmap;
		पूर्ण
	पूर्ण

	अगर (sbi->s_features & ZONEFS_F_GID) अणु
		sbi->s_gid = make_kgid(current_user_ns(),
				       le32_to_cpu(super->s_gid));
		अगर (!gid_valid(sbi->s_gid)) अणु
			zonefs_err(sb, "Invalid GID feature\n");
			जाओ unmap;
		पूर्ण
	पूर्ण

	अगर (sbi->s_features & ZONEFS_F_PERM)
		sbi->s_perm = le32_to_cpu(super->s_perm);

	अगर (स_प्रथम_inv(super->s_reserved, 0, माप(super->s_reserved))) अणु
		zonefs_err(sb, "Reserved area is being used\n");
		जाओ unmap;
	पूर्ण

	import_uuid(&sbi->s_uuid, super->s_uuid);
	ret = 0;

unmap:
	kunmap(page);
मुक्त_page:
	__मुक्त_page(page);

	वापस ret;
पूर्ण

/*
 * Check that the device is zoned. If it is, get the list of zones and create
 * sub-directories and files according to the device zone configuration and
 * क्रमmat options.
 */
अटल पूर्णांक zonefs_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा zonefs_zone_data zd;
	काष्ठा zonefs_sb_info *sbi;
	काष्ठा inode *inode;
	क्रमागत zonefs_ztype t;
	पूर्णांक ret;

	अगर (!bdev_is_zoned(sb->s_bdev)) अणु
		zonefs_err(sb, "Not a zoned block device\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Initialize super block inक्रमmation: the maximum file size is updated
	 * when the zone files are created so that the क्रमmat option
	 * ZONEFS_F_AGGRCNV which increases the maximum file size of a file
	 * beyond the zone size is taken पूर्णांकo account.
	 */
	sbi = kzalloc(माप(*sbi), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;

	spin_lock_init(&sbi->s_lock);
	sb->s_fs_info = sbi;
	sb->s_magic = ZONEFS_MAGIC;
	sb->s_maxbytes = 0;
	sb->s_op = &zonefs_sops;
	sb->s_समय_gran	= 1;

	/*
	 * The block size is set to the device zone ग_लिखो granularity to ensure
	 * that ग_लिखो operations are always aligned according to the device
	 * पूर्णांकerface स्थिरraपूर्णांकs.
	 */
	sb_set_blocksize(sb, bdev_zone_ग_लिखो_granularity(sb->s_bdev));
	sbi->s_zone_sectors_shअगरt = ilog2(bdev_zone_sectors(sb->s_bdev));
	sbi->s_uid = GLOBAL_ROOT_UID;
	sbi->s_gid = GLOBAL_ROOT_GID;
	sbi->s_perm = 0640;
	sbi->s_mount_opts = ZONEFS_MNTOPT_ERRORS_RO;
	sbi->s_max_खोलो_zones = bdev_max_खोलो_zones(sb->s_bdev);
	atomic_set(&sbi->s_खोलो_zones, 0);
	अगर (!sbi->s_max_खोलो_zones &&
	    sbi->s_mount_opts & ZONEFS_MNTOPT_EXPLICIT_OPEN) अणु
		zonefs_info(sb, "No open zones limit. Ignoring explicit_open mount option\n");
		sbi->s_mount_opts &= ~ZONEFS_MNTOPT_EXPLICIT_OPEN;
	पूर्ण

	ret = zonefs_पढ़ो_super(sb);
	अगर (ret)
		वापस ret;

	ret = zonefs_parse_options(sb, data);
	अगर (ret)
		वापस ret;

	स_रखो(&zd, 0, माप(काष्ठा zonefs_zone_data));
	zd.sb = sb;
	ret = zonefs_get_zone_info(&zd);
	अगर (ret)
		जाओ cleanup;

	zonefs_info(sb, "Mounting %u zones",
		    blkdev_nr_zones(sb->s_bdev->bd_disk));

	/* Create root directory inode */
	ret = -ENOMEM;
	inode = new_inode(sb);
	अगर (!inode)
		जाओ cleanup;

	inode->i_ino = blkdev_nr_zones(sb->s_bdev->bd_disk);
	inode->i_mode = S_IFसूची | 0555;
	inode->i_स_समय = inode->i_mसमय = inode->i_aसमय = current_समय(inode);
	inode->i_op = &zonefs_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;
	set_nlink(inode, 2);

	sb->s_root = d_make_root(inode);
	अगर (!sb->s_root)
		जाओ cleanup;

	/* Create and populate files in zone groups directories */
	क्रम (t = 0; t < ZONEFS_ZTYPE_MAX; t++) अणु
		ret = zonefs_create_zgroup(&zd, t);
		अगर (ret)
			अवरोध;
	पूर्ण

cleanup:
	zonefs_cleanup_zone_info(&zd);

	वापस ret;
पूर्ण

अटल काष्ठा dentry *zonefs_mount(काष्ठा file_प्रणाली_type *fs_type,
				   पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, zonefs_fill_super);
पूर्ण

अटल व्योम zonefs_समाप्त_super(काष्ठा super_block *sb)
अणु
	काष्ठा zonefs_sb_info *sbi = ZONEFS_SB(sb);

	अगर (sb->s_root)
		d_genocide(sb->s_root);
	समाप्त_block_super(sb);
	kमुक्त(sbi);
पूर्ण

/*
 * File प्रणाली definition and registration.
 */
अटल काष्ठा file_प्रणाली_type zonefs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "zonefs",
	.mount		= zonefs_mount,
	.समाप्त_sb	= zonefs_समाप्त_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;

अटल पूर्णांक __init zonefs_init_inodecache(व्योम)
अणु
	zonefs_inode_cachep = kmem_cache_create("zonefs_inode_cache",
			माप(काष्ठा zonefs_inode_info), 0,
			(SLAB_RECLAIM_ACCOUNT | SLAB_MEM_SPREAD | SLAB_ACCOUNT),
			शून्य);
	अगर (zonefs_inode_cachep == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम zonefs_destroy_inodecache(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy the inode cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(zonefs_inode_cachep);
पूर्ण

अटल पूर्णांक __init zonefs_init(व्योम)
अणु
	पूर्णांक ret;

	BUILD_BUG_ON(माप(काष्ठा zonefs_super) != ZONEFS_SUPER_SIZE);

	ret = zonefs_init_inodecache();
	अगर (ret)
		वापस ret;

	ret = रेजिस्टर_fileप्रणाली(&zonefs_type);
	अगर (ret) अणु
		zonefs_destroy_inodecache();
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास zonefs_निकास(व्योम)
अणु
	zonefs_destroy_inodecache();
	unरेजिस्टर_fileप्रणाली(&zonefs_type);
पूर्ण

MODULE_AUTHOR("Damien Le Moal");
MODULE_DESCRIPTION("Zone file system for zoned block devices");
MODULE_LICENSE("GPL");
module_init(zonefs_init);
module_निकास(zonefs_निकास);
