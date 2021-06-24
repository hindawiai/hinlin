<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2008,2010 Intel Corporation
 */

#समावेश <linux/पूर्णांकel-iommu.h>
#समावेश <linux/dma-resv.h>
#समावेश <linux/sync_file.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_syncobj.h>

#समावेश "display/intel_frontbuffer.h"

#समावेश "gem/i915_gem_ioctls.h"
#समावेश "gt/intel_context.h"
#समावेश "gt/intel_gpu_commands.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_buffer_pool.h"
#समावेश "gt/intel_gt_pm.h"
#समावेश "gt/intel_ring.h"

#समावेश "i915_drv.h"
#समावेश "i915_gem_clflush.h"
#समावेश "i915_gem_context.h"
#समावेश "i915_gem_ioctls.h"
#समावेश "i915_sw_fence_work.h"
#समावेश "i915_trace.h"
#समावेश "i915_user_extensions.h"
#समावेश "i915_memcpy.h"

काष्ठा eb_vma अणु
	काष्ठा i915_vma *vma;
	अचिन्हित पूर्णांक flags;

	/** This vma's place in the execbuf reservation list */
	काष्ठा drm_i915_gem_exec_object2 *exec;
	काष्ठा list_head bind_link;
	काष्ठा list_head reloc_link;

	काष्ठा hlist_node node;
	u32 handle;
पूर्ण;

क्रमागत अणु
	FORCE_CPU_RELOC = 1,
	FORCE_GTT_RELOC,
	FORCE_GPU_RELOC,
#घोषणा DBG_FORCE_RELOC 0 /* choose one of the above! */
पूर्ण;

/* __EXEC_OBJECT_NO_RESERVE is BIT(31), defined in i915_vma.h */
#घोषणा __EXEC_OBJECT_HAS_PIN		BIT(30)
#घोषणा __EXEC_OBJECT_HAS_FENCE		BIT(29)
#घोषणा __EXEC_OBJECT_USERPTR_INIT	BIT(28)
#घोषणा __EXEC_OBJECT_NEEDS_MAP		BIT(27)
#घोषणा __EXEC_OBJECT_NEEDS_BIAS	BIT(26)
#घोषणा __EXEC_OBJECT_INTERNAL_FLAGS	(~0u << 26) /* all of the above + */
#घोषणा __EXEC_OBJECT_RESERVED (__EXEC_OBJECT_HAS_PIN | __EXEC_OBJECT_HAS_FENCE)

#घोषणा __EXEC_HAS_RELOC	BIT(31)
#घोषणा __EXEC_ENGINE_PINNED	BIT(30)
#घोषणा __EXEC_USERPTR_USED	BIT(29)
#घोषणा __EXEC_INTERNAL_FLAGS	(~0u << 29)
#घोषणा UPDATE			PIN_OFFSET_FIXED

#घोषणा BATCH_OFFSET_BIAS (256*1024)

#घोषणा __I915_EXEC_ILLEGAL_FLAGS \
	(__I915_EXEC_UNKNOWN_FLAGS | \
	 I915_EXEC_CONSTANTS_MASK  | \
	 I915_EXEC_RESOURCE_STREAMER)

/* Catch emission of unexpected errors क्रम CI! */
#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM)
#अघोषित EINVAL
#घोषणा EINVAL (अणु \
	DRM_DEBUG_DRIVER("EINVAL at %s:%d\n", __func__, __LINE__); \
	22; \
पूर्ण)
#पूर्ण_अगर

/**
 * DOC: User command execution
 *
 * Userspace submits commands to be executed on the GPU as an inकाष्ठाion
 * stream within a GEM object we call a batchbuffer. This inकाष्ठाions may
 * refer to other GEM objects containing auxiliary state such as kernels,
 * samplers, render tarमाला_लो and even secondary batchbuffers. Userspace करोes
 * not know where in the GPU memory these objects reside and so beक्रमe the
 * batchbuffer is passed to the GPU क्रम execution, those addresses in the
 * batchbuffer and auxiliary objects are updated. This is known as relocation,
 * or patching. To try and aव्योम having to relocate each object on the next
 * execution, userspace is told the location of those objects in this pass,
 * but this reमुख्यs just a hपूर्णांक as the kernel may choose a new location क्रम
 * any object in the future.
 *
 * At the level of talking to the hardware, submitting a batchbuffer क्रम the
 * GPU to execute is to add content to a buffer from which the HW
 * command streamer is पढ़ोing.
 *
 * 1. Add a command to load the HW context. For Logical Ring Contexts, i.e.
 *    Execlists, this command is not placed on the same buffer as the
 *    reमुख्यing items.
 *
 * 2. Add a command to invalidate caches to the buffer.
 *
 * 3. Add a batchbuffer start command to the buffer; the start command is
 *    essentially a token together with the GPU address of the batchbuffer
 *    to be executed.
 *
 * 4. Add a pipeline flush to the buffer.
 *
 * 5. Add a memory ग_लिखो command to the buffer to record when the GPU
 *    is करोne executing the batchbuffer. The memory ग_लिखो ग_लिखोs the
 *    global sequence number of the request, ``i915_request::global_seqno``;
 *    the i915 driver uses the current value in the रेजिस्टर to determine
 *    अगर the GPU has completed the batchbuffer.
 *
 * 6. Add a user पूर्णांकerrupt command to the buffer. This command inकाष्ठाs
 *    the GPU to issue an पूर्णांकerrupt when the command, pipeline flush and
 *    memory ग_लिखो are completed.
 *
 * 7. Inक्रमm the hardware of the additional commands added to the buffer
 *    (by updating the tail poपूर्णांकer).
 *
 * Processing an execbuf ioctl is conceptually split up पूर्णांकo a few phases.
 *
 * 1. Validation - Ensure all the poपूर्णांकers, handles and flags are valid.
 * 2. Reservation - Assign GPU address space क्रम every object
 * 3. Relocation - Update any addresses to poपूर्णांक to the final locations
 * 4. Serialisation - Order the request with respect to its dependencies
 * 5. Conकाष्ठाion - Conकाष्ठा a request to execute the batchbuffer
 * 6. Submission (at some poपूर्णांक in the future execution)
 *
 * Reserving resources क्रम the execbuf is the most complicated phase. We
 * neither want to have to migrate the object in the address space, nor करो
 * we want to have to update any relocations poपूर्णांकing to this object. Ideally,
 * we want to leave the object where it is and क्रम all the existing relocations
 * to match. If the object is given a new address, or अगर userspace thinks the
 * object is अन्यथाwhere, we have to parse all the relocation entries and update
 * the addresses. Userspace can set the I915_EXEC_NORELOC flag to hपूर्णांक that
 * all the target addresses in all of its objects match the value in the
 * relocation entries and that they all match the presumed offsets given by the
 * list of execbuffer objects. Using this knowledge, we know that अगर we haven't
 * moved any buffers, all the relocation entries are valid and we can skip
 * the update. (If userspace is wrong, the likely outcome is an impromptu GPU
 * hang.) The requirement क्रम using I915_EXEC_NO_RELOC are:
 *
 *      The addresses written in the objects must match the corresponding
 *      reloc.presumed_offset which in turn must match the corresponding
 *      execobject.offset.
 *
 *      Any render tarमाला_लो written to in the batch must be flagged with
 *      EXEC_OBJECT_WRITE.
 *
 *      To aव्योम stalling, execobject.offset should match the current
 *      address of that object within the active context.
 *
 * The reservation is करोne is multiple phases. First we try and keep any
 * object alपढ़ोy bound in its current location - so as दीर्घ as meets the
 * स्थिरraपूर्णांकs imposed by the new execbuffer. Any object left unbound after the
 * first pass is then fitted पूर्णांकo any available idle space. If an object करोes
 * not fit, all objects are हटाओd from the reservation and the process rerun
 * after sorting the objects पूर्णांकo a priority order (more dअगरficult to fit
 * objects are tried first). Failing that, the entire VM is cleared and we try
 * to fit the execbuf once last समय beक्रमe concluding that it simply will not
 * fit.
 *
 * A small complication to all of this is that we allow userspace not only to
 * specअगरy an alignment and a size क्रम the object in the address space, but
 * we also allow userspace to specअगरy the exact offset. This objects are
 * simpler to place (the location is known a priori) all we have to करो is make
 * sure the space is available.
 *
 * Once all the objects are in place, patching up the buried poपूर्णांकers to poपूर्णांक
 * to the final locations is a fairly simple job of walking over the relocation
 * entry arrays, looking up the right address and rewriting the value पूर्णांकo
 * the object. Simple! ... The relocation entries are stored in user memory
 * and so to access them we have to copy them पूर्णांकo a local buffer. That copy
 * has to aव्योम taking any pagefaults as they may lead back to a GEM object
 * requiring the काष्ठा_mutex (i.e. recursive deadlock). So once again we split
 * the relocation पूर्णांकo multiple passes. First we try to करो everything within an
 * atomic context (aव्योम the pagefaults) which requires that we never रुको. If
 * we detect that we may रुको, or अगर we need to fault, then we have to fallback
 * to a slower path. The slowpath has to drop the mutex. (Can you hear alarm
 * bells yet?) Dropping the mutex means that we lose all the state we have
 * built up so far क्रम the execbuf and we must reset any global data. However,
 * we करो leave the objects pinned in their final locations - which is a
 * potential issue क्रम concurrent execbufs. Once we have left the mutex, we can
 * allocate and copy all the relocation entries पूर्णांकo a large array at our
 * leisure, reacquire the mutex, reclaim all the objects and other state and
 * then proceed to update any incorrect addresses with the objects.
 *
 * As we process the relocation entries, we मुख्यtain a record of whether the
 * object is being written to. Using NORELOC, we expect userspace to provide
 * this inक्रमmation instead. We also check whether we can skip the relocation
 * by comparing the expected value inside the relocation entry with the target's
 * final address. If they dअगरfer, we have to map the current object and reग_लिखो
 * the 4 or 8 byte poपूर्णांकer within.
 *
 * Serialising an execbuf is quite simple according to the rules of the GEM
 * ABI. Execution within each context is ordered by the order of submission.
 * Writes to any GEM object are in order of submission and are exclusive. Reads
 * from a GEM object are unordered with respect to other पढ़ोs, but ordered by
 * ग_लिखोs. A ग_लिखो submitted after a पढ़ो cannot occur beक्रमe the पढ़ो, and
 * similarly any पढ़ो submitted after a ग_लिखो cannot occur beक्रमe the ग_लिखो.
 * Writes are ordered between engines such that only one ग_लिखो occurs at any
 * समय (completing any पढ़ोs beक्रमehand) - using semaphores where available
 * and CPU serialisation otherwise. Other GEM access obey the same rules, any
 * ग_लिखो (either via mmaps using set-करोमुख्य, or via pग_लिखो) must flush all GPU
 * पढ़ोs beक्रमe starting, and any पढ़ो (either using set-करोमुख्य or pपढ़ो) must
 * flush all GPU ग_लिखोs beक्रमe starting. (Note we only employ a barrier beक्रमe,
 * we currently rely on userspace not concurrently starting a new execution
 * whilst पढ़ोing or writing to an object. This may be an advantage or not
 * depending on how much you trust userspace not to shoot themselves in the
 * foot.) Serialisation may just result in the request being inserted पूर्णांकo
 * a DAG aरुकोing its turn, but most simple is to रुको on the CPU until
 * all dependencies are resolved.
 *
 * After all of that, is just a matter of closing the request and handing it to
 * the hardware (well, leaving it in a queue to be executed). However, we also
 * offer the ability क्रम batchbuffers to be run with elevated privileges so
 * that they access otherwise hidden रेजिस्टरs. (Used to adjust L3 cache etc.)
 * Beक्रमe any batch is given extra privileges we first must check that it
 * contains no nefarious inकाष्ठाions, we check that each inकाष्ठाion is from
 * our whitelist and all रेजिस्टरs are also from an allowed list. We first
 * copy the user's batchbuffer to a shadow (so that the user doesn't have
 * access to it, either by the CPU or GPU as we scan it) and then parse each
 * inकाष्ठाion. If everything is ok, we set a flag telling the hardware to run
 * the batchbuffer in trusted mode, otherwise the ioctl is rejected.
 */

काष्ठा eb_fence अणु
	काष्ठा drm_syncobj *syncobj; /* Use with ptr_mask_bits() */
	काष्ठा dma_fence *dma_fence;
	u64 value;
	काष्ठा dma_fence_chain *chain_fence;
पूर्ण;

काष्ठा i915_execbuffer अणु
	काष्ठा drm_i915_निजी *i915; /** i915 backpoपूर्णांकer */
	काष्ठा drm_file *file; /** per-file lookup tables and limits */
	काष्ठा drm_i915_gem_execbuffer2 *args; /** ioctl parameters */
	काष्ठा drm_i915_gem_exec_object2 *exec; /** ioctl execobj[] */
	काष्ठा eb_vma *vma;

	काष्ठा पूर्णांकel_engine_cs *engine; /** engine to queue the request to */
	काष्ठा पूर्णांकel_context *context; /* logical state क्रम the request */
	काष्ठा i915_gem_context *gem_context; /** caller's context */

	काष्ठा i915_request *request; /** our request to build */
	काष्ठा eb_vma *batch; /** identity of the batch obj/vma */
	काष्ठा i915_vma *trampoline; /** trampoline used क्रम chaining */

	/** actual size of execobj[] as we may extend it क्रम the cmdparser */
	अचिन्हित पूर्णांक buffer_count;

	/** list of vma not yet bound during reservation phase */
	काष्ठा list_head unbound;

	/** list of vma that have execobj.relocation_count */
	काष्ठा list_head relocs;

	काष्ठा i915_gem_ww_ctx ww;

	/**
	 * Track the most recently used object क्रम relocations, as we
	 * frequently have to perक्रमm multiple relocations within the same
	 * obj/page
	 */
	काष्ठा reloc_cache अणु
		काष्ठा drm_mm_node node; /** temporary GTT binding */
		अचिन्हित दीर्घ vaddr; /** Current kmap address */
		अचिन्हित दीर्घ page; /** Currently mapped page index */
		अचिन्हित पूर्णांक gen; /** Cached value of INTEL_GEN */
		bool use_64bit_reloc : 1;
		bool has_llc : 1;
		bool has_fence : 1;
		bool needs_unfenced : 1;

		काष्ठा i915_request *rq;
		u32 *rq_cmd;
		अचिन्हित पूर्णांक rq_size;
		काष्ठा पूर्णांकel_gt_buffer_pool_node *pool;
	पूर्ण reloc_cache;

	काष्ठा पूर्णांकel_gt_buffer_pool_node *reloc_pool; /** relocation pool क्रम -EDEADLK handling */
	काष्ठा पूर्णांकel_context *reloc_context;

	u64 invalid_flags; /** Set of execobj.flags that are invalid */
	u32 context_flags; /** Set of execobj.flags to insert from the ctx */

	u64 batch_len; /** Length of batch within object */
	u32 batch_start_offset; /** Location within object of batch */
	u32 batch_flags; /** Flags composed क्रम emit_bb_start() */
	काष्ठा पूर्णांकel_gt_buffer_pool_node *batch_pool; /** pool node क्रम batch buffer */

	/**
	 * Indicate either the size of the hastable used to resolve
	 * relocation handles, or अगर negative that we are using a direct
	 * index पूर्णांकo the execobj[].
	 */
	पूर्णांक lut_size;
	काष्ठा hlist_head *buckets; /** ht क्रम relocation handles */

	काष्ठा eb_fence *fences;
	अचिन्हित दीर्घ num_fences;
पूर्ण;

अटल पूर्णांक eb_parse(काष्ठा i915_execbuffer *eb);
अटल काष्ठा i915_request *eb_pin_engine(काष्ठा i915_execbuffer *eb,
					  bool throttle);
अटल व्योम eb_unpin_engine(काष्ठा i915_execbuffer *eb);

अटल अंतरभूत bool eb_use_cmdparser(स्थिर काष्ठा i915_execbuffer *eb)
अणु
	वापस पूर्णांकel_engine_requires_cmd_parser(eb->engine) ||
		(पूर्णांकel_engine_using_cmd_parser(eb->engine) &&
		 eb->args->batch_len);
पूर्ण

