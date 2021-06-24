<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hfsplus/wrapper.c
 *
 * Copyright (C) 2001
 * Brad Boyer (flar@allandria.com)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 * Handling of HFS wrappers around HFS+ volumes
 */

#समावेश <linux/fs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/genhd.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "hfsplus_fs.h"
#समावेश "hfsplus_raw.h"

काष्ठा hfsplus_wd अणु
	u32 ablk_size;
	u16 ablk_start;
	u16 embed_start;
	u16 embed_count;
पूर्ण;

/**
 * hfsplus_submit_bio - Perक्रमm block I/O
 * @sb: super block of volume क्रम I/O
 * @sector: block to पढ़ो or ग_लिखो, क्रम blocks of HFSPLUS_SECTOR_SIZE bytes
 * @buf: buffer क्रम I/O
 * @data: output poपूर्णांकer क्रम location of requested data
 * @op: direction of I/O
 * @op_flags: request op flags
 *
 * The unit of I/O is hfsplus_min_io_size(sb), which may be bigger than
 * HFSPLUS_SECTOR_SIZE, and @buf must be sized accordingly. On पढ़ोs
 * @data will वापस a poपूर्णांकer to the start of the requested sector,
 * which may not be the same location as @buf.
 *
 * If @sector is not aligned to the bdev logical block size it will
 * be rounded करोwn. For ग_लिखोs this means that @buf should contain data
 * that starts at the rounded-करोwn address. As दीर्घ as the data was
 * पढ़ो using hfsplus_submit_bio() and the same buffer is used things
 * will work correctly.
 */
पूर्णांक hfsplus_submit_bio(काष्ठा super_block *sb, sector_t sector,
		       व्योम *buf, व्योम **data, पूर्णांक op, पूर्णांक op_flags)
अणु
	काष्ठा bio *bio;
	पूर्णांक ret = 0;
	u64 io_size;
	loff_t start;
	पूर्णांक offset;

	/*
	 * Align sector to hardware sector size and find offset. We
	 * assume that io_size is a घातer of two, which _should_
	 * be true.
	 */
	io_size = hfsplus_min_io_size(sb);
	start = (loff_t)sector << HFSPLUS_SECTOR_SHIFT;
	offset = start & (io_size - 1);
	sector &= ~((io_size >> HFSPLUS_SECTOR_SHIFT) - 1);

	bio = bio_alloc(GFP_NOIO, 1);
	bio->bi_iter.bi_sector = sector;
	bio_set_dev(bio, sb->s_bdev);
	bio_set_op_attrs(bio, op, op_flags);

	अगर (op != WRITE && data)
		*data = (u8 *)buf + offset;

	जबतक (io_size > 0) अणु
		अचिन्हित पूर्णांक page_offset = offset_in_page(buf);
		अचिन्हित पूर्णांक len = min_t(अचिन्हित पूर्णांक, PAGE_SIZE - page_offset,
					 io_size);

		ret = bio_add_page(bio, virt_to_page(buf), len, page_offset);
		अगर (ret != len) अणु
			ret = -EIO;
			जाओ out;
		पूर्ण
		io_size -= len;
		buf = (u8 *)buf + len;
	पूर्ण

	ret = submit_bio_रुको(bio);
out:
	bio_put(bio);
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक hfsplus_पढ़ो_mdb(व्योम *bufptr, काष्ठा hfsplus_wd *wd)
अणु
	u32 extent;
	u16 attrib;
	__be16 sig;

	sig = *(__be16 *)(bufptr + HFSP_WRAPOFF_EMBEDSIG);
	अगर (sig != cpu_to_be16(HFSPLUS_VOLHEAD_SIG) &&
	    sig != cpu_to_be16(HFSPLUS_VOLHEAD_SIGX))
		वापस 0;

	attrib = be16_to_cpu(*(__be16 *)(bufptr + HFSP_WRAPOFF_ATTRIB));
	अगर (!(attrib & HFSP_WRAP_ATTRIB_SLOCK) ||
	   !(attrib & HFSP_WRAP_ATTRIB_SPARED))
		वापस 0;

	wd->ablk_size =
		be32_to_cpu(*(__be32 *)(bufptr + HFSP_WRAPOFF_ABLKSIZE));
	अगर (wd->ablk_size < HFSPLUS_SECTOR_SIZE)
		वापस 0;
	अगर (wd->ablk_size % HFSPLUS_SECTOR_SIZE)
		वापस 0;
	wd->ablk_start =
		be16_to_cpu(*(__be16 *)(bufptr + HFSP_WRAPOFF_ABLKSTART));

	extent = get_unaligned_be32(bufptr + HFSP_WRAPOFF_EMBEDEXT);
	wd->embed_start = (extent >> 16) & 0xFFFF;
	wd->embed_count = extent & 0xFFFF;

	वापस 1;
पूर्ण

अटल पूर्णांक hfsplus_get_last_session(काष्ठा super_block *sb,
				    sector_t *start, sector_t *size)
