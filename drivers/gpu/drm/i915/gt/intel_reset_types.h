<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_RESET_TYPES_H_
#घोषणा __INTEL_RESET_TYPES_H_

#समावेश <linux/mutex.h>
#समावेश <linux/रुको.h>
#समावेश <linux/srcu.h>

काष्ठा पूर्णांकel_reset अणु
	/**
	 * flags: Control various stages of the GPU reset
	 *
	 * #I915_RESET_BACKOFF - When we start a global reset, we need to
	 * serialise with any other users attempting to करो the same, and
	 * any global resources that may be clobber by the reset (such as
	 * FENCE रेजिस्टरs).
	 *
	 * #I915_RESET_ENGINE[num_engines] - Since the driver करोesn't need to
	 * acquire the काष्ठा_mutex to reset an engine, we need an explicit
	 * flag to prevent two concurrent reset attempts in the same engine.
	 * As the number of engines जारीs to grow, allocate the flags from
	 * the most signअगरicant bits.
	 *
	 * #I915_WEDGED - If reset fails and we can no दीर्घer use the GPU,
	 * we set the #I915_WEDGED bit. Prior to command submission, e.g.
	 * i915_request_alloc(), this bit is checked and the sequence
	 * पातed (with -EIO reported to userspace) अगर set.
	 *
	 * #I915_WEDGED_ON_INIT - If we fail to initialize the GPU we can no
	 * दीर्घer use the GPU - similar to #I915_WEDGED bit. The dअगरference in
	 * the way we're handling "forced" unwedged (e.g. through debugfs),
	 * which is not allowed in हाल we failed to initialize.
	 *
	 * #I915_WEDGED_ON_FINI - Similar to #I915_WEDGED_ON_INIT, except we
	 * use it to mark that the GPU is no दीर्घer available (and prevent
	 * users from using it).
	 */
	अचिन्हित दीर्घ flags;
#घोषणा I915_RESET_BACKOFF	0
#घोषणा I915_RESET_MODESET	1
#घोषणा I915_RESET_ENGINE	2
#घोषणा I915_WEDGED_ON_INIT	(BITS_PER_LONG - 3)
#घोषणा I915_WEDGED_ON_FINI	(BITS_PER_LONG - 2)
#घोषणा I915_WEDGED		(BITS_PER_LONG - 1)

	काष्ठा mutex mutex; /* serialises wedging/unwedging */

	/**
	 * Waitqueue to संकेत when the reset has completed. Used by clients
	 * that रुको क्रम dev_priv->mm.wedged to settle.
	 */
	रुको_queue_head_t queue;

	काष्ठा srcu_काष्ठा backoff_srcu;
पूर्ण;

#पूर्ण_अगर /* _INTEL_RESET_TYPES_H_ */
