<शैली गुरु>
/*
 * Copyright 2017 Intel Corporation. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Zhiyuan Lv <zhiyuan.lv@पूर्णांकel.com>
 *
 * Contributors:
 *    Xiaoguang Chen
 *    Tina Zhang <tina.zhang@पूर्णांकel.com>
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/vfपन.स>

#समावेश "i915_drv.h"
#समावेश "gvt.h"

#घोषणा GEN8_DECODE_PTE(pte) (pte & GENMASK_ULL(63, 12))

अटल पूर्णांक vgpu_pin_dma_address(काष्ठा पूर्णांकel_vgpu *vgpu,
				अचिन्हित दीर्घ size,
				dma_addr_t dma_addr)
अणु
	पूर्णांक ret = 0;

	अगर (पूर्णांकel_gvt_hypervisor_dma_pin_guest_page(vgpu, dma_addr))
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल व्योम vgpu_unpin_dma_address(काष्ठा पूर्णांकel_vgpu *vgpu,
				   dma_addr_t dma_addr)
अणु
	पूर्णांकel_gvt_hypervisor_dma_unmap_guest_page(vgpu, dma_addr);
पूर्ण

अटल पूर्णांक vgpu_gem_get_pages(
		काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(obj->base.dev);
	काष्ठा पूर्णांकel_vgpu *vgpu;
	काष्ठा sg_table *st;
	काष्ठा scatterlist *sg;
	पूर्णांक i, j, ret;
	gen8_pte_t __iomem *gtt_entries;
	काष्ठा पूर्णांकel_vgpu_fb_info *fb_info;
	u32 page_num;

	fb_info = (काष्ठा पूर्णांकel_vgpu_fb_info *)obj->gvt_info;
	अगर (drm_WARN_ON(&dev_priv->drm, !fb_info))
		वापस -ENODEV;

	vgpu = fb_info->obj->vgpu;
	अगर (drm_WARN_ON(&dev_priv->drm, !vgpu))
		वापस -ENODEV;

	st = kदो_स्मृति(माप(*st), GFP_KERNEL);
	अगर (unlikely(!st))
		वापस -ENOMEM;

	page_num = obj->base.size >> PAGE_SHIFT;
	ret = sg_alloc_table(st, page_num, GFP_KERNEL);
	अगर (ret) अणु
		kमुक्त(st);
		वापस ret;
	पूर्ण
	gtt_entries = (gen8_pte_t __iomem *)dev_priv->ggtt.gsm +
		(fb_info->start >> PAGE_SHIFT);
	क्रम_each_sg(st->sgl, sg, page_num, i) अणु
		dma_addr_t dma_addr =
			GEN8_DECODE_PTE(पढ़ोq(&gtt_entries[i]));
		अगर (vgpu_pin_dma_address(vgpu, PAGE_SIZE, dma_addr)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		sg->offset = 0;
		sg->length = PAGE_SIZE;
		sg_dma_len(sg) = PAGE_SIZE;
		sg_dma_address(sg) = dma_addr;
	पूर्ण

	__i915_gem_object_set_pages(obj, st, PAGE_SIZE);
out:
	अगर (ret) अणु
		dma_addr_t dma_addr;

		क्रम_each_sg(st->sgl, sg, i, j) अणु
			dma_addr = sg_dma_address(sg);
			अगर (dma_addr)
				vgpu_unpin_dma_address(vgpu, dma_addr);
		पूर्ण
		sg_मुक्त_table(st);
		kमुक्त(st);
	पूर्ण

	वापस ret;

पूर्ण

अटल व्योम vgpu_gem_put_pages(काष्ठा drm_i915_gem_object *obj,
		काष्ठा sg_table *pages)
अणु
	काष्ठा scatterlist *sg;

	अगर (obj->base.dma_buf) अणु
		काष्ठा पूर्णांकel_vgpu_fb_info *fb_info = obj->gvt_info;
		काष्ठा पूर्णांकel_vgpu_dmabuf_obj *obj = fb_info->obj;
		काष्ठा पूर्णांकel_vgpu *vgpu = obj->vgpu;
		पूर्णांक i;

		क्रम_each_sg(pages->sgl, sg, fb_info->size, i)
			vgpu_unpin_dma_address(vgpu,
					       sg_dma_address(sg));
	पूर्ण

	sg_मुक्त_table(pages);
	kमुक्त(pages);
पूर्ण

अटल व्योम dmabuf_gem_object_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा पूर्णांकel_vgpu_dmabuf_obj *obj =
		container_of(kref, काष्ठा पूर्णांकel_vgpu_dmabuf_obj, kref);
	काष्ठा पूर्णांकel_vgpu *vgpu = obj->vgpu;
	काष्ठा list_head *pos;
	काष्ठा पूर्णांकel_vgpu_dmabuf_obj *dmabuf_obj;

	अगर (vgpu && vgpu->active && !list_empty(&vgpu->dmabuf_obj_list_head)) अणु
		list_क्रम_each(pos, &vgpu->dmabuf_obj_list_head) अणु
			dmabuf_obj = container_of(pos,
					काष्ठा पूर्णांकel_vgpu_dmabuf_obj, list);
			अगर (dmabuf_obj == obj) अणु
				list_del(pos);
				पूर्णांकel_gvt_hypervisor_put_vfio_device(vgpu);
				idr_हटाओ(&vgpu->object_idr,
					   dmabuf_obj->dmabuf_id);
				kमुक्त(dmabuf_obj->info);
				kमुक्त(dmabuf_obj);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Free the orphan dmabuf_objs here */
		kमुक्त(obj->info);
		kमुक्त(obj);
	पूर्ण
