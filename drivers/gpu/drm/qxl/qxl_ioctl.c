<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alon Levy
 */

#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>

#समावेश "qxl_drv.h"
#समावेश "qxl_object.h"

/*
 * TODO: allocating a new gem(in qxl_bo) क्रम each request.
 * This is wasteful since bo's are page aligned.
 */
अटल पूर्णांक qxl_alloc_ioctl(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv)
अणु
	काष्ठा qxl_device *qdev = to_qxl(dev);
	काष्ठा drm_qxl_alloc *qxl_alloc = data;
	पूर्णांक ret;
	काष्ठा qxl_bo *qobj;
	uपूर्णांक32_t handle;
	u32 करोमुख्य = QXL_GEM_DOMAIN_VRAM;

	अगर (qxl_alloc->size == 0) अणु
		DRM_ERROR("invalid size %d\n", qxl_alloc->size);
		वापस -EINVAL;
	पूर्ण
	ret = qxl_gem_object_create_with_handle(qdev, file_priv,
						करोमुख्य,
						qxl_alloc->size,
						शून्य,
						&qobj, &handle);
	अगर (ret) अणु
		DRM_ERROR("%s: failed to create gem ret=%d\n",
			  __func__, ret);
		वापस -ENOMEM;
	पूर्ण
	qxl_alloc->handle = handle;
	वापस 0;
पूर्ण

अटल पूर्णांक qxl_map_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv)
अणु
	काष्ठा qxl_device *qdev = to_qxl(dev);
	काष्ठा drm_qxl_map *qxl_map = data;

	वापस qxl_mode_dumb_mmap(file_priv, &qdev->ddev, qxl_map->handle,
				  &qxl_map->offset);
पूर्ण

काष्ठा qxl_reloc_info अणु
	पूर्णांक type;
	काष्ठा qxl_bo *dst_bo;
	uपूर्णांक32_t dst_offset;
	काष्ठा qxl_bo *src_bo;
	पूर्णांक src_offset;
पूर्ण;

/*
 * dst must be validated, i.e. whole bo on vram/surfacesram (right now all bo's
 * are on vram).
 * *(dst + dst_off) = qxl_bo_physical_address(src, src_off)
 */
अटल व्योम
apply_reloc(काष्ठा qxl_device *qdev, काष्ठा qxl_reloc_info *info)
अणु
	व्योम *reloc_page;

	reloc_page = qxl_bo_kmap_atomic_page(qdev, info->dst_bo, info->dst_offset & PAGE_MASK);
	*(uपूर्णांक64_t *)(reloc_page + (info->dst_offset & ~PAGE_MASK)) = qxl_bo_physical_address(qdev,
											      info->src_bo,
											      info->src_offset);
	qxl_bo_kunmap_atomic_page(qdev, info->dst_bo, reloc_page);
पूर्ण

अटल व्योम
apply_surf_reloc(काष्ठा qxl_device *qdev, काष्ठा qxl_reloc_info *info)
अणु
	uपूर्णांक32_t id = 0;
	व्योम *reloc_page;

	अगर (info->src_bo && !info->src_bo->is_primary)
		id = info->src_bo->surface_id;

	reloc_page = qxl_bo_kmap_atomic_page(qdev, info->dst_bo, info->dst_offset & PAGE_MASK);
	*(uपूर्णांक32_t *)(reloc_page + (info->dst_offset & ~PAGE_MASK)) = id;
	qxl_bo_kunmap_atomic_page(qdev, info->dst_bo, reloc_page);
पूर्ण

/* वापस holding the reference to this object */
अटल पूर्णांक qxlhw_handle_to_bo(काष्ठा drm_file *file_priv, uपूर्णांक64_t handle,
			      काष्ठा qxl_release *release, काष्ठा qxl_bo **qbo_p)
