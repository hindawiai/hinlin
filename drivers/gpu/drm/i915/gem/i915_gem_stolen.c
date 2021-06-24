<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2008-2012 Intel Corporation
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mutex.h>

#समावेश <drm/drm_mm.h>
#समावेश <drm/i915_drm.h>

#समावेश "gem/i915_gem_region.h"
#समावेश "i915_drv.h"
#समावेश "i915_gem_stolen.h"
#समावेश "i915_vgpu.h"

/*
 * The BIOS typically reserves some of the प्रणाली's memory क्रम the exclusive
 * use of the पूर्णांकegrated graphics. This memory is no दीर्घer available क्रम
 * use by the OS and so the user finds that his प्रणाली has less memory
 * available than he put in. We refer to this memory as stolen.
 *
 * The BIOS will allocate its framebuffer from the stolen memory. Our
 * goal is try to reuse that object क्रम our own fbcon which must always
 * be available क्रम panics. Anything अन्यथा we can reuse the stolen memory
 * क्रम is a boon.
 */

पूर्णांक i915_gem_stolen_insert_node_in_range(काष्ठा drm_i915_निजी *i915,
					 काष्ठा drm_mm_node *node, u64 size,
					 अचिन्हित alignment, u64 start, u64 end)
अणु
	पूर्णांक ret;

	अगर (!drm_mm_initialized(&i915->mm.stolen))
		वापस -ENODEV;

	/* WaSkipStolenMemoryFirstPage:bdw+ */
	अगर (INTEL_GEN(i915) >= 8 && start < 4096)
		start = 4096;

	mutex_lock(&i915->mm.stolen_lock);
	ret = drm_mm_insert_node_in_range(&i915->mm.stolen, node,
					  size, alignment, 0,
					  start, end, DRM_MM_INSERT_BEST);
	mutex_unlock(&i915->mm.stolen_lock);

	वापस ret;
पूर्ण

पूर्णांक i915_gem_stolen_insert_node(काष्ठा drm_i915_निजी *i915,
				काष्ठा drm_mm_node *node, u64 size,
				अचिन्हित alignment)
अणु
	वापस i915_gem_stolen_insert_node_in_range(i915, node,
						    size, alignment,
						    I915_GEM_STOLEN_BIAS,
						    U64_MAX);
पूर्ण

व्योम i915_gem_stolen_हटाओ_node(काष्ठा drm_i915_निजी *i915,
				 काष्ठा drm_mm_node *node)
अणु
	mutex_lock(&i915->mm.stolen_lock);
	drm_mm_हटाओ_node(node);
	mutex_unlock(&i915->mm.stolen_lock);
पूर्ण

अटल पूर्णांक i915_adjust_stolen(काष्ठा drm_i915_निजी *i915,
			      काष्ठा resource *dsm)