अटल पूर्णांक eb_create(काष्ठा i915_execbuffer *eb)
अणु
	अगर (!(eb->args->flags & I915_EXEC_HANDLE_LUT)) अणु
		अचिन्हित पूर्णांक size = 1 + ilog2(eb->buffer_count);

		/*
		 * Without a 1:1 association between relocation handles and
		 * the execobject[] index, we instead create a hashtable.
		 * We size it dynamically based on available memory, starting
		 * first with 1:1 assocative hash and scaling back until
		 * the allocation succeeds.
		 *
		 * Later on we use a positive lut_size to indicate we are
		 * using this hashtable, and a negative value to indicate a
		 * direct lookup.
		 */
		करो अणु
			gfp_t flags;

			/* While we can still reduce the allocation size, करोn't
			 * उठाओ a warning and allow the allocation to fail.
			 * On the last pass though, we want to try as hard
			 * as possible to perक्रमm the allocation and warn
			 * अगर it fails.
			 */
			flags = GFP_KERNEL;
			अगर (size > 1)
				flags |= __GFP_NORETRY | __GFP_NOWARN;

			eb->buckets = kzalloc(माप(काष्ठा hlist_head) << size,
					      flags);
			अगर (eb->buckets)
				अवरोध;
		पूर्ण जबतक (--size);

		अगर (unlikely(!size))
			वापस -ENOMEM;

		eb->lut_size = size;
	पूर्ण अन्यथा अणु
		eb->lut_size = -eb->buffer_count;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
eb_vma_misplaced(स्थिर काष्ठा drm_i915_gem_exec_object2 *entry,
		 स्थिर काष्ठा i915_vma *vma,
		 अचिन्हित पूर्णांक flags)
अणु
	अगर (vma->node.size < entry->pad_to_size)
		वापस true;

	अगर (entry->alignment && !IS_ALIGNED(vma->node.start, entry->alignment))
		वापस true;

	अगर (flags & EXEC_OBJECT_PINNED &&
	    vma->node.start != entry->offset)
		वापस true;

	अगर (flags & __EXEC_OBJECT_NEEDS_BIAS &&
	    vma->node.start < BATCH_OFFSET_BIAS)
		वापस true;

	अगर (!(flags & EXEC_OBJECT_SUPPORTS_48B_ADDRESS) &&
	    (vma->node.start + vma->node.size + 4095) >> 32)
		वापस true;

	अगर (flags & __EXEC_OBJECT_NEEDS_MAP &&
	    !i915_vma_is_map_and_fenceable(vma))
		वापस true;

	वापस false;
पूर्ण

अटल u64 eb_pin_flags(स्थिर काष्ठा drm_i915_gem_exec_object2 *entry,
			अचिन्हित पूर्णांक exec_flags)
अणु
	u64 pin_flags = 0;

	अगर (exec_flags & EXEC_OBJECT_NEEDS_GTT)
		pin_flags |= PIN_GLOBAL;

	/*
	 * Wa32bitGeneralStateOffset & Wa32bitInकाष्ठाionBaseOffset,
	 * limit address to the first 4GBs क्रम unflagged objects.
	 */
	अगर (!(exec_flags & EXEC_OBJECT_SUPPORTS_48B_ADDRESS))
		pin_flags |= PIN_ZONE_4G;

	अगर (exec_flags & __EXEC_OBJECT_NEEDS_MAP)
		pin_flags |= PIN_MAPPABLE;

	अगर (exec_flags & EXEC_OBJECT_PINNED)
		pin_flags |= entry->offset | PIN_OFFSET_FIXED;
	अन्यथा अगर (exec_flags & __EXEC_OBJECT_NEEDS_BIAS)
		pin_flags |= BATCH_OFFSET_BIAS | PIN_OFFSET_BIAS;

	वापस pin_flags;
पूर्ण

अटल अंतरभूत पूर्णांक
eb_pin_vma(काष्ठा i915_execbuffer *eb,
	   स्थिर काष्ठा drm_i915_gem_exec_object2 *entry,
	   काष्ठा eb_vma *ev)
अणु
	काष्ठा i915_vma *vma = ev->vma;
	u64 pin_flags;
	पूर्णांक err;

	अगर (vma->node.size)
		pin_flags = vma->node.start;
	अन्यथा
		pin_flags = entry->offset & PIN_OFFSET_MASK;

	pin_flags |= PIN_USER | PIN_NOEVICT | PIN_OFFSET_FIXED;
	अगर (unlikely(ev->flags & EXEC_OBJECT_NEEDS_GTT))
		pin_flags |= PIN_GLOBAL;

	/* Attempt to reuse the current location अगर available */
	err = i915_vma_pin_ww(vma, &eb->ww, 0, 0, pin_flags);
	अगर (err == -EDEADLK)
		वापस err;

	अगर (unlikely(err)) अणु
		अगर (entry->flags & EXEC_OBJECT_PINNED)
			वापस err;

		/* Failing that pick any _मुक्त_ space अगर suitable */
		err = i915_vma_pin_ww(vma, &eb->ww,
					     entry->pad_to_size,
					     entry->alignment,
					     eb_pin_flags(entry, ev->flags) |
					     PIN_USER | PIN_NOEVICT);
		अगर (unlikely(err))
			वापस err;
	पूर्ण

	अगर (unlikely(ev->flags & EXEC_OBJECT_NEEDS_FENCE)) अणु
		err = i915_vma_pin_fence(vma);
		अगर (unlikely(err)) अणु
			i915_vma_unpin(vma);
			वापस err;
		पूर्ण

		अगर (vma->fence)
			ev->flags |= __EXEC_OBJECT_HAS_FENCE;
	पूर्ण

	ev->flags |= __EXEC_OBJECT_HAS_PIN;
	अगर (eb_vma_misplaced(entry, vma, ev->flags))
		वापस -EBADSLT;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
eb_unreserve_vma(काष्ठा eb_vma *ev)
अणु
	अगर (!(ev->flags & __EXEC_OBJECT_HAS_PIN))
		वापस;

	अगर (unlikely(ev->flags & __EXEC_OBJECT_HAS_FENCE))
		__i915_vma_unpin_fence(ev->vma);

	__i915_vma_unpin(ev->vma);
	ev->flags &= ~__EXEC_OBJECT_RESERVED;
पूर्ण

अटल पूर्णांक
eb_validate_vma(काष्ठा i915_execbuffer *eb,
		काष्ठा drm_i915_gem_exec_object2 *entry,
		काष्ठा i915_vma *vma)
अणु
	/* Relocations are disallowed क्रम all platक्रमms after TGL-LP.  This
	 * also covers all platक्रमms with local memory.
	 */
	अगर (entry->relocation_count &&
	    INTEL_GEN(eb->i915) >= 12 && !IS_TIGERLAKE(eb->i915))
		वापस -EINVAL;

	अगर (unlikely(entry->flags & eb->invalid_flags))
		वापस -EINVAL;

	अगर (unlikely(entry->alignment &&
		     !is_घातer_of_2_u64(entry->alignment)))
		वापस -EINVAL;

	/*
	 * Offset can be used as input (EXEC_OBJECT_PINNED), reject
	 * any non-page-aligned or non-canonical addresses.
	 */
	अगर (unlikely(entry->flags & EXEC_OBJECT_PINNED &&
		     entry->offset != gen8_canonical_addr(entry->offset & I915_GTT_PAGE_MASK)))
		वापस -EINVAL;

	/* pad_to_size was once a reserved field, so sanitize it */
	अगर (entry->flags & EXEC_OBJECT_PAD_TO_SIZE) अणु
		अगर (unlikely(offset_in_page(entry->pad_to_size)))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		entry->pad_to_size = 0;
	पूर्ण
	/*
	 * From drm_mm perspective address space is continuous,
	 * so from this poपूर्णांक we're always using non-canonical
	 * क्रमm पूर्णांकernally.
	 */
	entry->offset = gen8_noncanonical_addr(entry->offset);

	अगर (!eb->reloc_cache.has_fence) अणु
		entry->flags &= ~EXEC_OBJECT_NEEDS_FENCE;
	पूर्ण अन्यथा अणु
		अगर ((entry->flags & EXEC_OBJECT_NEEDS_FENCE ||
		     eb->reloc_cache.needs_unfenced) &&
		    i915_gem_object_is_tiled(vma->obj))
			entry->flags |= EXEC_OBJECT_NEEDS_GTT | __EXEC_OBJECT_NEEDS_MAP;
	पूर्ण

	अगर (!(entry->flags & EXEC_OBJECT_PINNED))
		entry->flags |= eb->context_flags;

	वापस 0;
पूर्ण

अटल व्योम
eb_add_vma(काष्ठा i915_execbuffer *eb,
	   अचिन्हित पूर्णांक i, अचिन्हित batch_idx,
	   काष्ठा i915_vma *vma)
