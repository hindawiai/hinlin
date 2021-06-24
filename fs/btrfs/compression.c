<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2008 Oracle.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/bपन.स>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/backing-dev.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/log2.h>
#समावेश <crypto/hash.h>
#समावेश "misc.h"
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "btrfs_inode.h"
#समावेश "volumes.h"
#समावेश "ordered-data.h"
#समावेश "compression.h"
#समावेश "extent_io.h"
#समावेश "extent_map.h"
#समावेश "zoned.h"

अटल स्थिर अक्षर* स्थिर btrfs_compress_types[] = अणु "", "zlib", "lzo", "zstd" पूर्ण;

स्थिर अक्षर* btrfs_compress_type2str(क्रमागत btrfs_compression_type type)
अणु
	चयन (type) अणु
	हाल BTRFS_COMPRESS_ZLIB:
	हाल BTRFS_COMPRESS_LZO:
	हाल BTRFS_COMPRESS_ZSTD:
	हाल BTRFS_COMPRESS_NONE:
		वापस btrfs_compress_types[type];
	शेष:
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

bool btrfs_compress_is_valid_type(स्थिर अक्षर *str, माप_प्रकार len)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < ARRAY_SIZE(btrfs_compress_types); i++) अणु
		माप_प्रकार comp_len = म_माप(btrfs_compress_types[i]);

		अगर (len < comp_len)
			जारी;

		अगर (!म_भेदन(btrfs_compress_types[i], str, comp_len))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक compression_compress_pages(पूर्णांक type, काष्ठा list_head *ws,
               काष्ठा address_space *mapping, u64 start, काष्ठा page **pages,
               अचिन्हित दीर्घ *out_pages, अचिन्हित दीर्घ *total_in,
               अचिन्हित दीर्घ *total_out)
अणु
	चयन (type) अणु
	हाल BTRFS_COMPRESS_ZLIB:
		वापस zlib_compress_pages(ws, mapping, start, pages,
				out_pages, total_in, total_out);
	हाल BTRFS_COMPRESS_LZO:
		वापस lzo_compress_pages(ws, mapping, start, pages,
				out_pages, total_in, total_out);
	हाल BTRFS_COMPRESS_ZSTD:
		वापस zstd_compress_pages(ws, mapping, start, pages,
				out_pages, total_in, total_out);
	हाल BTRFS_COMPRESS_NONE:
	शेष:
		/*
		 * This can happen when compression races with remount setting
		 * it to 'no compress', while caller doesn't call
		 * inode_need_compress() to check अगर we really need to
		 * compress.
		 *
		 * Not a big deal, just need to inक्रमm caller that we
		 * haven't allocated any pages yet.
		 */
		*out_pages = 0;
		वापस -E2BIG;
	पूर्ण
पूर्ण

अटल पूर्णांक compression_decompress_bio(पूर्णांक type, काष्ठा list_head *ws,
		काष्ठा compressed_bio *cb)
अणु
	चयन (type) अणु
	हाल BTRFS_COMPRESS_ZLIB: वापस zlib_decompress_bio(ws, cb);
	हाल BTRFS_COMPRESS_LZO:  वापस lzo_decompress_bio(ws, cb);
	हाल BTRFS_COMPRESS_ZSTD: वापस zstd_decompress_bio(ws, cb);
	हाल BTRFS_COMPRESS_NONE:
	शेष:
		/*
		 * This can't happen, the type is validated several बार
		 * beक्रमe we get here.
		 */
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक compression_decompress(पूर्णांक type, काष्ठा list_head *ws,
               अचिन्हित अक्षर *data_in, काष्ठा page *dest_page,
               अचिन्हित दीर्घ start_byte, माप_प्रकार srclen, माप_प्रकार destlen)
अणु
	चयन (type) अणु
	हाल BTRFS_COMPRESS_ZLIB: वापस zlib_decompress(ws, data_in, dest_page,
						start_byte, srclen, destlen);
	हाल BTRFS_COMPRESS_LZO:  वापस lzo_decompress(ws, data_in, dest_page,
						start_byte, srclen, destlen);
	हाल BTRFS_COMPRESS_ZSTD: वापस zstd_decompress(ws, data_in, dest_page,
						start_byte, srclen, destlen);
	हाल BTRFS_COMPRESS_NONE:
	शेष:
		/*
		 * This can't happen, the type is validated several बार
		 * beक्रमe we get here.
		 */
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक btrfs_decompress_bio(काष्ठा compressed_bio *cb);

अटल अंतरभूत पूर्णांक compressed_bio_size(काष्ठा btrfs_fs_info *fs_info,
				      अचिन्हित दीर्घ disk_size)
अणु
	वापस माप(काष्ठा compressed_bio) +
		(DIV_ROUND_UP(disk_size, fs_info->sectorsize)) * fs_info->csum_size;
पूर्ण

अटल पूर्णांक check_compressed_csum(काष्ठा btrfs_inode *inode, काष्ठा bio *bio,
				 u64 disk_start)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	SHASH_DESC_ON_STACK(shash, fs_info->csum_shash);
	स्थिर u32 csum_size = fs_info->csum_size;
	स्थिर u32 sectorsize = fs_info->sectorsize;
	काष्ठा page *page;
	अचिन्हित दीर्घ i;
	अक्षर *kaddr;
	u8 csum[BTRFS_CSUM_SIZE];
	काष्ठा compressed_bio *cb = bio->bi_निजी;
	u8 *cb_sum = cb->sums;

	अगर (!fs_info->csum_root || (inode->flags & BTRFS_INODE_NODATASUM))
		वापस 0;

	shash->tfm = fs_info->csum_shash;

	क्रम (i = 0; i < cb->nr_pages; i++) अणु
		u32 pg_offset;
		u32 bytes_left = PAGE_SIZE;
		page = cb->compressed_pages[i];

		/* Determine the reमुख्यing bytes inside the page first */
		अगर (i == cb->nr_pages - 1)
			bytes_left = cb->compressed_len - i * PAGE_SIZE;

		/* Hash through the page sector by sector */
		क्रम (pg_offset = 0; pg_offset < bytes_left;
		     pg_offset += sectorsize) अणु
			kaddr = kmap_atomic(page);
			crypto_shash_digest(shash, kaddr + pg_offset,
					    sectorsize, csum);
			kunmap_atomic(kaddr);

			अगर (स_भेद(&csum, cb_sum, csum_size) != 0) अणु
				btrfs_prपूर्णांक_data_csum_error(inode, disk_start,
						csum, cb_sum, cb->mirror_num);
				अगर (btrfs_io_bio(bio)->device)
					btrfs_dev_stat_inc_and_prपूर्णांक(
						btrfs_io_bio(bio)->device,
						BTRFS_DEV_STAT_CORRUPTION_ERRS);
				वापस -EIO;
			पूर्ण
			cb_sum += csum_size;
			disk_start += sectorsize;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* when we finish पढ़ोing compressed pages from the disk, we
 * decompress them and then run the bio end_io routines on the
 * decompressed pages (in the inode address space).
 *
 * This allows the checksumming and other IO error handling routines
 * to work normally
 *
 * The compressed pages are मुक्तd here, and it must be run
 * in process context
 */
अटल व्योम end_compressed_bio_पढ़ो(काष्ठा bio *bio)
अणु
	काष्ठा compressed_bio *cb = bio->bi_निजी;
	काष्ठा inode *inode;
	काष्ठा page *page;
	अचिन्हित दीर्घ index;
	अचिन्हित पूर्णांक mirror = btrfs_io_bio(bio)->mirror_num;
	पूर्णांक ret = 0;

	अगर (bio->bi_status)
		cb->errors = 1;

	/* अगर there are more bios still pending क्रम this compressed
	 * extent, just निकास
	 */
	अगर (!refcount_dec_and_test(&cb->pending_bios))
		जाओ out;

	/*
	 * Record the correct mirror_num in cb->orig_bio so that
	 * पढ़ो-repair can work properly.
	 */
	btrfs_io_bio(cb->orig_bio)->mirror_num = mirror;
	cb->mirror_num = mirror;

	/*
	 * Some IO in this cb have failed, just skip checksum as there
	 * is no way it could be correct.
	 */
	अगर (cb->errors == 1)
		जाओ csum_failed;

	inode = cb->inode;
	ret = check_compressed_csum(BTRFS_I(inode), bio,
				    bio->bi_iter.bi_sector << 9);
	अगर (ret)
		जाओ csum_failed;

	/* ok, we're the last bio क्रम this extent, lets start
	 * the decompression.
	 */
	ret = btrfs_decompress_bio(cb);

