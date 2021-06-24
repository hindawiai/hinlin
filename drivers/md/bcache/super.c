<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bcache setup/tearकरोwn code, and some metadata io - पढ़ो a superblock and
 * figure out what to करो with it.
 *
 * Copyright 2010, 2011 Kent Overstreet <kent.overstreet@gmail.com>
 * Copyright 2012 Google, Inc.
 */

#समावेश "bcache.h"
#समावेश "btree.h"
#समावेश "debug.h"
#समावेश "extents.h"
#समावेश "request.h"
#समावेश "writeback.h"
#समावेश "features.h"

#समावेश <linux/blkdev.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/genhd.h>
#समावेश <linux/idr.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sysfs.h>

अचिन्हित पूर्णांक bch_cutoff_ग_लिखोback;
अचिन्हित पूर्णांक bch_cutoff_ग_लिखोback_sync;

अटल स्थिर अक्षर bcache_magic[] = अणु
	0xc6, 0x85, 0x73, 0xf6, 0x4e, 0x1a, 0x45, 0xca,
	0x82, 0x65, 0xf5, 0x7f, 0x48, 0xba, 0x6d, 0x81
पूर्ण;

अटल स्थिर अक्षर invalid_uuid[] = अणु
	0xa0, 0x3e, 0xf8, 0xed, 0x3e, 0xe1, 0xb8, 0x78,
	0xc8, 0x50, 0xfc, 0x5e, 0xcb, 0x16, 0xcd, 0x99
पूर्ण;

अटल काष्ठा kobject *bcache_kobj;
काष्ठा mutex bch_रेजिस्टर_lock;
bool bcache_is_reboot;
LIST_HEAD(bch_cache_sets);
अटल LIST_HEAD(uncached_devices);

अटल पूर्णांक bcache_major;
अटल DEFINE_IDA(bcache_device_idx);
अटल रुको_queue_head_t unरेजिस्टर_रुको;
काष्ठा workqueue_काष्ठा *bcache_wq;
काष्ठा workqueue_काष्ठा *bch_flush_wq;
काष्ठा workqueue_काष्ठा *bch_journal_wq;


#घोषणा BTREE_MAX_PAGES		(256 * 1024 / PAGE_SIZE)
/* limitation of partitions number on single bcache device */
#घोषणा BCACHE_MINORS		128
/* limitation of bcache devices number on single प्रणाली */
#घोषणा BCACHE_DEVICE_IDX_MAX	((1U << MINORBITS)/BCACHE_MINORS)

/* Superblock */

अटल अचिन्हित पूर्णांक get_bucket_size(काष्ठा cache_sb *sb, काष्ठा cache_sb_disk *s)
अणु
	अचिन्हित पूर्णांक bucket_size = le16_to_cpu(s->bucket_size);

	अगर (sb->version >= BCACHE_SB_VERSION_CDEV_WITH_FEATURES) अणु
		अगर (bch_has_feature_large_bucket(sb)) अणु
			अचिन्हित पूर्णांक max, order;

			max = माप(अचिन्हित पूर्णांक) * BITS_PER_BYTE - 1;
			order = le16_to_cpu(s->bucket_size);
			/*
			 * bcache tool will make sure the overflow won't
			 * happen, an error message here is enough.
			 */
			अगर (order > max)
				pr_err("Bucket size (1 << %u) overflows\n",
					order);
			bucket_size = 1 << order;
		पूर्ण अन्यथा अगर (bch_has_feature_obso_large_bucket(sb)) अणु
			bucket_size +=
				le16_to_cpu(s->obso_bucket_size_hi) << 16;
		पूर्ण
	पूर्ण

	वापस bucket_size;
पूर्ण

अटल स्थिर अक्षर *पढ़ो_super_common(काष्ठा cache_sb *sb,  काष्ठा block_device *bdev,
				     काष्ठा cache_sb_disk *s)
अणु
	स्थिर अक्षर *err;
	अचिन्हित पूर्णांक i;

	sb->first_bucket= le16_to_cpu(s->first_bucket);
	sb->nbuckets	= le64_to_cpu(s->nbuckets);
	sb->bucket_size	= get_bucket_size(sb, s);

	sb->nr_in_set	= le16_to_cpu(s->nr_in_set);
	sb->nr_this_dev	= le16_to_cpu(s->nr_this_dev);

	err = "Too many journal buckets";
	अगर (sb->keys > SB_JOURNAL_BUCKETS)
		जाओ err;

	err = "Too many buckets";
	अगर (sb->nbuckets > दीर्घ_उच्च)
		जाओ err;

	err = "Not enough buckets";
	अगर (sb->nbuckets < 1 << 7)
		जाओ err;

	err = "Bad block size (not power of 2)";
	अगर (!is_घातer_of_2(sb->block_size))
		जाओ err;

	err = "Bad block size (larger than page size)";
	अगर (sb->block_size > PAGE_SECTORS)
		जाओ err;

	err = "Bad bucket size (not power of 2)";
	अगर (!is_घातer_of_2(sb->bucket_size))
		जाओ err;

	err = "Bad bucket size (smaller than page size)";
	अगर (sb->bucket_size < PAGE_SECTORS)
		जाओ err;

	err = "Invalid superblock: device too small";
	अगर (get_capacity(bdev->bd_disk) <
	    sb->bucket_size * sb->nbuckets)
		जाओ err;

	err = "Bad UUID";
	अगर (bch_is_zero(sb->set_uuid, 16))
		जाओ err;

	err = "Bad cache device number in set";
	अगर (!sb->nr_in_set ||
	    sb->nr_in_set <= sb->nr_this_dev ||
	    sb->nr_in_set > MAX_CACHES_PER_SET)
		जाओ err;

	err = "Journal buckets not sequential";
	क्रम (i = 0; i < sb->keys; i++)
		अगर (sb->d[i] != sb->first_bucket + i)
			जाओ err;

	err = "Too many journal buckets";
	अगर (sb->first_bucket + sb->keys > sb->nbuckets)
		जाओ err;

	err = "Invalid superblock: first bucket comes before end of super";
	अगर (sb->first_bucket * sb->bucket_size < 16)
		जाओ err;

	err = शून्य;
err:
	वापस err;
पूर्ण


अटल स्थिर अक्षर *पढ़ो_super(काष्ठा cache_sb *sb, काष्ठा block_device *bdev,
			      काष्ठा cache_sb_disk **res)
अणु
	स्थिर अक्षर *err;
	काष्ठा cache_sb_disk *s;
	काष्ठा page *page;
	अचिन्हित पूर्णांक i;

	page = पढ़ो_cache_page_gfp(bdev->bd_inode->i_mapping,
				   SB_OFFSET >> PAGE_SHIFT, GFP_KERNEL);
	अगर (IS_ERR(page))
		वापस "IO error";
	s = page_address(page) + offset_in_page(SB_OFFSET);

	sb->offset		= le64_to_cpu(s->offset);
	sb->version		= le64_to_cpu(s->version);

	स_नकल(sb->magic,	s->magic, 16);
	स_नकल(sb->uuid,	s->uuid, 16);
	स_नकल(sb->set_uuid,	s->set_uuid, 16);
	स_नकल(sb->label,	s->label, SB_LABEL_SIZE);

	sb->flags		= le64_to_cpu(s->flags);
	sb->seq			= le64_to_cpu(s->seq);
	sb->last_mount		= le32_to_cpu(s->last_mount);
	sb->keys		= le16_to_cpu(s->keys);

	क्रम (i = 0; i < SB_JOURNAL_BUCKETS; i++)
		sb->d[i] = le64_to_cpu(s->d[i]);

	pr_debug("read sb version %llu, flags %llu, seq %llu, journal size %u\n",
		 sb->version, sb->flags, sb->seq, sb->keys);

	err = "Not a bcache superblock (bad offset)";
	अगर (sb->offset != SB_SECTOR)
		जाओ err;

	err = "Not a bcache superblock (bad magic)";
	अगर (स_भेद(sb->magic, bcache_magic, 16))
		जाओ err;

	err = "Bad checksum";
	अगर (s->csum != csum_set(s))
		जाओ err;

	err = "Bad UUID";
	अगर (bch_is_zero(sb->uuid, 16))
		जाओ err;

	sb->block_size	= le16_to_cpu(s->block_size);

	err = "Superblock block size smaller than device block size";
	अगर (sb->block_size << 9 < bdev_logical_block_size(bdev))
		जाओ err;

	चयन (sb->version) अणु
	हाल BCACHE_SB_VERSION_BDEV:
		sb->data_offset	= BDEV_DATA_START_DEFAULT;
		अवरोध;
	हाल BCACHE_SB_VERSION_BDEV_WITH_OFFSET:
	हाल BCACHE_SB_VERSION_BDEV_WITH_FEATURES:
		sb->data_offset	= le64_to_cpu(s->data_offset);

		err = "Bad data offset";
		अगर (sb->data_offset < BDEV_DATA_START_DEFAULT)
			जाओ err;

		अवरोध;
	हाल BCACHE_SB_VERSION_CDEV:
	हाल BCACHE_SB_VERSION_CDEV_WITH_UUID:
		err = पढ़ो_super_common(sb, bdev, s);
		अगर (err)
			जाओ err;
		अवरोध;
	हाल BCACHE_SB_VERSION_CDEV_WITH_FEATURES:
		/*
		 * Feature bits are needed in पढ़ो_super_common(),
		 * convert them firstly.
		 */
		sb->feature_compat = le64_to_cpu(s->feature_compat);
		sb->feature_incompat = le64_to_cpu(s->feature_incompat);
		sb->feature_ro_compat = le64_to_cpu(s->feature_ro_compat);

		/* Check incompatible features */
		err = "Unsupported compatible feature found";
		अगर (bch_has_unknown_compat_features(sb))
			जाओ err;

		err = "Unsupported read-only compatible feature found";
		अगर (bch_has_unknown_ro_compat_features(sb))
			जाओ err;

		err = "Unsupported incompatible feature found";
		अगर (bch_has_unknown_incompat_features(sb))
			जाओ err;

		err = पढ़ो_super_common(sb, bdev, s);
		अगर (err)
			जाओ err;
		अवरोध;
	शेष:
		err = "Unsupported superblock version";
		जाओ err;
	पूर्ण

	sb->last_mount = (u32)kसमय_get_real_seconds();
	*res = s;
	वापस शून्य;
err:
	put_page(page);
	वापस err;
पूर्ण

अटल व्योम ग_लिखो_bdev_super_endio(काष्ठा bio *bio)
अणु
	काष्ठा cached_dev *dc = bio->bi_निजी;

	अगर (bio->bi_status)
		bch_count_backing_io_errors(dc, bio);

	closure_put(&dc->sb_ग_लिखो);
पूर्ण

अटल व्योम __ग_लिखो_super(काष्ठा cache_sb *sb, काष्ठा cache_sb_disk *out,
		काष्ठा bio *bio)
अणु
	अचिन्हित पूर्णांक i;

	bio->bi_opf = REQ_OP_WRITE | REQ_SYNC | REQ_META;
	bio->bi_iter.bi_sector	= SB_SECTOR;
	__bio_add_page(bio, virt_to_page(out), SB_SIZE,
			offset_in_page(out));

	out->offset		= cpu_to_le64(sb->offset);

	स_नकल(out->uuid,	sb->uuid, 16);
	स_नकल(out->set_uuid,	sb->set_uuid, 16);
	स_नकल(out->label,	sb->label, SB_LABEL_SIZE);

	out->flags		= cpu_to_le64(sb->flags);
	out->seq		= cpu_to_le64(sb->seq);

	out->last_mount		= cpu_to_le32(sb->last_mount);
	out->first_bucket	= cpu_to_le16(sb->first_bucket);
	out->keys		= cpu_to_le16(sb->keys);

	क्रम (i = 0; i < sb->keys; i++)
		out->d[i] = cpu_to_le64(sb->d[i]);

	अगर (sb->version >= BCACHE_SB_VERSION_CDEV_WITH_FEATURES) अणु
		out->feature_compat    = cpu_to_le64(sb->feature_compat);
		out->feature_incompat  = cpu_to_le64(sb->feature_incompat);
		out->feature_ro_compat = cpu_to_le64(sb->feature_ro_compat);
	पूर्ण

	out->version		= cpu_to_le64(sb->version);
	out->csum = csum_set(out);

	pr_debug("ver %llu, flags %llu, seq %llu\n",
		 sb->version, sb->flags, sb->seq);

	submit_bio(bio);
पूर्ण

अटल व्योम bch_ग_लिखो_bdev_super_unlock(काष्ठा closure *cl)
अणु
	काष्ठा cached_dev *dc = container_of(cl, काष्ठा cached_dev, sb_ग_लिखो);

	up(&dc->sb_ग_लिखो_mutex);
पूर्ण

व्योम bch_ग_लिखो_bdev_super(काष्ठा cached_dev *dc, काष्ठा closure *parent)
अणु
	काष्ठा closure *cl = &dc->sb_ग_लिखो;
	काष्ठा bio *bio = &dc->sb_bio;

	करोwn(&dc->sb_ग_लिखो_mutex);
	closure_init(cl, parent);

	bio_init(bio, dc->sb_bv, 1);
	bio_set_dev(bio, dc->bdev);
	bio->bi_end_io	= ग_लिखो_bdev_super_endio;
	bio->bi_निजी = dc;

	closure_get(cl);
	/* I/O request sent to backing device */
	__ग_लिखो_super(&dc->sb, dc->sb_disk, bio);

	closure_वापस_with_deकाष्ठाor(cl, bch_ग_लिखो_bdev_super_unlock);
पूर्ण

अटल व्योम ग_लिखो_super_endio(काष्ठा bio *bio)
अणु
	काष्ठा cache *ca = bio->bi_निजी;

	/* is_पढ़ो = 0 */
	bch_count_io_errors(ca, bio->bi_status, 0,
			    "writing superblock");
	closure_put(&ca->set->sb_ग_लिखो);
