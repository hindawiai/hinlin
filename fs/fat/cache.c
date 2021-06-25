<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/fat/cache.c
 *
 *  Written 1992,1993 by Werner Almesberger
 *
 *  Mar 1999. AV. Changed cache, so that it uses the starting cluster instead
 *	of inode number.
 *  May 1999. AV. Fixed the bogosity with FAT32 (पढ़ो "FAT28"). Fscking lusers.
 */

#समावेश <linux/slab.h>
#समावेश "fat.h"

/* this must be > 0. */
#घोषणा FAT_MAX_CACHE	8

काष्ठा fat_cache अणु
	काष्ठा list_head cache_list;
	पूर्णांक nr_contig;	/* number of contiguous clusters */
	पूर्णांक fcluster;	/* cluster number in the file. */
	पूर्णांक dcluster;	/* cluster number on disk. */
पूर्ण;

काष्ठा fat_cache_id अणु
	अचिन्हित पूर्णांक id;
	पूर्णांक nr_contig;
	पूर्णांक fcluster;
	पूर्णांक dcluster;
पूर्ण;

अटल अंतरभूत पूर्णांक fat_max_cache(काष्ठा inode *inode)
अणु
	वापस FAT_MAX_CACHE;
पूर्ण

अटल काष्ठा kmem_cache *fat_cache_cachep;

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा fat_cache *cache = (काष्ठा fat_cache *)foo;

	INIT_LIST_HEAD(&cache->cache_list);
पूर्ण