csum_failed:
	अगर (ret)
		cb->errors = 1;

	/* release the compressed pages */
	index = 0;
	क्रम (index = 0; index < cb->nr_pages; index++) अणु
		page = cb->compressed_pages[index];
		page->mapping = शून्य;
		put_page(page);
	पूर्ण

	/* करो io completion on the original bio */
	अगर (cb->errors) अणु
		bio_io_error(cb->orig_bio);
	पूर्ण अन्यथा अणु
		काष्ठा bio_vec *bvec;
		काष्ठा bvec_iter_all iter_all;

		/*
		 * we have verअगरied the checksum alपढ़ोy, set page
		 * checked so the end_io handlers know about it
		 */
		ASSERT(!bio_flagged(bio, BIO_CLONED));
		bio_क्रम_each_segment_all(bvec, cb->orig_bio, iter_all)
			SetPageChecked(bvec->bv_page);

		bio_endio(cb->orig_bio);
	पूर्ण

	/* finally मुक्त the cb काष्ठा */
	kमुक्त(cb->compressed_pages);
	kमुक्त(cb);
out:
	bio_put(bio);
पूर्ण

/*
 * Clear the ग_लिखोback bits on all of the file
 * pages क्रम a compressed ग_लिखो
 */
अटल noअंतरभूत व्योम end_compressed_ग_लिखोback(काष्ठा inode *inode,
					      स्थिर काष्ठा compressed_bio *cb)
अणु
	अचिन्हित दीर्घ index = cb->start >> PAGE_SHIFT;
	अचिन्हित दीर्घ end_index = (cb->start + cb->len - 1) >> PAGE_SHIFT;
	काष्ठा page *pages[16];
	अचिन्हित दीर्घ nr_pages = end_index - index + 1;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (cb->errors)
		mapping_set_error(inode->i_mapping, -EIO);

	जबतक (nr_pages > 0) अणु
		ret = find_get_pages_contig(inode->i_mapping, index,
				     min_t(अचिन्हित दीर्घ,
				     nr_pages, ARRAY_SIZE(pages)), pages);
		अगर (ret == 0) अणु
			nr_pages -= 1;
			index += 1;
			जारी;
		पूर्ण
		क्रम (i = 0; i < ret; i++) अणु
			अगर (cb->errors)
				SetPageError(pages[i]);
			end_page_ग_लिखोback(pages[i]);
			put_page(pages[i]);
		पूर्ण
		nr_pages -= ret;
		index += ret;
	पूर्ण
	/* the inode may be gone now */
पूर्ण

/*
 * करो the cleanup once all the compressed pages hit the disk.
 * This will clear ग_लिखोback on the file pages and मुक्त the compressed
 * pages.
 *
 * This also calls the ग_लिखोback end hooks क्रम the file pages so that
 * metadata and checksums can be updated in the file.
 */
अटल व्योम end_compressed_bio_ग_लिखो(काष्ठा bio *bio)
अणु
	काष्ठा compressed_bio *cb = bio->bi_निजी;
	काष्ठा inode *inode;
	काष्ठा page *page;
	अचिन्हित दीर्घ index;

	अगर (bio->bi_status)
		cb->errors = 1;

	/* अगर there are more bios still pending क्रम this compressed
	 * extent, just निकास
	 */
	अगर (!refcount_dec_and_test(&cb->pending_bios))
		जाओ out;

	/* ok, we're the last bio क्रम this extent, step one is to
	 * call back पूर्णांकo the FS and करो all the end_io operations
	 */
	inode = cb->inode;
	cb->compressed_pages[0]->mapping = cb->inode->i_mapping;
	btrfs_record_physical_zoned(inode, cb->start, bio);
	btrfs_ग_लिखोpage_endio_finish_ordered(cb->compressed_pages[0],
			cb->start, cb->start + cb->len - 1,
			bio->bi_status == BLK_STS_OK);
	cb->compressed_pages[0]->mapping = शून्य;

	end_compressed_ग_लिखोback(inode, cb);
	/* note, our inode could be gone now */

	/*
	 * release the compressed pages, these came from alloc_page and
	 * are not attached to the inode at all
	 */
	index = 0;
	क्रम (index = 0; index < cb->nr_pages; index++) अणु
		page = cb->compressed_pages[index];
		page->mapping = शून्य;
		put_page(page);
	पूर्ण

	/* finally मुक्त the cb काष्ठा */
	kमुक्त(cb->compressed_pages);
	kमुक्त(cb);
out:
	bio_put(bio);
पूर्ण

/*
 * worker function to build and submit bios क्रम previously compressed pages.
 * The corresponding pages in the inode should be marked क्रम ग_लिखोback
 * and the compressed pages should have a reference on them क्रम dropping
 * when the IO is complete.
 *
 * This also checksums the file bytes and माला_लो things पढ़ोy क्रम
 * the end io hooks.
 */
