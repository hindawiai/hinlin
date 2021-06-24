<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2009-2015 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#समावेश <drm/tपंचांग/tपंचांग_placement.h>

#समावेश "vmwgfx_drv.h"
#समावेश "vmwgfx_resource_priv.h"
#समावेश "vmwgfx_so.h"
#समावेश "vmwgfx_binding.h"
#समावेश "device_include/svga3d_surfacedefs.h"

#घोषणा SVGA3D_FLAGS_64(upper32, lower32) (((uपूर्णांक64_t)upper32 << 32) | lower32)
#घोषणा SVGA3D_FLAGS_UPPER_32(svga3d_flags) (svga3d_flags >> 32)
#घोषणा SVGA3D_FLAGS_LOWER_32(svga3d_flags) \
	(svga3d_flags & ((uपूर्णांक64_t)U32_MAX))

/**
 * काष्ठा vmw_user_surface - User-space visible surface resource
 *
 * @prime:          The TTM prime object.
 * @base:           The TTM base object handling user-space visibility.
 * @srf:            The surface metadata.
 * @size:           TTM accounting size क्रम the surface.
 * @master:         Master of the creating client. Used क्रम security check.
 * @backup_base:    The TTM base object of the backup buffer.
 */
काष्ठा vmw_user_surface अणु
	काष्ठा tपंचांग_prime_object prime;
	काष्ठा vmw_surface srf;
	uपूर्णांक32_t size;
	काष्ठा drm_master *master;
	काष्ठा tपंचांग_base_object *backup_base;
पूर्ण;

/**
 * काष्ठा vmw_surface_offset - Backing store mip level offset info
 *
 * @face:           Surface face.
 * @mip:            Mip level.
 * @bo_offset:      Offset पूर्णांकo backing store of this mip level.
 *
 */
काष्ठा vmw_surface_offset अणु
	uपूर्णांक32_t face;
	uपूर्णांक32_t mip;
	uपूर्णांक32_t bo_offset;
पूर्ण;

/**
 * काष्ठा vmw_surface_dirty - Surface dirty-tracker
 * @cache: Cached layout inक्रमmation of the surface.
 * @size: Accounting size क्रम the काष्ठा vmw_surface_dirty.
 * @num_subres: Number of subresources.
 * @boxes: Array of SVGA3dBoxes indicating dirty regions. One per subresource.
 */
काष्ठा vmw_surface_dirty अणु
	काष्ठा svga3dsurface_cache cache;
	माप_प्रकार size;
	u32 num_subres;
	SVGA3dBox boxes[];
पूर्ण;

अटल व्योम vmw_user_surface_मुक्त(काष्ठा vmw_resource *res);
अटल काष्ठा vmw_resource *
vmw_user_surface_base_to_res(काष्ठा tपंचांग_base_object *base);
अटल पूर्णांक vmw_legacy_srf_bind(काष्ठा vmw_resource *res,
			       काष्ठा tपंचांग_validate_buffer *val_buf);
अटल पूर्णांक vmw_legacy_srf_unbind(काष्ठा vmw_resource *res,
				 bool पढ़ोback,
				 काष्ठा tपंचांग_validate_buffer *val_buf);
अटल पूर्णांक vmw_legacy_srf_create(काष्ठा vmw_resource *res);
अटल पूर्णांक vmw_legacy_srf_destroy(काष्ठा vmw_resource *res);
अटल पूर्णांक vmw_gb_surface_create(काष्ठा vmw_resource *res);
अटल पूर्णांक vmw_gb_surface_bind(काष्ठा vmw_resource *res,
			       काष्ठा tपंचांग_validate_buffer *val_buf);
अटल पूर्णांक vmw_gb_surface_unbind(काष्ठा vmw_resource *res,
				 bool पढ़ोback,
				 काष्ठा tपंचांग_validate_buffer *val_buf);
अटल पूर्णांक vmw_gb_surface_destroy(काष्ठा vmw_resource *res);
अटल पूर्णांक
vmw_gb_surface_define_पूर्णांकernal(काष्ठा drm_device *dev,
			       काष्ठा drm_vmw_gb_surface_create_ext_req *req,
			       काष्ठा drm_vmw_gb_surface_create_rep *rep,
			       काष्ठा drm_file *file_priv);
अटल पूर्णांक
vmw_gb_surface_reference_पूर्णांकernal(काष्ठा drm_device *dev,
				  काष्ठा drm_vmw_surface_arg *req,
				  काष्ठा drm_vmw_gb_surface_ref_ext_rep *rep,
				  काष्ठा drm_file *file_priv);

अटल व्योम vmw_surface_dirty_मुक्त(काष्ठा vmw_resource *res);
अटल पूर्णांक vmw_surface_dirty_alloc(काष्ठा vmw_resource *res);
अटल पूर्णांक vmw_surface_dirty_sync(काष्ठा vmw_resource *res);
अटल व्योम vmw_surface_dirty_range_add(काष्ठा vmw_resource *res, माप_प्रकार start,
					माप_प्रकार end);
अटल पूर्णांक vmw_surface_clean(काष्ठा vmw_resource *res);

अटल स्थिर काष्ठा vmw_user_resource_conv user_surface_conv = अणु
	.object_type = VMW_RES_SURFACE,
	.base_obj_to_res = vmw_user_surface_base_to_res,
	.res_मुक्त = vmw_user_surface_मुक्त
पूर्ण;

स्थिर काष्ठा vmw_user_resource_conv *user_surface_converter =
	&user_surface_conv;


अटल uपूर्णांक64_t vmw_user_surface_size;

अटल स्थिर काष्ठा vmw_res_func vmw_legacy_surface_func = अणु
	.res_type = vmw_res_surface,
	.needs_backup = false,
	.may_evict = true,
	.prio = 1,
	.dirty_prio = 1,
	.type_name = "legacy surfaces",
	.backup_placement = &vmw_srf_placement,
	.create = &vmw_legacy_srf_create,
	.destroy = &vmw_legacy_srf_destroy,
	.bind = &vmw_legacy_srf_bind,
	.unbind = &vmw_legacy_srf_unbind
पूर्ण;

अटल स्थिर काष्ठा vmw_res_func vmw_gb_surface_func = अणु
	.res_type = vmw_res_surface,
	.needs_backup = true,
	.may_evict = true,
	.prio = 1,
	.dirty_prio = 2,
	.type_name = "guest backed surfaces",
	.backup_placement = &vmw_mob_placement,
	.create = vmw_gb_surface_create,
	.destroy = vmw_gb_surface_destroy,
	.bind = vmw_gb_surface_bind,
	.unbind = vmw_gb_surface_unbind,
	.dirty_alloc = vmw_surface_dirty_alloc,
	.dirty_मुक्त = vmw_surface_dirty_मुक्त,
	.dirty_sync = vmw_surface_dirty_sync,
	.dirty_range_add = vmw_surface_dirty_range_add,
	.clean = vmw_surface_clean,
पूर्ण;

/*
 * काष्ठा vmw_surface_dma - SVGA3D DMA command
 */
काष्ठा vmw_surface_dma अणु
	SVGA3dCmdHeader header;
	SVGA3dCmdSurfaceDMA body;
	SVGA3dCopyBox cb;
	SVGA3dCmdSurfaceDMASuffix suffix;
पूर्ण;

/*
 * काष्ठा vmw_surface_define - SVGA3D Surface Define command
 */
काष्ठा vmw_surface_define अणु
	SVGA3dCmdHeader header;
	SVGA3dCmdDefineSurface body;
पूर्ण;

/*
 * काष्ठा vmw_surface_destroy - SVGA3D Surface Destroy command
 */
काष्ठा vmw_surface_destroy अणु
	SVGA3dCmdHeader header;
	SVGA3dCmdDestroySurface body;
पूर्ण;


/**
 * vmw_surface_dma_size - Compute fअगरo size क्रम a dma command.
 *
 * @srf: Poपूर्णांकer to a काष्ठा vmw_surface
 *
 * Computes the required size क्रम a surface dma command क्रम backup or
 * restoration of the surface represented by @srf.
 */
अटल अंतरभूत uपूर्णांक32_t vmw_surface_dma_size(स्थिर काष्ठा vmw_surface *srf)
अणु
	वापस srf->metadata.num_sizes * माप(काष्ठा vmw_surface_dma);
पूर्ण


/**
 * vmw_surface_define_size - Compute fअगरo size क्रम a surface define command.
 *
 * @srf: Poपूर्णांकer to a काष्ठा vmw_surface
 *
 * Computes the required size क्रम a surface define command क्रम the definition
 * of the surface represented by @srf.
 */
अटल अंतरभूत uपूर्णांक32_t vmw_surface_define_size(स्थिर काष्ठा vmw_surface *srf)
अणु
	वापस माप(काष्ठा vmw_surface_define) + srf->metadata.num_sizes *
		माप(SVGA3dSize);
पूर्ण


/**
 * vmw_surface_destroy_size - Compute fअगरo size क्रम a surface destroy command.
 *
 * Computes the required size क्रम a surface destroy command क्रम the deकाष्ठाion
 * of a hw surface.
 */
अटल अंतरभूत uपूर्णांक32_t vmw_surface_destroy_size(व्योम)
अणु
	वापस माप(काष्ठा vmw_surface_destroy);
पूर्ण

/**
 * vmw_surface_destroy_encode - Encode a surface_destroy command.
 *
 * @id: The surface id
 * @cmd_space: Poपूर्णांकer to memory area in which the commands should be encoded.
 */
अटल व्योम vmw_surface_destroy_encode(uपूर्णांक32_t id,
				       व्योम *cmd_space)
अणु
	काष्ठा vmw_surface_destroy *cmd = (काष्ठा vmw_surface_destroy *)
		cmd_space;

	cmd->header.id = SVGA_3D_CMD_SURFACE_DESTROY;
	cmd->header.size = माप(cmd->body);
	cmd->body.sid = id;
पूर्ण

/**
 * vmw_surface_define_encode - Encode a surface_define command.
 *
 * @srf: Poपूर्णांकer to a काष्ठा vmw_surface object.
 * @cmd_space: Poपूर्णांकer to memory area in which the commands should be encoded.
 */
अटल व्योम vmw_surface_define_encode(स्थिर काष्ठा vmw_surface *srf,
				      व्योम *cmd_space)
