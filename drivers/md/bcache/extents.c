<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010 Kent Overstreet <kent.overstreet@gmail.com>
 *
 * Uses a block device as cache क्रम other block devices; optimized क्रम SSDs.
 * All allocation is करोne in buckets, which should match the erase block size
 * of the device.
 *
 * Buckets containing cached data are kept on a heap sorted by priority;
 * bucket priority is increased on cache hit, and periodically all the buckets
 * on the heap have their priority scaled करोwn. This currently is just used as
 * an LRU but in the future should allow क्रम more पूर्णांकelligent heuristics.
 *
 * Buckets have an 8 bit counter; मुक्तing is accomplished by incrementing the
 * counter. Garbage collection is used to हटाओ stale poपूर्णांकers.
 *
 * Indexing is करोne via a btree; nodes are not necessarily fully sorted, rather
 * as keys are inserted we only sort the pages that have not yet been written.
 * When garbage collection is run, we resort the entire node.
 *
 * All configuration is करोne via sysfs; see Documentation/admin-guide/bcache.rst.
 */

#समावेश "bcache.h"
#समावेश "btree.h"
#समावेश "debug.h"
#समावेश "extents.h"
#समावेश "writeback.h"

अटल व्योम sort_key_next(काष्ठा btree_iter *iter,
			  काष्ठा btree_iter_set *i)
अणु
	i->k = bkey_next(i->k);

	अगर (i->k == i->end)
		*i = iter->data[--iter->used];
पूर्ण

अटल bool bch_key_sort_cmp(काष्ठा btree_iter_set l,
			     काष्ठा btree_iter_set r)
अणु
	पूर्णांक64_t c = bkey_cmp(l.k, r.k);

	वापस c ? c > 0 : l.k < r.k;
पूर्ण

अटल bool __ptr_invalid(काष्ठा cache_set *c, स्थिर काष्ठा bkey *k)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < KEY_PTRS(k); i++)
		अगर (ptr_available(c, k, i)) अणु
			काष्ठा cache *ca = c->cache;
			माप_प्रकार bucket = PTR_BUCKET_NR(c, k, i);
			माप_प्रकार r = bucket_reमुख्यder(c, PTR_OFFSET(k, i));

			अगर (KEY_SIZE(k) + r > c->cache->sb.bucket_size ||
			    bucket <  ca->sb.first_bucket ||
			    bucket >= ca->sb.nbuckets)
				वापस true;
		पूर्ण

	वापस false;
पूर्ण

/* Common among btree and extent ptrs */

अटल स्थिर अक्षर *bch_ptr_status(काष्ठा cache_set *c, स्थिर काष्ठा bkey *k)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < KEY_PTRS(k); i++)
		अगर (ptr_available(c, k, i)) अणु
			काष्ठा cache *ca = c->cache;
			माप_प्रकार bucket = PTR_BUCKET_NR(c, k, i);
			माप_प्रकार r = bucket_reमुख्यder(c, PTR_OFFSET(k, i));

			अगर (KEY_SIZE(k) + r > c->cache->sb.bucket_size)
				वापस "bad, length too big";
			अगर (bucket <  ca->sb.first_bucket)
				वापस "bad, short offset";
			अगर (bucket >= ca->sb.nbuckets)
				वापस "bad, offset past end of device";
			अगर (ptr_stale(c, k, i))
				वापस "stale";
		पूर्ण

	अगर (!bkey_cmp(k, &ZERO_KEY))
		वापस "bad, null key";
	अगर (!KEY_PTRS(k))
		वापस "bad, no pointers";
	अगर (!KEY_SIZE(k))
		वापस "zeroed key";
	वापस "";
पूर्ण

व्योम bch_extent_to_text(अक्षर *buf, माप_प्रकार size, स्थिर काष्ठा bkey *k)
अणु
	अचिन्हित पूर्णांक i = 0;
	अक्षर *out = buf, *end = buf + size;

