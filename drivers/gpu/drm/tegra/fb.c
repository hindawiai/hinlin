<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012-2013 Avionic Design GmbH
 * Copyright (C) 2012 NVIDIA CORPORATION.  All rights reserved.
 *
 * Based on the KMS/FB CMA helpers
 *   Copyright (C) 2012 Analog Devices Inc.
 */

#समावेश <linux/console.h>

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_modeset_helper.h>

#समावेश "drm.h"
#समावेश "gem.h"

#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
अटल अंतरभूत काष्ठा tegra_fbdev *to_tegra_fbdev(काष्ठा drm_fb_helper *helper)
अणु
	वापस container_of(helper, काष्ठा tegra_fbdev, base);
पूर्ण
#पूर्ण_अगर

काष्ठा tegra_bo *tegra_fb_get_plane(काष्ठा drm_framebuffer *framebuffer,
				    अचिन्हित पूर्णांक index)
अणु
	वापस to_tegra_bo(drm_gem_fb_get_obj(framebuffer, index));
पूर्ण

bool tegra_fb_is_bottom_up(काष्ठा drm_framebuffer *framebuffer)
अणु
	काष्ठा tegra_bo *bo = tegra_fb_get_plane(framebuffer, 0);

	अगर (bo->flags & TEGRA_BO_BOTTOM_UP)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक tegra_fb_get_tiling(काष्ठा drm_framebuffer *framebuffer,
			काष्ठा tegra_bo_tiling *tiling)
अणु
	uपूर्णांक64_t modअगरier = framebuffer->modअगरier;

	अगर ((modअगरier >> 56) == DRM_FORMAT_MOD_VENDOR_NVIDIA) अणु
		अगर ((modअगरier & DRM_FORMAT_MOD_NVIDIA_SECTOR_LAYOUT) == 0)
			tiling->sector_layout = TEGRA_BO_SECTOR_LAYOUT_TEGRA;
		अन्यथा
			tiling->sector_layout = TEGRA_BO_SECTOR_LAYOUT_GPU;

		modअगरier &= ~DRM_FORMAT_MOD_NVIDIA_SECTOR_LAYOUT;
	पूर्ण

	चयन (modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
		tiling->mode = TEGRA_BO_TILING_MODE_PITCH;
		tiling->value = 0;
		अवरोध;

	हाल DRM_FORMAT_MOD_NVIDIA_TEGRA_TILED:
		tiling->mode = TEGRA_BO_TILING_MODE_TILED;
		tiling->value = 0;
		अवरोध;

	हाल DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(0):
		tiling->mode = TEGRA_BO_TILING_MODE_BLOCK;
		tiling->value = 0;
		अवरोध;

	हाल DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(1):
		tiling->mode = TEGRA_BO_TILING_MODE_BLOCK;
		tiling->value = 1;
		अवरोध;

	हाल DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(2):
		tiling->mode = TEGRA_BO_TILING_MODE_BLOCK;
		tiling->value = 2;
		अवरोध;

	हाल DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(3):
		tiling->mode = TEGRA_BO_TILING_MODE_BLOCK;
		tiling->value = 3;
		अवरोध;

	हाल DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(4):
		tiling->mode = TEGRA_BO_TILING_MODE_BLOCK;
		tiling->value = 4;
		अवरोध;

	हाल DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(5):
		tiling->mode = TEGRA_BO_TILING_MODE_BLOCK;
		tiling->value = 5;
		अवरोध;

	शेष:
		DRM_DEBUG_KMS("unknown format modifier: %llx\n", modअगरier);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_framebuffer_funcs tegra_fb_funcs = अणु
	.destroy = drm_gem_fb_destroy,
	.create_handle = drm_gem_fb_create_handle,
पूर्ण;

अटल काष्ठा drm_framebuffer *tegra_fb_alloc(काष्ठा drm_device *drm,
					      स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
					      काष्ठा tegra_bo **planes,
					      अचिन्हित पूर्णांक num_planes)
अणु
	काष्ठा drm_framebuffer *fb;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	fb = kzalloc(माप(*fb), GFP_KERNEL);
	अगर (!fb)
		वापस ERR_PTR(-ENOMEM);

	drm_helper_mode_fill_fb_काष्ठा(drm, fb, mode_cmd);

	क्रम (i = 0; i < fb->क्रमmat->num_planes; i++)
		fb->obj[i] = &planes[i]->gem;

	err = drm_framebuffer_init(drm, fb, &tegra_fb_funcs);
	अगर (err < 0) अणु
		dev_err(drm->dev, "failed to initialize framebuffer: %d\n",
			err);
		kमुक्त(fb);
		वापस ERR_PTR(err);
	पूर्ण

	वापस fb;
पूर्ण

काष्ठा drm_framebuffer *tegra_fb_create(काष्ठा drm_device *drm,
					काष्ठा drm_file *file,
					स्थिर काष्ठा drm_mode_fb_cmd2 *cmd)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_get_क्रमmat_info(drm, cmd);
	काष्ठा tegra_bo *planes[4];
	काष्ठा drm_gem_object *gem;
	काष्ठा drm_framebuffer *fb;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < info->num_planes; i++) अणु
		अचिन्हित पूर्णांक width = cmd->width / (i ? info->hsub : 1);
		अचिन्हित पूर्णांक height = cmd->height / (i ? info->vsub : 1);
		अचिन्हित पूर्णांक size, bpp;

		gem = drm_gem_object_lookup(file, cmd->handles[i]);
		अगर (!gem) अणु
			err = -ENXIO;
			जाओ unreference;
		पूर्ण

		bpp = info->cpp[i];

		size = (height - 1) * cmd->pitches[i] +
		       width * bpp + cmd->offsets[i];

		अगर (gem->size < size) अणु
			err = -EINVAL;
			जाओ unreference;
		पूर्ण

		planes[i] = to_tegra_bo(gem);
	पूर्ण

	fb = tegra_fb_alloc(drm, cmd, planes, i);
	अगर (IS_ERR(fb)) अणु
		err = PTR_ERR(fb);
		जाओ unreference;
	पूर्ण

	वापस fb;

