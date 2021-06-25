<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Data verअगरication functions, i.e. hooks क्रम ->पढ़ोpages()
 *
 * Copyright 2019 Google LLC
 */

#समावेश "fsverity_private.h"

#समावेश <crypto/hash.h>
#समावेश <linux/bपन.स>
#समावेश <linux/ratelimit.h>

अटल काष्ठा workqueue_काष्ठा *fsverity_पढ़ो_workqueue;

/**
 * hash_at_level() - compute the location of the block's hash at the given level
 *
 * @params:	(in) the Merkle tree parameters
 * @dindex:	(in) the index of the data block being verअगरied
 * @level:	(in) the level of hash we want (0 is leaf level)
 * @hindex:	(out) the index of the hash block containing the wanted hash
 * @hoffset:	(out) the byte offset to the wanted hash within the hash block
 */
अटल व्योम hash_at_level(स्थिर काष्ठा merkle_tree_params *params,
			  pgoff_t dindex, अचिन्हित पूर्णांक level, pgoff_t *hindex,
			  अचिन्हित पूर्णांक *hoffset)
अणु
	pgoff_t position;

	/* Offset of the hash within the level's region, in hashes */
	position = dindex >> (level * params->log_arity);

	/* Index of the hash block in the tree overall */
	*hindex = params->level_start[level] + (position >> params->log_arity);

	/* Offset of the wanted hash (in bytes) within the hash block */
	*hoffset = (position & ((1 << params->log_arity) - 1)) <<
		   (params->log_blocksize - params->log_arity);
पूर्ण

/* Extract a hash from a hash page */
अटल व्योम extract_hash(काष्ठा page *hpage, अचिन्हित पूर्णांक hoffset,
			 अचिन्हित पूर्णांक hsize, u8 *out)
अणु
	व्योम *virt = kmap_atomic(hpage);

	स_नकल(out, virt + hoffset, hsize);
	kunmap_atomic(virt);
पूर्ण

अटल अंतरभूत पूर्णांक cmp_hashes(स्थिर काष्ठा fsverity_info *vi,
			     स्थिर u8 *want_hash, स्थिर u8 *real_hash,
			     pgoff_t index, पूर्णांक level)
अणु
	स्थिर अचिन्हित पूर्णांक hsize = vi->tree_params.digest_size;

	अगर (स_भेद(want_hash, real_hash, hsize) == 0)
		वापस 0;

	fsverity_err(vi->inode,
		     "FILE CORRUPTED! index=%lu, level=%d, want_hash=%s:%*phN, real_hash=%s:%*phN",
		     index, level,
		     vi->tree_params.hash_alg->name, hsize, want_hash,
		     vi->tree_params.hash_alg->name, hsize, real_hash);
	वापस -EBADMSG;
पूर्ण

/*
 * Verअगरy a single data page against the file's Merkle tree.
 *
 * In principle, we need to verअगरy the entire path to the root node.  However,
 * क्रम efficiency the fileप्रणाली may cache the hash pages.  Thereक्रमe we need
 * only ascend the tree until an alपढ़ोy-verअगरied page is seen, as indicated by
 * the PageChecked bit being set; then verअगरy the path to that page.
 *
 * This code currently only supports the हाल where the verity block size is
 * equal to PAGE_SIZE.  Doing otherwise would be possible but tricky, since we
 * wouldn't be able to use the PageChecked bit.
 *
 * Note that multiple processes may race to verअगरy a hash page and mark it
 * Checked, but it करोesn't matter; the result will be the same either way.
 *
 * Return: true अगर the page is valid, अन्यथा false.
 */
अटल bool verअगरy_page(काष्ठा inode *inode, स्थिर काष्ठा fsverity_info *vi,
			काष्ठा ahash_request *req, काष्ठा page *data_page,
			अचिन्हित दीर्घ level0_ra_pages)
