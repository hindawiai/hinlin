<शैली गुरु>
/*
 * Copyright 2015 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश <core/memory.h>
#समावेश <core/mm.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/insपंचांगem.h>

व्योम
nvkm_memory_tags_put(काष्ठा nvkm_memory *memory, काष्ठा nvkm_device *device,
		     काष्ठा nvkm_tags **ptags)
अणु
	काष्ठा nvkm_fb *fb = device->fb;
	काष्ठा nvkm_tags *tags = *ptags;
	अगर (tags) अणु
		mutex_lock(&fb->tags.mutex);
		अगर (refcount_dec_and_test(&tags->refcount)) अणु
			nvkm_mm_मुक्त(&fb->tags.mm, &tags->mn);
			kमुक्त(memory->tags);
			memory->tags = शून्य;
		पूर्ण
		mutex_unlock(&fb->tags.mutex);
		*ptags = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvkm_memory_tags_get(काष्ठा nvkm_memory *memory, काष्ठा nvkm_device *device,
		     u32 nr, व्योम (*clr)(काष्ठा nvkm_device *, u32, u32),
		     काष्ठा nvkm_tags **ptags)
अणु
	काष्ठा nvkm_fb *fb = device->fb;
	काष्ठा nvkm_tags *tags;

	mutex_lock(&fb->tags.mutex);
	अगर ((tags = memory->tags)) अणु
		/* If comptags exist क्रम the memory, but a dअगरferent amount
		 * than requested, the buffer is being mapped with settings
		 * that are incompatible with existing mappings.
		 */
		अगर (tags->mn && tags->mn->length != nr) अणु
			mutex_unlock(&fb->tags.mutex);
			वापस -EINVAL;
		पूर्ण

		refcount_inc(&tags->refcount);
		mutex_unlock(&fb->tags.mutex);
		*ptags = tags;
		वापस 0;
	पूर्ण

	अगर (!(tags = kदो_स्मृति(माप(*tags), GFP_KERNEL))) अणु
		mutex_unlock(&fb->tags.mutex);
		वापस -ENOMEM;
	पूर्ण

	अगर (!nvkm_mm_head(&fb->tags.mm, 0, 1, nr, nr, 1, &tags->mn)) अणु
		अगर (clr)
			clr(device, tags->mn->offset, tags->mn->length);
	पूर्ण अन्यथा अणु
		/* Failure to allocate HW comptags is not an error, the
		 * caller should fall back to an uncompressed map.
		 *
		 * As memory can be mapped in multiple places, we still
		 * need to track the allocation failure and ensure that
		 * any additional mappings reमुख्य uncompressed.
		 *
		 * This is handled by वापसing an empty nvkm_tags.
		 */
		tags->mn = शून्य;
	पूर्ण

	refcount_set(&tags->refcount, 1);
	*ptags = memory->tags = tags;
	mutex_unlock(&fb->tags.mutex);
	वापस 0;
पूर्ण

व्योम
nvkm_memory_ctor(स्थिर काष्ठा nvkm_memory_func *func,
		 काष्ठा nvkm_memory *memory)
अणु
	memory->func = func;
	kref_init(&memory->kref);
पूर्ण

अटल व्योम
nvkm_memory_del(काष्ठा kref *kref)
अणु
	काष्ठा nvkm_memory *memory = container_of(kref, typeof(*memory), kref);
	अगर (!WARN_ON(!memory->func)) अणु
		अगर (memory->func->dtor)
			memory = memory->func->dtor(memory);
		kमुक्त(memory);
	पूर्ण
पूर्ण

व्योम
nvkm_memory_unref(काष्ठा nvkm_memory **pmemory)
अणु
	काष्ठा nvkm_memory *memory = *pmemory;
	अगर (memory) अणु
		kref_put(&memory->kref, nvkm_memory_del);
		*pmemory = शून्य;
	पूर्ण
पूर्ण

काष्ठा nvkm_memory *
nvkm_memory_ref(काष्ठा nvkm_memory *memory)
अणु
	अगर (memory)
		kref_get(&memory->kref);
	वापस memory;
पूर्ण

पूर्णांक
nvkm_memory_new(काष्ठा nvkm_device *device, क्रमागत nvkm_memory_target target,
		u64 size, u32 align, bool zero,
		काष्ठा nvkm_memory **pmemory)
अणु
	काष्ठा nvkm_insपंचांगem *imem = device->imem;
	काष्ठा nvkm_memory *memory;
	पूर्णांक ret;

	अगर (unlikely(target != NVKM_MEM_TARGET_INST || !imem))
		वापस -ENOSYS;

	ret = nvkm_instobj_new(imem, size, align, zero, &memory);
	अगर (ret)
		वापस ret;

	*pmemory = memory;
	वापस 0;
पूर्ण