अणु
	काष्ठा drm_gem_object *gobj;
	काष्ठा qxl_bo *qobj;
	पूर्णांक ret;

	gobj = drm_gem_object_lookup(file_priv, handle);
	अगर (!gobj)
		वापस -EINVAL;

	qobj = gem_to_qxl_bo(gobj);

	ret = qxl_release_list_add(release, qobj);
	drm_gem_object_put(gobj);
	अगर (ret)
		वापस ret;

	*qbo_p = qobj;
	वापस 0;
पूर्ण

/*
 * Usage of execbuffer:
 * Relocations need to take पूर्णांकo account the full QXLDrawable size.
 * However, the command as passed from user space must *not* contain the initial
 * QXLReleaseInfo काष्ठा (first XXX bytes)
 */
अटल पूर्णांक qxl_process_single_command(काष्ठा qxl_device *qdev,
				      काष्ठा drm_qxl_command *cmd,
				      काष्ठा drm_file *file_priv)
अणु
	काष्ठा qxl_reloc_info *reloc_info;
	पूर्णांक release_type;
	काष्ठा qxl_release *release;
	काष्ठा qxl_bo *cmd_bo;
	व्योम *fb_cmd;
	पूर्णांक i, ret, num_relocs;
	पूर्णांक unwritten;

	चयन (cmd->type) अणु
	हाल QXL_CMD_DRAW:
		release_type = QXL_RELEASE_DRAWABLE;
		अवरोध;
	हाल QXL_CMD_SURFACE:
	हाल QXL_CMD_CURSOR:
	शेष:
		DRM_DEBUG("Only draw commands in execbuffers\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cmd->command_size > PAGE_SIZE - माप(जोड़ qxl_release_info))
		वापस -EINVAL;

	अगर (!access_ok(u64_to_user_ptr(cmd->command),
		       cmd->command_size))
		वापस -EFAULT;

	reloc_info = kदो_स्मृति_array(cmd->relocs_num,
				   माप(काष्ठा qxl_reloc_info), GFP_KERNEL);
	अगर (!reloc_info)
		वापस -ENOMEM;

	ret = qxl_alloc_release_reserved(qdev,
					 माप(जोड़ qxl_release_info) +
					 cmd->command_size,
					 release_type,
					 &release,
					 &cmd_bo);
	अगर (ret)
		जाओ out_मुक्त_reloc;

	/* TODO copy slow path code from i915 */
	fb_cmd = qxl_bo_kmap_atomic_page(qdev, cmd_bo, (release->release_offset & PAGE_MASK));
	unwritten = __copy_from_user_inatomic_nocache
		(fb_cmd + माप(जोड़ qxl_release_info) + (release->release_offset & ~PAGE_MASK),
		 u64_to_user_ptr(cmd->command), cmd->command_size);

	अणु
		काष्ठा qxl_drawable *draw = fb_cmd;

		draw->mm_समय = qdev->rom->mm_घड़ी;
	पूर्ण

	qxl_bo_kunmap_atomic_page(qdev, cmd_bo, fb_cmd);
	अगर (unwritten) अणु
		DRM_ERROR("got unwritten %d\n", unwritten);
		ret = -EFAULT;
		जाओ out_मुक्त_release;
	पूर्ण

	/* fill out reloc info काष्ठाs */
	num_relocs = 0;
	क्रम (i = 0; i < cmd->relocs_num; ++i) अणु
		काष्ठा drm_qxl_reloc reloc;
		काष्ठा drm_qxl_reloc __user *u = u64_to_user_ptr(cmd->relocs);

		अगर (copy_from_user(&reloc, u + i, माप(reloc))) अणु
			ret = -EFAULT;
			जाओ out_मुक्त_bos;
		पूर्ण

		/* add the bos to the list of bos to validate -
		   need to validate first then process relocs? */
		अगर (reloc.reloc_type != QXL_RELOC_TYPE_BO && reloc.reloc_type != QXL_RELOC_TYPE_SURF) अणु
			DRM_DEBUG("unknown reloc type %d\n", reloc.reloc_type);

			ret = -EINVAL;
			जाओ out_मुक्त_bos;
		पूर्ण
		reloc_info[i].type = reloc.reloc_type;

		अगर (reloc.dst_handle) अणु
			ret = qxlhw_handle_to_bo(file_priv, reloc.dst_handle, release,
						 &reloc_info[i].dst_bo);
			अगर (ret)
				जाओ out_मुक्त_bos;
			reloc_info[i].dst_offset = reloc.dst_offset;
		पूर्ण अन्यथा अणु
			reloc_info[i].dst_bo = cmd_bo;
			reloc_info[i].dst_offset = reloc.dst_offset + release->release_offset;
		पूर्ण
		num_relocs++;

		/* reserve and validate the reloc dst bo */
		अगर (reloc.reloc_type == QXL_RELOC_TYPE_BO || reloc.src_handle) अणु
			ret = qxlhw_handle_to_bo(file_priv, reloc.src_handle, release,
						 &reloc_info[i].src_bo);
			अगर (ret)
				जाओ out_मुक्त_bos;
			reloc_info[i].src_offset = reloc.src_offset;
		पूर्ण अन्यथा अणु
			reloc_info[i].src_bo = शून्य;
			reloc_info[i].src_offset = 0;
		पूर्ण
	पूर्ण

	/* validate all buffers */
	ret = qxl_release_reserve_list(release, false);
	अगर (ret)
		जाओ out_मुक्त_bos;

	क्रम (i = 0; i < cmd->relocs_num; ++i) अणु
		अगर (reloc_info[i].type == QXL_RELOC_TYPE_BO)
			apply_reloc(qdev, &reloc_info[i]);
		अन्यथा अगर (reloc_info[i].type == QXL_RELOC_TYPE_SURF)
			apply_surf_reloc(qdev, &reloc_info[i]);
	पूर्ण

	qxl_release_fence_buffer_objects(release);
	ret = qxl_push_command_ring_release(qdev, release, cmd->type, true);

out_मुक्त_bos:
out_मुक्त_release:
	अगर (ret)
		qxl_release_मुक्त(qdev, release);
out_मुक्त_reloc:
	kमुक्त(reloc_info);
	वापस ret;
पूर्ण

अटल पूर्णांक qxl_execbuffer_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv)
अणु
	काष्ठा qxl_device *qdev = to_qxl(dev);
	काष्ठा drm_qxl_execbuffer *execbuffer = data;
	काष्ठा drm_qxl_command user_cmd;
	पूर्णांक cmd_num;
	पूर्णांक ret;

	क्रम (cmd_num = 0; cmd_num < execbuffer->commands_num; ++cmd_num) अणु

		काष्ठा drm_qxl_command __user *commands =
			u64_to_user_ptr(execbuffer->commands);

		अगर (copy_from_user(&user_cmd, commands + cmd_num,
				       माप(user_cmd)))
			वापस -EFAULT;

		ret = qxl_process_single_command(qdev, &user_cmd, file_priv);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qxl_update_area_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file)