अणु
	स्थिर काष्ठा merkle_tree_params *params = &vi->tree_params;
	स्थिर अचिन्हित पूर्णांक hsize = params->digest_size;
	स्थिर pgoff_t index = data_page->index;
	पूर्णांक level;
	u8 _want_hash[FS_VERITY_MAX_DIGEST_SIZE];
	स्थिर u8 *want_hash;
	u8 real_hash[FS_VERITY_MAX_DIGEST_SIZE];
	काष्ठा page *hpages[FS_VERITY_MAX_LEVELS];
	अचिन्हित पूर्णांक hoffsets[FS_VERITY_MAX_LEVELS];
	पूर्णांक err;

	अगर (WARN_ON_ONCE(!PageLocked(data_page) || PageUptodate(data_page)))
		वापस false;

	pr_debug_ratelimited("Verifying data page %lu...\n", index);

	/*
	 * Starting at the leaf level, ascend the tree saving hash pages aदीर्घ
	 * the way until we find a verअगरied hash page, indicated by PageChecked;
	 * or until we reach the root.
	 */
	क्रम (level = 0; level < params->num_levels; level++) अणु
		pgoff_t hindex;
		अचिन्हित पूर्णांक hoffset;
		काष्ठा page *hpage;

		hash_at_level(params, index, level, &hindex, &hoffset);

		pr_debug_ratelimited("Level %d: hindex=%lu, hoffset=%u\n",
				     level, hindex, hoffset);

		hpage = inode->i_sb->s_vop->पढ़ो_merkle_tree_page(inode, hindex,
				level == 0 ? level0_ra_pages : 0);
		अगर (IS_ERR(hpage)) अणु
			err = PTR_ERR(hpage);
			fsverity_err(inode,
				     "Error %d reading Merkle tree page %lu",
				     err, hindex);
			जाओ out;
		पूर्ण

		अगर (PageChecked(hpage)) अणु
			extract_hash(hpage, hoffset, hsize, _want_hash);
			want_hash = _want_hash;
			put_page(hpage);
			pr_debug_ratelimited("Hash page already checked, want %s:%*phN\n",
					     params->hash_alg->name,
					     hsize, want_hash);
			जाओ descend;
		पूर्ण
		pr_debug_ratelimited("Hash page not yet checked\n");
		hpages[level] = hpage;
		hoffsets[level] = hoffset;
	पूर्ण

	want_hash = vi->root_hash;
	pr_debug("Want root hash: %s:%*phN\n",
		 params->hash_alg->name, hsize, want_hash);
descend:
	/* Descend the tree verअगरying hash pages */
	क्रम (; level > 0; level--) अणु
		काष्ठा page *hpage = hpages[level - 1];
		अचिन्हित पूर्णांक hoffset = hoffsets[level - 1];

		err = fsverity_hash_page(params, inode, req, hpage, real_hash);
		अगर (err)
			जाओ out;
		err = cmp_hashes(vi, want_hash, real_hash, index, level - 1);
		अगर (err)
			जाओ out;
		SetPageChecked(hpage);
		extract_hash(hpage, hoffset, hsize, _want_hash);
		want_hash = _want_hash;
		put_page(hpage);
		pr_debug("Verified hash page at level %d, now want %s:%*phN\n",
			 level - 1, params->hash_alg->name, hsize, want_hash);
	पूर्ण

	/* Finally, verअगरy the data page */
	err = fsverity_hash_page(params, inode, req, data_page, real_hash);
	अगर (err)
		जाओ out;
	err = cmp_hashes(vi, want_hash, real_hash, index, -1);
out:
	क्रम (; level > 0; level--)
		put_page(hpages[level - 1]);

	वापस err == 0;
पूर्ण

/**
 * fsverity_verअगरy_page() - verअगरy a data page
 * @page: the page to verity
 *
 * Verअगरy a page that has just been पढ़ो from a verity file.  The page must be a
 * pagecache page that is still locked and not yet uptodate.
 *
 * Return: true अगर the page is valid, अन्यथा false.
 */
