<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/module.h>

#समावेश <drm/drm_gem_tपंचांग_helper.h>

/**
 * DOC: overview
 *
 * This library provides helper functions क्रम gem objects backed by
 * tपंचांग.
 */

/**
 * drm_gem_tपंचांग_prपूर्णांक_info() - Prपूर्णांक &tपंचांग_buffer_object info क्रम debugfs
 * @p: DRM prपूर्णांकer
 * @indent: Tab indentation level
 * @gem: GEM object
 *
 * This function can be used as &drm_gem_object_funcs.prपूर्णांक_info
 * callback.
 */
व्योम drm_gem_tपंचांग_prपूर्णांक_info(काष्ठा drm_prपूर्णांकer *p, अचिन्हित पूर्णांक indent,
			    स्थिर काष्ठा drm_gem_object *gem)
अणु
	अटल स्थिर अक्षर * स्थिर plname[] = अणु
		[ TTM_PL_SYSTEM ] = "system",
		[ TTM_PL_TT     ] = "tt",
		[ TTM_PL_VRAM   ] = "vram",
		[ TTM_PL_PRIV   ] = "priv",

		[ 16 ]            = "cached",
		[ 17 ]            = "uncached",
		[ 18 ]            = "wc",
		[ 19 ]            = "contig",

		[ 21 ]            = "pinned", /* NO_EVICT */
		[ 22 ]            = "topdown",
	पूर्ण;
	स्थिर काष्ठा tपंचांग_buffer_object *bo = drm_gem_tपंचांग_of_gem(gem);

	drm_म_लिखो_indent(p, indent, "placement=");
	drm_prपूर्णांक_bits(p, bo->mem.placement, plname, ARRAY_SIZE(plname));
	drm_म_लिखो(p, "\n");

	अगर (bo->mem.bus.is_iomem)
		drm_म_लिखो_indent(p, indent, "bus.offset=%lx\n",
				  (अचिन्हित दीर्घ)bo->mem.bus.offset);
पूर्ण
EXPORT_SYMBOL(drm_gem_tपंचांग_prपूर्णांक_info);

/**
 * drm_gem_tपंचांग_vmap() - vmap &tपंचांग_buffer_object
 * @gem: GEM object.
 * @map: [out] वापसs the dma-buf mapping.
 *
 * Maps a GEM object with tपंचांग_bo_vmap(). This function can be used as
 * &drm_gem_object_funcs.vmap callback.
 *
 * Returns:
 * 0 on success, or a negative त्रुटि_सं code otherwise.
 */
पूर्णांक drm_gem_tपंचांग_vmap(काष्ठा drm_gem_object *gem,
		     काष्ठा dma_buf_map *map)
अणु
	काष्ठा tपंचांग_buffer_object *bo = drm_gem_tपंचांग_of_gem(gem);

	वापस tपंचांग_bo_vmap(bo, map);
पूर्ण
EXPORT_SYMBOL(drm_gem_tपंचांग_vmap);

/**
 * drm_gem_tपंचांग_vunmap() - vunmap &tपंचांग_buffer_object
 * @gem: GEM object.
 * @map: dma-buf mapping.
 *
 * Unmaps a GEM object with tपंचांग_bo_vunmap(). This function can be used as
 * &drm_gem_object_funcs.vmap callback.
 */
व्योम drm_gem_tपंचांग_vunmap(काष्ठा drm_gem_object *gem,
			काष्ठा dma_buf_map *map)
अणु
	काष्ठा tपंचांग_buffer_object *bo = drm_gem_tपंचांग_of_gem(gem);

	tपंचांग_bo_vunmap(bo, map);
पूर्ण
EXPORT_SYMBOL(drm_gem_tपंचांग_vunmap);

/**
 * drm_gem_tपंचांग_mmap() - mmap &tपंचांग_buffer_object
 * @gem: GEM object.
 * @vma: vm area.
 *
 * This function can be used as &drm_gem_object_funcs.mmap
 * callback.
 */
पूर्णांक drm_gem_tपंचांग_mmap(काष्ठा drm_gem_object *gem,
		     काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा tपंचांग_buffer_object *bo = drm_gem_tपंचांग_of_gem(gem);
	पूर्णांक ret;

	ret = tपंचांग_bo_mmap_obj(vma, bo);
	अगर (ret < 0)
		वापस ret;

	/*
	 * tपंचांग has its own object refcounting, so drop gem reference
	 * to aव्योम द्विगुन accounting counting.
	 */
	drm_gem_object_put(gem);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_gem_tपंचांग_mmap);

MODULE_DESCRIPTION("DRM gem ttm helpers");
MODULE_LICENSE("GPL");