unreference:
	जबतक (i--)
		drm_gem_object_put(&planes[i]->gem);

	वापस ERR_PTR(err);
पूर्ण

#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
अटल पूर्णांक tegra_fb_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_fb_helper *helper = info->par;
	काष्ठा tegra_bo *bo;
	पूर्णांक err;

	bo = tegra_fb_get_plane(helper->fb, 0);

	err = drm_gem_mmap_obj(&bo->gem, bo->gem.size, vma);
	अगर (err < 0)
		वापस err;

	वापस __tegra_gem_mmap(&bo->gem, vma);
पूर्ण

अटल स्थिर काष्ठा fb_ops tegra_fb_ops = अणु
	.owner = THIS_MODULE,
	DRM_FB_HELPER_DEFAULT_OPS,
	.fb_fillrect = drm_fb_helper_sys_fillrect,
	.fb_copyarea = drm_fb_helper_sys_copyarea,
	.fb_imageblit = drm_fb_helper_sys_imageblit,
	.fb_mmap = tegra_fb_mmap,
पूर्ण;

अटल पूर्णांक tegra_fbdev_probe(काष्ठा drm_fb_helper *helper,
			     काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा tegra_fbdev *fbdev = to_tegra_fbdev(helper);
	काष्ठा tegra_drm *tegra = helper->dev->dev_निजी;
	काष्ठा drm_device *drm = helper->dev;
	काष्ठा drm_mode_fb_cmd2 cmd = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक bytes_per_pixel;
	काष्ठा drm_framebuffer *fb;
	अचिन्हित दीर्घ offset;
	काष्ठा fb_info *info;
	काष्ठा tegra_bo *bo;
	माप_प्रकार size;
	पूर्णांक err;

	bytes_per_pixel = DIV_ROUND_UP(sizes->surface_bpp, 8);

	cmd.width = sizes->surface_width;
	cmd.height = sizes->surface_height;
	cmd.pitches[0] = round_up(sizes->surface_width * bytes_per_pixel,
				  tegra->pitch_align);

	cmd.pixel_क्रमmat = drm_mode_legacy_fb_क्रमmat(sizes->surface_bpp,
						     sizes->surface_depth);

	size = cmd.pitches[0] * cmd.height;

	bo = tegra_bo_create(drm, size, 0);
	अगर (IS_ERR(bo))
		वापस PTR_ERR(bo);

	info = drm_fb_helper_alloc_fbi(helper);
	अगर (IS_ERR(info)) अणु
		dev_err(drm->dev, "failed to allocate framebuffer info\n");
		drm_gem_object_put(&bo->gem);
		वापस PTR_ERR(info);
	पूर्ण

	fbdev->fb = tegra_fb_alloc(drm, &cmd, &bo, 1);
	अगर (IS_ERR(fbdev->fb)) अणु
		err = PTR_ERR(fbdev->fb);
		dev_err(drm->dev, "failed to allocate DRM framebuffer: %d\n",
			err);
		drm_gem_object_put(&bo->gem);
		वापस PTR_ERR(fbdev->fb);
	पूर्ण

	fb = fbdev->fb;
	helper->fb = fb;
	helper->fbdev = info;

	info->fbops = &tegra_fb_ops;

	drm_fb_helper_fill_info(info, helper, sizes);

	offset = info->var.xoffset * bytes_per_pixel +
		 info->var.yoffset * fb->pitches[0];

	अगर (bo->pages) अणु
		bo->vaddr = vmap(bo->pages, bo->num_pages, VM_MAP,
				 pgprot_ग_लिखोcombine(PAGE_KERNEL));
		अगर (!bo->vaddr) अणु
			dev_err(drm->dev, "failed to vmap() framebuffer\n");
			err = -ENOMEM;
			जाओ destroy;
		पूर्ण
	पूर्ण

	drm->mode_config.fb_base = (resource_माप_प्रकार)bo->iova;
	info->screen_base = (व्योम __iomem *)bo->vaddr + offset;
	info->screen_size = size;
	info->fix.smem_start = (अचिन्हित दीर्घ)(bo->iova + offset);
	info->fix.smem_len = size;

	वापस 0;

destroy:
	drm_framebuffer_हटाओ(fb);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा drm_fb_helper_funcs tegra_fb_helper_funcs = अणु
	.fb_probe = tegra_fbdev_probe,
पूर्ण;

अटल काष्ठा tegra_fbdev *tegra_fbdev_create(काष्ठा drm_device *drm)
अणु
	काष्ठा tegra_fbdev *fbdev;

	fbdev = kzalloc(माप(*fbdev), GFP_KERNEL);
	अगर (!fbdev) अणु
		dev_err(drm->dev, "failed to allocate DRM fbdev\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	drm_fb_helper_prepare(drm, &fbdev->base, &tegra_fb_helper_funcs);

	वापस fbdev;
पूर्ण

अटल व्योम tegra_fbdev_मुक्त(काष्ठा tegra_fbdev *fbdev)
अणु
	kमुक्त(fbdev);
पूर्ण

अटल पूर्णांक tegra_fbdev_init(काष्ठा tegra_fbdev *fbdev,
			    अचिन्हित पूर्णांक preferred_bpp,
			    अचिन्हित पूर्णांक num_crtc,
			    अचिन्हित पूर्णांक max_connectors)
अणु
	काष्ठा drm_device *drm = fbdev->base.dev;
	पूर्णांक err;

	err = drm_fb_helper_init(drm, &fbdev->base);
	अगर (err < 0) अणु
		dev_err(drm->dev, "failed to initialize DRM FB helper: %d\n",
			err);
		वापस err;
	पूर्ण

	err = drm_fb_helper_initial_config(&fbdev->base, preferred_bpp);
	अगर (err < 0) अणु
		dev_err(drm->dev, "failed to set initial configuration: %d\n",
			err);
		जाओ fini;
	पूर्ण

	वापस 0;

fini:
	drm_fb_helper_fini(&fbdev->base);
	वापस err;
पूर्ण

अटल व्योम tegra_fbdev_निकास(काष्ठा tegra_fbdev *fbdev)
अणु
	drm_fb_helper_unरेजिस्टर_fbi(&fbdev->base);

	अगर (fbdev->fb) अणु
		काष्ठा tegra_bo *bo = tegra_fb_get_plane(fbdev->fb, 0);

		/* Unकरो the special mapping we made in fbdev probe. */
		अगर (bo && bo->pages) अणु
			vunmap(bo->vaddr);
			bo->vaddr = शून्य;
		पूर्ण

		drm_framebuffer_हटाओ(fbdev->fb);
	पूर्ण

	drm_fb_helper_fini(&fbdev->base);
	tegra_fbdev_मुक्त(fbdev);
पूर्ण
#पूर्ण_अगर

पूर्णांक tegra_drm_fb_prepare(काष्ठा drm_device *drm)
अणु
#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
	काष्ठा tegra_drm *tegra = drm->dev_निजी;

	tegra->fbdev = tegra_fbdev_create(drm);
	अगर (IS_ERR(tegra->fbdev))
		वापस PTR_ERR(tegra->fbdev);
#पूर्ण_अगर

	वापस 0;
पूर्ण

व्योम tegra_drm_fb_मुक्त(काष्ठा drm_device *drm)
अणु
#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
	काष्ठा tegra_drm *tegra = drm->dev_निजी;

	tegra_fbdev_मुक्त(tegra->fbdev);
#पूर्ण_अगर
पूर्ण

पूर्णांक tegra_drm_fb_init(काष्ठा drm_device *drm)
अणु
#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
	काष्ठा tegra_drm *tegra = drm->dev_निजी;
	पूर्णांक err;

	err = tegra_fbdev_init(tegra->fbdev, 32, drm->mode_config.num_crtc,
			       drm->mode_config.num_connector);
	अगर (err < 0)
		वापस err;
#पूर्ण_अगर

	वापस 0;
पूर्ण

व्योम tegra_drm_fb_निकास(काष्ठा drm_device *drm)
अणु
#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
	काष्ठा tegra_drm *tegra = drm->dev_निजी;

	tegra_fbdev_निकास(tegra->fbdev);
#पूर्ण_अगर
पूर्ण