blk_status_t btrfs_submit_compressed_ग_लिखो(काष्ठा btrfs_inode *inode, u64 start,
				 अचिन्हित दीर्घ len, u64 disk_start,
				 अचिन्हित दीर्घ compressed_len,
				 काष्ठा page **compressed_pages,
				 अचिन्हित दीर्घ nr_pages,
				 अचिन्हित पूर्णांक ग_लिखो_flags,
				 काष्ठा cgroup_subsys_state *blkcg_css)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा bio *bio = शून्य;
	काष्ठा compressed_bio *cb;
	अचिन्हित दीर्घ bytes_left;
	पूर्णांक pg_index = 0;
	काष्ठा page *page;
	u64 first_byte = disk_start;
	blk_status_t ret;
	पूर्णांक skip_sum = inode->flags & BTRFS_INODE_NODATASUM;
	स्थिर bool use_append = btrfs_use_zone_append(inode, disk_start);
	स्थिर अचिन्हित पूर्णांक bio_op = use_append ? REQ_OP_ZONE_APPEND : REQ_OP_WRITE;

	WARN_ON(!PAGE_ALIGNED(start));
	cb = kदो_स्मृति(compressed_bio_size(fs_info, compressed_len), GFP_NOFS);
	अगर (!cb)
		वापस BLK_STS_RESOURCE;
	refcount_set(&cb->pending_bios, 0);
	cb->errors = 0;
	cb->inode = &inode->vfs_inode;
	cb->start = start;
	cb->len = len;
	cb->mirror_num = 0;
	cb->compressed_pages = compressed_pages;
	cb->compressed_len = compressed_len;
	cb->orig_bio = शून्य;
	cb->nr_pages = nr_pages;

	bio = btrfs_bio_alloc(first_byte);
	bio->bi_opf = bio_op | ग_लिखो_flags;
	bio->bi_निजी = cb;
	bio->bi_end_io = end_compressed_bio_ग_लिखो;

	अगर (use_append) अणु
		काष्ठा extent_map *em;
		काष्ठा map_lookup *map;
		काष्ठा block_device *bdev;

		em = btrfs_get_chunk_map(fs_info, disk_start, PAGE_SIZE);
		अगर (IS_ERR(em)) अणु
			kमुक्त(cb);
			bio_put(bio);
			वापस BLK_STS_NOTSUPP;
		पूर्ण

		map = em->map_lookup;
		/* We only support single profile क्रम now */
		ASSERT(map->num_stripes == 1);
		bdev = map->stripes[0].dev->bdev;

		bio_set_dev(bio, bdev);
		मुक्त_extent_map(em);
	पूर्ण

	अगर (blkcg_css) अणु
		bio->bi_opf |= REQ_CGROUP_PUNT;
		kthपढ़ो_associate_blkcg(blkcg_css);
	पूर्ण
	refcount_set(&cb->pending_bios, 1);

	/* create and submit bios क्रम the compressed pages */
	bytes_left = compressed_len;
	क्रम (pg_index = 0; pg_index < cb->nr_pages; pg_index++) अणु
		पूर्णांक submit = 0;
		पूर्णांक len = 0;

		page = compressed_pages[pg_index];
		page->mapping = inode->vfs_inode.i_mapping;
		अगर (bio->bi_iter.bi_size)
			submit = btrfs_bio_fits_in_stripe(page, PAGE_SIZE, bio,
							  0);

		/*
		 * Page can only be added to bio अगर the current bio fits in
		 * stripe.
		 */
		अगर (!submit) अणु
			अगर (pg_index == 0 && use_append)
				len = bio_add_zone_append_page(bio, page,
							       PAGE_SIZE, 0);
			अन्यथा
				len = bio_add_page(bio, page, PAGE_SIZE, 0);
		पूर्ण

		page->mapping = शून्य;
		अगर (submit || len < PAGE_SIZE) अणु
			/*
			 * inc the count beक्रमe we submit the bio so
			 * we know the end IO handler won't happen beक्रमe
			 * we inc the count.  Otherwise, the cb might get
			 * मुक्तd beक्रमe we're करोne setting it up
			 */
			refcount_inc(&cb->pending_bios);
			ret = btrfs_bio_wq_end_io(fs_info, bio,
						  BTRFS_WQ_ENDIO_DATA);
			BUG_ON(ret); /* -ENOMEM */

			अगर (!skip_sum) अणु
				ret = btrfs_csum_one_bio(inode, bio, start, 1);
				BUG_ON(ret); /* -ENOMEM */
			पूर्ण

			ret = btrfs_map_bio(fs_info, bio, 0);
			अगर (ret) अणु
				bio->bi_status = ret;
				bio_endio(bio);
			पूर्ण

			bio = btrfs_bio_alloc(first_byte);
			bio->bi_opf = bio_op | ग_लिखो_flags;
			bio->bi_निजी = cb;
			bio->bi_end_io = end_compressed_bio_ग_लिखो;
			अगर (blkcg_css)
				bio->bi_opf |= REQ_CGROUP_PUNT;
			/*
			 * Use bio_add_page() to ensure the bio has at least one
			 * page.
			 */
			bio_add_page(bio, page, PAGE_SIZE, 0);
		पूर्ण
		अगर (bytes_left < PAGE_SIZE) अणु
			btrfs_info(fs_info,
					"bytes left %lu compress len %lu nr %lu",
			       bytes_left, cb->compressed_len, cb->nr_pages);
		पूर्ण
		bytes_left -= PAGE_SIZE;
		first_byte += PAGE_SIZE;
		cond_resched();
	पूर्ण

	ret = btrfs_bio_wq_end_io(fs_info, bio, BTRFS_WQ_ENDIO_DATA);
	BUG_ON(ret); /* -ENOMEM */

	अगर (!skip_sum) अणु
		ret = btrfs_csum_one_bio(inode, bio, start, 1);
		BUG_ON(ret); /* -ENOMEM */
	पूर्ण

	ret = btrfs_map_bio(fs_info, bio, 0);
	अगर (ret) अणु
		bio->bi_status = ret;
		bio_endio(bio);
	पूर्ण

	अगर (blkcg_css)
		kthपढ़ो_associate_blkcg(शून्य);

	वापस 0;
पूर्ण

अटल u64 bio_end_offset(काष्ठा bio *bio)
अणु
	काष्ठा bio_vec *last = bio_last_bvec_all(bio);

	वापस page_offset(last->bv_page) + last->bv_len + last->bv_offset;
पूर्ण

अटल noअंतरभूत पूर्णांक add_ra_bio_pages(काष्ठा inode *inode,
				     u64 compressed_end,
				     काष्ठा compressed_bio *cb)
अणु
	अचिन्हित दीर्घ end_index;
	अचिन्हित दीर्घ pg_index;
	u64 last_offset;
	u64 isize = i_size_पढ़ो(inode);
	पूर्णांक ret;
	काष्ठा page *page;
	अचिन्हित दीर्घ nr_pages = 0;
	काष्ठा extent_map *em;
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा extent_map_tree *em_tree;
	काष्ठा extent_io_tree *tree;
	u64 end;
	पूर्णांक misses = 0;

	last_offset = bio_end_offset(cb->orig_bio);
	em_tree = &BTRFS_I(inode)->extent_tree;
	tree = &BTRFS_I(inode)->io_tree;

	अगर (isize == 0)
		वापस 0;

	end_index = (i_size_पढ़ो(inode) - 1) >> PAGE_SHIFT;

	जबतक (last_offset < compressed_end) अणु
		pg_index = last_offset >> PAGE_SHIFT;

		अगर (pg_index > end_index)
			अवरोध;

		page = xa_load(&mapping->i_pages, pg_index);
		अगर (page && !xa_is_value(page)) अणु
			misses++;
			अगर (misses > 4)
				अवरोध;
			जाओ next;
		पूर्ण

		page = __page_cache_alloc(mapping_gfp_स्थिरraपूर्णांक(mapping,
								 ~__GFP_FS));
		अगर (!page)
			अवरोध;

		अगर (add_to_page_cache_lru(page, mapping, pg_index, GFP_NOFS)) अणु
			put_page(page);
			जाओ next;
		पूर्ण

		/*
		 * at this poपूर्णांक, we have a locked page in the page cache
		 * क्रम these bytes in the file.  But, we have to make
		 * sure they map to this compressed extent on disk.
		 */
		ret = set_page_extent_mapped(page);
		अगर (ret < 0) अणु
			unlock_page(page);
			put_page(page);
			अवरोध;
		पूर्ण

		end = last_offset + PAGE_SIZE - 1;
		lock_extent(tree, last_offset, end);
		पढ़ो_lock(&em_tree->lock);
		em = lookup_extent_mapping(em_tree, last_offset,
					   PAGE_SIZE);
		पढ़ो_unlock(&em_tree->lock);

		अगर (!em || last_offset < em->start ||
		    (last_offset + PAGE_SIZE > extent_map_end(em)) ||
		    (em->block_start >> 9) != cb->orig_bio->bi_iter.bi_sector) अणु
			मुक्त_extent_map(em);
			unlock_extent(tree, last_offset, end);
			unlock_page(page);
			put_page(page);
			अवरोध;
		पूर्ण
		मुक्त_extent_map(em);

		अगर (page->index == end_index) अणु
			माप_प्रकार zero_offset = offset_in_page(isize);

			अगर (zero_offset) अणु
				पूर्णांक zeros;
				zeros = PAGE_SIZE - zero_offset;
				memzero_page(page, zero_offset, zeros);
				flush_dcache_page(page);
			पूर्ण
		पूर्ण

		ret = bio_add_page(cb->orig_bio, page,
				   PAGE_SIZE, 0);

		अगर (ret == PAGE_SIZE) अणु
			nr_pages++;
			put_page(page);
		पूर्ण अन्यथा अणु
			unlock_extent(tree, last_offset, end);
			unlock_page(page);
			put_page(page);
			अवरोध;
		पूर्ण
next:
		last_offset += PAGE_SIZE;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * क्रम a compressed पढ़ो, the bio we get passed has all the inode pages
 * in it.  We करोn't actually करो IO on those pages but allocate new ones
 * to hold the compressed pages on disk.
 *
 * bio->bi_iter.bi_sector poपूर्णांकs to the compressed extent on disk
 * bio->bi_io_vec poपूर्णांकs to all of the inode pages
 *
 * After the compressed pages are पढ़ो, we copy the bytes पूर्णांकo the
 * bio we were passed and then call the bio end_io calls
 */
