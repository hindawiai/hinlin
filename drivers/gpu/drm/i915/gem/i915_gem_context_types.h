<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __I915_GEM_CONTEXT_TYPES_H__
#घोषणा __I915_GEM_CONTEXT_TYPES_H__

#समावेश <linux/atomic.h>
#समावेश <linux/list.h>
#समावेश <linux/llist.h>
#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/types.h>

#समावेश "gt/intel_context_types.h"

#समावेश "i915_scheduler.h"
#समावेश "i915_sw_fence.h"

काष्ठा pid;

काष्ठा drm_i915_निजी;
काष्ठा drm_i915_file_निजी;
काष्ठा i915_address_space;
काष्ठा पूर्णांकel_समयline;
काष्ठा पूर्णांकel_ring;

काष्ठा i915_gem_engines अणु
	जोड़ अणु
		काष्ठा list_head link;
		काष्ठा rcu_head rcu;
	पूर्ण;
	काष्ठा i915_sw_fence fence;
	काष्ठा i915_gem_context *ctx;
	अचिन्हित पूर्णांक num_engines;
	काष्ठा पूर्णांकel_context *engines[];
पूर्ण;

काष्ठा i915_gem_engines_iter अणु
	अचिन्हित पूर्णांक idx;
	स्थिर काष्ठा i915_gem_engines *engines;
पूर्ण;

/**
 * काष्ठा i915_gem_context - client state
 *
 * The काष्ठा i915_gem_context represents the combined view of the driver and
 * logical hardware state क्रम a particular client.
 */
काष्ठा i915_gem_context अणु
	/** i915: i915 device backpoपूर्णांकer */
	काष्ठा drm_i915_निजी *i915;

	/** file_priv: owning file descriptor */
	काष्ठा drm_i915_file_निजी *file_priv;

	/**
	 * @engines: User defined engines क्रम this context
	 *
	 * Various uAPI offer the ability to lookup up an
	 * index from this array to select an engine operate on.
	 *
	 * Multiple logically distinct instances of the same engine
	 * may be defined in the array, as well as composite भव
	 * engines.
	 *
	 * Execbuf uses the I915_EXEC_RING_MASK as an index पूर्णांकo this
	 * array to select which HW context + engine to execute on. For
	 * the शेष array, the user_ring_map[] is used to translate
	 * the legacy uABI onto the approprate index (e.g. both
	 * I915_EXEC_DEFAULT and I915_EXEC_RENDER select the same
	 * context, and I915_EXEC_BSD is weird). For a use defined
	 * array, execbuf uses I915_EXEC_RING_MASK as a plain index.
	 *
	 * User defined by I915_CONTEXT_PARAM_ENGINE (when the
	 * CONTEXT_USER_ENGINES flag is set).
	 */
	काष्ठा i915_gem_engines __rcu *engines;
	काष्ठा mutex engines_mutex; /* guards ग_लिखोs to engines */

	काष्ठा पूर्णांकel_समयline *समयline;

	/**
	 * @vm: unique address space (GTT)
	 *
	 * In full-ppgtt mode, each context has its own address space ensuring
	 * complete seperation of one client from all others.
	 *
	 * In other modes, this is a शून्य poपूर्णांकer with the expectation that
	 * the caller uses the shared global GTT.
	 */
	काष्ठा i915_address_space __rcu *vm;

	/**
	 * @pid: process id of creator
	 *
	 * Note that who created the context may not be the principle user,
	 * as the context may be shared across a local socket. However,
	 * that should only affect the शेष context, all contexts created
	 * explicitly by the client are expected to be isolated.
	 */
	काष्ठा pid *pid;

	/** link: place with &drm_i915_निजी.context_list */
	काष्ठा list_head link;

	/**
	 * @ref: reference count
	 *
	 * A reference to a context is held by both the client who created it
	 * and on each request submitted to the hardware using the request
	 * (to ensure the hardware has access to the state until it has
	 * finished all pending ग_लिखोs). See i915_gem_context_get() and
	 * i915_gem_context_put() क्रम access.
	 */
	काष्ठा kref ref;

	/**
	 * @rcu: rcu_head क्रम deferred मुक्तing.
	 */
	काष्ठा rcu_head rcu;

	/**
	 * @user_flags: small set of booleans controlled by the user
	 */
	अचिन्हित दीर्घ user_flags;
#घोषणा UCONTEXT_NO_ZEROMAP		0
#घोषणा UCONTEXT_NO_ERROR_CAPTURE	1
#घोषणा UCONTEXT_BANNABLE		2
#घोषणा UCONTEXT_RECOVERABLE		3
#घोषणा UCONTEXT_PERSISTENCE		4

	/**
	 * @flags: small set of booleans
	 */
	अचिन्हित दीर्घ flags;
#घोषणा CONTEXT_CLOSED			0
#घोषणा CONTEXT_USER_ENGINES		1

	काष्ठा mutex mutex;

	काष्ठा i915_sched_attr sched;

	/** guilty_count: How many बार this context has caused a GPU hang. */
	atomic_t guilty_count;
	/**
	 * @active_count: How many बार this context was active during a GPU
	 * hang, but did not cause it.
	 */
	atomic_t active_count;

	काष्ठा अणु
		u64 समयout_us;
	पूर्ण watchकरोg;

	/**
	 * @hang_बारtamp: The last समय(s) this context caused a GPU hang
	 */
	अचिन्हित दीर्घ hang_बारtamp[2];
#घोषणा CONTEXT_FAST_HANG_JIFFIES (120 * HZ) /* 3 hangs within 120s? Banned! */

	/** remap_slice: Biपंचांगask of cache lines that need remapping */
	u8 remap_slice;

	/**
	 * handles_vma: rbtree to look up our context specअगरic obj/vma क्रम
	 * the user handle. (user handles are per fd, but the binding is
	 * per vm, which may be one per context or shared with the global GTT)
	 */
	काष्ठा radix_tree_root handles_vma;
	काष्ठा mutex lut_mutex;

	/**
	 * @name: arbitrary name, used क्रम user debug
	 *
	 * A name is स्थिरructed क्रम the context from the creator's process
	 * name, pid and user handle in order to uniquely identअगरy the
	 * context in messages.
	 */
	अक्षर name[TASK_COMM_LEN + 8];

	काष्ठा अणु
		spinlock_t lock;
		काष्ठा list_head engines;
	पूर्ण stale;
पूर्ण;

#पूर्ण_अगर /* __I915_GEM_CONTEXT_TYPES_H__ */