bool fsverity_verअगरy_page(काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	स्थिर काष्ठा fsverity_info *vi = inode->i_verity_info;
	काष्ठा ahash_request *req;
	bool valid;

	/* This allocation never fails, since it's mempool-backed. */
	req = fsverity_alloc_hash_request(vi->tree_params.hash_alg, GFP_NOFS);

	valid = verअगरy_page(inode, vi, req, page, 0);

	fsverity_मुक्त_hash_request(vi->tree_params.hash_alg, req);

	वापस valid;
पूर्ण
EXPORT_SYMBOL_GPL(fsverity_verअगरy_page);

#अगर_घोषित CONFIG_BLOCK
/**
 * fsverity_verअगरy_bio() - verअगरy a 'read' bio that has just completed
 * @bio: the bio to verअगरy
 *
 * Verअगरy a set of pages that have just been पढ़ो from a verity file.  The pages
 * must be pagecache pages that are still locked and not yet uptodate.  Pages
 * that fail verअगरication are set to the Error state.  Verअगरication is skipped
 * क्रम pages alपढ़ोy in the Error state, e.g. due to fscrypt decryption failure.
 *
 * This is a helper function क्रम use by the ->पढ़ोpages() method of fileप्रणालीs
 * that issue bios to पढ़ो data directly पूर्णांकo the page cache.  Fileप्रणालीs that
 * populate the page cache without issuing bios (e.g. non block-based
 * fileप्रणालीs) must instead call fsverity_verअगरy_page() directly on each page.
 * All fileप्रणालीs must also call fsverity_verअगरy_page() on holes.
 */
व्योम fsverity_verअगरy_bio(काष्ठा bio *bio)
अणु
	काष्ठा inode *inode = bio_first_page_all(bio)->mapping->host;
	स्थिर काष्ठा fsverity_info *vi = inode->i_verity_info;
	स्थिर काष्ठा merkle_tree_params *params = &vi->tree_params;
	काष्ठा ahash_request *req;
	काष्ठा bio_vec *bv;
	काष्ठा bvec_iter_all iter_all;
	अचिन्हित दीर्घ max_ra_pages = 0;

	/* This allocation never fails, since it's mempool-backed. */
	req = fsverity_alloc_hash_request(params->hash_alg, GFP_NOFS);

	अगर (bio->bi_opf & REQ_RAHEAD) अणु
		/*
		 * If this bio is क्रम data पढ़ोahead, then we also करो पढ़ोahead
		 * of the first (largest) level of the Merkle tree.  Namely,
		 * when a Merkle tree page is पढ़ो, we also try to piggy-back on
		 * some additional pages -- up to 1/4 the number of data pages.
		 *
		 * This improves sequential पढ़ो perक्रमmance, as it greatly
		 * reduces the number of I/O requests made to the Merkle tree.
		 */
		bio_क्रम_each_segment_all(bv, bio, iter_all)
			max_ra_pages++;
		max_ra_pages /= 4;
	पूर्ण

	bio_क्रम_each_segment_all(bv, bio, iter_all) अणु
		काष्ठा page *page = bv->bv_page;
		अचिन्हित दीर्घ level0_index = page->index >> params->log_arity;
		अचिन्हित दीर्घ level0_ra_pages =
			min(max_ra_pages, params->level0_blocks - level0_index);

		अगर (!PageError(page) &&
		    !verअगरy_page(inode, vi, req, page, level0_ra_pages))
			SetPageError(page);
	पूर्ण

	fsverity_मुक्त_hash_request(params->hash_alg, req);
पूर्ण
EXPORT_SYMBOL_GPL(fsverity_verअगरy_bio);
#पूर्ण_अगर /* CONFIG_BLOCK */

/**
 * fsverity_enqueue_verअगरy_work() - enqueue work on the fs-verity workqueue
 * @work: the work to enqueue
 *
 * Enqueue verअगरication work क्रम asynchronous processing.
 */
व्योम fsverity_enqueue_verअगरy_work(काष्ठा work_काष्ठा *work)
अणु
	queue_work(fsverity_पढ़ो_workqueue, work);
पूर्ण
EXPORT_SYMBOL_GPL(fsverity_enqueue_verअगरy_work);

पूर्णांक __init fsverity_init_workqueue(व्योम)
अणु
	/*
	 * Use an unbound workqueue to allow bios to be verअगरied in parallel
	 * even when they happen to complete on the same CPU.  This sacrअगरices
	 * locality, but it's worthजबतक since hashing is CPU-पूर्णांकensive.
	 *
	 * Also use a high-priority workqueue to prioritize verअगरication work,
	 * which blocks पढ़ोs from completing, over regular application tasks.
	 */
	fsverity_पढ़ो_workqueue = alloc_workqueue("fsverity_read_queue",
						  WQ_UNBOUND | WQ_HIGHPRI,
						  num_online_cpus());
	अगर (!fsverity_पढ़ो_workqueue)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम __init fsverity_निकास_workqueue(व्योम)
अणु
	destroy_workqueue(fsverity_पढ़ो_workqueue);
	fsverity_पढ़ो_workqueue = शून्य;
पूर्ण
