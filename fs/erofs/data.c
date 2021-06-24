<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#समावेश "internal.h"
#समावेश <linux/prefetch.h>

#समावेश <trace/events/erofs.h>

अटल व्योम erofs_पढ़ोendio(काष्ठा bio *bio)
अणु
	काष्ठा bio_vec *bvec;
	blk_status_t err = bio->bi_status;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		काष्ठा page *page = bvec->bv_page;

		/* page is alपढ़ोy locked */
		DBG_BUGON(PageUptodate(page));

		अगर (err)
			SetPageError(page);
		अन्यथा
			SetPageUptodate(page);

		unlock_page(page);
		/* page could be reclaimed now */
	पूर्ण
	bio_put(bio);
पूर्ण

काष्ठा page *erofs_get_meta_page(काष्ठा super_block *sb, erofs_blk_t blkaddr)
अणु
	काष्ठा address_space *स्थिर mapping = sb->s_bdev->bd_inode->i_mapping;
	काष्ठा page *page;

	page = पढ़ो_cache_page_gfp(mapping, blkaddr,
				   mapping_gfp_स्थिरraपूर्णांक(mapping, ~__GFP_FS));
	/* should alपढ़ोy be PageUptodate */
	अगर (!IS_ERR(page))
		lock_page(page);
	वापस page;
पूर्ण

अटल पूर्णांक erofs_map_blocks_flaपंचांगode(काष्ठा inode *inode,
				     काष्ठा erofs_map_blocks *map,
				     पूर्णांक flags)
अणु
	पूर्णांक err = 0;
	erofs_blk_t nblocks, lastblk;
	u64 offset = map->m_la;
	काष्ठा erofs_inode *vi = EROFS_I(inode);
	bool tailendpacking = (vi->datalayout == EROFS_INODE_FLAT_INLINE);

	trace_erofs_map_blocks_flaपंचांगode_enter(inode, map, flags);

	nblocks = DIV_ROUND_UP(inode->i_size, PAGE_SIZE);
	lastblk = nblocks - tailendpacking;

	अगर (offset >= inode->i_size) अणु
		/* leave out-of-bound access unmapped */
		map->m_flags = 0;
		map->m_plen = 0;
		जाओ out;
	पूर्ण

	/* there is no hole in flaपंचांगode */
	map->m_flags = EROFS_MAP_MAPPED;

	अगर (offset < blknr_to_addr(lastblk)) अणु
		map->m_pa = blknr_to_addr(vi->raw_blkaddr) + map->m_la;
		map->m_plen = blknr_to_addr(lastblk) - offset;
	पूर्ण अन्यथा अगर (tailendpacking) अणु
		/* 2 - inode अंतरभूत B: inode, [xattrs], अंतरभूत last blk... */
		काष्ठा erofs_sb_info *sbi = EROFS_SB(inode->i_sb);

		map->m_pa = iloc(sbi, vi->nid) + vi->inode_isize +
			vi->xattr_isize + erofs_blkoff(map->m_la);
		map->m_plen = inode->i_size - offset;

		/* अंतरभूत data should be located in one meta block */
		अगर (erofs_blkoff(map->m_pa) + map->m_plen > PAGE_SIZE) अणु
			erofs_err(inode->i_sb,
				  "inline data cross block boundary @ nid %llu",
				  vi->nid);
			DBG_BUGON(1);
			err = -EFSCORRUPTED;
			जाओ err_out;
		पूर्ण

		map->m_flags |= EROFS_MAP_META;
	पूर्ण अन्यथा अणु
		erofs_err(inode->i_sb,
			  "internal error @ nid: %llu (size %llu), m_la 0x%llx",
			  vi->nid, inode->i_size, map->m_la);
		DBG_BUGON(1);
		err = -EIO;
		जाओ err_out;
	पूर्ण

out:
	map->m_llen = map->m_plen;

err_out:
	trace_erofs_map_blocks_flaपंचांगode_निकास(inode, map, flags, 0);
	वापस err;
पूर्ण

अटल अंतरभूत काष्ठा bio *erofs_पढ़ो_raw_page(काष्ठा bio *bio,
					      काष्ठा address_space *mapping,
					      काष्ठा page *page,
					      erofs_off_t *last_block,
					      अचिन्हित पूर्णांक nblocks,
					      अचिन्हित पूर्णांक *eblks,
					      bool ra)
अणु
	काष्ठा inode *स्थिर inode = mapping->host;
	काष्ठा super_block *स्थिर sb = inode->i_sb;
	erofs_off_t current_block = (erofs_off_t)page->index;
	पूर्णांक err;

	DBG_BUGON(!nblocks);

	अगर (PageUptodate(page)) अणु
		err = 0;
		जाओ has_updated;
	पूर्ण

	/* note that क्रम पढ़ोpage हाल, bio also equals to शून्य */
	अगर (bio &&
	    (*last_block + 1 != current_block || !*eblks)) अणु
