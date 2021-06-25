<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM bcache

#अगर !defined(_TRACE_BCACHE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_BCACHE_H

#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(bcache_request,
	TP_PROTO(काष्ठा bcache_device *d, काष्ठा bio *bio),
	TP_ARGS(d, bio),

	TP_STRUCT__entry(
		__field(dev_t,		dev			)
		__field(अचिन्हित पूर्णांक,	orig_major		)
		__field(अचिन्हित पूर्णांक,	orig_minor		)
		__field(sector_t,	sector			)
		__field(dev_t,		orig_sector		)
		__field(अचिन्हित पूर्णांक,	nr_sector		)
		__array(अक्षर,		rwbs,	6		)
	),

	TP_fast_assign(
		__entry->dev		= bio_dev(bio);
		__entry->orig_major	= d->disk->major;
		__entry->orig_minor	= d->disk->first_minor;
		__entry->sector		= bio->bi_iter.bi_sector;
		__entry->orig_sector	= bio->bi_iter.bi_sector - 16;
		__entry->nr_sector	= bio->bi_iter.bi_size >> 9;
		blk_fill_rwbs(__entry->rwbs, bio->bi_opf);
	),

	TP_prपूर्णांकk("%d,%d %s %llu + %u (from %d,%d @ %llu)",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->rwbs, (अचिन्हित दीर्घ दीर्घ)__entry->sector,
		  __entry->nr_sector, __entry->orig_major, __entry->orig_minor,
		  (अचिन्हित दीर्घ दीर्घ)__entry->orig_sector)
);

DECLARE_EVENT_CLASS(bkey,
	TP_PROTO(काष्ठा bkey *k),
	TP_ARGS(k),

	TP_STRUCT__entry(
		__field(u32,	size				)
		__field(u32,	inode				)
		__field(u64,	offset				)
		__field(bool,	dirty				)
	),

	TP_fast_assign(
		__entry->inode	= KEY_INODE(k);
		__entry->offset	= KEY_OFFSET(k);
		__entry->size	= KEY_SIZE(k);
		__entry->dirty	= KEY_सूचीTY(k);
	),

	TP_prपूर्णांकk("%u:%llu len %u dirty %u", __entry->inode,
		  __entry->offset, __entry->size, __entry->dirty)
);

DECLARE_EVENT_CLASS(btree_node,
	TP_PROTO(काष्ठा btree *b),
	TP_ARGS(b),

	TP_STRUCT__entry(
		__field(माप_प्रकार,		bucket			)
	),

	TP_fast_assign(
		__entry->bucket	= PTR_BUCKET_NR(b->c, &b->key, 0);
	),

	TP_prपूर्णांकk("bucket %zu", __entry->bucket)
);

/* request.c */

DEFINE_EVENT(bcache_request, bcache_request_start,
	TP_PROTO(काष्ठा bcache_device *d, काष्ठा bio *bio),
	TP_ARGS(d, bio)
);

DEFINE_EVENT(bcache_request, bcache_request_end,
	TP_PROTO(काष्ठा bcache_device *d, काष्ठा bio *bio),
	TP_ARGS(d, bio)
);

DECLARE_EVENT_CLASS(bcache_bio,
	TP_PROTO(काष्ठा bio *bio),
	TP_ARGS(bio),

	TP_STRUCT__entry(
		__field(dev_t,		dev			)
		__field(sector_t,	sector			)
		__field(अचिन्हित पूर्णांक,	nr_sector		)
		__array(अक्षर,		rwbs,	6		)
	),

	TP_fast_assign(
		__entry->dev		= bio_dev(bio);
		__entry->sector		= bio->bi_iter.bi_sector;
		__entry->nr_sector	= bio->bi_iter.bi_size >> 9;
		blk_fill_rwbs(__entry->rwbs, bio->bi_opf);
	),

	TP_prपूर्णांकk("%d,%d  %s %llu + %u",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->rwbs,
		  (अचिन्हित दीर्घ दीर्घ)__entry->sector, __entry->nr_sector)
);

DEFINE_EVENT(bcache_bio, bcache_bypass_sequential,
	TP_PROTO(काष्ठा bio *bio),
	TP_ARGS(bio)
);

DEFINE_EVENT(bcache_bio, bcache_bypass_congested,
	TP_PROTO(काष्ठा bio *bio),
	TP_ARGS(bio)
);

