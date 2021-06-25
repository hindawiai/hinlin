<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Moving/copying garbage collector
 *
 * Copyright 2012 Google, Inc.
 */

#समावेश "bcache.h"
#समावेश "btree.h"
#समावेश "debug.h"
#समावेश "request.h"

#समावेश <trace/events/bcache.h>

काष्ठा moving_io अणु
	काष्ठा closure		cl;
	काष्ठा keybuf_key	*w;
	काष्ठा data_insert_op	op;
	काष्ठा bbio		bio;
पूर्ण;

अटल bool moving_pred(काष्ठा keybuf *buf, काष्ठा bkey *k)
अणु
	काष्ठा cache_set *c = container_of(buf, काष्ठा cache_set,
					   moving_gc_keys);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < KEY_PTRS(k); i++)
		अगर (ptr_available(c, k, i) &&
		    GC_MOVE(PTR_BUCKET(c, k, i)))
			वापस true;

	वापस false;
पूर्ण

/* Moving GC - IO loop */

अटल व्योम moving_io_deकाष्ठाor(काष्ठा closure *cl)
अणु
	काष्ठा moving_io *io = container_of(cl, काष्ठा moving_io, cl);

	kमुक्त(io);
पूर्ण

अटल व्योम ग_लिखो_moving_finish(काष्ठा closure *cl)
अणु
	काष्ठा moving_io *io = container_of(cl, काष्ठा moving_io, cl);
	काष्ठा bio *bio = &io->bio.bio;

	bio_मुक्त_pages(bio);

	अगर (io->op.replace_collision)
		trace_bcache_gc_copy_collision(&io->w->key);

	bch_keybuf_del(&io->op.c->moving_gc_keys, io->w);

	up(&io->op.c->moving_in_flight);

	closure_वापस_with_deकाष्ठाor(cl, moving_io_deकाष्ठाor);
पूर्ण

अटल व्योम पढ़ो_moving_endio(काष्ठा bio *bio)
अणु
	काष्ठा bbio *b = container_of(bio, काष्ठा bbio, bio);
	काष्ठा moving_io *io = container_of(bio->bi_निजी,
					    काष्ठा moving_io, cl);

	अगर (bio->bi_status)
		io->op.status = bio->bi_status;
	अन्यथा अगर (!KEY_सूचीTY(&b->key) &&
		 ptr_stale(io->op.c, &b->key, 0)) अणु
		io->op.status = BLK_STS_IOERR;
	पूर्ण

	bch_bbio_endio(io->op.c, bio, bio->bi_status, "reading data to move");
पूर्ण

अटल व्योम moving_init(काष्ठा moving_io *io)
अणु
	काष्ठा bio *bio = &io->bio.bio;

	bio_init(bio, bio->bi_अंतरभूत_vecs,
		 DIV_ROUND_UP(KEY_SIZE(&io->w->key), PAGE_SECTORS));
	bio_get(bio);
	bio_set_prio(bio, IOPRIO_PRIO_VALUE(IOPRIO_CLASS_IDLE, 0));

	bio->bi_iter.bi_size	= KEY_SIZE(&io->w->key) << 9;
	bio->bi_निजी		= &io->cl;
	bch_bio_map(bio, शून्य);
पूर्ण

अटल व्योम ग_लिखो_moving(काष्ठा closure *cl)
अणु
	काष्ठा moving_io *io = container_of(cl, काष्ठा moving_io, cl);
	काष्ठा data_insert_op *op = &io->op;

	अगर (!op->status) अणु
		moving_init(io);

		io->bio.bio.bi_iter.bi_sector = KEY_START(&io->w->key);
		op->ग_लिखो_prio		= 1;
		op->bio			= &io->bio.bio;

		op->ग_लिखोback		= KEY_सूचीTY(&io->w->key);
		op->csum		= KEY_CSUM(&io->w->key);

		bkey_copy(&op->replace_key, &io->w->key);
		op->replace		= true;

		closure_call(&op->cl, bch_data_insert, शून्य, cl);
	पूर्ण

	जारी_at(cl, ग_लिखो_moving_finish, op->wq);
पूर्ण

अटल व्योम पढ़ो_moving_submit(काष्ठा closure *cl)
अणु
	काष्ठा moving_io *io = container_of(cl, काष्ठा moving_io, cl);
	काष्ठा bio *bio = &io->bio.bio;

	bch_submit_bbio(bio, io->op.c, &io->w->key, 0);

	जारी_at(cl, ग_लिखो_moving, io->op.wq);
पूर्ण