submit_bio_retry:
		submit_bio(bio);
		bio = शून्य;
	पूर्ण

	अगर (!bio) अणु
		काष्ठा erofs_map_blocks map = अणु
			.m_la = blknr_to_addr(current_block),
		पूर्ण;
		erofs_blk_t blknr;
		अचिन्हित पूर्णांक blkoff;

		err = erofs_map_blocks_flaपंचांगode(inode, &map, EROFS_GET_BLOCKS_RAW);
		अगर (err)
			जाओ err_out;

		/* zero out the holed page */
		अगर (!(map.m_flags & EROFS_MAP_MAPPED)) अणु
			zero_user_segment(page, 0, PAGE_SIZE);
			SetPageUptodate(page);

			/* imply err = 0, see erofs_map_blocks */
			जाओ has_updated;
		पूर्ण

		/* क्रम RAW access mode, m_plen must be equal to m_llen */
		DBG_BUGON(map.m_plen != map.m_llen);

		blknr = erofs_blknr(map.m_pa);
		blkoff = erofs_blkoff(map.m_pa);

		/* deal with अंतरभूत page */
		अगर (map.m_flags & EROFS_MAP_META) अणु
			व्योम *vsrc, *vto;
			काष्ठा page *ipage;

			DBG_BUGON(map.m_plen > PAGE_SIZE);

			ipage = erofs_get_meta_page(inode->i_sb, blknr);

			अगर (IS_ERR(ipage)) अणु
				err = PTR_ERR(ipage);
				जाओ err_out;
			पूर्ण

			vsrc = kmap_atomic(ipage);
			vto = kmap_atomic(page);
			स_नकल(vto, vsrc + blkoff, map.m_plen);
			स_रखो(vto + map.m_plen, 0, PAGE_SIZE - map.m_plen);
			kunmap_atomic(vto);
			kunmap_atomic(vsrc);
			flush_dcache_page(page);

			SetPageUptodate(page);
			/* TODO: could we unlock the page earlier? */
			unlock_page(ipage);
			put_page(ipage);

			/* imply err = 0, see erofs_map_blocks */
			जाओ has_updated;
		पूर्ण

		/* pa must be block-aligned क्रम raw पढ़ोing */
		DBG_BUGON(erofs_blkoff(map.m_pa));

		/* max # of continuous pages */
		अगर (nblocks > DIV_ROUND_UP(map.m_plen, PAGE_SIZE))
			nblocks = DIV_ROUND_UP(map.m_plen, PAGE_SIZE);

		*eblks = bio_max_segs(nblocks);
		bio = bio_alloc(GFP_NOIO, *eblks);

		bio->bi_end_io = erofs_पढ़ोendio;
		bio_set_dev(bio, sb->s_bdev);
		bio->bi_iter.bi_sector = (sector_t)blknr <<
			LOG_SECTORS_PER_BLOCK;
		bio->bi_opf = REQ_OP_READ | (ra ? REQ_RAHEAD : 0);
	पूर्ण

	err = bio_add_page(bio, page, PAGE_SIZE, 0);
	/* out of the extent or bio is full */
	अगर (err < PAGE_SIZE)
		जाओ submit_bio_retry;
	--*eblks;
	*last_block = current_block;
	वापस bio;

err_out:
	/* क्रम sync पढ़ोing, set page error immediately */
	अगर (!ra) अणु
		SetPageError(page);
		ClearPageUptodate(page);
	पूर्ण
has_updated:
	unlock_page(page);

	/* अगर updated manually, continuous pages has a gap */
	अगर (bio)
		submit_bio(bio);
	वापस err ? ERR_PTR(err) : शून्य;
पूर्ण

/*
 * since we करोnt have ग_लिखो or truncate flows, so no inode
 * locking needs to be held at the moment.
 */
अटल पूर्णांक erofs_raw_access_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	erofs_off_t last_block;
	अचिन्हित पूर्णांक eblks;
	काष्ठा bio *bio;

	trace_erofs_पढ़ोpage(page, true);

	bio = erofs_पढ़ो_raw_page(शून्य, page->mapping,
				  page, &last_block, 1, &eblks, false);

	अगर (IS_ERR(bio))
		वापस PTR_ERR(bio);

	अगर (bio)
		submit_bio(bio);
	वापस 0;
पूर्ण

अटल व्योम erofs_raw_access_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	erofs_off_t last_block;
	अचिन्हित पूर्णांक eblks;
	काष्ठा bio *bio = शून्य;
	काष्ठा page *page;

	trace_erofs_पढ़ोpages(rac->mapping->host, पढ़ोahead_index(rac),
			पढ़ोahead_count(rac), true);

	जबतक ((page = पढ़ोahead_page(rac))) अणु
		prefetchw(&page->flags);

		bio = erofs_पढ़ो_raw_page(bio, rac->mapping, page, &last_block,
				पढ़ोahead_count(rac), &eblks, true);

		/* all the page errors are ignored when पढ़ोahead */
		अगर (IS_ERR(bio)) अणु
			pr_err("%s, readahead error at page %lu of nid %llu\n",
			       __func__, page->index,
			       EROFS_I(rac->mapping->host)->nid);

			bio = शून्य;
		पूर्ण

		put_page(page);
	पूर्ण

	अगर (bio)
		submit_bio(bio);
पूर्ण

अटल sector_t erofs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा erofs_map_blocks map = अणु
		.m_la = blknr_to_addr(block),
	पूर्ण;

	अगर (EROFS_I(inode)->datalayout == EROFS_INODE_FLAT_INLINE) अणु
		erofs_blk_t blks = i_size_पढ़ो(inode) >> LOG_BLOCK_SIZE;

		अगर (block >> LOG_SECTORS_PER_BLOCK >= blks)
			वापस 0;
	पूर्ण

	अगर (!erofs_map_blocks_flaपंचांगode(inode, &map, EROFS_GET_BLOCKS_RAW))
		वापस erofs_blknr(map.m_pa);

	वापस 0;
पूर्ण

/* क्रम uncompressed (aligned) files and raw access क्रम other files */
स्थिर काष्ठा address_space_operations erofs_raw_access_aops = अणु
	.पढ़ोpage = erofs_raw_access_पढ़ोpage,
	.पढ़ोahead = erofs_raw_access_पढ़ोahead,
	.bmap = erofs_bmap,
पूर्ण;

