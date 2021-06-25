<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

#अगर_अघोषित DRM_GEM_VRAM_HELPER_H
#घोषणा DRM_GEM_VRAM_HELPER_H

#समावेश <drm/drm_file.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_api.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>

#समावेश <linux/dma-buf-map.h>
#समावेश <linux/kernel.h> /* क्रम container_of() */

काष्ठा drm_mode_create_dumb;
काष्ठा drm_plane;
काष्ठा drm_plane_state;
काष्ठा drm_simple_display_pipe;
काष्ठा filp;
काष्ठा vm_area_काष्ठा;

#घोषणा DRM_GEM_VRAM_PL_FLAG_SYSTEM	(1 << 0)
#घोषणा DRM_GEM_VRAM_PL_FLAG_VRAM	(1 << 1)
#घोषणा DRM_GEM_VRAM_PL_FLAG_TOPDOWN	(1 << 2)

/*
 * Buffer-object helpers
 */

/**
 * काष्ठा drm_gem_vram_object - GEM object backed by VRAM
 * @bo:		TTM buffer object
 * @map:	Mapping inक्रमmation क्रम @bo
 * @placement:	TTM placement inक्रमmation. Supported placements are \
	%TTM_PL_VRAM and %TTM_PL_SYSTEM
 * @placements:	TTM placement inक्रमmation.
 *
 * The type काष्ठा drm_gem_vram_object represents a GEM object that is
 * backed by VRAM. It can be used क्रम simple framebuffer devices with
 * dedicated memory. The buffer object can be evicted to प्रणाली memory अगर
 * video memory becomes scarce.
 *
 * GEM VRAM objects perक्रमm reference counting क्रम pin and mapping
 * operations. So a buffer object that has been pinned N बार with
 * drm_gem_vram_pin() must be unpinned N बार with
 * drm_gem_vram_unpin(). The same applies to pairs of
 * drm_gem_vram_kmap() and drm_gem_vram_kunmap(), as well as pairs of
 * drm_gem_vram_vmap() and drm_gem_vram_vunmap().
 */
काष्ठा drm_gem_vram_object अणु
	काष्ठा tपंचांग_buffer_object bo;
	काष्ठा dma_buf_map map;

	/**
	 * @vmap_use_count:
	 *
	 * Reference count on the भव address.
	 * The address are un-mapped when the count reaches zero.
	 */
	अचिन्हित पूर्णांक vmap_use_count;

	/* Supported placements are %TTM_PL_VRAM and %TTM_PL_SYSTEM */
	काष्ठा tपंचांग_placement placement;
	काष्ठा tपंचांग_place placements[2];
पूर्ण;

/**
 * drm_gem_vram_of_bo - Returns the container of type
 * &काष्ठा drm_gem_vram_object क्रम field bo.
 * @bo:		the VRAM buffer object
 * Returns:	The containing GEM VRAM object
 */
अटल अंतरभूत काष्ठा drm_gem_vram_object *drm_gem_vram_of_bo(
	काष्ठा tपंचांग_buffer_object *bo)
अणु
	वापस container_of(bo, काष्ठा drm_gem_vram_object, bo);
पूर्ण

/**
 * drm_gem_vram_of_gem - Returns the container of type
 * &काष्ठा drm_gem_vram_object क्रम field gem.
 * @gem:	the GEM object
 * Returns:	The containing GEM VRAM object
 */
अटल अंतरभूत काष्ठा drm_gem_vram_object *drm_gem_vram_of_gem(
	काष्ठा drm_gem_object *gem)
अणु
	वापस container_of(gem, काष्ठा drm_gem_vram_object, bo.base);
पूर्ण

काष्ठा drm_gem_vram_object *drm_gem_vram_create(काष्ठा drm_device *dev,
						माप_प्रकार size,
						अचिन्हित दीर्घ pg_align);
व्योम drm_gem_vram_put(काष्ठा drm_gem_vram_object *gbo);
u64 drm_gem_vram_mmap_offset(काष्ठा drm_gem_vram_object *gbo);
s64 drm_gem_vram_offset(काष्ठा drm_gem_vram_object *gbo);
पूर्णांक drm_gem_vram_pin(काष्ठा drm_gem_vram_object *gbo, अचिन्हित दीर्घ pl_flag);
पूर्णांक drm_gem_vram_unpin(काष्ठा drm_gem_vram_object *gbo);
पूर्णांक drm_gem_vram_vmap(काष्ठा drm_gem_vram_object *gbo, काष्ठा dma_buf_map *map);
व्योम drm_gem_vram_vunmap(काष्ठा drm_gem_vram_object *gbo, काष्ठा dma_buf_map *map);

