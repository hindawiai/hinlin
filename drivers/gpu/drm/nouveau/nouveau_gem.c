<शैली गुरु>
/*
 * Copyright (C) 2008 Ben Skeggs.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <drm/drm_gem_tपंचांग_helper.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_dma.h"
#समावेश "nouveau_fence.h"
#समावेश "nouveau_abi16.h"

#समावेश "nouveau_ttm.h"
#समावेश "nouveau_gem.h"
#समावेश "nouveau_mem.h"
#समावेश "nouveau_vmm.h"

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/push206e.h>

व्योम
nouveau_gem_object_del(काष्ठा drm_gem_object *gem)
अणु
	काष्ठा nouveau_bo *nvbo = nouveau_gem_object(gem);
	काष्ठा nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	काष्ठा device *dev = drm->dev->dev;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (WARN_ON(ret < 0 && ret != -EACCES)) अणु
		pm_runसमय_put_स्वतःsuspend(dev);
		वापस;
	पूर्ण

	अगर (gem->import_attach)
		drm_prime_gem_destroy(gem, nvbo->bo.sg);

	tपंचांग_bo_put(&nvbo->bo);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
पूर्ण

पूर्णांक
nouveau_gem_object_खोलो(काष्ठा drm_gem_object *gem, काष्ठा drm_file *file_priv)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(file_priv);
	काष्ठा nouveau_bo *nvbo = nouveau_gem_object(gem);
	काष्ठा nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	काष्ठा device *dev = drm->dev->dev;
	काष्ठा nouveau_vmm *vmm = cli->svm.cli ? &cli->svm : &cli->vmm;
	काष्ठा nouveau_vma *vma;
	पूर्णांक ret;

	अगर (vmm->vmm.object.oclass < NVIF_CLASS_VMM_NV50)
		वापस 0;

	ret = tपंचांग_bo_reserve(&nvbo->bo, false, false, शून्य);
	अगर (ret)
		वापस ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		pm_runसमय_put_स्वतःsuspend(dev);
		जाओ out;
	पूर्ण

	ret = nouveau_vma_new(nvbo, vmm, &vma);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
out:
	tपंचांग_bo_unreserve(&nvbo->bo);
	वापस ret;
पूर्ण

काष्ठा nouveau_gem_object_unmap अणु
	काष्ठा nouveau_cli_work work;
	काष्ठा nouveau_vma *vma;
पूर्ण;

अटल व्योम
nouveau_gem_object_delete(काष्ठा nouveau_vma *vma)
अणु
	nouveau_fence_unref(&vma->fence);
	nouveau_vma_del(&vma);
पूर्ण

अटल व्योम
nouveau_gem_object_delete_work(काष्ठा nouveau_cli_work *w)
अणु
	काष्ठा nouveau_gem_object_unmap *work =
		container_of(w, typeof(*work), work);
	nouveau_gem_object_delete(work->vma);
	kमुक्त(work);
पूर्ण

अटल व्योम
nouveau_gem_object_unmap(काष्ठा nouveau_bo *nvbo, काष्ठा nouveau_vma *vma)
अणु
	काष्ठा dma_fence *fence = vma->fence ? &vma->fence->base : शून्य;
	काष्ठा nouveau_gem_object_unmap *work;

	list_del_init(&vma->head);

	अगर (!fence) अणु
		nouveau_gem_object_delete(vma);
		वापस;
	पूर्ण

	अगर (!(work = kदो_स्मृति(माप(*work), GFP_KERNEL))) अणु
		WARN_ON(dma_fence_रुको_समयout(fence, false, 2 * HZ) <= 0);
		nouveau_gem_object_delete(vma);
		वापस;
	पूर्ण

	work->work.func = nouveau_gem_object_delete_work;
	work->vma = vma;
	nouveau_cli_work_queue(vma->vmm->cli, fence, &work->work);
पूर्ण

व्योम
nouveau_gem_object_बंद(काष्ठा drm_gem_object *gem, काष्ठा drm_file *file_priv)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(file_priv);
	काष्ठा nouveau_bo *nvbo = nouveau_gem_object(gem);
	काष्ठा nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	काष्ठा device *dev = drm->dev->dev;
	काष्ठा nouveau_vmm *vmm = cli->svm.cli ? &cli->svm : & cli->vmm;
	काष्ठा nouveau_vma *vma;
	पूर्णांक ret;

	अगर (vmm->vmm.object.oclass < NVIF_CLASS_VMM_NV50)
		वापस;

	ret = tपंचांग_bo_reserve(&nvbo->bo, false, false, शून्य);
	अगर (ret)
		वापस;

	vma = nouveau_vma_find(nvbo, vmm);
	अगर (vma) अणु
		अगर (--vma->refs == 0) अणु
			ret = pm_runसमय_get_sync(dev);
			अगर (!WARN_ON(ret < 0 && ret != -EACCES)) अणु
				nouveau_gem_object_unmap(nvbo, vma);
				pm_runसमय_mark_last_busy(dev);
			पूर्ण
			pm_runसमय_put_स्वतःsuspend(dev);
		पूर्ण
	पूर्ण
	tपंचांग_bo_unreserve(&nvbo->bo);
पूर्ण

स्थिर काष्ठा drm_gem_object_funcs nouveau_gem_object_funcs = अणु
	.मुक्त = nouveau_gem_object_del,
	.खोलो = nouveau_gem_object_खोलो,
	.बंद = nouveau_gem_object_बंद,
	.pin = nouveau_gem_prime_pin,
	.unpin = nouveau_gem_prime_unpin,
	.get_sg_table = nouveau_gem_prime_get_sg_table,
	.vmap = drm_gem_tपंचांग_vmap,
	.vunmap = drm_gem_tपंचांग_vunmap,
पूर्ण;

पूर्णांक
nouveau_gem_new(काष्ठा nouveau_cli *cli, u64 size, पूर्णांक align, uपूर्णांक32_t करोमुख्य,
		uपूर्णांक32_t tile_mode, uपूर्णांक32_t tile_flags,
		काष्ठा nouveau_bo **pnvbo)
अणु
	काष्ठा nouveau_drm *drm = cli->drm;
	काष्ठा nouveau_bo *nvbo;
	पूर्णांक ret;

	अगर (!(करोमुख्य & (NOUVEAU_GEM_DOMAIN_VRAM | NOUVEAU_GEM_DOMAIN_GART)))
		करोमुख्य |= NOUVEAU_GEM_DOMAIN_CPU;

	nvbo = nouveau_bo_alloc(cli, &size, &align, करोमुख्य, tile_mode,
				tile_flags);
	अगर (IS_ERR(nvbo))
		वापस PTR_ERR(nvbo);

	nvbo->bo.base.funcs = &nouveau_gem_object_funcs;

	/* Initialize the embedded gem-object. We वापस a single gem-reference
	 * to the caller, instead of a normal nouveau_bo tपंचांग reference. */
	ret = drm_gem_object_init(drm->dev, &nvbo->bo.base, size);
	अगर (ret) अणु
		drm_gem_object_release(&nvbo->bo.base);
		kमुक्त(nvbo);
		वापस ret;
	पूर्ण

	ret = nouveau_bo_init(nvbo, size, align, करोमुख्य, शून्य, शून्य);
	अगर (ret) अणु
		nouveau_bo_ref(शून्य, &nvbo);
		वापस ret;
	पूर्ण

	/* we restrict allowed करोमुख्यs on nv50+ to only the types
	 * that were requested at creation समय.  not possibly on
	 * earlier chips without busting the ABI.
	 */
	nvbo->valid_करोमुख्यs = NOUVEAU_GEM_DOMAIN_VRAM |
			      NOUVEAU_GEM_DOMAIN_GART;
	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA)
		nvbo->valid_करोमुख्यs &= करोमुख्य;

	*pnvbo = nvbo;
	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_gem_info(काष्ठा drm_file *file_priv, काष्ठा drm_gem_object *gem,
		 काष्ठा drm_nouveau_gem_info *rep)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(file_priv);
	काष्ठा nouveau_bo *nvbo = nouveau_gem_object(gem);
	काष्ठा nouveau_vmm *vmm = cli->svm.cli ? &cli->svm : &cli->vmm;
	काष्ठा nouveau_vma *vma;

	अगर (is_घातer_of_2(nvbo->valid_करोमुख्यs))
		rep->करोमुख्य = nvbo->valid_करोमुख्यs;
	अन्यथा अगर (nvbo->bo.mem.mem_type == TTM_PL_TT)
		rep->करोमुख्य = NOUVEAU_GEM_DOMAIN_GART;
	अन्यथा
		rep->करोमुख्य = NOUVEAU_GEM_DOMAIN_VRAM;
	rep->offset = nvbo->offset;
	अगर (vmm->vmm.object.oclass >= NVIF_CLASS_VMM_NV50) अणु
		vma = nouveau_vma_find(nvbo, vmm);
		अगर (!vma)
			वापस -EINVAL;

		rep->offset = vma->addr;
	पूर्ण

	rep->size = nvbo->bo.mem.num_pages << PAGE_SHIFT;
	rep->map_handle = drm_vma_node_offset_addr(&nvbo->bo.base.vma_node);
	rep->tile_mode = nvbo->mode;
	rep->tile_flags = nvbo->contig ? 0 : NOUVEAU_GEM_TILE_NONCONTIG;
	अगर (cli->device.info.family >= NV_DEVICE_INFO_V0_FERMI)
		rep->tile_flags |= nvbo->kind << 8;
	अन्यथा
	अगर (cli->device.info.family >= NV_DEVICE_INFO_V0_TESLA)
		rep->tile_flags |= nvbo->kind << 8 | nvbo->comp << 16;
	अन्यथा
		rep->tile_flags |= nvbo->zeta;
	वापस 0;