अणु
	काष्ठा drm_i915_gem_exec_object2 *entry = &eb->exec[i];
	काष्ठा eb_vma *ev = &eb->vma[i];

	ev->vma = vma;
	ev->exec = entry;
	ev->flags = entry->flags;

	अगर (eb->lut_size > 0) अणु
		ev->handle = entry->handle;
		hlist_add_head(&ev->node,
			       &eb->buckets[hash_32(entry->handle,
						    eb->lut_size)]);
	पूर्ण

	अगर (entry->relocation_count)
		list_add_tail(&ev->reloc_link, &eb->relocs);

	/*
	 * SNA is करोing fancy tricks with compressing batch buffers, which leads
	 * to negative relocation deltas. Usually that works out ok since the
	 * relocate address is still positive, except when the batch is placed
	 * very low in the GTT. Ensure this करोesn't happen.
	 *
	 * Note that actual hangs have only been observed on gen7, but क्रम
	 * paranoia करो it everywhere.
	 */
	अगर (i == batch_idx) अणु
		अगर (entry->relocation_count &&
		    !(ev->flags & EXEC_OBJECT_PINNED))
			ev->flags |= __EXEC_OBJECT_NEEDS_BIAS;
		अगर (eb->reloc_cache.has_fence)
			ev->flags |= EXEC_OBJECT_NEEDS_FENCE;

		eb->batch = ev;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक use_cpu_reloc(स्थिर काष्ठा reloc_cache *cache,
				स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	अगर (!i915_gem_object_has_काष्ठा_page(obj))
		वापस false;

	अगर (DBG_FORCE_RELOC == FORCE_CPU_RELOC)
		वापस true;

	अगर (DBG_FORCE_RELOC == FORCE_GTT_RELOC)
		वापस false;

	वापस (cache->has_llc ||
		obj->cache_dirty ||
		obj->cache_level != I915_CACHE_NONE);
पूर्ण

अटल पूर्णांक eb_reserve_vma(काष्ठा i915_execbuffer *eb,
			  काष्ठा eb_vma *ev,
			  u64 pin_flags)
अणु
	काष्ठा drm_i915_gem_exec_object2 *entry = ev->exec;
	काष्ठा i915_vma *vma = ev->vma;
	पूर्णांक err;

	अगर (drm_mm_node_allocated(&vma->node) &&
	    eb_vma_misplaced(entry, vma, ev->flags)) अणु
		err = i915_vma_unbind(vma);
		अगर (err)
			वापस err;
	पूर्ण

	err = i915_vma_pin_ww(vma, &eb->ww,
			   entry->pad_to_size, entry->alignment,
			   eb_pin_flags(entry, ev->flags) | pin_flags);
	अगर (err)
		वापस err;

	अगर (entry->offset != vma->node.start) अणु
		entry->offset = vma->node.start | UPDATE;
		eb->args->flags |= __EXEC_HAS_RELOC;
	पूर्ण

	अगर (unlikely(ev->flags & EXEC_OBJECT_NEEDS_FENCE)) अणु
		err = i915_vma_pin_fence(vma);
		अगर (unlikely(err)) अणु
			i915_vma_unpin(vma);
			वापस err;
		पूर्ण

		अगर (vma->fence)
			ev->flags |= __EXEC_OBJECT_HAS_FENCE;
	पूर्ण

	ev->flags |= __EXEC_OBJECT_HAS_PIN;
	GEM_BUG_ON(eb_vma_misplaced(entry, vma, ev->flags));

	वापस 0;
पूर्ण

अटल पूर्णांक eb_reserve(काष्ठा i915_execbuffer *eb)
अणु
	स्थिर अचिन्हित पूर्णांक count = eb->buffer_count;
	अचिन्हित पूर्णांक pin_flags = PIN_USER | PIN_NONBLOCK;
	काष्ठा list_head last;
	काष्ठा eb_vma *ev;
	अचिन्हित पूर्णांक i, pass;
	पूर्णांक err = 0;

	/*
	 * Attempt to pin all of the buffers पूर्णांकo the GTT.
	 * This is करोne in 3 phases:
	 *
	 * 1a. Unbind all objects that करो not match the GTT स्थिरraपूर्णांकs क्रम
	 *     the execbuffer (fenceable, mappable, alignment etc).
	 * 1b. Increment pin count क्रम alपढ़ोy bound objects.
	 * 2.  Bind new objects.
	 * 3.  Decrement pin count.
	 *
	 * This aव्योम unnecessary unbinding of later objects in order to make
	 * room क्रम the earlier objects *unless* we need to defragment.
	 */
	pass = 0;
	करो अणु
		list_क्रम_each_entry(ev, &eb->unbound, bind_link) अणु
			err = eb_reserve_vma(eb, ev, pin_flags);
			अगर (err)
				अवरोध;
		पूर्ण
		अगर (err != -ENOSPC)
			वापस err;

		/* Resort *all* the objects पूर्णांकo priority order */
		INIT_LIST_HEAD(&eb->unbound);
		INIT_LIST_HEAD(&last);
		क्रम (i = 0; i < count; i++) अणु
			अचिन्हित पूर्णांक flags;

			ev = &eb->vma[i];
			flags = ev->flags;
			अगर (flags & EXEC_OBJECT_PINNED &&
			    flags & __EXEC_OBJECT_HAS_PIN)
				जारी;

			eb_unreserve_vma(ev);

			अगर (flags & EXEC_OBJECT_PINNED)
				/* Pinned must have their slot */
				list_add(&ev->bind_link, &eb->unbound);
			अन्यथा अगर (flags & __EXEC_OBJECT_NEEDS_MAP)
				/* Map require the lowest 256MiB (aperture) */
				list_add_tail(&ev->bind_link, &eb->unbound);
			अन्यथा अगर (!(flags & EXEC_OBJECT_SUPPORTS_48B_ADDRESS))
				/* Prioritise 4GiB region क्रम restricted bo */
				list_add(&ev->bind_link, &last);
			अन्यथा
				list_add_tail(&ev->bind_link, &last);
		पूर्ण
		list_splice_tail(&last, &eb->unbound);

		चयन (pass++) अणु
		हाल 0:
			अवरोध;

		हाल 1:
			/* Too fragmented, unbind everything and retry */
			mutex_lock(&eb->context->vm->mutex);
			err = i915_gem_evict_vm(eb->context->vm);
			mutex_unlock(&eb->context->vm->mutex);
			अगर (err)
				वापस err;
			अवरोध;

		शेष:
			वापस -ENOSPC;
		पूर्ण

		pin_flags = PIN_USER;
	पूर्ण जबतक (1);
पूर्ण

अटल अचिन्हित पूर्णांक eb_batch_index(स्थिर काष्ठा i915_execbuffer *eb)
अणु
	अगर (eb->args->flags & I915_EXEC_BATCH_FIRST)
		वापस 0;
	अन्यथा
		वापस eb->buffer_count - 1;
पूर्ण

अटल पूर्णांक eb_select_context(काष्ठा i915_execbuffer *eb)
अणु
	काष्ठा i915_gem_context *ctx;

	ctx = i915_gem_context_lookup(eb->file->driver_priv, eb->args->rsvd1);
	अगर (unlikely(!ctx))
		वापस -ENOENT;

	eb->gem_context = ctx;
	अगर (rcu_access_poपूर्णांकer(ctx->vm))
		eb->invalid_flags |= EXEC_OBJECT_NEEDS_GTT;

	eb->context_flags = 0;
	अगर (test_bit(UCONTEXT_NO_ZEROMAP, &ctx->user_flags))
		eb->context_flags |= __EXEC_OBJECT_NEEDS_BIAS;

	वापस 0;
पूर्ण

अटल पूर्णांक __eb_add_lut(काष्ठा i915_execbuffer *eb,
			u32 handle, काष्ठा i915_vma *vma)
अणु
	काष्ठा i915_gem_context *ctx = eb->gem_context;
	काष्ठा i915_lut_handle *lut;
	पूर्णांक err;

	lut = i915_lut_handle_alloc();
	अगर (unlikely(!lut))
		वापस -ENOMEM;

	i915_vma_get(vma);
	अगर (!atomic_fetch_inc(&vma->खोलो_count))
		i915_vma_reखोलो(vma);
	lut->handle = handle;
	lut->ctx = ctx;

	/* Check that the context hasn't been बंदd in the meanसमय */
	err = -EINTR;
	अगर (!mutex_lock_पूर्णांकerruptible(&ctx->lut_mutex)) अणु
		काष्ठा i915_address_space *vm = rcu_access_poपूर्णांकer(ctx->vm);

		अगर (unlikely(vm && vma->vm != vm))
			err = -EAGAIN; /* user racing with ctx set-vm */
		अन्यथा अगर (likely(!i915_gem_context_is_बंदd(ctx)))
			err = radix_tree_insert(&ctx->handles_vma, handle, vma);
		अन्यथा
			err = -ENOENT;
		अगर (err == 0) अणु /* And nor has this handle */
			काष्ठा drm_i915_gem_object *obj = vma->obj;

			spin_lock(&obj->lut_lock);
			अगर (idr_find(&eb->file->object_idr, handle) == obj) अणु
				list_add(&lut->obj_link, &obj->lut_list);
			पूर्ण अन्यथा अणु
				radix_tree_delete(&ctx->handles_vma, handle);
				err = -ENOENT;
			पूर्ण
			spin_unlock(&obj->lut_lock);
		पूर्ण
		mutex_unlock(&ctx->lut_mutex);
	पूर्ण
	अगर (unlikely(err))
		जाओ err;

	वापस 0;

err:
	i915_vma_बंद(vma);
	i915_vma_put(vma);
	i915_lut_handle_मुक्त(lut);
	वापस err;
पूर्ण

अटल काष्ठा i915_vma *eb_lookup_vma(काष्ठा i915_execbuffer *eb, u32 handle)
अणु
	काष्ठा i915_address_space *vm = eb->context->vm;

	करो अणु
		काष्ठा drm_i915_gem_object *obj;
		काष्ठा i915_vma *vma;
		पूर्णांक err;

		rcu_पढ़ो_lock();
		vma = radix_tree_lookup(&eb->gem_context->handles_vma, handle);
		अगर (likely(vma && vma->vm == vm))
			vma = i915_vma_tryget(vma);
		rcu_पढ़ो_unlock();
		अगर (likely(vma))
			वापस vma;

		obj = i915_gem_object_lookup(eb->file, handle);
		अगर (unlikely(!obj))
			वापस ERR_PTR(-ENOENT);

		vma = i915_vma_instance(obj, vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			i915_gem_object_put(obj);
			वापस vma;
		पूर्ण

		err = __eb_add_lut(eb, handle, vma);
		अगर (likely(!err))
			वापस vma;

		i915_gem_object_put(obj);
		अगर (err != -EEXIST)
			वापस ERR_PTR(err);
	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक eb_lookup_vmas(काष्ठा i915_execbuffer *eb)
अणु
	काष्ठा drm_i915_निजी *i915 = eb->i915;
	अचिन्हित पूर्णांक batch = eb_batch_index(eb);
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	INIT_LIST_HEAD(&eb->relocs);

	क्रम (i = 0; i < eb->buffer_count; i++) अणु
		काष्ठा i915_vma *vma;

		vma = eb_lookup_vma(eb, eb->exec[i].handle);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ err;
		पूर्ण

		err = eb_validate_vma(eb, &eb->exec[i], vma);
		अगर (unlikely(err)) अणु
			i915_vma_put(vma);
			जाओ err;
		पूर्ण

		eb_add_vma(eb, i, batch, vma);

		अगर (i915_gem_object_is_userptr(vma->obj)) अणु
			err = i915_gem_object_userptr_submit_init(vma->obj);
			अगर (err) अणु
				अगर (i + 1 < eb->buffer_count) अणु
					/*
					 * Execbuffer code expects last vma entry to be शून्य,
					 * since we alपढ़ोy initialized this entry,
					 * set the next value to शून्य or we mess up
					 * cleanup handling.
					 */
					eb->vma[i + 1].vma = शून्य;
				पूर्ण

				वापस err;
			पूर्ण

			eb->vma[i].flags |= __EXEC_OBJECT_USERPTR_INIT;
			eb->args->flags |= __EXEC_USERPTR_USED;
		पूर्ण
	पूर्ण

	अगर (unlikely(eb->batch->flags & EXEC_OBJECT_WRITE)) अणु
		drm_dbg(&i915->drm,
			"Attempting to use self-modifying batch buffer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (range_overflows_t(u64,
			      eb->batch_start_offset, eb->batch_len,
			      eb->batch->vma->size)) अणु
		drm_dbg(&i915->drm, "Attempting to use out-of-bounds batch\n");
		वापस -EINVAL;
	पूर्ण

	अगर (eb->batch_len == 0)
		eb->batch_len = eb->batch->vma->size - eb->batch_start_offset;
	अगर (unlikely(eb->batch_len == 0)) अणु /* impossible! */
		drm_dbg(&i915->drm, "Invalid batch length\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;

err:
	eb->vma[i].vma = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक eb_validate_vmas(काष्ठा i915_execbuffer *eb)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	INIT_LIST_HEAD(&eb->unbound);

	क्रम (i = 0; i < eb->buffer_count; i++) अणु
		काष्ठा drm_i915_gem_exec_object2 *entry = &eb->exec[i];
		काष्ठा eb_vma *ev = &eb->vma[i];
		काष्ठा i915_vma *vma = ev->vma;

		err = i915_gem_object_lock(vma->obj, &eb->ww);
		अगर (err)
			वापस err;

		err = eb_pin_vma(eb, entry, ev);
		अगर (err == -EDEADLK)
			वापस err;

		अगर (!err) अणु
			अगर (entry->offset != vma->node.start) अणु
				entry->offset = vma->node.start | UPDATE;
				eb->args->flags |= __EXEC_HAS_RELOC;
			पूर्ण
		पूर्ण अन्यथा अणु
			eb_unreserve_vma(ev);

			list_add_tail(&ev->bind_link, &eb->unbound);
			अगर (drm_mm_node_allocated(&vma->node)) अणु
				err = i915_vma_unbind(vma);
				अगर (err)
					वापस err;
			पूर्ण
		पूर्ण

		अगर (!(ev->flags & EXEC_OBJECT_WRITE)) अणु
			err = dma_resv_reserve_shared(vma->resv, 1);
			अगर (err)
				वापस err;
		पूर्ण

		GEM_BUG_ON(drm_mm_node_allocated(&vma->node) &&
			   eb_vma_misplaced(&eb->exec[i], vma, ev->flags));
	पूर्ण

	अगर (!list_empty(&eb->unbound))
		वापस eb_reserve(eb);

	वापस 0;
पूर्ण

अटल काष्ठा eb_vma *
eb_get_vma(स्थिर काष्ठा i915_execbuffer *eb, अचिन्हित दीर्घ handle)
अणु
	अगर (eb->lut_size < 0) अणु
		अगर (handle >= -eb->lut_size)
			वापस शून्य;
		वापस &eb->vma[handle];
	पूर्ण अन्यथा अणु
		काष्ठा hlist_head *head;
		काष्ठा eb_vma *ev;

		head = &eb->buckets[hash_32(handle, eb->lut_size)];
		hlist_क्रम_each_entry(ev, head, node) अणु
			अगर (ev->handle == handle)
				वापस ev;
		पूर्ण
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम eb_release_vmas(काष्ठा i915_execbuffer *eb, bool final, bool release_userptr)
अणु
	स्थिर अचिन्हित पूर्णांक count = eb->buffer_count;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा eb_vma *ev = &eb->vma[i];
		काष्ठा i915_vma *vma = ev->vma;

		अगर (!vma)
			अवरोध;

		eb_unreserve_vma(ev);

		अगर (release_userptr && ev->flags & __EXEC_OBJECT_USERPTR_INIT) अणु
			ev->flags &= ~__EXEC_OBJECT_USERPTR_INIT;
			i915_gem_object_userptr_submit_fini(vma->obj);
		पूर्ण

		अगर (final)
			i915_vma_put(vma);
	पूर्ण

	eb_unpin_engine(eb);
पूर्ण

अटल व्योम eb_destroy(स्थिर काष्ठा i915_execbuffer *eb)
अणु
	GEM_BUG_ON(eb->reloc_cache.rq);

	अगर (eb->lut_size > 0)
		kमुक्त(eb->buckets);
पूर्ण

अटल अंतरभूत u64
relocation_target(स्थिर काष्ठा drm_i915_gem_relocation_entry *reloc,
		  स्थिर काष्ठा i915_vma *target)
अणु
	वापस gen8_canonical_addr((पूर्णांक)reloc->delta + target->node.start);
पूर्ण

अटल व्योम reloc_cache_clear(काष्ठा reloc_cache *cache)
अणु
	cache->rq = शून्य;
	cache->rq_cmd = शून्य;
	cache->pool = शून्य;
	cache->rq_size = 0;
पूर्ण

अटल व्योम reloc_cache_init(काष्ठा reloc_cache *cache,
			     काष्ठा drm_i915_निजी *i915)
अणु
	cache->page = -1;
	cache->vaddr = 0;
	/* Must be a variable in the काष्ठा to allow GCC to unroll. */
	cache->gen = INTEL_GEN(i915);
	cache->has_llc = HAS_LLC(i915);
	cache->use_64bit_reloc = HAS_64BIT_RELOC(i915);
	cache->has_fence = cache->gen < 4;
	cache->needs_unfenced = INTEL_INFO(i915)->unfenced_needs_alignment;
	cache->node.flags = 0;
	reloc_cache_clear(cache);
पूर्ण

अटल अंतरभूत व्योम *unmask_page(अचिन्हित दीर्घ p)
अणु
	वापस (व्योम *)(uपूर्णांकptr_t)(p & PAGE_MASK);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक unmask_flags(अचिन्हित दीर्घ p)
अणु
	वापस p & ~PAGE_MASK;
पूर्ण

#घोषणा KMAP 0x4 /* after CLFLUSH_FLAGS */

अटल अंतरभूत काष्ठा i915_ggtt *cache_to_ggtt(काष्ठा reloc_cache *cache)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(cache, काष्ठा i915_execbuffer, reloc_cache)->i915;
	वापस &i915->ggtt;
पूर्ण

अटल व्योम reloc_cache_put_pool(काष्ठा i915_execbuffer *eb, काष्ठा reloc_cache *cache)
अणु
	अगर (!cache->pool)
		वापस;

	/*
	 * This is a bit nasty, normally we keep objects locked until the end
	 * of execbuffer, but we alपढ़ोy submit this, and have to unlock beक्रमe
	 * dropping the reference. Fortunately we can only hold 1 pool node at
	 * a समय, so this should be harmless.
	 */
	i915_gem_ww_unlock_single(cache->pool->obj);
	पूर्णांकel_gt_buffer_pool_put(cache->pool);
	cache->pool = शून्य;
पूर्ण

अटल व्योम reloc_gpu_flush(काष्ठा i915_execbuffer *eb, काष्ठा reloc_cache *cache)
अणु
	काष्ठा drm_i915_gem_object *obj = cache->rq->batch->obj;

	GEM_BUG_ON(cache->rq_size >= obj->base.size / माप(u32));
	cache->rq_cmd[cache->rq_size] = MI_BATCH_BUFFER_END;

	i915_gem_object_flush_map(obj);
	i915_gem_object_unpin_map(obj);

	पूर्णांकel_gt_chipset_flush(cache->rq->engine->gt);

	i915_request_add(cache->rq);
	reloc_cache_put_pool(eb, cache);
	reloc_cache_clear(cache);

	eb->reloc_pool = शून्य;
पूर्ण

अटल व्योम reloc_cache_reset(काष्ठा reloc_cache *cache, काष्ठा i915_execbuffer *eb)
अणु
	व्योम *vaddr;

	अगर (cache->rq)
		reloc_gpu_flush(eb, cache);

	अगर (!cache->vaddr)
		वापस;

	vaddr = unmask_page(cache->vaddr);
	अगर (cache->vaddr & KMAP) अणु
		काष्ठा drm_i915_gem_object *obj =
			(काष्ठा drm_i915_gem_object *)cache->node.mm;
		अगर (cache->vaddr & CLFLUSH_AFTER)
			mb();

		kunmap_atomic(vaddr);
		i915_gem_object_finish_access(obj);
	पूर्ण अन्यथा अणु
		काष्ठा i915_ggtt *ggtt = cache_to_ggtt(cache);

		पूर्णांकel_gt_flush_ggtt_ग_लिखोs(ggtt->vm.gt);
		io_mapping_unmap_atomic((व्योम __iomem *)vaddr);

		अगर (drm_mm_node_allocated(&cache->node)) अणु
			ggtt->vm.clear_range(&ggtt->vm,
					     cache->node.start,
					     cache->node.size);
			mutex_lock(&ggtt->vm.mutex);
			drm_mm_हटाओ_node(&cache->node);
			mutex_unlock(&ggtt->vm.mutex);
		पूर्ण अन्यथा अणु
			i915_vma_unpin((काष्ठा i915_vma *)cache->node.mm);
		पूर्ण
	पूर्ण

	cache->vaddr = 0;
	cache->page = -1;
पूर्ण

अटल व्योम *reloc_kmap(काष्ठा drm_i915_gem_object *obj,
			काष्ठा reloc_cache *cache,
			अचिन्हित दीर्घ pageno)
अणु
	व्योम *vaddr;
	काष्ठा page *page;

	अगर (cache->vaddr) अणु
		kunmap_atomic(unmask_page(cache->vaddr));
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक flushes;
		पूर्णांक err;

		err = i915_gem_object_prepare_ग_लिखो(obj, &flushes);
		अगर (err)
			वापस ERR_PTR(err);

		BUILD_BUG_ON(KMAP & CLFLUSH_FLAGS);
		BUILD_BUG_ON((KMAP | CLFLUSH_FLAGS) & PAGE_MASK);

		cache->vaddr = flushes | KMAP;
		cache->node.mm = (व्योम *)obj;
		अगर (flushes)
			mb();
	पूर्ण

	page = i915_gem_object_get_page(obj, pageno);
	अगर (!obj->mm.dirty)
		set_page_dirty(page);

	vaddr = kmap_atomic(page);
	cache->vaddr = unmask_flags(cache->vaddr) | (अचिन्हित दीर्घ)vaddr;
	cache->page = pageno;

	वापस vaddr;
पूर्ण

अटल व्योम *reloc_iomap(काष्ठा drm_i915_gem_object *obj,
			 काष्ठा i915_execbuffer *eb,
			 अचिन्हित दीर्घ page)
अणु
	काष्ठा reloc_cache *cache = &eb->reloc_cache;
	काष्ठा i915_ggtt *ggtt = cache_to_ggtt(cache);
	अचिन्हित दीर्घ offset;
	व्योम *vaddr;

	अगर (cache->vaddr) अणु
		पूर्णांकel_gt_flush_ggtt_ग_लिखोs(ggtt->vm.gt);
		io_mapping_unmap_atomic((व्योम __क्रमce __iomem *) unmask_page(cache->vaddr));
	पूर्ण अन्यथा अणु
		काष्ठा i915_vma *vma;
		पूर्णांक err;

		अगर (i915_gem_object_is_tiled(obj))
			वापस ERR_PTR(-EINVAL);

		अगर (use_cpu_reloc(cache, obj))
			वापस शून्य;

		err = i915_gem_object_set_to_gtt_करोमुख्य(obj, true);
		अगर (err)
			वापस ERR_PTR(err);

		vma = i915_gem_object_ggtt_pin_ww(obj, &eb->ww, शून्य, 0, 0,
						  PIN_MAPPABLE |
						  PIN_NONBLOCK /* NOWARN */ |
						  PIN_NOEVICT);
		अगर (vma == ERR_PTR(-EDEADLK))
			वापस vma;

		अगर (IS_ERR(vma)) अणु
			स_रखो(&cache->node, 0, माप(cache->node));
			mutex_lock(&ggtt->vm.mutex);
			err = drm_mm_insert_node_in_range
				(&ggtt->vm.mm, &cache->node,
				 PAGE_SIZE, 0, I915_COLOR_UNEVICTABLE,
				 0, ggtt->mappable_end,
				 DRM_MM_INSERT_LOW);
			mutex_unlock(&ggtt->vm.mutex);
			अगर (err) /* no inactive aperture space, use cpu reloc */
				वापस शून्य;
		पूर्ण अन्यथा अणु
			cache->node.start = vma->node.start;
			cache->node.mm = (व्योम *)vma;
		पूर्ण
	पूर्ण

	offset = cache->node.start;
	अगर (drm_mm_node_allocated(&cache->node)) अणु
		ggtt->vm.insert_page(&ggtt->vm,
				     i915_gem_object_get_dma_address(obj, page),
				     offset, I915_CACHE_NONE, 0);
	पूर्ण अन्यथा अणु
		offset += page << PAGE_SHIFT;
	पूर्ण

	vaddr = (व्योम __क्रमce *)io_mapping_map_atomic_wc(&ggtt->iomap,
							 offset);
	cache->page = page;
	cache->vaddr = (अचिन्हित दीर्घ)vaddr;

	वापस vaddr;
पूर्ण

अटल व्योम *reloc_vaddr(काष्ठा drm_i915_gem_object *obj,
			 काष्ठा i915_execbuffer *eb,
			 अचिन्हित दीर्घ page)
अणु
	काष्ठा reloc_cache *cache = &eb->reloc_cache;
	व्योम *vaddr;

	अगर (cache->page == page) अणु
		vaddr = unmask_page(cache->vaddr);
	पूर्ण अन्यथा अणु
		vaddr = शून्य;
		अगर ((cache->vaddr & KMAP) == 0)
			vaddr = reloc_iomap(obj, eb, page);
		अगर (!vaddr)
			vaddr = reloc_kmap(obj, cache, page);
	पूर्ण

	वापस vaddr;
पूर्ण

अटल व्योम clflush_ग_लिखो32(u32 *addr, u32 value, अचिन्हित पूर्णांक flushes)
अणु
	अगर (unlikely(flushes & (CLFLUSH_BEFORE | CLFLUSH_AFTER))) अणु
		अगर (flushes & CLFLUSH_BEFORE) अणु
			clflushopt(addr);
			mb();
		पूर्ण

		*addr = value;

		/*
		 * Writes to the same cacheline are serialised by the CPU
		 * (including clflush). On the ग_लिखो path, we only require
		 * that it hits memory in an orderly fashion and place
		 * mb barriers at the start and end of the relocation phase
		 * to ensure ordering of clflush wrt to the प्रणाली.
		 */
		अगर (flushes & CLFLUSH_AFTER)
			clflushopt(addr);
	पूर्ण अन्यथा
		*addr = value;
पूर्ण

अटल पूर्णांक reloc_move_to_gpu(काष्ठा i915_request *rq, काष्ठा i915_vma *vma)
अणु
	काष्ठा drm_i915_gem_object *obj = vma->obj;
	पूर्णांक err;

	निश्चित_vma_held(vma);

	अगर (obj->cache_dirty & ~obj->cache_coherent)
		i915_gem_clflush_object(obj, 0);
	obj->ग_लिखो_करोमुख्य = 0;

	err = i915_request_aरुको_object(rq, vma->obj, true);
	अगर (err == 0)
		err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);

	वापस err;
पूर्ण

अटल पूर्णांक __reloc_gpu_alloc(काष्ठा i915_execbuffer *eb,
			     काष्ठा पूर्णांकel_engine_cs *engine,
			     काष्ठा i915_vma *vma,
			     अचिन्हित पूर्णांक len)
अणु
	काष्ठा reloc_cache *cache = &eb->reloc_cache;
	काष्ठा पूर्णांकel_gt_buffer_pool_node *pool = eb->reloc_pool;
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *batch;
	u32 *cmd;
	पूर्णांक err;

	अगर (!pool) अणु
		pool = पूर्णांकel_gt_get_buffer_pool(engine->gt, PAGE_SIZE,
						cache->has_llc ?
						I915_MAP_WB :
						I915_MAP_WC);
		अगर (IS_ERR(pool))
			वापस PTR_ERR(pool);
	पूर्ण
	eb->reloc_pool = शून्य;

	err = i915_gem_object_lock(pool->obj, &eb->ww);
	अगर (err)
		जाओ err_pool;

	cmd = i915_gem_object_pin_map(pool->obj, pool->type);
	अगर (IS_ERR(cmd)) अणु
		err = PTR_ERR(cmd);
		जाओ err_pool;
	पूर्ण
	पूर्णांकel_gt_buffer_pool_mark_used(pool);

	स_रखो32(cmd, 0, pool->obj->base.size / माप(u32));

	batch = i915_vma_instance(pool->obj, vma->vm, शून्य);
	अगर (IS_ERR(batch)) अणु
		err = PTR_ERR(batch);
		जाओ err_unmap;
	पूर्ण

	err = i915_vma_pin_ww(batch, &eb->ww, 0, 0, PIN_USER | PIN_NONBLOCK);
	अगर (err)
		जाओ err_unmap;

	अगर (engine == eb->context->engine) अणु
		rq = i915_request_create(eb->context);
	पूर्ण अन्यथा अणु
		काष्ठा पूर्णांकel_context *ce = eb->reloc_context;

		अगर (!ce) अणु
			ce = पूर्णांकel_context_create(engine);
			अगर (IS_ERR(ce)) अणु
				err = PTR_ERR(ce);
				जाओ err_unpin;
			पूर्ण

			i915_vm_put(ce->vm);
			ce->vm = i915_vm_get(eb->context->vm);
			eb->reloc_context = ce;
		पूर्ण

		err = पूर्णांकel_context_pin_ww(ce, &eb->ww);
		अगर (err)
			जाओ err_unpin;

		rq = i915_request_create(ce);
		पूर्णांकel_context_unpin(ce);
	पूर्ण
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_unpin;
	पूर्ण

	err = पूर्णांकel_gt_buffer_pool_mark_active(pool, rq);
	अगर (err)
		जाओ err_request;

	err = reloc_move_to_gpu(rq, vma);
	अगर (err)
		जाओ err_request;

	err = eb->engine->emit_bb_start(rq,
					batch->node.start, PAGE_SIZE,
					cache->gen > 5 ? 0 : I915_DISPATCH_SECURE);
	अगर (err)
		जाओ skip_request;

	निश्चित_vma_held(batch);
	err = i915_request_aरुको_object(rq, batch->obj, false);
	अगर (err == 0)
		err = i915_vma_move_to_active(batch, rq, 0);
	अगर (err)
		जाओ skip_request;

	rq->batch = batch;
	i915_vma_unpin(batch);

	cache->rq = rq;
	cache->rq_cmd = cmd;
	cache->rq_size = 0;
	cache->pool = pool;

	/* Return with batch mapping (cmd) still pinned */
	वापस 0;

skip_request:
	i915_request_set_error_once(rq, err);
err_request:
	i915_request_add(rq);
err_unpin:
	i915_vma_unpin(batch);
err_unmap:
	i915_gem_object_unpin_map(pool->obj);
err_pool:
	eb->reloc_pool = pool;
	वापस err;
पूर्ण

अटल bool reloc_can_use_engine(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस engine->class != VIDEO_DECODE_CLASS || !IS_GEN(engine->i915, 6);
पूर्ण

अटल u32 *reloc_gpu(काष्ठा i915_execbuffer *eb,
		      काष्ठा i915_vma *vma,
		      अचिन्हित पूर्णांक len)
अणु
	काष्ठा reloc_cache *cache = &eb->reloc_cache;
	u32 *cmd;

	अगर (cache->rq_size > PAGE_SIZE/माप(u32) - (len + 1))
		reloc_gpu_flush(eb, cache);

	अगर (unlikely(!cache->rq)) अणु
		पूर्णांक err;
		काष्ठा पूर्णांकel_engine_cs *engine = eb->engine;

		अगर (!reloc_can_use_engine(engine)) अणु
			engine = engine->gt->engine_class[COPY_ENGINE_CLASS][0];
			अगर (!engine)
				वापस ERR_PTR(-ENODEV);
		पूर्ण

		err = __reloc_gpu_alloc(eb, engine, vma, len);
		अगर (unlikely(err))
			वापस ERR_PTR(err);
	पूर्ण

	cmd = cache->rq_cmd + cache->rq_size;
	cache->rq_size += len;

	वापस cmd;
पूर्ण

अटल अंतरभूत bool use_reloc_gpu(काष्ठा i915_vma *vma)
अणु
	अगर (DBG_FORCE_RELOC == FORCE_GPU_RELOC)
		वापस true;

	अगर (DBG_FORCE_RELOC)
		वापस false;

	वापस !dma_resv_test_संकेतed_rcu(vma->resv, true);
पूर्ण

अटल अचिन्हित दीर्घ vma_phys_addr(काष्ठा i915_vma *vma, u32 offset)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ addr;

	GEM_BUG_ON(vma->pages != vma->obj->mm.pages);

	page = i915_gem_object_get_page(vma->obj, offset >> PAGE_SHIFT);
	addr = PFN_PHYS(page_to_pfn(page));
	GEM_BUG_ON(overflows_type(addr, u32)); /* expected dma32 */

	वापस addr + offset_in_page(offset);
पूर्ण

अटल पूर्णांक __reloc_entry_gpu(काष्ठा i915_execbuffer *eb,
			      काष्ठा i915_vma *vma,
			      u64 offset,
			      u64 target_addr)
अणु
	स्थिर अचिन्हित पूर्णांक gen = eb->reloc_cache.gen;
	अचिन्हित पूर्णांक len;
	u32 *batch;
	u64 addr;

	अगर (gen >= 8)
		len = offset & 7 ? 8 : 5;
	अन्यथा अगर (gen >= 4)
		len = 4;
	अन्यथा
		len = 3;

	batch = reloc_gpu(eb, vma, len);
	अगर (batch == ERR_PTR(-EDEADLK))
		वापस -EDEADLK;
	अन्यथा अगर (IS_ERR(batch))
		वापस false;

	addr = gen8_canonical_addr(vma->node.start + offset);
	अगर (gen >= 8) अणु
		अगर (offset & 7) अणु
			*batch++ = MI_STORE_DWORD_IMM_GEN4;
			*batch++ = lower_32_bits(addr);
			*batch++ = upper_32_bits(addr);
			*batch++ = lower_32_bits(target_addr);

			addr = gen8_canonical_addr(addr + 4);

			*batch++ = MI_STORE_DWORD_IMM_GEN4;
			*batch++ = lower_32_bits(addr);
			*batch++ = upper_32_bits(addr);
			*batch++ = upper_32_bits(target_addr);
		पूर्ण अन्यथा अणु
			*batch++ = (MI_STORE_DWORD_IMM_GEN4 | (1 << 21)) + 1;
			*batch++ = lower_32_bits(addr);
			*batch++ = upper_32_bits(addr);
			*batch++ = lower_32_bits(target_addr);
			*batch++ = upper_32_bits(target_addr);
		पूर्ण
	पूर्ण अन्यथा अगर (gen >= 6) अणु
		*batch++ = MI_STORE_DWORD_IMM_GEN4;
		*batch++ = 0;
		*batch++ = addr;
		*batch++ = target_addr;
	पूर्ण अन्यथा अगर (IS_I965G(eb->i915)) अणु
		*batch++ = MI_STORE_DWORD_IMM_GEN4;
		*batch++ = 0;
		*batch++ = vma_phys_addr(vma, offset);
		*batch++ = target_addr;
	पूर्ण अन्यथा अगर (gen >= 4) अणु
		*batch++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
		*batch++ = 0;
		*batch++ = addr;
		*batch++ = target_addr;
	पूर्ण अन्यथा अगर (gen >= 3 &&
		   !(IS_I915G(eb->i915) || IS_I915GM(eb->i915))) अणु
		*batch++ = MI_STORE_DWORD_IMM | MI_MEM_VIRTUAL;
		*batch++ = addr;
		*batch++ = target_addr;
	पूर्ण अन्यथा अणु
		*batch++ = MI_STORE_DWORD_IMM;
		*batch++ = vma_phys_addr(vma, offset);
		*batch++ = target_addr;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक reloc_entry_gpu(काष्ठा i915_execbuffer *eb,
			    काष्ठा i915_vma *vma,
			    u64 offset,
			    u64 target_addr)
अणु
	अगर (eb->reloc_cache.vaddr)
		वापस false;

	अगर (!use_reloc_gpu(vma))
		वापस false;

	वापस __reloc_entry_gpu(eb, vma, offset, target_addr);
पूर्ण

अटल u64
relocate_entry(काष्ठा i915_vma *vma,
	       स्थिर काष्ठा drm_i915_gem_relocation_entry *reloc,
	       काष्ठा i915_execbuffer *eb,
	       स्थिर काष्ठा i915_vma *target)
अणु
	u64 target_addr = relocation_target(reloc, target);
	u64 offset = reloc->offset;
	पूर्णांक reloc_gpu = reloc_entry_gpu(eb, vma, offset, target_addr);

	अगर (reloc_gpu < 0)
		वापस reloc_gpu;

	अगर (!reloc_gpu) अणु
		bool wide = eb->reloc_cache.use_64bit_reloc;
		व्योम *vaddr;

repeat:
		vaddr = reloc_vaddr(vma->obj, eb,
				    offset >> PAGE_SHIFT);
		अगर (IS_ERR(vaddr))
			वापस PTR_ERR(vaddr);

		GEM_BUG_ON(!IS_ALIGNED(offset, माप(u32)));
		clflush_ग_लिखो32(vaddr + offset_in_page(offset),
				lower_32_bits(target_addr),
				eb->reloc_cache.vaddr);

		अगर (wide) अणु
			offset += माप(u32);
			target_addr >>= 32;
			wide = false;
			जाओ repeat;
		पूर्ण
	पूर्ण

	वापस target->node.start | UPDATE;
पूर्ण

अटल u64
eb_relocate_entry(काष्ठा i915_execbuffer *eb,
		  काष्ठा eb_vma *ev,
		  स्थिर काष्ठा drm_i915_gem_relocation_entry *reloc)
अणु
	काष्ठा drm_i915_निजी *i915 = eb->i915;
	काष्ठा eb_vma *target;
	पूर्णांक err;

	/* we've alपढ़ोy hold a reference to all valid objects */
	target = eb_get_vma(eb, reloc->target_handle);
	अगर (unlikely(!target))
		वापस -ENOENT;

	/* Validate that the target is in a valid r/w GPU करोमुख्य */
	अगर (unlikely(reloc->ग_लिखो_करोमुख्य & (reloc->ग_लिखो_करोमुख्य - 1))) अणु
		drm_dbg(&i915->drm, "reloc with multiple write domains: "
			  "target %d offset %d "
			  "read %08x write %08x",
			  reloc->target_handle,
			  (पूर्णांक) reloc->offset,
			  reloc->पढ़ो_करोमुख्यs,
			  reloc->ग_लिखो_करोमुख्य);
		वापस -EINVAL;
	पूर्ण
	अगर (unlikely((reloc->ग_लिखो_करोमुख्य | reloc->पढ़ो_करोमुख्यs)
		     & ~I915_GEM_GPU_DOMAINS)) अणु
		drm_dbg(&i915->drm, "reloc with read/write non-GPU domains: "
			  "target %d offset %d "
			  "read %08x write %08x",
			  reloc->target_handle,
			  (पूर्णांक) reloc->offset,
			  reloc->पढ़ो_करोमुख्यs,
			  reloc->ग_लिखो_करोमुख्य);
		वापस -EINVAL;
	पूर्ण

	अगर (reloc->ग_लिखो_करोमुख्य) अणु
		target->flags |= EXEC_OBJECT_WRITE;

		/*
		 * Sandybridge PPGTT errata: We need a global gtt mapping
		 * क्रम MI and pipe_control ग_लिखोs because the gpu करोesn't
		 * properly redirect them through the ppgtt क्रम non_secure
		 * batchbuffers.
		 */
		अगर (reloc->ग_लिखो_करोमुख्य == I915_GEM_DOMAIN_INSTRUCTION &&
		    IS_GEN(eb->i915, 6)) अणु
			err = i915_vma_bind(target->vma,
					    target->vma->obj->cache_level,
					    PIN_GLOBAL, शून्य);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	/*
	 * If the relocation alपढ़ोy has the right value in it, no
	 * more work needs to be करोne.
	 */
	अगर (!DBG_FORCE_RELOC &&
	    gen8_canonical_addr(target->vma->node.start) == reloc->presumed_offset)
		वापस 0;

	/* Check that the relocation address is valid... */
	अगर (unlikely(reloc->offset >
		     ev->vma->size - (eb->reloc_cache.use_64bit_reloc ? 8 : 4))) अणु
		drm_dbg(&i915->drm, "Relocation beyond object bounds: "
			  "target %d offset %d size %d.\n",
			  reloc->target_handle,
			  (पूर्णांक)reloc->offset,
			  (पूर्णांक)ev->vma->size);
		वापस -EINVAL;
	पूर्ण
	अगर (unlikely(reloc->offset & 3)) अणु
		drm_dbg(&i915->drm, "Relocation not 4-byte aligned: "
			  "target %d offset %d.\n",
			  reloc->target_handle,
			  (पूर्णांक)reloc->offset);
		वापस -EINVAL;
	पूर्ण

	/*
	 * If we ग_लिखो पूर्णांकo the object, we need to क्रमce the synchronisation
	 * barrier, either with an asynchronous clflush or अगर we executed the
	 * patching using the GPU (though that should be serialised by the
	 * समयline). To be completely sure, and since we are required to
	 * करो relocations we are alपढ़ोy stalling, disable the user's opt
	 * out of our synchronisation.
	 */
	ev->flags &= ~EXEC_OBJECT_ASYNC;

	/* and update the user's relocation entry */
	वापस relocate_entry(ev->vma, reloc, eb, target->vma);
पूर्ण

अटल पूर्णांक eb_relocate_vma(काष्ठा i915_execbuffer *eb, काष्ठा eb_vma *ev)
अणु
#घोषणा N_RELOC(x) ((x) / माप(काष्ठा drm_i915_gem_relocation_entry))
	काष्ठा drm_i915_gem_relocation_entry stack[N_RELOC(512)];
	स्थिर काष्ठा drm_i915_gem_exec_object2 *entry = ev->exec;
	काष्ठा drm_i915_gem_relocation_entry __user *urelocs =
		u64_to_user_ptr(entry->relocs_ptr);
	अचिन्हित दीर्घ reमुख्य = entry->relocation_count;

	अगर (unlikely(reमुख्य > N_RELOC(अच_दीर्घ_उच्च)))
		वापस -EINVAL;

	/*
	 * We must check that the entire relocation array is safe
	 * to पढ़ो. However, अगर the array is not writable the user loses
	 * the updated relocation values.
	 */
	अगर (unlikely(!access_ok(urelocs, reमुख्य * माप(*urelocs))))
		वापस -EFAULT;

	करो अणु
		काष्ठा drm_i915_gem_relocation_entry *r = stack;
		अचिन्हित पूर्णांक count =
			min_t(अचिन्हित दीर्घ, reमुख्य, ARRAY_SIZE(stack));
		अचिन्हित पूर्णांक copied;

		/*
		 * This is the fast path and we cannot handle a pagefault
		 * whilst holding the काष्ठा mutex lest the user pass in the
		 * relocations contained within a mmaped bo. For in such a हाल
		 * we, the page fault handler would call i915_gem_fault() and
		 * we would try to acquire the काष्ठा mutex again. Obviously
		 * this is bad and so lockdep complains vehemently.
		 */
		pagefault_disable();
		copied = __copy_from_user_inatomic(r, urelocs, count * माप(r[0]));
		pagefault_enable();
		अगर (unlikely(copied)) अणु
			reमुख्य = -EFAULT;
			जाओ out;
		पूर्ण

		reमुख्य -= count;
		करो अणु
			u64 offset = eb_relocate_entry(eb, ev, r);

			अगर (likely(offset == 0)) अणु
			पूर्ण अन्यथा अगर ((s64)offset < 0) अणु
				reमुख्य = (पूर्णांक)offset;
				जाओ out;
			पूर्ण अन्यथा अणु
				/*
				 * Note that reporting an error now
				 * leaves everything in an inconsistent
				 * state as we have *alपढ़ोy* changed
				 * the relocation value inside the
				 * object. As we have not changed the
				 * reloc.presumed_offset or will not
				 * change the execobject.offset, on the
				 * call we may not reग_लिखो the value
				 * inside the object, leaving it
				 * dangling and causing a GPU hang. Unless
				 * userspace dynamically rebuilds the
				 * relocations on each execbuf rather than
				 * presume a अटल tree.
				 *
				 * We did previously check अगर the relocations
				 * were writable (access_ok), an error now
				 * would be a strange race with mprotect,
				 * having alपढ़ोy demonstrated that we
				 * can पढ़ो from this userspace address.
				 */
				offset = gen8_canonical_addr(offset & ~UPDATE);
				__put_user(offset,
					   &urelocs[r - stack].presumed_offset);
			पूर्ण
		पूर्ण जबतक (r++, --count);
		urelocs += ARRAY_SIZE(stack);
	पूर्ण जबतक (reमुख्य);
out:
	reloc_cache_reset(&eb->reloc_cache, eb);
	वापस reमुख्य;
पूर्ण

अटल पूर्णांक
eb_relocate_vma_slow(काष्ठा i915_execbuffer *eb, काष्ठा eb_vma *ev)
अणु
	स्थिर काष्ठा drm_i915_gem_exec_object2 *entry = ev->exec;
	काष्ठा drm_i915_gem_relocation_entry *relocs =
		u64_to_ptr(typeof(*relocs), entry->relocs_ptr);
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < entry->relocation_count; i++) अणु
		u64 offset = eb_relocate_entry(eb, ev, &relocs[i]);

		अगर ((s64)offset < 0) अणु
			err = (पूर्णांक)offset;
			जाओ err;
		पूर्ण
	पूर्ण
	err = 0;
err:
	reloc_cache_reset(&eb->reloc_cache, eb);
	वापस err;
पूर्ण

अटल पूर्णांक check_relocations(स्थिर काष्ठा drm_i915_gem_exec_object2 *entry)
अणु
	स्थिर अक्षर __user *addr, *end;
	अचिन्हित दीर्घ size;
	अक्षर __maybe_unused c;

	size = entry->relocation_count;
	अगर (size == 0)
		वापस 0;

	अगर (size > N_RELOC(अच_दीर्घ_उच्च))
		वापस -EINVAL;

	addr = u64_to_user_ptr(entry->relocs_ptr);
	size *= माप(काष्ठा drm_i915_gem_relocation_entry);
	अगर (!access_ok(addr, size))
		वापस -EFAULT;

	end = addr + size;
	क्रम (; addr < end; addr += PAGE_SIZE) अणु
		पूर्णांक err = __get_user(c, addr);
		अगर (err)
			वापस err;
	पूर्ण
	वापस __get_user(c, end - 1);
पूर्ण

अटल पूर्णांक eb_copy_relocations(स्थिर काष्ठा i915_execbuffer *eb)
अणु
	काष्ठा drm_i915_gem_relocation_entry *relocs;
	स्थिर अचिन्हित पूर्णांक count = eb->buffer_count;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < count; i++) अणु
		स्थिर अचिन्हित पूर्णांक nreloc = eb->exec[i].relocation_count;
		काष्ठा drm_i915_gem_relocation_entry __user *urelocs;
		अचिन्हित दीर्घ size;
		अचिन्हित दीर्घ copied;

		अगर (nreloc == 0)
			जारी;

		err = check_relocations(&eb->exec[i]);
		अगर (err)
			जाओ err;

		urelocs = u64_to_user_ptr(eb->exec[i].relocs_ptr);
		size = nreloc * माप(*relocs);

		relocs = kvदो_स्मृति_array(size, 1, GFP_KERNEL);
		अगर (!relocs) अणु
			err = -ENOMEM;
			जाओ err;
		पूर्ण

		/* copy_from_user is limited to < 4GiB */
		copied = 0;
		करो अणु
			अचिन्हित पूर्णांक len =
				min_t(u64, BIT_ULL(31), size - copied);

			अगर (__copy_from_user((अक्षर *)relocs + copied,
					     (अक्षर __user *)urelocs + copied,
					     len))
				जाओ end;

			copied += len;
		पूर्ण जबतक (copied < size);

		/*
		 * As we करो not update the known relocation offsets after
		 * relocating (due to the complनिकासies in lock handling),
		 * we need to mark them as invalid now so that we क्रमce the
		 * relocation processing next समय. Just in हाल the target
		 * object is evicted and then rebound पूर्णांकo its old
		 * presumed_offset beक्रमe the next execbuffer - अगर that
		 * happened we would make the mistake of assuming that the
		 * relocations were valid.
		 */
		अगर (!user_access_begin(urelocs, size))
			जाओ end;

		क्रम (copied = 0; copied < nreloc; copied++)
			unsafe_put_user(-1,
					&urelocs[copied].presumed_offset,
					end_user);
		user_access_end();

		eb->exec[i].relocs_ptr = (uपूर्णांकptr_t)relocs;
	पूर्ण

	वापस 0;

