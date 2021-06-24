<शैली गुरु>
/*
 * Copyright 2008 Jerome Glisse.
 * All Rights Reserved.
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
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Jerome Glisse <glisse@मुक्तdesktop.org>
 */

#समावेश <linux/list_sort.h>
#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon.h"
#समावेश "radeon_reg.h"
#समावेश "radeon_trace.h"

#घोषणा RADEON_CS_MAX_PRIORITY		32u
#घोषणा RADEON_CS_NUM_BUCKETS		(RADEON_CS_MAX_PRIORITY + 1)

/* This is based on the bucket sort with O(n) समय complनिकासy.
 * An item with priority "i" is added to bucket[i]. The lists are then
 * concatenated in descending order.
 */
काष्ठा radeon_cs_buckets अणु
	काष्ठा list_head bucket[RADEON_CS_NUM_BUCKETS];
पूर्ण;

अटल व्योम radeon_cs_buckets_init(काष्ठा radeon_cs_buckets *b)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < RADEON_CS_NUM_BUCKETS; i++)
		INIT_LIST_HEAD(&b->bucket[i]);
पूर्ण

अटल व्योम radeon_cs_buckets_add(काष्ठा radeon_cs_buckets *b,
				  काष्ठा list_head *item, अचिन्हित priority)
अणु
	/* Since buffers which appear sooner in the relocation list are
	 * likely to be used more often than buffers which appear later
	 * in the list, the sort mustn't change the ordering of buffers
	 * with the same priority, i.e. it must be stable.
	 */
	list_add_tail(item, &b->bucket[min(priority, RADEON_CS_MAX_PRIORITY)]);
पूर्ण

अटल व्योम radeon_cs_buckets_get_list(काष्ठा radeon_cs_buckets *b,
				       काष्ठा list_head *out_list)
अणु
	अचिन्हित i;

	/* Connect the sorted buckets in the output list. */
	क्रम (i = 0; i < RADEON_CS_NUM_BUCKETS; i++) अणु
		list_splice(&b->bucket[i], out_list);
	पूर्ण
पूर्ण