पूर्ण

पूर्णांक
nouveau_gem_ioctl_new(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(file_priv);
	काष्ठा drm_nouveau_gem_new *req = data;
	काष्ठा nouveau_bo *nvbo = शून्य;
	पूर्णांक ret = 0;

	ret = nouveau_gem_new(cli, req->info.size, req->align,
			      req->info.करोमुख्य, req->info.tile_mode,
			      req->info.tile_flags, &nvbo);
	अगर (ret)
		वापस ret;

	ret = drm_gem_handle_create(file_priv, &nvbo->bo.base,
				    &req->info.handle);
	अगर (ret == 0) अणु
		ret = nouveau_gem_info(file_priv, &nvbo->bo.base, &req->info);
		अगर (ret)
			drm_gem_handle_delete(file_priv, req->info.handle);
	पूर्ण

	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put(&nvbo->bo.base);
	वापस ret;
पूर्ण

अटल पूर्णांक
nouveau_gem_set_करोमुख्य(काष्ठा drm_gem_object *gem, uपूर्णांक32_t पढ़ो_करोमुख्यs,
		       uपूर्णांक32_t ग_लिखो_करोमुख्यs, uपूर्णांक32_t valid_करोमुख्यs)
अणु
	काष्ठा nouveau_bo *nvbo = nouveau_gem_object(gem);
	काष्ठा tपंचांग_buffer_object *bo = &nvbo->bo;
	uपूर्णांक32_t करोमुख्यs = valid_करोमुख्यs & nvbo->valid_करोमुख्यs &
		(ग_लिखो_करोमुख्यs ? ग_लिखो_करोमुख्यs : पढ़ो_करोमुख्यs);
	uपूर्णांक32_t pref_करोमुख्यs = 0;;

	अगर (!करोमुख्यs)
		वापस -EINVAL;

	valid_करोमुख्यs &= ~(NOUVEAU_GEM_DOMAIN_VRAM | NOUVEAU_GEM_DOMAIN_GART);

	अगर ((करोमुख्यs & NOUVEAU_GEM_DOMAIN_VRAM) &&
	    bo->mem.mem_type == TTM_PL_VRAM)
		pref_करोमुख्यs |= NOUVEAU_GEM_DOMAIN_VRAM;

	अन्यथा अगर ((करोमुख्यs & NOUVEAU_GEM_DOMAIN_GART) &&
		 bo->mem.mem_type == TTM_PL_TT)
		pref_करोमुख्यs |= NOUVEAU_GEM_DOMAIN_GART;

	अन्यथा अगर (करोमुख्यs & NOUVEAU_GEM_DOMAIN_VRAM)
		pref_करोमुख्यs |= NOUVEAU_GEM_DOMAIN_VRAM;

	अन्यथा
		pref_करोमुख्यs |= NOUVEAU_GEM_DOMAIN_GART;

	nouveau_bo_placement_set(nvbo, pref_करोमुख्यs, valid_करोमुख्यs);

	वापस 0;
पूर्ण

काष्ठा validate_op अणु
	काष्ठा list_head list;
	काष्ठा ww_acquire_ctx ticket;
पूर्ण;

अटल व्योम
validate_fini_no_ticket(काष्ठा validate_op *op, काष्ठा nouveau_channel *chan,
			काष्ठा nouveau_fence *fence,
			काष्ठा drm_nouveau_gem_pushbuf_bo *pbbo)
अणु
	काष्ठा nouveau_bo *nvbo;
	काष्ठा drm_nouveau_gem_pushbuf_bo *b;

	जबतक (!list_empty(&op->list)) अणु
		nvbo = list_entry(op->list.next, काष्ठा nouveau_bo, entry);
		b = &pbbo[nvbo->pbbo_index];

		अगर (likely(fence)) अणु
			nouveau_bo_fence(nvbo, fence, !!b->ग_लिखो_करोमुख्यs);

			अगर (chan->vmm->vmm.object.oclass >= NVIF_CLASS_VMM_NV50) अणु
				काष्ठा nouveau_vma *vma =
					(व्योम *)(अचिन्हित दीर्घ)b->user_priv;
				nouveau_fence_unref(&vma->fence);
				dma_fence_get(&fence->base);
				vma->fence = fence;
			पूर्ण
		पूर्ण

		अगर (unlikely(nvbo->validate_mapped)) अणु
			tपंचांग_bo_kunmap(&nvbo->kmap);
			nvbo->validate_mapped = false;
		पूर्ण

		list_del(&nvbo->entry);
		nvbo->reserved_by = शून्य;
		tपंचांग_bo_unreserve(&nvbo->bo);
		drm_gem_object_put(&nvbo->bo.base);
	पूर्ण
पूर्ण

अटल व्योम
validate_fini(काष्ठा validate_op *op, काष्ठा nouveau_channel *chan,
	      काष्ठा nouveau_fence *fence,
	      काष्ठा drm_nouveau_gem_pushbuf_bo *pbbo)
अणु
	validate_fini_no_ticket(op, chan, fence, pbbo);
	ww_acquire_fini(&op->ticket);
पूर्ण

अटल पूर्णांक
validate_init(काष्ठा nouveau_channel *chan, काष्ठा drm_file *file_priv,
	      काष्ठा drm_nouveau_gem_pushbuf_bo *pbbo,
	      पूर्णांक nr_buffers, काष्ठा validate_op *op)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(file_priv);
	पूर्णांक trycnt = 0;
	पूर्णांक ret = -EINVAL, i;
	काष्ठा nouveau_bo *res_bo = शून्य;
	LIST_HEAD(gart_list);
	LIST_HEAD(vram_list);
	LIST_HEAD(both_list);

	ww_acquire_init(&op->ticket, &reservation_ww_class);
retry:
	अगर (++trycnt > 100000) अणु
		NV_PRINTK(err, cli, "%s failed and gave up.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < nr_buffers; i++) अणु
		काष्ठा drm_nouveau_gem_pushbuf_bo *b = &pbbo[i];
		काष्ठा drm_gem_object *gem;
		काष्ठा nouveau_bo *nvbo;

		gem = drm_gem_object_lookup(file_priv, b->handle);
		अगर (!gem) अणु
			NV_PRINTK(err, cli, "Unknown handle 0x%08x\n", b->handle);
			ret = -ENOENT;
			अवरोध;
		पूर्ण
		nvbo = nouveau_gem_object(gem);
		अगर (nvbo == res_bo) अणु
			res_bo = शून्य;
			drm_gem_object_put(gem);
			जारी;
		पूर्ण

		अगर (nvbo->reserved_by && nvbo->reserved_by == file_priv) अणु
			NV_PRINTK(err, cli, "multiple instances of buffer %d on "
				      "validation list\n", b->handle);
			drm_gem_object_put(gem);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ret = tपंचांग_bo_reserve(&nvbo->bo, true, false, &op->ticket);
		अगर (ret) अणु
			list_splice_tail_init(&vram_list, &op->list);
			list_splice_tail_init(&gart_list, &op->list);
			list_splice_tail_init(&both_list, &op->list);
			validate_fini_no_ticket(op, chan, शून्य, शून्य);
			अगर (unlikely(ret == -EDEADLK)) अणु
				ret = tपंचांग_bo_reserve_slowpath(&nvbo->bo, true,
							      &op->ticket);
				अगर (!ret)
					res_bo = nvbo;
			पूर्ण
			अगर (unlikely(ret)) अणु
				अगर (ret != -ERESTARTSYS)
					NV_PRINTK(err, cli, "fail reserve\n");
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (chan->vmm->vmm.object.oclass >= NVIF_CLASS_VMM_NV50) अणु
			काष्ठा nouveau_vmm *vmm = chan->vmm;
			काष्ठा nouveau_vma *vma = nouveau_vma_find(nvbo, vmm);
			अगर (!vma) अणु
				NV_PRINTK(err, cli, "vma not found!\n");
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			b->user_priv = (uपूर्णांक64_t)(अचिन्हित दीर्घ)vma;
		पूर्ण अन्यथा अणु
			b->user_priv = (uपूर्णांक64_t)(अचिन्हित दीर्घ)nvbo;
		पूर्ण

		nvbo->reserved_by = file_priv;
		nvbo->pbbo_index = i;
		अगर ((b->valid_करोमुख्यs & NOUVEAU_GEM_DOMAIN_VRAM) &&
		    (b->valid_करोमुख्यs & NOUVEAU_GEM_DOMAIN_GART))
			list_add_tail(&nvbo->entry, &both_list);
		अन्यथा
		अगर (b->valid_करोमुख्यs & NOUVEAU_GEM_DOMAIN_VRAM)
			list_add_tail(&nvbo->entry, &vram_list);
		अन्यथा
		अगर (b->valid_करोमुख्यs & NOUVEAU_GEM_DOMAIN_GART)
			list_add_tail(&nvbo->entry, &gart_list);
		अन्यथा अणु
			NV_PRINTK(err, cli, "invalid valid domains: 0x%08x\n",
				 b->valid_करोमुख्यs);
			list_add_tail(&nvbo->entry, &both_list);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (nvbo == res_bo)
			जाओ retry;
	पूर्ण

	ww_acquire_करोne(&op->ticket);
	list_splice_tail(&vram_list, &op->list);
	list_splice_tail(&gart_list, &op->list);
	list_splice_tail(&both_list, &op->list);
	अगर (ret)
		validate_fini(op, chan, शून्य, शून्य);
	वापस ret;

पूर्ण

अटल पूर्णांक
validate_list(काष्ठा nouveau_channel *chan, काष्ठा nouveau_cli *cli,
	      काष्ठा list_head *list, काष्ठा drm_nouveau_gem_pushbuf_bo *pbbo)
अणु
	काष्ठा nouveau_drm *drm = chan->drm;
	काष्ठा nouveau_bo *nvbo;
	पूर्णांक ret, relocs = 0;

	list_क्रम_each_entry(nvbo, list, entry) अणु
		काष्ठा drm_nouveau_gem_pushbuf_bo *b = &pbbo[nvbo->pbbo_index];

		ret = nouveau_gem_set_करोमुख्य(&nvbo->bo.base, b->पढ़ो_करोमुख्यs,
					     b->ग_लिखो_करोमुख्यs,
					     b->valid_करोमुख्यs);
		अगर (unlikely(ret)) अणु
			NV_PRINTK(err, cli, "fail set_domain\n");
			वापस ret;
		पूर्ण

		ret = nouveau_bo_validate(nvbo, true, false);
		अगर (unlikely(ret)) अणु
			अगर (ret != -ERESTARTSYS)
				NV_PRINTK(err, cli, "fail ttm_validate\n");
			वापस ret;
		पूर्ण

		ret = nouveau_fence_sync(nvbo, chan, !!b->ग_लिखो_करोमुख्यs, true);
		अगर (unlikely(ret)) अणु
			अगर (ret != -ERESTARTSYS)
				NV_PRINTK(err, cli, "fail post-validate sync\n");
			वापस ret;
		पूर्ण

		अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA) अणु
			अगर (nvbo->offset == b->presumed.offset &&
			    ((nvbo->bo.mem.mem_type == TTM_PL_VRAM &&
			      b->presumed.करोमुख्य & NOUVEAU_GEM_DOMAIN_VRAM) ||
			     (nvbo->bo.mem.mem_type == TTM_PL_TT &&
			      b->presumed.करोमुख्य & NOUVEAU_GEM_DOMAIN_GART)))
				जारी;

			अगर (nvbo->bo.mem.mem_type == TTM_PL_TT)
				b->presumed.करोमुख्य = NOUVEAU_GEM_DOMAIN_GART;
			अन्यथा
				b->presumed.करोमुख्य = NOUVEAU_GEM_DOMAIN_VRAM;
			b->presumed.offset = nvbo->offset;
			b->presumed.valid = 0;
			relocs++;
		पूर्ण
	पूर्ण

	वापस relocs;
पूर्ण

अटल पूर्णांक
nouveau_gem_pushbuf_validate(काष्ठा nouveau_channel *chan,
			     काष्ठा drm_file *file_priv,
			     काष्ठा drm_nouveau_gem_pushbuf_bo *pbbo,
			     पूर्णांक nr_buffers,
			     काष्ठा validate_op *op, bool *apply_relocs)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(file_priv);
	पूर्णांक ret;

	INIT_LIST_HEAD(&op->list);

	अगर (nr_buffers == 0)
		वापस 0;

	ret = validate_init(chan, file_priv, pbbo, nr_buffers, op);
	अगर (unlikely(ret)) अणु
		अगर (ret != -ERESTARTSYS)
			NV_PRINTK(err, cli, "validate_init\n");
		वापस ret;
	पूर्ण

	ret = validate_list(chan, cli, &op->list, pbbo);
	अगर (unlikely(ret < 0)) अणु
		अगर (ret != -ERESTARTSYS)
			NV_PRINTK(err, cli, "validating bo list\n");
		validate_fini(op, chan, शून्य, शून्य);
		वापस ret;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		*apply_relocs = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
u_मुक्त(व्योम *addr)
अणु
	kvमुक्त(addr);
पूर्ण

अटल अंतरभूत व्योम *
u_स_नकलa(uपूर्णांक64_t user, अचिन्हित nmemb, अचिन्हित size)
अणु
	व्योम *mem;
	व्योम __user *userptr = (व्योम __क्रमce __user *)(uपूर्णांकptr_t)user;

	size *= nmemb;

	mem = kvदो_स्मृति(size, GFP_KERNEL);
	अगर (!mem)
		वापस ERR_PTR(-ENOMEM);

	अगर (copy_from_user(mem, userptr, size)) अणु
		u_मुक्त(mem);
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	वापस mem;
पूर्ण

अटल पूर्णांक
nouveau_gem_pushbuf_reloc_apply(काष्ठा nouveau_cli *cli,
				काष्ठा drm_nouveau_gem_pushbuf *req,
				काष्ठा drm_nouveau_gem_pushbuf_reloc *reloc,
				काष्ठा drm_nouveau_gem_pushbuf_bo *bo)
अणु
	पूर्णांक ret = 0;
	अचिन्हित i;

	क्रम (i = 0; i < req->nr_relocs; i++) अणु
		काष्ठा drm_nouveau_gem_pushbuf_reloc *r = &reloc[i];
		काष्ठा drm_nouveau_gem_pushbuf_bo *b;
		काष्ठा nouveau_bo *nvbo;
		uपूर्णांक32_t data;

		अगर (unlikely(r->bo_index >= req->nr_buffers)) अणु
			NV_PRINTK(err, cli, "reloc bo index invalid\n");
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		b = &bo[r->bo_index];
		अगर (b->presumed.valid)
			जारी;

		अगर (unlikely(r->reloc_bo_index >= req->nr_buffers)) अणु
			NV_PRINTK(err, cli, "reloc container bo index invalid\n");
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		nvbo = (व्योम *)(अचिन्हित दीर्घ)bo[r->reloc_bo_index].user_priv;

		अगर (unlikely(r->reloc_bo_offset + 4 >
			     nvbo->bo.mem.num_pages << PAGE_SHIFT)) अणु
			NV_PRINTK(err, cli, "reloc outside of bo\n");
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (!nvbo->kmap.भव) अणु
			ret = tपंचांग_bo_kmap(&nvbo->bo, 0, nvbo->bo.mem.num_pages,
					  &nvbo->kmap);
			अगर (ret) अणु
				NV_PRINTK(err, cli, "failed kmap for reloc\n");
				अवरोध;
			पूर्ण
			nvbo->validate_mapped = true;
		पूर्ण

		अगर (r->flags & NOUVEAU_GEM_RELOC_LOW)
			data = b->presumed.offset + r->data;
		अन्यथा
		अगर (r->flags & NOUVEAU_GEM_RELOC_HIGH)
			data = (b->presumed.offset + r->data) >> 32;
		अन्यथा
			data = r->data;

		अगर (r->flags & NOUVEAU_GEM_RELOC_OR) अणु
			अगर (b->presumed.करोमुख्य == NOUVEAU_GEM_DOMAIN_GART)
				data |= r->tor;
			अन्यथा
				data |= r->vor;
		पूर्ण

		ret = tपंचांग_bo_रुको(&nvbo->bo, false, false);
		अगर (ret) अणु
			NV_PRINTK(err, cli, "reloc wait_idle failed: %d\n", ret);
			अवरोध;
		पूर्ण

		nouveau_bo_wr32(nvbo, r->reloc_bo_offset >> 2, data);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
nouveau_gem_ioctl_pushbuf(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv)
अणु
	काष्ठा nouveau_abi16 *abi16 = nouveau_abi16_get(file_priv);
	काष्ठा nouveau_cli *cli = nouveau_cli(file_priv);
	काष्ठा nouveau_abi16_chan *temp;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा drm_nouveau_gem_pushbuf *req = data;
	काष्ठा drm_nouveau_gem_pushbuf_push *push;
	काष्ठा drm_nouveau_gem_pushbuf_reloc *reloc = शून्य;
	काष्ठा drm_nouveau_gem_pushbuf_bo *bo;
	काष्ठा nouveau_channel *chan = शून्य;
	काष्ठा validate_op op;
	काष्ठा nouveau_fence *fence = शून्य;
	पूर्णांक i, j, ret = 0;
	bool करो_reloc = false, sync = false;

	अगर (unlikely(!abi16))
		वापस -ENOMEM;

	list_क्रम_each_entry(temp, &abi16->channels, head) अणु
		अगर (temp->chan->chid == req->channel) अणु
			chan = temp->chan;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!chan)
		वापस nouveau_abi16_put(abi16, -ENOENT);
	अगर (unlikely(atomic_पढ़ो(&chan->समाप्तed)))
		वापस nouveau_abi16_put(abi16, -ENODEV);

	sync = req->vram_available & NOUVEAU_GEM_PUSHBUF_SYNC;

	req->vram_available = drm->gem.vram_available;
	req->gart_available = drm->gem.gart_available;
	अगर (unlikely(req->nr_push == 0))
		जाओ out_next;

	अगर (unlikely(req->nr_push > NOUVEAU_GEM_MAX_PUSH)) अणु
		NV_PRINTK(err, cli, "pushbuf push count exceeds limit: %d max %d\n",
			 req->nr_push, NOUVEAU_GEM_MAX_PUSH);
		वापस nouveau_abi16_put(abi16, -EINVAL);
	पूर्ण

	अगर (unlikely(req->nr_buffers > NOUVEAU_GEM_MAX_BUFFERS)) अणु
		NV_PRINTK(err, cli, "pushbuf bo count exceeds limit: %d max %d\n",
			 req->nr_buffers, NOUVEAU_GEM_MAX_BUFFERS);
		वापस nouveau_abi16_put(abi16, -EINVAL);
	पूर्ण

	अगर (unlikely(req->nr_relocs > NOUVEAU_GEM_MAX_RELOCS)) अणु
		NV_PRINTK(err, cli, "pushbuf reloc count exceeds limit: %d max %d\n",
			 req->nr_relocs, NOUVEAU_GEM_MAX_RELOCS);
		वापस nouveau_abi16_put(abi16, -EINVAL);
	पूर्ण

	push = u_स_नकलa(req->push, req->nr_push, माप(*push));
	अगर (IS_ERR(push))
		वापस nouveau_abi16_put(abi16, PTR_ERR(push));

	bo = u_स_नकलa(req->buffers, req->nr_buffers, माप(*bo));
	अगर (IS_ERR(bo)) अणु
		u_मुक्त(push);
		वापस nouveau_abi16_put(abi16, PTR_ERR(bo));
	पूर्ण

	/* Ensure all push buffers are on validate list */
	क्रम (i = 0; i < req->nr_push; i++) अणु
		अगर (push[i].bo_index >= req->nr_buffers) अणु
			NV_PRINTK(err, cli, "push %d buffer not in list\n", i);
			ret = -EINVAL;
			जाओ out_prevalid;
		पूर्ण
	पूर्ण

	/* Validate buffer list */