end_user:
	user_access_end();
end:
	kvमुक्त(relocs);
	err = -EFAULT;
err:
	जबतक (i--) अणु
		relocs = u64_to_ptr(typeof(*relocs), eb->exec[i].relocs_ptr);
		अगर (eb->exec[i].relocation_count)
			kvमुक्त(relocs);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक eb_prefault_relocations(स्थिर काष्ठा i915_execbuffer *eb)
अणु
	स्थिर अचिन्हित पूर्णांक count = eb->buffer_count;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक err;

		err = check_relocations(&eb->exec[i]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक eb_reinit_userptr(काष्ठा i915_execbuffer *eb)
अणु
	स्थिर अचिन्हित पूर्णांक count = eb->buffer_count;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (likely(!(eb->args->flags & __EXEC_USERPTR_USED)))
		वापस 0;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा eb_vma *ev = &eb->vma[i];

		अगर (!i915_gem_object_is_userptr(ev->vma->obj))
			जारी;

		ret = i915_gem_object_userptr_submit_init(ev->vma->obj);
		अगर (ret)
			वापस ret;

		ev->flags |= __EXEC_OBJECT_USERPTR_INIT;
	पूर्ण

	वापस 0;
पूर्ण

अटल noअंतरभूत पूर्णांक eb_relocate_parse_slow(काष्ठा i915_execbuffer *eb,
					   काष्ठा i915_request *rq)
अणु
	bool have_copy = false;
	काष्ठा eb_vma *ev;
	पूर्णांक err = 0;

repeat:
	अगर (संकेत_pending(current)) अणु
		err = -ERESTARTSYS;
		जाओ out;
	पूर्ण

	/* We may process another execbuffer during the unlock... */
	eb_release_vmas(eb, false, true);
	i915_gem_ww_ctx_fini(&eb->ww);

	अगर (rq) अणु
		/* nonblocking is always false */
		अगर (i915_request_रुको(rq, I915_WAIT_INTERRUPTIBLE,
				      MAX_SCHEDULE_TIMEOUT) < 0) अणु
			i915_request_put(rq);
			rq = शून्य;

			err = -EINTR;
			जाओ err_relock;
		पूर्ण

		i915_request_put(rq);
		rq = शून्य;
	पूर्ण

	/*
	 * We take 3 passes through the slowpatch.
	 *
	 * 1 - we try to just prefault all the user relocation entries and
	 * then attempt to reuse the atomic pagefault disabled fast path again.
	 *
	 * 2 - we copy the user entries to a local buffer here outside of the
	 * local and allow ourselves to रुको upon any rendering beक्रमe
	 * relocations
	 *
	 * 3 - we alपढ़ोy have a local copy of the relocation entries, but
	 * were पूर्णांकerrupted (EAGAIN) whilst रुकोing क्रम the objects, try again.
	 */
	अगर (!err) अणु
		err = eb_prefault_relocations(eb);
	पूर्ण अन्यथा अगर (!have_copy) अणु
		err = eb_copy_relocations(eb);
		have_copy = err == 0;
	पूर्ण अन्यथा अणु
		cond_resched();
		err = 0;
	पूर्ण

	अगर (!err)
		err = eb_reinit_userptr(eb);

err_relock:
	i915_gem_ww_ctx_init(&eb->ww, true);
	अगर (err)
		जाओ out;

	/* reacquire the objects */
repeat_validate:
	rq = eb_pin_engine(eb, false);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		rq = शून्य;
		जाओ err;
	पूर्ण

	/* We didn't throttle, should be शून्य */
	GEM_WARN_ON(rq);

	err = eb_validate_vmas(eb);
	अगर (err)
		जाओ err;

	GEM_BUG_ON(!eb->batch);

	list_क्रम_each_entry(ev, &eb->relocs, reloc_link) अणु
		अगर (!have_copy) अणु
			pagefault_disable();
			err = eb_relocate_vma(eb, ev);
			pagefault_enable();
			अगर (err)
				अवरोध;
		पूर्ण अन्यथा अणु
			err = eb_relocate_vma_slow(eb, ev);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (err == -EDEADLK)
		जाओ err;

	अगर (err && !have_copy)
		जाओ repeat;

	अगर (err)
		जाओ err;

	/* as last step, parse the command buffer */
	err = eb_parse(eb);
	अगर (err)
		जाओ err;

	/*
	 * Leave the user relocations as are, this is the painfully slow path,
	 * and we want to aव्योम the complication of dropping the lock whilst
	 * having buffers reserved in the aperture and so causing spurious
	 * ENOSPC क्रम अक्रमom operations.
	 */

err:
	अगर (err == -EDEADLK) अणु
		eb_release_vmas(eb, false, false);
		err = i915_gem_ww_ctx_backoff(&eb->ww);
		अगर (!err)
			जाओ repeat_validate;
	पूर्ण

	अगर (err == -EAGAIN)
		जाओ repeat;

out:
	अगर (have_copy) अणु
		स्थिर अचिन्हित पूर्णांक count = eb->buffer_count;
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < count; i++) अणु
			स्थिर काष्ठा drm_i915_gem_exec_object2 *entry =
				&eb->exec[i];
			काष्ठा drm_i915_gem_relocation_entry *relocs;

			अगर (!entry->relocation_count)
				जारी;

			relocs = u64_to_ptr(typeof(*relocs), entry->relocs_ptr);
			kvमुक्त(relocs);
		पूर्ण
	पूर्ण

	अगर (rq)
		i915_request_put(rq);

	वापस err;
