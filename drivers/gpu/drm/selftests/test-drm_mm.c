<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Test हालs क्रम the drm_mm range manager
 */

#घोषणा pr_fmt(fmt) "drm_mm: " fmt

#समावेश <linux/module.h>
#समावेश <linux/prime_numbers.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/kसमय.स>

#समावेश <drm/drm_mm.h>

#समावेश "../lib/drm_random.h"

#घोषणा TESTS "drm_mm_selftests.h"
#समावेश "drm_selftest.h"

अटल अचिन्हित पूर्णांक अक्रमom_seed;
अटल अचिन्हित पूर्णांक max_iterations = 8192;
अटल अचिन्हित पूर्णांक max_prime = 128;

क्रमागत अणु
	BEST,
	BOTTOMUP,
	TOPDOWN,
	EVICT,
पूर्ण;

अटल स्थिर काष्ठा insert_mode अणु
	स्थिर अक्षर *name;
	क्रमागत drm_mm_insert_mode mode;
पूर्ण insert_modes[] = अणु
	[BEST] = अणु "best", DRM_MM_INSERT_BEST पूर्ण,
	[BOTTOMUP] = अणु "bottom-up", DRM_MM_INSERT_LOW पूर्ण,
	[TOPDOWN] = अणु "top-down", DRM_MM_INSERT_HIGH पूर्ण,
	[EVICT] = अणु "evict", DRM_MM_INSERT_EVICT पूर्ण,
	अणुपूर्ण
पूर्ण, evict_modes[] = अणु
	अणु "bottom-up", DRM_MM_INSERT_LOW पूर्ण,
	अणु "top-down", DRM_MM_INSERT_HIGH पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक igt_sanitycheck(व्योम *ignored)
अणु
	pr_info("%s - ok!\n", __func__);
	वापस 0;
पूर्ण

अटल bool निश्चित_no_holes(स्थिर काष्ठा drm_mm *mm)
अणु
	काष्ठा drm_mm_node *hole;
	u64 hole_start, __always_unused hole_end;
	अचिन्हित दीर्घ count;

	count = 0;
	drm_mm_क्रम_each_hole(hole, mm, hole_start, hole_end)
		count++;
	अगर (count) अणु
		pr_err("Expected to find no holes (after reserve), found %lu instead\n", count);
		वापस false;
	पूर्ण

	drm_mm_क्रम_each_node(hole, mm) अणु
		अगर (drm_mm_hole_follows(hole)) अणु
			pr_err("Hole follows node, expected none!\n");
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool निश्चित_one_hole(स्थिर काष्ठा drm_mm *mm, u64 start, u64 end)
अणु
	काष्ठा drm_mm_node *hole;
	u64 hole_start, hole_end;
	अचिन्हित दीर्घ count;
	bool ok = true;

	अगर (end <= start)
		वापस true;

	count = 0;
	drm_mm_क्रम_each_hole(hole, mm, hole_start, hole_end) अणु
		अगर (start != hole_start || end != hole_end) अणु
			अगर (ok)
				pr_err("empty mm has incorrect hole, found (%llx, %llx), expect (%llx, %llx)\n",
				       hole_start, hole_end,
				       start, end);
			ok = false;
		पूर्ण
		count++;
	पूर्ण
	अगर (count != 1) अणु
		pr_err("Expected to find one hole, found %lu instead\n", count);
		ok = false;
	पूर्ण

	वापस ok;
पूर्ण

अटल bool निश्चित_continuous(स्थिर काष्ठा drm_mm *mm, u64 size)
अणु
	काष्ठा drm_mm_node *node, *check, *found;
	अचिन्हित दीर्घ n;
	u64 addr;

	अगर (!निश्चित_no_holes(mm))
		वापस false;

	n = 0;
	addr = 0;
	drm_mm_क्रम_each_node(node, mm) अणु
		अगर (node->start != addr) अणु
			pr_err("node[%ld] list out of order, expected %llx found %llx\n",
			       n, addr, node->start);
			वापस false;
		पूर्ण

		अगर (node->size != size) अणु
			pr_err("node[%ld].size incorrect, expected %llx, found %llx\n",
			       n, size, node->size);
			वापस false;
		पूर्ण

		अगर (drm_mm_hole_follows(node)) अणु
			pr_err("node[%ld] is followed by a hole!\n", n);
			वापस false;
		पूर्ण

		found = शून्य;
		drm_mm_क्रम_each_node_in_range(check, mm, addr, addr + size) अणु
			अगर (node != check) अणु
				pr_err("lookup return wrong node, expected start %llx, found %llx\n",
				       node->start, check->start);
				वापस false;
			पूर्ण
			found = check;
		पूर्ण
		अगर (!found) अणु
			pr_err("lookup failed for node %llx + %llx\n",
			       addr, size);
			वापस false;
		पूर्ण

		addr += size;
		n++;
	पूर्ण

	वापस true;
पूर्ण

अटल u64 misalignment(काष्ठा drm_mm_node *node, u64 alignment)
अणु
	u64 rem;

	अगर (!alignment)
		वापस 0;

	भाग64_u64_rem(node->start, alignment, &rem);
	वापस rem;
पूर्ण

अटल bool निश्चित_node(काष्ठा drm_mm_node *node, काष्ठा drm_mm *mm,
			u64 size, u64 alignment, अचिन्हित दीर्घ color)
अणु
	bool ok = true;

	अगर (!drm_mm_node_allocated(node) || node->mm != mm) अणु
		pr_err("node not allocated\n");
		ok = false;
	पूर्ण

	अगर (node->size != size) अणु
		pr_err("node has wrong size, found %llu, expected %llu\n",
		       node->size, size);
		ok = false;
	पूर्ण

	अगर (misalignment(node, alignment)) अणु
		pr_err("node is misaligned, start %llx rem %llu, expected alignment %llu\n",
		       node->start, misalignment(node, alignment), alignment);
		ok = false;
	पूर्ण

	अगर (node->color != color) अणु
		pr_err("node has wrong color, found %lu, expected %lu\n",
		       node->color, color);
		ok = false;
	पूर्ण

	वापस ok;
पूर्ण

#घोषणा show_mm(mm) करो अणु \
	काष्ठा drm_prपूर्णांकer __p = drm_debug_prपूर्णांकer(__func__); \
	drm_mm_prपूर्णांक((mm), &__p); पूर्ण जबतक (0)

