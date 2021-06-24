<शैली गुरु>
/*
 * Copyright तऊ 2017 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#समावेश "../i915_selftest.h"
#समावेश "i915_random.h"

अटल अक्षर *
__sync_prपूर्णांक(काष्ठा i915_syncmap *p,
	     अक्षर *buf, अचिन्हित दीर्घ *sz,
	     अचिन्हित पूर्णांक depth,
	     अचिन्हित पूर्णांक last,
	     अचिन्हित पूर्णांक idx)
अणु
	अचिन्हित दीर्घ len;
	अचिन्हित पूर्णांक i, X;

	अगर (depth) अणु
		अचिन्हित पूर्णांक d;

		क्रम (d = 0; d < depth - 1; d++) अणु
			अगर (last & BIT(depth - d - 1))
				len = scnम_लिखो(buf, *sz, "|   ");
			अन्यथा
				len = scnम_लिखो(buf, *sz, "    ");
			buf += len;
			*sz -= len;
		पूर्ण
		len = scnम_लिखो(buf, *sz, "%x-> ", idx);
		buf += len;
		*sz -= len;
	पूर्ण

	/* We mark bits after the prefix as "X" */
	len = scnम_लिखो(buf, *sz, "0x%016llx", p->prefix << p->height << SHIFT);
	buf += len;
	*sz -= len;
	X = (p->height + SHIFT) / 4;
	scnम_लिखो(buf - X, *sz + X, "%*s", X, "XXXXXXXXXXXXXXXXX");

	अगर (!p->height) अणु
		क्रम_each_set_bit(i, (अचिन्हित दीर्घ *)&p->biपंचांगap, KSYNCMAP) अणु
			len = scnम_लिखो(buf, *sz, " %x:%x,",
					i, __sync_seqno(p)[i]);
			buf += len;
			*sz -= len;
		पूर्ण
		buf -= 1;
		*sz += 1;
	पूर्ण

	len = scnम_लिखो(buf, *sz, "\n");
	buf += len;
	*sz -= len;

	अगर (p->height) अणु
		क्रम_each_set_bit(i, (अचिन्हित दीर्घ *)&p->biपंचांगap, KSYNCMAP) अणु
			buf = __sync_prपूर्णांक(__sync_child(p)[i], buf, sz,
					   depth + 1,
					   last << 1 | !!(p->biपंचांगap >> (i + 1)),
					   i);
		पूर्ण
	पूर्ण

	वापस buf;
पूर्ण

अटल bool
i915_syncmap_prपूर्णांक_to_buf(काष्ठा i915_syncmap *p, अक्षर *buf, अचिन्हित दीर्घ sz)
अणु
	अगर (!p)
		वापस false;

	जबतक (p->parent)
		p = p->parent;

	__sync_prपूर्णांक(p, buf, &sz, 0, 1, 0);
	वापस true;
पूर्ण

अटल पूर्णांक check_syncmap_मुक्त(काष्ठा i915_syncmap **sync)
अणु
	i915_syncmap_मुक्त(sync);
	अगर (*sync) अणु
		pr_err("sync not cleared after free\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dump_syncmap(काष्ठा i915_syncmap *sync, पूर्णांक err)
अणु
	अक्षर *buf;

	अगर (!err)
		वापस check_syncmap_मुक्त(&sync);

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!buf)
		जाओ skip;

	अगर (i915_syncmap_prपूर्णांक_to_buf(sync, buf, PAGE_SIZE))
		pr_err("%s", buf);

	kमुक्त(buf);

skip:
	i915_syncmap_मुक्त(&sync);
	वापस err;
पूर्ण

अटल पूर्णांक igt_syncmap_init(व्योम *arg)
अणु
	काष्ठा i915_syncmap *sync = (व्योम *)~0ul;

	/*
	 * Cursory check that we can initialise a अक्रमom poपूर्णांकer and transक्रमm
	 * it पूर्णांकo the root poपूर्णांकer of a syncmap.
	 */

	i915_syncmap_init(&sync);
	वापस check_syncmap_मुक्त(&sync);
पूर्ण

अटल पूर्णांक check_seqno(काष्ठा i915_syncmap *leaf, अचिन्हित पूर्णांक idx, u32 seqno)
अणु
	अगर (leaf->height) अणु
		pr_err("%s: not a leaf, height is %d\n",
		       __func__, leaf->height);
		वापस -EINVAL;
	पूर्ण

	अगर (__sync_seqno(leaf)[idx] != seqno) अणु
		pr_err("%s: seqno[%d], found %x, expected %x\n",
		       __func__, idx, __sync_seqno(leaf)[idx], seqno);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_one(काष्ठा i915_syncmap **sync, u64 context, u32 seqno)