पूर्ण

अटल पूर्णांक eb_relocate_parse(काष्ठा i915_execbuffer *eb)
अणु
	पूर्णांक err;
	काष्ठा i915_request *rq = शून्य;
	bool throttle = true;

retry:
	rq = eb_pin_engine(eb, throttle);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		rq = शून्य;
		अगर (err != -EDEADLK)
			वापस err;

		जाओ err;
	पूर्ण

	अगर (rq) अणु
		bool nonblock = eb->file->filp->f_flags & O_NONBLOCK;

		/* Need to drop all locks now क्रम throttling, take slowpath */
		err = i915_request_रुको(rq, I915_WAIT_INTERRUPTIBLE, 0);
		अगर (err == -ETIME) अणु
			अगर (nonblock) अणु
				err = -EWOULDBLOCK;
				i915_request_put(rq);
				जाओ err;
			पूर्ण
			जाओ slow;
		पूर्ण
		i915_request_put(rq);
		rq = शून्य;
	पूर्ण

	/* only throttle once, even अगर we didn't need to throttle */
	throttle = false;

	err = eb_validate_vmas(eb);
	अगर (err == -EAGAIN)
		जाओ slow;
	अन्यथा अगर (err)
		जाओ err;

	/* The objects are in their final locations, apply the relocations. */
	अगर (eb->args->flags & __EXEC_HAS_RELOC) अणु
		काष्ठा eb_vma *ev;

		list_क्रम_each_entry(ev, &eb->relocs, reloc_link) अणु
			err = eb_relocate_vma(eb, ev);
			अगर (err)
				अवरोध;
		पूर्ण

		अगर (err == -EDEADLK)
			जाओ err;
		अन्यथा अगर (err)
			जाओ slow;
	पूर्ण

	अगर (!err)
		err = eb_parse(eb);

err:
	अगर (err == -EDEADLK) अणु
		eb_release_vmas(eb, false, false);
		err = i915_gem_ww_ctx_backoff(&eb->ww);
		अगर (!err)
			जाओ retry;
	पूर्ण

	वापस err;

slow:
	err = eb_relocate_parse_slow(eb, rq);
	अगर (err)
		/*
		 * If the user expects the execobject.offset and
		 * reloc.presumed_offset to be an exact match,
		 * as क्रम using NO_RELOC, then we cannot update
		 * the execobject.offset until we have completed
		 * relocation.
		 */
		eb->args->flags &= ~__EXEC_HAS_RELOC;

	वापस err;
पूर्ण

अटल पूर्णांक eb_move_to_gpu(काष्ठा i915_execbuffer *eb)
अणु
	स्थिर अचिन्हित पूर्णांक count = eb->buffer_count;
	अचिन्हित पूर्णांक i = count;
	पूर्णांक err = 0;

	जबतक (i--) अणु
		काष्ठा eb_vma *ev = &eb->vma[i];
		काष्ठा i915_vma *vma = ev->vma;
		अचिन्हित पूर्णांक flags = ev->flags;
		काष्ठा drm_i915_gem_object *obj = vma->obj;

		निश्चित_vma_held(vma);

		अगर (flags & EXEC_OBJECT_CAPTURE) अणु
			काष्ठा i915_capture_list *capture;

			capture = kदो_स्मृति(माप(*capture), GFP_KERNEL);
			अगर (capture) अणु
				capture->next = eb->request->capture_list;
				capture->vma = vma;
				eb->request->capture_list = capture;
			पूर्ण
		पूर्ण

		/*
		 * If the GPU is not _पढ़ोing_ through the CPU cache, we need
		 * to make sure that any ग_लिखोs (both previous GPU ग_लिखोs from
		 * beक्रमe a change in snooping levels and normal CPU ग_लिखोs)
		 * caught in that cache are flushed to मुख्य memory.
		 *
		 * We want to say
		 *   obj->cache_dirty &&
		 *   !(obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ)
		 * but gcc's optimiser doesn't handle that as well and emits
		 * two jumps instead of one. Maybe one day...
		 */
		अगर (unlikely(obj->cache_dirty & ~obj->cache_coherent)) अणु
			अगर (i915_gem_clflush_object(obj, 0))
				flags &= ~EXEC_OBJECT_ASYNC;
		पूर्ण

		अगर (err == 0 && !(flags & EXEC_OBJECT_ASYNC)) अणु
			err = i915_request_aरुको_object
				(eb->request, obj, flags & EXEC_OBJECT_WRITE);
		पूर्ण

		अगर (err == 0)
			err = i915_vma_move_to_active(vma, eb->request,
						      flags | __EXEC_OBJECT_NO_RESERVE);
	पूर्ण