पूर्णांक __init fat_cache_init(व्योम)
अणु
	fat_cache_cachep = kmem_cache_create("fat_cache",
				माप(काष्ठा fat_cache),
				0, SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD,
				init_once);
	अगर (fat_cache_cachep == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम fat_cache_destroy(व्योम)
अणु
	kmem_cache_destroy(fat_cache_cachep);
पूर्ण

अटल अंतरभूत काष्ठा fat_cache *fat_cache_alloc(काष्ठा inode *inode)
अणु
	वापस kmem_cache_alloc(fat_cache_cachep, GFP_NOFS);
पूर्ण

अटल अंतरभूत व्योम fat_cache_मुक्त(काष्ठा fat_cache *cache)
अणु
	BUG_ON(!list_empty(&cache->cache_list));
	kmem_cache_मुक्त(fat_cache_cachep, cache);
पूर्ण

अटल अंतरभूत व्योम fat_cache_update_lru(काष्ठा inode *inode,
					काष्ठा fat_cache *cache)
अणु
	अगर (MSDOS_I(inode)->cache_lru.next != &cache->cache_list)
		list_move(&cache->cache_list, &MSDOS_I(inode)->cache_lru);
पूर्ण

अटल पूर्णांक fat_cache_lookup(काष्ठा inode *inode, पूर्णांक fclus,
			    काष्ठा fat_cache_id *cid,
			    पूर्णांक *cached_fclus, पूर्णांक *cached_dclus)
अणु
	अटल काष्ठा fat_cache nohit = अणु .fcluster = 0, पूर्ण;

	काष्ठा fat_cache *hit = &nohit, *p;
	पूर्णांक offset = -1;

	spin_lock(&MSDOS_I(inode)->cache_lru_lock);
	list_क्रम_each_entry(p, &MSDOS_I(inode)->cache_lru, cache_list) अणु
		/* Find the cache of "fclus" or nearest cache. */
		अगर (p->fcluster <= fclus && hit->fcluster < p->fcluster) अणु
			hit = p;
			अगर ((hit->fcluster + hit->nr_contig) < fclus) अणु
				offset = hit->nr_contig;
			पूर्ण अन्यथा अणु
				offset = fclus - hit->fcluster;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (hit != &nohit) अणु
		fat_cache_update_lru(inode, hit);

		cid->id = MSDOS_I(inode)->cache_valid_id;
		cid->nr_contig = hit->nr_contig;
		cid->fcluster = hit->fcluster;
		cid->dcluster = hit->dcluster;
		*cached_fclus = cid->fcluster + offset;
		*cached_dclus = cid->dcluster + offset;
	पूर्ण
	spin_unlock(&MSDOS_I(inode)->cache_lru_lock);

	वापस offset;
पूर्ण

अटल काष्ठा fat_cache *fat_cache_merge(काष्ठा inode *inode,
					 काष्ठा fat_cache_id *new)
अणु
	काष्ठा fat_cache *p;

	list_क्रम_each_entry(p, &MSDOS_I(inode)->cache_lru, cache_list) अणु
		/* Find the same part as "new" in cluster-chain. */
		अगर (p->fcluster == new->fcluster) अणु
			BUG_ON(p->dcluster != new->dcluster);
			अगर (new->nr_contig > p->nr_contig)
				p->nr_contig = new->nr_contig;
			वापस p;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम fat_cache_add(काष्ठा inode *inode, काष्ठा fat_cache_id *new)
अणु
	काष्ठा fat_cache *cache, *पंचांगp;

	अगर (new->fcluster == -1) /* dummy cache */
		वापस;

	spin_lock(&MSDOS_I(inode)->cache_lru_lock);
	अगर (new->id != FAT_CACHE_VALID &&
	    new->id != MSDOS_I(inode)->cache_valid_id)
		जाओ out;	/* this cache was invalidated */

	cache = fat_cache_merge(inode, new);
	अगर (cache == शून्य) अणु
		अगर (MSDOS_I(inode)->nr_caches < fat_max_cache(inode)) अणु
			MSDOS_I(inode)->nr_caches++;
			spin_unlock(&MSDOS_I(inode)->cache_lru_lock);

			पंचांगp = fat_cache_alloc(inode);
			अगर (!पंचांगp) अणु
				spin_lock(&MSDOS_I(inode)->cache_lru_lock);
				MSDOS_I(inode)->nr_caches--;
				spin_unlock(&MSDOS_I(inode)->cache_lru_lock);
				वापस;
			पूर्ण

			spin_lock(&MSDOS_I(inode)->cache_lru_lock);
			cache = fat_cache_merge(inode, new);
			अगर (cache != शून्य) अणु
				MSDOS_I(inode)->nr_caches--;
				fat_cache_मुक्त(पंचांगp);
				जाओ out_update_lru;
			पूर्ण
			cache = पंचांगp;
		पूर्ण अन्यथा अणु
			काष्ठा list_head *p = MSDOS_I(inode)->cache_lru.prev;
			cache = list_entry(p, काष्ठा fat_cache, cache_list);
		पूर्ण
		cache->fcluster = new->fcluster;
		cache->dcluster = new->dcluster;
		cache->nr_contig = new->nr_contig;
	पूर्ण
out_update_lru:
	fat_cache_update_lru(inode, cache);
out:
	spin_unlock(&MSDOS_I(inode)->cache_lru_lock);
पूर्ण

/*
 * Cache invalidation occurs rarely, thus the LRU chain is not updated. It
 * fixes itself after a जबतक.
 */
अटल व्योम __fat_cache_inval_inode(काष्ठा inode *inode)
अणु
	काष्ठा msकरोs_inode_info *i = MSDOS_I(inode);
	काष्ठा fat_cache *cache;

	जबतक (!list_empty(&i->cache_lru)) अणु
		cache = list_entry(i->cache_lru.next,
				   काष्ठा fat_cache, cache_list);
		list_del_init(&cache->cache_list);
		i->nr_caches--;
		fat_cache_मुक्त(cache);
	पूर्ण
	/* Update. The copy of caches beक्रमe this id is discarded. */
	i->cache_valid_id++;
	अगर (i->cache_valid_id == FAT_CACHE_VALID)
		i->cache_valid_id++;
पूर्ण

व्योम fat_cache_inval_inode(काष्ठा inode *inode)
अणु
	spin_lock(&MSDOS_I(inode)->cache_lru_lock);
	__fat_cache_inval_inode(inode);
	spin_unlock(&MSDOS_I(inode)->cache_lru_lock);
पूर्ण

अटल अंतरभूत पूर्णांक cache_contiguous(काष्ठा fat_cache_id *cid, पूर्णांक dclus)
अणु
	cid->nr_contig++;
	वापस ((cid->dcluster + cid->nr_contig) == dclus);
पूर्ण

अटल अंतरभूत व्योम cache_init(काष्ठा fat_cache_id *cid, पूर्णांक fclus, पूर्णांक dclus)
अणु
	cid->id = FAT_CACHE_VALID;
	cid->fcluster = fclus;
	cid->dcluster = dclus;
	cid->nr_contig = 0;
पूर्ण

पूर्णांक fat_get_cluster(काष्ठा inode *inode, पूर्णांक cluster, पूर्णांक *fclus, पूर्णांक *dclus)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	स्थिर पूर्णांक limit = sb->s_maxbytes >> sbi->cluster_bits;
	काष्ठा fat_entry fatent;
	काष्ठा fat_cache_id cid;
	पूर्णांक nr;

	BUG_ON(MSDOS_I(inode)->i_start == 0);

	*fclus = 0;
	*dclus = MSDOS_I(inode)->i_start;
	अगर (!fat_valid_entry(sbi, *dclus)) अणु
		fat_fs_error_ratelimit(sb,
			"%s: invalid start cluster (i_pos %lld, start %08x)",
			__func__, MSDOS_I(inode)->i_pos, *dclus);
		वापस -EIO;
	पूर्ण
	अगर (cluster == 0)
		वापस 0;

	अगर (fat_cache_lookup(inode, cluster, &cid, fclus, dclus) < 0) अणु
		/*
		 * dummy, always not contiguous
		 * This is reinitialized by cache_init(), later.
		 */
		cache_init(&cid, -1, -1);
	पूर्ण

	fatent_init(&fatent);
	जबतक (*fclus < cluster) अणु
		/* prevent the infinite loop of cluster chain */
		अगर (*fclus > limit) अणु
			fat_fs_error_ratelimit(sb,
				"%s: detected the cluster chain loop (i_pos %lld)",
				__func__, MSDOS_I(inode)->i_pos);
			nr = -EIO;
			जाओ out;
		पूर्ण

		nr = fat_ent_पढ़ो(inode, &fatent, *dclus);
		अगर (nr < 0)
			जाओ out;
		अन्यथा अगर (nr == FAT_ENT_FREE) अणु
			fat_fs_error_ratelimit(sb,
				"%s: invalid cluster chain (i_pos %lld)",
				__func__, MSDOS_I(inode)->i_pos);
			nr = -EIO;
			जाओ out;
		पूर्ण अन्यथा अगर (nr == FAT_ENT_खातापूर्ण) अणु
			fat_cache_add(inode, &cid);
			जाओ out;
		पूर्ण
		(*fclus)++;
		*dclus = nr;
		अगर (!cache_contiguous(&cid, *dclus))
			cache_init(&cid, *fclus, *dclus);
	पूर्ण
	nr = 0;
	fat_cache_add(inode, &cid);
out:
	fatent_brअन्यथा(&fatent);
	वापस nr;
पूर्ण

अटल पूर्णांक fat_bmap_cluster(काष्ठा inode *inode, पूर्णांक cluster)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक ret, fclus, dclus;

	अगर (MSDOS_I(inode)->i_start == 0)
		वापस 0;

	ret = fat_get_cluster(inode, cluster, &fclus, &dclus);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret == FAT_ENT_खातापूर्ण) अणु
		fat_fs_error(sb, "%s: request beyond EOF (i_pos %lld)",
			     __func__, MSDOS_I(inode)->i_pos);
		वापस -EIO;
	पूर्ण
	वापस dclus;