अणु
	काष्ठा qxl_device *qdev = to_qxl(dev);
	काष्ठा drm_qxl_update_area *update_area = data;
	काष्ठा qxl_rect area = अणु.left = update_area->left,
				.top = update_area->top,
				.right = update_area->right,
				.bottom = update_area->bottomपूर्ण;
	पूर्णांक ret;
	काष्ठा drm_gem_object *gobj = शून्य;
	काष्ठा qxl_bo *qobj = शून्य;
	काष्ठा tपंचांग_operation_ctx ctx = अणु true, false पूर्ण;

	अगर (update_area->left >= update_area->right ||
	    update_area->top >= update_area->bottom)
		वापस -EINVAL;

	gobj = drm_gem_object_lookup(file, update_area->handle);
	अगर (gobj == शून्य)
		वापस -ENOENT;

	qobj = gem_to_qxl_bo(gobj);

	ret = qxl_bo_reserve(qobj);
	अगर (ret)
		जाओ out;

	अगर (!qobj->tbo.pin_count) अणु
		qxl_tपंचांग_placement_from_करोमुख्य(qobj, qobj->type);
		ret = tपंचांग_bo_validate(&qobj->tbo, &qobj->placement, &ctx);
		अगर (unlikely(ret))
			जाओ out;
	पूर्ण

	ret = qxl_bo_check_id(qdev, qobj);
	अगर (ret)
		जाओ out2;
	अगर (!qobj->surface_id)
		DRM_ERROR("got update area for surface with no id %d\n", update_area->handle);
	ret = qxl_io_update_area(qdev, qobj, &area);