अणु
	काष्ठा vmw_surface_define *cmd = (काष्ठा vmw_surface_define *)
		cmd_space;
	काष्ठा drm_vmw_size *src_size;
	SVGA3dSize *cmd_size;
	uपूर्णांक32_t cmd_len;
	पूर्णांक i;

	cmd_len = माप(cmd->body) + srf->metadata.num_sizes *
		माप(SVGA3dSize);

	cmd->header.id = SVGA_3D_CMD_SURFACE_DEFINE;
	cmd->header.size = cmd_len;
	cmd->body.sid = srf->res.id;
	/*
	 * Downcast of surfaceFlags, was upcasted when received from user-space,
	 * since driver पूर्णांकernally stores as 64 bit.
	 * For legacy surface define only 32 bit flag is supported.
	 */
	cmd->body.surfaceFlags = (SVGA3dSurface1Flags)srf->metadata.flags;
	cmd->body.क्रमmat = srf->metadata.क्रमmat;
	क्रम (i = 0; i < DRM_VMW_MAX_SURFACE_FACES; ++i)
		cmd->body.face[i].numMipLevels = srf->metadata.mip_levels[i];

	cmd += 1;
	cmd_size = (SVGA3dSize *) cmd;
	src_size = srf->metadata.sizes;

	क्रम (i = 0; i < srf->metadata.num_sizes; ++i, cmd_size++, src_size++) अणु
		cmd_size->width = src_size->width;
		cmd_size->height = src_size->height;
		cmd_size->depth = src_size->depth;
	पूर्ण
पूर्ण

/**
 * vmw_surface_dma_encode - Encode a surface_dma command.
 *
 * @srf: Poपूर्णांकer to a काष्ठा vmw_surface object.
 * @cmd_space: Poपूर्णांकer to memory area in which the commands should be encoded.
 * @ptr: Poपूर्णांकer to an SVGAGuestPtr indicating where the surface contents
 * should be placed or पढ़ो from.
 * @to_surface: Boolean whether to DMA to the surface or from the surface.
 */
अटल व्योम vmw_surface_dma_encode(काष्ठा vmw_surface *srf,
				   व्योम *cmd_space,
				   स्थिर SVGAGuestPtr *ptr,
				   bool to_surface)
अणु
	uपूर्णांक32_t i;
	काष्ठा vmw_surface_dma *cmd = (काष्ठा vmw_surface_dma *)cmd_space;
	स्थिर काष्ठा svga3d_surface_desc *desc =
		svga3dsurface_get_desc(srf->metadata.क्रमmat);

	क्रम (i = 0; i < srf->metadata.num_sizes; ++i) अणु
		SVGA3dCmdHeader *header = &cmd->header;
		SVGA3dCmdSurfaceDMA *body = &cmd->body;
		SVGA3dCopyBox *cb = &cmd->cb;
		SVGA3dCmdSurfaceDMASuffix *suffix = &cmd->suffix;
		स्थिर काष्ठा vmw_surface_offset *cur_offset = &srf->offsets[i];
		स्थिर काष्ठा drm_vmw_size *cur_size = &srf->metadata.sizes[i];

		header->id = SVGA_3D_CMD_SURFACE_DMA;
		header->size = माप(*body) + माप(*cb) + माप(*suffix);

		body->guest.ptr = *ptr;
		body->guest.ptr.offset += cur_offset->bo_offset;
		body->guest.pitch = svga3dsurface_calculate_pitch(desc,
								  cur_size);
		body->host.sid = srf->res.id;
		body->host.face = cur_offset->face;
		body->host.mipmap = cur_offset->mip;
		body->transfer = ((to_surface) ?  SVGA3D_WRITE_HOST_VRAM :
				  SVGA3D_READ_HOST_VRAM);
		cb->x = 0;
		cb->y = 0;
		cb->z = 0;
		cb->srcx = 0;
		cb->srcy = 0;
		cb->srcz = 0;
		cb->w = cur_size->width;
		cb->h = cur_size->height;
		cb->d = cur_size->depth;

		suffix->suffixSize = माप(*suffix);
		suffix->maximumOffset =
			svga3dsurface_get_image_buffer_size(desc, cur_size,
							    body->guest.pitch);
		suffix->flags.discard = 0;
		suffix->flags.unsynchronized = 0;
		suffix->flags.reserved = 0;
		++cmd;
	पूर्ण
पूर्ण;


/**
 * vmw_hw_surface_destroy - destroy a Device surface
 *
 * @res:        Poपूर्णांकer to a काष्ठा vmw_resource embedded in a काष्ठा
 *              vmw_surface.
 *
 * Destroys a the device surface associated with a काष्ठा vmw_surface अगर
 * any, and adjusts accounting and resource count accordingly.
 */
अटल व्योम vmw_hw_surface_destroy(काष्ठा vmw_resource *res)
अणु

	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	व्योम *cmd;

	अगर (res->func->destroy == vmw_gb_surface_destroy) अणु
		(व्योम) vmw_gb_surface_destroy(res);
		वापस;
	पूर्ण

	अगर (res->id != -1) अणु

		cmd = VMW_CMD_RESERVE(dev_priv, vmw_surface_destroy_size());
		अगर (unlikely(!cmd))
			वापस;

		vmw_surface_destroy_encode(res->id, cmd);
		vmw_cmd_commit(dev_priv, vmw_surface_destroy_size());

		/*
		 * used_memory_size_atomic, or separate lock
		 * to aव्योम taking dev_priv::cmdbuf_mutex in
		 * the destroy path.
		 */

		mutex_lock(&dev_priv->cmdbuf_mutex);
		dev_priv->used_memory_size -= res->backup_size;
		mutex_unlock(&dev_priv->cmdbuf_mutex);
	पूर्ण
पूर्ण

/**
 * vmw_legacy_srf_create - Create a device surface as part of the
 * resource validation process.
 *
 * @res: Poपूर्णांकer to a काष्ठा vmw_surface.
 *
 * If the surface करोesn't have a hw id.
 *
 * Returns -EBUSY अगर there wasn't sufficient device resources to
 * complete the validation. Retry after मुक्तing up resources.
 *
 * May वापस other errors अगर the kernel is out of guest resources.
 */
