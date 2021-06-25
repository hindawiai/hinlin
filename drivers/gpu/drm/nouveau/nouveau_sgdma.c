<शैली गुरु>
// SPDX-License-Identअगरier: MIT
#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_mem.h"
#समावेश "nouveau_ttm.h"
#समावेश "nouveau_bo.h"

काष्ठा nouveau_sgdma_be अणु
	/* this has to be the first field so populate/unpopulated in
	 * nouve_bo.c works properly, otherwise have to move them here
	 */
	काष्ठा tपंचांग_tt tपंचांग;
	काष्ठा nouveau_mem *mem;
पूर्ण;

व्योम
nouveau_sgdma_destroy(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा nouveau_sgdma_be *nvbe = (काष्ठा nouveau_sgdma_be *)tपंचांग;

	अगर (tपंचांग) अणु
		nouveau_sgdma_unbind(bdev, tपंचांग);
		tपंचांग_tt_destroy_common(bdev, tपंचांग);
		tपंचांग_tt_fini(&nvbe->tपंचांग);
		kमुक्त(nvbe);
	पूर्ण
पूर्ण

पूर्णांक
nouveau_sgdma_bind(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग, काष्ठा tपंचांग_resource *reg)
अणु
	काष्ठा nouveau_sgdma_be *nvbe = (काष्ठा nouveau_sgdma_be *)tपंचांग;
	काष्ठा nouveau_drm *drm = nouveau_bdev(bdev);
	काष्ठा nouveau_mem *mem = nouveau_mem(reg);
	पूर्णांक ret;

	अगर (nvbe->mem)
		वापस 0;

	ret = nouveau_mem_host(reg, &nvbe->tपंचांग);
	अगर (ret)
		वापस ret;

	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA) अणु
		ret = nouveau_mem_map(mem, &mem->cli->vmm.vmm, &mem->vma[0]);
		अगर (ret) अणु
			nouveau_mem_fini(mem);
			वापस ret;
		पूर्ण
	पूर्ण

	nvbe->mem = mem;
	वापस 0;
पूर्ण

व्योम
nouveau_sgdma_unbind(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा nouveau_sgdma_be *nvbe = (काष्ठा nouveau_sgdma_be *)tपंचांग;
	अगर (nvbe->mem) अणु
		nouveau_mem_fini(nvbe->mem);
		nvbe->mem = शून्य;
	पूर्ण
पूर्ण

काष्ठा tपंचांग_tt *
nouveau_sgdma_create_tपंचांग(काष्ठा tपंचांग_buffer_object *bo, uपूर्णांक32_t page_flags)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(bo->bdev);
	काष्ठा nouveau_bo *nvbo = nouveau_bo(bo);
	काष्ठा nouveau_sgdma_be *nvbe;
	क्रमागत tपंचांग_caching caching;

	अगर (nvbo->क्रमce_coherent)
		caching = tपंचांग_uncached;
	अन्यथा अगर (drm->agp.bridge)
		caching = tपंचांग_ग_लिखो_combined;
	अन्यथा
		caching = tपंचांग_cached;

	nvbe = kzalloc(माप(*nvbe), GFP_KERNEL);
	अगर (!nvbe)
		वापस शून्य;

	अगर (tपंचांग_sg_tt_init(&nvbe->tपंचांग, bo, page_flags, caching)) अणु
		kमुक्त(nvbe);
		वापस शून्य;
	पूर्ण
	वापस &nvbe->tपंचांग;
पूर्ण
