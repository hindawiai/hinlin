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
#समावेश <nvअगर/स्मृति.स>
#समावेश <nvअगर/client.h>

#समावेश <nvअगर/अगर000a.h>

पूर्णांक
nvअगर_mem_ctor_map(काष्ठा nvअगर_mmu *mmu, स्थिर अक्षर *name, u8 type, u64 size,
		  काष्ठा nvअगर_mem *mem)
अणु
	पूर्णांक ret = nvअगर_mem_ctor(mmu, name, mmu->mem, NVIF_MEM_MAPPABLE | type,
				0, size, शून्य, 0, mem);
	अगर (ret == 0) अणु
		ret = nvअगर_object_map(&mem->object, शून्य, 0);
		अगर (ret)
			nvअगर_mem_dtor(mem);
	पूर्ण
	वापस ret;
पूर्ण

व्योम
nvअगर_mem_dtor(काष्ठा nvअगर_mem *mem)
अणु
	nvअगर_object_dtor(&mem->object);
पूर्ण

पूर्णांक
nvअगर_mem_ctor_type(काष्ठा nvअगर_mmu *mmu, स्थिर अक्षर *name, s32 oclass,
		   पूर्णांक type, u8 page, u64 size, व्योम *argv, u32 argc,
		   काष्ठा nvअगर_mem *mem)
अणु
	काष्ठा nvअगर_mem_v0 *args;
	u8 stack[128];
	पूर्णांक ret;

	mem->object.client = शून्य;
	अगर (type < 0)
		वापस -EINVAL;

	अगर (माप(*args) + argc > माप(stack)) अणु
		अगर (!(args = kदो_स्मृति(माप(*args) + argc, GFP_KERNEL)))
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		args = (व्योम *)stack;
	पूर्ण
	args->version = 0;
	args->type = type;
	args->page = page;
	args->size = size;
	स_नकल(args->data, argv, argc);

	ret = nvअगर_object_ctor(&mmu->object, name ? name : "nvifMem", 0, oclass,
			       args, माप(*args) + argc, &mem->object);
	अगर (ret == 0) अणु
		mem->type = mmu->type[type].type;
		mem->page = args->page;
		mem->addr = args->addr;
		mem->size = args->size;
	पूर्ण

	अगर (args != (व्योम *)stack)
		kमुक्त(args);
	वापस ret;

पूर्ण

पूर्णांक
nvअगर_mem_ctor(काष्ठा nvअगर_mmu *mmu, स्थिर अक्षर *name, s32 oclass, u8 type,
	      u8 page, u64 size, व्योम *argv, u32 argc, काष्ठा nvअगर_mem *mem)
अणु
	पूर्णांक ret = -EINVAL, i;

	mem->object.client = शून्य;

	क्रम (i = 0; ret && i < mmu->type_nr; i++) अणु
		अगर ((mmu->type[i].type & type) == type) अणु
			ret = nvअगर_mem_ctor_type(mmu, name, oclass, i, page,
						 size, argv, argc, mem);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
