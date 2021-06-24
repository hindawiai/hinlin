<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/fs/fat/cache.c
 *
 *  Written 1992,1993 by Werner Almesberger
 *
 *  Mar 1999. AV. Changed cache, so that it uses the starting cluster instead
 *	of inode number.
 *  May 1999. AV. Fixed the bogosity with FAT32 (पढ़ो "FAT28"). Fscking lusers.
 *  Copyright (C) 2012-2013 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/buffer_head.h>

#समावेश "exfat_raw.h"
#समावेश "exfat_fs.h"

#घोषणा EXFAT_MAX_CACHE		16

काष्ठा exfat_cache अणु
	काष्ठा list_head cache_list;
	अचिन्हित पूर्णांक nr_contig;	/* number of contiguous clusters */
	अचिन्हित पूर्णांक fcluster;	/* cluster number in the file. */
	अचिन्हित पूर्णांक dcluster;	/* cluster number on disk. */
पूर्ण;

काष्ठा exfat_cache_id अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक nr_contig;
	अचिन्हित पूर्णांक fcluster;
	अचिन्हित पूर्णांक dcluster;
पूर्ण;

अटल काष्ठा kmem_cache *exfat_cachep;

अटल व्योम exfat_cache_init_once(व्योम *c)
अणु
	काष्ठा exfat_cache *cache = (काष्ठा exfat_cache *)c;

	INIT_LIST_HEAD(&cache->cache_list);
पूर्ण

पूर्णांक exfat_cache_init(व्योम)
अणु
	exfat_cachep = kmem_cache_create("exfat_cache",
				माप(काष्ठा exfat_cache),
				0, SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD,
				exfat_cache_init_once);
	अगर (!exfat_cachep)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम exfat_cache_shutकरोwn(व्योम)
अणु
	अगर (!exfat_cachep)
		वापस;
	kmem_cache_destroy(exfat_cachep);
पूर्ण

अटल अंतरभूत काष्ठा exfat_cache *exfat_cache_alloc(व्योम)
अणु
	वापस kmem_cache_alloc(exfat_cachep, GFP_NOFS);
पूर्ण

अटल अंतरभूत व्योम exfat_cache_मुक्त(काष्ठा exfat_cache *cache)
अणु
	WARN_ON(!list_empty(&cache->cache_list));
	kmem_cache_मुक्त(exfat_cachep, cache);
पूर्ण

अटल अंतरभूत व्योम exfat_cache_update_lru(काष्ठा inode *inode,
		काष्ठा exfat_cache *cache)
अणु
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);

	अगर (ei->cache_lru.next != &cache->cache_list)
		list_move(&cache->cache_list, &ei->cache_lru);
पूर्ण

अटल अचिन्हित पूर्णांक exfat_cache_lookup(काष्ठा inode *inode,
		अचिन्हित पूर्णांक fclus, काष्ठा exfat_cache_id *cid,
		अचिन्हित पूर्णांक *cached_fclus, अचिन्हित पूर्णांक *cached_dclus)
अणु
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	अटल काष्ठा exfat_cache nohit = अणु .fcluster = 0, पूर्ण;
	काष्ठा exfat_cache *hit = &nohit, *p;
	अचिन्हित पूर्णांक offset = EXFAT_खातापूर्ण_CLUSTER;

	spin_lock(&ei->cache_lru_lock);
	list_क्रम_each_entry(p, &ei->cache_lru, cache_list) अणु
		/* Find the cache of "fclus" or nearest cache. */
		अगर (p->fcluster <= fclus && hit->fcluster < p->fcluster) अणु
			hit = p;
			अगर (hit->fcluster + hit->nr_contig < fclus) अणु
				offset = hit->nr_contig;
			पूर्ण अन्यथा अणु
				offset = fclus - hit->fcluster;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (hit != &nohit) अणु
		exfat_cache_update_lru(inode, hit);

		cid->id = ei->cache_valid_id;
		cid->nr_contig = hit->nr_contig;
		cid->fcluster = hit->fcluster;
		cid->dcluster = hit->dcluster;
		*cached_fclus = cid->fcluster + offset;
		*cached_dclus = cid->dcluster + offset;
	पूर्ण
	spin_unlock(&ei->cache_lru_lock);

	वापस offset;
पूर्ण

अटल काष्ठा exfat_cache *exfat_cache_merge(काष्ठा inode *inode,
		काष्ठा exfat_cache_id *new)
अणु
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	काष्ठा exfat_cache *p;

	list_क्रम_each_entry(p, &ei->cache_lru, cache_list) अणु
		/* Find the same part as "new" in cluster-chain. */
		अगर (p->fcluster == new->fcluster) अणु
			अगर (new->nr_contig > p->nr_contig)
				p->nr_contig = new->nr_contig;
			वापस p;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम exfat_cache_add(काष्ठा inode *inode,
		काष्ठा exfat_cache_id *new)
