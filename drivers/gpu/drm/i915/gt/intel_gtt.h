<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 *
 * Please try to मुख्यtain the following order within this file unless it makes
 * sense to करो otherwise. From top to bottom:
 * 1. प्रकारs
 * 2. #घोषणाs, and macros
 * 3. काष्ठाure definitions
 * 4. function prototypes
 *
 * Within each section, please try to order by generation in ascending order,
 * from top to bottom (ie. gen6 on the top, gen8 on the bottom).
 */

#अगर_अघोषित __INTEL_GTT_H__
#घोषणा __INTEL_GTT_H__

#समावेश <linux/io-mapping.h>
#समावेश <linux/kref.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/workqueue.h>

#समावेश <drm/drm_mm.h>

#समावेश "gt/intel_reset.h"
#समावेश "i915_selftest.h"
#समावेश "i915_vma_types.h"

#घोषणा I915_GFP_ALLOW_FAIL (GFP_KERNEL | __GFP_RETRY_MAYFAIL | __GFP_NOWARN)

#अगर IS_ENABLED(CONFIG_DRM_I915_TRACE_GTT)
#घोषणा DBG(...) trace_prपूर्णांकk(__VA_ARGS__)
#अन्यथा
#घोषणा DBG(...)
#पूर्ण_अगर

#घोषणा NALLOC 3 /* 1 normal, 1 क्रम concurrent thपढ़ोs, 1 क्रम pपुनः_स्मृतिation */

#घोषणा I915_GTT_PAGE_SIZE_4K	BIT_ULL(12)
#घोषणा I915_GTT_PAGE_SIZE_64K	BIT_ULL(16)
#घोषणा I915_GTT_PAGE_SIZE_2M	BIT_ULL(21)

#घोषणा I915_GTT_PAGE_SIZE I915_GTT_PAGE_SIZE_4K
#घोषणा I915_GTT_MAX_PAGE_SIZE I915_GTT_PAGE_SIZE_2M

#घोषणा I915_GTT_PAGE_MASK -I915_GTT_PAGE_SIZE

#घोषणा I915_GTT_MIN_ALIGNMENT I915_GTT_PAGE_SIZE

#घोषणा I915_FENCE_REG_NONE -1
#घोषणा I915_MAX_NUM_FENCES 32
/* 32 fences + sign bit क्रम FENCE_REG_NONE */
#घोषणा I915_MAX_NUM_FENCE_BITS 6

प्रकार u32 gen6_pte_t;
प्रकार u64 gen8_pte_t;

#घोषणा ggtt_total_entries(ggtt) ((ggtt)->vm.total >> PAGE_SHIFT)

#घोषणा I915_PTES(pte_len)		((अचिन्हित पूर्णांक)(PAGE_SIZE / (pte_len)))
#घोषणा I915_PTE_MASK(pte_len)		(I915_PTES(pte_len) - 1)
#घोषणा I915_PDES			512
#घोषणा I915_PDE_MASK			(I915_PDES - 1)

/* gen6-hsw has bit 11-4 क्रम physical addr bit 39-32 */
#घोषणा GEN6_GTT_ADDR_ENCODE(addr)	((addr) | (((addr) >> 28) & 0xff0))
#घोषणा GEN6_PTE_ADDR_ENCODE(addr)	GEN6_GTT_ADDR_ENCODE(addr)
#घोषणा GEN6_PDE_ADDR_ENCODE(addr)	GEN6_GTT_ADDR_ENCODE(addr)
#घोषणा GEN6_PTE_CACHE_LLC		(2 << 1)
#घोषणा GEN6_PTE_UNCACHED		(1 << 1)
#घोषणा GEN6_PTE_VALID			REG_BIT(0)

#घोषणा GEN6_PTES			I915_PTES(माप(gen6_pte_t))
#घोषणा GEN6_PD_SIZE		        (I915_PDES * PAGE_SIZE)
#घोषणा GEN6_PD_ALIGN			(PAGE_SIZE * 16)
#घोषणा GEN6_PDE_SHIFT			22
#घोषणा GEN6_PDE_VALID			REG_BIT(0)
#घोषणा NUM_PTE(pde_shअगरt)     (1 << (pde_shअगरt - PAGE_SHIFT))