blk_status_t btrfs_submit_compressed_पढ़ो(काष्ठा inode *inode, काष्ठा bio *bio,
				 पूर्णांक mirror_num, अचिन्हित दीर्घ bio_flags)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा extent_map_tree *em_tree;
	काष्ठा compressed_bio *cb;
	अचिन्हित दीर्घ compressed_len;
	अचिन्हित दीर्घ nr_pages;
	अचिन्हित दीर्घ pg_index;
	काष्ठा page *page;
	काष्ठा bio *comp_bio;
	u64 cur_disk_byte = bio->bi_iter.bi_sector << 9;
	u64 em_len;
	u64 em_start;
	काष्ठा extent_map *em;
	blk_status_t ret = BLK_STS_RESOURCE;
	पूर्णांक faili = 0;
	u8 *sums;

	em_tree = &BTRFS_I(inode)->extent_tree;

	/* we need the actual starting offset of this extent in the file */
	पढ़ो_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree,
				   page_offset(bio_first_page_all(bio)),
				   fs_info->sectorsize);
	पढ़ो_unlock(&em_tree->lock);
	अगर (!em)
		वापस BLK_STS_IOERR;

	compressed_len = em->block_len;
	cb = kदो_स्मृति(compressed_bio_size(fs_info, compressed_len), GFP_NOFS);
	अगर (!cb)
		जाओ out;

	refcount_set(&cb->pending_bios, 0);
	cb->errors = 0;
	cb->inode = inode;
	cb->mirror_num = mirror_num;
	sums = cb->sums;

	cb->start = em->orig_start;
	em_len = em->len;
	em_start = em->start;

	मुक्त_extent_map(em);
	em = शून्य;

	cb->len = bio->bi_iter.bi_size;
	cb->compressed_len = compressed_len;
	cb->compress_type = extent_compress_type(bio_flags);
	cb->orig_bio = bio;

	nr_pages = DIV_ROUND_UP(compressed_len, PAGE_SIZE);
	cb->compressed_pages = kसुस्मृति(nr_pages, माप(काष्ठा page *),
				       GFP_NOFS);
	अगर (!cb->compressed_pages)
		जाओ fail1;

	क्रम (pg_index = 0; pg_index < nr_pages; pg_index++) अणु
		cb->compressed_pages[pg_index] = alloc_page(GFP_NOFS |
							      __GFP_HIGHMEM);
		अगर (!cb->compressed_pages[pg_index]) अणु
			faili = pg_index - 1;
			ret = BLK_STS_RESOURCE;
			जाओ fail2;
		पूर्ण
	पूर्ण
	faili = nr_pages - 1;
	cb->nr_pages = nr_pages;

	add_ra_bio_pages(inode, em_start + em_len, cb);

	/* include any pages we added in add_ra-bio_pages */
	cb->len = bio->bi_iter.bi_size;

	comp_bio = btrfs_bio_alloc(cur_disk_byte);
	comp_bio->bi_opf = REQ_OP_READ;
	comp_bio->bi_निजी = cb;
	comp_bio->bi_end_io = end_compressed_bio_पढ़ो;
	refcount_set(&cb->pending_bios, 1);

	क्रम (pg_index = 0; pg_index < nr_pages; pg_index++) अणु
		u32 pg_len = PAGE_SIZE;
		पूर्णांक submit = 0;

		/*
		 * To handle subpage हाल, we need to make sure the bio only
		 * covers the range we need.
		 *
		 * If we're at the last page, truncate the length to only cover
		 * the reमुख्यing part.
		 */
		अगर (pg_index == nr_pages - 1)
			pg_len = min_t(u32, PAGE_SIZE,
					compressed_len - pg_index * PAGE_SIZE);

		page = cb->compressed_pages[pg_index];
		page->mapping = inode->i_mapping;
		page->index = em_start >> PAGE_SHIFT;

		अगर (comp_bio->bi_iter.bi_size)
			submit = btrfs_bio_fits_in_stripe(page, pg_len,
							  comp_bio, 0);

		page->mapping = शून्य;
		अगर (submit || bio_add_page(comp_bio, page, pg_len, 0) < pg_len) अणु
			अचिन्हित पूर्णांक nr_sectors;

			ret = btrfs_bio_wq_end_io(fs_info, comp_bio,
						  BTRFS_WQ_ENDIO_DATA);
			BUG_ON(ret); /* -ENOMEM */

			/*
			 * inc the count beक्रमe we submit the bio so
			 * we know the end IO handler won't happen beक्रमe
			 * we inc the count.  Otherwise, the cb might get
			 * मुक्तd beक्रमe we're करोne setting it up
			 */
			refcount_inc(&cb->pending_bios);

			ret = btrfs_lookup_bio_sums(inode, comp_bio, sums);
			BUG_ON(ret); /* -ENOMEM */

			nr_sectors = DIV_ROUND_UP(comp_bio->bi_iter.bi_size,
						  fs_info->sectorsize);
			sums += fs_info->csum_size * nr_sectors;

			ret = btrfs_map_bio(fs_info, comp_bio, mirror_num);
			अगर (ret) अणु
				comp_bio->bi_status = ret;
				bio_endio(comp_bio);
			पूर्ण

			comp_bio = btrfs_bio_alloc(cur_disk_byte);
			comp_bio->bi_opf = REQ_OP_READ;
			comp_bio->bi_निजी = cb;
			comp_bio->bi_end_io = end_compressed_bio_पढ़ो;

			bio_add_page(comp_bio, page, pg_len, 0);
		पूर्ण
		cur_disk_byte += pg_len;
	पूर्ण

	ret = btrfs_bio_wq_end_io(fs_info, comp_bio, BTRFS_WQ_ENDIO_DATA);
	BUG_ON(ret); /* -ENOMEM */

	ret = btrfs_lookup_bio_sums(inode, comp_bio, sums);
	BUG_ON(ret); /* -ENOMEM */

	ret = btrfs_map_bio(fs_info, comp_bio, mirror_num);
	अगर (ret) अणु
		comp_bio->bi_status = ret;
		bio_endio(comp_bio);
	पूर्ण

	वापस 0;

fail2:
	जबतक (faili >= 0) अणु
		__मुक्त_page(cb->compressed_pages[faili]);
		faili--;
	पूर्ण

	kमुक्त(cb->compressed_pages);
fail1:
	kमुक्त(cb);
out:
	मुक्त_extent_map(em);
	वापस ret;
पूर्ण

/*
 * Heuristic uses प्रणालीatic sampling to collect data from the input data
 * range, the logic can be tuned by the following स्थिरants:
 *
 * @SAMPLING_READ_SIZE - how many bytes will be copied from क्रम each sample
 * @SAMPLING_INTERVAL  - range from which the sampled data can be collected
 */
#घोषणा SAMPLING_READ_SIZE	(16)
#घोषणा SAMPLING_INTERVAL	(256)

/*
 * For statistical analysis of the input data we consider bytes that क्रमm a
 * Galois Field of 256 objects. Each object has an attribute count, ie. how
 * many बार the object appeared in the sample.
 */
#घोषणा BUCKET_SIZE		(256)

/*
 * The size of the sample is based on a statistical sampling rule of thumb.
 * The common way is to perक्रमm sampling tests as दीर्घ as the number of
 * elements in each cell is at least 5.
 *
 * Instead of 5, we choose 32 to obtain more accurate results.
 * If the data contain the maximum number of symbols, which is 256, we obtain a
 * sample size bound by 8192.
 *
 * For a sample of at most 8KB of data per data range: 16 consecutive bytes
 * from up to 512 locations.
 */
#घोषणा MAX_SAMPLE_SIZE		(BTRFS_MAX_UNCOMPRESSED *		\
				 SAMPLING_READ_SIZE / SAMPLING_INTERVAL)

काष्ठा bucket_item अणु
	u32 count;
पूर्ण;

काष्ठा heuristic_ws अणु
	/* Partial copy of input data */
	u8 *sample;
	u32 sample_size;
	/* Buckets store counters क्रम each byte value */
	काष्ठा bucket_item *bucket;
	/* Sorting buffer */
	काष्ठा bucket_item *bucket_b;
	काष्ठा list_head list;
पूर्ण;

अटल काष्ठा workspace_manager heuristic_wsm;

अटल व्योम मुक्त_heuristic_ws(काष्ठा list_head *ws)
अणु
	काष्ठा heuristic_ws *workspace;

	workspace = list_entry(ws, काष्ठा heuristic_ws, list);

	kvमुक्त(workspace->sample);
	kमुक्त(workspace->bucket);
	kमुक्त(workspace->bucket_b);
	kमुक्त(workspace);