revalidate:
	ret = nouveau_gem_pushbuf_validate(chan, file_priv, bo,
					   req->nr_buffers, &op, &करो_reloc);
	अगर (ret) अणु
		अगर (ret != -ERESTARTSYS)
			NV_PRINTK(err, cli, "validate: %d\n", ret);
		जाओ out_prevalid;
	पूर्ण

	/* Apply any relocations that are required */
	अगर (करो_reloc) अणु
		अगर (!reloc) अणु
			validate_fini(&op, chan, शून्य, bo);
			reloc = u_स_नकलa(req->relocs, req->nr_relocs, माप(*reloc));
			अगर (IS_ERR(reloc)) अणु
				ret = PTR_ERR(reloc);
				जाओ out_prevalid;
			पूर्ण

			जाओ revalidate;
		पूर्ण

		ret = nouveau_gem_pushbuf_reloc_apply(cli, req, reloc, bo);
		अगर (ret) अणु
			NV_PRINTK(err, cli, "reloc apply: %d\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (chan->dma.ib_max) अणु
		ret = nouveau_dma_रुको(chan, req->nr_push + 1, 16);
		अगर (ret) अणु
			NV_PRINTK(err, cli, "nv50cal_space: %d\n", ret);
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < req->nr_push; i++) अणु
			काष्ठा nouveau_vma *vma = (व्योम *)(अचिन्हित दीर्घ)
				bo[push[i].bo_index].user_priv;

			nv50_dma_push(chan, vma->addr + push[i].offset,
				      push[i].length);
		पूर्ण
	पूर्ण अन्यथा
	अगर (drm->client.device.info.chipset >= 0x25) अणु
		ret = PUSH_WAIT(chan->chan.push, req->nr_push * 2);
		अगर (ret) अणु
			NV_PRINTK(err, cli, "cal_space: %d\n", ret);
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < req->nr_push; i++) अणु
			काष्ठा nouveau_bo *nvbo = (व्योम *)(अचिन्हित दीर्घ)
				bo[push[i].bo_index].user_priv;

			PUSH_CALL(chan->chan.push, nvbo->offset + push[i].offset);
			PUSH_DATA(chan->chan.push, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = PUSH_WAIT(chan->chan.push, req->nr_push * (2 + NOUVEAU_DMA_SKIPS));
		अगर (ret) अणु
			NV_PRINTK(err, cli, "jmp_space: %d\n", ret);
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < req->nr_push; i++) अणु
			काष्ठा nouveau_bo *nvbo = (व्योम *)(अचिन्हित दीर्घ)
				bo[push[i].bo_index].user_priv;
			uपूर्णांक32_t cmd;

			cmd = chan->push.addr + ((chan->dma.cur + 2) << 2);
			cmd |= 0x20000000;
			अगर (unlikely(cmd != req->suffix0)) अणु
				अगर (!nvbo->kmap.भव) अणु
					ret = tपंचांग_bo_kmap(&nvbo->bo, 0,
							  nvbo->bo.mem.
							  num_pages,
							  &nvbo->kmap);
					अगर (ret) अणु
						WIND_RING(chan);
						जाओ out;
					पूर्ण
					nvbo->validate_mapped = true;
				पूर्ण

				nouveau_bo_wr32(nvbo, (push[i].offset +
						push[i].length - 8) / 4, cmd);
			पूर्ण

			PUSH_JUMP(chan->chan.push, nvbo->offset + push[i].offset);
			PUSH_DATA(chan->chan.push, 0);
			क्रम (j = 0; j < NOUVEAU_DMA_SKIPS; j++)
				PUSH_DATA(chan->chan.push, 0);
		पूर्ण
	पूर्ण

	ret = nouveau_fence_new(chan, false, &fence);
	अगर (ret) अणु
		NV_PRINTK(err, cli, "error fencing pushbuf: %d\n", ret);
		WIND_RING(chan);
		जाओ out;
	पूर्ण

	अगर (sync) अणु
		अगर (!(ret = nouveau_fence_रुको(fence, false, false))) अणु
			अगर ((ret = dma_fence_get_status(&fence->base)) == 1)
				ret = 0;
		पूर्ण
	पूर्ण

