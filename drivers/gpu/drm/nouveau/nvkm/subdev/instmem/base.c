<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
 * Authors: Ben Skeggs
 */
#समावेश "priv.h"

#समावेश <subdev/bar.h>

/******************************************************************************
 * insपंचांगem object base implementation
 *****************************************************************************/
अटल व्योम
nvkm_instobj_load(काष्ठा nvkm_instobj *iobj)
अणु
	काष्ठा nvkm_memory *memory = &iobj->memory;
	स्थिर u64 size = nvkm_memory_size(memory);
	व्योम __iomem *map;
	पूर्णांक i;

	अगर (!(map = nvkm_kmap(memory))) अणु
		क्रम (i = 0; i < size; i += 4)
			nvkm_wo32(memory, i, iobj->suspend[i / 4]);
	पूर्ण अन्यथा अणु
		स_नकल_toio(map, iobj->suspend, size);
	पूर्ण
	nvkm_करोne(memory);

	kvमुक्त(iobj->suspend);
	iobj->suspend = शून्य;
पूर्ण

अटल पूर्णांक
nvkm_instobj_save(काष्ठा nvkm_instobj *iobj)
अणु
	काष्ठा nvkm_memory *memory = &iobj->memory;
	स्थिर u64 size = nvkm_memory_size(memory);
	व्योम __iomem *map;
	पूर्णांक i;

	iobj->suspend = kvदो_स्मृति(size, GFP_KERNEL);
	अगर (!iobj->suspend)
		वापस -ENOMEM;

	अगर (!(map = nvkm_kmap(memory))) अणु
		क्रम (i = 0; i < size; i += 4)
			iobj->suspend[i / 4] = nvkm_ro32(memory, i);
	पूर्ण अन्यथा अणु
		स_नकल_fromio(iobj->suspend, map, size);
	पूर्ण
	nvkm_करोne(memory);
	वापस 0;
पूर्ण

व्योम
nvkm_instobj_dtor(काष्ठा nvkm_insपंचांगem *imem, काष्ठा nvkm_instobj *iobj)
अणु
	spin_lock(&imem->lock);
	list_del(&iobj->head);
	spin_unlock(&imem->lock);
पूर्ण

व्योम
nvkm_instobj_ctor(स्थिर काष्ठा nvkm_memory_func *func,
		  काष्ठा nvkm_insपंचांगem *imem, काष्ठा nvkm_instobj *iobj)
अणु
	nvkm_memory_ctor(func, &iobj->memory);
	iobj->suspend = शून्य;
	spin_lock(&imem->lock);
	list_add_tail(&iobj->head, &imem->list);
	spin_unlock(&imem->lock);
पूर्ण

पूर्णांक
nvkm_instobj_new(काष्ठा nvkm_insपंचांगem *imem, u32 size, u32 align, bool zero,
		 काष्ठा nvkm_memory **pmemory)
अणु
	काष्ठा nvkm_subdev *subdev = &imem->subdev;
	काष्ठा nvkm_memory *memory = शून्य;
	u32 offset;
	पूर्णांक ret;

	ret = imem->func->memory_new(imem, size, align, zero, &memory);
	अगर (ret) अणु
		nvkm_error(subdev, "OOM: %08x %08x %d\n", size, align, ret);
		जाओ करोne;
	पूर्ण

	nvkm_trace(subdev, "new %08x %08x %d: %010llx %010llx\n", size, align,
		   zero, nvkm_memory_addr(memory), nvkm_memory_size(memory));

	अगर (!imem->func->zero && zero) अणु
		व्योम __iomem *map = nvkm_kmap(memory);
		अगर (unlikely(!map)) अणु
			क्रम (offset = 0; offset < size; offset += 4)
				nvkm_wo32(memory, offset, 0x00000000);
		पूर्ण अन्यथा अणु
			स_रखो_io(map, 0x00, size);
		पूर्ण
		nvkm_करोne(memory);
	पूर्ण