पूर्ण

अटल व्योम bcache_ग_लिखो_super_unlock(काष्ठा closure *cl)
अणु
	काष्ठा cache_set *c = container_of(cl, काष्ठा cache_set, sb_ग_लिखो);

	up(&c->sb_ग_लिखो_mutex);
पूर्ण

व्योम bcache_ग_लिखो_super(काष्ठा cache_set *c)
अणु
	काष्ठा closure *cl = &c->sb_ग_लिखो;
	काष्ठा cache *ca = c->cache;
	काष्ठा bio *bio = &ca->sb_bio;
	अचिन्हित पूर्णांक version = BCACHE_SB_VERSION_CDEV_WITH_UUID;

	करोwn(&c->sb_ग_लिखो_mutex);
	closure_init(cl, &c->cl);

	ca->sb.seq++;

	अगर (ca->sb.version < version)
		ca->sb.version = version;

	bio_init(bio, ca->sb_bv, 1);
	bio_set_dev(bio, ca->bdev);
	bio->bi_end_io	= ग_लिखो_super_endio;
	bio->bi_निजी = ca;

	closure_get(cl);
	__ग_लिखो_super(&ca->sb, ca->sb_disk, bio);

	closure_वापस_with_deकाष्ठाor(cl, bcache_ग_लिखो_super_unlock);
पूर्ण

/* UUID io */

अटल व्योम uuid_endio(काष्ठा bio *bio)
अणु
	काष्ठा closure *cl = bio->bi_निजी;
	काष्ठा cache_set *c = container_of(cl, काष्ठा cache_set, uuid_ग_लिखो);

	cache_set_err_on(bio->bi_status, c, "accessing uuids");
	bch_bbio_मुक्त(bio, c);
	closure_put(cl);
पूर्ण

अटल व्योम uuid_io_unlock(काष्ठा closure *cl)
अणु
	काष्ठा cache_set *c = container_of(cl, काष्ठा cache_set, uuid_ग_लिखो);

	up(&c->uuid_ग_लिखो_mutex);
पूर्ण

अटल व्योम uuid_io(काष्ठा cache_set *c, पूर्णांक op, अचिन्हित दीर्घ op_flags,
		    काष्ठा bkey *k, काष्ठा closure *parent)
अणु
	काष्ठा closure *cl = &c->uuid_ग_लिखो;
	काष्ठा uuid_entry *u;
	अचिन्हित पूर्णांक i;
	अक्षर buf[80];

	BUG_ON(!parent);
	करोwn(&c->uuid_ग_लिखो_mutex);
	closure_init(cl, parent);

	क्रम (i = 0; i < KEY_PTRS(k); i++) अणु
		काष्ठा bio *bio = bch_bbio_alloc(c);

		bio->bi_opf = REQ_SYNC | REQ_META | op_flags;
		bio->bi_iter.bi_size = KEY_SIZE(k) << 9;

		bio->bi_end_io	= uuid_endio;
		bio->bi_निजी = cl;
		bio_set_op_attrs(bio, op, REQ_SYNC|REQ_META|op_flags);
		bch_bio_map(bio, c->uuids);

		bch_submit_bbio(bio, c, k, i);

		अगर (op != REQ_OP_WRITE)
			अवरोध;
	पूर्ण

	bch_extent_to_text(buf, माप(buf), k);
	pr_debug("%s UUIDs at %s\n", op == REQ_OP_WRITE ? "wrote" : "read", buf);

	क्रम (u = c->uuids; u < c->uuids + c->nr_uuids; u++)
		अगर (!bch_is_zero(u->uuid, 16))
			pr_debug("Slot %zi: %pU: %s: 1st: %u last: %u inv: %u\n",
				 u - c->uuids, u->uuid, u->label,
				 u->first_reg, u->last_reg, u->invalidated);

	closure_वापस_with_deकाष्ठाor(cl, uuid_io_unlock);
पूर्ण

अटल अक्षर *uuid_पढ़ो(काष्ठा cache_set *c, काष्ठा jset *j, काष्ठा closure *cl)
अणु
	काष्ठा bkey *k = &j->uuid_bucket;

	अगर (__bch_btree_ptr_invalid(c, k))
		वापस "bad uuid pointer";

	bkey_copy(&c->uuid_bucket, k);
	uuid_io(c, REQ_OP_READ, 0, k, cl);

	अगर (j->version < BCACHE_JSET_VERSION_UUIDv1) अणु
		काष्ठा uuid_entry_v0	*u0 = (व्योम *) c->uuids;
		काष्ठा uuid_entry	*u1 = (व्योम *) c->uuids;
		पूर्णांक i;

		closure_sync(cl);

		/*
		 * Since the new uuid entry is bigger than the old, we have to
		 * convert starting at the highest memory address and work करोwn
		 * in order to करो it in place
		 */

		क्रम (i = c->nr_uuids - 1;
		     i >= 0;
		     --i) अणु
			स_नकल(u1[i].uuid,	u0[i].uuid, 16);
			स_नकल(u1[i].label,	u0[i].label, 32);

			u1[i].first_reg		= u0[i].first_reg;
			u1[i].last_reg		= u0[i].last_reg;
			u1[i].invalidated	= u0[i].invalidated;

			u1[i].flags	= 0;
			u1[i].sectors	= 0;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक __uuid_ग_लिखो(काष्ठा cache_set *c)
अणु
	BKEY_PADDED(key) k;
	काष्ठा closure cl;
	काष्ठा cache *ca = c->cache;
	अचिन्हित पूर्णांक size;

	closure_init_stack(&cl);
	lockdep_निश्चित_held(&bch_रेजिस्टर_lock);

	अगर (bch_bucket_alloc_set(c, RESERVE_BTREE, &k.key, true))
		वापस 1;

	size =  meta_bucket_pages(&ca->sb) * PAGE_SECTORS;
	SET_KEY_SIZE(&k.key, size);
	uuid_io(c, REQ_OP_WRITE, 0, &k.key, &cl);
	closure_sync(&cl);

	/* Only one bucket used क्रम uuid ग_लिखो */
	atomic_दीर्घ_add(ca->sb.bucket_size, &ca->meta_sectors_written);

	bkey_copy(&c->uuid_bucket, &k.key);
	bkey_put(c, &k.key);
	वापस 0;
पूर्ण

पूर्णांक bch_uuid_ग_लिखो(काष्ठा cache_set *c)
अणु
	पूर्णांक ret = __uuid_ग_लिखो(c);

	अगर (!ret)
		bch_journal_meta(c, शून्य);

	वापस ret;
पूर्ण

अटल काष्ठा uuid_entry *uuid_find(काष्ठा cache_set *c, स्थिर अक्षर *uuid)
अणु
	काष्ठा uuid_entry *u;

	क्रम (u = c->uuids;
	     u < c->uuids + c->nr_uuids; u++)
		अगर (!स_भेद(u->uuid, uuid, 16))
			वापस u;

	वापस शून्य;
पूर्ण

अटल काष्ठा uuid_entry *uuid_find_empty(काष्ठा cache_set *c)
अणु
	अटल स्थिर अक्षर zero_uuid[16] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

	वापस uuid_find(c, zero_uuid);
पूर्ण

/*
 * Bucket priorities/gens:
 *
 * For each bucket, we store on disk its
 *   8 bit gen
 *  16 bit priority
 *
 * See alloc.c क्रम an explanation of the gen. The priority is used to implement
 * lru (and in the future other) cache replacement policies; क्रम most purposes
 * it's just an opaque पूर्णांकeger.
 *
 * The gens and the priorities करोn't have a whole lot to करो with each other, and
 * it's actually the gens that must be written out at specific times - it's no
 * big deal अगर the priorities करोn't get written, अगर we lose them we just reuse
 * buckets in suboptimal order.
 *
 * On disk they're stored in a packed array, and in as many buckets are required
 * to fit them all. The buckets we use to store them क्रमm a list; the journal
 * header poपूर्णांकs to the first bucket, the first bucket poपूर्णांकs to the second
 * bucket, et cetera.
 *
 * This code is used by the allocation code; periodically (whenever it runs out
 * of buckets to allocate from) the allocation code will invalidate some
 * buckets, but it can't use those buckets until their new gens are safely on
 * disk.
 */

अटल व्योम prio_endio(काष्ठा bio *bio)
अणु
	काष्ठा cache *ca = bio->bi_निजी;

	cache_set_err_on(bio->bi_status, ca->set, "accessing priorities");
	bch_bbio_मुक्त(bio, ca->set);
	closure_put(&ca->prio);
पूर्ण

अटल व्योम prio_io(काष्ठा cache *ca, uपूर्णांक64_t bucket, पूर्णांक op,
		    अचिन्हित दीर्घ op_flags)
अणु
	काष्ठा closure *cl = &ca->prio;
	काष्ठा bio *bio = bch_bbio_alloc(ca->set);

	closure_init_stack(cl);

	bio->bi_iter.bi_sector	= bucket * ca->sb.bucket_size;
	bio_set_dev(bio, ca->bdev);
	bio->bi_iter.bi_size	= meta_bucket_bytes(&ca->sb);

	bio->bi_end_io	= prio_endio;
	bio->bi_निजी = ca;
	bio_set_op_attrs(bio, op, REQ_SYNC|REQ_META|op_flags);
	bch_bio_map(bio, ca->disk_buckets);

	closure_bio_submit(ca->set, bio, &ca->prio);
	closure_sync(cl);
पूर्ण

पूर्णांक bch_prio_ग_लिखो(काष्ठा cache *ca, bool रुको)
अणु
	पूर्णांक i;
	काष्ठा bucket *b;
	काष्ठा closure cl;

	pr_debug("free_prio=%zu, free_none=%zu, free_inc=%zu\n",
		 fअगरo_used(&ca->मुक्त[RESERVE_PRIO]),
		 fअगरo_used(&ca->मुक्त[RESERVE_NONE]),
		 fअगरo_used(&ca->मुक्त_inc));

	/*
	 * Pre-check अगर there are enough मुक्त buckets. In the non-blocking
	 * scenario it's better to fail early rather than starting to allocate
	 * buckets and करो a cleanup later in हाल of failure.
	 */
	अगर (!रुको) अणु
		माप_प्रकार avail = fअगरo_used(&ca->मुक्त[RESERVE_PRIO]) +
			       fअगरo_used(&ca->मुक्त[RESERVE_NONE]);
		अगर (prio_buckets(ca) > avail)
			वापस -ENOMEM;
	पूर्ण

	closure_init_stack(&cl);

	lockdep_निश्चित_held(&ca->set->bucket_lock);

	ca->disk_buckets->seq++;

	atomic_दीर्घ_add(ca->sb.bucket_size * prio_buckets(ca),
			&ca->meta_sectors_written);

	क्रम (i = prio_buckets(ca) - 1; i >= 0; --i) अणु
		दीर्घ bucket;
		काष्ठा prio_set *p = ca->disk_buckets;
		काष्ठा bucket_disk *d = p->data;
		काष्ठा bucket_disk *end = d + prios_per_bucket(ca);

		क्रम (b = ca->buckets + i * prios_per_bucket(ca);
		     b < ca->buckets + ca->sb.nbuckets && d < end;
		     b++, d++) अणु
			d->prio = cpu_to_le16(b->prio);
			d->gen = b->gen;
		पूर्ण

		p->next_bucket	= ca->prio_buckets[i + 1];
		p->magic	= pset_magic(&ca->sb);
		p->csum		= bch_crc64(&p->magic, meta_bucket_bytes(&ca->sb) - 8);

		bucket = bch_bucket_alloc(ca, RESERVE_PRIO, रुको);
		BUG_ON(bucket == -1);

		mutex_unlock(&ca->set->bucket_lock);
		prio_io(ca, bucket, REQ_OP_WRITE, 0);
		mutex_lock(&ca->set->bucket_lock);

		ca->prio_buckets[i] = bucket;
		atomic_dec_bug(&ca->buckets[bucket].pin);
	पूर्ण

	mutex_unlock(&ca->set->bucket_lock);

	bch_journal_meta(ca->set, &cl);
	closure_sync(&cl);

	mutex_lock(&ca->set->bucket_lock);

	/*
	 * Don't want the old priorities to get garbage collected until after we
	 * finish writing the new ones, and they're journalled
	 */
	क्रम (i = 0; i < prio_buckets(ca); i++) अणु
		अगर (ca->prio_last_buckets[i])
			__bch_bucket_मुक्त(ca,
				&ca->buckets[ca->prio_last_buckets[i]]);

		ca->prio_last_buckets[i] = ca->prio_buckets[i];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक prio_पढ़ो(काष्ठा cache *ca, uपूर्णांक64_t bucket)
अणु
	काष्ठा prio_set *p = ca->disk_buckets;
	काष्ठा bucket_disk *d = p->data + prios_per_bucket(ca), *end = d;
	काष्ठा bucket *b;
	अचिन्हित पूर्णांक bucket_nr = 0;
	पूर्णांक ret = -EIO;

	क्रम (b = ca->buckets;
	     b < ca->buckets + ca->sb.nbuckets;
	     b++, d++) अणु
		अगर (d == end) अणु
			ca->prio_buckets[bucket_nr] = bucket;
			ca->prio_last_buckets[bucket_nr] = bucket;
			bucket_nr++;

			prio_io(ca, bucket, REQ_OP_READ, 0);

			अगर (p->csum !=
			    bch_crc64(&p->magic, meta_bucket_bytes(&ca->sb) - 8)) अणु
				pr_warn("bad csum reading priorities\n");
				जाओ out;
			पूर्ण

			अगर (p->magic != pset_magic(&ca->sb)) अणु
				pr_warn("bad magic reading priorities\n");
				जाओ out;
			पूर्ण

			bucket = p->next_bucket;
			d = p->data;
		पूर्ण

		b->prio = le16_to_cpu(d->prio);
		b->gen = b->last_gc = d->gen;
	पूर्ण

	ret = 0;