अणु
	काष्ठा i915_ggtt *ggtt = &i915->ggtt;
	काष्ठा पूर्णांकel_uncore *uncore = ggtt->vm.gt->uncore;
	काष्ठा resource *r;

	अगर (dsm->start == 0 || dsm->end <= dsm->start)
		वापस -EINVAL;

	/*
	 * TODO: We have yet too encounter the हाल where the GTT wasn't at the
	 * end of stolen. With that assumption we could simplअगरy this.
	 */

	/* Make sure we करोn't clobber the GTT if it's within stolen memory */
	अगर (INTEL_GEN(i915) <= 4 &&
	    !IS_G33(i915) && !IS_PINEVIEW(i915) && !IS_G4X(i915)) अणु
		काष्ठा resource stolen[2] = अणु*dsm, *dsmपूर्ण;
		काष्ठा resource ggtt_res;
		resource_माप_प्रकार ggtt_start;

		ggtt_start = पूर्णांकel_uncore_पढ़ो(uncore, PGTBL_CTL);
		अगर (IS_GEN(i915, 4))
			ggtt_start = (ggtt_start & PGTBL_ADDRESS_LO_MASK) |
				     (ggtt_start & PGTBL_ADDRESS_HI_MASK) << 28;
		अन्यथा
			ggtt_start &= PGTBL_ADDRESS_LO_MASK;

		ggtt_res =
			(काष्ठा resource) DEFINE_RES_MEM(ggtt_start,
							 ggtt_total_entries(ggtt) * 4);

		अगर (ggtt_res.start >= stolen[0].start && ggtt_res.start < stolen[0].end)
			stolen[0].end = ggtt_res.start;
		अगर (ggtt_res.end > stolen[1].start && ggtt_res.end <= stolen[1].end)
			stolen[1].start = ggtt_res.end;

		/* Pick the larger of the two chunks */
		अगर (resource_size(&stolen[0]) > resource_size(&stolen[1]))
			*dsm = stolen[0];
		अन्यथा
			*dsm = stolen[1];

		अगर (stolen[0].start != stolen[1].start ||
		    stolen[0].end != stolen[1].end) अणु
			drm_dbg(&i915->drm,
				"GTT within stolen memory at %pR\n",
				&ggtt_res);
			drm_dbg(&i915->drm, "Stolen memory adjusted to %pR\n",
				dsm);
		पूर्ण
	पूर्ण

	/*
	 * Verअगरy that nothing अन्यथा uses this physical address. Stolen
	 * memory should be reserved by the BIOS and hidden from the
	 * kernel. So अगर the region is alपढ़ोy marked as busy, something
	 * is seriously wrong.
	 */
	r = devm_request_mem_region(i915->drm.dev, dsm->start,
				    resource_size(dsm),
				    "Graphics Stolen Memory");
	अगर (r == शून्य) अणु
		/*
		 * One more attempt but this समय requesting region from
		 * start + 1, as we have seen that this resolves the region
		 * conflict with the PCI Bus.
		 * This is a BIOS w/a: Some BIOS wrap stolen in the root
		 * PCI bus, but have an off-by-one error. Hence retry the
		 * reservation starting from 1 instead of 0.
		 * There's also BIOS with off-by-one on the other end.
		 */
		r = devm_request_mem_region(i915->drm.dev, dsm->start + 1,
					    resource_size(dsm) - 2,
					    "Graphics Stolen Memory");
		/*
		 * GEN3 firmware likes to smash pci bridges पूर्णांकo the stolen
		 * range. Apparently this works.
		 */
		अगर (!r && !IS_GEN(i915, 3)) अणु
			drm_err(&i915->drm,
				"conflict detected with stolen region: %pR\n",
				dsm);

			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम i915_gem_cleanup_stolen(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (!drm_mm_initialized(&i915->mm.stolen))
		वापस;

	drm_mm_takeकरोwn(&i915->mm.stolen);
पूर्ण

अटल व्योम g4x_get_stolen_reserved(काष्ठा drm_i915_निजी *i915,
				    काष्ठा पूर्णांकel_uncore *uncore,
				    resource_माप_प्रकार *base,
				    resource_माप_प्रकार *size)
अणु
	u32 reg_val = पूर्णांकel_uncore_पढ़ो(uncore,
					IS_GM45(i915) ?
					CTG_STOLEN_RESERVED :
					ELK_STOLEN_RESERVED);
	resource_माप_प्रकार stolen_top = i915->dsm.end + 1;

	drm_dbg(&i915->drm, "%s_STOLEN_RESERVED = %08x\n",
		IS_GM45(i915) ? "CTG" : "ELK", reg_val);

	अगर ((reg_val & G4X_STOLEN_RESERVED_ENABLE) == 0)
		वापस;

	/*
	 * Whether ILK really reuses the ELK रेजिस्टर क्रम this is unclear.
	 * Let's see अगर we catch anyone with this supposedly enabled on ILK.
	 */
	drm_WARN(&i915->drm, IS_GEN(i915, 5),
		 "ILK stolen reserved found? 0x%08x\n",
		 reg_val);

	अगर (!(reg_val & G4X_STOLEN_RESERVED_ADDR2_MASK))
		वापस;

	*base = (reg_val & G4X_STOLEN_RESERVED_ADDR2_MASK) << 16;
	drm_WARN_ON(&i915->drm,
		    (reg_val & G4X_STOLEN_RESERVED_ADDR1_MASK) < *base);

	*size = stolen_top - *base;
पूर्ण

अटल व्योम gen6_get_stolen_reserved(काष्ठा drm_i915_निजी *i915,
				     काष्ठा पूर्णांकel_uncore *uncore,
				     resource_माप_प्रकार *base,
				     resource_माप_प्रकार *size)
अणु
	u32 reg_val = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_STOLEN_RESERVED);

	drm_dbg(&i915->drm, "GEN6_STOLEN_RESERVED = %08x\n", reg_val);

	अगर (!(reg_val & GEN6_STOLEN_RESERVED_ENABLE))
		वापस;

	*base = reg_val & GEN6_STOLEN_RESERVED_ADDR_MASK;

	चयन (reg_val & GEN6_STOLEN_RESERVED_SIZE_MASK) अणु
	हाल GEN6_STOLEN_RESERVED_1M:
		*size = 1024 * 1024;
		अवरोध;
	हाल GEN6_STOLEN_RESERVED_512K:
		*size = 512 * 1024;
		अवरोध;
	हाल GEN6_STOLEN_RESERVED_256K:
		*size = 256 * 1024;
		अवरोध;
	हाल GEN6_STOLEN_RESERVED_128K:
		*size = 128 * 1024;
		अवरोध;
	शेष:
		*size = 1024 * 1024;
		MISSING_CASE(reg_val & GEN6_STOLEN_RESERVED_SIZE_MASK);
	पूर्ण
