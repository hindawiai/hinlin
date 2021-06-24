<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>

#समावेश "komeda_framebuffer.h"
#समावेश "komeda_dev.h"

अटल व्योम komeda_fb_destroy(काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा komeda_fb *kfb = to_kfb(fb);
	u32 i;

	क्रम (i = 0; i < fb->क्रमmat->num_planes; i++)
		drm_gem_object_put(fb->obj[i]);

	drm_framebuffer_cleanup(fb);
	kमुक्त(kfb);
पूर्ण

अटल पूर्णांक komeda_fb_create_handle(काष्ठा drm_framebuffer *fb,
				   काष्ठा drm_file *file, u32 *handle)
अणु
	वापस drm_gem_handle_create(file, fb->obj[0], handle);
पूर्ण

अटल स्थिर काष्ठा drm_framebuffer_funcs komeda_fb_funcs = अणु
	.destroy	= komeda_fb_destroy,
	.create_handle	= komeda_fb_create_handle,
पूर्ण;

अटल पूर्णांक
komeda_fb_afbc_size_check(काष्ठा komeda_fb *kfb, काष्ठा drm_file *file,
			  स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा drm_framebuffer *fb = &kfb->base;
	स्थिर काष्ठा drm_क्रमmat_info *info = fb->क्रमmat;
	काष्ठा drm_gem_object *obj;
	u32 alignment_w = 0, alignment_h = 0, alignment_header, n_blocks, bpp;
	u64 min_size;

	obj = drm_gem_object_lookup(file, mode_cmd->handles[0]);
	अगर (!obj) अणु
		DRM_DEBUG_KMS("Failed to lookup GEM object\n");
		वापस -ENOENT;
	पूर्ण

	चयन (fb->modअगरier & AFBC_FORMAT_MOD_BLOCK_SIZE_MASK) अणु
	हाल AFBC_FORMAT_MOD_BLOCK_SIZE_32x8:
		alignment_w = 32;
		alignment_h = 8;
		अवरोध;
	हाल AFBC_FORMAT_MOD_BLOCK_SIZE_16x16:
		alignment_w = 16;
		alignment_h = 16;
		अवरोध;
	शेष:
		WARN(1, "Invalid AFBC_FORMAT_MOD_BLOCK_SIZE: %lld.\n",
		     fb->modअगरier & AFBC_FORMAT_MOD_BLOCK_SIZE_MASK);
		अवरोध;
	पूर्ण

	/* tiled header afbc */
	अगर (fb->modअगरier & AFBC_FORMAT_MOD_TILED) अणु
		alignment_w *= AFBC_TH_LAYOUT_ALIGNMENT;
		alignment_h *= AFBC_TH_LAYOUT_ALIGNMENT;
		alignment_header = AFBC_TH_BODY_START_ALIGNMENT;
	पूर्ण अन्यथा अणु
		alignment_header = AFBC_BODY_START_ALIGNMENT;
	पूर्ण

	kfb->aligned_w = ALIGN(fb->width, alignment_w);
	kfb->aligned_h = ALIGN(fb->height, alignment_h);

	अगर (fb->offsets[0] % alignment_header) अणु
		DRM_DEBUG_KMS("afbc offset alignment check failed.\n");
		जाओ check_failed;
	पूर्ण

	n_blocks = (kfb->aligned_w * kfb->aligned_h) / AFBC_SUPERBLK_PIXELS;
	kfb->offset_payload = ALIGN(n_blocks * AFBC_HEADER_SIZE,
				    alignment_header);

	bpp = komeda_get_afbc_क्रमmat_bpp(info, fb->modअगरier);
	kfb->afbc_size = kfb->offset_payload + n_blocks *
			 ALIGN(bpp * AFBC_SUPERBLK_PIXELS / 8,
			       AFBC_SUPERBLK_ALIGNMENT);
	min_size = kfb->afbc_size + fb->offsets[0];
	अगर (min_size > obj->size) अणु
		DRM_DEBUG_KMS("afbc size check failed, obj_size: 0x%zx. min_size 0x%llx.\n",
			      obj->size, min_size);
		जाओ check_failed;
	पूर्ण

	fb->obj[0] = obj;
	वापस 0;

check_failed:
	drm_gem_object_put(obj);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
komeda_fb_none_afbc_size_check(काष्ठा komeda_dev *mdev, काष्ठा komeda_fb *kfb,
			       काष्ठा drm_file *file,
			       स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा drm_framebuffer *fb = &kfb->base;
	स्थिर काष्ठा drm_क्रमmat_info *info = fb->क्रमmat;
	काष्ठा drm_gem_object *obj;
	u32 i, block_h;
	u64 min_size;

	अगर (komeda_fb_check_src_coords(kfb, 0, 0, fb->width, fb->height))
		वापस -EINVAL;

	क्रम (i = 0; i < info->num_planes; i++) अणु
		obj = drm_gem_object_lookup(file, mode_cmd->handles[i]);
		अगर (!obj) अणु
			DRM_DEBUG_KMS("Failed to lookup GEM object\n");
			वापस -ENOENT;
		पूर्ण
		fb->obj[i] = obj;

		block_h = drm_क्रमmat_info_block_height(info, i);
		अगर ((fb->pitches[i] * block_h) % mdev->chip.bus_width) अणु
			DRM_DEBUG_KMS("Pitch[%d]: 0x%x doesn't align to 0x%x\n",
				      i, fb->pitches[i], mdev->chip.bus_width);
			वापस -EINVAL;
		पूर्ण

		min_size = komeda_fb_get_pixel_addr(kfb, 0, fb->height, i)
			 - to_drm_gem_cma_obj(obj)->paddr;
		अगर (obj->size < min_size) अणु
			DRM_DEBUG_KMS("The fb->obj[%d] size: 0x%zx lower than the minimum requirement: 0x%llx.\n",
				      i, obj->size, min_size);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (fb->क्रमmat->num_planes == 3) अणु
		अगर (fb->pitches[1] != fb->pitches[2]) अणु
			DRM_DEBUG_KMS("The pitch[1] and [2] are not same\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा drm_framebuffer *
komeda_fb_create(काष्ठा drm_device *dev, काष्ठा drm_file *file,
		 स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा komeda_dev *mdev = dev->dev_निजी;
	काष्ठा komeda_fb *kfb;
	पूर्णांक ret = 0, i;

	kfb = kzalloc(माप(*kfb), GFP_KERNEL);
	अगर (!kfb)
		वापस ERR_PTR(-ENOMEM);

	kfb->क्रमmat_caps = komeda_get_क्रमmat_caps(&mdev->fmt_tbl,
						  mode_cmd->pixel_क्रमmat,
						  mode_cmd->modअगरier[0]);
	अगर (!kfb->क्रमmat_caps) अणु
		DRM_DEBUG_KMS("FMT %x is not supported.\n",
			      mode_cmd->pixel_क्रमmat);
		kमुक्त(kfb);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	drm_helper_mode_fill_fb_काष्ठा(dev, &kfb->base, mode_cmd);

	अगर (kfb->base.modअगरier)
		ret = komeda_fb_afbc_size_check(kfb, file, mode_cmd);
	अन्यथा
		ret = komeda_fb_none_afbc_size_check(mdev, kfb, file, mode_cmd);
	अगर (ret < 0)
		जाओ err_cleanup;

	ret = drm_framebuffer_init(dev, &kfb->base, &komeda_fb_funcs);
	अगर (ret < 0) अणु
		DRM_DEBUG_KMS("failed to initialize fb\n");

		जाओ err_cleanup;
	पूर्ण

	kfb->is_va = mdev->iommu ? true : false;

	वापस &kfb->base;

err_cleanup:
	क्रम (i = 0; i < kfb->base.क्रमmat->num_planes; i++)
		drm_gem_object_put(kfb->base.obj[i]);

	kमुक्त(kfb);
	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक komeda_fb_check_src_coords(स्थिर काष्ठा komeda_fb *kfb,
			       u32 src_x, u32 src_y, u32 src_w, u32 src_h)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = &kfb->base;
	स्थिर काष्ठा drm_क्रमmat_info *info = fb->क्रमmat;
	u32 block_w = drm_क्रमmat_info_block_width(fb->क्रमmat, 0);
	u32 block_h = drm_क्रमmat_info_block_height(fb->क्रमmat, 0);

	अगर ((src_x + src_w > fb->width) || (src_y + src_h > fb->height)) अणु
		DRM_DEBUG_ATOMIC("Invalid source coordinate.\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((src_x % info->hsub) || (src_w % info->hsub) ||
	    (src_y % info->vsub) || (src_h % info->vsub)) अणु
		DRM_DEBUG_ATOMIC("Wrong subsampling dimension x:%d, y:%d, w:%d, h:%d for format: %x.\n",
				 src_x, src_y, src_w, src_h, info->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर ((src_x % block_w) || (src_w % block_w) ||
	    (src_y % block_h) || (src_h % block_h)) अणु
		DRM_DEBUG_ATOMIC("x:%d, y:%d, w:%d, h:%d should be multiple of block_w/h for format: %x.\n",
				 src_x, src_y, src_w, src_h, info->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

dma_addr_t
komeda_fb_get_pixel_addr(काष्ठा komeda_fb *kfb, पूर्णांक x, पूर्णांक y, पूर्णांक plane)
अणु
	काष्ठा drm_framebuffer *fb = &kfb->base;
	स्थिर काष्ठा drm_gem_cma_object *obj;
	u32 offset, plane_x, plane_y, block_w, block_sz;

	अगर (plane >= fb->क्रमmat->num_planes) अणु
		DRM_DEBUG_KMS("Out of max plane num.\n");
		वापस -EINVAL;
	पूर्ण

	obj = drm_fb_cma_get_gem_obj(fb, plane);

	offset = fb->offsets[plane];
	अगर (!fb->modअगरier) अणु
		block_w = drm_क्रमmat_info_block_width(fb->क्रमmat, plane);
		block_sz = fb->क्रमmat->अक्षर_per_block[plane];
		plane_x = x / (plane ? fb->क्रमmat->hsub : 1);
		plane_y = y / (plane ? fb->क्रमmat->vsub : 1);

		offset += (plane_x / block_w) * block_sz
			+ plane_y * fb->pitches[plane];
	पूर्ण

	वापस obj->paddr + offset;
पूर्ण

/* अगर the fb can be supported by a specअगरic layer */
bool komeda_fb_is_layer_supported(काष्ठा komeda_fb *kfb, u32 layer_type,
				  u32 rot)
अणु
	काष्ठा drm_framebuffer *fb = &kfb->base;
	काष्ठा komeda_dev *mdev = fb->dev->dev_निजी;
	u32 fourcc = fb->क्रमmat->क्रमmat;
	u64 modअगरier = fb->modअगरier;
	bool supported;

	supported = komeda_क्रमmat_mod_supported(&mdev->fmt_tbl, layer_type,
						fourcc, modअगरier, rot);
	अगर (!supported)
		DRM_DEBUG_ATOMIC("Layer TYPE: %d doesn't support fb FMT: %p4cc with modifier: 0x%llx.\n",
				 layer_type, &fourcc, modअगरier);

	वापस supported;
पूर्ण