out:
	वापस ret;
पूर्ण

/* Bcache device */

अटल पूर्णांक खोलो_dev(काष्ठा block_device *b, भ_शेषe_t mode)
अणु
	काष्ठा bcache_device *d = b->bd_disk->निजी_data;

	अगर (test_bit(BCACHE_DEV_CLOSING, &d->flags))
		वापस -ENXIO;

	closure_get(&d->cl);
	वापस 0;
पूर्ण

अटल व्योम release_dev(काष्ठा gendisk *b, भ_शेषe_t mode)
अणु
	काष्ठा bcache_device *d = b->निजी_data;

	closure_put(&d->cl);
पूर्ण

अटल पूर्णांक ioctl_dev(काष्ठा block_device *b, भ_शेषe_t mode,
		     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा bcache_device *d = b->bd_disk->निजी_data;

	वापस d->ioctl(d, mode, cmd, arg);
पूर्ण

अटल स्थिर काष्ठा block_device_operations bcache_cached_ops = अणु
	.submit_bio	= cached_dev_submit_bio,
	.खोलो		= खोलो_dev,
	.release	= release_dev,
	.ioctl		= ioctl_dev,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा block_device_operations bcache_flash_ops = अणु
	.submit_bio	= flash_dev_submit_bio,
	.खोलो		= खोलो_dev,
	.release	= release_dev,
	.ioctl		= ioctl_dev,
	.owner		= THIS_MODULE,
पूर्ण;

व्योम bcache_device_stop(काष्ठा bcache_device *d)
अणु
	अगर (!test_and_set_bit(BCACHE_DEV_CLOSING, &d->flags))
		/*
		 * closure_fn set to
		 * - cached device: cached_dev_flush()
		 * - flash dev: flash_dev_flush()
		 */
		closure_queue(&d->cl);
पूर्ण

अटल व्योम bcache_device_unlink(काष्ठा bcache_device *d)
अणु
	lockdep_निश्चित_held(&bch_रेजिस्टर_lock);

	अगर (d->c && !test_and_set_bit(BCACHE_DEV_UNLINK_DONE, &d->flags)) अणु
		काष्ठा cache *ca = d->c->cache;

		sysfs_हटाओ_link(&d->c->kobj, d->name);
		sysfs_हटाओ_link(&d->kobj, "cache");

		bd_unlink_disk_holder(ca->bdev, d->disk);
	पूर्ण
पूर्ण

अटल व्योम bcache_device_link(काष्ठा bcache_device *d, काष्ठा cache_set *c,
			       स्थिर अक्षर *name)
अणु
	काष्ठा cache *ca = c->cache;
	पूर्णांक ret;

	bd_link_disk_holder(ca->bdev, d->disk);

	snम_लिखो(d->name, BCACHEDEVNAME_SIZE,
		 "%s%u", name, d->id);

	ret = sysfs_create_link(&d->kobj, &c->kobj, "cache");
	अगर (ret < 0)
		pr_err("Couldn't create device -> cache set symlink\n");

	ret = sysfs_create_link(&c->kobj, &d->kobj, d->name);
	अगर (ret < 0)
		pr_err("Couldn't create cache set -> device symlink\n");

	clear_bit(BCACHE_DEV_UNLINK_DONE, &d->flags);
पूर्ण

अटल व्योम bcache_device_detach(काष्ठा bcache_device *d)
अणु
	lockdep_निश्चित_held(&bch_रेजिस्टर_lock);

	atomic_dec(&d->c->attached_dev_nr);

	अगर (test_bit(BCACHE_DEV_DETACHING, &d->flags)) अणु
		काष्ठा uuid_entry *u = d->c->uuids + d->id;

		SET_UUID_FLASH_ONLY(u, 0);
		स_नकल(u->uuid, invalid_uuid, 16);
		u->invalidated = cpu_to_le32((u32)kसमय_get_real_seconds());
		bch_uuid_ग_लिखो(d->c);
	पूर्ण

	bcache_device_unlink(d);

	d->c->devices[d->id] = शून्य;
	closure_put(&d->c->caching);
	d->c = शून्य;
पूर्ण

अटल व्योम bcache_device_attach(काष्ठा bcache_device *d, काष्ठा cache_set *c,
				 अचिन्हित पूर्णांक id)
अणु
	d->id = id;
	d->c = c;
	c->devices[id] = d;

	अगर (id >= c->devices_max_used)
		c->devices_max_used = id + 1;

	closure_get(&c->caching);
पूर्ण

अटल अंतरभूत पूर्णांक first_minor_to_idx(पूर्णांक first_minor)
अणु
	वापस (first_minor/BCACHE_MINORS);
पूर्ण

अटल अंतरभूत पूर्णांक idx_to_first_minor(पूर्णांक idx)
अणु
	वापस (idx * BCACHE_MINORS);
पूर्ण

अटल व्योम bcache_device_मुक्त(काष्ठा bcache_device *d)
अणु
	काष्ठा gendisk *disk = d->disk;

	lockdep_निश्चित_held(&bch_रेजिस्टर_lock);

	अगर (disk)
		pr_info("%s stopped\n", disk->disk_name);
	अन्यथा
		pr_err("bcache device (NULL gendisk) stopped\n");

	अगर (d->c)
		bcache_device_detach(d);

	अगर (disk) अणु
		bool disk_added = (disk->flags & GENHD_FL_UP) != 0;

		अगर (disk_added)
			del_gendisk(disk);

		अगर (disk->queue)
			blk_cleanup_queue(disk->queue);

		ida_simple_हटाओ(&bcache_device_idx,
				  first_minor_to_idx(disk->first_minor));
		अगर (disk_added)
			put_disk(disk);
	पूर्ण

	bioset_निकास(&d->bio_split);
	kvमुक्त(d->full_dirty_stripes);
	kvमुक्त(d->stripe_sectors_dirty);

	closure_debug_destroy(&d->cl);
पूर्ण

अटल पूर्णांक bcache_device_init(काष्ठा bcache_device *d, अचिन्हित पूर्णांक block_size,
		sector_t sectors, काष्ठा block_device *cached_bdev,
		स्थिर काष्ठा block_device_operations *ops)
अणु
	काष्ठा request_queue *q;
	स्थिर माप_प्रकार max_stripes = min_t(माप_प्रकार, पूर्णांक_उच्च,
					 SIZE_MAX / माप(atomic_t));
	uपूर्णांक64_t n;
	पूर्णांक idx;

	अगर (!d->stripe_size)
		d->stripe_size = 1 << 31;

	n = DIV_ROUND_UP_ULL(sectors, d->stripe_size);
	अगर (!n || n > max_stripes) अणु
		pr_err("nr_stripes too large or invalid: %llu (start sector beyond end of disk?)\n",
			n);
		वापस -ENOMEM;
	पूर्ण
	d->nr_stripes = n;

	n = d->nr_stripes * माप(atomic_t);
	d->stripe_sectors_dirty = kvzalloc(n, GFP_KERNEL);
	अगर (!d->stripe_sectors_dirty)
		वापस -ENOMEM;

	n = BITS_TO_LONGS(d->nr_stripes) * माप(अचिन्हित दीर्घ);
	d->full_dirty_stripes = kvzalloc(n, GFP_KERNEL);
	अगर (!d->full_dirty_stripes)
		वापस -ENOMEM;

	idx = ida_simple_get(&bcache_device_idx, 0,
				BCACHE_DEVICE_IDX_MAX, GFP_KERNEL);
	अगर (idx < 0)
		वापस idx;

	अगर (bioset_init(&d->bio_split, 4, दुरत्व(काष्ठा bbio, bio),
			BIOSET_NEED_BVECS|BIOSET_NEED_RESCUER))
		जाओ err;

	d->disk = alloc_disk(BCACHE_MINORS);
	अगर (!d->disk)
		जाओ err;

	set_capacity(d->disk, sectors);
	snम_लिखो(d->disk->disk_name, DISK_NAME_LEN, "bcache%i", idx);

	d->disk->major		= bcache_major;
	d->disk->first_minor	= idx_to_first_minor(idx);
	d->disk->fops		= ops;
	d->disk->निजी_data	= d;

	q = blk_alloc_queue(NUMA_NO_NODE);
	अगर (!q)
		वापस -ENOMEM;

	d->disk->queue			= q;
	q->limits.max_hw_sectors	= अच_पूर्णांक_उच्च;
	q->limits.max_sectors		= अच_पूर्णांक_उच्च;
	q->limits.max_segment_size	= अच_पूर्णांक_उच्च;
	q->limits.max_segments		= BIO_MAX_VECS;
	blk_queue_max_discard_sectors(q, अच_पूर्णांक_उच्च);
	q->limits.discard_granularity	= 512;
	q->limits.io_min		= block_size;
	q->limits.logical_block_size	= block_size;
	q->limits.physical_block_size	= block_size;

	अगर (q->limits.logical_block_size > PAGE_SIZE && cached_bdev) अणु
		/*
		 * This should only happen with BCACHE_SB_VERSION_BDEV.
		 * Block/page size is checked क्रम BCACHE_SB_VERSION_CDEV.
		 */
		pr_info("%s: sb/logical block size (%u) greater than page size (%lu) falling back to device logical block size (%u)\n",
			d->disk->disk_name, q->limits.logical_block_size,
			PAGE_SIZE, bdev_logical_block_size(cached_bdev));

		/* This also adjusts physical block size/min io size अगर needed */
		blk_queue_logical_block_size(q, bdev_logical_block_size(cached_bdev));
	पूर्ण

	blk_queue_flag_set(QUEUE_FLAG_NONROT, d->disk->queue);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, d->disk->queue);
	blk_queue_flag_set(QUEUE_FLAG_DISCARD, d->disk->queue);

	blk_queue_ग_लिखो_cache(q, true, true);

	वापस 0;

err:
	ida_simple_हटाओ(&bcache_device_idx, idx);
	वापस -ENOMEM;

पूर्ण

/* Cached device */

अटल व्योम calc_cached_dev_sectors(काष्ठा cache_set *c)
अणु
	uपूर्णांक64_t sectors = 0;
	काष्ठा cached_dev *dc;

	list_क्रम_each_entry(dc, &c->cached_devs, list)
		sectors += bdev_sectors(dc->bdev);

	c->cached_dev_sectors = sectors;
पूर्ण

#घोषणा BACKING_DEV_OFFLINE_TIMEOUT 5
अटल पूर्णांक cached_dev_status_update(व्योम *arg)
अणु
	काष्ठा cached_dev *dc = arg;
	काष्ठा request_queue *q;

	/*
	 * If this delayed worker is stopping outside, directly quit here.
	 * dc->io_disable might be set via sysfs पूर्णांकerface, so check it
	 * here too.
	 */
	जबतक (!kthपढ़ो_should_stop() && !dc->io_disable) अणु
		q = bdev_get_queue(dc->bdev);
		अगर (blk_queue_dying(q))
			dc->offline_seconds++;
		अन्यथा
			dc->offline_seconds = 0;

		अगर (dc->offline_seconds >= BACKING_DEV_OFFLINE_TIMEOUT) अणु
			pr_err("%s: device offline for %d seconds\n",
			       dc->backing_dev_name,
			       BACKING_DEV_OFFLINE_TIMEOUT);
			pr_err("%s: disable I/O request due to backing device offline\n",
			       dc->disk.name);
			dc->io_disable = true;
			/* let others know earlier that io_disable is true */
			smp_mb();
			bcache_device_stop(&dc->disk);
			अवरोध;
		पूर्ण
		schedule_समयout_पूर्णांकerruptible(HZ);
	पूर्ण

	रुको_क्रम_kthपढ़ो_stop();
	वापस 0;
पूर्ण


पूर्णांक bch_cached_dev_run(काष्ठा cached_dev *dc)
अणु
	पूर्णांक ret = 0;
	काष्ठा bcache_device *d = &dc->disk;
	अक्षर *buf = kmemdup_nul(dc->sb.label, SB_LABEL_SIZE, GFP_KERNEL);
	अक्षर *env[] = अणु
		"DRIVER=bcache",
		kaप्र_लिखो(GFP_KERNEL, "CACHED_UUID=%pU", dc->sb.uuid),
		kaप्र_लिखो(GFP_KERNEL, "CACHED_LABEL=%s", buf ? : ""),
		शून्य,
	पूर्ण;

	अगर (dc->io_disable) अणु
		pr_err("I/O disabled on cached dev %s\n",
		       dc->backing_dev_name);
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (atomic_xchg(&dc->running, 1)) अणु
		pr_info("cached dev %s is running already\n",
		       dc->backing_dev_name);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (!d->c &&
	    BDEV_STATE(&dc->sb) != BDEV_STATE_NONE) अणु
		काष्ठा closure cl;

		closure_init_stack(&cl);

		SET_BDEV_STATE(&dc->sb, BDEV_STATE_STALE);
		bch_ग_लिखो_bdev_super(dc, &cl);
		closure_sync(&cl);
	पूर्ण

	add_disk(d->disk);
	bd_link_disk_holder(dc->bdev, dc->disk.disk);
	/*
	 * won't show up in the uevent file, use udevadm monitor -e instead
	 * only class / kset properties are persistent
	 */
	kobject_uevent_env(&disk_to_dev(d->disk)->kobj, KOBJ_CHANGE, env);

	अगर (sysfs_create_link(&d->kobj, &disk_to_dev(d->disk)->kobj, "dev") ||
	    sysfs_create_link(&disk_to_dev(d->disk)->kobj,
			      &d->kobj, "bcache")) अणु
		pr_err("Couldn't create bcache dev <-> disk sysfs symlinks\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	dc->status_update_thपढ़ो = kthपढ़ो_run(cached_dev_status_update,
					       dc, "bcache_status_update");
	अगर (IS_ERR(dc->status_update_thपढ़ो)) अणु
		pr_warn("failed to create bcache_status_update kthread, continue to run without monitoring backing device status\n");
	पूर्ण

