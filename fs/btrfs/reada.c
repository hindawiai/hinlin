<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 STRATO.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश "ctree.h"
#समावेश "volumes.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "dev-replace.h"
#समावेश "block-group.h"

#अघोषित DEBUG

/*
 * This is the implementation क्रम the generic पढ़ो ahead framework.
 *
 * To trigger a पढ़ोahead, btrfs_पढ़ोa_add must be called. It will start
 * a पढ़ो ahead क्रम the given range [start, end) on tree root. The वापसed
 * handle can either be used to रुको on the पढ़ोahead to finish
 * (btrfs_पढ़ोa_रुको), or to send it to the background (btrfs_पढ़ोa_detach).
 *
 * The पढ़ो ahead works as follows:
 * On btrfs_पढ़ोa_add, the root of the tree is inserted पूर्णांकo a radix_tree.
 * पढ़ोa_start_machine will then search क्रम extents to prefetch and trigger
 * some पढ़ोs. When a पढ़ो finishes क्रम a node, all contained node/leaf
 * poपूर्णांकers that lie in the given range will also be enqueued. The पढ़ोs will
 * be triggered in sequential order, thus giving a big win over a naive
 * क्रमागतeration. It will also make use of multi-device layouts. Each disk
 * will have its on पढ़ो poपूर्णांकer and all disks will by utilized in parallel.
 * Also will no two disks पढ़ो both sides of a mirror simultaneously, as this
 * would waste seeking capacity. Instead both disks will पढ़ो dअगरferent parts
 * of the fileप्रणाली.
 * Any number of पढ़ोaheads can be started in parallel. The पढ़ो order will be
 * determined globally, i.e. 2 parallel पढ़ोaheads will normally finish faster
 * than the 2 started one after another.
 */

#घोषणा MAX_IN_FLIGHT 6

काष्ठा पढ़ोa_extctl अणु
	काष्ठा list_head	list;
	काष्ठा पढ़ोa_control	*rc;
	u64			generation;
पूर्ण;

काष्ठा पढ़ोa_extent अणु
	u64			logical;
	u64			owner_root;
	काष्ठा btrfs_key	top;
	काष्ठा list_head	extctl;
	पूर्णांक 			refcnt;
	spinlock_t		lock;
	काष्ठा पढ़ोa_zone	*zones[BTRFS_MAX_MIRRORS];
	पूर्णांक			nzones;
	पूर्णांक			scheduled;
	पूर्णांक			level;
पूर्ण;

काष्ठा पढ़ोa_zone अणु
	u64			start;
	u64			end;
	u64			elems;
	काष्ठा list_head	list;
	spinlock_t		lock;
	पूर्णांक			locked;
	काष्ठा btrfs_device	*device;
	काष्ठा btrfs_device	*devs[BTRFS_MAX_MIRRORS]; /* full list, incl
							   * self */
	पूर्णांक			ndevs;
	काष्ठा kref		refcnt;
पूर्ण;

काष्ठा पढ़ोa_machine_work अणु
	काष्ठा btrfs_work	work;
	काष्ठा btrfs_fs_info	*fs_info;
पूर्ण;

अटल व्योम पढ़ोa_extent_put(काष्ठा btrfs_fs_info *, काष्ठा पढ़ोa_extent *);
अटल व्योम पढ़ोa_control_release(काष्ठा kref *kref);
अटल व्योम पढ़ोa_zone_release(काष्ठा kref *kref);
अटल व्योम पढ़ोa_start_machine(काष्ठा btrfs_fs_info *fs_info);
अटल व्योम __पढ़ोa_start_machine(काष्ठा btrfs_fs_info *fs_info);

अटल पूर्णांक पढ़ोa_add_block(काष्ठा पढ़ोa_control *rc, u64 logical,
			   काष्ठा btrfs_key *top, u64 owner_root,
			   u64 generation, पूर्णांक level);

/* recurses */
/* in हाल of err, eb might be शून्य */
अटल व्योम __पढ़ोahead_hook(काष्ठा btrfs_fs_info *fs_info,
			     काष्ठा पढ़ोa_extent *re, काष्ठा extent_buffer *eb,
			     पूर्णांक err)
अणु
	पूर्णांक nritems;
	पूर्णांक i;
	u64 bytenr;
	u64 generation;
	काष्ठा list_head list;

	spin_lock(&re->lock);
	/*
	 * just take the full list from the extent. afterwards we
	 * करोn't need the lock anymore
	 */
	list_replace_init(&re->extctl, &list);
	re->scheduled = 0;
	spin_unlock(&re->lock);

	/*
	 * this is the error हाल, the extent buffer has not been
	 * पढ़ो correctly. We won't access anything from it and
	 * just cleanup our data काष्ठाures. Effectively this will
	 * cut the branch below this node from पढ़ो ahead.
	 */
	अगर (err)
		जाओ cleanup;

	/*
	 * FIXME: currently we just set nritems to 0 अगर this is a leaf,
	 * effectively ignoring the content. In a next step we could
	 * trigger more पढ़ोahead depending from the content, e.g.
	 * fetch the checksums क्रम the extents in the leaf.
	 */
	अगर (!btrfs_header_level(eb))
		जाओ cleanup;

	nritems = btrfs_header_nritems(eb);
	generation = btrfs_header_generation(eb);
	क्रम (i = 0; i < nritems; i++) अणु
		काष्ठा पढ़ोa_extctl *rec;
		u64 n_gen;
		काष्ठा btrfs_key key;
		काष्ठा btrfs_key next_key;

		btrfs_node_key_to_cpu(eb, &key, i);
		अगर (i + 1 < nritems)
			btrfs_node_key_to_cpu(eb, &next_key, i + 1);
		अन्यथा
			next_key = re->top;
		bytenr = btrfs_node_blockptr(eb, i);
		n_gen = btrfs_node_ptr_generation(eb, i);

		list_क्रम_each_entry(rec, &list, list) अणु
			काष्ठा पढ़ोa_control *rc = rec->rc;

			/*
			 * अगर the generation करोesn't match, just ignore this
			 * extctl. This will probably cut off a branch from
			 * prefetch. Alternatively one could start a new (sub-)
			 * prefetch क्रम this branch, starting again from root.
			 * FIXME: move the generation check out of this loop
			 */