अटल पूर्णांक igt_init(व्योम *ignored)
अणु
	स्थिर अचिन्हित पूर्णांक size = 4096;
	काष्ठा drm_mm mm;
	काष्ठा drm_mm_node पंचांगp;
	पूर्णांक ret = -EINVAL;

	/* Start with some simple checks on initialising the काष्ठा drm_mm */
	स_रखो(&mm, 0, माप(mm));
	अगर (drm_mm_initialized(&mm)) अणु
		pr_err("zeroed mm claims to be initialized\n");
		वापस ret;
	पूर्ण

	स_रखो(&mm, 0xff, माप(mm));
	drm_mm_init(&mm, 0, size);
	अगर (!drm_mm_initialized(&mm)) अणु
		pr_err("mm claims not to be initialized\n");
		जाओ out;
	पूर्ण

	अगर (!drm_mm_clean(&mm)) अणु
		pr_err("mm not empty on creation\n");
		जाओ out;
	पूर्ण

	/* After creation, it should all be one massive hole */
	अगर (!निश्चित_one_hole(&mm, 0, size)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	स_रखो(&पंचांगp, 0, माप(पंचांगp));
	पंचांगp.start = 0;
	पंचांगp.size = size;
	ret = drm_mm_reserve_node(&mm, &पंचांगp);
	अगर (ret) अणु
		pr_err("failed to reserve whole drm_mm\n");
		जाओ out;
	पूर्ण

	/* After filling the range entirely, there should be no holes */
	अगर (!निश्चित_no_holes(&mm)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* And then after emptying it again, the massive hole should be back */
	drm_mm_हटाओ_node(&पंचांगp);
	अगर (!निश्चित_one_hole(&mm, 0, size)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

out:
	अगर (ret)
		show_mm(&mm);
	drm_mm_takeकरोwn(&mm);
	वापस ret;
पूर्ण

अटल पूर्णांक igt_debug(व्योम *ignored)
अणु
	काष्ठा drm_mm mm;
	काष्ठा drm_mm_node nodes[2];
	पूर्णांक ret;

	/* Create a small drm_mm with a couple of nodes and a few holes, and
	 * check that the debug iterator करोesn't explode over a trivial drm_mm.
	 */

	drm_mm_init(&mm, 0, 4096);

	स_रखो(nodes, 0, माप(nodes));
	nodes[0].start = 512;
	nodes[0].size = 1024;
	ret = drm_mm_reserve_node(&mm, &nodes[0]);
	अगर (ret) अणु
		pr_err("failed to reserve node[0] {start=%lld, size=%lld)\n",
		       nodes[0].start, nodes[0].size);
		वापस ret;
	पूर्ण

	nodes[1].size = 1024;
	nodes[1].start = 4096 - 512 - nodes[1].size;
	ret = drm_mm_reserve_node(&mm, &nodes[1]);
	अगर (ret) अणु
		pr_err("failed to reserve node[1] {start=%lld, size=%lld)\n",
		       nodes[1].start, nodes[1].size);
		वापस ret;
	पूर्ण

	show_mm(&mm);
	वापस 0;
पूर्ण

अटल काष्ठा drm_mm_node *set_node(काष्ठा drm_mm_node *node,
				    u64 start, u64 size)
अणु
	node->start = start;
	node->size = size;
	वापस node;
पूर्ण

अटल bool expect_reserve_fail(काष्ठा drm_mm *mm, काष्ठा drm_mm_node *node)
अणु
	पूर्णांक err;

	err = drm_mm_reserve_node(mm, node);
	अगर (likely(err == -ENOSPC))
		वापस true;

	अगर (!err) अणु
		pr_err("impossible reserve succeeded, node %llu + %llu\n",
		       node->start, node->size);
		drm_mm_हटाओ_node(node);
	पूर्ण अन्यथा अणु
		pr_err("impossible reserve failed with wrong error %d [expected %d], node %llu + %llu\n",
		       err, -ENOSPC, node->start, node->size);
	पूर्ण
	वापस false;
पूर्ण

अटल bool check_reserve_boundaries(काष्ठा drm_mm *mm,
				     अचिन्हित पूर्णांक count,
				     u64 size)
अणु
	स्थिर काष्ठा boundary अणु
		u64 start, size;
		स्थिर अक्षर *name;
	पूर्ण boundaries[] = अणु
#घोषणा B(st, sz) अणु (st), (sz), "{ " #st ", " #sz "}" पूर्ण
		B(0, 0),
		B(-size, 0),
		B(size, 0),
		B(size * count, 0),
		B(-size, size),
		B(-size, -size),
		B(-size, 2*size),
		B(0, -size),
		B(size, -size),
		B(count*size, size),
		B(count*size, -size),
		B(count*size, count*size),
		B(count*size, -count*size),
		B(count*size, -(count+1)*size),
		B((count+1)*size, size),
		B((count+1)*size, -size),
		B((count+1)*size, -2*size),
#अघोषित B
	पूर्ण;
	काष्ठा drm_mm_node पंचांगp = अणुपूर्ण;
	पूर्णांक n;

	क्रम (n = 0; n < ARRAY_SIZE(boundaries); n++) अणु
		अगर (!expect_reserve_fail(mm,
					 set_node(&पंचांगp,
						  boundaries[n].start,
						  boundaries[n].size))) अणु
			pr_err("boundary[%d:%s] failed, count=%u, size=%lld\n",
			       n, boundaries[n].name, count, size);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक __igt_reserve(अचिन्हित पूर्णांक count, u64 size)
अणु
	DRM_RND_STATE(prng, अक्रमom_seed);
	काष्ठा drm_mm mm;
	काष्ठा drm_mm_node पंचांगp, *nodes, *node, *next;
	अचिन्हित पूर्णांक *order, n, m, o = 0;
	पूर्णांक ret, err;

	/* For exercising drm_mm_reserve_node(), we want to check that
	 * reservations outside of the drm_mm range are rejected, and to
	 * overlapping and otherwise alपढ़ोy occupied ranges. Afterwards,
	 * the tree and nodes should be पूर्णांकact.
	 */

	DRM_MM_BUG_ON(!count);
	DRM_MM_BUG_ON(!size);

	ret = -ENOMEM;
	order = drm_अक्रमom_order(count, &prng);
	अगर (!order)
		जाओ err;

	nodes = vzalloc(array_size(count, माप(*nodes)));
	अगर (!nodes)
		जाओ err_order;

	ret = -EINVAL;
	drm_mm_init(&mm, 0, count * size);

	अगर (!check_reserve_boundaries(&mm, count, size))
		जाओ out;

	क्रम (n = 0; n < count; n++) अणु
		nodes[n].start = order[n] * size;
		nodes[n].size = size;

		err = drm_mm_reserve_node(&mm, &nodes[n]);
		अगर (err) अणु
			pr_err("reserve failed, step %d, start %llu\n",
			       n, nodes[n].start);
			ret = err;
			जाओ out;
		पूर्ण

		अगर (!drm_mm_node_allocated(&nodes[n])) अणु
			pr_err("reserved node not allocated! step %d, start %llu\n",
			       n, nodes[n].start);
			जाओ out;
		पूर्ण

		अगर (!expect_reserve_fail(&mm, &nodes[n]))
			जाओ out;
	पूर्ण

	/* After अक्रमom insertion the nodes should be in order */
	अगर (!निश्चित_continuous(&mm, size))
		जाओ out;

	/* Repeated use should then fail */
	drm_अक्रमom_reorder(order, count, &prng);
	क्रम (n = 0; n < count; n++) अणु
		अगर (!expect_reserve_fail(&mm,
					 set_node(&पंचांगp, order[n] * size, 1)))
			जाओ out;

		/* Remove and reinsert should work */
		drm_mm_हटाओ_node(&nodes[order[n]]);
		err = drm_mm_reserve_node(&mm, &nodes[order[n]]);
		अगर (err) अणु
			pr_err("reserve failed, step %d, start %llu\n",
			       n, nodes[n].start);
			ret = err;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!निश्चित_continuous(&mm, size))
		जाओ out;

	/* Overlapping use should then fail */
	क्रम (n = 0; n < count; n++) अणु
		अगर (!expect_reserve_fail(&mm, set_node(&पंचांगp, 0, size*count)))
			जाओ out;
	पूर्ण
	क्रम (n = 0; n < count; n++) अणु
		अगर (!expect_reserve_fail(&mm,
					 set_node(&पंचांगp,
						  size * n,
						  size * (count - n))))
			जाओ out;
	पूर्ण

	/* Remove several, reinsert, check full */
	क्रम_each_prime_number(n, min(max_prime, count)) अणु
		क्रम (m = 0; m < n; m++) अणु
			node = &nodes[order[(o + m) % count]];
			drm_mm_हटाओ_node(node);
		पूर्ण

		क्रम (m = 0; m < n; m++) अणु
			node = &nodes[order[(o + m) % count]];
			err = drm_mm_reserve_node(&mm, node);
			अगर (err) अणु
				pr_err("reserve failed, step %d/%d, start %llu\n",
				       m, n, node->start);
				ret = err;
				जाओ out;
			पूर्ण
		पूर्ण

		o += n;

		अगर (!निश्चित_continuous(&mm, size))
			जाओ out;
	पूर्ण

	ret = 0;
out:
	drm_mm_क्रम_each_node_safe(node, next, &mm)
		drm_mm_हटाओ_node(node);
	drm_mm_takeकरोwn(&mm);
	vमुक्त(nodes);
err_order:
	kमुक्त(order);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक igt_reserve(व्योम *ignored)
अणु
	स्थिर अचिन्हित पूर्णांक count = min_t(अचिन्हित पूर्णांक, BIT(10), max_iterations);
	पूर्णांक n, ret;

	क्रम_each_prime_number_from(n, 1, 54) अणु
		u64 size = BIT_ULL(n);

		ret = __igt_reserve(count, size - 1);
		अगर (ret)
			वापस ret;

		ret = __igt_reserve(count, size);
		अगर (ret)
			वापस ret;

		ret = __igt_reserve(count, size + 1);
		अगर (ret)
			वापस ret;

		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

अटल bool expect_insert(काष्ठा drm_mm *mm, काष्ठा drm_mm_node *node,
			  u64 size, u64 alignment, अचिन्हित दीर्घ color,
			  स्थिर काष्ठा insert_mode *mode)
अणु
	पूर्णांक err;

	err = drm_mm_insert_node_generic(mm, node,
					 size, alignment, color,
					 mode->mode);
	अगर (err) अणु
		pr_err("insert (size=%llu, alignment=%llu, color=%lu, mode=%s) failed with err=%d\n",
		       size, alignment, color, mode->name, err);
		वापस false;
	पूर्ण

	अगर (!निश्चित_node(node, mm, size, alignment, color)) अणु
		drm_mm_हटाओ_node(node);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool expect_insert_fail(काष्ठा drm_mm *mm, u64 size)
अणु
	काष्ठा drm_mm_node पंचांगp = अणुपूर्ण;
	पूर्णांक err;

	err = drm_mm_insert_node(mm, &पंचांगp, size);
	अगर (likely(err == -ENOSPC))
		वापस true;

	अगर (!err) अणु
		pr_err("impossible insert succeeded, node %llu + %llu\n",
		       पंचांगp.start, पंचांगp.size);
		drm_mm_हटाओ_node(&पंचांगp);
	पूर्ण अन्यथा अणु
		pr_err("impossible insert failed with wrong error %d [expected %d], size %llu\n",
		       err, -ENOSPC, size);
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक __igt_insert(अचिन्हित पूर्णांक count, u64 size, bool replace)
अणु
	DRM_RND_STATE(prng, अक्रमom_seed);
	स्थिर काष्ठा insert_mode *mode;
	काष्ठा drm_mm mm;
	काष्ठा drm_mm_node *nodes, *node, *next;
	अचिन्हित पूर्णांक *order, n, m, o = 0;
	पूर्णांक ret;

	/* Fill a range with lots of nodes, check it करोesn't fail too early */

	DRM_MM_BUG_ON(!count);
	DRM_MM_BUG_ON(!size);

	ret = -ENOMEM;
	nodes = vदो_स्मृति(array_size(count, माप(*nodes)));
	अगर (!nodes)
		जाओ err;

	order = drm_अक्रमom_order(count, &prng);
	अगर (!order)
		जाओ err_nodes;

	ret = -EINVAL;
	drm_mm_init(&mm, 0, count * size);

	क्रम (mode = insert_modes; mode->name; mode++) अणु
		क्रम (n = 0; n < count; n++) अणु
			काष्ठा drm_mm_node पंचांगp;

			node = replace ? &पंचांगp : &nodes[n];
			स_रखो(node, 0, माप(*node));
			अगर (!expect_insert(&mm, node, size, 0, n, mode)) अणु
				pr_err("%s insert failed, size %llu step %d\n",
				       mode->name, size, n);
				जाओ out;
			पूर्ण

			अगर (replace) अणु
				drm_mm_replace_node(&पंचांगp, &nodes[n]);
				अगर (drm_mm_node_allocated(&पंचांगp)) अणु
					pr_err("replaced old-node still allocated! step %d\n",
					       n);
					जाओ out;
				पूर्ण

				अगर (!निश्चित_node(&nodes[n], &mm, size, 0, n)) अणु
					pr_err("replaced node did not inherit parameters, size %llu step %d\n",
					       size, n);
					जाओ out;
				पूर्ण

				अगर (पंचांगp.start != nodes[n].start) अणु
					pr_err("replaced node mismatch location expected [%llx + %llx], found [%llx + %llx]\n",
					       पंचांगp.start, size,
					       nodes[n].start, nodes[n].size);
					जाओ out;
				पूर्ण
			पूर्ण
		पूर्ण

		/* After अक्रमom insertion the nodes should be in order */
		अगर (!निश्चित_continuous(&mm, size))
			जाओ out;

		/* Repeated use should then fail */
		अगर (!expect_insert_fail(&mm, size))
			जाओ out;

		/* Remove one and reinsert, as the only hole it should refill itself */
		क्रम (n = 0; n < count; n++) अणु
			u64 addr = nodes[n].start;

			drm_mm_हटाओ_node(&nodes[n]);
			अगर (!expect_insert(&mm, &nodes[n], size, 0, n, mode)) अणु
				pr_err("%s reinsert failed, size %llu step %d\n",
				       mode->name, size, n);
				जाओ out;
			पूर्ण

			अगर (nodes[n].start != addr) अणु
				pr_err("%s reinsert node moved, step %d, expected %llx, found %llx\n",
				       mode->name, n, addr, nodes[n].start);
				जाओ out;
			पूर्ण

			अगर (!निश्चित_continuous(&mm, size))
				जाओ out;
		पूर्ण

		/* Remove several, reinsert, check full */
		क्रम_each_prime_number(n, min(max_prime, count)) अणु
			क्रम (m = 0; m < n; m++) अणु
				node = &nodes[order[(o + m) % count]];
				drm_mm_हटाओ_node(node);
			पूर्ण

			क्रम (m = 0; m < n; m++) अणु
				node = &nodes[order[(o + m) % count]];
				अगर (!expect_insert(&mm, node, size, 0, n, mode)) अणु
					pr_err("%s multiple reinsert failed, size %llu step %d\n",
					       mode->name, size, n);
					जाओ out;
				पूर्ण
			पूर्ण

			o += n;

			अगर (!निश्चित_continuous(&mm, size))
				जाओ out;

			अगर (!expect_insert_fail(&mm, size))
				जाओ out;
		पूर्ण

		drm_mm_क्रम_each_node_safe(node, next, &mm)
			drm_mm_हटाओ_node(node);
		DRM_MM_BUG_ON(!drm_mm_clean(&mm));

		cond_resched();
	पूर्ण

	ret = 0;
out:
	drm_mm_क्रम_each_node_safe(node, next, &mm)
		drm_mm_हटाओ_node(node);
	drm_mm_takeकरोwn(&mm);
	kमुक्त(order);
err_nodes:
	vमुक्त(nodes);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक igt_insert(व्योम *ignored)
अणु
	स्थिर अचिन्हित पूर्णांक count = min_t(अचिन्हित पूर्णांक, BIT(10), max_iterations);
	अचिन्हित पूर्णांक n;
	पूर्णांक ret;

	क्रम_each_prime_number_from(n, 1, 54) अणु
		u64 size = BIT_ULL(n);

		ret = __igt_insert(count, size - 1, false);
		अगर (ret)
			वापस ret;

		ret = __igt_insert(count, size, false);
		अगर (ret)
			वापस ret;

		ret = __igt_insert(count, size + 1, false);
		अगर (ret)
			वापस ret;

		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igt_replace(व्योम *ignored)
अणु
	स्थिर अचिन्हित पूर्णांक count = min_t(अचिन्हित पूर्णांक, BIT(10), max_iterations);
	अचिन्हित पूर्णांक n;
	पूर्णांक ret;

	/* Reuse igt_insert to exercise replacement by inserting a dummy node,
	 * then replacing it with the पूर्णांकended node. We want to check that
	 * the tree is पूर्णांकact and all the inक्रमmation we need is carried
	 * across to the target node.
	 */

	क्रम_each_prime_number_from(n, 1, 54) अणु
		u64 size = BIT_ULL(n);

		ret = __igt_insert(count, size - 1, true);
		अगर (ret)
			वापस ret;

		ret = __igt_insert(count, size, true);
		अगर (ret)
			वापस ret;

		ret = __igt_insert(count, size + 1, true);
		अगर (ret)
			वापस ret;

		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

अटल bool expect_insert_in_range(काष्ठा drm_mm *mm, काष्ठा drm_mm_node *node,
				   u64 size, u64 alignment, अचिन्हित दीर्घ color,
				   u64 range_start, u64 range_end,
				   स्थिर काष्ठा insert_mode *mode)
अणु
	पूर्णांक err;

	err = drm_mm_insert_node_in_range(mm, node,
					  size, alignment, color,
					  range_start, range_end,
					  mode->mode);
	अगर (err) अणु
		pr_err("insert (size=%llu, alignment=%llu, color=%lu, mode=%s) nto range [%llx, %llx] failed with err=%d\n",
		       size, alignment, color, mode->name,
		       range_start, range_end, err);
		वापस false;
	पूर्ण

	अगर (!निश्चित_node(node, mm, size, alignment, color)) अणु
		drm_mm_हटाओ_node(node);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool expect_insert_in_range_fail(काष्ठा drm_mm *mm,
					u64 size,
					u64 range_start,
					u64 range_end)
अणु
	काष्ठा drm_mm_node पंचांगp = अणुपूर्ण;
	पूर्णांक err;

	err = drm_mm_insert_node_in_range(mm, &पंचांगp,
					  size, 0, 0,
					  range_start, range_end,
					  0);
	अगर (likely(err == -ENOSPC))
		वापस true;

	अगर (!err) अणु
		pr_err("impossible insert succeeded, node %llx + %llu, range [%llx, %llx]\n",
		       पंचांगp.start, पंचांगp.size, range_start, range_end);
		drm_mm_हटाओ_node(&पंचांगp);
	पूर्ण अन्यथा अणु
		pr_err("impossible insert failed with wrong error %d [expected %d], size %llu, range [%llx, %llx]\n",
		       err, -ENOSPC, size, range_start, range_end);
	पूर्ण

	वापस false;
पूर्ण

अटल bool निश्चित_contiguous_in_range(काष्ठा drm_mm *mm,
				       u64 size,
				       u64 start,
				       u64 end)
अणु
	काष्ठा drm_mm_node *node;
	अचिन्हित पूर्णांक n;

	अगर (!expect_insert_in_range_fail(mm, size, start, end))
		वापस false;

	n = भाग64_u64(start + size - 1, size);
	drm_mm_क्रम_each_node(node, mm) अणु
		अगर (node->start < start || node->start + node->size > end) अणु
			pr_err("node %d out of range, address [%llx + %llu], range [%llx, %llx]\n",
			       n, node->start, node->start + node->size, start, end);
			वापस false;
		पूर्ण

		अगर (node->start != n * size) अणु
			pr_err("node %d out of order, expected start %llx, found %llx\n",
			       n, n * size, node->start);
			वापस false;
		पूर्ण

		अगर (node->size != size) अणु
			pr_err("node %d has wrong size, expected size %llx, found %llx\n",
			       n, size, node->size);
			वापस false;
		पूर्ण

		अगर (drm_mm_hole_follows(node) &&
		    drm_mm_hole_node_end(node) < end) अणु
			pr_err("node %d is followed by a hole!\n", n);
			वापस false;
		पूर्ण

		n++;
	पूर्ण

	अगर (start > 0) अणु
		node = __drm_mm_पूर्णांकerval_first(mm, 0, start - 1);
		अगर (drm_mm_node_allocated(node)) अणु
			pr_err("node before start: node=%llx+%llu, start=%llx\n",
			       node->start, node->size, start);
			वापस false;
		पूर्ण
	पूर्ण

	अगर (end < U64_MAX) अणु
		node = __drm_mm_पूर्णांकerval_first(mm, end, U64_MAX);
		अगर (drm_mm_node_allocated(node)) अणु
			pr_err("node after end: node=%llx+%llu, end=%llx\n",
			       node->start, node->size, end);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक __igt_insert_range(अचिन्हित पूर्णांक count, u64 size, u64 start, u64 end)
अणु
	स्थिर काष्ठा insert_mode *mode;
	काष्ठा drm_mm mm;
	काष्ठा drm_mm_node *nodes, *node, *next;
	अचिन्हित पूर्णांक n, start_n, end_n;
	पूर्णांक ret;

	DRM_MM_BUG_ON(!count);
	DRM_MM_BUG_ON(!size);
	DRM_MM_BUG_ON(end <= start);

	/* Very similar to __igt_insert(), but now instead of populating the
	 * full range of the drm_mm, we try to fill a small portion of it.
	 */

	ret = -ENOMEM;
	nodes = vzalloc(array_size(count, माप(*nodes)));
	अगर (!nodes)
		जाओ err;

	ret = -EINVAL;
	drm_mm_init(&mm, 0, count * size);

	start_n = भाग64_u64(start + size - 1, size);
	end_n = भाग64_u64(end - size, size);

	क्रम (mode = insert_modes; mode->name; mode++) अणु
		क्रम (n = start_n; n <= end_n; n++) अणु
			अगर (!expect_insert_in_range(&mm, &nodes[n],
						    size, size, n,
						    start, end, mode)) अणु
				pr_err("%s insert failed, size %llu, step %d [%d, %d], range [%llx, %llx]\n",
				       mode->name, size, n,
				       start_n, end_n,
				       start, end);
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (!निश्चित_contiguous_in_range(&mm, size, start, end)) अणु
			pr_err("%s: range [%llx, %llx] not full after initialisation, size=%llu\n",
			       mode->name, start, end, size);
			जाओ out;
		पूर्ण

		/* Remove one and reinsert, it should refill itself */
		क्रम (n = start_n; n <= end_n; n++) अणु
			u64 addr = nodes[n].start;

			drm_mm_हटाओ_node(&nodes[n]);
			अगर (!expect_insert_in_range(&mm, &nodes[n],
						    size, size, n,
						    start, end, mode)) अणु
				pr_err("%s reinsert failed, step %d\n", mode->name, n);
				जाओ out;
			पूर्ण

			अगर (nodes[n].start != addr) अणु
				pr_err("%s reinsert node moved, step %d, expected %llx, found %llx\n",
				       mode->name, n, addr, nodes[n].start);
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (!निश्चित_contiguous_in_range(&mm, size, start, end)) अणु
			pr_err("%s: range [%llx, %llx] not full after reinsertion, size=%llu\n",
			       mode->name, start, end, size);
			जाओ out;
		पूर्ण

		drm_mm_क्रम_each_node_safe(node, next, &mm)
			drm_mm_हटाओ_node(node);
		DRM_MM_BUG_ON(!drm_mm_clean(&mm));

		cond_resched();
	पूर्ण

	ret = 0;
out:
	drm_mm_क्रम_each_node_safe(node, next, &mm)
		drm_mm_हटाओ_node(node);
	drm_mm_takeकरोwn(&mm);
	vमुक्त(nodes);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक insert_outside_range(व्योम)
अणु
	काष्ठा drm_mm mm;
	स्थिर अचिन्हित पूर्णांक start = 1024;
	स्थिर अचिन्हित पूर्णांक end = 2048;
	स्थिर अचिन्हित पूर्णांक size = end - start;

	drm_mm_init(&mm, start, size);

	अगर (!expect_insert_in_range_fail(&mm, 1, 0, start))
		वापस -EINVAL;

	अगर (!expect_insert_in_range_fail(&mm, size,
					 start - size/2, start + (size+1)/2))
		वापस -EINVAL;

	अगर (!expect_insert_in_range_fail(&mm, size,
					 end - (size+1)/2, end + size/2))
		वापस -EINVAL;

	अगर (!expect_insert_in_range_fail(&mm, 1, end, end + size))
		वापस -EINVAL;

	drm_mm_takeकरोwn(&mm);
	वापस 0;
पूर्ण

अटल पूर्णांक igt_insert_range(व्योम *ignored)
अणु
	स्थिर अचिन्हित पूर्णांक count = min_t(अचिन्हित पूर्णांक, BIT(13), max_iterations);
	अचिन्हित पूर्णांक n;
	पूर्णांक ret;

	/* Check that requests outside the bounds of drm_mm are rejected. */
	ret = insert_outside_range();
	अगर (ret)
		वापस ret;

	क्रम_each_prime_number_from(n, 1, 50) अणु
		स्थिर u64 size = BIT_ULL(n);
		स्थिर u64 max = count * size;

		ret = __igt_insert_range(count, size, 0, max);
		अगर (ret)
			वापस ret;

		ret = __igt_insert_range(count, size, 1, max);
		अगर (ret)
			वापस ret;

		ret = __igt_insert_range(count, size, 0, max - 1);
		अगर (ret)
			वापस ret;

		ret = __igt_insert_range(count, size, 0, max/2);
		अगर (ret)
			वापस ret;

		ret = __igt_insert_range(count, size, max/2, max);
		अगर (ret)
			वापस ret;

		ret = __igt_insert_range(count, size, max/4+1, 3*max/4-1);
		अगर (ret)
			वापस ret;

		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक prepare_igt_frag(काष्ठा drm_mm *mm,
			    काष्ठा drm_mm_node *nodes,
			    अचिन्हित पूर्णांक num_insert,
			    स्थिर काष्ठा insert_mode *mode)
अणु
	अचिन्हित पूर्णांक size = 4096;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_insert; i++) अणु
		अगर (!expect_insert(mm, &nodes[i], size, 0, i,
				   mode) != 0) अणु
			pr_err("%s insert failed\n", mode->name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* पूर्णांकroduce fragmentation by मुक्तing every other node */
	क्रम (i = 0; i < num_insert; i++) अणु
		अगर (i % 2 == 0)
			drm_mm_हटाओ_node(&nodes[i]);
	पूर्ण

	वापस 0;

पूर्ण

अटल u64 get_insert_समय(काष्ठा drm_mm *mm,
			   अचिन्हित पूर्णांक num_insert,
			   काष्ठा drm_mm_node *nodes,
			   स्थिर काष्ठा insert_mode *mode)
अणु
	अचिन्हित पूर्णांक size = 8192;
	kसमय_प्रकार start;
	अचिन्हित पूर्णांक i;

	start = kसमय_get();
	क्रम (i = 0; i < num_insert; i++) अणु
		अगर (!expect_insert(mm, &nodes[i], size, 0, i, mode) != 0) अणु
			pr_err("%s insert failed\n", mode->name);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), start));