पूर्ण

अटल काष्ठा list_head *alloc_heuristic_ws(अचिन्हित पूर्णांक level)
अणु
	काष्ठा heuristic_ws *ws;

	ws = kzalloc(माप(*ws), GFP_KERNEL);
	अगर (!ws)
		वापस ERR_PTR(-ENOMEM);

	ws->sample = kvदो_स्मृति(MAX_SAMPLE_SIZE, GFP_KERNEL);
	अगर (!ws->sample)
		जाओ fail;

	ws->bucket = kसुस्मृति(BUCKET_SIZE, माप(*ws->bucket), GFP_KERNEL);
	अगर (!ws->bucket)
		जाओ fail;

	ws->bucket_b = kसुस्मृति(BUCKET_SIZE, माप(*ws->bucket_b), GFP_KERNEL);
	अगर (!ws->bucket_b)
		जाओ fail;

	INIT_LIST_HEAD(&ws->list);
	वापस &ws->list;
fail:
	मुक्त_heuristic_ws(&ws->list);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

स्थिर काष्ठा btrfs_compress_op btrfs_heuristic_compress = अणु
	.workspace_manager = &heuristic_wsm,
पूर्ण;

अटल स्थिर काष्ठा btrfs_compress_op * स्थिर btrfs_compress_op[] = अणु
	/* The heuristic is represented as compression type 0 */
	&btrfs_heuristic_compress,
	&btrfs_zlib_compress,
	&btrfs_lzo_compress,
	&btrfs_zstd_compress,
पूर्ण;

अटल काष्ठा list_head *alloc_workspace(पूर्णांक type, अचिन्हित पूर्णांक level)
अणु
	चयन (type) अणु
	हाल BTRFS_COMPRESS_NONE: वापस alloc_heuristic_ws(level);
	हाल BTRFS_COMPRESS_ZLIB: वापस zlib_alloc_workspace(level);
	हाल BTRFS_COMPRESS_LZO:  वापस lzo_alloc_workspace(level);
	हाल BTRFS_COMPRESS_ZSTD: वापस zstd_alloc_workspace(level);
	शेष:
		/*
		 * This can't happen, the type is validated several बार
		 * beक्रमe we get here.
		 */
		BUG();
	पूर्ण
पूर्ण

अटल व्योम मुक्त_workspace(पूर्णांक type, काष्ठा list_head *ws)
अणु
	चयन (type) अणु
	हाल BTRFS_COMPRESS_NONE: वापस मुक्त_heuristic_ws(ws);
	हाल BTRFS_COMPRESS_ZLIB: वापस zlib_मुक्त_workspace(ws);
	हाल BTRFS_COMPRESS_LZO:  वापस lzo_मुक्त_workspace(ws);
	हाल BTRFS_COMPRESS_ZSTD: वापस zstd_मुक्त_workspace(ws);
	शेष:
		/*
		 * This can't happen, the type is validated several बार
		 * beक्रमe we get here.
		 */
		BUG();
	पूर्ण
पूर्ण

अटल व्योम btrfs_init_workspace_manager(पूर्णांक type)
अणु
	काष्ठा workspace_manager *wsm;
	काष्ठा list_head *workspace;

	wsm = btrfs_compress_op[type]->workspace_manager;
	INIT_LIST_HEAD(&wsm->idle_ws);
	spin_lock_init(&wsm->ws_lock);
	atomic_set(&wsm->total_ws, 0);
	init_रुकोqueue_head(&wsm->ws_रुको);

	/*
	 * Pपुनः_स्मृतिate one workspace क्रम each compression type so we can
	 * guarantee क्रमward progress in the worst हाल
	 */
	workspace = alloc_workspace(type, 0);
	अगर (IS_ERR(workspace)) अणु
		pr_warn(
	"BTRFS: cannot preallocate compression workspace, will try later\n");
	पूर्ण अन्यथा अणु
		atomic_set(&wsm->total_ws, 1);
		wsm->मुक्त_ws = 1;
		list_add(workspace, &wsm->idle_ws);
	पूर्ण
पूर्ण

अटल व्योम btrfs_cleanup_workspace_manager(पूर्णांक type)
अणु
	काष्ठा workspace_manager *wsman;
	काष्ठा list_head *ws;

	wsman = btrfs_compress_op[type]->workspace_manager;
	जबतक (!list_empty(&wsman->idle_ws)) अणु
		ws = wsman->idle_ws.next;
		list_del(ws);
		मुक्त_workspace(type, ws);
		atomic_dec(&wsman->total_ws);
	पूर्ण
पूर्ण

/*
 * This finds an available workspace or allocates a new one.
 * If it's not possible to allocate a new one, waits until there's one.
 * Pपुनः_स्मृतिation makes a क्रमward progress guarantees and we करो not वापस
 * errors.
 */
काष्ठा list_head *btrfs_get_workspace(पूर्णांक type, अचिन्हित पूर्णांक level)
अणु
	काष्ठा workspace_manager *wsm;
	काष्ठा list_head *workspace;
	पूर्णांक cpus = num_online_cpus();
	अचिन्हित nofs_flag;
	काष्ठा list_head *idle_ws;
	spinlock_t *ws_lock;
	atomic_t *total_ws;
	रुको_queue_head_t *ws_रुको;
	पूर्णांक *मुक्त_ws;

	wsm = btrfs_compress_op[type]->workspace_manager;
	idle_ws	 = &wsm->idle_ws;
	ws_lock	 = &wsm->ws_lock;
	total_ws = &wsm->total_ws;
	ws_रुको	 = &wsm->ws_रुको;
	मुक्त_ws	 = &wsm->मुक्त_ws;

again:
	spin_lock(ws_lock);
	अगर (!list_empty(idle_ws)) अणु
		workspace = idle_ws->next;
		list_del(workspace);
		(*मुक्त_ws)--;
		spin_unlock(ws_lock);
		वापस workspace;

	पूर्ण
	अगर (atomic_पढ़ो(total_ws) > cpus) अणु
		DEFINE_WAIT(रुको);

		spin_unlock(ws_lock);
		prepare_to_रुको(ws_रुको, &रुको, TASK_UNINTERRUPTIBLE);
		अगर (atomic_पढ़ो(total_ws) > cpus && !*मुक्त_ws)
			schedule();
		finish_रुको(ws_रुको, &रुको);
		जाओ again;
	पूर्ण
	atomic_inc(total_ws);
	spin_unlock(ws_lock);

	/*
	 * Allocation helpers call vदो_स्मृति that can't use GFP_NOFS, so we have
	 * to turn it off here because we might get called from the restricted
	 * context of btrfs_compress_bio/btrfs_compress_pages
	 */
	nofs_flag = meदो_स्मृति_nofs_save();
	workspace = alloc_workspace(type, level);
	meदो_स्मृति_nofs_restore(nofs_flag);

	अगर (IS_ERR(workspace)) अणु
		atomic_dec(total_ws);
		wake_up(ws_रुको);

		/*
		 * Do not वापस the error but go back to रुकोing. There's a
		 * workspace pपुनः_स्मृतिated क्रम each type and the compression
		 * समय is bounded so we get to a workspace eventually. This
		 * makes our caller's lअगरe easier.
		 *
		 * To prevent silent and low-probability deadlocks (when the
		 * initial pपुनः_स्मृतिation fails), check अगर there are any
		 * workspaces at all.
		 */
		अगर (atomic_पढ़ो(total_ws) == 0) अणु
			अटल DEFINE_RATELIMIT_STATE(_rs,
					/* once per minute */ 60 * HZ,
					/* no burst */ 1);

			अगर (__ratelimit(&_rs)) अणु
				pr_warn("BTRFS: no compression workspaces, low memory, retrying\n");
			पूर्ण
		पूर्ण
		जाओ again;
	पूर्ण
	वापस workspace;
पूर्ण