#अगर_घोषित DEBUG
			अगर (rec->generation != generation) अणु
				btrfs_debug(fs_info,
					    "generation mismatch for (%llu,%d,%llu) %llu != %llu",
					    key.objectid, key.type, key.offset,
					    rec->generation, generation);
			पूर्ण
#पूर्ण_अगर
			अगर (rec->generation == generation &&
			    btrfs_comp_cpu_keys(&key, &rc->key_end) < 0 &&
			    btrfs_comp_cpu_keys(&next_key, &rc->key_start) > 0)
				पढ़ोa_add_block(rc, bytenr, &next_key,
						btrfs_header_owner(eb), n_gen,
						btrfs_header_level(eb) - 1);
		पूर्ण
	पूर्ण

cleanup:
	/*
	 * मुक्त extctl records
	 */
	जबतक (!list_empty(&list)) अणु
		काष्ठा पढ़ोa_control *rc;
		काष्ठा पढ़ोa_extctl *rec;

		rec = list_first_entry(&list, काष्ठा पढ़ोa_extctl, list);
		list_del(&rec->list);
		rc = rec->rc;
		kमुक्त(rec);

		kref_get(&rc->refcnt);
		अगर (atomic_dec_and_test(&rc->elems)) अणु
			kref_put(&rc->refcnt, पढ़ोa_control_release);
			wake_up(&rc->रुको);
		पूर्ण
		kref_put(&rc->refcnt, पढ़ोa_control_release);

		पढ़ोa_extent_put(fs_info, re);	/* one ref क्रम each entry */
	पूर्ण

	वापस;
पूर्ण

पूर्णांक btree_पढ़ोahead_hook(काष्ठा extent_buffer *eb, पूर्णांक err)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	पूर्णांक ret = 0;
	काष्ठा पढ़ोa_extent *re;

	/* find extent */
	spin_lock(&fs_info->पढ़ोa_lock);
	re = radix_tree_lookup(&fs_info->पढ़ोa_tree,
			       eb->start >> fs_info->sectorsize_bits);
	अगर (re)
		re->refcnt++;
	spin_unlock(&fs_info->पढ़ोa_lock);
	अगर (!re) अणु
		ret = -1;
		जाओ start_machine;
	पूर्ण

	__पढ़ोahead_hook(fs_info, re, eb, err);
	पढ़ोa_extent_put(fs_info, re);	/* our ref */

start_machine:
	पढ़ोa_start_machine(fs_info);
	वापस ret;
पूर्ण

अटल काष्ठा पढ़ोa_zone *पढ़ोa_find_zone(काष्ठा btrfs_device *dev, u64 logical,
					  काष्ठा btrfs_bio *bbio)
अणु
	काष्ठा btrfs_fs_info *fs_info = dev->fs_info;
	पूर्णांक ret;
	काष्ठा पढ़ोa_zone *zone;
	काष्ठा btrfs_block_group *cache = शून्य;
	u64 start;
	u64 end;
	पूर्णांक i;

	zone = शून्य;
	spin_lock(&fs_info->पढ़ोa_lock);
	ret = radix_tree_gang_lookup(&dev->पढ़ोa_zones, (व्योम **)&zone,
				     logical >> fs_info->sectorsize_bits, 1);
	अगर (ret == 1 && logical >= zone->start && logical <= zone->end) अणु
		kref_get(&zone->refcnt);
		spin_unlock(&fs_info->पढ़ोa_lock);
		वापस zone;
	पूर्ण

	spin_unlock(&fs_info->पढ़ोa_lock);

	cache = btrfs_lookup_block_group(fs_info, logical);
	अगर (!cache)
		वापस शून्य;

	start = cache->start;
	end = start + cache->length - 1;
	btrfs_put_block_group(cache);

	zone = kzalloc(माप(*zone), GFP_KERNEL);
	अगर (!zone)
		वापस शून्य;

	ret = radix_tree_preload(GFP_KERNEL);
	अगर (ret) अणु
		kमुक्त(zone);
		वापस शून्य;
	पूर्ण

	zone->start = start;
	zone->end = end;
	INIT_LIST_HEAD(&zone->list);
	spin_lock_init(&zone->lock);
	zone->locked = 0;
	kref_init(&zone->refcnt);
	zone->elems = 0;
	zone->device = dev; /* our device always sits at index 0 */
	क्रम (i = 0; i < bbio->num_stripes; ++i) अणु
		/* bounds have alपढ़ोy been checked */
		zone->devs[i] = bbio->stripes[i].dev;
	पूर्ण
	zone->ndevs = bbio->num_stripes;

	spin_lock(&fs_info->पढ़ोa_lock);
	ret = radix_tree_insert(&dev->पढ़ोa_zones,
			(अचिन्हित दीर्घ)(zone->end >> fs_info->sectorsize_bits),
			zone);

	अगर (ret == -EEXIST) अणु
		kमुक्त(zone);
		ret = radix_tree_gang_lookup(&dev->पढ़ोa_zones, (व्योम **)&zone,
					logical >> fs_info->sectorsize_bits, 1);
		अगर (ret == 1 && logical >= zone->start && logical <= zone->end)
			kref_get(&zone->refcnt);
		अन्यथा
			zone = शून्य;
	पूर्ण
	spin_unlock(&fs_info->पढ़ोa_lock);
	radix_tree_preload_end();

	वापस zone;