पूर्ण

अटल व्योम vlv_get_stolen_reserved(काष्ठा drm_i915_निजी *i915,
				    काष्ठा पूर्णांकel_uncore *uncore,
				    resource_माप_प्रकार *base,
				    resource_माप_प्रकार *size)
अणु
	u32 reg_val = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_STOLEN_RESERVED);
	resource_माप_प्रकार stolen_top = i915->dsm.end + 1;

	drm_dbg(&i915->drm, "GEN6_STOLEN_RESERVED = %08x\n", reg_val);

	अगर (!(reg_val & GEN6_STOLEN_RESERVED_ENABLE))
		वापस;

	चयन (reg_val & GEN7_STOLEN_RESERVED_SIZE_MASK) अणु
	शेष:
		MISSING_CASE(reg_val & GEN7_STOLEN_RESERVED_SIZE_MASK);
		fallthrough;
	हाल GEN7_STOLEN_RESERVED_1M:
		*size = 1024 * 1024;
		अवरोध;
	पूर्ण

	/*
	 * On vlv, the ADDR_MASK portion is left as 0 and HW deduces the
	 * reserved location as (top - size).
	 */
	*base = stolen_top - *size;
पूर्ण

अटल व्योम gen7_get_stolen_reserved(काष्ठा drm_i915_निजी *i915,
				     काष्ठा पूर्णांकel_uncore *uncore,
				     resource_माप_प्रकार *base,
				     resource_माप_प्रकार *size)
अणु
	u32 reg_val = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_STOLEN_RESERVED);

	drm_dbg(&i915->drm, "GEN6_STOLEN_RESERVED = %08x\n", reg_val);

	अगर (!(reg_val & GEN6_STOLEN_RESERVED_ENABLE))
		वापस;

	*base = reg_val & GEN7_STOLEN_RESERVED_ADDR_MASK;

	चयन (reg_val & GEN7_STOLEN_RESERVED_SIZE_MASK) अणु
	हाल GEN7_STOLEN_RESERVED_1M:
		*size = 1024 * 1024;
		अवरोध;
	हाल GEN7_STOLEN_RESERVED_256K:
		*size = 256 * 1024;
		अवरोध;
	शेष:
		*size = 1024 * 1024;
		MISSING_CASE(reg_val & GEN7_STOLEN_RESERVED_SIZE_MASK);
	पूर्ण
पूर्ण

अटल व्योम chv_get_stolen_reserved(काष्ठा drm_i915_निजी *i915,
				    काष्ठा पूर्णांकel_uncore *uncore,
				    resource_माप_प्रकार *base,
				    resource_माप_प्रकार *size)
अणु
	u32 reg_val = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_STOLEN_RESERVED);

	drm_dbg(&i915->drm, "GEN6_STOLEN_RESERVED = %08x\n", reg_val);

	अगर (!(reg_val & GEN6_STOLEN_RESERVED_ENABLE))
		वापस;

	*base = reg_val & GEN6_STOLEN_RESERVED_ADDR_MASK;

	चयन (reg_val & GEN8_STOLEN_RESERVED_SIZE_MASK) अणु
	हाल GEN8_STOLEN_RESERVED_1M:
		*size = 1024 * 1024;
		अवरोध;
	हाल GEN8_STOLEN_RESERVED_2M:
		*size = 2 * 1024 * 1024;
		अवरोध;
	हाल GEN8_STOLEN_RESERVED_4M:
		*size = 4 * 1024 * 1024;
		अवरोध;
	हाल GEN8_STOLEN_RESERVED_8M:
		*size = 8 * 1024 * 1024;
		अवरोध;
	शेष:
		*size = 8 * 1024 * 1024;
		MISSING_CASE(reg_val & GEN8_STOLEN_RESERVED_SIZE_MASK);
	पूर्ण