#घोषणा GEN7_PTE_CACHE_L3_LLC		(3 << 1)

#घोषणा BYT_PTE_SNOOPED_BY_CPU_CACHES	REG_BIT(2)
#घोषणा BYT_PTE_WRITEABLE		REG_BIT(1)

#घोषणा GEN12_PPGTT_PTE_LM	BIT_ULL(11)

#घोषणा GEN12_GGTT_PTE_LM	BIT_ULL(1)

/*
 * Cacheability Control is a 4-bit value. The low three bits are stored in bits
 * 3:1 of the PTE, जबतक the fourth bit is stored in bit 11 of the PTE.
 */
#घोषणा HSW_CACHEABILITY_CONTROL(bits)	((((bits) & 0x7) << 1) | \
					 (((bits) & 0x8) << (11 - 3)))
#घोषणा HSW_WB_LLC_AGE3			HSW_CACHEABILITY_CONTROL(0x2)
#घोषणा HSW_WB_LLC_AGE0			HSW_CACHEABILITY_CONTROL(0x3)
#घोषणा HSW_WB_ELLC_LLC_AGE3		HSW_CACHEABILITY_CONTROL(0x8)
#घोषणा HSW_WB_ELLC_LLC_AGE0		HSW_CACHEABILITY_CONTROL(0xb)
#घोषणा HSW_WT_ELLC_LLC_AGE3		HSW_CACHEABILITY_CONTROL(0x7)
#घोषणा HSW_WT_ELLC_LLC_AGE0		HSW_CACHEABILITY_CONTROL(0x6)
#घोषणा HSW_PTE_UNCACHED		(0)
#घोषणा HSW_GTT_ADDR_ENCODE(addr)	((addr) | (((addr) >> 28) & 0x7f0))
#घोषणा HSW_PTE_ADDR_ENCODE(addr)	HSW_GTT_ADDR_ENCODE(addr)

/*
 * GEN8 32b style address is defined as a 3 level page table:
 * 31:30 | 29:21 | 20:12 |  11:0
 * PDPE  |  PDE  |  PTE  | offset
 * The dअगरference as compared to normal x86 3 level page table is the PDPEs are
 * programmed via रेजिस्टर.
 *
 * GEN8 48b style address is defined as a 4 level page table:
 * 47:39 | 38:30 | 29:21 | 20:12 |  11:0
 * PML4E | PDPE  |  PDE  |  PTE  | offset
 */
#घोषणा GEN8_3LVL_PDPES			4

#घोषणा PPAT_UNCACHED			(_PAGE_PWT | _PAGE_PCD)
#घोषणा PPAT_CACHED_PDE			0 /* WB LLC */
#घोषणा PPAT_CACHED			_PAGE_PAT /* WB LLCeLLC */
#घोषणा PPAT_DISPLAY_ELLC		_PAGE_PCD /* WT eLLC */

#घोषणा CHV_PPAT_SNOOP			REG_BIT(6)
#घोषणा GEN8_PPAT_AGE(x)		((x)<<4)
#घोषणा GEN8_PPAT_LLCeLLC		(3<<2)
#घोषणा GEN8_PPAT_LLCELLC		(2<<2)
#घोषणा GEN8_PPAT_LLC			(1<<2)
#घोषणा GEN8_PPAT_WB			(3<<0)
#घोषणा GEN8_PPAT_WT			(2<<0)
#घोषणा GEN8_PPAT_WC			(1<<0)
#घोषणा GEN8_PPAT_UC			(0<<0)
#घोषणा GEN8_PPAT_ELLC_OVERRIDE		(0<<2)
#घोषणा GEN8_PPAT(i, x)			((u64)(x) << ((i) * 8))

#घोषणा GEN8_PDE_IPS_64K BIT(11)
#घोषणा GEN8_PDE_PS_2M   BIT(7)

क्रमागत i915_cache_level;

काष्ठा drm_i915_file_निजी;
काष्ठा drm_i915_gem_object;
काष्ठा i915_fence_reg;
काष्ठा i915_vma;
काष्ठा पूर्णांकel_gt;

