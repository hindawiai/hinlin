<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#अगर_अघोषित __I915_GEM_OBJECT_TYPES_H__
#घोषणा __I915_GEM_OBJECT_TYPES_H__

#समावेश <linux/mmu_notअगरier.h>

#समावेश <drm/drm_gem.h>
#समावेश <uapi/drm/i915_drm.h>

#समावेश "i915_active.h"
#समावेश "i915_selftest.h"

काष्ठा drm_i915_gem_object;
काष्ठा पूर्णांकel_fronbuffer;

/*
 * काष्ठा i915_lut_handle tracks the fast lookups from handle to vma used
 * क्रम execbuf. Although we use a radixtree क्रम that mapping, in order to
 * हटाओ them as the object or context is बंदd, we need a secondary list
 * and a translation entry (i915_lut_handle).
 */
काष्ठा i915_lut_handle अणु
	काष्ठा list_head obj_link;
	काष्ठा i915_gem_context *ctx;
	u32 handle;
पूर्ण;

काष्ठा drm_i915_gem_object_ops अणु
	अचिन्हित पूर्णांक flags;
#घोषणा I915_GEM_OBJECT_HAS_IOMEM	BIT(1)
#घोषणा I915_GEM_OBJECT_IS_SHRINKABLE	BIT(2)
#घोषणा I915_GEM_OBJECT_IS_PROXY	BIT(3)
#घोषणा I915_GEM_OBJECT_NO_MMAP		BIT(4)

	/* Interface between the GEM object and its backing storage.
	 * get_pages() is called once prior to the use of the associated set
	 * of pages beक्रमe to binding them पूर्णांकo the GTT, and put_pages() is
	 * called after we no दीर्घer need them. As we expect there to be
	 * associated cost with migrating pages between the backing storage
	 * and making them available क्रम the GPU (e.g. clflush), we may hold
	 * onto the pages after they are no दीर्घer referenced by the GPU
	 * in हाल they may be used again लघुly (क्रम example migrating the
	 * pages to a dअगरferent memory करोमुख्य within the GTT). put_pages()
	 * will thereक्रमe most likely be called when the object itself is
	 * being released or under memory pressure (where we attempt to
	 * reap pages क्रम the shrinker).
	 */
	पूर्णांक (*get_pages)(काष्ठा drm_i915_gem_object *obj);
	व्योम (*put_pages)(काष्ठा drm_i915_gem_object *obj,
			  काष्ठा sg_table *pages);
	व्योम (*truncate)(काष्ठा drm_i915_gem_object *obj);
	व्योम (*ग_लिखोback)(काष्ठा drm_i915_gem_object *obj);

	पूर्णांक (*pपढ़ो)(काष्ठा drm_i915_gem_object *obj,
		     स्थिर काष्ठा drm_i915_gem_pपढ़ो *arg);
	पूर्णांक (*pग_लिखो)(काष्ठा drm_i915_gem_object *obj,
		      स्थिर काष्ठा drm_i915_gem_pग_लिखो *arg);

	पूर्णांक (*dmabuf_export)(काष्ठा drm_i915_gem_object *obj);
	व्योम (*release)(काष्ठा drm_i915_gem_object *obj);

	स्थिर अक्षर *name; /* मित्रly name क्रम debug, e.g. lockdep classes */
पूर्ण;

क्रमागत i915_map_type अणु
	I915_MAP_WB = 0,
	I915_MAP_WC,
#घोषणा I915_MAP_OVERRIDE BIT(31)
	I915_MAP_FORCE_WB = I915_MAP_WB | I915_MAP_OVERRIDE,
	I915_MAP_FORCE_WC = I915_MAP_WC | I915_MAP_OVERRIDE,
पूर्ण;

क्रमागत i915_mmap_type अणु
	I915_MMAP_TYPE_GTT = 0,
	I915_MMAP_TYPE_WC,
	I915_MMAP_TYPE_WB,
	I915_MMAP_TYPE_UC,
पूर्ण;

काष्ठा i915_mmap_offset अणु
	काष्ठा drm_vma_offset_node vma_node;
	काष्ठा drm_i915_gem_object *obj;
	क्रमागत i915_mmap_type mmap_type;

	काष्ठा rb_node offset;
पूर्ण;

