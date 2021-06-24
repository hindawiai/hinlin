<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Assorted bcache debug code
 *
 * Copyright 2010, 2011 Kent Overstreet <kent.overstreet@gmail.com>
 * Copyright 2012 Google, Inc.
 */

#समावेश "bcache.h"
#समावेश "btree.h"
#समावेश "debug.h"
#समावेश "extents.h"

#समावेश <linux/console.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/seq_file.h>

काष्ठा dentry *bcache_debug;

#अगर_घोषित CONFIG_BCACHE_DEBUG

#घोषणा क्रम_each_written_bset(b, start, i)				\
	क्रम (i = (start);						\
	     (व्योम *) i < (व्योम *) (start) + (KEY_SIZE(&b->key) << 9) &&\
	     i->seq == (start)->seq;					\
	     i = (व्योम *) i + set_blocks(i, block_bytes(b->c->cache)) *	\
		 block_bytes(b->c->cache))

व्योम bch_btree_verअगरy(काष्ठा btree *b)
अणु
	काष्ठा btree *v = b->c->verअगरy_data;
	काष्ठा bset *ondisk, *sorted, *inmemory;
	काष्ठा bio *bio;

	अगर (!b->c->verअगरy || !b->c->verअगरy_ondisk)
		वापस;

	करोwn(&b->io_mutex);
	mutex_lock(&b->c->verअगरy_lock);

	ondisk = b->c->verअगरy_ondisk;
	sorted = b->c->verअगरy_data->keys.set->data;
	inmemory = b->keys.set->data;

	bkey_copy(&v->key, &b->key);
	v->written = 0;
	v->level = b->level;
	v->keys.ops = b->keys.ops;

	bio = bch_bbio_alloc(b->c);
	bio_set_dev(bio, b->c->cache->bdev);
	bio->bi_iter.bi_sector	= PTR_OFFSET(&b->key, 0);
	bio->bi_iter.bi_size	= KEY_SIZE(&v->key) << 9;
	bio->bi_opf		= REQ_OP_READ | REQ_META;
	bch_bio_map(bio, sorted);

	submit_bio_रुको(bio);
	bch_bbio_मुक्त(bio, b->c);

	स_नकल(ondisk, sorted, KEY_SIZE(&v->key) << 9);

	bch_btree_node_पढ़ो_करोne(v);
	sorted = v->keys.set->data;

	अगर (inmemory->keys != sorted->keys ||
	    स_भेद(inmemory->start,
		   sorted->start,
		   (व्योम *) bset_bkey_last(inmemory) -
		   (व्योम *) inmemory->start)) अणु
		काष्ठा bset *i;
		अचिन्हित पूर्णांक j;

		console_lock();

		pr_err("*** in memory:\n");
		bch_dump_bset(&b->keys, inmemory, 0);

		pr_err("*** read back in:\n");
		bch_dump_bset(&v->keys, sorted, 0);

		क्रम_each_written_bset(b, ondisk, i) अणु
			अचिन्हित पूर्णांक block = ((व्योम *) i - (व्योम *) ondisk) /
				block_bytes(b->c->cache);

			pr_err("*** on disk block %u:\n", block);
			bch_dump_bset(&b->keys, i, block);
		पूर्ण

		pr_err("*** block %zu not written\n",
		       ((व्योम *) i - (व्योम *) ondisk) / block_bytes(b->c->cache));

		क्रम (j = 0; j < inmemory->keys; j++)
			अगर (inmemory->d[j] != sorted->d[j])
				अवरोध;

		pr_err("b->written %u\n", b->written);

		console_unlock();
		panic("verify failed at %u\n", j);
	पूर्ण

	mutex_unlock(&b->c->verअगरy_lock);
	up(&b->io_mutex);
पूर्ण