#घोषणा p(...)	(out += scnम_लिखो(out, end - out, __VA_ARGS__))

	p("%llu:%llu len %llu -> [", KEY_INODE(k), KEY_START(k), KEY_SIZE(k));

	क्रम (i = 0; i < KEY_PTRS(k); i++) अणु
		अगर (i)
			p(", ");

		अगर (PTR_DEV(k, i) == PTR_CHECK_DEV)
			p("check dev");
		अन्यथा
			p("%llu:%llu gen %llu", PTR_DEV(k, i),
			  PTR_OFFSET(k, i), PTR_GEN(k, i));
	पूर्ण

	p("]");

	अगर (KEY_सूचीTY(k))
		p(" dirty");
	अगर (KEY_CSUM(k))
		p(" cs%llu %llx", KEY_CSUM(k), k->ptr[1]);
#अघोषित p
पूर्ण

अटल व्योम bch_bkey_dump(काष्ठा btree_keys *keys, स्थिर काष्ठा bkey *k)
अणु
	काष्ठा btree *b = container_of(keys, काष्ठा btree, keys);
	अचिन्हित पूर्णांक j;
	अक्षर buf[80];

	bch_extent_to_text(buf, माप(buf), k);
	pr_cont(" %s", buf);

	क्रम (j = 0; j < KEY_PTRS(k); j++) अणु
		माप_प्रकार n = PTR_BUCKET_NR(b->c, k, j);

		pr_cont(" bucket %zu", n);
		अगर (n >= b->c->cache->sb.first_bucket && n < b->c->cache->sb.nbuckets)
			pr_cont(" prio %i",
				PTR_BUCKET(b->c, k, j)->prio);
	पूर्ण

	pr_cont(" %s\n", bch_ptr_status(b->c, k));
पूर्ण

/* Btree ptrs */

bool __bch_btree_ptr_invalid(काष्ठा cache_set *c, स्थिर काष्ठा bkey *k)
अणु
	अक्षर buf[80];

	अगर (!KEY_PTRS(k) || !KEY_SIZE(k) || KEY_सूचीTY(k))
		जाओ bad;

	अगर (__ptr_invalid(c, k))
		जाओ bad;

	वापस false;
bad:
	bch_extent_to_text(buf, माप(buf), k);
	cache_bug(c, "spotted btree ptr %s: %s", buf, bch_ptr_status(c, k));
	वापस true;
पूर्ण

अटल bool bch_btree_ptr_invalid(काष्ठा btree_keys *bk, स्थिर काष्ठा bkey *k)
अणु
	काष्ठा btree *b = container_of(bk, काष्ठा btree, keys);

	वापस __bch_btree_ptr_invalid(b->c, k);
पूर्ण

अटल bool btree_ptr_bad_expensive(काष्ठा btree *b, स्थिर काष्ठा bkey *k)
अणु
	अचिन्हित पूर्णांक i;
	अक्षर buf[80];
	काष्ठा bucket *g;

	अगर (mutex_trylock(&b->c->bucket_lock)) अणु
		क्रम (i = 0; i < KEY_PTRS(k); i++)
			अगर (ptr_available(b->c, k, i)) अणु
				g = PTR_BUCKET(b->c, k, i);

				अगर (KEY_सूचीTY(k) ||
				    g->prio != BTREE_PRIO ||
				    (b->c->gc_mark_valid &&
				     GC_MARK(g) != GC_MARK_METADATA))
					जाओ err;
			पूर्ण

		mutex_unlock(&b->c->bucket_lock);
	पूर्ण

	वापस false;
err:
	mutex_unlock(&b->c->bucket_lock);
	bch_extent_to_text(buf, माप(buf), k);
	btree_bug(b,
"inconsistent btree pointer %s: bucket %zi pin %i prio %i gen %i last_gc %i mark %llu",
		  buf, PTR_BUCKET_NR(b->c, k, i), atomic_पढ़ो(&g->pin),
		  g->prio, g->gen, g->last_gc, GC_MARK(g));
	वापस true;
पूर्ण