पूर्ण

अटल पूर्णांक igt_frag(व्योम *ignored)
अणु
	काष्ठा drm_mm mm;
	स्थिर काष्ठा insert_mode *mode;
	काष्ठा drm_mm_node *nodes, *node, *next;
	अचिन्हित पूर्णांक insert_size = 10000;
	अचिन्हित पूर्णांक scale_factor = 4;
	पूर्णांक ret = -EINVAL;

	/* We need 4 * insert_size nodes to hold पूर्णांकermediate allocated
	 * drm_mm nodes.
	 * 1 बार क्रम prepare_igt_frag()
	 * 1 बार क्रम get_insert_समय()
	 * 2 बार क्रम get_insert_समय()
	 */
	nodes = vzalloc(array_size(insert_size * 4, माप(*nodes)));
	अगर (!nodes)
		वापस -ENOMEM;

	/* For BOTTOMUP and TOPDOWN, we first fragment the
	 * address space using prepare_igt_frag() and then try to verअगरy
	 * that that insertions scale quadratically from 10k to 20k insertions
	 */
	drm_mm_init(&mm, 1, U64_MAX - 2);
	क्रम (mode = insert_modes; mode->name; mode++) अणु
		u64 insert_समय1, insert_समय2;

		अगर (mode->mode != DRM_MM_INSERT_LOW &&
		    mode->mode != DRM_MM_INSERT_HIGH)
			जारी;

		ret = prepare_igt_frag(&mm, nodes, insert_size, mode);
		अगर (ret)
			जाओ err;

		insert_समय1 = get_insert_समय(&mm, insert_size,
					       nodes + insert_size, mode);
		अगर (insert_समय1 == 0)
			जाओ err;

		insert_समय2 = get_insert_समय(&mm, (insert_size * 2),
					       nodes + insert_size * 2, mode);
		अगर (insert_समय2 == 0)
			जाओ err;

		pr_info("%s fragmented insert of %u and %u insertions took %llu and %llu nsecs\n",
			mode->name, insert_size, insert_size * 2,
			insert_समय1, insert_समय2);

		अगर (insert_समय2 > (scale_factor * insert_समय1)) अणु
			pr_err("%s fragmented insert took %llu nsecs more\n",
			       mode->name,
			       insert_समय2 - (scale_factor * insert_समय1));
			जाओ err;
		पूर्ण

		drm_mm_क्रम_each_node_safe(node, next, &mm)
			drm_mm_हटाओ_node(node);
	पूर्ण

	ret = 0;