out:
	validate_fini(&op, chan, fence, bo);
	nouveau_fence_unref(&fence);

	अगर (करो_reloc) अणु
		काष्ठा drm_nouveau_gem_pushbuf_bo __user *upbbo =
			u64_to_user_ptr(req->buffers);

		क्रम (i = 0; i < req->nr_buffers; i++) अणु
			अगर (bo[i].presumed.valid)
				जारी;

			अगर (copy_to_user(&upbbo[i].presumed, &bo[i].presumed,
					 माप(bo[i].presumed))) अणु
				ret = -EFAULT;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
out_prevalid:
	अगर (!IS_ERR(reloc))
		u_मुक्त(reloc);
	u_मुक्त(bo);
	u_मुक्त(push);

out_next:
	अगर (chan->dma.ib_max) अणु
		req->suffix0 = 0x00000000;
		req->suffix1 = 0x00000000;
	पूर्ण अन्यथा
	अगर (drm->client.device.info.chipset >= 0x25) अणु
		req->suffix0 = 0x00020000;
		req->suffix1 = 0x00000000;
	पूर्ण अन्यथा अणु
		req->suffix0 = 0x20000000 |
			      (chan->push.addr + ((chan->dma.cur + 2) << 2));
		req->suffix1 = 0x00000000;
	पूर्ण

	वापस nouveau_abi16_put(abi16, ret);