काष्ठा i915_gem_object_page_iter अणु
	काष्ठा scatterlist *sg_pos;
	अचिन्हित पूर्णांक sg_idx; /* in pages, but 32bit eek! */

	काष्ठा radix_tree_root radix;
	काष्ठा mutex lock; /* protects this cache */
पूर्ण;

काष्ठा drm_i915_gem_object अणु
	काष्ठा drm_gem_object base;

	स्थिर काष्ठा drm_i915_gem_object_ops *ops;

	काष्ठा अणु
		/**
		 * @vma.lock: protect the list/tree of vmas
		 */
		spinlock_t lock;

		/**
		 * @vma.list: List of VMAs backed by this object
		 *
		 * The VMA on this list are ordered by type, all GGTT vma are
		 * placed at the head and all ppGTT vma are placed at the tail.
		 * The dअगरferent types of GGTT vma are unordered between
		 * themselves, use the @vma.tree (which has a defined order
		 * between all VMA) to quickly find an exact match.
		 */
		काष्ठा list_head list;

		/**
		 * @vma.tree: Ordered tree of VMAs backed by this object
		 *
		 * All VMA created क्रम this object are placed in the @vma.tree
		 * क्रम fast retrieval via a binary search in
		 * i915_vma_instance(). They are also added to @vma.list क्रम
		 * easy iteration.
		 */
		काष्ठा rb_root tree;
	पूर्ण vma;

	/**
	 * @lut_list: List of vma lookup entries in use क्रम this object.
	 *
	 * If this object is बंदd, we need to हटाओ all of its VMA from
	 * the fast lookup index in associated contexts; @lut_list provides
	 * this translation from object to context->handles_vma.
	 */
	काष्ठा list_head lut_list;
	spinlock_t lut_lock; /* guards lut_list */

	/**
	 * @obj_link: Link पूर्णांकo @i915_gem_ww_ctx.obj_list
	 *
	 * When we lock this object through i915_gem_object_lock() with a
	 * context, we add it to the list to ensure we can unlock everything
	 * when i915_gem_ww_ctx_backoff() or i915_gem_ww_ctx_fini() are called.
	 */
	काष्ठा list_head obj_link;

	जोड़ अणु
		काष्ठा rcu_head rcu;
		काष्ठा llist_node मुक्तd;
	पूर्ण;

	/**
	 * Whether the object is currently in the GGTT mmap.
	 */
	अचिन्हित पूर्णांक userfault_count;
	काष्ठा list_head userfault_link;

	काष्ठा अणु
		spinlock_t lock; /* Protects access to mmo offsets */
		काष्ठा rb_root offsets;
	पूर्ण mmo;

	I915_SELFTEST_DECLARE(काष्ठा list_head st_link);

	अचिन्हित दीर्घ flags;
#घोषणा I915_BO_ALLOC_CONTIGUOUS BIT(0)
#घोषणा I915_BO_ALLOC_VOLATILE   BIT(1)
#घोषणा I915_BO_ALLOC_STRUCT_PAGE BIT(2)
#घोषणा I915_BO_ALLOC_FLAGS (I915_BO_ALLOC_CONTIGUOUS | \
			     I915_BO_ALLOC_VOLATILE | \
			     I915_BO_ALLOC_STRUCT_PAGE)
#घोषणा I915_BO_READONLY         BIT(3)
#घोषणा I915_TILING_QUIRK_BIT    4 /* unknown swizzling; करो not release! */

	/*
	 * Is the object to be mapped as पढ़ो-only to the GPU
	 * Only honoured अगर hardware has relevant pte bit
	 */
	अचिन्हित पूर्णांक cache_level:3;
	अचिन्हित पूर्णांक cache_coherent:2;
#घोषणा I915_BO_CACHE_COHERENT_FOR_READ BIT(0)
#घोषणा I915_BO_CACHE_COHERENT_FOR_WRITE BIT(1)
	अचिन्हित पूर्णांक cache_dirty:1;

	/**
	 * @पढ़ो_करोमुख्यs: Read memory करोमुख्यs.
	 *
	 * These monitor which caches contain पढ़ो/ग_लिखो data related to the
	 * object. When transitioning from one set of करोमुख्यs to another,
	 * the driver is called to ensure that caches are suitably flushed and
	 * invalidated.
	 */
	u16 पढ़ो_करोमुख्यs;

	/**
	 * @ग_लिखो_करोमुख्य: Corresponding unique ग_लिखो memory करोमुख्य.
	 */
	u16 ग_लिखो_करोमुख्य;

	काष्ठा पूर्णांकel_frontbuffer __rcu *frontbuffer;

	/** Current tiling stride क्रम the object, अगर it's tiled. */
	अचिन्हित पूर्णांक tiling_and_stride;