err:
	drm_mm_क्रम_each_node_safe(node, next, &mm)
		drm_mm_हटाओ_node(node);
	drm_mm_takeकरोwn(&mm);
	vमुक्त(nodes);

	वापस ret;
पूर्ण

अटल पूर्णांक igt_align(व्योम *ignored)
अणु
	स्थिर काष्ठा insert_mode *mode;
	स्थिर अचिन्हित पूर्णांक max_count = min(8192u, max_prime);
	काष्ठा drm_mm mm;
	काष्ठा drm_mm_node *nodes, *node, *next;
	अचिन्हित पूर्णांक prime;
	पूर्णांक ret = -EINVAL;

	/* For each of the possible insertion modes, we pick a few
	 * arbitrary alignments and check that the inserted node
	 * meets our requirements.
	 */

	nodes = vzalloc(array_size(max_count, माप(*nodes)));
	अगर (!nodes)
		जाओ err;

	drm_mm_init(&mm, 1, U64_MAX - 2);

	क्रम (mode = insert_modes; mode->name; mode++) अणु
		अचिन्हित पूर्णांक i = 0;

		क्रम_each_prime_number_from(prime, 1, max_count) अणु
			u64 size = next_prime_number(prime);

			अगर (!expect_insert(&mm, &nodes[i],
					   size, prime, i,
					   mode)) अणु
				pr_err("%s insert failed with alignment=%d",
				       mode->name, prime);
				जाओ out;
			पूर्ण

			i++;
		पूर्ण

		drm_mm_क्रम_each_node_safe(node, next, &mm)
			drm_mm_हटाओ_node(node);
		DRM_MM_BUG_ON(!drm_mm_clean(&mm));

		cond_resched();
	पूर्ण

	ret = 0;
out:
	drm_mm_क्रम_each_node_safe(node, next, &mm)
		drm_mm_हटाओ_node(node);
	drm_mm_takeकरोwn(&mm);
	vमुक्त(nodes);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक igt_align_pot(पूर्णांक max)
अणु
	काष्ठा drm_mm mm;
	काष्ठा drm_mm_node *node, *next;
	पूर्णांक bit;
	पूर्णांक ret = -EINVAL;

	/* Check that we can align to the full u64 address space */

	drm_mm_init(&mm, 1, U64_MAX - 2);

	क्रम (bit = max - 1; bit; bit--) अणु
		u64 align, size;

		node = kzalloc(माप(*node), GFP_KERNEL);
		अगर (!node) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		align = BIT_ULL(bit);
		size = BIT_ULL(bit-1) + 1;
		अगर (!expect_insert(&mm, node,
				   size, align, bit,
				   &insert_modes[0])) अणु
			pr_err("insert failed with alignment=%llx [%d]",
			       align, bit);
			जाओ out;
		पूर्ण

		cond_resched();
	पूर्ण

	ret = 0;
out:
	drm_mm_क्रम_each_node_safe(node, next, &mm) अणु
		drm_mm_हटाओ_node(node);
		kमुक्त(node);
	पूर्ण
	drm_mm_takeकरोwn(&mm);
	वापस ret;
पूर्ण

अटल पूर्णांक igt_align32(व्योम *ignored)
अणु
	वापस igt_align_pot(32);
पूर्ण

अटल पूर्णांक igt_align64(व्योम *ignored)
अणु
	वापस igt_align_pot(64);
पूर्ण

अटल व्योम show_scan(स्थिर काष्ठा drm_mm_scan *scan)
अणु
	pr_info("scan: hit [%llx, %llx], size=%lld, align=%lld, color=%ld\n",
		scan->hit_start, scan->hit_end,
		scan->size, scan->alignment, scan->color);
पूर्ण