अटल bool bch_btree_ptr_bad(काष्ठा btree_keys *bk, स्थिर काष्ठा bkey *k)
अणु
	काष्ठा btree *b = container_of(bk, काष्ठा btree, keys);
	अचिन्हित पूर्णांक i;

	अगर (!bkey_cmp(k, &ZERO_KEY) ||
	    !KEY_PTRS(k) ||
	    bch_ptr_invalid(bk, k))
		वापस true;

	क्रम (i = 0; i < KEY_PTRS(k); i++)
		अगर (!ptr_available(b->c, k, i) ||
		    ptr_stale(b->c, k, i))
			वापस true;

	अगर (expensive_debug_checks(b->c) &&
	    btree_ptr_bad_expensive(b, k))
		वापस true;

	वापस false;
पूर्ण

अटल bool bch_btree_ptr_insert_fixup(काष्ठा btree_keys *bk,
				       काष्ठा bkey *insert,
				       काष्ठा btree_iter *iter,
				       काष्ठा bkey *replace_key)
अणु
	काष्ठा btree *b = container_of(bk, काष्ठा btree, keys);

	अगर (!KEY_OFFSET(insert))
		btree_current_ग_लिखो(b)->prio_blocked++;

	वापस false;
पूर्ण

स्थिर काष्ठा btree_keys_ops bch_btree_keys_ops = अणु
	.sort_cmp	= bch_key_sort_cmp,
	.insert_fixup	= bch_btree_ptr_insert_fixup,
	.key_invalid	= bch_btree_ptr_invalid,
	.key_bad	= bch_btree_ptr_bad,
	.key_to_text	= bch_extent_to_text,
	.key_dump	= bch_bkey_dump,
पूर्ण;

/* Extents */

/*
 * Returns true अगर l > r - unless l == r, in which हाल वापसs true अगर l is
 * older than r.
 *
 * Necessary क्रम btree_sort_fixup() - अगर there are multiple keys that compare
 * equal in dअगरferent sets, we have to process them newest to oldest.
 */
अटल bool bch_extent_sort_cmp(काष्ठा btree_iter_set l,
				काष्ठा btree_iter_set r)
अणु
	पूर्णांक64_t c = bkey_cmp(&START_KEY(l.k), &START_KEY(r.k));

	वापस c ? c > 0 : l.k < r.k;
पूर्ण

अटल काष्ठा bkey *bch_extent_sort_fixup(काष्ठा btree_iter *iter,
					  काष्ठा bkey *पंचांगp)
अणु
	जबतक (iter->used > 1) अणु
		काष्ठा btree_iter_set *top = iter->data, *i = top + 1;

		अगर (iter->used > 2 &&
		    bch_extent_sort_cmp(i[0], i[1]))
			i++;

		अगर (bkey_cmp(top->k, &START_KEY(i->k)) <= 0)
			अवरोध;

		अगर (!KEY_SIZE(i->k)) अणु
			sort_key_next(iter, i);
			heap_sअगरt(iter, i - top, bch_extent_sort_cmp);
			जारी;
		पूर्ण

		अगर (top->k > i->k) अणु
			अगर (bkey_cmp(top->k, i->k) >= 0)
				sort_key_next(iter, i);
			अन्यथा
				bch_cut_front(top->k, i->k);

			heap_sअगरt(iter, i - top, bch_extent_sort_cmp);
		पूर्ण अन्यथा अणु
			/* can't happen because of comparison func */
			BUG_ON(!bkey_cmp(&START_KEY(top->k), &START_KEY(i->k)));

			अगर (bkey_cmp(i->k, top->k) < 0) अणु
				bkey_copy(पंचांगp, top->k);

				bch_cut_back(&START_KEY(i->k), पंचांगp);
				bch_cut_front(i->k, top->k);
				heap_sअगरt(iter, 0, bch_extent_sort_cmp);

				वापस पंचांगp;
			पूर्ण अन्यथा अणु
				bch_cut_back(&START_KEY(i->k), top->k);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम bch_subtract_dirty(काष्ठा bkey *k,
			   काष्ठा cache_set *c,
			   uपूर्णांक64_t offset,
			   पूर्णांक sectors)
