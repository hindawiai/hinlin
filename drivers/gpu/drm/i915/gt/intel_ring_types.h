<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित INTEL_RING_TYPES_H
#घोषणा INTEL_RING_TYPES_H

#समावेश <linux/atomic.h>
#समावेश <linux/kref.h>
#समावेश <linux/types.h>

/*
 * Early gen2 devices have a cacheline of just 32 bytes, using 64 is overसमाप्त,
 * but keeps the logic simple. Indeed, the whole purpose of this macro is just
 * to give some inclination as to some of the magic values used in the various
 * workarounds!
 */
#घोषणा CACHELINE_BYTES 64
#घोषणा CACHELINE_DWORDS (CACHELINE_BYTES / माप(u32))

काष्ठा i915_vma;

काष्ठा पूर्णांकel_ring अणु
	काष्ठा kref ref;
	काष्ठा i915_vma *vma;
	व्योम *vaddr;

	/*
	 * As we have two types of rings, one global to the engine used
	 * by ringbuffer submission and those that are exclusive to a
	 * context used by execlists, we have to play safe and allow
	 * atomic updates to the pin_count. However, the actual pinning
	 * of the context is either करोne during initialisation क्रम
	 * ringbuffer submission or serialised as part of the context
	 * pinning क्रम execlists, and so we करो not need a mutex ourselves
	 * to serialise पूर्णांकel_ring_pin/पूर्णांकel_ring_unpin.
	 */
	atomic_t pin_count;

	u32 head; /* updated during retire, loosely tracks RING_HEAD */
	u32 tail; /* updated on submission, used क्रम RING_TAIL */
	u32 emit; /* updated during request स्थिरruction */

	u32 space;
	u32 size;
	u32 wrap;
	u32 effective_size;
पूर्ण;

#पूर्ण_अगर /* INTEL_RING_TYPES_H */