पूर्ण


अटल अंतरभूत व्योम dmabuf_obj_get(काष्ठा पूर्णांकel_vgpu_dmabuf_obj *obj)
अणु
	kref_get(&obj->kref);
पूर्ण

अटल अंतरभूत व्योम dmabuf_obj_put(काष्ठा पूर्णांकel_vgpu_dmabuf_obj *obj)
अणु
	kref_put(&obj->kref, dmabuf_gem_object_मुक्त);
पूर्ण

अटल व्योम vgpu_gem_release(काष्ठा drm_i915_gem_object *gem_obj)
अणु

	काष्ठा पूर्णांकel_vgpu_fb_info *fb_info = gem_obj->gvt_info;
	काष्ठा पूर्णांकel_vgpu_dmabuf_obj *obj = fb_info->obj;
	काष्ठा पूर्णांकel_vgpu *vgpu = obj->vgpu;

	अगर (vgpu) अणु
		mutex_lock(&vgpu->dmabuf_lock);
		gem_obj->base.dma_buf = शून्य;
		dmabuf_obj_put(obj);
		mutex_unlock(&vgpu->dmabuf_lock);
	पूर्ण अन्यथा अणु
		/* vgpu is शून्य, as it has been हटाओd alपढ़ोy */
		gem_obj->base.dma_buf = शून्य;
		dmabuf_obj_put(obj);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_i915_gem_object_ops पूर्णांकel_vgpu_gem_ops = अणु
	.name = "i915_gem_object_vgpu",
	.flags = I915_GEM_OBJECT_IS_PROXY,
	.get_pages = vgpu_gem_get_pages,
	.put_pages = vgpu_gem_put_pages,
	.release = vgpu_gem_release,
पूर्ण;

अटल काष्ठा drm_i915_gem_object *vgpu_create_gem(काष्ठा drm_device *dev,
		काष्ठा पूर्णांकel_vgpu_fb_info *info)