अणु
	अगर (KEY_सूचीTY(k))
		bcache_dev_sectors_dirty_add(c, KEY_INODE(k),
					     offset, -sectors);
पूर्ण

अटल bool bch_extent_insert_fixup(काष्ठा btree_keys *b,
				    काष्ठा bkey *insert,
				    काष्ठा btree_iter *iter,
				    काष्ठा bkey *replace_key)
अणु
	काष्ठा cache_set *c = container_of(b, काष्ठा btree, keys)->c;

	uपूर्णांक64_t old_offset;
	अचिन्हित पूर्णांक old_size, sectors_found = 0;

	BUG_ON(!KEY_OFFSET(insert));
	BUG_ON(!KEY_SIZE(insert));

	जबतक (1) अणु
		काष्ठा bkey *k = bch_btree_iter_next(iter);

		अगर (!k)
			अवरोध;

		अगर (bkey_cmp(&START_KEY(k), insert) >= 0) अणु
			अगर (KEY_SIZE(k))
				अवरोध;
			अन्यथा
				जारी;
		पूर्ण

		अगर (bkey_cmp(k, &START_KEY(insert)) <= 0)
			जारी;

		old_offset = KEY_START(k);
		old_size = KEY_SIZE(k);

		/*
		 * We might overlap with 0 size extents; we can't skip these
		 * because अगर they're in the set we're inserting to we have to
		 * adjust them so they करोn't overlap with the key we're
		 * inserting. But we करोn't want to check them क्रम replace
		 * operations.
		 */

		अगर (replace_key && KEY_SIZE(k)) अणु
			/*
			 * k might have been split since we inserted/found the
			 * key we're replacing
			 */
			अचिन्हित पूर्णांक i;
			uपूर्णांक64_t offset = KEY_START(k) -
				KEY_START(replace_key);

			/* But it must be a subset of the replace key */
			अगर (KEY_START(k) < KEY_START(replace_key) ||
			    KEY_OFFSET(k) > KEY_OFFSET(replace_key))
				जाओ check_failed;

			/* We didn't find a key that we were supposed to */
			अगर (KEY_START(k) > KEY_START(insert) + sectors_found)
				जाओ check_failed;

			अगर (!bch_bkey_equal_header(k, replace_key))
				जाओ check_failed;

			/* skip past gen */
			offset <<= 8;

			BUG_ON(!KEY_PTRS(replace_key));

			क्रम (i = 0; i < KEY_PTRS(replace_key); i++)
				अगर (k->ptr[i] != replace_key->ptr[i] + offset)
					जाओ check_failed;

			sectors_found = KEY_OFFSET(k) - KEY_START(insert);
		पूर्ण

		अगर (bkey_cmp(insert, k) < 0 &&
		    bkey_cmp(&START_KEY(insert), &START_KEY(k)) > 0) अणु
			/*
			 * We overlapped in the middle of an existing key: that
			 * means we have to split the old key. But we have to करो
			 * slightly dअगरferent things depending on whether the
			 * old key has been written out yet.
			 */

			काष्ठा bkey *top;

			bch_subtract_dirty(k, c, KEY_START(insert),
				       KEY_SIZE(insert));

			अगर (bkey_written(b, k)) अणु
				/*
				 * We insert a new key to cover the top of the
				 * old key, and the old key is modअगरied in place
				 * to represent the bottom split.
				 *
				 * It's completely arbitrary whether the new key
				 * is the top or the bottom, but it has to match
				 * up with what btree_sort_fixup() करोes - it
				 * करोesn't check क्रम this kind of overlap, it
				 * depends on us inserting a new key क्रम the top
				 * here.
				 */
				top = bch_bset_search(b, bset_tree_last(b),
						      insert);
				bch_bset_insert(b, top, k);
			पूर्ण अन्यथा अणु
				BKEY_PADDED(key) temp;
				bkey_copy(&temp.key, k);
				bch_bset_insert(b, k, &temp.key);
				top = bkey_next(k);
			पूर्ण

			bch_cut_front(insert, top);
			bch_cut_back(&START_KEY(insert), k);
			bch_bset_fix_invalidated_key(b, k);
			जाओ out;
		पूर्ण

		अगर (bkey_cmp(insert, k) < 0) अणु
			bch_cut_front(insert, k);
		पूर्ण अन्यथा अणु
			अगर (bkey_cmp(&START_KEY(insert), &START_KEY(k)) > 0)
				old_offset = KEY_START(insert);

			अगर (bkey_written(b, k) &&
			    bkey_cmp(&START_KEY(insert), &START_KEY(k)) <= 0) अणु
				/*
				 * Completely overwrote, so we करोn't have to
				 * invalidate the binary search tree
				 */
				bch_cut_front(k, k);
			पूर्ण अन्यथा अणु
				__bch_cut_back(&START_KEY(insert), k);
				bch_bset_fix_invalidated_key(b, k);
			पूर्ण
		पूर्ण

		bch_subtract_dirty(k, c, old_offset, old_size - KEY_SIZE(k));
	पूर्ण