#घोषणा FENCE_MINIMUM_STRIDE 128 /* See i915_tiling_ok() */
#घोषणा TILING_MASK (FENCE_MINIMUM_STRIDE - 1)
#घोषणा STRIDE_MASK (~TILING_MASK)

	काष्ठा अणु
		/*
		 * Protects the pages and their use. Do not use directly, but
		 * instead go through the pin/unpin पूर्णांकerfaces.
		 */
		atomic_t pages_pin_count;
		atomic_t shrink_pin;

		/**
		 * Memory region क्रम this object.
		 */
		काष्ठा पूर्णांकel_memory_region *region;
		/**
		 * List of memory region blocks allocated क्रम this object.
		 */
		काष्ठा list_head blocks;
		/**
		 * Element within memory_region->objects or region->purgeable
		 * अगर the object is marked as DONTNEED. Access is रक्षित by
		 * region->obj_lock.
		 */
		काष्ठा list_head region_link;

		काष्ठा sg_table *pages;
		व्योम *mapping;

		काष्ठा i915_page_sizes अणु
			/**
			 * The sg mask of the pages sg_table. i.e the mask of
			 * of the lengths क्रम each sg entry.
			 */
			अचिन्हित पूर्णांक phys;

			/**
			 * The gtt page sizes we are allowed to use given the
			 * sg mask and the supported page sizes. This will
			 * express the smallest unit we can use क्रम the whole
			 * object, as well as the larger sizes we may be able
			 * to use opportunistically.
			 */
			अचिन्हित पूर्णांक sg;

			/**
			 * The actual gtt page size usage. Since we can have
			 * multiple vma associated with this object we need to
			 * prevent any trampling of state, hence a copy of this
			 * काष्ठा also lives in each vma, thereक्रमe the gtt
			 * value here should only be पढ़ो/ग_लिखो through the vma.
			 */
			अचिन्हित पूर्णांक gtt;
		पूर्ण page_sizes;

		I915_SELFTEST_DECLARE(अचिन्हित पूर्णांक page_mask);

		काष्ठा i915_gem_object_page_iter get_page;
		काष्ठा i915_gem_object_page_iter get_dma_page;

		/**
		 * Element within i915->mm.unbound_list or i915->mm.bound_list,
		 * locked by i915->mm.obj_lock.
		 */
		काष्ठा list_head link;

		/**
		 * Advice: are the backing pages purgeable?
		 */
		अचिन्हित पूर्णांक madv:2;

		/**
		 * This is set अगर the object has been written to since the
		 * pages were last acquired.
		 */
		bool dirty:1;
	पूर्ण mm;

	/** Record of address bit 17 of each page at last unbind. */
	अचिन्हित दीर्घ *bit_17;

	जोड़ अणु
#अगर_घोषित CONFIG_MMU_NOTIFIER
		काष्ठा i915_gem_userptr अणु
			uपूर्णांकptr_t ptr;
			अचिन्हित दीर्घ notअगरier_seq;

			काष्ठा mmu_पूर्णांकerval_notअगरier notअगरier;
			काष्ठा page **pvec;
			पूर्णांक page_ref;
		पूर्ण userptr;
#पूर्ण_अगर

		काष्ठा drm_mm_node *stolen;

		अचिन्हित दीर्घ scratch;
		u64 encode;

		व्योम *gvt_info;
	पूर्ण;
पूर्ण;

अटल अंतरभूत काष्ठा drm_i915_gem_object *
to_पूर्णांकel_bo(काष्ठा drm_gem_object *gem)
अणु
	/* Assert that to_पूर्णांकel_bo(शून्य) == शून्य */
	BUILD_BUG_ON(दुरत्व(काष्ठा drm_i915_gem_object, base));

	वापस container_of(gem, काष्ठा drm_i915_gem_object, base);
पूर्ण

#पूर्ण_अगर