अणु
	अटल काष्ठा lock_class_key lock_class;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_i915_gem_object *obj;

	obj = i915_gem_object_alloc();
	अगर (obj == शून्य)
		वापस शून्य;

	drm_gem_निजी_object_init(dev, &obj->base,
		roundup(info->size, PAGE_SIZE));
	i915_gem_object_init(obj, &पूर्णांकel_vgpu_gem_ops, &lock_class, 0);
	i915_gem_object_set_पढ़ोonly(obj);

	obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_GTT;
	obj->ग_लिखो_करोमुख्य = 0;
	अगर (INTEL_GEN(dev_priv) >= 9) अणु
		अचिन्हित पूर्णांक tiling_mode = 0;
		अचिन्हित पूर्णांक stride = 0;

		चयन (info->drm_क्रमmat_mod) अणु
		हाल DRM_FORMAT_MOD_LINEAR:
			tiling_mode = I915_TILING_NONE;
			अवरोध;
		हाल I915_FORMAT_MOD_X_TILED:
			tiling_mode = I915_TILING_X;
			stride = info->stride;
			अवरोध;
		हाल I915_FORMAT_MOD_Y_TILED:
		हाल I915_FORMAT_MOD_Yf_TILED:
			tiling_mode = I915_TILING_Y;
			stride = info->stride;
			अवरोध;
		शेष:
			gvt_dbg_core("invalid drm_format_mod %llx for tiling\n",
				     info->drm_क्रमmat_mod);
		पूर्ण
		obj->tiling_and_stride = tiling_mode | stride;
	पूर्ण अन्यथा अणु
		obj->tiling_and_stride = info->drm_क्रमmat_mod ?
					I915_TILING_X : 0;
	पूर्ण

	वापस obj;
पूर्ण

अटल bool validate_hotspot(काष्ठा पूर्णांकel_vgpu_cursor_plane_क्रमmat *c)
अणु
	अगर (c && c->x_hot <= c->width && c->y_hot <= c->height)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक vgpu_get_plane_info(काष्ठा drm_device *dev,
		काष्ठा पूर्णांकel_vgpu *vgpu,
		काष्ठा पूर्णांकel_vgpu_fb_info *info,
		पूर्णांक plane_id)