check_failed:
	अगर (replace_key) अणु
		अगर (!sectors_found) अणु
			वापस true;
		पूर्ण अन्यथा अगर (sectors_found < KEY_SIZE(insert)) अणु
			SET_KEY_OFFSET(insert, KEY_OFFSET(insert) -
				       (KEY_SIZE(insert) - sectors_found));
			SET_KEY_SIZE(insert, sectors_found);
		पूर्ण
	पूर्ण
out:
	अगर (KEY_सूचीTY(insert))
		bcache_dev_sectors_dirty_add(c, KEY_INODE(insert),
					     KEY_START(insert),
					     KEY_SIZE(insert));

	वापस false;
पूर्ण

bool __bch_extent_invalid(काष्ठा cache_set *c, स्थिर काष्ठा bkey *k)
अणु
	अक्षर buf[80];

	अगर (!KEY_SIZE(k))
		वापस true;

	अगर (KEY_SIZE(k) > KEY_OFFSET(k))
		जाओ bad;

	अगर (__ptr_invalid(c, k))
		जाओ bad;

	वापस false;
bad:
	bch_extent_to_text(buf, माप(buf), k);
	cache_bug(c, "spotted extent %s: %s", buf, bch_ptr_status(c, k));
	वापस true;
पूर्ण

अटल bool bch_extent_invalid(काष्ठा btree_keys *bk, स्थिर काष्ठा bkey *k)
अणु
	काष्ठा btree *b = container_of(bk, काष्ठा btree, keys);

	वापस __bch_extent_invalid(b->c, k);
पूर्ण

अटल bool bch_extent_bad_expensive(काष्ठा btree *b, स्थिर काष्ठा bkey *k,
				     अचिन्हित पूर्णांक ptr)
अणु
	काष्ठा bucket *g = PTR_BUCKET(b->c, k, ptr);
	अक्षर buf[80];

	अगर (mutex_trylock(&b->c->bucket_lock)) अणु
		अगर (b->c->gc_mark_valid &&
		    (!GC_MARK(g) ||
		     GC_MARK(g) == GC_MARK_METADATA ||
		     (GC_MARK(g) != GC_MARK_सूचीTY && KEY_सूचीTY(k))))
			जाओ err;

		अगर (g->prio == BTREE_PRIO)
			जाओ err;

		mutex_unlock(&b->c->bucket_lock);
	पूर्ण

	वापस false;
err:
	mutex_unlock(&b->c->bucket_lock);
	bch_extent_to_text(buf, माप(buf), k);
	btree_bug(b,
"inconsistent extent pointer %s:\nbucket %zu pin %i prio %i gen %i last_gc %i mark %llu",
		  buf, PTR_BUCKET_NR(b->c, k, ptr), atomic_पढ़ो(&g->pin),
		  g->prio, g->gen, g->last_gc, GC_MARK(g));
	वापस true;