पूर्ण

पूर्णांक fat_get_mapped_cluster(काष्ठा inode *inode, sector_t sector,
			   sector_t last_block,
			   अचिन्हित दीर्घ *mapped_blocks, sector_t *bmap)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	पूर्णांक cluster, offset;

	cluster = sector >> (sbi->cluster_bits - sb->s_blocksize_bits);
	offset  = sector & (sbi->sec_per_clus - 1);
	cluster = fat_bmap_cluster(inode, cluster);
	अगर (cluster < 0)
		वापस cluster;
	अन्यथा अगर (cluster) अणु
		*bmap = fat_clus_to_blknr(sbi, cluster) + offset;
		*mapped_blocks = sbi->sec_per_clus - offset;
		अगर (*mapped_blocks > last_block - sector)
			*mapped_blocks = last_block - sector;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक is_exceed_eof(काष्ठा inode *inode, sector_t sector,
			 sector_t *last_block, पूर्णांक create)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	स्थिर अचिन्हित दीर्घ blocksize = sb->s_blocksize;
	स्थिर अचिन्हित अक्षर blocksize_bits = sb->s_blocksize_bits;

	*last_block = (i_size_पढ़ो(inode) + (blocksize - 1)) >> blocksize_bits;
	अगर (sector >= *last_block) अणु
		अगर (!create)
			वापस 1;

		/*
		 * ->mmu_निजी can access on only allocation path.
		 * (caller must hold ->i_mutex)
		 */
		*last_block = (MSDOS_I(inode)->mmu_निजी + (blocksize - 1))
			>> blocksize_bits;
		अगर (sector >= *last_block)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक fat_bmap(काष्ठा inode *inode, sector_t sector, sector_t *phys,
	     अचिन्हित दीर्घ *mapped_blocks, पूर्णांक create, bool from_bmap)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(inode->i_sb);
	sector_t last_block;

	*phys = 0;
	*mapped_blocks = 0;
	अगर (!is_fat32(sbi) && (inode->i_ino == MSDOS_ROOT_INO)) अणु
		अगर (sector < (sbi->dir_entries >> sbi->dir_per_block_bits)) अणु
			*phys = sector + sbi->dir_start;
			*mapped_blocks = 1;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (!from_bmap) अणु
		अगर (is_exceed_eof(inode, sector, &last_block, create))
			वापस 0;
	पूर्ण अन्यथा अणु
		last_block = inode->i_blocks >>
				(inode->i_sb->s_blocksize_bits - 9);
		अगर (sector >= last_block)
			वापस 0;
	पूर्ण

	वापस fat_get_mapped_cluster(inode, sector, last_block, mapped_blocks,
				      phys);
पूर्ण