पूर्ण

अटल काष्ठा पढ़ोa_extent *पढ़ोa_find_extent(काष्ठा btrfs_fs_info *fs_info,
					      u64 logical,
					      काष्ठा btrfs_key *top,
					      u64 owner_root, पूर्णांक level)
अणु
	पूर्णांक ret;
	काष्ठा पढ़ोa_extent *re = शून्य;
	काष्ठा पढ़ोa_extent *re_exist = शून्य;
	काष्ठा btrfs_bio *bbio = शून्य;
	काष्ठा btrfs_device *dev;
	काष्ठा btrfs_device *prev_dev;
	u64 length;
	पूर्णांक real_stripes;
	पूर्णांक nzones = 0;
	अचिन्हित दीर्घ index = logical >> fs_info->sectorsize_bits;
	पूर्णांक dev_replace_is_ongoing;
	पूर्णांक have_zone = 0;

	spin_lock(&fs_info->पढ़ोa_lock);
	re = radix_tree_lookup(&fs_info->पढ़ोa_tree, index);
	अगर (re)
		re->refcnt++;
	spin_unlock(&fs_info->पढ़ोa_lock);

	अगर (re)
		वापस re;

	re = kzalloc(माप(*re), GFP_KERNEL);
	अगर (!re)
		वापस शून्य;

	re->logical = logical;
	re->top = *top;
	INIT_LIST_HEAD(&re->extctl);
	spin_lock_init(&re->lock);
	re->refcnt = 1;
	re->owner_root = owner_root;
	re->level = level;

	/*
	 * map block
	 */
	length = fs_info->nodesize;
	ret = btrfs_map_block(fs_info, BTRFS_MAP_GET_READ_MIRRORS, logical,
			&length, &bbio, 0);
	अगर (ret || !bbio || length < fs_info->nodesize)
		जाओ error;

	अगर (bbio->num_stripes > BTRFS_MAX_MIRRORS) अणु
		btrfs_err(fs_info,
			   "readahead: more than %d copies not supported",
			   BTRFS_MAX_MIRRORS);
		जाओ error;
	पूर्ण

	real_stripes = bbio->num_stripes - bbio->num_tgtdevs;
	क्रम (nzones = 0; nzones < real_stripes; ++nzones) अणु
		काष्ठा पढ़ोa_zone *zone;

		dev = bbio->stripes[nzones].dev;

		/* cannot पढ़ो ahead on missing device. */
		अगर (!dev->bdev)
			जारी;

		zone = पढ़ोa_find_zone(dev, logical, bbio);
		अगर (!zone)
			जारी;

		re->zones[re->nzones++] = zone;
		spin_lock(&zone->lock);
		अगर (!zone->elems)
			kref_get(&zone->refcnt);
		++zone->elems;
		spin_unlock(&zone->lock);
		spin_lock(&fs_info->पढ़ोa_lock);
		kref_put(&zone->refcnt, पढ़ोa_zone_release);
		spin_unlock(&fs_info->पढ़ोa_lock);
	पूर्ण
	अगर (re->nzones == 0) अणु
		/* not a single zone found, error and out */
		जाओ error;
	पूर्ण

	/* Insert extent in पढ़ोa tree + all per-device trees, all or nothing */
	करोwn_पढ़ो(&fs_info->dev_replace.rwsem);
	ret = radix_tree_preload(GFP_KERNEL);
	अगर (ret) अणु
		up_पढ़ो(&fs_info->dev_replace.rwsem);
		जाओ error;
	पूर्ण

	spin_lock(&fs_info->पढ़ोa_lock);
	ret = radix_tree_insert(&fs_info->पढ़ोa_tree, index, re);
	अगर (ret == -EEXIST) अणु
		re_exist = radix_tree_lookup(&fs_info->पढ़ोa_tree, index);
		re_exist->refcnt++;
		spin_unlock(&fs_info->पढ़ोa_lock);
		radix_tree_preload_end();
		up_पढ़ो(&fs_info->dev_replace.rwsem);
		जाओ error;
	पूर्ण
	अगर (ret) अणु
		spin_unlock(&fs_info->पढ़ोa_lock);
		radix_tree_preload_end();
		up_पढ़ो(&fs_info->dev_replace.rwsem);
		जाओ error;
	पूर्ण
	radix_tree_preload_end();
	prev_dev = शून्य;
	dev_replace_is_ongoing = btrfs_dev_replace_is_ongoing(
			&fs_info->dev_replace);
	क्रम (nzones = 0; nzones < re->nzones; ++nzones) अणु
		dev = re->zones[nzones]->device;

		अगर (dev == prev_dev) अणु
			/*
			 * in हाल of DUP, just add the first zone. As both
			 * are on the same device, there's nothing to gain
			 * from adding both.
			 * Also, it wouldn't work, as the tree is per device
			 * and adding would fail with EEXIST
			 */
			जारी;
		पूर्ण
		अगर (!dev->bdev)
			जारी;

		अगर (test_bit(BTRFS_DEV_STATE_NO_READA, &dev->dev_state))
			जारी;

		अगर (dev_replace_is_ongoing &&
		    dev == fs_info->dev_replace.tgtdev) अणु
			/*
			 * as this device is selected क्रम पढ़ोing only as
			 * a last resort, skip it क्रम पढ़ो ahead.
			 */
			जारी;
		पूर्ण
		prev_dev = dev;
		ret = radix_tree_insert(&dev->पढ़ोa_extents, index, re);
		अगर (ret) अणु
			जबतक (--nzones >= 0) अणु
				dev = re->zones[nzones]->device;
				BUG_ON(dev == शून्य);
				/* ignore whether the entry was inserted */
				radix_tree_delete(&dev->पढ़ोa_extents, index);
			पूर्ण
			radix_tree_delete(&fs_info->पढ़ोa_tree, index);
			spin_unlock(&fs_info->पढ़ोa_lock);
			up_पढ़ो(&fs_info->dev_replace.rwsem);
			जाओ error;
		पूर्ण
		have_zone = 1;
	पूर्ण
	अगर (!have_zone)
		radix_tree_delete(&fs_info->पढ़ोa_tree, index);
	spin_unlock(&fs_info->पढ़ोa_lock);
	up_पढ़ो(&fs_info->dev_replace.rwsem);

	अगर (!have_zone)
		जाओ error;

	btrfs_put_bbio(bbio);
	वापस re;