पूर्णांक drm_gem_vram_fill_create_dumb(काष्ठा drm_file *file,
				  काष्ठा drm_device *dev,
				  अचिन्हित दीर्घ pg_align,
				  अचिन्हित दीर्घ pitch_align,
				  काष्ठा drm_mode_create_dumb *args);

/*
 * Helpers क्रम काष्ठा drm_driver
 */

पूर्णांक drm_gem_vram_driver_dumb_create(काष्ठा drm_file *file,
				    काष्ठा drm_device *dev,
				    काष्ठा drm_mode_create_dumb *args);
पूर्णांक drm_gem_vram_driver_dumb_mmap_offset(काष्ठा drm_file *file,
					 काष्ठा drm_device *dev,
					 uपूर्णांक32_t handle, uपूर्णांक64_t *offset);

/*
 * Helpers क्रम काष्ठा drm_plane_helper_funcs
 */
पूर्णांक
drm_gem_vram_plane_helper_prepare_fb(काष्ठा drm_plane *plane,
				     काष्ठा drm_plane_state *new_state);
व्योम
drm_gem_vram_plane_helper_cleanup_fb(काष्ठा drm_plane *plane,
				     काष्ठा drm_plane_state *old_state);

/*
 * Helpers क्रम काष्ठा drm_simple_display_pipe_funcs
 */

पूर्णांक drm_gem_vram_simple_display_pipe_prepare_fb(
	काष्ठा drm_simple_display_pipe *pipe,
	काष्ठा drm_plane_state *new_state);

व्योम drm_gem_vram_simple_display_pipe_cleanup_fb(
	काष्ठा drm_simple_display_pipe *pipe,
	काष्ठा drm_plane_state *old_state);

/**
 * define DRM_GEM_VRAM_DRIVER - शेष callback functions क्रम \
	&काष्ठा drm_driver
 *
 * Drivers that use VRAM MM and GEM VRAM can use this macro to initialize
 * &काष्ठा drm_driver with शेष functions.
 */
#घोषणा DRM_GEM_VRAM_DRIVER \
	.debugfs_init             = drm_vram_mm_debugfs_init, \
	.dumb_create		  = drm_gem_vram_driver_dumb_create, \
	.dumb_map_offset	  = drm_gem_vram_driver_dumb_mmap_offset, \
	.gem_prime_mmap		  = drm_gem_prime_mmap

/*
 *  VRAM memory manager
 */

/**
 * काष्ठा drm_vram_mm - An instance of VRAM MM
 * @vram_base:	Base address of the managed video memory
 * @vram_size:	Size of the managed video memory in bytes
 * @bdev:	The TTM BO device.
 * @funcs:	TTM BO functions
 *
 * The fields &काष्ठा drm_vram_mm.vram_base and
 * &काष्ठा drm_vram_mm.vrm_size are managed by VRAM MM, but are
 * available क्रम खुला पढ़ो access. Use the field
 * &काष्ठा drm_vram_mm.bdev to access the TTM BO device.
 */
काष्ठा drm_vram_mm अणु
	uपूर्णांक64_t vram_base;
	माप_प्रकार vram_size;

	काष्ठा tपंचांग_device bdev;
पूर्ण;

/**
 * drm_vram_mm_of_bdev() - \
	Returns the container of type &काष्ठा tपंचांग_device क्रम field bdev.
 * @bdev:	the TTM BO device
 *
 * Returns:
 * The containing instance of &काष्ठा drm_vram_mm
 */
अटल अंतरभूत काष्ठा drm_vram_mm *drm_vram_mm_of_bdev(
	काष्ठा tपंचांग_device *bdev)
अणु
	वापस container_of(bdev, काष्ठा drm_vram_mm, bdev);
पूर्ण

व्योम drm_vram_mm_debugfs_init(काष्ठा drm_minor *minor);

/*
 * Helpers क्रम पूर्णांकegration with काष्ठा drm_device
 */

काष्ठा drm_vram_mm *drm_vram_helper_alloc_mm(
	काष्ठा drm_device *dev, uपूर्णांक64_t vram_base, माप_प्रकार vram_size);
व्योम drm_vram_helper_release_mm(काष्ठा drm_device *dev);

पूर्णांक drmm_vram_helper_init(काष्ठा drm_device *dev, uपूर्णांक64_t vram_base,
			  माप_प्रकार vram_size);

/*
 * Mode-config helpers
 */

क्रमागत drm_mode_status
drm_vram_helper_mode_valid(काष्ठा drm_device *dev,
			   स्थिर काष्ठा drm_display_mode *mode);

#पूर्ण_अगर