अटल व्योम show_holes(स्थिर काष्ठा drm_mm *mm, पूर्णांक count)
अणु
	u64 hole_start, hole_end;
	काष्ठा drm_mm_node *hole;

	drm_mm_क्रम_each_hole(hole, mm, hole_start, hole_end) अणु
		काष्ठा drm_mm_node *next = list_next_entry(hole, node_list);
		स्थिर अक्षर *node1 = शून्य, *node2 = शून्य;

		अगर (drm_mm_node_allocated(hole))
			node1 = kaप्र_लिखो(GFP_KERNEL,
					  "[%llx + %lld, color=%ld], ",
					  hole->start, hole->size, hole->color);

		अगर (drm_mm_node_allocated(next))
			node2 = kaप्र_लिखो(GFP_KERNEL,
					  ", [%llx + %lld, color=%ld]",
					  next->start, next->size, next->color);

		pr_info("%sHole [%llx - %llx, size %lld]%s\n",
			node1,
			hole_start, hole_end, hole_end - hole_start,
			node2);

		kमुक्त(node2);
		kमुक्त(node1);

		अगर (!--count)
			अवरोध;
	पूर्ण
पूर्ण

काष्ठा evict_node अणु
	काष्ठा drm_mm_node node;
	काष्ठा list_head link;
पूर्ण;

अटल bool evict_nodes(काष्ठा drm_mm_scan *scan,
			काष्ठा evict_node *nodes,
			अचिन्हित पूर्णांक *order,
			अचिन्हित पूर्णांक count,
			bool use_color,
			काष्ठा list_head *evict_list)
अणु
	काष्ठा evict_node *e, *en;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		e = &nodes[order ? order[i] : i];
		list_add(&e->link, evict_list);
		अगर (drm_mm_scan_add_block(scan, &e->node))
			अवरोध;
	पूर्ण
	list_क्रम_each_entry_safe(e, en, evict_list, link) अणु
		अगर (!drm_mm_scan_हटाओ_block(scan, &e->node))
			list_del(&e->link);
	पूर्ण
	अगर (list_empty(evict_list)) अणु
		pr_err("Failed to find eviction: size=%lld [avail=%d], align=%lld (color=%lu)\n",
		       scan->size, count, scan->alignment, scan->color);
		वापस false;
	पूर्ण

	list_क्रम_each_entry(e, evict_list, link)
		drm_mm_हटाओ_node(&e->node);

	अगर (use_color) अणु
		काष्ठा drm_mm_node *node;

		जबतक ((node = drm_mm_scan_color_evict(scan))) अणु
			e = container_of(node, typeof(*e), node);
			drm_mm_हटाओ_node(&e->node);
			list_add(&e->link, evict_list);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (drm_mm_scan_color_evict(scan)) अणु
			pr_err("drm_mm_scan_color_evict unexpectedly reported overlapping nodes!\n");
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool evict_nothing(काष्ठा drm_mm *mm,
			  अचिन्हित पूर्णांक total_size,
			  काष्ठा evict_node *nodes)
अणु
	काष्ठा drm_mm_scan scan;
	LIST_HEAD(evict_list);
	काष्ठा evict_node *e;
	काष्ठा drm_mm_node *node;
	अचिन्हित पूर्णांक n;

	drm_mm_scan_init(&scan, mm, 1, 0, 0, 0);
	क्रम (n = 0; n < total_size; n++) अणु
		e = &nodes[n];
		list_add(&e->link, &evict_list);
		drm_mm_scan_add_block(&scan, &e->node);
	पूर्ण
	list_क्रम_each_entry(e, &evict_list, link)
		drm_mm_scan_हटाओ_block(&scan, &e->node);

	क्रम (n = 0; n < total_size; n++) अणु
		e = &nodes[n];

		अगर (!drm_mm_node_allocated(&e->node)) अणु
			pr_err("node[%d] no longer allocated!\n", n);
			वापस false;
		पूर्ण

		e->link.next = शून्य;
	पूर्ण

	drm_mm_क्रम_each_node(node, mm) अणु
		e = container_of(node, typeof(*e), node);
		e->link.next = &e->link;
	पूर्ण

	क्रम (n = 0; n < total_size; n++) अणु
		e = &nodes[n];

		अगर (!e->link.next) अणु
			pr_err("node[%d] no longer connected!\n", n);
			वापस false;
		पूर्ण
	पूर्ण

	वापस निश्चित_continuous(mm, nodes[0].node.size);
पूर्ण

अटल bool evict_everything(काष्ठा drm_mm *mm,
			     अचिन्हित पूर्णांक total_size,
			     काष्ठा evict_node *nodes)
अणु
	काष्ठा drm_mm_scan scan;
	LIST_HEAD(evict_list);
	काष्ठा evict_node *e;
	अचिन्हित पूर्णांक n;
	पूर्णांक err;

	drm_mm_scan_init(&scan, mm, total_size, 0, 0, 0);
	क्रम (n = 0; n < total_size; n++) अणु
		e = &nodes[n];
		list_add(&e->link, &evict_list);
		अगर (drm_mm_scan_add_block(&scan, &e->node))
			अवरोध;
	पूर्ण

	err = 0;
	list_क्रम_each_entry(e, &evict_list, link) अणु
		अगर (!drm_mm_scan_हटाओ_block(&scan, &e->node)) अणु
			अगर (!err) अणु
				pr_err("Node %lld not marked for eviction!\n",
				       e->node.start);
				err = -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (err)
		वापस false;

	list_क्रम_each_entry(e, &evict_list, link)
		drm_mm_हटाओ_node(&e->node);

	अगर (!निश्चित_one_hole(mm, 0, total_size))
		वापस false;

	list_क्रम_each_entry(e, &evict_list, link) अणु
		err = drm_mm_reserve_node(mm, &e->node);
		अगर (err) अणु
			pr_err("Failed to reinsert node after eviction: start=%llx\n",
			       e->node.start);
			वापस false;
		पूर्ण
	पूर्ण

	वापस निश्चित_continuous(mm, nodes[0].node.size);
पूर्ण

अटल पूर्णांक evict_something(काष्ठा drm_mm *mm,
			   u64 range_start, u64 range_end,
			   काष्ठा evict_node *nodes,
			   अचिन्हित पूर्णांक *order,
			   अचिन्हित पूर्णांक count,
			   अचिन्हित पूर्णांक size,
			   अचिन्हित पूर्णांक alignment,
			   स्थिर काष्ठा insert_mode *mode)