पूर्ण

अटल bool bch_extent_bad(काष्ठा btree_keys *bk, स्थिर काष्ठा bkey *k)
अणु
	काष्ठा btree *b = container_of(bk, काष्ठा btree, keys);
	अचिन्हित पूर्णांक i, stale;
	अक्षर buf[80];

	अगर (!KEY_PTRS(k) ||
	    bch_extent_invalid(bk, k))
		वापस true;

	क्रम (i = 0; i < KEY_PTRS(k); i++)
		अगर (!ptr_available(b->c, k, i))
			वापस true;

	क्रम (i = 0; i < KEY_PTRS(k); i++) अणु
		stale = ptr_stale(b->c, k, i);

		अगर (stale && KEY_सूचीTY(k)) अणु
			bch_extent_to_text(buf, माप(buf), k);
			pr_info("stale dirty pointer, stale %u, key: %s\n",
				stale, buf);
		पूर्ण

		btree_bug_on(stale > BUCKET_GC_GEN_MAX, b,
			     "key too stale: %i, need_gc %u",
			     stale, b->c->need_gc);

		अगर (stale)
			वापस true;

		अगर (expensive_debug_checks(b->c) &&
		    bch_extent_bad_expensive(b, k, i))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल uपूर्णांक64_t merge_chksums(काष्ठा bkey *l, काष्ठा bkey *r)
अणु
	वापस (l->ptr[KEY_PTRS(l)] + r->ptr[KEY_PTRS(r)]) &
		~((uपूर्णांक64_t)1 << 63);
पूर्ण

अटल bool bch_extent_merge(काष्ठा btree_keys *bk,
			     काष्ठा bkey *l,
			     काष्ठा bkey *r)
अणु
	काष्ठा btree *b = container_of(bk, काष्ठा btree, keys);
	अचिन्हित पूर्णांक i;

	अगर (key_merging_disabled(b->c))
		वापस false;

	क्रम (i = 0; i < KEY_PTRS(l); i++)
		अगर (l->ptr[i] + MAKE_PTR(0, KEY_SIZE(l), 0) != r->ptr[i] ||
		    PTR_BUCKET_NR(b->c, l, i) != PTR_BUCKET_NR(b->c, r, i))
			वापस false;

	/* Keys with no poपूर्णांकers aren't restricted to one bucket and could
	 * overflow KEY_SIZE
	 */
	अगर (KEY_SIZE(l) + KEY_SIZE(r) > अच_लघु_उच्च) अणु
		SET_KEY_OFFSET(l, KEY_OFFSET(l) + अच_लघु_उच्च - KEY_SIZE(l));
		SET_KEY_SIZE(l, अच_लघु_उच्च);

		bch_cut_front(l, r);
		वापस false;
	पूर्ण

	अगर (KEY_CSUM(l)) अणु
		अगर (KEY_CSUM(r))
			l->ptr[KEY_PTRS(l)] = merge_chksums(l, r);
		अन्यथा
			SET_KEY_CSUM(l, 0);
	पूर्ण

	SET_KEY_OFFSET(l, KEY_OFFSET(l) + KEY_SIZE(r));
	SET_KEY_SIZE(l, KEY_SIZE(l) + KEY_SIZE(r));

	वापस true;
पूर्ण

स्थिर काष्ठा btree_keys_ops bch_extent_keys_ops = अणु
	.sort_cmp	= bch_extent_sort_cmp,
	.sort_fixup	= bch_extent_sort_fixup,
	.insert_fixup	= bch_extent_insert_fixup,
	.key_invalid	= bch_extent_invalid,
	.key_bad	= bch_extent_bad,
	.key_merge	= bch_extent_merge,
	.key_to_text	= bch_extent_to_text,
	.key_dump	= bch_bkey_dump,
	.is_extents	= true,
पूर्ण;