पूर्ण

अटल व्योम bdw_get_stolen_reserved(काष्ठा drm_i915_निजी *i915,
				    काष्ठा पूर्णांकel_uncore *uncore,
				    resource_माप_प्रकार *base,
				    resource_माप_प्रकार *size)
अणु
	u32 reg_val = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_STOLEN_RESERVED);
	resource_माप_प्रकार stolen_top = i915->dsm.end + 1;

	drm_dbg(&i915->drm, "GEN6_STOLEN_RESERVED = %08x\n", reg_val);

	अगर (!(reg_val & GEN6_STOLEN_RESERVED_ENABLE))
		वापस;

	अगर (!(reg_val & GEN6_STOLEN_RESERVED_ADDR_MASK))
		वापस;

	*base = reg_val & GEN6_STOLEN_RESERVED_ADDR_MASK;
	*size = stolen_top - *base;
पूर्ण

अटल व्योम icl_get_stolen_reserved(काष्ठा drm_i915_निजी *i915,
				    काष्ठा पूर्णांकel_uncore *uncore,
				    resource_माप_प्रकार *base,
				    resource_माप_प्रकार *size)
अणु
	u64 reg_val = पूर्णांकel_uncore_पढ़ो64(uncore, GEN6_STOLEN_RESERVED);

	drm_dbg(&i915->drm, "GEN6_STOLEN_RESERVED = 0x%016llx\n", reg_val);

	*base = reg_val & GEN11_STOLEN_RESERVED_ADDR_MASK;

	चयन (reg_val & GEN8_STOLEN_RESERVED_SIZE_MASK) अणु
	हाल GEN8_STOLEN_RESERVED_1M:
		*size = 1024 * 1024;
		अवरोध;
	हाल GEN8_STOLEN_RESERVED_2M:
		*size = 2 * 1024 * 1024;
		अवरोध;
	हाल GEN8_STOLEN_RESERVED_4M:
		*size = 4 * 1024 * 1024;
		अवरोध;
	हाल GEN8_STOLEN_RESERVED_8M:
		*size = 8 * 1024 * 1024;
		अवरोध;
	शेष:
		*size = 8 * 1024 * 1024;
		MISSING_CASE(reg_val & GEN8_STOLEN_RESERVED_SIZE_MASK);
	पूर्ण
पूर्ण