#घोषणा क्रम_each_sgt_daddr(__dp, __iter, __sgt) \
	__क्रम_each_sgt_daddr(__dp, __iter, __sgt, I915_GTT_PAGE_SIZE)

काष्ठा i915_page_table अणु
	काष्ठा drm_i915_gem_object *base;
	जोड़ अणु
		atomic_t used;
		काष्ठा i915_page_table *stash;
	पूर्ण;
पूर्ण;

काष्ठा i915_page_directory अणु
	काष्ठा i915_page_table pt;
	spinlock_t lock;
	व्योम **entry;
पूर्ण;

#घोषणा __px_choose_expr(x, type, expr, other) \
	__builtin_choose_expr( \
	__builtin_types_compatible_p(typeof(x), type) || \
	__builtin_types_compatible_p(typeof(x), स्थिर type), \
	(अणु type __x = (type)(x); expr; पूर्ण), \
	other)

#घोषणा px_base(px) \
	__px_choose_expr(px, काष्ठा drm_i915_gem_object *, __x, \
	__px_choose_expr(px, काष्ठा i915_page_table *, __x->base, \
	__px_choose_expr(px, काष्ठा i915_page_directory *, __x->pt.base, \
	(व्योम)0)))

काष्ठा page *__px_page(काष्ठा drm_i915_gem_object *p);
dma_addr_t __px_dma(काष्ठा drm_i915_gem_object *p);
#घोषणा px_dma(px) (__px_dma(px_base(px)))

#घोषणा px_pt(px) \
	__px_choose_expr(px, काष्ठा i915_page_table *, __x, \
	__px_choose_expr(px, काष्ठा i915_page_directory *, &__x->pt, \
	(व्योम)0))
#घोषणा px_used(px) (&px_pt(px)->used)

काष्ठा i915_vm_pt_stash अणु
	/* pपुनः_स्मृतिated chains of page tables/directories */
	काष्ठा i915_page_table *pt[2];
पूर्ण;

काष्ठा i915_vma_ops अणु
	/* Map an object पूर्णांकo an address space with the given cache flags. */
	व्योम (*bind_vma)(काष्ठा i915_address_space *vm,
			 काष्ठा i915_vm_pt_stash *stash,
			 काष्ठा i915_vma *vma,
			 क्रमागत i915_cache_level cache_level,
			 u32 flags);
	/*
	 * Unmap an object from an address space. This usually consists of
	 * setting the valid PTE entries to a reserved scratch page.
	 */
	व्योम (*unbind_vma)(काष्ठा i915_address_space *vm,
			   काष्ठा i915_vma *vma);

	पूर्णांक (*set_pages)(काष्ठा i915_vma *vma);
	व्योम (*clear_pages)(काष्ठा i915_vma *vma);
पूर्ण;

काष्ठा i915_address_space अणु
	काष्ठा kref ref;
	काष्ठा rcu_work rcu;

	काष्ठा drm_mm mm;
	काष्ठा पूर्णांकel_gt *gt;
	काष्ठा drm_i915_निजी *i915;
	काष्ठा device *dma;
	/*
	 * Every address space beदीर्घs to a काष्ठा file - except क्रम the global
	 * GTT that is owned by the driver (and so @file is set to शून्य). In
	 * principle, no inक्रमmation should leak from one context to another
	 * (or between files/processes etc) unless explicitly shared by the
	 * owner. Tracking the owner is important in order to मुक्त up per-file
	 * objects aदीर्घ with the file, to aide resource tracking, and to
	 * assign blame.
	 */
	काष्ठा drm_i915_file_निजी *file;
	u64 total;		/* size addr space maps (ex. 2GB क्रम ggtt) */
	u64 reserved;		/* size addr space reserved */

	अचिन्हित पूर्णांक bind_async_flags;

	/*
	 * Each active user context has its own address space (in full-ppgtt).
	 * Since the vm may be shared between multiple contexts, we count how
	 * many contexts keep us "open". Once खोलो hits zero, we are बंदd
	 * and करो not allow any new attachments, and proceed to shutकरोwn our
	 * vma and page directories.
	 */
	atomic_t खोलो;

	काष्ठा mutex mutex; /* protects vma and our lists */
	काष्ठा dma_resv resv; /* reservation lock क्रम all pd objects, and buffer pool */