अटल पूर्णांक vmw_legacy_srf_create(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_surface *srf;
	uपूर्णांक32_t submit_size;
	uपूर्णांक8_t *cmd;
	पूर्णांक ret;

	अगर (likely(res->id != -1))
		वापस 0;

	srf = vmw_res_to_srf(res);
	अगर (unlikely(dev_priv->used_memory_size + res->backup_size >=
		     dev_priv->memory_size))
		वापस -EBUSY;

	/*
	 * Alloc id क्रम the resource.
	 */

	ret = vmw_resource_alloc_id(res);
	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Failed to allocate a surface id.\n");
		जाओ out_no_id;
	पूर्ण

	अगर (unlikely(res->id >= SVGA3D_MAX_SURFACE_IDS)) अणु
		ret = -EBUSY;
		जाओ out_no_fअगरo;
	पूर्ण

	/*
	 * Encode surface define- commands.
	 */

	submit_size = vmw_surface_define_size(srf);
	cmd = VMW_CMD_RESERVE(dev_priv, submit_size);
	अगर (unlikely(!cmd)) अणु
		ret = -ENOMEM;
		जाओ out_no_fअगरo;
	पूर्ण

	vmw_surface_define_encode(srf, cmd);
	vmw_cmd_commit(dev_priv, submit_size);
	vmw_fअगरo_resource_inc(dev_priv);

	/*
	 * Surface memory usage accounting.
	 */

	dev_priv->used_memory_size += res->backup_size;
	वापस 0;

out_no_fअगरo:
	vmw_resource_release_id(res);
out_no_id:
	वापस ret;
पूर्ण

/**
 * vmw_legacy_srf_dma - Copy backup data to or from a legacy surface.
 *
 * @res:            Poपूर्णांकer to a काष्ठा vmw_res embedded in a काष्ठा
 *                  vmw_surface.
 * @val_buf:        Poपूर्णांकer to a काष्ठा tपंचांग_validate_buffer containing
 *                  inक्रमmation about the backup buffer.
 * @bind:           Boolean wether to DMA to the surface.
 *
 * Transfer backup data to or from a legacy surface as part of the
 * validation process.
 * May वापस other errors अगर the kernel is out of guest resources.
 * The backup buffer will be fenced or idle upon successful completion,
 * and अगर the surface needs persistent backup storage, the backup buffer
 * will also be वापसed reserved अगरf @bind is true.
 */
अटल पूर्णांक vmw_legacy_srf_dma(काष्ठा vmw_resource *res,
			      काष्ठा tपंचांग_validate_buffer *val_buf,
			      bool bind)
अणु
	SVGAGuestPtr ptr;
	काष्ठा vmw_fence_obj *fence;
	uपूर्णांक32_t submit_size;
	काष्ठा vmw_surface *srf = vmw_res_to_srf(res);
	uपूर्णांक8_t *cmd;
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;

	BUG_ON(!val_buf->bo);
	submit_size = vmw_surface_dma_size(srf);
	cmd = VMW_CMD_RESERVE(dev_priv, submit_size);
	अगर (unlikely(!cmd))
		वापस -ENOMEM;

	vmw_bo_get_guest_ptr(val_buf->bo, &ptr);
	vmw_surface_dma_encode(srf, cmd, &ptr, bind);

	vmw_cmd_commit(dev_priv, submit_size);

	/*
	 * Create a fence object and fence the backup buffer.
	 */

	(व्योम) vmw_execbuf_fence_commands(शून्य, dev_priv,
					  &fence, शून्य);

	vmw_bo_fence_single(val_buf->bo, fence);

	अगर (likely(fence != शून्य))
		vmw_fence_obj_unreference(&fence);

	वापस 0;
पूर्ण

/**
 * vmw_legacy_srf_bind - Perक्रमm a legacy surface bind as part of the
 *                       surface validation process.
 *
 * @res:            Poपूर्णांकer to a काष्ठा vmw_res embedded in a काष्ठा
 *                  vmw_surface.
 * @val_buf:        Poपूर्णांकer to a काष्ठा tपंचांग_validate_buffer containing
 *                  inक्रमmation about the backup buffer.
 *
 * This function will copy backup data to the surface अगर the
 * backup buffer is dirty.
 */
अटल पूर्णांक vmw_legacy_srf_bind(काष्ठा vmw_resource *res,
			       काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	अगर (!res->backup_dirty)
		वापस 0;

	वापस vmw_legacy_srf_dma(res, val_buf, true);
पूर्ण


/**
 * vmw_legacy_srf_unbind - Perक्रमm a legacy surface unbind as part of the
 *                         surface eviction process.
 *
 * @res:            Poपूर्णांकer to a काष्ठा vmw_res embedded in a काष्ठा
 *                  vmw_surface.
 * @पढ़ोback:       Readback - only true अगर dirty
 * @val_buf:        Poपूर्णांकer to a काष्ठा tपंचांग_validate_buffer containing
 *                  inक्रमmation about the backup buffer.
 *
 * This function will copy backup data from the surface.
 */
अटल पूर्णांक vmw_legacy_srf_unbind(काष्ठा vmw_resource *res,
				 bool पढ़ोback,
				 काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	अगर (unlikely(पढ़ोback))
		वापस vmw_legacy_srf_dma(res, val_buf, false);
	वापस 0;
पूर्ण

/**
 * vmw_legacy_srf_destroy - Destroy a device surface as part of a
 *                          resource eviction process.
 *
 * @res:            Poपूर्णांकer to a काष्ठा vmw_res embedded in a काष्ठा
 *                  vmw_surface.
 */
अटल पूर्णांक vmw_legacy_srf_destroy(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	uपूर्णांक32_t submit_size;
	uपूर्णांक8_t *cmd;

	BUG_ON(res->id == -1);

	/*
	 * Encode the dma- and surface destroy commands.
	 */

	submit_size = vmw_surface_destroy_size();
	cmd = VMW_CMD_RESERVE(dev_priv, submit_size);
	अगर (unlikely(!cmd))
		वापस -ENOMEM;

	vmw_surface_destroy_encode(res->id, cmd);
	vmw_cmd_commit(dev_priv, submit_size);

	/*
	 * Surface memory usage accounting.
	 */

	dev_priv->used_memory_size -= res->backup_size;

	/*
	 * Release the surface ID.
	 */

	vmw_resource_release_id(res);
	vmw_fअगरo_resource_dec(dev_priv);

	वापस 0;
पूर्ण


/**
 * vmw_surface_init - initialize a काष्ठा vmw_surface
 *
 * @dev_priv:       Poपूर्णांकer to a device निजी काष्ठा.
 * @srf:            Poपूर्णांकer to the काष्ठा vmw_surface to initialize.
 * @res_मुक्त:       Poपूर्णांकer to a resource deकाष्ठाor used to मुक्त
 *                  the object.
 */
अटल पूर्णांक vmw_surface_init(काष्ठा vmw_निजी *dev_priv,
			    काष्ठा vmw_surface *srf,
			    व्योम (*res_मुक्त) (काष्ठा vmw_resource *res))
अणु
	पूर्णांक ret;
	काष्ठा vmw_resource *res = &srf->res;

	BUG_ON(!res_मुक्त);
	ret = vmw_resource_init(dev_priv, res, true, res_मुक्त,
				(dev_priv->has_mob) ? &vmw_gb_surface_func :
				&vmw_legacy_surface_func);

	अगर (unlikely(ret != 0)) अणु
		res_मुक्त(res);
		वापस ret;
	पूर्ण

	/*
	 * The surface won't be visible to hardware until a
	 * surface validate.
	 */

	INIT_LIST_HEAD(&srf->view_list);
	res->hw_destroy = vmw_hw_surface_destroy;
	वापस ret;
पूर्ण

/**
 * vmw_user_surface_base_to_res - TTM base object to resource converter क्रम
 *                                user visible surfaces
 *
 * @base:           Poपूर्णांकer to a TTM base object
 *
 * Returns the काष्ठा vmw_resource embedded in a काष्ठा vmw_surface
 * क्रम the user-visible object identअगरied by the TTM base object @base.
 */
अटल काष्ठा vmw_resource *
vmw_user_surface_base_to_res(काष्ठा tपंचांग_base_object *base)
अणु
	वापस &(container_of(base, काष्ठा vmw_user_surface,
			      prime.base)->srf.res);
पूर्ण

/**
 * vmw_user_surface_मुक्त - User visible surface resource deकाष्ठाor
 *
 * @res:            A काष्ठा vmw_resource embedded in a काष्ठा vmw_surface.
 */
अटल व्योम vmw_user_surface_मुक्त(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_surface *srf = vmw_res_to_srf(res);
	काष्ठा vmw_user_surface *user_srf =
	    container_of(srf, काष्ठा vmw_user_surface, srf);
	काष्ठा vmw_निजी *dev_priv = srf->res.dev_priv;
	uपूर्णांक32_t size = user_srf->size;

	WARN_ON_ONCE(res->dirty);
	अगर (user_srf->master)
		drm_master_put(&user_srf->master);
	kमुक्त(srf->offsets);
	kमुक्त(srf->metadata.sizes);
	kमुक्त(srf->snooper.image);
	tपंचांग_prime_object_kमुक्त(user_srf, prime);
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv), size);
पूर्ण

/**
 * vmw_user_surface_मुक्त - User visible surface TTM base object deकाष्ठाor
 *
 * @p_base:         Poपूर्णांकer to a poपूर्णांकer to a TTM base object
 *                  embedded in a काष्ठा vmw_user_surface.
 *
 * Drops the base object's reference on its resource, and the
 * poपूर्णांकer poपूर्णांकed to by *p_base is set to शून्य.
 */
अटल व्योम vmw_user_surface_base_release(काष्ठा tपंचांग_base_object **p_base)
अणु
	काष्ठा tपंचांग_base_object *base = *p_base;
	काष्ठा vmw_user_surface *user_srf =
	    container_of(base, काष्ठा vmw_user_surface, prime.base);
	काष्ठा vmw_resource *res = &user_srf->srf.res;

	*p_base = शून्य;
	अगर (user_srf->backup_base)
		tपंचांग_base_object_unref(&user_srf->backup_base);
	vmw_resource_unreference(&res);
पूर्ण

/**
 * vmw_user_surface_destroy_ioctl - Ioctl function implementing
 *                                  the user surface destroy functionality.
 *
 * @dev:            Poपूर्णांकer to a काष्ठा drm_device.
 * @data:           Poपूर्णांकer to data copied from / to user-space.
 * @file_priv:      Poपूर्णांकer to a drm file निजी काष्ठाure.
 */
पूर्णांक vmw_surface_destroy_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vmw_surface_arg *arg = (काष्ठा drm_vmw_surface_arg *)data;
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;

	वापस tपंचांग_ref_object_base_unref(tfile, arg->sid, TTM_REF_USAGE);
पूर्ण

/**
 * vmw_user_surface_define_ioctl - Ioctl function implementing
 *                                  the user surface define functionality.
 *
 * @dev:            Poपूर्णांकer to a काष्ठा drm_device.
 * @data:           Poपूर्णांकer to data copied from / to user-space.
 * @file_priv:      Poपूर्णांकer to a drm file निजी काष्ठाure.
 */
पूर्णांक vmw_surface_define_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file_priv)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा vmw_user_surface *user_srf;
	काष्ठा vmw_surface *srf;
	काष्ठा vmw_surface_metadata *metadata;
	काष्ठा vmw_resource *res;
	काष्ठा vmw_resource *पंचांगp;
	जोड़ drm_vmw_surface_create_arg *arg =
	    (जोड़ drm_vmw_surface_create_arg *)data;
	काष्ठा drm_vmw_surface_create_req *req = &arg->req;
	काष्ठा drm_vmw_surface_arg *rep = &arg->rep;
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = true,
		.no_रुको_gpu = false
	पूर्ण;
	पूर्णांक ret;
	पूर्णांक i, j;
	uपूर्णांक32_t cur_bo_offset;
	काष्ठा drm_vmw_size *cur_size;
	काष्ठा vmw_surface_offset *cur_offset;
	uपूर्णांक32_t num_sizes;
	uपूर्णांक32_t size;
	स्थिर काष्ठा svga3d_surface_desc *desc;

	अगर (unlikely(vmw_user_surface_size == 0))
		vmw_user_surface_size = tपंचांग_round_pot(माप(*user_srf)) +
			VMW_IDA_ACC_SIZE + TTM_OBJ_EXTRA_SIZE;

	num_sizes = 0;
	क्रम (i = 0; i < DRM_VMW_MAX_SURFACE_FACES; ++i) अणु
		अगर (req->mip_levels[i] > DRM_VMW_MAX_MIP_LEVELS)
			वापस -EINVAL;
		num_sizes += req->mip_levels[i];
	पूर्ण

	अगर (num_sizes > DRM_VMW_MAX_SURFACE_FACES * DRM_VMW_MAX_MIP_LEVELS ||
	    num_sizes == 0)
		वापस -EINVAL;

	size = vmw_user_surface_size +
		tपंचांग_round_pot(num_sizes * माप(काष्ठा drm_vmw_size)) +
		tपंचांग_round_pot(num_sizes * माप(काष्ठा vmw_surface_offset));

	desc = svga3dsurface_get_desc(req->क्रमmat);
	अगर (unlikely(desc->block_desc == SVGA3DBLOCKDESC_NONE)) अणु
		VMW_DEBUG_USER("Invalid format %d for surface creation.\n",
			       req->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	ret = tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, true);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = tपंचांग_mem_global_alloc(vmw_mem_glob(dev_priv),
				   size, &ctx);
	अगर (unlikely(ret != 0)) अणु
		अगर (ret != -ERESTARTSYS)
			DRM_ERROR("Out of graphics memory for surface.\n");
		जाओ out_unlock;
	पूर्ण

	user_srf = kzalloc(माप(*user_srf), GFP_KERNEL);
	अगर (unlikely(!user_srf)) अणु
		ret = -ENOMEM;
		जाओ out_no_user_srf;
	पूर्ण

	srf = &user_srf->srf;
	metadata = &srf->metadata;
	res = &srf->res;

	/* Driver पूर्णांकernally stores as 64-bit flags */
	metadata->flags = (SVGA3dSurfaceAllFlags)req->flags;
	metadata->क्रमmat = req->क्रमmat;
	metadata->scanout = req->scanout;

	स_नकल(metadata->mip_levels, req->mip_levels,
	       माप(metadata->mip_levels));
	metadata->num_sizes = num_sizes;
	user_srf->size = size;
	metadata->sizes =
		memdup_user((काष्ठा drm_vmw_size __user *)(अचिन्हित दीर्घ)
			    req->size_addr,
			    माप(*metadata->sizes) * metadata->num_sizes);
	अगर (IS_ERR(metadata->sizes)) अणु
		ret = PTR_ERR(metadata->sizes);
		जाओ out_no_sizes;
	पूर्ण
	srf->offsets = kदो_स्मृति_array(metadata->num_sizes, माप(*srf->offsets),
				     GFP_KERNEL);
	अगर (unlikely(!srf->offsets)) अणु
		ret = -ENOMEM;
		जाओ out_no_offsets;
	पूर्ण

	metadata->base_size = *srf->metadata.sizes;
	metadata->स्वतःgen_filter = SVGA3D_TEX_FILTER_NONE;
	metadata->multisample_count = 0;
	metadata->multisample_pattern = SVGA3D_MS_PATTERN_NONE;
	metadata->quality_level = SVGA3D_MS_QUALITY_NONE;

	cur_bo_offset = 0;
	cur_offset = srf->offsets;
	cur_size = metadata->sizes;

	क्रम (i = 0; i < DRM_VMW_MAX_SURFACE_FACES; ++i) अणु
		क्रम (j = 0; j < metadata->mip_levels[i]; ++j) अणु
			uपूर्णांक32_t stride = svga3dsurface_calculate_pitch
				(desc, cur_size);

			cur_offset->face = i;
			cur_offset->mip = j;
			cur_offset->bo_offset = cur_bo_offset;
			cur_bo_offset += svga3dsurface_get_image_buffer_size
				(desc, cur_size, stride);
			++cur_offset;
			++cur_size;
		पूर्ण
	पूर्ण
	res->backup_size = cur_bo_offset;
	अगर (metadata->scanout &&
	    metadata->num_sizes == 1 &&
	    metadata->sizes[0].width == 64 &&
	    metadata->sizes[0].height == 64 &&
	    metadata->क्रमmat == SVGA3D_A8R8G8B8) अणु

		srf->snooper.image = kzalloc(64 * 64 * 4, GFP_KERNEL);
		अगर (!srf->snooper.image) अणु
			DRM_ERROR("Failed to allocate cursor_image\n");
			ret = -ENOMEM;
			जाओ out_no_copy;
		पूर्ण
	पूर्ण अन्यथा अणु
		srf->snooper.image = शून्य;
	पूर्ण

	user_srf->prime.base.shareable = false;
	user_srf->prime.base.tfile = शून्य;
	अगर (drm_is_primary_client(file_priv))
		user_srf->master = drm_master_get(file_priv->master);

	/**
	 * From this poपूर्णांक, the generic resource management functions
	 * destroy the object on failure.
	 */

	ret = vmw_surface_init(dev_priv, srf, vmw_user_surface_मुक्त);
	अगर (unlikely(ret != 0))
		जाओ out_unlock;

	/*
	 * A gb-aware client referencing a shared surface will
	 * expect a backup buffer to be present.
	 */
	अगर (dev_priv->has_mob && req->shareable) अणु
		uपूर्णांक32_t backup_handle;

		ret = vmw_user_bo_alloc(dev_priv, tfile,
					res->backup_size,
					true,
					&backup_handle,
					&res->backup,
					&user_srf->backup_base);
		अगर (unlikely(ret != 0)) अणु
			vmw_resource_unreference(&res);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	पंचांगp = vmw_resource_reference(&srf->res);
	ret = tपंचांग_prime_object_init(tfile, res->backup_size, &user_srf->prime,
				    req->shareable, VMW_RES_SURFACE,
				    &vmw_user_surface_base_release, शून्य);

	अगर (unlikely(ret != 0)) अणु
		vmw_resource_unreference(&पंचांगp);
		vmw_resource_unreference(&res);
		जाओ out_unlock;
	पूर्ण

	rep->sid = user_srf->prime.base.handle;
	vmw_resource_unreference(&res);

	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
	वापस 0;
out_no_copy:
	kमुक्त(srf->offsets);
out_no_offsets:
	kमुक्त(metadata->sizes);
out_no_sizes:
	tपंचांग_prime_object_kमुक्त(user_srf, prime);
out_no_user_srf:
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv), size);
out_unlock:
	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
	वापस ret;