अटल व्योम पढ़ो_moving(काष्ठा cache_set *c)
अणु
	काष्ठा keybuf_key *w;
	काष्ठा moving_io *io;
	काष्ठा bio *bio;
	काष्ठा closure cl;

	closure_init_stack(&cl);

	/* XXX: अगर we error, background ग_लिखोback could stall indefinitely */

	जबतक (!test_bit(CACHE_SET_STOPPING, &c->flags)) अणु
		w = bch_keybuf_next_rescan(c, &c->moving_gc_keys,
					   &MAX_KEY, moving_pred);
		अगर (!w)
			अवरोध;

		अगर (ptr_stale(c, &w->key, 0)) अणु
			bch_keybuf_del(&c->moving_gc_keys, w);
			जारी;
		पूर्ण

		io = kzalloc(काष्ठा_size(io, bio.bio.bi_अंतरभूत_vecs,
					 DIV_ROUND_UP(KEY_SIZE(&w->key), PAGE_SECTORS)),
			     GFP_KERNEL);
		अगर (!io)
			जाओ err;

		w->निजी	= io;
		io->w		= w;
		io->op.inode	= KEY_INODE(&w->key);
		io->op.c	= c;
		io->op.wq	= c->moving_gc_wq;

		moving_init(io);
		bio = &io->bio.bio;

		bio_set_op_attrs(bio, REQ_OP_READ, 0);
		bio->bi_end_io	= पढ़ो_moving_endio;

		अगर (bch_bio_alloc_pages(bio, GFP_KERNEL))
			जाओ err;

		trace_bcache_gc_copy(&w->key);

		करोwn(&c->moving_in_flight);
		closure_call(&io->cl, पढ़ो_moving_submit, शून्य, &cl);
	पूर्ण

	अगर (0) अणु
err:		अगर (!IS_ERR_OR_शून्य(w->निजी))
			kमुक्त(w->निजी);

		bch_keybuf_del(&c->moving_gc_keys, w);
	पूर्ण

	closure_sync(&cl);
पूर्ण

अटल bool bucket_cmp(काष्ठा bucket *l, काष्ठा bucket *r)
अणु
	वापस GC_SECTORS_USED(l) < GC_SECTORS_USED(r);
पूर्ण

अटल अचिन्हित पूर्णांक bucket_heap_top(काष्ठा cache *ca)
अणु
	काष्ठा bucket *b;

	वापस (b = heap_peek(&ca->heap)) ? GC_SECTORS_USED(b) : 0;
पूर्ण

व्योम bch_moving_gc(काष्ठा cache_set *c)
अणु
	काष्ठा cache *ca = c->cache;
	काष्ठा bucket *b;
	अचिन्हित दीर्घ sectors_to_move, reserve_sectors;

	अगर (!c->copy_gc_enabled)
		वापस;

	mutex_lock(&c->bucket_lock);

	sectors_to_move = 0;
	reserve_sectors = ca->sb.bucket_size *
			     fअगरo_used(&ca->मुक्त[RESERVE_MOVINGGC]);

	ca->heap.used = 0;

	क्रम_each_bucket(b, ca) अणु
		अगर (GC_MARK(b) == GC_MARK_METADATA ||
		    !GC_SECTORS_USED(b) ||
		    GC_SECTORS_USED(b) == ca->sb.bucket_size ||
		    atomic_पढ़ो(&b->pin))
			जारी;

		अगर (!heap_full(&ca->heap)) अणु
			sectors_to_move += GC_SECTORS_USED(b);
			heap_add(&ca->heap, b, bucket_cmp);
		पूर्ण अन्यथा अगर (bucket_cmp(b, heap_peek(&ca->heap))) अणु
			sectors_to_move -= bucket_heap_top(ca);
			sectors_to_move += GC_SECTORS_USED(b);

			ca->heap.data[0] = b;
			heap_sअगरt(&ca->heap, 0, bucket_cmp);
		पूर्ण
	पूर्ण

	जबतक (sectors_to_move > reserve_sectors) अणु
		heap_pop(&ca->heap, b, bucket_cmp);
		sectors_to_move -= GC_SECTORS_USED(b);
	पूर्ण

	जबतक (heap_pop(&ca->heap, b, bucket_cmp))
		SET_GC_MOVE(b, 1);

	mutex_unlock(&c->bucket_lock);

	c->moving_gc_keys.last_scanned = ZERO_KEY;

	पढ़ो_moving(c);
पूर्ण

व्योम bch_moving_init_cache_set(काष्ठा cache_set *c)
अणु
	bch_keybuf_init(&c->moving_gc_keys);
	sema_init(&c->moving_in_flight, 64);
पूर्ण