#घोषणा VM_CLASS_GGTT 0
#घोषणा VM_CLASS_PPGTT 1

	काष्ठा drm_i915_gem_object *scratch[4];
	/**
	 * List of vma currently bound.
	 */
	काष्ठा list_head bound_list;

	/* Global GTT */
	bool is_ggtt:1;

	/* Some प्रणालीs support पढ़ो-only mappings क्रम GGTT and/or PPGTT */
	bool has_पढ़ो_only:1;

	u8 top;
	u8 pd_shअगरt;
	u8 scratch_order;

	काष्ठा drm_i915_gem_object *
		(*alloc_pt_dma)(काष्ठा i915_address_space *vm, पूर्णांक sz);

	u64 (*pte_encode)(dma_addr_t addr,
			  क्रमागत i915_cache_level level,
			  u32 flags); /* Create a valid PTE */
#घोषणा PTE_READ_ONLY	BIT(0)
#घोषणा PTE_LM		BIT(1)

	व्योम (*allocate_va_range)(काष्ठा i915_address_space *vm,
				  काष्ठा i915_vm_pt_stash *stash,
				  u64 start, u64 length);
	व्योम (*clear_range)(काष्ठा i915_address_space *vm,
			    u64 start, u64 length);
	व्योम (*insert_page)(काष्ठा i915_address_space *vm,
			    dma_addr_t addr,
			    u64 offset,
			    क्रमागत i915_cache_level cache_level,
			    u32 flags);
	व्योम (*insert_entries)(काष्ठा i915_address_space *vm,
			       काष्ठा i915_vma *vma,
			       क्रमागत i915_cache_level cache_level,
			       u32 flags);
	व्योम (*cleanup)(काष्ठा i915_address_space *vm);

	काष्ठा i915_vma_ops vma_ops;

	I915_SELFTEST_DECLARE(काष्ठा fault_attr fault_attr);
	I915_SELFTEST_DECLARE(bool scrub_64K);
पूर्ण;

/*
 * The Graphics Translation Table is the way in which GEN hardware translates a
 * Graphics Virtual Address पूर्णांकo a Physical Address. In addition to the normal
 * collateral associated with any va->pa translations GEN hardware also has a
 * portion of the GTT which can be mapped by the CPU and reमुख्य both coherent
 * and correct (in हालs like swizzling). That region is referred to as GMADR in
 * the spec.
 */
काष्ठा i915_ggtt अणु
	काष्ठा i915_address_space vm;

	काष्ठा io_mapping iomap;	/* Mapping to our CPU mappable region */
	काष्ठा resource gmadr;          /* GMADR resource */
	resource_माप_प्रकार mappable_end;	/* End offset that we can CPU map */

	/** "Graphics Stolen Memory" holds the global PTEs */
	व्योम __iomem *gsm;
	व्योम (*invalidate)(काष्ठा i915_ggtt *ggtt);

	/** PPGTT used क्रम aliasing the PPGTT with the GTT */
	काष्ठा i915_ppgtt *alias;

	bool करो_idle_maps;

	पूर्णांक mtrr;

	/** Bit 6 swizzling required क्रम X tiling */
	u32 bit_6_swizzle_x;
	/** Bit 6 swizzling required क्रम Y tiling */
	u32 bit_6_swizzle_y;

	u32 pin_bias;

	अचिन्हित पूर्णांक num_fences;
	काष्ठा i915_fence_reg *fence_regs;
	काष्ठा list_head fence_list;

	/**
	 * List of all objects in gtt_space, currently mmaped by userspace.
	 * All objects within this list must also be on bound_list.
	 */
	काष्ठा list_head userfault_list;

	/* Manual runसमय pm स्वतःsuspend delay क्रम user GGTT mmaps */
	काष्ठा पूर्णांकel_wakeref_स्वतः userfault_wakeref;

	काष्ठा mutex error_mutex;
	काष्ठा drm_mm_node error_capture;
	काष्ठा drm_mm_node uc_fw;