अणु
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	काष्ठा exfat_cache *cache, *पंचांगp;

	अगर (new->fcluster == EXFAT_खातापूर्ण_CLUSTER) /* dummy cache */
		वापस;

	spin_lock(&ei->cache_lru_lock);
	अगर (new->id != EXFAT_CACHE_VALID &&
	    new->id != ei->cache_valid_id)
		जाओ unlock;	/* this cache was invalidated */

	cache = exfat_cache_merge(inode, new);
	अगर (cache == शून्य) अणु
		अगर (ei->nr_caches < EXFAT_MAX_CACHE) अणु
			ei->nr_caches++;
			spin_unlock(&ei->cache_lru_lock);

			पंचांगp = exfat_cache_alloc();
			अगर (!पंचांगp) अणु
				spin_lock(&ei->cache_lru_lock);
				ei->nr_caches--;
				spin_unlock(&ei->cache_lru_lock);
				वापस;
			पूर्ण

			spin_lock(&ei->cache_lru_lock);
			cache = exfat_cache_merge(inode, new);
			अगर (cache != शून्य) अणु
				ei->nr_caches--;
				exfat_cache_मुक्त(पंचांगp);
				जाओ out_update_lru;
			पूर्ण
			cache = पंचांगp;
		पूर्ण अन्यथा अणु
			काष्ठा list_head *p = ei->cache_lru.prev;

			cache = list_entry(p,
					काष्ठा exfat_cache, cache_list);
		पूर्ण
		cache->fcluster = new->fcluster;
		cache->dcluster = new->dcluster;
		cache->nr_contig = new->nr_contig;
	पूर्ण
out_update_lru:
	exfat_cache_update_lru(inode, cache);
unlock:
	spin_unlock(&ei->cache_lru_lock);
पूर्ण

/*
 * Cache invalidation occurs rarely, thus the LRU chain is not updated. It
 * fixes itself after a जबतक.
 */
अटल व्योम __exfat_cache_inval_inode(काष्ठा inode *inode)
अणु
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	काष्ठा exfat_cache *cache;

	जबतक (!list_empty(&ei->cache_lru)) अणु
		cache = list_entry(ei->cache_lru.next,
				   काष्ठा exfat_cache, cache_list);
		list_del_init(&cache->cache_list);
		ei->nr_caches--;
		exfat_cache_मुक्त(cache);
	पूर्ण
	/* Update. The copy of caches beक्रमe this id is discarded. */
	ei->cache_valid_id++;
	अगर (ei->cache_valid_id == EXFAT_CACHE_VALID)
		ei->cache_valid_id++;
पूर्ण

व्योम exfat_cache_inval_inode(काष्ठा inode *inode)
अणु
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);

	spin_lock(&ei->cache_lru_lock);
	__exfat_cache_inval_inode(inode);
	spin_unlock(&ei->cache_lru_lock);
पूर्ण

अटल अंतरभूत पूर्णांक cache_contiguous(काष्ठा exfat_cache_id *cid,
		अचिन्हित पूर्णांक dclus)
अणु
	cid->nr_contig++;
	वापस cid->dcluster + cid->nr_contig == dclus;
पूर्ण

अटल अंतरभूत व्योम cache_init(काष्ठा exfat_cache_id *cid,
		अचिन्हित पूर्णांक fclus, अचिन्हित पूर्णांक dclus)
अणु
	cid->id = EXFAT_CACHE_VALID;
	cid->fcluster = fclus;
	cid->dcluster = dclus;
	cid->nr_contig = 0;
पूर्ण

पूर्णांक exfat_get_cluster(काष्ठा inode *inode, अचिन्हित पूर्णांक cluster,
		अचिन्हित पूर्णांक *fclus, अचिन्हित पूर्णांक *dclus,
		अचिन्हित पूर्णांक *last_dclus, पूर्णांक allow_eof)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	अचिन्हित पूर्णांक limit = sbi->num_clusters;
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	काष्ठा exfat_cache_id cid;
	अचिन्हित पूर्णांक content;

	अगर (ei->start_clu == EXFAT_FREE_CLUSTER) अणु
		exfat_fs_error(sb,
			"invalid access to exfat cache (entry 0x%08x)",
			ei->start_clu);
		वापस -EIO;
	पूर्ण

	*fclus = 0;
	*dclus = ei->start_clu;
	*last_dclus = *dclus;

	/*
	 * Don`t use exfat_cache अगर zero offset or non-cluster allocation
	 */
	अगर (cluster == 0 || *dclus == EXFAT_खातापूर्ण_CLUSTER)
		वापस 0;

	cache_init(&cid, EXFAT_खातापूर्ण_CLUSTER, EXFAT_खातापूर्ण_CLUSTER);

	अगर (exfat_cache_lookup(inode, cluster, &cid, fclus, dclus) ==
			EXFAT_खातापूर्ण_CLUSTER) अणु
		/*
		 * dummy, always not contiguous
		 * This is reinitialized by cache_init(), later.
		 */
		WARN_ON(cid.id != EXFAT_CACHE_VALID ||
			cid.fcluster != EXFAT_खातापूर्ण_CLUSTER ||
			cid.dcluster != EXFAT_खातापूर्ण_CLUSTER ||
			cid.nr_contig != 0);
	पूर्ण

	अगर (*fclus == cluster)
		वापस 0;

	जबतक (*fclus < cluster) अणु
		/* prevent the infinite loop of cluster chain */
		अगर (*fclus > limit) अणु
			exfat_fs_error(sb,
				"detected the cluster chain loop (i_pos %u)",
				(*fclus));
			वापस -EIO;
		पूर्ण

		अगर (exfat_ent_get(sb, *dclus, &content))
			वापस -EIO;

		*last_dclus = *dclus;
		*dclus = content;
		(*fclus)++;

		अगर (content == EXFAT_खातापूर्ण_CLUSTER) अणु
			अगर (!allow_eof) अणु
				exfat_fs_error(sb,
				       "invalid cluster chain (i_pos %u, last_clus 0x%08x is EOF)",
				       *fclus, (*last_dclus));
				वापस -EIO;
			पूर्ण

			अवरोध;
		पूर्ण

		अगर (!cache_contiguous(&cid, *dclus))
			cache_init(&cid, *fclus, *dclus);
	पूर्ण

	exfat_cache_add(inode, &cid);
	वापस 0;
पूर्ण
