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
#समावेश <nvअगर/mmu.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/अगर0008.h>

व्योम
nvअगर_mmu_dtor(काष्ठा nvअगर_mmu *mmu)
अणु
	kमुक्त(mmu->kind);
	kमुक्त(mmu->type);
	kमुक्त(mmu->heap);
	nvअगर_object_dtor(&mmu->object);
पूर्ण

पूर्णांक
nvअगर_mmu_ctor(काष्ठा nvअगर_object *parent, स्थिर अक्षर *name, s32 oclass,
	      काष्ठा nvअगर_mmu *mmu)
अणु
	अटल स्थिर काष्ठा nvअगर_mclass mems[] = अणु
		अणु NVIF_CLASS_MEM_GF100, -1 पूर्ण,
		अणु NVIF_CLASS_MEM_NV50 , -1 पूर्ण,
		अणु NVIF_CLASS_MEM_NV04 , -1 पूर्ण,
		अणुपूर्ण
	पूर्ण;
	काष्ठा nvअगर_mmu_v0 args;
	पूर्णांक ret, i;

	args.version = 0;
	mmu->heap = शून्य;
	mmu->type = शून्य;
	mmu->kind = शून्य;

	ret = nvअगर_object_ctor(parent, name ? name : "nvifMmu", 0, oclass,
			       &args, माप(args), &mmu->object);
	अगर (ret)
		जाओ करोne;

	mmu->dmabits = args.dmabits;
	mmu->heap_nr = args.heap_nr;
	mmu->type_nr = args.type_nr;
	mmu->kind_nr = args.kind_nr;

	ret = nvअगर_mclass(&mmu->object, mems);
	अगर (ret < 0)
		जाओ करोne;
	mmu->mem = mems[ret].oclass;

	mmu->heap = kदो_स्मृति_array(mmu->heap_nr, माप(*mmu->heap),
				  GFP_KERNEL);
	mmu->type = kदो_स्मृति_array(mmu->type_nr, माप(*mmu->type),
				  GFP_KERNEL);
	अगर (ret = -ENOMEM, !mmu->heap || !mmu->type)
		जाओ करोne;

	mmu->kind = kदो_स्मृति_array(mmu->kind_nr, माप(*mmu->kind),
				  GFP_KERNEL);
	अगर (!mmu->kind && mmu->kind_nr)
		जाओ करोne;

	क्रम (i = 0; i < mmu->heap_nr; i++) अणु
		काष्ठा nvअगर_mmu_heap_v0 args = अणु .index = i पूर्ण;

		ret = nvअगर_object_mthd(&mmu->object, NVIF_MMU_V0_HEAP,
				       &args, माप(args));
		अगर (ret)
			जाओ करोne;

		mmu->heap[i].size = args.size;
	पूर्ण

	क्रम (i = 0; i < mmu->type_nr; i++) अणु
		काष्ठा nvअगर_mmu_type_v0 args = अणु .index = i पूर्ण;

		ret = nvअगर_object_mthd(&mmu->object, NVIF_MMU_V0_TYPE,
				       &args, माप(args));
		अगर (ret)
			जाओ करोne;

		mmu->type[i].type = 0;
		अगर (args.vram) mmu->type[i].type |= NVIF_MEM_VRAM;
		अगर (args.host) mmu->type[i].type |= NVIF_MEM_HOST;
		अगर (args.comp) mmu->type[i].type |= NVIF_MEM_COMP;
		अगर (args.disp) mmu->type[i].type |= NVIF_MEM_DISP;
		अगर (args.kind    ) mmu->type[i].type |= NVIF_MEM_KIND;
		अगर (args.mappable) mmu->type[i].type |= NVIF_MEM_MAPPABLE;
		अगर (args.coherent) mmu->type[i].type |= NVIF_MEM_COHERENT;
		अगर (args.uncached) mmu->type[i].type |= NVIF_MEM_UNCACHED;
		mmu->type[i].heap = args.heap;
	पूर्ण

	अगर (mmu->kind_nr) अणु
		काष्ठा nvअगर_mmu_kind_v0 *kind;
		माप_प्रकार argc = काष्ठा_size(kind, data, mmu->kind_nr);

		अगर (ret = -ENOMEM, !(kind = kदो_स्मृति(argc, GFP_KERNEL)))
			जाओ करोne;
		kind->version = 0;
		kind->count = mmu->kind_nr;

		ret = nvअगर_object_mthd(&mmu->object, NVIF_MMU_V0_KIND,
				       kind, argc);
		अगर (ret == 0)
			स_नकल(mmu->kind, kind->data, kind->count);
		mmu->kind_inv = kind->kind_inv;
		kमुक्त(kind);
	पूर्ण

करोne:
	अगर (ret)
		nvअगर_mmu_dtor(mmu);
	वापस ret;
पूर्ण