अणु
	पूर्णांक err;

	err = i915_syncmap_set(sync, context, seqno);
	अगर (err)
		वापस err;

	अगर ((*sync)->height) अणु
		pr_err("Inserting first context=%llx did not return leaf (height=%d, prefix=%llx\n",
		       context, (*sync)->height, (*sync)->prefix);
		वापस -EINVAL;
	पूर्ण

	अगर ((*sync)->parent) अणु
		pr_err("Inserting first context=%llx created branches!\n",
		       context);
		वापस -EINVAL;
	पूर्ण

	अगर (hweight32((*sync)->biपंचांगap) != 1) अणु
		pr_err("First bitmap does not contain a single entry, found %x (count=%d)!\n",
		       (*sync)->biपंचांगap, hweight32((*sync)->biपंचांगap));
		वापस -EINVAL;
	पूर्ण

	err = check_seqno((*sync), ilog2((*sync)->biपंचांगap), seqno);
	अगर (err)
		वापस err;

	अगर (!i915_syncmap_is_later(sync, context, seqno)) अणु
		pr_err("Lookup of first context=%llx/seqno=%x failed!\n",
		       context, seqno);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igt_syncmap_one(व्योम *arg)
अणु
	I915_RND_STATE(prng);
	IGT_TIMEOUT(end_समय);
	काष्ठा i915_syncmap *sync;
	अचिन्हित दीर्घ max = 1;
	पूर्णांक err;

	/*
	 * Check that inserting a new id, creates a leaf and only that leaf.
	 */

	i915_syncmap_init(&sync);

	करो अणु
		u64 context = i915_pअक्रमom_u64_state(&prng);
		अचिन्हित दीर्घ loop;

		err = check_syncmap_मुक्त(&sync);
		अगर (err)
			जाओ out;

		क्रम (loop = 0; loop <= max; loop++) अणु
			err = check_one(&sync, context,
					pअक्रमom_u32_state(&prng));
			अगर (err)
				जाओ out;
		पूर्ण
		max++;
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));
	pr_debug("%s: Completed %lu single insertions\n",
		 __func__, max * (max - 1) / 2);
out:
	वापस dump_syncmap(sync, err);
पूर्ण

अटल पूर्णांक check_leaf(काष्ठा i915_syncmap **sync, u64 context, u32 seqno)
अणु
	पूर्णांक err;

	err = i915_syncmap_set(sync, context, seqno);
	अगर (err)
		वापस err;

	अगर ((*sync)->height) अणु
		pr_err("Inserting context=%llx did not return leaf (height=%d, prefix=%llx\n",
		       context, (*sync)->height, (*sync)->prefix);
		वापस -EINVAL;
	पूर्ण

	अगर (hweight32((*sync)->biपंचांगap) != 1) अणु
		pr_err("First entry into leaf (context=%llx) does not contain a single entry, found %x (count=%d)!\n",
		       context, (*sync)->biपंचांगap, hweight32((*sync)->biपंचांगap));
		वापस -EINVAL;
	पूर्ण

	err = check_seqno((*sync), ilog2((*sync)->biपंचांगap), seqno);
	अगर (err)
		वापस err;

	अगर (!i915_syncmap_is_later(sync, context, seqno)) अणु
		pr_err("Lookup of first entry context=%llx/seqno=%x failed!\n",
		       context, seqno);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igt_syncmap_join_above(व्योम *arg)
अणु
	काष्ठा i915_syncmap *sync;
	अचिन्हित पूर्णांक pass, order;
	पूर्णांक err;

	i915_syncmap_init(&sync);

	/*
	 * When we have a new id that करोesn't fit inside the existing tree,
	 * we need to add a new layer above.
	 *
	 * 1: 0x00000001
	 * 2: 0x00000010
	 * 3: 0x00000100
	 * 4: 0x00001000
	 * ...
	 * Each pass the common prefix shrinks and we have to insert a join.
	 * Each join will only contain two branches, the latest of which
	 * is always a leaf.
	 *
	 * If we then reuse the same set of contexts, we expect to build an
	 * identical tree.
	 */
	क्रम (pass = 0; pass < 3; pass++) अणु
		क्रम (order = 0; order < 64; order += SHIFT) अणु
			u64 context = BIT_ULL(order);
			काष्ठा i915_syncmap *join;

			err = check_leaf(&sync, context, 0);
			अगर (err)
				जाओ out;

			join = sync->parent;
			अगर (!join) /* very first insert will have no parents */
				जारी;

			अगर (!join->height) अणु
				pr_err("Parent with no height!\n");
				err = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (hweight32(join->biपंचांगap) != 2) अणु
				pr_err("Join does not have 2 children: %x (%d)\n",
				       join->biपंचांगap, hweight32(join->biपंचांगap));
				err = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (__sync_child(join)[__sync_branch_idx(join, context)] != sync) अणु
				pr_err("Leaf misplaced in parent!\n");
				err = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	वापस dump_syncmap(sync, err);
