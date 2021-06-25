<शैली गुरु>
/*
 * Copyright 2017 Red Hat Inc.
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
 */
#समावेश "nouveau_vmm.h"
#समावेश "nouveau_drv.h"
#समावेश "nouveau_bo.h"
#समावेश "nouveau_svm.h"
#समावेश "nouveau_mem.h"

व्योम
nouveau_vma_unmap(काष्ठा nouveau_vma *vma)
अणु
	अगर (vma->mem) अणु
		nvअगर_vmm_unmap(&vma->vmm->vmm, vma->addr);
		vma->mem = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nouveau_vma_map(काष्ठा nouveau_vma *vma, काष्ठा nouveau_mem *mem)
अणु
	काष्ठा nvअगर_vma पंचांगp = अणु .addr = vma->addr पूर्ण;
	पूर्णांक ret = nouveau_mem_map(mem, &vma->vmm->vmm, &पंचांगp);
	अगर (ret)
		वापस ret;
	vma->mem = mem;
	वापस 0;
पूर्ण

काष्ठा nouveau_vma *
nouveau_vma_find(काष्ठा nouveau_bo *nvbo, काष्ठा nouveau_vmm *vmm)
अणु
	काष्ठा nouveau_vma *vma;

	list_क्रम_each_entry(vma, &nvbo->vma_list, head) अणु
		अगर (vma->vmm == vmm)
			वापस vma;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम
nouveau_vma_del(काष्ठा nouveau_vma **pvma)
अणु
	काष्ठा nouveau_vma *vma = *pvma;
	अगर (vma && --vma->refs <= 0) अणु
		अगर (likely(vma->addr != ~0ULL)) अणु
			काष्ठा nvअगर_vma पंचांगp = अणु .addr = vma->addr, .size = 1 पूर्ण;
			nvअगर_vmm_put(&vma->vmm->vmm, &पंचांगp);
		पूर्ण
		list_del(&vma->head);
		kमुक्त(*pvma);
	पूर्ण
	*pvma = शून्य;
पूर्ण

पूर्णांक
nouveau_vma_new(काष्ठा nouveau_bo *nvbo, काष्ठा nouveau_vmm *vmm,
		काष्ठा nouveau_vma **pvma)
अणु
	काष्ठा nouveau_mem *mem = nouveau_mem(&nvbo->bo.mem);
	काष्ठा nouveau_vma *vma;
	काष्ठा nvअगर_vma पंचांगp;
	पूर्णांक ret;

	अगर ((vma = *pvma = nouveau_vma_find(nvbo, vmm))) अणु
		vma->refs++;
		वापस 0;
	पूर्ण

	अगर (!(vma = *pvma = kदो_स्मृति(माप(*vma), GFP_KERNEL)))
		वापस -ENOMEM;
	vma->vmm = vmm;
	vma->refs = 1;
	vma->addr = ~0ULL;
	vma->mem = शून्य;
	vma->fence = शून्य;
	list_add_tail(&vma->head, &nvbo->vma_list);

	अगर (nvbo->bo.mem.mem_type != TTM_PL_SYSTEM &&
	    mem->mem.page == nvbo->page) अणु
		ret = nvअगर_vmm_get(&vmm->vmm, LAZY, false, mem->mem.page, 0,
				   mem->mem.size, &पंचांगp);
		अगर (ret)
			जाओ करोne;

		vma->addr = पंचांगp.addr;
		ret = nouveau_vma_map(vma, mem);
	पूर्ण अन्यथा अणु
		ret = nvअगर_vmm_get(&vmm->vmm, PTES, false, mem->mem.page, 0,
				   mem->mem.size, &पंचांगp);
		vma->addr = पंचांगp.addr;
	पूर्ण

करोne:
	अगर (ret)
		nouveau_vma_del(pvma);
	वापस ret;
पूर्ण

व्योम
nouveau_vmm_fini(काष्ठा nouveau_vmm *vmm)
अणु
	nouveau_svmm_fini(&vmm->svmm);
	nvअगर_vmm_dtor(&vmm->vmm);
	vmm->cli = शून्य;
पूर्ण

पूर्णांक
nouveau_vmm_init(काष्ठा nouveau_cli *cli, s32 oclass, काष्ठा nouveau_vmm *vmm)
अणु
	पूर्णांक ret = nvअगर_vmm_ctor(&cli->mmu, "drmVmm", oclass, false, PAGE_SIZE,
				0, शून्य, 0, &vmm->vmm);
	अगर (ret)
		वापस ret;

	vmm->cli = cli;
	वापस 0;
पूर्ण
