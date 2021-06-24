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
#समावेश "nouveau_mem.h"
#समावेश "nouveau_drv.h"
#समावेश "nouveau_bo.h"

#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/अगर000a.h>
#समावेश <nvअगर/अगर500b.h>
#समावेश <nvअगर/अगर500d.h>
#समावेश <nvअगर/अगर900b.h>
#समावेश <nvअगर/अगर900d.h>

पूर्णांक
nouveau_mem_map(काष्ठा nouveau_mem *mem,
		काष्ठा nvअगर_vmm *vmm, काष्ठा nvअगर_vma *vma)
अणु
	जोड़ अणु
		काष्ठा nv50_vmm_map_v0 nv50;
		काष्ठा gf100_vmm_map_v0 gf100;
	पूर्ण args;
	u32 argc = 0;
	bool super;
	पूर्णांक ret;

	चयन (vmm->object.oclass) अणु
	हाल NVIF_CLASS_VMM_NV04:
		अवरोध;
	हाल NVIF_CLASS_VMM_NV50:
		args.nv50.version = 0;
		args.nv50.ro = 0;
		args.nv50.priv = 0;
		args.nv50.kind = mem->kind;
		args.nv50.comp = mem->comp;
		argc = माप(args.nv50);
		अवरोध;
	हाल NVIF_CLASS_VMM_GF100:
	हाल NVIF_CLASS_VMM_GM200:
	हाल NVIF_CLASS_VMM_GP100:
		args.gf100.version = 0;
		अगर (mem->mem.type & NVIF_MEM_VRAM)
			args.gf100.vol = 0;
		अन्यथा
			args.gf100.vol = 1;
		args.gf100.ro = 0;
		args.gf100.priv = 0;
		args.gf100.kind = mem->kind;
		argc = माप(args.gf100);
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -ENOSYS;
	पूर्ण

	super = vmm->object.client->super;
	vmm->object.client->super = true;
	ret = nvअगर_vmm_map(vmm, vma->addr, mem->mem.size, &args, argc,
			   &mem->mem, 0);
	vmm->object.client->super = super;
	वापस ret;
पूर्ण

व्योम
nouveau_mem_fini(काष्ठा nouveau_mem *mem)
अणु
	nvअगर_vmm_put(&mem->cli->drm->client.vmm.vmm, &mem->vma[1]);
	nvअगर_vmm_put(&mem->cli->drm->client.vmm.vmm, &mem->vma[0]);
	mutex_lock(&mem->cli->drm->master.lock);
	nvअगर_mem_dtor(&mem->mem);
	mutex_unlock(&mem->cli->drm->master.lock);
पूर्ण

पूर्णांक
nouveau_mem_host(काष्ठा tपंचांग_resource *reg, काष्ठा tपंचांग_tt *tt)
अणु
	काष्ठा nouveau_mem *mem = nouveau_mem(reg);
	काष्ठा nouveau_cli *cli = mem->cli;
	काष्ठा nouveau_drm *drm = cli->drm;
	काष्ठा nvअगर_mmu *mmu = &cli->mmu;
	काष्ठा nvअगर_mem_ram_v0 args = अणुपूर्ण;
	bool super = cli->base.super;
	u8 type;
	पूर्णांक ret;

	अगर (!nouveau_drm_use_coherent_gpu_mapping(drm))
		type = drm->tपंचांग.type_ncoh[!!mem->kind];
	अन्यथा
		type = drm->tपंचांग.type_host[0];

	अगर (mem->kind && !(mmu->type[type].type & NVIF_MEM_KIND))
		mem->comp = mem->kind = 0;
	अगर (mem->comp && !(mmu->type[type].type & NVIF_MEM_COMP)) अणु
		अगर (mmu->object.oclass >= NVIF_CLASS_MMU_GF100)
			mem->kind = mmu->kind[mem->kind];
		mem->comp = 0;
	पूर्ण

	अगर (tt->sg)
		args.sgl = tt->sg->sgl;
	अन्यथा
		args.dma = tt->dma_address;

	mutex_lock(&drm->master.lock);
	cli->base.super = true;
	ret = nvअगर_mem_ctor_type(mmu, "ttmHostMem", cli->mem->oclass, type, PAGE_SHIFT,
				 reg->num_pages << PAGE_SHIFT,
				 &args, माप(args), &mem->mem);
	cli->base.super = super;
	mutex_unlock(&drm->master.lock);
	वापस ret;
पूर्ण

पूर्णांक
nouveau_mem_vram(काष्ठा tपंचांग_resource *reg, bool contig, u8 page)
अणु
	काष्ठा nouveau_mem *mem = nouveau_mem(reg);
	काष्ठा nouveau_cli *cli = mem->cli;
	काष्ठा nouveau_drm *drm = cli->drm;
	काष्ठा nvअगर_mmu *mmu = &cli->mmu;
	bool super = cli->base.super;
	u64 size = ALIGN(reg->num_pages << PAGE_SHIFT, 1 << page);
	पूर्णांक ret;

	mutex_lock(&drm->master.lock);
	cli->base.super = true;
	चयन (cli->mem->oclass) अणु
	हाल NVIF_CLASS_MEM_GF100:
		ret = nvअगर_mem_ctor_type(mmu, "ttmVram", cli->mem->oclass,
					 drm->tपंचांग.type_vram, page, size,
					 &(काष्ठा gf100_mem_v0) अणु
						.contig = contig,
					 पूर्ण, माप(काष्ठा gf100_mem_v0),
					 &mem->mem);
		अवरोध;
	हाल NVIF_CLASS_MEM_NV50:
		ret = nvअगर_mem_ctor_type(mmu, "ttmVram", cli->mem->oclass,
					 drm->tपंचांग.type_vram, page, size,
					 &(काष्ठा nv50_mem_v0) अणु
						.bankswz = mmu->kind[mem->kind] == 2,
						.contig = contig,
					 पूर्ण, माप(काष्ठा nv50_mem_v0),
					 &mem->mem);
		अवरोध;
	शेष:
		ret = -ENOSYS;
		WARN_ON(1);
		अवरोध;
	पूर्ण
	cli->base.super = super;
	mutex_unlock(&drm->master.lock);

	reg->start = mem->mem.addr >> PAGE_SHIFT;
	वापस ret;
पूर्ण

व्योम
nouveau_mem_del(काष्ठा tपंचांग_resource *reg)
अणु
	काष्ठा nouveau_mem *mem = nouveau_mem(reg);
	अगर (!mem)
		वापस;
	nouveau_mem_fini(mem);
	kमुक्त(reg->mm_node);
	reg->mm_node = शून्य;
पूर्ण

पूर्णांक
nouveau_mem_new(काष्ठा nouveau_cli *cli, u8 kind, u8 comp,
		काष्ठा tपंचांग_resource *reg)
अणु
	काष्ठा nouveau_mem *mem;

	अगर (!(mem = kzalloc(माप(*mem), GFP_KERNEL)))
		वापस -ENOMEM;
	mem->cli = cli;
	mem->kind = kind;
	mem->comp = comp;

	reg->mm_node = mem;
	वापस 0;
पूर्ण