व्योम bch_data_verअगरy(काष्ठा cached_dev *dc, काष्ठा bio *bio)
अणु
	काष्ठा bio *check;
	काष्ठा bio_vec bv, cbv;
	काष्ठा bvec_iter iter, citer = अणु 0 पूर्ण;

	check = bio_kदो_स्मृति(GFP_NOIO, bio_segments(bio));
	अगर (!check)
		वापस;
	bio_set_dev(check, bio->bi_bdev);
	check->bi_opf = REQ_OP_READ;
	check->bi_iter.bi_sector = bio->bi_iter.bi_sector;
	check->bi_iter.bi_size = bio->bi_iter.bi_size;

	bch_bio_map(check, शून्य);
	अगर (bch_bio_alloc_pages(check, GFP_NOIO))
		जाओ out_put;

	submit_bio_रुको(check);

	citer.bi_size = अच_पूर्णांक_उच्च;
	bio_क्रम_each_segment(bv, bio, iter) अणु
		व्योम *p1 = kmap_atomic(bv.bv_page);
		व्योम *p2;

		cbv = bio_iter_iovec(check, citer);
		p2 = page_address(cbv.bv_page);

		cache_set_err_on(स_भेद(p1 + bv.bv_offset,
					p2 + bv.bv_offset,
					bv.bv_len),
				 dc->disk.c,
				 "verify failed at dev %s sector %llu",
				 dc->backing_dev_name,
				 (uपूर्णांक64_t) bio->bi_iter.bi_sector);

		kunmap_atomic(p1);
		bio_advance_iter(check, &citer, bv.bv_len);
	पूर्ण

	bio_मुक्त_pages(check);
out_put:
	bio_put(check);
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_FS

/* XXX: cache set refcounting */

काष्ठा dump_iterator अणु
	अक्षर			buf[PAGE_SIZE];
	माप_प्रकार			bytes;
	काष्ठा cache_set	*c;
	काष्ठा keybuf		keys;
पूर्ण;

अटल bool dump_pred(काष्ठा keybuf *buf, काष्ठा bkey *k)
अणु
	वापस true;
पूर्ण

अटल sमाप_प्रकार bch_dump_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			     माप_प्रकार size, loff_t *ppos)
अणु
	काष्ठा dump_iterator *i = file->निजी_data;
	sमाप_प्रकार ret = 0;
	अक्षर kbuf[80];

	जबतक (size) अणु
		काष्ठा keybuf_key *w;
		अचिन्हित पूर्णांक bytes = min(i->bytes, size);

		अगर (copy_to_user(buf, i->buf, bytes))
			वापस -EFAULT;

		ret	 += bytes;
		buf	 += bytes;
		size	 -= bytes;
		i->bytes -= bytes;
		स_हटाओ(i->buf, i->buf + bytes, i->bytes);

		अगर (i->bytes)
			अवरोध;

		w = bch_keybuf_next_rescan(i->c, &i->keys, &MAX_KEY, dump_pred);
		अगर (!w)
			अवरोध;

		bch_extent_to_text(kbuf, माप(kbuf), &w->key);
		i->bytes = snम_लिखो(i->buf, PAGE_SIZE, "%s\n", kbuf);
		bch_keybuf_del(&i->keys, w);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bch_dump_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा cache_set *c = inode->i_निजी;
	काष्ठा dump_iterator *i;

	i = kzalloc(माप(काष्ठा dump_iterator), GFP_KERNEL);
	अगर (!i)
		वापस -ENOMEM;

	file->निजी_data = i;
	i->c = c;
	bch_keybuf_init(&i->keys);
	i->keys.last_scanned = KEY(0, 0, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक bch_dump_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations cache_set_debug_ops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= bch_dump_खोलो,
	.पढ़ो		= bch_dump_पढ़ो,
	.release	= bch_dump_release
पूर्ण;

व्योम bch_debug_init_cache_set(काष्ठा cache_set *c)
अणु
	अगर (!IS_ERR_OR_शून्य(bcache_debug)) अणु
		अक्षर name[50];

		snम_लिखो(name, 50, "bcache-%pU", c->set_uuid);
		c->debug = debugfs_create_file(name, 0400, bcache_debug, c,
					       &cache_set_debug_ops);
	पूर्ण
पूर्ण

#पूर्ण_अगर

व्योम bch_debug_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(bcache_debug);
पूर्ण

व्योम __init bch_debug_init(व्योम)
अणु
	/*
	 * it is unnecessary to check वापस value of
	 * debugfs_create_file(), we should not care
	 * about this.
	 */
	bcache_debug = debugfs_create_dir("bcache", शून्य);
पूर्ण