पूर्ण;

काष्ठा i915_ppgtt अणु
	काष्ठा i915_address_space vm;

	काष्ठा i915_page_directory *pd;
पूर्ण;

#घोषणा i915_is_ggtt(vm) ((vm)->is_ggtt)

पूर्णांक __must_check
i915_vm_lock_objects(काष्ठा i915_address_space *vm, काष्ठा i915_gem_ww_ctx *ww);

अटल अंतरभूत bool
i915_vm_is_4lvl(स्थिर काष्ठा i915_address_space *vm)
अणु
	वापस (vm->total - 1) >> 32;
पूर्ण

अटल अंतरभूत bool
i915_vm_has_scratch_64K(काष्ठा i915_address_space *vm)
अणु
	वापस vm->scratch_order == get_order(I915_GTT_PAGE_SIZE_64K);
पूर्ण

अटल अंतरभूत bool
i915_vm_has_cache_coloring(काष्ठा i915_address_space *vm)
अणु
	वापस i915_is_ggtt(vm) && vm->mm.color_adjust;
पूर्ण

अटल अंतरभूत काष्ठा i915_ggtt *
i915_vm_to_ggtt(काष्ठा i915_address_space *vm)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा i915_ggtt, vm));
	GEM_BUG_ON(!i915_is_ggtt(vm));
	वापस container_of(vm, काष्ठा i915_ggtt, vm);
पूर्ण

अटल अंतरभूत काष्ठा i915_ppgtt *
i915_vm_to_ppgtt(काष्ठा i915_address_space *vm)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा i915_ppgtt, vm));
	GEM_BUG_ON(i915_is_ggtt(vm));
	वापस container_of(vm, काष्ठा i915_ppgtt, vm);
पूर्ण

अटल अंतरभूत काष्ठा i915_address_space *
i915_vm_get(काष्ठा i915_address_space *vm)
अणु
	kref_get(&vm->ref);
	वापस vm;
पूर्ण

व्योम i915_vm_release(काष्ठा kref *kref);

अटल अंतरभूत व्योम i915_vm_put(काष्ठा i915_address_space *vm)
अणु
	kref_put(&vm->ref, i915_vm_release);
पूर्ण

अटल अंतरभूत काष्ठा i915_address_space *
i915_vm_खोलो(काष्ठा i915_address_space *vm)
अणु
	GEM_BUG_ON(!atomic_पढ़ो(&vm->खोलो));
	atomic_inc(&vm->खोलो);
	वापस i915_vm_get(vm);
पूर्ण

अटल अंतरभूत bool
i915_vm_tryखोलो(काष्ठा i915_address_space *vm)
अणु
	अगर (atomic_add_unless(&vm->खोलो, 1, 0))
		वापस i915_vm_get(vm);

	वापस false;
पूर्ण

व्योम __i915_vm_बंद(काष्ठा i915_address_space *vm);

अटल अंतरभूत व्योम
i915_vm_बंद(काष्ठा i915_address_space *vm)
अणु
	GEM_BUG_ON(!atomic_पढ़ो(&vm->खोलो));
	__i915_vm_बंद(vm);

	i915_vm_put(vm);
पूर्ण

व्योम i915_address_space_init(काष्ठा i915_address_space *vm, पूर्णांक subclass);
व्योम i915_address_space_fini(काष्ठा i915_address_space *vm);

अटल अंतरभूत u32 i915_pte_index(u64 address, अचिन्हित पूर्णांक pde_shअगरt)
अणु
	स्थिर u32 mask = NUM_PTE(pde_shअगरt) - 1;

	वापस (address >> PAGE_SHIFT) & mask;
पूर्ण

/*
 * Helper to counts the number of PTEs within the given length. This count
 * करोes not cross a page table boundary, so the max value would be
 * GEN6_PTES क्रम GEN6, and GEN8_PTES क्रम GEN8.
 */