TRACE_EVENT(bcache_पढ़ो,
	TP_PROTO(काष्ठा bio *bio, bool hit, bool bypass),
	TP_ARGS(bio, hit, bypass),

	TP_STRUCT__entry(
		__field(dev_t,		dev			)
		__field(sector_t,	sector			)
		__field(अचिन्हित पूर्णांक,	nr_sector		)
		__array(अक्षर,		rwbs,	6		)
		__field(bool,		cache_hit		)
		__field(bool,		bypass			)
	),

	TP_fast_assign(
		__entry->dev		= bio_dev(bio);
		__entry->sector		= bio->bi_iter.bi_sector;
		__entry->nr_sector	= bio->bi_iter.bi_size >> 9;
		blk_fill_rwbs(__entry->rwbs, bio->bi_opf);
		__entry->cache_hit = hit;
		__entry->bypass = bypass;
	),

	TP_prपूर्णांकk("%d,%d  %s %llu + %u hit %u bypass %u",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->rwbs, (अचिन्हित दीर्घ दीर्घ)__entry->sector,
		  __entry->nr_sector, __entry->cache_hit, __entry->bypass)
);

TRACE_EVENT(bcache_ग_लिखो,
	TP_PROTO(काष्ठा cache_set *c, u64 inode, काष्ठा bio *bio,
		bool ग_लिखोback, bool bypass),
	TP_ARGS(c, inode, bio, ग_लिखोback, bypass),

	TP_STRUCT__entry(
		__array(अक्षर,		uuid,	16		)
		__field(u64,		inode			)
		__field(sector_t,	sector			)
		__field(अचिन्हित पूर्णांक,	nr_sector		)
		__array(अक्षर,		rwbs,	6		)
		__field(bool,		ग_लिखोback		)
		__field(bool,		bypass			)
	),

	TP_fast_assign(
		स_नकल(__entry->uuid, c->set_uuid, 16);
		__entry->inode		= inode;
		__entry->sector		= bio->bi_iter.bi_sector;
		__entry->nr_sector	= bio->bi_iter.bi_size >> 9;
		blk_fill_rwbs(__entry->rwbs, bio->bi_opf);
		__entry->ग_लिखोback = ग_लिखोback;
		__entry->bypass = bypass;
	),

	TP_prपूर्णांकk("%pU inode %llu  %s %llu + %u hit %u bypass %u",
		  __entry->uuid, __entry->inode,
		  __entry->rwbs, (अचिन्हित दीर्घ दीर्घ)__entry->sector,
		  __entry->nr_sector, __entry->ग_लिखोback, __entry->bypass)
);

DEFINE_EVENT(bcache_bio, bcache_पढ़ो_retry,
	TP_PROTO(काष्ठा bio *bio),
	TP_ARGS(bio)
);

DEFINE_EVENT(bkey, bcache_cache_insert,
	TP_PROTO(काष्ठा bkey *k),
	TP_ARGS(k)
);

/* Journal */

DECLARE_EVENT_CLASS(cache_set,
	TP_PROTO(काष्ठा cache_set *c),
	TP_ARGS(c),

	TP_STRUCT__entry(
		__array(अक्षर,		uuid,	16 )
	),

	TP_fast_assign(
		स_नकल(__entry->uuid, c->set_uuid, 16);
	),

	TP_prपूर्णांकk("%pU", __entry->uuid)
);

DEFINE_EVENT(bkey, bcache_journal_replay_key,
	TP_PROTO(काष्ठा bkey *k),
	TP_ARGS(k)
);

DEFINE_EVENT(cache_set, bcache_journal_full,
	TP_PROTO(काष्ठा cache_set *c),
	TP_ARGS(c)
);

DEFINE_EVENT(cache_set, bcache_journal_entry_full,
	TP_PROTO(काष्ठा cache_set *c),
	TP_ARGS(c)
);

TRACE_EVENT(bcache_journal_ग_लिखो,
	TP_PROTO(काष्ठा bio *bio, u32 keys),
	TP_ARGS(bio, keys),

	TP_STRUCT__entry(
		__field(dev_t,		dev			)
		__field(sector_t,	sector			)
		__field(अचिन्हित पूर्णांक,	nr_sector		)
		__array(अक्षर,		rwbs,	6		)
		__field(u32,		nr_keys			)
	),

	TP_fast_assign(
		__entry->dev		= bio_dev(bio);
		__entry->sector		= bio->bi_iter.bi_sector;
		__entry->nr_sector	= bio->bi_iter.bi_size >> 9;
		__entry->nr_keys	= keys;
		blk_fill_rwbs(__entry->rwbs, bio->bi_opf);
	),

	TP_prपूर्णांकk("%d,%d  %s %llu + %u keys %u",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->rwbs,
		  (अचिन्हित दीर्घ दीर्घ)__entry->sector, __entry->nr_sector,
		  __entry->nr_keys)
);