error:
	क्रम (nzones = 0; nzones < re->nzones; ++nzones) अणु
		काष्ठा पढ़ोa_zone *zone;

		zone = re->zones[nzones];
		kref_get(&zone->refcnt);
		spin_lock(&zone->lock);
		--zone->elems;
		अगर (zone->elems == 0) अणु
			/*
			 * no fs_info->पढ़ोa_lock needed, as this can't be
			 * the last ref
			 */
			kref_put(&zone->refcnt, पढ़ोa_zone_release);
		पूर्ण
		spin_unlock(&zone->lock);

		spin_lock(&fs_info->पढ़ोa_lock);
		kref_put(&zone->refcnt, पढ़ोa_zone_release);
		spin_unlock(&fs_info->पढ़ोa_lock);
	पूर्ण
	btrfs_put_bbio(bbio);
	kमुक्त(re);
	वापस re_exist;
पूर्ण

अटल व्योम पढ़ोa_extent_put(काष्ठा btrfs_fs_info *fs_info,
			     काष्ठा पढ़ोa_extent *re)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ index = re->logical >> fs_info->sectorsize_bits;

	spin_lock(&fs_info->पढ़ोa_lock);
	अगर (--re->refcnt) अणु
		spin_unlock(&fs_info->पढ़ोa_lock);
		वापस;
	पूर्ण

	radix_tree_delete(&fs_info->पढ़ोa_tree, index);
	क्रम (i = 0; i < re->nzones; ++i) अणु
		काष्ठा पढ़ोa_zone *zone = re->zones[i];

		radix_tree_delete(&zone->device->पढ़ोa_extents, index);
	पूर्ण

	spin_unlock(&fs_info->पढ़ोa_lock);

	क्रम (i = 0; i < re->nzones; ++i) अणु
		काष्ठा पढ़ोa_zone *zone = re->zones[i];

		kref_get(&zone->refcnt);
		spin_lock(&zone->lock);
		--zone->elems;
		अगर (zone->elems == 0) अणु
			/* no fs_info->पढ़ोa_lock needed, as this can't be
			 * the last ref */
			kref_put(&zone->refcnt, पढ़ोa_zone_release);
		पूर्ण
		spin_unlock(&zone->lock);

		spin_lock(&fs_info->पढ़ोa_lock);
		kref_put(&zone->refcnt, पढ़ोa_zone_release);
		spin_unlock(&fs_info->पढ़ोa_lock);
	पूर्ण

	kमुक्त(re);
पूर्ण

अटल व्योम पढ़ोa_zone_release(काष्ठा kref *kref)
अणु
	काष्ठा पढ़ोa_zone *zone = container_of(kref, काष्ठा पढ़ोa_zone, refcnt);
	काष्ठा btrfs_fs_info *fs_info = zone->device->fs_info;

	lockdep_निश्चित_held(&fs_info->पढ़ोa_lock);

	radix_tree_delete(&zone->device->पढ़ोa_zones,
			  zone->end >> fs_info->sectorsize_bits);

	kमुक्त(zone);
