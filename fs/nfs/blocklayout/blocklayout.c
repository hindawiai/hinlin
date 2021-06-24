<शैली गुरु>
/*
 *  linux/fs/nfs/blocklayout/blocklayout.c
 *
 *  Module क्रम the NFSv4.1 pNFS block layout driver.
 *
 *  Copyright (c) 2006 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Andy Adamson <andros@citi.umich.edu>
 *  Fred Isaman <iisaman@umich.edu>
 *
 * permission is granted to use, copy, create derivative works and
 * redistribute this software and such derivative works क्रम any purpose,
 * so दीर्घ as the name of the university of michigan is not used in
 * any advertising or खुलाity pertaining to the use or distribution
 * of this software without specअगरic, written prior authorization.  अगर
 * the above copyright notice or any other identअगरication of the
 * university of michigan is included in any copy of any portion of
 * this software, then the disclaimer below must also be included.
 *
 * this software is provided as is, without representation from the
 * university of michigan as to its fitness क्रम any purpose, and without
 * warranty by the university of michigan of any kind, either express
 * or implied, including without limitation the implied warranties of
 * merchantability and fitness क्रम a particular purpose.  the regents
 * of the university of michigan shall not be liable क्रम any damages,
 * including special, indirect, incidental, or consequential damages,
 * with respect to any claim arising out or in connection with the use
 * of the software, even अगर it has been or is hereafter advised of the
 * possibility of such damages.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/bपन.स>		/* काष्ठा bio */
#समावेश <linux/prefetch.h>
#समावेश <linux/pagevec.h>

#समावेश "../pnfs.h"
#समावेश "../nfs4session.h"
#समावेश "../internal.h"
#समावेश "blocklayout.h"

#घोषणा NFSDBG_FACILITY	NFSDBG_PNFS_LD

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andy Adamson <andros@citi.umich.edu>");
MODULE_DESCRIPTION("The NFSv4.1 pNFS Block layout driver");

अटल bool is_hole(काष्ठा pnfs_block_extent *be)
अणु
	चयन (be->be_state) अणु
	हाल PNFS_BLOCK_NONE_DATA:
		वापस true;
	हाल PNFS_BLOCK_INVALID_DATA:
		वापस be->be_tag ? false : true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* The data we are handed might be spपढ़ो across several bios.  We need
 * to track when the last one is finished.
 */
काष्ठा parallel_io अणु
	काष्ठा kref refcnt;
	व्योम (*pnfs_callback) (व्योम *data);
	व्योम *data;
पूर्ण;

अटल अंतरभूत काष्ठा parallel_io *alloc_parallel(व्योम *data)
अणु
	काष्ठा parallel_io *rv;

	rv  = kदो_स्मृति(माप(*rv), GFP_NOFS);
	अगर (rv) अणु
		rv->data = data;
		kref_init(&rv->refcnt);
	पूर्ण
	वापस rv;
पूर्ण

अटल अंतरभूत व्योम get_parallel(काष्ठा parallel_io *p)
अणु
	kref_get(&p->refcnt);
पूर्ण

अटल व्योम destroy_parallel(काष्ठा kref *kref)
अणु
	काष्ठा parallel_io *p = container_of(kref, काष्ठा parallel_io, refcnt);

	dprपूर्णांकk("%s enter\n", __func__);
	p->pnfs_callback(p->data);
	kमुक्त(p);
पूर्ण

अटल अंतरभूत व्योम put_parallel(काष्ठा parallel_io *p)
अणु
	kref_put(&p->refcnt, destroy_parallel);
पूर्ण