/* Btree */

DEFINE_EVENT(cache_set, bcache_btree_cache_cannibalize,
	TP_PROTO(काष्ठा cache_set *c),
	TP_ARGS(c)
);

DEFINE_EVENT(btree_node, bcache_btree_पढ़ो,
	TP_PROTO(काष्ठा btree *b),
	TP_ARGS(b)
);

TRACE_EVENT(bcache_btree_ग_लिखो,
	TP_PROTO(काष्ठा btree *b),
	TP_ARGS(b),

	TP_STRUCT__entry(
		__field(माप_प्रकार,		bucket			)
		__field(अचिन्हित,	block			)
		__field(अचिन्हित,	keys			)
	),

	TP_fast_assign(
		__entry->bucket	= PTR_BUCKET_NR(b->c, &b->key, 0);
		__entry->block	= b->written;
		__entry->keys	= b->keys.set[b->keys.nsets].data->keys;
	),

	TP_prपूर्णांकk("bucket %zu written block %u + %u",
		__entry->bucket, __entry->block, __entry->keys)
);

DEFINE_EVENT(btree_node, bcache_btree_node_alloc,
	TP_PROTO(काष्ठा btree *b),
	TP_ARGS(b)
);

DEFINE_EVENT(cache_set, bcache_btree_node_alloc_fail,
	TP_PROTO(काष्ठा cache_set *c),
	TP_ARGS(c)
);

DEFINE_EVENT(btree_node, bcache_btree_node_मुक्त,
	TP_PROTO(काष्ठा btree *b),
	TP_ARGS(b)
);

TRACE_EVENT(bcache_btree_gc_coalesce,
	TP_PROTO(अचिन्हित nodes),
	TP_ARGS(nodes),

	TP_STRUCT__entry(
		__field(अचिन्हित,	nodes			)
	),

	TP_fast_assign(
		__entry->nodes	= nodes;
	),

	TP_prपूर्णांकk("coalesced %u nodes", __entry->nodes)
);

DEFINE_EVENT(cache_set, bcache_gc_start,
	TP_PROTO(काष्ठा cache_set *c),
	TP_ARGS(c)
);

DEFINE_EVENT(cache_set, bcache_gc_end,
	TP_PROTO(काष्ठा cache_set *c),
	TP_ARGS(c)
);

DEFINE_EVENT(bkey, bcache_gc_copy,
	TP_PROTO(काष्ठा bkey *k),
	TP_ARGS(k)
);

DEFINE_EVENT(bkey, bcache_gc_copy_collision,
	TP_PROTO(काष्ठा bkey *k),
	TP_ARGS(k)
);

TRACE_EVENT(bcache_btree_insert_key,
	TP_PROTO(काष्ठा btree *b, काष्ठा bkey *k, अचिन्हित op, अचिन्हित status),
	TP_ARGS(b, k, op, status),

	TP_STRUCT__entry(
		__field(u64,	btree_node			)
		__field(u32,	btree_level			)
		__field(u32,	inode				)
		__field(u64,	offset				)
		__field(u32,	size				)
		__field(u8,	dirty				)
		__field(u8,	op				)
		__field(u8,	status				)
	),

	TP_fast_assign(
		__entry->btree_node = PTR_BUCKET_NR(b->c, &b->key, 0);
		__entry->btree_level = b->level;
		__entry->inode	= KEY_INODE(k);
		__entry->offset	= KEY_OFFSET(k);
		__entry->size	= KEY_SIZE(k);
		__entry->dirty	= KEY_सूचीTY(k);
		__entry->op = op;
		__entry->status = status;
	),

	TP_prपूर्णांकk("%u for %u at %llu(%u): %u:%llu len %u dirty %u",
		  __entry->status, __entry->op,
		  __entry->btree_node, __entry->btree_level,
		  __entry->inode, __entry->offset,
		  __entry->size, __entry->dirty)
);

DECLARE_EVENT_CLASS(btree_split,
	TP_PROTO(काष्ठा btree *b, अचिन्हित keys),
	TP_ARGS(b, keys),

	TP_STRUCT__entry(
		__field(माप_प्रकार,		bucket			)
		__field(अचिन्हित,	keys			)
	),

	TP_fast_assign(
		__entry->bucket	= PTR_BUCKET_NR(b->c, &b->key, 0);
		__entry->keys	= keys;
	),

	TP_prपूर्णांकk("bucket %zu keys %u", __entry->bucket, __entry->keys)
);