अटल पूर्णांक radeon_cs_parser_relocs(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा radeon_cs_chunk *chunk;
	काष्ठा radeon_cs_buckets buckets;
	अचिन्हित i;
	bool need_mmap_lock = false;
	पूर्णांक r;

	अगर (p->chunk_relocs == शून्य) अणु
		वापस 0;
	पूर्ण
	chunk = p->chunk_relocs;
	p->dma_reloc_idx = 0;
	/* FIXME: we assume that each relocs use 4 dwords */
	p->nrelocs = chunk->length_dw / 4;
	p->relocs = kvसुस्मृति(p->nrelocs, माप(काष्ठा radeon_bo_list),
			GFP_KERNEL);
	अगर (p->relocs == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण

	radeon_cs_buckets_init(&buckets);

	क्रम (i = 0; i < p->nrelocs; i++) अणु
		काष्ठा drm_radeon_cs_reloc *r;
		काष्ठा drm_gem_object *gobj;
		अचिन्हित priority;

		r = (काष्ठा drm_radeon_cs_reloc *)&chunk->kdata[i*4];
		gobj = drm_gem_object_lookup(p->filp, r->handle);
		अगर (gobj == शून्य) अणु
			DRM_ERROR("gem object lookup failed 0x%x\n",
				  r->handle);
			वापस -ENOENT;
		पूर्ण
		p->relocs[i].robj = gem_to_radeon_bo(gobj);

		/* The userspace buffer priorities are from 0 to 15. A higher
		 * number means the buffer is more important.
		 * Also, the buffers used क्रम ग_लिखो have a higher priority than
		 * the buffers used क्रम पढ़ो only, which द्विगुनs the range
		 * to 0 to 31. 32 is reserved क्रम the kernel driver.
		 */
		priority = (r->flags & RADEON_RELOC_PRIO_MASK) * 2
			   + !!r->ग_लिखो_करोमुख्य;

		/* The first reloc of an UVD job is the msg and that must be in
		 * VRAM, the second reloc is the DPB and क्रम WMV that must be in
		 * VRAM as well. Also put everything पूर्णांकo VRAM on AGP cards and older
		 * IGP chips to aव्योम image corruptions
		 */
		अगर (p->ring == R600_RING_TYPE_UVD_INDEX &&
		    (i <= 0 || pci_find_capability(p->rdev->pdev, PCI_CAP_ID_AGP) ||
		     p->rdev->family == CHIP_RS780 ||
		     p->rdev->family == CHIP_RS880)) अणु

			/* TODO: is this still needed क्रम NI+ ? */
			p->relocs[i].preferred_करोमुख्यs =
				RADEON_GEM_DOMAIN_VRAM;

			p->relocs[i].allowed_करोमुख्यs =
				RADEON_GEM_DOMAIN_VRAM;

			/* prioritize this over any other relocation */
			priority = RADEON_CS_MAX_PRIORITY;
		पूर्ण अन्यथा अणु
			uपूर्णांक32_t करोमुख्य = r->ग_लिखो_करोमुख्य ?
				r->ग_लिखो_करोमुख्य : r->पढ़ो_करोमुख्यs;

			अगर (करोमुख्य & RADEON_GEM_DOMAIN_CPU) अणु
				DRM_ERROR("RADEON_GEM_DOMAIN_CPU is not valid "
					  "for command submission\n");
				वापस -EINVAL;
			पूर्ण

			p->relocs[i].preferred_करोमुख्यs = करोमुख्य;
			अगर (करोमुख्य == RADEON_GEM_DOMAIN_VRAM)
				करोमुख्य |= RADEON_GEM_DOMAIN_GTT;
			p->relocs[i].allowed_करोमुख्यs = करोमुख्य;
		पूर्ण

		अगर (radeon_tपंचांग_tt_has_userptr(p->rdev, p->relocs[i].robj->tbo.tपंचांग)) अणु
			uपूर्णांक32_t करोमुख्य = p->relocs[i].preferred_करोमुख्यs;
			अगर (!(करोमुख्य & RADEON_GEM_DOMAIN_GTT)) अणु
				DRM_ERROR("Only RADEON_GEM_DOMAIN_GTT is "
					  "allowed for userptr BOs\n");
				वापस -EINVAL;
			पूर्ण
			need_mmap_lock = true;
			करोमुख्य = RADEON_GEM_DOMAIN_GTT;
			p->relocs[i].preferred_करोमुख्यs = करोमुख्य;
			p->relocs[i].allowed_करोमुख्यs = करोमुख्य;
		पूर्ण

		/* Objects shared as dma-bufs cannot be moved to VRAM */
		अगर (p->relocs[i].robj->prime_shared_count) अणु
			p->relocs[i].allowed_करोमुख्यs &= ~RADEON_GEM_DOMAIN_VRAM;
			अगर (!p->relocs[i].allowed_करोमुख्यs) अणु
				DRM_ERROR("BO associated with dma-buf cannot "
					  "be moved to VRAM\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		p->relocs[i].tv.bo = &p->relocs[i].robj->tbo;
		p->relocs[i].tv.num_shared = !r->ग_लिखो_करोमुख्य;

		radeon_cs_buckets_add(&buckets, &p->relocs[i].tv.head,
				      priority);
	पूर्ण

	radeon_cs_buckets_get_list(&buckets, &p->validated);

	अगर (p->cs_flags & RADEON_CS_USE_VM)
		p->vm_bos = radeon_vm_get_bos(p->rdev, p->ib.vm,
					      &p->validated);
	अगर (need_mmap_lock)
		mmap_पढ़ो_lock(current->mm);

	r = radeon_bo_list_validate(p->rdev, &p->ticket, &p->validated, p->ring);

	अगर (need_mmap_lock)
		mmap_पढ़ो_unlock(current->mm);

	वापस r;
पूर्ण

अटल पूर्णांक radeon_cs_get_ring(काष्ठा radeon_cs_parser *p, u32 ring, s32 priority)
अणु
	p->priority = priority;

	चयन (ring) अणु
	शेष:
		DRM_ERROR("unknown ring id: %d\n", ring);
		वापस -EINVAL;
	हाल RADEON_CS_RING_GFX:
		p->ring = RADEON_RING_TYPE_GFX_INDEX;
		अवरोध;
	हाल RADEON_CS_RING_COMPUTE:
		अगर (p->rdev->family >= CHIP_TAHITI) अणु
			अगर (p->priority > 0)
				p->ring = CAYMAN_RING_TYPE_CP1_INDEX;
			अन्यथा
				p->ring = CAYMAN_RING_TYPE_CP2_INDEX;
		पूर्ण अन्यथा
			p->ring = RADEON_RING_TYPE_GFX_INDEX;
		अवरोध;
	हाल RADEON_CS_RING_DMA:
		अगर (p->rdev->family >= CHIP_CAYMAN) अणु
			अगर (p->priority > 0)
				p->ring = R600_RING_TYPE_DMA_INDEX;
			अन्यथा
				p->ring = CAYMAN_RING_TYPE_DMA1_INDEX;
		पूर्ण अन्यथा अगर (p->rdev->family >= CHIP_RV770) अणु
			p->ring = R600_RING_TYPE_DMA_INDEX;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल RADEON_CS_RING_UVD:
		p->ring = R600_RING_TYPE_UVD_INDEX;
		अवरोध;
	हाल RADEON_CS_RING_VCE:
		/* TODO: only use the low priority ring क्रम now */
		p->ring = TN_RING_TYPE_VCE1_INDEX;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक radeon_cs_sync_rings(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा radeon_bo_list *reloc;
	पूर्णांक r;

	list_क्रम_each_entry(reloc, &p->validated, tv.head) अणु
		काष्ठा dma_resv *resv;

		resv = reloc->robj->tbo.base.resv;
		r = radeon_sync_resv(p->rdev, &p->ib.sync, resv,
				     reloc->tv.num_shared);
		अगर (r)
			वापस r;
	पूर्ण
	वापस 0;
पूर्ण

/* XXX: note that this is called from the legacy UMS CS ioctl as well */
पूर्णांक radeon_cs_parser_init(काष्ठा radeon_cs_parser *p, व्योम *data)
अणु
	काष्ठा drm_radeon_cs *cs = data;
	uपूर्णांक64_t *chunk_array_ptr;
	अचिन्हित size, i;
	u32 ring = RADEON_CS_RING_GFX;
	s32 priority = 0;

	INIT_LIST_HEAD(&p->validated);

	अगर (!cs->num_chunks) अणु
		वापस 0;
	पूर्ण

	/* get chunks */
	p->idx = 0;
	p->ib.sa_bo = शून्य;
	p->स्थिर_ib.sa_bo = शून्य;
	p->chunk_ib = शून्य;
	p->chunk_relocs = शून्य;
	p->chunk_flags = शून्य;
	p->chunk_स्थिर_ib = शून्य;
	p->chunks_array = kvदो_स्मृति_array(cs->num_chunks, माप(uपूर्णांक64_t), GFP_KERNEL);
	अगर (p->chunks_array == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण
	chunk_array_ptr = (uपूर्णांक64_t *)(अचिन्हित दीर्घ)(cs->chunks);
	अगर (copy_from_user(p->chunks_array, chunk_array_ptr,
			       माप(uपूर्णांक64_t)*cs->num_chunks)) अणु
		वापस -EFAULT;
	पूर्ण
	p->cs_flags = 0;
	p->nchunks = cs->num_chunks;
	p->chunks = kvसुस्मृति(p->nchunks, माप(काष्ठा radeon_cs_chunk), GFP_KERNEL);
	अगर (p->chunks == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < p->nchunks; i++) अणु
		काष्ठा drm_radeon_cs_chunk __user **chunk_ptr = शून्य;
		काष्ठा drm_radeon_cs_chunk user_chunk;
		uपूर्णांक32_t __user *cdata;

		chunk_ptr = (व्योम __user*)(अचिन्हित दीर्घ)p->chunks_array[i];
		अगर (copy_from_user(&user_chunk, chunk_ptr,
				       माप(काष्ठा drm_radeon_cs_chunk))) अणु
			वापस -EFAULT;
		पूर्ण
		p->chunks[i].length_dw = user_chunk.length_dw;
		अगर (user_chunk.chunk_id == RADEON_CHUNK_ID_RELOCS) अणु
			p->chunk_relocs = &p->chunks[i];
		पूर्ण
		अगर (user_chunk.chunk_id == RADEON_CHUNK_ID_IB) अणु
			p->chunk_ib = &p->chunks[i];
			/* zero length IB isn't useful */
			अगर (p->chunks[i].length_dw == 0)
				वापस -EINVAL;
		पूर्ण
		अगर (user_chunk.chunk_id == RADEON_CHUNK_ID_CONST_IB) अणु
			p->chunk_स्थिर_ib = &p->chunks[i];
			/* zero length CONST IB isn't useful */
			अगर (p->chunks[i].length_dw == 0)
				वापस -EINVAL;
		पूर्ण
		अगर (user_chunk.chunk_id == RADEON_CHUNK_ID_FLAGS) अणु
			p->chunk_flags = &p->chunks[i];
			/* zero length flags aren't useful */
			अगर (p->chunks[i].length_dw == 0)
				वापस -EINVAL;
		पूर्ण

		size = p->chunks[i].length_dw;
		cdata = (व्योम __user *)(अचिन्हित दीर्घ)user_chunk.chunk_data;
		p->chunks[i].user_ptr = cdata;
		अगर (user_chunk.chunk_id == RADEON_CHUNK_ID_CONST_IB)
			जारी;

		अगर (user_chunk.chunk_id == RADEON_CHUNK_ID_IB) अणु
			अगर (!p->rdev || !(p->rdev->flags & RADEON_IS_AGP))
				जारी;
		पूर्ण

		p->chunks[i].kdata = kvदो_स्मृति_array(size, माप(uपूर्णांक32_t), GFP_KERNEL);
		size *= माप(uपूर्णांक32_t);
		अगर (p->chunks[i].kdata == शून्य) अणु
			वापस -ENOMEM;
		पूर्ण
		अगर (copy_from_user(p->chunks[i].kdata, cdata, size)) अणु
			वापस -EFAULT;
		पूर्ण
		अगर (user_chunk.chunk_id == RADEON_CHUNK_ID_FLAGS) अणु
			p->cs_flags = p->chunks[i].kdata[0];
			अगर (p->chunks[i].length_dw > 1)
				ring = p->chunks[i].kdata[1];
			अगर (p->chunks[i].length_dw > 2)
				priority = (s32)p->chunks[i].kdata[2];
		पूर्ण
	पूर्ण

	/* these are KMS only */
	अगर (p->rdev) अणु
		अगर ((p->cs_flags & RADEON_CS_USE_VM) &&
		    !p->rdev->vm_manager.enabled) अणु
			DRM_ERROR("VM not active on asic!\n");
			वापस -EINVAL;
		पूर्ण

		अगर (radeon_cs_get_ring(p, ring, priority))
			वापस -EINVAL;

		/* we only support VM on some SI+ rings */
		अगर ((p->cs_flags & RADEON_CS_USE_VM) == 0) अणु
			अगर (p->rdev->asic->ring[p->ring]->cs_parse == शून्य) अणु
				DRM_ERROR("Ring %d requires VM!\n", p->ring);
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (p->rdev->asic->ring[p->ring]->ib_parse == शून्य) अणु
				DRM_ERROR("VM not supported on ring %d!\n",
					  p->ring);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cmp_size_smaller_first(व्योम *priv, स्थिर काष्ठा list_head *a,
				  स्थिर काष्ठा list_head *b)
अणु
	काष्ठा radeon_bo_list *la = list_entry(a, काष्ठा radeon_bo_list, tv.head);
	काष्ठा radeon_bo_list *lb = list_entry(b, काष्ठा radeon_bo_list, tv.head);

	/* Sort A beक्रमe B अगर A is smaller. */
	वापस (पूर्णांक)la->robj->tbo.mem.num_pages -
		(पूर्णांक)lb->robj->tbo.mem.num_pages;
पूर्ण

/**
 * cs_parser_fini() - clean parser states
 * @parser:	parser काष्ठाure holding parsing context.
 * @error:	error number
 * @backoff:	indicator to backoff the reservation
 *
 * If error is set than unvalidate buffer, otherwise just मुक्त memory
 * used by parsing context.
 **/
अटल व्योम radeon_cs_parser_fini(काष्ठा radeon_cs_parser *parser, पूर्णांक error, bool backoff)
अणु
	अचिन्हित i;

	अगर (!error) अणु
		/* Sort the buffer list from the smallest to largest buffer,
		 * which affects the order of buffers in the LRU list.
		 * This assures that the smallest buffers are added first
		 * to the LRU list, so they are likely to be later evicted
		 * first, instead of large buffers whose eviction is more
		 * expensive.
		 *
		 * This slightly lowers the number of bytes moved by TTM
		 * per frame under memory pressure.
		 */
		list_sort(शून्य, &parser->validated, cmp_size_smaller_first);

		tपंचांग_eu_fence_buffer_objects(&parser->ticket,
					    &parser->validated,
					    &parser->ib.fence->base);
	पूर्ण अन्यथा अगर (backoff) अणु
		tपंचांग_eu_backoff_reservation(&parser->ticket,
					   &parser->validated);
	पूर्ण

	अगर (parser->relocs != शून्य) अणु
		क्रम (i = 0; i < parser->nrelocs; i++) अणु
			काष्ठा radeon_bo *bo = parser->relocs[i].robj;
			अगर (bo == शून्य)
				जारी;

			drm_gem_object_put(&bo->tbo.base);
		पूर्ण
	पूर्ण
	kमुक्त(parser->track);
	kvमुक्त(parser->relocs);
	kvमुक्त(parser->vm_bos);
	क्रम (i = 0; i < parser->nchunks; i++)
		kvमुक्त(parser->chunks[i].kdata);
	kvमुक्त(parser->chunks);
	kvमुक्त(parser->chunks_array);
	radeon_ib_मुक्त(parser->rdev, &parser->ib);
	radeon_ib_मुक्त(parser->rdev, &parser->स्थिर_ib);
पूर्ण

अटल पूर्णांक radeon_cs_ib_chunk(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_cs_parser *parser)
अणु
	पूर्णांक r;

	अगर (parser->chunk_ib == शून्य)
		वापस 0;

	अगर (parser->cs_flags & RADEON_CS_USE_VM)
		वापस 0;

	r = radeon_cs_parse(rdev, parser->ring, parser);
	अगर (r || parser->parser_error) अणु
		DRM_ERROR("Invalid command stream !\n");
		वापस r;
	पूर्ण

	r = radeon_cs_sync_rings(parser);
	अगर (r) अणु
		अगर (r != -ERESTARTSYS)
			DRM_ERROR("Failed to sync rings: %i\n", r);
		वापस r;
	पूर्ण

	अगर (parser->ring == R600_RING_TYPE_UVD_INDEX)
		radeon_uvd_note_usage(rdev);
	अन्यथा अगर ((parser->ring == TN_RING_TYPE_VCE1_INDEX) ||
		 (parser->ring == TN_RING_TYPE_VCE2_INDEX))
		radeon_vce_note_usage(rdev);

	r = radeon_ib_schedule(rdev, &parser->ib, शून्य, true);
	अगर (r) अणु
		DRM_ERROR("Failed to schedule IB !\n");
	पूर्ण
	वापस r;
पूर्ण

अटल पूर्णांक radeon_bo_vm_update_pte(काष्ठा radeon_cs_parser *p,
				   काष्ठा radeon_vm *vm)
अणु
	काष्ठा radeon_device *rdev = p->rdev;
	काष्ठा radeon_bo_va *bo_va;
	पूर्णांक i, r;

	r = radeon_vm_update_page_directory(rdev, vm);
	अगर (r)
		वापस r;

	r = radeon_vm_clear_मुक्तd(rdev, vm);
	अगर (r)
		वापस r;

	अगर (vm->ib_bo_va == शून्य) अणु
		DRM_ERROR("Tmp BO not in VM!\n");
		वापस -EINVAL;
	पूर्ण

	r = radeon_vm_bo_update(rdev, vm->ib_bo_va,
				&rdev->ring_पंचांगp_bo.bo->tbo.mem);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < p->nrelocs; i++) अणु
		काष्ठा radeon_bo *bo;

		bo = p->relocs[i].robj;
		bo_va = radeon_vm_bo_find(vm, bo);
		अगर (bo_va == शून्य) अणु
			dev_err(rdev->dev, "bo %p not in vm %p\n", bo, vm);
			वापस -EINVAL;
		पूर्ण

		r = radeon_vm_bo_update(rdev, bo_va, &bo->tbo.mem);
		अगर (r)
			वापस r;

		radeon_sync_fence(&p->ib.sync, bo_va->last_pt_update);
	पूर्ण

	वापस radeon_vm_clear_invalids(rdev, vm);
पूर्ण

अटल पूर्णांक radeon_cs_ib_vm_chunk(काष्ठा radeon_device *rdev,
				 काष्ठा radeon_cs_parser *parser)
अणु
	काष्ठा radeon_fpriv *fpriv = parser->filp->driver_priv;
	काष्ठा radeon_vm *vm = &fpriv->vm;
	पूर्णांक r;

	अगर (parser->chunk_ib == शून्य)
		वापस 0;
	अगर ((parser->cs_flags & RADEON_CS_USE_VM) == 0)
		वापस 0;

	अगर (parser->स्थिर_ib.length_dw) अणु
		r = radeon_ring_ib_parse(rdev, parser->ring, &parser->स्थिर_ib);
		अगर (r) अणु
			वापस r;
		पूर्ण
	पूर्ण

	r = radeon_ring_ib_parse(rdev, parser->ring, &parser->ib);
	अगर (r) अणु
		वापस r;
	पूर्ण

	अगर (parser->ring == R600_RING_TYPE_UVD_INDEX)
		radeon_uvd_note_usage(rdev);

	mutex_lock(&vm->mutex);
	r = radeon_bo_vm_update_pte(parser, vm);
	अगर (r) अणु
		जाओ out;
	पूर्ण

	r = radeon_cs_sync_rings(parser);
	अगर (r) अणु
		अगर (r != -ERESTARTSYS)
			DRM_ERROR("Failed to sync rings: %i\n", r);
		जाओ out;
	पूर्ण

	अगर ((rdev->family >= CHIP_TAHITI) &&
	    (parser->chunk_स्थिर_ib != शून्य)) अणु
		r = radeon_ib_schedule(rdev, &parser->ib, &parser->स्थिर_ib, true);
	पूर्ण अन्यथा अणु
		r = radeon_ib_schedule(rdev, &parser->ib, शून्य, true);
	पूर्ण

out:
	mutex_unlock(&vm->mutex);
	वापस r;
पूर्ण

अटल पूर्णांक radeon_cs_handle_lockup(काष्ठा radeon_device *rdev, पूर्णांक r)
अणु
	अगर (r == -EDEADLK) अणु
		r = radeon_gpu_reset(rdev);
		अगर (!r)
			r = -EAGAIN;
	पूर्ण
	वापस r;
पूर्ण

अटल पूर्णांक radeon_cs_ib_fill(काष्ठा radeon_device *rdev, काष्ठा radeon_cs_parser *parser)
अणु
	काष्ठा radeon_cs_chunk *ib_chunk;
	काष्ठा radeon_vm *vm = शून्य;
	पूर्णांक r;

	अगर (parser->chunk_ib == शून्य)
		वापस 0;

	अगर (parser->cs_flags & RADEON_CS_USE_VM) अणु
		काष्ठा radeon_fpriv *fpriv = parser->filp->driver_priv;
		vm = &fpriv->vm;

		अगर ((rdev->family >= CHIP_TAHITI) &&
		    (parser->chunk_स्थिर_ib != शून्य)) अणु
			ib_chunk = parser->chunk_स्थिर_ib;
			अगर (ib_chunk->length_dw > RADEON_IB_VM_MAX_SIZE) अणु
				DRM_ERROR("cs IB CONST too big: %d\n", ib_chunk->length_dw);
				वापस -EINVAL;
			पूर्ण
			r =  radeon_ib_get(rdev, parser->ring, &parser->स्थिर_ib,
					   vm, ib_chunk->length_dw * 4);
			अगर (r) अणु
				DRM_ERROR("Failed to get const ib !\n");
				वापस r;
			पूर्ण
			parser->स्थिर_ib.is_स्थिर_ib = true;
			parser->स्थिर_ib.length_dw = ib_chunk->length_dw;
			अगर (copy_from_user(parser->स्थिर_ib.ptr,
					       ib_chunk->user_ptr,
					       ib_chunk->length_dw * 4))
				वापस -EFAULT;
		पूर्ण

		ib_chunk = parser->chunk_ib;
		अगर (ib_chunk->length_dw > RADEON_IB_VM_MAX_SIZE) अणु
			DRM_ERROR("cs IB too big: %d\n", ib_chunk->length_dw);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	ib_chunk = parser->chunk_ib;

	r =  radeon_ib_get(rdev, parser->ring, &parser->ib,
			   vm, ib_chunk->length_dw * 4);
	अगर (r) अणु
		DRM_ERROR("Failed to get ib !\n");
		वापस r;
	पूर्ण
	parser->ib.length_dw = ib_chunk->length_dw;
	अगर (ib_chunk->kdata)
		स_नकल(parser->ib.ptr, ib_chunk->kdata, ib_chunk->length_dw * 4);
	अन्यथा अगर (copy_from_user(parser->ib.ptr, ib_chunk->user_ptr, ib_chunk->length_dw * 4))
		वापस -EFAULT;
	वापस 0;
पूर्ण

पूर्णांक radeon_cs_ioctl(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *filp)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_cs_parser parser;
	पूर्णांक r;

	करोwn_पढ़ो(&rdev->exclusive_lock);
	अगर (!rdev->accel_working) अणु
		up_पढ़ो(&rdev->exclusive_lock);
		वापस -EBUSY;
	पूर्ण
	अगर (rdev->in_reset) अणु
		up_पढ़ो(&rdev->exclusive_lock);
		r = radeon_gpu_reset(rdev);
		अगर (!r)
			r = -EAGAIN;
		वापस r;
	पूर्ण
	/* initialize parser */
	स_रखो(&parser, 0, माप(काष्ठा radeon_cs_parser));
	parser.filp = filp;
	parser.rdev = rdev;
	parser.dev = rdev->dev;
	parser.family = rdev->family;
	r = radeon_cs_parser_init(&parser, data);
	अगर (r) अणु
		DRM_ERROR("Failed to initialize parser !\n");
		radeon_cs_parser_fini(&parser, r, false);
		up_पढ़ो(&rdev->exclusive_lock);
		r = radeon_cs_handle_lockup(rdev, r);
		वापस r;
	पूर्ण

	r = radeon_cs_ib_fill(rdev, &parser);
	अगर (!r) अणु
		r = radeon_cs_parser_relocs(&parser);
		अगर (r && r != -ERESTARTSYS)
			DRM_ERROR("Failed to parse relocation %d!\n", r);
	पूर्ण

	अगर (r) अणु
		radeon_cs_parser_fini(&parser, r, false);
		up_पढ़ो(&rdev->exclusive_lock);
		r = radeon_cs_handle_lockup(rdev, r);
		वापस r;
	पूर्ण

	trace_radeon_cs(&parser);

	r = radeon_cs_ib_chunk(rdev, &parser);
	अगर (r) अणु
		जाओ out;
	पूर्ण
	r = radeon_cs_ib_vm_chunk(rdev, &parser);
	अगर (r) अणु
		जाओ out;
	पूर्ण
out:
	radeon_cs_parser_fini(&parser, r, true);
	up_पढ़ो(&rdev->exclusive_lock);
	r = radeon_cs_handle_lockup(rdev, r);
	वापस r;
पूर्ण

/**
 * radeon_cs_packet_parse() - parse cp packet and poपूर्णांक ib index to next packet
 * @p:		parser काष्ठाure holding parsing context.
 * @pkt:	where to store packet inक्रमmation
 * @idx:	packet index
 *
 * Assume that chunk_ib_index is properly set. Will वापस -EINVAL
 * अगर packet is bigger than reमुख्यing ib size. or अगर packets is unknown.
 **/
पूर्णांक radeon_cs_packet_parse(काष्ठा radeon_cs_parser *p,
			   काष्ठा radeon_cs_packet *pkt,
			   अचिन्हित idx)
अणु
	काष्ठा radeon_cs_chunk *ib_chunk = p->chunk_ib;
	काष्ठा radeon_device *rdev = p->rdev;
	uपूर्णांक32_t header;
	पूर्णांक ret = 0, i;

	अगर (idx >= ib_chunk->length_dw) अणु
		DRM_ERROR("Can not parse packet at %d after CS end %d !\n",
			  idx, ib_chunk->length_dw);
		वापस -EINVAL;
	पूर्ण
	header = radeon_get_ib_value(p, idx);
	pkt->idx = idx;
	pkt->type = RADEON_CP_PACKET_GET_TYPE(header);
	pkt->count = RADEON_CP_PACKET_GET_COUNT(header);
	pkt->one_reg_wr = 0;
	चयन (pkt->type) अणु
	हाल RADEON_PACKET_TYPE0:
		अगर (rdev->family < CHIP_R600) अणु
			pkt->reg = R100_CP_PACKET0_GET_REG(header);
			pkt->one_reg_wr =
				RADEON_CP_PACKET0_GET_ONE_REG_WR(header);
		पूर्ण अन्यथा
			pkt->reg = R600_CP_PACKET0_GET_REG(header);
		अवरोध;
	हाल RADEON_PACKET_TYPE3:
		pkt->opcode = RADEON_CP_PACKET3_GET_OPCODE(header);
		अवरोध;
	हाल RADEON_PACKET_TYPE2:
		pkt->count = -1;
		अवरोध;
	शेष:
		DRM_ERROR("Unknown packet type %d at %d !\n", pkt->type, idx);
		ret = -EINVAL;
		जाओ dump_ib;
	पूर्ण
	अगर ((pkt->count + 1 + pkt->idx) >= ib_chunk->length_dw) अणु
		DRM_ERROR("Packet (%d:%d:%d) end after CS buffer (%d) !\n",
			  pkt->idx, pkt->type, pkt->count, ib_chunk->length_dw);
		ret = -EINVAL;
		जाओ dump_ib;
	पूर्ण
	वापस 0;

dump_ib:
	क्रम (i = 0; i < ib_chunk->length_dw; i++) अणु
		अगर (i == idx)
			prपूर्णांकk("\t0x%08x <---\n", radeon_get_ib_value(p, i));
		अन्यथा
			prपूर्णांकk("\t0x%08x\n", radeon_get_ib_value(p, i));
	पूर्ण
	वापस ret;
पूर्ण

/**
 * radeon_cs_packet_next_is_pkt3_nop() - test अगर the next packet is P3 NOP
 * @p:		काष्ठाure holding the parser context.
 *
 * Check अगर the next packet is NOP relocation packet3.
 **/
bool radeon_cs_packet_next_is_pkt3_nop(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा radeon_cs_packet p3reloc;
	पूर्णांक r;

	r = radeon_cs_packet_parse(p, &p3reloc, p->idx);
	अगर (r)
		वापस false;
	अगर (p3reloc.type != RADEON_PACKET_TYPE3)
		वापस false;
	अगर (p3reloc.opcode != RADEON_PACKET3_NOP)
		वापस false;
	वापस true;
पूर्ण

/**
 * radeon_cs_dump_packet() - dump raw packet context
 * @p:		काष्ठाure holding the parser context.
 * @pkt:	काष्ठाure holding the packet.
 *
 * Used mostly क्रम debugging and error reporting.
 **/
व्योम radeon_cs_dump_packet(काष्ठा radeon_cs_parser *p,
			   काष्ठा radeon_cs_packet *pkt)
अणु
	अस्थिर uपूर्णांक32_t *ib;
	अचिन्हित i;
	अचिन्हित idx;

	ib = p->ib.ptr;
	idx = pkt->idx;
	क्रम (i = 0; i <= (pkt->count + 1); i++, idx++)
		DRM_INFO("ib[%d]=0x%08X\n", idx, ib[idx]);
पूर्ण

/**
 * radeon_cs_packet_next_reloc() - parse next (should be reloc) packet
 * @p:			parser काष्ठाure holding parsing context.
 * @cs_reloc:		reloc inक्रमmations
 * @nomm:		no memory management क्रम debugging
 *
 * Check अगर next packet is relocation packet3, करो bo validation and compute
 * GPU offset using the provided start.
 **/
पूर्णांक radeon_cs_packet_next_reloc(काष्ठा radeon_cs_parser *p,
				काष्ठा radeon_bo_list **cs_reloc,
				पूर्णांक nomm)
अणु
	काष्ठा radeon_cs_chunk *relocs_chunk;
	काष्ठा radeon_cs_packet p3reloc;
	अचिन्हित idx;
	पूर्णांक r;

	अगर (p->chunk_relocs == शून्य) अणु
		DRM_ERROR("No relocation chunk !\n");
		वापस -EINVAL;
	पूर्ण
	*cs_reloc = शून्य;
	relocs_chunk = p->chunk_relocs;
	r = radeon_cs_packet_parse(p, &p3reloc, p->idx);
	अगर (r)
		वापस r;
	p->idx += p3reloc.count + 2;
	अगर (p3reloc.type != RADEON_PACKET_TYPE3 ||
	    p3reloc.opcode != RADEON_PACKET3_NOP) अणु
		DRM_ERROR("No packet3 for relocation for packet at %d.\n",
			  p3reloc.idx);
		radeon_cs_dump_packet(p, &p3reloc);
		वापस -EINVAL;
	पूर्ण
	idx = radeon_get_ib_value(p, p3reloc.idx + 1);
	अगर (idx >= relocs_chunk->length_dw) अणु
		DRM_ERROR("Relocs at %d after relocations chunk end %d !\n",
			  idx, relocs_chunk->length_dw);
		radeon_cs_dump_packet(p, &p3reloc);
		वापस -EINVAL;
	पूर्ण
	/* FIXME: we assume reloc size is 4 dwords */
	अगर (nomm) अणु
		*cs_reloc = p->relocs;
		(*cs_reloc)->gpu_offset =
			(u64)relocs_chunk->kdata[idx + 3] << 32;
		(*cs_reloc)->gpu_offset |= relocs_chunk->kdata[idx + 0];
	पूर्ण अन्यथा
		*cs_reloc = &p->relocs[(idx / 4)];
	वापस 0;
पूर्ण