पूर्ण


अटल पूर्णांक
vmw_surface_handle_reference(काष्ठा vmw_निजी *dev_priv,
			     काष्ठा drm_file *file_priv,
			     uपूर्णांक32_t u_handle,
			     क्रमागत drm_vmw_handle_type handle_type,
			     काष्ठा tपंचांग_base_object **base_p)
अणु
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा vmw_user_surface *user_srf;
	uपूर्णांक32_t handle;
	काष्ठा tपंचांग_base_object *base;
	पूर्णांक ret;

	अगर (handle_type == DRM_VMW_HANDLE_PRIME) अणु
		ret = tपंचांग_prime_fd_to_handle(tfile, u_handle, &handle);
		अगर (unlikely(ret != 0))
			वापस ret;
	पूर्ण अन्यथा अणु
		handle = u_handle;
	पूर्ण

	ret = -EINVAL;
	base = tपंचांग_base_object_lookup_क्रम_ref(dev_priv->tdev, handle);
	अगर (unlikely(!base)) अणु
		VMW_DEBUG_USER("Could not find surface to reference.\n");
		जाओ out_no_lookup;
	पूर्ण

	अगर (unlikely(tपंचांग_base_object_type(base) != VMW_RES_SURFACE)) अणु
		VMW_DEBUG_USER("Referenced object is not a surface.\n");
		जाओ out_bad_resource;
	पूर्ण

	अगर (handle_type != DRM_VMW_HANDLE_PRIME) अणु
		bool require_exist = false;

		user_srf = container_of(base, काष्ठा vmw_user_surface,
					prime.base);

		/* Error out अगर we are unauthenticated primary */
		अगर (drm_is_primary_client(file_priv) &&
		    !file_priv->authenticated) अणु
			ret = -EACCES;
			जाओ out_bad_resource;
		पूर्ण

		/*
		 * Make sure the surface creator has the same
		 * authenticating master, or is alपढ़ोy रेजिस्टरed with us.
		 */
		अगर (drm_is_primary_client(file_priv) &&
		    user_srf->master != file_priv->master)
			require_exist = true;

		अगर (unlikely(drm_is_render_client(file_priv)))
			require_exist = true;

		ret = tपंचांग_ref_object_add(tfile, base, TTM_REF_USAGE, शून्य,
					 require_exist);
		अगर (unlikely(ret != 0)) अणु
			DRM_ERROR("Could not add a reference to a surface.\n");
			जाओ out_bad_resource;
		पूर्ण
	पूर्ण

	*base_p = base;
	वापस 0;

out_bad_resource:
	tपंचांग_base_object_unref(&base);
out_no_lookup:
	अगर (handle_type == DRM_VMW_HANDLE_PRIME)
		(व्योम) tपंचांग_ref_object_base_unref(tfile, handle, TTM_REF_USAGE);

	वापस ret;
पूर्ण

/**
 * vmw_user_surface_define_ioctl - Ioctl function implementing
 *                                  the user surface reference functionality.
 *
 * @dev:            Poपूर्णांकer to a काष्ठा drm_device.
 * @data:           Poपूर्णांकer to data copied from / to user-space.
 * @file_priv:      Poपूर्णांकer to a drm file निजी काष्ठाure.
 */
पूर्णांक vmw_surface_reference_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	जोड़ drm_vmw_surface_reference_arg *arg =
	    (जोड़ drm_vmw_surface_reference_arg *)data;
	काष्ठा drm_vmw_surface_arg *req = &arg->req;
	काष्ठा drm_vmw_surface_create_req *rep = &arg->rep;
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा vmw_surface *srf;
	काष्ठा vmw_user_surface *user_srf;
	काष्ठा drm_vmw_size __user *user_sizes;
	काष्ठा tपंचांग_base_object *base;
	पूर्णांक ret;

	ret = vmw_surface_handle_reference(dev_priv, file_priv, req->sid,
					   req->handle_type, &base);
	अगर (unlikely(ret != 0))
		वापस ret;

	user_srf = container_of(base, काष्ठा vmw_user_surface, prime.base);
	srf = &user_srf->srf;

	/* Downcast of flags when sending back to user space */
	rep->flags = (uपूर्णांक32_t)srf->metadata.flags;
	rep->क्रमmat = srf->metadata.क्रमmat;
	स_नकल(rep->mip_levels, srf->metadata.mip_levels,
	       माप(srf->metadata.mip_levels));
	user_sizes = (काष्ठा drm_vmw_size __user *)(अचिन्हित दीर्घ)
	    rep->size_addr;

	अगर (user_sizes)
		ret = copy_to_user(user_sizes, &srf->metadata.base_size,
				   माप(srf->metadata.base_size));
	अगर (unlikely(ret != 0)) अणु
		VMW_DEBUG_USER("copy_to_user failed %p %u\n", user_sizes,
			       srf->metadata.num_sizes);
		tपंचांग_ref_object_base_unref(tfile, base->handle, TTM_REF_USAGE);
		ret = -EFAULT;
	पूर्ण

	tपंचांग_base_object_unref(&base);

	वापस ret;
पूर्ण

/**
 * vmw_surface_define_encode - Encode a surface_define command.
 *
 * @res:        Poपूर्णांकer to a काष्ठा vmw_resource embedded in a काष्ठा
 *              vmw_surface.
 */