#अगर_घोषित CONFIG_MMU_NOTIFIER
	अगर (!err && (eb->args->flags & __EXEC_USERPTR_USED)) अणु
		spin_lock(&eb->i915->mm.notअगरier_lock);

		/*
		 * count is always at least 1, otherwise __EXEC_USERPTR_USED
		 * could not have been set
		 */
		क्रम (i = 0; i < count; i++) अणु
			काष्ठा eb_vma *ev = &eb->vma[i];
			काष्ठा drm_i915_gem_object *obj = ev->vma->obj;

			अगर (!i915_gem_object_is_userptr(obj))
				जारी;

			err = i915_gem_object_userptr_submit_करोne(obj);
			अगर (err)
				अवरोध;
		पूर्ण

		spin_unlock(&eb->i915->mm.notअगरier_lock);
	पूर्ण
#पूर्ण_अगर

	अगर (unlikely(err))
		जाओ err_skip;

	/* Unconditionally flush any chipset caches (क्रम streaming ग_लिखोs). */
	पूर्णांकel_gt_chipset_flush(eb->engine->gt);
	वापस 0;

err_skip:
	i915_request_set_error_once(eb->request, err);
	वापस err;
पूर्ण

अटल पूर्णांक i915_gem_check_execbuffer(काष्ठा drm_i915_gem_execbuffer2 *exec)
अणु
	अगर (exec->flags & __I915_EXEC_ILLEGAL_FLAGS)
		वापस -EINVAL;

	/* Kernel clipping was a DRI1 misfeature */
	अगर (!(exec->flags & (I915_EXEC_FENCE_ARRAY |
			     I915_EXEC_USE_EXTENSIONS))) अणु
		अगर (exec->num_cliprects || exec->cliprects_ptr)
			वापस -EINVAL;
	पूर्ण

	अगर (exec->DR4 == 0xffffffff) अणु
		DRM_DEBUG("UXA submitting garbage DR4, fixing up\n");
		exec->DR4 = 0;
	पूर्ण
	अगर (exec->DR1 || exec->DR4)
		वापस -EINVAL;

	अगर ((exec->batch_start_offset | exec->batch_len) & 0x7)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक i915_reset_gen7_sol_offsets(काष्ठा i915_request *rq)