पूर्ण

अटल व्योम पढ़ोa_control_release(काष्ठा kref *kref)
अणु
	काष्ठा पढ़ोa_control *rc = container_of(kref, काष्ठा पढ़ोa_control,
						refcnt);

	kमुक्त(rc);
पूर्ण

अटल पूर्णांक पढ़ोa_add_block(काष्ठा पढ़ोa_control *rc, u64 logical,
			   काष्ठा btrfs_key *top, u64 owner_root,
			   u64 generation, पूर्णांक level)
अणु
	काष्ठा btrfs_fs_info *fs_info = rc->fs_info;
	काष्ठा पढ़ोa_extent *re;
	काष्ठा पढ़ोa_extctl *rec;

	/* takes one ref */
	re = पढ़ोa_find_extent(fs_info, logical, top, owner_root, level);
	अगर (!re)
		वापस -1;

	rec = kzalloc(माप(*rec), GFP_KERNEL);
	अगर (!rec) अणु
		पढ़ोa_extent_put(fs_info, re);
		वापस -ENOMEM;
	पूर्ण

	rec->rc = rc;
	rec->generation = generation;
	atomic_inc(&rc->elems);

	spin_lock(&re->lock);
	list_add_tail(&rec->list, &re->extctl);
	spin_unlock(&re->lock);

	/* leave the ref on the extent */

	वापस 0;
पूर्ण

/*
 * called with fs_info->पढ़ोa_lock held
 */
अटल व्योम पढ़ोa_peer_zones_set_lock(काष्ठा पढ़ोa_zone *zone, पूर्णांक lock)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ index = zone->end >> zone->device->fs_info->sectorsize_bits;

	क्रम (i = 0; i < zone->ndevs; ++i) अणु
		काष्ठा पढ़ोa_zone *peer;
		peer = radix_tree_lookup(&zone->devs[i]->पढ़ोa_zones, index);
		अगर (peer && peer->device != zone->device)
			peer->locked = lock;
	पूर्ण
पूर्ण

/*
 * called with fs_info->पढ़ोa_lock held
 */
अटल पूर्णांक पढ़ोa_pick_zone(काष्ठा btrfs_device *dev)
अणु
	काष्ठा पढ़ोa_zone *top_zone = शून्य;
	काष्ठा पढ़ोa_zone *top_locked_zone = शून्य;
	u64 top_elems = 0;
	u64 top_locked_elems = 0;
	अचिन्हित दीर्घ index = 0;
	पूर्णांक ret;

	अगर (dev->पढ़ोa_curr_zone) अणु
		पढ़ोa_peer_zones_set_lock(dev->पढ़ोa_curr_zone, 0);
		kref_put(&dev->पढ़ोa_curr_zone->refcnt, पढ़ोa_zone_release);
		dev->पढ़ोa_curr_zone = शून्य;
	पूर्ण
	/* pick the zone with the most elements */
	जबतक (1) अणु
		काष्ठा पढ़ोa_zone *zone;

		ret = radix_tree_gang_lookup(&dev->पढ़ोa_zones,
					     (व्योम **)&zone, index, 1);
		अगर (ret == 0)
			अवरोध;
		index = (zone->end >> dev->fs_info->sectorsize_bits) + 1;
		अगर (zone->locked) अणु
			अगर (zone->elems > top_locked_elems) अणु
				top_locked_elems = zone->elems;
				top_locked_zone = zone;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (zone->elems > top_elems) अणु
				top_elems = zone->elems;
				top_zone = zone;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (top_zone)
		dev->पढ़ोa_curr_zone = top_zone;
	अन्यथा अगर (top_locked_zone)
		dev->पढ़ोa_curr_zone = top_locked_zone;
	अन्यथा
		वापस 0;

	dev->पढ़ोa_next = dev->पढ़ोa_curr_zone->start;
	kref_get(&dev->पढ़ोa_curr_zone->refcnt);
	पढ़ोa_peer_zones_set_lock(dev->पढ़ोa_curr_zone, 1);

	वापस 1;
पूर्ण

अटल पूर्णांक पढ़ोa_tree_block_flagged(काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
				    u64 owner_root, पूर्णांक level, पूर्णांक mirror_num,
				    काष्ठा extent_buffer **eb)
अणु
	काष्ठा extent_buffer *buf = शून्य;
	पूर्णांक ret;

	buf = btrfs_find_create_tree_block(fs_info, bytenr, owner_root, level);
	अगर (IS_ERR(buf))
		वापस 0;

	set_bit(EXTENT_BUFFER_READAHEAD, &buf->bflags);

	ret = पढ़ो_extent_buffer_pages(buf, WAIT_PAGE_LOCK, mirror_num);
	अगर (ret) अणु
		मुक्त_extent_buffer_stale(buf);
		वापस ret;
	पूर्ण

	अगर (test_bit(EXTENT_BUFFER_CORRUPT, &buf->bflags)) अणु
		मुक्त_extent_buffer_stale(buf);
		वापस -EIO;
	पूर्ण अन्यथा अगर (extent_buffer_uptodate(buf)) अणु
		*eb = buf;
	पूर्ण अन्यथा अणु
		मुक्त_extent_buffer(buf);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ोa_start_machine_dev(काष्ठा btrfs_device *dev)