अटल पूर्णांक vmw_gb_surface_create(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_surface *srf = vmw_res_to_srf(res);
	काष्ठा vmw_surface_metadata *metadata = &srf->metadata;
	uपूर्णांक32_t cmd_len, cmd_id, submit_len;
	पूर्णांक ret;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDefineGBSurface body;
	पूर्ण *cmd;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDefineGBSurface_v2 body;
	पूर्ण *cmd2;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDefineGBSurface_v3 body;
	पूर्ण *cmd3;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDefineGBSurface_v4 body;
	पूर्ण *cmd4;

	अगर (likely(res->id != -1))
		वापस 0;

	vmw_fअगरo_resource_inc(dev_priv);
	ret = vmw_resource_alloc_id(res);
	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Failed to allocate a surface id.\n");
		जाओ out_no_id;
	पूर्ण

	अगर (unlikely(res->id >= VMWGFX_NUM_GB_SURFACE)) अणु
		ret = -EBUSY;
		जाओ out_no_fअगरo;
	पूर्ण

	अगर (has_sm5_context(dev_priv) && metadata->array_size > 0) अणु
		cmd_id = SVGA_3D_CMD_DEFINE_GB_SURFACE_V4;
		cmd_len = माप(cmd4->body);
		submit_len = माप(*cmd4);
	पूर्ण अन्यथा अगर (has_sm4_1_context(dev_priv) && metadata->array_size > 0) अणु
		cmd_id = SVGA_3D_CMD_DEFINE_GB_SURFACE_V3;
		cmd_len = माप(cmd3->body);
		submit_len = माप(*cmd3);
	पूर्ण अन्यथा अगर (metadata->array_size > 0) अणु
		/* VMW_SM_4 support verअगरied at creation समय. */
		cmd_id = SVGA_3D_CMD_DEFINE_GB_SURFACE_V2;
		cmd_len = माप(cmd2->body);
		submit_len = माप(*cmd2);
	पूर्ण अन्यथा अणु
		cmd_id = SVGA_3D_CMD_DEFINE_GB_SURFACE;
		cmd_len = माप(cmd->body);
		submit_len = माप(*cmd);
	पूर्ण

	cmd = VMW_CMD_RESERVE(dev_priv, submit_len);
	cmd2 = (typeof(cmd2))cmd;
	cmd3 = (typeof(cmd3))cmd;
	cmd4 = (typeof(cmd4))cmd;
	अगर (unlikely(!cmd)) अणु
		ret = -ENOMEM;
		जाओ out_no_fअगरo;
	पूर्ण

	अगर (has_sm5_context(dev_priv) && metadata->array_size > 0) अणु
		cmd4->header.id = cmd_id;
		cmd4->header.size = cmd_len;
		cmd4->body.sid = srf->res.id;
		cmd4->body.surfaceFlags = metadata->flags;
		cmd4->body.क्रमmat = metadata->क्रमmat;
		cmd4->body.numMipLevels = metadata->mip_levels[0];
		cmd4->body.multisampleCount = metadata->multisample_count;
		cmd4->body.multisamplePattern = metadata->multisample_pattern;
		cmd4->body.qualityLevel = metadata->quality_level;
		cmd4->body.स्वतःgenFilter = metadata->स्वतःgen_filter;
		cmd4->body.size.width = metadata->base_size.width;
		cmd4->body.size.height = metadata->base_size.height;
		cmd4->body.size.depth = metadata->base_size.depth;
		cmd4->body.arraySize = metadata->array_size;
		cmd4->body.bufferByteStride = metadata->buffer_byte_stride;
	पूर्ण अन्यथा अगर (has_sm4_1_context(dev_priv) && metadata->array_size > 0) अणु
		cmd3->header.id = cmd_id;
		cmd3->header.size = cmd_len;
		cmd3->body.sid = srf->res.id;
		cmd3->body.surfaceFlags = metadata->flags;
		cmd3->body.क्रमmat = metadata->क्रमmat;
		cmd3->body.numMipLevels = metadata->mip_levels[0];
		cmd3->body.multisampleCount = metadata->multisample_count;
		cmd3->body.multisamplePattern = metadata->multisample_pattern;
		cmd3->body.qualityLevel = metadata->quality_level;
		cmd3->body.स्वतःgenFilter = metadata->स्वतःgen_filter;
		cmd3->body.size.width = metadata->base_size.width;
		cmd3->body.size.height = metadata->base_size.height;
		cmd3->body.size.depth = metadata->base_size.depth;
		cmd3->body.arraySize = metadata->array_size;
	पूर्ण अन्यथा अगर (metadata->array_size > 0) अणु
		cmd2->header.id = cmd_id;
		cmd2->header.size = cmd_len;
		cmd2->body.sid = srf->res.id;
		cmd2->body.surfaceFlags = metadata->flags;
		cmd2->body.क्रमmat = metadata->क्रमmat;
		cmd2->body.numMipLevels = metadata->mip_levels[0];
		cmd2->body.multisampleCount = metadata->multisample_count;
		cmd2->body.स्वतःgenFilter = metadata->स्वतःgen_filter;
		cmd2->body.size.width = metadata->base_size.width;
		cmd2->body.size.height = metadata->base_size.height;
		cmd2->body.size.depth = metadata->base_size.depth;
		cmd2->body.arraySize = metadata->array_size;
	पूर्ण अन्यथा अणु
		cmd->header.id = cmd_id;
		cmd->header.size = cmd_len;
		cmd->body.sid = srf->res.id;
		cmd->body.surfaceFlags = metadata->flags;
		cmd->body.क्रमmat = metadata->क्रमmat;
		cmd->body.numMipLevels = metadata->mip_levels[0];
		cmd->body.multisampleCount = metadata->multisample_count;
		cmd->body.स्वतःgenFilter = metadata->स्वतःgen_filter;
		cmd->body.size.width = metadata->base_size.width;
		cmd->body.size.height = metadata->base_size.height;
		cmd->body.size.depth = metadata->base_size.depth;
	पूर्ण

	vmw_cmd_commit(dev_priv, submit_len);

	वापस 0;

out_no_fअगरo:
	vmw_resource_release_id(res);
out_no_id:
	vmw_fअगरo_resource_dec(dev_priv);
	वापस ret;
पूर्ण


अटल पूर्णांक vmw_gb_surface_bind(काष्ठा vmw_resource *res,
			       काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdBindGBSurface body;
	पूर्ण *cmd1;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdUpdateGBSurface body;
	पूर्ण *cmd2;
	uपूर्णांक32_t submit_size;
	काष्ठा tपंचांग_buffer_object *bo = val_buf->bo;

	BUG_ON(bo->mem.mem_type != VMW_PL_MOB);

	submit_size = माप(*cmd1) + (res->backup_dirty ? माप(*cmd2) : 0);

	cmd1 = VMW_CMD_RESERVE(dev_priv, submit_size);
	अगर (unlikely(!cmd1))
		वापस -ENOMEM;

	cmd1->header.id = SVGA_3D_CMD_BIND_GB_SURFACE;
	cmd1->header.size = माप(cmd1->body);
	cmd1->body.sid = res->id;
	cmd1->body.mobid = bo->mem.start;
	अगर (res->backup_dirty) अणु
		cmd2 = (व्योम *) &cmd1[1];
		cmd2->header.id = SVGA_3D_CMD_UPDATE_GB_SURFACE;
		cmd2->header.size = माप(cmd2->body);
		cmd2->body.sid = res->id;
	पूर्ण
	vmw_cmd_commit(dev_priv, submit_size);

	अगर (res->backup->dirty && res->backup_dirty) अणु
		/* We've just made a full upload. Cear dirty regions. */
		vmw_bo_dirty_clear_res(res);
	पूर्ण

	res->backup_dirty = false;

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_gb_surface_unbind(काष्ठा vmw_resource *res,
				 bool पढ़ोback,
				 काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा tपंचांग_buffer_object *bo = val_buf->bo;
	काष्ठा vmw_fence_obj *fence;

	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdReadbackGBSurface body;
	पूर्ण *cmd1;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdInvalidateGBSurface body;
	पूर्ण *cmd2;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdBindGBSurface body;
	पूर्ण *cmd3;
	uपूर्णांक32_t submit_size;
	uपूर्णांक8_t *cmd;


	BUG_ON(bo->mem.mem_type != VMW_PL_MOB);

	submit_size = माप(*cmd3) + (पढ़ोback ? माप(*cmd1) : माप(*cmd2));
	cmd = VMW_CMD_RESERVE(dev_priv, submit_size);
	अगर (unlikely(!cmd))
		वापस -ENOMEM;

	अगर (पढ़ोback) अणु
		cmd1 = (व्योम *) cmd;
		cmd1->header.id = SVGA_3D_CMD_READBACK_GB_SURFACE;
		cmd1->header.size = माप(cmd1->body);
		cmd1->body.sid = res->id;
		cmd3 = (व्योम *) &cmd1[1];
	पूर्ण अन्यथा अणु
		cmd2 = (व्योम *) cmd;
		cmd2->header.id = SVGA_3D_CMD_INVALIDATE_GB_SURFACE;
		cmd2->header.size = माप(cmd2->body);
		cmd2->body.sid = res->id;
		cmd3 = (व्योम *) &cmd2[1];
	पूर्ण

	cmd3->header.id = SVGA_3D_CMD_BIND_GB_SURFACE;
	cmd3->header.size = माप(cmd3->body);
	cmd3->body.sid = res->id;
	cmd3->body.mobid = SVGA3D_INVALID_ID;

	vmw_cmd_commit(dev_priv, submit_size);

	/*
	 * Create a fence object and fence the backup buffer.
	 */

	(व्योम) vmw_execbuf_fence_commands(शून्य, dev_priv,
					  &fence, शून्य);

	vmw_bo_fence_single(val_buf->bo, fence);

	अगर (likely(fence != शून्य))
		vmw_fence_obj_unreference(&fence);

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_gb_surface_destroy(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_surface *srf = vmw_res_to_srf(res);
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDestroyGBSurface body;
	पूर्ण *cmd;

	अगर (likely(res->id == -1))
		वापस 0;

	mutex_lock(&dev_priv->binding_mutex);
	vmw_view_surface_list_destroy(dev_priv, &srf->view_list);
	vmw_binding_res_list_scrub(&res->binding_head);

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(!cmd)) अणु
		mutex_unlock(&dev_priv->binding_mutex);
		वापस -ENOMEM;
	पूर्ण

	cmd->header.id = SVGA_3D_CMD_DESTROY_GB_SURFACE;
	cmd->header.size = माप(cmd->body);
	cmd->body.sid = res->id;
	vmw_cmd_commit(dev_priv, माप(*cmd));
	mutex_unlock(&dev_priv->binding_mutex);
	vmw_resource_release_id(res);
	vmw_fअगरo_resource_dec(dev_priv);

	वापस 0;
पूर्ण

/**
 * vmw_gb_surface_define_ioctl - Ioctl function implementing
 * the user surface define functionality.
 *
 * @dev: Poपूर्णांकer to a काष्ठा drm_device.
 * @data: Poपूर्णांकer to data copied from / to user-space.
 * @file_priv: Poपूर्णांकer to a drm file निजी काष्ठाure.
 */
पूर्णांक vmw_gb_surface_define_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv)
अणु
	जोड़ drm_vmw_gb_surface_create_arg *arg =
	    (जोड़ drm_vmw_gb_surface_create_arg *)data;
	काष्ठा drm_vmw_gb_surface_create_rep *rep = &arg->rep;
	काष्ठा drm_vmw_gb_surface_create_ext_req req_ext;

	req_ext.base = arg->req;
	req_ext.version = drm_vmw_gb_surface_v1;
	req_ext.svga3d_flags_upper_32_bits = 0;
	req_ext.multisample_pattern = SVGA3D_MS_PATTERN_NONE;
	req_ext.quality_level = SVGA3D_MS_QUALITY_NONE;
	req_ext.buffer_byte_stride = 0;
	req_ext.must_be_zero = 0;

	वापस vmw_gb_surface_define_पूर्णांकernal(dev, &req_ext, rep, file_priv);
पूर्ण

/**
 * vmw_gb_surface_reference_ioctl - Ioctl function implementing
 * the user surface reference functionality.
 *
 * @dev: Poपूर्णांकer to a काष्ठा drm_device.
 * @data: Poपूर्णांकer to data copied from / to user-space.
 * @file_priv: Poपूर्णांकer to a drm file निजी काष्ठाure.
 */
पूर्णांक vmw_gb_surface_reference_ioctl(काष्ठा drm_device *dev, व्योम *data,
				   काष्ठा drm_file *file_priv)
अणु
	जोड़ drm_vmw_gb_surface_reference_arg *arg =
	    (जोड़ drm_vmw_gb_surface_reference_arg *)data;
	काष्ठा drm_vmw_surface_arg *req = &arg->req;
	काष्ठा drm_vmw_gb_surface_ref_rep *rep = &arg->rep;
	काष्ठा drm_vmw_gb_surface_ref_ext_rep rep_ext;
	पूर्णांक ret;

	ret = vmw_gb_surface_reference_पूर्णांकernal(dev, req, &rep_ext, file_priv);

	अगर (unlikely(ret != 0))
		वापस ret;

	rep->creq = rep_ext.creq.base;
	rep->crep = rep_ext.crep;

	वापस ret;
पूर्ण

/**
 * vmw_gb_surface_define_ext_ioctl - Ioctl function implementing
 * the user surface define functionality.
 *
 * @dev: Poपूर्णांकer to a काष्ठा drm_device.
 * @data: Poपूर्णांकer to data copied from / to user-space.
 * @file_priv: Poपूर्णांकer to a drm file निजी काष्ठाure.
 */
पूर्णांक vmw_gb_surface_define_ext_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv)
अणु
	जोड़ drm_vmw_gb_surface_create_ext_arg *arg =
	    (जोड़ drm_vmw_gb_surface_create_ext_arg *)data;
	काष्ठा drm_vmw_gb_surface_create_ext_req *req = &arg->req;
	काष्ठा drm_vmw_gb_surface_create_rep *rep = &arg->rep;

	वापस vmw_gb_surface_define_पूर्णांकernal(dev, req, rep, file_priv);
पूर्ण

/**
 * vmw_gb_surface_reference_ext_ioctl - Ioctl function implementing
 * the user surface reference functionality.
 *
 * @dev: Poपूर्णांकer to a काष्ठा drm_device.
 * @data: Poपूर्णांकer to data copied from / to user-space.
 * @file_priv: Poपूर्णांकer to a drm file निजी काष्ठाure.
 */
पूर्णांक vmw_gb_surface_reference_ext_ioctl(काष्ठा drm_device *dev, व्योम *data,
				   काष्ठा drm_file *file_priv)
अणु
	जोड़ drm_vmw_gb_surface_reference_ext_arg *arg =
	    (जोड़ drm_vmw_gb_surface_reference_ext_arg *)data;
	काष्ठा drm_vmw_surface_arg *req = &arg->req;
	काष्ठा drm_vmw_gb_surface_ref_ext_rep *rep = &arg->rep;

	वापस vmw_gb_surface_reference_पूर्णांकernal(dev, req, rep, file_priv);
पूर्ण

/**
 * vmw_gb_surface_define_पूर्णांकernal - Ioctl function implementing
 * the user surface define functionality.
 *
 * @dev: Poपूर्णांकer to a काष्ठा drm_device.
 * @req: Request argument from user-space.
 * @rep: Response argument to user-space.
 * @file_priv: Poपूर्णांकer to a drm file निजी काष्ठाure.
 */
अटल पूर्णांक
vmw_gb_surface_define_पूर्णांकernal(काष्ठा drm_device *dev,
			       काष्ठा drm_vmw_gb_surface_create_ext_req *req,
			       काष्ठा drm_vmw_gb_surface_create_rep *rep,
			       काष्ठा drm_file *file_priv)
अणु
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा vmw_user_surface *user_srf;
	काष्ठा vmw_surface_metadata metadata = अणु0पूर्ण;
	काष्ठा vmw_surface *srf;
	काष्ठा vmw_resource *res;
	काष्ठा vmw_resource *पंचांगp;
	पूर्णांक ret = 0;
	uपूर्णांक32_t size;
	uपूर्णांक32_t backup_handle = 0;
	SVGA3dSurfaceAllFlags svga3d_flags_64 =
		SVGA3D_FLAGS_64(req->svga3d_flags_upper_32_bits,
				req->base.svga3d_flags);

	/* array_size must be null क्रम non-GL3 host. */
	अगर (req->base.array_size > 0 && !has_sm4_context(dev_priv)) अणु
		VMW_DEBUG_USER("SM4 surface not supported.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!has_sm4_1_context(dev_priv)) अणु
		अगर (req->svga3d_flags_upper_32_bits != 0)
			ret = -EINVAL;

		अगर (req->base.multisample_count != 0)
			ret = -EINVAL;

		अगर (req->multisample_pattern != SVGA3D_MS_PATTERN_NONE)
			ret = -EINVAL;

		अगर (req->quality_level != SVGA3D_MS_QUALITY_NONE)
			ret = -EINVAL;

		अगर (ret) अणु
			VMW_DEBUG_USER("SM4.1 surface not supported.\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (req->buffer_byte_stride > 0 && !has_sm5_context(dev_priv)) अणु
		VMW_DEBUG_USER("SM5 surface not supported.\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((svga3d_flags_64 & SVGA3D_SURFACE_MULTISAMPLE) &&
	    req->base.multisample_count == 0) अणु
		VMW_DEBUG_USER("Invalid sample count.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (req->base.mip_levels > DRM_VMW_MAX_MIP_LEVELS) अणु
		VMW_DEBUG_USER("Invalid mip level.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(vmw_user_surface_size == 0))
		vmw_user_surface_size = tपंचांग_round_pot(माप(*user_srf)) +
			VMW_IDA_ACC_SIZE + TTM_OBJ_EXTRA_SIZE;

	size = vmw_user_surface_size;

	metadata.flags = svga3d_flags_64;
	metadata.क्रमmat = req->base.क्रमmat;
	metadata.mip_levels[0] = req->base.mip_levels;
	metadata.multisample_count = req->base.multisample_count;
	metadata.multisample_pattern = req->multisample_pattern;
	metadata.quality_level = req->quality_level;
	metadata.array_size = req->base.array_size;
	metadata.buffer_byte_stride = req->buffer_byte_stride;
	metadata.num_sizes = 1;
	metadata.base_size = req->base.base_size;
	metadata.scanout = req->base.drm_surface_flags &
		drm_vmw_surface_flag_scanout;

	/* Define a surface based on the parameters. */
	ret = vmw_gb_surface_define(dev_priv, size, &metadata, &srf);
	अगर (ret != 0) अणु
		VMW_DEBUG_USER("Failed to define surface.\n");
		वापस ret;
	पूर्ण

	user_srf = container_of(srf, काष्ठा vmw_user_surface, srf);
	अगर (drm_is_primary_client(file_priv))
		user_srf->master = drm_master_get(file_priv->master);

	ret = tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, true);
	अगर (unlikely(ret != 0))
		वापस ret;

	res = &user_srf->srf.res;

	अगर (req->base.buffer_handle != SVGA3D_INVALID_ID) अणु
		ret = vmw_user_bo_lookup(tfile, req->base.buffer_handle,
					 &res->backup,
					 &user_srf->backup_base);
		अगर (ret == 0) अणु
			अगर (res->backup->base.base.size < res->backup_size) अणु
				VMW_DEBUG_USER("Surface backup buffer too small.\n");
				vmw_bo_unreference(&res->backup);
				ret = -EINVAL;
				जाओ out_unlock;
			पूर्ण अन्यथा अणु
				backup_handle = req->base.buffer_handle;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (req->base.drm_surface_flags &
		   (drm_vmw_surface_flag_create_buffer |
		    drm_vmw_surface_flag_coherent))
		ret = vmw_user_bo_alloc(dev_priv, tfile,
					res->backup_size,
					req->base.drm_surface_flags &
					drm_vmw_surface_flag_shareable,
					&backup_handle,
					&res->backup,
					&user_srf->backup_base);

	अगर (unlikely(ret != 0)) अणु
		vmw_resource_unreference(&res);
		जाओ out_unlock;
	पूर्ण

	अगर (req->base.drm_surface_flags & drm_vmw_surface_flag_coherent) अणु
		काष्ठा vmw_buffer_object *backup = res->backup;

		tपंचांग_bo_reserve(&backup->base, false, false, शून्य);
		अगर (!res->func->dirty_alloc)
			ret = -EINVAL;
		अगर (!ret)
			ret = vmw_bo_dirty_add(backup);
		अगर (!ret) अणु
			res->coherent = true;
			ret = res->func->dirty_alloc(res);
		पूर्ण
		tपंचांग_bo_unreserve(&backup->base);
		अगर (ret) अणु
			vmw_resource_unreference(&res);
			जाओ out_unlock;
		पूर्ण

	पूर्ण

	पंचांगp = vmw_resource_reference(res);
	ret = tपंचांग_prime_object_init(tfile, res->backup_size, &user_srf->prime,
				    req->base.drm_surface_flags &
				    drm_vmw_surface_flag_shareable,
				    VMW_RES_SURFACE,
				    &vmw_user_surface_base_release, शून्य);

	अगर (unlikely(ret != 0)) अणु
		vmw_resource_unreference(&पंचांगp);
		vmw_resource_unreference(&res);
		जाओ out_unlock;
	पूर्ण

	rep->handle      = user_srf->prime.base.handle;
	rep->backup_size = res->backup_size;
	अगर (res->backup) अणु
		rep->buffer_map_handle =
			drm_vma_node_offset_addr(&res->backup->base.base.vma_node);
		rep->buffer_size = res->backup->base.base.size;
		rep->buffer_handle = backup_handle;
	पूर्ण अन्यथा अणु
		rep->buffer_map_handle = 0;
		rep->buffer_size = 0;
		rep->buffer_handle = SVGA3D_INVALID_ID;
	पूर्ण

	vmw_resource_unreference(&res);

out_unlock:
	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
	वापस ret;
पूर्ण

/**
 * vmw_gb_surface_reference_पूर्णांकernal - Ioctl function implementing
 * the user surface reference functionality.
 *
 * @dev: Poपूर्णांकer to a काष्ठा drm_device.
 * @req: Poपूर्णांकer to user-space request surface arg.
 * @rep: Poपूर्णांकer to response to user-space.
 * @file_priv: Poपूर्णांकer to a drm file निजी काष्ठाure.
 */
अटल पूर्णांक
vmw_gb_surface_reference_पूर्णांकernal(काष्ठा drm_device *dev,
				  काष्ठा drm_vmw_surface_arg *req,
				  काष्ठा drm_vmw_gb_surface_ref_ext_rep *rep,
				  काष्ठा drm_file *file_priv)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा vmw_surface *srf;
	काष्ठा vmw_user_surface *user_srf;
	काष्ठा vmw_surface_metadata *metadata;
	काष्ठा tपंचांग_base_object *base;
	uपूर्णांक32_t backup_handle;
	पूर्णांक ret;

	ret = vmw_surface_handle_reference(dev_priv, file_priv, req->sid,
					   req->handle_type, &base);
	अगर (unlikely(ret != 0))
		वापस ret;

	user_srf = container_of(base, काष्ठा vmw_user_surface, prime.base);
	srf = &user_srf->srf;
	अगर (!srf->res.backup) अणु
		DRM_ERROR("Shared GB surface is missing a backup buffer.\n");
		जाओ out_bad_resource;
	पूर्ण
	metadata = &srf->metadata;

	mutex_lock(&dev_priv->cmdbuf_mutex); /* Protect res->backup */
	ret = vmw_user_bo_reference(tfile, srf->res.backup, &backup_handle);
	mutex_unlock(&dev_priv->cmdbuf_mutex);

	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Could not add a reference to a GB surface "
			  "backup buffer.\n");
		(व्योम) tपंचांग_ref_object_base_unref(tfile, base->handle,
						 TTM_REF_USAGE);
		जाओ out_bad_resource;
	पूर्ण

	rep->creq.base.svga3d_flags = SVGA3D_FLAGS_LOWER_32(metadata->flags);
	rep->creq.base.क्रमmat = metadata->क्रमmat;
	rep->creq.base.mip_levels = metadata->mip_levels[0];
	rep->creq.base.drm_surface_flags = 0;
	rep->creq.base.multisample_count = metadata->multisample_count;
	rep->creq.base.स्वतःgen_filter = metadata->स्वतःgen_filter;
	rep->creq.base.array_size = metadata->array_size;
	rep->creq.base.buffer_handle = backup_handle;
	rep->creq.base.base_size = metadata->base_size;
	rep->crep.handle = user_srf->prime.base.handle;
	rep->crep.backup_size = srf->res.backup_size;
	rep->crep.buffer_handle = backup_handle;
	rep->crep.buffer_map_handle =
		drm_vma_node_offset_addr(&srf->res.backup->base.base.vma_node);
	rep->crep.buffer_size = srf->res.backup->base.base.size;

	rep->creq.version = drm_vmw_gb_surface_v1;
	rep->creq.svga3d_flags_upper_32_bits =
		SVGA3D_FLAGS_UPPER_32(metadata->flags);
	rep->creq.multisample_pattern = metadata->multisample_pattern;
	rep->creq.quality_level = metadata->quality_level;
	rep->creq.must_be_zero = 0;

out_bad_resource:
	tपंचांग_base_object_unref(&base);

	वापस ret;
पूर्ण

/**
 * vmw_subres_dirty_add - Add a dirty region to a subresource
 * @dirty: The surfaces's dirty tracker.
 * @loc_start: The location corresponding to the start of the region.
 * @loc_end: The location corresponding to the end of the region.
 *
 * As we are assuming that @loc_start and @loc_end represent a sequential
 * range of backing store memory, अगर the region spans multiple lines then
 * regardless of the x coordinate, the full lines are dirtied.
 * Correspondingly अगर the region spans multiple z slices, then full rather
 * than partial z slices are dirtied.
 */
अटल व्योम vmw_subres_dirty_add(काष्ठा vmw_surface_dirty *dirty,
				 स्थिर काष्ठा svga3dsurface_loc *loc_start,
				 स्थिर काष्ठा svga3dsurface_loc *loc_end)
अणु
	स्थिर काष्ठा svga3dsurface_cache *cache = &dirty->cache;
	SVGA3dBox *box = &dirty->boxes[loc_start->sub_resource];
	u32 mip = loc_start->sub_resource % cache->num_mip_levels;
	स्थिर काष्ठा drm_vmw_size *size = &cache->mip[mip].size;
	u32 box_c2 = box->z + box->d;

	अगर (WARN_ON(loc_start->sub_resource >= dirty->num_subres))
		वापस;

	अगर (box->d == 0 || box->z > loc_start->z)
		box->z = loc_start->z;
	अगर (box_c2 < loc_end->z)
		box->d = loc_end->z - box->z;

	अगर (loc_start->z + 1 == loc_end->z) अणु
		box_c2 = box->y + box->h;
		अगर (box->h == 0 || box->y > loc_start->y)
			box->y = loc_start->y;
		अगर (box_c2 < loc_end->y)
			box->h = loc_end->y - box->y;

		अगर (loc_start->y + 1 == loc_end->y) अणु
			box_c2 = box->x + box->w;
			अगर (box->w == 0 || box->x > loc_start->x)
				box->x = loc_start->x;
			अगर (box_c2 < loc_end->x)
				box->w = loc_end->x - box->x;
		पूर्ण अन्यथा अणु
			box->x = 0;
			box->w = size->width;
		पूर्ण
	पूर्ण अन्यथा अणु
		box->y = 0;
		box->h = size->height;
		box->x = 0;
		box->w = size->width;
	पूर्ण
पूर्ण

/**
 * vmw_subres_dirty_full - Mark a full subresource as dirty
 * @dirty: The surface's dirty tracker.
 * @subres: The subresource
 */
अटल व्योम vmw_subres_dirty_full(काष्ठा vmw_surface_dirty *dirty, u32 subres)
अणु
	स्थिर काष्ठा svga3dsurface_cache *cache = &dirty->cache;
	u32 mip = subres % cache->num_mip_levels;
	स्थिर काष्ठा drm_vmw_size *size = &cache->mip[mip].size;
	SVGA3dBox *box = &dirty->boxes[subres];

	box->x = 0;
	box->y = 0;
	box->z = 0;
	box->w = size->width;
	box->h = size->height;
	box->d = size->depth;
पूर्ण

/*
 * vmw_surface_tex_dirty_add_range - The dirty_add_range callback क्रम texture
 * surfaces.
 */
अटल व्योम vmw_surface_tex_dirty_range_add(काष्ठा vmw_resource *res,
					    माप_प्रकार start, माप_प्रकार end)
अणु
	काष्ठा vmw_surface_dirty *dirty =
		(काष्ठा vmw_surface_dirty *) res->dirty;
	माप_प्रकार backup_end = res->backup_offset + res->backup_size;
	काष्ठा svga3dsurface_loc loc1, loc2;
	स्थिर काष्ठा svga3dsurface_cache *cache;

	start = max_t(माप_प्रकार, start, res->backup_offset) - res->backup_offset;
	end = min(end, backup_end) - res->backup_offset;
	cache = &dirty->cache;
	svga3dsurface_get_loc(cache, &loc1, start);
	svga3dsurface_get_loc(cache, &loc2, end - 1);
	svga3dsurface_inc_loc(cache, &loc2);

	अगर (loc1.sub_resource + 1 == loc2.sub_resource) अणु
		/* Dirty range covers a single sub-resource */
		vmw_subres_dirty_add(dirty, &loc1, &loc2);
	पूर्ण अन्यथा अणु
		/* Dirty range covers multiple sub-resources */
		काष्ठा svga3dsurface_loc loc_min, loc_max;
		u32 sub_res;

		svga3dsurface_max_loc(cache, loc1.sub_resource, &loc_max);
		vmw_subres_dirty_add(dirty, &loc1, &loc_max);
		svga3dsurface_min_loc(cache, loc2.sub_resource - 1, &loc_min);
		vmw_subres_dirty_add(dirty, &loc_min, &loc2);
		क्रम (sub_res = loc1.sub_resource + 1;
		     sub_res < loc2.sub_resource - 1; ++sub_res)
			vmw_subres_dirty_full(dirty, sub_res);
	पूर्ण
पूर्ण

/*
 * vmw_surface_tex_dirty_add_range - The dirty_add_range callback क्रम buffer
 * surfaces.
 */
अटल व्योम vmw_surface_buf_dirty_range_add(काष्ठा vmw_resource *res,
					    माप_प्रकार start, माप_प्रकार end)
अणु
	काष्ठा vmw_surface_dirty *dirty =
		(काष्ठा vmw_surface_dirty *) res->dirty;
	स्थिर काष्ठा svga3dsurface_cache *cache = &dirty->cache;
	माप_प्रकार backup_end = res->backup_offset + cache->mip_chain_bytes;
	SVGA3dBox *box = &dirty->boxes[0];
	u32 box_c2;

	box->h = box->d = 1;
	start = max_t(माप_प्रकार, start, res->backup_offset) - res->backup_offset;
	end = min(end, backup_end) - res->backup_offset;
	box_c2 = box->x + box->w;
	अगर (box->w == 0 || box->x > start)
		box->x = start;
	अगर (box_c2 < end)
		box->w = end - box->x;
पूर्ण

/*
 * vmw_surface_tex_dirty_add_range - The dirty_add_range callback क्रम surfaces
 */
अटल व्योम vmw_surface_dirty_range_add(काष्ठा vmw_resource *res, माप_प्रकार start,
					माप_प्रकार end)
अणु
	काष्ठा vmw_surface *srf = vmw_res_to_srf(res);

	अगर (WARN_ON(end <= res->backup_offset ||
		    start >= res->backup_offset + res->backup_size))
		वापस;

	अगर (srf->metadata.क्रमmat == SVGA3D_BUFFER)
		vmw_surface_buf_dirty_range_add(res, start, end);
	अन्यथा
		vmw_surface_tex_dirty_range_add(res, start, end);
पूर्ण

/*
 * vmw_surface_dirty_sync - The surface's dirty_sync callback.
 */
अटल पूर्णांक vmw_surface_dirty_sync(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	bool has_dx = 0;
	u32 i, num_dirty;
	काष्ठा vmw_surface_dirty *dirty =
		(काष्ठा vmw_surface_dirty *) res->dirty;
	माप_प्रकार alloc_size;
	स्थिर काष्ठा svga3dsurface_cache *cache = &dirty->cache;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXUpdateSubResource body;
	पूर्ण *cmd1;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdUpdateGBImage body;
	पूर्ण *cmd2;
	व्योम *cmd;

	num_dirty = 0;
	क्रम (i = 0; i < dirty->num_subres; ++i) अणु
		स्थिर SVGA3dBox *box = &dirty->boxes[i];

		अगर (box->d)
			num_dirty++;
	पूर्ण

	अगर (!num_dirty)
		जाओ out;

	alloc_size = num_dirty * ((has_dx) ? माप(*cmd1) : माप(*cmd2));
	cmd = VMW_CMD_RESERVE(dev_priv, alloc_size);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd1 = cmd;
	cmd2 = cmd;

	क्रम (i = 0; i < dirty->num_subres; ++i) अणु
		स्थिर SVGA3dBox *box = &dirty->boxes[i];

		अगर (!box->d)
			जारी;

		/*
		 * DX_UPDATE_SUBRESOURCE is aware of array surfaces.
		 * UPDATE_GB_IMAGE is not.
		 */
		अगर (has_dx) अणु
			cmd1->header.id = SVGA_3D_CMD_DX_UPDATE_SUBRESOURCE;
			cmd1->header.size = माप(cmd1->body);
			cmd1->body.sid = res->id;
			cmd1->body.subResource = i;
			cmd1->body.box = *box;
			cmd1++;
		पूर्ण अन्यथा अणु
			cmd2->header.id = SVGA_3D_CMD_UPDATE_GB_IMAGE;
			cmd2->header.size = माप(cmd2->body);
			cmd2->body.image.sid = res->id;
			cmd2->body.image.face = i / cache->num_mip_levels;
			cmd2->body.image.mipmap = i -
				(cache->num_mip_levels * cmd2->body.image.face);
			cmd2->body.box = *box;
			cmd2++;
		पूर्ण

	पूर्ण
	vmw_cmd_commit(dev_priv, alloc_size);
 out:
	स_रखो(&dirty->boxes[0], 0, माप(dirty->boxes[0]) *
	       dirty->num_subres);

	वापस 0;
पूर्ण

/*
 * vmw_surface_dirty_alloc - The surface's dirty_alloc callback.
 */
अटल पूर्णांक vmw_surface_dirty_alloc(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_surface *srf = vmw_res_to_srf(res);
	स्थिर काष्ठा vmw_surface_metadata *metadata = &srf->metadata;
	काष्ठा vmw_surface_dirty *dirty;
	u32 num_layers = 1;
	u32 num_mip;
	u32 num_subres;
	u32 num_samples;
	माप_प्रकार dirty_size, acc_size;
	अटल काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = false,
		.no_रुको_gpu = false
	पूर्ण;
	पूर्णांक ret;

	अगर (metadata->array_size)
		num_layers = metadata->array_size;
	अन्यथा अगर (metadata->flags & SVGA3D_SURFACE_CUBEMAP)
		num_layers *= SVGA3D_MAX_SURFACE_FACES;

	num_mip = metadata->mip_levels[0];
	अगर (!num_mip)
		num_mip = 1;

	num_subres = num_layers * num_mip;
	dirty_size = काष्ठा_size(dirty, boxes, num_subres);
	acc_size = tपंचांग_round_pot(dirty_size);
	ret = tपंचांग_mem_global_alloc(vmw_mem_glob(res->dev_priv),
				   acc_size, &ctx);
	अगर (ret) अणु
		VMW_DEBUG_USER("Out of graphics memory for surface "
			       "dirty tracker.\n");
		वापस ret;
	पूर्ण

	dirty = kvzalloc(dirty_size, GFP_KERNEL);
	अगर (!dirty) अणु
		ret = -ENOMEM;
		जाओ out_no_dirty;
	पूर्ण

	num_samples = max_t(u32, 1, metadata->multisample_count);
	ret = svga3dsurface_setup_cache(&metadata->base_size, metadata->क्रमmat,
					num_mip, num_layers, num_samples,
					&dirty->cache);
	अगर (ret)
		जाओ out_no_cache;

	dirty->num_subres = num_subres;
	dirty->size = acc_size;
	res->dirty = (काष्ठा vmw_resource_dirty *) dirty;

	वापस 0;

out_no_cache:
	kvमुक्त(dirty);
out_no_dirty:
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(res->dev_priv), acc_size);
	वापस ret;
पूर्ण

/*
 * vmw_surface_dirty_मुक्त - The surface's dirty_मुक्त callback
 */
अटल व्योम vmw_surface_dirty_मुक्त(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_surface_dirty *dirty =
		(काष्ठा vmw_surface_dirty *) res->dirty;
	माप_प्रकार acc_size = dirty->size;

	kvमुक्त(dirty);
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(res->dev_priv), acc_size);
	res->dirty = शून्य;
पूर्ण

/*
 * vmw_surface_clean - The surface's clean callback
 */
अटल पूर्णांक vmw_surface_clean(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	माप_प्रकार alloc_size;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdReadbackGBSurface body;
	पूर्ण *cmd;

	alloc_size = माप(*cmd);
	cmd = VMW_CMD_RESERVE(dev_priv, alloc_size);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_READBACK_GB_SURFACE;
	cmd->header.size = माप(cmd->body);
	cmd->body.sid = res->id;
	vmw_cmd_commit(dev_priv, alloc_size);

	वापस 0;
पूर्ण

/*
 * vmw_gb_surface_define - Define a निजी GB surface
 *
 * @dev_priv: Poपूर्णांकer to a device निजी.
 * @user_accounting_size:  Used to track user-space memory usage, set
 *                         to 0 क्रम kernel mode only memory
 * @metadata: Metadata representing the surface to create.
 * @user_srf_out: allocated user_srf. Set to शून्य on failure.
 *
 * GB surfaces allocated by this function will not have a user mode handle, and
 * thus will only be visible to vmwgfx.  For optimization reasons the
 * surface may later be given a user mode handle by another function to make
 * it available to user mode drivers.
 */
पूर्णांक vmw_gb_surface_define(काष्ठा vmw_निजी *dev_priv,
			  uपूर्णांक32_t user_accounting_size,
			  स्थिर काष्ठा vmw_surface_metadata *req,
			  काष्ठा vmw_surface **srf_out)
अणु
	काष्ठा vmw_surface_metadata *metadata;
	काष्ठा vmw_user_surface *user_srf;
	काष्ठा vmw_surface *srf;
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = true,
		.no_रुको_gpu = false
	पूर्ण;
	u32 sample_count = 1;
	u32 num_layers = 1;
	पूर्णांक ret;

	*srf_out = शून्य;

	अगर (req->scanout) अणु
		अगर (!svga3dsurface_is_screen_target_क्रमmat(req->क्रमmat)) अणु
			VMW_DEBUG_USER("Invalid Screen Target surface format.");
			वापस -EINVAL;
		पूर्ण

		अगर (req->base_size.width > dev_priv->texture_max_width ||
		    req->base_size.height > dev_priv->texture_max_height) अणु
			VMW_DEBUG_USER("%ux%u\n, exceed max surface size %ux%u",
				       req->base_size.width,
				       req->base_size.height,
				       dev_priv->texture_max_width,
				       dev_priv->texture_max_height);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा svga3d_surface_desc *desc =
			svga3dsurface_get_desc(req->क्रमmat);

		अगर (desc->block_desc == SVGA3DBLOCKDESC_NONE) अणु
			VMW_DEBUG_USER("Invalid surface format.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (req->स्वतःgen_filter != SVGA3D_TEX_FILTER_NONE)
		वापस -EINVAL;

	अगर (req->num_sizes != 1)
		वापस -EINVAL;

	अगर (req->sizes != शून्य)
		वापस -EINVAL;

	ret = tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, true);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = tपंचांग_mem_global_alloc(vmw_mem_glob(dev_priv),
				   user_accounting_size, &ctx);
	अगर (ret != 0) अणु
		अगर (ret != -ERESTARTSYS)
			DRM_ERROR("Out of graphics memory for surface.\n");
		जाओ out_unlock;
	पूर्ण

	user_srf = kzalloc(माप(*user_srf), GFP_KERNEL);
	अगर (unlikely(!user_srf)) अणु
		ret = -ENOMEM;
		जाओ out_no_user_srf;
	पूर्ण

	*srf_out  = &user_srf->srf;
	user_srf->size = user_accounting_size;
	user_srf->prime.base.shareable = false;
	user_srf->prime.base.tfile = शून्य;

	srf = &user_srf->srf;
	srf->metadata = *req;
	srf->offsets = शून्य;

	metadata = &srf->metadata;

	अगर (metadata->array_size)
		num_layers = req->array_size;
	अन्यथा अगर (metadata->flags & SVGA3D_SURFACE_CUBEMAP)
		num_layers = SVGA3D_MAX_SURFACE_FACES;

	अगर (metadata->flags & SVGA3D_SURFACE_MULTISAMPLE)
		sample_count = metadata->multisample_count;

	srf->res.backup_size =
		svga3dsurface_get_serialized_size_extended(metadata->क्रमmat,
							   metadata->base_size,
							   metadata->mip_levels[0],
							   num_layers,
							   sample_count);

	अगर (metadata->flags & SVGA3D_SURFACE_BIND_STREAM_OUTPUT)
		srf->res.backup_size += माप(SVGA3dDXSOState);

	/*
	 * Don't set SVGA3D_SURFACE_SCREENTARGET flag क्रम a scanout surface with
	 * size greater than STDU max width/height. This is really a workaround
	 * to support creation of big framebuffer requested by some user-space
	 * क्रम whole topology. That big framebuffer won't really be used क्रम
	 * binding with screen target as during prepare_fb a separate surface is
	 * created so it's safe to ignore SVGA3D_SURFACE_SCREENTARGET flag.
	 */
	अगर (dev_priv->active_display_unit == vmw_du_screen_target &&
	    metadata->scanout &&
	    metadata->base_size.width <= dev_priv->stdu_max_width &&
	    metadata->base_size.height <= dev_priv->stdu_max_height)
		metadata->flags |= SVGA3D_SURFACE_SCREENTARGET;

	/*
	 * From this poपूर्णांक, the generic resource management functions
	 * destroy the object on failure.
	 */
	ret = vmw_surface_init(dev_priv, srf, vmw_user_surface_मुक्त);

	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
	वापस ret;

out_no_user_srf:
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv), user_accounting_size);

out_unlock:
	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
	वापस ret;
पूर्ण