अटल अंतरभूत u32 i915_pte_count(u64 addr, u64 length, अचिन्हित पूर्णांक pde_shअगरt)
अणु
	स्थिर u64 mask = ~((1ULL << pde_shअगरt) - 1);
	u64 end;

	GEM_BUG_ON(length == 0);
	GEM_BUG_ON(offset_in_page(addr | length));

	end = addr + length;

	अगर ((addr & mask) != (end & mask))
		वापस NUM_PTE(pde_shअगरt) - i915_pte_index(addr, pde_shअगरt);

	वापस i915_pte_index(end, pde_shअगरt) - i915_pte_index(addr, pde_shअगरt);
पूर्ण

अटल अंतरभूत u32 i915_pde_index(u64 addr, u32 shअगरt)
अणु
	वापस (addr >> shअगरt) & I915_PDE_MASK;
पूर्ण

अटल अंतरभूत काष्ठा i915_page_table *
i915_pt_entry(स्थिर काष्ठा i915_page_directory * स्थिर pd,
	      स्थिर अचिन्हित लघु n)
अणु
	वापस pd->entry[n];
पूर्ण

अटल अंतरभूत काष्ठा i915_page_directory *
i915_pd_entry(स्थिर काष्ठा i915_page_directory * स्थिर pdp,
	      स्थिर अचिन्हित लघु n)
अणु
	वापस pdp->entry[n];
पूर्ण

अटल अंतरभूत dma_addr_t
i915_page_dir_dma_addr(स्थिर काष्ठा i915_ppgtt *ppgtt, स्थिर अचिन्हित पूर्णांक n)
अणु
	काष्ठा i915_page_table *pt = ppgtt->pd->entry[n];

	वापस __px_dma(pt ? px_base(pt) : ppgtt->vm.scratch[ppgtt->vm.top]);
पूर्ण

व्योम ppgtt_init(काष्ठा i915_ppgtt *ppgtt, काष्ठा पूर्णांकel_gt *gt);

पूर्णांक i915_ggtt_probe_hw(काष्ठा drm_i915_निजी *i915);
पूर्णांक i915_ggtt_init_hw(काष्ठा drm_i915_निजी *i915);
पूर्णांक i915_ggtt_enable_hw(काष्ठा drm_i915_निजी *i915);
व्योम i915_ggtt_enable_guc(काष्ठा i915_ggtt *ggtt);
व्योम i915_ggtt_disable_guc(काष्ठा i915_ggtt *ggtt);
पूर्णांक i915_init_ggtt(काष्ठा drm_i915_निजी *i915);
व्योम i915_ggtt_driver_release(काष्ठा drm_i915_निजी *i915);

अटल अंतरभूत bool i915_ggtt_has_aperture(स्थिर काष्ठा i915_ggtt *ggtt)
अणु
	वापस ggtt->mappable_end > 0;
पूर्ण

पूर्णांक i915_ppgtt_init_hw(काष्ठा पूर्णांकel_gt *gt);

काष्ठा i915_ppgtt *i915_ppgtt_create(काष्ठा पूर्णांकel_gt *gt);

व्योम i915_ggtt_suspend(काष्ठा i915_ggtt *gtt);
व्योम i915_ggtt_resume(काष्ठा i915_ggtt *ggtt);

#घोषणा kmap_atomic_px(px) kmap_atomic(__px_page(px_base(px)))

व्योम
fill_page_dma(काष्ठा drm_i915_gem_object *p, स्थिर u64 val, अचिन्हित पूर्णांक count);

#घोषणा fill_px(px, v) fill_page_dma(px_base(px), (v), PAGE_SIZE / माप(u64))
#घोषणा fill32_px(px, v) करो अणु						\
	u64 v__ = lower_32_bits(v);					\
	fill_px((px), v__ << 32 | v__);					\
पूर्ण जबतक (0)

पूर्णांक setup_scratch_page(काष्ठा i915_address_space *vm);
व्योम मुक्त_scratch(काष्ठा i915_address_space *vm);