अणु
	काष्ठा btrfs_fs_info *fs_info = dev->fs_info;
	काष्ठा पढ़ोa_extent *re = शून्य;
	पूर्णांक mirror_num = 0;
	काष्ठा extent_buffer *eb = शून्य;
	u64 logical;
	पूर्णांक ret;
	पूर्णांक i;

	spin_lock(&fs_info->पढ़ोa_lock);
	अगर (dev->पढ़ोa_curr_zone == शून्य) अणु
		ret = पढ़ोa_pick_zone(dev);
		अगर (!ret) अणु
			spin_unlock(&fs_info->पढ़ोa_lock);
			वापस 0;
		पूर्ण
	पूर्ण
	/*
	 * FIXME currently we issue the पढ़ोs one extent at a समय. If we have
	 * a contiguous block of extents, we could also coagulate them or use
	 * plugging to speed things up
	 */
	ret = radix_tree_gang_lookup(&dev->पढ़ोa_extents, (व्योम **)&re,
				dev->पढ़ोa_next >> fs_info->sectorsize_bits, 1);
	अगर (ret == 0 || re->logical > dev->पढ़ोa_curr_zone->end) अणु
		ret = पढ़ोa_pick_zone(dev);
		अगर (!ret) अणु
			spin_unlock(&fs_info->पढ़ोa_lock);
			वापस 0;
		पूर्ण
		re = शून्य;
		ret = radix_tree_gang_lookup(&dev->पढ़ोa_extents, (व्योम **)&re,
				dev->पढ़ोa_next >> fs_info->sectorsize_bits, 1);
	पूर्ण
	अगर (ret == 0) अणु
		spin_unlock(&fs_info->पढ़ोa_lock);
		वापस 0;
	पूर्ण
	dev->पढ़ोa_next = re->logical + fs_info->nodesize;
	re->refcnt++;

	spin_unlock(&fs_info->पढ़ोa_lock);

	spin_lock(&re->lock);
	अगर (re->scheduled || list_empty(&re->extctl)) अणु
		spin_unlock(&re->lock);
		पढ़ोa_extent_put(fs_info, re);
		वापस 0;
	पूर्ण
	re->scheduled = 1;
	spin_unlock(&re->lock);

	/*
	 * find mirror num
	 */
	क्रम (i = 0; i < re->nzones; ++i) अणु
		अगर (re->zones[i]->device == dev) अणु
			mirror_num = i + 1;
			अवरोध;
		पूर्ण
	पूर्ण
	logical = re->logical;

	atomic_inc(&dev->पढ़ोa_in_flight);
	ret = पढ़ोa_tree_block_flagged(fs_info, logical, re->owner_root,
				       re->level, mirror_num, &eb);
	अगर (ret)
		__पढ़ोahead_hook(fs_info, re, शून्य, ret);
	अन्यथा अगर (eb)
		__पढ़ोahead_hook(fs_info, re, eb, ret);

	अगर (eb)
		मुक्त_extent_buffer(eb);

	atomic_dec(&dev->पढ़ोa_in_flight);
	पढ़ोa_extent_put(fs_info, re);

	वापस 1;

पूर्ण

अटल व्योम पढ़ोa_start_machine_worker(काष्ठा btrfs_work *work)
अणु
	काष्ठा पढ़ोa_machine_work *rmw;
	पूर्णांक old_ioprio;

	rmw = container_of(work, काष्ठा पढ़ोa_machine_work, work);

	old_ioprio = IOPRIO_PRIO_VALUE(task_nice_ioclass(current),
				       task_nice_ioprio(current));
	set_task_ioprio(current, BTRFS_IOPRIO_READA);
	__पढ़ोa_start_machine(rmw->fs_info);
	set_task_ioprio(current, old_ioprio);

	atomic_dec(&rmw->fs_info->पढ़ोa_works_cnt);

	kमुक्त(rmw);
पूर्ण

/* Try to start up to 10k READA requests क्रम a group of devices */
अटल पूर्णांक पढ़ोa_start_क्रम_fsdevs(काष्ठा btrfs_fs_devices *fs_devices)
अणु
	u64 enqueued;
	u64 total = 0;
	काष्ठा btrfs_device *device;

	करो अणु
		enqueued = 0;
		list_क्रम_each_entry(device, &fs_devices->devices, dev_list) अणु
			अगर (atomic_पढ़ो(&device->पढ़ोa_in_flight) <
			    MAX_IN_FLIGHT)
				enqueued += पढ़ोa_start_machine_dev(device);
		पूर्ण
		total += enqueued;
	पूर्ण जबतक (enqueued && total < 10000);

	वापस total;
पूर्ण