अटल पूर्णांक i915_gem_init_stolen(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	resource_माप_प्रकार reserved_base, stolen_top;
	resource_माप_प्रकार reserved_total, reserved_size;

	mutex_init(&i915->mm.stolen_lock);

	अगर (पूर्णांकel_vgpu_active(i915)) अणु
		drm_notice(&i915->drm,
			   "%s, disabling use of stolen memory\n",
			   "iGVT-g active");
		वापस 0;
	पूर्ण

	अगर (पूर्णांकel_vtd_active() && INTEL_GEN(i915) < 8) अणु
		drm_notice(&i915->drm,
			   "%s, disabling use of stolen memory\n",
			   "DMAR active");
		वापस 0;
	पूर्ण

	अगर (resource_size(&पूर्णांकel_graphics_stolen_res) == 0)
		वापस 0;

	i915->dsm = पूर्णांकel_graphics_stolen_res;

	अगर (i915_adjust_stolen(i915, &i915->dsm))
		वापस 0;

	GEM_BUG_ON(i915->dsm.start == 0);
	GEM_BUG_ON(i915->dsm.end <= i915->dsm.start);

	stolen_top = i915->dsm.end + 1;
	reserved_base = stolen_top;
	reserved_size = 0;

	चयन (INTEL_GEN(i915)) अणु
	हाल 2:
	हाल 3:
		अवरोध;
	हाल 4:
		अगर (!IS_G4X(i915))
			अवरोध;
		fallthrough;
	हाल 5:
		g4x_get_stolen_reserved(i915, uncore,
					&reserved_base, &reserved_size);
		अवरोध;
	हाल 6:
		gen6_get_stolen_reserved(i915, uncore,
					 &reserved_base, &reserved_size);
		अवरोध;
	हाल 7:
		अगर (IS_VALLEYVIEW(i915))
			vlv_get_stolen_reserved(i915, uncore,
						&reserved_base, &reserved_size);
		अन्यथा
			gen7_get_stolen_reserved(i915, uncore,
						 &reserved_base, &reserved_size);
		अवरोध;
	हाल 8:
	हाल 9:
	हाल 10:
		अगर (IS_LP(i915))
			chv_get_stolen_reserved(i915, uncore,
						&reserved_base, &reserved_size);
		अन्यथा
			bdw_get_stolen_reserved(i915, uncore,
						&reserved_base, &reserved_size);
		अवरोध;
	शेष:
		MISSING_CASE(INTEL_GEN(i915));
		fallthrough;
	हाल 11:
	हाल 12:
		icl_get_stolen_reserved(i915, uncore,
					&reserved_base,
					&reserved_size);
		अवरोध;
	पूर्ण

	/*
	 * Our expectation is that the reserved space is at the top of the
	 * stolen region and *never* at the bottom. If we see !reserved_base,
	 * it likely means we failed to पढ़ो the रेजिस्टरs correctly.
	 */
	अगर (!reserved_base) अणु
		drm_err(&i915->drm,
			"inconsistent reservation %pa + %pa; ignoring\n",
			&reserved_base, &reserved_size);
		reserved_base = stolen_top;
		reserved_size = 0;
	पूर्ण

	i915->dsm_reserved =
		(काष्ठा resource)DEFINE_RES_MEM(reserved_base, reserved_size);

	अगर (!resource_contains(&i915->dsm, &i915->dsm_reserved)) अणु
		drm_err(&i915->drm,
			"Stolen reserved area %pR outside stolen memory %pR\n",
			&i915->dsm_reserved, &i915->dsm);
		वापस 0;
	पूर्ण

	/* It is possible क्रम the reserved area to end beक्रमe the end of stolen
	 * memory, so just consider the start. */
	reserved_total = stolen_top - reserved_base;

	drm_dbg(&i915->drm,
		"Memory reserved for graphics device: %lluK, usable: %lluK\n",
		(u64)resource_size(&i915->dsm) >> 10,
		((u64)resource_size(&i915->dsm) - reserved_total) >> 10);

	i915->stolen_usable_size =
		resource_size(&i915->dsm) - reserved_total;

	/* Basic memrange allocator क्रम stolen space. */
	drm_mm_init(&i915->mm.stolen, 0, i915->stolen_usable_size);

	वापस 0;
पूर्ण

अटल व्योम dbg_poison(काष्ठा i915_ggtt *ggtt,
		       dma_addr_t addr, resource_माप_प्रकार size,
		       u8 x)
अणु
#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM)
	अगर (!drm_mm_node_allocated(&ggtt->error_capture))
		वापस;

	अगर (ggtt->vm.bind_async_flags & I915_VMA_GLOBAL_BIND)
		वापस; /* beware stop_machine() inversion */

	GEM_BUG_ON(!IS_ALIGNED(size, PAGE_SIZE));

	mutex_lock(&ggtt->error_mutex);
	जबतक (size) अणु
		व्योम __iomem *s;

		ggtt->vm.insert_page(&ggtt->vm, addr,
				     ggtt->error_capture.start,
				     I915_CACHE_NONE, 0);
		mb();

		s = io_mapping_map_wc(&ggtt->iomap,
				      ggtt->error_capture.start,
				      PAGE_SIZE);
		स_रखो_io(s, x, PAGE_SIZE);
		io_mapping_unmap(s);

		addr += PAGE_SIZE;
		size -= PAGE_SIZE;
	पूर्ण
	mb();
	ggtt->vm.clear_range(&ggtt->vm, ggtt->error_capture.start, PAGE_SIZE);
	mutex_unlock(&ggtt->error_mutex);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा sg_table *
i915_pages_create_क्रम_stolen(काष्ठा drm_device *dev,
			     resource_माप_प्रकार offset, resource_माप_प्रकार size)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा sg_table *st;
	काष्ठा scatterlist *sg;

	GEM_BUG_ON(range_overflows(offset, size, resource_size(&i915->dsm)));

	/* We hide that we have no काष्ठा page backing our stolen object
	 * by wrapping the contiguous physical allocation with a fake
	 * dma mapping in a single scatterlist.
	 */

	st = kदो_स्मृति(माप(*st), GFP_KERNEL);
	अगर (st == शून्य)
		वापस ERR_PTR(-ENOMEM);

	अगर (sg_alloc_table(st, 1, GFP_KERNEL)) अणु
		kमुक्त(st);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	sg = st->sgl;
	sg->offset = 0;
	sg->length = size;

	sg_dma_address(sg) = (dma_addr_t)i915->dsm.start + offset;
	sg_dma_len(sg) = size;

	वापस st;
पूर्ण

अटल पूर्णांक i915_gem_object_get_pages_stolen(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा sg_table *pages =
		i915_pages_create_क्रम_stolen(obj->base.dev,
					     obj->stolen->start,
					     obj->stolen->size);
	अगर (IS_ERR(pages))
		वापस PTR_ERR(pages);

	dbg_poison(&to_i915(obj->base.dev)->ggtt,
		   sg_dma_address(pages->sgl),
		   sg_dma_len(pages->sgl),
		   POISON_INUSE);

	__i915_gem_object_set_pages(obj, pages, obj->stolen->size);

	वापस 0;
पूर्ण

अटल व्योम i915_gem_object_put_pages_stolen(काष्ठा drm_i915_gem_object *obj,
					     काष्ठा sg_table *pages)
अणु
	/* Should only be called from i915_gem_object_release_stolen() */

	dbg_poison(&to_i915(obj->base.dev)->ggtt,
		   sg_dma_address(pages->sgl),
		   sg_dma_len(pages->sgl),
		   POISON_FREE);

	sg_मुक्त_table(pages);
	kमुक्त(pages);
पूर्ण

अटल व्योम
i915_gem_object_release_stolen(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा drm_mm_node *stolen = fetch_and_zero(&obj->stolen);

	GEM_BUG_ON(!stolen);
	i915_gem_stolen_हटाओ_node(i915, stolen);
	kमुक्त(stolen);

	i915_gem_object_release_memory_region(obj);
पूर्ण

अटल स्थिर काष्ठा drm_i915_gem_object_ops i915_gem_object_stolen_ops = अणु
	.name = "i915_gem_object_stolen",
	.get_pages = i915_gem_object_get_pages_stolen,
	.put_pages = i915_gem_object_put_pages_stolen,
	.release = i915_gem_object_release_stolen,
पूर्ण;

अटल पूर्णांक __i915_gem_object_create_stolen(काष्ठा पूर्णांकel_memory_region *mem,
					   काष्ठा drm_i915_gem_object *obj,
					   काष्ठा drm_mm_node *stolen)
अणु
	अटल काष्ठा lock_class_key lock_class;
	अचिन्हित पूर्णांक cache_level;
	पूर्णांक err;

	drm_gem_निजी_object_init(&mem->i915->drm, &obj->base, stolen->size);
	i915_gem_object_init(obj, &i915_gem_object_stolen_ops, &lock_class, 0);

	obj->stolen = stolen;
	obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_CPU | I915_GEM_DOMAIN_GTT;
	cache_level = HAS_LLC(mem->i915) ? I915_CACHE_LLC : I915_CACHE_NONE;
	i915_gem_object_set_cache_coherency(obj, cache_level);

	अगर (WARN_ON(!i915_gem_object_trylock(obj)))
		वापस -EBUSY;

	err = i915_gem_object_pin_pages(obj);
	अगर (!err)
		i915_gem_object_init_memory_region(obj, mem);
	i915_gem_object_unlock(obj);

	वापस err;
पूर्ण

अटल पूर्णांक _i915_gem_object_stolen_init(काष्ठा पूर्णांकel_memory_region *mem,
					काष्ठा drm_i915_gem_object *obj,
					resource_माप_प्रकार size,
					अचिन्हित पूर्णांक flags)
अणु
	काष्ठा drm_i915_निजी *i915 = mem->i915;
	काष्ठा drm_mm_node *stolen;
	पूर्णांक ret;

	अगर (!drm_mm_initialized(&i915->mm.stolen))
		वापस -ENODEV;

	अगर (size == 0)
		वापस -EINVAL;

	stolen = kzalloc(माप(*stolen), GFP_KERNEL);
	अगर (!stolen)
		वापस -ENOMEM;

	ret = i915_gem_stolen_insert_node(i915, stolen, size, 4096);
	अगर (ret)
		जाओ err_मुक्त;

	ret = __i915_gem_object_create_stolen(mem, obj, stolen);
	अगर (ret)
		जाओ err_हटाओ;

	वापस 0;

err_हटाओ:
	i915_gem_stolen_हटाओ_node(i915, stolen);
err_मुक्त:
	kमुक्त(stolen);
	वापस ret;
पूर्ण

काष्ठा drm_i915_gem_object *
i915_gem_object_create_stolen(काष्ठा drm_i915_निजी *i915,
			      resource_माप_प्रकार size)
अणु
	वापस i915_gem_object_create_region(i915->mm.regions[INTEL_REGION_STOLEN_SMEM],
					     size, I915_BO_ALLOC_CONTIGUOUS);
पूर्ण

अटल पूर्णांक init_stolen(काष्ठा पूर्णांकel_memory_region *mem)
अणु
	पूर्णांकel_memory_region_set_name(mem, "stolen");

	/*
	 * Initialise stolen early so that we may reserve pपुनः_स्मृतिated
	 * objects क्रम the BIOS to KMS transition.
	 */
	वापस i915_gem_init_stolen(mem->i915);
पूर्ण

अटल व्योम release_stolen(काष्ठा पूर्णांकel_memory_region *mem)
अणु
	i915_gem_cleanup_stolen(mem->i915);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_memory_region_ops i915_region_stolen_ops = अणु
	.init = init_stolen,
	.release = release_stolen,
	.init_object = _i915_gem_object_stolen_init,
पूर्ण;

काष्ठा पूर्णांकel_memory_region *i915_gem_stolen_setup(काष्ठा drm_i915_निजी *i915)
अणु
	वापस पूर्णांकel_memory_region_create(i915,
					  पूर्णांकel_graphics_stolen_res.start,
					  resource_size(&पूर्णांकel_graphics_stolen_res),
					  PAGE_SIZE, 0,
					  &i915_region_stolen_ops);
पूर्ण

काष्ठा drm_i915_gem_object *
i915_gem_object_create_stolen_क्रम_pपुनः_स्मृतिated(काष्ठा drm_i915_निजी *i915,
					       resource_माप_प्रकार stolen_offset,
					       resource_माप_प्रकार size)
अणु
	काष्ठा पूर्णांकel_memory_region *mem = i915->mm.regions[INTEL_REGION_STOLEN_SMEM];
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा drm_mm_node *stolen;
	पूर्णांक ret;

	अगर (!drm_mm_initialized(&i915->mm.stolen))
		वापस ERR_PTR(-ENODEV);

	drm_dbg(&i915->drm,
		"creating preallocated stolen object: stolen_offset=%pa, size=%pa\n",
		&stolen_offset, &size);

	/* KISS and expect everything to be page-aligned */
	अगर (GEM_WARN_ON(size == 0) ||
	    GEM_WARN_ON(!IS_ALIGNED(size, I915_GTT_PAGE_SIZE)) ||
	    GEM_WARN_ON(!IS_ALIGNED(stolen_offset, I915_GTT_MIN_ALIGNMENT)))
		वापस ERR_PTR(-EINVAL);

	stolen = kzalloc(माप(*stolen), GFP_KERNEL);
	अगर (!stolen)
		वापस ERR_PTR(-ENOMEM);

	stolen->start = stolen_offset;
	stolen->size = size;
	mutex_lock(&i915->mm.stolen_lock);
	ret = drm_mm_reserve_node(&i915->mm.stolen, stolen);
	mutex_unlock(&i915->mm.stolen_lock);
	अगर (ret)
		जाओ err_मुक्त;

	obj = i915_gem_object_alloc();
	अगर (!obj) अणु
		ret = -ENOMEM;
		जाओ err_stolen;
	पूर्ण

	ret = __i915_gem_object_create_stolen(mem, obj, stolen);
	अगर (ret)
		जाओ err_object_मुक्त;

	i915_gem_object_set_cache_coherency(obj, I915_CACHE_NONE);
	वापस obj;

err_object_मुक्त:
	i915_gem_object_मुक्त(obj);
err_stolen:
	i915_gem_stolen_हटाओ_node(i915, stolen);
err_मुक्त:
	kमुक्त(stolen);
	वापस ERR_PTR(ret);
पूर्ण

bool i915_gem_object_is_stolen(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस obj->ops == &i915_gem_object_stolen_ops;
पूर्ण