out:
	kमुक्त(env[1]);
	kमुक्त(env[2]);
	kमुक्त(buf);
	वापस ret;
पूर्ण

/*
 * If BCACHE_DEV_RATE_DW_RUNNING is set, it means routine of the delayed
 * work dc->ग_लिखोback_rate_update is running. Wait until the routine
 * quits (BCACHE_DEV_RATE_DW_RUNNING is clear), then जारी to
 * cancel it. If BCACHE_DEV_RATE_DW_RUNNING is not clear after समय_out
 * seconds, give up रुकोing here and जारी to cancel it too.
 */
अटल व्योम cancel_ग_लिखोback_rate_update_dwork(काष्ठा cached_dev *dc)
अणु
	पूर्णांक समय_out = WRITEBACK_RATE_UPDATE_SECS_MAX * HZ;

	करो अणु
		अगर (!test_bit(BCACHE_DEV_RATE_DW_RUNNING,
			      &dc->disk.flags))
			अवरोध;
		समय_out--;
		schedule_समयout_पूर्णांकerruptible(1);
	पूर्ण जबतक (समय_out > 0);

	अगर (समय_out == 0)
		pr_warn("give up waiting for dc->writeback_write_update to quit\n");

	cancel_delayed_work_sync(&dc->ग_लिखोback_rate_update);
पूर्ण

