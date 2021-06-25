<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित INTEL_RING_H
#घोषणा INTEL_RING_H

#समावेश "i915_gem.h" /* GEM_BUG_ON */
#समावेश "i915_request.h"
#समावेश "intel_ring_types.h"

काष्ठा पूर्णांकel_engine_cs;

काष्ठा पूर्णांकel_ring *
पूर्णांकel_engine_create_ring(काष्ठा पूर्णांकel_engine_cs *engine, पूर्णांक size);

u32 *पूर्णांकel_ring_begin(काष्ठा i915_request *rq, अचिन्हित पूर्णांक num_dwords);
पूर्णांक पूर्णांकel_ring_cacheline_align(काष्ठा i915_request *rq);

अचिन्हित पूर्णांक पूर्णांकel_ring_update_space(काष्ठा पूर्णांकel_ring *ring);

व्योम __पूर्णांकel_ring_pin(काष्ठा पूर्णांकel_ring *ring);
पूर्णांक पूर्णांकel_ring_pin(काष्ठा पूर्णांकel_ring *ring, काष्ठा i915_gem_ww_ctx *ww);
व्योम पूर्णांकel_ring_unpin(काष्ठा पूर्णांकel_ring *ring);
व्योम पूर्णांकel_ring_reset(काष्ठा पूर्णांकel_ring *ring, u32 tail);

व्योम पूर्णांकel_ring_मुक्त(काष्ठा kref *ref);

अटल अंतरभूत काष्ठा पूर्णांकel_ring *पूर्णांकel_ring_get(काष्ठा पूर्णांकel_ring *ring)
अणु
	kref_get(&ring->ref);
	वापस ring;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_ring_put(काष्ठा पूर्णांकel_ring *ring)
अणु
	kref_put(&ring->ref, पूर्णांकel_ring_मुक्त);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_ring_advance(काष्ठा i915_request *rq, u32 *cs)
अणु
	/* Dummy function.
	 *
	 * This serves as a placeholder in the code so that the पढ़ोer
	 * can compare against the preceding पूर्णांकel_ring_begin() and
	 * check that the number of dwords emitted matches the space
	 * reserved क्रम the command packet (i.e. the value passed to
	 * पूर्णांकel_ring_begin()).
	 */
	GEM_BUG_ON((rq->ring->vaddr + rq->ring->emit) != cs);
पूर्ण

अटल अंतरभूत u32 पूर्णांकel_ring_wrap(स्थिर काष्ठा पूर्णांकel_ring *ring, u32 pos)
अणु
	वापस pos & (ring->size - 1);
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_ring_direction(स्थिर काष्ठा पूर्णांकel_ring *ring,
				       u32 next, u32 prev)
अणु
	typecheck(typeof(ring->size), next);
	typecheck(typeof(ring->size), prev);
	वापस (next - prev) << ring->wrap;
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_ring_offset_valid(स्थिर काष्ठा पूर्णांकel_ring *ring,
			अचिन्हित पूर्णांक pos)
अणु
	अगर (pos & -ring->size) /* must be strictly within the ring */
		वापस false;

	अगर (!IS_ALIGNED(pos, 8)) /* must be qword aligned */
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत u32 पूर्णांकel_ring_offset(स्थिर काष्ठा i915_request *rq, व्योम *addr)
अणु
	/* Don't ग_लिखो ring->size (equivalent to 0) as that hangs some GPUs. */
	u32 offset = addr - rq->ring->vaddr;

	GEM_BUG_ON(offset > rq->ring->size);
	वापस पूर्णांकel_ring_wrap(rq->ring, offset);
पूर्ण

अटल अंतरभूत व्योम
निश्चित_ring_tail_valid(स्थिर काष्ठा पूर्णांकel_ring *ring, अचिन्हित पूर्णांक tail)
अणु
	अचिन्हित पूर्णांक head = READ_ONCE(ring->head);

	GEM_BUG_ON(!पूर्णांकel_ring_offset_valid(ring, tail));

	/*
	 * "Ring Buffer Use"
	 *	Gen2 BSpec "1. Programming Environment" / 1.4.4.6
	 *	Gen3 BSpec "1c Memory Interface Functions" / 2.3.4.5
	 *	Gen4+ BSpec "1c Memory Interface and Command Stream" / 5.3.4.5
	 * "If the Ring Buffer Head Poपूर्णांकer and the Tail Poपूर्णांकer are on the
	 * same cacheline, the Head Poपूर्णांकer must not be greater than the Tail
	 * Poपूर्णांकer."
	 *
	 * We use ring->head as the last known location of the actual RING_HEAD,
	 * it may have advanced but in the worst हाल it is equally the same
	 * as ring->head and so we should never program RING_TAIL to advance
	 * पूर्णांकo the same cacheline as ring->head.
	 */
#घोषणा cacheline(a) round_करोwn(a, CACHELINE_BYTES)
	GEM_BUG_ON(cacheline(tail) == cacheline(head) && tail < head);
#अघोषित cacheline
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
पूर्णांकel_ring_set_tail(काष्ठा पूर्णांकel_ring *ring, अचिन्हित पूर्णांक tail)
अणु
	/* Whilst ग_लिखोs to the tail are strictly order, there is no
	 * serialisation between पढ़ोers and the ग_लिखोrs. The tail may be
	 * पढ़ो by i915_request_retire() just as it is being updated
	 * by execlists, as although the bपढ़ोcrumb is complete, the context
	 * चयन hasn't been seen.
	 */
	निश्चित_ring_tail_valid(ring, tail);
	ring->tail = tail;
	वापस tail;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
__पूर्णांकel_ring_space(अचिन्हित पूर्णांक head, अचिन्हित पूर्णांक tail, अचिन्हित पूर्णांक size)
अणु
	/*
	 * "If the Ring Buffer Head Poपूर्णांकer and the Tail Poपूर्णांकer are on the
	 * same cacheline, the Head Poपूर्णांकer must not be greater than the Tail
	 * Poपूर्णांकer."
	 */
	GEM_BUG_ON(!is_घातer_of_2(size));
	वापस (head - tail - CACHELINE_BYTES) & (size - 1);
पूर्ण

#पूर्ण_अगर /* INTEL_RING_H */