अणु
	काष्ठा पूर्णांकel_vgpu_primary_plane_क्रमmat p;
	काष्ठा पूर्णांकel_vgpu_cursor_plane_क्रमmat c;
	पूर्णांक ret, tile_height = 1;

	स_रखो(info, 0, माप(*info));

	अगर (plane_id == DRM_PLANE_TYPE_PRIMARY) अणु
		ret = पूर्णांकel_vgpu_decode_primary_plane(vgpu, &p);
		अगर (ret)
			वापस ret;
		info->start = p.base;
		info->start_gpa = p.base_gpa;
		info->width = p.width;
		info->height = p.height;
		info->stride = p.stride;
		info->drm_क्रमmat = p.drm_क्रमmat;

		चयन (p.tiled) अणु
		हाल PLANE_CTL_TILED_LINEAR:
			info->drm_क्रमmat_mod = DRM_FORMAT_MOD_LINEAR;
			अवरोध;
		हाल PLANE_CTL_TILED_X:
			info->drm_क्रमmat_mod = I915_FORMAT_MOD_X_TILED;
			tile_height = 8;
			अवरोध;
		हाल PLANE_CTL_TILED_Y:
			info->drm_क्रमmat_mod = I915_FORMAT_MOD_Y_TILED;
			tile_height = 32;
			अवरोध;
		हाल PLANE_CTL_TILED_YF:
			info->drm_क्रमmat_mod = I915_FORMAT_MOD_Yf_TILED;
			tile_height = 32;
			अवरोध;
		शेष:
			gvt_vgpu_err("invalid tiling mode: %x\n", p.tiled);
		पूर्ण
	पूर्ण अन्यथा अगर (plane_id == DRM_PLANE_TYPE_CURSOR) अणु
		ret = पूर्णांकel_vgpu_decode_cursor_plane(vgpu, &c);
		अगर (ret)
			वापस ret;
		info->start = c.base;
		info->start_gpa = c.base_gpa;
		info->width = c.width;
		info->height = c.height;
		info->stride = c.width * (c.bpp / 8);
		info->drm_क्रमmat = c.drm_क्रमmat;
		info->drm_क्रमmat_mod = 0;
		info->x_pos = c.x_pos;
		info->y_pos = c.y_pos;

		अगर (validate_hotspot(&c)) अणु
			info->x_hot = c.x_hot;
			info->y_hot = c.y_hot;
		पूर्ण अन्यथा अणु
			info->x_hot = अच_पूर्णांक_उच्च;
			info->y_hot = अच_पूर्णांक_उच्च;
		पूर्ण
	पूर्ण अन्यथा अणु
		gvt_vgpu_err("invalid plane id:%d\n", plane_id);
		वापस -EINVAL;
	पूर्ण

	info->size = info->stride * roundup(info->height, tile_height);
	अगर (info->size == 0) अणु
		gvt_vgpu_err("fb size is zero\n");
		वापस -EINVAL;
	पूर्ण

	अगर (info->start & (PAGE_SIZE - 1)) अणु
		gvt_vgpu_err("Not aligned fb address:0x%llx\n", info->start);
		वापस -EFAULT;
	पूर्ण

	अगर (!पूर्णांकel_gvt_ggtt_validate_range(vgpu, info->start, info->size)) अणु
		gvt_vgpu_err("invalid gma addr\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_vgpu_dmabuf_obj *
pick_dmabuf_by_info(काष्ठा पूर्णांकel_vgpu *vgpu,
		    काष्ठा पूर्णांकel_vgpu_fb_info *latest_info)
अणु
	काष्ठा list_head *pos;
	काष्ठा पूर्णांकel_vgpu_fb_info *fb_info;
	काष्ठा पूर्णांकel_vgpu_dmabuf_obj *dmabuf_obj = शून्य;
	काष्ठा पूर्णांकel_vgpu_dmabuf_obj *ret = शून्य;

	list_क्रम_each(pos, &vgpu->dmabuf_obj_list_head) अणु
		dmabuf_obj = container_of(pos, काष्ठा पूर्णांकel_vgpu_dmabuf_obj,
						list);
		अगर ((dmabuf_obj == शून्य) ||
		    (dmabuf_obj->info == शून्य))
			जारी;

		fb_info = (काष्ठा पूर्णांकel_vgpu_fb_info *)dmabuf_obj->info;
		अगर ((fb_info->start == latest_info->start) &&
		    (fb_info->start_gpa == latest_info->start_gpa) &&
		    (fb_info->size == latest_info->size) &&
		    (fb_info->drm_क्रमmat_mod == latest_info->drm_क्रमmat_mod) &&
		    (fb_info->drm_क्रमmat == latest_info->drm_क्रमmat) &&
		    (fb_info->width == latest_info->width) &&
		    (fb_info->height == latest_info->height)) अणु
			ret = dmabuf_obj;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा पूर्णांकel_vgpu_dmabuf_obj *
pick_dmabuf_by_num(काष्ठा पूर्णांकel_vgpu *vgpu, u32 id)
अणु
	काष्ठा list_head *pos;
	काष्ठा पूर्णांकel_vgpu_dmabuf_obj *dmabuf_obj = शून्य;
	काष्ठा पूर्णांकel_vgpu_dmabuf_obj *ret = शून्य;

	list_क्रम_each(pos, &vgpu->dmabuf_obj_list_head) अणु
		dmabuf_obj = container_of(pos, काष्ठा पूर्णांकel_vgpu_dmabuf_obj,
						list);
		अगर (!dmabuf_obj)
			जारी;

		अगर (dmabuf_obj->dmabuf_id == id) अणु
			ret = dmabuf_obj;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम update_fb_info(काष्ठा vfio_device_gfx_plane_info *gvt_dmabuf,
		      काष्ठा पूर्णांकel_vgpu_fb_info *fb_info)
अणु
	gvt_dmabuf->drm_क्रमmat = fb_info->drm_क्रमmat;
	gvt_dmabuf->drm_क्रमmat_mod = fb_info->drm_क्रमmat_mod;
	gvt_dmabuf->width = fb_info->width;
	gvt_dmabuf->height = fb_info->height;
	gvt_dmabuf->stride = fb_info->stride;
	gvt_dmabuf->size = fb_info->size;
	gvt_dmabuf->x_pos = fb_info->x_pos;
	gvt_dmabuf->y_pos = fb_info->y_pos;
	gvt_dmabuf->x_hot = fb_info->x_hot;
	gvt_dmabuf->y_hot = fb_info->y_hot;
पूर्ण

पूर्णांक पूर्णांकel_vgpu_query_plane(काष्ठा पूर्णांकel_vgpu *vgpu, व्योम *args)
अणु
	काष्ठा drm_device *dev = &vgpu->gvt->gt->i915->drm;
	काष्ठा vfio_device_gfx_plane_info *gfx_plane_info = args;
	काष्ठा पूर्णांकel_vgpu_dmabuf_obj *dmabuf_obj;
	काष्ठा पूर्णांकel_vgpu_fb_info fb_info;
	पूर्णांक ret = 0;

	अगर (gfx_plane_info->flags == (VFIO_GFX_PLANE_TYPE_DMABUF |
				       VFIO_GFX_PLANE_TYPE_PROBE))
		वापस ret;
	अन्यथा अगर ((gfx_plane_info->flags & ~VFIO_GFX_PLANE_TYPE_DMABUF) ||
			(!gfx_plane_info->flags))
		वापस -EINVAL;

	ret = vgpu_get_plane_info(dev, vgpu, &fb_info,
					gfx_plane_info->drm_plane_type);
	अगर (ret != 0)
		जाओ out;

	mutex_lock(&vgpu->dmabuf_lock);
	/* If exists, pick up the exposed dmabuf_obj */
	dmabuf_obj = pick_dmabuf_by_info(vgpu, &fb_info);
	अगर (dmabuf_obj) अणु
		update_fb_info(gfx_plane_info, &fb_info);
		gfx_plane_info->dmabuf_id = dmabuf_obj->dmabuf_id;

		/* This buffer may be released between query_plane ioctl and
		 * get_dmabuf ioctl. Add the refcount to make sure it won't
		 * be released between the two ioctls.
		 */
		अगर (!dmabuf_obj->initref) अणु
			dmabuf_obj->initref = true;
			dmabuf_obj_get(dmabuf_obj);
		पूर्ण
		ret = 0;
		gvt_dbg_dpy("vgpu%d: re-use dmabuf_obj ref %d, id %d\n",
			    vgpu->id, kref_पढ़ो(&dmabuf_obj->kref),
			    gfx_plane_info->dmabuf_id);
		mutex_unlock(&vgpu->dmabuf_lock);
		जाओ out;
	पूर्ण

	mutex_unlock(&vgpu->dmabuf_lock);

	/* Need to allocate a new one*/
	dmabuf_obj = kदो_स्मृति(माप(काष्ठा पूर्णांकel_vgpu_dmabuf_obj), GFP_KERNEL);
	अगर (unlikely(!dmabuf_obj)) अणु
		gvt_vgpu_err("alloc dmabuf_obj failed\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	dmabuf_obj->info = kदो_स्मृति(माप(काष्ठा पूर्णांकel_vgpu_fb_info),
				   GFP_KERNEL);
	अगर (unlikely(!dmabuf_obj->info)) अणु
		gvt_vgpu_err("allocate intel vgpu fb info failed\n");
		ret = -ENOMEM;
		जाओ out_मुक्त_dmabuf;
	पूर्ण
	स_नकल(dmabuf_obj->info, &fb_info, माप(काष्ठा पूर्णांकel_vgpu_fb_info));

	((काष्ठा पूर्णांकel_vgpu_fb_info *)dmabuf_obj->info)->obj = dmabuf_obj;

	dmabuf_obj->vgpu = vgpu;

	ret = idr_alloc(&vgpu->object_idr, dmabuf_obj, 1, 0, GFP_NOWAIT);
	अगर (ret < 0)
		जाओ out_मुक्त_info;
	gfx_plane_info->dmabuf_id = ret;
	dmabuf_obj->dmabuf_id = ret;

	dmabuf_obj->initref = true;

	kref_init(&dmabuf_obj->kref);

	mutex_lock(&vgpu->dmabuf_lock);
	अगर (पूर्णांकel_gvt_hypervisor_get_vfio_device(vgpu)) अणु
		gvt_vgpu_err("get vfio device failed\n");
		mutex_unlock(&vgpu->dmabuf_lock);
		जाओ out_मुक्त_info;
	पूर्ण
	mutex_unlock(&vgpu->dmabuf_lock);

	update_fb_info(gfx_plane_info, &fb_info);

	INIT_LIST_HEAD(&dmabuf_obj->list);
	mutex_lock(&vgpu->dmabuf_lock);
	list_add_tail(&dmabuf_obj->list, &vgpu->dmabuf_obj_list_head);
	mutex_unlock(&vgpu->dmabuf_lock);

	gvt_dbg_dpy("vgpu%d: %s new dmabuf_obj ref %d, id %d\n", vgpu->id,
		    __func__, kref_पढ़ो(&dmabuf_obj->kref), ret);

	वापस 0;

out_मुक्त_info:
	kमुक्त(dmabuf_obj->info);
out_मुक्त_dmabuf:
	kमुक्त(dmabuf_obj);
out:
	/* ENODEV means plane isn't पढ़ोy, which might be a normal हाल. */
	वापस (ret == -ENODEV) ? 0 : ret;
पूर्ण

/* To associate an exposed dmabuf with the dmabuf_obj */
पूर्णांक पूर्णांकel_vgpu_get_dmabuf(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक dmabuf_id)
अणु
	काष्ठा drm_device *dev = &vgpu->gvt->gt->i915->drm;
	काष्ठा पूर्णांकel_vgpu_dmabuf_obj *dmabuf_obj;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा dma_buf *dmabuf;
	पूर्णांक dmabuf_fd;
	पूर्णांक ret = 0;

	mutex_lock(&vgpu->dmabuf_lock);

	dmabuf_obj = pick_dmabuf_by_num(vgpu, dmabuf_id);
	अगर (dmabuf_obj == शून्य) अणु
		gvt_vgpu_err("invalid dmabuf id:%d\n", dmabuf_id);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	obj = vgpu_create_gem(dev, dmabuf_obj->info);
	अगर (obj == शून्य) अणु
		gvt_vgpu_err("create gvt gem obj failed\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	obj->gvt_info = dmabuf_obj->info;

	dmabuf = i915_gem_prime_export(&obj->base, DRM_CLOEXEC | DRM_RDWR);
	अगर (IS_ERR(dmabuf)) अणु
		gvt_vgpu_err("export dma-buf failed\n");
		ret = PTR_ERR(dmabuf);
		जाओ out_मुक्त_gem;
	पूर्ण

	ret = dma_buf_fd(dmabuf, DRM_CLOEXEC | DRM_RDWR);
	अगर (ret < 0) अणु
		gvt_vgpu_err("create dma-buf fd failed ret:%d\n", ret);
		जाओ out_मुक्त_dmabuf;
	पूर्ण
	dmabuf_fd = ret;

	dmabuf_obj_get(dmabuf_obj);

	अगर (dmabuf_obj->initref) अणु
		dmabuf_obj->initref = false;
		dmabuf_obj_put(dmabuf_obj);
	पूर्ण

	mutex_unlock(&vgpu->dmabuf_lock);

	gvt_dbg_dpy("vgpu%d: dmabuf:%d, dmabuf ref %d, fd:%d\n"
		    "        file count: %ld, GEM ref: %d\n",
		    vgpu->id, dmabuf_obj->dmabuf_id,
		    kref_पढ़ो(&dmabuf_obj->kref),
		    dmabuf_fd,
		    file_count(dmabuf->file),
		    kref_पढ़ो(&obj->base.refcount));

	i915_gem_object_put(obj);

	वापस dmabuf_fd;

out_मुक्त_dmabuf:
	dma_buf_put(dmabuf);
out_मुक्त_gem:
	i915_gem_object_put(obj);
out:
	mutex_unlock(&vgpu->dmabuf_lock);
	वापस ret;
पूर्ण

व्योम पूर्णांकel_vgpu_dmabuf_cleanup(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा list_head *pos, *n;
	काष्ठा पूर्णांकel_vgpu_dmabuf_obj *dmabuf_obj;

	mutex_lock(&vgpu->dmabuf_lock);
	list_क्रम_each_safe(pos, n, &vgpu->dmabuf_obj_list_head) अणु
		dmabuf_obj = container_of(pos, काष्ठा पूर्णांकel_vgpu_dmabuf_obj,
						list);
		dmabuf_obj->vgpu = शून्य;

		idr_हटाओ(&vgpu->object_idr, dmabuf_obj->dmabuf_id);
		पूर्णांकel_gvt_hypervisor_put_vfio_device(vgpu);
		list_del(pos);

		/* dmabuf_obj might be मुक्तd in dmabuf_obj_put */
		अगर (dmabuf_obj->initref) अणु
			dmabuf_obj->initref = false;
			dmabuf_obj_put(dmabuf_obj);
		पूर्ण

	पूर्ण
	mutex_unlock(&vgpu->dmabuf_lock);
पूर्ण