अटल काष्ठा list_head *get_workspace(पूर्णांक type, पूर्णांक level)
अणु
	चयन (type) अणु
	हाल BTRFS_COMPRESS_NONE: वापस btrfs_get_workspace(type, level);
	हाल BTRFS_COMPRESS_ZLIB: वापस zlib_get_workspace(level);
	हाल BTRFS_COMPRESS_LZO:  वापस btrfs_get_workspace(type, level);
	हाल BTRFS_COMPRESS_ZSTD: वापस zstd_get_workspace(level);
	शेष:
		/*
		 * This can't happen, the type is validated several बार
		 * beक्रमe we get here.
		 */
		BUG();
	पूर्ण
पूर्ण

/*
 * put a workspace काष्ठा back on the list or मुक्त it अगर we have enough
 * idle ones sitting around
 */
व्योम btrfs_put_workspace(पूर्णांक type, काष्ठा list_head *ws)
अणु
	काष्ठा workspace_manager *wsm;
	काष्ठा list_head *idle_ws;
	spinlock_t *ws_lock;
	atomic_t *total_ws;
	रुको_queue_head_t *ws_रुको;
	पूर्णांक *मुक्त_ws;

	wsm = btrfs_compress_op[type]->workspace_manager;
	idle_ws	 = &wsm->idle_ws;
	ws_lock	 = &wsm->ws_lock;
	total_ws = &wsm->total_ws;
	ws_रुको	 = &wsm->ws_रुको;
	मुक्त_ws	 = &wsm->मुक्त_ws;

	spin_lock(ws_lock);
	अगर (*मुक्त_ws <= num_online_cpus()) अणु
		list_add(ws, idle_ws);
		(*मुक्त_ws)++;
		spin_unlock(ws_lock);
		जाओ wake;
	पूर्ण
	spin_unlock(ws_lock);

	मुक्त_workspace(type, ws);
	atomic_dec(total_ws);
wake:
	cond_wake_up(ws_रुको);
पूर्ण

अटल व्योम put_workspace(पूर्णांक type, काष्ठा list_head *ws)
अणु
	चयन (type) अणु
	हाल BTRFS_COMPRESS_NONE: वापस btrfs_put_workspace(type, ws);
	हाल BTRFS_COMPRESS_ZLIB: वापस btrfs_put_workspace(type, ws);
	हाल BTRFS_COMPRESS_LZO:  वापस btrfs_put_workspace(type, ws);
	हाल BTRFS_COMPRESS_ZSTD: वापस zstd_put_workspace(ws);
	शेष:
		/*
		 * This can't happen, the type is validated several बार
		 * beक्रमe we get here.
		 */
		BUG();
	पूर्ण
पूर्ण

/*
 * Adjust @level according to the limits of the compression algorithm or
 * fallback to शेष
 */
अटल अचिन्हित पूर्णांक btrfs_compress_set_level(पूर्णांक type, अचिन्हित level)
अणु
	स्थिर काष्ठा btrfs_compress_op *ops = btrfs_compress_op[type];

	अगर (level == 0)
		level = ops->शेष_level;
	अन्यथा
		level = min(level, ops->max_level);

	वापस level;
पूर्ण

/*
 * Given an address space and start and length, compress the bytes पूर्णांकo @pages
 * that are allocated on demand.
 *
 * @type_level is encoded algorithm and level, where level 0 means whatever
 * शेष the algorithm chooses and is opaque here;
 * - compression algo are 0-3
 * - the level are bits 4-7
 *
 * @out_pages is an in/out parameter, holds maximum number of pages to allocate
 * and वापसs number of actually allocated pages
 *
 * @total_in is used to वापस the number of bytes actually पढ़ो.  It
 * may be smaller than the input length अगर we had to निकास early because we
 * ran out of room in the pages array or because we cross the
 * max_out threshold.
 *
 * @total_out is an in/out parameter, must be set to the input length and will
 * be also used to वापस the total number of compressed bytes
 *
 * @max_out tells us the max number of bytes that we're allowed to
 * stuff पूर्णांकo pages
 */
पूर्णांक btrfs_compress_pages(अचिन्हित पूर्णांक type_level, काष्ठा address_space *mapping,
			 u64 start, काष्ठा page **pages,
			 अचिन्हित दीर्घ *out_pages,
			 अचिन्हित दीर्घ *total_in,
			 अचिन्हित दीर्घ *total_out)
अणु
	पूर्णांक type = btrfs_compress_type(type_level);
	पूर्णांक level = btrfs_compress_level(type_level);
	काष्ठा list_head *workspace;
	पूर्णांक ret;

	level = btrfs_compress_set_level(type, level);
	workspace = get_workspace(type, level);
	ret = compression_compress_pages(type, workspace, mapping, start, pages,
					 out_pages, total_in, total_out);
	put_workspace(type, workspace);
	वापस ret;
पूर्ण

/*
 * pages_in is an array of pages with compressed data.
 *
 * disk_start is the starting logical offset of this array in the file
 *
 * orig_bio contains the pages from the file that we want to decompress पूर्णांकo
 *
 * srclen is the number of bytes in pages_in
 *
 * The basic idea is that we have a bio that was created by पढ़ोpages.
 * The pages in the bio are क्रम the uncompressed data, and they may not
 * be contiguous.  They all correspond to the range of bytes covered by
 * the compressed extent.
 */
अटल पूर्णांक btrfs_decompress_bio(काष्ठा compressed_bio *cb)
अणु
	काष्ठा list_head *workspace;
	पूर्णांक ret;
	पूर्णांक type = cb->compress_type;

	workspace = get_workspace(type, 0);
	ret = compression_decompress_bio(type, workspace, cb);
	put_workspace(type, workspace);

	वापस ret;
पूर्ण

/*
 * a less complex decompression routine.  Our compressed data fits in a
 * single page, and we want to पढ़ो a single page out of it.
 * start_byte tells us the offset पूर्णांकo the compressed data we're पूर्णांकerested in
 */
पूर्णांक btrfs_decompress(पूर्णांक type, अचिन्हित अक्षर *data_in, काष्ठा page *dest_page,
		     अचिन्हित दीर्घ start_byte, माप_प्रकार srclen, माप_प्रकार destlen)
अणु
	काष्ठा list_head *workspace;
	पूर्णांक ret;

	workspace = get_workspace(type, 0);
	ret = compression_decompress(type, workspace, data_in, dest_page,
				     start_byte, srclen, destlen);
	put_workspace(type, workspace);

	वापस ret;
पूर्ण

व्योम __init btrfs_init_compress(व्योम)
अणु
	btrfs_init_workspace_manager(BTRFS_COMPRESS_NONE);
	btrfs_init_workspace_manager(BTRFS_COMPRESS_ZLIB);
	btrfs_init_workspace_manager(BTRFS_COMPRESS_LZO);
	zstd_init_workspace_manager();
पूर्ण

व्योम __cold btrfs_निकास_compress(व्योम)
अणु
	btrfs_cleanup_workspace_manager(BTRFS_COMPRESS_NONE);
	btrfs_cleanup_workspace_manager(BTRFS_COMPRESS_ZLIB);
	btrfs_cleanup_workspace_manager(BTRFS_COMPRESS_LZO);
	zstd_cleanup_workspace_manager();
पूर्ण

/*
 * Copy uncompressed data from working buffer to pages.
 *
 * buf_start is the byte offset we're of the start of our workspace buffer.
 *
 * total_out is the last byte of the buffer
 */
पूर्णांक btrfs_decompress_buf2page(स्थिर अक्षर *buf, अचिन्हित दीर्घ buf_start,
			      अचिन्हित दीर्घ total_out, u64 disk_start,
			      काष्ठा bio *bio)