अटल व्योम __पढ़ोa_start_machine(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices, *seed_devs;
	पूर्णांक i;
	u64 enqueued = 0;

	mutex_lock(&fs_devices->device_list_mutex);

	enqueued += पढ़ोa_start_क्रम_fsdevs(fs_devices);
	list_क्रम_each_entry(seed_devs, &fs_devices->seed_list, seed_list)
		enqueued += पढ़ोa_start_क्रम_fsdevs(seed_devs);

	mutex_unlock(&fs_devices->device_list_mutex);
	अगर (enqueued == 0)
		वापस;

	/*
	 * If everything is alपढ़ोy in the cache, this is effectively single
	 * thपढ़ोed. To a) not hold the caller क्रम too दीर्घ and b) to utilize
	 * more cores, we broke the loop above after 10000 iterations and now
	 * enqueue to workers to finish it. This will distribute the load to
	 * the cores.
	 */
	क्रम (i = 0; i < 2; ++i) अणु
		पढ़ोa_start_machine(fs_info);
		अगर (atomic_पढ़ो(&fs_info->पढ़ोa_works_cnt) >
		    BTRFS_MAX_MIRRORS * 2)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम पढ़ोa_start_machine(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा पढ़ोa_machine_work *rmw;

	rmw = kzalloc(माप(*rmw), GFP_KERNEL);
	अगर (!rmw) अणु
		/* FIXME we cannot handle this properly right now */
		BUG();
	पूर्ण
	btrfs_init_work(&rmw->work, पढ़ोa_start_machine_worker, शून्य, शून्य);
	rmw->fs_info = fs_info;

	btrfs_queue_work(fs_info->पढ़ोahead_workers, &rmw->work);
	atomic_inc(&fs_info->पढ़ोa_works_cnt);
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम dump_devs(काष्ठा btrfs_fs_info *fs_info, पूर्णांक all)
अणु
	काष्ठा btrfs_device *device;
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices;
	अचिन्हित दीर्घ index;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक cnt;

	spin_lock(&fs_info->पढ़ोa_lock);
	list_क्रम_each_entry(device, &fs_devices->devices, dev_list) अणु
		btrfs_debug(fs_info, "dev %lld has %d in flight", device->devid,
			atomic_पढ़ो(&device->पढ़ोa_in_flight));
		index = 0;
		जबतक (1) अणु
			काष्ठा पढ़ोa_zone *zone;
			ret = radix_tree_gang_lookup(&device->पढ़ोa_zones,
						     (व्योम **)&zone, index, 1);
			अगर (ret == 0)
				अवरोध;
			pr_debug("  zone %llu-%llu elems %llu locked %d devs",
				    zone->start, zone->end, zone->elems,
				    zone->locked);
			क्रम (j = 0; j < zone->ndevs; ++j) अणु
				pr_cont(" %lld",
					zone->devs[j]->devid);
			पूर्ण
			अगर (device->पढ़ोa_curr_zone == zone)
				pr_cont(" curr off %llu",
					device->पढ़ोa_next - zone->start);
			pr_cont("\n");
			index = (zone->end >> fs_info->sectorsize_bits) + 1;
		पूर्ण
		cnt = 0;
		index = 0;
		जबतक (all) अणु
			काष्ठा पढ़ोa_extent *re = शून्य;

			ret = radix_tree_gang_lookup(&device->पढ़ोa_extents,
						     (व्योम **)&re, index, 1);
			अगर (ret == 0)
				अवरोध;
			pr_debug("  re: logical %llu size %u empty %d scheduled %d",
				re->logical, fs_info->nodesize,
				list_empty(&re->extctl), re->scheduled);

			क्रम (i = 0; i < re->nzones; ++i) अणु
				pr_cont(" zone %llu-%llu devs",
					re->zones[i]->start,
					re->zones[i]->end);
				क्रम (j = 0; j < re->zones[i]->ndevs; ++j) अणु
					pr_cont(" %lld",
						re->zones[i]->devs[j]->devid);
				पूर्ण
			पूर्ण
			pr_cont("\n");
			index = (re->logical >> fs_info->sectorsize_bits) + 1;
			अगर (++cnt > 15)
				अवरोध;
		पूर्ण
	पूर्ण

	index = 0;
	cnt = 0;
	जबतक (all) अणु
		काष्ठा पढ़ोa_extent *re = शून्य;

		ret = radix_tree_gang_lookup(&fs_info->पढ़ोa_tree, (व्योम **)&re,
					     index, 1);
		अगर (ret == 0)
			अवरोध;
		अगर (!re->scheduled) अणु
			index = (re->logical >> fs_info->sectorsize_bits) + 1;
			जारी;
		पूर्ण
		pr_debug("re: logical %llu size %u list empty %d scheduled %d",
			re->logical, fs_info->nodesize,
			list_empty(&re->extctl), re->scheduled);
		क्रम (i = 0; i < re->nzones; ++i) अणु
			pr_cont(" zone %llu-%llu devs",
				re->zones[i]->start,
				re->zones[i]->end);
			क्रम (j = 0; j < re->zones[i]->ndevs; ++j) अणु
				pr_cont(" %lld",
				       re->zones[i]->devs[j]->devid);
			पूर्ण
		पूर्ण
		pr_cont("\n");
		index = (re->logical >> fs_info->sectorsize_bits) + 1;
	पूर्ण
	spin_unlock(&fs_info->पढ़ोa_lock);
पूर्ण
#पूर्ण_अगर

/*
 * पूर्णांकerface
 */
काष्ठा पढ़ोa_control *btrfs_पढ़ोa_add(काष्ठा btrfs_root *root,
			काष्ठा btrfs_key *key_start, काष्ठा btrfs_key *key_end)
अणु
	काष्ठा पढ़ोa_control *rc;
	u64 start;
	u64 generation;
	पूर्णांक ret;
	पूर्णांक level;
	काष्ठा extent_buffer *node;
	अटल काष्ठा btrfs_key max_key = अणु
		.objectid = (u64)-1,
		.type = (u8)-1,
		.offset = (u64)-1
	पूर्ण;

	rc = kzalloc(माप(*rc), GFP_KERNEL);
	अगर (!rc)
		वापस ERR_PTR(-ENOMEM);

	rc->fs_info = root->fs_info;
	rc->key_start = *key_start;
	rc->key_end = *key_end;
	atomic_set(&rc->elems, 0);
	init_रुकोqueue_head(&rc->रुको);
	kref_init(&rc->refcnt);
	kref_get(&rc->refcnt); /* one ref क्रम having elements */

	node = btrfs_root_node(root);
	start = node->start;
	generation = btrfs_header_generation(node);
	level = btrfs_header_level(node);
	मुक्त_extent_buffer(node);

	ret = पढ़ोa_add_block(rc, start, &max_key, root->root_key.objectid,
			      generation, level);
	अगर (ret) अणु
		kमुक्त(rc);
		वापस ERR_PTR(ret);
	पूर्ण

	पढ़ोa_start_machine(root->fs_info);

	वापस rc;
पूर्ण

#अगर_घोषित DEBUG
पूर्णांक btrfs_पढ़ोa_रुको(व्योम *handle)
अणु
	काष्ठा पढ़ोa_control *rc = handle;
	काष्ठा btrfs_fs_info *fs_info = rc->fs_info;

	जबतक (atomic_पढ़ो(&rc->elems)) अणु
		अगर (!atomic_पढ़ो(&fs_info->पढ़ोa_works_cnt))
			पढ़ोa_start_machine(fs_info);
		रुको_event_समयout(rc->रुको, atomic_पढ़ो(&rc->elems) == 0,
				   5 * HZ);
		dump_devs(fs_info, atomic_पढ़ो(&rc->elems) < 10 ? 1 : 0);
	पूर्ण

	dump_devs(fs_info, atomic_पढ़ो(&rc->elems) < 10 ? 1 : 0);

	kref_put(&rc->refcnt, पढ़ोa_control_release);

	वापस 0;
पूर्ण
#अन्यथा
पूर्णांक btrfs_पढ़ोa_रुको(व्योम *handle)
अणु
	काष्ठा पढ़ोa_control *rc = handle;
	काष्ठा btrfs_fs_info *fs_info = rc->fs_info;

	जबतक (atomic_पढ़ो(&rc->elems)) अणु
		अगर (!atomic_पढ़ो(&fs_info->पढ़ोa_works_cnt))
			पढ़ोa_start_machine(fs_info);
		रुको_event_समयout(rc->रुको, atomic_पढ़ो(&rc->elems) == 0,
				   (HZ + 9) / 10);
	पूर्ण

	kref_put(&rc->refcnt, पढ़ोa_control_release);

	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम btrfs_पढ़ोa_detach(व्योम *handle)
अणु
	काष्ठा पढ़ोa_control *rc = handle;

	kref_put(&rc->refcnt, पढ़ोa_control_release);
पूर्ण

/*
 * Beक्रमe removing a device (device replace or device हटाओ ioctls), call this
 * function to रुको क्रम all existing पढ़ोahead requests on the device and to
 * make sure no one queues more पढ़ोahead requests क्रम the device.
 *
 * Must be called without holding neither the device list mutex nor the device
 * replace semaphore, otherwise it will deadlock.
 */
व्योम btrfs_पढ़ोa_हटाओ_dev(काष्ठा btrfs_device *dev)
अणु
	काष्ठा btrfs_fs_info *fs_info = dev->fs_info;

	/* Serialize with पढ़ोahead extent creation at पढ़ोa_find_extent(). */
	spin_lock(&fs_info->पढ़ोa_lock);
	set_bit(BTRFS_DEV_STATE_NO_READA, &dev->dev_state);
	spin_unlock(&fs_info->पढ़ोa_lock);

	/*
	 * There might be पढ़ोahead requests added to the radix trees which
	 * were not yet added to the पढ़ोahead work queue. We need to start
	 * them and रुको क्रम their completion, otherwise we can end up with
	 * use-after-मुक्त problems when dropping the last reference on the
	 * पढ़ोahead extents and their zones, as they need to access the
	 * device काष्ठाure.
	 */
	पढ़ोa_start_machine(fs_info);
	btrfs_flush_workqueue(fs_info->पढ़ोahead_workers);
पूर्ण

/*
 * If when removing a device (device replace or device हटाओ ioctls) an error
 * happens after calling btrfs_पढ़ोa_हटाओ_dev(), call this to unकरो what that
 * function did. This is safe to call even अगर btrfs_पढ़ोa_हटाओ_dev() was not
 * called beक्रमe.
 */
व्योम btrfs_पढ़ोa_unकरो_हटाओ_dev(काष्ठा btrfs_device *dev)
अणु
	spin_lock(&dev->fs_info->पढ़ोa_lock);
	clear_bit(BTRFS_DEV_STATE_NO_READA, &dev->dev_state);
	spin_unlock(&dev->fs_info->पढ़ोa_lock);
पूर्ण
