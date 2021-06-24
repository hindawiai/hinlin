<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright तऊ 2020 Intel Corporation
 */

अटल काष्ठा पूर्णांकel_ring *mock_ring(अचिन्हित दीर्घ sz)
अणु
	काष्ठा पूर्णांकel_ring *ring;

	ring = kzalloc(माप(*ring) + sz, GFP_KERNEL);
	अगर (!ring)
		वापस शून्य;

	kref_init(&ring->ref);
	ring->size = sz;
	ring->wrap = BITS_PER_TYPE(ring->size) - ilog2(sz);
	ring->effective_size = sz;
	ring->vaddr = (व्योम *)(ring + 1);
	atomic_set(&ring->pin_count, 1);

	पूर्णांकel_ring_update_space(ring);

	वापस ring;
पूर्ण

अटल व्योम mock_ring_मुक्त(काष्ठा पूर्णांकel_ring *ring)
अणु
	kमुक्त(ring);
पूर्ण

अटल पूर्णांक check_ring_direction(काष्ठा पूर्णांकel_ring *ring,
				u32 next, u32 prev,
				पूर्णांक expected)
अणु
	पूर्णांक result;

	result = पूर्णांकel_ring_direction(ring, next, prev);
	अगर (result < 0)
		result = -1;
	अन्यथा अगर (result > 0)
		result = 1;

	अगर (result != expected) अणु
		pr_err("intel_ring_direction(%u, %u):%d != %d\n",
		       next, prev, result, expected);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_ring_step(काष्ठा पूर्णांकel_ring *ring, u32 x, u32 step)
अणु
	u32 prev = x, next = पूर्णांकel_ring_wrap(ring, x + step);
	पूर्णांक err = 0;

	err |= check_ring_direction(ring, next, next,  0);
	err |= check_ring_direction(ring, prev, prev,  0);
	err |= check_ring_direction(ring, next, prev,  1);
	err |= check_ring_direction(ring, prev, next, -1);

	वापस err;
पूर्ण

अटल पूर्णांक check_ring_offset(काष्ठा पूर्णांकel_ring *ring, u32 x, u32 step)
अणु
	पूर्णांक err = 0;

	err |= check_ring_step(ring, x, step);
	err |= check_ring_step(ring, पूर्णांकel_ring_wrap(ring, x + 1), step);
	err |= check_ring_step(ring, पूर्णांकel_ring_wrap(ring, x - 1), step);

	वापस err;
पूर्ण

अटल पूर्णांक igt_ring_direction(व्योम *dummy)
अणु
	काष्ठा पूर्णांकel_ring *ring;
	अचिन्हित पूर्णांक half = 2048;
	पूर्णांक step, err = 0;

	ring = mock_ring(2 * half);
	अगर (!ring)
		वापस -ENOMEM;

	GEM_BUG_ON(ring->size != 2 * half);

	/* Precision of wrap detection is limited to ring->size / 2 */
	क्रम (step = 1; step < half; step <<= 1) अणु
		err |= check_ring_offset(ring, 0, step);
		err |= check_ring_offset(ring, half, step);
	पूर्ण
	err |= check_ring_step(ring, 0, half - 64);

	/* And check unwrapped handling क्रम good measure */
	err |= check_ring_offset(ring, 0, 2 * half + 64);
	err |= check_ring_offset(ring, 3 * half, 1);

	mock_ring_मुक्त(ring);
	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_ring_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_ring_direction),
	पूर्ण;

	वापस i915_subtests(tests, शून्य);
पूर्ण