अणु
	काष्ठा cdrom_device_info *cdi = disk_to_cdi(sb->s_bdev->bd_disk);

	/* शेष values */
	*start = 0;
	*size = i_size_पढ़ो(sb->s_bdev->bd_inode) >> 9;

	अगर (HFSPLUS_SB(sb)->session >= 0) अणु
		काष्ठा cdrom_tocentry te;

		अगर (!cdi)
			वापस -EINVAL;

		te.cdte_track = HFSPLUS_SB(sb)->session;
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

/* Find the volume header and fill in some minimum bits in superblock */
/* Takes in super block, वापसs true अगर good data पढ़ो */
पूर्णांक hfsplus_पढ़ो_wrapper(काष्ठा super_block *sb)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	काष्ठा hfsplus_wd wd;
	sector_t part_start, part_size;
	u32 blocksize;
	पूर्णांक error = 0;

	error = -EINVAL;
	blocksize = sb_min_blocksize(sb, HFSPLUS_SECTOR_SIZE);
	अगर (!blocksize)
		जाओ out;

	अगर (hfsplus_get_last_session(sb, &part_start, &part_size))
		जाओ out;

	error = -ENOMEM;
	sbi->s_vhdr_buf = kदो_स्मृति(hfsplus_min_io_size(sb), GFP_KERNEL);
	अगर (!sbi->s_vhdr_buf)
		जाओ out;
	sbi->s_backup_vhdr_buf = kदो_स्मृति(hfsplus_min_io_size(sb), GFP_KERNEL);
	अगर (!sbi->s_backup_vhdr_buf)
		जाओ out_मुक्त_vhdr;

reपढ़ो:
	error = hfsplus_submit_bio(sb, part_start + HFSPLUS_VOLHEAD_SECTOR,
				   sbi->s_vhdr_buf, (व्योम **)&sbi->s_vhdr,
				   REQ_OP_READ, 0);
	अगर (error)
		जाओ out_मुक्त_backup_vhdr;

	error = -EINVAL;
	चयन (sbi->s_vhdr->signature) अणु
	हाल cpu_to_be16(HFSPLUS_VOLHEAD_SIGX):
		set_bit(HFSPLUS_SB_HFSX, &sbi->flags);
		fallthrough;
	हाल cpu_to_be16(HFSPLUS_VOLHEAD_SIG):
		अवरोध;
	हाल cpu_to_be16(HFSP_WRAP_MAGIC):
		अगर (!hfsplus_पढ़ो_mdb(sbi->s_vhdr, &wd))
			जाओ out_मुक्त_backup_vhdr;
		wd.ablk_size >>= HFSPLUS_SECTOR_SHIFT;
		part_start += (sector_t)wd.ablk_start +
			       (sector_t)wd.embed_start * wd.ablk_size;
		part_size = (sector_t)wd.embed_count * wd.ablk_size;
		जाओ reपढ़ो;
	शेष:
		/*
		 * Check क्रम a partition block.
		 *
		 * (should करो this only क्रम cdrom/loop though)
		 */
		अगर (hfs_part_find(sb, &part_start, &part_size))
			जाओ out_मुक्त_backup_vhdr;
		जाओ reपढ़ो;
	पूर्ण

	error = hfsplus_submit_bio(sb, part_start + part_size - 2,
				   sbi->s_backup_vhdr_buf,
				   (व्योम **)&sbi->s_backup_vhdr, REQ_OP_READ,
				   0);
	अगर (error)
		जाओ out_मुक्त_backup_vhdr;

	error = -EINVAL;
	अगर (sbi->s_backup_vhdr->signature != sbi->s_vhdr->signature) अणु
		pr_warn("invalid secondary volume header\n");
		जाओ out_मुक्त_backup_vhdr;
	पूर्ण

	blocksize = be32_to_cpu(sbi->s_vhdr->blocksize);

	/*
	 * Block size must be at least as large as a sector and a multiple of 2.
	 */
	अगर (blocksize < HFSPLUS_SECTOR_SIZE || ((blocksize - 1) & blocksize))
		जाओ out_मुक्त_backup_vhdr;
	sbi->alloc_blksz = blocksize;
	sbi->alloc_blksz_shअगरt = ilog2(blocksize);
	blocksize = min_t(u32, sbi->alloc_blksz, PAGE_SIZE);

	/*
	 * Align block size to block offset.
	 */
	जबतक (part_start & ((blocksize >> HFSPLUS_SECTOR_SHIFT) - 1))
		blocksize >>= 1;

	अगर (sb_set_blocksize(sb, blocksize) != blocksize) अणु
		pr_err("unable to set blocksize to %u!\n", blocksize);
		जाओ out_मुक्त_backup_vhdr;
	पूर्ण

	sbi->blockoffset =
		part_start >> (sb->s_blocksize_bits - HFSPLUS_SECTOR_SHIFT);
	sbi->part_start = part_start;
	sbi->sect_count = part_size;
	sbi->fs_shअगरt = sbi->alloc_blksz_shअगरt - sb->s_blocksize_bits;
	वापस 0;

out_मुक्त_backup_vhdr:
	kमुक्त(sbi->s_backup_vhdr_buf);
out_मुक्त_vhdr:
	kमुक्त(sbi->s_vhdr_buf);
out:
	वापस error;
पूर्ण