अणु
	u32 *cs;
	पूर्णांक i;

	अगर (!IS_GEN(rq->engine->i915, 7) || rq->engine->id != RCS0) अणु
		drm_dbg(&rq->engine->i915->drm, "sol reset is gen7/rcs only\n");
		वापस -EINVAL;
	पूर्ण

	cs = पूर्णांकel_ring_begin(rq, 4 * 2 + 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(4);
	क्रम (i = 0; i < 4; i++) अणु
		*cs++ = i915_mmio_reg_offset(GEN7_SO_WRITE_OFFSET(i));
		*cs++ = 0;
	पूर्ण
	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल काष्ठा i915_vma *
shaकरोw_batch_pin(काष्ठा i915_execbuffer *eb,
		 काष्ठा drm_i915_gem_object *obj,
		 काष्ठा i915_address_space *vm,
		 अचिन्हित पूर्णांक flags)
अणु
	काष्ठा i915_vma *vma;
	पूर्णांक err;

	vma = i915_vma_instance(obj, vm, शून्य);
	अगर (IS_ERR(vma))
		वापस vma;

	err = i915_vma_pin_ww(vma, &eb->ww, 0, 0, flags);
	अगर (err)
		वापस ERR_PTR(err);

	वापस vma;
पूर्ण

काष्ठा eb_parse_work अणु
	काष्ठा dma_fence_work base;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_vma *batch;
	काष्ठा i915_vma *shaकरोw;
	काष्ठा i915_vma *trampoline;
	अचिन्हित दीर्घ batch_offset;
	अचिन्हित दीर्घ batch_length;
	अचिन्हित दीर्घ *jump_whitelist;
	स्थिर व्योम *batch_map;
	व्योम *shaकरोw_map;
पूर्ण;

अटल पूर्णांक __eb_parse(काष्ठा dma_fence_work *work)
अणु
	काष्ठा eb_parse_work *pw = container_of(work, typeof(*pw), base);
	पूर्णांक ret;
	bool cookie;

	cookie = dma_fence_begin_संकेतling();
	ret = पूर्णांकel_engine_cmd_parser(pw->engine,
				      pw->batch,
				      pw->batch_offset,
				      pw->batch_length,
				      pw->shaकरोw,
				      pw->jump_whitelist,
				      pw->shaकरोw_map,
				      pw->batch_map);
	dma_fence_end_संकेतling(cookie);

	वापस ret;
पूर्ण

अटल व्योम __eb_parse_release(काष्ठा dma_fence_work *work)
अणु
	काष्ठा eb_parse_work *pw = container_of(work, typeof(*pw), base);

	अगर (!IS_ERR_OR_शून्य(pw->jump_whitelist))
		kमुक्त(pw->jump_whitelist);

	अगर (pw->batch_map)
		i915_gem_object_unpin_map(pw->batch->obj);
	अन्यथा
		i915_gem_object_unpin_pages(pw->batch->obj);

	i915_gem_object_unpin_map(pw->shaकरोw->obj);

	अगर (pw->trampoline)
		i915_active_release(&pw->trampoline->active);
	i915_active_release(&pw->shaकरोw->active);
	i915_active_release(&pw->batch->active);
पूर्ण

अटल स्थिर काष्ठा dma_fence_work_ops eb_parse_ops = अणु
	.name = "eb_parse",
	.work = __eb_parse,
	.release = __eb_parse_release,
पूर्ण;

अटल अंतरभूत पूर्णांक
__parser_mark_active(काष्ठा i915_vma *vma,
		     काष्ठा पूर्णांकel_समयline *tl,
		     काष्ठा dma_fence *fence)
अणु
	काष्ठा पूर्णांकel_gt_buffer_pool_node *node = vma->निजी;

	वापस i915_active_ref(&node->active, tl->fence_context, fence);
पूर्ण

अटल पूर्णांक
parser_mark_active(काष्ठा eb_parse_work *pw, काष्ठा पूर्णांकel_समयline *tl)
अणु
	पूर्णांक err;

	mutex_lock(&tl->mutex);

	err = __parser_mark_active(pw->shaकरोw, tl, &pw->base.dma);
	अगर (err)
		जाओ unlock;

	अगर (pw->trampoline) अणु
		err = __parser_mark_active(pw->trampoline, tl, &pw->base.dma);
		अगर (err)
			जाओ unlock;
	पूर्ण

unlock:
	mutex_unlock(&tl->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक eb_parse_pipeline(काष्ठा i915_execbuffer *eb,
			     काष्ठा i915_vma *shaकरोw,
			     काष्ठा i915_vma *trampoline)
अणु
	काष्ठा eb_parse_work *pw;
	काष्ठा drm_i915_gem_object *batch = eb->batch->vma->obj;
	bool needs_clflush;
	पूर्णांक err;

	GEM_BUG_ON(overflows_type(eb->batch_start_offset, pw->batch_offset));
	GEM_BUG_ON(overflows_type(eb->batch_len, pw->batch_length));

	pw = kzalloc(माप(*pw), GFP_KERNEL);
	अगर (!pw)
		वापस -ENOMEM;

	err = i915_active_acquire(&eb->batch->vma->active);
	अगर (err)
		जाओ err_मुक्त;

	err = i915_active_acquire(&shaकरोw->active);
	अगर (err)
		जाओ err_batch;

	अगर (trampoline) अणु
		err = i915_active_acquire(&trampoline->active);
		अगर (err)
			जाओ err_shaकरोw;
	पूर्ण

	pw->shaकरोw_map = i915_gem_object_pin_map(shaकरोw->obj, I915_MAP_WB);
	अगर (IS_ERR(pw->shaकरोw_map)) अणु
		err = PTR_ERR(pw->shaकरोw_map);
		जाओ err_trampoline;
	पूर्ण

	needs_clflush =
		!(batch->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ);

	pw->batch_map = ERR_PTR(-ENODEV);
	अगर (needs_clflush && i915_has_स_नकल_from_wc())
		pw->batch_map = i915_gem_object_pin_map(batch, I915_MAP_WC);

	अगर (IS_ERR(pw->batch_map)) अणु
		err = i915_gem_object_pin_pages(batch);
		अगर (err)
			जाओ err_unmap_shaकरोw;
		pw->batch_map = शून्य;
	पूर्ण

	pw->jump_whitelist =
		पूर्णांकel_engine_cmd_parser_alloc_jump_whitelist(eb->batch_len,
							     trampoline);
	अगर (IS_ERR(pw->jump_whitelist)) अणु
		err = PTR_ERR(pw->jump_whitelist);
		जाओ err_unmap_batch;
	पूर्ण

	dma_fence_work_init(&pw->base, &eb_parse_ops);

	pw->engine = eb->engine;
	pw->batch = eb->batch->vma;
	pw->batch_offset = eb->batch_start_offset;
	pw->batch_length = eb->batch_len;
	pw->shaकरोw = shaकरोw;
	pw->trampoline = trampoline;

	/* Mark active refs early क्रम this worker, in हाल we get पूर्णांकerrupted */
	err = parser_mark_active(pw, eb->context->समयline);
	अगर (err)
		जाओ err_commit;

	err = dma_resv_reserve_shared(pw->batch->resv, 1);
	अगर (err)
		जाओ err_commit;

	err = dma_resv_reserve_shared(shaकरोw->resv, 1);
	अगर (err)
		जाओ err_commit;

	/* Wait क्रम all ग_लिखोs (and relocs) पूर्णांकo the batch to complete */
	err = i915_sw_fence_aरुको_reservation(&pw->base.chain,
					      pw->batch->resv, शून्य, false,
					      0, I915_FENCE_GFP);
	अगर (err < 0)
		जाओ err_commit;

	/* Keep the batch alive and unwritten as we parse */
	dma_resv_add_shared_fence(pw->batch->resv, &pw->base.dma);

	/* Force execution to रुको क्रम completion of the parser */
	dma_resv_add_excl_fence(shaकरोw->resv, &pw->base.dma);

	dma_fence_work_commit_imm(&pw->base);
	वापस 0;

err_commit:
	i915_sw_fence_set_error_once(&pw->base.chain, err);
	dma_fence_work_commit_imm(&pw->base);
	वापस err;

err_unmap_batch:
	अगर (pw->batch_map)
		i915_gem_object_unpin_map(batch);
	अन्यथा
		i915_gem_object_unpin_pages(batch);
err_unmap_shaकरोw:
	i915_gem_object_unpin_map(shaकरोw->obj);
err_trampoline:
	अगर (trampoline)
		i915_active_release(&trampoline->active);
err_shaकरोw:
	i915_active_release(&shaकरोw->active);
err_batch:
	i915_active_release(&eb->batch->vma->active);
err_मुक्त:
	kमुक्त(pw);
	वापस err;
पूर्ण

अटल काष्ठा i915_vma *eb_dispatch_secure(काष्ठा i915_execbuffer *eb, काष्ठा i915_vma *vma)
अणु
	/*
	 * snb/ivb/vlv conflate the "batch in ppgtt" bit with the "non-secure
	 * batch" bit. Hence we need to pin secure batches पूर्णांकo the global gtt.
	 * hsw should have this fixed, but bdw mucks it up again. */
	अगर (eb->batch_flags & I915_DISPATCH_SECURE)
		वापस i915_gem_object_ggtt_pin_ww(vma->obj, &eb->ww, शून्य, 0, 0, 0);

	वापस शून्य;
पूर्ण

अटल पूर्णांक eb_parse(काष्ठा i915_execbuffer *eb)
अणु
	काष्ठा drm_i915_निजी *i915 = eb->i915;
	काष्ठा पूर्णांकel_gt_buffer_pool_node *pool = eb->batch_pool;
	काष्ठा i915_vma *shaकरोw, *trampoline, *batch;
	अचिन्हित दीर्घ len;
	पूर्णांक err;

	अगर (!eb_use_cmdparser(eb)) अणु
		batch = eb_dispatch_secure(eb, eb->batch->vma);
		अगर (IS_ERR(batch))
			वापस PTR_ERR(batch);

		जाओ secure_batch;
	पूर्ण

	len = eb->batch_len;
	अगर (!CMDPARSER_USES_GGTT(eb->i915)) अणु
		/*
		 * ppGTT backed shaकरोw buffers must be mapped RO, to prevent
		 * post-scan tampering
		 */
		अगर (!eb->context->vm->has_पढ़ो_only) अणु
			drm_dbg(&i915->drm,
				"Cannot prevent post-scan tampering without RO capable vm\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		len += I915_CMD_PARSER_TRAMPOLINE_SIZE;
	पूर्ण
	अगर (unlikely(len < eb->batch_len)) /* last paranoid check of overflow */
		वापस -EINVAL;

	अगर (!pool) अणु
		pool = पूर्णांकel_gt_get_buffer_pool(eb->engine->gt, len,
						I915_MAP_WB);
		अगर (IS_ERR(pool))
			वापस PTR_ERR(pool);
		eb->batch_pool = pool;
	पूर्ण

	err = i915_gem_object_lock(pool->obj, &eb->ww);
	अगर (err)
		जाओ err;

	shaकरोw = shaकरोw_batch_pin(eb, pool->obj, eb->context->vm, PIN_USER);
	अगर (IS_ERR(shaकरोw)) अणु
		err = PTR_ERR(shaकरोw);
		जाओ err;
	पूर्ण
	पूर्णांकel_gt_buffer_pool_mark_used(pool);
	i915_gem_object_set_पढ़ोonly(shaकरोw->obj);
	shaकरोw->निजी = pool;

	trampoline = शून्य;
	अगर (CMDPARSER_USES_GGTT(eb->i915)) अणु
		trampoline = shaकरोw;

		shaकरोw = shaकरोw_batch_pin(eb, pool->obj,
					  &eb->engine->gt->ggtt->vm,
					  PIN_GLOBAL);
		अगर (IS_ERR(shaकरोw)) अणु
			err = PTR_ERR(shaकरोw);
			shaकरोw = trampoline;
			जाओ err_shaकरोw;
		पूर्ण
		shaकरोw->निजी = pool;

		eb->batch_flags |= I915_DISPATCH_SECURE;
	पूर्ण

	batch = eb_dispatch_secure(eb, shaकरोw);
	अगर (IS_ERR(batch)) अणु
		err = PTR_ERR(batch);
		जाओ err_trampoline;
	पूर्ण

	err = eb_parse_pipeline(eb, shaकरोw, trampoline);
	अगर (err)
		जाओ err_unpin_batch;

	eb->batch = &eb->vma[eb->buffer_count++];
	eb->batch->vma = i915_vma_get(shaकरोw);
	eb->batch->flags = __EXEC_OBJECT_HAS_PIN;

	eb->trampoline = trampoline;
	eb->batch_start_offset = 0;

secure_batch:
	अगर (batch) अणु
		eb->batch = &eb->vma[eb->buffer_count++];
		eb->batch->flags = __EXEC_OBJECT_HAS_PIN;
		eb->batch->vma = i915_vma_get(batch);
	पूर्ण
	वापस 0;

err_unpin_batch:
	अगर (batch)
		i915_vma_unpin(batch);
err_trampoline:
	अगर (trampoline)
		i915_vma_unpin(trampoline);
err_shaकरोw:
	i915_vma_unpin(shaकरोw);
err:
	वापस err;
पूर्ण

अटल पूर्णांक eb_submit(काष्ठा i915_execbuffer *eb, काष्ठा i915_vma *batch)
अणु
	पूर्णांक err;

	अगर (पूर्णांकel_context_nopreempt(eb->context))
		__set_bit(I915_FENCE_FLAG_NOPREEMPT, &eb->request->fence.flags);

	err = eb_move_to_gpu(eb);
	अगर (err)
		वापस err;

	अगर (eb->args->flags & I915_EXEC_GEN7_SOL_RESET) अणु
		err = i915_reset_gen7_sol_offsets(eb->request);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * After we completed रुकोing क्रम other engines (using HW semaphores)
	 * then we can संकेत that this request/batch is पढ़ोy to run. This
	 * allows us to determine अगर the batch is still रुकोing on the GPU
	 * or actually running by checking the bपढ़ोcrumb.
	 */
	अगर (eb->engine->emit_init_bपढ़ोcrumb) अणु
		err = eb->engine->emit_init_bपढ़ोcrumb(eb->request);
		अगर (err)
			वापस err;
	पूर्ण

	err = eb->engine->emit_bb_start(eb->request,
					batch->node.start +
					eb->batch_start_offset,
					eb->batch_len,
					eb->batch_flags);
	अगर (err)
		वापस err;

	अगर (eb->trampoline) अणु
		GEM_BUG_ON(eb->batch_start_offset);
		err = eb->engine->emit_bb_start(eb->request,
						eb->trampoline->node.start +
						eb->batch_len,
						0, 0);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक num_vcs_engines(स्थिर काष्ठा drm_i915_निजी *i915)
अणु
	वापस hweight_दीर्घ(VDBOX_MASK(&i915->gt));
पूर्ण

/*
 * Find one BSD ring to dispatch the corresponding BSD command.
 * The engine index is वापसed.
 */
अटल अचिन्हित पूर्णांक
gen8_dispatch_bsd_engine(काष्ठा drm_i915_निजी *dev_priv,
			 काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_file_निजी *file_priv = file->driver_priv;

	/* Check whether the file_priv has alपढ़ोy selected one ring. */
	अगर ((पूर्णांक)file_priv->bsd_engine < 0)
		file_priv->bsd_engine =
			get_अक्रमom_पूर्णांक() % num_vcs_engines(dev_priv);

	वापस file_priv->bsd_engine;
पूर्ण

अटल स्थिर क्रमागत पूर्णांकel_engine_id user_ring_map[] = अणु
	[I915_EXEC_DEFAULT]	= RCS0,
	[I915_EXEC_RENDER]	= RCS0,
	[I915_EXEC_BLT]		= BCS0,
	[I915_EXEC_BSD]		= VCS0,
	[I915_EXEC_VEBOX]	= VECS0
पूर्ण;

अटल काष्ठा i915_request *eb_throttle(काष्ठा i915_execbuffer *eb, काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा पूर्णांकel_ring *ring = ce->ring;
	काष्ठा पूर्णांकel_समयline *tl = ce->समयline;
	काष्ठा i915_request *rq;

	/*
	 * Completely unscientअगरic finger-in-the-air estimates क्रम suitable
	 * maximum user request size (to aव्योम blocking) and then backoff.
	 */
	अगर (पूर्णांकel_ring_update_space(ring) >= PAGE_SIZE)
		वापस शून्य;

	/*
	 * Find a request that after रुकोing upon, there will be at least half
	 * the ring available. The hysteresis allows us to compete क्रम the
	 * shared ring and should mean that we sleep less often prior to
	 * claiming our resources, but not so दीर्घ that the ring completely
	 * drains beक्रमe we can submit our next request.
	 */
	list_क्रम_each_entry(rq, &tl->requests, link) अणु
		अगर (rq->ring != ring)
			जारी;

		अगर (__पूर्णांकel_ring_space(rq->postfix,
				       ring->emit, ring->size) > ring->size / 2)
			अवरोध;
	पूर्ण
	अगर (&rq->link == &tl->requests)
		वापस शून्य; /* weird, we will check again later क्रम real */

	वापस i915_request_get(rq);
पूर्ण

अटल काष्ठा i915_request *eb_pin_engine(काष्ठा i915_execbuffer *eb, bool throttle)
अणु
	काष्ठा पूर्णांकel_context *ce = eb->context;
	काष्ठा पूर्णांकel_समयline *tl;
	काष्ठा i915_request *rq = शून्य;
	पूर्णांक err;

	GEM_BUG_ON(eb->args->flags & __EXEC_ENGINE_PINNED);

	अगर (unlikely(पूर्णांकel_context_is_banned(ce)))
		वापस ERR_PTR(-EIO);

	/*
	 * Pinning the contexts may generate requests in order to acquire
	 * GGTT space, so करो this first beक्रमe we reserve a seqno क्रम
	 * ourselves.
	 */
	err = पूर्णांकel_context_pin_ww(ce, &eb->ww);
	अगर (err)
		वापस ERR_PTR(err);

	/*
	 * Take a local wakeref क्रम preparing to dispatch the execbuf as
	 * we expect to access the hardware fairly frequently in the
	 * process, and require the engine to be kept awake between accesses.
	 * Upon dispatch, we acquire another proदीर्घed wakeref that we hold
	 * until the समयline is idle, which in turn releases the wakeref
	 * taken on the engine, and the parent device.
	 */
	tl = पूर्णांकel_context_समयline_lock(ce);
	अगर (IS_ERR(tl)) अणु
		पूर्णांकel_context_unpin(ce);
		वापस ERR_CAST(tl);
	पूर्ण

	पूर्णांकel_context_enter(ce);
	अगर (throttle)
		rq = eb_throttle(eb, ce);
	पूर्णांकel_context_समयline_unlock(tl);

	eb->args->flags |= __EXEC_ENGINE_PINNED;
	वापस rq;
पूर्ण

अटल व्योम eb_unpin_engine(काष्ठा i915_execbuffer *eb)
अणु
	काष्ठा पूर्णांकel_context *ce = eb->context;
	काष्ठा पूर्णांकel_समयline *tl = ce->समयline;

	अगर (!(eb->args->flags & __EXEC_ENGINE_PINNED))
		वापस;

	eb->args->flags &= ~__EXEC_ENGINE_PINNED;

	mutex_lock(&tl->mutex);
	पूर्णांकel_context_निकास(ce);
	mutex_unlock(&tl->mutex);

	पूर्णांकel_context_unpin(ce);
पूर्ण

अटल अचिन्हित पूर्णांक
eb_select_legacy_ring(काष्ठा i915_execbuffer *eb)
अणु
	काष्ठा drm_i915_निजी *i915 = eb->i915;
	काष्ठा drm_i915_gem_execbuffer2 *args = eb->args;
	अचिन्हित पूर्णांक user_ring_id = args->flags & I915_EXEC_RING_MASK;

	अगर (user_ring_id != I915_EXEC_BSD &&
	    (args->flags & I915_EXEC_BSD_MASK)) अणु
		drm_dbg(&i915->drm,
			"execbuf with non bsd ring but with invalid "
			"bsd dispatch flags: %d\n", (पूर्णांक)(args->flags));
		वापस -1;
	पूर्ण

	अगर (user_ring_id == I915_EXEC_BSD && num_vcs_engines(i915) > 1) अणु
		अचिन्हित पूर्णांक bsd_idx = args->flags & I915_EXEC_BSD_MASK;

		अगर (bsd_idx == I915_EXEC_BSD_DEFAULT) अणु
			bsd_idx = gen8_dispatch_bsd_engine(i915, eb->file);
		पूर्ण अन्यथा अगर (bsd_idx >= I915_EXEC_BSD_RING1 &&
			   bsd_idx <= I915_EXEC_BSD_RING2) अणु
			bsd_idx >>= I915_EXEC_BSD_SHIFT;
			bsd_idx--;
		पूर्ण अन्यथा अणु
			drm_dbg(&i915->drm,
				"execbuf with unknown bsd ring: %u\n",
				bsd_idx);
			वापस -1;
		पूर्ण

		वापस _VCS(bsd_idx);
	पूर्ण

	अगर (user_ring_id >= ARRAY_SIZE(user_ring_map)) अणु
		drm_dbg(&i915->drm, "execbuf with unknown ring: %u\n",
			user_ring_id);
		वापस -1;
	पूर्ण

	वापस user_ring_map[user_ring_id];
पूर्ण

अटल पूर्णांक
eb_select_engine(काष्ठा i915_execbuffer *eb)
अणु
	काष्ठा पूर्णांकel_context *ce;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	अगर (i915_gem_context_user_engines(eb->gem_context))
		idx = eb->args->flags & I915_EXEC_RING_MASK;
	अन्यथा
		idx = eb_select_legacy_ring(eb);

	ce = i915_gem_context_get_engine(eb->gem_context, idx);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	पूर्णांकel_gt_pm_get(ce->engine->gt);

	अगर (!test_bit(CONTEXT_ALLOC_BIT, &ce->flags)) अणु
		err = पूर्णांकel_context_alloc_state(ce);
		अगर (err)
			जाओ err;
	पूर्ण

	/*
	 * ABI: Beक्रमe userspace accesses the GPU (e.g. execbuffer), report
	 * EIO अगर the GPU is alपढ़ोy wedged.
	 */
	err = पूर्णांकel_gt_terminally_wedged(ce->engine->gt);
	अगर (err)
		जाओ err;

	eb->context = ce;
	eb->engine = ce->engine;

	/*
	 * Make sure engine pool stays alive even अगर we call पूर्णांकel_context_put
	 * during ww handling. The pool is destroyed when last pm reference
	 * is dropped, which अवरोधs our -EDEADLK handling.
	 */
	वापस err;

err:
	पूर्णांकel_gt_pm_put(ce->engine->gt);
	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल व्योम
eb_put_engine(काष्ठा i915_execbuffer *eb)
अणु
	पूर्णांकel_gt_pm_put(eb->engine->gt);
	पूर्णांकel_context_put(eb->context);
पूर्ण

अटल व्योम
__मुक्त_fence_array(काष्ठा eb_fence *fences, अचिन्हित पूर्णांक n)
अणु
	जबतक (n--) अणु
		drm_syncobj_put(ptr_mask_bits(fences[n].syncobj, 2));
		dma_fence_put(fences[n].dma_fence);
		kमुक्त(fences[n].chain_fence);
	पूर्ण
	kvमुक्त(fences);
पूर्ण

अटल पूर्णांक
add_समयline_fence_array(काष्ठा i915_execbuffer *eb,
			 स्थिर काष्ठा drm_i915_gem_execbuffer_ext_समयline_fences *समयline_fences)
अणु
	काष्ठा drm_i915_gem_exec_fence __user *user_fences;
	u64 __user *user_values;
	काष्ठा eb_fence *f;
	u64 nfences;
	पूर्णांक err = 0;

	nfences = समयline_fences->fence_count;
	अगर (!nfences)
		वापस 0;

	/* Check multiplication overflow क्रम access_ok() and kvदो_स्मृति_array() */
	BUILD_BUG_ON(माप(माप_प्रकार) > माप(अचिन्हित दीर्घ));
	अगर (nfences > min_t(अचिन्हित दीर्घ,
			    अच_दीर्घ_उच्च / माप(*user_fences),
			    SIZE_MAX / माप(*f)) - eb->num_fences)
		वापस -EINVAL;

	user_fences = u64_to_user_ptr(समयline_fences->handles_ptr);
	अगर (!access_ok(user_fences, nfences * माप(*user_fences)))
		वापस -EFAULT;

	user_values = u64_to_user_ptr(समयline_fences->values_ptr);
	अगर (!access_ok(user_values, nfences * माप(*user_values)))
		वापस -EFAULT;

	f = kपुनः_स्मृति(eb->fences,
		     (eb->num_fences + nfences) * माप(*f),
		     __GFP_NOWARN | GFP_KERNEL);
	अगर (!f)
		वापस -ENOMEM;

	eb->fences = f;
	f += eb->num_fences;

	BUILD_BUG_ON(~(ARCH_KMALLOC_MINALIGN - 1) &
		     ~__I915_EXEC_FENCE_UNKNOWN_FLAGS);

	जबतक (nfences--) अणु
		काष्ठा drm_i915_gem_exec_fence user_fence;
		काष्ठा drm_syncobj *syncobj;
		काष्ठा dma_fence *fence = शून्य;
		u64 poपूर्णांक;

		अगर (__copy_from_user(&user_fence,
				     user_fences++,
				     माप(user_fence)))
			वापस -EFAULT;

		अगर (user_fence.flags & __I915_EXEC_FENCE_UNKNOWN_FLAGS)
			वापस -EINVAL;

		अगर (__get_user(poपूर्णांक, user_values++))
			वापस -EFAULT;

		syncobj = drm_syncobj_find(eb->file, user_fence.handle);
		अगर (!syncobj) अणु
			DRM_DEBUG("Invalid syncobj handle provided\n");
			वापस -ENOENT;
		पूर्ण

		fence = drm_syncobj_fence_get(syncobj);

		अगर (!fence && user_fence.flags &&
		    !(user_fence.flags & I915_EXEC_FENCE_SIGNAL)) अणु
			DRM_DEBUG("Syncobj handle has no fence\n");
			drm_syncobj_put(syncobj);
			वापस -EINVAL;
		पूर्ण

		अगर (fence)
			err = dma_fence_chain_find_seqno(&fence, poपूर्णांक);

		अगर (err && !(user_fence.flags & I915_EXEC_FENCE_SIGNAL)) अणु
			DRM_DEBUG("Syncobj handle missing requested point %llu\n", poपूर्णांक);
			dma_fence_put(fence);
			drm_syncobj_put(syncobj);
			वापस err;
		पूर्ण

		/*
		 * A poपूर्णांक might have been संकेतed alपढ़ोy and
		 * garbage collected from the समयline. In this हाल
		 * just ignore the poपूर्णांक and carry on.
		 */
		अगर (!fence && !(user_fence.flags & I915_EXEC_FENCE_SIGNAL)) अणु
			drm_syncobj_put(syncobj);
			जारी;
		पूर्ण

		/*
		 * For समयline syncobjs we need to pपुनः_स्मृतिate chains क्रम
		 * later संकेतing.
		 */
		अगर (poपूर्णांक != 0 && user_fence.flags & I915_EXEC_FENCE_SIGNAL) अणु
			/*
			 * Waiting and संकेतing the same poपूर्णांक (when poपूर्णांक !=
			 * 0) would अवरोध the समयline.
			 */
			अगर (user_fence.flags & I915_EXEC_FENCE_WAIT) अणु
				DRM_DEBUG("Trying to wait & signal the same timeline point.\n");
				dma_fence_put(fence);
				drm_syncobj_put(syncobj);
				वापस -EINVAL;
			पूर्ण

			f->chain_fence =
				kदो_स्मृति(माप(*f->chain_fence),
					GFP_KERNEL);
			अगर (!f->chain_fence) अणु
				drm_syncobj_put(syncobj);
				dma_fence_put(fence);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			f->chain_fence = शून्य;
		पूर्ण

		f->syncobj = ptr_pack_bits(syncobj, user_fence.flags, 2);
		f->dma_fence = fence;
		f->value = poपूर्णांक;
		f++;
		eb->num_fences++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक add_fence_array(काष्ठा i915_execbuffer *eb)
अणु
	काष्ठा drm_i915_gem_execbuffer2 *args = eb->args;
	काष्ठा drm_i915_gem_exec_fence __user *user;
	अचिन्हित दीर्घ num_fences = args->num_cliprects;
	काष्ठा eb_fence *f;

	अगर (!(args->flags & I915_EXEC_FENCE_ARRAY))
		वापस 0;

	अगर (!num_fences)
		वापस 0;

	/* Check multiplication overflow क्रम access_ok() and kvदो_स्मृति_array() */
	BUILD_BUG_ON(माप(माप_प्रकार) > माप(अचिन्हित दीर्घ));
	अगर (num_fences > min_t(अचिन्हित दीर्घ,
			       अच_दीर्घ_उच्च / माप(*user),
			       SIZE_MAX / माप(*f) - eb->num_fences))
		वापस -EINVAL;

	user = u64_to_user_ptr(args->cliprects_ptr);
	अगर (!access_ok(user, num_fences * माप(*user)))
		वापस -EFAULT;

	f = kपुनः_स्मृति(eb->fences,
		     (eb->num_fences + num_fences) * माप(*f),
		     __GFP_NOWARN | GFP_KERNEL);
	अगर (!f)
		वापस -ENOMEM;

	eb->fences = f;
	f += eb->num_fences;
	जबतक (num_fences--) अणु
		काष्ठा drm_i915_gem_exec_fence user_fence;
		काष्ठा drm_syncobj *syncobj;
		काष्ठा dma_fence *fence = शून्य;

		अगर (__copy_from_user(&user_fence, user++, माप(user_fence)))
			वापस -EFAULT;

		अगर (user_fence.flags & __I915_EXEC_FENCE_UNKNOWN_FLAGS)
			वापस -EINVAL;

		syncobj = drm_syncobj_find(eb->file, user_fence.handle);
		अगर (!syncobj) अणु
			DRM_DEBUG("Invalid syncobj handle provided\n");
			वापस -ENOENT;
		पूर्ण

		अगर (user_fence.flags & I915_EXEC_FENCE_WAIT) अणु
			fence = drm_syncobj_fence_get(syncobj);
			अगर (!fence) अणु
				DRM_DEBUG("Syncobj handle has no fence\n");
				drm_syncobj_put(syncobj);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		BUILD_BUG_ON(~(ARCH_KMALLOC_MINALIGN - 1) &
			     ~__I915_EXEC_FENCE_UNKNOWN_FLAGS);

		f->syncobj = ptr_pack_bits(syncobj, user_fence.flags, 2);
		f->dma_fence = fence;
		f->value = 0;
		f->chain_fence = शून्य;
		f++;
		eb->num_fences++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम put_fence_array(काष्ठा eb_fence *fences, पूर्णांक num_fences)
अणु
	अगर (fences)
		__मुक्त_fence_array(fences, num_fences);
पूर्ण

अटल पूर्णांक
aरुको_fence_array(काष्ठा i915_execbuffer *eb)
अणु
	अचिन्हित पूर्णांक n;
	पूर्णांक err;

	क्रम (n = 0; n < eb->num_fences; n++) अणु
		काष्ठा drm_syncobj *syncobj;
		अचिन्हित पूर्णांक flags;

		syncobj = ptr_unpack_bits(eb->fences[n].syncobj, &flags, 2);

		अगर (!eb->fences[n].dma_fence)
			जारी;

		err = i915_request_aरुको_dma_fence(eb->request,
						   eb->fences[n].dma_fence);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम संकेत_fence_array(स्थिर काष्ठा i915_execbuffer *eb)
अणु
	काष्ठा dma_fence * स्थिर fence = &eb->request->fence;
	अचिन्हित पूर्णांक n;

	क्रम (n = 0; n < eb->num_fences; n++) अणु
		काष्ठा drm_syncobj *syncobj;
		अचिन्हित पूर्णांक flags;

		syncobj = ptr_unpack_bits(eb->fences[n].syncobj, &flags, 2);
		अगर (!(flags & I915_EXEC_FENCE_SIGNAL))
			जारी;

		अगर (eb->fences[n].chain_fence) अणु
			drm_syncobj_add_poपूर्णांक(syncobj,
					      eb->fences[n].chain_fence,
					      fence,
					      eb->fences[n].value);
			/*
			 * The chain's ownership is transferred to the
			 * समयline.
			 */
			eb->fences[n].chain_fence = शून्य;
		पूर्ण अन्यथा अणु
			drm_syncobj_replace_fence(syncobj, fence);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
parse_समयline_fences(काष्ठा i915_user_extension __user *ext, व्योम *data)
अणु
	काष्ठा i915_execbuffer *eb = data;
	काष्ठा drm_i915_gem_execbuffer_ext_समयline_fences समयline_fences;

	अगर (copy_from_user(&समयline_fences, ext, माप(समयline_fences)))
		वापस -EFAULT;

	वापस add_समयline_fence_array(eb, &समयline_fences);
पूर्ण

अटल व्योम retire_requests(काष्ठा पूर्णांकel_समयline *tl, काष्ठा i915_request *end)
अणु
	काष्ठा i915_request *rq, *rn;

	list_क्रम_each_entry_safe(rq, rn, &tl->requests, link)
		अगर (rq == end || !i915_request_retire(rq))
			अवरोध;
पूर्ण

अटल पूर्णांक eb_request_add(काष्ठा i915_execbuffer *eb, पूर्णांक err)
अणु
	काष्ठा i915_request *rq = eb->request;
	काष्ठा पूर्णांकel_समयline * स्थिर tl = i915_request_समयline(rq);
	काष्ठा i915_sched_attr attr = अणुपूर्ण;
	काष्ठा i915_request *prev;

	lockdep_निश्चित_held(&tl->mutex);
	lockdep_unpin_lock(&tl->mutex, rq->cookie);

	trace_i915_request_add(rq);

	prev = __i915_request_commit(rq);

	/* Check that the context wasn't destroyed beक्रमe submission */
	अगर (likely(!पूर्णांकel_context_is_बंदd(eb->context))) अणु
		attr = eb->gem_context->sched;
	पूर्ण अन्यथा अणु
		/* Serialise with context_बंद via the add_to_समयline */
		i915_request_set_error_once(rq, -ENOENT);
		__i915_request_skip(rq);
		err = -ENOENT; /* override any transient errors */
	पूर्ण

	__i915_request_queue(rq, &attr);

	/* Try to clean up the client's समयline after submitting the request */
	अगर (prev)
		retire_requests(tl, prev);

	mutex_unlock(&tl->mutex);

	वापस err;
पूर्ण

अटल स्थिर i915_user_extension_fn execbuf_extensions[] = अणु
	[DRM_I915_GEM_EXECBUFFER_EXT_TIMELINE_FENCES] = parse_समयline_fences,
पूर्ण;

अटल पूर्णांक
parse_execbuf2_extensions(काष्ठा drm_i915_gem_execbuffer2 *args,
			  काष्ठा i915_execbuffer *eb)
अणु
	अगर (!(args->flags & I915_EXEC_USE_EXTENSIONS))
		वापस 0;

	/* The execbuf2 extension mechanism reuses cliprects_ptr. So we cannot
	 * have another flag also using it at the same समय.
	 */
	अगर (eb->args->flags & I915_EXEC_FENCE_ARRAY)
		वापस -EINVAL;

	अगर (args->num_cliprects != 0)
		वापस -EINVAL;

	वापस i915_user_extensions(u64_to_user_ptr(args->cliprects_ptr),
				    execbuf_extensions,
				    ARRAY_SIZE(execbuf_extensions),
				    eb);
पूर्ण

अटल पूर्णांक
i915_gem_करो_execbuffer(काष्ठा drm_device *dev,
		       काष्ठा drm_file *file,
		       काष्ठा drm_i915_gem_execbuffer2 *args,
		       काष्ठा drm_i915_gem_exec_object2 *exec)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा i915_execbuffer eb;
	काष्ठा dma_fence *in_fence = शून्य;
	काष्ठा sync_file *out_fence = शून्य;
	काष्ठा i915_vma *batch;
	पूर्णांक out_fence_fd = -1;
	पूर्णांक err;

	BUILD_BUG_ON(__EXEC_INTERNAL_FLAGS & ~__I915_EXEC_ILLEGAL_FLAGS);
	BUILD_BUG_ON(__EXEC_OBJECT_INTERNAL_FLAGS &
		     ~__EXEC_OBJECT_UNKNOWN_FLAGS);

	eb.i915 = i915;
	eb.file = file;
	eb.args = args;
	अगर (DBG_FORCE_RELOC || !(args->flags & I915_EXEC_NO_RELOC))
		args->flags |= __EXEC_HAS_RELOC;

	eb.exec = exec;
	eb.vma = (काष्ठा eb_vma *)(exec + args->buffer_count + 1);
	eb.vma[0].vma = शून्य;
	eb.reloc_pool = eb.batch_pool = शून्य;
	eb.reloc_context = शून्य;

	eb.invalid_flags = __EXEC_OBJECT_UNKNOWN_FLAGS;
	reloc_cache_init(&eb.reloc_cache, eb.i915);

	eb.buffer_count = args->buffer_count;
	eb.batch_start_offset = args->batch_start_offset;
	eb.batch_len = args->batch_len;
	eb.trampoline = शून्य;

	eb.fences = शून्य;
	eb.num_fences = 0;

	eb.batch_flags = 0;
	अगर (args->flags & I915_EXEC_SECURE) अणु
		अगर (INTEL_GEN(i915) >= 11)
			वापस -ENODEV;

		/* Return -EPERM to trigger fallback code on old binaries. */
		अगर (!HAS_SECURE_BATCHES(i915))
			वापस -EPERM;

		अगर (!drm_is_current_master(file) || !capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		eb.batch_flags |= I915_DISPATCH_SECURE;
	पूर्ण
	अगर (args->flags & I915_EXEC_IS_PINNED)
		eb.batch_flags |= I915_DISPATCH_PINNED;

	err = parse_execbuf2_extensions(args, &eb);
	अगर (err)
		जाओ err_ext;

	err = add_fence_array(&eb);
	अगर (err)
		जाओ err_ext;

#घोषणा IN_FENCES (I915_EXEC_FENCE_IN | I915_EXEC_FENCE_SUBMIT)
	अगर (args->flags & IN_FENCES) अणु
		अगर ((args->flags & IN_FENCES) == IN_FENCES)
			वापस -EINVAL;

		in_fence = sync_file_get_fence(lower_32_bits(args->rsvd2));
		अगर (!in_fence) अणु
			err = -EINVAL;
			जाओ err_ext;
		पूर्ण
	पूर्ण
#अघोषित IN_FENCES

	अगर (args->flags & I915_EXEC_FENCE_OUT) अणु
		out_fence_fd = get_unused_fd_flags(O_CLOEXEC);
		अगर (out_fence_fd < 0) अणु
			err = out_fence_fd;
			जाओ err_in_fence;
		पूर्ण
	पूर्ण

	err = eb_create(&eb);
	अगर (err)
		जाओ err_out_fence;

	GEM_BUG_ON(!eb.lut_size);

	err = eb_select_context(&eb);
	अगर (unlikely(err))
		जाओ err_destroy;

	err = eb_select_engine(&eb);
	अगर (unlikely(err))
		जाओ err_context;

	err = eb_lookup_vmas(&eb);
	अगर (err) अणु
		eb_release_vmas(&eb, true, true);
		जाओ err_engine;
	पूर्ण

	i915_gem_ww_ctx_init(&eb.ww, true);

	err = eb_relocate_parse(&eb);
	अगर (err) अणु
		/*
		 * If the user expects the execobject.offset and
		 * reloc.presumed_offset to be an exact match,
		 * as क्रम using NO_RELOC, then we cannot update
		 * the execobject.offset until we have completed
		 * relocation.
		 */
		args->flags &= ~__EXEC_HAS_RELOC;
		जाओ err_vma;
	पूर्ण

	ww_acquire_करोne(&eb.ww.ctx);

	batch = eb.batch->vma;

	/* All GPU relocation batches must be submitted prior to the user rq */
	GEM_BUG_ON(eb.reloc_cache.rq);

	/* Allocate a request क्रम this batch buffer nice and early. */
	eb.request = i915_request_create(eb.context);
	अगर (IS_ERR(eb.request)) अणु
		err = PTR_ERR(eb.request);
		जाओ err_vma;
	पूर्ण

	अगर (in_fence) अणु
		अगर (args->flags & I915_EXEC_FENCE_SUBMIT)
			err = i915_request_aरुको_execution(eb.request,
							   in_fence,
							   eb.engine->bond_execute);
		अन्यथा
			err = i915_request_aरुको_dma_fence(eb.request,
							   in_fence);
		अगर (err < 0)
			जाओ err_request;
	पूर्ण

	अगर (eb.fences) अणु
		err = aरुको_fence_array(&eb);
		अगर (err)
			जाओ err_request;
	पूर्ण

	अगर (out_fence_fd != -1) अणु
		out_fence = sync_file_create(&eb.request->fence);
		अगर (!out_fence) अणु
			err = -ENOMEM;
			जाओ err_request;
		पूर्ण
	पूर्ण

	/*
	 * Whilst this request exists, batch_obj will be on the
	 * active_list, and so will hold the active reference. Only when this
	 * request is retired will the the batch_obj be moved onto the
	 * inactive_list and lose its active reference. Hence we करो not need
	 * to explicitly hold another reference here.
	 */
	eb.request->batch = batch;
	अगर (eb.batch_pool)
		पूर्णांकel_gt_buffer_pool_mark_active(eb.batch_pool, eb.request);

	trace_i915_request_queue(eb.request, eb.batch_flags);
	err = eb_submit(&eb, batch);

err_request:
	i915_request_get(eb.request);
	err = eb_request_add(&eb, err);

	अगर (eb.fences)
		संकेत_fence_array(&eb);

	अगर (out_fence) अणु
		अगर (err == 0) अणु
			fd_install(out_fence_fd, out_fence->file);
			args->rsvd2 &= GENMASK_ULL(31, 0); /* keep in-fence */
			args->rsvd2 |= (u64)out_fence_fd << 32;
			out_fence_fd = -1;
		पूर्ण अन्यथा अणु
			fput(out_fence->file);
		पूर्ण
	पूर्ण
	i915_request_put(eb.request);

err_vma:
	eb_release_vmas(&eb, true, true);
	अगर (eb.trampoline)
		i915_vma_unpin(eb.trampoline);
	WARN_ON(err == -EDEADLK);
	i915_gem_ww_ctx_fini(&eb.ww);

	अगर (eb.batch_pool)
		पूर्णांकel_gt_buffer_pool_put(eb.batch_pool);
	अगर (eb.reloc_pool)
		पूर्णांकel_gt_buffer_pool_put(eb.reloc_pool);
	अगर (eb.reloc_context)
		पूर्णांकel_context_put(eb.reloc_context);
err_engine:
	eb_put_engine(&eb);
err_context:
	i915_gem_context_put(eb.gem_context);
err_destroy:
	eb_destroy(&eb);
err_out_fence:
	अगर (out_fence_fd != -1)
		put_unused_fd(out_fence_fd);
err_in_fence:
	dma_fence_put(in_fence);
err_ext:
	put_fence_array(eb.fences, eb.num_fences);
	वापस err;
पूर्ण

अटल माप_प्रकार eb_element_size(व्योम)
अणु
	वापस माप(काष्ठा drm_i915_gem_exec_object2) + माप(काष्ठा eb_vma);
पूर्ण

अटल bool check_buffer_count(माप_प्रकार count)
अणु
	स्थिर माप_प्रकार sz = eb_element_size();

	/*
	 * When using LUT_HANDLE, we impose a limit of पूर्णांक_उच्च क्रम the lookup
	 * array size (see eb_create()). Otherwise, we can accept an array as
	 * large as can be addressed (though use large arrays at your peril)!
	 */

	वापस !(count < 1 || count > पूर्णांक_उच्च || count > SIZE_MAX / sz - 1);
पूर्ण

पूर्णांक
i915_gem_execbuffer2_ioctl(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा drm_i915_gem_execbuffer2 *args = data;
	काष्ठा drm_i915_gem_exec_object2 *exec2_list;
	स्थिर माप_प्रकार count = args->buffer_count;
	पूर्णांक err;

	अगर (!check_buffer_count(count)) अणु
		drm_dbg(&i915->drm, "execbuf2 with %zd buffers\n", count);
		वापस -EINVAL;
	पूर्ण

	err = i915_gem_check_execbuffer(args);
	अगर (err)
		वापस err;

	/* Allocate extra slots क्रम use by the command parser */
	exec2_list = kvदो_स्मृति_array(count + 2, eb_element_size(),
				    __GFP_NOWARN | GFP_KERNEL);
	अगर (exec2_list == शून्य) अणु
		drm_dbg(&i915->drm, "Failed to allocate exec list for %zd buffers\n",
			count);
		वापस -ENOMEM;
	पूर्ण
	अगर (copy_from_user(exec2_list,
			   u64_to_user_ptr(args->buffers_ptr),
			   माप(*exec2_list) * count)) अणु
		drm_dbg(&i915->drm, "copy %zd exec entries failed\n", count);
		kvमुक्त(exec2_list);
		वापस -EFAULT;
	पूर्ण

	err = i915_gem_करो_execbuffer(dev, file, args, exec2_list);

	/*
	 * Now that we have begun execution of the batchbuffer, we ignore
	 * any new error after this poपूर्णांक. Also given that we have alपढ़ोy
	 * updated the associated relocations, we try to ग_लिखो out the current
	 * object locations irrespective of any error.
	 */
	अगर (args->flags & __EXEC_HAS_RELOC) अणु
		काष्ठा drm_i915_gem_exec_object2 __user *user_exec_list =
			u64_to_user_ptr(args->buffers_ptr);
		अचिन्हित पूर्णांक i;

		/* Copy the new buffer offsets back to the user's exec list. */
		/*
		 * Note: count * माप(*user_exec_list) करोes not overflow,
		 * because we checked 'count' in check_buffer_count().
		 *
		 * And this range alपढ़ोy got effectively checked earlier
		 * when we did the "copy_from_user()" above.
		 */
		अगर (!user_ग_लिखो_access_begin(user_exec_list,
					     count * माप(*user_exec_list)))
			जाओ end;

		क्रम (i = 0; i < args->buffer_count; i++) अणु
			अगर (!(exec2_list[i].offset & UPDATE))
				जारी;

			exec2_list[i].offset =
				gen8_canonical_addr(exec2_list[i].offset & PIN_OFFSET_MASK);
			unsafe_put_user(exec2_list[i].offset,
					&user_exec_list[i].offset,
					end_user);
		पूर्ण
end_user:
		user_ग_लिखो_access_end();
end:;
	पूर्ण

	args->flags &= ~__I915_EXEC_UNKNOWN_FLAGS;
	kvमुक्त(exec2_list);
	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/i915_gem_execbuffer.c"
#पूर्ण_अगर