करोne:
	अगर (ret)
		nvkm_memory_unref(&memory);
	*pmemory = memory;
	वापस ret;
पूर्ण

/******************************************************************************
 * insपंचांगem subdev base implementation
 *****************************************************************************/

u32
nvkm_insपंचांगem_rd32(काष्ठा nvkm_insपंचांगem *imem, u32 addr)
अणु
	वापस imem->func->rd32(imem, addr);
पूर्ण

व्योम
nvkm_insपंचांगem_wr32(काष्ठा nvkm_insपंचांगem *imem, u32 addr, u32 data)
अणु
	वापस imem->func->wr32(imem, addr, data);
पूर्ण

व्योम
nvkm_insपंचांगem_boot(काष्ठा nvkm_insपंचांगem *imem)
अणु
	/* Separate bootstrapped objects from normal list, as we need
	 * to make sure they're accessed with the slowpath on suspend
	 * and resume.
	 */
	काष्ठा nvkm_instobj *iobj, *iपंचांगp;
	spin_lock(&imem->lock);
	list_क्रम_each_entry_safe(iobj, iपंचांगp, &imem->list, head) अणु
		list_move_tail(&iobj->head, &imem->boot);
	पूर्ण
	spin_unlock(&imem->lock);
पूर्ण

अटल पूर्णांक
nvkm_insपंचांगem_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	काष्ठा nvkm_insपंचांगem *imem = nvkm_insपंचांगem(subdev);
	काष्ठा nvkm_instobj *iobj;

	अगर (suspend) अणु
		list_क्रम_each_entry(iobj, &imem->list, head) अणु
			पूर्णांक ret = nvkm_instobj_save(iobj);
			अगर (ret)
				वापस ret;
		पूर्ण

		nvkm_bar_bar2_fini(subdev->device);

		list_क्रम_each_entry(iobj, &imem->boot, head) अणु
			पूर्णांक ret = nvkm_instobj_save(iobj);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (imem->func->fini)
		imem->func->fini(imem);

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_insपंचांगem_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_insपंचांगem *imem = nvkm_insपंचांगem(subdev);
	काष्ठा nvkm_instobj *iobj;

	list_क्रम_each_entry(iobj, &imem->boot, head) अणु
		अगर (iobj->suspend)
			nvkm_instobj_load(iobj);
	पूर्ण

	nvkm_bar_bar2_init(subdev->device);

	list_क्रम_each_entry(iobj, &imem->list, head) अणु
		अगर (iobj->suspend)
			nvkm_instobj_load(iobj);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_insपंचांगem_oneinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_insपंचांगem *imem = nvkm_insपंचांगem(subdev);
	अगर (imem->func->oneinit)
		वापस imem->func->oneinit(imem);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_insपंचांगem_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_insपंचांगem *imem = nvkm_insपंचांगem(subdev);
	व्योम *data = imem;
	अगर (imem->func->dtor)
		data = imem->func->dtor(imem);
	mutex_destroy(&imem->mutex);
	वापस data;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_insपंचांगem = अणु
	.dtor = nvkm_insपंचांगem_dtor,
	.oneinit = nvkm_insपंचांगem_oneinit,
	.init = nvkm_insपंचांगem_init,
	.fini = nvkm_insपंचांगem_fini,
पूर्ण;

व्योम
nvkm_insपंचांगem_ctor(स्थिर काष्ठा nvkm_insपंचांगem_func *func, काष्ठा nvkm_device *device,
		  क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_insपंचांगem *imem)
अणु
	nvkm_subdev_ctor(&nvkm_insपंचांगem, device, type, inst, &imem->subdev);
	imem->func = func;
	spin_lock_init(&imem->lock);
	INIT_LIST_HEAD(&imem->list);
	INIT_LIST_HEAD(&imem->boot);
	mutex_init(&imem->mutex);
पूर्ण