out2:
	qxl_bo_unreserve(qobj);

out:
	drm_gem_object_put(gobj);
	वापस ret;
पूर्ण

अटल पूर्णांक qxl_getparam_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा qxl_device *qdev = to_qxl(dev);
	काष्ठा drm_qxl_getparam *param = data;

	चयन (param->param) अणु
	हाल QXL_PARAM_NUM_SURFACES:
		param->value = qdev->rom->n_surfaces;
		अवरोध;
	हाल QXL_PARAM_MAX_RELOCS:
		param->value = QXL_MAX_RES;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qxl_clientcap_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file_priv)
अणु
	काष्ठा qxl_device *qdev = to_qxl(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा drm_qxl_clientcap *param = data;
	पूर्णांक byte, idx;

	byte = param->index / 8;
	idx = param->index % 8;

	अगर (pdev->revision < 4)
		वापस -ENOSYS;

	अगर (byte >= 58)
		वापस -ENOSYS;

	अगर (qdev->rom->client_capabilities[byte] & (1 << idx))
		वापस 0;
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक qxl_alloc_surf_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file)
अणु
	काष्ठा qxl_device *qdev = to_qxl(dev);
	काष्ठा drm_qxl_alloc_surf *param = data;
	काष्ठा qxl_bo *qobj;
	पूर्णांक handle;
	पूर्णांक ret;
	पूर्णांक size, actual_stride;
	काष्ठा qxl_surface surf;

	/* work out size allocate bo with handle */
	actual_stride = param->stride < 0 ? -param->stride : param->stride;
	size = actual_stride * param->height + actual_stride;

	surf.क्रमmat = param->क्रमmat;
	surf.width = param->width;
	surf.height = param->height;
	surf.stride = param->stride;
	surf.data = 0;

	ret = qxl_gem_object_create_with_handle(qdev, file,
						QXL_GEM_DOMAIN_SURFACE,
						size,
						&surf,
						&qobj, &handle);
	अगर (ret) अणु
		DRM_ERROR("%s: failed to create gem ret=%d\n",
			  __func__, ret);
		वापस -ENOMEM;
	पूर्ण अन्यथा
		param->handle = handle;
	वापस ret;
पूर्ण

स्थिर काष्ठा drm_ioctl_desc qxl_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(QXL_ALLOC, qxl_alloc_ioctl, DRM_AUTH),

	DRM_IOCTL_DEF_DRV(QXL_MAP, qxl_map_ioctl, DRM_AUTH),

	DRM_IOCTL_DEF_DRV(QXL_EXECBUFFER, qxl_execbuffer_ioctl,
							DRM_AUTH),
	DRM_IOCTL_DEF_DRV(QXL_UPDATE_AREA, qxl_update_area_ioctl,
							DRM_AUTH),
	DRM_IOCTL_DEF_DRV(QXL_GETPARAM, qxl_getparam_ioctl,
							DRM_AUTH),
	DRM_IOCTL_DEF_DRV(QXL_CLIENTCAP, qxl_clientcap_ioctl,
							DRM_AUTH),

	DRM_IOCTL_DEF_DRV(QXL_ALLOC_SURF, qxl_alloc_surf_ioctl,
			  DRM_AUTH),
पूर्ण;

पूर्णांक qxl_max_ioctls = ARRAY_SIZE(qxl_ioctls);