अणु
	अचिन्हित दीर्घ buf_offset;
	अचिन्हित दीर्घ current_buf_start;
	अचिन्हित दीर्घ start_byte;
	अचिन्हित दीर्घ prev_start_byte;
	अचिन्हित दीर्घ working_bytes = total_out - buf_start;
	अचिन्हित दीर्घ bytes;
	काष्ठा bio_vec bvec = bio_iter_iovec(bio, bio->bi_iter);

	/*
	 * start byte is the first byte of the page we're currently
	 * copying पूर्णांकo relative to the start of the compressed data.
	 */
	start_byte = page_offset(bvec.bv_page) - disk_start;

	/* we haven't yet hit data corresponding to this page */
	अगर (total_out <= start_byte)
		वापस 1;

	/*
	 * the start of the data we care about is offset पूर्णांकo
	 * the middle of our working buffer
	 */
	अगर (total_out > start_byte && buf_start < start_byte) अणु
		buf_offset = start_byte - buf_start;
		working_bytes -= buf_offset;
	पूर्ण अन्यथा अणु
		buf_offset = 0;
	पूर्ण
	current_buf_start = buf_start;

	/* copy bytes from the working buffer पूर्णांकo the pages */
	जबतक (working_bytes > 0) अणु
		bytes = min_t(अचिन्हित दीर्घ, bvec.bv_len,
				PAGE_SIZE - (buf_offset % PAGE_SIZE));
		bytes = min(bytes, working_bytes);

		स_नकल_to_page(bvec.bv_page, bvec.bv_offset, buf + buf_offset,
			       bytes);
		flush_dcache_page(bvec.bv_page);

		buf_offset += bytes;
		working_bytes -= bytes;
		current_buf_start += bytes;

		/* check अगर we need to pick another page */
		bio_advance(bio, bytes);
		अगर (!bio->bi_iter.bi_size)
			वापस 0;
		bvec = bio_iter_iovec(bio, bio->bi_iter);
		prev_start_byte = start_byte;
		start_byte = page_offset(bvec.bv_page) - disk_start;

		/*
		 * We need to make sure we're only adjusting
		 * our offset पूर्णांकo compression working buffer when
		 * we're चयनing pages.  Otherwise we can incorrectly
		 * keep copying when we were actually करोne.
		 */
		अगर (start_byte != prev_start_byte) अणु
			/*
			 * make sure our new page is covered by this
			 * working buffer
			 */
			अगर (total_out <= start_byte)
				वापस 1;

			/*
			 * the next page in the biovec might not be adjacent
			 * to the last page, but it might still be found
			 * inside this working buffer. bump our offset poपूर्णांकer
			 */
			अगर (total_out > start_byte &&
			    current_buf_start < start_byte) अणु
				buf_offset = start_byte - buf_start;
				working_bytes = total_out - start_byte;
				current_buf_start = buf_start + buf_offset;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Shannon Entropy calculation
 *
 * Pure byte distribution analysis fails to determine compressibility of data.
 * Try calculating entropy to estimate the average minimum number of bits
 * needed to encode the sampled data.
 *
 * For convenience, वापस the percentage of needed bits, instead of amount of
 * bits directly.
 *
 * @ENTROPY_LVL_ACEPTABLE - below that threshold, sample has low byte entropy
 *			    and can be compressible with high probability
 *
 * @ENTROPY_LVL_HIGH - data are not compressible with high probability
 *
 * Use of ilog2() decreases precision, we lower the LVL to 5 to compensate.
 */
#घोषणा ENTROPY_LVL_ACEPTABLE		(65)
#घोषणा ENTROPY_LVL_HIGH		(80)

/*
 * For increasead precision in shannon_entropy calculation,
 * let's करो घात(n, M) to save more digits after comma:
 *
 * - maximum पूर्णांक bit length is 64
 * - ilog2(MAX_SAMPLE_SIZE)	-> 13
 * - 13 * 4 = 52 < 64		-> M = 4
 *
 * So use घात(n, 4).
 */
अटल अंतरभूत u32 ilog2_w(u64 n)
अणु
	वापस ilog2(n * n * n * n);
पूर्ण

अटल u32 shannon_entropy(काष्ठा heuristic_ws *ws)
अणु
	स्थिर u32 entropy_max = 8 * ilog2_w(2);
	u32 entropy_sum = 0;
	u32 p, p_base, sz_base;
	u32 i;

	sz_base = ilog2_w(ws->sample_size);
	क्रम (i = 0; i < BUCKET_SIZE && ws->bucket[i].count > 0; i++) अणु
		p = ws->bucket[i].count;
		p_base = ilog2_w(p);
		entropy_sum += p * (sz_base - p_base);
	पूर्ण

	entropy_sum /= ws->sample_size;
	वापस entropy_sum * 100 / entropy_max;
पूर्ण

#घोषणा RADIX_BASE		4U
#घोषणा COUNTERS_SIZE		(1U << RADIX_BASE)

अटल u8 get4bits(u64 num, पूर्णांक shअगरt) अणु
	u8 low4bits;

	num >>= shअगरt;
	/* Reverse order */
	low4bits = (COUNTERS_SIZE - 1) - (num % COUNTERS_SIZE);
	वापस low4bits;
पूर्ण

/*
 * Use 4 bits as radix base
 * Use 16 u32 counters क्रम calculating new position in buf array
 *
 * @array     - array that will be sorted
 * @array_buf - buffer array to store sorting results
 *              must be equal in size to @array
 * @num       - array size
 */
अटल व्योम radix_sort(काष्ठा bucket_item *array, काष्ठा bucket_item *array_buf,
		       पूर्णांक num)
अणु
	u64 max_num;
	u64 buf_num;
	u32 counters[COUNTERS_SIZE];
	u32 new_addr;
	u32 addr;
	पूर्णांक bitlen;
	पूर्णांक shअगरt;
	पूर्णांक i;

	/*
	 * Try aव्योम useless loop iterations क्रम small numbers stored in big
	 * counters.  Example: 48 33 4 ... in 64bit array
	 */
	max_num = array[0].count;
	क्रम (i = 1; i < num; i++) अणु
		buf_num = array[i].count;
		अगर (buf_num > max_num)
			max_num = buf_num;
	पूर्ण

	buf_num = ilog2(max_num);
	bitlen = ALIGN(buf_num, RADIX_BASE * 2);

	shअगरt = 0;
	जबतक (shअगरt < bitlen) अणु
		स_रखो(counters, 0, माप(counters));

		क्रम (i = 0; i < num; i++) अणु
			buf_num = array[i].count;
			addr = get4bits(buf_num, shअगरt);
			counters[addr]++;
		पूर्ण

		क्रम (i = 1; i < COUNTERS_SIZE; i++)
			counters[i] += counters[i - 1];

		क्रम (i = num - 1; i >= 0; i--) अणु
			buf_num = array[i].count;
			addr = get4bits(buf_num, shअगरt);
			counters[addr]--;
			new_addr = counters[addr];
			array_buf[new_addr] = array[i];
		पूर्ण

		shअगरt += RADIX_BASE;

		/*
		 * Normal radix expects to move data from a temporary array, to
		 * the मुख्य one.  But that requires some CPU समय. Aव्योम that
		 * by करोing another sort iteration to original array instead of
		 * स_नकल()
		 */
		स_रखो(counters, 0, माप(counters));

		क्रम (i = 0; i < num; i ++) अणु
			buf_num = array_buf[i].count;
			addr = get4bits(buf_num, shअगरt);
			counters[addr]++;
		पूर्ण

		क्रम (i = 1; i < COUNTERS_SIZE; i++)
			counters[i] += counters[i - 1];

		क्रम (i = num - 1; i >= 0; i--) अणु
			buf_num = array_buf[i].count;
			addr = get4bits(buf_num, shअगरt);
			counters[addr]--;
			new_addr = counters[addr];
			array[new_addr] = array_buf[i];
		पूर्ण

		shअगरt += RADIX_BASE;
	पूर्ण
पूर्ण

/*
 * Size of the core byte set - how many bytes cover 90% of the sample
 *
 * There are several types of काष्ठाured binary data that use nearly all byte
 * values. The distribution can be unअगरorm and counts in all buckets will be
 * nearly the same (eg. encrypted data). Unlikely to be compressible.
 *
 * Other possibility is normal (Gaussian) distribution, where the data could
 * be potentially compressible, but we have to take a few more steps to decide
 * how much.
 *
 * @BYTE_CORE_SET_LOW  - मुख्य part of byte values repeated frequently,
 *                       compression algo can easy fix that
 * @BYTE_CORE_SET_HIGH - data have unअगरorm distribution and with high
 *                       probability is not compressible
 */