अणु
	काष्ठा drm_mm_scan scan;
	LIST_HEAD(evict_list);
	काष्ठा evict_node *e;
	काष्ठा drm_mm_node पंचांगp;
	पूर्णांक err;

	drm_mm_scan_init_with_range(&scan, mm,
				    size, alignment, 0,
				    range_start, range_end,
				    mode->mode);
	अगर (!evict_nodes(&scan,
			 nodes, order, count, false,
			 &evict_list))
		वापस -EINVAL;

	स_रखो(&पंचांगp, 0, माप(पंचांगp));
	err = drm_mm_insert_node_generic(mm, &पंचांगp, size, alignment, 0,
					 DRM_MM_INSERT_EVICT);
	अगर (err) अणु
		pr_err("Failed to insert into eviction hole: size=%d, align=%d\n",
		       size, alignment);
		show_scan(&scan);
		show_holes(mm, 3);
		वापस err;
	पूर्ण

	अगर (पंचांगp.start < range_start || पंचांगp.start + पंचांगp.size > range_end) अणु
		pr_err("Inserted [address=%llu + %llu] did not fit into the request range [%llu, %llu]\n",
		       पंचांगp.start, पंचांगp.size, range_start, range_end);
		err = -EINVAL;
	पूर्ण

	अगर (!निश्चित_node(&पंचांगp, mm, size, alignment, 0) ||
	    drm_mm_hole_follows(&पंचांगp)) अणु
		pr_err("Inserted did not fill the eviction hole: size=%lld [%d], align=%d [rem=%lld], start=%llx, hole-follows?=%d\n",
		       पंचांगp.size, size,
		       alignment, misalignment(&पंचांगp, alignment),
		       पंचांगp.start, drm_mm_hole_follows(&पंचांगp));
		err = -EINVAL;
	पूर्ण

	drm_mm_हटाओ_node(&पंचांगp);
	अगर (err)
		वापस err;

	list_क्रम_each_entry(e, &evict_list, link) अणु
		err = drm_mm_reserve_node(mm, &e->node);
		अगर (err) अणु
			pr_err("Failed to reinsert node after eviction: start=%llx\n",
			       e->node.start);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (!निश्चित_continuous(mm, nodes[0].node.size)) अणु
		pr_err("range is no longer continuous\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igt_evict(व्योम *ignored)
अणु
	DRM_RND_STATE(prng, अक्रमom_seed);
	स्थिर अचिन्हित पूर्णांक size = 8192;
	स्थिर काष्ठा insert_mode *mode;
	काष्ठा drm_mm mm;
	काष्ठा evict_node *nodes;
	काष्ठा drm_mm_node *node, *next;
	अचिन्हित पूर्णांक *order, n;
	पूर्णांक ret, err;

	/* Here we populate a full drm_mm and then try and insert a new node
	 * by evicting other nodes in a अक्रमom order. The drm_mm_scan should
	 * pick the first matching hole it finds from the अक्रमom list. We
	 * repeat that क्रम dअगरferent allocation strategies, alignments and
	 * sizes to try and stress the hole finder.
	 */

	ret = -ENOMEM;
	nodes = vzalloc(array_size(size, माप(*nodes)));
	अगर (!nodes)
		जाओ err;

	order = drm_अक्रमom_order(size, &prng);
	अगर (!order)
		जाओ err_nodes;

	ret = -EINVAL;
	drm_mm_init(&mm, 0, size);
	क्रम (n = 0; n < size; n++) अणु
		err = drm_mm_insert_node(&mm, &nodes[n].node, 1);
		अगर (err) अणु
			pr_err("insert failed, step %d\n", n);
			ret = err;
			जाओ out;
		पूर्ण
	पूर्ण

	/* First check that using the scanner करोesn't अवरोध the mm */
	अगर (!evict_nothing(&mm, size, nodes)) अणु
		pr_err("evict_nothing() failed\n");
		जाओ out;
	पूर्ण
	अगर (!evict_everything(&mm, size, nodes)) अणु
		pr_err("evict_everything() failed\n");
		जाओ out;
	पूर्ण

	क्रम (mode = evict_modes; mode->name; mode++) अणु
		क्रम (n = 1; n <= size; n <<= 1) अणु
			drm_अक्रमom_reorder(order, size, &prng);
			err = evict_something(&mm, 0, U64_MAX,
					      nodes, order, size,
					      n, 1,
					      mode);
			अगर (err) अणु
				pr_err("%s evict_something(size=%u) failed\n",
				       mode->name, n);
				ret = err;
				जाओ out;
			पूर्ण
		पूर्ण

		क्रम (n = 1; n < size; n <<= 1) अणु
			drm_अक्रमom_reorder(order, size, &prng);
			err = evict_something(&mm, 0, U64_MAX,
					      nodes, order, size,
					      size/2, n,
					      mode);
			अगर (err) अणु
				pr_err("%s evict_something(size=%u, alignment=%u) failed\n",
				       mode->name, size/2, n);
				ret = err;
				जाओ out;
			पूर्ण
		पूर्ण

		क्रम_each_prime_number_from(n, 1, min(size, max_prime)) अणु
			अचिन्हित पूर्णांक nsize = (size - n + 1) / 2;

			DRM_MM_BUG_ON(!nsize);

			drm_अक्रमom_reorder(order, size, &prng);
			err = evict_something(&mm, 0, U64_MAX,
					      nodes, order, size,
					      nsize, n,
					      mode);
			अगर (err) अणु
				pr_err("%s evict_something(size=%u, alignment=%u) failed\n",
				       mode->name, nsize, n);
				ret = err;
				जाओ out;
			पूर्ण
		पूर्ण

		cond_resched();
	पूर्ण

	ret = 0;
out:
	drm_mm_क्रम_each_node_safe(node, next, &mm)
		drm_mm_हटाओ_node(node);
	drm_mm_takeकरोwn(&mm);
	kमुक्त(order);
err_nodes:
	vमुक्त(nodes);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक igt_evict_range(व्योम *ignored)
अणु
	DRM_RND_STATE(prng, अक्रमom_seed);
	स्थिर अचिन्हित पूर्णांक size = 8192;
	स्थिर अचिन्हित पूर्णांक range_size = size / 2;
	स्थिर अचिन्हित पूर्णांक range_start = size / 4;
	स्थिर अचिन्हित पूर्णांक range_end = range_start + range_size;
	स्थिर काष्ठा insert_mode *mode;
	काष्ठा drm_mm mm;
	काष्ठा evict_node *nodes;
	काष्ठा drm_mm_node *node, *next;
	अचिन्हित पूर्णांक *order, n;
	पूर्णांक ret, err;

	/* Like igt_evict() but now we are limiting the search to a
	 * small portion of the full drm_mm.
	 */

	ret = -ENOMEM;
	nodes = vzalloc(array_size(size, माप(*nodes)));
	अगर (!nodes)
		जाओ err;

	order = drm_अक्रमom_order(size, &prng);
	अगर (!order)
		जाओ err_nodes;

	ret = -EINVAL;
	drm_mm_init(&mm, 0, size);
	क्रम (n = 0; n < size; n++) अणु
		err = drm_mm_insert_node(&mm, &nodes[n].node, 1);
		अगर (err) अणु
			pr_err("insert failed, step %d\n", n);
			ret = err;
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (mode = evict_modes; mode->name; mode++) अणु
		क्रम (n = 1; n <= range_size; n <<= 1) अणु
			drm_अक्रमom_reorder(order, size, &prng);
			err = evict_something(&mm, range_start, range_end,
					      nodes, order, size,
					      n, 1,
					      mode);
			अगर (err) अणु
				pr_err("%s evict_something(size=%u) failed with range [%u, %u]\n",
				       mode->name, n, range_start, range_end);
				जाओ out;
			पूर्ण
		पूर्ण

		क्रम (n = 1; n <= range_size; n <<= 1) अणु
			drm_अक्रमom_reorder(order, size, &prng);
			err = evict_something(&mm, range_start, range_end,
					      nodes, order, size,
					      range_size/2, n,
					      mode);
			अगर (err) अणु
				pr_err("%s evict_something(size=%u, alignment=%u) failed with range [%u, %u]\n",
				       mode->name, range_size/2, n, range_start, range_end);
				जाओ out;
			पूर्ण
		पूर्ण

		क्रम_each_prime_number_from(n, 1, min(range_size, max_prime)) अणु
			अचिन्हित पूर्णांक nsize = (range_size - n + 1) / 2;

			DRM_MM_BUG_ON(!nsize);

			drm_अक्रमom_reorder(order, size, &prng);
			err = evict_something(&mm, range_start, range_end,
					      nodes, order, size,
					      nsize, n,
					      mode);
			अगर (err) अणु
				pr_err("%s evict_something(size=%u, alignment=%u) failed with range [%u, %u]\n",
				       mode->name, nsize, n, range_start, range_end);
				जाओ out;
			पूर्ण
		पूर्ण

		cond_resched();
	पूर्ण

	ret = 0;
out:
	drm_mm_क्रम_each_node_safe(node, next, &mm)
		drm_mm_हटाओ_node(node);
	drm_mm_takeकरोwn(&mm);
	kमुक्त(order);
err_nodes:
	vमुक्त(nodes);
err:
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक node_index(स्थिर काष्ठा drm_mm_node *node)
अणु
	वापस भाग64_u64(node->start, node->size);
पूर्ण

अटल पूर्णांक igt_topकरोwn(व्योम *ignored)
अणु
	स्थिर काष्ठा insert_mode *topकरोwn = &insert_modes[TOPDOWN];
	DRM_RND_STATE(prng, अक्रमom_seed);
	स्थिर अचिन्हित पूर्णांक count = 8192;
	अचिन्हित पूर्णांक size;
	अचिन्हित दीर्घ *biपंचांगap;
	काष्ठा drm_mm mm;
	काष्ठा drm_mm_node *nodes, *node, *next;
	अचिन्हित पूर्णांक *order, n, m, o = 0;
	पूर्णांक ret;

	/* When allocating top-करोwn, we expect to be वापसed a node
	 * from a suitable hole at the top of the drm_mm. We check that
	 * the वापसed node करोes match the highest available slot.
	 */

	ret = -ENOMEM;
	nodes = vzalloc(array_size(count, माप(*nodes)));
	अगर (!nodes)
		जाओ err;

	biपंचांगap = biपंचांगap_zalloc(count, GFP_KERNEL);
	अगर (!biपंचांगap)
		जाओ err_nodes;

	order = drm_अक्रमom_order(count, &prng);
	अगर (!order)
		जाओ err_biपंचांगap;

	ret = -EINVAL;
	क्रम (size = 1; size <= 64; size <<= 1) अणु
		drm_mm_init(&mm, 0, size*count);
		क्रम (n = 0; n < count; n++) अणु
			अगर (!expect_insert(&mm, &nodes[n],
					   size, 0, n,
					   topकरोwn)) अणु
				pr_err("insert failed, size %u step %d\n", size, n);
				जाओ out;
			पूर्ण

			अगर (drm_mm_hole_follows(&nodes[n])) अणु
				pr_err("hole after topdown insert %d, start=%llx\n, size=%u",
				       n, nodes[n].start, size);
				जाओ out;
			पूर्ण

			अगर (!निश्चित_one_hole(&mm, 0, size*(count - n - 1)))
				जाओ out;
		पूर्ण

		अगर (!निश्चित_continuous(&mm, size))
			जाओ out;

		drm_अक्रमom_reorder(order, count, &prng);
		क्रम_each_prime_number_from(n, 1, min(count, max_prime)) अणु
			क्रम (m = 0; m < n; m++) अणु
				node = &nodes[order[(o + m) % count]];
				drm_mm_हटाओ_node(node);
				__set_bit(node_index(node), biपंचांगap);
			पूर्ण

			क्रम (m = 0; m < n; m++) अणु
				अचिन्हित पूर्णांक last;

				node = &nodes[order[(o + m) % count]];
				अगर (!expect_insert(&mm, node,
						   size, 0, 0,
						   topकरोwn)) अणु
					pr_err("insert failed, step %d/%d\n", m, n);
					जाओ out;
				पूर्ण

				अगर (drm_mm_hole_follows(node)) अणु
					pr_err("hole after topdown insert %d/%d, start=%llx\n",
					       m, n, node->start);
					जाओ out;
				पूर्ण

				last = find_last_bit(biपंचांगap, count);
				अगर (node_index(node) != last) अणु
					pr_err("node %d/%d, size %d, not inserted into upmost hole, expected %d, found %d\n",
					       m, n, size, last, node_index(node));
					जाओ out;
				पूर्ण

				__clear_bit(last, biपंचांगap);
			पूर्ण

			DRM_MM_BUG_ON(find_first_bit(biपंचांगap, count) != count);

			o += n;
		पूर्ण

		drm_mm_क्रम_each_node_safe(node, next, &mm)
			drm_mm_हटाओ_node(node);
		DRM_MM_BUG_ON(!drm_mm_clean(&mm));
		cond_resched();
	पूर्ण

	ret = 0;
out:
	drm_mm_क्रम_each_node_safe(node, next, &mm)
		drm_mm_हटाओ_node(node);
	drm_mm_takeकरोwn(&mm);
	kमुक्त(order);
err_biपंचांगap:
	biपंचांगap_मुक्त(biपंचांगap);
err_nodes:
	vमुक्त(nodes);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक igt_bottomup(व्योम *ignored)
अणु
	स्थिर काष्ठा insert_mode *bottomup = &insert_modes[BOTTOMUP];
	DRM_RND_STATE(prng, अक्रमom_seed);
	स्थिर अचिन्हित पूर्णांक count = 8192;
	अचिन्हित पूर्णांक size;
	अचिन्हित दीर्घ *biपंचांगap;
	काष्ठा drm_mm mm;
	काष्ठा drm_mm_node *nodes, *node, *next;
	अचिन्हित पूर्णांक *order, n, m, o = 0;
	पूर्णांक ret;

	/* Like igt_topकरोwn, but instead of searching क्रम the last hole,
	 * we search क्रम the first.
	 */

	ret = -ENOMEM;
	nodes = vzalloc(array_size(count, माप(*nodes)));
	अगर (!nodes)
		जाओ err;

	biपंचांगap = biपंचांगap_zalloc(count, GFP_KERNEL);
	अगर (!biपंचांगap)
		जाओ err_nodes;

	order = drm_अक्रमom_order(count, &prng);
	अगर (!order)
		जाओ err_biपंचांगap;

	ret = -EINVAL;
	क्रम (size = 1; size <= 64; size <<= 1) अणु
		drm_mm_init(&mm, 0, size*count);
		क्रम (n = 0; n < count; n++) अणु
			अगर (!expect_insert(&mm, &nodes[n],
					   size, 0, n,
					   bottomup)) अणु
				pr_err("bottomup insert failed, size %u step %d\n", size, n);
				जाओ out;
			पूर्ण

			अगर (!निश्चित_one_hole(&mm, size*(n + 1), size*count))
				जाओ out;
		पूर्ण

		अगर (!निश्चित_continuous(&mm, size))
			जाओ out;

		drm_अक्रमom_reorder(order, count, &prng);
		क्रम_each_prime_number_from(n, 1, min(count, max_prime)) अणु
			क्रम (m = 0; m < n; m++) अणु
				node = &nodes[order[(o + m) % count]];
				drm_mm_हटाओ_node(node);
				__set_bit(node_index(node), biपंचांगap);
			पूर्ण

			क्रम (m = 0; m < n; m++) अणु
				अचिन्हित पूर्णांक first;

				node = &nodes[order[(o + m) % count]];
				अगर (!expect_insert(&mm, node,
						   size, 0, 0,
						   bottomup)) अणु
					pr_err("insert failed, step %d/%d\n", m, n);
					जाओ out;
				पूर्ण

				first = find_first_bit(biपंचांगap, count);
				अगर (node_index(node) != first) अणु
					pr_err("node %d/%d not inserted into bottom hole, expected %d, found %d\n",
					       m, n, first, node_index(node));
					जाओ out;
				पूर्ण
				__clear_bit(first, biपंचांगap);
			पूर्ण

			DRM_MM_BUG_ON(find_first_bit(biपंचांगap, count) != count);

			o += n;
		पूर्ण

		drm_mm_क्रम_each_node_safe(node, next, &mm)
			drm_mm_हटाओ_node(node);
		DRM_MM_BUG_ON(!drm_mm_clean(&mm));
		cond_resched();
	पूर्ण

	ret = 0;
out:
	drm_mm_क्रम_each_node_safe(node, next, &mm)
		drm_mm_हटाओ_node(node);
	drm_mm_takeकरोwn(&mm);
	kमुक्त(order);
err_biपंचांगap:
	biपंचांगap_मुक्त(biपंचांगap);
err_nodes:
	vमुक्त(nodes);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक __igt_once(अचिन्हित पूर्णांक mode)
अणु
	काष्ठा drm_mm mm;
	काष्ठा drm_mm_node rsvd_lo, rsvd_hi, node;
	पूर्णांक err;

	drm_mm_init(&mm, 0, 7);

	स_रखो(&rsvd_lo, 0, माप(rsvd_lo));
	rsvd_lo.start = 1;
	rsvd_lo.size = 1;
	err = drm_mm_reserve_node(&mm, &rsvd_lo);
	अगर (err) अणु
		pr_err("Could not reserve low node\n");
		जाओ err;
	पूर्ण

	स_रखो(&rsvd_hi, 0, माप(rsvd_hi));
	rsvd_hi.start = 5;
	rsvd_hi.size = 1;
	err = drm_mm_reserve_node(&mm, &rsvd_hi);
	अगर (err) अणु
		pr_err("Could not reserve low node\n");
		जाओ err_lo;
	पूर्ण

	अगर (!drm_mm_hole_follows(&rsvd_lo) || !drm_mm_hole_follows(&rsvd_hi)) अणु
		pr_err("Expected a hole after lo and high nodes!\n");
		err = -EINVAL;
		जाओ err_hi;
	पूर्ण

	स_रखो(&node, 0, माप(node));
	err = drm_mm_insert_node_generic(&mm, &node, 2, 0, 0, mode);
	अगर (err) अणु
		pr_err("Could not insert the node into the available hole!\n");
		err = -EINVAL;
		जाओ err_hi;
	पूर्ण

	drm_mm_हटाओ_node(&node);
err_hi:
	drm_mm_हटाओ_node(&rsvd_hi);
err_lo:
	drm_mm_हटाओ_node(&rsvd_lo);
err:
	drm_mm_takeकरोwn(&mm);
	वापस err;
पूर्ण

अटल पूर्णांक igt_lowest(व्योम *ignored)
अणु
	वापस __igt_once(DRM_MM_INSERT_LOW);
पूर्ण

अटल पूर्णांक igt_highest(व्योम *ignored)
अणु
	वापस __igt_once(DRM_MM_INSERT_HIGH);
पूर्ण

अटल व्योम separate_adjacent_colors(स्थिर काष्ठा drm_mm_node *node,
				     अचिन्हित दीर्घ color,
				     u64 *start,
				     u64 *end)
अणु
	अगर (drm_mm_node_allocated(node) && node->color != color)
		++*start;

	node = list_next_entry(node, node_list);
	अगर (drm_mm_node_allocated(node) && node->color != color)
		--*end;
पूर्ण

अटल bool colors_abutt(स्थिर काष्ठा drm_mm_node *node)
अणु
	अगर (!drm_mm_hole_follows(node) &&
	    drm_mm_node_allocated(list_next_entry(node, node_list))) अणु
		pr_err("colors abutt; %ld [%llx + %llx] is next to %ld [%llx + %llx]!\n",
		       node->color, node->start, node->size,
		       list_next_entry(node, node_list)->color,
		       list_next_entry(node, node_list)->start,
		       list_next_entry(node, node_list)->size);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक igt_color(व्योम *ignored)
अणु
	स्थिर अचिन्हित पूर्णांक count = min(4096u, max_iterations);
	स्थिर काष्ठा insert_mode *mode;
	काष्ठा drm_mm mm;
	काष्ठा drm_mm_node *node, *nn;
	अचिन्हित पूर्णांक n;
	पूर्णांक ret = -EINVAL, err;

	/* Color adjusपंचांगent complicates everything. First we just check
	 * that when we insert a node we apply any color_adjusपंचांगent callback.
	 * The callback we use should ensure that there is a gap between
	 * any two nodes, and so after each insertion we check that those
	 * holes are inserted and that they are preserved.
	 */

	drm_mm_init(&mm, 0, U64_MAX);

	क्रम (n = 1; n <= count; n++) अणु
		node = kzalloc(माप(*node), GFP_KERNEL);
		अगर (!node) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		अगर (!expect_insert(&mm, node,
				   n, 0, n,
				   &insert_modes[0])) अणु
			pr_err("insert failed, step %d\n", n);
			kमुक्त(node);
			जाओ out;
		पूर्ण
	पूर्ण

	drm_mm_क्रम_each_node_safe(node, nn, &mm) अणु
		अगर (node->color != node->size) अणु
			pr_err("invalid color stored: expected %lld, found %ld\n",
			       node->size, node->color);

			जाओ out;
		पूर्ण

		drm_mm_हटाओ_node(node);
		kमुक्त(node);
	पूर्ण

	/* Now, let's start experimenting with applying a color callback */
	mm.color_adjust = separate_adjacent_colors;
	क्रम (mode = insert_modes; mode->name; mode++) अणु
		u64 last;

		node = kzalloc(माप(*node), GFP_KERNEL);
		अगर (!node) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		node->size = 1 + 2*count;
		node->color = node->size;

		err = drm_mm_reserve_node(&mm, node);
		अगर (err) अणु
			pr_err("initial reserve failed!\n");
			ret = err;
			जाओ out;
		पूर्ण

		last = node->start + node->size;

		क्रम (n = 1; n <= count; n++) अणु
			पूर्णांक rem;

			node = kzalloc(माप(*node), GFP_KERNEL);
			अगर (!node) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			node->start = last;
			node->size = n + count;
			node->color = node->size;

			err = drm_mm_reserve_node(&mm, node);
			अगर (err != -ENOSPC) अणु
				pr_err("reserve %d did not report color overlap! err=%d\n",
				       n, err);
				जाओ out;
			पूर्ण

			node->start += n + 1;
			rem = misalignment(node, n + count);
			node->start += n + count - rem;

			err = drm_mm_reserve_node(&mm, node);
			अगर (err) अणु
				pr_err("reserve %d failed, err=%d\n", n, err);
				ret = err;
				जाओ out;
			पूर्ण

			last = node->start + node->size;
		पूर्ण

		क्रम (n = 1; n <= count; n++) अणु
			node = kzalloc(माप(*node), GFP_KERNEL);
			अगर (!node) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			अगर (!expect_insert(&mm, node,
					   n, n, n,
					   mode)) अणु
				pr_err("%s insert failed, step %d\n",
				       mode->name, n);
				kमुक्त(node);
				जाओ out;
			पूर्ण
		पूर्ण

		drm_mm_क्रम_each_node_safe(node, nn, &mm) अणु
			u64 rem;

			अगर (node->color != node->size) अणु
				pr_err("%s invalid color stored: expected %lld, found %ld\n",
				       mode->name, node->size, node->color);

				जाओ out;
			पूर्ण

			अगर (colors_abutt(node))
				जाओ out;

			भाग64_u64_rem(node->start, node->size, &rem);
			अगर (rem) अणु
				pr_err("%s colored node misaligned, start=%llx expected alignment=%lld [rem=%lld]\n",
				       mode->name, node->start, node->size, rem);
				जाओ out;
			पूर्ण

			drm_mm_हटाओ_node(node);
			kमुक्त(node);
		पूर्ण

		cond_resched();
	पूर्ण

	ret = 0;
out:
	drm_mm_क्रम_each_node_safe(node, nn, &mm) अणु
		drm_mm_हटाओ_node(node);
		kमुक्त(node);
	पूर्ण
	drm_mm_takeकरोwn(&mm);
	वापस ret;
पूर्ण

अटल पूर्णांक evict_color(काष्ठा drm_mm *mm,
		       u64 range_start, u64 range_end,
		       काष्ठा evict_node *nodes,
		       अचिन्हित पूर्णांक *order,
		       अचिन्हित पूर्णांक count,
		       अचिन्हित पूर्णांक size,
		       अचिन्हित पूर्णांक alignment,
		       अचिन्हित दीर्घ color,
		       स्थिर काष्ठा insert_mode *mode)
अणु
	काष्ठा drm_mm_scan scan;
	LIST_HEAD(evict_list);
	काष्ठा evict_node *e;
	काष्ठा drm_mm_node पंचांगp;
	पूर्णांक err;

	drm_mm_scan_init_with_range(&scan, mm,
				    size, alignment, color,
				    range_start, range_end,
				    mode->mode);
	अगर (!evict_nodes(&scan,
			 nodes, order, count, true,
			 &evict_list))
		वापस -EINVAL;

	स_रखो(&पंचांगp, 0, माप(पंचांगp));
	err = drm_mm_insert_node_generic(mm, &पंचांगp, size, alignment, color,
					 DRM_MM_INSERT_EVICT);
	अगर (err) अणु
		pr_err("Failed to insert into eviction hole: size=%d, align=%d, color=%lu, err=%d\n",
		       size, alignment, color, err);
		show_scan(&scan);
		show_holes(mm, 3);
		वापस err;
	पूर्ण

	अगर (पंचांगp.start < range_start || पंचांगp.start + पंचांगp.size > range_end) अणु
		pr_err("Inserted [address=%llu + %llu] did not fit into the request range [%llu, %llu]\n",
		       पंचांगp.start, पंचांगp.size, range_start, range_end);
		err = -EINVAL;
	पूर्ण

	अगर (colors_abutt(&पंचांगp))
		err = -EINVAL;

	अगर (!निश्चित_node(&पंचांगp, mm, size, alignment, color)) अणु
		pr_err("Inserted did not fit the eviction hole: size=%lld [%d], align=%d [rem=%lld], start=%llx\n",
		       पंचांगp.size, size,
		       alignment, misalignment(&पंचांगp, alignment), पंचांगp.start);
		err = -EINVAL;
	पूर्ण

	drm_mm_हटाओ_node(&पंचांगp);
	अगर (err)
		वापस err;

	list_क्रम_each_entry(e, &evict_list, link) अणु
		err = drm_mm_reserve_node(mm, &e->node);
		अगर (err) अणु
			pr_err("Failed to reinsert node after eviction: start=%llx\n",
			       e->node.start);
			वापस err;
		पूर्ण
	पूर्ण

	cond_resched();
	वापस 0;
पूर्ण

अटल पूर्णांक igt_color_evict(व्योम *ignored)
अणु
	DRM_RND_STATE(prng, अक्रमom_seed);
	स्थिर अचिन्हित पूर्णांक total_size = min(8192u, max_iterations);
	स्थिर काष्ठा insert_mode *mode;
	अचिन्हित दीर्घ color = 0;
	काष्ठा drm_mm mm;
	काष्ठा evict_node *nodes;
	काष्ठा drm_mm_node *node, *next;
	अचिन्हित पूर्णांक *order, n;
	पूर्णांक ret, err;

	/* Check that the drm_mm_scan also honours color adjusपंचांगent when
	 * choosing its victims to create a hole. Our color_adjust करोes not
	 * allow two nodes to be placed together without an पूर्णांकervening hole
	 * enlarging the set of victims that must be evicted.
	 */

	ret = -ENOMEM;
	nodes = vzalloc(array_size(total_size, माप(*nodes)));
	अगर (!nodes)
		जाओ err;

	order = drm_अक्रमom_order(total_size, &prng);
	अगर (!order)
		जाओ err_nodes;

	ret = -EINVAL;
	drm_mm_init(&mm, 0, 2*total_size - 1);
	mm.color_adjust = separate_adjacent_colors;
	क्रम (n = 0; n < total_size; n++) अणु
		अगर (!expect_insert(&mm, &nodes[n].node,
				   1, 0, color++,
				   &insert_modes[0])) अणु
			pr_err("insert failed, step %d\n", n);
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (mode = evict_modes; mode->name; mode++) अणु
		क्रम (n = 1; n <= total_size; n <<= 1) अणु
			drm_अक्रमom_reorder(order, total_size, &prng);
			err = evict_color(&mm, 0, U64_MAX,
					  nodes, order, total_size,
					  n, 1, color++,
					  mode);
			अगर (err) अणु
				pr_err("%s evict_color(size=%u) failed\n",
				       mode->name, n);
				जाओ out;
			पूर्ण
		पूर्ण

		क्रम (n = 1; n < total_size; n <<= 1) अणु
			drm_अक्रमom_reorder(order, total_size, &prng);
			err = evict_color(&mm, 0, U64_MAX,
					  nodes, order, total_size,
					  total_size/2, n, color++,
					  mode);
			अगर (err) अणु
				pr_err("%s evict_color(size=%u, alignment=%u) failed\n",
				       mode->name, total_size/2, n);
				जाओ out;
			पूर्ण
		पूर्ण

		क्रम_each_prime_number_from(n, 1, min(total_size, max_prime)) अणु
			अचिन्हित पूर्णांक nsize = (total_size - n + 1) / 2;

			DRM_MM_BUG_ON(!nsize);

			drm_अक्रमom_reorder(order, total_size, &prng);
			err = evict_color(&mm, 0, U64_MAX,
					  nodes, order, total_size,
					  nsize, n, color++,
					  mode);
			अगर (err) अणु
				pr_err("%s evict_color(size=%u, alignment=%u) failed\n",
				       mode->name, nsize, n);
				जाओ out;
			पूर्ण
		पूर्ण

		cond_resched();
	पूर्ण

	ret = 0;
out:
	अगर (ret)
		show_mm(&mm);
	drm_mm_क्रम_each_node_safe(node, next, &mm)
		drm_mm_हटाओ_node(node);
	drm_mm_takeकरोwn(&mm);
	kमुक्त(order);
err_nodes:
	vमुक्त(nodes);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक igt_color_evict_range(व्योम *ignored)
अणु
	DRM_RND_STATE(prng, अक्रमom_seed);
	स्थिर अचिन्हित पूर्णांक total_size = 8192;
	स्थिर अचिन्हित पूर्णांक range_size = total_size / 2;
	स्थिर अचिन्हित पूर्णांक range_start = total_size / 4;
	स्थिर अचिन्हित पूर्णांक range_end = range_start + range_size;
	स्थिर काष्ठा insert_mode *mode;
	अचिन्हित दीर्घ color = 0;
	काष्ठा drm_mm mm;
	काष्ठा evict_node *nodes;
	काष्ठा drm_mm_node *node, *next;
	अचिन्हित पूर्णांक *order, n;
	पूर्णांक ret, err;

	/* Like igt_color_evict(), but limited to small portion of the full
	 * drm_mm range.
	 */

	ret = -ENOMEM;
	nodes = vzalloc(array_size(total_size, माप(*nodes)));
	अगर (!nodes)
		जाओ err;

	order = drm_अक्रमom_order(total_size, &prng);
	अगर (!order)
		जाओ err_nodes;

	ret = -EINVAL;
	drm_mm_init(&mm, 0, 2*total_size - 1);
	mm.color_adjust = separate_adjacent_colors;
	क्रम (n = 0; n < total_size; n++) अणु
		अगर (!expect_insert(&mm, &nodes[n].node,
				   1, 0, color++,
				   &insert_modes[0])) अणु
			pr_err("insert failed, step %d\n", n);
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (mode = evict_modes; mode->name; mode++) अणु
		क्रम (n = 1; n <= range_size; n <<= 1) अणु
			drm_अक्रमom_reorder(order, range_size, &prng);
			err = evict_color(&mm, range_start, range_end,
					  nodes, order, total_size,
					  n, 1, color++,
					  mode);
			अगर (err) अणु
				pr_err("%s evict_color(size=%u) failed for range [%x, %x]\n",
				       mode->name, n, range_start, range_end);
				जाओ out;
			पूर्ण
		पूर्ण

		क्रम (n = 1; n < range_size; n <<= 1) अणु
			drm_अक्रमom_reorder(order, total_size, &prng);
			err = evict_color(&mm, range_start, range_end,
					  nodes, order, total_size,
					  range_size/2, n, color++,
					  mode);
			अगर (err) अणु
				pr_err("%s evict_color(size=%u, alignment=%u) failed for range [%x, %x]\n",
				       mode->name, total_size/2, n, range_start, range_end);
				जाओ out;
			पूर्ण
		पूर्ण

		क्रम_each_prime_number_from(n, 1, min(range_size, max_prime)) अणु
			अचिन्हित पूर्णांक nsize = (range_size - n + 1) / 2;

			DRM_MM_BUG_ON(!nsize);

			drm_अक्रमom_reorder(order, total_size, &prng);
			err = evict_color(&mm, range_start, range_end,
					  nodes, order, total_size,
					  nsize, n, color++,
					  mode);
			अगर (err) अणु
				pr_err("%s evict_color(size=%u, alignment=%u) failed for range [%x, %x]\n",
				       mode->name, nsize, n, range_start, range_end);
				जाओ out;
			पूर्ण
		पूर्ण

		cond_resched();
	पूर्ण

	ret = 0;
out:
	अगर (ret)
		show_mm(&mm);
	drm_mm_क्रम_each_node_safe(node, next, &mm)
		drm_mm_हटाओ_node(node);
	drm_mm_takeकरोwn(&mm);
	kमुक्त(order);
err_nodes:
	vमुक्त(nodes);
err:
	वापस ret;
पूर्ण

#समावेश "drm_selftest.c"

अटल पूर्णांक __init test_drm_mm_init(व्योम)
अणु
	पूर्णांक err;

	जबतक (!अक्रमom_seed)
		अक्रमom_seed = get_अक्रमom_पूर्णांक();

	pr_info("Testing DRM range manager (struct drm_mm), with random_seed=0x%x max_iterations=%u max_prime=%u\n",
		अक्रमom_seed, max_iterations, max_prime);
	err = run_selftests(selftests, ARRAY_SIZE(selftests), शून्य);

	वापस err > 0 ? 0 : err;
पूर्ण

अटल व्योम __निकास test_drm_mm_निकास(व्योम)
अणु
पूर्ण

module_init(test_drm_mm_init);
module_निकास(test_drm_mm_निकास);

module_param(अक्रमom_seed, uपूर्णांक, 0400);
module_param(max_iterations, uपूर्णांक, 0400);
module_param(max_prime, uपूर्णांक, 0400);

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL");