पूर्ण

अटल पूर्णांक igt_syncmap_join_below(व्योम *arg)
अणु
	काष्ठा i915_syncmap *sync;
	अचिन्हित पूर्णांक step, order, idx;
	पूर्णांक err = -ENODEV;

	i915_syncmap_init(&sync);

	/*
	 * Check that we can split a compacted branch by replacing it with
	 * a join.
	 */
	क्रम (step = 0; step < KSYNCMAP; step++) अणु
		क्रम (order = 64 - SHIFT; order > 0; order -= SHIFT) अणु
			u64 context = step * BIT_ULL(order);

			err = i915_syncmap_set(&sync, context, 0);
			अगर (err)
				जाओ out;

			अगर (sync->height) अणु
				pr_err("Inserting context=%llx (order=%d, step=%d) did not return leaf (height=%d, prefix=%llx\n",
				       context, order, step, sync->height, sync->prefix);
				err = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (step = 0; step < KSYNCMAP; step++) अणु
		क्रम (order = SHIFT; order < 64; order += SHIFT) अणु
			u64 context = step * BIT_ULL(order);

			अगर (!i915_syncmap_is_later(&sync, context, 0)) अणु
				pr_err("1: context %llx (order=%d, step=%d) not found\n",
				       context, order, step);
				err = -EINVAL;
				जाओ out;
			पूर्ण

			क्रम (idx = 1; idx < KSYNCMAP; idx++) अणु
				अगर (i915_syncmap_is_later(&sync, context + idx, 0)) अणु
					pr_err("1: context %llx (order=%d, step=%d) should not exist\n",
					       context + idx, order, step);
					err = -EINVAL;
					जाओ out;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (order = SHIFT; order < 64; order += SHIFT) अणु
		क्रम (step = 0; step < KSYNCMAP; step++) अणु
			u64 context = step * BIT_ULL(order);

			अगर (!i915_syncmap_is_later(&sync, context, 0)) अणु
				pr_err("2: context %llx (order=%d, step=%d) not found\n",
				       context, order, step);
				err = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	वापस dump_syncmap(sync, err);
पूर्ण

अटल पूर्णांक igt_syncmap_neighbours(व्योम *arg)
अणु
	I915_RND_STATE(prng);
	IGT_TIMEOUT(end_समय);
	काष्ठा i915_syncmap *sync;
	पूर्णांक err = -ENODEV;

	/*
	 * Each leaf holds KSYNCMAP seqno. Check that when we create KSYNCMAP
	 * neighbouring ids, they all fit पूर्णांकo the same leaf.
	 */

	i915_syncmap_init(&sync);
	करो अणु
		u64 context = i915_pअक्रमom_u64_state(&prng) & ~MASK;
		अचिन्हित पूर्णांक idx;

		अगर (i915_syncmap_is_later(&sync, context, 0)) /* Skip repeats */
			जारी;

		क्रम (idx = 0; idx < KSYNCMAP; idx++) अणु
			err = i915_syncmap_set(&sync, context + idx, 0);
			अगर (err)
				जाओ out;

			अगर (sync->height) अणु
				pr_err("Inserting context=%llx did not return leaf (height=%d, prefix=%llx\n",
				       context, sync->height, sync->prefix);
				err = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (sync->biपंचांगap != BIT(idx + 1) - 1) अणु
				pr_err("Inserting neighbouring context=0x%llx+%d, did not fit into the same leaf bitmap=%x (%d), expected %lx (%d)\n",
				       context, idx,
				       sync->biपंचांगap, hweight32(sync->biपंचांगap),
				       BIT(idx + 1) - 1, idx + 1);
				err = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));
out:
	वापस dump_syncmap(sync, err);
पूर्ण