#घोषणा BYTE_CORE_SET_LOW		(64)
#घोषणा BYTE_CORE_SET_HIGH		(200)

अटल पूर्णांक byte_core_set_size(काष्ठा heuristic_ws *ws)
अणु
	u32 i;
	u32 coreset_sum = 0;
	स्थिर u32 core_set_threshold = ws->sample_size * 90 / 100;
	काष्ठा bucket_item *bucket = ws->bucket;

	/* Sort in reverse order */
	radix_sort(ws->bucket, ws->bucket_b, BUCKET_SIZE);

	क्रम (i = 0; i < BYTE_CORE_SET_LOW; i++)
		coreset_sum += bucket[i].count;

	अगर (coreset_sum > core_set_threshold)
		वापस i;

	क्रम (; i < BYTE_CORE_SET_HIGH && bucket[i].count > 0; i++) अणु
		coreset_sum += bucket[i].count;
		अगर (coreset_sum > core_set_threshold)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

/*
 * Count byte values in buckets.
 * This heuristic can detect textual data (configs, xml, json, hपंचांगl, etc).
 * Because in most text-like data byte set is restricted to limited number of
 * possible अक्षरacters, and that restriction in most हालs makes data easy to
 * compress.
 *
 * @BYTE_SET_THRESHOLD - consider all data within this byte set size:
 *	less - compressible
 *	more - need additional analysis
 */
#घोषणा BYTE_SET_THRESHOLD		(64)

अटल u32 byte_set_size(स्थिर काष्ठा heuristic_ws *ws)
अणु
	u32 i;
	u32 byte_set_size = 0;

	क्रम (i = 0; i < BYTE_SET_THRESHOLD; i++) अणु
		अगर (ws->bucket[i].count > 0)
			byte_set_size++;
	पूर्ण

	/*
	 * Continue collecting count of byte values in buckets.  If the byte
	 * set size is bigger then the threshold, it's poपूर्णांकless to जारी,
	 * the detection technique would fail क्रम this type of data.
	 */
	क्रम (; i < BUCKET_SIZE; i++) अणु
		अगर (ws->bucket[i].count > 0) अणु
			byte_set_size++;
			अगर (byte_set_size > BYTE_SET_THRESHOLD)
				वापस byte_set_size;
		पूर्ण
	पूर्ण

	वापस byte_set_size;
पूर्ण

अटल bool sample_repeated_patterns(काष्ठा heuristic_ws *ws)
अणु
	स्थिर u32 half_of_sample = ws->sample_size / 2;
	स्थिर u8 *data = ws->sample;

	वापस स_भेद(&data[0], &data[half_of_sample], half_of_sample) == 0;
पूर्ण

अटल व्योम heuristic_collect_sample(काष्ठा inode *inode, u64 start, u64 end,
				     काष्ठा heuristic_ws *ws)
अणु
	काष्ठा page *page;
	u64 index, index_end;
	u32 i, curr_sample_pos;
	u8 *in_data;

	/*
	 * Compression handles the input data by chunks of 128KiB
	 * (defined by BTRFS_MAX_UNCOMPRESSED)
	 *
	 * We करो the same क्रम the heuristic and loop over the whole range.
	 *
	 * MAX_SAMPLE_SIZE - calculated under assumption that heuristic will
	 * process no more than BTRFS_MAX_UNCOMPRESSED at a समय.
	 */
	अगर (end - start > BTRFS_MAX_UNCOMPRESSED)
		end = start + BTRFS_MAX_UNCOMPRESSED;

	index = start >> PAGE_SHIFT;
	index_end = end >> PAGE_SHIFT;

	/* Don't miss unaligned end */
	अगर (!IS_ALIGNED(end, PAGE_SIZE))
		index_end++;

	curr_sample_pos = 0;
	जबतक (index < index_end) अणु
		page = find_get_page(inode->i_mapping, index);
		in_data = kmap_local_page(page);
		/* Handle हाल where the start is not aligned to PAGE_SIZE */
		i = start % PAGE_SIZE;
		जबतक (i < PAGE_SIZE - SAMPLING_READ_SIZE) अणु
			/* Don't sample any garbage from the last page */
			अगर (start > end - SAMPLING_READ_SIZE)
				अवरोध;
			स_नकल(&ws->sample[curr_sample_pos], &in_data[i],
					SAMPLING_READ_SIZE);
			i += SAMPLING_INTERVAL;
			start += SAMPLING_INTERVAL;
			curr_sample_pos += SAMPLING_READ_SIZE;
		पूर्ण
		kunmap_local(in_data);
		put_page(page);

		index++;
	पूर्ण

	ws->sample_size = curr_sample_pos;
पूर्ण

/*
 * Compression heuristic.
 *
 * For now is's a naive and optimistic 'return true', we'll extend the logic to
 * quickly (compared to direct compression) detect data अक्षरacteristics
 * (compressible/uncompressible) to aव्योम wasting CPU समय on uncompressible
 * data.
 *
 * The following types of analysis can be perक्रमmed:
 * - detect mostly zero data
 * - detect data with low "byte set" size (text, etc)
 * - detect data with low/high "core byte" set
 *
 * Return non-zero अगर the compression should be करोne, 0 otherwise.
 */
पूर्णांक btrfs_compress_heuristic(काष्ठा inode *inode, u64 start, u64 end)
अणु
	काष्ठा list_head *ws_list = get_workspace(0, 0);
	काष्ठा heuristic_ws *ws;
	u32 i;
	u8 byte;
	पूर्णांक ret = 0;

	ws = list_entry(ws_list, काष्ठा heuristic_ws, list);

	heuristic_collect_sample(inode, start, end, ws);

	अगर (sample_repeated_patterns(ws)) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	स_रखो(ws->bucket, 0, माप(*ws->bucket)*BUCKET_SIZE);

	क्रम (i = 0; i < ws->sample_size; i++) अणु
		byte = ws->sample[i];
		ws->bucket[byte].count++;
	पूर्ण

	i = byte_set_size(ws);
	अगर (i < BYTE_SET_THRESHOLD) अणु
		ret = 2;
		जाओ out;
	पूर्ण

	i = byte_core_set_size(ws);
	अगर (i <= BYTE_CORE_SET_LOW) अणु
		ret = 3;
		जाओ out;
	पूर्ण

	अगर (i >= BYTE_CORE_SET_HIGH) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	i = shannon_entropy(ws);
	अगर (i <= ENTROPY_LVL_ACEPTABLE) अणु
		ret = 4;
		जाओ out;
	पूर्ण

	/*
	 * For the levels below ENTROPY_LVL_HIGH, additional analysis would be
	 * needed to give green light to compression.
	 *
	 * For now just assume that compression at that level is not worth the
	 * resources because:
	 *
	 * 1. it is possible to defrag the data later
	 *
	 * 2. the data would turn out to be hardly compressible, eg. 150 byte
	 * values, every bucket has counter at level ~54. The heuristic would
	 * be confused. This can happen when data have some पूर्णांकernal repeated
	 * patterns like "abbacbbc...". This can be detected by analyzing
	 * pairs of bytes, which is too costly.
	 */
	अगर (i < ENTROPY_LVL_HIGH) अणु
		ret = 5;
		जाओ out;
	पूर्ण अन्यथा अणु
		ret = 0;
		जाओ out;
	पूर्ण

out:
	put_workspace(0, ws_list);
	वापस ret;
पूर्ण

/*
 * Convert the compression suffix (eg. after "zlib" starting with ":") to
 * level, unrecognized string will set the शेष level
 */
अचिन्हित पूर्णांक btrfs_compress_str2level(अचिन्हित पूर्णांक type, स्थिर अक्षर *str)
अणु
	अचिन्हित पूर्णांक level = 0;
	पूर्णांक ret;

	अगर (!type)
		वापस 0;

	अगर (str[0] == ':') अणु
		ret = kstrtouपूर्णांक(str + 1, 10, &level);
		अगर (ret)
			level = 0;
	पूर्ण

	level = btrfs_compress_set_level(type, level);

	वापस level;
पूर्ण