अटल व्योम cached_dev_detach_finish(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा cached_dev *dc = container_of(w, काष्ठा cached_dev, detach);

	BUG_ON(!test_bit(BCACHE_DEV_DETACHING, &dc->disk.flags));
	BUG_ON(refcount_पढ़ो(&dc->count));


	अगर (test_and_clear_bit(BCACHE_DEV_WB_RUNNING, &dc->disk.flags))
		cancel_ग_लिखोback_rate_update_dwork(dc);

	अगर (!IS_ERR_OR_शून्य(dc->ग_लिखोback_thपढ़ो)) अणु
		kthपढ़ो_stop(dc->ग_लिखोback_thपढ़ो);
		dc->ग_लिखोback_thपढ़ो = शून्य;
	पूर्ण

	mutex_lock(&bch_रेजिस्टर_lock);

	calc_cached_dev_sectors(dc->disk.c);
	bcache_device_detach(&dc->disk);
	list_move(&dc->list, &uncached_devices);

	clear_bit(BCACHE_DEV_DETACHING, &dc->disk.flags);
	clear_bit(BCACHE_DEV_UNLINK_DONE, &dc->disk.flags);

	mutex_unlock(&bch_रेजिस्टर_lock);

	pr_info("Caching disabled for %s\n", dc->backing_dev_name);

	/* Drop ref we took in cached_dev_detach() */
	closure_put(&dc->disk.cl);
पूर्ण

व्योम bch_cached_dev_detach(काष्ठा cached_dev *dc)
अणु
	lockdep_निश्चित_held(&bch_रेजिस्टर_lock);

	अगर (test_bit(BCACHE_DEV_CLOSING, &dc->disk.flags))
		वापस;

	अगर (test_and_set_bit(BCACHE_DEV_DETACHING, &dc->disk.flags))
		वापस;

	/*
	 * Block the device from being बंदd and मुक्तd until we're finished
	 * detaching
	 */
	closure_get(&dc->disk.cl);

	bch_ग_लिखोback_queue(dc);

	cached_dev_put(dc);
पूर्ण

पूर्णांक bch_cached_dev_attach(काष्ठा cached_dev *dc, काष्ठा cache_set *c,
			  uपूर्णांक8_t *set_uuid)
अणु
	uपूर्णांक32_t rसमय = cpu_to_le32((u32)kसमय_get_real_seconds());
	काष्ठा uuid_entry *u;
	काष्ठा cached_dev *exist_dc, *t;
	पूर्णांक ret = 0;

	अगर ((set_uuid && स_भेद(set_uuid, c->set_uuid, 16)) ||
	    (!set_uuid && स_भेद(dc->sb.set_uuid, c->set_uuid, 16)))
		वापस -ENOENT;

	अगर (dc->disk.c) अणु
		pr_err("Can't attach %s: already attached\n",
		       dc->backing_dev_name);
		वापस -EINVAL;
	पूर्ण

	अगर (test_bit(CACHE_SET_STOPPING, &c->flags)) अणु
		pr_err("Can't attach %s: shutting down\n",
		       dc->backing_dev_name);
		वापस -EINVAL;
	पूर्ण

	अगर (dc->sb.block_size < c->cache->sb.block_size) अणु
		/* Will die */
		pr_err("Couldn't attach %s: block size less than set's block size\n",
		       dc->backing_dev_name);
		वापस -EINVAL;
	पूर्ण

	/* Check whether alपढ़ोy attached */
	list_क्रम_each_entry_safe(exist_dc, t, &c->cached_devs, list) अणु
		अगर (!स_भेद(dc->sb.uuid, exist_dc->sb.uuid, 16)) अणु
			pr_err("Tried to attach %s but duplicate UUID already attached\n",
				dc->backing_dev_name);

			वापस -EINVAL;
		पूर्ण
	पूर्ण

	u = uuid_find(c, dc->sb.uuid);

	अगर (u &&
	    (BDEV_STATE(&dc->sb) == BDEV_STATE_STALE ||
	     BDEV_STATE(&dc->sb) == BDEV_STATE_NONE)) अणु
		स_नकल(u->uuid, invalid_uuid, 16);
		u->invalidated = cpu_to_le32((u32)kसमय_get_real_seconds());
		u = शून्य;
	पूर्ण

	अगर (!u) अणु
		अगर (BDEV_STATE(&dc->sb) == BDEV_STATE_सूचीTY) अणु
			pr_err("Couldn't find uuid for %s in set\n",
			       dc->backing_dev_name);
			वापस -ENOENT;
		पूर्ण

		u = uuid_find_empty(c);
		अगर (!u) अणु
			pr_err("Not caching %s, no room for UUID\n",
			       dc->backing_dev_name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Deadlocks since we're called via sysfs...
	 * sysfs_हटाओ_file(&dc->kobj, &sysfs_attach);
	 */

	अगर (bch_is_zero(u->uuid, 16)) अणु
		काष्ठा closure cl;

		closure_init_stack(&cl);

		स_नकल(u->uuid, dc->sb.uuid, 16);
		स_नकल(u->label, dc->sb.label, SB_LABEL_SIZE);
		u->first_reg = u->last_reg = rसमय;
		bch_uuid_ग_लिखो(c);

		स_नकल(dc->sb.set_uuid, c->set_uuid, 16);
		SET_BDEV_STATE(&dc->sb, BDEV_STATE_CLEAN);

		bch_ग_लिखो_bdev_super(dc, &cl);
		closure_sync(&cl);
	पूर्ण अन्यथा अणु
		u->last_reg = rसमय;
		bch_uuid_ग_लिखो(c);
	पूर्ण

	bcache_device_attach(&dc->disk, c, u - c->uuids);
	list_move(&dc->list, &c->cached_devs);
	calc_cached_dev_sectors(c);

	/*
	 * dc->c must be set beक्रमe dc->count != 0 - paired with the mb in
	 * cached_dev_get()
	 */
	smp_wmb();
	refcount_set(&dc->count, 1);

	/* Block ग_लिखोback thपढ़ो, but spawn it */
	करोwn_ग_लिखो(&dc->ग_लिखोback_lock);
	अगर (bch_cached_dev_ग_लिखोback_start(dc)) अणु
		up_ग_लिखो(&dc->ग_लिखोback_lock);
		pr_err("Couldn't start writeback facilities for %s\n",
		       dc->disk.disk->disk_name);
		वापस -ENOMEM;
	पूर्ण

	अगर (BDEV_STATE(&dc->sb) == BDEV_STATE_सूचीTY) अणु
		atomic_set(&dc->has_dirty, 1);
		bch_ग_लिखोback_queue(dc);
	पूर्ण

	bch_sectors_dirty_init(&dc->disk);

	ret = bch_cached_dev_run(dc);
	अगर (ret && (ret != -EBUSY)) अणु
		up_ग_लिखो(&dc->ग_लिखोback_lock);
		/*
		 * bch_रेजिस्टर_lock is held, bcache_device_stop() is not
		 * able to be directly called. The kthपढ़ो and kworker
		 * created previously in bch_cached_dev_ग_लिखोback_start()
		 * have to be stopped manually here.
		 */
		kthपढ़ो_stop(dc->ग_लिखोback_thपढ़ो);
		cancel_ग_लिखोback_rate_update_dwork(dc);
		pr_err("Couldn't run cached device %s\n",
		       dc->backing_dev_name);
		वापस ret;
	पूर्ण

	bcache_device_link(&dc->disk, c, "bdev");
	atomic_inc(&c->attached_dev_nr);

	अगर (bch_has_feature_obso_large_bucket(&(c->cache->sb))) अणु
		pr_err("The obsoleted large bucket layout is unsupported, set the bcache device into read-only\n");
		pr_err("Please update to the latest bcache-tools to create the cache device\n");
		set_disk_ro(dc->disk.disk, 1);
	पूर्ण

	/* Allow the ग_लिखोback thपढ़ो to proceed */
	up_ग_लिखो(&dc->ग_लिखोback_lock);

	pr_info("Caching %s as %s on set %pU\n",
		dc->backing_dev_name,
		dc->disk.disk->disk_name,
		dc->disk.c->set_uuid);
	वापस 0;
पूर्ण

/* when dc->disk.kobj released */
व्योम bch_cached_dev_release(काष्ठा kobject *kobj)
अणु
	काष्ठा cached_dev *dc = container_of(kobj, काष्ठा cached_dev,
					     disk.kobj);
	kमुक्त(dc);
	module_put(THIS_MODULE);
पूर्ण

अटल व्योम cached_dev_मुक्त(काष्ठा closure *cl)
अणु
	काष्ठा cached_dev *dc = container_of(cl, काष्ठा cached_dev, disk.cl);

	अगर (test_and_clear_bit(BCACHE_DEV_WB_RUNNING, &dc->disk.flags))
		cancel_ग_लिखोback_rate_update_dwork(dc);

	अगर (!IS_ERR_OR_शून्य(dc->ग_लिखोback_thपढ़ो))
		kthपढ़ो_stop(dc->ग_लिखोback_thपढ़ो);
	अगर (!IS_ERR_OR_शून्य(dc->status_update_thपढ़ो))
		kthपढ़ो_stop(dc->status_update_thपढ़ो);

	mutex_lock(&bch_रेजिस्टर_lock);

	अगर (atomic_पढ़ो(&dc->running))
		bd_unlink_disk_holder(dc->bdev, dc->disk.disk);
	bcache_device_मुक्त(&dc->disk);
	list_del(&dc->list);

	mutex_unlock(&bch_रेजिस्टर_lock);

	अगर (dc->sb_disk)
		put_page(virt_to_page(dc->sb_disk));

	अगर (!IS_ERR_OR_शून्य(dc->bdev))
		blkdev_put(dc->bdev, FMODE_READ|FMODE_WRITE|FMODE_EXCL);

	wake_up(&unरेजिस्टर_रुको);

	kobject_put(&dc->disk.kobj);
पूर्ण

अटल व्योम cached_dev_flush(काष्ठा closure *cl)
अणु
	काष्ठा cached_dev *dc = container_of(cl, काष्ठा cached_dev, disk.cl);
	काष्ठा bcache_device *d = &dc->disk;

	mutex_lock(&bch_रेजिस्टर_lock);
	bcache_device_unlink(d);
	mutex_unlock(&bch_रेजिस्टर_lock);

	bch_cache_accounting_destroy(&dc->accounting);
	kobject_del(&d->kobj);

	जारी_at(cl, cached_dev_मुक्त, प्रणाली_wq);
पूर्ण

अटल पूर्णांक cached_dev_init(काष्ठा cached_dev *dc, अचिन्हित पूर्णांक block_size)
अणु
	पूर्णांक ret;
	काष्ठा io *io;
	काष्ठा request_queue *q = bdev_get_queue(dc->bdev);

	__module_get(THIS_MODULE);
	INIT_LIST_HEAD(&dc->list);
	closure_init(&dc->disk.cl, शून्य);
	set_closure_fn(&dc->disk.cl, cached_dev_flush, प्रणाली_wq);
	kobject_init(&dc->disk.kobj, &bch_cached_dev_ktype);
	INIT_WORK(&dc->detach, cached_dev_detach_finish);
	sema_init(&dc->sb_ग_लिखो_mutex, 1);
	INIT_LIST_HEAD(&dc->io_lru);
	spin_lock_init(&dc->io_lock);
	bch_cache_accounting_init(&dc->accounting, &dc->disk.cl);

	dc->sequential_cutoff		= 4 << 20;

	क्रम (io = dc->io; io < dc->io + RECENT_IO; io++) अणु
		list_add(&io->lru, &dc->io_lru);
		hlist_add_head(&io->hash, dc->io_hash + RECENT_IO);
	पूर्ण

	dc->disk.stripe_size = q->limits.io_opt >> 9;

	अगर (dc->disk.stripe_size)
		dc->partial_stripes_expensive =
			q->limits.raid_partial_stripes_expensive;

	ret = bcache_device_init(&dc->disk, block_size,
			 bdev_nr_sectors(dc->bdev) - dc->sb.data_offset,
			 dc->bdev, &bcache_cached_ops);
	अगर (ret)
		वापस ret;

	blk_queue_io_opt(dc->disk.disk->queue,
		max(queue_io_opt(dc->disk.disk->queue), queue_io_opt(q)));

	atomic_set(&dc->io_errors, 0);
	dc->io_disable = false;
	dc->error_limit = DEFAULT_CACHED_DEV_ERROR_LIMIT;
	/* शेष to स्वतः */
	dc->stop_when_cache_set_failed = BCH_CACHED_DEV_STOP_AUTO;

	bch_cached_dev_request_init(dc);
	bch_cached_dev_ग_लिखोback_init(dc);
	वापस 0;
पूर्ण

/* Cached device - bcache superblock */

अटल पूर्णांक रेजिस्टर_bdev(काष्ठा cache_sb *sb, काष्ठा cache_sb_disk *sb_disk,
				 काष्ठा block_device *bdev,
				 काष्ठा cached_dev *dc)
अणु
	स्थिर अक्षर *err = "cannot allocate memory";
	काष्ठा cache_set *c;
	पूर्णांक ret = -ENOMEM;

	bdevname(bdev, dc->backing_dev_name);
	स_नकल(&dc->sb, sb, माप(काष्ठा cache_sb));
	dc->bdev = bdev;
	dc->bdev->bd_holder = dc;
	dc->sb_disk = sb_disk;

	अगर (cached_dev_init(dc, sb->block_size << 9))
		जाओ err;

	err = "error creating kobject";
	अगर (kobject_add(&dc->disk.kobj, bdev_kobj(bdev), "bcache"))
		जाओ err;
	अगर (bch_cache_accounting_add_kobjs(&dc->accounting, &dc->disk.kobj))
		जाओ err;

	pr_info("registered backing device %s\n", dc->backing_dev_name);

	list_add(&dc->list, &uncached_devices);
	/* attach to a matched cache set अगर it exists */
	list_क्रम_each_entry(c, &bch_cache_sets, list)
		bch_cached_dev_attach(dc, c, शून्य);

	अगर (BDEV_STATE(&dc->sb) == BDEV_STATE_NONE ||
	    BDEV_STATE(&dc->sb) == BDEV_STATE_STALE) अणु
		err = "failed to run cached device";
		ret = bch_cached_dev_run(dc);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	pr_notice("error %s: %s\n", dc->backing_dev_name, err);
	bcache_device_stop(&dc->disk);
	वापस ret;
पूर्ण

/* Flash only volumes */

/* When d->kobj released */
व्योम bch_flash_dev_release(काष्ठा kobject *kobj)
अणु
	काष्ठा bcache_device *d = container_of(kobj, काष्ठा bcache_device,
					       kobj);
	kमुक्त(d);
पूर्ण

अटल व्योम flash_dev_मुक्त(काष्ठा closure *cl)
अणु
	काष्ठा bcache_device *d = container_of(cl, काष्ठा bcache_device, cl);

	mutex_lock(&bch_रेजिस्टर_lock);
	atomic_दीर्घ_sub(bcache_dev_sectors_dirty(d),
			&d->c->flash_dev_dirty_sectors);
	bcache_device_मुक्त(d);
	mutex_unlock(&bch_रेजिस्टर_lock);
	kobject_put(&d->kobj);
पूर्ण

अटल व्योम flash_dev_flush(काष्ठा closure *cl)
अणु
	काष्ठा bcache_device *d = container_of(cl, काष्ठा bcache_device, cl);

	mutex_lock(&bch_रेजिस्टर_lock);
	bcache_device_unlink(d);
	mutex_unlock(&bch_रेजिस्टर_lock);
	kobject_del(&d->kobj);
	जारी_at(cl, flash_dev_मुक्त, प्रणाली_wq);
पूर्ण

अटल पूर्णांक flash_dev_run(काष्ठा cache_set *c, काष्ठा uuid_entry *u)
अणु
	काष्ठा bcache_device *d = kzalloc(माप(काष्ठा bcache_device),
					  GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	closure_init(&d->cl, शून्य);
	set_closure_fn(&d->cl, flash_dev_flush, प्रणाली_wq);

	kobject_init(&d->kobj, &bch_flash_dev_ktype);

	अगर (bcache_device_init(d, block_bytes(c->cache), u->sectors,
			शून्य, &bcache_flash_ops))
		जाओ err;

	bcache_device_attach(d, c, u - c->uuids);
	bch_sectors_dirty_init(d);
	bch_flash_dev_request_init(d);
	add_disk(d->disk);

	अगर (kobject_add(&d->kobj, &disk_to_dev(d->disk)->kobj, "bcache"))
		जाओ err;

	bcache_device_link(d, c, "volume");

	अगर (bch_has_feature_obso_large_bucket(&c->cache->sb)) अणु
		pr_err("The obsoleted large bucket layout is unsupported, set the bcache device into read-only\n");
		pr_err("Please update to the latest bcache-tools to create the cache device\n");
		set_disk_ro(d->disk, 1);
	पूर्ण

	वापस 0;
err:
	kobject_put(&d->kobj);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक flash_devs_run(काष्ठा cache_set *c)
अणु
	पूर्णांक ret = 0;
	काष्ठा uuid_entry *u;

	क्रम (u = c->uuids;
	     u < c->uuids + c->nr_uuids && !ret;
	     u++)
		अगर (UUID_FLASH_ONLY(u))
			ret = flash_dev_run(c, u);

	वापस ret;
पूर्ण

पूर्णांक bch_flash_dev_create(काष्ठा cache_set *c, uपूर्णांक64_t size)
अणु
	काष्ठा uuid_entry *u;

	अगर (test_bit(CACHE_SET_STOPPING, &c->flags))
		वापस -EINTR;

	अगर (!test_bit(CACHE_SET_RUNNING, &c->flags))
		वापस -EPERM;

	u = uuid_find_empty(c);
	अगर (!u) अणु
		pr_err("Can't create volume, no room for UUID\n");
		वापस -EINVAL;
	पूर्ण

	get_अक्रमom_bytes(u->uuid, 16);
	स_रखो(u->label, 0, 32);
	u->first_reg = u->last_reg = cpu_to_le32((u32)kसमय_get_real_seconds());

	SET_UUID_FLASH_ONLY(u, 1);
	u->sectors = size >> 9;

	bch_uuid_ग_लिखो(c);

	वापस flash_dev_run(c, u);
पूर्ण

bool bch_cached_dev_error(काष्ठा cached_dev *dc)
अणु
	अगर (!dc || test_bit(BCACHE_DEV_CLOSING, &dc->disk.flags))
		वापस false;

	dc->io_disable = true;
	/* make others know io_disable is true earlier */
	smp_mb();

	pr_err("stop %s: too many IO errors on backing device %s\n",
	       dc->disk.disk->disk_name, dc->backing_dev_name);

	bcache_device_stop(&dc->disk);
	वापस true;
पूर्ण

/* Cache set */

__म_लिखो(2, 3)
bool bch_cache_set_error(काष्ठा cache_set *c, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (c->on_error != ON_ERROR_PANIC &&
	    test_bit(CACHE_SET_STOPPING, &c->flags))
		वापस false;

	अगर (test_and_set_bit(CACHE_SET_IO_DISABLE, &c->flags))
		pr_info("CACHE_SET_IO_DISABLE already set\n");

	/*
	 * XXX: we can be called from atomic context
	 * acquire_console_sem();
	 */

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	pr_err("error on %pU: %pV, disabling caching\n",
	       c->set_uuid, &vaf);

	बहु_पूर्ण(args);

	अगर (c->on_error == ON_ERROR_PANIC)
		panic("panic forced after error\n");

	bch_cache_set_unरेजिस्टर(c);
	वापस true;
पूर्ण

/* When c->kobj released */
व्योम bch_cache_set_release(काष्ठा kobject *kobj)
अणु
	काष्ठा cache_set *c = container_of(kobj, काष्ठा cache_set, kobj);

	kमुक्त(c);
	module_put(THIS_MODULE);
पूर्ण

अटल व्योम cache_set_मुक्त(काष्ठा closure *cl)
अणु
	काष्ठा cache_set *c = container_of(cl, काष्ठा cache_set, cl);
	काष्ठा cache *ca;

	debugfs_हटाओ(c->debug);

	bch_खोलो_buckets_मुक्त(c);
	bch_btree_cache_मुक्त(c);
	bch_journal_मुक्त(c);

	mutex_lock(&bch_रेजिस्टर_lock);
	bch_bset_sort_state_मुक्त(&c->sort);
	मुक्त_pages((अचिन्हित दीर्घ) c->uuids, ilog2(meta_bucket_pages(&c->cache->sb)));

	ca = c->cache;
	अगर (ca) अणु
		ca->set = शून्य;
		c->cache = शून्य;
		kobject_put(&ca->kobj);
	पूर्ण


	अगर (c->moving_gc_wq)
		destroy_workqueue(c->moving_gc_wq);
	bioset_निकास(&c->bio_split);
	mempool_निकास(&c->fill_iter);
	mempool_निकास(&c->bio_meta);
	mempool_निकास(&c->search);
	kमुक्त(c->devices);

	list_del(&c->list);
	mutex_unlock(&bch_रेजिस्टर_lock);

	pr_info("Cache set %pU unregistered\n", c->set_uuid);
	wake_up(&unरेजिस्टर_रुको);

	closure_debug_destroy(&c->cl);
	kobject_put(&c->kobj);
पूर्ण

अटल व्योम cache_set_flush(काष्ठा closure *cl)
अणु
	काष्ठा cache_set *c = container_of(cl, काष्ठा cache_set, caching);
	काष्ठा cache *ca = c->cache;
	काष्ठा btree *b;

	bch_cache_accounting_destroy(&c->accounting);

	kobject_put(&c->पूर्णांकernal);
	kobject_del(&c->kobj);

	अगर (!IS_ERR_OR_शून्य(c->gc_thपढ़ो))
		kthपढ़ो_stop(c->gc_thपढ़ो);

	अगर (!IS_ERR_OR_शून्य(c->root))
		list_add(&c->root->list, &c->btree_cache);

	/*
	 * Aव्योम flushing cached nodes अगर cache set is retiring
	 * due to too many I/O errors detected.
	 */
	अगर (!test_bit(CACHE_SET_IO_DISABLE, &c->flags))
		list_क्रम_each_entry(b, &c->btree_cache, list) अणु
			mutex_lock(&b->ग_लिखो_lock);
			अगर (btree_node_dirty(b))
				__bch_btree_node_ग_लिखो(b, शून्य);
			mutex_unlock(&b->ग_लिखो_lock);
		पूर्ण

	अगर (ca->alloc_thपढ़ो)
		kthपढ़ो_stop(ca->alloc_thपढ़ो);

	अगर (c->journal.cur) अणु
		cancel_delayed_work_sync(&c->journal.work);
		/* flush last journal entry अगर needed */
		c->journal.work.work.func(&c->journal.work.work);
	पूर्ण

	closure_वापस(cl);
पूर्ण

/*
 * This function is only called when CACHE_SET_IO_DISABLE is set, which means
 * cache set is unरेजिस्टरing due to too many I/O errors. In this condition,
 * the bcache device might be stopped, it depends on stop_when_cache_set_failed
 * value and whether the broken cache has dirty data:
 *
 * dc->stop_when_cache_set_failed    dc->has_dirty   stop bcache device
 *  BCH_CACHED_STOP_AUTO               0               NO
 *  BCH_CACHED_STOP_AUTO               1               YES
 *  BCH_CACHED_DEV_STOP_ALWAYS         0               YES
 *  BCH_CACHED_DEV_STOP_ALWAYS         1               YES
 *
 * The expected behavior is, अगर stop_when_cache_set_failed is configured to
 * "auto" via sysfs पूर्णांकerface, the bcache device will not be stopped अगर the
 * backing device is clean on the broken cache device.
 */
अटल व्योम conditional_stop_bcache_device(काष्ठा cache_set *c,
					   काष्ठा bcache_device *d,
					   काष्ठा cached_dev *dc)
अणु
	अगर (dc->stop_when_cache_set_failed == BCH_CACHED_DEV_STOP_ALWAYS) अणु
		pr_warn("stop_when_cache_set_failed of %s is \"always\", stop it for failed cache set %pU.\n",
			d->disk->disk_name, c->set_uuid);
		bcache_device_stop(d);
	पूर्ण अन्यथा अगर (atomic_पढ़ो(&dc->has_dirty)) अणु
		/*
		 * dc->stop_when_cache_set_failed == BCH_CACHED_STOP_AUTO
		 * and dc->has_dirty == 1
		 */
		pr_warn("stop_when_cache_set_failed of %s is \"auto\" and cache is dirty, stop it to avoid potential data corruption.\n",
			d->disk->disk_name);
		/*
		 * There might be a small समय gap that cache set is
		 * released but bcache device is not. Inside this समय
		 * gap, regular I/O requests will directly go पूर्णांकo
		 * backing device as no cache set attached to. This
		 * behavior may also पूर्णांकroduce potential inconsistence
		 * data in ग_लिखोback mode जबतक cache is dirty.
		 * Thereक्रमe beक्रमe calling bcache_device_stop() due
		 * to a broken cache device, dc->io_disable should be
		 * explicitly set to true.
		 */
		dc->io_disable = true;
		/* make others know io_disable is true earlier */
		smp_mb();
		bcache_device_stop(d);
	पूर्ण अन्यथा अणु
		/*
		 * dc->stop_when_cache_set_failed == BCH_CACHED_STOP_AUTO
		 * and dc->has_dirty == 0
		 */
		pr_warn("stop_when_cache_set_failed of %s is \"auto\" and cache is clean, keep it alive.\n",
			d->disk->disk_name);
	पूर्ण
पूर्ण

अटल व्योम __cache_set_unरेजिस्टर(काष्ठा closure *cl)
अणु
	काष्ठा cache_set *c = container_of(cl, काष्ठा cache_set, caching);
	काष्ठा cached_dev *dc;
	काष्ठा bcache_device *d;
	माप_प्रकार i;

	mutex_lock(&bch_रेजिस्टर_lock);

	क्रम (i = 0; i < c->devices_max_used; i++) अणु
		d = c->devices[i];
		अगर (!d)
			जारी;

		अगर (!UUID_FLASH_ONLY(&c->uuids[i]) &&
		    test_bit(CACHE_SET_UNREGISTERING, &c->flags)) अणु
			dc = container_of(d, काष्ठा cached_dev, disk);
			bch_cached_dev_detach(dc);
			अगर (test_bit(CACHE_SET_IO_DISABLE, &c->flags))
				conditional_stop_bcache_device(c, d, dc);
		पूर्ण अन्यथा अणु
			bcache_device_stop(d);
		पूर्ण
	पूर्ण

	mutex_unlock(&bch_रेजिस्टर_lock);

	जारी_at(cl, cache_set_flush, प्रणाली_wq);
पूर्ण

व्योम bch_cache_set_stop(काष्ठा cache_set *c)
अणु
	अगर (!test_and_set_bit(CACHE_SET_STOPPING, &c->flags))
		/* closure_fn set to __cache_set_unरेजिस्टर() */
		closure_queue(&c->caching);
पूर्ण

व्योम bch_cache_set_unरेजिस्टर(काष्ठा cache_set *c)
अणु
	set_bit(CACHE_SET_UNREGISTERING, &c->flags);
	bch_cache_set_stop(c);
पूर्ण

#घोषणा alloc_meta_bucket_pages(gfp, sb)		\
	((व्योम *) __get_मुक्त_pages(__GFP_ZERO|__GFP_COMP|gfp, ilog2(meta_bucket_pages(sb))))

काष्ठा cache_set *bch_cache_set_alloc(काष्ठा cache_sb *sb)
अणु
	पूर्णांक iter_size;
	काष्ठा cache *ca = container_of(sb, काष्ठा cache, sb);
	काष्ठा cache_set *c = kzalloc(माप(काष्ठा cache_set), GFP_KERNEL);

	अगर (!c)
		वापस शून्य;

	__module_get(THIS_MODULE);
	closure_init(&c->cl, शून्य);
	set_closure_fn(&c->cl, cache_set_मुक्त, प्रणाली_wq);

	closure_init(&c->caching, &c->cl);
	set_closure_fn(&c->caching, __cache_set_unरेजिस्टर, प्रणाली_wq);

	/* Maybe create जारी_at_noवापस() and use it here? */
	closure_set_stopped(&c->cl);
	closure_put(&c->cl);

	kobject_init(&c->kobj, &bch_cache_set_ktype);
	kobject_init(&c->पूर्णांकernal, &bch_cache_set_पूर्णांकernal_ktype);

	bch_cache_accounting_init(&c->accounting, &c->cl);

	स_नकल(c->set_uuid, sb->set_uuid, 16);

	c->cache		= ca;
	c->cache->set		= c;
	c->bucket_bits		= ilog2(sb->bucket_size);
	c->block_bits		= ilog2(sb->block_size);
	c->nr_uuids		= meta_bucket_bytes(sb) / माप(काष्ठा uuid_entry);
	c->devices_max_used	= 0;
	atomic_set(&c->attached_dev_nr, 0);
	c->btree_pages		= meta_bucket_pages(sb);
	अगर (c->btree_pages > BTREE_MAX_PAGES)
		c->btree_pages = max_t(पूर्णांक, c->btree_pages / 4,
				       BTREE_MAX_PAGES);

	sema_init(&c->sb_ग_लिखो_mutex, 1);
	mutex_init(&c->bucket_lock);
	init_रुकोqueue_head(&c->btree_cache_रुको);
	spin_lock_init(&c->btree_cannibalize_lock);
	init_रुकोqueue_head(&c->bucket_रुको);
	init_रुकोqueue_head(&c->gc_रुको);
	sema_init(&c->uuid_ग_लिखो_mutex, 1);

	spin_lock_init(&c->btree_gc_समय.lock);
	spin_lock_init(&c->btree_split_समय.lock);
	spin_lock_init(&c->btree_पढ़ो_समय.lock);

	bch_moving_init_cache_set(c);

	INIT_LIST_HEAD(&c->list);
	INIT_LIST_HEAD(&c->cached_devs);
	INIT_LIST_HEAD(&c->btree_cache);
	INIT_LIST_HEAD(&c->btree_cache_मुक्तable);
	INIT_LIST_HEAD(&c->btree_cache_मुक्तd);
	INIT_LIST_HEAD(&c->data_buckets);

	iter_size = ((meta_bucket_pages(sb) * PAGE_SECTORS) / sb->block_size + 1) *
		माप(काष्ठा btree_iter_set);

	c->devices = kसुस्मृति(c->nr_uuids, माप(व्योम *), GFP_KERNEL);
	अगर (!c->devices)
		जाओ err;

	अगर (mempool_init_slab_pool(&c->search, 32, bch_search_cache))
		जाओ err;

	अगर (mempool_init_kदो_स्मृति_pool(&c->bio_meta, 2,
			माप(काष्ठा bbio) +
			माप(काष्ठा bio_vec) * meta_bucket_pages(sb)))
		जाओ err;

	अगर (mempool_init_kदो_स्मृति_pool(&c->fill_iter, 1, iter_size))
		जाओ err;

	अगर (bioset_init(&c->bio_split, 4, दुरत्व(काष्ठा bbio, bio),
			BIOSET_NEED_RESCUER))
		जाओ err;

	c->uuids = alloc_meta_bucket_pages(GFP_KERNEL, sb);
	अगर (!c->uuids)
		जाओ err;

	c->moving_gc_wq = alloc_workqueue("bcache_gc", WQ_MEM_RECLAIM, 0);
	अगर (!c->moving_gc_wq)
		जाओ err;

	अगर (bch_journal_alloc(c))
		जाओ err;

	अगर (bch_btree_cache_alloc(c))
		जाओ err;

	अगर (bch_खोलो_buckets_alloc(c))
		जाओ err;

	अगर (bch_bset_sort_state_init(&c->sort, ilog2(c->btree_pages)))
		जाओ err;

	c->congested_पढ़ो_threshold_us	= 2000;
	c->congested_ग_लिखो_threshold_us	= 20000;
	c->error_limit	= DEFAULT_IO_ERROR_LIMIT;
	c->idle_max_ग_लिखोback_rate_enabled = 1;
	WARN_ON(test_and_clear_bit(CACHE_SET_IO_DISABLE, &c->flags));

	वापस c;
err:
	bch_cache_set_unरेजिस्टर(c);
	वापस शून्य;
पूर्ण

अटल पूर्णांक run_cache_set(काष्ठा cache_set *c)
अणु
	स्थिर अक्षर *err = "cannot allocate memory";
	काष्ठा cached_dev *dc, *t;
	काष्ठा cache *ca = c->cache;
	काष्ठा closure cl;
	LIST_HEAD(journal);
	काष्ठा journal_replay *l;

	closure_init_stack(&cl);

	c->nbuckets = ca->sb.nbuckets;
	set_gc_sectors(c);

	अगर (CACHE_SYNC(&c->cache->sb)) अणु
		काष्ठा bkey *k;
		काष्ठा jset *j;

		err = "cannot allocate memory for journal";
		अगर (bch_journal_पढ़ो(c, &journal))
			जाओ err;

		pr_debug("btree_journal_read() done\n");

		err = "no journal entries found";
		अगर (list_empty(&journal))
			जाओ err;

		j = &list_entry(journal.prev, काष्ठा journal_replay, list)->j;

		err = "IO error reading priorities";
		अगर (prio_पढ़ो(ca, j->prio_bucket[ca->sb.nr_this_dev]))
			जाओ err;

		/*
		 * If prio_पढ़ो() fails it'll call cache_set_error and we'll
		 * tear everything करोwn right away, but अगर we perhaps checked
		 * sooner we could aव्योम journal replay.
		 */

		k = &j->btree_root;

		err = "bad btree root";
		अगर (__bch_btree_ptr_invalid(c, k))
			जाओ err;

		err = "error reading btree root";
		c->root = bch_btree_node_get(c, शून्य, k,
					     j->btree_level,
					     true, शून्य);
		अगर (IS_ERR_OR_शून्य(c->root))
			जाओ err;

		list_del_init(&c->root->list);
		rw_unlock(true, c->root);

		err = uuid_पढ़ो(c, j, &cl);
		अगर (err)
			जाओ err;

		err = "error in recovery";
		अगर (bch_btree_check(c))
			जाओ err;

		bch_journal_mark(c, &journal);
		bch_initial_gc_finish(c);
		pr_debug("btree_check() done\n");

		/*
		 * bcache_journal_next() can't happen sooner, or
		 * btree_gc_finish() will give spurious errors about last_gc >
		 * gc_gen - this is a hack but oh well.
		 */
		bch_journal_next(&c->journal);

		err = "error starting allocator thread";
		अगर (bch_cache_allocator_start(ca))
			जाओ err;

		/*
		 * First place it's safe to allocate: btree_check() and
		 * btree_gc_finish() have to run beक्रमe we have buckets to
		 * allocate, and bch_bucket_alloc_set() might cause a journal
		 * entry to be written so bcache_journal_next() has to be called
		 * first.
		 *
		 * If the uuids were in the old क्रमmat we have to reग_लिखो them
		 * beक्रमe the next journal entry is written:
		 */
		अगर (j->version < BCACHE_JSET_VERSION_UUID)
			__uuid_ग_लिखो(c);

		err = "bcache: replay journal failed";
		अगर (bch_journal_replay(c, &journal))
			जाओ err;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक j;

		pr_notice("invalidating existing data\n");
		ca->sb.keys = clamp_t(पूर्णांक, ca->sb.nbuckets >> 7,
					2, SB_JOURNAL_BUCKETS);

		क्रम (j = 0; j < ca->sb.keys; j++)
			ca->sb.d[j] = ca->sb.first_bucket + j;

		bch_initial_gc_finish(c);

		err = "error starting allocator thread";
		अगर (bch_cache_allocator_start(ca))
			जाओ err;

		mutex_lock(&c->bucket_lock);
		bch_prio_ग_लिखो(ca, true);
		mutex_unlock(&c->bucket_lock);

		err = "cannot allocate new UUID bucket";
		अगर (__uuid_ग_लिखो(c))
			जाओ err;

		err = "cannot allocate new btree root";
		c->root = __bch_btree_node_alloc(c, शून्य, 0, true, शून्य);
		अगर (IS_ERR_OR_शून्य(c->root))
			जाओ err;

		mutex_lock(&c->root->ग_लिखो_lock);
		bkey_copy_key(&c->root->key, &MAX_KEY);
		bch_btree_node_ग_लिखो(c->root, &cl);
		mutex_unlock(&c->root->ग_लिखो_lock);

		bch_btree_set_root(c->root);
		rw_unlock(true, c->root);

		/*
		 * We करोn't want to ग_लिखो the first journal entry until
		 * everything is set up - क्रमtunately journal entries won't be
		 * written until the SET_CACHE_SYNC() here:
		 */
		SET_CACHE_SYNC(&c->cache->sb, true);

		bch_journal_next(&c->journal);
		bch_journal_meta(c, &cl);
	पूर्ण

	err = "error starting gc thread";
	अगर (bch_gc_thपढ़ो_start(c))
		जाओ err;

	closure_sync(&cl);
	c->cache->sb.last_mount = (u32)kसमय_get_real_seconds();
	bcache_ग_लिखो_super(c);

	अगर (bch_has_feature_obso_large_bucket(&c->cache->sb))
		pr_err("Detect obsoleted large bucket layout, all attached bcache device will be read-only\n");

	list_क्रम_each_entry_safe(dc, t, &uncached_devices, list)
		bch_cached_dev_attach(dc, c, शून्य);

	flash_devs_run(c);

	set_bit(CACHE_SET_RUNNING, &c->flags);
	वापस 0;
err:
	जबतक (!list_empty(&journal)) अणु
		l = list_first_entry(&journal, काष्ठा journal_replay, list);
		list_del(&l->list);
		kमुक्त(l);
	पूर्ण

	closure_sync(&cl);

	bch_cache_set_error(c, "%s", err);

	वापस -EIO;
पूर्ण

अटल स्थिर अक्षर *रेजिस्टर_cache_set(काष्ठा cache *ca)
अणु
	अक्षर buf[12];
	स्थिर अक्षर *err = "cannot allocate memory";
	काष्ठा cache_set *c;

	list_क्रम_each_entry(c, &bch_cache_sets, list)
		अगर (!स_भेद(c->set_uuid, ca->sb.set_uuid, 16)) अणु
			अगर (c->cache)
				वापस "duplicate cache set member";

			जाओ found;
		पूर्ण

	c = bch_cache_set_alloc(&ca->sb);
	अगर (!c)
		वापस err;

	err = "error creating kobject";
	अगर (kobject_add(&c->kobj, bcache_kobj, "%pU", c->set_uuid) ||
	    kobject_add(&c->पूर्णांकernal, &c->kobj, "internal"))
		जाओ err;

	अगर (bch_cache_accounting_add_kobjs(&c->accounting, &c->kobj))
		जाओ err;

	bch_debug_init_cache_set(c);

	list_add(&c->list, &bch_cache_sets);
found:
	प्र_लिखो(buf, "cache%i", ca->sb.nr_this_dev);
	अगर (sysfs_create_link(&ca->kobj, &c->kobj, "set") ||
	    sysfs_create_link(&c->kobj, &ca->kobj, buf))
		जाओ err;

	kobject_get(&ca->kobj);
	ca->set = c;
	ca->set->cache = ca;

	err = "failed to run cache set";
	अगर (run_cache_set(c) < 0)
		जाओ err;

	वापस शून्य;
err:
	bch_cache_set_unरेजिस्टर(c);
	वापस err;
पूर्ण

/* Cache device */

/* When ca->kobj released */
व्योम bch_cache_release(काष्ठा kobject *kobj)
अणु
	काष्ठा cache *ca = container_of(kobj, काष्ठा cache, kobj);
	अचिन्हित पूर्णांक i;

	अगर (ca->set) अणु
		BUG_ON(ca->set->cache != ca);
		ca->set->cache = शून्य;
	पूर्ण

	मुक्त_pages((अचिन्हित दीर्घ) ca->disk_buckets, ilog2(meta_bucket_pages(&ca->sb)));
	kमुक्त(ca->prio_buckets);
	vमुक्त(ca->buckets);

	मुक्त_heap(&ca->heap);
	मुक्त_fअगरo(&ca->मुक्त_inc);

	क्रम (i = 0; i < RESERVE_NR; i++)
		मुक्त_fअगरo(&ca->मुक्त[i]);

	अगर (ca->sb_disk)
		put_page(virt_to_page(ca->sb_disk));

	अगर (!IS_ERR_OR_शून्य(ca->bdev))
		blkdev_put(ca->bdev, FMODE_READ|FMODE_WRITE|FMODE_EXCL);

	kमुक्त(ca);
	module_put(THIS_MODULE);
पूर्ण

अटल पूर्णांक cache_alloc(काष्ठा cache *ca)
अणु
	माप_प्रकार मुक्त;
	माप_प्रकार btree_buckets;
	काष्ठा bucket *b;
	पूर्णांक ret = -ENOMEM;
	स्थिर अक्षर *err = शून्य;

	__module_get(THIS_MODULE);
	kobject_init(&ca->kobj, &bch_cache_ktype);

	bio_init(&ca->journal.bio, ca->journal.bio.bi_अंतरभूत_vecs, 8);

	/*
	 * when ca->sb.njournal_buckets is not zero, journal exists,
	 * and in bch_journal_replay(), tree node may split,
	 * so bucket of RESERVE_BTREE type is needed,
	 * the worst situation is all journal buckets are valid journal,
	 * and all the keys need to replay,
	 * so the number of  RESERVE_BTREE type buckets should be as much
	 * as journal buckets
	 */
	btree_buckets = ca->sb.njournal_buckets ?: 8;
	मुक्त = roundup_घात_of_two(ca->sb.nbuckets) >> 10;
	अगर (!मुक्त) अणु
		ret = -EPERM;
		err = "ca->sb.nbuckets is too small";
		जाओ err_मुक्त;
	पूर्ण

	अगर (!init_fअगरo(&ca->मुक्त[RESERVE_BTREE], btree_buckets,
						GFP_KERNEL)) अणु
		err = "ca->free[RESERVE_BTREE] alloc failed";
		जाओ err_btree_alloc;
	पूर्ण

	अगर (!init_fअगरo_exact(&ca->मुक्त[RESERVE_PRIO], prio_buckets(ca),
							GFP_KERNEL)) अणु
		err = "ca->free[RESERVE_PRIO] alloc failed";
		जाओ err_prio_alloc;
	पूर्ण

	अगर (!init_fअगरo(&ca->मुक्त[RESERVE_MOVINGGC], मुक्त, GFP_KERNEL)) अणु
		err = "ca->free[RESERVE_MOVINGGC] alloc failed";
		जाओ err_movinggc_alloc;
	पूर्ण

	अगर (!init_fअगरo(&ca->मुक्त[RESERVE_NONE], मुक्त, GFP_KERNEL)) अणु
		err = "ca->free[RESERVE_NONE] alloc failed";
		जाओ err_none_alloc;
	पूर्ण

	अगर (!init_fअगरo(&ca->मुक्त_inc, मुक्त << 2, GFP_KERNEL)) अणु
		err = "ca->free_inc alloc failed";
		जाओ err_मुक्त_inc_alloc;
	पूर्ण

	अगर (!init_heap(&ca->heap, मुक्त << 3, GFP_KERNEL)) अणु
		err = "ca->heap alloc failed";
		जाओ err_heap_alloc;
	पूर्ण

	ca->buckets = vzalloc(array_size(माप(काष्ठा bucket),
			      ca->sb.nbuckets));
	अगर (!ca->buckets) अणु
		err = "ca->buckets alloc failed";
		जाओ err_buckets_alloc;
	पूर्ण

	ca->prio_buckets = kzalloc(array3_size(माप(uपूर्णांक64_t),
				   prio_buckets(ca), 2),
				   GFP_KERNEL);
	अगर (!ca->prio_buckets) अणु
		err = "ca->prio_buckets alloc failed";
		जाओ err_prio_buckets_alloc;
	पूर्ण

	ca->disk_buckets = alloc_meta_bucket_pages(GFP_KERNEL, &ca->sb);
	अगर (!ca->disk_buckets) अणु
		err = "ca->disk_buckets alloc failed";
		जाओ err_disk_buckets_alloc;
	पूर्ण

	ca->prio_last_buckets = ca->prio_buckets + prio_buckets(ca);

	क्रम_each_bucket(b, ca)
		atomic_set(&b->pin, 0);
	वापस 0;

err_disk_buckets_alloc:
	kमुक्त(ca->prio_buckets);
err_prio_buckets_alloc:
	vमुक्त(ca->buckets);
err_buckets_alloc:
	मुक्त_heap(&ca->heap);
err_heap_alloc:
	मुक्त_fअगरo(&ca->मुक्त_inc);
err_मुक्त_inc_alloc:
	मुक्त_fअगरo(&ca->मुक्त[RESERVE_NONE]);
err_none_alloc:
	मुक्त_fअगरo(&ca->मुक्त[RESERVE_MOVINGGC]);
err_movinggc_alloc:
	मुक्त_fअगरo(&ca->मुक्त[RESERVE_PRIO]);
err_prio_alloc:
	मुक्त_fअगरo(&ca->मुक्त[RESERVE_BTREE]);
err_btree_alloc:
err_मुक्त:
	module_put(THIS_MODULE);
	अगर (err)
		pr_notice("error %s: %s\n", ca->cache_dev_name, err);
	वापस ret;
पूर्ण

अटल पूर्णांक रेजिस्टर_cache(काष्ठा cache_sb *sb, काष्ठा cache_sb_disk *sb_disk,
				काष्ठा block_device *bdev, काष्ठा cache *ca)
अणु
	स्थिर अक्षर *err = शून्य; /* must be set क्रम any error हाल */
	पूर्णांक ret = 0;

	bdevname(bdev, ca->cache_dev_name);
	स_नकल(&ca->sb, sb, माप(काष्ठा cache_sb));
	ca->bdev = bdev;
	ca->bdev->bd_holder = ca;
	ca->sb_disk = sb_disk;

	अगर (blk_queue_discard(bdev_get_queue(bdev)))
		ca->discard = CACHE_DISCARD(&ca->sb);

	ret = cache_alloc(ca);
	अगर (ret != 0) अणु
		/*
		 * If we failed here, it means ca->kobj is not initialized yet,
		 * kobject_put() won't be called and there is no chance to
		 * call blkdev_put() to bdev in bch_cache_release(). So we
		 * explicitly call blkdev_put() here.
		 */
		blkdev_put(bdev, FMODE_READ|FMODE_WRITE|FMODE_EXCL);
		अगर (ret == -ENOMEM)
			err = "cache_alloc(): -ENOMEM";
		अन्यथा अगर (ret == -EPERM)
			err = "cache_alloc(): cache device is too small";
		अन्यथा
			err = "cache_alloc(): unknown error";
		जाओ err;
	पूर्ण

	अगर (kobject_add(&ca->kobj, bdev_kobj(bdev), "bcache")) अणु
		err = "error calling kobject_add";
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mutex_lock(&bch_रेजिस्टर_lock);
	err = रेजिस्टर_cache_set(ca);
	mutex_unlock(&bch_रेजिस्टर_lock);

	अगर (err) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	pr_info("registered cache device %s\n", ca->cache_dev_name);

out:
	kobject_put(&ca->kobj);

err:
	अगर (err)
		pr_notice("error %s: %s\n", ca->cache_dev_name, err);

	वापस ret;
पूर्ण

/* Global पूर्णांकerfaces/init */

अटल sमाप_प्रकार रेजिस्टर_bcache(काष्ठा kobject *k, काष्ठा kobj_attribute *attr,
			       स्थिर अक्षर *buffer, माप_प्रकार size);
अटल sमाप_प्रकार bch_pending_bdevs_cleanup(काष्ठा kobject *k,
					 काष्ठा kobj_attribute *attr,
					 स्थिर अक्षर *buffer, माप_प्रकार size);

kobj_attribute_ग_लिखो(रेजिस्टर,		रेजिस्टर_bcache);
kobj_attribute_ग_लिखो(रेजिस्टर_quiet,	रेजिस्टर_bcache);
kobj_attribute_ग_लिखो(pendings_cleanup,	bch_pending_bdevs_cleanup);

अटल bool bch_is_खोलो_backing(dev_t dev)
अणु
	काष्ठा cache_set *c, *tc;
	काष्ठा cached_dev *dc, *t;

	list_क्रम_each_entry_safe(c, tc, &bch_cache_sets, list)
		list_क्रम_each_entry_safe(dc, t, &c->cached_devs, list)
			अगर (dc->bdev->bd_dev == dev)
				वापस true;
	list_क्रम_each_entry_safe(dc, t, &uncached_devices, list)
		अगर (dc->bdev->bd_dev == dev)
			वापस true;
	वापस false;
पूर्ण

अटल bool bch_is_खोलो_cache(dev_t dev)
अणु
	काष्ठा cache_set *c, *tc;

	list_क्रम_each_entry_safe(c, tc, &bch_cache_sets, list) अणु
		काष्ठा cache *ca = c->cache;

		अगर (ca->bdev->bd_dev == dev)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool bch_is_खोलो(dev_t dev)
अणु
	वापस bch_is_खोलो_cache(dev) || bch_is_खोलो_backing(dev);
पूर्ण

काष्ठा async_reg_args अणु
	काष्ठा delayed_work reg_work;
	अक्षर *path;
	काष्ठा cache_sb *sb;
	काष्ठा cache_sb_disk *sb_disk;
	काष्ठा block_device *bdev;
पूर्ण;

अटल व्योम रेजिस्टर_bdev_worker(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक fail = false;
	काष्ठा async_reg_args *args =
		container_of(work, काष्ठा async_reg_args, reg_work.work);
	काष्ठा cached_dev *dc;

	dc = kzalloc(माप(*dc), GFP_KERNEL);
	अगर (!dc) अणु
		fail = true;
		put_page(virt_to_page(args->sb_disk));
		blkdev_put(args->bdev, FMODE_READ | FMODE_WRITE | FMODE_EXCL);
		जाओ out;
	पूर्ण

	mutex_lock(&bch_रेजिस्टर_lock);
	अगर (रेजिस्टर_bdev(args->sb, args->sb_disk, args->bdev, dc) < 0)
		fail = true;
	mutex_unlock(&bch_रेजिस्टर_lock);

out:
	अगर (fail)
		pr_info("error %s: fail to register backing device\n",
			args->path);
	kमुक्त(args->sb);
	kमुक्त(args->path);
	kमुक्त(args);
	module_put(THIS_MODULE);
पूर्ण

अटल व्योम रेजिस्टर_cache_worker(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक fail = false;
	काष्ठा async_reg_args *args =
		container_of(work, काष्ठा async_reg_args, reg_work.work);
	काष्ठा cache *ca;

	ca = kzalloc(माप(*ca), GFP_KERNEL);
	अगर (!ca) अणु
		fail = true;
		put_page(virt_to_page(args->sb_disk));
		blkdev_put(args->bdev, FMODE_READ | FMODE_WRITE | FMODE_EXCL);
		जाओ out;
	पूर्ण

	/* blkdev_put() will be called in bch_cache_release() */
	अगर (रेजिस्टर_cache(args->sb, args->sb_disk, args->bdev, ca) != 0)
		fail = true;

out:
	अगर (fail)
		pr_info("error %s: fail to register cache device\n",
			args->path);
	kमुक्त(args->sb);
	kमुक्त(args->path);
	kमुक्त(args);
	module_put(THIS_MODULE);
पूर्ण

अटल व्योम रेजिस्टर_device_async(काष्ठा async_reg_args *args)
अणु
	अगर (SB_IS_BDEV(args->sb))
		INIT_DELAYED_WORK(&args->reg_work, रेजिस्टर_bdev_worker);
	अन्यथा
		INIT_DELAYED_WORK(&args->reg_work, रेजिस्टर_cache_worker);

	/* 10 jअगरfies is enough क्रम a delay */
	queue_delayed_work(प्रणाली_wq, &args->reg_work, 10);
पूर्ण

अटल sमाप_प्रकार रेजिस्टर_bcache(काष्ठा kobject *k, काष्ठा kobj_attribute *attr,
			       स्थिर अक्षर *buffer, माप_प्रकार size)
अणु
	स्थिर अक्षर *err;
	अक्षर *path = शून्य;
	काष्ठा cache_sb *sb;
	काष्ठा cache_sb_disk *sb_disk;
	काष्ठा block_device *bdev;
	sमाप_प्रकार ret;
	bool async_registration = false;

#अगर_घोषित CONFIG_BCACHE_ASYNC_REGISTRATION
	async_registration = true;
#पूर्ण_अगर

	ret = -EBUSY;
	err = "failed to reference bcache module";
	अगर (!try_module_get(THIS_MODULE))
		जाओ out;

	/* For latest state of bcache_is_reboot */
	smp_mb();
	err = "bcache is in reboot";
	अगर (bcache_is_reboot)
		जाओ out_module_put;

	ret = -ENOMEM;
	err = "cannot allocate memory";
	path = kstrndup(buffer, size, GFP_KERNEL);
	अगर (!path)
		जाओ out_module_put;

	sb = kदो_स्मृति(माप(काष्ठा cache_sb), GFP_KERNEL);
	अगर (!sb)
		जाओ out_मुक्त_path;

	ret = -EINVAL;
	err = "failed to open device";
	bdev = blkdev_get_by_path(strim(path),
				  FMODE_READ|FMODE_WRITE|FMODE_EXCL,
				  sb);
	अगर (IS_ERR(bdev)) अणु
		अगर (bdev == ERR_PTR(-EBUSY)) अणु
			dev_t dev;

			mutex_lock(&bch_रेजिस्टर_lock);
			अगर (lookup_bdev(strim(path), &dev) == 0 &&
			    bch_is_खोलो(dev))
				err = "device already registered";
			अन्यथा
				err = "device busy";
			mutex_unlock(&bch_रेजिस्टर_lock);
			अगर (attr == &ksysfs_रेजिस्टर_quiet)
				जाओ करोne;
		पूर्ण
		जाओ out_मुक्त_sb;
	पूर्ण

	err = "failed to set blocksize";
	अगर (set_blocksize(bdev, 4096))
		जाओ out_blkdev_put;

	err = पढ़ो_super(sb, bdev, &sb_disk);
	अगर (err)
		जाओ out_blkdev_put;

	err = "failed to register device";

	अगर (async_registration) अणु
		/* रेजिस्टर in asynchronous way */
		काष्ठा async_reg_args *args =
			kzalloc(माप(काष्ठा async_reg_args), GFP_KERNEL);

		अगर (!args) अणु
			ret = -ENOMEM;
			err = "cannot allocate memory";
			जाओ out_put_sb_page;
		पूर्ण

		args->path	= path;
		args->sb	= sb;
		args->sb_disk	= sb_disk;
		args->bdev	= bdev;
		रेजिस्टर_device_async(args);
		/* No रुको and वापसs to user space */
		जाओ async_करोne;
	पूर्ण

	अगर (SB_IS_BDEV(sb)) अणु
		काष्ठा cached_dev *dc = kzalloc(माप(*dc), GFP_KERNEL);

		अगर (!dc)
			जाओ out_put_sb_page;

		mutex_lock(&bch_रेजिस्टर_lock);
		ret = रेजिस्टर_bdev(sb, sb_disk, bdev, dc);
		mutex_unlock(&bch_रेजिस्टर_lock);
		/* blkdev_put() will be called in cached_dev_मुक्त() */
		अगर (ret < 0)
			जाओ out_मुक्त_sb;
	पूर्ण अन्यथा अणु
		काष्ठा cache *ca = kzalloc(माप(*ca), GFP_KERNEL);

		अगर (!ca)
			जाओ out_put_sb_page;

		/* blkdev_put() will be called in bch_cache_release() */
		अगर (रेजिस्टर_cache(sb, sb_disk, bdev, ca) != 0)
			जाओ out_मुक्त_sb;
	पूर्ण

करोne:
	kमुक्त(sb);
	kमुक्त(path);
	module_put(THIS_MODULE);
async_करोne:
	वापस size;

out_put_sb_page:
	put_page(virt_to_page(sb_disk));
out_blkdev_put:
	blkdev_put(bdev, FMODE_READ | FMODE_WRITE | FMODE_EXCL);
out_मुक्त_sb:
	kमुक्त(sb);
out_मुक्त_path:
	kमुक्त(path);
	path = शून्य;
out_module_put:
	module_put(THIS_MODULE);
out:
	pr_info("error %s: %s\n", path?path:"", err);
	वापस ret;
पूर्ण


काष्ठा pdev अणु
	काष्ठा list_head list;
	काष्ठा cached_dev *dc;
पूर्ण;

अटल sमाप_प्रकार bch_pending_bdevs_cleanup(काष्ठा kobject *k,
					 काष्ठा kobj_attribute *attr,
					 स्थिर अक्षर *buffer,
					 माप_प्रकार size)
अणु
	LIST_HEAD(pending_devs);
	sमाप_प्रकार ret = size;
	काष्ठा cached_dev *dc, *tdc;
	काष्ठा pdev *pdev, *tpdev;
	काष्ठा cache_set *c, *tc;

	mutex_lock(&bch_रेजिस्टर_lock);
	list_क्रम_each_entry_safe(dc, tdc, &uncached_devices, list) अणु
		pdev = kदो_स्मृति(माप(काष्ठा pdev), GFP_KERNEL);
		अगर (!pdev)
			अवरोध;
		pdev->dc = dc;
		list_add(&pdev->list, &pending_devs);
	पूर्ण

	list_क्रम_each_entry_safe(pdev, tpdev, &pending_devs, list) अणु
		अक्षर *pdev_set_uuid = pdev->dc->sb.set_uuid;
		list_क्रम_each_entry_safe(c, tc, &bch_cache_sets, list) अणु
			अक्षर *set_uuid = c->set_uuid;

			अगर (!स_भेद(pdev_set_uuid, set_uuid, 16)) अणु
				list_del(&pdev->list);
				kमुक्त(pdev);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&bch_रेजिस्टर_lock);

	list_क्रम_each_entry_safe(pdev, tpdev, &pending_devs, list) अणु
		pr_info("delete pdev %p\n", pdev);
		list_del(&pdev->list);
		bcache_device_stop(&pdev->dc->disk);
		kमुक्त(pdev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bcache_reboot(काष्ठा notअगरier_block *n, अचिन्हित दीर्घ code, व्योम *x)
अणु
	अगर (bcache_is_reboot)
		वापस NOTIFY_DONE;

	अगर (code == SYS_DOWN ||
	    code == SYS_HALT ||
	    code == SYS_POWER_OFF) अणु
		DEFINE_WAIT(रुको);
		अचिन्हित दीर्घ start = jअगरfies;
		bool stopped = false;

		काष्ठा cache_set *c, *tc;
		काष्ठा cached_dev *dc, *tdc;

		mutex_lock(&bch_रेजिस्टर_lock);

		अगर (bcache_is_reboot)
			जाओ out;

		/* New registration is rejected since now */
		bcache_is_reboot = true;
		/*
		 * Make रेजिस्टरing caller (अगर there is) on other CPU
		 * core know bcache_is_reboot set to true earlier
		 */
		smp_mb();

		अगर (list_empty(&bch_cache_sets) &&
		    list_empty(&uncached_devices))
			जाओ out;

		mutex_unlock(&bch_रेजिस्टर_lock);

		pr_info("Stopping all devices:\n");

		/*
		 * The reason bch_रेजिस्टर_lock is not held to call
		 * bch_cache_set_stop() and bcache_device_stop() is to
		 * aव्योम potential deadlock during reboot, because cache
		 * set or bcache device stopping process will acqurie
		 * bch_रेजिस्टर_lock too.
		 *
		 * We are safe here because bcache_is_reboot sets to
		 * true alपढ़ोy, रेजिस्टर_bcache() will reject new
		 * registration now. bcache_is_reboot also makes sure
		 * bcache_reboot() won't be re-entered on by other thपढ़ो,
		 * so there is no race in following list iteration by
		 * list_क्रम_each_entry_safe().
		 */
		list_क्रम_each_entry_safe(c, tc, &bch_cache_sets, list)
			bch_cache_set_stop(c);

		list_क्रम_each_entry_safe(dc, tdc, &uncached_devices, list)
			bcache_device_stop(&dc->disk);


		/*
		 * Give an early chance क्रम other kthपढ़ोs and
		 * kworkers to stop themselves
		 */
		schedule();

		/* What's a condition variable? */
		जबतक (1) अणु
			दीर्घ समयout = start + 10 * HZ - jअगरfies;

			mutex_lock(&bch_रेजिस्टर_lock);
			stopped = list_empty(&bch_cache_sets) &&
				list_empty(&uncached_devices);

			अगर (समयout < 0 || stopped)
				अवरोध;

			prepare_to_रुको(&unरेजिस्टर_रुको, &रुको,
					TASK_UNINTERRUPTIBLE);

			mutex_unlock(&bch_रेजिस्टर_lock);
			schedule_समयout(समयout);
		पूर्ण

		finish_रुको(&unरेजिस्टर_रुको, &रुको);

		अगर (stopped)
			pr_info("All devices stopped\n");
		अन्यथा
			pr_notice("Timeout waiting for devices to be closed\n");
out:
		mutex_unlock(&bch_रेजिस्टर_lock);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block reboot = अणु
	.notअगरier_call	= bcache_reboot,
	.priority	= पूर्णांक_उच्च, /* beक्रमe any real devices */
पूर्ण;

अटल व्योम bcache_निकास(व्योम)
अणु
	bch_debug_निकास();
	bch_request_निकास();
	अगर (bcache_kobj)
		kobject_put(bcache_kobj);
	अगर (bcache_wq)
		destroy_workqueue(bcache_wq);
	अगर (bch_journal_wq)
		destroy_workqueue(bch_journal_wq);
	अगर (bch_flush_wq)
		destroy_workqueue(bch_flush_wq);
	bch_btree_निकास();

	अगर (bcache_major)
		unरेजिस्टर_blkdev(bcache_major, "bcache");
	unरेजिस्टर_reboot_notअगरier(&reboot);
	mutex_destroy(&bch_रेजिस्टर_lock);
पूर्ण

/* Check and fixup module parameters */
अटल व्योम check_module_parameters(व्योम)
अणु
	अगर (bch_cutoff_ग_लिखोback_sync == 0)
		bch_cutoff_ग_लिखोback_sync = CUTOFF_WRITEBACK_SYNC;
	अन्यथा अगर (bch_cutoff_ग_लिखोback_sync > CUTOFF_WRITEBACK_SYNC_MAX) अणु
		pr_warn("set bch_cutoff_writeback_sync (%u) to max value %u\n",
			bch_cutoff_ग_लिखोback_sync, CUTOFF_WRITEBACK_SYNC_MAX);
		bch_cutoff_ग_लिखोback_sync = CUTOFF_WRITEBACK_SYNC_MAX;
	पूर्ण

	अगर (bch_cutoff_ग_लिखोback == 0)
		bch_cutoff_ग_लिखोback = CUTOFF_WRITEBACK;
	अन्यथा अगर (bch_cutoff_ग_लिखोback > CUTOFF_WRITEBACK_MAX) अणु
		pr_warn("set bch_cutoff_writeback (%u) to max value %u\n",
			bch_cutoff_ग_लिखोback, CUTOFF_WRITEBACK_MAX);
		bch_cutoff_ग_लिखोback = CUTOFF_WRITEBACK_MAX;
	पूर्ण

	अगर (bch_cutoff_ग_लिखोback > bch_cutoff_ग_लिखोback_sync) अणु
		pr_warn("set bch_cutoff_writeback (%u) to %u\n",
			bch_cutoff_ग_लिखोback, bch_cutoff_ग_लिखोback_sync);
		bch_cutoff_ग_लिखोback = bch_cutoff_ग_लिखोback_sync;
	पूर्ण
पूर्ण

अटल पूर्णांक __init bcache_init(व्योम)
अणु
	अटल स्थिर काष्ठा attribute *files[] = अणु
		&ksysfs_रेजिस्टर.attr,
		&ksysfs_रेजिस्टर_quiet.attr,
		&ksysfs_pendings_cleanup.attr,
		शून्य
	पूर्ण;

	check_module_parameters();

	mutex_init(&bch_रेजिस्टर_lock);
	init_रुकोqueue_head(&unरेजिस्टर_रुको);
	रेजिस्टर_reboot_notअगरier(&reboot);

	bcache_major = रेजिस्टर_blkdev(0, "bcache");
	अगर (bcache_major < 0) अणु
		unरेजिस्टर_reboot_notअगरier(&reboot);
		mutex_destroy(&bch_रेजिस्टर_lock);
		वापस bcache_major;
	पूर्ण

	अगर (bch_btree_init())
		जाओ err;

	bcache_wq = alloc_workqueue("bcache", WQ_MEM_RECLAIM, 0);
	अगर (!bcache_wq)
		जाओ err;

	/*
	 * Let's not make this `WQ_MEM_RECLAIM` क्रम the following reasons:
	 *
	 * 1. It used `प्रणाली_wq` beक्रमe which also करोes no memory reclaim.
	 * 2. With `WQ_MEM_RECLAIM` desktop stalls, increased boot बार, and
	 *    reduced throughput can be observed.
	 *
	 * We still want to user our own queue to not congest the `प्रणाली_wq`.
	 */
	bch_flush_wq = alloc_workqueue("bch_flush", 0, 0);
	अगर (!bch_flush_wq)
		जाओ err;

	bch_journal_wq = alloc_workqueue("bch_journal", WQ_MEM_RECLAIM, 0);
	अगर (!bch_journal_wq)
		जाओ err;

	bcache_kobj = kobject_create_and_add("bcache", fs_kobj);
	अगर (!bcache_kobj)
		जाओ err;

	अगर (bch_request_init() ||
	    sysfs_create_files(bcache_kobj, files))
		जाओ err;

	bch_debug_init();
	closure_debug_init();

	bcache_is_reboot = false;

	वापस 0;
err:
	bcache_निकास();
	वापस -ENOMEM;
पूर्ण

/*
 * Module hooks
 */
module_निकास(bcache_निकास);
module_init(bcache_init);

module_param(bch_cutoff_ग_लिखोback, uपूर्णांक, 0);
MODULE_PARM_DESC(bch_cutoff_ग_लिखोback, "threshold to cutoff writeback");

module_param(bch_cutoff_ग_लिखोback_sync, uपूर्णांक, 0);
MODULE_PARM_DESC(bch_cutoff_ग_लिखोback_sync, "hard threshold to cutoff writeback");

MODULE_DESCRIPTION("Bcache: a Linux block layer cache");
MODULE_AUTHOR("Kent Overstreet <kent.overstreet@gmail.com>");
MODULE_LICENSE("GPL");