पूर्ण

पूर्णांक
nouveau_gem_ioctl_cpu_prep(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_nouveau_gem_cpu_prep *req = data;
	काष्ठा drm_gem_object *gem;
	काष्ठा nouveau_bo *nvbo;
	bool no_रुको = !!(req->flags & NOUVEAU_GEM_CPU_PREP_NOWAIT);
	bool ग_लिखो = !!(req->flags & NOUVEAU_GEM_CPU_PREP_WRITE);
	दीर्घ lret;
	पूर्णांक ret;

	gem = drm_gem_object_lookup(file_priv, req->handle);
	अगर (!gem)
		वापस -ENOENT;
	nvbo = nouveau_gem_object(gem);

	lret = dma_resv_रुको_समयout_rcu(nvbo->bo.base.resv, ग_लिखो, true,
						   no_रुको ? 0 : 30 * HZ);
	अगर (!lret)
		ret = -EBUSY;
	अन्यथा अगर (lret > 0)
		ret = 0;
	अन्यथा
		ret = lret;

	nouveau_bo_sync_क्रम_cpu(nvbo);
	drm_gem_object_put(gem);

	वापस ret;
पूर्ण

पूर्णांक
nouveau_gem_ioctl_cpu_fini(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_nouveau_gem_cpu_fini *req = data;
	काष्ठा drm_gem_object *gem;
	काष्ठा nouveau_bo *nvbo;

	gem = drm_gem_object_lookup(file_priv, req->handle);
	अगर (!gem)
		वापस -ENOENT;
	nvbo = nouveau_gem_object(gem);

	nouveau_bo_sync_क्रम_device(nvbo);
	drm_gem_object_put(gem);
	वापस 0;
पूर्ण

पूर्णांक
nouveau_gem_ioctl_info(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_nouveau_gem_info *req = data;
	काष्ठा drm_gem_object *gem;
	पूर्णांक ret;

	gem = drm_gem_object_lookup(file_priv, req->handle);
	अगर (!gem)
		वापस -ENOENT;

	ret = nouveau_gem_info(file_priv, gem, req);
	drm_gem_object_put(gem);
	वापस ret;
पूर्ण