अटल पूर्णांक igt_syncmap_compact(व्योम *arg)
अणु
	काष्ठा i915_syncmap *sync;
	अचिन्हित पूर्णांक idx, order;
	पूर्णांक err = -ENODEV;

	i915_syncmap_init(&sync);

	/*
	 * The syncmap are "space efficient" compressed radix trees - any
	 * branch with only one child is skipped and replaced by the child.
	 *
	 * If we स्थिरruct a tree with ids that are neighbouring at a non-zero
	 * height, we क्रमm a join but each child of that join is directly a
	 * leaf holding the single id.
	 */
	क्रम (order = SHIFT; order < 64; order += SHIFT) अणु
		err = check_syncmap_मुक्त(&sync);
		अगर (err)
			जाओ out;

		/* Create neighbours in the parent */
		क्रम (idx = 0; idx < KSYNCMAP; idx++) अणु
			u64 context = idx * BIT_ULL(order) + idx;

			err = i915_syncmap_set(&sync, context, 0);
			अगर (err)
				जाओ out;

			अगर (sync->height) अणु
				pr_err("Inserting context=%llx (order=%d, idx=%d) did not return leaf (height=%d, prefix=%llx\n",
				       context, order, idx,
				       sync->height, sync->prefix);
				err = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण

		sync = sync->parent;
		अगर (sync->parent) अणु
			pr_err("Parent (join) of last leaf was not the sync!\n");
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (sync->height != order) अणु
			pr_err("Join does not have the expected height, found %d, expected %d\n",
			       sync->height, order);
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (sync->biपंचांगap != BIT(KSYNCMAP) - 1) अणु
			pr_err("Join is not full!, found %x (%d) expected %lx (%d)\n",
			       sync->biपंचांगap, hweight32(sync->biपंचांगap),
			       BIT(KSYNCMAP) - 1, KSYNCMAP);
			err = -EINVAL;
			जाओ out;
		पूर्ण

		/* Each of our children should be a leaf */
		क्रम (idx = 0; idx < KSYNCMAP; idx++) अणु
			काष्ठा i915_syncmap *leaf = __sync_child(sync)[idx];

			अगर (leaf->height) अणु
				pr_err("Child %d is a not leaf!\n", idx);
				err = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (leaf->parent != sync) अणु
				pr_err("Child %d is not attached to us!\n",
				       idx);
				err = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (!is_घातer_of_2(leaf->biपंचांगap)) अणु
				pr_err("Child %d holds more than one id, found %x (%d)\n",
				       idx, leaf->biपंचांगap, hweight32(leaf->biपंचांगap));
				err = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (leaf->biपंचांगap != BIT(idx)) अणु
				pr_err("Child %d has wrong seqno idx, found %d, expected %d\n",
				       idx, ilog2(leaf->biपंचांगap), idx);
				err = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	वापस dump_syncmap(sync, err);
पूर्ण

अटल पूर्णांक igt_syncmap_अक्रमom(व्योम *arg)
अणु
	I915_RND_STATE(prng);
	IGT_TIMEOUT(end_समय);
	काष्ठा i915_syncmap *sync;
	अचिन्हित दीर्घ count, phase, i;
	u32 seqno;
	पूर्णांक err;

	i915_syncmap_init(&sync);

	/*
	 * Having tried to test the inभागidual operations within i915_syncmap,
	 * run a smoketest exploring the entire u64 space with अक्रमom
	 * insertions.
	 */

	count = 0;
	phase = jअगरfies + HZ/100 + 1;
	करो अणु
		u64 context = i915_pअक्रमom_u64_state(&prng);

		err = i915_syncmap_set(&sync, context, 0);
		अगर (err)
			जाओ out;

		count++;
	पूर्ण जबतक (!समय_after(jअगरfies, phase));
	seqno = 0;

	phase = 0;
	करो अणु
		I915_RND_STATE(ctx);
		u32 last_seqno = seqno;
		bool expect;

		seqno = pअक्रमom_u32_state(&prng);
		expect = seqno_later(last_seqno, seqno);

		क्रम (i = 0; i < count; i++) अणु
			u64 context = i915_pअक्रमom_u64_state(&ctx);

			अगर (i915_syncmap_is_later(&sync, context, seqno) != expect) अणु
				pr_err("context=%llu, last=%u this=%u did not match expectation (%d)\n",
				       context, last_seqno, seqno, expect);
				err = -EINVAL;
				जाओ out;
			पूर्ण

			err = i915_syncmap_set(&sync, context, seqno);
			अगर (err)
				जाओ out;
		पूर्ण

		phase++;
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));
	pr_debug("Completed %lu passes, each of %lu contexts\n", phase, count);
out:
	वापस dump_syncmap(sync, err);
पूर्ण

पूर्णांक i915_syncmap_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_syncmap_init),
		SUBTEST(igt_syncmap_one),
		SUBTEST(igt_syncmap_join_above),
		SUBTEST(igt_syncmap_join_below),
		SUBTEST(igt_syncmap_neighbours),
		SUBTEST(igt_syncmap_compact),
		SUBTEST(igt_syncmap_अक्रमom),
	पूर्ण;

	वापस i915_subtests(tests, शून्य);
पूर्ण