अटल काष्ठा bio *
bl_submit_bio(काष्ठा bio *bio)
अणु
	अगर (bio) अणु
		get_parallel(bio->bi_निजी);
		dprपूर्णांकk("%s submitting %s bio %u@%llu\n", __func__,
			bio_op(bio) == READ ? "read" : "write",
			bio->bi_iter.bi_size,
			(अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector);
		submit_bio(bio);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा bio *bl_alloc_init_bio(अचिन्हित पूर्णांक npg,
		काष्ठा block_device *bdev, sector_t disk_sector,
		bio_end_io_t end_io, काष्ठा parallel_io *par)
अणु
	काष्ठा bio *bio;

	npg = bio_max_segs(npg);
	bio = bio_alloc(GFP_NOIO, npg);
	अगर (bio) अणु
		bio->bi_iter.bi_sector = disk_sector;
		bio_set_dev(bio, bdev);
		bio->bi_end_io = end_io;
		bio->bi_निजी = par;
	पूर्ण
	वापस bio;
पूर्ण

अटल bool offset_in_map(u64 offset, काष्ठा pnfs_block_dev_map *map)
अणु
	वापस offset >= map->start && offset < map->start + map->len;
पूर्ण

अटल काष्ठा bio *
करो_add_page_to_bio(काष्ठा bio *bio, पूर्णांक npg, पूर्णांक rw, sector_t isect,
		काष्ठा page *page, काष्ठा pnfs_block_dev_map *map,
		काष्ठा pnfs_block_extent *be, bio_end_io_t end_io,
		काष्ठा parallel_io *par, अचिन्हित पूर्णांक offset, पूर्णांक *len)
अणु
	काष्ठा pnfs_block_dev *dev =
		container_of(be->be_device, काष्ठा pnfs_block_dev, node);
	u64 disk_addr, end;

	dprपूर्णांकk("%s: npg %d rw %d isect %llu offset %u len %d\n", __func__,
		npg, rw, (अचिन्हित दीर्घ दीर्घ)isect, offset, *len);

	/* translate to device offset */
	isect += be->be_v_offset;
	isect -= be->be_f_offset;

	/* translate to physical disk offset */
	disk_addr = (u64)isect << SECTOR_SHIFT;
	अगर (!offset_in_map(disk_addr, map)) अणु
		अगर (!dev->map(dev, disk_addr, map) || !offset_in_map(disk_addr, map))
			वापस ERR_PTR(-EIO);
		bio = bl_submit_bio(bio);
	पूर्ण
	disk_addr += map->disk_offset;
	disk_addr -= map->start;

	/* limit length to what the device mapping allows */
	end = disk_addr + *len;
	अगर (end >= map->start + map->len)
		*len = map->start + map->len - disk_addr;

retry:
	अगर (!bio) अणु
		bio = bl_alloc_init_bio(npg, map->bdev,
				disk_addr >> SECTOR_SHIFT, end_io, par);
		अगर (!bio)
			वापस ERR_PTR(-ENOMEM);
		bio_set_op_attrs(bio, rw, 0);
	पूर्ण
	अगर (bio_add_page(bio, page, *len, offset) < *len) अणु
		bio = bl_submit_bio(bio);
		जाओ retry;
	पूर्ण
	वापस bio;
पूर्ण

अटल व्योम bl_mark_devices_unavailable(काष्ठा nfs_pgio_header *header, bool rw)
अणु
	काष्ठा pnfs_block_layout *bl = BLK_LSEG2EXT(header->lseg);
	माप_प्रकार bytes_left = header->args.count;
	sector_t isect, extent_length = 0;
	काष्ठा pnfs_block_extent be;

	isect = header->args.offset >> SECTOR_SHIFT;
	bytes_left += header->args.offset - (isect << SECTOR_SHIFT);

	जबतक (bytes_left > 0) अणु
		अगर (!ext_tree_lookup(bl, isect, &be, rw))
				वापस;
		extent_length = be.be_length - (isect - be.be_f_offset);
		nfs4_mark_deviceid_unavailable(be.be_device);
		isect += extent_length;
		अगर (bytes_left > extent_length << SECTOR_SHIFT)
			bytes_left -= extent_length << SECTOR_SHIFT;
		अन्यथा
			bytes_left = 0;
	पूर्ण
पूर्ण

अटल व्योम bl_end_io_पढ़ो(काष्ठा bio *bio)
अणु
	काष्ठा parallel_io *par = bio->bi_निजी;

	अगर (bio->bi_status) अणु
		काष्ठा nfs_pgio_header *header = par->data;

		अगर (!header->pnfs_error)
			header->pnfs_error = -EIO;
		pnfs_set_lo_fail(header->lseg);
		bl_mark_devices_unavailable(header, false);
	पूर्ण

	bio_put(bio);
	put_parallel(par);
पूर्ण

अटल व्योम bl_पढ़ो_cleanup(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rpc_task *task;
	काष्ठा nfs_pgio_header *hdr;
	dprपूर्णांकk("%s enter\n", __func__);
	task = container_of(work, काष्ठा rpc_task, u.tk_work);
	hdr = container_of(task, काष्ठा nfs_pgio_header, task);
	pnfs_ld_पढ़ो_करोne(hdr);
पूर्ण

अटल व्योम
bl_end_par_io_पढ़ो(व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	hdr->task.tk_status = hdr->pnfs_error;
	INIT_WORK(&hdr->task.u.tk_work, bl_पढ़ो_cleanup);
	schedule_work(&hdr->task.u.tk_work);
पूर्ण

अटल क्रमागत pnfs_try_status
bl_पढ़ो_pagelist(काष्ठा nfs_pgio_header *header)
अणु
	काष्ठा pnfs_block_layout *bl = BLK_LSEG2EXT(header->lseg);
	काष्ठा pnfs_block_dev_map map = अणु .start = NFS4_MAX_UINT64 पूर्ण;
	काष्ठा bio *bio = शून्य;
	काष्ठा pnfs_block_extent be;
	sector_t isect, extent_length = 0;
	काष्ठा parallel_io *par;
	loff_t f_offset = header->args.offset;
	माप_प्रकार bytes_left = header->args.count;
	अचिन्हित पूर्णांक pg_offset = header->args.pgbase, pg_len;
	काष्ठा page **pages = header->args.pages;
	पूर्णांक pg_index = header->args.pgbase >> PAGE_SHIFT;
	स्थिर bool is_dio = (header->dreq != शून्य);
	काष्ठा blk_plug plug;
	पूर्णांक i;

	dprपूर्णांकk("%s enter nr_pages %u offset %lld count %u\n", __func__,
		header->page_array.npages, f_offset,
		(अचिन्हित पूर्णांक)header->args.count);

	par = alloc_parallel(header);
	अगर (!par)
		वापस PNFS_NOT_ATTEMPTED;
	par->pnfs_callback = bl_end_par_io_पढ़ो;

	blk_start_plug(&plug);

	isect = (sector_t) (f_offset >> SECTOR_SHIFT);
	/* Code assumes extents are page-aligned */
	क्रम (i = pg_index; i < header->page_array.npages; i++) अणु
		अगर (extent_length <= 0) अणु
			/* We've used up the previous extent */
			bio = bl_submit_bio(bio);

			/* Get the next one */
			अगर (!ext_tree_lookup(bl, isect, &be, false)) अणु
				header->pnfs_error = -EIO;
				जाओ out;
			पूर्ण
			extent_length = be.be_length - (isect - be.be_f_offset);
		पूर्ण

		अगर (is_dio) अणु
			अगर (pg_offset + bytes_left > PAGE_SIZE)
				pg_len = PAGE_SIZE - pg_offset;
			अन्यथा
				pg_len = bytes_left;
		पूर्ण अन्यथा अणु
			BUG_ON(pg_offset != 0);
			pg_len = PAGE_SIZE;
		पूर्ण

		अगर (is_hole(&be)) अणु
			bio = bl_submit_bio(bio);
			/* Fill hole w/ zeroes w/o accessing device */
			dprपूर्णांकk("%s Zeroing page for hole\n", __func__);
			zero_user_segment(pages[i], pg_offset, pg_len);

			/* invalidate map */
			map.start = NFS4_MAX_UINT64;
		पूर्ण अन्यथा अणु
			bio = करो_add_page_to_bio(bio,
						 header->page_array.npages - i,
						 READ,
						 isect, pages[i], &map, &be,
						 bl_end_io_पढ़ो, par,
						 pg_offset, &pg_len);
			अगर (IS_ERR(bio)) अणु
				header->pnfs_error = PTR_ERR(bio);
				bio = शून्य;
				जाओ out;
			पूर्ण
		पूर्ण
		isect += (pg_len >> SECTOR_SHIFT);
		extent_length -= (pg_len >> SECTOR_SHIFT);
		f_offset += pg_len;
		bytes_left -= pg_len;
		pg_offset = 0;
	पूर्ण
	अगर ((isect << SECTOR_SHIFT) >= header->inode->i_size) अणु
		header->res.eof = 1;
		header->res.count = header->inode->i_size - header->args.offset;
	पूर्ण अन्यथा अणु
		header->res.count = (isect << SECTOR_SHIFT) - header->args.offset;
	पूर्ण
out:
	bl_submit_bio(bio);
	blk_finish_plug(&plug);
	put_parallel(par);
	वापस PNFS_ATTEMPTED;
पूर्ण

अटल व्योम bl_end_io_ग_लिखो(काष्ठा bio *bio)
अणु
	काष्ठा parallel_io *par = bio->bi_निजी;
	काष्ठा nfs_pgio_header *header = par->data;

	अगर (bio->bi_status) अणु
		अगर (!header->pnfs_error)
			header->pnfs_error = -EIO;
		pnfs_set_lo_fail(header->lseg);
		bl_mark_devices_unavailable(header, true);
	पूर्ण
	bio_put(bio);
	put_parallel(par);
पूर्ण

/* Function scheduled क्रम call during bl_end_par_io_ग_लिखो,
 * it marks sectors as written and extends the commitlist.
 */
अटल व्योम bl_ग_लिखो_cleanup(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rpc_task *task = container_of(work, काष्ठा rpc_task, u.tk_work);
	काष्ठा nfs_pgio_header *hdr =
			container_of(task, काष्ठा nfs_pgio_header, task);

	dprपूर्णांकk("%s enter\n", __func__);

	अगर (likely(!hdr->pnfs_error)) अणु
		काष्ठा pnfs_block_layout *bl = BLK_LSEG2EXT(hdr->lseg);
		u64 start = hdr->args.offset & (loff_t)PAGE_MASK;
		u64 end = (hdr->args.offset + hdr->args.count +
			PAGE_SIZE - 1) & (loff_t)PAGE_MASK;
		u64 lwb = hdr->args.offset + hdr->args.count;

		ext_tree_mark_written(bl, start >> SECTOR_SHIFT,
					(end - start) >> SECTOR_SHIFT, lwb);
	पूर्ण

	pnfs_ld_ग_लिखो_करोne(hdr);
पूर्ण

/* Called when last of bios associated with a bl_ग_लिखो_pagelist call finishes */
अटल व्योम bl_end_par_io_ग_लिखो(व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	hdr->task.tk_status = hdr->pnfs_error;
	hdr->verf.committed = NFS_खाता_SYNC;
	INIT_WORK(&hdr->task.u.tk_work, bl_ग_लिखो_cleanup);
	schedule_work(&hdr->task.u.tk_work);
पूर्ण

अटल क्रमागत pnfs_try_status
bl_ग_लिखो_pagelist(काष्ठा nfs_pgio_header *header, पूर्णांक sync)
अणु
	काष्ठा pnfs_block_layout *bl = BLK_LSEG2EXT(header->lseg);
	काष्ठा pnfs_block_dev_map map = अणु .start = NFS4_MAX_UINT64 पूर्ण;
	काष्ठा bio *bio = शून्य;
	काष्ठा pnfs_block_extent be;
	sector_t isect, extent_length = 0;
	काष्ठा parallel_io *par = शून्य;
	loff_t offset = header->args.offset;
	माप_प्रकार count = header->args.count;
	काष्ठा page **pages = header->args.pages;
	पूर्णांक pg_index = header->args.pgbase >> PAGE_SHIFT;
	अचिन्हित पूर्णांक pg_len;
	काष्ठा blk_plug plug;
	पूर्णांक i;

	dprपूर्णांकk("%s enter, %zu@%lld\n", __func__, count, offset);

	/* At this poपूर्णांक, header->page_aray is a (sequential) list of nfs_pages.
	 * We want to ग_लिखो each, and अगर there is an error set pnfs_error
	 * to have it reकरोne using nfs.
	 */
	par = alloc_parallel(header);
	अगर (!par)
		वापस PNFS_NOT_ATTEMPTED;
	par->pnfs_callback = bl_end_par_io_ग_लिखो;

	blk_start_plug(&plug);

	/* we always ग_लिखो out the whole page */
	offset = offset & (loff_t)PAGE_MASK;
	isect = offset >> SECTOR_SHIFT;

	क्रम (i = pg_index; i < header->page_array.npages; i++) अणु
		अगर (extent_length <= 0) अणु
			/* We've used up the previous extent */
			bio = bl_submit_bio(bio);
			/* Get the next one */
			अगर (!ext_tree_lookup(bl, isect, &be, true)) अणु
				header->pnfs_error = -EINVAL;
				जाओ out;
			पूर्ण

			extent_length = be.be_length - (isect - be.be_f_offset);
		पूर्ण

		pg_len = PAGE_SIZE;
		bio = करो_add_page_to_bio(bio, header->page_array.npages - i,
					 WRITE, isect, pages[i], &map, &be,
					 bl_end_io_ग_लिखो, par,
					 0, &pg_len);
		अगर (IS_ERR(bio)) अणु
			header->pnfs_error = PTR_ERR(bio);
			bio = शून्य;
			जाओ out;
		पूर्ण

		offset += pg_len;
		count -= pg_len;
		isect += (pg_len >> SECTOR_SHIFT);
		extent_length -= (pg_len >> SECTOR_SHIFT);
	पूर्ण

	header->res.count = header->args.count;
out:
	bl_submit_bio(bio);
	blk_finish_plug(&plug);
	put_parallel(par);
	वापस PNFS_ATTEMPTED;
पूर्ण

अटल व्योम bl_मुक्त_layout_hdr(काष्ठा pnfs_layout_hdr *lo)
अणु
	काष्ठा pnfs_block_layout *bl = BLK_LO2EXT(lo);
	पूर्णांक err;

	dprपूर्णांकk("%s enter\n", __func__);

	err = ext_tree_हटाओ(bl, true, 0, Lदीर्घ_उच्च);
	WARN_ON(err);

	kमुक्त_rcu(bl, bl_layout.plh_rcu);
पूर्ण

अटल काष्ठा pnfs_layout_hdr *__bl_alloc_layout_hdr(काष्ठा inode *inode,
		gfp_t gfp_flags, bool is_scsi_layout)
अणु
	काष्ठा pnfs_block_layout *bl;

	dprपूर्णांकk("%s enter\n", __func__);
	bl = kzalloc(माप(*bl), gfp_flags);
	अगर (!bl)
		वापस शून्य;

	bl->bl_ext_rw = RB_ROOT;
	bl->bl_ext_ro = RB_ROOT;
	spin_lock_init(&bl->bl_ext_lock);

	bl->bl_scsi_layout = is_scsi_layout;
	वापस &bl->bl_layout;
पूर्ण

अटल काष्ठा pnfs_layout_hdr *bl_alloc_layout_hdr(काष्ठा inode *inode,
						   gfp_t gfp_flags)
अणु
	वापस __bl_alloc_layout_hdr(inode, gfp_flags, false);
पूर्ण

अटल काष्ठा pnfs_layout_hdr *sl_alloc_layout_hdr(काष्ठा inode *inode,
						   gfp_t gfp_flags)
अणु
	वापस __bl_alloc_layout_hdr(inode, gfp_flags, true);
पूर्ण

अटल व्योम bl_मुक्त_lseg(काष्ठा pnfs_layout_segment *lseg)
अणु
	dprपूर्णांकk("%s enter\n", __func__);
	kमुक्त(lseg);
पूर्ण

/* Tracks info needed to ensure extents in layout obey स्थिरraपूर्णांकs of spec */
काष्ठा layout_verअगरication अणु
	u32 mode;	/* R or RW */
	u64 start;	/* Expected start of next non-COW extent */
	u64 inval;	/* Start of INVAL coverage */
	u64 cowपढ़ो;	/* End of COW पढ़ो coverage */
पूर्ण;

/* Verअगरy the extent meets the layout requirements of the pnfs-block draft,
 * section 2.3.1.
 */
अटल पूर्णांक verअगरy_extent(काष्ठा pnfs_block_extent *be,
			 काष्ठा layout_verअगरication *lv)
अणु
	अगर (lv->mode == IOMODE_READ) अणु
		अगर (be->be_state == PNFS_BLOCK_READWRITE_DATA ||
		    be->be_state == PNFS_BLOCK_INVALID_DATA)
			वापस -EIO;
		अगर (be->be_f_offset != lv->start)
			वापस -EIO;
		lv->start += be->be_length;
		वापस 0;
	पूर्ण
	/* lv->mode == IOMODE_RW */
	अगर (be->be_state == PNFS_BLOCK_READWRITE_DATA) अणु
		अगर (be->be_f_offset != lv->start)
			वापस -EIO;
		अगर (lv->cowपढ़ो > lv->start)
			वापस -EIO;
		lv->start += be->be_length;
		lv->inval = lv->start;
		वापस 0;
	पूर्ण अन्यथा अगर (be->be_state == PNFS_BLOCK_INVALID_DATA) अणु
		अगर (be->be_f_offset != lv->start)
			वापस -EIO;
		lv->start += be->be_length;
		वापस 0;
	पूर्ण अन्यथा अगर (be->be_state == PNFS_BLOCK_READ_DATA) अणु
		अगर (be->be_f_offset > lv->start)
			वापस -EIO;
		अगर (be->be_f_offset < lv->inval)
			वापस -EIO;
		अगर (be->be_f_offset < lv->cowपढ़ो)
			वापस -EIO;
		/* It looks like you might want to min this with lv->start,
		 * but you really करोn't.
		 */
		lv->inval = lv->inval + be->be_length;
		lv->cowपढ़ो = be->be_f_offset + be->be_length;
		वापस 0;
	पूर्ण अन्यथा
		वापस -EIO;
पूर्ण

अटल पूर्णांक decode_sector_number(__be32 **rp, sector_t *sp)
अणु
	uपूर्णांक64_t s;

	*rp = xdr_decode_hyper(*rp, &s);
	अगर (s & 0x1ff) अणु
		prपूर्णांकk(KERN_WARNING "NFS: %s: sector not aligned\n", __func__);
		वापस -1;
	पूर्ण
	*sp = s >> SECTOR_SHIFT;
	वापस 0;
पूर्ण

अटल काष्ठा nfs4_deviceid_node *
bl_find_get_deviceid(काष्ठा nfs_server *server,
		स्थिर काष्ठा nfs4_deviceid *id, स्थिर काष्ठा cred *cred,
		gfp_t gfp_mask)
अणु
	काष्ठा nfs4_deviceid_node *node;
	अचिन्हित दीर्घ start, end;

retry:
	node = nfs4_find_get_deviceid(server, id, cred, gfp_mask);
	अगर (!node)
		वापस ERR_PTR(-ENODEV);

	अगर (test_bit(NFS_DEVICEID_UNAVAILABLE, &node->flags) == 0)
		वापस node;

	end = jअगरfies;
	start = end - PNFS_DEVICE_RETRY_TIMEOUT;
	अगर (!समय_in_range(node->बारtamp_unavailable, start, end)) अणु
		nfs4_delete_deviceid(node->ld, node->nfs_client, id);
		जाओ retry;
	पूर्ण
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल पूर्णांक
bl_alloc_extent(काष्ठा xdr_stream *xdr, काष्ठा pnfs_layout_hdr *lo,
		काष्ठा layout_verअगरication *lv, काष्ठा list_head *extents,
		gfp_t gfp_mask)
अणु
	काष्ठा pnfs_block_extent *be;
	काष्ठा nfs4_deviceid id;
	पूर्णांक error;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 28 + NFS4_DEVICEID4_SIZE);
	अगर (!p)
		वापस -EIO;

	be = kzalloc(माप(*be), GFP_NOFS);
	अगर (!be)
		वापस -ENOMEM;

	स_नकल(&id, p, NFS4_DEVICEID4_SIZE);
	p += XDR_QUADLEN(NFS4_DEVICEID4_SIZE);

	be->be_device = bl_find_get_deviceid(NFS_SERVER(lo->plh_inode), &id,
						lo->plh_lc_cred, gfp_mask);
	अगर (IS_ERR(be->be_device)) अणु
		error = PTR_ERR(be->be_device);
		जाओ out_मुक्त_be;
	पूर्ण

	/*
	 * The next three values are पढ़ो in as bytes, but stored in the
	 * extent काष्ठाure in 512-byte granularity.
	 */
	error = -EIO;
	अगर (decode_sector_number(&p, &be->be_f_offset) < 0)
		जाओ out_put_deviceid;
	अगर (decode_sector_number(&p, &be->be_length) < 0)
		जाओ out_put_deviceid;
	अगर (decode_sector_number(&p, &be->be_v_offset) < 0)
		जाओ out_put_deviceid;
	be->be_state = be32_to_cpup(p++);

	error = verअगरy_extent(be, lv);
	अगर (error) अणु
		dprपूर्णांकk("%s: extent verification failed\n", __func__);
		जाओ out_put_deviceid;
	पूर्ण

	list_add_tail(&be->be_list, extents);
	वापस 0;

out_put_deviceid:
	nfs4_put_deviceid_node(be->be_device);
out_मुक्त_be:
	kमुक्त(be);
	वापस error;
पूर्ण

अटल काष्ठा pnfs_layout_segment *
bl_alloc_lseg(काष्ठा pnfs_layout_hdr *lo, काष्ठा nfs4_layoutget_res *lgr,
		gfp_t gfp_mask)
अणु
	काष्ठा layout_verअगरication lv = अणु
		.mode = lgr->range.iomode,
		.start = lgr->range.offset >> SECTOR_SHIFT,
		.inval = lgr->range.offset >> SECTOR_SHIFT,
		.cowपढ़ो = lgr->range.offset >> SECTOR_SHIFT,
	पूर्ण;
	काष्ठा pnfs_block_layout *bl = BLK_LO2EXT(lo);
	काष्ठा pnfs_layout_segment *lseg;
	काष्ठा xdr_buf buf;
	काष्ठा xdr_stream xdr;
	काष्ठा page *scratch;
	पूर्णांक status, i;
	uपूर्णांक32_t count;
	__be32 *p;
	LIST_HEAD(extents);

	dprपूर्णांकk("---> %s\n", __func__);

	lseg = kzalloc(माप(*lseg), gfp_mask);
	अगर (!lseg)
		वापस ERR_PTR(-ENOMEM);

	status = -ENOMEM;
	scratch = alloc_page(gfp_mask);
	अगर (!scratch)
		जाओ out;

	xdr_init_decode_pages(&xdr, &buf,
			lgr->layoutp->pages, lgr->layoutp->len);
	xdr_set_scratch_page(&xdr, scratch);

	status = -EIO;
	p = xdr_अंतरभूत_decode(&xdr, 4);
	अगर (unlikely(!p))
		जाओ out_मुक्त_scratch;

	count = be32_to_cpup(p++);
	dprपूर्णांकk("%s: number of extents %d\n", __func__, count);

	/*
	 * Decode inभागidual extents, putting them in temporary staging area
	 * until whole layout is decoded to make error recovery easier.
	 */
	क्रम (i = 0; i < count; i++) अणु
		status = bl_alloc_extent(&xdr, lo, &lv, &extents, gfp_mask);
		अगर (status)
			जाओ process_extents;
	पूर्ण

	अगर (lgr->range.offset + lgr->range.length !=
			lv.start << SECTOR_SHIFT) अणु
		dprपूर्णांकk("%s Final length mismatch\n", __func__);
		status = -EIO;
		जाओ process_extents;
	पूर्ण

	अगर (lv.start < lv.cowपढ़ो) अणु
		dprपूर्णांकk("%s Final uncovered COW extent\n", __func__);
		status = -EIO;
	पूर्ण

process_extents:
	जबतक (!list_empty(&extents)) अणु
		काष्ठा pnfs_block_extent *be =
			list_first_entry(&extents, काष्ठा pnfs_block_extent,
					 be_list);
		list_del(&be->be_list);

		अगर (!status)
			status = ext_tree_insert(bl, be);

		अगर (status) अणु
			nfs4_put_deviceid_node(be->be_device);
			kमुक्त(be);
		पूर्ण
	पूर्ण

out_मुक्त_scratch:
	__मुक्त_page(scratch);
out:
	dprपूर्णांकk("%s returns %d\n", __func__, status);
	चयन (status) अणु
	हाल -ENODEV:
		/* Our extent block devices are unavailable */
		set_bit(NFS_LSEG_UNAVAILABLE, &lseg->pls_flags);
		fallthrough;
	हाल 0:
		वापस lseg;
	शेष:
		kमुक्त(lseg);
		वापस ERR_PTR(status);
	पूर्ण
पूर्ण

अटल व्योम
bl_वापस_range(काष्ठा pnfs_layout_hdr *lo,
		काष्ठा pnfs_layout_range *range)
अणु
	काष्ठा pnfs_block_layout *bl = BLK_LO2EXT(lo);
	sector_t offset = range->offset >> SECTOR_SHIFT, end;

	अगर (range->offset % 8) अणु
		dprपूर्णांकk("%s: offset %lld not block size aligned\n",
			__func__, range->offset);
		वापस;
	पूर्ण

	अगर (range->length != NFS4_MAX_UINT64) अणु
		अगर (range->length % 8) अणु
			dprपूर्णांकk("%s: length %lld not block size aligned\n",
				__func__, range->length);
			वापस;
		पूर्ण

		end = offset + (range->length >> SECTOR_SHIFT);
	पूर्ण अन्यथा अणु
		end = round_करोwn(NFS4_MAX_UINT64, PAGE_SIZE);
	पूर्ण

	ext_tree_हटाओ(bl, range->iomode & IOMODE_RW, offset, end);
पूर्ण

अटल पूर्णांक
bl_prepare_layoutcommit(काष्ठा nfs4_layoutcommit_args *arg)
अणु
	वापस ext_tree_prepare_commit(arg);
पूर्ण

अटल व्योम
bl_cleanup_layoutcommit(काष्ठा nfs4_layoutcommit_data *lcdata)
अणु
	ext_tree_mark_committed(&lcdata->args, lcdata->res.status);
पूर्ण

अटल पूर्णांक
bl_set_layoutdriver(काष्ठा nfs_server *server, स्थिर काष्ठा nfs_fh *fh)
अणु
	dprपूर्णांकk("%s enter\n", __func__);

	अगर (server->pnfs_blksize == 0) अणु
		dprपूर्णांकk("%s Server did not return blksize\n", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (server->pnfs_blksize > PAGE_SIZE) अणु
		prपूर्णांकk(KERN_ERR "%s: pNFS blksize %d not supported.\n",
			__func__, server->pnfs_blksize);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
is_aligned_req(काष्ठा nfs_pageio_descriptor *pgio,
		काष्ठा nfs_page *req, अचिन्हित पूर्णांक alignment, bool is_ग_लिखो)
अणु
	/*
	 * Always accept buffered ग_लिखोs, higher layers take care of the
	 * right alignment.
	 */
	अगर (pgio->pg_dreq == शून्य)
		वापस true;

	अगर (!IS_ALIGNED(req->wb_offset, alignment))
		वापस false;

	अगर (IS_ALIGNED(req->wb_bytes, alignment))
		वापस true;

	अगर (is_ग_लिखो &&
	    (req_offset(req) + req->wb_bytes == i_size_पढ़ो(pgio->pg_inode))) अणु
		/*
		 * If the ग_लिखो goes up to the inode size, just ग_लिखो
		 * the full page.  Data past the inode size is
		 * guaranteed to be zeroed by the higher level client
		 * code, and this behaviour is mandated by RFC 5663
		 * section 2.3.2.
		 */
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम
bl_pg_init_पढ़ो(काष्ठा nfs_pageio_descriptor *pgio, काष्ठा nfs_page *req)
अणु
	अगर (!is_aligned_req(pgio, req, SECTOR_SIZE, false)) अणु
		nfs_pageio_reset_पढ़ो_mds(pgio);
		वापस;
	पूर्ण

	pnfs_generic_pg_init_पढ़ो(pgio, req);

	अगर (pgio->pg_lseg &&
		test_bit(NFS_LSEG_UNAVAILABLE, &pgio->pg_lseg->pls_flags)) अणु
		pnfs_error_mark_layout_क्रम_वापस(pgio->pg_inode, pgio->pg_lseg);
		pnfs_set_lo_fail(pgio->pg_lseg);
		nfs_pageio_reset_पढ़ो_mds(pgio);
	पूर्ण
पूर्ण

/*
 * Return 0 अगर @req cannot be coalesced पूर्णांकo @pgio, otherwise वापस the number
 * of bytes (maximum @req->wb_bytes) that can be coalesced.
 */
अटल माप_प्रकार
bl_pg_test_पढ़ो(काष्ठा nfs_pageio_descriptor *pgio, काष्ठा nfs_page *prev,
		काष्ठा nfs_page *req)
अणु
	अगर (!is_aligned_req(pgio, req, SECTOR_SIZE, false))
		वापस 0;
	वापस pnfs_generic_pg_test(pgio, prev, req);
पूर्ण

/*
 * Return the number of contiguous bytes क्रम a given inode
 * starting at page frame idx.
 */
अटल u64 pnfs_num_cont_bytes(काष्ठा inode *inode, pgoff_t idx)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	pgoff_t end;

	/* Optimize common हाल that ग_लिखोs from 0 to end of file */
	end = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);
	अगर (end != inode->i_mapping->nrpages) अणु
		rcu_पढ़ो_lock();
		end = page_cache_next_miss(mapping, idx + 1, अच_दीर्घ_उच्च);
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (!end)
		वापस i_size_पढ़ो(inode) - (idx << PAGE_SHIFT);
	अन्यथा
		वापस (end - idx) << PAGE_SHIFT;
पूर्ण

अटल व्योम
bl_pg_init_ग_लिखो(काष्ठा nfs_pageio_descriptor *pgio, काष्ठा nfs_page *req)
अणु
	u64 wb_size;

	अगर (!is_aligned_req(pgio, req, PAGE_SIZE, true)) अणु
		nfs_pageio_reset_ग_लिखो_mds(pgio);
		वापस;
	पूर्ण

	अगर (pgio->pg_dreq == शून्य)
		wb_size = pnfs_num_cont_bytes(pgio->pg_inode,
					      req->wb_index);
	अन्यथा
		wb_size = nfs_dreq_bytes_left(pgio->pg_dreq);

	pnfs_generic_pg_init_ग_लिखो(pgio, req, wb_size);

	अगर (pgio->pg_lseg &&
		test_bit(NFS_LSEG_UNAVAILABLE, &pgio->pg_lseg->pls_flags)) अणु

		pnfs_error_mark_layout_क्रम_वापस(pgio->pg_inode, pgio->pg_lseg);
		pnfs_set_lo_fail(pgio->pg_lseg);
		nfs_pageio_reset_ग_लिखो_mds(pgio);
	पूर्ण
पूर्ण

/*
 * Return 0 अगर @req cannot be coalesced पूर्णांकo @pgio, otherwise वापस the number
 * of bytes (maximum @req->wb_bytes) that can be coalesced.
 */
अटल माप_प्रकार
bl_pg_test_ग_लिखो(काष्ठा nfs_pageio_descriptor *pgio, काष्ठा nfs_page *prev,
		 काष्ठा nfs_page *req)
अणु
	अगर (!is_aligned_req(pgio, req, PAGE_SIZE, true))
		वापस 0;
	वापस pnfs_generic_pg_test(pgio, prev, req);
पूर्ण

अटल स्थिर काष्ठा nfs_pageio_ops bl_pg_पढ़ो_ops = अणु
	.pg_init = bl_pg_init_पढ़ो,
	.pg_test = bl_pg_test_पढ़ो,
	.pg_करोio = pnfs_generic_pg_पढ़ोpages,
	.pg_cleanup = pnfs_generic_pg_cleanup,
पूर्ण;

अटल स्थिर काष्ठा nfs_pageio_ops bl_pg_ग_लिखो_ops = अणु
	.pg_init = bl_pg_init_ग_लिखो,
	.pg_test = bl_pg_test_ग_लिखो,
	.pg_करोio = pnfs_generic_pg_ग_लिखोpages,
	.pg_cleanup = pnfs_generic_pg_cleanup,
पूर्ण;

अटल काष्ठा pnfs_layoutdriver_type blocklayout_type = अणु
	.id				= LAYOUT_BLOCK_VOLUME,
	.name				= "LAYOUT_BLOCK_VOLUME",
	.owner				= THIS_MODULE,
	.flags				= PNFS_LAYOUTRET_ON_SETATTR |
					  PNFS_LAYOUTRET_ON_ERROR |
					  PNFS_READ_WHOLE_PAGE,
	.पढ़ो_pagelist			= bl_पढ़ो_pagelist,
	.ग_लिखो_pagelist			= bl_ग_लिखो_pagelist,
	.alloc_layout_hdr		= bl_alloc_layout_hdr,
	.मुक्त_layout_hdr		= bl_मुक्त_layout_hdr,
	.alloc_lseg			= bl_alloc_lseg,
	.मुक्त_lseg			= bl_मुक्त_lseg,
	.वापस_range			= bl_वापस_range,
	.prepare_layoutcommit		= bl_prepare_layoutcommit,
	.cleanup_layoutcommit		= bl_cleanup_layoutcommit,
	.set_layoutdriver		= bl_set_layoutdriver,
	.alloc_deviceid_node		= bl_alloc_deviceid_node,
	.मुक्त_deviceid_node		= bl_मुक्त_deviceid_node,
	.pg_पढ़ो_ops			= &bl_pg_पढ़ो_ops,
	.pg_ग_लिखो_ops			= &bl_pg_ग_लिखो_ops,
	.sync				= pnfs_generic_sync,
पूर्ण;

अटल काष्ठा pnfs_layoutdriver_type scsilayout_type = अणु
	.id				= LAYOUT_SCSI,
	.name				= "LAYOUT_SCSI",
	.owner				= THIS_MODULE,
	.flags				= PNFS_LAYOUTRET_ON_SETATTR |
					  PNFS_LAYOUTRET_ON_ERROR |
					  PNFS_READ_WHOLE_PAGE,
	.पढ़ो_pagelist			= bl_पढ़ो_pagelist,
	.ग_लिखो_pagelist			= bl_ग_लिखो_pagelist,
	.alloc_layout_hdr		= sl_alloc_layout_hdr,
	.मुक्त_layout_hdr		= bl_मुक्त_layout_hdr,
	.alloc_lseg			= bl_alloc_lseg,
	.मुक्त_lseg			= bl_मुक्त_lseg,
	.वापस_range			= bl_वापस_range,
	.prepare_layoutcommit		= bl_prepare_layoutcommit,
	.cleanup_layoutcommit		= bl_cleanup_layoutcommit,
	.set_layoutdriver		= bl_set_layoutdriver,
	.alloc_deviceid_node		= bl_alloc_deviceid_node,
	.मुक्त_deviceid_node		= bl_मुक्त_deviceid_node,
	.pg_पढ़ो_ops			= &bl_pg_पढ़ो_ops,
	.pg_ग_लिखो_ops			= &bl_pg_ग_लिखो_ops,
	.sync				= pnfs_generic_sync,
पूर्ण;


अटल पूर्णांक __init nfs4blocklayout_init(व्योम)
अणु
	पूर्णांक ret;

	dprपूर्णांकk("%s: NFSv4 Block Layout Driver Registering...\n", __func__);

	ret = bl_init_pipefs();
	अगर (ret)
		जाओ out;

	ret = pnfs_रेजिस्टर_layoutdriver(&blocklayout_type);
	अगर (ret)
		जाओ out_cleanup_pipe;

	ret = pnfs_रेजिस्टर_layoutdriver(&scsilayout_type);
	अगर (ret)
		जाओ out_unरेजिस्टर_block;
	वापस 0;

out_unरेजिस्टर_block:
	pnfs_unरेजिस्टर_layoutdriver(&blocklayout_type);
out_cleanup_pipe:
	bl_cleanup_pipefs();
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास nfs4blocklayout_निकास(व्योम)
अणु
	dprपूर्णांकk("%s: NFSv4 Block Layout Driver Unregistering...\n",
	       __func__);

	pnfs_unरेजिस्टर_layoutdriver(&scsilayout_type);
	pnfs_unरेजिस्टर_layoutdriver(&blocklayout_type);
	bl_cleanup_pipefs();
पूर्ण

MODULE_ALIAS("nfs-layouttype4-3");
MODULE_ALIAS("nfs-layouttype4-5");

module_init(nfs4blocklayout_init);
module_निकास(nfs4blocklayout_निकास);