काष्ठा drm_i915_gem_object *alloc_pt_dma(काष्ठा i915_address_space *vm, पूर्णांक sz);
काष्ठा i915_page_table *alloc_pt(काष्ठा i915_address_space *vm);
काष्ठा i915_page_directory *alloc_pd(काष्ठा i915_address_space *vm);
काष्ठा i915_page_directory *__alloc_pd(पूर्णांक npde);

पूर्णांक pin_pt_dma(काष्ठा i915_address_space *vm, काष्ठा drm_i915_gem_object *obj);
पूर्णांक pin_pt_dma_locked(काष्ठा i915_address_space *vm, काष्ठा drm_i915_gem_object *obj);

व्योम मुक्त_px(काष्ठा i915_address_space *vm,
	     काष्ठा i915_page_table *pt, पूर्णांक lvl);
#घोषणा मुक्त_pt(vm, px) मुक्त_px(vm, px, 0)
#घोषणा मुक्त_pd(vm, px) मुक्त_px(vm, px_pt(px), 1)

व्योम
__set_pd_entry(काष्ठा i915_page_directory * स्थिर pd,
	       स्थिर अचिन्हित लघु idx,
	       काष्ठा i915_page_table *pt,
	       u64 (*encode)(स्थिर dma_addr_t, स्थिर क्रमागत i915_cache_level));

#घोषणा set_pd_entry(pd, idx, to) \
	__set_pd_entry((pd), (idx), px_pt(to), gen8_pde_encode)

व्योम
clear_pd_entry(काष्ठा i915_page_directory * स्थिर pd,
	       स्थिर अचिन्हित लघु idx,
	       स्थिर काष्ठा drm_i915_gem_object * स्थिर scratch);

bool
release_pd_entry(काष्ठा i915_page_directory * स्थिर pd,
		 स्थिर अचिन्हित लघु idx,
		 काष्ठा i915_page_table * स्थिर pt,
		 स्थिर काष्ठा drm_i915_gem_object * स्थिर scratch);
व्योम gen6_ggtt_invalidate(काष्ठा i915_ggtt *ggtt);

पूर्णांक ggtt_set_pages(काष्ठा i915_vma *vma);
पूर्णांक ppgtt_set_pages(काष्ठा i915_vma *vma);
व्योम clear_pages(काष्ठा i915_vma *vma);

व्योम ppgtt_bind_vma(काष्ठा i915_address_space *vm,
		    काष्ठा i915_vm_pt_stash *stash,
		    काष्ठा i915_vma *vma,
		    क्रमागत i915_cache_level cache_level,
		    u32 flags);
व्योम ppgtt_unbind_vma(काष्ठा i915_address_space *vm,
		      काष्ठा i915_vma *vma);

व्योम gtt_ग_लिखो_workarounds(काष्ठा पूर्णांकel_gt *gt);

व्योम setup_निजी_pat(काष्ठा पूर्णांकel_uncore *uncore);

पूर्णांक i915_vm_alloc_pt_stash(काष्ठा i915_address_space *vm,
			   काष्ठा i915_vm_pt_stash *stash,
			   u64 size);
पूर्णांक i915_vm_pin_pt_stash(काष्ठा i915_address_space *vm,
			 काष्ठा i915_vm_pt_stash *stash);
व्योम i915_vm_मुक्त_pt_stash(काष्ठा i915_address_space *vm,
			   काष्ठा i915_vm_pt_stash *stash);

काष्ठा i915_vma *
__vm_create_scratch_क्रम_पढ़ो(काष्ठा i915_address_space *vm, अचिन्हित दीर्घ size);

काष्ठा i915_vma *
__vm_create_scratch_क्रम_पढ़ो_pinned(काष्ठा i915_address_space *vm, अचिन्हित दीर्घ size);

अटल अंतरभूत काष्ठा sgt_dma अणु
	काष्ठा scatterlist *sg;
	dma_addr_t dma, max;
पूर्ण sgt_dma(काष्ठा i915_vma *vma) अणु
	काष्ठा scatterlist *sg = vma->pages->sgl;
	dma_addr_t addr = sg_dma_address(sg);

	वापस (काष्ठा sgt_dma)अणु sg, addr, addr + sg_dma_len(sg) पूर्ण;
पूर्ण

#पूर्ण_अगर