DEFINE_EVENT(btree_split, bcache_btree_node_split,
	TP_PROTO(काष्ठा btree *b, अचिन्हित keys),
	TP_ARGS(b, keys)
);

DEFINE_EVENT(btree_split, bcache_btree_node_compact,
	TP_PROTO(काष्ठा btree *b, अचिन्हित keys),
	TP_ARGS(b, keys)
);

DEFINE_EVENT(btree_node, bcache_btree_set_root,
	TP_PROTO(काष्ठा btree *b),
	TP_ARGS(b)
);

TRACE_EVENT(bcache_keyscan,
	TP_PROTO(अचिन्हित nr_found,
		 अचिन्हित start_inode, uपूर्णांक64_t start_offset,
		 अचिन्हित end_inode, uपूर्णांक64_t end_offset),
	TP_ARGS(nr_found,
		start_inode, start_offset,
		end_inode, end_offset),

	TP_STRUCT__entry(
		__field(__u32,	nr_found			)
		__field(__u32,	start_inode			)
		__field(__u64,	start_offset			)
		__field(__u32,	end_inode			)
		__field(__u64,	end_offset			)
	),

	TP_fast_assign(
		__entry->nr_found	= nr_found;
		__entry->start_inode	= start_inode;
		__entry->start_offset	= start_offset;
		__entry->end_inode	= end_inode;
		__entry->end_offset	= end_offset;
	),

	TP_prपूर्णांकk("found %u keys from %u:%llu to %u:%llu", __entry->nr_found,
		  __entry->start_inode, __entry->start_offset,
		  __entry->end_inode, __entry->end_offset)
);

/* Allocator */

TRACE_EVENT(bcache_invalidate,
	TP_PROTO(काष्ठा cache *ca, माप_प्रकार bucket),
	TP_ARGS(ca, bucket),

	TP_STRUCT__entry(
		__field(अचिन्हित,	sectors			)
		__field(dev_t,		dev			)
		__field(__u64,		offset			)
	),

	TP_fast_assign(
		__entry->dev		= ca->bdev->bd_dev;
		__entry->offset		= bucket << ca->set->bucket_bits;
		__entry->sectors	= GC_SECTORS_USED(&ca->buckets[bucket]);
	),

	TP_prपूर्णांकk("invalidated %u sectors at %d,%d sector=%llu",
		  __entry->sectors, MAJOR(__entry->dev),
		  MINOR(__entry->dev), __entry->offset)
);

TRACE_EVENT(bcache_alloc,
	TP_PROTO(काष्ठा cache *ca, माप_प्रकार bucket),
	TP_ARGS(ca, bucket),

	TP_STRUCT__entry(
		__field(dev_t,		dev			)
		__field(__u64,		offset			)
	),

	TP_fast_assign(
		__entry->dev		= ca->bdev->bd_dev;
		__entry->offset		= bucket << ca->set->bucket_bits;
	),

	TP_prपूर्णांकk("allocated %d,%d sector=%llu", MAJOR(__entry->dev),
		  MINOR(__entry->dev), __entry->offset)
);

TRACE_EVENT(bcache_alloc_fail,
	TP_PROTO(काष्ठा cache *ca, अचिन्हित reserve),
	TP_ARGS(ca, reserve),

	TP_STRUCT__entry(
		__field(dev_t,		dev			)
		__field(अचिन्हित,	मुक्त			)
		__field(अचिन्हित,	मुक्त_inc		)
		__field(अचिन्हित,	blocked			)
	),

	TP_fast_assign(
		__entry->dev		= ca->bdev->bd_dev;
		__entry->मुक्त		= fअगरo_used(&ca->मुक्त[reserve]);
		__entry->मुक्त_inc	= fअगरo_used(&ca->मुक्त_inc);
		__entry->blocked	= atomic_पढ़ो(&ca->set->prio_blocked);
	),

	TP_prपूर्णांकk("alloc fail %d,%d free %u free_inc %u blocked %u",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->मुक्त,
		  __entry->मुक्त_inc, __entry->blocked)
);

/* Background ग_लिखोback */

DEFINE_EVENT(bkey, bcache_ग_लिखोback,
	TP_PROTO(काष्ठा bkey *k),
	TP_ARGS(k)
);

DEFINE_EVENT(bkey, bcache_ग_लिखोback_collision,
	TP_PROTO(काष्ठा bkey *k),
	TP_ARGS(k)
);

#पूर्ण_अगर /* _TRACE_BCACHE_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
