<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित _I915_ACTIVE_TYPES_H_
#घोषणा _I915_ACTIVE_TYPES_H_

#समावेश <linux/atomic.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/llist.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/workqueue.h>

#समावेश "i915_utils.h"

काष्ठा i915_active_fence अणु
	काष्ठा dma_fence __rcu *fence;
	काष्ठा dma_fence_cb cb;
पूर्ण;

काष्ठा active_node;

#घोषणा I915_ACTIVE_MAY_SLEEP BIT(0)

#घोषणा __i915_active_call __aligned(4)
#घोषणा i915_active_may_sleep(fn) ptr_pack_bits(&(fn), I915_ACTIVE_MAY_SLEEP, 2)

काष्ठा i915_active अणु
	atomic_t count;
	काष्ठा mutex mutex;

	spinlock_t tree_lock;
	काष्ठा active_node *cache;
	काष्ठा rb_root tree;

	/* Pपुनः_स्मृतिated "exclusive" node */
	काष्ठा i915_active_fence excl;

	अचिन्हित दीर्घ flags;
#घोषणा I915_ACTIVE_RETIRE_SLEEPS BIT(0)

	पूर्णांक (*active)(काष्ठा i915_active *ref);
	व्योम (*retire)(काष्ठा i915_active *ref);

	काष्ठा work_काष्ठा work;

	काष्ठा llist_head pपुनः_स्मृतिated_barriers;
पूर्ण;

#पूर्ण_अगर /* _I915_ACTIVE_TYPES_H_ */
